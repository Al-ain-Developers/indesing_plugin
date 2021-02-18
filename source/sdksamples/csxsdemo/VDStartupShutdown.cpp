//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/csxsdemo/VDStartupShutdown.cpp $
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
//  Copyright 1997-2013 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"
#include "IStartupShutdownService.h"
#include "CPMUnknown.h"
#include "VDID.h"
#include "ICSXSPlugPlugEventHandler.h"
#include "CAlert.h"
#include "tinyxml2.h"

class VDStartupShutdown : public CPMUnknown<IStartupShutdownService>
{
public:
	//	Constructor
    VDStartupShutdown(IPMUnknown* boss);

	//	Destructor
	virtual ~VDStartupShutdown() {}

	//	Called when app is starting up
    virtual void Startup();

	//	Called when app is shutting down
	virtual void Shutdown();

	// Message listener for CSXS messages
	static void MessageEventListener(const ICSXSPlugPlugEventHandler::CSXSEvent* const csxsEvent, void* const context);

private:
	std::string MESSAGE_TYPE;
};

// Bind this C++ implementation onto its implementation ID so it's callable by InDesign.
CREATE_PMINTERFACE(VDStartupShutdown, kVDStartupShutdownImpl)

// Constructor
VDStartupShutdown::VDStartupShutdown(IPMUnknown* boss) : CPMUnknown<IStartupShutdownService>(boss)
{
	// we will register an event listener for this message type
	MESSAGE_TYPE = "com.adobe.indesign";
}

// On startup we add an event listener for a message type to catch CSXS messages from Illustrator
void VDStartupShutdown::Startup()
{
	InterfacePtr<ICSXSPlugPlugEventHandler> plugPlug(GetExecutionContextSession(), UseDefaultIID());
    plugPlug->AddPlugPlugEventListener(MESSAGE_TYPE.c_str(), &MessageEventListener, nil);
}

// On shutdown we remove the event listener for the message type that we added on startup
void VDStartupShutdown::Shutdown()
{
	InterfacePtr<ICSXSPlugPlugEventHandler> plugPlug(GetExecutionContextSession(), UseDefaultIID());
    plugPlug->RemovePlugPlugEventListener(MESSAGE_TYPE.c_str(), &MessageEventListener, nil);
}

// Handle received event
void VDStartupShutdown::MessageEventListener(const ICSXSPlugPlugEventHandler::CSXSEvent* const csxsEvent, void* const context)
{
	// parse the received event XML
	tinyxml2::XMLDocument xmlEvent;
	tinyxml2::XMLError result = xmlEvent.Parse(csxsEvent->data);
	if (result != tinyxml2::XML_SUCCESS)
	{
		return;
	}

    // extract payload from event xml
	tinyxml2::XMLElement * payloadElement = xmlEvent.FirstChildElement("payload");
	std::string payload = payloadElement->GetText();

	// show the payload in an alert dialog
	PMString alertText = PMString(payload.c_str());
	alertText.SetTranslatable(kFalse); // since we don't know the string we can't possibly have a translation of it
	CAlert::InformationAlert(alertText);
}
