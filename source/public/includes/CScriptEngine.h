//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CScriptEngine.h $
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
#ifndef __CSCRIPTENGINE__
#define __CSCRIPTENGINE__

#include "CPMUnknown.h"
#include "IScriptEngine.h"

/**
	Base implementation for IScriptEngine. May be used as is for most clients with a single 
	engine aggregated onto their IScriptManager boss. Clients with multiple engines will need 
	a separate boss, and will need to override at least QueryScriptManager() and GetName().
	@see IScriptEngine
*/

class PUBLIC_DECL CScriptEngine : public CPMUnknown<IScriptEngine>
{
	typedef CPMUnknown<IScriptEngine> Inherited ;

public:
	/**
		Constructor. Clients with a custom IScriptRequestData boss will need to subclass this
		implementation and pass the ClassID of their IScriptRequestData boss to this base class.
		@param requestDataBoss is the ClassID of the IScriptRequestData boss used to handle requests for this client
	*/
	CScriptEngine( IPMUnknown* boss, ClassID requestDataBoss = kCScriptRequestDataBoss ) ;
	/**
		Destructor
	*/
	virtual ~CScriptEngine() {}

	/**
		Tells the script engine to install
	*/
	virtual	ErrorCode			Install() ;
	/**
		Tells the script engine to uninstall
	*/
	virtual	ErrorCode			UnInstall() ;

	/**
		@return this engine's current request context for processing a script
	*/
	virtual EngineContext		GetRequestContext() const ;
	/**
		@return the script manager for this engine. Clients with multiple engines must override this method.
	*/
	virtual IScriptManager*		QueryScriptManager() const ;
	/**
		@return a script event data boss
	*/
	virtual IScriptRequestData*	CreateScriptRequestData() /*const*/ ;

	/**
		@return this engine's name. Clients with multiple engines will want to override this method.
	*/
	virtual PMString			GetName() const ;

	/**
		@return whether a script is running in this engine
	*/
	virtual bool16				IsScriptActive() const ;
	/**
		Increment the number of active scripts in this engine
	*/
	virtual void				IncrementActiveScriptCount() ;
	/**
		Decrement the number of active scripts in this engine
	*/
	virtual void				DecrementActiveScriptCount() ;

	/**
		@return whether alerts should be displayed when this engine is processing requests
	*/
	virtual bool16				GetShowAlerts() const ;
	/**
		@return whether dialogs should be displayed when this engine is processing requests
	*/
	virtual bool16				GetShowDialogs() const ;

protected:
	/**
		Called by CreateScriptRequestData() to initialize this script event data with default 
		policies for this engine. Most clients will not need to override this method.
		@param scriptRequestData is the script event data interface to initialize
	*/
	virtual void ResetScriptRequestData( IScriptRequestData* scriptRequestData ) const ;

private:
	/* The ClassID of the IScriptRequestData boss used to handle requests for this client */
	ClassID		fRequestDataBoss ;
	/* The number of active scripts in this engine */
	int32		fActiveScripts ;
	/* A cache of IScriptRequestData bosses created for this engine; maintained for performance reasons */
	K2Vector<InterfacePtr<IScriptRequestData> >	fSEDCache ;
} ;

#endif
