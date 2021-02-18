//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IReadDataImageStreamData.h $
//  
//  Owner: jargast
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
#ifndef __IReadDataImageStreamData__
#define __IReadDataImageStreamData__

#include "IPMUnknown.h"

class IImageReadData;

/** IReadDataImageStreamData
	This class is a data interface for the ReadDataImageStream, which is an implementation of IImageStream used
	by the ImageStreamManager as the first image stream segment in the pipeline to actually read untouched source
	data from disk or a database to pass to IImageStreamFormat implementations.  Each page item boss that is associated
	with image data typically has an IID_IIMAGEREADDATA interface such that it can be asked to obtain the source
	data.  The implementation of this IID_IIMAGEREADDATA is passed to the SetImageReadData method in this class.
	@see IImageStreamManager.h, IImageReadData.h, IImageReadformat.h
*/
class IReadDataImageStreamData : public IPMUnknown
{
public:
	/** Set method to specify which IImageReadData to use to obtain source image data from disk or embedded pub data, etc.
		@param iImageReadData - IN: Pointer to the IImageReadData for this image.  Note that the iImageReadData is not
		AddReferenced by this call.
	*/
	virtual void SetImageReadData (IImageReadData* iImageReadData) = 0;
	
	/** Set method to specify which IImageReadData to use to obtain source image data from disk or embedded pub data, etc.
		@return Pointer to the IImageReadData for this image.  Note that the IImageReadData IS AddReferenced by this call.
	*/
	virtual IImageReadData* QueryImageReadData () = 0;

	/** SetClip sets a clipping relative to the image, where (0,0) is the upper left, such that pixels 
		outside of the clip will be have 'fillColor' assigned to each channel.  By default, no clipping is
		applied. Using this method is optional.
		@param clipBounds [IN]: the clipping rect defined relative to upper left of image.  Pass an
			empty rectangle to remove the clipping.
		@param fillColor [IN]: value to assign to each channel of each pixel outside the clip.  By filling the
			clipped out portion of the image with a solid color, compression algorithms can effectively eliminate
			the impact of the clipped data on the total size of the data.
		@param numChannelsPerPixel [IN]: number of channels per pixel in the source data that is being read.
			This value is important in order to know how many bytes of data to fill with the fillColor if
			the 'clipBounds' clips out a portion of a scanline.
	*/
	virtual void SetClip(const PMRect& clipBounds, uint16 fillColor, uint32 numChannelsPerPixel) = 0;

	/** Get the values passed to SetClip.
		@param clipBounds [OUT]: rectangle most recently passed to SetClip. Ignore if return value is false.
		@param fillColor [OUT]: optional. If non-nil and true is returned, then fillColor will contain the
			value passed for 'fillColor' to the most recent call to SetClip.
		@param numChannelsPerPixel [OUT]: optional. if non-nil, will contain the number of source channels per pixel
			that was passed into SetClip.
		@return true if SetClip has been called with a non-empty rectangle.
	*/
	virtual bool GetClip(PMRect& clipBounds, uint16* fillColor, uint32* numChannelsPerPixel) const = 0;
};

#endif
