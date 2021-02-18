//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/ISAXServices.h $
//  
//  Owner: Robin Briggs
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
#ifndef __ISAXServices_h__
#define __ISAXServices_h__

#include "IPMUnknown.h"
#include "PMReal.h"
#include "XMLParserID.h"

class ISAXContentHandler;
class ISAXEntityResolver;
class ISAXDTDHandler;
class BaseProgressBar;
class IXMLDTDHandler;
class IXMLDTDTokenHandler;
class IXMLParsingContext;

/** Class responsible for SAX parsing of an XML-based stream. Clients pass in custom handlers.
	SAX (Simple API for XML) specifies an abstract set of interfaces a conforming parser should implement;
	it is an example of an event based API for parsing XML.
	The contrast between an event-based API like SAX, versus DOM-based APIs, which construct in-memory parse trees,
	is described in some detail at the <a href="http://www.saxproject.org/?selected=event">SAX Projects site</a>.

	InDesign constructs something akin to a DOM based representation of the logical structure of a document, using the services of
	the SAX based XML parser. One occasion where you may need to use this class from client code
	is to use IXMLStructureSuite::Import. You can construct an object supporting ISAXServices  for use in these situations with code like this:
	<pre>
	InterfacePtr<IK2ServiceRegistry> serviceRegistry(GetExecutionContextSession(), UseDefaultIID());
	InterfacePtr<IK2ServiceProvider> xmlProvider(
		serviceRegistry->QueryServiceProviderByClassID(kXMLParserService, 
			kXMLParserServiceBoss));
	InterfacePtr<ISAXServices> saxServices(xmlProvider, UseDefaultIID());
	</pre>

*/
class ISAXServices : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISAXSERVICES };

	/**	Parse the XML data in the incoming stream, calling out to the 
		DocumentHandler as elements are encountered.
		@param stream specifies the stream containing the XML content to parse
		@param progressBar the progress bar to use when importing XML content.
		@return bool16 
	 */
	virtual bool16 ParseStream(IPMStream *stream, ISAXContentHandler* defaultHandler,
								ISAXEntityResolver* entityResolver = nil,
								ISAXDTDHandler* dtdHandler = nil,
								IXMLDTDTokenHandler* dtdTokenHandler = nil,
								BaseProgressBar *progressBar =  nil) = 0;
	
	/** Return the default content handler that was supplied at the beginning of the parse.
		This is only valid during a parse.  Otherwise this will return nil.
	    
		@return the instance of the default content handler.  This is not addref'ed.
	*/
	virtual ISAXContentHandler* GetDefaultContentHandler() const = 0;
	
	/** Register a content handler for a given element.  When the parser encounters an element
	    with the specified name it will use this content handler to deal with it.
	    
		@param uri the uri (namespace) of the tag name
		@param localName the unqualifed portion of the tag name
		@param handler an instance of ISAXContentHandler that handle this element
	*/
	virtual void RegisterElementHandler(const WideString& uri, const WideString& localName, ISAXContentHandler* handler) = 0;
	
	/** Return the content handler registered for this element tag name.
	    
		@param uri the uri (namespace) of the tag name
		@param localName the unqualifed portion of the tag name
		@return addref'ed instance of the content handler
	*/
	virtual ISAXContentHandler* QueryElementHandler(const WideString& uri, const WideString& localName) const = 0;
	
	/** Register a content handler for a given attribute.  When the parser encounters an element
	    with the specified attribute it will use this content handler to deal with it.
	    
		@param uri the uri (namespace) of the attribute
		@param localName the unqualifed portion of the attribute
		@param handler an instance of ISAXContentHandler that handle this element
	*/
	virtual void RegisterAttributeHandler(const WideString& uri, const WideString& localName, ISAXContentHandler* handler) = 0;
	
	/** Return the content handler registered for this attribute.
	    
		@param uri the uri (namespace) of the attribute
		@param localName the unqualifed portion of the attribute
		@return addref'ed instance of the content handler
	*/
	virtual ISAXContentHandler* QueryAttributeHandler(const WideString& uri, const WideString& localName) const = 0;
	
	/** Register a content handler for a given processing instruction target.  When the parser encounters a PI
	    with the specified target name it will use this content handler to deal with it.
	    
		@param targetName the name of the processing instruction target
		@param handler an instance of ISAXContentHandler that handle this PI
	*/
	virtual void RegisterPIHandler(const WideString& targetName, ISAXContentHandler* handler) = 0;
	
	/** Return the content handler registered for this processing instruction target name.
	    
		@param targetName the name of the target
		@return addref'ed instance of the content handler
	*/
	virtual ISAXContentHandler* QueryPIHandler(const WideString& targetName) const = 0;
	
	/** Returns the current parsing context information.  This includes the current element, tag name,
	    child index, story reference, and text insertion position.  Additional parsing context information
	    can be accessed via this interface if content handlers have data interfaces to kXMLParsingLocatorBoss.
	    
		@return instance of IXMLParsingContext.
	*/
	virtual IXMLParsingContext* QueryCurrentParsingContext() = 0;
	
	/** Save the specified set of parsing context information on a stack.  When parsing an imported XML file
	    parent/child element parsing information is maintained on this stack.  For example StartElement pushes
	    the current parsing context information on the stack before creating a new element.
	    
		@param parsingContext a set of parsing context information, usually the current information.
	*/
	virtual void Push_Back(IXMLParsingContext* parsingContext) = 0;
	
	/** Remove the specified set of parsing context information on a stack.  
	    
		@return instance of IXMLParsingContext.
	*/
	virtual IXMLParsingContext* Pop_Back() = 0;

	/** Peek at the parsing context information on the top of the stack.  This does not remove the context
	    information from the stack.  Useful for examining parent information.  
	    
		@return instance of IXMLParsingContext.
	*/
	virtual IXMLParsingContext* Back() = 0;
};

#endif	// __ISAXServices_h__
