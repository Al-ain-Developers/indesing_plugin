//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLOutStream.h $
//  
//  Owner: Chris Parrish
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
#ifndef __IXMLOUTSTREAM__
#define __IXMLOUTSTREAM__

#include "XMLID.h"
#include "IPMUnknown.h"

#include "WideString.h"
#include "K2Vector.h"
#include "KeyValuePair.h"

class IPMStream;

/** Represents an XML based stream onto a file or memory; you'll find IXMLStreamUtils
	to create one of these stream types.

  The methods that write to the stream will use the proper encoding based on the current setting
	All methods expect data to be in the form of unicode strings with 16 bit chars.

	!!!!!!!!!  For MachO char literals 'L' construct 4 (count 'em 4!) byte char strings !!!!!!!
	!!!!!!!!!  For MachO char literals 'L' construct 4 (count 'em 4!) byte char strings !!!!!!!
	
	A 16-bit string literal can be constucted in code using 'L' such as:
	<pre>
		myStream->DocHeader((ConstWString)L"1.0");		// compiles but does the wrong thing!!! You can't cast an elephant to be a mouse!!!

		myStream->DocHeader(WideString(L"1.0"));		// preferred method - convert to a WideString, which method also accepts
		myStream->DocHeader(L"1.0");						// compiler does the above conversion for you - but it's better to do it manually
	</pre>

	For more information see these parts of the XML 1.0 specification: 
  	<a href="http://www.w3.org/TR/2000/REC-xml-20001006#sec-prolog-dtd">prolog sections</a>,
	<a href="http://www.w3.org/TR/2000/REC-xml-20001006#dt-doctype">document-types</a> 
	<a href="http://www.w3.org/TR/2000/REC-xml-20001006#NT-doctypedecl">doc-type declarations</a>,
  	<a href="http://www.w3.org/TR/2000/REC-xml-20001006#sec-comments">comments</a>,
	<a href="http://www.w3.org/TR/2000/REC-xml-20001006#sec-pi">processing instructions</a> and
	<a href="http://www.w3.org/TR/2000/REC-xml-20001006#sec-cdata-sect">CDATA sections</a>.
*/
class IXMLOutStream : public IPMUnknown
{
	public:
	
	enum { kDefaultIID = IID_IXMLOUTSTREAM };
	
	/**  Enumeration of supported encoding types. */
	enum eEncodingType { /** */ kUTF8, /** */ kUTF16, /** */ kShiftJIS};

	/**  Enumeration of supported attribute types. */
	enum eAttributeType { /** */ kCDATA, /** */ kNMTOKEN, /** */ kNMTOKENS, /** */ kENTITY, /** */ kENTITIES,
	                      /** */ kID, /** */ kIDREF, /** */ kIDREFS, /** */ kNOTATION, /** */ kEnumeration };

	/**  Enumeration of supported attribute qualifiers. */
	enum eAttributeQualifier { /** */ kQNone, /** */ kQRequired, /** */ kQImplied, /** */ kQFixed };

	//=====================================================================================
	// CLASS : AttributeDfn
	//=====================================================================================
	/** Nested class for IXMLOutStream methods which take an AttributeDfnList. This class defines 
		an attribute declaration in a DTD
	*/
	class AttributeDfn {
	public:
		typedef object_type data_type;
		
