//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/textiterator.h $
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
#ifndef __TextIterator__
#define __TextIterator__

//#include <iterator>

#include "DataWrapper.h"
#include "WideString.h"

class ITextModel;

#ifdef PUBLIC_BUILD
#pragma export on
#endif




class TextChunk
{
public:
	TextChunk() : fTextModelPtr(nil), fLength(0), fStartingIndex(0)
		{}

	PUBLIC_DECL TextChunk(const ITextModel* textModel, TextIndex index);
	PUBLIC_DECL TextChunk(const TextChunk& rhs); //define this to work around metrowerks 5 inline bug

	PUBLIC_DECL ~TextChunk();

	PUBLIC_DECL void ForceContainTextIndex(TextIndex index);
	bool16 Contains(TextIndex index)
		{ return index >= fStartingIndex && index < fStartingIndex + fLength; }
	int32 Length() const
		{ return fLength; }
	WideString::const_iterator begin() const
		{ return fWrapper.GetIteratorAt(0); }
	WideString::const_iterator end() const
		{ return fWrapper.GetIteratorAt(Length()); }

	PUBLIC_DECL TextChunk& operator=(const TextChunk& o);
	TextChunk& operator++ ()
		{
			ForceContainTextIndex(fStartingIndex + fLength);
			return *this;
		}
	TextChunk& operator-- ()
		{
			ForceContainTextIndex(fStartingIndex - 1);
			return *this;
		}

	WideString::const_iterator IndexToIterator(TextIndex index, int32 &numCharsLeft) const
		{
			ASSERT(index >= fStartingIndex && index < fStartingIndex + fLength);
			numCharsLeft = (fStartingIndex + fLength) - index;
			return fWrapper.GetIteratorAt(index - fStartingIndex);
		}
	const UTF16TextChar* IndexToPointer(TextIndex index, int32 &numUTF16sLeft)	const
		{
			ASSERT(index >= fStartingIndex && index < fStartingIndex + fLength);
			int32	numChars = 0;
			WideString::const_iterator iter = IndexToIterator(index, numChars);
			numUTF16sLeft = (iter + numChars).PtrAt() - iter.PtrAt();
			return iter.PtrAt();
		}

	const ITextModel * GetTextModel() const
		{ return fTextModelPtr; }

	const WideString* GetData() const
		{ return fWrapper.GetData(); }

	friend class ComposeScannerCache;	// since this holds a TextIterator but is on the same boss as the story, special access to the members is necessary.

protected:
	void 			Normalize(TextIndex chunkBegin);

protected:
	ITextModel				*fTextModelPtr;
	DataWrapper<textchar>	fWrapper;
	int32					fLength;
	TextIndex				fStartingIndex;
};




class TextIterator
	//: public std::iterator<random_access_iterator_tag, textchar, ptrdiff_t, const textchar*, const textchar&>
{
public:
	typedef UTF32TextChar				value_type;
	typedef std::ptrdiff_t					difference_type;
	typedef const UTF32TextChar*   			pointer;
	typedef const UTF32TextChar& 			reference;
	typedef std::bidirectional_iterator_tag	iterator_category;

	PUBLIC_DECL TextIterator(const ITextModel* textModel, TextIndex pos);
	PUBLIC_DECL TextIterator(const WideString::const_iterator& stringIter, TextIndex pos);
	PUBLIC_DECL TextIterator(const TextIterator&);

	TextIndex Position() const
		{ return fPosition; }
	bool16 IsNull() const
		{ return fCurrent.PtrAt() == nil; }

	PUBLIC_DECL void AppendToStringAndIncrement(WideString * str, int32 numChars);

	PUBLIC_DECL TextIterator& operator=(const TextIterator& o);
	TextIterator::value_type operator * () const
		{ ASSERT(fCurrent.PtrAt() != nil); return *fCurrent; }
	WideString::const_iterator operator -> () const
		{ ASSERT(fCurrent.PtrAt() != nil); return fCurrent; }
	PUBLIC_DECL TextIterator& operator ++ ();
	TextIterator operator ++ (int)
		{ TextIterator tmp(*this); ++(*this); return tmp; }
	PUBLIC_DECL TextIterator& operator -- ();
	TextIterator operator -- (int)
		{ TextIterator tmp(*this); --(*this); return tmp; }
	PUBLIC_DECL TextIterator& operator += (int32 n);
	TextIterator operator + (int32 n) const
		{ return TextIterator(*this) += n; }
	PUBLIC_DECL TextIterator& operator -= (int32 n);
	TextIterator operator - (int32 n) const
		{ return TextIterator(*this) -= n; }
	int32 operator - (const TextIterator& rhs) const
		{ return int32(fPosition - rhs.fPosition); }
	TextIterator::value_type operator [] (int32 i) const
		{ TextIterator tmp(*this); tmp += i; return *tmp; }

	friend TextIterator operator + (int32 n, const TextIterator& rhs)
		{ return TextIterator(rhs) += n; }
	friend bool operator ==(const TextIterator& x, const TextIterator& y)
		{ return x.fCurrent.PtrAt() == y.fCurrent.PtrAt(); }
	friend bool operator !=(const TextIterator& x, const TextIterator& y)
		{ return x.fCurrent.PtrAt() != y.fCurrent.PtrAt(); }
	friend bool operator < (const TextIterator& x, const TextIterator& y)
		{ return x.fPosition <  y.fPosition; }
	friend bool operator <=(const TextIterator& x, const TextIterator& y)
		{ return x.fPosition <= y.fPosition; }
	friend bool operator > (const TextIterator& x, const TextIterator& y)
		{ return x.fPosition >  y.fPosition; }
	friend bool operator >=(const TextIterator& x, const TextIterator& y)
		{ return x.fPosition >= y.fPosition; }

	PUBLIC_DECL const ITextModel* QueryTextModel() const;

#ifdef DEBUG
	const ITextModel * GetTextModel() const
		{ return fChunk.GetTextModel(); }
#endif

	friend class ComposeScannerCache;	// since this holds a TextIterator but is on the same boss as the story, special access to the members is necessary.

private:
	TextIterator() : fCurrent(nil, 0), fPosition(0) {}

protected:
	TextChunk		fChunk;
	WideString::const_iterator	fCurrent;
	TextIndex		fPosition;

};


#ifdef PUBLIC_BUILD
#pragma export off
#endif

#endif

