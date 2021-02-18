//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/HTTPAssetLinkResourceHandler.h $
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

#ifndef __HTTPAssetLinkResourceHandler__
#define __HTTPAssetLinkResourceHandler__

#include "CPMUnknown.h"
#include "LinksID.h"

#include "ILinkResourceHandler.h"
#include "IHTTPLinkConnectionManager.h"
#include "IHTTPLinkManager.h"
#include "IHTTPLinkUtils.h"

#include "FileTypeInfo.h"
#include "URICommonUtils.h"


// =============================================================================
//		* HTTPAssetLinkResourceHandler											
// =============================================================================

/**
Experimental header - will be modified/documented in future.
*/
class PUBLIC_DECL HTTPAssetLinkResourceHandler : public CPMUnknown<ILinkResourceHandler>
{
public:
	typedef CPMUnknown<ILinkResourceHandler> inherited;
	typedef object_type data_type;

	HTTPAssetLinkResourceHandler(IPMUnknown* boss);
	virtual ~HTTPAssetLinkResourceHandler();

	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param uri [IN] URI of the Link.
	@return True if init is successful else false.
	*/
	virtual bool Init(const UIDRef& ref, const URI& uri);

	/*
	 @param UIDRef [IN] UIDRef of the Link Resource.
	 @param uri [IN] URI of the Link.
	 @return true if the resource is Valid else false.
	*/
	virtual bool IsResourceURIValid(const UIDRef& ref, const URI& uri) const;

	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param uri [IN] URI of the Link.
	@return true if the resource'IDs are equivalent else false.
	*/
	virtual bool AreResourceIdsEquivalent(const ILinkResource::ResourceId& id1, const ILinkResource::ResourceId& id2) const;
	
	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param uri [IN] URI of the Link.
	@return the resource type 
	*/
	virtual FileTypeInfo GetResourceDataType(const UIDRef& ref, const URI& uri) const;

	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param uri [IN] URI of the Link.
	@param bUIName [IN] true if we want to show the name to UI else false.
	@return shortname of the resource
	*/
	virtual WideString GetShortResourceName(const UIDRef& ref, const URI& uri, bool bUIName) const;
	
	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param uri [IN] URI of the Link.
	@param bUIName [IN] true if we want to show the name to UI else false.
	@return LongName of the resource
	*/
	virtual WideString GetLongResourceName(const UIDRef& ref, const URI& uri, bool bUIName) const;

	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param state [IN] state of the resource.
	@param storeState [IN] store state of the resource.
	@return resource state as PMString
	*/
	virtual PMString GetResourceStateInfo(const UIDRef& ref, const URI& uri, ILinkResource::ResourceState state, ILinkResource::ResourceStoreState storeState) const;

