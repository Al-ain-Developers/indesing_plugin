//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/private/toolkit/interfaces/IDiagLoggerManager.h $
//  
//  Owner: rbriggs 
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
#ifndef __IDiagLoggerManager__
#define __IDiagLoggerManager__

#include "IDiagLoggingAPI.h"

#include "DiagnosticLogID.h"

class IDiagnosticLogger;
class IDiagLogModifier;

/**
	This interface manages each individual logger. It implements common logging 
	interface IDiagLoggingAPI.

	@see IDiagLoggingAPI
*/
class IDiagLoggerManager : public IDiagLoggingAPI 
{
public:
	enum { kDefaultIID = IID_IDIAGLOGGERMANAGER };

	// Logger management
	/**	
		Add a logger.

		@param log a logger to be added
	*/
	virtual void AddLogger(IDiagnosticLogger * log) = 0;
	/**	
		Delete a logger.

		@param log a logger to be deleted
	*/
	virtual void DeleteLogger(IDiagnosticLogger * log) = 0;
	/**	
		Get then number of loggers.

		@return	the total count of loggers
	*/
	virtual int32 GetNumLoggers() const = 0;
	/**	
		Return the Nth logger.

		@param index the logger
		@return	the logger with this index
	*/
	virtual IDiagnosticLogger * GetNthLogger(int32 index) const = 0;
	/**	
		Return the logger given its name.

		@param name string name of logger. Text logger has name "text"
		@return	the logger with this name
	*/
	virtual IDiagnosticLogger * GetLogger(const PMString & name) = 0;

	// Utility
	/**	
		Tell each logger to reset. Not implemented yet
	*/
	virtual void Reset() = 0;
};

#endif // __IDiagLoggerManager__