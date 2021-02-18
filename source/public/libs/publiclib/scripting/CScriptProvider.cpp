//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/scripting/CScriptProvider.cpp $
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
#include "CScriptProvider.h"

#include "IScriptManager.h"
#include "IScriptRequestHandler.h"

#include "INXPerformanceStat.h"

#ifdef MACINTOSH
using std::rand;
#endif

#ifdef ID_ENABLE_DEBUGGING

#include "IScriptInfoManager.h"
#include "Trace.h"
using namespace Trace;

#endif

//---------------------------------------------------------------------------------------------
// Class CScriptProvider
//---------------------------------------------------------------------------------------------

CScriptProvider::CScriptProvider( IPMUnknown* boss ) :
	Inherited( boss )
{
}

CScriptProvider::~CScriptProvider()
{
}

//This method is only relevant for subclasses of RepresentScriptProvider
void CScriptProvider::GetObject( IScriptRequestData* data, IScript* parent )
{
	ASSERT_UNIMPLEMENTED();
	data->AppendReturnData( parent, data->GetRequestInfo()->GetScriptID(), kFailure ) ;
}

//Most subclasses will not need to override this method
void CScriptProvider::HandleMethodOnObjects( ScriptID methodID, IScriptRequestData* data, const ScriptList& scriptList )
{
	//Handle method for each individual object separately
	for ( int32 i = 0 ; i < scriptList.size() ; i++ )
	{
		const uint32 preReturnDataLen = data->GetNumReturnData( scriptList[i] ) ;
		ErrorCode err = kInvalidScriptTargetError ;
		if ( scriptList[i] != nil )
		{
#ifdef DEBUG
			if (Utils<IScriptUtils>()->IsINX(data->GetRequestContext()))
				ASSERT(!scriptList[i]->HasBeenDeleted( data->GetRequestContext() ));
#endif
			if ( !Utils<IScriptUtils>()->IsINX(data->GetRequestContext())  && scriptList[i]->HasBeenDeleted( data->GetRequestContext() ) )
				err = kObjectDeletedError ;
			else
			{
				INX_DECLARE_CLOCK(inxStart, kINXModelTime);
				err = HandleMethod( methodID, data, scriptList[i] ) ;
				INX_INC_METRIC(kINXModelTime, INX_DIFF_CLOCK(inxStart));
			}
		}
#ifdef ID_ENABLE_DEBUGGING
		const ScriptReturnDataList& returnDataList = data->GetAllReturnData( scriptList[i] ) ;
		InterfacePtr<IScriptInfoManager> scriptInfoMgr( Utils<IScriptUtils>()->QueryScriptInfoManager( data->GetRequestContext() ) ) ;
		PMString requestDescription( scriptInfoMgr->FindMethodName( methodID ) ) ;
		requestDescription.Append( "' on object '" ) ;
		requestDescription.Append( scriptList[i]->GetObjectInfo( data->GetRequestContext() )->GetName() ) ;
#endif
		if ( err != kSuccess )
		{
#ifdef DEBUG
            ASSERT_MSG(returnDataList.size() == preReturnDataLen, FORMAT_ARGS("HandleMethod request for method '%s' returned an error AND a value", requestDescription.GetUTF8String().c_str()));
#endif
			data->AppendReturnData( scriptList[i], methodID, err ) ;	//push the script provider's error case here
		}
		else
		{
			ASSERT( data->IsMethod() ) ;
			if ( data->IsMethod() && kScriptInfoVoidType == static_cast<const MethodScriptElement*>( data->GetRequestInfo() )->GetReturnType(nil).GetType() )
			{
#ifdef DEBUG
                ASSERT_MSG(returnDataList.size() == preReturnDataLen, FORMAT_ARGS("HandleMethod request for method '%s' declared as void but returned a value", requestDescription.GetUTF8String().c_str()));
#endif
				data->AppendReturnData( scriptList[i], methodID, kSuccess ) ;	//push the script provider's success case here
			}
			else
			{
#ifdef DEBUG
                ASSERT_MSG(returnDataList.size() > preReturnDataLen, FORMAT_ARGS("HandleMethod request for method '%s' returned kSuccess but no value", requestDescription.GetUTF8String().c_str()));
				ASSERT_MSG(returnDataList.size() < preReturnDataLen + 2, FORMAT_ARGS("HandleMethod request for method '%s' returned more than one value", requestDescription.GetUTF8String().c_str()));
				if ( returnDataList.size() > preReturnDataLen )
					ASSERT_MSG( returnDataList[preReturnDataLen].GetRequestID() == methodID, FORMAT_ARGS( "HandleMethod request for method '%s' returned value for method '%s'",
					requestDescription.GetUTF8String().c_str(), Utils<IScriptUtils>()->GetScriptID(returnDataList[preReturnDataLen].GetRequestID()).GetUTF8String().c_str()));	//sanity check
#endif
			}
		}

		//Check the error code in the return data because it may have been overridden with a global error code
		ASSERT_MSG( data->GetNumReturnData( scriptList[i] ) == preReturnDataLen + 1, "HandleMethod request has not called AppendReturnData" ) ;
		if ( data->GetNumReturnData( scriptList[i] ) > preReturnDataLen )
		{
			const ScriptReturnData returnData = data->GetNthReturnData( scriptList[i], preReturnDataLen ) ;
			err = returnData.GetErrorCode() ;
			TRACEFLOW( "Script:ScriptRequestHandler", "  %s handled method '%s' with return data %s\n",
				GetIDName(::GetClass(this)), requestDescription.GetUTF8String().c_str(),
				GetAsString(returnData, data->GetRequestContext()).GetUTF8String().c_str());
		}
		if ( err != kSuccess && data->GetErrorPolicy() == kReturnFirstError )
			break ;
	}
}

//Most subclasses will override this method
ErrorCode CScriptProvider::HandleMethod( ScriptID methodID, IScriptRequestData* data, IScript* script )
{
#ifdef DEBUG
    ASSERT_FAIL( FORMAT_ARGS( "%s failed to handle %s", GetIDName( ::GetClass( this ) ), data->GetRequestInfo()->WhoAmI() ) ) ;
#endif
    return kRequestNotHandledError ;
}

