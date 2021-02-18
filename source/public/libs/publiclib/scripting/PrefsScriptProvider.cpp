//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/scripting/PrefsScriptProvider.cpp $
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
#include "PrefsScriptProvider.h"

#include "IDocument.h"

#include "PreferenceUtils.h"

//---------------------------------------------------------------------------------------
//	SingletonScriptProvider
//---------------------------------------------------------------------------------------

SingletonScriptProvider::SingletonScriptProvider(IPMUnknown *boss):
	Inherited(boss),
	fSingletonIDs()
{
}

void SingletonScriptProvider::DefineSingleton( const ScriptID& objectID, const ScriptID& propID, const ClassID& bossID )
{
	InsertKeyValue( fSingletonIDs, propID, SingletonData( objectID, bossID ) ) ;
}

int32 SingletonScriptProvider::GetNumObjects( const IScriptRequestData* data, IScript* parent )
{
	//Locate the correct propID based on the desired objectType
	ScriptID propID = kInvalidScriptID ;
	for ( int32 i = 0 ; i < fSingletonIDs.size() ; ++i )
	{
		if ( fSingletonIDs[i].Value().fObjectID == data->GetDesiredType() )
		{
			propID = fSingletonIDs[i].Key() ;
			break ;
		}
	}

	if ( propID != kInvalidScriptID )
		return 1 ;
	else
		return 0 ;
}

ErrorCode SingletonScriptProvider::AppendNthObject( const IScriptRequestData* data, IScript* parent, int32 n, ScriptList& objectList )	//0-based index
{
	ErrorCode err = kInvalidCollectionItemError ;

	if ( n == 0 )
	{
		//Locate the correct propID based on the desired objectType
		ScriptID propID = kInvalidScriptID ;
		for ( int32 i = 0 ; i < fSingletonIDs.size() ; ++i )
		{
			if ( fSingletonIDs[i].Value().fObjectID == data->GetDesiredType() )
			{
				propID = fSingletonIDs[i].Key() ;
				break ;
			}
		}

		if ( propID != kInvalidScriptID )
		{
			InterfacePtr<IScript> script( QuerySingleton( data, parent, propID ) ) ;
			ASSERT( script ) ;
			if ( script )
				objectList.push_back( script ) ;
			err = kSuccess ;
		}
	}

	return err ;
}

void SingletonScriptProvider::GetObject( IScriptRequestData* data, IScript* parent )
{
	if ( data->GetAccessorForm() == kFormPropertyID )
	{
		ScriptID propID;
		ErrorCode err = data->GetAccessorData().GetEnumeration(&propID);
		if ( err == kSuccess )
		{
			if ( CanAccessSingleton( propID, parent ) )
			{
				InterfacePtr<IScript> singletonScript( QuerySingleton( data, parent, propID ) ) ;
				if ( singletonScript )
					data->AppendReturnData( parent, data->GetRequestInfo()->GetScriptID(), ScriptData( singletonScript ) ) ;
			}
			else
			{
				ASSERT_FAIL("Trying to get a singleton scripting object using the wrong property ID!");
			}
		}
		else
		{
			data->AppendReturnData( parent, data->GetRequestInfo()->GetScriptID(), err ) ;
		}
	}
	else
	{
		Inherited::GetObject( data, parent ) ;
	}
}

ErrorCode SingletonScriptProvider::AccessProperty( ScriptID propID, IScriptRequestData* data, IScript* script )
{
	//Trap pref case
	if ( CanAccessSingleton( propID, script ) )
		return AccessSingleton( propID, data, script ) ;

	return Inherited::AccessProperty( propID, data, script ) ;
}

bool16 SingletonScriptProvider::CanAccessSingleton( ScriptID propID, IScript* parent ) const
{
	if ( FindLocation( fSingletonIDs, propID ) >= 0 )
		return kTrue ;
	else
		return kFalse ;
}

ErrorCode SingletonScriptProvider::AccessSingleton( ScriptID propID, IScriptRequestData* data, IScript* parent )
{
	if ( data->IsPropertyGet() )
	{
		InterfacePtr<IScript> singletonScript( QuerySingleton( data, parent, propID ) ) ;
		if ( singletonScript != nil )
		{
			data->AppendReturnData( parent, propID, ScriptData( singletonScript ) ) ;
			return kSuccess ;
		}
	}
	else if ( data->IsPropertyPut() )
	{
		ASSERT_UNIMPLEMENTED() ;
	}

	return kFailure ;
}

