//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IINXInfo.h $
//  
//  Owner: Steve Pellegrin
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
#ifndef __IINXInfo_h__
#define __IINXInfo_h__

// Adobe Patent or Adobe Patent Pending Invention Included Within this File
// Adobe patent application tracking B234, entitled Method and apparatus for formatting portion of content, inventors: Craig Rainwater, Steve Pellegrin,  Robin Briggs 

// ----- Interfaces -----

#include "IDOMElement.h"
//#include "IINXImportPolicy.h"
#include "IScript.h"
#include "IPMUnknown.h"

// ----- Includes -----

#include "DOMAttributeValue.h"
#include "ScriptInfo.h"

// ----- ID.h files -----

#include "INXCoreID.h"

// ----- Forward -----

class WideString;

#define kInvalidMetadataID		((IINXInfo::MetadataID)kInvalidScriptID)

/** Provides information about INX elements and attributes. 
	
	This interface is intened to be used under INX context (both import and export).
	If you use this interface outside of INX context, result is not predictable. You may
	crash or get wrong return value.
*/
class IINXInfo : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IINXINFO };

	enum INXNameStyle
	{
		kINXNameAsFormat,	// decide by INX format style 
		kINXNameLong,		// always get verbose name
		kINXNameShort		// always get short name (INX traditional)
	};

	typedef K2Vector<DOMAttributeValue>					MetadataValueList;
	typedef ScriptID									MetadataID;

