//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/scripting/CScriptManager.cpp $
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
#include "CScriptManager.h"

#include "IScriptEngine.h"
#include "IScriptInfoManager.h"
#include "IScriptUtils.h"

#ifdef DEBUG
static IDThreading::ThreadLocalManagedObject<K2Vector<ClassID> > tl_ScriptMgrs ;
#endif

CScriptManager::CScriptManager( IPMUnknown* boss ) :
	Inherited( boss ),
	fErrorPolicies(),
	fSetPropertiesOrderPolicy( kDefaultOrder )
{
	SetDefaultErrorPolicy( kReturnFirstError ) ;	//Return the first error, or kSuccess if none

#ifdef DEBUG
	//Script managers are typically singletons, created by aggregating IID_IK2SERVICEPROVIDER (as 
	//implemented by kScriptManagerServiceImpl) via boss subclassing of kCoreScriptManagerBoss,
	//and accessed by calling IScriptUtils::QueryScriptManager.
	const ClassID myClass = ::GetClass( this ) ;
	ASSERT_MSG( tl_ScriptMgrs.Get()->end() == std::find( tl_ScriptMgrs.Get()->begin(), tl_ScriptMgrs.Get()->end(), myClass ), 
				FORMAT_ARGS( "A script mgr with class ID 0x%x already exists", myClass.Get() ) ) ;
	tl_ScriptMgrs.Get()->push_back( myClass ) ;
#endif
}

CScriptManager::~CScriptManager()
{
#ifdef DEBUG
	ClassID* iter = std::find( tl_ScriptMgrs.Get()->begin(), tl_ScriptMgrs.Get()->end(), ::GetClass( this ) ) ;
	ASSERT( iter != tl_ScriptMgrs.Get()->end() ) ;
	if ( iter != tl_ScriptMgrs.Get()->end() )
		tl_ScriptMgrs.Get()->erase( iter ) ;
#endif
}

ErrorCode CScriptManager::Install()
{
	return kSuccess ;
}

ErrorCode CScriptManager::UnInstall()
{
	return kSuccess ;
}

bool16 CScriptManager::IsScriptActive() const
{
	const uint32 num = GetNumEngines() ;
	for ( uint32 i = 0 ; i < num ; ++i )
	{
		InterfacePtr<IScriptEngine> scriptEngine( QueryNthEngine( i ) ) ;
		if ( scriptEngine && scriptEngine->IsScriptActive() )
			return kTrue ;
	}
	return kFalse ;
}

uint32 CScriptManager::GetNumEngines() const
{
	//There must be at least one and, for the single engine client, there's only one
	return 1 ;
}

IScriptEngine* CScriptManager::QueryNthEngine( uint32 n ) const
{
	//For the single engine client, return the single default engine
	ASSERT( n < GetNumEngines() ) ;
	return QueryDefaultEngine() ;
}

IScriptEngine* CScriptManager::QueryDefaultEngine() const
{
	//For the single engine client, it's simplest to aggregate its IScriptEngine to the IScriptManager boss
	InterfacePtr<IScriptEngine> scriptEngine( this, UseDefaultIID() ) ;
	ASSERT( scriptEngine ) ;
	return scriptEngine.forget() ;
}

ErrorPolicy CScriptManager::GetErrorPolicy( ScriptID requestID /*= kInvalidScriptID*/ ) const
{
	int32 loc = FindLocation( fErrorPolicies, requestID ) ;
	if ( loc < 0 )
		loc = FindLocation( fErrorPolicies, kInvalidScriptID ) ;
	return fErrorPolicies[ loc ].Value() ;
}

void CScriptManager::SetDefaultErrorPolicy( ErrorPolicy policy )
{
	SetSpecificErrorPolicy( kInvalidScriptID, policy ) ;
}

void CScriptManager::SetSpecificErrorPolicy( ScriptID requestID, ErrorPolicy policy )
{
	InsertOrReplaceKeyValue( fErrorPolicies, requestID, policy ) ;
}

void CScriptManager::SetSetPropertiesOrderPolicy( SetPropertiesOrderPolicy policy )
{
	fSetPropertiesOrderPolicy = policy ;
}

SetPropertiesOrderPolicy CScriptManager::GetSetPropertiesOrderPolicy() const
{
	return fSetPropertiesOrderPolicy ;
}

FormatNamePolicy CScriptManager::GetFormatNamePolicy( ScriptElementType element, const RequestContext& context ) const
{
	//For all element types, return the default name (i.e., as it appears in the resource)
	return FormatNamePolicy() ;
}

