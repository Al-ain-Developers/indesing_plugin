//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPrintSetupProvider.h $
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
//  Provider interface for setting up or changing the print parameters, prior to
//  and during the printing process.
//  
//  Use the helper class CPrintSetupProvider.h to inherit from instead of this
//  pure virtual class, so that any future methods added will not break existing
//  implementations.
//  
//========================================================================================

#pragma once
#ifndef __IPrintSetupProvider__
#define __IPrintSetupProvider__

#include "IPMUnknown.h"
#include "IPrintCmdData.h"
#include "IBookOutputActionCmdData.h"

class IPrintData;
class IDocument;
class IBook;
class IOutputPages;
class IInkList;
class IPrintJobData;
class ITrapStyleListMgr;
class IViewPort;
class PMRect;
class GraphicsData;
class IInCopyGalleyPrintData;
class IInCopyLayoutPrintData;

/**
 Provider interface for setting up or changing the print parameters,
 prior to and during the printing process.

 Use the helper class CPrintSetupProvider.h to inherit from instead of this
 pure virtual class, so that any future methods added will not break existing
 implementations.
*/
class IPrintSetupProvider : public IPMUnknown
{
public:
	/**
	 Called at the start of printing a single pub. For properly ref counting of interfaces, this must
	 be paired with an EndPrint() call when you are done with printing.
	 @param bReturn			OUT Return value: true to continue, false to stop.
	 @param iDoc			IN IDocument of the pub being printed.
	 @param styleUIDRef		IN If valid, is the printer style UIDRef to be used.
	 @param printPubUIOpt	IN UI options invoked (see IPrintCmdData.h for definitions).
	 @param iInkList		IN Ink list to be used throughout the print job.
	 @param iTrapListMgr	IN Trap list manager to be used throughout the print job.
	 */
	virtual void StartPrintPub (
			bool16&				bReturn,
			IDocument*			iDoc,
			UIDRef&				styleUIDRef,
			IPrintCmdData::PrintUIOptions&	printPubUIOpt,
			IInkList*			iInkList,
			ITrapStyleListMgr*	iTrapListMgr
			) = 0;

	/**
	 Called at the start of printing a book. For properly ref counting of interfaces, this must
	 be paired with an EndPrint() call when you are done with printing.
	 @param bReturn			OUT Return value: true to continue, false to stop.
	 @param iBook			IN IBook interface of the book being printed.
	 @param pubsUIDList		IN UIDList of the pubs in the book that are being printed.
	 @param printBookUIOpt	IN UI options invoked (see IBookOutputActionCmdData.h for definitions).
	 @param iInkList		IN Ink list to be used throughout the print job.
	 @param iTrapListMgr	IN Trap list manager to be used throughout the print job.
	 */
	virtual void StartPrintBook (
			bool16&				bReturn,
			IBook*				iBook,
			UIDList*			pubsUIDList,
			IBookOutputActionCmdData::OutputUIOptions&	printBookUIOpt,
			IInkList*			iInkList,
			ITrapStyleListMgr*	iTrapListMgr
			) = 0;

	/**
	 Called before the InDesign Print UI dialog is opened.
	 @param bReturn		OUT Return value: true to continue, false to don't show the Print UI.
	 @param iPrintData	IN IPrintData containing all the print settings to be used.
	 */
	virtual void BeforePrintUI (
			bool16&				bReturn,
			IPrintData*			iPrintData
			) = 0;

