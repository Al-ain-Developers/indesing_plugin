//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/itksamples/detailswitchlogger/DswLgrDiagLogModifier.cpp $
//  
//  Owner: InDesign Developer Technologies
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
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#include "VCPlugInHeaders.h"
#include "ICreateMCFrameData.h"
#include "IDiagLogModifier.h"
#include "IDiagnosticLog.h"
#include "IDiagLogConfigManager.h"
#include "DswLgrID.h"

/** 
	A logger modifier service provider that implements IDiagLogModifier. Each logger modifier is called by the application's
	logger dispatcher component (see Diagnostic Logger technote about the application's logging service) before
	the log being sent to the a logger provider (IDiagnosticLogger) for output.  The IDiagLogModifier and IDiagnosticLogger
	both inherit from the same IDiagLoggingAPI, and they both implements the EnterContext() method, which is called by the 
	dispatcher when certain context has happened.  The application dispatcher component passes the same parameters into the
	IDiagLogModifier::EnterContext and IDiagnosticLogger::EnterContext.  Since modifier is called before the logger, it
	gets the chance to "modify" the parameter, which is essentially the log output data.
	
	In this sample code, 2 major extensible possibilities are shown:
	1. Event driven configuration: to change the configuration triggerred by the receiving of certain event. 
		This is useful when you want minimum logging detail until the event you're interested has happened, then you can turn 
		on more things to watch. For example, you might only want to start logging in maximum when certain menu action happens.
	
	
	2. Customized logging output information: to customize the way log is output. 
		Some events are passed in some useful object pointers in the IDiagLogModifier::EnterContext() that you can get more 
		information out of it.  For example, the Command context is passed in an ICommand * as its Param1 parameter.  You can 
		use it to ask for other information that is not already appended in the attribute lists, or you can use the pointer to 
		query other interface on the same command boss for more information.  Then you can re-format the attributes to the way 
		you like, add or remove attributes from the list to your like. See IDiagLoggingAPI for information on what extra parameters
		are pssed in for each context.
	

    @ingroup detailswitchlogger
	@see IDiagLoggingAPI
	@see IDiagnosticLogger
	@see IDiagLogModifier	
*/
class DswLgrDiagLogModifier : public CPMUnknown<IDiagLogModifier>
{
public:		
	/** ctor */
	DswLgrDiagLogModifier(IPMUnknown *boss);
	/** dtor */
	~DswLgrDiagLogModifier();

	/**
		Enter pre-defined context.  Each context will be accompanied by an attribute list that is pre-defined by the logging 
		dispatcher.  Your implementation of this method can change the way log is output cause the same context and attribute
		list will be passed into a logger service for output.  You can access every element in the attribute list, i.e., you can
		add/remove/modify any element from the list.  Use Param1 and Param2 when available to get more information about the
		current context.
		
		To see this modifier in action, create a document, select the text tool, create a text box on the document, you should observe
		the log output for kCreateMultiColumnItemCmdBoss, you will see <Command Status: xxx> and <Frame orientation is xxx> trace append
		to the log for the command boss.  Also execute the Layout>Pages>Add Page menu, you should see a log message saying 
		<DswLgrDiagLogModifier:===== log detail level is about to change to maximum =====>, then after the current context is exit, you
		will notice the log level is changed to maximum and the kLButtonUp event will be logged if previously not enabled.

		@param context The name of context ("Action", "Command", etc.).
		@param attrs A reference to attribute list that contains the name and value pairs about context.
		@param Param1 A generic pointer associated with context. See IDiagLoggingAPI.h
		@param Param2 A generic pointer associated with context. See IDiagLoggingAPI.h
	*/
	virtual void EnterContext(const PMString & context, IXMLOutStream::AttributeList& attrs, const void * Param1 = nil, const void * Param2 = nil);
	/**
		Exit pre-defined context.

		@param context The name of context ("action", "command", etc.). It should match the context in 
		EnterContext method.
	*/
	virtual void ExitContext(const PMString & context);
	/**
		Log a message.  This is for message event as discussed in the Diagnostic Logger technote. The usage for message
		is similar to the context except the message does not have enter/exit pairing.

		@param messageType The name of message ("tracking", "transaction", etc.).
		@param attrs A reference to attribute list that contains the name and value pairs about message.
		@param Param1 A generic pointer associated with message. See following table
	*/
	virtual void LogMessage(const PMString & messageType, IXMLOutStream::AttributeList& attrs, const void * Param1);
private:
	bool	fNeedToConfigure;
};

