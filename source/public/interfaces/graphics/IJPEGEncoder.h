//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IJPEGEncoder.h $
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
//  Defines the JPEG coder interface.
//  
//========================================================================================

#pragma once
#ifndef __IJPEGEncoder__
#define __IJPEGEncoder__

#include "IPMUnknown.h"
#include "JPEGCodecID.h"
#include "IPMStream.h"

/** JPEG encoding schemes
*/
typedef enum _JPEGEncoding			// Match Photoshop defs: 0, 1, 2, 3
{									// last two options not implemented
	kJPEGBaseline,
	kJPEGSequential,
	kJPEGProgressive,
	kJPEGLossless,
	kJPEGHierarchical
} JPEGEncoding; 

/** JPEG compression quality settings.
	These now match Photoshop defs (was 0, 2, 4, 6 for low, med, high, max)
*/
typedef enum
{
	kPoorQuality		= -2,
	kFairQuality		= 0,
	kGoodQuality 		= 1,
	kVeryGoodQuality	= 3,
	kExcellentQuality 	= 6,
	kGreatQuality 		= 8
} JPEGQuality;

/** JPEG Scanning quality.  Not actually used by the encoder or decoder.
*/
typedef enum
{									// Match Photoshop defs
	kFairScan		= 1,
	kGoodScan		= 2,
	// kVeryGoodScan= 4,			// Yes, these are out of order
	kExcellentScan	= 3
} JPEGScanTabGroup;

/** JPEGWriteOptions is a structure which specifies output options as well as information
about the source image.
*/
class JPEGWriteOptions {
public:
	JPEGWriteOptions() :
		xResolution(0),
		yResolution(0),
		xSize(0),
		ySize(0),
		colorType(0), 
		imageResources(nil), 
		imageResourcesSize(0UL),
		jpegQuality(kFairQuality),
		encoding(kJPEGBaseline),
		customHuff(kFalse),
		scanTabGroup(kFairScan),
		iccProfileData(nil), 
		iccProfileDataLen(0UL)
	{}

	short			xResolution;	// These two parameters are ignored if the image is CMYK
	short			yResolution;	// and the resolution must then be stored in the image resources
	uint16			xSize;
	uint16			ySize;
	short			colorType;		// 1 = Gray, 3 = RGB, 4 = CMYK
	char*			imageResources;
	uint32			imageResourcesSize;
	JPEGQuality		jpegQuality;
	JPEGEncoding	encoding;		// sequential, progressive...
	bool16			customHuff;		// whether to use custom Huff tables		
	JPEGScanTabGroup scanTabGroup;	// what scan order to use for progressive encoding
	uint8*			iccProfileData;
	uint32			iccProfileDataLen;
} ;
						
/** Interface for encoding buffers of image data to JPEG
*/
class IJPEGEncoder : public IPMUnknown
{

public:
	/** Specify the destination stream and JPEG options.  This method must be
		called first.
		@param jpegWriteOptions - IN: JPEG options
		@param iPMStream - IN: destination stream
		@return kTrue if success, kFalse if failure.
	*/
	virtual bool16 Open ( const JPEGWriteOptions&	jpegWriteOptions, 						 
						 IPMStream*					iPMStream ) = 0; 
						
	/** Encode the provided buffer of data to JPEG using the output stream and JPEG options
		specified by the Open method.
		@param rowBuffer - IN: Source data
		@param numberOfRows - IN: Number of scanlines of image data in the rowbuffer
		@return kTrue if successful, kFalse if failure.
	*/
	virtual bool16 WriteRows (char* rowBuffer, uint32 numberOfRows) = 0;
	
	/** Upon completion, call Close to release the output stream.
		@return kTrue if successful, kFalse if failure.
	*/
	virtual bool16 Close () = 0;
};


#endif
