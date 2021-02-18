//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicpersistinterfaceui/BPIUIActionComponent.cpp $
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
#include "ISession.h"
#include "IApplication.h"
#include "IDialogMgr.h"
#include "ISelectionManager.h"
#include "IActiveContext.h"
#include "IActionStateList.h"

// API includes:
#include "CActionComponent.h"
#include "CAlert.h"
#include "CoreResTypes.h"
#include "LocaleSetting.h"
#include "RsrcSpec.h"

// Project includes:
#include "BPIUIID.h"
#include "IBPISuite.h"

/** Implements an action component, IActionComponent, defining the actions 
	that are executed when this plug-in's menu items are chosen.

	@ingroup basicpersistinterface
	
*/
class BPIActionComponent : public CActionComponent
{
public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		BPIActionComponent(IPMUnknown* boss);

		/** Destructor
		 */
		virtual ~BPIActionComponent() {};

		/** Called by the framework when the action is to be performed.
			@param ac context in which the action is to be performed.
			@param actionID identifies the action to be performed.
			@param mousePoint ontains the global mouse location at time of event causing action (e.g. context menus), kInvalidMousePoint otherwise.
			@param widget the widget that invoked the action or nil otherwise
		 */
		virtual void	DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);

		/** Called by the framework to allow actions to be enabled or disabled
			dependent on the capability of the selection.
			@param ac context in which the action is to be performed.
			@param listToUpdate list containing items to be enabled disabled.
			@param mousePoint ontains the global mouse location at time of event causing action (e.g. context menus), kInvalidMousePoint otherwise.
			@param widget the widget that invoked the action or nil otherwise
		*/
		virtual void	UpdateActionStates(IActiveContext* ac, IActionStateList* listToUpdate, GSysPoint mousePoint, IPMUnknown* widget);

private:
		/** Pops the plug-ins about alert.
		*/
		void DoAbout();

		/** Pops the plug-ins SetBPIData dialog
		*/
		void DoSetBPIData();
};

/* 
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(BPIActionComponent, kBPIUIActionComponentImpl)

/* Constructor
*/
BPIActionComponent::BPIActionComponent(IPMUnknown* boss)
: CActionComponent(boss)
{
}

/* 
*/
void BPIActionComponent::UpdateActionStates(IActiveContext* ac, IActionStateList* listToUpdate, GSysPoint mousePoint, IPMUnknown* widget)
{	
	ASSERT(ac);
	ASSERT(listToUpdate);
	if(ac != nil && listToUpdate != nil) {

		// All the actions in this plug-in that have custom enabling specify
		// the availability of IID_IBPISUITE as a precondition in their
		// ActionDef statement. If the suite is not available complain by raising
		// an assert.
		InterfacePtr<IBPISuite> bpiSuite(ac->GetContextSelection(), UseDefaultIID());
		ASSERT(bpiSuite);
		
		for(int i=0; i < listToUpdate->Length(); i++) {
			ActionID actionID = listToUpdate->GetNthAction(i);
			int16 state = kDisabled_Unselected;
			switch (actionID.Get())
			{
			case kBPIUISetBPIDataActionID:
				{
					if(bpiSuite && bpiSuite->CanApplyBPIData() == kTrue) {
						state = kEnabledAction;
					}
					break;
				}
			default: 
				{
					ASSERT_FAIL(FORMAT_ARGS("BPIActionComponent::UpdateActionStates does not know how to custom enable ActionID 0x%x", 
						actionID.Get()));
					break;
				}	
			} // end switch
			listToUpdate->SetNthActionState(i, state);
		} // end for	
	}
}

/*
*/
void BPIActionComponent::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
	switch (actionID.Get())
	{
		case kBPIUIPopupAboutThisActionID:
		case kBPIUIAboutActionID:
		{
			this->DoAbout();
			break;
		}

		case kBPIUISetBPIDataActionID:
		{
			this->DoSetBPIData();
			break;
		}

		default:
		{
			ASSERT_FAIL("BPIActionComponent::DoAction called for unknown ActionID");
			break;
		}
	}
}

/* 
*/
void BPIActionComponent::DoAbout()
{
	// Bring up the About box
	CAlert::ModalAlert
	(
	   kBPIUIAboutBoxStringKey,						// Alert string
	   kOKString, 							// OK button
	   kNullString, 						// No second button
	   kNullString, 						// No third button
	   1,									// Set OK button to default
	   CAlert::eInformationIcon				// Information icon.
	);
}

/*
*/
void BPIActionComponent::DoSetBPIData()
{
	do
	{
		// Get the applicaton interface and the dialog manager	
		InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
		ASSERT(app);
		if (!app) {
			break;
		}
		InterfacePtr<IDialogMgr> dialogMgr(app, UseDefaultIID());
		ASSERT(dialogMgr);
		if (!dialogMgr) {
			break;
		}

		// We need to load the plug-ins resource:
		PMLocaleId nLocale = LocaleSetting::GetLocale();
		RsrcSpec dialogSpec
		(
			nLocale,					// Locale index from PMLocaleIDs.h. 
			kBPIUIPluginID,				// Our Plug-in ID. 
			kViewRsrcType,				// This is the kViewRsrcType.
			kSDKDefDialogResourceID,	// Resource ID for our dialog.
			kTrue						// Initially visible.
		);

		// CreateNewDialog takes the dialogSpec created above, and also
		// the type of dialog being created (kMovableModal).
		IDialog* dialog = dialogMgr->CreateNewDialog(dialogSpec, IDialog::kMovableModal);
		ASSERT(dialog);
		if (!dialog){
			break;
		}

		// Open causes the dialog to be displayed and then returns immediately
		dialog->Open();
	}
	while (false);
}

//  Generated by Dolly build 11: template "IfPanelMenu".

// End, BPIActionComponent.cpp.




