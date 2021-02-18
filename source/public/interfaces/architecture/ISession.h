//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ISession.h $
//  
//  Owner: Lonnie Millett
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
#ifndef __ISESSION__
#define __ISESSION__

#include "IPMUnknown.h"
#include "ShuksanID.h"

//----------------------------------------------------------------------------------------
// Forward Declarations
//----------------------------------------------------------------------------------------

class IApplication;
class IActiveContext;
class IChangeManager;
class IWorkspace;
class ICommandProcessor;
class IEventConverter;
class IDataBase;
class GlobalTime;
class IObjectModel;
class VersionNumber;
class IStartupScreen;
class IAutomationManager;
class IUserActionPersonalityManager;
class IINXManager;
class IDocumentList;
/** ISession is the main interface off the root object in the hierarchy (instance of kSessionBoss). It contains
	global state information. The session is handed to every plug-in in its IPlugIn::Load
	function. Each execution context (thread) has only one session object which is accessible
	via GetExecutionContextSession()or by calling GetSession() on IExecutionContext.

	Supplies plugins with references to key objects, such as:
	\li the active context (kActiveContextBoss, via interface IActiveContext), 
	\li the application (kAppBoss, via interface IApplication), 
	\li the session workspace (kWorkspaceBoss, via interface IWorkspace), 
	\li the command processor (kCommandProcessorBoss , via interface ICommandProcessor).
	
	@ingroup arch_session
	@see kSessionBoss
	@see kActiveContextBoss
	@see IActiveContext
	@see kWorkspaceBoss
	@see IWorkspace
	@see kAppBoss
	@see IApplication
	@see kCommandProcessorBoss
	@see ICommandProcessor
*/
class ISession : public IPMUnknown
{
public:		
	/** Return the active context object. You shouldn't need to call this function,
		since the active context is now passed into every method that needs it. But
		there may be some edge cases we missed, so if you need the active document,
		active tool, active window, etc., and find no other way to get it, this is
		left available. 
		
		@return IActiveContext* the global active context 
	*/
	virtual IActiveContext* GetActiveContext() = 0;
		
	/** Return the global change manager used in broadcasting messages. Normally you 
		do not need to call this; it is called for you by CSubject.
		
		@return IChangeManager* the global change manager
	*/
	virtual IChangeManager* GetChangeManager() = 0;
	
	/** Return an instance of a global event converter to convert system events to IEvents.
		You should not need to call this directly.

		@return IEventConverter* the global event converter
	*/
	virtual IEventConverter* GetEventConverter() = 0;
		
	/** Return a reference to the global application. The application object is a singleton
		that contains the list of open documents, windows, panels, tools, etc. Also version 
		number and name info for the application. Returns nil if the application is in the
		process of shutting down.
		
		@return IApplication* the global application
	*/
	virtual IApplication* QueryApplication() = 0;
		
	/** Return a reference to the global workspace. The workspace contains application
		preference data. Returns nil if called very early in startup, or late in shutdown.
		For instance, plug-in load functions, or early initializers will return nil.
		Left here for compatibility with previous releases.
		
		@return IWorkspace* the global workspace
	*/
	virtual IWorkspace* QueryWorkspace() = 0;
		
	/** Return a reference to the global workspace, with a particular interface requested. 
		The workspace contains application preference data. Returns nil if called very 
		early in startup, or late in shutdown. For instance, plug-in load functions, or 
		early initializers will return nil.
		@param faceID which interface to return
		@return IWorkspace* the global workspace
	*/
	virtual IPMUnknown* QueryWorkspace(PMIID faceID) = 0;
		
	/** Return a reference to the global command processor. Normally this is called for
		you by CmdUtils.
		
		@return ICommandProcessor* the global command processor
	*/
	virtual ICommandProcessor* QueryCommandProcessor() = 0;
	
	/** Return a reference to the global automation manager
		
		@return IAutomationManager* the global automation manager boss
	*/
	virtual IAutomationManager* QueryAutomationMangager() = 0;

	/** Return a reference to the global user action personality manager
		
		@return IUserActionPersonalityManager* the global user action personality manager boss
	*/
	virtual IUserActionPersonalityManager* QueryUserActionPersonalityMangager() = 0;
	
	/** Return a reference to the global INX manager
		
		@return IINXManager* the global INX manager boss
	*/
	virtual IINXManager * QueryINXManager() = 0;

	/**	The state of the session: starting up, running, shutting down.
	*/
	typedef enum SessionStateType
	{ kUnknown, kStartingUp, kRunning, kShuttingDown } SessionStateType;

	/** Return the current state of the session.
	
		@return SessionStateType session status
	*/
	virtual SessionStateType GetState() = 0;
	
	/**@name For internal use only */
	//@{-----------------------------------------------------------------------------


	// Purge handler is called automatically when memory allocation fails.
	virtual bool16 PurgeMemory(int32 level) = 0;
	
	// Get the startup time
	virtual const GlobalTime &GetStartupTime() = 0;
	
	// Is InDesign running without saved data
	virtual const bool16 IsStartupWithoutSavedData (void) = 0;

	// Initialize the session.
	virtual bool16 Init(IDataBase* workSpaceDB = nil, const GlobalTime* const pStartupTime = nil) = 0;
	
	// Shutdown the session.
	virtual void Cleanup() = 0;
	
	// access to the startup screen.
	virtual IStartupScreen *GetStartupScreen() const = 0;

	// This call can be used to insert a proxy command processor, or to remove
	// the proxy and restore the original command processor that will be returned
	// by QueryCommandProcessor().  This will not change the reference count
	// of their command processor boss.
	virtual ICommandProcessor *SetProxyCommandProcessor (ICommandProcessor *proxy) = 0;


	/** Returns a reference to the list of open documents.
	*/
	virtual IDocumentList* QueryDocumentList() const = 0;


	//@}-----------------------------------------------------------------------------
};	

/** Retrieves the ISession instance for the calling thread.
*/
PUBLIC_DECL ISession* GetExecutionContextSession();


template <class FACE>									
inline FACE* QuerySessionWorkspace()				
{	
	IPMUnknown* face = GetExecutionContextSession()->QueryWorkspace(FACE::kDefaultIID);
	
	return static_cast<FACE*>(face);
}


#endif // __ISESSION__
