//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/K2Vector.tpp $
//  
//  Owner: Mat Marcus and Jesse Jones
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//	ADOBE CONFIDENTIAL. Portions Copyright 2013 Adobe Systems Incorporated.  All rights reserved.
//
//	NOTICE: All information contained herein is, and remain the property of Adobe Systems Incorporated
//	and its suppliers, if any. The intellectual and technical concepts contained herein are proprietary
//	to Adobe Systems Incorporated and its suppliers and are protected by all applicable intellectual property
//	laws, including trade secret and copyright laws. Dissemination of this information or reproduction of
//	this material is strictly forbidden unless prior written permission is obtained from Adobe Systems Incorporated.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//
//  Copyright (c) 1994
//  Hewlett-Packard Company
//  
//  Copyright (c) 1996,1997
//  Silicon Graphics Computer Systems, Inc.
//  
//  Copyright (c) 1997
//  Moscow Center for SPARC Technology
//  
//  Copyright (c) 1999 
//  Boris Fomitchev
//  
//  This material is provided "as is", with absolutely no warranty expressed
//  or implied. Any use is at your own risk.
//  
//  Permission to use or copy this software for any purpose is hereby granted 
//  without fee, provided the above notices are retained on all copies.
//  Permission to modify the code and to distribute modified code is granted,
//  provided the above notices are retained, and a notice that the code was
//  modified is included with the above copyright notice.
//  
//========================================================================================

#ifndef __K2VectorTPP__
#define __K2VectorTPP__

#ifndef __K2Vector__
#include "K2Vector.h"
#endif

