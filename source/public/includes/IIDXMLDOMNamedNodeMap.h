//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/IIDXMLDOMNamedNodeMap.h $
//  
//  Owner: Ryan Gano
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

#ifndef __IIDXMLDOMNamedNodeMap_h__
#define __IIDXMLDOMNamedNodeMap_h__

class IIDXMLDOMNode;
class ISAXServices;

// Forward declare this in the proper namespace
namespace BIB_NAMESPACE {
	class CAXENamedNodeMapDOM;
}

/**
A map of named nodes

IIDXMLDOMNamedNodeMaps are used to
represent collections of nodes that can be accessed by
name.

Note that IIDXMLDOMNamedNodeMap does not inherit from
IIDXMLDOMNList; IIDXMLDOMNamedNodeMaps are not maintained in any
particular order. Nodes contained in a IIDXMLDOMNamedNodeMap
may also be accessed by an ordinal index, but this is simply
to allow convenient enumeration of the contents, and does not
imply that the DOM specifies an order to these Nodes.

<b>Invalid Parameters</b>

Unless otherwise indicated, it is an error to use an invalid
container (IsValid() == false), or a NULL pointer, as a
parameter to any function. In some instances, the requirement
that a specific parameter must be valid is repeated in the
commentary for the specific function. The lack of any
indication in the commentary for the specific function should
still be taken to mean that an invalid container or NULL
pointer will result in an error.
*/
class IIDXMLDOMNamedNodeMap
{
public:

	IIDXMLDOMNamedNodeMap(const BIB_NAMESPACE::CAXENamedNodeMapDOM& /*attributes*/) {}
	virtual ~IIDXMLDOMNamedNodeMap() {}

	/**
	Get number of nodes in list

	The range of valid child node indices is 0 to length-1
	inclusive.

	@return                     Number of nodes
	*/
	virtual int32 Length() const = 0;

	/**
	Returns an item in the map

	If 'which' is greater than or equal to the number of nodes in
	the map, returns nil.

	@param which                   Index into the list, starting
								with 0.

	@return                     Returns a pointer to the specified
								item. Nil is returned if the item
								wasn't found
	*/
	virtual IIDXMLDOMNode *GetNthNode(int32 which) = 0;

	/**
	Get node by name

	@param name                 The nodeName of a node to
								retrieve.

	@return                     Returns a pointer to the specified
								item. Nil is returned if the item
								wasn't found
	*/
	virtual IIDXMLDOMNode *GetNamedItem(const WideString &name) = 0;

	/**
	Get node by local name and namespace URI

    @param namespaceURI         The namespace URI of
                                the node to retrieve.

    @param localName            The local part of the node to
                                retrieve.

	@return                     Returns a pointer to the specified
								item. Nil is returned if the item
								wasn't found
	*/
	virtual IIDXMLDOMNode *GetNamedItemNS(const WideString &namespaceURI, const WideString &localName) = 0;

	/**
	Removes a node specified by name.

	@param name                 The nodeName of a node to remove.

	@return                     The node that was removed. Nil if
								no item was removed
								Caller is responsible for releasing the node.
	*/
	virtual IIDXMLDOMNode *RemoveNamedItem(const WideString &name) = 0;

	/**
	Removes a node specified by local name and namespace URI.

    @param namespaceURI         The namespace URI of
                                the node to remove.

    @param localName            The local part of the node to
                                remove. When this map
                                contains the attributes attached
                                to an element, as returned by the
                                GetAttributes call of the
                                IIDXMLDOMNode interface, if the
                                removed attribute is known to
                                have a default value, an
                                attribute immediately appears
                                containing the default value as
                                well as the corresponding
                                namespace URI, local name, and
                                prefix.

	@return                     The node that was removed. Nil if
								no item was removed.
								Caller is responsible for releasing the node.

	*/
	virtual IIDXMLDOMNode *RemoveNamedItemNS(const WideString &namespaceURI, const WideString &localName) = 0;

	/**
	Adds a node by name

	As the nodeName attribute is used to derive the name which
	the node must be stored under, multiple nodes of certain
	types (those that have a "special" string value) cannot be
	stored as the names would clash. This is seen as preferable
	to allowing nodes to be aliased.

	@param newNode				A node to store in a named node
								map. The node will later be
								accessible using the value of the
								nodeName attribute of the node.
								If a node with that name is
								already present in the map, it is
								replaced by the new one.

	@return                     If the new Node replaces an
								existing node, returns that 
								node otherwise nil is returned
	*/
	virtual IIDXMLDOMNode *SetNamedItem(IIDXMLDOMNode *newNode) = 0;

	/**
	Adds a node by local name and namespace URI

	As the nodeName attribute is used to derive the name which
	the node must be stored under, multiple nodes of certain
	types (those that have a "special" string value) cannot be
	stored as the names would clash. This is seen as preferable
	to allowing nodes to be aliased.

	@param newNode				A node to store in a named node
								map. The node will later be
								accessible using the value of the
								nodeName attribute of the node.
								If a node with that name is
								already present in the map, it is
								replaced by the new one.

	@return                     If the new Node replaces an
								existing node, returns that 
								node otherwise nil is returned
	*/
	virtual IIDXMLDOMNode *SetNamedItemNS(IIDXMLDOMNode *newNode) = 0;
};

#endif