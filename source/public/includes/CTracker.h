//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CTracker.h $
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
#ifndef __CTRACKER__
#define __CTRACKER__

#include "ITracker.h"
#include "ITrackerTimer.h"
#include "HelperInterface.h"
#include "PMRect.h"
#include "AcquireModalCursor.h"
#include "AutoBusyCursor.h"
#include "IDynamicTrackerData.h"
#include "K2Vector.h"
#include "CSprite.h"

class IPanorama;
class ISnapTo;
class ILayoutSelectionSuite;
class ISelectionManager;
class IRulerData;
class IEventHandler;

//----------------------------------------------------------------------------------------
// CTracker: Concrete implementation for trackers
//----------------------------------------------------------------------------------------

#pragma export on

/** Concrete implementation for trackers.

	A tracker monitors mouse movement while an object is being manipulated by a
	tool and provides visual feedback in the layout view. It makes the changes to the
	objects being manipulated using commands. A tool may have one or more
	trackers but only a single tracker will be active at any one time.

	Tracking occurs when the user manipulates objects (or widgets) using the mouse. Tracking
	behavior is context sensitive and depends on the selected tool, where and on
	what the mouse down event occurs. Tracking the mouse can occur in order to
	create something or select something, or move a control in a widget for example.

	ITracker is the main controlling interface for a tracker. It is the interface used by clients of
	the tracker to focus the tracker on a view and to which overall control is passed
	so the mouse can be tracked. It manages and controls all other interfaces in the boss.
*/
class WIDGET_DECL CTracker : public ITracker
{
	public:
		CTracker(IPMUnknown *boss);
		virtual ~CTracker();
		
		/** Initialize the state of the tracker with a control-view and other optional abstractions.
			Indicate which control view the tracker is modifying. Used for access to
			graphics context. Snap to interface is optional, but it must be present
			if the tracker needs to do snap to.

			@param theControlView [IN] the control view to track in.
			@param theSnapper [IN] the ISnapTo interface if the tracker want snap to behavior. Applies to tracker in the layout widget. May be nil.
			@param context [IN] the item context for the tracker to use. Obsolete. 
			@see IControlView.h
			@see ISnapTo.h
			@see IItemContext.h
		*/
		virtual void SetupTracker(IControlView* theControlView, ISnapTo* theSnapper = NULL, IItemContext* context = NULL);

		/** Acquire interface ptr to associated control-view.
			@return reference-increment ptr to the associated IControlView
		*/
		virtual IControlView* QueryControlView() const;

		/** Determine if tracking is turned on.
		*/
		virtual bool16 IsEnabled();

		/** Determine if this tracker is actively tracking at present time. Means that 
			the tracker's BeginTracking() method has been called, i.e. the tracker
			is actually tracking the mouse.
			@return kTrue if tracking (BeginTracking() has been called), kFalse otherwise
		*/
		virtual bool16 IsTracking();

		/** Turn on tracking; means that the tracker's eventhandler is on the stack ready to accept events.
			Called automatically in base class BeginTracking.
		*/
		virtual void EnableTracking();

		/** Turns off tracking; this should rarely be overridden by client code. 
			Removes the tracker's eventhandler from the stack, releases the mouse capture.
			Also stops the timer (fMouseTrackerThread).
			Called automatically in base class EndTracking (and AbortTracking).
		*/
		virtual void DisableTracking();
		
		/** Start tracking the mouse. Usually called as the result of a mouse down event.
			@param theEvent [IN] the associated event
		*/
		virtual bool16 BeginTracking(IEvent* theEvent);

		/** Called by the tracker event handler. This is a cover routine for
			ContinueTracking for things like autoscrolling. Generally this is not
			overridden in sub-classes of CTracker.
			@param where [IN] the global system point at time of call. Can convert to a pasteboard coordinate
			via GlobalToPasteboard method in CTracker.h.
		*/
		virtual void HandleContinueTracking(const GSysPoint& where);

