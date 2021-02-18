//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IScriptRequestHandler.h $
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
#ifndef __IScriptRequestHandler__
#define __IScriptRequestHandler__

#include "IPMUnknown.h"

#include "IScriptRequestData.h"

class IScript ;

namespace ScriptInfo
{
class ObjectScriptElement ;
}

/**
	Matches requests from clients to the appropriate script provider.
*/
class IScriptRequestHandler : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISCRIPTREQUESTHANDLER };

	// Handling Script Requests ---------------------------------------------------------------------------------------------

	/**
		Get a script object
		@param parent - the parent script object
		@param objectType - the type of the desired script object
		@param accessorForm - the form of the get request
		@param accessorData - the data for the get request
		@param scriptRequestData - the request context
		@return	kSuccess if the specified object was found,
				kInvalidCollectionItemError if the specified object wasn't found,
				or another error code if getting the specified object failed
	*/
	virtual ErrorCode DoGetObject( IScript* parent, const ScriptID& objectType, SpecifierForm accessorForm, const ScriptData& accessorData, IScriptRequestData* scriptRequestData ) const = 0 ;

	/**
		Handle a method request
		@param script - the script object
		@param objectType - the type of object
		@param methodID - the method's ID
		@param scriptRequestData - the request context
		@return	kSuccess if the method was handled successfully,
				kRequestNotHandledError if the method wasn't handled at all,
				or another error code if the method failed
	*/
	virtual ErrorCode DoHandleMethod( IScript* script, const ScriptID& methodID, IScriptRequestData* scriptRequestData ) const = 0 ;
	virtual ErrorCode DoHandleMethod( IScript* script, const ScriptElementID& methodID, IScriptRequestData* scriptRequestData ) const = 0 ;
	virtual ErrorCode DoHandleMethod( const ScriptList& scriptList, const ScriptID& methodID, IScriptRequestData* scriptRequestData ) const = 0 ;
	virtual ErrorCode DoHandleMethod( const ScriptList& scriptList, const ScriptElementID& methodID, IScriptRequestData* scriptRequestData ) const = 0 ;

	/**
		Handle a collection method request
		@param parent - the parent script object
		@param objectType - the type of child object
		@param methodID - the method's ID
		@param scriptRequestData - the request context
		@return	kSuccess if the method was handled successfully,
				kRequestNotHandledError if the method wasn't handled at all,
				or another error code if the method failed
	*/
	virtual ErrorCode DoHandleCollectionMethod( IScript* parent, const ScriptID& childType, const ScriptID& methodID, IScriptRequestData* scriptRequestData ) const = 0 ;
	virtual ErrorCode DoHandleCollectionMethod( IScript* parent, const ScriptID& childType, const ScriptElementID& methodID, IScriptRequestData* scriptRequestData ) const = 0 ;
	virtual ErrorCode DoHandleCollectionMethod( const ScriptList& parentList, const ScriptID& childType, const ScriptID& methodID, IScriptRequestData* scriptRequestData ) const = 0 ;
	virtual ErrorCode DoHandleCollectionMethod( const ScriptList& parentList, const ScriptID& childType, const ScriptElementID& methodID, IScriptRequestData* scriptRequestData ) const = 0 ;

	/**
		Handle a set property request
		@param script - the script object
		@param objectType - the type of object
		@param propertyID - the property
		@param scriptRequestData - the request context
		@return	kSuccess if the property was accessed successfully,
				kRequestNotHandledError if the property wasn't accessed at all,
				or another error code if the property access failed
	*/
	virtual ErrorCode DoSetProperty( IScript* script, const ScriptID& propertyID, IScriptRequestData* scriptRequestData ) const = 0 ;
	virtual ErrorCode DoSetProperty( IScript* script, const ScriptElementID& propertyID, IScriptRequestData* scriptRequestData ) const = 0 ;
	virtual ErrorCode DoSetProperty( const ScriptList& scriptList, const ScriptID& propertyID, IScriptRequestData* scriptRequestData ) const = 0 ;
	virtual ErrorCode DoSetProperty( const ScriptList& scriptList, const ScriptElementID& propertyID, IScriptRequestData* scriptRequestData ) const = 0 ;

	/**
		Handle a get property request
		@param script - the script object
		@param objectType - the type of object
		@param propertyID - the property
		@param scriptRequestData - the request context
		@return	kSuccess if the property was accessed successfully,
				kRequestNotHandledError if the property wasn't accessed at all,
				or another error code if the property access failed
	*/
	virtual ErrorCode DoGetProperty( IScript* script, const ScriptID& propertyID, IScriptRequestData* scriptRequestData ) const = 0 ;
	virtual ErrorCode DoGetProperty( IScript* script, const ScriptElementID& propertyID, IScriptRequestData* scriptRequestData ) const = 0 ;
	virtual ErrorCode DoGetProperty( const ScriptList& scriptList, const ScriptID& propertyID, IScriptRequestData* scriptRequestData ) const = 0 ;
	virtual ErrorCode DoGetProperty( const ScriptList& scriptList, const ScriptElementID& propertyID, IScriptRequestData* scriptRequestData ) const = 0 ;

	/**
		Get a script object collection
		@param script - the parent script object
		@param collectionID - the type of the object for which a collection is desired
		@param scriptRequestData - the request context
		@return	a pointer to the specified collection's object info,
				or nil if the specified collection wasn't found
	*/
	virtual const ScriptInfo::ObjectScriptElement* FindCollectionInfo( IScript* script, const ScriptID& collectionID, IScriptRequestData* scriptRequestData ) const = 0 ;
	virtual const ScriptInfo::ObjectScriptElement* FindCollectionInfo( IScript* script, const ScriptElementID& collectionID, IScriptRequestData* scriptRequestData ) const = 0 ;

	/**
		Set multiple properties of an object
	*/
	virtual ErrorCode SetProperties( IScript* script, IScriptRequestData* data ) const = 0 ;
	/**
		Get all properties of an object
	*/
	virtual ErrorCode GetProperties( IScript* script, IScriptRequestData* data ) const = 0 ;
} ;

#endif	// __IScriptRequestHandler__
