//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/IDThreading.h $
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
//  ADOBE CONFIDENTIAL
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
#ifndef __IDTHREADING__
#define __IDTHREADING__

#include "IDThreadingPrimitives.h"
#include "OMTypes.h"
#include "K2Assert.h"

namespace IDThreading
{
	typedef uint32 ExecutionContextID;
	extern RUNTIME_DECL const ExecutionContextID kInvalidExecutionContextID;

	/** Retrieves the ExecutionContextID for the calling thread.
		If the thread doesn't have an execution context associated with it (might be from an external library)
		this function returns kInvalidExecutionContextID.
	*/
	RUNTIME_DECL ExecutionContextID CurrentExecutionContextId ();

	/** Sets the name for the specified thread.
		Useful for debugging purposes (these names will show in the debugger).
	*/
	RUNTIME_DECL void SetThreadName(ThreadID id, const char* name);

	//****************************************************************************************

	/** To be called after threads are started, after BeginReservedThreadBottleneck(), but before
	    any usage of the model by a thread.
		This function is implicitly called for any thread in the pool used by the AsyncWorkManager.
	*/
	RUNTIME_DECL void BeginPublicThreadBottleneck ();

	/** To be called when the thread is finished using the model, before EndReservedThreadBottleneck().  
		This allows certainly cleanup to happen, such as freeing model thread local resources.
		This function is implicitly called for any thread in the pool used by the AsyncWorkManager.

	*/
	RUNTIME_DECL void EndPublicThreadBottleneck ();

	typedef uint32 PublicThreadLocalStorageKey;
	typedef uint64 PublicThreadLocalStorageValue;

	RUNTIME_DECL PublicThreadLocalStorageKey PublicThreadLocalStorageAllocKey ();
	RUNTIME_DECL  void PublicThreadLocalStorageRealeaseKey(PublicThreadLocalStorageKey key);
	RUNTIME_DECL void PublicThreadLocalStorageSet (PublicThreadLocalStorageKey key, PublicThreadLocalStorageValue value);
	RUNTIME_DECL PublicThreadLocalStorageValue PublicThreadLocalStorageGet (PublicThreadLocalStorageKey key, PublicThreadLocalStorageValue initialVal);

	typedef uint32 PublicThreadLocalSmartPointerKey;
	typedef boost::shared_ptr<void> PublicThreadLocalSmartPointerValue;


	RUNTIME_DECL PublicThreadLocalSmartPointerKey PublicThreadLocalSmartPointerAllocKey ();
	RUNTIME_DECL  void PublicThreadLocalSmartPointerRealeaseKey(PublicThreadLocalSmartPointerKey key);
	RUNTIME_DECL void PublicThreadLocalSmartPointerSet (PublicThreadLocalSmartPointerKey key, PublicThreadLocalSmartPointerValue value);
	RUNTIME_DECL PublicThreadLocalSmartPointerValue PublicThreadLocalSmartPointerGet (PublicThreadLocalSmartPointerKey key);

	/** Platform independent thread local storage (TLS).
		It is built on top of the existing TLS offered by the OS and it uses a single slot in the TLS.
		Since the OS support for TLS is very limited, this class offers some nice features,
		like unlimited number of keys (limited only by the available memory), support for initial values, value semantics for certain operations, etc.
	 */
	template<typename T>
	class ThreadLocal : boost::noncopyable
	{
	public:

		explicit ThreadLocal (const T & initialVal) : 
		fKey (PublicThreadLocalStorageAllocKey ()), 
		fInitialVal(PublicThreadLocalStorageValue(CONVERSION_TO_THREADLOCALSTORAGE<T>::CONVERT(initialVal)))
		{
		}
		
		~ThreadLocal ()
		{
			PublicThreadLocalStorageRealeaseKey(fKey);
		}

		/** Read access */
		T Get () const
		{
			return T (PublicThreadLocalStorageGet (fKey, fInitialVal));
		}

		/** Write access */
		void Set (T x)
		{
			PublicThreadLocalStorageValue value =
				(PublicThreadLocalStorageValue) (CONVERSION_TO_THREADLOCALSTORAGE<T>::CONVERT(x));
			PublicThreadLocalStorageSet (fKey, value);
		}
		
		/** Assignment */
		ThreadLocal<T>& operator=(T x)
		{
			Set(x);
			return *this;
		}

