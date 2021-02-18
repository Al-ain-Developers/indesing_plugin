//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/SpellTargetListObserver.cpp $
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
//  
//  Proj:	DictEditor
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "IApplication.h"
#include "ICommand.h"
#include "IControlView.h"
#include "IDataBase.h"
#include "IDocumentList.h"
#include "IDropDownListController.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "ILanguage.h"
#include "ILanguageList.h"
#include "ILinguisticMgr.h"
#include "ISession.h"
#include "IStringListControlData.h"
#include "ISubject.h"
#include "IUserDictService.h"
#include "IVendorList.h"

#include "SpellPanelID.h"
#include "DictEditorID.h"
#include "SpellPanelObserver.h"
#include "FileUtils.h"
#include "LinguisticID.h"
#include "PMString.h"
#include "PreferenceUtils.h"
#include "UIDList.h"
#include "Utils.h"
#include "widgetid.h"


//----------------------------------------------------------------------------------------
// Class SpellTargetListObserver
//
// for Firedrake we now can have multiple dictionaries as well
//----------------------------------------------------------------------------------------
#define INHERITED 	SpellPanelObserver

class SpellTargetListObserver : public INHERITED
{
public:
						SpellTargetListObserver(IPMUnknown *boss);

	virtual	void		Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);
	virtual void		AutoAttach();
	virtual void 		AutoDetach();
	virtual	bool16		ApplyToWidget();
	virtual	bool16		ApplyToFocus();
	virtual	bool16		SetupWidget();
	


private:
			void		NotifyTargetHasChanged(const void* target);
			bool16		SetupStringListControlDataAndList(void);
			IPMUnknown*	GetWidgetData();
			
	IUserDict*			fTargetUserDictionary;
};


#define CONTROL_PMIID		IID_ISTRINGLISTCONTROLDATA

//---------------------------------------------------------------
// static functions
//---------------------------------------------------------------

CREATE_PMINTERFACE(SpellTargetListObserver, kSpellTargetListObserverImpl)


SpellTargetListObserver::SpellTargetListObserver(IPMUnknown *boss) :
	INHERITED(boss),
		fTargetUserDictionary(nil)
{
	this->SetControlID( CONTROL_PMIID );
	this->SetReset( kTrue );
	//this->SetMessageID( kDictEditorMsgOpenDocsListHasChanged );
}


bool16 SpellTargetListObserver::ApplyToWidget()
{
	bool16 	bFound = kFalse;
	return bFound;
}


bool16 SpellTargetListObserver::ApplyToFocus()
{
	IPMUnknown * target = this->GetWidgetData();
	
	if (target != fTargetUserDictionary)
	{
		this->SetTarget(target);
		this->NotifyTargetHasChanged(target);
		
		fTargetUserDictionary = (IUserDict*)target;
	}

	return kTrue;
}


bool16 SpellTargetListObserver::SetupWidget()
{
	if( !INHERITED::SetupWidget() )
		return kFalse;
		
	this->SetupStringListControlDataAndList();

	ApplyToFocus();

	return kFalse;
}


void SpellTargetListObserver::AutoAttach()
{
	if (fAttached)
		return;

	INHERITED::AutoAttach();

	InterfacePtr<ILanguageList> sessionLangList( (ILanguageList*)::QuerySessionPreferences(IID_ILANGUAGELIST));
	InterfacePtr<ISubject> subject(sessionLangList, IID_ISUBJECT);
	if( subject )
	{
		if( !subject->IsAttached( this, IID_ISPELLVENDORLIST ) )
			subject->AttachObserver(this, IID_ISPELLVENDORLIST );
	}

	fTargetUserDictionary = nil;
}


void SpellTargetListObserver::AutoDetach()
{
	if (!fAttached)
		return;
	
	this->SetTarget(nil);

	InterfacePtr<ILanguageList> sessionLangList( (ILanguageList*)::QuerySessionPreferences(IID_ILANGUAGELIST));
	InterfacePtr<ISubject> subject(sessionLangList, IID_ISUBJECT);
	if (subject)
	{
		if (subject->IsAttached(this, IID_ISPELLVENDORLIST))
			subject->DetachObserver(this, IID_ISPELLVENDORLIST);
	}

	INHERITED::AutoDetach();
}

void	SpellTargetListObserver::Update( const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy )
{
	// ==> Please update GetObserverInfo()  <==
	if( fInUpdate || this->IsMuted() )
		return;

	if (protocol == IID_ISPELLPANELMSG)
	{
		if (theChange == kSpellPanelMsgWordHasChanged || theChange == kSpellPanelMsgSelectedItemHasChanged || theChange == kSpellPanelMsgNewWordToSpell)
		{
			// if the language changed we want to change this
			SetupStringListControlDataAndList();
			ApplyToFocus();								/* update list */
		}
	}

	if (protocol == IID_ISPELLVENDORLIST)
	{
		//if (theChange == kxxx)
		{
			SetupStringListControlDataAndList();
			ApplyToFocus();								/* update list */
		}
	}

	if (protocol == IID_IDICTEDITORMSG)
	{
		switch (theChange.Get())
		{
			case kDictOrderMsgDictionaryAdded:
			case kDictOrderMsgRemoveDictionary:
			case kDictOrderMsgReloadDictionary:
			case kDictOrderMsgRelinkDictionary:
			case kDictOrderMsgReorderDictionary:
			{
				SetupStringListControlDataAndList();
				ApplyToFocus();								/* update list */
			}
			break;
		}

		/* if the language changed update the list */
		if (theChange == kDictEditorMsgLanguageHasChanged || theChange == kDictEditorMsgDefaultDictCreated)
		{
			SetupStringListControlDataAndList();
			ApplyToFocus();								/* update list */
		}

		if (theChange == kDictEditorMsgListHasChanged)
		{
			SetupStringListControlDataAndList();
			ApplyToFocus();								/* update list */
		}
	}

	INHERITED::Update( theChange, theSubject, protocol, changedBy );
}

