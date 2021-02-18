//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CLayoutTracker.h $
//  
//  Owner: Richard Rodseth
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
//  Base class of ScaleTracker and RotateTracker
//  Introduces StartDrag/ContinueDrag/StopDrag protocol, and patient user support
//  Intended as potential replacement for CWireTracker
//  
//========================================================================================

#pragma once
#ifndef __CLAYOUTTRACKER__
#define __CLAYOUTTRACKER__

#include "CTracker.h"
#include "PMRect.h"

//----------------------------------------------------------------------------------------
// Forward declarations
//----------------------------------------------------------------------------------------
class ITrackerTimer;

//----------------------------------------------------------------------------------------
// Class CLayoutTracker
//----------------------------------------------------------------------------------------

#pragma export on

class WIDGET_DECL CLayoutTracker : public CTracker
{
	public:
		virtual ~CLayoutTracker();

		virtual bool16 BeginTracking(IEvent* theEvent);
		virtual void ContinueTracking(const PBPMPoint& where, bool16 mouseDidMove);
		virtual bool16 EndTracking(IEvent* theEvent);
		virtual void AbortTracking(IEvent* theEvent);

	protected: // Frequently overridden
		virtual void Initialize(IEvent* theEvent);
		virtual bool16 DoBeginTracking(IEvent* theEvent);
		virtual void StartDrag(const PBPMPoint& where);		
		virtual void ContinueDrag(const PBPMPoint& where, bool16 shiftDown);
		virtual void StopDrag(const PBPMPoint& where);
	
	
	protected: // Rarely overridden	
		CLayoutTracker(IPMUnknown* boss);

		virtual void HandleStartDrag(const PBPMPoint& where);
			// Sets fDragStarted, and calls StartDrag
		
		virtual void HandleStopDrag(const PBPMPoint& where);
			// Calls StartDrag and sets fDragStarted

		virtual void TimerMessage(int32 flags);
		virtual bool16 WantTimer(ClassID trackerTimerBoss);

		// Drag state
		virtual void SetDragStarted(bool16 start);
		virtual bool16 IsDragStarted() const;

		// Shift key state
		virtual void SetShiftKeyPressed(bool16 pressed);
		virtual bool16 IsShiftKeyPressed() const;		

		
	protected:
		// PMPoint fInitialPoint; Use fFirstPoint from CTracker.h instead.
		PMPoint fInitialViewPoint;
		bool16 fDragStarted;
		bool16 fShiftKeyPressed;				// True if shift key is currently pressed
		PMRect fPasteboardBounds;
};

#pragma export off

#endif