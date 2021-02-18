//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CScriptRequestData.h $
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
#ifndef __CScriptRequestData__
#define __CScriptRequestData__

#include "IScriptRequestData.h"

#include <map>

class IScript ;

using namespace ScriptInfo ;

typedef std::pair< InterfacePtr<IScript>, ScriptReturnDataList > ScriptTargetReturnDataPair ;
typedef std::map< InterfacePtr<IScript>, ScriptReturnDataList > ScriptTargetReturnDataList ;
typedef std::pair< ScriptList, ScriptReturnDataList > ScriptListReturnDataPair ;
typedef adobe::vector<ScriptListReturnDataPair> ScriptListReturnDataList ;

#pragma export on

class PUBLIC_DECL CScriptRequestData : public CPMUnknown<IScriptRequestData>
{
public:
	CScriptRequestData(IPMUnknown *boss);
	virtual ~CScriptRequestData();

	virtual ErrorCode InsertRequestData( const ScriptID dataLocation, const ScriptData& data ) ;
	virtual ErrorCode InsertRequestData( const ScriptRecordData& record ) ;
	virtual ErrorCode ExtractRequestData( const ScriptID dataLocation, ScriptData& data ) const ;
	virtual bool16 HasRequestData( const ScriptID dataLocation ) const ;
	virtual ScriptRecordData GetRequestData() const ;

	virtual void ClearReturnData( const IScript* target ) ;
	virtual void ClearReturnData( const ScriptList& targets ) ;
	virtual void AppendReturnData( const IScript* target, const ScriptID requestID, const ErrorCode errorCode ) ;
	virtual void AppendReturnData( const ScriptList& targets, const ScriptID requestID, const ErrorCode errorCode ) ;
	virtual void AppendReturnData( const IScript* target, const ScriptID requestID, const ScriptData& returnValue ) ;
	virtual void AppendReturnData( const ScriptList& targets, const ScriptID requestID, const ScriptData& returnValue ) ;
	virtual void AppendReturnData( const IScript* target, const ScriptReturnData& data ) ;
	virtual void AppendReturnData( const ScriptList& targets, const ScriptReturnData& data ) ;
	virtual void ReplaceReturnData( const IScript* target, const ScriptReturnDataList& data ) ;
	virtual void ReplaceReturnData( const ScriptList& targets, const ScriptReturnDataList& data ) ;
	virtual void AppendReturnData( const IScript* target, const ScriptReturnDataList& data ) ;
	virtual void AppendReturnData( const ScriptList& targets, const ScriptReturnDataList& data ) ;
	virtual uint32 GetNumReturnData( const IScript* target ) const ;		
	virtual uint32 GetNumReturnData( const ScriptList& targets ) const ;		
	virtual ScriptReturnData GetNthReturnData( const IScript* target, uint32 n ) const ;		
	virtual ScriptReturnData GetNthReturnData( const ScriptList& targets, uint32 n ) const ;		
	virtual ScriptReturnDataList GetAllReturnData( const IScript* target ) const ;		
	virtual ScriptReturnDataList GetAllReturnData( const ScriptList& targets ) const ;		

	virtual void SetErrorPolicy( ErrorPolicy policy ) ;
	virtual ErrorPolicy GetErrorPolicy() const ;

	virtual void SetSetPropertiesOrderPolicy( SetPropertiesOrderPolicy policy ) ;
	virtual SetPropertiesOrderPolicy GetSetPropertiesOrderPolicy() const ;

	virtual void SetTargetInfo( const ScriptElementID objectID ) ;
	virtual void SetTargetInfo( const ObjectScriptElement* pObject ) ;
	virtual const ObjectScriptElement* GetTargetInfo() const ;

	virtual const ScriptID GetDesiredType() const ;

	virtual RequestType GetRequestType() const ;
	virtual const ScriptElement* GetRequestInfo() const ;

	virtual void SetMethod( const ScriptElementID methodID ) ;
	virtual void SetMethod( const MethodScriptElement* pMethod ) ;
	virtual bool16 IsMethod() const ;
	virtual void SetMethodWithProperties( bool16 withProperties ) ;
	virtual bool16 IsMethodWithProperties() const ;

	virtual void SetPropertyGet( const ScriptElementID propID ) ;
	virtual void SetPropertyGet( const PropertyScriptElement* pProp ) ;
	virtual bool16 IsPropertyGet() const ;

	virtual void SetPropertyPut( const ScriptElementID propID ) ;
	virtual void SetPropertyPut( const PropertyScriptElement* pProp ) ;
	virtual bool16 IsPropertyPut() const ;

	virtual void SetFindCollection( const ScriptElementID objID ) ;
	virtual void SetFindCollection( const ObjectScriptElement* pObj ) ;
	virtual bool16 IsFindCollection() const ;

	virtual void SetGetObject( const ScriptElementID objID, SpecifierForm accessorForm, const ScriptData& accessorData ) ;
	virtual void SetGetObject( const ObjectScriptElement* pObj, SpecifierForm accessorForm, const ScriptData& accessorData ) ;
	virtual bool16 IsGetObject() const ;
	virtual SpecifierForm GetAccessorForm() const ;
	virtual ScriptData GetAccessorData() const ;

	virtual void SetTargetHandlingPolicy( TargetHandlingPolicy policy ) ;
	virtual TargetHandlingPolicy GetTargetHandlingPolicy() const ;

	virtual void SetRequestedDataType( const ScriptID requestedType ) ;
	virtual const ScriptID GetRequestedDataType() const ;

	virtual void SetFormTestCaseSensitive( bool16 caseSensitive ) ;
	virtual bool16 GetFormTestCaseSensitive() const ;

	// Access to the request context for this request
	virtual const EngineContext& GetRequestContext() const ;
	virtual void SetRequestContext( const EngineContext& context ) ;

	virtual void CloneRequestData( IScriptRequestData* other ) const ;
	virtual void Reset() ;
	virtual void Release() const ;

protected:
	/** Override in subclass if you need to translate client-specific request data before request data is accessed.
		Return const& internally for performance.
	*/
	virtual const ScriptRecordData& InternalGetRequestData() const ;

private:
	ScriptRecordData			fRequestData ;
	ScriptTargetReturnDataList	fReturnData ;		//return data for single targets
	ScriptListReturnDataList	fCollectiveReturnData ;	//return data for collective targets
	ErrorPolicy					fErrorPolicy ;
	SetPropertiesOrderPolicy	fSetPropertiesOrderPolicy ;
	const ObjectScriptElement*	fTargetInfo ;
	const ScriptElement*		fRequestInfo ;
	RequestType					fRequestType ;
	bool16						fIsMethodWithProperties ;
	SpecifierForm				fAccessorForm ;
	ScriptData					fAccessorData ;
	TargetHandlingPolicy		fHandlingPolicy ;
	ScriptID					fRequestedDataType ;
	bool16						fFormTestCaseSensitive ;
	EngineContext				fRequestContext ;
};

#pragma export off

#endif
