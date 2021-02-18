//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/links/HTTPAssetLinkResourceHandler.cpp $
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

#include "VCPublicHeaders.h"
#include "HTTPAssetLinkResourceHandler.h"
#include "DocHTTPBatchQueryManager.h"
#include "IPrivateLinkUtils.h"
#include "InDesignSessionDataManager.h"
#include "boost/bind.hpp"
#include "IUIDRefListData.h"
#include "ILayoutUIUtils.h"
#include "ILayoutUtils.h"
#include "IDocument.h"
#include "ICallbackTimer.h"
#include "ILinkManager.h"
#include "ILinkObject.h"
#include "IShape.h"
#include "IShapeGraphixCache.h"
#include "ILinkFacade.h"
#include "IHierarchy.h"
#include "IControlView.h"
#include "AGMGraphicsContext.h"
#include "IPageItemCache.h"
#include "IImageCacheMgr.h"
#include "IWorkspace.h"

/*
 AdobePatentID="P7137-US"
 */

// =============================================================================
// *** HTTPAssetLinkResourceHandler implementation ***
// -----------------------------------------------------------------------------


// see  .../source/components/utilities/plugin/PublicImpl.cpp
//CREATE_PMINTERFACE(HTTPAssetLinkResourceHandler, kHTTPAssetLinkResourceHandlerImpl)

static ICallbackTimer* gAssetsInvalidationDelayTimer = nil;

//========================================================================================
// Constructor
//========================================================================================
HTTPAssetLinkResourceHandler::HTTPAssetLinkResourceHandler(IPMUnknown* boss)
: inherited(boss),
fbInited(false)
{
}

//========================================================================================
// Destructor
//========================================================================================
HTTPAssetLinkResourceHandler::~HTTPAssetLinkResourceHandler()
{
}

// -----------------------------------------------------------------------------
bool HTTPAssetLinkResourceHandler::Init(const UIDRef& ref, const URI& uri)
{
	IHTTPLinkUtils* httpLinkUtils = Utils<IHTTPLinkUtils>();
	if (!httpLinkUtils)
	{
		fbInited = false;
		return false;
	}

	if (!httpLinkUtils->IsHTTPLinksSupportedURI(uri))
	{
		fbInited = false;
		return false;
	}

	if (ref.GetDataBase() == nil || !ref.GetDataBase()->IsValidUID(ref.GetUID()))
	{
		fbInited = false;
		return false;
	}

	if (!httpLinkUtils)
	{
		fbInited = false;
		return false;
	}

	//get connection for the http uri
	fConnection = httpLinkUtils->GetHTTPLinkResourceConnection(uri);
	fCache = httpLinkUtils->GetHTTPLinkResourceServerCache(uri);
	if (!fCache || !fConnection)
	{
		fbInited = false;
		return false;
	}

	fbInited = true;
	fShortNameCache.Clear();
	fShortUINameCache.Clear();
	fLongNameCache.Clear();
	fLongUINameCache.Clear();

	return fbInited;
}

// -----------------------------------------------------------------------------

bool HTTPAssetLinkResourceHandler::AreResourceIdsEquivalent(const ILinkResource::ResourceId& id1, const ILinkResource::ResourceId& id2) const
{
	return (id1 == id2);
}


bool HTTPAssetLinkResourceHandler::AreStampsEquivalent(const WideString& stamp1, const WideString& stamp2) const
{
	return (stamp1 == stamp2);
}

bool HTTPAssetLinkResourceHandler::CanCreateResourceStream(const UIDRef& ref, const URI& uri, ILinkResource::AccessMode mode) const
{
	if (!fbInited || mode != ILinkResource::kRead)
	{
		return false;
	}

	return true;
}

bool HTTPAssetLinkResourceHandler::CanEditResource(const UIDRef& ref, const URI& uri) const
{
	return false;
}

