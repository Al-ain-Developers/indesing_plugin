//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PMString.h $
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
#ifndef __PMSTRING__
#define __PMSTRING__

#include "K2Debugging.h"
#include "K2TypeTraits.h"
#include "PMTypes.h"
#include "UnicodeSavvyString.h"
#include <string>
#include <adobe/move.hpp>
#include <adobe/typeinfo.hpp>

class IPMStream;
class PMLocaleId;
class WideString;

#include "PlatformChar.h"
#include "Invariant.h"

// API's with DEPRECATED_PLATFORM_BUFFER will be removed in the 
// future. 
#define DEPRECATED_PLATFORM_BUFFER 1

/**
PMString is used for strings that show in the UI. Given a key then calling
Translate will lookup the translation for the key for the current UI locale.
This class should not be used for strings that are not in the UI. Please use
WideString for strings that do not need to be translated.
*/
class PUBLIC_DECL PMString : public UnicodeSavvyString
{
	public:
		typedef object_type data_type;

		/**
			Specify whether to translate during call
			
			@see SetKey and Constructor
		*/
        enum TranslateDuringCall
         {
			/** Keep as key string. calling Translate will give translation. */
            kDontTranslateDuringCall,
			/** Translate during call */
            kTranslateDuringCall
         };

		//----------Constructors-----------------
		
		PMString();

		/**  Constuctor
				Construct PMString using a ascii key. Caller is responsible for the 
				memory of ConstCString key. Keys are the first string of the string pair
				in a resource StringTable.
				@param key			platform C string. Need to be null terminated.
				@param translate	using kTranslateDuringCall will put the translation in the string.
											The key will be lost. 
		 */
		PMString(ConstCString key, TranslateDuringCall translate = kDontTranslateDuringCall);

		/**  Constuctor
			@param string		IN Unicode representation (in UTF-16 encoding) of the string for
								initialization. This string need not be null-terminated
			@param nDblBytes	IN The number of 16-bit values in the string buffer.
								This value may be greater than the number of characters represented since
								UTF-16 can contain surrogate pairs, each of which represents a single
								character.
								Composed characters are not supported
		*/
		PMString(const UTF16TextChar * string, int32 nDblBytes);

		/** Constructs from Unicode characters. Allows construction of a PMString from L"" constants.
			On Windows wchar_t matches UTF16, on the Mac they are UTF32s.
			NOTE: 	This should be used to set strings that are not keys. Calling Translate on this string will do
			nothing. If you want to translate the string use SetKey.
			@param s [IN] - buffer containing wchar_t characters. Needs to be null terminated.
		 */
		explicit PMString(const wchar_t* s);
	
		/** Constructs from Unicode characters. On Windows wchar_t matches UTF16, on the Mac they are UTF32s.
			NOTE: 	This should be used to set strings that are not keys. Calling Translate on this string will do
			nothing. If you want to translate the string use SetKey.
			@param s [IN] - buffer containing wchar_t characters. Doesn't have to be null terminated since the len parameter is mandatory.
			@param len [IN] - number of wchar_t's in s to be read.
		 */
		PMString(const wchar_t* s, size_t len);

		/** Movable constructor - assumes ownership of the remote part.
		 */
		PMString(adobe::move_from<PMString> other)
			: UnicodeSavvyString(adobe::move_from<UnicodeSavvyString>(other.source)),
			fEncoding(other.source.fEncoding),
			fShouldTranslate(other.source.fShouldTranslate), fHasTranslated(other.source.fHasTranslated)
#if defined(DEBUG)			
			,fFormatNumber(other.source.fFormatNumber)
#endif		
		{
		}

		PMString(PMString &&other) noexcept
			: UnicodeSavvyString(std::move(other)),
			fEncoding(other.fEncoding),
			fShouldTranslate(other.fShouldTranslate), fHasTranslated(other.fHasTranslated)
#if defined(DEBUG)			
			, fFormatNumber(other.fFormatNumber)
#endif		
		{
		}

		PMString(const PMString& s);
		PMString(const WideString& s);
		~PMString();


		//----------GET/SET STRING Routines-----------------
		
		/**	Set string using PMString s
			@param s	string used to set this PMString.
		 */
		void SetString(const PMString& s);

		/**	Set PMString using a ascii key. Caller is responsible for the 
				memory of ConstCString key.
				@param key			ascii key string. Need to be null terminated.
				@param translate	using kTranslateDuringCall will put the translation in the string.
											The key will be lost. 
		 */
		void SetKey(ConstCString key, TranslateDuringCall translate = kDontTranslateDuringCall);
		
		//----------GET/SET UNICODE STRING Routines-----------------
		
		/**	Get a null terminated wchar_t string.

			@param wchar_tString	OUT returns string as wchar_t string
			@param bufferSize		size of wchar_tString buffer
		*/
		void GetWChar_tString(wchar_t *wchar_tString, int32 bufferSize) const;


