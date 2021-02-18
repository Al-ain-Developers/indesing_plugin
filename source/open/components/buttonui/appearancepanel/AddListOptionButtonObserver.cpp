//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/appearancepanel/AddListOptionButtonObserver.cpp $
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

#include "IBoolData.h"
#include "IControlView.h"
#include "IFormFieldSuite.h"
#include "ISelectionDataSuite.h"
#include "ISubject.h"
#include "ITextControlData.h"
#include "IWidgetUtils.h"

// ----- Implementation Includes -----

#include "CWidgetObserver.h"
#include "IntNodeID.h"

// ----- Utility files -----

#include "FormFieldUIUtils.h"
#include "SelectionUtils.h"

// ----- ID.h files -----

#include "FormFieldUIID.h"

//========================================================================================
// CLASS AddListOptionButtonObserver
//========================================================================================

class AddListOptionButtonObserver : public CWidgetObserver
{
public:
	typedef CWidgetObserver	Inherited;

	AddListOptionButtonObserver(IPMUnknown *boss);
	virtual ~AddListOptionButtonObserver();

	virtual void AutoAttach();
	virtual void AutoDetach();
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
};

//========================================================================================
// METHODS AddListOptionButtonObserver
//========================================================================================

CREATE_PMINTERFACE(AddListOptionButtonObserver, kAddListOptionButtonObserverImpl)

//----------------------------------------------------------------------------------------
// AddListOptionButtonObserver constructor 
//----------------------------------------------------------------------------------------

AddListOptionButtonObserver::AddListOptionButtonObserver(IPMUnknown *boss) :
Inherited(boss)
{
}

//----------------------------------------------------------------------------------------
// AddListOptionButtonObserver destructor 
//----------------------------------------------------------------------------------------

AddListOptionButtonObserver::~AddListOptionButtonObserver()
{
}

//----------------------------------------------------------------------------------------
// AddListOptionButtonObserver::AutoAttach: 
//----------------------------------------------------------------------------------------

void AddListOptionButtonObserver::AutoAttach()
{
	AttachToWidget(kAddListOptionButtonWidgetID, IID_ITRISTATECONTROLDATA);
	AttachToWidget(kListItemTextNodeWID, IID_ITEXTCONTROLDATA);
}

//----------------------------------------------------------------------------------------
// AddListOptionButtonObserver::AutoDetach: 
//----------------------------------------------------------------------------------------

void AddListOptionButtonObserver::AutoDetach()
{
	DetachFromWidget(kAddListOptionButtonWidgetID, IID_ITRISTATECONTROLDATA);
	DetachFromWidget(kListItemTextNodeWID, IID_ITEXTCONTROLDATA);
}

//----------------------------------------------------------------------------------------
// AddListOptionButtonObserver::Update: 
//----------------------------------------------------------------------------------------

void AddListOptionButtonObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	InterfacePtr<IControlView> view(theSubject, UseDefaultIID());
	bool16 isEnterKeyDown = kFalse;

	if(view && view->GetWidgetID() == kListItemTextNodeWID )
	{
		InterfacePtr<IBoolData> iEnterKeyDown( view, IID_IBOOLDATA );
		isEnterKeyDown = iEnterKeyDown->Get();
		iEnterKeyDown->Set(kFalse);

		if(theChange == kEditBoxKeyStrokeMessage)
		{
			InterfacePtr<ITextControlData> iEdit(view, UseDefaultIID());
			const PMString &textStr = iEdit->GetString();
			InterfacePtr<IControlView> addListItemView(this, UseDefaultIID());

			if(textStr.empty())
				addListItemView->Disable();
			else
				addListItemView->Enable();
		}
	}

	if (view && ((view->GetWidgetID() == kAddListOptionButtonWidgetID && theChange == kTrueStateMessage) ||
				 (view->GetWidgetID() == kListItemTextNodeWID && theChange == kTextChangeStateMessage && isEnterKeyDown)))
	{
		InterfacePtr<IFormFieldSuite> iFormFieldSuite(FormFieldUIUtils::QueryFormSuite());
		InterfacePtr<ISelectionDataSuite> iSelectionDataSuite (static_cast<ISelectionDataSuite*>(Utils<ISelectionUtils>()->QuerySuite(IID_ISELECTIONDATASUITE)));
		bool16 isSingleSelection = iSelectionDataSuite && iSelectionDataSuite->GetSelectionCount() == 1;

		if (iFormFieldSuite && isSingleSelection && 
			(iFormFieldSuite->IsFieldSelectionOfType(kComboBoxItemBoss) || iFormFieldSuite->IsFieldSelectionOfType(kListBoxFieldItemBoss)))
		{
			// Get the string to add - do not add to the list if empty or if it already exists in the list.
			InterfacePtr<ITextControlData> iEdit((ITextControlData*) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kListItemTextNodeWID, IID_ITEXTCONTROLDATA));
			ASSERT(iEdit != nil);

			const PMString &choiceStr = iEdit->GetString();
			if (!choiceStr.empty())
			{
				Form::ChoiceList choiceList;
				iFormFieldSuite->GetChoiceList(choiceList);

				int32 choiceListSize = choiceList.size();
				for (int32 i = 0; i < choiceListSize; i++)
				{
					if (choiceStr == choiceList[i])
						return;
				}

				iFormFieldSuite->AddChoice(choiceStr);
				iEdit->SetString(PMString());
			}
		}
	}
}
