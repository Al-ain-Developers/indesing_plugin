//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/appearancepanel/AppearancePanelMenuComp.cpp $
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
//  Based on LayerPanelMenuComponent.cpp in Layer Panel Project
//  SPAM Not actually hooked up to the palette yet...
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IActionStateList.h"
#include "IActiveContext.h"
#include "IAppearanceSuite.h"
#include "ICmdCollection.h"
#include "ICommand.h"
#include "IDialog.h"
#include "IDialogController.h"
#include "IDocument.h"
#include "IFormFieldSuite.h"
#include "IGraphicAttributeSuite.h"
#include "IGraphicStateUtils.h"
#include "IIntData.h"
#include "ILayoutControlData.h"
#include "IListBoxAttributes.h"
#include "INamedPageItemList.h"
#include "IPanelControlData.h"
#include "IPanelDetailController.h"
#include "IPlaceGun.h"
#include "ISession.h"

#include "FileUtils.h"
#include "IK2ServiceRegistry.h"
#include "LibraryProviderID.h"
#include "IK2ServiceProvider.h"
#include "ILibraryService.h"
#include "ILibraryCmdUtils.h"
#include "ILibraryCmdData.h"

// ----- Includes -----

#include "CActionComponent.h"
#include "CAlert.h"
#include "FormFieldUIDefs.h"
#include "UIDList.h"

// ----- Utility files -----

#include "AppearancePanelUtils.h"
#include "AttributesUtils.h"
#include "CmdUtils.h"
#include "EventUtilities.h"
#include "FormFieldUIUtils.h"
#include "IFormFieldUtils.h"
#include "ILayoutUIUtils.h"
#include "IPalettePanelUtils.h"
#include "PreferenceUtils.h"
#include "StringUtils.h"
#include "UserInterfaceUtils.h"

// ----- ID.h files -----

#include "FormFieldUIID.h"
#include "LayoutUIID.h"
#include "widgetid.h"

//========================================================================================
// CLASS AppearancePanelMenuComponent
//========================================================================================

class AppearancePanelMenuComponent : public CActionComponent
{
public:
	AppearancePanelMenuComponent(IPMUnknown *boss);
	
		virtual void	DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);
		virtual void	UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint, IPMUnknown*);

protected:
		virtual void	GetButtonLibrary(IDFile* buttonLibrary);
};

CREATE_PMINTERFACE(AppearancePanelMenuComponent, kAppearancePanelMenuComponentImpl)

//========================================================================================
// CLASS AppearancePanelMenuComponent
//========================================================================================

AppearancePanelMenuComponent::AppearancePanelMenuComponent(IPMUnknown *boss) :
	CActionComponent(boss)
{
}

