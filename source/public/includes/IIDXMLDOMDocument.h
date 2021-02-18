//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/IIDXMLDOMDocument.h $
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

#ifndef __IIDOMXMLDocument_h__
#define __IIDOMXMLDocument_h__

class IIDXMLDOMNode;
class ISAXDOMSerializerHandler;
class ISAXDOMSerializerServices;
class ISAXServices;
class BaseProgressBar;

// Forward declare this in the proper namespace
namespace BIB_NAMESPACE {
	class CAXEDocumentDOM;
}

        /**
        Document Node

        Conceptually, a DOM document node is the root of the document
        tree, and provides the primary access to the document's
        data. The IIDXMLDOMDocument class wraps the CAXEDocumentDOM class 
		which follows the rules specified by the W3C DOM Core Level 2 
		specification.

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
class IIDXMLDOMDocument
{
public:
	virtual ~IIDXMLDOMDocument() {}

	/**
		Returns the document level node. This is one level up from the
		root node because it can contain other items (PIs, comments, etc)

		@return - A pointer to the document node. Nil will be return if the 
				  DocumentDOM is not valid.
	*/
	virtual IIDXMLDOMNode *GetDocumentNode() const = 0;

	/**
		Returns the root node

		@return - A pointer to the root node
	*/
	virtual IIDXMLDOMNode *GetRootNode() const = 0;

        /**
        Import nodes from another document

        Imports a node from another document to this document. The
        returned node has no parent (parentNode is null), with the
        expectation that the client will insert it somewhere in the
        current document's tree. The source node is not altered or
        removed from the original document; this method creates a new
        copy of the source node. For all nodes, importing a node
        creates a node object owned by the importing document, with
        DOM IDL attribute values identical to the source node's
        nodeName and nodeType, plus the DOM IDL attributes related to
        namespaces (prefix and namespaces URI).

        See the W3C DOM specification for the details on how
        each of the node types is handled during import.

        <b>DOM Level 2</b>

        @param toImport         The node to import.

        @param deepImport       If 'kTrue', recursively import the
                                subtree under the specified node; if
                                kFalse, import only the node itself,
                                as explained above. See the
                                W3C DOM specification for a
                                detailed discussion of the impact
                                and relevance of the 'deep' parameter
                                on various node types.

        @return                 The imported node that belongs to
                                this Document.
        */
	virtual IIDXMLDOMNode *ImportNode(IIDXMLDOMNode *toImport, bool16 deepImport) = 0;

        /**
        Create element in namespace

        Create an element with the given qualified name in the
        given namespace. The prefix part of the qualified name is
        assumed to be mapped to the specified namespace.

        The prefix and local name are extracted from the
        'qName'.

		The client owns this pointer you must either pass it to another object
		which will take ownership or delete it yourself

        @param namespaceURI The namespace URI of the attribute

        @param qName        The qualified name of the attribute

        @return             A new IIDXMLDOMNode pointer. Remember you own
							this pointer. You must either delete it or 
							pass it to IIDXMLDOMNode::InsertBefore()

		@see IIDXMLDOMNode
        */
	virtual IIDXMLDOMNode *CreateElementNode(const WideString &namespaceURI, const WideString &qName) = 0;

        /**
        Create a comment

		The client owns this pointer you must either pass it to another object
		which will take ownership or delete it yourself

        @param comment      The text in the comment

        @return             A new IIDXMLDOMNode pointer. Remember you own
							this pointer. You must either delete it or 
							pass it to IIDXMLDOMNode::InsertBefore()

		@see IIDXMLDOMNode
        */
	virtual IIDXMLDOMNode *CreateCommentNode(const WideString &comment) = 0;

        /**
        Create a processing instruction

		The client owns this pointer you must either pass it to another object
		which will take ownership or delete it yourself

        @param target		The target for the PI

        @param value		The value for the PI

        @return             A new IIDXMLDOMNode pointer. Remember you own
							this pointer. You must either delete it or 
							pass it to IIDXMLDOMNode::InsertBefore()

		@see IIDXMLDOMNode
        */
	virtual IIDXMLDOMNode *CreatePINode(const WideString &target, const WideString &value) = 0;

        /**
        Create a text node

		The client owns this pointer you must either pass it to another object
		which will take ownership or delete it yourself

        @param text			The text to be inserted into the DOM

        @return             A new IIDXMLDOMNode pointer. Remember you own
							this pointer. You must either delete it or 
							pass it to IIDXMLDOMNode::InsertBefore()

		@see IIDXMLDOMNode
        */
	virtual IIDXMLDOMNode *CreateTextNode(const WideString &text) = 0;

        /**
        Create attribute in namespace

        Create an attribute with the given qualified name in the
        given namespace. The prefix part of the qualified name is
        assumed to be mapped to the specified namespace.

        The prefix and local name are extracted from the
        'qName'.

		The client owns this pointer you must either pass it to another object
		which will take ownership or delete it yourself

        @param namespaceURI The namespace URI of the attribute

        @param qName        The qualified name of the attribute

        @return             A new IIDXMLDOMNode pointer. Remember you own
							this pointer. You must either delete it or 
							pass it to IIDXMLDOMNode::InsertBefore()

		@see IIDXMLDOMNode
        */
	virtual IIDXMLDOMNode *CreateAttribute(const WideString &namespaceURI, const WideString &qName, const WideString &value) = 0;

		/**
		Get the number of elements in this DOM

		@return				The number of elements in this DOM
		*/
	virtual int32 GetDOMElementCount() const = 0;
	
		/** 
		For internal use only.
		Set the pre-computed number of elements in the DOM. This is an optimization, so
		that when we call GetDOMElementCount, we don't have to iterate through all the 
		nodes counting.
		
		@param elementCount	The number of elements in this DOM
		*/
	virtual void SetDOMElementCount(int32 elementCount) = 0;

	virtual  bool16 operator == (const IIDXMLDOMDocument *other) = 0;

        /**
        Serialize a Document. For internal use only.

        The document DOM will be serialized through a series 
        of SAX-like messages to the client's implementation of the 
        HAXEDOMSerializerHandlerBase class.

        @param owner           The SAXDOMSerializerServices that starts the serialization.

		@param defaultHandler	The default handler to hanlder meesages during the serialization.

		@param progressBar		The progress bar to be checked and updated while serializing the DOM

		@param allowProviders	Specifies whether to search customized handlers before using the default handler.
        */

	virtual void Serialize(ISAXDOMSerializerServices* owner, ISAXDOMSerializerHandler* defaultHandler, BaseProgressBar *progressBar, bool16 allowProviders) = 0;

        /**
        For internal use only.
        */
        
	virtual BIB_NAMESPACE::CAXEDocumentDOM GetAXEObject() = 0;
	virtual void SetAXEObject(BIB_NAMESPACE::CAXEDocumentDOM newObj) = 0;
};

#endif