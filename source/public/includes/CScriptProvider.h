//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CScriptProvider.h $
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
#ifndef __CScriptProvider__
#define __CScriptProvider__

#include "CPMUnknown.h"
#include "ICommand.h"
#include "IScript.h"
#include "IScriptErrorUtils.h"
#include "IScriptRequestData.h"
#include "IScriptProvider.h"
#include "IScriptUtils.h"

#pragma export on

/**
	A base class for script providers that add support for methods and properties.
*/
class PUBLIC_DECL CScriptProvider : public CPMUnknown<IScriptProvider>
{
protected:
	typedef CPMUnknown<IScriptProvider> Inherited ;

	CScriptProvider(IPMUnknown *boss);
	virtual ~CScriptProvider();

	/** Obtain a list of child objects, as specified by the data, that are contained in the parent object. 
		This method is only relevant for subclasses of RepresentScriptProvider. */
	virtual void	GetObject( IScriptRequestData* data, IScript* parent ) ;

	/**	Handle the specified method using the provided data for the target objects. 
		Most subclasses will not need to override this method.
			@param methodID is the request ID
			@param data is the request data. The implementation must call AppendReturnData before returning.
			@param scriptList is the target objects
	*/
	virtual void	HandleMethodOnObjects( ScriptID methodID, IScriptRequestData* data, const ScriptList& scriptList ) ;

	/**	Access the specified property using the provided data for the target objects. 
		Most subclasses will not need to override this method.
			@param propID is the request ID
			@param data is the request data. The implementation must call AppendReturnData before returning.
			@param scriptList is the target objects
	*/
	virtual void	AccessPropertyOnObjects( ScriptID propID, IScriptRequestData* data, const ScriptList& scriptList ) ;

	/**	Access multiple properties using the provided data for the target object. 
		Most subclasses will not need to override this method.
			@param data is the request data. The implementation must call AppendReturnData before returning.
			@param script is the target object
	*/
	virtual void	AccessProperties( IScriptRequestData* data, IScript* script ) ;

	/**	Handle the specified method using the provided data for the target object.
		Most subclasses will override this method.
			@param methodID is the request ID
			@param data is the request data. If the return value is kSuccess, the implementation must call AppendReturnData 
				before returning. If the return value is not kSuccess, the implementation should not call AppendReturnData.
			@param script is the target object
			@return kSuccess or an error code
	*/
	virtual ErrorCode	HandleMethod( ScriptID methodID, IScriptRequestData* data, IScript* script ) ;

	/**	Access the specified property using the provided data for the target object.
		Most subclasses will override this method.
			@param propID is the request ID
			@param data is the request data. If the return value is kSuccess, the implementation must call AppendReturnData 
				before returning. If the return value is not kSuccess, the implementation should not call AppendReturnData.
			@param script is the target object
			@return kSuccess or an error code
	*/
	virtual ErrorCode	AccessProperty( ScriptID propID, IScriptRequestData* data, IScript* script ) ;

	/**	Called by AccessProperty before processing a single property on an object.
		Some subclasses may want to override this method. */
	virtual ErrorCode	PreAccessProperty( ScriptID propID, IScriptRequestData* data, IScript* script ) ;

	/**	Called by AccessProperty after processing a single property on an object.
		Some subclasses may want to override this method. */
	virtual ErrorCode	PostAccessProperty( ScriptID propID, IScriptRequestData* data, IScript* script ) ;

	/**	Called by AccessProperties before processing multiple properties on an object.
		Some subclasses may want to override this method. */
	virtual ErrorCode	PreAccessProperties( IScriptRequestData* data, IScript* script ) ;

	/**	Called by AccessProperties after processing multiple properties on an object.
		Some subclasses may want to override this method. */
	virtual ErrorCode	PostAccessProperties( IScriptRequestData* data, IScript* script ) ;

	/**	Access the parent property using the provided data for the target object. 
		Most subclasses will not need to override this method.
			@param propID is the request ID
			@param data is the request data. If the return value is kSuccess, the implementation must call AppendReturnData 
				before returning. If the return value is not kSuccess, the implementation should not call AppendReturnData.
			@param script is the target object
			@return kSuccess or an error code
	*/
	virtual ErrorCode	AccessParent( ScriptID propID, IScriptRequestData* data, IScript* script ) ;
};