bool HTTPAssetLinkResourceHandler::CanReadResource(const UIDRef& ref, const URI& uri) const
{
	std::shared_ptr<IHTTPLinkCachedAssetEntry> cachedAssetEntry = GetCachedAssetEntry(ref, HTTPLinkSubsystemTypes::kAssetDownloadMode_ASync, kFalse /*shouldDownload*/);
	return fbInited && (cachedAssetEntry != nil) && cachedAssetEntry->CanRead();
}

bool HTTPAssetLinkResourceHandler::CanWriteResource(const UIDRef& ref, const URI& uri) const
{
	return false;
}

bool HTTPAssetLinkResourceHandler::CanReadWriteResource(const UIDRef& ref, const URI& uri) const
{
	return false;
}

IPMStream* HTTPAssetLinkResourceHandler::CreateResourceReadStream(const UIDRef& ref, const URI& inUri) const
{
	if (!fbInited)
	{
		return nil;
	}
	
	HTTPLinkSubsystemTypes::AssetDownloadMode downloadMode = HTTPLinkSubsystemTypes::kAssetDownloadMode_Sync;
	IHTTPLinkResourceServerCache::AssetDownloadCompletionCallback highResDrawingDownloadCompletionCallback = NULL;
	
	bool16 documentDrawingInProcess = ValueTypeConversion<bool16>().get(InDesignSessionDataStoreKeyType::kDocumentDrawingInProcess, kFalse);
	bool16 docScrollInProcess = ValueTypeConversion<bool16>().get(InDesignSessionDataStoreKeyType::kDocScrollInProcess, kFalse);
	bool16 highResMode = ValueTypeConversion<bool16>().get(InDesignSessionDataStoreKeyType::kIsHighResMode, kFalse);
	
	
	// If the doc-drawing or doc-scrolling is in process in the High-res mode, then we would want to
	// faciliate async on-demand download of assets in case they are not present in cache.
	// It is done so the user does not get blocked due to sync-download of assets.
	// While the original assets are being downloaded, the proxy-image is shown to the user.
	// After the original assets are available, proxy images are invalidated and the original assets are re-drawn .
	
	if((documentDrawingInProcess || docScrollInProcess ) && highResMode)
	{
		HTTPLinkSubsystemTypes::HTTPAssetDownloadState donwnloadState =  fCache->GetDownloadState(inUri);
		if(donwnloadState == HTTPLinkSubsystemTypes::kHTTPAssetDownloadState_InProgress) // if download is in progress then do-nothing and return nil.
			return nil;
		
		downloadMode = HTTPLinkSubsystemTypes::kAssetDownloadMode_ASync;
		IDataBase *db = ref.GetDataBase();
		DocHTTPBatchQueryManager* instance = DocHTTPBatchQueryManager::Instance();
		HTTPLinkSubsystemTypes::GUID guid = instance->GenerateGuidAndCreateMapping(db);
		UID uid = ref.GetUID();
		
		//Making our custom-callback for the special case of async download of assets while doc-drawing and doc-scrolling.
		highResDrawingDownloadCompletionCallback = boost::bind<void>(&HTTPAssetLinkResourceHandler::HighResDrawingDownloadCompletionCallback,ref, guid, uid, _1, _2, _3);
	}
	
	std::shared_ptr<IHTTPLinkCachedAssetEntry> cachedAssetEntry = GetCachedAssetEntry(ref, downloadMode, kTrue /*shouldDownload*/, kFalse, highResDrawingDownloadCompletionCallback);

	if (cachedAssetEntry == nil || !cachedAssetEntry->CanRead())
	{
		return nil;
	}

	return cachedAssetEntry->CreateReadStream();
}

IPMStream* HTTPAssetLinkResourceHandler::CreateResourceWriteStream(const UIDRef& ref, const URI& uri) const
{
	return nil;
}

IPMStream* HTTPAssetLinkResourceHandler::CreateResourceReadWriteStream(const UIDRef& ref, const URI& uri) const
{
	return nil;
}

