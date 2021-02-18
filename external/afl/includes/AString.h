//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/external/afl/includes/AString.h $
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
#ifndef __AString__
#define __AString__

// ----- Includes -----
#include "AFLDecl.h"
#include "AAllocator.h"
#include "ATypes.h"
#include "AString8.h"

namespace adobe {
namespace afl {

/**
 Returns the number of UTF16s in the given wide string.
 @param str		IN Null terminated wide string.
 @return Number of UTF16s in the string.
 */
AFL_DECL uint32 WLength(ConstWString str);

class AStringImpl;

/**
 Class used to hold and manipulate a UTF16 string.
*/
class AFL_DECL AString
{
public:
	/** Constant used to denote a character index beyond the the last character in a string. */
	static const uint32 kAtEnd = kMaxUInt32;

	/** Constant used to denote all characters to the end of a string. */
	static const uint32 kToEnd = kMaxUInt32;

	/**
	 Converts an AString to a UTF8 string.
	 @param strIn	IN AString to convert.
	 @param strOut	OUT Resulting null terminated UTF8 string.
	 */
	static void AStringToUTF8(const AString& strIn, AString8& strOut);

	/**
	 Converts a UTF8 string to an AString.
	 @param strIn	IN Null terminated UTF8 string to convert.
	 @param strOut	OUT Resulting AString object.
	 */
	static void UTF8ToAString(const AString8& strIn, AString& strOut);

	/**
	 Converts an ASCII C string to an AString.
	 @param strIn	IN Null terminated C string to convert.
					   The string's character set is assumed to be ISO Latin-1.
	 @param strOut	OUT Resulting AString object.
	 */
	static void CStringToAString(ConstCString strIn, AString& strOut);

	/**
	 Default constructor.
	 Constructs an empty AString object.
	 */
	AString();

	/**
	 Constructor.
	 Constructs an AString object from the given wide string.
	 @param str	IN Null terminated wide string.
	 */
	AString(ConstWString str);

	/**
	 Constructor.
	 Constructs an AString object from the given ASCII C string.
	 @param str	IN Null terminated C string.
				   The string's character set is assumed to be ISO Latin-1.
	 */
	AString(ConstCString str);

	/**
	 Constructor.
	 Constructs an AString object from UTF16 characters in the given buffer.
	 @param buf		IN Buffer containing UTF16 encoded characters.
					   The buffer does not need to be null-terminated.
	 @param nUTF16s	IN Number of UTF16s to get from the buffer.
	 */
	AString(const UTF16TextChar* buf, uint32 nUTF16s);

	/**
	 Copy constructor.
	 Constructs an AString object that is a copy of the given string.
	 @param str	IN String to copy.
	 */
	AString(const AString& str);

	/**
	 Destructor.
	 Destroys the AString object.
	 */
	virtual ~AString();

	/**
	 Swap function.
	 Swaps this object with the passed in object.
	 @param lhs, rhs	IN The strings to swap.
	 */
	friend void swap(AString &lhs, AString& rhs) noexcept;

	/**
	 Assignment operator.
	 Assigns the given string to this string.
	 @param rhs	IN String to assign to this string.
	 @return Reference to this string.
	 */
	AString& operator=(const AString& rhs);

	/**
	 Copy constructor using rvalue references.
	 Constructs an AString object that is a copy of the given string.
	 @param rhs	IN String to copy.
	 */
	AString(AString&& rhs) noexcept
		: fpImpl(rhs.fpImpl)
	{
		rhs.fpImpl = nullptr;
	}

	/**
	 Assignment operator using rvalue references
	 Assigns the given string to this string.
	 @param rhs	IN String to assign to this string.
	 @return Reference to this string.
	 */
	AString& operator=(AString&& rhs) noexcept;

	/**
	 Assignment operator.
	 Assigns the given wide string to this string.
	 @param rhs	IN Null terminated wide string to assign to this string.
	 @return Reference to this string.
	 */
	AString& operator=(ConstWString rhs);

	/**
	 Assignment operator.
	 Assigns the given ASCII C string to this string.
	 @param rhs	IN Null terminated C string to assign to this string.
					   The string's character set is assumed to be ISO Latin-1.
	 @return Reference to this string.
	 */
	AString& operator=(ConstCString rhs);

	/**
	 Equality operator.
	 Test whether this string is equal to the given string.
	 @param rhs	IN String to test for equality against this string.
	 @return True if this string is equal to the given string, else false.
	 */
	bool operator==(const AString& rhs) const;

