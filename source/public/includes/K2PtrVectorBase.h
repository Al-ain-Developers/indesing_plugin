//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/K2PtrVectorBase.h $
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
#ifndef __K2PtrVectorBase__
#define __K2PtrVectorBase__

#include "K2VectorBase.h"

// ===================================================================================
//	K2PtrVectorBase: don not use directly - use K2Vector instead
// 		When Visual C supports it we can use partial class specialization instead
// ===================================================================================
namespace K2Internals {
template <class T/*, class Allocator = K2Allocator<T>*/ > // Can't support Allocators here with VC6 (Rebind crashes compiler)
class K2PtrVectorBase {
// Classes in K2Internals are not intended to be used directly. Use K2vector instead
	typedef K2VectorBase<const void*, K2Allocator<const void*> > Inherited;
	typedef Inherited::allocator_type base_allocator; // really want rebind here
	typedef K2Allocator<T> Allocator;
	friend class K2Vector<T, Allocator>;
public:
	typedef	object_type 				data_type;

	typedef T			 				value_type;
	typedef value_type* 				pointer;
	typedef const value_type* 			const_pointer;
	typedef value_type* 				iterator;
	typedef const value_type* 			const_iterator;
	typedef value_type& 				reference;
	typedef const value_type& 			const_reference;
	typedef std::size_t 						size_type;
	typedef std::ptrdiff_t 					difference_type;
  	typedef Allocator					allocator_type;

	typedef K2Reverse_iterator<iterator, value_type, difference_type, pointer, reference>       			reverse_iterator;
	typedef K2Reverse_iterator<const_iterator, value_type, difference_type, const_pointer, const_reference> const_reverse_iterator;

public:
	explicit 	K2PtrVectorBase(/*const Allocator& a = Allocator()*/)  : fArray(base_allocator()) {}
				K2PtrVectorBase(size_type count, const T& value/*, const Allocator& a = Allocator()*/)
					: fArray((Inherited::size_type)count, value) {}
				K2PtrVectorBase(const_iterator first, const_iterator last/*, const Allocator& a = Allocator()*/)
					: fArray(Inherited::const_iterator(first), Inherited::const_iterator(last)) {}
				K2PtrVectorBase(const K2PtrVectorBase& rhs) = default;
				K2PtrVectorBase(K2PtrVectorBase&& rhs) noexcept = default;
				K2PtrVectorBase &operator=(const K2PtrVectorBase& rhs) = default;
				K2PtrVectorBase &operator=(K2PtrVectorBase&& rhs) noexcept = default;

public:
	iterator               begin()					{return iterator(fArray.begin());}
	const_iterator         begin() const			{return const_iterator(fArray.begin());}
	iterator               end()					{return iterator(fArray.end());}
	const_iterator         end() const				{return const_iterator(fArray.end());}
	reverse_iterator       rbegin()					{return reverse_iterator(end());}
	const_reverse_iterator rbegin() const			{return const_reverse_iterator(end());}
	reverse_iterator       rend()					{return reverse_iterator(begin());}
	const_reverse_iterator rend() const				{return const_reverse_iterator(begin());}

	size_type 	size() const						{return fArray.size();}
	size_type 	max_size() const					{return fArray.max_size();}
	size_type 	capacity() const					{return fArray.capacity();}
	bool16      empty() const						{return fArray.empty();}

	allocator_type get_allocator() const			{return fArray.get_allocator();}

	void 		assign(size_type count, const T& v) {fArray.assign((Inherited::size_type)count, v);}

	template <class InputIter>
	void		assign(InputIter first, InputIter last) { fArray.assign(first, last); }

	reference       operator[](size_type i)			{return reference(fArray.operator[]((Inherited::size_type)i));}
	const_reference operator[](size_type i) const 	{return const_reference(fArray.operator[]((Inherited::size_type)i));}
	reference       at(size_type i)					{return reference(fArray.at((Inherited::size_type)i));}
	const_reference at(size_type i) const			{return const_reference(fArray.at((Inherited::size_type)i));}
	reference       front()							{return reference(fArray.front());}
	const_reference front() const					{return const_reference(fArray.front());}
	reference       back()							{return reference(fArray.back());}
	const_reference back() const					{return const_reference(fArray.back());}

	void 		push_back(const T& x)					{fArray.push_back((const void*)x);}
	void 		pop_back()								{fArray.pop_back();}
	iterator 	insert(iterator position, const T& x)	{return iterator(fArray.insert(Inherited::iterator(position), (const void*)x));}
	void     	insert(iterator position, size_type n, const T& x) 					{fArray.insert(Inherited::iterator(position), (Inherited::size_type)n, (const void*)x);}
	template <class InputIter>
	void		insert(iterator pos, InputIter first, InputIter last)
				{
					fArray.insert(Inherited::iterator(pos), first, last);
				}


	iterator 	erase(iterator position) 				{return iterator(fArray.erase(Inherited::iterator(position)));}
	iterator 	erase(iterator first, iterator last) 	{return iterator(fArray.erase(Inherited::iterator(first), Inherited::iterator(last)));}
	void     	swap(K2PtrVectorBase& rhs) noexcept 				{fArray.swap(rhs.fArray);}
	void     	clear()									{fArray.clear();}
	//void      resize(size_type sz);
	void      	resize(size_type sz, const T& value){fArray.resize((Inherited::size_type)sz, value);}
	void		reserve(size_type sz)					{fArray.reserve((Inherited::size_type)sz);}

	void initialize(size_type , const T& ) {}
	void fill_assign(size_type, const T&) {}
	void fill_insert(iterator, size_type, const T&){}
	void CopyConstructHelper(const K2PtrVectorBase&) {}
protected:
	void 		DoCleanup()								{}
	size_type 	DoGetCapacity(size_type)				{return 0;}
	void 		DoReset(pointer, size_type, size_type)	{}
				// Need these for ForceInstantiation.

private:
	Inherited	fArray;
};

template <typename T>
inline bool16 operator==(const K2PtrVectorBase<T>& lhs, const K2PtrVectorBase<T>& rhs)	{return lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin());}

template <typename T>
inline bool16 operator!=(const K2PtrVectorBase<T>& lhs, const K2PtrVectorBase<T>& rhs)	{return !(lhs == rhs);}

template <typename T>
inline bool16 operator< (const K2PtrVectorBase<T>& lhs, const K2PtrVectorBase<T>& rhs)	{return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());}

template <typename T>
inline bool16 operator> (const K2PtrVectorBase<T>& lhs, const K2PtrVectorBase<T>& rhs)	{return rhs < lhs;}

template <typename T>
inline bool16 operator>=(const K2PtrVectorBase<T>& lhs, const K2PtrVectorBase<T>& rhs)	{return !(lhs < rhs);}

template <typename T>
inline bool16 operator<=(const K2PtrVectorBase<T>& lhs, const K2PtrVectorBase<T>& rhs)	{return !(rhs < lhs);}

template <class T/*, class Allocator*/>
inline void swap(K2PtrVectorBase<T/*, Allocator*/>& x, K2PtrVectorBase<T/*, Allocator*/>& y) noexcept
{
	x.swap(y);
}
}	// namespace K2Internals

#endif // __K2PtrVectorBase__
