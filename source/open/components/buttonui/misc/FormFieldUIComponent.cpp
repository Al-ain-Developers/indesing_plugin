//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/misc/FormFieldUIComponent.cpp $
//  
//  Owner: Tim Wright
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
//  Adapted from GroupComponent.h
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IActionManager.h"
#include "IActionMenuManager.h"
#include "IActionStateList.h"
#include "IActiveContext.h"
#include "IAnimationBehaviorData.h"
#include "IAppearanceItemFacade.h"
#include "IAppearanceSuite.h"
#include "IApplication.h"
#include "IBehaviorData.h"
#include "IBehaviorSuite.h"
#include "IDialog.h"
#include "IDialogCreator.h"
#include "IDocument.h"
#include "IDropDownListController.h"
#include "IDynamicTargetsFacade.h"
#include "IFormFieldSuite.h"
#include "IIntData.h"
#include "IUIDData.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "ILayoutControlData.h"
#include "IListControlDataOf.h"
#include "IMovieActionData.h"
#include "IMultiStateObjectBehaviorData.h"
#include "IPanelControlData.h"
#include "IPanelDetailController.h"
#include "IPanelMgr.h"
#include "ISelectionDataSuite.h"
#include "ISelectableDialogSwitcher.h"
#include "ISoundActionData.h"
#include "ISpreadFieldOrder.h"
#include "IWidgetParent.h"
#include "IWidgetUtils.h"
#include "IWorkspace.h"

// ----- Includes -----

#include "BehaviorTypes.h"
#include "CActionComponent.h"
#include "CAlert.h"
#include "FormFieldTypes.h"
#include "FormFieldUIDefs.h"
#include "InterfacePtr.h"
#include "K2Pair.h"
#include "K2SmartPtr.h"
#include "UIDList.h"

// ----- Utility files -----

#include "AttributesUtils.h"
#include "CmdUtils.h"
#include "EventUtilities.h"
#include "FormFieldUIUtils.h"
#include "ILayoutUIUtils.h"
#include "IPageItemUtils.h"
#include "IPalettePanelUtils.h"
#include "ISelectionUtils.h"
#include "SelectionUtils.h"
#include "UIDListUtils.h"
#include "UserInterfaceUtils.h"

// ----- ID.h files -----

#include "BehaviorID.h"
#include "BehaviorUIID.h"
#include "FormFieldID.h"
#include "FormFieldUIID.h"


using namespace UserInterfaceUtils;
using namespace AttributesUtils;

// ----------------------------------------------------------------------------------------

class ICommand;
class UIDList;

class FormFieldUIComponent : public CActionComponent
{
public:
	FormFieldUIComponent(IPMUnknown *boss) : CActionComponent(boss) {}

	void UpdateActionStates(IActiveContext* ac, IActionStateList *actionList, GSysPoint mousePoint, IPMUnknown* widget);
	void DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);

private:
	void AddBehavior(ActionID inActionID, IPMUnknown* widget, int32 behavior);
	IBehaviorData* QuerySelectedBehaviorData(int32 actionType) const;
	IUIDData* QueryAction(const IPanelControlData* buttonsPanel, const int32& action);

};

// ----------------------------------------------------------------------------------------

CREATE_PMINTERFACE(FormFieldUIComponent, kFormFieldUIComponentImpl)

// ----------------------------------------------------------------------------------------
// Enable menu items based on selection...

