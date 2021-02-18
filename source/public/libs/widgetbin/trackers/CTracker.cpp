//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/trackers/CTracker.cpp $
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
#include "CTracker.h"

// ----- Interface Includes -----

#include "IEventHandler.h"
#include "IContextualUIDUsageLogger.h"
#include "IControlView.h"
#include "ICursorUtils.h"
#include "IApplication.h"
#include "IEventDispatcher.h"
#include "IPanorama.h"
#include "IEventConverter.h"
#include "IWindow.h"
#include "IWidgetParent.h"
#include "IColumns.h"
#include "IDocument.h"
#include "IKeyBoard.h"
#include "ILayoutController.h"
#include "IPageItemFocus.h"
#include "IItemContext.h"
#include "IRulerData.h"
#include "IEventUtils.h"

#ifdef DRAW_COLORIZED_TEXT_HIGHLIGHT
#include "ITextOffscreen.h"
#include "PMTextUtils.h"
#endif

// ----- Implementation Includes -----

#include "EventUtilities.h"
#include "ITrackerTimer.h"
#include "SpreadID.h"
#include "ILayoutUtils.h"
#include "ILayoutUIUtils.h"
#include "IPageItemUtils.h"
#include "TransformUtils.h"
#include "ISelectionUtils.h"
#include "DiagnosticLogHook.h"

#include "IUserInterfacePreferencesFacade.h"

#if DEBUG && MACINTOSH
#include "DebugClassUtils.h"
#include "StackCrawler.h"
#endif


#pragma mark CTracker implementation

//========================================================================================
// CLASS CTracker
//========================================================================================

DEFINE_HELPER_METHODS(CTracker)


//----------------------------------------------------------------------------------------
// CTracker constructor
//----------------------------------------------------------------------------------------

CTracker::CTracker(IPMUnknown *boss) :	HELPER_METHODS_INIT(boss),
										fControlView(NULL),
										fDataBase(NULL),
										fItemContext(NULL),
										fIsTracking(kFalse),
										fWantsToAutoScroll(kTrue),
										fSnapTo(NULL),
										fSnapType(ISnapTo::kSnapNone),
										fEnabled(kFalse),
										fFirstPoint(0, 0),
										fPreviousPoint(0, 0),
										fHorzRuler(nil),
										fVertRuler(nil),
										fModalCursor(nil),
										fAutoBusyCursor(nil),
										fOldSchedulerMask(0),
										fTimerFlags(0),
										fTimerPtrs(),
										fFirstTicks(0)
									#ifdef DEBUG
									,	fMyEventHandler(nil)
									#endif
{
	SysPointH(fFirstGlobalWhere) = SysPointV(fFirstGlobalWhere) = 0;
}

//----------------------------------------------------------------------------------------
// CTracker destructor
//----------------------------------------------------------------------------------------

CTracker::~CTracker()
{
	if (fDataBase)
		fDataBase->EndTransaction();

	if (fControlView)
		fControlView->Release();

	if ( fHorzRuler )
		fHorzRuler->Release();

	if ( fVertRuler )
		fVertRuler->Release();

	if (fSnapTo)
		fSnapTo->Release();

	if (fItemContext)
		fItemContext->Release();

	ASSERT_MSG(fTimerPtrs.size() == 0, "A tracker timer is still running.");
	for (int32 i = 0; i < fTimerPtrs.size(); i++)
	{
		fTimerPtrs[i]->StopTimer();
		fTimerPtrs[i]->Release();
	}
	fTimerPtrs.clear();

	if (fModalCursor != nil)
	{
		TRACEFLOW_OBSOLETE("Old:Public", "CTracker destructing with as yet unreleased AcquireModalCursor\n");
		ReleaseModalCursor();
	}
#ifdef DEBUG
	{
		InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
		InterfacePtr<IEventDispatcher> dispatcher(theApp, UseDefaultIID());
		if (dispatcher && fMyEventHandler)
		{
			ASSERT_MSG(dispatcher->Peek() != fMyEventHandler, "~CTracker:Event handler still on event dispatcher stack! Did not call CTracker::DisableTracking or CTracker::AbortTracking?");
		}
	}
#endif
}

