//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/InLineEditEventMonitorEH.h $
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
//========================================================================================

#pragma once
#ifndef __INLINEEDITEVENTMONITOREH__
#define __INLINEEDITEVENTMONITOREH__

#include "CEventHandler.h"
#include "VirtualKey.h"

class IEvent;

#ifdef WIDGET_BUILD
#pragma export on
#endif

class WIDGET_DECL  InLineEditEventMonitorEH : public CEventHandler
{
public:
	InLineEditEventMonitorEH(IPMUnknown *boss);
	virtual ~InLineEditEventMonitorEH();

	virtual bool16 Suspend(IEvent* e);
		// Application has been suspended. Control is passed to another application. 
	virtual bool16 LButtonDn(IEvent* e); 
		// Left mouse button (or only mouse button) has been pressed.
	virtual bool16 RButtonDn(IEvent* e);
		// Right mouse button (or second button) has been pressed.
	virtual bool16 MButtonDn(IEvent* e);
		// Middle mouse button of a 3 button mouse has been pressed.		
	virtual bool16 KeyDown(IEvent* e);
		// Key has been pressed.
	
	virtual bool16 KeyCmd(IEvent* e);

	virtual bool16 MouseWheel(IEvent* e);

protected:
	virtual bool16	IsInsideEditingWidget(IEvent* e , bool16& inOSControl );
	virtual bool16	StopEditing(bool16 syncData);
private:
	bool16 IsInsideOSControl(IEvent* e);
	void   HandleOwnerDrawnPopup(VirtualKey theKey);
	
};


#pragma export off

#endif