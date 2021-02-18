//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IConvertDepthImageStreamData.h $
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
#ifndef __IConvertDepthImageStreamData__
#define __IConvertDepthImageStreamData__

#include "IPMUnknown.h"

/**
 Data interface for the ConvertBitDepthImageStream segment of the ImageStreamManager.
 The segment is used to convert to or from 8-bit data.  To convert from bit depth X to bit
 depth Y, where X and Y are not 8, create 1 segment which converts from X to 8-bit Hi or Low,
 and another segment which converts the results of the previous segment to Y.
 
 @see ImageStreamManager
*/
class IConvertDepthImageStreamData : public IPMUnknown
{
public:
	/** enum of the bit depth conversion options.
		kConvertFromP8Hi		8-bits of image data is in the high byte
		kConvertFromP8Low		8-bits of image data is in the low byte
		kConvertToP8Hi			If source data is 16 bit, convert to 8 bit.  Otherwise, convert to target bitdepth
								with 8-bits of image data in high byte.
		kConvertToP8Low			Convert to target bitdepth with 8-bits of image data in low byte.
	*/
	typedef enum 
	{
		kConvertFromP8Hi	= 1,
		kConvertFromP8Low	= 2,
		kConvertToP8Hi		= 3,
		kConvertToP8Low		= 4
	} ConvertType;

	/** ConvertDepthInfo structure
		width				How many pixels wide is the image data?
		bitdepth			If convertType is kConvertFromP8Hi or kConvertFromP8Low, then bitdepth is the target bitdepth.  Otherwise,
							it is the source bitdepth.
		numberOfChannels	Number of source channels
		threshold			If converting to 1-bit from 8-bit, use this threshold to determine whether the 8 bit value should become a 0 or 1.
		unused[3]			long alignment
		convertType			One of kConvertFromP8Hi, kConvertFromP8Low, kConvertToP8Hi, kConvertToP8Low
	*/
	typedef struct {
		uint32		width;
		uint32		bitdepth;
		uint32		numberOfChannels;
		uint8		threshold;
		uint8		unused[3];	//long align
		ConvertType	convertType;
	} ConvertDepthInfo;

	/**
	 Stores the settings used by kConvertBitDepthImageStreamBoss
	 
	 @param convertDepthInfo		The settings to use
	*/
	virtual void SetConvertDepthInfo (const ConvertDepthInfo& convertDepthInfo) = 0;
	
	/**
	 Retrieves the settings used by kConvertBitDepthImageStreamBoss
	 
	 @param convertDepthInfo		The settings to retrieve
	*/
	virtual void GetConvertDepthInfo (ConvertDepthInfo* convertDepthInfo) const = 0;
	
};

#endif
