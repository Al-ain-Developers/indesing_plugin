//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CTrackerEventHandler.h $
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
#ifndef __CTRACKEREVENTHANDLER__
#define __CTRACKEREVENTHANDLER__

#include "CEventHandler.h"

//----------------------------------------------------------------------------------------
// CTrackerEventHandler: Forwards events to CTracker
//----------------------------------------------------------------------------------------

#pragma export on

/** Implementation of IEventHandler that forwards events to CTracker.
*/
class WIDGET_DECL CTrackerEventHandler : public CEventHandler
{
	public:
		/** Constructor.
			@param boss object on which this interface is aggregated
		*/
		CTrackerEventHandler(IPMUnknown *boss);

		/** Destructor.
		*/
		virtual ~CTrackerEventHandler();			
			
		/** Begin tracking message will get sent out, if event in bounds.

			@param theEvent event being handled
			@return kTrue if the event is within the bounds of the control-view of the tracker,
				kFalse otherwise
		*/
		virtual bool16 LButtonDn(IEvent* theEvent);
			 
			
		/** End tracking message will get sent to tracker.
			@return value returned by ITracker::EndTracking
		*/
		virtual bool16 LButtonUp(IEvent* theEvent);
		
			
		/** We still need to do this.  It used to be that all mouse movement happened
			from a mouse tracker task.  But that resulted in jerky tracking and fought
			with the drag event.  Once solution would be to remove the mousedrag code and
			rely solely on the idle task but that results in an unwanted behaviour: 
			For a quick drag (mouse down followed by mouse up) the idle task inserts 
			a bogus mouse position into the tracker but before the tracker can handle the
			end tracking event.  This gives a momentary flash of drawing the sprite where
			the mouse is and then redrawing the sprite to where the mouse button was let up.
			This effect will happen anytime the sequence of events is:
			GetNextEvent, mouse up inserted into event queue, run all tasks, GetNextEvent, mouse up handled.
	
			Now the only thing the tracker thread is responsible for is generating mouse drag
			events when the mouse is outside the window and has not moved.

			@param e event of interest
			@return kTrue, meaning that the event has been consumed
		*/
		virtual bool16 MouseDrag(IEvent* e);

		/** Disallow handling of keyboard shortcuts during tracking

			@param e event of interest
			@return kTrue, meaning that the event has been consumed
		*/
		virtual bool16 KeyCmd(IEvent* e);
			

		/** Disallow handling of keyboard shortcuts during tracking
			@param e event of interest
			@return kTrue, meaning that the event has been consumed
			*/
		virtual bool16 KeyUp(IEvent* e);

		/** Disallow handling of keyboard shortcuts during tracking
			@param e event of interest
			@return kTrue, meaning that the event has been consumed
		*/
		virtual bool16 KeyDown(IEvent* e);

		/** Calls AbortTracking if the application is suspended
			@param theEvent event of interest
			@return kFalse
		*/ 
		virtual bool16 Suspend(IEvent* theEvent);
			 
			
		/**Calls AbortTracking if the application is deactivated
			@param theEvent event of interest
			@return kFalse
		*/
		virtual bool16 Deactivate(IEvent* theEvent);
			

		/** Swallows the event to suppress right button activity while tracking
			@param theEvent event of interest
			@return kTrue if tracking, kFalse otherwise
		*/
		virtual bool16 RButtonDn(IEvent *e);
			
		/** Swallows the event to suppress right button activity while tracking
			@param theEvent event of interest
			@return kTrue if tracking, kFalse otherwise
		*/
		virtual bool16 RButtonUp(IEvent *e);

		/** Swallows the event to suppress wheel activity while tracking
			@param theEvent event of interest
			@return kTrue if tracking, kFalse otherwise
		*/
		virtual bool16 MouseWheel(IEvent* e);
		
};

#pragma export off

#endif