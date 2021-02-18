//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/K2VectorHelpers.h $
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

#pragma once
#ifndef __K2VectorHelpers__
#define __K2VectorHelpers__

namespace VectorHelpers {	
	struct ForwardIterTag {};
	struct IntegerTag {};
	struct InputIterTag {};

	// Forward (or better) Iterators
	template <class ForwardIterator, class Vector>
	void assign(ForwardIterator first, ForwardIterator last, Vector* v, typename Vector::Hole h, ForwardIterTag)
	{
		typedef typename Vector::size_type size_type;
		size_type (&fLength) (h.LengthRef(v)); 
		typedef typename Vector::pointer pointer;
//		pointer(&fArray)(h.ArrayRef(v));
		typedef typename Vector::allocator_type allocator_type;
		K2EmptyMemberOpt<allocator_type, size_type> (& fAllocator) (h.AllocatorRef(v));
		size_type len = (size_type)std::distance(first, last);	// $$$ need to get rid of all the calls to standard algorithms
		ASSERT_MSG(len <= v->max_size(), "K2VectorTempBase::assign length error");

		if (len <= v->capacity())
		{
			typename Vector::iterator i = v->begin();
			
			if (len <= fLength)
			{
				i = K2copy(first, last, i);
				K2destroy(i, v->end());
			}
			else
			{

    			ForwardIterator mid = first;
    			std::advance(mid, fLength); //$$$ remove std calls 
    			i = K2copy(first, mid, i);
    			K2uninitialized_copy(mid, last, i);    
   		}
			
			fLength = len;
		}
		else
		{
			typename Vector::pointer newData = fAllocator.allocate(len);
			K2uninitialized_copy(first, last, newData);
			v->DoReset(newData, len, len);
		}
	}

	template <class ForwardIterator, class Vector>
	void insert(typename Vector::iterator position, ForwardIterator first, ForwardIterator last, Vector* v, typename Vector::Hole h, ForwardIterTag)
	{
		typedef typename Vector::size_type size_type;
		typedef typename Vector::Hole Hole;
		size_type (&fLength) (h.LengthRef(v)); 
		typedef typename Vector::pointer pointer;
		pointer(&fArray)(h.ArrayRef(v));

		typedef typename Vector::allocator_type allocator_type;
		K2EmptyMemberOpt<allocator_type, size_type> (& fAllocator) (h.AllocatorRef(v));

		ASSERT(position >= v->begin());
		ASSERT(position <= v->end());
		ASSERT(first <= last);

		size_type n = (size_type) std::distance(first, last); // $$$ remove calls to std::
		ASSERT(n <= v->max_size());
		ASSERT(fLength <= v->max_size() - n);

		if (first == last)
			return;
			
		if (fLength + n <= v->capacity())
		{
 			typename Vector::pointer oldFinish = fArray + fLength; // same as end()
			const size_type elementsAfter = static_cast<size_type>(oldFinish - position);
			if (n <= elementsAfter)
			{
				// Copy the elements at the end of the array into the uninitialized part 
				// of the vector
				K2uninitialized_copy(oldFinish - n, oldFinish, oldFinish);

				// Move any remaining elements over to make room for the new elements
				K2copy_backward(position, oldFinish - n,  oldFinish);
		
				// Copy the new elements in
				K2copy(first, last, position);
			}
			else
			{
				// Copy the elements at the end of the array into the uninitialized part 
				// of the vector
				K2uninitialized_copy(position, oldFinish, oldFinish + n - elementsAfter);
		
				// Copy the new elements in
				K2copy(first, first+elementsAfter, position);
				
				std::advance(first, elementsAfter); //$$$ remove calls to std::
			
				// Construct the new elements after the old array end
				K2uninitialized_copy(first, last, oldFinish);
			}
			fLength += n;
		}
		else
		{
			size_type newLen = fLength + n;
			size_type newCap = v->DoGetCapacity(newLen);
			
			// Copy over the old data up to our insertion point
			typename Vector::pointer newData = fAllocator.allocate(newCap);
			typename Vector::pointer newFinish = K2uninitialized_copy(fArray, position, newData);

			// Stick the new data in
			newFinish = K2uninitialized_copy(first, last, newFinish);
			
			// And copy any old data after the insertion point
			K2uninitialized_copy(position, fArray + fLength, newFinish);
					
			v->DoReset(newData, newLen, newCap);
		}
	}

	template <class ForwardIterator, class Vector>
	void initialize(ForwardIterator first, ForwardIterator last, Vector* v, typename Vector::Hole h, ForwardIterTag)

	{
		typedef typename Vector::size_type size_type;
		typedef typename Vector::Hole Hole;
		size_type (&fLength) (h.LengthRef(v)); 
		typedef typename Vector::pointer pointer;
		pointer(&fArray)(h.ArrayRef(v));
		typedef typename Vector::allocator_type allocator_type;
		K2EmptyMemberOpt<allocator_type, size_type> (& fAllocator) (h.AllocatorRef(v));

		fLength = fAllocator.f = std::distance(first, last); // $$$ remove calls to std::
		ASSERT_MSG (fAllocator.f <= v->max_size(), "K2VectorTempBase::construction length error");
		fArray = nil;

		if (fAllocator.f > 0)
		{
			fArray = fAllocator.allocate(fAllocator.f);
			K2uninitialized_copy(first, last, fArray);
		}					
	}

	// Integers
	template <typename I, class Vector>
	void assign(I count, I value, Vector* v, typename Vector::Hole h, IntegerTag)
	{
		v->fill_assign(count, value);
	}


	template <typename I, class Vector>
	void initialize(I count, I value, Vector*  v, typename Vector::Hole h, IntegerTag)
	{
		v->initialize(count, value);
	}

	template <typename I, class Vector>
	void insert(typename Vector::iterator pos, I count, I value, Vector* v, typename Vector::Hole /* h */, IntegerTag)
	{
		v->fill_insert(pos, count, value);
	}

	// Input Iterators
	template <class InputIterator, class Vector>
	void assign(InputIterator first, InputIterator last, Vector* v, typename Vector::Hole h, InputIterTag)
	{
		typename Vector::iterator cur = v->begin();
		for ( ; first != last && cur != v->end(); ++cur, ++first)
		  *cur = *first;
		  
		if (first == last)
		  v->erase(cur, v->end());
		else
		  v->insert(v->end(), first, last);
	}

	template <class InputIterator, class Vector>
	void initialize(InputIterator first, InputIterator last, Vector* v, typename Vector::Hole h, InputIterTag)
	{
		for ( ; first != last; ++first)
			v->push_back(*first);
	}

	template <class InputIterator, class Vector>
	void insert(typename Vector::iterator pos, InputIterator first, InputIterator last, Vector* v, typename Vector::Hole h, InputIterTag)
	{
		uint32 index = pos - v->begin();
		for ( ; first != last; ++first)				// with a normal iterator we can optimize the code using std::distance 
		{											// but this doesn't work too well with input iterators so we have to go the inefficient route
			v->insert(v->begin() + index, *first);
			++index;								// insert invalidates iterators so we'll use indices
		}
	}
	
}	// namespace VectorHelpers
#endif // __K2VectorHelpers__
