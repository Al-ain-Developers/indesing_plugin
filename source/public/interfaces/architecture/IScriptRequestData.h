//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IScriptRequestData.h $
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
#ifndef __IScriptRequestData__
#define __IScriptRequestData__

#include "IPMUnknown.h"
#include "IScript.h"
#include "ScriptInfo.h"
#include "ScriptingID.h"
#include "ScriptReturnData.h"

using namespace ScriptInfo ;

/**
	Used to pass data into and out of a scripting request.
*/
class IScriptRequestData : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_ISCRIPTREQUESTDATA };

	/**
		Insert request data
	*/	//Methods, Properties IN
	virtual ErrorCode InsertRequestData( const ScriptID dataLocation, const ScriptData& data ) = 0 ;

	/**
		Insert all of the data from a ScriptRecordData into the request data
		@param record is the list of data to insert
	*/	//Methods, Properties IN
	virtual ErrorCode InsertRequestData( const ScriptRecordData& record ) = 0;

	/**
		Extract data out of the script request
		@param dataLocation is the key that specifies the desired parameter
		@param data is the extracted data
	*/	//Methods, Properties IN
	virtual ErrorCode ExtractRequestData(	const ScriptID dataLocation, ScriptData& data ) const = 0 ;

	/**
		Returns kTrue if there is request data at the specified location
		@param dataLocation is the key that specifies the desired parameter
	*/	//Methods, Properties IN
	virtual bool16 HasRequestData( const ScriptID dataLocation ) const = 0 ;

	/**
		Access to all the request data
	*/	//Methods IN
	virtual ScriptRecordData GetRequestData() const = 0 ;

	/**
		Clear all return data for a particular target
		@target - the target (must be non-nil)
	*/
	virtual void ClearReturnData( const IScript* target ) = 0 ;
	/**
		Clear all return data for a particular set of targets
		@targets - the targets (must be 1 or more)
	*/
	virtual void ClearReturnData( const ScriptList& targets ) = 0 ;

	/**
		Append one item of return data for a particular target
		@target - the target (must be non-nil)
	*/	//Methods, Properties, Objects OUT
	//Use for successful kMethodRequest (no return value), kPutPropertyRequest, or kFindCollectionRequest
	//Use for unsuccessful request
	virtual void AppendReturnData( const IScript* target, const ScriptID requestID, const ErrorCode errorCode ) = 0 ;
	virtual void AppendReturnData( const ScriptList& targets, const ScriptID requestID, const ErrorCode errorCode ) = 0 ;
	//Use for successful kMethodRequest (with return value), kGetPropertyRequest, or kGetObjectRequest
	virtual void AppendReturnData( const IScript* target, const ScriptID requestID, const ScriptData& returnValue ) = 0 ;
	virtual void AppendReturnData( const ScriptList& targets, const ScriptID requestID, const ScriptData& returnValue ) = 0 ;

	/**
		Append multiple items of return data for a particular target
		@target - the target (must be non-nil)
	*/
	virtual void AppendReturnData( const IScript* target, const ScriptReturnDataList& data ) = 0 ;
	/**
		Append multiple items of return data for a particular set of targets
		@targets - the targets (must be 1 or more)
	*/
	virtual void AppendReturnData( const ScriptList& targets, const ScriptReturnDataList& data ) = 0 ;

	/**
		Replace all return data for a particular target
		@target - the target (must be non-nil)
	*/
	virtual void ReplaceReturnData( const IScript* target, const ScriptReturnDataList& data ) = 0 ;
	/**
		Replace all return data for a particular set of targets
		@targets - the targets (must be 1 or more)
	*/
	virtual void ReplaceReturnData(const ScriptList& targets, const ScriptReturnDataList& data ) = 0 ;

	/**
		Retrieve the return data for a particular target
		@target - the target (must be non-nil)
	*/
	virtual uint32 GetNumReturnData( const IScript* target ) const = 0 ;		
	virtual uint32 GetNumReturnData( const ScriptList& targets ) const = 0 ;		
	virtual ScriptReturnData GetNthReturnData( const IScript* target, uint32 n ) const = 0 ;		
	virtual ScriptReturnData GetNthReturnData( const ScriptList& targets, uint32 n ) const = 0 ;		
	virtual ScriptReturnDataList GetAllReturnData( const IScript* target ) const = 0 ;		
	virtual ScriptReturnDataList GetAllReturnData( const ScriptList& targets ) const = 0 ;		

	/** Convert the return data into a list of return values */
	static ScriptListData ConvertToScriptListData( const ScriptReturnDataList& srdl )
	{
		ScriptListData sld ;
		for ( ScriptReturnDataList::const_iterator iter = srdl.begin() ; iter != srdl.end() ; ++iter )
		{
			if ( iter->GetErrorCode() == kSuccess && !iter->GetReturnValue().IsEmpty() )
				sld.push_back( iter->GetReturnValue() ) ;
		}
		return sld ;
	}

	/** Convert the return data into a list of request ID/return value pairs */
	static ScriptRecordData ConvertToScriptRecordData( const ScriptReturnDataList& srdl )
	{
		ScriptRecordData srd ;
		for ( ScriptReturnDataList::const_iterator iter = srdl.begin() ; iter != srdl.end() ; ++iter )
		{
			if ( iter->GetErrorCode() == kSuccess && !iter->GetReturnValue().IsEmpty() )
				srd.push_back( ScriptIDValuePair( iter->GetRequestID(), iter->GetReturnValue() ) ) ;
		}
		return srd ;
	}

	/**
		Access to the error policy for handling multiple requests.
	*/
	virtual void SetErrorPolicy( ErrorPolicy policy ) = 0 ;
	virtual ErrorPolicy GetErrorPolicy() const = 0 ;

	/**
		Access to the policy for the order to set properties when setting multiple properties at once
	*/
	virtual void						SetSetPropertiesOrderPolicy( SetPropertiesOrderPolicy policy ) = 0 ;
	virtual SetPropertiesOrderPolicy	GetSetPropertiesOrderPolicy() const = 0 ;

	/**
		Set the object at which a request is targeted.
		For a regular method or property request, the target is the object being manipulated.
		For a method request on a collection, the target is the object being counted or created (not the parent).
		For a get object or find collection request, the target is the parent.
	*/	//IN
	virtual void SetTargetInfo( const ScriptElementID objectID ) = 0 ;
	virtual void SetTargetInfo( const ObjectScriptElement* pObject ) = 0 ;
	/**
		Retrieve the object at which this request is targeted.
	*/
	virtual const ObjectScriptElement* GetTargetInfo() const = 0 ;

	/**
		For a get object or find collection request, equivalent to GetRequestInfo()->GetScriptID().
		For all other requests, equivalent to GetTargetInfo()->GetScriptID().
	*/
	virtual const ScriptID GetDesiredType() const = 0 ;

	/**
		Script request types
	*/
	enum RequestType
	{
		/** */
		kUnknownRequest,
		/** */
		kMethodRequest,
		/** */
		kGetPropertyRequest,
		/** */
		kPutPropertyRequest,
		/** */
		kGetObjectRequest,
		/** */
		kFindCollectionRequest
	} ;

	/**
		Returns the request type
	*/
	virtual RequestType GetRequestType() const = 0 ;
	/**
		Returns the request
	*/
	virtual const ScriptElement* GetRequestInfo() const = 0 ;

	/**
		Set if the request is to handle a method.
		May be retrieved via GetRequestInfo().
	*/	//Methods IN
	virtual void SetMethod( const ScriptElementID methodID ) = 0 ;
	virtual void SetMethod( const MethodScriptElement* pMethod ) = 0 ;
	/**
		Returns kTrue if this request is to handle a method.
	*/
	virtual bool16 IsMethod() const = 0 ;

	/**
		Indicates whether a method that creates an object includes data to initialize its properties
	*/	//Methods IN
	virtual void SetMethodWithProperties( bool16 withProperties ) = 0 ;
	virtual bool16 IsMethodWithProperties() const = 0 ;

	/**
		Set if the request is to get a property.
		May be retrieved via GetRequestInfo().
	*/	//Properties IN
	virtual void SetPropertyGet( const ScriptElementID propID ) = 0 ;
	virtual void SetPropertyGet( const PropertyScriptElement* pProp ) = 0 ;
	/**
		Returns kTrue if this request is to get a property.
	*/
	virtual bool16 IsPropertyGet() const = 0 ;

	/**
		Set if the request is to set a property.
		May be retrieved via GetRequestInfo().
	*/	//Properties IN
	virtual void SetPropertyPut( const ScriptElementID propID ) = 0 ;
	virtual void SetPropertyPut( const PropertyScriptElement* pProp ) = 0 ;
	/**
		Returns kTrue if this request is to set a property.
	*/
	virtual bool16 IsPropertyPut() const = 0 ;

	/**
		Set if the request is to find a collection.
		May be retrieved via GetRequestInfo().
	*/	//Collection IN
	virtual void SetFindCollection( const ScriptElementID objID ) = 0 ;
	virtual void SetFindCollection( const ObjectScriptElement* pObj ) = 0 ;
	/**
		Returns kTrue if this request is to find a collection.
	*/
	virtual bool16 IsFindCollection() const = 0 ;

	/**
		Set if the request is to get objects.
		@param objID/pObj is the object to get. May be retrieved via GetRequestInfo().
		@param accessorForm is the key specifying which objects to get
		@param accessorData is the additional data required by some specifiers
	*/	//Objects IN
	virtual void SetGetObject( const ScriptElementID objID, SpecifierForm accessorForm, const ScriptData& accessorData ) = 0 ;
	virtual void SetGetObject( const ObjectScriptElement* pObj, SpecifierForm accessorForm, const ScriptData& accessorData ) = 0 ;
	/**
		Returns kTrue if this request is to get objects.
	*/
	virtual bool16 IsGetObject() const = 0 ;

	/**
		Retrieve accessor form for a get objects request.
	*/
	virtual SpecifierForm GetAccessorForm() const = 0 ;
	/**
		Retrieve accessor data for a get objects request.
	*/
	virtual ScriptData GetAccessorData() const = 0 ;

	/**
		Used to express a preference for how a script provider should 
		handle a request on multiple targets.
	*/
	enum TargetHandlingPolicy
	{
		kDefault,			//use default approach for the request
		kIndividually,		//handle request on each target separately
		kCollectively		//handle request on all targets simultaneously
	} ;
	virtual void SetTargetHandlingPolicy( TargetHandlingPolicy policy ) = 0 ;
	virtual TargetHandlingPolicy GetTargetHandlingPolicy() const = 0 ;

	/**
		The format in which to return a result.
	*/	//Objects, Properties( Text Contents ) IN
	virtual void SetRequestedDataType( const ScriptID requestedType ) = 0 ;
	virtual const ScriptID GetRequestedDataType() const = 0 ;

	/**
		Indicates whether to ignore case when comparing strings.
		Note: The value of this option is not currently honored.
	*/	//Objects, Properties IN
	virtual void SetFormTestCaseSensitive( bool16 caseSensitive ) = 0 ;
	virtual bool16 GetFormTestCaseSensitive() const = 0 ;

	/**
		Access to the request context for this request
	*/
	virtual const EngineContext& GetRequestContext() const = 0 ;

	/**
		Called during creation of the interface to set the request context for the request
	*/	//Internal Use Only
	virtual void SetRequestContext( const EngineContext& context ) = 0 ;

	/**
		Copy this request data into another request data interface
	*/
	virtual void CloneRequestData( IScriptRequestData* other ) const = 0 ;
};

#endif