		/** AttributeDfn default constructor */
		AttributeDfn()
			{}
		/** AttributeDfn constructor
			@param n name of the attribute
			@param t type of the attribute
			@param q qualifier of the attribute
		*/
		AttributeDfn(const WideString &n, eAttributeType t, eAttributeQualifier q)
			: fName(n), fType(t), fQualifier(q), fDefault()
			{}
		/** AttributeDfn constructor
			@param n name of the attribute
			@param t type of the attribute
			@param d default value of the attribute
			@param q qualifier of the attribute
		*/
		AttributeDfn(const WideString &n, eAttributeType t, const WideString &d, eAttributeQualifier q)
			: fName(n), fType(t), fQualifier(q), fDefault(d)
			{}
		/** AttributeDfn constructor
			@param n name of the attribute
			@param t type of the attribute
			@param d default value of the attribute
			@param q qualifier of the attribute
		*/
		AttributeDfn(const WideString &n, eAttributeType t, const UTF16TextChar *d, eAttributeQualifier q)
			: fName(n), fType(t), fQualifier(q), fDefault(d)
			{}
		/** AttributeDfn constructor
			@param n name of the attribute
			@param t type of the attribute
			@param q qualifier of the attribute
		*/
		AttributeDfn(const UTF16TextChar* n, eAttributeType t, eAttributeQualifier q)
			: fName(n), fType(t), fQualifier(q), fDefault()
			{}
		/** AttributeDfn constructor
			@param n name of the attribute
			@param t type of the attribute
			@param d default value of the attribute
			@param q qualifier of the attribute
		*/
		AttributeDfn(const UTF16TextChar* n, eAttributeType t, const WideString &d, eAttributeQualifier q)
			: fName(n), fType(t), fQualifier(q), fDefault(d)
			{}
		/** AttributeDfn constructor
			@param n name of the attribute
			@param t type of the attribute
			@param d default value of the attribute
			@param q qualifier of the attribute
		*/
		AttributeDfn(const UTF16TextChar* n, eAttributeType t, const UTF16TextChar* d, eAttributeQualifier q)
			: fName(n), fType(t), fQualifier(q), fDefault(d)
			{}
		/** AttributeDfn copy constructor */
		AttributeDfn(const AttributeDfn &other)
			{Copy(other);}
		
		/** AttributeDfn operator== */
		bool16 operator==(const AttributeDfn &other) const
			{return (fName == other.fName) && (fType == other.fType);}
		/** AttributeDfn operator= */
		AttributeDfn& operator=(const AttributeDfn &other)
			{Copy(other); return *this;}
		
	private:
		void Copy(const AttributeDfn &other)
			{fName = other.fName; fType = other.fType; fQualifier = other.fQualifier; fDefault = other.fDefault;}
		
	public:
		WideString			fName;			/** attribute name */
		eAttributeType		fType;			/** attribute type */
		eAttributeQualifier	fQualifier;		/** attribute qualifier */
		WideString			fDefault;		/** attribute default value */
	};
	
	/** Used to represent a list of AttributeDfn objects for an IXMLOutStream */
	typedef K2Vector<AttributeDfn> AttributeDfnList;

	//=====================================================================================
	// CLASS : Attribute
	//=====================================================================================
	/** Nested class for IXMLOutStream methods which take an AttributeList. Defines an attribute 
		for an element
	*/
	class Attribute {
	public:
		typedef object_type data_type;
		
		/** Attribute default constructor */
		Attribute()
			{}
		/** Attribute constructor
			@param n name of attribute
			@param v value of attribute
		*/
		Attribute(const WideString &n, const WideString &v)
			: fName(n), fValue(v)
			{}
		/** Attribute constructor
			@param n name of attribute
			@param v value of attribute
		*/
		Attribute(const UTF16TextChar *n, const UTF16TextChar *v)
			: fName(n), fValue(v)
			{}
		/** Attribute copy constructor */
		Attribute(const Attribute &other)
			{Copy(other);}
			
		/** Get attribute name
			@returns name of the attribute
		*/
		const WideString &GetName() const
			{return fName;}
		/** Get attribute value
			@returns attribute value
		*/
		const WideString &GetValue() const
			{return fValue;}
		
		/** Attribute operator== */
		bool16 operator==(const Attribute &other) const
			{return (fName == other.fName) && (fValue == other.fValue);}
		/** Attribute operator= */
		Attribute& operator=(const Attribute &other)
			{Copy(other); return *this;}
		
	private:
		void Copy(const Attribute &other)
			{fName = other.fName; fValue = other.fValue;}
		
