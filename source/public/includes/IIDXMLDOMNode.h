//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/IIDXMLDOMNode.h $
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

#ifndef __IIDXMLDOMNode_h__
#define __IIDXMLDOMNode_h__

class ISAXServices;
class IIDXMLDOMNamedNodeMap;
class IIDXMLDOMNList;
class IIDXMLDOMDocument;

// Forward declare this in the proper namespace
namespace BIB_NAMESPACE {
	class CAXENodeDOM;
}

/**
DOM Node

Conceptually, a DOM Node is any type of object in a DOM
Tree rather than just an element. This includes (elements,
attributes, processing instructions, comments, text, etc)

<b>Memory Management</b>

Unless otherwise stated pointers returned by methods in
this class are owned by the class and not the client.
Exceptions to this rule will be stated clearly where
they apply.

<b>Invalid Parameters</b>

Unless otherwise indicated, it is an error to use an invalid
container (IsValid() == false), or a NULL pointer, as a
parameter to any function. In some instances, the requirement
that a specific parameter must be valid is repeated in the
commentary for the specific function. The lack of any
indication in the commentary for the specific function should
still be taken to mean that an invalid container or NULL
pointer will result in a kAXEErrClientFault exception.
*/
class IIDXMLDOMNode
{
public:
	/** Supported Node Types */
	typedef enum {
		/** Element type */
		kElement, 
		/** Document type */
		kDocument, 
		/** Simple Characters */
		kText, 
		/** Processing Instruction */
		kProcessingInstruction, 
		/** Attribute */
		kAttribute, 
		/** Comment */
		kComment, 
		/** Type not supported */
		kUnknown} kNodeTypes;

	virtual ~IIDXMLDOMNode() {}
	
        /**
        Clone a node and optionally clone its descendants

        The returned node has no parent (parentNode is null), 
		with the expectation that the client will insert it 
		somewhere in the current document's tree. The source 
		node is not altered or removed from the document; this 
		method creates a new copy of the source node. For all 
		nodes, cloning a node creates a node object owned by 
		the owning document, with DOM IDL attribute values 
		identical to the source node's nodeName and nodeType, 
		plus the DOM IDL attributes related to namespaces 
		(prefix and namespaces URI).

        See the W3C DOM specification for the details on how
        each of the node types is handled during import.

		Note: You own the pointer to this node and must either
		insert it into the document or delete it yourself.

        <b>DOM Level 2</b>

        @param deepClone		If 'kTrue', recursively clone the
                                subtree under the specified node; if
                                kFalse, clone only the node itself,
                                as explained above. See the
                                W3C DOM specification for a
                                detailed discussion of the clone
                                and relevance of the 'deepClone' parameter
                                on various node types.

        @return                 The cloned node that belongs to
                                the same document as this node.
        */
	virtual IIDXMLDOMNode *CloneNode(bool deepClone) = 0;

	/** 
	Is Valid
	Is this node in a valid state

	@return kTrue - Valid, kFalse - Invalid
	*/
	virtual bool16 IsValid() const = 0;

    /**
    Node type

    Get the node type. To allow for possible additions in the
    future, the type is an integer value, selected from
    the constants enumerated as kNodeTypes.

    @return                 Node type code.

    @see kNodeTypes
    */
	virtual IIDXMLDOMNode::kNodeTypes GetNodeType() const = 0;

	/**
	Local part of qualified name

	Get the local part of the qualified name given to this
	node. Not all node types can have a qualified name.
	If no qualification was ever specified, this
	function returns false.  The prefix and local part
	of a qualified name are always stored separately,
	though the combined qualified name is available
	through GetNodeName.

	@param localName        An output parameter that is assigned
							with the local part of the qualified
							name if it exists, otherwise it
							is left unchanged.

	@return                 'kTrue' if a local part was specified,
							'kFalse' otherwise, also 'kFalse' if
							this node type cannot have a
							qualified name.

	@see #GetNamespaceURI
	@see #GetPrefix
	*/
	virtual bool16 GetLocalName(WideString& localName) const = 0;

