//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/ScriptIDEnumMap.h $
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
//  
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __ScriptIDEnumMap__
#define __ScriptIDEnumMap__

#include "IScriptErrorUtils.h"
#include "IScriptRequestData.h"

/** ScriptIDMap class
*/
template<class T>
class ScriptIDMap
{
public:
	/** Entry structure
	*/
	struct Entry
	{
		/** T */
		T t;
		/** ScriptID */
		ScriptID id;
	} ;

	/**	Construct a new ScriptIDMap
		@param firstEntry
		@param tableSize
	*/
	ScriptIDMap( const Entry* firstEntry, size_t tableSize )
	{
		fMappingTable = firstEntry ;
		fNumEntries = (int32)(tableSize / sizeof( Entry )) ;
	}

	/** TranslateFromScriptID
		@param t
		@param id
		@return bool16
	*/
	bool16 TranslateFromScriptID( T& t, const ScriptID& script_id ) const
	{
		for ( int32 i = 0 ; i < fNumEntries ; ++i )
		{
			if ( fMappingTable[i].id == script_id )
			{
				t = fMappingTable[i].t ;
				return kTrue ;
			}
		}
		return kFalse ;
	}

	/** TranslateToScriptID
		@param id
		@param t
		@return bool16
	*/
	bool16 TranslateToScriptID( ScriptID& script_id, const T& t ) const
	{
		for ( int32 i = 0 ; i < fNumEntries ; ++i )
		{
			if ( fMappingTable[i].t == t )
			{
				script_id = fMappingTable[i].id ;
				return kTrue ;
			}
		}
		return kFalse ;
	}

	/** GetForGetProperty
		@param script
		@param data
		@param propID
		@param t
		@return kSuccess if successful or returns an error code.
	*/
	ErrorCode GetForGetProperty( const IScript* script, IScriptRequestData* data, const ScriptID& propID, const T& t ) const
	{
		ScriptID script_id ;
		if ( !TranslateToScriptID( script_id, t ) )
		{
			ASSERT_FAIL( "ScriptIDMap::TranslateToScriptID failed to find a scripting enum to match the current value of a property" ) ;
			return kFailure ;
		}

		ScriptData scriptData ;
		scriptData.SetEnumeration( script_id ) ;
		data->AppendReturnData( script, propID, scriptData ) ;
		return kSuccess ;
	}

	/** GetForSetProperty
		@param script
		@param data
		@param propID
		@param t
		@return kSuccess if successful or returns an error code.
	*/
	ErrorCode GetForSetProperty( const IScript* script, IScriptRequestData* data, const ScriptID& propID, T& t ) const
	{
		ScriptData scriptData ;
		ErrorCode err = data->ExtractRequestData( propID, scriptData ) ;
		if ( err != kSuccess ) return err ;

		ScriptID script_id ;
		err = scriptData.GetEnumeration( &script_id ) ;
		if ( err != kSuccess ) return Utils<IScriptErrorUtils>()->SetInvalidParameterErrorData( data, propID ) ;

		if ( !TranslateFromScriptID( t, script_id ) )
			return Utils<IScriptErrorUtils>()->SetInvalidParameterErrorData( data, propID ) ;

		return kSuccess ;
	}

protected:
	const Entry*	fMappingTable ;
	int32			fNumEntries ;
} ;

//Here int32 represents any enum value
typedef ScriptIDMap<int32> ScriptIDEnumMap ;
typedef ScriptIDMap<int32>::Entry ScriptIDEnumMapEntry ;

#endif	//__ScriptIDEnumMap__