	public:
		WideString	fName;	/** attribute name */
		WideString 	fValue;	/** attribute value */
	};
	
	/** Used to represent a list of Attribute objects for an IXMLOutStream */
	typedef K2Vector<Attribute> AttributeList;

	typedef KeyValuePair<UTF16TextChar, const WideString* > Entity;

	typedef K2Vector<Entity> EntityMap;
	

	/**  Enumeration of content particle separators */
	enum eContentParticleSeparator {
		/** no separator */ kNone,
		/** choice | */ kChoice,
		/** sequence , */ kSequence
	};

	/**  Enumeration of content particle occurrences */
	enum eContentParticleOccurrence {
		/** */ kExactlyOnce,
		/** */ kOneOrMore,
		/** */ kZeroOrMore,
		/** */ kOptional
	};

	/**  Enumeration of keywords */
	enum eKeyword {
		/** */ kKW_SPACE,
		/** */ kKW_PCDATA,
		/** */ kKW_ANY,
		/** */ kKW_EMPTY,
		/** */ kKW_REQUIRED,
		/** */ kKW_IMPLIED,
		/** */ kKW_FIXED,
		/** */ kKW_SYSTEM,
		/** */ kKW_PUBLIC,
		/** */ kKW_NDATA
	};
	

	//----- Stream

	/**	Must be called before any other methods to initialize stream.
		@param encoding kUTF16 is Big or Litle Endian, depending on platform
		@param stripInvalid determines if invalid Unicode chars are stripped from the output
			or converted to processing instructions that contain their hexidecimal equivalent
		@return  kTrue if stream could be opened, kFalse otherwise
	 */
	virtual bool16		Open(eEncodingType encoding = kUTF16, bool16 stripInvalid = kTrue) = 0;

	/**	must be called when done with stream to ensure final flush of stream content
	 */
	virtual void		Close() = 0;

	/**	force all pending writes
		@return  kSuccess if Flush succeeds, kFailure otherwise
	 */
	virtual ErrorCode	Flush() = 0;
	

	//----- Standard elements and data  

	/**	Write the XML header for this document.
	
		@param version XML version (e.g. 1.0 is expected)
		@param standalone  specifies whether the document should be described as standalone="yes" or not
	 */
	virtual void		DocHeader(const WideString& version, bool16 standalone = kTrue) = 0;

	/**	Write the XML header for this document.
	
		@param version XML version (e.g. 1.0 is expected)
		@param standalone  specifies whether the document should be described as standalone="yes" or not
	 */
			void		DocHeader(const UTF16TextChar* version, bool16 standalone = kTrue)
							{ this->DocHeader(WideString(version), standalone); }

	/** write the XML text declaration. See XML 1.0 spec 20001006, section 4.3.1
		@param version XML version (e.g. 1.0 is expected)
	*/
	virtual void		TextDeclaration(const WideString& version) = 0;

	/** write the XML text declaration. See XML 1.0 spec 20001006, section 4.3.1
		@param version XML version (e.g. 1.0 is expected)
	*/
			void		TextDeclaration(const UTF16TextChar* version)
							{ this->TextDeclaration(WideString(version)); }

	/**	Write a SYSTEM DocType with root element and DTD pointed to by URI.

		@param root name of the root element, e.g. article
		@param URI identifier for the document type
	 */
	virtual void		DocType(const WideString& root, const WideString& URI) = 0;

	/**	Write a SYSTEM DocType with root element and DTD pointed to by URI.

		@param root name of the root element, e.g. article
		@param URI identifier for the document type
	 */
			void		DocType(const UTF16TextChar* root, const WideString& URI)
							{ this->DocType(WideString(root), URI); }

	/**	Write a SYSTEM DocType with root element and DTD pointed to by URI.

		@param root name of the root element, e.g. article
		@param URI identifier for the document type
	 */
			void		DocType(const WideString& root, const UTF16TextChar* URI)
							{ this->DocType(root, WideString(URI)); }