IScript* SingletonScriptProvider::QuerySingleton( const IScriptRequestData* data, IScript* parent, const ScriptID& propID )
{
	IScript* singletonScript = nil ;

	if ( parent != nil )
	{
		int32 loc = FindLocation( fSingletonIDs, propID ) ;
		if ( loc >= 0 )
		{
			const SingletonData& singletonData = fSingletonIDs[loc].Value() ;
			singletonScript = Utils<IScriptUtils>()->CreateProxyScriptObject( data->GetRequestContext(), singletonData.fBossID, singletonData.fObjectID, parent, propID.Get() ) ;
		}
	}

	return singletonScript ;
}

//---------------------------------------------------------------------------------------
//	PrefsScriptProvider
//---------------------------------------------------------------------------------------

void PrefsScriptProvider::DefinePreference( const ScriptID& objectID, const ScriptID& propID, const ClassID& bossID /*= kBasePrefsScriptObjectBoss*/ )
{
	Inherited::DefineSingleton( objectID, propID, bossID ) ;
}

int32 PrefsScriptProvider::GetNumObjects( const IScriptRequestData* data, IScript* parent )
{
	if ( data->GetDesiredType() == c_PrefsObject )
	{
		ASSERT( data->GetRequestContext().GetVersion() >= kCS4ScriptVersion ) ;
		int32 count = 0 ;
		const ObjectScriptElement* pParentSI = parent->GetObjectInfo( data->GetRequestContext() ) ;
		ASSERT( pParentSI ) ;
		if ( pParentSI )
		{
			for ( ChildProviderIterator iter = pParentSI->Children() ; iter != iter.end() ; ++iter )
			{
				const ObjectScriptElement* pChildSI = iter->Element() ;
				if ( pChildSI->IsPreferencesObject() && pChildSI->IsSingletonChild() )
					++count ;
			}
		}
		return count ;
	}

	return Inherited::GetNumObjects( data, parent ) ;
}

ErrorCode PrefsScriptProvider::AppendNthObject( const IScriptRequestData* data, IScript* parent, int32 n, ScriptList& objectList )	//0-based index
{
	if ( data->GetDesiredType() == c_PrefsObject )
	{
		ASSERT( data->GetRequestContext().GetVersion() >= kCS4ScriptVersion ) ;
		const ObjectScriptElement* pParentSI = parent->GetObjectInfo( data->GetRequestContext() ) ;
		ASSERT( pParentSI ) ;
		if ( pParentSI )
		{
			for ( ChildProviderIterator iter = pParentSI->Children() ; iter != iter.end() && n >= 0 ; ++iter )
			{
				const ObjectScriptElement* pChildSI = iter->Element() ;
				if ( pChildSI->IsPreferencesObject() && pChildSI->IsSingletonChild() )
				{
					//Find the script provider that represents this object on its parent and call GetObject on that script provider
					InterfacePtr<IScriptProvider> scriptProvider( iter->QueryScriptProvider() ) ;
					ASSERT( scriptProvider ) ;
					if ( scriptProvider )
					{
						InterfacePtr<IScriptManager> scriptMgr( data->GetRequestContext().QueryScriptManager() ) ;
						InterfacePtr<IScriptEngine> scriptEngine( data->GetRequestContext().QueryScriptEngine() ) ;
						InterfacePtr<IScriptRequestData> scriptRequestData( scriptEngine->CreateScriptRequestData() ) ;
						scriptRequestData->SetTargetInfo( pParentSI ) ;
						scriptRequestData->SetGetObject( pChildSI, kFormIndex, ScriptData( scriptMgr->GetBaseIndex() ) ) ;
						scriptProvider->GetObject( scriptRequestData, parent ) ;
						ASSERT( scriptRequestData->GetNumReturnData( parent ) == 1 ) ;
						if ( scriptRequestData->GetNumReturnData( parent ) > 0 )
						{
							if ( n == 0 )
							{
								ScriptList returnList ;
								scriptRequestData->GetNthReturnData( parent, 0 ).GetReturnValue().GetObjectList( returnList ) ;
								ASSERT( returnList.size() == 1 ) ;
								objectList.insert( objectList.end(), returnList.begin(), returnList.end() ) ;
								return kSuccess ;
							}
							else
							{
#ifdef DEBUG
								ScriptList returnList ;
								scriptRequestData->GetNthReturnData( parent, 0 ).GetReturnValue().GetObjectList( returnList ) ;
								ASSERT( returnList.size() == 1 ) ;
#endif
								--n ;
							}
						}
					}
				}
			}
		}
		return kInvalidCollectionItemError ;
	}

	return Inherited::AppendNthObject( data, parent, n, objectList ) ;
}

