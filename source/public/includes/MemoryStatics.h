//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/MemoryStatics.h $
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

#ifndef __MemoryStatics__
#define __MemoryStatics__

// This definition is checked for elsewhere as a sanity check to make sure we aren't
// missing this header (and thus missing our new/delete) in InDesign / plug-in code.

#define INCLUDED_MEMORY_STATICS 1	

#ifndef INTERNAL_TEST_WITH_PLATFORM_ALLOCATOR

#ifdef WINDOWS

// On Windows, these are exported from PMRuntime.
// NOT CURRENTLY TRUE:  On the Mac, these are in MemoryStatics.cpp which is present in (but not exported from) each linkage unit

void* operator new(size_t size);

void* operator new[](size_t size);

void operator delete(void*p) noexcept;

void operator delete[](void*p) noexcept;

void* operator new(size_t size, const std::nothrow_t&) noexcept;

void* operator new[](size_t size, const std::nothrow_t&) noexcept;

void operator delete(void*p, const std::nothrow_t&) noexcept;

void operator delete[](void*p, const std::nothrow_t&) noexcept;

void * operator new(size_t size, short temporary);	// [][] get rid of these, temporary memory does nothing special anymore

void * operator new[](size_t size, short temporary);	// [][] get rid of these, temporary memory does nothing special anymore

#endif

#ifdef MACINTOSH

#include <new>

namespace K2Memory	// in PMRuntime
{
	__attribute__ ((visibility("default"))) void *RTLCompatibleNewDelegate (size_t size);

	__attribute__ ((visibility("default"))) void *RTLCompatibleNewArrayDelegate (size_t size);

	__attribute__ ((visibility("default"))) void RTLCompatibleDeleteDelegate (void *p);

	__attribute__ ((visibility("default"))) void RTLCompatibleDeleteArrayDelegate (void *p);
};

// These new and delete operators must be forced inline, because if code is actually
// generated for them, new and delete are always default visibility and they will
// be exported from where they are generated, which causes link problems with libraries, etc...

// both "inline" and "__attribute__ ((__always_inline__))" are reqyured
#define FORCE_INLINE inline __attribute__ ((__always_inline__))

FORCE_INLINE void* operator new(std::size_t size)
{
	// Doesn't actually throw
	return K2Memory::RTLCompatibleNewDelegate (size);
}

FORCE_INLINE void* operator new[](std::size_t size)
{
	// Doesn't actually throw
	return K2Memory::RTLCompatibleNewArrayDelegate (size);
}

FORCE_INLINE void operator delete(void*p) noexcept
{
	K2Memory::RTLCompatibleDeleteDelegate (p);
}

FORCE_INLINE void operator delete[](void*p) noexcept
{
	K2Memory::RTLCompatibleDeleteArrayDelegate (p);
}

FORCE_INLINE void operator delete(void*p, std::size_t) noexcept
{
    K2Memory::RTLCompatibleDeleteDelegate(p);
}

FORCE_INLINE void operator delete[](void*p, std::size_t) noexcept
{
    K2Memory::RTLCompatibleDeleteArrayDelegate(p);
}


FORCE_INLINE void* operator new(std::size_t size, const std::nothrow_t&) noexcept
{
	return K2Memory::RTLCompatibleNewDelegate (size);
}

FORCE_INLINE void* operator new[](std::size_t size, const std::nothrow_t&) noexcept
{
	return K2Memory::RTLCompatibleNewArrayDelegate (size);
}

FORCE_INLINE void operator delete(void*p, const std::nothrow_t&) noexcept
{
	K2Memory::RTLCompatibleDeleteDelegate (p);
}

FORCE_INLINE void operator delete[](void*p, const std::nothrow_t&) noexcept
{
	K2Memory::RTLCompatibleDeleteArrayDelegate (p);
}

FORCE_INLINE void * operator new(std::size_t size, short temporary)
{
	#pragma unused(temporary)
	// [][] get rid of these, temporary memory does nothing special anymore
	return K2Memory::RTLCompatibleNewDelegate (size);
}

FORCE_INLINE void * operator new[](std::size_t size, short temporary)
{
	#pragma unused(temporary)
	// [][] get rid of these, temporary memory does nothing special anymore
	return K2Memory::RTLCompatibleNewArrayDelegate (size);
}

#endif // MACINTOSH

#endif // !INTERNAL_TEST_WITH_PLATFORM_ALLOCATOR

#endif // __MemoryStatics__


