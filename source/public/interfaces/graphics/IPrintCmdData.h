//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPrintCmdData.h $
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
//  The command data interface for all of the printing commands in K2.	
//  
//========================================================================================

#pragma once
#ifndef __IPrintCmdData__
#define __IPrintCmdData__

#include "IPMUnknown.h"
#include "IDocument.h"
#include "UIDRef.h"
#include "IPrintData.h"
#include "IPrintJobData.h"
#include "IInkList.h"
#include "ITrapStyleListMgr.h"
#include "IOutputPages.h"

/**	Print progress bar information
*/
class IPrintProgress: public IPMUnknown
{
public:
	/**	Initialize the class
		@param nPrintTo		IN where we are printing to, i.e. from IPrintData::GetPrintTo
		@param bPrintReverse	IN if we are printing in reverse order
	*/
	virtual void Initialize(int32 nPrintTo, bool16 bPrintReverse ) = 0;
	/**	Start the printing - this will construct a RangeProgressBar
		@param nPages	IN the number of pages printing
	*/
	virtual void StartPrint(int32 nPages) = 0;
	/**	Begin a page
		@param uidPage		IN UIDRef of the page begin printed, or UIDRef::gNull
		@param whichPage	IN if uidPage is null, use this as the page number
	*/
	virtual void BeginPage(UIDRef& uidPage, int32 whichPage) = 0;
	/** Draw a page
		@param whichPage	IN which page being printed
		@param currInkStr	IN either "Composite" or the plate name
	*/
	virtual void DrawPage(int32 whichPage, PMString& currInkStr) = 0;
	/** Callback that is called by AGM Print 
		@param current		IN current percentage done
		@param name			IN current name of resource
		@param stage		IN current stage of callback - defined in GraphicsExternal.h
		@return kTrue if cancelled, kFalse otherwise
		@see GraphicsExternal.h
	*/
	virtual Bool8 Update(float current, const char* name, long stage) = 0;
	/** End a page
		@param whichPage	IN which page is ending
	*/
	virtual void EndPage(int32 whichPage) = 0;
	/** End printing
	*/
	virtual void EndPrint() = 0;
	/** Check if progress has been cancelled
		@return kTrue if cancelled, kFalse otherwise
	*/
	virtual bool16 WasCancelled() = 0;
	/** Clear the sub task progress information
	*/
	virtual void ClearSubTaskProgress() = 0;
	/** Supress the creation of the RangeProgressBar in StartPrint
		@param bSupress		IN kTrue to supress progress bar creation, kFalse otherwise
	*/
	virtual void SetSupressStartStopPrint( bool16 bSupress ) = 0;
	/** Set the current sub task text
		@param pszText		IN the new text to display
	*/
	virtual void SetCurrentSubtaskText( const char* pszText ) = 0;
	/** Begin a galley page - InCopy specific
		@param whichPage	IN which page is beginning
	*/
	virtual void BeginGalleyPage(int32 whichPage) = 0;

};

