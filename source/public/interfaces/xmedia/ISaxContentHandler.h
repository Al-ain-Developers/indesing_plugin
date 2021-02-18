//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/ISaxContentHandler.h $
//  
//  Owner: Lonnie Millett
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
#ifndef __ISAXContentHandler_h__
#define __ISAXContentHandler_h__

#include "IPMUnknown.h"
#include "XMLParserID.h"

class ISAXServices;
class ISAXAttributes;
class ISAXLocator;
class IXMLImporter;

        /**
		Wrapper for HAXEContentHandlerBase.  
		Receives notification of general document events.

        This is the main interface that most applications
        implement for parsing of XML files.  It provides 
        an InDesign friendly interface to the AXE (xerces)
        XML parser. If the application needs to be informed
        of basic parsing events, it provides an implementation
        of this interface and passes it to ISAXServices::ParseStream.
        Additional paramaters are specified via specific data
        interfaces. The parser uses the instance to report basic
        document-related events like the start and end of elements
        and character data.

        The order of events in this interface is very important because
        it mirrors the order of information in the document itself.
        For example, all of an element's content (character data,
        processing instructions, and/or subelements) will appear, in
        order, between the StartElement event and the corresponding
        EndElement event.
        */
class ISAXContentHandler : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISAXCONTENTHANDLER };

        /**
     	Register this content handler to handle specific elements, attributes,
     	and processing instructions.
     	
     	When combined with a service provider implementation SAXServices will call
     	your Register method to allow the content handler to specify which elements,
     	attributes, and/or processing instructions it is interested in handling.
     	Registration is accomplished by calling RegisterElementHandler,
     	RegisterAttributeHandler, and RegisterPIHandler.

        @param saxServices		The instance of ISAXServices instantiated for this parse.
		@param importer		The instance of XMLImporter being used for this import. The Content
							Handler needs to be able to get to the IMatchRecorder and IXMLImporterDOM
							from the interface passed in here.
        */
	virtual void Register(ISAXServices* saxServices, IPMUnknown *importer = nil) = 0;

        /**
        Receives character data

        The parser will call this method to report each chunk of
        character data.  SAX parsers may return all contiguous
        character data in a single chunk, or they may split it into
        several chunks. But all characters in any single
        event must come from the same external entity so the
        Locator provides useful information.

        Note some parsers will report whitespace using the
        IgnorableWhitespace() method rather than this one (validating
        parsers must do so).

        @param Chars            The characters from the XML document.
        */
	virtual void Characters(const WideString& chars) = 0;

        /**
        Receive the beginning of document notification

        The SAX parser will invoke this method once before
        other methods in this interface or in DTDHandler (except
        for setDocumentLocator).

        @param saxServices		The instance of ISAXServices instantiated for this parse.
        */
	virtual void StartDocument(ISAXServices* saxServices) = 0;

        /**
        Receive end of document notification

        The SAX parser will invoke this method only once and it
        will be the last method invoked during the parse.  The parser
        shall not invoke this method until it has either abandoned
        parsing (because of an unrecoverable error) or reached the
        end of input.
        */
	virtual void EndDocument() = 0;

        /**
        Receive the beginning of element notification

        The parser will invoke this method at the beginning of
        every element in the XML document; there will be a
        corresponding endElement() event for every startElement()
        event (even when the element is empty). All of the element's
        content will be reported, in order, before the corresponding
        endElement() event.

        Note that the attribute list provided will
        contain only attributes with explicit values (specified or
        defaulted): #IMPLIED attributes will be omitted.

        @param uri          The URI of the asscioated namespace
                            for this element

        @param localname    The local part of the element name

        @param qname        The QName of this element

        @param attrs        The attributes attached to the element,
                            if any.

        @see #EndElement
        @see ISAXAttributes
        */
	virtual void StartElement(const WideString& uri, const WideString& localname,
								const WideString& qname, ISAXAttributes* attrs) = 0;

        /**
        Receive end of element notification

        The SAX parser will invoke this method at the end of every
        element in the XML document; there will be a corresponding
        startElement() event for every endElement() event (even when
        the element is empty).

        @param uri          The URI of the associated namespace for
                            this element

        @param localname    The local part of the element name

        @param qname        The QName of this element
        */
	virtual void EndElement(const WideString& uri, const WideString& localname, const WideString& qname) = 0;

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
        Receive ignorable whitespace in element content

        Validating parsers must use this method to report each
        chunk of ignorable whitespace (see the W3C XML 1.0
        recommendation, section 2.10). Non-validating parsers may
        also use this method if they are capable of parsing and using
        content models.

        SAX parsers may return all contiguous whitespace in a
        single chunk, or they may split it into several chunks.
        But all characters in any single event must come
        from the same external entity so the Locator provides
        useful information.

        @param chars        The characters from the XML document.

        @see #Characters
        */
	virtual void IgnorableWhitespace(const WideString& chars) = 0;

        /**
        Receive a processing instruction

        The parser will invoke this method once for each
        processing instruction found: note that processing
        instructions may occur before or after the main document
        element.

        A SAX parser should never report an XML declaration (XML
        1.0, section 2.8) or a text declaration (XML 1.0, section
        4.3.1) using this method.

        @param target       The processing instruction target

        @param data         The processing instruction data, or null
                            if none was supplied
        */
	virtual void ProcessingInstruction(const WideString& target, const WideString& data) = 0;

        /**
        Receive a skipped entity notification

        The parser will invoke this method once for each entity
        skipped.  All processors may skip external entities,
        depending on the values of the features:<br>
        http://xml.org/sax/features/external-general-entities<br>
        http://xml.org/sax/features/external-parameter-entities

        @param name         The name of the skipped entity.
                            If it is a parameter entity, the name
                            will begin with %, and if it is the
                            external DTD subset, it will be the
                            string [dtd].
        */
	virtual void SkippedEntity(const WideString& name) = 0;

        /**
        (Extension) Receive a comment

        The parser will invoke this method when it encounters
        a comment.

        @param comment      The interior text of the comment.
        */
	virtual void ExtComment(const WideString& comment) = 0;

        /**
        (Extension) Receive the XML declaration

        The parser will invoke this method when it encounters
        a well-formed XML declaration. Any or all of these
        strings may be invalid, so check first before using them.

        @param version      The XML version

        @param encoding     The encoding specified in the
                            declaration

        @param standalone   The value of the standalone indicator.

        @param actualEncoding The actual encoding detected by the
                            parser
        */
	virtual void ExtXMLDecl(const WideString& version, const WideString& encoding,
								const WideString& standalone, const WideString& actualEncoding) = 0;

        /**
        Receive a parser position locator

        If this method is called at all, it is guaranteed to be
        called before invoking any of the other methods in this
        interface.

        The locator allows the application to determine the end
        position of any document-related event, even if the parser is
        not reporting an error.  Typically, the application will
        use this information for reporting its own errors (such as
        character content that does not match an application's
        business rules). The information returned by the locator
        is probably not sufficient for use with a search engine.

        Note that the locator will return correct information only
        during each individual call to the functions in this
        interface. The application should not attempt to use it at
        any other time.

        @param locator      An object that can return the
                            location of any SAX document event.

        @see ISAXLocator
        */
	virtual void SetDocumentLocator(ISAXLocator* locator) = 0;

        /**
        return a parser position locator
        
        This is the document locator that was set before an parsing began

        @see ISAXContentHandler#SetDocumentLocator
        */
	virtual ISAXLocator* GetDocumentLocator() const = 0;
};

#endif