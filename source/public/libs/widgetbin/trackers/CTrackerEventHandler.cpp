//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/trackers/CTrackerEventHandler.cpp $
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

#include "VCWidgetHeaders.h"
#include "CTrackerEventHandler.h"

// ----- Interface Includes -----

#include "IControlView.h"

// ----- Implementation Includes -----

#include "ErrorUtils.h"
#include "EventUtilities.h"
#include "keyboarddefs.h"
#include "KeyStates.h"
#include "PlatformEvent.h"
#include "IIntData.h"

#include "CTracker.h"

//========================================================================================
// CLASS CTrackerEventHandler
//========================================================================================
// BP 04/17/01: moved to  .../source/components/WidgetBin/WidgetBinImpl.cpp
// CREATE_PMINTERFACE(CTrackerEventHandler, kCTrackerEventHandlerImpl)

//----------------------------------------------------------------------------------------
// CTrackerEventHandler constructor 
//----------------------------------------------------------------------------------------

CTrackerEventHandler::CTrackerEventHandler(IPMUnknown *boss) :
	CEventHandler(boss)
{
}

//----------------------------------------------------------------------------------------
// CTrackerEventHandler destructor 
//----------------------------------------------------------------------------------------

CTrackerEventHandler::~CTrackerEventHandler()
{
}

//----------------------------------------------------------------------------------------
// CTrackerEventHandler::LButtonDn
//----------------------------------------------------------------------------------------

bool16 CTrackerEventHandler::LButtonDn(IEvent* e)
{
	InterfacePtr<ITracker> tracker(this, IID_ITRACKER);
	InterfacePtr<IControlView> controlView(tracker->QueryControlView());
	
	PMPoint localPoint(controlView->GlobalToWindow(e->GlobalWhere()));
	PMRect bounds(controlView->GetBBox());
	
	bool16 bIsTracking = tracker->IsTracking();

	if (!bIsTracking && bounds.PointIn(localPoint))
	{
		return tracker->BeginTracking(e);
	}
	else if (bIsTracking)	// Safety check: LButtonUp probably was lost. See bug 541289.
	{
		// Simulate an LButtonUp to force tracking to end
		return LButtonUp(e);	
	}

	return kFalse;
}

//----------------------------------------------------------------------------------------
// CTrackerEventHandler::LButtonUp
//----------------------------------------------------------------------------------------

bool16 CTrackerEventHandler::LButtonUp(IEvent* theEvent)
{
	bool16 results = kFalse;
	
	InterfacePtr<ITracker> tracker(this, IID_ITRACKER);
	if (tracker->IsTracking())
	{
		// Call ContinueTracking one last time to ensure that it was called at least once
		tracker->HandleContinueTracking(theEvent->GlobalWhere());

		// (dbessett) Check to see if something happened and tracking is already disabled
		if(tracker->IsTracking())
		{		
			// Disable event handling before we do anything else
			tracker->DisableTracking();
				
			results = tracker->EndTracking(theEvent);
				
			// This release brackets the ITrackerFactory::QueryTracker which created the tracker.
			// This should be the last thing done with the tracker
			tracker->Release();
		}
		else
		{	
			// (dbessett) Tracking was already disabled so we call end tracking.  
			// Since tracking was diasabled we assume someone else will release this tracker
			results = tracker->EndTracking(theEvent);
		}
	}
	
	return results;
}

//----------------------------------------------------------------------------------------
// CTrackerEventHandler::KeyCmd
//----------------------------------------------------------------------------------------

bool16 CTrackerEventHandler::KeyCmd( IEvent* theEvent )
{
#ifdef WINDOWS // [RCR] 5/14/99 See #305290
	if (::GetFocus() == nil) 
		theEvent->SetSystemHandledState(IEvent::kDontCall);
#endif
   	if ( !theEvent->IsRepeatKey()  && !::IsMouseButtonReleased())	// Check for mouse still down, key repeats can still come in on Mac after mouse has been released, #1684392 
	{
		InterfacePtr<ITracker> tracker( this, IID_ITRACKER ) ;
		tracker->HandleContinueTracking( ::GetGlobalMouseLocation() ) ;
	}

	return kTrue ;
}

bool16 CTrackerEventHandler::KeyDown( IEvent* theEvent )
{ 
	InterfacePtr<IIntData> trackerKeyData(this, IID_ITRACKERKEYDATA);
	VirtualKey theKey = theEvent->GetVirtualKey();

	if ( !theEvent->IsRepeatKey( ) && !::IsMouseButtonReleased())		// Check for mouse still down, key repeats can still come in on Mac after mouse has been released, #1684392 
	{
		// Save off key state for use by trackers in ContinueTracking. Allows use of keys (such as arrow keys) as modifiers.
		if (trackerKeyData)
			trackerKeyData->Set(theKey.GetDVKeyCode());

		InterfacePtr<ITracker> tracker( this, IID_ITRACKER ) ;
		
		// Just like escape key cancels drag and drop operations, use escape to abort tracking
		if( theKey == kVirtualEscapeKey )
		{		
			tracker->AbortTracking( theEvent ) ;
			tracker->Release();
		}
		else
		{
			tracker->HandleContinueTracking( ::GetGlobalMouseLocation() ) ;
		}
	}
	else if (trackerKeyData)
	{
		// Otherwise, clear out the key
		trackerKeyData->Set(kVirtualNullKey.GetDVKeyCode());
	}

	return kTrue ;
}

