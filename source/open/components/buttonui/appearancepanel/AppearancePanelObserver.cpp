//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/appearancepanel/AppearancePanelObserver.cpp $
//  
//  Owner: Mark VerMurlen
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
//  Comments: Updates list in appearance panel based on changes to the current
//  selection's IAppearanceList.  Also hooks up buttons to listen to
//  changes in the list, and watches for user interaction with the list
//  (handling selection, eyeball clicking etc.)
//  This is currently attached to the list, but it observes things outside the
//  list.  It probably should be moved to the palette boss (SPAM TODO)
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interfaces:
#include "IActionManager.h"
#include "IAppearanceSuite.h"
#include "IApplication.h"
#include "IBehaviorSuite.h"
#include "IconRsrcDefs.h"
#include "IControlView.h"
#include "IDropDownListController.h"
#include "DropDownListControlDataOf.tpp"
#include "IFormFieldFactory.h"
#include "IFormFieldSuite.h"
#include "IGraphicAttributeSuite.h"
#include "IListControlDataOf.h"
#include "IPanelControlData.h"
#include "IPanelDetailController.h"
#include "IPanelMgr.h"
#include "ISelectionDataSuite.h"
#include "IStringListControlData.h"
#include "ISubject.h"
#include "ITextControlData.h"
#include "ITextValue.h"
#include "ITreeViewController.h"
#include "ITriStateControlData.h"
#include "IUsageTracking.h"
#include "IWidgetUtils.h"
#include "IFontMgr.h"
#include "IFontGroup.h"
#include "IPMFont.h"
#include "IFontUtilData.h"
#include "IFontFamily.h"

// Includes:
#include "K2Pair.h"
#include "SelectionObserver.h"
#include "Trace.h"
#include "UIDList.h"
#include "KeyStates.h"
#include "CAlert.h"

// Utility files:
#include "AttributesUtils.h"
#include "ErrorUtils.h"
#include "FormFieldUIUtils.h"
#include "IFormFieldUtils.h"
#include "IGraphicStateUtils.h"
#include "ILayoutUIUtils.h"
#include "IPalettePanelUtils.h"
#include "PaletteRefUtils.h"
#include "SelectionUtils.h"
#include "PersistUtils.h"
#include "UserInterfaceUtils.h"

// ID.h files:
#include "BehaviorUIID.h"
#include "FormFieldUIID.h"
#include "FormFieldID.h"
#include "GraphicStylesID.h"
#include "DynamicDocumentsUIID.h"

using namespace UserInterfaceUtils;
using namespace FormFieldUIUtils;

//----------------------------------------------------------------------------------------
// Class AppearancePanelObserver
//----------------------------------------------------------------------------------------

class AppearancePanelObserver : public ActiveSelectionObserver
{
public:
	AppearancePanelObserver(IPMUnknown *boss);
	virtual ~AppearancePanelObserver();

protected:
	virtual void AutoAttach();
	virtual void AutoDetach();

	virtual void HandleSelectionChanged (const ISelectionMessage*);
	virtual void HandleSelectionAttributeChanged (const ISelectionMessage*);
	virtual void HandleSelectionUpdate
		(
		const ClassID&	inBossClassID, 
		ISubject* inSubject, 
		const PMIID& 	inProtocol,
		void* 			inMessage
		);
	
private:
	bool16 DoSelectionUpdate(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy); //adapted from LayerPanelObserver::Update

	// Methods for updating the panel, called in response to various changes	
	void UpdateWidgets( bool inFormWidgets); //adapted from LayerPanelObserver::UpdatePanel

	bool16 HandleControlChanged( const ClassID& inChange, ISubject* inSubject);

	void UpdateButtonNameWidget( IPanelControlData* panelData, bool inEnable );
	void UpdateConvertWidgets( IPanelControlData* panelData, bool bIsForm );
	void UpdateHiddenUntilWidget( IPanelControlData* inPanelData, bool bEnable );
	void UpdateFormFieldtypeWidget( IPanelControlData* inPanelData, bool bEnable );
						
	void AttachDetachControl(WidgetID inWID, PMIID inIID, bool32 inAttach);
	void HandleFormFieldsChoices(IFormFieldSuite* iFormSuite);

	bool16 SelectionHasStates();
	bool16 SelectionIsForm();
	bool16 SelectionHasAnyFormFields();

	bool16 IsPDFOptionsExpanded();
	void ShowHidePDFOptionsWidgets();
	void UpdatePDFOptionsWidgets();
	bool16 HandlePDFOptionsWidgetsChange(ISubject* inSubject);
	void FillOutFontAttributes(IPanelControlData* panelData, const PMString& fontFamily, const PMString& fontStyle, const bool16 isFontFamilyValid, const bool16 isFontStyleValid);
	void AddBracketsAroundString(PMString& name);
	Form::AppearanceState fSelectedState;
	bool	 fListWidgetsAttached;
	bool	 fFormWidgetsAttached;
};


CREATE_PMINTERFACE(AppearancePanelObserver, kAppearancePanelObserverImpl)

//----------------------------------------------------------------------------------------
// AppearancePanelObserver constructor 
//----------------------------------------------------------------------------------------

AppearancePanelObserver::AppearancePanelObserver(IPMUnknown *boss) :
	ActiveSelectionObserver(boss, IID_IOBSERVER),
	fListWidgetsAttached(false),
	fFormWidgetsAttached(false),
	fSelectedState(Form::kStateInvalid)
{
	
}


//----------------------------------------------------------------------------------------
// AppearancePanelObserver::~AppearancePanelObserver: 
//----------------------------------------------------------------------------------------

AppearancePanelObserver::~AppearancePanelObserver()
{
}


//________________________________________________________________________________________

void AppearancePanelObserver::UpdateButtonNameWidget( IPanelControlData* inPanelData, bool inEnable )
{
	IControlView* iEditView = inPanelData->FindWidget(kNameEditWID);
	InterfacePtr<IAppearanceSuite> iAppearanceSuite( QueryAppearanceSuite() );

	ASSERT_MSG(iEditView, "Widget Not Found");
	if ( iEditView ==0 )
		return;

	PMString strValue = "";
	InterfacePtr<ITextControlData> iEdit(iEditView, ::UseDefaultIID());
	ITextValue::TextControlState controlState = ITextValue::kUnknown;
	InterfacePtr<ITextValue> iTextValue(iEditView, ::UseDefaultIID());
	
	if ( !iAppearanceSuite || ! iAppearanceSuite->GetName(strValue) )
	{
		InterfacePtr<IFormFieldSuite> iFormSuite( FormFieldUIUtils::QueryFormSuite() );
		if (iFormSuite && iFormSuite->IsDefaultSelection() )
		{
			InterfacePtr<IGraphicAttributeSuite> iGfxAttrSuite ( Utils<IGraphicStateUtils>()->QueryActiveGraphicAttrSuite ());
			if ( iGfxAttrSuite && iGfxAttrSuite->GetAttributeCount(kFormNameAttrBoss) == 1)
			{
				if ( AttributesUtils::HasUniqueValue(iGfxAttrSuite, kFormNameAttrBoss, &strValue) )
					controlState = ITextValue::kNormal;	
			}
			else
			{
				InterfacePtr<IFormFieldFactory> fieldFactory(Utils<IFormFieldUtils>()->QueryFormFieldFactory(kPushButtonFactoryBoss));
				if ( fieldFactory )
					strValue = fieldFactory->GetDefaultBaseObjectName();
			}
		}
	}
	
	if ( !strValue.empty() )
		controlState = ITextValue::kNormal;		

	//Need to set iLastGood, otherwise we don't always get change notifications...

	iEdit->SetString(strValue);
	iTextValue->SetControlState(controlState);
	iEditView->Enable(inEnable);
}


//________________________________________________________________________________________

void AppearancePanelObserver::UpdateConvertWidgets( IPanelControlData* inPanelData, bool bIsForm )
{
	IControlView* iConvertToButton = inPanelData->FindWidget(kConvertToButtonButtonWidgetID);
	IControlView* iConvertToObject = inPanelData->FindWidget(kConvertToObjectButtonWidgetID);
	
	if ( !iConvertToButton || !iConvertToObject )
		return;
	
	InterfacePtr<IFormFieldSuite> iFormFieldSuite(FormFieldUIUtils::QueryFormSuite());

	if ( bIsForm )
	{
		bool16 outWarnNonEmptyStates = false;
		iConvertToObject->Enable(iFormFieldSuite->CanDestroyFieldFromSelection(outWarnNonEmptyStates), kFalse);
		iConvertToObject->ShowView();
		iConvertToButton->HideView();
		iConvertToButton->Disable(kFalse);
	}
	else
	{		
		bool16 enable = iFormFieldSuite && iFormFieldSuite->CanCreateFieldFromSelection(kPushButtonItemBoss);							
		iConvertToObject->HideView();
		iConvertToObject->Disable(kFalse);		
		iConvertToButton->Enable(enable, kFalse);
		iConvertToButton->ShowView();
	}
}

