//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IChunkyToIndexedImageStmData.h $
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
#ifndef __IChunkyToIndexedImageStreamData__
#define __IChunkyToIndexedImageStreamData__

#include "IPMUnknown.h"

/**
 Data interface for the IChunkyToIndexedImageStream segment of the IImageStreamManager.
 
 This segment is used to convert interleaved RGB data, RGBRGBRGB..., to indexed RGB, III...
 This segment allows for extra channels of data.  For example RGBXYZRGBXYZRGBXYZ (RGB plus alpha
 X, alpha Y and alpha Z) to IXYZIXYZIXYZ.
 
 The colormap is a series of RGB triplets, starting at index 0 and working up.
 If numColors < 256 the unused entries must by 0!!!

 Note: Assumes RGB!!!
 Note: The colormap is copied during set.
 
 @see IImageStreamManager
 */
 
class IChunkyToIndexedImageStreamData : public IPMUnknown
{
public:

	typedef struct
	{
		uint32	width;
		uint32	height;
		uint32	numChannels;  // there could be extra channels
		uint8*	colorMap;     // use this if generateMap is false.  768 = 3 * 256 = RGB 256 entries
		bool16	dither;		
	} ChunkyToIndexedInfo;

	/**
	 Stores the provided settings in the interface
	 
	 @param chunkyToIndexedInfo		The settings to store
	 */
	virtual void SetChunkyToIndexedInfo (const ChunkyToIndexedInfo& chunkyToIndexedInfo) = 0;
	
	/**
	 Retrieves the settings stored in the interface
	 
	 @param chunkyToIndexedInfo		The settings to retrieve
	 */
	virtual void GetChunkyToIndexedInfo (ChunkyToIndexedInfo* chunkyToIndexedInfo) const = 0;

};

#endif
