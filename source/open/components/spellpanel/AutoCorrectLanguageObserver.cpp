//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/AutoCorrectLanguageObserver.cpp $
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

#include "IControlView.h"
#include "IDropDownListController.h"
#include "ILanguage.h"
#include "ILanguageList.h"
#include "ILinguisticMgr.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "ISession.h"
#include "IStringListControlData.h"
#include "ISubject.h"

#include "AutoCorrectPanelObserver.h"
#include "CObserver.h"
#include "LanguageID.h"
#include "LinguisticID.h"
#include "PMString.h"
#include "PreferenceUtils.h"
#include "SpellPanelID.h"
#include "widgetid.h"


//----------------------------------------------------------------------------------------
// Class AutoCorrectLanguageObserver
//----------------------------------------------------------------------------------------

class AutoCorrectLanguageObserver : public AutoCorrectPanelObserver
{
public:
						AutoCorrectLanguageObserver(IPMUnknown *boss);
		
		virtual	void		Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);

		virtual	bool16	ApplyToWidget();
		virtual	bool16	ApplyToFocus();

		virtual	bool16	SetupWidget();
		
protected:
		virtual bool16	SetupStringListControlData();
				int32	FindNumberItem( const ILanguage *pLanguage);
				bool16	GetWidgetData( ILanguage *pLanguage );
				void	NotifyLangHasChanged( const ILanguage *pLanguage );

};


#define CONTROL_PMIID		IID_ISTRINGLISTCONTROLDATA
// #define kNoLanguageString	"[No language]"

//---------------------------------------------------------------
// static functions
//---------------------------------------------------------------

//===============================================================
// CLASS AutoCorrectLanguageObserver
//===============================================================

CREATE_PMINTERFACE(AutoCorrectLanguageObserver, kAutoCorrectLanguageObserverImpl)
#define INHERITED 	AutoCorrectPanelObserver

//---------------------------------------------------------------
// AutoCorrectLanguageObserver constructor 
//---------------------------------------------------------------

AutoCorrectLanguageObserver::AutoCorrectLanguageObserver(IPMUnknown *boss) :
	INHERITED(boss)
{
	this->SetControlID( CONTROL_PMIID );
	this->SetReset( kTrue );
	this->SetMessageID( kAutoCorrectEditorMsgLanguageHasChanged );
}


//---------------------------------------------------------------
// AutoCorrectLanguageObserver::ApplyToWidget
//---------------------------------------------------------------

bool16 AutoCorrectLanguageObserver::ApplyToWidget()
{
	bool16 	bFound = kFalse;
	return bFound;
}

//---------------------------------------------------------------
// AutoCorrectLanguageObserver::ApplyToFocus
//---------------------------------------------------------------

bool16 AutoCorrectLanguageObserver::ApplyToFocus()
{
	InterfacePtr<ILanguage>pLanguage( QueryLanguage() );
	if( !pLanguage )
		return kFalse;
	
	if (this->GetWidgetData( pLanguage ))
	{
		this->NotifyLangHasChanged( pLanguage );
	}

	return kTrue;
}

//---------------------------------------------------------------
// AutoCorrectLanguageObserver::SetupWidget
//---------------------------------------------------------------

bool16 AutoCorrectLanguageObserver::SetupWidget()
{
	if( !INHERITED::SetupWidget() )
		return kFalse;
		
	this->SetupStringListControlData();

	// set up the item
	InterfacePtr<const ILanguage>pLanguage(  QueryLanguage() );
	const int32 nSelect = this->FindNumberItem( pLanguage );
	InterfacePtr<IDropDownListController> pController( this, IID_IDROPDOWNLISTCONTROLLER );
	if( nSelect < 0 )
		pController->Deselect( kTrue );
	else
	{
		pController->Select( nSelect  , kTrue, kFalse );
		this->NotifyLangHasChanged( pLanguage );
	}

	return kFalse;
}

//---------------------------------------------------------------
// AutoCorrectLanguageObserver::Update
//---------------------------------------------------------------

void	AutoCorrectLanguageObserver::Update( const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy )
{
	// ==> Please update GetObserverInfo()  <==
	if( fInUpdate || this->IsMuted() )
		return;

	INHERITED::Update( theChange, theSubject, protocol, changedBy );
}

//---------------------------------------------------------------
// AutoCorrectLanguageObserver::FindNumberItem
//---------------------------------------------------------------

