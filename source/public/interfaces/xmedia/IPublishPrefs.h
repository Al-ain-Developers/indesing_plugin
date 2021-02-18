//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IPublishPrefs.h $
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
#ifndef __IPUBLISHPREFS__
#define __IPUBLISHPREFS__

#include "IPMUnknown.h"
#include "IXMLExportOptions.h"
#include "HTMLEPubExportTypes.h"
#include "EBookExportID.h"

static const char* kPublishExtPdfExport = "LastMile PDF export";
static const char* kPublishExtExportWarn = "LastMile warning dialog";

using namespace HTMLExport; 

class IPublishPrefs : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPUBLISHPREFS };

	//Get Set Export order
	virtual ExportOrder GetExportOrder() const = 0;
	virtual void SetExportOrder(ExportOrder order) = 0;
	//Get Set description
	virtual PMString GetDescription() const = 0;
	virtual void SetDescription(PMString& des) = 0;
	//Get/Set File Name
	virtual PMString GetFileName() const = 0;
	virtual void SetFileName(PMString& fileName) = 0;
	//Get/Set Page range
	virtual PMString GetPageRange() const = 0;
	virtual void SetPageRange(PMString& pageRange) = 0;
	//Get/set page range format
	virtual PageRangeFormat GetRangeFormat() const = 0;
	virtual void SetRangeFormat(PageRangeFormat rangeFormat) = 0;
	//Get/set export is page wise or spread wise.
	virtual int32 GetSpreadControl() const = 0;
	virtual void SetSpreadControl(int32 spreadControl) = 0;
	
	//Get/set gif interlaced
	virtual bool16 GetGIFInterlaced() const = 0;
	virtual void SetGIFInterlaced(bool16 gif) = 0;

	//Get/set cover options.
	virtual EBookCover GetCoverOptions() const = 0;
	virtual void SetCoverOptions(EBookCover coverOptions)= 0;
	//Get/set cover image path.
	virtual PMString GetCoverImage() const = 0; 
	virtual void SetCoverImage(const PMString & image) = 0; 
	//Get/set exported image ppi.
	virtual uint32 GetImagePPI() const = 0;
	virtual void SetImagePPI(uint32 ppi) = 0;
	//Get/set exported image format.
	virtual IXMLExportOptions::ImageType GetImageType() const = 0;
	virtual void SetImageType(IXMLExportOptions::ImageType type) = 0;
	//Get/Set GIF Palette type
	virtual IXMLExportOptions::PaletteType GetGIFPaletteType() const =0;
	virtual void SetGIFPaletteType(IXMLExportOptions::PaletteType type) =0;

	//Get/Set cover page 
	virtual PMString GetCoverPage() const =0;
	virtual void SetCoverPage(const PMString& pageNumber) =0;
	//Get/Set JPEG Quality
	virtual IXMLExportOptions::JPEGQuality GetJPEGQuality() const =0;
	virtual void SetJPEGQuality (const IXMLExportOptions::JPEGQuality qual) =0;
	//Get/Set JPEG Encoding
	virtual IXMLExportOptions::JPEGEncoding GetJPEGEncoding() const =0;
	virtual void SetJPEGEncoding(IXMLExportOptions::JPEGEncoding jpgEnc)=0;
	//Function to copy IPublishPrefs
	virtual void Copy(IPublishPrefs const * other) = 0;
};
#endif