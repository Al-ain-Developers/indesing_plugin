//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IInCopyPDFExptLayoutData.h $
//  
//  Owner: Cindy Chen
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
#ifndef __IInCopyPDFExptLayoutData__
#define __IInCopyPDFExptLayoutData__

#include "IPMUnknown.h"
#include "IXferBytes.h"
#include "InCopyCoreID.h"
#include "PersistUIDList.h"
#include "PMString.h"
#include "PMReal.h"
#include "PMRect.h"
#include "IGenericSettings.h"

/**
 Interface that contains data items used to configure InCopy to export
 documents to PDF in layout mode.  The interface is persist to session workspace.

 InCopy using IInCopyGalleyPrintData to configure the pdf export dialog, 
 then copy the data into corresponding IPDFExportPrefs data fields, for the
 export command using IPDFExportPrefs.
*/
class IInCopyPDFExptLayoutData : public IPMUnknown
{
public:
enum	{	kDefaultIID = IID_IINCOPYPDFEXPTLAYOUTDATA };

enum {
		//scope
		kAllPages = 0,			// Ignore range string, use all pages of the document.
		kUseRange,				// Use range string.  The string must be specified with ordinal page numbers.
		kLastType = kUseRange
	};

	// Copy methods
	virtual void CopyData(IInCopyPDFExptLayoutData* copyFrom) = 0;
	
	// Change notification method
	virtual void Notify(void* changedBy = nil) = 0;

	// set methods
	virtual void SetPDFExLaunchAcrobat(const bool16 value) = 0;
	virtual void SetPDFExPageInfo(const bool16 value) = 0;
	virtual void SetPDFExReaderSpreads(const bool16 value) = 0;
	virtual void SetPDFExThumbnails(const bool16 value) = 0;
	virtual void SetPDFExLinearized(const bool16 value) = 0;
	virtual void SetPDFExAnnotationNotes(const bool16 value) = 0;
	virtual void SetPDFExAcrobatCompatibilityLevel(const int32 value) = 0;
	virtual void SetPDFExPageRangeFormat(const int32 format) = 0;
	virtual void SetPDFExPageRange(const PMString range) = 0;
	virtual void SetPDFExSubsetFontsThreshold(const int32 subsetFontsThreshold) = 0;
	//virtual void SetPDFExStandardsCompliance(const int32 standard) = 0;
	virtual void SetPDFExAddInteractiveElements(const bool16 add) = 0;
	virtual void SetContentToEmbed(const int32 content) = 0;

	// Get methods
	virtual bool16 GetPDFExLaunchAcrobat() const = 0;
	virtual bool16 GetPDFExPageInfo() const = 0;
	virtual bool16 GetPDFExReaderSpreads() const = 0;
	virtual bool16 GetPDFExThumbnails() const = 0;
	virtual bool16 GetPDFExLinearized() const = 0;
	virtual bool16 GetPDFExAnnotationNotes() const = 0;
	virtual int32 GetPDFExAcrobatCompatibilityLevel() const = 0;
	virtual int32 GetPDFExPageRangeFormat() const = 0;
	virtual PMString GetPDFExPageRange() const = 0;
	virtual int32 GetPDFExSubsetFontsThreshold() const = 0;
	//virtual int32 GetPDFExStandardsCompliance() const = 0;
	virtual bool16 GetPDFExAddInteractiveElements() const = 0;
	virtual int32 GetContentToEmbed() const = 0;
};

#endif

// End, IInCopyPDFExptLayoutData.h.
