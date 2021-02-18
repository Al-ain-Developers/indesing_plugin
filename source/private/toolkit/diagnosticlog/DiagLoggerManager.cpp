//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/private/toolkit/diagnosticlog/DiagLoggerManager.cpp $
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

#include "IDiagLoggerManager.h"

#include "IApplication.h"
#include "IActionManager.h"
#include "IPMStream.h"
#include "IDiagnosticLogger.h"
#include "IDiagLogModifier.h"
#include "IK2ServiceRegistry.h"
#include "IK2ServiceProvider.h"

#include <vector>

#include "DiagnosticLogID.h"

class DiagLoggerManager: public CPMUnknown<IDiagLoggerManager>
{
public:		
	typedef std::vector<IDiagnosticLogger *> Logger;
	typedef std::vector<IDiagLogModifier *> Modifier;

	DiagLoggerManager(IPMUnknown *boss);
	~DiagLoggerManager();

	virtual void EnterContext(const PMString & context, IXMLOutStream::AttributeList& attrs, const void * Param1, const void * Param2);
	virtual void ExitContext(const PMString & context);
	virtual void LogMessage(const PMString & messageType, IXMLOutStream::AttributeList& attrs, const void * Param1);

	virtual void AddLogger(IDiagnosticLogger * log);
	virtual void DeleteLogger(IDiagnosticLogger * log);
	virtual int32 GetNumLoggers() const;
	virtual IDiagnosticLogger * GetNthLogger(int32 index) const;
	virtual IDiagnosticLogger * GetLogger(const PMString & name);

	virtual void Reset();

private:
	Logger fLogs;
	Modifier fModifier;
};


CREATE_PMINTERFACE(DiagLoggerManager, kDiagLoggerManagerImpl)


DiagLoggerManager::DiagLoggerManager(IPMUnknown *boss) : 
	CPMUnknown<IDiagLoggerManager>(boss),
	fModifier()
{

	InterfacePtr<IK2ServiceRegistry> pServices(GetExecutionContextSession(), IID_IK2SERVICEREGISTRY);
	int32 nProviderMax = pServices->GetServiceProviderCount(kDiagLogModifierService);
	for ( int32 i = 0; i < nProviderMax; ++i )
	{
		InterfacePtr<IK2ServiceProvider> pProvider( pServices->QueryNthServiceProvider(kDiagLogModifierService, i));
		if (pProvider)
		{
			IDiagLogModifier * modifier = (IDiagLogModifier *) pProvider->QueryInterface(IID_IDIAGLOGMODIFIER);
			fModifier.push_back(modifier);
		}
	}

	nProviderMax = pServices->GetServiceProviderCount(kDiagnosticLoggerService);
	for ( int32 i = 0; i < nProviderMax; ++i )
	{
		InterfacePtr<IK2ServiceProvider> pProvider( pServices->QueryNthServiceProvider(kDiagnosticLoggerService, i));
		if (pProvider)
		{
			IDiagnosticLogger * logger = (IDiagnosticLogger *) pProvider->QueryInterface(IID_IDIAGNOSTICLOGGER);
			AddLogger(logger);
		}
	}
}


DiagLoggerManager::~DiagLoggerManager()
{
	std::vector<IDiagLogModifier *>::iterator modIter = fModifier.begin();
	while (modIter != fModifier.end()) 
	{
		IDiagLogModifier * modifier = *modIter;
		++modIter;
		
		modifier->Release();
	}

	std::vector<IDiagnosticLogger *>::iterator iter = fLogs.begin();
	while (iter != fLogs.end()) 
	{
		IDiagnosticLogger * log = *iter;
		++iter;
		
		log->Release();
	}

}


void DiagLoggerManager::EnterContext(const PMString & context, IXMLOutStream::AttributeList& attrs, const void * Param1, const void * Param2)
{
	ASSERT(context.IsEmpty() == kFalse);

	std::vector<IDiagLogModifier *>::iterator modIter = fModifier.begin();
	while (modIter != fModifier.end()) 
	{
		IDiagLogModifier * modifier = *modIter;
		modifier->EnterContext(context, attrs, Param1, Param2);

		++modIter;
	}

	std::vector<IDiagnosticLogger *>::iterator iter = fLogs.begin();
	while (iter != fLogs.end())
	{
		IDiagnosticLogger * log = *iter;
		
		if (log->IsEnabled())
			log->EnterContext(context, attrs, Param1, Param2);

		++iter;
	}
}


void DiagLoggerManager::ExitContext(const PMString & context)
{
	ASSERT(context.IsEmpty() == kFalse);

	std::vector<IDiagLogModifier *>::iterator modIter = fModifier.begin();
	while (modIter != fModifier.end()) 
	{
		IDiagLogModifier * modifier = *modIter;
		modifier->ExitContext(context);

		++modIter;
	}

	std::vector<IDiagnosticLogger *>::iterator iter = fLogs.begin();
	while (iter != fLogs.end())
	{
		IDiagnosticLogger * log = *iter;
		
		if (log->IsEnabled())
			log->ExitContext(context);

		++iter;
	}
}


void DiagLoggerManager::LogMessage(const PMString & messageType, IXMLOutStream::AttributeList& attrs, const void * Param1)
{
	std::vector<IDiagLogModifier *>::iterator modIter = fModifier.begin();
	while (modIter != fModifier.end()) 
	{
		IDiagLogModifier * modifier = *modIter;
		modifier->LogMessage(messageType, attrs, Param1);

		++modIter;
	}

	std::vector<IDiagnosticLogger *>::iterator iter = fLogs.begin();
	while (iter != fLogs.end())
	{
		IDiagnosticLogger * log = *iter;
		
		if (log->IsEnabled())
			log->LogMessage(messageType, attrs, Param1);

		++iter;
	}
}


void DiagLoggerManager::AddLogger(IDiagnosticLogger * log)
{
	ASSERT(log != nil);
	ASSERT(std::find(fLogs.begin(), fLogs.end(), log) == fLogs.end());

	fLogs.push_back(log);
}


void DiagLoggerManager::DeleteLogger(IDiagnosticLogger * log)
{
	ASSERT(log != nil);

	std::vector<IDiagnosticLogger *>::iterator iter = fLogs.begin();
	while (iter != fLogs.end())
	{
		IDiagnosticLogger * existingLog = *iter;
		
		if (log == *iter)
		{
			fLogs.erase(iter);
			log->Release();
			break;
		}

		++iter;
	}
}


int32 DiagLoggerManager::GetNumLoggers() const
{
	return static_cast<int32>(fLogs.size());
}


IDiagnosticLogger * DiagLoggerManager::GetNthLogger(int32 index) const
{
	ASSERT(index < fLogs.size());
	
	return fLogs[index];
}


IDiagnosticLogger * DiagLoggerManager::GetLogger(const PMString & name)
{
	std::vector<IDiagnosticLogger *>::iterator iter = fLogs.begin();
	while (iter != fLogs.end())
	{
		IDiagnosticLogger * log = *iter;
		
		if (log->GetName() == name)
			return log;

		++iter;
	}
	
	return nil;
}


void DiagLoggerManager::Reset()
{
}
