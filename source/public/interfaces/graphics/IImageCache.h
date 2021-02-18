//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IImageCache.h $
//  
//  Owner: Dave Stephens
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
//  Purpose of Interface:
//  The IImageCache is a wrapper around an AGMImageRecord which provides a mechanism
//  for storing statistical data such as amount of time used to create the cache, resolution
//  of the cache, frequency of use, etc.
//  
//  References:  The IImageCacheMgr manages a list of IImageCache objects.
//  
//========================================================================================

#pragma once
#ifndef __IImageCache__
#define __IImageCache__

#include "AGMImageAccessor.h"
#include "GraphicsData.h"

#include "IPMUnknown.h"
#include "ColorSystemID.h"
#include "BravoForwardDecl.h"

class PMMatrix;
class IGeometry;

/** IImageCache
	This class contains an AGM Image plus additional information and metrics used by the ImageCacheManager
	to determine which IImageCache's should be serialized/virtualized to disk in low memory situations.
*/
class IImageCache : public IPMUnknown
{
public:	
	/** Initialize the ImageCache - image will be owned by the ImageCache and should not be deleted
		by the client.  Image should be a heap ptr and not a stack ptr (i.e., don't pass in the address
		of a local stack based AGMImageAccessor variable).
		@param image - IN: Ptr to a valid non-stack based AGMImageAccessor
		@param resolution - IN: Image resolution.  Used as a key by the ImageCacheManager.
		@param ticksToGenerate - IN: A tick is 1/60th of a second.  This metric is used by the ImageCacheManager to
			determine the cost of generating this cache from scratch.
		@param profileChecksum - IN: A checksum of the color profile for the image.  This value is used as a key by the
			ImageCacheManager and is useful if two caches with the same resolution exist for the same page item.
		@param adjustmentMatrix - IN: The adjustment needed to align the image.  Used when the image itself doesn't 
			represent all the info needed for this purpose (e.g., transparency effect masks, which require additional
			translation information).  Not used by the image cache manager since it does not change the uniqueness
			of the cache entry.
	*/
	virtual void Init(AGMImageAccessor* image, uint32 resolution, uint32 ticksToGenerate, uint32 profileChecksum = 0L, const PMMatrix& adjustmentMatrix = PMMatrix()) = 0;
	
	/** Returns resolution of the image in the cache as specified in the Init method.
	*/
	virtual uint32 GetResolution(void) const = 0;
	
	/** Returns size of the image in the cache where the size is defined as the rowbytes * height + the number of colors
		in the color map (if one exists).
	*/
	virtual uint32 GetSize(void) const = 0;
	
	/** Returns number of ticks needed to generate the cache as specified in the Init method
	*/
	virtual uint32 GetGenerateTime(void) const = 0;
	
	/** Returns the time (in ticks) of the last time this cache was drawn
	*/
	virtual uint32 GetLastDrawTime(void) const = 0;
	
	/** Returns the number of times Draw() has been drawn
	*/
	virtual uint32 GetDrawCount(void) const = 0;

	/** Returns one of kPMGrayColorSpace, kPMRGBColorSpace, kPMCMYKColorSpace, kPMICCLabColorSpace
	*/
	virtual uint32 GetColorFamily(void) const = 0;
	
	/** Returns the Checksum of the source profile for this image as specified in the Init method.
	*/
	virtual uint32 GetProfileChecksum(void) const = 0;

	/** Returns the adjustment matrix as specified through Init.
	*/
	virtual const PMMatrix& GetAdjustmentMatrix(void) const = 0;

	/** Returns the image record - care should be taken not to delete any fields
	*/
	virtual AGMImageAccessor* GetImageAccessor(void) const = 0;
	
	/** Draw the cache
		@param gd - IN: Pointer to information about the destination device.
		@param imageGeometry - IN: Pointer to the IGeometry of the image's corresponding page item.
		@param additionalXform - IN: If there are additional transforms you want applied to the image while drawing, pass them here.
		@param colorSpace - IN: Used when applying a color to a grayscale image.
		@param tint - IN: Used when applying a color to a grayscale image.
	*/
	virtual void Draw(const GraphicsData* gd, IGeometry* imageGeometry, const PMMatrix& additionalXform = PMMatrix(), const AGMColorSpace* colorSpace = nil, const PMReal& tint = kDefaultTintPercent) = 0;
};

#endif
