//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IObjectExportOptionsData.h $
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
#ifndef __IObjectExportOptionsData__
#define __IObjectExportOptionsData__

#include "GenericID.h"
#include "IObjectExportOptions.h"

/**
	Interface for export options associated with an object. Also maintains
	a state value for with each export option.
*/
class IObjectExportOptionsData : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_IOBJECTEXPORTOPTIONSDATA};

	/* Enumerates the state of an option.
	   The option's value should not be accessed if the state is "kValueNotSet" or "kValueMixed".
	*/
	typedef enum
	{
		/* No value set - invalid (clients should treat as opaque). This is the default state. */
		kValueNotSet = 0,
		/* Valid value set. */
		kValueSet,
		/* The value is different across the selection. */
		kValueMixed
	} OptionState;

	/**
		Set alternate text source type.
		@param sourceType IN the alternate text source type
	*/
	virtual void SetAltTextSourceType(IObjectExportOptions::TextSourceType sourceType) = 0;

	/**
		Get alternate text source type.
		@return IObjectExportOptions::TextSourceType the alternate text source type
	*/
	virtual IObjectExportOptions::TextSourceType GetAltTextSourceType() const = 0;

	/**
		Get alternate text source type state.
		@return OptionState: the current state of the option
	*/
	virtual OptionState GetAltTextSourceTypeState() const = 0;

	/**
		Set custom alternate text.
		@param customText IN the custom alternate text
	*/
	virtual void SetCustomAltText(const PMString &customText) = 0;

	/**
		Get custom alternate text.
		@param customText OUT the custom alternate text
	*/
	virtual void GetCustomAltText(PMString &customText) const = 0;

	/**
		Get custom alternate text state.
		@return OptionState: the current state of the option
	*/
	virtual OptionState GetCustomAltTextState() const = 0;

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
		Get alt text metadata property state.
		@return OptionState: the current state of the option
	*/
	virtual OptionState GetAltTextMetadataPropertyState() const = 0;

	/**
		Set actual text source type.
		@param sourceType IN the actual text source type
	*/
	virtual void SetActualTextSourceType(IObjectExportOptions::TextSourceType sourceType) = 0;

	/**
		Get actual text source type.
		@return IObjectExportOptions::TextSourceType the actual text source type
	*/
	virtual IObjectExportOptions::TextSourceType GetActualTextSourceType() const = 0;

	/**
		Get actual text source type state.
		@return OptionState: the current state of the option
	*/
	virtual OptionState GetActualTextSourceTypeState() const = 0;

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
		Get custom actual text state.
		@return OptionState: the current state
	*/
	virtual OptionState GetCustomActualTextState() const = 0;

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
		Get actual text metadata property state.
		@return OptionState: the current state of the option
	*/
	virtual OptionState GetActualTextMetadataPropertyState() const = 0;

	/**
		Set tag type.
		@param tagType IN the tag type
	*/
	virtual void SetTagType(IObjectExportOptions::TagType tagType) = 0;

	/**
		Get tag type.
		@return IObjectExportOptions::TagType: the tag type
	*/
	virtual IObjectExportOptions::TagType GetTagType() const = 0;

	/**
		Get tag type state.
		@return OptionState: the current state of the option
	*/
	virtual OptionState GetTagTypeState() const = 0;

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
		Get custom image conversion state.
		@return OptionState: the current state of the option
	*/
	virtual OptionState GetCustomImageConversionState() const = 0;

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
		Get image conversion type state.
		@return OptionState: the current state of the option
	*/
	virtual OptionState GetImageTypeState() const = 0;


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
		Get image resolution state.
		@return OptionState: the current state of the option
	*/
	virtual OptionState GetImageResolutionState() const = 0;

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
		Get jpeg encoding option state.
		@return OptionState: the current state of the option
	*/
	virtual OptionState GetJPEGEncodingState() const = 0;

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
		Get jpeg quality state.
		@return OptionState: the current state of the option
	*/
	virtual OptionState GetJPEGQualityState() const = 0;

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
		Get gif palette type state.
		@return OptionState: the current state of the option
	*/
	virtual OptionState GetGIFPaletteTypeState() const = 0;

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
		Get gif interlaced option state.
		@return OptionState: the current state of the option
	*/
	virtual OptionState GetGIFInterlacedState() const = 0;

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
		Get custom layout state.
		@return OptionState: the current state of the option
	*/
	virtual OptionState GetCustomLayoutState() const = 0;

	/**
		Set custom layout type.
		@param  customLayoutType IN kind of custom layout
	*/
	virtual void SetCustomLayoutType(IObjectExportOptions::CustomLayoutType customLayoutType) = 0;

	/**
		Get custom layout type.
		@return CustomLayoutType: the type of custom layout
	*/
	virtual IObjectExportOptions::CustomLayoutType GetCustomLayoutType() const = 0;

	/**
		Get custom layout type state.
		@return OptionState: the current state of the option
	*/
	virtual OptionState GetCustomLayoutTypeState() const = 0;

	/**
		Set image alignment option.
		@param align IN kind of image alignment.
	*/
	virtual void SetImageAlignment(IObjectExportOptions::ImageAlignment align) = 0; 

	/**
		Get image alignment option.
		@return ImageAlignment: kind of image alignment.
	*/
	virtual IObjectExportOptions::ImageAlignment GetImageAlignment() const = 0; 

	/**
		Get image alignment option state.
		@return OptionState: the current state of the option
	*/
	virtual OptionState GetImageAlignmentState() const = 0;

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
		Get image space before state.
		@return OptionState: the current state of the option
	*/
	virtual OptionState GetImageSpaceBeforeState() const = 0; 

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
		Get image space after state.
		@return OptionState: the current state of the option
	*/
	virtual OptionState GetImageSpaceAfterState() const = 0; 	
	
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
		Get use image page break state.
		@return OptionState: the current state of the option
	*/
	virtual OptionState GetUseImagePageBreakState() const = 0; 

	/**
		Set image page break.
		@param pageBreak IN image page break.
	*/
    virtual void SetImagePageBreak(IObjectExportOptions::ImagePageBreak pageBreak) = 0; 

	/**
		Get image page break.
		@return ImagePageBreak: image page break.
	*/
	virtual IObjectExportOptions::ImagePageBreak GetImagePageBreak() const = 0; 

	/**
		Get image page break state.
		@return OptionState: the current state of the option
	*/
	virtual OptionState GetImagePageBreakState() const = 0; 

	/**
		Copy data from an instance of the same interface to this instance.
		@param pCopyFrom IN instance to copy from
	*/
	virtual void CopyData(const IObjectExportOptionsData *pCopyFrom) = 0;

	/**
		Copy data from an instance of IObjectExportOptions to this instance.
		@param pCopyFrom IN instance to copy from
	*/
    virtual void CopyOptions(const IObjectExportOptions *pCopyFrom) = 0;

	/**
		Resets the state of all options to kValueNotSet.
	*/
	virtual void ResetState() = 0;

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
		Get use original image state.
		@return OptionState: the current state of the option
	*/
	virtual OptionState GetUseOriginalImageState() const = 0;

	/**
		Set the epub type.
		The list of valid epub types are in http://www.idpf.org/epub/vocab/structure/# .
		@param epubType IN to set epub type
	*/
	virtual void SetEpubType(const PMString & epubType) = 0;

	/**
		Get epub type.
		@return PMString: epub type
	*/
	virtual void GetEpubType(PMString & epubType) const = 0; 

	/**
		Get epub type state.
		@return OptionState: the current state of the option
	*/
	virtual OptionState GetEpubTypeState() const = 0;

	/* OBSOLETE: Do not use. Use CustomSizeType based APIs instead. */
	/* Obsolete block starts */

		/**
		Set value of custom height.
		@param height IN to set custom height value.
	*/
	virtual void SetCustomHeightValue(const PMString &height) = 0; 

	/**
		Get the value of custom height.
		@return height: custom height value.
	*/
	virtual void GetCustomHeightValue(PMString &height) const = 0; 

	/**
		Set value of custom width. 
		@param width IN to set custom width value.
	*/
	virtual void SetCustomWidthValue(const PMString &width) = 0; 

	/**
		Get value of custom width.
		@return width: custom width value.
	*/
	virtual void GetCustomWidthValue(PMString &width) const = 0; 

	/**
		Get state of custom height value.
		@return OptionState: current state of custom height value.
	*/
	virtual OptionState GetCustomHeightValueState() const = 0;

	/**
		Get state of custom width value.
		@return OptionState: current state of custom width value.
	*/
	virtual OptionState GetCustomWidthValueState() const = 0;

	/**
		Get state of height type.
		@return OptionState: current state of height type.
	*/
	virtual OptionState GetCustomHeightTypeState() const = 0;

	/**
		Get state of width type.
		@return OptionState: current state of width type.
	*/
	virtual OptionState GetCustomWidthTypeState() const = 0;

	/**
		Set width type
		@param customWidthType IN to set width type.
	*/
	virtual  void SetCustomWidthType(IObjectExportOptions::CustomWidthType customWidthType) = 0;

	/**
		Get width type.
		@return CustomWidthType:  width type.
	*/
	virtual IObjectExportOptions::CustomWidthType GetCustomWidthType() const = 0;

	/**
		Set height type
		@param customHeightType IN to set height type.
	*/
	virtual  void SetCustomHeightType(IObjectExportOptions::CustomHeightType customHeightType) = 0;

	/**
		Get height type.
		@return CustomHeightType: height type.
	*/
	virtual IObjectExportOptions::CustomHeightType GetCustomHeightType() const = 0;
	/* Obsolete block ends */

	/**
		Get value of custom size.
		@return size: custom size value.
	*/
	virtual void GetCustomSizeValue(PMString &size) const = 0; 

	/**
		Get state of custom size value.
		@return OptionState: current state of custom size value.
	*/
	virtual OptionState GetCustomSizeValueState() const = 0;

	/**
		Get state of size type.
		@return OptionState: current state of size type.
	*/
	virtual OptionState GetCustomSizeTypeState() const = 0;

	/**
		Set size type
		@param CustomSizeType IN to set size type.
	*/
	virtual  void SetCustomSizeType(IObjectExportOptions::CustomSizeType CustomSizeType) = 0;

	/**
		Get size type.
		@return CustomSizeType:  size type.
	*/
	virtual IObjectExportOptions::CustomSizeType GetCustomSizeType() const = 0;

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

	/**
		Get custom content conversion preference state.
		@return OptionState: the current state of the option
	*/
	virtual OptionState GetCustomContentConversionState() const = 0;
};

#endif