//----------------------------------------------------------------------------------------
// CTracker::Set
//----------------------------------------------------------------------------------------

void CTracker::SetupTracker(IControlView* theControlView, ISnapTo* theSnapper, IItemContext* theContext)
{
	if (fControlView)
		fControlView->Release();

	fControlView = theControlView;
	if (fControlView)
		fControlView->AddRef();

	if ( fHorzRuler )
		fHorzRuler->Release();

	if ( fVertRuler )
		fVertRuler->Release();

	fHorzRuler = Utils<ILayoutUIUtils>()->QueryHorzRulerData (fControlView);
	fVertRuler = Utils<ILayoutUIUtils>()->QueryVertRulerData (fControlView);

	if (fSnapTo)
		fSnapTo->Release();

	fSnapTo = theSnapper;
	if (fSnapTo)
	{
		fSnapTo->AddRef();
		if (theControlView)
			fSnapTo->Init(theControlView);
	}

	fSnapType = ISnapTo::kSnapNone;
	if (fSnapTo == nil)
	{
		InterfacePtr<ILayoutControlData> layoutData(fControlView, UseDefaultIID());
		const UIDRef& spreadGeometry = layoutData ? layoutData->GetSpreadRef() : UIDRef::gNull;
		if (spreadGeometry)
		{
			InterfacePtr<IItemContext> spreadContext(spreadGeometry, IID_IITEMCONTEXT);
			if (spreadContext)
				fSnapTo = spreadContext->QuerySnapTo();
			if (fSnapTo)
				fSnapTo->Init(fControlView);
		}
	}

	if (fItemContext)
		fItemContext->Release();

	fItemContext = theContext;
	if (fItemContext)
		fItemContext->AddRef();
}

//----------------------------------------------------------------------------------------
// CTracker::QueryControlView
//----------------------------------------------------------------------------------------

IControlView* CTracker::QueryControlView() const
{
	if (fControlView)
		fControlView->AddRef();

	return fControlView;
}

//----------------------------------------------------------------------------------------
// CTracker::IsEnabled
//----------------------------------------------------------------------------------------

bool16 CTracker::IsEnabled()
{
	return fEnabled;
}

//----------------------------------------------------------------------------------------
// CTracker::IsTracking
//----------------------------------------------------------------------------------------

bool16 CTracker::IsTracking()
{
	return fIsTracking;
}

//----------------------------------------------------------------------------------------
// CTracker::EnableTracking
//----------------------------------------------------------------------------------------

void CTracker::EnableTracking()
{
	if (!IsEnabled())
	{
		this->PushEventHandler();

		IWindow* window = (IWindow*) fControlView->QueryInterface(IID_IWINDOW);
		if (!window)
		{
			InterfacePtr<IWidgetParent> parent(fControlView, IID_IWIDGETPARENT);
			window = (IWindow*) parent->QueryParentFor(IID_IWINDOW);
		}

		InterfacePtr<IWindow> cleanUp(window); // ?? is this still needed?

		(Utils<IEventUtils>())->PMCaptureMouse(this->fControlView);
	}
}

//----------------------------------------------------------------------------------------
// CTracker::DisableTracking
//----------------------------------------------------------------------------------------

void CTracker::DisableTracking()
{
	// Turn off tracking here since this should rarely be overridden.  In any event
	// if the tracker is disabled is certainly is not tracking anymore.

	if (IsEnabled())
	{
		this->PopEventHandler();

		StopTimer(kPatientUserBoss);
		StopTimer(kMouseTrackerBoss);
		StopTimer(kDynamicPauseTimerBoss);

		(Utils<IEventUtils>())->PMReleaseMouse();
	}
}

//----------------------------------------------------------------------------------------
// CTracker::Initialize
//----------------------------------------------------------------------------------------