		/**	Set PMString using a Unicode string.
			@param x			Unicode buffer. Does not need to be null terminated as nDblBytes
								determines what will be read.
			@param nDblBytes	number of UTF16TextChars in x to be read to set PMString. Do not
								include count of null terminator.
		 */
		void SetXString(const UTF16TextChar* x, int32 nDblBytes);
	
		// Discriminator for wchar_t size
		template<int bytes>
		struct wchar_size{};
	
		/**	Sets the content of the PMString using a non-translatable Unicode string.
			The string will be marked as non-translatable.
		 @param s			Unicode buffer. Does not need to be null terminated as len
		 determines how much it will be read.
		 @param len	number of wchar_t in s to be read to set PMString. Do not
		 include count of null terminator.
		 */
		inline PMString& assign(const wchar_t* s, size_t len)
		{
			fShouldTranslate = kFalse;
			fHasTranslated = kFalse;
			return assign_impl(s, len, wchar_size<sizeof(wchar_t)>());
		}

#if 0// routine defined in UnicodeSavvyString.h included here for reference
		/**	Grab the Unicode representation of the string.
			@param numUTF16s		OUT number of UTF16s in buffer. Can be nil.
			@return UTF16TextChar	buffer of UTF16s
		 */
		const UTF16TextChar * GrabUTF16Buffer(int32 *numUTF16s) const;

		/**	Get number of UTF16s in string
			@return int32	number of UTF16s in string
		 */
		int32 NumUTF16TextChars() const;
#endif

		/**	Gets a std::string encoded as UTF8.

			@return utf8 encoded string
		*/
		std::string GetUTF8String() const;

		/**	Sets using a std::string encoded as UTF8. String is marked as not translatable
		*/
		void SetUTF8String(const std::string &utf8String);

		//----------GET/SET OS STRING Routines-----------------

#ifdef MACINTOSH
		/**	Provide a reference to a Macintosh CFString, which must be released with a call to ::CFRelease
			@return A Macintosh CFString object
		*/
		CFStringRef CreateCFString() const;

		/**	Set PMString using a reference to a Macintosh CFString, the string is copied and caller is
			responsible for releasing with a call to ::CFRelease
			@param A Macintosh CFString object
		*/
		void SetCFString(CFStringRef cfstring);
#endif

#ifdef WINDOWS
		/**	Grab a TCHAR* string. Since we are a unicode application this is the same as GrabWString()
			@return TCHAR*	buffer of TCHARs
		 */
		TCHAR* GrabTString(void)
			{ return (TCHAR*)UnicodeSavvyString::GrabUTF16Buffer(nil); }

		/**	Grab a const TCHAR* string. Since we are a unicode application this is the same as
			const version of GrabUTF16Buffer()
			@return TCHAR*	buffer of TCHARs
		 */
		const TCHAR* GrabTString(void) const
			{ return (const TCHAR*)UnicodeSavvyString::GrabUTF16Buffer(nil); }

		/**	Set PMString using a TCHAR* string. Since we are a unicode application this is the same
			as SetXString.
			@param x			TCHAR* string which is a Unicode buffer for this application.
		 */
		void SetTString(const TCHAR* x);

		/**	The number of TCHARs in this string
			@return uint32	number of TCHARs
		 */
		uint32 GetTLength() const;
#endif


		//---------CHARACTER LEVEL ROUTINES-----------------

		// NOTE: Routines with a "W" in the name imply the operation occurs on the Unicode representation
		// of the string.
		// Using the Unicode version is recommended.

		/**	returns the double byte textchar at a specific character offset into the Unicode string
			representation.
			@param pos				character offset. O based.
			@return UTF32TextChar	character at index
		 */
		UTF32TextChar GetWChar(int32 pos) const;


		//---------BASIC STRING ROUTINES-----------------

		// basic string routines, clear, length, etc.

#if 0// routine defined in UnicodeSavvyString.h included here for reference
		/** Retrieves the number of code points stored in this string.
			The number of code points can be different from the number of code values
			if surrogates are present
			@return number of unicode code points.
		*/
		size_type CharCount() const;
#endif

		/**	Get the number of UTF16s required to store this string. Same value as returned in numUTF16s by
			GrabUTF16Buffer.
			@return int32	number of UTF16s required to store 
		 */
		int32 WCharLength(void) const;

		/**	Number of characters is 0.
			@return bool16	kTrue if no characters in string
		 */
		bool16 empty() const;
		
		/** Erases the string making it empty. Capacity stays the same.
			@see reserve, capacity
		*/
		void clear();

		//---------APPEND ROUTINES-----------------

		/**	Append the first n characters of s onto this string.
			@param s			string to append
			@param nCharacters	number of characters in s to append
		 */
		void Append(const PMString &s, CharCounter nCharacters = kMaxInt32);

		/**	Append a WideString
			@param s	WideString to append
		 */
		void Append(const WideString& s);

		/**	Append a Unicode string
			@param ws			string to append
			@param nDblBytes	number of UTF16s to append
		 */
		void AppendW(const UTF16TextChar * ws, int32 nDblBytes = kMaxInt32);

