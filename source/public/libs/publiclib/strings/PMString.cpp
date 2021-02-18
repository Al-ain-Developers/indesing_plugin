//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/strings/PMString.cpp $
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
//  Major Revisions:	DJB (1/1998)    Support for "Embedded Unicode" to keep track of unembeddable foreign characters
//  DJB (3/2000)    Multibyte platform support (pre CoolType 3.0 - i.e. platform char offsets not known)
//  
//========================================================================================

#include "VCPublicHeaders.h"

// ----- Interfaces -----

#include "LocaleSetting.h"
#include "CTUnicodeTranslator.h"
#include "CompressInt.h"
#include "StreamUtil.h"
#include "WideString.h"
#include "StdObjFormatNumbers.h"		// For our string format value
#include "StdObjUtils.h"
#include "StringUIEmbedding.h"
#include "StringStorage.h"
#include "StringUtils.h"
#include "gdtoa.h"

#ifdef WINDOWS
#include "mbstring.h"
#endif

#include "IStringDataBase.h"
#include "IStringDataBaseTable.h"
#include "adobe/unicode.hpp"
#include "IDThreadingPrimitives.h" // For CompareAndSwap

/*
namespace
{
	// Functor that checks if the specified character is low ASCII [0x20, 0x7E]
	struct IsPrintableASCII : public std::unary_function<char, bool>
	{
		bool operator()(char c) const
		{
			// Check if c is within the range [0x20-0x7E]
			return (c > 0x1F && c < 0x7F);
		}
	};

}
*/


#undef  CHECK_MY_INVARIANT
#define CHECK_MY_INVARIANT() AUTO_INVARIANT_CHECKER(PMString)

PlatformChar TextCharToPlatformChar(UTF32TextChar &utf32, int8 encoding);


const int32 kStringChunk = 16;
const int32 kMaxPrefixLen = 255;

const PMString kNullString("", PMString::kUnknownEncoding);

#ifdef DEBUG
#include "IDBStreamData.h"
#include "DocumentID.h"
#endif

const int32 kSuffix	= 1;	//length suffix for null terminated C string


int32 EmbedWideCharInCharString(UTF32TextChar w, char* toBuffer, int32 toBufferLen, int16 writingscript);
int32 BytesNeededToEmbedUnicodeChars(const UTF16TextChar* fromString, long fromStrNumUTF16s);
int32 TranslateTextCharToEmbeddedChar(const UTF16TextChar* fromString, long fromStrNumUTF16s, char* toStringBuffer, long toStrBufferLength, int16 writingscript, bool16& foundMissingChar);
int32 TranslateCharToTextChar(const char* fromString, long fromStrNumUTF16s, UTF16TextChar* toStringBuffer, long toStrBufferLength, int16 writingscript);

const uchar kEmbeddedUnicodePrefixChar = 0x3c;
const uchar kEmbeddedUnicodeSuffixChar = 0x3e;



const long kBytesPerUnicodeChar = 8;		// With UTF32, a Unicode character may be up to 8 characters
			

// This is defined by default, but it can be removed to test the non-roman
// implementations on a US system.
#define DEBUG_UNICODE_LENGTHCACHE	0 

#define IS_DOUBLEBYTE_SCRIPT(script) (script == kEncodingShiftJIS || script == kEncodingChineseBig5 || script == kEncodingKorean || script == kEncodingChineseGBK)

// Given a requested length (newByteLength) & currentLength return a padded new size for the buffer.
// Performance optimization.
// Increase the size of the string by 50% Performance measurements have shown that in the case 
// of large strings we pay a large penalty in the extra calls to memcpys if the size is increased 
// by some small chunk size like 16 or 32. For very large strings (as in XML SaveBackwards) this change 
// resulted in a 50% speed up. [jshankar Aug-5-2003]
// If currentLength is zero then default value of kStringChunk is used.
inline int32 CalcStringSize(int32 newByteLength, int32 currentByteLength)
{
	ASSERT(newByteLength >= 0 && currentByteLength >= 0);
	ASSERT(newByteLength		< 128 * 1024 * 1024);
	ASSERT(currentByteLength	< 128 * 1024 * 1024);

	int32 myStringChunk = currentByteLength / 2;

	// Ensure minimum string chunk size
	if (myStringChunk  < kStringChunk)
		myStringChunk  =  kStringChunk;

	ASSERT(myStringChunk  > 0);
	const int32 calcLength = myStringChunk  * ((newByteLength + myStringChunk  + kSuffix) / myStringChunk);
	ASSERT(calcLength >= newByteLength + kSuffix);
	return calcLength;
}


inline int32 CalcShrinkSize(int32 newLength)
{
	// Second parameter is the currentByteLength
	return CalcStringSize(newLength, 0) ;
}

inline uchar LengthPrefix(const int32 len)
{
	int32 temp = kMaxPrefixLen;		// VC 5.0 beta work around
	return (uchar)::minimum(temp, len);
}

/* Compare lexigraphically two strings */
int PUBLIC_DECL stricmp(const char *s1, const char *s2)
{
    char c1, c2;
    while (1)
    {
    	c1 = tolower(*s1++);
    	c2 = tolower(*s2++);
        if (c1 < c2) return -1;
        if (c1 > c2) return 1;
        if (c1 == 0) return 0;
    }
}

#pragma mark -
#pragma mark *CONSTRUCTORS*
PMString::PMString() :
#if defined(DEBUG)
	fFormatNumber(kPMStringFormatNumber),
#endif
	fShouldTranslate(kTrue),
	fHasTranslated(kFalse)
{
	fEncoding = (StringEncoding) LocaleSetting::GetSystemScript();
}

// SetKey
PMString::PMString(ConstCString key, TranslateDuringCall translate) :
#if defined(DEBUG)
	fFormatNumber(kPMStringFormatNumber),
#endif
	fShouldTranslate(kTrue),
	fHasTranslated(kFalse)
{
	fEncoding = (StringEncoding) LocaleSetting::GetSystemScript();
	CHECK_MY_INVARIANT();
	ASSERT(key != nil);
	if (*key)
	{
		SetKey(key, translate);
	}
	else if (translate == kTranslateDuringCall)
	{
		// The key string is empty and we've been asked to translate it!
		ASSERT_FAIL("The key string is empty!");
		fHasTranslated = kTrue;
	}
}

PMString::PMString(ConstWString string, int32 nDblBytes) :
#if defined(DEBUG)
	fFormatNumber(kPMStringFormatNumber),
#endif
	fShouldTranslate(kTrue),
	fHasTranslated(kFalse)
{
	fEncoding = (StringEncoding) LocaleSetting::GetSystemScript();
	CHECK_MY_INVARIANT();
	SetXString(string, nDblBytes);
}

PMString::PMString(const wchar_t* s) :
#if defined(DEBUG)
fFormatNumber(kPMStringFormatNumber),
#endif
fShouldTranslate(kFalse),
fHasTranslated(kFalse)
{
	fEncoding = (StringEncoding) LocaleSetting::GetSystemScript();
	CHECK_MY_INVARIANT();
	const size_t len = std::wcslen(s);
	assign(s, len);
}

PMString::PMString(const wchar_t* s, size_t len) :
#if defined(DEBUG)
fFormatNumber(kPMStringFormatNumber),
#endif
fShouldTranslate(kFalse),
fHasTranslated(kFalse)
{
	fEncoding = (StringEncoding) LocaleSetting::GetSystemScript();
	CHECK_MY_INVARIANT();
	assign(s, len);
}

// The default encoding is set to the same as the copy
PMString::PMString(const PMString& s) :
#if defined(DEBUG)
	fFormatNumber(kPMStringFormatNumber),
#endif
	fShouldTranslate(kTrue),
	fHasTranslated(kFalse)
{
	fEncoding = s.fEncoding;
	SetString(s);
} 

PMString::PMString(const WideString &s) :
#if defined(DEBUG)
	fFormatNumber(kPMStringFormatNumber),
#endif
	fShouldTranslate(kTrue),
	fHasTranslated(kFalse)
{
	fEncoding = (StringEncoding) LocaleSetting::GetSystemScript() ;
	CopyFrom(s);
}

PMString::~PMString()
{
}


#pragma mark -
#pragma mark *GET/SET STRING*
// Does SetString set the encoding as well?
void PMString::SetString(const PMString& s)
{
	CHECK_MY_INVARIANT();
#ifdef DEBUG
	s.Invariant();
#endif

	if (&s == this)
	{
		return;
	}

	fEncoding = s.fEncoding;
	fShouldTranslate = s.IsTranslatable();
	fHasTranslated = s.HasTranslated();

	CopyFrom(s);

	return;
}

void PMString::SetKey(ConstCString key, TranslateDuringCall translate)
{
	CHECK_MY_INVARIANT();
	ASSERT(key != nil);

//should we check key is 7 bit and set encoding to ascii?

	fShouldTranslate = kTrue; //ldb 11/15/99
	fHasTranslated = kFalse;

	if (translate == kTranslateDuringCall)
	{
		// we just translate using the passed in key rather than using our internal buffer.
		bool16 result = kFalse;
		InterfacePtr<IStringDataBase> sdb(GetExecutionContextSession(), IID_ISTRINGDATABASE);
		if( sdb )	
		{
			result = sdb->Retrieve(LocaleSetting::GetLocale(), key, *this);
		}
		
		// note: this member must be changed after the call to Retrieve, because therein we
		// actually change what 'this' is.
		fHasTranslated = kTrue;
		return;
	}


	const int32	len = (int32)std::strlen((char *)key);

#ifdef DEBUG
	for (int i = 0; i < len; i++)
	{
		if ((key[i] < 0x20) || ((key[i]&0x80) != 0))
		{
			PMString temp;
			InterfacePtr<IStringDataBase> sdb(GetExecutionContextSession(), IID_ISTRINGDATABASE);
			const IStringDataBaseTable *table = sdb ? sdb->GetStringTable(LocaleSetting::GetLocale()) : nil;
			bool16 transResult = table ? table->Retrieve(key, temp) : kTrue;

			//SetKey should only be called with a translatable key.
			// If you had code that was not setting a key like - 
			// "Glyph Threshold:5.\t32768 glyphs"
			// and want to fix this assert you can use -
			// PMString(L"Glyph Threshold:5.\t32768 glyphs")
			// Note that using the wchar_t constructor will set translatable to false.
			// which is correct in the case where you are not setting a key.
			// Another case you may have is something like -
			// mystring += "\n"
			// That can be fixed by changing to -
			// mystring.AppendW(kTextChar_LF);
			ASSERT_MSG(transResult, FORMAT_ARGS("PMString::SetKey - calling SetKey with a string that does not have a tranlsation. String is - %s", key));
			//Keys must be ascii. For this assert we have a translatable key but it contains
			// invalid characters. Tab(0x09) and LF(0x0A) are currently used in some keys.
			ASSERT_MSG(!transResult || (key[i] == 0x09) || (key[i] == 0x0A), "PMString::SetKey - Not a valid key. Trying to set key with value < 0x20 or > 0x7F");
			break;
		}
	}
#endif

	UTF16TextChar * unicodeBuffer = GetBufferForWriting(len);
	fUTF16BufferLength = len;
	try
	{
		UTF16TextChar *unicodeBufferEnd = adobe::detail::to_utf16<UTF16TextChar>(key, key+len, unicodeBuffer, adobe::detail::unicode_size_type_<sizeof(char)>());
		fUTF16BufferLength = unicodeBufferEnd - unicodeBuffer;
		ASSERT_MSG((len == 0 || fUTF16BufferLength > 0) && fUTF16BufferLength <= len, "Error converting UTF8 string");
	}
	catch(std::runtime_error &error)
	{
		ASSERT_FAIL(FORMAT_ARGS("PMString::ReadPlatformWriteUnicode - Error converting UTF8 string - %s", error.what()));

		throw error;
	}

	// Ensure the terminating null
	unicodeBuffer[fUTF16BufferLength] = 0;

	fNumChars = CountChars();
}

