//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IExportValidationCmdData.h $
//  
//  Owner: Chris Jones
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
#ifndef __IExportValidationCmdData__
#define __IExportValidationCmdData__

class RangeProgressBar;

#include "IPMUnknown.h"
#include "IXferBytes.h"
#include "PrintID.h"
#include "PersistUIDList.h"
#include "PMString.h"
#include "PMReal.h"
#include "PMRect.h"
#include "IGenericSettings.h"
#include "IOutputPages.h"
#include "IDocIterationProvider.h"
#include "IDocIterationResult.h"

/**
 Data interface to the export validation command.
 */
class IExportValidationCmdData: public IPMUnknown
{
public:
	enum	
	{	
		kDefaultIID = IID_IEXPORTVALIDATIONCMDDATA 
	};

	/**
	 Flags used to indicate what types of verification should be performed.
	 */
	enum ValidationFlags
	{
		/// Don't do any verification
		kVerifyNone						= 0x00000000,
		/// Verify that all of the links in the document are up to date
		kVerifyLinks					= 0x00000001,
		/// Verify that all of the fonts used in the document are present
		kVerifyFonts					= 0x00000002,
		/// Verify that there are no DCS pageitems
		kVerifyNoDCSPlates				= 0x00000004,
		/// Verify that only CMYK color is used in the document
		kVerifyOnlyCMYKColor			= 0x00000008,
		/// Verify that there are no blank pages in the document
		kVerifyHasNonBlankPages			= 0x00000010,
		/// Verify that there are no pageitems with an invalid PostScript language level
		kVerifyLanguageLevel			= 0x00000020,
		/// Verify that there are no pageitems with an apparently invalid PostScript language level (obsolete)
		kVerifyLanguageLevelMaybe		= 0x00000040,
		/// Verify that there are no pageitems using binary PostScript data
		kVerifyBinaryData				= 0x00000080,
		/// Verify that there are no pageitems that might be using binary PostScript data
		kVerifyBinaryDataMaybe			= 0x00000100,
		/// Verify that there are no multimedia pageitems using invalid coordinate transformations
		kVerifyMultiMediaTransforms		= 0x00000200,
		/// Verify that there are no multimedia pageitems with invalid clipping paths
		kVerifyMultiMediaClipping		= 0x00000400,
		/// Verify that there are no multimedia pageitems that cannot be supported in the selected PDF language level
		kVerifyMoviePDFCompat			= 0x00000800,
		/// Verify that there are no movie pageitems whose colorspaces cannot be represented with current PDF color settings
		kVerifyMoviePosterColorCompat	= 0x00001000,
		/// Verify that there are no movie pageitems whose embed settings are unsupported in the selected PDF language level
		kVerifyMovieEmbedCompat			= 0x00002000,
		/// Verify that there are no sound pageitems whose embed settings are unsupported in the selected PDF language level
		kVerifySoundEmbedCompat			= 0x00004000,
		/// Verify that the inks used in placed EPS files are valid
		kVerifyEPSInks					= 0x00008000,
		/// Verify that there are no Atmosphere pageitems that cannot be supported in the selected PDF language level
		kVerifyAtmospherePDFCompat		= 0x00010000,
		/// Verify that there are no problems with the blending colorspace
		kVerifyBlendingSpace			= 0x00020000,
		/// Verify that there is no overset text
		kVerifyOversetText				= 0x00040000,
		/// Verify that condition tags that are used have consistent visibilities
		kVerifyConditionTags			= 0x00080000,
		/// Verify special conditions related to SWF and XFL export
		kVerifyFlashExport				= 0x00100000,
		/// Verify xrefs' status is okay
		kVerifyXRefsStatus				= 0x00200000,
		/// Check for unsupported button actions when exporting to PDF
		kVerifyPDFButtonActions			= 0x00400000,
		/// Check for legacy media
		kVerifyLegacyMedia				= 0x00800000,
		/// Check for missing controller skins
		kVerifyControllerSkins			= 0x01000000,
		/// Verify that all of the links in the document, have their content ready
		kVerifyLinksContentAvailable		= 0x02000000,

