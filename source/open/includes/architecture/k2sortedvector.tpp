//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/architecture/k2sortedvector.tpp $
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

#ifndef __K2SortedVectortpp__
#define __K2SortedVectortpp__
#include "k2sortedvector.h"

#ifdef ID_DEPRECATED


template <class T, class Allocator>
K2SortedVector<T, Allocator>::K2SortedVector(const  K2Vector<T, Allocator>& rhs)
	: fVector(rhs)
{
	std::sort(fVector.begin(), fVector.end());
	typename K2Vector<T, Allocator>::iterator i = std::unique(fVector.begin(), fVector.end());
	fVector.erase(i, fVector.end());
}

template <class T, class Allocator>
int32 K2SortedVector<T, Allocator>::Insert(const T& t)
{
	typename K2Vector<T, Allocator>::iterator i = std::lower_bound(fVector.begin(), fVector.end(), t);
	//if(i != fVector.end() && t == *i)
	//	*i = t;
	//else
		i = fVector.insert(i, t);
	return i - fVector.begin();
}

template <class T, class Allocator>
int32 K2SortedVector<T, Allocator>::Insert(const T& t, int32 hint)
{
	typedef typename K2Vector<T, Allocator>::iterator iteratorV;
	typename K2Vector<T, Allocator>::iterator i = fVector.begin() + hint;
#if DEBUG
	std::pair<iteratorV, iteratorV> p = std::equal_range(fVector.begin(), fVector.end(), t);
	ASSERT_MSG(p.first <= i && i <= p.second,  "K2SortedVector::Insert hint is wrong");
#endif
	//if(i != fVector.end() && t == *i)
	//	*i = t;
	//else
		i = fVector.insert(i, t);
	return i - fVector.begin();
}

template <class T, class Allocator>
int32 K2SortedVector<T, Allocator>::Location(const T& t) const
{
	typename K2Vector<T, Allocator>::const_iterator i = std::lower_bound(fVector.begin(), fVector.end(), t);
	int32 index = -1;
	if(i != fVector.end() && *i == t) 
		index = i - fVector.begin();
	return index;
}

#endif // ID_DEPRECATED
#endif // __K2SortedVectortpp__