//________________________________________________________________________________________

void AppearancePanelObserver::UpdateHiddenUntilWidget( IPanelControlData* inPanelData, bool bEnable )
{
	IControlView* iHiddenUntilCBView = inPanelData->FindWidget(kHiddenUntilCheckBoxWidgetID);
	InterfacePtr<ITriStateControlData> data(iHiddenUntilCBView, IID_ITRISTATECONTROLDATA);
	ASSERT( data != nil);
	if (bEnable)
	{
		InterfacePtr<IFormFieldSuite> iFormFieldSuite(FormFieldUIUtils::QueryFormSuite());
		bool16 isMixed = kFalse;
		bool16 isHidden = iFormFieldSuite && iFormFieldSuite->GetIsInitiallyHidden(isMixed);
		if (!isMixed && isHidden)
			data->Select();
		else if (isMixed)
			data->SetUnknown();
		else
			data->Deselect();
	}
	else
		data->Deselect();

	iHiddenUntilCBView->Enable(bEnable);	
}

//________________________________________________________________________________________

void AppearancePanelObserver::UpdateFormFieldtypeWidget( IPanelControlData* inPanelData, bool inEnable )
{
	IControlView* iEditView = inPanelData->FindWidget(kFormFieldChoicesWidgetID);
	InterfacePtr<IAppearanceSuite> iAppearanceSuite( QueryAppearanceSuite() );

	ASSERT_MSG(iEditView, "Widget Not Found");
	if ( iEditView ==0 )
		return;

	InterfacePtr<IDropDownListController> formfieldChoice((IDropDownListController *) 
		Utils<IWidgetUtils>()->QueryRelatedWidget(inPanelData, kFormFieldChoicesWidgetID, IID_IDROPDOWNLISTCONTROLLER));

	if(formfieldChoice)
	{
		formfieldChoice->Deselect();
		formfieldChoice->Disable(2);
		formfieldChoice->Select(-1);
	}

	InterfacePtr<IFormFieldSuite> iFormSuite( FormFieldUIUtils::QueryFormSuite() );
	if (iFormSuite)
	{	
		if (iFormSuite->IsFieldSelectionOfType(kPushButtonItemBoss))
			formfieldChoice->Select(0);
		else if(iFormSuite->IsFieldSelectionOfType(kCheckBoxItemBoss))
			formfieldChoice->Select(3);
		else if(iFormSuite->IsFieldSelectionOfType(kComboBoxItemBoss))
			formfieldChoice->Select(4);
		else if(iFormSuite->IsFieldSelectionOfType(kListBoxFieldItemBoss))
			formfieldChoice->Select(5);
		else if(iFormSuite->IsFieldSelectionOfType(kRadioButtonItemBoss))
			formfieldChoice->Select(6);
		else if(iFormSuite->IsFieldSelectionOfType(kSignatureFieldItemBoss))
			formfieldChoice->Select(7);
		else if(iFormSuite->IsFieldSelectionOfType(kTextFieldItemBoss))
			formfieldChoice->Select(8);
		else
			formfieldChoice->Select(-1);
	}
	
	iEditView->Enable(inEnable);
}

//________________________________________________________________________________________

bool16 AppearancePanelObserver::SelectionHasStates()
{
	if (!fCurrentSelection || ! fCurrentSelection->IsInterfaceEnabled (IID_IFORMFIELDSUITE) )
		return kFalse;

	InterfacePtr<IFormFieldSuite> iFormFieldSuite(FormFieldUIUtils::QueryFormSuite());

	ClassID inFormFieldType = kInvalidClass;
	if (iFormFieldSuite)
	{
		if (iFormFieldSuite->IsFieldSelectionOfType(kPushButtonItemBoss))
			inFormFieldType = kPushButtonItemBoss;
		else if (iFormFieldSuite->IsFieldSelectionOfType(kCheckBoxItemBoss))
			inFormFieldType = kCheckBoxItemBoss;
		else if (iFormFieldSuite->IsFieldSelectionOfType(kRadioButtonItemBoss))
			inFormFieldType = kRadioButtonItemBoss;
		else if (iFormFieldSuite->IsFieldSelectionOfType(kTextFieldItemBoss))
			inFormFieldType = kTextFieldItemBoss;
		else if (iFormFieldSuite->IsFieldSelectionOfType(kListBoxFieldItemBoss))
			inFormFieldType = kListBoxFieldItemBoss;
		else if (iFormFieldSuite->IsFieldSelectionOfType(kComboBoxItemBoss))
			inFormFieldType = kComboBoxItemBoss;
		else if (iFormFieldSuite->IsFieldSelectionOfType(kSignatureFieldItemBoss))
			inFormFieldType = kSignatureFieldItemBoss;
	}

	return FormFieldUIUtils::SelectionHasStates(inFormFieldType);
}

//________________________________________________________________________________________

bool16 AppearancePanelObserver::SelectionIsForm()
{
	if (!fCurrentSelection || !fCurrentSelection->IsInterfaceEnabled (IID_IFORMFIELDSUITE) )
		return kFalse;
		
	InterfacePtr<IFormFieldSuite> iFormFieldSuite(FormFieldUIUtils::QueryFormSuite());

	ClassID inFormFieldType = kInvalidClass;
	if (iFormFieldSuite)
	{
		if (iFormFieldSuite->IsFieldSelectionOfType(kPushButtonItemBoss))
			inFormFieldType = kPushButtonItemBoss;
		else if (iFormFieldSuite->IsFieldSelectionOfType(kCheckBoxItemBoss))
			inFormFieldType = kCheckBoxItemBoss;
		else if (iFormFieldSuite->IsFieldSelectionOfType(kRadioButtonItemBoss))
			inFormFieldType = kRadioButtonItemBoss;
		else if (iFormFieldSuite->IsFieldSelectionOfType(kTextFieldItemBoss))
			inFormFieldType = kTextFieldItemBoss;
		else if (iFormFieldSuite->IsFieldSelectionOfType(kListBoxFieldItemBoss))
			inFormFieldType = kListBoxFieldItemBoss;
		else if (iFormFieldSuite->IsFieldSelectionOfType(kComboBoxItemBoss))
			inFormFieldType = kComboBoxItemBoss;
		else if (iFormFieldSuite->IsFieldSelectionOfType(kSignatureFieldItemBoss))
			inFormFieldType = kSignatureFieldItemBoss;
	}

	return FormFieldUIUtils::SelectionIsForm(inFormFieldType);
}

//________________________________________________________________________________________

bool16 AppearancePanelObserver::SelectionHasAnyFormFields()
{
	if (!fCurrentSelection || !fCurrentSelection->IsInterfaceEnabled (IID_IFORMFIELDSUITE) )
		return kFalse;
		
	InterfacePtr<IFormFieldSuite> iFormFieldSuite(FormFieldUIUtils::QueryFormSuite());
	if (iFormFieldSuite)
	{
		return iFormFieldSuite->SelectionHasAnyFormFields();
	}

	return kFalse;
}

//________________________________________________________________________________________
//tw  Reponds to  IID_SELECTION_MESSAGE, ISelectionMessage::kSelectionChanged

void AppearancePanelObserver::HandleSelectionChanged(const ISelectionMessage* inSelMsg)
{
	ActiveSelectionObserver::HandleSelectionChanged(inSelMsg);
	
	UpdateWidgets( true );
}

//________________________________________________________________________________________
//tw  Reponds to  IID_SELECTION_MESSAGE, ISelectionMessage::kSelectionAttributeChanged

void AppearancePanelObserver::HandleSelectionAttributeChanged( const ISelectionMessage*	iSelectionMsg )
{
	//Update widgets that correspond to the change...

	bool wasStateChange = iSelectionMsg->WasSuiteAffected (IID_IAPPEARANCESUITE);
	bool wasFormAttrChanged = iSelectionMsg->WasSuiteAffected (IID_IAPPEARANCESUITE) ||
								iSelectionMsg->WasSuiteAffected (IID_IGRAPHICATTRIBUTESUITE) ||
								iSelectionMsg->WasSuiteAffected (IID_IFORMFIELDSUITE);

	if (wasStateChange || wasFormAttrChanged)
	{
		bool isForm = SelectionIsForm();

        bool updateFormWidgets = (isForm && wasFormAttrChanged); //TODO: What was this for: || fFormWidgetsAttached != fFormWidgetsAttached;
		
		UpdateWidgets( updateFormWidgets );
	}
}

