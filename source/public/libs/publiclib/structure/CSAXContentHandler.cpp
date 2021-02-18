//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/structure/CSAXContentHandler.cpp $
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
//  
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#include "VCPublicHeaders.h"

// ----- Interface Includes -----
#include "ShuksanBravo.h"
#include "CSAXContentHandler.h"
#include "ISAXAttributes.h"

//========================================================================================
// METHODS CSAXContentHandler
//========================================================================================

//----------------------------------------------------------------------------------------
// CSAXContentHandler::CSAXContentHandler
//----------------------------------------------------------------------------------------

CSAXContentHandler::CSAXContentHandler(IPMUnknown *boss) :
	CPMUnknown<ISAXContentHandler>(boss),
	fLocator(nil)
{
}


//----------------------------------------------------------------------------------------
// CSAXContentHandler::~SAXAttributes
//----------------------------------------------------------------------------------------

CSAXContentHandler::~CSAXContentHandler()
{
}

//----------------------------------------------------------------------------------------
// CSAXContentHandler::Register
//----------------------------------------------------------------------------------------

void CSAXContentHandler::Register(ISAXServices* saxServices, IPMUnknown *importer)
{
}

//----------------------------------------------------------------------------------------
// CSAXContentHandler::Characters
//----------------------------------------------------------------------------------------

void CSAXContentHandler::Characters(const WideString& chars)
{
}


//----------------------------------------------------------------------------------------
// CSAXContentHandler::StartDocument
//----------------------------------------------------------------------------------------

void CSAXContentHandler::StartDocument(ISAXServices* saxServices)
{
}

//----------------------------------------------------------------------------------------
// CSAXContentHandler::EndDocument
//----------------------------------------------------------------------------------------

void CSAXContentHandler::EndDocument()
{
}

//----------------------------------------------------------------------------------------
// CSAXContentHandler::StartElement
//----------------------------------------------------------------------------------------

void CSAXContentHandler::StartElement(const WideString& uri, const WideString& localname, const WideString& qname, ISAXAttributes* attrs)
{
}


//----------------------------------------------------------------------------------------
// CSAXContentHandler::EndElement
//----------------------------------------------------------------------------------------

void CSAXContentHandler::EndElement(const WideString& uri, const WideString& localname, const WideString& qname )
{
}

//----------------------------------------------------------------------------------------
// CSAXContentHandler::EndElement
//----------------------------------------------------------------------------------------

bool16 CSAXContentHandler::HandlesSubElements( ) const
{
	return kFalse;
}

//----------------------------------------------------------------------------------------
// CSAXContentHandler::StartPrefixMapping
//----------------------------------------------------------------------------------------

void CSAXContentHandler::StartPrefixMapping(const WideString& prefix, const WideString& uri)
{
}

//----------------------------------------------------------------------------------------
// CSAXContentHandler::EndPrefixMapping
//----------------------------------------------------------------------------------------

void CSAXContentHandler::EndPrefixMapping(const WideString& prefix)
{
}


//----------------------------------------------------------------------------------------
// CSAXContentHandler::ExtComment
//----------------------------------------------------------------------------------------

void CSAXContentHandler::ExtComment(const WideString& comment)
{
}


//----------------------------------------------------------------------------------------
// CSAXContentHandler::ExtComment
//----------------------------------------------------------------------------------------

void CSAXContentHandler::ExtXMLDecl(const WideString& version, const WideString& encoding, const WideString& standalone, const WideString& actualEncoding)
{
}


//----------------------------------------------------------------------------------------
// CSAXContentHandler::IgnorableWhitespace
//----------------------------------------------------------------------------------------

void CSAXContentHandler::IgnorableWhitespace(const WideString& chars)
{
}

//----------------------------------------------------------------------------------------
// CSAXContentHandler::SkippedEntity
//----------------------------------------------------------------------------------------

void CSAXContentHandler::SkippedEntity(const WideString& name)
{
}

//----------------------------------------------------------------------------------------
// CSAXContentHandler::ProcessingInstruction
//----------------------------------------------------------------------------------------

void CSAXContentHandler::ProcessingInstruction(const WideString& target, const WideString& data)
{
}

//----------------------------------------------------------------------------------------
// CSAXContentHandler::SetDocumentLocator
//----------------------------------------------------------------------------------------

void CSAXContentHandler::SetDocumentLocator(ISAXLocator* locator)
{
	fLocator = locator;
}

//----------------------------------------------------------------------------------------
// CSAXContentHandler::GetDocumentLocator
//----------------------------------------------------------------------------------------

ISAXLocator* CSAXContentHandler::GetDocumentLocator() const
{
	return fLocator;
}

//----------------------------------------------------------------------------------------
// CSAXContentHandler::HasAttribute
//----------------------------------------------------------------------------------------
bool16 CSAXContentHandler::HasAttribute( ISAXAttributes* attrs, const PMString& key)
{
	return attrs->HasAttribute(key);
}

bool16 CSAXContentHandler::HasAttribute( ISAXAttributes* attrs, const WideString& key)
{
 return attrs->HasAttribute(key);
}

//----------------------------------------------------------------------------------------
// CSAXContentHandler::GetAttributeString
//----------------------------------------------------------------------------------------
PMString CSAXContentHandler::GetAttributeString( ISAXAttributes* attrs, const PMString& key, const PMString& defaultValue)
{
	return attrs->GetAttributeString(key, defaultValue);
}

WideString CSAXContentHandler::GetAttributeString( ISAXAttributes* attrs, const WideString& key, const WideString* pDefaultValue)
{
	return attrs->GetAttributeString(key, pDefaultValue);
}

//----------------------------------------------------------------------------------------
// CSAXContentHandler::GetAttributeBool
//----------------------------------------------------------------------------------------
bool16 CSAXContentHandler::GetAttributeBool( ISAXAttributes* attrs, const PMString& key, bool16 defaultValue)
{
	return attrs->GetAttributeBool(key, defaultValue);
}

bool16 CSAXContentHandler::GetAttributeBool( ISAXAttributes* attrs, const WideString& key, bool16 defaultValue)
{
	return attrs->GetAttributeBool(key, defaultValue);
}

//----------------------------------------------------------------------------------------
// CSAXContentHandler::GetAttributeInt
//----------------------------------------------------------------------------------------
int32 CSAXContentHandler::GetAttributeInt( ISAXAttributes* attrs, const PMString& key, int32 defaultValue)
{
	return attrs->GetAttributeInt(key, defaultValue);
}

int32 CSAXContentHandler::GetAttributeInt( ISAXAttributes* attrs, const WideString& key, int32 defaultValue)
{
	return attrs->GetAttributeInt(key, defaultValue);
}
