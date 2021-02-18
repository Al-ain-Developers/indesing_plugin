//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPrintDialogData.h $
//  
//  Owner: Michael Easter
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
//  The data interface for the print dialog in InDesign.	
//  
//========================================================================================

#pragma once
#ifndef __IPrintDialogData__
#define __IPrintDialogData__

#include "IPMUnknown.h"
#include "IInkList.h"
#include "IPrintData.h"
#include "IPrintPageInitializer.h"
#include "UIDRef.h"

class IPrintDialogData : public IPMUnknown
{
public:
	// set method for IPrintData object pointer 
	virtual void SetPrintData(IPrintData* iPrintData) = 0;

	// set method for IInkList to use
	virtual void SetInkList(IInkList* iInkList) = 0;

	// set method for document UIDRef object 
	virtual void SetDocUIDRef(const UIDRef& docUIDRef) = 0;

	// set method for print flags
	enum {
		kShowPageSetup		= 0x0001,
		kWorkingOnStyle		= 0x0002,
		kWorkingOnBook		= 0x0004,
		kPrintUsingStyle	= 0x0008,
		kIsNewStyle			= 0x0010,
		kFromPrintBooklet	= 0x0020	//Signifies if the print dialog has been opened from PrintBooklet Dialog
	};
	virtual void SetFlags(const uint32 flags) = 0;

	// set/add method for ink screening information by name
	virtual void SetInkScreening(const PMString& name, bool16 print, const PMReal& frequency, const PMReal& angle) = 0;

	// set method for ink screening information by index
	virtual bool16 SetNthInkScreening(int32 index, bool16 print, const PMReal& frequency, const PMReal& angle) = 0;

	// get method for IPrintData object pointer
	virtual IPrintData* GetPrintData() const = 0;

	// get method for IInkList to use
	virtual IInkList* GetInkList() const = 0;

	// get method for document UIDRef object 
	virtual const UIDRef& GetDocUIDRef() const = 0;

	// get method for print flags
	virtual uint32 GetFlags() const = 0;

	// get method for ink screening information by ink name
	virtual bool16 GetInkScreening(const PMString& name, bool16& print, PMReal& frequency, PMReal& angle) const = 0;

	// get method for ink screening information by index
	virtual bool16 GetNthInkScreening(int32 index, bool16& print, PMReal& frequency, PMReal& angle) const = 0;

	// get method for ink screening information by index
	virtual bool16 GetNthInkScreening(int32 index, PMString& name, bool16& print, PMReal& frequency, PMReal& angle) const = 0;

	// get method for ink screening information count
	virtual int32 GetInkScreeningCount() const = 0;

	// remove method for ink screening information by name
	virtual void RemoveInkScreening(const PMString& name) = 0;

	// remove method for ink screening information by index
	virtual void RemoveNthInkScreening(int32 index) = 0;

	// clear method for ink screening information
	virtual void ClearInkScreenings() = 0;

	/**
	 * The initializer allows for a different page initializion
	 * routine to be used for book printing vs. doc printing.
	 */

	virtual void SetInitializer( IPrintPageInitializer* pInit ) = 0;

	/**
	 * Returns whatever was passed to SetInitializer.
	 */

	virtual IPrintPageInitializer* GetInitializer() = 0;
};

#endif // __IPrintDialogData__