/**	Print command data - data container for most print commands
*/
class IPrintCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPRINTCMDDATA };
	
	/** Set method for IDocument
		@param iDoc		IN pointer to IDocument being printed
		@see IDocument
	*/
	virtual void SetIDoc(IDocument* iDoc) = 0;

	/** Set method for print progress data
		@param pProcData	IN pointer to IPrintProgress, the print
		progress callback class
	*/
	virtual void SetProgressData(IPrintProgress* pProcData) = 0;

	/** Set method for print data object 
		@param iPrintData	IN pointer to IPrintData to use - contains
		all the print settings
		@see IPrintData
	*/
	virtual void SetPrintData(IPrintData* iPrintData) = 0;

	/** Set method for the print job data to use 
		@param iPrintJobData	IN pointer to the IPrintJobData information
		that was collected in the gathering process
		@see IPrintJobData
	*/
	virtual void SetPrintJobData(IPrintJobData* iPrintData) = 0;

	/** Set method for ink list to use 
		@param iInkList		IN pointer the IInkList to use
		@see IInkList
	*/
	virtual void SetInkList(IInkList* iInkList) = 0;

	/** Set method for ITrapStyleListMgr to use 
		@param iTrapListMgr		IN pointer to ITrapStyleListMgr to use
		@see ITrapStyleListMgr
	*/
	virtual void SetTrapListMgr(ITrapStyleListMgr* iTrapListMgr) = 0;

	/** Print flags
	*/
	enum {
		kShowPageSetup		= 0x0001,
		kWorkingOnStyle		= 0x0002,
		kWorkingOnBook		= 0x0004,
		kPrintUsingStyle	= 0x0008,
		kIsNewStyle			= 0x0010,
		kFromPrintBooklet	= 0x0020,	//Signifies if the print dialog has been opened from PrintBooklet Dialog
		kPrintingBooklet	= 0x0040,	// we are actually printing the booklet if this is set
		kPreflighting		= 0x0080	// Signifies that we are collecting resources for preflight purposes.
	};
	/** Set method for the print flags
		@param flags	IN flags regarding the current state
	*/
	virtual void SetFlags(const uint32 flags) = 0;

	/** Print UI options
	*/
	enum PrintUIOptions {
		kSuppressNothing		= 0x0,
		kSuppressPrintProgress	= 0x1,
		kSuppressPrintWarnings	= 0x2,
		kSuppressPrintDialog	= 0x4,
		kSuppressFileSaveDialog	= 0x8,
		kSuppressEverything		= 0xFF
	};
	/** Set method for the print UI options
		@param uiOptions	IN the UI options to use
	*/
	virtual void SetPrintUIOptions(const PrintUIOptions uiOptions) = 0;

	/** Set method for Printer Sytle UIDRef (if used)
		@param prtStyleUIDRef	IN UIDRef of the printer style to use,
		if desired
	*/
	virtual void SetPrtStyleUIDRef(const UIDRef prtStyleUIDRef) = 0;

	/** Get method for IDocument
		@return IDocument pointer to the document being printed
		@see IDocument
	*/
	virtual IDocument* GetIDoc() const = 0;

	/** Get method for print progress callback
		@return IPrintProgress pointer to use
	*/
	virtual IPrintProgress* GetProgressData() const = 0;

	/** Get method for IPrintData object pointer
		@return IPrintData containing all of the print settings
		@see IPrintData
	*/
	virtual IPrintData* GetPrintData() const = 0;

	/** Get method for IPrintJobData object pointer
		@return IPrintJobData information that was collected
		@see IPrintJobData
	*/
	virtual IPrintJobData* GetPrintJobData() const = 0;

	/** Get method for IInkList object pointer
		@return IInkList to use when printing
		@see IInkList
	*/
	virtual IInkList* GetInkList() const = 0;

	/** Get method for ITrapStyleListMgr object pointer
		@return ITrapStyleListMgr pointer to use
		@see ITrapStyleListMgr
	*/
	virtual ITrapStyleListMgr* GetTrapListMgr() const = 0;

	/** Get method for print flags
		@return print flags to use
	*/
	virtual uint32 GetFlags() const = 0;

	/** Get method for the print UI options
		@return print UI options to use
	*/
	virtual PrintUIOptions GetPrintUIOptions() const = 0;

	/** Get method for Printer Sytle UIDRef (if used)
		@return UIDRef of the printer style to use
	*/
	virtual UIDRef GetPrtStyleUIDRef() const = 0;

	/** Get method for number of pages exported in PDF passthrough mode
		@return uint32 number of pages exported
	*/
	virtual uint32 GetNumberOfExportedPages() const = 0;

	/** Set method for number of pages exported in PDF passthrough mode
		@param IN number of pages exported
		@return void
	*/
	virtual void SetNumberOfExportedPages(uint32 numPages) = 0;
};

#endif // __IPrintCmdData__
