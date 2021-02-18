//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CSAXContentHandler.h $
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
//  A default implementation of ISAXContentHandler.  This provides an empty implementation
//  of each method so that clients can only override those that they really care about.
//  
//========================================================================================

#pragma once
#ifndef __CSAXContentHandler_h__
#define __CSAXContentHandler_h__

#include "CPMUnknown.h"
#include "ISaxContentHandler.h"

    /**
    A empty base class implementation of ISAXContentHandler.
    Clients who wish to parse XML content should implement new classes
    derived from this class.

    For a description of each method @see #ISAXContentHandler
    */
#ifdef __clang__
template class PUBLIC_DECL CPMUnknown<ISAXContentHandler>;
#endif

class PUBLIC_DECL CSAXContentHandler : public CPMUnknown<ISAXContentHandler>
{
public:
	CSAXContentHandler(IPMUnknown *boss);
	virtual ~CSAXContentHandler();

	virtual void Register(ISAXServices* saxServices, IPMUnknown *importer = nil);
	virtual bool16 HandlesSubElements() const;

	virtual void Characters(const WideString& chars);

	virtual void StartDocument(ISAXServices* saxServices);
	virtual void EndDocument();

	virtual void StartElement(const WideString& uri, const WideString& localname,
								const WideString& qname, ISAXAttributes* attrs);
	virtual void EndElement(const WideString& uri, const WideString& localname, const WideString& qname);

	virtual void StartPrefixMapping(const WideString& prefix, const WideString& uri);
	virtual void EndPrefixMapping(const WideString& prefix);

	virtual void IgnorableWhitespace(const WideString& chars);
	virtual void ProcessingInstruction(const WideString& target, const WideString& data);
	virtual void SkippedEntity(const WideString& name);
	virtual void ExtComment(const WideString& comment);
	virtual void ExtXMLDecl(const WideString& version, const WideString& encoding,
								const WideString& standalone, const WideString& actualEncoding);

	virtual void SetDocumentLocator(ISAXLocator* locator);
	virtual ISAXLocator* GetDocumentLocator() const;

protected:
	// Helper methods to easily extract basic types from attributes list.  If the attribute exists, it will extract
	// the basic type from it.  If it doesn't exist, it returns the default value you passed in.
	bool16		HasAttribute( ISAXAttributes* attrs, const PMString& key);
	bool16		HasAttribute( ISAXAttributes* attrs, const WideString& key);

	PMString		GetAttributeString( ISAXAttributes* attrs, const PMString& key, const PMString& defaultValue = "");
	WideString	GetAttributeString( ISAXAttributes* attrs, const WideString& key, const WideString* defaultValue = nil);

	bool16 		GetAttributeBool( ISAXAttributes* attrs, const PMString& key, bool16 defaultValue = kFalse);
	bool16 		GetAttributeBool( ISAXAttributes* attrs, const WideString& key, bool16 defaultValue = kFalse);

	int32 		GetAttributeInt( ISAXAttributes* attrs, const PMString& key, int32 defaultValue = 0);
	int32 		GetAttributeInt( ISAXAttributes* attrs, const WideString& key, int32 defaultValue = 0);

private:
	ISAXLocator* fLocator;
};

#endif
