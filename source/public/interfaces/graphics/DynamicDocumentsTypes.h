//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/DynamicDocumentsTypes.h $
//  
//  Owner: Greg St. Pierre
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

#include "IPMStream.h"

/**
 A collection of types used by Dynamic Documents (SWF and XFL) exports. 
 
 @see IXFLExportPreferences
 @see ISWFExportPreferences
 */
namespace flash_export
{
	/**
	 Format for rasters
	 */
	enum RasterFormat
	{
		kJPEGFormat,
		kGIFFormat,
		kPNGFormat,
		kAutomaticFormat
	};
	
	/**
	 Compression for rasters
	 */
	enum RasterCompression
	{
		kJPEGCompression,
		kLosslessCompression,
		kAutomaticCompression
	};
	
	/**
	 JPEG quality
	 */
	enum JPEGQuality
	{
		kJPEGQuality_Minimum,
		kJPEGQuality_Low,
		kJPEGQuality_Medium,
		kJPEGQuality_High,
		kJPEGQuality_Maximum
	};
	
	/**
	 Options for image raster image resampling
	 */
	enum ResamplingType
	{
		kNoResampling,
		kAverageResampling,
		kSubsampleResampling,
		kBicubicResampling
	};
	
	/**
	 Policies for text export
	 */
	enum TextExportPolicy 
	{
		kLiveText = 0,	// default
		kRasterizeText,
		kVectorizeText,
		kVellumText
	};
	
	/**
	 Transparency handling options
	 */
	enum TransparencyHandling
	{
		kIgnoreTransparency,
		kFlattenTransparency,
		kNativeTransparency
	};
	
	/**
	 Dynamic media handling options
	 */
	enum DynamicMediaHandling
	{
		kIncludeAll,
		kAppearanceOnly
	};
	
	/**
	 Size selection
	 */
	enum SizeSelection
	{
		kFitTo,
		kWidthAndHeight,
		kScale
	};
	
	/**
	 Fit To selection
	 */
	enum FitToSelection
	{
		k1280x800,
		k1240x620,
		k1024x768,
		k984x588,
		k800x600,
		k760x420,
		k640x480,
		k600x300
	};
	
	/**
	Curve Quality
	*/
	enum CurveQuality
	{
		kMinCurveQuality			= 1,
		kLowCurveQuality			= 3,
		kMedCurveQuality			= 5,
		kHighCurveQuality			= 7,
		kMaxCurveQuality			= 10
	};

	enum SWFScaleMode		// Indicates the current scaling of the SWF file within Flash Player.
	{
		kNoScale	= 0,	// makes the size of the Flash content fixed, so that it remains unchanged even as the size of the player window changes. Cropping may occur if the player window is smaller than the Flash content. 
		kExactFit	= 1,	// makes the entire Flash content visible in the specified area without trying to preserve the original aspect ratio. Distortion can occur. 
		kShowAll	= 2,	// (Default in Flash Player) makes the entire Flash content visible in the specified area without distortion while maintaining the original aspect ratio of the. Borders can appear on two sides of the application. 
		kNoBorder	= 3		// scales the Flash content to fill the specified area, without distortion but possibly with some cropping, while maintaining the original aspect ratio of the application. 
	};

	/**
	 Size and fit settings are used to control how SWF and XFL output are scaled during
	 an export.
	 
	 Note: InDesign does not support anisomorphic scaling. A single scaling factor will
	 be used during exports for both horizontal and vertical scaling. This will preserve
	 the source document's aspect ratio.
	 
	 The simplest setting is a constant scaling factor that is applied during the export.
	 For instance, to scale the contents of a document by 200% while exporting, use a
	 SizeSelection of kScale and a scale amount of 200. The FitToSelection, width, and 
	 height values are ignored in this case.
	 
	 To scale the contents of a document so that they will fit as tightly as possible within 
	 one of a set of predefined bounding rectangles, use a SizeSelection of kFitTo and a
	 FitToSelection indicating which bounding rectangle to use. The width, height and 
	 scaling amount values are ignored in this case.
	 
	 To scale the contents of a document so that they will fit as tightly as possible within
	 a specified bounding rectangle, use a SizeSelection of kWidthAndHeight and width and
	 height values corresponding to the dimensions you need. The FitToSelection and scale
	 values are ignored in this case.
	 
	 Note that when kFitTo or kWidthAndHeight are chosen, the actual scaling factor may vary
	 depending on the size of the source document. Likewise, the actual output dimensions
	 may vary as InDesign calculates these based on the scaling factor.
	 */
	class SizeAndFitSettings
	{		
	public:
		typedef object_type data_type;

