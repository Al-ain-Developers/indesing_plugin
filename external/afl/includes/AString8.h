//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/external/afl/includes/AString8.h $
//  
//  Owner: Michael Easter
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
#ifndef __AString8__
#define __AString8__

// ----- Includes -----
#include "AFLDecl.h"
#include "AAllocator.h"
#include "ATypes.h"
#include <algorithm>

namespace adobe {
namespace afl {

class AString8Impl;

/**
 Class used to hold and manipulate a C string.
*/
class AFL_DECL AString8
{
public:
	/**
	 Default constructor.
	 Constructs an empty AString8 object.
	 */
	AString8();

	/**
	 Constructor.
	 Constructs an AString8 object from the given ASCII C string.
	 @param str	IN Null terminated C string.
				   The string's character set is assumed to be ISO Latin-1.
	 */
	AString8(ConstCString str);

	/**
	 Constructor.
	 Constructs an AString8 object from the given ASCII C string.
	 @param str	IN Null terminated C string.
				   The string's character set is assumed to be ISO Latin-1.
	 */
	AString8(ConstCString str, size_t sz);

	/**
	 Copy constructor.
	 Constructs an AString8 object that is a copy of the given string.
	 @param str	IN String to copy.
	 */
	AString8(const AString8& str);

	/**
	 Destructor.
	 Destroys the AString8 object.
	 */
	virtual ~AString8();

	/**
	 Swap function.
	 Swaps this object with the passed in object.
	 @param lhs, rhs	IN The strings to swap.
	 */
	friend void swap(AString8 &lhs, AString8& rhs) noexcept;

	/**
	 Assignment operator.
	 Assigns the given string to this string.
	 @param rhs	IN String to assign to this string.
	 @return Reference to this string.
	 */
	AString8& operator=(const AString8& rhs);

	/**
	 Copy constructor using rvalue references.
	 Constructs an AString8 object that is a copy of the given string.
	 @param rhs	IN String to copy.
	 */
	AString8(AString8&& rhs) noexcept
		: fpImpl(rhs.fpImpl)
	{
		rhs.fpImpl = nullptr;
	}

	/**
	 Assignment operator using rvalue references.
	 Assigns the given string to this string.
	 @param rhs	IN String to assign to this string.
	 @return Reference to this string.
	 */
	AString8& operator=(AString8&& rhs) noexcept;

	/**
	 Assignment operator.
	 Assigns the given ASCII C string to this string.
	 @param rhs	IN Null terminated C string to assign to this string.
	 @return Reference to this string.
	 */
	AString8& operator=(ConstCString rhs);

	/**
	 Equality operator.
	 Test whether this string is equal to the given string.
	 @param rhs	IN String to test for equality against this string.
	 @return True if this string is equal to the given string, else false.
	 */
	bool operator==(const AString8& rhs) const;

	/**
	 Equality operator.
	 Test whether this string is equal to the given wide string.
	 @param rhs	IN  Null terminated wide string to compare to this string.
	 @return True if this string is equal to the given string, else false.
	 */
	bool operator==(ConstCString rhs) const;

	/**
	 Non-equality operator.
	 Test whether this string is not equal to the given string.
	 @param rhs	IN String to test for non-equality against this string.
	 @return True if this string is not equal to the given string, else false.
	 */
	bool operator!=(const AString8& rhs) const;

	/**
	 Non-equality operator.
	 Test whether this string is not equal to the given wide string.
	 @param rhs	IN Null terminated wide string to compare to the string.
	 @return True if this string is not equal to the given string, else false.
	 */
	bool operator!=(ConstCString rhs) const;

	/**
	 Greater than operator.
	 Tests whether this string is lexicographically greater than the given string.
	 @param rhs	IN String to test against this string.
	 @return True if this string is lexicographically greater than the given string, else false.
	 */
	bool operator>(const AString8& rhs) const;

	/**
	 Greater than or equal to operator.
	 Tests whether this string is lexicographically greater than or equal to the given string.
	 @param rhs	IN String to test against this string.
	 @return True if this string is lexicographically greater than or equal to the given string,
			 else false.
	 */
	bool operator>=(const AString8& rhs) const;

