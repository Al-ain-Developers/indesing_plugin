//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/structure/XMLContentIterator.cpp $
//  
//  Owner: Lonnie Millett
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
//  Summary: 
//  
//========================================================================================

#include "VCPublicHeaders.h"

#include "XMLContentIterator.h"
#include "IXMLUtils.h"
#include "ITableTextContainer.h"
#include "ITextIndexIDRange.h"

XMLContentIterator::XMLContentIterator() :
	fElement(nil),
	fStartIndex(kInvalidTextIndex),
	fEndIndex(kInvalidTextIndex),
	fCurrent(),
	fPosition(-1)
{
}


XMLContentIterator::XMLContentIterator(const XMLContentIterator& rhs) :
	fElement(rhs.fElement),
	fStartIndex(rhs.fStartIndex),
	fEndIndex(rhs.fEndIndex),
	fCurrent(rhs.fCurrent),
	fPosition(rhs.fPosition)
{
}


XMLContentIterator::XMLContentIterator(const IIDXMLElement* element, int32 position) :
	fPosition(position)
{
	const_cast<IIDXMLElement*>(element)->AddRef();
	fElement.reset(element);

	// -- The default range for an invalid state
	InterfacePtr<ITextModel> textModel(Utils<IXMLUtils>()->QueryTextModel(element));
	ASSERT(textModel != nil);
	fCurrent = InDesign::TextRange(textModel, kInvalidTextIndex, 0);

	// computer the content range
	bool16 isMarkerPos(Utils<IXMLUtils>()->GetElementIndices(element, &fStartIndex, &fEndIndex));
	if (fStartIndex != kInvalidTextIndex)
	{
		// -- Move it past the marker
		if (isMarkerPos)
			++fStartIndex;
		
		// -- In the case of a graphic, we'll have an invalid text index as the end index.  We want this to return
		// -- empty content, so we set the start to the end
		if (fEndIndex == kInvalidTextIndex)
			fEndIndex = fStartIndex;
			
		// -- If the position specified is a valid one then intialize the iterator to its initial state
		if (fPosition >= 0 && fPosition  <= fElement->GetChildCount())
			CalcCurrentTextRange();
	}
	else
	{
		// if there is no start, then there shouldn't be an end either
		ASSERT_MSG(fEndIndex == kInvalidTextIndex, "XMLContentIterator::XMLContentIterator: valid end index with invalid start index");

		// this element has no content, so set the current position to same as end
		fPosition = element->GetChildCount()+1;
	}
}


XMLContentIterator::~XMLContentIterator()
{
}


XMLContentIterator& XMLContentIterator::operator= (const XMLContentIterator& rhs)
{
	if(&rhs != this)
	{
		fElement = rhs.fElement;
		fStartIndex = rhs.fStartIndex;
		fEndIndex = rhs.fEndIndex;
		fCurrent = rhs.fCurrent;
		fPosition = rhs.fPosition;
	}
	return *this;
}

XMLContentIterator& XMLContentIterator::operator ++ ()
{
	++fPosition;
	
	// -- If we are incrementing beyond the last range of text then put then iterator
	// -- into its end state
	if (fPosition  < 0  || fPosition > fElement->GetChildCount())
	{
		InterfacePtr<ITextModel> textModel(fCurrent.QueryModel());
		fCurrent = InDesign::TextRange(textModel, kInvalidTextIndex, 0);
	}
	else
		CalcCurrentTextRange();
	
	return *this;
}

XMLContentIterator& XMLContentIterator::operator -- ()
{
	--fPosition;
	
	if (fPosition  < 0  || fPosition > fElement->GetChildCount())
	{
		InterfacePtr<ITextModel> textModel(fCurrent.QueryModel());
		fCurrent = InDesign::TextRange(textModel, kInvalidTextIndex, 0);
	}
	else
		CalcCurrentTextRange();
	
	return *this;
}

XMLContentIterator& XMLContentIterator::operator += (int32 offset)
{
	ASSERT(fPosition + offset >= 0 && fPosition + offset <= fElement->GetChildCount());
	ASSERT_MSG(fCurrent.IsValid(), "XMLContentIterator: ++ off end?");

	if (offset == 0)
		return *this;
		
	fPosition += offset;
	
	CalcCurrentTextRange();
	
	return *this;
}

XMLContentIterator& XMLContentIterator::operator -= (int32 offset)
{
	ASSERT(fPosition + offset >= 0 && fPosition + offset <= fElement->GetChildCount());
	ASSERT_MSG(fCurrent.IsValid(), "XMLContentIterator: ++ off end?");

	fPosition -= offset;
	
	CalcCurrentTextRange();
	
	return *this;
}