/**
	A base class for script providers that represent objects.
*/
class PUBLIC_DECL RepresentScriptProvider : public CScriptProvider
{
protected:
	typedef CScriptProvider Inherited ;

	RepresentScriptProvider( IPMUnknown* boss ) ;
	virtual ~RepresentScriptProvider() ;

	/** Obtain a list of child objects, as specified by the data, that are contained in the parent object. 
		Most subclasses will not need to override this method.
			@param data is the request data. The implementation must call AppendReturnData before returning.
			@param parent is the parent object
	*/
	virtual void		GetObject(			IScriptRequestData* data, IScript* parent ) ;

	/** Obtain a list of child objects, as specified by the data, that are contained in the parent object. 
		Most subclasses will not need to override these methods. 
			@param data is the request data. If the return value is kSuccess, the implementation must call AppendReturnData 
				before returning. If the return value is not kSuccess, the implementation should not call AppendReturnData.
			@param parent is the parent object
			@return kSuccess or an error code
	*/
	virtual ErrorCode	GetObjectByIndex(	IScriptRequestData* data, IScript* parent ) ;
	virtual ErrorCode	GetObjectByName(	IScriptRequestData* data, IScript* parent ) ;
	virtual ErrorCode	GetObjectByID(		IScriptRequestData* data, IScript* parent ) ;
	virtual ErrorCode	GetObjectByRange(	IScriptRequestData* data, IScript* parent ) ;
	virtual ErrorCode	GetObjectPrevious(	IScriptRequestData* data, IScript* parent ) ;
	virtual ErrorCode	GetObjectNext(		IScriptRequestData* data, IScript* parent ) ;
	virtual ErrorCode	GetObjectFirst(		IScriptRequestData* data, IScript* parent ) ;
	virtual ErrorCode	GetObjectLast(		IScriptRequestData* data, IScript* parent ) ;
	virtual ErrorCode	GetObjectMiddle(	IScriptRequestData* data, IScript* parent ) ;
	virtual ErrorCode	GetObjectAny(		IScriptRequestData* data, IScript* parent ) ;
	virtual ErrorCode	GetObjectAll(		IScriptRequestData* data, IScript* parent ) ;
	virtual ErrorCode	GetObjectWhose(		IScriptRequestData* data, IScript* parent ) ;

	/**	Handle the specified method using the provided data for the target object.
		Most subclasses will override this method.
			@param methodID is the request ID
			@param data is the request data. If the return value is kSuccess, the implementation must call AppendReturnData 
				before returning. If the return value is not kSuccess, the implementation should not call AppendReturnData.
			@param script is the target object
			@return kSuccess or an error code
	*/
	virtual ErrorCode	HandleMethod(		ScriptID methodID, IScriptRequestData* data, IScript* script ) ;

	/**	Access the specified property using the provided data for the target object.
		Most subclasses will override this method.
			@param propID is the request ID
			@param data is the request data. If the return value is kSuccess, the implementation must call AppendReturnData 
				before returning. If the return value is not kSuccess, the implementation should not call AppendReturnData.
			@param script is the target object
			@return kSuccess or an error code
	*/
	virtual ErrorCode	AccessProperty(		ScriptID propID, IScriptRequestData* data, IScript* script ) ;

	/**	Get the number of child objects, as specified by the data, that are contained in the parent object.
		All subclasses must override this method.
			@param data is the request data
			@param parent is the parent object
			@return the number of child objects
	*/
	virtual int32		GetNumObjects(		const IScriptRequestData* data, IScript* parent ) = 0 ;

	/**	Append the nth child object, as specified by the data, that is contained in the parent object.
		All subclasses must override this method.
			@param data is the request data
			@param parent is the parent object
			@param n is the index of the child
			@param objectList - the child object should be appended to this list
			@return kSuccess or an error code
	*/
	virtual ErrorCode	AppendNthObject(	const IScriptRequestData* data, IScript* parent, int32 n, ScriptList& objectList ) = 0 ;	//0-based index

	/**	Append all of the child objects, as specified by the data, that are contained in the parent object.
		Some subclasses may want to override this method for performance reasons.
			@param data is the request data
			@param parent is the parent object
			@param objectList - the child objects should be appended to this list. The number of objects appended must 
				equal the value returned by calling GetNumObjects on the same implementation with the same parameters.
			@return kSuccess or an error code. Only return an error code to indicate an exception. If the number of 
				child objects is zero, return kSuccess.
	*/
	virtual ErrorCode	AppendAllObjects(	const IScriptRequestData* data, IScript* parent, ScriptList& objectList ) ;