		/** The default implementation does nothing; client code will likely override this.
			Called after BeginTracking() and before EndTracking().
			ContinueTracking is called repeatedly even when the mouse is not moving
			(to support things like auto scrolling)
			@param where [IN] current location of mouse ptr
			@param mouseDidMove [IN] kTrue if mouse-event generated this call, kFalse otherwise (e.g. auto-scrolling)
		*/
		virtual void ContinueTracking(const PBPMPoint& where, bool16 mouseDidMove);

		/** Tracking is completed. Tidy up and post any dynamic commands.
			@param theEvent [IN] the associated event
		*/
		virtual bool16 EndTracking(IEvent* theEvent);

		/** Override this method to provide any special behavior required if the tracker
			was aborted in the middle of tracking.  For example the PlaceTextTracker needs
			to abort if a menu is selected after the tracker is enabled
			@param theEvent [IN] the associated event
		*/
		virtual void AbortTracking(IEvent* theEvent);

		/**	Called after the ITrackerTimer has expired. Timer is started in
			BeginTracking. Used to turn on patient user tracking by CLayoutTracker. Can be used to change cursor feedback.
			@param flags [IN] int32 value, flags from IShape, typically draw flags such as kPatientUser or kDynamicPause
			@see kMouseTrackerBoss
			@see ITrackerTimer.h
			@see CLayoutTracker.h
			@see IShape.h
			@see StartTimer, StopTimer, WantTimer
		 */
		virtual void TimerMessage(int32 flags)	{ SetTimerFlags(GetTimerFlags() | flags); }

		/** Stop a tracker timer with a particular ClassID
			@param trackerTimerBoss	[IN] ClassID for the tracker timer. Typical values are kMouseTrackerBoss, kPatientUserBoss and kDynamicPauseTimerBoss.
			@return bool16 kTrue to start the timer for this class, kFalse otherwise. Default implemention returns kFalse.
		*/
		virtual bool16 WantTimer(ClassID trackerTimerBoss);

	protected:
	
		/** Subclasses of CTracker can override Initialize and DoBeginTracking()
			instead of overriding BeginTracking(). This way they are guaranteed
			that Initialize has been called first, and the thread only gets
			started if DoBeginTracking() returns kTrue.

			Previously, overrides of BeginTracking() had to call the inherited method
			at the end, thereby losing the benefit of any initialization done
			by the base class.
			
			Set initial fields. 
			Called before DoBeginTracking()
			@param theEvent [IN] the event at time of call
		 */
		virtual void Initialize(IEvent* theEvent);
		
		/** 
			A return value of kTrue means "continue tracking". i.e. this
			tracker did not simply spawn a different one
			@param theEvent [IN] event that is behind this call
		*/
		virtual bool16 DoBeginTracking(IEvent* theEvent);
			
		/**	Called by EndTracking, does the action end tracking would do without ending the tracking.
			@param theEvent [IN] event that is behind this call
			@return bool16 return value appears to be unused.
		 */
		virtual bool16 DoEndTracking(IEvent* theEvent);
						
		/** If IDynamicTrackerData is present, use it to notify document observers. Can pass effect directly, 
			or GetTrackingEffect will be used to determine it if effect is IDynamicTrackerData::kUnknown.
			@param startPt
			@param endPoint
			@param effect, How tracker affects x, y, w, h, etc values. See IDynamicTrackerData::TrackingEffect.
		*/
		virtual void NotifyBeginTracking(const PMPoint& startPt, IDynamicTrackerData::TrackingEffect effect = IDynamicTrackerData::kUnknown);

		/** If IDynamicTrackerData is present, use it to notify document observers. Can pass effect directly, 
			or GetTrackingEffect will be used to determine it if effect is IDynamicTrackerData::kUnknown.
			@param startPt
			@param endPoint
		*/
		virtual void NotifyContinueTracking(const PMPoint& startPt, const PMPoint& endPoint, IDynamicTrackerData::TrackingEffect effect = IDynamicTrackerData::kUnknown);
			
