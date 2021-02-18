//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/CTreeViewDragDropTarget.h $
//  
//  Owner: Matt Joss
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
//  Implementation of a TreeView Drag and Drop target
//  
//========================================================================================

#include "ShuksanID.h"
#include "DragDropID.h"

#include "IEvent.h"
#include "CDragDropTarget.h"
#include "IDragDropController.h"
#include "PMFlavorTypes.h"
#include "DataObjectIterator.h"
#include "CmdUtils.h"
#include "PMRect.h"
#include "IControlView.h"

#include "DVAForwardDeclarations.h"

#pragma once
#ifdef WIDGET_BUILD
#pragma export on
#endif

class WIDGET_DECL CTreeViewDragDropTarget : public CDragDropTarget
{
	public:
								CTreeViewDragDropTarget(IPMUnknown *boss);
		virtual					~CTreeViewDragDropTarget();

		virtual void			DoDragEnter();
		virtual void			DoDragWithin(const PMPoint& localPt);
		virtual void			DoDragLeave();
			// Tracking the drag as it enters, drags, and leaves this target
	
//		virtual DragDrop::TargetResponse		
//									CouldAcceptTypes(DataObjectIterator*, const IDragDropSource*, const IDragDropController*) const;
			// Can the target accept the data being dragged?
			//	(Drag source is provided to determine if data should be moved, copied or linked.)

		virtual bool16		HitTest_OutsideBounds(const SysPoint&) const;
			// Override to allow drop targets to respond outside their actual bounds. 
			// 	(usually used for autoscrolling a target when over its scroll bars)
			//	default implementation returns kFalse

	protected:
		enum { kNotHit = 0, kAbove = 1, kBelow = -1, kInsideNode = 2};
		virtual int32			HitTest( IControlView*	widget, const PMPoint& localPoint );
		virtual	IControlView* 	GetTarget( IControlView*	widget, int32* hitWhere, const PMPoint& localPt );
		virtual void			DrawHilite(IControlView*	targetWidget, int32 hitWhere);
		
			// The default hilite will be the width of the widget, but if you have an expander icon or something, this
			// may not be what you want.   Override this method to change the width
		virtual void			AdjustHiliteLine( IControlView* widget, PMReal& left, PMReal& right );
		
		
		virtual void			RemoveOldHilite();
		virtual	bool16 			CheckScroll(const PMPoint& localPt);
		virtual	bool16 			LastSeenOverScrollArea();
		// This is the callback we attach to drover and it forwards the call to DirectDrawHilite which derived classes can override
		bool					DoDirectDrawing(const dvaui::ui::UI_Node*, dvaui::drawbot::Drawbot* drawbotP);
		virtual bool			DirectDrawHilite(const dvaui::ui::UI_Node* nodeP, dvaui::drawbot::Drawbot* drawbotP);
			// Is the cursor over the scroll region?
	
	protected:
		IControlView*			fTreeScrollerView;
		SysRect 				fPreviousHilite;
		IControlView*			fOldTarget;
		int32					fHitLocation;
		bool16					fOverScrollArea;
		bool16					fAutoScrollVertical;
		bool16					fAutoScrollHorizontal;
};

#pragma export off
