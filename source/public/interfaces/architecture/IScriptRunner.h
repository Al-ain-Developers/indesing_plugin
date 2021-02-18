//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IScriptRunner.h $
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
#ifndef __IScriptRunner__
#define __IScriptRunner__

#include "ScriptingID.h"
#include "ScriptData.h"

#include "IScriptRequestData.h"

class IScriptCoreFunctor ;
class RunScriptParams ;

/**
	The Scripts panel and any other client that wants to execute a script uses this interface.
	Implemented by each scripting language supported by InDesign.
*/  
class IScriptRunner : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISCRIPTRUNNER };

	/**
		Return kTrue if this runner can execute this file
		@param idFile the script file to check
	*/
	virtual bool16		CanHandleFile( const IDFile& idFile ) const = 0;

	/**
		Execute a script file. Should only be called if CanHandleFile returns kTrue.
		@param idFile the script file to execute IN
		@param params contains settings and data for script execution IN/OUT
		@return is kSuccess or an error code
	*/
	virtual ErrorCode	RunFile( const IDFile& idFile, const RunScriptParams& params ) = 0;
	/**
		Execute a script given the text of the script.
		@param scriptText the script text to execute IN
		@param params contains settings and data for script execution IN/OUT
		@return is kSuccess or an error code
	*/
	virtual ErrorCode	RunScript( const PMString& scriptText, const RunScriptParams& params ) = 0;
	/**
		Invoke a function.
		@param scriptFunction is the function IN
		@param params contains settings and data for script execution IN/OUT
		@return is kSuccess or an error code
	*/
	virtual ErrorCode	InvokeFunction( const IScriptCoreFunctor* scriptFunction, const RunScriptParams& params ) = 0 ;

	/**
		Edit a script file.
		@param idFile the script file to edit
	*/
	virtual ErrorCode	EditFile( const IDFile& idFile ) const = 0;
	/**
		Show a script file in the Mac Finder/Windows shell
		@param idFile the script file to show
	*/
	virtual ErrorCode	ShowFile( const IDFile& idFile ) const = 0;
	
	/**
		Return kTrue if a script has a description.
		@param idFile the script file to check for a description
	*/
	virtual bool16		ScriptHasDescription( const IDFile& idFile ) const = 0;
	/**
		Get a script's description.
		@param idFile the script file from which to get a description
	*/
	virtual PMString	GetScriptDescription( const IDFile& idFile ) const = 0;
	
	/**
		@return a file icon for a script.
		@param idFile the script file to get an icon for
	*/
	virtual PMRsrcID	GetFileIcon( const IDFile& idFile ) const = 0;

	/**
		@return kTrue if user is trying to cancel script execution
	*/
	virtual bool16		CheckForUserCancel() const = 0;

	/**
		Cancel the execution of the currently running script
	*/
	virtual ErrorCode	CancelScriptExecution() const = 0;

	/**
		Handle any periodic tasks requested by the system
	*/
	virtual ErrorCode	HandleIdleTasks() const = 0;

	/**
		Process any commands that were scheduled during a script request
	*/
	virtual ErrorCode	ProcessScheduledCmds() const = 0;

	/**
		@return kTrue if a script is currently running
	*/
	virtual bool16		IsScriptRunning() const = 0;
	/**
		Get the currently running script.
		@param idFile the script file that is currently running
	*/
	virtual ErrorCode	GetRunningScriptFile( IDFile& idFile ) const = 0;

	/**
		Display a script error alert
		@param errorNumber - the error number (must != kSuccess)
		@param errorString - a description of the error (must != "")
		@param lineNumber - 1-based index of the line of the script on which the error occurred (ignored if == 0)
		@param sourceCode - the line of the script that contains the error (ignored if == "")
		@param offendingText - the code snippet that caused the error (ignored if == "")
		@param scriptFile - the script file that contains the error (ignored if empty)
		@return kSuccess
	*/
	virtual ErrorCode	DisplayErrorMessage( ErrorCode errorNumber, const PMString& errorString, 
											 int32 lineNumber, const PMString& sourceCode, 
											 const PMString& offendingText, const IDFile& scriptFile ) const = 0 ;
};

