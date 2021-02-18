//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ISimpleImageStreamManager.h $
//  
//  Owner: Dave Stephens
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
//  A simple envelope/wrapper class around the IImageStreamManager designed to ease
//  the setup of the IImageStreamManager when all you want to do is get an IImageStream
//  hooked up to an image for the purpose of reading.
//  
//========================================================================================

#pragma once
#ifndef __ISimpleImageStreamManager__
#define __ISimpleImageStreamManager__

#include "IPMUnknown.h"

#include "IImageStream.h"

class IImageAttributes;
class IImageStreamManager;
class IImageStream;

/**
 This interface is a helper class for creating an ImageStreamManager to convert either
 the proxy image data or linked image data, associated with a placed image, to a new
 image described by a set of IImageAttributes.

 @see IImageStreamManager, IImageStream, IImageAttributes
 */

class ISimpleImageStreamManager : public IPMUnknown
{
public:
	
	/** Set the conversion options.
		@param imageRef - IN: UIDRef of the placed image whose image data we want to use as the source.
		@param bUseHighRes - IN: kTrue to use the high-res linked image data.  kFalse to use the low resolution
			proxy image.
		@param dstImageAttributes - IN/OUT: used to setup a pipeline of ImageStream segments
			to convert the source to a destination with the given attributes.
		@param antiAliasing - IN: If down sampling is required, then passing kTrue causes an averaging based
			strategy to be used. kFalse causes a simple sub-sampling strategy to be used.  Default is kFalse.
		@param doDiffusion - IN: Sets whether or not to do diffusion during chunky to indexed conversion.
			Default is not.
		@param grayThreshold - IN: If converting to 1-bit, use this value to determine if a pixel should be black or white.
			Default is 128
	*/
	virtual ErrorCode Set (const UIDRef& imageRef, bool16 bUseHighRes, IImageAttributes* dstImageAttributes,
			bool16 antiAliasing = kFalse, bool16 doDiffusion = kFalse, uint8 grayThreshold = 128) = 0;
		

	/** Obtain an IImageStream from which a ReadData() method can be called to retrieve data.
		NOTE: This call could return NULL if an IImageStream cannot be created to map between
		the source and destination attributes.
		NOTE: The dstImageAttributes provided to Set() could be changed by the call to Open()
		is some circumstances.  See the notes for QueryImageStream() in IImageStreamManager.h.
		@return Ptr to an IImageStream for retrieving the converted image data.
	*/
	virtual IImageStream* Open (void) = 0;	

	/** Call Close if the Open returns a valid IImageStream after you are done with the IImageStream.
		Calling Close() allows the IImageStream to be Released.
	*/
	virtual void Close (void) = 0;	

	/** The ISimpleImageStreamManager is a simple envelope class around the IImageStreamManager.
		If you want this class to do all the basic setup but then you want to tweak one or two things,
		you can simple ask it for its IImageStreamManager and make the changes directly.
		NOTE: Calls to the IImageStreamManager returned via QueryImageStreamManager() should be made
		after the call to Set() and BEFORE the call to Open().
		@return Ptr to the underlying IImageStreamManager.
	*/
	virtual IImageStreamManager* QueryImageStreamManager() = 0;

};

#endif
