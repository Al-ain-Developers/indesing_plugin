//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IHTTPServerInfo.h $
//  
//  Owner: Arvinder Singh
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
//  Copyright 2016 Adobe 
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
#ifndef __IHTTPServerInfo__
#define __IHTTPServerInfo__

#include "IPMUnknown.h"

#include "LinksID.h"
#include "URI.h"

/*
 AdobePatentID="P7137-US"
 AdobePatentID="P7225-US"
 AdobePatentID="P7609-US"
 */

/**
This interface contains URI related function for the connection. 
*/
class IHTTPServerInfo : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IHTTPSERVERINFO };
	
	/**
	Initializion function
	@param inAssetUri [IN] uri of the asset.
	@return kTrue if initialization is successful else kFalse
	*/
	virtual bool16 Init(const URI& inAssetUri) = 0;

	/** 
	Fetches the full server URI
	@return server URI
	*/
	virtual URI GetServerURI() const = 0;

	/**
	Fetches the authority of server URI
	@return server URI authority
	*/
	virtual WideString GetAuthority() const = 0;

	/**
	Fetches the protocol/scheme of server URI
	@return server URI scheme/protocol
	*/
	virtual WideString GetProtocol() const = 0;

	/*
	Fetches the complete asset URI for the given relative path of the asset
	@param inRelativeAssetPath [IN] asset path to get the complete uri.
	@return complete uri from the asset relative path.
	*/
	virtual URI GetCompleteAssetURI(const WideString& inRelativeAssetPath) const = 0;

};

#endif	// __IHTTPServerInfo__
