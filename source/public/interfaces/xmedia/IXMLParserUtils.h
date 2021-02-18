//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLParserUtils.h $
//  
//  Owner: Rich Gartland
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
#ifndef __IXMLParserUtils_h__
#define __IXMLParserUtils_h__

#include "Utils.h"
#include "XMLParserID.h"

class IIDXMLDOMDocument;
class ISAXServices;


class IIDXMLElement;
class XMLReference;
#include <map>
typedef std::map<XMLReference, K2Vector<int32> > HitMatches;
typedef std::map<WideString, WideString> PrefixToURIMap;

/**
General utilities for XMLParser
*/
class IXMLParserUtils : public IPMUnknown 
{
	public:
		enum	{kDefaultIID = IID_IXMLPARSERUTILS};
	
	/** 
	Used to create a new DOM Document

	NOTE: The caller of this method will be responsible for its destruction

	@param characterSize - Used to set the character encoding of the stream to parse
	@param uri - The uri to use for the resolver
	@param owner - The owner of this parser (used for error handling)

	return - A new DOM document that can be be used to build out an entire DOM
	*/
	virtual IIDXMLDOMDocument *CreateNewDOMDocument(const char* const uri = nil, ISAXServices *owner = nil) = 0;

	/**
	Creates a list of elements from the XML structure of the document, beginning with the rootElement,
	matching the xpaths in the input vector.
	@param xPaths A vector of XPath strings
	@param rootElement The IIDXMLElement to start from in the document's structure
	@param matches The pairs of XMLReferences and xpath indices matched
	@return kFalse for errors occurred, kTrue otherwise (does not necessarily indicate a match was found)
	*/
	virtual bool16 EvaluateXPathsForElement(const K2Vector<WideString>& xPaths, InterfacePtr<IIDXMLElement> rootElement, HitMatches& matches, PrefixToURIMap* prefixMap) const = 0;

	virtual PMString GetContentAtChild(const PMString &xml, const PMString & valueToFind, bool* pFoundIt = nil) = 0;
};

#endif