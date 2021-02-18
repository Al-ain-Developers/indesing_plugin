//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLExportOptions.h $
//  
//  Owner: Ryan Gano
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
#ifndef __IXMLExportOptions__
#define __IXMLExportOptions__

#include "XMLID.h"
#include "IPMUnknown.h"
#include "IXMLOutStream.h"

//========================================================================================
// CLASS IXMLExportOptions
//========================================================================================
/** Interface for export preferences. To change preferences from client code,
	use kChangeXMLExportOptionsCmdBoss rather than calling mutators on this interface.
	

*/
class IXMLExportOptions : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXMLEXPORTOPTIONS };

    /** Supported image types. */
	typedef enum ImageType {
        kImageBest = 0,
        kImageJPEG,
        kImageGIF,
        kImagePNG
    } ImageType;

	/** JPEGEncoding */
	typedef enum	
	{
		kJPEGBaseline = 0,
		kJPEGProgressive
	} JPEGEncoding; 

	/** JPEGQuality */
	typedef enum
	{
		kJPEGLowQuality = 0,
		kJPEGMediumQuality,
		kJPEGGoodQuality,
		kJPEGMaxQuality
	} JPEGQuality;
	
	/** PaletteType (GIF)  */
	typedef enum
	{
		/** Tries to create an exact palette first.  If it cannot, an adaptive palette will be created.
		*/
		kAdaptivePalette = 0,			
		/** Use the Macintosh 256 entry system palette from Photoshop */
		kMacPalette,					 
		/** Use a 216 entry web safe color palette*/
		kWebPalette,
		/** Use the Windows 256 entry system palette from Photoshop */
		kWinPalette						
	} PaletteType;
	
	/** UntaggedTablesFormat */
	typedef enum
	{
		/** Don't export untagged tables. */
		kNone = 0,
		/** Export untagged tables as CALS XML. */
		kCALS
	} UntaggedTablesFormat;

	/** When rasterizing, the frame of reference for that rasterization. */
	typedef enum
	{
		/** Spread coords (the default) */
		kSpread,

		/** In item coordinates. */
		kItem,

		/** In frame coordinates if the item is a graphic; otherwise the item's coordinates. */
		kGraphicFrame,

		/** In frame coordinates if the item is a graphic; otherwise the item's coordinates. 
			Use frame pathBounds for clipping (instead of Printed bounding box) */
		kGraphicFrameWithoutStyle,
	} FrameOfReference;

	/**	Acccessor for property specifying whether to export from selection
		
		@return bool16 kTrue if should export from selection, kFalse otherwise
	 */
	virtual bool16 	GetExportFromSelected() const = 0;

	/**	Mutator  for property specifying whether to export from selection 
		@param exportFromSelected kTrue if should be exporting from selection
	 */
	virtual void 	SetExportFromSelected(bool16 exportFromSelected) = 0;


	/**	Accessor for encoding type	
		@return  IXMLOutStream::eEncodingType stored
	 */
	virtual IXMLOutStream::eEncodingType	GetEncodingType() const = 0;

	/**	Mutator for encoding type stored on this interface
		@param encodingType specify a new encoding type to store on this interface
	 */
	virtual void 	SetEncodingType(IXMLOutStream::eEncodingType encodingType) = 0;


	/**	Mutator for image setting; see IXMLExportUtils for information
		@param enable 
		@return  
	 */
	virtual void	EnableOptimizedImages(bool8 enable) = 0;

	/**	Mutator for image setting; see IXMLExportUtils for information
		@param enable 
		@return  
	 */
	virtual void	EnableFormattedImages(bool8 enable) = 0;

	/**	Mutator for image setting; see IXMLExportUtils for information
		@param enable 
	 */
	virtual void	EnableCopyOriginals(bool8 enable) = 0;

	/**	Mutator for image setting
		@param type specify how exported images should be represented
	 */
	virtual void	SetImageType(ImageType type) = 0;

	/**	Mutator for image setting; JPEG parameters
		@param encode what variant of JPEG encoding schemes to choose
		@param quality specifies quality level to use for exported JPEGs
	 */
	virtual void	SetJPEGOptions(JPEGEncoding encode, JPEGQuality quality) = 0;

	/**	Mutator for image setting; GIF parameters
		@param palette kind of palette (from PaletteType) to create on export
		@param interlaced whether interlaced GIFs created on export
	 */
	virtual void	SetGIFOptions(PaletteType palette, bool8 interlaced) = 0;
	
	
	/**	Mutator for image setting; PNG parameters
		@param compressionLevel 0..9 are allowed levels of compression with 9 being the highest compression.
	 */
	virtual void	SetPNGOptions(uint32 compressionLevel) = 0;

	/**	Accessor for property stored on this interface
		@return  bool8
	 */
	virtual bool8	IsEnabledOptimizedImages(void) const = 0;

	/**	Accessor for property stored on this interface
		@return bool8	
	 */
	virtual bool8	IsEnabledFormattedImages(void) const = 0;

	/**	Accessor for property stored on this interface
		@return bool8	
	 */
	virtual bool8	IsEnabledCopyOriginals() const = 0;

	/**	Accessor for ImageType stored on this interface
		@return ImageType 
	 */
	virtual ImageType GetImageType(void) const = 0;

	/**	Accessor for JPEG parameters stored on this interface
		@param encode [OUT]
		@param quality [OUT]
	 */
	virtual void	GetJPEGOptions(JPEGEncoding *encode, JPEGQuality *quality) const = 0;

	/**	Accessor for GIF parameters stored on this interface
		@param palette [OUT]
		@param interlaced [OUT]
	 */
	virtual void	GetGIFOptions(PaletteType *palette, bool8 *interlaced) const = 0;
	
	/**	Accessor for PNG parameters stored on this interface
		@param compressionLevel [OUT]
	 */
	virtual void	GetPNGOptions(uint32 *compressionLevel) const = 0;
	
	/** Mutator for specifying the desired export resolution for graphic types like jpeg and png.
		Actual output resolution may differ dependent on source image.
		@param resolution desired resolution (dpi)
	*/
	virtual void SetImagePPI(const PMReal &resolution) = 0;
	
	/** Accessor for retrieving desired resolution set in SetImagePPI().
		@return resolution current resolution setting
	*/
	virtual PMReal GetImagePPI() const = 0;

	/** Accessor for rasterization frame of reference. */
	virtual FrameOfReference GetFrameOfReference() const = 0;

	/** Mutator for rasterization frame of reference. */
	virtual void SetFrameOfReference(FrameOfReference x) = 0;

	/**	Acccessor for property whether to export ruby with the W3C markup
		
		@return bool16 kTrue if should export ruby, false otherwise
	 */
	virtual bool16 	GetExportRuby() const = 0;

	/**	Mutator for property whether to export ruby with the W3C markup
		@param exportRuby kTrue if exporting ruby
	 */
	virtual void 	SetExportRuby(bool16 exportRuby) = 0;

	/**	Acccessor for property whether to exclude a DTD reference on export
		
		@return bool16 kTrue if should DTD reference should be exluded on export, false otherwise
	 */
	virtual bool16 	GetExcludeDTD() const = 0;

	/**	Mutator for property whether to exclude a DTD reference on export
		@param exclude DTD kTrue if excluding DTD on export
	 */
	virtual void 	SetExcludeDTD(bool16 excludeDTD) = 0;
	
	/**	Acccessor for property specifying the format to use when exporting untagged tables.

		@return UntaggedTablesFormat The format to use when exporting untagged tables.
	 */
	virtual UntaggedTablesFormat 	GetExportUntaggedTablesFormat() const = 0;

	/**	Mutator for property specifying the format to use when exporting untagged tables.
		@param exportUntaggedTables The format to use when exporting untagged tables.
	 */
	virtual void 	SetExportUntaggedTablesFormat(UntaggedTablesFormat exportUntaggedTables) = 0;

	/**	Acccessor for property specifying whether to run an XSLT script during export. 
		This goes along with GetXSLTScriptFileName.
		@return kTrue if should be Running a Script, kFalse otherwise
	 */
	virtual bool16 GetRunScriptOnExport() const = 0;

	/**	Mutator for property specifying whether to run an XSLT script during export. 
		This goes along with SetXSLTScriptFileName.
		@param runScript kTrue if should be Running a Script
	 */
	virtual void SetRunScriptOnExport(bool16 runScript) = 0;

	/**	Acccessor for property specifying where the XSLT script is located. 
		This goes along with GetRunScriptOnExport.
		@return The filename of the script to run
	 */
	virtual IDFile GetXSLTScriptFileName() const = 0;

	/**	Mutator for property specifying where the XSLT script is located. 
		This goes along with SetRunScriptOnExport.
		@param fileName The filename of the script to run
	 */
	virtual void SetXSLTScriptFileName(IDFile fileName) = 0;
	/** Accessor for property specifying whether to export special characters as entities.
		@return bool16 kTrue if special characters are to be exported as entities.
	*/
	virtual bool16 GetExportCharacterReferences() const = 0;

	/** Mutator for property specifying whether to export special characters as references.
		@param exportReference kTrue to export references.
	*/
	virtual void 	SetExportCharacterReferences(bool16 exportReferences) = 0;
	
	/**	Set the state stored on this interface based off another similar interface
		@param otherOptions interface whose state we'll copy over to this
	 */
	virtual void Copy(IXMLExportOptions* otherOptions) = 0;

	/**	Set xScale, ysScale for the image which are exported. 
		@param xScale exported image's xScale
		@param yScale exported image's yscale
	 */
	virtual void SetImageScale(PMReal xScale = 1.0, PMReal yScale = 1.0) = 0;

	/**	Get xScale of the image
		@param xScale exported image's xScale
		@param yScale exported image's yScale 
	 */
	virtual void GetImageScale(PMReal &xScale, PMReal &yScale) const = 0;

};

#endif
