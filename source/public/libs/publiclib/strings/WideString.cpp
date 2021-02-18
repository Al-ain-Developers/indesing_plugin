//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/strings/WideString.cpp $
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
//========================================================================================

#include "VCPublicHeaders.h"

#include "WideString.h"
#include "IPMStream.h"

#include "PMString.h"		// for conversion to sys string
#include "PMUtils.h"
#include "CompressInt.h"		// all widestrings are streamed compressed
#include "CTUnicodeTranslator.h"
#include "TextChar.h"
#include "UnicodeClass.h"

#include "ITextUtils.h"
#include "MemXferBytes.h"
#include "StreamUtil.h"
#include "Utils.h"
#include "StringStorage.h"
#include "StringUtils.h"

#undef  CHECK_MY_INVARIANT
#define CHECK_MY_INVARIANT() AUTO_INVARIANT_CHECKER(WideString)

#ifdef DEBUG
bool16 WideString::ts_ForceRoundtrip = kFalse;
static IDThreading::ThreadLocal<bool16> tl_ForcingRoundtrip(kFalse);
#endif

const boost::shared_ptr<WideString> WideString::kNil_shared_ptr;

extern int32 ShrinkStringSizeW(int32 newLength);

namespace detail
{
	// Check that the iterator is in the valid range (end is a valid iterator position)
	bool IsValidIterator(const WideString& s, const WideString::const_iterator& i)
	{
		return (i.PtrAt() >= s.begin_raw() && i.PtrAt() <= s.end_raw());
	}
}


WideString::WideString(const wchar_t* s, int32 len) 	// wchar_t is a distinct type on CW
{
	this->SetX16String(s, len);
//	COMPILE_CHECK(sizeof(wchar_t) == 2);
//	ASSERT(sizeof(wchar_t) == 2);
}						// but the size is undefined so we'll check it here (so it's checked for each plugin that uses WideString)


WideString::WideString()
{
}

WideString::WideString(WideString::const_pointer_raw s, int32 len, int32 numChars)
{
	this->SetX16String(s, len, numChars);
}

WideString::WideString(const WideString::const_iterator &iter, int32 numChars)
{
	this->SetX16String(iter.PtrAt(), (iter + numChars).PtrAt() - iter.PtrAt(), numChars);
}

WideString::WideString(const WideString& w)
{
	CHECK_MY_INVARIANT();
	CopyFrom(w);
}

WideString::WideString(ConstCString string, int32 numChars)
{
	const int32	len = (numChars >= 0) ? numChars : (int32)std::strlen((char *)string);
	bool16 allLowerASCII = kTrue;

	ASSERT_MSG(len < 128, FORMAT_ARGS("WideString::WideString(ConstCString) - calling with length %d len. String is - %s. Recommend not using this constructor. If ConstCString is utf8 use StringUtils::ConvertUTF8ToWideString.", len, string));
	for (int i = 0; i < len; i++)
	{
		char c = string[i];
		if ( (c < 0x20 && c != 0x09 && c != 0x0A && c != 0x0D) || ((c & 0x80) != 0) )
		{
			ASSERT_FAIL(FORMAT_ARGS("WideString - calling with a ConstCString that contains upper ASCII! String is - %s", string));
			allLowerASCII = kFalse;
			break;
		}
	}

	if (allLowerASCII)
	{
		UTF16TextChar * unicodeBuffer = GetBufferForWriting(len);
		fUTF16BufferLength = len;
		
		std::copy(string, string + len, unicodeBuffer);

		// Ensure the terminating null
		unicodeBuffer[fUTF16BufferLength] = 0;

		fNumChars = CountChars();
	}
	else
		this->SetCString(string, kFalse, len);
}

WideString::WideString(const PMString& s)
{
	this->BuildFromSystemString(s);
}

WideString::~WideString()
{
}


/////////////////////////

