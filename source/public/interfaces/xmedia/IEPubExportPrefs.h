//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IEPubExportPrefs.h $
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
#ifndef __IEPubExportPrefs_h__
#define __IEPubExportPrefs_h__

//#include "IPMUnknown.h"
#include "IXMLExportOptions.h"

#include "HTMLEPubExportTypes.h"

#include "EBookExportID.h"

#include "K2Vector.h"

class IEPubExportPrefs : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IEPUBEXPORTPREFS };

	// general panel

	/** EPub version. epub2, epub3, and epub3+layout
	*/
	virtual HTMLExport::EBookFormat GetEBookFormat() const = 0;
	virtual void SetEBookFormat(HTMLExport::EBookFormat format) = 0;

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

	/** EPub margin. Unit is pixels.
	*/
	virtual PMReal GetMarginLeft() const = 0;
	virtual void SetMarginLeft(const PMReal & left) = 0;

	virtual PMReal GetMarginRight() const = 0;
	virtual void SetMarginRight(const PMReal & right) = 0;

	virtual PMReal GetMarginTop() const = 0;
	virtual void SetMarginTop(const PMReal & top) = 0;

	virtual PMReal GetMarginBottom() const = 0;
	virtual void SetMarginBottom(const PMReal & bottom) = 0;

	/** Content order. Layout, XML structure, and article panel.
	*/
	virtual HTMLExport::ExportOrder GetExportOrder() const = 0;
	virtual void SetExportOrder(HTMLExport::ExportOrder order) = 0;

	/** Export ID footnote after paragraph. Only applied to epub2 and epub3
	*/
	virtual bool16 GetFootnoteAfterPara() const = 0;
	virtual void SetFootnoteAfterPara(bool16 ft) = 0;

	/** Strip soft return. If not, soft return convert to <br />
	*/
	virtual bool16 GetRemoveSoftReturn() const = 0;
	virtual void SetRemoveSoftReturn(bool16 sr) = 0;

	/** Bullet export option. HTML unordered list or convert to text 
	*/
	virtual HTMLExport::BulletOption GetBulletOption() const = 0;
	virtual void SetBulletOption(HTMLExport::BulletOption option) = 0;

	/** Numbering export option. HTML ordered list or convert to text 
	*/
	virtual HTMLExport::NumberingOption GetNumberingOption() const = 0;
	virtual void SetNumberingOption(HTMLExport::NumberingOption option) = 0;

	// image option

	/** Keep image appearance in layout.
	*/
	virtual bool16 GetLayoutAppearance() const = 0;
	virtual void SetLayoutAppearance(bool16 layoutFormat) = 0;

	/** Specify image PPI (pixel per inch). 
	*/
	virtual uint32 GetImagePPI() const = 0;
	virtual void SetImagePPI(uint32 ppi) = 0;

	/** Specify image size, fixed or relative. Relative is restricted to certain case, eg it
		won't work if image is in table
	*/
	virtual HTMLExport::ImageSize GetImageSize() const = 0;
	virtual void SetImageSize(HTMLExport::ImageSize option) = 0;

	/** Specify image alignment (left/center/right).
	*/
	virtual HTMLExport::ImageAlignment GetImageAlignment() const = 0; 
	virtual void SetImageAlignment(HTMLExport::ImageAlignment align) = 0; 

	/** Space before image in pixel.
	*/
	virtual PMReal GetImageSpaceBefore() const = 0;
	virtual void SetImageSpaceBefore(const PMReal & before) = 0;

	/** Space after image in pixel.
	*/
	virtual PMReal GetImageSpaceAfter() const = 0;
	virtual void SetImageSpaceAfter(const PMReal & after) = 0;

	/** Apply page break to image if true.
	*/
	virtual bool16 GetUseImagePageBreak() const = 0;
	virtual void SetUseImagePageBreak(bool16 use) = 0;

	/** Page break type for image (before/after/both).
	*/
	virtual HTMLExport::PageBreak GetImagePageBreak() const = 0;
	virtual void SetImagePageBreak(HTMLExport::PageBreak imageBreak) = 0;

	/** The GetApplyImageASToAnchoredObject and SetApplyImageASToAnchoredObject methods are deprecated now.
		Apply image space and alignment option to anchored object. This will cause 
		image not exported as inline HTML. 
	*/
	virtual bool16 GetApplyImageASToAnchoredObject() const = 0;
	virtual void SetApplyImageASToAnchoredObject(bool16 apply) = 0;

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

	// SVG export type options
    virtual HTMLExport::SVGExportType GetSVGExportType() const = 0;
    virtual void SetSVGExportType(HTMLExport::SVGExportType type) = 0;

	/** PNG compression level. Not exposed via UI. Internally set to 5.
	*/
	virtual uint32 GetPNGCompression() const = 0;
	virtual void SetPNGCompression(uint32 compression) = 0;
	
	/** Ignore image export setting specified on pageitem.
	*/
	virtual bool16 GetIgnorePageitemImageSetting() const = 0;
	virtual void SetIgnorePageitemImageSetting(bool16 setting) = 0;

	// content options

	/** Split indd document into multiple html files if true.
	*/
	virtual bool16 GetBreakDocument() const = 0;
	virtual void SetBreakDocument(bool16 chunk) = 0;

	/** Paragraph style used to split indd document. If style name is empty and split 
		flag is true, use setting on tag mapping panel.
	*/
	virtual PMString GetBreakDocParaStyleName() const = 0;
	virtual void SetBreakDocParaStyleName(const PMString & name) = 0;

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

	/** Generate cascade style sheet
	*/
	virtual bool16 GetGenerateCSS() const = 0;
	virtual void SetGenerateCSS(bool16 content) = 0;

	/** Generate CSS for text formatting applied as override.
	*/
	virtual bool16 GetIncludeOverrides() const = 0;
	virtual void SetIncludeOverrides(bool16 overrides) = 0;

	/** Embed font into epub if true.
	*/
	virtual bool16 GetEmbedFont() const = 0;
	virtual void SetEmbedFont(bool16 embed) = 0;

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
	virtual void Copy(IEPubExportPrefs const * other) = 0;
	
	// image option
	virtual HTMLExport::ImageOption GetImageOption() const = 0;
	virtual void SetImageOption(HTMLExport::ImageOption option) = 0;

	/* footnote placement option 
	    After Story, After paragraph, inside popup
	*/
	virtual HTMLExport::FootnotePlacement GetFootnotePlacement() const = 0;
	virtual void SetFootnotePlacement(HTMLExport::FootnotePlacement footnotePlacement) = 0;

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

	/** For excluding class & id names, as well as remove extra div containers while exporting HTML and Reflowable EPUB,
		corresponding to the "Don't Include Classes in HTML" check in HTML and EBook Export
	*/

	virtual bool16 GetIncludeClassesInHTML() const = 0;
	virtual void SetIncludeClassesInHTML(bool16 includeClassesInHTML) = 0;
};

#endif