		/** If IDynamicTrackerData is present, use it to notify document observers. Can pass effect directly, 
			or GetTrackingEffect will be used to determine it if effect is IDynamicTrackerData::kUnknown.
			@param startPt
			@param endPoint
			@param effect, How tracker affects x, y, w, h, etc values. See IDynamicTrackerData::TrackingEffect.
		*/
		virtual void NotifyEndTracking(const PMPoint& startPt, const PMPoint& endPoint, IDynamicTrackerData::TrackingEffect effect = IDynamicTrackerData::kUnknown);

		/** If IDynamicTrackerData is present, use it to notify document observers. This function is called
			by NotifyBeginTracking(), NotifyContinueTracking(), and NotifyEndTracking() whenever a specific tracking state is not 
			provided to determine what effect to use for notifying. (i.e. when effect is IDynamicTrackerData::kUnknown).
			By default kBeginTracking -> kAffectsXY, kContinueTracking -> kAffectsXYWH, kEndTracking -> kAffectsXYWH
			@param state, one of kNotTracking, kBeginTracking, kContinueTracking, kEndTracking, kAbortTracking.
			@return - returns IDynamicTrackerData::TrackingEffect, IDynamicTrackerData::kAffectsXY by default.
		*/
		virtual IDynamicTrackerData::TrackingEffect GetTrackingEffect(IDynamicTrackerData::TrackingState state);
		
		/** Push tracker's event handler on the stack. In general should be for internal use only since
			this is called automatically in EnableTracking.
		*/
		virtual void PushEventHandler();
		
		/** Pop tracker's event handler from the stack. In general should be for internal use only since
			this is called automatically in DisableTracking.
		*/
		virtual void PopEventHandler();
		
		/**	Determine if this tracker wants to provide automatic scrolling.
			@param currentPoint [IN] the point in pasteboard coordinates.
			@return bool16 return kTrue to autoscroll, kFalse otherwise.
		 */
		virtual bool16 WantsToAutoScroll(const PMPoint& currentPoint);

		/**	Scroll the view by the indicated amount
			@param scrollBy [IN] how much to scroll by. Typical value obtained from the panorama
			associated with this tracker's view.
			@param scrolledPoint [IN] the point from HandleContinueTracking that caused the autoscroll
			@return PMPoint the amount that the panorama scrolled
			@see QueryPanorama
			@see IPanorama.h
			@see GetAutoScrollDelta
			@see ScrollBy
		 */
		virtual PMPoint AutoScroll(const PMPoint& scrollBy, const PMPoint& scrolledPoint);
		
		/**	Convert a point from global system coordinate to pasteboard point.
			@param thePoint [IN] input point
			@param convertedPoint [OUT] output point
		 */
		virtual void GlobalToPasteboard(const GSysPoint& thePoint, PBPMPoint& convertedPoint);

		/**	Convert a point from pasteboard point to global system coordinate.
			@param pbPoint [IN] input point
			@return PMPoint converted point in pasteboard coordinates
		 */
		virtual PMPoint PasteboardToGlobal(const PBPMPoint& pbPoint);
		
		/** Return a bumped reference to the panorama associated with this tracker's view.
		*/
		virtual IPanorama *QueryPanorama( IControlView *pView ) const;
		
		/** Helper method called in base class during BeginTracking to turn off updates.
			@see ILayoutUIUtils.h
			@see DisableUpdateAllDocumentViews
		*/
		virtual void DisableUpdates();
		
		/** Helper method called in base class during EndTracking to turn on updates.
			@see ILayoutUIUtils.h
			@see EnableUpdateAllDocumentViews
		*/
		virtual void EnableUpdates();

		/** Deselect all types of selection in the fControlView
			@see ISelectionManager.h
			@see DeselectAll
		*/
		void DeselectAllItems() ;			

		/** Override if the base class wants to change the input value in any way.
			This method is called before snap to is called
			The implementation in CTracker computes the ruler adjusted value, if the
			tracker is tracking in the layout view 
			@param adjustedPoint [IN/OUT] the adjusted value
		 */
		virtual void ComputeAdjustedPoint (PMPoint& adjustedPoint);
		
		/** Called internally during BeginTracking to set up the modal cursor during life of tracker.
		*/
		void InitializeModalCursor();

