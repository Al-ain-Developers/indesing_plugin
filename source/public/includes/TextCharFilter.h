//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/TextCharFilter.h $
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
#ifndef __TextCharFilter__
#define __TextCharFilter__

#include "AnsiBasedTypes.h"
#include <functional>
#include <set>

/**
	Unary predicate that filters out the specified characters.
	See bottom of the file for usage examples.
*/
class TextCharFilter : public std::unary_function<UTF32TextChar, bool>
{
public:
	typedef std::set<UTF32TextChar> CharSet;


	TextCharFilter() { }

	/**
		Initializes the filter.
		@param pFilteredChars [in]- characters to be filtered out.
		@param count [in]- number of characters in pFilteredChars.
	*/
	TextCharFilter( textchar const* pFilteredChars, size_t count )
	{
		size_t i(0);
		for (; i < count; ++i)
		{
			Add(pFilteredChars[i]);
		}
	}

	/**
		Adds a new character to the filter.
		@param ch [in]- new character to be filtered out.
		@return true if the operation succeeded.
	*/
	bool Add( textchar ch )
	{
		return fFilter.insert( ch ).second;
	}

	/**
		Removes a character from the filter.
		@param ch [in]- character to be removed from the filter.
		@return true if the operation succeeded.
	*/
	bool Remove( textchar ch )
	{
		return (fFilter.erase( ch ) != 0);
	}

	/**
		Accessor for the filter. Can be used to iterate the content of the filter.
		@return const reference to the filter's character set.
	*/
	CharSet const& GetFilter( void ) const
	{
		return fFilter;
	}

	/**
		Filters the specified character.
		If the character is in the filtered set, the predicate returns true.
		@param ch [in]- character to be filtered.
		@return true if ch is in the filtered set.
	*/
	bool operator()( UTF32TextChar const& ch ) const
	{
		return (fFilter.find(ch) != fFilter.end());
	}

private:
	CharSet fFilter;
};


/** Usage examples **

	// Removes kTextChar_Table and kTextChar_TableContinued from buffer
	textchar const specialChars[] = {kTextChar_Table, kTextChar_TableContinued};
	StringUtils::TextCharFilter filter(specialChars, ELEM_COUNT(specialChars));

	buffer.erase( std::remove_if( buffer.begin(), buffer.end(), filter), buffer.end() );

***************************************/


#endif // __TextCharFilter__ //