	/**	Write a SYSTEM DocType with root element and DTD pointed to by URI.

		@param root name of the root element, e.g. article
		@param URI identifier for the document type
	 */
			void		DocType(const UTF16TextChar* root, const UTF16TextChar* URI)
							{ this->DocType(WideString(root), WideString(URI)); }

	/**	Write a PUBLIC DocType with root element and DTD pointed to by URI and a name of public DTD.
	
		@param root name of the root element, e.g. article
		@param name public identifier
		@param URI identifier for the document type
	 */
	virtual void		DocType(const WideString& root, const WideString& name, const WideString& URI) = 0;

	/** Begin definition of an Internal DTD with root element.
		@param root name of the root element, e.g. article
		@param newLine whether to write new-line into stream after this content
	 */
	virtual void		BeginDocType(const WideString& root, bool16 newLine = kFalse) = 0;

	/** Begin definition of an Internal DTD with root element.
		@param root name of the root element, e.g. article
		@param newLine whether to write new-line into stream after this content
	 */
			void		BeginDocType(const UTF16TextChar* root, bool16 newLine = kFalse)
							{ this->BeginDocType(WideString(root), newLine); }

	/** Begin definition of an external SYSTEM DTD with root element
		@param root name of the root element, e.g. article
		@param systemIDLiteral SYSTEM ID literal
		@param newLine whether to write new-line into stream after this content
	*/
	virtual void		BeginDocType(const WideString& root, const WideString& systemIDLiteral, bool16 newLine = kFalse) = 0;

	/** Begin definition of an external PUBLIC DTD with root element
		@param root name of the root element, e.g. article
		@param publicIDLiteral PUBLIC ID literal
		@param systemIDLiteral SYSTEM ID literal
		@param newLine whether to write new-line into stream after this content
	*/
	virtual void		BeginDocType(const WideString& root, const WideString& publicIDLiteral, const WideString& systemIDLiteral, bool16 newLine = kFalse) = 0;

	/** Ends definition of an Internal DTD.
		@param newLine whether to write new-line into stream after this content
	 */
	virtual void		EndDocType(bool16 newLine = kFalse) = 0;

	/** Write a declaration for an ATTLIST..
		@param elementName name of the element, e.g. document
		@param attrDfns list of its attribute definitions
		@param 	newLine  whether to write new-line into stream after this content
	 */
	virtual void		WriteAttributeList(const WideString &elementName, const AttributeDfnList &dfns, bool16 newLine = kFalse) = 0;

	/** Write a declaration for an ATTLIST..
		@param elementName name of the element, e.g. document
		@param attrDfns list of its attribute definitions
		@param 	newLine  whether to write new-line into stream after this content
	 */
			void		WriteAttributeList(const UTF16TextChar* elementName, const AttributeDfnList &dfns, bool16 newLine = kFalse)
							{ this->WriteAttributeList(WideString(elementName), dfns, newLine); }

	/**	Begin an element type declaration. i.e. "<!ELEMENT elementName "
		@param elementName specifies name of element
		@param 	newLine  whether to write new-line into stream after this content
	 */
	virtual void		BeginElementTypeDecl(const WideString& elementName, bool16 newLine = kFalse) = 0;

	/**	Begin an element type declaration. i.e. "<!ELEMENT elementName "
		@param elementName specifies name of element
		@param 	newLine  whether to write new-line into stream after this content
	 */
			void		BeginElementTypeDecl(const UTF16TextChar* elementName, bool16 newLine = kFalse)
							{ this->BeginElementTypeDecl(WideString(elementName), newLine); }

	/**	End an element type declaration. i.e. ">"
		@param newLine whether to write new-line into stream after this content
	 */
	virtual void		EndElementTypeDecl(bool16 newLine = kFalse) = 0;