	/*
	 @param stamp1 [IN] resource1 stamp
	 @param stamp2 [IN] resource2 stamp
	 @return true if both stamps are equivalent.
	*/
	virtual bool AreStampsEquivalent(const WideString& stamp1, const WideString& stamp2) const;

	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param uri [IN] URI of the Link.
	@return true if we can read the resource else false.
	*/
	virtual bool CanReadResource(const UIDRef& ref, const URI& uri) const;

	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param uri [IN] URI of the Link.
	@return true if we can write the resource else false.
	*/
	virtual bool CanWriteResource(const UIDRef& ref, const URI& uri) const;

	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param uri [IN] URI of the Link.
	@return true if we can read and write the resource else false.
	*/
	virtual bool CanReadWriteResource(const UIDRef& ref, const URI& uri) const;

	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param uri [IN] URI of the Link.
	@param mode [IN] access mode for the resource
	@return true if we can create the resource stream else false.
	*/
	virtual bool CanCreateResourceStream(const UIDRef& ref, const URI& uri, ILinkResource::AccessMode mode) const;
	
	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param uri [IN] URI of the Link.
	@return create the resource read stream.
	*/
	virtual IPMStream* CreateResourceReadStream(const UIDRef& ref, const URI& uri) const;

	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param uri [IN] URI of the Link.
	@return create the resource write stream.
	*/
	virtual IPMStream* CreateResourceWriteStream(const UIDRef& ref, const URI& uri) const;
	
	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param uri [IN] URI of the Link.
	@return create the resource read write stream.
	*/
	virtual IPMStream* CreateResourceReadWriteStream(const UIDRef& ref, const URI& uri) const;

	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param uri [IN] URI of the Link.
	@return true if can cache the resource else false.
	*/
	virtual bool CanCacheResource(const UIDRef& ref, const URI& uri) const { return true; }


	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param uri [IN] URI of the Link.
	@return true if can embed the resource else false.
	*/
	virtual bool CanEmbedResource(const UIDRef& ref, const URI& uri) const;


	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param uri [IN] URI of the Link.
	@return true if can unembed the resource else false.
	*/
	virtual bool CanUnembedResource(const UIDRef& ref, const URI& uri) const { return true; }



	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param uri [IN] URI of the Link.
	@return true if can copy the resource to file else false.
	*/
	virtual bool CanCopyToFile(const UIDRef& ref, const URI& uri) const;
	
	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param uri [IN] URI of the Link.
	@param file [OUT] file to copy
	@return kSuccess if copy is success else kFailure.
	*/
	virtual ErrorCode CopyToFile(const UIDRef& ref, const URI& uri, IDFile& file) const;

	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param uri [IN] URI of the Link.
	@return true if can edit the resource else false.
	*/
	virtual bool CanEditResource(const UIDRef& ref, const URI& uri) const;

	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param uri [IN] URI of the Link.
	@param appInfo [IN] appinfo
	@param errorString [OUT] output error string.
	@return kSuccess on success else kFailure.
	*/
	virtual ErrorCode EditResource(const UIDRef& ref, const URI& uri, const AppInfo& appInfo, PMString* errorString) const;


	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param uri [IN] URI of the Link.
	@return true if can reveal the resource else false.
	*/
	virtual bool CanRevealResource(const UIDRef& ref, const URI& uri) const;

	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param uri [IN] URI of the Link.
	@return true if revealing the resource else false.
	*/
	virtual ErrorCode RevealResource(const UIDRef& ref, const URI& uri) const;


	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param uri [IN] URI of the Link.
	@return true if can reveal the resource  in Bridge else false.
	*/
	virtual bool CanRevealResourceInBridge(const UIDRef& ref, const URI& uri) const{ return false; }
	
	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param uri [IN] URI of the Link.
	@return true if revealing the resource in bridge else false.
	*/
	virtual ErrorCode RevealResourceInBridge(const UIDRef& ref, const URI& uri) const{ return kFailure; }

	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param uri [IN] URI of the Link.
	@return true if can reveal the resource  in CloudLibraries else false.
	*/
	virtual bool CanRevealResourceInCloudLibraries(const UIDRef& ref, const URI& uri) const { return false; }
	
	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param uri [IN] URI of the Link.
	@return true if revealing the resource in Cloud Lib else false.
	*/
	virtual ErrorCode RevealResourceInCloudLibraries(const UIDRef& ref, const URI& uri) const  { ASSERT_UNIMPLEMENTED(); return kFailure; }
	
	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param uri [IN] URI of the Link.
	@param packet [OUT] filled XMPInfo packet 
	@return true on success else false.
	*/
	virtual bool GetXMPPacketInfo(const UIDRef& resourceRef, const URI& uri, std::string& packet) const;
	
	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param uri [IN] URI of the Link.
	@return true if Getting XMP info is allowed  else false.
	*/
	virtual bool CanGetXMPPacketInfo(const UIDRef& ref, const URI& uri) const;
	
	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param uri [IN] URI of the Link.
	@return true if a FPO can be replaced else false.
	*/
	virtual bool CanReplaceFPOWithOriginalResource(const UIDRef& ref, const URI& uri) const;
	
	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param uri [IN] URI of the Link.
	@return true if original resource can be downloaded else false.
	*/
	virtual bool CanDownloadOriginalResource(const UIDRef& ref, const URI& uri) const;
	
	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param uri [IN] URI of the Link.
	@return KSuccess on success else kFailure.
	*/
	virtual ErrorCode DownloadOriginalResource(const UIDRef& ref, const URI& uri) const;
	
	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param uri [IN] URI of the Link.
	@param completionFunction [IN] download completion function.
	@return KSuccess on AsyncDownloadOriginalResource success else kFailure.
	*/
	virtual ErrorCode AsyncDownloadOriginalResource(const UIDRef& ref, const URI& uri, ILinkResource::DownloadCompletionFunction completionFunction) const;
	
	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param uri [IN] URI of the Link.
	@param progress [IN] downloading progress.
	@return ResourceDownloadState as output.
	*/
	virtual ILinkResource::ResourceDownloadState GetResourceDownloadProgress(const UIDRef& ref, const URI& uri, PMReal& progress) const;

	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param uri [IN] URI of the Link.
	@return true if it can provide IDFile corresponsing to uri.
	*/
	virtual bool CanProvideFile(const UIDRef& ref, const URI& uri) const;
	
