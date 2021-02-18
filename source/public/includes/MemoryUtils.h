//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/MemoryUtils.h $
//  
//  Owner: pmessmer
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
//  
//  Memory utilities
//  
//========================================================================================

#pragma once
#ifndef __MEMORYUTILS__
#define __MEMORYUTILS__

#ifdef MACINTOSH
	#define MEM_FUNC_DECL __attribute__ ((visibility("default")))
#else
	#ifdef PMRUNTIME_BUILD
		#define MEM_FUNC_DECL __declspec(dllexport)
	#else
		#define MEM_FUNC_DECL __declspec(dllimport)
	#endif

#endif

namespace K2Memory
{

/**	Allocates a block of memory compatible with the runtime's operator new, except that
	the block is tracked for the purposes of finding leaks and the call may trigger
	a purge operation.  You normally never need to call this directly; it is called 
	by our operator new overload, which simply delegates to this function.
	@param size is the number of bytes to allocate
	@return the address of the new memory block.
*/
MEM_FUNC_DECL void *RTLCompatibleNewDelegate (size_t size);

/**	Allocates a block of memory compatible with the runtime's operator new[], except that
	the block is tracked for the purposes of finding leaks and the call may trigger
	a purge operation.  You normally never need to call this directly; it is called 
	by our operator new[] overload, which simply delegates to this function.
	@param size is the number of bytes to allocate
	@return the address of the new memory block.
*/
MEM_FUNC_DECL void *RTLCompatibleNewArrayDelegate (size_t size);

/** Deletes a block of memory allocated by operator new, or RTLCompatibleNewDelegate.
	You normally never need to call this directly, it is called by our operator delete
	overload, which simply delegates to this function.
	@param p is the block to delete.
*/
MEM_FUNC_DECL void RTLCompatibleDeleteDelegate (void *p);

/** Deletes a block of memory allocated by operator new[], or RTLCompatibleNewArrayDelegate.
	You normally never need to call this directly, it is called by our operator delete[]
	overload, which simply delegates to this function.
	@param p is the block to delete.
*/
MEM_FUNC_DECL void RTLCompatibleDeleteArrayDelegate (void *p);

/** Tells the memory tracking system to stop tracking an allocation that was performed
	by RTLCompatibleNewDelegate, RTLCompatibleNewArrayDelegate, or RTLCompatibleMalloc.
	This function is useful if the block in question must be passed to some outside code
	and will be deleted by the runtime library, trigger a spurrious memory leak assert.
	If you call this function to supress a leak, make SURE there really is no leak.
	@param p is the block to not report a leak about.
*/
MEM_FUNC_DECL void StopTrackingRTLCompatibleAllocation (void *p);

/** Interchangable and compatible with C's malloc(), except that the block is tracked for the purposes 
	of finding leaks and the call may trigger a purge operation.  You should call this
	in preference to malloc() so that we can find memory errors.
	@param size is the number of bytes to allocate
	@return the address of the new memory block.
*/
MEM_FUNC_DECL void *RTLCompatibleMalloc (size_t size);

	
/** Same as RTLCompatibleMalloc except that purging is disabled. This is used by STL compatible allocators in
	a few sensitive areas. Note that his may return NULL if the system allocator can't satisfy the request and the caller should be prepared to handle that.
	@param size is the number of bytes to allocate
	@return the address of the new memory block.
 */
MEM_FUNC_DECL void *RTLCompatibleMallocNoPurging (size_t size);
	
/** Interchangable and compatible with C's free(), except that the block is removed from
	tracking by our memory debugging system.  You should call this in preference to free()
	so that we can find memory errors.
	@param p is the block to delete.
*/
MEM_FUNC_DECL void RTLCompatibleFree (void *p);

/** Interchangable and compatible with C's realloc(), except that the block is tracked for the purposes 
	of finding leaks and the call may trigger a purge operation.  You should call this
	in preference to realloc() so that we can find memory errors.
	@param p is the block to reallocate, or 0 to allocate a new block.
	@param size is the number of bytes to reallocate the block to, or 0 to delete the block p.
	@return the address of the new memory block.
*/
MEM_FUNC_DECL void *RTLCompatibleRealloc (void *p, size_t size);

/** Compatible with C's mallocsize() (see also _msize on Windows).  It will give you
	information about the size of a block allocated through RTLCompatibleMalloc, RTLCompatibleRealloc,
	malloc, realloc, or calloc.  Note that the return value is NOT necessarily the exact allocation
	size you originally requested, but rather is an upper bound on the size of the block.
	@param p is the block to discover the size of.
	@return an upper bound on the size of the memory block p.
*/
MEM_FUNC_DECL size_t RTLCompatibleMallocSize (void *p);

    
#if defined(MACINTOSH) && defined(DEBUG)
    
// Used to completely bypass any overrides on malloc/free that may have been done. Used by BypassAllocator
MEM_FUNC_DECL void *RTLCompatibleBypassMalloc (size_t size);
MEM_FUNC_DECL void RTLCompatibleBypassFree (void *p);

#endif
};


#endif  // __MEMORYUTILS__
