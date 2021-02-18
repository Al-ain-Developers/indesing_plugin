//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IInCopyLayoutPrintData.h $
//  
//  Owner: David Berggren
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
#ifndef __IInCopyLayoutPrintData__
#define __IInCopyLayoutPrintData__

#include "IPMUnknown.h"
#include "IXferBytes.h"
#include "InCopyCoreID.h"
#include "PersistUIDList.h"
#include "PMString.h"
#include "PMReal.h"
#include "PMRect.h"
#include "IGenericSettings.h"
#include "IPrintData.h"
/**
 Interface that contains data items used to configure InCopy to print
 documents in layout mode.  The interface is persist to session workspace.

 InCopy using IInCopyLayoutPrintData to configure the print dialog, 
 then copy the data into corresponding IPrintData data fields, for the
 print command using IPrintData.
*/
class IInCopyLayoutPrintData : public IPMUnknown
{
public:
enum	{	kDefaultIID = IID_IINCOPYLAYOUTPRINTDATA };
enum	{	// DeviceType
			kPostScriptDeviceType	= 0,
			kNonPostScriptDeviceType,
			// printer
			kPrinter				= 0,
			kVirtualPrinter,
			
			// PaperSizeSelection
			kPaperSizeDefinedByUser		= -1,
			kPaperSizeDefinedByDriver	= -2,
			kPaperSizeDefinedByName		= -3,
			// PageOrientation
			kPortrait				= 0, 
			kLandscape,						// Counterclockwise 90 degrees
			// WhichPages
			kAllPages				= 0, 
			kPageRange,
			// ScaleMode
			kScaleToFit				= 0, 
			kScaleXAndY,
			
			kDontCare				= ((int32)-32767) 
		};


	// Copy/Initialization methods
	virtual void CopyData(IInCopyLayoutPrintData* copyFromPD, bool16 bCopyPrintRecord = kFalse) = 0;

	// Change notification method
	virtual void Notify(void* changedBy = nil) = 0;

	// sync to IPrintData
	virtual void CopyToPrintData(IPrintData * data) = 0;
	// sync from IPrintData
	virtual void CopyFromPrintData(IPrintData * data) = 0;

	// Set methods
	virtual void SetDeviceType(const int32 deviceType) = 0;
	virtual	void SetPrintTo(const int32 to) = 0;
	virtual void SetPrinter(const PMString& printer) = 0;
	virtual void SetFileName(const PMString& fileName) = 0;
	virtual void SetPPDName(const PMString& Name) = 0;
	virtual void SetPaperSize(const PMRect& paperSize) = 0;
	virtual void SetImageablePaperSize(const PMRect& paperSize) = 0;
	virtual void SetPaperSizeSelection(const int32 paperSizeSelection) = 0;
	virtual void SetPaperSizeName(const PMString& paperSizeName) = 0;
	virtual void SetOrientation(const int32 pageOrientation) = 0;
	virtual void SetCopies(const int32 copies) = 0;
	virtual void SetCollate(const bool16 collate) = 0;
	virtual void SetReverse(const bool16 reverse) = 0;
	virtual void SetWhichPages(const int32 whichPages) = 0;
	virtual void SetPageRange(const PMString& pageRange) = 0; 
	virtual void SetSpreads(const bool16 spreads) = 0;
	virtual void SetShowSaveDialog(const bool16 showSaveDialog) = 0;
	virtual void SetScaleMode(const int32 scaleMode) = 0;
	virtual void SetProportional(const bool16 proportional) = 0;
	virtual void SetXScale(const PMReal& xScale) = 0;
	virtual void SetYScale(const PMReal& yScale) = 0;
	virtual void SetImages(const bool16 images) = 0;
	virtual void SetPagesInfo(const bool16 pageNumber) = 0;

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
	virtual bool16 GetReverse() const = 0;
	virtual int32 GetWhichPages() const = 0;
	virtual PMString GetPageRange() const = 0; 
	virtual bool16 GetSpreads() const = 0;
	virtual bool16 GetShowSaveDialog() const = 0;
	virtual int32 GetScaleMode() const = 0;
	virtual bool16 GetProportional() const = 0;
	virtual PMReal GetXScale() const = 0;
	virtual PMReal GetYScale() const = 0;
	virtual bool16 GetImages() const = 0;
	virtual bool16 GetPagesInfo() const = 0;

	virtual uchar* GetPaperSizeSelector(uint32 &outSize) const = 0; // NOTE!!! Caller is responsible for delete[]-ing the return value!!!

};

#endif

// End, IInCopyLayoutPrintData.h.
