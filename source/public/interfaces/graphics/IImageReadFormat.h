//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IImageReadFormat.h $
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
#ifndef __IImageReadFormat__
#define __IImageReadFormat__

#include "IPMUnknown.h"
#include "IImageStream.h"

class IGraphicLayerInfo;
class IImageAttributes;
class IPMStream;

/**
 Interface defining the mechanism for reading an image from a stream.
 
 Image format reading sequence:

 First, the app calls CanRead with the data stream. If the filter returns 
 kTrue, the app calls Open with the data stream. The app then may or may not 
 call SetFormatOption and GetImageAttributes. In general the app will only 
 query for that information once and then cache it for later use. The app then
 calls GetImageAttributes, which returns the attributes of the currently 
 selected image within the file (high res or low res in this revision). At this
 point, the app calls ReadData repeatedly, possibly in random order. The data 
 returned should come from the currently set image, layer, and plane as 
 specified via SetFormatOption. Note that calls to SetFormatOption and 
 GetImageAttributes can happen any time and multiple times between Open and 
 Close. Finally, the app calls close and terminates the connection.
 
 @see IImageWriteFormat
 */
class IImageReadFormat : public IPMUnknown
{
public:
	// format options for SetFormatOption
	enum {
		kOptionSetImage = 1,
		kOptionSetLayer = 2
	};

	// format data options for SetFormatOption
	enum {
		kOptionUseFullRes = kMaxInt32,
		kOptionUseSmallestRes = 0
	};

	/**
	 Open is the initial call made to the image format reader (after the 
	 optional CanRead call, however). The image format reader should do any 
	 initialization and check the stream to make sure it really understands 
	 the data.
	 
	 @param iPMStream		IN The stream to read
	 @return kTrue if the reader can process the data in the given stream, else kFalse
	 */
	virtual bool16 Open(IPMStream* iPMStream) = 0;
	
	/**
	 Retrieves the image attributes for the current image (there may be only
	 one; see note below about multiple images).
	 
	 GetImageAttributes will return kFalse if Open has not been called.
	 
	 GetAttributes is a separate method so that IImageReadFormat users can 
	 cache the information.  
	 
	 IMPORTANT: If the format supports more than one image per file and there 
	 is another image, then the attributes returned are those for the currently
	 set image (via the SetFormatOption call).
	 
	 @param iImageAttributes	OUT The IImageAttributes object to which the attributes are written
	 @return kTrue if the method succeeds, else kFalse
	 @see IImageAttributes
	 */
	virtual bool16 GetImageAttributes(IImageAttributes* iImageAttributes) = 0;
	
	/**
	 Retrieves the graphic layer information for the current image.
	 
	 GetGraphicLayerInfo will return kFalse if Open has not been called.
	 
	 Note: May return kTrue even if layers do not exist.
	 
	 @param iLayerInfo			OUT The IGraphicLayerInfo object to which the layer information is written
	 @return kTrue if the method succeeds, else kFalse
	 @see IGraphicLayerInfo
	 */
	virtual bool16 GetGraphicLayerInfo(IGraphicLayerInfo* iLayerInfo) = 0;
	
	/**
	 Closes this reader.
	 
	 @return kTrue if the method succeeds, else kFalse
	 */
	virtual bool16 Close() = 0;
	
	/**
	 Called to determine if this reader can process the data in the given 
	 stream.
	 
	 This can be the first call to the image format reader. It does not take 
	 place after the Open call. CanRead is the filter's oppurtunity to 
	 determine if it in fact can read the stream of data.
	 
	 @param iPMStream			IN The stream of data
	 @return kTrue if the reader can process the data in the stream, else kFalse
	 @see IPMStream
	 */
	virtual bool16 CanRead(IPMStream* iPMStream) = 0;
	
	/**
	 Sets an additional format option. It allows the caller to request a 
	 particular resolution of image or a specific layer in a multi-layer image,
	 if the IImageReadFormat instance supports the options. Returns kTrue if 
	 the reader supports the option and the image contains sufficient data to
	 satisify the request, otherwise kFalse. 
	  
	 Inputs are as follows:

		formatOption = kOptionSetImage, formatData = kOptionUseFullRes. The 
		resolution of the main image will be returned in formatData.
		
		formatOption = kOptionSetImage, formatData = kOptionUseSmallestRes. 
		If there are multiple images then the resolution of the smallest 
		subsampled version of the main image will be returned in formatData.
			
		formatOption = kOptionSetImage, formatData = desired resolution. If 
		there are multiple images then the closest resolution which is greater 
		than or equal to the desired resolution will be returned in
		formatData.

		formatOption = kOptionSetLayer, formatData = zero based index of desired layer.
		Sets the index of the layer to use. No return value will be placed 
		in formatData.
			
	 Note: This call must be made after the call to Open().
	 
	 @param formatOption	IN The selector for the format to use
	 @param formatData		IN/OUT The data to use with the specified selector on input; various on output
	 @return kTrue if the method succeeds, else kFalse
	 */
	virtual bool16 SetFormatOption (uint32 formatOption, uint32& formatData) = 0;

	/**
	 Reads data from the image. The data copied into outRecord.buffer is 
	 expected to be in the format described by the image attributes. 
	 
	 Note: For 1-bit data each row is bit-padded to a byte boundary.
	 
	 @param outRecord		IN/OUT Describes the data to be read and holds pointer to the caller-provided buffer to which data is copied
	 @see IImageStream
	 */
	virtual bool16 ReadData(ImageStreamRecord& outRecord) = 0;
	
	
};

#endif