//________________________________________________________________________________________
//tw

void AppearancePanelObserver::HandleSelectionUpdate
	(
	const ClassID&	inBossClassID, 
	ISubject* inSubject, 
	const PMIID& 	inProtocol,
	void* 			inMessage
	)
{
	if ( !DoSelectionUpdate(inBossClassID, inSubject, inProtocol, inMessage) )
		ActiveSelectionObserver::HandleSelectionUpdate(inBossClassID, inSubject, inProtocol, inMessage);
}

//----------------------------------------------------------------------------------------
// AppearancePanelObserver::DoSelectionUpdate: (was Update - tw)
//----------------------------------------------------------------------------------------

bool16 AppearancePanelObserver::DoSelectionUpdate(const ClassID& inChange, ISubject* inSubject, const PMIID& protocol, void* changedBy)
{
	// ==> Please update GetObserverInfo()  <==

//	Trace("got message %x\n",inChange);
	
	// Check if the view is active before handling this update
	// The reason we are checking this is because multiple AppearancePanelObservers are being created
	// for each thumbnail size.  This could result in multiple calls to this routine for just one
	// single event.  See Vantive # 616089.
	InterfacePtr<IControlView> view( this, IID_ICONTROLVIEW );
	if ( ! view->IsVisible() )
		return kTrue;

	if (FormWidgetBlocker::Blocked())
		return kFalse;

	if (protocol == IID_IFONTMGR && inChange == kFontSystemChangedMessage)
	{
		InterfacePtr<IFontUtilData> fontutilData(GetExecutionContextSession(), UseDefaultIID());
		fontutilData->InvalidateFontCacheData();
		fontutilData->UpdateFontCacheData();

		UpdatePDFOptionsWidgets();
		return kTrue;
	}

	FormWidgetBlocker blocker;

	return HandleControlChanged(inChange, inSubject); //Handle any other control changed (name, visible, etc.)	
}

//----------------------------------------------------------------------------------------
//Handle any other control changed (name, visible, etc.)

bool16 AppearancePanelObserver::HandleControlChanged( const ClassID& inChange, ISubject* inSubject)
{
	//Blocking handled by caller (DoSelectionUpdate)
	bool16 handled = kFalse;
	
	InterfacePtr<IControlView> iView(inSubject, IID_ICONTROLVIEW);
	if (!iView) return kFalse;

	InterfacePtr<IFormFieldSuite> iFormSuite( FormFieldUIUtils::QueryFormSuite() );
	InterfacePtr<IAppearanceSuite> iAppearanceSuite( QueryAppearanceSuite() );

	WidgetID wid = iView->GetWidgetID();
	switch (wid.Get())
	{
	case kNameEditWID:
		// Requires selection
		if (iFormSuite)
		{
			handled = kTrue;
			// Make sure we don't set a blank name... #525049
			InterfacePtr<ITextControlData> iEdit(inSubject, ::UseDefaultIID());
			if (!iEdit->GetString().IsEmpty())
			{
				if ( iAppearanceSuite )
				{
					ErrorCode setNameResult = iAppearanceSuite->SetName(iEdit->GetString());
					if (setNameResult != kSuccess )
					{
						PMString string = ErrorUtils::PMGetErrorString(setNameResult);
						if (!string.IsNull()) {
							ErrorUtils::PMSetGlobalErrorCode(kSuccess);
							CAlert::ErrorAlert(string);
						}
						// Name wasn't set presumably because the selected item is not a button, set the user default instead.
						if ( iFormSuite && iFormSuite->IsDefaultSelection() )
						{
							InterfacePtr<IFormFieldFactory> fieldFactory(Utils<IFormFieldUtils>()->QueryFormFieldFactory(kPushButtonFactoryBoss));
							InterfacePtr<IGraphicAttributeSuite> iGfxAttrSuite ( Utils<IGraphicStateUtils>()->QueryActiveGraphicAttrSuite ());
							if ( fieldFactory && iGfxAttrSuite )
								AttributesUtils::SetStringValue( "$$$/Panel/CmdName/FormFieldName", iGfxAttrSuite, kFormNameAttrBoss, fieldFactory->GetDefaultBaseObjectName() );
						}
					}
				}
				else if ( iFormSuite && iFormSuite->IsDefaultSelection() )
				{
					InterfacePtr<IGraphicAttributeSuite> iGfxAttrSuite ( Utils<IGraphicStateUtils>()->QueryActiveGraphicAttrSuite ());
					UpdateTextAttribute( "$$$/Panel/CmdName/FormFieldName", iGfxAttrSuite, kFormNameAttrBoss, inSubject );
				}
			}
			else
			{
				if ( iFormSuite->IsDefaultSelection() ) {
					InterfacePtr<IFormFieldFactory> fieldFactory(Utils<IFormFieldUtils>()->QueryFormFieldFactory(kPushButtonFactoryBoss));
					if(fieldFactory)
					{
						InterfacePtr<IGraphicAttributeSuite> iGfxAttrSuite ( Utils<IGraphicStateUtils>()->QueryActiveGraphicAttrSuite ());
						AttributesUtils::SetStringValue( "$$$/Panel/CmdName/FormFieldName", iGfxAttrSuite, kFormNameAttrBoss, fieldFactory->GetDefaultBaseObjectName() );
					}
				}
			}
		}
		break;

	case kFormFieldChoicesWidgetID:
		// Requires selection
		if (inChange == kPopupChangeStateMessage && iFormSuite)
		{
			handled = kTrue;
			HandleFormFieldsChoices(iFormSuite);
		}
		break;

	case kShowPreviewButtonWidgetID:
		// Show preview even in no selection or non form-field selection cases.
		if (inChange == kTrueStateMessage)
		{
			handled = kTrue;											
			InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
			InterfacePtr<IActionManager> iActionMgr(theApp->QueryActionManager());
			if (iActionMgr)
			{
                // HTML Preview
                iActionMgr->PerformAction(GetExecutionContextSession()->GetActiveContext(), kHTMLFXLPreviewActionID);
			}
		}
		break;	

	case kHiddenUntilCheckBoxWidgetID:
		// Requires selection
		if ((inChange == kTrueStateMessage || inChange == kFalseStateMessage) && iFormSuite)
		{
			handled = kTrue;
			InterfacePtr<ITriStateControlData> data(inSubject, ::UseDefaultIID());
			iFormSuite->SetIsInitiallyHidden(data->IsSelected());
		}
		break;

	case kPDFOptionsExpanderWidgetID:
		if (inChange == kTrueStateMessage)
		{
			handled = kTrue;
			// Toggle the expander icon resource, and update the PDF options widgets.
			if (iView->GetRsrcID() == kTreeBranchExpandedRsrcID)
			{
				iView->SetRsrcID(kTreeBranchCollapsedRsrcID);
				ShowHidePDFOptionsWidgets();
			}
			else
			{
				iView->SetRsrcID(kTreeBranchExpandedRsrcID);
				ShowHidePDFOptionsWidgets();
				UpdatePDFOptionsWidgets();
			}
		}
		break;

	default:
		handled = HandlePDFOptionsWidgetsChange(inSubject);
		break;
	}

	return handled;
}

//----------------------------------------------------------------------------------------
// AppearancePanelObserver::UpdateWidgets: 
//----------------------------------------------------------------------------------------