//Most subclasses will not need to override this method
void CScriptProvider::AccessPropertyOnObjects( ScriptID propID, IScriptRequestData* data, const ScriptList& scriptList )
{
	//Access property for each individual object separately
	for ( int32 i = 0 ; i < scriptList.size() ; i++ )
	{
		const uint32 preReturnDataLen = data->GetNumReturnData( scriptList[i] ) ;
		ErrorCode err = kInvalidScriptTargetError ;
		if ( scriptList[i] != nil )
		{
			INX_DECLARE_CLOCK(inxStart, kINXModelTime);

#ifdef DEBUG
			if (Utils<IScriptUtils>()->IsINX(data->GetRequestContext()))
				ASSERT(!scriptList[i]->HasBeenDeleted( data->GetRequestContext() ));
#endif
			if ( !Utils<IScriptUtils>()->IsINX(data->GetRequestContext()) && scriptList[i]->HasBeenDeleted( data->GetRequestContext() ) )
				err = kObjectDeletedError ;
			else
				err = PreAccessProperty( propID, data, scriptList[i] ) ;

			if ( err == kSuccess )
				err = AccessProperty( propID, data, scriptList[i] ) ;

			if ( err == kSuccess )
				err = PostAccessProperty( propID, data, scriptList[i] ) ;

			INX_INC_METRIC(kINXModelTime, INX_DIFF_CLOCK(inxStart));
		}
#ifdef ID_ENABLE_DEBUGGING
		const ScriptReturnDataList& returnDataList = data->GetAllReturnData( scriptList[i] ) ;
		InterfacePtr<IScriptInfoManager> scriptInfoMgr( Utils<IScriptUtils>()->QueryScriptInfoManager( data->GetRequestContext() ) ) ;
		PMString requestDescription( scriptInfoMgr->FindPropertyName( propID ) ) ;
		requestDescription.append( L"' on object '" ) ;
		requestDescription.Append( scriptList[i]->GetObjectInfo( data->GetRequestContext() )->GetName() ) ;
#endif
		if ( err != kSuccess )
		{
#ifdef DEBUG			
            ASSERT_MSG(returnDataList.size() == preReturnDataLen, FORMAT_ARGS("AccessProperty request for property '%s' returned an error AND a value", requestDescription.GetUTF8String().c_str()));
#endif
			data->AppendReturnData( scriptList[i], propID, err ) ;	//push the script provider's error case here
		}
		else //err == kSuccess
		{
			if ( data->IsPropertyGet() )
			{
#ifdef DEBUG
				ASSERT_MSG(returnDataList.size() > preReturnDataLen, FORMAT_ARGS("AccessProperty request to get property '%s' returned kSuccess but no value", requestDescription.GetUTF8String().c_str()));
				ASSERT_MSG(returnDataList.size() < preReturnDataLen + 2, FORMAT_ARGS("AccessProperty request to get property '%s' returned more than one value", requestDescription.GetUTF8String().c_str()));
				if ( returnDataList.size() > preReturnDataLen )
					ASSERT_MSG( returnDataList[preReturnDataLen].GetRequestID() == propID, FORMAT_ARGS( "AccessProperty request to get property '%s' returned value for property '%s'",
					requestDescription.GetUTF8String().c_str(), Utils<IScriptUtils>()->GetScriptID(returnDataList[preReturnDataLen].GetRequestID()).GetUTF8String().c_str()));	//sanity check
#endif
			}
			else
			{
				ASSERT( data->IsPropertyPut() ) ;
#ifdef DEBUG
                ASSERT_MSG(returnDataList.size() == preReturnDataLen, FORMAT_ARGS("AccessProperty request to put property '%s' returned a value", requestDescription.GetUTF8String().c_str()));
#endif
				data->AppendReturnData( scriptList[i], propID, kSuccess ) ;	//push the script provider's success case here
			}
		}

		//Check the error code in the return data because it may have been overridden with a global error code
		ASSERT_MSG( data->GetNumReturnData( scriptList[i] ) == preReturnDataLen + 1, "AccessProperty request has not called AppendReturnData" ) ;
		if ( data->GetNumReturnData( scriptList[i] ) > preReturnDataLen )
		{
			const ScriptReturnData returnData = data->GetNthReturnData( scriptList[i], preReturnDataLen ) ;
			err = returnData.GetErrorCode() ;
			TRACEFLOW( "Script:ScriptRequestHandler", "  %s handled %s property '%s' with return data %s\n",
				GetIDName(::GetClass(this)), data->IsPropertyGet() ? "get" : "set", requestDescription.GetUTF8String().c_str(),
				GetAsString(returnData, data->GetRequestContext()).GetUTF8String().c_str());
		}
		if ( err != kSuccess && data->GetErrorPolicy() == kReturnFirstError )
			break ;
	}
}

//Some subclasses may want to override this method
ErrorCode CScriptProvider::PreAccessProperty( ScriptID propID, IScriptRequestData* data, IScript* script )
{
	return kSuccess ;
}

//Some subclasses may want to override this method
ErrorCode CScriptProvider::PostAccessProperty( ScriptID propID, IScriptRequestData* data, IScript* script )
{
	return kSuccess ;
}

//Most subclasses will override this method
ErrorCode CScriptProvider::AccessProperty( ScriptID propID, IScriptRequestData* data, IScript* script )
{
#ifdef DEBUG
	InterfacePtr<IScriptInfoManager> scriptInfoMgr( Utils<IScriptUtils>()->QueryScriptInfoManager( data->GetRequestContext() ) ) ;
	ASSERT_FAIL(FORMAT_ARGS("%s failed to handle property '%s'", GetIDName(::GetClass(this)), scriptInfoMgr->FindPropertyName(propID).GetUTF8String().c_str()));
#endif
	return kRequestNotHandledError ;
}

//Some subclasses may want to override this method
ErrorCode CScriptProvider::PreAccessProperties( IScriptRequestData* data, IScript* script )
{
	return PreAccessProperty( p_Properties, data, script ) ;
}

//Some subclasses may want to override this method
ErrorCode CScriptProvider::PostAccessProperties( IScriptRequestData* data, IScript* script )
{
	return PostAccessProperty( p_Properties, data, script ) ;
}

