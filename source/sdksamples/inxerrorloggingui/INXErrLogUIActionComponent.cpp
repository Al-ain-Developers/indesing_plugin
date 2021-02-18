//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/inxerrorloggingui/INXErrLogUIActionComponent.cpp $
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
#include "IStringData.h"

// General includes:
#include "CActionComponent.h"
#include "CAlert.h"
#include "StringUtils.h"
#include "SDKFileHelper.h"
#include "Utils.h"

// Project includes:
#include "INXErrLogUIID.h"
#include "INXErrLogID.h"
#include "iinxerrlogfacade.h"


/** Implements IActionComponent; performs the actions that are executed when the plug-in's
	menu items are selected.
	
	@ingroup inxerrorloggingui.sdk

*/
class INXErrLogUIActionComponent : public CActionComponent
{
public:
/**
 Constructor.
 @param boss interface ptr from boss object on which this interface is aggregated.
 */
		INXErrLogUIActionComponent(IPMUnknown* boss);

		/**
			Enables or disables actions, see CActionComponent::UpdateActionStates.

		*/
        virtual void    UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget);

		/** The action component should perform the requested action.
			This is where the menu item's action is taken.
			When a menu item is selected, the Menu Manager determines
			which plug-in is responsible for it, and calls its DoAction
			with the ID for the menu item chosen.

			@param actionID identifies the menu item that was selected.
			@param ac active context
			@param mousePoint contains the global mouse location at time of event causing action (e.g. context menus). kInvalidMousePoint if not relevant.
			@param widget contains the widget that invoked this action. May be nil. 
			*/
		virtual void DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);

	private:
		/** Encapsulates functionality for the about menu item. */
		void DoAbout();
		


};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(INXErrLogUIActionComponent, kINXErrLogUIActionComponentImpl)

/* INXErrLogActionComponent Constructor
*/
INXErrLogUIActionComponent::INXErrLogUIActionComponent(IPMUnknown* boss)
: CActionComponent(boss)
{
}

void INXErrLogUIActionComponent::UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget)
{
    int32 count = listToUpdate->Length();
    while (count--)
    {
        ActionID action = listToUpdate->GetNthAction(count);

        switch (action.Get())
        {
			case kINXErrLogUIToggleActionID:
			{
				
				PMString actionStr;
				bool16 errorHandleValue = kFalse;
				//Get the INXErrorHandler state from model plug-in
				Utils<IINXErrLogFacade>()->GetINXErrorHandlerState(errorHandleValue);	
				if(errorHandleValue == kTrue)
				{
					actionStr = kINXErrLogUIToggleMenuRemoveKey;
				}
				else
				{
					actionStr = kINXErrLogUIToggleMenuInstallKey;
				}

				actionStr.Translate();
				PMString menuItemString (kINXErrLogUIToggleMenuKey);
				menuItemString.Translate();
				::ReplaceStringParameters(&menuItemString, actionStr);

                listToUpdate->SetNthActionState(count,kEnabledAction);
				listToUpdate->SetNthActionName(count,menuItemString);
				break;
			}
		}
	}

}


/* DoAction
*/
void INXErrLogUIActionComponent::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
	switch (actionID.Get())
	{

		case kINXErrLogUIAboutActionID:
		{
			this->DoAbout();
			break;
		}
		
					
        case kINXErrLogUIToggleActionID:
        {
			
			bool16 errorHandleValue = kFalse;
			Utils<IINXErrLogFacade>()->GetINXErrorHandlerState(errorHandleValue);	
			if(errorHandleValue == kTrue)
			{
				Utils<IINXErrLogFacade>()->ClearINXErrorHandler();
			}
			else
			{	
				SDKFileOpenChooser fileChooser;
				fileChooser.SetTitle(kINXErrLogUIChooseFileStringKey);	
				fileChooser.AddAllFiles();
				fileChooser.ShowDialog();
				if (!fileChooser.IsChosen()) {
					Utils<IINXErrLogFacade>()->ClearINXErrorHandler();
					break;
				}
				PMString path = fileChooser.GetPath();
				path.SetTranslatable(kFalse);
				Utils<IINXErrLogFacade> errorLogFacade;
				errorLogFacade->SetBaseINXErrorHandlerPath(path);	
				errorLogFacade->CreateINXErrorHandler();				
			}
		}
		default:
		{
			break;
		}
	}
}

/* DoAbout
*/
void INXErrLogUIActionComponent::DoAbout()
{
	CAlert::ModalAlert
	(
		kINXErrLogUIAboutBoxStringKey,				// Alert string
		kOKString, 						// OK button
		kNullString, 						// No second button
		kNullString, 						// No third button
		1,							// Set OK button to default
		CAlert::eInformationIcon				// Information icon.
	);
}



//  Code generated by DollyXs code generator