ErrorCode PrefsScriptProvider::AppendAllObjects( const IScriptRequestData* data, IScript* parent, ScriptList& objectList )
{
	if ( data->GetDesiredType() == c_PrefsObject )
	{
		ASSERT( data->GetRequestContext().GetVersion() >= kCS4ScriptVersion ) ;
		const ObjectScriptElement* pParentSI = parent->GetObjectInfo( data->GetRequestContext() ) ;
		ASSERT( pParentSI ) ;
		if ( pParentSI )
		{
			for ( ChildProviderIterator iter = pParentSI->Children() ; iter != iter.end() ; ++iter )
			{
				const ObjectScriptElement* pChildSI = iter->Element() ;
				if ( pChildSI->IsPreferencesObject() && pChildSI->IsSingletonChild() )
				{
					//Find the script provider that represents this object on its parent and call GetObject on that script provider
					InterfacePtr<IScriptProvider> scriptProvider( iter->QueryScriptProvider() ) ;
					ASSERT( scriptProvider ) ;
					if ( scriptProvider )
					{
						InterfacePtr<IScriptManager> scriptMgr( data->GetRequestContext().QueryScriptManager() ) ;
						InterfacePtr<IScriptEngine> scriptEngine( data->GetRequestContext().QueryScriptEngine() ) ;
						InterfacePtr<IScriptRequestData> scriptRequestData( scriptEngine->CreateScriptRequestData() ) ;
						scriptRequestData->SetTargetInfo( pParentSI ) ;
						scriptRequestData->SetGetObject( pChildSI, kFormIndex, ScriptData( scriptMgr->GetBaseIndex() ) ) ;
						scriptProvider->GetObject( scriptRequestData, parent ) ;
						ASSERT( scriptRequestData->GetNumReturnData( parent ) == 1 ) ;
						if ( scriptRequestData->GetNumReturnData( parent ) > 0 )
						{
							ScriptList returnList ;
							scriptRequestData->GetNthReturnData( parent, 0 ).GetReturnValue().GetObjectList( returnList ) ;
							ASSERT( returnList.size() == 1 ) ;
							objectList.insert( objectList.end(), returnList.begin(), returnList.end() ) ;
						}
					}
				}
			}
		}
		return kSuccess ;
	}

	return Inherited::AppendAllObjects( data, parent, objectList ) ;
}

ErrorCode PrefsScriptProvider::AccessProperty( ScriptID propID, IScriptRequestData* data, IScript* script )
{
	//Trap pref case (#1574644)
	if ( CanAccessPreference( propID, script ) )
		return AccessPreference( propID, data, script ) ;

	return Inherited::AccessProperty( propID, data, script ) ;
}

bool16 PrefsScriptProvider::CanAccessPreference( ScriptID propID, IScript* parent ) const
{
	return Inherited::CanAccessSingleton( propID, parent ) ;
}

ErrorCode PrefsScriptProvider::AccessPreference( ScriptID propID, IScriptRequestData* data, IScript* parent )
{
	return Inherited::AccessSingleton( propID, data, parent ) ;
}

IScript* PrefsScriptProvider::QueryPrefScript( const IScriptRequestData* data, IScript* parent, const ScriptID& propID )
{
	return Inherited::QuerySingleton( data, parent, propID ) ;
}

/*static*/ IPMUnknown* PrefsScriptProvider::QueryPreferences( const IScriptRequestData* data, const IScript* prefsScript, const PMIID& prefInterfaceID )
{
	InterfacePtr<IDocument> document ( Utils<IScriptUtils>()->QueryDocumentFromScript( prefsScript, data->GetRequestContext() ) ) ;
	if (document)
		return  ::QueryPreferences( prefInterfaceID, document ) ;
	else
		return  ::QuerySessionPreferences( prefInterfaceID ) ;
}
