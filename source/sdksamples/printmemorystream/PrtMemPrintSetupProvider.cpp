//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/printmemorystream/PrtMemPrintSetupProvider.cpp $
//  
//  Owner: Adobe Developer Technologies
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
//========================================================================================

#include "VCPlugInHeaders.h"			    

// Interface includes:
#include "IPrintData.h"
#include "IOutputPages.h"

// Implementation includes:
#include "CPrintSetupProvider.h"
#include "PrintID.h"

// Project includes:
#include "PrtMemID.h"

// NOTE: See comment about this global flag in PrtMemActionComponent.cpp.
extern bool16 gPrtMemPrintingToMemory;

/**	Implements a print setup provider that 
 * 	customizes print sequences initiated by this plug-in.
 * 	@ingroup printmemorystream
*/
class PrtMemPrintSetupProvider : public CPrintSetupProvider
{
public:
	/** Constructor.
	 * 	@param boss interface ptr from boss object on which this interface is aggregated.
	 */
	PrtMemPrintSetupProvider(IPMUnknown* boss);

	/** Destructor
	 */
	virtual ~PrtMemPrintSetupProvider(void);

	/** See IPrintSetupProvider::StartPrintPub
	 */
	virtual void StartPrintPub(bool16&             bReturn,
							   IDocument*          iDoc,
							   UIDRef&             styleUIDRef,
							   IPrintCmdData::PrintUIOptions&  printPubUIOpt,
							   IInkList*           iInkList,
							   ITrapStyleListMgr*  iTrapListMgr);
	/** See IPrintSetupProvider::StartPrintBook
	 */
	virtual void StartPrintBook(bool16&             bReturn,
								IBook*              iBook,
								UIDList*            pubsUIDList,
								IBookOutputActionCmdData::OutputUIOptions&  printBookUIOpt,
								IInkList*           iInkList,
								ITrapStyleListMgr*  iTrapListMgr);
	/** See IPrintSetupProvider::BeforePrintUI
	 */
	virtual void BeforePrintUI(bool16&              bReturn,
							   IPrintData*          iPrintData);
	/** See IPrintSetupProvider::AfterPrintUI
	 */
	virtual void AfterPrintUI(bool16& bReturn, 
							  IPrintData* iPrintData);
	/** See IPrintSetupProvider::BeforePrintGatherCmd
	 */
	virtual void BeforePrintGatherCmd(bool16& bReturn, 
									  IPrintData* iPrintData, 
									  IOutputPages* iOutputPages);
	/** See IPrintSetupProvider::AfterPrintGatherCmd
	 */
	virtual void AfterPrintGatherCmd(bool16&                bReturn,
									 IPrintData*            iPrintData,
									 IOutputPages*      iOutputPages,
									 IPrintJobData*     iPrintJobData);
	/** See IPrintSetupProvider::BeforePrintJobParamsInit
	 */
	virtual void BeforePrintJobParamsInit(bool16&               bReturn,
										  IPrintData*           iPrintData,
										  IOutputPages*     iOutputPages,
										  IPrintJobData*        iPrintJobData);
	/** See IPrintSetupProvider::AfterPrintJobParamsInit
	 */
	virtual void AfterPrintJobParamsInit(bool16&                bReturn,
										 IPrintData*            iPrintData,
										 IOutputPages*      iOutputPages,
										 IPrintJobData*     iPrintJobData);
	/** See IPrintSetupProvider::EndPrint
	 */
	virtual void EndPrint(void);
	/** See IPrintSetupProvider::BeginPageEvent
	 */
	virtual void BeginPageEvent(IPrintData*         iPrintData,
								IOutputPages*       iOutputPages,
								IPrintJobData*      iPrintJobData,
								int32*              whichPage);
	/** See IPrintSetupProvider::BeforeDrawPageEvent
	 */
	virtual void BeforeDrawPageEvent(bool16&                bReturn,
									 IPrintData*            iPrintData,
									 IOutputPages*      iOutputPages,
									 IPrintJobData*     iPrintJobData,
									 int32*             whichPage);
	/** See IPrintSetupProvider::BeforeDrawPage
	 */
	virtual void BeforeDrawPage(bool16&             bReturn,
								IPrintData*         iPrintData,
								IOutputPages*       iOutputPages,
								int32*              whichPage,
								PMRect*             outputRect,
								GraphicsData*       gd);
	/** See IPrintSetupProvider::AfterDrawPageEvent
	 */
	virtual void AfterDrawPageEvent(IPrintData*         iPrintData,
									IOutputPages*       iOutputPages,
									IPrintJobData*      iPrintJobData,
									int32*              whichPage);
	/** See IPrintSetupProvider::BeforeDrawGalleyPageEvent
	 */
	virtual void BeforeDrawGalleyPageEvent(bool16&              bReturn,
										   IPrintData*          iPrintData,
										   IOutputPages*        iOutputPages,
										   IPrintJobData*       iPrintJobData,
										   int32*               whichPage);
	/** See IPrintSetupProvider::BeforeDrawGalleyPage
	 */
	virtual void BeforeDrawGalleyPage(bool16&               bReturn,
									  IPrintData*           iPrintData,
									  IOutputPages*     iOutputPages,
									  int32*                whichPage,
									  PMRect*               outputRect,
									  GraphicsData*     gd);
	/** See IPrintSetupProvider::AfterDrawGalleyPageEvent
	 */
	virtual void AfterDrawGalleyPageEvent(IPrintData*           iPrintData,
										  IOutputPages*     iOutputPages,
										  IPrintJobData*        iPrintJobData,
										  int32*                whichPage);
	/** See IPrintSetupProvider::EndPageEvent
	 */
	virtual void EndPageEvent(IPrintData*           iPrintData,
							  IOutputPages*     iOutputPages,
							  IPrintJobData*        iPrintJobData,
							  int32*                whichPage);
	/** See IPrintSetupProvider::EndPrintingEvent
	 */
	virtual void EndPrintingEvent(void);
	/** See IPrintSetupProvider::PrintErrorEvent
	 */
	virtual void PrintErrorEvent(bool16&                bReturn,
								 IPrintData*            iPrintData,
								 ErrorCode&         errorNum,
								 PMString&          errComponent,
								 PMString&          errText,
								 PMString&          errOtherInfo);