//Most subclasses will not need to override this method
void CScriptProvider::AccessProperties( IScriptRequestData* data, IScript* script )
{
	if ( script == nil )
		return data->AppendReturnData( script, data->GetRequestInfo()->GetScriptID(), kInvalidScriptTargetError ) ;

#ifdef DEBUG
	if (Utils<IScriptUtils>()->IsINX(data->GetRequestContext()))
		ASSERT(!script->HasBeenDeleted( data->GetRequestContext() ));
#endif
	if ( !Utils<IScriptUtils>()->IsINX(data->GetRequestContext()) && script->HasBeenDeleted( data->GetRequestContext() ) )
		return data->AppendReturnData( script, data->GetRequestInfo()->GetScriptID(), kObjectDeletedError ) ;

	INX_DECLARE_CLOCK(inxStart, kINXModelTime);
	ErrorCode err = PreAccessProperties( data, script ) ;
	INX_INC_METRIC(kINXModelTime, INX_DIFF_CLOCK(inxStart));
	if ( err != kSuccess )
		return data->AppendReturnData( script, data->GetRequestInfo()->GetScriptID(), err ) ;

	//Access each individual property separately
	const ScriptRecordData props = data->GetRequestData() ;
	for ( ScriptRecordData::const_iterator iter = props.begin() ; iter != props.end() ; ++iter )
	{
		const uint32 preReturnDataLen = data->GetNumReturnData( script ) ;
		const ScriptID& propID = iter->Key() ;
		INX_DECLARE_CLOCK(inxAccessStart, kINXModelTime);
		err = AccessProperty( propID, data, script ) ;
		INX_INC_METRIC(kINXModelTime, INX_DIFF_CLOCK(inxAccessStart));

#ifdef ID_ENABLE_DEBUGGING
		const ScriptReturnDataList& returnDataList = data->GetAllReturnData( script ) ;
		InterfacePtr<IScriptInfoManager> scriptInfoMgr( Utils<IScriptUtils>()->QueryScriptInfoManager( data->GetRequestContext() ) ) ;
		PMString requestDescription( scriptInfoMgr->FindPropertyName( propID ) ) ;
		requestDescription.Append( "' on object '" ) ;
		requestDescription.Append( script->GetObjectInfo( data->GetRequestContext() )->GetName() ) ;
#endif
		if ( err != kSuccess )
		{
#ifdef DEBUG
            ASSERT_MSG(returnDataList.size() == preReturnDataLen, FORMAT_ARGS("AccessProperty request for property '%s' returned an error AND a value", requestDescription.GetUTF8String().c_str()));
#endif
			data->AppendReturnData( script, propID, err ) ;	//push the script provider's error case here
		}
		else //err == kSuccess
		{
			if ( data->IsPropertyGet() )
			{
#ifdef DEBUG
                ASSERT_MSG(returnDataList.size() > preReturnDataLen, FORMAT_ARGS("AccessProperty request to get property '%s' returned kSuccess but no value", requestDescription.GetUTF8String().c_str()));
				ASSERT_MSG(returnDataList.size() < preReturnDataLen + 2, FORMAT_ARGS("AccessProperty request to get property '%s' returned more than one value", requestDescription.GetUTF8String().c_str()));
				if ( returnDataList.size() > preReturnDataLen )
					ASSERT_MSG( returnDataList[preReturnDataLen].GetRequestID() == propID, FORMAT_ARGS( "AccessProperty request to get property '%s' returned value for property '%s'",
					requestDescription.GetUTF8String().c_str(), Utils<IScriptUtils>()->GetScriptID(returnDataList[preReturnDataLen].GetRequestID()).GetUTF8String().c_str()));	//sanity check
#endif
			}
			else
			{
				ASSERT( data->IsPropertyPut() ) ;
#ifdef DEBUG
                ASSERT_MSG(returnDataList.size() == preReturnDataLen, FORMAT_ARGS("AccessProperty request to put property '%s' returned a value", requestDescription.GetUTF8String().c_str()));
#endif
				data->AppendReturnData( script, propID, kSuccess ) ;	//push the script provider's success case here
			}
		}

		//Check the error code in the return data because it may have been overridden with a global error code
		ASSERT_MSG( data->GetNumReturnData( script ) == preReturnDataLen + 1, "AccessProperty request has not called AppendReturnData" ) ;
		if ( data->GetNumReturnData( script ) > preReturnDataLen )
		{
			const ScriptReturnData returnData = data->GetNthReturnData( script, preReturnDataLen ) ;
			err = returnData.GetErrorCode() ;
			TRACEFLOW( "Script:ScriptRequestHandler", "  %s handled %s property '%s' with return data %s\n",
				GetIDName(::GetClass(this)), data->IsPropertyGet() ? "get" : "set", requestDescription.GetUTF8String().c_str(),
				GetAsString(returnData, data->GetRequestContext()).GetUTF8String().c_str());
		}
		if ( err != kSuccess && data->GetErrorPolicy() == kReturnFirstError )
			break ;
		err = kSuccess ;	//Reset to kSuccess in case this is the end of the loop
	}

	if ( err == kSuccess )
	{
		INX_DECLARE_CLOCK(inxStart1, kINXModelTime);
		err = PostAccessProperties( data, script ) ;
		INX_INC_METRIC(kINXModelTime, INX_DIFF_CLOCK(inxStart1));

		if ( err != kSuccess )
			data->AppendReturnData( script, data->GetRequestInfo()->GetScriptID(), err ) ;
	}
}

//Most subclasses will not need to override this method
ErrorCode CScriptProvider::AccessParent( ScriptID propID, IScriptRequestData* data, IScript* script )
{
	if ( data->IsPropertyGet() )
	{
		InterfacePtr<IScript> parentScript ( (IScript*) script->QueryParent( IID_ISCRIPT, data->GetRequestContext() ) ) ;
		ASSERT_MSG( parentScript != nil, "Missing parent script object for this object" ) ;

		if ( parentScript != nil )
		{
			data->AppendReturnData( script, propID, ScriptData( parentScript ) ) ;
			return kSuccess ;
		}

		return kFailure ;
	}

	return Utils<IScriptErrorUtils>()->SetReadOnlyPropertyErrorData( data, propID ) ;
}

//---------------------------------------------------------------------------------------------
// Class RepresentScriptProvider
//---------------------------------------------------------------------------------------------

RepresentScriptProvider::RepresentScriptProvider( IPMUnknown* boss ) :
	Inherited( boss )
{
}

RepresentScriptProvider::~RepresentScriptProvider()
{
}

//Most subclasses will override this method
ErrorCode RepresentScriptProvider::HandleMethod( ScriptID methodID, IScriptRequestData* data, IScript* script )
{
	switch ( methodID.Get() )
	{
		case e_Count :
			return CountObjects( methodID, data, script ) ;
		case e_ExtractLabel :
			return ExtractLabel( methodID, data, script ) ;
		case e_InsertLabel :
			return InsertLabel( methodID, data, script ) ;
		default:
			return Inherited::HandleMethod( methodID, data, script ) ;
	}
}

