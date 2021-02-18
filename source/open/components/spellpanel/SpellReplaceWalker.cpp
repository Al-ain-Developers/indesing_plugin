//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/SpellReplaceWalker.cpp $
//  
//  Owner:
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
#include "ICmdCollection.h"
#include "ICommand.h"
#include "IComposeScanner.h"
#include "IDocument.h"
#include "IDrawingStyle.h"
#include "IEditBoxAttributes.h"
#include "IEventHandler.h"
#include "IFindChangeOptions.h"
#include "IGalleyUtils.h"
#include "IHyphenationStyle.h"
#include "IKeyBoard.h"
#include "ILanguage.h"
#include "ILayoutControlData.h"
#include "IReplaceAllTextData.h"
#include "IReplaceAllTextUtil.h"
#include "IPanelControlData.h"
#include "IFindChangeUtils.h"
#include "ISpellingUtils.h"
#include "ITextLines.h"
#include "ITextModel.h"
#include "ITextWalker.h"
#include "ITextWalkerProgressMonitor.h"
#include "IWidgetParent.h"

#include "CmdUtils.h"
#include "HelperInterface.h"
#include "InCopySharedID.h"
#include "K2Vector.tpp"
#include "ILayoutUIUtils.h"
#include "ILayoutUIUtils.h"
#include "NoteID.h"
#include "PMTextUtils.h"
#include "ProgressBar.h"
#include "SpellPanelID.h"
#include "TextChar.h"
#include "TextEditorID.h"
#include "TextID.h"
#include "TextWalkerServiceProviderID.h"
#include "Trace.h"
#include "UnicodeClass.h"
#include "Utils.h"
#include "WideString.h"
#include "IItemLockData.h"
#include "IInCopySharedUtils.h"
#include "ConditionalTextID.h"
#include "ISpellCheckWalkerData.h"


//----------------------------------------------------------------------------------------
// class SaveKeyboardEventHandler2
//----------------------------------------------------------------------------------------

class SaveKeyboardEventHandler2
{
public:
		SaveKeyboardEventHandler2();
		~SaveKeyboardEventHandler2();

private:
		IEventHandler *fEH;
};


SaveKeyboardEventHandler2::SaveKeyboardEventHandler2()
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
		InterfacePtr<const ILayoutControlData>testForLayoutControlData(fEH, UseDefaultIID() );
		if( testForLayoutControlData )
			fEH = nil;
		else
		{
			InterfacePtr<IWidgetParent>widgetParent(fEH, UseDefaultIID() );
			if( widgetParent )
			{
				InterfacePtr<IPMUnknown>layoutControlData( widgetParent->QueryParentFor( IID_ILAYOUTCONTROLDATA ) );
				if( layoutControlData )
					fEH = nil;
			}
		}

		if( fEH )
			theKeyBoard->RelinquishKeyFocus();
	}
}

SaveKeyboardEventHandler2::~SaveKeyboardEventHandler2()
{
	if( fEH )
	{
		InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
		InterfacePtr<IKeyBoard> theKeyBoard(theApp, IID_IKEYBOARD);

		theKeyBoard->AcquireKeyFocus( fEH );

		// Select the text, if possible
		InterfacePtr<IEditBoxAttributes> editBoxAttributes(fEH, IID_IEDITBOXATTRIBUTES);
		if (editBoxAttributes)
			editBoxAttributes->SelectRange(0, kEndOfRange);
	}
}

//===============================================================
// CLASS SpellReplaceWalkerClient
//===============================================================

class SpellReplaceWalkerClient : public ITextWalkerClient
{
public:
					SpellReplaceWalkerClient(IPMUnknown * boss);
					~SpellReplaceWalkerClient();

	virtual	bool16		OnStart( ITextWalker *pWalker );
	virtual	bool16		OnEnd( ITextWalker *pWalker );
	virtual	bool16		OnResume( ITextWalker *pWalker );
	virtual bool16		OnSuspend( ITextWalker *pWalker ) { return kTrue; }

