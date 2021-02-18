//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/CustomHttpLinkUI/CustomHttpLinkUIActionComponent.cpp $
//  
//  Owner: swagarg
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//
//  ADOBE CONFIDENTIAL
//  
//  Copyright 2019 Adobe
//  All Rights Reserved.
//
//  NOTICE: Adobe permits you to use, modify, and distribute this file in
//  accordance with the terms of the Adobe license agreement accompanying
//  it. If you have received this file from a source other than Adobe,
//  then your use, modification, or distribution of it requires the prior
//  written permission of Adobe. 
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// General includes:
#include "CActionComponent.h"
#include "CAlert.h"

// Project includes:
#include "CustomHttpLinkUIID.h"

#include "IActiveContext.h"
#include "IActionStateList.h"
#include "IHTTPLinkResourceConnection.h"
#include "IHTTPLinkUtils.h"
#include "IJsonUtils.h"
#include "URI.h"

/** Implements IActionComponent;
    performs the actions that are executed when the plug-in's
	menu items are selected.

	@ingroup customhttplinkui.sdk
*/
class CustomHttpLinkUIActionComponent : public CActionComponent
{
public:
/**
 Constructor.
 @param boss interface ptr from boss object on which this interface is aggregated.
 */
		CustomHttpLinkUIActionComponent(IPMUnknown* boss);

		/** The action component should perform the requested action.
			This is where the menu item's action is taken.
			When a menu item is selected, the Menu Manager determines
			which plug-in is responsible for it, and calls its DoAction
			with the ID for the menu item chosen.

            @param ac active context
			@param actionID identifies the menu item that was selected.
			@param mousePoint contains the global mouse location at time of event causing action (e.g. context menus). kInvalidMousePoint if not relevant.
			@param widget contains the widget that invoked this action. May be nil. 
			*/
		virtual void DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);
        virtual void UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget);

	private:
		/** Encapsulates functionality for the about menu item. */
		void DoAbout();
};

// Dummy login credentials
const char* username_key = "username";
const char* username_value = "admin";
const char* password_key = "password";
const char* password_value = "admin";


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(CustomHttpLinkUIActionComponent, kCustomHttpLinkUIActionComponentImpl)

/* CustomHttpLinkUIActionComponent Constructor
*/
CustomHttpLinkUIActionComponent::CustomHttpLinkUIActionComponent(IPMUnknown* boss)
: CActionComponent(boss)
{
}

/* DoAction
*/
void CustomHttpLinkUIActionComponent::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
    switch (actionID.Get())
	{
        // Show about dialog
		case kCustomHttpLinkUIPopupAboutThisActionID:
		case kCustomHttpLinkUIAboutActionID:
		{
			this->DoAbout();
			break;
		}
        
        // Login to the server. Send dummy login credentials
        case kCustomHttpLinkUILoginActionID:
        {
            URI uri;
            uri.SetComponent(URI::kScheme, WideString(kCusHttpLnkScheme));
            uri.SetComponent(URI::kAuthority, WideString(kCusHttpLnkAuthority));
            InterfacePtr<IHTTPLinkResourceConnection> connection = Utils<IHTTPLinkUtils>()->GetHTTPLinkResourceConnection(uri);
            ASSERT(connection);
            if (connection) {
                JSON loginCredentials;
                loginCredentials.addValue(username_key, username_value);
                loginCredentials.addValue(password_key, password_value);
                std::stringstream str;
                loginCredentials.write_json(str);
                connection->SetLoginCredentials(str);
                connection->Connect();
            }
        }
            break;
        
        // Logout from the server
        case kCustomHttpLinkUILogoutActionID:
        {
            URI uri;
            uri.SetComponent(URI::kScheme, WideString(kCusHttpLnkScheme));
            uri.SetComponent(URI::kAuthority, WideString(kCusHttpLnkAuthority));
            InterfacePtr<IHTTPLinkResourceConnection> connection = Utils<IHTTPLinkUtils>()->GetHTTPLinkResourceConnection(uri);
            ASSERT(connection);
            if (connection)
                connection->Disconnect();
        }
            break;
            
		default:
		{
			break;
		}
	}
}


void CustomHttpLinkUIActionComponent::UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget)
{
    const int32 nCount = listToUpdate->Length();
    
    for (int32 i = 0; i < nCount; i++)
    {
        ActionID nAction = listToUpdate->GetNthAction(i);
        
        switch (nAction.Get())
        {
            // If the user is not connected, enable login action
            case kCustomHttpLinkUILoginActionID:
            {
                URI uri;
                uri.SetComponent(URI::kScheme, WideString(kCusHttpLnkScheme));
                uri.SetComponent(URI::kAuthority, WideString(kCusHttpLnkAuthority));
                InterfacePtr<IHTTPLinkResourceConnection> connection = Utils<IHTTPLinkUtils>()->GetHTTPLinkResourceConnection(uri);
                ASSERT(connection);
                if (connection && !connection->IsConnected())
                {
                    listToUpdate->SetNthActionState(i, kEnabledAction);
                }
            }
                break;
                
            // If the user is connected, enable logout action
            case kCustomHttpLinkUILogoutActionID:
            {
                URI uri;
                uri.SetComponent(URI::kScheme, WideString(kCusHttpLnkScheme));
                uri.SetComponent(URI::kAuthority, WideString(kCusHttpLnkAuthority));
                InterfacePtr<IHTTPLinkResourceConnection> connection = Utils<IHTTPLinkUtils>()->GetHTTPLinkResourceConnection(uri);
                ASSERT(connection);
                if (connection && connection->IsConnected())
                {
                    listToUpdate->SetNthActionState(i, kEnabledAction);
                }
                
            }
                break;
                
            default:
                ASSERT_FAIL("asked to update action I don't know about!");
                break;
        }
    }
}


/* DoAbout
*/
void CustomHttpLinkUIActionComponent::DoAbout()
{
	CAlert::ModalAlert
	(
		kCustomHttpLinkUIAboutBoxStringKey,				// Alert string
		kOKString, 						// OK button
		kNullString, 						// No second button
		kNullString, 						// No third button
		1,							// Set OK button to default
		CAlert::eInformationIcon				// Information icon.
	);
}

