//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IMungeSamplesImageStreamData.h $
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
//  Data interface for the IMungeSamplesImageStream segment of the IImageStreamManager.
//  This segment is used to strip extra channels from image data.
//  
//========================================================================================

#pragma once
#ifndef __IMungeSamplesImageStreamData__
#define __IMungeSamplesImageStreamData__

#include "IPMUnknown.h"

/** IMungeSamplesImageStreamData
	This class is a data interface for the MungeSamplesImageStream, which is an implementation of IImageStream used
	by the ImageStreamManager to strip color/alpha channels from an image at read time.  Various IImageStreams are
	pipelined together by the ImageStreamManager in order to convert a source image to a destination image
	with a given set of attributes.  This interface should probably be private.
	@see IImageStreamManager.h
*/
class IMungeSamplesImageStreamData : public IPMUnknown
{
public:
	/** MungeSamplesInfo structure
		width			number of pixels
		numChannels		number of channels to skip
		extraChannels	number of channels to strip
		alphaIndex		if >= 0 and alphaType is kPMAlphaAssociated, zero-based index of extra channel
						to use as the alpha.  If alphaType is kPMAlphaUnassociated, zero-based index
						of extra channel to keep.
		colorSpace		kPMGrayColorSpace, kPMRGBColorSpace, kPMCMYKColorSpace, kPMICCLabColorSpace
		alphaType		type of data in the extra channels - either kPMAlphaAssociated or kPMAlphaUnassociated.
						kPMAlphaAssociated will leave the color channels unchanged.
						kPMAlphaUnassociated will multiply the color channels by the white alpha
	*/
	typedef struct 
	{
		uint32	width;				// number of pixels
		uint16	numChannels;		// number of channels to skip
		uint16	extraChannels;		// number of channels to strip
		int16	alphaIndex;			// if >= 0 and alphaType is kPMAlphaAssociated, zero-based index of extra channel
									// to use as the alpha.  If alphaType is kPMAlphaUnassociated, zero-based index
									// of extra channel to keep.
		uint32	colorSpace;			// kPMGrayColorSpace, kPMRGBColorSpace, kPMCMYKColorSpace, kPMICCLabColorSpace
		uint32	alphaType;			// type of data in the extra channels - either kPMAlphaAssociated or kPMAlphaUnassociated.
									// kPMAlphaAssociated will leave the color channels unchanged.
									// kPMAlphaUnassociated will multiply the color channels by the white alpha
		
	} MungeSamplesInfo;
	
	/**
		Set method for specifying which channels should be munged
		@param mungeSamplesInfo - IN: structure containing information about which channels to munge.
	*/
	virtual void SetMungeSamplesInfo (const MungeSamplesInfo& mungeSamplesInfo) = 0;
	
	/**
		Get method
		@param mungeSamplesInfo - Out: structure containing information about which channels to munge.
	*/
	virtual void GetMungeSamplesInfo (MungeSamplesInfo* mungeSamplesInfo) const = 0;
};

#endif
