//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IEPSExportPrefsCmdData.h $
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
//  Command data for setting the EPS export preferences. Used for
//  the kSetEPSExportPrefsCmdBoss command.	
//  
//========================================================================================

#pragma once
#ifndef __IEPSExportPrefsCmdData__
#define __IEPSExportPrefsCmdData__

#include "IPMUnknown.h"
#include "IEPSExportPreferences.h"

/** Command data inteface for setting the EPS export preferences, IEPSExportPreference.
	Use the enum values defined in IEPSExportPreferences.h to set most options.
*/
class IEPSExportPrefsCmdData : public IPMUnknown
{
public:

	/**	Copy the given IEPSExportPrefences to here. This is a shortcut if you only
		want to change one setting, use this to copy the settings then just change the one.
		@param prefsToCopy IN the IEPSExportPrefences to copy
	 */
	virtual void CopyPrefs(IEPSExportPreferences* prefsToCopy) = 0;

	/**	Set which pages to export
		@param pageOption IN kExportAllPages or kExportRanges
	 */
	virtual void SetExportEPSPageOption(const int32 pageOption) = 0;

	/**	Set page range
		@param pageRange IN page range string
	 */
	virtual void SetExportEPSPageRange(const PMString& pageRange) = 0;

	/**	Set reader spread
		@param readerSpread IN kExportReaderSpreadON or kExportReaderSpreadOFF
	 */
	virtual void SetExportEPSReaderSpread(const int32 readerSpread) = 0;

	/**	Set PostScript level
		@param postScriptLevel IN kExportPSLevel2 or kExportPSLevel2WithDEFG or kExportPSLevel3
	 */
	virtual void SetExportEPSPSLevel(const int32 postScriptLevel) = 0;

	/**	Set Bleed on/off
		@param bleedOnOff IN kExportBleedON or kExportBleedOFF
	 */
	virtual void SetExportEPSBleedOnOff(const int32 bleedOnOff) = 0;

	/**	Set Bleed top value
		@param bleedAmt IN bleed top value
	 */
	virtual void SetExportEPSBleedTop(const PMReal bleedAmt) = 0;

	/**	Set Bleed bottom value
		@param bleedAmt IN bleed bottom value
	 */
	virtual void SetExportEPSBleedBottom(const PMReal bleedAmt) = 0;

	/**	Set Bleed inside (side closest to binding) value
		@param bleedAmt IN bleed inside value
	 */
	virtual void SetExportEPSBleedInside(const PMReal bleedAmt) = 0;

	/**	Set Bleed outside (side farthest from binding) value
		@param bleedAmt IN bleed outside value
	 */
	virtual void SetExportEPSBleedOutside(const PMReal bleedAmt) = 0;

	/**	Set output color space
		@param colorSpace IN kExportPSColorSpaceGray, kExportPSColorSpaceRGB, kExportPSColorSpaceCMYK, 
				kExportPSColorSpaceDIC or kExportPSColorSpaceLeaveUnchanged
	 */
	virtual void SetExportEPSColorSpace(const int32 colorSpace) = 0;

	/**	Set preview generation
		@param preview IN kExportPreviewNone or kExportPreviewTIFF or kExportPreviewPICT (Mac only)
	 */
	virtual void SetExportEPSPreview(const int32 preview) = 0;

	/**	Set output data format
		@param dataFormat IN kExportBinaryData or kExportASCIIData
	 */
	virtual void SetExportEPSDataFormat(const int32 dataFormat) = 0;

	/**	Set send image data
		@param bitmapSampling IN kExportBMSampleNormal (All) or kExportBMSampleLowRes (Proxy)
	 */
	virtual void SetExportEPSBitmapSampling(const int32 bitmapSampling) = 0;

	/**	Set include fonts
		@param includeFonts IN kExportIncludeFontsWhole (Complete) or kExportIncludeFontsSubset or kExportIncludeFontsNone
	 */
	virtual void SetExportEPSIncludeFonts(const int32 includeFonts) = 0;

