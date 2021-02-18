//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPrintUtils.h $
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
#ifndef __IPrintUtils__
#define __IPrintUtils__


#include "IPMUnknown.h"

#include "PMRect.h"
#include "PrintID.h"
#include "Utils.h"

class ICMSProofing;
class IColorPresetsSettings;
class IDocument;
class IOutputPages;
class IPrintData;
class IPrintDeviceInfo;
class IPrintDialogData;
class IViewPortAttributes;
class IInkList;
class IPrintJobData;
class GraphicsData;

#define PRINTUTILS Utils<IPrintUtils>()

/** Public Print Utility class
*/
class IPrintUtils : public IPMUnknown
{
public:
	/** Print event print stages - used in InvokePrintSetupServices method
	*/
	enum PrintStage {

		kBeforePrintJobParamsInit = 0,
		kAfterPrintJobParamsInit,

		kBeforePrintLoop,

		kBeginPageEvent,

		kBeforeDrawPageEvent,
		kBeforeDrawPage,
		kAfterDrawPageEvent,

		kEndPageEvent,

		kBeforeDrawGalleyPageEvent,
		kBeforeDrawGalleyPage,
		kAfterDrawGalleyPageEvent,

		kEndPrintingEvent
		};

public:
	enum { kDefaultIID = IID_IPRINTUTILS };

	/** Determine if printing in a composite (vs. separation) mode
		@param outputMode	IN the current color output mode
		@return kTrue if printing composite, kFalse otherwise
	*/
	virtual bool16 IsCompositeMode(int32 outputMode) = 0;
	/** Determine if printing in a separation (vs. composite) mode
		@param outputMode	IN the current color output mode
		@return kTrue if printing separations, kFalse otherwise
	*/
	virtual bool16 IsSeparationMode(int32 outputMode) = 0;
	/** Determine the printer's default color output mode
		@param iPrintDeviceInfo	IN pointer to IPrintDeviceInfo for the printer
		@return one of kCompositeGray, kCompositeRGB, kCompositeCMYK defined in IPrintData
		@see IPrintDeviceInfo IPrintData
	*/
	virtual int32 GetDefaultOutputMode(const IPrintDeviceInfo* iPrintDeviceInfo) = 0;

	/** Determine if any bleed is turned on in the given IPrintData
		@param iPD	IN pointer to IPrintData to query
		@return kTrue if there is any bleed, kFalse otherwise
		@see IPrintData
	*/
	virtual bool16 BleedIsOn(const IPrintData* iPD) = 0;
	/** Determine if any page marks are turned on in the given IPrintData
		@param iPD	IN pointer to IPrintData to query
		@return kTrue if there are any marks, kFalse otherwise
		@see IPrintData
	*/
	virtual bool16 MarksAreOn(const IPrintData* iPD) = 0;

	/** Determine the name of the profile that will be used, based on whether CMS on/off,
		and the IPrintData and IDocument settings
		@param iPrintData	IN pointer to IPrintData to query
		@param iDocument	IN pointer to IDocument to query
		@return PMString of the profile name in use
		@see IPrintData IDocument
	*/
	virtual PMString GetUsedProfileName(const IPrintData* iPrintData, IDocument* iDocument) = 0;
	/** Determine the name of the document profile, based on the selected output mode in
		the IPrintData and the IDocument settings
		@param iPrintData	IN pointer to IPrintData to query
		@param iDocument	IN pointer to IDocument to query
		@return PMString of the document profile name 
		@see IPrintData IDocument
	*/
	virtual PMString GetDocumentProfileName(const IPrintData* iPrintData, IDocument* iDocument) = 0;
	/** Determine the name of the document profile, based on the given colorspace 
		and the IDocument settings
		@param iDocument	IN pointer to IDocument to query
		@param source		IN source colorspace, either kPMCsCalCMYK or kPMCsCalRGB
		@return PMString of the document profile name 
		@see IDocument GraphicTypes.h
	*/
	virtual PMString GetDocumentProfileName(IDocument* iDocument, int32 source) = 0;
	/** Determine the name of the working profile, based on the selected output mode in
		the IPrintData given
		@param iPrintData	IN pointer to IPrintData to query
		@return PMString of the working profile name 
		@see IPrintData
	*/
	virtual PMString GetWorkingProfileName(const IPrintData* iPrintData) = 0;
	/** Determine the name of the working profile, based on the given colorspace 
		@param source		IN source colorspace, either kPMCsCalCMYK or kPMCsCalRGB
		@return PMString of the working profile name 
		@see GraphicTypes.h
	*/
	virtual PMString GetWorkingProfileName(int32 source) = 0;

