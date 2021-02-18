//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CSAXDOMSerializerHandler.h $
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
//  A default implementation of ISAXContentHandler.  This provides an empty implementation
//  of each method so that clients can only override those that they really care about.
//  
//========================================================================================

#pragma once
#ifndef __CSAXDOMSerializerHandler_h__
#define __CSAXDOMSerializerHandler_h__

#include "CPMUnknown.h"
#include "ISAXDOMSerializerHandler.h"

    /**
    An empty base class implementation of ISAXDOMSerializerHandler.
    Clients who wish to serialize DOM should implement new classes
    derived from this class.
    
    For a description of each method @see #ISAXDOMSerializerHandler
    */
class PUBLIC_DECL CSAXDOMSerializerHandler : public CPMUnknown<ISAXDOMSerializerHandler>
{
public:
	CSAXDOMSerializerHandler(IPMUnknown *boss);
	virtual ~CSAXDOMSerializerHandler();
	
	virtual void Register(ISAXDOMSerializerServices* saxServices, IPMUnknown *importer = nil);
	virtual bool16 HandlesSubElements() const;
	
	virtual void Characters(const WideString& chars, IIDXMLDOMNode* currentNode);

	virtual void StartDocument(ISAXDOMSerializerServices* saxServices);
	virtual void EndDocument();

	virtual void StartElement(const WideString& uri, const WideString& localname,
								const WideString& qname, ISAXAttributeList* attrs, IIDXMLDOMNode* currentNode);
	virtual void EndElement(const WideString& uri, const WideString& localname, const WideString& qname, IIDXMLDOMNode* currentNode);

	virtual void StartPrefixMapping(const WideString& prefix, const WideString& uri);
	virtual void EndPrefixMapping(const WideString& prefix);

	virtual void ProcessingInstruction(const WideString& target, const WideString& data, IIDXMLDOMNode* currentNode);
	virtual void ExtComment(const WideString& comment, IIDXMLDOMNode* currentNode);

protected:
	// Helper methods to easily extract basic types from attributes list.  If the attribute exists, it will extract
	// the basic type from it.  If it doesn't exist, it returns the default value you passed in.
	bool16		HasAttribute( ISAXAttributeList* attrs, const WideString& key);
	WideString	GetAttributeString( ISAXAttributeList* attrs, const WideString& key, const WideString& defaultValue = WideString());
	bool16 		GetAttributeBool( ISAXAttributeList* attrs, const WideString& key, bool16 defaultValue = kFalse);
	int32 		GetAttributeInt( ISAXAttributeList* attrs, const WideString& key, int32 defaultValue = 0);
};

#endif