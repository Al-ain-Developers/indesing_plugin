//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IEvent.h $
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
#ifndef __IEVENT__
#define __IEVENT__

#include "PMTypes.h"
#include "VirtualKey.h"

class IEventHandler;

/**   Core Event Interface. System for encoding a single event in a core manner. Edge specific access is in MEvent or WEvent.
*/
class INTERFACE_DECL IEvent	INHERITFROM {
public:
	virtual ~IEvent() {}
	
	/** 	Check if left mouse button down
		@return kTrue if left mouse button was pressed when this event was generated.
	*/
	virtual bool16	LButtonDn() const = 0;

	/** 	Check if option key down (Alt on PC)
		@return kTrue if option/alt key was pressed when this event was generated.
	*/
	virtual bool16	OptionAltKeyDown() const = 0;

	/** 	Check if command key down (Ctrl on PC)
		@return kTrue if command/cntrl key was pressed when this event was generated.
	*/
	virtual bool16	CmdKeyDown() const = 0;

	/** 	Check if shift key down
		@return kTrue if shift key was pressed when this event was generated.
	*/
	virtual bool16	ShiftKeyDown() const = 0;

	/** 	Check if shift lock is on
		@return kTrue if shift lock(aka caps lock) was on when this event was generated.
	*/
	virtual bool16	ShiftLockKeyDown() const = 0;

	/** 	Check if the Control key on a Macintosh extended keyboard is down. Will always return false on Windows.
		@return kTrue if mac control key was pressed when this event was generated.
	*/
	virtual bool16	MacCtrlDown() const = 0;

	/** 	Check if the left Alt/Option key on keyboard is down. Works on mac and windows both.
		@return kTrue if the left alt key was pressed when this event was generated.
	*/
	virtual bool16	LeftAltDown() const = 0;

	/** 	Check if the right Alt/Option key on keyboard is down. Works on mac and windows both.
		@return kTrue if the right alt key was pressed when this event was generated.
	*/
	virtual bool16	RightAltDown() const = 0;

	/** 	Check if the left Control key on Windows keyboard is down.
		On Macintosh, returns TRUE if either Command key is down.
		@return kTrue if the left(On windows, either on mac) control key was pressed when this event was generated.
	*/
	virtual bool16	LeftControlDown() const = 0;

	/** 	Check if the right Control key on Windows keyboard is down.
		On Macintosh, returns TRUE if either Command key is down.
		@return kTrue if the left(On windows, either on mac) control key was pressed when this event was generated.
	*/
	virtual bool16	RightControlDown() const = 0;

	/** 	Return the ASCII key associated with the event. Valid only for key-related events.
		@return the character associated with this key event.
	*/
	virtual SysChar GetChar() const = 0;

	/** 	Sets the ASCII key associated with the event. Valid only for key-related events.
		Usually only done to indicate the event has been handled as a shortcut. Changing the char of a KeyDown cmd to 0
		Prevents redispatching the event as a KeyCmd
		@param theChar the new ascii character for this event.
	*/
	virtual void  SetChar( SysChar theChar ) = 0;

	/** 	Return the virtual key associated with a kKeyDown event. @see KeyboardDefs.h for the various defines for virtual keys.
		@return the virtual key for this event.
	*/
	virtual VirtualKey GetVirtualKey() const = 0;

	/** Returns kTrue if the event generates a valid unicode character or kFalse if the keystroke doesn't map
		to a unicode character. This function is used to figure out if AltGR (right-alt on non-US keyboards) should be
		treated as a shortcut or as a special character. The result of this function is only valid during a KeyDown event.
		On Macintosh, this function always returns false.
		@return kTrue if this is an AltGR event.
	*/
	virtual bool16		IsAltGrChar() const = 0;


	/** Returns kTrue if key event is an automatically repeating key (caused by holding a key down).
	*/
	virtual bool16		IsRepeatKey() const = 0;

	/** 	Return the location associated with the event. The validity of the contents depends on the type of event;
		 for events containing a location, we return the location of the mouse, in global coordinates, at the time of the event.
	 
		 Platform details: On Win, only mouse related events contain a location, and this method returns nonsense for non-mouse events. 
		However on OS X any event can have a location, and we will return it, in particular keyboard events contain a location.
		 @return mouse location at the time of this event.
	*/
	virtual GSysPoint GlobalWhere() const = 0;

	enum ScrollUnits { kLines, kPixels };

	/** 	Return the scroll data for the event. Only valid for mouse wheel events.
			Can contain an x and y scroll value on some devices (e.g. Apple's Mighty Mouse or some track pads).
		@return distance user scrolled the wheel (in lines or pixels) with an x and y component. For kLines values,
			typically multiplied by the panorama's delta value to compute how much to scroll. For kPixels values,
			value may be used directly. Note the kPixels values can be 0, 0 for non-track pad/Mighty Mouse-like devices.
			Windows platform will return 0, 0 at this time since no platform pixel wheel return messages yet exist.
			If client code calls GetMouseScrollDelta with kPixels enum, and return value is kZeroPoint, client code should
			call again with kLines to get a true value (i.e. Scrolling device didn't support pixel return values).
	*/
	virtual PMPoint GetMouseScrollDelta(ScrollUnits units = kLines) const = 0;

