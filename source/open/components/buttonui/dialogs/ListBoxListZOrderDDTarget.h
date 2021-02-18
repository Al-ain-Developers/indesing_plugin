//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/dialogs/ListBoxListZOrderDDTarget.h $
//  
//  Owner: Mark VerMurlen
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
//  Drop target for z-order reordering of the list box in the list box field options panel
//  
//========================================================================================

#pragma once
#ifndef __ListBoxListZOrderDDTarget_h__
#define __ListBoxListZOrderDDTarget_h__

#include "CTreeViewDragDropTarget.h"

//========================================================================================

class ListBoxListZOrderDDTarget : public CTreeViewDragDropTarget
{
	public:
								ListBoxListZOrderDDTarget(IPMUnknown *boss);
		virtual					~ListBoxListZOrderDDTarget();
		
		virtual DragDrop::TargetResponse		CouldAcceptTypes(DataObjectIterator*, const IDragDropSource*, const IDragDropController*) const;
			// Can the target accept the data being dragged?
			//	(Drag source is provided to determine if data should be moved, copied or linked.)

		virtual ErrorCode		ProcessDragDropCommand(IDragDropController*, DragDrop::eCommandType);
			// Create the commands needed to complete a drop 
			// 	(targets will only receive kDragMove or kDrop)

	protected:
	
		virtual void	MoveItems( int32 inMoveToIndex );
		
	private:
	
		DECLARE_HELPER_METHODS()
};

#endif	

