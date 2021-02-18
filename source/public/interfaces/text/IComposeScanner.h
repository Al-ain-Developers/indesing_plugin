//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IComposeScanner.h $
//  
//  Owner: eric_menninga
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
#ifndef __IComposeScanner__
#define __IComposeScanner__

#include "IPMUnknown.h"
#include "TextID.h"
#include "K2Vector.h"
#include "PMTextUtils.h"
#include "textiterator.h"
#include "IRunInStylesUtils.h"

class AttributeBossList;
class IDrawingStyle;
class WideString;
class IAttrReport;
class RangeData;

/** This is the primary iterator for reading a text model (a story).
	It can return characters and attributes for ranges of text
	@ingroup text_comp
*/
class IComposeScanner : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ICOMPOSESCANNER };

		//-----------------------------------------------------------------------------------------
			/** copies the word at the position. Uses FindSurroundingWord() to find the word, then copies it into copy
				@see FindSurroundingWord
				@param position Copy the word that contains this index
				@param copy Is set to the word found by FindSurroundingWord(). Must be non-nil.
				@param pLanguageUID Set the language applied to the word if non-nil.
				@param func Allows word detection heuristics to be overridden.
				@return the word's starting position.
			*/
		virtual TextIndex CopySurroundingWord(TextIndex position, WideString *copy, UID *pLanguageUID = nil, FuncIsWordChar func = nil ) = 0;

			/** Copies the specified text into the WideString.
				@param position Copy the word that contains this index
				@param length How many characters should be copied
				@param copy must be non-nil. Is set to the text specified
				@return Returns position
			*/
		virtual TextIndex CopyText(TextIndex position, int32 length, WideString *copy) const = 0;
			/** @see CopyText */
		virtual TextIndex CopyText(const RangeData& range, WideString *copy) const = 0;

		//-----------------------------------------------------------------------------------------
			/** @return the word's starting index and optionally the language applied to the word
				@param position Get the word that contains this index
				@param length length of the word, can be nil but default parameter causes ambiguity.
				@param pLanguageUID if non-nil, is set to the language at the position
				@param wordFunc allows the "is a word" function to get overridden
			*/
		virtual TextIndex FindSurroundingWord(TextIndex position, int32 *length, UID *pLanguageUID = nil, FuncIsWordChar wordFunc = nil ) = 0;
			/** @see FindSurroundingWord */
		virtual RangeData FindSurroundingWord(TextIndex position, UID *pLanguageUID = nil, FuncIsWordChar wordFunc = nil ) = 0;

			/** @see FindSurroundingWord */
		virtual TextIndex FindSurroundingWordUsingWordCharFuncOnly(TextIndex position, int32 *length, UID *pLanguageUID = nil, FuncIsWordChar wordFunc = nil ) = 0;
			/** @see FindSurroundingWord */
		virtual RangeData FindSurroundingWordUsingWordCharFuncOnly(TextIndex position, UID *pLanguageUID = nil, FuncIsWordChar wordFunc = nil ) = 0;

		//-----------------------------------------------------------------------------------------
			/** @return the paragraph's starting index, optionally including the end-of-story mark
				@param position Get the paragraph that contains this index
				@param length Get the length of the paragraph, can be nil but default parameter causes ambiguity.
				@param excludeEOS if the paragraph ends at the story end (no CR) should the story end get counted or not?
				@param validatePara Only used in the debug build for more rigorous internal checks
			*/
		virtual TextIndex FindSurroundingParagraph(TextIndex position, int32 *length, bool16 excludeEOS = kTrue, bool16 validatePara = kTrue) const = 0;
			/** @see FindSurroundingParagraph */
		virtual RangeData FindSurroundingParagraph(TextIndex position, bool16 excludeEOS = kTrue, bool16 validatePara = kTrue) const = 0;


		//-----------------------------------------------------------------------------------------
			/** @return the specified attribute applied at startPosition. Will join runs when this attribute
				is unchanged until endPosition.
				@param startPosition initial text location to start from
				@param endPosition text location to not bother looking beyond
				@param typeAttribute the text attribute in question
				@param length pointer to value that will contain the number of characters after
							startPosition that share the same attribute value for forward direction 
							and number of characters from end position for backwards direction.
				@param moveBackwards specifies the direction in which above stated length parameter is to be reported.
							The value is kTrue for backwards direction and kFalse for forward direction.
			*/
		virtual const IAttrReport* QueryAttributeAt(int32 startPosition, int32 endPosition,
												ClassID typeAttribute, int32 *length = nil, bool16 moveBackwards = kFalse) const = 0;
			/** @see QueryAttributeAt */
		virtual const IAttrReport* QueryAttributeAt( const RangeData& range,
												ClassID typeAttribute, int32 *length = nil, bool16 moveBackwards = kFalse) const = 0;

			/** This version of QueryAttributeAt works on collections of attributes.
				@precondition Params must not contain any duplicate ClassIDs.
					Results must be empty on input (results->CountBosses() == 0)
				@postcondition Results will contain attributes for each classID of params (results->CountBosses() == params.Length())
					If length != nil on input, *length will be the number of characters
					starting at startPosition that have the same values for all of the given text attributes.
					length <= endPosition - startPosition
				@param startPosition initial text location to start from
				@param endPosition text location to not bother looking beyond
				@param firstAttribute iterator.begin() of list of attributes being examined
				@param endAttribute iterator.end() of list of attributes being examined
				@param results filled with the list of attributes in question. Should NOT be nil.
				@param length pointer to value that will contain the number of characters after
							startPosition that share the same attribute value for forward direction 
							and number of characters from end position for backwards direction.
				@param moveBackwards specifies the direction in which above stated length parameter is to be reported.
							The value is kTrue for backwards direction and kFalse for forward direction.
			*/
		virtual void QueryAttributeAt(
			int32 								startPosition,
			int32 								endPosition,
			K2Vector<ClassID>::const_iterator 	firstAttribute,
			K2Vector<ClassID>::const_iterator	endAttribute,
			AttributeBossList*					results,		// output: AttributeBossList of att
			int32*								length = nil,			// output: can be nil on input
			bool16								moveBackwards = kFalse
		) const = 0;

		//-----------------------------------------------------------------------------------------
			/** @return a NON-ADDREF'D drawingstyle that reflects ALL attributes at the passed in location
				The returned length is not guaranteed to be precise. It may be that the next run shares these
				attributes due to the lazy combining that can occur.
				@param position Get attributes for this location
				@param lenleft If non-nil, indicates how many characters (at least) share these attributes
			*/
		virtual IDrawingStyle* GetCompleteStyleAt(TextIndex position, int32 *lenleft = nil) = 0;

			/** @return a NON-ADDREF'D drawingstyle that reflects the paragraph attributes at the passed in location
				The returned length is not guaranteed to be precise. It may be that the next paragraph shares these
				attributes due to the lazy combining that can occur. Run-in styles can also affect the length
				@param position Get attributes for this location
				@param lenleft If non-nil, indicates how many characters (at least) share these attributes
				@param paragraphStart If non-nil, indicates the position of the start of the paragraph containing position
			*/
		virtual IDrawingStyle* GetParagraphStyleAt(TextIndex position, int32 *lenleft = nil, TextIndex *paragraphStart = nil) = 0;

		virtual const RunInStyleResults& GetRunInStylesResultsAt(TextIndex position, TextIndex *paragraphStart = nil) = 0;

			/** This is the primary method that text composition uses to iterate the text model
				@return an iterator on the buffer to characters. This buffer is referenced in the TextIterator, therefore, it
				is valid beyond the next call to the compose scanner.
				@param position index to get the data for
				@param newstyle address of pointer to drawingstyle. If non-nil, the address will return
								pointing to an AddRef'd drawingstyle
				@param numChars if non-nil, number of characters (either 2 or 4 bytes) in the returned iterator that have the
									same style
			*/
		virtual TextIterator QueryDataAt(TextIndex position, IDrawingStyle **newstyle, int32 *numChars) = 0;

		//-----------------------------------------------------------------------------------------
			/** Indicates that the model has changed for the indicated range, called automatically */
		virtual void AttributesChanged(TextIndex start, int32 length) = 0;
			/** Clears the cache. Shouldn't be necessary to call */
		virtual void Clear() = 0;

		virtual void StartComposingNestedStyles() = 0;
		virtual void StopComposingNestedStyles() = 0;
};




#endif		// __IComposeScanner__


