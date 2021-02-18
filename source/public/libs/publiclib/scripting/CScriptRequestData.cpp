//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/scripting/CScriptRequestData.cpp $
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
#include "CScriptRequestData.h"

#include "IScript.h"
#include "IScriptDOMCoverage.h"
#include "IScriptError.h"
#include "IScriptInfoManager.h"
#include "IScriptUtils.h"

#include <boost/bind.hpp>
#include <type_traits>
#ifdef ID_ENABLE_DEBUGGING

#include "Trace.h"
using namespace Trace;

#include "DebugClassUtils.h"

// Thread local data
static ModelThreadLocal_DebugClassUtilsBuffer  tl_IDNameBuff;

template <class T> static ConstCString GetIDName( T id )
{
	return DebugClassUtils::GetIDName( (DebugClassUtilsBuffer*)tl_IDNameBuff.Get(), id, kFalse ) ;
}

#endif

// Moved to PublicImpl.cpp in Utilities project
// CREATE_PMINTERFACE( CScriptRequestData, kCScriptRequestDataImpl ) ;

CScriptRequestData::CScriptRequestData( IPMUnknown* boss ) : 
	CPMUnknown<IScriptRequestData>(boss),
	fRequestContext()
{
	Reset();
}

CScriptRequestData::~CScriptRequestData()
{
}

void CScriptRequestData::Reset()
{
	fRequestData.clear();
	fReturnData.clear();
	fCollectiveReturnData.clear();
	fErrorPolicy = kReturnFirstError ;
	fSetPropertiesOrderPolicy = kDefaultOrder ;
	fTargetInfo = nil ;
	fRequestInfo = nil ;
	fRequestType = kUnknownRequest ;
	fIsMethodWithProperties = kFalse ;
	fAccessorForm = kFormInvalid ;
	fAccessorData.Reset();
	fHandlingPolicy = kDefault ;
	fRequestedDataType = kInvalidScriptID ;
 	fFormTestCaseSensitive = kFalse ;
}

ErrorCode CScriptRequestData::InsertRequestData( const ScriptID dataLocation, const ScriptData& data )
{
	::InsertOrReplaceKeyValue( fRequestData, dataLocation, data ) ;
	return kSuccess ;
}

ErrorCode CScriptRequestData::InsertRequestData( const ScriptRecordData& record )
{
	ErrorCode err = kSuccess ;

	for ( int32 i = 0 ; err == kSuccess && i < record.size() ; ++i )
	{
		err = InsertRequestData( record[i].Key(), record[i].Value() ) ;
	}

	return err ;
}

ErrorCode CScriptRequestData::ExtractRequestData( const ScriptID dataLocation, ScriptData& returnData ) const
{
	const ScriptRecordData& requestData = InternalGetRequestData() ;
	int32 loc = ::FindLocation( requestData, dataLocation ) ;
	if ( loc >= 0 )
	{
		returnData = requestData[loc].Value() ;
		return kSuccess ;
	}

	return kFailure ;
}

bool16 CScriptRequestData::HasRequestData( const ScriptID dataLocation ) const
{
	int32 loc = ::FindLocation( InternalGetRequestData(), dataLocation ) ;
	return ( loc >= 0 ) ;
}

ScriptRecordData CScriptRequestData::GetRequestData() const
{
	return InternalGetRequestData() ;
}

const ScriptRecordData& CScriptRequestData::InternalGetRequestData() const
{
	return fRequestData ;
}

static void TraceReturnData( const ScriptTargetReturnDataList& returnDataList, const ScriptListReturnDataList& returnDataList2, ConstCString status )
{
#ifdef DEBUG
	if ( TraceFlow::IsCategoryEnabled( "Script:ScriptReturnData" ) )
	{
		TRACE( "%s ", status ) ;
		for ( ScriptTargetReturnDataList::const_iterator iter = returnDataList.begin() ; iter != returnDataList.end() ; ++iter )
			TRACE( "0x%x:%d ", iter->first.get(), iter->second.size() ) ;
		for ( ScriptListReturnDataList::const_iterator iter2 = returnDataList2.begin() ; iter2 != returnDataList2.end() ; ++iter2 )
		{
			const ScriptList& targets = iter2->first ;
			ASSERT( targets.size() > 0 ) ;
			TRACE( "0x%x", targets[0].get() ) ;
			for ( int32 i = 1 ; i < targets.size() ; ++i )
				TRACE( "/0x%x", targets[i].get() ) ;
			TRACE( ":%d ", iter2->second.size() ) ;
		}
	}
#endif
}

static bool CompareTargets( const ScriptListReturnDataPair& strdp, const ScriptList& targets ) { return strdp.first == targets ; }

