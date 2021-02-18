//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IImageStreamManager.h $
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
#ifndef __IImageStreamManager__
#define __IImageStreamManager__

#include "IPMUnknown.h"
#include "BravoForwardDecl.h"
#include "IGraphicsPort.h"

#include "ImageID.h"

class IImageStream;
class IImageAttributes;
class ICMSProfile;
class IDocument;

/**
 An interface to create an image manipulation pipeline. The manager is given
 attributes describing the source and destination images (colorspaces, bit 
 depths, planar/chunky layout, dimensions, etc), and creates a chain of image
 streams. The image stream chain is an exemplar of the pipe and filter pattern.
 As an image data consumer reads from the tail of the chain, preceding segments
 of the pipeline perform transformations required to massage the source data
 into the required output format.

 Basic operation is: create an instance of the stream manager; set attributes
 describing the source and destinations formats, and set any desired options,
 profile information, etc.; then query for an image stream that will return 
 image data in the requested destination format.

 Most of the methods exposed by the interface set options and should be called
 before calling QueryImageStream to create the image stream. For instance, if 
 the user specifies kTrue for anti-aliasing, then the ImageStream manager will
 choose the anti-aliasing segment instead of the downsample segment when the 
 output image dimensions are smaller than the input dimensions.

 @see IImageStream, IImageAttributes, ICMSProfile
 */