#pragma mark -
#pragma mark *GET/SET UNICODE STRING*
void PMString::GetWChar_tString(wchar_t *wchar_tString, int32 bufferSize) const
{
	ASSERT(wchar_tString != nil);
	ASSERT(bufferSize >= 0);

	// Make sure the target buffer is big enough.
	if (fUTF16BufferLength + 1 > bufferSize)
	{
		ASSERT_FAIL("buffer too small");
		return;
	}

	if (fUTF16BufferLength)
    {
		if (sizeof(wchar_t) == sizeof(UTF16TextChar))
		{
			::memcpy(wchar_tString, ConstBuffer(), fUTF16BufferLength * sizeof(wchar_t));
			wchar_tString[fUTF16BufferLength] = 0;
		}
		else if (sizeof(wchar_t) == 4)
		{
			int32 numChars = CharCount();
			for (int32 i = 0; i < numChars; i++)
			{
				wchar_tString[i] = (wchar_t)(GetUTF32TextChar(i).GetValue());
			}
			wchar_tString[numChars] = 0;
		}
    }
}

void PMString::SetXString(const UTF16TextChar* x, int32 nDblBytes)
{
	CHECK_MY_INVARIANT();
	if (nDblBytes == kMaxInt32)
	{
//		nDblBytes = std::wcslen((wchar_t*)x);
		nDblBytes = (int32)UTF16TextCharLength(x);
	}
	ASSERT(nDblBytes >= 0);
	
	fNumChars = fUTF16BufferLength = 0; // Necessary to avoid invariant violation upon entering UnicodeSavvyString::assign
	UnicodeSavvyString::assign(x, x + nDblBytes);
}

PMString& PMString::assign_impl(const wchar_t* s, size_t len, wchar_size<4>)
{
	// We should get a valid pointer and a valid length
	ASSERT(s && len < static_cast<size_t>(kMaxInt32));

	CHECK_MY_INVARIANT();
	fNumChars = fUTF16BufferLength = 0;
		
	// TODO - implement this in UnicodeSavvyString
	UnicodeSavvyString::reserve(static_cast<UnicodeSavvyString::size_type>(len));
	for (int32 i = 0; i < len; ++i)
	{
		UnicodeSavvyString::AppendUTF32TextChar(s[i]);
	}
	
	ASSERT(fNumChars == len);
	ASSERT(fUTF16BufferLength >= len);
	
	return *this;
}

std::string PMString::GetUTF8String() const
{
	std::string retString;
	try
	{
		adobe::detail::to_utf8<char>(this->begin(), this->end(), std::back_inserter(retString), adobe::detail::unicode_size_type_<sizeof(UTF16TextChar)>());
	}
	catch(std::runtime_error &error)
	{
		ASSERT_FAIL(FORMAT_ARGS("PMString::GetUTF8String - Error converting to UTF8 string - %s", error.what()));

		throw error;
	}

	return retString;
}


void PMString::SetUTF8String(const std::string &utf8String)
{
	int32 len = (int32)utf8String.size();
	UTF16TextChar * unicodeBuffer = GetBufferForWriting(len);
	fUTF16BufferLength = len;
	bool isUTFCompliant = true;
	UTF16TextChar *unicodeBufferEnd = adobe::detail::to_utf16<UTF16TextChar>(utf8String.begin(), utf8String.end(), unicodeBuffer, adobe::detail::unicode_size_type_<sizeof(char)>(),&isUTFCompliant);
	
	ASSERT_MSG(isUTFCompliant, "The string is not UTF8 Compliant!");
	fUTF16BufferLength = unicodeBufferEnd - unicodeBuffer;
	if (isUTFCompliant)
	{
		ASSERT_MSG((len == 0 || fUTF16BufferLength > 0) && fUTF16BufferLength <= len, "Error converting UTF8 string");
	}
	else
	{
		throw std::runtime_error("unicode: ill-defined utf8 (>= 254)");
	}
	// Ensure the terminating null
	unicodeBuffer[fUTF16BufferLength] = 0;

	fNumChars = CountChars();
	fShouldTranslate = kFalse;
	fHasTranslated = kFalse;
}

#pragma mark -
#pragma mark *GET/SET OS STRING*
#ifdef WINDOWS
void PMString::SetTString(const TCHAR* t)
{
	CHECK_MY_INVARIANT();
	ASSERT(t != nil);
	int32 nTChars = 0;

	if (t)
	{
		nTChars = (int32)_tcslen(t);	
		ASSERT(nTChars >= 0);

		SetXString((UTF16TextChar*)t, nTChars);
	}
}

#ifndef UNICODE
#error PMString expects UNICODE to be defined
#endif

uint32 PMString::GetTLength() const				// The number of TCHARs in this string
{
	return fUTF16BufferLength;
}

#endif

#pragma mark -
#pragma mark *CHARACTER LEVEL ROUTINES*
//----------------------------------------------------------------------
// GetWChar
//
//		Returns the Unicode character at a specific offset into the Unicode string representation. 
//	
//		NOTE: CoolType 3.0 allows some platform characters to encode to multiple Unicode characters.
//			In situations where such characters are present, this routine will return fragments of such a character - DJB 2/22/2000
//
//		NOTE: position is interpreted as a character offset. This offset is measured in Unicode space, 
//		where until CoolType 3 comes along, all characters map to a double byte. 
//
//----------------------------------------------------------------------
UTF32TextChar PMString::GetWChar(int32 pos) const
{
	return GetUTF32TextChar(pos);
}

#pragma mark -
#pragma mark *BASIC STRING ROUTINES*
//----------------------------------------------------------------------
// WCharLength
//
//		Returns the number of double byte characters needed to represent the string in Unicode. 
//	
//		NOTE: CoolType 3.0 allows some platform characters to encode to multiple Unicode characters.
//			In situations where such characters are present, this routine will count these as multiple Unicode characters - DJB 2/22/2000
//
//----------------------------------------------------------------------
int32 PMString::WCharLength(void) const
{
	return fUTF16BufferLength;
}

bool16 PMString::empty() const
{
	return CharCount() == 0;
}

void PMString::clear(void)
{ 
	CHECK_MY_INVARIANT();
	fShouldTranslate = kTrue;
	fHasTranslated = kFalse;
	fNumChars = 0;
	
	UnicodeSavvyString::clear();
}


#pragma mark -
#pragma mark *APPEND*
//----------------------------------------------------------------------
// Append
//
//		Various character/string parameters are allowed.
//
//
//		Added default length parameter to the char and unicode buffer cases.
//		forgetting to specify the length would result in C++ doing some hidden construction
//		and you'd end up with a different result than if you'd remembered to specify a length.		- DJB 3/16/2000
//----------------------------------------------------------------------
void PMString::Append(const PMString &s, CharCounter nCharacters)
{
	// Assume we will append the whole string (common case)
	const UTF16TextChar* srcBuf = s.GrabUTF16Buffer(nil);
	size_type codeValuesToAdd(s.NumUTF16TextChars());
	size_type codePointsToAdd(s.CharCount());
	
	// Do we want just some part of the string?
	if (nCharacters != kMaxInt32)
	{
		const size_type srcCharCount = s.CharCount();

		ASSERT(nCharacters <= srcCharCount);
		if (nCharacters <= srcCharCount)
		{
			// Convert the code point (char) count into code value count (UTF16s)
			codeValuesToAdd = CharOffsetToUTF16Offset(srcBuf, s.NumUTF16TextChars(), nCharacters);
			codePointsToAdd = nCharacters;
		}
	}
	
	UnicodeSavvyString::append(srcBuf, codeValuesToAdd, codePointsToAdd);
}

// Unicode characters
void PMString::Append(const WideString& s)
{
	InsertW(s.GrabUTF16Buffer(nil), s.NumUTF16TextChars(),CharCount());
}

// Unicode strings
void PMString::AppendW(ConstWString w, int32 nDblBytes)
{
	CHECK_MY_INVARIANT();
	ASSERT(w != nil || nDblBytes == 0);
	ASSERT(nDblBytes >= 0);
	// if length wasn't specified, use wcslen to find the length of the buffer passed in
	if (nDblBytes == kMaxInt32)
	{
//		nDblBytes = std::wcslen((wchar_t*)w);
		nDblBytes = (int32)UTF16TextCharLength(w);
	}

	UnicodeSavvyString::append(w, nDblBytes);
}

void PMString::AppendW(UTF32TextChar wc32)
{
	CHECK_MY_INVARIANT();
	UnicodeSavvyString::AppendUTF32TextChar(wc32);
}

void PMString::append(const wchar_t* s)
{
	const size_t len = std::wcslen(s);
	append_dispatch(s, len);
}

PMString& PMString::append_impl(const wchar_t* s, size_t len, wchar_size<4>)
{
	// We should get a valid pointer and a valid length
	ASSERT(s && len < static_cast<size_t>(kMaxInt32));

	CHECK_MY_INVARIANT();
		
	// TODO - implement this in UnicodeSavvyString
	UnicodeSavvyString::reserve(static_cast<UnicodeSavvyString::size_type>(fUTF16BufferLength+len));
	for (int32 i = 0; i < len; ++i)
	{
		UnicodeSavvyString::AppendUTF32TextChar(s[i]);
	}
	
	//ASSERT(fNumChars == len);
	//ASSERT(fUTF16BufferLength >= len);

	return *this;
}

#pragma mark -
#pragma mark *INSERT*
//----------------------------------------------------------------------
// Insert
//
//		Various character/string parameters are allowed.
//
//		These routines have been rewritten for compatibility with multibyte encodings.
//
//		NOTE: In InDesign 1.0 and 1.5, the int32 position parameter was interpreted as a BYTE offset
//		into the target string, which is inappropriate for multibyte encodings.
//
//		NOTE: position is now interpreted as a character offset. This offset is measured in platform character space.
//		Until CoolType 3 comes along, determining character offsets isn't possible, so we translate to Unicode space 
//		where all characters map to a double byte. 
//
//		EMBEDDING NOTE: Notice that it is possible to accidentally insert characters inside the <XXXX> sequences used 
//		to embed foreign characters. This can only be avoided if all operations take place in Unicode space, which has 
//		the undesirable side effect that the character offsets are different. Stick with platform offsets for now.
//
//		 																				- DJB 2/22/2000
//
//----------------------------------------------------------------------
void PMString::Insert(const PMString &s, CharCounter position , CharCounter nCharacters)
{
	CHECK_MY_INVARIANT();
	ASSERT(position >= 0);
	ASSERT(position <= this->CharCount());
	ASSERT(nCharacters >= 0);
	
	if (position < 0 || nCharacters <= 0)
	{
		return;
	}

	CharCounter nWchars = s.CharCount();
	const UTF16TextChar* wBuf = s.GrabUTF16Buffer(nil);
	if (nWchars > 0 && wBuf)
	{
		int32 nDblBytesToInsert = (nCharacters >= s.fNumChars) ? s.WCharLength() : CharOffsetToUTF16Offset(wBuf, s.WCharLength() ,nCharacters);
		InsertW(wBuf, nDblBytesToInsert, CharCounter_GetInt32(position));
	}
}

