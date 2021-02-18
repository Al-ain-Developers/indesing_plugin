//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/StringUtils.h $
//  
//  Owner: Paul Sorrick
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
#ifndef __STRINGUTILS__
#define __STRINGUTILS__

#include "IPMUnknown.h"
#include "PMString.h"
#include "WideString.h"
#include "EscapeTable.h"
#include <algorithm>
#include <utility>
#include "K2Pair.h"
#include <boost/range/iterator_range.hpp>

// Forward declarations
class TextCharFilter;
class IPMStream;

#pragma export on

namespace StringUtils
{

	// Array containing the replacement strings.
	typedef K2Vector<WideString> ArgArray;
	
	/** Formats a string replacing the positional arguments with the ones supplied.
		The positional argument is specified by %N% where N can be any positive number.
		Obviously the supplied args array needs to have as many arguments as the largest specified N in the format string.
		One parameter can appear in multiple places:
		 if the format string is "%1% is before %2% but reversed, %2% is before %1%"
		 and "one and two" are the elements of the args, the function will print "one is before two but reversed, two is before one".
		 @param formatString [IN, OUT] - on input contains the format string, on output the modified string with all the %N% specifiers replaced.
		 @param args [IN] - array containing the positional argument values that will replace %N% specifiers in the string.
	*/
	PUBLIC_DECL void FormatPositionalArgs(WideString& formatString, ArgArray const& args);


	// String parameter replacement - NOTE: you should have translated aString before passing it
	// to this routine. It will be marked as non-translating by this routine.
	// Note that more than one occurrence of a placeholder (^1, ^2, ^3, ^4, ^5, ^6, ^7) can occur and
	// all will be replaced with the provided string.
	PUBLIC_DECL void ReplaceStringParameters(
		PMString *aString,						// Input and output string that contains up to four different placeholders
		const PMString& parm1,					// String to replace ^1 with, may be empty
		const PMString& parm2 = kNullString,	// String to replace ^2 with, may be empty
		const PMString& parm3 = kNullString,	// String to replace ^3 with, may be empty
		const PMString& parm4 = kNullString,	// String to replace ^4 with, may be empty
		const PMString& parm5 = kNullString,	// String to replace ^5 with, may be empty
		const PMString& parm6 = kNullString,	// String to replace ^6 with, may be empty
		const PMString& parm7 = kNullString		// String to replace ^7 with, may be empty
		);

	// Input UTF16 String, Returns a PMString Translated to a UTF8 String
	PUBLIC_DECL void ConvertWideStringToUTF8 (const WideString & str, std::string & returnval );

	// An iterator range specifies a sequence of characters
	typedef boost::iterator_range<const unsigned char*> UTF8CharRange;
	
	// Helper function - constructs an UTF8CharRange from a std::string
	// This will be removed when ConvertUTF8ToWideString will be a template and it will work with any type of iterators (not only pointers)
	inline UTF8CharRange MakeUTF8CharRange(const std::string& str)
	{
		const unsigned char* b((const unsigned char*)(str.c_str()));
		const unsigned char* e(b + str.size());
		return UTF8CharRange(b, e);
	}
	
	/** Constructs an UTF8CharRange from a char buffer.
		Note: This utility function does not do any Unicode conversion.
		It is merely a convenient utility function. It assumes that utf8Buffer contains valid UTF8 encoded chars.
		Example:
			const char* text = "My Text";
			UTF8CharRange myRange(StringUtils::MakeUTF8CharRange(text, strlen(text));
	*/
	inline UTF8CharRange MakeUTF8CharRange(const char* utf8Buffer, size_t length)
	{
		const unsigned char* b((const unsigned char*)utf8Buffer);
		const unsigned char* e(b + length);
		return UTF8CharRange(b, e);
	}


	/** Converts a UTF8 encoded range to a WideString (UTF16)
		Note: UTF8 uses unsigned 8 bit values (unsigned char).
		@param utf8Range [IN] - the input range.
		@param returnVal [OUT] - the result string.
		@return a subrange of utf8Range containing the unconverted characters.
		If the conversion was successful this will be an empty range.
		If the input sequence had malformed UTF8, it will contain the subrange
		starting with the first invalid character and returnVal will contain the characters that were successfully converted.
		Depending on the context, the caller might choose to ignore the invalid character(s) and call this function again with the remaining range (after skipping the invalid characters).
	*/
	PUBLIC_DECL UTF8CharRange ConvertUTF8RangeToWideString (const UTF8CharRange& utf8Range, WideString & returnval) ;
	
