//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IScriptInfoManager.h $
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
#ifndef __IScriptInfoManager__
#define __IScriptInfoManager__

#include "IPMUnknown.h"
#include "ScriptingID.h"

#include "ScriptInfo.h"

using namespace ScriptInfo ;

/**
	Manages information about elements in the scripting DOM.
*/
class IScriptInfoManager : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISCRIPTINFOMANAGER };

	/**
		Get the request context
	*/
	virtual const RequestContext&			GetRequestContext() const = 0 ;

	/**
		Find a script element
	*/
	virtual const TypeDefScriptElement*		FindTypeDef(	const ScriptElementID& id ) const = 0 ;
	virtual const SuiteScriptElement*		FindSuite(		const ScriptElementID& id ) const = 0 ;
	virtual const ObjectScriptElement*		FindObject(		const ScriptElementID& id ) const = 0 ;
	virtual const MethodScriptElement*		FindMethod(		const ScriptElementID& id ) const = 0 ;
	virtual const PropertyScriptElement*	FindProperty(	const ScriptElementID& id ) const = 0 ;
	virtual const EventScriptElement*		FindEvent(		const ScriptElementID& id ) const = 0 ;
	virtual const EnumScriptElement*		FindEnum(		const ScriptElementID& id ) const = 0 ;

	virtual const TypeDefScriptElement*		FindTypeDef(	const ScriptID& id ) const = 0 ;
	virtual const SuiteScriptElement*		FindSuite(		const ScriptID& id ) const = 0 ;
	virtual const ObjectScriptElement*		FindObject(		const ScriptID& id ) const = 0 ;
	virtual const ObjectScriptElement*		FindCollection(	const ScriptID& id ) const = 0 ;
	virtual const EventScriptElement*		FindEvent(		const ScriptID& id ) const = 0 ;
	virtual const EnumScriptElement*		FindEnum(		const ScriptID& id ) const = 0 ;
#ifdef DEBUG
private:
	virtual const MethodScriptElement*		FindMethod(		const ScriptID& id ) const = 0 ;	//Not allowed; ScriptID is not unique across all methods
	virtual const PropertyScriptElement*	FindProperty(	const ScriptID& id ) const = 0 ;	//Not allowed; ScriptID is not unique across all properties
public:
#endif

	/**
		Find the an element
		@param name is the name of the element
		@param as indicates how the name is formatted
	*/
	virtual const TypeDefScriptElement*		FindTypeDef(	const PMString& name, ScriptElementType as = kTypeDefElement ) const = 0 ;
	virtual const SuiteScriptElement*		FindSuite(		const PMString& name, ScriptElementType as = kSuiteElement ) const = 0 ;
	virtual const ObjectScriptElement*		FindObject(		const PMString& name, ScriptElementType as = kObjectElement ) const = 0 ;
	virtual const EventScriptElement*		FindEvent(		const PMString& name, ScriptElementType as = kEventElement ) const = 0 ;
	virtual const EnumScriptElement*		FindEnum(		const PMString& name, ScriptElementType as = kEnumElement ) const = 0 ;
	//Name is not unique across Methods and Properties, so we can't find a ScriptElement, but we can find the matching ScriptID
	virtual		  ScriptID					FindMethod(		const PMString& name, ScriptElementType as = kMethodElement ) const = 0 ;
	virtual		  ScriptID					FindProperty(	const PMString& name, ScriptElementType as = kPropertyElement ) const = 0 ;
	virtual		  ScriptID					FindEnumValue(	const PMString& name, ScriptElementType as = kEnumValueElement ) const = 0 ;

	/**
		Find the name of an element
		@param id is the id of the element
		@param as indicates how to format the name
	*/
	virtual		  PMString					FindTypeDefName(	const ScriptID& id, ScriptElementType as = kTypeDefElement ) const = 0 ;
	virtual		  PMString					FindSuiteName(		const ScriptID& id, ScriptElementType as = kSuiteElement ) const = 0 ;
	virtual		  PMString					FindObjectName(		const ScriptID& id, ScriptElementType as = kObjectElement ) const = 0 ;
	virtual		  PMString					FindCollectionName(	const ScriptID& id, ScriptElementType as = kObjectElement ) const = 0 ;
	virtual		  PMString					FindPropertyName(	const ScriptID& id, ScriptElementType as = kPropertyElement ) const = 0 ;
	virtual		  PMString					FindMethodName(		const ScriptID& id, ScriptElementType as = kMethodElement ) const = 0 ;
	virtual		  PMString					FindEventName(		const ScriptID& id, ScriptElementType as = kEventElement ) const = 0 ;
	virtual		  PMString					FindEnumName(		const ScriptID& id, ScriptElementType as = kEnumElement ) const = 0 ;
	virtual		  PMString					FindEnumValueName(	const ScriptID& id, ScriptElementType as = kEnumValueElement ) const = 0 ;

	/**
		Find the properties associated with an attribute id
		@param attributeID is the id of the attribute
		@return the list of elements (may be empty)
	*/
	virtual		  PropertyElementIterator	FindProperties(	const ClassID& attributeID ) const = 0 ;

	/**
		Iterate all script elements
	*/
	virtual TypeDefElementIterator		TypeDefs() const = 0 ;
	virtual SuiteElementIterator		Suites() const = 0 ;
	virtual ObjectElementIterator		Objects() const = 0 ;
	virtual MethodElementIterator		Methods() const = 0 ;
	virtual PropertyElementIterator		Properties() const = 0 ;
	virtual EventElementIterator		Events() const = 0 ;
	virtual EnumElementIterator			Enums() const = 0 ;

	//------------------- Utilities ------------------------------------------------------

	/** Obtain information about a type */
	virtual bool16			IsValidType(	const TypeInfo& ti ) const = 0 ;
	virtual bool16			IsBaseType(		const TypeInfo& ti ) const = 0 ;
	virtual bool16			IsObjectType(	const TypeInfo& ti ) const = 0 ;
	virtual bool16			IsEnumType(		const TypeInfo& ti ) const = 0 ;
	virtual bool16			IsTypeDef(		const TypeInfo& ti ) const = 0 ;
	virtual bool16			IsArrayType(	const TypeInfo& ti ) const = 0 ;
	virtual bool16			IsVariableType(	const TypeInfo& ti ) const = 0 ;
	virtual bool16			IsStructType(	const TypeInfo& ti ) const = 0 ;
	virtual bool16			IsRecordType(	const TypeInfo& ti ) const = 0 ;
} ;

#endif	// __IScriptInfoManager__