void CTracker::Initialize(IEvent* theEvent)
{
	fFirstGlobalWhere = theEvent->GlobalWhere();
	this->GlobalToPasteboard(fFirstGlobalWhere, fFirstPoint);

	fPreviousPoint = fFirstPoint;

	if( fSnapType == ISnapTo::kSnapNone )
		(void)AdjustPoint(fPreviousPoint);

	fFirstPoint = fPreviousPoint;
	fFirstTicks = SystemUtils::TickCount();
}

IDataBase* CTracker::GetTrackingDataBase() const
{
		// Start a transaction during tracking so that mini saves don't occur
		// When the layout widget is persistent we should get the data base from that
		// BP 10/16/97: tracker are also used in no pub state (see TabPanel)!
	IDataBase *db = ::GetDataBase(Utils<ILayoutUIUtils>()->GetFrontDocument());
	if(!db && fControlView)
		db = ::GetDataBase(fControlView);
	ASSERT_MSG(db != nil, "CTracker : can't get the database from controlview");
	return db;
}

//----------------------------------------------------------------------------------------
// CTracker::BeginTracking
//----------------------------------------------------------------------------------------
bool16 CTracker::BeginTracking(IEvent* theEvent)
{
#ifdef DIAGNOSTICLOG
	DiagLogHookUtils::DiagLogTrackingHook(this);
#endif
	ASSERT_MSG(theEvent != NULL, "Need an event to begin tracking");
	ASSERT_MSG(fIsTracking == kFalse, "CTracker::BeginTracking(). Already in tracking mode, last BeginTracking not end properly.");

    InterfacePtr<IContextualUIDUsageLogger> contextualUIDLogger(GetExecutionContextSession(), UseDefaultIID());
    if(contextualUIDLogger)
        contextualUIDLogger->EnableLogOnceMode();
    
	this->DisableUpdates();
	this->Initialize(theEvent);

	InitializeModalCursor();

	UpdateModalCursor();	// Update to possibly snapped or unsnapped cursor

	bool16 continueTracking = DoBeginTracking(theEvent);

	if (continueTracking)
	{
		this->EnableTracking(); // May already have been enabled (eg. Place)

		// Patient user timer is tied to a preference, so it may not need to run, but flag should already be set.
		if (WantTimer(kPatientUserBoss))
		{
			int32 patientUserDelay = Utils<Facade::IUserInterfacePreferencesFacade>()->GetUIPatientUserDelay();
			if (patientUserDelay == IPatientUserPreference::kPatientUserWithNoDelay)
				TimerMessage(IShape::kPatientUser);	// Will trigger SetTimerFlags(IShape::kPatientUser)
			else
				StartTimer(kPatientUserBoss, patientUserDelay);
		}

		if (WantTimer(kMouseTrackerBoss))
			StartTimer(kMouseTrackerBoss, 0, GetMouseMoveDelay(), GetMouseSteadyDelay());

		// Dynamic Pause (for text recomposition) user timer is tied to a preference, so it may not need to run, but flag should already be set.
		if (WantTimer(kDynamicPauseTimerBoss))
		{
			int32 patientUserDelay = Utils<Facade::IUserInterfacePreferencesFacade>()->GetUIPatientUserDelay();
			if (patientUserDelay == IPatientUserPreference::kPatientUserWithNoDelay)
				TimerMessage(IShape::kDynamicPause);	// Will trigger SetTimerFlags(IShape::kDynamicPause)
			else
				StartTimer(kDynamicPauseTimerBoss, patientUserDelay);
		}

		fIsTracking = kTrue;
		GetExecutionContextSession()->GetEventConverter()->TrackingMouse(kTrue);

		fDataBase = GetTrackingDataBase();
		fDataBase->BeginTransaction();
	}
	else
		this->EnableUpdates(); // Because EndTracking won't get called.

	return continueTracking;
}

//----------------------------------------------------------------------------------------
// CTracker::DoBeginTracking
//----------------------------------------------------------------------------------------

bool16 CTracker::DoBeginTracking(IEvent* theEvent)
{
	return kTrue;
}

//----------------------------------------------------------------------------------------
// CTracker::HandleContinueTracking
//----------------------------------------------------------------------------------------