		/** Call this method to switch the cursor while tracking.
			Make sure CTracker::BeginTracking() gets called first, however.
			@param spec [IN] the cursor spec to change to
		 */
		void ChangeModalCursor(const CursorSpec& spec);

		/** Call this after DoSnapTo() has been called and fSnapType is updated
			if your tracker wants to update the cursor as the mouse snaps and unsnaps.
		*/
		void UpdateModalCursor();
		
		/** Called internally by CTracker in various places.  
		*/
		void ReleaseModalCursor();

		/** Called to initialize tracker timer
		*/
		virtual uint32 GetMouseMoveDelay(){ return kDefaultMouseMoveDelay; }
		
		/** Called to initialize tracker timer
		*/
		virtual uint32 GetMouseSteadyDelay(){ return kDefaultMouseSteadyDelay; }

		/**
		The CTracker will call this method to adjust the raw point. The current
		implemention will use fSnapTo or ComputeAdjustedPoint() to do this.
		Some classes may find it useful to override this method if they wish
		to only adjust/Snap one dimension.
		@param point to adjust
		@return kTrue if the point changed
		*/
		virtual bool16	AdjustPoint(PBPMPoint& point);

		/** Called if WantTimer for a particular ITrackerTimer ClassID returns kTrue.
			@param trackerTimerBoss	[IN] ClassID for the tracker timer. Typical values are kMouseTrackerBoss, kPatientUserBoss and kDynamicPauseTimerBoss.
			@param milliSeconds	[IN] delay until timer is first called. Typically the tracker timer would then call the tracker's TimerMessage method.
			@param mouseMoveDelay [IN] how frequently in milliseconds RunTask is called while mouse is moving.
			@param mouseSteadyDelay [IN] how frequently in milliseconds RunTask is called while mouse is not moving.
		*/
		void StartTimer(ClassID trackerTimerBoss, uint32 milliSeconds, uint32 mouseMoveDelay = kDefaultMouseMoveDelay, uint32 mouseSteadyDelay = kDefaultMouseSteadyDelay);

		/** Stop a tracker timer with a particular ClassID
			@param trackerTimerBoss	[IN] ClassID for the tracker timer to stop.
		*/
		void StopTimer(ClassID trackerTimerBoss);

		/** Timer management flags, set when an tracker timer is run, typically when an ITrackerTimer's RunTask method is called. */
		bool16 GetTimerFlags()				{ return (fTimerFlags); }
		void SetTimerFlags(int32 flags)		{ fTimerFlags = flags; }
		
		uint32 GetElapsedTime()				{ return SystemUtils::TickCount() - fFirstTicks; }

protected:
		virtual IDataBase* GetTrackingDataBase() const;
		
		IControlView* fControlView;
		IDataBase* fDataBase;
		IItemContext* fItemContext;
		ISnapTo* fSnapTo;
		SnapType fSnapType;	// Current snap status of fCurrentPoint. Should be updated when DoSnapTo is called.

		bool16 fIsTracking;
		bool16 fWantsToAutoScroll;
		PMPoint fPreviousPoint;
		PMPoint fFirstPoint;
		GSysPoint fFirstGlobalWhere;
		uint32 fFirstTicks;	// TickCount at BeginTracking time
		
	
		bool16 fEnabled;

		IRulerData*	fHorzRuler;
		IRulerData*	fVertRuler;

		AcquireModalCursor* fModalCursor;
		AutoBusyCursor* fAutoBusyCursor;
			
		uint32 fOldSchedulerMask;		// save off the old scheduler mask, so it can be restored

		int32 fTimerFlags;
		K2Vector<ITrackerTimer*>	fTimerPtrs;
		//InterfaceCollection<ITrackerTimer> fTimerCollection;

#ifdef DEBUG
		const IEventHandler*	fMyEventHandler;
#endif
		
		// Deactivate the IPageItemFocus at the keyboard
		static void	DeactivatePageItem() ;
	
	DECLARE_HELPER_METHODS()
};

#pragma export off

#endif
