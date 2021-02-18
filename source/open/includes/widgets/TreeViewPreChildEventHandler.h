//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/TreeViewPreChildEventHandler.h $
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
//========================================================================================

#pragma once
#ifndef __TreeViewPreChildEventHandler__
#define __TreeViewPreChildEventHandler__



#include "NodeID.h"
#include "IEvent.h"
#include "IEventHandler.h"
//----------------------------------------------------------------------------------------
// Forward Declarations
//----------------------------------------------------------------------------------------
class IEvent;

//----------------------------------------------------------------------------------------
// Class Info
//----------------------------------------------------------------------------------------
#pragma export on 

#include "DVHostedWidgetEH.h"

//========================================================================================
// CLASS TreeViewPreChildEventHandler
//========================================================================================
class WIDGET_DECL TreeViewPreChildEventHandler : public DVHostedWidgetEH
{
	typedef DVHostedWidgetEH inherited;

public:
	TreeViewPreChildEventHandler(IPMUnknown *boss);
	virtual ~TreeViewPreChildEventHandler();
				
	// Mouse Related Events
	virtual bool16 MouseMove(IEvent* e );
	virtual bool16 MouseExit(IEvent* e);
	virtual bool16 MouseDrag(IEvent* e);
	virtual bool16 LButtonDn(IEvent* e);
	virtual bool16 RButtonDn(IEvent* e);
	virtual bool16 MButtonDn(IEvent* e);
	virtual bool16 LButtonUp(IEvent* e);
	virtual bool16 RButtonUp(IEvent* e);
	virtual bool16 MButtonUp(IEvent* e);
	virtual bool16 ButtonDblClk(IEvent* e);
	virtual bool16 ButtonTrplClk(IEvent* e);
	virtual bool16 ButtonQuadClk(IEvent* e);
	virtual bool16 ButtonQuintClk(IEvent* e);
	virtual bool16 MouseWheel(IEvent* e);
						
	virtual bool16 BaseHandleMouseEvent(IEvent* e);

	// Keyboard Related Events
	virtual bool16 KeyDown(IEvent* e);
	virtual bool16 KeyCmd(IEvent* e);
	virtual bool16 KeyUp(IEvent* e);
			 		
protected:
	bool16 	ClickWasInScrollBar(IEvent* e);
	bool16 	CheckForKeyFocusGrab(IEvent* e);
	int32 ScrollBarAdjustment( bool16 horizontalScrollBar );

	int32 fHScrollAdjustment;
	int32 fVScrollAdjustment;
};

#pragma export off 

#endif