	// Overload for convenience when you already have a std::string
	// If you have raw pointers use the UTF8CharRange version (faster - avoids std::string construction)
	inline UTF8CharRange ConvertUTF8ToWideString (const std::string& str, WideString & returnval)
	{
		return ConvertUTF8RangeToWideString(StringUtils::MakeUTF8CharRange(str), returnval);
	}
	
	// Functor that checks if the specified character is in the range [0x20, 0x7E]
	// This range does not include the control characters (like '\t' or 'n') which are below 0x20.
	struct IsPrintableASCII : public std::unary_function<char, bool>
	{
		inline bool operator()(char c) const
		{
			// Check if c is within the range [0x20-0x7E]
			return (c > 0x1F && c < 0x7F);
		}
	};
	
	PUBLIC_DECL void Reverse(WideString& w);

	// std::back_insert_iterator doesn't work with our non-standard containers
	// Optimized insert iterator that saves on re-allocations
	template<class Container>
	class back_insert_iterator
		: public std::iterator<std::output_iterator_tag, void, void, void, void>
	{
	public:
		explicit back_insert_iterator(Container& cont)
			: fContainer(cont)
		{
		}

		back_insert_iterator<Container>& operator=(UTF32TextChar val)
		{
			if ((fContainer.capacity() - fContainer.size()) < 2)
			{
				grow_capacity();
			}

			// push value into container
			fContainer.push_back(val);
			return (*this);
		}

		back_insert_iterator<Container>& operator*()
		{
			return (*this);
		}

		back_insert_iterator<Container>& operator++()
		{
			return (*this);
		}

		back_insert_iterator<Container> operator++(int)
		{
			return (*this);
		}

		back_insert_iterator<Container>& operator=(back_insert_iterator<Container> const&)
		{
			return (*this);
		}

	protected:

		// Grows the capacity of the container by a factor of 1.5
		// We want to have at least two empty slots available at the end.
		void grow_capacity(void)
		{
			size_t newSize(1);
			if (fContainer.capacity())
			{
				// Multiply by 1.5
				newSize = fContainer.capacity() + (fContainer.capacity() >> 1);
			}
			fContainer.reserve(++newSize);
		}

		Container& fContainer;
	};

	template<> PUBLIC_DECL back_insert_iterator<PMString>& back_insert_iterator<PMString>::operator=(UTF32TextChar val);
	template<> PUBLIC_DECL back_insert_iterator<WideString>& back_insert_iterator<WideString>::operator=(UTF32TextChar val);

	// Generic back_inserter

	template<class Container>
	inline back_insert_iterator<Container> back_inserter(Container& cont)
	{
		return (StringUtils::back_insert_iterator<Container>(cont));
	}

	/**
		Escapes the specified characters in the table.
		The caller must ensure that the destination range is big enough or that insert iterators are used
		The source and destination should not overlap
		@param srcBeg [in] - begin iterator for source
		@param srcEnd [in]- end iterator for sorce
		@param destBeg [in]- begin iterator for destination
		@param mappingTable [in] - the mapping table for the escaped characters
		@return the output iterator
	*/
	template <typename InputIt, typename OutputIt, typename CharType, typename EscapeType>
	OutputIt Escape( InputIt srcBeg, InputIt srcEnd, OutputIt destBeg,
					 EscapeTable<CharType, EscapeType> const& mappingTable )
	{
		typedef typename EscapeTable<CharType, EscapeType>::EscapeMap MapType;
		typedef typename EscapeTable<CharType, EscapeType>::EscapeMapKey MapKeyType;
		typedef typename EscapeTable<CharType, EscapeType>::EscapeMapValue MapValueType;

		MapType const& searchMap = mappingTable.GetEscapeMap();
		ASSERT( !searchMap.empty() );

		for ( ; srcBeg != srcEnd; ++srcBeg )
		{
			MapKeyType key(*srcBeg);
			typename MapType::const_iterator i = searchMap.find( key );
			if ( i != searchMap.end() )
			{
				destBeg = std::copy( i->second.begin(), i->second.end(), destBeg );
			}
			else
			{
				*destBeg++ = *srcBeg;
			}
		}
		return destBeg;
	}


