//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ITracker.h $
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
#ifndef __ITRACKER__
#define __ITRACKER__

#include "PMTypes.h"
#include "PMPoint.h"

//----------------------------------------------------------------------------------------
// Forward Declarations
//----------------------------------------------------------------------------------------

class IEvent;
class IControlView;
class ISnapTo;
class IItemContext;

//----------------------------------------------------------------------------------------
// ITracker: Abstract interface for trackers
//----------------------------------------------------------------------------------------

/** Abstract interface for trackers.
	@see CTracker.h
*/
class ITracker : public IPMUnknown
{
	public:
		/** Initialize the state of the tracker with a control-view. Called just prior to BeginTracking.
			This differs from SetupSpecialTracker in that it just requires a control view.
			Trackers for widgets, or trackers that don't require snap to behavior or other layout-special behavior
			would likely use this method before calling BeginTracking.

			@param theControlView [IN] the control view to track in.
			@param theSnapper [IN] the ISnapTo interface if the tracker want snap to behavior. Applies to tracker in the layout widget.
			@param context [IN] the IItemContext for the tracker to use.
			@see SetupSpecialTracker
			@see ISnapTo.h
			@see IItemContext.h
		*/
		inline void SetupTracker( IControlView* theControlView){ SetupTracker(theControlView, (ISnapTo*)0, (IItemContext*)0);}

		/** Initialize the state of the tracker with a control-view and other optional abstractions.
			Typically called just prior to BeginTracking to see the tracker with various information
			needed during tracking. 
			Indicate which control view the tracker is modifying. Used for access to
			graphics context. Snap to interface is optional, but it must be present
			if the tracker needs to do snap to.

			@param theControlView [IN] the control view to track in.
			@param theSnapper [IN] the ISnapTo interface if the tracker want snap to behavior. Applies to tracker in the layout widget.
			@param context [IN] the IItemContext for the tracker to use.
			@see SetupTracker
			@see ISnapTo.h
			@see IItemContext.h
		 */
		inline void SetupSpecialTracker( IControlView* theControlView, ISnapTo* theSnapper, IItemContext* context){ SetupTracker(theControlView, theSnapper, context);}
		
		/**	Return a bumped reference to the trackers IControlView.
			@param none
			@return IControlView* 
		 */
		virtual IControlView* QueryControlView() const = 0;

		/**	The tracker's eventhandler is on the stack ready to accept events.
			@param none
			@return bool16 kTrue if enabled, kFalse otherwise.
		 */
		virtual bool16 IsEnabled() = 0;

		/**	Has BeginTracking been called?
			@param none
			@return bool16 return kTrue if the tracker's BeginTracking method has been called, i.e. the tracker is actually tracking the mouse. Otherwise return kFalse.
		 */
		virtual bool16 IsTracking() = 0;	// BeginTracking has been called

		/**	Push the tracker's eventhandler on the event handling stack. Create the mouse
			tracking thread. Tracking however will not start until a mouse down occurs. Should not
			be necessary for external callers since EnableTracking is called automatically for tracker
			clients in CTracker::BeginTracking.
			@param none
		 */
		virtual void EnableTracking() = 0;

		/**	Remove the tracker's eventhandler from the stack and terminate the mouse tracking thread.
			@param none
		 */
		virtual void DisableTracking() = 0;

		/**	Start tracking the mouse. Usually called as the result of a mouse down event.
			@param theEvent [IN] the event that starts the tracker.
			@return bool16 return kTrue to continue tracking, kFalse if tracking should stop.
		 */
		virtual bool16 BeginTracking(IEvent* theEvent) = 0;

		/**	Called by the tracker event handler.  This is a cover routine for ContinueTracking for
			things like autoscrolling.  Generally this is not overridden in subclasses of CTracker.
			@param where [IN] global system coordinate at time of the call. Can convert to a pasteboard coordinate
			via GlobalToPasteboard method in CTracker.h.
		 */
		virtual void HandleContinueTracking(const GSysPoint& where) = 0;

		/**	Called after BeginTracking and before EndTracking.  ContinueTracking is called 
			repeatedly even when the mouse is not moving (to support things like auto scrolling)
			@param where [IN] current mouse position in pasteboard coordinates
			@param mouseDidMove [IN] did the mouse actually move from previous call?
		 */
		virtual void ContinueTracking(const PBPMPoint& where, bool16 mouseDidMove) = 0;

		/**	Tracking is completed (user has releasted mouse). Clean up any loose ends and post any dynamic commands.
			@param theEvent [IN] the event at end tracking time (typically a mouse up event).
			@return bool16 return code appears to be unused (typically trackers return kTrue)
		 */
		virtual bool16 EndTracking(IEvent* theEvent) = 0;

		/**	Immediately terminate tracking. Typically called in error state situations.
			@param theEvent [IN] the event 
		 */
		virtual void AbortTracking(IEvent* theEvent) = 0;

		/**	Used by certain timer threads to indicate that they have fired.
			@param data [IN] int32 value, elapsed time in milliseconds
		 */
		virtual void TimerMessage(int32 data) = 0;

		/**	Called by BeginTracking, does the action of tracking without setting up the tracker
			@param theEvent 
			@return bool16 
		 */
		virtual bool16 DoBeginTracking(IEvent* theEvent) = 0;

		/**	Called by EndTracking, does the action end tracking would do without ending the tracking
			@param theEvent [IN] the IEvent
			@return bool16 return value undefined, though typical trackers return kTrue.
		 */
		virtual bool16 DoEndTracking(IEvent* theEvent) = 0;

		/**	Initializes the starting point (fFirstPoint) and other values the tracker needs to run.
			Typically called automatically by base class CTracker, BeginTracking. Clients may want to
			override if they have additional private initialization tasks to do.
			@param theEvent [IN] the IEvent
		 */
		virtual void Initialize(IEvent* theEvent) = 0;

private:

		/**	Indicate which control view the tracker is modifying. Used for access to
			graphics contexts, etc. Snap to interface is optional, but is must be present
			if the tracker wants to do snap to.

			@param theControlView [IN] the control view to track in.
			@param theSnapper [IN] the ISnapTo interface if the tracker want snap to behavior. Applies to tracker in the layout widget.
			@param context [IN] the item context for the tracker to use. Obsolete. 
			@see IControlView.h
			@see ISnapTo.h
			@see IItemContext.h
		 */
		virtual void SetupTracker(IControlView* theControlView, ISnapTo* theSnapper, IItemContext* context) = 0;
};

#endif