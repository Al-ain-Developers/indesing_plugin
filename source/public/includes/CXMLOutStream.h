//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CXMLOutStream.h $
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

#pragma once
#ifndef __CXMLOutStream__
#define __CXMLOutStream__

#include "IXMLOutStream.h"
#include "CPMUnknown.h"	

#include "K2Stack.h"
#include "K2Vector.h"
#include "KeyValuePair.h"
#include "UTF16TextCharStreamBuf.h"


#pragma export on
	
//----------------------------------------------------------------------------------------
// CLASS XMLStream - base implementation of IXMLOutStream
//----------------------------------------------------------------------------------------
	
class PUBLIC_DECL CXMLOutStream : public CPMUnknown<IXMLOutStream>
{
public:
	
	
	CXMLOutStream(IPMUnknown* boss);						  
	virtual ~CXMLOutStream();

	typedef K2::stack< WideString, K2Vector<  WideString > > TagStack;
		
	//----- Stream
	// must be overriden by derived classes. Call Initialize on Open() and Terminante on Close()
	
	virtual	bool16	Open(eEncodingType encoding = kUTF16, bool16 stripInvalid = kTrue) = 0;
	virtual void	Close() = 0;
	
	virtual ErrorCode	Flush();
	// force all pending writes to happen
	
	//----- Standard elements and data  
	
	virtual void		DocHeader(const WideString& version, bool16 standalone);
	// Write the XML header for this document
	virtual void		TextDeclaration(const WideString& version);
	// Write the XML text declaration
	virtual void		DocType(const WideString& root, const WideString& URI);
	// Write a SYSTEM DocType with root element
	// and DTD pointed to by URI (auto adds quotes)
	virtual void		DocType(const WideString& root, const WideString& name, const WideString& URI);
	// Write a PUBLIC DocType with root element (auto adds brackets)
	// and DTD pointed to by URI (auto adds quotes) and a name of public DTD (auto adds quotes)
	virtual void		BeginDocType(const WideString& root, bool16 newLine);
	// Begin definition of an Internal DTD with root element.
	virtual void		BeginDocType(const WideString& root, const WideString& systemIDLiteral, bool16 newLine);
	// Begin definition of an external SYSTEM DTD with root element.
	virtual void		BeginDocType(const WideString& root, const WideString& publicIDLiteral, const WideString& systemIDLiteral, bool16 newLine);
	// Begin definition of an external PUBLIC DTD with root element.
	virtual void		EndDocType(bool16 newLine);
	// Ends definition of an Internal DTD.
	virtual void		WriteAttributeList(const WideString &elementName, const AttributeDfnList &dfns, bool16 newLine);	
	// Write a declaration for an ATTLIST.

	virtual void		BeginElementTypeDecl(const WideString& elementName, bool16 newLine);
	// Begin an element type declaration. i.e. "<!ELEMENT elementName "
	virtual void		EndElementTypeDecl(bool16 newLine);
	// End an element type declaration. i.e. ">"
	virtual void		BeginContentModelDecl(eContentParticleSeparator separator, bool16 newLine);
	// Begin a content model declaration. i.e. ", ("
	virtual void		EndContentModelDecl(eContentParticleOccurrence occurrence, bool16 newLine);
	// End a content model declaration. i.e. ")+"
	virtual void		BeginMixedContentModelDecl(eContentParticleSeparator separator, bool16 newLine);
	// Begin a mixed content model declaration. i.e. ", (#PCDATA"
	virtual void		EndMixedContentModelDecl(bool16 writeOccurrence, bool16 newLine);
	// End a mixed content model declaration. i.e. ")*"
	virtual void		WriteSeparator(eContentParticleSeparator separator, bool16 newLine);
	// Write separator
	virtual void		WriteContentParticle(const WideString& contentParticleName, eContentParticleOccurrence occurrence, bool16 newLine);
	// Write content particle
	virtual void		WriteKeyword(eKeyword keyword, bool16 newLine);
	// Write a keyword
	virtual void		BeginAttListDecl(const WideString& elementName, bool16 newLine);
	// Begin an ATTLIST declaration
	virtual void		EndAttListDecl(bool16 newLine);
	// End an ATTLIST declaration
	virtual void		WriteName(const WideString& name, bool16 newLine);
	// Write a name
	virtual void		WriteAttributeType(eAttributeType attType, bool16 newLine);
	// Write an attribute type
	virtual void		WriteAttributeValue(const WideString& attValue, bool16 newLine);
	// Write an attribute value
	virtual void		BeginEntityDecl(const WideString& entityName, bool16 generalEntity, bool16 newLine);
	// Begin an ENTITY declaration. i.e. "<!ENTITY entityName " or "<!ENTITY % entityName "
	virtual void		EndEntityDecl(bool16 newLine);
	// End an ENTITY declaration. i.e. ">"
	virtual void		WriteLiteral(const WideString& literal, bool16 wrapInQuotes, bool16 newLine);
	// Write literal. i.e. ""literal""
	virtual void		BeginNotationDecl(const WideString& notationName, bool16 newLine);
	// Begin a NOTATION declaration. i.e. "<!NOTATION notationName "
	virtual void		EndNotationDecl(bool16 newLine);
	// End a NOTATION declaration. i.e. ">"

