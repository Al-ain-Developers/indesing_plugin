//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IErrorState.h $
//  
//  Owner: ?
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
#ifndef __IErrorState__
#define __IErrorState__

// ----- Interfaces -----

#include "IPMUnknown.h"

// ----- ID.h files -----

#include "ShuksanID.h"


class PMString;

/** Interface that stores the global error state, and hangs off the session (kSessionBoss); use
	the methods in ErrorUtils rather than this interface to manipulate the global error state. 

	The application 
	maintains a global error state associated with the session.
	When an error happens, the error should be posted to the global
	error state via IErrorState, and the error returned by the function.

	Usually you don't access 
	this directly: ErrorUtils is a handy shell over this function.

	@ingroup arch_error
	@see ErrorUtils
	@see kSessionBoss
*/
class IErrorState : public IPMUnknown 
{
public:
	enum { kDefaultIID = IID_IERRORSTATE };

	/** Sets the current error code to errCode. If no string is passed in the
		error state will find a string based on the code (see IErrorCodeService).
		Set platformErr to true if the error code is from the platform.
		errInfo can be an error specific object that contains more information
		about the error.  The object only means something to the originator of the
		error and the handler of the error.  For instance, suppose the error
		is "file %s not found", where you want %s to be filled in with the filename.
		It could be that associated with the file not found error is an object 
		containing the filename.  SetErrorCode AddRefs on errInfo and makes a 
		copy of the string pointed to be errStr.
	*/
	virtual void Set
				(
					ErrorCode 			errCode, 
					const PMString*		errStr      = nil, 
					IPMUnknown*			errInfo     = nil,
					const PMString*		errContext	= nil
				) = 0;
				
	/** Get the current error code
		@return the error code
	*/
	virtual ErrorCode GetErrorCode() const = 0;
		
	/**	Return the current error string. Attempts to resolve it via the error registry
		if the string was not set explicitly.
	*/
	virtual PMString GetErrorString() const = 0;
	
	/** Return the error info object, (errInfo passed into Set). Client must release
		it when done with it.
	*/
	virtual IPMUnknown* QueryErrorInfo() const = 0;
	
	/** Return the context info. Typically this is empty, except in Macintosh Debug where
		it may contain a stack trace of the location that set the error code.
	*/
	virtual PMString GetContextInfo() const = 0;

	/** Returns kTrue if the error string was set explicitly in the call to Set.
	*/
	virtual bool16 IsExplicitString() const = 0;
};


#endif // __IErrorState__