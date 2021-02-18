//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IApplication.h $
//  
//  Owner: Robin Briggs
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
#ifndef __IAPPLICATION__
#define __IAPPLICATION__

#include "IPMUnknown.h"
#include "ShuksanID.h"


//----------------------------------------------------------------------------------------
// Forward Declarations
//----------------------------------------------------------------------------------------

class IFile;
class IDocument;
class IWindow;
class IEventConverter;
class IDocumentList;
class IEvent;
class IActionManager;
class IPaletteMgr;
class IPanelMgr;
class PMLocaleId;
class IToolManager;
class PMString;


/** IApplication is similar to ISession, and holds all the app-specific and UI-specific 
	information on the current session (kSessionBoss). 
	The application object (kAppBoss) also manages and provides access to the global event loop 
	(via its interface IEventDispatcher).

	There is only ever one application object (kAppBoss), and you
	can get a reference to its IApplication interface 
	by querying the session (ISession, off kSessionBoss), for example:
	<pre>
	InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
	</pre>

	@ingroup arch_session
	@see kAppBoss
	@see kSessionBoss
*/
class  IApplication : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IAPPLICATION };

	/** Return the API major version number.
	*/
	virtual int32 GetAPIMajorVersion() const = 0;
		
	/** Return the API minor version number.
	*/
	virtual int32 GetAPIMinorVersion() const = 0;
		
	/** Return the UI major version number.
	*/
	virtual int32 GetUIMajorVersion() const = 0;
		
	/** Return the UI minor version number.
	*/
	virtual int32 GetUIMinorVersion() const = 0;
		
	/** Return the UI dot version number.
	*/
	virtual int32 GetUIDotVersion() const = 0;
		
	/** Return the build number of the application.
	*/
	virtual int32 GetBuildNumber() const = 0;
		
	/** Return a string identifying the package version of the application. (e.g. "CC")
	*/
	virtual PMString GetUIVersionString() const = 0;
		
	/** Return a string indicating the version number of the application. (e.g. "4.0" or "4.0.1", etc.)
	*/
	virtual PMString GetUIVersionNumberString() const = 0;

	/** Return the application name.
	*/
	virtual PMString GetApplicationName() const = 0;
			
	/** return kTrue is the application is active, not in background, etc.
	*/
	virtual bool16 IsApplicationActive() const = 0;
	
	/** Returns a reference to the application's list of open documents.
	*/
	virtual IDocumentList* QueryDocumentList() const = 0;

	/** Returns a reference to the action manager - the manager responsible for menus/shortcuts.
	*/
	virtual IActionManager* QueryActionManager() const = 0;
	
	/** Returns a reference to the panel manager.
	*/
	virtual IPanelMgr* QueryPanelManager() const = 0;
		
	/** Returns a reference to the tool manager.
	*/
	virtual IToolManager* QueryToolManager() const = 0;
	
	/** Internal Use Only:
		Used by Run() This function does not return until ExitEventLoop() gets called.
		Calls to EventLoop can no longer be nested in CC and beyond.
	*/
	virtual void EventLoop(bool16 bSuppressScheduled = kFalse) = 0;
		
	/** Calling ExitEventLoop() will cause the current execution of EventLoop()
		to exit and return to its caller.
	*/
	virtual void ExitEventLoop() = 0;
	
	
	/**	The state of the application: starting up, running, quitting, and shutting down.
		kQuitting indicates Terminate has been called (typically by the QuitCmd) which happens before we enter kShuttingDown.
		The transition from kQuitting to kShuttingDown occurs once the event loop has stopped. 
		Neither kQuitting nor kShuttingDown is user cancelable
	*/
	typedef enum ApplicationStateType
	{ kUnknown, kStartingUp, kRunning, kQuitting, kShuttingDown } ApplicationStateType;

	/** Return the current state of the application.
		@return ApplicationStateType session status
	*/
	virtual ApplicationStateType GetApplicationState() const = 0;


	/**@name  For Internal Use Only  */
	//@{-----------------------------------------------------------------------------

	/** Start the main event loop.
	*/
	virtual void Run() = 0;
	
	/** Terminate the application. Terminates the event loop, and closes all open windows.
	*/
	virtual void Terminate(bool16 emergencyExit) = 0;
	
	/** Suspend processing scheduled commands in the event loop. Used for Drover-based Dialogs
		Handles nested calls correctly.
	*/
	virtual void SuspendScheduledCommandProcessing(bool16 suspend = kTrue) = 0;
	virtual bool HasSuspendedScheduledCommandProcessing() = 0;
	//@}-----------------------------------------------------------------------------
};

/**@name  For Internal Use Only  */
//@{-----------------------------------------------------------------------------
class  IApplicationDelegate : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IAPPLICATIONDELEGATE };

	virtual void Initialize() = 0;
	virtual void LateInitialize() = 0;
	
	virtual void InitializePalettes() = 0;
	virtual void InitializePaletteWorkspace() = 0;
	
	virtual void ShutdownPalettes() = 0;
	
	virtual void Terminate() = 0;
	
	/** Used by Run(). This function does not return until
		ExitEventLoop() gets called.
	*/
	virtual void EventLoop() = 0;
		
	/** Calling ExitEventLoop() will cause the EventLoop()
		to exit.
	*/
	virtual void ExitEventLoop() = 0;
};
//@}-----------------------------------------------------------------------------


#endif // __IAPPLICATION__