	virtual	bool16		OnNextPosition( ITextWalker *pWalker, ITextModel *pModel, TextIndex nPosition, TextIndex nStartRange, TextIndex nEndRange, int32 startRangePrcnt, int32 endRangePrcnt, bool16 rangeAdjustable);
	virtual	bool16		OnStoryStart( ITextWalker *pWalker, UID storyUID );
	virtual	void		OnStoryEnd( ITextWalker *pWalker );
	virtual	bool16		OnDocumentStart( ITextWalker *pWalker, const UIDRef &doc );
	virtual	void		OnDocumentEnd( ITextWalker *pWalker) { }
	virtual void		SetReplacementCount(int32 nCount) { fReplaceCount = nCount;}
	virtual	int32		GetReplacementCount() { return fReplaceCount; }
	virtual bool16		UpdateTextRange() { return kTrue; }

DECLARE_HELPER_METHODS()

private:
	bool16 				OnStart_Resume(ITextWalker *pWalker);
	void				GetACmdSequenceForReplaceAll();
	void 				ResetReplaceAllSatateInfo(bool16 aborted);

	WideString			fFindString;
	WideString			fReplaceString;
	int32				fReplaceCount;
	SaveKeyboardEventHandler2* 	fSaveKeyboardEventHandler2;
	IAbortableCmdSeq			*fReplaceAllSequence;
	bool16						fReplaceAllHasACmdSequence;
	IReplaceAllTextData	*fReplaceAllData;
	IDataBase*					fDataBase;


	bool16				IsFindWord( const WideString &rWord, WideString *pReplaceString ) const;
	bool16				MatchesLanguage( ITextModel *pModel,TextIndex nStart, TextIndex nEnd, UID nLanguage ) const;

	RangeProgressBar		*fProgress;
	bool16					fHaveCheckedForProgressBar;
	int32					fReplaceAllStartPercentage;
	int32					fReplaceAllEndPercentage;
	int32 					fProgressBarPos;
	bool16					fCurrentReplacementStringIsUserString;
	bool16 					fFindStringHasDot;
};


//=====================================================
// CLASS SpellReplaceWalkerClient
//=====================================================

CREATE_PMINTERFACE(SpellReplaceWalkerClient, kSpellReplaceClientImpl)
DEFINE_HELPER_METHODS(SpellReplaceWalkerClient)
#define INHERITED 		ITextWalkerClient


//---------------------------------------------------------------
// SpellReplaceWalkerClient constructor
//---------------------------------------------------------------

SpellReplaceWalkerClient::SpellReplaceWalkerClient( IPMUnknown *boss) :
	HELPER_METHODS_INIT(boss),
		fFindString(),
		fReplaceString(),
		fSaveKeyboardEventHandler2(nil),
		fReplaceAllSequence(nil),
		fReplaceAllData(nil),
		fReplaceAllHasACmdSequence(kFalse),
		fProgress(nil),
		fHaveCheckedForProgressBar(kFalse),
		fReplaceAllStartPercentage(0),
		fReplaceAllEndPercentage(0),
		fProgressBarPos(0),
		fCurrentReplacementStringIsUserString(kFalse),
		fFindStringHasDot(kFalse),
		fDataBase(nil)
{
	fReplaceCount = 0;
}

//---------------------------------------------------------------
// SpellReplaceWalkerClient destructor
//---------------------------------------------------------------

SpellReplaceWalkerClient::~SpellReplaceWalkerClient()
{
	ResetReplaceAllSatateInfo(kFalse);
}


//---------------------------------------------------------------
// SpellReplaceWalkerClient::OnStart
//---------------------------------------------------------------

bool16	SpellReplaceWalkerClient::OnStart( ITextWalker *pWalker )
{
	return this->OnStart_Resume(pWalker);
}

bool16	SpellReplaceWalkerClient::OnEnd( ITextWalker *pWalker )
{
	fFindString.Clear();

	if (fSaveKeyboardEventHandler2)
	{
		delete fSaveKeyboardEventHandler2;
		fSaveKeyboardEventHandler2 = nil;
	}
	ResetReplaceAllSatateInfo(kFalse);
	return kTrue;
}

	//---------------------------------------------------------------
// SpellReplaceWalkerClient::OnResume
//---------------------------------------------------------------

