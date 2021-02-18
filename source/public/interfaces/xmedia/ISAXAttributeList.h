//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/ISAXAttributeList.h $
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

#ifndef __ISAXAttributeList_h__
#define __ISAXAttributeList_h__

#include "IPMUnknown.h"
#include "XMLParserID.h"

namespace BIB_NAMESPACE {
	class CAXEAttributeList;
}

class ISAXDOMSerializerServices;

        /**
		An InDesign friendly Wrapper for CAXEAttributeList.  
		An instance of this class will be passed to	ISaxContentHandler::StartElement.

        Deliver a list of an element's attributes

        The DOM serializer implements this interface and passes an 
        instance as an argument of the startElement event. This class
        mimics the CAXEAttributes class so to make the interfaces of 
        HAXEContentHandlerBase and HAXEDOMSerializerHandlerBase 
        classes as similar as possible.

        The instance provided is guaranteed to return valid results 
        only during the scope of the startElement invocation. It is
        a reference to a live AXE DOM which could change. To save the
        attribute values for future use, the application must make 
        a copy.

        An attribute only includes traits that have been
        specified or defaulted: #IMPLIED attributes will not be
        included.

        There are two ways for the application to obtain information 
        from the CAXEAttributesList class. First, it can iterate 
        through the entire list:

        <pre>
        startElement(CAXEString& uri, CAXEString& localname,
            CAXEString& qname, CAXEAttributeList& attrs, 
            CAXENodeDOM& sourceNode ) {
          for (unsigned int i = 0; i < atts.getLength(); i++) {
            CAXEString qName, URI, local, type, value;
            if (!atts.getQName(i, qName)) ...
            if (!atts.getURI(i, URI)) ...
            if (!atts.getLocalName(i, local)) ...
            if (!atts.getType(i, type)) ...
            if (!atts.getValue(i, value)) ...
            [...]
          }
        }
        </pre>

        (Note: The result of getLength() will be zero if there
        are no attributes.)

        As an alternative, the application can request the value or
        type of specific attributes by qualified name or by
        fully expanded name with namespace:

        <pre>
        startElement(CAXEString& uri, CAXEString& localname,
        CAXEString& qname, CAXEAttributeList& attrs, 
            CAXENodeDOM& sourceNode )
          CAXEString identifier;
          if (!atts.getValue("id", identifier)) ...
          CAXEString label;
          if (!atts.getValue("label", label)) ...
          [...]
        }
        </pre>

        <b>Invalid Parameters</b>

        Unless otherwise indicated, it is an error to use an invalid
        container (IsValid() == false), or a NULL pointer, as a
        parameter to any function. In some instances, the requirement
        that a specific parameter must be valid is repeated in the
        commentary for the specific function. The lack of any
        indication in the commentary for the specific function should
        still be taken to mean that an invalid container or NULL
        pointer will result in a kAXEErrClientFault exception.

        @see ISAXOMSerializerHandler#startElement
        */

