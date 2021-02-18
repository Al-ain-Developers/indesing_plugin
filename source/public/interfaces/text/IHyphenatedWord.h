//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IHyphenatedWord.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __IHyphenatedWord__
#define __IHyphenatedWord__

#include "GRRefCountedObj.h"
#include "InterfacePtr.h"

#include "K2Vector.h"
#include "KeyValuePair.h"


class WideString;


/**
	A HyphenPoint is a possible break point within a word.
	@see IHyphenatedWord
	@ingroup text_hyphen
*/
struct HyphenPoint
{
	typedef base_type data_type;

	HyphenPoint(int32 pos, int32 val) : nPosition(pos), nValue(val)
		{}

	int32	nPosition;	// the position of the break.
	int32	nValue;		// the "quality" of the brea.
};

/** A sorted list of break points.
	Similar to HyphenPoint, the first int32 is the position,
	the second in the value. */
typedef K2Vector<KeyValuePair<int32, int32> >	HyphenPoints;



/** IHyphenatedWord stores information about the hyphenation points within a particular word.
	It is not an interface itself, but rather just an AddRef/Release abstract C++ object.
	@ingroup text_hyphen
*/
class IHyphenatedWord : public grRefCountedObj
{
public:
			/**	Quality values for hyphenation points are ranked between -100 and +100:
				The negative value should only be use internally. */
	enum {	kNoHyphenPoint = 0,
			kVeryUnpreferredHyphenPoint = 10,
			kUnpreferredHyphenPoint = 25,
			kRegularHyphenPoint = 50,
			kPreferredHyphenPoint = 75,
			kDiscretionaryHyphenPoint = 80,
			kHardHyphenPoint = 90,

			kBestHyphenPoint = 100,
			kWorstHyphenPoint = 0,
			kForcedHyphenPoint = kBestHyphenPoint,
			kRefusedHyphenPoint = kWorstHyphenPoint,

			kInvalidHyphenPoint = -1
		};


			/** How many hyphenation points?
				@return the count of hyphenation points that has been found. */
	virtual	int32		GetPointCount() const = 0;

			/** The index is the position before the hyphen: i.e. ser-vice returns 2 (zero-based).
				@param nNthPoint is which point to ask about.
				@return the index in the word of the Nth hyphenation point.	*/
	virtual	int32		GetIndexOfPoint( int32 nNthPoint ) const = 0;

			/** The quality value of the Nth hyphenation point.
				@param nNthPoint is which point to ask about.
				@return the quality in the word of the Nth hyphenation point.	*/
	virtual	int32		GetQualityOfPoint( int32 nNthPoint ) const = 0;

			/** Copies the word (might be different because the linguisitc systems do their own character translations).
				@return a WideString version of the word being hyphenated. */
	virtual	WideString	GetWord() const = 0;

			/** Fills the WideStrings without hyphen, i.e.: "service" to "ser" and "vice". Will do spelling changes
				but doesn't add the hyphen (if it wasn't already there).
				@param nNthPoint is which break point.
				@param pFirstPart is a pointer (not nil) to a blank WideString, is filled out with the pre-break point part.
				@param pLastPart is a pointer (not nil) to a blank WideString, is filled out with the post-break point part.
			*/
	virtual	void			GetPartsOfPoint( int32 nNthPoint, WideString *pFirstPart, WideString *pLastPart ) const = 0;

			/** Fills the WideString without hyphen, i.e.: "service" to "ser". Will do spelling changes
				but doesn't add the hyphen (if it wasn't already there).
				@param nNthPoint is which break point.
				@param pPart is a pointer (not nil) to a blank WideString, is filled out with the pre-break point part.
			*/
	virtual	void			GetFirstPartOfPoint( int32 nNthPoint, WideString *pPart ) const = 0;

