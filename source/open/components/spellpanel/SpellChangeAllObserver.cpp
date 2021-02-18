//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/SpellChangeAllObserver.cpp $
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
#include "ShuksanID.h"

#include "ICmdCollection.h"
#include "ICommand.h"
#include "IControlView.h"
#include "IDocumentPresentation.h"
#include "IFindChangeCmdData.h"
#include "IFindChangeService.h"
#include "ILanguage.h"
#include "ISpellCheckWalkerData.h"
#include "ISpellPanelOptions.h"
#include "IFindChangeOptions.h"
#include "IStringData.h"
#include "ISubject.h"
#include "ITextControlData.h"
#include "ITextFocus.h"
#include "ITextTrackerAccess.h"
#include "ITextWalker.h"
#include "ITriStateControlData.h"
#include "IUIDData.h"
#include "IWorkspace.h"

#include "CAlert.h"
#include "CmdUtils.h"
#include "ILayoutUIUtils.h"
#include "PreferenceUtils.h"
#include "SpellPanelID.h"
#include "SpellPanelObserver.h"
#include "StringUtils.h"
#include "TextID.h"
#include "TextPanelID.h"
#include "TextWalkerServiceProviderID.h"
#include "UnicodeClass.h"
#include "widgetid.h"
#include "CreateObject.h"
#include "ITextWalkerSelectionUtils.h"
#include "ITextModel.h"
#include "ITextWalkerScope.h"
#include "ProgressBar.h"
#include "ITextWalkerProgressMonitor.h"

#include "ISelectionManager.h"
#include "IConcreteSelection.h"
#include "IGalleyUtils.h"
#include "ISelectionUtils.h"
#include "ITextTarget.h"
#include "Utils.h"
#include "IPanelControlData.h"
#include "ITextLines.h"

#include "INoteFindChangeSpelling.h"
#include "IInCopyApp.h"
#include "RangeData.h"

#include "TextEditorID.h"
#include "IItemLockData.h"

#include "SpellingServiceID.h"

//----------------------------------------------------------------------------------------
// Class SpellChangeAllObserver
//----------------------------------------------------------------------------------------

class SpellChangeAllObserver : public SpellPanelObserver
{
public:
						SpellChangeAllObserver(IPMUnknown *boss);

		// SpellPanelObserver: override
		virtual	bool16	ApplyToFocus();
		virtual	void		Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);
		virtual	void		AutoAttach();
		virtual	void		AutoDetach();



private:
			void			NotifyObserver( ClassID nMsg );
			void			ShowFindChangeResult( IFindChangeService::FindChangeResult nResult, int32 nTotalReplaced );
			bool16		IsSelected() const;
			void			Deselect();
			void			DisableOnEqualString();
};


//---------------------------------------------------------------
// static functions
//---------------------------------------------------------------

//===============================================================
// CLASS SpellChangeAllObserver
//===============================================================

CREATE_PMINTERFACE(SpellChangeAllObserver, kSpellChangeAllObserver)
#define INHERITED 	SpellPanelObserver

//---------------------------------------------------------------
// SpellChangeAllObserver constructor
//---------------------------------------------------------------

SpellChangeAllObserver::SpellChangeAllObserver(IPMUnknown *boss) :
	INHERITED(boss)
{
	InterfacePtr<const ITriStateControlData>pTriData( this, IID_ITRISTATECONTROLDATA );
	this->SetControlID( pTriData != nil ? IID_ITRISTATECONTROLDATA : IID_IBOOLEANCONTROLDATA );
	this->SetReset( kTrue );
}

//---------------------------------------------------------------
// SpellChangeAllObserver::AutoAttach:
//---------------------------------------------------------------

void SpellChangeAllObserver::AutoAttach()
{
	if( !fAttached )
	{
		INHERITED::AutoAttach();
		this->AutoAttachToTextWalker();
	}
}

//---------------------------------------------------------------
// SpellChangeAllObserver::AutoDetach:
//---------------------------------------------------------------

void SpellChangeAllObserver::AutoDetach()
{
	if( fAttached )
	{
		this->AutoDetachFromTextWalker();
		INHERITED::AutoDetach();
	}
}

//---------------------------------------------------------------
// SpellChangeAllObserver::ApplyToFocus
//---------------------------------------------------------------

// see FindPanelObserver::DoWalkAndResumeCommand()

