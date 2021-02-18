//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalink/CusDtLnkLinkResourceStateUpdaterIdleTask.cpp $
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
//  ADOBE CONFIDENTIAL
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
#include "CIdleTask.h"

// ----- Interfaces -----
#include "IDataBase.h"
#include "IIdleTaskMgr.h"
#include "ILinkManager.h"
#include "ICusDtLnkStateUpdateProcessor.h"
// ----- ID.h files -----
#include "CusDtLnkID.h"

//========================================================================================
// Class CusDtLnkLinkResourceStateUpdaterIdleTask
//========================================================================================
/**
 This idle task is to process the pending job for providing status update for a link resource.  
 The jobs are maintained by the ICusDtLnkStateUpdateProcessor, this idle task simply calls 
 ICusDtLnkStateUpdateProcessor::UpdateStateForTopJob to process the job on the queue.
 
 @ingroup customdatalink
 @see CusDtLnkLinkResourceStateUpdater
 @see ICusDtLnkStateUpdateProcessor
 @see CusDtLnkStateUpdateProcessor
 */
class CusDtLnkLinkResourceStateUpdaterIdleTask : public CIdleTask
	{
	public:
		CusDtLnkLinkResourceStateUpdaterIdleTask(IPMUnknown* boss);
		
		virtual uint32 RunTask(uint32 flags, IdleTimer* timeCheck);
		virtual const char* TaskName();
	};

CREATE_PMINTERFACE(CusDtLnkLinkResourceStateUpdaterIdleTask, kCusDtLnkLinkResourceStateUpdaterIdleTaskImpl)


//========================================================================================
//
// CusDtLnkLinkResourceStateUpdaterIdleTask Public Implementation
//
//========================================================================================

//========================================================================================
// Constructor
//========================================================================================
CusDtLnkLinkResourceStateUpdaterIdleTask::CusDtLnkLinkResourceStateUpdaterIdleTask(IPMUnknown* boss) 
: CIdleTask(boss)
{
}

//========================================================================================
// CusDtLnkLinkResourceStateUpdaterIdleTask::RunTask
//========================================================================================
uint32 CusDtLnkLinkResourceStateUpdaterIdleTask::RunTask(uint32 flags, IdleTimer* idleTimer)
{
	if (flags & (IIdleTaskMgr::kInBackground | IIdleTaskMgr::kMenuUp | IIdleTaskMgr::kMouseTracking)) return kOnFlagChange;
	
	InterfacePtr<ICusDtLnkStateUpdateProcessor> stateUpdateProcessor(this, UseDefaultIID());
	if (stateUpdateProcessor) {
		bool outOfTime(false);
		do {
			stateUpdateProcessor->UpdateStateForTopJob();
			if (idleTimer && (*idleTimer)() == 0)
				outOfTime = true;
		} while (!outOfTime);
	}
	return 300;
}

//========================================================================================
// CusDtLnkLinkResourceStateUpdaterIdleTask::TaskName
//========================================================================================
const char* CusDtLnkLinkResourceStateUpdaterIdleTask::TaskName()
{
	return "CusDtLnkLinkResourceStateUpdaterIdleTask";
}