ScriptListReturnDataList::const_iterator FindTargets( const ScriptListReturnDataList& slrdl, const ScriptList& targets )
{
	return std::find_if( slrdl.begin(), slrdl.end(), boost::bind( &CompareTargets, _1, std::cref(targets) ) ) ;
}

ScriptListReturnDataList::iterator FindTargets( ScriptListReturnDataList& slrdl, const ScriptList& targets )
{
	return std::find_if( slrdl.begin(), slrdl.end(), boost::bind( &CompareTargets, _1, std::cref(targets) ) ) ;
}

void CScriptRequestData::ClearReturnData( const IScript* target )
{
	ASSERT( target != nil ) ;
	TRACEFLOW( "Script:ScriptReturnData", "SED(0x%x) ", this ) ;
	TraceReturnData( fReturnData, fCollectiveReturnData, "ClearRD Before" ) ;
	//Single target should not be in collective return data
	ASSERT( fCollectiveReturnData.end() == FindTargets( fCollectiveReturnData, ScriptList( 1, InterfacePtr<const IScript>( target, UseDefaultIID() ) ) ) ) ;

	//Find the return data that matches the target
	ScriptTargetReturnDataList::iterator iter = fReturnData.find( InterfacePtr<const IScript>( target, UseDefaultIID() ) ) ;
	if ( iter != fReturnData.end() )
		iter->second.clear() ;

	TraceReturnData( fReturnData, fCollectiveReturnData, "After" ) ;
	TRACEFLOW( "Script:ScriptReturnData", "\n" ) ;
}

void CScriptRequestData::ClearReturnData( const ScriptList& targets )
{
	ASSERT( targets.size() > 0 ) ;

	//For single target, delegate to single-target overload
	if ( targets.size() == 1 )
		return ClearReturnData( targets[0] ) ;

	TRACEFLOW( "Script:ScriptReturnData", "SED(0x%x) ", this ) ;
	TraceReturnData( fReturnData, fCollectiveReturnData, "ClearRD Before" ) ;

	//Find the collective return data that matches the targets
	ScriptListReturnDataList::iterator iter = FindTargets( fCollectiveReturnData, targets ) ;
	if ( iter != fCollectiveReturnData.end() )
	{
		iter->second.clear() ;
	}
	else
	{
		//Clear return data for each target individually
		for ( ScriptList::const_iterator iter2 = targets.begin() ; iter2 != targets.end() ; ++iter2 )
			ClearReturnData( *iter2 ) ;
	}

	TraceReturnData( fReturnData, fCollectiveReturnData, "After" ) ;
	TRACEFLOW( "Script:ScriptReturnData", "\n" ) ;
}

void CScriptRequestData::AppendReturnData( const IScript* target, const ScriptID requestID, const ErrorCode errorCode )
{
	AppendReturnData( target, ScriptReturnData( requestID, errorCode ) ) ;
}

void CScriptRequestData::AppendReturnData( const ScriptList& targets, const ScriptID requestID, const ErrorCode errorCode )
{
	AppendReturnData( targets, ScriptReturnData( requestID, errorCode ) ) ;
}

void CScriptRequestData::AppendReturnData( const IScript* target, const ScriptID requestID, const ScriptData& returnValue )
{
	AppendReturnData( target, ScriptReturnData( requestID, returnValue ) ) ;
}

void CScriptRequestData::AppendReturnData( const ScriptList& targets, const ScriptID requestID, const ScriptData& returnValue )
{
	AppendReturnData( targets, ScriptReturnData( requestID, returnValue ) ) ;
}