		/// Perform all of the available verifications
		kVerifyAll						= 0xFFFFFFFF
	};

public:
	/**
	 Sets the flags used to determine what validation should be performed.
	 
	 @param nValidateFlags	IN A bitmap of validation options from the ValidationFlags enumeration
	 */
	virtual void SetValidateFlags( int32  nValidateFlags ) = 0;
	
	/**
	 Determines if the specified validation should be performed based on the
	 current validation flags.
	 
	 @return kTrue if the validation should be performed, else kFalse
	 */
	virtual bool16 ShouldValidate( int32 nFlag ) = 0;

	/**
	 Sets whether warnings should be shown for the specified validation failures.
	 
	 @param nFlags			IN A bitmap of validation options from the ValidationFlags enumeration
	 */
	virtual void SetShowWarnings( int32 nFlags ) = 0;
	
	/**
	 Determines if a warning should be shown for the specified validation flag.
	 
	 @return kTrue if a warning should be shown the specified validation flag
	 */
	virtual bool16 ShowWarning( int32 nFlag ) = 0;

	/**
	 Indicates that the specified validation type failed.
	 
	 @param nFlag			IN One of the validation options from the ValidationFlags enumeration
	 */
	virtual void SetValidationFailure( int32 nFlag ) = 0;
	
	/**
	 Determines whether the specified type failed validation.
	 
	 @param nFlag			IN One of the validation options from the ValidationFlags enumeration
	 @return kTrue if the specified failure occurred, else kFalse
	 */
	virtual bool16 GetValidationFailure( int32 nFlag ) = 0;

	/**
	 Sets whether the specified validation failure should cause further 
	 verification to be canceled.
	 
	 @param nFlag			IN One of the validation options from the ValidationFlags enumeration
	 */
	virtual void SetCanceled( int32 nFlag ) = 0;
	
	/**
	 Gets whether the specified validation failure should cause further 
	 verification to be canceled.
	 
	 @param nFlag			IN One of the validation options from the ValidationFlags enumeration
	 @return kTrue if further validation should be canceled
	 */
	virtual bool16 GetCancelled( int32 nFlag ) = 0;

	/**
	 Sets the bleed size to be used during validation.
	 
	 @param rectSize		IN The bleed size to use
	 */
	virtual void SetBleedSize( const PMRect& rectSize ) = 0;
	
	/**
	 Gets the bleed size to be used during validation.
	 
	 @return The bleed size to use
	 */
	virtual PMRect& GetBleedSize() = 0;

	/**
	 Sets whether spreads are enabled.
	 
	 @param bSpreads		IN The new enabled value
	 */
	virtual void SetSpreadsEnabled( bool16 bSpreads ) = 0;
	
	/**
	 Gets whether spreads are enabled.
	 
	 @return kTrue if spreads are enabled, else kFalse
	 */
	virtual bool16 SpreadsEnabled() = 0;

	/**
	 Sets the output pages to use during validation. Implicitly calls AddRef
	 on the output pages object.
	 
	 @param pOutputPages	IN The output pages to be used for validation
	 */
	virtual void SetOutputPages( IOutputPages* pOutputPages ) = 0;
	
	/**
	 Gets the output pages to use during validation. The returned pointer is
	 unowned and must not be released by the caller.
	 
	 @return The output pages to use for validation
	 */
	virtual IOutputPages* GetOutputPages() = 0;

	/**
	 Sets the drawing flags to be used while iterating through drawable 
	 pageitems. The values to be used are taken from IShape's drawing flags.
	 
	 @param nFlags			IN The drawing flags to use while iterating
	 @see IShape
	 */
	virtual void SetIterationFlags( int32 nFlags ) = 0;
	
	/**
	 Gets the drawing flags to be used while iterating through drawable
	 pageitems.
	 
	 @return The drawing flags to use while iterating
	 @see IShape
	 */
	virtual int32 GetIterationFlags() = 0;

	/**
	 Sets whether raster images are being omitted for output.
	 
	 @param b				IN kTrue if raster images are being omitted, else kFalse
	 */
	virtual void SetOmitBitmaps( bool16 b ) = 0;
	
	/**
	 Gets whether raster images are being omitted for output.
	 
	 @return kTrue if raster images are being omitted, else kFalse
	 */
	virtual bool16 GetOmitBitmaps() = 0;

