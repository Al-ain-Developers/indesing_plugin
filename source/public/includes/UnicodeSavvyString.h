//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/UnicodeSavvyString.h $
//  
//  Owner:
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
//  A 16-bit character string.
//  
//========================================================================================

#pragma once
#ifndef __UNICODESAVVYSTRING
#define __UNICODESAVVYSTRING

#include "PlatformChar.h"
#include <cstddef>
#include <iterator> // for iterator_traits
#include <boost/static_assert.hpp>
#include <adobe/move.hpp>

PUBLIC_DECL int32 CharOffsetToUTF16Offset(const UTF16TextChar *buffer, int32 length, int32 charOffset);
PUBLIC_DECL int UTF16TextCharCompare(const UTF16TextChar *utf16str1, const UTF16TextChar *utf16str2);
PUBLIC_DECL size_t UTF16TextCharLength(const UTF16TextChar *utf16str);

//class StringStorage;
// We can't debug the StringStorage if we use a forward declare (bug in MSDev Studio 2003)
// This bug is fixed in MS Dev Studio 2005, so we should go back to a forward declare than.
#include "StringStorage.h"

/** This is a base class that handles UTF16 code values. It is really important that
	the users of this class understand the distinction between a code value and a code point.
	A code point (or a Unicode character) can be stored as one or more code values.
	In the UTF16 encoding you can have one or two code values for each code point.
	When a character has two code values, those are called surrogates.
	Most of the functions of this class work on code values, not code points.
*/
class UnicodeSavvyString
{
	// Copy constructor and assignment disabled
	UnicodeSavvyString(const UnicodeSavvyString& s);
	UnicodeSavvyString& operator=(const UnicodeSavvyString& s);

public:
	// traits
	typedef int32	size_type;
	typedef std::ptrdiff_t	difference_type;
	typedef UTF16TextChar code_value;
	typedef UTF32TextChar code_point;
	typedef code_value*		code_value_iterator;
	typedef code_value const*	  const_code_value_iterator;
    typedef const UnicodeSavvyString& const_reference;
    typedef UTF16TextChar value_type;

	/** Checks if the string has surrogates.
		@return true if the string has surrogate pairs.
	*/
	bool16 HasMultiWordUnicode() const
	{
		return fNumChars != fUTF16BufferLength;
	}

	/** Retrieves the number of code points stored in this string.
		The number of code points can be different from the number of code values
		if surrogates are present
		@return number of unicode code points.
	*/
	size_type CharCount() const
	{
		return fNumChars;
	}

	/** Retrieves the number of code values present in this string.
		The number of code points (characters) can be smaller than this number
		if surrogates are present.
	*/
	size_type NumUTF16TextChars() const
	{
		return fUTF16BufferLength;
	}

	/** Retrieves the number of UTF16 code values that we can fit in the string without re-allocating.
		An unicode code value is not the same with an unicode code point (unicode character).
		Beware of unicode code points that can span 2 code values (surrogates)!
		@return current capacity in code values that the string can hold.
	*/
	size_type capacity(void) const
	{
	return (UnicodeBufferIsValid()) ? fStorage->capacity() : kMaxSmallString;
	}

	/** Reserves internal memory for at least newSize UTF16 code values.
		If newCapacity is smaller than the current capacity,
		the call is taken as a nonbinding request to shrink the capacity.
		The capacity is never reduced below the current number of code values in the string
		(a call to reserve() doesn't modify the number of code values in the string).
		Each reallocation invalidates all references, pointers and iterators
		and it carries a cost so a preemptive call to reserve() is useful to increase speed
		and not invalidate references and iterators.
		@param newCapacity [IN] - the minimum capacity that the string should have.
	*/
	PUBLIC_DECL void reserve(size_type newCapacity);

	/** Changes the number of code values of *this to newSize.
		If newSize is bigger than current size, new code values initialized
		with the fill value are appended to the string.
		If fill parameter is not specified, the default constructor for code_value is used ('\0').
		If newSize is smaller, code values are removed from the end of the string.
		Calling resize(0) has the same effect as clearing the string.
		@param newSize [IN] - the new size of the string.
		@param fill [IN] - the fill value for new code values if size increases.
	*/
	PUBLIC_DECL void resize(size_type newSize, code_value fill = code_value());