void CScriptRequestData::AppendReturnData( const IScript* target, const ScriptReturnData& data )
{
#ifdef DEBUG
	if ( data.GetErrorCode() == kFailure )
	{
		PMString request /*= Utils<IScriptUtils>()->GetScriptID( data.GetRequestID() )*/ ;
		if ( GetRequestInfo() && GetRequestInfo()->GetScriptID() == data.GetRequestID() )
		{
			request = GetRequestInfo()->WhoAmI() ;
		}
		else	//p_Properties case
		{
			InterfacePtr<IScriptInfoManager> scriptInfoMgr( Utils<IScriptUtils>()->QueryScriptInfoManager( GetRequestContext() ) ) ;
			request = scriptInfoMgr->FindPropertyName( data.GetRequestID() ) ;
		}
		ASSERT_FAIL( FORMAT_ARGS( "Script request %s on object '%s' returning generic error kFailure. "
								  "Eng: Please replace with a more specific error code. "
								  "QE: Please report this assert as a 2/2 bug with keyword 'Better Scripting Error.'", 
								  request.GetUTF8String().c_str(), target->GetObjectInfo(GetRequestContext())->GetName().GetUTF8String().c_str()));
	}
#endif
	ASSERT( target != nil ) ;
	TRACEFLOW( "Script:ScriptReturnData", "SED(0x%x) ", this ) ;
	TraceReturnData( fReturnData, fCollectiveReturnData, "AppendRD Before" ) ;
	//Single target should not be in collective return data
	ASSERT( fCollectiveReturnData.end() == FindTargets( fCollectiveReturnData, ScriptList( 1, InterfacePtr<const IScript>( target, UseDefaultIID() ) ) ) ) ;

	//Find the return data that matches the target
	ScriptTargetReturnDataList::iterator iter = fReturnData.find( InterfacePtr<const IScript>( target, UseDefaultIID() ) ) ;
	if ( iter != fReturnData.end() )
		iter->second.push_back( data ) ;
	else
		fReturnData.insert( ScriptTargetReturnDataPair( InterfacePtr<IScript>( target, UseDefaultIID() ), ScriptReturnDataList( 1, data ) ) ) ;

	TraceReturnData( fReturnData, fCollectiveReturnData, "After" ) ;
	TRACEFLOW( "Script:ScriptReturnData", "\n" ) ;

	InterfacePtr<IScriptDOMCoverageHelper> domCoverage( this, UseDefaultIID() ) ;
	if ( domCoverage )
		domCoverage->LogRequest( this, data ) ;
}

void CScriptRequestData::AppendReturnData( const ScriptList& targets, const ScriptReturnData& data )
{
	ASSERT( targets.size() > 0 ) ;

	//For single target, delegate to single-target overload
	if ( targets.size() == 1 )
		return AppendReturnData( targets[0], data ) ;

#ifdef DEBUG
	if ( data.GetErrorCode() == kFailure )
	{
		PMString request /*= Utils<IScriptUtils>()->GetScriptID( data.GetRequestID() )*/ ;
		if ( GetRequestInfo() && GetRequestInfo()->GetScriptID() == data.GetRequestID() )
		{
			request = GetRequestInfo()->WhoAmI() ;
		}
		else	//p_Properties case
		{
			InterfacePtr<IScriptInfoManager> scriptInfoMgr( Utils<IScriptUtils>()->QueryScriptInfoManager( GetRequestContext() ) ) ;
			request = scriptInfoMgr->FindPropertyName( data.GetRequestID() ) ;
		}
		ASSERT_FAIL( FORMAT_ARGS( "Script request %s on object '%s' returning generic error kFailure. "
								  "Eng: Please replace with a more specific error code. "
								  "QE: Please report this assert as a 2/2 bug with keyword 'Better Scripting Error.'", 
								  request.GetUTF8String().c_str(), targets[0]->GetObjectInfo(GetRequestContext())->GetName().GetUTF8String().c_str()));
	}
#endif
	TRACEFLOW( "Script:ScriptReturnData", "SED(0x%x) ", this ) ;
	TraceReturnData( fReturnData, fCollectiveReturnData, "AppendRD Before" ) ;

	//Find the return data that matches the targets
	ScriptListReturnDataList::iterator iter = FindTargets( fCollectiveReturnData, targets ) ;
	if ( iter != fCollectiveReturnData.end() )
		iter->second.push_back( data ) ;
	else
		fCollectiveReturnData.push_back( ScriptListReturnDataPair( targets, ScriptReturnDataList( 1, data ) ) ) ;

	TraceReturnData( fReturnData, fCollectiveReturnData, "After" ) ;
	TRACEFLOW( "Script:ScriptReturnData", "\n" ) ;

	InterfacePtr<IScriptDOMCoverageHelper> domCoverage( this, UseDefaultIID() ) ;
	if ( domCoverage )
		domCoverage->LogRequest( this, data ) ;
}

void CScriptRequestData::AppendReturnData( const IScript* target, const ScriptReturnDataList& data )
{
	ASSERT( target != nil ) ;
	TRACEFLOW( "Script:ScriptReturnData", "SED(0x%x) ", this ) ;
	TraceReturnData( fReturnData, fCollectiveReturnData, "AppendRD Before" ) ;
	//Single target should not be in collective return data
	ASSERT( fCollectiveReturnData.end() == FindTargets( fCollectiveReturnData, ScriptList( 1, InterfacePtr<const IScript>( target, UseDefaultIID() ) ) ) ) ;

	//Find the return data that matches the target
	ScriptTargetReturnDataList::iterator iter = fReturnData.find( InterfacePtr<const IScript>( target, UseDefaultIID() ) ) ;
	if ( iter != fReturnData.end() )
		iter->second.insert( iter->second.end(), data.begin(), data.end() ) ;
	else
		fReturnData.insert( ScriptTargetReturnDataPair( InterfacePtr<IScript>( target, UseDefaultIID() ), data ) ) ;

	TraceReturnData( fReturnData, fCollectiveReturnData, "After" ) ;
	TRACEFLOW( "Script:ScriptReturnData", "\n" ) ;
}

