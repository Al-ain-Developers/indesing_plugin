//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IImageCacheMgr.h $
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
//  The IImageCacheMgr is a centralized list of image caches which lives off of
//  kDocWorkspaceBoss.  It can be accessed by anyone at any time allowing image
//  caches to be purged separately from the IShape instance which generated it.
//  Moreover, it will allow clients to purge a cache based on when it was last
//  used, its size and amount of time required to regenerate it.
//  
//========================================================================================

#pragma once
#ifndef __IImageCacheMgr__
#define __IImageCacheMgr__

#include "IPMUnknown.h"
#include "IImageStreamManager.h"
#include "ImageID.h"

class IImageCache;

/** 
	IImageCacheMgr
	Description: The IImageCacheMgr is used to store 1 or more in-memory raster images
	for a given page item.  Image's are identified by a UIDRef, resolution and a 32-bit
	selector.  The IImageCacheMgr makes it easy for the Draw method of an IShape implementation
	to store caches at various resolutions for its page item and easily retrieve them.
	One major benefit of the IImageCacheMgr is that it allows copies of page items to easily
	share caches.  It also has the ability to serialize caches to temp files in low memory
	situations without forcing the client to reconstruct the cache from scratch.
*/
class IImageCacheMgr : public IPMUnknown
{
public:	
 	enum { kDefaultIID = IID_IIMAGECACHEMGR };
 
	/**
		Selectors enumeration
	*/
	enum {
		kWildCard = 0,		// matches anything
		kRasterImage = 1,
		kAlphaMask = 2,
		kLinkThumbnail = 4,
		kUncalibratedRasterImage = 5,

		// Transparency effect masks (yes, in theory, there really could be this many on a page item)
		kXP_DSH_PI = 10,
		kXP_DSH_ST = 11,
		kXP_DSH_FI = 12,
		kXP_DSH_CT = 13,
		kXP_ISH_PI = 14,
		kXP_ISH_ST = 15,
		kXP_ISH_FI = 16,
		kXP_ISH_CT = 17,
		kXP_OGL_PI = 18,
		kXP_OGL_ST = 19,
		kXP_OGL_FI = 20,
		kXP_OGL_CT = 21,
		kXP_IGL_PI = 22,
		kXP_IGL_ST = 23,
		kXP_IGL_FI = 24,
		kXP_IGL_CT = 25,
		kXP_BE1_PI = 26,
		kXP_BE1_ST = 27,
		kXP_BE1_FI = 28,
		kXP_BE1_CT = 29,
		kXP_BE2_PI = 30,
		kXP_BE2_ST = 31,
		kXP_BE2_FI = 32,
		kXP_BE2_CT = 33,
		kXP_BE3_PI = 34,
		kXP_BE3_ST = 35,
		kXP_BE3_FI = 36,
		kXP_BE3_CT = 37,
		kXP_BE4_PI = 38,
		kXP_BE4_ST = 39,
		kXP_BE4_FI = 40,
		kXP_BE4_CT = 41,
		kXP_SAT_PI = 42,
		kXP_SAT_ST = 43,
		kXP_SAT_FI = 44,
		kXP_SAT_CT = 45,
		kXP_FTH_PI = 46,
		kXP_FTH_ST = 47,
		kXP_FTH_FI = 48,
		kXP_FTH_CT = 49,
		kXP_DRF_PI = 50,
		kXP_DRF_ST = 51,
		kXP_DRF_FI = 52,
		kXP_DRF_CT = 53,
		kXP_GRF_PI = 54,
		kXP_GRF_ST = 55,
		kXP_GRF_FI = 56,
		kXP_GRF_CT = 57
	};
	
	/**
		Add
		Add a cache to the list along with information about the size of the cache
		and the amount of time needed to compute the cache.  cache->AddRef() will be
		called.  purgeFirst signals the IImageCacheMgr that it should remove this item
		first during a PurgeMemory() call.
		@param imageRef	- IN: the UIDRef of the page item.
		@param cache	- IN: the cache to add.
		@param purgeFirst	- IN: A hint to the memory management system that it is okay to purge
								this cache first as it is being used for a short term purpose.
		@param selector	- IN: Another key.  This key allows the client to store different types of caches.
								For example, you may have a color managed version, an uncalibrated version,
								a drop shadow mask and an alpha mask all at the same resolution for a given
								page item.

	*/
	virtual ErrorCode Add(const UIDRef& imageRef, IImageCache* cache, bool8 purgeFirst = kFalse, uint32 selector = kRasterImage) = 0;
	
	/** Purge an image cache and call cache->Release().  
		@return Return amount of memory purged.
	*/
	virtual uint32 Purge(const UIDRef& imageRef, IImageCache* cache) = 0;
	
	/** Purge all caches matching the given imageRef, resolution and selector.  
		@return Return amount of memory purged.
	*/
	virtual uint32 Purge(const UIDRef& imageRef, const PMReal& resolution, uint32 selector = kWildCard) = 0;

	/** 
		Purge all image caches associated with the given imageRef.
		@return Return amount of memory purged.
	*/
	virtual uint32 Purge(const UIDRef& imageRef, uint32 selector = kWildCard) = 0;

	/** 
		Purge all image caches associated with the given db.
		@return Return amount of memory purged.
	*/
	virtual uint32 Purge(const IDataBase *db, uint32 selector = kWildCard) = 0;
	
	/**
		Get the total size of the image caches tracked by the IImageCacheMgr
	*/
	virtual uint32 GetSize(void) const = 0;
	