	/**	Begin a content model declaration. i.e. "("
		@param separator may optionally prepend a separator. i.e. ", (" Use kNone to add nothing
		@param 	newLine  whether to write new-line into stream after this content
	 */
	virtual void		BeginContentModelDecl(eContentParticleSeparator separator = kNone, bool16 newLine = kFalse) = 0;

	/**	End a content model declaration. i.e. ")+"
		@param occurrence occurrence of the content model
		@param newLine whether to write new-line into stream after this content
	 */
	virtual void		EndContentModelDecl(eContentParticleOccurrence occurrence = kExactlyOnce, bool16 newLine = kFalse) = 0;

	/**	Begin a mixed content model declaration. i.e. "(#PCDATA"
		@param separator may optionally prepend a separator. i.e. ", (#PCDATA" Use kNone to add nothing
		@param 	newLine  whether to write new-line into stream after this content
	 */
	virtual void		BeginMixedContentModelDecl(eContentParticleSeparator separator = kNone, bool16 newLine = kFalse) = 0;

	/**	End a mixed content model declaration. i.e. ")*"
		@param writeOccurrence whether to write the "*" occurrence. This should be kFalse only 
		when the PCDATA is the only content particle in a mixed content model
		@param newLine whether to write new-line into stream after this content
	 */
	virtual void		EndMixedContentModelDecl(bool16 writeOccurrence = kTrue, bool16 newLine = kFalse) = 0;

	/** Write a separator. i.e. " | "
		@param separator content particle separator
		@param 	newLine  whether to write new-line into stream after this content
	*/
	virtual void		WriteSeparator(eContentParticleSeparator separator, bool16 newLine = kFalse) = 0;

	/** Write a content particle. i.e. "contentParticleName+"
		@param contentParticleName content particle name
		@param occurrence content particle occurrence
		@param 	newLine  whether to write new-line into stream after this content
	*/
	virtual void		WriteContentParticle(const WideString& contentParticleName, eContentParticleOccurrence occurrence = kExactlyOnce, bool16 newLine = kFalse) = 0;

	/** Write a content particle. i.e. "contentParticleName+"
		@param contentParticleName content particle name
		@param occurrence content particle occurrence
		@param 	newLine  whether to write new-line into stream after this content
	*/
			void		WriteContentParticle(const UTF16TextChar* contentParticleName, eContentParticleOccurrence occurrence = kExactlyOnce, bool16 newLine = kFalse)
							{ this->WriteContentParticle(WideString(contentParticleName), occurrence, newLine); }

	/** Write a keyword. i.e. "#PCDATA"
		@param keyword keyword to write
		@param 	newLine  whether to write new-line into stream after this content
	*/
	virtual void		WriteKeyword(eKeyword keyword, bool16 newLine = kFalse) = 0;

	/** Begin an ATTLIST declaration. i.e. "<!ATTLIST elementName"
		@param elementName name of the element for the attributes
		@param 	newLine  whether to write new-line into stream after this content
	*/
	virtual void		BeginAttListDecl(const WideString& elementName, bool16 newLine = kFalse) = 0;

	/** Begin an ATTLIST declaration. i.e. "<!ATTLIST elementName"
		@param elementName name of the element for the attributes
		@param 	newLine  whether to write new-line into stream after this content
	*/
			void		BeginAttListDecl(const UTF16TextChar* elementName, bool16 newLine = kFalse)
							{ this->BeginAttListDecl(WideString(elementName), newLine); }

	/** End an ATTLIST declaration. i.e. ">"
		@param 	newLine  whether to write new-line into stream after this content
	*/
	virtual void		EndAttListDecl(bool16 newLine = kFalse) = 0;

	/** Write a name. i.e. "name"
		@param name name to write
		@param 	newLine  whether to write new-line into stream after this content
	*/
	virtual void		WriteName(const WideString& name, bool16 newLine = kFalse) = 0;

