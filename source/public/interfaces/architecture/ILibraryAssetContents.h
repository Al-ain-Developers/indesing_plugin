//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILibraryAssetContents.h $
//  
//  Owner: Mark VerMurlen
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
//  Reviewed: 9/25/98
//  
//  Purpose:
//  This interface is a secondary interface to the LibraryAsset Boss.  This interface
//  controls reading and writing of the "Content" data of the asset.
//  
//========================================================================================

#pragma once
#ifndef __ILibraryAssetContents__
#define __ILibraryAssetContents__

#include "IPMUnknown.h"
#include "LibraryProviderID.h"

class IDirInfo;
class IPMStream;
class IXferBytes;

/**	A secondary interface to the LibraryAsset boss, this controls reading and writing of the "content" data of an asset.
	@see IDirInfo
*/
class ILibraryAssetContents : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILIBRARYASSETCONTENTS };

	/** What's in an asset, with respect to pageitems and/or structure.
	*/
	typedef enum {
		/** All untagged pageitems
		*/
		kAllUntaggedPageItems = 0,
		/** All tagged pageitems
		*/
		kAllTaggedPageItems,
		/** Mixed tagged and untagged pageitems
		*/
		kMixedTaggedAndUntaggedPageItems,
		/** All structure elements
		*/
		kAllStructureElements,
		/** Unknown makeup
		*/
		kUnknownAssetMakeup
	} AssetMakeup;

	/** Returns a pointer to a stream from which the asset's contents
		can be read.  Pointer must be released by caller.  May return nil if no content data exists.
		@return an IPMStream interface pointer or nil
	*/
	virtual IPMStream* QueryDataReadStream() = 0;

	/** Returns a pointer to a stream to which the asset's contents
		can be written.  Pointer must be released by caller.  May return nil if no content data exists.
		@return an IPMStream interface pointer or nil
	*/
	virtual IPMStream* QueryDataWriteStream() = 0;
	
	/** Deletes the current contents of the asset.
	*/
	virtual void DeleteData() = 0;

	/** Sets the data of an asset.
		@param assetData IN a pointer to the asset data, in INX snippet form
		@param assetDatalength IN the length of the data block
	*/
	virtual void SetAssetData(const uchar* assetData,int32 assetDatalength) = 0;

	/** Sets the data of an asset.
		@param assetData IN a pointer to the asset data, in INX snippet form
		@param assetDatalength IN the length of the data block
	*/
	virtual void SetAssetData(IXferBytes* assetData, int32 assetDatalength) = 0;

	/** Get a pointer to the data block for the asset.
		@return a pointer to the first data character
	*/
	virtual uchar* GetAssetData() const = 0;

	/** Get the length of the data block.
		@return the length of the data block
	*/
	virtual int32 GetAssetDatalength() const = 0;

	/** Get general information on what's in the asset.
		@return an interface pointer to the IDirInfo for the asset.  Must be released by caller.
	*/
	virtual IDirInfo*	QueryDirInfo() { return nil; }

	/** Get pageitem/structure mixture data on the asset.
		@return an AssetMakeup telling what's in the asset.
	*/
	virtual AssetMakeup GetAssetMakeup() = 0;

};

#endif