bool16	SpellReplaceWalkerClient::OnResume( ITextWalker *pWalker )
{
	return this->OnStart_Resume(pWalker);
}

//---------------------------------------------------------------
// SpellReplaceWalkerClient::IsFindWord
//---------------------------------------------------------------

/*
BP 09/25/98:  #262895 Change All is case sensitive in some cases and not case sensitive in other cases

"A dogg a dogg a Dogg a Dogg."

(1) 'dogg' to 'Dog'

Word97:	A Dog a Dog a Dog a Dog.
K2:		A Dog a Dog a Dog a Dog.
262895:	A Dog a Dog a Dogg a Dogg.


(2) 'dogg' to 'dog'

Word97:	A dog a dog a Dog a Dog.
K2:		A dog a dog a Dog a Dog.
262895:	A dog a dog a Dog a Dog.


(3) 'Dogg' to 'Dog'

Word97:	A dogg a dogg a Dog a Dog.
K2:		A dog a dog a Dog a Dog.
262895:	A dogg a dogg a Dog a Dog.


(4) 'Dogg' to 'dog'

Word97:	A dogg a dogg a dog a Dog.
K2:		A dog a dog a dog a dog.
262895:	A dogg a dogg a dog a dog.
*/

bool16 SpellReplaceWalkerClient::IsFindWord( const WideString &rTheWord, WideString *pReplaceString ) const
{
	pReplaceString->Clear();
	WideString aTempWord;
	//bool16 bStripHardHyphens = kFalse, bStripDiscretionaryHyphens = kTrue, bConvertApostrophes = kFalse, bConvertHyphens = kFalse
	const WideString &rWord =  Utils<ITextUtils>()->ConvertTextModelText( rTheWord, &aTempWord, kFalse, kTrue, kFalse, kTrue, kFalse );

	if( rWord.Length() != fFindString.Length() || !fFindString.Length() )
		return kFalse;

	// BP 11/11/98: #279675 Deleting misspelled words automatically by using the Change all button does not work
	if( fReplaceString.Length() == 0 )
	{
		// no tricks, it needs to be exact.
		return fFindString == rWord;
	}

	// OPTIMIZATION: cache bFindIsLower and bReplaceIsLower.
	const bool16 bFindIsLower = UnicodeClass::IsLowercase( fFindString[0] );
	const bool16 bReplaceIsLower = UnicodeClass::IsLowercase( fReplaceString[0] );
	const bool16 bWordIsLower = UnicodeClass::IsLowercase( rWord[0] );
	WideString aTemp;

	if( bFindIsLower && !bReplaceIsLower )
	{
		// (1) 'dogg' to 'Dog'
		if( bWordIsLower )
		{
			// 'dogg' to 'Dog'
			return fFindString == rWord;
		}
		else
		{
			// 'Dogg' to 'Dog'
			aTemp = rWord;
			aTemp.Remove( 0, 1 );
			aTemp.Insert( (textchar) UnicodeClass::ToLower( rWord[0] ).GetValue(), 0 );
			return fFindString == aTemp;
		}
	}
	else if( bFindIsLower && bReplaceIsLower )
	{
		// (2) 'dogg' to 'dog'
		if( bWordIsLower )
		{
			// 'dogg' to 'dog'
			return fFindString == rWord;
		}
		else
		{
			// 'Dogg' to 'Dog'
			aTemp = rWord;
			aTemp.Remove( 0, 1 );
			aTemp.Insert( (textchar) UnicodeClass::ToLower( rWord[0] ).GetValue(), 0 );
			if( fFindString != aTemp )
				return kFalse;

			// replace: 'dog' to 'Dog'
			*pReplaceString = fReplaceString;
			pReplaceString->Remove( 0, 1 );
			pReplaceString->Insert( (textchar) UnicodeClass::ToUpper( fReplaceString[0] ).GetValue(), 0 );
			return kTrue;
		}
	}
	else if( !bFindIsLower && !bReplaceIsLower )
	{
		// (3) 'Dogg' to 'Dog'
		if( bWordIsLower )
		{
			// 'dogg' to 'dog'
			aTemp = rWord;
			aTemp.Remove( 0, 1 );
			aTemp.Insert( (textchar) UnicodeClass::ToUpper( rWord[0] ).GetValue(), 0 );
			if( fFindString != aTemp )
				return kFalse;

			// replace: 'Dog' to 'dog'
			*pReplaceString = fReplaceString;
			pReplaceString->Remove( 0, 1 );
			pReplaceString->Insert( (textchar) UnicodeClass::ToLower( fReplaceString[0] ).GetValue(), 0 );
			return kTrue;
		}
		else
		{
			// 'Dogg' to 'Dog'
			return fFindString == rWord;
		}
	}
	else if( !bFindIsLower && bReplaceIsLower )
	{
		// (4) 'Dogg' to 'dog'
		if( bWordIsLower )
		{
			// 'dogg' to 'dog'
			aTemp = rWord;
			aTemp.Remove( 0, 1 );
			aTemp.Insert( (textchar) UnicodeClass::ToUpper( rWord[0] ).GetValue(), 0 );

			return fFindString == aTemp;
		}
		else
		{
			// 'Dogg' to 'Dog', replace: 'Dogg' to 'dog'.
			return rWord == fFindString;
		}
	}

	return kFalse;
}