void FormFieldUIComponent::UpdateActionStates(IActiveContext* ac, IActionStateList *inListToUpdate, GSysPoint mousePoint, IPMUnknown* widget)
{
	InterfacePtr<IFormFieldSuite> iFormSuite( FormFieldUIUtils::QueryFormSuite() );
	InterfacePtr<IAppearanceSuite> iAppearanceSuite( SelectionUtils::QuerySuite<IAppearanceSuite>());

	bool enable = false;
	int32 count = inListToUpdate->Length();
	
	while( count-- )
	{
		ActionID action = inListToUpdate->GetNthAction(count);
		switch( action.Get() )
		{
			case kGoToFirstPageBehaviorActionID:
			case kGoToAnchorBehaviorActionID:
			case kGoToLastPageBehaviorActionID:
			case kGoToNextPageBehaviorActionID:
			case kGoToNextViewBehaviorActionID:
			case kGoToPreviousPageBehaviorActionID:
			case kGoToPreviousViewBehaviorActionID:
			case kGoToURLBehaviorActionID:
			case kMovieBehaviorActionID:
			case kOpenFileBehaviorActionID:
			case kShowHideBehaviorActionID:
			case kSoundBehaviorActionID:
			case kViewZoomBehaviorActionID:
			case kPrintFormBehaviorActionID:
			case kResetFormBehaviorActionID:
			case kSubmitFormBehaviorActionID:
			{
				// The above actions can be applied to all form fields as well as buttons.
				bool isFormField = iFormSuite && (iFormSuite->IsFieldSelection());

				// Also enable the actions if the selection is a single object (not a form field), which can be converted to a button..
				InterfacePtr<const ISelectionDataSuite> iSelectionDataSuite (static_cast<ISelectionDataSuite*>(Utils<ISelectionUtils>()->QuerySuite (IID_ISELECTIONDATASUITE, ac->GetContextSelection())));
				bool isSingleSelection = iSelectionDataSuite && iSelectionDataSuite->GetSelectionCount() == 1;
				bool ConvertibleToButton = !isFormField && isSingleSelection && iFormSuite && iFormSuite->CanCreateFieldFromSelection(kPushButtonItemBoss);

				enable =  isFormField || ConvertibleToButton;

				// Indent the action's name by prepending a couple of space characters. 
				// Doing in code instead of the resource per request to avoid localization mistakes and costs.
				InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
				InterfacePtr<IActionManager> actionMgr(app->QueryActionManager());
				PMString actionName(actionMgr->GetActionName(action));
				if ( actionName.NumUTF16TextChars() < 2 || 
					(actionName.GetWChar(0) != kTextChar_Space || actionName.GetWChar(1) != kTextChar_Space) )
				{
					actionName.Translate();
					actionName.InsertW(kTextChar_Space);
					actionName.InsertW(kTextChar_Space);
					actionName.SetTranslatable(kFalse);
					inListToUpdate->SetNthActionName(count, actionName);
				}
				break;
			}

			case kAnimationBehaviorActionID:
			case kGoToPageBehaviorActionID:
			case kSwitchToMSOStateBehaviorActionID:
			case kSwitchToNextMSOStateBehaviorActionID:
			case kSwitchToPrevMSOStateBehaviorActionID:
			{
				// These Actions should be enabled only for Push buttons..
				
				bool isButton = ( iFormSuite && iFormSuite->IsFieldSelectionOfType(kPushButtonItemBoss) && iAppearanceSuite && iAppearanceSuite->NumStates() );

				// Also enable the actions if the selection is a single object (not a form field), which can be converted to a button..
				InterfacePtr<const ISelectionDataSuite> iSelectionDataSuite (static_cast<ISelectionDataSuite*>(Utils<ISelectionUtils>()->QuerySuite (IID_ISELECTIONDATASUITE, ac->GetContextSelection())));
				bool isSingleSelection = iSelectionDataSuite && iSelectionDataSuite->GetSelectionCount() == 1;
				bool ConvertibleToButton = isSingleSelection && iFormSuite && 
					(!iFormSuite->IsFieldSelection() || iFormSuite->IsFieldSelectionOfType(kMultiStateObjectItemBoss)) && 
					iFormSuite->CanCreateFieldFromSelection(kPushButtonItemBoss);

				enable = isButton || ConvertibleToButton;

				// Indent the action's name by prepending a couple of space characters. 
				// Doing in code instead of the resource per request to avoid localization mistakes and costs.
				InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
				InterfacePtr<IActionManager> actionMgr(app->QueryActionManager());
				PMString actionName(actionMgr->GetActionName(action));
				if ( actionName.NumUTF16TextChars() < 2 || 
					(actionName.GetWChar(0) != kTextChar_Space || actionName.GetWChar(1) != kTextChar_Space) )
				{
					actionName.Translate();
					actionName.InsertW(kTextChar_Space);
					actionName.InsertW(kTextChar_Space);
					actionName.SetTranslatable(kFalse);
					inListToUpdate->SetNthActionName(count, actionName);
				}
				break;
			}
			
			case kCreateButtonActionID:
				if ( iFormSuite ) {
					bool16 doWarnNonEmptyStates = kFalse;
					inListToUpdate->SetNthActionName(count,"$$$/Menu/CreateButton");
					if ( iFormSuite->CanCreateFieldFromSelection(kPushButtonItemBoss) ) 
						enable = true;
					else 
						enable = false;
				}
				break;

			case kTextFieldToolActionID:
				if ( iFormSuite ) {
					bool16 doWarnNonEmptyStates = kFalse;
					inListToUpdate->SetNthActionName(count,"$$$/Menu/CreateTextField");
					if ( iFormSuite->CanCreateFieldFromSelection(kTextFieldItemBoss) )
						enable = true;
					else 
						enable = false;
				}
				break;

			case kCheckBoxToolActionID:
				if ( iFormSuite ) {
					bool16 doWarnNonEmptyStates = kFalse;
					inListToUpdate->SetNthActionName(count,"$$$/Menu/CreateCheckBox");
					if ( iFormSuite->CanCreateFieldFromSelection(kCheckBoxItemBoss ))
						enable = true;
					else 
						enable = false;
				}
				break;

			case kComboBoxToolActionID:
				if ( iFormSuite ) {
					bool16 doWarnNonEmptyStates = kFalse;
					inListToUpdate->SetNthActionName(count,"$$$/Menu/CreateComboBox");
					if ( iFormSuite->CanCreateFieldFromSelection(kComboBoxItemBoss ) )
						enable = true;
					else 
						enable = false;
				}
				break;

			case kListBoxToolActionID:
				if ( iFormSuite ) {
					bool16 doWarnNonEmptyStates = kFalse;
					inListToUpdate->SetNthActionName(count,"$$$/Menu/CreateListBox");
					if ( iFormSuite->CanCreateFieldFromSelection(kListBoxFieldItemBoss )) 
						enable = true;
					else 
						enable = false;
				}
				break;

			case kRadioButtonToolActionID:
				if ( iFormSuite ) {
					bool16 doWarnNonEmptyStates = kFalse;
					inListToUpdate->SetNthActionName(count,"$$$/Menu/CreateRadioButton");
					if ( iFormSuite->CanCreateFieldFromSelection(kRadioButtonItemBoss ) ) 
						enable = true;
					else 
						enable = false;
				}
				break;

			case kSignatureFieldToolActionID:
				if ( iFormSuite ) {
					bool16 doWarnNonEmptyStates = kFalse;
					inListToUpdate->SetNthActionName(count,"$$$/Menu/CreateSignatureField");
					if ( iFormSuite->CanCreateFieldFromSelection(kSignatureFieldItemBoss ) ) 
						enable = true;
					else 
						enable = false;
				}
				break;


			case kFormFieldPropertiesActionID:
			case kFormFieldProperties2ActionID:
				enable = iFormSuite && iFormSuite->CanEditFieldSelection() && !iFormSuite->IsDefaultSelection();
				break;

			case kSetTabOrderActionID:
			{
				IDocument* document = Utils<ILayoutUIUtils>()->GetFrontDocument();
				if (!document)
					break;
				
				InterfacePtr<IControlView> layoutView( Utils<ILayoutUIUtils>()->QueryFrontView() );
				InterfacePtr<ILayoutControlData> layoutData(layoutView, IID_ILAYOUTCONTROLDATA);
				if (!layoutView || !layoutData)
					break;

				UID pageUID = layoutData->GetPage();
				if (pageUID == kInvalidUID )
					break;

				UID spreadUID = layoutData->GetSpreadRef().GetUID();
				if (spreadUID == kInvalidUID )
					break;

				InterfacePtr<ISpreadFieldOrder> iSpreadFieldOrder( UIDRef(::GetDataBase(document),spreadUID), ::UseDefaultIID() );				

				ASSERT_MSG(iSpreadFieldOrder, "Expected spread field order interface not found.");
				if (!iSpreadFieldOrder )
					break;

				ISpreadFieldOrder::TabOrder tabOrder = iSpreadFieldOrder->GetTabOrder( pageUID );

				enable = tabOrder.size() > 1;
			
				break;
			}	

/*				
			case kSetCalculationOrderActionID:
			{
				IDocument* document = Utils<ILayoutUIUtils>()->GetFrontDocument();
				if (!document)
					break;
					
				InterfacePtr<IDocumentFieldOrder> docFieldOrder( document, ::UseDefaultIID() );
				if (docFieldOrder)
				{
					IDocumentFieldOrder::CalculationOrder calculationOrder = docFieldOrder->GetCalculationOrder();
					enable = calculationOrder.size() > 1;
				}
			
				break;
			}
*/

			case kAboutFormFieldsActionID:
				enable = true;
				break;

			case kConvertToObjectToolActionID:
				if ( iFormSuite ) {
					// Show the "Convert to object" in the interactive menu in case of different type of fields are selected..
					bool16 doWarnNonEmptyStates = kFalse;
					inListToUpdate->SetNthActionName(count,"$$$/Menu/DestroyButton");
					if( iFormSuite->CanDestroyFieldFromSelection(doWarnNonEmptyStates) && iFormSuite->SelectionHasAnyFormFields())
						enable = true;
					else
						enable = false;
				}
				break;
		}
		
		if (enable)
			inListToUpdate->SetNthActionState( count, kEnabledAction );		
	}	
}

