//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/dialogs/CDialogController.cpp $
//  
//  Owner: Tom Taylor
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

#include "VCWidgetHeaders.h"

#include "CDialogController.h"
#include "DVModelessDialogWindow.h"
#include "DVUtilities.h"

// ----- Interface Includes -----

#include "IBoolData.h"
#include "IPanelControlData.h"
#include "IControlView.h"
#include "IDialog.h"
#include "ITextControlData.h"
#include "IBooleanControlData.h"
#include "IWidgetParent.h"
#include "IKeyFocusHandler.h"
#include "IStringListControlData.h"
#include "IEventHandler.h"
#include "ITextValue.h"
#include "IEditBoxAttributes.h"
#include "IWindow.h"
#include "IActiveContext.h"
#include "IObserver.h"
#include "IWidgetUtils.h"
#include "IClusterController.h"


CDialogController::CDialogController(IPMUnknown *boss) :
	fInitialized(kFalse),
	fOwner(nil),
	fPreviewModeOn(kFalse),
	fDialogContext(nil),
	CPMUnknown<IDialogController>(boss)
{
}

CDialogController::~CDialogController()
{
}

void CDialogController::InitializeDialogFields(IActiveContext* context)
{
}

void CDialogController::InitializeDialog(IActiveContext* context)
{
	// Note: the state of the preview button is intentially not changed or reset here.
	// Playing around with Photoshop, I found that the state of the preview checkbox
	// is persistent across closing and reopening the same dialog.
	IActiveContext* oldDialogContext = fDialogContext;
	fDialogContext = context;  //add ref in boss leak savvy way
	fDialogContext = QueryDialogContext(); //hold a ref 'til DialogClosing
	if( oldDialogContext) oldDialogContext->Release();
	this->InitializeDialogFields(fDialogContext);
	SetInitialized(kTrue);

	// Check if the dialog validation status is already set to false, if not reset the flag, checking only for modal dialogs
	InterfacePtr<IWidgetParent> parentHolder(this, IID_IWIDGETPARENT);
	InterfacePtr<IDialog> dialog((IDialog*) parentHolder->QueryParentFor(IID_IDIALOG));
	{
		if(dialog)
		{
			IDialog::DialogType dialogType = dialog->GetDialogType();
			if(dialogType == IDialog::kModal || dialogType == IDialog::kMovableModal)
			{
				InterfacePtr<IWidgetParent> parentPtr(this, UseDefaultIID());
				InterfacePtr<IBoolData> dataInvalid((IBoolData *)parentPtr->QueryParentFor(IID_IDIALOGVALIDATIONFAILED));

				// Reset the dialog invalidation status, this would have been set during the previous dialog launch,
				if (dataInvalid )
				{
					// reset the flag here and this flag will be set again (iff needed) on ValidateDialog() call
					dataInvalid->Set(kFalse);

					ASSERT_MSG(dataInvalid->Get() == kFalse, "Dialog Validation Status is failed in CDialogController::InitializeDialog(), the status should have been reset.");
				}
			}
			else if(dialogType == IDialog::kModeless )
			{
				// If a modeLess dialog said to forcefully accept enter key,
				// its dialog view container should not accept enter key.
				InterfacePtr<const IBoolData>    isForceAcceptEnterkey(this, IID_IFORCEACCEPTENTERKEY); 
				if(isForceAcceptEnterkey && isForceAcceptEnterkey->GetBool())
				{
					InterfacePtr<IDV_UI_NodeRef> windowRef(dialog, IID_IDV_OS_WINDOWREF);
					IDBase_UI_ModelessDialog* modelessDialog = dynamic_cast<IDBase_UI_ModelessDialog*>(windowRef->Get_UI_Node());
					if(modelessDialog)
					{
						modelessDialog->SetTextEditReturnClosesDialog(false);
					}
				}
			}
		}
	}
}

