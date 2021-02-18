//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/IDThreadingPrimitives.h $
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
//========================================================================================

#pragma once
#ifndef __IDTHREADINGPRIMITIVES__
#define __IDTHREADINGPRIMITIVES__

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/or.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits.hpp>
#include <vector>

#ifdef MACINTOSH
#include <pthread.h>
#include <libkern/OSAtomic.h>
#endif

namespace IDThreading
{
	/** ID of a thread entity.
		DO NOT CALL THIS IN APPLICATION CODE! IT SHOULD BE USED ONLY BY THE ARCHITECTURE TEAM!
		USE ExecutionContextIDs instead!
	*/
#ifdef MACINTOSH
	typedef pthread_t ThreadID;
#elif defined(WINDOWS)	
	typedef DWORD ThreadID;
#endif

	/** ID of a thread domain
		DO NOT CALL THIS IN APPLICATION CODE! IT SHOULD BE USED ONLY BY THE ARCHITECTURE TEAM!
		USE ExecutionContextIDs instead!
	*/
	typedef ThreadID ThreadDomainID;

	// Invalid thread and thread domain IDs.
	extern RUNTIME_DECL const ThreadID kInvalidThreadID;
	extern RUNTIME_DECL const ThreadDomainID kInvalidThreadDomainID;

	/** Returns the thread id of the calling entity.
		DO NOT CALL THIS IN APPLICATION CODE! IT SHOULD BE USED ONLY BY THE ARCHITECTURE TEAM!
		USE CurrentExecutionContextID() INSTEAD!
		@return the current thread id.
	*/
	RUNTIME_DECL ThreadID GetCurrentThreadId();

	/** Returns the ThreadDomainID for the calling thread.
		DO NOT CALL THIS IN APPLICATION CODE! IT SHOULD BE USED ONLY BY THE ARCHITECTURE TEAM!
		USE CurrentExecutionContextID() INSTEAD!
		A thread domain is a set of threads that never run preemptively against each other,
		but are scheduled cooperatively (as fibers on Win32 are).  Currently, each thread
		is simply its own thread domain with the exception that the original thread of
		execution and the qa thread both live in one thread domain on the Mac (on Windows
		these are two fibers within one thread).  This function is intended to be used to
		check for thread safety.
		@returns the calling thread's domain ID.
	*/
	RUNTIME_DECL ThreadDomainID GetCurrentThreadDomainId ();
	

	/** Checks if the calling thread is the one that initialized the application (the main thread),
		or is the qa thread that runs cooperatively with this thread on Mac.
		@return true if the calling entity is the main thread (or qa thread), false otherwise.
	*/
	RUNTIME_DECL bool IsMainThreadDomain();


	/** Retrieves the number of hardware cores that are enabled on this machine.
	*/
	RUNTIME_DECL uint32 GetHardwareConcurrency();

	// Discriminator for the size type for atomic operations
	template <int s>
	struct SizeType
	{
		enum { valueSize = s };
	};

	template<size_t sizeInBytes>
	struct AtomicTraits
	{
		template <typename T>
		static T Increment(T& value);

		template <typename T>
		static T Decrement(T& value);

		template<typename T>
		static T* CompareAndSwap(T*& ptr, T* newValue, T* oldValue);

		template<typename T>
		static T CompareAndSwap(T& variable, T newValue, T oldValue);		
	};
	
	/** Increments by one the specified integer as an atomic operation.
		This function generates a full memory barrier (or fence) to ensure that memory operations are completed in order.
		The memory address of value must be naturally aligned, ie 32-bit aligned
		for 32-bit operations and 64-bit aligned for 64-bit operations.
		@param value The integer to increment
		@return the new value after the operation has been performed
	*/
	template<typename T>
	typename boost::enable_if<boost::is_integral<T>, T>::type
	AtomicIncrement(T& value)
	{
		// 32 or 64 bit values
		BOOST_STATIC_ASSERT(sizeof(T) == 4 || sizeof(T) == 8);
		return AtomicTraits<sizeof(T)>::Increment(value);	
	}

	/** Decrement by one the specified integer as an atomic operation.
		This function generates a full memory barrier (or fence) to ensure that memory operations are completed in order.
		The memory address of value must be naturally aligned, ie 32-bit aligned
		for 32-bit operations and 64-bit aligned for 64-bit operations.
		@param value The integer to decrement
		@return the new value after the operation has been performed
	*/
	template<typename T>
	typename boost::enable_if<boost::is_integral<T>, T>::type
	AtomicDecrement(T& value)
	{
		// 32 or 64 bit values
		BOOST_STATIC_ASSERT(sizeof(T) == 4 || sizeof(T) == 8);
		return AtomicTraits<sizeof(T)>::Decrement(value);	
	}
	
	/** Compares the content of the variable with the oldValue and sets the variable to newValue if they are equal.
		The comparison and assignment occur as one atomic operation.
		This function generates a full memory barrier (or fence) to ensure that memory operations are completed in order.
		The memory address of variable must be naturally aligned, ie 32-bit aligned
		for 32-bit operations and 64-bit aligned for 64-bit operations.
		@param variable The variable to compare and set
		@return the old value of variable.
	*/
	template<typename T>
	typename boost::enable_if<boost::mpl::or_<boost::is_integral<T>, boost::is_pointer<T> >, T >::type
	CompareAndSwap(T& variable, T newValue, T oldValue)
	{
		// 32 or 64 bit values
		BOOST_STATIC_ASSERT(sizeof(T) == 4 || sizeof(T) == 8);
		return AtomicTraits<sizeof(T)>::CompareAndSwap(variable, newValue, oldValue);	
	}

