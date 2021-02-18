//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IMemoryManager.h $
//  
//  Owner: ?
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

#include "PMTypes.h"
#include "IPMUnknown.h"

#pragma once
#ifndef __IMemoryManager__
#define __IMemoryManager__

	/** Old-style memory notification function. If you use the old-style, the purge handler
		will not be called on the Macintosh as a result of a grow zone failure. 
	*/
typedef void (*MemoryNotificationFunction)(int32 level, void *refPtr);

	/** New-style memory notification function. Memory notification functions are called
		when memory gets low. They are a way for the memory manager to tell objects that
		maintain caches to release the caches to free up memory. NewMemoryNotificationFunction 
		allows the function to find out if it's being called from within the grow zone 
		fail function. On the Macintosh, some operations cannot be done while the system 
		is handling a grow zone failure.
		@param level the priority of the purge request (see PurgeLevel data type).
		@param refPtr the pointer that was passed in when the handler was registered.
		@param bInGrowZone kTrue if the system is currently handling a grow zone failure.
	*/
typedef void (*NewMemoryNotificationFunction)(int32 level, void *refPtr, bool16 bInGrowZone);

	/** Memory state notification function. These are called when the MemoryState changes.
	*/
typedef void (*AdviseMemoryStateNotificationFunction)(int32 state, void *refPtr);

/** The memory manager keeps track of the memory load, and acts as a central handler
	for memory issues. 
*/
class IMemoryManager : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IMEMORYMANAGER };
		
		virtual void Init() = 0;
		
		/** Every purge request has a priority attached to it, which is the PurgeLevel.
		*/
		typedef enum 
		{
				/** Used to indicate no purge is necessary */ 
			kNoPurge = -1,
				/** Called when document focus changes, releases document oriented caches */
			kSwitchingDocuments = 0,		// release document oriented caches
				/** Called when the application is being switched out, releases temporary memory */ 
			kSwitchingApplications = 1,		// release temporary memory
				/** Called when memory is getting tight */
			kLowMemory1 = 2,
				/** Called when memory is getting more tight */
			kLowMemory2 = 3,
				/** Called when memory is getting even more tight */
			kLowMemory3 = 4,
				/** Called when a memory request is about to fail. Release all caches. */
			kReleaseEverything = 5,			// release all you can
				/** Attempt to free up memory by unloading plug-ins. Called only on the Mac, when a plug-in
					fails to load. Purge handlers will not get this level. */
			kMaxMemoryLevel = 5					
		} PurgeLevel;
		
		/** Load on memory */
		typedef enum 
		{
				/** Normal state, there is plenty of memory */
			kNormalMemoryState = 0,			// Normal state, there is plenty of memory
				/** Heap is relatively full, around 10-20% free (a good time to fix sizes of caches) */
			kConstrainedMemoryState = 1,		// Heap is relatively full, around 10-20% free (a good time to fix sizes of caches)
				/** Heap is very full, less than 5% free (a good time to reduce memory footprint) */
			kLowMemoryState = 2					// Heap is very full, less than 5% free (a good time to reduce memory footprint)
		} MemoryState;
		
			/** Tries to free some memory. Calls out to the purge handlers and requests them
				to free up memory. PurgeObjects is called by the new fail handler.
				@param purgeLevel, the priority level of the request
			*/
		virtual void PurgeObjects(PurgeLevel purgeLevel) = 0;
		
			/** Checks available memory and notifies registered memory state clients so thay can 
				make caching algorithm adjustments.
			*/
		virtual void CheckMemoryState() = 0;

			/** Tries to free the last memory reserves. The memory manager maintains a reserve 
				emergency block of memory that can be freed in order to satisfy memory requests
				when all other attempts have failed. These blocks will be reacquired as soon as
				the application judges the memory state has improved.
				@return kTrue if it released any emergency block and the caller should retry,
				kFalse if no emergency blocks were available
			*/
		virtual bool16 MemoryPanic() = 0;

			/** If CheckMemory() returns kFalse the application should quit asap.
			*/
		virtual bool16 CheckMemory(bool16 showAlerts = kFalse) = 0;	
	
			/** If MemoryIsLow returns kTrue certain methods and commands will not work.
			*/
		virtual bool16 MemoryIsLow() = 0;
			
			/** If MemoryIsFailing() returns kTrue the application should quit asap
			*/
		virtual bool16 MemoryIsFailing() = 0;
		

	/**@name  Register and de-register purge handlers  */
	//@{-----------------------------------------------------------------------------
			// NOTE that the two versions of these functions are named differently (as opposed to overloaded)
			// *Don't* overload them, or code which calls these functions then fails to compile
			// as the compiler cannot disambiguate the caller's first parameter which could either be
			// a pointer to a virtual function or a static function in the caller's class

			/** Register a purge handler. 
				@param func the memory notification function to register
				@param refPtr the pointer to pass the function when it's called
			*/
		virtual void RegisterMemoryNotification(MemoryNotificationFunction func, void *refPtr) = 0;
		
			/** Register a purge handler.
				@param func the memory notification function to register
				@param refPtr the pointer to pass the function when it's called
			*/
		virtual void RegisterNewMemoryNotification(NewMemoryNotificationFunction func, void *refPtr, bool16 bGrowZoneFailSafe) = 0;

			/** De-register a purge handler.
				@param func the memory notification function to register
				@param refPtr the pointer to pass the function when it's called
			*/
		virtual void UnregisterMemoryNotification(MemoryNotificationFunction func, void *refPtr) = 0;

			/** De-register a purge handler.
				@param func the memory notification function to register
				@param refPtr the pointer to pass the function when it's called
			*/
		virtual void UnregisterNewMemoryNotification(NewMemoryNotificationFunction func, void *refPtr) = 0;
	//@}-----------------------------------------------------------------------------
		
			/** Register a memory state notification function.
				@param func the memory state notification function to register
				@param refPtr the pointer to pass the function when it's called
			*/
		virtual void RegisterAdviseMemoryStateNotification(AdviseMemoryStateNotificationFunction func, void *refPtr) = 0;

			/** De-register a memory state notification function.
				@param func the memory state notification function to de-register
				@param refPtr the pointer to pass the function when it's called
			*/
		virtual void UnregisterAdviseMemoryStateNotification(AdviseMemoryStateNotificationFunction func, void *refPtr) = 0;

			/** Return the number of times PurgeObjects has been called
			*/
		virtual uint32	GetPurgeCount() const = 0;

			/** Returns the cumulative time spent in PurgeObjects
			*/
		virtual uint32	GetPurgeTime() const = 0;

		//////////// FOR INTERNAL USE ONLY! ////////////

		/** Returns true if a memory purge is in progress for the calling thread.
			Note that the function can return false, but other threads can be purging.
			Reserved for internal use only.
		*/
		virtual bool16 PurgeInProgress() const = 0;

		/** Called when an allocation fails.
			It will attempt to free some memory by calling the purge handlers.
			Returns true if it made any progress and the caller should retry the allocation, false if no progress was made and we should give up.
			@param blockSize [IN] - the size of the block that the allocator failed to allocate.
		*/
		virtual bool16 HandleAllocationFailure(size_t blockSize) = 0;

		/** Resets the failure handler into its initial state. Called after the failure handler was invoked (one or more times) in order to reset the purge level back to normal.
			Reserved for internal use only.
		*/
		virtual void ResetFailureHandler() = 0;
};


#endif // __IMemoryManager__
