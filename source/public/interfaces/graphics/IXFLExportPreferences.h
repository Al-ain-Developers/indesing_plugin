//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IXFLExportPreferences.h $
//  
//  Owner: Greg St. Pierre
//  
//  $Author: vans $
//  
//  $DateTime: 2020/11/06 05:06:09 $
//  
//  $Revision: #1 $
//  
//  $Change: 1088554 $
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

#include "DynamicDocumentsID.h"
#include "DynamicDocumentsTypes.h"

/**
 Export preferences for XFL (Flash interchange) exports.
 
 IXFLExportPreferences is used to configure the parameters for an export to the
 XFL format supported by the Flash Authoring application.
 
 In order to export InDesign content to XFL, you will typically create an instance
 of the XFL export command (kXFLExportCommandBoss), set its item list to refer to 
 the pages to be exported, and set up the stream and UI flags to be used. You can
 then use the IXFLExportPreferences aggregated on the command boss to set up
 various parameters for the export, including how to treat raster images, text,
 etc.
 
 IXFLExportPreferences is also aggregated on the app workspace, where it is used
 to ensure that default export settings are preserved from export to export. You
 might consider using this instance as the base for your export settings. You 
 might also consider using kSetXFLSessionPrefsCmdBoss to update the default export
 settings for subsequent exports.
 */
