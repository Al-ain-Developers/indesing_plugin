//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/SpellCheckWalker.cpp $
//  
//  Owner: Bernd Paradies
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "IApplication.h"
#include "ICellContent.h"
#include "ICommand.h"
#include "IEditBoxAttributes.h"
#include "IEventHandler.h"
#include "IKeyBoard.h"
#include "ILayoutControlData.h"
#include "ISelectionManager.h"
#include "ISpellCheckWalkerData.h"
#include "ISubject.h"
#include "ITextFocus.h"
#include "ITextWalker.h"
#include "ITextParcelList.h"
#include "IWidgetParent.h"
#include "IDocumentPresentation.h"
#include "ITextStoryThread.h"
#include "IOwnedItem.h"
#include "ISpreadLayer.h"
#include "IHierarchy.h"

#include "K2SmartPtr.h"
#include "CmdUtils.h"
#include "DocumentID.h"
#include "HelperInterface.h"
#include "ILayoutUIUtils.h"
#include "ProgressBar.h"
#include "ProgressBarID.h"
#include "ISelectionUtils.h"
#include "Trace.h"
#include "UIDList.h"
#include "ITextWalkerSelectionUtils.h"
#include "ITextWalkerScope.h"
#include "IGalleyUtils.h"
#include "IContainerClassification.h"
#include "ITextFrameColumn.h"
#include "IPageItemVisibilityFacade.h"

#include "ITextModel.h"
#include "WritingModeUIID2.h"
#include "InCopySharedID.h"
#include "LocaleSetting.h"
#include "INoteDataUtils.h"
#include "ISpellPanelOptions.h"
#include "PreferenceUtils.h"

//----------------------------------------------------------------------------------------
// class SaveKeyboardEventHandler
//----------------------------------------------------------------------------------------

class SaveKeyboardEventHandler
{
public:
		SaveKeyboardEventHandler();
		~SaveKeyboardEventHandler();

private:
		IEventHandler *fEH;
};

//SEIssue hmm same code as in TextWalkerSelectionUtils::EnterWalkerSelections_CriticalSection
SaveKeyboardEventHandler::SaveKeyboardEventHandler()
{
	InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IKeyBoard> theKeyBoard(theApp, IID_IKEYBOARD);
	fEH = theKeyBoard->GetKeyFocus();
	if( fEH )
	{
		// BP 06/07/99: #308310 Page views don't update when use KBSCs to Find Next or Change/Find
		//	We don't want to shut down the text editor...
		// BP 06/07/99: #308475 First occurrence of found text not highlighted when selected, followed by asserts
		//	It turns out that the LayoutEventHandler is also a friend. In reality we don't want to switch from
		//	a UI eventhandler to a document event handler. How do we differentiate them? We scan the parents
		//	for LayoutControlData.
		InterfacePtr<const IDocumentPresentation>docEventHandler(fEH, UseDefaultIID() );
		if( docEventHandler )
		{
			fEH = nil;
		}
		else
		{
			InterfacePtr<IWidgetParent>widgetParent(fEH, UseDefaultIID() );
			if( widgetParent )
			{
				InterfacePtr<IPMUnknown>docWindow( widgetParent->QueryParentFor( IDocumentPresentation::kDefaultIID));
				if( docWindow )
				{
					fEH = nil;
				}
			}
		}

		if( fEH )
		{
			theKeyBoard->RelinquishKeyFocus();
		}
	}
}

SaveKeyboardEventHandler::~SaveKeyboardEventHandler()
{
	if( fEH )
	{
		InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
		InterfacePtr<IKeyBoard> theKeyBoard(theApp, IID_IKEYBOARD);

		theKeyBoard->AcquireKeyFocus( fEH );

		// Select the text, if possible
		InterfacePtr<IEditBoxAttributes> editBoxAttributes(fEH, IID_IEDITBOXATTRIBUTES);
		if (editBoxAttributes)
		{
			editBoxAttributes->SelectRange(0, kEndOfRange);
		}
	}

}


//===============================================================
// CLASS SpellCheckWalkerClient
//===============================================================

class SpellCheckWalkerClient : public ITextWalkerClient
{
public:
						SpellCheckWalkerClient(IPMUnknown * boss);
						~SpellCheckWalkerClient();

	virtual	bool16		OnStart( ITextWalker *pWalker );
	virtual	bool16		OnEnd( ITextWalker *pWalker );
	virtual	bool16		OnResume( ITextWalker *pWalker );
	virtual	bool16		OnSuspend( ITextWalker *pWalker );