bool16 SpellTargetListObserver::SetupStringListControlDataAndList()
{
	InterfacePtr<IStringListControlData> pController( this, IID_ISTRINGLISTCONTROLDATA );
	InterfacePtr<IK2ServiceRegistry> pServices(GetExecutionContextSession(), IID_IK2SERVICEREGISTRY);
	InterfacePtr<IK2ServiceProvider> pLinguMgrService( pServices->QueryDefaultServiceProvider( kLinguisticManagerService ) );
	InterfacePtr<ILinguisticMgr> pLinguMgr( pLinguMgrService, IID_ILINGUISTICMGR );

	const SpellPanelObserverMuter aMuter( this );
	
	// Save selection in case we can restore it after filling in menu
	PMString previousItemName;
	InterfacePtr<IDropDownListController> wordListController( this, IID_IDROPDOWNLISTCONTROLLER );
	int32 oldSelection = wordListController->GetSelected();
	if (oldSelection >= 0)
		previousItemName = pController->GetString(oldSelection);
	pController->Clear(kFalse, kFalse);
	
	InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IDocumentList>	documentList(theApp->QueryDocumentList());
	
	/* populate menu */
	int32 numMenuEntries = 0;
	int32 firstValidEntry = 0;

	InterfacePtr<IUserDictService> userDictService(this->QueryUserDictService());
	if (userDictService)
	{
		K2Vector<IUserDict*> userDictList;
		int32 numUserDicts = userDictService->QueryAllUserDictsInSearchPath(userDictList, kTrue);

		for (int32 i = 0; i < numUserDicts; ++i)
		{
			PMString userDictName(userDictList[i]->GetDisplayName());
			if (userDictName.empty())
				continue;

			pController->AddString(userDictName, IStringListControlData::kEnd, kFalse, kFalse);

			if (userDictService->IsReadOnly(userDictList[i]))
			{
				pController->Enable(numMenuEntries, kFalse /*doEnable*/, kFalse /*invalidate*/, kFalse /*notifyOfChange*/);
				//should also add a lock icon

				if (numMenuEntries == firstValidEntry)
					firstValidEntry++;
			}
			numMenuEntries++;
		}
	}

	if (numMenuEntries == 0)
		pController->AddString(PMString("DE_UserDict"), IStringListControlData::kEnd, kFalse, kFalse);
	else if (firstValidEntry == numMenuEntries)
		firstValidEntry = -1;

	// See if same string exists and is enabled--if so select it
	int32 testIndex = pController->GetIndex(previousItemName);
	if (testIndex >= 0 && pController->IsEnabled(testIndex))
		firstValidEntry = testIndex;

	wordListController->Select( firstValidEntry, kTrue, kFalse );	/* set selection */


	return kTrue;
}

IPMUnknown* SpellTargetListObserver::GetWidgetData()
{
	IPMUnknown *pThis = (IPMUnknown *)this;
	InterfacePtr<IDropDownListController> controller( pThis, IID_IDROPDOWNLISTCONTROLLER );
	InterfacePtr<IStringListControlData> pData( pThis, IID_ISTRINGLISTCONTROLDATA );

	const int32 nSelected = controller->GetSelected();	/* 0 based */
	if( nSelected < 0 )
		return nil;

	PMString itemName = pData->GetString(nSelected);

	InterfacePtr<IUserDictService> userDictService(this->QueryUserDictService());
	if (userDictService)
	{	
		K2Vector<IUserDict*> userDictList;
		int32 numUserDicts = userDictService->QueryAllUserDictsInSearchPath(userDictList, kTrue);

		int32 numRemoved = 0;

		for (int32 i = numUserDicts-1; i >= 0; i--)
		{
			PMString userDictPathName = userDictList[i]->GetFilePathName();
			
			if (userDictList[i]->GetDataFile() == nil || userDictPathName.CharCount() <= 0)
			{
				userDictList.erase(userDictList.begin() + i);
				numRemoved++;
			}
		}

		if (nSelected < numUserDicts - numRemoved)
			return userDictList[nSelected];
	}

	return nil;
}

//---------------------------------------------------------------
// SpellTargetListObserver::NotifyTargetHasChanged
//---------------------------------------------------------------

void	SpellTargetListObserver::NotifyTargetHasChanged(const void *target)
{
	InterfacePtr<ISubject> pPanel( this->QueryPanelSubject() );
	if( pPanel )
	{
		//pPanel->Change( kDictEditorMsgTargetHasChanged, IID_IDICTEDITORMSG, (void*)target );
	}
}