//Most subclasses will not need to override this method
ErrorCode RepresentScriptProvider::CountObjects( ScriptID methodID, IScriptRequestData* data, IScript* parent )
{
	int32 count = GetNumObjects( data, parent ) ;
	ScriptData scriptData ;
	scriptData.SetInt32( count ) ;
	data->AppendReturnData( parent, methodID, scriptData ) ;
	return kSuccess ;
}
/*
//All subclasses must override this method
int32 RepresentScriptProvider::GetNumObjects( const IScriptRequestData* data, IScript* parent)
{
	ASSERT_UNIMPLEMENTED() ;	//Override in subclass
	return 0 ;
}

//All subclasses must override this method
ErrorCode RepresentScriptProvider::AppendNthObject( const IScriptRequestData* data, IScript* parent, int32 n, ScriptList& objectList )	//0-based index
{
	ASSERT_UNIMPLEMENTED() ;	//Override in subclass
	return kInvalidCollectionItemError ;
}
*/
//Some subclasses may want to override this method for performance reasons
ErrorCode RepresentScriptProvider::AppendAllObjects( const IScriptRequestData* data, IScript* parent, ScriptList& objectList )
{
	int32 count = GetNumObjects( data, parent ) ;

	for ( int32 i = 0 ; i < count ; ++i )
	{
		AppendNthObject( data, parent, i, objectList ) ;
	}

	return kSuccess ;
}

//Most subclasses will not need to override this method
int32 RepresentScriptProvider::GetObjectIndex( const IScriptRequestData* data, IScript* parent, IScript* script )
{
	if ( parent && script )
	{
		int32 count = GetNumObjects( data, parent ) ;
		for ( int32 n = 0 ; n < count ; ++n )
		{
			ScriptList objectList ;
			if ( kSuccess == AppendNthObject( data, parent, n, objectList ) )
			{
				if ( script->IsEqual( objectList[0], data->GetRequestContext() ))
					return n ;
			}
		}
	}

	return -1 ;
}

//Most subclasses will not need to override this method
ErrorCode RepresentScriptProvider::AppendObjectsWhose( const IScriptRequestData* data, IScript* parent, ScriptID propID, const ScriptData& propData, bool16 bFirstMatchOnly, ScriptList& objectList )
{
	Utils<IScriptUtils> scriptUtils ;
	InterfacePtr<IScriptEngine> scriptEngine( data->GetRequestContext().QueryScriptEngine() ) ;
	InterfacePtr<IScriptRequestHandler> scriptRequestHandler( scriptUtils->QueryScriptRequestHandler( data->GetRequestContext() ) ) ;

	ScriptList objectList2 ;
	ErrorCode err = AppendAllObjects( data, parent, objectList2 ) ;
	if ( err == kSuccess )
	{
		for ( int32 n = 0 ; n < objectList2.size() && err == kSuccess ; ++n )
		{
			InterfacePtr<IScriptRequestData> scriptRequestData( scriptEngine->CreateScriptRequestData() ) ;
			err = scriptRequestHandler->DoGetProperty( objectList2[n], propID, scriptRequestData ) ;
			if ( err == kSuccess )
			{
				ASSERT( scriptRequestData->GetNumReturnData( objectList2[n] ) == 1 ) ;
				if ( scriptRequestData->GetNumReturnData( objectList2[n] ) > 0 && 
					 propData.IsEqual( scriptRequestData->GetNthReturnData( objectList2[n], 0 ).GetReturnValue(), data->GetRequestContext() ) )
				{
					objectList.push_back( objectList2[n] ) ;
					if ( bFirstMatchOnly )
						break ;
				}
			}
		}
	}

	return err ;
}

//Most subclasses will not need to override this method
ErrorCode RepresentScriptProvider::GetObjectWhose( IScriptRequestData* data, IScript* parent )
{
	ErrorCode err = kFailure ;
	ScriptList objectList ;
	const ScriptData accessorData = data->GetAccessorData() ;
	bool16 bFirstMatchOnly = kFalse ;

	ScriptRecordData propListData ;
	err = accessorData.GetRecord( propListData ) ;
	if ( err == kSuccess )
	{
		Utils<IScriptUtils> scriptUtils ;
		InterfacePtr<IScriptEngine> scriptEngine( data->GetRequestContext().QueryScriptEngine() ) ;
		InterfacePtr<IScriptRequestHandler> scriptRequestHandler( scriptUtils->QueryScriptRequestHandler( data->GetRequestContext() ) ) ;

		//Start with all the objects
		ScriptList objectList2 ;
		err = AppendAllObjects( data, parent, objectList2 ) ;
		if ( err == kSuccess )
		{
			//Check for each property
			for ( int32 p = 0 ; p < propListData.size() && err == kSuccess ; ++p )
			{
				//Extract the property and value to match
				const ScriptID& propID = propListData[p].Key() ;
				const ScriptData& propData = propListData[p].Value() ;

				//Check on each object
				for ( int32 n = (int32)objectList2.size() - 1 ; n >= 0 && err == kSuccess ; --n )
				{
					InterfacePtr<IScriptRequestData> scriptRequestData( scriptEngine->CreateScriptRequestData() ) ;
					err = scriptRequestHandler->DoGetProperty( objectList2[n], propID, scriptRequestData ) ;
					ASSERT( err != kSuccess || scriptRequestData->GetNumReturnData( objectList2[n] ) == 1 ) ;
					if ( err != kSuccess || scriptRequestData->GetNumReturnData( objectList2[n] ) == 0 || 
						 !propData.IsEqual( scriptRequestData->GetNthReturnData( objectList2[n], 0 ).GetReturnValue(), data->GetRequestContext() ) )
					{
						//Drop this object since it doesn't match
						objectList2.erase( objectList2.begin() + n ) ;
					}
				}
			}

			//Append any remaining objects--they're the ones that matched
			if ( !objectList2.empty() )
			{
				if ( bFirstMatchOnly )
				{
					objectList.push_back( objectList2[0] ) ;
				}
				else
				{
					for ( int32 i = 0 ; i <  objectList2.size() ; ++i )
						objectList.push_back( objectList2[i] ) ;
				}
			}

			data->AppendReturnData( parent, data->GetRequestInfo()->GetScriptID(), ScriptData( objectList ) ) ;
		}
	}

	return err ;
}

ErrorCode RepresentScriptProvider::GetIndex( const IScriptRequestData* data, IScript* parent, const ScriptData& accessorData, int32& index )
{
	if ( accessorData.GetInt32( &index ) == kSuccess )
	{
		const int32 count = GetNumObjects( data, parent ) ;

		if ( index >= 0 )
		{
			//Adjust index for base
			InterfacePtr<IScriptManager> scriptManager( data->GetRequestContext().QueryScriptManager() ) ;
			const int32 base = scriptManager->GetBaseIndex() ;
			ASSERT( base >= 0 ) ;
			if ( index >= base )
				index -= base ;
			else
				return kInvalidCollectionItemError ;
		}
		else	// ( index < 0 )
		{
			//Adjust index to positive
			index += count ;
		}

		if ( index < 0 || index >= count )
			return kInvalidCollectionItemError ;
	}
	return kSuccess ;
}