	virtual	bool16		OnNextPosition( ITextWalker *pWalker, ITextModel *pModel, TextIndex nPosition, TextIndex nStartRange, TextIndex nEndRange, int32 startRangePrcnt, int32 endRangePrcnt, bool16 rangeAdjustable);
	virtual	bool16		OnStoryStart( ITextWalker *pWalker, UID storyUID ) { return kTrue; }
	virtual	void			OnStoryEnd( ITextWalker *pWalker ) { }
	virtual	bool16		OnDocumentStart( ITextWalker *pWalker, const UIDRef &doc );
	virtual	void			OnDocumentEnd( ITextWalker *pWalker ) { }
	virtual	void			SetReplacementCount(int32 nCount) {};
	virtual	int32		GetReplacementCount() { return 0; }
	virtual bool16		UpdateTextRange() { return kTrue; }

DECLARE_HELPER_METHODS()

private:
//	ProgressBarAccessor*		fProgress;
	SaveKeyboardEventHandler* 	fSaveKeyboardEventHandler;

	ISubject *			QueryPanelSubject(ITextWalker *pWalker);
	void					NotifyStartWalking( ITextWalker *pWalker );
	void					NotifyDoSuspend(ITextWalker *pWalker);
	void					NotifyOfWordStatus(ITextWalker *pWalker, const ITextModel *pModel, TextIndex nFoundStart);
	void					NotifyEnd(ITextWalker *pWalker);
	void					NotifySelectedItemHasChanged( const WideString &rText, ITextWalker *pWalker);
	void 					DetermineIfTextIsHidden(const ITextModel* pModel, TextIndex nFoundStart,bool16 &isOverset, bool16 &isInTable, bool16 &isHidden);

	bool16				SuspendWalkAt(  ITextWalker *pWalker, ITextModel* pModel, TextIndex nStartOfWord, int32 nWordLength );
};

//=====================================================
// CLASS SpellCheckWalkerClient
//=====================================================

CREATE_PMINTERFACE(SpellCheckWalkerClient, kSpellCheckClientImpl)
DEFINE_HELPER_METHODS(SpellCheckWalkerClient)
#define INHERITED 		ITextWalkerClient

//---------------------------------------------------------------
// SpellCheckWalkerClient constructor
//---------------------------------------------------------------

SpellCheckWalkerClient::SpellCheckWalkerClient( IPMUnknown *boss) :
	HELPER_METHODS_INIT(boss),
//		fProgress(nil),
		fSaveKeyboardEventHandler(nil)
{
}

SpellCheckWalkerClient::~SpellCheckWalkerClient()
{
	if (fSaveKeyboardEventHandler)
		delete fSaveKeyboardEventHandler;
}
//---------------------------------------------------------------
// SpellCheckWalkerClient::OnStart
//---------------------------------------------------------------

bool16	SpellCheckWalkerClient::OnStart( ITextWalker *pWalker )
{
	if (! fSaveKeyboardEventHandler)
	{
		fSaveKeyboardEventHandler = new SaveKeyboardEventHandler();
	}

	this->NotifyStartWalking( pWalker );
	return kTrue;
}

//---------------------------------------------------------------
// SpellCheckWalkerClient::OnResume
//---------------------------------------------------------------

bool16	SpellCheckWalkerClient::OnResume( ITextWalker *pWalker )
{
	if (! fSaveKeyboardEventHandler)
	{
		fSaveKeyboardEventHandler = new SaveKeyboardEventHandler();
	}

	this->NotifyStartWalking( pWalker );
	return kTrue;
}

//---------------------------------------------------------------
// SpellCheckWalkerClient::OnEnd
//---------------------------------------------------------------

bool16 SpellCheckWalkerClient::OnEnd( ITextWalker *pWalker )
{
	if( pWalker->IsSuspended() )
	{
		this->NotifyDoSuspend(pWalker);
	}

	this->NotifyEnd(pWalker);

	if (fSaveKeyboardEventHandler)
	{
		delete fSaveKeyboardEventHandler;
		fSaveKeyboardEventHandler = nil;
	}

	return kTrue;
}

//---------------------------------------------------------------
// SpellCheckWalkerClient::OnSuspend
//---------------------------------------------------------------

