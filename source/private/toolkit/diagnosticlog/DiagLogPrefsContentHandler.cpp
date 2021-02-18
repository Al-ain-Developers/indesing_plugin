//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/private/toolkit/diagnosticlog/DiagLogPrefsContentHandler.cpp $
//  
//  Owner:
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

#include "CSAXContentHandler.h"

// Interface includes:
#include "IDiagLogConfigManager.h"
#include "IDiagnosticLog.h"
#include "ISAXAttributes.h"
#include "IDiagnosticLog.h"
#include "IDiagLoggerManager.h"
#include "IDiagnosticLogger.h"

#include "DiagnosticLogID.h"

#include <vector>
#include <sstream>
//#include <iomanip>

// ===================================================================================
//	Parser Classes		
// ===================================================================================

class DiagLogPrefsContentHandler : public CSAXContentHandler
{
public:
	DiagLogPrefsContentHandler(IPMUnknown* boss);
	virtual ~DiagLogPrefsContentHandler();

	virtual void StartElement(const WideString& uri, const WideString& localname, const WideString& qname, ISAXAttributes* attrs);
	virtual void EndElement(const WideString& uri, const WideString& localname, const WideString& qname);

protected:

	void BeginChildren(const WideString& qname);
	void EndChildren();
	
	void ParseEventType(ISAXAttributes* attrs);
	void ParseLogging(ISAXAttributes* attrs);
	void ParseIDDataBase(ISAXAttributes* attrs);
	void ParseCategory(ISAXAttributes* attrs);
	void ParseIDList(ISAXAttributes* attrs);
	void ParseFileLocation(ISAXAttributes* attrs);
	void ParseLogger(ISAXAttributes* attrs);

private:
	IDiagLogConfigManager::ListType fListType;
	IDiagLogConfigManager::DiagLogCategory fCategory;
	PMString fParentElement;
	mutable std::vector<PMString> fStack;
};

//========================================================================================
// METHODS DiagLogPrefsContentHandler
//========================================================================================

CREATE_PMINTERFACE(DiagLogPrefsContentHandler, kDiagLogPrefsContentHandlerImpl)


//----------------------------------------------------------------------------------------
// DebugPrefsDocumentHandler::DebugPrefsDocumentHandler
//----------------------------------------------------------------------------------------

DiagLogPrefsContentHandler::DiagLogPrefsContentHandler(IPMUnknown* boss) :
	CSAXContentHandler(boss)
{
}


//----------------------------------------------------------------------------------------
// DebugPrefsDocumentHandler::~DebugPrefsDocumentHandler
//----------------------------------------------------------------------------------------

DiagLogPrefsContentHandler::~DiagLogPrefsContentHandler()
{
}

//----------------------------------------------------------------------------------------
// DiagLogPrefsContentHandler::StartElement
//----------------------------------------------------------------------------------------

void DiagLogPrefsContentHandler::StartElement(const WideString& uri, const WideString& localname, const WideString& qname, ISAXAttributes* attrs)
{	
	if (qname == WideString("eventtype"))
		ParseEventType(attrs);

	else if (qname == WideString("logging"))
		ParseLogging(attrs);

	else if (qname == WideString("iddatabase"))
		ParseIDDataBase(attrs);

	else if (qname == WideString("category"))
		ParseCategory(attrs);

	else if (qname == WideString("includelist") || qname == WideString("excludelist"))
	{
		if (qname == WideString("includelist"))
			fListType = IDiagLogConfigManager::kIncludeList;
		else
			fListType = IDiagLogConfigManager::kExcludeList;
	}

	else if (qname == WideString("id"))
		ParseIDList(attrs);

	else if (qname == WideString("filelocation"))
		ParseFileLocation(attrs);

	else if (qname == WideString("logger"))
		ParseLogger(attrs);

	else if (qname != WideString("DiagnosticLogConfiguration") && qname != WideString("loggers"))
		ASSERT_FAIL(FORMAT_ARGS("Ignoring the unrecognized element named %s", PMString(qname).GetUTF8String().c_str()));

	// --- Save the current state
	this->BeginChildren(qname);
}


