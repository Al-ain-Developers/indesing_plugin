//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/scripting/CProxyScript.cpp $
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
#include "CProxyScript.h"

#include "IIntData.h"
#include "IScriptManager.h"
#include "IScriptObjectParent.h"

// Moved to PublicImpl.cpp
// CREATE_PMINTERFACE( CProxyScript, kCProxyScriptImpl )

CProxyScript::CProxyScript( IPMUnknown* boss ) :
	CScript( boss ),
	fObjectType( kInvalidScriptID )
{
}

CProxyScript::~CProxyScript()
{
}

void CProxyScript::SetObjectType( const ScriptID& objectType, const RequestContext& context )
{
	fObjectType = objectType ;
}

ScriptID CProxyScript::GetObjectType( const RequestContext& context ) const
{
	ASSERT_MSG( fObjectType != kInvalidScriptID, "Object type of this object has not been set yet" ) ;

	return fObjectType ;
}

// A safe way to determine the appropriate database for this object. Most implementations 
// can simply inherit and use the default implementation { return ::GetDataBase( this ) ; }
// but some script bosses are non-persistent, and should therefore override this method.
IDataBase* CProxyScript::GetDataBase( const RequestContext& context ) const
{
	IDataBase* db = nil ;

	InterfacePtr<const IScriptObjectParent> parentData( this, UseDefaultIID() ) ;
	if ( parentData )
		db = parentData->GetParentDataBase() ;

	ASSERT_MSG( db != nil, "Database is nil" ) ;
	return db ;
}

ScriptObject CProxyScript::GetScriptObject( const RequestContext& context ) const
{
	int32 index = 0 ; //default to 0

	InterfacePtr<IScriptManager> scriptManager( context.QueryScriptManager() ) ;
	ASSERT( scriptManager ) ;
	if ( scriptManager )
		index = scriptManager->GetBaseIndex() ;

	InterfacePtr<const IIntData> indexData( this, UseDefaultIID() ) ;
	ASSERT( indexData ) ;
	if ( indexData != nil )
		index += indexData->GetInt() ;	//convert internal index to external index

	return ScriptObject( ScriptData( index ), GetObjectType( context ), kFormIndex ) ;
}

IPMUnknown* CProxyScript::QueryParent( const PMIID& iid, const RequestContext& context ) const
{
	IPMUnknown* parent = nil ;

	InterfacePtr<const IScriptObjectParent> parentData( this, UseDefaultIID() ) ;
	if ( parentData != nil )
		parent = parentData->QueryParent( iid ) ;
	else
		ASSERT_FAIL( "Missing IScriptObjectParent interface on this proxy script object boss." ) ;

	return parent ;
}

bool16 CProxyScript::HasBeenDeleted( const RequestContext& context )
{
	//At the very least, this object's parent must still be valid
	InterfacePtr<IScript> parent( (IScript*) QueryParent( IID_ISCRIPT, context ) ) ;
	return ( parent == nil ) ;
}

bool16 CProxyScript::IsEqual( const IScript* script, const RequestContext& context ) const
{
	if ( script == nil ) return kFalse ;

	if ( this == script ) return kTrue ;

	if ( context.GetVersion() < kCS3ScriptVersion )
	{
		//Old way
		if (this->GetObjectType( context ) != script->GetObjectType( context )) return kFalse;

		InterfacePtr<const IIntData> indexData( this, UseDefaultIID() ) ;
		ASSERT_MSG( indexData, "Missing IIntData on proxy script object boss" ) ;
		if (!indexData) return kFalse;

		InterfacePtr<const IIntData> inIndexData( script, UseDefaultIID() ) ;
		ASSERT_MSG( inIndexData, "Missing IIntData on proxy script object boss" ) ;
		if (!inIndexData) return kFalse;

		if (indexData->Get() != inIndexData->Get()) return kFalse ;
	}
	else
	{
		//New, more flexible way
		if ( !( this->GetScriptObject( context ) == script->GetScriptObject( context ) ) )
			return kFalse ;
	}

	InterfacePtr<IScript> myParent( (IScript*) this->QueryParent( IID_ISCRIPT, context ) ) ;
	ASSERT_MSG( myParent, "Missing parent for proxy script object" ) ;
	if (!myParent) return kFalse ;

	InterfacePtr<IScript> inParent( (IScript*) script->QueryParent( IID_ISCRIPT, context ) ) ;
	ASSERT_MSG( inParent, "Missing parent for proxy script object" ) ;
	if (!inParent) return kFalse ;

	return myParent->IsEqual( inParent, context ) ; 
}

void CProxyScript::SetTag( const ScriptLabelKey& key, const ScriptLabelValue& value )
{
	//NOTE: Since proxy objects are temporary, if you want to set a label on a proxy object, you must 
	//override the default implementation in order to transfer the label onto a persistent object!
	ASSERT_FAIL( "Calling SetTag to save a label on a (non-persistent) proxy script object" ) ;
	CScript::SetTag( key, value ) ;
}
