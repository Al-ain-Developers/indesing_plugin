//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CEventHandler.h $
//  
//  Owner: ?
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
#ifndef __CEVENTHANDLER__
#define __CEVENTHANDLER__

#include "IEventHandler.h"
#include "HelperInterface.h"


class IControlView;

#pragma export on

/** Entry-level implementation of IEventHandler, should be used for EventFilters or non-widget event handlers.
	use or derive from DVControlEventHandler or widget event handlers
*/
class WIDGET_DECL CEventHandler : public IEventHandler
{			
	public:
	
		/** Constructor 
			@param boss object on which this interface is aggregated
		*/
		CEventHandler(IPMUnknown *boss);
										
		/** Destructor */
		virtual ~CEventHandler();
			
		// --- IEventHandler Methods --
		
		/** Window has been activated. Traditional response is to
			activate the controls in the window.
			@param e event of interest
			@return kTrue if event was handled, kFalse to propagate event, i.e. pass to next handler
		*/
		virtual bool16 Activate(IEvent* e);
			
		/** Window has been deactivated. Traditional response is to
			deactivate the controls in the window.
			@param e event of interest
			@return kTrue if event was handled, kFalse to propagate event, i.e. pass to next handler
		*/
		virtual bool16 Deactivate(IEvent* e);
			 
		/** Application has been suspended. Control is passed to
			another application. 
			@param e event of interest
			@return kTrue if event was handled, kFalse to propagate event, i.e. pass to next handler
		*/
		virtual bool16 Suspend(IEvent* e);
			
		/** Application has been resumed. Control is passed back to the
			application from another application.
			@param e event of interest
			@return kTrue if event was handled, kFalse to propagate event, i.e. pass to next handler
		*/
		virtual bool16 Resume(IEvent* e);
			 
		/** Mouse has moved outside the sensitive region.
			@param e event of interest
			@return kTrue if event was handled, kFalse to propagate event, i.e. pass to next handler
		*/
		virtual bool16 MouseMove(IEvent* e); 

		/** Mouse has exited  the current control's bounds.
			@param e event of interest
			@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
		*/
		virtual bool16 MouseExit(IEvent* e);
		/** User is holding down the mouse button and dragging the mouse.
			@param e event of interest
			@return kTrue if event was handled, kFalse to propagate event, i.e. pass to next handler
		*/
		virtual bool16 MouseDrag(IEvent* e);
			
		/** Left mouse button (or only mouse button) has been pressed.
			@param e event of interest
			@return kTrue if event was handled, kFalse to propagate event, i.e. pass to next handler
		*/
		virtual bool16 LButtonDn(IEvent* e); 
			
		/** Right mouse button (or second button) has been pressed.
			@param e event of interest
			@return kTrue if event was handled, kFalse to propagate event, i.e. pass to next handler
		*/
		virtual bool16 RButtonDn(IEvent* e);
			
		/** Middle mouse button of a 3 button mouse has been pressed.
			@param e event of interest
			@return kTrue if event was handled, kFalse to propagate event, i.e. pass to next handler
		*/ 
		virtual bool16 MButtonDn(IEvent* e);
			
		/** Left mouse button released.
			@param e event of interest
			@return kTrue if event was handled, kFalse to propagate event, i.e. pass to next handler
		*/
		virtual bool16 LButtonUp(IEvent* e); 
			 
		/** Right mouse button released.
			@param e event of interest
			@return kTrue if event was handled, kFalse to propagate event, i.e. pass to next handler
		*/
		virtual bool16 RButtonUp(IEvent* e); 
			
		/** Middle mouse button released.
			@param e event of interest
			@return kTrue if event was handled, kFalse to propagate event, i.e. pass to next handler
		*/
		virtual bool16 MButtonUp(IEvent* e); 
			
		/** Double click with any button.
			@param e event of interest
			@return kTrue if event was handled, kFalse to propagate event, i.e. pass to next handler
		*/
		virtual bool16 ButtonDblClk(IEvent* e); 
			 
		/** Triple click with any button.
			@param e event of interest
			@return kTrue if event was handled, kFalse to propagate event, i.e. pass to next handler
		*/
		virtual bool16 ButtonTrplClk(IEvent* e); 
			
		/** Quadruple click with any button.
			@param e event of interest
			@return kTrue if event was handled, kFalse to propagate event, i.e. pass to next handler
		*/
		virtual bool16 ButtonQuadClk(IEvent* e);
			 