void XMLContentIterator::CalcCurrentTextRange()
{
	InterfacePtr<ITextModel> textModel(fCurrent.QueryModel());
	
	// -- Check for the beginning run
	if (fPosition == 0)
	{
		// -- If there are no children then there is only one run of content.
		if (fElement->GetChildCount() == 0)
			fCurrent = InDesign::TextRange(textModel, fStartIndex, fEndIndex - fStartIndex);
		else
		{
			TextIndex childStartIndex;
			InterfacePtr<IIDXMLElement> childElement(fElement->GetNthChild(fPosition).Instantiate());
			
			// -- We can't use the utility function here because we always want to know the EXACT position of the
			// -- child, not what the indices of its content item.
			GetElementMarkerPositions(textModel, childElement, &childStartIndex, nil);
			fCurrent = InDesign::TextRange(textModel, fStartIndex, childStartIndex - fStartIndex);
		}
	}
	else if (fPosition == fElement->GetChildCount())
	{
		TextIndex previousChildEndIndex;
		InterfacePtr<IIDXMLElement> previousChildElement(fElement->GetNthChild(fPosition - 1).Instantiate());

		// -- We can't use the utility function here because we always want to know the EXACT position of the
		// -- child, not what the indices of its content item.
		if (!GetElementMarkerPositions(textModel, previousChildElement, nil, &previousChildEndIndex) && previousChildEndIndex != kInvalidTextIndex)
		{
			// if content range was returned, then the end is one past the actual content end 
			//	position. Since we want the actual end position, back it up by one
			ASSERT(previousChildEndIndex >= 0);
			--previousChildEndIndex;
		}

		fCurrent = InDesign::TextRange(textModel, previousChildEndIndex + 1, fEndIndex - (previousChildEndIndex + 1));
	}
	else
	{
		// -- We can't use the utility function here because we always want to know the EXACT position of the
		// -- child, not what the indices of its content item.
		TextIndex previousChildEndIndex;
		InterfacePtr<IIDXMLElement> previousChildElement(fElement->GetNthChild(fPosition - 1).Instantiate());
		if (!GetElementMarkerPositions(textModel, previousChildElement, nil, &previousChildEndIndex) && previousChildEndIndex != kInvalidTextIndex)
		{
			// if content range was returned, then the end is one past the actual content end 
			//	position. Since we want the actual end position, back it up by one
			ASSERT(previousChildEndIndex >= 0);
			--previousChildEndIndex;
		}

		TextIndex childStartIndex;
		InterfacePtr<IIDXMLElement> childElement(fElement->GetNthChild(fPosition).Instantiate());
		GetElementMarkerPositions(textModel, childElement, &childStartIndex, nil);

		fCurrent = InDesign::TextRange(textModel, previousChildEndIndex + 1, (childStartIndex == kInvalidTextIndex) ? 0 : childStartIndex - (previousChildEndIndex + 1));
	}
}


//
// XMLContentIterator::GetElementMarkerPositions
//
// Attempt to return a valid marker range for the given element
//
// @returns kTrue if marker positions returned; kFalse if content range is returned
//
bool16 XMLContentIterator::GetElementMarkerPositions(ITextModel *textModel, IIDXMLElement *element, TextIndex *startIndex, TextIndex *endIndex)
{
	bool16 isMarkerRange(kTrue);

	switch (element->GetContentReference().GetContentType()) {
	case XMLContentReference::kContentType_Table:
		{
			// a table element, return the table anchor character range as content range
			InterfacePtr<ITableTextContainer> tableTextContainer(element->GetContentReference().GetUIDRef(), UseDefaultIID());
			if (startIndex)
				*startIndex = tableTextContainer->GetAnchorTextIndex();
			if (endIndex)
				*endIndex = tableTextContainer->GetAnchorTextIndex()+tableTextContainer->GetAnchorSpan();

			isMarkerRange = kFalse;
		}
		break;

	case XMLContentReference::kContentType_Text:
	case XMLContentReference::kContentType_PageItem:
		{
			InterfacePtr<ITextIndexIDList> textIndexIDList(static_cast<ITextIndexIDList*>(textModel->QueryStrand(kTextIndexIDListStrandBoss, ITextIndexIDList::kDefaultIID)));
			InterfacePtr<const ITextIndexIDRange> textIndexIDRange(element, UseDefaultIID());
			TextIndex start(textIndexIDList->GetTextIndex(textIndexIDRange->GetStart()));
			if (startIndex)
				*startIndex = start;
			if (endIndex)
				*endIndex = (textIndexIDRange->GetEnd() == kInvalidTextIndexID) ? start : textIndexIDList->GetTextIndex(textIndexIDRange->GetEnd());
		}
		break;

	default:
		{
			if (startIndex)
				*startIndex = kInvalidTextIndex;
			if (endIndex)
				*endIndex = kInvalidTextIndex;
		}
		break;
	}

	return isMarkerRange;
}