	/**
	 Called before the InCopy Print UI dialog is opened.
	 @param bReturn				OUT Return value: true to continue, false - don't show the Print UI.
	 @param currentPanel		IN which panel is currently active, IInCopyPrintDialogData::kGalleyPanel 
									or IInCopyPrintDialogData::kLayoutPanel.
	 @param iGalleyPrintData	IN IInCopyGalleyPrintData containing galley print settings to be used, 
									if the currentPanel is IInCopyPrintDialogData::kGalleyPanel.
	 @param iLayoutPrintData	IN IInCopyLayoutPrintData containing layout print settings to be used, 
									if the currentPanel is IInCopyPrintDialogData::kLayoutPanel.
	 @param iPrintData			IN IPrintData containing the print settings to be used. This interface 
									will be intialized by the relevant settings from iGalleyPrintData 
									or iLayoutPrintData.
	*/
	virtual void BeforeInCopyPrintUI (
			bool16&					bReturn,
			int32					currentPanel,
			IInCopyGalleyPrintData*	iGalleyPrintData,
			IInCopyLayoutPrintData* iLayoutPrintData,
			IPrintData*				iPrintData
			) = 0;

	/**
	 Called after the InDesign Print UI dialog is closed. The PM global error code 
	 will be set to kCancel if the Print UI was cancelled. 
	 @param bReturn		OUT Return value: true to continue, false to stop.
	 @param iPrintData	IN IPrintData containing all the print settings to be used.
	 */
	virtual void AfterPrintUI (
			bool16&				bReturn,
			IPrintData*			iPrintData
			) = 0;

	/**
	 Called after the InCopy Print UI dialog is closed. The PM global error code will 
	 be set to kCancel if the Print UI was cancelled. 
	 @param bReturn				OUT Return value: true to continue, false to stop.
	 @param currentPanel		IN which panel is currently active, IInCopyPrintDialogData::kGalleyPanel 
									or IInCopyPrintDialogData::kLayoutPanel.
	 @param iGalleyPrintData	IN IInCopyGalleyPrintData containing galley print settings to be used, if 
									the currentPanel is IInCopyPrintDialogData::kGalleyPanel.
	 @param iLayoutPrintData	IN IInCopyLayoutPrintData containing layout print settings to be used, if 
									the currentPanel is IInCopyPrintDialogData::kLayoutPanel.
	 @param iPrintData			IN IPrintData containing the print settings to be used. This interface will 
									be intialized by the relevant settings from iGalleyPrintData or iLayoutPrintData.
	 */
	virtual void AfterInCopyPrintUI (
			bool16&					bReturn,
			int32					currentPanel,
			IInCopyGalleyPrintData*	iGalleyPrintData,
			IInCopyLayoutPrintData* iLayoutPrintData,
			IPrintData*				iPrintData
			) = 0;

	/**
	 Called before the print gather command.
	 @param bReturn			OUT Return value: true to continue, false to stop.
	 @param iPrintData		IN IPrintData containing all the print settings to be used.
	 @param iOutputPages	IN IOutputPages containing the pages to gather info for.
	 */
	virtual void BeforePrintGatherCmd (
			bool16&				bReturn,
			IPrintData*			iPrintData,
			IOutputPages*		iOutputPages
			) = 0;

	/**
	 Called after the print gather command.
	 @param bReturn			OUT Return value: true to continue, false to stop.
	 @param iPrintData		IN IPrintData containing all the print settings to be used.
	 @param iOutputPages	IN IOutputPages containing the pages the info was gathered for.
	 @param iPrintJobData	IN IPrintJobData containing the gathered information.
	 */
	virtual void AfterPrintGatherCmd (
			bool16&				bReturn,
			IPrintData*			iPrintData,
			IOutputPages*		iOutputPages,
			IPrintJobData*		iPrintJobData
			) = 0;


	/**
	 Called before initialization of the print job parameters.
	 @param bReturn			OUT Return value: true to continue, false to stop.
	 @param iPrintData		IN IPrintData containing all the print settings to be used.
	 @param iOutputPages	IN IOutputPages containing the pages to output.
	 @param iPrintJobData	IN IPrintJobData containing the gathered information.
	 */
	virtual void BeforePrintJobParamsInit (
			bool16&				bReturn,
			IPrintData*			iPrintData,
			IOutputPages*		iOutputPages,
			IPrintJobData*		iPrintJobData
			) = 0;

