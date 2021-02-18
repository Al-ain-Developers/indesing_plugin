//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPDFExportPrefs.h $
//  
//  Owner: Tommy Donovan
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
#ifndef __IPDFExportPrefs__
#define __IPDFExportPrefs__

#ifndef __ODFRC__	// when used for core resource compilation, provide just the parameter range constants

#include "PDFID.h"
#include "IGenericSettings.h"

class PDFSettings;
class POSObject;
class RangeProgressBar;
class IDocument;

#endif	// __ODFRC__

// not used
const PMReal kMinSampleRatioThreshold = 1.0;
// not used
const PMReal kMaxSampleRatioThreshold = 3.0;
const int32 kMinSampleColorImageRes = 9;
const int32 kMaxSampleColorImageRes = 2400;
const int32 kMinSampleGrayImageRes = 9;
const int32 kMaxSampleGrayImageRes = 2400;
const int32 kMinSampleMonoImageRes = 9;
const int32 kMaxSampleMonoImageRes = 2400;
const int32 kMinJPG2000TileSize = 128;
const int32 kMaxJPG2000TileSize = 2048;
const int32 kDefaultJPG2000TileSize = 256;	// used for Interactive PDF export

#ifndef __ODFRC__	// when used for core resource compilation, provide just the parameter range constants