bool16 CTrackerEventHandler::KeyUp( IEvent* theEvent )
{ 
	if ( !(::IsVirtualKeyPressed(kVirtualUpArrowKey)
		||	::IsVirtualKeyPressed(kVirtualDownArrowKey)
		||	::IsVirtualKeyPressed(kVirtualLeftArrowKey)
		||	::IsVirtualKeyPressed(kVirtualRightArrowKey)) )
	{
		InterfacePtr<ITracker> tracker( this, IID_ITRACKER ) ;
		tracker->HandleContinueTracking( ::GetGlobalMouseLocation() ) ;
	}
	
	return kTrue ;
}

//----------------------------------------------------------------------------------------
// CTrackerEventHandler::Suspend
//----------------------------------------------------------------------------------------

bool16 CTrackerEventHandler::Suspend(IEvent* theEvent)
{
	InterfacePtr<ITracker> tracker(this, IID_ITRACKER);
	
	// Application is being suspended in the middle of a track so abort
	tracker->AbortTracking(theEvent);

	// This release brackets the ITrackerFactory::QueryTracker which created the tracker.
	// This should be the last thing done with the tracker
	this->Release();
	
	return kFalse;
}

//----------------------------------------------------------------------------------------
// CTrackerEventHandler::Deactivate
//----------------------------------------------------------------------------------------

bool16 CTrackerEventHandler::Deactivate(IEvent* theEvent)
{
	InterfacePtr<ITracker> tracker(this, IID_ITRACKER);
	
	// Application is being deactivated in the middle of a track so abort
	tracker->AbortTracking(theEvent);

	// This release brackets the ITrackerFactory::QueryTracker which created the tracker.
	// This should be the last thing done with the tracker
	this->Release();
	
	return kFalse;
}

//----------------------------------------------------------------------------------------
// CTrackerEventHandler::MouseDrag
//----------------------------------------------------------------------------------------

bool16 CTrackerEventHandler::MouseDrag(IEvent* theEvent)
{
	// We still need to do this.  It used to be that all mouse movement happened
	// from a mouse tracker task.  But that resulted in jerky tracking and fought
	// with the drag event.  Once solution would be to remove the mousedrag code and
	// rely solely on the idle task but that results in an unwanted behaviour: 
	// For a quick drag (mouse down followed by mouse up) the idle task inserts 
	// a bogus mouse position into the tracker but before the tracker can handle the
	// end tracking event.  This gives a momentary flash of drawing the sprite where
	// the mouse is and then redrawing the sprite to where the mouse button was let up.
	// This effect will happen anytime the sequence of events is:
	// GetNextEvent, mouse up inserted into event queue, run all tasks, GetNextEvent, mouse up handled.
	//
	// Now the only thing the tracker thread is responsible for is generating mouse drag
	// events when the mouse is outside the window and has not moved.
	// -jargast 3/22/99
	InterfacePtr<ITracker> tracker(this, IID_ITRACKER);
	
	if (ErrorUtils::PMGetGlobalErrorCode() == kSuccess)
		tracker->HandleContinueTracking(theEvent->GlobalWhere());

	// If we have an error state, abort tracking so we don't process commands any further.
	if (ErrorUtils::PMGetGlobalErrorCode() != kSuccess)
	{
		tracker->AbortTracking(theEvent);
		tracker->Release();
	}
	
	return kTrue;
}

//----------------------------------------------------------------------------------------
// CTrackerEventHandler::RButtonDn
//----------------------------------------------------------------------------------------

bool16 CTrackerEventHandler::RButtonDn(IEvent *e)
{
	// Simulate an LButtonUp to force tracking to end
	InterfacePtr<ITracker> tracker(this, IID_ITRACKER);
	if (tracker->IsTracking())
		return LButtonUp(e);

	return kFalse;
}

//----------------------------------------------------------------------------------------
// CTrackerEventHandler::RButtonDn
//----------------------------------------------------------------------------------------

bool16 CTrackerEventHandler::RButtonUp(IEvent *e)
{
	// Simulate an LButtonUp to force tracking to end
	InterfacePtr<ITracker> tracker(this, IID_ITRACKER);
	if (tracker->IsTracking())
		return LButtonUp(e);

	return kFalse;
}

//----------------------------------------------------------------------------------------
// CTrackerEventHandler::MouseWheel
//----------------------------------------------------------------------------------------

bool16 CTrackerEventHandler::MouseWheel(IEvent* e)
{
	return kTrue;
}

