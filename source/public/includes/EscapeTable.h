//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/EscapeTable.h $
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
#ifndef __EscapeTable__
#define __EscapeTable__

#include "AnsiBasedTypes.h"
#include <memory>
#include <string>
#include <map>
#include "K2Assert.h"
#include <boost/range/iterator_range.hpp>
#include <boost/range/as_literal.hpp>

// Defines the escaped character and the replacement escape sequence
template<typename T, typename U>
struct EscapePair
{
	// A character range reference is merely a boost::iterato_range of simple pointers 
	typedef typename boost::iterator_range<U const*> char_range_ref;
	
	T ch;						// char to be escaped
	char_range_ref escapeSeq;	// Escape sequence
};

/**
 Selects one of two types based upon a boolean constant
 Usage: SelectType<flag, T, U>::Result
 flag has to be a compile-time boolean constant
 Result evaluates to T if flag is true, and to U otherwise.
*/

template <bool flag, typename T, typename U>
struct SelectType
{
    typedef T Result;
};
template <typename T, typename U>
struct SelectType<false, T, U>
{
    typedef U Result;
};


//
// Wrapper over a C-array of EscapePairs
//
// WARNING: this class does NOT copy the data passed in the constructor.
// It is rather a wrapper over a C-array of EscapePairs.
// The array that is passed in the constructor has to be valid for the lifetime of this object.
//
// All escape sequences must start with the same escape char AND they must either be the same length
// or they should have the same ending escape char.
//
// T is the character type for the character to be escaped
// U is the character type of the escape sequence
//
// The escape tables can come in two flavors:
//  - all escape sequences have the same start escape marker and fixed length (the end escape marker doesn't exist)
//  - all escape sequences have the same pair of start and end markers and they can be of different lengths.
//

// EscapeTable is usually a shared const variable. 
// However, initialization of the members can lead to undesirable 
// race conditions unless synchronization is implemented. 
#pragma export on
PUBLIC_DECL	void* AcquireEscapeTableLock();
PUBLIC_DECL	void ReleaseEscapeTableLock(void* lock);
#pragma export off
template<typename T, typename U>
class EscapeTable
{
	// This class is not copyable
    EscapeTable(const EscapeTable &);
    EscapeTable& operator=(const EscapeTable &);


public:
	typedef size_t					size_type;
	typedef EscapePair<T, U>		value_type;
	typedef EscapePair<T, U>&		reference;
	typedef EscapePair<T, U> const&	const_reference;
//	typedef std::map<T, std::basic_string<U> > EscapeMap;
//	typedef std::map<std::basic_string<U>, T> UnescapeMap;
	// Determine which char type is larger
	typedef typename SelectType<(sizeof(T) > sizeof(U)), T, U>::Result BigCharType;

	// Select the bigger char type as lookup key and the smaller one as the value
	// This will make it easier with the casts
	// (always better to go from char->wide char take advantage of type promotion)
	typedef BigCharType EscapeMapKey;
	typedef typename  EscapePair<T, U>::char_range_ref EscapeMapValue;

	typedef typename std::basic_string<BigCharType> UnescapeMapKey;
	typedef T UnescapeMapValue;

	typedef typename std::map<EscapeMapKey, EscapeMapValue> EscapeMap;
	typedef typename std::map<UnescapeMapKey, UnescapeMapValue> UnescapeMap;

	/** Constructor - initializes the escape table with an array of escape pairs
	    All the escape sequences must start with the same escape marker and they should be the same length (since the end escape marker is not defined)
	*/
	EscapeTable( EscapePair<T, U> escapes[], size_type count )
		: array_(escapes), size_(count), endEscapeMarker_(U())
	{
		// Alias for easier reading
		EscapeMapValue const& escapeSequence( array_[0].escapeSeq );
		ASSERT( !escapeSequence.empty() );
		
		// Save the start escape marker (all start escape markers should be the same)
		startEscapeMarker_ = escapeSequence.front();
		
		ASSERT( IsValid() );
	}

