//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/K2STLUtilities.h $
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
//  Summary: This file includes implementations of selected algorithms from STL. Normally
//  the STL versions will work fine. However K2's collection classes contain inline calls
//  to some of the algorithms. If these algorithms are exported from Public via the explicit
//  instantiations in templates_pub.cpp the tiniest change in the functions signature could
//  change the mangled name and break the old plugin.
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
#ifndef __K2STLUtilities__
#define __K2STLUtilities__

#include "K2TypeTraits.h"

#include "MetaProgramming.h"
#include "InterfaceTrackingUtils.h"

#if MACINTOSH
using std::memset;
#endif

// ===================================================================================
//	IsBaseOrOjectType
// ===================================================================================
template <class T>
inline typename PODTraits<T>::data_type IsBaseOrObjectType(const T*)
{
	typedef typename PODTraits<T>::data_type loc_data_type;
	return loc_data_type();
}


// ===================================================================================
//	K2destroy and K2construct
// ===================================================================================

// ---- __value is a keyword, when compiling with managed code. [amb]

template <class T>
inline void K2destroy(T* pointer)
{
	ASSERT(pointer != nil);
	pointer->~T ();
}

namespace K2Internals {
	template <class ForwardIterator>
		inline void destroyAux(ForwardIterator, ForwardIterator, base_type)
	{
	}

	template <class ForwardIterator>
		inline void destroyAux(ForwardIterator first, ForwardIterator last, object_type)
	{
		for(; first < last; ++first) 
			K2destroy(&*first);
	}
} //namespace K2Internals


template <class ForwardIterator>
inline void K2destroy(ForwardIterator first, ForwardIterator last)
{
	K2Internals::destroyAux(first, last, IsBaseOrObjectType(first));
}

namespace K2Internals {
	template <class _T1, class _T2>
	inline void _K2Construct(_T1* __p, const _T2& __v) {
	    new (__p) _T1(__v);
	}

	template <class _T1>
	inline void _K2Construct(_T1* __p) {
	  new (__p) _T1();
	}

} //namespace K2Internals

template <class _T1, class _T2>
inline void K2construct(_T1* __p, const _T2& __v) {
  K2Internals::_K2Construct(__p, __v);
}

template <class _T1>
inline void K2construct(_T1* __p) {
  K2Internals::_K2Construct(__p);
}

// ===================================================================================
//	K2fill and family
// ===================================================================================

template <class _ForwardIter, class _Tp>
void K2fill(_ForwardIter __first, _ForwardIter __last, const _Tp& __v) {
  for ( ; __first != __last; ++__first)
    *__first = __v;
}

template <class _OutputIter, class _Size, class _Tp>
_OutputIter K2fill_n(_OutputIter __first, _Size __n, const _Tp& __v) {
  for ( ; __n > 0; --__n, ++__first)
    *__first = __v;
  return __first;
}


// Specialization: for one-byte types we can use memset.

inline void K2fill(unsigned char* __first, unsigned char* __last,
                 const unsigned char& __c) {
  unsigned char __tmp = __c;
  memset(__first, __tmp, __last - __first);
}

inline void K2fill(signed char* __first, signed char* __last,
                 const signed char& __c) {
  signed char __tmp = __c;
  memset(__first, static_cast<unsigned char>(__tmp), __last - __first);
}

inline void K2fill(char* __first, char* __last, const char& __c) {
  char __tmp = __c;
  memset(__first, static_cast<unsigned char>(__tmp), __last - __first);
}

//


// ===================================================================================
//	K2uninitialized_fill and family
// ===================================================================================

namespace K2Internals {
// Valid if copy construction is equivalent to assignment, and if the
// destructor is trivial.
	template <class _ForwardIter, class _Tp>
	inline void
	__uninitialized_fill_aux(_ForwardIter __first, _ForwardIter __last, 
	                         const _Tp& __x, K2Meta::META_TRUE)
	{
		K2fill(__first, __last, __x);
	}

	template <class _ForwardIter, class _Tp>
	void
	__uninitialized_fill_aux(_ForwardIter __first, _ForwardIter __last, 
	                         const _Tp& __x, K2Meta::META_FALSE)
	{
		_ForwardIter __cur = __first;
		for ( ; __cur != __last; ++__cur)
			K2construct(&*__cur, __x);
	}


	// Valid if copy construction is equivalent to assignment, and if the
	//  destructor is trivial.
	template <class _ForwardIter, class _Size, class _Tp>
	inline _ForwardIter
	__uninitialized_fill_n_aux(_ForwardIter __first, _Size __n,
	                           const _Tp& __x, K2Meta::META_TRUE)
	{
		return K2fill_n(__first, __n, __x);
	}