	/**
		Unescapes the specified characters in the table.
		If an escape sequence is not present in the escape table, it will be copied to output unchanged and
		pFoundInvalidEscape flag will be set if the caller passed it in.
		The caller must ensure that the destination range is big enough or that insert iterators are used
		The source and destination should not overlap
		@param srcBeg [in]- begin iterator for source
		@param srcEnd [in]- end iterator for sorce
		@param destBeg [in]- begin iterator for destination
		@param mappingTable [in]- the mapping table for the escaped characters
		@param pFoundInvalidEscape [out,optional]- flag to signal if an unexpected escape sequence was found
		@return the output iterator
	*/
	template <typename InputIt, typename OutputIt, typename CharType, typename EscapeType>
	OutputIt Unescape( InputIt srcBeg, InputIt srcEnd, OutputIt destBeg,
					   EscapeTable<CharType, EscapeType> const& mappingTable, bool16* pFoundInvalidEscape = nil )
	{
		typedef typename EscapeTable<CharType, EscapeType>::UnescapeMap MapType;
		typedef typename EscapeTable<CharType, EscapeType>::UnescapeMapKey MapKeyType;
		typedef typename EscapeTable<CharType, EscapeType>::UnescapeMapValue MapValueType;

		if ( pFoundInvalidEscape )
		{
			*pFoundInvalidEscape = kFalse;
		}

		MapType const& searchMap = mappingTable.GetUnescapeMap();
		ASSERT( !searchMap.empty() );

		MapKeyType const& escapeString = searchMap.begin()->first;

		typename MapKeyType::value_type escapeChar = escapeString[0];
		size_t escapeLen = escapeString.size();

		while ( srcBeg != srcEnd )
		{
			// Is it an escape char?
			if ( *srcBeg == escapeChar )
			{
				// Do we have enough chars left to be considered an escape sequence?
				if ( escapeLen <= (size_t)std::distance(srcBeg, srcEnd) )
				{
					//MapKeyType key(srcBeg, srcBeg + escapeLen);
					MapKeyType key;
					std::copy(srcBeg, srcBeg + (int32)escapeLen, std::back_inserter(key) );
					typename MapType::const_iterator i = searchMap.find( key );
					if ( i != searchMap.end() )
					{
						// Replace with the found character
						*destBeg++ = i->second;
						std::advance(srcBeg, escapeLen);
						// Continue with next char
						continue;
					}
				}

				// We either found an invalid combination or a truncated escape sequence
				// Signal that to the caller if it cares
				if ( pFoundInvalidEscape )
				{
					*pFoundInvalidEscape = kTrue;
				}
			}

			// Copy the char to the output unchanged
			*destBeg++ = *srcBeg++;
		}

		return destBeg;
	}

	// Some predefined tables; these are implemented in stringutils.cpp

	// Table for escaping control characters ( '\r', '\n', etc)
	// This table should be used for finding control characters and display them to the UI.
	PUBLIC_DECL extern EscapeTable<uint32, char> const kSearchableCtrlCharsTable;

	// This table should be used for replacing control characters.
	// It contains only control chars that are safe to replace in the actual document.
	PUBLIC_DECL extern EscapeTable<uint32, char> const kReplaceableCtrlCharsTable;

	// This table should be used for replacing control characters that do not include meta meaning.
	// It contains only control chars that are safe to replace in the actual document and excludes
	// characters such as page number.
	PUBLIC_DECL extern EscapeTable<uint32, char> const kReplaceableNoMetaCtrlCharsTable;

	PUBLIC_DECL extern EscapeTable<uint32, char> const kSearchableGrepCtrlCharsTable;
	PUBLIC_DECL extern EscapeTable<uint32, char> const kReplaceableGrepCtrlCharsTable;

	PUBLIC_DECL extern EscapeTable<uint32, char> const kReplaceableXRefFormatCtrlCharsTable;
	
	// This table is used for replacing those special chars to HTML version.
	//PUBLIC_DECL extern EscapeTable<uint32, char> const kReplaceableHTMLCharsTable;

	// Predefined XML entities that should be recognized by any XML parser
	PUBLIC_DECL extern EscapeTable<uint32, char> const kXMLPredefinedEntitiesCharsTable;

	// Wraps together the C-array and it's size
	typedef K2Pair<textchar const*, size_t> CharArray;

	// Filter for commonly ignored chars.
	PUBLIC_DECL extern CharArray const kIgnoredCharsFilterArray;

	// Filter for special control chars
	PUBLIC_DECL extern CharArray const kSpecialControlCharsFilterArray;