		/**	Append a Unicode character
			@param wc	character to append
		 */
		void AppendW(UTF32TextChar wc);

		/** Append Unicode characters. Allows appending L"" constants to the PMString.
			On Windows wchar_t matches UTF16, on the Mac they are UTF32s.
			This does not change whether the string is translatable or not.
			@param s [IN] - buffer containing wchar_t characters. Needs to be null terminated.
		 */
		void append(const wchar_t *s);


		//---------INSERT ROUTINES-----------------

		/**	Insert the first n characters of s into this string. pos is interpreted as a true platform
			character offset not as a byte offset.
			@param s			string to insert
			@param pos			insert at this position. move existing characters to end
			@param nCharacters	how many characters of s to insert. Default kMaxInt32 means insert
								all characters.
		 */
		void Insert(const PMString &s, CharCounter pos = 0, CharCounter nCharacters = kMaxInt32);

		/**	Insert a Unicode string
			@param ws			string to insert
			@param nDblBytes	number of UTF16s to insert
			@param pos			insert at this position
		 */
		void InsertW(const UTF16TextChar *ws, int32 nDblBytes = kMaxInt32, int32 pos = 0);

		/**	Insert a Unicode character
			@param wc	character to insert
			@param pos	insert at this position
		 */
		void InsertW(UTF32TextChar wc, int32 pos = 0);


		//---------PARSE ROUTINES-----------------

		/**	Creates a new string based on count characters (not bytes) from this string. The
			substring begins at pos (0 based). Return nil if selected range is empty.
			@param pos			position to get string. 0 based.
			@param count		number of character to get. kMaxInt32 goes to end of string.
			@return PMString*	substring. return nil if selected range is empty.
		 */
		PMString* Substring(CharCounter pos, CharCounter count = kMaxInt32) const;

		/**	Returns the specified token/item of a string, given a single delimiter
		 	@param delimiter	IN The string to use as a delimiter
		 	@param nItem		IN The one based item number for the the desired item
		 	@return				A pointer to a string you need to deallocate, typically
								via k2::scoped_ptr. If the item does not exist (i.e. nItem
								is too low or high) then nil will be returned instead of a
								valid object.
		 */
		PMString* GetItem(const PMString& delimiter, const int32 nItem) const;

		/**	This routines removes count characters (not bytes) from this string, starting after
			the pos'th platform character.
			@param pos		IN zero-based character counter representing the position for the operation.
			@param count	IN The number of characters (not bytes). Using kMaxInt32 will remove from pos to end of string.
		*/
		void Remove(CharCounter pos, CharCounter count = 1);	

		/**	This routines truncates the final count platform characters (not bytes) from the string.
			@param count	number of characters to remove from end
		 */
		void Truncate(CharCounter count = 1);	

		
		/**	What kind of white space to strip
			
			@see StripWhiteSpace
		*/
 		typedef enum {
			/** Strip white space in the beginning of string */
 			kLeadingWhiteSpace = 0,
			/** Strip white space at the end of string */
			kTrailingWhiteSpace,
			/** Strip both white space at end and beginning of string */
			kLeadingAndTrailingWhiteSpace,
			/** Strip all white space */
			kAllWhiteSpace
		} WhitespaceType; 

		/**	Strip white space from string. This routine only strips kTextChar_Space (U+0020).
			@param wsType	where to strip white space from 
		 */
		void StripWhiteSpace(WhitespaceType wsType = kAllWhiteSpace);

		/**	This routine looks for a substring within this string.
			pos is the platform character offset (not byte count) to start looking.
			@param keyString	string to look for
			@param pos			where to start looking.
			@return CharCounter	The character offset (not byte count) at which the
								string was found, or -1 when not found 
		 */
		CharCounter IndexOfString(const PMString& keyString, CharCounter pos = 0) const;

		/**	Last index of substring within this string.
			@param keyString	string to look for
			@return CharCounter	The character offset (not byte count) at which the
								string was found, or -1 when not found 
		 */
		CharCounter LastIndexOfString(const PMString& keyString) const;

		/**	Index of Unicode char in Unicode version of string
			@param wc			Unicode character to find index for
			@param pos			position to start looking
			@return CharCounter	0 based index. -1 when not found
		 */
		CharCounter IndexOfWChar(UTF32TextChar wc, int32 pos = 0) const;

		/**	Last index of Unicode char in Unicode version of string
			@param wc			Unicode character to find index for
			@return CharCounter 0 based index. -1 when not found
		 */
		CharCounter LastIndexOfWChar(UTF32TextChar wc) const;

		/**	Returns true if string contains searchString
			@param searchString		string to look for
			@param pos				where to start looking.
			@return bool16			kTrue if searchString is contained in string
		 */
		bool16 Contains(const PMString& searchString, CharCounter pos = 0) const;

