//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IImageWriteFormat.h $
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
#ifndef __IImageWriteFormat__
#define __IImageWriteFormat__

#include "IPMUnknown.h"

class IImageAttributes;
class IImageStream;
class ProgressBarAccessor;

/**
 Interface defining the mechanism for writing an image to a stream.
 
 Image format writing sequence:
 
 First, a client should call Open to begin a write session. It should then 
 call SetFormatOption (if required), SetImageAttributes, and WriteData. This 
 sequence of calls to SetFormatOption, SetImageAttributes, and WriteData may 
 be called as necessary if multiple images per file are supported. Close should 
 then be called to terminate the write session.
 
 @see IImageReadFormat
 */
class IImageWriteFormat : public IPMUnknown
{
public:
	/**
	 Sets the image attributes to use when writing the image. Unlike reading,
	 image attributes are required before writing the image data.
	 
	 IMPORTANT: If the format supports more than one image per file, then the 
	 attributes set are those for the current image (via the SetFormatOption 
	 call). 
	 
	 @param iImageAttributes	IN The image attributes to use for the write
	 @return kTrue if the method succeeds, else kFalse
	 */
	virtual bool16 SetImageAttributes (IImageAttributes* iImageAttributes) = 0;
	
	/**
	 Initializes a writer for a write session to the specified stream.
	 
	 @param iPMStream			IN The stream to write to
	 @return kTrue if the method succeeds, else kFalse
	 */
	virtual bool16 Open(IPMStream* iPMStream) = 0;
	
	/**
	 Terminates a write session started by a prior call to Open.
	 
	 @return kTrue if the method succeeds, else kFalse
	 */
	virtual bool16 Close() = 0;
	
	enum
	{
		kOptionSetImage = 1
	};

	/**
	 Sets an additional option for the image write. Only option supported at
	 this point is whether to write high res (kPMHighResImage) or low res 
	 (kPMLowResImage) image.
	 
	 @param formatOption		IN The selector for the option to set
	 @param formatData			IN The data for the option
	 @return kTrue if the method succeeds, else kFalse
	 */
	virtual bool16 SetFormatOption (uint32 formatOption, uint32 formatData) = 0;

	/**
	 Reads source data from the given IImageStream and writes to the output 
	 stream.
	
	 Note: The format may read the data in any row, plane, or layer order. 
	 Also, Because the format is driving the interaction, it is responsible for 
	 posting the progress bar.
	 
	 @param iImageStream		IN The source input stream
	 @return kTrue if the method succeeds, else kFalse
	 */
	virtual bool16 WriteData (IImageStream* iImageStream) = 0;
};

#endif