	/**
	 Less than operator.
	 Tests whether this string is lexicographically less than the given string.
	 @param rhs	IN String to test against this string.
	 @return True if this string is lexicographically less than the given string, else false.
	 */
	bool operator<(const AString8& rhs) const;

	/**
	 Less than or equal to operator.
	 Tests whether this string is lexicographically less than or equal to the given string.
	 @param rhs	IN String to test against this string.
	 @return True if this string is lexicographically less than or equal to the given string,
			 else false.
	 */
	bool operator<=(const AString8& rhs) const;

	/**
	 Addition operator.
	 Appends the given string to the end of this string.
	 @param rhs	IN String to append to this string.
	 @return A string that is the result of appending the given string to this string.
	 */
	AString8 operator+(const AString8& rhs) const;

	/**
	 Addition operator.
	 Appends the given string to the end of this string.
	 @param rhs	IN String to append to this string.
	 @return Reference to this string.
	 */
	AString8& operator+=(const AString8& rhs);

	/**
	 Addition operator.
	 Appends the given wide string to the end of this string.
	 @param rhs	IN Null terminated wide string to append to this string.
	 @return A string that is the result of appending the given string to this string.
	 */
	AString8 operator+(ConstCString rhs) const;

	/**
	 Addition operator.
	 Appends the given wide string to the end of this string.
	 @param rhs	IN Null terminated wide string to append to this string.
	 @return Reference to this string.
	 */
	AString8& operator+=(ConstCString rhs);

	/**
	 Addition operator.
	 Appends the given character to the end of this string.
	 @param rhs	IN character to append to this string.
	 @return A string that is the result of appending the given character to this string.
	 */
	AString8 operator+(char rhs) const;

	/**
	 Addition operator.
	 Appends the given character to the end of this string.
	 @param rhs	IN character to append to this string.
	 @return Reference to this string.
	 */
	AString8& operator+=(char rhs);

	/**
	 Test whether the string is empty.
	 An empty string does not contain any characters.
	 @return True if the string is empty, else false.
	 */
	bool empty() const;

	/**
	 Returns the length in the string.
	 @return Number of characters in the string.
	 */
	size_t size() const;

	/**
	 Returns the length in the string.
	 @return Number of characters in the string.
	 */
	size_t length() const;

	/**
	 Erases all the characters in the string.
	 */
	void clear();

	/**
	 Reserves space in the string.
	 @param nChars	IN Number of characters to reserve in the string.
	 */
	void reserve(uint32 nChars = 0);

	/**
	 Returns the character at the specified index in the string.
	 @param idx	IN the index in the string whose character is to be returned.
	 @return Character at the specified index in the string.
	 */
	const char at(size_t idx) const;

	/**
	 Returns the string's internal null terminated string.
	 @return Constant null terminated string.\\
			 Any attempt to modify the returned string may invalidate this object.
	 */
	ConstCString c_str() const;

	/**
	 Assigns all or part of CString to this string.
	 @param inStr	IN the CString to assign to this string.
	 @param count	IN the number of characters to assign to this string.
	 @return Reference to the modified string.
	 */
	AString8 &assign(ConstCString inStr, size_t count);

	/**
	 Erases elements from string.
	 @param offset	IN the offset in the string to begin deleting from.
	 @param count	IN the number of characters to delete.
	 @return Reference to the modified string.
	 */
	AString8 &erase(size_t offset, size_t count);

	// Override new and delete operators
	void* operator new(size_t size);
	void operator delete(void* p);
	void* operator new[](size_t size);
	void operator delete[](void* p);
	void* operator new(size_t, void* p) { return p; }
	void operator delete (void*, void*) {} 

protected:
	friend class AString8Impl;
	AString8Impl* fpImpl;
};

}	// namespace afl
}	// namespace adobe

namespace adobe
{
namespace afl
{
inline void swap(AString8 &lhs, AString8 &rhs) noexcept
{
	using std::swap;
	swap(lhs.fpImpl, rhs.fpImpl);
}

inline AString8& AString8::operator=(AString8&& rhs) noexcept
{
	using std::swap;
	swap(*this, rhs);

	return *this;
}
}
}

#endif	// __AString8__