		/**	Returns true if string starts with searchString
			@param searchString		string to look for
			@param pos				where to start looking.
			@return bool16			kTrue if string begins with searchString at given pos.
		 */
		bool16 BeginsWith(const PMString& searchString, CharCounter pos = 0) const;

		/** Search the string and replace valid occurences of the form <xxxx> or <xxxxxx>
			(where 'x' is a hex digit) into a single character corresponding to that Unicode value
			@return kTrue if there were embedded characters
		*/
		bool16 ParseForEmbeddedCharacters();

		
		//----------Compare Routines---------------

		/**	Lexicographically compares strings like strcmp or stricmp, except based on UNICODE values.
			If both strings are roman encoded then compared based on platform values instead of Unicode.
			@param casesensitive	if kTrue use case to compare
			@param s				string to compare to
			@return int32			0 strings are equal. -1 string < s. 1 string > s
		 */
		int32 Compare(bool16 casesensitive, const PMString &s) const;

		/**	If limitCompareToShorterLength is true, you can use IsEqual to compare n characters of 2
			strings, where 'n' is the length of the shorter string
			@param s							string to compare
			@param casesensitive				if kTrue use case to compare
			@param limitCompareToShorterLength	if kTrue only compare to shortest string
			@return bool16						kTrue if equal
		 */
		bool16 IsEqual(const PMString &s, bool8 casesensitive = kTrue, bool8 limitCompareToShorterLength = kFalse) const;
		
	
		//----------OPERATORS---------------
		
		/**	Equals. Compares buffers. If either has a unicode buffer these are compared. If both have
			platform buffers then those are compared.
			@param s	string to compare
		 */
		bool16 operator == (const PMString &s) const;

		/**	Equals. Compares key. Parameter key must be a key. no translation is done.
			@param key	key to compare
		 */
		bool16 operator == (ConstCString key) const;

		/**	This is really just a not of the == operator. Calls !(this==s)
			@param s	string to compare
		 */
		bool16 operator != (const PMString &s) const;
				
		/**	Lexicographically compares strings like strcmp or stricmp. If both are encoded in roman
			and neither has embedded unicode then platform compare is done. Otherwise compare is
			based on UNICODE values.
			@param s	string to compare
		 */
		bool16 operator < (const PMString &s) const;

		/**	Lexicographically compares strings like strcmp or stricmp. If both are encoded in roman
			and neither has embedded unicode then platform compare is done. Otherwise compare is
			based on UNICODE values.
			@param s	string to compare
		 */
		bool16 operator > (const PMString &s) const;

		/**	Lexicographically compares strings like strcmp or stricmp. If both are encoded in roman
			and neither has embedded unicode then platform compare is done. Otherwise compare is
			based on UNICODE values.
			@param s	string to compare
		 */
		bool16 operator <= (const PMString &s) const;

		/**	Lexicographically compares strings like strcmp or stricmp. If both are encoded in roman
			and neither has embedded unicode then platform compare is done. Otherwise compare is
			based on UNICODE values.
			@param s	string to compare
		 */
		bool16 operator >= (const PMString &s) const;

		/**	Appends PMString s
			@param s	string to append
		 */
		PMString& operator+=(const PMString& s);

		/**	Appends PMString s2 to PMString s1 and returns it as a PMString
			@param s1	string to append to
			@param s2	string to append
			@return PMString	string to set
		 */
		friend PMString operator+(const PMString& s1, const PMString& s2);


		/** Swaps the contents of two strings.
		 */
		friend void swap( PMString& left, PMString& right ) noexcept;

		/** operator copy assignment 
		 */
		inline PMString& operator=(const PMString &other)
		{
			if (&other != this)
				SetString(other);
			return *this;
		}

		/** operator move assignment 
		*/
		inline PMString& operator=(PMString &&other) noexcept
		{
			swap(*this, other);
			return *this;
		}

		//---------------MISC ROUTINES------------------------
		
		/**	Provide a binary hash value based on numeric codes
			@return uint32	hash value
		 */
		uint32 Hash(void) const;

		/**	Append number as string to existing string.
			@param i	number to convert to string and append to existing string.
		 */
		void AppendNumber(int32 i);

		/**	Append number as string to existing string.
			@param r						number to convert to string and append to existing string.
			@param digitsPrecision			how many decimal points to show. -1 means show all
			@param round					if kTrue value is rounded else value is floored. Only
											used if digitsPrecision is > -1.
			@param eliminateTrailingZeros	if kTrue trailing zeros are not in string
		 */
		void AppendNumber(const PMReal& r,int32 digitsPrecision = -1, bool16 round = kFalse, bool16 eliminateTrailingZeros = kFalse);

		/**	Set string to value.
			@param i	value to convert to string
		 */
		void AsNumber(int32 i);

		/**	Set string to value.
			@param r						PMReal to convert to string
			@param digitsPrecision			how many decimal points to show. -1 means show all
			@param round					if kTrue value is rounded else value is floored. Only
											used if digitsPrecision is > -1.
			@param eliminateTrailingZeros	if kTrue trailing zeros are not in string
		 */
		void AsNumber(const PMReal& r,int32 digitsPrecision = -1, bool16 round = kFalse, bool16 eliminateTrailingZeros = kFalse);