#pragma export on

class PUBLIC_DECL RunScriptParams
{
public:
	/** Construct a new RunScriptParams object
		@param scriptRunner is the script runner that will execute the script
	*/
	explicit RunScriptParams( IScriptRunner* scriptRunner ) ;
	/** Construct a new RunScriptParams object as a copy of the passed in object but using 
		the passed in scriptRunner (e.g., for re-targeting a script to a different engine)
		@param params is the object to copy
		@param scriptRunner is the script runner that will execute the script
	*/
	RunScriptParams( const RunScriptParams& params, IScriptRunner* scriptRunner ) ;
	~RunScriptParams() ;

	/** Query the IScriptRequestData that is used to pass arguments and return the result */
	IScriptRequestData* QueryScriptRequestData() const ;

	/** Get the desired version of the DOM in which to execute the script (defaults to 
		the version of the DOM corresponding to the current version of the application) */
	ScriptVersion GetVersion() const { return fVersion ; }
	/** Set the desired version of the DOM in which to execute the script (defaults to 
		the version of the DOM corresponding to the current version of the application) */
	void SetVersion( const ScriptVersion& version ) { fVersion = version ; }

	/** Query the target IScript (defaults to the application object) */
	IScript* QueryTarget() const ;
	/** Set the target IScript (defaults to the application object) */
	void SetTarget( IScript* target ) ;

	/** Get whether the runner should display an alert with the error if an error occurs (defaults to kTrue) */
	bool16 GetShowErrorAlert() const { return fShowErrorAlert ; }
	/** Set whether the runner should display an alert with the error if an error occurs (defaults to kTrue) */
	void SetShowErrorAlert( bool16 showErrorAlert ) { fShowErrorAlert = showErrorAlert ; }
	
	/** Get whether to load the script into a debugger for execution (defaults to kFalse) */
	bool16 GetInvokeDebugger() const { return fInvokeDebugger ; }
	/** Set whether to load the script into a debugger for execution (defaults to kFalse) */
	void SetInvokeDebugger( bool16 invokeDebugger ) { fInvokeDebugger = invokeDebugger ; }

	/** The undo mode for script execution */
	enum UndoMode
	{
		/** Push each script request as a separate undo step */
		kUndoScriptRequest	= en_UndoScriptRequest,
		/** Push the entire script as a single regular undo step. If an error occurs,
			roll back to the beginning of the script request that generated the error. */
		kUndoEntireScript	= en_UndoEntireScript,
		/** Similar to kUndoEntireScript, however faster because we don't snapshot each script  
			request. If an error occurs, we roll back to the beginning of the entire script. */
		kFastUndoEntireScript	= en_FastUndoEntireScript,
		/** Push the entire script as a single auto-undoable step */
		kAutoUndoScript		= en_AutoUndoScript
	} ;	

	/** Get the undo mode for the script's execution (defaults to kUndoScriptRequest) */
	virtual UndoMode	GetUndoMode() const { return fUndoMode ; }
	/** Set the undo mode for the script's execution (defaults to kUndoScriptRequest) */
	virtual void		SetUndoMode( UndoMode undoMode ) { fUndoMode = undoMode	; }

	/** Get the undo name for the undo step in single undo step mode (defaults to "Script") */
	PMString GetUndoName() const { return fUndoName ; }
	/** Set the undo name for the undo step in single undo step mode (defaults to "Script") */
	void SetUndoName( const PMString& undoName ) { fUndoName = undoName ; }

private:
	InterfacePtr<IScriptRequestData> fScriptRequestData ;
	InterfacePtr<IScript> fTarget ;
	bool16 fShowErrorAlert ;
	bool16 fInvokeDebugger ;
	UndoMode fUndoMode ;
	PMString fUndoName ;
	ScriptVersion fVersion ;
} ;

#pragma export reset

#endif	// __IScriptRunner__
