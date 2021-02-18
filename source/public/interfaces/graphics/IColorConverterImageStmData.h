//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IColorConverterImageStmData.h $
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
//  Data interface for the IColorConverterImageStream segment of the IImageStreamManager.
//  This segment is used to convert image data from one color space to another using either
//  uncalibrated methods or client supplied profile information.
//  
//========================================================================================

#pragma once
#ifndef __IColorConverterImageStreamData__
#define __IColorConverterImageStreamData__

#include "IPMUnknown.h"
#include "BravoForwardDecl.h"

class ICMSProfile;

/** IColorConverterImageStreamData
	This class is a data interface for the ColorConverterImageStream, which is an implementation of IImageStream used
	by the ImageStreamManager to convert image data from one colorspace to another.  Various IImageStreams are
	pipelined together by the ImageStreamManager in order to convert a source image to a destination image
	with a given set of attributes.  This interface should probably be private.
	@see IImageStreamManager.h
*/

class IColorConverterImageStreamData : public IPMUnknown
{
public:
	/** ColorConverterInfo structure.
		width				How many pixels wide is the source image
		numExtraChannels	How many alpha channels are in the source image 
		srcColorSpace		One of kPMGrayColorSpace, kPMRGBColorSpace, kPMCMYKColorSpace, kPMICCLabColorSpace.
							Can compute color channels from space
		dstColorSpace		One of kPMGrayColorSpace, kPMRGBColorSpace, kPMCMYKColorSpace, kPMICCLabColorSpace.
							Can compute color channels from space
		srcProfile			Pointer to CMSProfile of source image.
		dstProfile			Pointer to CMSProfile of destination image.
		srcAGMColorSpace	Pointer to AGMColorSpace of source image.
		dstAGMColorSpace	Pointer to AGMColorSpace of destination image.
	*/
	typedef struct
	{
		uint32	width;
		uint32  numExtraChannels;  
		uint32	srcColorSpace; // Can compute color channels from space
		uint32	dstColorSpace; // Can compute color channels from space
		ICMSProfile *srcProfile;
		ICMSProfile *dstProfile;
		AGMColorSpace *srcAGMColorSpace;
		AGMColorSpace *dstAGMColorSpace;
	} ColorConverterInfo;
	
	/* Set method
		@param colorConverterInfo - IN: Specifies information about the source image and the desired
			target image.
	*/
	virtual void SetColorConverterInfo (const ColorConverterInfo& colorConverterInfo) = 0;
	
	/* Get method
		@param colorConverterInfo - Out: Obtains information about the source image and the desired
			target image.
	*/
	virtual void GetColorConverterInfo (ColorConverterInfo* colorConverterInfo) const = 0;
};

#endif