// Unicode strings
void PMString::InsertW(ConstWString s, int32 nDblBytes, int32 pos)
{
	CHECK_MY_INVARIANT();
// would like to remove this. Who is depending on it!	fHasTranslated = kFalse;
	UnicodeSavvyString::InsertUTF16String(s, nDblBytes, pos);
}

// Unicode characters
void PMString::InsertW(UTF32TextChar wc, int32 pos)
{
	CHECK_MY_INVARIANT();
// would like to remove this. Who is depending on it!	fHasTranslated = kFalse;
	UnicodeSavvyString::InsertUTF32TextChar(wc, pos);
}


#pragma mark -
#pragma mark *PARSE*
//----------------------------------------------------------------------
// Substring - return nil if the substring is empty
//
//		These routines have been rewritten for compatibility with multibyte encodings.
//
//		NOTE: In InDesign 1.0 and 1.5, the int32 pos parameter was interpreted as a BYTE offset
//		into the target string, which is inappropriate for multibyte encodings. - DJB 2/22/2000
//
//		NOTE: position is now interpreted as a character offset. 
//
//		 																				- DJB 2/22/2000
//		@param pos is the zero-based index of the first character of the range desired
//		@param len is the number of characters in the desired substring.  If pos + len exceeds the
//			number of characters in the string, the substring returned will be from pos to the end
//
//----------------------------------------------------------------------
PMString* PMString::Substring(CharCounter pos, CharCounter len) const
{
	ASSERT(pos <= fNumChars && pos >= 0);
	ASSERT(len >= 0);
	if (pos >= fNumChars || pos < 0 || len == 0)
	{
		return nil;
	}

	int32 utf16start = CodePointIndexToUTF16Index(pos);
	int32 utf16end;
	if (len == kMaxInt32 || pos + len >= fNumChars)
	{
		utf16end = fUTF16BufferLength;
	}
	else
	{
		utf16end = CodePointIndexToUTF16Index(pos + len);
	}

	// TODO: Make a private PMString constructor to optimize this
	PMString * retval = new PMString();
	retval->fEncoding = fEncoding;
	retval->fShouldTranslate = IsTranslatable();
	retval->fHasTranslated = HasTranslated();

	retval -> SetXString(UnicodeSavvyString::GrabUTF16Buffer(nil) + utf16start, utf16end - utf16start);

#ifdef DEBUG	
	retval -> Invariant();
#endif
	return retval;
}

//----------------------------------------------------------------------
// GetItem - return token nItem given a delimiter
//----------------------------------------------------------------------
PMString* PMString::GetItem(const PMString& delimiter, const int32 nItem) const
{
	int32 start = 0;
	int32 item = 0;
	while (true)
	{
		int32 offset = IndexOfString(delimiter, start);
		item++;
		if (item > nItem)
			return nil;
		if (offset == -1 && item == nItem)
		{
			return Substring(start);
		}
		else if (item == nItem)
		{
			return Substring(start, offset-start);
		}
		if (offset > -1)
			start = offset + 1;
		else
			return nil;
	}
}


//----------------------------------------------------------------------
// Remove - remove a specified range of characters from a string
//
//----------------------------------------------------------------------
void PMString::Remove(CharCounter pos, CharCounter len)
{
	CHECK_MY_INVARIANT();
	ASSERT(pos >= 0);
	ASSERT(pos <= this->CharCount());
	ASSERT(len >= 0);

	UnicodeSavvyString::Remove(pos, len);

	return;
}

//----------------------------------------------------------------------
// Truncate - truncate a string to a specified number of characters.
//
//		This routine has been rewritten for compatibility with multibyte encodings.
//
//		NOTE: In InDesign 1.0 and 1.5, the int32 len parameter was interpreted as a BYTE count
//		in the target string, which is inappropriate for multibyte encodings. - DJB 2/22/2000
//
//		NOTE: len is now interpreted as platform character counts. 
//		Until CoolType 3 comes along, determining platform character offsets isn't possible, so we translate to 
//		Unicode space where all characters map to a double byte. 
//
//		EMBEDDING NOTE: Notice that it is possible to accidentally remove a portion of a <XXXX> sequence used 
//		to embed foreign characters. Should there be a TruncateW?, we're trying to avoid it.
//
//		HH 6/26/00 I added the "handleTwoByte" which is on by default.
//		If you set this to false be sure the string you're working with does not need 
//		special 2-byte handling
//
//																			- DJB 2/22/2000
//
//----------------------------------------------------------------------

void PMString::Truncate(CharCounter len)
{
	CHECK_MY_INVARIANT();

	UnicodeSavvyString::Truncate(len);

	return;
}

//----------------------------------------------------------------------
// StripWhiteSpace
//
//		Remove the whitespace from a string.
//
//		Luckily these routines take a specific definition of whitespace as the normal ACSII space character only.
//		(In Unicode there are lots of white space characters)
//		Given that we only search for ASCII type blanks, this routine is reasonably compatible with multibyte encodings. 
//
//		 																				- DJB 3/3/2000
//
//----------------------------------------------------------------------
void PMString::StripWhiteSpace(WhitespaceType wsType)
{
	CHECK_MY_INVARIANT();

	if (!CharCount())
	{
		return;
	}

	if (wsType == kAllWhiteSpace)
	{
		CharCounter	strIndex = 0;
		CharCounter stringLength = CharCount();
		while (strIndex < stringLength )
		{
			if(GetWChar(strIndex) == kTextChar_Space)
			{
				Remove(strIndex);
				stringLength = CharCount();
			}
			else
			{
				strIndex++;
			}
		}
		return;
	}
		
	if (wsType == kTrailingWhiteSpace || wsType == kLeadingAndTrailingWhiteSpace)
	{
		CharCounter charLength = CharCount();
		CharCounter poststrip = 0;

		while (poststrip < charLength && (GetWChar(charLength -1 - poststrip) == kTextChar_Space))
		{
			poststrip++;
		}

		Truncate(poststrip);	// remove trailing white space

			
		if (wsType == kTrailingWhiteSpace)
		{
			return;
		}
	}
				
	if (wsType == kLeadingWhiteSpace || wsType == kLeadingAndTrailingWhiteSpace)
	{
		CharCounter charLength = CharCount();
		CharCounter prestrip = 0;
			
		while (prestrip < charLength && (GetWChar(prestrip) == kTextChar_Space))
		{
			prestrip++;
		}
			
		if (prestrip >= charLength)
		{
			clear();
		}
		else
		{
			Remove(0, prestrip);	// remove preceding white space
		}

		return;
	}		
		
	ASSERT_FAIL("unknown whitespace type");
	return;	
}

//----------------------------------------------------------------------
// IndexOfString
//
//		Find one string within the body of another, return starting location.
//		Used by exceptions to replace parameter strings like file names and directory names.
//
//		This routine is compatible with multibyte encodings.
//
//		NOTE: In InDesign 1.0 and 1.5, this routine compared bytes - so while the string find would succeed, the return
//		value was a byte offset instead of a character offset
//
//		NOTE: the return value is now a character offset. This offset is measured in platform character space.

//		EMBEDDING NOTE: Notice that it is possible to match a portion of a <XXXX> sequence used 
//		to embed foreign characters.
//
//		 																				- DJB 3/3/2000
//
//----------------------------------------------------------------------
CharCounter PMString::IndexOfString(const PMString& keyString, CharCounter position) const
{
	ASSERT(position >= 0);
	ASSERT(position <= this->CharCount());
	
	CharCounter		keyLen = keyString.CharCount();
	CharCounter		myLen = CharCount();
	// make sure the strings being compared make sense. Comparing a string which has been translated to one which has not is a no-no.
	// we only allow it if one of the strings is empty, or if one is non-translatable
	ASSERT_MSG(myLen == 0 || keyLen == 0 || keyString.HasTranslated() == this->HasTranslated() || !IsTranslatable() || !keyString.IsTranslatable(),FORMAT_ARGS("Comparing translated string to non-translated string!(Strings are '%s' and '%s'",GetUTF8String().c_str(),keyString.GetUTF8String().c_str()));
	
	// some calls to IndexOfString use s1.CharCount - s2.CharCount for position
	// this should always return not found
	if (position < 0)
	{
		return -1;
	}

	// Simplify the algorithm below:  If we're searching for a zero-length string, we already know what the
	// answer will be
	if (keyLen == 0)
	{
		return -1;
	}
	
	for (CharCounter	i = position; i < myLen; i++)
	{
		if (keyLen > myLen - i)		// too short to match
		{
			return -1;
		}

		CharCounter	j = 0;
		CharCounter	k = i;
		
		while (GetWChar(k) == keyString.GetWChar(j))
		{
			j++;
			k++;
			if (j == keyLen)
			{
				return i;			// success!
			}

			// We must specifically check our lengths to break out of the loop because reading
			// past the end of a string with GetChar() above returns 0, WHICH IS A VALID CHARACTER!
			if (j >= keyLen || k >= myLen)
			{
				break;
			}
		}
	}

	return -1;		// failure
}

//----------------------------------------------------------------------
// LastIndexOfString
//
//		Find one string within the body of another, return starting location.
//		Used by exceptions to replace parameter strings like file names and directory names.
//
//		This routine is compatible with multibyte encodings.
//
//		EMBEDDING NOTE: Notice that it is possible to match a portion of a <XXXX> sequence used 
//		to embed foreign characters.
//
//----------------------------------------------------------------------
CharCounter PMString::LastIndexOfString(const PMString& keyString) const
{
	const int32 stringLength = fNumChars;
	for (int32 i = stringLength - 1; i >= 0; --i)
	{
		if (IndexOfString(keyString, i) != -1)
		{
			return i;
		}
	}

	return -1;
}


//----------------------------------------------------------------------
// IndexOfWChar/LastIndexOfWChar
//
//		Find one Unicode character within the Unicode version of a string, return its location in the Unicode string.
//
//		These routines are compatible with multibyte encodings.
//
//		NOTE: In InDesign 1.0 and 1.5, thes routine compared bytes - so while the find would succeed, the return
//		value was a byte offset instead of a character offset. It might also be a false character match in multibyte encodings.
//
//		EMBEDDING NOTE: Notice that it is possible to match a portion of a <XXXX> sequence used 
//		to embed foreign characters.
//
//		 																				- DJB 3/3/2000
//
//----------------------------------------------------------------------
int32 PMString::IndexOfWChar(UTF32TextChar wc, int32 position) const
{
	ASSERT(position >= 0);
	ASSERT(position <= CharCounter_GetInt32(this->CharCount()));
	
	if (position < 0)
	{
		return -1;
	}

	const int32 stringLength = fNumChars;
	for (int32 i = position; i < stringLength; ++i)
	{
		if (GetUTF32TextChar(i) == wc)
		{
			return i;
		}
	}
	return -1;
}

int32 PMString::LastIndexOfWChar(UTF32TextChar wc) const
{
	const int32 stringLength = fNumChars;
	for (int32 i = stringLength - 1; i >= 0; --i)
	{
		if (GetUTF32TextChar(i) == wc)
		{
			return i;
		}
	}

	return -1;
}

bool16 PMString::Contains(const PMString& searchString, CharCounter pos ) const
{
	return( IndexOfString(searchString, pos) >= 0 );
}

