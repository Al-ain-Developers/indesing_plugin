//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPrintData.h $
//  
//  Owner: Michael Easter
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
//  
//========================================================================================

#pragma once
#ifndef __IPrintData__
#define __IPrintData__

#include "IPMUnknown.h"

#include "IGenericSettings.h"
#include "IXferBytes.h"

#include "PMReal.h"
#include "PMRect.h"
#include "PMString.h"
#include "PrintID.h"
#include "UIDRef.h"

class IEPSExportPreferences;
class IPrintDialogData;

/**
 Interface that contains data items used to configure InDesign to print
 documents and books.  The interface supports the management of print data
 item values by provide set and get methods for all the print settings.

 In addition to a value, every print data item has two states that affect
 its behavior and appearance in the InDesign Print UI, and its behavior in
 InDesign's Print scripting.  The locked and relevant states only affect the
 way a print data item is presented to the user, and do not impose any
 restrictions on the internal workings of the print data interface.

 Locked items are assumed to have a single value that is relevant within the
 current print data context.  The value of a locked item is viewable by a
 user, but cannot be changed via direct user interaction.
 
 Non-relevant items are assumed to have no relevant value within the current
 print data context.  The value of a non-relevant item is not viewable by a
 user, and cannot be changed via direct user interaction. */
class IPrintData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPRINTDATA };

	/**
	 Identifiers that uniquely identify all print data items.  The identifiers
	 are used by IPrintData when notifying clients of item value and state
	 changes.  Clients also use the identifiers to get the current locked and
	 relevant state of a print data item. */
	enum Id {
			kInvalidId = -1,
			kDeviceTypeId = 1,
			kStyleNameId,
			kPrintToId,
			kPrinterId,
			kFileNameId,
			kPPDNameId,
			kPPDFileId,
			kPSLangLevelId,
			kResolutionId,
			kPaperSizeId,
			kImageablePaperSizeId,
			kPaperSizeSelectionId,
			kPaperSizeNameId,
			kCustomPaperWidthId,
			kDeviceCustomPaperWidthRangeId,
			kCustomPaperHeightId,
			kDeviceCustomPaperHeightRangeId,
			kCustomPaperOffsetId,
			kDeviceCustomPaperWidthOffsetRangeId,
			kCustomPaperGapId,
			kPaperOrientationId,
			kPageOrientationId,
			kProxyPageSizeId,
			kProxySpreadSizeId,
			kCopiesId,
			kCollateId,
			kReverseOrderId,
			kFlipModeId,
			kNegativeId,
			kPrintBlankPagesId,
			kPrintNonPrintingObjectsId,
			kWhichPagesId,
			kPageRangeId, 
			kPrintOptionId,
			kSpreadsId,
			kOutputModeId,
			kPrintColorsInBlackId,
			kShowSaveDialogId,
			kCompositeAngleId,
			kCompositeFrequencyId,
			kCompositeScreenTextId,
			kSeparationScreenTextId,
			kScaleModeId,
			kProportionalId,
			kXScaleId,
			kYScaleId,
			kPagePositionId,
			kPrintLayersId,
			kTileThumbModeId,
				kTileThumbModeTileId,	// Sub-identifiers needed to accommodate the way the  
				kTileThumbModeThumbId,	// TileThumbMode setting is handled in the print UI.
			kTilingModeId,
			kTilingOverlapId,
			kNumberOfThumbsPerPageId,
			kImageDataId,
			kImageDataFormatId,
			kOPIReplacementId,
			kOmitEPSId,
			kOmitPDFId,
			kOmitImagesId,
			kFontDownloadId,
			kDownloadPPDFontsId,
			kPageMarkFileId,
			kMarkLineWeightId,
			kPageMarkOffsetId,
			kCropMarksId,
			kPageInformationId,
			kColorBarsId,
			kRegistrationMarksId,
			kBleedMarksId,
			kUseDocumentBleedId,
			kBleedChainId,
			kBleedTopId,
			kBleedInsideId,
			kBleedBottomId,
			kBleedOutsideId,
			kIncludeSlugId,
			kTrappingModeId,
			kSourceSpaceId,
			kProfileTypeId,
				kPrinterProfileId,		// UI Only identifier to aid in Relevant status
				kProofProfileLabelId,	// UI Only identifier to aid in Relevant status
				kProofProfileTextId,	// UI Only identifier to aid in Relevant status
				kSimPaperColorId,		// UI Only identifier to aid in Relevant status
			kProfileNameId,
			kCRDTypeId,
			kCRDNameId,
			kIntentId,
			kPreserveColorNumbersId,
			kSpotOverPrintId,
			kPrintWYSIWYGGridsGuidesId,
			kCJKFilterContentId,
			kCJKPrintTextId,
			kCJKPrintPageItemsId,
			kCJKPrintLayoutGridsId,
			kCJKPrintFrameGridsId,
			kCJKPrintFrameGridViewId,
			kCJKOnlyPrintFrameGridWhenEmptyId,
			kCJKFrameGridStrokeWeightId,
			kCJKLayoutGridStrokeWeightId,
			kCyanPrintInkId,
			kCyanFrequencyId,
			kCyanAngleId,
			kMagentaPrintInkId,
			kMagentaFrequencyId,
			kMagentaAngleId,
			kYellowPrintInkId,
			kYellowFrequencyId,
			kYellowAngleId,
			kBlackPrintInkId,
			kBlackFrequencyId,
			kBlackAngleId,
			kSpotFrequencyId,
			kSpotAngleId,
			kFlattenerStyleUIDId,
			kFlattenerStyleNameId,
			kIgnoreSpreadOverridesId,
			kScopeId,
			kPaperSizeSelectorId,
			kBitmapPrintingId,
			kBitmapResolutionId,
			kPDFPassthroughModeId,
			kLastId
		};


	/**
	 Print data uses Notification class objects when notifying clients of item
	 value and state changes.
	 @see IPrintData
	 */
	class Notification
	{
	public:
		/**
		 Default constructor.  Member variables set to denote that all the print
		 data items changed and need to be updated. */
		Notification() : fUpdateAll(kTrue), fId(kInvalidId) {};

		/**
		 Constructor. 

		 @param updateAll	IN boolean denoting whether all print data items
							changed and need to be updated.  Pass kTrue for all
							items, and kFalse for a single item denoted by the id
							parameter.
		 @param id			IN identifier of the print data item to update.  Set to
							kInvalidId if the updateAll parameter is set to kTrue.
		 */
		Notification(bool16 updateAll, Id id) : fUpdateAll(updateAll), fId(id) {};

		/**
		 kTrue if all the print data items changed and need to be updated, else
		 kFalse. */
		bool16 fUpdateAll;

		/**
		 The print data item denoted by the given identifier changed and needs
		 to be updated.  Should be set to kInvalidId if the fUpdateAll member
		 variable is set to kTrue. */
		Id     fId;
	};


	/**
	 Valid settings for each print data item.
	*/
	enum {	// DeviceType
			kPostScriptDeviceType	= 0,
			kNonPostScriptDeviceType,
			// PrintTo
			kPrinter				= 0, 
			kVirtualPrinter,
			kPrepressFile,
			kEPSFile,
			// PSLangLevel
			kPSLangLevel_all		= 1,
			kPSLangLevel_2,
			kPSLangLevel_3,
			// PaperSizeSelection
			kPaperSizeDefinedByUser		= -1,
			kPaperSizeDefinedByDriver	= -2,
			kPaperSizeDefinedByName		= -3,
			// Custom Paper Size
			kCustomPaperSizeAuto		= -1,
			// PaperOrientation
			kNormal					= 0, 
			kTransverse,
			// PageOrientation
			kPortrait				= 0, 
			kLandscape,						// Counterclockwise 90 degrees
			kReversePortrait,				// Counterclockwise 180 degrees
			kReverseLandscape,				// Counterclockwise 270 degrees
			// FlipMode
			kFlipOff				= 0,
			kFlipHorizontal,
			kFlipVertical,
			kFlipBoth,
			// WhichPages
			kAllPages				= 0, 
			kPageRange,
			kCurrentPage,
			// PrintOption
			kBothPages				= 0, 
			kEvenPagesOnly,
			kOddPagesOnly,
			// OutputMode
			kCompositeGray			= 0, 
			kCompositeRGB, 
			kCompositeCMYK, 
			kSeparationBuiltIn,
			kSeparationInRIP,
			kCompositeLeaveUnchanged,
			// ScaleMode
			kScaleToFit				= 0, 
			kScaleXAndY,
			// Page Position
			kPagePositionUpperLeft	= 0, 
			kPagePositionCenterHorizontally,
			kPagePositionCenterVertically,
			kPagePositionCentered,
			// Print Layers
			kPrintAllLayers			= 0, 
			kPrintVisibleLayers,
			kPrintVisiblePrintableLayers,
			// TileThumbMode
			kTileThumbOff			= 0,
			kTiling,
			kThumbnails,
			// TilingMode
			kTilingAutomatic		= 0,
			kTilingManual,
			kTilingAutoJustified,
			// ImageData
			kImageDataAll			= 0, 
			kImageDataOptimized,
			kImageDataLoRez,
			kImageDataProofPrint,
			// ImageDataFormat
			kImageDataBinary		= 0, 
			kImageDataASCII,
			// FontDownload
			kFontDownloadNone		= 0, 
			kFontDownloadComplete,
			kFontDownloadSubset,
			kFontDownloadSubsetLrg,
			// TrappingMode
			kTrappingNone			= 0, 
			kTrappingBuiltIn,
			kTrappingInRIP,
			// SourceSpace
			kDocumentSourceSpace	= 0,
			kProofSourceSpace,
			// Intent
			kPerceptual				= 0,
			kSaturation,
			kRelativeColorimetric,
			kAbsoluteColorimetric,
			// SpotOverPrint
			kLegacy					= 0,
			kSimulatePress,
			kSimulateScreen,
			// ProfileType
			kUsePostScriptCMS		= 0,
			kUseDocumentProfile,
			kUseWorkingProfile,
			kUseSpecificProfile,
			kUseNoCMS,
			// CRDType
			kUseNoCRD				= 0,
			kUseDocumentCRD,
			kUseWorkingCRD,
			kUseSpecificCRD,
			// Scope
			kScopeDocument			= 0,
			kScopeMaster,
			// MarkLineWeight
			kMarkLineWeight125pt	= 0,
			kMarkLineWeight25pt,
			kMarkLineWeight50pt,
			kMarkLineWeight05mm,
			kMarkLineWeight07mm,
			kMarkLineWeight10mm,
			kMarkLineWeight15mm,
			kMarkLineWeight20mm,
			kMarkLineWeight30mm,
			// Bitmap Printing Resolution
			kBitmapResolution_72	= 0,
			kBitmapResolution_150,
			kBitmapResolution_300,
			kBitmapResolution_600,
			kBitmapResolutionMinimum	= 72,
			kBitmapResolutionMaximum	= 1200,
			kBitmapResolutionDefault_R	= 300,
			kBitmapResolutionDefault_J	= 600,
			
			kDontCare				= ((int32)-32767) 
		};


	// Copy/Initialization methods
	/**
	 Copy all settings from another PrintData to this one.

	 @param copyFromPD			IN denotes the PrintData to copy from
	 @param bCopyPrintRecord	IN whether to copy the PrintRecord data as well. Defaults
								to kFalse, pass kTrue to copy the PrintRecord data.
	 */
	virtual void CopyData(IPrintData* copyFromPD, bool16 bCopyPrintRecord = kFalse) = 0;
	/**
	 Verify that the Printer Style name that is saved in this PrintData (in GetStyleName)
	 is indeed a valid Printer Style and that all the settings are the same as this PrintData.
	 If the PrinterStyle does not exist, is not valid, or does not verify, VerifyStyle will put 
	 an empty string into SetStyleName for this PrintData. There are some fields that are not
	 compared. They are: GetFileName, GetPPDFile, GetDeviceCustomPaperWidthRange, GetDeviceCustomPaperHeightRange,
	 GetDeviceCustomPaperWidthOffsetRange, GetWhichPages, and GetPageRange.

	 @return kTrue if the style verifies, kFalse if it is different
	 */
	virtual bool16 VerifyStyle() = 0;	// returns kTrue is style verified OK
	/**
	 Initialize this PrintData using the settings from IEPSExportPreferences.

 	 @param iEPSExPreferences	IN pointer to IEPSExportPreferences from which to get the settings.
	 @see IEPSExportPreferences
	*/
	virtual void InitializeForEPS(IEPSExportPreferences *iEPSExPreferences) = 0;

	// Print data helper interaction methods
	/**
	 Normalizes print data items that aren't relevant and thus may contain values
	 that can cause processing errors during the printing process. */
	virtual void Normalize() = 0;

	/**
	 Validates print data and updates item values necessary to a ensure a consistent
	 and valid context.  Optionally updates the locked and relevant states of print
	 data items.
	 Differs from Normalize() by only updating items that are necessary for the
	 Print UI to function properly.  Most non-relevant items are not changed.

	 @param updateStates	IN denotes whether to update the states of the print
							data items.  Pass kTrue to update states, else kFalse.
	 */
	virtual void Validate(bool16 updateStates = kTrue) = 0;

	/**
	 Verifies whether the print data is in a consistent and valid context.

	 @return kTrue print data is in a valid context, else kFalse
	 */
	virtual bool16 Verify() = 0;

	/**
	 Returns a boolean value denoting whether the print data item identified by
	 the given identifier is currently in a locked state.  Locked print data
	 items cannot be changed by the user, but are visible to the user.

	 @param id	IN identifier of the print data item
	 @return kTrue if the item is locked, else kFalse
	 */
	virtual bool16 IsLocked(Id id) const = 0;

	/**
	 Returns a boolean value denoting whether the print data item identified by
	 the given identifier is in a relevant state.  Print data items that are
	 not relevant cannot be changed by the user, and are not visible to the user.

	 @param id	IN identifier of the print data item
	 @return kTrue if the item is relevant, else kFalse
	 */
	virtual bool16 IsRelevant(Id id) const = 0;

	/**
	 Suppresses validation and notification of print data value and state changes. 
	 Used when several print data items need to be updated simultaneously and
	 the print data may temporarily be in an invalid context. For example, when
	 changing printers. */
	virtual void BeginUnvalidatedUpdate() const = 0;

	/**
	 Stops suppressing the validation and notification of print data value and
	 state changes.

	 @param notify			IN denotes whether to notify print data clients with an
							"update all" notification.  Pass kTrue to notify, else
							kFalse.
	 @param updateStates	IN denotes whether to update the states of the print
							data items.  Pass kTrue to update states, else kFalse.
	 */
	virtual void EndUnvalidatedUpdate(bool16 notify = kTrue, bool16 updateStates = kTrue) = 0;

	/**
	 Notifys print data clients that all or a specific print data item experienced
	 a change in value or state. 

	 @param notification	IN notification class object denoting which print
							data items changed and need to be updated. 
	 */
	virtual void Notify(Notification& notification) const = 0;

	// Print Record methods
	/** Create a new print record stream - an opaque stream
		@return pointer to IXferBytes of the print record stream
	*/
	virtual IXferBytes* CreatePrintRecordStream(void) = 0;
	/** Gets the print record stream - an opaque stream
		@return pointer to IXferBytes of the print record stream, or nil if there
		isn't one
	*/
	virtual IXferBytes* GetPrintRecordStream(void) = 0;
	/** Delete the print record stream
	*/
	virtual void DeletePrintRecordStream(void) = 0;

	// Set methods
	/**	Set the device type
		@param deviceType	IN one of kPostScriptDeviceType, kNonPostScriptDeviceType
	*/
	virtual void SetDeviceType(const int32 deviceType) = 0;
	/**	Set the Printer Style Name
		@param styleName	IN PMString reference to the name of the style
	*/
	virtual void SetStyleName(const PMString& styleName) = 0;
	/**	Set where we are printing to
		@param printTo	IN one of kPrinter (direct to printer), kVirtualPrinter (PostScript
		file with PPD selected), kPrepressFile (PostScript file Device Independent), kEPSFile (EPS file)
	*/
	virtual void SetPrintTo(const int32 printTo) = 0;
	/**	Set the name of the printer we are printing to
		@param printer	IN PMString reference to the name of the printer, "kPrepress File" if printing
		to a PostScript file.
	*/
	virtual void SetPrinter(const PMString& printer) = 0;
	/**	Set the name and path of the file we are printing to
		@param fileName	IN PMString reference to the full path name of the file we are printing to.
	*/
	virtual void SetFileName(const PMString& fileName) = 0;
	/**	Set the model name of the PPD we are using
		@param ppdName	IN PMString reference to the model name of the PPD in use. Can be 
		"kDevice Independent" for Device Independent PostScript file.
	*/
	virtual void SetPPDName(const PMString& ppdName) = 0;
	/**	Set the path and file name of the PPD we are using
		@param ppdFile	IN PMString reference to the full path and file name of the PPD file.
	*/
	virtual void SetPPDFile(const PMString& ppdName) = 0;
	/**	Set the PostScript language level we will generate
		@param psLangLevel	IN one of kPSLangLevel_2, kPSLangLevel_3. Note: kPSLangLevel_all
		is not support any longer.
	*/
	virtual void SetPSLangLevel(const int32 psLangLevel) = 0;
	/**	Set the output resolution
		@param resolution	IN PMReal reference to the output resolution
	*/
	virtual void SetResolution(const PMReal& resolution) = 0;
	/**	Set the paper size
		@param paperSize	IN PMRect reference to the paper size
		@see IPrintDeviceInfo GetPaperSize
	*/
	virtual void SetPaperSize(const PMRect& paperSize) = 0;
	/**	Set the imageable paper size - the imageable area for the paper
		@param imageablePaperSize	IN PMRect reference to the paper's imageable area size
		@see IPrintDeviceInfo GetImageablePaperSize
	*/
	virtual void SetImageablePaperSize(const PMRect& imageablePaperSize) = 0;
	/**	Set the paper size selection.
		@param paperSizeSelection	IN one of kPaperSizeDefinedByUser (Custom paper size), 
		kPaperSizeDefinedByDriver (Defined by Driver), kPaperSizeDefinedByName (see SetPaperSizeName)
	*/
	virtual void SetPaperSizeSelection(const int32 paperSizeSelection) = 0;
	/**	Set the paper size name. This is only applicable if paper size selection is kPaperSizeDefinedByName
		@param paperSizeName	IN PMString reference to the paper size name, as defined in the PPD
		@see IPrintDeviceInfo GetPaperSizeName
	*/
	virtual void SetPaperSizeName(const PMString& paperSizeName) = 0;
	/**	Set the custom paper size width. This is only applicable if the paper size selection is kPaperSizeDefinedByUser
		@param customPaperWidth	IN PMReal reference to the custom paper size width. This can be kCustomPaperSizeAuto.
	*/
	virtual void SetCustomPaperWidth(const PMReal& customPaperWidth) = 0;
	/**	Set the custom paper size width range. This is only applicable if the paper size selection is kPaperSizeDefinedByUser
		@param minWidth	IN PMReal reference to the minimum value for the custom paper size width.
		@param maxWidth	IN PMReal reference to the maximum value for the custom paper size width.
	*/
	virtual void SetDeviceCustomPaperWidthRange(const PMReal& minWidth, const PMReal& maxWidth) = 0;
	/**	Set the custom paper size height. This is only applicable if the paper size selection is kPaperSizeDefinedByUser
		@param customPaperHeight	IN PMReal reference to the custom paper size height. This can be kCustomPaperSizeAuto.
	*/
	virtual void SetCustomPaperHeight(const PMReal& customPaperHeight) = 0;
	/**	Set the custom paper size height range. This is only applicable if the paper size selection is kPaperSizeDefinedByUser
		@param minHeight	IN PMReal reference to the minimum value for the custom paper size height.
		@param maxHeight	IN PMReal reference to the maximum value for the custom paper size height.
	*/
	virtual void SetDeviceCustomPaperHeightRange(const PMReal& minHeight, const PMReal& maxHeight) = 0;
	/**	Set the custom paper size offset amount. This is only applicable if the paper size selection is kPaperSizeDefinedByUser
		@param customPaperOffset	IN PMReal reference to the custom paper size offset.
	*/
	virtual void SetCustomPaperOffset(const PMReal& customPaperOffset) = 0;
	/**	Set the custom paper size offset range. This is only applicable if the paper size selection is kPaperSizeDefinedByUser
		@param nOffsetMin	IN PMReal reference to the minimum value for the custom paper size offset.
		@param nOffsetMax	IN PMReal reference to the maximum value for the custom paper size offset.
	*/
	virtual void SetDeviceCustomPaperWidthOffsetRange(const PMReal &nOffsetMin, const PMReal &nOffsetMax) = 0;
	/**	Set the custom paper size gap amount. This is only applicable if the paper size selection is kPaperSizeDefinedByUser
		@param customPaperGap	IN PMReal reference to the custom paper size gap.
	*/
	virtual void SetCustomPaperGap(const PMReal& customPaperGap) = 0;
	/**	Set the paper orientation
		@param paperOrientation	IN one of kNormal, kTransverse
	*/
	virtual void SetPaperOrientation(const int32 paperOrientation) = 0;
	/**	Set the page orientation
		@param pageOrientation	IN one of kPortrait, kLandscape (Counterclockwise 90 degrees), 
		kReversePortrait (180 degrees), kReverseLandscape (Counterclockwise 270 degrees)
	*/
	virtual void SetPageOrientation(const int32 pageOrientation) = 0;
	/**	Set the proxy page size - used in drawing the proxy page preview (only used in the UI)
		@param proxyPageWidth	IN uint32 of the proxy page width
		@param proxyPageHeight	IN uint32 of the proxy page height
	*/
	virtual void SetProxyPageSize(const uint32 proxyPageWidth, const uint32 proxyPageHeight) = 0;
	/**	Set the proxy spread size - used in drawing the proxy preview when spreads is on (only used in the UI)
		@param proxySpreadWidth		IN uint32 of the proxy spread width
		@param proxySpreadHeight	IN uint32 of the proxy spread height
	*/
	virtual void SetProxySpreadSize(const uint32 proxySpreadWidth, const uint32 proxySpreadHeight) = 0;
	/**	Set the number of copies
		@param copies	IN number of copies
	*/
	virtual void SetCopies(const int32 copies) = 0;
	/**	Set to collate or not
		@param collate	IN kTrue to collate, kFalse otherwise
	*/
	virtual void SetCollate(const bool16 collate) = 0;
	/**	Set to reverse order or not
		@param reverseOrder	IN kTrue to reverse order, kFalse otherwise
	*/
	virtual void SetReverseOrder(const bool16 reverseOrder) = 0;
	/**	Set the flip mode
		@param flipMode	IN one of kFlipOff, kFlipHorizontal, kFlipVertical, kFlipBoth
	*/
	virtual void SetFlipMode(const int32 flipMode) = 0;
	/**	Set to print page as negative or not
		@param negative	IN kTrue to print as negative, kFalse otherwise
	*/
	virtual void SetNegative(const bool16 negative) = 0;
	/**	Set to print blank pages or not
		@param printBlankPages	IN kTrue to print blank pages, kFalse otherwise
	*/
	virtual void SetPrintBlankPages(const bool16 printBlankPages) = 0;
	/**	Set to print non printing objects or not
		@param printNonPrintingObjects	IN kTrue to override page item non-printing attribute, kFalse otherwise
	*/
	virtual void SetPrintNonPrintingObjects(const bool16 printNonPrintingObjects) = 0;
	/**	Set which pages to print, all pages or page range
		@param whichPages	IN one of kAllPages, kPageRange
	*/
	virtual void SetWhichPages(const int32 whichPages) = 0;
	/**	Set the page range to print
		@param pageRange	IN PMString reference to page range string.
		@see IPageList PageRangeStringToUIDList regarding valid page range strings
	*/
	virtual void SetPageRange(const PMString& pageRange) = 0; 
	/**	Set which pages to print, both odd and even, odd only or even only
		@param printOption	IN one of kBothPages, kEvenPagesOnly, kOddPagesOnly
	*/
	virtual void SetPrintOption(const int32 printOption) = 0;
	/**	Set to print spreads or not
		@param spreads	IN kTrue to print spreads, kFalse otherwise
	*/
	virtual void SetSpreads(const bool16 spreads) = 0;
	/**	Set the color output mode
		@param outputMode	IN one of kCompositeGray, kCompositeRGB, kCompositeCMYK,
		kSeparationBuiltIn, kSeparationInRIP, kCompositeLeaveUnchanged
	*/
	virtual void SetOutputMode(const int32 outputMode) = 0;
	/**	Set to print text as black or not
		@param printColorsInBlack	IN kTrue to print text as black, kFalse otherwise
	*/
	virtual void SetPrintColorsInBlack(const bool16 printColorsInBlack) = 0;
	/**	Set to show the file save dialog or not
		@param showSaveDialog	IN kTrue to show the file save dialog, kFalse otherwise
	*/
	virtual void SetShowSaveDialog(const bool16 showSaveDialog) = 0;
	/**	Set the composite angle amount
		@param compositeAngle	IN PMReal reference to the composite angle value.
		@see IPrintDeviceInfo GetDeviceCompositeAngle
	*/
	virtual void SetCompositeAngle(const PMReal &compositeAngle) = 0;
	/**	Set the composite frequency amount
		@param compositeFrequency	IN PMReal reference to the composite frequency value.
		@see IPrintDeviceInfo GetDeviceCompositeFrequency
	*/
	virtual void SetCompositeFrequency(const PMReal &compositeFrequency) = 0;
	/**	Set the composite screening text
		@param compositeScreenStr	IN PMString reference to the composite screening text.
		This can be "kDefault" or "kCustom" if kCompositeGray is color output mode
	*/
	virtual void SetCompositeScreenText(const PMString& compositeScreenStr) = 0;
	/**	Set the separation screening text
		@param sepScreenStr	IN PMString reference to the separation screening text.
		This is a string from the PPD.
		@see IPrintDeviceInfo GetNthSeparationFrequency and GetDefaultSeparationFrequencyIndex
	*/
	virtual void SetSeparationScreenText(const PMString& sepScreenStr) = 0;
	/**	Set the scaling mode, either scale to fit, or scale by X and Y
		@param scaleMode	IN one of kScaleToFit, kScaleXAndY
	*/
	virtual void SetScaleMode(const int32 scaleMode) = 0;
	/**	Set if to scale proportionally or not
		@param proportional	IN kTrue to contrain proportions, kFalse otherwise
	*/
	virtual void SetProportional(const bool16 proportional) = 0;
	/**	Set the X scale amount - only applicable if scale mode is kScaleXAndY
		@param xScale	IN PMReal reference to the X scale value.
	*/
	virtual void SetXScale(const PMReal& xScale) = 0;
	/**	Set the Y scale amount - only applicable if scale mode is kScaleXAndY
		@param yScale	IN PMReal reference to the Y scale value.
	*/
	virtual void SetYScale(const PMReal& yScale) = 0;
	/**	Set the page positioning on the paper
		@param pagePosition	IN one of kPagePositionUpperLeft, kPagePositionCenterHorizontally,
		kPagePositionCenterVertically, kPagePositionCentered
	*/
	virtual void SetPagePosition(const int32 pagePosition) = 0;
	/**	Set which layers will print
		@param printLayers	IN one of kPrintAllLayers, kPrintVisibleLayers, kPrintVisiblePrintableLayers
	*/
	virtual void SetPrintLayers(const int32 printLayers) = 0;
	/**	Set the tiling and thumbnail mode
		@param tileThumbMode	IN one of kTileThumbOff, kTiling, kThumbnails
	*/
	virtual void SetTileThumbMode(const int32 tileThumbMode) = 0;
	/**	Set the tiling mode - only applicable if tile thumb mode is kTiling
		@param tilingMode	IN one of kTilingAutomatic, kTilingManual, kTilingAutoJustified
	*/
	virtual void SetTilingMode(const int32 tilingMode) = 0;
	/**	Set the tiling overlap amount - only applicable if tile thumb mode is kTiling
		@param tilingOverlap	IN PMReal reference to the tiling overlap value.
	*/
	virtual void SetTilingOverlap(const PMReal& tilingOverlap) = 0;
	/**	Set the number of thumbnails per page - only applicable if tile thumb mode is kThumbnails
		@param numberOfThumbsPerPage	IN the number of thumbnails on a page. Should be 
		2, 4, 9, 16, 25, 36 or 49
	*/
	virtual void SetNumberOfThumbsPerPage(const int32 numberOfThumbsPerPage) = 0;
	/**	Set how the image data will be printed
		@param imageData	IN one of kImageDataAll, kImageDataOptimized, kImageDataLoRez, kImageDataProofPrint 
	*/
	virtual void SetImageData(const int32 imageData) = 0;
	/**	Set how the image data will be formatted
		@param imageDataFormat	IN one of kImageDataBinary, kImageDataASCII
	*/
	virtual void SetImageDataFormat(const int32 imageDataFormat) = 0;
	/**	Set to print as bitmap or not. Bitmap printing required on Mac OSX < 10.3.
		@param bitmapPrinting	IN kTrue if printing using bitmap, kFalse otherwise
	*/
	virtual void SetBitmapPrinting(const bool16 bitmapPrinting) = 0;
	/**	Set the bitmap printing resolution
		@param bitmapResolution	IN either an IPrintData enum kBitmapResolution_72, 
					kBitmapResolution_150, etc. or a resolution >= 72 and <= 1200.
	*/
	virtual void SetBitmapResolution(const int32 bitmapResolution) = 0;
	/**	Set to perform OPI replacement or not
		@param opiReplacement	IN kTrue if OPI replacement, kFalse otherwise
	*/
	virtual void SetOPIReplacement(const bool16 opiReplacement) = 0;
	/**	Set to omit EPS data from output stream or not
		@param omitEPS	IN kTrue if omitting EPS data, kFalse otherwise
	*/
	virtual void SetOmitEPS(const bool16 omitEPS) = 0;
	/**	Set to omit PDF data from output stream or not
		@param omitPDF	IN kTrue if omitting PDF data, kFalse otherwise
	*/
	virtual void SetOmitPDF(const bool16 omitPDF) = 0;
	/**	Set to omit bitmap data from output stream or not - not valid if doing
		OPI replacement
		@param omitImages	IN kTrue if omitting images, kFalse otherwise
	*/
	virtual void SetOmitImages(const bool16 omitImages) = 0;
	/**	Set the font download mode
		@param fontDownload	IN one of kFontDownloadNone, kFontDownloadComplete,
		kFontDownloadSubset, kFontDownloadSubsetLrg (deprecated)
	*/
	virtual void SetFontDownload(const int32 fontDownload) = 0;
	/**	Set to download PPD fonts or not 
		@param downloadPPDFonts	IN kTrue if downloading PPD fonts, kFalse otherwise
	*/
	virtual void SetDownloadPPDFonts(const bool16 downloadPPDFonts) = 0;
	/**	Set the page mark file to use
		@param tilingOverlap	IN PMString reference to the page mark file. Can be
		empty string for Default
	*/
	virtual void SetPageMarkFile(const PMString& pageMarkFile) = 0;
	/**	Set the page mark line weight 
		@param markLineWeight	IN one of kMarkLineWeight125pt, kMarkLineWeight25pt,
		kMarkLineWeight50pt, OR if Japanese, kMarkLineWeight05mm, kMarkLineWeight07mm,
		kMarkLineWeight10mm, kMarkLineWeight15mm, kMarkLineWeight20mm, kMarkLineWeight30mm
	*/
	virtual void SetMarkLineWeight(const int32 markLineWeight) = 0;
	/**	Set the page mark offset amount
		@param pageMarkOffset	IN PMReal reference to the page mark offset value.
	*/
	virtual void SetPageMarkOffset(const PMReal& pageMarkOffset) = 0;
	/**	Set to print crop marks or not 
		@param cropMarks	IN kTrue if printing crop marks, kFalse otherwise
	*/
	virtual void SetCropMarks(const bool16 cropMarks) = 0;
	/**	Set to print page information or not 
		@param pageInformation	IN kTrue if printing page information, kFalse otherwise
	*/
	virtual void SetPageInformation(const bool16 pageInformation) = 0;
	/**	Set to print color bars or not 
		@param colorBars	IN kTrue if printing color bars, kFalse otherwise
	*/
	virtual void SetColorBars(const bool16 colorBars) = 0;
	/**	Set to print registration marks or not 
		@param registrationMarks	IN kTrue if printing registration marks, kFalse otherwise
	*/
	virtual void SetRegistrationMarks(const bool16 registrationMarks) = 0;
	/**	Set to print bleed marks or not 
		@param bleedMarks	IN kTrue if printing bleed marks, kFalse otherwise
	*/
	virtual void SetBleedMarks(const bool16 bleedMarks) = 0;
	/**	Set to use the document bleed amount or not 
		@param useDocumentBleed	IN kTrue if using the document bleed values, kFalse otherwise
	*/
	virtual void SetUseDocumentBleed(const bool16 useDocumentBleed) = 0;
	/**	Set the bleed value for the top edge
		@param bleedTop	IN PMReal reference to the top bleed value.
	*/
	virtual void SetBleedTop(const PMReal& bleedTop) = 0;
	/**	Set if the bleed values are chained together or not
		@param bleedChain	IN kTrue if the bleed values are chained, kFalse otherwise
	*/
	virtual void SetBleedChain(const bool16 bleedChain) = 0;
	/**	Set the bleed value for the inside edge - that is the edge closest to the 
		binding for facing pages. This is the left side if printing spreads, or if
		there is not facing pages.
		@param bleedInside	IN PMReal reference to the inside bleed value.
	*/
	virtual void SetBleedInside(const PMReal& bleedInside) = 0;
	/**	Set the bleed value for the bottom edge
		@param bleedBottom	IN PMReal reference to the bottom bleed value.
	*/
	virtual void SetBleedBottom(const PMReal& bleedBottom) = 0;
	/**	Set the bleed value for the outside edge - that is the edge farthest from the 
		binding for facing pages. This is the right side if printing spreads, or if
		there is not facing pages.
		@param bleedOutside	IN PMReal reference to the outside bleed value.
	*/
	virtual void SetBleedOutside(const PMReal& bleedOutside) = 0;
	/**	Set if the slug area is included or not
		@param includeSlug	IN kTrue if the slug area is included, kFalse otherwise
	*/
	virtual void SetIncludeSlug(const bool16 includeSlug) = 0;
	/**	Set the trapping mode
		@param trappingMode	IN one of kTrappingNone, kTrappingBuiltIn, kTrappingInRIP
	*/
	virtual void SetTrappingMode(const int32 trappingMode) = 0;
	/**	Set the source space for color management
		@param sourceSpace	IN one of kDocumentSourceSpace, kProofSourceSpace
	*/
	virtual void SetSourceSpace(const int32 sourceSpace) = 0;
	/**	Set the profile type for color management
		@param profileType	IN one of kUsePostScriptCMS, kUseDocumentProfile,
		kUseWorkingProfile, kUseSpecificProfile, kUseNoCMS
	*/
	virtual void SetProfileType(const int32 profileType) = 0;
	/**	Set the profile name for color management - only applicable if profile 
		type is kUseSpecificProfile
		@param profileType	IN PMString reference to the name of the profile
	*/
	virtual void SetProfileName(const PMString &profileName) = 0;
	/**	Set the CRD type for color management
		@param crdType	IN one of kUseNoCRD, kUseDocumentCRD,
		kUseWorkingCRD, kUseSpecificCRD
	*/
	virtual void SetCRDType(const int32 crdType) = 0;
	/**	Set the CRD name for color management - only applicable if CRD 
		type is kUseSpecificCRD
		@param crdName	IN PMString reference to the name of the CRD
	*/
	virtual void SetCRDName(const PMString &crdName) = 0;
	/**	Set intent type for color management
		@param intent	IN one of kPerceptual, kSaturation,
		kRelativeColorimetric, kAbsoluteColorimetric
	*/
	virtual void SetIntent(const int32 intent) = 0;
	/**	Set the Simulate Overprint type. 
		@param spotOverPrint	IN one of kLegacy (SimOP off), kSimulatePress (SimOP on),
		kSimulateScreen (deprecated)
	*/
	virtual void SetSpotOverPrint(int32 spotOverPrint) = 0;
	/**	Set whether to print visible guides and baseline grids or not
		@param printWYSIWYGGridsGuides	IN kTrue if printing guides and grids, kFalse otherwise
	*/
	virtual void SetPrintWYSIWYGGridsGuides(bool16 printWYSIWYGGridsGuides) = 0;
	/**	Set whether to filter port contents or not - CJK specific
		@param filter	IN kTrue if filtering, kFalse otherwise
		@see IPrintContentPrefs
	*/
	virtual void SetCJKFilterContent(bool16 filter) = 0;
	/**	Set whether to print text or not - CJK specific
		@param printText	IN kTrue if printing text, kFalse otherwise
		@see IPrintContentPrefs
	*/
	virtual void SetCJKPrintText(bool16 printText) = 0;
	/**	Set whether to print page items or not - CJK specific
		@param printPageItems	IN kTrue if printing page items, kFalse otherwise
		@see IPrintContentPrefs
	*/
	virtual void SetCJKPrintPageItems(bool16 printPageItems) = 0;
	/**	Set whether to print layout grids or not - CJK specific
		@param printLayoutGrids	IN kTrue if printing layout grids, kFalse otherwise
		@see IPrintContentPrefs
	*/
	virtual void SetCJKPrintLayoutGrids(bool16 printLayoutGrids) = 0;
	/**	Set whether to print frame grids or not - CJK specific
		@param printFrameGrids	IN kTrue if printing frame grids, kFalse otherwise
		@see IPrintContentPrefs
	*/
	virtual void SetCJKPrintFrameGrids(bool16 printFrameGrids) = 0;
	/**	Set the print frame grid view - CJK specific
		@param viewNumber	IN frame grid view
		@see IPrintContentPrefs GridView
	*/
	virtual void SetCJKPrintFrameGridView(int32 viewNumber) = 0;
	/**	Set whether to print frame grid when empty or not - CJK specific
		@param whenEmpty	IN kTrue if printing frame grid when empty, kFalse otherwise
		@see IPrintContentPrefs 
	*/
	virtual void SetCJKOnlyPrintFrameGridWhenEmpty(bool16 whenEmpty) = 0;
	/**	Set the frame grid stroke weight - CJK specific
		@param points	IN PMReal reference to the frame grid stroke weight
		@see IPrintContentPrefs 
	*/
	virtual void SetCJKFrameGridStrokeWeight( const PMReal & points ) = 0;
	/**	Set the layout grid stroke weight - CJK specific
		@param points	IN PMReal reference to the layout grid stroke weight
		@see IPrintContentPrefs 
	*/
	virtual void SetCJKLayoutGridStrokeWeight( const PMReal & points ) = 0;
	/**	Set whether to print the Cyan ink or not
		@param cyanPrintInk	IN kTrue if printing the Cyan ink, kFalse otherwise
	*/
	virtual void SetCyanPrintInk(bool16 cyanPrintInk) = 0;
	/**	Set the Cyan ink frequency value
		@param cyanFrequency	IN PMReal reference to the Cyan ink frequency value
	*/
	virtual void SetCyanFrequency(const PMReal &cyanFrequency) = 0;
	/**	Set the Cyan ink angle value
		@param cyanAngle	IN PMReal reference to the Cyan ink angle value
	*/
	virtual void SetCyanAngle(const PMReal &cyanAngle) = 0;
	/**	Set whether to print the Magenta ink or not
		@param magentaPrintInk	IN kTrue if printing the Magenta ink, kFalse otherwise
	*/
	virtual void SetMagentaPrintInk(bool16 magentaPrintInk) = 0;
	/**	Set the Magenta ink frequency value
		@param magentaFrequency	IN PMReal reference to the Magenta ink frequency value
	*/
	virtual void SetMagentaFrequency(const PMReal &magentaFrequency) = 0;
	/**	Set the Magenta ink angle value
		@param magentaAngle	IN PMReal reference to the Magenta ink angle value
	*/
	virtual void SetMagentaAngle(const PMReal &magentaAngle) = 0;
	/**	Set whether to print the Yellow ink or not
		@param yellowPrintInk	IN kTrue if printing the Yellow ink, kFalse otherwise
	*/
	virtual void SetYellowPrintInk(bool16 yellowPrintInk) = 0;
	/**	Set the Yellow ink frequency value
		@param yellowFrequency	IN PMReal reference to the Yellow ink frequency value
	*/
	virtual void SetYellowFrequency(const PMReal &yellowFrequency) = 0;
	/**	Set the Yellow ink angle value
		@param yellowAngle	IN PMReal reference to the Yellow ink angle value
	*/
	virtual void SetYellowAngle(const PMReal &yellowAngle) = 0;
	/**	Set whether to print the Black ink or not
		@param blackPrintInk	IN kTrue if printing the Black ink, kFalse otherwise
	*/
	virtual void SetBlackPrintInk(bool16 blackPrintInk) = 0;
	/**	Set the Black ink frequency value
		@param blackFrequency	IN PMReal reference to the Black ink frequency value
	*/
	virtual void SetBlackFrequency(const PMReal &blackFrequency) = 0;
	/**	Set the Black ink angle value
		@param blackAngle	IN PMReal reference to the Black ink angle value
	*/
	virtual void SetBlackAngle(const PMReal &blackAngle) = 0;
	/**	Set the spot ink frequency value
		@param spotFrequency	IN PMReal reference to the spot ink frequency value
	*/
	virtual void SetSpotFrequency(const PMReal &spotFrequency) = 0;
	/**	Set the spot ink angle value
		@param spotAngle	IN PMReal reference to the spot ink angle value
	*/
	virtual void SetSpotAngle(const PMReal &spotAngle) = 0;
	/**	Set the name of the flattener style to use
		@param spstrNameotAngle	IN PMString reference to the name of the flattener style
	*/
	virtual void SetFlattenerStyleName(const PMString& strName) = 0;
	/**	Set whether to ignore flattener spread overrides or not
		@param ignoreSpreadOverrides	IN kTrue to ignore spread overrides, kFalse otherwise
	*/
	virtual void SetIgnoreSpreadOverrides(bool16 ignoreSpreadOverrides) = 0;
	/**	Set the scope of pages to print - either the document or Master pages
		@param scope	IN one of kScopeDocument, kScopeMaster
	*/
	virtual void SetScope(const int32 scope) = 0;
	/**	Set the paper size selector data - a magic cookie to select paper sizes
		@param inData	IN opaque data bytes
		@param inSize	IN size of data in inData
		@see IPrintDeviceInfo GetPaperSizeSelector
	*/
	virtual void SetPaperSizeSelector(uchar* inData, uint32 inSize) = 0;
	/**	Set whether to preserve the CMYK/RGB color numbers or not
		@param preserveColorNumbers	IN kTrue if preserving color numbers, kFalse otherwise
	*/
	virtual void SetPreserveColorNumbers(bool16 preserveColorNumbers) = 0;

	// Get methods
	/** Determines if any field values have been modified from their original (default) values.
		@return kTrue - fields modified, kFalse otherwise
	*/
	virtual bool16 GetIsDefaultValues() const = 0;
	/**	Get the device type
		@return one of kPostScriptDeviceType, kNonPostScriptDeviceType
	*/
	virtual int32 GetDeviceType() const = 0;
	/**	Get the Printer Style Name - will be "kPrSt_DefaultName" if default
		@return PMString of the name of the style
	*/
	virtual PMString GetStyleName() const = 0;
	/**	Get where we are printing to
		@return one of kPrinter (direct to printer), kVirtualPrinter (PostScript file with PPD selected), 
		kPrepressFile (PostScript file Device Independent), kEPSFile (EPS file)
	*/
	virtual int32 GetPrintTo() const = 0;
	/**	Get the name of the printer we are printing to
		@return PMString of the name of the printer, "kPrepress File" if printing
		to a PostScript file.
	*/
	virtual PMString GetPrinter() const = 0;
	/**	Get the name and path of the file we are printing to
		@return PMString of the full path name of the file we are printing to.
	*/
	virtual PMString GetFileName() const = 0;
	/**	Get the model name of the PPD we are using
		@return PMString of the model name of the PPD in use. Will be 
		"kDevice Independent" for Device Independent PostScript file.
	*/
	virtual PMString GetPPDName() const = 0;
	/**	Get the path and file name of the PPD we are using
		@return PMString of the full path and file name of the PPD file.
	*/
	virtual PMString GetPPDFile() const = 0;
	/**	Get the PostScript language level we will generate
		@return one of kPSLangLevel_2, kPSLangLevel_3. Note: kPSLangLevel_all
		is not support any longer.
	*/
	virtual int32 GetPSLangLevel() const = 0;
	/**	Get the output resolution
		@return PMReal of the output resolution
	*/
	virtual PMReal GetResolution() const = 0;
	/**	Get the paper size
		@return PMRect of the paper size
	*/
	virtual PMRect GetPaperSize() const = 0;
	/**	Get the imageable paper size - the imageable area for the paper
		@return PMRect of the paper's imageable area size
	*/
	virtual PMRect GetImageablePaperSize() const = 0;
	/**	Get the paper size selection.
		@return one of kPaperSizeDefinedByUser (Custom paper size), 
		kPaperSizeDefinedByDriver (Defined by Driver), kPaperSizeDefinedByName (see SetPaperSizeName)
	*/
	virtual int32 GetPaperSizeSelection() const = 0;
	/**	Get the paper size name. This is only applicable if paper size selection is kPaperSizeDefinedByName
		@return PMString of the paper size name
	*/
	virtual PMString GetPaperSizeName() const = 0;
	/**	Get the custom paper size width. This is only applicable if the paper size selection is kPaperSizeDefinedByUser
		@return PMReal of the custom paper size width. This can be kCustomPaperSizeAuto.
	*/
	virtual PMReal GetCustomPaperWidth() const = 0;
	/**	Get the custom paper size width range. This is only applicable if the paper size selection is kPaperSizeDefinedByUser
		@param outMinWidth	OUT PMReal reference to the minimum value for the custom paper size width.
		@param outMaxWidth	OUT PMReal reference to the maximum value for the custom paper size width.
	*/
	virtual void GetDeviceCustomPaperWidthRange(PMReal &outMinWidth, PMReal &outMaxWidth) const = 0;
	/**	Get the custom paper size height. This is only applicable if the paper size selection is kPaperSizeDefinedByUser
		@return PMReal of the custom paper size height. This can be kCustomPaperSizeAuto.
	*/
	virtual PMReal GetCustomPaperHeight() const = 0;
	/**	Get the custom paper size height range. This is only applicable if the paper size selection is kPaperSizeDefinedByUser
		@param outMinHeight	OUT PMReal reference to the minimum value for the custom paper size height.
		@param outMaxHeight	OUT PMReal reference to the maximum value for the custom paper size height.
	*/
	virtual void GetDeviceCustomPaperHeightRange(PMReal &outMinHeight, PMReal &outMaxHeight) const = 0;
	/**	Get the custom paper size offset amount. This is only applicable if the paper size selection is kPaperSizeDefinedByUser
		@return PMReal of the custom paper size offset.
	*/
	virtual PMReal GetCustomPaperOffset() const = 0;
	/**	Get the custom paper size offset range. This is only applicable if the paper size selection is kPaperSizeDefinedByUser
		@param outMin	OUT PMReal reference to the minimum value for the custom paper size offset.
		@param outMax	OUT PMReal reference to the maximum value for the custom paper size offset.
	*/
	virtual void GetDeviceCustomPaperWidthOffsetRange(PMReal &outMin, PMReal &outMax) const = 0;
	/**	Get the custom paper size gap amount. This is only applicable if the paper size selection is kPaperSizeDefinedByUser
		@return PMReal of the custom paper size gap.
	*/
	virtual PMReal GetCustomPaperGap() const = 0;
	/**	Get the paper orientation
		@return one of kNormal, kTransverse
	*/
	virtual int32 GetPaperOrientation() const = 0;
	/**	Get the page orientation
		@return one of kPortrait, kLandscape (Counterclockwise 90 degrees), 
		kReversePortrait (180 degrees), kReverseLandscape (Counterclockwise 270 degrees)
	*/
	virtual int32 GetPageOrientation() const = 0;
	/**	Get if page orientation is up and down (portrait or reverse portrait)
		@return kTrue if page orientation is either kPortrait or kReversePortrait, kFalse otherwise
	*/
	virtual bool16 IsPageOrientationLikePortrait() const = 0;
	/**	Get if page orientation is the same as paper orientation - i.e. landscape and tranverse selected
		@return kTrue if page and paper orientation are the same, kFalse otherwise
	*/
	virtual bool16 IsPageOrientationLikePortraitOnDevice() const = 0;
	/**	Get the proxy page width size (only used in the UI)
		@return uint32 of the proxy page width
	*/
	virtual uint32 GetProxyPageWidth() const = 0;
	/**	Get the proxy page height size (only used in the UI)
		@return uint32 of the proxy page height
	*/
	virtual uint32 GetProxyPageHeight() const = 0;
	/**	Get the proxy spread width size - used for drawing the proxy when spreads are on (only used in the UI)
		@return uint32 of the proxy spread width
	*/
	virtual uint32 GetProxySpreadWidth() const = 0;
	/**	Get the proxy spread height size - used for drawing the proxy when spreads are on (only used in the UI)
		@return uint32 of the proxy spread height
	*/
	virtual uint32 GetProxySpreadHeight() const = 0;
	/**	Get the number of copies
		@return number of copies
	*/
	virtual int32 GetCopies() const = 0;
	/**	Get if collating or not
		@return kTrue if collate, kFalse otherwise
	*/
	virtual bool16 GetCollate() const = 0;
	/**	Get if reverse order turned on
		@return kTrue if reverse order, kFalse otherwise
	*/
	virtual bool16 GetReverseOrder() const = 0;
	/**	Get the flip mode
		@return one of kFlipOff, kFlipHorizontal, kFlipVertical, kFlipBoth
	*/
	virtual int32 GetFlipMode() const = 0;
	/**	Get if printing page as negative 
		@return kTrue if printing as negative, kFalse otherwise
	*/
	virtual bool16 GetNegative() const = 0;
	/**	Get if printing blank pages 
		@return kTrue if printing blank pages, kFalse otherwise
	*/
	virtual bool16 GetPrintBlankPages() const = 0;
	/**	Get if printing non printing objects 
		@return kTrue if overriding page item non-printing attribute, kFalse otherwise
	*/
	virtual bool16 GetPrintNonPrintingObjects() const = 0;
	/**	Get which pages are printing, all pages or page range
		@return one of kAllPages, kPageRange
	*/
	virtual int32 GetWhichPages() const = 0;
	/**	Get the page range printing
		@return PMString of the page range string.
	*/
	virtual PMString GetPageRange() const = 0; 
	/**	Get which pages are printing, both odd and even, odd only or even only
		@return one of kBothPages, kEvenPagesOnly, kOddPagesOnly
	*/
	virtual int32 GetPrintOption() const = 0;
	/**	Get if printing spreads 
		@return kTrue if printing spreads, kFalse otherwise
	*/
	virtual bool16 GetSpreads() const = 0;
	/**	Get the color output mode
		@return one of kCompositeGray, kCompositeRGB, kCompositeCMYK,
		kSeparationBuiltIn, kSeparationInRIP, kCompositeLeaveUnchanged
	*/
	virtual int32 GetOutputMode() const = 0;
	/**	Get if printing text as black 
		@return kTrue if printing text as black, kFalse otherwise
	*/
	virtual bool16 GetPrintColorsInBlack() const = 0;
	/**	Get if showing the file save dialog 
		@return kTrue if showing the file save dialog, kFalse otherwise
	*/
	virtual bool16 GetShowSaveDialog() const = 0;
	/**	Get the composite angle amount
		@return PMReal of the composite angle value.
	*/
	virtual PMReal GetCompositeAngle() const = 0;
	/**	Get the composite frequency amount
		@return PMReal of the composite frequency value.
	*/
	virtual PMReal GetCompositeFrequency() const = 0;
	/**	Get the composite screening text
		@return PMString of the composite screening text.
		This can be "kDefault" or if kCompositeGray is color output mode, "kCustom" 
	*/
	virtual PMString GetCompositeScreenText() const = 0;
	/**	Get the separation screening text
		@return PMString of the separation screening text.
	*/
	virtual PMString GetSeparationScreenText() const = 0;
	/**	Get the scaling mode, either scale to fit, or scale by X and Y
		@return one of kScaleToFit, kScaleXAndY
	*/
	virtual int32 GetScaleMode() const = 0;
	/**	Get if scaling proportionally 
		@return kTrue to contraining to proportions, kFalse otherwise
	*/
	virtual bool16 GetProportional() const = 0;
	/**	Get the X scale amount - only applicable if scale mode is kScaleXAndY
		@return PMReal of the X scale value.
	*/
	virtual PMReal GetXScale() const = 0;
	/**	Get the Y scale amount - only applicable if scale mode is kScaleXAndY
		@return PMReal of the Y scale value.
	*/
	virtual PMReal GetYScale() const = 0;
	/**	Get the page positioning on the paper
		@return one of kPagePositionUpperLeft, kPagePositionCenterHorizontally,
		kPagePositionCenterVertically, kPagePositionCentered
	*/
	virtual int32 GetPagePosition() const = 0;
	/**	Get which layers will print
		@return one of kPrintAllLayers, kPrintVisibleLayers, kPrintVisiblePrintableLayers
	*/
	virtual int32 GetPrintLayers() const = 0;
	/**	Get the tiling and thumbnail mode
		@return one of kTileThumbOff, kTiling, kThumbnails
	*/
	virtual int32 GetTileThumbMode() const = 0;
	/**	Get the tiling mode - only applicable if tile thumb mode is kTiling
		@return one of kTilingAutomatic, kTilingManual, kTilingAutoJustified
	*/
	virtual int32 GetTilingMode() const = 0;
	/**	Get the tiling overlap amount - only applicable if tile thumb mode is kTiling
		@return PMReal of the tiling overlap value.
	*/
	virtual PMReal GetTilingOverlap() const = 0;
	/**	Get the number of thumbnails per page - only applicable if tile thumb mode is kThumbnails
		@return the number of thumbnails on a page
	*/
	virtual int32 GetNumberOfThumbsPerPage() const = 0;
	/**	Get how the image data will be printed
		@return one of kImageDataAll, kImageDataOptimized, kImageDataLoRez, kImageDataProofPrint 
	*/
	virtual int32 GetImageData() const = 0;
	/**	Get how the image data will be formatted
		@return one of kImageDataBinary, kImageDataASCII
	*/
	virtual int32 GetImageDataFormat() const = 0;
	/**	Get if printing using bitmap 
		@return kTrue if bitmap printing, kFalse otherwise
	*/
	virtual bool16 GetBitmapPrinting() const = 0;
	/**	Get the bitmap printing resolution value
		@return int32 of the bitmap resolution value. If set using IPrintData::kBitmapResolution_300,
					this will return the value 300, not kBitmapResolution_300.
	*/
	virtual int32 GetBitmapResolution() const = 0;
	/**	Get if performing OPI replacement 
		@return kTrue if doing OPI replacement, kFalse otherwise
	*/
	virtual bool16 GetOPIReplacement() const = 0;
	/**	Get if omitting EPS data from output stream 
		@return kTrue if omitting EPS data, kFalse otherwise
	*/
	virtual bool16 GetOmitEPS() const = 0;
	/**	Get if omitting PDF data from output stream 
		@return kTrue if omitting PDF data, kFalse otherwise
	*/
	virtual bool16 GetOmitPDF() const = 0;
	/**	Get if omitting bitmap data from output stream - not valid if doing
		OPI replacement
		@return kTrue if omitting images, kFalse otherwise
	*/
	virtual bool16 GetOmitImages() const = 0;
	/**	Get the font download mode
		@return one of kFontDownloadNone, kFontDownloadComplete,
		kFontDownloadSubset, kFontDownloadSubsetLrg (deprecated)
	*/
	virtual int32 GetFontDownload() const = 0;
	/**	Get if downloading PPD fonts  
		@return kTrue if downloading PPD fonts, kFalse otherwise
	*/
	virtual bool16 GetDownloadPPDFonts() const = 0;
	/**	Get the page mark file in use
		@return PMString of the page mark file. Can be
		empty string for Default
	*/
	virtual PMString GetPageMarkFile() const = 0;
	/**	Get the page mark line weight 
		@return one of kMarkLineWeight125pt, kMarkLineWeight25pt,
		kMarkLineWeight50pt, OR if Japanese, kMarkLineWeight05mm, kMarkLineWeight07mm,
		kMarkLineWeight10mm, kMarkLineWeight15mm, kMarkLineWeight20mm, kMarkLineWeight30mm
	*/
	virtual int32 GetMarkLineWeight() const = 0;
	/**	Get the page mark offset amount
		@return PMReal of the page mark offset value.
	*/
	virtual PMReal GetPageMarkOffset() const = 0;
	/**	Get if printing crop marks  
		@return kTrue if printing crop marks, kFalse otherwise
	*/
	virtual bool16 GetCropMarks() const = 0;
	/**	Get if printing page information 
		@return kTrue if printing page information, kFalse otherwise
	*/
	virtual bool16 GetPageInformation() const = 0;
	/**	Get if printing color bars 
		@return kTrue if printing color bars, kFalse otherwise
	*/
	virtual bool16 GetColorBars() const = 0;
	/**	Get if printing registration marks 
		@return kTrue if printing registration marks, kFalse otherwise
	*/
	virtual bool16 GetRegistrationMarks() const = 0;
	/**	Get if printing bleed marks 
		@return kTrue if printing bleed marks, kFalse otherwise
	*/
	virtual bool16 GetBleedMarks() const = 0;
	/**	Get if using the document bleed values 
		@return kTrue if using the document bleed values, kFalse otherwise
	*/
	virtual bool16 GetUseDocumentBleed() const = 0;
	/**	Get the bleed value for the top edge
		@return PMReal of the top bleed value.
	*/
	virtual PMReal GetBleedTop() const = 0;
	/**	Get if the bleed values are chained together 
		@return kTrue if the bleed values are chained, kFalse otherwise
	*/
	virtual bool16 GetBleedChain() const = 0;
	/**	Get the bleed value for the inside edge - that is the edge closest to the 
		binding for facing pages. This is the left side if printing spreads, or if
		there is not facing pages.
		@return PMReal of the inside bleed value.
	*/
	virtual PMReal GetBleedInside() const = 0;
	/**	Get the bleed value for the bottom edge
		@return PMReal of the bottom bleed value.
	*/
	virtual PMReal GetBleedBottom() const = 0;
	/**	Get the bleed value for the outside edge - that is the edge farthest from the 
		binding for facing pages. This is the right side if printing spreads, or if
		there is not facing pages.
		@return PMReal of the outside bleed value.
	*/
	virtual PMReal GetBleedOutside() const = 0;
	/**	Get if the slug area is included 
		@return kTrue if the slug area is included, kFalse otherwise
	*/
	virtual bool16 GetIncludeSlug() const = 0;
	/**	Get the trapping mode
		@return one of kTrappingNone, kTrappingBuiltIn, kTrappingInRIP
	*/
	virtual int32 GetTrappingMode() const = 0;
	/**	Get the source space for color management
		@return one of kDocumentSourceSpace, kProofSourceSpace
	*/
	virtual int32 GetSourceSpace() const = 0;
	/**	Get the profile type for color management
		@return one of kUsePostScriptCMS, kUseDocumentProfile, kUseWorkingProfile, kUseSpecificProfile, kUseNoCMS
	*/
	virtual int32 GetProfileType() const = 0;
	/**	Get the profile name for color management - only applicable if profile 
		type is kUseSpecificProfile
		@return PMString of the name of the profile
	*/
	virtual PMString GetProfileName() const = 0;
	/**	Get the CRD type for color management
		@return one of kUseNoCRD, kUseDocumentCRD, kUseWorkingCRD, kUseSpecificCRD
	*/
	virtual int32 GetCRDType() const = 0;
	/**	Get the CRD name for color management - only applicable if CRD 
		type is kUseSpecificCRD
		@return PMString of the name of the CRD
	*/
	virtual PMString GetCRDName() const = 0;
	/**	Get intent type for color management
		@return one of kPerceptual, kSaturation, kRelativeColorimetric, kAbsoluteColorimetric
	*/
	virtual int32 GetIntent() const = 0;
	/**	Get the Simulate Overprint type. 
		@return one of kLegacy (SimOP off), kSimulatePress (SimOP on), kSimulateScreen (deprecated)
	*/
	virtual int32 GetSpotOverPrint() const = 0;
	/**	Get whether printing visible guides and baseline grids 
		@return kTrue if printing guides and grids, kFalse otherwise
	*/
	virtual bool16 GetPrintWYSIWYGGridsGuides() const = 0;
	/**	Get if filtering port contents - CJK specific
		@return kTrue if filtering, kFalse otherwise
		@see IPrintContentPrefs
	*/
	virtual bool16 GetCJKFilterContent(void) const = 0;
	/**	Get if printing text - CJK specific
		@return kTrue if printing text, kFalse otherwise
		@see IPrintContentPrefs
	*/
	virtual bool16 GetCJKPrintText() const = 0;
	/**	Get if printing page items - CJK specific
		@return kTrue if printing page items, kFalse otherwise
		@see IPrintContentPrefs
	*/
	virtual bool16	GetCJKPrintPageItems() const = 0;
	/**	Get if printing layout grids - CJK specific
		@return kTrue if printing layout grids, kFalse otherwise
		@see IPrintContentPrefs
	*/
	virtual bool16	GetCJKPrintLayoutGrids() const = 0;
	/**	Get if printing frame grids - CJK specific
		@return kTrue if printing frame grids, kFalse otherwise
		@see IPrintContentPrefs
	*/
	virtual bool16	GetCJKPrintFrameGrids() const = 0;
	/**	Get if printing frame grid when empty - CJK specific
		@return kTrue if printing frame grid when empty, kFalse otherwise
		@see IPrintContentPrefs 
	*/
	virtual bool16	GetCJKOnlyPrintFrameGridWhenEmpty() const = 0;
	/**	Get the print frame grid view - CJK specific
		@return frame grid view
		@see IPrintContentPrefs GridView
	*/
	virtual int32	GetCJKPrintFrameGridView() const = 0;
	/**	Get the frame grid stroke weight - CJK specific
		@return PMReal of the frame grid stroke weight
		@see IPrintContentPrefs 
	*/
	virtual PMReal GetCJKFrameGridStrokeWeight() const = 0;
	/**	Get the layout grid stroke weight - CJK specific
		@return PMReal of the layout grid stroke weight
		@see IPrintContentPrefs 
	*/
	virtual PMReal GetCJKLayoutGridStrokeWeight()  const = 0;
	/**	Get if printing the Cyan ink 
		@return kTrue if printing the Cyan ink, kFalse otherwise
	*/
	virtual bool16 GetCyanPrintInk() const = 0;
	/**	Get the Cyan ink frequency value
		@return PMReal of the Cyan ink frequency value
	*/
	virtual PMReal GetCyanFrequency() const = 0;
	/**	Get the Cyan ink angle value
		@return PMReal of the Cyan ink angle value
	*/
	virtual PMReal GetCyanAngle() const = 0;
	/**	Get if printing the Magenta ink
		@return kTrue if printing the Magenta ink, kFalse otherwise
	*/
	virtual bool16 GetMagentaPrintInk() const = 0;
	/**	Get the Magenta ink frequency value
		@return PMReal of the Magenta ink frequency value
	*/
	virtual PMReal GetMagentaFrequency() const = 0;
	/**	Get the Magenta ink angle value
		@return PMReal of the Magenta ink angle value
	*/
	virtual PMReal GetMagentaAngle() const = 0;
	/**	Get if printing the Yellow ink
		@return kTrue if printing the Yellow ink, kFalse otherwise
	*/
	virtual bool16 GetYellowPrintInk() const = 0;
	/**	Get the Yellow ink frequency value
		@return PMReal of the Yellow ink frequency value
	*/
	virtual PMReal GetYellowFrequency() const = 0;
	/**	Get the Yellow ink angle value
		@return PMReal of the Yellow ink angle value
	*/
	virtual PMReal GetYellowAngle() const = 0;
	/**	Get if printing the Black ink
		@return kTrue if printing the Black ink, kFalse otherwise
	*/
	virtual bool16 GetBlackPrintInk() const = 0;
	/**	Get the Black ink frequency value
		@return PMReal of the Black ink frequency value
	*/
	virtual PMReal GetBlackFrequency() const = 0;
	/**	Get the Black ink angle value
		@return PMReal of the Black ink angle value
	*/
	virtual PMReal GetBlackAngle() const = 0;
	/**	Get the spot ink frequency value
		@return PMReal of the spot ink frequency value
	*/
	virtual PMReal GetSpotFrequency() const = 0;
	/**	Get the spot ink angle value
		@return PMReal of the spot ink angle value
	*/
	virtual PMReal GetSpotAngle() const = 0;
	/**	Get the UID of the flattener style in use
		@return UID of the name of the flattener style in use
	*/
	virtual UID GetFlattenerStyleUID() const = 0;
	/**	Get the name of the flattener style in use
        @translateName IN kTrue to translate the string, if possible.
		@return PMString of the name of the flattener style
	*/
	virtual PMString GetFlattenerStyleName(bool16 translateName = kTrue) const = 0;
	/**	Get if ignoring flattener spread overrides 
		@return kTrue if ignoring spread overrides, kFalse otherwise
	*/
	virtual bool16 GetIgnoreSpreadOverrides() const = 0;
	/**	Get the scope of pages printing - either the document or Master pages
		@return one of kScopeDocument, kScopeMaster
	*/
	virtual int32 GetScope() const = 0;
	/**	Get the paper size selector data - a magic cookie to select paper sizes
		NOTE - Caller is responsible for delete[]-ing the return value!!!
		@param outSize	OUT size of data returned
		@return opaque data bytes
	*/
	virtual uchar* GetPaperSizeSelector(uint32 &outSize) const = 0; // NOTE!!! Caller is responsible for delete[]-ing the return value!!!
	/**	Get whether to preserve the CMYK/RGB color numbers or not
		@return kTrue if preserving color numbers, kFalse otherwise
	*/
	virtual bool16 GetPreserveColorNumbers() const = 0;

	/** Convert the print data to a more general form. Used in generating the Summary panel.
		@param pDlgData			IN IPrintDialogData pointer
		@param bWorkingOnStyle	IN kTrue if working on a printer style, kFalse otherwise
		@param nSpreadsPerPage	IN number of spread per page
		@param uidDoc			IN UIDReference to the document
		@return IGenericSettings pointer
		@see ISummaryUtils, IGenericSettings and IPrintDialogData
	*/
	virtual IGenericSettings* _GetSettings( const  IPrintDialogData* pDlgData,
						                   bool16                   bWorkingOnStyle,
										   int32                    nSpreadsPerPage,
										   UIDRef&                  uidDoc) const = 0;
	/**	Get whether PDF passthrough mode is enabled on the selected printer.
		@return kTrue if PDF passthrough is on, kFalse otherwise
	*/
	virtual bool16 GetPDFPassthroughMode() const = 0;

	/**	Set whether PDF passthrough mode should be enabled on the selected printer.
		@param pdfPassthrough IN kTrue if passthrough should be enabled, kFalse otherwise
	*/
	virtual void SetPDFPassthroughMode(bool16 pdfPassthrough) = 0;
};

#endif

// End, IPrintData.h.