//Most client-specific implementations subclassing CScriptManager will NOT need to override this method
PMString CScriptManager::GetTypeAsString( const TypeInfo& ti, const ObjectScriptElement* pObjSI, int32 includeInfo ) const
{
	PMString typeString ;
	ASSERT( pObjSI ) ;
	if ( pObjSI )
	{
		ASSERT( pObjSI->GetRequestContext().GetClient() == ::GetClass( this ) ) ;
		AppendTypeAsString( pObjSI, pObjSI->GetRequestContext(), ti, includeInfo, typeString ) ;
	}
	return typeString.SetTranslatable( kFalse ) ;
}

//Most client-specific implementations subclassing CScriptManager will NOT need to override this method
PMString CScriptManager::GetTypeAsString( const TypeInfo& ti, const RequestContext& context, int32 includeInfo ) const
{
	ASSERT( context.GetClient() == ::GetClass( this ) ) ;
	PMString typeString ;
	AppendTypeAsString( nil, context, ti, includeInfo, typeString ) ;
	return typeString.SetTranslatable( kFalse ) ;
}

//Most client-specific implementations subclassing CScriptManager will NOT need to override this method
void CScriptManager::AppendTypeAsString( const ObjectScriptElement* pObjSI, const RequestContext& context, const TypeInfo& ti, int32 includeInfo, PMString& typeString ) const
{
	ASSERT( pObjSI == nil || pObjSI->GetRequestContext() == context ) ;
	if ( ti.IsVariableType() || ti.IsStructType() )
	{
		if ( includeInfo & kFormatAsPlural )
			includeInfo -= kFormatAsPlural ;
		if ( AppendArrayString( context, ti, includeInfo, typeString ) )
			includeInfo |= kFormatAsPlural ;
		if ( AppendStructString( context, ti, includeInfo, typeString ) && ( includeInfo & kFormatAsPlural ))
			includeInfo -= kFormatAsPlural ;

		const TypeInfoList& types = ti.IsVariableType() ? ti.GetVariableTypes() : ti.GetStructFields() ;
		const int32 length = types.size() ;
		for ( int32 i = 0 ; i < length ; ++i )
		{
			if ( ti.IsVariableType() )
			{
				AppendTypeAsString( pObjSI, context, types[i], includeInfo, typeString ) ;
				if ( i + 2 == length )
					typeString.append( L" or " ) ;
				else if ( i + 3 <= length )
					typeString.append( L", " ) ;
			}
			else
			{
				ASSERT( ti.IsStructType() ) ;
				typeString.Append( types[i].GetFormattedStructFieldName( context ) ) ;
				typeString.AppendW( L':' ) ;
				AppendTypeAsString( pObjSI, context, types[i], includeInfo, typeString ) ;
				if ( i + 1 < length )
					typeString.append( L", " ) ;
			}
		}
	}
	else
	{
		if ( AppendArrayString( context, ti, includeInfo, typeString ) )
			includeInfo |= kFormatAsPlural ;

		if ( kFalse == AppendBaseTypeAsString( context, ti, includeInfo, typeString ) )
		{
			if ( kFalse == AppendObjectTypeAsString( context, ti, includeInfo, typeString ) )
			{
				if ( kFalse == AppendEnumTypeAsString( context, ti, includeInfo, typeString ) )
				{
					if ( kFalse == AppendTypeDefAsString( pObjSI, context, ti, includeInfo, typeString ) )
					{
						ASSERT_FAIL( "CScriptManager::AppendTypeAsString - Unrecognized type" ) ;
					}
				}
			}
		}
	}

	AppendRangeDataAsString( context, ti, includeInfo, typeString ) ;
	AppendDefaultValueAsString( context, ti, includeInfo, typeString ) ;
}

//Most client-specific implementations subclassing CScriptManager WILL want to override this method
bool16 CScriptManager::AppendBaseTypeAsString( const RequestContext& context, const TypeInfo& ti, int32 includeInfo, PMString& typeString ) const
{
	switch ( ti.GetType().Get() )
	{
		case kScriptInfoVoidType :		typeString.append( L"Empty" ) ; break ;
		case kScriptInfoAnyType :		typeString.append( L"Any Type" ) ; break ;
		case kScriptInfoInt16Type :		context.GetVersion() < kCS3ScriptVersion ?
											typeString.append( L"Short" ) : typeString.append( L"Short Integer" ) ; break ;
		case kScriptInfoInt32Type :		context.GetVersion() < kCS3ScriptVersion ?
											typeString.append( L"Long" ) : typeString.append( L"Long Integer" ) ; break ;
		case kScriptInfoInt64Type :		context.GetVersion() < kCS3ScriptVersion ?
											typeString.append( L"LongLong" ) : typeString.append( L"Long Long Integer" ) ; break ;
		case kScriptInfoBoolType :		typeString.append( L"Boolean" ) ; break ;
		case kScriptInfoStringType :	typeString.append( L"String" ) ; break ;
		case kScriptInfoUnitType :		typeString.append( L"Unit" ) ; break ;
		case kScriptInfoRealType :		typeString.append( L"Real" ) ; break ;
		case kScriptInfoDateType :		typeString.append( L"Date" ) ; break ;
		case kScriptInfoFileType :		typeString.append( L"File" ) ; break ;
		case kScriptInfoRecordType :	typeString.append( L"ID/Value Pair" ) ; break ;
		case kScriptInfoStreamType :	typeString.append( L"Stream" ) ; break ;
		case kScriptInfoFunctionType :	typeString.append( L"JavaScript Function" ) ; break ;	//#1442481
		case kScriptInfoVariableType :	ASSERT_FAIL( "Unexpected variable type in AppendBaseTypeAsString" ) ; return kFalse ;
		case kScriptInfoStructType :	ASSERT_FAIL( "Unexpected struct type in AppendBaseTypeAsString" ) ; return kFalse ;
		default:
			return kFalse ;	//not a base type
	}

	if ( includeInfo & kFormatAsPlural )
		typeString.AppendW( L's' ) ;

	return kTrue ;	//handled base type
}

