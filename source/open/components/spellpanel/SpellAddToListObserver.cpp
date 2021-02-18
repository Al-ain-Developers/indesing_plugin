//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/SpellAddToListObserver.cpp $
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

// ----- Interfaces -----

#include "IBoolData.h"
#include "IBooleanControlData.h"
#include "ICommand.h"
#include "IControlView.h"
#include "IHyphenationExceptions.h"
#include "ILanguage.h"
#include "ILinguisticMgr.h"
#include "IPanelControlData.h"
#include "ISpellCheckWalkerData.h"
#include "ISpellPanelOptions.h"
#include "ISpellingService.h"
#include "IStringData.h"
#include "ISubject.h"
#include "ITextControlData.h"
#include "ITriStateControlData.h"
#include "IUserDictService.h"
#include "IWidgetParent.h"

// ----- Includes -----

#include "SpellPanelObserver.h"
#include "TextChar.h"
#include "TextCharBuffer.h"
#include "Trace.h"
#include "UserDictWordList.h"

// ----- Utility files -----

#include "CmdUtils.h"
#include "IDictionaryUtils.h"
#include "IWidgetUtils.h"
#include "PreferenceUtils.h"

// ----- ID.h files -----

#include "DictEditorID.h"
#include "LinguisticID.h"
#include "SpellPanelID.h"
#include "TextPanelID.h"
#include "widgetid.h"
#include "IPrivateSpellingUtils.h"


//----------------------------------------------------------------------------------------
// Class SpellAddToListObserver
//----------------------------------------------------------------------------------------

class SpellAddToListObserver : public SpellPanelObserver
{
public:
						SpellAddToListObserver(IPMUnknown *boss);

		// SpellPanelObserver: override 
		virtual	void		AutoAttach();
		virtual	void		AutoDetach();
		virtual	bool16	ApplyToFocus();
		virtual	bool16	SetupWidget();

		virtual	void		Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);


private:
			void			NotifyObserver();
			bool16		CheckWord( const PMString &rWord, IUserDictService::UserDictType& dictType );
			void			EnableView( bool16 bEnable );
			bool16			GetOpenDialog();
};


#define CONTROL_PMIID		IID_IBOOLEANCONTROLDATA

//---------------------------------------------------------------
// static functions
//---------------------------------------------------------------

//===============================================================
// CLASS SpellAddToListObserver
//===============================================================

CREATE_PMINTERFACE(SpellAddToListObserver, kSpellAddToListObserver)
#define INHERITED 	SpellPanelObserver

//---------------------------------------------------------------
// SpellAddToListObserver constructor 
//---------------------------------------------------------------

SpellAddToListObserver::SpellAddToListObserver(IPMUnknown *boss) :
	INHERITED(boss)
{
	this->SetControlID( CONTROL_PMIID );
	this->SetReset( kTrue );
}

//---------------------------------------------------------------
// SpellAddToListObserver::AutoAttach: 
//---------------------------------------------------------------

void SpellAddToListObserver::AutoAttach()
{
	if( !fAttached )
	{
		// test for DictEditor plugin...
		InterfacePtr<ICommand>pDictEditorCmd( CmdUtils::CreateCommand( kOpenDictEditorCmdBoss ) );
		if( !pDictEditorCmd )
		{
			this->EnableView( kFalse );
			return;
		}

		INHERITED::AutoAttach();

		InterfacePtr<ISubject> pPanel( this->QueryPanelSubject() );
		if( pPanel)
		{ 	
			if (!pPanel->IsAttached( this, IID_ITALANGUAGEOBSERVER ) )
			{
				pPanel->AttachObserver( this, IID_ITALANGUAGEOBSERVER ); 
			
			//if (!pPanel->IsAttached( this, IID_IDICTEDITORMSG ) )
			//	pPanel->AttachObserver( this, IID_IDICTEDITORMSG ); 
			}
		}

		// TBD for Heath: This needs to set up a target based on the Add To popup menu (document or user dictionary)
		// For now, set to nil, which means use user dictionary. This happens in the dictionary editor via
		// the OptnDocumentsListObserver.cpp. PaulS 5/5/2004.
		SetTarget(nil);
	}
}

//---------------------------------------------------------------
// SpellAddToListObserver::AutoDetach: 
//---------------------------------------------------------------

