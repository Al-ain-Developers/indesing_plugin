//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IJPEGDecoder.h $
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
//  Defines the JPEG decoder interface.
//  
//========================================================================================

#pragma once
#ifndef __IJPEGDecoder__
#define __IJPEGDecoder__

#include "IPMUnknown.h"
#include "JPEGCodecID.h"
#include "IPMStream.h"

/** structure for holding information about the source image
*/
class JPEGReadInfo
{
public:
	JPEGReadInfo()
	:	xSize(0), ySize(0),
		colorType(0),
		encoding(0),
		resolution(0),
		exifResolution(0),
		iccProfile(nil),
		iccProfileSize(0UL),
		imageResources(nil),
		imageResourcesSize(0),
		xmpData(nil),
		xmpDataSize(0UL),
		orientation(0)
	{}
	
	unsigned short	xSize;
	unsigned short	ySize;
	short	colorType;  		// 1 = Gray, 3 = RGB, 4 = CMYK, 5 = YCC (pass as input to indicate that no color conversion should occur)
	short	encoding;			// 0 = baseline, 1 = sequential, 2 = progressive, 3 = lossless, 4 = hierachical.
	Fixed	resolution;
	Fixed	exifResolution;
	char*	imageResources;		// Owned by the JPEG decoder. Don't delete or rely on
	uint32	imageResourcesSize; // in bytes
	uint8*	iccProfile;
	uint32	iccProfileSize;		// in bytes
	char*	xmpData;
	uint32	xmpDataSize;		// in bytes
	int16	orientation;		// See TIFF spec for documentation on tag #274 (Orientation). Zero indicates unset.
};

/** Interface for decoding JPEG compressed data
*/
class IJPEGDecoder : public IPMUnknown
{

public:

	/** Specify the input stream and read the JPEG tags.
		@param jpegReadInfo - OUT: Pointer to a valid jpegReadInfo structure which client should memset to zeroes.
			Decoder will fill in the structure based on the JPEG tags.
		@param iPMStream - IN: input stream.
		@return kTrue if the decoder can decode the stream.
	*/
	virtual bool16 Open ( JPEGReadInfo*	jpegReadInfo,
						 IPMStream*		iPMStream) = 0; 
						
	/** Read numberOfRows of image data into rowBuffer. If rowBuffer is nil,
		then skip numberOfRows.
		@param rowBuffer - OUT: destination buffer or nill to skip 'numberOfRows' rows.
		@param numberOfRows - IN: how many rows of data to read.
		@return kTrue if successful.
	*/
	virtual bool16 ReadRows (char* rowBuffer, uint32 numberOfRows) = 0;
	
	/** Close the stream and cleanup
		@return kTrue if successful.
	*/
	virtual bool16 Close () = 0;
};


#endif
