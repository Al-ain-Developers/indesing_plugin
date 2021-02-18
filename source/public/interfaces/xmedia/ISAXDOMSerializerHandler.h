//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/ISAXDOMSerializerHandler.h $
//  
//  Owner: Lin Xia
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
//  
//  Wrapper for HAXEContentHandlerBase.  Receives notification of general document events.
//  
//========================================================================================

#pragma once
#ifndef __ISAXDOMSerializerHandler_h__
#define __ISAXDOMSerializerHandler_h__

#include "IPMUnknown.h"
#include "XMLParserID.h"

class IIDXMLDOMNode;
class ISAXDOMSerializerServices;
class ISAXAttributeList;

        /**
        This interface provides an InDesign friendly interface to 
        the AXE (xerces) DOM serializer handler. It receives 
        notification of document events as an AXE DOM is traversed.
        This interface is based upon ISAXContentHandler but is a 
        subset of that interface.
        @see ISAXContentHandler

        This interface provides the contents of an AXE DOM in an 
        ordered series of events. The client can put that information 
        to use in a variety of ways such as serializing the contents 
        to disk or incorporating the contents into their own document 
        structure.

        The order of events in this interface is very important
        because it mirrors the order of information in the document
        itself. For example, all of an element's content (character
        data, processing instructions, and/or subelements) will
        appear, in order, between the startElement event and the
        corresponding endElement event.

        A pointer to IIDXMLDOMNode is supplied to pertinent
        methods so that an application can obtain any attached private
        client data. 

        Important: This handler can be used with a single DOM traversal
        only. A new handler should be constructed for such traversal.
        */
class ISAXDOMSerializerHandler : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISAXDOMSERIALIZERHANDLER };

        /**
     	Register this handler to handle specific elements, attributes,
     	and processing instructions.
     	
     	When combined with a service provider implementation SAXDOMSerializerServices will call
     	your Register method to allow the serializer handler to specify which elements,
     	attributes, and/or processing instructions it is interested in handling.
     	Registration is accomplished by calling RegisterElementHandler,
     	RegisterAttributeHandler, and RegisterPIHandler.

        @param saxServices	The instance of ISAXDOMSerializerServices instantiated for this DOM serialization.
		@param importer		The instance of XMLImporter being used for this DOM serialization. The 
							Handler needs to be able to get to the IMatchRecorder and IXMLImporterDOM
							from the interface passed in here.
        */
	virtual void Register(ISAXDOMSerializerServices* saxServices, IPMUnknown *importer = nil) = 0;

        /**
         Receives character data

        This method is called to report each chunk of character data.  
        Contiguous character data is reported in a single chunk, or it
        may be split it into several chunks. But all characters in any 
        single event must come from the same external entity.

        The ignorableWhitespace() method is not implemented on this 
        interface so all character data in the AXE DOM will be reported
        by this method.
		
        @param chars            The characters from the XML document.

        @param currentNode      The node that contained this data. It is
                                only passed for access to any private
                                client data.
        */
	virtual void Characters(const WideString& chars, IIDXMLDOMNode* currentNode) = 0;

        /**
        Receive the beginning of document notification

        This method will be invoked once before other methods in this 
        interface.

        <b>NOTE</b>:
        Do NOT throw exceptions from this function.

        @param saxServices		The instance of ISAXDOMSerializerServices instantiated for this DOM serialization.
        */
	virtual void StartDocument(ISAXDOMSerializerServices* saxServices) = 0;

        /**
        Receive end of document notification

        This method only once and it will be the last method invoked 
        during the traversal.

        */
	virtual void EndDocument() = 0;

        /**
        Receive the beginning of element notification

        This method will be invoked at the beginning of every element 
        in the XML document; there will be a corresponding endElement() 
        event for every startElement() event (even when the element is 
        empty). All of the element's content will be reported, in order, 
        before the corresponding endElement() event.

        Note that the attribute list provided will contain only 
        attributes with explicit values (specified or defaulted): 
        #IMPLIED attributes will be omitted.

        @param uri          The URI of the associated namespace
                            for this element

        @param localname    The local part of the element name

        @param qname        The QName of this element

        @param attrList     The attributes attached to the element,
                            if any.

        @param currentNode  The node that contained this data. It is
                            passed for access to the attribute value
                            tree so that a client can determine if any
                            entities were used to construct the attribute
                            value. It can also be used to retrieve any 
                            private client data.

        @see #EndElement
        @see ISAXAttributeList
        */
	virtual void StartElement(const WideString& uri, const WideString& localname,
								const WideString& qname, ISAXAttributeList* attrList, IIDXMLDOMNode* currentNode) = 0;

        /**
        Receive end of element notification

        This method will be invoked at the end of every element in the 
        XML document; there will be a corresponding startElement() 
        event for every endElement() event (even when the element is 
        empty).

        @param uri          The URI of the associated namespace for
                            this element

        @param localname    The local part of the element name

        @param qname        The QName of this element

        @param currentNode  The same node passed to startElement.
        */
	virtual void EndElement(const WideString& uri, const WideString& localname, const WideString& qname, IIDXMLDOMNode* currentNode) = 0;

        /**
     	When this handler is registered to handle an element with a specific tagname, 
     	the handler can decide if it wants to handle any subelements of that element
     	that don't have a handler for themselves.  If true is returned, any elements that 
     	are child elements without their own ISAXContentHandler will cause StartElement()
     	to be called on this handler. If, however, false is returned, next handler on the
     	stack will be called with HandlesSubElements() until one returns tru or we get to the 
     	default handler.
     	
        @return true if this handler will handle subelements, false if doesn't handle subelements
        */
	virtual bool16 HandlesSubElements() const = 0;

        /**
        Receive start of namespace prefix mapping notification

        By default, do nothing.  Application writers may override
        this method in a subclass to take specific actions at the
        start of each namespace prefix mapping.

        @param prefix       The namespace prefix used

        @param uri          The namespace URI used.
        */
	virtual void StartPrefixMapping(const WideString& prefix, const WideString& uri) = 0;

        /**
        Receive end of namespace prefix mapping notification

        By default, do nothing.  Application writers may override
        this method in a subclass to take specific actions at the end
        of each namespace prefix mapping.

        @param prefix       The namespace prefix used
        */
	virtual void EndPrefixMapping(const WideString& prefix) = 0;

        /**
		Receive a processing instruction

        This method will be invoked once for each processing 
        instruction found: note that processing instructions may occur 
        before or after the root element.

        @param target       The processing instruction target

        @param data         The processing instruction data, or null
                            if none was supplied

        @param currentNode  The node that contained this data. It is
                            only passed for access to any private
                            client data.
        */
	virtual void ProcessingInstruction(const WideString& target, const WideString& data, IIDXMLDOMNode* currentNode) = 0;

        /**
        (Extension) Receive a comment

        This method will be invoked when the traveral encounters
        a comment.

        @param comment      The interior text of the comment.

        @param currentNode  The node that contained this data. It is
                            only passed for access to any private
                            client data.
        */
	virtual void ExtComment(const WideString& comment, IIDXMLDOMNode* currentNode) = 0;
};

#endif