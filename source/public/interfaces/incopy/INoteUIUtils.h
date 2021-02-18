//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/INoteUIUtils.h $
//  
//  Owner: Wai Cheuk
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
#ifndef __INOTEUIUTILS__
#define __INOTEUIUTILS__

#include "NoteID.h"
//-----------------------------------
//	Forward References
//
class IPanelControlData;
class ITextLines;
class IControlView;
class IWaxStrand;
class ITextModel;
class ISelectionManager;

#include "IPMUnknown.h"
#include "UIDList.h"
#include "PMPoint.h"
#include "IRangeData.h"

/** Utility interface for Notes. 
	Most of the utilities are not used in CS anymore. Instead, you should use INoteSuite and INoteSuiteUtils to achieve the same purpose.
*/    
class INoteUIUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_INOTEUIUTILS };
	enum SelectionOwnerType { kNone, kSelectionInLayout, kSelectionInGalley, kSelectionInNoteInGalley, kSelectionInNoteInLayout };
	

/**	Not used anymore. You can use INoteSuitUtils::NavigateNote(ISelectionManager* selMgr, IControlView *docView, TextIndex fromThisTextIndex, UIDRef storyRef, INoteSuite::NavigateType type) to navigate Notes.
	@param selMgr 
	@param fromThisTextIndex 
	@param docRef 
	@param storyRef 
 */
	virtual void GoToNextNote(ISelectionManager* selMgr, TextIndex fromThisTextIndex, UIDRef docRef, UIDRef storyRef) = 0;
				//	Search the next note from the given text index in the main story.
				//	Display the content in the appropriate UI and ends with selecting
				//	the note anchor of the note we're searching. 
	

/**	Not used anymore. You can use INoteSuitUtils::NavigateNote(ISelectionManager* selMgr, IControlView *docView, TextIndex fromThisTextIndex, UIDRef storyRef, INoteSuite::NavigateType type) to navigate Notes.
	@param selMgr 
	@param fromThisTextIndex 
	@param docRef 
	@param storyRef 
 */
	virtual void GoToPreviousNote(ISelectionManager* selMgr, TextIndex fromThisTextIndex, UIDRef docRef, UIDRef storyRef) = 0;
				//	Search the previous note from the given text index in the main story.
				//	Display the content in the appropriate UI and ends with selecting
				//	the note anchor of the note we're searching. 
	

/**	Not used anymore. You can use INoteSuite::DoScrollToNote(IControlView* view, IControlView* docView) 
	@param selMgr 
	@param noteAnchorPosition 
	@param storyRef 
 */
	virtual void ShowNoteAnchorAt(ISelectionManager* selMgr, TextIndex noteAnchorPosition, UIDRef storyRef) = 0;
				// Select the note anchor at the given text index in the given story and 
				// scroll the page to the location if the anchor is not already in the 
				// current page


/**	This method draws a thick caret over the galley text with the given caret offset
	in the given line index.  This can be used by the cursor provider to show
	visual feedback that galley text is being hovered on.
	@param writingView The galley/story control view
	@param textLines The galley's ITextLines
	@param lineIndex The line index
	@param caretOffsetIntoLine The text index
	@param runIndex The text run index, default = -1, -1 means to use param caretOffsetIntoLine
	@param caretOffsetIntoRun default to -1, -1 means to use param caretOffsetIntoLine
			If runIndex != -1 and caretOffsetIntoRun  != -1, means to use param caretOffsetIntoRun
 */
	virtual void DrawGalleyCaret(IControlView* writingView, ITextLines* textLines, int32 lineIndex, int32 caretOffsetIntoLine, int32 runIndex = -1, int32 caretOffsetIntoRun = -1) = 0;

/**	This method draws a thick caret over the galley text with the given drawPt and endPt. Used by DrawGalleyCaret
	@param writingView The galley control view
	@param startPt The start point
	@param endPt The end point
 */
	virtual void RenderThickCaret(IControlView* writingView, const IPMPoint& startPt, const IPMPoint& endPt) = 0;
				// 