			/** Fills the WideString, i.e.: "service" to "vice". Can do spelling changes.
				@param nNthPoint is which break point.
				@param pPart is a pointer (not nil) to a blank WideString, is filled out with the post-break point part.
			*/
	virtual	void			GetLastPartOfPoint( int32 nNthPoint, WideString *pPart ) const = 0;

			/** Merge 2 lists of break points. Used to combine dictionary breakpoints with other types of breaking
				Used only for to combine hard dash breaking since Discretionary hyphens always take precidence.
				@param pToMergeWith is another hyphenated word to merge into this one.
			*/
	virtual	void			Merge( const IHyphenatedWord *pToMergeWith ) = 0;

			/** after merging, this routine is called as a post-method clean up */
	virtual void		ValidatePointRanges(void) = 0;
};


/** specialized version of InterfacePtr because IHyphenatedWord is not an interface */
template <>
class InterfacePtr<IHyphenatedWord>
{
public:
		InterfacePtr(IHyphenatedWord * pFace = nil) : fFace(pFace)
			{}

//		template <class OtherType>
//			InterfacePtr(const InterfacePtr<OtherType>& p)
//			:fFace(AddRef_(p.get()))
//		{ /* Implementation Note: we use a template member fucntion here to do the right thing
//		  when an InterfacePtr<const IFoo> is constructed from an InterfacePtr<IFoo> */
//		}

		/** Copy constructor. Increments the ref count of p by one. We define this to prevent the
		compiler from generating a bitwise copying version (template members do not suffice).
		@param p [IN] - InterfacePtr to be copied.
		*/
		InterfacePtr(const InterfacePtr<IHyphenatedWord>& p)
			:fFace(AddRef_(p.get()))  { }

		/** Assigment operator. Increments the ref count of p by one.
		This one enables InterfacePtr<const IFoo> = InterfacePtr<IFoo>
		@param p [IN] - InterfacePtr to be copied.
		*/
		template <class OtherType>
			InterfacePtr<IHyphenatedWord>& operator=(const InterfacePtr<OtherType>& p)
		{
			// Take ownership of p
			reset(AddRef_(p.get()));
			return *this;
			/* Implementation Note: we use a template member function here to do the right thing
			when an InterfacePtr<const IFoo> is constructed from an InterfacePtr<IFoo> */
		}

		/** Assigment operator. Increments the ref count of p by one.
		This one enables copying of InterfacePtr of the same types.
		@param p [IN] - InterfacePtr to be copied.
		*/
		InterfacePtr<IHyphenatedWord>& operator=(const InterfacePtr<IHyphenatedWord>& p)
			{
			// Take ownership of p
			reset(AddRef_(p.get()));
			return *this;
			}

		~InterfacePtr()
			{
			Release_(fFace);
			}

		operator IHyphenatedWord*() const
			{ return fFace; }

		IHyphenatedWord * operator ->() const
			{
			#ifdef DEBUG
				ASSERT_MSG(fFace != nil,"About to use nil interface ptr!");
			#endif
			return fFace;
			}

			// Null test
		bool16 operator!() const
			{ return fFace == nil; }

		IHyphenatedWord* forget() // was release
			{
				IHyphenatedWord* result = fFace;
				fFace = 0;
				return result;
			}

		IHyphenatedWord* get() const
			{ return fFace; }

		void reset(IHyphenatedWord* p = 0)
			{
			IHyphenatedWord* oldFace = fFace;
			fFace = p;
			Release_(oldFace);
			}

private:
	IHyphenatedWord * fFace;

	static IHyphenatedWord* AddRef_(const IHyphenatedWord* p)
		{ if(p) p->AddRef(); return const_cast<IHyphenatedWord*>(p);}

	static void Release_(IHyphenatedWord* p)
		{ if(p) p->Release(); }

	/** Prohibit assignment of a plain (dumb) pointer to an InterfacePtr by declaring operator= as private.
	*/
		template <class OtherType>
		InterfacePtr<IHyphenatedWord>& operator=(OtherType* p); // intentionally unimplemented
};

#endif
	// __IHyphenatedWord__