FileTypeInfo HTTPAssetLinkResourceHandler::GetResourceDataType(const UIDRef& ref, const URI& uri) const
{
	if (!fbInited)
	{
		return FileTypeInfo();
	}

	std::shared_ptr<IHTTPLinkCachedAssetEntry> cachedAssetEntry = GetCachedAssetEntry(ref, HTTPLinkSubsystemTypes::kAssetDownloadMode_Sync, kFalse /*shouldDownload*/);

	if (cachedAssetEntry == nil)
		return FileTypeInfo();

	return cachedAssetEntry->GetFileTypeInfo();
}

WideString HTTPAssetLinkResourceHandler::GetShortResourceName(const UIDRef& ref, const URI& uri, bool bUIName) const
{
	if (bUIName && !fShortUINameCache.empty())
	{
		return fShortUINameCache;
	}

	if (!fShortNameCache.empty())
		return fShortNameCache;

	if (Utils<IHTTPLinkUtils>()->IsHTTPLinksSupportedURI(uri))
	{
		PMString assetShortName;
		Utils<IPrivateLinkUtils>()->URIToAssetName(uri, assetShortName);
		fShortNameCache.clear();
		fShortNameCache.BuildFromSystemString(assetShortName);
		fShortUINameCache = fShortNameCache;
	}

	return bUIName ? fShortUINameCache : fShortNameCache;
}

bool HTTPAssetLinkResourceHandler::IsHTTPSSupportedURI(const URI& uri) const
{
	return (uri.GetComponent(URI::kScheme) == kHTTPSAssetURIScheme) ? true : false;
}
WideString HTTPAssetLinkResourceHandler::GetLongResourceName(const UIDRef& ref, const URI& uri, bool bUIName) const
{
	return WideString("");
}

ErrorCode HTTPAssetLinkResourceHandler::EditResource(const UIDRef& ref, const URI& uri, const AppInfo& appInfo, PMString* errorString) const
{
	//edit resource not allowed
	return kFailure;
}

bool HTTPAssetLinkResourceHandler::IsResourceURIValid(const UIDRef& ref, const URI& uri) const
{
	bool isValid(false);

	if (Utils<IHTTPLinkUtils>()->IsHTTPLinksSupportedURI(uri))
	{
		WideString path(uri.GetComponent(URI::kPath));
		isValid = !path.IsNull();
	}

	return isValid;
}

bool HTTPAssetLinkResourceHandler::CanCopyToFile(const UIDRef& ref, const URI& uri) const
{
	if (!fbInited)
		return false;
	return true;
}

ErrorCode HTTPAssetLinkResourceHandler::CopyToFile(const UIDRef& ref, const URI& uri, IDFile& file) const
{
	std::shared_ptr<IHTTPLinkCachedAssetEntry> cachedAssetEntry = GetCachedAssetEntry(ref, HTTPLinkSubsystemTypes::kAssetDownloadMode_Sync, kTrue /*shouldDownload*/, kTrue /*forceOriginal*/);
	if (!fbInited || cachedAssetEntry == nil || !cachedAssetEntry->CanCopyToFile())
		return kFailure;

	return cachedAssetEntry->CopyToFile(file);
}

bool HTTPAssetLinkResourceHandler::CanRevealResource(const UIDRef& ref, const URI& uri) const
{
	return false;
}

ErrorCode HTTPAssetLinkResourceHandler::RevealResource(const UIDRef& ref, const URI& uri) const
{
	return false;
}

PMString HTTPAssetLinkResourceHandler::GetResourceStateInfo(const UIDRef& ref, const URI& uri, ILinkResource::ResourceState state, ILinkResource::ResourceStoreState storeState) const
{
	return PMString();
}

bool HTTPAssetLinkResourceHandler::CanEmbedResource(const UIDRef& ref, const URI& uri) const
{
	if (!fbInited)
	{
		return false;
	}
	return true;
}

bool HTTPAssetLinkResourceHandler::CanGetXMPPacketInfo(const UIDRef& ref, const URI& uri) const
{
	if (fbInited)
	{
		InterfacePtr<ILinkResource> iLinkResource(ref, UseDefaultIID());
		if (iLinkResource && iLinkResource->GetState() == ILinkResource::kAvailable)
			return true;
	}
	return false;
}

