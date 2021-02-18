//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/ISAXAttributes.h $
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

#ifndef __ISAXAttributes_h__
#define __ISAXAttributes_h__

#include "IPMUnknown.h"
#include <vector>
#include "XMLParserID.h"

class ISAXServices;


        /**
		An InDesign friendly Wrapper for attributes in Expat.  
		An instance of this class will be passed to	ISaxContentHandler::StartElement.

		An element's attributes

        The instance provided will return valid results only during
        the scope of the startElement invocation. To save it for
        future use, the application must make a copy.

        There are two ways for the SAX application to obtain
        information from the ISAXAttributes interface.  First, it can iterate
        through the entire list:

        <pre>
        StartElement(const WideString& uri, const WideString& localname,
        const WideString& qname, ISAXAttributes* attrs) {
          for (unsigned int i = 0; i < atts->GetLength(); i++) {
            WideString Qname, URI, local, type, value;
            if (!atts->getQName(i, Qname)) ...
            if (!atts->getURI(i, URI)) ...
            if (!atts->getLocalName(i, local)) ...
            if (!atts->getType(i, type)) ...
            if (!atts->getValue(i, value)) ...
            [...]
          }
        }
        </pre>

        (Note: The result of GetLength() will be zero if there
        are no attributes.)

        As an alternative, the application can request the value or
        type of specific attributes by qualified name or by
        fully expanded name with namespace:

        <pre>
        StartElement(const WideString& uri, const WideString& localname,
        const WideString& qname, ISAXAttributes* attrs) {
          WideString identifier;
          if (!atts->GetValue("id", identifier)) ...
          WideString label;
          if (!atts->GetValue("label", label)) ...
          [...]
        }
        </pre>

        <b>Invalid Parameters</b>


        @see ISAXContentHandler#StartElement
        */

class ISAXAttributes : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISAXATTRIBUTES };

	typedef std::vector< std::pair<WideString, WideString> > NamespaceDecl;
	
        /**
        Adopt an instance of attributes provided by the parser.
        This is not intended to be used by clients.

		'attributes' is an array of name/value pairs,
		terminated by 0; names and values are 0
		terminated. The name of each attribute
		may include the namespace URI and the
		prefix, depending on the parser options.

		Namespace declarations are not included in 'attributes'.
		'namespaceDecls' contains namespace declarations in the same scope of 'attributes'.
        */

		virtual void Adopt(const char** attributes, bool16 namespaced, ISAXServices* owner, const NamespaceDecl& namespaceDecls) = 0;

        /**
        Number of attributes in this list

        The SAX parser may provide attributes in any
        arbitrary order, regardless of the order in which they were
        declared or specified.  The number of attributes may be
        zero.

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

        The QNames must be unique: the SAX parser will not include
        the same attribute twice.  Attributes without values (those
        declared #IMPLIED without a value specified in the start tag)
        will be omitted from the list.

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

        The QNames must be unique: the SAX parser shall not include
        the same attribute twice.  Attributes without values (those
        declared #IMPLIED without a value specified in the start tag)
        will be omitted from the list.

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

        The QNames must be unique: the SAX parser shall not include
        the same attribute twice.  Attributes without values (those
        declared #IMPLIED without a value specified in the start tag)
        will be omitted from the list.

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

        The attribute type is one of the strings "CDATA", "ID",
        "IDREF", "IDREFS", "NMTOKEN", "NMTOKENS", "ENTITY",
        "ENTITIES", or "NOTATION" (always in upper case).

        If the parser has not read a declaration for the attribute,
        or if the parser does not report attribute types, then it
        must return the value "CDATA" as stated in the XML 1.0
        Recommentation (clause 3.3.3, "Attribute-Value
        Normalization").

        For an enumerated attribute that is not a notation, the
        parser will report the type as "NMTOKEN".

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

        If the attribute value is a list of tokens (IDREFS,
        ENTITIES, or NMTOKENS), the tokens will be concatenated
        into a single string separated by whitespace.

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
	
	
	/** Convenience methods to easily extract basic types from a set of attributes.  If the attribute exists, it will extract
		the basic type from it.  If it doesn't exist, it returns the default value you passed in. */
	virtual bool16		HasAttribute(const PMString& key) const = 0;
	virtual bool16		HasAttribute(const WideString& key) const = 0;

	virtual PMString		GetAttributeString(const PMString& key, const PMString& defaultValue = "") const = 0;
	virtual WideString	GetAttributeString(const WideString& key, const WideString* defaultValue = nil) const = 0;

	virtual bool16 		GetAttributeBool(const PMString& key, bool16 defaultValue = kFalse) const = 0;
	virtual bool16 		GetAttributeBool(const WideString& key, bool16 defaultValue = kFalse) const = 0;

	virtual int32 		GetAttributeInt(const PMString& key, int32 defaultValue = 0) const = 0;
	virtual int32 		GetAttributeInt(const WideString& key, int32 defaultValue = 0) const = 0;
	
};

#endif