//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customconditionaltext/CusCondTxtResponder.cpp $
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
#include "IConditionalTextFacade.h"
#include "IConditionTagList.h"
#include "ICommandSequence.h"
#include "IExportProviderSignalData.h"
#include "IBoolData.h"
#include "IConditionTagList.h"
#include "IWorkspace.h"
#include "IDocument.h"

// General includes:
#include "CmdUtils.h"
#include "PDFID.h"
#include "CreateObject.h"
#include "CResponder.h"

// Project includes:
#include "CusCondTxtID.h"
#include "ICustomConditionTag.h"
#include "CusCondTxtFacade.h"

/** CusCondTxtResponder
	Handles signals related to print, export to PDF/IDML and new document file actions.  
	The action signals it receives are dictated by the CusCondTxtServiceProvider class.

	CusCondTxtResponder implements IResponder based on
	the partial implementation CResponder.

	@ingroup customconditionaltext	
*/
class CusCondTxtResponder : public CResponder
{
public:
	/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	CusCondTxtResponder(IPMUnknown* boss);

	/**
		Respond() handles the file action signals when they
		are dispatched by the signal manager.  This implementation
		simply creates alerts to display each signal.

		@param signalMgr Pointer back to the signal manager to get
		additional information about the signal.
	*/
	virtual void Respond(ISignalMgr* signalMgr);
	
private:
		
	void RespondExport(ISignalMgr* signalMgr);

	void RespondAfterNewDoc(ISignalMgr* signalMgr);
};


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(CusCondTxtResponder, kCusCondTxtResponderImpl)

/* CusCondTxtActionComponent Constructor
*/
CusCondTxtResponder::CusCondTxtResponder(IPMUnknown* boss) :
	CResponder(boss)
{
}

/* Respond
*/
void CusCondTxtResponder::Respond(ISignalMgr* signalMgr)
{
	// Take action based on the service ID
	switch (signalMgr->GetServiceID().Get())
	{
		case kBeforeExportSignalResponderService:
		case kAfterExportSignalResponderService:
		case kFailedExportSignalResponderService:
			RespondExport(signalMgr);
			break;

		case kAfterNewDocSignalResponderService:	
			RespondAfterNewDoc(signalMgr);
			break;
	}
}

void CusCondTxtResponder::RespondExport(ISignalMgr* signalMgr)
{
	InterfacePtr<IExportProviderSignalData> signalData( signalMgr, UseDefaultIID() ) ;
	if(!signalData)
		return;
	
	CusCondTxtFacade::CustomConditionAttr cusCondAttr;
	PMString format = signalData->GetFormat();
	if(format == "InDesignMarkup")
	{
		cusCondAttr = CusCondTxtFacade::kIdmlVisibility;
	}
	else if(format == "Adobe PDF" || format == "Adobe PDF (Interactive)" || format == "Adobe PDF (Print)")
	{
		cusCondAttr = CusCondTxtFacade::kPrintVisibility;
	}
	else return;
		
	IDocument* document = signalData->GetDocument();
	if(document)
	{
		// Take action based on the service ID
		switch (signalMgr->GetServiceID().Get())
		{
			case kBeforeExportSignalResponderService:
				Utils<ICusCondTxtFacade>()->TurnOffConditionVisibility(document, cusCondAttr);
				break;
			
			case kAfterExportSignalResponderService:
			case kFailedExportSignalResponderService:
				Utils<ICusCondTxtFacade>()->TurnOnConditionVisibility(document);
				break;
		}
	}
}

void CusCondTxtResponder::RespondAfterNewDoc(ISignalMgr* signalMgr)
{
	InterfacePtr<IDocumentSignalData> docData(signalMgr, UseDefaultIID());
	if (docData == nil)
	{
		ASSERT_FAIL("Invalid IDocumentSignalData* - CusCondTxtResponder::RespondAfterNewDoc");
		return;
	}
	
	InterfacePtr<IDocument> newDocument(docData->GetDocument(), UseDefaultIID());
	ASSERT(newDocument);
	if(!newDocument)
		return;
	
	InterfacePtr<IWorkspace> appWS(GetExecutionContextSession()->QueryWorkspace());
	InterfacePtr<IConditionTagList> appConditionTags(appWS, UseDefaultIID());
	
	InterfacePtr<IWorkspace> docWS(newDocument->GetDocWorkSpace(), UseDefaultIID());
	InterfacePtr<IConditionTagList> docConditionTags(docWS, UseDefaultIID());

	if(appConditionTags->GetCount() != docConditionTags->GetCount())
	{
		return;
	}
	
	IDataBase* appDB = ::GetDataBase(appConditionTags);
	IDataBase* docDB = ::GetDataBase(docConditionTags);

	for (int32 i = 0; i < appConditionTags->GetCount(); i++)
	{
		InterfacePtr<ICustomConditionTag> nthAppConditionTag(appDB, appConditionTags->GetNthCondition(i), UseDefaultIID());		
		Utils<ICusCondTxtFacade>()->SetPrintVisibility(UIDRef(docDB, docConditionTags->GetNthCondition(i)), nthAppConditionTag->IsPrintVisible());
		Utils<ICusCondTxtFacade>()->SetIDMLVisibility(UIDRef(docDB, docConditionTags->GetNthCondition(i)), nthAppConditionTag->IsIdmlVisible());
	}
}

// End, CusCondTxtResponder.cpp.