	/** Constructor - initializes the escape table with an array of escape pairs.
	    All the escape sequences must be delimited by the same pair of escape markers.
	    The escape sequences might be different in length since we have both delimiters in this case.
	*/
	EscapeTable( EscapePair<T, U> escapes[], size_type count, U startEscapeMarker, U endEscapeMarker )
		: array_(escapes), size_(count), startEscapeMarker_(startEscapeMarker), endEscapeMarker_(endEscapeMarker)
	{
		// The end marker can not be the nil character
		ASSERT( endEscapeMarker_ != U() );
		ASSERT( IsValid() );
	}

	bool16 IsValidEscapeSequence( const EscapeMapValue& escapeSequence ) const
	{
		ASSERT( !escapeSequence.empty() );
		// All escape sequences must start with the same escape char
		// AND they either must be the same length or they should have the same ending escape char

		if ( endEscapeMarker_ != U() )
		{
			return (escapeSequence.front() == startEscapeMarker_ && escapeSequence.back() == endEscapeMarker_);
		}
		
		// Must have the same length
		return ( escapeSequence.front() == startEscapeMarker_ && escapeSequence.size() == array_[0].escapeSeq.size() );
	}

	// Checks if this table is valid
	bool16 IsValid() const
	{
		ASSERT( size() );
		bool16 result( true );

		size_type i( 0 );
		for (; i < size() && result; ++i )
		{
			// all escape sequences must start with the same escape char
			// AND they either must be the same length or they should have the same ending escape char
			result = IsValidEscapeSequence(array_[i].escapeSeq);
		}
		return result;
	}

	// read-only access for an EscapePair at the specified index
	const_reference operator[]( size_type index ) const
	{
		return array_[index];
	}

	// number of elements in the array
	size_type size() const
	{
		return size_;
	}

	EscapeMap const& GetEscapeMap() const
	{
		if (!escapeMap_.get() )
		{
			void* lock = AcquireEscapeTableLock();
			if ( !escapeMap_.get() )
				escapeMap_.reset( CreateEscapeMap());
			ReleaseEscapeTableLock(lock);
		}
		return *escapeMap_;
	}

	UnescapeMap const& GetUnescapeMap() const
	{
		if ( !unescapeMap_.get() )
		{
			void* lock = AcquireEscapeTableLock();
			if ( !unescapeMap_.get() )
			{
				unescapeMap_.reset( CreateUnescapeMap());
			}
			ReleaseEscapeTableLock(lock);
		}
		return *unescapeMap_;
	}
	

private:

	EscapeMap* CreateEscapeMap( ) const
	{
		ASSERT( IsValid() );
		
		bool16 result(true);
		EscapeMap* escapeMap = new EscapeMap;
		size_type i(0);
		for (; i < size() && result; ++i )
		{
			result = escapeMap->insert(
				std::make_pair(array_[i].ch, array_[i].escapeSeq) ).second;
			ASSERT_MSG( result, "CreateEscapeMap failed to insert escape seq! Check for duplicates!" );
		}

		if (!result)
		{
			delete escapeMap;
			escapeMap = nil; 
		}
		return escapeMap;
	}

	UnescapeMap* CreateUnescapeMap( ) const
	{
		ASSERT( IsValid() );
		UnescapeMap* unescapeMap = new UnescapeMap;

		bool16 result(true);
		size_type i(0);
		for (; i < size() && result; ++i )
		{
			UnescapeMapKey key(array_[i].escapeSeq.begin(), array_[i].escapeSeq.end());

			result = unescapeMap->insert(
				std::make_pair(key, array_[i].ch) ).second;
			ASSERT_MSG( result, "CreateUnescapeMap failed to insert unescape seq! Check for duplicates!" );
		}

		if ( !result )
		{
			delete unescapeMap;
			unescapeMap = nil;
		}
		return unescapeMap;
	}

	// Data
	EscapePair<T, U> const* array_;
	size_type size_;
	U						startEscapeMarker_;
	U						endEscapeMarker_;
	
	mutable std::auto_ptr<EscapeMap> escapeMap_;
	mutable std::auto_ptr<UnescapeMap> unescapeMap_;
};

#endif // __EscapeTable__ //
