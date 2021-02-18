//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/SpellSkipObserver.cpp $
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

#include "IBoolData.h"
#include "ICommand.h"
#include "IControlView.h"
#include "IFindChangeCmdData.h"
#include "IPanelControlData.h"
#include "ISpellPanelOptions.h"
#include "IStringData.h"
#include "ISubject.h"
#include "ITextControlData.h"
#include "ITextWalker.h"
#include "IWidgetParent.h"

#include "CAlert.h"
#include "CmdUtils.h"
#include "SpellPanelID.h"
#include "SpellPanelObserver.h"
#include "TextEditorID.h"
#include "TextPanelID.h"
#include "TextWalkerServiceProviderID.h"
#include "Trace.h"
#include "widgetid.h"

#include "IWorkspace.h"
#include "ITextWalkerSelectionUtils.h"
#include "ITextWalkerScope.h"
#include "Utils.h"

#include "INoteFindChangeSpelling.h"
#include "SpellingServiceID.h"
#include "WalkerScopeOptions.h"
#include "ISpellCheckWalkerData.h"
#include "IWidgetUtils.h"
#include "IKeyFocusHandler.h"
#include "IEventHandler.h"
#include "IDropDownListController.h"
#include "CWalkerScopeObserver.h"

//----------------------------------------------------------------------------------------
// Class SpellSkipObserver
//----------------------------------------------------------------------------------------

class SpellSkipObserver : public SpellPanelObserver
{
public:
		enum	 Mode { kStart, kCancel, kSkip, kFinished };
						SpellSkipObserver(IPMUnknown *boss);

		// SpellPanelObserver: override 
		virtual	bool16	ApplyToFocus();
		virtual	void		AutoAttach();
		virtual	void		AutoDetach();
		virtual	void		Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);


private:
			void			NotifyObserver( ClassID nMsg );
			void			StartCheck();
			void			SetText( const PMString &rText );
			void			SetMode( SpellSkipObserver::Mode nMode );
			void			TerminateWalker();
				
		Mode				fMode;
};


#define CONTROL_PMIID		IID_IBOOLEANCONTROLDATA

//---------------------------------------------------------------
// static functions
//---------------------------------------------------------------

//===============================================================
// CLASS SpellSkipObserver
//===============================================================

CREATE_PMINTERFACE(SpellSkipObserver, kSpellSkipObserver)
#define INHERITED 	SpellPanelObserver

//---------------------------------------------------------------
// SpellSkipObserver constructor 
//---------------------------------------------------------------

SpellSkipObserver::SpellSkipObserver(IPMUnknown *boss) :
	INHERITED(boss),
	fMode( kStart )
{
	this->SetControlID( CONTROL_PMIID );
	this->SetReset( kTrue );
}

//---------------------------------------------------------------
// SpellSkipObserver::TerminateWalker: 
//---------------------------------------------------------------

void SpellSkipObserver::TerminateWalker()
{
	InterfacePtr<IStringData>pWordToSpell( this->QueryWordToSpell() );
	InterfacePtr<ITextWalker>pWalker( this->QueryTextWalker() );
	if (pWalker && pWalker->IsWalking())
		pWalker->Halt( );
}		

//---------------------------------------------------------------
// SpellSkipObserver::AutoAttach: 
//---------------------------------------------------------------

void SpellSkipObserver::AutoAttach()
{
	if( !fAttached )
	{
		INHERITED::AutoAttach();
		this->TerminateWalker();
		this->SetMode( kStart );
		this->AutoAttachToTextWalker();
	}
}

//---------------------------------------------------------------
// SpellSkipObserver::AutoDetach: 
//---------------------------------------------------------------

void SpellSkipObserver::AutoDetach()
{
	if( fAttached )
	{
		this->AutoDetachFromTextWalker();
		this->TerminateWalker();
		
		INHERITED::AutoDetach();
	}
}

//---------------------------------------------------------------
// SpellSkipObserver::Update
//---------------------------------------------------------------

