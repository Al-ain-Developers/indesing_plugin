//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IInteractivePDFExportFacade.h $
//  
//  Owner: DBerggren
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
#ifndef __IInteractivePDF_ExportFacade__
#define __IInteractivePDF_ExportFacade__

// ----- Interface files -----

#include "IPageRange.h"
#include "IPMUnknown.h"
#include "IInteractivePDFExportPrefs.h"
#include "IPDFSecurityPrefs.h"

// ----- ID files -----

#include "PDFID.h"

// ===================================================================================
//	class IInteractivePDF_ExportFacade 
// ===================================================================================
namespace Facade
{
	/** This facade provides services for obtaining and modifying the preference settings for  
		Interactive PDF export that is new to InDesign CS5. The preference is on the application workspace 
		boss and the main interfaces in the preference are:
			@see IInteractivePDFExportPreferences
			@see IPDFSecurityPrefs
			@see IPageRange
	*/

	class IInteractivePDF_ExportFacade : public IPMUnknown 
	{
		public:
			// ----- Constants -----
			enum {kDefaultIID = IID_IINTERACTIVEPDFEXPORTFACADE};

			/**
			 Gets the page range information from the session preferences.
			 	 
			 @param pageRange [OUT]: contains string of page range.
			 @param pageRangeFormat [OUT]: contains enum value of page range format.
			 */
			virtual void GetPageRangeInfo(PMString &pageRange, IPageRange::RangeFormat &pageRangeFormat) const = 0;

			/**
			 Gets the page range information from the session preferences.
			 	 
			 @param iPageRange [OUT]: contains the page range info.
			 */
			virtual void GetPageRangeInfo(IPageRange* iPageRange) const = 0;

			/**
			 Gets whether to export as reader's spreads.
			 
			 @return kTrue if exporting as reader's spreads; otherwise kFalse.
			 */
			virtual bool ReadersSpreads() const = 0;

			/**
			 Gets whether to view generated interactive PDF after export.
			 
			 @return kTrue if view after export.
			 */		
			virtual bool ViewAfterExport() const = 0;

			/**
			 Gets whether to embed page thumbnails in the interactive PDF.
			 
			 @return kTrue if embedding page thumnails.
			 */		
			virtual bool EmbedPageThumbnails() const = 0;

			/**
			 Gets whether to create Acrobat layers in the interactive PDF.
			 
			 @return kTrue if creating Acrobat layers.
			 */		
			virtual bool CreateAcrobatLayers() const = 0;

			/**
			 Gets whether to create a tagged (structured) interactive PDF.
			 
			 @return kTrue if creating PDF tags.
			 */		
			virtual bool CreateTaggedPDF() const = 0;

			/**
			 Gets the magnification setting for the exported PDF.
			 
			 @return one of the Magnification enum defined in IInteractivePDFExportPrefs.
			 */		
			virtual IInteractivePDFExportPrefs::Magnification ExportMagnification() const = 0;

			/**
			 Gets the page layout of the exported PDF.
			 
			 @return one of the PageLayout enum defined in IInteractivePDFExportPrefs.
			 */		
			virtual IInteractivePDFExportPrefs::PageLayout ExportPageLayout() const = 0;

			/**
			 Gets whether to open the exported PDF in full screen mode.
			 
			 @return kTrue if opening in full screen mode.
			 */		
			virtual bool OpenInFullScreenMode() const = 0;

			/**
			 Gets whether to automatically flip pages in the exported PDF.
			 
			 @return kTrue if flip pages is turned on.
			 */		
			virtual bool FlipPages() const = 0;

			/**
			 If FlipPages() is true, this returns the speed (in seconds) that the pages are flipped.
			 
			 @return uint32 the flip pages speed (in seconds).
			 */		
			virtual uint32 FlipPagesSpeed() const = 0;

			/**
			 Returns the ClassID of an IPageTransition, if one is selected as an override. If 
			 this returns kPageTransitionFromDocument the page transitions will honor the page
			 transition that is set on the spread. kInvalidClass means no page transition.
			 
			 @return ClassID the page transition, kInvalidClass if none selected, kPageTransitionFromDocument if not overridden.
			 @see IPageTransition 
			 @see IPageTransitionFacade
			 */		
			virtual ClassID PageTransitionOverride() const = 0;

			/**
			 Gets how interactive elements in the document are drawn to the interactive PDF. The
			 choices are either Include All or Appearance Only.

			 @return One of the InteractiveElements enum defined in IInteractivePDFExportPrefs.
			 */
			virtual IInteractivePDFExportPrefs::InteractiveElements GetInteractiveElements() const = 0;

			/**
			 Gets the preferred raster compression to be used for the interactive PDF export.

			 @return One of the RasterCompression enum defined in IInteractivePDFExportPrefs.
			 */
			virtual IInteractivePDFExportPrefs::RasterCompression GetRasterCompression() const = 0;

			/**
			 Gets the quality to be used for JPEG compressed images during the interactive PDF export.
			 
			 @return One of the JPEGQuality enum defined in IInteractivePDFExportPrefs.
			 */
			virtual IInteractivePDFExportPrefs::JPEGQuality GetJPEGQuality() const = 0;

			/**
			 Get the raster resolution used for raster data.
			 
			 @return uint32 raster resolution (in ppi).
			 */		
			virtual uint32 RasterResolution() const = 0;

			/**
			 Gets the PDF export security session workspace preferences.
			 	 
			 @param iSecurityPrefsData [OUT]: the IPDFSecurityPrefs interface contains PDF export security preferences.
			 */
			virtual void GetWorkspaceSecurityPreferences(IPDFSecurityPrefs* iSecurityPrefsData) const = 0;

			/**
			 Set the PDF export security preferences for the session workspace.
			 	 
			 @param iSecurityPrefsData [IN]: The PDF security preference data to save in the session preferences.
			 */
			virtual ErrorCode SetWorkspaceSecurityPreferences(IPDFSecurityPrefs* iSecurityPrefsData) = 0;

			/**
			 Gets the interactive PDF session workspace preferences.
			 	 
			 @param iPrefsData [OUT]: the IInteractivePDFExportPreferences interface contains InteractivePDF export preferences.
			 */
			virtual void GetWorkspacePreferences(IInteractivePDFExportPrefs* iPrefsData) const = 0;

			/**
			 Set the InteractivePDF export preferences for the session workspace.
			 	 
			 @param iPrefsData [IN]: The InteractivePDF general preference data where we use for setting export preferences.
			 @param iPageRangeData [IN]: The page preference data where we use for setting export preferences.
			 */
			virtual ErrorCode SetWorkspacePreferences(IInteractivePDFExportPrefs* iPrefsData, IPageRange* iPageRangeData) = 0;

			/**
			 Gets whether to use tagged PDF structure for ordering tabs.

			 @return kTrue if using PDF structure for tab order.
			 */
			virtual bool16 GetUsePDFStructureForTabs() const = 0;

			/**
			 Gets the display title option of the exported PDF.

			 @return one of the DisplayTitle enum defined in IInteractivePDFExportPrefs.
			*/
			virtual IInteractivePDFExportPrefs::DisplayTitle GetDisplayTitle() const = 0;

			/**
			Gets the default document language of the exported PDF.
			*/
			virtual PMString GetDefaultDocumentLanguage() const = 0;

			/**
			Gets whether to export each page of the document as a single pages PDF.
			*/
			virtual bool16 GetExportSinglePagesPDF() const = 0;

			/**
			Gets the suffix to be used in exported PDF file's name if document is exported as single pages PDF.
			*/
			virtual PMString GetSinglePagesPDFSuffix() const = 0;
	};
}
#endif // define
