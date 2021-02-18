//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/TextAttributeRunIterator.h $
//  
//  Owner: zwilliam
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
//  Purpose:
//  
//========================================================================================

#pragma once
#ifndef __TextAttributeRunIterator__
#define __TextAttributeRunIterator__

#include "TextRange.h"
#include "K2Vector.h"
#include "AttributeBossList.h"
#include "K2SmartPtr.h"

/** The TextAttributeRunIterator class is very handy for walking through one or more text ranges,
	examining the value of one or more text attributes within the ranges and optionally applying
	different attributes to the ranges.
	
	Here's a simple example for increasing the point size of text by "incrementAmt" relative to whatever
	size it was to begin with.  Note that this works when the selection contains mixed point sizes since
	the iterator "walks" to each range of text that has one consistent set of values for the given attributes.
	(In this case each span of text that has the same point size with in the given set of ranges.)

		K2Vector<ClassID> attributeClasses;
		attributeClasses.reserve(1);
		attributeClasses.push_back(kTextAttrPointSizeBoss);

		TextAttributeRunIterator runIter(textRanges.begin(), textRanges.end(), attributeClasses.begin(), attributeClasses.end());

		while (runIter)
			{
			// At this point the only attribute in the AttributeBossList at *runIter is a kTextAttrPointSizeBoss.  If the iterator had
			// been constructed with more than one attribute in the attributeClasses vector, then QueryByClassID would be used to access the
			// desired text attribute (i.e. runIter->QueryByClassID(kTextAttrPointSizeBoss, ITextAttrRealNumber::kDefaultIID)).
			
			InterfacePtr<const ITextAttrRealNumber> originalAttr(static_cast<const ITextAttrRealNumber *>(runIter->QueryBossN(0, ITextAttrRealNumber::kDefaultIID)));

			// Create a new attribute with an incremented point size.
			InterfacePtr<ITextAttrRealNumber> newAttr(this->CreateRealNumberAttribute(attributeClass, originalAttr->Get() + incrementAmt));

			// Apply the new point size to the range that had the previous point size.
			runIter.ApplyAttribute(newAttr);

			++runIter;
			}

	This iterator class is used extensively by the various implementations of ITextAttributeSuite to implement the
	increase/decrease and toggle attribute value features.
	
	Applying attributes via the iterator doesn't invalidate the iterator.  However, applying attributes outside the iterator,
	editing styles or performing text edits (insert/delete) do invalidate the iterator and will result in unpredicatable behavior.
	If you need to mix these operations with using a TextAttributeRunIterator, you should destruct and construct a new iterator
	after each "external" operation.
 */
class TextAttributeRunIterator
{
	public:
			/** Construct an interator by passing in iterators for the start and end of a range
				of InDesign::TextRange objects within a vector.  The TextRange vector can represent
				multiple ranges within a single text model (i.e. table cells), multiple ranges in
				different text models (i.e. text frame pointer tool selection), or just a single
				range in a single text model.
				And pass the same style of begin/end iterators into a vector of the ClassIDs of
				the text attributes to be considered when breaking the text into runs.
				@param firstRange	the first TextRange of those to be iterated.
				@param endOfRanges	the last+1th TextRange of those to be iterated.
				@param firstAttributeClass the first attribute ClassID of those to be considered as part of a "run".
				@param endOfAttributeClasses	the last+1th attributes ClassID of those to be consider as part of a "run".
			 */
		PUBLIC_DECL TextAttributeRunIterator(K2Vector<InDesign::TextRange>::const_iterator firstRange,
				K2Vector<InDesign::TextRange>::const_iterator endOfRanges,
				K2Vector<ClassID>::const_iterator firstAttributeClass,
				K2Vector<ClassID>::const_iterator endOfAttributeClasses);

			/** Copy constructor
			 */
		TextAttributeRunIterator(const TextAttributeRunIterator& other)
			: fCurrentRange(other.fCurrentRange),
				fEndOfRanges(other.fEndOfRanges),
				fRunStart(other.fRunStart),
				fRunEnd(other.fRunEnd),
				fFirstClass(other.fFirstClass),
				fEndOfClasses(other.fEndOfClasses),
				fAttributes(other.fAttributes)
			{}

		~TextAttributeRunIterator()
			{}

			/** Returns an AttributeBossList at the current location of the iterator.
				WARNING: This const & is only valid as long as the iterator is in scope
				and is altered by advancing (operator++) the iterator.  If you wish to
				compare the attributes of consecutive runs, you need to either use 2
				iterators or be sure to make a copy of the AttributeBossList before calling
				operator++.
			 */
		PUBLIC_DECL const AttributeBossList& operator * () const;
		
			/** Allows for iter-> usage to access the member functions of the AttributeBossList
				at the iterator location.
			 */
		PUBLIC_DECL const AttributeBossList * operator -> () const;

			/** Advances the iterator to the next span of text where the list of attributes
				passed to the constructor all have the same values, and silently walks from
				each of the passed in text ranges to the next.
			 */
		PUBLIC_DECL TextAttributeRunIterator& operator ++ ();

			/** Compare the locations of two text iterators.
			 *	This is really only meaningful if the iterators are in the same text model.
			 */
		bool16 operator < (const TextAttributeRunIterator& other) const
			{
				if (fCurrentRange < other.fCurrentRange)
					return kTrue;

				if (fCurrentRange > other.fCurrentRange)
					return kFalse;

				// Both iterators are in the same range of the same text model.
				if (fRunStart < other.fRunStart)
					return kTrue;

				return kFalse;
			}

			/** Used to indicate when the iterator has fallen of the end of the list of ranges
			 */
		operator bool()
			{ return fCurrentRange < fEndOfRanges; }

			/** Applies the given set of text attributes to the range of text at the current position
			 *	of the iterator.
			 */
		PUBLIC_DECL ErrorCode ApplyAttributes(const boost::shared_ptr<AttributeBossList>&  attributes, const ClassID& which = kCharAttrStrandBoss);
		
			/** Applies a single text attributes to the range of text at the current position
				of the iterator.
			 */
		PUBLIC_DECL ErrorCode ApplyAttribute(IPMUnknown * attribute, const ClassID& which = kCharAttrStrandBoss);

			/** Returns the range of the current span of text at the iterator.
			  */
		RangeData GetRunRange() const
			{ return RangeData( fRunStart, fRunEnd, RangeData::kLeanForward);}
			
	private:
		void UpdateRunEnd(bool16 calledFromConstructor);

		K2Vector<InDesign::TextRange>::const_iterator fCurrentRange;
		K2Vector<InDesign::TextRange>::const_iterator fEndOfRanges;

		TextIndex fRunStart;
		TextIndex fRunEnd;

		K2Vector<ClassID>::const_iterator fFirstClass;
		K2Vector<ClassID>::const_iterator fEndOfClasses;

		AttributeBossList fAttributes;
};

#endif