// ----------------------------------------------------------------------------------------

// Perform action for menu id.  Returns whether command was processed

void FormFieldUIComponent::DoAction(IActiveContext* ac, ActionID inActionID, GSysPoint mousePoint, IPMUnknown* widget)
{
	ICommandSequence* createButtoncmdSeq = nil;
	bool16 createButton = kFalse;

	switch (inActionID.Get())
	{
		case kGoToPageBehaviorActionID:
		case kGoToAnchorBehaviorActionID:
		case kGoToFirstPageBehaviorActionID:
		case kGoToLastPageBehaviorActionID:
		case kGoToNextPageBehaviorActionID:
		case kGoToNextViewBehaviorActionID:
		case kGoToPreviousPageBehaviorActionID:
		case kGoToPreviousViewBehaviorActionID:
		case kGoToURLBehaviorActionID:
		case kMovieBehaviorActionID:
		case kOpenFileBehaviorActionID:
		case kShowHideBehaviorActionID:
		case kSoundBehaviorActionID:
		case kViewZoomBehaviorActionID:
		case kAnimationBehaviorActionID:
		case kSwitchToMSOStateBehaviorActionID:
		case kSwitchToNextMSOStateBehaviorActionID:
		case kSwitchToPrevMSOStateBehaviorActionID:
		case kPrintFormBehaviorActionID:
		case kResetFormBehaviorActionID:
		case kSubmitFormBehaviorActionID:
		{
			// Actions will be enabled for all form fields, so just check that its a form field once..

			InterfacePtr<IFormFieldSuite> iFormFieldSuite(FormFieldUIUtils::QueryFormSuite());
			if ( iFormFieldSuite)
			{				
				// If this is a simple object on which we want to apply an action as well as convert to button, 
				// convert it to a button here first..
				if ( iFormFieldSuite && iFormFieldSuite->CanCreateFieldFromSelection(kPushButtonItemBoss) && 
					(!iFormFieldSuite->IsFieldSelection() || iFormFieldSuite->IsFieldSelectionOfType(kMultiStateObjectItemBoss)))
				{
					createButton = kTrue;
					createButtoncmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);

					iFormFieldSuite->CreateFieldFromSelection(kPushButtonItemBoss);	


					// Make sure the event menu is populated, sigh.
					// I'll need to do this only if I'm directly converting an object to a button. If its already a form field,
					// the menu would be populated just fine.
					InterfacePtr<IPanelControlData> panelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kAppearanceParentWidgetId));
					if (panelData)
					{
						InterfacePtr<IDropDownListController> eventChoice((IDropDownListController *) Utils<IWidgetUtils>()->QueryRelatedWidget(panelData, kButtonEventChoicesWidgetID, IID_IDROPDOWNLISTCONTROLLER));
						if (eventChoice)
						{
							InterfacePtr<IActionMenuManager> actionMenuMgr(GetExecutionContextSession(), UseDefaultIID());
							if (actionMenuMgr)
								actionMenuMgr->BuildEventMenuSupportingSelection(eventChoice, 0);
						}
					}
				}
			}
			break;
		}
	}

	switch (inActionID.Get())
	{

		case kAboutFormFieldsActionID:
		{
			InvokePlugInAboutBox("$$$/Dialog/About/Description");
			break;
		}
		
		//twright 02/08/2001 The dialog can handle new forms and existing forms...
		//This way we can specify properties for a new form item before it is created...

		//twright 06/05/2001 
		//Dialog is now for setting defaults and form properties of
		//existing forms only... Not used for creation any more...
	
		case kFormFieldPropertiesActionID:
		case kFormFieldProperties2ActionID:
		{
			InterfacePtr<IK2ServiceRegistry> serviceReg(GetExecutionContextSession(), IID_IK2SERVICEREGISTRY);
			InterfacePtr<IK2ServiceProvider> selectableDialogService(serviceReg->QueryServiceProviderByClassID(kSelectableDialogServiceImpl, kFormOptionsDialogBoss));
			InterfacePtr<IDialogCreator> dialogCreator(selectableDialogService, IID_IDIALOGCREATOR);
			IDialog* dialog = dialogCreator->CreateDialog();

			IControlView* dialogView = dialog->GetDialogPanel();
			InterfacePtr<ISelectableDialogSwitcher> dialogSwitcher2(dialogView, IID_ISELECTABLEDIALOGSWITCHER);
			dialogSwitcher2->SetDialogServiceID(kFormOptionsDialogService);
			dialogSwitcher2->SwitchDialogPanelByID(kFormFieldUIDialogWID);
					
			if (dialog != nil)
			{
				// Open causes the dialog to be displayed and then returns immediately
				//	so WaitForDialog() is used.
				dialog->Open();
				dialog->WaitForDialog();
			}

			break;
		}

		case kSetTabOrderActionID:
		{
			PresentModalDialog(kFormFieldUIPluginID, kTabOrderDialogRsrcID);
			break;
		}
		
//		case kSetCalculationOrderActionID:
//		{
//			PresentModalDialog(kFormFieldUIPluginID, kCalculationOrderDialogRsrcID);
//			break;
//		}
		
		case kCreateButtonActionID:
		{
			InterfacePtr<ISelectionManager>			iSelectMgr ( Utils<ISelectionUtils>()->QueryActiveSelection ());
			InterfacePtr<IFormFieldSuite>			iFormSuite (iSelectMgr, UseDefaultIID ());

			if (iFormSuite) {
				bool16 doWarnNonEmptyStates = kFalse;
				if ( iFormSuite->CanCreateFieldFromSelection(kPushButtonItemBoss))
				{
					ICommandSequence* cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);

					if( iFormSuite->SelectionHasAnyFormFields())
						iFormSuite->DestroyFieldFromSelection(kPushButtonItemBoss);

					iFormSuite->CreateFieldFromSelection(kPushButtonItemBoss);

					CmdUtils::EndCommandSequence(cmdSeq);
					InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
					InterfacePtr<IPanelMgr> iPanelMgr(app->QueryPanelManager());
					iPanelMgr->ShowPanelByMenuID(kAppearancePanelActionID);
				}
			}

			break;
		}

		case kTextFieldToolActionID:
			{
				InterfacePtr<ISelectionManager>			iSelectMgr ( Utils<ISelectionUtils>()->QueryActiveSelection ());
				InterfacePtr<IFormFieldSuite>			iFormSuite (iSelectMgr, UseDefaultIID ());

				if (iFormSuite) {
					bool16 doWarnNonEmptyStates = kFalse;
					if ( iFormSuite->CanCreateFieldFromSelection(kTextFieldItemBoss) )
					{
						ICommandSequence* cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
						cmdSeq->SetName( PMString("$$$/Command/TextField") );

						if( iFormSuite->SelectionHasAnyFormFields())
							iFormSuite->DestroyFieldFromSelection(kTextFieldItemBoss);
						
						iFormSuite->CreateFieldFromSelection(kTextFieldItemBoss);

						CmdUtils::EndCommandSequence(cmdSeq);

						InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
						InterfacePtr<IPanelMgr> iPanelMgr(app->QueryPanelManager());
						iPanelMgr->ShowPanelByMenuID(kAppearancePanelActionID);
					}
				}

				break;
			}

		case kCheckBoxToolActionID:
			{
				InterfacePtr<ISelectionManager>			iSelectMgr ( Utils<ISelectionUtils>()->QueryActiveSelection ());
				InterfacePtr<IFormFieldSuite>			iFormSuite (iSelectMgr, UseDefaultIID ());

				if (iFormSuite) {
					bool16 doWarnNonEmptyStates = kFalse;
					if ( iFormSuite->CanCreateFieldFromSelection(kCheckBoxItemBoss) )
					{
						ICommandSequence* cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
						cmdSeq->SetName( PMString("$$$/Command/CheckBox") );

						if( iFormSuite->SelectionHasAnyFormFields())
							iFormSuite->DestroyFieldFromSelection(kCheckBoxItemBoss);
												
						iFormSuite->CreateFieldFromSelection(kCheckBoxItemBoss);

						CmdUtils::EndCommandSequence(cmdSeq);
						InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
						InterfacePtr<IPanelMgr> iPanelMgr(app->QueryPanelManager());
						iPanelMgr->ShowPanelByMenuID(kAppearancePanelActionID);
					}
				}

				break;
			}

		case kComboBoxToolActionID:
			{
				InterfacePtr<ISelectionManager>			iSelectMgr ( Utils<ISelectionUtils>()->QueryActiveSelection ());
				InterfacePtr<IFormFieldSuite>			iFormSuite (iSelectMgr, UseDefaultIID ());

				if (iFormSuite) {
					bool16 doWarnNonEmptyStates = kFalse;
					if ( iFormSuite->CanCreateFieldFromSelection(kComboBoxItemBoss) )
					{
						ICommandSequence* cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
						cmdSeq->SetName( PMString("$$$/Command/ComboBox") );

						if( iFormSuite->SelectionHasAnyFormFields())
							iFormSuite->DestroyFieldFromSelection(kComboBoxItemBoss);
	
						iFormSuite->CreateFieldFromSelection(kComboBoxItemBoss);
						CmdUtils::EndCommandSequence(cmdSeq);

						InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
						InterfacePtr<IPanelMgr> iPanelMgr(app->QueryPanelManager());
						iPanelMgr->ShowPanelByMenuID(kAppearancePanelActionID);
					}
				}
				break;
			}

		case kListBoxToolActionID:
			{
				InterfacePtr<ISelectionManager>			iSelectMgr ( Utils<ISelectionUtils>()->QueryActiveSelection ());
				InterfacePtr<IFormFieldSuite>			iFormSuite (iSelectMgr, UseDefaultIID ());

				if (iFormSuite) {
					bool16 doWarnNonEmptyStates = kFalse;
					if ( iFormSuite->CanCreateFieldFromSelection(kListBoxFieldItemBoss) )
					{
						ICommandSequence* cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
						cmdSeq->SetName( PMString("$$$/Command/ListBox") );

						if( iFormSuite->SelectionHasAnyFormFields())
							iFormSuite->DestroyFieldFromSelection(kListBoxFieldItemBoss);
						
						iFormSuite->CreateFieldFromSelection(kListBoxFieldItemBoss);
						CmdUtils::EndCommandSequence(cmdSeq);

						InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
						InterfacePtr<IPanelMgr> iPanelMgr(app->QueryPanelManager());
						iPanelMgr->ShowPanelByMenuID(kAppearancePanelActionID);
					}
				}

				break;
			}

		case kRadioButtonToolActionID:
			{
				InterfacePtr<ISelectionManager>			iSelectMgr ( Utils<ISelectionUtils>()->QueryActiveSelection ());
				InterfacePtr<IFormFieldSuite>			iFormSuite (iSelectMgr, UseDefaultIID ());

				if (iFormSuite) {
					bool16 doWarnNonEmptyStates = kFalse;
					if ( iFormSuite->CanCreateFieldFromSelection(kRadioButtonItemBoss) )
					{
						ICommandSequence* cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
						cmdSeq->SetName( PMString("$$$/Command/RadioButton") );

						if( iFormSuite->SelectionHasAnyFormFields())
							iFormSuite->DestroyFieldFromSelection(kRadioButtonItemBoss);
						
						iFormSuite->CreateFieldFromSelection(kRadioButtonItemBoss);
						CmdUtils::EndCommandSequence(cmdSeq);

						InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
						InterfacePtr<IPanelMgr> iPanelMgr(app->QueryPanelManager());
						iPanelMgr->ShowPanelByMenuID(kAppearancePanelActionID);
					}
				}

				break;
			}

		case kSignatureFieldToolActionID:
		{
			InterfacePtr<ISelectionManager>			iSelectMgr ( Utils<ISelectionUtils>()->QueryActiveSelection ());
			InterfacePtr<IFormFieldSuite>			iFormSuite (iSelectMgr, UseDefaultIID ());

			if (iFormSuite) {
				bool16 doWarnNonEmptyStates = kFalse;
				if ( iFormSuite->CanCreateFieldFromSelection(kSignatureFieldItemBoss) )
				{
					ICommandSequence* cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
					cmdSeq->SetName( PMString("$$$/Command/SignatureField") );

					if( iFormSuite->SelectionHasAnyFormFields())
						iFormSuite->DestroyFieldFromSelection(kSignatureFieldItemBoss);

					iFormSuite->CreateFieldFromSelection(kSignatureFieldItemBoss);
					CmdUtils::EndCommandSequence(cmdSeq);

					InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
					InterfacePtr<IPanelMgr> iPanelMgr(app->QueryPanelManager());
					iPanelMgr->ShowPanelByMenuID(kAppearancePanelActionID);
				}
			}

			break;
		}

		case kConvertToObjectToolActionID:
		{
			InterfacePtr<ISelectionManager>			iSelectMgr ( Utils<ISelectionUtils>()->QueryActiveSelection ());
			InterfacePtr<IFormFieldSuite>			iFormSuite (iSelectMgr, UseDefaultIID ());

			if (iFormSuite) {
				bool16 doWarnNonEmptyStates = kFalse;
				if ( iFormSuite->CanDestroyFieldFromSelection(doWarnNonEmptyStates)  && iFormSuite->SelectionHasAnyFormFields()) 
				{
					if ( doWarnNonEmptyStates && !(::IsOptionAltKeyPressed()) ) {

						// Display a destroy warning dialog
						PMString alertStr("$$$/Dialog/FormFieldUI/DestroyAlert");
						int16 whatToDo = CAlert::ModalAlert(alertStr,
							kOKString, 
							kCancelString, 
							kNullString, 
							1,                        // pass in 1, 2, or 3 to make that button the default button or 0 for no default
							CAlert::eWarningIcon);

						// If they don't want to continue, then punt
						if ( whatToDo == 2 )
							break;
					}
					iFormSuite->DestroyFieldFromSelection();
				}
			}
			break;
		}

		case kGoToFirstPageBehaviorActionID:
		{
			AddBehavior(inActionID, widget, kGoToFirstPageBehavior);
			break;
		}
		case kGoToPageBehaviorActionID:
		{
			AddBehavior(inActionID, widget, kGoToPageBehavior);
			break;
		}
		case kGoToAnchorBehaviorActionID:
		{
			AddBehavior(inActionID, widget, kGoToAnchorBehavior);
			break;
		}
		case kGoToLastPageBehaviorActionID:
		{
			AddBehavior(inActionID, widget, kGoToLastPageBehavior);
			break;
		}
		case kGoToNextPageBehaviorActionID:
		{
			AddBehavior(inActionID, widget, kGoToNextPageBehavior);
			break;
		}
		case kGoToNextViewBehaviorActionID:
		{
			AddBehavior(inActionID, widget, kGoToNextViewBehavior);
			break;
		}
		case kGoToPreviousPageBehaviorActionID:
		{
			AddBehavior(inActionID, widget, kGoToPreviousPageBehavior);
			break;
		}
		case kGoToPreviousViewBehaviorActionID:
		{
			AddBehavior(inActionID, widget, kGoToPreviousViewBehavior);
			break;
		}
		case kGoToURLBehaviorActionID:
		{
			AddBehavior(inActionID, widget, kGoToURLBehavior);
			break;
		}
		case kMovieBehaviorActionID:
		{
			AddBehavior(inActionID, widget, kMovieBehavior);
			break;
		}
		case kOpenFileBehaviorActionID:
		{
			AddBehavior(inActionID, widget, kOpenFileBehavior);
			break;
		}
		case kShowHideBehaviorActionID:
		{
			AddBehavior(inActionID, widget, kShowHideFieldsBehavior);
			break;
		}
		case kSoundBehaviorActionID:
		{
			AddBehavior(inActionID, widget, kSoundBehavior);
			break;
		}
		case kViewZoomBehaviorActionID:
		{
			AddBehavior(inActionID, widget, kViewZoomBehavior);
			break;
		}

		case kAnimationBehaviorActionID:
			AddBehavior(inActionID, widget, kAnimationBehavior);
			break;

		case kSwitchToMSOStateBehaviorActionID:
			AddBehavior(inActionID, widget, kSwitchToMSOStateBehavior);
			break;

		case kSwitchToNextMSOStateBehaviorActionID:
			AddBehavior(inActionID, widget, kSwitchToNextMSOStateBehavior);
			break;

		case kSwitchToPrevMSOStateBehaviorActionID:
			AddBehavior(inActionID, widget, kSwitchToPrevMSOStateBehavior);
			break;

		case kResetFormBehaviorActionID:
			AddBehavior(inActionID, widget, kResetFormBehavior);
			break;

		case kSubmitFormBehaviorActionID:
			AddBehavior(inActionID, widget, kSubmitFormBehavior);
			break;

		case kPrintFormBehaviorActionID:
			AddBehavior(inActionID, widget, kPrintFormBehavior);
			break;
	}

	if(createButton)
		CmdUtils::EndCommandSequence(createButtoncmdSeq);
}