	/** Returns the time of the event, in SECONDS since startup.  On Win, this
		is a DWORD, so it'll roll over after ~47 days
		@return time of event.
	*/
	virtual PMReal	GetTime() const = 0;


	/** EventHandledState:
		 With the droverized (non-platform) widget set in CS6.5, we have replaced IEvent's SystemHandledState 
		 with the (similar but distinct) notion of whether or not the event has been or should be processed by the underlying drover widget/ui_node.
		
		 While there are similarities between how SystemHandledState was used prior to droverization and how UI_DoEventHandledState is now used,
		 they are different enough that we could not just reuse SystemHandledState. The key difference: UI_DoEventHandledState applies on a per widget basis,
		 while SystemHandledState was applied once per event. We will deprecate/remove SystemHandledState before shipping to force clients to 
		 revisit Set/GetSystemHandledState call-sites to determine the appropriate conversion.
		 
		For pointer (mouse, touch and gesture) and keyboard events delivered to the widget via our widget event hook (DVEventHandler::DVPointerEvent), the process is as follows:
		 0) In DVEventHandler::DVPointerEvent, after the DVEvent is created, it's state is set to kShouldCall prior to sending the event on to the IEventHandler.
		 	
		 1)	If MyWidgetEH::HandlerMethod returns kTrue: HandlerMethod has handled the event, no further processing is performed.
				HandlerMethod may choose to call inherited::HandlerMethod which calls the underlying 
				drover widget/ui_node's UI_DoMouseEvent/UI_DoKeyboardEvent method.
		
		 2) If MyWidgetEH::HandlerMethod returns kFalse: HandlerMethod has declined to handle the event, further processing is performed. 
				By default, we then pass the event to the underlying drover widget/ui_node's UI_DoMouseEvent/UI_DoKeyboardEvent method.
				However, if the HandlerMethod sets the event's BaseWidgetHandledState to kDontCall or kHasCalled, then base widget handling
				is skipped and the event continues on to the widget's parent for processing
				
		For events delivered directly to an IEventHandler (event filters pushed on the dispatcher) or an IEventWatcher, the underlying 
				drover widget/ui_node's UI_DoMouseEvent/UI_DoKeyboardEvent method will not be called.
				
		NOTE: At this time this change has only been implemented for mouse events.
	*/
	enum BaseEventHandledState { kShouldCall, kDontCall, kHasCalled };
	typedef BaseEventHandledState UI_DoEventHandledState;

	/** Set the base (drover) widget handledness for this event. IEvent constructors default to kDontCall.
		@param state new system handled state
	*/
	virtual void SetUI_DoEventHandledState(UI_DoEventHandledState /* state */) {}

	/** Set the base (drover) widget handledness for this event. IEvent constructors default to kDontCall.
		@return the current system handled state of this event.
	*/
	virtual UI_DoEventHandledState GetUI_DoEventHandledState() const {return kDontCall;}

	// Note: These API are needed in CC and beyond - and should be removed. For now they are no-ops.
#ifdef ID_DEPRECATED
	typedef BaseEventHandledState SystemHandledState;

	/** DEPRECATED: Set the system handledness for this event. Events generally start out with kShouldCall. After we dispatch events internally, if the
		SystemHandledState is still kShouldCall, we pass this event back to the system to do whatever the default behavior is. If you don't
		want that to happen, set the state to kDontCall( or kHasCalled if that's more appropriate)
		@param state new system handled state
	*/
	virtual void SetSystemHandledState(SystemHandledState state) = 0;

	/** DEPRECATED: Get the system handledness for this event. Events generally start out with kShouldCall. After we dispatch events internally, if the
		SystemHandledState is still kShouldCall, we pass this event back to the system to do whatever the default behavior is.
		@return the current system handled state of this event.
	*/
	virtual SystemHandledState GetSystemHandledState() const = 0;
#endif // ID_DEPRECATED
	
	/** ID's for the different types of events.
		Note an EventType of 0 is used to mean all EventTypes in the EventWatcher API
		I.e., zero shouldn't be used as a real EventType. I probably should add an enumerator here...<sheridan>
	*/