//Most subclasses will not need to override this method
ErrorCode RepresentScriptProvider::GetObjectByIndex( IScriptRequestData* data, IScript* parent )
{
	ErrorCode err = kSuccess ;
	ScriptList objectList ;
	const ScriptData accessorData = data->GetAccessorData() ;

	switch ( accessorData.GetType() )
	{
		case ScriptData::s_shortint :
		case ScriptData::s_longint :
		{
			int32 n ;
			err = GetIndex( data, parent, accessorData, n ) ;
			if ( err == kSuccess )
			{
				err = AppendNthObject( data, parent, n, objectList ) ;
			}
			break ;
		}
		default :
		{
			ASSERT_FAIL( "Unsupported access data type for GetObjectByIndex" ) ;
			err = kInvalidParameterError ;
			break ;
		}
	}

	if ( err == kSuccess )
		data->AppendReturnData( parent, data->GetRequestInfo()->GetScriptID(), ScriptData( objectList ) ) ;

	return err ;
}

//Most subclasses will not need to override this method
ErrorCode RepresentScriptProvider::GetObjectFirst( IScriptRequestData* data, IScript* parent )
{
	ErrorCode err = kInvalidCollectionItemError ;
	ScriptList objectList ;

#ifdef DEBUG
	const ScriptData accessorData = data->GetAccessorData() ;
	ASSERT( accessorData.GetType() == ScriptData::s_enumeration ) ;
	ScriptID ordinalForm ;
	accessorData.GetEnumeration( &ordinalForm ) ;
	ASSERT( ordinalForm == kFormFirst ) ;
#endif

	int32 count = GetNumObjects( data, parent ) ;
	if ( count > 0 )
	{
		err = AppendNthObject( data, parent, 0, objectList ) ;
	}

	if ( err == kSuccess )
		data->AppendReturnData( parent, data->GetRequestInfo()->GetScriptID(), ScriptData( objectList ) ) ;

	return err ;
}

//Most subclasses will not need to override this method
ErrorCode RepresentScriptProvider::GetObjectLast( IScriptRequestData* data, IScript* parent )
{
	ErrorCode err = kInvalidCollectionItemError ;
	ScriptList objectList ;

#ifdef DEBUG
	const ScriptData accessorData = data->GetAccessorData() ;
	ASSERT( accessorData.GetType() == ScriptData::s_enumeration ) ;
	ScriptID ordinalForm ;
	accessorData.GetEnumeration( &ordinalForm ) ;
	ASSERT( ordinalForm == kFormLast ) ;
#endif

	int32 count = GetNumObjects( data, parent ) ;
	if ( count > 0 )
	{
		err = AppendNthObject( data, parent, count-1, objectList ) ;
	}

	if ( err == kSuccess )
		data->AppendReturnData( parent, data->GetRequestInfo()->GetScriptID(), ScriptData( objectList ) ) ;

	return err ;
}

//Most subclasses will not need to override this method
ErrorCode RepresentScriptProvider::GetObjectMiddle( IScriptRequestData* data, IScript* parent )
{
	ErrorCode err = kInvalidCollectionItemError ;
	ScriptList objectList ;

#ifdef DEBUG
	const ScriptData accessorData = data->GetAccessorData() ;
	ASSERT( accessorData.GetType() == ScriptData::s_enumeration ) ;
	ScriptID ordinalForm ;
	accessorData.GetEnumeration( &ordinalForm ) ;
	ASSERT( ordinalForm == kFormMiddle ) ;
#endif

	int32 count = GetNumObjects( data, parent ) ;
	if ( count > 0 )
	{
		err = AppendNthObject( data, parent, count/2, objectList ) ;
	}

	if ( err == kSuccess )
		data->AppendReturnData( parent, data->GetRequestInfo()->GetScriptID(), ScriptData( objectList ) ) ;

	return err ;
}

//Most subclasses will not need to override this method
ErrorCode RepresentScriptProvider::GetObjectAny( IScriptRequestData* data, IScript* parent )
{
	ErrorCode err = kInvalidCollectionItemError ;
	ScriptList objectList ;

#ifdef DEBUG
	const ScriptData accessorData = data->GetAccessorData() ;
	ASSERT( accessorData.GetType() == ScriptData::s_enumeration ) ;
	ScriptID ordinalForm ;
	accessorData.GetEnumeration( &ordinalForm ) ;
	ASSERT( ordinalForm == kFormAny ) ;
#endif

	int32 count = GetNumObjects( data, parent ) ;
	if ( count > 0 )
	{
		int32 index = count * ((double)rand() / (static_cast<uint32>(RAND_MAX) + 1));
		ASSERT(index>=0 && index < count);
		err = AppendNthObject( data, parent, index, objectList ) ;
	}

	if ( err == kSuccess )
		data->AppendReturnData( parent, data->GetRequestInfo()->GetScriptID(), ScriptData( objectList ) ) ;

	return err ;
}

//Most subclasses will not need to override this method
ErrorCode RepresentScriptProvider::GetObjectAll( IScriptRequestData* data, IScript* parent )
{
	ErrorCode err = kInvalidCollectionItemError ;
	ScriptList objectList ;

#ifdef DEBUG
	const ScriptData accessorData = data->GetAccessorData() ;
	ASSERT( accessorData.GetType() == ScriptData::s_enumeration ) ;
	ScriptID ordinalForm ;
	accessorData.GetEnumeration( &ordinalForm ) ;
	ASSERT( ordinalForm == kFormAll ) ;
#endif

	err = AppendAllObjects( data, parent, objectList ) ;

	if ( err == kSuccess )
		data->AppendReturnData( parent, data->GetRequestInfo()->GetScriptID(), ScriptData( objectList ) ) ;

	return err ;
}

//Most subclasses will not need to override this method
ErrorCode RepresentScriptProvider::GetObjectByName( IScriptRequestData* data, IScript* parent )
{
	ErrorCode err = kSuccess ;
	const ScriptData accessorData = data->GetAccessorData() ;

	if ( accessorData.GetType() == ScriptData::s_string )
	{
		ScriptList objectList ;
		err = AppendObjectsWhose( data, parent, p_Name, accessorData, kTrue, objectList ) ;
		if ( err == kSuccess )
			data->AppendReturnData( parent, data->GetRequestInfo()->GetScriptID(), ScriptData( objectList ) ) ;
	}
	else
	{
		ASSERT_FAIL( "Unsupported access data type for GetObjectByName" ) ;
		err = kInvalidParameterError ;
	}

	return err ;
}