void AppearancePanelMenuComponent::UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint, IPMUnknown*)
{
	int32 count = listToUpdate->Length();

	// Get a list of selected states and their UIDs

	PMString menuItemString;
	InterfacePtr<IPanelControlData> panelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kAppearanceParentWidgetId));
	if(!panelData)
		return;

	InterfacePtr<IPanelDetailController> detail(panelData,IID_ILISTBOXDETAILCONTROLLER);
	InterfacePtr<IGraphicAttributeSuite> iGfxAttrSuite ( Utils<IGraphicStateUtils>()->QueryActiveGraphicAttrSuite ());

	InterfacePtr<IFormFieldSuite> iFormSuite( FormFieldUIUtils::QueryFormSuite() );
	bool bIsPushButton = iFormSuite && iFormSuite->IsFieldSelectionOfType(kPushButtonItemBoss) && !iFormSuite->IsDefaultSelection();
	bool bIsFormField = iFormSuite && ( iFormSuite->IsFieldSelectionOfType(kCheckBoxItemBoss) || iFormSuite->IsFieldSelectionOfType(kRadioButtonItemBoss) ||
										iFormSuite->IsFieldSelectionOfType(kTextFieldItemBoss) || iFormSuite->IsFieldSelectionOfType(kListBoxFieldItemBoss) ||
										iFormSuite->IsFieldSelectionOfType(kComboBoxItemBoss) || iFormSuite->IsFieldSelectionOfType(kSignatureFieldItemBoss));

	while (count--)
	{
		ActionID action = listToUpdate->GetNthAction(count);
		
		switch (action.Get())
		{
			case kNewStateActionID:
			{
				if ( CanCreateNewState() )
					listToUpdate->SetNthActionState(count,kEnabledAction);
				break;
			}
				
			case kDeleteStateActionID:
			{
				K2Vector<int32> selectedItems;
				K2Vector<Form::AppearanceState>  selectedStates;
				GetSelectedStates(selectedItems, selectedStates, panelData);
				
				int32 numSelected = selectedItems.size();

				if(CanDeleteSelectedStates(panelData))
					listToUpdate->SetNthActionState(count,kEnabledAction);
				
				if (numSelected == 1)
					menuItemString = "$$$/Menu/DeleteState";
				else
					menuItemString = "$$$/Menu/DeleteStates";

				listToUpdate->SetNthActionName(count,menuItemString);
				break;
			}
			
			case kDeleteStateContentActionID:
			{
				K2Vector<int32> selectedItems;
				K2Vector<Form::AppearanceState>  selectedStates;
				GetSelectedStates(selectedItems, selectedStates, panelData);
				
				int32 numSelected = selectedItems.size();
				if ( HasStateContent(panelData) )
					listToUpdate->SetNthActionState(count,kEnabledAction);
				
				break;
			}
			
			case kPlaceIntoStateActionID:
			{
				K2Vector<int32> selectedItems;
				K2Vector<Form::AppearanceState>  selectedStates;
				GetSelectedStates(selectedItems, selectedStates, panelData);
				
				int32 numSelected = selectedItems.size();
				if ( numSelected == 1 ) {
					
					// Check if the place gun is not already loaded
					InterfacePtr<IPlaceGun> placeGun(ac->GetContextDocument(), UseDefaultIID());
					if ( !placeGun || !placeGun->IsLoaded() ) {
						listToUpdate->SetNthActionState(count,kEnabledAction);
					}
				}
				
				break;
			}

			case kStatePropertiesActionID:
			{
				InterfacePtr<IAppearanceSuite> iAppearanceSuite( FormFieldUIUtils::QueryAppearanceSuite() );
				if (iAppearanceSuite &&  CanDoStatePropertiesDialog(iAppearanceSuite->GetActiveState()))
					listToUpdate->SetNthActionState(count,kEnabledAction);
				break;
			}

			case kAppearancePalettePrefsActionID:
				listToUpdate->SetNthActionState(count,kEnabledAction);
				break;

			case kOpenButtonLibraryActionID:
			{
				IDFile buttonLibrary;
				GetButtonLibrary(&buttonLibrary);
				if(FileUtils::DoesFileExist(buttonLibrary))
					listToUpdate->SetNthActionState(count,kEnabledAction);
				break;
			}

			case kButtonPDFOptionsActionID:
			{
				if ( listToUpdate->GetNthActionState(count) != kEnabledAction )
				{
					// enable if it is a button
					if ( bIsPushButton || bIsFormField )
						listToUpdate->SetNthActionState(count, kEnabledAction);
				}
				else if ( !bIsPushButton && !bIsFormField) // disable if not a button
					listToUpdate->SetNthActionState(count, kDisabled_Unselected);
				break;
			}

			case kResetAllButtonsActionID:
			{
				int16 state = kDisabled_Unselected;

				IDocument* doc = ac->GetContextDocument();
				if (doc)
				{
					InterfacePtr<INamedPageItemList> namedPageItems(doc, IID_IFORMPAGEITEMLIST);
					if (namedPageItems)
					{
						IDataBase *db = ::GetDataBase(doc);
						K2Vector<UID> forms = namedPageItems->Get();

						for (K2Vector<UID>::iterator i = forms.begin(); i != forms.end(); i++) 
						{
							if (db->GetClass(*i) == kPushButtonItemBoss)
							{
								InterfacePtr<IAppearanceList> appearanceList(db, *i, UseDefaultIID());
								if (appearanceList && appearanceList->GetActiveState() != appearanceList->GetNthState(Form::kStateNormal))
								{
									state = kEnabledAction;
									break;
								}
							}
						}
					}
				}
				listToUpdate->SetNthActionState(count, state);
				break;
			}
		}
	}
}

