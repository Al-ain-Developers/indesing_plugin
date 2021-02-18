//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/SpellIgnoreObserver.cpp $
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
#include "SpellPanelObserver.h"

#include "IApplication.h"
#include "ICommand.h"
#include "IControlView.h"
#include "IDynamicSpellCheckCache.h"
#include "IFrameList.h"
#include "IGalleyUtils.h"
#include "ILayoutController.h"
#include "IPanelControlData.h"
#include "ISpellCheckWalkerData.h"
#include "ISpellingPrefs.h"
#include "ISpellingUtils.h"
#include "IPrivateSpellingUtils.h"
#include "ISpellPanelOptions.h"
#include "IStringData.h"
#include "ISubject.h"
#include "ITextEditor.h"
#include "ITextLines.h"
#include "ITextModel.h"
#include "ITextWalker.h"
#include "ITriStateControlData.h"	
#include "IWaxIterator.h"
#include "IWaxLine.h"
#include "IWaxRun.h"
#include "IWaxRunIterator.h"
#include "IWaxStrand.h"

#include "K2SmartPtr.h"
#include "CmdUtils.h"
#include "PMTextUtils.h"
#include "PreferenceUtils.h"
#include "ILayoutUIUtils.h"
#include "Utils.h"
#include "TextChar.h"

#include "SpellPanelID.h"
#include "TextID.h"
#include "TextPanelID.h"
#include "widgetid.h"
#include "WritingModeID.h"
#include "TextEditorImplID.h"

//----------------------------------------------------------------------------------------
// Class SpellIgnoreObserver
//----------------------------------------------------------------------------------------

class SpellIgnoreObserver : public SpellPanelObserver
{
public:
						SpellIgnoreObserver(IPMUnknown *boss);

		// SpellPanelObserver: override 
		virtual	bool16	ApplyToFocus();
		virtual	void		Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);
		virtual	void		AutoAttach();
		virtual	void		AutoDetach();



private:
			void			NotifyObserver( ClassID nMsg );

			bool16		IsSelected() const;
			void			Deselect();
			bool16		IgnoreAll();
};



//===============================================================
// CLASS SpellIgnoreObserver
//===============================================================

CREATE_PMINTERFACE(SpellIgnoreObserver, kSpellIgnoreObserver)

//---------------------------------------------------------------
// SpellIgnoreObserver constructor 
//---------------------------------------------------------------

SpellIgnoreObserver::SpellIgnoreObserver(IPMUnknown *boss)
	:SpellPanelObserver(boss)
{
	InterfacePtr<const ITriStateControlData>pTriData( this, IID_ITRISTATECONTROLDATA );	
	this->SetControlID( pTriData != nil ? IID_ITRISTATECONTROLDATA : IID_IBOOLEANCONTROLDATA );
	this->SetReset( kTrue );
}

//---------------------------------------------------------------
// SpellIgnoreObserver::AutoAttach: 
//---------------------------------------------------------------

void SpellIgnoreObserver::AutoAttach()
{
	if( !fAttached )
	{
		SpellPanelObserver::AutoAttach();
		this->AutoAttachToTextWalker();
	}
}

//---------------------------------------------------------------
// SpellIgnoreObserver::AutoDetach: 
//---------------------------------------------------------------

void SpellIgnoreObserver::AutoDetach()
{
	if( fAttached )
	{
		this->AutoDetachFromTextWalker();
		SpellPanelObserver::AutoDetach();
	}
}

//---------------------------------------------------------------
// SpellIgnoreObserver::ApplyToFocus
//---------------------------------------------------------------

bool16 SpellIgnoreObserver::ApplyToFocus()
{
	if( this->IsControlSelected() )
	{
		const bool16 bIgnore =  this->IgnoreAll();
		InterfacePtr<ITextWalker>pWalker( this->QueryTextWalker() );
		if( pWalker )
		{
			InterfacePtr<ISubject>pPanel(this->QueryPanelSubject() );
			InterfacePtr<ISpellCheckWalkerData>pWalkerData( pPanel, UseDefaultIID() );

			/* HH 4/12/99 Need to set the proper word function if the word ends with a period */
			FuncIsWordChar oldFunc = pWalkerData->GetWordFilter();

			InterfacePtr<IStringData> pWordToSpell( this->QueryWordToSpell() );
			if (pWordToSpell)
			{
				const PMString& word = pWordToSpell->GetString();
				if (!word.IsNull() && word[word.CharCount() - 1] != kTextChar_Period)
					pWalkerData->SetWordFilter(PMCharFilters::SpellingIsWordCharNoPeriod);
			}
			
			if( pWalker->IsWalking() )
				this->NotifyObserver( kSpellPanelMsgResumeChecking );
			else	
				this->NotifyObserver( kSpellPanelMsgSetToStart );
		
			pWalkerData->SetWordFilter(oldFunc);	/* restore original */
		}

		this->DeselectControl();
	}
	return kTrue;
}

