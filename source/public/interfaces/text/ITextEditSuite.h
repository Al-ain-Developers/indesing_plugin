//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextEditSuite.h $
//  
//  Owner: Zak Williamson
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
//  Notes:
//  
//========================================================================================

#pragma once
#ifndef __ITextEditSuite__
#define __ITextEditSuite__

#include "IPMUnknown.h"
#include "TextID.h"
#include "CTextEnum.h"
#include "WideString.h"


/** This interface is implemented by the abstract selection boss and by the concrete selection
	bosses for text.
	@ingroup text_suite
*/
class ITextEditSuite : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTEDIT_ISUITE };

			/** Are insertions/deletions allowed?  Returns kFalse is the story is locked, for example.
			 */
		virtual bool16 CanEditText() const = 0;

			/** Insert the given Unicode character.  Replaces the current selection.
			 */
		virtual ErrorCode InsertCharacter(UTF32TextChar ch) = 0;

		typedef enum { kThisPage, kContinuedFrom, kContinuedOn } PageNumberType;
			/** Insert a page number, continued on, or continued from marker.
				Replaces the current selection.
			 */
		virtual ErrorCode InsertPageNumber(PageNumberType pageNumberType) = 0;

			/** Insert a next column, next frame, next page, next odd page, or next even page
				character.  Replaces the current selection.
			 */
		virtual ErrorCode InsertBreakCharacter(Text::StartBreakLocation breakLocation) = 0;

			/** Can a footnote be inserted here?
			 */
		virtual bool16 CanInsertFootnote() = 0;

			/** Insert a footnote OR a footnote designator into an existing footnote.
				Fails inserting into tables, notes, etc.
			 */
		virtual ErrorCode InsertFootnote() = 0;

			/** Can a variable be converted here? 
				Optionally specify the class of a variable. If one is specified, this method will only return true if
				a variable of that type can be converted.
			 */
		virtual bool16 CanConvertVariable(ClassID whichVariableClass = kInvalidClass) const = 0;

			/** Convert Variable to text.
			 */
		virtual ErrorCode ConvertVariableToText(ClassID whichVariableClass = kInvalidClass) = 0;

			/** Insert this Unicode string.  Replaces the current selection.
				Goes through the user typing path and therefore includes font locking
				behavior, command joining, and forcing recomposition to complete before returning.
			 */
		virtual ErrorCode InsertText(const WideString& theText) = 0;

			/** Deletes the current selection.  If the selection is an insertion point,
				deletes the character to the left of the insertion point.
				This goes through the user typing path, and therefore includes command
				joining behavior and forcing recomposition to complete before returning.
			 */
		virtual ErrorCode Delete(CharCounter numChars = 1) = 0;

			/** The same as Delete(), if a range is selected.  If the selection is an
				insertion point, deletes the character to the right of the insertion point.
				This goes through the user typing path, and therefore includes command
				joining behavior and forcing recomposition to complete before returning.
			 */
		virtual ErrorCode ForwardDelete(CharCounter numChars = 1) = 0;

			/**	Insert an endnote
			 */
		virtual ErrorCode InsertEndnote() = 0;

		/** Can an endnote be inserted here?
		*/
		virtual bool16 CanInsertEndnote() = 0;

		/** Is selection in endnote story?
		*/
		virtual bool16 IsTextSelectionInEndnoteStory() = 0;

		/** Is selection within an endnote text?
		*/
		virtual bool16 IsInsideEndnoteTextRange() = 0;

		/** Is selection an endnote reference?
		*/
		virtual bool16 IsInsideEndnoteAnchor() = 0;

		/** Jump to the matching endnote anchor if current selection is in an endnote text.
		*/
		virtual bool16 GotoEndnoteAnchor() = 0;

		/** Jump to the matching endnote text if current selection is an endnote reference.
		*/
		virtual	bool16 GotoEndnoteTextRange() = 0;
};

#endif
