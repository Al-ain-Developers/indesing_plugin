//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/AutoCorrectPanelObserver.cpp $
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

#include "IAutoCorrectPrefs.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "ILanguage.h"
#include "ILanguageList.h"
#include "ILinguisticMgr.h"
#include "ISession.h"
#include "ISubject.h"
#include "IWidgetParent.h"

#include "AutoCorrectPanelObserver.h"
#include "PreferenceUtils.h"
#include "SpellPanelID.h"

AutoCorrectPanelObserverData::AutoCorrectPanelObserverData(IPMUnknown *boss) :
    CObserver(boss)
{
    fControlID = IID_IUNKNOWN;
    fReset = kTrue;
    fMessageID = kInvalidClass;
}


AutoCorrectPanelObserver::AutoCorrectPanelObserver(IPMUnknown *boss):
	AutoCorrectPanelObserverData(boss),
		fInUpdate(kFalse),
		fAttached(kFalse),
		fInApplyToWidget(kFalse),
		fMute(kFalse)
{
}


void AutoCorrectPanelObserver::AutoAttach()
{
    if( fAttached )
        return;
    fAttached = kTrue;

    InterfacePtr<ISubject> pPanel( this->QueryPanelSubject() );
    if( pPanel )
    {
        if( !pPanel->IsAttached( this, IID_IAUTOCORRECTPANELMSG ) )
            pPanel->AttachObserver( this, IID_IAUTOCORRECTPANELMSG );
    }

	InterfacePtr<IAutoCorrectPrefs> autoCorrectPrefs((IAutoCorrectPrefs*)::QuerySessionPreferences( IID_IAUTOCORRECTPREFS ));	
	InterfacePtr<ISubject> workspaceSubject( autoCorrectPrefs, IID_ISUBJECT );
	if( workspaceSubject )
		workspaceSubject->AttachObserver(ISubject::kRegularAttachment, this, IID_IAUTOCORRECTPREFS, IID_IOBSERVER  );

    InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
    if( subject )
    {
        const PMIID nControlID = this->GetControlID();
        if(nControlID != IID_IUNKNOWN && !subject->IsAttached( this, nControlID ) )
            subject->AttachObserver(this, nControlID );
    }

    const AutoCorrectPanelObserverMuter aMuter( this );
    this->SetupWidget();
}


void AutoCorrectPanelObserver::AutoDetach()
{
	if( !fAttached )
		return;
	fAttached = kFalse;

    InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
    if (subject)
    {
        const PMIID nControlID = this->GetControlID();
        if( subject->IsAttached( this, nControlID ) )
            subject->DetachObserver(this, nControlID );
    }

	InterfacePtr<IAutoCorrectPrefs> autoCorrectPrefs((IAutoCorrectPrefs*)::QuerySessionPreferences( IID_IAUTOCORRECTPREFS ));	
	InterfacePtr<ISubject> workspaceSubject( autoCorrectPrefs, IID_ISUBJECT );
	if( workspaceSubject )
		workspaceSubject->DetachObserver(ISubject::kRegularAttachment, this, IID_IAUTOCORRECTPREFS, IID_IOBSERVER  );

    InterfacePtr<ISubject> pPanel( this->QueryPanelSubject() );
    if( pPanel )
    {
        if( pPanel->IsAttached( this, IID_IAUTOCORRECTPANELMSG ) )
            pPanel->DetachObserver( this, IID_IAUTOCORRECTPANELMSG );
    }
}


ILanguage* AutoCorrectPanelObserver::QueryLanguage()
{
    InterfacePtr<ISubject>pPanel( this->QueryPanelSubject() );
    if( !pPanel )
        return nil;

    InterfacePtr<ILanguage>pLanguage( pPanel, IID_ILANGUAGE );
    if( !pLanguage )
        return nil;

    if( !pLanguage->GetLanguageName().empty() )
    {
        pLanguage->AddRef();
        return pLanguage;
    }

    InterfacePtr<ILanguageList>pLanguageList( (ILanguageList*)::QuerySessionPreferences( IID_ILANGUAGELIST ) );
    if( !pLanguageList )
        return nil;

    InterfacePtr<ILanguage>pDefaultLanguage( pLanguageList->QueryDefaultLanguage() );
    if( !pDefaultLanguage || pDefaultLanguage->GetLanguageID() == kLanguageNeutral )
        return nil;

    pLanguage->CopyFrom( pDefaultLanguage );
    pLanguage->AddRef();
    return pLanguage;
}


ISubject* AutoCorrectPanelObserver::QueryPanelSubject()
{
    InterfacePtr<IWidgetParent>pParent( this, IID_IWIDGETPARENT );
    if( !pParent )
        return nil;

    InterfacePtr<IPMUnknown> pPanel( pParent->QueryParentFor( IID_IAUTOCORRECTPANELMSG ) );
    if( !pPanel )
        return nil;

    return (ISubject*)pPanel->QueryInterface( IID_ISUBJECT );

}


IUserDictService* AutoCorrectPanelObserver::QueryUserDictService()
{
    InterfacePtr<const ILanguage>pLanguage( this->QueryLanguage() );
    if( !pLanguage )
        return nil;

    // --- get the Hyphenation Service
    InterfacePtr<IK2ServiceRegistry>    pServices(GetExecutionContextSession(), IID_IK2SERVICEREGISTRY);
    InterfacePtr<IK2ServiceProvider>pLinguMgrService( pServices->QueryDefaultServiceProvider( kLinguisticManagerService ) );
    InterfacePtr<ILinguisticMgr>pLinguMgr( pLinguMgrService, IID_ILINGUISTICMGR );

    IUserDictService *pUserDictService = pLinguMgr->QueryUserDictService( pLanguage );

    // Japanese has no user dict
    //ASSERT_MSG( pUserDictService != nil, "AutoCorrectPanelObserver - no UserDict service" );

    return pUserDictService;
}


void AutoCorrectPanelObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy)
{
	// ==> Please update GetObserverInfo()  <==
   
	if( fInUpdate || this->IsMuted() )
		return;

	//HH	LockUpdate aLock( &fInUpdate );

	if( protocol != this->GetControlID() )
	{
		// INHERITED::Update(theChange, theSubject, protocol, changedBy);
		return;
	}

	this->DoApplyToFocus();
}

bool16	AutoCorrectPanelObserver::DoApplyToFocus()
{
	if( fInApplyToWidget )
		return kFalse;

	return this->ApplyToFocus();
}

bool16 AutoCorrectPanelObserver::SetupWidget()
{
	this->SetReset( kTrue );
	return kTrue;
}

bool16 AutoCorrectPanelObserver::ApplyToWidget()
{
	bool16 bChanged = kFalse;
	return bChanged;
}

bool16 AutoCorrectPanelObserver::ApplyToFocus()
{
	const ClassID nMsg = this->GetMessageID();
	if( nMsg == kInvalidClass )
	{
		ASSERT_MSG( kFalse, "Please override AutoCorrectPanelObserver::ApplyToFocus() or set message ID." );
		return kFalse;
	}

	InterfacePtr<ISubject> pPanel( this->QueryPanelSubject() );
	if( pPanel )
		pPanel->Change( nMsg, IID_IAUTOCORRECTPANELMSG, this );

	return kFalse;
}

void AutoCorrectPanelObserver::Mute( bool16 bOn )
{
	if( bOn )
		++fMute;
	else
	{
		if( fMute > 0 )
			--fMute;
		else
			ASSERT_MSG( kFalse, "AutoCorrectPanelObserver - this has not been muted." );
	}
}

bool16 AutoCorrectPanelObserver::IsMuted() const
{
	return fMute > 0;
}