/**	Check if textIndex is inside a Note.
	@param storyRef The story
	@param textIndex The text index
	@param anchorPosition return the text anchor index of the Note or kInvalidTextIndex
	@return bool16 kTrue means textIndex is inside a Note, kFalse means textIndex is not inside a Note
 */
	virtual bool16 TextFocusInNote(UIDRef storyRef, TextIndex textIndex, TextIndex* anchorPosition) = 0;

/**	Not used anymore.
	@param storyRef 
	@param textFocus 
	@param owneItemPosition 
	@return bool16 
 */
	virtual bool16 TextFocusInOwnedItem(UIDRef storyRef, TextIndex textFocus, TextIndex* owneItemPosition) = 0;
				// If textFocus is inside any owned item (regardless of UI) return kTrue and its anchor position,
				// otherwise, return kFalse and kInvalidTextIndex in anchorPosition


/**	Not used anymore.
	@param range 
 */
	virtual void SetGalleyWritingSelection(  const RangeData& range) = 0;
				// activate the galley writing widget;
				// hilite selection from start to end.


/**	Not used anymore.
	@param ISelectionManager* 
 */
	virtual void SelectNextNote(ISelectionManager*) = 0;
				// Actions driven calls - main note menu, palette fly-out menu, kbsc


/**	Not used anymore.
	@param ISelectionManager* 
 */
	virtual void SelectPrevNote(ISelectionManager*) = 0;
				// Actions driven calls - main note menu, palette fly-out menu, kbsc


/**	Not used anymore. You can use INoteSuite::DoShowHideNote(IControlView* view, IControlView* docView) 
	@param none
 */
	virtual void ToggleNoteDisplay() = 0;
				// Actions driven calls - main note menu, palette fly-out menu, kbsc


/**	Not used anymore. You can use INoteSuite::DoExpandAllNotes(IControlView* view, IControlView* docView) 
	@param none
 */
	virtual void ExpandAllNotes() = 0;
				// Expand all inline notes in the view story


/**	Not used anymore. You can use INoteSuite::DoCollapseAllNotes(IControlView* view, IControlView* docView)
	@param none
 */
	virtual void CollapseAllNotes() = 0;
				// Collapse all inline notes in the view story


/**	Not used anymore. You can use INoteSuite::DoRemoveAllNotes(IControlView* view, IControlView* docView, IDocument *doc)
	@param none
 */
	virtual void DoClearAllNotes() = 0;
				// Remove all note data from the view document (layout),
				// or remove all note data from the view story (galley)


/**	Not used anymore. You can use INoteSuite::DoOpenNote(IControlView* view, IControlView* docView)
	@param none
 */
	virtual void DoOpenCloseNote() = 0;
				// Galley: expand or collapse inline note (a toggle) based on current selection
				// Layout: open the selected note in the note palette


/**	Not used anymore.
	@param none
	@return bool16 
 */
	virtual bool16 GetFindChangeTextWalker() const = 0;

/**	Not used anymore.
	@param none
	@return bool16 
 */
	virtual bool16 GetSpellTextWalker() const = 0;
				// find text walker is active, find/change or spell


/**	Deselect note text selection.
	@param noteView The Note palette control view
	@return bool16 kTrue means active selection is Note selection and has been deselect
				   kFalse means active selection is not Note selection
 */
	virtual bool16 GiveUpNoteSelection(IControlView *noteView = nil) = 0;
	
/**	Yields selection back to the frontmost document window
	@param none
	@return ErrorCode 
 */
	virtual ErrorCode SetFrontDocViewSelection() = 0;

/**	Draw a sqare box around the expansion zone near the note anchor
	character given in caret (RangeData(NoteAnchorIndex, RangeData::kLeanForward))
	@param view The galley control view
	@param caret The range to be drawn
	@param storyRef The story
 */
	virtual void DrawHitTestBox(IControlView* view, const RangeData &caret, UIDRef storyRef) = 0;