bool HTTPAssetLinkResourceHandler::GetXMPPacketInfo(const UIDRef& resourceRef, const URI& uri, std::string& packet) const
{
	if (CanGetXMPPacketInfo(resourceRef, uri))
	{
		std::shared_ptr<IHTTPLinkCachedAssetEntry> cachedAssetEntry = GetCachedAssetEntry(resourceRef, HTTPLinkSubsystemTypes::kAssetDownloadMode_Sync, kFalse /*shouldDownload*/);
		if (cachedAssetEntry != nil)
			return cachedAssetEntry->GetXMPPacketInfo(packet);
	}
	return false;
}

bool HTTPAssetLinkResourceHandler::CanDownloadOriginalResource(const UIDRef& ref, const URI& uri) const
{
	if (!fbInited)
		return false;

	//check if the valid connection to server exists
	bool isConnectionValid = false;
	InterfacePtr<IHTTPLinkConnectionManager> connectionMgr(GetExecutionContextSession(), UseDefaultIID());
	ASSERT(connectionMgr);
	if (connectionMgr)
	{
		InterfacePtr<IHTTPLinkResourceConnection> connection(connectionMgr->GetHTTPConnection(uri), UseDefaultIID());
		ASSERT(connection);
		if (connection)
			isConnectionValid = connection->IsConnected();
	}
	if (!isConnectionValid)
		return false;

	if (CanReplaceFPOWithOriginalResource(ref, uri))
		return false;

	PMReal progress;
	ILinkResource::ResourceDownloadState downloadState = GetResourceDownloadProgress(ref, uri, progress);

	if (downloadState == ILinkResource::kInProgress)
		return false;
	return true;
}

ErrorCode HTTPAssetLinkResourceHandler::DownloadOriginalResource(const UIDRef& ref, const URI& uri) const
{
	std::shared_ptr<IHTTPLinkCachedAssetEntry> cachedAssetEntry = GetCachedAssetEntry(ref, HTTPLinkSubsystemTypes::kAssetDownloadMode_Sync, kTrue /*shouldDownload*/, kTrue /*forceOriginalURI*/);
	if (cachedAssetEntry == nil)
		return kFailure;
	return kSuccess;
}

ErrorCode HTTPAssetLinkResourceHandler::AsyncDownloadOriginalResource(const UIDRef& ref, const URI& uri, ILinkResource::DownloadCompletionFunction completionFunction) const
{
	IHTTPLinkResourceServerCache::AssetDownloadCompletionCallback inDownloadCompletionCallback = NULL;
	if (completionFunction != NULL)
	{
		inDownloadCompletionCallback = boost::bind<void>(&HTTPAssetLinkResourceHandler::DownloadCompletionCallback, _1, _2, _3, completionFunction);
	}

	GetCachedAssetEntry(ref, HTTPLinkSubsystemTypes::kAssetDownloadMode_ASync, kTrue /*shouldDownload*/, kTrue /*forceOriginalURI*/, inDownloadCompletionCallback);
	return kSuccess;
}

bool HTTPAssetLinkResourceHandler::CanReplaceFPOWithOriginalResource(const UIDRef& ref, const URI& uri) const
{
	if (!fbInited)
		return false;

	std::shared_ptr<IHTTPLinkCachedAssetEntry> cachedAssetEntry = GetCachedAssetEntry(ref, HTTPLinkSubsystemTypes::kAssetDownloadMode_ASync, kFalse /*shouldDownload*/, kTrue /*forceOriginalURI*/);
	return (cachedAssetEntry != nil) && cachedAssetEntry->CanCreateReadStream();
}

ILinkResource::ResourceDownloadState HTTPAssetLinkResourceHandler::GetResourceDownloadProgress(const UIDRef& ref, const URI& uri, PMReal& progress) const
{
	if (!fbInited)
		return ILinkResource::kDownloadError;

	InterfacePtr<ILinkResource> iLinkResource(ref, UseDefaultIID());
	if (!iLinkResource)
		return ILinkResource::kDownloadError;

	URI origAssetURI;
	IHTTPLinkUtils* httpLinkUtils = Utils<IHTTPLinkUtils>();
	if (httpLinkUtils->GetOriginalURIForResource(iLinkResource, origAssetURI))
	{
		HTTPLinkSubsystemTypes::HTTPAssetDownloadState downloadState = fCache->GetDownloadState(origAssetURI);
		return DownloadStateConverter(downloadState);
	}


	return ILinkResource::kDownloadError;
}

