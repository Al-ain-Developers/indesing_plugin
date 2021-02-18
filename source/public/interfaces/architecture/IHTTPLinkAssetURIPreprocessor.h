//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IHTTPLinkAssetURIPreprocessor.h $
//  
//  Owner: Nitin Kumar
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 2017 Adobe 
//  All Rights Reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in 
//  accordance with the terms of the Adobe license agreement accompanying 
//  it. If you have received this file from a source other than Adobe, 
//  then your use, modification, or distribution of it requires the prior 
//  written permission of Adobe.
//  
//========================================================================================
#pragma once
#ifndef __IHTTPLinkAssetURIPreprocessor__
#define __IHTTPLinkAssetURIPreprocessor__

#include "IPMUnknown.h"
#include "LinksID.h"

#include "URI.h"

/*
 AdobePatentID="P7225-US"
 AdobePatentID="P7609-US"
 */

/**
Experimental interface - will be modified/documented in future.
*/
class IHTTPLinkAssetURIPreprocessor : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IHTTPLINKASSETURIPREPROCESSOR };
	/*
	Creates a URI which has Tagname combined with it.
	@param inURI	[IN]  URI of the text fragment link.
	@param tagName	[IN]  input tag name.
	@param outURI	[OUT] output URI after incorporating the tag name of the text fragment link with the input URI.
	@return if the operation is successful else kFalse 
	*/
	virtual bool16 GetTextFragmentLinkCreationURI(const URI& inURI, const WideString* tagName, URI& outURI) = 0;

	/*Decouple the tagName from the URI if present. 
	@param inURI	[IN] inURI of the text fragment link with tag name as input.
	@param outURI   [OUT] URI without a tagname as output
	@return kTrue if the operation is successful else kFalse
	*/
	virtual bool16 GetXMLHrefAttributeURI(const URI& inURI, URI& outURI) = 0;
	
};

#endif	// __IHTTPLinkAssetURIPreprocessor__