//----------------------------------------------------------------------
// BeginsWith
//
//		Check if a string begins with another from a specific position.
//
//		This routine is compatible with multibyte encodings.
//
//----------------------------------------------------------------------
bool16 PMString::BeginsWith(const PMString & searchString, CharCounter position) const
{
	ASSERT(position >= 0);
	ASSERT(position <= this->CharCount());

	CharCounter		searchLen = searchString.CharCount();
	CharCounter		myLen = CharCount();
	// make sure the strings being compared make sense. Comparing a string which has been translated to one which has not is a no-no.
	// we only allow it if one of the strings is empty, or if one is non-translatable
	ASSERT_MSG(myLen == 0 || searchLen == 0 || searchString.HasTranslated() == this->HasTranslated() || !IsTranslatable() || !searchString.IsTranslatable(), FORMAT_ARGS("Comparing translated string to non-translated string!(Strings are '%s' and '%s'", GetUTF8String().c_str(), searchString.GetUTF8String().c_str()));

	// this should always return not found
	if (position < 0)
	{
		return kFalse;
	}

	// If we're searching for a zero-length string or if our remaining string is smaller than searchString, we already know what the
	// answer will be
	if (searchLen == 0 || searchLen > (myLen - position))
	{
		return kFalse;
	}

	CharCounter i = position;
	bool16 beginsWith = kTrue;

	for (CharCounter j = 0; j < searchLen; ++j, ++i)
	{
		if (GetWChar(i) != searchString.GetWChar(j))
		{
			beginsWith = kFalse;		// failure
			break;
		}
	}

	return beginsWith;
}

bool16 PMString::ParseForEmbeddedCharacters()
{
	return StringUIEmbedding::ConvertEmbeddedCharacters(*this) > 0;
}

#pragma mark -
#pragma mark *COMPARE*
//----------------------------------------------------------------------
// Compare, operator ==, operator >, operator <
//
//		Compare two strings ala strcmp.
//
//		These routines are reasonably compatible with multibyte encodings. 
//		We await CoolType 3 to allow us to determine character offsets in platform strings.
//
//		 																				- DJB 3/3/2000
//
//----------------------------------------------------------------------
int32 PMString::Compare(bool16 casesensitive, const PMString &s) const
{
	uint32		l1 = CharCount();
	uint32		l2 = s.CharCount();

	// make sure the strings being compared make sense. Comparing a string which has been translated to one which has not is a no-no.
	// we only allow it if one of the strings is empty, or if one is non-translatable
	ASSERT_MSG(!l1 || !l2 || s.HasTranslated() == this->HasTranslated() || !IsTranslatable() || !s.IsTranslatable(),FORMAT_ARGS("Comparing translated string to non-translated string!(Strings are '%s' and '%s'",GetUTF8String().c_str(),s.GetUTF8String().c_str()));

	if (!l1 && !l2)
	{
		return 0; // empty strings are equal
	}
	else if (!l1)
	{
		return -1; // string1 < string2
	}
	else if (!l2)
	{
		return 1; // string1 > string2
	}

	// If not roman chars, then case sensitivity isn't possible yet. Unicode character sorting is the best we can do.
	//	I dont think it matters whether we use the Unicode or platform encoded Unicode version here, but the
	//	platform ones will have been cached by the calls to Length above...
	// (This version was used previously regardless of the script)
	if (casesensitive)
	{
//				return std::wcscmp((wchar_t*)UnicodeSavvyString::GrabUTF16Buffer(nil), (wchar_t*)s.GrabUTF16Buffer(nil));
		return UTF16TextCharCompare(UnicodeSavvyString::GrabUTF16Buffer(nil), s.GrabUTF16Buffer(nil));
	}
	else
	{
//can't use wchar_t in macho - return wcsicmp((wchar_t*)UnicodeSavvyString::GrabUTF16Buffer(nil), (wchar_t*)s.GrabUTF16Buffer(nil)); //wcsicmp only knows about roman chars
		UTF32TextChar c1,c2;
		UTF32TextChar cL1, cL2;
		int32 len = std::max( l1, l2 ) ;
		for (int32 pos = 0; pos < len; pos++)
		{
			c1 = GetWChar(pos);
			c2 = s.GetWChar(pos);
			cL1 = UnicodeClass::ToLower(c1);
			cL2 = UnicodeClass::ToLower(c2);
			if (cL1 != cL2)
				break;
		}
		
		return(cL1.GetValue() - cL2.GetValue());

	}
}

bool16 PMString::IsEqual(const PMString &s, bool8 casesensitive, bool8 limitCompareToShorterLength) const
{
	uint32		l1 = CharCount();
	uint32		l2 = s.CharCount();

	// make sure the strings being compared make sense. Comparing a string which has been translated to one which has not is a no-no.
	// we only allow it if one of the strings is empty, or if one is non-translatable
	ASSERT_MSG(!l1 || !l2 || s.HasTranslated() == this->HasTranslated() || !IsTranslatable() || !s.IsTranslatable(),FORMAT_ARGS("Comparing translated string to non-translated string!(Strings are '%s' and '%s'",GetUTF8String().c_str(),s.GetUTF8String().c_str()));
	
	if (!l1 && !l2)
	{
		return kTrue;
	}
	else if (!limitCompareToShorterLength && (l1 != l2))
	{
		return kFalse;
	}
	else
	{
		if (casesensitive)
		{
			l1 = fUTF16BufferLength;
			l2 = s.fUTF16BufferLength;
			int compLen = std::min(l1,l2); // if limitCompareToShorterLength is false, l1 == l2
			return std::memcmp(ConstBuffer(), s.ConstBuffer(), sizeof(textchar) * compLen) == 0;	
		}
		else
		{
			l1 = fNumChars;
			l2 = s.fNumChars;
			int compLen = std::min(l1,l2); // if limitCompareToShorterLength is false, l1 == l2
			UTF32TextChar c1,c2;
			UTF32TextChar cL1, cL2;
			int32 pos;
			for (pos = 0; pos < compLen; pos++)
			{
				c1 = GetWChar(pos);
				c2 = s.GetWChar(pos);
				cL1 = UnicodeClass::ToLower(c1);
				cL2 = UnicodeClass::ToLower(c2);
				if (cL1 != cL2)
					break;
			}
			
			return(pos == compLen);
		}
	}
}


#pragma mark -
#pragma mark *OPERATORS*

bool16 PMString::operator != (const PMString &s) const
{
	return (!(*this == s)); 
}

bool16 PMString::operator <= (const PMString &s) const
{
	return (!(*this > s)); 
}


bool16 PMString::operator >= (const PMString &s) const
{
	return (!(*this < s));
}


PMString& PMString::operator+=(const PMString& s)
{
	Append(s); return *this; 
}

bool16 PMString::operator == (const PMString &s) const
{
	
	if (this == &s)
		return kTrue;		// a == a
		
	// make sure the strings being compared make sense. Comparing a string which has been translated to one which has not is a no-no.
	// we only allow it if one of the strings is empty, or if one is non-translatable
	ASSERT_MSG(!fUTF16BufferLength || !s.fUTF16BufferLength || s.HasTranslated() == this->HasTranslated() || !IsTranslatable() || !s.IsTranslatable(),FORMAT_ARGS("Comparing translated string to non-translated string!(Strings are '%s' and '%s'",GetUTF8String().c_str(),s.GetUTF8String().c_str()));

	return this->UnicodeSavvyString::operator==(s);
}

bool16 PMString::operator == (ConstCString key) const
{
		
	uint32		l1 = CharCount();
	uint32		keyLength = static_cast<uint32>(::strlen(key));

#ifdef DEBUG
	//First we assert that what is passed in is indeed a key. as long as it is then we can do this
	//quick compare
	for (int i = 0; i < keyLength; i++)
	{
		if ((key[i] < 0x20) || ((key[i]&0x80) != 0))
		{
			ASSERT_FAIL("PMString == - Not a valid key. Trying to compare key with value < 0x20 or > 0x7F");
			break;
		}
	}
#endif

	// make sure the strings being compared make sense. Comparing a string which has been translated to one which has not is a no-no.
	// we only allow it if one of the strings is empty, or if one is non-translatable
	ASSERT_MSG(!l1 || !keyLength || !HasTranslated() || !IsTranslatable(),FORMAT_ARGS("Comparing translated string to non-translated string!(Strings are '%s' and '%s'",GetUTF8String().c_str(),key));
	
	if (!l1 && !keyLength)
	{
		return kTrue;
	}
	else if (l1 != keyLength)
	{
		return kFalse;
	}
	else
	{
		for (uint32 i = 0; i < l1; i++)
		{
			if (key[i] != ConstBuffer()[i])
				return kFalse;
		}
		return kTrue;
	}
}

bool16 PMString::operator < (const PMString &s) const
{
	// Do a case sensitive compare
	return Compare(kTrue, s) < 0;
}

bool16 PMString::operator > (const PMString &s) const
{
	return s < *this;
}


#pragma mark -
#pragma mark *MISC*

uint32 PMString::Hash(void) const
{
	const uint32 kHashMod = 33554393;
	
	uchar	*buf = nil;
	uint32	bufLength = 0;
	uint32	hash = 0;
	
	int32 numUTF16s = 0;
	buf = (uchar*) UnicodeSavvyString::GrabUTF16Buffer(&numUTF16s);
	bufLength = numUTF16s*sizeof(UTF16TextChar);
	
	if ( buf && bufLength )
	{
		hash = *buf++;
		
		for (int i = 1; i < bufLength; i++)
		{
			hash = ((hash * 32) + *buf++) % kHashMod;		
		}
	}
	
	return hash;
}

void PMString::AppendNumber(int32 i)
{
	CHECK_MY_INVARIANT();
	UTF16TextChar wBuff[13];
	UTF16TextChar* term = StringUtils::ConvertInt32ToUTF16(i, boost::begin(wBuff), boost::end(wBuff));

	AppendW(wBuff, (term - wBuff));
}

void PMString::AppendNumber(const PMReal& r,int32 digitsPrecision, bool16 round, bool16 eliminateTrailingZeros)
{
	ASSERT_MSG(round == kFalse || digitsPrecision >= 0,"PMString::AppendNumber() - What are you expecting this to do?");
	double d = ::ToDouble(r);
	if (digitsPrecision >= 0)
	{
		if (round)
		{
			int32 multiplier = (int32)std::pow((double)10,(int)digitsPrecision);
			PMReal numberToRound = r * 	multiplier;
			numberToRound = ::Round(numberToRound);	
			numberToRound /= multiplier;
			d = ::ToDouble(numberToRound);
		}
		else
		{
			// ----- We have to explicitly do the truncate because sprintf rounds. [amb 3-11-99]
			
			int32 multiplier = (int32)std::pow((double)10,(int)digitsPrecision);
			PMReal numberToRound = r * 	multiplier;
			numberToRound = ::Floor(numberToRound);	
			numberToRound /= multiplier;
			d = ::ToDouble(numberToRound);
		}
	}
	
	// "+(309 digits).(188 digits)\0" = 512, max 64bit float precision is 16-17 anyway
	ASSERT(digitsPrecision <= 188);
	char buff[512];
	
	// If the client want the most compact form, use David Gay's library.
	// Otherwise, do it the conventional way.
	// Crashes when precision is high
	if (eliminateTrailingZeros || (digitsPrecision < 0))
	{
		::g_dfmt(buff, &d, 0, sizeof(buff));
	}
	else
	{
		::sprintf(buff, "%-.*f", digitsPrecision, d);
	}

	// dwaterfa: Ths assert is designed to catch folks passing in uninitialized
	// values for d. This caused overflows in the original 256 byte buffer and
	// trashed the stack. If this causes someone pain for valid reasons just make
	// the number larger, but nothing in excess of 511.
	int	len = (int32)::strlen(buff);
	ASSERT_MSG(len < 96, "Are you sure you want a string this long");

	if (len > 0)
	{
		// Special formatting for numbers between -1 and 1
		int32 zeroPos = -1;

		if (buff[0] == '.')
		{
			ASSERT_MSG(d >= 0 && d < 1, "Number between 0 and 1 appears to be incorrectly formatted.");
			zeroPos = CharCount();	// Numbers between 0 and 1 (including 0)
		}
		else if (len > 1 && buff[0] == '-' && buff[1] == '.')
		{
			ASSERT_MSG(d > -1 && d < 0, "Number between -1 and 0 appears to be incorrectly formatted.");
			zeroPos = CharCount() + 1;	// Numbers between -1 and 0
		}

		UTF16TextChar wBuff[512];
		UTF16TextChar *unicodeBufferEnd = adobe::detail::to_utf16<UTF16TextChar>(buff, buff+len, wBuff, adobe::detail::unicode_size_type_<sizeof(char)>());
		UnicodeSavvyString::size_type wLen = unicodeBufferEnd - wBuff;
		AppendW(wBuff, wLen);

		// Insert a '0' as necessary, we always want at least one digit to the left of the decimal point.
		if (zeroPos != -1)
			InsertW(kTextChar_Zero, zeroPos);
	}
}