bool16 SpellChangeAllObserver::ApplyToFocus()
{
	if( !this->IsControlSelected() )
		return kFalse;

	InterfacePtr<ICommand>pReplaceCmd( CmdUtils::CreateCommand( kSpellReplaceTextCmdBoss ) );
	if(!pReplaceCmd)
	{
		ASSERT_MSG( pReplaceCmd != nil, " can't create kSpellReplaceTextCmdBoss." );
		return kFalse;
	}

	// ensure interfaces
	InterfacePtr<ITextWalker>pWalker( this->QueryTextWalker() );
	if( !pWalker)
	{
		ASSERT_FAIL(" can't find TextWalker." );
		return kFalse;
	}
	if (!pWalker->IsWalking() || !pWalker->IsSuspended())
	{
		ASSERT_FAIL(" Walker must be walking and suspended" );
		return kFalse;
	}

	InterfacePtr<ISubject>pWalkerSubject( pWalker, IID_ISUBJECT );
	InterfacePtr<ISpellPanelOptions> pSpellPanelOptions((ISpellPanelOptions*)::QuerySessionPreferences( IID_ISPELLPANELOPTIONS ));

	InterfacePtr<IFindChangeCmdData>pData( pReplaceCmd, IID_IFINDCHANGECMDDATA );

	InterfacePtr<IFindChangeOptions>
		pFindChangeOptions(static_cast<IFindChangeOptions*>
								(::CreateObject(kSpellCheckFindChangeDataBoss, IID_IFINDCHANGEOPTIONS)));

	ITextFocus* pFocus = pWalker->GetClientSelection(nil, nil);

	if( !pData || !pWalkerSubject || !pSpellPanelOptions || !pFocus )
	{
		ASSERT_MSG( pData != nil, "missing IID_IFINDCHANGECMDDATA at kSpellReplaceTextCmdBoss." );
		ASSERT_MSG( pWalkerSubject != nil, " missing IID_ISUBJECT at TextWalker." );
		ASSERT_MSG( pSpellPanelOptions != nil, " can't find ISpellPanelOptions at session's workspace." );
		return kFalse;
	}

	InterfacePtr<ITextModel>pModel(pFocus, UseDefaultIID());
	UIDRef textStory = ::GetUIDRef(pFocus);

	InterfacePtr<IItemLockData> itemLockData(textStory, IID_IITEMLOCKDATA);
	if (itemLockData && itemLockData->GetInsertLock())
	{
		// can't change the model so we are done.
		return kFalse;
	}

	InterfacePtr<const ISpellCheckWalkerData>pWalkerData( pWalker, UseDefaultIID() );

	// If spell checking was done in backward direction, we will also want change all to change in reverse order. Hence, we need to set the findchangeoptions of the nestedwalker in reverse direction.
	bool16 searchBack = pWalkerData->GetDirection();
	pFindChangeOptions->SetSearchBackwards(searchBack, pFindChangeOptions->GetSearchMode());

	ASSERT(pWalkerData);
	if(!pWalkerData)
		return kFalse;

	const bool16 bOverset = pSpellPanelOptions->GetOverset();

	pData->SetRange( textStory, pFocus->GetStart(nil), kInvalidTextIndex );

	const WideString& findString = pWalkerData->Get_Unnormalized_ModelText();
	pFindChangeOptions->SetFindString( findString, IFindChangeOptions::kTextSearch );
	WideString replaceString  (this->GetUserCorrectedWord());
	pFindChangeOptions->SetReplaceString(replaceString, IFindChangeOptions::kTextSearch);

	InterfacePtr<ILanguage>pCurrentLanguage( this->QueryCurrentLanguage() );
	InterfacePtr<ILanguage>pCmdLanguage( pReplaceCmd, UseDefaultIID() );
	if( pCurrentLanguage && pCmdLanguage )
		pCmdLanguage->CopyFrom( pCurrentLanguage );

	const bool16 bMuted = pWalkerSubject->IsMuted();
	if( !bMuted )
		pWalkerSubject->Mute( kTrue );

	InterfacePtr<INoteFindChangeSpelling> fcs(GetExecutionContextSession(), UseDefaultIID());
	ASSERT(fcs != nil);
	InterfacePtr<IInCopyApp> inCopy(GetExecutionContextSession(), IID_IINCOPYAPP);
	//this falg will only affect galley/story
	fcs->SetStartSpellingAll(true);

	// The problem is that the walker has already moved to the next word. The walker needs
	// to be moved to the word that is questioned, see GetStartPosition().
	pWalker->MoveTo( pFocus->GetStart(nil) );

	InterfacePtr<ITextWalker>nestedWalker(static_cast<ITextWalker*>(::CreateObject(kBasicTextWalkerBoss, IID_ITEXTWALKER)));
	InterfacePtr<ITextWalkerClient>pNewClient(static_cast<ITextWalkerClient*>(::CreateObject(kSpellReplaceClientBoss,IID_ITEXTWALKERCLIENT)));

	//Fixes 515403, Change all changes text in different language. See #263972
	InterfacePtr<ILanguage> pClientLanguage( pNewClient, UseDefaultIID() );
	if (pClientLanguage)
		pClientLanguage->CopyFrom( pCurrentLanguage );

	InterfacePtr<ITextWalkerScope>pScope(pWalker->QueryScope());
	if(!pScope)
	{
		ASSERT_FAIL("Walker not initialized with a valid scope");
		fcs->SetStartSpellingAll(false);

		return kFalse;
	}

	if (inCopy)
	{

	       	// To include tables recalculate scope. Reason, InCopy in Galley and Story views,
   		    // does not collect table content at beginning of the search.
   		    // Note, this will still not work for the selection scope. The reason is that the
   		    // misspelled word will be selected at this time, and we will be using the wrong selection.
            // reset the scope query to include tables
            IWalkerScopeFactoryUtils::WalkScopeType nScope  = pSpellPanelOptions->GetFindChangeScope();
            if (nScope != IWalkerScopeFactoryUtils::kSelectionScope)
            {
	            InterfacePtr<ITextWalkerScope>wScope(static_cast<ITextWalkerScope*>
   	                 (Utils<IWalkerScopeFactoryUtils>()->QueryWalkerScope_UsingSelections(nScope)));

   		         if (!wScope)
   	   		      {
           		         PMString alertString = "SpellCheckCompleteAlertStr";
                 	   		alertString.Translate();
                  		  CAlert::WarningAlert(alertString);
                   	 	fcs->SetStartSpellingAll(false);
                    	return kTrue;
            	 }

	            nestedWalker->Initialize(pNewClient, wScope, pFindChangeOptions, nil);
	        }
	        else
				nestedWalker->Initialize(pNewClient, pScope, pFindChangeOptions, pWalker->GetCursorToken());
    }
    else
		nestedWalker->Initialize(pNewClient, pScope, pFindChangeOptions, pWalker->GetCursorToken());

	InterfacePtr<ITextWalkerProgressMonitor>pProgressMonitor(pNewClient,UseDefaultIID());
	RangeProgressBar* progress = nil;

	if (pProgressMonitor)
	{
		PMString taskText("Replacing text...");
		progress = new RangeProgressBar(taskText, 0, 100, kFalse);
		taskText.Translate();
		pProgressMonitor->SetWalkerProgressMonitor(progress);
	}
	pData->SetTextWalker(nestedWalker);

 	{
 		InterfacePtr<ITextWalkerSelectionUtils>pUtils(pWalker,UseDefaultIID());
 		const TextWalkerSelections_CriticalSection criticalSection(pUtils);


		// get the current story index before change all so we can
		// restore it after the change all is finished; text walker resets story
		// index for galley and story view in order to make changes in the
		// correct textlines so we need to do this stuff here....
		int32 currentStoryIndex = -1;
		IDocumentPresentation* frontWindow = Utils<IGalleyUtils>()->FindFrontmostGalleyPresentation();
		if (frontWindow)
		{
			InterfacePtr<IPanelControlData> windowPanel(frontWindow, IID_IPANELCONTROLDATA);
			IControlView *galleyWidget = windowPanel->FindWidget(kWritingId);
			if (galleyWidget)
			{
				InterfacePtr<ITextLines> textLines(galleyWidget, IID_ITEXTLINES);
				currentStoryIndex = textLines->GetCurrentStoryIndex();
			}
		}

		// process the replace command
		CmdUtils::ProcessCommand( pReplaceCmd );

		// now we go restore the current story index for galley and story views...
		if (frontWindow && currentStoryIndex >= 0)
		{
			InterfacePtr<IPanelControlData> windowPanel(frontWindow, IID_IPANELCONTROLDATA);
			IControlView *galleyWidget = windowPanel->FindWidget(kWritingId);
			if (galleyWidget)
			{
				InterfacePtr<ITextLines> textLines(galleyWidget, IID_ITEXTLINES);
				textLines->SetCurrentStoryIndex(currentStoryIndex);
			}
		}
 	}

	if (progress)
		delete progress;

	if( !bMuted )
		pWalkerSubject->Mute( kFalse );

	if (findString.Length() != replaceString.Length())
	{
		InterfacePtr<ISelectionManager> selMgr(Utils<ISelectionUtils>()->QueryActiveSelection()); 
		InterfacePtr<ITextTrackerAccess> focusAccess(selMgr, UseDefaultIID()); 
		InterfacePtr<ITextFocus> activeFocus(focusAccess->QueryTextFocus()); 
		InterfacePtr<ITextModel>pActiveFocusModel( activeFocus->QueryModel() );
		InterfacePtr<ITextModel>pFocusModel( pFocus->QueryModel() );
		TextIndex startIndex = activeFocus->GetStart(nil);
		
		/* sachsing: Fix for #3736420.
		 			Changing "startIndex+replaceString.Length() <= pActiveFocusModel->TotalLength()" check to
		 			"startIndex+replaceString.Length() < pActiveFocusModel->TotalLength()" to 
		 			avoid the selection to move outside the selectable range.
			 (ToDo) There are some selection issues associated with Change All of spell check. Need to be revisted.
		 */
		ASSERT(pActiveFocusModel == pFocusModel && startIndex+replaceString.Length() < pActiveFocusModel->TotalLength());
		if (pActiveFocusModel == pFocusModel
			&& startIndex+replaceString.Length() < pActiveFocusModel->TotalLength())
		{
			UIDRef storyRef = ::GetUIDRef(pActiveFocusModel); 
			InterfacePtr<ITextWalkerSelectionUtils>twSelectUtils(pWalker, IID_ITEXTWALKERSELECTIONUTILS);
			twSelectUtils->SelectText(storyRef, activeFocus->GetStart(nil), replaceString.Length());
		}
	}

	// get the nResult from command's action
	const IFindChangeService::FindChangeResult nResult = pData->GetFindChangeResult();
	const int32 totalReplacementCount = pData->GetReplacementCount();

	this->ShowFindChangeResult( nResult, totalReplacementCount );
	this->NotifyObserver( kSpellPanelMsgDone );

	// continue...
	pWalker->Walk();

	fcs->SetStartSpellingAll(false);

	return kTrue;
}