//Some client-specific implementations subclassing CScriptManager may want to override this method
bool16 CScriptManager::AppendRangeDataAsString( const RequestContext& context, const TypeInfo& ti, int32 includeInfo, PMString& typeString ) const
{
	if (( includeInfo & kIncludeRangeData ) && ti.HasRangeData() )
	{
		PMReal min, max ;
		bool16 hasMin = ( kSuccess == ti.GetMinimum().GetPMReal( &min ) ) ;
		bool16 hasMax = ( kSuccess == ti.GetMaximum().GetPMReal( &max ) ) ;
		typeString.append( L" (" ) ;
		if ( hasMin && hasMax )
		{
			typeString.AppendNumber( min, -1, kFalse, kTrue ) ;
			typeString.append( L" - " ) ;
			typeString.AppendNumber( max, -1, kFalse, kTrue ) ;
		}
		else if ( hasMin )
		{
			typeString.append( L">= " ) ;
			typeString.AppendNumber( min, -1, kFalse, kTrue ) ;
		}
		else if ( hasMax )
		{
			typeString.append( L"<= " ) ;
			typeString.AppendNumber( max, -1, kFalse, kTrue ) ;
		}
		else
		{
			ASSERT_FAIL( "ti.HasRangeData() returned kTrue but no valid range data was found" ) ;
		}

		if ( ti.GetType() == kScriptInfoUnitType )
			typeString.append( L" points" ) ;

		typeString.AppendW( L')' ) ;
		return kTrue ;	//handled range data
	}

	return kFalse ;	//no range data
}

//Some client-specific implementations subclassing CScriptManager may want to override this method
bool16 CScriptManager::AppendDefaultValueAsString( const RequestContext& context, const TypeInfo& ti, int32 includeInfo, PMString& typeString ) const
{
	if (( includeInfo & kIncludeDefaultValue ) && ti.HasDefault() )
	{
		ScriptData defaultValue = ti.GetDefault() ;
		if ( context.GetVersion() >= kCS4ScriptVersion && defaultValue.GetType() == ScriptData::s_string &&
			 !( includeInfo & kDontTranslateKeyStringDefaultType ) )	//#2337786
		{
			PMString temp ;
			defaultValue.GetPMString( temp ) ;
			temp.Translate() ;
			defaultValue.SetPMString( temp ) ;
		}
		typeString.append( L" (Default: " ) ;
		typeString.Append( defaultValue.GetValueAsString( context ) ) ;

		if ( ti.GetType() == kScriptInfoUnitType )
			typeString.append( L" points" ) ;

		typeString.AppendW( L')' ) ;
		return kTrue ;	//handled default value
	}

	return kFalse ;	//no default value
}

//Some client-specific implementations subclassing CScriptManager may want to override this method
bool16 CScriptManager::AppendObjectTypeAsString( const RequestContext& context, const TypeInfo& ti, int32 includeInfo, PMString& typeString ) const
{
	InterfacePtr<IScriptInfoManager> scriptInfoMgr( Utils<IScriptUtils>()->QueryScriptInfoManager( context ) ) ;
	ASSERT( scriptInfoMgr ) ;
	if ( scriptInfoMgr ) 
	{
		if ( const ObjectScriptElement* pObjSI = scriptInfoMgr->FindObject( ti.GetType() ) )
		{
			if ( includeInfo & kFormatAsPlural )
				typeString.Append( pObjSI->GetCollectionInfo()->GetFormattedName( GetFormatNamePolicy( kObjectElement, context ) ) ) ;
			else
				typeString.Append( ((const BaseScriptInfo*) pObjSI)->GetFormattedName( GetFormatNamePolicy( kObjectElement, context ) ) ) ;
			return kTrue ;	//handled object type
		}
	}
	return kFalse ;	//not an object type
}

