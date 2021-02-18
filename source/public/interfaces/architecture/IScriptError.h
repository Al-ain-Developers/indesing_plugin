//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IScriptError.h $
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
#ifndef __IScriptError__
#define __IScriptError__

#include "IPMUnknown.h"
#include "ScriptingID.h"

/**
	Used to pass error info related to a scripting request from the script request handler back 
	to the client (@see IScriptRequestHandler). This interface should not be used by script 
	providers (@see ScriptReturnData instead).
*/
class IScriptError : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISCRIPTERROR };

	/**
		Set the error code (assumes default error string)
		@param err is the error code
	*/
	virtual void SetErrorCode( ErrorCode err ) = 0 ;

	/**
		Set the error code with an explicit error string
		@param err is the error code
		@param errorString is the error string
	*/
	virtual void SetErrorCode( ErrorCode err, const PMString& errorString ) = 0 ;

	/**
		@return the error code
	*/
	virtual ErrorCode GetErrorCode() const = 0 ;

	/**
		Retrieve the error string. Looks it up using error string services if none has been set explicitly.
		@return the error string
	*/
	virtual PMString GetErrorString() const = 0 ;

	//----------- Internal Use Only --------------------

	/**
		Copy error information into another IScriptError
		@param target is the IScriptError to which to copy our error info
	*/
	virtual void CopyErrorInfoInto( IScriptError* target ) const = 0 ;
	/**
		Clear the error info
	*/
	virtual void Reset() = 0 ;
};

#endif
