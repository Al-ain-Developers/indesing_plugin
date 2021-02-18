//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/trackers/CLayoutTracker.cpp $
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
//  Will be base class of ScaleTracker and RotateTracker
//  Introduces StartDrag/ContinueDrag/StopDrag protocol, and patient user support
//  Intended as potential replacement for CWireTracker
//  
//========================================================================================

#include "VCWidgetHeaders.h"

// ----- Interfaces -----

#include "IControlView.h"
#include "ICursorUtils.h"
#include "IEvent.h"
#include "ILayoutTrackerAccess.h"
#include "ISpread.h"
#include "ISprite.h"
#include "IGeometryFacade.h"

// ----- Includes -----

#include "AGMGraphicsContext.h"
#include "CLayoutTracker.h"
#include "KeyStates.h"

// ----- Utility files -----

#include "EventUtilities.h"
#include "IPageItemTypeUtils.h"
#include "ILayoutUIUtils.h"
#include "IPageItemUtils.h"
#include "IPasteboardUtils.h"
#include "PreferenceUtils.h"
#include "SelectionUtils.h"
#include "TransformUtils.h"

//========================================================================================
// CLASS CLayoutTracker
//========================================================================================

//----------------------------------------------------------------------------------------
// CLayoutTracker constructor
//----------------------------------------------------------------------------------------

CLayoutTracker::CLayoutTracker(IPMUnknown *boss) :
	CTracker(boss),
	fDragStarted(kFalse),
	fShiftKeyPressed(kFalse)
{
}


//----------------------------------------------------------------------------------------
// CLayoutTracker::~CLayoutTracker
//----------------------------------------------------------------------------------------

CLayoutTracker::~CLayoutTracker()
{
}

//----------------------------------------------------------------------------------------
// CLayoutTracker::Initialize
//----------------------------------------------------------------------------------------

void CLayoutTracker::Initialize(IEvent* theEvent)
{
	fSnapType = ISnapTo::kSnapNone;
	CTracker::Initialize(theEvent);

	InterfacePtr<ILayoutControlData> viewData(fControlView, IID_ILAYOUTCONTROLDATA);
	InterfacePtr<ISpread> spread(viewData->GetSpreadRef(), IID_ISPREAD);
	fPasteboardBounds = Utils<Facade::IGeometryFacade>()->GetItemBounds( GetUIDRef(spread), Transform::PasteboardCoordinates(), Geometry::OuterStrokeBounds());//XFSpreadIssue

	// We need the initial point in view coords
	fInitialViewPoint = fFirstPoint;
	fControlView->ContentToWindowTransform(&fInitialViewPoint);
}

//----------------------------------------------------------------------------------------
// CLayoutTracker::BeginTracking
//----------------------------------------------------------------------------------------

bool16 CLayoutTracker::BeginTracking(IEvent* theEvent)
{
	// Prevent multiple enabled CSBs
	InterfacePtr<ISelectionManager> iSelectionManager( Utils<ISelectionUtils>()->QueryViewSelectionManager(fControlView));
	K2Vector<ClassID>       csbKeepList;
	csbKeepList.push_back (kNewLayoutSelectionBoss);
	iSelectionManager->DeselectAllExcept(&csbKeepList);

	return CTracker::BeginTracking(theEvent);
}


//----------------------------------------------------------------------------------------
// CLayoutTracker::DoBeginTracking
//----------------------------------------------------------------------------------------

bool16 CLayoutTracker::DoBeginTracking(IEvent* theEvent)
{
	return kTrue;
}

//----------------------------------------------------------------------------------------
// CLayoutTracker::ContinueTracking
//----------------------------------------------------------------------------------------

void CLayoutTracker::ContinueTracking(const PBPMPoint& where, bool16 mouseDidMove)
{
	if (mouseDidMove || (::IsShiftKeyPressed() != this->IsShiftKeyPressed()) || (::IsShiftKeyPressed() && !IsDragStarted()))
	{
		this->SetShiftKeyPressed(::IsShiftKeyPressed());

		// Make sure mouse is still down before we start dragging items around.
		if (!this->IsDragStarted() && !::IsMouseButtonReleased())
		{
			PMPoint viewWhere(where);
			fControlView->ContentToWindowTransform (&viewWhere);

			// Drag operation starts when the mouse has moved away from
			// the starting point by the minimum drag amount.
			// In patient user, make sure mouse has moved past kMinDragDistance or kPatientUserMinDragTicks has elapsed, even
			// though patient user might have a shorter delay. Prevents accidental transforming of items.
			if (abs(viewWhere.X() - fInitialViewPoint.X()) > kMinDragDistance || 
				abs(viewWhere.Y() - fInitialViewPoint.Y()) > kMinDragDistance ||
				((GetTimerFlags() & IShape::kPatientUser) && GetElapsedTime() > kPatientUserMinDragTicks) )
			{
				this->HandleStartDrag(where);
			}
		}

		if (this->IsDragStarted())
		{
			// handle move is not called first time thru.  This allows
			// an update to go thru when we invalidate the old location
			this->ContinueDrag( where, this->IsShiftKeyPressed() ) ;
		}
	}
}

//----------------------------------------------------------------------------------------
// CLayoutTracker::EndTracking
//----------------------------------------------------------------------------------------