	// Filter for whitespace (and similar) chars.
	PUBLIC_DECL extern CharArray const kWhitespaceCharsFilterArray;

	// Filter for special/variable width whitespace (e.g. CR/LF, tabs, indent to here, etc) chars.
	PUBLIC_DECL extern CharArray const kSpecialWhitespaceCharsFilterArray;

	// Filter for proxy chars (e.g. page numbers, footnotes, inlines, etc).
	PUBLIC_DECL extern CharArray const kProxyCharsFilterArray;

	// Filter for illegal chars within calculated text (e.g. proxyChars + specialWhitespace + tables-related chars).
	PUBLIC_DECL extern CharArray const kCalcTextIllegalCharsFilterArray;

 	enum StripType
	{
		/** Strip characters in the beginning of string */
		kStripLeadingChars = 0,
		/** Strip characters at the end of string */
		kStripTrailingChars,
		/** Strip characters both at end and beginning of string */
		kStripLeadingAndTrailingChars,
	}; 

	/**
		Strips the specified leading/trailing characters out of the text. 
		@param text [in,out]- text to be filtered.
		@param filter [in]- filter predicate that specifies which characters will be filtered out from beginning/end of the text.
		@param stripType [in]- flag to specify if leading or trailing or both need to be stripped.
	*/
	PUBLIC_DECL void StripBeginEndChars( WideString& text, CharArray const& charArray, StringUtils::StripType stripType);

	/**
		Strips the specified leading/trailing characters out of the text. 
		@param text [in,out]- text to be filtered.
		@param filter [in]- filter predicate that specifies which characters will be filtered out from beginning/end of the text.
		@param stripType [in]- flag to specify if leading or trailing or both need to be stripped.
	*/
	template<class PR> void StripBeginEndChars( WideString& text, PR filter, StringUtils::StripType stripType)
	{		
		// remove leading characters
		if (stripType == StringUtils::kStripLeadingAndTrailingChars || stripType == StringUtils::kStripLeadingChars)
		{
			WideString::const_iterator newBegin = text.begin();
			for (; newBegin != text.end(); ++newBegin)
			{
				if (!filter(*newBegin))
					break;
			}
			text.erase(text.begin(), newBegin);
		}

		// remove trailing characters
		if (stripType == StringUtils::kStripLeadingAndTrailingChars || stripType == StringUtils::kStripTrailingChars)
		{
			WideString::const_reverse_iterator rNewBegin = text.rbegin();
			for (; rNewBegin != text.rend(); ++rNewBegin)
			{
				const UTF32TextChar c = *rNewBegin;
				if (!filter(c))
					break;
			}
			
			text.erase(rNewBegin.base(), text.end());
		}
	}
	
	/**
		Filters the specified characters out of the text. This is a thin wrapper around remove_if algorithm
		because WideString doesn't implement erase().
		@param text [in,out]- text to be filtered.
		@param filter [in]- specifies the characters to be filtered out.
	*/
	PUBLIC_DECL void FilterString( WideString& text, CharArray const& charArray);

	/**
		Filters the specified characters out of the text. This is a thin wrapper around remove_if algorithm
		because WideString doesn't implement erase(). Before writing a new filter, consider whether one of
		the above pre-defined CharArray filters will do.
		@param text [in,out]- text to be filtered.
		@param filter [in]- filter predicate that specifies which characters will be filtered out.
	*/
	template<class PR> void FilterString( WideString& text, PR filter)
	{
		WideString::iterator_raw newEnd = std::remove_if(text.begin_raw(), text.end_raw(), filter);
		if ( newEnd != text.end_raw() )
		{
			// text.erase(newEnd, text.end());
			int32 pos = newEnd - text.begin_raw();
			int32 len = text.end_raw() - newEnd;
			text.remove_raw(pos, len);
		}
	}

	/** Convert a PMString retrieved from the user and convert it into a WideString.
		It converts embedded unicode (of the form <xxxx>), unescaping chars as described (e.g. ^t becomes tab, etc), and strips chars as described.

		@param ps The incoming string
		@param escapeTable The table to use, if any, to unmap escape sequences.
		@param stripArray The array to use, if any, that lists illegal characters to strip.
		@return the converted string
		@note used primarily by Dialogs and Scripting for converting between strings to/from the user and strings in the settings, etc
		@see IDialogUtils, IScriptProviderUtils
	*/
	PUBLIC_DECL WideString ConvertFromUIString(const PMString& ps, EscapeTable<uint32, char> const *escapeTable, const CharArray* stripArray);

