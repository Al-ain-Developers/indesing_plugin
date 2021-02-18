//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ILibraryAssetThumbnail.h $
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
//  controls reading and writing of the "Thumbnail" image of the asset.
//  
//========================================================================================

#pragma once
#ifndef __ILibraryAssetThumbnail__
#define __ILibraryAssetThumbnail__

#include "IPMUnknown.h"
#include "LibraryProviderID.h"


class IPMStream;

/** This secondary interface to the LibraryAsset boss controls reading and writing of the 
	"thumbnail" image for the asset.  Library asset thumbnail images are defined to be
	uncompressed 24 bit/pixel RGB images with a line byte width which is a multiple of
	4 bytes.
*/
class ILibraryAssetThumbnail : public IPMUnknown
{
public:
	
	// This is the maximum x or y dimension of a thumbnail image
	enum {
		kLibAssetThumbnailMaxSize = 112
	};
	
	/** Sets the thumbnail to the given image.
		@param xSize IN width in pixels
		@param ySize IN height in pixels
		@param bitmapPtr IN pointer to the bitmap
		@param bitmapSize IN the size of the bitmap in bytes
	*/
	virtual void Set(int16 xSize, int16 ySize, const void *bitmapPtr, int32 bitmapSize) = 0;
	
	/** Gets the thumbnail image X and Y pixel count.
		@param xSize OUT the width in pixels
		@param ySize OUT the height in pixels
	*/
	virtual void GetDimensions(int16 &xSize, int16 &ySize) const = 0;
		
	/** Gets the size in bytes of the thumbnail image bitmap.
		@param bitmapSize OUT hte size of the bitmap in bytes
	*/
	virtual void GetImageSize(int32 &bitmapSize) const = 0;
		
	/** Copy the thumbnail image bitmap to a buffer.
		@param bitmapPtr IN a pointer to the bitmap -- caller must allocate the buffer
	*/
	virtual void GetImage(void *bitmapPtr) const = 0;
		
	/** Deletes the thumbnail.
	*/
	virtual void Delete() = 0;
		
};


#endif
