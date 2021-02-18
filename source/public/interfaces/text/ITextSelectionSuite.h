//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextSelectionSuite.h $
//  
//  Owner: Richard Rodseth
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
#ifndef _ITextSelectionSuite_
#define _ITextSelectionSuite_

#include "IPMUnknown.h"
#include "TextEditorID.h"
#include "ISelectionMessages.h"

class ITextFocus;
class RangeData;
class IControlView;
class ITextStoryThread;
class ITableModel;
class ITextModel;
class IShape;
class GraphicsData;
#include "PMPoint.h"

/** for internal use only */
class TextSelectionState
{
public:
	virtual ~TextSelectionState() {} //public only until table tracker is refactored

	virtual ITextStoryThread* GetStoryThread() = 0;
	virtual ParcelKey GetLastParcelKey() = 0;
	virtual IControlView* GetView() = 0;
};


/** Interface for the text selection suite.

	@note several declarations are marked for internal use only.  These declarations
		are still present in this file in their current form due to time contraints only.
		Expect that they will be modified or removed in a future version of this interface.

	@ingroup text_suite
	@ingroup text_select
*/
class ITextSelectionSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITEXTSELECTION_SUITE};

/** for internal use only */
	virtual void SetActiveConcreteSelection( ClassID ) = 0;
/** for internal use only */
	virtual ClassID GetActiveConcreteSelection() = 0;

/** select text in the view or views associated with this suite.
	@param story the story to select.
	@param range the text range to select.
	@param doScroll whether to scroll the new selection into view.
	@param scrollTo if doScroll == Selection::kScrollIntoView, the range of text that should be brought into view.
	@return on success, kTrue, otherwise, kFalse.
*/
	virtual bool16 SetTextSelection( const UIDRef& story, const RangeData& range, Selection::ScrollChoice doScroll, const RangeData* scrollTo) = 0;


/** select text in the view or views associated with this suite.
	@param targetingBoss a boss with an ITextTarget interface containing the story and range to select.
	@param doScroll whether to scroll the new selection into view.
	@param scrollTo if doScroll == Selection::kScrollIntoView, the range of text that should be brought into view.
	@return on success, kTrue, otherwise, kFalse.
*/
	virtual bool16 SetTextSelection( IPMUnknown* targetingBoss, Selection::ScrollChoice doScroll, const RangeData* scrollTo) = 0;

	enum ToggleType { kFootnotesOnly, kAnchoredFramesOnly, kAnyType };

/** can we move the selection from anchored text (anchored frame, footnote, etc.) to the anchor itself (or vice-versa)
	@param type can control what sort of toggling to test
	@return can Toggle, kTrue, otherwise, kFalse.
*/
	virtual bool16 CanToggleAnchorSelection(ToggleType type = kAnyType) = 0;

/** move the selection from anchored text (anchored frame, footnote, etc.) to the anchor itself (or vice-versa)
	@param type can control what sort of toggling to allow
	@return on success, kTrue, otherwise, kFalse.
*/
	virtual bool16 ToggleAnchorSelection(ToggleType type = kAnyType) = 0;

	enum Change { kMoveSelection = 0, kMove = kMoveSelection, kReplaceSelection = kMove, kExtendSelection = 1, kExtend = kExtendSelection};
	enum Units { kNone = 0, kCharacter, kChar = kCharacter, kWord, kLine, kSentence, kParagraph = 5, /*kFrame, kPage, kSpread,*/ kStory = 9 };
	enum Direction { kNext, kPrev, kStart, kEnd, kAll  };

/** select text relative to the current text selection in the view or views associated with this suite.
	@param moveOrExtend kExtend causes the selection to be extended from its current position, kMove causes
	the selection to move relative to its current position.
	@param textUnits the units of text by which the selection changes.
	@param direction the direction by which the selection changes.
	@param autoScroll whether to scroll the new selection into view.
	@return on success, kTrue, otherwise, kFalse.
*/
	virtual bool16 ChangeTextSelection( Change moveOrExtend,  Units textUnits, Direction direction, Selection::ScrollChoice autoScroll ) = 0;

/** without changing the current text selection, scroll into view the given text location of the story currently containing the selection.
	@param view the view to be scrolled.
	@param location the text range to scroll into view.
	@return on success, kTrue, otherwise, kFalse.
*/
	virtual bool16	ScrollViewTo( IControlView* view, const RangeData& location ) = 0;

/** for internal use only */
	virtual bool16	ScrollViewToSelection( IControlView* view) = 0;

/** for internal use only */
	virtual bool16	CenterViewOn( IControlView* view, const RangeData& location ) = 0;

/** for internal use only */
	virtual bool16	CenterSelectionInView( IControlView* view) = 0;


/** for internal use only */
	virtual TextSelectionState* SelectTextInViewBegin(
				IControlView* view, const PBPMPoint& viewLoc,
				ITextStoryThread* theStoryThread, ParcelKey theParcel,
				Change change, Units units) = 0;