	/** Get the ICMSProofing interface for the given IDocument 
		@param iDocument	IN pointer to IDocument to use
		@return ICMSProofing pointer  
		@see ICMSProofing IDocument
	*/
	virtual ICMSProofing* QueryICMSProofing(IDocument* iDocument) = 0;
	/** Update the IPrintDialogData settings for process and spot inks from
		the IPrintData settings (IPrintData retrieved from IPrintDialogData::GetPrintData)
		@param iPrintDialogData	IN pointer to IPrintDialogData to use and update
		@see IPrintDialogData
	*/
	virtual void UpdateInkScreening(IPrintDialogData* iPrintDialogData) = 0;

	/** Initialize the document's inks from the settings stored in the 'Default'
		printer style. Will initialize the print/no print state as well as the
		frequency and angle for the process inks, and the frequency and angles
		of the spot inks. Called from the new document responder.
		@param doc	IN pointer to IDocument to update
		@see IDocument
	*/
	virtual void InitPrintDataAndInks(IDocument* doc) = 0;
	/** Perform a fix-up of IPrintData for the current document. Will set the 
		page orientation setting to match the document, and will determine the
		best orientation if thumbnails is on and the number of thumbs is 2.
		Called from the later new document responder, so page setup is done first.
		@param doc	IN pointer to IDocument to update
		@see IDocument
	*/
	virtual void FixupPrintDataForPub(IDocument* doc) = 0;

	/** Figure out the width and height and width offset for custom paper size
		@param whichPage	IN which page to use for calculations
		@param iPrintData	IN IPrintData pointer to use
		@param iOutputPages	IN IOutputPages pointer to use
		@param nWidth		OUT PMReal reference to the calculated custom paper size width
		@param nHeight		OUT PMReal reference to the calculated custom paper size height
		@param nWidthOffset	OUT PMReal reference to the calculated custom paper size width offset
	*/
	virtual void FigureCustomPaperSizeSettings(int32 whichPage,				// input
											   IPrintData* iPrintData,		// input 
											   IOutputPages* iOutputPages,	// input
											   PMReal& nWidth,				// output
											   PMReal& nHeight,				// output 
											   PMReal& nWidthOffset) = 0;	// output

	/** Determine number of rows and columns for thumbnails
		@param thumbsPerPage	IN desired number of thumbnails per page
		@param pageRect			IN PMRect reference to the page size
		@param iPrintData		IN IPrintData pointer to use
		@param rows				OUT the calculated number of rows
		@param columns			OUT the calculated number of columns
	*/
	virtual void ThumbCalculateRowsAndColumns(uint32 thumbsPerPage,
											  PMRect const& pageRect,
											  IPrintData const* iPrintData,
											  uint32& rows,
											  uint32& columns) = 0;

	/** Determine if the document is wide (landscape orientation)
		@param pageRect		IN PMRect reference to the page size
		@param iPrintData	IN IPrintData pointer to use
		@return kTrue if the document is wide, kFalse otherwise
	*/
	virtual bool16 IsDocumentWide(PMRect const& pageRect, IPrintData const* printData) = 0;
	/** Determine if the print settings for the page is wide (landscape or rev. landscape orientation)
		@param iPrintData	IN IPrintData pointer to use
		@return kTrue if the print setting for the page is wide, kFalse otherwise
	*/
	virtual bool16 IsPrinterWide(IPrintData const* printData) = 0;


	/** Check the tiling overlap and reduce it to half of the smallest paper size
		dimension (width or height) if it is larger.
		This may not always work for books using Auto custom paper sizes, since the
		paper size used can change at print time.
		@param iPrintData	IN IPrintData pointer to use
		@return PMReal of the corrected tile overlap
	*/
	virtual PMReal GetCorrectedTilingOverlap(const IPrintData* iPrintData) const = 0;