    /**
    Namespace URI

    <b>WARNING:</b>
    This is not a computed value that is the result of a
    namespace lookup based on an examination of the namespace
    declarations in scope. It is merely the namespace URI given
    at creation time.

    For nodes of any type other than kElement and
    kAttribute and nodes created with a DOM Level 1
    method, such as CreateElement from the IIDXMLDOMDocument
    interface, this always returns false.

    @param namespaceURI     An output parameter that is assigned
                            with the namespace URI if it exists,
                            otherwise it is left unchanged.

    @return                 'kTrue' if a namespace URI was
                            defined, 'kFalse' otherwise.
    */
	virtual bool16 GetNamespaceURI(WideString& namespaceURI) const = 0;

    /**
    Node name

    Get the node name. Not all node types have names. Comments will
	have names and the target of a PI is given
	by the name property

    @param name             An output parameter that is assigned
                            the node name if this function
                            returns 'true', left unchanged
                            otherwise. 

    @return                 'true' if this node type has a name,
                            'false' otherwise.
    */
	virtual bool16 GetNodeName(WideString& name) const = 0;
	
    /**
    Node value

    Get the node value. Not all node types have values. Comments
	will have their data stored in the value.

    @param val              An output parameter that is assigned
                            the node value if this function
                            returns 'true', left unchanged
                            otherwise.

    @return                 'true' if this node type has a value,
                            'false' otherwise.
    */
	virtual bool16 GetNodeValue(WideString& value) const = 0;

    /**
    Set node value

    Any node which can have a nodeValue (@see #GetNodeValue) will
    also accept requests to set it to a string. The exact
    response to this varies from node to node.

    For most types of node, value is null and attempting to set
    it will result in an error. This will also be the result if the
    node is read-only.

    @param val              The value to set the node to.
    */
	virtual void SetNodeValue(const WideString& val) = 0;

    /**
    Prefix of qualified name

    Get the prefix of the qualified name given to this
    node. Not all node types can have a qualified name.
    If no qualification was ever specified, this
    function returns false.  The prefix and local part
    of a qualified name are always stored separately,
    though the combined qualified name is available
    through GetNodeName.

    @param prefix           An output parameter that is assigned
                            with the prefix of the qualified
                            name if it exists, otherwise it
                            is left unchanged.

    @return                 'kTrue' if a prefix was specified,
                            'kFalse' otherwise, also 'kFalse' if
                            this node type cannot have a
                            qualified name.

    @see #GetLocalName
    @see #GetNamespaceURI
    */
	virtual bool16 GetPrefix(WideString& prefix) const = 0;

    /**
    Set prefix of qualified name

    Note that setting this attribute, when permitted, changes the
    nodeName attribute, which holds the qualified name, as well
    as the tagName and name attributes of the an element or 
	attribute interface, when applicable.

    @param prefix           The prefix to set.
    */
	virtual void SetPrefix(const WideString& prefix) = 0;
	
	/**
    Get attributes

    Get attributes from a kElement node. For any
    other type of node this function returns nil.

    @return                 The map of attributes
                            for this element. If there are
                            no attributes on this element,
                            the length will be 0.  If this
                            is not an element node, return
							will be nil.
    */
	virtual IIDXMLDOMNamedNodeMap *GetAttributes() const = 0;
	
    /**
    Node has children?

    This is a convenience method to allow easy determination of
    whether a node has any children.

    @return                 true if the node has any children,
                            false if the node has no children.

    @see #GetChildNodes
    */
	virtual bool16 HasChildNodes() const = 0;
	
	/**
	List of child nodes

	If there are no children, this is a node list containing no
	nodes. The content of the returned node list is "live" in the
	sense that, for instance, changes to the children of the node
	object that it was created from are immediately reflected in
	the nodes returned by the node list accessors; it is not a
	static snapshot of the content of the node.

	For node types that do not have children, a list of
	zero length is returned.  Note that a zero length node
	list will not keep the DOM tree alive if all other references
	to that tree are destroyed.

	@return                 Node list of children, which may
							have a length of 0.
	*/
	virtual IIDXMLDOMNList *GetChildNodes() const = 0;