	virtual void		Push(const WideString& tagName, bool16 newLine);
	// Use push to write a new tag and optional data after it, standard
	// entities are escaped.
	virtual void		PushWithAttributes(const WideString& tagName, const AttributeList& attrs, bool16 newLine);
	// Use push to write a new tag with attributes and optional data after it,
	//standard entities are escaped.
	virtual ErrorCode	Pop(bool16 newLine);
	// Use pop to write the end tag for the top tag on the stack and to remove
	//  it from the stack		
	virtual void		Write(const WideString& data, bool16 newLine, bool16 escape );
	// Write will output data to stream at current position, and escape
	// the standard 5 entities, unless a CData or PI section has been started
	// with escaping off
	virtual void		WritePlatformText(IPMStream *data, int32 start, int32 count, bool16 newLine = kFalse, bool16 escape = kTrue);
	// WritePlatformText will output data to stream at current position, and escape
	// the standard 5 entities, unless a CData or PI section has been started
	// with escaping off
	virtual void		WriteEmpty(const WideString& tagName, bool16 newLine);
	// Write an empty tag such as '<foo/>'
	virtual void		WriteEmptyWithAttributes(const WideString& tag, const AttributeList& attrs, bool16 newLine);
	// Write an empty tag with attributes such as '<foo bar = true/>'		
	virtual void		Comment(const WideString& comment, bool16 newLine);
	// Comment will output a comment at the current stream position
	// with no escaping of entities
	
	virtual void     	BeginCData(const WideString& data, bool16 escape);
	// Begin a CData section data and subsequent calls to Write() will escape entities or not
	// depending on bool - escape.
	virtual void		EndCData(bool16 newLine);
	// end a CDataSection, with a newLine after if neccesary.
	
	virtual void    	BeginPI(const WideString& piTarget, const WideString& piData, bool16 newLine, bool16 escape);
	// Begin a Processing Instruction section.
	// until EndCdata() is called. NewLine after the tag if necessary
	virtual void		EndPI(bool16 newLine);
	// end a Processing Instruction, with a newLine after if neccesary		
	
	
	//----- Formatting
	
	virtual void		IndentLevel(bool increase);
	// Indent level will determine how much to indent each write
	// to the output stream, only effective if Indent is on
	virtual void     	Indent(bool on);
	// If on, each output operation is indented based on the current indent level
	virtual bool16		DoIndent(void) const;
	// whether indent is on
	virtual void		WriteIndent(void);
	// output the current indent
	
	virtual void	ResetEntityMap(bool16 addStandardXMLEntity = kTrue);
	//  Clears Entity map & resets the "default" set of mappings.
	
	virtual void AppendEntityMap( EntityMap& map);
	// Add Character Entity References 

	//----- Utility
	virtual bool		CheckStatus();

	

protected:

	//-----
	// Set-up
	// 	Derived classes must call these methods before use, and before destruction of the stream
	//  to ensure that all data output is properly flushed. This call permanately sets the encoding
	//  type of the stream.
	
	virtual ErrorCode			Initialize(std::streambuf* destBuf, eEncodingType encoding = kUTF16, bool16 stripInvalid = kTrue, bool16 showCannotEncodeAlert = kFalse);
	// Use to initialize the stream with the indicated conversion, outputing result to destBuf
	virtual ErrorCode			Terminate();
	// Call before the destruction of destBuf passed in to Initialize(). 
	// After call to terminate, stream is no longer availabe for any output
	
	virtual ErrorCode			sputnEsc(const WideString& source, bool16 bJustWriteIt = kFalse);
	// Writes to the stream, escaping entities, if bJustWriteIt is set don't try and translate or enclose characters in PIs

private:
	
			bool16				IsValidXMLChar(UTF16TextChar c);		
			void				EncodeChar(UTF16TextChar charToEncode);
			bool16				SubstituteValidChar(UTF16TextChar& c);		
			void				WriteOccurrence(eContentParticleOccurrence occurrence);
			void				EscAttrValueChars(const WideString& source, WideString& dest);
			void				InsertToEscBuf(int32& index, UTF16TextChar c);

private:
		
	K2::UTF16TextCharStreamBuf*	fConvBuf;
	std::streambuf*		fFinalBuf;		
	
	TagStack			fTags;
	
	EntityMap			fEntities;
	EntityMap			fAttrEntities;
	UTF16TextChar*		fEscBuf;
	int32				fEscLen;
	
	int32				fIndentLevel;	
	bool				fDoIndent;
	eEncodingType		fEncoding;
	bool16				fCData;
	bool16				fPI;
	bool16              fDoEscape;
	bool16				fStrip;
	bool16				fShowCannotEncodeAlert;	// display an alert if characters cannot be encoded

	bool16				fInitialized;	// this flag check internal integrity
};

#pragma export off

#endif //__CXMLOutStream
