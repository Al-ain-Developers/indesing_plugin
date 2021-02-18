//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/UnspecifiableOf.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __UnspecifiableOf_h__
#define __UnspecifiableOf_h__

//========================================================================================
// TEMPLATE UnspecifiableOf
//========================================================================================

struct Unspecified { };

/** UnspecifiableOf is a template that can be used to implement optional arguments to methods
	and functions. For example, if you have a method that takes a optional int argument,
	declare the type of the argument to be UnspecifiableOf<int>. Clients of the method can
	then pass an int or kUnspecified.
*/

template <class ValueType>
class UnspecifiableOf
{
public:
	/** Constructor for unspecified case
		@param unspecified
	*/
	
	UnspecifiableOf(const Unspecified& /*unspecified*/) : fSpecified(false) { }
	
	/** Constructor for specified case
		@param value
	*/
	
	UnspecifiableOf(const ValueType& value) : fSpecified(true), fValue(value) { }
	
	/** Copy constuctor
		@param other is the object to copy
	*/
	
	UnspecifiableOf(const UnspecifiableOf& other) : fSpecified(other.fSpecified), fValue(other.fValue) { }

	/** Assignment operator
		@param other, the object to assign to this object
	*/
	
	UnspecifiableOf<ValueType>& operator=(const UnspecifiableOf<ValueType>& other)
	{
		if (this != &other)
		{
			fSpecified = other.fSpecified;
			fValue = other.fValue;
		}
		
		return *this;
	}
	
	/** IsSpecified return true if the argument was specified otherwise false
		@return whether specified
	*/
	
	bool		IsSpecified() const { return fSpecified; }
	
	/** GetValue returns the value if specified
		@return the value
	*/
	
	ValueType	GetValue() const { ASSERT(IsSpecified()); return fValue; }
	
private:
	bool			fSpecified;
	ValueType		fValue;
};

// was: extern const Unspecified kUnspecified;

#ifdef WINDOWS
// pjm - figure out what is going on here
const Unspecified kUnspecified;
#else
const Unspecified kUnspecified = {};
#endif

#endif // __UnspecifiableOf_h__
