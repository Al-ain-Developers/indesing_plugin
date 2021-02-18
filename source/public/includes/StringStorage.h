//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/StringStorage.h $
//  
//  Owner: EricM
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
#ifndef __STRINGSTORAGE__
#define __STRINGSTORAGE__

#include "BaseType.h"
#include "IDThreading.h"

const int32 kStringStorageChunk = 32;

// Given a requested length (newLength) & currentLength return a padded new size for the buffer.
// Performance optimization.
// Increase the size of the string by 50% Performance measurements have shown that in the case
// of large strings we pay a large penalty in the extra calls to memcpys if the size is increased
// by some small chunk size like 16 or 32. For very large strings (as in XML SaveBackwards) this change
// resulted in a 50% speed up. [jshankar Aug-5-2003]
// If currentLength is zero then default value of kStringChunk is used.
inline int32 CalcStringSizeW(int32 newLength, int32 currentLength)
{
	ASSERT(newLength >= 0 && currentLength >= 0);
	ASSERT(newLength		< 128 * 1024 * 1024);
	ASSERT(currentLength	< 128 * 1024 * 1024);

	int32 myStringChunk = currentLength / 2;

	// Ensure minimum string chunk size
	if (myStringChunk  < kStringStorageChunk)
		myStringChunk  =  kStringStorageChunk;

	ASSERT(myStringChunk  > 0);
	const int32 calcLength = myStringChunk  * ((newLength + myStringChunk  -1 ) / myStringChunk);
	ASSERT(calcLength >= newLength);
	return calcLength;
}



int32 CheckTotalUnicodeSavvyStringReferences();


/** StringStorage encapsulates management of the buffer of a string. A StringStorage may be used by
multiple strings, and the shared storage makes copying strings cheaper (you can just copy the reference
to the StringStorage instead of allocating a block and doing a memcpy). The owning string must acquire
a unique reference inorder to update the StringStorage.

A StringStorage and the buffer it holds are allocated as a single block of memory. The StringStorage is
in the start of the block, and the buffer follows immediately after (the last field of the StringStorage
is the first character of the buffer).

StringStorage holds 16-bit characters and is null terminated. The buffer must be big enough for the string
and for the null character.

This class just maintains an array of textchars; all handling of Unicode surrogates, etc., must be done
in the client code.
*/
class StringStorage
{
public:
	// traits
	typedef int32	size_type;

	enum {kDefaultLength = 16};

	/**
	Factory function for creating StringStorage objects. Allocates a single block for the StringStorage and
	for the buffer, based on the initial requested size, and calls the placement new operator on StringStorage.
	The actual size of the buffer that is allocated is adjusted upward to make room for expected edits (this
	is an optimization).
	@param initialLength - The initial expected size of the string, as the number of textchars required for storing
							characters.
	@param sourceStr - The new string will be a copy of the source string. The StringStorage may be copied because
							the string the references needs a copy it owns so it can update it, or because the
							buffer needs to be enlarged.
	@return the new StringStorage that was created. The caller is responsible for calling Dispose() when it's done
							with the Storage.
	*/
	static StringStorage *CreateStringStorage(int32 initialLength = kDefaultLength, StringStorage *sourceStr = nil);

	operator const UTF16TextChar *(void) const;
	UTF16TextChar operator[](int pos) const;

	/** Call this before making changes to the buffer data. It will create a new StringStorage of the
	requested size if either this StringStorage has multiple references on it, or if it is too small.
	@param requestedSize - size in textchars of the buffer
	*/
	StringStorage * 	MakeSize(size_type requestedSize);

	/** Returns the size in textchars that has been allocated for the string buffer.
	*/
	size_type 				capacity() const;

	/** GetBuffer returns a pointer to the start of the character storage. The caller MUST make sure
	that it holds the only reference on the storage first, and that it has requested enough storage space for
	what it needs to do (e.g., by calling MakeSize()).
	*/
	UTF16TextChar * 	GetBuffer();
	/** ConstBuffer returns a const pointer to the start of the character storage (it's a const safe
	version of GetBuffer().
	*/
	const UTF16TextChar *ConstBuffer() const;