	/**	Set OPI replacement on/off
		@param opiReplace IN kExportOPIReplaceON or kExportOPIReplaceOFF
	 */
	virtual void SetExportEPSOPIReplace(const int32 opiReplace) = 0;

	/**	Set all page marks on/off - not supported don't use
		@param allPageMarks IN kExportAllPageMarksON or kExportAllPageMarksOFF
	 */
	virtual void SetExportEPSAllPageMarks(const int32 allPageMarks) = 0;

	/**	Set crop marks on/off - not supported don't use
		@param cropMarks IN kExportCropMarksON or kExportCropMarksOFF
	 */
	virtual void SetExportEPSCropMarks(const int32 cropMarks) = 0;

	/**	Set bleed marks on/off - not supported don't use
		@param bleedMarks IN kExportBleedMarksON or kExportBleedMarksOFF
	 */
	virtual void SetExportEPSBleedMarks(const int32 cropMarks) = 0;

	/**	Set page info on/off - not supported don't use
		@param pageInfo IN kExportPageInfoON or kExportPageInfoOFF
	 */
	virtual void SetExportEPSPageInfo(const int32 pageInfo) = 0;

	/**	Set registration marks on/off - not supported don't use
		@param regMarks IN kExportRegMarksON or kExportRegMarksOFF
	 */
	virtual void SetExportEPSRegMarks(const int32 regMarks) = 0;

	/**	Set color bars on/off - not supported don't use
		@param colorBars IN kExportColorBarsON or kExportColorBarsOFF
	 */
	virtual void SetExportEPSColorBars(const int32 colorBars) = 0;

	/**	Set omit PDF on/off
		@param omitPDF IN kExportOmitPDFON or kExportOmitPDFOFF
	 */
	virtual void SetExportEPSOmitPDF(const int32 omitPDF) = 0;

	/**	Set omit EPS on/off
		@param omitEPS IN kExportOmitEPSON or kExportOmitEPSOFF
	 */
	virtual void SetExportEPSOmitEPS(const int32 omitEPS) = 0;

	/**	Set omit bitmap images on/off
		@param omitBitmapImages IN kExportOmitBitmapImagesON or kExportOmitBitmapImagesOFF
	 */
	virtual void SetExportEPSOmitBitmapImages(const int32 omitBitmapImages) = 0;

	/**	Set Simulate Overprint on/off
		@param spotOverPrint IN kExportLegacy (OFF) or kExportSimulatePress (ON)
	 */
	virtual void SetExportEPSSpotOverPrint(int32 spotOverPrint) = 0;

	/**	Set flattener style UID to use
		@param style IN UID of flattener style to use
	 */
	virtual void SetExportEPSFlattenerStyle(UID const &style) = 0;

	/**	Set ignore flattener spread overrides on/off
		@param ignoreOverrides IN kExportIgnoreSpreadOverridesON or kExportIgnoreSpreadOverridesOFF
	 */
	virtual void SetExportEPSIgnoreFlattenerSpreadOverrides(const int32 ignore) = 0;

	/**	Get which pages to export
		@return kExportAllPages or kExportRanges
	 */
	virtual int32			GetExportEPSPageOption(void) const = 0;

	/**	Get page range
		@return page range string
	 */
	virtual PMString		GetExportEPSPageRange(void) const = 0;

	/**	Get reader spread
		@return kExportReaderSpreadON or kExportReaderSpreadOFF
	 */
	virtual int32			GetExportEPSReaderSpread(void) const = 0;

	/**	Get PostScript level
		@return kExportPSLevel2 or kExportPSLevel2WithDEFG or kExportPSLevel3
	 */
	virtual int32			GetExportEPSPSLevel(void) const = 0;

	/**	Get Bleed on/off
		@return kExportBleedON or kExportBleedOFF
	 */
	virtual int32			GetExportEPSBleedOnOff(void) const = 0;

	/**	Get Bleed top value
		@return bleed top value
	 */
	virtual PMReal			GetExportEPSBleedTop(void) const = 0;

	/**	Get Bleed bottom value
		@return bleed bottom value
	 */
	virtual PMReal          GetExportEPSBleedBottom(void) const = 0;

