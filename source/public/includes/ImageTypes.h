//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/ImageTypes.h $
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
#ifndef __ImageTypes__
#define __ImageTypes__

#include "PMTypes.h"


// We need to guarantee all structures here are packed the same.
// For Win32 we will force it to 1-byte alignment.
#ifdef WIN32
#pragma pack(push, 1)
#endif

/**  Image color space definitions
	@see IImageAttributes::kPMTagColorSpace
*/
enum
{
	kPMGrayColorSpace			= 0x00000001,		// 0 black, 1 white. Primary channels = 1
	kPMRGBColorSpace			= 0x00000002,		// Primary channels = 3
	kPMCMYKColorSpace			= 0x00000004,		// Primary channels = 4
	kPMICCLabColorSpace			= 0x00000008,		// maps a and b from -128/127 to 0/255. Primary channels = 3
	//kPMDuotoneColorSpace		= 0x00000010,		// Primary channels = ?
	kPM1InkColorSpace			= 0x00000020,		// Unknown color space consisting of 1 ink
	kPM2InkColorSpace			= 0x00000040,		// Unknown color space consisting of 2 inks
	kPM3InkColorSpace			= 0x00000080,		// Unknown color space consisting of 3 inks
	kPM4InkColorSpace			= 0x00000100,		// Unknown color space consisting of 4 inks
	kPM5InkColorSpace			= 0x00000200,		// Unknown color space consisting of 5 inks
	kPM6InkColorSpace			= 0x00000400,		// Unknown color space consisting of 6 inks
	kPM7InkColorSpace			= 0x00000800,		// Unknown color space consisting of 7 inks
	kPM8InkColorSpace			= 0x00001000		// Unknown color space consisting of 8 inks
};

const uint32 kPMNumberOfColorSpaces = 13;

// Maximum number of channels we support is 8;
const uint32 kPMMaxChannels = 8;

/** planarconfiguration values
	@see IImageAttributes::kPMTagPlanarConfig
*/
enum
{
	kPMChunky	= 1,
	kPMPlanar	= 2
};

/** Alpha types enumeration.  
	@see IImageAttributes::kPMTagChannelTypeArray
*/
enum
{
	kPMAlphaAssociated				= 1,	// alpha is pre-multiplied into the color values and is used as a transparency mask
	kPMAlphaUnassociated			= 2,	// alpha is not pre-multiplied and is not used as transparency
	kPMSpotChannel					= 3,	// spot channel
	kPMAlphaUnassociatedBackground	= 4		// alpha is unassociated, yet used as transparency mask
};

/** Alpha packing order enumeration.  
	@see IImageAttributes::kPMTagAlphaPacking
*/enum
{
	kPMAlphaPackingPreOrder		= 1,	// e.g., ACMYK, ARGB, etc.  May not be supported by write filters.
	kPMAlphaPackingPostOrder	= 2		// e.g., CMYKA, RGBA, etc.  Preferred packing.
};

// kPMFormatOptionSetImage
//
enum
{
	kPMLowResImage		= 1,	// NOTE:  A High res image can exist without a
	kPMHighResImage		= 2		// low res image but not vice versa.  
};


// The application type code
#define kPSApplicationCode	'8BIM'


// We need to guarantee all structures here are packed the same.
// For Win32 we will force it to 1-byte alignment.
#ifdef WIN32
#pragma pack(pop)
#endif

#endif
