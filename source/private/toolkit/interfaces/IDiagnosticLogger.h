//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/private/toolkit/interfaces/IDiagnosticLogger.h $
//  
//  Owner: gxiao 
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
#ifndef __IDiagnosticLogger__
#define __IDiagnosticLogger__

#include "IDiagLoggingAPI.h"

#include "DiagnosticLogID.h"

class ISAXAttributes;

#define kDIAGLOGSTRINGBUFFERSIZE 256
#define kDIAGLOGLINEBUFFERSIZE 2048

/**
	This is logger interface. It implements common logging interface IDiagLoggingAPI.

	@see IDiagLoggingAPI
*/
class IDiagnosticLogger : public IDiagLoggingAPI 
{
public:
	enum { kDefaultIID = IID_IDIAGNOSTICLOGGER };
	
	typedef enum { kUnhandledException, kProtectiveShutdown } AppTerminationState;

	/**
		DiagLogStackItem is used by logger manager to store context information
	*/
	class DiagLogStackItem
	{
	public:
		DiagLogStackItem()
			{}

		DiagLogStackItem(const PMString &context, const clock_t &time)
			: fContext(context), fTimeStamp(time)
			{}

		const PMString &GetContext() const
			{return fContext;}

		const clock_t &GetTimeStamp() const
			{return fTimeStamp;}

		PMString	fContext;
		clock_t 	fTimeStamp;
	};
	
	/**	
		Initialize logger.
	*/
	virtual void InitializeLogger() = 0;

	/**	
		Enable a logger.

		@param enable boolean flag if to enable logger
		@return	the logger with this name
	*/
	virtual void Enable(bool16 enable = kTrue) = 0;

	/**	
		Return if logger is enabled.

		@return	kTrue if logger is enabled
	*/
	virtual bool16 IsEnabled() const = 0;

	/**	
		Return the logger  name.

		@return	PMString the name of logger
	*/
	virtual const PMString GetName() const = 0;

	/**	
		Load logger configuration.

		@param attrs AttributeList which contains configuration data
	*/
	virtual void LoadLoggerConfig(ISAXAttributes * attrs) = 0;

	/**	
		Generate logger configuration.

		@param attrs AttributeList which contains configuration data
	*/
	virtual void GenerateLoggerConfig(IXMLOutStream::AttributeList& attrs) = 0;

	/**
		Handle abnormal application termination.
	*/
	virtual void HandleAbnormalAppTermination(AppTerminationState state) = 0;

	/**	
		Flush logger buffer during idle time. This function will be called from idle task.
		Logger shouldn't perform any long operation in this function.
	*/
	virtual void IdleFlush() = 0;

	/**	
		Reset logger. Not implemented yet.
	*/
	virtual void Reset() = 0;
};

#endif // __IDiagnosticLogger__