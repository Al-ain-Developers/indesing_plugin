//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/architecture/k2sortedvector.h $
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
#ifndef __K2SORTEDVECTOR__
#define __K2SORTEDVECTOR__

#ifdef ID_DEPRECATED
#include "K2Vector.h"

//-----------------------------------
//	Forward References
//
template <class T, class A> class K2SortedVector;

class IPMStream;
template <class T, class A> void K2Read(IPMStream* stream, K2SortedVector<T, A>& v);
template <class T, class A> void K2Write(IPMStream* stream, const K2SortedVector<T, A>& v);


// ===================================================================================
//	K2SortedVector
// ===================================================================================
template <class T, class Allocator = K2Allocator<T> >
class K2SortedVector {
public:
	// types:
	typedef	object_type data_type;

	typedef typename Allocator::reference         reference;
	typedef typename Allocator::const_reference   const_reference;
	typedef typename Allocator::const_pointer     iterator;				// since we don't change elements in sorted collections
	typedef typename Allocator::const_pointer     const_iterator;
	typedef typename Allocator::size_type         size_type;
	typedef typename Allocator::difference_type   difference_type;
	typedef T                                     value_type;
	typedef Allocator                             allocator_type;
	typedef typename Allocator::pointer           pointer;
	typedef typename Allocator::const_pointer     const_pointer;
	typedef K2Reverse_iterator<const_iterator, value_type, difference_type, const_pointer, const_reference> const_reverse_iterator;
	typedef const_reverse_iterator       		  reverse_iterator;


	// construction and assignment
							K2SortedVector() 										{}
    explicit 				K2SortedVector(int32 cap) 				: fVector()
                                    { fVector.reserve(cap); }
	K2SortedVector(const K2SortedVector& rhs) = default;
	K2SortedVector(K2SortedVector&& rhs) = default;
	K2SortedVector &operator=(const K2SortedVector& rhs) = default;
	K2SortedVector &operator=(K2SortedVector&& rhs) = default;

	friend inline void swap(K2SortedVector<T, Allocator>& a, K2SortedVector<T, Allocator>& b) noexcept(noexcept(swap(a.fVector, b.fVector)))
	{
		using std::swap;
		swap(a.fVector, b.fVector);
	}

	explicit 				K2SortedVector(const K2Vector<T, Allocator>& rhs);
							// Note that this removes duplicate values.

	~K2SortedVector() {}

	// iterators
	iterator               begin()					{return fVector.begin();}
	const_iterator         begin() const			{return fVector.begin();}
	iterator               end()					{return fVector.end();}
	const_iterator         end() const				{return fVector.end();}
	//reverse_iterator       rbegin()					{return fVector.rbegin();}
	const_reverse_iterator rbegin() const			{return fVector.rbegin();}
	//reverse_iterator       rend()					{return fVector.rend();}
	const_reverse_iterator rend() const				{return fVector.rend();}

	//  capacity:
	bool          			empty() const			{return fVector.empty();}
	size_type     			size() const			{return (size_type)fVector.size();}
	size_type     			max_size() const		{return (size_type)fVector.max_size();}
	size_type 	 			capacity () const 		{return (size_type)fVector.capacity();}

	//  modifiers:
	bool16 					operator==(const K2SortedVector& rhs) const {return fVector == rhs.fVector;}
	bool16 					operator!=(const K2SortedVector& rhs) const {return fVector != rhs.fVector;}

	const T& 				operator[](int32 i) const 		{return fVector[i];}
	T&						operator[](int32 i)				{return fVector[i];}

	void 					SetChunkSize(int32 chunk) 		{fVector.reserve(chunk);}
	bool16 					Preallocate(int32 newlen) 		{fVector.reserve(newlen); return kTrue;}

	void 					Clear() 						{fVector.clear();}
	int32 					Insert(const T& x);
	int32 					Insert(const T& x, int32 insertBeforeHint);
	void 					Remove(int32 at) 				{fVector.erase(fVector.begin() + at);}
	void 					Remove(int32 from, int32 to) 	{fVector.erase(fVector.begin() + from,fVector.begin() + to);}
	void 					Replace(int32 at, const T& x) 	{fVector.erase(fVector.begin() + at); Insert( x);}

	int32 					ChunkSize() const 				{return 8;}  //AW_TODO: Possibly deprecate this?
	int32 					Length() const 					{return (int32)fVector.size();}
	bool16 					IsEmpty() const 				{return fVector.empty();}
	const T& 				First() const 					{return fVector.front();}
	const T& 				Last() const 					{return fVector.back();}
	int32 					Location(const T& x) const;

	// streaming
#ifdef WINDOWS
	friend void K2Read(IPMStream* stream, K2SortedVector<T, Allocator>& v);				// these are defined in k2VectorStreaming.h
	friend void K2Write(IPMStream* stream, const K2SortedVector<T, Allocator>& v);
#else
	friend void K2Read <T>(IPMStream* stream, K2SortedVector<T, Allocator>& v);
	friend void K2Write <T>(IPMStream* stream, const K2SortedVector<T, Allocator>& v);
#endif

private:
	 K2Vector<T, Allocator>	fVector;
};

#define K2SortedPtrVector K2SortedVector
#ifdef _INCLUDE_TPP_IN_H_
	#include "k2sortedvector.tpp"
#endif //_INCLUDE_TPP_IN_H_
#endif // ID_DEPRECATED
#endif //__K2SORTEDVECTOR__