namespace K2Internals {


//---------------------------------------------------------------
//
// K2VectorBase::CopyConstructHelper
//
//---------------------------------------------------------------
template <class T, class Allocator>
void K2VectorBase<T, Allocator>::CopyConstructHelper(const K2VectorBase<T, Allocator>& rhs)
{	
	fLength = rhs.fLength;
	
	if (fLength != 0)
	{
		typename K2Allocator<T>::size_type newCap = rhs.capacity ();

		if (newCap <= kPrivateBufferBytes / sizeof (value_type))
		{
			fArray = (pointer)fPrivateBuffer;
		}
		else
		{
			fArray = fAllocator.allocate(newCap);
		}
			
		K2uninitialized_copy(rhs.fArray, rhs.fArray + rhs.fLength, fArray);
	}		
	else
	{
		fArray = InitialArrayValue ();
	}
}


#if 0
//---------------------------------------------------------------
//
// K2VectorBase::operator=
//
//---------------------------------------------------------------
template <class T, class Allocator>
K2VectorBase<T, Allocator>&
K2VectorBase<T, Allocator>::operator=(const K2VectorBase& rhs)
{
	if (this != &rhs)
		assign(rhs.begin(), rhs.end());
		
	return *this;
}
#endif

//---------------------------------------------------------------
//
// K2VectorBase::fill_assign
//
//---------------------------------------------------------------
template <class T, class Allocator>
void K2VectorBase<T, Allocator>::fill_assign(size_type n, const T& value)
{

	if (n > capacity()) {
		K2VectorBase<T, Allocator> tmp(n, value);
		tmp.swap(*this);
	}
	else {
		if (n > size()) {
			K2fill(begin(), end(), value);
			K2uninitialized_fill_n(end(), n - size(), value);
		}
		else
			erase(K2fill_n(begin(), n, value), end());
		fLength = n;
	}
}


//---------------------------------------------------------------
//
// K2VectorBase::fill_insert
//
//---------------------------------------------------------------
template <class T, class Allocator>
void K2VectorBase<T, Allocator>::fill_insert(iterator position, size_type n, const T& value)
{
	ASSERT_MSG(position >= this->begin(),FORMAT_ARGS("Cannot insert before start of vector(position index %d)",position - this->begin()));
	ASSERT_MSG(position <= this->end(),FORMAT_ARGS("Cannot insert past end of vector(position %d, end index %d)",position - this->begin(),this->end() - this->begin()));
	ASSERT(n <= max_size());
	ASSERT(fLength <= max_size() - n);

	if (n > 0)
	{	
		if (fLength + n <= capacity())
		{
 			pointer oldFinish = fArray + fLength; // same as end()
			size_type elementsAfter = static_cast<size_type>(oldFinish - position);
			if (n != 0)
			{
				if (n <= elementsAfter)
				{			
					// Copy the elements at the end of the array into the uninitialized part 
					// of the vector
					K2uninitialized_copy(oldFinish - n, oldFinish, oldFinish);
					
					// Move any remaining elements over to make room for the new elements
					if (n < elementsAfter)
						K2copy_backward(position, oldFinish - n, oldFinish);
					
					// Assign the new value to the old elements
					K2fill(position, position + n, value);
				}
				else
				{					
					// Copy the elements at the end of the array into the uninitialized part 
					// of the vector
					K2uninitialized_copy(position, oldFinish, oldFinish +  n - elementsAfter);
										
					// Assign the new value to the old elements
					K2fill(position, oldFinish, value);
					
					// Create any new values extending past the end of the array
					K2uninitialized_fill_n(oldFinish, n - elementsAfter, value); 
				}				
				// In both cases we finally update length
				fLength += n;
			}
		}
		else
		{
			// Get the new numbers
			size_type newLen = fLength + n;
			size_type newCap = this->DoGetCapacity(newLen);
			pointer newData = fAllocator.allocate(newCap);

			// Copy over the old data up to our insertion point
			pointer newFinish = K2uninitialized_copy(fArray, position, newData);

			// Stick the new data in
			newFinish = K2uninitialized_fill_n(newFinish, n, value); 
			
			// And copy any old data after the insertion point
			K2uninitialized_copy(position, fArray + fLength, newFinish);
			
			this->DoReset(newData, newLen, newCap);
		}
	}
}


//---------------------------------------------------------------
//
// K2VectorBase::resize
//
//---------------------------------------------------------------
template <class T, class Allocator>
void K2VectorBase<T, Allocator>::resize(size_type newsize, const T& value)
{
	if (newsize > size())
		insert(end(), newsize-size(), value);
	else if (newsize < size())
		erase(begin() + newsize, end());
}


//---------------------------------------------------------------
//
// K2VectorBase::reserve
//
//---------------------------------------------------------------
template <class T, class Allocator>
void K2VectorBase<T, Allocator>::reserve(size_type newCap)
{
	ASSERT_MSG (newCap <= max_size(), "K2VectorBase::reserve length error");
	
	if (newCap > capacity())
	{
		pointer newData = fAllocator.allocate(newCap);

		K2uninitialized_copy(fArray, fArray + fLength, newData);
		
		this->DoReset(newData, fLength, newCap);
	}
}

//---------------------------------------------------------------
//
// K2VectorBase::push_back
//
//---------------------------------------------------------------
template <class T, class Allocator>
void K2VectorBase<T, Allocator>::push_back(const T& value)
{
	ASSERT_MSG (fLength <= max_size() - 1, "Fatal: K2VectorBase::push_back length error");
	
	if (fLength < capacity())
	{
		new (fArray + fLength) T(value);
		++fLength;
	}
	else
	{
		size_type newCap = this->DoGetCapacity(fLength+1);
		pointer newData = fAllocator.allocate(newCap);
		
		K2uninitialized_copy(fArray, fArray + fLength, newData);
		new (newData + fLength) T(value);
		
		this->DoReset(newData, fLength+1, newCap);
	}
}


//---------------------------------------------------------------
//
// K2VectorBase::pop_back
//
//---------------------------------------------------------------
template <class T, class Allocator>
void K2VectorBase<T, Allocator>::pop_back()
{	
	ASSERT(fLength > 0);
	
	fAllocator.destroy(&*(end() - 1));
	--fLength;
}


//---------------------------------------------------------------
//
// K2VectorBase::erase (iterator)
//
//---------------------------------------------------------------
template <class T, class Allocator>
typename K2VectorBase<T, Allocator>::iterator
K2VectorBase<T, Allocator>::erase(iterator position)
{
	ASSERT(position >= this->begin());
	ASSERT(position < this->end());

	size_type n = size_type(end() - position - 1);
	if (n > 0)
		K2copy(position + 1, end(), position);
	--fLength;
	K2destroy(end());
	return position;
}


//---------------------------------------------------------------
//
// K2VectorBase::erase (iterator, iterator)
//
//---------------------------------------------------------------
template <class T, class Allocator>
typename K2VectorBase<T, Allocator>::iterator
K2VectorBase<T, Allocator>::erase(iterator first, iterator last)
{
	ASSERT(first <= last);
	ASSERT(first >= this->begin());
	ASSERT(last <= this->end());
	
	if (first == last)
		return first;
		
	size_type n = size_type(end() - last);
	if (n > 0)
		K2copy(last, end(), first);
	K2destroy(first + n, end());
	fLength -= size_type(last - first);
	
	return first;
}


//---------------------------------------------------------------
//
// K2VectorBase::swap
//
//---------------------------------------------------------------
template <class T, class Allocator>
void K2VectorBase<T, Allocator>::swap(K2VectorBase& rhs) noexcept
{
	// [][] Note that now with the private buffer optimization, that swap
	// differs from std::vector swap in that it may have to copy elements,
	// and thus it may throw.  This is probably moot since we're not really
	// exception safe including this class itself in other ways.
	
	// Also, note that this could be improved if swap is a common operation,
	// since after swap private buffers aren't used.  This could be better,
	// but it would be more complex and I don't really know how common
	// swap is and thus how worthwhile that would be.

	if (this != &rhs)
	{
		if (fLength != 0 || rhs.fLength != 0)
		{
			if (fLength == 0 && fArray == (pointer)fPrivateBuffer)
			{
				if (rhs.fArray == (pointer)rhs.fPrivateBuffer)
				{
					rhs.reserve (rhs.capacity () + 1);
				}
				ASSERT (rhs.fArray != (pointer)rhs.fPrivateBuffer);
				
				fArray = rhs.fArray;
				rhs.fArray = rhs.InitialArrayValue ();
				std::swap(fAllocator, rhs.fAllocator);
				fLength = rhs.fLength;
				rhs.fLength = 0;
			}
			else if (rhs.fLength == 0 && rhs.fArray == (pointer)rhs.fPrivateBuffer)
			{
				if (fArray == (pointer)fPrivateBuffer)
				{
					reserve (capacity () + 1);
				}
				ASSERT (fArray != (pointer)fPrivateBuffer);
				
				rhs.fArray = fArray;
				fArray = InitialArrayValue ();
				std::swap(fAllocator, rhs.fAllocator);
				rhs.fLength = fLength;
				fLength = 0;
			}	
			else
			{		
				if (fArray == (pointer)fPrivateBuffer)
				{
					reserve (capacity () + 1);
				}
				ASSERT (fArray != (pointer)fPrivateBuffer);
			
				if (rhs.fArray == (pointer)rhs.fPrivateBuffer)
				{
					rhs.reserve (rhs.capacity () + 1);
				}
				ASSERT (rhs.fArray != (pointer)rhs.fPrivateBuffer);
				
				std::swap(fArray, rhs.fArray);
				std::swap(fAllocator, rhs.fAllocator);
				std::swap(fLength, rhs.fLength);
			}
		}
	}
}


//---------------------------------------------------------------
//
// K2VectorBase::clear
//
//---------------------------------------------------------------
template <class T, class Allocator>
void K2VectorBase<T, Allocator>::clear()
{
	K2destroy(begin(), end());
	fLength = 0;
}


//---------------------------------------------------------------
//
// K2VectorBase::DoCleanup
//
//---------------------------------------------------------------
template <class T, class Allocator>
void K2VectorBase<T, Allocator>::DoCleanup()
{
	if (fArray != nil)
	{
		typedef typename PODTraits<T>::data_type loc_data_type;
		K2Internals::destroyAux(fArray, fArray + fLength, loc_data_type());
		if (fArray != (pointer)fPrivateBuffer)
		{
			fAllocator.deallocate(fArray, fAllocator.f);
		}
	}
}


//---------------------------------------------------------------
//
// K2VectorBase::DoGetCapacity
//
//---------------------------------------------------------------
template <class T, class Allocator>
typename K2VectorBase<T, Allocator>::size_type K2VectorBase<T, Allocator>::DoGetCapacity(size_type newLength)
{
	size_type newCap = capacity();
	
	if (newCap < 4)
		newCap = kInitialAllocSize > 4 ? kInitialAllocSize : 4;
	
	while (newLength > newCap) { // multiply times 1.5
		newCap *= 3;
		newCap /= 2;		
	}
	return newCap;
}


//---------------------------------------------------------------
//
// K2VectorBase::DoReset
//
//---------------------------------------------------------------
template <class T, class Allocator>
void K2VectorBase<T, Allocator>::DoReset(pointer newData, size_type newLength, size_type newCap)
{
	if (fArray != nil)
	{
		K2destroy(fArray, fArray + fLength);
		if (fArray != (pointer)fPrivateBuffer)
		{
			fAllocator.deallocate(fArray, fAllocator.f);
		}
	}

	fArray = newData;
	fLength = newLength;
	fAllocator.f = newCap;
}


//---------------------------------------------------------------
//
// K2VectorBase::initialize
//
//---------------------------------------------------------------
template <class T, class Allocator>
void K2VectorBase<T, Allocator>::initialize(size_type count, const T& value)
{
	ASSERT_MSG (count <= max_size(), "K2VectorBase::construction length error");
	ASSERT_MSG (fArray == nil || fArray == (pointer)fPrivateBuffer, "K2VectorBase::construction fArray has unexpected value?");
	ASSERT_MSG (fLength == 0, "K2VectorBase::construction fLength isn't 0?");

	if (count > 0)
	{
		fLength = fAllocator.f = count;
		fArray = fAllocator.allocate(count);
		K2uninitialized_fill_n(fArray, fLength, value);	
	}	
}

}	// namespace K2Internals