CREATE_PMINTERFACE(DswLgrDiagLogModifier, kDswLgrDiagLogModifierImpl)

DswLgrDiagLogModifier::DswLgrDiagLogModifier(IPMUnknown *boss) : 
	CPMUnknown<IDiagLogModifier>(boss),
	fNeedToConfigure(kFalse)
{
}


DswLgrDiagLogModifier::~DswLgrDiagLogModifier()
{
}


/* EnterContext
 */

void DswLgrDiagLogModifier::EnterContext(const PMString & context, IXMLOutStream::AttributeList& attrs, const void * Param1, const void * Param2)
{
	for (int32 i=0; i<attrs.size(); i++)
	{
	    IXMLOutStream::Attribute aAttr = attrs[i];
		PMString name(aAttr.GetName());
		PMString value(aAttr.GetValue());
		if (context == PMString(kDswLgrCommandContext) && name == PMString(kDswLgrClsIDAttrName) && (value == PMString(kDswLgrClsIDAttrShortValue) || (value == PMString(kDswLgrClsIDAttrLongValue))))
		{
			bool isDone = ((ICommand*)Param1)->IsDone();
	    	IXMLOutStream::Attribute myAttr;
	    	myAttr.fName = WideString("Command Status:");
	    	if (isDone)
				myAttr.fValue = WideString("TRUE");
	    	else
	    		myAttr.fValue = WideString("FALSE");
	    		
			attrs.push_back(myAttr);
			
			InterfacePtr<ICreateMCFrameData>	cmdData((ICommand*)Param1, UseDefaultIID());
			if (cmdData)
			{
				myAttr.fName = WideString("Frame orientation is ");
				if (cmdData->GetOrientation() == ICreateMCFrameData::kHorizontal)
					myAttr.fValue = WideString("horizontal");
				else
					myAttr.fValue = WideString("vertical");
				attrs.push_back(myAttr);
			}
			
			// as you can see, you can also modify the passed in attrs, which is the default attributes list to be logged, you can
			// re-arrange the order or add/delete to the list to customize your output.
		}

		if (context == PMString(kDswLgrActionContext) && name == PMString(kDswLgrActIDAttrName) && (value == PMString(kDswLgrActIDAttrShortValue) || (value == PMString(kDswLgrActIDAttrLongValue))))
		{
			fNeedToConfigure = kTrue;
	    	IXMLOutStream::Attribute modifierAttr;
	    	modifierAttr.fName = WideString("DswLgrDiagLogModifier:");
			modifierAttr.fValue = WideString("===== log detail level is about to change to maximum =====");	    		
			attrs.push_back(modifierAttr);
		}
	}
}

/* ExitContext
 */
void DswLgrDiagLogModifier::ExitContext(const PMString & context)
{
	do 
	{
		InterfacePtr<IDiagnosticLog> iDiagnosticLog(GetExecutionContextSession(), UseDefaultIID());
		ASSERT(iDiagnosticLog != nil);
		if (iDiagnosticLog == nil){
			break;
		}
		InterfacePtr<IDiagLogConfigManager> iConfigManager(iDiagnosticLog->QueryDiagLogConfigManager());
		ASSERT(iConfigManager != nil);
		if (iConfigManager == nil){
			break;
		}

		if (fNeedToConfigure)
		{
			fNeedToConfigure = kFalse;
			// switch to maximum detail
			iConfigManager->SetLoggingLevel(IDiagLogConfigManager::kDiagLogMaximum);
			// this is just randomly picked to show some more preference changes.
			iConfigManager->SetCategoryLogging(IDiagLogConfigManager::kDiagLogEvents, kTrue);
			iConfigManager->SetLogEvent(PMString(kDswLgrKeyDnEvent), kTrue);	// available event names are in the configuration file
			iConfigManager->Save();
			iConfigManager->Load();			    		
		}
	} while (false);
}

/* LogMessage
 */
void DswLgrDiagLogModifier::LogMessage(const PMString & messageType, IXMLOutStream::AttributeList& attrs, const void * Param1)
{
}