void SpellAddToListObserver::AutoDetach()
{
	if( fAttached )
	{
		InterfacePtr<ISubject> pPanel( this->QueryPanelSubject() );
		if( pPanel)
		{ 	
			if (pPanel->IsAttached( this, IID_ITALANGUAGEOBSERVER ) )
			{
				pPanel->DetachObserver( this, IID_ITALANGUAGEOBSERVER ); 
			//if (pPanel->IsAttached( this, IID_IDICTEDITORMSG ) )
			//	pPanel->DetachObserver( this, IID_IDICTEDITORMSG ); 
			}
		}
		
		INHERITED::AutoDetach();
	}
}

//---------------------------------------------------------------
// SpellAddToListObserver::ApplyToFocus
//---------------------------------------------------------------

bool16 SpellAddToListObserver::ApplyToFocus()
{
	if( this->IsControlSelected() )
	{
		// Open dictionary editor dialog with this misspelled word
		if (GetOpenDialog())
		{
			IUserDictService::UserDictType dictType1;
			
			if( this->CheckWord(this->GetUserCorrectedWord(), dictType1))
			{	
				InterfacePtr<ICommand>pDictEditorCmd( CmdUtils::CreateCommand( kOpenDictEditorCmdBoss ) );
				InterfacePtr<IStringData>pWord( pDictEditorCmd, IID_ISTRINGDATA );
				InterfacePtr<ILanguage>pDictLang( pDictEditorCmd, IID_ILANGUAGE );
				InterfacePtr<IBoolData>pNotWordDict( pDictEditorCmd, IID_INOTWORDDICT );

				ASSERT_MSG( pDictEditorCmd != nil, "SpellAddToListObserver - can't create kOpenDictEditorCmdBoss" );		
				ASSERT_MSG( pWord != nil, "SpellAddToListObserver - missing IID_ISTRINGDATA at OpenDictEditorCmdBoss" );		
				ASSERT_MSG( pDictLang != nil, "SpellAddToListObserver - missing IID_ILANGUAGE at OpenDictEditorCmdBoss" );		
				ASSERT_MSG( pNotWordDict != nil, "SpellAddToListObserver - missing IID_INOTWORDDICT at OpenDictEditorCmdBoss" );		
			
				if( pDictEditorCmd && pWord && pDictLang && pNotWordDict )
				{
					InterfacePtr<const ISubject>pPanel(this->QueryPanelSubject() );
					InterfacePtr<const ISpellCheckWalkerData>pWalkerData( pPanel, UseDefaultIID() );
					InterfacePtr<const ILanguage>pLanguage( pWalkerData, IID_ILANGUAGE );
					
					pWord->Set( this->GetUserCorrectedWord() );
					pDictLang->CopyFrom( pLanguage );
					pNotWordDict->Set(dictType1 == IUserDictService::kNotDict ? kTrue : kFalse);

			 		// BP 12/23/98: #262216 Adding a word to the user dictionary while spell checking does not change the spelling choice when Spelling is reactivated
					// HH 2/18/99: there doesn't appear to be an interface flag on the command.
					InterfacePtr<IBoolData>pModeLessFlag( pDictEditorCmd, UseDefaultIID() );
					if( pModeLessFlag )
						pModeLessFlag->Set( kFalse );
					
					CmdUtils::ProcessCommand( pDictEditorCmd );
					this->NotifyObserver();
					
					IUserDictService::UserDictType dictType;
					const bool16 bEnable = this->CheckWord( this->GetUserCorrectedWord(), dictType );
					this->EnableView( bEnable );
				}
			}
		}
		else	// Add automatically to dictionary and continue spelling
		{
			IUserDictService::UserDictType dictType;
			
			const PMString &originalWord = this->GetUserCorrectedWord();
			if(this->CheckWord(originalWord, dictType))
			{

				// Get all the parameters for adding/removing to dictionary
				InterfacePtr<const ISubject>pPanel(this->QueryPanelSubject() );
				InterfacePtr<const ISpellCheckWalkerData>pWalkerData( pPanel, UseDefaultIID() );
				InterfacePtr<ILanguage>pLanguage( pWalkerData, IID_ILANGUAGE );
				InterfacePtr<ILinguisticMgr>pLinguMgr( this->QueryLinguisticMgr() );
				if( !pLinguMgr || !pLanguage )
					return kFalse;
				
				bool16 bCaseSensitive = kFalse;

				InterfacePtr<ISpellPanelOptions> spellPanelOptions((ISpellPanelOptions*)::QuerySessionPreferences(IID_ISPELLPANELOPTIONS));
				if (spellPanelOptions)
					bCaseSensitive = spellPanelOptions->GetCaseSensitive();

				InterfacePtr<IWidgetParent> parent(this, UseDefaultIID());
				InterfacePtr<IPanelControlData> panel(parent->GetParent(), UseDefaultIID());
				InterfacePtr<IControlView> checkBoxView(panel->FindWidget(kSpellCaseSensitiveWidgetID), IID_ICONTROLVIEW);
				if (checkBoxView)
				{
					InterfacePtr<ITriStateControlData> triState(checkBoxView, UseDefaultIID());
					if (triState)
						bCaseSensitive = triState->IsSelected();
				}
				
				UserDictWordList udStrList;
				bool16 bAdded = Utils<IPrivateSpellingUtils>()->ModifyDictionary(originalWord, kAddToDict, bCaseSensitive, GetTarget(), pLanguage, udStrList );

				// Simulate a click on the "Skip" button so user won't be interrupted and spell checking continues.
				if (bAdded)
				{
					InterfacePtr<IBooleanControlData> skipButton((IBooleanControlData*)Utils<IWidgetUtils>()->QueryRelatedWidget(this, kSpellSkipButtonID, IID_IBOOLEANCONTROLDATA));
					if (skipButton)
					{
						skipButton->Select();
						skipButton->Deselect();

						// Re-enable state of "Add" button now that we skipped to next misspelling.
						const bool16 bEnable = this->CheckWord( this->GetUserCorrectedWord(), dictType );
						this->EnableView( bEnable );
					}
				}
			}
		}

		this->DeselectControl();
	}
	return kTrue;
}