	DECLARE_HELPER_METHODS()

	private:
	/** cached stream pointer */
	IPMStream* fStream;

	/** Do cleanup of cached members. */
	void Cleanup(void);
};

// CREATE_PMINTERFACE
//	Binds the C++ implementation class onto its ImplementationID 
// 	making the C++ code callable by the application.
CREATE_PMINTERFACE(PrtMemPrintSetupProvider, kPrtMemPrintSetupProviderImpl)

DEFINE_HELPER_METHODS(PrtMemPrintSetupProvider)

/* Constructor
*/
PrtMemPrintSetupProvider::PrtMemPrintSetupProvider(IPMUnknown* boss)
:   HELPER_METHODS_INIT(boss),
	fStream(nil)
{
}

/* Destructor
*/
PrtMemPrintSetupProvider::~PrtMemPrintSetupProvider(void)
{
	this->Cleanup();
}


/* StartPrintPub
 */
void PrtMemPrintSetupProvider::StartPrintPub(bool16&               bReturn,
											 IDocument*            iDoc,
											 UIDRef&               styleUIDRef,
											 IPrintCmdData::PrintUIOptions&    printPubUIOpt,
											 IInkList*         iInkList,
											 ITrapStyleListMgr*    iTrapListMgr)
{
	TRACEFLOW(kPrtMemPluginName, "PrtMemPrintSetupProvider::StartPrintPub()\n");
}

/* StartPrintBook
 */
void PrtMemPrintSetupProvider::StartPrintBook(bool16&   bReturn,
											  IBook*    iBook,
											  UIDList*  pubsUIDList,
											  IBookOutputActionCmdData::OutputUIOptions&    printBookUIOpt,
											  IInkList* iInkList,
											  ITrapStyleListMgr*    iTrapListMgr)
{
	TRACEFLOW(kPrtMemPluginName, "PrtMemPrintSetupProvider::StartPrintBook()\n");
}