bool16 SpellCheckWalkerClient::OnSuspend( ITextWalker *pWalker )
{
	if( pWalker->IsSuspended() )
	{
		this->NotifyDoSuspend(pWalker);
	}

	if (fSaveKeyboardEventHandler)
	{
		delete fSaveKeyboardEventHandler;
		fSaveKeyboardEventHandler = nil;
	}

	return kTrue;
}

//---------------------------------------------------------------
// SpellCheckWalkerClient::OnNextPosition
//---------------------------------------------------------------

bool16 SpellCheckWalkerClient::OnNextPosition( ITextWalker *pWalker,
									   ITextModel *pModel,
									   TextIndex nPosition,
									   TextIndex nStartRange,
									   TextIndex nEndRange,
									   int32 /* startRangePrcnt */,
									   int32 /* endRangePrcnt */,
									   bool16 rangeAdjustable)
{
	ASSERT_MSG(pWalker != nil, "pWalker != nil");
	ASSERT_MSG(pModel != nil, "pModel != nil");

	InterfacePtr<ISpellCheckWalkerData>pData(pWalker, IID_ISPELLCHECKWALKERDATA);	

	bool16 searchBack = pData->GetDirection();//Spell Backwards Implementation

	if ((!searchBack && nPosition >= nEndRange) || (searchBack && nPosition <= nStartRange))
	{
		return kTrue;
	}

	TextIndex nStart = nPosition;

	bool16 bCorrect, bNoteAnchor = kFalse;

	TextIndex nNewPos = nStart;
	ISpellingService::SpellResult spellRet;

	if (searchBack)
	{
		spellRet = pData->FindNextError(pModel, nStartRange, nPosition, &nStart, &nNewPos);
	}
	else
	{
		spellRet = pData->FindNextError(pModel, nPosition, nEndRange, &nStart, &nNewPos);
	}	

	if (spellRet == ISpellingService::kNoteAnchor || spellRet == ISpellingService::kDeletedText)
	{
		bCorrect = bNoteAnchor = kTrue;
	}
	else if (spellRet == ISpellingService::kCorrect)
	{
		bCorrect = kTrue;
	}
	else
	{
		bCorrect = kFalse;
	}

	const WideString &rText = pData->GetText();
	const int32 nWordLength = rText.Length();

	if (searchBack)
	{
		if (nStart > nPosition - 1 )
		{
			nStart = nPosition - 1;
		}
	}
	else
	{
		if (nNewPos < nPosition + 1)
		{
			nNewPos = nPosition + 1;
		}
	}

	//
	// To deal with problem of starting the search in the middle
	// of a word we adjust the starting point to the first position
	// we have found something. This allows the search to wrap
	// around (if that's the scope) and find the word we started on.
	//
	if (rangeAdjustable)
	{
		int32	delta;
		if (!searchBack)
		{
			if (nStart == kInvalidTextIndex)
			{
				delta = nEndRange - nPosition;
			}
			else
			{
				// delta can be negative because of grammar aspell checking looking
				// backwards up to beginning of para.
				delta = (nStart - nPosition);
			}
			if (delta && pWalker->AdjustRangeToStoryStart(delta))
			{
				// the change was accepted. it is important to leave without doing
				// anything to give the walker a chance to re-synchronize itself.
				return kTrue;
			}
		}
		else
		{
			if (nStart == kInvalidTextIndex)
			{
				delta = nEndRange - nPosition;
			}
			else
			{
				delta = (nEndRange - nNewPos); // ------>>> change this depending on which side of word we want to search
			}

			if ((delta) && (pWalker->AdjustRangeToStoryEnd(delta)))
			{
				// the change was accepted. it is important to leave without doing
				// anything to give the walker a chance to re-synchronize itself.
				return kTrue;
			}
		}
	}
	else
	{
		// If the range is NOT adjustable, then we shouldn't be spellchecking a word that extends beyond our range
		// when we've looped back to the beginning - allow for extending beyond our range for notes or deleted text
		if (!searchBack)
		{
			if (nNewPos > nEndRange && nStart == nEndRange)
			{
				pWalker->MoveTo(nEndRange);
				return kTrue;
			}
		}
		else
		{
			if (nStart < nStartRange && nNewPos == nStartRange)
			{
				pWalker->MoveTo(nStartRange);
				return kTrue;
			}
		}
	}

	if (!searchBack)
	{
		if (bCorrect && nNewPos >= nEndRange)
		{
			pWalker->MoveTo(nEndRange);
			return kTrue;
		}
	}
	else
	{
		if (bCorrect && nStart <= nStartRange)
		{
			pWalker->MoveTo(nStartRange);
			return kTrue;
		}
	}

	ASSERT((nStart == kInvalidTextIndex) ||	
		//hkhalfal Feb 15 2001: spell check looks back up to beginning of para
		//((nStart >= nPosition) &&
		(!searchBack && (nStart < nEndRange) &&
		(nNewPos >= nStart)) || (searchBack && (nStartRange < nNewPos) && (nNewPos >= nStart)));
		//hkhalfal June 07 2001: spell check looks ahead sometimes beyond selected range
		//(nNewPos <= nEndRange)));

	//
	// If we didn't find anything in this range then move the
	// current position to the end of the range and return.
	//

	if ((nStart == kInvalidTextIndex) || (nWordLength == 0))
	{
		if (!searchBack)
		{
			pWalker->MoveTo(nNewPos /*nEndRange*/);	//HH 1/30/01 move to the next position, don't just skip entire range. #392800, I believe this is necessary due to changes in the walker code. Habib?
			TRACEFLOW_OBSOLETE("Old:SpellPanel", "SpellCheckWalkerClient - IComposeScanner could not find the word with CopySurroundingWord(). Skipping...\n");
		}
		else
		{
			pWalker->MoveTo(nStart);
		}
		return kTrue;
	}

	//
	// We found something!
	//
	if (!searchBack)
	{
		if (nNewPos >= nEndRange)
		{
			pWalker->MoveTo(nEndRange);
		}
		else
		{
			pWalker->MoveTo(nNewPos);
		}
	}
	else
	{
		if (nStart <= nStartRange)
		{
			pWalker->MoveTo(nStartRange);
		}
		else
		{
			pWalker->MoveTo(nStart);
		}
	}

	if (!bCorrect)
	{
		bCorrect = this->SuspendWalkAt(pWalker, pModel, nStart, nWordLength);

		// if there is no grammar error, it's an incorrect word.
		const ISpellingService::SpellResult nResult = pData->GetSpellResult();
		if (nResult != ISpellingService::kCorrect)
		{
			this->NotifySelectedItemHasChanged(rText, pWalker);
		}
	}
	return bCorrect;
}