//---------------------------------------------------------------
// SpellAddToListObserver::NotifyObserver
//---------------------------------------------------------------

// see SpellAddToListObserver::NotifyObserver

void	SpellAddToListObserver::NotifyObserver()
{
	InterfacePtr<ISubject> pPanel( this->QueryPanelSubject() );
	if( pPanel )
	{
		pPanel->Change( kSpellPanelMsgDone, IID_ISPELLPANELMSG, this );
	}
}
//---------------------------------------------------------------
// SpellAddToListObserver::SetupWidget
//---------------------------------------------------------------

bool16	SpellAddToListObserver::SetupWidget()
{
	IUserDictService::UserDictType dictType;
	const bool16 bEnable = this->CheckWord( this->GetUserCorrectedWord(), dictType );
	this->EnableView( bEnable );
	return INHERITED::SetupWidget();
}

//---------------------------------------------------------------
// SpellAddToListObserver::Update
//---------------------------------------------------------------

void	SpellAddToListObserver::Update( const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy )
{
	// ==> Please update GetObserverInfo()  <==
	if( fInUpdate || this->IsMuted() )
		return;
		
	// sent by HYPLanguageObserver::NotifyFlagObserver on language changes
	if( protocol == IID_ITALANGUAGEOBSERVER )
	{
		InterfacePtr<const ILanguage>pLang( (const IPMUnknown*)changedBy, UseDefaultIID() );
		if( pLang )
			this->SetupWidget();

		return;
	}
		
	ASSERT_MSG(theChange != kDictEditorMsgWordAdded, "theChange == kDictEditorMsgWordAdded");
	
	if (protocol == IID_ISPELLPANELMSG || protocol == IID_IDICTEDITORMSG )
	{
		//ASSERT_MSG(protocol != IID_IDICTEDITORMSG, "protocol != IID_IDICTEDITORMSG");
	
		const SpellPanelObserverMuter aMuter( this );

		// sent by SpellWordObserver::NotifySpellWordObserver and SpellWordEventHandler::NotifySpellWordObserver on word changes
		if (theChange == kSpellPanelMsgWordHasChanged || theChange == kDictEditorMsgWordAdded)
		{	
			InterfacePtr<ITextControlData>pWordData( (IPMUnknown*)changedBy, IID_ITEXTCONTROLDATA );			
			if( pWordData )
			{
				// If the word is correct, you can't add it.
				// If the word is incorrect, the word only could be added if it's not a grammar error.
				const PMString &rNewString =  pWordData->GetString();				
				IUserDictService::UserDictType dictType;
				const bool16 bEnable = this->CheckWord( rNewString, dictType );
				this->EnableView( bEnable );
			}
			return;
		}


		// BP 09/29/98:   #262225 Duplicate word and capitalization spelling errors do not enable the buttons in the dialog correctly.
		// sent by SpellCheckWalkerClient::NotifyDoSuspend()
		if( theChange == kSpellPanelMsgStartCorrect )
		{
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

	// hkhalfallah: Oct 09 2000
	// This will attach/detach the terminator and save restore the selections.		
	
	INHERITED::Update( theChange, theSubject, protocol, changedBy );
}

//---------------------------------------------------------------
// SpellAddToListObserver::CheckWord
//---------------------------------------------------------------

bool16 SpellAddToListObserver::CheckWord( const PMString &rWord, IUserDictService::UserDictType& dictType )
{
	dictType = IUserDictService::kNone;
	
	const CharCounter nWordLength = rWord.CharCount();
	if( nWordLength == 0 )
	{
		return kFalse;
	}

	// BP 09/29/98:   #262225 Duplicate word and capitalization spelling errors do not enable the buttons in the dialog correctly.
	InterfacePtr<const ISubject>pPanel(this->QueryPanelSubject() );
	InterfacePtr<const ISpellCheckWalkerData>pWalkerData( pPanel, UseDefaultIID() );
	
	// if the word is correct or if we deal witha grammar error return false.
	if( pWalkerData && (pWalkerData->GetSpellResult() == ISpellingService::kCorrect || pWalkerData->GetSpellResult() >= ISpellingService::kGrammarError) )
	{
		return kFalse;
	}

	// BP 12/23/98:  #282119 Add button is disabled
	InterfacePtr<const ILanguage>pLanguage( pWalkerData, IID_ILANGUAGE );
	if( !pLanguage )
		return kFalse;

	InterfacePtr<ILinguisticMgr>pLinguMgr( this->QueryLinguisticMgr() );
	if( !pLinguMgr )
		return kFalse;
	InterfacePtr<IUserDictService>pUserDict(  pLinguMgr->QueryUserDictService( pLanguage ) );
	if (GetTarget() == nil && pUserDict)
	{
		InterfacePtr<IUserDict>mainUserDict(  pUserDict->QueryMainUserDict() );
		// nil target means either main dict not setup yet or no read write dicts available
		// if there is a mainUserDict check if read only.
		if (mainUserDict && pUserDict->IsReadOnly(mainUserDict)) 
			return kFalse;
	}

	// BP 12/23/98:  safety check.
	InterfacePtr<ICommand>pDictEditorCmd( CmdUtils::CreateCommand( kOpenDictEditorCmdBoss ) );
	if( !pDictEditorCmd )
	{
		return kFalse;
	}

	// test for blank
	for( CharCounter i = 0; i < nWordLength; ++i )
	{
		if( rWord[i] == kTextChar_Space )
			return kFalse;
		
		// BP 01/08/99: #286930 K2 gives an assert by checking spelling of mixed of roman and Japanese text.
		//	ASSERT_MSG( CharacterClass::IsClickWordSelect(  rWord[i] ), "SpellAddToListObserver - bad character in word." );
	}

	InterfacePtr<ISpellingService>pDict(  pLinguMgr->QuerySpellingService( pLanguage ) );
	if( !pDict )
	{
		return kFalse;
	}
		
	// BP 04/06/98: calling the spell checker seems to be expensive but Proximity caches.
	// BP 12/23/98:  #282119 Add button is disabled
	// If the word is correct, you can't add it.
	bool16 bEndsWithPeriod;
	const WideString aWideWord( rWord );
	const ISpellingService::SpellResult nResult = pDict->IsCorrect( aWideWord, &bEndsWithPeriod );
	if( nResult == ISpellingService::kCorrect || nResult >= ISpellingService::kGrammarError )
	{
		return kFalse;
	}

	// look for the word in the user dict.
	// If the word is found you cannot add it.
	WideString aTemp;
	
	if (pUserDict)
	{
		dictType = pUserDict->GetCorrectedWord( nil, aWideWord, &aTemp );
	
		if( dictType == IUserDictService::kIsDict )
		{
			ASSERT_MSG(nResult == ISpellingService::kUncapitalizedWord, "SpellAddToListObserver::CheckWord - why didn't pDict->IsCorrect find this?");
			return kFalse;
		}
	}

	return kTrue;
}

//---------------------------------------------------------------
// SpellAddToListObserver::EnableView
//---------------------------------------------------------------

void	SpellAddToListObserver::EnableView( bool16 bEnable )
{
	InterfacePtr<IControlView>pView( this, IID_ICONTROLVIEW );
	if( pView && pView->IsEnabled() != bEnable )
		pView->Enable( bEnable );
}


//---------------------------------------------------------------
// SpellAddToListObserver::GetOpenDialog
//---------------------------------------------------------------

bool16 SpellAddToListObserver::GetOpenDialog()
{
	InterfacePtr<IControlView>pView( this, IID_ICONTROLVIEW );
	if (pView && pView->GetWidgetID() == kSpellAddToListButtonID)
		return kTrue;
	return kFalse;
}