	/**
	 Called after initialization of the print job parameters.
	 @param bReturn			OUT Return value: true to continue, false to stop.
	 @param iPrintData		IN IPrintData containing all the print settings to be used.
	 @param iOutputPages	IN IOutputPages containing the pages to output.
	 @param iPrintJobData	IN IPrintJobData containing the gathered information.
	 */
	virtual void AfterPrintJobParamsInit (
			bool16&				bReturn,
			IPrintData*			iPrintData,
			IOutputPages*		iOutputPages,
			IPrintJobData*		iPrintJobData
			) = 0;

	/**
	 Called before the print loop starts.
	 @param bReturn			OUT Return value: true to continue, false to stop.
	 @param iPrintData		IN IPrintData containing all the print settings to be used.
	 @param iOutputPages	IN IOutputPages containing the pages to output.
	 @param iPrintJobData	IN IPrintJobData containing the gathered information.
	 */
	virtual void BeforePrintLoop (
			bool16&				bReturn,
			IPrintData*			iPrintData,
			IOutputPages*		iOutputPages,
			IPrintJobData*		iPrintJobData
			) = 0;

	/**
	 Called when the printing has ended. Doing so ensures that the ref counts 
	 for all interfaces are properly decremented and any other cleanup
	 tasks are completed..
	 The PM global error code denotes the final status of the print job:
		kSuccess if the print job completed successfully,
		kCancel if the print job was cancelled,
		an error code if the print job failed. 
	 */
	virtual void EndPrint() = 0;


	//
	// Print Loop
	//

	/**
	 Called before a begin page event is processed.
	 @param iPrintData		IN IPrintData containing all the print settings to be used.
	 @param iOutputPages	IN IOutputPages containing the pages to output.
	 @param iPrintJobData	IN IPrintJobData containing the gathered information.
	 @param whichPage		IN Which page is being printed; can be used as index into IOutputPages.
	 */
	virtual void BeginPageEvent (
			IPrintData*			iPrintData,
			IOutputPages*		iOutputPages,
			IPrintJobData*		iPrintJobData,
			int32*				whichPage
			) = 0;

	/**
	 Called before a draw page event is processed.
	 @param bReturn			OUT Return value: true to continue, false to continue to the next event.
	 @param iPrintData		IN IPrintData containing all the print settings to be used.
	 @param iOutputPages	IN IOutputPages containing the pages to output.
	 @param iPrintJobData	IN IPrintJobData containing the gathered information.
	 @param whichPage		IN Which page is being printed; can be used as index into IOutputPages.
	 */
	virtual void BeforeDrawPageEvent (
			bool16&				bReturn,
			IPrintData*			iPrintData,
			IOutputPages*		iOutputPages,
			IPrintJobData*		iPrintJobData,
			int32*				whichPage
			) = 0;

	/**
	 Called before a page is drawn.
	 @param bReturn			OUT Return value: true to continue, false to not draw page or spread.
	 @param iPrintData		IN IPrintData containing all the print settings to be used.
	 @param iOutputPages	IN IOutputPages containing the pages to output.
	 @param whichPage		IN Which page is being printed; can be used as index into IOutputPages.
	 @param outputRect		IN Rect used for setting up the draw manager filter.
	 @param gd				IN Graphics data from which you can get IGraphicsPort, IViewPortAttributes etc.
	 */
	virtual void BeforeDrawPage (
			bool16&				bReturn,
			IPrintData*			iPrintData,
			IOutputPages*		iOutputPages,
			int32*				whichPage,
			PMRect*				outputRect,
			GraphicsData*		gd
			) = 0;

	/**
	 Called after a draw page event is processed.
	 @param iPrintData		IN IPrintData containing all the print settings to be used.
	 @param iOutputPages	IN IOutputPages containing the pages to output.
	 @param iPrintJobData	IN IPrintJobData containing the gathered information.
	 @param whichPage		IN Which page is being printed; can be used as index into IOutputPages.
	 */
	virtual void AfterDrawPageEvent (
			IPrintData*			iPrintData,
			IOutputPages*		iOutputPages,
			IPrintJobData*		iPrintJobData,
			int32*				whichPage
			) = 0;

