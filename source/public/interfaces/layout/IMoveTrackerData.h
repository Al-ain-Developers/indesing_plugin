//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IMoveTrackerData.h $
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
//========================================================================================

#pragma once
#ifndef __IMOVETRACKERDATA__
#define __IMOVETRACKERDATA__

#include "LayoutUIID.h"
#include "PMTypes.h"
#include "PMPoint.h"

//----------------------------------------------------------------------------------------
// Forward Declarations
//----------------------------------------------------------------------------------------

class UIDList;

//----------------------------------------------------------------------------------------
// ITracker: Abstract interface for trackers
//----------------------------------------------------------------------------------------

class IMoveTrackerData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IMOVETRACKERDATA };

	public:
		/**
		   Set method to control how a tracker moves page items.
		   @param itemList A pointer to the item list of page items for tracker to move.
		   @param startPt A PMPoint in pasteboard coordinate space. Represents the users mouse down location.
		   @param selectionMode how to select the item(s). Either  Selection::kAddTo or  Selection::kReplace
		   @param isVisible The setting for the new layer's visibility. Default is kTrue for visible, kFalse for hidden.
		   @param deselect Should the tracker deselect the items in item list. Typically set when user Shift clicks on an item. Typically set to kFalse and by default tracker selects the items in the item list.
		   @param reselectItemList A pointer to the "reselect" item list of page items for tracker to select after move has completed. Used for moving content of an image frame with rollover effect when we don't want to select the content.
		   If nil, after move is completed, selection won't be altered. If empty list, selection will be set to this list (i.e. no selection), otherwise items in list will be selected.				
		 */
		virtual void Set(UIDList *itemList, const PBPMPoint& startPt, int32 selectionMode, bool16 deselect, UIDList *reselectItemList = nil) = 0;

		/**
		   Gets the data value for the tracker's item list.
		   @return a pointer to the item list for the tracker to operate on.
		 */
		virtual UIDList* GetItemList() const = 0;

		/**
		   Gets the data value for the tracker's "reselect" item list. May be nil, and defaults to nil if not set.
		   @return a pointer to the "reselect" item list for the tracker to select after tracking has completed.
		 */
		virtual UIDList* GetReselectItemList() const = 0;

		/**
		   Gets the data value for the initial mouse down location for the tracker.
		   @return a PMPoint in pasteboard coordinate space.
		 */
		virtual const PBPMPoint GetStartPoint() const = 0;

		/**
		   Gets the data value for the Selection enum type.
		   @return the selectionMode for how the tracker should select the item(s). Either  Selection::kAddTo or  Selection::kReplace
		 */
		virtual int32 GetSelectionMode() const = 0;

		/**
		   Gets the data value for whether to deselect page items.
		   @return the deselect value. kFalse means tracker will select page items in item list, kTrue means then will be deselected.
		 */
		virtual bool16 GetDeselect() const = 0;
		
		/**
		   Gets the data value for if drawing should the Selection enum type. Calling this method toggles the value to
		   kFalse. Use for drag and drop between targets to know if drag is local or not.
		   @return the value
		 */
		virtual bool16 ShouldDrawFirst() = 0;
	};

#endif