	/** Obtain a list of child objects, as specified by the data and the whose value for the specified property
			matches the specified value, that are contained in the parent object. 
		Most subclasses will not need to override this method.
			@param data is the request data
			@param parent is the parent object
			@param propID is the property on the child object to match
			@param propData is the value on the child object to match
			@param bFirstMatchOnly indicates whether to return only the first matching child or all matching children
			@param objectList - the child objects should be appended to this list
			@return kSuccess or an error code. Only return an error code to indicate an exception. If the number of 
				matching child objects is zero, return kSuccess.
	*/
	virtual ErrorCode	AppendObjectsWhose(	const IScriptRequestData* data, IScript* parent, ScriptID propID, const ScriptData& propData, bool16 bFirstMatchOnly, ScriptList& objectList ) ;

	/** Return the index of the child object within the list of such child objects that are contained in the parent object. 
		Most subclasses will not need to override this method.
			@param data is the request data
			@param parent is the parent object
			@param script is the child object
			@return the index of the child within all children of the same type on the parent, or -1 if not found
	*/
	virtual int32		GetObjectIndex(		const IScriptRequestData* data, IScript* parent, IScript* script ) ;	//0-based index

	/**	Get the number of child objects, as specified by the data, that are contained in the parent object.
		Most subclasses will not need to override this method.
			@param methodID is the request ID
			@param data is the request data. If the return value is kSuccess, the implementation must call AppendReturnData 
				before returning. If the return value is not kSuccess, the implementation should not call AppendReturnData.
			@param parent is the parent object
			@return kSuccess or an error code
	*/
	virtual ErrorCode	CountObjects(		ScriptID methodID, IScriptRequestData* data, IScript* parent ) ;

	/**	Access the specified property using the provided data for the target object.
		Most subclasses will not need to override these methods.
			@param propID is the request ID
			@param data is the request data. If the return value is kSuccess, the implementation must call AppendReturnData 
				before returning. If the return value is not kSuccess, the implementation should not call AppendReturnData.
			@param script is the target object
			@return kSuccess or an error code
	*/
	virtual ErrorCode	AccessObject(		ScriptID propID, IScriptRequestData* data, IScript* script ) ;
	virtual ErrorCode	AccessID(			ScriptID propID, IScriptRequestData* data, IScript* script ) ;
	virtual ErrorCode	AccessIndex(		ScriptID propID, IScriptRequestData* data, IScript* script ) ;
	virtual ErrorCode	AccessLabel(		ScriptID propID, IScriptRequestData* data, IScript* script ) ;
	virtual ErrorCode	AccessClass(		ScriptID propID, IScriptRequestData* data, IScript* script ) ;
	virtual ErrorCode	AccessPropertiesProperty(	ScriptID propID, IScriptRequestData* data, IScript* script ) ;

	/** Handle the specified method using the provided data for the target object. 
		Most subclasses will not need to override this method.
			@param methodID is the request ID
			@param data is the request data. If the return value is kSuccess, the implementation must call AppendReturnData 
				before returning. If the return value is not kSuccess, the implementation should not call AppendReturnData.
			@param script is the target object
			@return kSuccess or an error code
	*/
	virtual ErrorCode	ExtractLabel(		ScriptID methodID, IScriptRequestData* data, IScript* script ) ;  
	/** Handle the specified method using the provided data for the target object. 
		Most subclasses will not need to override this method.
			@param methodID is the request ID
			@param data is the request data. The implementation should not call AppendReturnData.
			@param script is the target object
			@return kSuccess or an error code
	*/
	virtual ErrorCode	InsertLabel(		ScriptID methodID, IScriptRequestData* data, IScript* script ) ;

	/** A utility to extract an index from accessor data supplied for a GetObject request.
			@param data is the request data
			@param parent is the parent object
			@param accessorData is the client-supplied accessor data from which to extract an index
			@param index is used to return the result
			@return kSuccess or an error code
	*/
			ErrorCode	GetIndex(			const IScriptRequestData* data, IScript* parent, const ScriptData& accessorData, int32& index ) ;
};

#pragma export reset

#endif