void CTracker::HandleContinueTracking(const GSysPoint& where)
{
	ASSERT_MSG(fIsTracking == kTrue, "CTracker::HandleContinueTracking()");
	if (fIsTracking) // Why is this necessary? Is thread running in Place case
					 // because EnableTracking starts the thread?
					 // Enable should just push event handler on stack
					 // BeginTracking should start the tracking thread
	{
		bool16 mouseDidMove = kFalse;
		bool16 willScroll = kFalse;
		PMPoint scrollBy;

		PBPMPoint convertedPoint;
		this->GlobalToPasteboard(where, convertedPoint);
		bool16 isEqualPoint = (convertedPoint == fFirstPoint);

		if (!isEqualPoint && this->WantsToAutoScroll(convertedPoint))
		{
			InterfacePtr<IPanorama> panorama(this->QueryPanorama(fControlView));
			if (panorama != nil)
			{
				scrollBy = panorama->GetAutoScrollDelta(convertedPoint);
				if (scrollBy.X() != 0.0 || scrollBy.Y() != 0.0)
				{
					willScroll = kTrue;
					convertedPoint += scrollBy;
				}
			}
		}

		// A Dynamic Drag operation starts if user doesn't move mouse away from starting
		// point by the minimum drag amount before timer elapses. Hook for patient text composition.
		if ( (GetTimerFlags() & IShape::kDynamicPause) ||
			 abs(SysPointH(fFirstGlobalWhere) - SysPointH(where)) > kMinDragDistance  ||
			 abs(SysPointV(fFirstGlobalWhere) - SysPointV(where)) > kMinDragDistance  )
		{
			StopTimer(kDynamicPauseTimerBoss);
		}

		// A patient user drag operation starts if user doesn't move mouse away from starting
		// point by the minimum drag amount before timer elapses. Hook for live redraw of page items on screen.
		if ( (GetTimerFlags() & IShape::kPatientUser) ||
			 abs(SysPointH(fFirstGlobalWhere) - SysPointH(where)) > kMinDragDistance  ||
			 abs(SysPointV(fFirstGlobalWhere) - SysPointV(where)) > kMinDragDistance  )
		{
			StopTimer(kPatientUserBoss);
		}

		SnapType savedSnap = fSnapType;

		(void)AdjustPoint(convertedPoint);

		if (convertedPoint != fPreviousPoint)
			mouseDidMove = kTrue;

		this->ContinueTracking(convertedPoint, mouseDidMove || willScroll);

		// Some trackers may snap in ContinueTracking (RowCol Table tracker, ILG tracker)
		if (fSnapType != savedSnap)
			UpdateModalCursor();	// Update to possibly snapped or unsnapped cursor

		// $$$ dbessett:  This is pretty messy, but this stops the CTextSelectTracker from crashing when
		// it releases itselef
		if (fIsTracking == kTrue && willScroll)
			this->AutoScroll(scrollBy, convertedPoint);

		fPreviousPoint = convertedPoint;
	}
}

//----------------------------------------------------------------------------------------
// CTracker::ContinueTracking
//----------------------------------------------------------------------------------------

void CTracker::ContinueTracking(const PBPMPoint& where, bool16 mouseDidMove)
{
}

//----------------------------------------------------------------------------------------
// CTracker::DoEndTracking
//----------------------------------------------------------------------------------------
bool16 CTracker::DoEndTracking(IEvent* /*theEvent*/)
{
	return kTrue;
}

//----------------------------------------------------------------------------------------
// CTracker::EndTracking
//----------------------------------------------------------------------------------------