//Most subclasses will not need to override this method
ErrorCode RepresentScriptProvider::GetObjectByID( IScriptRequestData* data, IScript* parent )
{
	ErrorCode err = kSuccess ;
	ScriptList objectList ;
	const ScriptData accessorData = data->GetAccessorData() ;

	switch ( accessorData.GetType() )
	{
		case ScriptData::s_shortint :
		case ScriptData::s_longint :
		{
#if 1
			IDataBase* dB = parent->GetDataBase( data->GetRequestContext() ) ;
			ASSERT(dB) ;

			int32 temp;
			err = accessorData.GetInt32(&temp);
			if ( err == kSuccess )
			{
				UID uid = temp;
				if (dB->GetClass(uid) == kInvalidClass)
				{
					if ( data->GetRequestContext().GetVersion() < kCS4ScriptVersion )
						err = kFailure;
					//else return kSuccess and an empty list #1788913
				}
				else
				{
					InterfacePtr<IScript> object(dB, uid, IID_ISCRIPT);
					if (object)
					{
						objectList.push_back(object);
						err = kSuccess;
					}
				}
			}
#else
			err = AppendObjectsWhose( parent, data->GetDesiredType(), p_ID, accessorData, kTrue, objectList ) ;
#endif
			break ;
		}
		default :
		{
			ASSERT_FAIL( "Unsupported access data type for GetObjectByID" ) ;
			err = kInvalidParameterError ;
			break ;
		}
	}

	if ( err == kSuccess )
		data->AppendReturnData( parent, data->GetRequestInfo()->GetScriptID(), ScriptData( objectList ) ) ;

	return err ;
}

//Most subclasses will not need to override this method
ErrorCode RepresentScriptProvider::GetObjectByRange( IScriptRequestData* data, IScript* parent )
{
	ErrorCode err = kSuccess ;
	ScriptList objectList ;
	int32 nBegin = -1 ;
	int32 nEnd = -1 ;
	const ScriptData accessorData = data->GetAccessorData() ;

	switch ( accessorData.GetType() )
	{
		case ScriptData::s_list :
		{
			ScriptListData dataList ;
			err = accessorData.GetList( dataList ) ;
			if ( err != kSuccess || dataList.size() != 2 )
			{
				err = kReqParamMissing ;
				break ;
			}

			ScriptData fromScriptData = dataList[0] ;
			if ( fromScriptData.GetType() == ScriptData::s_shortint || fromScriptData.GetType() == ScriptData::s_longint )
			{
				err = GetIndex( data, parent, fromScriptData, nBegin ) ;
			}
			else if ( fromScriptData.GetType() == ScriptData::s_string )
			{
				ScriptList whoseList ;
				err = AppendObjectsWhose( data, parent, p_Name, fromScriptData, kTrue, whoseList ) ;
				if ( err != kSuccess ) return err ;
				if ( whoseList.size() != 1 ) return kInvalidParameterError ;
				nBegin = GetObjectIndex( data, parent, whoseList[0] ) ;		//this is inefficient; implement GetIndexOfFirstObjectWhose instead?
			}
			else if ( fromScriptData.GetType() == ScriptData::s_object )
			{
				InterfacePtr<IScript> from( fromScriptData.QueryObject() ) ;
				nBegin = GetObjectIndex( data, parent, from ) ;
			}

			ScriptData toScriptData = dataList[1] ;
			if ( toScriptData.GetType() == ScriptData::s_shortint || toScriptData.GetType() == ScriptData::s_longint )
			{
				err = GetIndex( data, parent, toScriptData, nEnd ) ;
			}
			else if ( toScriptData.GetType() == ScriptData::s_string )
			{
				ScriptList whoseList ;
				err = AppendObjectsWhose( data, parent, p_Name, toScriptData, kTrue, whoseList ) ;
				if ( err != kSuccess ) return err ;
				if ( whoseList.size() != 1 ) return kInvalidParameterError ;
				nEnd = GetObjectIndex( data, parent, whoseList[0] ) ;		//this is inefficient; implement GetIndexOfFirstObjectWhose instead?
			}
			else if ( toScriptData.GetType() == ScriptData::s_object )
			{
				InterfacePtr<IScript> to( toScriptData.QueryObject() ) ;
				nEnd = GetObjectIndex( data, parent, to ) ;
			}
			break ;
		}
		case ScriptData::s_objectlist :
		{
			ScriptList rangeList ;
			err = accessorData.GetObjectList( rangeList ) ;
			if ( err != kSuccess || rangeList.size() != 2 )
			{
				err = kReqParamMissing ;
				break ;
			}

			nBegin = GetObjectIndex( data, parent, rangeList[0] ) ;
			nEnd = GetObjectIndex( data, parent, rangeList[1] ) ;
			break ;
		}
		default :
		{
			ASSERT_FAIL( "Unsupported access data type for GetObject" ) ;
			err = kInvalidParameterError ;
			break ;
		}
	}

	if ( err == kSuccess )
	{
		int32 count = GetNumObjects( data, parent ) ;
		if ( nBegin < 0 || nBegin >= count || nEnd < 0 || nEnd >= count )
		{
			err = kInvalidCollectionItemError ;
		}
	}

	if ( err == kSuccess )
	{
		//Always return objects in forward order
		if ( nEnd < nBegin )
		{
			int32 temp = nEnd ; nEnd = nBegin ; nBegin = temp ;
		}

		for ( int32 n = nBegin ; n <= nEnd && err == kSuccess ; ++n )
		{
			err = AppendNthObject( data, parent, n, objectList ) ;
		}
	}

	if ( err == kSuccess )
		data->AppendReturnData( parent, data->GetRequestInfo()->GetScriptID(), ScriptData( objectList ) ) ;

	return err ;
}

//Most subclasses will not need to override this method
ErrorCode RepresentScriptProvider::GetObjectPrevious( IScriptRequestData* data, IScript* parent )
{
	ErrorCode err = kSuccess ;
	ScriptList objectList ;
	const ScriptData accessorData = data->GetAccessorData() ;

	switch ( accessorData.GetType() )
	{
		case ScriptData::s_object :
		{
			InterfacePtr<IScript> script( accessorData.QueryObject() ) ;
			if ( script == nil )
			{
				err = kReqParamMissing ;
			}
			else
			{
				int32 n = GetObjectIndex( data, parent, script ) ;
				if ( n > 0 )
				{
					err = AppendNthObject( data, parent, n - 1, objectList ) ;
				}
				else
				{
					err = kInvalidParameterError ;
				}
			}
			break ;
		}
		default :
		{
			ASSERT_FAIL( "Unsupported access data type for GetObjectPrevious" ) ;
			err = kInvalidParameterError ;
			break ;
		}
	}

	if ( err == kSuccess )
		data->AppendReturnData( parent, data->GetRequestInfo()->GetScriptID(), ScriptData( objectList ) ) ;

	return err ;
}

