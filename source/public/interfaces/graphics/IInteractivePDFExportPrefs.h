//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IInteractivePDFExportPrefs.h $
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

#include "PDFID.h"
#include "IPMStream.h"

/**
 Export preferences for interactive PDF exports.
 
 IInteractivePDFExportPrefs is used to configure the parameters for an export to the
 PDF format specifically targetted to Acrobat 9 and above.
 
 In order to export InDesign content to an interactive PDF, you will typically create an 
 instance of the interactive PDF export command (kInteractivePDFExportCmdBoss), set its 
 IOutputPages interface to the pages to be exported, and set up the output file (ISysFileData) 
 and UI flags (IUIFlagData) to be used. You can then use the IInteractivePDFExportPrefs 
 aggregated on the command boss to set up various parameters for the export, including how 
 to treat raster images, video, etc. There is also an interface off of the command boss
 to set the security settings for the exported PDF (IPDFSecurityPrefs).
 
 IInteractivePDFExportPrefs is also aggregated on the app workspace, where it is used
 to ensure that default export settings are preserved from export to export. You
 might consider using this instance as the base for your export settings. You 
 might also consider using kSetInteractivePDFExportPrefsCmdBoss to update the default export
 settings for subsequent exports. There is also a facade available (IInteractivePDFExportFacade.h)
 to assist in retrieving the application workspace settings.
 */