class IImageStreamManager : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IIMAGESTREAMMANAGER };

	/**
	 Set attributes for source image. Tells manager how to construct the image 
	 stream

	 @param srcImageAttributes	The attributes describing the source image
	 */
	virtual void SetSourceAttributes(IImageAttributes* srcImageAttributes) = 0;

	/**
	 Set attributes for destination image. Tells manager how to construct the
	 image stream

	 @param dstImageAttributes	The attributes describing the source image
	 */
	virtual void SetDestinationAttributes(IImageAttributes* dstImageAttributes) = 0;

	/**
	 Sets the first image stream segment. This segment is closest to the source
	 data and serves as the glue tying the source image data to the rest of the
	 image manager pipeline.
	 
	 @param firstImageStreamSegment		The head of the image stream
	 */
	virtual void SetFirstImageStreamSegment(IImageStream* firstImageStreamSegment) = 0;
	
	/**
	 Resampling type. 
	 
	 Note: these all downsample; we don't support upsampling
	 */
	enum ResamplingType
	{
		kSubsample,				// Default (anti-aliasing off). Fast, lowest quality
		kDownsample,			// Averaging sample (anti-aliasing on). Slower, better quality
		kBicubicDownsample,		// Weighted average sample. Slowest, best quality
		kSubAverage				// Hybrid of kSubsample and kDownsample. Better quality than kSubsample but much faster than kDownsample
	};

	/**
	 If downsampling is required, then this determines whether we subsample, 
	 downsample (anti-alias), or downsample using a weighted average. 
	 
	 Default is subsampling.

	 @param resample	Resampling type
	 @see IImageStreamManager::ResamplingType
	 */
	virtual void SetResamplingType(ResamplingType resample) = 0;
	
	/**
	 Sets the cache buffer (default is no cache)

	 Cache must be large enough to hold the output image data

	 The image stream manager does _not_ take possession of the cache buffer.
	 It is the responsibility of the caller to delete the buffer

	 @param cacheptr	The cache buffer
	 */
	virtual void SetCache(uint8* cacheptr) = 0; 
	
	/**
	 Sets whether or not to do diffusion during chunky to indexed conversion.
	 Default is kFalse (no)

	 @param yesno		Boolean: kTrue = do diffusion, kFalse, no diffusion
	 */
	virtual void SetDoDiffusion(bool16 yesno) = 0;
	
	/**
	 If converting to 1-bit, use this value to determine if a pixel should be 
	 black or white. Default is 128.

	 @param threshold	Threshold for gray
	 */
	virtual void SetGrayThreshold(uint8 threshold) = 0;

	/**
	 Read a specific alpha channel and strip away all other channels including 
	 the color channels.
	
	 @param channelIndex	Zero based index, where zero refers to the first 
		extra channel after the color channels
	 */
	virtual void SetReadAlphaChannelOnly(uint16 channelIndex) = 0;

	/**
	 When printing separations, the client may be requesting individual planes 
	 of data which are represented in gray space.  The client can request that 
	 the data is presented such that white is zero which may have the effect of 
	 inverting the color channel. 
	 
	 If this method is NOT called, then the ImageStreamManager will not touch 
	 the planar data. 
	 
	 If this method IS called and the kPMTagPlanarConfig is kPMPlanar, then the 
	 ImageStreamManager will look at the destination color space to determine 
	 whether or not each channel of data needs to be inverted. 
	 
	 Calling this method does not change the destination IImageAttributes as it 
	 is intended to only be used when printing separations.

	 @param yesno	Boolean: kTrue = set white is zero. Default = kFalse
	 */
	virtual void SetWhiteIsZeroForPlanarChannels(bool16 yesno) = 0;

	/**
	 Sets source color profile
	 
	 It is assumed that either the item contains a profile (i.e. an image with 
	 an embedded profile) or if not then its owning document should be used as 
	 the container of the profile

	 If profile information is not provided, then color conversion will be 
	 uncalibrated.

	 @param ownerItem	Profile owner
	 */
	virtual void SetSourceProfile(IPMUnknown *ownerItem) = 0;

	/**
	 Sets source color profile

	 @param srcProfile	The profile, specified as an ICMSProfile
	 */
	virtual void SetSourceProfile(ICMSProfile *srcProfile) = 0;

	/**
	 Sets source color profile

	 @param srcAGMColorSpace	Colorspace, assumed to be profile based
	 */
	virtual void SetSourceAGMColorSpace(AGMColorSpace *srcAGMColorSpace) = 0;

	/**
	 Sets destination color profile. 
	 
	 It is assumed that either the item contains a profile (i.e. an image with 
	 an embedded profile) or if not then its owning document should be used as 
	 the container of the profile

	 If profile information is not provided, then color conversion will be 
	 uncalibrated.

	 @param ownerItem	Profile owner
	 */
	virtual void SetDestinationProfile(IPMUnknown *ownerItem) = 0;

	/**
	 Sets destination color profile

	 @param dstProfile	The profile, specified as an ICMSProfile
	 */
	virtual void SetDestinationProfile(ICMSProfile *dstProfile) = 0;

	/**
	 Sets destination color profile

	 @param dstAGMColorSpace	Colorspace, assumed to be profile based
	 */
	virtual void SetDestinationAGMColorSpace(AGMColorSpace *dstAGMColorSpace) = 0;

	/**
	 Returns number of tasks that will take place during the creation of the
	 image stream. This should be called after attributes and other stream 
	 creation options have been set and before calling QueryImageStream.

	 Intended to be used in initializing a progress bar

	 @return number of tasks to be performed during creation of image stream
	 */
	virtual uint32 GetNumberOfTasks() = 0;
	
	/**
	 Creates an IImageStream based on specified attributes and options

	 The image stream is cached, so that subsequent calls without additional
	 changes to the attributes and/or options will return the cached stream.

	 Note: The colormap in the destination image attributes may be modified
	 during the creation of the image stream. As a result, you should access
	 the colormap after you have queried for the image stream

	 @return AddRef'd IImageStream
	 */
	virtual IImageStream *QueryImageStream() = 0;

	/**
	 Instructs image stream manager to create a stream that reads only a single
	 specific channel and to strip away data for all other channels. Similar to
	 SetReadAlphaChannelOnly, but is not limited to alpha channels. Also, index
	 is absolute and is _not_ relative to color channels.
	
	 @param channelIndex	Zero based index of channel to read
	 */
	virtual void SetReadSingleChannelOnly(uint16 channelIndex) = 0;

	/**
	 Provides color conversion options for cases where color conversions are
	 requested.
	
	 @param defRGBProfile	The default rgb profile to use for uncalibrated rgb.
	 @param defCMYKProfile	The default cmyk profile to use for uncalibrated rgb.
	 @param idealizedBlack	If true, uses idealized black conversions from CMYK to RGB/Gray.
							If false, uses accurate black conversions.
	 @param oppBlending		If true, uses XYZ-based blending for NChannel->process conversion.
							If false, blends in destination space.
	 @param fastXforms		If true, uses faster but less accurate xforms.
							If false, uses slower but more accurate xforms.
	 */
	virtual void SetColorConvertOptions
		(
			AGMColorProfile* defRGBProfile, 
			AGMColorProfile* defCMYKProfile, 
			bool32 idealizedBlack,
			bool32 oppBlending,
			bool32 fastXforms,
			IGraphicsPort::RenderingIntent defaultRI
		) = 0;

	/**
	 Internal-only direct setting of all color convert options.
	
	 @param opts	A pointer to the options dictionary container.
	 */
	virtual void SetColorConvertOptions(void* opts, IGraphicsPort::RenderingIntent defaultRI) = 0;
};

#endif