		/** Quintuple click with any button.
			@param e event of interest
			@return kTrue if event was handled, kFalse to propagate event, i.e. pass to next handler
		*/
		virtual bool16 ButtonQuintClk(IEvent* e);
			 
		/** Mouse wheel moved
			@param e event of interest
			@return kTrue if event was handled, kFalse to propagate event, i.e. pass to next handler
		*/
		virtual bool16 MouseWheel(IEvent* e);
			 
		/** Tablet and Gesture events
		 New for CC, previously these would come through PlatformEvent
		 @param e event of interest
		 @return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
		 */
		virtual bool16 TabletEvent(IEvent* e);
		virtual bool16 GestureEvent(IEvent* e);

		virtual bool16 MultiTouchEvent(IEvent* e);
	
		/** Event for a particular control. Used only on Windows.
			@param e event of interest
			@return kTrue if event was handled, kFalse to propagate event, i.e. pass to next handler
		*/
		virtual bool16 ControlCmd(IEvent* e); 
			
			
		// Keyboard Related Events
		
		/** Keyboard key down for every key.  Normally, override KeyCmd, not KeyDown.
			@param e event of interest
			@return kTrue if event was handled, kFalse to propagate event, i.e. pass to next handler
		*/
		virtual bool16 KeyDown(IEvent* e);
			 
		/** Keyboard key down that generates a character.
			@param e event of interest
			@return kTrue if event was handled, kFalse to propagate event, i.e. pass to next handler
		*/
		virtual bool16 KeyCmd(IEvent* e);
			 
		/** Keyboard key released.
			@param e event of interest
			@return kTrue if event was handled, kFalse to propagate event, i.e. pass to next handler
		*/ 
		virtual bool16 KeyUp(IEvent* e);
			
		
		// Keyboard Focus Related Functions
		
		/** Called before getting focus onto the associated widget/window
			@param none
			@return none
		*/
		virtual void PreGetKeyFocus() { }

		/** Called after getting focus onto the associated widget/window
			@param none
			@return none
		*/
		virtual void PostGetKeyFocus() { }

		/** Called before giving up focus onto the associated widget/window
			@param none
			@return none
		*/
		virtual void PreGiveUpKeyFocus() { }

		/** Called after giving up focus onto the associated widget/window
			@param none
			@return none
		*/
		virtual void PostGiveUpKeyFocus() { }

		/** Typically called before focus is given up. 
			@return kFalse to hold onto the keyboard focus, kTrue otherwise
		*/
		virtual bool16 WillingToGiveUpKeyFocus();
			
		/** The keyboard is temporarily being taken away. Remember enough state
			to resume where you left off. 

			@return kTrue if you really suspended
			yourself. If you simply gave up the keyboard, return kFalse.
		*/
		virtual bool16 SuspendKeyFocus();
			
		/** The keyboard has been handed back. 

			@return kTrue if you really resumed
			yourself. Otherwise, return kFalse.
		*/
		virtual bool16 ResumeKeyFocus();
			 
		/** Determine if this event handler wants to be focus.
			@return kTrue if this eventhandler supports being the focus
			of keyboard events, kFalse otherwise	
		*/
		virtual bool16 CanHaveKeyFocus() const;
			
		/** Determine if this event handler wants to get focus from tabbing through controls.
			@return kTrue if this event handler wants to get keyboard focus
			while tabbing through widgets, kFalse otherwise
		*/
		virtual bool16 WantsTabKeyFocus() const;
		 		
		/** Window needs to repaint.
			@param e event of interest
			@return kTrue if event was handled, kFalse to propagate event, i.e. pass to next handler
		*/
		virtual bool16 Update(IEvent* e);
			
		/** Method to handle platform specific events	
			@param e event of interest
			@return kTrue if event was handled, kFalse to propagate event, i.e. pass to next handler
		*/
		virtual bool16 PlatformEvent(IEvent* e);
			 		
		/** Call the base system event handler.
			@param e event of interest
			@return kTrue if event was handled, kFalse to propagate event, i.e. pass to next handler
		*/
		virtual bool16 CallSysEventHandler(IEvent* e);
			
		/** Temporary.
		*/
		virtual void SetView(IControlView* view);

		
protected:
	IControlView*	fView;
	
DECLARE_HELPER_METHODS()
};

#pragma export off

#endif // __CEVENTHANDLER__
