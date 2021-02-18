//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/tablebasics/TblBscActionComponent.cpp $
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
#include "IDialogMgr.h"
#include "IDialog.h"
#include "IApplication.h"
#include "ISession.h"
#include "IActiveContext.h"
#include "ISelectionManager.h"

// General includes:
#include "LocaleSetting.h"
#include "CActionComponent.h"
#include "CAlert.h"
#include "WideString.h"
#include "CoreResTypes.h" // kViewRsrcType
#include "RsrcSpec.h"

// Project includes:
#include "TblBscID.h"
#include "ITblBscSuite.h"


/** Implements the actions that are executed when the plug-in's
	menu items are selected.

	
	@ingroup tablebasics
 */
class TblBscActionComponent : public CActionComponent
{
	public:
		/** Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		TblBscActionComponent(IPMUnknown* boss);

		/** Called by the framework when the action is to be performed.
			@param ac context in which action is to be performed.
			@param actionID identifies the action that was selected.
			@param mousePoint contains the global mouse location at time of event causing action
			(e.g. context menus). kInvalidMousePoint if not relevant.
		 */
		virtual void	DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);

		/** Called by the framework to allow actions to be enabled or disabled
			dependent on the capability of the selection.
			@param ac context in which action is to be performed.
			@param listToUpdate
			@param mousePoint contains the global mouse location at time of event causing action
			(e.g. context menus). kInvalidMousePoint if not relevant.
		*/
		virtual void	UpdateActionStates(IActiveContext* ac, IActionStateList* listToUpdate, GSysPoint mousePoint, IPMUnknown* widget);
		
	private:
		/** Pops the about this plug-in alert. 
		 */
		void DoAbout();

		/** Pops this plug-in's "TableBasics" dialog, see TblBscDialogController. 
		 */
		void DoNewTable();

};

/* Makes the implementation available to the application.
*/
CREATE_PMINTERFACE(TblBscActionComponent, kTblBscActionComponentImpl)

/* 
*/
TblBscActionComponent::TblBscActionComponent(IPMUnknown* boss)
: CActionComponent(boss)
{
}

/* 
*/
void TblBscActionComponent::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
	switch (actionID.Get())
	{
		case kTblBscAboutActionID:
		{
			this->DoAbout();
			break;
		}

		case kTblBscNewTableActionID:
		{
			this->DoNewTable();
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
void TblBscActionComponent::UpdateActionStates(IActiveContext* ac, IActionStateList* listToUpdate, GSysPoint mousePoint, IPMUnknown* widget)
{	
	ASSERT(ac);
	ASSERT(listToUpdate);
	if(ac != nil && listToUpdate != nil) {

		// All the actions in this plug-in that have custom enabling specify
		// the availability of IID_ITBLBSCSUITE as a precondition in their
		// ActionDef statement. If the suite is not available complain by raising
		// an assert.
		InterfacePtr<ITblBscSuite> tblBscSuite(ac->GetContextSelection(), UseDefaultIID());
		ASSERT(tblBscSuite);
		
		for(int i=0; i < listToUpdate->Length(); i++) {
			ActionID actionID = listToUpdate->GetNthAction(i);
			int16 state = kDisabled_Unselected;
			switch (actionID.Get())
			{
			case kTblBscNewTableActionID:
				{
					if(tblBscSuite && tblBscSuite->CanInsertTable() == kTrue) {
						state = kEnabledAction;
					}
					break;
				}
			default: 
				{
					ASSERT_FAIL(FORMAT_ARGS("TblBscActionComponent::UpdateActionStates does not know how to custom enable ActionID 0x%x", 
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
void TblBscActionComponent::DoAbout()
{
	CAlert::ModalAlert
	(
	   kTblBscAboutBoxStringKey,			// Alert string
	   kOKString, 							// OK button
	   kNullString, 						// No second button
	   kNullString, 						// No third button
	   1,									// Set OK button to default
	   CAlert::eInformationIcon				// Information icon.
	);
}

/*
*/
void TblBscActionComponent::DoNewTable()
{
	do
	{
		// Get the application interface and the DialogMgr.	
		InterfacePtr<IApplication> application(GetExecutionContextSession()->QueryApplication());
		ASSERT(application);
		if (application == nil)	{
			break;
		}
		InterfacePtr<IDialogMgr> dialogMgr(application, UseDefaultIID());
		ASSERT(dialogMgr);
		if (dialogMgr == nil)	{ 
			break;
		}

		// Load the plug-in's resource.
		PMLocaleId nLocale = LocaleSetting::GetLocale();
		RsrcSpec dialogSpec
		(
			nLocale,					// Locale index from PMLocaleIDs.h. 
			kTblBscPluginID,			// Our Plug-in ID from TblBscID.h. 
			kViewRsrcType,				// This is the kViewRsrcType.
			kSDKDefDialogResourceID,	// Resource ID for our dialog.
			kTrue						// Initially visible.
		);

		// CreateNewDialog takes the dialogSpec created above, and also
		// the type of dialog being created (kMovableModal).
		IDialog* dialog = dialogMgr->CreateNewDialog(dialogSpec, IDialog::kMovableModal);
		ASSERT(dialog);
		if (dialog == nil) { 
			break;
		}

		// Open the dialog.
		dialog->Open(); 
	
	} while (false);			
}

//  Generated by Dolly build 17: template "ActivePanelMenu".
// End, TblBscActionComponent.cpp.





