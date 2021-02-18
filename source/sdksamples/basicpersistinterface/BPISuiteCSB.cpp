//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicpersistinterface/BPISuiteCSB.cpp $
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

// Interface includes
#include "IDocumentBroadcastMsg.h"
#include "ICommand.h"
								
// General includes
#include "K2Vector.tpp"
#include "SelectionExtTemplates.tpp"
#include "GenericID.h"
#include "UIDList.h"

// Project includes
#include "BPIID.h"
#include "IBPIData.h"
#include "IBPISuite.h"
#include "BPISuiteCSB.h"
#include "BPIHelper.h"

/* Constructor
*/
BPISuiteCSB::BPISuiteCSB(IPMUnknown* iBoss) :
	CPMUnknown<IBPISuite>(iBoss)
{
}

/* Destructor
*/
BPISuiteCSB::~BPISuiteCSB(void)
{
}

/* 
*/
bool16 BPISuiteCSB::CanApplyBPIData(void)
{
	bool16 result = kFalse;
	do {
		UIDList target = this->GetTarget();
		if (target.Length() <= 0) {	
			break;
		}
		BPIHelper bpiHelper;
		result = bpiHelper.HasBPIData(target);
	} while (false);
	return result;
}

/*
*/
ErrorCode BPISuiteCSB::ApplyBPIData(const WideString& value)
{
	ErrorCode result = kFailure;
	do {
		UIDList target = this->GetTarget();
		BPIHelper bpiHelper;
		bpiHelper.FilterForBPIData(target);
		if (target.Length() <= 0) {	
			break;
		}
		result = bpiHelper.ProcessBPISetDataCmd(target, value);
	} while (false);
	return (result);
}

/*
*/
bool16 BPISuiteCSB::CanGetBPIData(void)
{
	return this->CanApplyBPIData();
}

/*
*/
void BPISuiteCSB::GetBPIData(K2Vector<WideString>& values)
{
	do {
		UIDList target = this->GetTarget();
		if (target.Length() <= 0) {	
			break;
		}
		BPIHelper bpiHelper;
		bpiHelper.GetBPIData(target, values);
	} while(false);
}	

/*
*/
void BPISuiteCSB::Startup(void)
{
//	TRACEFLOW(kBPIPluginName, "BPISuiteCSB::Startup-->In\n");
//	TRACEFLOW(kBPIPluginName, "BPISuiteCSB::Startup-->Out\n");
}


/*
*/
void BPISuiteCSB::Shutdown(void)
{
//	TRACEFLOW(kBPIPluginName,"BPISuiteCSB::Shutdown-->In\n");
//	TRACEFLOW(kBPIPluginName,"BPISuiteCSB::Shutdown-->Out\n");
}

/*
*/
void BPISuiteCSB::SelectionChanged(SuiteBroadcastData* broadcastData, const PMIID& messageID, void* message)
{
//	TRACEFLOW(kBPIPluginName,"BPISuiteCSB::SelectionChanged-->In\n");
//	TRACEFLOW(kBPIPluginName,"BPISuiteCSB::SelectionChanged-->Out\n");
}

/*
*/
ProtocolCollection*	BPISuiteCSB::CreateObserverProtocolCollection(void)
{
//	TRACEFLOW(kBPIPluginName, "BPISuiteCSB::CreateObserverProtocolCollection-->In\n");
	ProtocolCollection*	protocolList = new ProtocolCollection();
	protocolList->insert(protocolList->begin(), 1, IBPIData::kDefaultIID);
//	TRACEFLOW(kBPIPluginName, "BPISuiteCSB::CreateObserverProtocolCollection-->Out\n");
	return protocolList;
}

/*
*/
void BPISuiteCSB::SelectionAttributeChanged(SuiteBroadcastData* broadcastData, const PMIID& messageID, void* message)
{
//	TRACEFLOW(kBPIPluginName, "BPISuiteCSB::SelectionAttributeChanged-->In\n");
	do {
		// Changes to IBPIData are posted inside messages of type IDocumentBroadcastMsg.
		// Check that we have received a message that might be of interest to
		// IBPISuite client code.
		if (messageID != IID_IDOCUMENT_BROADCAST) {
			// Just stop, this is a message we don't handle or tell
			// IBPISuite clients about.
			break;
		}

		// Check message contains a protocol we registered in CreateObserverProtocolCollection.
		IDocumentBroadcastMsg* documentMessage = static_cast<IDocumentBroadcastMsg*>(message);
		if (documentMessage->GetPMIID () != IBPIData::kDefaultIID) {
			// We shouldn't be sent IDocumentBroadcastMsg messages we didn't ask for.
			ASSERT_FAIL("BPISuiteCSB::SelectionAttributeChanged called for an unregistered protocol.");
			break;
		}

		// The command that made the change to IBPIData is indicated
		// by the IDocumentBroadcastMsg.
		// Check the state of the command indicates that the 
		// change is complete. 
		ICommand* cmd = static_cast<ICommand*>(documentMessage->GetVoidStar());
		ASSERT(cmd);
		if (!cmd) {
			break;
		}
		if (!(cmd->GetCommandState() == ICommand::kDone)) {
			break;
		}

 		// Check that at least one item whose IBPIData has changed
		// is a selected object.
		const UIDList& itemList = cmd->GetItemListReference();
		if (this->IntersectsTarget(itemList) == kFalse) {
			break;
		}

		// Check we didn't already post a message to client code about
		// change to IBPIData.
		int32 keyLocation = FindLocationInSorted(*broadcastData, static_cast<PMIID>(IBPISuite::kDefaultIID));
		if (keyLocation >= 0){
			// We already posted a message.
			// Note that ::InsertOrReplaceKeyValueInSorted is useful if you 
			// need to replace any message you already posted.
			// See header KeyValuePair.h.
			break;
		}

		// Post a message to clients of IBPISuite about the change.
		// Note that me message is independent of the underlying
		// data model. We don't pass protocol IBPIData::kDefaultIID,
		// we pass the suite's protocol, IBPISuite::kDefaultIID.
		// Client code must be kept decoupled from the model.
		::InsertKeyValueInSorted(*broadcastData, static_cast<PMIID>(IBPISuite::kDefaultIID), boost::shared_ptr<SelectionSuiteData>());

	} while(false);
//	TRACEFLOW(kBPIPluginName, "BPISuiteCSB::SelectionAttributeChanged-->Out\n");
}

/*
*/
void BPISuiteCSB::HandleIntegratorSuiteMessage(void* message, const ClassID&, ISubject*, const PMIID&, void*)
{
//	TRACEFLOW(kBPIPluginName,"BPISuiteCSB::HandleIntegratorSuiteMessage-->In\n");
	ASSERT_FAIL("BPISuiteCSB::HandleIntegratorSuiteMessage should never be called");
//	TRACEFLOW(kBPIPluginName,"BPISuiteCSB::HandleIntegratorSuiteMessage-->Out\n");
}

/*
*/
bool16 BPISuiteCSB::IntersectsTarget(const UIDList& itemList)
{
	bool16 result = kFalse;
	do {
		UIDList target = this->GetTarget();
		if (itemList.GetDataBase() != target.GetDataBase()) {
			// Different databases so no intersection.
			break;
		}
		for (int32 i = 0 ; i < itemList.Length(); i++) {
			if (target.Location(itemList[i]) >= 0) {
				result = kTrue;
				break;
			}
		}
	} while(false);
	return result;
}	

// End, BPISuite.cpp