	/**
		Swaps this object with another one.
		swap() should never throw.
		@doc The swap idiom is used to efficiently exchange two objects.
		It is important to declare swap for your own data structs so other classes
		can contain them and implement swap().
		Is is important to have swap() defined in your class because it allows other clients who use it as a data member
		to implement a correct assignment operator for their classes.
		@param rhs [IN/OUT] - the other object.
	*/
	friend inline void swap(UnicodeSavvyString& lhs, UnicodeSavvyString& rhs) noexcept
	{
		std::swap_ranges(lhs.fSmallStorage, lhs.fSmallStorage + kMaxSmallString + 1, rhs.fSmallStorage);
		std::swap(lhs.fStorage, rhs.fStorage);
		std::swap(lhs.fUTF16BufferLength, rhs.fUTF16BufferLength);
		std::swap(lhs.fNumChars, rhs.fNumChars);
	}

	/** Erases the string making it empty. Capacity stays the same.
		@see reserve, capacity
	*/
	PUBLIC_DECL void clear();

	/** Retrieves a pointer to a UTF16 encoded representation of the string (null terminated).
		This function is identical to c_str() of the std::string.
		@param numUTF16s [OUT, OPTIONAL] - if the pointer is not nil the function
		will set it on return  to the number of code values it contains.
		@return a pointer to a null terminated buffer of code values.
		This pointer can (and will) be different after a non-const method was called on the string.
	*/
	const UTF16TextChar* GrabUTF16Buffer(int32* numUTF16s) const;

	/** Converts a code point index to a code value index inside the string.
		@param index [IN] - zero based index of the code point.
		@return the code value index where the code point start in the UTF16 buffer.
	*/
	int32 CodePointIndexToUTF16Index(int32 index) const;

	/** Truncates the string so it contains the specified number of code points.
		@param count [IN] - the desired number of code points the string should contain.
	*/
	PUBLIC_DECL void Truncate(CharCounter count);

	/** Removes the specified number of code points starting at position.
		@param position [IN] - index of code point from where the removal should start.
		@param count [IN] - number of code points to remove.
		If the value of count is kMaxInt32 the function will remove all the code points after position.
	*/
	PUBLIC_DECL void Remove(int32 position, CharCounter count);


	/** Retrieves the unicode code point at the specified position.
		@param pos [IN] - position (in code points) where the character is.
		@return the unicode character.
	*/
	UTF32TextChar GetUTF32TextChar(int32 pos) const;


	/** Returns a const iterator for the beginning of the storage of the string.
		The iterator works only over code values and it is agnostic of code points.
	*/
    const_code_value_iterator begin() const
    {
        return ConstBuffer();
    }

	/** Returns a const iterator for the end of the storage of the string.
		The iterator works only over code values and it is agnostic of code points.
	*/
	const_code_value_iterator end() const
    {
        return ConstBuffer() + fUTF16BufferLength;
    }


protected:
	UnicodeSavvyString() : fStorage(nil), fUTF16BufferLength(0), fNumChars(0)
	{
		fSmallStorage[0] = UTF16TextChar();
	}

	/** Movable constructor - assumes ownership of the remote part
	 */
	UnicodeSavvyString(adobe::move_from<UnicodeSavvyString> other)
	:	fStorage(nil)
	{
		move_from(other.source);
	}
	
	UnicodeSavvyString(UnicodeSavvyString &&other) noexcept
		: fStorage(nil)
	{
		move_from(other);
	}

	/** Moves the data from other into this leaving other in destructible state
	 */
	void move_from(UnicodeSavvyString& other) noexcept
	{
		std::swap(fStorage, other.fStorage);
		fUTF16BufferLength = other.fUTF16BufferLength;
		fNumChars = other.fNumChars;

		if (!fStorage && fUTF16BufferLength)
			std::copy(other.fSmallStorage, other.fSmallStorage + kMaxSmallString + 1, fSmallStorage);
		else
			fSmallStorage[0] = code_value();

		other.fUTF16BufferLength = other.fNumChars = 0;
	}

	PUBLIC_DECL ~UnicodeSavvyString();

	/** Constructs the string using a range of code values [b, e).
		The code values in the range need to be UTF16 encoded.
		@param b [IN] - beginning  of the range.
		@param e [IN] - end of the range (one past last one).
		@param nCodePoints [IN, OPTIONAL] - number of code points in the range.
			This parameter can be used for optimization purposes, if the caller
			knows the number of code points represented in the range.
	*/
    template <class IteratorType>
	UnicodeSavvyString(IteratorType b, IteratorType e, size_type nCodePoints = 0)
		: fStorage(nil), fUTF16BufferLength(0), fNumChars(0)
	{
		assign(b, e, nCodePoints);
	}

