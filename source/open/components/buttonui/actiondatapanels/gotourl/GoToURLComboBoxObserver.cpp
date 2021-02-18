//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/gotourl/GoToURLComboBoxObserver.cpp $
//  
//  Owner: Dave Stephens
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
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

// ----- Interface Includes -----

#include "IActiveContext.h"
#include "IBoolData.h"
#include "IComboBoxCalculatedValue.h"
#include "IDocument.h"
#include "IDropDownListController.h"
#include "IHyperlinkDestination.h"
#include "IHyperlinkTable.h"
#include "IOtherEntryData.h"
#include "IStringListControlData.h"
#include "ISubject.h"
#include "ITextControlData.h"
#include "ITextValue.h"
#include "IUIDData.h"

// ----- Implementation Includes -----

#include "BehaviorUIDefs.h"
#include "CObserver.h"

// ----- ID Includes -----

#include "BehaviorUIID.h"
#include "HyperlinkID.h"

//========================================================================================
// CLASS GoToURLComboBoxObserver
//========================================================================================

class GoToURLComboBoxObserver : public CObserver
{
public:
	GoToURLComboBoxObserver(IPMUnknown *boss, PMIID interfaceID = IID_IOBSERVER);
	virtual ~GoToURLComboBoxObserver();
	
	virtual void 	AutoAttach();
	virtual void 	AutoDetach();
	virtual void 	Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
	virtual void	DoPopupChange();
	
	protected:
		virtual void FillHyperlinkDestinationURL(PMString & name, PMString* URL);
};

//========================================================================================
// METHODS GoToURLComboBoxObserver
//========================================================================================

CREATE_PMINTERFACE(GoToURLComboBoxObserver, kGoToURLComboBoxObserverImpl)

//----------------------------------------------------------------------------------------
// GoToURLComboBoxObserver constructor 
//----------------------------------------------------------------------------------------

GoToURLComboBoxObserver::GoToURLComboBoxObserver(IPMUnknown *boss, PMIID interfaceID) :
	CObserver(boss, interfaceID)
{
}


//----------------------------------------------------------------------------------------
// GoToURLComboBoxObserver::~GoToURLComboBoxObserver
//----------------------------------------------------------------------------------------

GoToURLComboBoxObserver::~GoToURLComboBoxObserver()
{
}

//----------------------------------------------------------------------------------------
// GoToURLComboBoxObserver::AutoAttach
//----------------------------------------------------------------------------------------

void GoToURLComboBoxObserver::AutoAttach()
{
	InterfacePtr<ISubject> dropDownSubject(this, IID_ISUBJECT);
	dropDownSubject->AttachObserver(this, IID_ISTRINGLISTCONTROLDATA,IID_ICOMBOBOXOBSERVER);
}

//----------------------------------------------------------------------------------------
// GoToURLComboBoxObserver::AutoDetach
//----------------------------------------------------------------------------------------

void GoToURLComboBoxObserver::AutoDetach() 
{
	InterfacePtr<ISubject> dropDownSubject(this, IID_ISUBJECT);
	dropDownSubject->DetachObserver(this, IID_ISTRINGLISTCONTROLDATA,IID_ICOMBOBOXOBSERVER);
}

//----------------------------------------------------------------------------------------
// GoToURLComboBoxObserver::Update
//----------------------------------------------------------------------------------------

void GoToURLComboBoxObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	if ( theChange == kPopupChangeStateMessage )
	{
		DoPopupChange();
	}
}

//----------------------------------------------------------------------------------------
// GoToURLComboBoxObserver::DoPopupChange
//----------------------------------------------------------------------------------------

void GoToURLComboBoxObserver::DoPopupChange()
{
	InterfacePtr<IDropDownListController> controller(this,IID_IDROPDOWNLISTCONTROLLER);
	
	InterfacePtr<ITextValue> textValue(this,IID_ITEXTVALUE);
	
	bool16 doNotify = kTrue;
	InterfacePtr<IBoolData> typeaheadData(this,IID_ITYPEAHEADNOTACTIVE);
	if(typeaheadData && typeaheadData->GetBool() == kFalse)
		doNotify = kFalse;
	
	if(controller->GetSelected() != IStringListControlData::kInvalidStringIndex)
	{
		InterfacePtr<IStringListControlData> stringData(this,IID_ISTRINGLISTCONTROLDATA);
		PMString dropDownString(stringData->GetString(controller->GetSelected()));
		
		//TODO: if items in dropdowns can be disabled, can remove this code...
		InterfacePtr<IOtherEntryData> otherData(this,IID_IOTHERENTRYDATA);
		if(otherData->GetOtherIndex() == controller->GetSelected() )
		{
			PMString otherString("Other");
			if(dropDownString.HasTranslated())
				otherString.Translate();
			if(otherString == dropDownString)
				return;
			else if(dropDownString == "hyphenInOtherSpot")
				dropDownString = "-";
		}
		
		
		InterfacePtr<IComboBoxCalculatedValue> cbCalcVal(this,UseDefaultIID());
		if(cbCalcVal && doNotify)
		{
			PMString translatedString(dropDownString);
			translatedString.Translate();
			cbCalcVal->UserChoseItem(translatedString);
		}
		
		InterfacePtr<ITextControlData> textData(this,IID_ITEXTCONTROLDATA);

		// --- Fill the edit box with the URL not the URL name!
		PMString URL;
		FillHyperlinkDestinationURL(dropDownString, &URL);
		textData->SetString(URL,kTrue,kFalse,kFalse);
		
		textValue->ReformatText(kTrue,doNotify);
	}
	else
		textValue->SetControlState(ITextValue::kUnknown,kTrue,doNotify);
}

//----------------------------------------------------------------------------------------
// GoToURLComboBoxObserver::FillHyperlinkDestinationURL
//----------------------------------------------------------------------------------------

void GoToURLComboBoxObserver::FillHyperlinkDestinationURL(PMString & name, PMString* URL)
{
	IDocument *doc = GetExecutionContextSession()->GetActiveContext()->GetContextDocument();
	IDataBase *db = ::GetDataBase(doc);	
	bool16 foundInList(kFalse);
	InterfacePtr<IHyperlinkTable> docHyperlinkTable(db, db->GetRootUID(), IID_IHYPERLINKTABLE);
	for (UniqueKeyToUIDMap::const_iterator iter = docHyperlinkTable->GetDestinationKeyToUIDMapBeginIter(); 
		 iter != docHyperlinkTable->GetDestinationKeyToUIDMapEndIter(); ++iter)
	{
		InterfacePtr<IHyperlinkDestination> ithDestination(db, iter->second, IID_IHYPERLINKDESTINATION);
		if(ithDestination)
		{
			PMString destName;
			ithDestination->GetName(&destName);
			if(destName.IsEqual(name))
			{
				InterfacePtr<IUIDData> uidData(this, IID_IUIDDATA);	
				uidData->Set(db, iter->second);
				ithDestination->GetInfo(URL);
				return;
			}
		}
	}
	ASSERT("Hyperlink name not found in hyperlink destination list of this document");
	*URL = PMString("HyperlinksDefaultURL");
	URL->Translate();
}
