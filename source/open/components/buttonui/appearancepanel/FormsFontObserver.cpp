//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/appearancepanel/FormsFontObserver.cpp $
//  
//  Owner: Reena Agrawal
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

// ----- Interfaces -----
#include "CObserver.h"
// ----- Includes -----
#include "FormFieldUIID.h"
#include "ISubject.h"
#include "IFontMgr.h"
#include "FontMgrID.h"
#include "IControlView.h"
#include "IDropDownListController.h"
#include "IStringListControlData.h"
#include "IFontUtilData.h"
#include "IWidgetUtils.h"
#include "ITextControlData.h"

class FormsFontObserver : public CObserver
{
	typedef CObserver Inherited;
public:
	FormsFontObserver(IPMUnknown* boss);
	virtual ~FormsFontObserver();
	virtual void AutoAttach();
	virtual void AutoDetach();
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);

private:
	void InitializeFontCollection();
	bool16 IsStringOrderOK(std::vector<PMString>& list);

};

CREATE_PMINTERFACE(FormsFontObserver, kFormsFontObserverImpl)

FormsFontObserver::FormsFontObserver(IPMUnknown* boss) :Inherited(boss)
{
}

FormsFontObserver::~FormsFontObserver()
{}

void FormsFontObserver::AutoAttach()
{
	Inherited::AutoAttach();
	InterfacePtr<IStringListControlData> stringListData(this, UseDefaultIID());
	if (stringListData && stringListData->Length() == 0)
		InitializeFontCollection();
}
void FormsFontObserver::AutoDetach()
{
	Inherited::AutoDetach();
}

void FormsFontObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy)
{
}

void FormsFontObserver::InitializeFontCollection()
{

	InterfacePtr<IControlView> myView(this, UseDefaultIID());
	WidgetID wID = myView->GetWidgetID();
	InterfacePtr<IFontUtilData> fontUtilData(GetExecutionContextSession(), UseDefaultIID());
	ASSERT(fontUtilData);
	if (wID == kFormFontFamilyWidgetID)
	{
		std::vector<PMString> fontFamilyList;
		fontUtilData->GetFontFamiliesList(fontFamilyList);
		ASSERT(IsStringOrderOK(fontFamilyList));
		InterfacePtr<IStringListControlData> stringListData(this, UseDefaultIID());
		for (size_t i = 0; i < fontFamilyList.size(); i++)
			stringListData->AddString(fontFamilyList[i], IStringListControlData::kEnd, kFalse);
		InterfacePtr<IDropDownListController> ddListController(this, UseDefaultIID());
		ddListController->Select(0, kFalse, kFalse);
	}
	else
	{
		InterfacePtr<IControlView> familyView((IControlView*)Utils<IWidgetUtils>()->QueryRelatedWidget(this, kFormFontFamilyWidgetID, IID_ICONTROLVIEW));
		InterfacePtr<IStringListControlData> familyListData(familyView, UseDefaultIID());
		InterfacePtr<IDropDownListController> familyDDLView(familyView, UseDefaultIID());
        if (familyDDLView->GetSelected() != -1)
        {
            PMString fontFamilyName = familyListData->GetString(familyDDLView->GetSelected());
            std::vector<PMString> styles;
            fontUtilData->GetStylesInFontFamily(fontFamilyName, styles);
            ASSERT(IsStringOrderOK(styles));
            InterfacePtr<IStringListControlData> stringListData(this, UseDefaultIID());
            for (size_t i = 0; i < styles.size(); i++)
                stringListData->AddString(styles[i], IStringListControlData::kEnd, kFalse);
            InterfacePtr<IDropDownListController> ddListController(this, UseDefaultIID());
            ddListController->Select(0, kFalse, kFalse);
        }
	}
}

bool16 FormsFontObserver::IsStringOrderOK(std::vector<PMString>& list)
{
	if (list.size() > 1)
	{
		PMString previousString = list[0];
		PMString lastString = list[1];
		for (int32 i = 1; i < list.size(); i++)
		{
			lastString = list[i];
			if (previousString.Compare(kFalse, lastString) <= 0)
				previousString = lastString;
			else
				return kFalse;
		}
	}
	return kTrue;
}