	template <class _ForwardIter, class _Size, class _Tp>
	_ForwardIter
	__uninitialized_fill_n_aux(_ForwardIter __first, _Size __n,
	                           const _Tp& __x, K2Meta::META_FALSE)
	{
		_ForwardIter __cur = __first;
		for ( ; __n > 0; --__n, ++__cur)
			K2Internals::_K2Construct(&*__cur, __x);
		return __cur;
	}

} //namespace K2Internals

template <class _ForwardIter, class _Tp>
inline void K2uninitialized_fill(_ForwardIter __first,
                               _ForwardIter __last, 
                               const _Tp& __x)
{
	//$$$ Could do better: _ForwardIter doesn't have to be a POD ptr. Need metafunction IS_POD_ITER
	K2Internals::__uninitialized_fill_aux(__first, __last, __x, K2Meta::BOOL_TO_TYPE<K2Meta::IS_POD_PTR<_ForwardIter>::RET>::RET());
}

template <class _ForwardIter, class _Size, class _Tp>
inline _ForwardIter 
K2uninitialized_fill_n(_ForwardIter __first, _Size __n, const _Tp& __x)
{
	//$$$ Could do better: _ForwardIter doesn't have to be a POD ptr. Need metafunction IS_POD_ITER
	typedef typename K2Meta::BOOL_TO_TYPE<K2Meta::IS_POD_PTR<_ForwardIter>::RET>::RET loc_tag;
	return K2Internals::__uninitialized_fill_n_aux(__first, __n, __x,  loc_tag()
	);
}






namespace K2Internals {
	template <class InputIter, class ForwardIter>
	struct SafeCopy {
		static ForwardIter copy(InputIter first, InputIter last, ForwardIter result);
		static ForwardIter copy_backward(InputIter first, InputIter last, ForwardIter result);
		static ForwardIter uninitialized_copy(InputIter first, InputIter last, ForwardIter result);
	};

	template <class InputIter, class ForwardIter>
	struct FastCopy {
		static ForwardIter copy(InputIter first, InputIter last, ForwardIter result);
		static ForwardIter copy_backward(InputIter first, InputIter last, ForwardIter result);
		static ForwardIter uninitialized_copy(InputIter first, InputIter last, ForwardIter result);
	};

}



namespace K2Internals {
	template <class InputIter, class ForwardIter>
	inline ForwardIter SafeCopy<InputIter, ForwardIter>::copy(InputIter first, InputIter last, ForwardIter result)
	{
		for (; first != last; ++first, ++result)			// object type 
			*result = *first;
		return result;
	}


	template <class InputIter, class ForwardIter>
	inline ForwardIter SafeCopy<InputIter, ForwardIter>::copy_backward(InputIter first, InputIter last, ForwardIter result)
	{
		while (last != first)								// object type or custom iterators
			*--result = *--last;
		return result;
	}


	template <class InputIter, class ForwardIter>
	inline ForwardIter SafeCopy<InputIter, ForwardIter>::uninitialized_copy(InputIter first, InputIter last, ForwardIter result)
	{
		return std::uninitialized_copy(first, last, result);
	}


	class FastCopy_on_bad_types {			// not instantiable (private default ctor)
		FastCopy_on_bad_types() {}
	};
	
	template <class InputIter, class ForwardIter>
	inline ForwardIter FastCopy<InputIter, ForwardIter>::copy(InputIter first, InputIter last, ForwardIter result)
	{
	    using namespace K2Meta;
	    META_ASSERT<IS_PTR<InputIter>::RET 
			&& IS_PTR<ForwardIter>::RET 
			&& IS_POD_PTR<InputIter>::RET 
			&& IS_POD_PTR<ForwardIter>::RET
			&& sizeof(*first) == sizeof(*result),
			FastCopy_on_bad_types>();
		std::ptrdiff_t count = last - first;				// POD type and pointer iterators
		std::memmove((void*) result, (void*) first, count*sizeof(*first));
		return result + count;
	}
	template <class InputIter, class ForwardIter>
	inline ForwardIter FastCopy<InputIter, ForwardIter>::copy_backward(InputIter first, InputIter last, ForwardIter result)
	{
	    using namespace K2Meta;
	    META_ASSERT<IS_PTR<InputIter>::RET 
			&& IS_PTR<ForwardIter>::RET 
			&& IS_POD_PTR<InputIter>::RET 
			&& IS_POD_PTR<ForwardIter>::RET
			&& sizeof(*first) == sizeof(*result),
			FastCopy_on_bad_types>();
		std::ptrdiff_t count = last - first;						// POD type and pointer iterators
		std::memmove((void*) (result - count), (void*) first, count*sizeof(*first));
		return result - count;
	}

