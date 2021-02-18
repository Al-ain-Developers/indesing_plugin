//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/SnipRunActionComponent.cpp $
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
#include "IWidgetParent.h"
#include "IPanelPtr.h"
#include "IControlView.h"
#include "IPanelControlData.h"
#include "IActionStateList.h"

// General includes:
#include "CActionComponent.h"
#include "CAlert.h"


// Project includes:
#include "SnipRunID.h"

/** Implements the actions provided by this plug-in.

	Implements IActionComponent based on
	the partial implementation CActionComponent.

	@ingroup snippetrunner
	
*/
class SnipRunActionComponent : public CActionComponent
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		SnipRunActionComponent(IPMUnknown* boss);
		/**
			This method is called when the action component's menus need updating -- this is 
			where menu items are enabled or disabled, checked or unchecked, etc.
			@param ac context in which action is to be performed.	
			@param listToUpdate contains a list of menu items for menu states updates.
            @param mousePoint contains the global mouse location at time of event causing action.
            @param widget contains the widget that invoked this action. May be nil. 
		*/
		virtual void UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint = kInvalidMousePoint, IPMUnknown* widget = nil);

		/** Called by the framework when the action is to be performed.
			@param ac context in which action is to be performed.
			@param actionID identifies the action that was selected.
			@param mousePoint contains the global mouse location at time of event causing action
			(e.g. context menus). kInvalidMousePoint if not relevant.
			@param widget
		 */
		virtual void	DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);

	private:

		/**	Pop the about box.
		 */
		void DoAbout();

		/**	Locate the parameter widget on the panel, show it if it
			is hidden, or hide it of it is shown.
            @param widget contains the widget that invoked this action.
		 */
		void DoShowParameterBox(IPMUnknown* widget);
};

/* Make the implementation available to the application.
*/
CREATE_PMINTERFACE(SnipRunActionComponent, kSnipRunActionComponentImpl)

/*
*/
SnipRunActionComponent::SnipRunActionComponent(IPMUnknown* boss)
: CActionComponent(boss)
{
}

/*	UpdateActionStates
*/
void SnipRunActionComponent::UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget)
{
	// Iterate through the menu items and enable or disable them
	const int32 total_items = listToUpdate->Length();
	for(int32 i = 0; i < total_items; i++)
	{
		ActionID action = listToUpdate->GetNthAction(i);
		switch (action.Get())
		{
		case kSnipRunShowParameterBoxActionID:
			{	
				// Find the parameter widget on the panel.
				InterfacePtr<IWidgetParent> widgetParent(widget, UseDefaultIID());
				ASSERT(widgetParent);
				if (!widgetParent) {
					break;
				}
				InterfacePtr<IPanelControlData> panelControlData((IPanelControlData*)widgetParent->QueryParentFor(IID_IPANELCONTROLDATA));
				ASSERT(panelControlData);
				if (!panelControlData) {
					break;
				}
				IControlView* parameterControlView(panelControlData->FindWidget(kSnipRunParametersWidgetID));
				ASSERT(parameterControlView);
				if (!parameterControlView) {
					break;
				}

				// Add or clear check mark for the action's associated menu item depending
				// on whether the parameter widget is shown or hidden.
				bool16 isParameterWidgetVisible = parameterControlView->GetVisibleState();
				if (isParameterWidgetVisible) {
					listToUpdate->SetNthActionState(i,kEnabledAction|kSelectedAction);
				}
				else {
					listToUpdate->SetNthActionState(i,kEnabledAction);
				}
				break;
			}
		default:
			{
				break;
			}				
		}
	}
}

/*
*/
void SnipRunActionComponent::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
	switch (actionID.Get())
	{
	case kSnipRunPopupAboutThisActionID:
	case kSnipRunAboutActionID:
		{
			this->DoAbout();
			break;
		}

	case kSnipRunShowParameterBoxActionID:
		{
			this->DoShowParameterBox(widget);
			break;
		}

	default:
		{
			break;
		}
	}
}

/* 
*/
void SnipRunActionComponent::DoAbout()
{
	CAlert::ModalAlert
	(
		kSnipRunAboutBoxStringKey,		// Alert string
		kOKString, 						// OK button
		kNullString, 					// No second button
		kNullString, 					// No third button
		1,								// Set OK button to default
		CAlert::eInformationIcon		// Information icon.
	);
}


/* 
*/
void SnipRunActionComponent::DoShowParameterBox(IPMUnknown* widget)
{
	do {
		// Find the parameter widget on the panel.
		InterfacePtr<IWidgetParent> widgetParent(widget, UseDefaultIID());
		ASSERT(widgetParent);
		if (!widgetParent) {
			break;
		}
		InterfacePtr<IPanelControlData> panelControlData((IPanelControlData*)widgetParent->QueryParentFor(IID_IPANELCONTROLDATA));
		ASSERT(panelControlData);
		if (!panelControlData) {
			break;
		}
		IControlView* parameterControlView(panelControlData->FindWidget(kSnipRunParametersWidgetID));
		ASSERT(parameterControlView);
		if (!parameterControlView) {
			break;
		}

		// Show or hide the parameter widget.
		bool16 isParameterWidgetVisible = parameterControlView->GetVisibleState();
		if (isParameterWidgetVisible) {
			parameterControlView->HideView();
		}
		else {
			parameterControlView->ShowView();
		}	
	} while(false);

}
//  Generated by Dolly build 17: template "IfPanelMenu".
// End, SnipRunActionComponent.cpp.






