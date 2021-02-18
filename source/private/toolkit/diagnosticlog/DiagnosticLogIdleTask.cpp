//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/private/toolkit/diagnosticlog/DiagnosticLogIdleTask.cpp $
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

// Interface includes:
#include "IDiagnosticLog.h"
#include "IDiagLoggerManager.h"
#include "IDiagnosticLogger.h"

// General includes:
#include "CIdleTask.h"

// Project includes:
#include "DiagnosticLogID.h"


class DiagnosticLogIdleTask : public CIdleTask
{
public:
	DiagnosticLogIdleTask(IPMUnknown* boss);

	virtual	~DiagnosticLogIdleTask();

    virtual uint32 RunTask( uint32 appFlags, IdleTimer* timeCheck);

    virtual const char* TaskName();

private:
	IDiagLoggerManager * fLoggerManager;

	int32 fStartLogger;
	int32 fLoggerCount;
};

CREATE_PMINTERFACE(DiagnosticLogIdleTask, kDiagnosticLogIdleTaskImpl)

DiagnosticLogIdleTask::DiagnosticLogIdleTask(IPMUnknown* boss) :
	CIdleTask(boss)
	,fStartLogger(0)
{
	ISession* session = GetExecutionContextSession();
	ASSERT(session != nil);
	InterfacePtr<IDiagnosticLog> iDiagnosticLog(session, UseDefaultIID());
	fLoggerManager = iDiagnosticLog->QueryDiagLoggerManager();
	fLoggerCount = fLoggerManager->GetNumLoggers();
}

DiagnosticLogIdleTask::~DiagnosticLogIdleTask()
{
	fLoggerManager->Release();
}

//----------------------------------------------------------------------------------------
// DiagnosticLogIdleTask::RunTask
//----------------------------------------------------------------------------------------

uint32 DiagnosticLogIdleTask::RunTask( uint32 appFlags, IdleTimer* timeCheck)
{
	if ((*timeCheck)() > 5)
	{
		for (int32 i=0; i<fLoggerCount; i++)
		{
			IDiagnosticLogger * logger = fLoggerManager->GetNthLogger(fStartLogger);
			logger->IdleFlush();

			fStartLogger++;
			if (fStartLogger == fLoggerCount)
				fStartLogger = 0;

			if ((*timeCheck)() < 5)
				break;
		}
	}

	return 5000; // 5 seconds
}

const char* DiagnosticLogIdleTask::TaskName()
{
     return "DiagnosticLog Idle Task";
}
