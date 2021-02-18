//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/scripting/ScriptReturnData.cpp $
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

#include "VCPublicHeaders.h"
#include "ScriptReturnData.h"

#include "IErrorState.h"

#include "ErrorUtils.h"
#include "ScriptingID.h"

ScriptReturnData::ScriptReturnData( const ScriptID requestID ) :
	fRequestID( requestID ),
	fReturnValue(),
	fErrorCode( kSuccess ),
	fErrorString(),
	fErrorInfo()
{
	CheckGlobalErrorCode() ;
}

ScriptReturnData::ScriptReturnData( const ScriptID requestID, ScriptData returnValue ) :
	fRequestID( requestID ),
	fReturnValue( adobe::move(returnValue) ),
	fErrorCode( kSuccess ),
	fErrorString(),
	fErrorInfo()
{
	CheckGlobalErrorCode() ;
}

ScriptReturnData::ScriptReturnData( const ScriptID requestID, const ErrorCode errorCode ) :
	fRequestID( requestID ),
	fReturnValue(),
	fErrorCode( errorCode ),
	fErrorString(),
	fErrorInfo()
{
	CheckGlobalErrorCode() ;
}

void ScriptReturnData::CheckGlobalErrorCode()
{
	//Defer to the global error if there is one
	ErrorCode globalErrorCode = ErrorUtils::PMGetGlobalErrorCode() ;
	if ( globalErrorCode != kSuccess )
	{
#ifdef DEBUG
		if ( fErrorCode != globalErrorCode )
			TRACEFLOW( "Script:ScriptRequestHandler", "ScriptReturnData::SetErrorCode is overriding local error 0x%x with global error 0x%x\n", fErrorCode, globalErrorCode ) ;
#endif
		//Override the local error with the global one
		fErrorCode = globalErrorCode ;

		//Cache the error string if it was set explicitly
		InterfacePtr<IErrorState> iErrorState( GetExecutionContextSession(), UseDefaultIID() ) ;
		if ( iErrorState && iErrorState->IsExplicitString() )
		{
			fErrorString = iErrorState->GetErrorString() ;
			ASSERT_MSG( !fErrorString.empty(), "IErrorState::IsExplicitString is true, but IErrorState::GetErrorString returned empty string" ) ;
		}

		//Cache the error info
		fErrorInfo.reset( ErrorUtils::PMQueryGlobalErrorInfo() ) ;

		//Clear the global error state
		ErrorUtils::PMSetGlobalErrorCode( kSuccess ) ;
	}
}

PMString ScriptReturnData::GetErrorString() const
{
	ASSERT_MSG( fErrorCode != kSuccess || fErrorString.empty(), "Returning non-empty error string when error code is kSuccess" ) ;
	if ( fErrorCode != kSuccess )
	{
		//If the error string hasn't been set explicitly (which is typical), then we need to find or create one
		if ( fErrorString.empty() )
		{
			//Use the error string service providers to look up the associated error string
			fErrorString = ErrorUtils::PMGetErrorString( fErrorCode, fErrorInfo ) ;
		}

#ifdef DEBUG
		if ( fErrorString.empty() )
		{
			ASSERT_MSG( fErrorCode == kFailure || ( fErrorCode >= kFirstScriptErrorWithoutString && fErrorCode <= kLastScriptErrorWithoutString ),
						FORMAT_ARGS( "No error string for error code 0x%x. Missing ErrorStringService implementation?", fErrorCode ) ) ;
		}
#endif
	}

	return fErrorString;
}

#ifdef ID_ENABLE_DEBUGGING

PMString GetAsString( const ScriptReturnData& srd, const RequestContext& context )
{
	if ( srd.GetErrorCode() == kSuccess )
		return srd.GetReturnValue().GetValueAsString( context ) ;

	ASSERT( srd.GetReturnValue().IsEmpty() ) ;
	PMString s( "Error " ) ;
	s.AppendNumber( srd.GetErrorCode() ) ;
	s.Append( ": " ) ;
	s.Append( srd.GetErrorString() ) ;
	return s ;
}

PMString GetAsString( const ScriptReturnDataList& srdl, const RequestContext& context )
{
	PMString s( "[" ) ;
	for ( ScriptReturnDataList::const_iterator iter = srdl.begin() ; iter != srdl.end() ; ++iter )
	{
		if ( iter != srdl.begin() )
			s.Append( ", " ) ;
		s.Append( GetAsString( *iter, context ) ) ;
	}
	s.Append( "]" ) ;
	return s ;
}

#endif
