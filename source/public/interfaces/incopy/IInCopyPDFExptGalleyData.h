//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IInCopyPDFExptGalleyData.h $
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
#ifndef __IInCopyPDFExptGalleyData__
#define __IInCopyPDFExptGalleyData__

#include "IPMUnknown.h"
#include "IXferBytes.h"
#include "InCopyCoreID.h"
#include "PersistUIDList.h"
#include "PMString.h"
#include "PMReal.h"
#include "PMRect.h"
#include "IGenericSettings.h"
#include "IInCopyGalleySettingData.h"

/**
 Interface that contains data items used to configure InCopy to export
 documents to PDF in galley mode.  The interface is persist to session workspace.

 InCopy using IInCopyGalleyPrintData to configure the pdf export dialog, 
 then copy the data into corresponding IPDFExportPrefs data fields, for the
 export command using IPDFExportPrefs.
*/

class IInCopyPDFExptGalleyData : public IPMUnknown
{
public:
enum	{	kDefaultIID = IID_IINCOPYPDFEXPTGALLEYDATA };

enum {
		//line range scope
		kAllLines = 0,			// Ignore range string, use all pages of the document.
		kUseRange,				// Use range string.  The string must be specified with ordinal page numbers.
		
		//the scope
		kAllStories = 0,
		kCurrentStory,
		kExpandedStory,

		//the Notes/Track changes
		kAll = 0,
		kVisible,

		//the column unit
		kInches = 0,
		kCentimeter
	};

	virtual bool16 GetIsDefaultValues() const = 0;

	// Copy/Initialization methods
	virtual void CopyData(IInCopyPDFExptGalleyData* copyFrom) = 0;
	// set the default setting from IInCopyGalleySettingData
	virtual void CopyDefault(IInCopyGalleySettingData* setting) = 0;

	// Change notification method
	virtual void Notify(void* changedBy = nil) = 0;

	// Set methods
	virtual void SetPDFExLaunchAcrobat(const bool16 value) = 0;
	virtual void SetPDFExPageInfo(const bool16 value) = 0;
	virtual void SetPDFExStyle(const bool16 value) = 0;
	virtual void SetPDFExLineNumber(const bool16 value) = 0;
	virtual void SetPDFExInlineNotes(const bool16 value) = 0;
	virtual void SetPDFExTrackChanges(const bool16 value) = 0;
	virtual void SetPDFExFill(const bool16 value) = 0;
	virtual void SetPDFExALE(const bool16 value) = 0;
	virtual void SetPDFExLineRangeFormat(const int32 value) = 0;
	virtual void SetPDFExLineRange(const PMString value) = 0;
	virtual void SetPDFExAcrobatCompatibilityLevel(const int32 value) = 0;
	virtual void SetPDFExFont(const PMString value) = 0;
	virtual void SetPDFExFontType(const PMString value) = 0;
	virtual void SetPDFExFontSize(const PMString value) = 0;
	virtual void SetPDFExFontLeading(const PMString value) = 0;
	virtual void SetPDFExColumnWidth(const PMReal value) = 0;
	virtual void SetPDFExColumnWidthType(const int32 value) = 0;
	virtual void SetPDFExCustomUnit(const PMReal value) = 0;
	virtual void SetPDFExNotesType(const int32 value) = 0;
	virtual void SetPDFExTrackChangesType(const int32 value) = 0;
	virtual void SetPDFExNotesBackground(const bool16 value) = 0;
	virtual void SetPDFExTrackChangesBackground(const bool16 value) = 0;
	virtual void SetPDFExScope(const int32 value) = 0;
	virtual void SetPDFExStoryInfo(const bool16 value) = 0;
	virtual void SetPDFExSubsetFontsThreshold(const int32 subsetFontsThreshold) = 0;
	
	// Get methods
	virtual bool16 GetPDFExLaunchAcrobat() const = 0;
	virtual bool16 GetPDFExPageInfo() const = 0;
	virtual bool16 GetPDFExStyle() const = 0;
	virtual bool16 GetPDFExLineNumber() const = 0;
	virtual bool16 GetPDFExInlineNotes() const = 0;
	virtual bool16 GetPDFExTrackChanges() const = 0;
	virtual bool16 GetPDFExFill() const = 0;
	virtual bool16 GetPDFExALE() const = 0;
	virtual int32 GetPDFExLineRangeFormat() const = 0;
	virtual PMString GetPDFExLineRange() const = 0;
	virtual int32 GetPDFExAcrobatCompatibilityLevel() const = 0;
	virtual PMString GetPDFExFont() const = 0;
	virtual PMString GetPDFExFontType() const = 0;
	virtual PMString GetPDFExFontSize() const = 0;
	virtual PMString GetPDFExFontLeading() const = 0;
	virtual PMReal GetPDFExColumnWidth() const = 0;
	virtual int32 GetPDFExColumnWidthType() const = 0;
	virtual PMReal GetPDFExCustomUnit() const = 0;
	virtual int32 GetPDFExNotesType() const = 0;
	virtual int32 GetPDFExTrackChangesType() const = 0;
	virtual bool16 GetPDFExNotesBackground() const = 0;
	virtual bool16 GetPDFExTrackChangesBackground() const = 0;
	virtual int32 GetPDFExScope() const = 0;
	virtual bool16 GetPDFExStoryInfo() const = 0;
	virtual int32 GetPDFExSubsetFontsThreshold() const = 0;
};

#endif

// End, IInCopyPDFExptGalleyData.h.
