//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/INoteSuite.h $
//  
//  Owner: ???
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
#ifndef __INoteSuite__
#define __INoteSuite__

#include "IPMUnknown.h"
#include "InCopySharedID.h"
#include "ITextSelectionSuite.h"

class IControlView;
class ISelectionManager;
class IDocument;

/** A selection related text suite interface to perform the Notes actions
*/
class INoteSuite : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_INOTESUITE };

/** The navigation type */
	enum NavigateType { kNextNote=0, kPreviousNote };
/** The type of text content copied to convert to a Note 	*/
	enum CopyToNoteType {kWordToNote=0, kLineToNote, kParaToNote, kStoryToNote};


/**	Can add a Note
	@param view The active context control view
	@return bool16 kTrue means can add a Note 
 */
	virtual bool16 CanAddNote(IControlView* view) const = 0;

/**	Process Add a Note
	@param view The active context control view

 */
	virtual void DoAddNote(IControlView* view) = 0;

/**	Can convert the selected text into a Note
	@param view The active context control view
	@return bool16 
 */
	virtual bool16 CanConvertToNote(IControlView* view) const = 0;

/**	Process the convertion of the selected text into a Note
	@param view The active context control view
	@param commandBossID kConvertToNoteCmdBoss means convert the selected text into a Note( selected text was deleted).
						 kCopyToNoteCmdBoss means copy the selected text and make a Note with the selected content (selected text was not deleted)

 */
	virtual void DoConvertToNote(IControlView* view, ClassID commandBossID) = 0;

/**	Can open the Note
	@param view The active context control view
	@param docView The current view in the document
	@param menuString "Open Note" if the active context is layout view,
					  "Collapse Note" or "Expand Note" if the active context is galley/story view or Note palette view
	@return bool16 kTrue means can open the Note in Note palette if active context is in layout view,
				   kTrue means can collapsed/expand the Note if active context is in galley view or in Note Palette
 */
	virtual bool16 CanOpenNote(IControlView* view, IControlView* docView, PMString &menuString) const = 0;

/**	Process display the selected Note to Note Palette if active context is layout view
    Process collapsed/expanded the Note if active context is galley/story view or Note Palette view
	@param view The active context control view
	@param docView The current view in the document
*/
	virtual void DoOpenNote(IControlView* view, IControlView* docView) = 0;

	/**	Can delete the selected Note
		@param view The active context control view
		@param docView The current view in the document
		@return bool16 kTrue means can deleted the Note
	 */
	virtual bool16 CanDeleteNote(IControlView* view, IControlView *docView) const = 0;

/**	Process the deletion of Note
		@param view The active context control view
		@param docView The current view in the document
 */
	virtual void DoDeleteNote(IControlView* view, IControlView* docView) = 0;


/**	Can convert the selected text to a Note
		@param view The active context control view
		@param docView The current view in the document
	@return bool16 
 */
	virtual bool16 CanConvertToText(IControlView* view, IControlView *docView) const = 0;

/**	Convert the selected text to a Note
		@param view The active context control view
		@param docView The current view in the document
 */
	virtual void DoConvertToText(IControlView* view, IControlView* docView) = 0;

/**	Can scroll to Note anchor
		@param view The active context control view
		@param docView The current view in the document
	@return bool16 
 */
	virtual bool16 CanScrollToNote(IControlView* view, IControlView *docView) const = 0;

/**	Scroll to Note anchor
		@param view The active context control view
		@param docView The current view in the document
 */
	virtual void DoScrollToNote(IControlView* view, IControlView* docView) = 0;


/**	Can navigate to previous/next Note
	@param view The active context control view
	@param docView The current view in the document
	@param inPalette kTrue means the active context is in Note Palette
	@return bool16 
 */
	virtual bool16 CanNavigateNote(IControlView* view, IControlView *docView, bool16 *inPalette=nil) const = 0;

/**	Navigate the Note forward (kNextNote) or backward (kPreviousNote) from current insertion point
	@param view The active context control view
	@param docView The current view in the document
	@param selMgr The selection manager for the view
	@param type kNextNote, kPreviousNote
 */
	virtual void DoNavigateNote(IControlView* view, IControlView* docView, ISelectionManager* selMgr, NavigateType type) = 0;