class IXFLExportPreferences : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXFLEXPORTPREFERENCES };
		
	/**
	 Copies one set of prefs into another

	 @param other			IN The preferences to copy
	 */
	virtual void Copy(IXFLExportPreferences const *other) = 0;

	/**
	 Sets the preferred raster format to be used for the export. Note that some formats
	 will be required in certain scenarios and that those will take precedence over the
	 setting specified here. This will be used when no particular format is required.
	 
	 @param format		One of the RasterFormat enum specifying the preferred raster format
	 */
	virtual void SetRasterFormat(flash_export::RasterFormat format) = 0;
	
	/**
	 Gets the preferred raster format to be used for the export.
	 
	 @return One of the RasterFormat enum specifying the preferred raster format
	 */
	virtual flash_export::RasterFormat GetRasterFormat() const = 0;
	
	/**
	 Sets the quality to be used for JPEG compressed images during the export.
	 
	 @param quality		One of the JPEGQuality enum
	 */
	virtual void SetJPEGQuality(flash_export::JPEGQuality quality) = 0;
	
	/**
	 Gets the quality to be used for JPEG compressed images during the export.
	 
	 @return One of the JPEGQuality enum
	 */
	virtual flash_export::JPEGQuality GetJPEGQuality() const = 0;
	
	/**
	 Sets the preferred raster resolution for the export. This controls two related
	 items: the resolution at which content will be rasterized and the resolution to
	 which raster images will be resampled when resampling is enabled.
	 
	 @param ppi			The preferred resolution, in ppi, for raster images
	 */
	virtual void SetRasterResolution(uint32 ppi) = 0;
	
	/**
	 Gets the preferred raster resolution for the export.
	 
	 @return The preferred resolution, in ppi, for raster images.
	 */
	virtual uint32 GetRasterResolution() const = 0;
	
	/**
	 Sets the algorithm to be used for resampling raster images that exceed the 
	 specified resolution threshold. Setting to kNoResampling disables resampling.
	 
	 @type		One of the ResamplingType enum specifying the resampling algorithm to use.
	 */
	virtual void SetResamplingType(flash_export::ResamplingType type) = 0;
	
	/**
	 Gets the algorithm to be used for resampling raster images.
	 
	 @return One of the ResamplingType enum specifying the resampling algorithm to use.
	 */
	virtual flash_export::ResamplingType GetResamplingType() const = 0;

	/**
	 Sets the raster resolution threshold. Raster images whose rendered resolutions 
	 exceed this value will be resampled using the resampling algorithm specified by
	 SetResamplingType.
	 
	 @param ppi		The resolution threshold, in ppi
	 */
	virtual void SetResampleThresholdResolution(uint32 ppi) = 0;
	
	/**
	 Gets the raster resolution threshold.
	 
	 @return The raster resolution threshold, in ppi
	 */
	virtual uint32 GetResampleThresholdResolution() const = 0;
	
	/**
	 Sets whether to export as reader's spreads.
	 
	 @param spreads		Boolean. If kTrue, export as reader's spread; if kFalse, export as pages
	 */
	virtual void SetReadersSpreads(bool16 spreads) = 0;
	
	/**
	 Gets whether to export as reader's spreads.
	 
	 @return kTrue if exporting as reader's spreads; otherwise kFalse
	 */
	virtual bool16 GetReadersSpreads() const = 0;
	
	/**
	 Sets whether to rasterize each page/spread
	 
	 @param rasterize	Boolean. If kTrue, pages/spreads are rasterized
	 */
	virtual void SetRasterizePages(bool16 rasterize) = 0;
	
	/**
	 Gets whether to rasterize each page/spread
	 
	 @return kTrue if pages/spreads are to be rasterized
	 */
	virtual bool16 GetRasterizePages() const = 0;

	/**
	 Sets the preferred method for handling dynamic media page items.
	 
	 @param the method to be used for dynamic media page items
	 */
	virtual void SetDynamicMediaHandling(flash_export::DynamicMediaHandling dmh) = 0;
	
	/**
	 Gets the preferred method for handling dynamic media page items.
	 
	 @return The method to be used dynamic media page items
	 */
	virtual flash_export::DynamicMediaHandling GetDynamicMediaHandling() const = 0;

	/**
	 Sets the text export policy for all text frame dictating how text is to be represented in the exported file.
	 
	 @param policy	One of the TextExportPolicy enum
	 */
	virtual void SetTextExportPolicy(flash_export::TextExportPolicy policy) = 0;
	
	/**
	 Gets the text export policy for all text frame dictating how text is to be represented in the exported file.
	 
	 @return One of the TextExportPolicy
	 */
	virtual flash_export::TextExportPolicy GetTextExportPolicy() const = 0;
	
	/**
	 Sets whether to insert discretionary hyphenation points for TLF text. Only relevant when
	 Flash TLF Text is the text export policy.
	 
	 @param insertHyphens	Boolean. If kTrue, discretionary hyphenation points are included
	 */
	virtual void SetInsertHyphensForTLF(bool16 insertHyphens) = 0;
	
	/**
	 Gets whether to insert discretionary hyphenation points for TLF text. Only relevant when
	 Flash TLF Text is the text export policy.
	 
	 @return kTrue if discretionary hyphenation points are included
	 */
	virtual bool16 GetInsertHyphensForTLF() const = 0;
	
	/**
	 Sets the preferred method for handling transparency on a page or spread, if it exists.
	 
	 @param th		The method to be used for pages or spreads with transparency
	 */
	virtual void SetTransparencyHandling(flash_export::TransparencyHandling th) = 0;
	
	/**
	 Gets the preferred method for handling transparency on a page or spread, if it exists.
	 
	 @return The method to be used for pages or spread with transparency
	 */
	virtual flash_export::TransparencyHandling GetTransparencyHandling() const = 0;
	
	/**
	 Sets the UID for the flattener style to be used when exporting pages or spreads
	 with transparency and SetTransparencyHandling is set to kFlattenTransparency.
	 
	 @param style	The UID of the flattener style to be used
	 */
	virtual void SetFlattenerStyle(UID const &style) = 0;
	
	/**
	 Gets the UID for the flattener style to be used when exporting pages or spreads
	 with transparency and SetTransparencyHandling is set to kFlattenTransparency.
	 
	 @return The UID of the flattener style to be used
	 */
	virtual UID GetFlattenerStyle() const = 0;

	/**
	 Sets the scale and fit settings to be applied for the export.
	 	 
	 @param settings		A SizeAndFitSettings structure to be filled with current settings
	 */
	virtual void SetSizeAndFitSettings(flash_export::SizeAndFitSettings const &settings) = 0;
	
	/**
	 Gets the scale and fit settings for the exported file.
	 	 
	 @param settings		A SizeAndFitSettings structure to be filled with current settings
	 */
	virtual void GetSizeAndFitSettings(flash_export::SizeAndFitSettings &settings) const = 0;
};