//---------------------------------------------------------------
// SpellIgnoreObserver::Update
//---------------------------------------------------------------

void	SpellIgnoreObserver::Update( const ClassID& theChange, ISubject*theSubject, const PMIID &protocol, void* changedBy )
{
	// ==> Please update GetObserverInfo()  <==
	if( this->IsMuted() )
		return;

	if( protocol == IID_ITEXTWALKERMSG  )
	{
		const SpellPanelObserverMuter aMuter( this );

		// sent by SpellCheckWalkerClient::NotifyDoSuspend()
		if( theChange == kTextWalkerOnHaltMessage || theChange == kTextWalkerOnSuspendMessage )
		{
			// if the word is in the selection, there is no change
			InterfacePtr<IControlView>pView( this, IID_ICONTROLVIEW );
			if( pView )
			{
				const bool16 bEnable = theChange == kTextWalkerOnSuspendMessage;
				if( pView->IsEnabled() !=  bEnable )
					pView->Enable( bEnable );
			}
			return;
		}

	}

	if( protocol == IID_ISPELLPANELMSG  )
	{
		const SpellPanelObserverMuter aMuter( this );

		// sent by SpellChangeObserver::SetMode()
		if( theChange == kSpellPanelMsgReadyToChange || theChange == kSpellPanelMsgReadyToStart )
		{
			InterfacePtr<IControlView>pView( this, IID_ICONTROLVIEW );
			if( pView )
			{
				bool16 bEnable = theChange == kSpellPanelMsgReadyToChange;

				// BP 09/23/98:  #262238 The Spelling Ignore All button is incorrectly available for Duplicate word and Capitalization errors.
				if( bEnable )
				{
					// BP 09/29/98:   #262225 Duplicate word and capitalization spelling errors do not enable the buttons in the dialog correctly.
					InterfacePtr<const ISubject>pPanel(this->QueryPanelSubject() );
					InterfacePtr<const ISpellCheckWalkerData>pWalkerData( pPanel, UseDefaultIID() );

					// BP 12/23/98:  #282832 Change All disable
					if( pWalkerData && pWalkerData->GetSpellResult() >= ISpellingService::kGrammarError )
						bEnable = kFalse;
				}

				if( pView->IsEnabled() !=  bEnable )
					pView->Enable( bEnable );
			}
			return;
		}

		// BP 09/23/98:  #262238 The Spelling Ignore All button is incorrectly available for Duplicate word and Capitalization errors.
		// sent by SpellCheckWalkerClient::NotifyDoSuspend()
		if( theChange == kSpellPanelMsgStartCorrect )
		{
			// BP 03/31/98: flag that toggles background spelling
			const IPMUnknown *pSpellCheckWalker = static_cast<const IPMUnknown*>(changedBy);
			InterfacePtr<const ISpellCheckWalkerData>pWalkerData( pSpellCheckWalker, UseDefaultIID() );
			if( pWalkerData )
			{			
				const bool16 bEnable = pWalkerData->GetSpellResult() < ISpellingService::kGrammarError;
				InterfacePtr<IControlView>pView( this, IID_ICONTROLVIEW );
				if( pView && pView->IsEnabled() != bEnable )
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
	SpellPanelObserver::Update(theChange, theSubject, protocol, changedBy );
}

//---------------------------------------------------------------
// SpellIgnoreObserver::NotifyObserver
//---------------------------------------------------------------

// see SpellWordObserver::NotifyObserver

void	SpellIgnoreObserver::NotifyObserver( ClassID nMsg )
{
	InterfacePtr<ISubject> pPanel( this->QueryPanelSubject() );
	if( pPanel )
		pPanel->Change( nMsg, IID_ISPELLPANELMSG, this );
}

//---------------------------------------------------------------
// SpellIgnoreObserver::IgnoreAll
//---------------------------------------------------------------

bool16 SpellIgnoreObserver::IgnoreAll()
{
	InterfacePtr<ISpellPanelOptions> pSpellPanelOptions( this->QuerySpellPanelOptions() );	
	InterfacePtr<IStringData> pWordToSpell( this->QueryWordToSpell() );	
	if( !pSpellPanelOptions || !pWordToSpell || pWordToSpell->GetString().IsEmpty() )
		return kFalse;
		
	if(  pSpellPanelOptions->IsIgnored( pWordToSpell->GetString() ) )
		return kTrue;
	
	InterfacePtr<ICommand>pApplyOptionsCmd( CmdUtils::CreateCommand( kApplySpellPanelOptionsCmdBoss ) );
	InterfacePtr<ISpellPanelOptions>pCmdData( pApplyOptionsCmd, IID_ISPELLPANELOPTIONS );

	if( !pApplyOptionsCmd || !pCmdData )
		return kFalse;

	pCmdData->CopyFrom( pSpellPanelOptions );
	pCmdData->AddToIgnoreList( pWordToSpell->GetString() );
	CmdUtils::ExecuteCommand( pApplyOptionsCmd );

	return kTrue;
}