		ThreadLocal<T>& operator +=(T x)
		{
			Set(Get() + x);
			return *this;
		}
		ThreadLocal<T>& operator -=(T x)
		{
			Set(Get() - x);
			return *this;
		}
		ThreadLocal<T>& operator ++()
		{
			return operator+=(1);
		}
		ThreadLocal<T>& operator --()
		{
			return operator-=(1);
		}
	private:
		PublicThreadLocalStorageKey fKey;
		PublicThreadLocalStorageValue fInitialVal;
	};
	

	/** Similar to ThreadLocal, this class allows users to create unique instances of a variable for each thread.
		It actually uses a ThreadLocal internally and it adds the ability to automatically create the instance
		on the first access of the variable.
		All instances of ThreadLocalManagedObject associated with a thread will be destroyed when EndPublicThreadBottleneck() is called
		(when the thread finishes).
	 */
	template<typename T>
	class ThreadLocalManagedObject : boost::noncopyable
	{
	public:
		ThreadLocalManagedObject():
				fKey (PublicThreadLocalSmartPointerAllocKey ()), 
				fInitialVal(nil)
			{
			}
		ThreadLocalManagedObject(const T& intVal):
			fKey (PublicThreadLocalSmartPointerAllocKey ()), 
			fInitialVal(new T(intVal))
			{
			}

		~ThreadLocalManagedObject ()
		{
			delete fInitialVal;
			PublicThreadLocalSmartPointerRealeaseKey(fKey);
		}
		T *Get ()
		{
			return _get ();
		}

		const T *Get () const
		{
			return _get ();
		}

		const T& GetReference () const
		{
			return *_get ();
		}

		void Set (const T& val)
		{
			*_get () = val;
		}

		void Reset ()
		{
			*_get () = T();
		}
	private:
	
		T *_get () const
		{
			PublicThreadLocalSmartPointerValue value = 
				PublicThreadLocalSmartPointerGet (fKey);
			T *p =  (T*) (value.get());

			if ( p == 0)
			{
				p = fInitialVal? new T(*fInitialVal) : new T;

				value =
					(PublicThreadLocalSmartPointerValue) (p);
				PublicThreadLocalSmartPointerSet (fKey, value);
			}
			return p;
		}

		PublicThreadLocalSmartPointerKey fKey;
		T* fInitialVal;

	};

	/** Models a fixed size array for thread local data.
	 */
	template<typename T>
	class ThreadLocalManagedArray : boost::noncopyable
	{
	public:
		ThreadLocalManagedArray(size_t __size):
		fKey (PublicThreadLocalSmartPointerAllocKey ()), 
		fSize(__size)
		{
		}

		~ThreadLocalManagedArray()
		{
			PublicThreadLocalSmartPointerRealeaseKey(fKey);
		}

		T *Get ()
		{
			return _get ();
		}

		const T *Get () const
		{
			return _get ();
		}


		T *begin ()
		{
			return _get ();
		}

		const T *begin () const
		{
			return _get ();
		}

		T *end ()
		{
			return _get () + fSize;
		}

		const T *end () const
		{
			return _get () + fSize;
		}

		size_t  size () const
		{
			return fSize;
		}

	private:
  		T *_get () const
   		{
			PublicThreadLocalSmartPointerValue value = 
				PublicThreadLocalSmartPointerGet (fKey);
 			std::vector<T> *p =  (std::vector<T> *) (value.get());
  
   			if (p == 0)
   			{
   				p = new std::vector<T>(fSize);
				value =
					(PublicThreadLocalSmartPointerValue) (p);
				PublicThreadLocalSmartPointerSet (fKey, value);
   			}
   
			return &(*p)[0];
   		}
   
		const size_t fSize;
		PublicThreadLocalSmartPointerKey fKey;
 
	};

	// private testing use only
	RUNTIME_DECL void TestHook ();

	/** Global comparison operators for ThreadLocal for syntactic convenience */

	template<typename T>
	inline bool operator<(ThreadLocal<T> const& left, ThreadLocal<T> const& right)
	{
		return left.Get() < right.Get();
	}

	template<typename T>
	inline bool operator==(ThreadLocal<T> const& left, ThreadLocal<T> const& right)
	{
		return left.Get() == right.Get();
	}

	template<typename T>
	inline bool operator<(ThreadLocal<T> const& left, T right)
	{
		return left.Get() < right;
	}

