//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/K2Stack.h $
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
//  This is an STL style stack (adaptor) based on K2Vector
//  
//========================================================================================

#pragma once
#ifndef __K2STACK__
#define __K2STACK__

#include "K2Vector.h"

namespace K2 {

template <class T, class _C>
class stack;

template <class T, class _C >
bool16 operator==(const stack<T, _C>& lhs, const stack<T, _C>& rhs);

template <class T, class _C >
bool16 operator!= (const stack<T, _C>& lhs, const stack<T, _C>& rhs);

template <class T, class _C >
bool16 operator< (const stack<T, _C>& lhs, const stack<T, _C>& rhs);

template <class T, class _C >
bool16 operator<= (const stack<T, _C>& lhs, const stack<T, _C>& rhs);

template <class T, class _C >
bool16 operator> (const stack<T, _C>& lhs, const stack<T, _C>& rhs);

template <class T, class _C >
bool16 operator>= (const stack<T, _C>& lhs, const stack<T, _C>& rhs);

/**
	This is an STL style stack (adaptor) based on K2Vector.
*/
template <class T, class _C = K2Vector<T> >
class stack
{
public:
	typedef typename _C::value_type value_type;
	typedef typename _C::size_type size_type;
	typedef _C container_type;

	explicit stack(const _C& x = _C()) : c(x) {}

	/**
		Tests if the stack is empty.
		@return kTrue if the stack is empty, kFalse otherwise.
	*/
	bool16 empty() const { return c.empty(); }

	/**
		Gets the size of the stack (number of elements).
		@return number of elements in the stack.
	*/
	size_type size() const { return c.size(); }

	/**
		Gets the element at the top of the stack without extracting it.
		@return reference to the top element.
	*/
	value_type& top() { return c.back(); }

	/**
		Gets the element at the top of the stack.
		@return reference to the top element.
	*/
	const value_type& top() const { return c.back(); }

	/**
		Adds an element to the top of the stack.
	*/
	void push(const value_type& x) { c.push_back(x); }

	/**
		Extracts an element from the top of the stack.
	*/
	void pop() { c.pop_back(); }

	friend bool16 operator== <>(const stack<T, _C>& lhs, const stack<T, _C>& rhs);
	friend bool16 operator!= <>(const stack<T, _C>& lhs, const stack<T, _C>& rhs);
	friend bool16 operator< <>(const stack<T, _C>& lhs, const stack<T, _C>& rhs);
	friend bool16 operator<= <>(const stack<T, _C>& lhs, const stack<T, _C>& rhs);
	friend bool16 operator> <>(const stack<T, _C>& lhs, const stack<T, _C>& rhs);
	friend bool16 operator>= <>(const stack<T, _C>& lhs, const stack<T, _C>& rhs);

protected:
	_C c;
};

template <class T, class _C>
bool16 operator==(const stack<T, _C>& lhs, const stack<T, _C>& rhs)
{
	return lhs.c == rhs.c;
}

template <class T, class _C>
bool16 operator< (const stack<T, _C>& lhs, const stack<T, _C>& rhs)
{
	return lhs.c < rhs.c;
}

template <class T, class _C>
bool16 operator!=(const stack<T, _C>& lhs, const stack<T, _C>& rhs)
{
	return lhs.c != rhs.c;
}

template <class T, class _C>
bool16 operator> (const stack<T, _C>& lhs, const stack<T, _C>& rhs)
{
	return lhs.c > rhs.c;
}

template <class T, class _C>
bool16 operator>=(const stack<T, _C>& lhs, const stack<T, _C>& rhs)
{
	return lhs.c >= rhs.c;
}

template <class T, class _C>
bool16 operator<=(const stack<T, _C>& lhs, const stack<T, _C>& rhs)
{
	return lhs.c <= rhs.c;
}

} // K2 namespace


#endif

