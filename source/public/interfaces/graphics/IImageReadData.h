//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IImageReadData.h $
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
#ifndef __IImageReadData__
#define __IImageReadData__

#include "IPMUnknown.h"
#include "IImageStream.h"

/**
 Interface that defines mechanism for reading image data from a source.
 
 @see IImageStream
 @see IReadDataImageStreamData
 */
class IImageReadData : public IPMUnknown
{
public:
	/**
	 Reads data from underlying source, based on parameters in the specified
	 image record. The image record defines the geometry for the data to read,
	 including the area to read (left, top, width, height), the bytewidth for
	 the specified buffer, the plane to read (if planar data), as well as the
	 buffer into which the data should be read.

	 @param outImageRecord		IN/OUT Defines dimensions for image, as well as data buffer
	 @return kTrue if read is successful, else kFalse
	 @see IImageStream
	 */
	virtual bool16 ReadData(ImageStreamRecord& outImageRecord) = 0;
};


#endif