bool HTTPAssetLinkResourceHandler::CanProvideFile(const UIDRef& ref, const URI& uri) const
{
	if (!fbInited)
		return false;

	std::shared_ptr<IHTTPLinkCachedAssetEntry> cachedAssetEntry = GetCachedAssetEntry(ref, HTTPLinkSubsystemTypes::kAssetDownloadMode_ASync, kFalse /*shouldDownload*/);
	if (cachedAssetEntry == nil)
		return false;
	return cachedAssetEntry->CanGetFile();
}

ErrorCode HTTPAssetLinkResourceHandler::GetFile(const UIDRef& ref, const URI& uri, IDFile& idFile) const
{
	if (!CanProvideFile(ref, uri))
		return kFailure;
	std::shared_ptr<IHTTPLinkCachedAssetEntry> cachedAssetEntry = GetCachedAssetEntry(ref, HTTPLinkSubsystemTypes::kAssetDownloadMode_ASync, kFalse /*shouldDownload*/);
	if (cachedAssetEntry && cachedAssetEntry->GetFile(idFile))
		return kSuccess;

	return kFailure;
}

std::shared_ptr<IHTTPLinkCachedAssetEntry> HTTPAssetLinkResourceHandler::GetCachedAssetEntry(const UIDRef& ref,
	HTTPLinkSubsystemTypes::AssetDownloadMode downloadMode,
	bool16 shouldDownload,
	bool16 forceOriginalURI,
	IHTTPLinkResourceServerCache::AssetDownloadCompletionCallback downloadCompletionFunction) const
{
	InterfacePtr<ILinkResource> iLinkResource(ref, UseDefaultIID());

	if (!iLinkResource)
		return nil;

	URI assetUri;
	if (forceOriginalURI)
	{
		if (!Utils<IHTTPLinkUtils>()->GetOriginalURIForResource(iLinkResource, assetUri))
			return nil;
	}
	else
	{
		if (iLinkResource->IsFPO())
		{
			if (!Utils<IHTTPLinkUtils>()->GetRenditionURIForResource(iLinkResource, assetUri))
			{
				return nil;
			}
		}
		else if (!Utils<IHTTPLinkUtils>()->GetOriginalURIForResource(iLinkResource, assetUri))
			return nil;
	}

	return fCache->GetCachedAssetEntry(assetUri,
		shouldDownload /* inDownloadIfMissing */,
		downloadMode,
		NULL,
		downloadCompletionFunction);
}

ILinkResource::ResourceDownloadState HTTPAssetLinkResourceHandler::DownloadStateConverter(const HTTPLinkSubsystemTypes::HTTPAssetDownloadState downloadState)
{
	switch (downloadState)
	{
	case HTTPLinkSubsystemTypes::kHTTPAssetDownloadState_Start:
	case HTTPLinkSubsystemTypes::kHTTPAssetDownloadState_InProgress:
	case HTTPLinkSubsystemTypes::kHTTPAssetDownloadState_Paused:
		return ILinkResource::kInProgress;
	case HTTPLinkSubsystemTypes::kHTTPAssetDownloadState_Complete:
		return ILinkResource::kComplete;
	case HTTPLinkSubsystemTypes::kHTTPAssetDownloadState_NotStarted:
		return ILinkResource::kNotStarted;
		//Error states
	case HTTPLinkSubsystemTypes::kHTTPAssetDownloadState_Cancelled:
	case HTTPLinkSubsystemTypes::kHTTPAssetDownloadState_ConnectionError:
	case HTTPLinkSubsystemTypes::kHTTPAssetDownloadState_ServerError:
	case HTTPLinkSubsystemTypes::kHTTPAssetDownloadState_ClientError:
	case HTTPLinkSubsystemTypes::kHTTPAssetDownloadState_DownloadTimeout:
	case HTTPLinkSubsystemTypes::kHTTPAssetDownloadState_UnknownError:
	default:
		return ILinkResource::kDownloadError;

	}
	return ILinkResource::kDownloadError;
}

