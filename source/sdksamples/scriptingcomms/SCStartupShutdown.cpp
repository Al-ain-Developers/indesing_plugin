//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/scriptingcomms/SCStartupShutdown.cpp $
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
#include "SCID.h"
#include "ICSXSPlugPlugEventHandler.h"
#include "CAlert.h"
#include "adobe/unicode.hpp" // for adobe::to_utf8
#include "FileTypeRegistry.h"

// Implements IStartupShutdownService
class SCStartupShutdown : public CPMUnknown<IStartupShutdownService>
{
public:
	//	Constructor
    SCStartupShutdown(IPMUnknown* boss);

	//	Destructor
	virtual ~SCStartupShutdown() {}

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
CREATE_PMINTERFACE(SCStartupShutdown, kSCStartupShutdownImpl)

// Constructor
SCStartupShutdown::SCStartupShutdown(IPMUnknown* boss) : CPMUnknown<IStartupShutdownService>(boss)
{
	// we will register an event listener for this message type
	MESSAGE_TYPE = "com.adobe.indesign.scriptingcomms.cpp";
}

// On startup we add an event listener for a message type to catch CSXS messages from the HTML extension 
void SCStartupShutdown::Startup()
{
	InterfacePtr<ICSXSPlugPlugEventHandler> plugPlug(GetExecutionContextSession(), UseDefaultIID());
    plugPlug->AddPlugPlugEventListener(MESSAGE_TYPE.c_str(), &MessageEventListener, nil);
}

// On shutdown we remove the event listener for the message type that we added on startup
void SCStartupShutdown::Shutdown()
{
	InterfacePtr<ICSXSPlugPlugEventHandler> plugPlug(GetExecutionContextSession(), UseDefaultIID());
    plugPlug->RemovePlugPlugEventListener(MESSAGE_TYPE.c_str(), &MessageEventListener, nil);
}

// Message handler
void SCStartupShutdown::MessageEventListener(const ICSXSPlugPlugEventHandler::CSXSEvent* const csxsEvent, void* const context)
{
	// Display received data in alert dialog..
	PMString receivedData = PMString("Message received: ");
	receivedData.Append(csxsEvent->data);
	receivedData.SetTranslatable(kFalse);
	CAlert::InformationAlert(receivedData);

	// Send a message back to the HTML extension..
    InterfacePtr<ICSXSPlugPlugEventHandler> plugPlug(GetExecutionContextSession(), UseDefaultIID());
    
    PMString csxsEventStr;
    csxsEventStr.SetCString("Hello from CPP!");
    PMString eventData(csxsEventStr);
    std::string csxsEventUtf8;
    adobe::detail::to_utf8<char>(csxsEventStr.begin(), csxsEventStr.end(), std::back_inserter(csxsEventUtf8), adobe::detail::unicode_size_type_<sizeof(UTF16TextChar)>());
    
    ICSXSPlugPlugEventHandler::CSXSEvent responseEvent;
    responseEvent.type = "com.adobe.indesign.scriptingcomms.html";
    responseEvent.scope = ICSXSPlugPlugEventHandler::kEventScope_Application; // not sending outside of app
    responseEvent.extensionId = nil;
    responseEvent.data = csxsEventUtf8.c_str();
    
    if (LocaleSetting::GetLocale().IsProductFS(kInDesignProductFS))
    {
        responseEvent.appId = kIDEnigmaCode; // as defined in ICSXSPlugPlugEventHandler.h
    }
    else
    {
        responseEvent.appId = kICEnigmaCode; // as defined in ICSXSPlugPlugEventHandler.h
    }
    
    plugPlug->DispatchPlugPlugEvent(&responseEvent);
}