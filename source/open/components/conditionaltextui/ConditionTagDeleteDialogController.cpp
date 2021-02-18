//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/ConditionTagDeleteDialogController.cpp $
//  
//  Owner: Michele Stutzman
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

#include "IActiveContext.h"
#include "IColorListControlData.h"
#include "IConditionTag.h"
#include "IConditionTagList.h"
#include "IDialogMgr.h"
#include "IDocument.h"
#include "IDropDownListController.h"
#include "IPanelControlData.h"
#include "IStringListControlData.h"
#include "ITextControlData.h"
#include "IUIDListData.h"
#include "IWidgetParent.h"
#include "IWindow.h"
#include "IWorkspace.h"

// ----- Includes -----

#include "CDialogController.h"

// ----- Utility files -----

#include "IConditionalTextFacade.h"
#include "IConditionalTextUIFacade.h"

// ----- ID.h files -----

#include "ColorSystemID.h"
#include "ConditionalTextUIID.h"


class ConditionTagDeleteDialogController : public CDialogController
{
public:
	ConditionTagDeleteDialogController(IPMUnknown *boss);
	virtual	~ConditionTagDeleteDialogController();

	virtual void		InitializeDialogFields(IActiveContext* dlgContext);
	virtual WidgetID	ValidateDialogFields(IActiveContext* myContext);
	virtual void		ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId);
};

// =============================================================================
// *** ConditionTagDeleteDialogController impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(ConditionTagDeleteDialogController, kConditionTagDeleteDialogControllerImpl)

ConditionTagDeleteDialogController::ConditionTagDeleteDialogController(IPMUnknown *boss) :
	CDialogController(boss)
{
} // end constructor

ConditionTagDeleteDialogController::~ConditionTagDeleteDialogController()
{
} // end destructor

// -----------------------------------------------------------------------------

void ConditionTagDeleteDialogController::InitializeDialogFields(IActiveContext* dlgContext)
{
	// Get the data from dialog.  Set by IConditionalTextUIFacade::DoConditionDeleteDialog(...).
	InterfacePtr<IUIDListData> tagData(this, UseDefaultIID());
	IDataBase* db = tagData->GetDataBase();
	UIDList tagsToDelete(*(tagData->GetRef()));

	InterfacePtr<IStringListControlData> replaceWithListData(this->QueryListControlDataInterface(kConditionTagDeletePopupWidgetID));
	replaceWithListData->Clear(kTrue, kFalse);
	
	PMString addString("#ConditionTag_DeleteNoReplaceChoice");
	addString.Translate();
	replaceWithListData->AddString(addString);

	InterfacePtr<IConditionTagList> tagList(Utils<Facade::IConditionalTextFacade>()->QueryConditionList(db));
	if (tagList)
	{
		for (int32 i = 0; i < tagList->GetCount(); i++)
		{
			WideString tagName;
			if (Utils<Facade::IConditionalTextFacade>()->GetConditionName(UIDRef(db, tagList->GetNthCondition(i)), tagName) == kSuccess)
			{
				addString = PMString(tagName);
				addString.SetTranslatable(kFalse);
				replaceWithListData->AddString(addString);
				if (std::find(tagsToDelete.begin(), tagsToDelete.end(), tagList->GetNthCondition(i)) != tagsToDelete.end())
					replaceWithListData->Disable(replaceWithListData->Length()-1, kFalse, kFalse);
			}
		}
	}

	InterfacePtr<IDropDownListController> replaceWithDropDownList(replaceWithListData, UseDefaultIID());
	replaceWithDropDownList->Select(0);

	// Set dialog window title.
	InterfacePtr<IWidgetParent> parentHolder(this, UseDefaultIID());
	ASSERT_MSG(parentHolder, "ConditionTagDeleteDialogController::InitializeDialogFields() widget parent is invalid!");
	InterfacePtr<IWindow> window(static_cast<IWindow*>(parentHolder->QueryParentFor(IID_IWINDOW)));
	if (window)
	{
		if (tagsToDelete.Length() > 1)
			window->SetTitle(PMString("#ConditionTag_DeleteConditionsDialog", PMString::kTranslateDuringCall));
		else
			window->SetTitle(PMString("#ConditionTag_DeleteConditionDialog", PMString::kTranslateDuringCall));
	}

	// Set dialog static text.
	if (tagsToDelete.Length() > 1)
		SetTextControlData(kConditionTagDeleteStaticWidgetID, PMString("#ConditionTag_DeleteConditionsAndReplace:", PMString::kTranslateDuringCall));
	else
		SetTextControlData(kConditionTagDeleteStaticWidgetID, PMString("#ConditionTag_DeleteConditionAndReplace:", PMString::kTranslateDuringCall));

} // end InitializeDialogFields()

// -----------------------------------------------------------------------------

void ConditionTagDeleteDialogController::ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId) 
{
	// Get the data from dialog.  Set by IConditionalTextUIFacade::DoConditionDeleteDialog(...).
	InterfacePtr<IUIDListData> tagData(this, UseDefaultIID());
	IDataBase* db = tagData->GetDataBase();

	// Now the workspace from the provided database.
	InterfacePtr<IWorkspace> workspace(nil);
	InterfacePtr<IDocument> doc(db, db->GetRootUID(), IID_IDOCUMENT);
	if (doc)
		workspace.reset(static_cast<IWorkspace*>(doc->GetDocWorkSpace().Instantiate(IWorkspace::kDefaultIID)));
	else
		workspace.reset(GetExecutionContextSession()->QueryWorkspace());

	InterfacePtr<IConditionTagList> tagList(Utils<Facade::IConditionalTextFacade>()->QueryConditionList(db));

	InterfacePtr<IStringListControlData> replaceWithListData(this->QueryListControlDataInterface(kConditionTagDeletePopupWidgetID));
	InterfacePtr<IDropDownListController> replaceWithDropDownList(replaceWithListData, UseDefaultIID());
	int32 selected = replaceWithDropDownList->GetSelected();
	ASSERT(selected <= tagList->GetCount());

	Utils<Facade::IConditionalTextFacade>()->DeleteConditions(*(tagData->GetRef()), tagList->GetNthCondition(selected-1));

} // end ApplyDialogFields()

// -----------------------------------------------------------------------------

WidgetID ConditionTagDeleteDialogController::ValidateDialogFields(IActiveContext* myContext)
{
	return kNoInvalidWidgets;
} // end ValidateDialogFields()