void AppearancePanelObserver::UpdateWidgets(bool inFormWidgets)
{
	if (FormWidgetBlocker::Blocked())
		return;

	FormWidgetBlocker blocker;

	InterfacePtr<IFormFieldSuite> iFormSuite( FormFieldUIUtils::QueryFormSuite() );
	InterfacePtr<IPanelControlData> panelData(this, UseDefaultIID());
	
	InterfacePtr<ISelectionDataSuite> iSelectionDataSuite(static_cast<ISelectionDataSuite*>(QueryAbstractSelection(IID_ISELECTIONDATASUITE)));
	bool enableFormFieldType = (iFormSuite && (iFormSuite->CanCreateFieldFromSelection(kPushButtonItemBoss)||
			iFormSuite->CanCreateFieldFromSelection(kCheckBoxItemBoss) ||
			iFormSuite->CanCreateFieldFromSelection(kRadioButtonItemBoss) ||
			iFormSuite->CanCreateFieldFromSelection(kTextFieldItemBoss) ||
			iFormSuite->CanCreateFieldFromSelection(kListBoxFieldItemBoss) ||
			iFormSuite->CanCreateFieldFromSelection(kComboBoxItemBoss) ||
			iFormSuite->CanCreateFieldFromSelection(kSignatureFieldItemBoss) ));

	if (inFormWidgets)
	{
		InterfacePtr<IFormFieldFactory> fieldFactory(Utils<IFormFieldUtils>()->QueryFormFieldFactory(kPushButtonFactoryBoss));
		bool16 isSingleSelection = iSelectionDataSuite && iSelectionDataSuite->GetSelectionCount() == 1;
		
		bool isForm = SelectionIsForm();
		// if the selection has any form fields, enable the convert to object widget instead of the convert to button widget..
		// Enable the Hidden until triggered widget too if the selection has any form fields.
		bool enableConvertToObject = SelectionHasAnyFormFields();	
		
		// Enable the application of actions onto simple objects so as to save an extra step of conversion to button first..
		bool ConvertibleToButton = !isForm && iFormSuite && iFormSuite->CanCreateFieldFromSelection(kPushButtonItemBoss);

		IControlView *popup = panelData->FindWidget(kBehaviorChoicesWidgetID);
		if ( popup )
		{
			popup->Enable(((isForm || ConvertibleToButton) && isSingleSelection), kTrue);
		}
		UpdateStaticWidget( panelData, (isForm && isSingleSelection), kActionsListStaticWID );
		
		IControlView *actionsList = panelData->FindWidget(kBehaviorsTreeBorderWidgetID);
		if ( actionsList )
			actionsList->Enable((isForm && isSingleSelection), kTrue);

		IControlView *eventDropDown = panelData->FindWidget(kButtonEventChoicesWidgetID);
		if ( eventDropDown )
		{
			if (!isForm && iFormSuite && !iFormSuite->IsDefaultSelection() )
			{
				// Reset to the "On Release" event otherwise when create button by choosing an
				// action puts it in the event last used.
				InterfacePtr<IDropDownListController> eventDropDownCntrl((IDropDownListController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kButtonEventChoicesWidgetID, IID_IDROPDOWNLISTCONTROLLER));
				if (eventDropDownCntrl)
				{
					InterfacePtr<IStringListControlData> eventDDListData(eventDropDownCntrl, IID_ISTRINGLISTCONTROLDATA);
					if (eventDDListData && eventDDListData->Length() > 0)
						eventDropDownCntrl->Select(IDropDownListController::kBeginning, kFalse, kTrue);
				}
			}
			eventDropDown->Enable((isForm && isSingleSelection), kTrue);
		}

		UpdateStaticWidget( panelData, (isForm && isSingleSelection), kEventStaticWID );

		bool16 enableNameWidget =  (isForm && (isSingleSelection || iFormSuite->IsFieldSelectionOfType(kRadioButtonItemBoss))) 
			|| (iFormSuite && iFormSuite->IsDefaultSelection());

		UpdateStaticWidget( panelData, enableNameWidget, kNameStaticWID );
		UpdateButtonNameWidget( panelData, enableNameWidget);
		UpdateConvertWidgets( panelData, enableConvertToObject );

		UpdateStaticWidget( panelData, enableFormFieldType, kFormsListStaticWID );
		UpdateFormFieldtypeWidget(panelData, enableFormFieldType);

		UpdateHiddenUntilWidget( panelData, enableConvertToObject );
		FormFieldUIUtils::UpdateShowPreviewWidget( panelData, fCurrentSelection );

		ShowHidePDFOptionsWidgets();
		if (IsPDFOptionsExpanded())
			UpdatePDFOptionsWidgets();
	}
}

//----------------------------------------------------------------------------------------

void AppearancePanelObserver::AttachDetachControl(WidgetID inWID, PMIID inIID, bool32 inAttach)
{
	InterfacePtr<IPanelControlData> panelData(this, UseDefaultIID());
	IControlView* iView = panelData->FindWidget(inWID);
	ASSERT_MSG(iView != nil, "FormFieldUIWidgetsObserver::AttachDetachControl: Can't find widget ID!");
	if (iView == nil)
		return;
		
	InterfacePtr<ISubject> iSubject(iView, IID_ISUBJECT);
	if (inAttach) {
		ASSERT_MSG( !iSubject->IsAttached(this, inIID), "AppearancePanelObserver::AttachDetachControl - Control already attached" );
		iSubject->AttachObserver( this, inIID);
	}
	else
		iSubject->DetachObserver( this, inIID);
}

//----------------------------------------------------------------------------------------
// Attach observers we need when an item with appearance states is selected...

void AppearancePanelObserver::AutoAttach()
{
	ActiveSelectionObserver::AutoAttach();
	if (!fFormWidgetsAttached)
	{
		AttachDetachControl(kNameEditWID, IID_ITEXTCONTROLDATA, true);			
		AttachDetachControl(kButtonEventChoicesWidgetID, IID_ISTRINGLISTCONTROLDATA, true);
		AttachDetachControl(kHiddenUntilCheckBoxWidgetID, IID_ITRISTATECONTROLDATA, true);
		AttachDetachControl(kShowPreviewButtonWidgetID, IID_ITRISTATECONTROLDATA, true);					
		AttachDetachControl(kFormFieldChoicesWidgetID, IID_ISTRINGLISTCONTROLDATA, true);
		AttachDetachControl(kPDFOptionsExpanderWidgetID, IID_ITRISTATECONTROLDATA, true);
		AttachDetachControl(kReadOnlyCheckBoxWidgetID, IID_ITRISTATECONTROLDATA, true);
		AttachDetachControl(kRequiredCheckBoxWidgetID, IID_ITRISTATECONTROLDATA, true);
		AttachDetachControl(kSelectedByDefaultCheckBoxWidgetID, IID_ITRISTATECONTROLDATA, true);
		AttachDetachControl(kMultilineCheckBoxWidgetID, IID_ITRISTATECONTROLDATA, true);
		AttachDetachControl(kPasswordCheckBoxWidgetID, IID_ITRISTATECONTROLDATA, true);
		AttachDetachControl(kScrollableCheckBoxWidgetID, IID_ITRISTATECONTROLDATA, true);
		AttachDetachControl(kButtonPDFPrintableCheckBoxWID, IID_ITRISTATECONTROLDATA, true);
		AttachDetachControl(kButtonPDFDescriptionWID, IID_ITEXTCONTROLDATA, true);	
		AttachDetachControl(kMultipleSelectionCheckBoxWidgetID, IID_ITRISTATECONTROLDATA, true);
		AttachDetachControl(kFontSizeEditBoxWidgetID, IID_ITEXTCONTROLDATA, true);	
		AttachDetachControl(kSortItemsCheckBoxWidgetID, IID_ITRISTATECONTROLDATA, true);
		AttachDetachControl(kMERTLOptionCheckBoxWidgetID, IID_ITRISTATECONTROLDATA, true);
		AttachDetachControl(kExportValueEditWidgetID, IID_ITEXTCONTROLDATA, true);
		AttachDetachControl(kFormFontFamilyWidgetID, IID_ISTRINGLISTCONTROLDATA, true);
		AttachDetachControl(kFormFontStyleWidgetID, IID_ISTRINGLISTCONTROLDATA, true);

		InterfacePtr<ISubject> subjSession(GetExecutionContextSession(), UseDefaultIID());
		if (subjSession && !subjSession->IsAttached(this, IID_IFONTMGR))
			subjSession->AttachObserver(this, IID_IFONTMGR);

		fFormWidgetsAttached = true;
	}

	UpdateWidgets( true );
}

//----------------------------------------------------------------------------------------
// Detach observers we need when an item with appearance states is selected...