WideString::iterator_raw WideString::begin_raw()
{
	TRACE_IF(HasMultiWordUnicode(), "About to hand back non-const iterator on WideString's buffer! Be careful with surrogates!");
	return GetBufferForWriting(fUTF16BufferLength);
}

WideString::const_iterator_raw WideString::begin_raw() const
{
	return ConstBuffer();
}

WideString::iterator_raw WideString::end_raw()
{
	TRACE_IF(HasMultiWordUnicode(), "About to hand back non-const iterator on WideString's buffer! Be careful with surrogates!");
	return GetBufferForWriting(fUTF16BufferLength) + fUTF16BufferLength;
}

WideString::const_iterator_raw WideString::end_raw() const
{
	return ConstBuffer() + fUTF16BufferLength;
}


int32 WideString::UTF16IndexToCodePointIndex(int32 index) const
{
	return HasMultiWordUnicode() ? CountCharsUtil(ConstBuffer(), index) : index;
}

void WideString::Append(const WideString &s)
{
	Append(s.ConstBuffer(), s.fUTF16BufferLength, s.fNumChars);
}

bool16 WideString::operator==(const WideString& s) const
{
	return this->UnicodeSavvyString::operator==(s);
}

bool16 WideString::operator==(WideString::const_pointer_raw b) const
{
	if (ConstBuffer() == b)		// takes care of 2 nulls & self compare
		return kTrue;

	if ((b == nil || b[0] == 0) && fUTF16BufferLength == 0)
		return kTrue;

		// everything equal until...
	for (int32 i = 0; i < fUTF16BufferLength; ++i)
	{
		if (b[i] != ConstBuffer()[i])
		{
			return kFalse;
		}
	}
		// end of buffers
	return (b[fUTF16BufferLength] == 0);
}

WideString::value_type WideString::LastChar() const
{
	ASSERT(fUTF16BufferLength > 0);
	// If we know there aren't any long characters, OR the last character isn't long, just return the last 16 bits
	if (!HasMultiWordUnicode() || !UnicodeClass::IsSurrogate(ConstBuffer()[fUTF16BufferLength - 1]))
	{
		return ConstBuffer()[fUTF16BufferLength - 1];
	}
	// else we know the LAST character must be long, so we'll assemble it from the last 2 characters
	return UTF32TextChar(ConstBuffer()[fUTF16BufferLength -2], ConstBuffer()[fUTF16BufferLength -1]);
}

WideString::value_type WideString::FirstChar() const
{
	ASSERT(fUTF16BufferLength > 0);
	if (!HasMultiWordUnicode() || !UnicodeClass::IsSurrogate(ConstBuffer()[0]))
	{
		return ConstBuffer()[0];
	}
	return UTF32TextChar(ConstBuffer()[0], ConstBuffer()[1]);
}

void WideString::SetChar(int32 index, WideString::value_type c32)
{
	CHECK_MY_INVARIANT();
	ASSERT(index >= 0);
	const uint32 wordwiseIndex = CodePointIndexToUTF16Index(index);
	if (!c32.isExtraWide())
	{
		if (HasMultiWordUnicode() && UnicodeClass::IsSurrogate(ConstBuffer()[wordwiseIndex]))
		{
			RemoveGap(wordwiseIndex, 1);
		}
		UTF16TextChar * buffer = GetBufferForWriting(fUTF16BufferLength);
		buffer[wordwiseIndex] = c32.GetValue();
	}
	else
	{
		if (!UnicodeClass::IsSurrogate(ConstBuffer()[wordwiseIndex]))
		{
			InsertGap(wordwiseIndex, 1);
		}
		UTF16TextChar * buffer = GetBufferForWriting(fUTF16BufferLength);
		buffer[wordwiseIndex] = c32.CalcHighSurrogate();
		buffer[wordwiseIndex + 1] = c32.CalcLowSurrogate();
	}
}



