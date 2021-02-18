//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/events/CEventHandler.cpp $
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
//  Do-nothing event handler
//  
//  Defines an event handler that returns "not handled" for all 
//  event handling methods. Intended for use as a base handler
//  class: derived classes should override the event handler 
//  methods that they need to handle, and return true for the 
//  overridden methods.
//  
//========================================================================================

#include "VCWidgetHeaders.h"

#include "CEventHandler.h"

// ----- Interface Includes -----
#include "IControlView.h"

// ----- Implementation Includes -----

DEFINE_HELPER_METHODS(CEventHandler)

CEventHandler::CEventHandler(IPMUnknown *boss) :
	HELPER_METHODS_INIT(boss),
	fView(nil)
{
}

CEventHandler::~CEventHandler()
{
	if (fView)
		fView->Release();
}
	

bool16 CEventHandler::Activate(IEvent* e)
{ 
	return kFalse;
}


bool16 CEventHandler::Deactivate(IEvent* e)
{  
	return kFalse;
 }


bool16 CEventHandler::Suspend(IEvent* e)
{ 
	return kFalse;
}


bool16 CEventHandler::Resume(IEvent* e)
{ 
	return kFalse;
}

bool16 CEventHandler::MouseMove(IEvent* e)
{ 
	return kFalse;
}

bool16 CEventHandler::MouseExit(IEvent* e)
{ 
	return kFalse;
}

bool16 CEventHandler::MouseDrag(IEvent* e)
{ 
	return kFalse;
}


bool16 CEventHandler::LButtonDn(IEvent* e)
{ 
	return kFalse;
}


bool16 CEventHandler::RButtonDn(IEvent* e)
{ 
	return kFalse;
}


bool16 CEventHandler::MButtonDn(IEvent* e)
{ 
	return kFalse;
}


bool16 CEventHandler::LButtonUp(IEvent* e)
{ 
	return kFalse;
}


bool16 CEventHandler::RButtonUp(IEvent* e)
{ 
	return kFalse;
}


bool16 CEventHandler::MButtonUp(IEvent* e)
{ 
	return kFalse;
}


bool16 CEventHandler::ButtonDblClk(IEvent* e)
{ 
	return LButtonDn(e);
}


bool16 CEventHandler::ButtonTrplClk(IEvent* e)
{ 
	return LButtonDn(e);
}


bool16 CEventHandler::ButtonQuadClk(IEvent* e)
{ 
	return LButtonDn(e);
}


bool16 CEventHandler::ButtonQuintClk(IEvent* e)
{ 
	return LButtonDn(e);
}


bool16 CEventHandler::MouseWheel(IEvent* e)
{
	return kFalse;
}

bool16 CEventHandler::TabletEvent(IEvent* e)
{
	return kFalse;
}

bool16 CEventHandler::GestureEvent(IEvent* e)
{
	return kFalse;
}

bool16 CEventHandler::MultiTouchEvent(IEvent* e)
{
	return kFalse;
}


bool16 CEventHandler::ControlCmd(IEvent* e)
{ 
	return kFalse;
}


bool16 CEventHandler::KeyDown(IEvent* e)
{ 
	return kFalse;
}

bool16 CEventHandler::KeyCmd(IEvent* e)
{ 
	return kFalse;
}


bool16 CEventHandler::KeyUp(IEvent* e)
{ 
	return kFalse;
}


bool16 CEventHandler::Update(IEvent* e)
{ 
	return kFalse;
}

bool16 CEventHandler::WillingToGiveUpKeyFocus()
{ 
	return kTrue;	// by default, we're always willing to give up the keyboard
}

bool16 CEventHandler::SuspendKeyFocus()
{
	return kFalse;
}

bool16 CEventHandler::ResumeKeyFocus()
{ 
	return kFalse;
}

bool16 CEventHandler::PlatformEvent(IEvent* e)
{ 
	return kFalse;
}

bool16 CEventHandler::CanHaveKeyFocus() const
{ 
	return kFalse;	// by default, we don't accept keyboard events
}


bool16 CEventHandler::WantsTabKeyFocus() const
{
	return CanHaveKeyFocus();
}


void CEventHandler::SetView(IControlView* view)
{
	// In case a mouse down event got dropped (it can happen) call this to
	// release memory before reassigning the pointers. This should get fixed!
	if (fView)
		fView->Release();
	
	fView = view;
	
	if( fView )	
		fView->AddRef();
}

bool16 CEventHandler::CallSysEventHandler(IEvent* e)
{
	return kFalse;
}


