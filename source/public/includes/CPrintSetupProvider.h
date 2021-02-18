//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CPrintSetupProvider.h $
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
//  Helper class for implementation of the pure virtual IPrintSetupProvider interface class
//  
//========================================================================================

#pragma once
#ifndef __CPrintSetupProvider__
#define __CPrintSetupProvider__

#include "IPrintSetupProvider.h"

/**
 Stubbed out default implementation of the IPrintSetupProvider interface, which is used
 for setting up or changing the print parameters, prior to and during the printing process.

 Users can subclass from this class, and only have to override methods that they are 
 interested in.
 @see IPrintSetupProvider
*/
class CPrintSetupProvider : public IPrintSetupProvider
{
public:
	/** Start of Printing of a single pub. For properly ref counting of interfaces, this must
	 be paired with an EndPrint() call when you are done with printing.
		@param bReturn OUT return value - true means continue on, false means STOP
		@param iDoc IN the IDocument of the pub being printed
		@param styleUIDRef IN if valid, is the printer style UIDRef to be used
		@param printPubUIOpt IN UI options invoked - see IPrintCmdData.h for definitions
		@param iInkList IN the ink list to be used throughout the print job
		@param iTrapListMgr IN the trap list manager to be used throughout the print job
	*/
	virtual void StartPrintPub (
			bool16&				bReturn,
			IDocument*			iDoc,
			UIDRef&				styleUIDRef,
			IPrintCmdData::PrintUIOptions&	printPubUIOpt,
			IInkList*			iInkList,
			ITrapStyleListMgr*	iTrapListMgr
			) {}

	/** Start of Printing of a book. For properly ref counting of interfaces, this must
	 be paired with an EndPrint() call when you are done with printing.
		@param bReturn OUT return value - true means continue on, false means STOP
		@param iBook IN the IBook interface of the book being printed
		@param pubsUIDList IN the UIDList of the pubs in the book that are being printed
		@param printBookUIOpt IN UI options invoked - see IBookOutputActionCmdData.h for definitions
		@param iInkList IN the ink list to be used throughout the print job
		@param iTrapListMgr IN the trap list manager to be used throughout the print job
	*/
	virtual void StartPrintBook (
			bool16&				bReturn,
			IBook*				iBook,
			UIDList*			pubsUIDList,
			IBookOutputActionCmdData::OutputUIOptions&	printBookUIOpt,
			IInkList*			iInkList,
			ITrapStyleListMgr*	iTrapListMgr
			) {}

	/** Before the InDesign Print UI is shown
		@param bReturn OUT return value - true means continue on, false means don't show print UI
		@param iPrintData IN the IPrintData containing all the print settings to be used
	*/
	virtual void BeforePrintUI (
			bool16&				bReturn,
			IPrintData*			iPrintData
			) {}


	/** Before the InCopy Print UI is shown.
		@param bReturn			OUT Return value: true to continue, false to don't show the Print UI.
		@param currentPanel		IN which panel is currently active, IInCopyPrintDialogData::kGalleyPanel
									or IInCopyPrintDialogData::kLayoutPanel.
		@param iGalleyPrintData	IN IInCopyGalleyPrintData containing galley print settings to be used, if
									the currentPanel is IInCopyPrintDialogData::kGalleyPanel.
		@param iLayoutPrintData	IN IInCopyLayoutPrintData containing layout print settings to be used, if
									the currentPanel is IInCopyPrintDialogData::kLayoutPanel.
		@param iPrintData		IN IPrintData containing the print settings to be used. This interface will
									be intialized by the relevant settings from iGalleyPrintData or iLayoutPrintData.
	 */
	virtual void BeforeInCopyPrintUI (
			bool16&					bReturn,
			int32					currentPanel,
			IInCopyGalleyPrintData*	iGalleyPrintData,
			IInCopyLayoutPrintData* iLayoutPrintData,
			IPrintData*				iPrintData
			) {}

	/** After the InDesign Print UI is shown
		@param bReturn OUT return value - true means continue on, false means STOP
		@param iPrintData IN the IPrintData containing all the print settings to be used
	*/
	virtual void AfterPrintUI (
			bool16&				bReturn,
			IPrintData*			iPrintData
			) {}

	/** After the InCopy Print UI is shown.
		@param bReturn			OUT Return value: true to continue, false to stop.
		@param currentPanel		IN which panel is currently active, IInCopyPrintDialogData::kGalleyPanel
									or IInCopyPrintDialogData::kLayoutPanel.
		@param iGalleyPrintData	IN IInCopyGalleyPrintData containing galley print settings to be used, if
									the currentPanel is IInCopyPrintDialogData::kGalleyPanel.
		@param iLayoutPrintData	IN IInCopyLayoutPrintData containing layout print settings to be used, if
									the currentPanel is IInCopyPrintDialogData::kLayoutPanel.
		@param iPrintData		IN IPrintData containing the print settings to be used. This interface will
									be intialized by the relevant settings from iGalleyPrintData or iLayoutPrintData.
	 */
	virtual void AfterInCopyPrintUI (
			bool16&					bReturn,
			int32					currentPanel,
			IInCopyGalleyPrintData*	iGalleyPrintData,
			IInCopyLayoutPrintData* iLayoutPrintData,
			IPrintData*				iPrintData
			) {}