public:
	/** Release all cached resources.
	    Should be called when a client is finished using this interface.
	*/
	virtual void Reset() = 0;
	
	// Metadata
	/** Returns metadata associated with a type of DOM element, will use the DOM element's inheritance hierarchy to find any and all matches
	    @param elemID IN The element type.
		@param keyID IN The metadata type.
		@param values OUT The metadata values, if any.
		@return kTrue if values were found, kFalse if not.
		@see INXMetadataDefs.h
	*/
	virtual bool16 GetElementMetadata(IDOMElement::DOMElementID elemID, MetadataID keyID, MetadataValueList &values) const = 0;

	// Metadata
	/** Returns metadata associated with a type of DOM element, searching only that DOM element for associated data.
		@param elemID IN The element type.
		@param keyID IN The metadata type.
		@param value OUT The metadata valuep, if any.
		@return kTrue if values were found, kFalse if not.
		@see INXMetadataDefs.h
	*/
	virtual bool16 GetElementMetadata_ElementOnly(IDOMElement::DOMElementID elemID, MetadataID keyID, DOMAttributeValue &value) const = 0;

	/** Returns metadata associated with a type of DOM attribute.
	    @param elemID IN The element type.
	    @param attrID IN The attribute type.
		@param keyID IN The metadata type.
		@param values OUT The metadata values, if any.
		@return kTrue if values were found, kFalse if not.
		@see INXMetadataDefs.h
	*/
	virtual bool16 GetAttributeMetadata(IDOMElement::DOMElementID elemID, IDOMElement::DOMAttributeID attrID, MetadataID keyID, MetadataValueList &values) const = 0;

	// Name <--> ID
	/** Get the name of a DOM element.
	    @param elemID IN The element type.
	    @param style IN The style of name requested.
		@return The element name. The string will be empty if the element type is unknown.
	*/
	virtual WideString GetElementName(IDOMElement::DOMElementID elemID, INXNameStyle style = kINXNameAsFormat) const = 0;

	/** Get the name of a DOM element.
	    Note: This method is more efficient than the one that uses an element ID.
	    @param elemID IN The element type.
		@return The element name. The string will be empty if the element type is unknown.
	*/
	virtual WideString GetElementName(const ScriptInfo::ObjectScriptElement* pElem) const = 0;

	/** Get the ID of a DOM element.
	    @param name IN The element name.
		@return The element ID. An invalid ID will be returned if the name is unknown.
	*/
	virtual IDOMElement::DOMElementID GetElementID(const WideString &name) const = 0;

	/** Get the ID and object script element of a DOM element. This version is only for new markup language environment (IDML).
	    @param name IN The element name.
		@param elemID OUT The element ID
		@return The ObjectScriptElement *. A null point will be returned if the name is unknown.
	*/
	virtual const ObjectScriptElement * GetElementID(const WideString &name, IDOMElement::DOMElementID &elemID) const = 0;

	/** Get the name of an element's attribute.
	    @param elemID IN The element type.
		@param propID IN The attribute type.
		@return The attribute name. The string will be empty if the attribute is unknown.
	*/
	virtual WideString GetPropertyName(IDOMElement::DOMElementID elemID, IDOMElement::DOMAttributeID propID) const = 0;

	/** Get the ID of an element's attribute.
	    @param elemID IN The element type.
		@param propName IN The attribute name.
		@return The attribute ID. An invalid ID will be returned if the name is unknown.
	*/
	virtual IDOMElement::DOMAttributeID GetPropertyID(IDOMElement::DOMElementID elemID, const WideString &propName) const = 0;

	/** Get the ID of an element's attribute.
	    Note: This method is more efficient than the one that uses an element ID.
	    @param pElem IN The element type.
		@param propName IN The attribute name.
		@return The attribute ID. An invalid ID will be returned if the name is unknown.
	*/
	virtual IDOMElement::DOMAttributeID GetPropertyID(const ScriptInfo::ObjectScriptElement* pElem, const WideString &propName) const = 0;

	/** Get the ID and property script element of an element's attribute. This version is only for new markup language environment (IDML).
	    @param pElem IN The element type.
		@param propName IN The attribute name.
		@param attrID OUT The attribute ID
		@return The PropertyScriptElement *. A null point will be returned if the name is unknown.
	*/
	virtual const PropertyScriptElement * GetPropertyID(const ScriptInfo::ObjectScriptElement* pElem, const WideString &propName, IDOMElement::DOMAttributeID &attrID) const = 0;

	/** Get an enum value's name.
	    @param eValueID IN The enum value ID.
		@return The enum value's name. The string will be empty if the enum value is unknown.
	*/
	virtual WideString GetEnumValueName(ScriptID eValueID) const = 0;

	/** Get an enum value's ID.
	    @param name IN The enum value name.
		@return The enum value ID. An invalid ID will be returned if the name is unknown.
	*/
	virtual ScriptID GetEnumValueID(const WideString &name) const = 0;
		
	// Element info
	/** Determine whether a particular type of element should be ignored when it appears as
	    a child of another type of element.
		@param parentInfo IN The parent element info.
		@param childInfo IN The child element info.
		@return kTrue if the child type should be ignored, kFalse if not.
	*/
	virtual bool16 IsExcludedChild(const ObjectScriptElement* parentInfo, const ObjectScriptElement* childInfo) const = 0;

	/** Determines whether a particular type of element is a subclass of another.
	    @param elemType IN The type to test.
		@param ancestorType IN The ancestor type of interest.
		@return kTrue if the type is a subclass of the ancestor, kFalse if not.
	*/
	virtual bool16 DoesElementInheritFrom(IDOMElement::DOMElementID elemType, IDOMElement::DOMElementID ancestorType) const = 0;

	/** Determine whether an element is a type of preference object.
	    @param element IN The element.
		@return kTrue if it is a preference object, kFalse if not.
	*/
 	virtual bool16 IsPreferenceObject(IDOMElement *element) const = 0;

	/** Access the current request context */
	virtual const EngineContext &GetRequestContext() const = 0;

	/** @return kTrue if INX is active*/
	virtual bool16 IsINXContextActive() const = 0;

	// return kTrue if INX export session in progress
	virtual bool16 IsINXExportSession() const = 0;

	// return kTrue if INX import session in progress
	virtual bool16 IsINXImportSession() const = 0;
};

#endif // __IINXInfo_h__
