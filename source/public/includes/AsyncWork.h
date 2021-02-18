//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/AsyncWork.h $
//  
//  Owner: Paul Messmer
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

#pragma once
#ifndef __ASYNCWORK__
#define __ASYNCWORK__

//--------------------------------------------------------------------------------------
/**
base class, descendents must use only thread-safe code if processor promises thread-safety, not a boss
*/
class AsyncWorkPacket	
{						
public:

	enum Priority
	{
		kLowestPriority = 0,
        
		kLowPriority = 0,
		kNormalPriority = 1,
        kHighPriority = 2,

        kHighestPriority = 2,

		kReservedForceCompletionPriority = 3,	// clients shouldn't use; this level is used by IAsyncWorkManager::WaitForCompletion
	};
	/**
	virtual destructor because the architecture deletes these.	
	A packet may be deleted before it's ever processed (if you call cancel),
	or may be deleted after processing but before the completion callback (if
	you call cancel too late), or may be deleted after the completion callback
	has occured (this is the normal case), so be sure that your destructor
	properly cleans up everything in any of these three cases.	
	*/
	virtual ~AsyncWorkPacket () {}	
};

//--------------------------------------------------------------------------------------

typedef uint64 AsyncWorkPacketID;
typedef void (*AsyncWorkCompletionCallback) (AsyncWorkPacket *completedPacket);

const AsyncWorkPacketID kInvalidAsyncWorkPacketID((uint64) -1);

//--------------------------------------------------------------------------------------

/**
base class, descendents must use only thread-safe code if factory promises thread-safety
not a boss, instances of this class are constructed and returned by the factory below
*/
class AsyncWorkProcessor
{						  
public:

	virtual ~AsyncWorkProcessor () {}	// virtual destructor because the architecture deletes these

	virtual void ProcessPacket (AsyncWorkPacket *packetToProcess) = 0;
};

//--------------------------------------------------------------------------------------

#endif // __ASYNCWORK__
