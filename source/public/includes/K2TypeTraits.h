//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/K2TypeTraits.h $
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
#ifndef __K2TypeTraits__
#define __K2TypeTraits__

#include "MetaProgramming.h"
#define BOOST_HAS_THREADS 

#include <boost/shared_ptr.hpp>

// ===================================================================================
//	PODTraits
// 		POD stands for Plain Old Data
// ===================================================================================

struct base_type  { typedef  base_type   data_type;};
struct object_type{ typedef  object_type data_type;};


template <class T>
class PODTraits { 
public:
	typedef typename K2Meta::IF<K2Meta::IS_PTR<T>::RET /*|| K2Meta::IS_ENUM<T>::RET*/, base_type, T>::RET::data_type data_type;	
};


#define DECLARE_BASE_TYPE(type) 					\
template <>											\
class PODTraits<type > { 							\
public:												\
	typedef base_type data_type;					\
}													\

#define DECLARE_OBJECT_TYPE(type) 					\
template <>											\
class PODTraits<type > { 							\
public:												\
	typedef object_type data_type;					\
}													

		
// ===================================================================================
//	Specializations for common base types
// ===================================================================================
DECLARE_BASE_TYPE(bool);
DECLARE_BASE_TYPE(char);
DECLARE_BASE_TYPE(short);
DECLARE_BASE_TYPE(int);
DECLARE_BASE_TYPE(long);
DECLARE_BASE_TYPE(unsigned char);
DECLARE_BASE_TYPE(unsigned short);
DECLARE_BASE_TYPE(unsigned int);
DECLARE_BASE_TYPE(unsigned long);
#if defined WINDOWS
DECLARE_BASE_TYPE(__int64);
DECLARE_BASE_TYPE(unsigned __int64);
#else
DECLARE_BASE_TYPE(long long);
DECLARE_BASE_TYPE(unsigned long long);
#endif
DECLARE_BASE_TYPE(float);
DECLARE_BASE_TYPE(double);
DECLARE_BASE_TYPE(long double);

DECLARE_BASE_TYPE(const void*);	

template <typename T>											\
class PODTraits<boost::shared_ptr<T>  > { 							\
public:												\
	typedef object_type data_type;					\
};												\

namespace K2Meta {				

// ----- IS_POD -----
	template <class T>
	struct IsPOD {
		enum {RET = false};
	};

	template <>
		struct IsPOD<base_type> {
		enum {RET = true};
	};

	template <class T>
	struct IS_POD {
		enum {RET = IsPOD<typename PODTraits<T>::data_type>::RET};
	};

// ----- IS_POD_PTR -----

#if HAS_PARTIAL_SPECIALIZATION
	template <typename T>
	struct IS_POD_PTR {
		enum { RET = false};
	};
		
	template <typename T>
	struct IS_POD_PTR<const T*> {
		enum { RET = K2Meta::IS_POD<T>::RET };
	};
	template <typename T>
	struct IS_POD_PTR<T*> {
		enum { RET = K2Meta::IS_POD<T>::RET };
	};


#else
	template class IF<1, int, char>; // for VC6.4

	template <class Q>
	typename IF<IS_POD<Q>::RET, int, char>::RET IsPODPtr(const Q*);
	
	char IsPODPtr(...);

	template <class Q>
		struct IS_POD_PTR { 
		static Q q;
	public:
		enum { RET = sizeof(IsPODPtr(q)) == sizeof(int) };
	};
#endif
}	// namespace K2Meta

	
	template <typename T>
	struct CONVERSION_TO_THREADLOCALSTORAGE {
		static T CONVERT(T arg) {return arg;}
	};

#endif //__K2TypeTraits__