	// Implementations for the atomic operations
	// Do not call these directly
#ifdef MACINTOSH

	template<>
	struct AtomicTraits<4>
	{
		template <typename T>
		static inline T Increment(T& value)
		{
			return ::OSAtomicIncrement32Barrier((int32_t*)(&value));
		}
		
		template <typename T>
		static inline T Decrement(T& value)
		{
			return ::OSAtomicDecrement32Barrier((int32_t*)(&value));
		}
		
		template<typename T>
		static inline T* CompareAndSwap(T*& ptr, T* newValue, T* oldValue)
		{
			BOOST_STATIC_ASSERT(sizeof(T*) == sizeof(intptr_t) && sizeof(intptr_t) == 4);
			return reinterpret_cast<T*>(intptr_t(CompareAndSwapImpl4(&ptr, reinterpret_cast<intptr_t>(newValue),  reinterpret_cast<intptr_t>(oldValue))));
		}
		
		template<typename T>
		static inline T CompareAndSwap(T& variable, T newValue, T oldValue)
		{
			return T(CompareAndSwapImpl4(&variable, newValue, oldValue));
		}
		
	private:
		RUNTIME_DECL static int32_t CompareAndSwapImpl4(volatile void* location, int32_t newValue, int32_t oldValue);
	};	

#if defined(__ppc64__) || defined(__i386__) || defined(__x86_64__)

	template<>
	struct AtomicTraits<8>
	{
		template <typename T>
		static inline T Increment(T& value)
		{
			return ::OSAtomicIncrement64Barrier((int64_t*)(&value));
		}
		
		template <typename T>
		static inline T Decrement(T& value)
		{
			return ::OSAtomicDecrement64Barrier((int64_t*)(&value));
		}
		
		template<typename T>
		static inline T* CompareAndSwap(T*& ptr, T* newValue, T* oldValue)
		{
			BOOST_STATIC_ASSERT(sizeof(T*) == sizeof(intptr_t) && sizeof(intptr_t) == 8);
			return reinterpret_cast<T*>(intptr_t(CompareAndSwapImpl8(&ptr, reinterpret_cast<intptr_t>(newValue),  reinterpret_cast<intptr_t>(oldValue))));
		}
		
		template<typename T>
		static inline T CompareAndSwap(T& variable, T newValue, T oldValue)
		{
			return T(CompareAndSwapImpl8(&variable, newValue, oldValue));
		}
		
	private:
		RUNTIME_DECL static int64_t CompareAndSwapImpl8(volatile void* location, int64_t newValue, int64_t oldValue);
	};	

#endif  // defined(__ppc64__) || defined(__i386__) || defined(__x86_64__)

#elif defined(WINDOWS)	
	
	template<>
	struct AtomicTraits<4>
	{
		template <typename T>
		static inline T Increment(T& value)
		{
			return ::InterlockedIncrement(reinterpret_cast<volatile long*>(&value));
		}
		
		template <typename T>
		static inline T Decrement(T& value)
		{
			return ::InterlockedDecrement(reinterpret_cast<volatile long*>(&value));
		}
		
		template<typename T>
		static inline T* CompareAndSwap(T*& ptr, T* newValue, T* oldValue)
		{
			BOOST_STATIC_ASSERT(sizeof(T*) == sizeof(intptr_t) && sizeof(intptr_t) == 4);
			return reinterpret_cast<T*>(intptr_t(CompareAndSwapImpl4(&ptr, reinterpret_cast<intptr_t>(newValue),  reinterpret_cast<intptr_t>(oldValue))));
		}
		
		template<typename T>
		static inline T CompareAndSwap(T& variable, T newValue, T oldValue)
		{
			return T(CompareAndSwapImpl4(&variable, newValue, oldValue));
		}
		
	private:
		RUNTIME_DECL static long CompareAndSwapImpl4(volatile void* location, long newValue, long oldValue);
	};	
	

	template<>
	struct AtomicTraits<8>
	{
		template <typename T>
		static inline T Increment(T& value)
		{
			return ::InterlockedIncrement64(reinterpret_cast<volatile long long*>(&value));
		}
		
		template <typename T>
		static inline T Decrement(T& value)
		{
			return ::InterlockedDecrement64(reinterpret_cast<volatile long long*>(&value));
		}
		
		template<typename T>
		static inline T* CompareAndSwap(T*& ptr, T* newValue, T* oldValue)
		{
			BOOST_STATIC_ASSERT(sizeof(T*) == sizeof(intptr_t) && sizeof(intptr_t) == 8);
			return reinterpret_cast<T*>(intptr_t(CompareAndSwapImpl8(&ptr, reinterpret_cast<intptr_t>(newValue),  reinterpret_cast<intptr_t>(oldValue))));
		}
		
		template<typename T>
		static inline T CompareAndSwap(T& variable, T newValue, T oldValue)
		{
			return T(CompareAndSwapImpl8(&variable, newValue, oldValue));
		}
		
	private:
		RUNTIME_DECL static long long CompareAndSwapImpl8(volatile void* location, long long newValue, long long oldValue);
	};		

#endif // defined(WINDOWS)


} //IDThreading
#endif // __IDTHREADINGPRIMITIVES__
