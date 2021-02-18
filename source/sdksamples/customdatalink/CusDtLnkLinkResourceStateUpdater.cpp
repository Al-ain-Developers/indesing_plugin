//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalink/CusDtLnkLinkResourceStateUpdater.cpp $
//  
//  Owner: Michael Easter
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
#include "CPMUnknown.h"
#include "ILinkResourceStateUpdater.h"

#include "ICusDtLnkStateUpdateProcessor.h"
#include "ILinkResourceStateUpdateCmdData.h"

#include "CusDtLnkLinkResourceStatePacket.h"
#include "CusDtLnkID.h"


//========================================================================================
// Class CusDtLnkLinkResourceStateUpdater
//========================================================================================
/**
	Provide state update specifically to link resource whose URI scheme matches the one specified in 
	CusDtLnkLinkResourceFactory, i.e., 'CSVLink'.  Link manager will call ILinkResourceStateUpdater
	when necessary, and it may request a synchronous or asynchronous update.  The main difference is
	you have to make sure synchronous update is done upon return to the caller (link manager).
	
	ILinkResourceStateUpdater will be given a link resource's UID when it is called to update its state.
	Typically, you "package" whatever information (probably most likely from the link resource) is pertinent 
	to your state update in a AsyncWorkPacket, and then you enque the packet with IExtLinkStateUpdateProcessor.  
	Then an idle task CusDtLnkLinkResourceStateUpdaterIdleTask will process the packet (i.e. provide the 
	latest state information) when your packet's turn is up in the queue.
 
	@ingroup customdatalink
	@see CusDtLnkLinkResourceFactory
	@see CusDtLnkLinkResourceStatePacket
	@see CusDtLnkLinkResourceStateProcessor
	@see CusDtLnkLinkResourceStateProcessorFactory
*/
class CusDtLnkLinkResourceStateUpdater : public CPMUnknown<ILinkResourceStateUpdater>
{
public:
	typedef CPMUnknown<ILinkResourceStateUpdater> inherited;
	typedef object_type data_type;

	CusDtLnkLinkResourceStateUpdater(IPMUnknown* boss);
	virtual ~CusDtLnkLinkResourceStateUpdater();

	/**	
		Delegate to UpdateResourceState
		@see ILinkResourceHandler::UpdateResourceStateSync
	 */
	virtual ErrorCode UpdateResourceStateSync(const UIDRef& resourceRef, bool bNotify);
	/**	
		Delegate to UpdateResourceState
		@see ILinkResourceHandler::UpdateResourceStateAsync
	 */
	virtual ErrorCode UpdateResourceStateAsync(const UIDRef& resourceRef);

	/**	
		When you enqueue an AsyncWorkPacket, you supply an AsyncWorkPacketJobSpec that can identify
		your packet.  When link manager needs to cancel the resource update state request for whatever reason, 
		we search all outstanding AsyncWorkPackets for matches with the AsyncWorkPacketJobSpec when we enqueued it.
		Then we cancel the job.
		
		@see ILinkResourceHandler::CancelUpdateResourceState
	 */
	virtual void CancelUpdateResourceState(const UIDRef& resourceRef);

	virtual void WaitForUpdateResourceStateCompletion(const UIDRef& resourceRef) {}

	/**	@see ILinkResourceHandler::ResolveResource
	 */
	virtual ErrorCode ResolveResource(const UIDRef& resourceRef, const URI& relativeURI, bool bIgnoreStamp);

private:
	// Prevent copy construction and assignment.
	CusDtLnkLinkResourceStateUpdater(const CusDtLnkLinkResourceStateUpdater&);
	CusDtLnkLinkResourceStateUpdater& operator=(const CusDtLnkLinkResourceStateUpdater&);

	ErrorCode UpdateResourceState(const UIDRef& resourceRef, bool bNotify, bool bSynchronous) const;
};

CREATE_PMINTERFACE(CusDtLnkLinkResourceStateUpdater, kCusDtLnkLinkResourceStateUpdaterImpl)


//========================================================================================
//
// CusDtLnkLinkResourceStateUpdater Public Implementation
//
//========================================================================================

//========================================================================================
// Constructor
//========================================================================================
CusDtLnkLinkResourceStateUpdater::CusDtLnkLinkResourceStateUpdater(IPMUnknown* boss)
: inherited(boss)
{
}

//========================================================================================
// Destructor
//========================================================================================
CusDtLnkLinkResourceStateUpdater::~CusDtLnkLinkResourceStateUpdater()
{
}

//========================================================================================
// CusDtLnkLinkResourceStateUpdater::UpdateResourceStateSync
//========================================================================================
ErrorCode CusDtLnkLinkResourceStateUpdater::UpdateResourceStateSync(const UIDRef& resourceRef, bool bNotify)
{
	return UpdateResourceState(resourceRef, bNotify, true);
}

//========================================================================================
// CusDtLnkLinkResourceStateUpdater::UpdateResourceStateAsync
//========================================================================================
ErrorCode CusDtLnkLinkResourceStateUpdater::UpdateResourceStateAsync(const UIDRef& resourceRef)
{
	return UpdateResourceState(resourceRef, true, false);
}

