//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/WResourceShell.h $
//  
//  Owner: Michael Burbidge, Mouhammad Fakhoury, lance bushore
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
#ifndef __WResourceShell_h__
#define __WResourceShell_h__

#include "RsrcSpec.h"
#include "PMLocaleId.h"
#include "CResourceShell.h"

/** Windows implementation for some resource reading methods. 
	@see CResourceShell
*/
class PUBLIC_DECL WResourceShell : public CResourceShell
{
public:
#ifdef ID_DEPRECATED	
	/** Obsolete. No longer does anything on either platform. Previously, it locked a resource handle, so it won't move even if memory is purged. 
	*/
	static void			LockResourceHandle( SysHandle rsrcHandle);

	/** Obsolete. No longer does anything on either platform. Previously, it unlocked a previously-locked resource handle. 
	*/
	static void			UnlockResourceHandle( SysHandle rsrcHandle);
#endif

	/** Releases resource handle. Usually called to free up memory after a call to GetResource.
		@param rsrcHandle which handle to free
	*/
	static void			ReleaseResource(const SysHandle rsrcHandle);
	
	/** does nothing on windows. Provided so it's simpler to write cross platform code with #ifdefs
		@param rsrcHandle ignored
	*/
	static void			DetachResource(const SysHandle rsrcHandle){};

	/** Get the size of a resource
		@param rsrcHandle handle to the resource you want to know the size of.
		@return size of the resource
	*/
	static int32		GetSizeofResource(const SysHandle rsrcHandle);

	/** Windows only. Get a handle to a resource.
		@param rsrcType which resource type as a string
		@param id which resource id, as a string
		@return handle to the requested resource
	*/
	static SysHandle GetWinResource(LPTSTR  rsrcType, LPTSTR  id); 


	/** Windows only. Get a handle to a resource.
		@param hModule - the module from which to load the resource from.
		@param rsrcType which resource type as a string
		@param id which resource id, as a string
		@return handle to the requested resource
	*/
	static SysHandle GetWinResource(HMODULE hModule, LPTSTR  rsrcType, LPTSTR  id); 

	/** Get a handle to a resource by ID.
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

	WResourceShell(){} // don't make one please
};

/** See GetResourceByID()
*/
inline SysHandle WResourceShell::GetResourceByID(RsrcType type, RsrcID rsrcID)
{
	return WResourceShell::GetWinResource(MAKEINTRESOURCE(type),MAKEINTRESOURCE(rsrcID));
}

/** Obsolete
*/
inline void WResourceShell::LockResourceHandle(SysHandle rsrcHandle)
{
}

/** Obsolete
*/
inline void WResourceShell::UnlockResourceHandle(SysHandle rsrcHandle)
{
}

#endif // __WResourceShell__