	/**
	 Called before an InCopy draw galley page event is processed.
	 @param bReturn			OUT Return value: true to continue, false to continue to the next event.
	 @param iPrintData		IN IPrintData containing all the print settings to be used.
	 @param iOutputPages	IN IOutputPages containing the pages to output.
							   The IOutputPages GetNthUIDRef() method returns the physcial galley page number, not the page's UIDRef.
	 @param iPrintJobData	IN IPrintJobData containing the gathered information.
	 @param whichPage		IN Which page is being printed; can be used as index into IOutputPages.
	 */
	virtual void BeforeDrawGalleyPageEvent (
			bool16&				bReturn,
			IPrintData*			iPrintData,
			IOutputPages*		iOutputPages,
			IPrintJobData*		iPrintJobData,
			int32*				whichPage
			) = 0;

	/**
	 Called before an InCopy galley page is drawn.
	 @param bReturn			OUT Return value: true to continue, false to not draw page or spread.
	 @param iPrintData		IN IPrintData containing all the print settings to be used.
	 @param iOutputPages	IN IOutputPages containing the pages to output.
							   The IOutputPages GetNthUIDRef() method returns the physcial galley page number, not the page's UIDRef.
	 @param whichPage		IN Which page is being printed; can be used as index into IOutputPages.
	 @param outputRect		IN Rect used for setting up the draw manager filter.
	 @param gd				IN Graphics data from which you can get IGraphicsPort, IViewPortAttributes etc.
	 */
	virtual void BeforeDrawGalleyPage (
			bool16&				bReturn,
			IPrintData*			iPrintData,
			IOutputPages*		iOutputPages,
			int32*				whichPage,
			PMRect*				outputRect,
			GraphicsData*		gd
			) = 0;

	/**
	 Called after an InCopy draw galley page event is processed.
	 @param iPrintData		IN IPrintData containing all the print settings to be used.
	 @param iOutputPages	IN IOutputPages containing the pages to output.
							   The IOutputPages GetNthUIDRef() method returns the physcial galley page number, not the page's UIDRef.
	 @param iPrintJobData	IN IPrintJobData containing the gathered information.
	 @param whichPage		IN Which page is being printed; can be used as index into IOutputPages.
	 */
	virtual void AfterDrawGalleyPageEvent (
			IPrintData*			iPrintData,
			IOutputPages*		iOutputPages,
			IPrintJobData*		iPrintJobData,
			int32*				whichPage
			) = 0;

	/**
	 Called before an end page event is processed.
	 @param iPrintData		IN IPrintData containing all the print settings to be used.
	 @param iOutputPages	IN IOutputPages containing the pages to output.
	 @param iPrintJobData	IN IPrintJobData containing the gathered information.
	 @param whichPage		IN Which page is being printed; can be used as index into IOutputPages.
	 */
	virtual void EndPageEvent (
			IPrintData*			iPrintData,
			IOutputPages*		iOutputPages,
			IPrintJobData*		iPrintJobData,
			int32*				whichPage
			) = 0;

	/**
	 Called before the end printing event is processed. 
	 */
	virtual void EndPrintingEvent ( ) = 0;

	/**
	 Called before an error event is processed. 
	 NOTE: This is an error event from AGM. InDesign maps the error number to strings
		   that are localized. We do not use the errText that this event provides.
	 @param bReturn			OUT Return value: true to continue, false to not set the global error code.
	 @param iPrintData		IN IPrintData containing all the print settings to be used.
	 @param errorNum		IN Error number.
	 @param errComponent	IN Error component from Bravo.
	 @param errText			IN Error text.
	 @param errOtherInfo	IN Other error information; i.e. name of a problem font.
	 */
	virtual void PrintErrorEvent (
			bool16&				bReturn,
			IPrintData*			iPrintData,
			ErrorCode&			errorNum,
			PMString&			errComponent,
			PMString&			errText,
			PMString&			errOtherInfo
			) = 0;
};

#endif
