//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/K2SmartPtr.h $
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
//  
//  (C) Copyright Greg Colvin and Beman Dawes 1998, 1999. Permission to copy,
//  use, modify, sell and distribute this software is granted provided this
//  copyright notice appears in all copies. This software is provided "as is"
//  without express or implied warranty, and with no claim as to its
//  suitability for any purpose.
//  
//  Also based on Loki/SmartPtr.h
//  
//  The Loki Library
//  Copyright (c) 2001 by Andrei Alexandrescu
//  This code accompanies the book:
//  Alexandrescu, Andrei. "Modern C++ Design: Generic Programming and Design 
//  Patterns Applied". Copyright (c) 2001. Addison-Wesley.
//  Permission to use, copy, modify, distribute and sell this software for any 
//  purpose is hereby granted without fee, provided that the above copyright 
//  notice appear in all copies and that both that copyright notice and this 
//  permission notice appear in supporting documentation.
//  The author or Addison-Welsey Longman make no representations about the 
//  suitability of this software for any purpose. It is provided "as is" 
//  without express or implied warranty.
//  
//========================================================================================

#pragma once
#ifndef __K2SmartPtr__
#define __K2SmartPtr__

#include <boost/config.hpp>   // for broken compiler workarounds
#include <cstddef>            // for std::size_t
#include <memory>             // for std::auto_ptr
#include <algorithm>          // for std::swap
#include <boost/utility.hpp>  // for boost::noncopyable
#include <functional>         // for std::less

