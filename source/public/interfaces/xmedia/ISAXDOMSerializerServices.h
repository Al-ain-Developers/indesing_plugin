//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/ISAXDOMSerializerServices.h $
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
//========================================================================================

#pragma once
#ifndef __ISAXDOMSerializerServices_h__
#define __ISAXDOMSerializerServices_h__

#include "IPMUnknown.h"
#include "PMReal.h"
#include "XMLParserID.h"

class IIDXMLDOMDocument;
class ISAXDOMSerializerHandler;
class BaseProgressBar;
class IXMLParsingContext;

/** Class responsible for serialization of a document DOM. Clients pass in custom handlers.
	SAX (Simple API for XML) specifies an abstract set of interfaces a conforming serializer should implement.
	
	@see ISAXDOMSerializerHandler.
*/
class ISAXDOMSerializerServices : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISAXDOMSERIALIZERSERVICES };

	/**	Serialize the incoming document DOM, calling out to the 
		DOMSerializerHandler as elements are encountered.
		@param documentDOM specifies the document DOM to be serialzied.
		@param defaultHandler the default DOMSerializerHandler.
		@param progressBar the progress bar to use when importing XML content.
		@return bool16 
	 */
	virtual bool16 SerializeDOM(IIDXMLDOMDocument *documentDOM, ISAXDOMSerializerHandler* defaultHandler,
								BaseProgressBar *progressBar) = 0;
	
	/** Return the default content handler that was supplied at the beginning of the serialization.
		This is only valid during a serialization.  Otherwise this will return nil.
	    
		@return the instance of the default serialization handler.  This is not addref'ed.
	*/
	virtual ISAXDOMSerializerHandler* GetDefaultContentHandler() const = 0;
	
	/** Register a content handler for a given element.  When the serialization encounters an element
	    with the specified name it will use this content handler to deal with it.
	    
		@param uri the uri (namespace) of the tag name
		@param localName the unqualifed portion of the tag name
		@param handler an instance of ISAXDOMSerializerHandler that handle this element
	*/
	virtual void RegisterElementHandler(const WideString& uri, const WideString& localName, ISAXDOMSerializerHandler* handler) = 0;
	
	/** Return the content handler registered for this element tag name.
	    
		@param uri the uri (namespace) of the tag name
		@param localName the unqualifed portion of the tag name
		@return addref'ed instance of the content handler
	*/
	virtual ISAXDOMSerializerHandler* QueryElementHandler(const WideString& uri, const WideString& localName) const = 0;
	
	/** Register a content handler for a given attribute.  When the serialization encounters an element
	    with the specified attribute it will use this content handler to deal with it.
	    
		@param uri the uri (namespace) of the attribute
		@param localName the unqualifed portion of the attribute
		@param handler an instance of ISAXDOMSerializerHandler that handle this element
	*/
	virtual void RegisterAttributeHandler(const WideString& uri, const WideString& localName, ISAXDOMSerializerHandler* handler) = 0;
	
	/** Return the content handler registered for this attribute.
	    
		@param uri the uri (namespace) of the attribute
		@param localName the unqualifed portion of the attribute
		@return addref'ed instance of the content handler
	*/
	virtual ISAXDOMSerializerHandler* QueryAttributeHandler(const WideString& uri, const WideString& localName) const = 0;
	
	/** Register a content handler for a given processing instruction target.  When the serialization encounters a PI
	    with the specified target name it will use this content handler to deal with it.
	    
		@param targetName the name of the processing instruction target
		@param handler an instance of ISAXDOMSerializerHandler that handle this PI
	*/
	virtual void RegisterPIHandler(const WideString& targetName, ISAXDOMSerializerHandler* handler) = 0;
	
	/** Return the content handler registered for this processing instruction target name.
	    
		@param targetName the name of the target
		@return addref'ed instance of the content handler
	*/
	virtual ISAXDOMSerializerHandler* QueryPIHandler(const WideString& targetName) const = 0;
	
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

#endif	// __ISAXDOMSerializerServices_h__
