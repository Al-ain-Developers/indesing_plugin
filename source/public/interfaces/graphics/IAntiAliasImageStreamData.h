//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IAntiAliasImageStreamData.h $
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
#ifndef __IAntiAliasImageStreamData__
#define __IAntiAliasImageStreamData__

#include "IPMUnknown.h"

/**
 Data interface for the anti-aliasing segment of the image stream manager. 
 This segment can be used to subsample image data to the desired resolution 
 using anti-aliasing (averaging) instead of using the subsampling or bicubic
 downsampling segments.
 
 @see IImageStreamManager
 */
class IAntiAliasImageStreamData : public IPMUnknown
{
public:
	typedef struct {
		uint32	inWidth;		// source number of pixels per scanline
		uint32	inHeight;		// source number of scanlines
		uint32	outWidth;		// destination number of pixels per scanline
		uint32	outHeight;		// destination number of scanlines
		uint32	samplesPerPixel; // number of samples per pixel.
	} AntiAliasInfo;
	
	/**
	 Sets the parameters to use when average downsampling an image.
	 
	 @param antiAliasInfo		IN The parameters to use
	 */
	virtual void SetAntiAliasInfo (const AntiAliasInfo& antiAliasInfo) = 0;
	
	/**
	 Retrieves the parameters to use where average downsampling an image.
	 
	 @param antiAliasInfo		OUT Pointer to storage for parameters to retrieve
	 */
	virtual void GetAntiAliasInfo (AntiAliasInfo* antiAliasInfo) const = 0;
};

#endif