	/** Opposite of ConvertFromUIString() - convert a WideString to a user-friendly PMString
		@param ws The incoming string
		@param escapeTable The table to use, if any, to unmap escape sequences.
		@return the converted string
		@note used primarily by Dialogs and Scripting for converting between strings to/from the user and strings in the settings, etc
		@see IDialogUtils, IScriptProviderUtils
	*/
	PUBLIC_DECL PMString ConvertToUIString(const WideString& ws, EscapeTable<uint32, char> const *escapeTable);

	/** A platform-independent version of itow that converts an int32 into its UTF16 representation.
		used by PMString::AppendNumber and PMString::AsNumber.

		@param i the number to Convert
		@param wBuffBegin the start of the output range
		@param wBuffEnd the end of the output range
		@return pointer to trailing null UTF16TextChar* or wBuffBegin if (wBuffEnd - wBuffBegin) is too small
		*/
	PUBLIC_DECL UTF16TextChar* ConvertInt32ToUTF16(int32 i, UTF16TextChar* wBuffBegin, UTF16TextChar* wBuffEnd);

	///** A platform-independent version of i64tow that converts an int64 into its UTF16 representation.
	//	used by PMString::AppendNumber and PMString::AsNumber.

	//	@param i the number to Convert
	//	@param wBuffBegin the start of the output range
	//	@param wBuffEnd the end of the output range
	//	@return pointer to trailing null UTF16TextChar* or wBuffBegin if (wBuffEnd - wBuffBegin) is too small
	//	*/
	PUBLIC_DECL UTF16TextChar* ConvertInt64ToUTF16(int64 i, UTF16TextChar* wBuffBegin, UTF16TextChar* wBuffEnd);

	/** A platform-independent version of uitow that converts a uint32 into its UTF16 representation.
		used by PMString::AppendNumber and PMString::AsNumber.

		@param i the number to Convert
		@param wBuffBegin the start of the output range
		@param wBuffEnd the end of the output range
		@return pointer to trailing null UTF16TextChar* or wBuffBegin if (wBuffEnd - wBuffBegin) is too small
		*/
	PUBLIC_DECL UTF16TextChar* ConvertUInt32ToUTF16(uint32 i, UTF16TextChar* wBuffBegin, UTF16TextChar* wBuffEnd);

	/** A platform-independent version of ui64tow that converts a uint64 into its UTF16 representation.
		used by PMString::AppendNumber and PMString::AsNumber.

		@param i the number to Convert
		@param wBuffBegin the start of the output range
		@param wBuffEnd the end of the output range
		@return pointer to trailing null UTF16TextChar* or wBuffBegin if (wBuffEnd - wBuffBegin) is too small
		*/
	PUBLIC_DECL UTF16TextChar* ConvertUInt64ToUTF16(uint64 i, UTF16TextChar* wBuffBegin, UTF16TextChar* wBuffEnd);

	/** Read bytes from stream into std::string

		@param s stream to read from
		@return string read in
		*/
	PUBLIC_DECL std::string	ReadStdString(IPMStream *s);

	/** Write std::string into stream

		@param s stream to write into
		@param writestring string to write
		*/
	PUBLIC_DECL void WriteStdString(IPMStream *s, std::string writeString);

	/** Given a WideString, will tokenize the WideString by white space and add each token to the tokens vector.
		The token added will not contain the white space and will not be empty. If given an empty string or a
		string that is all white space (has not tokens) nothing will be added to the vector.

		@param ws WideString to be tokenized by white space
		@param tokens vector of WideStrings that each token (if any) will be added to

		*/
	PUBLIC_DECL void TokenizeByWhitespace(const WideString& ws, std::vector<WideString>& tokens);

	/** Converts ArabicIndic, Farsi or full width digits to western digits (0x0030-0x0039)

		@param stringToNormalize string to convert
		*/
	PUBLIC_DECL void NormalizeDigits(PMString *stringToNormalize);

}

PUBLIC_DECL void ReplaceStringParameters(PMString *aString,const PMString& parm1,const PMString& parm2 = kNullString,
			const PMString& parm3 = kNullString,const PMString& parm4 = kNullString,const PMString& parm5 = kNullString,
			const PMString& parm6 = kNullString,const PMString& parm7 = kNullString);


#pragma export off


/** Usage examples **

	Escape( test.begin(), test.end(), std::back_inserter(out), kCtrlCharEscapeTable);

***************************************/


#endif