/** for internal use only */
	virtual void SelectTextInViewContinue( TextSelectionState* state, const PBPMPoint& viewLoc, ParcelKey parcelHitKey) = 0;

/** for internal use only */
	virtual void SelectTextInViewFlush(    TextSelectionState* state) = 0;

/** for internal use only */
	virtual void SelectTextInViewSuspend(  TextSelectionState* state) = 0;

/** for internal use only */
	virtual void SelectTextInViewResume(   TextSelectionState* state, const PBPMPoint& viewLoc, ParcelKey parcelHitKey) = 0;

/** for internal use only */
	virtual void SelectTextInViewEnd(      TextSelectionState* state) = 0;


/** for internal use only */
	virtual bool16	IsTextSelectionInTable() const = 0;
	virtual bool16 IsTextSelectionInFootnote() const = 0;
	virtual bool16	IsInsertionPoint() const = 0;

/** for internal use only */
	virtual bool16	CanTrackerExtendTableSelection(ITableModel *trackerFramesTableModel) const = 0;

protected:
/** for internal use only */
	enum DrawChoice { kDontDrawSelection, kDrawSelection};

private:
/** for internal use only - draw the selection only if the selection is within the IShape specified */
	virtual bool16 DrawShapeDynamicTextHighlight( GraphicsData* gd, IShape *textFrameShape) = 0;
/** for internal use only - draw the selection only for one frame */
	virtual bool16 DrawOneFrameHighlight( GraphicsData *gd, IShape *frameShape) = 0;
/** for internal use only */
	virtual	void DrawDynamicHighlight( IControlView* view, const UIDRef& story, const RangeData& range) = 0; //must contain anchor end
/** for internal use only */
	virtual	RangeData GetDynamicHighlight()  = 0;
/** for internal use only */
	virtual	void ResetDynamicHighlight()  = 0;
/** for internal use only */
	virtual bool16 SetTextSelectionHmm( const UIDRef& story, const RangeData& range, Selection::ScrollChoice doScroll, const RangeData* scrollTo, DrawChoice drawIt) = 0;

	friend class TextSelectionIntegratorSuite;
	friend class TextSelectionIntegratorSuiteTemp;
	friend class TextCellTextSelectTracker;
	friend class TextCellSelectTracker;
	friend class HorizontalIBeamCrsrProvider;
	friend class FootnoteTextSelectTracker;
	friend class FrameShape;
	friend class TextSelectionHighlighter;
	friend class CWaxRunText;
	friend class TableShape;
	friend class CLineSegmentAdornment;
	friend class MoveRowColumnTracker;
	friend class CharacterAlternatesData;

};

#endif // _ITextSelectionSuite_


/*
 	699	Move to the right one character 	kChar	kNext	kMove		Right arrow
 	700	Move to the left one character 		kChar	kPrev	kMove		Left arrow
 	701	Move up one line 					kLine	kPrev	kMove		Up arrow
 	702	Move down one line 					kLine	kNext	kMove		Down arrow
 	703	Move to the right one word 			kWord	kNext	kMove		Cmd + Right Arrow
 	704	Move to the left one word 			kWord	kPrev	kMove		Cmd + Left Arrow
 	705	Move to the start of the line 		kLine	kStart	kMove		Home
 	706	Move to the end of the line 		kLine	kEnd	kMove		End
 	707	Move to the previous para 			kPara	kPrev	kMove		Cmd + Up Arrow
 	708	Move to the next para 				kPara	kNext	kMove		Cmd + Down Arrow
 	709	Move to end of story 				kStory	kEnd	kMove		Cmd + End
 	710	Move to begining of story 			kStory	kStart	kMove		Cmd + Home
 	712	Select word 						kWord	kAll	kMove		Double Click

 	713	Select one character to the right 	kChar	kNext	kExtend		Shift + Right  Arrow
 	714	Select one character to the left 	kChar	kPrev	kExtend		Shift + Left  Arrow
 	715	Select one word to the right 		kWord	kNext	kExtend		Cmd + Shift + Right Arrow
 	716	Select one word to the left 		kWord	kPrev	kExtend		Cmd + Shift + Left Arrow
 	717	Select to the start of the line 	kLine	kStart	kExtend		Shift + Home
 	718	Select to the end of the line 		kLine	kEnd	kExtend		Shift + End
 	719	Select one line above 				kLine	kPrev	kExtend		Shift +  Up Arrow
 	720	Select one line below 				kLine	kNext	kExtend		Shift + Down Arrow
 	721	Select one paragraph before			kPara	kPrev	kExtend		Cmd + Shift + Up Arrow
 	722	Select one paragraph forward 		kPara	kPrev	kExtend		Cmd + Shift + Down Arrow
 	723	Select all chars. in story 			kStory	kAll	kExtend		Cmd +  A
 	724	Select chars. from insertion point	kChar	kAll	kExtend		Shift + Click
 	725	Select to end of story 				kStory	kEnd	kExtend		Cmd + Shift + End
 	726	Select to beginning of story 		kStory	kStart	kExtend		Cmd + Shift + Home
*/
