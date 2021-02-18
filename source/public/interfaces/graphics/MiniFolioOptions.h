//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/MiniFolioOptions.h $
//  
//  Owner: Adobe Systems Inc.
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

#include "IJPEGEncoder.h"		// For JPEG quality enum
#include <adobe/vector.hpp>

/**
 Options for creating a mini-folio from a pair of InDesign documents
 
 NOTE: This structure, and the IDigitalPublishingFacade functions that
 reference it, is now deprecated. Do not make any changes to this!
 */
struct MiniFolioOptions
{
	/**
	 Specifies the wide dimension for the folio's assets
	 */
	uint32 fWideDimension;
	
	/**
	 Specifies the narrow dimension for the folio's assets
	 */
	uint32 fNarrowDimension;
	
	/**
	 Formats for the assets in the folio
	 */
	enum AssetFormat
	{
		kPNGFormat,
		kJPEGFormat,
		kAutoRasterFormat,			// uses various heuristics to select between PNG and JPEG formats
		kPDFFormat,
		kPGTFormat,

		kInvalidAssetFormat = 0xffffffff
	};
	
	/**
	 Specifies the format for the assets in the folio
	 */
	AssetFormat fFormat;
	
	/**
	 Specifies the quality to be used for JPEG assets
	 */
	JPEGQuality fJPEGQuality;

	/**
	 Specifies a file, assumed to be in PNG, JPEG or GIF format, to be used as the 
	 table of contents image for the mini-folio.
	 */
	IDFile fTOCImageFile;

	/**
	 Specifies a directory to look for FPO asset sub-directories in.
	 */
	IDFile fFPOAssetDirectory;
	
	/**
	 Smooth scrolling behavior
	 */
	enum SmoothScrollingBehavior
	{
		kNoSmoothScrolling,
		kVerticalSmoothScrolling,
		kHorizontalSmoothScrolling,
		kVerticalAndHorizontalSmoothScrolling,
		
		kInvalidSmoothScrolling = 0xffffffff
	};
	
	SmoothScrollingBehavior fSmoothScrollingBehavior;

	WideString fContentStackID;

	bool fIsFlattened;

	bool fAlwaysDisplayOverlays;

	/**
	 Spreads to export or to get overlays
	 If empty, all pages are included.
	 */
	adobe::vector<uint32> fSpreadList;


	/**
	 A directory for generated assets. 
	 If not specified, a temporary directory is used.
	*/
	IDFile fLocationForGeneratedAssets;

	MiniFolioOptions() :
		fWideDimension(1024),
		fNarrowDimension(768),
		fFormat(MiniFolioOptions::kAutoRasterFormat),
		fJPEGQuality(kExcellentQuality),
		fSmoothScrollingBehavior(MiniFolioOptions::kNoSmoothScrolling),
		fIsFlattened(false),
		fAlwaysDisplayOverlays(false)
	{
	}
};