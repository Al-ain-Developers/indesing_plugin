//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/PageTransitionsMenuComponent.cpp $
//  
//  Owner: Yeming Liu
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

// ----- Interface files -----

#include "IActionStateList.h"
#include "IActiveContext.h"
#include "IApplication.h"
#include "IControlView.h"
#include "IDialog.h"
#include "IDialogMgr.h"
#include "IDocument.h"
#include "IDropDownListController.h"
#include "ILayoutControlData.h"
#include "IMasterSpread.h"
#include "IPanelControlData.h"
#include "IPageTransition.h"
#include "ISpread.h"


// ----- Include files -----

#include "CActionComponent.h"
#include "CoreResTypes.h"
#include "DynamicDocumentsUIDefs.h"
#include "LocaleSetting.h"
#include "RsrcSpec.h"
#include "UIDList.h"

// ----- Utility files -----

#include "DynamicDocumentsUIUtils.h"
#include "IPageTransitionFacade.h"
#include "IPalettePanelUtils.h"
#include "Utils.h"

// ----- ID files -----

#include "DynamicDocumentsUIID.h"

//========================================================================================
// CLASS PageTransitionsMenuComponent
//========================================================================================
class PageTransitionsMenuComponent : public CActionComponent
{
	public:
		PageTransitionsMenuComponent(IPMUnknown *boss);
		
		virtual void	UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget);
		virtual void	DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);

	private:
		void GetPageTransitionDataFromPanel(ClassID &transitionClass, uint32 &direction, uint32 &speed);
};

CREATE_PMINTERFACE(PageTransitionsMenuComponent, kPageTransitionsMenuComponentImpl)

//---------------------------------------------------------------
// Constructor
//---------------------------------------------------------------
PageTransitionsMenuComponent::PageTransitionsMenuComponent(IPMUnknown *boss) :
	CActionComponent(boss)
{
}

//---------------------------------------------------------------
// PageTransitionsMenuComponent::UpdateActionStates()
//---------------------------------------------------------------
void PageTransitionsMenuComponent::UpdateActionStates(IActiveContext* ac, IActionStateList *updateList, GSysPoint mousePoint, IPMUnknown* widget)
{				
	IDocument* doc = ac->GetContextDocument();
	if (!doc)
		return;

	UIDList spreadList(::GetDataBase(doc));

	int32 count = updateList->Length();

	for (int32 i = 0; i < count; ++i)
	{
		ActionID nthActionID = updateList->GetNthAction(i);
		switch (nthActionID.Get())
		{
			case kTransitionPanelChooseActionID:
			{
				IControlView* layoutView = ac->GetContextView();
				if(layoutView)
				{
					InterfacePtr<ILayoutControlData> iLayoutControlData(layoutView, UseDefaultIID());
					if(iLayoutControlData)
					{
						const UIDRef& currentSpread = iLayoutControlData->GetSpreadRef();
						InterfacePtr<ISpread> iSpread(currentSpread, UseDefaultIID());
						InterfacePtr<IMasterSpread> iMasterSpread(iSpread, UseDefaultIID());
						
						// Enable the menu when it is not master spread.
						updateList->SetNthActionState(i, (iMasterSpread == nil) ? kEnabledAction : kDisabled_Unselected);
					}
				}

				break;
			}

			case kTransitionPanelApplyToAllSpreadsActionID:
			{				
				ClassID resultTransitionClass = kInvalidClass;
				if (Utils<Facade::IPageTransitionFacade>()->AllSpreadsHaveSamePageTransition(spreadList, resultTransitionClass))
					updateList->SetNthActionState(i, kDisabled_Unselected);
				else
					updateList->SetNthActionState(i, kEnabledAction);
			
				break;
			}
			case kTransitionPanelClearAllTransitionsActionID:
			{
				if (Utils<Facade::IPageTransitionFacade>()->SpreadsHavePageTransition(spreadList))
					updateList->SetNthActionState(i, kEnabledAction);
				else
					updateList->SetNthActionState(i, kDisabled_Unselected);

				break;
			}
			default:
				ASSERT("Unknown action!");
				break;
		}
	}
}

