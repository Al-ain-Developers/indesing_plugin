//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IEventHandler.h $
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
#ifndef __IEVENTHANDLER__
#define __IEVENTHANDLER__

#include "IPMUnknown.h"
#include "ShuksanID.h"		// for IID_IEVENTHANDLER


class IEvent;
class IEventHandler;
class IControlView;

/** Event handler interface.
 
	Defines an interface for handling events. Events themselves are untyped,
	but are always handled to a specific event-typed handler. The event handling
	method returns True if the event has been handled and should not be 
	further dispatched. False means that the event will be passed to the next
	event handler.

*/
class INTERFACE_DECL IEventHandler : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IEVENTHANDLER };  // for UseDefaultIID()
		
		/**  Window has been activated. Traditional response is to
			activate the controls in the window.
			@param e event of interest
			@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
		*/
		virtual bool16 Activate(IEvent* e) = 0; 
			
		/** Window has been deactivated. Traditional response is to
			deactivate the controls in the window.
			@param e event of interest
			@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
		*/
		virtual bool16 Deactivate(IEvent* e) = 0;
		
		/** Application has been suspended. Control is passed to
			another application. 
			@param e event of interest
			@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
		*/
		virtual bool16 Suspend(IEvent* e) = 0;
		
		/** Application has been resumed. Control is passed back to the
			application from another application.
			@param e event of interest
			@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
		*/
		virtual bool16 Resume(IEvent* e) = 0;
			
		/** Mouse has moved outside the sensitive region.
			@param e event of interest
			@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
		*/
		virtual bool16 MouseMove(IEvent* e) = 0; 

		/** Mouse has exited  the current control's bounds.
			@param e event of interest
			@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
		*/
		virtual bool16 MouseExit(IEvent* e) = 0;

		/** User is holding down the mouse button and dragging the mouse.
			@param e event of interest
			@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
		*/
		virtual bool16 MouseDrag(IEvent* e) = 0;
			 
		/** Left mouse button (or only mouse button) has been pressed.
			@param e event of interest
			@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
		*/ 
		virtual bool16 LButtonDn(IEvent* e) = 0;
			 
		/** Right mouse button (or second button) has been pressed.
			@param e event of interest
			@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
		*/
		virtual bool16 RButtonDn(IEvent* e) = 0;
			 
		/** Middle mouse button of a 3 button mouse has been pressed.
			@param e event of interest
			@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
		*/
		virtual bool16 MButtonDn(IEvent* e) = 0;
			
		/** Left mouse button released.
			@param e event of interest
			@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
		*/
		virtual bool16 LButtonUp(IEvent* e) = 0; 
			 
		/** Right mouse button released.
			@param e event of interest
			@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
		*/
		virtual bool16 RButtonUp(IEvent* e) = 0; 
			 
		/** Middle mouse button released.
			@param e event of interest
			@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
		*/
		virtual bool16 MButtonUp(IEvent* e) = 0; 
			 
		/** Double click with any button.
			@param e event of interest
			@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
		*/
		virtual bool16 ButtonDblClk(IEvent* e) = 0; 
			 
		/** Triple click with any button.
			@param e event of interest
			@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
		*/
		virtual bool16 ButtonTrplClk(IEvent* e) = 0;
			 
		/** Quadruple click with any button.
			@param e event of interest
			@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
		*/
		virtual bool16 ButtonQuadClk(IEvent* e) = 0;
			 
		/** Quintuple click with any button.
			@param e event of interest
			@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
		*/
		virtual bool16 ButtonQuintClk(IEvent* e) = 0;
			 
		/** Mouse wheel moved
			@param e event of interest
			@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
		*/
		virtual bool16 MouseWheel(IEvent* e) = 0;
	
		/** Tablet and Gesture events
		 New for CC, previously these would come through PlatformEvent
		 @param e event of interest
		 @return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
		 */
		virtual bool16 TabletEvent(IEvent* e) = 0;
		virtual bool16 GestureEvent(IEvent* e) = 0;

		/** MultiTouchEvents events
		 New for CC
		 @param e event of interest
		 @return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
		 */
		virtual bool16 MultiTouchEvent(IEvent* e) = 0;
			 
		/** Event for a particular control. Used only on Windows.
			@param e event of interest
			@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
		*/
		virtual bool16 ControlCmd(IEvent* e) = 0; 
			
			
		// Keyboard Related Events
		
		/** Keyboard key down for every key.  Normally you want to override KeyCmd, rather than KeyDown.
			@param e event of interest
			@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
		*/
		virtual bool16 KeyDown(IEvent* e) = 0;
			 
		/** Keyboard key down that generates a character.
			@param e event of interest
			@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
		*/
		virtual bool16 KeyCmd(IEvent* e) = 0;
			
		/** Keyboard key released.
			@param e event of interest
			@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
		*/
		virtual bool16 KeyUp(IEvent* e) = 0;
			 
		
		// Keyboard Focus Related Functions
		
		/** Called before getting focus onto the associated widget/window
			@param none
			@return none
		*/
		virtual void PreGetKeyFocus() = 0;

		/** Called after getting focus onto the associated widget/window
			@param none
			@return none
		*/
		virtual void PostGetKeyFocus() = 0;

		/** Called before giving up focus onto the associated widget/window
			@param none
			@return none
		*/
		virtual void PreGiveUpKeyFocus() = 0;

		/** Called after giving up focus onto the associated widget/window
			@param none
			@return none
		*/
		virtual void PostGiveUpKeyFocus() = 0;
			
		/** Typically called before the keyfocus is taken from the widget/window is called. Return kFalse
			to hold onto the keyboard focus.
			@return kFalse to hold onto the keyboard focus
		*/
		virtual bool16 WillingToGiveUpKeyFocus() = 0;
			 
		/** The keyboard focus if going to be taken offis temporarily being taken away. Remember enough state
			to resume where you left off. 
			@return kTrue if you really suspended
			yourself. If you simply gave up the keyboard, return kFalse.
		*/
		virtual bool16 SuspendKeyFocus() = 0;
			 
		/** The keyboard has been handed back. 
			@return kTrue if you really resumed
			yourself. Otherwise, return kFalse.
		*/
		virtual bool16 ResumeKeyFocus() = 0;
			 
		/** Determine if this eventhandler can be focus of keyboard event 
			@return kTrue if this eventhandler supports being the focus
			of keyboard event
		*/
		virtual bool16 CanHaveKeyFocus() const = 0;
			 
		/** Return kTrue if this event handler wants to get keyboard focus
			while tabbing through widgets. Note: For almost all event handlers
			CanHaveKeyFocus and WantsTabKeyFocus will return the same value.
			If WantsTabKeyFocus returns kTrue then CanHaveKeyFocus should also return kTrue
			for the event handler to actually get keyboard focus. If WantsTabKeyFocus returns
			kFalse then the event handler is skipped.
			@return kTrue if event handler wants to get focus during tabbing, kFalse otherwise
		*/
		virtual bool16 WantsTabKeyFocus() const = 0;

#if 0 // OBSOLETE AS OF CC
		/** Window needs to repaint.
			@param e event of interest
			@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
		*/
		virtual bool16 Update(IEvent* e) = 0;
			
		/** Method to handle platform specific events
			@param e event of interest
			@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
		*/
		virtual bool16 PlatformEvent(IEvent* e) = 0;
			 
		/** Call the base system event handler.
			@param e event of interest
			@return kTrue if event has been handled and should not be further dispatched, kFalse otherwise (pass event to next handler)
		*/
		virtual bool16 CallSysEventHandler(IEvent* e) = 0;
#endif // OBSOLETE AS OF CC
			
			
		/** Temporary.
		*/
		virtual void SetView(IControlView* view) = 0;
			 
};

// All the event handler's methods for handling specific event types
// share the EHandlerMethod prototype.
//
typedef bool16 (IEventHandler::*EHandlerMethod)(IEvent* e);



#endif // __IEVENTHANDLER__