void	SpellSkipObserver::Update( const ClassID& theChange, ISubject*theSubject, const PMIID &protocol, void* changedBy )
{
	// ==> Please update GetObserverInfo()  <==

	// mute checking is after IID_ISPELLPANELMSG
	// mute is here 

	if( protocol == IID_ITEXTWALKERMSG  )
	{
			
		// sent by TextWalker::Suspend()
		if( theChange == kTextWalkerOnSuspendMessage )
		{
			this->SetMode( kSkip );
			return;
		}

		// sent by TextWalker::Halt()
		if( theChange == kTextWalkerOnHaltMessage )
		{
			this->SetMode( kStart );
			return;
		}

		if( theChange == kTextWalkerOnEndMessage )
		{
			//Need to do something ala the find change dialog here, but will have to wait til after Anna, too many changes.
			//PMString alertString = "SpellCheckCompleteAlertStr";
			//alertString.Translate();
			//CAlert::WarningAlert(alertString);
		
			this->SetMode( kFinished );
			return;
		}

		// sent by TextWalkerScopeObserver::NotifyObserver()
		if( theChange == kTextWalkerScopeHasChangedMessage )
		{
			this->SetMode( kStart  );
			return;
		}
	}
	
	if( protocol == IID_ISPELLPANELMSG )
	{
		const SpellPanelObserverMuter aMuter( this );

		// sent by SpellWordObserver::NotifySpellWordObserver
		// sent by SpellWordObserver::SetNewWordToSpell
		if( theChange == kSpellPanelMsgWordHasChanged )
		{		
			// BP 03/31/98: only for enable/disable
			if( fMode == kSkip )
				this->SetMode( kSkip );
			return;
		}

		// sent by SpellWordObserver::NotifyMsgSetToStart.
		if( theChange == kSpellPanelMsgSetToStart )
		{		
			// there are two cases:
			// (1) you click in a word that is correct: 
			//	WordObserver::ApplyToWidget() -> Alternatives,kSpellPanelMsgWordHasBeenCorrected -> SpellSkipObserver
			// (2) you type in a word that is correct
			//	WordObserver, kSpellPanelMsgWordHasChanged -> Alternatives,kSpellPanelMsgWordHasBeenCorrected -> SpellSkipObserver
			// We only want to set the mode to kStart for #1.
			this->SetMode( kStart );
			return;
		}

		// sent by nobody
		if( theChange == kSpellPanelMsgSetToChange )
		{		
			this->SetMode( kSkip );
			return;
		}

		// sent by SpellSkipObserver::NotifySpellWordObserver()
		if( theChange == kSpellPanelMsgResumeChecking )
		{
			this->StartCheck(); 
			return;
		}

		// sent by SpellAlternativesObserver::NotifySpellCorrect
		if( theChange == kSpellPanelMsgWordHasBeenCorrected  )
		{
			InterfacePtr<ITextWalker>pWalker( this->QueryTextWalker() );
			if( !pWalker || pWalker->IsWalking() )
				return;

			// if the dialog opens with a misspelled word we want to be in Change mode.
			InterfacePtr<IBoolData>pBoolData( (IPMUnknown*)changedBy, IID_IBOOLDATA );
			const bool16 bCorrect = pBoolData ? pBoolData->GetBool() : kFalse;
			if( !bCorrect )
				this->SetMode( kSkip );
			return;
		}

		return;
	}

	INHERITED::Update(theChange, theSubject, protocol, changedBy );
}

//---------------------------------------------------------------
// SpellSkipObserver::ApplyToFocus
//---------------------------------------------------------------

bool16 SpellSkipObserver::ApplyToFocus()
{
	if( this->IsControlSelected() )
	{
		switch( fMode )
		{
			case kStart : 
			case kFinished : 
				{
					this->StartCheck(); 
				}
				break;

			case kSkip : 
				{
					InterfacePtr<ITextWalker>pWalker( this->QueryTextWalker() );
					if( pWalker )
					{
						if( pWalker->IsWalking() )
							this->NotifyObserver( kSpellPanelMsgResumeChecking );
						else	
							this->NotifyObserver( kSpellPanelMsgSetToStart );
					}
				}
				break;
		}
		
		this->DeselectControl();
	}
	return kTrue;
}

//---------------------------------------------------------------
// SpellSkipObserver::NotifyObserver
//---------------------------------------------------------------

// see SpellWordObserver::NotifyObserver

void	SpellSkipObserver::NotifyObserver( ClassID nMsg )
{
	if (nMsg == kTextWalkerDoHaltMessage)
	{
		InterfacePtr<ITextWalker>pWalker(this->QueryTextWalker());
		InterfacePtr<ISubject> pWalkerSubject(pWalker, IID_ISUBJECT);
		if (pWalkerSubject)
			pWalkerSubject->Change(nMsg, IID_ITEXTWALKERMSG, this);
		return;
	}

	InterfacePtr<ISubject> pPanel( this->QueryPanelSubject() );
	if( pPanel )
	{
		pPanel->Change( nMsg, IID_ISPELLPANELMSG, this );
	}
}

