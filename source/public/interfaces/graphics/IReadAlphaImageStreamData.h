//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IReadAlphaImageStreamData.h $
//  
//  Owner: dstephen
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
//  Purpose:
//  Data interface for the ReadAlphasImageStream segment of the IImageStreamManager.
//  This segment is used to read an alpha channel from an image.
//  
//========================================================================================

#pragma once
#ifndef __IReadAlphasImageStreamData__
#define __IReadAlphasImageStreamData__

#include "IPMUnknown.h"

/**
 Data interface for the ReadAlpha segment of the image stream manager. 
 This segment can be used to read a particular channel of data from an image
 (typically an alpha channel).  This interface should probably be private.
 
 @see IImageStreamManager, IImageStream
 */

class IReadAlphaImageStreamData : public IPMUnknown
{
public:

	/** Specify the channel to read
		@param index - IN: zero based and refers to the specific channel of data to retrieve.
			For example, if the image is RGB with 2 alphas (for a total of 5 channels) and
			you want the second alpha, pass 4.
	*/
	virtual void SetChannelToRead (uint16 index) = 0;
	
	/** Specify the number of channels in the source image.
		@param channelsPerPixel - IN: refers to the total number of channels per pixel , including the alphas,
			which will be retrieved from the next image stream segment (the source data to this ImageStream).
	*/
	virtual void SetChannelsPerPixel (uint16 channelsPerPixel) = 0;

	/** Specify the bits per channel of the source data.
		@param bits - IN: Number of bits per channel
	*/
	virtual void SetSourceBitsPerChannel (uint16 bits) = 0;
	
	/** Specify whether the source image is planar or interleaved (chunky)
		@param isPlanar - IN: kTrue for planar, kFalse for interleaved.
	*/
	virtual void SetIsPlanar(bool8 isPlanar) = 0;
	
	/** Retrieve the channel specified via SetChannelToRead
	*/
	virtual uint16 GetChannelToRead (void) const = 0;

	/** Retrieve the channels per pixel value specified via SetChannelsPerPixel
	*/
	virtual uint16 GetChannelsPerPixel (void) const = 0;

	/** Retrieve the bits per channel value specified via SetSourceBitsPerChannel
	*/
	virtual uint16 GetSourceBitsPerChannel (void) const = 0;

	/** Retrieve whether or not the image data is planar.  Specified via SetIsPlanar
	*/
	virtual bool8 GetIsPlanar(void) const = 0;
};

#endif