	/**
	 Equality operator.
	 Test whether this string is equal to the given wide string.
	 @param rhs	IN  Null terminated wide string to compare to this string.
	 @return True if this string is equal to the given string, else false.
	 */
	bool operator==(ConstWString rhs) const;

	/**
	 Non-equality operator.
	 Test whether this string is not equal to the given string.
	 @param rhs	IN String to test for non-equality against this string.
	 @return True if this string is not equal to the given string, else false.
	 */
	bool operator!=(const AString& rhs) const;

	/**
	 Non-equality operator.
	 Test whether this string is not equal to the given wide string.
	 @param rhs	IN Null terminated wide string to compare to the string.
	 @return True if this string is not equal to the given string, else false.
	 */
	bool operator!=(ConstWString rhs) const;

	/**
	 Greater than operator.
	 Tests whether this string is lexicographically greater than the given string.
	 @param rhs	IN String to test against this string.
	 @return True if this string is lexicographically greater than the given string, else false.
	 */
	bool operator>(const AString& rhs) const;

	/**
	 Greater than or equal to operator.
	 Tests whether this string is lexicographically greater than or equal to the given string.
	 @param rhs	IN String to test against this string.
	 @return True if this string is lexicographically greater than or equal to the given string,
			 else false.
	 */
	bool operator>=(const AString& rhs) const;

	/**
	 Less than operator.
	 Tests whether this string is lexicographically less than the given string.
	 @param rhs	IN String to test against this string.
	 @return True if this string is lexicographically less than the given string, else false.
	 */
	bool operator<(const AString& rhs) const;

	/**
	 Less than or equal to operator.
	 Tests whether this string is lexicographically less than or equal to the given string.
	 @param rhs	IN String to test against this string.
	 @return True if this string is lexicographically less than or equal to the given string,
			 else false.
	 */
	bool operator<=(const AString& rhs) const;

	/**
	 Addition operator.
	 Appends the given string to the end of this string.
	 @param rhs	IN String to append to this string.
	 @return A string that is the result of appending the given string to this string.
	 */
	AString operator+(const AString& rhs) const;

	/**
	 Addition operator.
	 Appends the given string to the end of this string.
	 @param rhs	IN String to append to this string.
	 @return Reference to this string.
	 */
	AString& operator+=(const AString& rhs);

	/**
	 Addition operator.
	 Appends the given wide string to the end of this string.
	 @param rhs	IN Null terminated wide string to append to this string.
	 @return A string that is the result of appending the given string to this string.
	 */
	AString operator+(ConstWString rhs) const;

	/**
	 Addition operator.
	 Appends the given wide string to the end of this string.
	 @param rhs	IN Null terminated wide string to append to this string.
	 @return Reference to this string.
	 */
	AString& operator+=(ConstWString rhs);

	/**
	 Addition operator.
	 Appends the given UTF16 character to the end of this string.
	 @param rhs	IN UTF16 character to append to this string.
	 @return A string that is the result of appending the given character to this string.
	 */
	AString operator+(UTF16TextChar rhs) const;

	/**
	 Addition operator.
	 Appends the given UTF16 character to the end of this string.
	 @param rhs	IN UTF16 character to append to this string.
	 @return Reference to this string.
	 */
	AString& operator+=(UTF16TextChar rhs);

	/**
	 Lexicographically compares this string to the given string.
	 @param rhs	IN String to compare with this string.
	 @return 0 if this string is lexicographically equal to the given string.\\
			 1 if this string is lexicographically greater than the given string.\\
			-1 if this string is lexicographically less than the given string.
	 */
	int32 Compare(const AString& str) const;

	/**
	 Returns the number of UTF16s, not characters, the string can hold.
	 @return Number of UTF16s the string can hold.
	 */
	uint32 Capacity() const;

	/**
	 Returns the number of characters, not UTF16s, in the string.
	 @return Number of characters in the string.
	 */
	uint32 CharCount() const;

	/**
	 Returns the number of UTF16s, not characters, in the string.
	 @return Number of UTF16s in the string.
	 */
	uint32 UTF16Count() const;

	/**
	 Test whether the string is empty.
	 An empty string does not contain any characters.
	 @return True if the string is empty, else false.
	 */
	bool IsEmpty() const;

	/**
	 Erases all the characters in the string.
	 */
	void Clear();

	/**
	 Preallocates space in the string.
	 Preallocating space optimizes the behavior with repeated appends and insertions.
	 @param nUTF16s	IN Number of UTF16s to preallocate in the string.
	 */
	void Preallocate(uint32 nUTF16s);

