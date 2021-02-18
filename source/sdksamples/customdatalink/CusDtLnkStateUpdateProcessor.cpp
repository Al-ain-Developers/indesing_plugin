//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalink/CusDtLnkStateUpdateProcessor.cpp $
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
#include "ILinkResourceStateUpdateCmdData.h"

// Implementation includes:
#include "CPMUnknown.h"
#include "StringNumeric.h"
// Project includes:
#include "Utils.h"
#include "ICusDtLnkFacade.h"
#include "CusDtLnkLinkResourceStatePacket.h"
#include "ICusDtLnkStateUpdateProcessor.h"
#include "CusDtLnkID.h"


/** ICusDtLnkStateUpdateProcessor implementation which maintains a queue of CusDtLnkLinkResourceStatePacket.  CusDtLnkLinkResourceStatePacket is
 created by CusDtLnkLinkResourceStateUpdater, when the updater is asked by link manager to give a state update for a link resource, it creates
 a packet which contains a snapshot of the resource state at the time when link manager asks for status update.  The packet is then queued in the
 fJobQueue of CusDtLnkStateUpdateProcessor.  The CusDtLnk sample has an idle task, which will call CusDtLnkStateUpdateProcessor::UpdateStateForTopJob
 each time the task is run, which essentially takes one packet off the queue and update the packet with the latest resource information.
 
 @ingroup customdatalink
 @see ICusDtLnkStateUpdateProcessor
 */
class CusDtLnkStateUpdateProcessor : public CPMUnknown<ICusDtLnkStateUpdateProcessor>
{
public:
	/**
	 Constructor.
	 @param boss interface ptr from boss object on 
	 which this interface is aggregated.
	 */
	CusDtLnkStateUpdateProcessor(IPMUnknown* boss);
	
	/** Destructor
	 */
	virtual ~CusDtLnkStateUpdateProcessor() {}
	
	
	/** Add a job (CusDtLnkLinkResourceStatePacket) to the processor
	 
	 @return kTrue if job is added successfully.
	 */
	virtual bool16 AddJob(const CusDtLnkLinkResourceStatePacket& job);
	
	/** Remove the job (CusDtLnkLinkResourceStatePacket) from the processor
	 
	 @return kTrue if job is removed successfully.
	 */
	virtual bool16 RemoveJob(const CusDtLnkLinkResourceStatePacket& job);
	
	/** Remove the job from the processor
	 
	 @return kTrue if job is removed successfully.
	 */
	virtual bool16 IsJobPending(const CusDtLnkLinkResourceStatePacket& job) const;
	
	/** The state updater mainains a job queue. A job is to provide state update for a particular linkr resource.
	 This routine process the state update function given a particular job packet, and remove it from the queue
	 
	 @return kTrue if job is removed successfully.
	 */
	virtual bool16 UpdateStateForJob(const CusDtLnkLinkResourceStatePacket& job);
	
	/**
	 The state updater mainains a job queue. A job is to provide state update for a particular linkr resource.
	 This routine removes a job from the job queue and process the state update function
	 */
	virtual bool16 UpdateStateForTopJob();
private:
	
	std::vector<CusDtLnkLinkResourceStatePacket> fJobQueue;
};

/*	Makes the implementation available to the application.
 */
CREATE_PMINTERFACE(CusDtLnkStateUpdateProcessor, kCusDtLnkStateUpdateProcessorImpl)


/* Constructor
 */
CusDtLnkStateUpdateProcessor::CusDtLnkStateUpdateProcessor(IPMUnknown* boss) :
CPMUnknown<ICusDtLnkStateUpdateProcessor>(boss)
{
}


/*
 */
bool16 CusDtLnkStateUpdateProcessor::AddJob(const CusDtLnkLinkResourceStatePacket& job)
{
	std::vector<CusDtLnkLinkResourceStatePacket>::iterator iter = std::find(fJobQueue.begin(), fJobQueue.end(), job);
	if (iter != fJobQueue.end()) {
		fJobQueue.erase(iter);
	}
	fJobQueue.push_back(job);
	return true;
}


/*
 */
bool16 CusDtLnkStateUpdateProcessor::RemoveJob(const CusDtLnkLinkResourceStatePacket& job)
{
	std::vector<CusDtLnkLinkResourceStatePacket>::iterator iter = std::find(fJobQueue.begin(), fJobQueue.end(), job);
	if (iter != fJobQueue.end()) {
		fJobQueue.erase(iter);
		return true;
	}
	else
		return false;
}


/*
 */
bool16 CusDtLnkStateUpdateProcessor::IsJobPending(const CusDtLnkLinkResourceStatePacket& job) const
{
	std::vector<CusDtLnkLinkResourceStatePacket>::const_iterator iter = std::find(fJobQueue.begin(), fJobQueue.end(), job);
	if (iter != fJobQueue.end())
		return true;
	else
		return false;
}

/*
 */