//----------------------------------------------------------------------------------------
// DiagLogPrefsContentHandler::EndElement
//----------------------------------------------------------------------------------------

void DiagLogPrefsContentHandler::EndElement(const WideString& uri, const WideString& localname, const WideString& qname )
{
	this->EndChildren();
}


//----------------------------------------------------------------------------------------
// DiagLogPrefsContentHandler::BeginChildren
//----------------------------------------------------------------------------------------

void DiagLogPrefsContentHandler::BeginChildren(const WideString& qname)
{
	fStack.push_back(fParentElement);
	fParentElement = qname;
}


//----------------------------------------------------------------------------------------
// DiagLogPrefsContentHandler::EndChildren
//----------------------------------------------------------------------------------------

void DiagLogPrefsContentHandler::EndChildren()
{
	fParentElement = fStack.back();
	fStack.pop_back();
}

	
//----------------------------------------------------------------------------------------
// DebugPrefsDocumentHandler::ParseTraceCategory
//----------------------------------------------------------------------------------------

void DiagLogPrefsContentHandler::ParseFileLocation(ISAXAttributes* attrs)
{
	ASSERT(fParentElement == PMString("DiagnosticLogConfiguration"));
	InterfacePtr<IDiagLogConfigManager> iDiagLogConfig(this, UseDefaultIID());

	iDiagLogConfig->SetOutputPath(GetAttributeString(attrs, "outputpath"));
}


//----------------------------------------------------------------------------------------
// DebugPrefsDocumentHandler::ParseTraceCategory
//----------------------------------------------------------------------------------------

void DiagLogPrefsContentHandler::ParseEventType(ISAXAttributes* attrs)
{
	ASSERT(fParentElement == PMString("category"));
	InterfacePtr<IDiagLogConfigManager> iDiagLogConfig(this, UseDefaultIID());
	iDiagLogConfig->SetLogEvent(GetAttributeString(attrs, "name"), GetAttributeBool(attrs, "enabled"));
}


//----------------------------------------------------------------------------------------
// DiagLogPrefsContentHandler::ParseTraceSink
//----------------------------------------------------------------------------------------

void DiagLogPrefsContentHandler::ParseLogging(ISAXAttributes* attrs)
{
	ASSERT(fParentElement == PMString("DiagnosticLogConfiguration"));
	InterfacePtr<IDiagLogConfigManager> iDiagLogConfig(this, UseDefaultIID());

	iDiagLogConfig->SetLogging(GetAttributeBool(attrs, "enabled"));
	iDiagLogConfig->SetLoggingTimeInfo(GetAttributeBool(attrs, "timeinfo"));
	iDiagLogConfig->SetLoggingTimeThreshold(GetAttributeInt(attrs, "timethreshold"));

	IDiagLogConfigManager::DiagLoggingLevel level = IDiagLogConfigManager::kDiagLogMinimum;
	PMString name = GetAttributeString(attrs, "level");
	if (name == PMString("kDiagLogMinimum"))
		level = IDiagLogConfigManager::kDiagLogMinimum;
	else if (name == PMString("kDiagLogMedium"))
		level = IDiagLogConfigManager::kDiagLogMedium;
	else if (name == PMString("kDiagLogMaximum"))
		level = IDiagLogConfigManager::kDiagLogMaximum;
	else
		ASSERT_FAIL(FORMAT_ARGS("Unknown logging level %s", name.GetUTF8String().c_str()));
	iDiagLogConfig->SetLoggingLevel(level);
}


//----------------------------------------------------------------------------------------
// DiagLogPrefsContentHandler::ParseIDDataBase
//----------------------------------------------------------------------------------------

void DiagLogPrefsContentHandler::ParseIDDataBase(ISAXAttributes* attrs)
{
	ASSERT(fParentElement == PMString("DiagnosticLogConfiguration"));
	InterfacePtr<IDiagLogConfigManager> iDiagLogConfig(this, UseDefaultIID());

	iDiagLogConfig->SetIDDatabaseName(GetAttributeString(attrs, "name"));
	iDiagLogConfig->SetLoadIDDatabase(GetAttributeBool(attrs, "load"));
}