bool16 CTracker::EndTracking(IEvent* theEvent)
{
	// RCR Include DisableTracking here, for symmetry?
#ifdef DIAGNOSTICLOG
	DiagLogHookUtils::DiagLogTrackingHook(this, DiagLogHookUtils::kTrackingEnd);
#endif
	if (fIsTracking)
	{
		DoEndTracking(theEvent);

		StopTimer(kPatientUserBoss);
		StopTimer(kMouseTrackerBoss);
		StopTimer(kDynamicPauseTimerBoss);

		fIsTracking = kFalse;

        InterfacePtr<IContextualUIDUsageLogger> contextualUIDLogger(GetExecutionContextSession(), UseDefaultIID());
        if(contextualUIDLogger)
            contextualUIDLogger->DisableLogOnceMode(); /* on leave end the user patient mode */

		GetExecutionContextSession()->GetEventConverter()->TrackingMouse(kFalse);

		fDataBase->EndTransaction();
		Utils<IPageItemUtils>()->NotifyDocumentObservers(fDataBase, kTrackingCompleteMessage, IID_ITRACKER, nil, nil /* nil cookie */);
		fDataBase = nil;

#ifdef DRAW_COLORIZED_TEXT_HIGHLIGHT
		InterfacePtr<ITextOffscreen> pOff(::QueryTextOffscreen());
		if (pOff && pOff->IsInTypingMode())
			pOff->SetTypingMode(kFalse);
#endif

		// Remove our modal cursor
		ReleaseModalCursor();
	}

	this->EnableUpdates();

	return kTrue;
}

//----------------------------------------------------------------------------------------
// CTracker::AbortTracking
//----------------------------------------------------------------------------------------

void CTracker::AbortTracking(IEvent* theEvent)
{
	// Override this method to provide any special behavior required if the tracker
	// was aborted in the middle of tracking.  For example the PlaceTextTracker needs
	// to abort if a menu is selected after the tracker is enabled
#ifdef DIAGNOSTICLOG
	DiagLogHookUtils::DiagLogTrackingHook(this, DiagLogHookUtils::kTrackingAbort);
#endif
	if (fIsTracking)
	{
		fIsTracking = kFalse;
        InterfacePtr<IContextualUIDUsageLogger> contextualUIDLogger(GetExecutionContextSession(), UseDefaultIID());
        if(contextualUIDLogger)
            contextualUIDLogger->DisableLogOnceMode(); /* on leave end the user patient mode */
        
		GetExecutionContextSession()->GetEventConverter()->TrackingMouse(kFalse);

		fDataBase->EndTransaction();
		Utils<IPageItemUtils>()->NotifyDocumentObservers(fDataBase, kTrackingCompleteMessage, IID_ITRACKER, nil, nil /* nil cookie */);
		fDataBase = nil;

		// Remove our modal cursor
		ReleaseModalCursor();
	}

	this->EnableUpdates();

	this->DisableTracking();
}

//----------------------------------------------------------------------------------------
// CTracker::NotifyBeginTracking
//----------------------------------------------------------------------------------------

void CTracker::NotifyBeginTracking(const PMPoint& startPt, IDynamicTrackerData::TrackingEffect effect)
{
	InterfacePtr<IDynamicTrackerData> dynamicData(this, IID_IDYNAMICTRACKERDATA);
	if (dynamicData)
	{
		if (effect == IDynamicTrackerData::kUnknown)
			effect = GetTrackingEffect(IDynamicTrackerData::kBeginTracking);
		dynamicData->NotifyBeginTracking(startPt, effect);
	}
}

//----------------------------------------------------------------------------------------
// CTracker::NotifyContinueTracking
//----------------------------------------------------------------------------------------

void CTracker::NotifyContinueTracking(const PMPoint& startPoint, const PMPoint& endPoint, IDynamicTrackerData::TrackingEffect effect)
{
	InterfacePtr<IDynamicTrackerData> dynamicData(this, IID_IDYNAMICTRACKERDATA);
	if (dynamicData)
	{
		if (effect == IDynamicTrackerData::kUnknown)
			effect = GetTrackingEffect(IDynamicTrackerData::kContinueTracking);
		dynamicData->NotifyContinueTracking(startPoint, endPoint, effect);
	}
}

//----------------------------------------------------------------------------------------
// CTracker::NotifyEndTracking
//----------------------------------------------------------------------------------------

void CTracker::NotifyEndTracking(const PMPoint& startPoint, const PMPoint& endPoint, IDynamicTrackerData::TrackingEffect effect)
{
	InterfacePtr<IDynamicTrackerData> dynamicData(this, IID_IDYNAMICTRACKERDATA);
	if (dynamicData)
	{
		if (effect == IDynamicTrackerData::kUnknown)
			effect = GetTrackingEffect(IDynamicTrackerData::kEndTracking);
		dynamicData->NotifyEndTracking(startPoint, endPoint, effect);
	}
}