//------------------------------------------------------------------------------------------------
// SpellCheckWalkerClient::IsInOversetText()
//
// Descriptions:
//	Determine if the nFoundStart position is in the overset frame.
//
//	This code is the same as in FindChangeClient.cpp, but there's no implementation inheritance
//------------------------------------------------------------------------------------------------
void SpellCheckWalkerClient::DetermineIfTextIsHidden(const ITextModel* pModel, TextIndex nFoundStart,bool16 &isOverset, bool16 &isInTable, bool16 &isHidden)
{
	InterfacePtr<const ITextParcelList> tpl(pModel->QueryTextParcelList(nFoundStart));
	ParcelKey	key;
	isOverset = kFalse;
	isInTable = kFalse;
	isHidden = kFalse;
	if ((tpl) &&
		((key = tpl->GetParcelContaining(nFoundStart)).IsValid()))
	{
		InterfacePtr<const IParcelList> pl(tpl, UseDefaultIID());
		InterfacePtr<const ICellContent> cellContent(tpl, UseDefaultIID());
		
		InterfacePtr<ITextFrameColumn> tfc(pl->QueryParcelFrame(key));
		InterfacePtr<IHierarchy> hier(tfc,UseDefaultIID());
		if (hier)
		{
			InterfacePtr<ISpreadLayer> itemSpreadLayer(::GetDataBase(hier), hier->GetLayerUID(), UseDefaultIID());
			if (itemSpreadLayer && !itemSpreadLayer->IsVisible())
				isHidden = kTrue;
			else if (Utils<Facade::IPageItemVisibilityFacade>()->IsHidden(::GetUIDRef(tfc)))
				isHidden = kTrue;
		}

		
		isInTable = (cellContent) ? kTrue : kFalse;
		if (pl->GetParcelFrameUID(key) == kInvalidUID)
		{
			isOverset = kTrue;
		}
		else if (LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS))
		{
			// in InCopy we create a frame to hold overset text so that copyfit
			// information will be as accurate as possible - check the classification
			// of the tfc to see if it is overset or not (fix bug 612429)
			InterfacePtr<IContainerClassification> classifier(tfc, UseDefaultIID());
			if (classifier && classifier->GetClassification() == IContainerClassification::kOversetContainer)
			{
				isOverset = kTrue;
			}
		}
	}
	else
	{
		// could be in a note or deleted text as they do not have a parcel list...let's check;
		// fix bug 617933 (micheleg, 6/18/2003)
		InterfacePtr<ITextStoryThread> storyThread(pModel->QueryStoryThread(nFoundStart));
		if (storyThread)
		{
			InterfacePtr<IOwnedItem> ownedItem(::GetDataBase(pModel), storyThread->GetDictUID(), UseDefaultIID());
			if (ownedItem && (::GetClass(ownedItem) == kDeletedTextBoss ||
				Utils<INoteDataUtils>()->IsNoteOwnedItem(::GetClass(ownedItem))))
				return;
		}
		
		InterfacePtr<IFrameList>frameList(pModel->QueryFrameList());
		if (frameList && frameList->GetFrameCount() > 0)
		{
			// If text is overset check also to see if the last frame is on a hidden layer. So treat the overset text as though it lives in the
			// last frame.
			InterfacePtr<ITextFrameColumn> lastFrame(frameList->QueryNthFrame(frameList->GetFrameCount() - 1));
			ASSERT_MSG(lastFrame != nil, "FindChangeClient::DetermineIfTextIsHidden() Something is wrong, could not find last frame in framelist");
			InterfacePtr<IHierarchy> lastFrameHier(lastFrame, UseDefaultIID());
			InterfacePtr<ISpreadLayer> lastFrameLayer(::GetDataBase(lastFrameHier), lastFrameHier->GetLayerUID(), UseDefaultIID());
			if (lastFrameLayer && !lastFrameLayer->IsVisible())
				isHidden = kTrue;
			else if (Utils<Facade::IPageItemVisibilityFacade>()->IsHidden(::GetUIDRef(lastFrame)))
				isHidden = kTrue;
		}

		isOverset = kTrue;
	}
}

