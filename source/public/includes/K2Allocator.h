//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/K2Allocator.h $
//  
//  Owner: Mat Marcus
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
#ifndef __K2Allocator__
#define __K2Allocator__

#include "K2STLUtilities.h"
#include "K2Assert.h"


/** Allocators represent a special memory model and are an abstraction used to translate
	the need to use memory into a raw call for memory.
	K2Allocator is the default allocator used by the new K2 collections (like K2Vector).
	This class would be deprecated soon along with the other K2 containers.
*/
template <class T>
class K2Allocator {
public:
	typedef uint32	    	size_type;
	typedef std::ptrdiff_t 	difference_type;
	typedef T*        		pointer;
	typedef const T*  		const_pointer;
	typedef T&        		reference;
	typedef const T&  		const_reference;
	typedef T         		value_type;

	template <class U> struct rebind { typedef K2Allocator<U> other; };

	/** Default constructor.
		Creates an empty allocator.
	*/
				K2Allocator()							{}

	template <class U>
	K2Allocator(const K2Allocator<U>&)
	{
	}

	/** Returns address of values.
		@param x [IN] - a value.
		@return the address of the specified value.
	*/
	pointer 	address(reference x) const				{return &x;}
	const_pointer address(const_reference x) const		{return &x;}

	/** Allocates but doesn't initialize n elements of type T.
		@param n [IN] - number of element of type T to allocate space for.
		@param hint [IN] - not used.
	*/
	pointer 	allocate(size_type n, const void* hint = nil);

	/** Frees the storage to which p refers.
		The storage p has to be allocated by allocate() of the same or an equal allocator.
		The elements should have been destroyed already.
		@param p [IN] - pointer to the storage to be freed.
	*/
	void 		deallocate(pointer p, size_type)		{operator delete(p);}

	/** Returns the maximum number of elements that can be allocated.
		@return the maximum number of elements that can be allocated.
	*/
	size_type 	max_size() const {return kMaxUInt32 / sizeof(T);}

	/** Initializes the storage of one element to which p refers with value.
		@param p [IN] - pointer to the storage.
		@param val [IN] - value for initialization.
	*/
	void 		construct(pointer p, const T& val)		{new(p) T(val);}

	/** Destroys the object to which p refers without deallocating the storage.
		Simply calls the destructor for the object.
		@param p [IN] - pointer to the object.
	*/
	void 		destroy(pointer p)						{p->~T();}
};


// ===================================================================================
//	K2Allocator<void>
//		specialization for void
// ===================================================================================
template <>
class K2Allocator<void> {
public:
	typedef std::size_t     size_type;
	typedef std::ptrdiff_t  difference_type;
	typedef void*       	pointer;
	typedef const void* 	const_pointer;
	typedef void        	value_type;
};


// ===================================================================================
//	Inlines
// ===================================================================================
template <class T>
inline typename K2Allocator<T>::pointer
K2Allocator<T>::allocate(size_type n, const void*)
{
	pointer p = static_cast<pointer>(operator new(n * sizeof(T)));
	ASSERT_MSG(p != nil, "Memory allocation failure");
	return p;
}

template <class T, class U>
inline bool16
operator==(const K2Allocator<T>&, const K2Allocator<U>&)
{
	return true;
}

template <class T, class U>
inline bool16
operator!=(const K2Allocator<T>&, const K2Allocator<U>&)
{
	return false;
}


#endif