	/*
	@param UIDRef [IN] UIDRef of the Link Resource.
	@param uri [IN] URI of the Link.
	@param idFile [OUT] resultant IDFile for uri.
	@return kSuccess on success else kFailure.
	*/
	virtual ErrorCode GetFile(const UIDRef& ref, const URI& uri, IDFile& idFile) const;

	/*
	@param uri [IN] URI of the Link.
	@return if URI is HTTPS supported or not.
	*/
	virtual bool IsHTTPSSupportedURI(const URI& uri) const;
    
    /*
     @return kSuccess if the handler can provide the current instance name
     and want to show the instance name in links info in links panel
     */
	virtual bool canGetInstanceName() const { return false; }
    
    /*
     @param uri [OUT] Instance name for the uri
     @return kSuccess on success else kFailure.
     */
    virtual ErrorCode GetInstanceName(PMString &uri) const { return kFailure; }
    
private:
	// Prevent copy construction and assignment.
	HTTPAssetLinkResourceHandler(const HTTPAssetLinkResourceHandler&);
	HTTPAssetLinkResourceHandler& operator=(const HTTPAssetLinkResourceHandler&);

	std::shared_ptr<IHTTPLinkCachedAssetEntry> GetCachedAssetEntry(const UIDRef& ref,
		HTTPLinkSubsystemTypes::AssetDownloadMode downloadMode,
		bool16 shouldDownload = kTrue,
		bool16 forceOriginalURI = kFalse,
		IHTTPLinkResourceServerCache::AssetDownloadCompletionCallback completionFunction = NULL) const;

	static ILinkResource::ResourceDownloadState DownloadStateConverter(const HTTPLinkSubsystemTypes::HTTPAssetDownloadState downloadState);
	static void DownloadCompletionCallback(const URI& inUri,
		const HTTPLinkSubsystemTypes::HTTPAssetDownloadState& inState,
		std::shared_ptr<IHTTPLinkCachedAssetEntry> cachedAssetEntry,
		ILinkResource::DownloadCompletionFunction downloadCompletionFunction);
		
	static void HighResDrawingDownloadCompletionCallback(const UIDRef& ref,
														 const HTTPLinkSubsystemTypes::GUID guid,
														 const UID uid,
														 const URI& inUri,
														 const HTTPLinkSubsystemTypes::HTTPAssetDownloadState& inState,
														 std::shared_ptr<IHTTPLinkCachedAssetEntry> cachedAssetEntry);
	
	static uint32 PerformAssetsInvalidation(void* ptr);
	static void StartAssetsInvalidationDelayTimer(uint32 delayTime);

protected:

	/**
	Denotes whether the handler was able to successfully initialize via a call to Init()
	by converting the link resource's URI to an IDFile.
	*/
	bool										fbInited;

	InterfacePtr<IHTTPLinkResourceServerCache>	fCache;
	InterfacePtr<IHTTPLinkResourceConnection>	fConnection;

	/**
	Caches used to store the resource's short and long names so that they don't
	have to regenerated every time.  The caches should always be invalidated
	every time the handler is initialized.
	*/
	mutable WideString		fShortNameCache;
	mutable WideString		fShortUINameCache;
	mutable WideString		fLongNameCache;
	mutable WideString		fLongUINameCache;

};

#endif // __HTTPAssetLinkResourceHandler__