int32 WideString::compare(const WideString& s) const
{
	const textchar	*b1 = ConstBuffer();
	const textchar	*b2 = s.ConstBuffer();
	int32			l1 = fUTF16BufferLength;
	int32			l2 = s.fUTF16BufferLength;

	if (fStorage && fStorage == s.fStorage)
	{
		return 0;
	}
	while (l1 && l2)
	{
		if (*b1 > *b2)
		{
			return +1;
		}
		else if (*b1 < *b2)
		{
			return -1;
		}
		else
		{
			b1++;
			b2++;
			l1--;
			l2--;
		}
	}

	if (l1 == l2)		// both same means both equal to end
	{
		return 0;
	}
	else				// not the same to the end
	{
		return l1 > 0 ? +1 : -1;
	}
}


void WideString::SetString(const WideString& a)
{
	CHECK_MY_INVARIANT();
	CopyFrom(a);
}

void WideString::SetString(const WideString::const_iterator& iter, int32 numChars)
{
	CHECK_MY_INVARIANT();
	this->SetX16String(iter.PtrAt(), (iter + numChars).PtrAt() - iter.PtrAt(), numChars);
}



void WideString::SetCString(ConstCString c, bool16 convertEmbeddedUnicode, int32 numChars)
{
	CHECK_MY_INVARIANT();
	ASSERT(c != nil);

	if (convertEmbeddedUnicode)
	{
		// Use a PMString to do the conversion for us
		PMString tempStr;
		if (numChars < 0)
		{
			// Caller's buffer is null-terminated
			tempStr.SetCString(c, PMString::kUnknownEncoding);
		}
		else
		{
			// Caller's buffer is not null-terminated
			tempStr.SetXString(c, numChars);
		}
		this->BuildFromSystemString(tempStr);
	}
	else
	{
		int32	len = (numChars < 0) ? static_cast<int32>(strlen((char *)c)) : numChars;
		UTF16TextChar * buffer = GetBufferForWriting(len);
		int32 nUTF16s = ::CTUnicodeTranslator::Instance()->CharToTextChar( c, len, buffer, capacity() );
		buffer[nUTF16s] = 0;
		fUTF16BufferLength = nUTF16s;
		fNumChars = CountCharsUtil(buffer, nUTF16s);
	}
#ifdef DEBUG
    ASSERT(!ParseForMultiWordUnicode());
#endif
}



void WideString::SetX16String(WideString::const_pointer_raw x, int32 len, int32 numChars)
{
	if (len == INT_MAX)
	{
		len = (int32)UTF16TextCharLength(x);
	}

	if (numChars == -1)
		numChars = CountCharsUtil(x, len);

	UnicodeSavvyString::assign(x, x + len, numChars);
}


void WideString::SetX16String(const wchar_t* x, int32 len, int32 numChars)
{
	CHECK_MY_INVARIANT();
	ASSERT(x != nil || len == 0);

	if (len == INT_MAX)
	{
		len = (int32)std::wcslen(x);
	}

	fUTF16BufferLength = 0;
	fNumChars = 0;
	if (len)
	{
		if (sizeof(wchar_t) == sizeof(UTF16TextChar))
		{
			UTF16TextChar * buffer = GetBufferForWriting(len);
			::memcpy(buffer, x, len * sizeof(wchar_t));
			fUTF16BufferLength = len;
			buffer[fUTF16BufferLength] = 0;
			if (numChars == -1)
			{
				fNumChars = CountChars();
			}
			else
			{
				fNumChars = numChars;
				ASSERT(fNumChars == CountChars());
			}
		}
		else if (sizeof(wchar_t) == 4)
		{
			for (int32 i = 0; i < len; i++)
			{
				UnicodeSavvyString::AppendUTF32TextChar(x[i]);
				if (fNumChars == numChars)
					break;
			}

			// Either numChars was less than the real number of chars or wcslen should == fUTF16BufferLength
			ASSERT((numChars != -1) || fUTF16BufferLength == len);
			// If numChars is bigger than chars in buffer this will assert.
			ASSERT((numChars == -1) || fNumChars == numChars);
		}
	}

}



