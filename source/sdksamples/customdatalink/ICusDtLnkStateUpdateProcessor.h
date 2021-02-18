//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalink/ICusDtLnkStateUpdateProcessor.h $
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

#ifndef __ICusDtLnkStateUpdateProcessor_h__
#define __ICusDtLnkStateUpdateProcessor_h__

// Interface includes:
#include "IPMUnknown.h"
#include "URI.h"
#include "URIList.h"

class CusDtLnkLinkResourceStatePacket;
// Project includes:
#include "CusDtLnkID.h"

/** Abstract interface for CusDtLnk to maintain a queue for link status update job packets.
 
 @ingroup customdatalink
 @see CusDtLnkLinkResourceStateUpdater
 @see CusDtLnkLinkResourceStateUpdaterIdleTask
 */
class ICusDtLnkStateUpdateProcessor : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_ICUSDTLNKSTATEUPDATEPROCESSOR };
		
		
		/** Add a job to the processor
		 
		 @param job	 [IN] to be added to the queue.
		 @return kTrue if job is added successfully.
		 */
		virtual bool16 AddJob(const CusDtLnkLinkResourceStatePacket& job) = 0;
		
		/** Remove the job from the processor
		 
		 @param job	 [IN] to be removed from the queue.
		 @return kTrue if job is removed successfully.
		 */
		virtual bool16 RemoveJob(const CusDtLnkLinkResourceStatePacket& job) = 0;
		
		/** Check if a job is already queued
		 
		 @param job	 [IN] to be checked.
		 @return kTrue if job is removed successfully.
		 */
		virtual bool16 IsJobPending(const CusDtLnkLinkResourceStatePacket& job) const = 0;
		
		/** The state updater mainains a job queue. A job is to provide state update for a particular linkr resource.
		 This routine process the state update function given a particular job packet, and remove it from the queue
		 
		 @return kTrue if job is removed successfully.
		 */
		virtual bool16 UpdateStateForJob(const CusDtLnkLinkResourceStatePacket& job) = 0;
		
		/** Give a status update to the top job from the processor, and when job is updated and the 
		 link manager is informed, remove the job from job queue
		 
		 @return kTrue if job is removed successfully.
		 */
		virtual bool16 UpdateStateForTopJob() = 0;
	};

#endif