void AppearancePanelObserver::AutoDetach()
{
	ActiveSelectionObserver::AutoDetach();
	if (fFormWidgetsAttached)
	{		
		// ----- Detach from the view.
		AttachDetachControl(kNameEditWID, IID_ITEXTCONTROLDATA, false);
		AttachDetachControl(kButtonEventChoicesWidgetID, IID_ISTRINGLISTCONTROLDATA, false);
		AttachDetachControl(kHiddenUntilCheckBoxWidgetID, IID_ITRISTATECONTROLDATA, false);
		AttachDetachControl(kShowPreviewButtonWidgetID, IID_ITRISTATECONTROLDATA, false);					
		AttachDetachControl(kFormFieldChoicesWidgetID, IID_ISTRINGLISTCONTROLDATA, false);			
		AttachDetachControl(kPDFOptionsExpanderWidgetID, IID_ITRISTATECONTROLDATA, false);	
		AttachDetachControl(kReadOnlyCheckBoxWidgetID, IID_ITRISTATECONTROLDATA, false);
		AttachDetachControl(kRequiredCheckBoxWidgetID, IID_ITRISTATECONTROLDATA, false);
		AttachDetachControl(kSelectedByDefaultCheckBoxWidgetID, IID_ITRISTATECONTROLDATA, false);
		AttachDetachControl(kMultilineCheckBoxWidgetID, IID_ITRISTATECONTROLDATA, false);
		AttachDetachControl(kPasswordCheckBoxWidgetID, IID_ITRISTATECONTROLDATA, false);
		AttachDetachControl(kScrollableCheckBoxWidgetID, IID_ITRISTATECONTROLDATA, false);
		AttachDetachControl(kButtonPDFPrintableCheckBoxWID, IID_ITRISTATECONTROLDATA, false);
		AttachDetachControl(kButtonPDFDescriptionWID, IID_ITEXTCONTROLDATA, false);	
		AttachDetachControl(kMultipleSelectionCheckBoxWidgetID, IID_ITRISTATECONTROLDATA, false);
		AttachDetachControl(kFontSizeEditBoxWidgetID, IID_ITEXTCONTROLDATA, false);	
		AttachDetachControl(kSortItemsCheckBoxWidgetID, IID_ITRISTATECONTROLDATA, false);
		AttachDetachControl(kMERTLOptionCheckBoxWidgetID, IID_ITRISTATECONTROLDATA, false);
		AttachDetachControl(kExportValueEditWidgetID, IID_ITEXTCONTROLDATA, false);	
		AttachDetachControl(kFormFontFamilyWidgetID, IID_ISTRINGLISTCONTROLDATA, false);
		AttachDetachControl(kFormFontStyleWidgetID, IID_ISTRINGLISTCONTROLDATA, false);

		InterfacePtr<ISubject>        subjSession(GetExecutionContextSession(), UseDefaultIID());
		if (subjSession && subjSession->IsAttached(this, IID_IFONTMGR))
			subjSession->DetachObserver(this, IID_IFONTMGR);

		fFormWidgetsAttached = false;
	}
}

//----------------------------------------------------------------------------------------

void AppearancePanelObserver::HandleFormFieldsChoices(IFormFieldSuite* iFormSuite)
{
	InterfacePtr<IPanelControlData> panelData(this, UseDefaultIID());
	InterfacePtr<IDropDownListController> formfieldChoice((IDropDownListController *) 
		Utils<IWidgetUtils>()->QueryRelatedWidget(panelData, kFormFieldChoicesWidgetID, IID_IDROPDOWNLISTCONTROLLER));

	if (formfieldChoice && iFormSuite)
	{
		int32 eventChoiceIndex = formfieldChoice->GetSelected();
		switch (eventChoiceIndex)
		{
		case 0:
			if ( iFormSuite->CanCreateFieldFromSelection(kPushButtonItemBoss) )
			{
				ICommandSequence* cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);

				if( iFormSuite->SelectionHasAnyFormFields())
					iFormSuite->DestroyFieldFromSelection(kPushButtonItemBoss);

				iFormSuite->CreateFieldFromSelection(kPushButtonItemBoss);

				CmdUtils::EndCommandSequence(cmdSeq);
			}
			break;
		
		case 3:
			if ( iFormSuite->CanCreateFieldFromSelection(kCheckBoxItemBoss) )
			{
				ICommandSequence* cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
				cmdSeq->SetName( PMString("$$$/Command/CheckBox") );

				if( iFormSuite->SelectionHasAnyFormFields())
					iFormSuite->DestroyFieldFromSelection(kCheckBoxItemBoss);

				iFormSuite->CreateFieldFromSelection(kCheckBoxItemBoss);

				CmdUtils::EndCommandSequence(cmdSeq);
			}
			break;
		
		case 4:
			if ( iFormSuite->CanCreateFieldFromSelection(kComboBoxItemBoss) )
			{
				ICommandSequence* cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
				cmdSeq->SetName( PMString("$$$/Command/ComboBox") );

				if( iFormSuite->SelectionHasAnyFormFields())
					iFormSuite->DestroyFieldFromSelection(kComboBoxItemBoss);

				iFormSuite->CreateFieldFromSelection(kComboBoxItemBoss);

				CmdUtils::EndCommandSequence(cmdSeq);
			}
			break;
		
		case 5:
			if ( iFormSuite->CanCreateFieldFromSelection(kListBoxFieldItemBoss) )
			{
				ICommandSequence* cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
				cmdSeq->SetName( PMString("$$$/Command/ListBox") );
				
				if( iFormSuite->SelectionHasAnyFormFields())
					iFormSuite->DestroyFieldFromSelection(kListBoxFieldItemBoss);

				iFormSuite->CreateFieldFromSelection(kListBoxFieldItemBoss);

				CmdUtils::EndCommandSequence(cmdSeq);
			}
			break;
		
		case 6:
			if ( iFormSuite->CanCreateFieldFromSelection(kRadioButtonItemBoss) )
			{
				ICommandSequence* cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
				cmdSeq->SetName( PMString("$$$/Command/RadioButton") );

				if( iFormSuite->SelectionHasAnyFormFields())
					iFormSuite->DestroyFieldFromSelection(kRadioButtonItemBoss);

				iFormSuite->CreateFieldFromSelection(kRadioButtonItemBoss);

				CmdUtils::EndCommandSequence(cmdSeq);
			}
			break;
			
		case 7:
			if ( iFormSuite->CanCreateFieldFromSelection(kSignatureFieldItemBoss) )
			{
				ICommandSequence* cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
				cmdSeq->SetName( PMString("$$$/Command/SignatureField") );

				if( iFormSuite->SelectionHasAnyFormFields())
					iFormSuite->DestroyFieldFromSelection(kSignatureFieldItemBoss);

				iFormSuite->CreateFieldFromSelection(kSignatureFieldItemBoss);

				CmdUtils::EndCommandSequence(cmdSeq);
			}
			break;
			
		case 8:
			if ( iFormSuite->CanCreateFieldFromSelection(kTextFieldItemBoss) )
			{
				ICommandSequence* cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
				cmdSeq->SetName( PMString("$$$/Command/TextField") );

				if( iFormSuite->SelectionHasAnyFormFields())
					iFormSuite->DestroyFieldFromSelection(kTextFieldItemBoss);

				iFormSuite->CreateFieldFromSelection(kTextFieldItemBoss);

				CmdUtils::EndCommandSequence(cmdSeq);
			}
			break;
		}
	}
}

//----------------------------------------------------------------------------------------

bool16 AppearancePanelObserver::IsPDFOptionsExpanded()
{
	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
	IControlView* iTreeExpanderIconView = iPanelControlData->FindWidget(kPDFOptionsExpanderWidgetID);

	ASSERT_MSG(iTreeExpanderIconView != nil, "IsPDFOptionsExpanded: nil expander view.");
	if (iTreeExpanderIconView->GetRsrcID() == kTreeBranchExpandedRsrcID)
		return kTrue;
	return kFalse;
}

//----------------------------------------------------------------------------------------

