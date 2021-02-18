//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/ConditionTagOptionsDialogController.cpp $
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
#include "IDialogMgr.h"
#include "IDocument.h"
#include "IDropDownListController.h"
#include "IPanelControlData.h"
#include "IStringListControlData.h"
#include "ITextControlData.h"
#include "IUIDData.h"
#include "IWorkspace.h"

// ----- Includes -----

#include "CAlert.h"
#include "CDialogController.h"

// ----- Utility files -----

#include "IConditionalTextFacade.h"
#include "IConditionalTextUIFacade.h"

// ----- ID.h files -----

#include "ColorSystemID.h"
#include "ConditionalTextUIID.h"


class ConditionTagOptionsDialogController : public CDialogController
{
public:
	ConditionTagOptionsDialogController(IPMUnknown *boss);
	virtual	~ConditionTagOptionsDialogController();

	virtual void		InitializeDialogFields(IActiveContext* dlgContext);
	virtual WidgetID	ValidateDialogFields(IActiveContext* myContext);
	virtual void		ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId);
};

// =============================================================================
// *** ConditionTagOptionsDialogController impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(ConditionTagOptionsDialogController, kConditionTagOptionsDialogControllerImpl)

ConditionTagOptionsDialogController::ConditionTagOptionsDialogController(IPMUnknown *boss) :
	CDialogController(boss)
{
} // end constructor

ConditionTagOptionsDialogController::~ConditionTagOptionsDialogController()
{
} // end destructor

// -----------------------------------------------------------------------------

void ConditionTagOptionsDialogController::InitializeDialogFields(IActiveContext* dlgContext)
{
	InterfacePtr<IPanelControlData> panelData(this, IID_IPANELCONTROLDATA);

	// Get the data from dialog.  Set by IConditionalTextUIFacade::DoConditionTagOptionsDialog(...).
	InterfacePtr<IUIDData> tagData(this, UseDefaultIID());
	IDataBase* db = tagData->GetItemDataBase();

	// Now the workspace from the provided database.
	InterfacePtr<IWorkspace> workspace(nil);
	InterfacePtr<IDocument> doc(db, db->GetRootUID(), IID_IDOCUMENT);
	if (doc)
		workspace.reset(static_cast<IWorkspace*>(doc->GetDocWorkSpace().Instantiate(IWorkspace::kDefaultIID)));
	else
		workspace.reset(GetExecutionContextSession()->QueryWorkspace());

	WideString tagName;
	UID tagColorUID;
	IConditionTag::IndicatorMethod tagMethod = IConditionTag::kUnderline;
	IConditionTag::UnderlineIndicatorAppearance tagAppearance = IConditionTag::kSingleWavy;
	InterfacePtr<IConditionTag> conditionTag(tagData->GetRef(), UseDefaultIID());
	if (conditionTag)
	{
		// Editing condition tag.
		tagName = conditionTag->GetName();
		tagColorUID = conditionTag->GetColor();
		tagMethod = conditionTag->GetMethod();
		tagAppearance = conditionTag->GetAppearance();
	}
	else
	{
		// Defaults for new condition tag.
		Utils<Facade::IConditionalTextFacade>()->GetFirstAvailableDefaultConditionName(workspace, tagName);
		Utils<Facade::IConditionalTextFacade>()->GetNextDefaultConditionColor(workspace, tagColorUID);
	}

	// Initialize the fields of the dialog.

	// Name field
	IControlView* nameControlView = panelData ? panelData->FindWidget(kConditionTagNameEditWidgetID) : nil;
	InterfacePtr<ITextControlData> nameControlData(nameControlView, UseDefaultIID());
	if (nameControlData)
	{
		PMString stringTagName(tagName);
		stringTagName.SetTranslatable(kFalse);
		nameControlData->SetString(stringTagName);
	}

	// Color field
	IControlView* colorControlView = panelData ? panelData->FindWidget(kConditionTagIndicatorColorEditWidgetID) : nil;
	InterfacePtr<IColorListControlData> colorListControlData(colorControlView, UseDefaultIID());
	if (colorListControlData)
		colorListControlData->Setup(::GetUIDRef(workspace), IID_IUICOLORLIST, IColorListControlData::kIncludeCustom, tagColorUID);

	// Method field
	InterfacePtr<IStringListControlData> methodDropDownData(this->QueryListControlDataInterface(kConditionTagIndicatorMethodEditWidgetID));
	InterfacePtr<IDropDownListController> methodDropDownList(methodDropDownData, UseDefaultIID());
	methodDropDownList->Select(tagMethod);

	// Appearance field
	InterfacePtr<IStringListControlData> appearanceDropDownData(this->QueryListControlDataInterface(kConditionTagIndicatorAppearanceEditWidgetID));
	InterfacePtr<IDropDownListController> appearanceDropDownList(appearanceDropDownData, UseDefaultIID());
	appearanceDropDownList->Select(tagAppearance);
} // end InitializeDialogFields()

