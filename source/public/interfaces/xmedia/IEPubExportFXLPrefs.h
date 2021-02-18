//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IEPubExportFXLPrefs.h $
//  
//  Owner: Gang Xiao
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once
#ifndef __IEPubExportFXLPrefs_h__
#define __IEPubExportFXLPrefs_h__

//#include "IPMUnknown.h"
#include "IXMLExportOptions.h"

#include "HTMLEPubExportTypes.h"

#include "EBookExportID.h"

#include "K2Vector.h"

class IEPubExportFXLPrefs : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IEPUBEXPORTFXLPREFS };

	// general panel

	/** EPub cover option. None, first page, and external image.
	*/
	virtual HTMLExport::EBookCover GetEBookCoverOption() const = 0;
	virtual void SetEBookCoverOption(HTMLExport::EBookCover option) = 0;

	/** EPub cover image. Full path to external cover image file.
	*/
	virtual PMString GetCoverImage() const = 0;
	virtual void SetCoverImage(const PMString & image) = 0;

	/** InDesign TOC style used in generating EPub TOC.
	*/	
	virtual PMString GetTOCStyleName() const = 0;
	virtual void SetTOCStyleName(const PMString & name) = 0;

	// image option

	/** Specify image PPI (pixel per inch). 
	*/
	virtual uint32 GetImagePPI() const = 0;
	virtual void SetImagePPI(uint32 ppi) = 0;

	/** Please refer to IXMLExportOptions for detail for following functions.
	*/
	virtual IXMLExportOptions::ImageType GetImageType() const = 0;
	virtual void SetImageType(IXMLExportOptions::ImageType type) = 0;

	virtual IXMLExportOptions::PaletteType GetGIFPaletteType() const = 0;
	virtual void SetGIFPaletteType(IXMLExportOptions::PaletteType type) = 0;

	virtual bool16 GetGIFInterlaced() const = 0;
	virtual void SetGIFInterlaced(bool16 gif) = 0;

	virtual IXMLExportOptions::JPEGEncoding GetJPEGEncoding() const = 0;
	virtual void SetJPEGEncoding(IXMLExportOptions::JPEGEncoding encoding) = 0;

	virtual IXMLExportOptions::JPEGQuality GetJPEGQuality() const = 0;
	virtual void SetJPEGQuality(IXMLExportOptions::JPEGQuality quality) = 0;

	/** PNG compression level. Not exposed via UI. Internally set to 5.
	*/
	virtual uint32 GetPNGCompression() const = 0;
	virtual void SetPNGCompression(uint32 compression) = 0;
	
	// content options

	/** If true, use metadata stored in indd file to generate epub opf.
	*/
	virtual bool16 GetIncludeDocMetadata() const = 0;
	virtual void SetIncludeDocMetadata(bool16 include) = 0;

	/** Specify epub publisher.
	*/
	virtual PMString GetPublisherEntry() const = 0;
	virtual void SetPublisherEntry(const PMString & entry) = 0;

	/** Specify epub uuid.
	*/
	virtual PMString GetMetadataIdentifier() const = 0;
	virtual void SetMetadataIdentifier(const PMString & uuid) = 0;

	/** User specified cascade style sheets.
	*/
	virtual K2Vector<PMString> GetCascadeStyleSheets() const = 0;
	virtual void SetCascadeStyleSheets(const K2Vector<PMString> & sheets) = 0;

	/** User specified javascript (epub3 only).
	*/
	virtual K2Vector<PMString> GetJavascripts() const = 0;
	virtual void SetJavascripts(const K2Vector<PMString> & scripts) = 0;

	/** Copies one set of prefs into another
		@param other IN The preferences to copy
	*/
	virtual void Copy(IEPubExportFXLPrefs const * other) = 0;
	
	/** User specified title of the epub. If not specified by user, taken from XMP (if available).
	*/
	virtual PMString GetMetadataTitle() const = 0;
	virtual void SetMetadataTitle(const PMString & title) = 0;

	/** User specified creator of the epub. If not specified by user, taken from XMP (if available).
	*/
	virtual PMString GetMetadataCreator() const = 0;
	virtual void SetMetadataCreator(const PMString & creator) = 0;

	/** User specified date of the epub.
	*/
	virtual PMString GetMetadataDate() const  = 0;
	virtual void SetMetadataDate(const PMString & date) = 0;

	/** User specified description of the epub. If not specified by user, taken from XMP (if available).
	*/

	virtual PMString GetMetadataDescription() const = 0;
	virtual void SetMetadataDescription(const PMString & description) = 0;

	/** User specified rights of the epub. If not specified by user, taken from XMP (if available).
	*/

	virtual PMString GetMetadataRights() const = 0;
	virtual void SetMetadataRights(const PMString & rights) = 0;

	/** User specified subject of the epub. If not specified by user, taken from XMP (if available).
	*/
	virtual PMString GetMetadataSubject() const = 0;
	virtual void SetMetadataSubject(const PMString & subject) = 0;

	/** Page range to be exported
		options - kAllPages, kUseRange
	*/

	virtual HTMLExport::PageRangeFormat GetPageRangeFormat() const = 0;
	virtual void SetPageRangeFormat(HTMLExport::PageRangeFormat format) = 0;

	/**
		The actual pages to be exported if page range is selected for export
	*/

	virtual PMString GetPageRange() const = 0;
	virtual void SetPageRange(const PMString & range) = 0;


	/** Spread control options.
		options - kSpreadsBasedOnDocument, kSpreadsPhysical, kSpreadsSynthetic, kSpreadsNone
	*/
	virtual HTMLExport::SpreadControlOption GetSpreadControlOption() const = 0;
	virtual void SetSpreadControlOption(HTMLExport::SpreadControlOption option) = 0;

	/** User specified navigation Style
		options - no navigation, toc style navigation, file name navigation
	*/

	virtual HTMLExport::NavigationStyle GetNavigationStyle() const = 0;
	virtual void SetNavigationStyle(HTMLExport::NavigationStyle style) = 0;
};

#endif
