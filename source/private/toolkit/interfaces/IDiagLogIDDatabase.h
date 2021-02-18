//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/private/toolkit/interfaces/IDiagLogIDDatabase.h $
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
#ifndef __IDiagLogIDDatabase__
#define __IDiagLogIDDatabase__

#include "IPMUnknown.h"

#include "DiagnosticLogID.h"

/**
	This interface manages ID database in DiagnosticLog. Database is used to 
	translate a numeric ID value into human readable string. For example, class 
	ID value 257 is tranlated into kSessionBoss.
*/
class IDiagLogIDDatabase: public IPMUnknown 
{
public:
	enum { kDefaultIID = IID_IDIAGLOGIDDATABASE };

	/**	
		Build ID database. This function only create database in debug build since
		all ID string does not exist in release build.
	*/
	virtual void BuildIDDatabase() = 0;

	/**	
		Load ID database. The name and path of ID database are specified in 
		configuration file.

		@see IDiagLogConfigManager
	*/
	virtual void LoadIDDatabase() = 0;

	/**	
		Return if database is loaded in current session.

		@return	kTrue if database is loaded
	*/
	virtual bool16 IsDatabaseLoaded() = 0;

	/**	
		Add an ID into database.

		@param idSpace the space which this ID belongs to
		@param id value of the ID 
		@param idName string representation of this ID 
	*/
	virtual void AddID(int32 idSpace, int32 id, const char * idName) = 0;

	/**	
		Retrieve ID string from database.

		@param idSpace the space which this ID belongs to
		@param id value of the ID 
		@return	pointer to string representation of this ID
	*/
	virtual char * FindID(int32 idSpace, int32 id) = 0;
};

#endif // __IDiagLogIDDatabase__