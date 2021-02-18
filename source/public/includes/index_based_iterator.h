//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/index_based_iterator.h $
//  
//  Owner: Florin Trofin
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
//  Iterator adapter for containers that support indexes.
//  Most iterators are implemented with straight pointers. However, those will not work
//  with containers that implement copy-on-write (COW). In that case the containers
//  will share the same storage until a non-const operation occurs (like changing a value) when
//  a separate copy of the existing storage needs to be made which will invalidate all iterators.
//  Because this iterator uses indexes rather than pointers, it does not suffer from that problem.
//  
//  INTERNAL USE ONLY! Do not use this class directly.
//  
//========================================================================================

#pragma once
#ifndef __INDEX_BASED_ITERATOR__
#define __INDEX_BASED_ITERATOR__

#include <boost/iterator/iterator_facade.hpp>
#include <boost/type_traits.hpp>

# ifndef BOOST_NO_SFINAE
#  include <boost/type_traits/is_convertible.hpp>
#  include <boost/utility/enable_if.hpp>
# endif

/** INTERNAL USE ONLY! Do not use this class directly.
	Index-based iterator class used by containers that support indexes.
	T models the container type and needs to implement these methods:
		size_type size() const;
		const_reference get_const_ref(difference_type pos) const;
		reference get_ref(difference_type pos);

	R models the return type for the dereference operation
*/
template<class T, typename R>
class index_based_iterator :
	public boost::iterator_facade<
		index_based_iterator<T, R>,
		R,
		boost::random_access_traversal_tag>
{
	// Helper for special constructor
	struct conversion_enabler {};

public:
	typedef typename T::difference_type difference_type;

	index_based_iterator()
		: fContainer(nil), fPos(0)
	{
	}
	explicit index_based_iterator(T const& storage, difference_type pos)
		: fContainer(&storage), fPos(pos)
	{
	}
	// This constructor ensures conversion from iterator to const_iterator
	// but not viceversa (the second parameter of the constructor
	template<typename OtherValue>
	index_based_iterator( index_based_iterator<T, OtherValue> const& other,
		typename boost::enable_if<boost::is_convertible<OtherValue*, R*>, conversion_enabler>::type = conversion_enabler() )
		: fContainer(other.fContainer), fPos(other.fPos)
	{
	}

#ifdef DEBUG
	// These functions are for DEBUG purposes only! use them only in ASSERTS!

	// Checks if the iterator is within the valid range [begin, end]
	// Note that end is a valid position for the iterator, but it should not be dereferenced.
	bool is_valid() const
	{
		return fContainer && fPos >=0 && fPos <= (difference_type)fContainer->size();
	}

	// Retrieves the container to which this iterator belongs
	T const* get_container() const
	{
		return fContainer;
	}
#endif

	// Data members
private:
	difference_type fPos;
	T const* fContainer;
	
	// The base class will call these core functions to do it's work
private:
	friend class boost::iterator_core_access; // grant access to base class
	template <class, typename> friend class index_based_iterator;

	void increment()
	{
#ifdef DEBUG
        ASSERT(is_valid());
#endif
		++fPos;
	}

	void decrement()
	{
#ifdef DEBUG
        ASSERT(is_valid());
#endif
		--fPos;
	}

	void advance(difference_type n)
	{
		ASSERT(fContainer);
		fPos += n;
#ifdef DEBUG
        ASSERT(is_valid());
#endif
	}

	template<typename OtherValue>
	difference_type distance_to(index_based_iterator<T, OtherValue> const& rhs) const
	{
		ASSERT(fContainer == rhs.fContainer);
		return rhs.fPos - fPos;
	}

	template<typename OtherValue>
	bool equal(index_based_iterator<T, OtherValue> const& rhs) const
	{
		ASSERT(fContainer == rhs.fContainer);
		return fPos == rhs.fPos;
	}

    template <bool> class Selector {};

	// delegates to specific implementations (const and non-const)
	R& dereference() const
	{
		ASSERT(fContainer && fPos >=0 && fPos < (difference_type)fContainer->size());
		return dereference_impl(Selector<boost::is_const<R>::value>());
	}

	// mutable access
	R& dereference_impl(Selector<false>) const
	{
		return const_cast<T&>(*fContainer).get_ref(fPos);
	}

	// const read access
	R& dereference_impl(Selector<true>) const
	{
		return fContainer->get_const_ref(fPos);
	}
}; // index_based_iterator

#endif  // __INDEX_BASED_ITERATOR__

