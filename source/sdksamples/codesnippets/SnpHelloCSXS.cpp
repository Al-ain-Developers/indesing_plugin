//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpHelloCSXS.cpp $
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
//  Copyright 2013 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interface includes:
#include "FileTypeRegistry.h"

// Snippet runner includes
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

// CSXS/PlugPlug includes
#include "ICSXSPlugPlugEventHandler.h" // for sending CSXS events through PlugPlug
#include "ICSXSVulcanMessageHandler.h"
#include "adobe/unicode.hpp" // for adobe::to_utf8

#include "CAlert.h"

/**
  * \li Sends a CSXS event using PlugPlug.
  *
  * @ingroup sdk_snippet
  */
class SnpHelloCSXS
{
	public:
		// Constructor.
		SnpHelloCSXS() {}

		// Destructor.
		virtual ~SnpHelloCSXS() {}
};

// --------------------------------- SnippetRunner framework hook ---------------------------------------------------

/** Makes the snippet SnpHelloCSXS available to the SnippetRunner framework.
  *
  * @ingroup sdk_snippet_run
  */
class _SnpHelloCSXS : public SnpRunnable
{
	public:
		// Constructor.
		_SnpHelloCSXS();

		// Destructor.
		virtual			~_SnpHelloCSXS();

		/** Return kTrue if the snippet can run.
		  * @param runnableContext see ISnpRunnableContext for documentation.
		  * @return kTrue if snippet can run, kFalse otherwise
		  */
		bool16			CanRun(ISnpRunnableContext* runnableContext);

		/** Run the snippet.
		  *	@param runnableContext see ISnpRunnableContext for documentation.
		  * @return kSuccess on success, other ErrorCode otherwise.
		  */
		ErrorCode		Run(ISnpRunnableContext* runnableContext);

		/** 
		  * get the snippet context
		  * @return eSnpRunContextType for this snippet
		  */
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunNoContext;}

	private:
		static void PlugPlugEventListener(const ICSXSPlugPlugEventHandler::CSXSEvent* const csxsEvent, void* const context);
		static void VulcanMessageListener(const std::string &message);

		bool16 plugPlugReady; // used to avoid adding event listener more than once
		bool16 vulcanListenerAdded;	// so that message listener is added just once.
};

/* 
 * Describes this snippet to the snippet runner framework - 
 * common to all snippets.
 */
_SnpHelloCSXS::_SnpHelloCSXS() : SnpRunnable("HelloCSXS")
{	
	this->SetDescription("Sends and receives a CSXS message using PlugPlug.");
	this->SetPreconditions("none");
	this->SetCategories("sdk_snippet");
	this->plugPlugReady = kFalse;
	this->vulcanListenerAdded = kFalse;
}

_SnpHelloCSXS::~_SnpHelloCSXS()
{
    // remove event listener
	InterfacePtr<ICSXSPlugPlugEventHandler> plugPlug(GetExecutionContextSession(), UseDefaultIID());
    if (plugPlug)
    {
        plugPlug->RemovePlugPlugEventListener("hellocsxs", &PlugPlugEventListener, nil);
    }

	InterfacePtr<ICSXSVulcanMessageHandler> vulcanMessage(GetExecutionContextSession(), UseDefaultIID());
	if(vulcanMessage && vulcanListenerAdded)
		vulcanMessage->RemoveMessageListener(&VulcanMessageListener, "com.adobe.indesign");
}

/* 
 * Check if your snippet's preconditions are met here.
 * For this particular snippet there are no preconditions
 * so we always return kTrue.
 */
bool16 _SnpHelloCSXS::CanRun(ISnpRunnableContext* runnableContext)
{
	return kTrue;
}

/* 
 * The main functionality of the snippet. 
 * This is where we create a CSXS event and then send it
 * using PlugPlug. We also attach a message listener so
 * we can catch the message in this snippet too, thus showing 
 * how to send and receive a message using CSXS and PlugPlug.
 */
ErrorCode _SnpHelloCSXS::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kFailure;

	do {
		// prepare some data to send
		PMString csxsEvent;
		csxsEvent.SetCString(kSnipRunHelloCSXSMessage);
		PMString eventData(csxsEvent);
		std::string csxsEventUtf8;
		adobe::detail::to_utf8<char>(csxsEvent.begin(), csxsEvent.end(), std::back_inserter(csxsEventUtf8), adobe::detail::unicode_size_type_<sizeof(UTF16TextChar)>());

		// create CSXSEvent which we will send using plugplug
		ICSXSPlugPlugEventHandler::CSXSEvent idCSXSEvent;
		idCSXSEvent.type = "hellocsxs";
		idCSXSEvent.scope = ICSXSPlugPlugEventHandler::kEventScope_Application; // not sending outside of app
		idCSXSEvent.extensionId = nil;
		idCSXSEvent.data = csxsEventUtf8.c_str();

		if (LocaleSetting::GetLocale().IsProductFS(kInDesignProductFS))
		{
			idCSXSEvent.appId = kIDEnigmaCode; // as defined in ICSXSPlugPlugEventHandler.h
		}
		else
		{
			idCSXSEvent.appId = kICEnigmaCode; // as defined in ICSXSPlugPlugEventHandler.h
		}
		
		// now send the message through PlugPlug
		InterfacePtr<ICSXSPlugPlugEventHandler> plugPlug(GetExecutionContextSession(), UseDefaultIID());
		if (!plugPlug)
		{
            break;
        }

        // we use a boolean flag to avoid adding the event listener more than once
        if (!plugPlugReady)
        {
            plugPlug->AddPlugPlugEventListener(idCSXSEvent.type, &PlugPlugEventListener, nil);
            plugPlugReady = kTrue;
        }

		plugPlug->DispatchPlugPlugEvent(&idCSXSEvent);

		// Now send a message using vulcan messages.
		InterfacePtr<ICSXSVulcanMessageHandler> vulcanMessage(GetExecutionContextSession(), UseDefaultIID());
		if (!vulcanMessage)
		{
			status = kFailure;
			break;
		}

		// Add the listener if not added yet.
		if(!vulcanListenerAdded)
		{
			vulcanListenerAdded = kTrue;
			vulcanMessage->AddMessageListener(&VulcanMessageListener, "com.adobe.indesign");
		}

		// Send the message
		vulcanMessage->SendMessage("com.adobe.indesign", "IDSN", "10.0", kSnipRunHelloCSXSMessage); // not sending outside of app

		status = kSuccess;

	} while(false);

	return status;
}

/*
 * This is the message handler for the CSXS event we dispatch in 
 * _SnpHelloCSXS::Run (above).
 * It displays an information dialog when a message is received.
 */
void _SnpHelloCSXS::PlugPlugEventListener(const ICSXSPlugPlugEventHandler::CSXSEvent* const csxsEvent, void* const context)
{
	CAlert::InformationAlert(PMString(csxsEvent->data)); // data is a key for the string
}

void _SnpHelloCSXS::VulcanMessageListener(const std::string &message)
{
	CAlert::InformationAlert(PMString(message.c_str())); 
}

/*	
 * This is boilerplate code used by all snippets to register an 
 * instance of the snippet with the snippet runner framework.
 */
static _SnpHelloCSXS instance_SnpHelloCSXS;
DEFINE_SNIPPET(_SnpHelloCSXS) 	