//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/CButtonDragDropTarget.h $
//  
//  Owner: Tom Taylor
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
//  Implementation of Drag and Drop targets for palette buttons
//  
//========================================================================================

#pragma once
#ifndef __CButtonDragDropTarget__
#define __CButtonDragDropTarget__

#include "ShuksanID.h"
#include "DragDropID.h"

#include "IEvent.h"
#include "CDragDropTarget_Extensible.h"
#include "IDragDropController.h"
#include "PMFlavorTypes.h"
#include "DataObjectIterator.h"
#include "CmdUtils.h"

#pragma export on

class WIDGET_DECL CButtonDragDropTarget : public CDragDropTarget
{
	public:
									CButtonDragDropTarget(IPMUnknown *boss);
		virtual						~CButtonDragDropTarget();
		
		virtual void				DoDragEnter();
		virtual void				DoDragWithin(const PMPoint& localPt);
		virtual void				DoDragLeave();
			// Tracking the drag as it enters, drags, and leaves this target
		
		virtual ErrorCode		ProcessDragDropCommand(IDragDropController*, DragDrop::eCommandType);
			// Create the commands needed to complete a drop 
			// 	(targets will only receive kDragMove or kDrop)
		
	private:
		bool16						fFirstTime;
};


class WIDGET_DECL CButtonDragDropTarget_Extensible : public CDragDropTarget_Extensible
{
	public:
									CButtonDragDropTarget_Extensible(IPMUnknown *boss);
		virtual						~CButtonDragDropTarget_Extensible();
		
		virtual void				DoDragEnter();
		virtual void				DoDragWithin(const PMPoint& localPt);
		virtual void				DoDragLeave();
			// Tracking the drag as it enters, drags, and leaves this target
		
		// Extensibility
		virtual ServiceID GetFlavorHelperServiceID() const = 0;
		
	private:
		bool16						fFirstTime;
};

#pragma export off

#endif