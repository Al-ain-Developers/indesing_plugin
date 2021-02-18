//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IErrorList.h $
//  
//  Owner: Steve Dowd
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

#ifndef __IERRORLIST_h__
#define __IERRORLIST_h__

#include "IPMUnknown.h"
#include "K2Vector.h"
#include "BaseType.h"
#include "FileUtils.h"
#include "SoapServerID.h"
#include "UIDRef.h"

//========================================================================================
// CLASS IErrorList
//========================================================================================

/** Stores errors for later display, an interface off the session (kSessionBoss).

	@ingroup arch_error
*/
class IErrorList : public IPMUnknown
{
public:

public:
	enum { kDefaultIID = IID_IERRORLIST };

		/** Adds an error to the in-memory error capture list.

			@param iconID the error "level" that would normally be put in the CAlert - one of Error, Warning, Information, Question
			@param message the message that would normally be put in the CAlert
			@param target the target of this error, the most used part is the database which is used to match errors to a
			              specific document
			@param errorCode the error code (number) of the error
		*/
	virtual void			AddError( const int32 iconID, const PMString& message, const UIDRef& target, const ErrorCode errCode ) = 0;

		/** Removes an error from the in-memory error capture list.

			@param whichOne which entry in the error list to remove
		*/
	virtual void			RemoveError( int32 whichOne ) = 0;

		/** Removes all errors from the in-memory error capture list.

		*/
	virtual void			Clear() = 0;

		/** Returns the total number of errors from the in-memory error capture list.

		*/
	virtual int32			GetNumErrors() = 0;

		/** Returns the maximum allowed number of errors before the in-memory error capture list resets.
		    This value is settable from the command line using "-maxerrors NNNN."
		    If maxNumErrors is set to -1 (or any other negative number), we interpret that as no maximum.

		*/
	virtual int32			GetMaxNumErrors() = 0;

		/** Sets the maximum allowed number of errors before the in-memory error capture list resets.
		    This value is settable from the command line using "-maxerrors NNNN."
		    Use of this method may override what was set on the command line.

		*/
	virtual void SetMaxNumErrors( int32 newMaxNumErrors ) = 0;

		/** Returns the error code of the specified error in the list.

			@param whichOne which entry in the error list
			@return the stored error code
		*/
	virtual ErrorCode		GetErrorCode( int32 whichOne ) = 0;

		/** Returns the error level (number) of the specified error in the list. The
		    error level is one of Error, Warning, Information, or Question.

			@param whichOne which entry in the error list
			@return the error level
		*/
	virtual int32			GetErrorLevel( int32 whichOne ) = 0;

		/** Returns the error message of the specified error in the list.

			@param whichOne which entry in the error list
			@return the stored error message
		*/
	virtual PMString		GetErrorMessage( int32 whichOne ) = 0;

		/** Returns the time the error occurred of the specified error in the list.

			@param whichOne which entry in the error list
			@return the stored error occurance time
		*/
	virtual GlobalTime		GetErrorTime( int32 whichOne ) = 0;

		/** Returns the time the error occurred of the specified error in the list.

			@param whichOne which entry in the error list
			@return the stored error occurance time
		*/
	virtual PMString		GetErrorTimeAsString( int32 whichOne) = 0;
};


#endif // __IERRORLIST_h__
