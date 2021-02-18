//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/K2Vector.h $
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
#ifndef __K2Vector__
#define __K2Vector__

#include "K2VectorBase.h"
#include "K2PtrVectorBase.h"

//template <typename T, class Allocator>
//struct GENERATE_VECTOR {
//	typedef typename K2Meta::IF_IS_PTR<T, K2Internals::K2PtrVectorBase<T>, K2Internals::K2VectorBase<T, Allocator> >::RET RET;
//};

/**
	K2Vector is an implementation of STL's vector class.

	@doc
	Summary: There are three differences between K2Vector and std::vector:

	1) the K2Vector(uint32) ctor reserves space instead of resizing the array;

	2) a number of deprecated methods have been added for backward compatibility;

	and 3) K2Vector distinguishes between base types (no copy constructor needed)
	and object types (need copy constructor) - for element copying performance reasons,
	using two typedefs that you can use in the public section of your data structures:
 
	typedef object_type data_type;

	and

	typedef base_type datatype;

	Which you choose depends upon whether your struct or class includes any data member that
	itself requires construction. If so then choose object_type; otherwise choose base_type.
	If you choose base_type, this naturally means that your object has become fragile because
	somebody later might extend your class by adding data members that require construction,
	yet they might forget to change the typedef. On the other hand, if object construction is
	not required then base_type is much faster.

	So, why do we need to define our own vector class? The problem with the compiler provided
	STL implementations is that they are not interface classes and we have no control over the
	implementation. So, if an interface in Public returns a reference to a std::vector a plugin
	compiled with a different version of the compiler may experience difficulties since the
	internals of the vector may have changed.
*/
template <class T, class Allocator = K2Allocator<T> >
class K2Vector : public K2Internals::K2VectorBase<T, Allocator> {

	typedef typename K2Internals::K2VectorBase<T, Allocator> Inherited;
	typedef void (K2Vector::*Method)();

	public:
		/**
			Default constructor.
			Creates an empty vector.
		*/
		explicit 	K2Vector(/*const Allocator& a = Allocator()*/)  :  Inherited() {}

		/**
			Constructs a vector initialized with <count> copies of element <value>.
			@param count [IN] - the number of copies of the specified element.
			@param value [IN] - the element used for initialization.
		*/
					K2Vector(typename Allocator::size_type count, const T& value
						/*, const Allocator& a = Allocator()*/)
						:  Inherited(static_cast<typename Inherited::size_type>(count), value) {}
					
		/**
			Copy constructor.
			Creates a new vector as a copy of another vector of the same type (all elements are copied).
			@param rhs [IN] - the source vector to be copied.
		*/
					K2Vector(const K2Vector& rhs) = default;
					K2Vector(K2Vector&& rhs) noexcept = default;
					K2Vector &operator=(const K2Vector& rhs) = default;
					K2Vector &operator=(K2Vector&& rhs) noexcept = default;

			// MSVC 6.5 gets internal compiler errors if we try to use a default allocator parameter instead of
			//using two constructors here

		/**
			Creates a vector that is initialized with all the elements of the range [first, last).
			@param first [IN] - iterator that points to the first element in the source sequence.
			@param last [IN] - iterator that points AFTER the last element to be copied.
			@param a [IN] - allocator to be used.
		*/
					template <class InputIterator>
					K2Vector(InputIterator first, InputIterator last, const Allocator& a)
								: Inherited(first, last, a) {}

			
		/**
			Creates a vector that is initialized with all the elements of the range [first, last).
			@param first [IN] - iterator that points to the first element in the source sequence.
			@param last [IN] - iterator that points AFTER the last element to be copied.
		*/
					template <class InputIterator>
					K2Vector(InputIterator first, InputIterator last) 
						: Inherited(first, last, Allocator()) {}
    