//Most subclasses will not need to override this method
ErrorCode RepresentScriptProvider::GetObjectNext( IScriptRequestData* data, IScript* parent )
{
	ErrorCode err = kSuccess ;
	ScriptList objectList ;
	const ScriptData accessorData = data->GetAccessorData() ;

	switch ( accessorData.GetType() )
	{
		case ScriptData::s_object :
		{
			InterfacePtr<IScript> script( accessorData.QueryObject() ) ;
			if ( script == nil )
			{
				err = kReqParamMissing ;
			}
			else
			{
				int32 count = GetNumObjects( data, parent ) ;
				int32 n = GetObjectIndex( data, parent, script ) ;
				if ( n < count - 1 )
				{
					err = AppendNthObject( data, parent, n + 1, objectList ) ;
				}
				else
				{
					err = kInvalidParameterError ;
				}
			}
			break ;
		}
		default :
		{
			ASSERT_FAIL( "Unsupported access data type for GetObjectNext" ) ;
			err = kInvalidParameterError ;
			break ;
		}
	}

	if ( err == kSuccess )
		data->AppendReturnData( parent, data->GetRequestInfo()->GetScriptID(), ScriptData( objectList ) ) ;

	return err ;
}

//Most subclasses will not need to override this method
void RepresentScriptProvider::GetObject( IScriptRequestData* data, IScript* parent )
{
	ErrorCode err = kSuccess ;
	const RequestContext& context = data->GetRequestContext() ;
#ifdef DEBUG
	if (Utils<IScriptUtils>()->IsINX(context))
		ASSERT(!parent->HasBeenDeleted( context));
#endif
	if ( context.GetVersion() >= kCS3ScriptVersion && !Utils<IScriptUtils>()->IsINX(context) && parent->HasBeenDeleted( context ) )
		err = kObjectDeletedError ;

	if ( err == kSuccess )
	{
		switch ( data->GetAccessorForm() )
		{
			case kFormIndex :
				err = GetObjectByIndex( data, parent ) ;
				break ;
			case kFormFirst :
				err = GetObjectFirst( data, parent ) ;
				break ;
			case kFormLast :
				err = GetObjectLast( data, parent ) ;
				break ;
			case kFormMiddle :
				err = GetObjectMiddle( data, parent ) ;
				break ;
			case kFormAny :
				err = GetObjectAny( data, parent ) ;
				break ;
			case kFormAll :
				err = GetObjectAll( data, parent ) ;
				break ;
			case kFormUniqueID :
				err = GetObjectByID( data, parent ) ;
				break ;
			case kFormName :
				err = GetObjectByName( data, parent ) ;
				break ;
			case kFormRange :
				err = GetObjectByRange( data, parent ) ;
				break ;
			case kFormPrevious :
				err = GetObjectPrevious( data, parent ) ;
				break ;
			case kFormNext :
				err = GetObjectNext( data, parent ) ;
				break ;
			case kFormWhose :
				err = GetObjectWhose( data, parent ) ;
				break ;
			case kFormPropertyID :
			default:
				ASSERT_FAIL( "Unsupported access form for GetObject" ) ;
				err = kFailure ;
				break ;
		}
	}

	if ( err != kSuccess )
		data->AppendReturnData( parent, data->GetRequestInfo()->GetScriptID(), err ) ;
}

//Most subclasses will not need to override this method
ErrorCode RepresentScriptProvider::AccessObject( ScriptID propID, IScriptRequestData* data, IScript* script )
{
	if ( data->IsPropertyGet() )
	{
		data->AppendReturnData( script, propID, ScriptData( script ) ) ;
		return kSuccess ;
	}

	return Utils<IScriptErrorUtils>()->SetReadOnlyPropertyErrorData( data, propID ) ;
}

//Most subclasses will not need to override this method
ErrorCode RepresentScriptProvider::AccessID( ScriptID propID, IScriptRequestData* data, IScript* script )
{
	if ( data->IsPropertyGet() )
	{
		ScriptObject scriptObject = script->GetScriptObject( data->GetRequestContext() );
		if (scriptObject.specifierForm != kFormUniqueID)
		{
			ASSERT_FAIL("RepresentScriptProvider::AccessID expects that an object based on kIDBasedObjectScriptElement or "
						"kUIDBasedObjectScriptElement will return a kFormUniqueID scriptObject");
			return kFailure;
		}

		data->AppendReturnData( script, propID, scriptObject.specifierData ) ;
		return kSuccess;
	}

	return Utils<IScriptErrorUtils>()->SetReadOnlyPropertyErrorData( data, propID );
}

//Most subclasses will not need to override this method
ErrorCode RepresentScriptProvider::AccessIndex( ScriptID propID, IScriptRequestData* data, IScript* script )
{
	if ( data->IsPropertyGet() )
	{
		InterfacePtr<IScript> parent( (IScript*) script->QueryParent( IID_ISCRIPT, data->GetRequestContext() ) ) ;
		int32 index = GetObjectIndex( data, parent, script ) ;

		InterfacePtr<IScriptManager> scriptManager( data->GetRequestContext().QueryScriptManager() ) ;
		ASSERT( scriptManager ) ;
		index += scriptManager->GetBaseIndex() ;

		data->AppendReturnData( script, propID, ScriptData( index ) ) ;
		return kSuccess;
	}

	return Utils<IScriptErrorUtils>()->SetReadOnlyPropertyErrorData( data, propID );
}

