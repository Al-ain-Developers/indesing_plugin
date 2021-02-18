//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IAssignmentUIUtils.h $
//  
//  Owner: Michele Goodwin
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
#ifndef __IASSIGNMENTUIUTILS__
#define __IASSIGNMENTUIUTILS__

#include "AssignmentUIID.h"
#include "ITreeViewMgr.h"
#include "Utils.h"

class IAssignedDocument;

/**
	IAssignmentUIUtils is an utility functions to help ICBridge to enable and process the menu items on assignment panel
*/

class IAssignmentUIUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IASSIGNMENTUIUTILS };

/**	Can show the object in the document based on the selected item in assignment panel
	@param none
	@return bool16 kTrue if one InCopy Content node is selected
 */
	virtual bool16  CanGoTo() = 0;

/**	If text story is selected in the panel, go to the text story in the document
	If gaphic story is selected in the panel, bring the graphic story in center view of the document
	@param none
 */
	virtual void GoTo() = 0;

	/** Can new an Assignment in the active document
		@param ac The active context
		@return kTrue if document is saved
	*/
	virtual bool16 CanNewAssignment(IActiveContext* ac) = 0;

	/**	Choose the location for the Assignment, display New Assignment dialog, and new a assignment
		@param ac The active context
		@param uiFlag kFullUI means to display the Assignment options dialog, otherwise the new Assignment will have the default options
		@param saveAssignment kTrue means to save the physical Assignment file 
		@return UIDRef The UIDRef of the new Assignment
	*/
	virtual UIDRef NewAssignment(IActiveContext* ac, UIFlags uiFlag, bool16 saveAssignment = kTrue) = 0;

	/** Can add the selection on the panel to Assignment
		@param ac The active context
		@return kTrue if unassigned exported/unexported objects are selected on the panel or on active doc window
	*/
	virtual bool16 CanPanelAddSelToAssignment(IActiveContext* ac) = 0;

	/**
		Add the objects selected in panel or active window to the assignment
		@param ac The active context
		@param assignRef The Assignment that the selected stories are added to. If a null UIDRef passed in, then a new Assignment will be created first.
	*/
	virtual void PanelAddSelToAssignment(IActiveContext* ac, UIDRef &assignRef) = 0;

	/**
		@param ac The active context
		@return kTrue if unassigned exported/unexported objects are selected on active doc window
	*/
	virtual bool16 CanAddSelToAssignment(IActiveContext* ac) = 0;
	
	/**
		Add the objects selected in window to the assignment
		@param ac The active context
		@param assignRef The UIDRef of the assignment the objects added to
		@return An error code indicating whether the add to assignment succeeded or not.
	*/
	virtual ErrorCode AddSelToAssignment(IActiveContext* ac, UIDRef assignRef) = 0;
	
	/**
		Add the objects to assignment
		@param assignRef assignment UIDRef
		@param itemList UIDList of objects to be added to assignment
		@return An error code indicating whether the add to assignment succeeded or not.
	*/
	virtual ErrorCode AddListToAssignment(UIDRef assignRef, UIDList itemList) = 0;
	
	/**	Can invoke Assignment options		
		@param ac The active context
		@return kTrue if one assignment is selected on the story list panel
	*/
	virtual bool16 CanInvokeAssignmentOptions(IActiveContext* ac) = 0;
	
	/**	Display the Assignment Options dialog, widgets are read-only in InCopy.
		@param none
	*/
	virtual void InvokeAssignmentOptions() = 0;

	/** Can change the Assignment location
		@return kTrue if one orphaned assignment is selected on the story list panel
	*/
	virtual bool16 CanRelinkAssignment() = 0;
	
	/** Choose the new location for Assignment, and change it
		@param none
	*/
	virtual void RelinkAssignment() = 0;

	/** Can remove the selected items on the panel
		@return kTrue if assigned InCopy content or assignments are selected on Assignment Panel
		@param removeStory return kTrue if assign InCopy content selected
	*/
	virtual bool16 CanRemove(bool16 &removeStory) = 0;

	/**	When stories are selected, remove the the selected assigned story from the Assignment and move them to unassigned, 
		when Assignments are selected, remove all story belong to this Assignment and move them into unassigned, 
			then remove this Assignment from document, display message to ask if it is ok the delete the physical Assignment file, then delete it
		@param byPassDialog kTrue means don't display the message about deleting the physical Assignment file
	*/
	virtual void Remove(bool16 byPassDialog = kFalse) = 0;

	/** Check the selected Assignments need to be saved
		@return kTrue if assignments selected in panel are dirty
	*/
	virtual bool16 CanUpdateSelectedAssignments()= 0;

	/** Check if there is any Assignment in the active document
		@param ac The active context
		@return kTrue if the active document has any assignment
	*/
	virtual bool16 CanUpdateAllAssignments(IActiveContext* ac) =0;

	/** Check if there is any Assignment in the active document that is out of date (or missing).
		@param ac The active context
		@return kTrue if the active document has any assignment that is out of date.
	*/
	virtual bool16 CanUpdateOutOfDateAssignments(IActiveContext* ac) =0;

	/**
		Save the current asssignment selected in the panel
		@param none
	*/
	virtual void UpdateSelectedAssignments() =0;

	/**	Save all asssignments in the active doc
		@param ac The active context
	*/
	virtual void UpdateAllAssignments(IActiveContext* ac) =0;

	/**	Save all out of date (or missing) asssignments in the active doc
		@param ac The active context
	*/
	virtual void UpdateOutOfDateAssignments(IActiveContext* ac) =0;

	/** Can check out the selection on the panel
		@param ac The active context
		@return kTrue if the panel has same type selection and can be check out		
	*/
	virtual bool16 CanEditOnSelection(IActiveContext* ac) = 0;

	/**	Checkout the selection items on Assignment Panel
		@return the success of checkout
	*/
	virtual bool16 EditInPlace( void ) = 0;

	/** Can check in selection on Assignment panel
		@param ac The active context
		@return kTrue if the panel has same type selection and can be check in		
	*/
	virtual bool16 CanSubmitOnSelection(IActiveContext* ac) = 0;

	/**	Check in the selection items on Assignment Panel
		@return the success of the submit(checkin)
	*/
	virtual bool16 Submit( void ) = 0;

	/** Can cancel checkout the selection on Assignment panel
		@param ac The active context
		@return kTrue if the panel has same type selection and can be reverted	
	*/
	virtual bool16 CanRevertOnSelection(IActiveContext* ac) = 0;

	/**
		Cancel Checkedout items selected on Assignment Panel
		@return the success of the Cancel Checkedout
	*/
	virtual bool16 RevertChanges( void ) = 0;

	/** Can check in all stories on the active document
		@param ac The active context
		@return kTrue if the panel items can be check in
	*/
	virtual bool16 CanSubmitAll(IActiveContext* ac) = 0;

	/**	Checkin All items on active document
		@return the success of check in all
	*/
	virtual bool16 SubmitAll( void ) = 0;

	/** Can update story selected on Assignment panel
		@param ac The active context
		@return kTrue if the panel has same type selection and can be relinked
	*/
	virtual bool16 CanUpdateContentOnSelection(IActiveContext* ac) = 0;

	/**	Relink (update story) on selection on Assignment panel
		@return the success of update story
	*/
	virtual bool16 UpdateContent( void ) = 0;

	/**	Can show/hide the objects assigned color
		@return kTrue if can toggle to show/hide the assigned frame color
	*/
	virtual bool16 CanToggleAssignmentColor() = 0;

	/**	Can reveal the selected item in the finder/explorer.
		@param none
		@return kTrue if one node is selected.
	*/
	virtual bool16  CanRevealInFinderExplorer() = 0;

	/**	Reveals the selected item (document, assignment, story) in the finder/explorer.
		@param none
	*/
	virtual void RevealInFinderExplorer() = 0;

	/**	Can reveal the selected item in the Adobe Bridge.
		@param none
		@return kTrue if one node is selected.
	*/
	virtual bool16  CanRevealInBridge() = 0;

	/**	Reveals the selected item (document, assignment, story) in the Adobe Bridge.
		@param none
	*/
	virtual void RevealInBridge() = 0;

	/**	To toggle show/hide the assigned frame color
		@param none
	*/
	virtual void ToggleAssignmentColor() = 0;

	/**	Double click on Document node will bring the document forward
		Double click on Assignment node will open Assignment Options dialog
		Double click on InCopy content node will select the item on document view, or set the text insertion point on the document.
		@param none
	*/
	virtual void DoubleClickNode() = 0;
	
	/**
		Ask the user if they want to save all modified assignments.
		@param doc The assignment document to examine for assignments.
		@param allowCancel Flag indicating whether or not there should be a cancel button, true by default.
		@return 0 = doc == nil, 1 = to save, 2 = not save, and 3 = cancel
	*/
	virtual int32 ShouldSaveAssignments(IAssignedDocument* doc, bool8 allowCancel = kTrue) = 0;

	/**
		Display warning message if any assignment file is missing. 
		@param doc The document to be checked for missing assignments
	*/
	virtual void CheckForMissingAssignments(UIDRef doc) = 0;
};

#endif // __IASSIGNMENTUIUTILS__