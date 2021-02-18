//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextMiscellanySuite.h $
//  
//  Owner: Michael Martz
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
//  Note:
//  
//========================================================================================

#pragma once
#ifndef _ITextMiscellanySuite_
#define _ITextMiscellanySuite_

#include "IPMUnknown.h"
#include "TextEditorModelID.h"
#include "CTextEnum.h"
#include "BravoForwardDecl.h"	// for kDontKnowScript

class WideString;
class IPMFont;
class GraphicsData;
class IControlView;
class IActiveContext;

/**
	@ingroup text_suite
*/
class ITextMiscellanySuite : public IPMUnknown
	{
	//____________________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_ITEXTMISCELLANYSUITE };

	//____________________________________________________________________________________________
	//	Member functions
	//____________________________________________________________________________________________
	public:
		//________________________________________________________________________________________
		//	DESCR:		Should the "Fill with Placeholder text" function be enabled for the
		//				selection.
		//
		//	RETURNS:	kTrue / kFalse
		//________________________________________________________________________________________
			virtual bool16			CanFillWithPlaceHolderText (void) const = 0;

		//________________________________________________________________________________________
		//	DESCR:		Process commands in a sequence which fill with placeholder text those
		//				items in the selection.
		//
		//	RETURNS:	Error code.
		//________________________________________________________________________________________
		virtual ErrorCode		FillWithPlaceHolderText (int32 script = kDontKnowScript) = 0;



		/**
			always clears parameter "word" and then
			copies the first word (according to dictionary code) into the parameter
			if no selection, word is blank **/
		virtual ErrorCode GetFirstSelectedWord(PMString& word) = 0;

		/**
		@param text is overwritten with the currently selected text in this selection.  text is set to empty if there's no selection
		**/
		virtual ErrorCode GetSelectedText(WideString &text) = 0;

		/**
			always clears theChars & glyphList
			puts the characters and the glyphs represented by the selection into the
			two data structures and can report the INITIAL font as well.
			@param theChars will have the selected characters
			@param glyphList contains the selected glyphs
			@param selectedFont (if non-nil) will be set with an add'refed font
			if all of the characters have the same font, combining glyphs (e.g. ligatures) can produce fewer glyphs than characters.
		*/
		virtual ErrorCode GetGlyphsFromSelection(WideString& theChars, K2Vector<Text::GlyphID>& glyphList, IPMFont **selectedFont = nil) = 0;

		// Determine the typing range based on the selection and special character, and set RangeData on the global workspace
		virtual ErrorCode SetWorkSpaceTypingRangeData(int32 specialCharacter, PMIID interfaceID) = 0;

		/**
		@param result is filled in with kTrue or kFalse to indicate whether the selection is in overset
		*/
		virtual ErrorCode IsSelectionCompletelyOverset(bool16 &result) = 0;

		/**
		@return result is filled in with kTrue or kFalse to indicate whether the selection supports frame edge drawing
		*/
		virtual bool16 CanDrawSelectedFrameEdges() = 0;

		/**
		Draws the frame edges
		*/
		virtual void DrawSelectedFrameEdges(GraphicsData *gd) = 0;

		/**
		Places the frame thread bounding box into @param invalRect
		*/
		virtual void GetFrameThreadsBBox(GraphicsData *gd, PMRect& invalRect) = 0;

		/**
			Values for CanSelectAnotherFrame and SelectAnotherFrame to select various threaded frames in a frame list.
			kNextFrame selects frame after currently selected frame.
			kPreviousFrame select frame before currently selected frame.
			kFirstFrame selects first frame in the frame list of the selection.
			kLastFrame selects last frame in the frame list of the selection.
		*/
		typedef enum { kNextFrame, kPreviousFrame, kFirstFrame, kLastFrame } WhichOtherFrame;

		/**	Can the selection be changed to the appropriate TextFrame relative to the current selection.
			@param which, which frame in the threaded frame list to select, as an WhichOtherFrame value
			@param targetLayer, selection on source IDocumentLayer will be moved to targetLayer IDocumentLayer.
			@param view, the IControlView to use.
			@param guideLayerOnly, kTrue if moving guide layers, kFalse otherwise.
			@param replaceOrAdd - Selection::kReplace or Selection::kAddTo
			@param bDuplicate, kTrue to duplicate the selection before moving to the destination layer.
			@return ErrorCode
		 */
		virtual bool16 CanSelectAnotherFrame(WhichOtherFrame which) = 0;

		/**
			Change the selection to the appropriate TextFrame relative to the current selection
			@param which, which frame in the threaded frame list to select, as an WhichOtherFrame value
			@param ac, IActiveContext to use for the selection action. Typically driven from an ActionComponent.
		*/
		virtual ErrorCode SelectAnotherFrame(WhichOtherFrame which, IActiveContext* ac) = 0;

		/**
		currently we only do offscreening for shapes that are in the selection
		*/
		virtual bool16 CanOffscreenWithShape(IPMUnknown *pShape) = 0;

		/**
		@param result (in InCopy) is filled in with kTrue or kFalse to indicate whether the selection is in deleted text
		@param result (in InDesign) is filled in with kFalse because deletions are not accessible in InDesign (yet?)
		*/
		virtual ErrorCode IsSelectionInDeletedText(bool16 &result) = 0;

		/** DoesSelectionContainTableAnchors
		@return true if this selection is one which is valid for the find font dialog to leave when exitting
		*/
		virtual bool16	IsSafeSelectionForFindFontDialog() const = 0;

		/** 
		Ask the user if they want to check out the story or, InCopy only, alert them that
		they cannot make edits.  IInCopyBridgeUIUtils must be available.
		@return kTrue if check out was successful
		*/
		virtual bool16 WantCheckOutOrAlertCant() = 0;

		/**
			Enum for specifying a hint for IsHiddenTextInSelection to use when the selection is an insertion point.
		*/
		enum HintForInsertionPoint
		{ 
			/** IsHiddenTextInSelection doesn't look back or forward. */
			kDontLook, 
			/** IsHiddenTextInSelection looks back. */
			kLookBack, 
			/** IsHiddenTextInSelection looks forward. */
			kLookForward 
		};

		/**
			Detect if the selection contains hidden conditional text. If the selection is a range it is examined for 
			hidden text but if it is an insertion point then use the hint to look back, forward or don't look for the
			case of backspace versus forward delete versus typing.
			@param hint A hint for detecting hidden text if selection is an insertion point.
			@return kTrue if found hidden conditional text.		
		*/
		virtual bool16 IsHiddenTextInSelection(HintForInsertionPoint hint = kDontLook) = 0;
	};

#endif // _ITextMiscellanySuite_
