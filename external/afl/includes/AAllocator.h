//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/external/afl/includes/AAllocator.h $
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

#pragma once
#ifndef __AAllocator__
#define __AAllocator__

// ----- Includes -----
#include <stddef.h>
#include "AFLDecl.h"
#include "ATypes.h"

#ifdef MACINTOSH
#include <new>
#endif

namespace adobe {
namespace afl {

class AFL_DECL AAllocator
{
public:
	typedef void* (*AllocateProc)(size_t);
	typedef void (*FreeProc)(void*);

	/**
	 Registers the memory allocation and deallocation procedures
	 that AFL will call to allocate and free memory.
	 @param pAllocProc	IN Pointer to the procedure to call to allocate memory.
	 @param pFreeProc	IN Pointer to the procedure to call to free memory.
	 */
	static void RegisterMemoryProcs(AllocateProc pAllocProc, FreeProc pFreeProc);

	/**
	 Returns the registered memory allocation procedure that AFL calls to allocate memory.
	 @return Pointer to the registered memory allocation procedure.
			 NULL if no memory allocation procedure has been registered.
	 */
	static AllocateProc GetAllocateProc();

	/**
	 Returns the registered memory deallocation procedure that AFL calls to free memory.
	 @return Pointer to the registered memory deallocation procedure.
			 NULL if no memory deallocation procedure has been registered.
	 */
	static FreeProc GetFreeProc();

	/**
	 Allocates the requested size of memory using the registered allocation procedure,
	 or operator new if no allocation procedure has been registered.
	 @param size	IN Number of bytes to allocate.
	 @return Pointer to the allocated memory.
	 */
	static void* Alloc(size_t size);

	/**
	 Frees the memory pointed to by the given pointer using the registered deallocation
	 procedure, or operator delete if no allocation procedure has been registered.
	 @param p	IN Pointer to the memory to free.
	 */
	static void Free(void* p);
};


//========================================================================================
// The point of this allocator is to have all AFL STL objects use the Alloc() and
// Free() methods above.  This ensures that the STL objects use the memory procedures
// registered by the app linking to AFL.
//========================================================================================
template <class T>
class AFLAllocator
{
public:
	// type definitions
	typedef T        value_type;
	typedef T*       pointer;
	typedef const T* const_pointer;
	typedef T&       reference;
	typedef const T& const_reference;
	typedef size_t    size_type;
	typedef ptrdiff_t difference_type;

	// rebind allocator to type U
	template <class U>
	struct rebind {
		typedef AFLAllocator<U> other;
	};

	// return address of values
	pointer address(reference value) const {
		return &value;
	}
	const_pointer address(const_reference value) const {
		return &value;
	}

	// constructors and destructor
	// - nothing to do because the allocator has no state
	AFLAllocator() noexcept {
	}
	AFLAllocator(const AFLAllocator& src) noexcept {
	}
	template <class U>
	AFLAllocator(const AFLAllocator<U> &src) noexcept {
	}
	~AFLAllocator() noexcept {
	}

	// return maximum number of elements that can be allocated
	size_type max_size() const noexcept {
		return (size_type) (int64) -1 / sizeof(T);
	}

	// allocate but don't initialize num elements of type T
	pointer allocate(size_type num, const void* = 0) {
		pointer ret = (pointer) AAllocator::Alloc(num * sizeof(T));
		if (!ret) throw std::bad_alloc();
		return ret;
	}

	// initialize elements of allocated storage p with value value
	void construct(pointer p, const T& value) {
		// initialize memory with placement new
		new((void*)p)T(value);
	}

	// destroy elements of initialized storage p
	void destroy(pointer p) {
		// destroy objects by calling their destructor
		p->~T();
	}

	// deallocate storage p of deleted elements
	void deallocate(pointer p, size_type num) {
		AAllocator::Free(p);
	}
};

// return that all specializations of this allocator are interchangeable
template <class T1, class T2>
bool operator==(const AFLAllocator<T1>&, const AFLAllocator<T2>&) noexcept {
	return true;
}
template <class T1, class T2>
bool operator!=(const AFLAllocator<T1>&, const AFLAllocator<T2>&) noexcept {
	return false;
}

}	// namespace afl
}	// namespace adobe

#endif	// __AAllocator__