void CScriptRequestData::AppendReturnData( const ScriptList& targets, const ScriptReturnDataList& data )
{
	ASSERT( targets.size() > 0 ) ;

	//For single target, delegate to single-target overload
	if ( targets.size() == 1 )
		return AppendReturnData( targets[0], data ) ;

	TRACEFLOW( "Script:ScriptReturnData", "SED(0x%x) ", this ) ;
	TraceReturnData( fReturnData, fCollectiveReturnData, "AppendRD Before" ) ;

	//Find the return data that matches the targets
	ScriptListReturnDataList::iterator iter = FindTargets( fCollectiveReturnData, targets ) ;
	if ( iter != fCollectiveReturnData.end() )
		iter->second.insert( iter->second.end(), data.begin(), data.end() ) ;
	else
		fCollectiveReturnData.push_back( ScriptListReturnDataPair( targets, data ) ) ;

	TraceReturnData( fReturnData, fCollectiveReturnData, "After" ) ;
	TRACEFLOW( "Script:ScriptReturnData", "\n" ) ;
}

void CScriptRequestData::ReplaceReturnData( const IScript* target, const ScriptReturnDataList& data )
{
	ASSERT( target != nil ) ;
	TRACEFLOW( "Script:ScriptReturnData", "SED(0x%x) ", this ) ;
	TraceReturnData( fReturnData, fCollectiveReturnData, "ReplaceRD Before" ) ;
	//Single target should not be in collective return data
	ASSERT( fCollectiveReturnData.end() == FindTargets( fCollectiveReturnData, ScriptList( 1, InterfacePtr<const IScript>( target, UseDefaultIID() ) ) ) ) ;

	//Find the return data that matches the target
	ScriptTargetReturnDataList::iterator iter = fReturnData.find( InterfacePtr<const IScript>( target, UseDefaultIID() ) ) ;
	if ( iter != fReturnData.end() )
		iter->second = data ;
	else
		fReturnData.insert( ScriptTargetReturnDataPair( InterfacePtr<IScript>( target, UseDefaultIID() ), data ) ) ;

	TraceReturnData( fReturnData, fCollectiveReturnData, "After" ) ;
	TRACEFLOW( "Script:ScriptReturnData", "\n" ) ;
}

void CScriptRequestData::ReplaceReturnData( const ScriptList& targets, const ScriptReturnDataList& data )
{
	ASSERT( targets.size() > 0 ) ;

	//For single target, delegate to single-target overload
	if ( targets.size() == 1 )
		return ReplaceReturnData( targets[0], data ) ;

	TRACEFLOW( "Script:ScriptReturnData", "SED(0x%x) ", this ) ;
	TraceReturnData( fReturnData, fCollectiveReturnData, "ReplaceRD Before" ) ;

	//Find the return data that matches the targets
	ScriptListReturnDataList::iterator iter = FindTargets( fCollectiveReturnData, targets ) ;
	if ( iter != fCollectiveReturnData.end() )
		iter->second = data ;
	else
		fCollectiveReturnData.push_back( ScriptListReturnDataPair( targets, data ) ) ;

	TraceReturnData( fReturnData, fCollectiveReturnData, "After" ) ;
	TRACEFLOW( "Script:ScriptReturnData", "\n" ) ;
}

uint32 CScriptRequestData::GetNumReturnData( const IScript* target ) const
{
	ASSERT( target != nil ) ;
	//Single target should not be in collective return data
	ASSERT( fCollectiveReturnData.end() == FindTargets( fCollectiveReturnData, ScriptList( 1, InterfacePtr<const IScript>( target, UseDefaultIID() ) ) ) ) ;

	//Find the return data that matches this target
	ScriptTargetReturnDataList::const_iterator iter = fReturnData.find( InterfacePtr<const IScript>( target, UseDefaultIID() ) ) ;
	if ( iter != fReturnData.end() )
		return static_cast<uint32>(iter->second.size()) ;
	return 0 ;
}

uint32 CScriptRequestData::GetNumReturnData( const ScriptList& targets ) const
{
	ASSERT( targets.size() > 0 ) ;

	//For single target, delegate to single-target overload
	if ( targets.size() == 1 )
		return GetNumReturnData( targets[0] ) ;

	ScriptListReturnDataList::const_iterator iter = FindTargets( fCollectiveReturnData, targets ) ;
	if ( iter != fCollectiveReturnData.end() )
	{
		return static_cast<uint32>(iter->second.size()) ;
	}
	else
	{
		//Get all return data for each target individually
		uint32 count = 0 ;
		for ( ScriptList::const_iterator iter2 = targets.begin() ; iter2 != targets.end() ; ++iter2 )
		{
			//Find the return data that matches this target
			ScriptTargetReturnDataList::const_iterator iter3 = fReturnData.find( *iter2 ) ;
			if ( iter3 != fReturnData.end() )
				count += static_cast<uint32>(iter3->second.size()) ;
		}
		return count ;
	}
}

