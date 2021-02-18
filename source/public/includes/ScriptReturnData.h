//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/ScriptReturnData.h $
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
#ifndef __ScriptReturnData__
#define __ScriptReturnData__

#include "ScriptData.h"

/**
	Encapsulates the return data from a scripting request. @see IScriptRequestData
*/
class PUBLIC_DECL ScriptReturnData
{
public:
	typedef object_type data_type ;

	/**
		Use this constructor to represent a successful kMethodRequest (with no return value), 
		kPutPropertyRequest, or kFindCollectionRequest
		@requestID is the ID of the request
	*/
	explicit ScriptReturnData( const ScriptID requestID ) ;
	/**
		Use this constructor to represent a successful kMethodRequest (with a return value), 
		kGetPropertyRequest, or kGetObjectRequest
		@requestID is the ID of the request
		@returnValue is the return value
	*/
	ScriptReturnData( const ScriptID requestID, ScriptData returnValue ) ;
	
	/**
		Use this constructor to represent an unsuccessful request by returning the error code
		@requestID is the ID of the request
		@param errorCode is the error code
	*/
	ScriptReturnData( const ScriptID requestID, const ErrorCode errorCode ) ;
	/**
		Destructor
	*/
	~ScriptReturnData() {}

	/**
		@return the request ID
	*/
	ScriptID GetRequestID() const { return fRequestID ; }

	/**
		@return the return value
	*/
	ScriptData GetReturnValue() const { return fReturnValue ; }

	/**
		@return the error code
	*/
	ErrorCode GetErrorCode() const { return fErrorCode ; }

	/**
		Retrieve the error string. Looks it up using error string services 
		if none has been set explicitly.
		@return the error string
	*/
	PMString GetErrorString() const ;

	/**
		Set an explicit error string
		@param errorString is the error string
	*/
	void SetErrorString( PMString errorString ) { swap( fErrorString, errorString ) ; }
	
	/** Defining swap() ensures efficient swapping of ScriptReturnData objects by swapping the remote parts.
	 */	
	friend inline void swap( ScriptReturnData& left, ScriptReturnData& right )
	{
		std::swap(left.fRequestID, right.fRequestID);
		swap(left.fReturnValue, right.fReturnValue);
		std::swap(left.fErrorCode, right.fErrorCode);
		swap(left.fErrorString, right.fErrorString);
		std::swap(left.fErrorInfo, right.fErrorInfo);
	}
	
	/** Copy constructor
	 */
	ScriptReturnData(const ScriptReturnData& other)
	: fRequestID(other.fRequestID), fReturnValue(other.fReturnValue),
	  fErrorCode(other.fErrorCode), fErrorString(other.fErrorString), fErrorInfo(other.fErrorInfo)
	{
	}
	
	/** Movable constructor - assumes ownership of the remote part
	 */
	ScriptReturnData(adobe::move_from<ScriptReturnData> other)
		: fRequestID(other.source.fRequestID), fReturnValue(adobe::move(other.source.fReturnValue)),
		  fErrorCode(other.source.fErrorCode), fErrorString(adobe::move(other.source.fErrorString))
	{
		std::swap(fErrorInfo, other.source.fErrorInfo);
	}
	
	/** operator assignment on a movable type takes parameter by value and consumes it
	 */
	ScriptReturnData& operator=(ScriptReturnData other)
    { swap(*this, other); return *this; }

protected:
	/**
		If the global error code is not kSuccess, update the local error code to match
		and then clear the global error code. This method is called by all constructors.
	*/
	void CheckGlobalErrorCode() ;

private:
	ScriptID					fRequestID ;
	ScriptData					fReturnValue ;
	ErrorCode					fErrorCode ;
	mutable PMString			fErrorString ;
	InterfacePtr<IPMUnknown>	fErrorInfo ;
} ;

typedef adobe::vector<ScriptReturnData> ScriptReturnDataList ;

#ifdef ID_ENABLE_DEBUGGING

/** Get the return data as a string (for trace) */
PUBLIC_DECL PMString GetAsString( const ScriptReturnData& srd, const RequestContext& context ) ;
/** Get a list of return data as a string (for trace) */
PUBLIC_DECL PMString GetAsString( const ScriptReturnDataList& srdl, const RequestContext& context ) ;

#endif

#endif