//----------------------------------------------------------------------------------------
// FormFieldUIComponent::QueryAction
//----------------------------------------------------------------------------------------
IUIDData* FormFieldUIComponent::QueryAction(const IPanelControlData* buttonsPanel, const int32& action)
{
	InterfacePtr<IPanelControlData> panels(buttonsPanel->FindWidget(kBehaviorsDataHolderWidgetID), IID_IPANELCONTROLDATA);
	for (int32 i = 0; i < panels->Length(); i++)
	{
		InterfacePtr<IIntData> behaviorId(panels->GetWidget(i), UseDefaultIID());		
		if (behaviorId && action == behaviorId->Get())
			return (IUIDData*) panels->GetWidget(i)->QueryInterface(IID_IUIDDATA);
	}
	
	return nil;
}

//----------------------------------------------------------------------------------------
// FormFieldUIComponent::QuerySelectedBehavior
//----------------------------------------------------------------------------------------

IBehaviorData* FormFieldUIComponent::QuerySelectedBehaviorData(int32 actionType) const
{
	//Get prototype action data for selected behavior type from the Behavior service.

	InterfacePtr<IK2ServiceRegistry> servReg(GetExecutionContextSession(), UseDefaultIID());
	int32 serviceCount = servReg->GetServiceProviderCount(kBehaviorService);
	
	for(int32 serviceIndex = 0; serviceIndex < serviceCount; serviceIndex++)
	{
		InterfacePtr<IK2ServiceProvider> provider(servReg->QueryNthServiceProvider(kBehaviorService, serviceIndex));
		InterfacePtr<IBehaviorData> actionData(provider, UseDefaultIID());
		if (actionData && actionData->GetAction() == actionType)
		{
			actionData->AddRef();
			return actionData;
		}
	}

	return nil;
}