void PMString::AsNumber(int32 i)
{
	CHECK_MY_INVARIANT();
	UTF16TextChar wBuff[13];
	UTF16TextChar* term = StringUtils::ConvertInt32ToUTF16(i, boost::begin(wBuff), boost::end(wBuff) );
	
	SetXString(wBuff,(term - wBuff));
	SetTranslatable(kFalse); // if the whole string is a number, don't need to translate anything.
}

void PMString::AsNumber(const PMReal& r,int32 digitsPrecision, bool16 round, bool16 eliminateTrailingZeros)
{
	CHECK_MY_INVARIANT();
	clear();
	AppendNumber(r,digitsPrecision,round,eliminateTrailingZeros);
	SetTranslatable(kFalse); // if the whole string is a number, don't need to translate anything.
}

int32 PMString::GetAsNumber( ConversionError *pError, CharCounter *lenUnconverted /*= nil*/ ) const
{
	int32 num = 0;
	if(lenUnconverted)
	{
		*lenUnconverted = 0;
	}
	if( !empty() )
	{
		wchar_t* pEnd;
		wchar_t *tempWChar_tString;
		tempWChar_tString = new wchar_t[fUTF16BufferLength+1];
		GetWChar_tString(tempWChar_tString, fUTF16BufferLength+1);
		num = std::wcstol(tempWChar_tString,&pEnd,10);

		if(pEnd != nil && lenUnconverted != nil)
		{
			CharCounter  unconvertedLen = 0;
			WideString unconvertedString(pEnd);
			unconvertedLen = unconvertedString.CharCount();
			//ASSERT_MSG(unconvertedLen != 0, "unconvertedLen is 0");
			*lenUnconverted = unconvertedLen;
		}

		if( pError && (!pEnd || (std::wcslen(pEnd) == 0)))
		{
			*pError = kNoError;
		}
		else if( pError )
		{
			*pError = kNotJustNumber;
		}
		delete []tempWChar_tString;
	}
	else if( pError )
	{
		*pError = kNoNumber;
	}
	return num;
}

double  PMString::GetAsDouble( ConversionError *pError, CharCounter *lenUnconverted ) const
{		
	double num = 0.0;
	if(lenUnconverted)
	{
		*lenUnconverted = 0;
	}
	if( !empty() )
	{
		wchar_t* pEnd = nil;
		wchar_t *tempWChar_tString;
#ifdef qME_CS3
		PMString modifiedString;
		Utils<IWidgetUtils>()->StripUserDecimal(&modifiedString);
        tempWChar_tString = new wchar_t[modifiedString.WCharLength()+1];
		modifiedString.GetWChar_tString(tempWChar_tString, modifiedString.WCharLength()+1);
#else
		tempWChar_tString = new wchar_t[fUTF16BufferLength+1];
		GetWChar_tString(tempWChar_tString, fUTF16BufferLength+1);
#endif
		num = std::wcstod(tempWChar_tString,&pEnd);

		if(pEnd != nil && lenUnconverted != nil)
		{
			CharCounter  unconvertedLen = 0;
			WideString unconvertedString(pEnd);
			unconvertedLen = unconvertedString.CharCount();
			*lenUnconverted = unconvertedLen;
		}
			
		if(pError)
		{
			if(pEnd == nil || (std::wcslen(pEnd) == 0))
			{
				*pError = kNoError;
			}
			else
			{
				// some part of string didn't convert.				
				if(pEnd == tempWChar_tString)
				{
					// didn't convert anything.
					*pError = kNoNumber;
				}
				else
				{
					// converted part.
					*pError = kNotJustNumber;
				}
			}
		}
		delete []tempWChar_tString;
	}
	else if( pError )
	{
		*pError = kNoNumber;
	}
	return num;
}

void PMString::ToLower(void)
{
	//should use u_strToLower GetUserInterfaceICULocale 
	UTF16TextChar * buffer;
	buffer = GetBufferForWriting(fUTF16BufferLength);
	int32 nWchars = fUTF16BufferLength;
	for (int32 i = 0; i < nWchars; i++)
	{
		buffer[i] = UnicodeClass::ToLower(buffer[i]).GetValue();
	}

	// Ensure the terminating null
	buffer[fUTF16BufferLength] = 0;

	return;
}

void PMString::ToUpper(void)
{
	//should use u_strToUpper GetUserInterfaceICULocale 
	UTF16TextChar * buffer;
	buffer = GetBufferForWriting(fUTF16BufferLength);
	int32 nWchars = fUTF16BufferLength;
	for (int32 i = 0; i < nWchars; i++)
	{
		buffer[i] = UnicodeClass::ToUpper(buffer[i]).GetValue();
	}
	// Ensure the terminating null
	buffer[fUTF16BufferLength] = 0;

	return;
}

#pragma mark -
#pragma mark *READ/WRITE ROUTINES*
void PMString::ReadWrite(IPMStream *s)
{
	CHECK_MY_INVARIANT();
	// Store or fetch the format number and flags.
	uchar formatNumber = kPMStringFormatNumber;
	XferBoolsAndFormatNumber(s, formatNumber, 2, &fHasTranslated, &fShouldTranslate);

	if (s->IsReading())
	{
#if defined(DEBUG)
		fFormatNumber = formatNumber;
#endif
		// Figure out which format we're reading.
		switch (formatNumber)
		{
			case 0:
			case 1:
			case 2:
				{
					uchar	script = s->XferByte(script);
					
					if (script == 0xff)
						fEncoding = kUnknownEncoding;
					else
						fEncoding = (StringEncoding) script;

					ReadUnicode(s);
				}
				break;
				
			default:
				ASSERT_FAIL(FORMAT_ARGS("PMString::ReadWrite - Unknown format number (%d) while reading.", formatNumber));
				break;
		}
	}
	else
	{
#if defined(DEBUG)
		if (fFormatNumber != kPMStringFormatNumber)
		{
			// Give our caller a clue that we may change the data without Dirty() being called.
			// (Note: This call is a No-op in the Release build.)
			StreamUtil::SetStreamContentsChanged(s);
		}
#endif

		// This is Format #1, but it is really the same as Format #0.
		// The number was bumped because ReadWritePlatformEncoding() changed.

		// ----- Limit the length written and read to an uint16 until the resource compiler
		//		 is changed to support strings with a 4 byte length. [amb]
		uchar script = (uchar)fEncoding;
		s->XferByte(script);

		WriteUnicode(s);
	}
}

void PMString::ReadUnicode(IPMStream *s)
{
	//Note:this is a number of Unicode characters
	uint16	unicodeLen = s->XferInt16((int16&)unicodeLen);
	fNumChars = fUTF16BufferLength = 0;
	UTF16TextChar * unicodeBuffer = GetBufferForWriting(unicodeLen);
	fUTF16BufferLength = unicodeLen;

	// this can happen if we are mis-aligned, and end up reading data
	// that is not really a number.  In debug, we issue an error.  In release
	// we fall back to an empty string.  Note that w/o this code, we would
	// attempt to allocate a negative (read very large positive) UTF16TextChar array below.
	if( fUTF16BufferLength < 0 )
	{
		ASSERT_FAIL( "PMString::ReadWrite: read negative string length, reading string at wrong offset?" );
		fUTF16BufferLength = 0;
	};

	// Read the string
	if(fUTF16BufferLength)
	{
		CompressInt_Read	reader(s);
		for (int32 i = 0; i < fUTF16BufferLength; i++)
		{
			unicodeBuffer[i] = (uint16)reader.Read();
		}
	}

	// Ensure the terminating null
	unicodeBuffer[fUTF16BufferLength] = 0;
	fNumChars = CountChars();
}

void PMString::WriteUnicode(IPMStream *s)
{
	ASSERT_MSG(fUTF16BufferLength <= 32768, FORMAT_ARGS("PMString::ReadWrite - PMString length is %d", fUTF16BufferLength));

	uint16 shortLen = fUTF16BufferLength;

	s->XferInt16((int16&)shortLen);
	
	s->Comment("\"");

	if(UnicodeSavvyString::NumUTF16TextChars())
	{
		CompressInt_Write	writer(s);
		for (int32 i = 0; i < shortLen; i++)
		{
			writer.Write((int16)ConstBuffer()[i]);	
		}
	}
		
	s->Comment("\",");
}


static const UTF16TextChar k_WinToUnicodeConverter[] =
{
	0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x000A, 0x000B, 0x000C, 0x000D, 0x000E, 0x000F,
	0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017, 0x0018, 0x0019, 0x001A, 0x001B, 0x001C, 0x001D, 0x001E, 0x001F,
	0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002A, 0x002B, 0x002C, 0x002D, 0x002E, 0x002F,
	0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x003F,
	0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 0x0048, 0x0049, 0x004A, 0x004B, 0x004C, 0x004D, 0x004E, 0x004F,
	0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 0x0058, 0x0059, 0x005A, 0x005B, 0x005C, 0x005D, 0x005E, 0x005F,
	0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067, 0x0068, 0x0069, 0x006A, 0x006B, 0x006C, 0x006D, 0x006E, 0x006F,
	0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077, 0x0078, 0x0079, 0x007A, 0x007B, 0x007C, 0x007D, 0x007E, 0x007F,

	0x20AC, 0x0081, 0x201A, 0x0192, 0x201E, 0x2026, 0x2020, 0x2021, 0x02C6, 0x2030, 0x0160, 0x2039, 0x0152, 0x008D, 0x008E, 0x008F,
	0x0090, 0x2018, 0x2019, 0x201C, 0x201D, 0x2022, 0x2013, 0x2014, 0x02DC, 0x2122, 0x0161, 0x203A, 0x0153, 0x009D, 0x017E, 0x0178,
	0x00A0, 0x00A1, 0x00A2, 0x00A3, 0x00A4, 0x00A5, 0x00A6, 0x00A7, 0x00A8, 0x00A9, 0x00AA, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x00AF,
	0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x00B4, 0x00B5, 0x00B6, 0x00B7, 0x00B8, 0x00B9, 0x00BA, 0x00BB, 0x00BC, 0x00BD, 0x00BE, 0x00BF,
	0x00C0, 0x00C1, 0x00C2, 0x00C3, 0x00C4, 0x00C5, 0x00C6, 0x00C7, 0x00C8, 0x00C9, 0x00CA, 0x00CB, 0x00CC, 0x00CD, 0x00CE, 0x00CF,
	0x00D0, 0x00D1, 0x00D2, 0x00D3, 0x00D4, 0x00D5, 0x00D6, 0x00D7, 0x00D8, 0x00D9, 0x00DA, 0x00DB, 0x00DC, 0x00DD, 0x00DE, 0x00DF,
	0x00E0, 0x00E1, 0x00E2, 0x00E3, 0x00E4, 0x00E5, 0x00E6, 0x00E7, 0x00E8, 0x00E9, 0x00EA, 0x00EB, 0x00EC, 0x00ED, 0x00EE, 0x00EF,
	0x00F0, 0x00F1, 0x00F2, 0x00F3, 0x00F4, 0x00F5, 0x00F6, 0x00F7, 0x00F8, 0x00F9, 0x00FA, 0x00FB, 0x00FC, 0x00FD, 0x00FE, 0x00FF
};