		/**
		 One of SizeSelection enum indicating which sizing and fitting mode is used
		 */
		SizeSelection fSizeSelection;
		
		/**
		 One of FitToSelection enum indicating which predefined bounding box to fit to. 
		 Ignored if fSizeSelection is not kFitTo.
		 */
		FitToSelection fFitToSelection;
		
		/**
		 Width to use in fitting and scaling if fSizeSelection is kWidthAndHeight.
		 Ignored otherwise.
		 */
		uint32 fWidthAmount;
		
		/**
		 Height to use in fitting and scaling if fSizeSelection is kWidthAndHeight.
		 Ignored otherwise.
		 */
		uint32 fHeightAmount;
		
		/**
		 Constant scaling amount used if fSizeSelection is kScale.
		 Ignored otherwise.
		 */
		PMReal fScaleAmount;

		/** Default constructor.
		*/
		SizeAndFitSettings() :
			fSizeSelection(kScale),
			fFitToSelection(k1024x768),
			fWidthAmount(1024),
			fHeightAmount(768),
			fScaleAmount(100.0)
		{
		}

		/**
		 SizeAndFitSettings constructor. May be used to used to initialize an instance
		 of the class with given values.
		 
		 @param sizeSelection	One of SizeSelection enum indicating which sizing and fitting mode is used
		 @param fitToSelection	One of FitToSelection enum indicating which predefined bounding box to fit to. Ignored if sizeSelection is not kFitTo.
		 @param widthAmount		Width to use in fitting and scaling if sizeSelection is kWidthAndHeight. Ignored otherwise.
		 @param heightAmount	Height to use in fitting and scaling if sizeSelection is kWidthAndHeight. Ignored otherwise.
		 @param scaleAmount		Constant scaling amount used if sizeSelection is kScale. Ignored otherwise.
		 */
		SizeAndFitSettings(SizeSelection const &sizeSelection, 
						   FitToSelection const &fitToSelection,
						   uint32 const &widthAmount,
						   uint32 const &heightAmount,
						   PMReal const &scaleAmount) :
			fSizeSelection(sizeSelection),
			fFitToSelection(fitToSelection),
			fWidthAmount(widthAmount),
			fHeightAmount(heightAmount),
			fScaleAmount(scaleAmount)
		{
		}

		/** Equal operator for comparison.
	    @param other IN the object to compare with.
		@return bool16 kTrue means equal, otherwise kFalse.
		*/
		bool16 operator==(const SizeAndFitSettings& other) const
		{
			return ( (fSizeSelection == other.fSizeSelection) &&
					 (fFitToSelection == other.fFitToSelection) &&
					 (fWidthAmount == other.fWidthAmount) &&
					 (fHeightAmount == other.fHeightAmount) && 
					 (fScaleAmount == other.fScaleAmount) );
		}

		/** Not equal operator for comparison.
	    @param other IN the object to compare with.
		@return bool16 kTrue means NOT equal, otherwise kFalse.
		*/
		bool16 operator!=(const SizeAndFitSettings& other) const
		{
			return ( (fSizeSelection != other.fSizeSelection) ||
					 (fFitToSelection != other.fFitToSelection) ||
					 (fWidthAmount != other.fWidthAmount) ||
					 (fHeightAmount != other.fHeightAmount) || 
					 (fScaleAmount != other.fScaleAmount) );
		}

		/** Persist SizeAndFitSettings
	    @param s IN stream where we read/write object of SizeAndFitSettings.
		*/
		void ReadWrite(IPMStream *s)
		{
			XFER_ENUM(s, fSizeSelection);
			XFER_ENUM(s, fFitToSelection);
			s->XferInt32((int32&)fWidthAmount);
			s->XferInt32((int32&)fHeightAmount);
			s->XferRealNumber(fScaleAmount);
		}
	};
}
