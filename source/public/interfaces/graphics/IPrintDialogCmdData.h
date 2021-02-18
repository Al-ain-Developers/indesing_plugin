//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPrintDialogCmdData.h $
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
//  The command data interface for the book printing command in K2.	
//  
//========================================================================================

#pragma once
#ifndef __IPrintDialogCmdData__
#define __IPrintDialogCmdData__

#include "IPMUnknown.h"
#include "IPrintData.h"
#include "IInkList.h"
#include "ITrapStyleListMgr.h"
#include "IPrintPageInitializer.h"
#include "UIDRef.h"

class IPrintDialogCmdData : public IPMUnknown
{
public:
	// set method for IInkList
	virtual void SetInkList(IInkList *iInkList) = 0;

	// set method for ITrapStyleListMgr
	virtual void SetTrapListMgr (ITrapStyleListMgr* iTrapListMgr) = 0;

	// set method for print data object 
	virtual void SetPrintData(IPrintData *iPrintData) = 0;

	// set method for document UIDRef object 
	virtual void SetDocUIDRef(const UIDRef& docUIDRef) = 0;

	// set method for boolean - different meanings (default false)
	// kPlatformPrintDialogCmd:
	//		true - show page setup dialog (Mac only)
	//		false - show platform print dialog
	enum {
		kShowPageSetup		= 0x0001,
		kWorkingOnStyle		= 0x0002,
		kWorkingOnBook		= 0x0004,
		kPrintUsingStyle	= 0x0008,
		kIsNewStyle			= 0x0010,
		kFromPrintBooklet	= 0x0020	//Signifies if the print dialog has been opened from PrintBooklet Dialog
	};
	virtual void SetFlags(const uint32 flags) = 0;

	// set method for the return code (kSuccess or kCancel)
	virtual void SetReturnCode(const ErrorCode returnCode) = 0;

	// get method for the IInkList to use
	virtual IInkList *GetInkList() const = 0;

	//	get method for the ITrapStyleListMgr to use
	//	(This should really by QueryTrapListMgr () since the caller
	//	must call release.)
	virtual ITrapStyleListMgr* GetTrapListMgr() const = 0;

	// get method for IPrintData object pointer
	virtual IPrintData* GetPrintData() const = 0;

	// get method for document UIDRef object 
	virtual const UIDRef& GetDocUIDRef() const = 0;

	// get method for the boolean
	virtual uint32 GetFlags() const = 0;

	// get method for the return code (kSuccess or kCancel)
	virtual ErrorCode GetReturnCode() const = 0;

	/**
	 * Retrieves a object that can be used to initializer the
	 * IOutputPages.
	 */

	virtual void SetInitializer( IPrintPageInitializer* pInit ) = 0;

	/**
	 * Retrieve the value from SetInitializer.  The default is nil.
	 */

	virtual IPrintPageInitializer* GetInitializer() const = 0;
};

#endif // __IPrintBookCmdData__
