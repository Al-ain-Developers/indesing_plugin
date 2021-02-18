//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/ErrorUtils.h $
//  
//  Owner: jargast
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
#ifndef __ErrorUtils__
#define __ErrorUtils__

#include "PMString.h"

/** Utilities for getting and setting the global error state.
	The global error state holds an error code, an error string (typically for showing in an alert
	box), and (optionally) an object to hold whatever additional information is necessary. The error
	string may be set at the time the error is set, or it may be dynamically assocated with the error
	by putting it in an UserErrorTable resource.
	@see UserErrorTable
*/

class PUBLIC_DECL ErrorUtils
{
public:
	/** Sets the global error code on the session. The error code starts off kSuccess. When it gets 
		set to anything else, it goes into error state. Once it is in error state, subsequent attempts
		to set the error code are ignored, until the error code is restored to kSuccess. This is 
		because sometimes one error can result in a cascade of other errors, but the important error
		to report is the original error.
		
		If no string is passed (or string is nil), the central error handling code will attempt to find
		a string based on the error code. It maintains a registry of strings declared in UserErrorTable
		resources, and will return the first matching string it finds for any subsequent requests. For 
		directions on how to use the facility, see IErrorStringService.h
		@see IErrorStringService
		
		errInfo can be an error specific object that contains more information
		about the error.  The object only means something to the originator of the
		error and the handler of the error.  For instance, suppose the error
		is "file %s not found", where you want %s to be filled in with the filename.
		It could be that associated with the file not found error is an object 
		containing the filename.  PMSetGlobalErrorCode will do an AddRef on the errInfo,
		so that it may keep its own reference to the object.

		@param errCode the new error code
		@param isPlatform is it a platform error code (should always be false)
		@param errString message string to show in the alert box
		@param errInfo any extra information you want to attach to the error state	
	*/
	static void PMSetGlobalErrorCode (ErrorCode errCode, const PMString* errString = nil, IPMUnknown* errInfo = nil, const PMString* contextInfo =  nil);
	
	/** Gets the current global error code
		@return the current error code, or kSuccess if there's no error
	*/
	static ErrorCode PMGetGlobalErrorCode();
	
	/** Gets the current global error string.  The string may be empty.
		@return PMString the error string
	*/
	static PMString PMGetGlobalErrorString();
	
	/** Returns the current global error info
		@return IPMUnknown* the optional extra information posted with the error state
	*/
	static IPMUnknown* PMQueryGlobalErrorInfo();
	
	/** May be empty, but if full contains context information about where the error occurred.
		This will contain whatever stack information can be determined on Macintosh Debug, otherwise
		it will empty.
	*/
	static PMString PMGetGlobalContextInfo();
	
	/** Finds the error string corresponding to the errCode
		Queries all services for user errors and redirects to application for platform errors
		@param errCode the error code to search for
		@param isPlatform (pass false)
		@param errInfo other info necessary for resolving the error string
		@return PMString the default error string to use for this error
	*/
	static PMString PMGetErrorString (ErrorCode errCode, IPMUnknown* errInfo = nil);

	/** Read the user error string from the current resource fork. This is a helper function
		provided because almost every user error string service will need the same functionality.
		This function is different from PMGetErrorString in that it only reads the error.
		If it isn't in the current resource fork it won't find it.
	*/
	static PMString PMLoadErrorStringFromRsrc( ErrorCode errCode, PluginID errorRsrcPluginId, RsrcID errorTableId );

	/** Set the application's exit code. For internal use only.
	*/
	static void		SetExitCode( int16 exitCode );
	
	/** Get the application's exit code. For internal use only.
	*/
	static int16	GetExitCode();
};


/** Stack-based object used for preserving the error code across a scope. The constructor saves 
	the current error state, and the destructor restores the error state back to the saved state.
*/
class PUBLIC_DECL GlobalErrorStatePreserver
{
	public:
		GlobalErrorStatePreserver() ;
		
		~GlobalErrorStatePreserver();
		
		/** Call this to prevent the preserver from restoring the previous error state in its destructor 
		*/
		void DoNotRestoreErrorState();
		
	private:
		ErrorCode						fErrorCode;
		bool16							fIsPlatform;
		IPMUnknown *			 		fErrInfo;
		PMString 						fContextString;
		PMString						fErrorString;
		bool16							fDoRestore;
		bool16							fExplicitString;
};

#endif