	int32 CountChars() const;
	PUBLIC_DECL int32 CountCharsUtil(const UTF16TextChar* buffer, int32 bufferLength) const;

	// Buffer manipulation
	PUBLIC_DECL void InsertGap(uint32 wordWiseIndex, size_type numberOfSpaces);
	PUBLIC_DECL void RemoveGap(uint32 wordWiseIndex, size_type numberOfSpaces);

	PUBLIC_DECL void InsertUTF32TextChar(UTF32TextChar c, int32 pos = 0);
	PUBLIC_DECL void InsertUTF16String(const UTF16TextChar* buf, int32 len, int32 position = 0);

	PUBLIC_DECL void AppendUTF32TextChar(UTF32TextChar c32);

	PUBLIC_DECL void CopyFrom(const UnicodeSavvyString& other);

	/** Equality check for two strings.
		@param s [IN] - other string to compare with.
		@return kTrue if the strings are equal, kFalse otherwise.
	*/
	bool16 operator==(const UnicodeSavvyString& s) const;

#ifdef DEBUG
	PUBLIC_DECL void CheckPairedSurrogates(const UTF16TextChar* buffer, int32 utf16Count) const;

	/** Checks the invariant of this string.
	*/
	PUBLIC_DECL void InvariantCheck() const;

	/** Automatic checker of the invariant on constructor and destructor.
	*/
	struct InvariantChecker
	{
		InvariantChecker(UnicodeSavvyString const& s) : fString(s)
		{
			fString.InvariantCheck();
		}

		~InvariantChecker()
		{
			fString.InvariantCheck();
		}
	private:
		UnicodeSavvyString const& fString;
	};
#endif

	/** Assigns to the string the code values in the specified range [b, e).
		The code values in the range need to be UTF16 encoded.
		@param b [IN] - beginning  of the range.
		@param e [IN] - end of the range (one past last one).
		@param nCodePoints [IN, OPTIONAL] - number of code points in the range.
			This parameter can be used for optimization purposes, if the caller
			knows the number of code points represented in the range.
	*/
    template <class IteratorType>
	UnicodeSavvyString& assign(IteratorType b, IteratorType e, size_type nCodePoints = 0);

	/** Replaces the code values in range [pos, pos + n1) with n2 code values from  the C-array s.
		WARNING: This function operates on CODE VALUES only. It doesn't know anything about surrogate pairs.
		It is the caller's responsability to make sure that the replacement leaves the string in a consistent state.
		The function grows the string if necessary to accomodate for the replacement string.
		@param pos [IN] - index of the code value from where the replacement starts.
		@param n1 [IN] - number of code values to be replaced.
		@param s [IN] - C-array of code values that will replace the existing code values in the string. Needs to have at least n2 code values in it.
		@param n2 [IN] - length of the replacement sequence.
		@return reference to this string.
	*/
	PUBLIC_DECL UnicodeSavvyString& replace(size_type pos, size_type n1,
											code_value const* s, size_type n2);

	/** Appends the code values from the C-array s at the end of the current string.
		@param s [IN] - C-array of code values that will be added to this string.
		@param nCodeValues [IN] - number of code values to be added.
		@param nCodePoints [IN, OPTIONAL] - number of code points that nCodeValues represent.
		This can be used for optimization purposes if the caller knows how many code points are added.
		@return reference to this string.
	*/
	PUBLIC_DECL UnicodeSavvyString& append(code_value const* s, size_type nCodeValues, size_type nCodePoints = 0);

protected:
	PUBLIC_DECL UTF32TextChar			surro_GetUTF32TextChar(int32 pos) const;
	const UTF16TextChar*	ConstBuffer() const
	{
		return UnicodeBufferIsValid() ? fStorage->ConstBuffer() : fSmallStorage;
	}

	// Utility functions that are called under a "safe" circumstance.
	// Should not be used directly
	void insert_safe(code_value_iterator i, const_code_value_iterator sb, const_code_value_iterator se);
	void erase_safe(code_value_iterator b, code_value_iterator e);
	void replace_safe(code_value_iterator b, code_value_iterator e,
					  const_code_value_iterator sb, const_code_value_iterator se);


