//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/CListBoxDragDropTarget.h $
//  
//  Owner: Dave Burnard
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
//  Implementation of a ListBox Drag and Drop target
//  
//========================================================================================

#ifdef ID_DEPRECATED  // listboxes will disappear from a future version of InDesign. Please use TreeViews instead.

#include "ShuksanID.h"
#include "DragDropID.h"

#include "IEvent.h"
#include "CDragDropTarget.h"
#include "IDragDropController.h"
#include "PMFlavorTypes.h"
#include "DataObjectIterator.h"
#include "CmdUtils.h"
#include "PMRect.h"

#include "DVAForwardDeclarations.h"

#pragma once
#ifdef WIDGET_BUILD
#pragma export on
#endif

class WIDGET_DECL CListBoxDragDropTarget : public CDragDropTarget
{
	public:
								CListBoxDragDropTarget(IPMUnknown *boss);
		virtual					~CListBoxDragDropTarget();

		virtual void			DoDragEnter();
		virtual void			DoDragWithin(const PMPoint& localPt);
		virtual void			DoDragLeave();
			// Tracking the drag as it enters, drags, and leaves this target
	
		virtual DragDrop::TargetResponse		
									CouldAcceptTypes(DataObjectIterator*, const IDragDropSource*, const IDragDropController*) const;
			// Can the target accept the data being dragged?
			//	(Drag source is provided to determine if data should be moved, copied or linked.)

		virtual bool16		HitTest_OutsideBounds(const SysPoint&) const;
			// Override to allow drop targets to respond outside their actual bounds. 
			// 	(usually used for autoscrolling a target when over its scroll bars)
			//	default implementation returns kFalse

	protected:
		virtual void			CalculateCanInsertRange(int32 item);
		virtual bool16			CanInsertBefore(int32 item) const;
		virtual bool16			ShouldDrawInsertionGraphic() const;
		virtual int32			GetDropBeforeItemNumber() const;
		
		virtual void			DrawInsertionGraphic(const PMRect& itemBounds);
		virtual void			RemoveInsertionGraphic(const PMRect& itemBounds);
				bool			DoDirectDrawingForTargetHilite(const dvaui::ui::UI_Node* nodeP, dvaui::drawbot::Drawbot* drawbotP);
				bool			DirectDrawHilite(const dvaui::ui::UI_Node* nodeP, dvaui::drawbot::Drawbot* drawbotP);

		bool16					fLocalDrop;		// true if target == source
	
		
	private:
		int32					fStartCanInsertItem;
		int32					fEndCanInsertItem;
		bool16					fInsertDrawn;	// true if insert graphic is currently visible
		int32					fItemLocation;	// 0 - item in middle; 1 - first item in view; 2 - last item in view
		int32					fInsertBeforeItem;
		PMRect					fInsertionBounds;
		SysRect					fPreviousHilite;
		int32					fInsertionPointIndex;
};

#pragma export off

#endif
