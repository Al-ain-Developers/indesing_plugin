//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/INoteSuiteUtils.h $
//  
//  Owner: Cindy Chen
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
#ifndef __INoteSuiteUtils__
#define __INoteSuiteUtils__

#include "InCopySharedID.h"

//-----------------------------------
//	Forward References
//

#include "IPMUnknown.h"
#include "UIDRef.h"
#include "INoteSuite.h"

class ISelectionManager;
class IControlView;

/** This utility interface for INoteSuit
*/
class INoteSuiteUtils : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_INOTESUITEUTILS };


/**	Navigate to next Note (when type = kNextNote) or previous Note (when type = kPreviousNote)
    from fromThisTextIndex, display Note content into Note palette
	@param selMgr Currect active selection manager
	@param docView Current document view
	@param fromThisTextIndex Current text index
	@param storyRef Current story ref
	@param type INoteSuite::kNextNote or INoteSuite::kPreviousNote
 */
		virtual void NavigateNote(ISelectionManager* selMgr, IControlView *docView, TextIndex fromThisTextIndex, UIDRef storyRef, INoteSuite::NavigateType type)=0;	


/**	Check if layer is editable
	@param layoutView The layout control view
	@return bool16 kTrue means layer is editable
 */
		virtual bool16 IsLayerEditable(IControlView* layoutView)=0;


/**	Check if Notes are hidden
	@param none
	@return bool16 kTrue means the Notes are in hidden state
 */
		virtual bool16 IsNoteHidden() =0;
		

/**	Check if there is at least one Note with the desired state
	@param storyRef The story
	@param collapsed kTrue means to check the collapsed state
					 kFalse means to check the expanded state
	@return bool16 kTrue if at least one note is collapsed when param collapsed is kTrue,
					kTrue if at least one note is expand when param collapsed is kFalse
 */
		virtual bool16 CheckNotesState(UIDRef storyRef, bool16 collapsed)=0;
	


/**	Check if there are other Notes in any editable story excepted param storyRef
	@param document The document
	@param storyRef The story
	@param galleyView The galley control view, default to nil,(this param was not used, can always be nil)
	@return bool16 kTrue means there are other Notes in other editable story can be removed
 */
		virtual bool16 CanRemoveAllNotes(IDocument* document, UIDRef &storyRef, IControlView *galleyView = nil) =0;
		

/**	Process UnlockLayerCmd and ShowLayerCmd based on layerList
	@param layerList The layer list
	@return bool16 kTrue means the action is successed
 */
		virtual bool16 UnlockLayers(UIDList &layerList) = 0;


/**	Check if story(param textModel) is collapsed
	@param view Galley control view
	@param textModel The story's ITextModel interface pointer
	@return bool16 kTrue means the story (textModel is valid) is collapsed in galley view;
				   kTrue means all stories (textModel = nil) are collapsed in galley view;
 */
		virtual bool16 CheckStoryCollapsed(IControlView *view, ITextModel *textModel = nil) = 0;
	

/**	Check if at least one story has notes and is expanded
	@param view The galley control view
	@param doc The document
	@return bool16 kTrue at least one story has notes and is expanded
 */
		virtual bool16 CheckExpandedNoteAnchor(IControlView *view, IDocument *doc) = 0;


/**	Get the active document's current control view (galley control view or layout control view)
	@param none
	@return IControlView The current control view of the active document
 */
		virtual IControlView * GetDocControlView() = 0;
		
/**	Utility used for "Convert To Note" action, check if there is XML structure in the range(start,end), then
    display message to ask if it is ok to remove the XML
	@param storyRef The current story
	@param start The start text index
	@param end The end text idnex
	@return bool16 kTrue means there is no xml tag within the start and end,
				   kTrue means there is xml tag, and user click yes to remove the xml tag
				   kFalse means there is xml tag, and user click cancel to remove xml tag
 */
		virtual bool16 CheckRemoveXML(UIDRef &storyRef, TextIndex start, TextIndex end) = 0;

/**	Warming message when remove all Notes and there is Note in collapsed story (in galley view)
	@param galleyView Galley control view
	@param doc The document
	@return bool16	kTrue user click "YES" or no notes in collapsed story, 
					kFalse user click "No"
 */
		virtual bool16 RemoveAllNotesOnCollapsedStory(IControlView *galleyView, IDocument *doc) = 0;

/**	Utility used for "Convert To Note" and "Create Note" action, check if there is Ruby in the range (start, end), then
    display message to ask if it is ok to remove the Ruby
	@param storyRef The story
	@param start The start text index
	@param end The end text idnex
	@return bool16 	
		return kTrue if there is no Ruby Attributes within the start and end,
		return kTrue if there is Ruby Attributes, and user click yes to remove the Ruby Attributes
		return kFalse if there is Ruby Attributes, and user click cancel to remove Ruby Attributes
 */
		virtual bool16 CheckRemoveRuby(UIDRef &storyRef, TextIndex start, TextIndex end=kInvalidTextIndex) = 0;

};

#endif // __INoteSuiteUtils__