//----------------------------------------------------------------------------------------
// DiagLogPrefsContentHandler::ParseBreakOnAsserts
//----------------------------------------------------------------------------------------

void DiagLogPrefsContentHandler::ParseCategory(ISAXAttributes* attrs)
{
	ASSERT(fParentElement == PMString("logging"));
	InterfacePtr<IDiagLogConfigManager> iDiagLogConfig(this, UseDefaultIID());

	PMString name = GetAttributeString(attrs, "name");
	if (name == PMString("kDiagLogAction"))
		fCategory = IDiagLogConfigManager::kDiagLogAction;
	else if (name == PMString("kDiagLogCommand"))
		fCategory = IDiagLogConfigManager::kDiagLogCommand;
	else if (name == PMString("kDiagLogIdleTask"))
		fCategory = IDiagLogConfigManager::kDiagLogIdleTask;
	else if (name == PMString("kDiagLogObserver"))
		fCategory = IDiagLogConfigManager::kDiagLogObserver;
	else if (name == PMString("kDiagLogResponder"))
		fCategory = IDiagLogConfigManager::kDiagLogResponder;
	else if (name == PMString("kDiagLogEvents"))
		fCategory = IDiagLogConfigManager::kDiagLogEvents;
	else if (name == PMString("kDiagLogTracking"))
		fCategory = IDiagLogConfigManager::kDiagLogTracking;
	else if (name == PMString("kDiagLogTransaction"))
		fCategory = IDiagLogConfigManager::kDiagLogTransaction;
	else if (name == PMString("kDiagLogMemoryPurge"))
		fCategory = IDiagLogConfigManager::kDiagLogMemoryPurge;
	else if (name == PMString("kDiagLogGlobalErrorState"))
		fCategory = IDiagLogConfigManager::kDiagLogGlobalErrorState;
	else if (name == PMString("kDiagLogTextDamageMark"))
		fCategory = IDiagLogConfigManager::kDiagLogTextDamageMark;
	else
		ASSERT_FAIL(FORMAT_ARGS("Unknown category %s", name.GetUTF8String().c_str()));

	bool16 enabled = GetAttributeBool(attrs, "enabled");
	iDiagLogConfig->SetCategoryLogging(fCategory, enabled);
}

//----------------------------------------------------------------------------------------
// DiagLogPrefsContentHandler::ParseIDList
//----------------------------------------------------------------------------------------

void DiagLogPrefsContentHandler::ParseIDList(ISAXAttributes* attrs)
{
	ASSERT(fParentElement == PMString("includelist") || fParentElement == PMString("excludelist"));

	PMString hexValueString = GetAttributeString(attrs, "value");
	std::string src(hexValueString.GetUTF8String().c_str());
	std::istringstream iStream(src);
	
	uint32 intVal;
	iStream >> std::hex >> intVal;	

	InterfacePtr<IDiagLogConfigManager> iDiagLogConfig(this, UseDefaultIID());
	iDiagLogConfig->AddCategoryList(fCategory, fListType, intVal);
}

//----------------------------------------------------------------------------------------
// DiagLogPrefsContentHandler::ParseLogger
//----------------------------------------------------------------------------------------

void DiagLogPrefsContentHandler::ParseLogger(ISAXAttributes* attrs)
{
	ASSERT(fParentElement == PMString("loggers"));

	PMString name = GetAttributeString(attrs, "name");
	InterfacePtr<IDiagnosticLog> iDiagnosticLog(GetExecutionContextSession(), UseDefaultIID());
	InterfacePtr<IDiagLoggerManager> iLoggerManager(iDiagnosticLog->QueryDiagLoggerManager());
	IDiagnosticLogger * logger = iLoggerManager->GetLogger(name);
	if (logger)
		logger->LoadLoggerConfig(attrs);
}
