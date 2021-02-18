//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IHTTPLinkUtils.h $
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
#ifndef __IHTTPLinkUtils__
#define __IHTTPLinkUtils__

#include "IPMUnknown.h"

#include "Utils.h"
#include "ILink.h"
#include "ILinkResource.h"
#include "IDataBase.h"
#include "IDatabaseSnapshot.h"

#include "string"
#include "WideString.h"


class IHTTPLinkResourceConnection;
class IHTTPLinkResourceServerCache;

/*
 AdobePatentID="P7137-US"
 AdobePatentID="P7225-US"
 AdobePatentID="P7609-US"
 */

/**
Experimental interface - will be modified/documented in future.
*/
class IHTTPLinkUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IHTTPLINKUTILS };

	/**
	API to get the URI for original asset based on the information in the input UIDRef
	@param  iLinkResource [IN]	Input Link Resource
	@param	URI			  [OUT] The asset original URI for the input Link Resource
	@return kTrue if the operation is successful else kFalse
	*/
	virtual bool16 GetOriginalURIForResource(const ILinkResource* iLinkResource, URI& uri) const = 0;

	/**
	API to get the URI for rendition of the original asset based on the information in the input UIDRef
	@param  iLinkResource [IN]	Input Link Resource
	@param	URI			  [OUT] The rendition URI for the input Link Resource
	@return kTrue if the operation is successful else kFalse
	*/
	virtual bool16 GetRenditionURIForResource(const ILinkResource* iLinkResource, URI& uri) const = 0;

	/**
	Gets Short Resource Name for the input URI
	@param uri [IN] uri of the asset.
	@return Short Name.
	*/
	virtual WideString GetShortName(const URI& uri) const = 0;
	
	/**
	Utility API to change WideString to AString
	@param wString [IN] input WideString.
	@return Output AString.
	*/
	virtual AString WideStringToAString(const WideString& wString) const = 0;

	/**
	Fetches the server URI for the asset URI
	@param inAssetUri [IN] uri of the asset.
	@return server URI for the asset.
	*/
	virtual URI GetServerURI(const URI& inAssetUri) const = 0;

	/**
	If the URI is HTTP Link Supported
	@param uri [IN] uri of the asset.
	@return kTrue if the uri is  Http Link supported else return  kFalse.
	*/
	virtual bool16 IsHTTPLinksSupportedURI(const URI& uri) const = 0;

	/**
	Checks if Database is valid for the HTTP Link
	@param db [IN] database for HTTP Link.
	** return kTrue if the db is valid else return  kFalse.
	*/
	virtual bool16 IsValidDataBaseForHttpLink(IDataBase *db) const = 0;


	/**
	Fetches the Http Link resource connection on the given uri.
	@param uri [IN] uri of the asset.
	@return Http Link resource Connection on the given uri.
	*/
	virtual InterfacePtr<IHTTPLinkResourceConnection> GetHTTPLinkResourceConnection(const URI& uri) const = 0;

	/**
	Fetches the Http Link resource Server cache on the given uri. 
	@param uri [IN] uri of the asset.
	@return Http Link resource Server cache on the given uri.
	*/
	virtual InterfacePtr<IHTTPLinkResourceServerCache> GetHTTPLinkResourceServerCache(const URI& uri) const = 0;

	virtual void ReadWriteSnapshotForBackgroundThread(DatabaseSnapshotPtr db, bool16 isReadingMode) const = 0;

	// Do not call it from outside world, this is for our internal purpose only.
	virtual void ShutdownHTTPLinksSubsystem() const = 0;

	/**
	Fetches the full path of HTTP Asset Cache
	@return HTTP Asset Cache Path.
	*/
	virtual PMString GetHTTPAssetCachePath() const = 0;
};

#endif	// __IHTTPLinkUtils__