//----------------------------------------------------------------------------------------
// CTracker::GetTrackingEffect
//----------------------------------------------------------------------------------------

IDynamicTrackerData::TrackingEffect CTracker::GetTrackingEffect(IDynamicTrackerData::TrackingState state)
{
	if (state == IDynamicTrackerData::kBeginTracking ||
		state == IDynamicTrackerData::kContinueTracking ||
		state == IDynamicTrackerData::kEndTracking ||
		state == IDynamicTrackerData::kAbortTracking)
		return IDynamicTrackerData::kAffectsXYWH;
	else if (state == IDynamicTrackerData::kNotTracking)
		return IDynamicTrackerData::kAffectsNone;

	ASSERT_FAIL("CTracker::GetTrackingEffect, unknown tracking state");
	return IDynamicTrackerData::kAffectsXY;
}

//----------------------------------------------------------------------------------------
// CTracker::PushEventHandler
//----------------------------------------------------------------------------------------
static void trace_me( const char* funcStr, IPMUnknown* that)
{
#if DEBUG && MACINTOSH
	DebugClassUtilsBuffer buf;
	static int counter = 0;
	TRACEFLOW("Tracker", "%d\t%s--%s\n", ++counter, funcStr, DebugClassUtils::GetIDName(&buf,::GetClass(that)));

	const int skip_frames = 5, show_frames = 6;
	StackCrawler::TraceStackCrawl("Tracker", "TrackerStack", skip_frames, skip_frames + show_frames);

#if 0
	const int skip_frames = 4, show_frames = 6;
	int i;
	char* frameNames[show_frames + 1];
	for( i = 0; i <= show_frames; ++i) frameNames[i] = 0;
	StackCrawler::RecordStackCrawl( frameNames, skip_frames, skip_frames + show_frames);
	for( i = 0; frameNames[i]; ++i){
		char cString[4096];
		char *p = cString;
		for( int j = 2; j <= frameNames[i][0]; ++j) *p++ = frameNames[i][j];
		*p = 0;
		TRACEFLOW_OBSOLETE("TrackerStack", "\t%*s%s\n", 2*(i+1), "", cString);
	}
#endif
#endif
}

void CTracker::PushEventHandler()
{
	trace_me( "CTracker::PushEventHandler" , this);
	InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IEventDispatcher> dispatcher(theApp, UseDefaultIID());
	InterfacePtr<IEventHandler> eventHandler(this, UseDefaultIID());
	dispatcher->Push(eventHandler);
	fEnabled = kTrue;

#ifdef DEBUG
	fMyEventHandler = eventHandler.get();
#endif
}

//----------------------------------------------------------------------------------------
// CTracker::PopEventHandler
//----------------------------------------------------------------------------------------

void CTracker::PopEventHandler()
{
	trace_me( "CTracker::PopEventHandler" , this);
	InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IEventDispatcher> dispatcher(theApp, UseDefaultIID());
	InterfacePtr<IEventHandler> eventHandler(this, UseDefaultIID());
	dispatcher->Remove(eventHandler);
	fEnabled = kFalse;

#ifdef DEBUG
	fMyEventHandler = nil;
#endif

}

//----------------------------------------------------------------------------------------
// CTracker::WantsToAutoScroll
//----------------------------------------------------------------------------------------

bool16 CTracker::WantsToAutoScroll(const PMPoint& currentPoint)
{
	return fWantsToAutoScroll;
}

//----------------------------------------------------------------------------------------
// CTracker::AutoScroll
//----------------------------------------------------------------------------------------

PMPoint CTracker::AutoScroll(const PMPoint& scrollBy, const PMPoint& scrolledPoint)
{
	InterfacePtr<IPanorama> panorama( this->QueryPanorama( fControlView ) );
	PMPoint scrolledAmount = panorama->ScrollBy(scrollBy, kTrue);
	return scrolledAmount;
}

