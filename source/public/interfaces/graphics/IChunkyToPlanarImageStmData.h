//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IChunkyToPlanarImageStmData.h $
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
//  
//========================================================================================

#pragma once
#ifndef __IChunkyToPlanarImageStreamData__
#define __IChunkyToPlanarImageStreamData__

#include "IPMUnknown.h"	

/**
 Data interface for the chunky-to-planar segment of the image stream manager.
 This segment is used to convert interleaved (chunky) image data to planar 
 image data.
 
 @see IImageStreamManager
 */
class IChunkyToPlanarImageStreamData : public IPMUnknown
{
public:
	typedef struct
	{
		uint32	width;			// number of pixels
		uint32	numChannels;	// number of channels per pixel
	} ChunkyToPlanarInfo;
	
	/**
	 Sets the parameters to use when converting chunky image data to planar.
	 
	 @param chunkyToPlanarInfo	IN The parameters to use when converting an image from chunky to planar
	 */
	virtual void SetChunkyToPlanarInfo (const ChunkyToPlanarInfo& chunkyToPlanarInfo) = 0;
	
	/**
	 Retrieves the parameters to use when converting chunky image data to planar.
	 
	 @param chunkyToPlanarInfo	OUT Pointer to storage to receive parameters to use when converting an image from chunky to planar
	 */
	virtual void GetChunkyToPlanarInfo (ChunkyToPlanarInfo* chunkyToPlanarInfo) = 0;
};

#endif