	/**
	 Removes unused space from the string.
	 @param bMaxShrink	IN Denotes whether to remove the maximum amount of extra space.
	 */
	void Shrink(bool bMaxShrink = false);

	/**
	 Returns a wide string from this string.
	 @return Null terminated wide string.\\
			 The caller is responsible for deleting the returned string.
	 */
	WString GetWString() const;

	/**
	 Returns the string's internal null terminated wide string.
	 @return Constant null terminated wide string.\\
			 Any attempt to modify the returned wide string may invalidate this object.
	 */
	ConstWString GrabWString() const;

	/**
	 Sets the string from the given string.
	 @param str		IN String used to set this string.
	 @param nChars	IN Maximum number of characters to set from the given string.
					   kToEnd to set using the entire string.
	 @return Reference to this string.
	 */
	AString& SetString(const AString& str, uint32 nChars = kToEnd);

	/**
	 Sets the string from the given wide string.
	 @param str		IN Null terminated wide string used to set this string.
	 @param nChars	IN Maximum number of characters to set from the given string.
					   kToEnd to set using the entire string.
	 @return Reference to this string.
	 */
	AString& SetString(ConstWString str, uint32 nChars = kToEnd);

	/**
	 Sets the string from UTF16 characters in the given buffer.
	 @param buf		IN Buffer containing UTF16 encoded characters.
					   The buffer does not need to be null-terminated.
	 @param nUTF16s	IN Number of UTF16s to get from the buffer.
	 @return Reference to this string.
	 */
	AString& SetBuffer(const UTF16TextChar* buf, uint32 nUTF16s);

	/**
	 Character access operator.
	 Returns the nth character in the string.
	 This operator is equivalent to calling GetChar().
	 @param iChar	IN Zero-based index of the character to retrieve.
	 @return The character at the given index.\\
			 0 if the character index is past the end of the string.
	 */
	UTF16TextChar operator[](uint32 iChar) const
		{ return GetChar(iChar); }

	/**
	 Returns the nth character in the string.
	 @param iChar	IN Zero-based index of the character to retrieve.
	 @return The character at the given index.\\
			 0 if the character index is past the end of the string.
	 */
	UTF16TextChar GetChar(uint32 iChar) const;

	/**
	 Replaces a character in the string with the given character.
	 @param iChar	IN Zero-based index of the character in the string to replace with the
					   given character.
	 @param c		IN Character used to replace the current character.
	 @return Reference to this string.
	 */
	AString& SetChar(uint32 iChar, UTF16TextChar c);

	/**
	 Appends a string to this string.
	 @param str		IN String to append to this string.
	 @param nChars	IN Maximum number of characters to append from the given string.
					   kToEnd to append the entire string.
	 @return Reference to this string.
	 */
	AString& Append(const AString& str, uint32 nChars = kToEnd);

	/**
	 Appends a wide string to the string.
	 @param str		IN Null terminated wide string to append to the string.
	 @param nChars	IN Maximum number of characters to append from the given string.
					   kToEnd to append the entire string.
	 @return Reference to this string.
	 */
	AString& Append(ConstWString str, uint32 nChars = kToEnd);

	/**
	 Appends a UTF16 character to the string.
	 @param c	IN UTF16 character to append to the string.
	 @return Reference to this string.
	 */
	AString& Append(UTF16TextChar c);

	/**
	 Inserts a string into this string.
	 @param iChar	IN Zero-based index of the character in the string where
	 				   to insert the given string.
	 @param str		IN String to insert into this string.
	 @param nChars	IN Maximum number of characters to insert from the given string.
					   kToEnd to insert the entire string.
	 @return Reference to this string.
	 */
	AString& Insert(uint32 iChar, const AString& str, uint32 nChars = kToEnd);

	/**
	 Inserts a wide string into this string.
	 @param iChar	IN Zero-based index of the character in the string where
	 				   to insert the given string.
	 @param str		IN Null terminated wide string to insert into this string.
	 @param nChars	IN Maximum number of characters to insert from the given string.
					   kToEnd to insert the entire string.
	 @return Reference to this string.
	 */
	AString& Insert(uint32 iChar, ConstWString str, uint32 nChars = kToEnd);

	/**
	 Removes characters from the string.
	 @param iChar	IN Zero-based index of the first character to remove.
	 @param nChars	IN Maximum number of characters to remove from the string.
					   kToEnd to remove all characters after, and including, the character at the
					   given index.
	 @return Reference to this string.
	 */
	AString& Remove(uint32 iChar, uint32 nChars = kToEnd);