//----------------------------------------------------------------------------------------
// CTracker::GlobalToPasteboard
//----------------------------------------------------------------------------------------

void CTracker::GlobalToPasteboard(const GSysPoint& thePoint, PBPMPoint& convertedPoint)
{
	convertedPoint = Utils<ILayoutUIUtils>()->ComputePasteboardPoint (thePoint, fControlView);
}

//----------------------------------------------------------------------------------------
// CTracker::PasteboardToGlobal
//----------------------------------------------------------------------------------------

PMPoint CTracker::PasteboardToGlobal(const PBPMPoint& pbPoint)
{
	ASSERT(fControlView != nil);
	PMPoint localPoint(pbPoint);

	if (fControlView)
	{
		fControlView->ContentToWindowTransform(&localPoint);
		return fControlView->WindowToGlobal (localPoint);
	}

	return localPoint;
}


//----------------------------------------------------------------------------------------
// CTracker::QueryPanorama
//----------------------------------------------------------------------------------------

// BP 1/16/97:	The pageitem widgets don't have panoramas because they are children
//				of the LayoutWidget. In those cases we want to autoscroll the
//				LayoutWidget's panorama.
//				See #1028	Screen does not scroll when trying to select text.

IPanorama *CTracker::QueryPanorama( IControlView *pView ) const
{
	IPanorama *pPanorama = (IPanorama*)pView->QueryInterface( IID_IPANORAMA );
	if( pPanorama )
		return pPanorama;

	InterfacePtr<IWidgetParent> pParent( pView, IID_IWIDGETPARENT );
	if( !pParent )
		return 0;

	pPanorama = (IPanorama*)pParent->QueryParentFor( IID_IPANORAMA );
	return pPanorama;
}

//----------------------------------------------------------------------------------------
// CTracker::DisableUpdates
//----------------------------------------------------------------------------------------

void CTracker::DisableUpdates()
{
	Utils<ILayoutUIUtils>()->DisableUpdateAllDocumentViews();
}

//----------------------------------------------------------------------------------------
// CTracker::EnableUpdates
//----------------------------------------------------------------------------------------

void CTracker::EnableUpdates()
{
	Utils<ILayoutUIUtils>()->EnableUpdateAllDocumentViews();
	InterfacePtr<ILayoutController> iLayoutController(fControlView, UseDefaultIID());
	if(iLayoutController)
		iLayoutController->InvalidateSelection((SysRgn)nil);
}

//----------------------------------------------------------------------------------------
// CTracker::InitializeModalCursor
//----------------------------------------------------------------------------------------

void CTracker::InitializeModalCursor()
{
	// Turn off busy cursor support in command processor so trackers can control cursor themselves.
	fAutoBusyCursor = new AutoBusyCursor(kFalse);

	InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<ICursorMgr> cursorMgr(theApp, UseDefaultIID());
	fModalCursor = new AcquireModalCursor(cursorMgr->GetCursorSpec());
}

//----------------------------------------------------------------------------------------
// CTracker::ChangeModalCursor
//----------------------------------------------------------------------------------------

void CTracker::ChangeModalCursor(const CursorSpec& spec)
{
	ASSERT_MSG(fModalCursor!=nil, "CTracker::ChangeModalCursor: modal cursor not acquired. Called inherited BeginTracking yet?\n");

	if (fModalCursor)
	{
		if ( !spec.GetCustomBitmapCreationProc() )
		{
			CursorSpec adjustedCursorSpec(spec);

			Utils<ICursorUtils>()->UpdateCursor(adjustedCursorSpec);			

			fModalCursor->ChangeCursor(adjustedCursorSpec);
		}
		else
			fModalCursor->ChangeCursor(spec);
	}
}

//----------------------------------------------------------------------------------------
// CTracker::UpdateModalCursor
//----------------------------------------------------------------------------------------

void CTracker::UpdateModalCursor()
{
 	// Possibly adjust cursor for snap to
 	InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
 	InterfacePtr<ICursorMgr> cursorMgr(theApp, UseDefaultIID());
	CursorSpec currentSpec = cursorMgr->GetCursorSpec();
 	CursorSpec newCursorSpec = cursorMgr->GetSnapToCursorSpec(currentSpec, fSnapType);

	this->ChangeModalCursor(newCursorSpec);
}

