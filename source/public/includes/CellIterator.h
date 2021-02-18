//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CellIterator.h $
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
#ifndef __CellIterator__
#define __CellIterator__

#include <iterator>
#include <functional>
#include "TableTypes.h"
#include "K2Iterator.h"

template<class S, class T, class A>
inline
std::binder1st<std::mem_fun1_t<S, T, A> >
mem_functor(S (T::*f)(A), T* obj)
{
	return std::bind1st(mem_fun(f), obj);
}

template <class Structure>
class CellIterator
{
public:
	// declare typedefs by hand instead of inheriting from std::iterator
	typedef GridAddress							value_type;
	typedef std::ptrdiff_t						difference_type;
	typedef const GridAddress*   				pointer;
	typedef const GridAddress& 					reference;

	typedef std::bidirectional_iterator_tag	iterator_category;

						CellIterator(const GridAddress& gridRef, const GridArea& gridArea, const Structure* structure);
						CellIterator(const CellIterator& rhs);
						~CellIterator();

	const GridAddress&	operator * () const;
	const GridAddress*	operator -> () const;

	CellIterator&		operator ++ ();
	CellIterator		operator ++ (int);
	CellIterator&		operator= (const CellIterator& rhs);

	CellIterator&		operator -- ();
	CellIterator		operator -- (int);

	bool16				operator ==(const CellIterator& rhs) const;
	bool16				operator != (const CellIterator& rhs) const;
	bool16				operator < (const CellIterator& rhs) const;

private:
	void				MoveForward();
	void				MoveBackward();

private:
	GridAddress			fGridAddress;
	GridArea  			fGridArea;
	const Structure*	fStructure;
};

template <class Structure>
struct ReverseCellIterator
{

public:
	typedef CellIterator<Structure>	iterator_type;
	typedef std::bidirectional_iterator_tag iterator_category;

	typedef GridAddress				value_type;
	typedef std::ptrdiff_t			difference_type;
	typedef const GridAddress*   	pointer;
	typedef const GridAddress& 		reference;

	explicit ReverseCellIterator(iterator_type x) : fCurrent(x), fCached(fCurrent) {}

	iterator_type base() const {	return fCurrent; }
	reference operator*() const
	{
		if(fCached != fCurrent)
			fCached = fCurrent;
		return *--fCached;
	}
	pointer   operator->() const { return &(**this); }

	ReverseCellIterator& operator++()	{ --fCurrent; return *this; }

	ReverseCellIterator  operator++(int)
	{
		ReverseCellIterator tmp = *this;
		--fCurrent;
		return tmp;
	}

	ReverseCellIterator& operator--() 	{++fCurrent; return *this; }

	ReverseCellIterator  operator--(int)
	{
		ReverseCellIterator tmp = *this;
		++fCurrent;
		return tmp;
	}

//	ReverseCellIterator  operator+ (difference_type n) const {	return ReverseCellIterator(fCurrent - n); }
//	ReverseCellIterator& operator+=(difference_type n) { fCurrent -= n; return *this; }

//	ReverseCellIterator  operator- (difference_type n) const {	return ReverseCellIterator(fCurrent + n); }
//	ReverseCellIterator& operator-=(difference_type n) { fCurrent += n; return *this; }
//	reference operator[](difference_type n) const 	{return fCurrent[-n-1];}

protected:
	iterator_type			fCurrent;
	mutable iterator_type	fCached;
};

template <typename T>
inline bool16 operator==(const ReverseCellIterator<T>& lhs,
						 const ReverseCellIterator<T>& rhs)
{
	return static_cast<bool16>(lhs.base() == rhs.base());
}

template <typename T>
inline
bool16
operator< (const ReverseCellIterator<T>& lhs,
           const ReverseCellIterator<T>& rhs)
{
	return static_cast<bool16>(lhs.base() < rhs.base());
}

template <typename T>
inline
bool16
operator!=(const ReverseCellIterator<T>& lhs,
           const ReverseCellIterator<T>& rhs)
{
	return static_cast<bool16>(lhs.base() != rhs.base());
}

/*
template <typename T>
inline
bool16
operator> (const ReverseCellIterator<T>& lhs,
           const ReverseCellIterator<T>& rhs)
{
	return static_cast<bool16>(lhs.base() > rhs.base());
}

template <typename T>
inline
bool16
operator>=(const ReverseCellIterator<T>& lhs,
           const ReverseCellIterator<T>& rhs)
{
	return static_cast<bool16>(lhs.base() >= rhs.base());
}

template <typename T>
inline
bool16
operator<=(const ReverseCellIterator<T>& lhs,
           const ReverseCellIterator<T>& rhs)
{
	return static_cast<bool16>(lhs.base() <= rhs.base());
}

template <typename T>
inline
ReverseCellIterator::difference_type
operator-(const ReverseCellIterator<T>& lhs,
          const ReverseCellIterator<T>& rhs)
{
	return rhs.base() - lhs.base();
}

template <typename T>
inline ReverseCellIterator<T>
operator+(ReverseCellIterator<T>::difference_type n,
          const ReverseCellIterator<T>& lhs)
{
	return ReverseCellIterator(lhs.base() - n);
}


*/

#endif //__CellIterator__