	/**	Before the print gather command
		@param bReturn OUT return value - true means continue on, false means STOP
		@param iPrintData IN the IPrintData containing all the print settings to be used
		@param iOutputPages IN the IOutputPages containing which pages to gather info 
	*/
	virtual void BeforePrintGatherCmd (
			bool16&				bReturn,
			IPrintData*			iPrintData,
			IOutputPages*		iOutputPages
			) {}

	/**	After the print gather command
		@param bReturn OUT return value - true means continue on, false means STOP
		@param iPrintData IN the IPrintData containing all the print settings to be used
		@param iOutputPages IN the IOutputPages containing which pages to gather info 
		@param iPrintJobData IN the IPrintJobData containing the gathered information 
	*/
	virtual void AfterPrintGatherCmd (
			bool16&				bReturn,
			IPrintData*			iPrintData,
			IOutputPages*		iOutputPages,
			IPrintJobData*		iPrintJobData
			) {}

	/**	Before initialization of the Print Job Params
		@param bReturn OUT return value - true means continue on, false means STOP
		@param iPrintData IN the IPrintData containing all the print settings to be used
		@param iOutputPages IN the IOutputPages containing which pages to gather info 
		@param iPrintJobData IN the IPrintJobData containing the gathered information 
	*/
	virtual void BeforePrintJobParamsInit (
			bool16&				bReturn,
			IPrintData*			iPrintData,
			IOutputPages*		iOutputPages,
			IPrintJobData*		iPrintJobData
			) {}

	/**	After initialization of the Print Job Params
		@param bReturn OUT return value - true means continue on, false means STOP
		@param iPrintData IN the IPrintData containing all the print settings to be used
		@param iOutputPages IN the IOutputPages containing which pages to gather info 
		@param iPrintJobData IN the IPrintJobData containing the gathered information 
	*/
	virtual void AfterPrintJobParamsInit (
			bool16&				bReturn,
			IPrintData*			iPrintData,
			IOutputPages*		iOutputPages,
			IPrintJobData*		iPrintJobData
			) {}

	/**	Before the beginning of the execution of the print loop. After information is
		put into the print record (print driver settings) if printing to a printer
		@param bReturn OUT return value - true means continue on, false means STOP
		@param iPrintData IN the IPrintData containing all the print settings to be used
		@param iOutputPages IN the IOutputPages containing which pages to gather info 
		@param iPrintJobData IN the IPrintJobData containing the gathered information 
	*/
	virtual void BeforePrintLoop (
			bool16&				bReturn,
			IPrintData*			iPrintData,
			IOutputPages*		iOutputPages,
			IPrintJobData*		iPrintJobData
			) {}

	/**	End of Printing. Doing so ensures that the ref counts for
	 all interfaces are properly decremented and any other cleanup
	 tasks are completed.
	*/
	virtual void EndPrint() {};


	/** Print Loop - BeginPageEvent
		@param bReturn OUT return value - true means continue on, false means STOP
		@param iPrintData IN the IPrintData containing all the print settings to be used
		@param iOutputPages IN the IOutputPages containing which pages to gather info 
		@param iPrintJobData IN the IPrintJobData containing the gathered information 
		@param whichPage IN which page is being printed - can be used as index into IOutputPages
	*/
	virtual void BeginPageEvent (
			IPrintData*			iPrintData,
			IOutputPages*		iOutputPages,
			IPrintJobData*		iPrintJobData,
			int32*				whichPage
			) {}

	/** Print Loop - Before DrawPage Event
		@param bReturn OUT return value - true means continue on, false means continue to next event
		@param iPrintData IN the IPrintData containing all the print settings to be used
		@param iOutputPages IN the IOutputPages containing which pages to gather info 
		@param iPrintJobData IN the IPrintJobData containing the gathered information 
		@param whichPage IN which page is being printed - can be used as index into IOutputPages
	*/
	virtual void BeforeDrawPageEvent (
			bool16&				bReturn,
			IPrintData*			iPrintData,
			IOutputPages*		iOutputPages,
			IPrintJobData*		iPrintJobData,
			int32*				whichPage
			) {}

