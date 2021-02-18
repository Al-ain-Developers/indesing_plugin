//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CScriptRunner.h $
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
#ifndef __CScriptRunner__
#define __CScriptRunner__

#include "CPMUnknown.h"
#include "IScriptRunner.h"

#include "AcquireModalCursor.h"

class IScriptCoreFunctor ;

#pragma export on

/**
	A base class for script runners
*/
class PUBLIC_DECL CScriptRunner : public CPMUnknown<IScriptRunner>
{
public:
	CScriptRunner(IPMUnknown *boss);
	virtual ~CScriptRunner() {}

	//edge implementations
	virtual bool16		CanHandleFile(const IDFile& idFile) const = 0;
	virtual ErrorCode	RunFile(const IDFile& idFile, const RunScriptParams& params ) = 0;
	virtual ErrorCode	RunScript(const PMString& scriptText, const RunScriptParams& params ) = 0;
	virtual ErrorCode	InvokeFunction( const IScriptCoreFunctor* scriptFunction, const RunScriptParams& params ) = 0 ;
	virtual PMString	GetScriptDescription(const IDFile& idFile) const = 0;
	virtual PMRsrcID	GetFileIcon(const IDFile& idFile) const = 0;
	virtual ErrorCode	CancelScriptExecution() const = 0;
	/**
		Define a variable in the global name space of the scripting engine. 
		Called by AddArguments to pass arguments to scripts.
		@param scriptContext is client-specific information
		@param name is the variable name to define
		@param value is the value to assign the variable
		@return kSuccess if registered successfully, kFailure otherwise
	*/
	virtual ErrorCode DefineGlobal( void* scriptContext, const PMString& name, const ScriptData& value ) = 0 ;

	//platform implementations
	virtual ErrorCode	EditFile(const IDFile& idFile) const ;
	virtual ErrorCode	ShowFile(const IDFile& idFile) const ;
	virtual bool16		CheckForUserCancel() const ;
	virtual ErrorCode	HandleIdleTasks() const ;

	//core implementations
	virtual ErrorCode	ProcessScheduledCmds() const ;
	virtual bool16		ScriptHasDescription( const IDFile& idFile ) const ;
	virtual void		SetScriptRunning( bool16 scriptRunning, const IDFile& runningScript )
							{ fScriptRunning = scriptRunning ; fRunningScript = runningScript ; }
	virtual bool16		IsScriptRunning() const { return fScriptRunning ; }
	virtual ErrorCode	GetRunningScriptFile(IDFile& idFile) const ;

	virtual ErrorCode	DisplayErrorMessage( ErrorCode			errorNumber,	//must != kSuccess
											 const PMString&	errorString,	//must != "" 
											 int32				lineNumber,		//1-based index (ignored if == 0)
											 const PMString&	sourceCode,		//ignored if == ""
											 const PMString&	offendingText,	//ignored if == ""
											 const IDFile&		scriptFile		//ignored if empty
											) const ;

protected:
	virtual ErrorCode	AddArguments( void* scriptContext, IScriptRequestData* data ) ;

private:
	bool16 fScriptRunning;
	IDFile fRunningScript;
};

//Stack-based class to SetScriptRunning at beginning and end of running a script
class PUBLIC_DECL ScriptRunning
{
public:
	ScriptRunning( CScriptRunner* scriptRunner, const RunScriptParams& params, const IDFile& scriptFile );
	ScriptRunning( CScriptRunner* scriptRunner, const RunScriptParams& params, const PMString& scriptText );
	ScriptRunning( CScriptRunner* scriptRunner, const RunScriptParams& params, const IScriptCoreFunctor* scriptFunc );
	~ScriptRunning();

private:
	void InitScriptRunning( const RunScriptParams& params, const IDFile& runningScript ) ;

private:
	CScriptRunner*		fScriptRunner ;
	bool16				fPreviousRunning ;
	IDFile				fPreviousFile ;
	ScriptVersion		fPreviousVersion ;
	bool16				fRunningAsSingleUndoStep ;
	AcquireDelayedBusyCursor	fWaitCursor ;	
} ;

#pragma export reset

#endif