//---------------------------------------------------------------
// SpellReplaceWalkerClient::OnNextPosition
//---------------------------------------------------------------

bool16 SpellReplaceWalkerClient::OnNextPosition( ITextWalker *					pWalker,
											     ITextModel * 					pModel,
											     TextIndex 						nPosition,
											     TextIndex 						nStartRange, 		/* HH 3/7/00 uncommented these 3 */
											     TextIndex 						nEndRange,
												 int32							startRangePrcnt,
												 int32							endRangePrcnt,
												 bool16							rangeAdjustable)
{
	ASSERT_MSG(pWalker != nil, "pWalker != nil");
	ASSERT_MSG(pModel != nil, "pModel != nil");

	InterfacePtr<IFindChangeOptions> pFindChangeOptions(pWalker->QueryFindChangeOptions());

	//Spell Replace Backwards Implementation

	bool16 searchBack = pFindChangeOptions->GetSearchBackwards(pFindChangeOptions->GetSearchMode());

	InterfacePtr<IItemLockData> itemLockData(pModel, IID_IITEMLOCKDATA);
	if (itemLockData && itemLockData->GetInsertLock())
	{
		// can't change the model so we are done.
		//ResetReplaceAllSatateInfo(kTrue);
		//return kFalse;

		// Bug # 616540
		// actually we can't change THIS model, there may be more!
		// when walking multiple stories in a document we do want to change
		// the unlocked stories, ResetReplaceAllSatateInfo(kTrue) had the effect of "undoing"
		// all legal changes before this.
		
		if (searchBack)
		{
			pWalker->MoveTo(nStartRange);	// Move to the start of the range
		}
		else
		{
			pWalker->MoveTo(nEndRange);	// Move to the end of the range
		}
		return kTrue;
	}

	if (!fHaveCheckedForProgressBar )
	{
		ASSERT( !fProgress);
		fHaveCheckedForProgressBar = kTrue;
		InterfacePtr<ITextWalkerProgressMonitor>
			pProgressMonitor(this, IID_ITEXTWALKERPROGRESSMONITOR);

		if(pProgressMonitor)
			fProgress = pProgressMonitor->GetWalkerProgressMonitor();
		fReplaceAllStartPercentage = startRangePrcnt;
	}

	if (fProgress && fProgress->WasCancelled())
	{
		ResetReplaceAllSatateInfo(kTrue);
		return kFalse;
	}

 	if (fProgress)
 	{
		int32 ratio = 0;
		if (searchBack)
		{
			ratio = (nEndRange - nStartRange) > 0 ?
				((nEndRange - nPosition ) * (endRangePrcnt - startRangePrcnt)) / (nEndRange - nStartRange)
				:
				(endRangePrcnt - startRangePrcnt);
		}
		else
		{
			ratio = (nEndRange - nStartRange) > 0 ?
				((nPosition - nStartRange) * (endRangePrcnt - startRangePrcnt)) / (nEndRange - nStartRange)
				:
				(endRangePrcnt - startRangePrcnt);
		}
 		
		fProgressBarPos = (fReplaceAllStartPercentage + startRangePrcnt + ratio)/2;
 		fProgress->SetPosition(fProgressBarPos) ;
 		fReplaceAllEndPercentage = endRangePrcnt;
 	}

	if (!fReplaceAllData) // Client Changed to SpellReplaceWalkerClient
	{
		fDataBase = ::GetDataBase(pModel);
		InterfacePtr<IPMUnknown> pBoss (::CreateObject(kReplaceAllTextDataBoss, IID_IUNKNOWN));
		fReplaceAllData = static_cast<IReplaceAllTextData*>
								(pBoss->QueryInterface (IID_IREPLACEALLTEXTDATA));
		fReplaceAllData->Clear();
		fReplaceAllData->SetTextModel(pModel);

		fReplaceAllData->UseReplacementString(boost::shared_ptr<WideString>(new WideString(fReplaceString)));
		fCurrentReplacementStringIsUserString = kTrue;
		if (searchBack)
		{
			nPosition = nEndRange; // In searchBack, the walker has already moved past the word which has to be replaced. Removing this will result in all words except the selected word getting replaced.
		}
	}

	if (!fReplaceAllHasACmdSequence)
		GetACmdSequenceForReplaceAll();


	// Find the string first
	TextIndex nFoundStart = kInvalidTextIndex;
	TextIndex nFoundEnd = kInvalidTextIndex;

	if (fFindString.Length() > 0)
	{
		if (searchBack)
		{
			Utils<IFindChangeUtils>()->FindThisItem(pModel,fFindString,
				nStartRange,nPosition,
				nFoundStart,nFoundEnd,
				pFindChangeOptions,	0);
		}
		else
		{
			Utils<IFindChangeUtils>()->FindThisItem(pModel,	fFindString,
				nPosition,nEndRange,
				nFoundStart,nFoundEnd,
				pFindChangeOptions,0);
		}
		
		//
		// If we didn't find anything in this range then move the
		// current position to the end of the range and return.
		//
		if (nFoundStart == kInvalidTextIndex)
		{
			if (searchBack)
			{
				pWalker->MoveTo(nStartRange);
			}
			else
			{
				pWalker->MoveTo(nEndRange);	
			}
			return kTrue;
		}
	}
	else
		nFoundStart = nPosition;

	InterfacePtr<IComposeScanner>pScanner( pModel, IID_ICOMPOSESCANNER );
	ASSERT_MSG( pScanner != 0, "SpellReplaceWalkerClient - missing IID_ICOMPOSESCANNER" );

	UID nLanguageUID = kInvalidUID;
	WideString aWord, tmpWord;
	TextIndex nStart = pScanner->CopySurroundingWord( nFoundStart, &tmpWord, &nLanguageUID, fFindStringHasDot >= 0 ? PMCharFilters::SpellingIsWordChar : PMCharFilters::SpellingIsWordCharNoPeriod );

	if( nStart == kInvalidTextIndex || tmpWord.Length() == 0 )
	{
		// just move on...
		if (searchBack)
		{
			if (nStartRange < nFoundStart - 1)
				pWalker->MoveTo(nFoundStart - 1);
			else
				pWalker->MoveTo(nStartRange);
				TRACEFLOW_OBSOLETE("Old:SpellPanel", "SpellReplaceWalkerClient - IComposeScanner could not find the word with CopySurroundingWord(). Skipping...\n");
		}
		else
		{
			if (nEndRange > nFoundStart + 1)
				pWalker->MoveTo(nFoundStart + 1);
			else
				pWalker->MoveTo(nEndRange);
				TRACEFLOW_OBSOLETE("Old:SpellPanel", "SpellReplaceWalkerClient - IComposeScanner could not find the word with CopySurroundingWord(). Skipping...\n");
		}
		return kTrue;
	}

	/* HH 4/12/99 #302129 words with a . don't replace all correctly */
	int32 numLeadingStripped, numTrailingStripped;
	ASSERT_MSG(Utils<ISpellingUtils>() != nil, "Utils<ISpellingUtils>() != nil");
	Utils<ISpellingUtils>()->StripLeadingAndTrailingPunctuation(tmpWord, aWord, numLeadingStripped, numTrailingStripped);
	nStart += numLeadingStripped;

	// BP 09/29/98: #263972 Spelling Change All and Ignore All do not respect the langauge settings.
	const TextIndex nEnd = nStart + aWord.Length();
	if( !this->MatchesLanguage( pModel, nStart, nEnd, nLanguageUID ) )
	{
		if (searchBack)
		{
			if (nStart - numLeadingStripped  > nStartRange)
				pWalker->MoveTo(nStart - numLeadingStripped);
			else
				pWalker->MoveTo(nStartRange);
		}
		else
		{
			if (nEnd + numTrailingStripped  < nEndRange)
				pWalker->MoveTo(nEnd + numTrailingStripped);
			else
				pWalker->MoveTo(nEndRange);
		}

		TRACEFLOW_OBSOLETE("Old:SpellPanel", "SpellReplaceWalkerClient - Skipping word that does not match our language...\n" );
		return kTrue;
	}

	if (!searchBack && nStart >= nEndRange)
	{
		pWalker->MoveTo( nEndRange);
		return kTrue;
	}
	else if (searchBack && nEnd <= nStartRange)
	{
		pWalker->MoveTo(nStartRange);
		return kTrue;
	}


	ASSERT( (nStart < nEndRange) && (nEnd <= nEndRange) &&
			(nEnd >= nStart) &&
			(nStart>= nStartRange) && (nEnd > nStartRange) );

	//
	// To deal with problem of starting the search in the middle
	// of a word we adjust the starting point to the first position
	// we have found something. This allows the search to wrap
	// around (if that's the scope) and find the word we started on.
	//
	if (rangeAdjustable)
	{
		int32	delta;
		if (searchBack)
		{
			delta = (nEndRange - nEnd);
			if ((delta) &&
				(pWalker->AdjustRangeToStoryEnd(delta)))
			{
				// the change was accepted. it is important to leave without doing
				// anything to give the walker a chance to re-synchronize itself.
				return kTrue;
			}
		}
		else
		{
			delta = (nStart - nPosition);
			if ((delta) &&
				(pWalker->AdjustRangeToStoryStart(delta)))
			{
				// the change was accepted. it is important to leave without doing
				// anything to give the walker a chance to re-synchronize itself.
				return kTrue;
			}
		}
		
	}

	int32 nWordLength = aWord.Length();

	/* HH 3/15/99 seperated out the BP's if below */
	if ( nWordLength == 0)
	{
		if (searchBack)
		{
			if (nFoundStart > nStartRange)
				pWalker->MoveTo(nFoundStart - 1);
			else
				pWalker->MoveTo(nStartRange);
		}
		else
		{
			if (nFoundStart + numLeadingStripped + numTrailingStripped  < nEndRange)
				pWalker->MoveTo(nFoundStart + numLeadingStripped + numTrailingStripped + 1);
			else
				pWalker->MoveTo(nEndRange);
		}
		
		TRACEFLOW_OBSOLETE("Old:SpellPanel", "SpellReplaceWalkerClient - IComposeScanner could not find the word with CopySurroundingWord(). Moving one space...\n" );
		return kTrue;
	}

	WideString aDifferentReplaceString;
	if( !this->IsFindWord( aWord, &aDifferentReplaceString ) )
	{
		// just move on...
		if (searchBack)
		{
			if (nFoundStart > nStartRange)
				pWalker->MoveTo(nFoundStart -1); // Go before the entire word.
			else
				pWalker->MoveTo(nStartRange);
		}
		else
		{
			if (nFoundStart + numLeadingStripped + nWordLength + numTrailingStripped < nEndRange)
				pWalker->MoveTo(nFoundStart + numLeadingStripped + nWordLength + numTrailingStripped);	/* HH 3/15/99 Slight optimization here (instead of incrementing 1 go forward the whole word) */
			else
				pWalker->MoveTo(nEndRange);
		}		

		TRACEFLOW_OBSOLETE("Old:SpellPanel", "SpellReplaceWalkerClient - IComposeScanner could not find the word with CopySurroundingWord(). Skipping word...\n" );
		return kTrue;
	}

	WideString * pReplaceString = aDifferentReplaceString.Length() ? &aDifferentReplaceString : &fReplaceString;

	if (aDifferentReplaceString.Length() > 0)
	{
		fReplaceAllData->UseReplacementString(boost::shared_ptr<WideString>(new WideString(aDifferentReplaceString)));
		fCurrentReplacementStringIsUserString = kFalse;
	}
	else
	{
		if (!fCurrentReplacementStringIsUserString)
		{
			fReplaceAllData->UseReplacementString(boost::shared_ptr<WideString>(new WideString(fReplaceString)));
			fCurrentReplacementStringIsUserString = kTrue;
		}
	}

	TextIndex newStart;
	int32 newLength = nWordLength;

	ASSERT_MSG(Utils<ISpellingUtils>() != nil, "Utils<ISpellingUtils>() != nil");
	K2Vector<ClassID> moveOwnedItemClasses;
	moveOwnedItemClasses.push_back(kNoteDataBoss);
	moveOwnedItemClasses.push_back(kHiddenTextBoss);
	bool16 gotMoved = Utils<IInCopySharedUtils>()->MoveOwnedItem(pModel, nStart, nWordLength, newStart, newLength, moveOwnedItemClasses);

	if (gotMoved)
		{
		nStart = newStart;
		nWordLength = newLength;
		}

	fReplaceAllData->SetNextReplacement(nStart, nWordLength);
	fReplaceCount++;
	if (searchBack)
	{
		if (nStart > nStartRange)
			pWalker->MoveTo(nStart- 1);
		else
			pWalker->MoveTo(nStartRange);
	}
	else
	{
		if (nStart + nWordLength + numTrailingStripped < nEndRange)
			pWalker->MoveTo(nStart + nWordLength + numTrailingStripped + 1);
		else
			pWalker->MoveTo(nEndRange);
	}
	return kTrue;
}