//---------------------------------------------------------------
// SpellCheckWalkerClient::OnDocumentStart
//---------------------------------------------------------------

bool16 SpellCheckWalkerClient::OnDocumentStart( ITextWalker* pWalker, const UIDRef& doc )
{
	return kTrue;
}

//---------------------------------------------------------------
// SpellCheckWalkerClient::SuspendWalkAt
//---------------------------------------------------------------

bool16 SpellCheckWalkerClient::SuspendWalkAt( ITextWalker *pWalker,
											  ITextModel *pModel,
											  TextIndex nStartOfWord,
											  int32 nWordLength )
{
	UIDRef textStory (::GetDataBase(pModel), ::GetUID(pModel));

	InterfacePtr<ITextWalkerSelectionUtils>twSelectUtils(pWalker, IID_ITEXTWALKERSELECTIONUTILS);
	twSelectUtils->SelectText(textStory, nStartOfWord, nWordLength );
	pWalker->SetClientSelection(nStartOfWord, nWordLength);
	pWalker->Suspend();
	NotifyOfWordStatus( pWalker, pModel, nStartOfWord);
	this->NotifyDoSuspend(pWalker);
	return kFalse;
}

//---------------------------------------------------------------
// SpellCheckWalkerClient::NotifyStartWalking
//---------------------------------------------------------------

// see TextWalkerObserver::NotifyStartWalking, don't call INHERITED.

void	SpellCheckWalkerClient::NotifyStartWalking( ITextWalker *pWalker )
{
	InterfacePtr<ISubject> pPanel( this->QueryPanelSubject(pWalker) );
	if( pPanel )
	{
		pPanel->Change( kSpellPanelMsgTextWalker, IID_ISPELLPANELMSG, pWalker );
	}
}

//---------------------------------------------------------------
// SpellCheckWalkerClient::NotifyDoSuspend
//---------------------------------------------------------------

// see TextWalkerObserver::NotifyDoSuspend, don't call INHERITED.

// BP 4/11/97: #204356 The Spelling Scope Status text is incorrect during interactive spell checks.
//	Now the TextWalkerObserver sends a kTextWalkerDoSuspendMessage and kTextWalkerDoHaltMessage
//	message before entering/leaving the interactive spelling mode. These messages are received by the SpellScopeObserver.
//	The SpellScopeObserver now suspends itself during interactive spelling mode.

