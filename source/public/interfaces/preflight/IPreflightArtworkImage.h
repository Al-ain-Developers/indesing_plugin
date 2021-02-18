//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightArtworkImage.h $
//  
//  Owner: Matt Phillips
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
//========================================================================================

#pragma once

#include "IPMUnknown.h"
#include "PackageAndPreflightID.h"
#include "GraphicTypes.h"

class IPreflightArtworkCSInfo;

/**	This interface provides access to image data provided from mark or group interfaces. 
	In particular, IPreflightArtworkMarkInfo::Rasterize(). This interface sits on a boss
	pretty much all by itself. Typically it's used to look at a raster version of some
	object when inspecting the attributes are not sufficient.

	@see IPreflightArtworkMarkInfo
*/

class IPreflightArtworkImage : public IPMUnknown
{
public:
	enum
	{
		/** The default rasterization set: no alpha
		*/
		kRF_Default = 0,

		/** Include an alpha channel in the rasterized image.
		*/
		kRF_Alpha = (1L<<0)
	};

	enum { kDefaultIID = IID_IPREFLIGHTARTWORKIMAGE };

public:
	/** Get the pixel bounds of the image.
		@return The pixel bounds of the image.
	*/
	virtual Int32Rect GetBounds() const = 0;

	/** Get the colorspace information. You'll need this to get most of the stats about the
		space, including whether it has alpha, how many channels, which channel is which, etc.

		@return A refcounted colorspace info interface.
	*/
	virtual IPreflightArtworkCSInfo* QueryColorSpace() const = 0;

	/** Get a pointer to the image data for a particular pixel.

		@param channel IN Which channel you want a pointer to.
		@param x IN The x coordinate in GetBounds() space (note that xMin, xMax can be negative)
		@param y IN The y coordinate in GetBounds() space (note that yMin, yMax can be negative)
		@return A pointer to the pixel/channel, or nil if any of the parameters are out of bounds.
	*/
	virtual const uint8* GetPixelPtr(int32 channel, int32 x, int32 y) const = 0;

	/** Get the number of bytes between pixels (in a given row). This along with GetPixelPtr() allows
		you to walk the pixel data quickly, but you need to be careful to use it properly. In 
		particular you need to use GetPixelIncrement() to know how far to move in a given row
		and GetRowIncrement() to know how to move to the same pixel in the next/prev row.

		@param n The channel for which you want the increment. In some cases (eg separate alpha)
			the channel data may be in a completely separate piece of memory with a different
			row/pixel increment from other channels.
		@return The number of bytes to add to a pixel pointer to get to the next (x+1) pixel in the same row.
	*/
	virtual int32 GetPixelIncrement(int32 channel) const = 0;

	/** Get the number of bytes between rows. This along with GetPixelPtr() and GetPixelIncrement()
		allows you to walk the pixel data quickly, but you need to be careful to use it properly. In 
		particular you need to use GetPixelIncrement() to know how far to move in a given row
		and GetRowIncrement() to know how to move to the same pixel in the next/prev row.

		@param n The channel for which you want the increment. In some cases (eg separate alpha)
			the channel data may be in a completely separate piece of memory with a different
			row/pixel increment from other channels.
		@return The number of bytes to add to a pixel pointer to get to the same pixel in the next (y+1) row.
	*/
	virtual int32 GetRowIncrement(int32 channel) const = 0;

	/** Alternative pixel interface that provides chunky pixels. If you want to look at all of the
		channels of the data together, chunky is generally easiest, but the generic accessors above
		support chunky, planar, or a combination, so it's hard to make a compact and efficient 
		algorithm (the general case involves incrementing N pointers for each pixel). The chunky 
		accessors will rearrange pixel data on a scanline basis *if necessary* in order to provide 
		chunky data. If the data is already chunky then this is a very fast operation; if it's not, 
		it's going to be as least as fast as any chunkifier you would write.

		This method obtains a pointer to chunky data for the specified scanline. (And only that
		scanline; you can't generally go beyond or before this in order to get next/prev rows.)

		@param y IN The Y coordinate of the scanline in which you're interested. Must be within
			the bounds (@see GetBounds).
		@return A pointer to the chunky scanline data. You need to release this when you're done
			via @see ReleaseChunkyScanline.
	*/
	virtual const uint8* QueryChunkyScanline(int32 y) const = 0;

	/** Releases the scanline reserved by QueryChunkyScanline.

		@param p IN The scanline you're releasing. After this you should not attempt to access it.
	*/
	virtual void ReleaseChunkyScanline(const uint8* p) const = 0;

	/** Obtains the byte size of each pixel; ie the increment by which you should increase the pointer
		to get to the next pixel.

		@return The number of bytes between pixel origins.
	*/
	virtual const int32 GetChunkyPixelSize() const = 0;

	/** Sets the colorspace. Internal use only.
		@param iCS IN The colorspace.
	*/
	virtual void SetColorSpace(const InterfacePtr<IPreflightArtworkCSInfo>& iCS) = 0;

	/** Sets the bounds. Internal use only.
		@param b IN The bounds.
	*/
	virtual void SetBounds(const Int32Rect& b) = 0;

	/** Sets the shared buffer. Internal use only.
		@param buf IN The buffer; this is an opaque type, not a memory buffer.
	*/
	virtual void SetSharedBuffer(void* buf) = 0;

	/** Sets the pixel increment. Internal use only.
		@param inc IN The increment.
	*/
	virtual void SetPixelIncrement(int32 inc) = 0;

	/** Sets the row increment. Internal use only.
		@param inc IN The increment.
	*/
	virtual void SetRowIncrement(int32 inc) = 0;
};

