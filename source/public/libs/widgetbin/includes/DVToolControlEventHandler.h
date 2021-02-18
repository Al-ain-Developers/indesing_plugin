//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/DVToolControlEventHandler.h $
//  
//  Owner: Frits Habermann
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
//  DVToolControlEventHandler is an event handler for tool items, and is the base class 
//  for ToolEventHandler. DVToolControlEventHandler helps in customizing the event handling
//  specific to tool items, over DVHostedWidgetEH event handler.
//  
//========================================================================================

#pragma once
#ifndef __DVToolControlEventHandler__
#define __DVToolControlEventHandler__

#include "DVHostedWidgetEH.h"

class IControlView;
class IWindow;

#ifdef WIDGET_BUILD
#pragma export on
#endif

class DVToolControlEventHandler : public DVHostedWidgetEH
{
	typedef DVHostedWidgetEH inherited;
public:
	DVToolControlEventHandler(IPMUnknown *boss);
	virtual ~DVToolControlEventHandler();

	virtual bool16 LButtonDn(IEvent* e) ; //Override
	virtual bool16 LButtonUp(IEvent* e) ; //Override

	virtual bool16 KeyDown(IEvent* e) ;
	virtual bool16 KeyCmd(IEvent* e) ;
	virtual bool16 KeyUp(IEvent* e) ;

protected:
	virtual bool16 CleanupMouseUp();
	virtual void   TriggerControlData();

protected:
	IControlView*	fMyView;
	bool16			fMouseOverControl;
	bool16			fLButtonPressed;
	bool16			fIsToolboxSubtoolsPopoutOpen;
};

#pragma export off

#endif
