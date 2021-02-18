//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IImageStream.h $
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
#ifndef __IImageStream__
#define __IImageStream__

#include "IPMUnknown.h"
#include "ImageID.h"

#define BYTES2ROWBYTES(x) ((((uint32)(x) + 3) >> 2) << 2)
#define BITS2ROWBYTES(x) ((((uint32)(x) + 31) >> 5) << 2)

typedef struct
{
	uint8*		fBuffer;		// preallocated buffer with size = fRowBytes * fHeight;
	uint32		fTop;
	uint32		fLeft;
	uint32		fWidth;			// Image Width, must be <= fRowBytes
	uint32		fHeight;
	uint32		fRowBytes;		// number of bytes in a row (desirable to be a multiple of 4)
	uint32		fPlane;			// index of color plane to return.  This only applies if the
								// destination configuration is planar.  If chunky, this field
								// is ignored.
} ImageStreamRecord;

class IImageStream : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IIMAGESTREAM };

	/**
	 Read row(s) of data and return. If there is another segment in the 
	 ImageStream, ReadRows will cause a cascade of ReadRows calls

	 @param outRecord		Defines dimensions for image, as well as data buffer
	 @return kTrue if read is successful, else kFalse
	 */
	virtual bool16 ReadData (ImageStreamRecord &outRecord) = 0;	
};


#endif