ScriptReturnData CScriptRequestData::GetNthReturnData( const IScript* target, uint32 n ) const
{
	ASSERT( target != nil ) ;
	//Single target should not be in collective return data
	ASSERT( fCollectiveReturnData.end() == FindTargets( fCollectiveReturnData, ScriptList( 1, InterfacePtr<const IScript>( target, UseDefaultIID() ) ) ) ) ;

	//Find the return data that matches this target
	ScriptTargetReturnDataList::const_iterator iter = fReturnData.find( InterfacePtr<const IScript>( target, UseDefaultIID() ) ) ;
	ASSERT( iter != fReturnData.end() && n < iter->second.size() ) ;
	return iter->second[n] ;
}

ScriptReturnData CScriptRequestData::GetNthReturnData( const ScriptList& targets, uint32 n ) const
{
	ASSERT( targets.size() > 0 ) ;

	//For single target, delegate to single-target overload
	if ( targets.size() == 1 )
		return GetNthReturnData( targets[0], n ) ;

	ScriptListReturnDataList::const_iterator iter = FindTargets( fCollectiveReturnData, targets ) ;
	if ( iter != fCollectiveReturnData.end() )
	{
		ASSERT( n < iter->second.size() ) ;
		return iter->second[n] ;
	}
	else
	{
		//Get all return data for each target individually
		ScriptReturnDataList srdl ;
		for ( ScriptList::const_iterator iter2 = targets.begin() ; iter2 != targets.end() ; ++iter2 )
		{
			//Find the return data that matches this target
			ScriptTargetReturnDataList::const_iterator iter3 = fReturnData.find( *iter2 ) ;
			if ( iter3 != fReturnData.end() )
				srdl.insert( srdl.end(), iter3->second.begin(), iter3->second.end() ) ;
		}
		ASSERT( n < srdl.size() ) ;
		return srdl[n] ;
	}
}

ScriptReturnDataList CScriptRequestData::GetAllReturnData( const IScript* target ) const
{
	ASSERT( target != nil ) ;
	TRACEFLOW( "Script:ScriptReturnData", "SED(0x%x) ", this ) ;
	TraceReturnData( fReturnData, fCollectiveReturnData, "GetRD Before" ) ;
	//Single target should not be in collective return data
	ASSERT( fCollectiveReturnData.end() == FindTargets( fCollectiveReturnData, ScriptList( 1, InterfacePtr<const IScript>( target, UseDefaultIID() ) ) ) ) ;

	//Find the return data that matches this target
	ScriptTargetReturnDataList::const_iterator iter = fReturnData.find( InterfacePtr<const IScript>( target, UseDefaultIID() ) ) ;
	if ( iter != fReturnData.end() )
	{
		TraceReturnData( fReturnData, fCollectiveReturnData, "After" ) ;
		TRACEFLOW( "Script:ScriptReturnData", "\n" ) ;
		return iter->second ;
	}
	else
	{
		TraceReturnData( fReturnData, fCollectiveReturnData, "After" ) ;
		TRACEFLOW( "Script:ScriptReturnData", "\n" ) ;
		return ScriptReturnDataList() ;
	}
}

ScriptReturnDataList CScriptRequestData::GetAllReturnData( const ScriptList& targets ) const
{
	ASSERT( targets.size() > 0 ) ;

	//For single target, delegate to single-target overload
	if ( targets.size() == 1 )
		return GetAllReturnData( targets[0] ) ;

	TRACEFLOW( "Script:ScriptReturnData", "SED(0x%x) ", this ) ;
	TraceReturnData( fReturnData, fCollectiveReturnData, "GetRD Before" ) ;

	ScriptListReturnDataList::const_iterator iter = FindTargets( fCollectiveReturnData, targets ) ;
	if ( iter != fCollectiveReturnData.end() )
	{
		TraceReturnData( fReturnData, fCollectiveReturnData, "After" ) ;
		TRACEFLOW( "Script:ScriptReturnData", "\n" ) ;
		return iter->second ;
	}
	else
	{
		//Get all return data for each target individually
		ScriptReturnDataList srdl ;
		for ( ScriptList::const_iterator iter2 = targets.begin() ; iter2 != targets.end() ; ++iter2 )
		{
			//Find the return data that matches this target
			ScriptTargetReturnDataList::const_iterator iter3 = fReturnData.find( *iter2 ) ;
			if ( iter3 != fReturnData.end() )
				srdl.insert( srdl.end(), iter3->second.begin(), iter3->second.end() ) ;
		}
		TraceReturnData( fReturnData, fCollectiveReturnData, "After" ) ;
		TRACEFLOW( "Script:ScriptReturnData", "\n" ) ;
		return srdl ;
	}
}

