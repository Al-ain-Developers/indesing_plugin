//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IDownSampleImageStreamData.h $
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
//  
//  Purpose:
//  Data interface for the DownSampleImageStream segment of the IImageStreamManager.
//  This segment is used to downsample the given image data to the desired resolution.
//  Note: alpha data must be removed using the IMungeSamplesImageStream segment prior
//  to downsampling.
//  
//========================================================================================

#pragma once
#ifndef __IDownSampleImageStreamData__
#define __IDownSampleImageStreamData__

#include "IPMUnknown.h"

/** IDownSampleImageStreamData
	This class is a data interface for the DownSampleImageStream, which is an implementation of IImageStream used
	by the ImageStreamManager to subsample image data to reduce the resolution.  Various IImageStreams are
	pipelined together by the ImageStreamManager in order to convert a source image to a destination image
	with a given set of attributes.  This interface should probably be private.
	@see IImageStreamManager.h
*/
class IDownSampleImageStreamData : public IPMUnknown
{
public:
	/** DownSampleInfo structure
		inWidth				source pixels per scanline
		inHeight			source number of scanlines
		outWidth			destination pixels per scanline
		outHeight			destination number of scanlines
		samplesPerPixel		number of color samples per pixel
	*/
	typedef struct {
		uint32	inWidth;			// source pixels per scanline
		uint32	inHeight;			// source number of scanlines
		uint32	outWidth;			// destination pixels per scanline
		uint32	outHeight;			// destination number of scanlines
		uint32	samplesPerPixel;	// number of color samples per pixel
	} DownSampleInfo;

	/**
		Set method for specifying downsampling information.
		@param downSampleInfo - IN: structure containing downsampling information.
	*/
	virtual void SetDownSampleInfo (const DownSampleInfo& downSampleInfo) = 0;
	
	/**
		Get method for obtaining downsampling information.
		@param downSampleInfo - Out: structure containing downsampling information.
	*/
	virtual void GetDownSampleInfo (DownSampleInfo* downSampleInfo) const = 0;
};

#endif