//----------------------------------------------------------------------------------------
// CTracker::ReleaseModalCursor
//----------------------------------------------------------------------------------------

void CTracker::ReleaseModalCursor()
{
	if (fModalCursor)
	{
		delete fModalCursor;
		fModalCursor= nil;
	}

	Utils<ICursorUtils>()->ReleaseCursor();			

	// Restore busy cursor support in command processor.
	if (fAutoBusyCursor)
	{
		delete fAutoBusyCursor;
		fAutoBusyCursor = nil;
	}
}

//----------------------------------------------------------------------------------------
// ::DeactivatePageItem
//----------------------------------------------------------------------------------------

// BP 6/23/96: bug #147, we have to deactivate the PageItem widget

void CTracker::DeactivatePageItem()
{
	InterfacePtr<IApplication> theApp( GetExecutionContextSession()->QueryApplication() ) ;
	InterfacePtr<IKeyBoard> keyBoard( theApp, IID_IKEYBOARD ) ;

	IEventHandler* pHandler = keyBoard->GetKeyFocus() ;
	if( pHandler )
	{
		InterfacePtr<IPageItemFocus> pFocus( pHandler, IID_IPAGEITEMFOCUS ) ;
		if( pFocus )
			pFocus->RevokePageItemFocus() ;
	}
}



void CTracker::DeselectAllItems()
{
	InterfacePtr<ISelectionManager> selectionMgr( Utils<ISelectionUtils>()->QueryViewSelectionManager(fControlView));

	selectionMgr->DeselectAll (nil);
}

void CTracker::ComputeAdjustedPoint (PMPoint& adjustedPoint)
{
	if ( fHorzRuler && fVertRuler && fControlView )
	{
		// If items were not snapped to an exact coordinate, ruler adjust them. If just x was snapped, ruler adjust only in y direction and vice versa.
		adjustedPoint = Utils<ILayoutUIUtils>()->ComputeRulerAdjustedPoint (adjustedPoint, (fSnapType & ISnapTo::kSnapX) ? nil : fHorzRuler, (fSnapType & ISnapTo::kSnapY) ? nil :  fVertRuler, fControlView->GetContentToWindowMatrix());
	}
}

bool16 CTracker::AdjustPoint(PBPMPoint& point)
{
	PMPoint	save_point(point);

	if (fSnapTo && fSnapTo->GetSnappingEnabled())
	{
		fSnapType = fSnapTo->DoSnapTo(fControlView, point, nil /* theRect */, fSnapTo->GetSnapType());
	}

	ComputeAdjustedPoint(point);

	return (point != save_point);
}

bool16 CTracker::WantTimer(ClassID trackerTimerBoss)
{
	if (trackerTimerBoss == kMouseTrackerBoss)
		return kTrue;
	
	return kFalse;
}

void CTracker::StartTimer(ClassID trackerTimerBoss, uint32 delay, uint32 mouseMoveDelay, uint32 mouseSteadyDelay)
{
	if (delay != IIdleTask::kEndOfTime)
	{
		ITrackerTimer* timer = (ITrackerTimer*)::CreateObject(trackerTimerBoss, IID_ITRACKERTIMER);
		if (timer)
		{
			timer->StartTimer(this, delay, mouseMoveDelay, mouseSteadyDelay);
			fTimerPtrs.push_back(timer);	// Already AddRef'ed
		}
	}
}

void CTracker::StopTimer(ClassID trackerTimerBoss)
{
	for (int32 i = 0; i < fTimerPtrs.size(); i++)
	{
		ITrackerTimer* ithTimer = fTimerPtrs[i];
		if (ithTimer && ::GetClass(ithTimer) == trackerTimerBoss)
		{
			ithTimer->StopTimer();
			ithTimer->Release();
			fTimerPtrs.erase(fTimerPtrs.begin() + i);
			break;
		}
	}
}

