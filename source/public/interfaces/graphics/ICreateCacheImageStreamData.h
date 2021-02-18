//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ICreateCacheImageStreamData.h $
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
#ifndef __ICreateCacheImageStreamData__
#define __ICreateCacheImageStreamData__

#include "IPMUnknown.h"

/** ICreateCacheImageStreamData
	This class is a data interface for the CreateCacheImageStream, which is an implementation of IImageStream 
	(on the kCreateCacheImageStreamBoss) used
	by the ImageStreamManager to the results of an image stream conversion.  Various IImageStreams are
	pipelined together by the ImageStreamManager in order to convert a source image to a destination image
	with a given set of attributes.  This interface should probably be private.
	@see IImageStreamManager
*/
class ICreateCacheImageStreamData : public IPMUnknown
{
public:
	/** CreateCacheInfo structure defining where to cache the results as well as information about the image
		data that will be streamed when calling the ReadData method of the next IImageStream segment from
		the current IImageStream::ProcessImageTile method.
	*/
	typedef struct
	{
		uint8*	cachePtr;
		uint32	numChannels;
		uint32	width;
		uint32	bits;
	} CreateCacheInfo;

	/**
	 Stores the settings used by kCreateCacheImageStreamBoss
	 
	 @param createCacheInfo		The settings to use
	*/
	virtual void SetCreateCacheInfo (const CreateCacheInfo& createCacheInfo) = 0;
	
	/**
	 Retrieves the settings used by kCreateCacheImageStreamBoss

	 @param createCacheInfo		The settings to retrieve
	*/
	virtual void GetCreateCacheInfo (CreateCacheInfo* createCacheInfo) const = 0;
};

#endif