//---------------------------------------------------------------
// SpellReplaceWalkerClient::MatchesLanguage
//---------------------------------------------------------------

bool16 SpellReplaceWalkerClient::MatchesLanguage( ITextModel *pModel, TextIndex nStart, TextIndex nEnd, UID nLanguage) const
{
	InterfacePtr<const ILanguage>pLanguage( this, UseDefaultIID() );
	if( !pLanguage || pLanguage->GetLanguageID() == kLanguageNeutral )
		return kTrue;

	if( nLanguage == kInvalidUID )
		return kFalse;

	InterfacePtr<const ILanguage>pFoundLanguage( ::GetDataBase( pModel ), nLanguage, UseDefaultIID() );
	if( !pFoundLanguage )
		return kFalse;

	return pLanguage->IsEqual( pFoundLanguage );
}

//---------------------------------------------------------------
// SpellReplaceWalkerClient::OnDocumentStart
//---------------------------------------------------------------

bool16 SpellReplaceWalkerClient::OnDocumentStart( ITextWalker *, const UIDRef &doc)
{
	fDataBase = doc.GetDataBase();
	return kTrue;
}

//---------------------------------------------------------------
// SpellReplaceWalkerClient::OnStoryStart
//---------------------------------------------------------------

bool16	SpellReplaceWalkerClient::OnStoryStart( ITextWalker *pWalker, UID storyUID )
{
	InterfacePtr<ITextModel>pModel(fDataBase,storyUID,UseDefaultIID());
	return kTrue;
}