void CScriptRequestData::SetErrorPolicy( ErrorPolicy policy )
{
	fErrorPolicy = policy ;
}

ErrorPolicy CScriptRequestData::GetErrorPolicy() const
{
	return fErrorPolicy ;
}

void CScriptRequestData::SetSetPropertiesOrderPolicy( SetPropertiesOrderPolicy policy )
{
	fSetPropertiesOrderPolicy = policy ;
}

SetPropertiesOrderPolicy CScriptRequestData::GetSetPropertiesOrderPolicy() const
{
	return fSetPropertiesOrderPolicy ;
}

void CScriptRequestData::SetMethod( const ScriptElementID methodID )
{
	InterfacePtr<IScriptInfoManager> scriptInfoMgr( Utils<IScriptUtils>()->QueryScriptInfoManager( fRequestContext ) ) ;
	ASSERT( scriptInfoMgr ) ;
	if ( scriptInfoMgr )
	{
		const MethodScriptElement* pMethod = scriptInfoMgr->FindMethod( methodID ) ;
#ifdef DEBUG
        ASSERT_MSG( pMethod, FORMAT_ARGS( "Missing scriptinfo for method %s", GetIDName( methodID ) ) ) ;
#endif
		if ( pMethod )
			SetMethod( pMethod ) ;
	}
}

void CScriptRequestData::SetMethod( const MethodScriptElement* pMethod )
{
	ASSERT_MSG( pMethod != nil, "Missing ScriptElement info for method request" ) ;
	fRequestType = kMethodRequest ;
	fRequestInfo = pMethod ;
}

bool16 CScriptRequestData::IsMethod() const
{
	return fRequestType == kMethodRequest ;
}

void CScriptRequestData::SetMethodWithProperties( bool16 withProperties )
{
//	ASSERT_MSG( IsMethod(), "Calling SetMethodWithProperties on a non-method request" ) ;
	fIsMethodWithProperties = withProperties ;
}

bool16 CScriptRequestData::IsMethodWithProperties() const
{
//	ASSERT_MSG( fRequestType != kUnknownRequest, "Calling IsMethodWithProperties on unknown request" ) ;
	return fIsMethodWithProperties;
}

void CScriptRequestData::SetPropertyGet( const ScriptElementID propID )
{
	InterfacePtr<IScriptInfoManager> scriptInfoMgr( Utils<IScriptUtils>()->QueryScriptInfoManager( fRequestContext ) ) ;
	ASSERT( scriptInfoMgr ) ;
	if ( scriptInfoMgr )
	{
		const PropertyScriptElement* pProp = scriptInfoMgr->FindProperty( propID ) ;
#ifdef DEBUG
        ASSERT_MSG( pProp, FORMAT_ARGS( "Missing scriptinfo for property %s", GetIDName( propID ) ) ) ;
#endif
        if ( pProp )
			SetPropertyGet( pProp ) ;
	}
}

void CScriptRequestData::SetPropertyGet( const PropertyScriptElement* pProp )
{
	ASSERT_MSG( pProp != nil, "Missing ScriptElement info for property get request" ) ;
	fRequestType = kGetPropertyRequest ;
	fRequestInfo = pProp ;
}

bool16 CScriptRequestData::IsPropertyGet() const
{
	return fRequestType == kGetPropertyRequest ;
}

void CScriptRequestData::SetPropertyPut( const ScriptElementID propID )
{
	InterfacePtr<IScriptInfoManager> scriptInfoMgr( Utils<IScriptUtils>()->QueryScriptInfoManager( fRequestContext ) ) ;
	ASSERT( scriptInfoMgr ) ;
	if ( scriptInfoMgr )
	{
		const PropertyScriptElement* pProp = scriptInfoMgr->FindProperty( propID ) ;
#ifdef DEBUG		
        ASSERT_MSG( pProp, FORMAT_ARGS( "Missing scriptinfo for property %s", GetIDName( propID ) ) ) ;
#endif
		if ( pProp )
			SetPropertyPut( pProp ) ;
	}
}

void CScriptRequestData::SetPropertyPut( const PropertyScriptElement* pProp )
{
	ASSERT_MSG( pProp != nil, "Missing ScriptElement info for property put request" ) ;
	fRequestType = kPutPropertyRequest ;
	fRequestInfo = pProp ;
}

bool16 CScriptRequestData::IsPropertyPut() const
{
	return fRequestType == kPutPropertyRequest ;
}