	/**
	 Truncates characters from the end of the string.
	 @param nChars	IN Maximum number of characters to remove from the end of the string.
	 @return Reference to this string.
	 */
	AString& Truncate(uint32 nChars);

	/**
	 Extracts a substring from the string.
	 @param iChar	IN Zero-based index of the first character to include in the substring.
	 @param nChars	IN Maximum number of characters to put in the substring.
					   kToEnd to include all characters to the end of the string.
	 @return The resulting string, or an empty string if the input parameters are invalid.
	 */
	AString Substring(uint32 iChar, uint32 nChars = kToEnd) const;

	/**
	 Returns the specified token from the string, given a string delimiter.
	 @param delimiter	IN String to use as the delimiter.
	 @param nToken		IN One-based number denoting the desired token.
	 @return The resulting string, or an empty string if the token is not found in the string.
	*/
	AString GetToken(const AString& delimiter, uint32 nToken) const;
	
	/**
	 Returns the specified token of the string, given a UT16 character delimiter.
	 @param delimiter	IN UT16 character to use as the delimiter.
	 @param nToken		IN One-based number denoting the desired token.
	 @return The resulting string, or an empty string if the token is not found in the string.
	*/
	AString GetToken(UTF16TextChar delimiter, uint32 nToken) const;

	/**
	 Searches the string for the first occurrence of the given string.
	 @param keyStr	IN String to search this string for.
	 @param iChar	IN Zero-based index of the character where the search begins.
	 @return Character index of the first occurrence of the given string in this string.\\
			 kAtEnd is returned when no occurrences are found.
	 */
	uint32 IndexOf(const AString& keyStr, uint32 iChar = 0) const;

	/**
	 Searches the string for the first occurrence of the given character.
	 @param keyChar	IN Character to search this string for.
	 @param iChar	IN Zero-based index of the character where the search begins.
	 @return Character index of the first occurrence of the given character in this string.\\
			 kAtEnd is returned when no occurrences are found.
	 */
	uint32 IndexOf(UTF16TextChar keyChar, uint32 iChar = 0) const;

	/**
	 Searches the string for the first occurrence of any character that
	 belongs to the given set of characters.
	 @param charSet	IN Set of characters to search this string for.
	 @param iChar	IN Zero-based index of the character where the search begins.
	 @return Character index of the first occurrence of a character in this string that belongs to
			 the given set of characters.\\
			 kAtEnd is returned when no occurrences are found.
	 */
	uint32 IndexOfAny(const AString& charSet, uint32 iChar = 0) const;

	/**
	 Searches the string to determine if it contains the given string.
	 @param keyStr	IN String to search this string for.
	 @param iChar	IN Zero-based index of the character where the search begins.
	 @return True if this string contains the given string, else false.
	 */
	bool Contains(const AString& keyStr, uint32 iChar = 0) const
		{ return (IndexOf(keyStr, iChar) != kAtEnd); }

	/**
	 Searches the string to determine if it contains the given character.
	 @param keyChar	IN Character to search this string for.
	 @param iChar	IN Zero-based index of the character where the search begins.
	 @return True if this string contains the given string, else false.
	 */
	bool Contains(UTF16TextChar keyChar, uint32 iChar = 0) const
		{ return (IndexOf(keyChar, iChar) != kAtEnd); }

	/**
	 Searches the string to determine if it contains any character that belongs to the given set
	 of characters.
	 @param charSet	IN Set of characters to search this string for.
	 @param iChar	IN Zero-based index of the character where the search begins.
	 @return True if this string contains any character in the given set of characters, else false.
	 */
	bool ContainsAny(const AString& charSet, uint32 iChar = 0) const
		{ return (IndexOfAny(charSet, iChar) != kAtEnd); }

	// Override new and delete operators
	void* operator new(size_t size);
	void operator delete(void* p);
	void* operator new[](size_t size);
	void operator delete[](void* p);
	void* operator new(size_t, void* p) { return p; }
	void operator delete (void*, void*) {} 

protected:
	friend class AStringImpl;
	AStringImpl* fpImpl;
};

}	// namespace afl
}	// namespace adobe


namespace adobe
{
namespace afl
{
inline void swap(AString &lhs, AString &rhs) noexcept
{
	using std::swap;
	swap(lhs.fpImpl, rhs.fpImpl);
}

inline AString& AString::operator=(AString&& rhs) noexcept
{
	using std::swap;
	swap(*this, rhs);

	return *this;
}
}
}

#endif	// __AString__