	/**
	 Sets whether placed EPS files are being omitted for output.
	 
	 @param b				IN kTrue if placed EPS files are being omitted, else kFalse
	 */
	virtual void SetOmitEPS( bool16 b ) = 0;
	
	/**
	 Gets whether placed EPS files are being omitted for output.
	 
	 @return kTrue if placed EPS files are being omitted, else kFalse
	 */
	virtual bool16 GetOmitEPS() = 0;

	/**
	 Sets whether placed PDF files are being omitted for output.
	 
	 @param b				IN kTrue if placed PDF files are being omitted, else kFalse
	 */
	virtual void SetOmitPDF( bool16 b ) = 0;

	/**
	 Gets whether placed PDF files are being omitted for output.
	 
	 @return kTrue if placed PDF files are being omitted, else kFalse
	 */
	virtual bool16 GetOmitPDF() = 0;

	/**
	 Sets the selector for font download while printing.
	 
	 @param nFontDownload	IN The selector for font download while printing
	 @see IPrintData
	 */
	virtual void SetFontDownload( int32 nFontDownload ) = 0;
	
	/**
	 Gets the selector for font download while printing.
	 
	 @return The selector for font download while printing
	 @see IPrintData
	 */
	virtual int32 GetFontDownload() = 0;

	/**
	 Sets whether the output is for a placed INDD page.
	 @param b		IN kTrue if output is for a palced INDD page, else kFalse
	 */
	virtual void SetIsINDDPage( bool16 b ) = 0;

	/**
	 Gets whether output is for a placed INDD page.
	 @return kTrue if output is for a placed INDD page, else kFalse
	 */
	virtual bool16 GetIsINDDPage() const = 0;

	/**
	 Sets whether output is for a book.
	 
	 @param b		IN kTrue if output is for a book, else kFalse
	 */
	virtual void SetIsBook( bool16 b ) = 0;

	/**
	 Gets whether output is for a book.
	 
	 @return kTrue if output is for a book, else kFalse
	 */
	virtual bool16 GetIsBook() = 0;

	/**
	 Sets whether have guides or grids.
	 
	 @param b		IN kTrue if have guides or grids, else kFalse
	 */
	virtual void SetHasGuidesOrGrids( bool16 b ) = 0;

	/**
	 Gets whether have guides or grids.
	 
	 @return kTrue if have guides or grids, else kFalse
	 */
	virtual bool16 GetHasGuidesOrGrids() = 0;

	/**
	 Overrides error message for the specified validation type.
	 
	 @param nValidateFlags	IN The validation type to override
	 @param strMsg			IN The new error message for the validation type
	 */
	virtual void OverrideErrorMessage( int32 nValidateFlags, const PMString& strMsg ) = 0;

	/**
	 Gets the error message for the specified validation type.
	 
	 @param nValidateFlags	IN The validation type requested
	 @param strMsg			OUT The error message for the validation type
	 */
	virtual void GetErrorMessage( int32 nValidateFlags, PMString& strMsg ) = 0;

	/**
	 Sets the document iteration context for the validation.
	 
	 @param nContext		IN The context to use for the validation
	 */
	virtual void SetContext( IDocIterationProvider::IterationContext nContext ) = 0;
	
	/**
	 Gets the document iteration context for the validation.
	 
	 @return The context to use for the validation
	 */
	virtual IDocIterationProvider::IterationContext GetContext() = 0;

	/**
	 Sets the context specific data to use for the validation.
	 
	 NOTE: pData is not owned by this interface and must remain valid for the
	 duration of the validation pass.
	 
	 @param pData			IN Context specific data to use for the validation
	 */	 
	virtual void SetContextSpecificData( IPMUnknown* pData ) = 0;
	
	/**
	 Gets the context specific data to use for the validation.
	 
	 @return The context specific data to use for the validation
	 */
	virtual IPMUnknown* GetContextSpecificData() = 0;

	/**
	 Sets additional context specific data to use for the validation.
	 
	 NOTE: pData is not owned by this interface and must remain valid for the
	 duration of the validation pass.
	 
	 @param pData			IN Context specific data to use for the validation
	 */	 
	virtual void SetContextSpecificData2( IPMUnknown* pData ) = 0;