	/** "Copies" the string storage. Really it justs increments the ref-count. Returns a pointer
	to the storage that the copy can use (always the same as this). If you wanted to turn off
	copy-on-write, you could override this function, and make it allocate a new StringStorage instead.
	Call this when you are copying from one string to another, and want to have the two strings use the
	same StringStorage.
	*/
	StringStorage *		Copy();
	/** Releases the StringStorage. Decrements the ref-count, and if the ref-count goes to zero, also
	deletes the StringStorage (since no one is using it). Call this when you are all done with the
	string storage.
	*/
	void 				Dispose();

	/** Checks if this storage is shared (ref count is greater than one).
		@return true if the string storage is not shared.
	*/
	bool IsUnique() const;


#ifdef DEBUG
	/** Asserts if the StringStorage is not in a valid state. Checks for null termination, and allocated
	memory size is greater than requested (or its zero).
	*/
	void				Validate();

	/** Return the total amount of memory used by all StringStorage objects. */
	static int32 		TotalAllocatedMemory();

	/** Return the total number of references on all StringStorage objects. */
	static int32		TotalReferences();
#endif


protected:
	/**	Constructor
	@param initialLength - The initial expected size of the string, as the number of textchars required for storing
							characters.
	@param adjustedLength - The actual size in textchars of the buffer that was allocated.
	*/
	StringStorage(int32 initialLength, size_type adjustedLength) ;

	/** Constructor - create a new StringStorage based on an existing one
	@param srcStorage - The storage we're copying from
	@param initialLength - The initial expected size of the string, as the number of textchars required for storing
							characters.
	@param adjustedLength - The actual size in textchars of the buffer that was allocated.
	*/
	StringStorage(const StringStorage &srcStorage, size_type initialLength, size_type adjustedLength);

	int32					fMemorySize;			// number of textchars allocated for the buffer
	int32					fRequestedSize;			// number of textchars required for the buffer
	size_type				fReferenceCount;		// number of strings that use this buffer
	UTF16TextChar 			fFirstCharOfBuffer[1];		// the rest continues and is allocated together in this block

private:
#ifdef DEBUG
	// In a multi-threaded environment these stats may not be updated accurately.
	// Atomic add and subtracts of these stats are required in order to have accurate values. 
	// This would put a great overhead on the performance. Hence, we are not using atomic add and
	// subtract expecting that these stats need not be accurate.
	static int32 ts_TotalReferences;
	static int32 ts_TotalAllocatedMemory;
#endif
};


inline StringStorage::operator const UTF16TextChar *(void) const
{
	return ConstBuffer();
}

inline UTF16TextChar *StringStorage::GetBuffer()
{
	ASSERT(fReferenceCount == 1);
	return fFirstCharOfBuffer;
}

inline const UTF16TextChar *StringStorage::ConstBuffer() const
{
	return fFirstCharOfBuffer;
}


inline UTF16TextChar StringStorage::operator [] (int pos) const
{
	ASSERT(fRequestedSize > 0);
	return ConstBuffer()[pos];
}


inline StringStorage * StringStorage::Copy()
{
	IDThreading::AtomicIncrement(fReferenceCount);
#ifdef DEBUG
	++ts_TotalReferences;
#endif
 	return this;
}


inline StringStorage::size_type StringStorage::capacity() const
{
	return fMemorySize - 1;
}

inline bool StringStorage::IsUnique() const
{
	return (fReferenceCount == 1);
}

#ifdef DEBUG
inline int32 StringStorage::TotalReferences()
{
	return ts_TotalReferences;
}

inline int32 StringStorage::TotalAllocatedMemory()
{
	return ts_TotalAllocatedMemory;
}
#endif


#endif // __STRINGSTORAGE__


