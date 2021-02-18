//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IScriptEngine.h $
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
#ifndef __IScriptEngine__
#define __IScriptEngine__

#include "IPMUnknown.h"
#include "ScriptingID.h"
#include "RequestContext.h"

class IScriptRequestData ;
class IScriptManager ;

using namespace ScriptInfo ;

/**
	Every scripting client must implement this interface to provide
	basic information about support for its scripting engine.

	Clients with a single engine may aggregate onto their IScriptManager
	boss. Clients with multiple engines will need a separate boss.
*/
class IScriptEngine : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISCRIPTENGINE } ;

	/**
		Tells the script engine to install
	*/
	virtual	ErrorCode			Install() = 0 ;
	/**
		Tells the script engine to uninstall
	*/
	virtual	ErrorCode			UnInstall() = 0 ;

	/**
		@return this engine's current request context for processing a script
	*/
	virtual EngineContext		GetRequestContext() const = 0 ;

	/**
		@return the script manager for this engine
	*/
	virtual IScriptManager*		QueryScriptManager() const = 0 ;

	/**
		@return a script event data boss
	*/
	virtual IScriptRequestData*	CreateScriptRequestData() /*const*/ = 0 ;

	/**
		@return this engine's name
	*/
	virtual PMString			GetName() const = 0 ;

	/**
		@return whether a script is running in this engine
	*/
	virtual bool16				IsScriptActive() const = 0 ;
	/**
		Increment the number of active scripts in this engine
	*/
	virtual void				IncrementActiveScriptCount() = 0 ;
	/**
		Decrement the number of active scripts in this engine
	*/
	virtual void				DecrementActiveScriptCount() = 0 ;

	/**
		@return whether alerts should be displayed when this engine is processing requests
	*/
	virtual bool16				GetShowAlerts() const = 0 ;
	/**
		@return whether dialogs should be displayed when this engine is processing requests
	*/
	virtual bool16				GetShowDialogs() const = 0 ;
} ;

#endif