	/** Write a name. i.e. "name"
		@param name name to write
		@param 	newLine  whether to write new-line into stream after this content
	*/
			void		WriteName(const UTF16TextChar* name, bool16 newLine = kFalse)
							{ this->WriteName(WideString(name), newLine); }

	/** Write an attribute type. i.e. " CDATA"
		@param attType attribute type to write
		@param 	newLine  whether to write new-line into stream after this content
	*/
	virtual void		WriteAttributeType(eAttributeType attType, bool16 newLine = kFalse) = 0;

	/** Write an attribute value. i.e. ""true""
		@param attValue attribute value to write
		@param 	newLine  whether to write new-line into stream after this content
	*/
	virtual void		WriteAttributeValue(const WideString& attValue, bool16 newLine = kFalse) = 0;

	/** Write an attribute value. i.e. ""true""
		@param attValue attribute value to write
		@param 	newLine  whether to write new-line into stream after this content
	*/
			void		WriteAttributeValue(const UTF16TextChar* attValue, bool16 newLine = kFalse)
							{ this->WriteAttributeValue(WideString(attValue), newLine); }

	/** Begin an ENTITY declaration. i.e. "<!ENTITY entityName " or "<!ENTITY % entityName "
		@param entityName name of the entity
		@param generalEntity kTrue to write a general entity; kFalse to write parameter entity
		@param 	newLine  whether to write new-line into stream after this content
	*/
	virtual void		BeginEntityDecl(const WideString& entityName, bool16 generalEntity = kTrue, bool16 newLine = kFalse) = 0;

	/** Begin an ENTITY declaration. i.e. "<!ENTITY entityName " or "<!ENTITY % entityName "
		@param entityName name of the entity
		@param generalEntity kTrue to write a general entity; kFalse to write parameter entity
		@param 	newLine  whether to write new-line into stream after this content
	*/
			void		BeginEntityDecl(const UTF16TextChar* entityName, bool16 generalEntity = kTrue, bool16 newLine = kFalse)
							{ this->BeginEntityDecl(WideString(entityName), generalEntity, newLine); }

	/** End an ENTITY declaration. i.e. ">"
		@param 	newLine  whether to write new-line into stream after this content
	*/
	virtual void		EndEntityDecl(bool16 newLine = kFalse) = 0;

	/** Begin a NOTATION declaration. i.e. "<!NOTATION notationName "
		@param notationName name of the notation
		@param 	newLine  whether to write new-line into stream after this content
	*/
	virtual void		BeginNotationDecl(const WideString& notationName, bool16 newLine = kFalse) = 0;

	/** Begin a NOTATION declaration. i.e. "<!NOTATION notationName "
		@param notationName name of the notation
		@param 	newLine  whether to write new-line into stream after this content
	*/
			void		BeginNotationDecl(const UTF16TextChar* notationName, bool16 newLine = kFalse)
							{ this->BeginNotationDecl(WideString(notationName), newLine); }

	/** End a NOTATION declaration. i.e. ">"
		@param 	newLine  whether to write new-line into stream after this content
	*/
	virtual void		EndNotationDecl(bool16 newLine = kFalse) = 0;

	/** Write a literal enclosed in quotes. i.e. ""literal""
		@param literal literal to write
		@param wrapInQuotes whether to wrap the literal in quotes
		@param 	newLine  whether to write new-line into stream after this content
	*/
	virtual void		WriteLiteral(const WideString& literal, bool16 wrapInQuotes = kFalse, bool16 newLine = kFalse) = 0;

	/** Write a literal enclosed in quotes. i.e. ""literal""
		@param literal literal to write
		@param wrapInQuotes whether to wrap the literal in quotes
		@param 	newLine  whether to write new-line into stream after this content
	*/
			void		WriteLiteral(const UTF16TextChar* literal, bool16 wrapInQuotes = kFalse, bool16 newLine = kFalse)
							{ this->WriteLiteral(WideString(literal), wrapInQuotes, newLine); }