        void         swap(K2Vector &other) noexcept
        {
            this->Inherited::swap(static_cast<Inherited &>(other));
        }

/* Documentation
	typedef T			 				value_type;
	typedef value_type* 				pointer;
	typedef const value_type* 			const_pointer;
	typedef value_type* 				iterator;
	typedef const value_type* 			const_iterator;
	typedef value_type& 				reference;
	typedef const value_type& 			const_reference;
	typedef size_t 						size_type;
	typedef ptrdiff_t 					difference_type;
  	typedef Allocator					allocator_type;
	
	typedef K2Reverse_iterator<iterator, value_type, difference_type, pointer, reference>       			reverse_iterator;
	typedef K2Reverse_iterator<const_iterator, value_type, difference_type, const_pointer, const_reference> const_reverse_iterator;


		iterator             	begin();
		const_iterator        	begin() const;
		iterator               	end();
		const_iterator         	end() const;
		reverse_iterator       	rbegin();
		const_reverse_iterator 	rbegin() const;
		reverse_iterator       	rend();
		const_reverse_iterator	rend() const;

		size_type 				size() const;
		size_type 				max_size() const;
		size_type 				capacity() const;
		bool16      			empty() const;

		allocator_type 			get_allocator() const;


		void 					assign(size_type count, const T& v);
		
		template <class InputIter>
		void					assign(InputIter first, InputIter last);
		
		reference       operator[](size_type i);
		const_reference operator[](size_type i) const;
		reference       at(size_type i);
		const_reference at(size_type i) const;
		reference       front();
		const_reference front() const;
		reference       back();
		const_reference back() const;

		void 		push_back(const T& x);
		void 		pop_back();
		iterator 	insert(iterator position, const T& x);
		void     	insert(iterator position, size_type n, const T& x);

		template <class InputIter>
		void		insert(iterator pos, InputIter first, InputIter last);

		
		iterator 	erase(iterator position);
		iterator 	erase(iterator first, iterator last);
		void     	swap(K2Vector& rhs);
		void     	clear();
		void      	resize(size_type sz, const T& value);
		void      	reserve(size_type sz, const T& value);





*/


		static Method ForceInstantiation(int n);
					// Force instantiation of all inherited outlined functions so that 
					// clients can explicitly instantiate K2Vector instead of K2VectorBase.
};


template <class U >
class K2Vector<U*, K2Allocator<U*> > : public K2Internals::K2PtrVectorBase<U*> {
	typedef typename K2Internals::K2PtrVectorBase<U*> Inherited;
		typedef void (K2Vector::*Method)();
		typedef K2Allocator<U*> Allocator;
	public:
		explicit 	K2Vector(/*const Allocator& a = Allocator()*/)  :  Inherited() {}

					K2Vector(typename Allocator::size_type count,  U*const& value
						/*, const Allocator& a = Allocator()*/)
						:  Inherited(count, value) {}
					

                    K2Vector(const K2Vector& rhs) = default;
                    K2Vector(K2Vector&& rhs) noexcept = default;
                    K2Vector &operator=(const K2Vector& rhs) = default;
                    K2Vector &operator=(K2Vector&& rhs) noexcept = default;

                    void         swap(K2Vector &other) noexcept
                    {
                        this->Inherited::swap(static_cast<Inherited &>(other));
                    }
			// MSVC 6.5 gets internal compiler errors if we try to use a default allocator parameter instead of
			//using two constructors here

					template <class InputIterator>
					K2Vector(InputIterator first, InputIterator last, const Allocator& a)
								: Inherited(first, last, a) {}

			
					template <class InputIterator>
					K2Vector(InputIterator first, InputIterator last) 
						: Inherited(first, last, Allocator()) {}
};

template <class T/*, class Allocator*/>
inline void swap(K2Vector<T/*, Allocator*/>& x, K2Vector<T/*, Allocator*/>& y) noexcept
{
	x.swap(y);
}

#ifdef _INCLUDE_TPP_IN_H_
	#include "K2Vector.tpp"
#endif //INCLUDE_TPP_IN_H_

// specialize adobe::type_info<> to avoid typeid problems across DLL boundaries
ADOBE_NAME_TYPE_1("k2vector:indesign:adobe",K2Vector<T0,K2Allocator<T0> >)
ADOBE_NAME_TYPE_2("k2vector:indesign:adobe",K2Vector<T0, T1>)


#endif	// __K2Vector__