		/**	Append fixed number as string to existing string.
			@param f	fixed to to convert to string and append
		 */
		void AppendFixed(Fixed f)
			{ AppendNumber( PMReal((double)(f/(double)65536.0))); }

		/**	Set string to fixed value.
			@param f	fixed to convert to string.
		 */
		void AsFixed(Fixed f)
			{ AsNumber( PMReal((double)(f / (double)65536.0))); }

		/**
			Error in converting string to number
			
			@see GetAsNumber and GetAsDouble
		*/
		typedef enum {
			/** No Error. */
			kNoError = 0,
			/** String has no number. */
			kNoNumber,
			/** String has more than just number. */
			kNotJustNumber
		} ConversionError; 
		/**	Try to interpert the string as a number.
			@param pError	sets to a ConversionError if the entire string cannot be converted.
			@param lenNotConverted	number of characters at the end that were not converted
			@return int32	number that string represents
		*/
		int32 GetAsNumber( ConversionError *pError = nil, CharCounter *lenNotConverted = nil ) const;

		/**	Try to interpert the string as a double.
			@param pError			sets to a ConversionError if the entire string cannot be converted.
			@param lenNotConverted	number of characters at the end that were not converted
			@return double			number that string represents
		 */
		double GetAsDouble(  ConversionError *pError = nil, CharCounter *lenNotConverted = nil ) const;

		/**	Converts characters to Upper case.
		 */
		void ToUpper(void);

		/**	Converts characters to Lower case.
		 */
		void ToLower(void);


		//----------READ/WRITE ROUTINES---------------

		/**	This writes Unicode representation of string. Encoding, HasTranslated and
			IsTranslatable are also written.
			@param s	string to read or write
		 */
		void ReadWrite(IPMStream *s);
		
		/**	Reads a key from a resouce that is of type wstring. If it is a write stream
			wstring type is written out.

			@param *s	IN OUT The stream object from which to read.
		*/
		void ReadWriteKey(IPMStream *s); 

		/**	What kind of encoding to use to convert to unicode
			
			@see ReadPlatformWriteUnicode
		*/
		typedef enum { 
			/** Roman windows encoding  */
			kPlatformEncodingWin, 
			/** Roman mac encoding  */
			kPlatformEncodingMac,
			/** All other platform encodings (uses String encoding to convert) */
			kPlatformEncodingOther,
			/** UTF8 encoding */
			kUTF8Encoding
		}  StringPlatformEncoding;
		/**
			This will read a platform encoded string from s and store it in unicode (UTF16) in this
			PMString. We use this to read the Translations saved in .fr files. This is for
			performance reasons because when they are drawn to screen the OS wants unicode.

 			@param s				stream to read string from
			@param encodingClass	how the string being read is encoded
			@param includeBools		includes format, shouldTranslate, HasTranslated. set kTrue if resource is PlatformPMString. set kFalse if resource is wstring
		*/
		void ReadPlatformWriteUnicode(IPMStream *s, PMString::StringPlatformEncoding encoding = kPlatformEncodingOther, bool16 includeBools = kTrue);


		//----------TRANSLATE ROUTINES---------------

		/**	translate from key to another locale, over-loaded so that if no locale is specified
			the current global locale setting is used.
			@param locale	locale to translate to
			@return bool16	kTrue if translated. Also kTrue if IsTranslatable is kFalse or
							HasTranslated if kTrue.
		 */
		bool16 Translate(const PMLocaleId& locale);

		/**	translate from key using current locale.
			@return bool16	kTrue if translated. Also kTrue if IsTranslatable is kFalse or
							HasTranslated if kTrue.
		 */
		bool16 Translate();

		//----------DISCOURAGED TRANSLATE ROUTINES---------------
		// DISCOURAGED.
		// As much as possible do not use these routines. If the usage does not need translation
		// consider using WideString.

		/**	Find out if string is translatable. This is true when constructed with default parameters.
			This does not mean there is a translation for the string just that calling Translate will
			look for a translation.
			@return bool16	kTrue if string is translatable.
		 */
		bool16 IsTranslatable() const;

		/**	Sets weather the string should be translated. If the string was typed by the user often
			you want to turn off translation.

			RECOMMENDATION -
			If you need to turn translation off think about using WideString instead. If that cannot be done
			Try calling constructor with kNoTranslate or SetCString with an encoding (that defaults to
			an untranslatable string).
			
			@param shouldTranslate	kFalse to turn off translation
			@return PMString&		returns this
		 */
		PMString& SetTranslatable(bool16 shouldTranslate); 

		/**	String has been translated. Calling Translate will set this to kTrue if IsTranslatable
			is kTrue and the string length is greater than 0. Also calling SetTranslated will set
			this to kTrue.
			@return bool16	kTrue if the string has been translated. 
		 */
		bool16 HasTranslated() const;