IActiveContext*CDialogController::QueryDialogContext()
{
#ifdef DEBUG
	ASSERT( fDialogContext);
	return static_cast<IActiveContext*>(fDialogContext->QueryInterface(IActiveContext::kDefaultIID));  //add ref in boss leak savvy way
#else
	fDialogContext->AddRef();
	return fDialogContext;
#endif
}


void CDialogController::ApplyDialogFields( IActiveContext* myContext, const WidgetID& widgetId)
{
	ASSERT_MSG(HasBeenInitialized(), "CDialogController::ApplyDialogFields - Hey, you're trying to apply a dialog that has never been initialized!");
}

void CDialogController::ApplyDialog(const WidgetID& widgetId)
{
	ASSERT_MSG(HasBeenInitialized(), "CDialogController::ApplyDialog - Hey, you're trying to apply a dialog that has never been initialized!");
	this->ApplyDialogFields( fDialogContext, widgetId);
}

void CDialogController::ResetDialogFields(IActiveContext* c)
{
//SEIssue should I assert c == fDialogContext? should reset be allowed to change contexts?
	this->InitializeDialogFields(fDialogContext);
}

void CDialogController::ResetDialog()
{
	SetInitialized(kFalse);
	this->ResetDialogFields(fDialogContext);
	SetInitialized(kTrue);
}

WidgetID CDialogController::ValidateDialogFields(IActiveContext* myContext)
{
	ASSERT_MSG(HasBeenInitialized(), "CDialogController::ValidateFields - Hey, you're trying to validate a dialog that has never been initialized!");
	return kNoInvalidWidgets;
}

WidgetID CDialogController::ValidateDialog()
{
	ASSERT_MSG(HasBeenInitialized(), "CDialogController::ValidateFields - Hey, you're trying to validate a dialog that has never been initialized!");
	return this->ValidateDialogFields(fDialogContext);
}

void CDialogController::UserCancelled()
{
}






void CDialogController::SetTextControlData(
	const WidgetID& widgetId,
	const PMString& text,
	const IPanelControlData* panel,
	bool16 invalidate,
	bool16 notifyOfChange)
{
	InterfacePtr<IPanelControlData> panelData(QueryIfNilElseAddRef(panel));
	IControlView* view = panelData->FindWidget(widgetId);
	if (view)
	{
		InterfacePtr<ITextControlData> data(view, IID_ITEXTCONTROLDATA);
		if (data)
			data->SetString(text, invalidate, notifyOfChange);
		else
		{
			ASSERT_FAIL("This widget doesn't have text data!");
		}
	}
}

PMString CDialogController::GetTextControlData(const WidgetID& widgetId, const IPanelControlData* panel) const
{
	InterfacePtr<IPanelControlData> panelData(QueryIfNilElseAddRef(panel));
	IControlView* view = panelData->FindWidget(widgetId);
	if (view)
	{
		InterfacePtr<ITextControlData> data(view, IID_ITEXTCONTROLDATA);
		if (data)
			return data->GetString();
		ASSERT_FAIL("This widget doesn't have text data!");

	}

	return PMString();
}

void CDialogController::SetTextValue(
	const WidgetID& widgetId,
	const PMReal& value,
	const IPanelControlData* panel,
	bool16 invalidate,
	bool16 notifyOfChange)
{
	InterfacePtr<IPanelControlData> panelData(QueryIfNilElseAddRef(panel));
	IControlView* view = panelData->FindWidget(widgetId);
	if (view)
	{
		InterfacePtr<ITextValue> textValue(view, IID_ITEXTVALUE);
		if (textValue)
			textValue->SetTextFromValue(value, invalidate, notifyOfChange);
		else
		{
			ASSERT_FAIL("This widget doesn't have ITextValue!");
		}
	}
}

PMReal CDialogController::GetTextValue(const WidgetID& widgetId, const IPanelControlData* panel, bool16 *outParsingError, bool16 *outIsBlank) const
{
	InterfacePtr<IPanelControlData> panelData(QueryIfNilElseAddRef(panel));
	InterfacePtr<IControlView> view((IControlView*) Utils<IWidgetUtils>()->QueryRelatedWidget(panelData, widgetId, IID_ICONTROLVIEW));
	if (view)
	{
		InterfacePtr<ITextValue> textValue(view, IID_ITEXTVALUE);
		if (textValue)
			return textValue->GetTextAsValue(outParsingError,outIsBlank);

	}
	ASSERT_FAIL("Couldn't find widget, or it doesn't have ITextValue!");

	return PMReal(0.0);
}

