//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IServerSettings.h $
//  
//  Owner: Peter Boctor
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
#ifndef __IServerSettings__
#define __IServerSettings__

#include "IPMUnknown.h"
#include "ServerSettingsID.h"

/** Settings used by InDesign Server to increase performance and control UI for debugging.
The undo state is referenced when creating new documents and is used to control the document's
command mgr undo state.  Changing the undo state with IServerSettings has no effect
on the current undo state of a document, only new ones.  By default the undo state is kFalse
for increased performance.

The image preview state is referenced during import of images and determines whether a preview
will be generated for the newly imported image.  If the document being created will not be
opened by an end user in InDesign than there are significant advantages to turning of image
preview support.  With image previews turned off graphics will appear in InDesign as gray boxes
until re-linked.  By default, image previews are turned off in the server.

The JavaScript UI setting controls whether JavaScript native dialogs will display.  Sometimes it
is useful while debugging to have access to these dialogs.  By default JavaScript UI is turned
off in the Server.
*/
class IServerSettings : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISERVERSETTINGS } ;

	virtual void SetImagePreview(bool16 imagePreview) = 0;

	/** Get the value of the image preview state. 
		@return kTrue if image previews are enabled.  The default value is kFalse.
	*/
	virtual bool16 GetImagePreview() = 0;
	
	/** Set the value of JavaScript UI.  Setting the state to kTrue will allow JavaScript
		native UI dialogs to be displayed.
		@param javaScriptUI indicates whether JavaScript native UI dialogs will be displayed.
	*/
	virtual void SetJavaScriptUI(bool16 javaScriptUI) = 0 ;

	/** Get the value of the JavaScript UI state. 
		@return kTrue if JavaScript UI is displayable.  The default value is kFalse.
	*/
	virtual bool16 GetJavaScriptUI() = 0 ;
	
	/** Did this instance of InDesignServer start a console window? 
		@return kTrue if this instance of InDesignServer started a console window.  The default value is kFalse.
	*/
	virtual bool16		GetHasConsole() = 0 ;

	/** Get the path to the IOR file. 
		@return path to the IOR file.  The default value is an empty string.
	*/
	virtual PMString	GetIORFile() = 0 ;

	/** Is this instance logging to the event log?
		@return kTrue if this instance is logging to the event log.  The default value is kFalse.
	*/
	virtual bool16		GetLogToEventLog() = 0 ;

	/** Get the maximum size of the error list. 
		@return maximum size of the error list. Default is 10000.
	*/
	virtual int32		GetMaxErrors() = 0 ;

	/** Set the maximum size of the error list. 
		@param maxErrors maximum size the error list can grow to
	*/
	virtual void		SetMaxErrors(int32 maxErrors) = 0 ;

	/** Get the string of paths to additional plugin directories. 
		@return paths of additional plugin directories.  The default value is an empty string.
	*/
	virtual PMString	GetPluginPath() = 0;

	/** Will crashes cause crash logs to be sent to Adobe? 
		@return kTrue if a crash will automatically send crash logs to Adobe.  The default value is kFalse.
	*/
	virtual bool16		GetSendCrashLogs() = 0;

	/** Should errors be saved in the error list? 
		@return kTrue if errors should be saved in the error list.  The default value is kFalse.
	*/
	virtual bool16		GetUseErrorList() = 0;

	/** Set the value of the Use Error List state. 
		@param if kTrue, errors up to the value set via SetMaxErrors are saved.  The default value is kFalse.
	*/
	virtual void		SetUseErrorList(bool16 buseErrorList) = 0;

	/** Did a structured event handler get installed on launch? 
		@return kTrue if a structured event handler got installed on launch.  The default value is kTrue.
	*/
	virtual bool16		GetUseSEH() = 0;
	

	/** Which port is IDS listening on for SOAP messages?
		@return port number IDS is listening on.  A return of -1 indicates no port.
	*/
	virtual int32		GetPortNumber() = 0;

	/** What is configuration name is being used? 
		@return name of the configuration provided on the command line or a name constructed based on the current port number.
	*/
	virtual PMString	GetConfigurationName() = 0;

	/**
		@return true if all client requests are executed on main thread only
	*/
	virtual bool16 GetOnMainThreadExecutionMode() = 0;

	/**
		@return true if Session Support logging is enabled
	*/
	virtual bool16 IsSessionSupportLoggingEnabled() = 0;

	/**
		@return session timeout in seconds
	*/
	virtual int32 GetSessionTimeout() = 0;

	/** Which port is open for admin messages?
		@return port number for administration messages.  A return of -1 indicates no port.
	*/
	virtual int32		GetAdminPortNumber() = 0;

	/**
	** @return interval at which last active timestamp of IDS is sent to
	** IDS console application
	*/
	virtual int32		GetHeartbeatUpdateInterval() = 0;


	/** What is the host name this instance is running on? 
		@return name of the host either as DNS style name (foo.bar.com) or IP (123.456.78.90).
	*/
	virtual PMString	GetHostName() = 0;

	/**
		@return kTrue if a BeginSession request should be non blocking
	*/
	virtual bool16 IsSessionSupportNonBlocking() = 0;

	/*
	@param bSSNonBlocking if kTrue, BeginSession request will be non blocking
	*/
	virtual void SetIsSessionSupportNonBlocking(bool16 bSSNonBlocking) = 0;

		/**
	** @return maximum wait time in secs for begin session 
	** to take place in case of non-blocking begin session requests
	*/
	virtual uint16 GetMaximumWaitForBeginSession() = 0;

	/**
	** @param inMaxWaitTime wait time in secs for non blocking 
	** begin session
	*/
	virtual void SetMaximumWaitForBeginSession(
		uint16 inMaxWaitTime) = 0;
} ;

#endif