bool16 CLayoutTracker::EndTracking(IEvent* theEvent)
{
	if (IsDragStarted())
	{
		this->ContinueDrag(fPreviousPoint, theEvent->ShiftKeyDown());
		this->HandleStopDrag(fPreviousPoint);
	}

	return CTracker::EndTracking(theEvent);
}

//----------------------------------------------------------------------------------------
// CLayoutTracker::AbortTracking
//----------------------------------------------------------------------------------------

void CLayoutTracker::AbortTracking(IEvent* theEvent)
{
	InterfacePtr<ISprite> sprite(this, UseDefaultIID());
	if (sprite && sprite->ValidSprite())
	{
		NonMarkingAGMGraphicsContext gc(fControlView);
		sprite->Hide(&gc, kFalse, nil);
		sprite->DestroySprite(&gc);
	}

	CTracker::AbortTracking(theEvent);
}

//----------------------------------------------------------------------------------------
// CLayoutTracker::ContinueDrag
//----------------------------------------------------------------------------------------

void CLayoutTracker::ContinueDrag(const PBPMPoint& where, bool16 shiftDown)
{
}

//----------------------------------------------------------------------------------------
// CLayoutTracker::HandleStartDrag
//----------------------------------------------------------------------------------------

void CLayoutTracker::HandleStartDrag(const PBPMPoint& where)
{
	ASSERT_MSG(!fDragStarted, "Restarting a drag!");

	fDragStarted = kTrue;
	this->StartDrag(where);
}

//----------------------------------------------------------------------------------------
// CLayoutTracker::StartDrag
//----------------------------------------------------------------------------------------

void CLayoutTracker::StartDrag(const PBPMPoint& where)
{
}

//----------------------------------------------------------------------------------------
// CLayoutTracker::HandleStopDrag
//----------------------------------------------------------------------------------------

void CLayoutTracker::HandleStopDrag(const PBPMPoint& where)
{
	ASSERT_MSG(fDragStarted, "Drag not started, can't stop it!");
	this->StopDrag(where);
	fDragStarted = kFalse;
}

//----------------------------------------------------------------------------------------
// CLayoutTracker::StopDrag
//----------------------------------------------------------------------------------------

void CLayoutTracker::StopDrag(const PBPMPoint& where)
{
}

//----------------------------------------------------------------------------------------
// CLayoutTracker::SetDragStarted
//----------------------------------------------------------------------------------------

void  CLayoutTracker::SetDragStarted(bool16 start)
{
	fDragStarted = start;
}

//----------------------------------------------------------------------------------------
// CLayoutTracker::IsDragStarted
//----------------------------------------------------------------------------------------

bool16 CLayoutTracker::IsDragStarted() const
{
	return fDragStarted;
}

//----------------------------------------------------------------------------------------
// CLayoutTracker::SetShiftKeyPressed
//----------------------------------------------------------------------------------------

void  CLayoutTracker::SetShiftKeyPressed(bool16 pressed)
{
	fShiftKeyPressed = pressed;
}

//----------------------------------------------------------------------------------------
// CLayoutTracker::IsShiftKeyPressed
//----------------------------------------------------------------------------------------

bool16  CLayoutTracker::IsShiftKeyPressed() const
{
	return fShiftKeyPressed;
}

//----------------------------------------------------------------------------------------
// CLayoutTracker::TimerMessage
//----------------------------------------------------------------------------------------

void CLayoutTracker::TimerMessage(int32 flags)
{
	this->ChangeModalCursor(CursorSpec(kCrsrDrag));
	CTracker::TimerMessage(flags);
}

//----------------------------------------------------------------------------------------
// CLayoutTracker::WantTimer
//----------------------------------------------------------------------------------------

bool16 CLayoutTracker::WantTimer(ClassID trackerTimerBoss)
{
	// Allow text recomposition if the user pauses, except for anchored objects.
	// Anchored objects are moved by composition at the same time they are transformed by this tracker, which this tracker can't handle. #1055131, #2767219, #2759919
	InterfacePtr<ISelectionManager> selMgr( Utils<ISelectionUtils>()->QueryViewSelectionManager(fControlView));
	InterfacePtr<ILayoutTrackerAccess> layoutTrackerAccess(static_cast<ILayoutTrackerAccess*>(Utils<ISelectionUtils>()->QuerySuite(ILayoutTrackerAccess::kDefaultIID, selMgr)));
	const UIDList itemList = layoutTrackerAccess->GetUIDList(this, kDontStripStandoffs);

	bool16 bAnchoredObjectSelected(kFalse);
	if (itemList.Length() && Utils<IPageItemTypeUtils>()->IsInline(itemList.GetRef(0)) && 
		Utils<IPageItemTypeUtils>()->GetInlinePosition(itemList.GetRef(0)) == IAnchoredObjectData::kAnchoredObject)
		bAnchoredObjectSelected = kTrue;

	if (trackerTimerBoss == kDynamicPauseTimerBoss)
	{
		if (!bAnchoredObjectSelected)
			return kTrue;
	}
	else if (trackerTimerBoss == kPatientUserBoss)	
	{
		// Allow live updates of screen after GetUIPatientUserDelay has elapsed (except for anchored objects, see #1055131, #2759919
		if (!bAnchoredObjectSelected)
			return kTrue;
	}

	return CTracker::WantTimer(trackerTimerBoss);
}


