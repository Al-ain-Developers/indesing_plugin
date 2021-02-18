//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/private/interfaces/testing/IQAMessageUtils.h $
//  
//  Owner: Kristina Roberts
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

#pragma once
#ifndef __IQAMessageUtils__
#define __IQAMessageUtils__
//________________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________________

#include "TestID.h"
#include "IPMUnknown.h"

//================================================================================================

class BaseTestMessage;
class BenchInfo;
class IQATestLog;
class ITestSuite;
class QAFile;
class QATest;

//________________________________________________________________________________________________
//	CLASS DECLARATION
//________________________________________________________________________________________________
class IQAMessageUtils : public IPMUnknown
{
	//____________________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_IQAMESSAGEUTILS };
		
		//returns a non-refcounted ptr to the IQATestLog just created;
		virtual IQATestLog*	EnableLog(const QAFile &file, const PMString &key, const ClassID &cid, bool16* newLog = nil) = 0;
		virtual IQATestLog*	GetLog(const PMString &key) = 0;
		
		virtual PMString GetQALogDirectory() = 0;
		
		virtual void	ClearLogs(void) = 0;
		virtual void	ClearLog(const PMString &key) = 0;
		
		virtual void	Message(const PMString &msg) = 0;
		virtual void	Message(BaseTestMessage *msg) = 0;
		virtual void	MessageWithFilter(void *msg, PMString filter) = 0;
		virtual void	MessageWithFilter(void *msg, const ClassID &filter) = 0;
		
		virtual void	Error( const char* formatstring, ...) = 0;
		virtual void	LogAssert(const char* formatstring, ...) = 0;
		virtual	void	Warning( const char* formatstring, ...) = 0;
		virtual	void	FatalError( const char* formatstring, ...) = 0;
		virtual	void	Comment( const char* formatstring, ...) = 0;
		virtual	void	ResultFile( PMString& errorInfoString ) = 0;
		virtual	void	Alert( const char* formatstring, ...) = 0;
		virtual	void	Step( const char* formatstring, ...) = 0;

		virtual	void	LogString( PMString formattingInfo, const char* formatstring, ...) = 0;
		
		virtual	void	ErrorAssert( bool16 condition, const char* formatstring, ...) = 0;
		virtual	void	WarningAssert( bool16 condition, const char* formatstring, ...) = 0;
		virtual	void	FatalErrorAssert( bool16 condition, const char* formatstring, ...) = 0;
				
		virtual	ErrorCode	Error( ErrorCode error ) = 0;
		virtual	ErrorCode	Warning( ErrorCode error ) = 0;
		virtual	ErrorCode	FatalError( ErrorCode error ) = 0;
		
		virtual void	WriteSeparatorToLogs(void) = 0;
		
		virtual void		PushMessageHeader(const PMString &head) = 0;
		virtual void		PushMessageHeader(const char* formatstring, ...) = 0;
		virtual void		PopMessageHeader(void) = 0;
		
		virtual bool16	XMLLogBeforeStep (const PMString &suiteName, const PMString &testName, const PMString &testPath) = 0;
		virtual void	XMLLogAfterStep (bool16 wasTest) = 0;

		virtual void LogBenchmarkData(BenchInfo& benchInfo) = 0;
		virtual void LogSuiteBegin(ITestSuite* suite) = 0;
		virtual void LogSuiteEnd(bool16 suiteWasCancelled) = 0;
		virtual void LogTestBegin(ITestSuite* suite, QATest* test) = 0;
		virtual void LogTestEnd(ITestSuite* suite, QATest* test, bool16 skipped,
			bool16 logTime, const PMReal& startTime, bool16 benchmarksEnabled) = 0;
};

#endif // __IQAMessageUtils__