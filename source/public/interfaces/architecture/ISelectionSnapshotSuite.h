//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ISelectionSnapshotSuite.h $
//  
//  Owner: Rich Gartland
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
#ifndef __ISELECTIONSNAPSHOTSUITE__
#define __ISELECTIONSNAPSHOTSUITE__

// Interface Includes:
#include "IPMUnknown.h"

// Implementation includes:

// Forward declarations
class SelectionSnapshotData;
class IControlView;

/** Defines the interface for a selection snapshot to be used for restoring the selection, typically after Undo.
	@see SelectionSnapshotData
*/
class ISelectionSnapshotSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISELECTIONSNAPSHOTSUITE };
	
	/** Create the appropriate snapshot and return a pointer to it.
		@return pointer to the SelectionSnapshotData item created.
	*/
	virtual SelectionSnapshotData* CreateSnapshot() = 0;

	/** Copy selection data from this to another selection target boss.
		@param targetingBoss IN an interface pointer on the boss to receive this target's selection data.
	*/
	virtual void CreateSnapshot(IPMUnknown* targetingBoss) = 0;
	
	/**	Reset the selection to what it was when this snapshot was created.
		@param theSS IN pointer to selection snapshot to use (created in CreateSnapshot)
		@param pView IN pointer to the view where the selection is to be displayed
		@param bDrawSel IN whether to draw the selection
		@param autoScroll IN whether to scroll the view to make the selection visible
	*/
	virtual void RestoreSelection(SelectionSnapshotData *theSS, IControlView* ,bool16 bDrawSel, bool16 autoScroll = kTrue) = 0;

	/** Tell whether the selection is empty.
		@param theSS IN pointer to the selection snapshot data
		@return kTrue if the selection is empty, kFalse otherwise
	*/
	virtual bool16 SelectionIsEmpty(SelectionSnapshotData *theSS) = 0;
		
	/** Tell whether the selection can be restored.
		@param theSS IN pointer to the selection snapshot data
		@param activeSpreadRef IN reference to the active spread
		@return kTrue if the items to be selected still exist; kFalse otherwise
	*/
	virtual bool16 SelectionIsValid(SelectionSnapshotData *theSS, UIDRef activeSpreadRef) = 0;
};


#endif		// __ISELECTIONSNAPSHOTSUITE__