static const UTF16TextChar k_MacToUnicodeConverter[] =
{
	0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x000A, 0x000B, 0x000C, 0x000D, 0x000E, 0x000F,
	0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017, 0x0018, 0x0019, 0x001A, 0x001B, 0x001C, 0x001D, 0x001E, 0x001F,
	0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002A, 0x002B, 0x002C, 0x002D, 0x002E, 0x002F,
	0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x003F,
	0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 0x0048, 0x0049, 0x004A, 0x004B, 0x004C, 0x004D, 0x004E, 0x004F,
	0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 0x0058, 0x0059, 0x005A, 0x005B, 0x005C, 0x005D, 0x005E, 0x005F,
	0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067, 0x0068, 0x0069, 0x006A, 0x006B, 0x006C, 0x006D, 0x006E, 0x006F,
	0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077, 0x0078, 0x0079, 0x007A, 0x007B, 0x007C, 0x007D, 0x007E, 0x007F,
	
	0x00C4, 0x00C5, 0x00C7, 0x00C9, 0x00D1, 0x00D6, 0x00DC, 0x00E1, 0x00E0, 0x00E2, 0x00E4, 0x00E3, 0x00E5, 0x00E7, 0x00E9, 0x00E8,
	0x00EA, 0x00EB, 0x00ED, 0x00EC, 0x00EE, 0x00EF, 0x00F1, 0x00F3, 0x00F2, 0x00F4, 0x00F6, 0x00F5, 0x00FA, 0x00F9, 0x00FB, 0x00FC,
	0x2020, 0x00B0, 0x00A2, 0x00A3, 0x00A7, 0x2022, 0x00B6, 0x00DF, 0x00AE, 0x00A9, 0x2122, 0x00B4, 0x00A8, 0x2260, 0x00C6, 0x00D8,
	0x221E, 0x00B1, 0x2264, 0x2265, 0x00A5, 0x00B5, 0x2202, 0x2211, 0x220F, 0x03C0, 0x222B, 0x00AA, 0x00BA, 0x03A9, 0x00E6, 0x00F8,
	0x00BF, 0x00A1, 0x00AC, 0x221A, 0x0192, 0x2248, 0x2206, 0x00AB, 0x00BB, 0x2026, 0x00A0, 0x00C0, 0x00C3, 0x00D5, 0x0152, 0x0153,
	0x2013, 0x2014, 0x201C, 0x201D, 0x2018, 0x2019, 0x00F7, 0x25CA, 0x00FF, 0x0178, 0x2044, 0x20AC, 0x2039, 0x203A, 0xFB01, 0xFB02,
	0x2021, 0x00B7, 0x201A, 0x201E, 0x2030, 0x00C2, 0x00CA, 0x00C1, 0x00CB, 0x00C8, 0x00CD, 0x00CE, 0x00CF, 0x00CC, 0x00D3, 0x00D4,
	0xF8FF, 0x00D2, 0x00DA, 0x00DB, 0x00D9, 0x0131, 0x02C6, 0x02DC, 0x00AF, 0x02D8, 0x02D9, 0x02DA, 0x00B8, 0x02DD, 0x02DB, 0x02C7 
};

void PMString::ReadPlatformWriteUnicode(IPMStream *s, PMString::StringPlatformEncoding encoding, bool16 includeBools)
{
	CHECK_MY_INVARIANT();
	ASSERT_IF_WRITING_TO_DOCUMENT(s);
	// [shp]

	// Store or fetch the format number and flags.
	uchar formatNumber = 0;
	
	if (s->IsReading())
	{
		if (includeBools)
			XferBoolsAndFormatNumber(s, formatNumber, 2, &fHasTranslated, &fShouldTranslate);
		else
		{
			fShouldTranslate = kTrue;
			fHasTranslated = kFalse;
		}
		fUTF16BufferLength = fNumChars = 0;
						
		// Figure out which format we're reading.
		switch (formatNumber)
		{
  		case 0:
			{
				if (includeBools)
					s->XferBool(fHasTranslated);	// fHasTranslated is really in a bool16 all by itself.
				if (encoding == kPlatformEncodingOther)
				{
					uint16 shortLen;
					s->XferInt16((int16&)shortLen);
					if (shortLen)
					{
						char* tempPlatBuffer;
						tempPlatBuffer = new char[shortLen];
						s->XferByte((uchar*)tempPlatBuffer, shortLen);
						SetUTF16Buffer(tempPlatBuffer, shortLen, fEncoding);
						delete[] tempPlatBuffer;
					}
				}
				else
				{
					// read and convert platform to unicode
					uint16 unicodeLen = s->XferInt16((int16&)unicodeLen);
					UTF16TextChar * unicodeBuffer = GetBufferForWriting(unicodeLen);
					fUTF16BufferLength = unicodeLen;

					// this can happen if we are mis-aligned, and end up reading data
					// that is not really a number.  In debug, we issue an error.  In release
					// we fall back to an empty string.  Note that w/o this code, we would
					// attempt to allocate a negative (read very large positive) UTF16TextChar array below.
					if( fUTF16BufferLength < 0 )
					{
						ASSERT_FAIL( "PMString::ReadWrite: read negative string length, reading string at wrong offset?" );
						fUTF16BufferLength = 0;
					};

					// Read the string
					if(fUTF16BufferLength)
					{
						// This isn't as dangerous as it sounds.
						uchar *platformBuffer = (uchar*)unicodeBuffer+fUTF16BufferLength; //reuse already allocated memory to improve performance
						s->XferByte(platformBuffer, unicodeLen);

						if (encoding == kUTF8Encoding)
						{
							try
							{
								UTF16TextChar *unicodeBufferEnd = adobe::detail::to_utf16<UTF16TextChar>(platformBuffer,platformBuffer+unicodeLen, unicodeBuffer, adobe::detail::unicode_size_type_<sizeof(char)>());
								fUTF16BufferLength = unicodeBufferEnd - unicodeBuffer;
								ASSERT_MSG((unicodeLen == 0 || fUTF16BufferLength > 0) && fUTF16BufferLength <= unicodeLen, "Error converting UTF8 string");
							}
							catch(std::runtime_error &error)
							{
								ASSERT_FAIL(FORMAT_ARGS("PMString::ReadPlatformWriteUnicode - Error converting UTF8 string - %s", error.what()));

								throw error;
							}
						}
						else
						{
							// convert to unicode
							const UTF16TextChar *platformToUnicode;
							if (encoding == kPlatformEncodingWin)
								platformToUnicode = k_WinToUnicodeConverter;
							else if (encoding == kPlatformEncodingMac)
								platformToUnicode = k_MacToUnicodeConverter;
							else
							{
								ASSERT_FAIL("Unsupported encoding");
								// Assume encoding of current platform and see where that leads us instead of a dangling pointer crash.
#ifdef WINDOWS
								platformToUnicode = k_WinToUnicodeConverter;
#else
								platformToUnicode = k_MacToUnicodeConverter;
#endif
							}

							for (int32 i = 0; i < fUTF16BufferLength; i++)
							{
								unicodeBuffer[i] = platformToUnicode[platformBuffer[i]];
							}
						}
					}
					// Ensure the terminating null
					unicodeBuffer[fUTF16BufferLength] = 0;

					fNumChars = CountChars();
				}
			}
			break;
		case 3:
			{
				ReadUnicode(s);
			}
			break;
		default:
			// Unsupported format.
			ASSERT_FAIL(FORMAT_ARGS("PMString::ReadPlatformWriteUnicode - Unknown format number (%d)", formatNumber));
			break;
		}
	}
	else	// Writing
	{
#if defined(DEBUG)
		// Give our caller a clue that we may change the data without Dirty() being called.
		// (Note: This call is a No-op in the Release build.)
		StreamUtil::SetStreamContentsChanged(s);
#endif
		if (includeBools)
		{
			formatNumber = 3;
			XferBoolsAndFormatNumber(s, formatNumber, 2, &fHasTranslated, &fShouldTranslate);
		}

		WriteUnicode(s);
	}
}

#pragma mark -
#pragma mark *TRANSLATE ROUTINES*
bool16 PMString::Translate(const PMLocaleId& locale)
{
	CHECK_MY_INVARIANT();
	if (fShouldTranslate && !fHasTranslated)
	{
		if (CharCount() > 0)
		{
			bool16 result = kFalse;
			InterfacePtr<IStringDataBase> sdb(GetExecutionContextSession(), IID_ISTRINGDATABASE);
			if( sdb )	
			{
				result = sdb->Retrieve(locale, *this, *this);
			}
			
			// note: this member must be changed after the call to Retrieve, because therein we
			// actually change what 'this' is.
			fHasTranslated = kTrue;
			return result;
		}
		else
		{
			fHasTranslated = kTrue;
		}
	}
	
	return kTrue;
}

bool16 PMString::Translate()
{
	return Translate(LocaleSetting::GetLocale());
}

#pragma mark -
#pragma mark *DISCOURAGED TRANSLATE ROUTINES*
bool16 PMString::IsTranslatable() const
{
	return fShouldTranslate;
}

PMString& PMString::SetTranslatable(bool16 shouldTranslate) 
{
	fShouldTranslate = shouldTranslate; return *this; 
}

bool16 PMString::HasTranslated() const 
{
	return fHasTranslated; 
}

		// SetTranslated should not usually be called. It is only used when we get a string the user typed in,
		// so we know it is translated, but it isn't marked that way.
void PMString::SetTranslated()
{
	fHasTranslated = kTrue;  
}

#pragma mark -
#pragma mark *DISCOURAGED PLATFORM STRING ROUTINES*
PMString::PMString(ConstCString string, StringEncoding encoding) :
#if defined(DEBUG)
	fFormatNumber(kPMStringFormatNumber),
#endif
	fShouldTranslate(kFalse),
	fHasTranslated(kFalse)
{
	fEncoding = (StringEncoding)((encoding == kUnknownEncoding) ? LocaleSetting::GetSystemScript() : encoding);
	CHECK_MY_INVARIANT();
	
	SetCString(string, fEncoding);
}

void PMString::SetPString(ConstPString p, PMString::StringEncoding encoding)
{
	CHECK_MY_INVARIANT();
	ASSERT(p != nil);

	if (encoding != kUnknownEncoding)
	{
		fEncoding = encoding;
	}

	fHasTranslated = kFalse;
	fShouldTranslate = kFalse;

	SetUTF16Buffer((ConstCString)p+1, p[0], fEncoding);
}

