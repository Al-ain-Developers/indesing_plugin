//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/printselection/PrnSelPrintSetupProvider.cpp $
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

//Interface includes:
#include "IActiveContext.h"
#include "IDocument.h"
#include "IDrwEvtDispatcher.h"
#include "IDrwEvtHandler.h"
#include "IOutputPages.h"
#include "IPrintData.h"
#include "ISelectionManager.h"
#include "ISession.h" // for the session

// General includes:
#include "CoreResTypes.h"
#include "CPrintSetupProvider.h"
#include "DocumentID.h"
#include "HelperInterface.h"
#include "LocaleSetting.h"
#include "PrintID.h"
#include "ShuksanID.h"
#include "Utils.h"

// Project includes:
#include "PrnSelID.h"
#include "IPrnSelData.h"
#include "IPrnSelSuite.h"
#include "IPrnSelUtils.h"


/**	Provides a mechanism to selectively enter into the print process.

	@ingroup printselection
*/
class PrnSelPrintSetupProvider : public CPrintSetupProvider
{
public:
	/** Constructor
	 */
	PrnSelPrintSetupProvider(IPMUnknown* boss);

	/** Destructor
	 */
	~PrnSelPrintSetupProvider();

	/**	Called after the print UI is shown.
		@param bReturn [out] specifies whether to continue. kFalse means quit.
		@param iPrintData (in) specifies IPrintData containing all print settings used.
	*/
	virtual void AfterPrintUI(bool16& bReturn, IPrintData* iPrintData);

	/**	Called before PrintGatherCmd.
		@param bReturn (in/out) specifies whether to process PrintGatherCmd.
		@param iPrintData (in) specifies IPrintData containing all print settings used.
		@param iOutputPages (in) specifies IOutputPages containing which pages to gather info for. 
	*/
	virtual void BeforePrintGatherCmd(bool16& bReturn, 
									  IPrintData* iPrintData, 
									  IOutputPages* iOutputPages);

	/**	Called to end printing.
	 */
	virtual void EndPrint(void);

	DECLARE_HELPER_METHODS()

