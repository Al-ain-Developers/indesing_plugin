//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CProxyScript.h $
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
#ifndef __CProxyScript__
#define __CProxyScript__

#include "CScript.h"

class PUBLIC_DECL CProxyScript : public CScript
{
public:
	CProxyScript( IPMUnknown* boss ) ;
	~CProxyScript() ;

	/** Return the object's type */
	virtual ScriptID		GetObjectType( const RequestContext& context ) const ;

	/**	Most objects know what type they are. But when supporting generic objects, 
		there are cases where 1) the object can be interpreted as different types 
		and/or 2) it is expensive to constantly figure out what type the object is,
		so we provide a way for the object to be told what type it is. */
	virtual void			SetObjectType( const ScriptID& objectType, const RequestContext& context ) ;

	/**	A safe way to determine the appropriate database for this object. Most implementations 
		can simply inherit and use the default implementation { return ::GetDataBase( this ) ; }
		but some script bosses are non-persistent, and should therefore override this method. */
	virtual IDataBase*		GetDataBase( const RequestContext& context ) const ;

	/**	Return specifier information for this object */
	virtual ScriptObject	GetScriptObject( const RequestContext& context ) const ;

	/**	Return the parent of this object in the script hierarchy */
	virtual IPMUnknown*		QueryParent( const PMIID& iid, const RequestContext& context ) const ;

	/**	Return kTrue if the underlying object that this script object represents has been deleted */
	virtual bool16			HasBeenDeleted( const RequestContext& context ) ;

	/**	Return kTrue if the passed in object is (or represents) the same object */
	virtual	bool16			IsEqual( const IScript* script, const RequestContext& context ) const ;

	/** Set a user-definable label.
		NOTE: Since proxy objects are temporary, if you want to set a label on a proxy object, you must 
		override the default implementation in order to transfer the label onto a persistent object!
		@param key is the key
		@param value is the value
	*/
	virtual void			SetTag( const ScriptLabelKey& key, const ScriptLabelValue& value ) ;
	using CScript::SetTag; // needed to defeat C++ name lookup rules, to allow looking in base class for function with same name as one here

protected:
	ScriptID fObjectType ;
} ;

#endif