void SpellReplaceWalkerClient::OnStoryEnd( ITextWalker *pWalker)
{
	if (fProgress && fProgress->WasCancelled())
	{
		ResetReplaceAllSatateInfo(kTrue);
		return;
	}

	if (fReplaceAllData)
	{
		if (fProgress)
		{
			fReplaceAllData->SetWalkerProgressMonitor(fProgress);
			fReplaceAllData->SetRangeStartPrcnt(fProgressBarPos);
			fReplaceAllData->SetRangeEndPrcnt(fReplaceAllEndPercentage);
		}
		ErrorCode errCode = Utils<IReplaceAllTextUtil>()->DoReplaceAll(fReplaceAllData);
		fReplaceAllStartPercentage = fReplaceAllEndPercentage;
		fReplaceAllData->Release();
	}
	fReplaceAllData = nil;
}
//---------------------------------------------------------------
// static ::CleanupText
//---------------------------------------------------------------

// see ::CleanupText in ProxSpelling.

// BP 5/5/97: #207790 Spelling flags words contianing discretionary hyphens as errors.,
//			#207659 Interactive spell checking flags inline graphics as misspellings.
//			#214437 Spelling flags certain contractions as being misspelled and suggests the same word in the suggested word list.
// Don't strip the '.
// This helper function should be moved to TextChar.cpp.