	template <class InputIter, class ForwardIter>
	inline ForwardIter FastCopy<InputIter, ForwardIter>::uninitialized_copy(InputIter first, InputIter last, ForwardIter result)
	{
	    using namespace K2Meta;
		META_ASSERT<IS_PTR<InputIter>::RET 
			&& IS_PTR<ForwardIter>::RET 
			&& IS_POD_PTR<InputIter>::RET 
			&& IS_POD_PTR<ForwardIter>::RET
			&& sizeof(*first) == sizeof(*result),
			FastCopy_on_bad_types>();
		std::ptrdiff_t count = last - first;				// POD type and pointer iterators
		std::memmove((void*) result, (void*) first, count*sizeof(*first));
		return result + count;
	}
}

template <class InputIter, class ForwardIter>
inline ForwardIter K2copy(InputIter first, InputIter last, ForwardIter result)
{
	    using namespace K2Meta;
		return IF<IS_PTR<InputIter>::RET 
			&& IS_PTR<ForwardIter>::RET 
			&& IS_POD_PTR<InputIter>::RET 
			&& IS_POD_PTR<ForwardIter>::RET
			&& sizeof(*first) == sizeof(*result), 
	   K2Internals::FastCopy<InputIter, ForwardIter>,
	   K2Internals::SafeCopy<InputIter, ForwardIter>
	>::RET::copy(first, last, result);
}

	

// ===================================================================================
//	K2uninitialized_copy
// ===================================================================================

template <class InputIter, class ForwardIter>
inline ForwardIter K2uninitialized_copy(InputIter first, InputIter last, ForwardIter result)
{
	    using namespace K2Meta;
		return IF<IS_PTR<InputIter>::RET 
			&& IS_PTR<ForwardIter>::RET 
			&& IS_POD_PTR<InputIter>::RET 
			&& IS_POD_PTR<ForwardIter>::RET
			&& sizeof(*first) == sizeof(*result), 
	   K2Internals::FastCopy<InputIter, ForwardIter>,
	   K2Internals::SafeCopy<InputIter, ForwardIter>
	>::RET::uninitialized_copy(first, last, result);
}


// ===================================================================================
//	K2copy_backward
// ===================================================================================


template <class InputIter, class ForwardIter>
inline ForwardIter K2copy_backward(InputIter first, InputIter last, ForwardIter result)
{
	    using namespace K2Meta;
		return IF<IS_PTR<InputIter>::RET 
			&& IS_PTR<ForwardIter>::RET 
			&& IS_POD_PTR<InputIter>::RET 
			&& IS_POD_PTR<ForwardIter>::RET
			&& sizeof(*first) == sizeof(*result), 
	   K2Internals::FastCopy<InputIter, ForwardIter>,
	   K2Internals::SafeCopy<InputIter, ForwardIter>
	>::RET::copy_backward(first, last, result);
}



// ===================================================================================
//	Shrink
//		Releases the memory consumed by the container's reserve bytes.
// ===================================================================================
template <class CONTAINER>
void Shrink(CONTAINER& c, int32 newlen)				
{
	ASSERT_MSG(newlen >= c.size(), "Shrink: newlen is too small");
	ASSERT_MSG(newlen <= c.capacity(), "Shrink: newlen is too large");

	if (newlen < c.capacity()) {
		CONTAINER temp;
		temp.reserve(newlen);
		temp.assign(c.begin(), c.begin() + c.size());
		
		c.swap(temp);			// this looks a bit odd, but it's just as efficient as the more cumbersome hand-coded version
	}
}


// ===================================================================================
//	K2EmptyMemberOpt
// 		A helper class for Nathan Myers empty member optimization. See for example 
//		<http://www.cantrip.org/emptyopt.html>. The purpose is to save 4 bytes in 
//		classes which have an empty class as a member. We use it in K2vector. The 
//		fAllocatedSize member shares space with the (empty) fAllocator member.
// ===================================================================================
template <class Base, class Member>
struct K2EmptyMemberOpt : public Base
{
	K2EmptyMemberOpt();
	K2EmptyMemberOpt(Base const & base);
	K2EmptyMemberOpt(Base const & base, Member const& member);

	Member f;
};

template <class Base, class Member>
inline K2EmptyMemberOpt<Base, Member>::K2EmptyMemberOpt() 
	: Base(Base()),
	  f(Member())
{
}

template <class Base, class Member>
inline K2EmptyMemberOpt<Base, Member>::K2EmptyMemberOpt(Base const & base) 
	: Base(base),
	  f(Member())
{
}

template <class Base, class Member>
inline K2EmptyMemberOpt<Base, Member>::K2EmptyMemberOpt(Base const & base, Member const& member) 
	: Base(base),
	  f(member)
{
}