void CScriptRequestData::SetFindCollection( const ScriptElementID objID )
{
	InterfacePtr<IScriptInfoManager> scriptInfoMgr( Utils<IScriptUtils>()->QueryScriptInfoManager( fRequestContext ) ) ;
	ASSERT( scriptInfoMgr ) ;
	if ( scriptInfoMgr )
	{
		const ObjectScriptElement* pObj = scriptInfoMgr->FindObject( objID ) ;
#ifdef DEBUG
        ASSERT_MSG( pObj, FORMAT_ARGS( "Missing scriptinfo for object %s", GetIDName( objID ) ) ) ;
#endif
		if ( pObj )
			SetFindCollection( pObj ) ;
	}
}

void CScriptRequestData::SetFindCollection( const ObjectScriptElement* pObj )
{
	ASSERT_MSG( pObj != nil, "Missing ScriptElement info for collection request" ) ;
	fRequestType = kFindCollectionRequest ;
	fRequestInfo = pObj ;
}

bool16 CScriptRequestData::IsFindCollection() const
{
	return fRequestType == kFindCollectionRequest ;
}

IScriptRequestData::RequestType CScriptRequestData::GetRequestType() const
{
	return fRequestType ;
}

const ScriptElement* CScriptRequestData::GetRequestInfo() const
{
	ASSERT_MSG( fRequestInfo, "Request info has not been set" ) ;
	return fRequestInfo ;
}

void CScriptRequestData::SetGetObject( const ScriptElementID objID, SpecifierForm accessorForm, const ScriptData& accessorData )
{
	InterfacePtr<IScriptInfoManager> scriptInfoMgr( Utils<IScriptUtils>()->QueryScriptInfoManager( fRequestContext ) ) ;
	ASSERT( scriptInfoMgr ) ;
	if ( scriptInfoMgr )
	{
		const ObjectScriptElement* pObj = scriptInfoMgr->FindObject( objID ) ;
#ifdef DEBUG
        ASSERT_MSG( pObj, FORMAT_ARGS( "Missing scriptinfo for object %s", GetIDName( objID ) ) ) ;
#endif
		if ( pObj )
			SetGetObject( pObj, accessorForm, accessorData ) ;
	}
}

void CScriptRequestData::SetGetObject( const ObjectScriptElement* pObj, SpecifierForm accessorForm, const ScriptData& accessorData )
{
	ASSERT_MSG( pObj != nil, "Missing ScriptElement info for collection request" ) ;
	fRequestType = kGetObjectRequest ;
	fRequestInfo = pObj ;
	fAccessorForm = accessorForm ;
	fAccessorData = accessorData ;
}

bool16 CScriptRequestData::IsGetObject() const
{
	return fRequestType == kGetObjectRequest ;
}

SpecifierForm CScriptRequestData::GetAccessorForm() const
{
	return fAccessorForm ;
}

ScriptData CScriptRequestData::GetAccessorData() const
{
	return fAccessorData;
}

void CScriptRequestData::SetTargetInfo( const ScriptElementID objectID )
{
	InterfacePtr<IScriptInfoManager> scriptInfoMgr( Utils<IScriptUtils>()->QueryScriptInfoManager( fRequestContext ) ) ;
	ASSERT( scriptInfoMgr ) ;
	if ( scriptInfoMgr )
	{
		const ObjectScriptElement* pObject = scriptInfoMgr->FindObject( objectID ) ;
#ifdef DEBUG
        ASSERT_MSG( pObject, FORMAT_ARGS( "Missing scriptinfo for object %s", GetIDName( objectID ) ) ) ;
#endif
		if ( pObject )
			SetTargetInfo( pObject ) ;
	}
}

void CScriptRequestData::SetTargetInfo( const ObjectScriptElement* pObject )
{
	//ASSERT_MSG( pObject != nil, "Missing object info for target" ) ;	//may happen in CScriptRequestData::CloneRequestData
	fTargetInfo = pObject ;
}

const ObjectScriptElement* CScriptRequestData::GetTargetInfo() const
{
//	ASSERT_MSG( fTargetInfo, "Target info has not been set" ) ;	//may be checked by the UserActionManager
	return fTargetInfo ;
}

const ScriptID CScriptRequestData::GetDesiredType() const
{
	if ( GetRequestType() == kGetObjectRequest || GetRequestType() == kFindCollectionRequest )
	{
		ASSERT( fRequestInfo ) ;
		if ( fRequestInfo )
			return fRequestInfo->GetScriptID() ;
	}
	else if ( GetRequestType() != kUnknownRequest )
	{
		ASSERT( fTargetInfo ) ;
        if ( fTargetInfo )
			return fTargetInfo->GetScriptID() ;
	}

	return kInvalidScriptID ;
}