	private:
	IDrwEvtHandler* fPSEH;
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class to its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(PrnSelPrintSetupProvider, kPrnSelPrintSetupProviderImpl)

DEFINE_HELPER_METHODS(PrnSelPrintSetupProvider)


/* Constructor
*/
PrnSelPrintSetupProvider::PrnSelPrintSetupProvider(IPMUnknown* boss)
:   HELPER_METHODS_INIT(boss)
{
	fPSEH = nil;
}


/* Destructor
*/
PrnSelPrintSetupProvider::~PrnSelPrintSetupProvider()
{
}


/* AfterPrintUI
*/
void PrnSelPrintSetupProvider::AfterPrintUI(bool16& bReturn, IPrintData* iPrintData)
{
	do
	{
		// check the flag first - if it says "don't return", then skip this whole method
		if (bReturn == kFalse)
		{
			break; // out of do-while
		}
		// We are in the unfortunate position of having to get the
		// active context out of the blue here.
		InterfacePtr<IActiveContext> ac(GetExecutionContextSession()->GetActiveContext(), UseDefaultIID());
		if (ac == nil)
		{
			ASSERT_FAIL("active context is nil");
			break;
		}

		// get the IPrnSelData via the document
		IDocument* doc = ac->GetContextDocument();
		if (doc == nil)
		{
			// we shouldn't be printing if we don't have a document
			ASSERT_FAIL("doc is nil");
			break; 
		}
		ISelectionManager* selectionMgr = ac->GetContextSelection();
		if (selectionMgr == nil)
		{
			ASSERT_FAIL("selectionMgr is nil");
			break; 
		}
		
		
		// Get our custom selection suite
		InterfacePtr<IPrnSelSuite> iPrnSelSuite(selectionMgr, UseDefaultIID());
		
		// Check if the print selection flag is set
		// AND that there is some selection of a supported selection type? 

		bool16 printSelectionFlag = Utils<IPrnSelUtils>()->_GetPrintSelectionFlag(doc);
		if (printSelectionFlag == kFalse)
		{
			// if the flag isn't set, we don't care about the selection
			// just print everything the user wants
			bReturn = kTrue;
		}
		else
		{
			// flag is true
			if (iPrnSelSuite &&
				iPrnSelSuite->CanSetPrintSelectionFlag() == kTrue)
			{
				// Register our special draw event handler for selected items
				
				// Store UIDs of document pages containing selection, as well
				// as UIDs of selected page items in IPrnSelData data structures.
				iPrnSelSuite->StoreSelectionData();

				// Our checkbox is checked, so register our draw event handler.
				InterfacePtr<IDrwEvtDispatcher> 
					prtEvt(GetExecutionContextSession(), IID_IDRWEVTDISPATCHER);
				if (prtEvt != nil)
				{
					prtEvt->RegisterDrawEventServices(kPrintEventService);
				}

				fPSEH = (IDrwEvtHandler*)::CreateObject(kPrnSelDrawServicesBoss, IID_IDRWEVTHANDLER);
				if (fPSEH != nil)
				{
					InterfacePtr<IDrwEvtDispatcher> 
						drawEvtDisp(GetExecutionContextSession(), IID_IDRWEVTDISPATCHER);
					fPSEH->Register(drawEvtDisp);
				}
				// we are ok to continue
				bReturn = kTrue;
			}
			else
			{
				// this case means:
				// * IPrnSelData::GetIsChecked returned kTrue, meaning print only selected items
				// * but there were no selected items
				// so we shall just cancel the print operation by returning kFalse
				bReturn = kFalse;			
			}
		}
	} while (kFalse); 
	if (bReturn == kFalse) 
	{
		TRACEFLOW(kPrnSelPluginName, "PrnSelPrintSetupProvider::AfterPrintUI: We aren't going to print anything...");
	}
}


/* BeforePrintGatherCmd
*/
void PrnSelPrintSetupProvider::BeforePrintGatherCmd(bool16& bReturn, IPrintData* iPrintData, IOutputPages* iOutputPages)
{
	do
	{
		InterfacePtr<IActiveContext> ac(GetExecutionContextSession()->GetActiveContext(), UseDefaultIID());
		if (ac == nil)
		{
			ASSERT_FAIL("active context is nil");
			break;
		}
		IDocument* doc = ac->GetContextDocument();
		if (doc == nil)
		{
			// we shouldn't be printing if we don't have a document
			ASSERT_FAIL("doc is nil");
			break;
		}
		// Get our custom selection suite
		ISelectionManager* selectionMgr = ac->GetContextSelection();
		if (selectionMgr == nil)
		{
			ASSERT_FAIL("selectionMgr is nil");
			break; 
		}
		InterfacePtr<IPrnSelSuite> iPrnSelSuite(selectionMgr, UseDefaultIID());
		
		// Is there a selection? or was PrintSelection flag NOT set?
		if (iPrnSelSuite == nil || 
			Utils<IPrnSelUtils>()->_GetPrintSelectionFlag(doc) == kFalse)
		{
			// exit silently, don't modify the page list
			break;
		}

		// We are only doing pages for the moment
		if (iOutputPages->GetIsSpreads() == kTrue)
		{
			break;
		}

		IDataBase* db = iOutputPages->GetMasterDataBase();
		int32 numPages = iOutputPages->Number();
		UIDList pgList(db);

		InterfacePtr<IPrnSelData> psData(doc, UseDefaultIID());
		if (psData == nil)
		{
			ASSERT_FAIL("psData is nil");
			break;
		}

		// Limit the pages we gather data for to those that 
		// contained a selection.
		for (int32 i = 0; i < numPages; i++)
		{
			UIDRef ref = iOutputPages->GetNthUIDRef(i);
			UID uid = ref.GetUID();

			// Did page contain a qualified selection?
			if (psData->GetPageUIDHadSelection(uid) == kTrue)
			{
				// Add to new UIDList.
				pgList.Append(uid);
			}
		}
		// Initialize output pages from our new UIDList.
		iOutputPages->InitializeFrom(pgList, kFalse);
	} while (0);

	bReturn = kTrue;
}


/* EndPrint
*/
void PrnSelPrintSetupProvider::EndPrint(void)
{
	do
	{
		// Flush the UIDs saved in our custom data structures.
		InterfacePtr<IActiveContext> ac(GetExecutionContextSession()->GetActiveContext(), UseDefaultIID());
		if (ac == nil)
		{
			ASSERT_FAIL("active context is nil");
			break;
		}
		IDocument* doc = ac->GetContextDocument();
		if (doc == nil)
		{
			// we shouldn't be printing if we don't have a document
			ASSERT_FAIL("doc is nil");
			break; 
		}
		InterfacePtr<IPrnSelData> psData(doc, UseDefaultIID());
		if (psData != nil)
		{
			psData->FlushUIDs();
		}

		// If registered, unregister our draw event handler.
		if (fPSEH != nil)
		{
			InterfacePtr<IDrwEvtDispatcher> 
				drawEvtDisp(GetExecutionContextSession(), IID_IDRWEVTDISPATCHER);
			fPSEH->UnRegister(drawEvtDisp);
			fPSEH->Release();
			fPSEH = nil;
		}
	} while (kFalse);
}

// End, PrnSelPrintSetupProvider.cpp