	/**	Use to write a new tag.
		@param tagName specifies name of tag
		@param newLine whether to write new-line into stream after this content
	 */
	virtual void		Push(const WideString& tagName, bool16 newLine = kFalse) = 0;

	/**	Use to write a new tag.
		@param tagName specifies name of tag
		@param newLine whether to write new-line into stream after this content
	 */
			void		Push(const UTF16TextChar* tagName, bool16 newLine = kFalse)
							{ this->Push(WideString(tagName), newLine); }

	/**	Use to write a new tag with attributes.

		@param tagName specifies name of tag
		@param attrs list of its attributes
		@param 	newLine  whether to write new-line into stream after this content
 	 */
	virtual void		PushWithAttributes(const WideString& tagName, const AttributeList& attrs, bool16 newLine = kFalse) = 0;

	/**	Use to write a new tag with attributes.

		@param tagName specifies name of tag
		@param attrs list of its attributes
		@param 	newLine  whether to write new-line into stream after this content
 	 */
			void		PushWithAttributes(const UTF16TextChar* tagName, const AttributeList& attrs, bool16 newLine = kFalse)
							{ this->PushWithAttributes(WideString(tagName), attrs, newLine); }

	/**	Use to write the end tag for the top tag on the stack and to remove it from the stack		
	
		@param newLine whether to write new-line into stream after this content
		@return kTrue if stream IO succeeds, kFalse otherwise
	 */
	virtual ErrorCode	Pop(bool16 newLine = kFalse) = 0;

	/**	Write will output data to stream at current position, and escape the standard 5 entities, unless a
		CData or PI section has been started with escaping off.
	
		@param data specifies content to write out
		@param escape kTrue if data to be escaped, kFalse otherwise
		@param newLine whether to write new-line into stream after this content 
	 */
	virtual void		Write(const WideString& data, bool16 newLine = kFalse, bool16 escape = kTrue) = 0;

	/**	Write will output data to stream at current position, and escape the standard 5 entities, unless a
		CData or PI section has been started with escaping off.
	
		@param data specifies content to write out
		@param escape kTrue if data to be escaped, kFalse otherwise
		@param newLine whether to write new-line into stream after this content 
	 */
	inline  void		Write(const UTF16TextChar* data, bool16 newLine = kFalse, bool16 escape = kTrue)
							{ this->Write(WideString(data), newLine, escape); }

	/**	WritePlatformText will output data to stream at current position, and escape the standard 5 entities,
	    unless a CData or PI section has been started with escaping off.
	
		@param data stream containing platform characters
		@param start stream offset of the first character to write
		@param count the number of characters to write
		@param escape kTrue if data to be escaped, kFalse otherwise
		@param newLine whether to write new-line into stream after this content 
	 */
	virtual void		WritePlatformText(IPMStream *data, int32 start, int32 count, bool16 newLine = kFalse, bool16 escape = kTrue) = 0;

	/**	Write an empty tag such as '&lt;foo/&gt;'
		@param tagName specifies name of tag to write
		@param newLine whether to write new-line into stream after this content
	 */
	virtual void		WriteEmpty(const WideString& tagName, bool16 newLine = kFalse) = 0;

	/**	Write an empty tag such as '&lt;foo/&gt;'
		@param tagName specifies name of tag to write
		@param newLine whether to write new-line into stream after this content
	 */
			void		WriteEmpty(const UTF16TextChar* tagName, bool16 newLine = kFalse)
							{ this->WriteEmpty(WideString(tagName), newLine); }

	/**	Write an empty tag with attributes such as '&lt;foo bar = true/&gt;'.	
		@param tag specifies tag name
		@param attrs list of attributes to write out
		@param newLine whether to write new-line into stream after this content
	 */
	virtual void		WriteEmptyWithAttributes(const WideString& tag, const AttributeList& attrs, bool16 newLine = kFalse) = 0;