//---------------------------------------------------------------
// SpellSkipObserver::SetMode
//---------------------------------------------------------------

void SpellSkipObserver::SetMode( SpellSkipObserver::Mode nMode )
{
	// if the word is in the selection, there is no change
	// disable the item if the editbox is identical to the mispelled word.
	bool16 bEnable = nMode != kStart && nMode != kFinished;
	if( nMode == kSkip )
	{
		InterfacePtr<IStringData>pWordToSpell( this->QueryWordToSpell() );	
		const bool16 bSameString = pWordToSpell && this->GetUserCorrectedWord() == pWordToSpell->GetString();	
		bEnable = !bSameString;
	}
	this->NotifyObserver( bEnable ? kSpellPanelMsgChangeEnabled : kSpellPanelMsgChangeDisabled );

	/* HH 6/21/99 
	 * No longer return here if fMode == nMode, weird problem with the dialog opening with Ignore button instead of Start button 
	 * Now we'll always update the text of the button and Notify if we are actually changing mode
	 * Also I think kCancel is obsolete but I'll leave it here since it's so close to shipping
	 */
	
	const bool16 bNewMode = nMode != fMode;

	fMode = nMode;	/* set the new mode */
			
	InterfacePtr<IWidgetParent> parent(this, UseDefaultIID());
	InterfacePtr<IPanelControlData> panel(parent->GetParent(), UseDefaultIID());
           
	switch (fMode)
	{
		case kStart:
		{
			const PMString aStart("S&tart");
			this->SetText(aStart);
			if (bNewMode)
				this->NotifyObserver( kSpellPanelMsgReadyToStart );

			/* reset icon and stat text widgets */
			IControlView* widget = panel->FindWidget(kSpellCompleteIconWidgetID);
            if (widget)
				widget->HideView();
            
			IControlView* statTextWidget = panel->FindWidget(kSpellStatusTextWidgetID);
            if (statTextWidget)
			{
				PMRect frame = statTextWidget->GetFrame();
				frame.Left(15);
				statTextWidget->HideView();
				statTextWidget->SetFrame(frame);	//PMRect(15,15,235,35)
				statTextWidget->ShowView();
			}
			break;
		}
		case kSkip:
		case kCancel:
		{
			const PMString aChange("kSkipButtonInSpellingDialog");
			this->SetText(aChange);
			if (bNewMode)
				this->NotifyObserver( kSpellPanelMsgReadyToChange );

			/* reset icon and stat text widgets */
			IControlView* widget = panel->FindWidget(kSpellCompleteIconWidgetID);
            if (widget)
				widget->HideView();
            
			IControlView* statTextWidget = panel->FindWidget(kSpellStatusTextWidgetID);
            if (statTextWidget)
			{
				PMRect frame = statTextWidget->GetFrame();
				frame.Left(15);
				statTextWidget->HideView();
				statTextWidget->SetFrame(frame);	//PMRect(15,15,235,35)
				statTextWidget->ShowView();
			}
			break;
		}
		case kFinished:
		{
			if (bNewMode)
				this->NotifyObserver( kSpellPanelMsgFinished );
         
			/* show spell check complete icon */
			IControlView* statTextWidget = panel->FindWidget(kSpellStatusTextWidgetID);
            if (statTextWidget)
			{
				PMRect frame = statTextWidget->GetFrame();
				frame.Left(35);
				statTextWidget->HideView();
				statTextWidget->SetFrame(frame);	//PMRect(15,15,235,35)
				statTextWidget->ShowView();
			}
			
			IControlView* widget = panel->FindWidget(kSpellCompleteIconWidgetID);
            if (widget)
				widget->ShowView();
			break;
		}
		default:
			ASSERT_MSG(kFalse, "Unknown spell mode");
			break;
	}
}

//---------------------------------------------------------------
// SpellSkipObserver::SetText
//---------------------------------------------------------------

void SpellSkipObserver::SetText( const PMString &rText )
{
	InterfacePtr<ITextControlData>pData( this, IID_ITEXTCONTROLDATA );
	if( pData && pData->GetString() != rText )	
		pData->SetString( rText );
}

//---------------------------------------------------------------
// SpellSkipObserver::StartCheck
//---------------------------------------------------------------
#if __profile__
#include <Profiler.h>
#endif