class ISAXAttributeList : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISAXATTRIBUTELIST };
	
        /**
        Adopt an instance of a CAXEAttributeList class provided by the serializer.
        This is not intended to by used by clients.
        */

	virtual void Adopt(BIB_NAMESPACE::CAXEAttributeList attributes, ISAXDOMSerializerServices* owner) = 0;

        /**
        Number of attributes in this list

        The attributes may be delivered in any arbitrary order, 
        regardless of the order in which they were declared or 
        specified.  The number of attributes may be zero.

        @return The number of attributes in the list.
        */
	virtual int32 GetLength() const = 0;

        /**
        Mark an attribute as handled so that other attribute
		handlers will not have to try and deal with it.

        @param index        The index of the attribute in the list
                            (starting at 0).
        */
	virtual void AttributeHandled(uint32 index) = 0;

        /**
        Namespace URI of an attribute by position

        The QNames must be unique: no attribute will be included in
        the list twice. Attributes without values (those declared 
        #IMPLIED without a value specified in the start tag) will be 
        omitted from the list.

        @param index        The index of the attribute in the list
                            (starting at 0).

        @param uri          The output parameter specified by the
                            caller to contain the returned URI.

        @return kFalse if the index is out of range, true otherwise.

        @see #GetLength
        */
	virtual bool16 GetURI(uint32 index, WideString& uri) const = 0;

        /**
        Local name of an attribute by position

        The QNames must be unique: no attribute will be included in
        the list twice. Attributes without values (those declared 
        #IMPLIED without a value specified in the start tag) will be 
        omitted from the list.

        @param index        The index of the attribute in the list
                            (starting at 0).

        @param localName    The output parameter specified by the
                            caller to contain the returned local name
                            of the indexed attribute.

        @return kFalse if the index is out of range, true otherwise.

        @see #GetLength
        */
	virtual bool16 GetLocalName(uint32 index, WideString& localName) const = 0;

        /**
        QName of an attribute by position

        The QNames must be unique: no attribute will be included in
        the list twice. Attributes without values (those declared 
        #IMPLIED without a value specified in the start tag) will be 
        omitted from the list.

        @param index        The index of the attribute in the list
                            (starting at 0).

        @param qName        The output parameter specified by the
                            caller to contain the returned QName of
                            the indexed attribute.

        @return kFalse if the index is out of range, true otherwise.

        @see #GetLength
        */
	virtual bool16 GetQName(uint32 index, WideString& qName) const = 0;

        /**
        Return the type of an attribute in the list (by position).

        This method is included to provide consistency with the
        CAXEAttributes class. Every call to this method will 
        return "CDATA" as the type if the index is in range.

        @param index        The index of the attribute in the
                            list (starting at 0).

        @param attributeType The output parameter specified by the
                            caller to contain the returned type
                            string of the indexed attribute.

        @return kFalse if the index is out of range, true otherwise.

        @see #GetLength
        @see #GetType(String)
        */
	virtual bool16 GetType(uint32 index, WideString& attributeType) const = 0;

        /**
        Value of an attribute by position

        @param index        The index of the attribute in the list
                            (starting at 0).

        @param attributeValue The output parameter specified by the
                            caller to contain the returned value of
                            the indexed attribute.

        @return kFalse if the index is out of range, true otherwise.

        @see #GetLength
        @see #GetValue
        */
	virtual bool16 GetValue(uint32 index, WideString& attributeValue) const = 0;

        /**
        Index by namespace name

        @param uri          The Namespace URI, or the empty string if
                            the name has no Namespace URI.

        @param localPart    The attribute's local name.

        @param index        Output of index if returned true.

        @return kFalse if no such attribute, true otherwise.
        */
	virtual bool16 GetIndex(const WideString& uri, const WideString& localPart, uint32& index) const = 0;

        /**
        Index by XML 1.0 qualified name

        @param qName        The qualified (prefixed) name.

        @param index        Output of index if returned true.

        @return             kFalse if no such attribute, true
                            otherwise.
        */
	virtual bool16 GetIndex(const WideString& qName, uint32& index) const = 0;

        /**
        Type by namespace name

        <p>See #GetType for a description of the possible types.</p>

        @param uri          The namespace URI, or the empty string if
                            the name has no namespace URI.

        @param localPart    The local name of the attribute.

        @param attributeType The output parameter specified by the
                            caller to contain the returned type
                            string of the named attribute.

        @return             kFalse if the attribute is not in the list
                            or if namespace processing is not being
                            performed, true otherwise.
        */
	virtual bool16 GetType(const WideString& uri, const WideString& localPart, WideString& attributeType) const = 0;

        /**
        Type by qualified name

        <p>See #GetType for a description of the possible types.</p>

        @param qName        The XML 1.0 qualified name.

        @param attributeType The output parameter specified by the
                            caller to contain the returned type
                            string of the named attribute.

        @return             kFalse if the attribute is not in the list
                            or if qualified names are not available,
                            true otherwise.
        */
	virtual bool16 GetType(const WideString& qName, WideString& attributeType) const = 0;

        /**
        Value by namespace name

        @param uri          The namespace URI, or the empty String if
                            the name has no Namespace URI.

        @param localPart    The local name of the attribute.

        @param attributeValue The output parameter specified by the
                            caller to contain the returned value of
                            the named attribute.

        @return             kFalse if the attribute is not in the
                            list, true otherwise.
        */
	virtual bool16 GetValue(const WideString& uri, const WideString& localPart, WideString& attributeValue) const = 0;

        /**
        Look up an attribute's value by XML 1.0 qualified name.

        @param qName        The XML 1.0 qualified name.

        @param attributeValue The output parameter specified by the
                            caller to contain the returned value of
                            the named attribute.

        @return             kFalse if the attribute is not in the list
                            or if qualified names are not available,
                            true otherwise.
        */
	virtual bool16 GetValue(const WideString& qName, WideString& attributeValue) const = 0;
};

#endif