bool16 CusDtLnkStateUpdateProcessor::UpdateStateForJob(const CusDtLnkLinkResourceStatePacket& job)
{	
	std::vector<CusDtLnkLinkResourceStatePacket>::iterator iter = std::find(fJobQueue.begin(), fJobQueue.end(), job);
	if (iter != fJobQueue.end()) {
		CusDtLnkLinkResourceStatePacket& packet = *iter;
		
		const WideString kMyScheme(kCusDtLnkScheme);
		URI uri = packet.GetURI();
		WideString scheme = uri.GetComponent(URI::kScheme);
		if (scheme == kMyScheme)
		{
			IDFile	file;
			// Use URIToIDFile to check the following conditions:
			// 1 if we have no notion where the database we refer to is, we are plain "missing"
			// 2 if there is not a record in the database for the asset, it is missing too
			// 3 if there is not a localfile for the asset, then it is missing
			// if a valid IDFile existed, the state will be ILinkResource::kAvailable, otherwise ILinkResource::kMissing
			Utils<ICusDtLnkFacade>()->URIToIDFile(uri, file);
			bool bFileExists(file.Exists());
			packet.SetState(bFileExists ? ILinkResource::kAvailable : ILinkResource::kMissing);
			if (bFileExists)
			{
				uint64 size(file.GetSize());
				WideString sizeStr;
				if (stringnumeric::ToString(size, sizeStr) != kSuccess) {
					// bail, since it is better to leave the stamp in a out-of-date but correct state
					ASSERT_FAIL("CusDtLnkFacade::UpdateLinkResourceState - File size to WideString failed!");
					return false;
				}
				
				uint64 modTime = Utils<ICusDtLnkFacade>()->GetAssetTimestampFromURI(uri);
				WideString modTimeStr;
				if (stringnumeric::ToString(modTime, modTimeStr) != kSuccess) {
					// bail, since it is better to leave the stamp in a out-of-date but correct state
					ASSERT_FAIL("FileLinkResourceStateProcessor::UpdateState - File modified time to WideString failed!");
					return false;
				}
				// update the resource's stamp
				WideString stamp;
				stamp.Append(scheme);
				stamp.Append(modTimeStr);
				stamp.Append(WideString(" "));
				stamp.Append(sizeStr);
				
				packet.SetStamp(stamp);
				packet.SetModTime(modTime);
				packet.SetSize(size);
			}
		}	// if (scheme == kMyScheme)
		
		if (packet.LinkResourceChanged()) {
			InterfacePtr<ICommand> updateCmd(CmdUtils::CreateCommand(kLinkResourceStateUpdateCmdBoss));
			InterfacePtr<ILinkResourceStateUpdateCmdData> updateCmdData(updateCmd, UseDefaultIID());
			
			updateCmdData->SetResource(packet.GetResource());
			updateCmdData->SetDatabase(packet.GetDatabase());
			updateCmdData->SetNotify(packet.GetNotify());
			
			if (packet.URIChanged()) {
				updateCmdData->SetUpdateAction(ILinkResourceStateUpdateCmdData::kUpdateURI);
				updateCmdData->SetURI(packet.GetURI());
			}
			else if (packet.StateChanged()) {
				updateCmdData->SetUpdateAction(ILinkResourceStateUpdateCmdData::kUpdateState);
				updateCmdData->SetState(packet.GetState());
				updateCmdData->SetStamp(packet.GetStamp());
				updateCmdData->SetModTime(packet.GetModTime());
				updateCmdData->SetSize(packet.GetSize());
			}
			else if (packet.StampChanged()) {
				updateCmdData->SetUpdateAction(ILinkResourceStateUpdateCmdData::kUpdateStamp);
				updateCmdData->SetStamp(packet.GetStamp());
				updateCmdData->SetModTime(packet.GetModTime());
				updateCmdData->SetSize(packet.GetSize());
			}
			else if (packet.ModTimeChanged()) {
				updateCmdData->SetUpdateAction(ILinkResourceStateUpdateCmdData::kUpdateModTime);
				updateCmdData->SetModTime(packet.GetModTime());
			}
			else if (packet.SizeChanged()) {
				updateCmdData->SetUpdateAction(ILinkResourceStateUpdateCmdData::kUpdateSize);
				updateCmdData->SetSize(packet.GetSize());
			}
			
			if (packet.GetOperationType() == ILinkManager::kAsynchronous) {
				CmdUtils::ScheduleCommand(updateCmd, ICommand::kMediumPriority);
			}
			else {
				CmdUtils::ProcessCommand(updateCmd);
			}
		}
		fJobQueue.erase(iter);	// remove job from queue
		return true;
	}
	else
		return false;
}

/*
 */
bool16 CusDtLnkStateUpdateProcessor::UpdateStateForTopJob()
{
	if (fJobQueue.empty())
		return true;
	
	CusDtLnkLinkResourceStatePacket& packet = fJobQueue.front();
	return UpdateStateForJob(packet);
}


// end:	PrnSelSuiteASB.cpp