	/** Utility which fills in the specified IOutputPages with the set of pages to print, given 
		the print data, which specifies things like page ranges, whether to print even/odd/all,
		whether to print master pages, and so on.
		This function should only be used for non-book printing.
		@param iDoc			IN IDocument pointer to use
		@param iPrintData	IN IPrintData pointer to use
		@param iPrintPages	OUT IOutputPages pointer to fill out
		@return kTrue if successful, kFalse if error
	 */
	virtual bool16	InitializeOutputPages(IDocument *iDoc, IPrintData *iPrintData, IOutputPages *iPrintPages) = 0;

	/** Uses the specified print data to configure the specified attributes in a way that is appropriate for
		printing to a PostScript printer.
		@param pAttrs		OUT IViewPortAttributes pointer initialize
		@param pConfig		IN IPrintData pointer to use
		@param iInkList		IN IInkList pointer to use
	 */
	virtual void SetupPSViewPortAttrs( IViewPortAttributes* pAttrs, IPrintData* pConfig, IInkList* iInkList  ) = 0;

	/** Uses the specified print data to configure the specified attributes in a way that is appropriate for
		printing to a non-PostScript printer.
		@param pAttrs		OUT IViewPortAttributes pointer initialize
		@param pConfig		IN IPrintData pointer to use
	 */
	virtual void SetupNonPSViewPortAttrs( IViewPortAttributes* pAttrs, IPrintData* pConfig ) = 0;

	/** A simplified mechanism for invoking the print setup service calls.  This prevents you from having to
		write code to iterate over the service provider for every different call.  It iterates over the service
		providers, and makes the correct call based on the PrintSetupStage parameter.  See IPrintSetupProvider
		to determine which parameters are required for a given PrintSetupStage.
		@param printStage		IN current PrintStage, defined above 
		@param iPrintData		IN IPrintData pointer in use, or nil
		@param iOutputPages		IN IOutputPages pointer in use, or nil
		@param iPrintJobData	IN IPrintJobData pointer in use, or nil
		@param whichPage		IN which page is currently being printed, or nil
		@param outputRect		IN PMRect pointer to the current output rect, or nil
		@param gd				IN GraphicsData pointer in use, or nil
		@return kTrue to continue printing, kFalse to stop printing
	 */
	virtual bool16 InvokePrintSetupServices( 			
		    PrintStage						printStage,
			IPrintData*						iPrintData = nil,
			IOutputPages*					iOutputPages = nil,
			IPrintJobData*					iPrintJobData = nil,
			int32*							whichPage = nil,
			PMRect*							outputRect = nil,
			GraphicsData*					gd = nil
		) = 0;

	/** A utility for calling the error handling method of all the IPrintSetupProviders.  See that interface for
		information on the PrintErrorEvent method.
		@param iPrintData		IN IPrintData pointer in use
		@param errorNum			IN ErrorCode of the current error
		@param errComponent		IN PMString reference of which component detected the error
		@param errText			IN PMString reference of any additional error text
		@param errOtherInfo		IN PMString reference of any other error text
		@return kTrue to set the normal print error, kFalse not to set the internal print error
	 */
	virtual bool16 InvokePrintSetupError( 
			IPrintData*						iPrintData,
			ErrorCode&						errorNum,
			PMString&						errComponent,
			PMString&						errText,
			PMString&						errOtherInfo
			) = 0;

	/** Determines the image resolution that will be used in the view port attrs for the specified
		settings.  This is the resolution used to downsample the image.
		@param pConfig		IN IPrintData pointer in use
		@param iInkList		IN IInkList pointer in use, only used if printing seps
		@return PMReal of the image resolution that will be used
	 */
	virtual PMReal CalculateImageResolution( IPrintData* pConfig, IInkList* iInkList  ) = 0;

#ifdef DEBUG
	virtual bool16& gShowImageableArea() = 0;
	virtual bool16& gCheckPaperRects() = 0;
	virtual int32& gDownloadFontGlyphThreshold() = 0;
	virtual bool16& gTraceFlattenerInput() = 0;
	virtual bool16& gTraceFlattenerOutput() = 0;
#endif
};

#endif	// __IPrintUtils__
