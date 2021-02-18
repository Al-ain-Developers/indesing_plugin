//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/TextCharBuffer.h $
//  
//  Owner: Nat McCully
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
#ifndef __TextCharBuffer__
#define __TextCharBuffer__


#include "WideString.h"


inline bool IsHighSurrogate(UTF16TextChar c)
{ return (c >= kTextChar_HighSurrogateStart && c <= kTextChar_HighSurrogateEnd); }

inline bool IsLowSurrogate(UTF16TextChar c)
{ return (c >= kTextChar_LowSurrogateStart && c <= kTextChar_LowSurrogateEnd); }

inline UTF32TextChar BuildUTF32Char(UTF16TextChar hi, UTF16TextChar low)
{ return ((hi - 0xD800) * 0x400 + (low - 0xDC00) + 0x10000); }



/**
	TextCharBuffer is a container for two WideString::const_iterator objects that iterate
	over the same WideString. By moving the iterators, you can pretend you are truncating
	the buffer, but the buffer itself is protected. This is an efficient way of supporting correct
	trucation of buffers containing Unicode surrogate characters (mixed byte-length characters)
	@see WideString
*/
class TextCharBuffer
{
	public:
		TextCharBuffer(WideString::const_iterator b, WideString::const_iterator e) :fBegin(b.PtrAt()), fEnd(e.PtrAt())
			{ fCharCount = e - b; }
		TextCharBuffer(const TextCharBuffer& o) :fBegin(o.fBegin), fEnd(o.fEnd), fCharCount(o.fCharCount)
			{}
		explicit TextCharBuffer(const WideString& s) :fBegin(s.begin_raw()), fEnd(s.end_raw()), fCharCount(s.Length())
			{}
		TextCharBuffer(const UTF16TextChar *begin, const UTF16TextChar *end, int32 charCount)
				:fBegin(begin), fEnd(end), fCharCount(charCount)
			{}

		/**
		@return the first character in the buffer
		*/
		UTF32TextChar First() const
		{	return !IsHighSurrogate(*fBegin) ? *fBegin : BuildUTF32Char(fBegin[0], fBegin[1]); }

		/**  This function directly accesses the buffer in the WideString, so it is not Unicode savvy.
		You cannot assume it points to a whole character, or that you can increment it and find whole characters.
		@return raw ptr to the beginning of the buffer in the WideString (UTF16TextChar *).
		*/
		const UTF16TextChar* begin_raw() const
			{ return fBegin; }
		/**  This function directly accesses the buffer in the WideString, so it is not Unicode savvy.
		You cannot assume it points to a whole character, or that you can decrement it and find whole characters.
		@return raw ptr to the end of the buffer in the WideString (UTF16TextChar *).
		*/
		const UTF16TextChar* end_raw() const
			{ return fEnd; }

		/**
		@return character count (not same as buffer byte length) of buffer
		*/
		int32 CharCount() const
			{ return fCharCount; }

		/** truncate first whole character of buffer
		*/
		void RemoveFirst()
		{	--fCharCount;
			if (!IsHighSurrogate(*fBegin))
				++fBegin;	// not high surrogate
			else
				fBegin += 2; }

		/** truncate last whole character of buffer
		*/
		void RemoveLast()
		{	--fCharCount;
			--fEnd;
			if (IsLowSurrogate(*fEnd))
				--fEnd; }	// was low surrogate

	private:
		TextCharBuffer() :fBegin(nil), fEnd(nil), fCharCount(0)
			{}

		const UTF16TextChar	*fBegin;
		const UTF16TextChar	*fEnd;
		int32			fCharCount;
};


#endif
		//  __TextCharBuffer__
