//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ISVGExportSetPrefsCmdData.h $
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
//  Copyright 1997-2007 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __ISVGExportSetPrefsCmdData__
#define __ISVGExportSetPrefsCmdData__

#include "SVGExportID.h"
#include "ISVGExportPreferences.h"

/**
 A non-persistent data interface similar to ISVGExportPreferences
 
 @see ISVGExportPreferences
 */
class ISVGExportSetPrefsCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISVGEXPORTSETPREFSCMDDATA };

	/**
	 Gets embed images flag. If true, images should be embedded in the
	 generated SVG file; otherwise, images are externalized

	 @return kTrue if images should be embedded, else kFalse
	 */
	virtual bool16 GetEmbedImages() const = 0;
	/**
	 Sets embed images flag

	 @param embed	IN If kTrue, images are embedded.
	 */
	virtual void SetEmbedImages(bool16 embed) = 0;

	/**
	 Gets preferred image format

	 @return Preferred image format
	 */
	virtual ISVGExportPreferences::ImageFormat GetImageFormat() const = 0;
	/**
	 Sets preferred image format

	 @param format	IN Preferred image format
	 */
	virtual void SetImageFormat(ISVGExportPreferences::ImageFormat format) = 0;

	/**
	 Gets JPEG compression quality

	 @return JPEG compression quality
	 */
	virtual ISVGExportPreferences::JPEGQuality GetJPEGQuality() const = 0;
	/**
	 Sets JPEG compression quality

	 @param quality		IN New compression quality
	 */
	virtual void SetJPEGQuality(ISVGExportPreferences::JPEGQuality quality) = 0;

	/**
	 Gets GIF palette type

	 @return GIF palette type
	 */
	virtual ISVGExportPreferences::GIFPaletteType GetGIFPaletteType() const = 0;
	/**
	 Sets GIF palette type

	 @param palette		IN New GIF palette type
	 */
	virtual void SetGIFPaletteType(ISVGExportPreferences::GIFPaletteType palette) = 0;

	/**
	 Gets GIF interlacing

	 @return GIF interlacing setting
	 */
	virtual bool16 GetInterlacedGIF() const = 0;
	/**
	 Sets GIF interlacing

	 @param interlace	IN New GIF interlace setting
	 */
	virtual void SetInterlacedGIF(bool16 interlace) = 0;

	/**
	 Gets bitmap sampling

	 @return Bitmap sampling
	 */
	virtual ISVGExportPreferences::ExportBitmapSampling GetExportBitmapSampling() const = 0;
	/**
	 Sets bitmap sampling

	 @param sampling	IN New sampling setting
	 */
	virtual void SetExportBitmapSampling(ISVGExportPreferences::ExportBitmapSampling sampling) = 0;

	/**
	 Gets embed fonts flag

	 @return Embed fonts flag
	 */
	virtual bool16 GetEmbedFonts() const = 0;
	/**
	 Sets embed fonts flag

	 @param embed	IN New embed setting
	 */
	virtual void SetEmbedFonts(bool16 embed) = 0;

	/**
	 Gets font subsetting option

	 @return Font subsetting option
	 */
	virtual ISVGExportPreferences::FontSubsetting GetFontSubsetting() const = 0;
	/**
	 Sets font subsetting option

	 @param subset	IN New font subsetting option
	 */
	virtual void SetFontSubsetting(ISVGExportPreferences::FontSubsetting subset) = 0;
	
	/**
	 Gets reader's spreads setting

	 @return Reader's spreads setting
	 */
	virtual bool16 GetOutputReadersSpreads() const = 0;
	/**
	 Sets reader's spreads setting

	 @param output	IN New reader's spreads setting
	 */
	virtual void SetOutputReadersSpreads(bool16 output) = 0;

	/**
	 Gets image sampling option

	 @return Image sampling option
	 */
	virtual ISVGExportPreferences::ImageSampling GetImageSampling() const = 0;
	/**
	 Sets image sampling option

	 @param sampling	IN New sampling option
	 */
	virtual void SetImageSampling(ISVGExportPreferences::ImageSampling sampling) = 0;

	/**
	 Gets real precision

	 @return Real precision as an int between 1 and 7, inclusive
	 */
	virtual uint32 GetRealPrecision() const = 0;
	/**
	 Sets real precision. Must be between 1 and 7, inclusive

	 @param precision	IN New real precision
	 */
	virtual void SetRealPrecision(uint32 precision) = 0;

	/**
	 Gets rendering style

	 @return Rendering style
	 */
	virtual ISVGExportPreferences::RenderingStyle GetRenderingStyle() const = 0;
	/**
	 Sets rendering style

	 @param style	IN New rendering style
	 */
	virtual void SetRenderingStyle(ISVGExportPreferences::RenderingStyle style) = 0;

	/**
	 Gets file encoding option

	 @return File encoding option
	 */
	virtual ISVGExportPreferences::FileEncoding GetFileEncoding() const = 0;
	/**
	 Sets file encoding option

	 @param encoding	IN New encoding option
	 */
	virtual void SetFileEncoding(ISVGExportPreferences::FileEncoding encoding) = 0;

	/**
	 Gets style format

	 @return Style format
	 */
	virtual ISVGExportPreferences::StyleFormat GetStyleFormat() const = 0;
	/**
	 Sets style format

	 @param format	IN New style format
	 */
	virtual void SetStyleFormat(ISVGExportPreferences::StyleFormat format) = 0;

	/**
	 Gets page range format

	 @return Page range format
	 */
	virtual ISVGExportPreferences::PageRangeFormat GetPageRangeFormat() const = 0;
	/**
	 Sets page range format

	 @param format		IN New page range format
	 */
	virtual void SetPageRangeFormat(ISVGExportPreferences::PageRangeFormat format) = 0;

	/**
	 Gets page range as a string

	 @return Page range string
	 */
	virtual PMString const &GetPageRange() const = 0;
	/**
	 Sets page range as a string

	 @param range		IN New page range string
	 */
	virtual void SetPageRange(PMString const &range) = 0;

	/**
	 Gets flatten output flag

	 @return Flatten output flag
	 */
	virtual bool16 GetFlattenOutput() const = 0;
	/**
	 Sets flatten output flag

	 @param flatten		IN New flatten output flag
	 */
	virtual void SetFlattenOutput(bool16 flatten) = 0;

	/**
	 Gets use native XP flag

	 @return Use native XP flag
	 */
	virtual bool16 GetUseNativeXP() const = 0;
	/**
	 Sets use native XP flag

	 @param useNativeXP		IN New use native XP flag
	 */
	virtual void SetUseNativeXP(bool16 useNativeXP) = 0;

	/**
	 Gets flattener style

	 @return UID of flattener style
	 */
	virtual UID GetFlattenerStyle() const = 0;
	/**
	 Sets flattener style

	 @param style		IN New flattener style UID
	 */
	virtual void SetFlattenerStyle(UID const &style) = 0;

	/**
	 Gets ignore spread overrides flag

	 @return Ignore spread overrides flag
	 */
	virtual bool16 GetIgnoreFlattenerSpreadOverrides() const = 0;
	/**
	 Sets ignore spread overrides flag

	 @param ignore		IN New ignore spread overrides flag
	 */
	virtual void SetIgnoreFlattenerSpreadOverrides(bool16 ignore) = 0;

	/**
	 Gets pageitem export flag

	 @return pageitem export flag
	 */
	virtual bool16 GetPageItemExport() const = 0;
	/**
	 Sets pageitem export flag

	 @param pageitemExport	IN New pageitem export flag
	 */
	virtual void SetPageItemExport(bool16 pageitemExport) = 0;
};

#endif //!def __ISVGExportSetPrefsCmdData__