void AppearancePanelObserver::ShowHidePDFOptionsWidgets()
{
	int32 detailLevel = 7; // Hide everything i.e. PDFOptionsDetailController::kMainConfig
	InterfacePtr<IFormFieldSuite> iFormSuite( FormFieldUIUtils::QueryFormSuite() );
	if (IsPDFOptionsExpanded())
	{
		// Expanded PDF options view.
		// Find out the PDF options detail level to show according to the selection.
		if (iFormSuite && (iFormSuite->IsFieldSelectionOfType(kListBoxFieldItemBoss) ||
							iFormSuite->IsFieldSelectionOfType(kComboBoxItemBoss)))
		{
			if (iFormSuite->IsFieldSelectionOfType(kListBoxFieldItemBoss))
				detailLevel = 4;
			else
				detailLevel = 3;	// PDFOptionsDetailController::kListAndComboOptionsConfig
		}
		else if (iFormSuite && (iFormSuite->IsFieldSelectionOfType(kRadioButtonItemBoss) ||
								iFormSuite->IsFieldSelectionOfType(kCheckBoxItemBoss)))
			detailLevel = 6;	// PDFOptionsDetailController::kCheckBoxOptionsConfig
		else if (iFormSuite && iFormSuite->IsFieldSelectionOfType(kTextFieldItemBoss))
			detailLevel = 5;	// PDFOptionsDetailController::kTextFieldOptionsConfig
		else if (iFormSuite && iFormSuite->IsFieldSelection() && 
			!iFormSuite->SelectionHasAnyFieldsOfType(kMultiStateObjectItemBoss) && 
			!iFormSuite->SelectionHasAnyFieldsOfType(kPushButtonItemBoss))
			detailLevel = 2;	// PDFOptionsDetailController::kFormFieldOptionsConfig
		else if (iFormSuite && (iFormSuite->IsFieldSelectionOfType(kPushButtonItemBoss) || 
			 (iFormSuite->IsFieldSelection() && 
			!iFormSuite->SelectionHasAnyFieldsOfType(kMultiStateObjectItemBoss) && 
			iFormSuite->SelectionHasAnyFieldsOfType(kPushButtonItemBoss))))
			detailLevel = 1;	// PDFOptionsDetailController::kButtonOptionsConfigEnabled
		else
			detailLevel = 0;	// PDFOptionsDetailController::kButtonOptionsConfigDisabled
	}

	InterfacePtr<IPanelDetailController> iPanelDetail(this, UseDefaultIID());
	if (iPanelDetail && detailLevel != iPanelDetail->GetDetailLevel())
	{
		iPanelDetail->ShowDetailLevel(detailLevel);
	}

	// Enable adding to the list only if its a single selection.
	InterfacePtr<ISelectionDataSuite> iSelectionDataSuite(static_cast<ISelectionDataSuite*>(QueryAbstractSelection(IID_ISELECTIONDATASUITE)));
	bool16 isSingleSelection = iSelectionDataSuite && iSelectionDataSuite->GetSelectionCount() == 1;
	if (detailLevel == 3 || detailLevel == 4)
	{
		InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
		IControlView* listItemTextBoxWidgetView = iPanelControlData->FindWidget(kListItemTextNodeWID);
		IControlView* itemAddButtonWidgetView = iPanelControlData->FindWidget(kAddListOptionButtonWidgetID);
		IControlView* itemRemoveButtonWidgetView = iPanelControlData->FindWidget(kRemoveListOptionButtonWidgetID);
		IControlView* listItemsLabelWidgetView = iPanelControlData->FindWidget(kListItemsLabelWidgetID);

		if (!isSingleSelection)
		{
			listItemTextBoxWidgetView->Disable();			
			itemRemoveButtonWidgetView->Disable();
			itemAddButtonWidgetView->Disable();
			listItemsLabelWidgetView->Disable();
		}
		else
		{
			InterfacePtr<ITreeViewController> optionsTreeViewCntlr((ITreeViewController*) Utils<IWidgetUtils>()->QueryRelatedWidget(
				this, kListItemsWidgetID, IID_ITREEVIEWCONTROLLER));
			NodeIDList selectedItems;
			optionsTreeViewCntlr->GetSelectedItems(selectedItems);
			// Enable the delete button if there is some default list item.
			if (isSingleSelection && selectedItems.size() == 1)
				itemRemoveButtonWidgetView->Enable();
			else
				itemRemoveButtonWidgetView->Disable();

			InterfacePtr<ITextControlData> iListOptionEdit(listItemTextBoxWidgetView, UseDefaultIID());
			const PMString &textStr = iListOptionEdit->GetString();
			if(textStr.empty())
				itemAddButtonWidgetView->Disable();
			else
				itemAddButtonWidgetView->Enable();

			listItemTextBoxWidgetView->Enable();
			listItemsLabelWidgetView->Enable();
		}
	}

	// Enable selected by default only if a single radio button is selected in case of radio buttons. 
	// For check boxes, multiple selection is a valid case.
	if (detailLevel == 6)
	{
		InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
		IControlView* selectedByDefaultWidgetView = iPanelControlData->FindWidget(kSelectedByDefaultCheckBoxWidgetID);

		if(!isSingleSelection && iFormSuite && iFormSuite->IsFieldSelectionOfType(kRadioButtonItemBoss))
		{
			selectedByDefaultWidgetView->Disable();
		}
		else
		{
			selectedByDefaultWidgetView->Enable();
		}		
	}
}

//----------------------------------------------------------------------------------------
// This function handles updates from the PDF Options widgets.

bool16 AppearancePanelObserver::HandlePDFOptionsWidgetsChange(ISubject* inSubject)
{
	InterfacePtr<IControlView> iView(inSubject, IID_ICONTROLVIEW);
	if (!iView)	return kFalse;

	InterfacePtr<IFormFieldSuite> iFormSuite( FormFieldUIUtils::QueryFormSuite() );
	if (iFormSuite)
	{
		ICommandSequence* cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
		bool16 handled = kTrue;
		WidgetID wid = iView->GetWidgetID();
		switch (wid.Get())
		{
		case kButtonPDFDescriptionWID:
			{
				InterfacePtr<ITextControlData> data(inSubject, ::UseDefaultIID());
				iFormSuite->SetFormFieldDescription(data->GetString());
			}
			break;

		case kButtonPDFPrintableCheckBoxWID:
			{
				InterfacePtr<ITriStateControlData> data(inSubject, ::UseDefaultIID());
				iFormSuite->SetIsPrintable(data->IsSelected());
			}
			break;

		case kReadOnlyCheckBoxWidgetID:
			{
				InterfacePtr<ITriStateControlData> data(inSubject, ::UseDefaultIID());
				iFormSuite->SetIsReadOnly(data->IsSelected());
			}
			break;

		case kRequiredCheckBoxWidgetID:
			{
				InterfacePtr<ITriStateControlData> data(inSubject, ::UseDefaultIID());
				iFormSuite->SetIsRequired(data->IsSelected());
			}
			break;

		case kSelectedByDefaultCheckBoxWidgetID:
			{
				InterfacePtr<ITriStateControlData> data(inSubject, ::UseDefaultIID());
				iFormSuite->SetIsSelectedByDefault(data->IsSelected());
			}
			break;

		case kMultilineCheckBoxWidgetID:
			{
				InterfacePtr<ITriStateControlData> data(inSubject, ::UseDefaultIID());
				iFormSuite->SetIsTextFieldMultiline(data->IsSelected());
			}
			break;

		case kPasswordCheckBoxWidgetID:
			{
				InterfacePtr<ITriStateControlData> data(inSubject, ::UseDefaultIID());
				iFormSuite->SetIsTextFieldPasswordField(data->IsSelected());
			}
			break;

		case kScrollableCheckBoxWidgetID:
			{
				InterfacePtr<ITriStateControlData> data(inSubject, ::UseDefaultIID());
				iFormSuite->SetIsTextFieldScrollable(data->IsSelected());
			}
			break;
		
		case kMultipleSelectionCheckBoxWidgetID:
			{
				InterfacePtr<ITriStateControlData> data(inSubject, ::UseDefaultIID());
				iFormSuite->SetIsMultipleSelectionEnabled(data->IsSelected());
			}
			break;

		case kFontSizeEditBoxWidgetID:
			{
				InterfacePtr<ITextValue> textValue(inSubject, IID_ITEXTVALUE);
				bool16 err = kFalse;
				PMReal TextSize(textValue->GetTextAsValue(&err));

				iFormSuite->SetTextSizeAttribute(TextSize);
			}
			break;

		case kFormFontFamilyWidgetID:
			{
				InterfacePtr<IPanelControlData> panelData(this, UseDefaultIID());
				IControlView* familyView = panelData->FindWidget(kFormFontFamilyWidgetID);
				InterfacePtr<IStringListControlData> familyStringData(familyView, UseDefaultIID());
				InterfacePtr<IDropDownListController> familyDDLController(familyView, UseDefaultIID());
				int32 familyIndex = familyDDLController->GetSelected();
				if (familyIndex >= 0)
				{
					PMString fontFamilyName = familyStringData->GetString(familyIndex);
					InterfacePtr<IFontUtilData> fontutilData(GetExecutionContextSession(), UseDefaultIID());
					std::vector<PMString> styles;
					fontutilData->GetStylesInFontFamily(fontFamilyName, styles);
					IControlView* styleView = panelData->FindWidget(kFormFontStyleWidgetID);
					InterfacePtr<IStringListControlData> styleListData(styleView, UseDefaultIID());
					styleListData->Clear();
					for (size_t t = 0; t < styles.size(); t++)
						styleListData->AddString(styles[t]);
					InterfacePtr<IDropDownListController> styleDDLController(styleListData, UseDefaultIID());
					styleDDLController->Select(0, kTrue, kTrue);
					iFormSuite->SetFontFamilyAttr(fontFamilyName);
				}
		}
		case kFormFontStyleWidgetID:
			{
				InterfacePtr<IPanelControlData> panelData(this, UseDefaultIID());
				IControlView* familyView = panelData->FindWidget(kFormFontFamilyWidgetID);
				IControlView* styleView = panelData->FindWidget(kFormFontStyleWidgetID);
				InterfacePtr<IDropDownListController> familyDDLController(familyView, UseDefaultIID());
				InterfacePtr<IDropDownListController> styleDDLController(styleView, UseDefaultIID());
				int32 familyIndex = familyDDLController->GetSelected();
				int32 styleIndex = styleDDLController->GetSelected();
				if (familyIndex >= 0 && styleIndex >= 0)
				{
					InterfacePtr<IStringListControlData> familyStringData(familyView, UseDefaultIID());
					PMString family = familyStringData->GetString(familyIndex);
					InterfacePtr<IStringListControlData> styleStringData(styleView, UseDefaultIID());
					PMString style = styleStringData->GetString(styleIndex);
					InterfacePtr<IFontUtilData> fontutilData(GetExecutionContextSession(), UseDefaultIID());
					iFormSuite->SetFontStyleAttribute(style);
					iFormSuite->SetFontFamilyUIDAttr(family, style);
                    
                    //Highbeam Logging
                    InterfacePtr<IUsageTracking> usageTracking(GetExecutionContextSession(), UseDefaultIID());
                    if (usageTracking && usageTracking->IsUsageLoggingEnabled())
                    {
                        PMString category(IDUsageTracking_kPDFForm);
                        InterfacePtr<IFormFieldSuite> iFormSuite( FormFieldUIUtils::QueryFormSuite() );
                        if (iFormSuite)
                        {
                            if(iFormSuite->IsFieldSelectionOfType(kComboBoxItemBoss))
                                category.Append("_ComboBox");
                            else if(iFormSuite->IsFieldSelectionOfType(kListBoxFieldItemBoss))
                                category.Append("_ListBox");
                            else if(iFormSuite->IsFieldSelectionOfType(kTextFieldItemBoss))
                                category.Append("_TextField");
                        }
                        PMString fontName = family;
                        fontName.Append("_");
                        fontName.Append(style);
                        usageTracking->LogUsageEvent(category.GetUTF8String().c_str(), IDUsageTracking_kFontChange,fontName.GetUTF8String().c_str());
                    }
				}
				break;
			}

		case kSortItemsCheckBoxWidgetID:
			{
				InterfacePtr<ITriStateControlData> data(inSubject, ::UseDefaultIID());
				iFormSuite->SetShouldSortListItems(data->IsSelected());
			}
			break;

		case kMERTLOptionCheckBoxWidgetID:
			{
				InterfacePtr<ITriStateControlData> data(inSubject, ::UseDefaultIID());
				iFormSuite->SetIsMERTLEnabled(data->IsSelected());
			}
			break;

		case kExportValueEditWidgetID:
			{
				InterfacePtr<ITextControlData> data(inSubject, ::UseDefaultIID());
				iFormSuite->SetExportValue(data->GetString());
			}
			break;

		default:
			handled = kFalse;
			break;
		}
		CmdUtils::EndCommandSequence(cmdSeq);

		return handled;
	}
	return kFalse;
}