	/** Print Loop - Before DrawPage performed
		@param bReturn OUT return value - true means continue on, false means don't draw page/spread
		@param iPrintData IN the IPrintData containing all the print settings to be used
		@param iOutputPages IN the IOutputPages containing which pages to gather info 
		@param iPrintJobData IN the IPrintJobData containing the gathered information 
		@param whichPage IN which page is being printed - can be used as index into IOutputPages
		@param outputRect IN the rect which is used for setting up the draw mgr filter
		@param gd IN from which you can get IGraphicsPort, IViewPortAttributes etc.
	*/
	virtual void BeforeDrawPage (
			bool16&				bReturn,
			IPrintData*			iPrintData,
			IOutputPages*		iOutputPages,
			int32*				whichPage,
			PMRect*				outputRect,
			GraphicsData*		gd
			) {}

	/** Print Loop - After DrawPage Event
		@param iPrintData IN the IPrintData containing all the print settings to be used
		@param iOutputPages IN the IOutputPages containing which pages to gather info 
		@param iPrintJobData IN the IPrintJobData containing the gathered information 
		@param whichPage IN which page is being printed - can be used as index into IOutputPages
	*/
	virtual void AfterDrawPageEvent (
			IPrintData*			iPrintData,
			IOutputPages*		iOutputPages,
			IPrintJobData*		iPrintJobData,
			int32*				whichPage
			) {}

	/** Print Loop - Before Draw Galley Page Event - same as BeforeDrawPageEvent, only for InCopy
		@param bReturn OUT return value - true means continue on, false means continue to next event
		@param iPrintData IN the IPrintData containing all the print settings to be used
		@param iOutputPages IN the IOutputPages didn't containing the pages UID (GetNthUIDRef() will return non page UIDRef), rather, it contains the physcial galley page number.
		@param iPrintJobData IN the IPrintJobData containing the gathered information 
		@param whichPage IN which page is being printed - can be used as index into IOutputPages
	*/
	virtual void BeforeDrawGalleyPageEvent (
			bool16&				bReturn,
			IPrintData*			iPrintData,
			IOutputPages*		iOutputPages,
			IPrintJobData*		iPrintJobData,
			int32*				whichPage
			) {};

	/** Print Loop - Before Draw Galley Page - same as BeforeDrawPage, only for InCopy
		@param bReturn OUT return value - true means continue on, false means don't draw page/spread
		@param iPrintData IN the IPrintData containing all the print settings to be used
		@param iOutputPages IN the IOutputPages didn't containing the pages UID (GetNthUIDRef() will return non page UIDRef), rather, it contains the physcial galley page number.
		@param iPrintJobData IN the IPrintJobData containing the gathered information 
		@param whichPage IN which page is being printed - can be used as index into IOutputPages
		@param outputRect IN the rect which is used for setting up the draw mgr filter
		@param gd IN from which you can get IGraphicsPort, IViewPortAttributes etc.
	*/
	virtual void BeforeDrawGalleyPage (
			bool16&				bReturn,
			IPrintData*			iPrintData,
			IOutputPages*		iOutputPages,
			int32*				whichPage,
			PMRect*				outputRect,
			GraphicsData*		gd
			) {};

	/** Print Loop - After Draw Galley Page Event - same as AfterDrawPageEvent, only for InCopy
		@param iPrintData IN the IPrintData containing all the print settings to be used
		@param iOutputPages IN the IOutputPages didn't containing the pages UID (GetNthUIDRef() will return non page UIDRef), rather, it contains the physcial galley page number.
		@param iPrintJobData IN the IPrintJobData containing the gathered information 
		@param whichPage IN which page is being printed - can be used as index into IOutputPages
	*/
	virtual void AfterDrawGalleyPageEvent (
			IPrintData*			iPrintData,
			IOutputPages*		iOutputPages,
			IPrintJobData*		iPrintJobData,
			int32*				whichPage
			) {};

	/** Print Loop - EndPage Event
		@param iPrintData IN the IPrintData containing all the print settings to be used
		@param iOutputPages IN the IOutputPages containing which pages to gather info 
		@param iPrintJobData IN the IPrintJobData containing the gathered information 
		@param whichPage IN which page is being printed - can be used as index into IOutputPages
	*/
	virtual void EndPageEvent (
			IPrintData*			iPrintData,
			IOutputPages*		iOutputPages,
			IPrintJobData*		iPrintJobData,
			int32*				whichPage
			) {}

	/** Print Loop - EndPrinting Event
	*/
	virtual void EndPrintingEvent ( ) {}

	/** Print Loop - Error Event
		@param bReturn OUT return value - true means continue on, false means don't set the global error code
					NOTE: this is an error event from AGM. InD maps the error number to set strings, which
					are localized. We do not use the errText that this event provides.
		@param iPrintData IN the IPrintData containing all the print settings to be used
		@param errorNum IN the error number 
		@param errComponent IN the error component from Bravo 
		@param errText IN the error text
		@param errOtherInfo IN other error information, i.e. name of a problem font
	*/
	virtual void PrintErrorEvent (
			bool16&				bReturn,
			IPrintData*			iPrintData,
			ErrorCode&			errorNum,
			PMString&			errComponent,
			PMString&			errText,
			PMString&			errOtherInfo
			) {}

};

#endif
