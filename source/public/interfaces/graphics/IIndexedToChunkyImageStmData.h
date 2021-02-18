//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IIndexedToChunkyImageStmData.h $
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
//  Data interface for the IIndexedToChunkyImageStream segment of the IImageStreamManager.
//  This segment is used to convert colormapped image data to interleaved data.
//  
//========================================================================================

#pragma once
#ifndef __IIndexedToChunkyImageStreamData__
#define __IIndexedToChunkyImageStreamData__

#include "IPMUnknown.h"
	
/** IIndexedToChunkyImageStreamData
	This class is a data interface for the IndexedToChunkyImageStream, which is an implementation of IImageStream used
	by the ImageStreamManager to convert an indexed image to non-indexed.  Various IImageStreams are
	pipelined together by the ImageStreamManager in order to convert a source image to a destination image
	with a given set of attributes.  This interface should probably be private.
	@see IImageStreamManager.h
*/
class IIndexedToChunkyImageStreamData : public IPMUnknown
{
public:
	/** Data structure specifying attributes of the data.  This structure contains
		the number of pixels wide, the number of channels per pixel of the source data, 
		the number of color channels in the colorMap and a pointer to the color map.
	*/
	typedef struct
	{
		uint32	width;
		uint32	numChannels;
		uint32	numColorChannels;
		uint8*	colorMap; // Size is numColorChannels * 256 
	} IndexedToChunkyInfo;
	
	/** Set method which specifies information about the image data that the IndexedToChunkyImageStream
		will see.
		@param indexedToChunkyInfo - IN: This structure contains
			the number of pixels wide, the number of channels per pixel of the source data, 
			the number of color channels in the colorMap and a pointer to the color map.  If
			the numChannels is greater than 1, then the first channel is considered the index
			and the other channels are considered alpha.
			Note that a copy of the colorMap is made and hence the caller is still responsible for
			disposing of the colorMap passed into this method.
	*/
	virtual void SetIndexedToChunkyInfo (const IndexedToChunkyInfo& indexedToChunkyInfo) = 0;
	
	/** Get method for obtaining information about the image data that the IndexedToChunkyImageStream
		will see.
		@param indexedToChunkyInfo - OUT: This structure contains
			the number of pixels wide, the number of channels per pixel of the source data, 
			the number of color channels in the colorMap and a pointer to the color map.  If
			the numChannels is greater than 1, then the first channel is considered the index
			and the other channels are considered alpha.  Do not delete the colorMap that is returned.
	*/
	virtual void GetIndexedToChunkyInfo (IndexedToChunkyInfo* indexedToChunkyInfo) const = 0;
};

#endif
