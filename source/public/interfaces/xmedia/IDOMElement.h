//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IDOMElement.h $
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
#ifndef __IDOMElement_h__
#define __IDOMElement_h__

// Adobe Patent or Adobe Patent Pending Invention Included Within this File
// Adobe patent application tracking B234, entitled Method and apparatus for formatting portion of content, inventors: Craig Rainwater, Steve Pellegrin,  Robin Briggs 

// ----- Interfaces -----

#include "IPMUnknown.h"

// ----- Includes -----

#include "K2Vector.h"
#include "KeyValuePair.h"
#include <adobe/vector.hpp>

// ----- ID.h files -----

#include "INXCoreID.h"

class WideString;
class DOMAttributeValue;

/**
	Represents a node in the DOM used to import and export InDesign documents as XML.

	A particular node can be thought of as the root of a tree that defines either
	an entire document, or a portion of a document (such as a Story).

	Since DOM elements cache information during use, it is best to call the Reset()
	method on the topmost node when you are finished working with the DOM. This method
	will recursively reset all nodes beneath it.

	This interface is intened to be used under INX context (both import and export).
	If you use this interface outside of INX context, result is not predictable. You may
	crash or get wrong return value.
*/


#define kInvalidDOMElementID		((IDOMElement::DOMElementID)kInvalidScriptID)
#define kInvalidDOMAttributeID		((IDOMElement::DOMAttributeID)kInvalidScriptID)

#define kSelfAttributeID			((IDOMElement::DOMAttributeID)'Self')
#define kSelfAttributeName			IDOMElement::DOMElementName(L"Self")

#define kPICharAttributeName		IDOMElement::DOMElementName(L"Char")
 
class IDOMElement : public IPMUnknown
{
public:
	typedef object_type data_type;

	enum { kDefaultIID = IID_IDOMELEMENT };

	typedef ScriptID											DOMElementID;
	typedef WideString											DOMElementName;
	typedef ScriptID											DOMAttributeID;
	typedef WideString											DOMAttributeName;
	typedef KeyValuePair<DOMAttributeID, DOMAttributeValue>		AttributeIDValuePair;
	typedef K2Vector<InterfacePtr<IDOMElement> >				ElementList;
	typedef K2Vector<DOMElementID>								ElementIDList;
	typedef adobe::vector<AttributeIDValuePair>					AttributeList;
	typedef K2Vector<DOMAttributeID>							AttributeIDList;

	typedef enum {kTextContent, kBreakContent, kNonContent}		ContentType;

public:
/**
   Releases all cached resources held by the node and all nodes beneath it.
 */
	virtual void Reset() = 0;

/**
   Returns the ID of the node.
   @return The node ID.
 */
	virtual DOMElementID GetElementID() const = 0;

/**
   Returns the name of the node.
   @return The node name.
 */
	virtual DOMElementName GetElementName() const = 0;
	
/**
	Determines if two IDOMElement pointers reference the same Element.
	@return kTrue if the Elements are the same, kFalse if not.
 */
 	virtual bool16 IsSameElement(IDOMElement *other) const = 0;

/**
   Returns a pointer to the node's parent. The parent's reference count is incremented.
   @return A pointer to the parent node.
 */
	virtual IDOMElement * QueryParent() const = 0;

/**
   Tests to see whether the node has an attribute of the specified ID.
   @param id IN The attribute ID.
   @return kTrue if the attribute exists, kFalse if not.
 */
	virtual bool16 HasAttribute(const DOMAttributeID id) = 0;

/**
   Tests to see whether the attribute is read-only.
   @param id IN The attribute ID.
   @return kTrue if the attribute is read-only, kFalse if not.
 */
	virtual bool16 IsAttributeReadOnly(const DOMAttributeID id) = 0;

/**
   Returns a list of the IDs of all of the node's attributes.
   @param ids IN A reference to the list to be filled with the attribute IDs.
   @return The number of attributes in the list.
 */
	virtual int32 GetAttributeIDs(AttributeIDList &ids) = 0;

/**
   Returns the current value of the specified attribute.
   @param id IN The attribute ID.
   @param value OUT A reference to an object that will hold the value.
   @return kTrue if the value was returned, kFalse if the value could not be obtained.
 */
	virtual bool16 GetAttribute(const DOMAttributeID id, DOMAttributeValue &value) = 0;