// -----------------------------------------------------------------------------

void ConditionTagOptionsDialogController::ApplyDialogFields(IActiveContext* myContext, const WidgetID& widgetId) 
{
	InterfacePtr<IPanelControlData> panelData(this, IID_IPANELCONTROLDATA);

	// Get the data and workspace.

	InterfacePtr<IUIDData> tagData(this, UseDefaultIID());
	IDataBase* db = tagData->GetItemDataBase();

	InterfacePtr<IWorkspace> workspace(nil);
	InterfacePtr<IDocument> doc(db, db->GetRootUID(), IID_IDOCUMENT);
	if (doc)
		workspace.reset(static_cast<IWorkspace*>(doc->GetDocWorkSpace().Instantiate(IWorkspace::kDefaultIID)));
	else
		workspace.reset(GetExecutionContextSession()->QueryWorkspace());

	// Get the fields from the dailog.

	// Name field
	WideString tagName;
	IControlView* nameControlView = panelData ? panelData->FindWidget(kConditionTagNameEditWidgetID) : nil;
	InterfacePtr<ITextControlData> nameControlData(nameControlView, UseDefaultIID());
	if (nameControlData)
		tagName = WideString(nameControlData->GetString());

	// Color field
	UID colorUID;
	IControlView* colorControlView = panelData ? panelData->FindWidget(kConditionTagIndicatorColorEditWidgetID) : nil;
	InterfacePtr<IColorListControlData> colorListControlData(colorControlView, UseDefaultIID());
	if (colorListControlData)
		colorUID = colorListControlData->GetSelection();

	// Method field
	IConditionTag::IndicatorMethod tagMethod;
	InterfacePtr<IStringListControlData> methodDropDownData(this->QueryListControlDataInterface(kConditionTagIndicatorMethodEditWidgetID));
	InterfacePtr<IDropDownListController> methodDropDownList(methodDropDownData, UseDefaultIID());
	tagMethod = (IConditionTag::IndicatorMethod)methodDropDownList->GetSelected();

	// Appearance field
	IConditionTag::UnderlineIndicatorAppearance tagAppearance;
	InterfacePtr<IStringListControlData> appearanceDropDownData(this->QueryListControlDataInterface(kConditionTagIndicatorAppearanceEditWidgetID));
	InterfacePtr<IDropDownListController> appearanceDropDownList(appearanceDropDownData, UseDefaultIID());
	tagAppearance = (IConditionTag::UnderlineIndicatorAppearance)appearanceDropDownList->GetSelected();

	if (tagData->GetItemUID() != kInvalidUID)
	{
		// Edit the condition tag fields.
		InterfacePtr<IConditionTag> tag(tagData->GetRef(), UseDefaultIID());
		if (tag->GetName() != tagName || tag->GetColor() != colorUID || tag->GetMethod() != tagMethod || tag->GetAppearance() != tagAppearance)
			Utils<Facade::IConditionalTextFacade>()->SetConditionOptions(::GetUIDRef(tag), tagName, colorUID, tagMethod, tagAppearance);
	}
	else
	{
		// Make new condition tag.
		Utils<Facade::IConditionalTextFacade>()->CreateCondition(workspace, nil, tagName, colorUID, tagMethod, tagAppearance, kTrue);
	}

} // end ApplyDialogFields()

// -----------------------------------------------------------------------------

WidgetID ConditionTagOptionsDialogController::ValidateDialogFields(IActiveContext* myContext)
{
	InterfacePtr<IPanelControlData> controlData(this, UseDefaultIID());
	IControlView *nameEditField = controlData->FindWidget(kConditionTagNameEditWidgetID);
	InterfacePtr<ITextControlData> textData(nameEditField, UseDefaultIID());

	// See if name is empty.
	if (textData->GetString().IsEmpty())
	{
		PMString message("#ConditionTag_EmptyNameMsg", PMString::kTranslateDuringCall);
		CAlert::WarningAlert(message);
		return kConditionTagNameEditWidgetID;
	}
	
	// See if this name already exists or is reserved.
	InterfacePtr<IUIDData> tagData(this, UseDefaultIID());
	WideString nameString(textData->GetString());
	UID conditionUID;
	PMString reservedName("#ConditionTag_Unconditional", PMString::kTranslateDuringCall);
	if ((Utils<Facade::IConditionalTextFacade>()->FindCondition(myContext->GetContextWorkspace(), nameString, conditionUID) == kSuccess && conditionUID != tagData->Get())
		|| textData->GetString() == reservedName)
	{
		PMString message("#ConditionTag_NameInUseMsg", PMString::kTranslateDuringCall);
		CAlert::WarningAlert(message);
		return kConditionTagNameEditWidgetID;
	}

	return kNoInvalidWidgets;
} // end ValidateDialogFields()