//---------------------------------------------------------------
// SpellChangeAllObserver::Update
//---------------------------------------------------------------

void	SpellChangeAllObserver::Update( const ClassID& theChange, ISubject*theSubject, const PMIID &protocol, void* changedBy )
{
	// ==> Please update GetObserverInfo()  <==
	if( this->IsMuted() )
		return;

	if( protocol == IID_ISPELLPANELMSG  )
	{
		const SpellPanelObserverMuter aMuter( this );

		// sent by SpellChangeObserver::SetMode()
		if( theChange == kSpellPanelMsgChangeEnabled || theChange == kSpellPanelMsgChangeDisabled )
		{
			// if the word is in the selection, there is no change
			InterfacePtr<IControlView>pView( this, IID_ICONTROLVIEW );
			if( pView )
			{
				bool16 bEnable = theChange == kSpellPanelMsgChangeEnabled;

				if( bEnable )
				{
					// BP 09/29/98:   #262225 Duplicate word and capitalization spelling errors do not enable the buttons in the dialog correctly.
					InterfacePtr<const ISubject>pPanel(this->QueryPanelSubject() );
					InterfacePtr<const ISpellCheckWalkerData>pWalkerData( pPanel, UseDefaultIID() );

					// BP 12/23/98:  #282832 Change All disable
					if( pWalkerData && pWalkerData->GetSpellResult() >= ISpellingService::kGrammarError )
						bEnable = kFalse;

					// disable if the misspelled word has whitespace. HH 3/30/99
					if (bEnable)
					{
						InterfacePtr<IStringData>pMisspelledWord( this->QueryWordToSpell() );
						if (pMisspelledWord)
						{
							int32 i;
							const PMString& word = pMisspelledWord->GetString();
							for (i = 0; i < word.CharCount(); ++i)
							{
								if (UnicodeClass::IsWhiteSpace(word.GetWChar(i)))
								{
									bEnable = kFalse;
									break;
								}
							}
						}
					}
				}

				if( pView->IsEnabled() !=  bEnable )
					pView->Enable( bEnable );
			}
			return;
		}
	}

	if (protocol == IID_ITEXTWALKERMSG	&& theChange ==  kTextWalkerOnEndMessage)
	{
		InterfacePtr<IControlView>pView( this, IID_ICONTROLVIEW );
		pView->Enable( kFalse );
	}
	INHERITED::Update(theChange, theSubject, protocol, changedBy );
}

//---------------------------------------------------------------
// SpellChangeAllObserver::NotifyObserver
//---------------------------------------------------------------

// see SpellWordObserver::NotifyObserver

void	SpellChangeAllObserver::NotifyObserver( ClassID nMsg )
{
	InterfacePtr<ISubject> pPanel( this->QueryPanelSubject() );
	if( pPanel )
		pPanel->Change( nMsg, IID_ISPELLPANELMSG, this );
}

//---------------------------------------------------------------
// SpellChangeAllObserver::ShowFindChangeResult
//---------------------------------------------------------------

void	SpellChangeAllObserver::ShowFindChangeResult( IFindChangeService::FindChangeResult nResult, int32 nTotalReplaced )
{
	// see ShowFindChangeResult() of FindChangeUtils.cpp .
	PMString alertString( "Search is completed.  ^1  replacement(s) made." );
	alertString.Translate();
	PMString replaceCountStr;
	replaceCountStr.AsNumber(nTotalReplaced);
	::ReplaceStringParameters(&alertString, replaceCountStr );

	CAlert::ModalAlert(alertString,
						   "OK",
						   kNullString,
					       kNullString,
						   1,
						   CAlert::eWarningIcon);
}