namespace K2 {

//  scoped_ptr  --------------------------------------------------------------//

/**
	scoped_ptr mimics a built-in pointer except that it guarantees deletion
	of the object pointed to, either on destruction of the scoped_ptr or via
	an explicit reset(). scoped_ptr is a simple solution for simple needs;
	see std::auto_ptr if your needs are more complex.
	Because scoped_ptr is simple, in its usual implementation every operation
	is as fast as for a built-in pointer and it has no more space overhead
	that a built-in pointer.
	scoped_ptr cannot be used in C++ Standard Library containers.
	Use a scoped_array if you need to manage a pointer to an array.
*/
template<typename T> class scoped_ptr : boost::noncopyable {
	typedef scoped_ptr Self;
  T* ptr;

public:
  typedef T element_type;	// The type of the stored pointer

  /**
	Constructs a scoped_ptr, storing a copy of p which MUST have been allocated
	using the operator new (or must be nil).
	@param p [IN] - pointer to the resource that will transfer the ownership to this object.
  */
  explicit scoped_ptr( T* p=0 ) : ptr(p) {}

  /**
	Destroys the object pointed by stored pointer by calling the operator delete.
  */
  ~scoped_ptr()                 { delete ptr; }

  /**
	Destroys the object pointed by the stored pointer
	and then re-assigns it to the new value.
  */
  void reset( T* p=0 )          { if ( ptr != p ) { delete ptr; ptr = p; } }

  /**
	Detaches from the stored pointer by transferring the ownership to the caller.
	Note: the signature of this method is error prone because it allows the caller
	to lose the	resource by not assign it to anything.
	@return the stored pointer.
  */
  T* release( )					{ T* ret = ptr; ptr = nil; return ret; }

  /**
	De-reference operator.
	Behavior is undefined if the stored pointer is nil.
	@returns a reference to the object pointed by the stored pointer.
  */
  T& operator*() const          { return *ptr; } 

#ifdef BOOST_MSVC
# pragma warning(push)
# pragma warning(disable:4284) // return type for 'identifier::operator->' is not a UDT or reference to a UDT. Will produce errors if applied using infix notation
#endif
  /**
	Indirection operator.
	Behavior is undefined if the stored pointer is nil.
	@returns the stored pointer.
  */
  T* operator->() const         { return ptr; }  
#ifdef BOOST_MSVC
# pragma warning(pop)
#endif  
  /**
	Gets the stored pointer.
	@return the stored pointer.
  */
  T* get() const                { return ptr; }  


    bool operator!() const // Enables "if (!sp) ..."
    { return get() == 0; }
    
    inline friend bool operator==(const Self& lhs,
        const T* rhs)
    { return lhs.get() == rhs; }
    
    inline friend bool operator==(const T* lhs,
        const Self& rhs)
    { return rhs == lhs; }
    
    inline friend bool operator!=(const Self& lhs,
        const T* rhs)
    { return !(lhs == rhs); }
    
    inline friend bool operator!=(const T* lhs,
        const Self& rhs)
    { return rhs != lhs; }

#if 0
	private:
        // Helper for enabling 'if (sp)'
        class Tester
        {
            void operator delete(void*);
        };
        
	public:
        // enable 'if (sp)'
        operator Tester*() const
        {
            if (!*this) return 0;
            static Tester t;
            return &t;
        }
#else
		operator void*() const {
			return get();
		}
#endif

  };  // scoped_ptr


//  scoped_array  ------------------------------------------------------------//

/**
	scoped_array extends scoped_ptr to arrays. Deletion of the array pointed to
	is guaranteed, either on destruction of the scoped_array or via an explicit
	reset(). See shared_array or std::vector if your needs are more complex.

	Notes:
	 - It cannot be used in C++ standard library containers.
	 - See  shared_array if scoped_array does not meet your needs.
	 - Use scoped_ptr to hold a pointer to a single object.
	 - A std::vector is an alternative to a scoped_array that is a bit heavier
	 duty but far more flexible.
*/
template<typename T> class scoped_array : boost::noncopyable {

  T* ptr;

 public:
  typedef T element_type;

  /**
	Constructs a scoped_array, storing a copy of p which MUST have been allocated
	using the operator new[] (or must be nil).
  */
  explicit scoped_array( T* p=0 ) : ptr(p) {} 

  /**
	Deletes the array pointed by the stored pointer.
	Note that a delete[] on a nil pointer is harmless.
  */
  ~scoped_array()                    { delete [] ptr; }

  /**
	Deletes the array pointed by the stored pointer
	and then re-assigns it to the new value.
  */
  void reset( T* p=0 )               { if ( ptr != p ) {delete [] ptr; ptr=p;} }

  /**
	Gets the stored pointer.
	@return the stored pointer.
  */
  T* get() const                     { return ptr; }  

  /**
	Detaches from the stored pointer by transferring the ownership to the caller.
	Note: the signature of this method is error prone because it allows the caller
	to lose the	resource by not assign it to anything.
	@return the stored pointer.
  */
  T* release( )						 { T* ret = ptr; ptr = nil; return ret; }

  /**
	Subscript operator. Returns the element at the specified position in the array.
	Behavior is undefined and almost certainly undesirable if the stored pointer is nil,
	or if i is less than 0 or is greater than or equal to the number of elements in the array.
	@param i [IN] - index in the array of the element.
	@return a reference to the element i of the array pointed by the stored pointer.
  */
  T& operator[](std::size_t i) const { return ptr[i]; }  
 };  // scoped_array

//  shared_array  ------------------------------------------------------------//

/**
	shared_array.
	The array pointed to is deleted when the last shared_array pointing to it
	is destroyed or reset.
*/
template<typename T> class shared_array {
 typedef shared_array Self; 
 public:
   typedef T element_type;
   typedef object_type data_type;

   explicit shared_array(T* p =0) : px(p) {
      pn = new long(1);  // fix: prevent leak if new throws
   }

   shared_array(const shared_array& r) : px(r.px)  
      { ++*(pn = r.pn); }

   ~shared_array() { dispose(); }

   shared_array& operator=(const shared_array& r) {
      if (pn != r.pn) { // Q: why not px != r.px? A: fails when both px == 0
          ++*r.pn;	// done before dispose() in case r.pn transitively
					// dependent on *this (bug reported by Thomas Maeder)
         dispose();
         px = r.px;
         pn = r.pn;
      }
      return *this;
   } // operator=

	/**
		Releases the currenly owned resource and aquires the new one.
		@param p [IN] - pointer to the new resource.
	*/
   void reset(T* p=0) {
      if ( px == p ) return;  // fix: self-assignment safe
      if (--*pn == 0) { delete [] px; }
      else { // allocate new reference counter
        pn = new long;   // fix: prevent leak if new throws
       } // allocate new reference counter
      *pn = 1;
      px = p;
   } // reset

   T* get() const                     { return px; }  
   T& operator[](std::size_t i) const { return px[i]; }  
 
	/**
		Retrieves the usage count for this resource.
		@return the usage count.
	*/
   long use_count() const             { return *pn; }  

   /**
		Checks if there is only one owner of this resource.
		@return true if there is only one owner, false otherwise.
   */
   bool unique() const                { return *pn == 1; }  

   /**
	Exchanges the contents of the two smart pointers.
	@param other [IN] - the second smart pointer which will exchange contents with *this.
   */
   void swap(shared_array<T>& other)  
     { std::swap(px,other.px); std::swap(pn,other.pn); }

     bool operator!() const // Enables "if (!sp) ..."
        { return get() == 0; }
        
        inline friend bool operator==(const Self& lhs,
            const T* rhs)
        { return lhs.get() == rhs; }
        
        inline friend bool operator==(const T* lhs,
            const Self& rhs)
        { return rhs == lhs; }
        
        inline friend bool operator!=(const Self& lhs,
            const T* rhs)
        { return !(lhs == rhs); }
        
        inline friend bool operator!=(const T* lhs,
            const Self& rhs)
        { return rhs != lhs; }

#if 0
	private:
        // Helper for enabling 'if (sp)'
        class Tester
        {
            void operator delete(void*);
        };
        
	public:
        // enable 'if (sp)'
        operator Tester*() const
        {
            if (!*this) return 0;
            static Tester t;
            return &t;
        }
#else
		operator void*() const {
			return get();
		}
 #endif
 	private:
   T*     px;     // contained pointer
   long*  pn;     // ptr to reference counter

   void dispose() { if (--*pn == 0) { delete [] px; delete pn; } }
  
 };  // shared_array

template<typename T>
  inline bool operator==(const shared_array<T>& a, const shared_array<T>& b)
    { return a.get() == b.get(); }

template<typename T>
  inline bool operator!=(const shared_array<T>& a, const shared_array<T>& b)
    { return a.get() != b.get(); }

} // namespace K2



//  specializations for things in namespace std  -----------------------------//

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

namespace std {

template<typename T>
  inline void swap(K2::shared_array<T>& a, K2::shared_array<T>& b)
    { a.swap(b); }

// Specialize std::less so we can use shared pointers and arrays as keys in
// associative collections.

// It's still a controversial question whether this is better than supplying
// a full range of comparison operators (<, >, <=, >=).

template<typename T>
  struct less< K2::shared_array<T> >
    : binary_function<K2::shared_array<T>, K2::shared_array<T>, bool>
  {
    bool operator()(const K2::shared_array<T>& a,
        const K2::shared_array<T>& b) const
      { return less<T*>()(a.get(),b.get()); }
  };

} // namespace std

#endif  // ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif  // __K2SmartPtr__