void HTTPAssetLinkResourceHandler::DownloadCompletionCallback(const URI& inUri,
	const HTTPLinkSubsystemTypes::HTTPAssetDownloadState& inState,
	std::shared_ptr<IHTTPLinkCachedAssetEntry> cachedAssetEntry,
	ILinkResource::DownloadCompletionFunction completionFunction)
{
	if (completionFunction)
	{
		completionFunction(inUri, DownloadStateConverter(inState));
	}
}

uint32 HTTPAssetLinkResourceHandler::PerformAssetsInvalidation(void* ptr)
{
	// resetting the timer
	InDesignSessionDataManager::GetInstance().Insert(InDesignSessionDataStoreKeyType::kAssetsInvalidationDelayTime, (uint32)0);
	gAssetsInvalidationDelayTimer->Release();
	gAssetsInvalidationDelayTimer = nil;
	
	InterfacePtr<ISession> session(GetExecutionContextSession(), IID_ISESSION);
	InterfacePtr<IUIDRefListData> asyncDownloadedAssets(session, IID_IASYNCDOWNLOADEDASSETS);
	IDataBase* frontDb = ::GetDataBase(Utils<ILayoutUIUtils>()->GetFrontDocument());
	if(!frontDb) // do not invalidate anything, if no document is open.
	{
		asyncDownloadedAssets->clear();
		return (~(uint32)0);
	}
	
	if(!Utils<ILayoutUIUtils>().Exists())
	{
		asyncDownloadedAssets->clear();
		return (~(uint32)0);
	}
	
	// Instance of DocHTTPBatchQueryManager to know whether the particular db is open or not.
	DocHTTPBatchQueryManager* instance = DocHTTPBatchQueryManager::Instance();
	
	// For each aysnc downloaded asset, we are removing its ImageCache and ShapeGraphixCache - so that they are redrawn when they come into view.
	// Also, if any asset is in visible view, then we are invalidating their IShape too - so that they are re-drawn immediately.
	InterfacePtr<IWorkspace>ws(GetExecutionContextSession()->QueryWorkspace());
	InterfacePtr<IImageCacheMgr> iImageCacheMgr(ws, IID_IIMAGECACHEMGR);
	InterfacePtr<IControlView> frontView( Utils<ILayoutUIUtils>()->QueryFrontView());
	UIDList visibleSpreads = Utils<ILayoutUIUtils>()->GetVisibleSpreads(frontView);
	
	for(int32 i=0; i<asyncDownloadedAssets->size(); i++)
	{
		UIDRef resourceRef = asyncDownloadedAssets->at(i);
		UID resourceUID = resourceRef.GetUID();
		IDataBase* db = resourceRef.GetDataBase();
		// UIDRef will contain a pointer to database and if the databse is closed and we try to access corresponding db pointer of uidref, then ID will
		// crash [since that db poiter will have some address and there is nothing at that address]. Hence using concept of guid.
		HTTPLinkSubsystemTypes::GUID guid = instance->GetGuid(db);
		if(guid.empty()) // Implies that corresponding database is Null/closed, so don't do anything.
			continue;
		if (!db->IsValidUID(resourceUID)) continue;
		
		InterfacePtr<ILinkManager> iLinkManager(db, db->GetRootUID(), UseDefaultIID());
		ILinkManager::QueryResult linkQueryResult;
		iLinkManager->QueryLinksByResourceUID(resourceUID, true, linkQueryResult);
		ILinkManager::QueryResult::const_iterator linkIter = linkQueryResult.begin();
		
		while (linkIter != linkQueryResult.end())
		{
			InterfacePtr<ILink> iLink(iLinkManager->QueryLinkByUID(*linkIter));
			InterfacePtr<ILinkObject> iLinkObject(iLinkManager->QueryObjectByUID(iLink->GetObject()));
			if(! iLinkObject) continue;
			UIDRef linkObjectRef = ::GetUIDRef(iLinkObject);
			if ( iImageCacheMgr )
				iImageCacheMgr->Purge(linkObjectRef);
			
			InterfacePtr<IShape> iShape((IShape*)iLinkObject->QueryLinkedObject(IID_ISHAPE));
			if(! iShape) continue;
			InterfacePtr<IShapeGraphixCache> gfxCache(iShape, UseDefaultIID());
			if(gfxCache)
				gfxCache->Invalidate();
			
			InterfacePtr<IHierarchy> iHierarchy(iShape, UseDefaultIID());
			UID spreadUID = iHierarchy->GetSpreadUID();
			bool16 isLinkObjectInView = kFalse;
			for (int32 j = 0; j < visibleSpreads.Length(); j++)
			{
				if((visibleSpreads[j] == spreadUID) && (db == frontDb))
				{
					isLinkObjectInView = kTrue;
					break;
				}
			}
			
			if(isLinkObjectInView)
			{
				NonMarkingAGMGraphicsContext gc(frontView);
				GraphicsDataPtr gd(&gc);
				iShape->Inval(gd);
			}
			++linkIter;
		}
	}
	// clear asyncDownloadedAssets list once all assets have been invalidated.
	asyncDownloadedAssets->clear();
	return (~(uint32)0);
}

