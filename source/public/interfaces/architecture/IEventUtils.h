//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IEventUtils.h $
//  
//  Owner: Lonnie Millett
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
#ifndef __IEventUtils__
#define __IEventUtils__

// ----- Interfaces -----

#include "IPMUnknown.h"

#include "VirtualKey.h"
#include "KeyStates.h"
#include "PMTypes.h"

// ----- ID.h files -----

#include "AppUIID.h"

// ----- Forward declarations -----

class IEvent;
class IControlView;
class CursorSpec;

/**	Utils interface which provides methods for working with events.
	Use like so:
	<pre>
		Utils<IEventUtils>()->BuildAndDispatchUpdateOrActivateEvent(*theEvent);
	</pre>
*/
class IEventUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IEVENTUTILS };

	/** Get the current mouse location. It's much better if you can get this information from an IEvent
		@return	the current position of the mouse.
	*/
	virtual GSysPoint GetGlobalMouseLocation() = 0;

	/** Get the current mouse button state. It's much better if you can get this information from an IEvent
		@return	the current state of the left mouse button.
	*/
	virtual bool16 IsMouseButtonDown() = 0;

	/** Get the current mouse button state. It's much better if you can get this information from an IEvent.
		Roughly equivilent to calling StillDown() on the mac.
		@return	the current state of the left mouse button.
	*/
	virtual bool16 IsMouseButtonReleased() = 0;

	/** Check if this event indicates a drag is starting
		@param e the OS event
		@param isPatientUser OUT indicates if this is a patient user drag
		@param patientCursor cursor to use if this is a patient user drag
		@return kTrue if the user is starting a drag
	*/
	virtual bool16 IsUserStartingDrag(IEvent *e, bool16 &isPatientUser, const CursorSpec* patientCursor = nil) = 0;

	/** Check if this event indicates a drag is starting
		@param e the OS event
		@param isPatientUser OUT indicates if this is a patient user drag
		@param startOnExitGRect a rectangle indicating an area which is not considered to be starting a drag, i.e. the user has to move outside this rect before a drag is started.
		@param patientCursor cursor to use if this is a patient user drag
		@return kTrue if the user is starting a drag
	*/
	virtual bool16 IsUserStartingDrag(IEvent *e, bool16 &isPatientUser, const SysRect& startOnExitGRect, const CursorSpec* patientCursor = nil) = 0;

	/** Captures the mouse events for this window. Before capturing the mouse, it will release any other captures also attached to this window. 
		If this method is called without pushing an event handler to the dispatcher, it will have no effect as the captured mouse events
	    will not be properly dispatched. This method is functional for Windows platform only and results in a no-op on the Macintosh platform.
		@param theView  pointer to the control view to use, capture will actually occur on theView's top level parent
	*/
	virtual void PMCaptureMouse(IControlView* theView) = 0;
	
	/** Releases the previous captured mouse. This method is functional for Windows platform only and results in a no-op on the Macintosh platform.
	*/
	virtual void PMReleaseMouse(void) = 0;

	/** 	Called in some circumstances when we handle the KeyDown and want to remove the following KeyCmd event. No op on Macintosh.
		@param e the keydown event
	*/
	virtual void RemoveNextKeyCmd(IEvent* e) = 0;

	/** Check to see if we're currently dragging or tracking the mouse
		@return kTrue if we're either doing a drag or tracking.
	*/
	virtual bool16 IsDragOrTrackInProgress() = 0;

#ifdef MACINTOSH
	/**	This method is called when switching out of InDesign, or back in. It doesn't actually do anything with palettes now, just suspends/resumes key focus.
	 @param off kTrue to move the palettes offscreen, kFalse to bring them back.
	 */
	virtual void MovePaletteWindowsOffScreen(bool16 off) = 0;
#endif
	
	/**	Get the modifiers from an event as bits or'd together.
		@param e event to get the modifiers from
		@return modifier bits. @see KBSCModifierDefs.h
	*/
	virtual int16 GetModifiersFromEvent(const IEvent* e) = 0;

#ifdef WINDOWS
	/** INTERNAL USE ONLY:
		Consolidation function used to handle the WM_SYSCOMMAND message. This is a windows-message sent when user
		tries to use "Alt+letter" keyboard shortcut to access to the main menu bar.
		This method can be used in a Windows-specific event handler's PlatformEvent method. The parameters
		may be extracted via a SysEvent
		@param hWnd the HWND as extracted from the SysEvent, msg = e->GetSysEvent(), then msg->hwnd, msg->message, msg->wParam, msg->lParam.
		@param sysMsg the UINT as extracted from the SysEvent, msg = e->GetSysEvent(), msg->message. In this case must be WM_SYSCOMMAND.
		@param wParam the WPARAM as extracted from the SysEvent, msg = e->GetSysEvent(), then msg->wParam.
		@param lParam the LPARAM as extracted from the SysEvent, msg = e->GetSysEvent(), then msg->lParam.
		Return value is kTrue if the message was handled, caller should then return MAKELRESULT(0, 0). 
		If kFalse, event wasn't handled and that handlers normal PlatformEvent handling should take place.
	*/

	virtual bool16 HandleSysCommandMessage(HWND hWnd, UINT sysMsg, WPARAM wParam, LPARAM lParam) = 0;
#endif
	/** Check to see if we're tracking the mouse
        @return kTrue if we're tracking.
     */
	virtual bool16 IsTrackInProgress() = 0;
	
	/** Check to see if any user event is pending
		@param needPendingKeyEventOnly In case there is a need to check only pending key events. Default value for this param is false.
        @return kTrue if true.
     */
	virtual bool16 IsUserEventPending(bool16 needPendingKeyEventOnly = kFalse) = 0;
};

#endif