void PMString::SetCString(ConstCString c, PMString::StringEncoding encoding)
{
	CHECK_MY_INVARIANT();
	ASSERT(c != nil);

	if (encoding != kUnknownEncoding)
	{
		fEncoding = encoding;
	}
	
	int32	len = (int32)std::strlen((char *)c);

	if (len == 0)
	{
		clear();
		fShouldTranslate = kFalse;
		return;
	}
	
	fShouldTranslate = kFalse;
	fHasTranslated = kFalse;

	SetUTF16Buffer(c, len, fEncoding);
}

void PMString::SetXString(const char* x, int32 nBytes, PMString::StringEncoding encoding)
{
	CHECK_MY_INVARIANT();
	ASSERT(x != nil);
	ASSERT(nBytes >= 0);

	fEncoding = (StringEncoding)((encoding == kUnknownEncoding) ? LocaleSetting::GetSystemScript() : encoding);

	SetUTF16Buffer(x, nBytes, fEncoding);
}

void PMString::SetUTF16Buffer(const char* x, int32 nBytes, PMString::StringEncoding encoding)
{
	//TODO: GetBufferForWriting doesn't allocate enough if the string tranlates to surrogates.
	UTF16TextChar * buffer = GetBufferForWriting(nBytes);
	int32 numChars = 0;
	if(nBytes)
	{
		numChars = ::TranslateCharToTextChar( x, nBytes, buffer, nBytes, encoding );
	}
	buffer[numChars] = 0;
	fUTF16BufferLength = numChars;

	fNumChars = CountChars();
}

void PMString::GetPString(PString p, int32 bufferSize, PMString::StringEncoding encoding) const
{
	ASSERT(p != nil);
	ASSERT(bufferSize >= 0);
	// WARNING this function does not null terminate the buffer	
	int32 lengthInBytes = GetPlatformBuffer((char*)p+1, bufferSize, encoding);

	// Make sure the target buffer is big enough.
	if (lengthInBytes + 1 > bufferSize)
	{
		return;
	}

	p[0] = LengthPrefix(lengthInBytes);
}



void PMString::GetCString(CString c, int32 bufferSize, PMString::StringEncoding encoding) const
{
	ASSERT(c != nil);
	ASSERT(bufferSize >= 0);

	int32 lengthInBytes = GetPlatformBuffer(c, bufferSize, encoding);

	// Make sure the target buffer is big enough.
	if (bufferSize > lengthInBytes)
	{
		c[lengthInBytes] = 0;
	}
}


std::string PMString::GetPlatformString(PMString::StringEncoding encoding) const
{
	//optimize by using std::string directly instead of new char[bufferSize]
	int32 bufferSize = BytesNeededToEmbedUnicodeChars(ConstBuffer(), fUTF16BufferLength) + 1;
	char *platformBuffer = new char[bufferSize];
	int32 lengthInBytes = GetPlatformBuffer(platformBuffer, bufferSize, encoding);
	platformBuffer[lengthInBytes] = 0;
	std::string retString(platformBuffer);
	delete[] platformBuffer;
	
	return retString;
}

int32 PMString::GetPlatformBuffer(char *buffer, int32 bufferSize, PMString::StringEncoding encoding) const
{
	if (buffer == nil || bufferSize == 0)
		return 0;

	if (encoding == kUnknownEncoding)
		 encoding = fEncoding;
 	
 	int32 lengthInBytes = 0;
 	
	if (fNumChars > bufferSize)
		return fNumChars;

	if (fNumChars > 0)
	{
 		bool16 foundMissingChar;
		lengthInBytes = ::TranslateTextCharToEmbeddedChar( ConstBuffer(), fUTF16BufferLength, buffer, bufferSize-1, encoding, foundMissingChar );
	}
	
	return lengthInBytes;
}

void PMString::ReadWriteKey(IPMStream *s)
{
	if (s->IsReading())
	{
		fShouldTranslate = kTrue;
		fHasTranslated = kFalse;
		fUTF16BufferLength = fNumChars = 0;

		// read and convert platform to unicode
		uint16 shortLen;
		s->XferInt16((int16&)shortLen);
		UTF16TextChar * unicodeBuffer = GetBufferForWriting(shortLen);
		fUTF16BufferLength = shortLen;
		// Read the string
		if(fUTF16BufferLength)
		{
			// This isn't as dangerous as it sounds.
			uchar *platformBuffer = (uchar*)unicodeBuffer+fUTF16BufferLength; //reuse already allocated memory to improve performance
			s->XferByte(platformBuffer, shortLen);

			try
			{
				UTF16TextChar *unicodeBufferEnd = adobe::detail::to_utf16<UTF16TextChar>(platformBuffer,platformBuffer+shortLen, unicodeBuffer, adobe::detail::unicode_size_type_<sizeof(char)>());
				fUTF16BufferLength = unicodeBufferEnd - unicodeBuffer;
				ASSERT_MSG((shortLen == 0 || fUTF16BufferLength > 0) && fUTF16BufferLength <= shortLen, "Error converting UTF8 string");
			}
			catch(std::runtime_error &error)
			{
				ASSERT_FAIL(FORMAT_ARGS("PMString::ReadPlatformWriteUnicode - Error converting UTF8 string - %s", error.what()));

				throw error;
			}
		}

		// Ensure the terminating null
		unicodeBuffer[fUTF16BufferLength] = 0;

		fNumChars = CountChars();
	}
	else	// Writing
	{
		ASSERT(!fHasTranslated);

		std::string nameStdString;
		try
		{
			adobe::detail::to_utf8<char>(this->begin(), this->end(), std::back_inserter(nameStdString), adobe::detail::unicode_size_type_<sizeof(UTF16TextChar)>());
		}
		catch(std::runtime_error &error)
		{
			ASSERT_FAIL(FORMAT_ARGS("PMString::ReadWriteKey - Error converting to UTF8 string - %s", error.what()));

			throw error;
		}
		StringUtils::WriteStdString(s, nameStdString);
	}
}

///////////////////////////////////////////////////////
// Platform buffer access
///////////////////////////////////////////////////////

//----------------------------------------------------------------------
// IndexOfCharacter/LastIndexOfCharacter
//
//		Find one character within the body of a string, return its location.
//
//		These routines are compatible with multibyte encodings.
//
//		NOTE: In InDesign 1.0 and 1.5, these routine took char parameters and compared bytes - so while the find might succeed, 
//		it might be a false character match in multibyte encodings. Also, the return value was a byte offset instead of a character offset. 
//
//----------------------------------------------------------------------
CharCounter PMString::IndexOfCharacter(const PlatformChar &c, CharCounter position) const
{
	ASSERT(position >= 0);
	
	if (position > CharCount() - 1)
	{
		return -1;
	}
	
	CharCounter stringLength = CharCount();
	
	for (CharCounter i = position; i < stringLength; ++i)
	{
		if (GetChar(i, kUnknownEncoding) == c)
		{
			return i;
		}
	}
	return -1;
}


const PlatformChar PMString::operator[](CharCounter index) const
{
	return GetChar(index, kUnknownEncoding); 
}


CharCounter PMString::LastIndexOfCharacter(const PlatformChar &c) const
{
	if (CharCount() == 0)
	{
		return -1;
	}

	for (CharCounter i = CharCount() - 1; i >= 0; --i)
	{
		if (GetChar(i, kUnknownEncoding) == c)
		{
			return i;
		}
	}
	return -1;
}

	
#pragma mark -
// platform strings
void PMString::Append(const char* ps, int32 nBytes, PMString::StringEncoding encoding)
{
	Insert(ps, nBytes, fNumChars, encoding);
}

// platform characters
void PMString::Append(char pc, PMString::StringEncoding encoding)
{
	Append(&pc, 1, encoding);
}

void PMString::Append(const PlatformChar &pc)
{
	Insert(pc, fNumChars);
}

#pragma mark -
// platform characters
void PMString::Insert(char pc, CharCounter pos, PMString::StringEncoding encoding)
{
	if (pos < 0)
	{
		return;
	}

	Insert(&pc, 1, pos, encoding);
}

void PMString::Insert(const PlatformChar &pc, CharCounter pos)
{
	CHECK_MY_INVARIANT();
	if (pos < 0)
	{
		return;
	}
	
	// Must behave differently for 1 vs 2 byte character values
	if (pc.IsTwoByte())
	{
		char bytes[2];
		bytes[0] = pc.HighByte();
		bytes[1] = pc.LowByte();
		Insert(bytes, 2, pos, (StringEncoding)pc.GetScript());
	}
	else
	{
		char lowerbyte = pc.LowByte();
		Insert(&lowerbyte, 1, pos,  (StringEncoding)pc.GetScript());
	}		
}

// platform strings
void PMString::Insert(const char* c, int32 nBytes, CharCounter pos, PMString::StringEncoding encoding)
{
	CHECK_MY_INVARIANT();
	ASSERT(c != nil || nBytes == 0);
	ASSERT(pos >= 0);
	ASSERT(pos <= this->CharCount());
	ASSERT(nBytes >= 0);
	
	// if length wasn't specified, use strlen to find the length of the buffer passed in
	if (c && nBytes == kMaxInt32)
	{
		nBytes = (int32)::strlen(c);
	}

	if (c && nBytes)
	{
		int16 cEncoding = (encoding == kUnknownEncoding) ? fEncoding : encoding;
		UTF16TextChar *newWbuf = new UTF16TextChar[nBytes+1];
		int32 numChars = ::TranslateCharToTextChar( c, nBytes, newWbuf, nBytes, cEncoding );
		InsertW(newWbuf, numChars, pos);
		delete[] newWbuf;
	}
}


#pragma mark -
//----------------------------------------------------------------------
// GetChar
//
//		Returns the platform encoded character at a specific character offset into the platform string representation. 
//		(This routine is multibyte character safe)
//	
//		NOTE: CoolType 3.0 allows some platform characters to encode to multiple Unicode characters.
//			In situations where such characters are present, this routine may return the wrong platform character - DJB 2/22/2000
//
//		NOTE: position is now interpreted as a character offset. This offset is measured in platform character space.
//			Using platform character space allows retrieval of the <XXXX> character sequences used to embed foreign characters.
//----------------------------------------------------------------------
const PlatformChar PMString::GetChar(CharCounter pos, PMString::StringEncoding encoding) const
{
	PlatformChar returnChar;

	ASSERT_MSG(pos >= 0 && pos < fNumChars, "PMString::GetChar - invalid index");

	UTF32TextChar unicodeChar32 (GetUTF32TextChar(pos));
	int16 cEncoding = (encoding == kUnknownEncoding) ? fEncoding : encoding;
	return TextCharToPlatformChar(unicodeChar32, cEncoding);
}

