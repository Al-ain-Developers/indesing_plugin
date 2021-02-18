//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IHTTPAssetDownloadManager.h $
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
#ifndef __IHTTPAssetDownloadManager__
#define __IHTTPAssetDownloadManager__

#include "IPMUnknown.h"
#include "LinksID.h"
#include "HTTPLinkSubsystemTypes.h"
#include "URI.h"

#include "boost/config.hpp" 
#include "boost/shared_ptr.hpp" 
#include "boost/function.hpp" 

/*
 AdobePatentID="P7137-US"
 AdobePatentID="P7225-US"
 AdobePatentID="P7609-US"
*/

/**
IHTTPAssetDownloadManager manages downloads for http link assets(see IHTTPLinkSubsystemObjectFactory.h
 for more details). It is called when specific asset is not found in cache from IHTTPLinkResourceServerCache.
 Include this interface on http asset link resource server helper boss which is registered as
 kHTTPAssetLinkResourceServerHelperBoss. For custom implementation derive from above specified boss
 and override this interface. Also custom implementations should aggregate this interface on the boss serving
 IID_IHTTPLINKRESOURCESERVERAPIWRAPPER.
*/
class IHTTPAssetDownloadManager : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IHTTPASSETDOWNLOADMANAGER };

	/**
	AssetDownload progress callback definition
	@param inUri				[IN]  Input URI whose download progress is to be started
	@param cachedFilePath		[IN]  Download path for the given input URI
	@param inState				[IN]  Download state for the given input URI
	@param inProgress			[IN]  Download progress for the given input URI
	*/
	typedef boost::function<void (
		const URI& inURI,
		const IDFile& cachedFilePath,
		HTTPLinkSubsystemTypes::HTTPAssetDownloadState inState, 
		const float inProgress)> AssetDownloadProgressCallback;

	/**
	AssetDownload completion callback definition
	@param inUri				[IN]  Input URI whose download progress is to be started
	@param inState				[IN]  Download state for the given input URI
	@param cachedFilePath		[IN]  Download path for the given input URI
	*/
	typedef boost::function<void (
		const URI& inURI,
		HTTPLinkSubsystemTypes::HTTPAssetDownloadState inState,
		const IDFile& cachedFilePath)> AssetDownloadCompletionCallback;

	/**
	Initializes the download manager
	@return kTrue if the download manager initialization is successful esle kFalse
	*/
	virtual bool16 Initialize() = 0;

	/**
	Shuts down the download manager
	@return kTrue if the download manager shutdown is successful else kFalse
	*/
	virtual bool16 Shutdown() = 0;

	/**
	Starts the download for the input URI
	@param inUri				[IN]  Input URI whose download progress is to be started
	@param inDownloadMode		[IN]  Download mode(sync/async) for the given input URI
	@param progressCallback		[IN]  Download progress callback
	@param completionCallback	[IN]  Download completion callback
	@return kTrue if the download for input uri is started else kFalse
	*/
	virtual bool16 StartDownload(const URI& inUri,
		HTTPLinkSubsystemTypes::AssetDownloadMode inDownloadMode, 
		IHTTPAssetDownloadManager::AssetDownloadProgressCallback progressCallback = NULL,
		IHTTPAssetDownloadManager::AssetDownloadCompletionCallback completionCallback = NULL) = 0;

	/**
	Starts the download for the input URI with download path specified
	@param inUri				[IN]  Input URI whose download progress is to be started
	@param inDownloadMode		[IN]  Download mode(sync/async) for the given input URI
	@param downloadPath			[IN]  Download path for the given input URI
	@param progressCallback		[IN]  Download progress callback 
	@param completionCallback	[IN]  Download completion callback
	@return kTrue if the download for input uri is started else kFalse
	*/
	virtual bool16 StartDownload(const URI& inUri,
		HTTPLinkSubsystemTypes::AssetDownloadMode inDownloadMode,
		const IDFile& downloadPath,
		IHTTPAssetDownloadManager::AssetDownloadProgressCallback progressCallback = NULL,
		IHTTPAssetDownloadManager::AssetDownloadCompletionCallback completionCallback = NULL) = 0;

	/**
	Pauses the download for the input URI.
	@param inUri			[IN] Input URI whose download progress is to be paused
	@return kTrue if the download for input uri is paused
	*/
	virtual bool16 PauseDownload(const URI& inUri) = 0;

	/**
	Resumes the download for the input URI.
	@param inUri			[IN] Input URI whose download progress is to be resumed
	@return kTrue if the download for input uri is resumed
	*/
	virtual bool16 ResumeDownload(const URI& inUri) = 0;

	/**
	Cancels the download for the input URI.
	@param inUri			[IN] Input URI whose download progress is to be cancelled
	@return kTrue if the download for input uri is cancelled
	*/
	virtual bool16 CancelDownload(const URI& inUri) = 0;

	/**
	Pauses all the downloads
	@return kTrue if this operation is successful
	*/
	virtual bool16 PauseAllDownloads() = 0;

	/**
	Resumes all the downloads
	@return kTrue if this operation is successful
	*/
	virtual bool16 ResumeAllDownloads() = 0;

	/**
	Cancels all the downloads currently running
	@return kTrue if this operation is successful
	*/
	virtual bool16 CancelAllDownloads() = 0;
	
	/**
	Fetches the download state for the input URI.
	@param inUri			[IN]  Input URI whose download state is to be fetched
	@return HTTPAssetDownloadState the download state for input uri
	*/
	virtual HTTPLinkSubsystemTypes::HTTPAssetDownloadState GetDownloadState(const URI& inUri) const = 0;

	/**
	Fetches the download progress for the input URI.
	@param inUri			[IN]  Input URI whose download progress is to be fetched
	@param outProgress		[OUT] Download progress
	@return kTrue if the download for input uri is in progress else kFalse
	*/
	virtual bool16 GetProgress(const URI& inUri, float& outProgress) const = 0;

	/**
	Checks if the download is in progress for the input URI.
	@param inUri			[IN] Input URI whose download progress is to be checked.
	@return kTrue if the download for input uri is in progress else kFalse
	*/	
	virtual bool16 InProgress(const URI& inUri) const = 0;
};

#endif	// __IHTTPAssetDownloadManager__