void HTTPAssetLinkResourceHandler::StartAssetsInvalidationDelayTimer(uint32 delayTime)
{
	InDesignSessionDataManager::GetInstance().Insert(InDesignSessionDataStoreKeyType::kAssetsInvalidationDelayTime, delayTime);
	gAssetsInvalidationDelayTimer = (ICallbackTimer*)::CreateObject(kCallbackTimerBoss, IID_ICALLBACKTIMER);
	gAssetsInvalidationDelayTimer->StartTimer(PerformAssetsInvalidation, delayTime);
}

void HTTPAssetLinkResourceHandler::HighResDrawingDownloadCompletionCallback(const UIDRef& ref,
	const HTTPLinkSubsystemTypes::GUID guid,
	const UID uid,
	const URI& inUri,
	const HTTPLinkSubsystemTypes::HTTPAssetDownloadState& inState,
	std::shared_ptr<IHTTPLinkCachedAssetEntry> cachedAssetEntry)
{
	uint32 initialDelayTime = 2500;
	uint32 thresholdDelayTime = 300;
	uint32 timeDivisionFactor = 2;
	
	//asyncDownloadedAssets contains list of all assets which have been downloaded and have not been invalidated.
	InterfacePtr<ISession> session(GetExecutionContextSession(), IID_ISESSION);
	InterfacePtr<IUIDRefListData> asyncDownloadedAssets(session, IID_IASYNCDOWNLOADEDASSETS);	
	if(gAssetsInvalidationDelayTimer) //AssetsInvalidationDelayTimer timer is running.
	{
		// Using buffered-delay time approach, so that if multiple assets are downloaded at the same time
		// multiple calls are not made to PerformAssetsInvalidation(), but are clubbed into a single invalidation call.
		// 2500 -> 1250 -> 625 -> .... since n/2 + n/4 + n/8 + n/16 + ... = n [hence a maximum total buffer of n seconds]
		asyncDownloadedAssets->push_back(ref);
		uint32 delayTime = ValueTypeConversion<uint32>().get(InDesignSessionDataStoreKeyType::kAssetsInvalidationDelayTime, (uint32)0);
		if(delayTime > thresholdDelayTime)
		{
			//Stop the ongoing timer and again start the timer with half delaytime.
			gAssetsInvalidationDelayTimer->StopTimer();
			gAssetsInvalidationDelayTimer->Release();
			gAssetsInvalidationDelayTimer = nil;
			StartAssetsInvalidationDelayTimer(delayTime/timeDivisionFactor);
		}
	}
	else
	{
		asyncDownloadedAssets->push_back(ref);
		StartAssetsInvalidationDelayTimer(initialDelayTime);
	}
}