void CDialogController::SetTextValueControlState(
	const WidgetID& widgetId,
	ITextValue::TextControlState newState,
	const IPanelControlData* panel,
	bool16 invalidate,
	bool16 notifyOfChange)
{
	InterfacePtr<IPanelControlData> panelData(QueryIfNilElseAddRef(panel));
	InterfacePtr<IControlView> view((IControlView*) Utils<IWidgetUtils>()->QueryRelatedWidget(panelData, widgetId, IID_ICONTROLVIEW));
	if (view)
	{
		InterfacePtr<ITextValue> textValue(view, IID_ITEXTVALUE);
		if (textValue)
			textValue->SetControlState(newState, invalidate, notifyOfChange);
		else
		{
			ASSERT_FAIL("This widget doesn't have ITextValue!");
		}
	}
}

ITextValue::TextControlState CDialogController::GetTextValueControlState(const WidgetID& widgetId, const IPanelControlData* panel) const
{
	InterfacePtr<IPanelControlData> panelData(QueryIfNilElseAddRef(panel));
	InterfacePtr<IControlView> view((IControlView*) Utils<IWidgetUtils>()->QueryRelatedWidget(panelData, widgetId, IID_ICONTROLVIEW));
	if (view)
	{
		InterfacePtr<ITextValue> textValue(view, IID_ITEXTVALUE);
		if (textValue)
			return textValue->GetControlState();

	}
	ASSERT_FAIL("Couldn't find widget, or it doesn't have ITextValue!");
	return ITextValue::kNormal;
}

void CDialogController::SetBooleanControlData(
	const WidgetID& widgetId,
	bool16 isChecked,
	const IPanelControlData* panel,
	bool16 invalidate,
	bool16 notifyOfChange)
{
	InterfacePtr<IPanelControlData> panelData(QueryIfNilElseAddRef(panel));
	InterfacePtr<IControlView> view((IControlView*) Utils<IWidgetUtils>()->QueryRelatedWidget(panelData, widgetId, IID_ICONTROLVIEW));
	if (view)
	{
		InterfacePtr<IBooleanControlData> data(view, IID_IBOOLEANCONTROLDATA);
		if (data)
		{
			if (isChecked)
				data->Select(invalidate, notifyOfChange);
			else
				data->Deselect(invalidate, notifyOfChange);
		}
		else
		{
			ASSERT_FAIL("This widget doesn't have boolean data!");
		}
	}
}

bool16 CDialogController::GetBooleanControlData(const WidgetID& widgetId, const IPanelControlData* panel) const
{
	InterfacePtr<IPanelControlData> panelData(QueryIfNilElseAddRef(panel));
	InterfacePtr<IControlView> view((IControlView*) Utils<IWidgetUtils>()->QueryRelatedWidget(panelData, widgetId, IID_ICONTROLVIEW));
	if (view)
	{
		InterfacePtr<IBooleanControlData> data(view, IID_IBOOLEANCONTROLDATA);
		if (data)
			return data->IsSelected();
		ASSERT_FAIL("This widget doesn't have boolean data!");
	}

	return kFalse;
}

void CDialogController::SetTriStateControlData(
	const WidgetID& widgetId,
	bool16 isSelected,
	const IPanelControlData* panel,
	bool16 invalidate,
	bool16 notifyOfChange)
{
	ASSERT_MSG(widgetId != kPreviewButtonWidgetID,"SetTriStateControlData - You cannot set state of a preview checkbox directly! Dialog controller will initialize it to previous state for you.");

	if(isSelected)
		SetTriStateControlData(widgetId,ITriStateControlData::kSelected,panel, invalidate, notifyOfChange);
	else
		SetTriStateControlData(widgetId,ITriStateControlData::kUnselected,panel, invalidate, notifyOfChange);
}