/**	Can remove all Notes in the document
		@param view The active context control view
		@param docView The current view in the document
		@param doc The document
		@return bool16 kTrue means there is at least a Note in any editable story excepted the current story
 */
	virtual bool16 CanRemoveAllNotes(IControlView* view, IControlView* docView, IDocument *doc) const = 0;

	/**	Remove the Notes in all unlocked stories in the document
		@param view The active context control view
		@param docView The current view in the document
		@param doc The document
	 */
	virtual void DoRemoveAllNotes(IControlView* view, IControlView* docView, IDocument *doc) = 0;

	/**	Can remove Notes from the story has insertion point
		@param view The active context control view
		@param docView The current view in the document
		@return bool16 kTrue means there is at least one Note in the current story and story is editable
	 */
	virtual bool16 CanRemoveStoryNotes(IControlView* view, IControlView *docView) const = 0;

	/**	Remove all Notes from the unlocked story which has insertion point
		@param view The active context control view
		@param docView The current view in the document
	 */
	virtual void DoRemoveStoryNotes(IControlView* view, IControlView* docView) = 0;

	/**	Can split a Note
		@param view The active context control view
		@param docView The current view in the document
		@param bNotesMode kTrue means to check if can split a Note from NotesMode action
		@return bool16 if bNotesMode is kTrue, return kTrue when insertion point is inside a Note and not in the begin nor end of the Note content
					   if bNotesMode is kFalse, return kTrue when insertion point is inside a Note
	 */
	virtual bool16 CanSplitNote(IControlView* view, IControlView *docView, bool16 bNotesMode = kFalse) const = 0;

	/**	Split a Note into two Notes, place insertion point between two Notes in story
		@param view The active context control view
		@param docView The current view in the document
	 */
	virtual void DoSplitNote(IControlView* view, IControlView* docView) = 0;

	/**	Can show or hide Notes
		@param view The active context control view
		@param docView The current view in the document
		@return bool16 kTrue means there is at least one Note in the document
	 */
	virtual bool16 CanShowHideNote(IControlView* view, IControlView *docView) const = 0;

	/** Toggle displaying Notes
		@param view The active context control view
		@param docView The current view in the document
	 */
	virtual void DoShowHideNote(IControlView* view, IControlView* docView) = 0;


	/**	Can expand all Notes in the document
		@param view The active context control view
		@param docView The current view in the document
		@return bool16 kTrue means there is at least one collapsed Note displaying in the document
	 */
	virtual bool16 CanExpandAllNotes(IControlView* view, IControlView* docView) const = 0;

	/**	Process expand all Notes in the document
		@param view The active context control view
		@param docView The current view in the document
	 */
	virtual void DoExpandAllNotes(IControlView* view, IControlView* docView) = 0;


	/**	Can collapse all Notes in the document
		@param view The active context control view
		@param docView The current view in the document
		@return bool16 kTrue means there is at least one expanded Note displaying in the document
	 */
	virtual bool16 CanCollapseAllNotes(IControlView* view, IControlView* docView) const =0;

	/**	Collapse all Notes in the document
		@param view The active context control view
		@param docView The current view in the document
	 */
	virtual void DoCollapseAllNotes(IControlView* view, IControlView* docView) =0;


	/**	Process set selection
		@param view The active context control view
		@param selectType The selection type
	 */
	virtual void SetSelection(IControlView* view, ITextSelectionSuite::Units selectType)=0;

	/**	Display the Note content to palette if clicks inside the inline Note, or selects the Note 
		void action when the text focus is in Note palette
		@param view The active context control view
		@param docView The current view in the document
	 */
	virtual void DoSetNoteToPalette(IControlView* view, IControlView* docView) = 0;

	/**	Check if the insertion point is in a Note.
		@param none
		@return bool16 kTrue if the selection is in a Note.
	 */
	virtual bool16 IsInNote() const = 0; 

};

#endif // _INoteSuite_