//----------------------------------------------------------------------------------------
// This function will update the state of the PDF options widgets.

void AppearancePanelObserver::UpdatePDFOptionsWidgets()
{
	InterfacePtr<IFormFieldSuite> iFormFieldSuite(FormFieldUIUtils::QueryFormSuite());
	InterfacePtr<IPanelControlData> panelData(this, UseDefaultIID());

	// Description widget..
	IControlView* iDescriptionEditView = panelData->FindWidget(kButtonPDFDescriptionWID);
	if (iDescriptionEditView->IsVisible())
	{
		InterfacePtr<ITextControlData> data(iDescriptionEditView, UseDefaultIID());
		ASSERT(data != nil);

		PMString description;
		if (iFormFieldSuite)
			iFormFieldSuite->GetFormFieldDescription(description);
		data->SetString(description, kTrue, kFalse);
	}	

	// Printable Widget..
	IControlView* iPrintableCBView = panelData->FindWidget(kButtonPDFPrintableCheckBoxWID);
	if (iPrintableCBView->IsVisible())
	{
		InterfacePtr<ITriStateControlData> data(iPrintableCBView, UseDefaultIID());
		ASSERT(data != nil);

		if(iPrintableCBView->IsEnabled())
		{
			bool16 isMixed = kFalse;
			bool16 isPrintable = iFormFieldSuite && iFormFieldSuite->GetIsPrintable(isMixed);
			if (!isMixed && isPrintable)
				data->Select(kTrue, kFalse);
			else if (isMixed)
				data->SetUnknown(kTrue, kFalse);
			else
				data->Deselect(kTrue, kFalse);
		}
		else
			data->Deselect(kTrue, kFalse);	// Show as Deselected in case its not enabled.
	}

	// ReadOnly Widget..
	IControlView* iReadOnlyCBView = panelData->FindWidget(kReadOnlyCheckBoxWidgetID);
	if (iReadOnlyCBView->IsVisible())
	{
		InterfacePtr<ITriStateControlData> data(iReadOnlyCBView, UseDefaultIID());
		ASSERT(data != nil);

		bool16 isMixed = kFalse;
		bool16 isReadOnly = iFormFieldSuite && iFormFieldSuite->GetIsReadOnly(isMixed);
		if (!isMixed && isReadOnly)
			data->Select(kTrue, kFalse);
		else if (isMixed)
			data->SetUnknown(kTrue, kFalse);
		else
			data->Deselect(kTrue, kFalse);
	}

	// Required Widget..
	IControlView* iRequiredCBView = panelData->FindWidget(kRequiredCheckBoxWidgetID);
	if (iRequiredCBView->IsVisible())
	{
		InterfacePtr<ITriStateControlData> data(iRequiredCBView, UseDefaultIID());
		ASSERT(data != nil);

		bool16 isMixed = kFalse;
		bool16 isRequired = iFormFieldSuite && iFormFieldSuite->GetIsRequired(isMixed);
		if (!isMixed && isRequired)
			data->Select(kTrue, kFalse);
		else if (isMixed)
			data->SetUnknown(kTrue, kFalse);
		else
			data->Deselect(kTrue, kFalse);
	}

	// Selected by default Widget..
	IControlView* iSelectedByDefaultCBView = panelData->FindWidget(kSelectedByDefaultCheckBoxWidgetID);
	if (iSelectedByDefaultCBView->IsVisible())
	{
		InterfacePtr<ITriStateControlData> data(iSelectedByDefaultCBView, UseDefaultIID());
		ASSERT(data != nil);

		bool16 isMixed = kFalse;
		bool16 isSelectedByDefault = iFormFieldSuite && iFormFieldSuite->GetIsSelectedByDefault(isMixed);
		if (!isMixed && isSelectedByDefault)
			data->Select(kTrue, kFalse);
		else if (isMixed)
			data->SetUnknown(kTrue, kFalse);
		else
			data->Deselect(kTrue, kFalse);
	}

	// MultiLine Text Field Widget..
	IControlView* iMultiLineCBView = panelData->FindWidget(kMultilineCheckBoxWidgetID);
	if (iMultiLineCBView->IsVisible())
	{
		InterfacePtr<ITriStateControlData> data(iMultiLineCBView, UseDefaultIID());
		ASSERT(data != nil);
	
		bool16 isMixed = kFalse;
		bool16 isMultiline = iFormFieldSuite && iFormFieldSuite->GetIsMultiLineTextField(isMixed);
		if (!isMixed && isMultiline)
			data->Select(kTrue, kFalse);
		else if (isMixed)
			data->SetUnknown(kTrue, kFalse);
		else
			data->Deselect(kTrue, kFalse);
	}

	// Password Text Field Widget..
	IControlView* iPasswordCBView = panelData->FindWidget(kPasswordCheckBoxWidgetID);
	if (iPasswordCBView->IsVisible())
	{
		InterfacePtr<ITriStateControlData> data(iPasswordCBView, UseDefaultIID());
		ASSERT(data != nil);

		bool16 isMixed = kFalse;
		bool16 isPassword = iFormFieldSuite && iFormFieldSuite->GetIsPasswordTextField(isMixed);
		if (!isMixed && isPassword)
			data->Select(kTrue, kFalse);
		else if (isMixed)
			data->SetUnknown(kTrue, kFalse);
		else
			data->Deselect(kTrue, kFalse);
	}

	// Scrollable Text Field Widget..
	IControlView* iScrollableCBView = panelData->FindWidget(kScrollableCheckBoxWidgetID);
	if (iScrollableCBView->IsVisible())
	{
		InterfacePtr<ITriStateControlData> data(iScrollableCBView, UseDefaultIID());
		ASSERT(data != nil);

		bool16 isMixed = kFalse;
		bool16 isScrollable = iFormFieldSuite && iFormFieldSuite->GetIsScrollableTextField(isMixed);
		if (!isMixed && isScrollable)
			data->Select(kTrue, kFalse);
		else if (isMixed)
			data->SetUnknown(kTrue, kFalse);
		else
			data->Deselect(kTrue, kFalse);
	}

	IControlView* iMultipleSelectionCBView = panelData->FindWidget(kMultipleSelectionCheckBoxWidgetID);
	if (iMultipleSelectionCBView->IsVisible())
	{
		InterfacePtr<ITriStateControlData> data(iMultipleSelectionCBView, UseDefaultIID());
		ASSERT(data != nil);

		bool16 isMixed = kFalse;
		bool16 isMultipleSelection = iFormFieldSuite && iFormFieldSuite->GetIsMultipleSelectionEnabled(isMixed);
		if (!isMixed && isMultipleSelection)
			data->Select(kTrue, kFalse);
		else if (isMixed)
			data->SetUnknown(kTrue, kFalse);
		else
			data->Deselect(kTrue, kFalse);
	}

	IControlView* iFontSizeView = panelData->FindWidget(kFontSizeEditBoxWidgetID);
	if (iFontSizeView->IsVisible())
	{
		PMReal fontSize;
		bool16 isValid = kFalse;
		if (iFormFieldSuite)
			isValid = iFormFieldSuite->GetTextSizeAttribute(fontSize);

		if (isValid)
		{
			InterfacePtr<ITextValue> textValue(iFontSizeView, IID_ITEXTVALUE);
			ASSERT(textValue != nil);
			textValue->SetTextFromValue(fontSize, kTrue, kFalse);
		}
	}

	PMString fontStyle,fontFamily;
    bool16 isFontStyleValid(kFalse), isFontFamilyValid(kFalse);
	if (iFormFieldSuite)
	{
        isFontStyleValid = iFormFieldSuite->GetFontStyleAttribute(fontStyle);
		isFontFamilyValid = iFormFieldSuite->GetFontFamilyAttribute(fontFamily);
	}
	
	if (!(fontFamily.IsEmpty() || fontStyle.IsEmpty()))
	{
		FillOutFontAttributes(panelData, fontFamily, fontStyle, isFontFamilyValid, isFontStyleValid);
	}
	
	IControlView* iSortItemsCBView = panelData->FindWidget(kSortItemsCheckBoxWidgetID);
	if (iSortItemsCBView->IsVisible())
	{
		InterfacePtr<ITriStateControlData> data(iSortItemsCBView, UseDefaultIID());
		ASSERT(data != nil);

		bool16 isMixed = kFalse;
		bool16 isSorted = iFormFieldSuite && iFormFieldSuite->GetShouldSortListItems(isMixed);
		if (!isMixed && isSorted)
			data->Select(kTrue, kFalse);
		else if (isMixed)
			data->SetUnknown(kTrue, kFalse);
		else
			data->Deselect(kTrue, kFalse);
	}

	IControlView* iMERTLCBView = panelData->FindWidget(kMERTLOptionCheckBoxWidgetID);
	if (iMERTLCBView->IsVisible())
	{
		InterfacePtr<ITriStateControlData> data(iMERTLCBView, UseDefaultIID());
		ASSERT(data != nil);

		bool16 isMixed = kFalse;
		bool16 isRTL = iFormFieldSuite && iFormFieldSuite->GetIsMERTLEnabled(isMixed);
		if (!isMixed && isRTL)
			data->Select(kTrue, kFalse);
		else if (isMixed)
			data->SetUnknown(kTrue, kFalse);
		else
			data->Deselect(kTrue, kFalse);
	}

	IControlView* iExportValueEditView = panelData->FindWidget(kExportValueEditWidgetID);
	if (iExportValueEditView->IsVisible())
	{
		InterfacePtr<ITextControlData> data(iExportValueEditView, UseDefaultIID());
		ASSERT(data != nil);

		PMString exportValue;
		if (iFormFieldSuite)
			iFormFieldSuite->GetExportValue(exportValue);

		data->SetString(exportValue, kTrue, kFalse);
	}	
}