		/**	SetTranslated should not usually be called. It is only used when we get a string
			the user typed in, so we know it is translated, but it isn't marked that way.

			RECOMMENDATION -
			If you need to turn translation off think about using WideString instead. If that cannot be done
			Try calling constructor with kNoTranslate or SetCString with an encoding (that sets to
			an untranslatable string).
			
		 */
		void SetTranslated();


		//----------PLATFORM STRING Routines-----------------
		// DISCOURAGED
		// PMString using Unicode internally so as much as possible restrict the use of 
		// platform string calls
		
		/**	What kind of encoding to use to represent the platform string as. These are platform
			specific. If running on mac this is mac encoding. On windows it is windows encoding.
			You should persist Unicode if you want to take data cross platform.
			Comments for encoding list Macintosh script first than Windows codepage.
			@see SetEncoding
		*/
		enum StringEncoding
		{ 
			/** smRoman,			Codepage 1252 */
			kEncodingASCII,
			/** smJapanese,			Codepage 932 */
			kEncodingShiftJIS,
			/** smTradChinese,		Codepage 950 */
			kEncodingChineseBig5,
			/** smKorean,			Codepage 949 */
			kEncodingKorean,
			/** smArabic,			Codepage 1256 */
			kEncodingArabic,
			/** smHebrew,			Codepage 1255 */
			kEncodingHebrew,
			/** smGreek,			Codepage 1253 */
			kEncodingGreek,				
			/** smCyrillic,			Codepage 1251 */
			kEncodingCyrillic,
			/** smThai,				Codepage 874 */
			kEncodingThai = 21,
			/** smSimpChinese,		Codepage 936 */
			kEncodingChineseGBK = 25,
			/** smCentralEuroRoman,	Codepage 1250 */
			kEncodingEastEuropean = 29,
			/** smVietnamese,		Codepage 1258 */
			kEncodingVietnamese,
			
			kUnknownEncoding = -1
		};

		/**  Constuctor

			Set PMString using a platform string. Same as calling -
			SetCString(ConstCString C, PMString::StringEncoding encoding)
			This should be used to set strings that are not keys. Calling Translate on this string will do
			nothing. If you want to translate use the constructor without encoding -
			PMString(ConstCString key, TranslateDuringCall translate = kDontTranslateDuringCall);

			If it is not a key first consider using WideString.
			If you are you are using a string you don't want to be the same in all languages consider
			adding it as a key to the notranslate table.
						
			@param string		C string to set PMString to. Make sure script of passed in C string
								matchs the script of the PMString.
			@param encoding	The desired script of the platform representation of this string.
								The default value creates a PMString with the encoding set appropriately
								for the	current operating environment of the operating system: ASCII for
								English language systems, ShiftJIS for Japanese systems, etc.  It is
								recommended that this parameter be set explicitly, however.
		*/
		PMString(ConstCString string,  PMString::StringEncoding encoding);

		/**	Set PMString using a pascal string. Make sure the encoding passed in matchs the
			encoding of p. Caller is responsible for the memory of ConstPString p.
			This should be used to set strings that are not keys. Calling Translate on this string will do
			nothing. If you want to translate the string use SetKey.

			RECOMMENDATION -
			See if the ContPString p came from an API for the Macintosh. See if there is a new version of the 
			API that gives a Unicode buffer or CFString.
			
			@param p	string used to set PMString
			@param encoding	encoding of C string.
		 */
		void SetPString(ConstPString p, PMString::StringEncoding encoding);

		/**	Set PMString using a platform string. Make sure encoding passed in matchs the
			encoding of C. Caller is responsible for the memory of ConstCString C.
			This should be used to set strings that are not keys. Calling Translate on this string will do
			nothing. If you want to translate the string use SetKey.
			@param C			platform C string. Need to be null terminated.
			@param encoding	encoding of C string.
		 */
		void SetCString(ConstCString C, PMString::StringEncoding encoding);
		
		/**	Set PMString using a platform string. Make sure encoding passed in matchs the
			encoding of x. Caller is responsible for the memory of char* x.
			@param x		platform string. Does not need to be null terminated as nBytes
							determines what will be read.
			@param nBytes	number of bytes in x to be read to set PMString. Do not include count
							of null terminator
			@param encoding	encoding of C string.
		 */
		void SetXString(const char* x, int32 nBytes, PMString::StringEncoding encoding = kUnknownEncoding);

		/**	Get pascal string. If PMString byte length is greater than 255 all bytes will still be
			copied to the buffer but the lenght byte will be truncated to 255. If bufferSize is not
			big enough the call returns and does not copy anything to the buffer p.

			RECOMMENDATION -
			See if this API is used for a Macintosh API call see if there is a new version of the 
			API that takes a CFString.
			
			@param p			OUT A pointer to string of bufferSize which will be filled in with
								the characters of the string represented in GetEncoding() encoding.
			@param bufferSize	IN the size of the provided buffer measured in bytes, including
								space for the length byte.
			@param encoding	encoding of pascal string.
		 */
		void GetPString(PString p, int32 bufferSize, PMString::StringEncoding encoding = kUnknownEncoding) const;