// ===================================================================================
//	K2find
// ===================================================================================
#ifndef INTERFACEPROXIES_SUPPORTED
template <class InputIterator, class T>
inline InputIterator									// in release builds the codegen is quite a bit better when this is inline
K2find(InputIterator first, InputIterator last, const T& value)
{
	while (first != last && !(*first == value))
		++first;
	return first;
}
#else
// this should be used from main thread only. That is only what makes it thread safe.
extern PUBLIC_DECL bool16 ts_tkSupportInterfaceProxies;

template <class InputIterator, class T>
class NotPtr_K2Find
{
public:
	static InputIterator execute(InputIterator first, InputIterator last, const T& value);
};

template <class InputIterator, class T>
inline InputIterator NotPtr_K2Find<InputIterator, T>::execute(InputIterator first, InputIterator last, const T& value)
	{
		while (first != last && !(*first == value))
			++first;
		return first;
	}

template <class InputIterator, class T>
class Ptr_K2Find
{
public:
	static InputIterator execute(InputIterator first, InputIterator last, const T& value);
};

template <class InputIterator, class T>
InputIterator Ptr_K2Find<InputIterator, T>:: execute(InputIterator first, InputIterator last, const T& value)
{
	if (ts_tkSupportInterfaceProxies) {
		while (first != last && 
				(InterfaceTrackingUtils::ExtractInterfaceImplementation (*first) !=
				InterfaceTrackingUtils::ExtractInterfaceImplementation (value)))
			++first;
		return first;
	}
	return
		NotPtr_K2Find<InputIterator,T>::execute(first, last, value);
}


template <class InputIterator, class T>
inline InputIterator
K2find(InputIterator first, InputIterator last, const T& value)
{
	return K2Meta::IF<K2Meta::IS_PTR<T>::RET, 
					 Ptr_K2Find<InputIterator,T>,
					 NotPtr_K2Find<InputIterator,T> >::RET::execute(first, last, value);
}

#endif

template <typename CONTAINER, class T>
inline typename CONTAINER::iterator 
K2find(CONTAINER& c, const T& value)
{
	return K2find(c.begin(), c.end(), value);
}

template <typename CONTAINER, class T>
inline typename CONTAINER::const_iterator 
K2find(const CONTAINER& c, const T& value)
{
	return K2find(c.begin(), c.end(), value);
}

template <class InputIterator, class T>
inline bool
K2notfound(InputIterator first, InputIterator last, const T& value)
{
	return (std::find(first, last, value) == last);
}

template <typename CONTAINER, class T>
inline bool
K2notfound(const CONTAINER& c, const T& value)
{
	return (std::find(std::begin(c), std::end(c), value) == std::end(c));
}

template <class InputIterator, class T>
inline bool									
K2found(InputIterator first, InputIterator last, const T& value)
{
	return (std::find(first, last, value) != last);
}

template <typename CONTAINER, class T>
inline bool
K2found(const CONTAINER& c, const T& value)
{
	return (std::find(std::begin(c), std::end(c), value) != std::end(c));
}

#ifdef ID_DEPRECATED
// Temporarily added function K2location as an out-of-class
// replacement for deprecated K2Vector method Location.
// Only use it where actual location index was intended to
// be used. Otherwise, use K2found or K2notfound where
// existence or non-existence in container is to be checked.
// Though a large function, defining it in the header
// could help avoid clients declaring operator == for
// the type being searched for.
// Only tested for K2Vector.
template <typename CONTAINER, class T>
inline int32 K2location(const CONTAINER& c, const T& value)
{
    typename CONTAINER::const_iterator i = std::find(c.begin(), c.end(), value);
	int32 index = i != c.end() ? i - c.begin() : -1;
	return index;
}

// Temporarily added function K2length to replace K2Vector deprecated Length API and to 
// convert size_type value returned by size() API to int32.
// When we clean up the data types to replace signed int32 with actual size_type, this API should
// also be removed. It is needed currently because some existing code compares int32 value of -1
// with the value returned by Length() API, which also returns an int32 value. If the Length()
// API was replaced with size() API directly, the return type would become K2Vector's size_type, 
// which is uint32. In this case, the compiler would convert the int32 value of -1 being compared
// to the maximum possible value for uint32. 
// So a comparison like (val < k2vec.Length()) which would have succeeded for val == -1,
// would start failing if the replacement code is (val < k2vec.size()) because -1 would get converted
// to maximum possible value of uint32. To avoid this until the int32 cleanup happens across the code base,
// one would need to use static_cast<int32>(k2vec.size()).
// This function is provided as a simpler notation than repeatedly writing static_cast<int32>(k2vec.size()).
template <typename CONTAINER>
inline int32 K2length(const CONTAINER& c)
{
	return static_cast<int32>(c.size());
}

#endif //ID_DEPRECATED

#endif //__K2STLUtilities__