//---------------------------------------------------------------
// PageTransitionsMenuComponent::DoAction()
//---------------------------------------------------------------
void PageTransitionsMenuComponent::DoAction(IActiveContext* ac, ActionID id, GSysPoint mousePoint, IPMUnknown* widget)
{
	switch (id.Get()) 
	{
		case kTransitionPanelApplyToAllSpreadsActionID:
		case kTransitionPanelClearAllTransitionsActionID:
		{
			IControlView* layoutView = ac->GetContextView();
			InterfacePtr<ILayoutControlData> iLayoutControlData(layoutView, UseDefaultIID());
			if (iLayoutControlData)
			{
				ClassID transitionClass = kInvalidClass;
				uint32 direction = IPageTransition::kNA;
				uint32 speed = IPageTransition::kDefaultDurationTime;

				// If we apply all, we apply the transition shown in the transition panel since transition panel reflects the current selection in pages panel.
				// If we clear all transition, we just apply no transition.
				if (id.Get() == kTransitionPanelApplyToAllSpreadsActionID)
					this->GetPageTransitionDataFromPanel(transitionClass, direction, speed);

				const UIDRef& currentSpread = iLayoutControlData->GetSpreadRef();
				UIDList spreadList(currentSpread.GetDataBase());
				ErrorCode result = Utils<Facade::IPageTransitionFacade>()->ApplyPageTransitionToAllSpreads(spreadList, transitionClass, direction, speed);
			}
			break;
		}
		
		case kTransitionPanelChooseActionID:
		{
			// Bring up page transition dialog.
			InterfacePtr<IApplication> iApp(GetExecutionContextSession()->QueryApplication());
			InterfacePtr<IDialogMgr> iDialogMgr(iApp, IID_IDIALOGMGR);
			IDialog* iDialog = iDialogMgr->CreateNewDialog(RsrcSpec(LocaleSetting::GetLocale(), kDynamicDocumentsUIPluginID, kViewRsrcType, kPageTransitionsDialogRsrcID),
								IDialog::kMovableModal);

			if (iDialog)
			{
				iDialog->Open();
				iDialog->WaitForDialog();
			}

			break;
		}

		default:
			ASSERT_FAIL("Asked to do unknown action");
			break;
	}
}

void PageTransitionsMenuComponent::GetPageTransitionDataFromPanel(ClassID &transitionClass, uint32 &direction, uint32 &speed)
{
	InterfacePtr<IPanelControlData> iPanelControlData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kPageTransitionsPanelWidgetID)); 
	if (!iPanelControlData)
		return;

	// Get transition class
 	IControlView* transitionDropDown = iPanelControlData->FindWidget(kPageTransitionDropDownWidgetID);
	InterfacePtr<IDropDownListController> iTransitionDDListController(transitionDropDown, UseDefaultIID());
	int32 transitionSelected = iTransitionDDListController->GetSelected();
	if (transitionSelected >= 2) // 2 is to count for the "No Transition" and separator
		transitionClass = Utils<Facade::IPageTransitionFacade>()->GetNthPageTransitionClassID(transitionSelected-2);	// -2 is to count for the "No Transition" and separator

	// Get transition direction
	IControlView* directionDropDown = iPanelControlData->FindWidget(kPageDirectionDropDownWidgetID);
	InterfacePtr<IDropDownListController> iDirectionDDListController(directionDropDown, UseDefaultIID());
	int32 directionSelectedIndex = iDirectionDDListController->GetSelected();
	direction = ddui_utils::GetDirectionFromSelectionIndex(transitionClass, directionSelectedIndex);

	// Get transition speed
	IControlView* speedDropDown = iPanelControlData->FindWidget(kPageSpeedDropDownWidgetID);
	InterfacePtr<IDropDownListController> iSpeedDDListController(speedDropDown, UseDefaultIID());
	int32 speedSelectedIndex = iSpeedDDListController->GetSelected();
	speed = ddui_utils::GetSpeedFromSelectionIndex(speedSelectedIndex);
}