		/**	Gets a C string.  If bufferSize is not big enough the call returns and does not copy
			anything to the buffer c.
			@param C			OUT A pointer to string of bufferSize which will be filled in with
								the characters of the string represented in GetEncoding() encoding.
			@param bufferSize	IN the size of the provided buffer measured in bytes, including
								space for the terminating zero.
		*/
		void GetCString(CString C, int32 bufferSize, PMString::StringEncoding encoding = kUnknownEncoding) const;

		/**	Gets a platform string.
			Check to make sure the code really wants a plaform encoded string if instead
			it wants utf8 you can call GetUTF8String

			@param encoding	encoding for string to return.
		*/
		std::string GetPlatformString(PMString::StringEncoding encoding = kUnknownEncoding) const;

		/**	Insert a platform string
			@param ps		platform string to insert
			@param nBytes	number of bytes to insert. kMaxInt32 means insert ::strlen of ps bytes.
			@param pos		insert at this position. This is a character position not a byte
							position.
			@param encoding	encoding of ps
		 */
		void Insert(const char* ps, int32 nBytes = kMaxInt32, CharCounter pos = 0, PMString::StringEncoding encoding = kUnknownEncoding);

		/**	Insert a platform character
		
				RECOMMENDATION -
				If you are appending a hard coded value look for the value in TextChar.h and call InsertW(UTF32TextChar wc).
			
			@param pc	platform character
			@param pos	insert at this position
			@param encoding	encoding of pc
		 */
		void Insert(char pc, CharCounter pos = 0, PMString::StringEncoding encoding = kUnknownEncoding);

		/**	Insert a platform character
			@param pc	platform character
			@param pos	insert at this position
		 */
		void Insert(const PlatformChar &pc, CharCounter pos = 0);

		/**	Append a series of characters which may have NO or MULTIPLE nul characters.  No length
			checking is performed
			@param ps		platform string.
			@param nBytes	number of bytes in ps to append
			@param encoding	encoding of ps
		 */
		void Append(const char* ps, int32 nBytes = kMaxInt32, PMString::StringEncoding encoding = kUnknownEncoding);

		/**	Append a platform or ascii character [replaces Append(char c)]
		
				RECOMMENDATION -
				If you are appending a hard coded value look for the value in TextChar.h and call AppendW(UTF32TextChar wc).
			
			@param pc	platform character.
			@param encoding	encoding of pc
		 */
		void Append(char pc, PMString::StringEncoding encoding = kUnknownEncoding);

		/**	Append a platform or ascii character [replaces Append(char c)]
			@param pc	platform character.
		 */
		void Append(const PlatformChar &pc);

		/** returns the platform encoded character (as a PlatformChar) at a specific character offset
			into the platform string representation. This routine is multibyte (shift-JIS) character safe.
			It is read-only */
		const PlatformChar operator[](CharCounter index) const;	// based on new multibyte safe GetChar()

		/** returns the platform encoded character (as a PlatformChar) at a specific character offset
			@param pos		IN The character position (0-based) of the desired character.  Note that
							embedded characters shown in the format "<1234>" returned from GrabCString()
							count as a single character, which will be returned as an invalid PlatformChar
			@param encoding	encoding to get character as
			@return			The platform character object at the given position.  Note that a PMString
							may contain 0 characters other than	the terminating character.  GetChar will
							return an invalid PlatformChar in this case.	
		*/
		const PlatformChar GetChar(CharCounter pos, PMString::StringEncoding encoding = kUnknownEncoding) const;
				
		/**	This routine looks for a character within this string.
			pos is the platform character offset (not byte count) to start looking.
			@param keyString	string to look for
			@param pos			where to start looking.
			@return CharCounter	The character offset (not byte count) at which the character
								was found, or -1 when not found 
		 */
		CharCounter IndexOfCharacter(const PlatformChar &pc, CharCounter pos = 0) const;

		/**	Last index of platform char in string. Starts looking from end of string.
			@param pc			character to find index for
			@return CharCounter	0 based index. -1 when not found
		 */
		CharCounter LastIndexOfCharacter(const PlatformChar &pc) const;


		//----------NOT RECOMMENDED. All these APIs should not be used---------------
		//API's at top are the least recommend. Please remove them first.

#ifdef DEPRECATED_PLATFORM_BUFFER
		/**	OBSOLETE. Use GetEncoding instead

			PORTING RECIPE -
			Encoding (also known as script) should be obtained when calling a routing that gets a
			platform string. After the encoding is put at the point of the call this API should be removed.

			@return uint8	script of string
		 */
		uint8	  GetScript() const;

		/**	OBSOLETE. Use SetEncoding instead

			PORTING RECIPE -
			Encoding (also known as script) should be set when calling a routing that sets or gets a
			platform string. After the encoding is put at the point of the call this API should be removed.

			@return uint8	script of string
		 */
		void	  SetScript(uint8 script);

