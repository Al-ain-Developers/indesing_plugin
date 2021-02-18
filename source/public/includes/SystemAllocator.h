//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/SystemAllocator.h $
//  
//  Owner: Jesse Jones (jejones)
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
#ifndef __SystemAllocator__
#define __SystemAllocator__

#include "K2STLUtilities.h"
#include "K2Assert.h"

/** Summary: An STL compliant allocator that uses OS calls to allocate memory.
*/
template <class T>
class SystemAllocator {
public:
	typedef size_t    size_type;
	typedef std::ptrdiff_t difference_type;
	typedef T*        pointer;
	typedef const T*  const_pointer;
	typedef T&        reference;
	typedef const T&  const_reference;
	typedef T         value_type;

	/** */
	pointer 	address(reference x) const						{return &x;}
	/** */
	const_pointer address(const_reference x) const				{return &x;}

	/** */
	pointer 	allocate(size_type n, const void* hint = nil);
	/** */
	void 		deallocate(pointer p, size_type /*n*/);
	/** */
	size_type 	max_size() const								{return ULONG_MAX / sizeof(T);}

	/** */
	void 		construct(pointer p, const T& value)			{new(p) T(value);}
	/** */
	void 		destroy(pointer p)								{p->~T();}
	
	/** */
	bool16 		operator==(const SystemAllocator<T>&) const		{return true;}
	/** */
	bool16 		operator!=(const SystemAllocator<T>&) const		{return false;}
};


template <class T>
inline typename SystemAllocator<T>::pointer
SystemAllocator<T>::allocate(size_type n, const void* /*hint*/)
{
	size_t bytes = n*sizeof(T);
	
#if defined(MACINTOSH)
	// This bypasses our leak detection code! DJB 4/11/2005.
	void* ptr = malloc(bytes);	
	// But if I replace it, we crash for an unknown reason at static destructor time.
	//void* ptr = new char[bytes];
	
#elif defined(WINDOWS)
	void* ptr = VirtualAlloc(nil, bytes, MEM_COMMIT, PAGE_READWRITE);
#endif

	return static_cast<pointer>(ptr);
}

template <class T>
inline void SystemAllocator<T>::deallocate(pointer ptr, size_type /*n*/)
{
	if (ptr != nil) {
#if defined(MACINTOSH)
	free(ptr);
	// delete [] ptr;

#elif defined(WINDOWS)
		BOOL success = VirtualFree(ptr, 0, MEM_RELEASE);
		ASSERT(success);
#endif
	}
}


#endif	// __SystemAllocator__
