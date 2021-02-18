//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPlanarToChunkyImageStmData.h $
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
//  Data interface for the IPlanarToChunkyImageStream segment of the IImageStreamManager.
//  This segment is used to convert planes of image data to interleaved data.
//  
//========================================================================================

#pragma once
#ifndef __IPlanarToChunkyImageStreamData__
#define __IPlanarToChunkyImageStreamData__

#include "IPMUnknown.h"
	
/**
 Data interface for the planar-to-chunky segment of the image stream manager.
 This segment is used to convert planar image data to interleaved (chunky)
 image data.  This interface should probably be private.
 
 @see IImageStreamManager
 */

class IPlanarToChunkyImageStreamData : public IPMUnknown
{
public:
	/** Structure to pass information about the image to the PlanarToChunkImageStream.
	*/
	typedef struct
	{
		/** Width of the image in pixels */
		uint32	width;
		/** Total number of channels in the source image */
		uint32	numChannels;
		/** zero-based index with respect to first color plane of an extra channel to keep. 
			If you set 'alpha' to -1, then all channels after the first 'numChannels' will
			be stripped.
		*/
		int16	alpha;	
	} PlanarToChunkyInfo;

	/**
	 Sets the parameters to use when converting planar image data to chunky (interleaved).
	 
	 @param planarToChunkyInfo	IN The parameters to use when converting an image from planar to chunky
	 */
	virtual void SetPlanarToChunkyInfo (const PlanarToChunkyInfo& planarToChunkyInfo) = 0;
	
	/**
	 Retrieves the parameters to use when converting planar image data to chunky (interleaved).
	 
	 @param planarToChunkyInfo	OUT Pointer to storage to receive parameters to use when converting an image from planar to chunky
	 */
	virtual void GetPlanarToChunkyInfo (PlanarToChunkyInfo* planarToChunkyInfo) const = 0;
};

#endif