//Some client-specific implementations subclassing CScriptManager may want to override this method
bool16 CScriptManager::AppendEnumTypeAsString( const RequestContext& context, const TypeInfo& ti, int32 includeInfo, PMString& typeString ) const
{
	InterfacePtr<IScriptInfoManager> scriptInfoMgr( Utils<IScriptUtils>()->QueryScriptInfoManager( context ) ) ;
	ASSERT( scriptInfoMgr ) ;
	if ( scriptInfoMgr ) 
	{
		if ( const ScriptElement* pEnumSI = scriptInfoMgr->FindEnum( ti.GetType() ) )
		{
			typeString.Append( pEnumSI->GetFormattedName( GetFormatNamePolicy( kEnumElement, context ) ) ) ;
			if ( includeInfo & kFormatAsPlural )
				typeString.append( L" enumerators" ) ;
			else
				typeString.append( L" enumerator" ) ;
			return kTrue ;	//handled enum type
		}
	}
	return kFalse ;	//not an enum type
}

//Some client-specific implementations subclassing CScriptManager may want to override this method
bool16 CScriptManager::AppendTypeDefAsString( const ObjectScriptElement* pObjSI, const RequestContext& context, const TypeInfo& ti, int32 includeInfo, PMString& typeString ) const
{
	InterfacePtr<IScriptInfoManager> scriptInfoMgr( Utils<IScriptUtils>()->QueryScriptInfoManager( context ) ) ;
	ASSERT( scriptInfoMgr ) ;
	if ( scriptInfoMgr ) 
	{
#if 0
		//If your client's DOM supports user-defined types, override this method in your subclass
		//of CScriptManager and use this code to append the name of the typedef itself
		if ( const ScriptElement* pTypeDefSI = scriptInfoMgr->FindTypeDef( ti.GetType() ) )
		{
			typeString.Append( pTypeDefSI->GetFormattedName( GetFormatNamePolicy( kTypeDefElement, context ) ) ) ;
			return kTrue ;
		}
#else
		//By default, we return the name of the underlying type for backwards compatibility in
		//existing clients, most of which don't support user-defined types
		if ( const TypeDefScriptElement* pTypeDefSI = scriptInfoMgr->FindTypeDef( ti.GetType() ) )
		{
			AppendTypeAsString( pObjSI, context, pTypeDefSI->GetDefinedType( pObjSI ), includeInfo, typeString ) ;
			return kTrue ;	//handled typedef
		}
#endif
	}
	return kFalse ;	//not a typedef
}

//Some client-specific implementations subclassing CScriptManager may want to override this method
bool16 CScriptManager::AppendArrayString( const RequestContext& context, const TypeInfo& ti, int32 includeInfo, PMString& typeString ) const
{
	if ( ti.IsArrayType() )
	{
		if ( includeInfo & kFormatAsPlural )
			typeString.append( L"Arrays of " ) ;
		else
			typeString.append( L"Array of " ) ;

		if ( ti.GetLength() > 1 )
		{
			typeString.AppendNumber( ti.GetLength() ) ;
			typeString.AppendW( L' ' ) ;
		}

		return kTrue ;	//handled array type
	}
	return kFalse ;	//not an array type
}

//Some client-specific implementations subclassing CScriptManager may want to override this method
bool16 CScriptManager::AppendStructString( const RequestContext& context, const TypeInfo& ti, int32 includeInfo, PMString& typeString ) const
{
	if ( ti.IsStructType() )
	{
		if ( includeInfo & kFormatAsPlural )
			typeString.append( L"Structs containing " ) ;
		else
			typeString.append( L"Struct containing " ) ;

		return kTrue ;	//handled struct type
	}
	return kFalse ;	//not a struct type
}

int32 CScriptManager::GetBaseIndex() const
{
	return 0 ;
}

ErrorCode CScriptManager::PublishDescription( const RequestContext& ) 
{
	return kSuccess ;
}

ScriptVersion CScriptManager::GetMinimumDOMVersion( const PMLocaleId& locale ) const
{
	//The first version to support the new scripting architecture was 3.0
	return kCS1ScriptVersion ;
}

ScriptVersion CScriptManager::GetMaximumDOMVersion( const PMLocaleId& locale ) const
{
	return kMaximumScriptVersion ;
}

ScriptID CScriptManager::GetLanguageEnumerator() const
{
	//Scripting language clients should override
	return kInvalidScriptID ;
}

PMString CScriptManager::GetName() const
{
	//Scripting language clients should override
	return "" ;
}