    /**
    First child node

    Get the first child node.  Not all node types have
    children.

    @return                 The first child under this node if
							there is one. Otherwise nil.
    */
	virtual IIDXMLDOMNode *GetFirstChild() const = 0;

    /**
    Last child node

    Get the last child node.  Not all node types have
    children.

    @return                 The last child under this node if
							there is one. Otherwise nil.
    */
	virtual IIDXMLDOMNode *GetLastChild() const = 0;
	
    /**
    Next sibling node

    Get the sibling that follows this one in document order.
    Not all node types have siblings.

    @return                 The first child after this node if
							there is one. Otherwise nil.
    */
	virtual IIDXMLDOMNode *GetNextSibling() const = 0;

    /**
    Previous sibling node

    Get the sibling that preceeds this one in document order.
    Not all node types have siblings.

    @return                 The first child before this node if
							there is one. Otherwise nil.
    */
	virtual IIDXMLDOMNode *GetPreviousSibling() const = 0;
	
    /**
    Parent node

    All nodes, except kDocument and kAttribute
    may have a parent. However, if a node has just
    been created and not yet added to the tree, 
	or if it has been removed from the tree, nil 
	is returned.

    @return                 The parent node if there 
							is one. Otherwise nil.
    */
	virtual IIDXMLDOMNode *GetParentNode() const = 0;

    /*
    Owner document

    Get the owner document for this node. This is also the
    CAXEDocumentDOM object used to create new nodes. When this
    node is a CAXEDocumentDOM or a CAXEDocTypeDOM which is not
    used with any document yet, false is returned.

    @param owner            An output parameter that is assigned
                            with the owner document node, if
                            there is one, otherwise it is left
                            unchanged.

    @return                 'true' if there is an owner document,
                            'false' otherwise.

    */
	virtual IIDXMLDOMDocument *GetOwnerDocument() const = 0;
	
	/**
    Insert node before

    Inserts the node 'newChild' before the existing child node
    'refChild', or at the end of the list of children if refChild
    is nil.

    If newChild is already in the tree, it is first removed.

    @param newChild         The node to insert. It must be a
                            node owned by the same document
                            as this node.

    @param refChild         The reference node, i.e., the node
                            before which the new node must be
                            inserted. May be invalid.
                            If not invalid, must be a current
                            child of this node.
    */
	virtual void InsertBefore(IIDXMLDOMNode* newNode, IIDXMLDOMNode* whichNode) = 0;

    /**
    Append child node

    Adds the node 'newChild' to the end of the list of children
    of this node.

    If the 'newChild' is already in the tree, it is
    first removed.

    @param newChild         The node to add.  It must be a
                            node owned by the same document
                            as this node.

    @see #insertBefore
    @see IIDXMLDOMCDocument::ImportNode
    */
	virtual void AppendChild(IIDXMLDOMNode *newChild) = 0;

    /**
    Replace child node

    Replaces the child node 'oldChild' with 'newChild' in the
    list of children.

    If the newChild is already in the tree, it is
    first removed.

    @param newChild         The new node to put in the child
                            list. It must be a node owned by
                            the same document as this node.

    @param oldChild         The node being replaced in the list.
                            Must be a current child of this node.
    */
	virtual void ReplaceChild(IIDXMLDOMNode *newChild, IIDXMLDOMNode *oldChild) = 0;

	/*
	Remove child node
	
	Removes the child node from the list of children
	
	@param oldChild			Child node to remove from child list
	
	@return					The node removed
	*/
	virtual IIDXMLDOMNode *RemoveChild(IIDXMLDOMNode* oldChild) = 0;

    /**
    For internal use only.
    */
	virtual BIB_NAMESPACE::CAXENodeDOM GetAXEObject() = 0;
};

#endif