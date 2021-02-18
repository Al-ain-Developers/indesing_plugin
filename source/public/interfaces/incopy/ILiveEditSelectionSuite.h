//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/ILiveEditSelectionSuite.h $
//  
//  Owner:
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
#ifndef __ILiveEditSelectionSuite__
#define __ILiveEditSelectionSuite__

#include "InCopyBridgeID.h"
#include "IPMUnknown.h"
#include "IControlView.h"
#include "IAssignment.h"

class IAssignment;

class ILiveEditSelectionSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILIVEEDITSELECTIONSUITE };

   /**
		Tests whether or not we can save edits to the current selection.
		@return kTrue if can save.
    */
   virtual bool16 CanSaveEdits() const = 0;
  
   /**
		Tests whether or not a we can export the current selection.
		@return kTrue if checked out.
    */
   virtual bool16 CanExport() const = 0;
   
   /**
		Tests whether or not a we can check in the current selection.
		@return kTrue if we can export
    */
   virtual bool16 CanCheckIn() const = 0;

   /**
		Tests whether or not can cancel check out (revert edits).
		@return kTrue if can cancel check out.
    */
   virtual bool16 CanCancelCheckOut() const = 0;

   /**
		Tests whether or not can check out for editing.
		@return kTrue if can lock.
    */
   virtual bool16 CanCheckOut() const = 0;

   /**
		Exports selected stories as InCopy stories.
		@param destinationDir - A pointer to a directory path to be used in place of prompting the user, or nil to prompt.
		@param exportCompatibility - The export formats to allow.
		@return kTrue if operation succeeded.
		@see IAssignment::AssignmentCompatibility
    */
   virtual bool16 Export(const IDFile* destinationDir = nil, IAssignment::AssignmentCompatibility exportCompatibility = IAssignment::kUnassignedCompatibility) const = 0;

   /**
		Check out selected InCopy stories. 
		Collects stories from selection and processes ICBridgeEditInPlaceCmd, which calls ILiveEditSelectionSuite::EditInPlace().
		@return kTrue if story is editable.
    */
   virtual bool16 CheckOut() const = 0;

   /**
		Release the lock on a previously checked out selected story. This operation reverts local copy to match the project version.
		Collects stories from selection and processes ICBridgeRevertChangesCmd, which calls ILiveEditSelectionSuite::RevertChanges().
		@return kTrue if operation succeeded.
   */
   virtual bool16 CancelCheckOut() const = 0;

   /**
		Save any local changes to a project and release the project lock
		@return kTrue if operation succeeded.
    */
   virtual bool16 CheckIn() const = 0;

   /**
		Save any local changes to a project and release the project lock
		@return kTrue if operation succeeded for all the lewt.
    */
   virtual bool16 CheckInAll() const = 0;

   /**
		Reimport the selected story if changes have been made to it outside of the application
		@return kTrue if operation succeeded.
    */
   virtual bool16 Relink() const = 0;

   /**
		Saves edits to selected stories to their respective story files. Stories remain checked out.
		@return kTrue if operation succeeded.
    */
   virtual bool16 SaveEdits() const = 0;

 	/**
		Determine if a story is out of date.
		Collects stories from selection checks the datalink.
		@return kTrue if the selected story is out of date.
	*/
   virtual bool16 IsOutOfDate() const = 0;


   virtual bool16 IsInCopyStorySelected () const = 0;

   /**
		Set the panel rsrc id, so the suite knows how to get selected items
		Two panels are using this suite, kLinksUIPanelWidgetID and kStoryListPanelWidgetID
		@param widgetID the panel widget id that the suite should get the selection items from
	*/
   virtual void SetPanel(WidgetID panelID) = 0;

   /**
		Set the view and mouse point, so the default context suite knows how to get selected
		items from under the mouse point when there is no document selection (currently used
		by InCopy only).
		@param view the relevant control view
		@param point the relevant mouse point
	*/
   virtual void SetViewPoint(IControlView *view, const PMPoint& point) = 0;

};


#endif	// __ILiveEditSelectionSuite__