	/**
		Return the resolution of the IImageCache which would be returned via QueryClosestResolution().
		This call avoids add-refing of the IImageCache and keeps it out of any LRU lists.
		Returns kTrue if an image is found.
		@param imageRef	- IN: the UIDRef of the page item.
		@param resolution - IN/OUT: On input, the desired resolution.  On output, the actual resolution found.
		@param selector	- IN: Another key.  This key allows the client to store different types of caches.
								For example, you may have a color managed version, an uncalibrated version,
								a drop shadow mask and an alpha mask all at the same resolution for a given
								page item.
		@param selectorFound - OUT: Optional.  If non-nil and a cache is found, the selector of the cache is
			returned.
		@return kTrue if a cache is found, kFalse otherwise.
	*/
	virtual bool16 GetClosestMatchResolution(const UIDRef& imageRef, PMReal& resolution, uint32 selector = kRasterImage,
			uint32* selectorFound = nil) const = 0;

	/**
		Find the closest resolution which is greater than or equal to the requested resolution.
		If one cannot be found, then find the first resolution which is less than the requested
		resolution.  If a cache for the given imageRef cannot be found, then nil is returned.
		@param imageRef	- IN: the UIDRef of the page item.
		@param resolution - IN: the desired resolution.
		@param selector	- IN: Another key.  This key allows the client to store different types of caches.
								For example, you may have a color managed version, an uncalibrated version,
								a drop shadow mask and an alpha mask all at the same resolution for a given
								page item.
		@param selectorFound - OUT: Optional.  If non-nil and a cache is found, the selector of the cache is
			returned.
		@return The image cache matching the input parameters or nil if one is not found.
	*/
	virtual IImageCache* QueryClosestResolution(const UIDRef& imageRef, const PMReal& resolution, uint32 selector = kRasterImage,
				uint32* selectorFound = nil) = 0;

	/**
		Given an imageRef and an image cache, find the next smallest resolution cache for the same image
		@param imageRef	- IN: the UIDRef of the page item.
		@param currentCache - IN: tells the IImageCacheMgr to look relative to this cache.
		@param selector	- IN: Another key.  This key allows the client to store different types of caches.
								For example, you may have a color managed version, an uncalibrated version,
								a drop shadow mask and an alpha mask all at the same resolution for a given
								page item.
		@param selectorFound - OUT: Optional.  If non-nil and a cache is found, the selector of the cache is
			returned.
		@return The image cache matching the input parameters or nil if one is not found.
	*/
	virtual IImageCache* QueryPreviousResolution(const UIDRef& imageRef, const IImageCache& currentCache, uint32 selector = kRasterImage,
				uint32* selectorFound = nil) = 0;
	
	/**
		Given an imageRef and an image cache, find the next largest resolution cache for the same image 
		@param imageRef	- IN: the UIDRef of the page item.
		@param currentCache - IN: tells the IImageCacheMgr to look relative to this cache.
		@param selector	- IN: Another key.  This key allows the client to store different types of caches.
								For example, you may have a color managed version, an uncalibrated version,
								a drop shadow mask and an alpha mask all at the same resolution for a given
								page item.
		@param selectorFound - OUT: Optional.  If non-nil and a cache is found, the selector of the cache is
			returned.
		@return The image cache matching the input parameters or nil if one is not found.
	*/
	virtual IImageCache* QueryNextResolution(const UIDRef& imageRef, const IImageCache& currentCache, uint32 selector = kRasterImage,
				uint32* selectorFound = nil) = 0;

	/**
		Resample an existing cache to create a lower resolution cache.
		@param imageRef	- IN: the UIDRef of the page item.
		@param srcSelector	- IN: Another key.  This key allows the client to store different types of caches.
								For example, you may have a color managed version, an uncalibrated version,
								a drop shadow mask and an alpha mask all at the same resolution for a given
								page item.  The srcSelector is used to help identify the source image from which
								we will resample.
		@param dstSelector - IN: The resulting cache will be added to the ImageCacheMgr using dstSelector as a key.
								Typically, the dstSelector is the same as the srcSelector.
		@param resToResampleFrom	- IN: The source resolution.  This parameter is used as another key for
								identifying the source image cache.
		@param resToResampleTo	- IN: The destination resolution.
		@param sampleType	- IN/OUT: On input, the desired resampling type.  For non-virtual images, AGM does the
							resampling and they support 2 kinds: Bicubic and Dowsampling (averaging).  Therefore, on
							if AGM is used to resample the image and Subsampling is chosen, Downsampling will
							be used instead (which is of higher quality than Subsampling but slower).  On return,
							therefore, this parameter will be set to the actual sampling method used.
		@param bForceNonVirtual	- IN: If the source image is virtual, the typical result of downsampling is
							another virtual image which will downsample from the original EVERY time it is drawn.
							If this cache is going to be used to draw to the screen and will be drawn multiple
							times, then assuming you have enough memory, it is more optimal to convert the image
							to a non-virtual image.  If after conversion the application gets low on memory, the
							ImageCacheMgr will serialize the image to disk.
		@return The resampled image cache matching the input parameters.  Note that the resulting cache will
							automatically be added to the ImageCacheMgr.
	*/
	virtual IImageCache* Resample(const UIDRef& imageRef, uint32 srcSelector, uint32 dstSelector, const PMReal &resToResampleFrom,
									 const PMReal &resToResampleTo, IImageStreamManager::ResamplingType &sampleType,
									 bool32 bForceNonVirtual = kFalse) = 0;

	/**
		OBSOLETE
		Set a maximum amount of memory which can be used by IImageCaches in kilobytes.
	*/
	virtual void SetMaxSize(uint32 kiloBytes) = 0;

	/**
		Purge routine registered with the memory manager which
		uses heuristics to purge image caches.
	*/
	virtual void PurgeMemory(int32 level, bool16 inGrowZone) = 0; // levels from MemUtils.h	
};

#endif
