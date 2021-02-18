//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/SpellCaseSensitiveObserver.cpp $
//  
//  Owner: Heath Horton
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

#include "IBooleanControlData.h"
#include "IControlView.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "ILanguage.h"
#include "ILinguisticMgr.h"
#include "ISubject.h"
#include "ISession.h"
#include "ISpellingService.h"
#include "ISpellPanelOptions.h"
#include "ITriStateControlData.h"

#include "CmdUtils.h"
#include "SpellPanelObserver.h"
#include "PreferenceUtils.h"
#include "SpellPanelID.h"
#include "DictEditorID.h"

//----------------------------------------------------------------------------------------
// Class SpellCaseSensitiveObserver
//----------------------------------------------------------------------------------------
#define INHERITED 	SpellPanelObserver

class SpellCaseSensitiveObserver : public INHERITED
{
public:
					SpellCaseSensitiveObserver(IPMUnknown *boss);

	virtual	void	Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);
	virtual	bool16	SetupWidget();
	
	virtual bool16	ApplyToFocus();
	virtual bool16	ApplyToWidget();

	virtual void	AutoAttach();
	virtual void	AutoDetach();
private:
	void EnableCaseSensitive();
};


#define CONTROL_PMIID		IID_ITRISTATECONTROLDATA

//===============================================================
// CLASS SpellCaseSensitiveObserver
//===============================================================

CREATE_PMINTERFACE(SpellCaseSensitiveObserver, kSpellCaseSensitiveObserverImpl)

//---------------------------------------------------------------
// SpellCaseSensitiveObserver constructor 
//---------------------------------------------------------------

SpellCaseSensitiveObserver::SpellCaseSensitiveObserver(IPMUnknown *boss) :
	INHERITED(boss)
{
	this->SetControlID( CONTROL_PMIID );
	this->SetReset( kTrue );
	//HH	this->SetMessageID( kDictOrderMsgCaseSensitiveHasChanged );
}

void SpellCaseSensitiveObserver::AutoAttach()
{
    InterfacePtr<ISubject> pThisSubject(this, IID_ISUBJECT);
    if(pThisSubject)
    {
        if(!pThisSubject->IsAttached(this, IID_ITRISTATECONTROLDATA))
            pThisSubject->AttachObserver(this, IID_ITRISTATECONTROLDATA);
    }

    INHERITED::AutoAttach();
}

void SpellCaseSensitiveObserver::AutoDetach()
{
    INHERITED::AutoDetach();

	InterfacePtr<ISubject> pThisSubject(this, IID_ISUBJECT);
    if(pThisSubject)
    {
        if(pThisSubject->IsAttached(this, IID_ITRISTATECONTROLDATA))
            pThisSubject->DetachObserver(this, IID_ITRISTATECONTROLDATA);
    }
}

//---------------------------------------------------------------
// SpellCaseSensitiveObserver::SetupWidget
//---------------------------------------------------------------

bool16 SpellCaseSensitiveObserver::SetupWidget()
{
	if( !INHERITED::SetupWidget() )
		return kFalse;

	EnableCaseSensitive();
	
	return kTrue;
}

//---------------------------------------------------------------
// SpellCaseSensitiveObserver::Update
//---------------------------------------------------------------