void WideString::Append(WideString::const_pointer_raw s, int32 n, int32 numChars)
{
	if (n == -1)
		n = static_cast<int32>(UTF16TextCharLength(s));
		
	if (numChars == -1)
		numChars = CountCharsUtil(s, n);
		
	UnicodeSavvyString::append(s, n, numChars);
}


void WideString::Insert(const WideString& s, int32 pos, int32 charCount)
{
	int32 count = charCount;
	if (charCount > s.fUTF16BufferLength)
	{
		count = s.fUTF16BufferLength;
	}
	else if (s.HasMultiWordUnicode())
	{
		count = s.CodePointIndexToUTF16Index(charCount);
	}
	Insert(s.ConstBuffer(), count, pos);
}

/** Replaces the code points in range [b, e) with the code points in the range [br, er).
	The function grows the string if necessary to accomodate for the replacement string.
	Note: to remove the specified range, use an empty range for replacement (i.e. br == er).
	To insert or append characters without removing anything, use the same iterator for b and e.
	@param b [IN] - begining of the range where replacement starts.
	@param e [IN] - end of the range to be replaced.
	@param br [IN] - begin of replacement range.
	@param er [IN] - begin of replacement range.
	@return reference to this string.
*/
WideString& WideString::replace(const WideString::const_iterator& b, const WideString::const_iterator& e,
								const WideString::const_iterator& br, const WideString::const_iterator& er)
{
	ASSERT(b <= e && br <= er);
	// b and e should be iterators of this container
	ASSERT(detail::IsValidIterator(*this, b) && detail::IsValidIterator(*this, e));

	if (b == e && br == er)
		return *this;		// nothing to do
	
	// Switch to code values calculations (UnicodeSavvyString::replace works on code values)
	size_type const startPos = b.PtrAt() - ConstBuffer();
	ASSERT(startPos <= fUTF16BufferLength);

	size_type const n1 = e.PtrAt() - b.PtrAt();
	// Assume replacing with empty range
	size_type n2(0);
	code_value const* buf = nil;
	// Non-empty replacement range?
	if (br != er)
	{
		buf = br.PtrAt();
		n2 = er.PtrAt() - br.PtrAt();
	}
	
	// Do the replacement
	UnicodeSavvyString::replace(startPos, n1, buf, n2);
	return *this;
}

WideString* WideString::Substring(int32 pos, int32 count) const
{
	ASSERT(count >= 0);
	ASSERT(pos >= 0);
	ASSERT(pos <= this->CharCount());

	WideString	*result = nil;

	// %brycem%
	if (count > 0 && fUTF16BufferLength && pos < fNumChars)
	{
		count = ::minimum<int32>(count, fNumChars - pos);
		if (count > 0)
		{
			result = new WideString(begin() + pos, count);
		}
	}

	return result;
}