void AppearancePanelObserver::FillOutFontAttributes(IPanelControlData* panelData,const PMString& fontFamilyName, const PMString& fontStyleName, const bool16 isFontFamilyValid, const bool16 isFontStyleValid)
{
	IControlView* familyWidgetView = panelData->FindWidget(kFormFontFamilyWidgetID);
	IControlView* styleWidgetView = panelData->FindWidget(kFormFontStyleWidgetID);
	PMString familyName(fontFamilyName), styleName(fontStyleName);
	InterfacePtr<IStringListControlData> familyListData(familyWidgetView, UseDefaultIID());
	InterfacePtr<IStringListControlData> styleListData(styleWidgetView, UseDefaultIID());
	familyListData->Clear();
	styleListData->Clear();
	InterfacePtr<IFontUtilData> fontutilData(GetExecutionContextSession(), UseDefaultIID());
    // if font does not exist in util data, then invalidate its cache. it fixes the bug ID-4210382
    if (!fontutilData->IsFontStyleAvailable(fontFamilyName, fontStyleName))
        fontutilData->InvalidateFontCacheData();
    
	std::vector<PMString> families;
    fontutilData->GetFontFamiliesList(families);
	if (familyListData && familyListData->Length() == 0)
	{
		for (size_t i = 0; i < families.size(); i++)
			familyListData->AddString(families[i], IStringListControlData::kEnd, kFalse, kFalse);
	}

	int32 familyIndex = -1, styleIndex = -1;
	familyIndex = familyName.CharCount() > 0 ? familyListData->GetIndex(familyName) : familyIndex;

    //if family or style is missing, then show the family/style name in square brackets
    if (familyIndex == -1)
	{
		AddBracketsAroundString(familyName);
		familyIndex = familyName.CharCount() > 0 ? familyListData->GetIndex(familyName) : familyIndex;
	}
	std::vector<PMString> styles;
	fontutilData->GetStylesInFontFamily(familyName, styles);
	bool16 addSeparatorInStyles = kTrue;
	for (size_t i = 0; i < styles.size(); i++)
	{
		if (addSeparatorInStyles && styles[i][0] == kTextChar_LeftSquareBracket)
		{
			styleListData->AddString("-", IStringListControlData::kEnd, kFalse, kFalse);
			addSeparatorInStyles = kFalse;
		}
		styleListData->AddString(styles[i], IStringListControlData::kEnd, kFalse, kFalse);
	}
	styleIndex = styleName.CharCount() > 0 ? styleListData->GetIndex(styleName) : styleIndex;
	if (styleIndex == -1)
	{
		AddBracketsAroundString(styleName);
		styleIndex = styleName.CharCount() > 0 ? styleListData->GetIndex(styleName) : styleIndex;
	}

    if(!isFontFamilyValid) {
        familyName = PMString("");
        familyIndex = IDropDownListController::kNoSelection;
        styleListData->Clear();
        if(isFontStyleValid)
            styleListData->AddString(styleName, IStringListControlData::kEnd, kFalse, kFalse);
    }
    if(!isFontStyleValid) {
        styleName = PMString("");
        styleIndex = IDropDownListController::kNoSelection;
    }
    
    InterfacePtr<IDropDownListController> familyDDLController(familyListData, UseDefaultIID());
    InterfacePtr<IDropDownListController> styleDDLController(styleListData, UseDefaultIID());
	InterfacePtr<ITextControlData> familyData(familyDDLController, UseDefaultIID());
	ASSERT(familyData != nil);
	familyData->SetString(familyName, kTrue, kFalse);
	InterfacePtr<ITextControlData> styleData(styleDDLController, UseDefaultIID());
	ASSERT(styleData != nil);
	styleData->SetString(styleName, kTrue, kFalse);
	familyDDLController->Select(familyIndex, kTrue, kFalse);
	styleDDLController->Select(styleIndex, kTrue, kFalse);
}

//missing style name is displayed as [Name]
//this function add brackets around name
void AppearancePanelObserver::AddBracketsAroundString(PMString& name)
{
	if (!name.IsEmpty())
	{
		//Do not add further brackets if name aready has bracket around it
		if (name[0] != kTextChar_LeftSquareBracket)
		{
			name.InsertW(kTextChar_LeftSquareBracket);
			name.AppendW(kTextChar_RightSquareBracket);
		}
		name.SetTranslatable(kFalse);
	}
}