	/**
	   Returns the IDs and current values of node's attributes specified in ID list.
	   @param idList IN The list which contains the IDs of attribute we want to collect.
	   @param attributes OUT A reference to a list that will contain the attributes.
	   @return The number of attributes returned in the list.
	*/
	virtual int32 GetMultipleAttributes(const AttributeIDList & idList, AttributeList & attributes) = 0;

/**
   Returns the IDs and current values of all of the node's attributes.
   @param attributes OUT A reference to a list that will contain the attributes.
   @return The number of attributes returned in the list.
 */
	virtual int32 GetAttributes(AttributeList &attributes) = 0;

/**
   Sets the value of the specified attribute.
   @param id IN The attribute ID.
   @param value IN A const reference to an object that holds the new value.
   @return kTrue if the value was set, kFalse if the value could not be set.
 */
	virtual bool16 SetAttribute(const DOMAttributeID id, const DOMAttributeValue &value) = 0;

/**
   Sets the values of one or more of the node's attributes.
   @param attributes IN A const reference to a list that contains the attribute IDs and values.
   @return kTrue if at least one value was set, kFalse if none of the values could be set.
 */
	virtual bool16 SetAttributes(const AttributeList &attributes) = 0;

/**
   Returns a list of all of the node's children.
   @param children OUT A reference to the list that will contain the children.
          Note that current contents of the caller's list are REPLACED.
   @return The number of children returned in the list.
 */
	virtual int32 GetChildElements(ElementList &children) = 0;

	/**
	   Returns a list of all of the node's children of childType.
	   @param children IN The type of child element to get.
	   @param children OUT A reference to the list that will contain the children.
	   @param children IN flag to indicate whether or not also collect subtypes.
			  Note that current contents of the caller's list are REPLACED.
	   @return The number of children returned in the list.
	 */
	virtual int32 GetSpecificChildElements(DOMElementID childType, ElementList &children, bool includeSubtypes = kFalse) = 0;

/**
   Creates a new child element.
   @param type IN The type of child to create ("Color", "XMLElement", etc.).
   @param attributes IN A const reference to a list that contains the attribute IDs and values.
   @return A pointer to the newly created child, or nil if the child could not be created.
 */
	virtual IDOMElement * CreateChildElement(DOMElementID type, const AttributeList &attributes) = 0;

/**
   Delete a child element.
   @param child IN A pointer to the child element.
   @return kTrue if the child was deleted, kFalse if not.
 */
	virtual bool16 DeleteChildElement(IDOMElement *child) = 0;

/**
   Delete one or more child elements.
   @param children IN A const reference to the list of children to delete.
   @return kTrue if at least one child was deleted, kFalse if none of the children could be deleted.
 */
	virtual bool16 DeleteChildElements(const ElementList &children) = 0;

/**
	Set this flag put element in special state. When flag is set to kTrue, element won't retrieve child
	and attribute information from underline system. Element will only return children and attributes in 
	its cache. Flag is initialized to kFalse. Calling Reset also set this flag to kFalse.
	@param flag IN Do not discover resource flag
*/
	virtual void SetDontDiscoverResource(bool16 flag) = 0;

/**
	Retrieve do not discover resource flag.
	@return do not discover resource flag, kTrue or kFalse
*/
	virtual bool16 GetDontDiscoverResource() const = 0;

/**
   Add an element to its cached child list.
   @param child IN A pointer to the child element that should be added.
   @return kTrue if the child was added, kFalse if it was already a child of the parent.
 */
	virtual bool16 AddChildElement(IDOMElement * child) = 0;

/**
   Remove a child element from its cached child list. Note: The child is NOT destroyed.
   @param child IN A pointer to the child element that should be removed.
   @return kTrue if the child was removed, kFalse if it was not found in the parent.
 */
	virtual bool16 RemoveChildElement(IDOMElement * child) = 0;

/**
   Add an attribute to its cached attribute list.
   @param id IN The attribute ID.
   @param value IN A reference to DOMAttributeValue that will hold the attribute value.
   @return kTrue if the attribute was added, kFalse if it already has this attribute.
 */
	virtual bool16 AddAttribute(const DOMAttributeID id, const DOMAttributeValue &value) = 0;

/**
   Remove an attribute from its cached attribute list.
   @param id IN The attribute ID.
   @return kTrue if the attribute was removed, kFalse if it was not found on this element.
 */
	virtual bool16 RemoveAttribute(const DOMAttributeID id) = 0;

/**
   A special form of SetAttributes used during object creation.
   Should only be used during object creation. Other clients should use SetAttributes instead.
   @param attributes IN A const reference to a list that contains the attribute IDs and values.
   @param checkForSpecialObjects IN kTrue to handle properties in an object-type-specific way. kFalse to just set them with no extra checking.
   @return kTrue if at least one value was set, kFalse if none of the values could be set.
 */
	virtual bool16 InitializeAttributes(const IDOMElement::AttributeList &attributes, bool16 checkForSpecialObjects = kTrue) = 0;

/**
   Ask the element if it has content children
   @return kTrue if the element has children that contain content
 */
	virtual bool16 HasContentChildren() = 0;

/**
	Used in IDML (INX-Alt) to add text content and break children to a text object for output
	@param type, IN Type of content child to add
	@param content, IN Text content or string indicating type of break
*/
	virtual void AddContent(ContentType type, WideString& content) = 0;

};

#endif	// __IDOMElement_h__