	/**	Write an empty tag with attributes such as '&lt;foo bar = true/&gt;'.	
		@param tag specifies tag name
		@param attrs list of attributes to write out
		@param newLine whether to write new-line into stream after this content
	 */
			void		WriteEmptyWithAttributes(const UTF16TextChar* tag, const AttributeList& attrs, bool16 newLine = kFalse)
							{ this->WriteEmptyWithAttributes(WideString(tag), attrs, newLine); }
	

	/**	Comment will output a comment at the current stream position with no escaping of entities.
		@param comment specifies comment data to write out
		@param newLine whether to write new-line into stream after this content
	 */
	virtual void		Comment(const WideString& comment, bool16 newLine = kFalse) = 0;

	/**	Comment will output a comment at the current stream position with no escaping of entities.
		@param comment specifies comment data to write out
		@param newLine whether to write new-line into stream after this content
	 */
			void		Comment(const UTF16TextChar* comment, bool16 newLine = kFalse)
							{ this->Comment(WideString(comment), newLine); }
	

	/**	Begin a CData section. Data and subsequent calls to Write() will escape entities or not depending on bool.
	
		@param data content to write into CDATA section
		@param escape kTrue if standard entities to be escaped, kFalse otherwise
	 */
	virtual void     	BeginCData(const WideString& data, bool16 escape = kFalse) = 0;

	/**	Begin a CData section. Data and subsequent calls to Write() will escape entities or not depending on bool.
	
		@param data content to write into CDATA section
		@param escape kTrue if standard entities to be escaped, kFalse otherwise
	 */
			void     	BeginCData(const UTF16TextChar* data, bool16 escape = kFalse)
							{ this->BeginCData(WideString(data), escape); }
	
	/**	 End a CDataSection, with a newLine after if neccesary.
		@param newLine whether to write new-line into stream after this content
	 */
	virtual void		EndCData(bool16 newLine = kTrue) = 0;
	

	/**	Begin a Processing Instruction section.
		until EndCdata() is called. NewLine after the tag if necessary.
	
		@param piTarget application to which the instruction is directed
		@param piData data to pass through to target application
		@param newLine whether to write new-line into stream after this content
		@param escape kTrue if standard entities to be escaped, kFalse otherwise
	 */
	virtual void    	BeginPI(const WideString& piTarget, const WideString& piData, bool16 newLine = kFalse, bool16 escape = kFalse) = 0;

	/**	End a Processing Instruction, with a newLine after if neccesary		
		@param newLine whether to write new-line into stream after this content
	 */
	virtual void		EndPI(bool16 newLine = kFalse) = 0;
	
	//----- Formatting

	/**	Formatting related; indent level will determine how much to indent each write to the output stream, 
		only effective if Indent is on

		@param increase specifies whether to increase indent level or not
	 */
	virtual void		IndentLevel(bool increase) = 0;

	/**	Formatting related; enable indent. If on, each output operation is indented based on the current indent level
		@param on specifies whether to turn indenting on or off
	 */
	virtual void     	Indent(bool on) = 0;

	/** return whether indent is on or not
		@return bool16 kTrue if indent is on; kFalse otherwise
	*/
	virtual bool16		DoIndent(void) const = 0;

	/** output the current indent
	*/
	virtual void		WriteIndent(void) = 0;
	
	//----- Utility

	/**	Utility method to check status flag on this interface
		@return bool status flag, kSuccess if all going well
	 */
	virtual bool				CheckStatus() = 0;	

	/** Clear the character entity table
		@param addStandardXMLEntity specifies whether to add standard XML entity.
	*/
	virtual void	ResetEntityMap(bool16 addStandardXMLEntity = kTrue) = 0;

	/** Add character entity mappings ('&' to '&amp;', '<' to '&lt;' etc)
	      New mappings overwrite existing ones for the same character.
	*/
	virtual void AppendEntityMap( EntityMap& map) = 0;
	
};

#endif //__IXMLOUTSTREAM__