/**	Not used anymore.
	@param textModel 
	@param cursorIndexHit 
	@param hitTestExpandOffset 
	@param anchorIndex 
	@return bool16 
 */
	virtual bool16 GetNoteRegion(ITextModel* textModel, TextIndex cursorIndexHit, int32 hitTestExpandOffset, TextIndex& anchorIndex) const = 0;
				// With the given cursor position in a story and an expansion zone (in terms of
				// number of characters), this method returns if there is any note near
				// the cursor position with hitTestExpandOffset as offset to its right
				// and to its left position.  It returns kTrue and the note anchor position
				// if note is found in the region.  It returns kFalse if no note is found.

/**	Put focus into an inline note.
	@param storyRef The story
	@param noteDataRef The Note
 */
	virtual void ActivateInlineNote(UIDRef storyRef, UIDRef noteDataRef) = 0;

/**	Invalidate the front document layout view to force redraw.
	@param none
 */
	virtual void InvalidateLayoutView() = 0;
				
/**	Get current text selection from galley or layout
	@param nStart The begin text index selection
	@param nEnd The end text index selection
	@param storyRef The story
	@return SelectionOwnerType  return INoteUIUtils::kSelectionInGalley, INoteUIUtils::kSelectionInNoteInGalley, INoteUIUtils::kSelectionInNoteInLayout, and INoteUIUtils::kSelectionInLayout
 */
	virtual SelectionOwnerType GetCurrentTextSelection_(TextIndex& nStart, TextIndex& nEnd, UIDRef* storyRef) = 0;
	
/**	check to see if active view is galley/story view
	@param none
	@return bool16 
 */
	virtual bool16 InGalleyView() = 0;

/** Internal Use Only
*/
	virtual void GetCurrentActionState(TextIndex& focusStart, TextIndex& focusEnd, TextIndex& noteAnchorPos,
									   UIDRef& storyRef, bool16& storyHasFocus, bool16& focusInsideNote,
									   bool16& focusInMainStoryThread, bool16& noteHidden, bool16& editable,
									   bool16& focusInsideDeletedText, TextIndex * threadStart = nil, TextIndex * threadEnd = nil) = 0;

/** Internal Use Only
*/
	virtual bool16 GetNewNoteActionState() = 0;
/** Internal Use Only
*/
	virtual bool16 GetConvertToNoteActionState() = 0;
/** Internal Use Only
*/
	virtual bool16 GetOpenNoteActionState() = 0;
/** Internal Use Only
*/
	virtual bool16 GetDeleteNoteActionState() = 0;
/** Internal Use Only
*/
	virtual bool16 GetScrollToAnchorActionState() = 0;
/** Internal Use Only
*/
	virtual bool16 GetConvertToTextActionState() = 0;
/** Internal Use Only
*/
	virtual bool16 GetSplitNoteActionState() = 0;
/** Internal Use Only
*/
	virtual bool16 GetNaviationActionState() = 0;
/** Internal Use Only
*/
	virtual bool16 GetExpandAllNoteActionState() = 0;
/** Internal Use Only
*/
	virtual bool16 GetCollapseAllNoteActionState() = 0;
/** Internal Use Only
*/
	virtual bool16 GetRemoveAllNoteActionState() = 0;
/** Internal Use Only
*/
	virtual bool16 GetDisplayNoteActionState() = 0;
				// Various methods to alllow access to the action states

/** Internal Use Only
*/
	virtual	bool16	GetStoryNoteState(bool16 checkCollapsedState) = 0;
				// helper method

/** 
Removed : DoDragDropNote; use INoteUtils::DoDragDropNoteModel instead
*/

/** Internal Use Only
*/
	virtual bool16 FrontWindowGalley() = 0;
				// InCopy 2.0 -  return the front most galley window

};

#endif // __INOTEUIUTILS__