		/**	Provide the current encoding of the platform buffer for the string

			PORTING RECIPE -
			Encoding (also known as script) should be obtained when calling a routing that gets a
			platform string. After the encoding if put at the point of the call this API should be removed.

			@return An identifier in the enumeration of String Encodings above
		*/
		PMString::StringEncoding	GetEncoding() const;

		/**	Sets to encoding of the string. If there is a platform buffer in the string then
			this will delete the Unicode buffer so changing the encoding when there is a platform
			buffer may change the Unicode buffer. However if there is no platform buffer and only
			a Unicode buffer the unicode will stay the same and calls to get the platform buffer
			will use the new encoding to convert the unicode to platform. Due to this it is best
			to call this when your string is empty so you have easy to understand behavior.

			PORTING RECIPE -
			Encoding (also known as script) should be set when calling a routine that sets or gets a
			platform string. After the encoding is put at the point of the call this API should be removed.

			@param encoding		new encoding to set for string. 
		 */
		void		SetEncoding(PMString::StringEncoding encoding);

		/**	DEPRECATED: Use GrabUTF16Buffer

			PORTING RECIPE -
			Use GrabUTF16Buffer(nil)

			@return UTF16TextChar* 
		 */
		const UTF16TextChar* GrabWString(void) const;

		/**	Set PMString using a platform string. Make sure script of passed in string matchs the
			script of the PMString. This can be changed by calling SetEncoding. Buffer is copied so
			caller is responsible for the memory of ConstCString C.
			This is the same as SetKey. defaults to set the string to TRANSLATABLE but not translated.

			PORTING RECIPE -
			If the cstring is a key use SetKey.
			If the cstring is not a key use SetCString with encoding parameter.

			@param C			platform C string. Need to be null terminated.
		 */
		void SetCString(ConstCString C);

		/**	Number of character is 0. Same as calling empty().

			PORTING RECIPE -
			Call empty().

			@return bool16	kTrue if no characters in string
		 */
		bool16 IsNull(void) const;

		/**	Number of character is 0. Same as calling empty().

			PORTING RECIPE -
			Call empty().

			@return bool16	kTrue if no characters in string
		 */
		bool16 IsEmpty() const;

		/**	To be deprecated. Use clear() instead.

			PORTING RECIPE -
			Call clear().

		*/
		void Clear(void)
		{
			PMString::clear();
		}
#endif

	protected:

		void AssignToPlatformBuffer(ConstCString src, int32 lengthInBytes);

#ifdef DEBUG			
		mutable InvariantCount 	fInvariant;
public:
		void Invariant() const;
#endif
	private:
		int32 CountChars() const;

		void SetUTF16Buffer(const char* x, int32 nBytes, PMString::StringEncoding encoding);

		int32 GetPlatformBuffer(char *buffer, int32 bufferSize, PMString::StringEncoding encoding) const;
		void ReadUnicode(IPMStream *s);
		void WriteUnicode(IPMStream *s);
	
		inline PMString& assign_impl(const wchar_t* s, size_t len, wchar_size<2>)
		{ 
			SetXString(reinterpret_cast<const UTF16TextChar*>(s), static_cast<int32>(len));
			return *this;
		}
	
		PMString& assign_impl(const wchar_t* s, size_t len, wchar_size<4>);

		inline PMString& append_dispatch(const wchar_t* s, size_t len)
		{
			return append_impl(s, len, wchar_size<sizeof(wchar_t)>());
		}

		inline PMString& append_impl(const wchar_t* s, size_t len, wchar_size<2>)
		{ 
			AppendW(reinterpret_cast<const UTF16TextChar*>(s), static_cast<int32>(len));
			return *this;
		}
	
		PMString& append_impl(const wchar_t* s, size_t len, wchar_size<4>);

		StringEncoding		fEncoding;
		bool16				fShouldTranslate;
		bool16				fHasTranslated;

public:
#if defined(DEBUG)
		uchar					fFormatNumber;
#endif
};

extern PUBLIC_DECL const PMString kNullString;


// Friend functions ---

inline PMString operator+(const PMString& s1, const PMString& s2)
{
 	PMString result(s1);
 	result.Append(s2);
 	return result;
}

inline void swap( PMString& left, PMString& right ) noexcept
{
	// Base class swap
	swap(static_cast<UnicodeSavvyString&>(left), static_cast<UnicodeSavvyString&>(right));

	std::swap(left.fEncoding, right.fEncoding);
	std::swap(left.fShouldTranslate, right.fShouldTranslate);
	std::swap(left.fHasTranslated, right.fHasTranslated);
#if defined(DEBUG)			
	std::swap(left.fFormatNumber, right.fFormatNumber);
#endif
}

// specialize adobe::type_info<> to avoid typeid problems across DLL boundaries
ADOBE_NAME_TYPE_0("pmstring:indesign:adobe",PMString);
#endif
