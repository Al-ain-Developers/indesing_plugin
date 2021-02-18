//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snapshot/ISnapSelectionSuite.h $
//  
//  Owner: Adobe Developer Technologies
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

#ifndef __ISnapSelectionSuite__
#define __ISnapSelectionSuite__

#include "IPMUnknown.h"
#include "SnapID.h"
#include "SnapshotUtilsEx.h"
#include "ISpread.h"

/**	From SDK sample;  abstract interface for a snap shot selection suite to be used in the new selection architecture.
  
	@ingroup snapshot
	
*/
class ISnapSelectionSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISNAPSELECTIONSUITE };

	/**
		Create a snap shot of the selected items.
		If the user chooses to draw area as the preference in the Snapshot dialog,
		then we need to draw everything withing the bounds of the selection.
		Otherwise, we draw the selected items only.
		@param spread The spread which the selected items are on
		@return SnapshotUtilsEx* the new snapshot object
	*/
	virtual SnapshotUtilsEx* CreateSnapshot(ISpread* spread) = 0;

	/**
		Return kTrue if the selection has nothing in it; kFalse otherwise.
	*/
	virtual bool16 SelectionIsEmpty() = 0;

};

#endif // __ISnapSelectionSuite__



