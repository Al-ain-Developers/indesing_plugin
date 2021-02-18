//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/MResourceShell.h $
//  
//  Owner: Michael Burbidge, Robin Briggs
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
#ifndef __MResourceShell_h__
#define __MResourceShell_h__

#include "RsrcSpec.h"
#include "PMLocaleId.h"
#include "CResourceShell.h"

#ifdef PUBLIC_BUILD
#pragma export on
#endif

/** Macintosh implementation for some resource reading methods. @see CResourceShell for more
*/
class MResourceShell : public CResourceShell
{
public:

#ifdef ID_DEPRECATED	
	/** Obsolete. No longer does anything on either platform. Previously, locks a resource handle, so it won't move even if memory is purged.
		@param rsrcHandle which handle to lock
	*/
	static void			LockResourceHandle( SysHandle rsrcHandle);

	/** Obsolete. No longer does anything on either platform. Previously, unlocks a previously locked resource handle.  
		@param rsrcHandle which handle to unlock
	*/
	static void			UnlockResourceHandle( SysHandle rsrcHandle);
#endif

	/** Releases resource handle. Usually called to free up memory after a call to GetResource.
		@param rsrcHandle which handle to free
	*/
	static void			ReleaseResource(const SysHandle rsrcHandle);

	/** Retains a resource handle. Breaks the connection to the resource. Equivilent to mac toolbox DetachResource call.
		@param rsrcHandle which handle to detach
	*/
	static void			DetachResource(const SysHandle rsrcHandle); 

	/** Get the size of a resource
		@param rsrcHandle handle to the resource you want to know the size of.
		@return size of the resource
	*/
	static int32		GetSizeofResource(const SysHandle rsrcHandle);

	/** Get a handle to a resource.
		@param type which resource type
		@param id which resource id
		@return handle to the requested resource
	*/
	 static SysHandle GetResourceByID(RsrcType type, RsrcID id);
	 
	/** Get a handle to a resource by index
		@param type which resource type
		@param index which resource index
		@return handle to the requested resource
	*/
	 static SysHandle GetResourceByIndex(RsrcType type, RsrcID index /*1-based*/);
	 
	/** Get a count of resources of a certain type.
		@param type which resource type
		@return the count of resources of the desired type
	*/
	 static int16 CountResources(RsrcType type);
private:

	MResourceShell(){} // don't make one please
};

//========================================================================================
// INLINES MResourceShell
//========================================================================================
#define MTOOLBOX
#ifdef DEBUG
	extern 	int64 ts_TotalNumResourceAccesses;
#endif

/** @see LockResourceHandle
*/
inline void MResourceShell::LockResourceHandle(SysHandle /*rsrcHandle*/)
{
	// This assert no longer means anything because HLOCK is a no-op
	// ASSERT_MSG(!(::HGetState(rsrcHandle) & kHandleLockedMask),"Trying to lock already locked handle - could be bad");
	//HLOCK(rsrcHandle);
}

/** @see UnlockResourceHandle
*/
inline void MResourceShell::UnlockResourceHandle(SysHandle /*rsrcHandle*/)
{
	// This assert no longer means anything because HUNLOCK is a no-op
	//ASSERT_MSG((::HGetState(rsrcHandle) & kHandleLockedMask),"Trying to unlock handle which is not locked!");
	//HUNLOCK(rsrcHandle);
}

/** @see ReleaseResource
*/
inline void MResourceShell::ReleaseResource(const SysHandle rsrcHandle)
{
	MTOOLBOX::ReleaseResource(rsrcHandle);
}

/** @see DetachResource
*/
inline void MResourceShell::DetachResource(const SysHandle rsrcHandle)
{
	MTOOLBOX::DetachResource(rsrcHandle);
}

/** @see GetSizeofResource
*/
inline int32 MResourceShell::GetSizeofResource(const SysHandle rsrcHandle)
{
	return MTOOLBOX::GetHandleSize(rsrcHandle);
}

/** @see CountResources
*/
inline int16 MResourceShell::CountResources(RsrcType rsrcType)
{
#ifdef DEBUG
	ts_TotalNumResourceAccesses++;
//	ASSERT_MSG(IDThreading::IsMainThreadDomain(),"Making non-threadsafe call to mac resource manager from non-main thread");
#endif
	

	return MTOOLBOX::Count1Resources(rsrcType);
}

/** @see GetResourceByID
*/
inline SysHandle MResourceShell::GetResourceByID(RsrcType type, RsrcID id)
{
#ifdef DEBUG
	ts_TotalNumResourceAccesses++;
//	ASSERT_MSG(IDThreading::IsMainThreadDomain(),"Making non-threadsafe call to mac resource manager from non-main thread");
#endif
	return MTOOLBOX::Get1Resource(type, id);
}

/** @see GetResourceByIndex
*/
inline SysHandle MResourceShell::GetResourceByIndex(RsrcType type, RsrcID index)
{
#ifdef DEBUG
	ts_TotalNumResourceAccesses++;
//	ASSERT_MSG(IDThreading::IsMainThreadDomain(),"Making non-threadsafe call to mac resource manager from non-main thread");
#endif
	return MTOOLBOX::Get1IndResource(type, index);
}

#pragma export off

#endif // __MResourceShell_h__