//========================================================================================
// CusDtLnkLinkResourceStateUpdater::CancelUpdateResourceState
//========================================================================================
void CusDtLnkLinkResourceStateUpdater::CancelUpdateResourceState(const UIDRef& resourceRef)
{
	IDataBase* db = resourceRef.GetDataBase();
	InterfacePtr<ILinkManager> iLinkMgr(db, db->GetRootUID(), UseDefaultIID());
	if (!iLinkMgr) {
		ASSERT_FAIL("CusDtLnkLinkResourceStateUpdater::CancelUpdateResourceState() - ILinkManager is nil!");
		return;
	}
	
	UID resourceUID = resourceRef.GetUID();
	
	// check to make sure we have a valid resource to queue
	InterfacePtr<ILinkResource> iResource(iLinkMgr->QueryResourceByUID(resourceUID));
	if (!iResource) {
		ASSERT_FAIL("CusDtLnkLinkResourceStateUpdater::CancelUpdateResourceState() - ILinkResource is nil!");
		return;
	}
	
	ClassID providerId = iLinkMgr->GetResourceProviderByScheme(iResource->GetURI().GetComponent(URI::kScheme));
	if (!providerId.IsValid()) {
		ASSERT_FAIL("CusDtLnkLinkResourceStateUpdater::CancelUpdateResourceState() - resource provider id is invalid!");
		return;
	}
	
	CusDtLnkLinkResourceStatePacket job(ILinkManager::kAsynchronous,
										   false,
										   db,
										   resourceUID,
										   iResource->GetURI(),
										   iResource->GetState(),
											iResource->GetStamp(),
											iResource->GetModTime(),
											iResource->GetSize());
	
	// first check to see if a job is already pending
	InterfacePtr<ICusDtLnkStateUpdateProcessor> stateUpdateProcessor(GetExecutionContextSession(), UseDefaultIID());
	if (stateUpdateProcessor) {
		if (stateUpdateProcessor->IsJobPending(job))
			stateUpdateProcessor->RemoveJob(job);
	}
}

//========================================================================================
// CusDtLnkLinkResourceStateUpdater::ResolveResource
//========================================================================================
ErrorCode CusDtLnkLinkResourceStateUpdater::ResolveResource(const UIDRef& resourceRef, const URI& relativeURI, bool bIgnoreStamp)
{
	#pragma unused(resourceRef, relativeURI, bIgnoreStamp)
	return kFailure;
}


//========================================================================================
//
// CusDtLnkLinkResourceStateUpdater Private Implementation
//
//========================================================================================

//========================================================================================
// CusDtLnkLinkResourceStateUpdater::UpdateResourceState
//========================================================================================
ErrorCode CusDtLnkLinkResourceStateUpdater::UpdateResourceState(const UIDRef& resourceRef, bool bNotify, bool bSynchronous) const
{
	IDataBase* db = resourceRef.GetDataBase();
	InterfacePtr<ILinkManager> iLinkMgr(db, db->GetRootUID(), UseDefaultIID());
	if (!iLinkMgr) {
		ASSERT_FAIL("CusDtLnkLinkResourceStateUpdater::UpdateResourceState() - ILinkManager is nil!");
		return kFailure;
	}
	
	UID resourceUID = resourceRef.GetUID();
	
	// check to make sure we have a valid resource to queue
	InterfacePtr<ILinkResource> iResource(iLinkMgr->QueryResourceByUID(resourceUID));
	if (!iResource) {
		ASSERT_FAIL("CusDtLnkLinkResourceStateUpdater::UpdateResourceState() - ILinkResource is nil!");
		return kFailure;
	}
	
	ClassID providerId = iLinkMgr->GetResourceProviderByScheme(iResource->GetURI().GetComponent(URI::kScheme));
	if (!providerId.IsValid()) {
		ASSERT_FAIL("CusDtLnkLinkResourceStateUpdater::UpdateResourceState() - resource provider id is invalid!");
		return kFailure;
	}
	InterfacePtr<ICusDtLnkStateUpdateProcessor> stateUpdateProcessor(GetExecutionContextSession(), UseDefaultIID());
	if (!stateUpdateProcessor) {
		ASSERT_FAIL("CusDtLnkLinkResourceStateUpdater::UpdateResourceState() - stateUpdateProcessor is nil!");
		return kFailure;
	}
	
	CusDtLnkLinkResourceStatePacket job(bSynchronous ? ILinkManager::kSynchronous : ILinkManager::kAsynchronous,
										  bNotify,
										  db,
										  resourceUID,
										  iResource->GetURI(),
										  iResource->GetState(),
										  iResource->GetStamp(),
										  iResource->GetModTime(),
										  iResource->GetSize());
	// first check to see if a job is already pending
	if (stateUpdateProcessor->IsJobPending(job)) {
		if (bSynchronous)
			// cancel the pending packet, so we can process it synchronously
			stateUpdateProcessor->RemoveJob(job);
		else
			// allow the pending packet to complete processing asynchronously
			return kSuccess;
	}
	
	stateUpdateProcessor->AddJob(job);
	
	if (bSynchronous) {
		if (stateUpdateProcessor) {
			stateUpdateProcessor->UpdateStateForJob(job);
		}
	}
	
	return kSuccess;
}