int32 AutoCorrectLanguageObserver::FindNumberItem( const ILanguage *pLanguage  )
{
	// the first entry is always [unknown]
	InterfacePtr<IStringListControlData> pData( this, IID_ISTRINGLISTCONTROLDATA );
	if( !pData || !pLanguage )
		return IStringListControlData::kInvalidStringIndex;
		
	const int32 nMax = pData->Length();

#ifdef DEBUG
	if( nMax <= 0)
		TRACEFLOW_OBSOLETE("Linguistics", "AutoCorrectLanguageObserver - empty language table");
#endif

	const PMString &rName = pLanguage->GetLanguageName();
	for( int32 i = 0; i < nMax; ++i )
	{
		if( rName == pData->GetString( i ) )
			return i;
	}
	
	return IStringListControlData::kInvalidStringIndex;
}

//---------------------------------------------------------------
// AutoCorrectLanguageObserver::SetupStringListControlData
//---------------------------------------------------------------

bool16 AutoCorrectLanguageObserver::SetupStringListControlData()
{
	InterfacePtr<IStringListControlData> pData( this, IID_ISTRINGLISTCONTROLDATA );
	if( !pData )
	{
		// BP 3/4/97: this is temporary disabled because we don't have WPopupControlData yet.
		ASSERT_MSG( kFalse, "AutoCorrectLanguageObserver - could not set up the style popup" );
		return kFalse;
	}
	InterfacePtr<IK2ServiceRegistry>	pServices(GetExecutionContextSession(), IID_IK2SERVICEREGISTRY);
	InterfacePtr<IK2ServiceProvider>pLinguMgrService( pServices->QueryDefaultServiceProvider( kLinguisticManagerService ) );
	InterfacePtr<ILinguisticMgr>pLinguMgr( pLinguMgrService, IID_ILINGUISTICMGR );

	const AutoCorrectPanelObserverMuter aMuter( this );
	
	pData->Clear(kFalse, kFalse);
	
	LinguisticCompareMap tempLangStrings;

	const uint32 nLanguageMax = pLinguMgr->GetLanguageCount();
	for( uint32 i = 0; i < nLanguageMax; ++i )
	{
		// Language
		InterfacePtr<const ILanguage>pLanguage( pLinguMgr->QueryNthLanguage( i ) );
		if( pLanguage )
		{
			// have to do this so we can sort by translated name.
			PMString translatedLang(pLanguage->GetLanguageName());
			translatedLang.Translate();
			tempLangStrings[translatedLang] = pLanguage->GetLanguageName();
		}
	}	
		
	LinguisticCompareMap::iterator m1_Iter;
	for( m1_Iter = tempLangStrings.begin(); m1_Iter != tempLangStrings.end(); m1_Iter++ )
	{
		pData->AddString( m1_Iter->second, IStringListControlData::kEnd, kFalse, kFalse );
	}	
		
	
	return kTrue;
}

//---------------------------------------------------------------
// AutoCorrectLanguageObserver::GetWidgetData
// HH 4/7/99 returns true if the language changed false otherwise.
//---------------------------------------------------------------

bool16 AutoCorrectLanguageObserver::GetWidgetData( ILanguage *pLanguage )
{
	// 'logical const'
	IPMUnknown *pThis = (IPMUnknown *)this;
	InterfacePtr<IDropDownListController> controller( pThis, IID_IDROPDOWNLISTCONTROLLER );
	InterfacePtr<IStringListControlData> pData( pThis, IID_ISTRINGLISTCONTROLDATA );

	const int32 nSelected = controller->GetSelected();
	if( nSelected < 0 )
		return kFalse;

	InterfacePtr<IK2ServiceRegistry>	pServices(GetExecutionContextSession(), IID_IK2SERVICEREGISTRY);
	InterfacePtr<IK2ServiceProvider>pLinguMgrService( pServices->QueryDefaultServiceProvider( kLinguisticManagerService ) );
	InterfacePtr<ILinguisticMgr>pLinguMgr( pLinguMgrService, IID_ILINGUISTICMGR );
	InterfacePtr<ILanguage>pSelectedLanguage( pLinguMgr->QueryLanguage(  pData->GetString( nSelected ) ) );
	if( !pSelectedLanguage )
		return kFalse;
		
	if (! pLanguage->IsEqual(pSelectedLanguage))
	{
		pLanguage->CopyFrom( pSelectedLanguage );	/* Update to the new language */
		
		return kTrue;
	}
	
	return kFalse;
}

//---------------------------------------------------------------
// AutoCorrectLanguageObserver::NotifyLangHasChanged
//---------------------------------------------------------------

void	AutoCorrectLanguageObserver::NotifyLangHasChanged( const ILanguage *pLanguage )
{
	InterfacePtr<ISubject> pPanel( QueryPanelSubject() );
	if( pPanel )
	{
		pPanel->Change( kAutoCorrectEditorMsgLanguageHasChanged, IID_IAUTOCORRECTPANELMSG, (void*)pLanguage );
	}
}

