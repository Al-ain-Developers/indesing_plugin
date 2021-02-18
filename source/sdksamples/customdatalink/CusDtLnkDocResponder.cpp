//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalink/CusDtLnkDocResponder.cpp $
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
#include "IClassIDData.h"
#include "isignalmgr.h"
#include "IDocumentSignalData.h"
#include "IUIDData.h"
#include "IDocument.h"
#include "IWorkspace.h"
#include "IObserver.h"
#include "ICusDtLnkFacade.h"
// Implementation includes:

#include "CResponder.h"
#include "Utils.h"
#include "DebugClassUtils.h"

#include "CusDtLnkID.h"

/** Implements IResponder based on
	the partial implementation CResponder.
	Main function is to attach and detach our doc-observer.

	@see CusDtLnkDocRespServiceProvider for signals we receive
	@ingroup customdatalink
	
*/
class CusDtLnkDocResponder : public CResponder
{
	public:
	
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		CusDtLnkDocResponder(IPMUnknown* boss);

		/**
			Respond() handles the file action signals when they
			are dispatched by the signal manager.  This implementation
			simply creates alerts to display each signal.

			@param signalMgr Pointer back to the signal manager to get
			additional information about the signal.
		*/
		virtual void Respond(ISignalMgr* signalMgr);

};


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(CusDtLnkDocResponder, kCusDtLnkDocResponderImpl)

/* CusDtLnkActionComponent Constructor
*/
CusDtLnkDocResponder::CusDtLnkDocResponder(IPMUnknown* boss) :
	CResponder(boss)
{
}

/* Respond
*/
void CusDtLnkDocResponder::Respond(ISignalMgr* signalMgr)
{
	do {
		// Get a UIDRef for the document.  It will be an invalid UIDRef
		// for BeforeNewDoc, BeforeOpenDoc, AfterSaveACopy, and AfterCloseDoc because
		// the document doesn't exist at that point.
		InterfacePtr<IDocumentSignalData> documentSignalData(signalMgr, UseDefaultIID());
		ASSERT(documentSignalData);
		if (!documentSignalData) {
			break;

		}
		UIDRef documentUIDRef = documentSignalData->GetDocument();
		if (documentUIDRef.GetDataBase() != nil)
		{
			InterfacePtr<IDocument> document(documentUIDRef, UseDefaultIID());
			ASSERT(document);
			if(document) {
				PMString docName;
				document->GetName(docName);
				TRACEFLOW(kCusDtLnkPluginName, "Document name=%s, ", docName.GetPlatformString().c_str());
			}
		}

		
const ServiceID serviceID = signalMgr->GetServiceID();
#ifdef DEBUG
		DebugClassUtilsBuffer serviceBuf;
		const char* serviceName = DebugClassUtils::GetIDName(&serviceBuf, serviceID);
		TRACEFLOW(kCusDtLnkPluginName, "Respond: serviceName=%s, ", serviceName);
#endif

		// TRACE the command associated with the signal.
		
		ICommand* signallingCommand = documentSignalData->GetCommand();
		ASSERT(signallingCommand);
		if (!signallingCommand) {
			break;
		}
		const ICommand::CommandState cmdState = signallingCommand->GetCommandState();
#ifdef DEBUG		
			DebugClassUtilsBuffer classBuf;
			const char* className = DebugClassUtils::GetIDName(&classBuf, ::GetClass(signallingCommand));
			TRACEFLOW(kCusDtLnkPluginName, " signalling cmd=%s, cmdState=%d\n", 
				className,
				cmdState);			
#endif

		// Take action based on the service ID
		switch (serviceID.Get())
		{
			case kBeforeNewDocSignalResponderService:
			break;

			case kDuringNewDocSignalResponderService:
			{ // Copy workspace database options to documents
				Utils<ICusDtLnkFacade> facade;
				InterfacePtr<IWorkspace> appWorkspace(GetExecutionContextSession()->QueryWorkspace());
				InterfacePtr<IDocument> doc(documentUIDRef, UseDefaultIID());
				InterfacePtr<IWorkspace> docWorkspace(doc->GetDocWorkSpace(), UseDefaultIID());
				int32 dbCount = facade->GetAssetDataBaseCount(appWorkspace);
				for(int32 i=0; i < dbCount; i++) 
				{
					PMString dbName = facade->GetNthAssetDataBase(appWorkspace, i);
					if(dbName.empty()) {
						continue;
					}
					PMString path = facade->GetAssetDataBasePath(appWorkspace, dbName);
					ErrorCode err = facade->AddAssetDataBase(docWorkspace, dbName,path);
				}
				break;
			}

			case kAfterNewDocSignalResponderService:
			case kDuringOpenDocSignalResponderService:
			{
				InterfacePtr<IObserver> docObserver(documentUIDRef, IID_ICUSDTLNKDOCOBSERVER);
				if (docObserver != nil) {
					docObserver->AutoAttach();
				}
				break;
			}
			
			

			case kBeforeOpenDocSignalResponderService:
			break;

			// We used this case already above
			//case kDuringOpenDocSignalResponderService:
			//break;

			case kAfterOpenDocSignalResponderService:
			break;

			case kBeforeSaveDocSignalResponderService:
			break;

			case kAfterSaveDocSignalResponderService:
			break;

			case kBeforeSaveAsDocSignalResponderService:
			break;

			case kAfterSaveAsDocSignalResponderService:
			break;

			case kBeforeSaveACopyDocSignalResponderService:
			break;

			case kDuringSaveACopyDocSignalResponderService:
			break;

			case kAfterSaveACopyDocSignalResponderService:
			break;

			case kBeforeRevertDocSignalResponderService:
			break;

			case kAfterRevertDocSignalResponderService:
			break;

			case kBeforeCloseDocSignalResponderService:
			{
				InterfacePtr<IObserver> docObserver(documentUIDRef, IID_ICUSDTLNKDOCOBSERVER);
				if (docObserver != nil) {
					docObserver->AutoDetach();
				}
			
			}
			break;

			case kAfterCloseDocSignalResponderService:
			break;

			default:
				break;
	}

		} while(kFalse);
}