//----------------------------------------------------------------------
// TranslateTextCharToEmbeddedChar
//
//		This routine takes a wide char string and translates it into a platform
//		string with embedded unicode characters in a human readable/writable format.
//
//----------------------------------------------------------------------
int32 TranslateTextCharToEmbeddedChar(const UTF16TextChar* fromString, long fromStrNumUTF16s, char* toStringBuffer, long toStrBufferLength, int16 writingscript, bool16 &foundMissingChar2)
{
	ASSERT_MSG(toStrBufferLength >= fromStrNumUTF16s, "Each UTF16 maps to at least one byte of platform character: toStrBufferLength isn't sufficient");
	int32 nChars = 0;
	int32 nBytesWritten = 0;
	int32 nBytesTranslated = 0;

	bool16 foundMissingChar = kFalse;
	foundMissingChar2 = kFalse;
	
	UTF16TextChar *fromWCharPtr = (UTF16TextChar *) fromString;
	int32 fromStrWCharsRemaining = fromStrNumUTF16s;
	
	char *toCharPtr = toStringBuffer;
	int32 toBufferBytesRemaining = toStrBufferLength;
	
	while (fromStrWCharsRemaining > 0 && toBufferBytesRemaining > 0 )
	{
		int32 wChars2Attempt2Translate = fromStrWCharsRemaining;
		foundMissingChar = kFalse;

	
		// Let the Unicode translator try its luck. 
		//	This will stop at the first character that can't be mapped back into the platform encoding
		if (wChars2Attempt2Translate > 0)
		{
			nBytesWritten = ::CTUnicodeTranslator::Instance()->TextCharToChar_Exact(fromWCharPtr, wChars2Attempt2Translate, toCharPtr, toBufferBytesRemaining,
																					foundMissingChar, nBytesTranslated, writingscript);

			nChars += nBytesWritten;							// advance number of bytes written
			fromWCharPtr += nBytesTranslated/sizeof(UTF16TextChar);	// advance to the next wide char to translate
			fromStrWCharsRemaining -= nBytesTranslated/sizeof(UTF16TextChar); // how many wide chars left to translate
			toCharPtr += nBytesWritten;							// the next character to be written
			toBufferBytesRemaining -= nBytesWritten;			// how much space left to in the "to" buffer
			
			// CoolType translation can also fail benignly and just not translate anything.
			//	this often happens when Font cmaps are missing. 
			//	i.e Opening a japanese pub on a roman system without japanese cmaps, deleting a cmap while K2 is running.
			// Treat the unicode as non-embeddable characters.
			if (nBytesWritten == 0)
			{
				foundMissingChar = kTrue;
			}
		}
		
		if (foundMissingChar)
		{
			foundMissingChar2 = kTrue;
			// Now comes the hard part!
			// These bytes could potentially be surrogates, so build a proper character from the buffer

			// TODO: Provide a constructor on UTF32TextChar that will do this for us
			UTF32TextChar missingChar(UnicodeClass::IsHighSurrogate(*fromWCharPtr) && toBufferBytesRemaining > 2 ? 
							(*fromWCharPtr - 0xD800) * 0x400 + (fromWCharPtr[1] - 0xDC00) + 0x10000 :
							*fromWCharPtr);
			nBytesWritten = EmbedWideCharInCharString(missingChar, toCharPtr, toBufferBytesRemaining, writingscript);
			
			nChars += nBytesWritten;						// advance number of bytes written to embed unicode
			if (missingChar.isExtraWide())
			{
				fromWCharPtr += 2;
				fromStrWCharsRemaining -= 2;						// how many wide chars left to translate
			}
			else
			{
				fromWCharPtr += 1;								// advance to the next wide char to translate
				fromStrWCharsRemaining -= 1;						// how many wide chars left to translate
			}
			toCharPtr += nBytesWritten;						// the next character to be written
			toBufferBytesRemaining -= nBytesWritten;		// how much space left to in the "to" buffer
		}
	}

	return nChars;
}

//----------------------------------------------------------------------
// BytesNeededToEmbedUnicodeChars
//
//		This routine looks at a wide char string and estimates the number of
//		bytes needed to embed the Unicode chars not found in the platform encoding.
//
//		NOTE: This is only an estimate, especially in non-roman scripts, 
//			  and may not be conservative enough...
//
//----------------------------------------------------------------------
int32 BytesNeededToEmbedUnicodeChars(const UTF16TextChar* fromString, long numUTF16s)
{
	int32 nBytes = numUTF16s;
	
	for (long i = 0; i < numUTF16s; i++)
	{
		UTF16TextChar fromCharW = *fromString++;
		if (fromCharW & 0xFF80)		/* 0xFF80 since high-bit ascii values may be unicode, too */
		{
			nBytes += kBytesPerUnicodeChar - 1;
		}
	} 
	
	return nBytes;
}

//----------------------------------------------------------------------
// EmbedWideCharInCharString
//
//		This routine takes a wide char and translates it into a platform
//		string with embedded unicode characters in a human readable/writable format.
//
//----------------------------------------------------------------------
int32 EmbedWideCharInCharString(UTF32TextChar w, char* toBuffer, int32 toBufferLen, int16 writingscript)
{
	UTF16TextChar wBuffer[9];
	int32 nBytesWritten = 0;

	ASSERT(w != kEmbeddedUnicodePrefixChar);

	// Which character to translate?
	if (w.GetValue() < 0x10000 && std::iswcntrl(w.GetValue()))
	{
		// GetValue() is known to be safe here since we've verified the value is within a 16-bit range
		wBuffer[0] = (UTF16TextChar) w.GetValue();
		nBytesWritten = ::CTUnicodeTranslator::Instance()->TextCharToChar(wBuffer, 1, toBuffer, toBufferLen, writingscript);
	}
	else
	{
		int32 index = 9;
		StringUIEmbedding::EmbedCharacter(w, wBuffer, &index);
		nBytesWritten = ::CTUnicodeTranslator::Instance()->TextCharToChar(wBuffer, index, toBuffer, toBufferLen, writingscript);
	}
	
	return nBytesWritten;
}

///////////////////////////////////////////////////////
// Unicode buffer access
///////////////////////////////////////////////////////


// Counts the number of characters in the UNICODE buffer
int32 PMString::CountChars() const
{
	// Refactoring is a lovely thing.  UnicodeSavvyString has a CountChars that does the same thing as this function.  In fact, UnicodeSavvyString is a parent of this class
	// So why do we have a separate, equivalent implementation here?
	// Because...
	// PMString doesn't store its "number of characters" in its written form, so CountChars on a PMString gets called during a depersist through ReadWrite, and THAT can
	// happen before the utilities class that UnicodeSavvyString's implementation relies on has been constructed.
	int32 count = 0;
	int32 i;
	const UTF16TextChar * buffer = ConstBuffer();
	for (i = 0; i < fUTF16BufferLength ; i++)
	{
		if (UnicodeClass::IsHighSurrogate(buffer[i]))
		{
			ASSERT(/*i + 1 < length &&*/ UnicodeClass::IsLowSurrogate(buffer[i + 1]));	// lets caller use length as an offset into larger buffer
			i++;
			if (i >= fUTF16BufferLength)
			{
				break;
			}
		}
		count++;
	}
	return count;
}


PlatformChar TextCharToPlatformChar(UTF32TextChar &utf32, int8 encoding)
{
	const int32 bufferlen = 2;
	int32 buflen=bufferlen;
	UTF16TextChar buf[bufferlen];
	utf32.ToUTF16(buf, &buflen);
	uchar toBuffer[2];
	int32 toBufferLen = 2;

	bool16 stoppedFlag;
	int32 bytesTranslated = 0;
	
	int32 nBytesWritten = ::CTUnicodeTranslator::Instance()->TextCharToChar_Exact(buf, utf32.isExtraWide() ? 2 : 1, (char *) toBuffer, toBufferLen, stoppedFlag, bytesTranslated, encoding);
	if (nBytesWritten == 0 || bytesTranslated == 0)
	{
		// Create an invalid platform character, since we couldn't translate the Unicode
		return PlatformChar((uchar16) 0, encoding);
	}
	return nBytesWritten == 1 ? PlatformChar((uchar16) toBuffer[0], encoding) : PlatformChar(toBuffer[0], toBuffer[1], encoding);
}

//----------------------------------------------------------------------
// TranslateEmbeddedCharToTextChar
//
//		This routine takes a platform acsii string possibly containing 
//		embedded unicode characters and translates it into a wide char string.
//
//----------------------------------------------------------------------
int32 TranslateCharToTextChar(const char* fromString, long fromStrLength, UTF16TextChar* toStringBuffer, long toStrBufferLength, int16 writingscript)
{
	UTF16TextChar *toWCharPtr = toStringBuffer;
	long nWideChars = 0;

	//
	// The algorithm here is pretty ugly, because in non roman encodings, character width may not
	//	always be predictable, all chars fit in either 1 or 2 byte. In Shift-JIS there are both one 
	//	and two byte characters.
	//
	// The easiest thing to do is to first do the full conversion to Unicode in a temporary buffer, 
	//	then look through this buffer for the special character sequences that denote embedding, 
	//	and do the special translation they require, then the buffer is copied to the buffer 
	//	passed in by the caller.
	//
	if (fromStrLength <= 0 || toStrBufferLength <= 0)
	{
		return 0;
	}
	
	long tempBufLength = fromStrLength;
	UTF16TextChar *tempBuf = new UTF16TextChar[tempBufLength];
	ASSERT_MSG(tempBuf != nil, "PMString::TranslateEmbeddedCharToTextChar - tempBuf != nil");

	int32 numWChars = ::CTUnicodeTranslator::Instance()->CharToTextChar( fromString, fromStrLength, tempBuf, tempBufLength, writingscript );

	if (numWChars > 0)
	{
		UTF16TextChar *tempWCharPtr = tempBuf;
		for (long i = 0; i < numWChars; i++)
		{
			UTF16TextChar tempWChar = *tempWCharPtr++;
			UTF16TextChar wChar;
			
			 wChar = tempWChar;

			// Enough room in output buffer?
			if (nWideChars > toStrBufferLength - 1) 
			{
				ASSERT_FAIL("PMString::TranslateEmbeddedChar2TextChar: insufficient buffer space");
				break;
			}
			
			*toWCharPtr++ = wChar;
			nWideChars++;
		} 
	}

	delete []tempBuf;

	return nWideChars;
}

///////////////////////////////////////////////////////
// Utility functions
///////////////////////////////////////////////////////


#ifdef DEBUG
void PMString::Invariant() const
{
	if(fUTF16BufferLength)
	{ 
		UnicodeSavvyString::InvariantCheck();
	}
}
#endif

#pragma mark -
#pragma mark -DEPRECATED_PLATFORM_BUFFER-
#ifdef DEPRECATED_PLATFORM_BUFFER
// Slated for obsolesence

uint8 PMString::GetScript() const
{
//	ASSERT_FAIL("PMString::GetScript OBSOLETE - DO NOT USE. See PMString.h for porting recipe");
	return GetEncoding(); 
}

void	  PMString::SetScript(uint8 script)
{
	SetEncoding(static_cast<PMString::StringEncoding>(script)); 
}

PMString::StringEncoding PMString::GetEncoding() const
{
//	ASSERT_FAIL("PMString::GetEncoding OBSOLETE - DO NOT USE. See PMString.h for porting recipe");
	return fEncoding; 
}


void PMString::SetEncoding(PMString::StringEncoding encoding)
{
//	ASSERT_FAIL("PMString::SetEncoding OBSOLETE - DO NOT USE. See PMString.h for porting recipe");
	CHECK_MY_INVARIANT();
	if (encoding != fEncoding)
	{
		fEncoding = encoding;
	}
}

//----------------------------------------------------------------------
// GrabWString
//----------------------------------------------------------------------
ConstWString  PMString::GrabWString(void) const
{
	return UnicodeSavvyString::GrabUTF16Buffer(nil);
}

void PMString::SetCString(ConstCString c)
{
	SetKey(c, kDontTranslateDuringCall);
}

bool16 PMString::IsNull() const
{
	return empty();
}

bool16 PMString::IsEmpty() const
{
	return empty();
}
#endif

//#include "StringUtils.tpp"
//namespace StringUtils
//{
//	// Specialization for PMString
//	template<>
//		back_insert_iterator<PMString>& back_insert_iterator<PMString>::operator=(UTF32TextChar val)
//	{
//		// Push value into container
//		// No need to grow capacity here; now it is handled in UniCodeSavvyString
//		fContainer.AppendW(val);
//		return (*this);
//	}
//}

#if __MWERKS__
#pragma mark -
#endif