//Most subclasses will not need to override this method
ErrorCode RepresentScriptProvider::AccessLabel( ScriptID propID, IScriptRequestData* data, IScript* script )
{
	ErrorCode err = kFailure ;
	ScriptData scriptData ;
	Utils<IScriptUtils> scriptUtils ;

	if ( data->IsPropertyGet() )
	{
		if ( scriptUtils->IsINX( data->GetRequestContext() ) && 
			 data->GetRequestContext().GetVersion() >= kCS2ScriptVersion )
		{
			//for INX, return the list of key/value label pairs
			ScriptListData tagList ;
			const IScriptLabel::ScriptLabelKeyValueList labels = script->GetTags() ;
			for ( IScriptLabel::ScriptLabelKeyValueList::const_iterator iter = labels.begin() ;
				  iter != labels.end() ; ++iter )
			{
				ScriptListData tagPair ;
				PMString key( iter->Key() ) ;
				PMString value( iter->Value() ) ;
				tagPair.push_back( ScriptData( key.SetTranslatable( kFalse ) ) ) ;
				tagPair.push_back( ScriptData( value.SetTranslatable( kFalse ) ) ) ;
				tagList.push_back( ScriptData( tagPair ) ) ;
			}
			if ( tagList.size() == 0 && scriptUtils->IsINXExport(data->GetRequestContext()) )
				err = kPropertyNotApplicableError;
			else
			{
				scriptData.SetList( tagList );
				data->AppendReturnData( script, propID, scriptData ) ;
				err = kSuccess;
			}
		}
		else
		{
			//for other clients, return the default label
			scriptData.SetPMString( script->GetTag() ) ;
			data->AppendReturnData( script, propID, scriptData ) ;
			err = kSuccess ;
		}
	}
	else if ( data->IsPropertyPut() )
	{
		err = data->ExtractRequestData( propID, scriptData ) ;
		if ( err == kSuccess )
		{
			if ( scriptUtils->IsINX( data->GetRequestContext() ) && 
				data->GetRequestContext().GetVersion() >= kCS2ScriptVersion )
			{
				//for INX, expect a list of key/value label pairs
				ScriptListData tagList ;
				err = scriptData.GetList( tagList ) ;
				if ( err == kSuccess )
				{
					IScriptLabel::ScriptLabelKeyValueList labels ;
					for ( ScriptListData::const_iterator iter = tagList.begin() ; iter != tagList.end() ; ++iter )
					{
						ScriptListData tagPair ;
						err = iter->GetList( tagPair ) ;
						ASSERT( err == kSuccess && tagPair.size() == 2 ) ;
						if ( err == kSuccess && tagPair.size() == 2 )
						{
							IScriptLabel::ScriptLabelKey key ;
							err = tagPair[0].GetPMString( key ) ;
							ASSERT( err == kSuccess ) ;
							IScriptLabel::ScriptLabelValue value ;
							err = tagPair[1].GetPMString( value ) ;
							ASSERT( err == kSuccess ) ;
							labels.push_back( IScriptLabel::ScriptLabelKeyValuePair( key, value ) ) ;
						}
					}

					if ( labels == script->GetTags() )
						return kSuccess ;

					ScriptList scriptList ;
					scriptList.push_back( InterfacePtr<IScript>( script, UseDefaultIID() ) ) ;
					err = scriptUtils->SetScriptingTags( scriptList, data->GetRequestContext(), labels, kTrue ) ;
					return err;
				}
			}
			//else	//also support the single label case for INX
			{
				//for other clients, expect a single label
				IScriptLabel::ScriptLabelValue tag ;
				err = scriptData.GetPMString( tag ) ;
				if ( err == kSuccess && script->GetTag() != tag )
				{
					ScriptList scriptList ;
					scriptList.push_back( InterfacePtr<IScript>( script, UseDefaultIID() ) ) ;
					return scriptUtils->SetScriptingTag( scriptList, data->GetRequestContext(), tag ) ;
				}
			}
		}
	}

	return err ;
}

//Most subclasses will not need to override this method
ErrorCode RepresentScriptProvider::AccessClass( ScriptID propID, IScriptRequestData* data, IScript* script )
{

	if (data->IsPropertyGet())
	{
		ScriptData scriptData ;
		scriptData.SetInt32( script->GetObjectType( data->GetRequestContext() ).Get() ) ;
		data->AppendReturnData( script, propID, scriptData ) ;
		return kSuccess ;
	}

	return Utils<IScriptErrorUtils>()->SetReadOnlyPropertyErrorData( data, propID ) ;
}

//Most subclasses will not need to override this method
ErrorCode RepresentScriptProvider::AccessPropertiesProperty( ScriptID propID, IScriptRequestData* data, IScript* script )
{
	ErrorCode err = kFailure ;
	InterfacePtr<IScriptRequestHandler> scriptRequestHandler( Utils<IScriptUtils>()->QueryScriptRequestHandler( data->GetRequestContext() ) ) ;

	if ( data->IsPropertyGet() )
	{
		err = scriptRequestHandler->GetProperties( script, data ) ;
		if ( err == kSuccess )
		{
			//Extract the results and bundle into a single record
			const ScriptRecordData srd = IScriptRequestData::ConvertToScriptRecordData( data->GetAllReturnData( script ) ) ;
			data->ClearReturnData( script ) ;
			data->AppendReturnData( script, propID, ScriptData( srd ) ) ;
		}
		else
		{
			//Replace the results with a single error	//##jwb what about the error string?
			data->ClearReturnData( script ) ;
		}
	}
	else if ( data->IsPropertyPut() )
	{
		err = scriptRequestHandler->SetProperties( script, data ) ;

		//Replace the results with a single error	//##jwb what about the error string?
		data->ClearReturnData( script ) ;
	}

	return err ;
}

//Most subclasses will override this method
ErrorCode RepresentScriptProvider::AccessProperty( ScriptID propID, IScriptRequestData* data, IScript* script )
{
	switch ( propID.Get() )
	{
		case p_ID:
			return AccessID( propID, data, script ) ;
		case p_Index:
			return AccessIndex( propID, data, script ) ;
		case p_ScriptLabel:
			return AccessLabel( propID, data, script ) ;
		case p_Class:
			return AccessClass( propID, data, script ) ;
		case p_Properties:
			return AccessPropertiesProperty( propID, data, script ) ;
		case p_ObjectSpecifier:
			return AccessObject( propID, data, script ) ;
		case p_Parent:
			return AccessParent( propID, data, script ) ;

		default:
			return Inherited::AccessProperty( propID, data, script ) ;
	}
}

//Most subclasses will not need to override this method
ErrorCode RepresentScriptProvider::ExtractLabel( ScriptID methodID, IScriptRequestData* data, IScript* script )
{
	ScriptData scriptData;
	ErrorCode err = data->ExtractRequestData(keyASPrepositionWith, scriptData);

	PMString	key;
	err = scriptData.GetPMString(key);

	scriptData.SetPMString(script->GetTag(key));
	data->AppendReturnData( script, methodID, scriptData ) ;
	return kSuccess ;
}

//Most subclasses will not need to override this method
ErrorCode RepresentScriptProvider::InsertLabel( ScriptID methodID, IScriptRequestData* data, IScript* script)
{
	ScriptData scriptData;
	PMString key, value;

	ErrorCode err = data->ExtractRequestData(keyASPrepositionWith, scriptData);
	if (err != kSuccess) return err;

	err = scriptData.GetPMString(key);
	if (err != kSuccess) return err;

	err = data->ExtractRequestData(keyASPrepositionTo, scriptData);
	if (err != kSuccess) return err;

	err = scriptData.GetPMString(value);
	if (err != kSuccess) return err;

	ScriptList scriptList ;
	scriptList.push_back( InterfacePtr<IScript>( script, UseDefaultIID() ) ) ;
	return Utils<IScriptUtils>()->SetScriptingTag( scriptList, data->GetRequestContext(), value, key ) ;
}