void FormFieldUIComponent::AddBehavior(ActionID inActionID, IPMUnknown* widget, int32 actionID)
{	
	InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IPanelMgr> iPanelMgr(app->QueryPanelManager());
	iPanelMgr->ShowPanelByMenuID(kAppearancePanelActionID);
	InterfacePtr<IPanelControlData> panelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kAppearanceParentWidgetId));

	InterfacePtr<IDropDownListController> eventChoice(panelData->FindWidget(kButtonEventChoicesWidgetID), IID_IDROPDOWNLISTCONTROLLER);
	InterfacePtr< IListControlDataOf< K2Pair<PMString, int32> > > eventData(eventChoice, IID_ILISTCONTROLDATA);
	if ( eventData)
	{
		int32 eventChoiceIndex = eventChoice->GetSelected();
		if ( eventChoiceIndex >= 0 )
		{
			ActionEvent selectedEvent =  (*eventData)[eventChoiceIndex].second;

			InterfacePtr<IIntData> chosenAction(panelData,IID_IINTDATA);
			chosenAction->Set(actionID);
			
			InterfacePtr<IUIDData> panelActionData(QueryAction(panelData, actionID));
			if ( panelActionData )
				panelActionData->Set(UIDRef(nil, kInvalidUID));

			// grab the IBehaviorData for the subpanel associated with the selected action/behavior.  Each
			// behavior has its own IBehaviorData implementation, which we locate by iterating over the registered
			// behaviors until we find one whose ID matches actionID.
			InterfacePtr<IBehaviorData> actionData(QuerySelectedBehaviorData(actionID));
			InterfacePtr<IBehaviorSuite> actionSuite( SelectionUtils::QuerySuite<IBehaviorSuite>() );

			ICommandSequence* cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__); 

			// Add a new <event, action> pair to the button.
			UID newAction;
			actionSuite->AddAction(selectedEvent, actionData, newAction);
			
			// Default to the first target object for Animation, Sound, Video,
			// and the Multi-state Object actions.
			IDataBase* db(nil);
			std::vector< std::pair<ActionEvent, UID> > behaviors;			
			actionSuite->GetEventAndActions(db, behaviors);

			if (db != nil)
			{
				InterfacePtr<IBehaviorData> newActionData(db, newAction, UseDefaultIID());
				ASSERT(newActionData != nil);

				switch (actionID)
				{
				case kMovieBehavior:
					{
						std::vector<UID> itemList;
						if (Utils<Facade::IDynamicTargetsFacade> ()->GetTargetList (UIDRef (db, newActionData->GetOwner()), ISpreadDynamicContentMgr::kMovieItemType, itemList, true) && itemList.size() > 0)
						{
							InterfacePtr<IMovieActionData> movieData((IMovieActionData*)QuerySelectedBehaviorData(actionID));
							movieData->Copy(newActionData);
							movieData->SetMovie(itemList[0]);

							actionSuite->ReplaceAction(selectedEvent, newAction, movieData);
						}
					}
					break;

				case kSoundBehavior:
					{
						std::vector<UID> itemList;
						if (Utils<Facade::IDynamicTargetsFacade> ()->GetTargetList (UIDRef (db, newActionData->GetOwner()), ISpreadDynamicContentMgr::kSoundItemType, itemList, true) && itemList.size() > 0)
						{
							InterfacePtr<ISoundActionData> soundData((ISoundActionData*)QuerySelectedBehaviorData(actionID));
							soundData->Copy(newActionData);
							soundData->SetSound(itemList[0]);

							actionSuite->ReplaceAction(selectedEvent, newAction, soundData);
						}
					}
					break;

				case kAnimationBehavior:
					{
						std::vector<UID> itemList;
						if (Utils<Facade::IDynamicTargetsFacade> ()->GetTargetList (UIDRef (db, newActionData->GetOwner()), ISpreadDynamicContentMgr::kAnimationItemType, itemList, true) && itemList.size() > 0)
						{
							InterfacePtr<IAnimationBehaviorData> animationData((IAnimationBehaviorData*)QuerySelectedBehaviorData(actionID));
							animationData->Copy(newActionData);
							animationData->SetTarget(itemList[0]);

							actionSuite->ReplaceAction(selectedEvent, newAction, animationData);
						}
					}
					break;

				case kSwitchToMSOStateBehavior:
				case kSwitchToNextMSOStateBehavior:
				case kSwitchToPrevMSOStateBehavior:
					{
						std::vector<UID> itemList;
						if (Utils<Facade::IDynamicTargetsFacade> ()->GetTargetList (UIDRef (db, newActionData->GetOwner()), ISpreadDynamicContentMgr::kMultiStateItemType, itemList, true) && itemList.size() > 0)
						{
							InterfacePtr<IMultiStateObjectBehaviorData> msoData((IMultiStateObjectBehaviorData*)QuerySelectedBehaviorData(actionID));
							msoData->Copy(newActionData);
							msoData->SetTarget(itemList[0]);

							if (actionID == kSwitchToMSOStateBehavior)
							{
								// Default to the first state of the MSO
								ASSERT_MSG(Utils<Facade::IAppearanceItemFacade>()->GetNumStates(UIDRef(db, itemList[0])) > 0, "This multi-state object has NO states?");
								msoData->SetState(Utils<Facade::IAppearanceItemFacade>()->GetNthState(UIDRef(db, itemList[0]), 0));
							}

							actionSuite->ReplaceAction(selectedEvent, newAction, msoData);
						}
					}
					break;
				}
			}

			CmdUtils::EndCommandSequence(cmdSeq); 

			// store the UIDRef of the new action on an interface in the subpanel for the selected behavior.
			if ( panelActionData )
				panelActionData->Set(UIDRef(nil, newAction));
		}
	}
}