class IInteractivePDFExportPrefs : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IINTERACTIVEPDFEXPORTPREFS };
	
	/**
	 Copies one set of prefs into another

	 @param other			IN The preferences to copy
	 */
	virtual void Copy(IInteractivePDFExportPrefs const *other) = 0;

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
	 Sets whether to view the generated PDF file after exporting.
	 
	 @param viewAfterExport		Boolean. If kTrue, view the generated PDF file after exporting.
	 */
	virtual void SetViewAfterExport(bool16 viewAfterExport) = 0;
	
	/**
	 Gets whether to view the generated PDF file after exporting.
	 
	 @return kTrue if viewing the generated PDF file after exporting.
	 */
	virtual bool16 GetViewAfterExport() const = 0;

	/**
	 Sets whether to embed page thumbnails in the exported PDF file.
	 
	 @param embedPageThumbnails	Boolean. If kTrue, page thumbnails are embedded.
	 */
	virtual void SetEmbedPageThumbnails(bool16 embedPageThumbnails) = 0;
	
	/**
	 Gets whether to embed page thumbnails in the exported PDF file.
	 
	 @return kTrue if page thumbnails are to be embedded.
	 */
	virtual bool16 GetEmbedPageThumbnails() const = 0;

	/**
	 Sets whether to create Acrobat layers in the PDF.
	 
	 @param acrobatLayers	Boolean. If kTrue, create Acrobat layers.
	 */
	virtual void SetAcrobatLayers(bool16 acrobatLayers) = 0;
	
	/**
	 Gets whether to create Acrobat layers in the PDF.
	 
	 @return kTrue if creating Acrobat layers.
	 */
	virtual bool16 GetAcrobatLayers() const = 0;

	/**
	 Sets whether to create a tagged (structured) interactive PDF.
	 
	 @param taggedPDF	Boolean. If kTrue, create structured PDF.
	 */
	virtual void SetTaggedPDF(bool16 taggedPDF) = 0;
	
	/**
	 Gets whether to create a tagged (structured) interactive PDF.
	 
	 @return kTrue if creating tagged PDF.
	 */
	virtual bool16 GetTaggedPDF() const = 0;

	/**
	 Magnification - Options for magnification
	 */
	enum Magnification
	{
		kDefaultMagnification = 0,
		kActualSize,
		kFitPage,
		kFitWidth,
		kFitHeight,
		kFitVisible,
		k25percent,
		k50percent,
		k75percent,
		k100percent
	};
	
	/**
	 Sets the initial magnification when the PDF is opened.
	 
	 @type Magnification: One of the Magnification enum specifying the initial magnification to use.
	 */
	virtual void SetMagnification(Magnification magnification) = 0;
	
	/**
	 Gets the initial magnification setting.
	 
	 @return One of the Magnification enum specifying the magnification to use.
	 */
	virtual Magnification GetMagnification() const = 0;

	/**
	 Page Layout - Options for page layout
	 */
	enum PageLayout
	{
		kDefaultPageLayout = 0,
		kSinglePage,
		kSinglePageContinuous,
		kTwoUpFacing,
		kTwoUpFacingContinuous,
		kTwoUpCoverPage,
		kTwoUpCoverPageContinuous
	} ;
	
	/**
	 Sets the page layout for the PDF being exported.
	 
	 @type PageLayout: One of the PageLayout enum specifying the page layout to use.
	 */
	virtual void SetPageLayout(PageLayout pageLayout) = 0;
	
	/**
	 Gets the page layout for the PDF being exported.
	 
	 @return One of the PageLayout enum specifying the page layout to use.
	 */
	virtual PageLayout GetPageLayout() const = 0;

	/**
	 Sets whether to open the PDF in full screen mode.
	 
	 @param fullScreen	Boolean. If kTrue, PDF is opened in full screen mode.
	 */
	virtual void SetOpenInFullScreenMode(bool16 fullScreen) = 0;
	
	/**
	 Gets whether to open the PDF in full screen mode.
	 
	 @return kTrue if PDF is to be opened in full screen mode.
	 */
	virtual bool16 GetOpenInFullScreenMode() const = 0;

	/**
	 Sets whether to automatically flip pages in the PDF. If this is true,
	 the set/get flip pages speed will determine the speed that the pages flip.
	 
	 @param flipPages	Boolean. If kTrue, pages will automatically flip.
	 */
	virtual void SetFlipPages(bool16 flipPages) = 0;
	
	/**
	 Gets whether to automatically flip pages in the PDF.
	 
	 @return kTrue if pages will automatically flip.
	 */
	virtual bool16 GetFlipPages() const = 0;

	/**
	 Sets the flip pages speed, in seconds. If GetFlipPages() is true, the speed
	 that the pages flip is controlled by the flip pages speed setting.
	 
	 @param speed uint32: the speed that the pages flip, in seconds.
	 */
	virtual void SetFlipPagesSpeed(uint32 speed) = 0;
	
	/**
	 Gets the flip pages speed, in seconds.
	 
	 @return the flip pages speed, in seconds.
	 */
	virtual uint32 GetFlipPagesSpeed() const = 0;
	
	/**
	 Sets the page transition to use for all pages, overriding any page tranition 
	 set on a spread. If the parameter passed is kInvalidClass then no page 
	 transition will be used. If the parameter passed is kPageTransitionFromDocument
	 then the spread's page transition will be honored.
	 
	 @param pageTransition ClassID: the ClassID of the page tranition to use.
	 @see IPageTransitionFacade
	 @see IPageTransition
	 */
	virtual void SetPageTransitionOverride(const ClassID& pageTransition) = 0;
	
	/**
	 Gets the page transition ClassID that will be used for all pages exported,
	 overriding any page transition on a spread. If the ClassID is kInvalidClass
	 then no page transition will be used. If the ClassID is kPageTransitionFromDocument,
	 the spread's page transition will be used.
	 
	 @return ClassID of the page transition.
	 @see IPageTransitionFacade
	 @see IPageTransition
	 */
	virtual ClassID GetPageTransitionOverride() const = 0;
	
	/**
	 Button and Media
	 */
	enum InteractiveElements
	{
		kIncludeAll = 0,
		kAppearanceOnly
	};
	
	/**
	 Sets how to handle interactive elements such as buttons and media.
	 
	 @param iElements:	One of the InteractiveElements enum specifying how to handle buttons and media
	 */
	virtual void SetInteractiveElements(InteractiveElements iElements) = 0;
	
	/**
	 Gets the setting for how to handle interactive elements such as buttons and media.
	 
	 @return One of the InteractiveElements enum specifying what to do with buttons and media
	 */
	virtual InteractiveElements GetInteractiveElements() const = 0;

	/**
	 RasterCompression - Compression for rasters
	 */
	enum RasterCompression
	{
		kJPEGCompression = 0,
		kLosslessCompression,
		kAutomaticCompression
	};
	
	/**
	 Sets the preferred raster compression to be used for the export. Note that some 
	 compression types will be required in certain scenarios and that those will take 
	 precedence over the setting specified here. This will be used when no particular 
	 compression type is required.
	 
	 @param compression:	One of the RasterCompression enum specifying the preferred raster compression
	 */
	virtual void SetRasterCompression(RasterCompression compression) = 0;
	
	/**
	 Gets the preferred raster compression to be used for the export.
	 
	 @return One of the RasterCompression enum specifying the preferred raster compression
	 */
	virtual RasterCompression GetRasterCompression() const = 0;

	/**
	 JPEGQuality - JPEG quality
	 */
	enum JPEGQuality
	{
		kJPEGQuality_Minimum = 0,
		kJPEGQuality_Low,
		kJPEGQuality_Medium,
		kJPEGQuality_High,
		kJPEGQuality_Maximum
	};
	
	/**
	 Sets the quality to be used for JPEG compressed images during the export.
	 
	 @param quality		One of the JPEGQuality enum
	 */
	virtual void SetJPEGQuality(JPEGQuality quality) = 0;
	
	/**
	 Gets the quality to be used for JPEG compressed images during the export.
	 
	 @return One of the JPEGQuality enum
	 */
	virtual JPEGQuality GetJPEGQuality() const = 0;
	
	/**
	 Sets the resolution to use for the PDF export, in pixels per inch.
	 
	 @param	resolution uint32:	The resolution to use (ppi).
	 */
	virtual void SetResolution(uint32 resolution) = 0;
	
	/**
	 Gets the resolution to use for the PDF export, in pixels per inch.
	 
	 @return The resolution to use (ppi).
	 */
	virtual uint32 GetResolution() const = 0;
	
	/**
	 Sets whether to use tagged PDF structure for ordering tabs.
	 
	 @param useStructure	whether to use PDF structure for tab order.
	 */
	virtual void SetUsePDFStructureForTabs(bool16 useStructure) = 0;
	
	/**
	 Gets whether to use tagged PDF structure for ordering tabs.
	 
	 @return kTrue if using PDF structure for tab order.
	 */
	virtual bool16 GetUsePDFStructureForTabs() const = 0;

	/**
	 Display Title - Options for display title.
	*/
	enum DisplayTitle
	{
		kFileName = 0,
		kDocumentTitle
	};

	/**
	 Sets the display title for the PDF being exported.

	 @type DisplayTitle: One of the DisplayTitle enum specifying the display title to use.
	*/
	virtual void SetDisplayTitle(DisplayTitle title) = 0;

	/**
	 Gets the display title for the PDF being exported.

	 @return One of the DisplayTitle enum specifying the display title to use.
	*/
	virtual DisplayTitle GetDisplayTitle() const = 0;

	/**
	Sets the default document language for the PDF being exported.
	*/
	virtual void SetDefaultDocumentLanguage(const PMString& language) = 0;

	/**
	Gets the default document language for the PDF being exported.
	*/
	virtual PMString GetDefaultDocumentLanguage() const = 0;

	/**
	Sets whether to export single page PDF or not.
	*/
	virtual void SetExportSinglePagesPDF(bool16 exportSinglePagesPDF) = 0;

	/**
	Gets the exportSinglePagesPDF preference.
	*/
	virtual bool16 GetExportSinglePagesPDF() const = 0;

	/**
	Sets single pages PDF suffix to be used at the end of filenames.
	*/
	virtual void SetSinglePagesPDFSuffix(PMString suffix) = 0;

	/**
	Gets single pages PDF suffix to be used at the end of filename.
	*/
	virtual PMString GetSinglePagesPDFSuffix() const = 0;
};
