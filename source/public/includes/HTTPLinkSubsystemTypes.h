//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/HTTPLinkSubsystemTypes.h $
//  
//  Owner: Sanyam Jain
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
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
//  ABSTRACT:
//  This file defines a set of base types for use by all PageMaker applications.
//  See the comments below for the different types.
//  
//========================================================================================

#pragma once
#ifndef __HTTPLinkSubsystemTypes__
#define __HTTPLinkSubsystemTypes__

#include <map>

/**
Experimental header - will be modified/documented in future.
*/
namespace HTTPLinkSubsystemTypes
{
	typedef WideString																				HeaderKey;
	typedef WideString																				HeaderValue;
	typedef std::pair<HTTPLinkSubsystemTypes::HeaderKey, HTTPLinkSubsystemTypes::HeaderValue>		HeadersPair;
	typedef std::multimap<HTTPLinkSubsystemTypes::HeaderKey, HTTPLinkSubsystemTypes::HeaderValue>	Headers;
	typedef Headers::iterator																		HeadersIterator;
	typedef Headers::const_iterator																	HeadersConstIterator;

	typedef WideString																				GUID;
	typedef GUID																					RequestID;

	/**
	Asset Download Mode
	*/
	enum AssetDownloadMode
	{
		kAssetDownloadMode_Sync,
		kAssetDownloadMode_ASync,
		kAssetDownloadMode_Unknown
	};

	/**
	Asset Batch Request Object Type(Asset/AssetMetadata(Asset Text Fragment Link)
	*/
	enum BatchRequestObjectType
	{
		kAsset,
		kAssetMetadata		
	};

	/**
	Asset Download State
	*/
	enum HTTPAssetDownloadState
	{
		kHTTPAssetDownloadState_Start,
		kHTTPAssetDownloadState_InProgress,
		kHTTPAssetDownloadState_Complete,
		kHTTPAssetDownloadState_Paused,
		kHTTPAssetDownloadState_Cancelled,
		kHTTPAssetDownloadState_NotStarted,

		//Error states
		kHTTPAssetDownloadState_ConnectionError,
		kHTTPAssetDownloadState_ServerError,
		kHTTPAssetDownloadState_ClientError,
		kHTTPAssetDownloadState_DownloadTimeout,
		kHTTPAssetDownloadState_UnknownError
	};

	/*
	Link Resource State ClientData
	*/
	struct UpdateLinkResourceStateClientData
	{
		HTTPLinkSubsystemTypes::GUID	fGuid;
		bool							fNotify;
		bool							fAsync;
	};
}





#endif // __HTTPLinkSubsystemTypes__
