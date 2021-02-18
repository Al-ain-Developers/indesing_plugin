//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IHTTPLinkResourceServerCacheStorage.h $
//  
//  Owner: Sumit Pandey
//  
//  $Author: vans $
//  
//  $DateTime: 2020/11/06 05:06:09 $
//  
//  $Revision: #1 $
//  
//  $Change: 1088554 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================
#pragma once
#ifndef __HTTPLinkResourceServerCacheStorage__
#define __HTTPLinkResourceServerCacheStorage__

#include "IPMUnknown.h"
#include "IHTTPLinkCachedAssetEntry.h"
#include "LinksID.h"
#include "URI.h"
#include <memory>

/*
AdobePatentID="P7137-US"
*/

// =============================================================================
//		* HTTPLinkServerCacheStorage											
// =============================================================================

class IHTTPLinkResourceServerCacheStorage : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IHTTPLINKRESOURCESERVERCACHESTORAGE };

	/**
	Get entry from URI
	@param uri [IN] input URI.
	@return entry object corressponding to URI
	*/
	virtual std::shared_ptr<IHTTPLinkCachedAssetEntry> GetEntry(URI uri) = 0;

	/**
	Get entry corresponding to given URI
	@param uri [IN] input URI.
	@return is delete successful
	*/
	virtual bool16 RemoveEntry(URI uri) = 0;

	/**
	Get entry corresponding to given URI
	@param uri [IN] input URI.
	@param assetCurrentAttributes [IN] asset current attributes.
	@return if add successful
	*/
	virtual bool16 AddEntry(URI uri, const IHTTPLinkResourceServerAPIWrapper::AssetStatusWithMetadataPtr  assetCurrentAttributes,
		const IDFile& cachedFilePath) = 0;

	/**
	Get if entry is stale or not
	@param uri [IN] input URI.
	@param assetCurrentAttributes [IN] asset current attributes.
	@return is entry stale
	*/

	virtual bool16 IsStale(URI uri, const IHTTPLinkResourceServerAPIWrapper::AssetMetadataPtr  assetCurrentAttributes) = 0;

	/**
	Purge cache 
	@Param num [IN} number of entries to purge
	@return True of purge successful
	*/
	virtual bool16 Purge(int num = -1) = 0;

	/**
	Get number of entries in cache
	@return number for entries
	*/
	virtual int64 GetNumEntries() = 0;

	// See if entry is present or not
	/**
	Returns true if entry exists
	@param uri [IN] input URI.
	@return true if entry exists in cache
	*/
	virtual bool16 Exists(URI uri) = 0;


	virtual void ReadWriteSnapshotForBackgroundThread(IPMStream *s) = 0;
};

#endif // __HTTPLinkResourceServerCacheStorage__