// BP 10/13/98: #263289 Spelling's Change All function misses 'words' containing non-alpha / non-numeric characters.


bool16 SpellReplaceWalkerClient::OnStart_Resume(ITextWalker *pWalker)
{
	// BP 07/10/98: TODO: right now OnStart() is called twice from TextWalker::WalkAllDocument().
	//	This is unnecessary since the introduction of OnDocumentChange(). After Wai has switched
	//	the code in FindChangeWalker you can remove the following two lines.

	/* HH 3/15/99 I'll go ahead and remove these */
	//if( fReplaceCmd )
	//	return kTrue;

	if (! fSaveKeyboardEventHandler2)
		fSaveKeyboardEventHandler2 = new SaveKeyboardEventHandler2();

	fReplaceCount = 0;
	fFindString.Clear();
	fReplaceString.Clear();

	InterfacePtr<IFindChangeOptions> pFindChangeOptions(pWalker->QueryFindChangeOptions());

	// BP 07/06/98:  #262120 Deleting misspelled word by using the "Change to" button not only deletes them but also replaces with square boxes
	//	There is a bug in WideString. If you do WideString::BuildFromSystemString( PMString() ) you will get WideString.Length() == 1.
	const WideString &rFindStr = pFindChangeOptions->GetFindString(IFindChangeOptions::kTextSearch);
	if( !rFindStr.IsNull() )
		fFindString = rFindStr;//.BuildFromSystemString( rFindStr );
	const WideString &rReplaceStr = pFindChangeOptions->GetReplaceString(IFindChangeOptions::kTextSearch);
	if( !rReplaceStr.IsNull() )
		fReplaceString = rReplaceStr;//.BuildFromSystemString( rReplaceStr );

	if( fFindString == fReplaceString || fFindString.Length() == 0 )
	{
		ASSERT_MSG( fFindString != fReplaceString, "SpellReplaceWalkerClient - find = replace." );
		ASSERT_MSG( fFindString.Length() > 0, "SpellReplaceWalkerClient - no find string." );
		return kFalse;
	}

	/* handle abbreviations and strings with periods properly */
	if (fFindString.Length())
		fFindStringHasDot = fFindString.IndexOf(kTextChar_Period);

	return kTrue;

}

void SpellReplaceWalkerClient::GetACmdSequenceForReplaceAll()
{
	fReplaceAllSequence = CMDUTILS_BEGINABORTABLECMDSEQ(__FILE__,__LINE__);
	fReplaceAllSequence->SetName("Replace Text");
	fReplaceAllHasACmdSequence = kTrue;
}

void SpellReplaceWalkerClient::ResetReplaceAllSatateInfo(bool16 aborted)
{
	if(fReplaceAllSequence)
	{
		if(aborted)
			CmdUtils::AbortCommandSequence(fReplaceAllSequence);
		else
			CmdUtils::EndCommandSequence(fReplaceAllSequence);
	}
	if (fReplaceAllData)
		fReplaceAllData->Release();

	fReplaceAllData = nil;
	fReplaceAllSequence = nil;
	fReplaceAllHasACmdSequence = kFalse;
	fProgress = nil;
	fHaveCheckedForProgressBar= kFalse,
	fReplaceAllStartPercentage = 0,
	fReplaceAllEndPercentage = 0,
	fProgressBarPos = 0;
}
