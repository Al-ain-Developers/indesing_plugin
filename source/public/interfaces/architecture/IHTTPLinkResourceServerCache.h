//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IHTTPLinkResourceServerCache.h $
//  
//  Owner: Sanyam Jain
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
#ifndef __IHTTPLinkResourceServerCache__
#define __IHTTPLinkResourceServerCache__

#include "IPMUnknown.h"
#include "IHTTPLinkCachedAssetEntry.h"
#include "LinksID.h"
#include "HTTPLinkSubsystemTypes.h"
#include "URI.h"
#include "IHTTPLinkResourceServerAPIWrapper.h"

/*
 AdobePatentID="P7137-US"
 AdobePatentID="P7225-US"
 AdobePatentID="P7609-US"
 */

/**
 This interface provides deals with caching mechanism for files and metadata for HTTP links.
 This interface is responsible for storing asset metadata. Ideally it should persist across the session.
 Also it should clear cache and metadata also, so that it doesn't bloat.
 
 To subclass create a boss based on kHTTPAssetLinkResourceServerHelperBoss with the implementation of this
 interface. And return this connection instance from the IHTTPLinkSubsystemObjectFactory.
*/
class IHTTPLinkResourceServerCache : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IHTTPLINKRESOURCESERVERCACHE };

	/**
	Asset Download Progress callback
	@param inUri				[IN]  Input URI whose download progress is to be retrieved
	@param inState				[IN]  Download state for the given input URI
	@param inProgress			[IN]  Download progress for the asset corresponding to input URI
	*/
	typedef boost::function<void(
		const URI& inUri, 
		const HTTPLinkSubsystemTypes::HTTPAssetDownloadState& inState,
		const float inProgress)> AssetDownloadProgressCallback;

	/**
	Asset Download Completion callback
	@param inUri				[IN]  Input URI whose download progress is to be retrieved
	@param inState				[IN]  Download state for the given input URI
	@param cachedAssetEntry		[IN]  Cached Entry for the given uri.
	*/
	typedef boost::function<void(
		const URI& inUri,
		const HTTPLinkSubsystemTypes::HTTPAssetDownloadState& inState,
		std::shared_ptr<IHTTPLinkCachedAssetEntry> cachedAssetEntry)> AssetDownloadCompletionCallback;

	/**
	Initializes the HTTP Link Resource Server Cache
	@return kTrue if the initialization is successful
	*/
	virtual bool16 Initialize() = 0;

	/**
	Shuts down the HTTP Link Resource Server Cache
	@return kTrue if the shutdown is successful
	*/
	virtual bool16 Shutdown() = 0;

	/**
	Fetches the the cached entry of the file downloaded for the input URI.
	@param inUri						[IN]  input Uri.
	@param inDownloadIfMissing			[IN]  asset corresponding to input Uri requres download or not.
	@param inDownloadMode				[IN]  sync/async mode.
	@param downloadProgressCallback		[IN]  download progress callback
	@param downloadCompletionCallback	[IN]  download completion callback
	@return CachedAssetEntry
	*/
	virtual std::shared_ptr<IHTTPLinkCachedAssetEntry> GetCachedAssetEntry(const URI& inUri,
									  bool16 inDownloadIfMissing = kTrue,
									  HTTPLinkSubsystemTypes::AssetDownloadMode inDownloadMode = HTTPLinkSubsystemTypes::kAssetDownloadMode_Sync,
									  IHTTPLinkResourceServerCache::AssetDownloadProgressCallback downloadProgressCallback = NULL,
									  IHTTPLinkResourceServerCache::AssetDownloadCompletionCallback downloadCompletionCallback = NULL) = 0;

	/**
	Invalidate the cache entry of the file downloaded for the input URI.
	@param inUri [IN]  inUri.
	@return kTrue on success else kFalse.
	*/
	virtual bool16 InvalidateCacheForURI(const URI& inUri) = 0;

	/**
	Checks if the cached asset entry is stale
	@param inUri				[IN]  input URI for the cached asset entry.
	@param serverAssetAttribute [IN]  current HTTP Asset Attribute.
	@return kTrue if cached asset entry is stale else kFalse.
	*/
	virtual bool16 IsCachedAssetEntryStale(const URI& inUri, const IHTTPLinkResourceServerAPIWrapper::AssetMetadataPtr assetCurrentAttributes) = 0;

	/**
	Purges the cache.
	@param forcePurgeAll [IN] true if we want forceful purging.
	@return kTrue on success else kFalse.
	*/
	virtual bool16 PurgeCache(bool16 forcePurgeAll = kFalse) = 0;

	/**
	Gets the download state for the input URI.
	@param inUri [IN] input URI.
	@return download state for the uri
	*/
	virtual HTTPLinkSubsystemTypes::HTTPAssetDownloadState GetDownloadState(const URI& inUri) = 0;

	/**
	Used when snapshot is created for the object for running in background thread. Snapshots are used in
     some of the InDesign workflows like PDF export, to pass objects for processing in background thread.
     In this function, object should write relevant data into stream or read from it to create necessary data
     depending on type of stream.
     @param s stream for reading/writing object's data
	*/
	virtual void ReadWriteSnapshotForBackgroundThread(IPMStream* s) = 0;
};

#endif	// __IHTTPLinkResourceServerCache__