#if __MWERKS__
#pragma mark -
#endif

//---------------------------------------------------------------
//
// K2Vector::ForceInstantiation
//
// To reduce code bloat Public explicitly instantiates and exports
// K2Vector's of the most common types. Unfortunately instantiating
// K2Vector may not cause K2VectorBase to be instantiated. To work
// around this we'll reference all the outlined K2VectorBase methods
// here. To prevent the references from being optimized away we'll
// return the member function pointer from the function.
//
//---------------------------------------------------------------
template <class T, class Allocator>
typename K2Vector<T, Allocator>::Method K2Vector<T, Allocator>::ForceInstantiation(int n)
{	
	ASSERT(false);				// this function should never be called
	
	using namespace K2Internals;
	
	Method m = nil;
	switch (n) {
		case 0:
			break;

		case 1:
			break;

		case 2:
			m = (Method) &Inherited::CopyConstructHelper;
			break;

		case 3:
			m = (Method) &Inherited::DoCleanup;
			break;

		//case 4:
		//	m = (Method) &Inherited::operator=;
		//	break;

		case 5:
			m =  (Method) &Inherited::fill_assign;
			//m = (Method) (void (Inherited::*)(Inherited::const_iterator, Inherited::const_iterator)) &Inherited::fill_assign;
			//m = (Method) (void (Inherited::*)(Inherited::const_iterator, Inherited::const_iterator)) &Inherited::fill_assign;
//			&vector_assign_forward_iter<K2Vector, K2Vector::iterator>;
			break;

		case 6:
			{
			typedef void (K2Vector::*foo)(typename K2Vector<T,Allocator>::size_type, const T&);
			m = (Method) (foo) &Inherited::assign;
			}
			break;

		case 7:
			{
			typedef void (K2Vector::*foo)(typename K2Vector<T,Allocator>::size_type, const T&);
			m = (Method) (foo) &Inherited::resize;
			}
			break;

		case 8:
			{
			typedef void (K2Vector::*foo)(typename K2Vector<T,Allocator>::size_type);
			m = (Method) (foo) &Inherited::reserve;
			}
			break;

		case 9:
			{
			typedef void (K2Vector::*foo)(const T&);
			m = (Method) (foo) &Inherited::push_back;
			}
			break;

		case 10:
			m = &Inherited::pop_back;
			break;

		//case 11:
		//	m = (Method) (void (K2Vector::*)(K2Vector<T,Allocator>::iterator, size_type, const T&)) &K2Vector::insert;
		//	break;

		//case 12:
		//	m = (Method) (void (K2Vector::*)(K2Vector<T,Allocator>::iterator, 
		//			K2Vector<T,Allocator>::const_iterator, K2Vector<T,Allocator>::const_iterator))
		//			 &K2Vector::insert;
		//	break;

		case 13:
			m =  (Method) &Inherited::fill_insert;
			break;

		case 14:
			m = (Method) &Inherited::initialize;
			break;

		case 20:
			m = (Method) (typename Inherited::iterator (Inherited::*)(typename Inherited::iterator)) &Inherited::erase;
			break;

		case 21:
			m = (Method) (typename Inherited::iterator (Inherited::*)(typename Inherited::iterator, typename Inherited::iterator)) &Inherited::erase;
			break;

		case 22:
			m = (Method) (typename Inherited::iterator (Inherited::*)(Inherited&)) &Inherited::swap;
			break;

		case 23:
			m = &Inherited::clear;
			break;

		case 24:
			{
			typedef typename Inherited::iterator bar;
			typedef bar (Inherited::*foo)(typename Inherited::size_type);
			m = (Method) (foo) &Inherited::DoGetCapacity;
			}
			break;

		case 25:
			m = (Method) (void (Inherited::*)(typename Inherited::pointer, typename Inherited::size_type, typename Inherited::size_type)) &Inherited::DoReset;
			break;
	}
	
	return m;
}


#endif 

