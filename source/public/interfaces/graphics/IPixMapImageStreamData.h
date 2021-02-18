//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPixMapImageStreamData.h $
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
//  Purpose:
//  Data interface for the IPixMapImageStream segment of the IImageStreamManager.
//  This segment is used simply to read a PixMap into an ImageStream.
//  
//========================================================================================

#pragma once
#ifndef __IPixMapImageStreamData__
#define __IPixMapImageStreamData__

#include "IPMUnknown.h"

/**
 Data interface for PixMapImageStream segment of the image stream manager.
 This segment is used to target a pixmap as the source image for an ImageStreamManager
 conversion.  This interface should probably be private.
 
 @see IImageStreamManager
 */
class IPixMapImageStreamData : public IPMUnknown
{
public:
	/** Pixel channel value considered to be transparent */
	enum { kTransparentSampleValue = 0xFE };

	/** Set the pixmap used by PixMapImageStream. 
		
		@param pixMap - IN: The source image.  The client still owns the pixmap
			and should dispose of it after releasing the ImageStreamManager.  Do not
			dispose of the pixMap until the ImageStreamManager is disposed.
		@param AddNonWhiteAlpha - IN: The AddNonWhiteAlpha is used as follows:
			If kTrue then an alpha channel byte will added after each
			pixel (e.g., RGBARGBA...) where the value of each component is
			not kTransparentSampleValue.  Additionally, if each component is kTransparentSampleValue, 
			then the component will be set to 0xFF.  So, a client could initialize an image buffer 
			to kTransparentSampleValue, draw into the buffer, and any pixel which was marked by 
			something other than kTransparentSampleValue in any of the components will have a 
			non-zero alpha (effectively clipping out all other pixels).
	*/
	virtual void SetPixMap (PixMapHandle pixMap, bool8 AddNonWhiteAlpha) = 0;

	/** Return the source image.
	*/
	virtual const PixMapHandle GetPixMap () const = 0;

	/** Return the current AddNonWhiteAlpha value
	*/
	virtual bool8 GetAddNonWhiteAlpha () const = 0; 
};

#endif