	template<typename T>
	inline bool operator<(T left, ThreadLocal<T> const& right)
	{
		return left < right.Get();
	}

	template<typename T>
	inline bool operator==(ThreadLocal<T> const& left, T right)
	{
		return left.Get() == right;
	}

	template<typename T>
	inline bool operator==(T left, ThreadLocal<T> const& right)
	{
		return left == right.Get();
	}

	template<typename T>
	inline bool operator!=(ThreadLocal<T> const& left, T right)
	{
		return left.Get() != right;
	}

	template<typename T>
	inline bool operator!=(T left, ThreadLocal<T> const& right)
	{
		return left != right.Get();
	}

	/**
	 Halt the current thread of execution of the specified number of 
	 milliseconds
	 */
	RUNTIME_DECL void Sleep( uint32 milliseconds );
	
	
	/** This section provides synchronization constructs compatible with the ones in the upcoming C++0x standard */
	
	struct adopt_lock_t {};
	extern const adopt_lock_t adopt_lock;

	/**  A lock_guard is an object that controls the ownership of an existing mutex object within a scope.
	     It maintains ownership of the mutex object throughout the lock_guard object's lifetime.
		 It does not manage the lifetime of the mutex it references.
		 The behavior of a program is undefined if the mutex referenced by the lock_guard does not exist for the entire lifetime of the lock_guard object.
	 */
	template <class Mutex>
	class lock_guard
	{
	public:
		/** Acquires ownership of the specified mutex by calling mx.lock().
			PRECONDITION: if Mutex is not a recursive mutex, the calling thread does not own the mutex mx.
		 */
		explicit lock_guard(Mutex& mx)
		: fMutex(mx), fLocked(false)
		{
			lock();
		}

		/** Adopts ownership of the mutex mx without calling lock().
			PRECONDITION: the calling thread owns the mutex mx.
		 */
		lock_guard(Mutex& mx, adopt_lock_t)
		: fMutex(mx), fLocked(true)
		{
		}
		
		/** Releases the ownership of the mutex by calling mx.unlock().
			PRECONDITION: The calling thread must own the mutex.
		 */
		~lock_guard()
		{
			if (fLocked)
				unlock();
		}

	private:

		// This class is not copyable
		lock_guard(const lock_guard&);
		lock_guard& operator=(const lock_guard&);
		
		/** Locks the mutex. If Mutex is not a recursive mutex, the calling thread should not own the mutex. */
		void lock()
		{
			ASSERT_MSG (!fLocked, "lock_guard::lock called on an already owned mutex!");
			fMutex.lock();
			fLocked = true;
		}

		/** Unlocks the mutex. The mutex must be locked. */
		void unlock()
		{
			ASSERT_MSG (fLocked, "lock_guard::unlock called on a mutex we don't own!");
			fMutex.unlock();
			fLocked = false;
		}
		
		/** Returns true if this lock object has ownership of the mutex, false otherwise. */
		bool is_locked() const {	return fLocked;	}

		Mutex& fMutex;
		bool fLocked;
	};

	/** spin_mutex is the fastest mutex. It occupies a single byte and it is non-recursive.
	 It should be used only for locking *short* critical sections (less than 20 CPU instructions).
	 This type of mutex is not fair and does not scale well under contention.
	 */
	class spin_mutex
	{
	public:
		spin_mutex() : fIsLocked(0)
		{}

		/** Blocks the current thread until ownership of the mutex can be obtained for the calling thread.
			PRECONDITION: the calling thread must not already have ownership of this mutex object.
		 */
		RUNTIME_DECL void lock();
		
		/** Attempts to obtain the ownership of the mutex for the calling thread without blocking.
		 If ownership is not obtained, there is no effect and try_lock immediately returns false.
		 If the ownership is obtained the call will return true.
		 */
		RUNTIME_DECL bool try_lock();
		
		/** Releases the calling thread's ownership of the mutex.
		    PRECONDITION: The calling thread must own this mutex, otherwise behavior is undefined.
		 */
		RUNTIME_DECL void unlock();	
		
	private:
		// This class is not copyable
		spin_mutex(const spin_mutex&);
		spin_mutex& operator=(const spin_mutex&);
		
		unsigned char fIsLocked;
	};
	
} //IDThreading
#endif // __IDTHREADING__
