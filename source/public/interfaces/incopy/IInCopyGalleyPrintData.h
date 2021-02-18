//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IInCopyGalleyPrintData.h $
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
#ifndef __IInCopyGalleyPrintData__
#define __IInCopyGalleyPrintData__

#include "IPMUnknown.h"
#include "IXferBytes.h"
#include "InCopyCoreID.h"
#include "PersistUIDList.h"
#include "PMString.h"
#include "PMReal.h"
#include "PMRect.h"
#include "IGenericSettings.h"
#include "IPrintData.h"
#include "IInCopyGalleySettingData.h"

class IPrintDialogData;

/**
 Interface that contains data items used to configure InCopy to print
 documents in galley mode.  The interface is persist to session workspace.

 InCopy using IInCopyGalleyPrintData to configure the print dialog, 
 then copy the data into corresponding IPrintData data field, for the
 print command using IPrintData.
*/
class IInCopyGalleyPrintData : public IPMUnknown
{
public:
enum	{	kDefaultIID = IID_IINCOPYGALLEYPRINTDATA };
enum	{	// DeviceType
			kPostScriptDeviceType	= 0,
			kNonPostScriptDeviceType,
			// print to
			kPrinter				= 0,
			kVirtualPrinter	,
			// PaperSizeSelection
			kPaperSizeDefinedByUser		= -1,
			kPaperSizeDefinedByDriver	= -2,
			kPaperSizeDefinedByName		= -3,
			// PageOrientation
			kPortrait				= 0, 
			kLandscape,						// Counterclockwise 90 degrees
			// Which
			kAll				= 0, 
			kRange,
			
			// Scope
			kAllStories			= 0,			
			kCurrentStory,
			kExpandedStory,

			// setting
			kCurrentSetting				= 0,
			kOverrideSetting,

			// notes/track changes type
			kVisible			=1,
			kNone				= -1,
			// column unit
			kInches				= 0,
			kCentimeter,

			kDontCare				= ((int32)-32767) 
		};


	// Copy/Initialization methods
	virtual void CopyData(IInCopyGalleyPrintData* copyFromPD, bool16 bCopyPrintRecord = kFalse) = 0;
	
	// Change notification method
	virtual void Notify(void* changedBy = nil) = 0;

	// sync to IPrintData
	virtual void CopyToPrintData(IPrintData * data) = 0;
	// sync from IPrintData
	virtual void CopyFromPrintData(IPrintData * data) = 0;
	// set the default setting
	virtual void CopyDefault(IInCopyGalleySettingData * setting) = 0;

	// Set methods
	virtual void SetDeviceType(const int32 deviceType) = 0;
	virtual void SetPrintTo(const int32 to) = 0;
	virtual void SetPrinter(const PMString& printer) = 0;
	virtual void SetFileName(const PMString& fileName) = 0;
	virtual void SetPPDName(const PMString& fileName) = 0;
	virtual void SetPaperSize(const PMRect& paperSize) = 0;
	virtual void SetImageablePaperSize(const PMRect& paperSize) = 0;
	virtual void SetPaperSizeSelection(const int32 paperSizeSelection) = 0;
	virtual void SetPaperSizeName(const PMString& paperSizeName) = 0;
	virtual void SetOrientation(const int32 orientation) = 0;
	virtual void SetCopies(const int32 copies) = 0;
	virtual void SetCollate(const bool16 collate) = 0;
	virtual void SetWhich(const int32 which) = 0;
	virtual void SetRange(const PMString& range) = 0; 
	virtual void SetShowSaveDialog(const bool16 showSaveDialog) = 0;
	virtual void SetScope(const int32 scope) = 0;
	virtual void SetFill(const bool16 fill) = 0;
	virtual void SetParaStyles(const bool16 column) = 0;
	virtual void SetNotes(const bool16 notes) = 0;
	virtual void SetNotesType(const int32 type) = 0;
	virtual void SetTrackChanges(const bool16 changes) = 0;
	virtual void SetTrackChangesType(const int32 changes) = 0;
	virtual void SetALE(const bool16 ale) = 0;
	virtual void SetLineNumber(const bool16 number) = 0;
	virtual void SetPagesInfo(const bool16 number) = 0;
	virtual void SetSetting(const int32 setting) = 0;
	virtual void SetReverse(const  bool16 Reverse) = 0;
	virtual void SetStoryInfo(const  bool16 StoryInfo) = 0; 
	virtual void SetNotesBackgroundInColor(const bool16  value) = 0; 
	virtual void SetTrackChangesBackgroundInColor(const bool16  value) = 0; 
	virtual void SetFontSize(const PMString& FontSize) = 0; 
	virtual void SetColumnWidth(const PMReal columns) = 0; 
	virtual void SetColumnWidthType(const int32 type) = 0;
	virtual void SetCustomUnit(const PMReal custom) = 0; 
	virtual void SetFontName(const PMString& FontName) = 0;  
	virtual void SetFontType(const PMString& FontType) = 0; 
	virtual void SetFontLeading(const PMString& FontLeading) = 0; 

	virtual void SetPaperSizeSelector(uchar* inData, uint32 inSize) = 0;

	// Get methods
	virtual bool16 GetIsDefaultValues() const = 0;

	virtual int32 GetDeviceType() const = 0;
	virtual int32 GetPrintTo() const = 0;
	virtual PMString GetPrinter() const = 0;
	virtual PMString GetFileName() const = 0;
	virtual PMString GetPPDName() const = 0;
	virtual PMRect GetPaperSize() const = 0;
	virtual PMRect GetImageablePaperSize() const = 0;
	virtual int32 GetPaperSizeSelection() const = 0;
	virtual PMString GetPaperSizeName() const = 0;
	virtual int32 GetOrientation() const = 0;
	virtual int32 GetCopies() const = 0;
	virtual bool16 GetCollate() const = 0;
	virtual int32 GetWhich() const = 0;
	virtual PMString GetRange() const = 0; 
	virtual bool16 GetShowSaveDialog() const = 0;
	virtual int32 GetScope() const = 0;
	
	virtual bool16 GetFill() const = 0;
	virtual bool16 GetParaStyles() const = 0;
	virtual bool16 GetNotes() const = 0;
	virtual int32 GetNotesType() const = 0;
	virtual bool16 GetTrackChanges() const = 0;
	virtual int32 GetTrackChangesType() const = 0;
	virtual bool16 GetALE() const = 0;
	virtual bool16 GetLineNumber() const = 0;
	virtual bool16 GetPagesInfo() const = 0;
	virtual int32 GetSetting() const = 0;
	virtual bool16 GetReverse() const = 0;
	virtual bool16 GetStoryInfo() const = 0;
	virtual bool16 GetNotesBackgroundInColor() const = 0;
	virtual bool16 GetTrackChangesBackgroundInColor() const = 0;
	virtual PMString GetFontSize() const = 0;
	virtual PMReal GetColumnWidth() const = 0;
	virtual int32 GetColumnWidthType() const = 0;
	virtual PMReal GetCustomUnit() const = 0;
	virtual PMString GetFontName() const = 0;
	virtual PMString GetFontType() const = 0;
	virtual PMString GetFontLeading() const = 0;

	virtual uchar* GetPaperSizeSelector(uint32 &outSize) const = 0; // NOTE!!! Caller is responsible for delete[]-ing the return value!!!

};

#endif

// End, IInCopyGalleyPrintData.h.
