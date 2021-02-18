//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IObjectExportOptions.h $
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
#ifndef __IObjectExportOptions__
#define __IObjectExportOptions__

#include "GenericID.h"
#include "IXMLExportOptions.h"

/**
	Interface for export options associated with an object.
*/
class IObjectExportOptions : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_IOBJECTEXPORTOPTIONS};

	typedef enum
	{
		/** User entered alt/actual text. */
		kCustom = 0,

		/** Alt/actual text obtained from object's dc:title metadata. */
		kXMPTitle,

		/** Alt/actual text obtained from object's dc:description metadata. */
		kXMPDescription,

		/** Alt/actual text obtained from object's photoshop:Headline metadata. */
		kXMPHeadline,

		/** Alt/actual text obtained from object's user specified metadata property. */
		kXMPOther,

		/** Alt/actual text associated through XML structure. */
		kXMLStructure
	} TextSourceType;

	typedef enum
	{
		/** Determine the tag from XML structure, or fallback to standard tag. */
		kFromStructure = 0,
		/** Tag as artifact. */
		kArtifact,
		/** Apply standard tag (based on object type). */
		kBasedOnObject
	} TagType;

	typedef enum
	{
		/** Fixed size. */
		kFixed = 0,
		/** Size relative to page width. */
		kRelative
	} ImageSize;

	typedef enum
	{
		/** Image will be aligned left. */
		kAlignLeft = 0, 
		/** Image will be aligned center. */
		kAlignCenter, 
		/** Image will be aligned right. */
		kAlignRight,
	} ImageAlignment;

	typedef enum
	{
		/** Page Break before image. */
		kBefore = 0, 
		/** Page Break after image. */
		kAfter,
		/** Page Break before and after image. */
		kBeforeAndAfter
	} ImagePageBreak;

	typedef enum
	{
		/** Float left. */
		kFloatLeft = 0,
		/** Float right. */
		kFloatRight,
		/** Custom alignment and spacing. */
        kAlignmentAndSpacing
	} CustomLayoutType;

	/* OBSOLETE: Do not use. Use CustomSizeType instead. */
	typedef enum
	{
		/** Width none. */
		kNoneWidth = 0,
		/** Width default. */
		kDefaultWidth,
		/** Size relative to text flow. */
		kRelativeWidth,
		/** Width fixed. */
		kFixedWidth,
		/** Width set to custom value. */
		kCustomValueWidth
	} CustomWidthType;

	/* OBSOLETE: Do not use. Use CustomSizeType instead. */
	typedef enum
	{
		/** Height none. */
		kNoneHeight = 0,
		/** Height default. */
		kDefaultHeight,
		/** Height fixed. */
		kFixedHeight,
		/** Height set to custom value. */
		kCustomValueHeight
	} CustomHeightType;

	typedef enum
	{
		/** Size none. */
		kNoneSize = 0,
		/** Size default. */
		kDefaultSize,
		/** Size fixed. */
		kFixedSize,
		/** Size relative to text flow. */
		kRelativeToTextFlow,
		/** Size relative to text Size. */
		kRelativeToTextSize,
		/** Width set to custom value. */
		kCustomValWidth,
		/** Height set to custom value. */
		kCustomValHeight
	} CustomSizeType;

	/**
		Set alternate text source type.
		@param sourceType IN the alternate text source type
	*/
	virtual void SetAltTextSourceType(TextSourceType sourceType) = 0;

	/**
		Get alternate text source type.
		@return TextSourceType: the alternate text source type
	*/
	virtual TextSourceType GetAltTextSourceType() const = 0;

	/**
		Set custom alternate text.
		@param customText IN the custom alternate text
	*/
	virtual void SetCustomAltText(const PMString &customText) = 0;

	/**
		Get custom alternate text.
		@param customText OUT the cutom alternate text
	*/
	virtual void GetCustomAltText(PMString &customText) const = 0;

	/**
		Set alt text metadata property.
		@param nsPrefix IN the xmp schema namespace prefix
		@param propertyPath IN the xmp property path
	*/
	virtual void SetAltTextMetadataProperty(const PMString& nsPrefix, const PMString& propertyPath) = 0;

	/**
		Get alt text metadata property.
		@param nsPrefix OUT the xmp schema namespace prefix
		@param propertyPath OUT the xmp property path
	*/
	virtual void GetAltTextMetadataProperty(PMString& nsPrefix, PMString& propertyPath) const = 0;

	/**
		Set actual text source type.
		@param sourceType IN the actual text source type
	*/
	virtual void SetActualTextSourceType(TextSourceType sourceType) = 0;

	/**
		Get actual text source type.
		@return TextSourceType: the actual text source type
	*/
	virtual TextSourceType GetActualTextSourceType() const = 0;

	/**
		Set custom actual text.
		@param customText IN the custom actual text
	*/
	virtual void SetCustomActualText(const PMString &customText) = 0;

	/**
		Get custom actual text.
		@param customText OUT the custom actual text
	*/
	virtual void GetCustomActualText(PMString &customText) const = 0;

	/**
		Set actual text metadata property.
		@param nsPrefix IN the xmp schema namespace prefix
		@param propertyPath IN the xmp property path
	*/
	virtual void SetActualTextMetadataProperty(const PMString& nsPrefix, const PMString& propertyPath) = 0;

	/**
		Get actual text metadata property.
		@param nsPrefix OUT the xmp schema namespace prefix
		@param propertyPath OUT the xmp property path
	*/
	virtual void GetActualTextMetadataProperty(PMString& nsPrefix, PMString& propertyPath) const = 0;

	/**
		Set tag type.
		@param tagType IN the tag type
	*/
	virtual void SetTagType(TagType tagType) = 0;

	/**
		Get tag type.
		@return TagType: the tag type
	*/
	virtual TagType GetTagType() const = 0;

	/**
		Set custom image conversion preference.
		@param custom IN whether to do custom conversion or not
	*/
	virtual void SetCustomImageConversion(bool16 custom) = 0;

	/**
		Get custom image conversion preference.
		@return bool16: whether to do custom conversion or not
	*/
	virtual bool16 GetCustomImageConversion() const = 0;

	/**
		Set image conversion type.
		@param type IN image conversion format
	*/
	virtual void SetImageType(IXMLExportOptions::ImageType type) = 0;

	/**
		Get image conversion type.
		@return IXMLExportOptions::ImageType: image conversion format
	*/
	virtual IXMLExportOptions::ImageType GetImageType() const = 0;


	/**
		Set image resolution.
		@param resolution IN the resolution value
	*/
	virtual void SetImageResolution(const PMReal &resolution) = 0;

	/**
		Get image resolution.
		@param resolution OUT the resolution value
	*/
	virtual void GetImageResolution(PMReal &resolution) const = 0;

	/**
		Set jpeg encoding option.
		@param encoding IN JPEG encoding scheme to choose
	*/
	virtual void SetJPEGEncoding(IXMLExportOptions::JPEGEncoding encoding) = 0;

	/**
		Get jpeg encoding option.
		@return IXMLExportOptions::JPEGEncoding: JPEG encoding scheme
	*/
	virtual IXMLExportOptions::JPEGEncoding GetJPEGEncoding() const = 0;

	/**
		Set jpeg quality.
		@param quality IN quality level to use for exported JPEG
	*/
	virtual void SetJPEGQuality(IXMLExportOptions::JPEGQuality quality) = 0;

	/**
		Get jpeg quality.
		@return IXMLExportOptions::JPEGQuality: quality level to use for exported JPEG
	*/
	virtual IXMLExportOptions::JPEGQuality GetJPEGQuality() const = 0;

	/**
		Set gif palette type.
		@param palette IN kind of GIF palette to create
	*/
	virtual void SetGIFPaletteType(IXMLExportOptions::PaletteType palette) = 0;

	/**
		Get gif palette type.
		@return IXMLExportOptions::PaletteType: kind of GIF palette to create
	*/
	virtual IXMLExportOptions::PaletteType GetGIFPaletteType() const = 0;

	/**
		Set gif interlaced option.
		@param interlaced IN whether to create interlaced GIF
	*/
	virtual void SetGIFInterlaced(bool16 interlaced) = 0;

	/**
		Get gif interlaced option.
		@return bool16: whether to create interlaced GIF
	*/
	virtual bool16 GetGIFInterlaced() const = 0;

	/**
		Set custom layout.
		@param layout IN whether to do custom layout or not
	*/
	virtual void SetCustomLayout(bool16 layout) = 0;

	/**
		Get custom layout.
		@return bool16: whether to do custom layout or not
	*/
	virtual bool16 GetCustomLayout() const = 0;

	/**
		Set custom layout type.
		@param customLayoutType IN kind of custom layout type
	*/
	virtual void SetCustomLayoutType(CustomLayoutType customLayoutType) = 0;

	/**
		Get custom layout type.
		@return CustomLayoutType: type of custom layout
	*/
	virtual CustomLayoutType GetCustomLayoutType() const = 0;

	/**
		Set image alignment option.
		@param align IN kind of image alignment.
	*/
    virtual void SetImageAlignment(ImageAlignment align) = 0; 

	/**
		Get image alignment option.
		@return ImageAlignment: kind of image alignment.
	*/
	virtual ImageAlignment GetImageAlignment() const = 0; 

	/**
		Set image space before.
		@param before IN the space before
	*/
    virtual void SetImageSpaceBefore(const PMReal &before) = 0; 

	/**
		Get image space before.
		@return PMReal: the space before
	*/
	virtual void GetImageSpaceBefore(PMReal &before) const = 0; 

	/**
		Set image space after.
		@param before IN the space after
	*/
    virtual void SetImageSpaceAfter(const PMReal &after) = 0; 

	/**
		Get image space after.
		@return PMReal: the space after
	*/
	virtual void GetImageSpaceAfter(PMReal &after) const = 0; 

	/**
		Set use image page break.
		@param use IN use image page break.
	*/
    virtual void SetUseImagePageBreak(bool16 use) = 0; 

	/**
		Get use image page break.
		@return bool16: use image page break.
	*/
	virtual bool16 GetUseImagePageBreak() const = 0; 

	/**
		Set image page break.
		@param pageBreak IN image page break.
	*/
    virtual void SetImagePageBreak(ImagePageBreak pageBreak) = 0; 

	/**
		Get image page break.
		@return ImagePageBreak: image page break.
	*/
	virtual ImagePageBreak GetImagePageBreak() const = 0; 

	/**
		Copy data from pCopyFrom to the current instance.
		@param pCopyFrom IN instance to copy from
	*/
	virtual void CopyData(IObjectExportOptions *pCopyFrom) = 0;


	/**
		Get use original image preference.
		@return bool16: whether to use original image or not
	*/
	virtual bool16 GetUseOriginalImage() const = 0; 
	
	/**
		Set the use original image preference.
		@param useOriginalImage IN whether to use original image or not
	*/
	virtual void SetUseOriginalImage(bool16 useOriginalImage) = 0; 

	/**
		Set epub type.
		The list of valid epub types are in http://www.idpf.org/epub/vocab/structure/# .
		@param epubType IN epub type
	*/
	virtual void SetEpubType(const PMString & epubType) = 0; 

	/**
		Get epub type.
		@return PMString: the epub type
	*/
	virtual void GetEpubType(PMString & epubType) const = 0;

	/* OBSOLETE: Do not use. Use CustomSizeType based APIs instead. */
	/* Obsolete block starts */

	/**
		Set the value of custom height.
		@param height IN to set the value of custom height.
	*/
    virtual void SetCustomHeightValue(const PMString &height) = 0;

	/**
		Get the value of custom height.
		@return height: custom height value.
	*/
	virtual void GetCustomHeightValue(PMString &height) const = 0; 

	/**
		Set the value of custom width.
		@param width IN to set the value of width.
	*/
    virtual void SetCustomWidthValue(const PMString &width) = 0;

	/**
		Get the value of custom width.
		@return width: custom  width value.
	*/
	virtual void GetCustomWidthValue(PMString &width) const = 0; 

	/**
		Get width type.
		@return CustomWidthType:  width type.
	*/
	virtual CustomWidthType GetCustomWidthType() const = 0;

	/**
		Get height type.
		@return CustomHeightType: height type.
	*/
	virtual CustomHeightType GetCustomHeightType() const = 0;

	/**
		Set width type
		@param customWidthType IN to set width type.
	*/
	virtual void SetCustomWidthType(CustomWidthType customWidthType) = 0;

	/**
		Set height type
		@param customHeightType IN to set height type.
	*/
	virtual void SetCustomHeightType(CustomHeightType customHeightType) = 0;

	/* Obsolete block ends */

	/**
		Set the value of custom size.
		@param Size IN to set the value of size.
	*/
    virtual void SetCustomSizeValue(const PMString & sizeString) = 0;

	/**
		Get the value of custom sizeString.
		@return sizeString: custom  width value.
	*/
	virtual void GetCustomSizeValue(PMString &sizeString) const = 0; 

	/**
		Get size type.
		@return CustomSizeType:  size type.
	*/
	virtual CustomSizeType GetCustomSizeType() const = 0;

	/**
		Set size type.
		@param customSizeType IN to set size type.
	*/
	virtual void SetCustomSizeType(CustomSizeType customSizeType) = 0;

	/** 
        Get custom content conversion preference. 
        @return bool16: whether to do custom conversion or not 
    */ 
	virtual bool16 GetCustomContentConversion() const = 0; 

	 /** 
        Set custom content conversion preference. 
        @param custom IN whether to do custom conversion or not 
    */
	virtual void SetCustomContentConversion(bool16 custom) = 0;
};

#endif