void	SpellCheckWalkerClient::NotifyOfWordStatus(ITextWalker *pWalker, const ITextModel *pModel, TextIndex nFoundStart)
{
	InterfacePtr<ISubject> pSubject( this->QueryPanelSubject(pWalker) );

	bool16 inLayout = kTrue;

	if (LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS))
	{
		IDocumentPresentation *galleyWindow = Utils<IGalleyUtils>() ? Utils<IGalleyUtils>()->FindFrontmostGalleyPresentation() : nil;

		if (galleyWindow && Utils<IGalleyUtils>()->InGalleyOrStory(galleyWindow))
		{
			// we don't want to show "overset text" in galley view ever
			pSubject->Change(kWalkText, IID_ITEXTWALKERMSG);
			inLayout = kFalse;
		}
	}

	if (inLayout)
	{
		bool16 isOverset, isInTable, isHidden;
		DetermineIfTextIsHidden( pModel,  nFoundStart, isOverset, isInTable, isHidden);
		
		if (isHidden)
		{
			pSubject->Change(kWalkHiddenLayerText, IID_ITEXTWALKERMSG, pWalker);
		}
		else if (isOverset)
		{
			pSubject->Change(kWalkOverSetText, IID_ITEXTWALKERMSG, pWalker);
		}
		else if (isInTable)
		{
			pSubject->Change(kWalkTextInTable, IID_ITEXTWALKERMSG, pWalker);
		}
		else
		{
			pSubject->Change(kWalkText, IID_ITEXTWALKERMSG, pWalker);
		}
	}
}

void	SpellCheckWalkerClient::NotifyDoSuspend(ITextWalker *pWalker)
{
	InterfacePtr<ISubject> pSubject( this->QueryPanelSubject(pWalker) );

	if( pSubject )
	{
		pSubject->Change( kSpellPanelMsgStartCorrect, IID_ISPELLPANELMSG, pWalker/*this*/ );
	}
}

//---------------------------------------------------------------
// SpellCheckWalkerClient::NotifyEnd
//---------------------------------------------------------------

// see TextWalkerObserver::NotifyEnd, don't call INHERITED.

// BP 4/11/97: #204356 The Spelling Scope Status text is incorrect during interactive spell checks.
//	Now the TextWalkerObserver sends a kTextWalkerDoSuspendMessage and kTextWalkerDoHaltMessage
//	message before entering/leaving the interactive spelling mode. These messages are received by the SpellScopeObserver.
//	The SpellScopeObserver now suspends itself during interactive spelling mode.

void	SpellCheckWalkerClient::NotifyEnd(ITextWalker *pWalker)
{
	InterfacePtr<ISubject> pPanel( this->QueryPanelSubject(pWalker) );
	if( pPanel )
	{
		pPanel->Change( kSpellPanelMsgEndCorrect, IID_ISPELLPANELMSG, pWalker/*this*/ );
	}
}

//---------------------------------------------------------------
// SpellCheckWalkerClient::NotifySelectedItemHasChanged
//---------------------------------------------------------------

// notify	kSpellPanelMsgSelectedItemHasChanged: SpellWordObserver ->
//		kSpellPanelMsgWordHasChanged: SpellAlternativesObserver, SpellLightObserver, SpellCheckWalkerClient(blocked)
void	SpellCheckWalkerClient::NotifySelectedItemHasChanged( const WideString &rText, ITextWalker *pWalker)
{
	InterfacePtr<ISubject> pSubject( this->QueryPanelSubject(pWalker) );
	if( pSubject )
	{
		pSubject->Change( kSpellPanelMsgSelectedItemHasChanged, IID_ISPELLPANELMSG, pWalker/*this*/ );
	}

}

//---------------------------------------------------------------
// SpellCheckWalkerClient::QueryPanelSubject
//---------------------------------------------------------------

ISubject *SpellCheckWalkerClient::QueryPanelSubject(ITextWalker *pWalker)
{
	InterfacePtr<IPMUnknown>pThisPanel( pWalker, IID_IPANELCONTROLDATA );
	if( pThisPanel )
	{
		return (ISubject*)pWalker->QueryInterface( IID_ISUBJECT );
	}

	InterfacePtr<IWidgetParent>pParent( pWalker, IID_IWIDGETPARENT );
	if( !pParent )
	{
		return nil;
	}

	InterfacePtr<IPMUnknown>pPanel( pParent->QueryParentFor( IID_IPANELCONTROLDATA ) );
	if( !pPanel )
	{
		return nil;
	}

	return (ISubject*)pPanel->QueryInterface( IID_ISUBJECT );
}
