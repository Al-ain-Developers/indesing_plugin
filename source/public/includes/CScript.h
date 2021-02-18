//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CScript.h $
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
#ifndef __CScript__
#define __CScript__

#include "IScript.h"

#pragma export on
class PUBLIC_DECL CScript : public CPMUnknown<IScript>
{
public:
	CScript( IPMUnknown* boss ) ;
	~CScript();
	
	/** Return the object's type */
	virtual ScriptID		GetObjectType( const RequestContext& context ) const = 0 ;

	/** Return kTrue if this object is or is based on this type */
	virtual bool16			IsObjectType( const ScriptID& type, const RequestContext& context ) const ;
	virtual bool16			IsObjectType( const ScriptElementID& type, const RequestContext& context ) const ;

	/** Return the object's script info */
	virtual const ObjectScriptElement*	GetObjectInfo( const RequestContext& context ) const ;

	/**	Most objects know what type they are. But when supporting generic objects, 
		there are cases where 1) the object can be interpreted as different types 
		and/or 2) it is expensive to constantly figure out what type the object is,
		so we provide a way for the object to be told what type it is. This base
		class does NOT support this feature, so a subclass that wants it must (i.e.,
		by storing the current object type as private data). */
	virtual void			SetObjectType( const ScriptID& type, const RequestContext& context ) ;

	/**	A safe way to determine the appropriate database for this object. Most implementations 
		can simply inherit and use the default implementation { return ::GetDataBase( this ) ; }
		but some script bosses are non-persistent, and should therefore override this method. */
	virtual IDataBase*		GetDataBase( const RequestContext& context ) const ;

	/**	Return specifier information for this object */
	virtual ScriptObject	GetScriptObject( const RequestContext& context ) const ;

	/**	Return the parent of this object in the script hierarchy */
	virtual IPMUnknown*		QueryParent( const PMIID& iid, const RequestContext& context ) const = 0 ;

	/**	Return kTrue if the underlying object that this script object represents has been deleted */
	virtual bool16			HasBeenDeleted( const RequestContext& context ) ;

	/**	Return kTrue if the passed in object is (or represents) the same object */
	virtual	bool16			IsEqual( const IScript* script, const RequestContext& context ) const;

	/**
		Register a scripting client object. Calls ScriptClientObject::AddRef().
		Does nothing if the client object passed in is nil.
		@param clientObject is the scripting client object. Must NOT be an interface on this boss.
	*/
	virtual void			RegisterClientObject( ScriptClientObject* clientObject ) ;
	/**
		Unregister a scripting client object. Calls ScriptClientObject::Release(). 
		Does nothing if the client object passed in is nil or was not previously 
		passed to RegisterClientObject() on this IScript.
		@param clientObject is the scripting client object
	*/
	virtual void			UnregisterClientObject( ScriptClientObject* clientObject ) ;
	/**
		Notify all registered client objects to release any references they're holding on my boss.
	*/
	virtual void			NotifyClientObjectsToReleaseMe() ;

	/** Set the default label property
		@param string is the label to set
	*/
	virtual void							SetTag( const ScriptLabelValue& string ) ;
	/** Get the default label property */
	virtual ScriptLabelValue				GetTag() const ;

	/** Set a user-definable label
		@param key is the key
		@param value is the value
	*/
	virtual void							SetTag( const ScriptLabelKey& key, const ScriptLabelValue& value ) ;
	/** Get a user-definable label
		@param key is the key
		@return is the value
	*/
	virtual ScriptLabelValue				GetTag( const ScriptLabelKey& key ) const ;

	/** Set a list of user-definable labels */
	virtual void							SetTags( const ScriptLabelKeyValueList& labels ) ;
	/** Get the list of all the user-definable labels */
	virtual ScriptLabelKeyValueList			GetTags() const ;

	/** Clear all of the user-definable labels */
	virtual void							ClearTags() ;

	/**	This is a persistent implementation to support the tag property */
	virtual void			ReadWrite(IPMStream *s, ImplementationID prop);

private:
	ScriptLabelKeyValueList			fLabels;
	K2Vector<ScriptClientObject*>	fClientObjects ;	//not persisted

#ifdef DEBUG
	bool16		fBDidConversion;
#endif
};

inline void K2Write(IPMStream* stream, const CScript::ScriptLabelKeyValuePair& kvp)
{
	PMString& keyStr = const_cast<PMString&>(kvp.Key());
	keyStr.ReadWrite(stream);
	PMString& valStr = const_cast<PMString&>(kvp.Value());
	valStr.ReadWrite(stream);
}

inline void K2Read(IPMStream* stream, CScript::ScriptLabelKeyValuePair& kvp)
{
	kvp.Key().ReadWrite(stream);
	kvp.Value().ReadWrite(stream);
}


#pragma export off

#endif
