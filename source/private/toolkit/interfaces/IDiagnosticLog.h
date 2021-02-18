//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/private/toolkit/interfaces/IDiagnosticLog.h $
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
#ifndef __IDiagnosticLog__
#define __IDiagnosticLog__

#include "IPMUnknown.h"
#include "DiagnosticLogID.h"

class IDiagLogConfigManager;
class IDiagLoggerManager;

/**
	Main interface to access function in DiagnosticLog.

    There is only ever one instance of IDiagnosticLog, and you can get a reference 
	to it by querying the session (ISession, off kSessionBoss), for example:
	<Pre>
	InterfacePtr<IDiagnosticLog> iDiagLog(GetExecutionContextSession(), IID_IDIAGNOSTICLOG);
	</Pre>
*/
class IDiagnosticLog: public IPMUnknown 
{
public:
	enum { kDefaultIID = IID_IDIAGNOSTICLOG };

	/**	
		Return a reference to IDiagLogConfigManager.

		@return	IDiagLogConfigManager * the configuration manager of DiagnosticLog
		@see IDiagLogConfigManager
	*/
	virtual IDiagLogConfigManager * QueryDiagLogConfigManager() = 0;

	/**	
		Return a reference to IDiagLoggerManager.

		@return	IDiagLoggerManager * the logger manager of DiagnosticLog
		@see IDiagLoggerManager
	*/
	virtual IDiagLoggerManager * QueryDiagLoggerManager() = 0;
};

#endif // __IDiagnosticLogSession__