	/**
	 Gets additional context specific data to use for the validation.
	 
	 @return The context specific data to use for the validation
	 */
	virtual IPMUnknown* GetContextSpecificData2() = 0;

	/**
	 Sets the results of the iteration. Implicitly AddRef's the data.
	 
	 @param pData			IN The iteration results
	 */
	virtual void SetResult( IDocIterationResult* pData ) = 0;
	
	/**
	 Gets the results of the iteration. The returned interface is owned by this
	 object and must not be released by the caller.
	 
	 @return The results of the iteration
	 */
	virtual IDocIterationResult* GetResult() = 0;

	/**
	 Sets whether iteration is for InCopy galley view.
	 
	 @param nFlag			IN kTrue if iteration is for InCopy galley view
	 */
	virtual void SetInGalleyView( bool16 nFlag ) = 0;
	
	/**
	 Gets whether iteration is for InCopy galley view.
	 
	 @return kTrue if iteration is for InCopy galley view, else kFalse
	 */
	virtual bool16 GetInGalleyView() = 0;

	/**
	 Sets whether transparency is supported in the output scenario.
	 
	 @param bSupported		IN kTrue if transparency is supported in the output scenario
	 */
	virtual void SetSupportsTransparency( bool16 bSupported ) = 0;

	/**
	 Gets whether transparency is supported in the output scenario.
	 
	 @return kTrue if transparency is supported in the output scenario
	 */
	virtual bool16 GetSupportsTransparency() = 0;

	/**
	 Sets the PDF compatibility level.
	 
	 @param pdfVersion		IN The PDF compatibility level
	 @see IPDFExportPrefs::GetPDFExAcrobatCompatibilityLevel
	 */
	virtual void SetPDFCompatibilityLevel( int32 pdfVersion ) = 0;

	/**
	 Gets the PDF compatibility level.
	 
	 @return The PDF compatibility level
	 @see IPDFExportPrefs::GetPDFExAcrobatCompatibilityLevel
	 */
	virtual int32 GetPDFCompatibilityLevel() = 0;

	/**
	 Sets the Embed Media option (PDF only).
	 
	 @param mediaEmbedOption	IN The Embed Media option
	 @see IPDFExportPrefs::GetContentToEmbed
	 */
	virtual void SetMediaEmbedOption( int32 mediaEmbedOption ) = 0;

	/**
	 Gets the Embed Media option (PDF only).
	 
	 @return The Embed Media option
	 @see IPDFExportPrefs::GetContentToEmbed
	 */
	virtual int32 GetMediaEmbedOption() = 0;

	/**
	 Sets the PDF export output colorspace.
	 
	 @param colorSpace			IN The PDF export colorspace
	 @see IPDFExportPrefs::GetPDFExColorSpace
	 */
	virtual void SetPDFOutputColorSpace( int32 colorSpace ) = 0;

	/**
	 Gets the PDF export output colorspace.
	 
	 @return The PDF export colorspace
	 @see IPDFExportPrefs::GetPDFExColorSpace
	 */
	virtual int32 GetPDFOutputColorSpace() = 0;

	/**
	 Sets whether to use document bleed.
	 
	 @param bUseDocBleed		IN kTrue if should use document bleed
	 */
	virtual void SetUseDocumentBleed( bool16 bUseDocBleed ) = 0;

	/**
	 Gets whether to use document bleed.
	 
	 @return kTrue if should use document bleed
	 */
	virtual bool16 GetUseDocumentBleed() = 0;

	/**
	 Sets whether to include slug area.
	 
	 @param bIncludeSlugArea	IN kTrue if should include slug area
	 */
	virtual void SetIncludeSlugArea( bool16 bIncludeSlugArea ) = 0;

	/**
	 Gets whether to include slug area.
	 
	 @return kTrue if should include slug area
	 */
	virtual bool16 GetIncludeSlugArea() = 0;

	/**
	 Sets whether or not to collect page items with links.

	 @param collectLinks [IN]: kTrue to collect page items with links, kFalse otherwise.
	*/
	virtual void SetCollectLinks(bool32 collectLinks) = 0;

	/**
	 Gets whether or not to collect page items with links.

	 @return kTrue if collecting page items with links, kFalse otherwise.
	*/
	virtual bool32 GetCollectLinks() const = 0;
};

#endif