	template <class InputIterator>
	void assign_impl(InputIterator b, InputIterator e, size_type nCodePoints, std::input_iterator_tag);

	template <class FwdIterator>
	void assign_impl(FwdIterator b, FwdIterator e, size_type nCodePoints, std::forward_iterator_tag);

	//fStorage may have two states:
	// 1)  It is allocated and terminated with a trailing zero
	// 2)  Is is nil, and the storage has already been released
	// UnicodeBufferIsValid() distinguishes these states
	bool16				UnicodeBufferIsValid() const
	{
		return (fStorage ? true : false);
	}

	PUBLIC_DECL UTF16TextChar*		GetBufferForWriting(size_type size);

protected:
 	StringStorage*		fStorage;	// big storage

	enum {kMaxSmallString = 15}; // Threshold for the small buffer
	UTF16TextChar fSmallStorage[kMaxSmallString + 1]; // Small string optimization

	size_type			fUTF16BufferLength;	// The number of UTF16s in here
	size_type			fNumChars;			// The number of Unicode codepoints (2 surrogates == 1 char == 1 codepoint) in here
};


// Inline implementations below:

// Assign with iterators
template <class IteratorType>
inline	UnicodeSavvyString& UnicodeSavvyString::assign(IteratorType b, IteratorType e, size_type nCodePoints)
{
	// The value from the iterator should be 16 bit
	typedef typename std::iterator_traits<IteratorType>::value_type iterator_value_type;
	BOOST_STATIC_ASSERT(sizeof(iterator_value_type)*CHAR_BIT == 16);
	typedef typename std::iterator_traits<IteratorType>::iterator_category iterator_category;

#ifdef DEBUG
	InvariantChecker checkThis(*this);
#endif

	// Dispatch to the optimized version
	assign_impl(b, e, nCodePoints, iterator_category());
	return *this;
}

// Input iterators assign implementation
template <class InputIterator>
inline void UnicodeSavvyString::assign_impl(InputIterator b, InputIterator e, size_type nCodePoints, std::input_iterator_tag)
{
	UnicodeSavvyString temp;

	// Try to optimize allocations in case the client told us the number of code points.
	if (nCodePoints)
	{
		temp.reserve(nCodePoints);
	}

	std::copy(b, e, std::back_inserter(temp));
	swap(*this, temp);
}

template <class FwdIterator>
inline void UnicodeSavvyString::assign_impl(FwdIterator b, FwdIterator e, size_type nCodePoints, std::forward_iterator_tag)
{
	const difference_type nCodeValues = std::distance(b, e);
	ASSERT(nCodeValues >= 0);

	// Make room for the chars
	code_value* buffer = GetBufferForWriting(nCodeValues);

	// Copy them into the buffer
	std::copy(b, e, buffer);

	// Ensure terminating null
	buffer[nCodeValues] = code_value();

	fUTF16BufferLength = nCodeValues;

	// Calculate how many code points we will have at the end
	if (nCodePoints == 0 && nCodeValues)
	{
		fNumChars = CountCharsUtil(buffer, nCodeValues);
	}
	else
	{
		ASSERT((size_type)CountCharsUtil(buffer, nCodeValues) == nCodePoints);
		fNumChars = nCodePoints;
	}
}



inline int32 UnicodeSavvyString::CodePointIndexToUTF16Index(int32 index) const
{
	return HasMultiWordUnicode() ? CharOffsetToUTF16Offset(ConstBuffer(), fUTF16BufferLength, index) : index;
}

inline const UTF16TextChar * UnicodeSavvyString::GrabUTF16Buffer(int32* numUTF16s) const
{
	if (numUTF16s)
	{
		*numUTF16s = fUTF16BufferLength;
	}
	return ConstBuffer();
}

inline UTF32TextChar UnicodeSavvyString::GetUTF32TextChar(int32 pos) const
{
	return HasMultiWordUnicode() ? surro_GetUTF32TextChar(pos) : UTF32TextChar(ConstBuffer()[pos]);
}


inline int32 UnicodeSavvyString::CountChars() const
{
	return CountCharsUtil(ConstBuffer(), fUTF16BufferLength);
}



inline UTF16TextChar * UnicodeSavvyString::GetBufferForWriting(UnicodeSavvyString::size_type len)
{
	reserve(len);
	return fStorage ? fStorage->GetBuffer() : &fSmallStorage[0];
}









#endif

