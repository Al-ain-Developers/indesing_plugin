//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXHTMLExportPrefs.h $
//  
//  Owner: Matt Phillips
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
#ifndef __IXHTMLExportPrefs__
#define __IXHTMLExportPrefs__

#include "IPMUnknown.h"
#include "IXMLExportOptions.h"

#include "HTMLEPubExportTypes.h"

#include "EBookExportID.h"

using namespace HTMLExport; 

class IXHTMLExportPrefs : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXHTMLEXPORTPREFS };

	// general options
	virtual ExportScope GetExportScope() const = 0;
	virtual void SetExportScope(ExportScope scope) = 0;

	virtual ExportOrder GetExportOrder() const = 0;
	virtual void SetExportOrder(ExportOrder order) = 0;

	virtual BulletOption GetBulletOption() const = 0;
	virtual void SetBulletOption(BulletOption option) = 0;

	virtual NumberingOption GetNumberingOption() const = 0;
	virtual void SetNumberingOption(NumberingOption option) = 0;

	virtual bool16 GetPreview() const = 0;
	virtual void SetPreview(bool16 preview) = 0;
	
	// SVG export type options
	virtual SVGExportType GetSVGExportType() const = 0;
	virtual void SetSVGExportType(SVGExportType type) = 0;

	// image option
	virtual ImageOption GetImageOption() const = 0;
	virtual void SetImageOption(ImageOption option) = 0;

	virtual bool16 GetLayoutAppearance() const = 0;
	virtual void SetLayoutAppearance(bool16 layoutFormat) = 0;

	virtual uint32 GetImagePPI() const = 0;
	virtual void SetImagePPI(uint32 ppi) = 0;

	virtual ImageSize GetImageSize() const = 0;
	virtual void SetImageSize(ImageSize option) = 0;

	virtual ImageAlignment GetImageAlignment() const = 0; 
	virtual void SetImageAlignment(ImageAlignment align) = 0; 

	virtual PMReal GetImageSpaceBefore() const = 0;
	virtual void SetImageSpaceBefore(const PMReal & before) = 0;

	virtual PMReal GetImageSpaceAfter() const = 0;
	virtual void SetImageSpaceAfter(const PMReal & after) = 0;

	/** The GetApplyImageASToAnchoredObject and SetApplyImageASToAnchoredObject methods are deprecated now.*/
	virtual bool16 GetApplyImageASToAnchoredObject() const = 0;
	virtual void SetApplyImageASToAnchoredObject(bool16 apply) = 0;

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

	virtual uint32 GetPNGCompression() const = 0;
	virtual void SetPNGCompression(uint32 compression) = 0;
	
	virtual bool16 GetIgnorePageitemImageSetting() const = 0;
	virtual void SetIgnorePageitemImageSetting(bool16 setting) = 0;

	virtual PMString GetServerPath() const = 0;
	virtual void SetServerPath(const PMString & path) = 0;

	virtual PMString GetImageExtension() const = 0;
	virtual void SetImageExtension(const PMString & ext) = 0;

	// advanced options
	virtual bool16 GetGenerateCSS() const = 0;
	virtual void SetGenerateCSS(bool16 css) = 0;

	virtual bool16 GetIncludeOverrides() const = 0;
	virtual void SetIncludeOverrides(bool16 overrides) = 0;

		// user specified CSS
	virtual K2Vector<PMString> GetCascadeStyleSheets() const = 0;
	virtual void SetCascadeStyleSheets(const K2Vector<PMString> & sheets) = 0;

		// user specified javascript
	virtual K2Vector<PMString> GetJavascripts() const = 0;
	virtual void SetJavascripts(const K2Vector<PMString> & scripts) = 0;

	/** Copies one set of prefs into another
		@param other IN The preferences to copy
	*/
	virtual void Copy(IXHTMLExportPrefs const * other) = 0;
	
	//Advanced options to generate Plain HTML
	virtual bool16 GetIncludeClassesInHTML() const = 0;
	virtual void SetIncludeClassesInHTML(bool16 includeClassesInHTML) = 0;
};


#endif // __IHTMLPGTExportPrefs__