/* BeforePrintUI
 */
void PrtMemPrintSetupProvider::BeforePrintUI(bool16&                bReturn,
											 IPrintData*            iPrintData)
{
	TRACEFLOW(kPrtMemPluginName, "PrtMemPrintSetupProvider::BeforePrintUI()\n");
}

/* AfterPrintUI
*/
void PrtMemPrintSetupProvider::AfterPrintUI(bool16& bReturn, 
											IPrintData* iPrintData)
{
	TRACEFLOW(kPrtMemPluginName, "PrtMemPrintSetupProvider::AfterPrintUI()\n");
	do
	{
		// Only do memory printing if asked
		if (gPrtMemPrintingToMemory == kFalse)
		{
			break;
		}
		if (iPrintData == nil)
		{
			ASSERT_FAIL("iPrintData is nil");
			break;
		}
		iPrintData->SetPrintTo(IPrintData::kVirtualPrinter);
		//iPrintData->SetPrinter(PMString("kPrepress File"));
	} while (kFalse);
	bReturn = kTrue;
}

/* BeforePrintGatherCmd
*/
void PrtMemPrintSetupProvider::BeforePrintGatherCmd(bool16& bReturn, 
													IPrintData* iPrintData, 
													IOutputPages* iOutputPages)
{
	TRACEFLOW(kPrtMemPluginName, "PrtMemPrintSetupProvider::BeforePrintGatherCmd()\n");
	do
	{
		// Only do memory printing if asked
		if (gPrtMemPrintingToMemory == kFalse)
		{
			break;
		}

		// if the stream is already cached, make sure we get a new one. 
		this->Cleanup();
		fStream = CreateObject2<IPMStream>(kPrtMemCustomStreamBoss, IID_IPMSTREAM);
		if (fStream == nil)
		{
			ASSERT_FAIL("fStream is nil!");
			break;
		}

		// register the output stream
		iOutputPages->SetOutputStream(fStream);
	} while (false);
	bReturn = kTrue;
}

/* AfterPrintGatherCmd
 */
void PrtMemPrintSetupProvider::AfterPrintGatherCmd(bool16&              bReturn,
												   IPrintData*            iPrintData,
												   IOutputPages*      iOutputPages,
												   IPrintJobData*     iPrintJobData)
{
	TRACEFLOW(kPrtMemPluginName, "PrtMemPrintSetupProvider::AfterPrintGatherCmd()\n");
}
/* BeforePrintJobParamsInit
 */
void PrtMemPrintSetupProvider::BeforePrintJobParamsInit(bool16&             bReturn,
														IPrintData*           iPrintData,
														IOutputPages*     iOutputPages,
														IPrintJobData*        iPrintJobData)
{
	TRACEFLOW(kPrtMemPluginName, "PrtMemPrintSetupProvider::BeforePrintJobParamsInit()\n");
}

/* AfterPrintJobParamsInit
 */
void PrtMemPrintSetupProvider::AfterPrintJobParamsInit(bool16&              bReturn,
													   IPrintData*            iPrintData,
													   IOutputPages*      iOutputPages,
													   IPrintJobData*     iPrintJobData)
{
	TRACEFLOW(kPrtMemPluginName, "PrtMemPrintSetupProvider::AfterPrintJobParamsInit()\n");
}

/* EndPrint
*/
void PrtMemPrintSetupProvider::EndPrint(void)
{
	TRACEFLOW(kPrtMemPluginName, "PrtMemPrintSetupProvider::EndPrint()\n");
	this->Cleanup();
}

/* BeginPageEvent
 */
void PrtMemPrintSetupProvider::BeginPageEvent(IPrintData*           iPrintData,
											  IOutputPages*       iOutputPages,
											  IPrintJobData*      iPrintJobData,
											  int32*              whichPage)
{
	TRACEFLOW(kPrtMemPluginName, "PrtMemPrintSetupProvider::BeginPageEvent()\n");
}