void CDialogController::SetTriStateControlData(
	const WidgetID& widgetId,
	ITriStateControlData::TriState triState,
	const IPanelControlData* panel,
	bool16 invalidate,
	bool16 notifyOfChange)
{
	ASSERT_MSG(widgetId != kPreviewButtonWidgetID,"SetTriStateControlData - You cannot set state of a preview checkbox directly! Dialog controller will initialize it to previous state for you.");

	InterfacePtr<IPanelControlData> panelData(QueryIfNilElseAddRef(panel));
	InterfacePtr<IControlView> view((IControlView*) Utils<IWidgetUtils>()->QueryRelatedWidget(panelData, widgetId, IID_ICONTROLVIEW));
	if (view)
	{
		InterfacePtr<ITriStateControlData> data(view, IID_ITRISTATECONTROLDATA);
		if (data)
		{
			if (triState == ITriStateControlData::kSelected)
				data->Select(invalidate, notifyOfChange);
			else if (triState == ITriStateControlData::kUnknown)
				data->SetUnknown(invalidate, notifyOfChange);
			else
				data->Deselect(invalidate, notifyOfChange);
		}
		else
		{
			ASSERT_FAIL("This widget doesn't have tristate data!");
		}
	}
}

ITriStateControlData::TriState CDialogController::GetTriStateControlData(const WidgetID& widgetId, const IPanelControlData* panel) const
{
	InterfacePtr<IPanelControlData> panelData(QueryIfNilElseAddRef(panel));
	InterfacePtr<IControlView> view((IControlView*) Utils<IWidgetUtils>()->QueryRelatedWidget(panelData, widgetId, IID_ICONTROLVIEW));
	if (view)
	{
		InterfacePtr<ITriStateControlData> data(view, IID_ITRISTATECONTROLDATA);
		if (data)
			return data->GetState();
		ASSERT_FAIL("This widget doesn't have tristate data!");
	}

	return ITriStateControlData::kUnselected;
}

WidgetID CDialogController::GetSelectedClusterWidget(WidgetID cluster, const IPanelControlData* panel)
{
	InterfacePtr<IPanelControlData> panelData(QueryIfNilElseAddRef(panel));
	InterfacePtr<IControlView> clusterView((IControlView*) Utils<IWidgetUtils>()->QueryRelatedWidget(panelData, cluster, IID_ICONTROLVIEW));

	if (clusterView)
	{		
		InterfacePtr<IClusterController> clusterController(clusterView, UseDefaultIID());
		if(clusterController)
		{
			//Get the selected widget's (if any) event handler, and use it to obtain the widget ID
			InterfacePtr<IEventHandler> selectedWidgetEH(clusterController->QuerySelectedClusterWidgetEH());
			if(selectedWidgetEH)
			{
				InterfacePtr<IControlView> selectedWidgetView(selectedWidgetEH, UseDefaultIID());

				if(selectedWidgetView)
				{
					return selectedWidgetView->GetWidgetID();
				}
			}
		}
	}
	return kInvalidWidgetID;
}

void CDialogController::SetSelectedClusterWidget(WidgetID clusterId, WidgetID widgetToSelect, const IPanelControlData* panel,bool16 invalidate, bool16 notifyOfChange)
{
	InterfacePtr<IPanelControlData> panelData(QueryIfNilElseAddRef(panel));
	InterfacePtr<IControlView> clusterView((IControlView*) Utils<IWidgetUtils>()->QueryRelatedWidget(panelData, clusterId, IID_ICONTROLVIEW));
	if (clusterView)
	{
		InterfacePtr<IPanelControlData> clusterPanel(clusterView, IID_IPANELCONTROLDATA);
		if (clusterPanel)
		{
			IControlView *childView = clusterPanel->FindWidget(widgetToSelect);
			ASSERT_MSG(childView != nil,"SetSelectedClusterWidget - couldn't find widget to select!");
			InterfacePtr<ITriStateControlData> triData(childView, IID_ITRISTATECONTROLDATA);
			if (triData)
			{
				triData->Select(invalidate,	notifyOfChange);
			}
			else
			{
				InterfacePtr<IBooleanControlData> boolData(childView, IID_IBOOLEANCONTROLDATA);
				if (boolData)
				{
					boolData->Select(invalidate,notifyOfChange);
				}
			}

		}
	}

}