void CScriptRequestData::SetTargetHandlingPolicy( TargetHandlingPolicy policy )
{
	fHandlingPolicy = policy ;
}

IScriptRequestData::TargetHandlingPolicy CScriptRequestData::GetTargetHandlingPolicy() const
{
	return fHandlingPolicy ;
}

void CScriptRequestData::SetRequestedDataType( const ScriptID requestedType )
{
	fRequestedDataType = requestedType ;
}

const ScriptID CScriptRequestData::GetRequestedDataType() const
{
	return fRequestedDataType ;
}

void CScriptRequestData::SetFormTestCaseSensitive( bool16 caseSensitive )
{
	fFormTestCaseSensitive = caseSensitive;
}

bool16 CScriptRequestData::GetFormTestCaseSensitive() const
{
	return fFormTestCaseSensitive;
}

const EngineContext& CScriptRequestData::GetRequestContext() const
{
	return fRequestContext ;
}

void CScriptRequestData::SetRequestContext( const EngineContext& context )
{
	fRequestContext = context ;
}

void CScriptRequestData::CloneRequestData( IScriptRequestData* other ) const
{
	if ( other != nil )
	{
		//other->Reset() ;
		ASSERT( RequestContext( fRequestContext ) == RequestContext( other->GetRequestContext() ) ) ;
		other->InsertRequestData( InternalGetRequestData() ) ;
		for ( ScriptTargetReturnDataList::const_iterator iter = fReturnData.begin() ; iter != fReturnData.end() ; ++iter )
			other->ReplaceReturnData( iter->first, iter->second ) ;
		for ( ScriptListReturnDataList::const_iterator iter2 = fCollectiveReturnData.begin() ; iter2 != fCollectiveReturnData.end() ; ++iter2 )
			other->ReplaceReturnData( iter2->first, iter2->second ) ;
		other->SetSetPropertiesOrderPolicy( fSetPropertiesOrderPolicy ) ;
		other->SetTargetInfo( fTargetInfo ) ;
		if ( IsMethod() )
			other->SetMethod( (const MethodScriptElement*) fRequestInfo ) ;
		else if ( IsPropertyGet() )
			other->SetPropertyGet( (const PropertyScriptElement*) fRequestInfo ) ;
		else if ( IsPropertyPut() )
			other->SetPropertyPut( (const PropertyScriptElement*) fRequestInfo ) ;
		else if ( IsGetObject() )
			other->SetGetObject( (const ObjectScriptElement*) fRequestInfo, fAccessorForm, fAccessorData ) ;
		else if ( IsFindCollection() )
			other->SetFindCollection( (const ObjectScriptElement*) fRequestInfo ) ;
		else
			ASSERT_MSG( fRequestType == kUnknownRequest && fRequestInfo == nil, "CScriptRequestData::CloneRequestData - Unexpected request type" ) ;
		other->SetTargetHandlingPolicy( fHandlingPolicy ) ;
		other->SetRequestedDataType( fRequestedDataType ) ;
		other->SetFormTestCaseSensitive( fFormTestCaseSensitive ) ;
		other->SetMethodWithProperties( fIsMethodWithProperties ) ;

		InterfacePtr<IScriptError> thisScriptError( this, UseDefaultIID() ) ;
		InterfacePtr<IScriptError> otherScriptError( other, UseDefaultIID() ) ;
		thisScriptError->CopyErrorInfoInto( otherScriptError ) ;
	}
}

//To support recycling of ScriptRequestData bosses in CScriptManager::CreateScriptRequestData,
//we have to reset this interface on the last client release. We assume that all 
//ScriptRequestData bosses are created via CreateScriptRequestData and that that reference
//is the last one released by the client.
void CScriptRequestData::Release() const
{
	{	//scope IControllingUnknown
		InterfacePtr<IControllingUnknown> boss( this, UseDefaultIID() ) ;
		ASSERT( boss ) ;
		if ( boss && boss->GetRefCount() == 3 )	//one ref being released by this method, one for the cache in CScriptManager and one for IControllingUnknown
		{
#ifdef DEBUG
            ASSERT( fHelperInterface.fInterfaceRefCount == 2 ) ;	//two of this bosses' references must be this interface or our assumption that this is the last client ref is false
#endif
            const_cast<CScriptRequestData*>(this)->Reset() ;

			//Reset other interfaces on this boss
			InterfacePtr<IScriptError> scriptError( this, UseDefaultIID() ) ;
			scriptError->Reset() ;

			const_cast<CScriptRequestData*>(this)->SetRequestContext( EngineContext() ) ;	//don't hold a reference to IScriptEngine, since it is holding a reference to us!
		}
	}
	CPMUnknown<IScriptRequestData>::Release() ;
}
