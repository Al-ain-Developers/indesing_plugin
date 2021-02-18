//========================================================================================
//   
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IObjectExportOptionsSuite.h $ 
//   
//  Owner: Mainak Ghosh 
//   
//  $Author: pmbuilder $ 
//   
//  $DateTime: 2020/11/06 13:08:29 $ 
//   
//  $Revision: #2 $ 
//   
//  $Change: 1088580 $ 
//   
//  ADOBE CONFIDENTIAL 
//   
//  Copyright 2010 Adobe Systems Incorporated. All rights reserved. 
//   
//  NOTICE:  Adobe permits you to use, modify, and distribute this
//  file in accordance with the terms of the Adobe license agreement
//  accompanying it. If you have received this file from a source
//  other than Adobe, then your use, modification, or distribution of
//  it requires the prior written permission of Adobe.
//   
//========================================================================================

#pragma once
#ifndef __IObjectExportOptionSuite__
#define __IObjectExportOptionSuite__

#include "GenericID.h"
#include "IObjectExportOptionsData.h"
#include "ISVGExportOptionsData.h"

/** IID_IOBJECTEXPORTOPTIONSUITE interface; this interface involves selections; There will be
    an implementation on the ASB which is referred to as the integrator, and different
    selection format such as Layout implement their own CSB; when client code ask for a method,
    it check current selection and let each selection CSB do their own work.
*/
class IObjectExportOptionsSuite : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_IOBJECTEXPORTOPTIONSSUITE};

	/**
		Checks whether we can apply export options to the selection.
		@return bool16: return kTrue if the selection is valid.
	*/
	virtual bool16 CanApplyObjectExportOptions(void) const = 0;

	/**
		Gets the export options for the selection.
		@param objExpOptsData OUT export options with the state information
	*/
	virtual void GetObjectExportOptions(IObjectExportOptionsData *objExpOptsData) const = 0;
    
    /**
     Checks whether we can apply svg export options to the selection.
     @return bool16: return kTrue if the selection is valid.
     */
    virtual bool16 CanApplySVGExportOptions(void) const = 0;
    
    /**
     Gets the svg export options for the selection.
     @param svgExpOptsData OUT export options with the state information
     */
    virtual void GetSVGExportOptions(ISVGExportOptionsData *svgExpOptsData) const = 0;


	/**
		Applies the alternate text source type export option to the selection.
		@param sourceType IN the alternate text source type
	*/
	virtual void ApplyAltTextSourceType(IObjectExportOptions::TextSourceType sourceType) = 0;

	/**
		Applies custom alternate text export option to the selection.
		@param customText IN the custom alternate text
	*/
	virtual void ApplyCustomAltText(const PMString& customText) = 0;

	/**
		Applies the alternate text metadata property export option to the selection.
		@param nsPrefix IN the xmp schema namespace prefix
		@param propertyPath IN the xmp property path
	*/
	virtual void ApplyAltTextMetadataProperty(const PMString& nsPrefix, const PMString& propertyPath) = 0;

	/**
		Applies the actual text source type export option to the selection.
		@param sourceType IN the actual text source type
	*/
	virtual void ApplyActualTextSourceType(IObjectExportOptions::TextSourceType sourceType) = 0;

	/**
		Applies custom actual text export option to the selection.
		@param customText IN the custom actual text
	*/
	virtual void ApplyCustomActualText(const PMString& customText) = 0;

	/**
		Applies the actual text metadata property export option to the selection.
		@param nsPrefix IN the xmp schema namespace prefix
		@param propertyPath IN the xmp property path
	*/
	virtual void ApplyActualTextMetadataProperty(const PMString& nsPrefix, const PMString& propertyPath) = 0;

	/**
		Applies the tag type export option to the selection.
		@param tagType IN the tag type
	*/
	virtual void ApplyTagType(IObjectExportOptions::TagType tagType) = 0;

	/**
		Applies the custom image conversion export option to the selection.
		@param custom IN whether to do custom conversion or not
	*/
	virtual void ApplyCustomImageConversion(bool16 custom) = 0;

	/**
		Applies the image type export option to the selection.
		@param type IN image conversion format
	*/
	virtual void ApplyImageType(IXMLExportOptions::ImageType type) = 0;


	/**
		Applies the image resolution export option to the selection.
		@param resolution IN the resolution value
	*/
	virtual void ApplyImageResolution(const PMReal &resolution) = 0;

	/**
		Applies the jpeg encoding export option to the selection.
		@param encoding IN JPEG encoding scheme to choose
	*/
	virtual void ApplyJPEGEncoding(IXMLExportOptions::JPEGEncoding encoding) = 0;

	/**
		Applies the jpeg quality export option to the selection.
		@param quality IN quality level to use for exported JPEG
	*/
	virtual void ApplyJPEGQuality(IXMLExportOptions::JPEGQuality quality) = 0;

	/**
		Applies the gif palette type export option to the selection.
		@param palette IN kind of GIF palette to create
	*/
	virtual void ApplyGIFPaletteType(IXMLExportOptions::PaletteType palette) = 0;

	/**
		Applies the gif interlaced export option to the selection.
		@param interlaced IN whether to create interlaced GIF
	*/
	virtual void ApplyGIFInterlaced(bool16 interlaced) = 0;

	/**
		Applies the custom layout export option to the selection.
		@param layout IN whether to use custom layout or not
	*/
	virtual void ApplyCustomLayout(bool16 layout) = 0;

	/**
		Applies the custom layout type export option to the selection.
		@param customLayoutType IN type of custom layout to be used
	*/
	virtual void ApplyCustomLayoutType(IObjectExportOptions::CustomLayoutType customLayoutType) = 0;

	/**
		Applies the image alignment export option to the selection.
		@param align IN the alignment type
	*/
	virtual void ApplyImageAlignment(IObjectExportOptions::ImageAlignment align) = 0;

	/**
		Applies image space before export option to the selection.
		@param before IN the image space before value
	*/
	virtual void ApplyImageSpaceBefore(const PMReal &before) = 0;

	/**
		Applies the image space after export option to the selection.
		@param after IN the image space after value
	*/
	virtual void ApplyImageSpaceAfter(const PMReal &after) = 0;

	/**
		Applies the use image page break export option to the selection.
		@param usePageBreak IN whether to page break on encountering image
	*/
	virtual void ApplyUseImagePageBreak(bool16 usePageBreak) = 0;

	/**
		Applies the image page break export option to the selection.
		@param pageBreak IN the page break to apply
	*/
	virtual void ApplyImagePageBreak(IObjectExportOptions::ImagePageBreak pageBreak) = 0;

	/**
		Gets the unique xml structure value of alt/actual text for the selection.
		@param alt IN boolean passed to indicate whether we want alt or actual text, kTrue: alt, kFalse: actual.
		@param structureText OUT the alt/actual text from the xml structure
		@return ErrorCode: error code
	*/
	virtual ErrorCode GetTextFromStructure(bool16 alt, PMString &structureText) const = 0;

	/**
		Gets the unique xmp metadata property value for the selection.
		@param nsPrefix IN the xmp schema namespace prefix
		@param propertyPath IN the xmp property path
		@param metadataText OUT the value of the xmp property
		@return ErrorCode: error code
	*/
	virtual ErrorCode GetTextFromMetadata(const PMString &nsPrefix, const PMString &propertyPath, PMString &metadataText) const = 0;

	/**
		Applies the use original image option to the selection.
		@param useOriginal IN whether to use original image or not
	*/
	virtual void ApplyUseOriginalImage(bool16 useOriginal) = 0;

	/**
		Applies the epub type to the selection.
		The list of valid epub types are in http://www.idpf.org/epub/vocab/structure/# .
		@param eType IN the epub type to set
	*/
	virtual void ApplyEpubType(const PMString &eType) = 0;

	/* OBSOLETE: Do not use. Use CustomSizeType based APIs instead. */
	/* Obsolete block starts */

		/**
		Applies custom width type export option to the selection.
		@param customWidthType IN the custom width type.
	*/
	virtual void ApplyCustomWidthType(IObjectExportOptions::CustomWidthType customWidthType) = 0;

	/**
		Applies custom height type export option to the selection.
		@param customHeightType IN the custom height type.
	*/
	virtual void ApplyCustomHeightType(IObjectExportOptions::CustomHeightType customHeightType) = 0;

	/**
		Applies custom width value to the selection.
		@param width IN the custom width.
	*/
	virtual void ApplyCustomWidth(const PMString &width) = 0; 

	/**
		Applies custom height value  to the selection.
		@param height IN the custom height.
	*/
	virtual void ApplyCustomHeight(const PMString &height) = 0; 
	/* Obsolete block ends */


	/**
		Applies custom Size type export option to the selection.
		@param customSizeType IN the custom Size type.
	*/
	virtual void ApplyCustomSizeType(IObjectExportOptions::CustomSizeType customSizeType) = 0;

	/**
		Applies custom size string to the selection.
		@param sizeString IN the custom string.
	*/
	virtual void ApplyCustomSize(const PMString &sizeString) = 0; 

	/**
		Applies the custom content rasterization option to the selection.
		@param custom IN whether to rasterize content or not
	*/
	virtual void ApplyCustomContentConversion(bool16 custom) = 0;
    
    /**
       Applies the SVG Export type i.e. embed code or object tags to the selection.
       @param type IN the SVG Export type.
     */
    virtual void ApplySVGExportType(ISVGAttributes::EPubExportSVGStrategy type) = 0;
    
    /**
       Sets the document preferences, type of SVG export, and whether the type needs to
       be applied to all current and incoming SVGs. Also, applies the export preference
       to all existing SVGs.
       @param value IN whether to apply the input SVG export type to all SVGs in document.
       @param type IN the SVG Export type.
     */
    virtual void ApplyOnAllSVGs(bool16 value, ISVGAttributes::EPubExportSVGStrategy type) = 0;
};

#endif
