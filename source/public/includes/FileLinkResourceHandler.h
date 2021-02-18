//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/FileLinkResourceHandler.h $
//  
//  Owner: Michael Easter
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
//  
//  Description:
//  
//========================================================================================

#pragma once
#ifndef __FileLinkResourceHandler__
#define __FileLinkResourceHandler__

// ----- Includes -----
#include "CPMUnknown.h"
#include "ILinkResourceHandler.h"


/**
 Implementation of ILinkResourceHandler for a file based link resources.
 This class serves as the resource handler for all link resources with a URI
 scheme of 'file', and  can be utilized as a base implementation for any link
 resource that is file based.
 @see ILinkResourceHandler
 */
class PUBLIC_DECL FileLinkResourceHandler : public CPMUnknown<ILinkResourceHandler>
{
public:
	typedef CPMUnknown<ILinkResourceHandler> inherited;
	typedef object_type data_type;

	FileLinkResourceHandler(IPMUnknown* boss);
	virtual ~FileLinkResourceHandler();

	virtual bool Init(const UIDRef& ref, const URI& uri);

	virtual bool IsResourceURIValid(const UIDRef& ref, const URI& uri) const;
	virtual bool AreResourceIdsEquivalent(const ILinkResource::ResourceId& id1, const ILinkResource::ResourceId& id2) const;
	virtual FileTypeInfo GetResourceDataType(const UIDRef& ref, const URI& uri) const;

	virtual WideString GetShortResourceName(const UIDRef& ref, const URI& uri, bool bUIName) const;
	virtual WideString GetLongResourceName(const UIDRef& ref, const URI& uri, bool bUIName) const;

	virtual PMString GetResourceStateInfo(const UIDRef& ref, const URI& uri, ILinkResource::ResourceState state, ILinkResource::ResourceStoreState storeState) const { return PMString(); }

	virtual bool AreStampsEquivalent(const WideString& stamp1, const WideString& stamp2) const;

	virtual bool CanReadResource(const UIDRef& ref, const URI& uri) const;
	virtual bool CanWriteResource(const UIDRef& ref, const URI& uri) const;
	virtual bool CanReadWriteResource(const UIDRef& ref, const URI& uri) const;

	virtual bool CanCreateResourceStream(const UIDRef& ref, const URI& uri, ILinkResource::AccessMode mode) const;
	virtual IPMStream* CreateResourceReadStream(const UIDRef& ref, const URI& uri) const;
	virtual IPMStream* CreateResourceWriteStream(const UIDRef& ref, const URI& uri) const;
	virtual IPMStream* CreateResourceReadWriteStream(const UIDRef& ref, const URI& uri) const;

	virtual bool CanCacheResource(const UIDRef& ref, const URI& uri) const { return true; }
	virtual bool CanEmbedResource(const UIDRef& ref, const URI& uri) const { return true; }
	virtual bool CanUnembedResource(const UIDRef& ref, const URI& uri) const { return true; }

	virtual bool CanCopyToFile(const UIDRef& ref, const URI& uri) const;
	virtual ErrorCode CopyToFile(const UIDRef& ref, const URI& uri, IDFile& file) const;

	virtual bool CanEditResource(const UIDRef& ref, const URI& uri) const;
	virtual ErrorCode EditResource(const UIDRef& ref, const URI& uri, const AppInfo& appInfo, PMString* errorString) const;

	virtual bool CanRevealResource(const UIDRef& ref, const URI& uri) const;
	virtual ErrorCode RevealResource(const UIDRef& ref, const URI& uri) const;
	virtual bool CanRevealResourceInBridge(const UIDRef& ref, const URI& uri) const;
	virtual ErrorCode RevealResourceInBridge(const UIDRef& ref, const URI& uri) const;

	virtual bool CanRevealResourceInCloudLibraries(const UIDRef& ref, const URI& uri) const { return false; }
	virtual ErrorCode RevealResourceInCloudLibraries(const UIDRef& ref, const URI& uri) const  { ASSERT_UNIMPLEMENTED(); return kFailure; }

	// XMP info functions
	virtual bool GetXMPPacketInfo(const UIDRef& resourceRef, const URI& uri, std::string& packet) const;
	virtual bool CanGetXMPPacketInfo(const UIDRef& ref, const URI& uri) const;

	//FPO related workflow functions
	virtual bool CanReplaceFPOWithOriginalResource(const UIDRef& ref, const URI& uri) const;
	virtual bool CanDownloadOriginalResource(const UIDRef& ref, const URI& uri) const;
	virtual ErrorCode DownloadOriginalResource(const UIDRef& ref, const URI& uri) const;
	virtual ErrorCode AsyncDownloadOriginalResource(const UIDRef& ref, const URI& uri, ILinkResource::DownloadCompletionFunction completionFunction) const;
	virtual ILinkResource::ResourceDownloadState GetResourceDownloadProgress(const UIDRef& ref, const URI& uri,PMReal& progress) const { ASSERT_UNIMPLEMENTED(); return ILinkResource::kNotStarted; };

	virtual bool CanProvideFile(const UIDRef& ref, const URI& uri) const;
	virtual ErrorCode GetFile(const UIDRef& ref, const URI& uri, IDFile& idFile) const;
	virtual bool canGetInstanceName() const { return false; }
	virtual ErrorCode GetInstanceName(PMString &uri) const { return kFailure; }
protected:
	/**
	 Denotes whether the handler was able to successfully initialize via a call to Init()
	 by converting the link resource's URI to an IDFile.
	 */
	bool					fbInited;

	/**
	 The file referenced in the link resource's URI. 
	 */
	IDFile					fFile;

	/**
	 Key used to access the file's type, creator, file extension, and mime type
	 from the FileTypeRegistry.
	 */
	mutable FileTypeInfoID	fFileTypeInfoID;

	/**
	 Caches used to store the resource's short and long names so that they don't
	 have to regenerated every time.  The caches should always be invalidated
	 every time the handler is initialized. 
	 */
	mutable WideString		fShortNameCache;
	mutable WideString		fShortUINameCache;
	mutable WideString		fLongNameCache;
	mutable WideString		fLongUINameCache;


private:
	// Prevent copy construction and assignment.
	FileLinkResourceHandler(const FileLinkResourceHandler&);
	FileLinkResourceHandler& operator=(const FileLinkResourceHandler&);
};

#endif // __FileLinkResourceHandler__