void AppearancePanelMenuComponent::DoAction(IActiveContext* ac, ActionID id, GSysPoint mousePoint, IPMUnknown* widget)
{
	
	InterfacePtr<IPanelControlData> panelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kAppearanceParentWidgetId));

	switch (id.Get())
	{
		case kNewStateActionID:
		{
			CreateNewState();
			break;
		}
						
		case kDeleteStateActionID:
		{
			// Check if the Alt/Option key is down
			bool16 optionKeyDown = ::IsOptionAltKeyPressed();
			if ( !optionKeyDown && HasStateContent(panelData) ) {
				
				// Display a delete warning dialog
		        PMString alertStr("$$$/Dialog/FormFieldUI/DeleteAlert");
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
			
			if ( panelData )
				DeleteSelectedStates(panelData);
			break;
		}
		
		case kDeleteStateContentActionID:
		{
			// Check if the Alt/Option key is down
			bool16 optionKeyDown = ::IsOptionAltKeyPressed();
			if ( !optionKeyDown ) {
				
				// Display a delete warning dialog
		        PMString alertStr("$$$/Dialog/FormFieldUI/DeleteContentAlert");
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
			
			if ( panelData )
				DeleteSelectedStateContent(panelData);
			break;
		}
		
		case kPlaceIntoStateActionID:
		{
			if ( panelData )
				PlaceIntoSelectedState(panelData);
			break;
		}

		case kStatePropertiesActionID:
		{
			InterfacePtr<IAppearanceSuite> iAppearanceSuite( FormFieldUIUtils::QueryAppearanceSuite() );
			if (iAppearanceSuite)
				DoStatePropertiesDialog(iAppearanceSuite->GetActiveState() );
			break;
		}

		case kAppearancePalettePrefsActionID:
		{
			if ( panelData ) {
				
				IDialog* dialog = UserInterfaceUtils::GetModalDialog( kFormFieldUIPluginID, kAppearancePanelPrefsDialogRsrcID );
			
				IControlView* dialogView = dialog->GetDialogPanel();
				InterfacePtr<IDialogController> iDialogController(dialogView, IID_IDIALOGCONTROLLER);
				InterfacePtr<IIntData> iThumbSizeIndex( iDialogController, IID_IINTDATA );

				IControlView* layerPanel = panelData->FindWidget(kAppearanceParentWidgetId);
				InterfacePtr<IPanelDetailController> detail(layerPanel, IID_ILISTBOXDETAILCONTROLLER);
				if (detail)
				{
					// DJB: iThumbSizeIndex is 1 based, but IPanelDetailController is zero based
					iThumbSizeIndex->Set( detail->GetDetailLevel() + 1);
					dialog->Open();
					dialog->WaitForDialog();
					detail->ShowDetailLevel(iThumbSizeIndex->Get() - 1);
				}
			}

			break;
		}

		case kOpenButtonLibraryActionID:
		{
			IDFile buttonLibrary;
			GetButtonLibrary(&buttonLibrary);
			ASSERT(FileUtils::DoesFileExist(buttonLibrary));
			//open the library
			InterfacePtr<IK2ServiceRegistry> registry(GetExecutionContextSession(), IID_IK2SERVICEREGISTRY); 
			InterfacePtr<IK2ServiceProvider> service(registry->QueryDefaultServiceProvider(kLibraryServiceID)); 
			InterfacePtr<ILibraryService> libraryService(service, IID_ILIBRARYSERVICE); 
			InterfacePtr<ILibraryCmdUtils> libraryCmdUtils(libraryService->QueryLibraryCmdUtils()); 
			InterfacePtr<ICommand> cmd(libraryCmdUtils->CreateLibraryOpenLibCmd(buttonLibrary)); 
			InterfacePtr<ILibraryCmdData> data(cmd, IID_ILIBRARYCMDDATA); 
			CmdUtils::ProcessCommand(cmd); 
			break;
		}


		case kButtonPDFOptionsActionID:
		{

			IDialog* dialog = UserInterfaceUtils::GetModalDialog( kFormFieldUIPluginID, kButtonPDFOptionsDialogRsrcID );
			if (dialog)
			{
				dialog->Open();
				dialog->WaitForDialog();
			}
			break;
		}

		case kResetAllButtonsActionID:
		{
			IDocument* doc = ac->GetContextDocument();
			if (doc)
				Utils<IFormFieldUtils>()->ResetAllButtons(::GetUIDRef(doc));
			break;
		}


	}
}

void AppearancePanelMenuComponent::GetButtonLibrary(IDFile* buttonLibrary)
{
	PMString fileName("$$$/SampleButtonsLibary", PMString::kTranslateDuringCall);
	PMString subFolder("button library");
	FileUtils::GetPresetsFolder(buttonLibrary,subFolder,PMLocaleId());
	FileUtils::AppendPath(buttonLibrary, fileName);
}