	/**	Get Bleed inside (side closest to binding) value
		@return bleed inside value
	 */
	virtual PMReal          GetExportEPSBleedInside(void) const = 0;

	/**	Get Bleed outside (side farthest from binding) value
		@return bleed outside value
	 */
	virtual PMReal          GetExportEPSBleedOutside(void) const = 0;

	/**	Get output color space
		@return kExportPSColorSpaceGray, kExportPSColorSpaceRGB, kExportPSColorSpaceCMYK, 
				kExportPSColorSpaceDIC or kExportPSColorSpaceLeaveUnchanged
	 */
	virtual int32			GetExportEPSColorSpace(void) const = 0;

	/**	Get preview generation
		@return kExportPreviewNone or kExportPreviewTIFF or kExportPreviewPICT (Mac only)
	 */
	virtual int32			GetExportEPSPreview(void) const = 0;

	/**	Get output data format
		@return kExportBinaryData or kExportASCIIData
	 */
	virtual int32			GetExportEPSDataFormat(void) const = 0;

	/**	Get send image data
		@return kExportBMSampleNormal (All) or kExportBMSampleLowRes (Proxy)
	 */
	virtual int32			GetExportEPSBitmapSampling(void) const = 0;

	/**	Get include fonts
		@return kExportIncludeFontsWhole (Complete) or kExportIncludeFontsSubset or kExportIncludeFontsNone
	 */
	virtual int32			GetExportEPSIncludeFonts(void) const = 0;

	/**	Get OPI replacement on/off
		@return kExportOPIReplaceON or kExportOPIReplaceOFF
	 */
	virtual int32			GetExportEPSOPIReplace(void) const = 0;

	/**	Get all page marks on/off - not supported don't use
		@return kExportAllPageMarksON or kExportAllPageMarksOFF
	 */
	virtual int32			GetExportEPSAllPageMarks(void) const = 0;

	/**	Get crop marks on/off - not supported don't use
		@return kExportCropMarksON or kExportCropMarksOFF
	 */
	virtual int32			GetExportEPSCropMarks(void) const = 0;

	/**	Get bleed marks on/off - not supported don't use
		@return kExportBleedMarksON or kExportBleedMarksOFF
	 */
	virtual int32			GetExportEPSBleedMarks(void) const = 0;

	/**	Get page info on/off - not supported don't use
		@return kExportPageInfoON or kExportPageInfoOFF
	 */
	virtual int32			GetExportEPSPageInfo(void) const = 0;

	/**	Get registration marks on/off - not supported don't use
		@return kExportRegMarksON or kExportRegMarksOFF
	 */
	virtual int32			GetExportEPSRegMarks(void) const = 0;

	/**	Get color bars on/off - not supported don't use
		@return kExportColorBarsON or kExportColorBarsOFF
	 */
	virtual int32			GetExportEPSColorBars(void) const = 0;

	/**	Get omit PDF on/off
		@return kExportOmitPDFON or kExportOmitPDFOFF
	 */
	virtual int32			GetExportEPSOmitPDF(void) const = 0;

	/**	Get omit EPS on/off
		@return kExportOmitEPSON or kExportOmitEPSOFF
	 */
	virtual int32			GetExportEPSOmitEPS(void) const = 0;

	/**	Get omit bitmap images on/off
		@return kExportOmitBitmapImagesON or kExportOmitBitmapImagesOFF
	 */
	virtual int32			GetExportEPSOmitBitmapImages(void) const = 0;

	/**	Get Simulate Overprint on/off
		@return kExportLegacy (OFF) or kExportSimulatePress (ON)
	 */
	virtual int32			GetExportEPSSpotOverPrint(void) const = 0;

	/**	Get flattener style UID to use
		@return UID of flattener style to use
	 */
	virtual UID				GetExportEPSFlattenerStyle() const = 0;

	/**	Get ignore flattener spread overrides on/off
		@return kExportIgnoreSpreadOverridesON or kExportIgnoreSpreadOverridesOFF
	 */
	virtual int32			GetExportEPSIgnoreFlattenerSpreadOverrides() const = 0;
};


#endif
