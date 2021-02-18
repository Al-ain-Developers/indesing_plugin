//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IHTTPLinkCachedAssetEntry.h $
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
#ifndef __IHTTPLinkCachedAssetEntry__
#define __IHTTPLinkCachedAssetEntry__

#include "IPMUnknown.h"
#include "LinksID.h"

#include "ILinkResource.h"

#include "IHTTPLinkResourceServerAPIWrapper.h"
/*
 AdobePatentID="P7137-US"
 AdobePatentID="P7225-US"
 AdobePatentID="P7609-US"
*/

/**
This abstract class is used by server cache and http links mechanism to refer a
 downloaded http asset. This is not part of any boss class. It emcompasses one
 entry in server cache(refer to IHTTPLinkResourceServerCache.h for more details).
 It contains information about the downloaded asset location and metadata(see
 AssetMetadata in IHTTPLinkResourceServerAPIWrapper for more details). It contains
 functions related to operations on asset.
 
 @see IHTTPLinkResourceServerAPIWrapper
 @see IHTTPLinkResourceServerCache
*/
class IHTTPLinkCachedAssetEntry
{
public:
	/**
	Checks if the file exists in cache
	@return kTrue if file exists in cache else kFalse.
	**/
	virtual bool16 Exists() = 0;

	/**
	Checks if the file in the cache is readable or not.
	@return kTrue if file in cache is readable else kFalse.
	**/
	virtual bool16 CanRead() = 0;

	/**
	Checks if the file in the cache can be opened or not.
	@return kTrue if file in cache can be opened else kFalse.
	**/
	virtual bool16 CanCreateReadStream() = 0;

	/**
	Checks if we can create a Stream for the file in cache.
	@return kTrue if we can create a Stream for the file in cache else kFalse.
	**/
	virtual IPMStream* CreateReadStream() = 0;

	/**
	Checks if the file in cache can be copied to file.
	@return kTrue if cached file can be copied to file else kFalse.
	**/
	virtual bool16 CanCopyToFile() = 0;

	/**
	Copy to cached file to outFile.
	@param	outFile     [OUT] the output file where the cached file is to be copied
	@return kSuccess if the operation is successful else kFalse
	**/
	virtual ErrorCode CopyToFile(IDFile& outFile) = 0;

	/**
	Gets the file type info for the cached file
	@return File type info for the specified file.
	**/
	virtual FileTypeInfo GetFileTypeInfo() = 0;

	/*
	Fills the packet with XMPInfo of the cached file.
	@param	packet     [OUT] the output packet with XMPInfo of the cached file.
	@return true if the operation is successful else false
	*/
	virtual bool GetXMPPacketInfo(std::string& packet) const = 0;

	/*
	Checks if we can get the file in cache or not
	@return true if we can get the file in cache or false
	*/
	virtual bool CanGetFile() const = 0;

	/*
	Fills the passed file with the cached file.
	@param	file     [OUT] the output file to be filled with the cached file.
	@return true if the output file to be filled with the cached file else false
	*/
	virtual bool GetFile(IDFile& file) const = 0;

	/**
	Checks if the cached file is valid.
	@return kTrue if the file is valid or not
	**/
	virtual bool16 IsValid()  { return fIsValid;  }

	/**
	Checks if the cached file is stale.
	@param	assetCurrentAttributes     [IN] the current asset attributes which would be compared with to determine staleness of cached asset file
	@return kTrue if the file is stale else kFalse
	**/
	virtual bool16 IsStale(const IHTTPLinkResourceServerAPIWrapper::AssetMetadataPtr  assetCurrentAttributes) = 0;

	/**
	Sets the cached file as valid
	@param	valid     [IN] the cached file is valid or not.
	**/
	virtual void SetValid(bool16 valid)  { fIsValid = valid; }

	IHTTPLinkCachedAssetEntry() : fIsValid(kTrue) {}

	virtual ~IHTTPLinkCachedAssetEntry() {}

	virtual void ReadWrite(IPMStream *s) = 0;
	
private:
	bool16	fIsValid;
};

#endif	// __IHTTPLinkCachedAssetEntry__
