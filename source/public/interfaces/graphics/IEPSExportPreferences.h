//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IEPSExportPreferences.h $
//  
//  Owner: David Berggren
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
//  Stores the current EPS export preferences. These preferences should
//  be set using the kSetEPSExportPrefsCmdBoss command.	
//  
//========================================================================================

#pragma once
#ifndef __IEPSExportPreferences__
#define __IEPSExportPreferences__

#include "IPMUnknown.h"
#include "PersistUIDList.h"
#include "PrintID.h"

/** Settings for EPS export.
	Use the kSetEPSExportPrefsCmdBoss command to set EPS Export Prefs!
*/
class IEPSExportPreferences : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_IEPSEXPORTPREFERENCES };
public:
	/** For use with EPS export settings.
	*/
	enum 
	{
		/** Don't Change current setting - can be used for any setting.
		*/
		kDontChange						= 0,

		/** Type of output file - EPS file is only option supported.
		*/
		kExportEPSFile					= 1,
		/** Type of output file - SEP file - not supported don't use.
		*/
		kExportSEPFile_Inval			= 2,

		/** Page option - export all pages.
		*/
		kExportAllPages					= 3,
		/** Page option - export page range.
		*/
		kExportRanges					= 4,
		/** Page option - export section - not supported don't use.
		*/
		kExportBySection_Inval			= 5,

		/** Export reader's spread ON.
		*/
		kExportReaderSpreadON			= 6,
		/** Export reader's spread OFF.
		*/
		kExportReaderSpreadOFF			= 7,

		/** Desired PS output level - All - not suported don't use.
		*/
		kExportPSLevelAll_Obsolete		= 8,
		/** Desired PS output level - PostScript level 2.
		*/
		kExportPSLevel2					= 9,
		/** Desired PS output level - PostScript level 2 with DEFG support.
		*/
		kExportPSLevel2WithDEFG			= 10,
		/** Desired PS output level - PostScript level 3.
		*/
		kExportPSLevel3					= 11,

		/** Desired Output Color Space - Gray.
		*/
		kExportPSColorSpaceGray			= 12,
		/** Desired Output Color Space - RGB.
		*/
		kExportPSColorSpaceRGB			= 13,
		/** Desired Output Color Space - CMYK.
		*/
		kExportPSColorSpaceCMYK			= 14,
		/** Desired Output Color Space - Device Independent - PostScript Color Management.
		*/
		kExportPSColorSpaceDIC			= 15,
		/** Desired Output Color Space - Leave Unchanged
		*/
		kExportPSColorSpaceLeaveUnchanged = 56,

		/** Preview option - No preview
		*/
		kExportPreviewNone				= 16,
		/** Preview option - TIFF preview
		*/
		kExportPreviewTIFF				= 17,
		/** Preview option - PICT preview - Mac only
		*/
		kExportPreviewPICT				= 18,   // PICT preview is not supported from CC

		/** Desired Data Format - Binary data
		*/
		kExportBinaryData				= 19,
		/** Desired Data Format - ASCII data
		*/
		kExportASCIIData				= 20,

		/** Bitmap output options - Omit - not supported don't use - instead use kExportOmitBitmapImagesON below
		*/
		kExportBMSampleOmit_Inval		= 21,
		/** Bitmap output options - Normal mean All image data
		*/
		kExportBMSampleNormal			= 22,
		/** Bitmap output options - LowRes means Proxy image data
		*/
		kExportBMSampleLowRes			= 23,
		/** Bitmap output options - Optimized subsample - not supported don't use
		*/
		kExportBMSampleOptimized		= 24,

		/** OPI image replacement ON
		*/
		kExportOPIReplaceON				= 25,
		/** OPI image replacement OFF
		*/
		kExportOPIReplaceOFF			= 26,

		/** Include Fonts - Whole means Complete
		*/
		kExportIncludeFontsWhole		= 27,
		/** Include Fonts - Subset 
		*/
		kExportIncludeFontsSubset		= 28,
		/** Include Fonts - None
		*/
		kExportIncludeFontsNone			= 29,
		/** Include Fonts - Subset Large - not supported don't use
		*/
		kExportIncludeFontsSubsetLarge	= 50, 
		
		/** Turn Bleed ON
		*/
		kExportBleedON					= 30,
		/** Turn Bleed OFF
		*/
		kExportBleedOFF					= 31,

		/** Page marks - All page marks ON - not supported don't use
		*/
		kExportAllPageMarksON			= 32,
		/** Page marks - All page marks OFF - not supported don't use
		*/
		kExportAllPageMarksOFF			= 33,
		/** Page marks - Crop marks ON - not supported don't use
		*/
		kExportCropMarksON				= 34,
		/** Page marks - Crop marks OFF - not supported don't use
		*/
		kExportCropMarksOFF				= 35,
		/** Page marks - Bleed marks ON - not supported don't use
		*/
		kExportBleedMarksON				= 36,
		/** Page marks - Bleed marks OFF - not supported don't use
		*/
		kExportBleedMarksOFF			= 37,
		/** Page marks - Page Info ON - not supported don't use
		*/
		kExportPageInfoON				= 38,
		/** Page marks - Page Info OFF - not supported don't use
		*/
		kExportPageInfoOFF				= 39,
		/** Page marks - Registration marks ON - not supported don't use
		*/
		kExportRegMarksON				= 40,
		/** Page marks - Registration marks OFF - not supported don't use
		*/
		kExportRegMarksOFF				= 41,
		/** Page marks - Color bars ON - not supported don't use
		*/
		kExportColorBarsON				= 42,
		/** Page marks - Color bars OFF - not supported don't use
		*/
		kExportColorBarsOFF				= 43,

		/** Omit placed PDFs ON
		*/
		kExportOmitPDFON				= 44,
		/** Omit placed PDFs OFF
		*/
		kExportOmitPDFOFF				= 45,

		/** Omit placed EPSs ON
		*/
		kExportOmitEPSON				= 46,
		/** Omit placed EPSs OFF
		*/
		kExportOmitEPSOFF				= 47,

		/** Omit placed bitmap images ON
		*/
		kExportOmitBitmapImagesON		= 48,
		/** Omit placed bitmap images OFF
		*/
		kExportOmitBitmapImagesOFF		= 49,
		
		/** Spot/OverPrint - Legacy - Simulate Overprint OFF
		*/
		kExportLegacy					= 51,
		/** Spot/OverPrint - Simulate Press - Simulate Overprint ON
		*/
		kExportSimulatePress			= 52,
		/** Spot/OverPrint - Simulate Screen - not supported don't use
		*/
		kExportSimulateScreen			= 53,

		/** Ignore spread overrides when flattening ON
		*/
		kExportIgnoreSpreadOverridesON	= 54,
		/** Ignore spread overrides when flattening OFF
		*/
		kExportIgnoreSpreadOverridesOFF	= 55

		// LAST ENUM NUMBER ADDED: kExportPSColorSpaceLeaveUnchanged = 56
	};

	/**	Set which pages to export.
		@param pageOption IN kExportAllPages or kExportRanges
	 */
	virtual void SetEPSExPageOption(const int32 pageOption) = 0;

	/**	Set page range string.
		@param pageRange IN page range string
	 */
	virtual void SetEPSExPageRange(const PMString& pageRange) = 0;

	/**	Set export readers spread.
		@param readerSpread IN kExportReaderSpreadON or kExportReaderSpreadOFF
	 */
	virtual void SetEPSExReaderSpread(const int32 readerSpread) = 0;

	/**	Set PostScript level.
		@param postScriptLevel IN kExportPSLevel2 or kExportPSLevel2WithDEFG or kExportPSLevel3
	 */
	virtual void SetEPSExPSLevel(const int32 postScriptLevel) = 0;

	/**	Set Bleed on/off.
		@param bleedOnOff IN kExportBleedON or kExportBleedOFF
	 */
	virtual void SetEPSExBleedOnOff(const int32 bleedOnOff) = 0;

	/**	Set Bleed top value.
		@param bleedAmt IN bleed top value
	 */
	virtual void SetEPSExBleedTop(const PMReal bleedAmt) = 0;

	/**	Set Bleed bottom value.
		@param bleedAmt IN bleed bottom value
	 */
	virtual void SetEPSExBleedBottom(const PMReal bleedAmt) = 0;

	/**	Set Bleed inside (side closest to binding) value.
		@param bleedAmt IN bleed inside value
	 */
	virtual void SetEPSExBleedInside(const PMReal bleedAmt) = 0;

	/**	Set Bleed outside (side farthest from binding) value.
		@param bleedAmt IN bleed outside value
	 */
	virtual void SetEPSExBleedOutside(const PMReal bleedAmt) = 0;

	/**	Set output color space.
		@param colorSpace IN kExportPSColorSpaceGray, kExportPSColorSpaceRGB, kExportPSColorSpaceCMYK, 
				kExportPSColorSpaceDIC or kExportPSColorSpaceLeaveUnchanged
	 */
	virtual void SetEPSExColorSpace(const int32 colorSpace) = 0;

	/**	Set preview generation.
		@param preview IN kExportPreviewNone or kExportPreviewTIFF or kExportPreviewPICT (Mac only)
	 */
	virtual void SetEPSExPreview(const int32 preview) = 0;

	/**	Set output data format.
		@param dataFormat IN kExportBinaryData or kExportASCIIData
	 */
	virtual void SetEPSExDataFormat(const int32 dataFormat) = 0;

	/**	Set send image data.
		@param bitmapSampling IN kExportBMSampleNormal (All) or kExportBMSampleLowRes (Proxy)
	 */
	virtual void SetEPSExBitmapSampling(const int32 bitmapSampling) = 0;

	/**	Set include fonts.
		@param includeFonts IN kExportIncludeFontsWhole (Complete) or kExportIncludeFontsSubset or kExportIncludeFontsNone
	 */
	virtual void SetEPSExIncludeFonts(const int32 includeFonts) = 0;

	/**	Set OPI replacement on/off.
		@param opiReplace IN kExportOPIReplaceON or kExportOPIReplaceOFF
	 */
	virtual void SetEPSExOPIReplace(const int32 opiReplace) = 0;

	/**	Set all page marks on/off - not supported don't use.
		@param allPageMarks IN kExportAllPageMarksON or kExportAllPageMarksOFF
	 */
	virtual void SetEPSExAllPageMarks(const int32 allPageMarks) = 0;

	/**	Set crop marks on/off - not supported don't use.
		@param cropMarks IN kExportCropMarksON or kExportCropMarksOFF
	 */
	virtual void SetEPSExCropMarks(const int32 cropMarks) = 0;

	/**	Set bleed marks on/off - not supported don't use.
		@param bleedMarks IN kExportBleedMarksON or kExportBleedMarksOFF
	 */
	virtual void SetEPSExBleedMarks(const int32 bleedMarks) = 0;

	/**	Set page info on/off - not supported don't use.
		@param pageInfo IN kExportPageInfoON or kExportPageInfoOFF
	 */
	virtual void SetEPSExPageInfo(const int32 pageInfo) = 0;

	/**	Set registration marks on/off - not supported don't use.
		@param regMarks IN kExportRegMarksON or kExportRegMarksOFF
	 */
	virtual void SetEPSExRegMarks(const int32 regMarks) = 0;

	/**	Set color bars on/off - not supported don't use.
		@param colorBars IN kExportColorBarsON or kExportColorBarsOFF
	 */
	virtual void SetEPSExColorBars(const int32 colorBars) = 0;

	/**	Set omit PDF on/off.
		@param omitPDF IN kExportOmitPDFON or kExportOmitPDFOFF
	 */
	virtual void SetEPSExOmitPDF(const int32 omitPDF) = 0;

	/**	Set omit EPS on/off.
		@param omitEPS IN kExportOmitEPSON or kExportOmitEPSOFF
	 */
	virtual void SetEPSExOmitEPS(const int32 omitEPS) = 0;

	/**	Set omit bitmap images on/off.
		@param omitBitmapImages IN kExportOmitBitmapImagesON or kExportOmitBitmapImagesOFF
	 */
	virtual void SetEPSExOmitBitmapImages(const int32 omitBitmapImages) = 0;

	/**	Set Simulate Overprint on/off.
		@param spotOverPrint IN kExportLegacy (OFF) or kExportSimulatePress (ON)
	 */
	virtual void SetEPSExSpotOverPrint(int32 spotOverPrint) = 0;

	/**	Set flattener style UID to use.
		@param style IN UID of flattener style to use
	 */
	virtual void SetEPSExFlattenerStyle(UID const &style) = 0;

	/**	Set ignore flattener spread overrides on/off.
		@param ignoreOverrides IN kExportIgnoreSpreadOverridesON or kExportIgnoreSpreadOverridesOFF
	 */
	virtual void SetEPSExIgnoreFlattenerSpreadOverrides(const int32 ignoreOverrides) = 0;

	/**	Get which pages to export.
		@return kExportAllPages or kExportRanges
	 */
	virtual int32			GetEPSExPageOption() const = 0;

	/**	Get page range string.
		@return page range string
	 */
	virtual PMString		GetEPSExPageRange() const = 0;

	/**	Get readers spread.
		@return kExportReaderSpreadON or kExportReaderSpreadOFF
	 */
	virtual int32			GetEPSExReaderSpread() const = 0;

	/**	Get PostScript level.
		@return kExportPSLevel2 or kExportPSLevel2WithDEFG or kExportPSLevel3
	 */
	virtual int32			GetEPSExPSLevel() const = 0;

	/**	Get Bleed on/off.
		@return kExportBleedON or kExportBleedOFF
	 */
	virtual int32			GetEPSExBleedOnOff() const = 0;

	/**	Get Bleed top value.
		@return bleed top value
	 */
	virtual PMReal			GetEPSExBleedTop() const = 0;

	/**	Get Bleed bottom value.
		@return bleed bottom value
	 */
	virtual PMReal			GetEPSExBleedBottom() const = 0;

	/**	Get Bleed inside (side closest to binding) value.
		@return bleed inside value
	 */
	virtual PMReal			GetEPSExBleedInside() const = 0;

	/**	Get Bleed outside (side farthest from binding) value.
		@return bleed outside value
	 */
	virtual PMReal			GetEPSExBleedOutside() const = 0;

	/**	Get output color space.
		@return kExportPSColorSpaceGray, kExportPSColorSpaceRGB, kExportPSColorSpaceCMYK, 
				kExportPSColorSpaceDIC or kExportPSColorSpaceLeaveUnchanged
	 */
	virtual int32			GetEPSExColorSpace() const = 0;

	/**	Get preview generation.
		@return kExportPreviewNone or kExportPreviewTIFF or kExportPreviewPICT (Mac only)
	 */
	virtual int32			GetEPSExPreview() const = 0;

	/**	Get output data format.
		@return kExportBinaryData or kExportASCIIData
	 */
	virtual int32			GetEPSExDataFormat() const = 0;

	/**	Get send image data.
		@return kExportBMSampleNormal (All) or kExportBMSampleLowRes (Proxy)
	 */
	virtual int32			GetEPSExBitmapSampling() const = 0;

	/**	Get include fonts.
		@return kExportIncludeFontsWhole (Complete) or kExportIncludeFontsSubset or kExportIncludeFontsNone
	 */
	virtual int32			GetEPSExIncludeFonts() const = 0;

	/**	Get OPI replacement on/off.
		@return kExportOPIReplaceON or kExportOPIReplaceOFF
	 */
	virtual int32			GetEPSExOPIReplace() const = 0;

	/**	Get all page marks on/off - not supported don't use.
		@return kExportAllPageMarksON or kExportAllPageMarksOFF
	 */
	virtual int32			GetEPSExAllPageMarks() const = 0;

	/**	Get crop marks on/off - not supported don't use.
		@return kExportCropMarksON or kExportCropMarksOFF
	 */
	virtual int32			GetEPSExCropMarks() const = 0;

	/**	Get bleed marks on/off - not supported don't use.
		@return kExportBleedMarksON or kExportBleedMarksOFF
	 */
	virtual int32			GetEPSExBleedMarks() const = 0;

	/**	Get page info on/off - not supported don't use.
		@return kExportPageInfoON or kExportPageInfoOFF
	 */
	virtual int32			GetEPSExPageInfo() const = 0;

	/**	Get registration marks on/off - not supported don't use.
		@return kExportRegMarksON or kExportRegMarksOFF
	 */
	virtual int32			GetEPSExRegMarks() const = 0;

	/**	Get color bars on/off - not supported don't use.
		@return kExportColorBarsON or kExportColorBarsOFF
	 */
	virtual int32			GetEPSExColorBars() const = 0;

	/**	Get omit PDF on/off.
		@return kExportOmitPDFON or kExportOmitPDFOFF
	 */
	virtual int32			GetEPSExOmitPDF() const = 0;

	/**	Get omit EPS on/off.
		@return kExportOmitEPSON or kExportOmitEPSOFF
	 */
	virtual int32			GetEPSExOmitEPS() const = 0;

	/**	Get omit bitmap images on/off.
		@return kExportOmitBitmapImagesON or kExportOmitBitmapImagesOFF
	 */
	virtual int32			GetEPSExOmitBitmapImages() const = 0;

	/**	Get Simulate Overprint on/off.
		@return kExportLegacy (OFF) or kExportSimulatePress (ON)
	 */
	virtual int32			GetEPSExSpotOverPrint() const = 0;

	/**	Get flattener style UID to use.
		@return UID of flattener style to use
	 */
	virtual UID				GetEPSExFlattenerStyle() const = 0;

	/**	Get ignore flattener spread overrides on/off.
		@return kExportIgnoreSpreadOverridesON or kExportIgnoreSpreadOverridesOFF
	 */
	virtual int32			GetEPSExIgnoreFlattenerSpreadOverrides() const = 0;
};

#endif
