//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IScript.h $
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
#ifndef __IScript__
#define __IScript__

#include "IScriptLabel.h"

#include "ScriptingID.h"
#include "ScriptObject.h"

class ScriptClientObject ;

using namespace ScriptInfo ;

/**
	Added to any boss that wants to be visible as an object in the scripting 
	architecture and thus available to any scripting client.
*/  
class IScript : public IScriptLabel
{
public:
	enum { kDefaultIID = IID_ISCRIPT };

	virtual ~IScript() {}
	/**
		Return the object's type
		@param context is the request context
	*/
	virtual	ScriptID		GetObjectType( const RequestContext& context ) const = 0 ;

	/**
		Return kTrue if this object is or is based on the specified type
		@param type is the type to check
		@param context is the request context
	*/
	virtual bool16			IsObjectType( const ScriptID& type, const RequestContext& context ) const = 0 ;
	virtual bool16			IsObjectType( const ScriptElementID& type, const RequestContext& context ) const = 0 ;

	/**
		Return the object's script info
		@param context is the request context
	*/
	virtual const ObjectScriptElement* GetObjectInfo( const RequestContext& context ) const = 0 ;

	/**
		Most objects know what type they are. But when supporting generic objects such as 
		page items or text, there are cases where 1) the object can be interpreted as 
		different types and/or 2) it is expensive to constantly figure out what type the 
		object is. So we allow the object to be told what type it is.
		@param type is the type to set
		@param context is the request context
	*/
	virtual void			SetObjectType( const ScriptID& type, const RequestContext& context ) = 0 ;

	/**
		A safe way to determine the appropriate database for this object. Most implementations 
		can simply inherit and use the default implementation { return ::GetDataBase( this ) ; }
		but some script bosses are non-persistent, and should therefore override this method.
		@param context is the request context
	*/
	virtual IDataBase*		GetDataBase( const RequestContext& context ) const = 0 ;

	/**
		Return information for the object specifier
		@param context is the request context
	*/
	virtual ScriptObject	GetScriptObject( const RequestContext& context ) const = 0 ;

	/**
		Return the parent of this object in the script hierarchy
		@param iid is desired interface on the parent
		@param context is the request context
	*/
	virtual IPMUnknown*		QueryParent( const PMIID& iid, const RequestContext& context ) const = 0 ;

	/**
		Return kTrue if the underlying object that this script object represents has been deleted
		@param context is the request context
	*/
	virtual bool16			HasBeenDeleted( const RequestContext& context ) = 0 ;
	
	/**
		An IScript represents an object that is visible to scripting
		The IScript either lives on the object itself or on a proxy object
		Comparing IScripts means determining whether both IScripts point to
		the same object. Since you can have multiple proxy objects pointing
		at the same object we need this operator.
		@param script is the other script object
		@param context is the request context
	*/
	virtual	bool16			IsEqual( const IScript* script, const RequestContext& context ) const = 0;

	/**
		Register a scripting client object. Calls ScriptClientObject::AddRef().
		Does nothing if the client object passed in is nil.
		@param clientObject is the scripting client object. Must NOT be an interface on this boss.
	*/
	virtual void			RegisterClientObject( ScriptClientObject* clientObject ) = 0 ;

	/**
		Unregister a scripting client object. Calls ScriptClientObject::Release(). 
		Does nothing if the client object passed in is nil or was not previously 
		passed to RegisterClientObject() on this IScript.
		@param clientObject is the scripting client object
	*/
	virtual void			UnregisterClientObject( ScriptClientObject* clientObject ) = 0 ;

	/**
		Notify all registered client objects to release any references they're holding on my boss.
	*/
	virtual void			NotifyClientObjectsToReleaseMe() = 0 ;
};

// specialize adobe::type_info<> to avoid typeid problems across DLL boundaries
ADOBE_NAME_TYPE_0("iscript:indesign:adobe",IScript);

#endif