/** IPDFExportPrefs contains the PDF export preferences.
*/
class IPDFExportPrefs : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPDFEXPORTPREFS };
	
	enum 
	{
		// not used
		kDontChange = -1,

		// Launch Acrobat Viewer
		kExportLaunchAcrobatON = 1,
		kExportLaunchAcrobatOFF,

		// Reader Spread
		kExportReaderSpreadsON = 1,
		kExportReaderSpreadsOFF,

		// PDF Thumbnails
		kExportThumbnailsON = 1,
		kExportThumbnailsOFF,

		// Linearized PDF
		kExportLinearizedON = 1,
		kExportLinearizedOFF,

		// Embed Fonts
		kExportEmbedFontsON = 1,
		kExportEmbedFontsOFF,

		// Subset Fonts
		kExportSubsetFontsON = 1,
		kExportSubsetFontsOFF,

		// Desired Color Output Space
		kExportPDFColorSpaceRGB = 1,
		kExportPDFColorSpaceCMYK,
		kExportPDFColorSpaceDIC,
		kExportPDFColorSpacePassthru,
		kExportPDFRepurposeColorSpaceRGB,
		kExportPDFRepurposeColorSpaceCMYK,
		kExportPDFColorSpaceGray,

		// Desired Destination Color Profile Selector.
		// These constants are used by SetPDFExDstProfileSelector, GetPDFExDstProfileSelector,
		// GetPDFXProfileSelector and SetPDFXProfileSelector.
		kExportPDFDestProfileNA = 1,		// only valid for kExportPDFColorSpacePassthru
		kExportPDFDestProfileMonitor,		// only valid for kExportPDFColorSpaceRGB
		kExportPDFDestProfileDocument,		// use doc RGB/CMYK (for ID 3.0 compatibility in Dest Profile only)
		kExportPDFDestProfileWorking,		// use working RGB/CMYK  (for ID 3.0 compatibility in Dest Profile only)
		kExportPDFDestProfileUseName,		// use Get/SetPDFExDstProfileName() or Get/SetPDFXProfileName()
		
		// ICC Profiles
		kExportIncludeICCProfilesON = 1,
		kExportIncludeICCProfilesOFF,
		kExportIncludeTaggedSourceProfiles,
		kExportIncludeRGBAndTaggedCMYKSourceProfiles,
		
		// Write OPI comments
		kExportOutputOPION = 1,
		kExportOutputOPIOFF,

		// Bitmap output options
		kExportBMSampleOmit_Inval = 1,	// Omit bitmaps with SetPDFExOmitBitmapImages(kExportOmitBitmapImagesON/OFF)
		kExportBMSampleHiRes,
		kExportBMSampleLowRes,
		
		// Compress line art and text
		kExportCompressLineArtAndTextON = 1,
		kExportCompressLineArtAndTextOFF,

		// Options to go with SetCompressionType and GetCompressionType (compressionType parameter).
		// kCompressNone = 0;		// don't compress - compatible with all versions of PDF and Acrobat.
		kCompressStructure = 1,		/*	Compress the objects, and ONLY the objects, that are 
										related to logical structure (e.g., tagged PDF).
										The result is compatible with any version of PDF or Acrobat,
										but the compressed objects are usable only in PDF 1.5 (Acrobat 6). */
		kCompressObjects,			/*	Compress objects, without restrictions about which objects to compress.
										The result is compatible only with PDF 1.5 (Acrobat 6) or greater. */

		// Image sampling options
		kExportSampleImagesNone = 1,
		kExportSampleImagesByDownsampling,
		kExportSampleImagesBySubsampling,
		kExportSampleImagesByBicubicDownsampling,

		// Image compression		
		kExportCompressImagesNone = 1,
		
		// Color and Grayscale Image compression options
		kExportCompressImagesAutoLZWJPEGHigh = 2,	// make sure it doesn't overlap w/ kExportCompressImagesNone
		kExportCompressImagesAutoLZWJPEGMedHigh,
		kExportCompressImagesAutoLZWJPEGMed,
		kExportCompressImagesAutoLZWJPEGMedLow,
		kExportCompressImagesAutoLZWJPEGLow,
		kExportCompressImagesManualJPEGHigh,
		kExportCompressImagesManualJPEGMedHigh,
		kExportCompressImagesManualJPEGMed,
		kExportCompressImagesManualJPEGMedLow,
		kExportCompressImagesManualJPEGLow,
		kExportCompressImagesManualLZW4Bit,
		kExportCompressImagesManualLZW8Bit,
		kExportCompressImagesManualJPEG2000High,
		kExportCompressImagesManualJPEG2000MedHigh,
		kExportCompressImagesManualJPEG2000Med,
		kExportCompressImagesManualJPEG2000MedLow,
		kExportCompressImagesManualJPEG2000Low,
		kExportCompressImagesManualJPEG2000Lossless,
			// Automatic (JPEG2000 + ZIP)
		kExportCompressImagesAutoJPXMaximum,		// Quality = 100  ...ManualJPEG2000High
		kExportCompressImagesAutoJPXedHigh,			// Quality = 75   ...ManualJPEG2000MedHigh
		kExportCompressImagesAutoJPXMedium,			// Quality = 50   ...ManualJPEG2000Med
		kExportCompressImagesAutoJPXMLow,			// Quality = 25   ...ManualJPEG2000MedLow
		kExportCompressImagesAutoJPXMinimum,		// Quality = 1    ...ManualJPEG2000Low
		kExportCompressImagesAutoJPXLossless,		//                ...ManualJPEG2000Lossless
		
		// Monochrome Image compression options
		kExportCompressImagesCCITTGroup4 = (2+65536),	// prevent overlap w/ color/grayscale compressions
		kExportCompressImagesCCITTGroup3,
		kExportCompressImagesZip,
		kExportCompressImagesRunLength,
		
		// Prepress options
		kExportBleedON = 1,
		kExportBleedOFF,
		kExportBleedMarksON = 1,
		kExportBleedMarksOFF,
		kExportCropMarksON = 1,
		kExportCropMarksOFF,
		kExportRegistrationMarksON = 1,
		kExportRegistrationMarksOFF,
		kExportColorBarsON = 1,
		kExportColorBarsOFF,
		kExportPageInfoON = 1,
		kExportPageInfoOFF,

		// Error reporting
		kExportErrorControlWarnAndContinue = 1,
		kExportErrorControlIgnore,
		kExportErrorControlCancelJob,

		// Include image data that is cropped out by
		// its frame
		kExportDisallowImageCropON = 1,
		kExportDisallowImageCropOFF,

		// Omit placed PDFs
		kExportOmitPDFON = 1,
		kExportOmitPDFOFF,

		// Omit placed EPSs
		kExportOmitEPSON = 1,
		kExportOmitEPSOFF,

		// Omit placed bitmap imagess
		kExportOmitBitmapImagesON = 1,
		kExportOmitBitmapImagesOFF,

		// Content Prefs
		kExportContentON = 1,
		kExportContentOFF,

		kInvalidView = -1,
		kPerFrameGridView = 0,
		kGridView = 1,
		kZNGridView = 2,
		kAlignmentGridView = 3,

		kAlways = 0,
		kWhenEmpty = 1,
		
		// Inc. Hyper Links
		kExportIncHyperLinksOFF = 0,
		kExportIncHyperLinksON, 
		
		// Export Layers
		kExportAllLayers			= 0, 
		kExportVisibleLayers,
		kExportVisiblePrintableLayers,

		kExportLegacy			= 1,
		kExportSimulatePress,
		kExportSimulateScreen,
		
		kPDFVersion12 = 12,		// This value for interop display only.  
		kPDFVersion13,
		kPDFVersion14,
		kPDFVersion15,
		kPDFVersion16,
		kPDFVersion17,
		
		// Additions for InDesign 3.0
		// Controls for standards compliance
		// TODO: Need to check that PDFX3 meets ISO acceptance with year of 2002
		kExportNoStandardsCompliance = 0,
		kExportPDFX1a2001,
		kExportPDFX32002,
		kExportPDFX1a2003,
		kExportPDFX32003,
		kExportPDFA,			// This value for interop display only
		kExportPDFX42010,
		
		// OutputCondition information required for PDF/X compliance
		kExportCustomOutputCondition = 0, // "Custom" use to indicate there is a profile enclosed
		kExportCGATSOutputCondition,	// CGATS TR001
		kExportNamedOutputCondition,	// Use Get/SetPDFExOutputConditionName
		
		kExportBlankRegistryName = 0,
		kExportICCRegistryName,		// www.color.org
		kExportCustomRegistryName,		// Use Get/SetPDFExOCRegistryName

		// Values to go with SetContentToEmbed and GetContentToEmbed.
		// NOTE: as of CS5, these settings are obsolete since Export to PDF for Print
		// does not output interactive elements. Instead use the IInteractivePDFExportFacade.
		kUseObjectSettings = 0,
		kLinkAll,
		kEmbedAll,

		// Magnification
		kExportMagnificationDefault = 0,
		kExportMagnificationActualSize,
		kExportMagnificationFitPage,
		kExportMagnificationFitWidth,
		kExportMagnificationFitHeight,
		kExportMagnificationFitVisible,
		kExportMagnification25percent,
		kExportMagnification50percent,
		kExportMagnification75percent,
		kExportMagnification100percent,

		// PageLayout
		kExportLayoutDefault = 0,
		kExportLayoutSinglePage,
		kExportLayoutSinglePageContinuous,
		kExportLayoutTwoUpFacing,
		kExportLayoutTwoUpFacingContinuous,
		kExportLayoutTwoUpCoverPage,
		kExportLayoutTwoUpCoverPageContinuous,

		// DisplayTitle
		kExportDisplayFileName = 0,
		kExportDisplayDocumentTitle
	};

	enum {  kCompressNone = 0,      // ordering of the color & grayscale compression type lists
			kCompressAutomatic,
			kCompressJPEG,
			kCompressZip,
			kCompressJPEG2000,
			kCompressAutomaticJPEG2000};
	enum {  kQualityNone = -1,
			kQualityMinimum = 0,    // ordering of the JPEG and JPEG2000 compression quality lists
			kQualityLow,
			kQualityMedium,
			kQualityHigh,
			kQualityMaximum,
			kQualityLossless};		// Lossless only applies to JPEG2000.
	enum {  kQuality4Bit = 0,       // ordering of the Zip compression quality list
			kQuality8Bit };
	enum {  //kCompressNone = 0,   // ordering of the monochrome compression type list
			kCompressGroup3 = 1,
			kCompressGroup4,
			kCompressMonoZip,
			kCompressRLE };
	enum {  kResampleNone = 0,      // ordering of the resampling type lists
		    kDownsample,
			kSubsample,
			kBicubicDownsample };
			
	/** Copy the specified preferences to this object.
		@param prefsToCopy is a pointer to the preferences to copy.
	*/
	virtual void CopyPrefs(IPDFExportPrefs const* prefsToCopy) = 0;

	/** Deprecated. Set the launch Acrobat after exporting preference. 
		Use IPDFPostProcessPrefs::SetViewAfterExport off the workspace instead.
		@param launchAcrobat is either kExportLaunchAcrobatON or kExportLaunchAcrobatOFF.
	*/
	virtual void SetPDFExLaunchAcrobat(int32 launchAcrobat) = 0; // Deprecated, use IPDFPostProcessPrefs off the workspace.

	/** Set the reader spreads preference. When true each PDF page is an InDesign spread.
		@param readerSpreads is either kExportReaderSpreadsON or kExportReaderSpreadsOFF.
	*/
	virtual void SetPDFExReaderSpreads(int32 readerSpreads) = 0;

	/** Set the thumbnails preference.  When true thumbnails are written to the PDF file.
		@param thumbnails is either kExportThumbnailsON or kExportThumbnailsOFF.
	*/
	virtual void SetPDFExThumbnails(int32 thumbnails) = 0;

	/** Set linearized preference.  When true the PDF file is linearized.
		@param linearized is either kExportLinearizedON or kExportLinearizedOFF.
	*/
	virtual void SetPDFExLinearized(int32 linearized) = 0;

	/** Not used. InDesign embeds fonts unless they are missing or protected.
	*/
	virtual void SetPDFExEmbedFonts(int32 embedFonts) = 0;

	/** Not used. InDesign subsets fonts it embeds depending on the threshold.
	*/
	virtual void SetPDFExSubsetFonts(int32 subsetFonts) = 0;

	/** Set subset fonts threshold preference.  This controls whether to embed a subset font
		or the complete font in the PDF file.
		@param subsetFontsThreshold glyph percentage. When the precent of glyphs 
		of the font used in the PDF file exceeds the specified percentage, the 
		completed font is embedded, otherwise a subsetted version is embedded.
	*/
	virtual void SetPDFExSubsetFontsThreshold(int32 subsetFontsThreshold) = 0;

	/** Set PDF color space preference. This is the color space used when exporting.
		@param colorSpace is one of the following values:
		kExportPDFColorSpaceRGB,
		kExportPDFColorSpaceCMYK,
		kExportPDFColorSpaceDIC,
		kExportPDFColorSpacePassthru,
		kExportPDFRepurposeColorSpaceRGB,
		kExportPDFRepurposeColorSpaceCMYK,
	*/
	virtual void SetPDFExColorSpace(int32 colorSpace) = 0;

	/** Set the include ICC profiles preference.
		@param includeICCProfiles is one of the following values:
		kExportIncludeICCProfilesON,
		kExportIncludeICCProfilesOFF,
		kExportIncludeTaggedSourceProfiles,
		kExportIncludeRGBAndTaggedCMYKSourceProfiles,
	*/
	virtual void SetPDFExIncludeICCProfiles(int32 includeICCProfiles) = 0;

	/** Not used.
	*/
	virtual void SetPDFExOutputOPI(int32 outputOPI) = 0;

	/** Not used.
	*/
	virtual void SetPDFExBitmapSampling(int32 bitmapSampling) = 0;

	/** Set compress line art and text preference.  This controls whether the PDF content streams are compressed.
		@param compressLineArtAndText is either kExportCompressLineArtAndTextON or kExportCompressLineArtAndTextOFF.
	*/
	virtual void SetPDFExCompressLineArtAndText(int32 compressLineArtAndText) = 0;

	/** Set color subsampling preference.  This controls the type of subsampling done for color images.
		@param sampleColorImages is one of the following:
		kExportSampleImagesNone,
		kExportSampleImagesByDownsampling,
		kExportSampleImagesBySubsampling,
		kExportSampleImagesByBicubicDownsampling.
	*/
	virtual void SetPDFExSampleColorImages(int32 sampleColorImages) = 0;

	/** Set gray subsampling preference.  This controls the type of subsampling done for gray images.
		@param sampleGrayImages is one of the following:
		kExportSampleImagesNone,
		kExportSampleImagesByDownsampling,
		kExportSampleImagesBySubsampling,
		kExportSampleImagesByBicubicDownsampling.
	*/
	virtual void SetPDFExSampleGrayImages(int32 sampleGrayImages) = 0;

	/** Set monochrome subsampling preference.  This controls the type of subsampling done for monochrome images.
		@param sampleMonoImages is one of the following:
		kExportSampleImagesNone,
		kExportSampleImagesByDownsampling,
		kExportSampleImagesBySubsampling,
		kExportSampleImagesByBicubicDownsampling.
	*/
	virtual void SetPDFExSampleMonoImages(int32 sampleMonoImages) = 0;

	/** Set the resolution of down sampled color images.
		@param colorImagesXRes is a value from kMinSampleColorImageRes to kMaxSampleColorImageRes.
	*/
	virtual void SetPDFExSampleColorImagesXRes(int32 colorImagesXRes) = 0;

	/** Set the resolution of down sampled color images.
		@param colorImagesYRes is a value from kMinSampleColorImageRes to kMaxSampleColorImageRes.
	*/
	virtual void SetPDFExSampleColorImagesYRes(int32 colorImagesYRes) = 0;

	/** Set the resolution of down sampled gray images.
		@param grayImagesXRes is a value from kMinSampleGrayImageRes to kMaxSampleGrayImageRes.
	*/
	virtual void SetPDFExSampleGrayImagesXRes(int32 grayImagesXRes) = 0;

	/** Set the resolution of down sampled gray images.
		@param grayImagesYRes is a value from kMinSampleGrayImageRes to kMaxSampleGrayImageRes.
	*/
	virtual void SetPDFExSampleGrayImagesYRes(int32 grayImagesYRes) = 0;

	/** Set the resolution of down sampled monochrome images.
		@param monoImagesXRes is a value from kMinSampleMonoImageRes to kMaxSampleMonoImageRes.
	*/
	virtual void SetPDFExSampleMonoImagesXRes(int32 monoImagesXRes) = 0;

	/** Set the resolution of down sampled monochrome images.
		@param monoImagesYRes is a value from kMinSampleMonoImageRes to kMaxSampleMonoImageRes.
	*/
	virtual void SetPDFExSampleMonoImagesYRes(int32 monoImagesYRes) = 0;

	/** Set the compression strategy to use for color images.
		@param compressColorImages see kExportCompressImages... values above.
	*/
	virtual void SetPDFExCompressColorImages(int32 compressColorImages) = 0;

	/** Set the compression strategy to use for gray images.
		@param compressGrayImages see kExportCompressImages... values above.
	*/
	virtual void SetPDFExCompressGrayImages(int32 compressGrayImages) = 0;

	/** Set the compression strategy to use for monochrome images.
		@param compressMonoImages see kExportCompressImages... values above.
	*/
	virtual void SetPDFExCompressMonoImages(int32 compressMonoImages) = 0;

	/** Set whether to include the bleed area in the PDF file.
		@param bleed is either kExportBleedON or kExportBleedOFF.
	*/
	virtual void SetPDFExBleed(int32 bleed) = 0;

	/** Set whether to include the bleed marks in the PDF file.
		@param bleedMarks is either kExportBleedMarksON or kExportBleedMarksOFF.
	*/
	virtual void SetPDFExBleedMarks(int32 bleedMarks) = 0;

	/** Set whether to include the crop marks in the PDF file.
		@param cropMarks is either kExportCropMarksON or kExportCropMarksOFF.
	*/
	virtual void SetPDFExCropMarks(int32 cropMarks) = 0;

	/** Set whether to include the registration marks in the PDF file.
		@param registrationMarks is either kExportRegistrationMarksON or kExportRegistrationMarksOFF.
	*/
	virtual void SetPDFExRegistrationMarks(int32 registrationMarks) = 0;

	/** Set whether to include the color bars in the PDF file.
		@param colorBars is either kExportColorBarsON or kExportColorBarsOFF.
	*/
	virtual void SetPDFExColorBars(int32 colorBars) = 0;

	/** Set whether to include the page information in the PDF file.
		@param pageInfo is either kExportPageInfoON or kExportPageInfoOFF.
	*/
	virtual void SetPDFExPageInfo(int32 pageInfo) = 0;

	/** Set the distance between the crop marks and the image area.
		@param printerMarksOffset distance value.
	*/
	virtual void SetPDFExPrinterMarksOffset(PMReal printerMarksOffset) = 0;

	/** Set how errors and warnings are displayed when exporting to PDF.
		@param errorControl is one of kExportErrorControlWarnAndContinue, kExportErrorControlIgnore, or
		kExportErrorControlCancelJob.
	*/
	virtual void SetPDFExErrorControl(int32 errorControl) = 0;

	/** Set whether to crop the image to the frame or to include the complete image.
		@param disallowImageCrop is either kExportDisallowImageCropON, or kExportDisallowImageCropOFF.
	*/
	virtual void SetPDFExDisallowImageCrop(int32 disallowImageCrop) = 0;

	/** Set the omit PDF images for OPI preference.
		@param omitPDF is either kExportOmitPDFON, or kExportOmitPDFOFF.
	*/
	virtual void SetPDFExOmitPDF(int32 omitPDF) = 0;

	/** Set the omit EPS images for OPI preference.
		@param omitEPS is either kExportOmitEPSON, or kExportOmitEPSOFF.
	*/
	virtual void SetPDFExOmitEPS(int32 omitEPS) = 0;

	/** Set the omit bitmap images for OPI preference.
		@param omitBitmapImages is either kExportOmitBitmapImagesON, or kExportOmitBitmapImagesON.
	*/
	virtual void SetPDFExOmitBitmapImages(int32 omitBitmapImages) = 0;
	
	/** Set whether to generate Tagged PDF.
		@param add is true to generate Tagged PDF.
	*/
	virtual void	SetAddStructure(bool16 add) = 0;
	
	/** Deprecated.
	*/
	virtual int32	GetPDFExLaunchAcrobat() const = 0;  // Deprecated, use IPDFPostProcessPrefs off the workspace.

	/** Get reader spreads preference.
		@return either kExportReaderSpreadsON or kExportReaderSpreadsOFF.
	*/
	virtual int32	GetPDFExReaderSpreads() const = 0;

	/** Get thumbnail generation preference.
		@return either either kExportThumbnailsON or kExportThumbnailsOFF.
	*/
	virtual int32	GetPDFExThumbnails() const = 0;

	/** Get linearized preference.
		@return either either kExportLinearizedON or kExportLinearizedOFF.
	*/
	virtual int32	GetPDFExLinearized() const = 0;

	/** Not used.
	*/
	virtual int32	GetPDFExEmbedFonts() const = 0;

	/** Not used.
	*/
	virtual int32	GetPDFExSubsetFonts() const = 0;

	/** Get the glyph percentage threshold.
		@return the glyph percentage.
	*/
	virtual int32	GetPDFExSubsetFontsThreshold() const = 0;

	/** Get the PDF color space.
		@return PDF color space, see kExportPDFColorSpace... values.
	*/
	virtual int32	GetPDFExColorSpace() const = 0;

	/** Get the include ICC profile preference.
		@return the include ICC profile.  See kExportInclude... values.
	*/
	virtual int32	GetPDFExIncludeICCProfiles() const = 0;

	/** Not used.
	*/
	virtual int32	GetPDFExOutputOPI() const = 0;

	/** Not used.
	*/
	virtual int32	GetPDFExBitmapSampling() const = 0;

	/** Get compress line art and text preference.
		@return either kExportCompressLineArtAndTextON or kExportCompressLineArtAndTextOFF.
	*/
	virtual int32	GetPDFExCompressLineArtAndText() const = 0;

	/** Get down sample color image preference.
		@return color image preference. See kExportSampleImages... values.
	*/
	virtual int32	GetPDFExSampleColorImages() const = 0;

	/** Get down sample gray image preference.
		@return gray image preference. See kExportSampleImages... values.
	*/
	virtual int32	GetPDFExSampleGrayImages() const = 0;

	/** Get down sample monochrome image preference.
		@return monochrome image preference. See kExportSampleImages... values.
	*/
	virtual int32	GetPDFExSampleMonoImages() const = 0;

	/** Get color down sample resolution preference.
		@return down sample resolution preference.
	*/
	virtual int32	GetPDFExSampleColorImagesXRes() const = 0;

	/** Get color down sample resolution preference.
		@return down sample resolution preference.
	*/
	virtual int32	GetPDFExSampleColorImagesYRes() const = 0;

	/** Get gray sample resolution preference.
		@return down sample resolution preference.
	*/
	virtual int32	GetPDFExSampleGrayImagesXRes() const = 0;

	/** Get gray sample resolution preference.
		@return down sample resolution preference.
	*/
	virtual int32	GetPDFExSampleGrayImagesYRes() const = 0;

	/** Get monochrome sample resolution preference.
		@return down sample resolution preference.
	*/
	virtual int32	GetPDFExSampleMonoImagesXRes() const = 0;

	/** Get monochrome sample resolution preference.
		@return down sample resolution preference.
	*/
	virtual int32	GetPDFExSampleMonoImagesYRes() const = 0;

	/** Get compression strategy to use for color images.
		@return compression strategy.  See kExportCompressImages... values.
	*/
	virtual int32	GetPDFExCompressColorImages() const = 0;

	/** Get compression strategy to use for gray images.
		@return compression strategy.  See kExportCompressImages... values.
	*/
	virtual int32	GetPDFExCompressGrayImages() const = 0;

	/** Get compression strategy to use for monochrome images.
		@return compression strategy.  See kExportCompressImages... values.
	*/
	virtual int32	GetPDFExCompressMonoImages() const = 0;

	/** Get whether to include bleed.
		@return include bleed preference.
	*/
	virtual int32	GetPDFExBleed() const = 0;

	/** Get include bleed marks preference.
		@return either kExportBleedMarksON or kExportBleedMarksOFF.
	*/
	virtual int32	GetPDFExBleedMarks() const = 0;

	/** Get include copy marks preference.
		@return either kExportCropMarksON or kExportCropMarksOFF.
	*/
	virtual int32	GetPDFExCropMarks() const = 0;

	/** Get include registration marks preference.
		@return either kExportRegistrationMarksON or kExportRegistrationMarksOFF.
	*/
	virtual int32	GetPDFExRegistrationMarks() const = 0;

	/** Get include color bars preference.
		@return either kExportColorBarsON or kExportColorBarsOFF.
	*/
	virtual int32	GetPDFExColorBars() const = 0;

	/** Get include page information preference.
		@return either kExportPageInfoON or kExportPageInfoOFF.
	*/
	virtual int32	GetPDFExPageInfo() const = 0;

	/** Get crop mark offset preference.
		@return crop mark offset.
	*/
	virtual PMReal	GetPDFExPrinterMarksOffset() const = 0;

	/** Get error control preference.
		@return either kExportErrorControlWarnAndContinue, kExportErrorControlIgnore, or
		kExportErrorControlCancelJob.
	*/
	virtual int32	GetPDFExErrorControl() const = 0;

	/** Get image crop to frame preference.
		@return either kExportDisallowImageCropON, or kExportDisallowImageCropOFF.
	*/
	virtual int32	GetPDFExDisallowImageCrop() const = 0;

	/** Get omit PDF for OPI preference.
		@return either kExportOmitPDFON, or kExportOmitPDFOFF.
	*/
	virtual int32	GetPDFExOmitPDF() const = 0;

	/** Get omit EPS for OPI preference.
		@return either kExportOmitEPSON, or kExportOmitEPSOFF.
	*/
	virtual int32	GetPDFExOmitEPS() const = 0;

	/** Get omit bitmap images for OPI preference.
		@return either kExportOmitBitmapImagesON, or kExportOmitBitmapImagesON.
	*/
	virtual int32	GetPDFExOmitBitmapImages() const = 0;

	/** Get Tagged PDF preference.
		@return true when generating Tagged PDF.
	*/
	virtual bool16	GetAddStructure() const = 0;

	// Added for Anna

	/** Set Acrobat compatibility level.
		@param appVersion is kPDFVersion12, kPDFVersion13, kPDFVersion14,
		kPDFVersion15, kPDFVersion16, or kPDFVersion17.  kPDFVersion12 is for interoperbility only.
	*/
	virtual void	SetPDFExAcrobatCompatibilityLevel(int32 appVersion) = 0;

	/** Get Acrobat compatibility level.
		@return kPDFVersion12, kPDFVersion13, kPDFVersion14,
		kPDFVersion15, kPDFVersion16, kPDFVersion17.  kPDFVersion12 is for interoperbility only.
	*/
	virtual int32	GetPDFExAcrobatCompatibilityLevel() const = 0;

	/** Set image resolution.
		@param resolution 72 to 4000.
	*/
	virtual void SetPDFExResolution(int32 resolution) = 0;

	/** Get image resolution.
		@return image resolution.
	*/
	virtual int32 GetPDFExResolution() const = 0;
	
	/** Set destination profile selector and name
	
		This is an atomic setter which replaces both the SetPDFExDstProfileSelector and
		SetPDFExDstProfileName interfaces which were available until InDesign 4.0.  Both
		values must be kept in sync for proper interchange with Distiller's edits to
		.joboptions files.
		
		@param selector value. See kExportPDFDestProfile... values.
		@param name of the profile.  This value is ignored if using a selector other
		than kExportPDFDestProfileUseName.  The effective profile is set instead.
	*/
	virtual void SetPDFExDstProfileSelectorAndName(int32 selector, const PMString &name) = 0;
	
	/** Set destination profile selector.
		Deprecated for InDesign 5.0.  See SetPDFExDstProfileSelectorAndName
		@param selector value.  See kExportPDFDestProfile... values.
	virtual void SetPDFExDstProfileSelector(int32 selector) = 0;
	*/

	/** Get destination profile selector.
		@return selector value.  See kExportPDFDestProfile... values.
	*/
	virtual int32 GetPDFExDstProfileSelector() const = 0;
	
	/** Set destination profile name. This applies when the destination selector is use name.
		Deprecated for InDesign 5.0.  See SetPDFExDstProfileSelectorAndName
		@param name of the profile.
	virtual void SetPDFExDstProfileName(const PMString &name) = 0;
	*/

	/** Get destination profile name. This applies when the destination selector is use name.
		@return name of the profile.
	*/
	virtual PMString GetPDFExDstProfileName() const = 0;
	
	/** Get destination profile name. 
	    This returns the resulting profile after mapping the selector value to an actual profile.
		@return name of the profile.
	*/
	virtual PMString GetEffectiveDstProfileName() const = 0;
	
	/** Set include hyperlinks preference.
		@param incHyperLinks either kExportIncHyperLinksON or kExportIncHyperLinksOFF.
	*/
	virtual void SetPDFExIncHyperLinks(int32 incHyperLinks) = 0;

	/** Get include hyperlinks preference.
		@return either kExportIncHyperLinksON or kExportIncHyperLinksOFF.
	*/
	virtual int32 GetPDFExIncHyperLinks() const = 0;
	
	/** Set mark line weight preference.
		@param markLineWeight one of the following values:
		0.125
		0.25
		0.50
		(0.05 / 25.4) * 72.0)
		(0.07 / 25.4) * 72.0)
		(0.10 / 25.4) * 72.0)
		(0.15 / 25.4) * 72.0)
		(0.20 / 25.4) * 72.0)
		(0.30 / 25.4) * 72.0)
	*/
	virtual void SetPDFExMarkLineWeight(const PMReal &markLineWeight) = 0;

	/** Get mark line weight preference including Japanese.  This is done
		to allow scripting to get the same value as the put.  Previously the put did
		not restrict the value to match the system locale but the get did (J has metric values
		in addition to Roman).  If a script put a J value it would be stored but was returned
		as the nearest matching R value if the locale was R. The DOM now controls the legality
		of the enum, not the scripting methods.  Bug #1147387.
		@return line weight.
	*/
	virtual PMReal GetPDFExMarkLineWeightJ() const = 0;

	/** Get mark line weight preference.  This call will return the closest value to a legal
		value based on system locale.  A valid Japanese value (J is a superset of R - see call above)
		will only be returned if the system locale is J.
		@return line weight.
	*/
	virtual PMReal GetPDFExMarkLineWeight() const = 0;
	
	/** Set bleed top offset preference.
		@param bleedTop is the top offset.
	*/
	virtual void SetPDFExBleedTop(const PMReal &bleedTop) = 0;

	/** Get bleed top offset preference.
		@return bleed top offset.
	*/
	virtual PMReal GetPDFExBleedTop() const = 0;
	
	/** Set bleed inside offset preference.
		@param bleedInside is the inside offset.
	*/
	virtual void SetPDFExBleedInside(const PMReal &bleedInside) = 0;

	/** Get bleed inside offset preference.
		@return bleed inside offset.
	*/
	virtual PMReal GetPDFExBleedInside() const = 0;
	
	/** Set bleed bottom offset preference.
		@param bleedBottom is the bottom offset.
	*/
	virtual void SetPDFExBleedBottom(const PMReal &bleedBottom) = 0;

	/** Get bleed bottom offset preference.
		@return bleed bottom offset.
	*/
	virtual PMReal GetPDFExBleedBottom() const = 0;
	
	/** Set bleed outside offset preference.
		@param bleedOutside is the outside offset.
	*/
	virtual void SetPDFExBleedOutside(const PMReal &bleedOutside) = 0;

	/** Get bleed outside offset preference.
		@return bleed outside offset.
	*/
	virtual PMReal GetPDFExBleedOutside() const = 0;
	
	/** Set spot over print preference.
		@param spotOverPrint is kExportLegacy, kExportSimulatePress, or	kExportSimulateScreen.
	*/
	virtual void SetPDFExSpotOverPrint(int32 spotOverPrint) = 0;

	/** Get spot over print preference.
		@return kExportLegacy, kExportSimulatePress, or	kExportSimulateScreen.
	*/
	virtual int32 GetPDFExSpotOverPrint() const = 0;

	/** Get flattener preset UID for the associated flattener preset name.
		@return UID of flattener preset.
	*/
	virtual UID GetPDFExFlattenerStyle() const = 0;

	/** Set the associated flattener preset name.
		@param strStyle is the name of a flattener preset.
	*/
	virtual void SetPDFExFlattenerStyleName(const PMString& strStyle) = 0;

	/** Get the associated flattener preset name.
		@return UID of flattener preset.
	*/
	virtual PMString GetPDFExFlattenerStyleName() const = 0;

	/** Set the preference to ignore flattener spread overrides.
		@param ignore is true to ignore flattener spread overrides.
	*/
	virtual void SetPDFExIgnoreFlattenerSpreadOverrides(bool16 ignore) = 0;

	/** Get the preference to ignore flattener spread overrides.
		@return true when ignore flattener spread overrides.
	*/
	virtual bool16 GetPDFExIgnoreFlattenerSpreadOverrides() const = 0;

	/** Set include bookmarks preference.
		@param add is true to include bookmarks in the PDF.
	*/
	virtual void SetIncludeBookmarks(bool32 add) = 0;

	/** Get include bookmarks preference.
		@return include bookmarks preference.
	*/
	virtual bool32 GetIncludeBookmarks() const = 0;
	
	/** Set include non-printing objects preference.
		@param checked is true to include non-printing objects in the PDF.
	*/
	virtual void SetNonprintingObjects(bool32 checked) = 0;

	/** Get include non-printing objects preference.
		@return include non-printing objects preference.
	*/
	virtual bool32 GetNonprintingObjects() const = 0;

	/** Set include visible guides and grids preference.
		@param checked is true to include visible guides and grids in the PDF.
	*/
	virtual void SetVisibleGuidesGrids(bool32 checked) = 0;

	/** Get include visible guides and grids preference.
		@return include visible guides and grids.
	*/
	virtual bool32 GetVisibleGuidesGrids() const = 0;

	// Added for InDesign 3.0

	/** Set standard compliance level to use in the PDF.
		@param standardLevel is the standard compliance level. One of these values:
		kExportNoStandardsCompliance,
		kExportPDFX1a2001,
		kExportPDFX32002,
		kExportPDFX1a2003,
		kExportPDFX32003,
		kExportPDFA, kExportPDFA value is for interoperbility display only.
		kExportPDFX42010.
	*/
	virtual void SetPDFExStandardsCompliance(int32 standardLevel) = 0;

	/** Get the standard compliance level.
		@return standard compliance level.
	*/
	virtual int32 GetPDFExStandardsCompliance(void) const = 0;

	/** Set the output condition identifier.
		@param name of the output condition identifier.
	*/
	virtual void SetPDFExOutputConditionName(PMString name) = 0;

	/** Get the output condition identifier.
		@return output condition identifier.
	*/
	virtual PMString GetPDFExOutputConditionName() const = 0;
	
	/** Get the output condition identifier.
	    Returns a known condition if the effective output intent profile maps to one.
	    Otherwise the name specfied in the preset is returned.
		@return output condition identifier.
	*/
	virtual PMString GetEffectivePDFXOutputConditionName() const = 0;
	
	/** Set the output condition registry name.
		@param name of the output condition registry.
	*/
	virtual void SetPDFExOCRegistryName(PMString name) = 0;

	/** Get the output condition registry name.
		@return the name of the output condition registry name.
	*/
	virtual PMString GetPDFExOCRegistryName() const = 0;
	
	/** Get the output condition registry name.  This returns the
	    known condition associated with an output intent profile identified by the
	    selector value.
		@return the name of the output condition registry name.
	*/
	
	virtual PMString GetEffectivePDFXOCRegistryName() const = 0;
	
	/** Set the include interactive elements preference.
		NOTE: As of CS5, Export to PDF for Print does not export interactive elements.
		To export create an interactive PDF, use Export PDF (Interactive). The
		SetPDFExAddInteractiveElements preference here now maps to the Interactive
		Elements choice in the UI. If TRUE, interactive elements are drawn as 
		'Appearance Only'. If FALSE, interactive elements are set to 'Do Not Include'.
		@param addIElems is true to include interactive elements.
	*/
	virtual void SetPDFExAddInteractiveElements(bool16 addIElems) = 0;

	/** Get the include interactive elements preference.
		NOTE: As of CS5, Export to PDF for Print does not export interactive elements.
		To export create an interactive PDF, use Export PDF (Interactive). The
		GetPDFExAddInteractiveElements preference here now maps to the Interactive
		Elements choice in the UI. If TRUE, interactive elements are drawn as 
		'Appearance Only'. If FALSE, interactive elements are set to 'Do Not Include'.
		@return include interactive elements.
	*/
	virtual bool16 GetPDFExAddInteractiveElements() const = 0;
	
	/** Get the associated IGenericSettings interface.
		@return associated IGenericSettings interface.
	*/
	virtual IGenericSettings* GetSettings( bool16 fShowSecurity = kFalse, bool16 bShowDescriptionAndWarnings = kFalse, IDocument *iDoc = nil) const = 0;

	/** Set the progress bar to use.
		@param pProgress is the progress bar.
	*/
	virtual void SetProgress( RangeProgressBar* pProgress ) = 0;

	/** Get the progress bar.
		@return the progress bar.
	*/
	virtual RangeProgressBar* GetProgress() const = 0;

	/** Set the name of the page mark file to use.
		@param pageMarkFile is the name of the page mark file.

		There are three special names.
		1. The empty string means to use the default,
		2. "kJMarksWithCircle" means to use the Japanese mark file containing circles,
		3. "kJMarksWithoutCircle" means to use the Japanese mark file without circles.
		The name must not be translated (the translated bit is 0).

		For the other cases, pass the file name part without the path and extension.
		Page mark files reside in the common Adobe PrintSpt folder.
	*/
	virtual void SetPageMarkFile(const PMString& pageMarkFile) = 0;

	/** Get the page mark file.
		@return the page mark file.
	*/
	virtual PMString GetPageMarkFile() const = 0;

	/** Set the include layers in the PDF file.
		@param includeLayers is true to include layers.
	*/
	virtual void SetIncludeLayers(bool32 includeLayers) = 0;

	/** Get the include layers preference.
		@return the include layers preference.
	*/
	virtual bool32 GetIncludeLayers() const = 0;

	/**	Set which layers will export
		@param exportLayers	IN one of kExportAllLayers, kExportVisibleLayers, kExportVisiblePrintableLayers
	*/
	virtual void SetExportLayers(const int32 exportLayers) = 0;

	/**	Get which layers will export
		@return one of kExportAllLayers, kExportVisibleLayers, kExportVisiblePrintableLayers
	*/
	virtual int32 GetExportLayers() const = 0;

	/** Set the color resolution threshold. Images above this resolution are compressed.
		@param dpi is the resolution to use. It is a value from the image resolution 
		(see SetPDFExSampleColorImagesXRes) to ten times the image resolution.
	*/
	virtual void SetCompressColorAbove(int32 dpi) = 0;

	/** Get the color resolution threshold.
		@return the resolution.
	*/
	virtual int32 GetCompressColorAbove() const = 0;

	/** Set the gray resolution threshold. Images above this resolution are compressed.
		@param dpi is the resolution to use. It is a value from the image resolution 
		(see SetPDFExSampleGrayImagesXRes) to ten times the image resolution.
	*/
	virtual void SetCompressGrayAbove(int32 dpi) = 0;

	/** Get the gray resolution threshold.
		@return the resolution.
	*/
	virtual int32 GetCompressGrayAbove() const = 0;

	/** Set the monochrome resolution threshold. Images above this resolution are compressed.
		@param dpi is the resolution to use. It is a value from the image resolution 
		(see SetPDFExSampleMonoImagesXRes) to ten times the image resolution.
	*/
	virtual void SetCompressMonochromeAbove(int32 dpi) = 0;

	/** Get the monochrome resolution threshold.
		@return the resolution.
	*/
	virtual int32 GetCompressMonochromeAbove() const = 0;

	/** Set the color tile size to use with JPEG2000 compression.
		@param dpi is the tile size, a value from kMinJPG2000TileSize to kMaxJPG2000TileSize.
	*/
	virtual void SetColorTileSize(int32 dpi) = 0;

	/** Get the color tile size.
		@return the tile size.
	*/
	virtual int32 GetColorTileSize() const = 0;

	/** Set the gray tile size to use with JPEG2000 compression.
		@param dpi is the tile size, a value from kMinJPG2000TileSize to kMaxJPG2000TileSize.
	*/
	virtual void SetGrayTileSize(int32 dpi) = 0;

	/** Get the gray tile size.
		@return the tile size.
	*/
	virtual int32 GetGrayTileSize() const = 0;

	/** Set the use document bleed preference.
		@param documentBleed is true to use the document bleed values.
	*/
	virtual void SetUseDocumentBleed(bool32 documentBleed) = 0;

	/** Get the use document bleed preference.
		@return use the document bleed preference.
	*/
	virtual bool32 GetUseDocumentBleed() const = 0;

	/** Set include slug preference.
		@param includeSlug is true to include the slug area in the PDF.
	*/
	virtual void SetIncludeSlug(bool32 includeSlug) = 0;

	/** Get include slug preference.
		@return include slug preference.
	*/
	virtual bool32 GetIncludeSlug() const = 0;

	/** Set interactive content to embed.
		NOTE: as of CS5, SetContentToEmbed is obsolete since Export to PDF for Print
		does not output interactive elements. Instead use the IInteractivePDFExportFacade.
		@param contentToEmbed is kUseObjectSettings, kLinkAll, or kEmbedAll.
	*/
	virtual void SetContentToEmbed(int32 contentToEmbed) = 0;

	/** Get interactive content to embed.
		NOTE: as of CS5, GetContentToEmbed is obsolete since Export to PDF for Print
		does not output interactive elements. Instead use the IInteractivePDFExportFacade.
		@return interactive content to embed.
	*/
	virtual int32 GetContentToEmbed() const = 0;

	/** Set the compression type to apply to the PDF file.
		@param compressionType is kCompressNone, kCompressStructure. kCompressObjects is not used.
	*/
	virtual void SetCompressionType(int32 compressionType) = 0;

	/** Get compression type.
		@return compression type.
	*/
	virtual int32 GetCompressionType() const = 0;

	/** Set PDFX Output Intent profile  selector and name
	
		This is an atomic setter which replaces both the SetPDFXProfileSelector and
		SetPDFXProfileName interfaces which were available until InDesign 4.0.  Both
		values must be kept in sync for proper interchange with Distiller's edits to
		.joboptions files.
		
		@param selector value. See kExportPDFDestProfile... values.
		@param name of the profile.  This value is ignored if using a selector other
		than kExportPDFDestProfileUseName.  The effective profile is set instead.
	*/
	virtual void SetPDFXProfileSelectorAndName(int32 selector, const PMString &name) = 0;
	
	/** Set PDF/X profile selector.
		Deprecated for InDesign 5.0.  See SetPDFXProfileSelectorAndName
		
		@param selector value.  See kExportPDFDestProfile... values.
		
	virtual void SetPDFXProfileSelector(int32 selector) = 0;
	*/

	/** Get PDF/X profile selector.
		@return selector value.  See kExportPDFDestProfile... values.
	*/
	virtual int32 GetPDFXProfileSelector() const = 0;
	
	/** Set PDF/X profile name. This applies when the selector is use name.
		Deprecated for InDesign 5.0.  See SetPDFXProfileSelectorAndName

		@param name of the profile.
	virtual void SetPDFXProfileName(const PMString &name) = 0;
	*/

	/** Get PDF/X profile name. This applies when the selector is use name.
		@return name of the profile.
	*/
	virtual PMString GetPDFXProfileName() const = 0;
	
	/** Get PDF/X profile name. This applies when the selector is use name.
		It returns the mapped profile if the selector references document or 
		working space rather than using a name directly.
		@return name of the profile.
	*/
	virtual PMString GetEffectivePDFXProfileName() const = 0;
	
	/** Set the description string.
		@param desc is the description string.
		@param langid is the language of the string.

		typedef enum {
			kLanguageENU = 1,
			kLanguageJPN,
			kLanguageDEU,
			kLanguageFRA,
			kLanguagePTB,
			kLanguageDAN,
			kLanguageNLD,
			kLanguageESP,
			kLanguageSUO,
			kLanguageITA,
			kLanguageNOR,
			kLanguageSVE,
			kLanguageCHS,
			kLanguageCHT,
			kLanguageKOR
		} LanguageID;
	*/
	virtual void SetTranslatedDescription(const PMString &desc, int32 langid) = 0;

	/** Get the description string for the specified language.
		@param langid of the string.
		@return the description string.
	*/
	virtual PMString GetTranslatedDescription(int32 langid) = 0;
	
	/** Set the output condition name.
		@param id is the output condition name.
	*/
	virtual void SetOutputConditionHumanReadable(const PMString &id) = 0;

	/** Get the output condition name.
		@return the output condition name.
	*/
	virtual PMString GetOutputConditionHumanReadable( ) const = 0;
	
	/** Read the preferences from the given PDF preset file to this object.
		@param presetFile is the preset file to read.
		@return kSuccess when successful.
	*/
	virtual ErrorCode ReadJobOptionsDataFromDisk(const IDFile &presetFile) = 0;

	/** Write a PDF preset file using current preferences.
		@param presetFile is the preset file to write.
		@return kSuccess when successful.
	*/
	virtual ErrorCode WriteJobOptionsDataToDisk(const IDFile &presetFile) = 0;

	/** Get the associated job options data.
		@return PDFSettings object.
	*/
	virtual PDFSettings* GetJobOptionsData() const = 0;

	/** Determine whether these preferences are valid. 
		@return true when the preferences are valid.
	*/
	virtual bool16 IsPresetUsable() const  = 0;

	/** Get the associated warning list object.
		@param document. The document used to determine working profiles. When it is non-nil, the 
		CMS on/off state is looked up and applies to the warnings. When nil, CMS is treated as if it is on.
		@return POSObject object.
	*/
	virtual POSObject *GetWarningList(IDocument const *document) const = 0;

	/** Get the associated preset filename without directory or extension information.

	There are three types of preset names.
	1. presetFilename returned from GetPresetFilename.
	   This is the name of the preset file on disk (without the directory or extension).
	2. uiName returned from GetUIName.
	   This is the name you see in the UI.  It has special characters replaces with underscores
	   and Read Only presets have bracket around them. Special names get translated, for example
	   "PDFX1a 2001" becomes "PDF/X-1a 2001".
	3. presetName returned from PDF style list manager.
		This is the name you get from the manager, it is the same as the uiName.

		@return the filename.
	*/
	virtual PMString GetPresetFilename() const = 0;
	
	/** Set the UI name for these preferences.
		@param name of these preferences.
	*/
	virtual void SetUIName(PMString const &name) = 0;

	/** Get the UI name for these preferences.
		@return the name of these preferences.
	*/
	virtual PMString GetUIName() const = 0;
	
	/** Get the associated preset file's modified time stamp.
		@return the time stamp.  See GlobalTime.h.
	*/
	virtual uint64 GetTimeStamp() const = 0;

	/** Method to stream in/out the preferences.
        @param iPMStream is the stream to read/write.
        @param prop is the implementation ID.
	*/ 
	virtual void ReadWrite (IPMStream* iPMStream, ImplementationID prop) = 0;
	
	/** Set the associated preset filename without path or extension information. Internal use only!
        @param filename is the filename to use.
	*/
	virtual void SetPresetFilename(PMString const &filename) = 0;
	
	/** Determine whether the user has modified the settings. This is reflected in the UI
		when (modified) is appended to the preset name.
		@return kTrue when the preferences have been modified.
	 */
	virtual bool16 IsModified() const = 0;

	/**	
	 Make the PDF preferences consistent for a document's CMS state.
	 
	 FixUpSettings is meant to ensure that settings are in a consistent state, especially with
	 regards to color conversion and color management options. It is called at various points 
	 in the export process, typically where we've read in a set of settings from a .joboptions
	 file on disk. InDesign will also call this at various places in the UI and scripting code
	 to ensure that changes made don't put things into an inconsistent state.

	 The document parameter to FixUpSettings is used to determine two things: First, whether
	 CMS is on in the specified document; and second, what the current CMYK and RGB working
	 profiles are. If the default nil value is used, InDesign uses profiles from the workspace
	 and makes the assumption that CMS is *on*. InDesign uses this information to apply 
	 various heuristics. At a 10K foot level, it: 
	 
	 1) Applies some basic fix ups related to obsolete keys or bogus entries. This is most 
	 relevant when a joboptions file is read in from disk, particularly when the source for 
	 that joboptions file is Distiller or an obsolete CS app. It is usually not necessary if 
	 the source is a CS app or if entries in the settings are programmatically edited.
	 
	 2) Fills in any default values that may be missing. Again, this is most common for files
	 read in from disk any is usually not required if entries are explicitly modified.
	 
	 3) Determines whether we should honor the so-called 'private dict' settings used by CS 
	 apps or the 'official' ones that Distiller uses. 
	 
	 The third item is the most important. The problem is that Distiller and the CS apps 
	 differ in the way CMS works and the joboptions parameters used to configure it. As a
	 result, CS apps must at times approximate the behavior implied by the Distiller settings.
	 The private dict settings reduce the problem somewhat by standardizing treatment of CMS-
	 related options across CS apps, but present a different problem in that CS apps must be
	 able to determine if a joboptions file has been edited in a way to invalidates the 
	 private settings. FixUpSettings accomplishes that.
	 
	 The recommendation is that a call to FixUpSettings be made after programmatically editing
	 an IPDFExportPrefs instance, particularly with options related to color conversion or 
	 color management. Whenever possible, this should include a pointer to the document to be
	 exported to ensure the correct working profiles are used and any necessary corrections
	 are made. It is also recommended - but not required - that a call to IsPresetUsable be
	 made to ensure that the settings instance is in a usable state.
	 
	 @param iDoc [IN, OPTIONAL] The associated document to use with these settings. A nil value (the default) indicates that there is
		no associated document and that the settings should behave as if CMS were on, using default profiles (as the preset editor does).
	 @param clearDirty [IN, OPTIONAL]. A value of true clears the use modified flag (makes IsModified return false).
	 
	 @return true when changes were made to the settings.
	 */
	virtual bool32 FixUpSettings(IDocument *iDoc = nil, bool32 clearDirty = kFalse) = 0;

	/** Get the pristine job option preferences.  These settings reflect the preferences on disk before fixups.
		@return PDFSettings object.
	 */
	virtual PDFSettings* GetPristineJobOptionsData() const = 0;

	/** The following flattener settings get methods are used to create a flattener preset
		when the PDF preset is added to the PDF preset list.  When you change
		the flattener name with SetPDFExFlattenerStyleName all these settings
		are changed to match the settings in the flattener style list.
		If there is no associated flattener setting, the default values are returned.
	*/

	/** Get the flattener raster vector balance (GetFlattenerLevel).
		@return the level.
	*/
	virtual PMReal GetFlattenerRasterVectorBalance() const = 0;		// GetFlattenerLevel

	/** Get the flattener line art text resolution (GetFlattenerExternalDPI).
		@return the resolution.
	*/
	virtual PMReal GetFlattenerLineArtTextResolution() const = 0;	// GetFlattenerExternalDPI

	/** Get the flattener gradient resolution (GetFlattenerInternalDPI).
		@return the resolution.
	*/
	virtual PMReal GetFlattenerGradientResolution() const = 0;		// GetFlattenerInternalDPI

	/** Get the flattener clip complex regions state (GetFlattenerFlags - IFlattenerSettings::kFlOptkClipComplexRegions).
		@return the state.
	*/
	virtual bool32 GetFlattenerClipComplexRegions() const = 0;		// GetFlattenerFlags - IFlattenerSettings::kFlOptkClipComplexRegions

	/** Get the flattener convert strokes to outlines state (GetFlattenerFlags - IFlattenerSettings::kFlOptkConvertStrokeToFill).
		@return the state.
	*/
	virtual bool32 GetFlattenerConvertStrokesToOutlines() const = 0;// GetFlattenerFlags - IFlattenerSettings::kFlOptkConvertStrokeToFill

	/** Get the flattener convert text to outlines state (GetFlattenerFlags - IFlattenerSettings::kFlOptUseTextOutlines).
		@return the state.
	*/
	virtual bool32 GetFlattenerConvertTextToOutlines() const = 0;	// GetFlattenerFlags - IFlattenerSettings::kFlOptUseTextOutlines

	/**
	 Sets the initial magnification when the PDF is opened.
	 
	 @param Magnification: One of the Magnification enum specifying the initial magnification to use.
	 */
	virtual void SetMagnification(int32 magnification) = 0;
	
	/**
	 Gets the initial magnification setting.
	 
	 @return One of the Magnification enum specifying the magnification to use.
	 */
	virtual int32 GetMagnification() const = 0;

	/**
	 Sets the page layout for the PDF being exported.
	 
	 @param PageLayout: One of the PageLayout enum specifying the page layout to use.
	 */
	virtual void SetPageLayout(int32 pageLayout) = 0;
	
	/**
	 Gets the page layout for the PDF being exported.
	 
	 @return One of the PageLayout enum specifying the page layout to use.
	 */
	virtual int32 GetPageLayout() const = 0;

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
	 Sets the display title for the PDF being exported.

	 @param title: One of the DisplayTitle enum specifying the title to use.
	*/
	virtual void SetDisplayTitle(int32 title) = 0;

	/**
	 Gets the display title for the PDF being exported.

	 @return One of the DisplayTitle enum specifying the document title to use.
	*/
	virtual int32 GetDisplayTitle() const = 0;

	/**
	Sets the default document language for the PDF being exported.
	*/
	virtual void SetDefaultDocumentLanguage(const PMString& language) = 0;

	/**
	Gets the default document language for the PDF being exported.
	*/
	virtual PMString GetDefaultDocumentLanguage () const = 0;

	/**
	Sets whether to export document in single pages PDF.

	@param exportSinglePages Boolean. If kTrue, document is exported in single pages PDF.
	*/
	virtual void SetExportSinglePagesPDF(bool16 exportSinglePages) = 0;

	/**
	Gets whether to export the document in single pages PDF.

	@return kTrue if PDF is to be exported in single pages.
	*/
	virtual bool16 GetExportSinglePagesPDF() const = 0;

	/**
	Sets the suffix to be used in PDF file names when exporting single pages PDF.

	@param singlePagesSuffix PMString. 
	*/
	virtual void SetSinglePagesPDFSuffix(PMString singlePagesSuffix) = 0;

	/**
	Gets the suffix to be used in PDF file names when exporting single pages PDF.
	*/
	virtual PMString GetSinglePagesPDFSuffix() const = 0;
};

#endif	// __ODFRC__

#endif
