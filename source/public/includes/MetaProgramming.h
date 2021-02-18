//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/MetaProgramming.h $
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
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __MetaProgramming__
#define __MetaProgramming__

#if WINDOWS
#pragma warning(disable: 4786)					// Long names truncated in browser
#endif

#ifdef WINDOWS
	#define HAS_PARTIAL_SPECIALIZATION	0
#else
	#define HAS_PARTIAL_SPECIALIZATION	1
#endif


namespace K2Meta {				

// ----- IF -----
struct FirstPicker {
	template <class First, class Second>
	struct Result {
		typedef First RET;
	};
};

struct SecondPicker {
	template <class First, class Second>
	struct Result {
		typedef Second RET;
	};
};

template <bool condition>
struct BoolToPicker {
	typedef SecondPicker RET;
};

template <>
struct BoolToPicker<true> {
	typedef FirstPicker RET;
};

template <bool condition, class IfType, class ElseType>	
class IF {													// $$ can simplify this quite a bit once MSVC supports partial specialization
	typedef typename BoolToPicker<condition>::RET Picker;
public:
	typedef typename Picker::template Result<IfType, ElseType>::RET RET;
};



struct META_FALSE {
	enum {RET = false};
};

struct META_TRUE {
	enum {RET = true};
};

template <bool condition>	
struct BOOL_TO_TYPE {
	typedef typename IF<condition, META_TRUE, META_FALSE>::RET RET;
};
		
// ----- META_ASSERT -----
struct ValidCode {};								// type used by code that is OK

template <bool PREDICATE, typename ERR_MESG>	// metafunction that returns a type that cannot be instantiated if the predicate is true
struct ASSERT_SELECTOR 
{
	typedef typename K2Meta::IF<PREDICATE, ValidCode, ERR_MESG>::RET RET;
};

template <bool PREDICATE, typename ERR_MESG>	// causes a compile time error if the predicate is false
void META_ASSERT()
{
	typename ASSERT_SELECTOR<PREDICATE, ERR_MESG>::RET checker;
	(void) checker;
}


// ----- IS_POD -----
// see K2TypeTraits.h	


// ----- IS_PTR -----
#if HAS_PARTIAL_SPECIALIZATION
	template <typename T>
	struct IS_PTR {
		enum { RET = false};
	};
		
	template <typename T>
	struct IS_PTR<T*> {
		enum { RET = true };
	};

	template <typename T>
	struct IS_PTR<T* const> {
		enum { RET = true };
	};

#else
	struct IsPtrConverter {							// allows IsPtr to test only ptrs not classes with conversion operators
		IsPtrConverter(const volatile void* const) {}
	};
	
	char IsPtr(IsPtrConverter);
	int IsPtr(...);
	
	template <typename T>
	struct IS_PTR {
		static T t;
		enum { RET = (sizeof(IsPtr(t)) == 1) };
	};
#endif


// ----- IF_IS_PTR -----
template <class T, class IfType, class ElseType>
struct IF_IS_PTR 
{
	typedef typename IF<IS_PTR<T>::RET, IfType, ElseType>::RET RET;
};


// ----- IS_SAME_TYPE -----
#if HAS_PARTIAL_SPECIALIZATION
	template <typename T, typename U> struct IS_SAME_TYPE 	{enum {RET = false};};
	template <typename T> struct IS_SAME_TYPE<T, T>			{enum {RET = true};};

#else
	int IsSameType(...);
	
	template <typename T>
	char IsSameType(T, T);
	
	template <typename T, typename U>
	struct IS_SAME_TYPE {
		static T t;
		static U u;
		enum {RET = (sizeof(IsSameType(t, u)) == 1)};
	};
#endif


#if 0
// Metrowerks sizeof till too buggy
#include <boost/type_traits.hpp>
// ----- IS_CONVERTIBLE -----
	// Thanks to A. Alexandrescu for the idea
	template <typename From, typename To>
	struct IS_CONVERTIBLE {	// can T be converted to U?	
		static char IsConvertible(To);
		static int IsConvertible(...);
		static From t;
		static const int RET  = sizeof(IsConvertible(t)) == 1;
	};

	// Metrowerks sizeof bug workaround
	template <typename From, typename To>
	const int IS_CONVERTIBLE<From, To>::RET = sizeof(IsConvertible(t)) == 1;

// ----- IS_ENUM -----
template <typename T> struct IS_ENUM
{
//Copyright for IS_ENUM
//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
private:
	typedef typename ::boost::add_reference<T>::type r_type;
	enum { NOT_ARITH = !(::boost::is_arithmetic<T>::value) };
	enum { NOT_REF = !(::boost::is_reference<T>::value)};
	enum { INT_CONVERT = (K2Meta::IS_CONVERTIBLE<r_type, ::boost::detail::int_convertible>::RET)};
  
public:
    enum { RET = NOT_ARITH && NOT_REF && INT_CONVERT};
};

#endif
}	// namespace K2Meta

#endif //__MetaProgramming__
