//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CCommandLineArgs.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __CCommandLineArgs_h__
#define __CCommandLineArgs_h__

#include "IDFile.h"

#include <string>
#include <vector>


/** Class for the server that parses and provides access to the command line
	paramters. Command line parameters are accessed through the global variable
	named gCommandLineArgs, which is an object of this type.
*/
class PUBLIC_DECL CCommandLineArgs
{
public:
	enum { kInvalidPort = -1 };

	enum { kInvalidTimeValue = -1 };

	enum SessionSupportTimeoutType
	{
		kTimeoutSessionIdle,
		kTimeoutReceiveIdle,
		kSSTimeoutUnknown
	};
	
	/** Internal use only*/
	CCommandLineArgs();
	/** Internal use only*/
	virtual ~CCommandLineArgs();
	
	/** Internal use only*/
	virtual void Terminate();
	
	/**
	 * Returns the number of command line arguments.
	 */
	virtual int32 GetArgCnt();
	
	/**
	 * Get the nth command line argument. This is the raw arguments passed in on the command
	 * line. Plug-in developers can use this to access their own arguments.
	 */
	virtual const PMString& GetNthArg(const int32& nth);
		
	/**
	 * Return the port number.
	 */
	virtual int			GetPortNumber();

	/**
	 * Return the admin port number.
	 */
	virtual int			GetAdminPortNumber();
	
	/**
	 * Return whether to create a console window or not. No-op on Macintosh.
	 */
	virtual bool		ShouldCreateConsole();
	
	/**
	 * Return the configuration name.
	 */
	virtual PMString	GetConfigurationName();
	
	/**
	* Return the executable path.
	*/
	virtual const PMString& GetExecutablePath();
	
	/**
	 * Return the maximum number of errors stored in the SOAP server's in-memory error capture list.
	 */
	virtual int32		GetMaxErrors();

	/**
	 * Sets the maximum number of errors stored in the SOAP server's in-memory error capture list.
	 * Use of this method may override what was originally set on the command line.
	 */
	virtual void		SetMaxErrors(int32 newMaxErrors );

    /**
	 * Returns whether errors should be posted to the error list interface or not.
	 */
	virtual bool		ShouldPostToErrorList();

    /**
	 * Sets whether errors should be posted to the error list interface or not.
	 */
	virtual void		SetPostToErrorList(bool16 bShouldPost);
	
	/**
	 * Returns whether structured event handling should be used on Windows or not.
	 */
	virtual bool		ShouldUseSEH();
	
	/**
	 * Returns whether previews should be generated for placed images or not.
	 */
	virtual bool		ArePreviewsOn();
	
	/**
	 * Returns the home folder.
	 */
	virtual PMString	GetHomeFolder();
	
	/**
	 * Returns the plugin path specified on the command line. Plug-ins are loaded from this path
	 * in addition to the regular search paths.
	 */
	virtual PMString	GetPluginPath();
	
	/**
	 * Return the name absolute pathname of the CORBA IOR file. The IOR for the application object
	 * will be written to this file.
	 */
	virtual PMString	GetIORFile();

	/**
	 * Return the host name 
	 */
	virtual PMString	GetHostName();
	
	/**
	 * Returns whether errors should be logged to the system services log.
	 */
	virtual bool		ShouldLogToSystemEventLog();
	
	/**
	 * Returns whether crash logs should be sent to Adobe (there is no UI either way)
	 */
	virtual bool		ShouldSendCrashLogs();

	/**
	* Returns the timeout of specified type for Session Support functionality
	*/
	virtual int GetSessionSupportTimeout(SessionSupportTimeoutType type);

	/**
	** @return interval at which last active timestamp of IDS is sent to
	** IDS console
	*/
	virtual int GetHeartbeatUpdateInterval();

	/**
	** @return true if all incoming soap requests should be executed
	** on main thread
	*/
	virtual bool ExecuteOnMainThreadOnly();

	/**
	** @return true if a BeginSession() request should be non
	** blocking
	*/
	virtual bool IsSessionSupportNonBlocking();

	/**
	** @return maximum wait time in secs for begin session 
	** to take place in case of non-blocking begin session requests
	*/
	virtual uint16 GetMaximumWaitForBeginSession();

	/** Internal use only*/
	virtual bool		ProcessArgs() { return (ProcessArgsEarly() && ProcessArgsLate()); };
	virtual bool		ProcessArgsEarly();	// may be called before initialization is complete
	virtual bool		ProcessArgsLate();	// may only be called after initialization (especially CoolType) is complete
	
	/**
	 * Write abbreviated usage text to the terminal window
	 */
	virtual void		ShowUsage();

	/**
	 * Return kTrue if Version Cue was requested.
	 * 
	 */
	virtual bool GetUseVersionCue();

private:
	virtual void Abort(const PMString& msg = "", bool bShowUsage = kTrue);

	virtual bool AcquireSingleInstance() = 0;
	virtual void ReleaseSingleInstance() = 0;
	
	virtual bool AcquirePort(const int& portNumber) = 0;
	virtual void ReleasePort() = 0;
	
	virtual bool AcquireConfiguration(const PMString& configurationName) = 0;
	virtual void ReleaseConfiguration() = 0;
	
	virtual bool PortIsInUse(const int& portNumber) = 0;

protected:
	virtual IDFile MakeFileInSemaphoreFolder(const PMString& filename);

	std::vector<PMString>	fArgs;	// used by M/WCommandLineArgs

private:
	enum Status { kNotProcessed, kPartiallyProcessed, kProcessedSuccess, kProcessedFailure };
	
	PMString	fConfigurationName;
	PMString	fExecutablePath;
	PMString	fHomeFolder;
	PMString	fPluginPath;
	PMString	fIORFile;
	PMString	fHostName;

	int			fPortNumber;
	int			fAdminPortNumber;
	int32		fMaxErrors;

	Status		fStatus;
	bool		fShouldCreateConsole;
	bool		fShouldPostToErrorList;
	bool		fShouldUseSEH;
	bool		fPreviews;
	bool		fBShouldLogToSystemEventLog;
	bool		fBConfigurationAcquired;
	bool		fBSendCrashLogs;

	int			fSessionSupportSessionIdleTimeout;
	int			fSessionSupportReceiveIdleTimeout;
	int			fHeartbeatUpdateTimeInterval;

	bool		fExecuteOnMainThreadOnly;
	bool		fNonBlockingSessionSupport;
	int16		fMaxWaitTimeForBeginSession;
	bool		fBShouldUseVersionCue;
};

extern PUBLIC_DECL CCommandLineArgs* gCommandLineArgs;

#endif
