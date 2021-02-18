//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/K2Iterator.h $
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
#ifndef __K2Iterator__
#define __K2Iterator__

#ifdef WINDOWS
#pragma warning(disable: 4786)		// warning: identifier was truncated to 255 characters
#endif

#include <iterator>

/** Generic reverse iterator. Implements a "reversed iterator" i.e. an iterator that goes backwards.
	When this class was developped we were using VC6
	and it was difficult to implement certain things with VC6's limited support for templates.
	This class was tested only for random access iterator types.
	Template parameter "Iterator" models an iterator type. K2Reverse_iterator uses this iterator to advance.
*/
template <class Iterator, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
class K2Reverse_iterator
{
public:
	typedef Iterator                iterator_type;
	typedef typename std::iterator_traits<Iterator>::iterator_category iterator_category;
	typedef T						value_type;
	typedef Pointer					pointer;
	typedef Reference				reference;
	typedef Distance				difference_type;

	K2Reverse_iterator();
	explicit K2Reverse_iterator(Iterator x);
	Iterator base() const;      //  explicit
	reference operator*() const;
	pointer   operator->() const;
	K2Reverse_iterator& operator++();
	K2Reverse_iterator  operator++(int);
	K2Reverse_iterator& operator--();
	K2Reverse_iterator  operator--(int);
	K2Reverse_iterator  operator+ (difference_type n) const;
	K2Reverse_iterator& operator+=(difference_type n);
	K2Reverse_iterator  operator- (difference_type n) const;
	K2Reverse_iterator& operator-=(difference_type n);
	reference operator[](difference_type n) const;

protected:
	Iterator		fCurrent;
};

/** Inline implementations for K2Reverse_iterator member functions.
*/

template <class Iterator, class T, class Distance, class Pointer, class Reference>
inline
K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>::K2Reverse_iterator()
{
}

template <class Iterator, class T, class Distance, class Pointer, class Reference>
inline
K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>::K2Reverse_iterator(Iterator x)
	: fCurrent(x)
{
}


template <class Iterator, class T, class Distance, class Pointer, class Reference>
inline
Iterator
K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>::base() const
{
	return fCurrent;
}

template <class Iterator, class T, class Distance, class Pointer, class Reference>
inline
typename K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>::reference
K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>::operator*() const
{
	Iterator tmp = fCurrent;
	return *--tmp;
}

template <class Iterator, class T, class Distance, class Pointer, class Reference>
inline
typename K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>::pointer
K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>::operator->() const
{
	return &(**this);
}

template <class Iterator, class T, class Distance, class Pointer, class Reference>
inline
K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>&
K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>::operator++()
{
	--fCurrent;
	return *this;
}

template <class Iterator, class T, class Distance, class Pointer, class Reference>
inline
K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>
K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>::operator++(int)
{
	K2Reverse_iterator tmp = *this;
	--fCurrent;
	return tmp;
}

template <class Iterator, class T, class Distance, class Pointer, class Reference>
inline
K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>&
K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>::operator--()
{
	++fCurrent;
	return *this;
}

template <class Iterator, class T, class Distance, class Pointer, class Reference>
inline
K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>
K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>::operator--(int)
{
	K2Reverse_iterator tmp = *this;
	++fCurrent;
	return tmp;
}

template <class Iterator, class T, class Distance, class Pointer, class Reference>
inline
K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>
K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>::operator+ (difference_type n) const
{
	return K2Reverse_iterator(fCurrent - n);
}

template <class Iterator, class T, class Distance, class Pointer, class Reference>
inline
K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>
K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>::operator- (difference_type n) const
{
	return K2Reverse_iterator(fCurrent + n);
}

template <class Iterator, class T, class Distance, class Pointer, class Reference>
inline
K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>&
K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>::operator+=(difference_type n)
{
	fCurrent -= n;
	return *this;
}

template <class Iterator, class T, class Distance, class Pointer, class Reference>
inline
K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>&
K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>::operator-=(difference_type n)
{
	fCurrent += n;
	return *this;
}

template <class Iterator, class T, class Distance, class Pointer, class Reference>
inline
typename K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>::reference
K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>::operator[](difference_type n) const
{
	return fCurrent[-n-1];
}

template <class Iterator, class T, class Distance, class Pointer, class Reference>
inline
bool16
operator==(const K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>& lhs,
           const K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>& rhs)
{
	return static_cast<bool16>(lhs.base() == rhs.base());
}

template <class Iterator, class T, class Distance, class Pointer, class Reference>
inline
bool16
operator< (const K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>& lhs,
           const K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>& rhs)
{
	return static_cast<bool16>(lhs.base() < rhs.base());
}

template <class Iterator, class T, class Distance, class Pointer, class Reference>
inline
bool16
operator!=(const K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>& lhs,
           const K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>& rhs)
{
	return static_cast<bool16>(lhs.base() != rhs.base());
}

template <class Iterator, class T, class Distance, class Pointer, class Reference>
inline
bool16
operator> (const K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>& lhs,
           const K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>& rhs)
{
	return static_cast<bool16>(lhs.base() > rhs.base());
}

template <class Iterator, class T, class Distance, class Pointer, class Reference>
inline
bool16
operator>=(const K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>& lhs,
           const K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>& rhs)
{
	return static_cast<bool16>(lhs.base() >= rhs.base());
}

template <class Iterator, class T, class Distance, class Pointer, class Reference>
inline
bool16
operator<=(const K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>& lhs,
           const K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>& rhs)
{
	return static_cast<bool16>(lhs.base() <= rhs.base());
}

template <class Iterator, class T, class Distance, class Pointer, class Reference>
inline
typename K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>::difference_type
operator-(const K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>& lhs,
          const K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>& rhs)
{
	return rhs.base() - lhs.base();
}

template <class Iterator, class T, class Distance, class Pointer, class Reference>
inline K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>
operator+(typename K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>::difference_type n,
          const K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>& lhs)
{
	return K2Reverse_iterator<Iterator, T, Distance, Pointer, Reference>(lhs.base() - n);
}



#endif //__K2Iterator__