WideString* WideString::GetItem(const WideString& delimiter, const int32 nItem) const
{
	int32 start = 0;
	int32 item = 0;
	while (true)
	{
		int32 offset = IndexOf(delimiter, start);
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


void WideString::remove_raw(int32 utf16Pos, int32 utf16Count)
{
	CHECK_MY_INVARIANT();
	ASSERT(utf16Pos >= 0);
	ASSERT(utf16Pos <= this->NumUTF16TextChars());
	ASSERT(utf16Count >= 0);

	if (utf16Count > fUTF16BufferLength - utf16Pos)
		utf16Count = fUTF16BufferLength - utf16Pos;

	if (utf16Count)
	{
		RemoveGap(utf16Pos, utf16Count);
	}
	fNumChars = CountChars();	// numChars can't be used because caller sometimes passes in huge value
}




// starting with position "pos" look for string s, return its index.
// if not found, return "kAtEnd"
int32 WideString::IndexOf(const WideString& key, int32 testPosition) const
{
	ASSERT(testPosition >= 0);
	ASSERT(testPosition <= this->CharCount());

	// %brycem%
	if (!fUTF16BufferLength)		// not found because no string to search
	{
		return -1;
	}

	if (key.fUTF16BufferLength == 0)			// always matches the empty string
	{
		return testPosition;
	}

	int32	utf16TestPos = CodePointIndexToUTF16Index(testPosition);

	if (fUTF16BufferLength < utf16TestPos + key.fUTF16BufferLength)		// can't match because not enough characters left
	{
		return -1;
	}

	int32		matchCount = 0;
	do
	{
		if (ConstBuffer()[utf16TestPos] == key.ConstBuffer()[matchCount])
		{
			utf16TestPos++;		// still matches
			matchCount++;
		}
		else
		{
			utf16TestPos -= matchCount;		// doesn't match, move to beginning + 1
			utf16TestPos++;
			matchCount = 0;
		}
	} while (matchCount < key.fUTF16BufferLength && utf16TestPos < fUTF16BufferLength);

	if (matchCount < key.fUTF16BufferLength)
	{
		return -1;
	}
	else
	{
		return UTF16IndexToCodePointIndex(utf16TestPos - key.fUTF16BufferLength);
	}
}


// starting with position "pos" look for string s, return its index
// if not found, return "kAtEnd"
int32 WideString::IndexOf(WideString::value_type key, int32 pos) const
{
	ASSERT(pos >= 0);
	ASSERT(pos <= this->CharCount());

	// %Brycem%
	if (!fUTF16BufferLength)		// not found cause no string to search
		return -1;

	int32	utf16Pos = CodePointIndexToUTF16Index(pos);

	while (utf16Pos < fUTF16BufferLength)
	{
		if (ConstBuffer()[utf16Pos] == key.CalcHighSurrogate() &&
				( (!key.isExtraWide()) ||
				(key.isExtraWide() && utf16Pos+1 < fUTF16BufferLength &&
				ConstBuffer()[utf16Pos+1] == key.CalcLowSurrogate()) ) )
		{
			return UTF16IndexToCodePointIndex(utf16Pos);
		}
		utf16Pos++;
	}
	return -1;
}


// remove extra chunks if false, all extra space if true.
// not an efficient thing to do very often!
void WideString::Shrink(bool16 maxshrink)
{
	if (!UnicodeBufferIsValid())		// null strings don't shrink
	{
		return;
	}
	if (!fUTF16BufferLength)		// null strings with buffers are shrunk
	{
// %brycem%
//		fUTF16BufferMemSize = 0;
		return;
	}

		// find proper size
	int32		newsize = (maxshrink ? fUTF16BufferLength : ShrinkStringSizeW(fUTF16BufferLength));

	// check to see if the buffer should be shrunk
	ASSERT( capacity() > newsize );
	if (capacity() != newsize)
	{
		fStorage = fStorage->MakeSize(newsize);
	}
}


// this function returns an unsigned hash for the string.
// formula came from Sedgewick.
uint32 WideString::Hash(void) const
{
	const uint32 kHashMod = 33554393;

	uint32		hash = 0;

	if (fUTF16BufferLength)
	{
		hash = ConstBuffer()[0];

		for (int32 i = 1; i < fUTF16BufferLength; i++)
		{
			hash = ((hash * 32) + ConstBuffer()[i]) % kHashMod;
		}
	}

	return hash;
}

void WideString::ToUpper(void)
{
	for (int32 i = 0; i < fUTF16BufferLength; i++)
	{
		UTF16TextChar * buffer;
		buffer = GetBufferForWriting(fUTF16BufferLength);
		buffer[i] = UnicodeClass::ToUpper(ConstBuffer()[i]).GetValue();
	}
}

void WideString::ToLower(void)
{
	for (int32 i = 0; i < fUTF16BufferLength; i++)
	{
		UTF16TextChar * buffer;
		buffer = GetBufferForWriting(fUTF16BufferLength);
		buffer[i] = UnicodeClass::ToLower(ConstBuffer()[i]).GetValue();
	}
}

void WideString::GetSystemString( PMString *ss ) const
{
	ASSERT( ss != 0 );
	if (fUTF16BufferLength)
	{
		ss->SetXString(ConstBuffer(),fUTF16BufferLength );
	}
	else
	{
		ss->clear();
	}
}

void WideString::BuildFromSystemString(const PMString& ss)
{
	if (ss.CharCount() > 0)
	{
		ss.GrabUTF16Buffer(nil);		// force unicode up to date
		CopyFrom(ss);
	}
	else
	{
		clear();
	}
}




void WideString::ReadWrite(IPMStream* s)
{
	int32		len = fUTF16BufferLength;
	s->XferInt32(len);

	if (s->IsReading())
	{
		UTF16TextChar * buffer;
		buffer = GetBufferForWriting(len);
		CompressInt_Read	reader(s);
		fUTF16BufferLength = len;
		fNumChars = len;
		// now decrement fNumChars for every low surrogate we find
		for (int32 i = 0; i < len; i++)
		{
			buffer[i] = (uint16)reader.Read();
			if (UnicodeClass::IsLowSurrogate(ConstBuffer()[i]))
			{
				ASSERT(i - 1 >= 0 && UnicodeClass::IsHighSurrogate(ConstBuffer()[i - 1]));
				fNumChars--;
			}
		}
		ASSERT(fNumChars == CountChars());
		buffer[fUTF16BufferLength] = 0;
	}
	else
	{
		CompressInt_Write	writer(s);

		for (int32 i = 0; i < fUTF16BufferLength; i++)
		{
			writer.Write((int16)ConstBuffer()[i]);
		}
	}
}



void WideString::RemoveCodePoints(int32 startCodePointIndex, int32 numCodePoints)
{
	ASSERT(startCodePointIndex >= 0 && startCodePointIndex < fNumChars);
	ASSERT(startCodePointIndex + numCodePoints <= fNumChars);

	const int32	utf16Start = CodePointIndexToUTF16Index(startCodePointIndex);
	const int32	utf16Count = CodePointIndexToUTF16Index(startCodePointIndex + numCodePoints) - utf16Start;

	RemoveGap(utf16Start, utf16Count);
	fNumChars -= numCodePoints;
}


#ifdef DEBUG
bool16 WideString::ParseForMultiWordUnicode() const
{
	for (int32 i = 0; i < fUTF16BufferLength; i++) {
		if (UnicodeClass::IsSurrogate(ConstBuffer()[i]))
		{
			return kTrue;
		}
	}
	return kFalse;
}
#endif


#ifdef DEBUG

template<class T>
void PersistAndDepersist(const T &thisString)
{
	T copy;
	MemXferBytes currentOutBuffer;
	InterfacePtr<IPMStream> currentOutStream(StreamUtil::CreateMemoryStreamWrite(&currentOutBuffer));
	const_cast<T &>(thisString).ReadWrite(currentOutStream);
	InterfacePtr<IPMStream> currentInStream( StreamUtil::CreateMemoryStreamRead(&currentOutBuffer));
	copy.ReadWrite(currentInStream);
	ASSERT(thisString == copy);
	currentOutStream->Close();
	currentInStream->Close();
}

void WideString::Invariant() const
{
	UnicodeSavvyString::InvariantCheck();

	if (WideString::ts_ForceRoundtrip && tl_ForcingRoundtrip.Get() == kFalse)
	{
		tl_ForcingRoundtrip.Set(kTrue);
		PersistAndDepersist(*this);
		tl_ForcingRoundtrip.Set(kFalse);
		UnicodeSavvyString::InvariantCheck();
	}
}

#endif

/*
textchar UTF32TextChar::GetTextChar() const
{
	// If someone is trying to process a wide character, their code should be updated to support actual UTF32TextChars and disallow
	// this forced coercion
	ASSERT_MSG(fCharacterValue < 0x10000,"Code that does not support 32-bit Unicode is trying to process a 32-bit character");
	return (textchar) fCharacterValue;
}

void UTF32TextChar::ReadWrite(IPMStream *s) { s->XferInt32((long&)fCharacterValue); }
*/

void UTF32TextChar::ReadWriteUTF16(IPMStream *s)
{
	if(s->IsWriting())
	{
		// assert if the value is a high or low surrogate. These are invalid UTF32 values.
		// also assert value is less than 0x0010FFFF. That is the max value possible by the max surrogate pair DBFFDFFF
		ASSERT_MSG(((fCharacterValue & 0xFFFFF800) != 0x0000D800) && fCharacterValue <= 0x0010FFFF, "Invalid Unicode value in ReadWriteUTF16");
		uint16	high;
		uint16	low;
		if (isExtraWide())
		{
			high = CalcHighSurrogate();
			s->XferInt16((short&)high);
		}
		low = CalcLowSurrogate();
		s->XferInt16((short&)low);
	}
	else
	{
		uint16	value;
		s->XferInt16((short&)value);
		if (UnicodeClass::IsHighSurrogate(value))
		{
			uint16 low;
			s->XferInt16((short&)low);
			UTF32TextChar readChar(value, low);
			fCharacterValue = readChar.GetValue();
		}
		else
		{
			fCharacterValue = value;
		}
	}
}


// ==================================================

UniCodePoint WideStringConstUTF32Iter::surro_operStar() const
{
	ASSERT(fCurrent != nil && fHasSurrogates);

	if (UnicodeClass::IsHighSurrogate(*fCurrent))
		return UTF32TextChar(*fCurrent, *(fCurrent + 1)).GetValue();
	else
		return *fCurrent;
}

void WideStringConstUTF32Iter::surro_operPP()
{
	ASSERT(fCurrent != nil && fHasSurrogates);
	if (UnicodeClass::IsHighSurrogate(*fCurrent))
	{
		ASSERT(UnicodeClass::IsLowSurrogate(*(fCurrent + 1)));
		fCurrent += 2;
	}
	else
	{
		++fCurrent;
	}
}

void WideStringConstUTF32Iter::surro_operMM()
{
	ASSERT(fCurrent != nil && fHasSurrogates);

	--fCurrent;
	if (fHasSurrogates && UnicodeClass::IsLowSurrogate(*fCurrent))
	{
		--fCurrent;
		ASSERT(UnicodeClass::IsHighSurrogate(*fCurrent));
	}
}

void WideStringConstUTF32Iter::surro_operPE(int32 n)
{
	ASSERT(fCurrent != nil && fHasSurrogates);

	for (int32 i = 0; i < n; ++i)
		++(*this);
}

void WideStringConstUTF32Iter::surro_operME(int32 n)
{
	ASSERT(fCurrent != nil && fHasSurrogates);

	for (int32 i = 0; i < n; ++i)
		--(*this);
}

int32 WideStringConstUTF32Iter::surro_operDiff(const WideStringConstUTF32Iter& other) const
{
	ASSERT(fHasSurrogates && fHasSurrogates == other.fHasSurrogates);	// same string?

	int32 diff = fCurrent - other.fCurrent;
	if (diff > 0)
	{
		int32 tempDiff = 0;
		WideStringConstUTF32Iter tmp(*this);
		while (tmp > other)
		{
			--tmp;
			++tempDiff;
		}
		ASSERT(tempDiff <= diff);
		diff = tempDiff;
	}
	ASSERT(diff >= 0);
	return diff;
}


