//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/DVHostedWidgetEH.h $
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
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2008 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once
#ifndef __DVHostedWidgetEH__
#define __DVHostedWidgetEH__
	
#include "IEventHandler.h"

#include "DVAForwardDeclarations.h"

#ifdef WIDGET_BUILD
#pragma export on
#endif

/**	IEventHandler baseclass used for widgets in the Drover world.

	The theory going forward is that most of what our existing IEventHandlers do will be replaced 
	by the default behavior of the drover widgets themselves. Thus an IEventHandler will typically not
	be necessary, unless our version of the widget expects to do something unusual, and even then that
	code may not reside in an IEventHandler interface.
*/

class DV_WIDGET_DECL DVHostedWidgetEH : public IEventHandler
{
public:
	// ----- Initialization -----

	DVHostedWidgetEH(IPMUnknown *boss);
	virtual ~DVHostedWidgetEH();
	
		// App Related Events
		virtual bool16 Activate(IEvent* )			{TRACEFLOW("Drover:Windows", "%s::Activate\n", class_name()); return kFalse;} 
		virtual bool16 Deactivate(IEvent* )		{TRACEFLOW("Drover:Windows", "%s::Deactivate\n", class_name()); return kFalse;}
		virtual bool16 Suspend(IEvent* )			{TRACEFLOW("Drover:Windows", "%s::Suspend\n", class_name()); return kFalse;}
		virtual bool16 Resume(IEvent* )			{TRACEFLOW("Drover:Windows", "%s::Resume\n", class_name()); return kFalse;}
			
		// Mouse Related Events
		virtual bool16 MouseMove(IEvent* );
		virtual bool16 MouseExit(IEvent* );
		virtual bool16 MouseDrag(IEvent* );
		virtual bool16 LButtonDn(IEvent* );
		virtual bool16 RButtonDn(IEvent* );
		virtual bool16 MButtonDn(IEvent* );
		virtual bool16 LButtonUp(IEvent* ); 
		virtual bool16 RButtonUp(IEvent* );
		virtual bool16 MButtonUp(IEvent* );
		virtual bool16 ButtonDblClk(IEvent* ); 
		virtual bool16 ButtonTrplClk(IEvent* );
		virtual bool16 ButtonQuadClk(IEvent* );
		virtual bool16 ButtonQuintClk(IEvent* );
		virtual bool16 MouseWheel(IEvent* );
		virtual bool16 TabletEvent(IEvent* );
		virtual bool16 GestureEvent(IEvent* );
		virtual bool16 MultiTouchEvent(IEvent* );
						
		virtual bool16 BaseHandlePointerEvent(IEvent* );

		// Keyboard Related Events
		virtual bool16 KeyDown(IEvent* );
		virtual bool16 KeyCmd(IEvent* );
		virtual bool16 KeyUp(IEvent* );
			 		
		virtual bool16 BaseHandleKeyboardEvent(IEvent* );

		// Keyboard Focus Related Functions
		// Keyboard Focus Related Functions
		virtual void PreGetKeyFocus() { }
		virtual void PostGetKeyFocus() { }
		virtual void PreGiveUpKeyFocus() { }
		virtual void PostGiveUpKeyFocus() { }
		virtual bool16 WillingToGiveUpKeyFocus();
		virtual bool16 SuspendKeyFocus();
		virtual bool16 ResumeKeyFocus();
		virtual bool16 CanHaveKeyFocus() const;
		virtual bool16 WantsTabKeyFocus() const;
			 			 
		virtual bool16 ControlCmd(IEvent* )		{TRACEFLOW("Drover:Windows", "%s::ControlCmd\n", class_name()); return kFalse;}
		virtual bool16 Update(IEvent* )			{TRACEFLOW("Drover:Windows", "%s::Update\n", class_name()); return kFalse;}
		virtual bool16 PlatformEvent(IEvent* )		{TRACEFLOW("Drover:Windows", "%s::PlatformEvent\n", class_name()); return kFalse;}
		virtual bool16 CallSysEventHandler(IEvent* ) {TRACEFLOW("Drover:Windows", "%s::CallSysEventHandler\n", class_name()); return kFalse;}
			
			
		virtual void SetView(IControlView* )	{TRACEFLOW("Drover:Windows", "%s::SetView\n", class_name()); return;}
			 
		virtual const char* class_name()		{static const char* name = "DVHostedWidgetEH"; return name;}
protected:
		dvaui::ui::UI_Node*		Get_UI_Node() const;

private:

	DECLARE_HELPER_METHODS()
};

#pragma export off

#endif