void	SpellSkipObserver::StartCheck()
{
#if HEATH
#if __profile__
	::ProfilerInit(collectDetailed, bestTimeBase, 10000, 75);
	::ProfilerClear();
	::ProfilerSetStatus(1);
#endif
#endif

	InterfacePtr<IStringData>pWordToSpell( this->QueryWordToSpell() );
	InterfacePtr<ICommand>pSpellTextCmd( CmdUtils::CreateCommand( kSpellCheckTextCmdBoss ) );	
	if (!pSpellTextCmd)
	{
		ASSERT_FAIL("Cannot create spell cmd");
		return;
	}

	InterfacePtr<IFindChangeCmdData>pData( pSpellTextCmd, IID_IFINDCHANGECMDDATA );
	InterfacePtr<ITextWalker>pWalker( this->QueryTextWalker() );
	InterfacePtr<ISpellPanelOptions> pSpellPanelOptions( this->QuerySpellPanelOptions() );	

	InterfacePtr<IWorkspace> sessionWorkSpace(GetExecutionContextSession()->QueryWorkspace());

	if( !pData || !pWalker || !pSpellPanelOptions )
	{
		ASSERT_MSG( pData != nil, "missing IID_IFINDCHANGECMDDATA at kSpellCheckTextCmdBoss." );		
		ASSERT_MSG( pWalker != nil, " can't find TextWalker." );		
		ASSERT_MSG( pSpellPanelOptions != nil, " can't find ISpellPanelOptions at session's workspace." );		
		return;
	}

	// in InCopy, then set FindChanges flag in
	// NoteFindChangeSpelling interface, so the table content will be skipped in galley view
	InterfacePtr<INoteFindChangeSpelling> fcs(GetExecutionContextSession(), UseDefaultIID());
	ASSERT(fcs != nil);
	fcs->SetStartSpelling(true);

	// Check Spell Backwards. Setting searchBackwards flag in WalkerScopeOptions.

	InterfacePtr<const ISpellCheckWalkerData> spellWalkerData(pWalker, UseDefaultIID());
	bool16 searchBack = kFalse;
	if (spellWalkerData)
		searchBack = spellWalkerData->GetDirection();
	WalkerScopeOptions options = WalkerScopeOptions();
	options.SetSearchBackwards(searchBack);
	
	if (!pWalker->IsWalking())
	{
		IWalkerScopeFactoryUtils::WalkScopeType nScope  = pSpellPanelOptions->GetFindChangeScope();
	
		InterfacePtr<ITextWalkerScope>pScope(static_cast<ITextWalkerScope*>
			(Utils<IWalkerScopeFactoryUtils>()->QueryWalkerScope_UsingSelections(nScope, options)));

			// check the flag is user cancel in the Skip Tables dialog
			if (fcs->GetCancelSkipTables())
			{
				fcs->SetCancelSkipTables(false);
				fcs->SetStartSpelling(false);
				this->SetMode( kStart );
				return;
			}

		if (!pScope)
		{
#if NO_DIALOG
			PMString alertString = "SpellCheckCompleteAlertStr";
			alertString.Translate();
			CAlert::WarningAlert(alertString);
#endif
			//this->SetMode( kFinished );
			fcs->SetStartSpelling(false);
			return;
		}

		InterfacePtr<ITextWalkerClient>pClient(static_cast<ITextWalkerClient*>(::CreateObject(kSpellCheckClientBoss, IID_ITEXTWALKERCLIENT)));
		pWalker->Initialize(pClient,pScope,nil, nil);
	}

	pData->SetTextWalker( pWalker );

	{
 		InterfacePtr<ITextWalkerSelectionUtils>pUtils(pWalker,UseDefaultIID());
 		const TextWalkerSelections_CriticalSection criticalSection(pUtils);
 
		CmdUtils::ProcessCommand( pSpellTextCmd );
	}
	if (!pWalker->IsWalking())
	{
#if NO_DIALOG
		PMString alertString = "SpellCheckCompleteAlertStr";
		alertString.Translate();
		CAlert::WarningAlert(alertString);
#endif
		//this->SetMode(kFinished);
	}
	this->NotifyObserver( kSpellPanelMsgDone );

	fcs->SetStartSpelling(false);

#if HEATH
#if __profile__
	ProfilerSetStatus(0);
	ProfilerDump("\pSpellCheck.prof");
	ProfilerTerm();
#endif
#endif

}