void	SpellCaseSensitiveObserver::Update( const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy )
{
	// ==> Please update GetObserverInfo()  <==
	if( fInUpdate || this->IsMuted() )
		return;

	if (theChange == kTrueStateMessage || theChange == kFalseStateMessage)
	{
        InterfacePtr<ISpellPanelOptions> spellPanelOptions((ISpellPanelOptions*)::QuerySessionPreferences(IID_ISPELLPANELOPTIONS));
        if (!spellPanelOptions)
            return;

        InterfacePtr<ICommand> applyOptionsCmd(CmdUtils::CreateCommand(kApplySpellPanelOptionsCmdBoss));
        InterfacePtr<ISpellPanelOptions> cmdData(applyOptionsCmd, UseDefaultIID());

        if (!applyOptionsCmd || !cmdData)
            return;

		{
		const SpellPanelObserverMuter aMuter( this );    /* scoped */

        cmdData->CopyFrom(spellPanelOptions);    /* copy previous settings */
		cmdData->SetCaseSensitive(theChange == kTrueStateMessage ? kTrue:kFalse);    /* add word to ignored list */
        CmdUtils::ExecuteCommand(applyOptionsCmd);
		}

		//HH	this->Notify( kDictOrderMsgCaseSensitiveHasChanged );
		
		return;
	}	

 	if (protocol == IID_ISPELLPANELMSG && theChange == kSpellPanelMsgWordHasChanged || theChange == kSpellPanelMsgSelectedItemHasChanged || theChange == kSpellPanelMsgNewWordToSpell)
	{
		EnableCaseSensitive();
	}

	INHERITED::Update( theChange, theSubject, protocol, changedBy );
}

bool16 SpellCaseSensitiveObserver::ApplyToWidget()
{
	//HH	this->Notify( kDictOrderMsgCaseSensitiveHasChanged );
	
	return kTrue;
}

//---------------------------------------------------------------
// SpellCaseSensitiveObserver::ApplyToFocus
//---------------------------------------------------------------

bool16 SpellCaseSensitiveObserver::ApplyToFocus()
{
	InterfacePtr<IBooleanControlData>pData( this, IID_IBOOLEANCONTROLDATA );
	if( pData && pData->IsSelected() )
	{
		//HH	this->Notify( kDictOrderMsgCaseSensitiveHasChanged );
	}

	return kTrue;
}

#if 0
void	SpellCaseSensitiveObserver::NotifyObserver()
{
	InterfacePtr<ISubject> pPanel( this->QueryPanelSubject() );
	if( pPanel )
	{
		InterfacePtr<ITriStateControlData>pData( this, IID_ITRISTATECONTROLDATA );
		const bool16 bSelected =  pData->IsSelected();
		pPanel->Change( kDictEditorMsgBreaksHasChanged, IID_IDICTEDITORMSG, (void*)&bSelected );
	}
}
#endif

void SpellCaseSensitiveObserver::EnableCaseSensitive()
{
	// --- get the Spelling Service
	InterfacePtr<IK2ServiceRegistry>    pServices(GetExecutionContextSession(), IID_IK2SERVICEREGISTRY);
	InterfacePtr<IK2ServiceProvider>pLinguMgrService( pServices->QueryDefaultServiceProvider( kLinguisticManagerService ) );
	InterfacePtr<ILinguisticMgr>pLinguMgr( pLinguMgrService, IID_ILINGUISTICMGR );
	if( !pLinguMgr )
		return;

	InterfacePtr<const ILanguage>pLanguage( this->QueryCurrentLanguage() );
	InterfacePtr<ISpellingService>spelling( pLinguMgr->QuerySpellingService( pLanguage ) );
	bool16 bEnable = kTrue;
	ITriStateControlData::TriState newState = ITriStateControlData::kUnselected;

	// All Languages has no spelling service but is case sensitve
	if( spelling && !spelling->SupportsCaseSensitive())
		bEnable = kFalse;
	else
	{
        InterfacePtr<ISpellPanelOptions> spellPanelOptions((ISpellPanelOptions*)::QuerySessionPreferences(IID_ISPELLPANELOPTIONS));
		if (spellPanelOptions && spellPanelOptions->GetCaseSensitive())
			newState = ITriStateControlData::kSelected;
	}

	InterfacePtr<IControlView>pView( this, IID_ICONTROLVIEW );
	if( pView && pView->IsEnabled() != bEnable )
		 pView->Enable( bEnable );

	InterfacePtr<ITriStateControlData> checkBox(pView, UseDefaultIID());
	if (checkBox && checkBox->GetState() != newState)
		checkBox->SetState(newState, kTrue, kFalse);

}