/* BeforeDrawPageEvent
 */
void PrtMemPrintSetupProvider::BeforeDrawPageEvent(bool16&              bReturn,
												   IPrintData*            iPrintData,
												   IOutputPages*      iOutputPages,
												   IPrintJobData*     iPrintJobData,
												   int32*             whichPage)
{
	TRACEFLOW(kPrtMemPluginName, "PrtMemPrintSetupProvider::BeforeDrawPageEvent()\n");
}
/* BeforeDrawPage
 */
void PrtMemPrintSetupProvider::BeforeDrawPage(bool16&               bReturn,
											  IPrintData*         iPrintData,
											  IOutputPages*       iOutputPages,
											  int32*              whichPage,
											  PMRect*             outputRect,
											  GraphicsData*       gd)
{
	TRACEFLOW(kPrtMemPluginName, "PrtMemPrintSetupProvider::BeforeDrawPage()\n");
}

/* AfterDrawPageEvent
 */
void PrtMemPrintSetupProvider::AfterDrawPageEvent(IPrintData*           iPrintData,
												  IOutputPages*       iOutputPages,
												  IPrintJobData*      iPrintJobData,
												  int32*              whichPage)
{
	TRACEFLOW(kPrtMemPluginName, "PrtMemPrintSetupProvider::AfterDrawPageEvent()\n");
}

/* BeforeDrawGalleyPageEvent
 */
void PrtMemPrintSetupProvider::BeforeDrawGalleyPageEvent(bool16&                bReturn,
														 IPrintData*          iPrintData,
														 IOutputPages*        iOutputPages,
														 IPrintJobData*       iPrintJobData,
														 int32*               whichPage)
{
	TRACEFLOW(kPrtMemPluginName, "PrtMemPrintSetupProvider::BeforeDrawGalleyPageEvent()\n");
}

/* BeforeDrawGalleyPage
 */
void PrtMemPrintSetupProvider::BeforeDrawGalleyPage(bool16&             bReturn,
													IPrintData*         iPrintData,
													IOutputPages*       iOutputPages,
													int32*              whichPage,
													PMRect*             outputRect,
													GraphicsData*       gd)
{
	TRACEFLOW(kPrtMemPluginName, "PrtMemPrintSetupProvider::BeforeDrawGalleyPage()\n");
}

/* AfterDrawGalleyPageEvent
 */
void PrtMemPrintSetupProvider::AfterDrawGalleyPageEvent(IPrintData*         iPrintData,
														IOutputPages*       iOutputPages,
														IPrintJobData*      iPrintJobData,
														int32*              whichPage)
{
	TRACEFLOW(kPrtMemPluginName, "PrtMemPrintSetupProvider::AfterDrawGalleyPageEvent()\n");
}

/* EndPageEvent
 */
void PrtMemPrintSetupProvider::EndPageEvent(IPrintData*         iPrintData,
											IOutputPages*       iOutputPages,
											IPrintJobData*      iPrintJobData,
											int32*              whichPage)
{
	TRACEFLOW(kPrtMemPluginName, "PrtMemPrintSetupProvider::EndPageEvent()\n");
}

/* EndPrintingEvent
 */
void PrtMemPrintSetupProvider::EndPrintingEvent(void)
{
	TRACEFLOW(kPrtMemPluginName, "PrtMemPrintSetupProvider::EndPrintingEvent()\n");
}

/* PrintErrorEvent
 */
void PrtMemPrintSetupProvider::PrintErrorEvent(bool16&              bReturn,
											   IPrintData*            iPrintData,
											   ErrorCode&         errorNum,
											   PMString&          errComponent,
											   PMString&          errText,
											   PMString&          errOtherInfo)
{
	TRACEFLOW(kPrtMemPluginName, "PrtMemPrintSetupProvider::PrintErrorEvent()\n");
}

/* Cleanup
*/
void PrtMemPrintSetupProvider::Cleanup(void)
{
	if (fStream != nil)
	{
		fStream->Release();
		fStream = nil;
	}
	
}
// End, PrtMemPrintSetupProvider.cpp.