	typedef enum IEventType {
		/** 0 reserved to mean all event types for event watcher API */
		kFirstEventType = 1,

	// The following event types are available to event watchers and to event handlers pushed on to the event dispatcher, and are also delivered to widget event handlers, 
	
		/** mouse has been moved outside the sensitive area */
		kMouseMove = kFirstEventType,
		/** mouse has exited  the current control's bounds */
		kMouseExit,
		/** mouse has been moved while mouse button is down */
		kMouseDrag,
		/**  user has pressed left mouse button */
		kLButtonDn,
		/** user has pressed right mouse button */
		kRButtonDn,
		/** user has pressed middle mouse button */
		kMButtonDn,
		/** user has released left mouse button */
		kLButtonUp,
		/**  user has released right mouse button */
		kRButtonUp,
		/** user has released middle mouse button */
		kMButtonUp,
		/** double click on any mouse button */
		kDoubleClick,
		/** triple click on any mouse button */
		kTripleClick,
		/** quadruple click on any mouse button */
		kQuadrupleClick,
		/** quintuple click on any mouse button */
		kQuintupleClick,
		/** mouse wheel moved */
		kMouseWheel,
		/** control has been pushed (PC only) */
		kControlCmd,
		/** user pushed a key on the keyboard */
		kKeyDown,
		/** user pushed a key on the keyboard that generates a character. Usually follows kKeyDown */
		kKey,
		/** user released a key on the keyboard */
		kKeyUp,
		/** tablet event. Proximity or Pen */
		kTabletEvent,
		/** tablet event. Begin/End, Rotate, Magnify. Swipe, Pan */
		kGestureEvent,
		/** multi-touch event. lower-level than a gesture. Details under construction */
		kMultiTouchEvent,
		
		
	// The following event types are ONLY available to event watchers and to event handlers pushed on to the event dispatcher
	//	Note: These events may be removed later in the CC dev cycle, so it is preferable to rely on alternative mechanisms
	//	see: IApplicationActiveState, kApplicationSuspend/ResumeMsg notifications, and the WindowActivationChanged method of IControlView
	
		/** application is being suspended (context switch to another application) - simulated as of CC */
		kSuspend,
		/** application resumed (context switch from another application back to Shuksan) - simulated as of CC */
		kResume,
		/** a window is being activated - simulated as of CC (for palettes, documents and dialogs) */
		kActivate,
		/** a window is being deactivated - simulated as of CC (for palettes, documents and dialogs) */
		kDeactivate,
		
		
	// The following event types are ONLY available to event watchers
	//	Note: This events may be removed later in the CC dev cycle, so it is preferable to rely on alternative mechanisms
	//	see: idle tasks or timers.
	
		/** idle event. Periodically sent when there are no events pending in the queue  - simulated */
		kNull,
		
		
	// Unrecognized event
	
		/** empty or unconverted event, should be ignored */
		kInvalid,

#if 0 // OBSOLETE EVENT TYPES, these are not sent in CC and beyond
		kApple,	
		kUpdate,
		kCarbonModifierChangedEvent,
		kCommandProcess,
		kPlatformEvent,
#endif // OBSOLETE

		/**	note if you add EventTypes so that the value of kEndOfEventType is pushed greater than 32, then IEventDispatcher::EventTypeList will have to
			be reimplemented not to mention that all EventHandlers will need additional methods... <sheridan> */

		/** no event type constants can be greater than kEndOfEventTypes */
		kEndOfEventTypes
	} EventType;

	/** 	Get the type of the event.
		@return the type of the event
	*/
	virtual EventType GetType() const = 0;

	/** 	Set the type of the event. Typically this is done by the EventConverter.
		@param the event type
	*/
	virtual void SetType(const EventType theType) = 0;
	
	/** Gesture event subtypes */
	enum GestureType {
		kGestureNone = 0,
		kGestureBegin,
		kGestureEnd,
		kGestureRotation,
		kGestureMagnify,
		kGestureSwipe,
		kGesturePan,
		kEndOfGestureTypes
	};
	
	/** Get the gesture type of the event.
	 @return the gesture type of the event
	 */
	virtual GestureType GetGestureType() const {return IEvent::kGestureNone;}
	
	/** Gesture data accessors */
	virtual float	GetRotationInDegrees() const {return 0.0f;}
	virtual float	GetMagnificationAmount() const {return 0.0f;}

	enum SwipeDirection {
		kSwipeDirectionNone = 0,
		kSwipeDirectionLeft,
		kSwipeDirectionRight,
		kSwipeDirectionUp,
		kSwipeDirectionDown
	};
	virtual SwipeDirection GetSwipeDirection() const {return IEvent::kSwipeDirectionNone;}

	/** Tablet event subtypes - actions for want of a better word */
	enum TabletAction {
		kTabletActionNone = 0,
		kTabletActionProximity,	// pen entered/exited the tablet's sensitivity range
		kTabletActionPen,		// pen param changed: pressure, tilt, tip, etc.  -- not just position
		kEndOfTabletActions
	};
	
	/** Get the gesture type of the event.
	 @return the gesture type of the event
	 */
	virtual TabletAction GetTabletAction() const {return IEvent::kTabletActionNone;}
	
	// Note: no support yet for tablet event details (have to look at underlying platform event) 

};

#endif // __IEVENT__
