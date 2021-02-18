//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/detailcontrollistsize/DCLSizActionComponent.cpp $
//  
//  Owner: Adobe Developer Technologies
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

// Interface includes:
#include "IActionStateList.h"
#include "IPanelControlData.h"

// General includes:
#include "CActionComponent.h"
#include "CAlert.h"
#include "IPalettePanelUtils.h"
#include "ITreeViewController.h"
#include "ITreeViewWidgetMgr.h"
#include "TreeViewDefs.h"
#include "IDCLSizPanelOptions.h"

// Project includes:
#include "DCLSizID.h"


/** Implements the actions that are executed when the plug-in's
	menu items are selected. 

	@ingroup detailcontrollistsize
	
*/
class DCLSizActionComponent : public CActionComponent
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		DCLSizActionComponent(IPMUnknown* boss);

		/** The action component should do the requested action. Note this will never be called 
			except when the action is enabled. 

			@param ac points to the current active context
			@param actionID identifies which action this action component should perform
			@param mousePoint contains the global mouse location at time of event causing action (e.g. context menus). kInvalidMousePoint if not relevant.
			@param widget contains the widget that invoked this action. May be nil. 
		*/
		virtual void	DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);

		/** Called when the action component is asked to update a list of actions to the proper state.
			This method is required to be overridden by subclasses only if there are action components with 
			kCustomEnabling specified.

			The list of actions is initially disabled and unselected, so it only has to be
			changed if this state is not correct. Note that action components are never asked to update
			actions that don't belong to them, or actions they have not specified kCustomEnabling for.
			
			@param ac points to the current active context
			@param listToUpdate contains the items that client code should update the state for
			@param mousePoint contains the global mouse location at time of event causing action (e.g. context menus). kInvalidMousePoint if not relevant.
			@param widget contains the widget that invoked this action. May be nil. 
		*/
		virtual void	UpdateActionStates(IActiveContext* ac, IActionStateList* listToUpdate, GSysPoint mousePoint, IPMUnknown* widget);

	private:

		/** Encapsulates functionality for the SmallPaletteRows menu item. */
		void DoSmallPaletteRows();

};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(DCLSizActionComponent, kDCLSizActionComponentImpl)

/* DCLSizActionComponent Constructor
*/
DCLSizActionComponent::DCLSizActionComponent(IPMUnknown* boss)
: CActionComponent(boss)
{
}

/* DoAction
*/
void DCLSizActionComponent::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
	switch (actionID.Get())
	{
		case kDCLSizPopupAboutThisActionID:
		case kDCLSizAboutActionID:
		{
			CAlert::ModalAlert
			(
				kDCLSizAboutBoxStringKey,		// Alert string
				kOKString, 						// OK button
				kNullString, 					// No second button
				kNullString, 					// No third button
				1,								// Set OK button to default
				CAlert::eInformationIcon		// Information icon.
			);
			break;
		}

		case kDCLSizSmallPaletteRowsActionID:
		{
			this->DoSmallPaletteRows();
			break;
		}

		default:
		{
			break;
		}
	}
}


/* UpdateActionStates
*/
void DCLSizActionComponent::UpdateActionStates(IActiveContext* ac, IActionStateList* listToUpdate, GSysPoint mousePoint, IPMUnknown* widget)
{
	do {

		bool16 bSmallPaletteRows = kFalse;
		InterfacePtr<IPanelControlData> panelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kDCLSizPanelWidgetID));
		ASSERT_MSG(panelData !=nil, "No panelData");
		if(!panelData) 
		{
			break;
		}

		IControlView* treeWidget = panelData->FindWidget(kDCLSizListBoxWidgetID);
		if(treeWidget == nil) 
		{
			break;
		}

	    InterfacePtr<ITreeViewWidgetMgr> treeMgr(treeWidget, UseDefaultIID());
	    ASSERT_MSG(treeMgr, "TableStylesUIFacade::ToggleSmallPaletteRows() could not get tree manager!");

	    bSmallPaletteRows = treeMgr->GetStyle() == kSmallPaletteRowsTreeStyle;
		
		for(int i=0 ; i < listToUpdate->Length() ; i++) 
		{
        	ActionID action = listToUpdate->GetNthAction(i);
			switch (action.Get())
			{
				case kDCLSizSmallPaletteRowsActionID:
				{
					if(bSmallPaletteRows) 
					{
						listToUpdate->SetNthActionState(i,kEnabledAction|kSelectedAction);
					}
					else 
					{
						listToUpdate->SetNthActionState(i,kEnabledAction);
					}
				}
				break;
			}
		}

	} while(false);
}

/* DoSmallPaletteRows
*/
void DCLSizActionComponent::DoSmallPaletteRows()
{
	do
	{
		InterfacePtr<IPanelControlData> panelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kDCLSizPanelWidgetID));	
		ASSERT_MSG( panelData !=nil, "panelData nil");
		if(panelData==nil) 
		{
			break;
		}

		InterfacePtr<IDCLSizPanelOptions> iDCLSizPanelPrefs(panelData, IID_IDCLSizPanelOptions);
		if(iDCLSizPanelPrefs == nil) 
		{
			break;
		}
	
		IControlView* treeWidget = panelData->FindWidget(kDCLSizListBoxWidgetID);
		if(treeWidget == nil) 
		{
			break;
		}

	    InterfacePtr<ITreeViewWidgetMgr> treeMgr(treeWidget, UseDefaultIID());
	    ASSERT_MSG(treeMgr, "Could not get tree manager!");

	    if(treeMgr->GetStyle() == kLargePaletteRowsTreeStyle)
	    {
		   treeMgr->SetStyle(kSmallPaletteRowsTreeStyle);
		   iDCLSizPanelPrefs->Set(kFalse);
	    }
	    else if(treeMgr->GetStyle() == kSmallPaletteRowsTreeStyle)
	    {
		   treeMgr->SetStyle(kLargePaletteRowsTreeStyle);
		   iDCLSizPanelPrefs->Set(kTrue);
	    }

	} while(false);
}
//  Generated by Dolly build 12: template "IfPanelMenu".
// End, DCLSizActionComponent.cpp.