// ----- This should be called QueryListControlDataInterface! [amb]
IStringListControlData* CDialogController::QueryListControlDataInterface(const WidgetID& widgetId, const IPanelControlData* panel) const
{
	InterfacePtr<IPanelControlData> panelData(QueryIfNilElseAddRef(panel));
	InterfacePtr<IControlView> view((IControlView*) Utils<IWidgetUtils>()->QueryRelatedWidget(panelData, widgetId, IID_ICONTROLVIEW));
	IStringListControlData* listControlData = nil;
	if (view)
	{
		listControlData = (IStringListControlData*) view->QueryInterface(IID_ISTRINGLISTCONTROLDATA);
	}

	return listControlData;
}

IPanelControlData* CDialogController::QueryIfNilElseAddRef(const IPanelControlData* panel) const
{
	if (panel)
		panel->AddRef();
	else
		panel = (IPanelControlData*) ((CDialogController*) this)->QueryInterface(IID_IPANELCONTROLDATA);

	return (IPanelControlData*)panel;
}

void CDialogController::SelectDialogWidget(const WidgetID& widgetId)
{
	InterfacePtr<IWidgetParent> parentHolder(this, IID_IWIDGETPARENT);
	InterfacePtr<IDialog> dialog((IDialog*) parentHolder->QueryParentFor(IID_IDIALOG));

	// Try and select the control as the keyboard target
	InterfacePtr<IPanelControlData> panelData(dialog, UseDefaultIID());
	if (panelData)
	{
		IControlView* view = panelData->FindWidget(widgetId);

		if (view) {
			InterfacePtr<IKeyFocusHandler> keyFocusHandler(dialog, IID_IKEYFOCUSHANDLER);
			if (keyFocusHandler) {
				InterfacePtr<IEventHandler> viewEH(view, IID_IEVENTHANDLER);
				if (viewEH)
					keyFocusHandler->SetCurrentTargetEventHandler(viewEH, kFalse);	// kFalse so we don't revalidate.
			}
		}
	}
}

bool16 CDialogController::HasBeenInitialized() const
{
	return fInitialized;
}

void CDialogController::SetInitialized(bool16 initialized)
{
	fInitialized = initialized;
}

void CDialogController::SetOwner(IControlView* ownerPanel)
{
	fOwner = ownerPanel;
}

IControlView* CDialogController::GetOwner() const
{
	return fOwner;
}

void CDialogController::GetName(PMString& name)
{
	if (fName == kNullString) {
		// Set the name of the dialog command to the name of the dialog
		// HACK for now. We should get undo/redo name from the dialog itself.
		// ***** 2/1//98 TURN THIS INTO AN ASSERT REAL SOON NOW
		InterfacePtr<IWidgetParent> parentHolder(this, IID_IWIDGETPARENT);
		InterfacePtr<IWindow> window((IWindow*) parentHolder->QueryParentFor(IID_IWINDOW));
		if (window)
		{
			name = window->GetTitle();
		}
	}
	else
	{
		name = fName;
	}
}

void CDialogController::ClosingDialog(IActiveContext* lastChanceToUseMyContext)
{
}

void CDialogController::DialogClosing()
{
	this->ClosingDialog( fDialogContext);
	if( fDialogContext){
		fDialogContext->Release();
		fDialogContext = nil;
	}
}


bool16 CDialogController::GetPreviewModeOn()
{
	return fPreviewModeOn;
}

void CDialogController::SetPreviewModeOn(bool16 bOn)
{
	fPreviewModeOn = bOn;
}