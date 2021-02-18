//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IScriptObjectMgr.h $
//  
//  Owner: Jonathan W. Brown
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __IScriptObjectMgr__
#define __IScriptObjectMgr__

#include "ScriptingID.h"

class IScriptEventTarget ;
class IScriptObjectParent ;

/** 
	Manages non-persistent script objects that are created within the script
	object hierarchy of the database whose boss aggregates this interface.
	The main purpose is to ensure that they are properly deleted when the
	database is closed.
	@see IScriptObjectParent
*/  
class IScriptObjectMgr : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISCRIPTOBJECTMGR } ;

	/**	Add an object to the manager's care */
	virtual ErrorCode AddObject( IScriptObjectParent* scriptObjectParent ) = 0 ;

	/**	Remove an object from the manager (returns kFailure if not found) */
	virtual ErrorCode RemoveObject( IScriptObjectParent* scriptObjectParent ) = 0 ;

	/** Release all objects */
	virtual void ReleaseAllObjects() = 0 ;

	/** Query an interface to store event target data for this proxy script object */
	virtual IScriptEventTarget* QueryProxyScriptObjectEventTargetBoss( const IScriptObjectParent* scriptObjectParent ) = 0 ;
} ;

#endif // __IScriptObjectMgr__
