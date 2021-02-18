//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/trackers/CPathCreationTracker.cpp $
//  
//  Owner: Jeff Argast
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

// ----- Interfaces -----

#include "IApplication.h"
#include "IBoolData.h"
#include "IBoundsData.h"
#include "ICmdCollection.h"
#include "ICJKGridPrefs.h"
#include "IColumns.h"
#include "ICommandSequence.h"
#include "IControlView.h"
#include "ICursorMgr.h"
#include "ICursorUtils.h"
#include "IDocument.h"
#include "IDynamicTrackerData.h"
#include "IDynamicTransformData.h"
#include "IGeometry.h"
#include "IGraphicFrameData.h"
#include "IGuidePreferencesFacade.h"
#include "IHierarchy.h"
#include "IHierarchyCmdData.h"
#include "IIntData.h"
#include "IItemContext.h"
#include "ILayoutCmdData.h"
#include "ILayoutControlData.h"
#include "ILayoutControlViewHelper.h"
#include "ILayoutSelectionSuite.h"
#include "ILayoutUtils.h"
#include "IModifyPathPointsCmdData.h"
#include "INewPageItemCmdData.h"
#include "IPlaceGun.h"
#include "IPMMatrixListData.h"
#include "IPathGeometry.h"
#include "ISelectionManager.h"
#include "ISession.h"
#include "ISetBoundingBoxCmdData.h"
#include "ISmartDimensions.h"
#include "ISnapTo.h"
#include "ISnapToPrefs.h"
#include "ISpread.h"
#include "ISprite.h"
#include "ISubject.h"
#include "IMultiColumnTextFrame.h"
#include "ITextModel.h"
#include "ITransform.h"
#include "IUIDData.h"
#include "ITransformPanelPrefs.h"
#include "IBoundsData.h"
#include "ITransformFacade.h"
#include "ITransformCmdData.h"
#include "IUnitOfMeasureSettings.h"
#include "IPMPointData.h"
#include "IPMRectData.h"
#include "IIntData.h"
#include "IPersistUIDData.h"
#include "IGfxLayoutAttributeOptions.h"

// ----- Includes -----

#include "AGMGraphicsContext.h"
#include "CPathCreationTracker.h"
#include "HitTestDragConstants.h"
#include "keyboarddefs.h"
#include "LocaleSetting.h"
#include "PMPathPoint.h"
#include "StackPageItemSessionDataResetter.h"

// ----- Utility files -----

#include "CmdUtils.h"
#include "ErrorUtils.h"
#include "EventUtilities.h"
#include "KeyStates.h"
#include "ISelectionUtils.h"
#include "ILayoutUIUtils.h"
#include "IPageItemUtils.h"
#include "IPathUtils.h"
#include "IPasteboardUtils.h"
#include "PreferenceUtils.h"
#include "TransformUtils.h"
#include "TransformUtilsPrivate.h"
#include "IGeometryFacade.h"
#include "IUIFeedbackUtils.h"
#include "ITouchWSUtils.h"
#include "ILayoutAttrsHelperUtils.h"
// ----- ID.h files -----

#include "PageItemScrapID.h"
#include "RectID.h"
#include "SplineID.h"
#include "SpreadID.h"
#include "GenericID.h"

#ifdef DEBUG
#include "GuideID.h"	// for kGuideCreationTrackerBoss
#endif

static void ClearChangedState(const UIDRef& newItem);

#if DEBUG && MACINTOSH
#	include "DebugClassUtils.h"
#endif


#ifdef DEBUG
extern PUBLIC_DECL UID ts_SmartLayoutItemUID;
#endif

#if DEBUG
static void NaNCheck( PMReal x)
{
	double x_ = ::ToDouble( x); //uninitialized check
	ASSERT( x_ <= 0. || x_ > 0.);//NaN check
}
#endif

//========================================================================================
// CLASS CPathCreationTracker
//========================================================================================
PMReal CPathCreationTracker::fHSpacing = 9.0;
PMReal CPathCreationTracker::fVSpacing = 9.0;

//----------------------------------------------------------------------------------------
// CPathCreationTracker constructor 
//----------------------------------------------------------------------------------------

CPathCreationTracker::CPathCreationTracker(IPMUnknown *boss) :
	CTracker(boss),
	fClassID(IID_IUNKNOWN),
	fStartPnt(),
	fPasteBoardBoundaries(),
	fPasteBoardBoundsSpreadCoordinates(),
  	fShiftKeyPressed(kFalse),
	fOptionAltKeyPressed(kFalse),
	fCmdCtrlKeyPressed(kFalse),
	fCreatingFromCenter(kFalse),
	fSpreadToPasteboardMatrix(),
	fPasteboardToSpreadMatrix(),
	fTransformMatrix(),
	fBackTransformMatrix(),
	fTrackerSequence(nil),
	fRows(1),
	fColumns(1),
	fCreateMultiple(false),
	fGraphicBBox(kZeroRect),
	fShownFirstTime(kFalse)
{
}

//----------------------------------------------------------------------------------------
// CPathCreationTracker destructor 
//----------------------------------------------------------------------------------------

CPathCreationTracker::~CPathCreationTracker()
{
	Utils<ICursorUtils>()->ReleaseCursor();			
}

//----------------------------------------------------------------------------------------
// CPathCreationTracker SetUpParentTransforms 
//----------------------------------------------------------------------------------------
void CPathCreationTracker::SetUpParentTransforms(PMPoint *endPoint)
{
	UIDRef parentRef = GetParent();

	InterfacePtr<ITransform> parentTransform(parentRef, IID_ITRANSFORM);
	if (parentTransform)
	{
		fTransformMatrix = ::InnerToPasteboardMatrix(parentTransform);
		fBackTransformMatrix = fTransformMatrix.Inverse();
		fBackTransformMatrix.Transform(&fStartPnt);
		fBackTransformMatrix.Transform(endPoint);
	}
}

//----------------------------------------------------------------------------------------
// CPathCreationTracker::BeginTracking 
//----------------------------------------------------------------------------------------

#include "IRulerData.h"
#include "IEvent.h"

bool16 CPathCreationTracker::BeginTracking(IEvent* theEvent)
{	
	ASSERT_MSG(theEvent != nil, "Need an event to begin tracking");
	ASSERT_MSG(!fIsTracking, "CPathCreationTracker::BeginTracking called twice");

	// Initialize custom cursor
	CursorOptions option = GetCursorOption();
	if (DrawingCursorFeedback() && option != kDefaultCursor)
		Utils<ICursorUtils>()->InitCursor((ICursorUtils::CursorOptions)option);
	else
	{
		InterfacePtr<IIntData> cursorOptionData(this, UseDefaultIID());	//Used by sprite to draw feedback
		if(cursorOptionData)
			cursorOptionData->Set((ICursorUtils::CursorOptions)option);
	}
			

	fCreateMultiple = false;

	// mouseDragged specifies if mouse has been dragged. It is used to catch single mouse click.
	// We use an interface instead of a member data in order to keep backward compatibility in Sherpa.
	InterfacePtr<IBoolData> mouseDragged(this, IID_IMOUSEDRAGGED);
	if (mouseDragged != nil)
	{
		mouseDragged->Set(kFalse);
	}

	// Creation trackers want snapping at all times, so just enable it
	// in the constructor and CTracker will take care it it. Creation
	// trackers support snapping to all page marks.
	if (fSnapTo)
	{
		fSnapTo->SetSnappingEnabled(kTrue);
		fSnapTo->SetSnapFlags(fControlView, ISnapTo::kSnapAllPageMarks);
	}

	if (!CTracker::BeginTracking(theEvent))
		return kFalse;

	ASSERT_MSG(!fTrackerSequence, "fTrackerSequence must be nil");
	fTrackerSequence = CMDUTILS_BEGINABORTABLECMDSEQ(__FILE__,__LINE__);	

	if (DrawingCursorFeedback() || option == kDefaultCursor)
		this->ChangeModalCursor(CursorSpec(fSnapType == ISnapTo::kSnapNone ? kCrsrItemCreation : kCrsrItemCreationSnap));
	else
	{
		PMPoint mouseMotion(theEvent->GlobalWhere());
		InterfacePtr<IPMPointData> offset(this, UseDefaultIID());
		offset->Set(mouseMotion);
	}
	
	// BP 6/23/96: bug #147, we have to deactivate the PageItem widget  [jwbrown 10/2/09 bug #147?!]
	DeactivatePageItem() ;

	//Hold a reference to myself so I can't be destructed unexpectedly (#2440545)
	{
		AddRef() ;
		DeselectAllItems() ;

		if ( !IsTracking() ) //#2440545
		{
			if ( fTrackerSequence )
				CmdUtils::AbortCommandSequence(fTrackerSequence);
			fTrackerSequence = nil;
			return kFalse; //caller will release ref (in IBeamTracker::BeginTracking())
		}
		Release() ;
	}

	// Set the current spread to be the one we're working on
	InterfacePtr<ILayoutControlData> layoutData(fControlView, IID_ILAYOUTCONTROLDATA);
	InterfacePtr<ISpread> spread(Utils<IPasteboardUtils>()->QuerySpread(fControlView, fFirstPoint));
	if (spread && ::GetUIDRef(spread) != layoutData->GetSpreadRef())
	{
		InterfacePtr<ICommand> setSpreadCmd(CmdUtils::CreateCommand(kSetSpreadCmdBoss));
		InterfacePtr<ILayoutCmdData> setSpreadLayoutCmdData(setSpreadCmd, IID_ILAYOUTCMDDATA);
		setSpreadLayoutCmdData->Set(::GetUIDRef(layoutData->GetDocument()), layoutData);
	
		setSpreadCmd->SetItemList(UIDList(::GetDataBase(layoutData->GetDocument()), ::GetUID(spread)));
	
		CmdUtils::ProcessCommand(setSpreadCmd);
		
		// Since we are changing spreads, recalculate the starting point
		fSnapType = ISnapTo::kSnapNone; 
		this->Initialize(theEvent);
	}

	// Save the paste board boundaries inset it a little
	InterfacePtr<ITransform> spreadTransform( layoutData->GetSpreadRef(), UseDefaultIID());
	fSpreadToPasteboardMatrix = spreadTransform->GetInnerToParentMatrix();
	fPasteboardToSpreadMatrix = spreadTransform->GetParentToInnerMatrix();

	fPasteBoardBoundaries = Utils<Facade::IGeometryFacade>()->GetItemBounds( GetUIDRef(spreadTransform), Transform::PasteboardCoordinates(), Geometry::OuterStrokeBounds());
	fPasteBoardBoundsSpreadCoordinates = Utils<Facade::IGeometryFacade>()->GetItemBounds( GetUIDRef(spreadTransform), Transform::SpreadCoordinates(), Geometry::OuterStrokeBounds());
	PMReal insetAmount(6.0);
	fPasteBoardBoundaries.Inset(insetAmount, insetAmount);
	fPasteBoardBoundsSpreadCoordinates.Inset(insetAmount, insetAmount);
	
	// Do all calculations in Pasteboard coordinates. Use fPreviousPoint since
	// it has already been snapped by the CTracker::BeginTracking code.
	PMPoint endPoint;
	fStartPnt = fFirstPoint; //fFirstPoint is in pasteboard coordinates
	// fStartPnt is used in ConvertToPasteboardContrained(), 
	//   use ConstrainTo() to constrain fStartPnt.
	// We don't constrain fFirstPoint. Otherwise when space bar is pressed and
	//   the page item is constrained to pasterboard boundary, we will not be
	//   able to know the original size of the item.
	fPasteboardToSpreadMatrix.Transform( &fStartPnt); //fStartPnt now in spread coordinates
	fStartPnt.ConstrainTo( fPasteBoardBoundsSpreadCoordinates);
	fSpreadToPasteboardMatrix.Transform( &fStartPnt); //fStartPnt now in pasteboard coordinates

	GSysPoint m2 = theEvent->GlobalWhere();
	
	// need to initialize fStartGlobalPt before calling ConvertToPasteboardConstrained. Otherwise, MovedMinimumDistance will always succeed and 
	// smart guide snapping will occur prematurely. See bug #2304103: "When an image is placed in attached document, graphics frame drawn for
	// placed image is of very small size."
	// Question: Why is there an fStartGlobalPt when CTracker, the parent class, already has an fFirstGlobalWhere
	fStartGlobalPt = PasteboardToGlobal (fStartPnt);
	
	//careful ConvertToPasteboardConstrained is a virtual call perhaps to derived class implementation EraseTracker.cpp, FrameTracker.cpp, GuideCreationTracker.cpp, PencilCreationTracker.cpp, PlacePITracker.cpp, SmoothTracker.cpp
	this->ConvertToPasteboardConstrained( m2, endPoint);  //clobbers fStartPnt with constrained fFirstPoint in pasteboard coordinates
	//as of now  endPoint is in PB coordinates

	fStartGlobalPt = PasteboardToGlobal (fStartPnt);
	
	// In case our parent isn't a layer (it could be a Smart Layout Object from Woodwing),
	// make sure we transform ourselves according to the parent's transform
	SetUpParentTransforms(&endPoint);		// startpoint handled via fStartPnt
	//as of now fStartPnt and endPoint are in spread coordinates -- seems to be fighting with ConvertToPasteboardConstrained

    Utils<ILayoutUtils> iLayoutUtils; 
	if ( iLayoutUtils && spread)
	{
        int32    pageIndex; 
        InterfacePtr<IGeometry> pageGeo(spread->QueryNearestPage(fStartPnt, &pageIndex)); 
		InterfacePtr<IColumns> iColumns(iLayoutUtils->Query_Columns(pageIndex, spread));
		if ( iColumns /* && iColumns->GetNumberColumns(kTrue) >  */)
		{
			PMReal gutter = iColumns->GetGutter_();
			
			fVSpacing = fHSpacing = gutter;
		}
	}

    InterfacePtr<IDynamicTrackerData> dynamicData(this, IID_IDYNAMICTRACKERDATA); 
    if (dynamicData) 
	{
		dynamicData->SetRows(fRows);
		dynamicData->SetColumns(fColumns);
		dynamicData->SetGridBounds(fGraphicBBox);
		dynamicData->SetInsets(0.0, 0.0, 0.0, 0.0);
		dynamicData->SetHorizontalSpacing(fHSpacing);
		dynamicData->SetVerticalSpacing(fVSpacing);
		dynamicData->EnableGridMode(fCreateMultiple);
	}

	NonMarkingAGMGraphicsContext gc(fControlView);
	InterfacePtr<ISprite> sprite(this, IID_ISPRITE);
	sprite->CreateSprite(&gc, nil, PMPoint(), kFalse /* don't draw item list */);

	InterfacePtr<IPathGeometry> spritePathGeom(this, IID_IPATHGEOMETRY);
#if SPREAD_ALIGNED_CREATION
	this->MakePath( fStartPnt, endPoint, spritePathGeom);//the path is created in spread coordinates
	spritePathGeom->TransformPath( fTransformMatrix); //now the path is transformed to pb coordinates
#else
	PMPoint p1 = fStartPnt, p2 = endPoint;
	fTransformMatrix.Transform( &p1);
	fTransformMatrix.Transform( &p2);
	this->MakePath( p1, p2, spritePathGeom);
#endif

	PMPoint mousePBPos = Utils<ILayoutUIUtils>()->GetMousePasteboardPosition(::GetGlobalMouseLocation(), fControlView);
	this->NotifyBeginTracking(mousePBPos);
	
	// It is possible to get a mouse down, drag, mouse up before we ever get here.
	// Therefore, don't show the sprite here.
	// sprite->Show(&gc, fStartPnt, IShape::kDrawCreateDynamic);
	fShownFirstTime = kFalse;

	//manage to leave CPathCreationTracker::BeginTracking with fStartPnt in parent coordinates
	return kTrue;
}

//----------------------------------------------------------------------------------------
// CPathCreationTracker::ContinueTracking 
//----------------------------------------------------------------------------------------

void CPathCreationTracker::ContinueTracking(const PBPMPoint& where, bool16 mouseDidMove)
{
	//at this point fStartPnt is in parent coordinates where BeginTracking left it (or I left it)

	bool16 bNewMouseDidMove = mouseDidMove;
	bool16 bIsCmdKeyPressed = ::IsCommandKeyPressed();

	VirtualKey theKey = kVirtualNullKey;
	InterfacePtr<IIntData> trackerKeyData(this, IID_ITRACKERKEYDATA);
	if (trackerKeyData)
		theKey = VirtualKey((uint32)trackerKeyData->Get());

	// Allow user modification of number of rows or columns via keyboard modifiers while tracking
	if (theKey != kVirtualNullKey)
	{
		bool bUp = (theKey == kVirtualUpArrowKey);
		bool bDown = (theKey == kVirtualDownArrowKey);
		bool bLeft = (theKey == kVirtualLeftArrowKey);
		bool bRight = (theKey == kVirtualRightArrowKey);
		bool bPageUp = (theKey == kVirtualPageUpKey);
		bool bPageDown = (theKey == kVirtualPageDownKey);

		if ( bUp || bDown || bLeft || bRight || bPageUp || bPageDown )
		{
			bNewMouseDidMove = kTrue;

			PMReal gapIncrement(1.0);
			if ( bPageDown || bPageUp || bIsCmdKeyPressed )
			{
				InterfacePtr<IUnitOfMeasureSettings> iMeasurePrefs( 
                    (IUnitOfMeasureSettings*)::QueryPreferences(IID_IUNITOFMEASURESETTINGS, GetExecutionContextSession()->GetActiveContext())); 
				gapIncrement = iMeasurePrefs->GetKeyNudgeInc();
				if ( gapIncrement < 0.0 )
					gapIncrement = 0;
			}

			if ( bPageDown )
			{
				if ( fHSpacing > 0 )
					fHSpacing -= gapIncrement;
				if ( fVSpacing > 0 )
					fVSpacing -= gapIncrement;
			}
			else if ( bPageUp )
			{
				if ( fHSpacing > 0 )
					fHSpacing += gapIncrement;
				if ( fVSpacing > 0 )
					fVSpacing += gapIncrement;
			}

			if ( bDown )
			{
				if ( bIsCmdKeyPressed )
					fVSpacing -= gapIncrement;
				else if ( fRows > 1 )
					fRows--;
			}

			if ( bUp )
			{
				if ( bIsCmdKeyPressed )
					fVSpacing += gapIncrement;
				else
					fRows++;
			}

			if ( bLeft )
			{
				if ( bIsCmdKeyPressed )
					fHSpacing -= gapIncrement;
				else if ( fColumns > 1 )
					fColumns--;
			}

			if (bRight)
			{
				if ( bIsCmdKeyPressed )
					fHSpacing += gapIncrement;
				else
					++fColumns;
			}

			if ( fHSpacing < 0.0 )
				fHSpacing = 0.0;
			if ( fVSpacing < 0.0 )
				fVSpacing = 0.0;
		}

		if ( bNewMouseDidMove )
		{
			InterfacePtr<IDynamicTrackerData> dynamicData(this, IID_IDYNAMICTRACKERDATA); 
			if (dynamicData) 
			{
				dynamicData->SetRows(fRows);
				dynamicData->SetColumns(fColumns);
				dynamicData->SetGridBounds(fGraphicBBox);
				dynamicData->SetHorizontalSpacing(fHSpacing);
				dynamicData->SetVerticalSpacing(fVSpacing);
				fCreateMultiple = (fRows > 1 || fColumns > 1);
				dynamicData->EnableGridMode(fCreateMultiple);
			}

			// Clear key state since we handled it
			trackerKeyData->Set(kVirtualNullKey.GetDVKeyCode());
		}
	}

	if ( bNewMouseDidMove )
	{
		InterfacePtr<IBoolData> mouseDragged(this, IID_IMOUSEDRAGGED);
		if ( mouseDragged )
			mouseDragged->Set(true);
	}

	if ( bNewMouseDidMove
		|| ((mouseDidMove || ::IsShiftKeyPressed() != fShiftKeyPressed || ::IsOptionAltKeyPressed() != fOptionAltKeyPressed
		|| 	fCmdCtrlKeyPressed != bIsCmdKeyPressed)
		&& MovedMinimumDistance(where)) )
	{
		PMPoint endPoint(where);
		
		this->ConvertToPasteboardConstrained (where, endPoint);  //clobbers fStartPnt with constrained fFirstPoint in pasteboard coordinates
#if DEBUG
		NaNCheck( endPoint.X());
		NaNCheck( endPoint.Y());
#endif

		if ( fCreateMultiple )
		{
			InterfacePtr<IDynamicTrackerData> dynamicData(this, IID_IDYNAMICTRACKERDATA); 
			if (dynamicData) 
				dynamicData->SetGridBounds(fGraphicBBox);
		}
		
		//at this point fStartPnt is in pasteboard coordinates where ConvertToPasteboardConstrained left it.
		this->HandleMove (endPoint);
		//at this point fStartPnt is in parent coordinates where HandleMove left it.		

		CursorOptions option = GetCursorOption();
		if (DrawingCursorFeedback() || option == kDefaultCursor)
			this->ChangeModalCursor(CursorSpec(fSnapType == ISnapTo::kSnapNone ? kCrsrItemCreation : kCrsrItemCreationSnap));
		else
		{
			PMMatrix pbtoview = fControlView->GetContentToWindowMatrix();
			PMPoint mouseMotion(where);
			pbtoview.Transform(&mouseMotion);

			InterfacePtr<IPMPointData> offset(this, UseDefaultIID());
			offset->Set(mouseMotion);
		}

		fCmdCtrlKeyPressed = bIsCmdKeyPressed;
	}
	//at this point fStartPnt is in parent coordinates -- what a mess
}

//----------------------------------------------------------------------------------------
// CPathCreationTracker::EndTracking
//----------------------------------------------------------------------------------------

bool16 CPathCreationTracker::EndTracking(IEvent* theEvent)
{	
	ASSERT_MSG(theEvent != nil, "Event is nil in CPathCreationTracker::EndTracking");

	bool16 result = CTracker::EndTracking(theEvent);

    StackPageItemSessionDataResetter stresetter(IObjStyleOverrideActionData::kCreatePageItem);
	CompletelyCreateItem(theEvent);
	CleanupTracking();

	if (fTrackerSequence)
		CmdUtils::EndCommandSequence(fTrackerSequence);
	fTrackerSequence = nil;
	return result;
}

//----------------------------------------------------------------------------------------
// CPathCreationTracker::AbortTracking
//----------------------------------------------------------------------------------------

void CPathCreationTracker::AbortTracking(IEvent* theEvent)
{
	CleanupTracking();
		
	if (fTrackerSequence)
		CmdUtils::AbortCommandSequence(fTrackerSequence);
	fTrackerSequence = nil;
	CTracker::AbortTracking(theEvent);
}

//----------------------------------------------------------------------------------------
// CPathCreationTracker::ProcessAddToSelectionCommand
//----------------------------------------------------------------------------------------

void CPathCreationTracker::ProcessAddToSelectionCommand(IControlView *view, const UIDRef& newItem)
{
    // Create a command to select the page item.
    InterfacePtr<ISelectionManager> iSelectionManager(Utils<ISelectionUtils>()->QueryViewSelectionManager(view));
    InterfacePtr<ILayoutSelectionSuite>    iLayoutSelectionSuite (Utils<ISelectionUtils>()->QueryLayoutSelectionSuite (iSelectionManager));
	
    // Prevent multiple enabled CSBs
    K2Vector<ClassID>       csbKeepList;
    csbKeepList.push_back (kNewLayoutSelectionBoss);
    iSelectionManager->DeselectAllExcept(&csbKeepList);

	iLayoutSelectionSuite->SelectPageItems ( UIDList(newItem), Selection::kAddTo, Selection::kDontScrollLayoutSelection);
}

//----------------------------------------------------------------------------------------
// CPathCreationTracker::CompletelyCreateItem
//----------------------------------------------------------------------------------------

void CPathCreationTracker::CompletelyCreateItem(IEvent* theEvent)
{
	PBPMPoint endPoint(fPreviousPoint);

	InterfacePtr<IBoolData> mouseDragged(this, IID_IMOUSEDRAGGED);
	if (!mouseDragged || mouseDragged->GetBool())
	{
		this->ConvertToPasteboardConstrained(fPreviousPoint, endPoint);  //clobbers fStartPnt with constrained fFirstPoint in pasteboard coordinates

		this->NotifyEndTracking(fStartPnt, endPoint);
	}
	
	PMPointList points;
	bool bUseDragRect = false;
	
	// If we didn't move the minimum distance, then make both points equal
	// MovedMinimumDistance deals with screen coordinates, whereas SufficientSize
	// works completely in pasteboard space.  
 	if ( !MovedMinimumDistance (endPoint) ) {
		points.push_back(fStartPnt);
		points.push_back(fStartPnt);
	} else {
		bUseDragRect = true;
		points.push_back(fStartPnt);
		points.push_back(endPoint);
	}

	if (SufficientSize(points))
	{
	
		ASSERT_MSG(Utils<ILayoutUIUtils>()->GetFrontDocument() != nil, "CPathCreationTracker::CompletelyCreateItem on nil front document!");
	
		UIDRef parentRef = GetParent();

		IDataBase *db = ::GetDataBase(Utils<ILayoutUIUtils>()->GetFrontDocument());
#ifdef DEBUG
		InterfacePtr<IHierarchy> myParent(db, ts_SmartLayoutItemUID, IID_IHIERARCHY);
		if (myParent && ::GetClass(this) != kGuideCreationTrackerBoss)
			parentRef = UIDRef(db, ts_SmartLayoutItemUID);
#endif

		//ICommandSequence *cascadeSequence = nil;

		PMRect spreadBBox;
		PBPMRect pbSpreadBBox;
		PMRect cellSize;
		int32	rows = 0, columns = 0;
		int32	rowIndex = 0;
		int32	columnIndex = 0;
		PMReal horizSpacing(9.0);
		PMReal vertSpacing(9.0);
		PMReal cellWidth(0.0);
		PMReal cellHeight(0.0);
		PMRect insets(9.0, 9.0, 9.0, 9.0);
		PMPoint cellTopLeft(0.0, 0.0);
		PMPoint cellBotRight(0.0, 0.0);
		
		if(fCreateMultiple)
		{
			GlobalErrorStatePreserver preserver;
			InterfacePtr<ILayoutControlData> viewLayerMgr(fControlView, IID_ILAYOUTCONTROLDATA);
			InterfacePtr<IDynamicTrackerData> dynamicData(this, IID_IDYNAMICTRACKERDATA); 
			if (dynamicData) 
			{
				rows = dynamicData->GetRows();
				columns = dynamicData->GetColumns();
				fGraphicBBox = dynamicData->GetGridBounds();
				insets = dynamicData->GetInsets();
				horizSpacing = dynamicData->GetHorizontalSpacing();
				vertSpacing = dynamicData->GetVerticalSpacing();
			}
		
			InterfacePtr<IShape> spreadShape(viewLayerMgr->GetSpreadRef(), UseDefaultIID());
			if ( spreadShape )
			{
				if ( bUseDragRect )
					spreadBBox = PMRect(fStartPnt.X(), fStartPnt.Y(), endPoint.X(), endPoint.Y());
				else
				{
					InterfacePtr<ISpread> spread(spreadShape, UseDefaultIID());
					InterfacePtr<IHierarchy> pagesLayer(spread->QueryPagesLayer());
					if (pagesLayer)
					{//XFSpreadIssue what is this code trying to do
						spreadBBox = Utils<Facade::IGeometryFacade>()->GetItemBounds( UIDRef(db, pagesLayer->GetChildUID(0)), 
										Transform::PasteboardCoordinates(), Geometry::OuterStrokeBounds());
						pbSpreadBBox = Utils<Facade::IGeometryFacade>()->GetItemBounds( GetUIDRef(spread), Transform::PasteboardCoordinates(), Geometry::OuterStrokeBounds());
						spreadBBox.MoveTo(fStartPnt.X(), fStartPnt.Y());
					}	
					else
					{
						spreadBBox = spreadShape->GetPrintedBBox(PMMatrix(), Transform::PasteboardCoordinates());
						pbSpreadBBox = spreadBBox;
					}
				}

				spreadBBox.Left() += insets.Left();
				spreadBBox.Right() -= insets.Right();
				spreadBBox.Top() += insets.Top();
				spreadBBox.Bottom() -= insets.Bottom();
				
				cellWidth = (spreadBBox.Width() - (columns - 1) * horizSpacing)/columns;
				if ( cellWidth < 0.0 )
				{
					horizSpacing = 0.0;
					cellWidth = spreadBBox.Width()/columns;
				}
				cellHeight = (spreadBBox.Height() - (rows - 1) * vertSpacing)/rows;
				if ( cellHeight < 0.0 )
				{
					vertSpacing = 0.0;
					cellHeight = spreadBBox.Height()/rows;
				}
								
				// left to right
				if ( fStartPnt.X() <= endPoint.X() )
				{
					// top to bottom
					if ( fStartPnt.Y() <= endPoint.Y() )
					{
						cellTopLeft = spreadBBox.LeftTop();
						cellBotRight.X() = cellTopLeft.X() + cellWidth;
						cellBotRight.Y() = cellTopLeft.Y() + cellHeight;
					}
					else	// bottom to top
					{
						cellTopLeft.X() = spreadBBox.Left();
						cellBotRight.X() = cellTopLeft.X() + cellWidth;
						cellBotRight.Y() = spreadBBox.Bottom();
						cellTopLeft.Y() = cellBotRight.Y() - cellHeight;
						cellHeight = -cellHeight;
						vertSpacing = -vertSpacing;
					}
				}
				else	// right to left
				{					
					// top to bottom
					if ( fStartPnt.Y() <= endPoint.Y() )
					{
						cellTopLeft.X() = spreadBBox.Right() - cellWidth;
						cellTopLeft.Y() = spreadBBox.Top();
						cellBotRight.X() = cellTopLeft.X() + cellWidth;
						cellBotRight.Y() = cellTopLeft.Y() + cellHeight;
					}
					else	// bottom to top
					{
						cellBotRight = spreadBBox.RightBottom();
						cellTopLeft.X() = cellBotRight.X() - cellWidth;
						cellTopLeft.Y() = cellBotRight.Y() - cellHeight;
						cellHeight = -cellHeight;
						vertSpacing = -vertSpacing;
					}
					cellWidth = -cellWidth;
					horizSpacing = -horizSpacing;
				}

				points.clear();
				points.push_back(cellTopLeft);
				points.push_back(cellBotRight);
			}

			//cascadeSequence = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
			//cascadeSequence->SetName("#cascadeplacecmd");
		}

		int creationCount(0);
		bool keepGoing = (ErrorUtils::PMGetGlobalErrorCode() == kSuccess);
		PMPoint startPt(cellTopLeft);
		// Create the page items, then leave them selected.
		ICommandSequence *cmdSequence = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);

		while (keepGoing )
		{
			// Create the page items, then leave them selected.
			IPlaceBehavior::eAfterPlace afterPlace = IPlaceBehavior::kOldBehavior;
			UIDRef newItem = CreatePageItem(parentRef, points, *theEvent, &afterPlace);

			if(newItem != UIDRef(nil, kInvalidUID)) 
			{
				++creationCount;

				if(kSuccess == ErrorUtils::PMGetGlobalErrorCode()) 
					ProcessAdditionalCreationCommands (newItem, parentRef, points, afterPlace);
				
				// [RCR] 9/28/98 #274166 Horizontal/Vertical lines don't get added to hierarchy because
				// SetBoundingBox fails. Paul added the SetBoundingBox step to ensure that the stroke is
				// within the dragged area. Since this step is not necessary for horizontal or vertical lines,
				// we skip it.
				
				// [RCR] 10/6/98 #274166 There was still a problem for lines that weren't exactly horizontal
				// or vertical. The minimum size alert was triggered.
				// So I just overrode SetBoundingBox in LineTracker to do nothing
				// Since the line tracker doesn't draw a bounding box, I think it's fine that the beginning
				// and ending points become the location of the _path_ points.
				// bool16 hasBounds = (endPoint.X() != fStartPnt.X()) && (endPoint.Y() != fStartPnt.Y());
#if SPREAD_ALIGNED_CREATION
				if (kSuccess == ErrorUtils::PMGetGlobalErrorCode())
					SetBoundingBox (newItem, parentRef, points);

				if(kSuccess == ErrorUtils::PMGetGlobalErrorCode()) 
					AddToHierarchy (parentRef, newItem);
#else
				if(kSuccess == ErrorUtils::PMGetGlobalErrorCode()) 
					AddToHierarchy (parentRef, newItem);

				if (kSuccess == ErrorUtils::PMGetGlobalErrorCode())
				{
					PMPointList effectivePointList = GetEffectiveBoundsUsingObjectStyle(points, newItem);
					SetBoundingBox(newItem, parentRef, effectivePointList);
				}
#endif

				if (kSuccess == ErrorUtils::PMGetGlobalErrorCode()) 
					ClearChangedState(newItem);

				if ( (!fCreateMultiple || (creationCount == 1)) 
					&& kSuccess == ErrorUtils::PMGetGlobalErrorCode()) 
				{
					if ( fCreateMultiple && (rows > 1 || columns > 1) )
					{
						CPathCreationTracker::ProcessAdditionalSelectionCommands (newItem);
					}
					else
						ProcessAdditionalSelectionCommands (newItem);
				}
			}

			keepGoing = (ErrorUtils::PMGetGlobalErrorCode() == kSuccess);
			if(fCreateMultiple && keepGoing)
			{
				if( creationCount > 1 ) 
					ProcessAddToSelectionCommand(fControlView, newItem);

				PMReal nextX = cellTopLeft.X() + cellWidth + horizSpacing;
				if ( ++columnIndex == columns || (!bUseDragRect && (nextX >= pbSpreadBBox.Right() || nextX <= pbSpreadBBox.Left())) )
				{
					columnIndex = 0;
					++rowIndex;

					cellTopLeft.X() = startPt.X();
					cellTopLeft.Y() += cellHeight + vertSpacing;
					cellBotRight.X() = cellTopLeft.X() + ::abs(cellWidth);
					cellBotRight.Y() = cellTopLeft.Y() + ::abs(cellHeight);
				}
				else
				{
					cellTopLeft.X() += cellWidth + horizSpacing;
					cellBotRight.X() = cellTopLeft.X() + ::abs(cellWidth);
				}
				points.clear();
				points.push_back(cellTopLeft);
				points.push_back(cellBotRight);

				keepGoing = (ErrorUtils::PMGetGlobalErrorCode() == kSuccess) && rowIndex < rows && columnIndex < columns
					&& (bUseDragRect || (cellTopLeft.Y() < pbSpreadBBox.Bottom() && cellTopLeft.Y() >= pbSpreadBBox.Top()));

			}
			else
				keepGoing = kFalse;			
		}
		CmdUtils::EndCommandSequence(cmdSequence);
	}

	// pass the endpoint back to RectangleTracker and RegPolyTracker
	if (mouseDragged && mouseDragged->GetBool())
		fPreviousPoint = endPoint;
}

void CPathCreationTracker::CleanupTracking()
{
	NonMarkingAGMGraphicsContext gc(fControlView);
	InterfacePtr<ISprite> sprite(this, IID_ISPRITE);
	sprite->Hide(&gc, kFalse);
	sprite->DestroySprite(&gc);

	fTransformMatrix.ResetToIdentity();
}

//----------------------------------------------------------------------------------------
// CPathCreationTracker::SetBoundingBox
//----------------------------------------------------------------------------------------
Geometry::BoundsKind CPathCreationTracker::GetPathCreationBoundsKind()
{
	Geometry::BoundsKind boundsKind = Geometry::PathBounds();
	InterfacePtr<ITransformPanelPrefs> transformPrefs( (ITransformPanelPrefs*)::QuerySessionPreferences(IID_ITRANSFORMPANELPREFERENCES));	
	if( transformPrefs)
		boundsKind = transformPrefs->GetShowStrokeBounds();
	return boundsKind;
}


void CPathCreationTracker::SetBoundingBox
	( 
		const UIDRef& newItem,
		const UIDRef& parent,
		const PMPointList& points
	)
{
	// Set the bbox of the new item to fit in points. We do this after the item has been
	// fully created so that its stroke is completely set up and so the item exactly fit
	// inside the box.
	InterfacePtr<ICommand> setBBoxCmd ( CmdUtils::CreateCommand(kSetBoundingBoxCmdBoss));
	InterfacePtr<ISetBoundingBoxCmdData> bboxCmdData(setBBoxCmd, IID_ISETBOUNDINGBOXCMDDATA);

	InterfacePtr<ITransform> parentTransform(parent, IID_ITRANSFORM);
	PMMatrix transformMatrix = ::InnerToPasteboardMatrix(parentTransform).Inverse();


	Geometry::BoundsKind boundsKind = GetPathCreationBoundsKind();


#if SPREAD_ALIGNED_CREATION
	PMPoint startPoint = points[0];
	PMPoint endPoint = points[1];
	transformMatrix.Transform(&startPoint);
	transformMatrix.Transform(&endPoint);

	PMRectCollection rectCollection;
	rectCollection.push_back(PMRect (startPoint, endPoint));


	bboxCmdData->SetBoundingBoxData(rectCollection, Transform::InnerCoordinates(), boundsKind);
	setBBoxCmd->SetItemList(  UIDList(newItem));

	InterfacePtr<IBoundsData> boundsData(setBBoxCmd, IID_IBOUNDSDATA);
	boundsData->SetDefaultBoundsChecking();

	CmdUtils::ProcessCommand(setBBoxCmd);

#else

//	PMReal xscale, yscale, skewslope, costheta, sintheta, xtranslation, ytranslation;
//	
//	transformMatrix.GetTransformValues( &xscale, &yscale, &skewslope, &costheta, &sintheta, &xtranslation, &ytranslation);
//
//	InterfacePtr<ICommand> transformCommand( CmdUtils::CreateCommand( kTransformPageItemsCmdBoss));
//	transformCommand->SetItemList( UIDList(newItem));
//	InterfacePtr<IBoundsData> transformBoundsData( transformCommand, UseDefaultIID());
//	if( transformBoundsData) transformBoundsData->SetNoBoundsChecking();
//	InterfacePtr<ITransformCmdData> data( transformCommand, UseDefaultIID());
//	data->SetTransformData( Transform::PasteboardCoordinates(), Transform::LeftTopLocation( boundsKind), Transform::RotateBy( costheta, -sintheta));
//	ErrorCode err = CmdUtils::ProcessCommand( transformCommand);
//
//	if( err) return;


	PMPoint startPoint = points[0];
	PMPoint endPoint = points[1];
	PMRectCollection rectCollection;
	rectCollection.push_back(PMRect (startPoint, endPoint));

	bboxCmdData->SetBoundingBoxData(rectCollection, Transform::PasteboardCoordinates(), boundsKind);
	setBBoxCmd->SetItemList(  UIDList(newItem));

	InterfacePtr<IBoundsData> boundsData( setBBoxCmd, IID_IBOUNDSDATA);
	boundsData->SetDefaultBoundsChecking();

	CmdUtils::ProcessCommand(setBBoxCmd);
#endif

}

//----------------------------------------------------------------------------------------
// CPathCreationTracker::ProcessAdditionalCreationCommands
//----------------------------------------------------------------------------------------

void CPathCreationTracker::ProcessAdditionalCreationCommands
	( 
		const UIDRef& newItem,
		const UIDRef& parent,
		const PMPointList& points,
		IPlaceBehavior::eAfterPlace afterPlace
	)
{
#if SPREAD_ALIGNED_CREATION
	// Add the points to the item
	InterfacePtr<ICommand>  addpointsCmd ( CmdUtils::CreateCommand(kAddSplinePointsCmdBoss));
	addpointsCmd->SetItemList(  UIDList(newItem));
	InterfacePtr<IPathGeometry> iPathGeometry(addpointsCmd, IID_IPATHGEOMETRY);

	PMMatrix pbtop;

	InterfacePtr<ITransform> parentTransform( parent, IID_ITRANSFORM);
	if (parentTransform)
	{
#if 0 
		pbtop = ::InnerToPasteboardMatrix(parentTransform).Inverse();
#endif
	}

	PMRect pathBounds(iPathGeometry->GetCtrlPointsBoundingBox (pbtop));
	PMPoint boundsCenter = pathBounds.GetCenter();
	
	PMMatrix itop(1.0, 0.0, 0.0, 1.0, boundsCenter.X(), boundsCenter.Y());
	PMMatrix ptoi(1.0, 0.0, 0.0, 1.0, -boundsCenter.X(), -boundsCenter.Y());

	pbtop.PostConcat (ptoi);

	PMPoint p0 = points[0], p1 = points[1];

	this->MakePath (p0, p1, iPathGeometry); //points[] are in pasteboard coordinates at this point
	InterfacePtr<IModifyPathPointsCmdData> iModPoints(addpointsCmd, IID_IMODIFYPATHPOINTSCMDDATA);
	
	// -1 tells the add command to copy all the paths and points
	iModPoints->SetStartingIndex (-1);
	iModPoints->SetPathIndex (-1);
	iModPoints->SetTransformMatrix(pbtop);
	
	CmdUtils::ProcessCommand(addpointsCmd);

	PMMatrixCollection matCol;
	
	matCol.push_back (itop);
	
	InterfacePtr<ICommand> setMatCmd(CmdUtils::CreateCommand (kSetPMMatrixCmdBoss));
	InterfacePtr<IPMMatrixListData> iSetMatCmdData(setMatCmd, IID_IPMMATRIXLISTDATA);
	iSetMatCmdData->Set (matCol);

	setMatCmd->SetItemList (UIDList (newItem));
	
	CmdUtils::ProcessCommand (setMatCmd);
#else

	// Add the points to the item
	InterfacePtr<ICommand>  addpointsCmd ( CmdUtils::CreateCommand(kAddSplinePointsCmdBoss));
	addpointsCmd->SetItemList(  UIDList(newItem));
	InterfacePtr<IPathGeometry> iPathGeometry(addpointsCmd, IID_IPATHGEOMETRY);

	PMMatrix pbtop;

	InterfacePtr<ITransform> parentTransform( parent, IID_ITRANSFORM);
	if (parentTransform)
	{
		pbtop = ::InnerToPasteboardMatrix(parentTransform).Inverse();
	}

	PMPoint p0 = points[0], p1 = points[1];

	this->MakePath (p0, p1, iPathGeometry); //points[] are in pasteboard coordinates at this point
	InterfacePtr<IModifyPathPointsCmdData> iModPoints(addpointsCmd, IID_IMODIFYPATHPOINTSCMDDATA);
	
	// -1 tells the add command to copy all the paths and points
	iModPoints->SetStartingIndex (-1);
	iModPoints->SetPathIndex (-1);
	iModPoints->SetTransformMatrix( PMMatrix());
	
	CmdUtils::ProcessCommand(addpointsCmd);

//		PMMatrixCollection matCol;
//		
//		matCol.push_back (itop);
//		
//		InterfacePtr<ICommand> setMatCmd(CmdUtils::CreateCommand (kSetPMMatrixCmdBoss));
//		InterfacePtr<IPMMatrixListData> iSetMatCmdData(setMatCmd, IID_IPMMATRIXLISTDATA);
//		iSetMatCmdData->Set (matCol);
//
//		setMatCmd->SetItemList (UIDList (newItem));
//		
//		CmdUtils::ProcessCommand (setMatCmd);

	if( ErrorUtils::PMGetGlobalErrorCode() == kSuccess){
		InterfacePtr<ICommand> transformCommand( CmdUtils::CreateCommand( kTransformPageItemsCmdBoss));
		transformCommand->SetItemList( UIDList(newItem));
		InterfacePtr<IBoundsData> transformBoundsData( transformCommand, UseDefaultIID());
		if( transformBoundsData) transformBoundsData->SetNoBoundsChecking();
		InterfacePtr<ITransformCmdData> data( transformCommand, UseDefaultIID());
		data->SetTransformData( Transform::ParentCoordinates(), Transform::CurrentOrigin(), Transform::TransformBy( pbtop));
		CmdUtils::ProcessCommand( transformCommand);
	}
#endif

#ifdef WINDOWS // TWS is Windows only for now.
	// If in TWS, and creating a graphic frame, apply the default fill color.
	Utils<ITouchWSUtils> touchWSUtils;
	if (touchWSUtils && touchWSUtils->IsAppInTouchWSMode())
	{
		InterfacePtr<IGraphicFrameData> frameData(newItem, UseDefaultIID());
		if (frameData && frameData->GetTextContentUID() == kInvalidUID)
			touchWSUtils->ApplyDefaultFillColor(UIDList(newItem));
	}
#endif
}

//----------------------------------------------------------------------------------------
// CPathCreationTracker::AddSelectionCommands
//----------------------------------------------------------------------------------------

void CPathCreationTracker::ProcessAdditionalSelectionCommands(const UIDRef& newItem)
{
	// Create a command to select the page item.
	InterfacePtr<ISelectionManager> iSelectionManager(Utils<ISelectionUtils>()->QueryViewSelectionManager( fControlView));
	InterfacePtr<ILayoutSelectionSuite>	iLayoutSelectionSuite (Utils<ISelectionUtils>()->QueryLayoutSelectionSuite (iSelectionManager));	
	
    // Prevent multiple enabled CSBs
    K2Vector<ClassID>       csbKeepList;
    csbKeepList.push_back (kNewLayoutSelectionBoss);
    iSelectionManager->DeselectAllExcept(&csbKeepList);

	iLayoutSelectionSuite->SelectPageItems ( UIDList(newItem), Selection::kReplace, Selection::kDontScrollLayoutSelection);
}

//----------------------------------------------------------------------------------------
// CPathCreationTracker::HandleMove
//----------------------------------------------------------------------------------------

void CPathCreationTracker::HandleMove(PMPoint& where)
{
	//at this point fStartPnt is in pasteboard coordinates
	PMPoint originalWhere = where;
	PMPoint originalStartPoint = fStartPnt;

	ASSERT_MSG(fControlView != nil, "nil control view in CPathCreationTracker::HandleMove()");
	NonMarkingAGMGraphicsContext gc(fControlView);//set up gc with pasteboard2window CTM (i.e. includes panorama); the entire layout view in window coords becomes clip-but since there is no IDVOffscreenPortData the clip doesn't make it into a platform buffer
	InterfacePtr<ISprite> sprite(this, IID_ISPRITE);
	
	if ( fShownFirstTime )
		sprite->Erase(&gc, PMPoint(), IShape::kDrawCreateDynamic/*, &transformMatrix*/);

	InterfacePtr<IPathGeometry> spritePathGeom(this, IID_IPATHGEOMETRY);

	fBackTransformMatrix.Transform(&fStartPnt);
	//at this point fStartPnt is in parent coordinates--usually spread coordinates
	fBackTransformMatrix.Transform(&where);//now also in (usually) spread coordinates
#if SPREAD_ALIGNED_CREATION	
	this->MakePath( fStartPnt, where, spritePathGeom);
	spritePathGeom->TransformPath( fTransformMatrix);
#else
	PMPoint p1 = fStartPnt, p2 = where;
	fTransformMatrix.Transform( &p1);
	fTransformMatrix.Transform( &p2);
	this->MakePath( p1, p2, spritePathGeom); //pasteboard aligned
#endif

	this->NotifyContinueTracking(originalStartPoint, originalWhere);
		
	sprite->Show(&gc, PMPoint(), IShape::kDrawCreateDynamic/*, &transformMatrix*/);	//hand make sprite path in pb coords--don't need additional matrix to pass in
		
	fShownFirstTime = kTrue;
}

static bool32 KeyboardSnapToToggle()
{
#ifdef MACINTOSH
    // On the Mac use the Control key as the toggle. Works with any active tool, matches Photoshop.
    return ::IsMacControlKeyPressed();
#else
    // On Windows, there is no Control key. Do nothing. Too many issues to try and use the Ctrl key as Photoshop
    // does in some situations. e.g. what about temporary toggle to pointer tool, or is user is trying to scale
    // an object via pointer tool (Ctrl will be held down). If it were possible to determine we were in a creation
    // tracking state, that might be restricted enough. For now though, can't toggle snapping on Windows.
    return kFalse;
#endif
}

static bool32 DoSnap()
{
	InterfacePtr<ISnapToPrefs> iSnapToPreferences((ISnapToPrefs*)::QueryPreferences(IID_ISNAPTOPREFERENCES, GetExecutionContextSession()->GetActiveContext()));	
	if (iSnapToPreferences && iSnapToPreferences->GetSnapToGrid())
		return kFalse;

 	// disable smart guides when snapping to layout grid
	InterfacePtr<ICJKGridPrefs> cjkGridPrefs((ICJKGridPrefs*)::QueryPreferences(IID_ICJKGRIDPREFS, GetExecutionContextSession()->GetActiveContext()));
	if ( cjkGridPrefs && cjkGridPrefs->GetSnapToLayoutGrid() )
		return kFalse;

	Utils<Facade::IGuidePreferencesFacade> guidePrefsFacade;
    bool32 smartGuides = ( guidePrefsFacade && guidePrefsFacade->GetShowSmartGuides()
		&& (guidePrefsFacade->GetSmartAlignToObjectCenter()
        ||		guidePrefsFacade->GetSmartAlignToObjectEdges()) );

	return smartGuides ^ KeyboardSnapToToggle();
}

void CPathCreationTracker::CheckSmartDimensions(PBPMPoint& endPoint, PBPMPoint& startPoint, SnapType& snapType, const IControlView* view)
{
	// see if we should be snapping to a width or height of an existing page item
	if ( DoSnap() )
	{
		UIDList emptyList;
		PMPoint centerPoint = (startPoint + endPoint) / 2;

		InterfacePtr<ISmartDimensions> iSmartDimensions(view, UseDefaultIID());
		
		// Don't use smart dimensions if point has already been snapped in x direction
		if ( iSmartDimensions && !(snapType & ISnapTo::kSnapX) )
		{
			PMReal width = ::abs(endPoint.X() - startPoint.X());

			PMReal snapX = iSmartDimensions->GetClosestWidth(width, emptyList);
			if ( snapX != 0.0 && ::abs(snapX - width) < 4.0 )
			{
				if (endPoint.X() > startPoint.X())
				{
					if (fCreatingFromCenter)
					{
						startPoint.X() = centerPoint.X() - snapX / 2;
						endPoint.X() = centerPoint.X() + snapX / 2;
					}
					else
					{
						endPoint.X() = startPoint.X() + snapX;
					}
				}
				else
				{
					if (fCreatingFromCenter)
					{
						startPoint.X() = centerPoint.X() + snapX;
						endPoint.X() = centerPoint.X() - snapX;
					}
					else
					{
						endPoint.X() = startPoint.X() - snapX;
					}
				}

				snapType |= ISnapTo::kSnapX;
			}
		}

		// Don't use smart dimensions if point has already been snapped in y direction
		if ( iSmartDimensions && !(snapType & ISnapTo::kSnapY) )
		{
			PMReal height = ::abs(endPoint.Y() - startPoint.Y());

			PMReal snapY = iSmartDimensions->GetClosestHeight(height, emptyList);
			if ( snapY != 0.0 && ::abs(snapY - height) < 4.0 )
			{
				if (endPoint.Y() > startPoint.Y())
				{
					if (fCreatingFromCenter)
					{
						startPoint.Y() = centerPoint.Y() - snapY / 2;
						endPoint.Y() = centerPoint.Y() + snapY / 2;
					}
					else
					{
						endPoint.Y() = startPoint.Y() + snapY;
					}
				}
				else
				{
					if (fCreatingFromCenter)
					{
						startPoint.Y() = centerPoint.Y() + snapY / 2;
						endPoint.Y() = centerPoint.Y() - snapY / 2;
					}
					else
					{
						endPoint.Y() = startPoint.Y() - snapY;
					}
				}

				snapType |= ISnapTo::kSnapY;
			}
		}
	}
}

//----------------------------------------------------------------------------------------
// CPathCreationTracker::ConvertToPasteboardConstrained
//----------------------------------------------------------------------------------------

void CPathCreationTracker::ConvertToPasteboardConstrained(PMPoint thePoint, PMPoint& convertedPoint)
{
	PMPoint delta;
	convertedPoint = thePoint;

	fShiftKeyPressed = ::IsShiftKeyPressed();	// Store the status of shift key in fShiftKeyPressed
	fOptionAltKeyPressed = ::IsOptionAltKeyPressed();	// Store the status of option/alt key in fOptionAltKeyPressed
	fCmdCtrlKeyPressed = ::IsCommandKeyPressed();
	ASSERT_MSG(fControlView != nil, "nil control view in CPathCreationTracker::ConvertToPasteboardConstrained()");

	// When spacebar is pressed, move the object while dragging.
	if(::IsSpaceKeyPressed())
	{
		delta = convertedPoint - fPreviousPoint;
		fFirstPoint += delta;
	}

	// If the user is holding down Option/Alt key, we use the starting point of dragging as the middle point
	IDataBase *db = ::GetDataBase(Utils<ILayoutUIUtils>()->GetFrontDocument());
    InterfacePtr<IPlaceGun> placeGun(db, db->GetRootUID(), UseDefaultIID());
	bool16 bPlaceGunActive = placeGun && placeGun->IsLoaded();
	if (fOptionAltKeyPressed && !bPlaceGunActive && !fCreateMultiple)
	{
		delta = convertedPoint - fFirstPoint;
		fStartPnt = fFirstPoint - delta;
		fCreatingFromCenter = kTrue;
	}
	else
	{
		fStartPnt = fFirstPoint;
		fCreatingFromCenter = kFalse;
	}
	
	// Constrain fStartPnt and convertedPoint at last.
	fPasteboardToSpreadMatrix.Transform( &fStartPnt);
	fStartPnt.ConstrainTo( fPasteBoardBoundsSpreadCoordinates);
	fSpreadToPasteboardMatrix.Transform( &fStartPnt);

	CursorOptions dynamicCursorSetting = GetCursorOption();
	if ( MovedMinimumDistance(thePoint) 
		&& (dynamicCursorSetting == kShowWidthHeight || dynamicCursorSetting == kShowLineLength || dynamicCursorSetting == kShowScale) )
	{
		CheckSmartDimensions(convertedPoint, fStartPnt, fSnapType, fControlView);
	}


	fPasteboardToSpreadMatrix.Transform( &convertedPoint);
	convertedPoint.ConstrainTo( fPasteBoardBoundsSpreadCoordinates);
	fSpreadToPasteboardMatrix.Transform( &convertedPoint);

	fStartGlobalPt = PasteboardToGlobal (fStartPnt);	

	// Do shift-constraint at last so the item will always be proportional.
	// #341493		Lin Xia 2/23/2000

	// If the user is holding down shift key, we want to constrain. For most
	// trackers this is to a square, but creation trackers can override for
	// some other behavior.
	if (fShiftKeyPressed)
		this->ShiftConstrainPoint(convertedPoint);
}

//----------------------------------------------------------------------------------------
// CPathCreationTracker::ConvertToPasteboardConstrained
//----------------------------------------------------------------------------------------

void CPathCreationTracker::ConvertToPasteboardConstrained(GSysPoint thePoint, PMPoint& convertedPoint)
{
	// Convert to local coordinates, constrained to pasteboard
	this->GlobalToPasteboard(thePoint, convertedPoint);
	this->ConvertToPasteboardConstrained (convertedPoint, convertedPoint);  //clobbers fStartPnt with constrained fFirstPoint in pasteboard coordinates
}

//----------------------------------------------------------------------------------------
// CPathCreationTracker::MakePath
//----------------------------------------------------------------------------------------

void CPathCreationTracker::MakePath 
	(
		const PMPoint& startPt, 
		const PMPoint& endPoint,
		IPathGeometry* pathGeometry
	)
{
	if (pathGeometry)
	{
		PMRect bbox(startPt, endPoint);
		Utils<IPathUtils>()->MakeRectanglePath(pathGeometry, bbox);
	}
}

//----------------------------------------------------------------------------------------
// CPathCreationTracker::AutoScroll
//----------------------------------------------------------------------------------------

PMPoint CPathCreationTracker::AutoScroll(const PMPoint& scrollBy, const PMPoint& scrolledPoint)
{	
	PMPoint amountScrolled = CTracker::AutoScroll(scrollBy, scrolledPoint);
	
	NonMarkingAGMGraphicsContext gc(fControlView);

	InterfacePtr<ISprite> sprite(this, IID_ISPRITE);
	sprite->InvalidateBBox();
	sprite->Scroll(&gc, amountScrolled, IShape::kDrawCreateDynamic);
	
	return amountScrolled;
}

bool16 CPathCreationTracker::IsGraphicFrame()
{
	return kFalse; // By default not a graphic frame
} 

void CPathCreationTracker::ShiftConstrainPoint(PMPoint& convertedPoint)
{
	// If creating from center (option/alt key is pressed), constrain to the center point.	
	if (fCreatingFromCenter)
	{
		PMRect constrainedRect(fStartPnt, convertedPoint);
		PMPoint centerPoint = constrainedRect.GetCenter();

		PMPoint delta(convertedPoint);
		delta -= centerPoint;

		if (abs(delta.X()) > abs(delta.Y()))  // greater change in x, use deltaY
		{
			PMReal newX(delta.X() > 0 ? abs(delta.Y()) : -abs(delta.Y()));
			convertedPoint.X(centerPoint.X() + newX);
			fStartPnt.X(centerPoint.X() - newX);
		}
		else
		{
			PMReal newY(delta.Y() > 0 ? abs(delta.X()) : -abs(delta.X()));
			convertedPoint.Y(centerPoint.Y() + newY);
			fStartPnt.Y(centerPoint.Y() - newY);
		}
	}
	else	// Constrain to the left-top point.
	{
		PMPoint delta(convertedPoint);
		delta -= fStartPnt;

		PMReal hGaps(0.0);
		PMReal vGaps(0.0);

		if ( fCreateMultiple && (fRows > 1 || fColumns > 1) )
		{
			hGaps = (fColumns - 1) * fHSpacing;
			if ( delta.X() < 0.0 )
				hGaps *= -1.0;
			vGaps = (fRows - 1) * fVSpacing;
			if ( delta.Y() < 0.0 )
				vGaps *= -1.0;

			delta.X() = (delta.X() - hGaps)/fColumns;
			delta.Y() = (delta.Y() - vGaps)/fRows;
		}

		if (abs(delta.X()) > abs(delta.Y()))  // greater change in x, use deltaY
		{
			PMReal newX(delta.X() > 0 ? abs(delta.Y()) : -abs(delta.Y()));

			if ( fCreateMultiple && (fRows > 1 || fColumns > 1) )
				newX = (newX * fColumns) + hGaps;
			convertedPoint.X(fStartPnt.X() + newX);
		}
		else
		{
			PMReal newY(delta.Y() > 0 ? abs(delta.X()) : -abs(delta.X()));
			if ( fCreateMultiple && (fRows > 1 || fColumns > 1) )
				newY = (newY * fRows) + vGaps;
			convertedPoint.Y(fStartPnt.Y() + newY);
		}
	}
}

bool16 CPathCreationTracker::SufficientSize(const PMPointList& points)
{
	return (points[0] != points[1]);
}

bool16 CPathCreationTracker::MovedMinimumDistance (const PBPMPoint& newLocation)
{
	PMPoint globalPoint = PasteboardToGlobal (newLocation);
	
	if ( abs(globalPoint.X() - fStartGlobalPt.X()) > kMinDragDistance ||
	     abs(globalPoint.Y() - fStartGlobalPt.Y()) > kMinDragDistance )
	{
		InterfacePtr<IBoolData> mouseDragged(this, IID_IMOUSEDRAGGED);
		if (mouseDragged != nil)
		{
			mouseDragged->Set(kTrue);
		}

		return kTrue;
	}
	
	return kFalse;
}


UIDRef CPathCreationTracker::CreatePageItem (const UIDRef& parent, const PMPointList& points, const IEvent& theEvent, IPlaceBehavior::eAfterPlace *afterPlace)
{
	InterfacePtr<ICommand> newPageItem (  CmdUtils::CreateCommand(kNewPageItemCmdBoss));
	InterfacePtr<INewPageItemCmdData> data(newPageItem, IID_INEWPAGEITEMCMDDATA);
	data->Set(parent.GetDataBase (), kSplineItemBoss, this->IsGraphicFrame() ? INewPageItemCmdData::kGraphicFrameAttributes : 
		INewPageItemCmdData::kDefaultGraphicAttributes);

	CmdUtils::ProcessCommand(newPageItem);
	const UIDList* itemList = newPageItem->GetItemList();
	UIDRef result(nil, kInvalidUID);
	if(itemList && itemList->Length() > 0)
		result = itemList->GetRef(0);

	if (afterPlace)
		*afterPlace = IPlaceBehavior::kOldBehavior;

	return result;
}


void CPathCreationTracker::AddToHierarchy (const UIDRef& parent, const UIDRef& newItem)
{
	InterfacePtr<ICommand> pAddCmd(CmdUtils::CreateCommand(kAddToHierarchyCmdBoss));

	InterfacePtr<IHierarchyCmdData>pCmdData( pAddCmd, IID_IHIERARCHYCMDDATA );
	pCmdData->SetParent( parent );
		
	K2Vector<int32> indexList;
	indexList.push_back (IHierarchy::kAtTheEnd);

	pCmdData->SetIndexInParent( indexList );
	pAddCmd->SetItemList(  UIDList(newItem));
	
	CmdUtils::ProcessCommand (pAddCmd);
}

void ClearChangedState(const UIDRef& newItem)
{
	// See whether the new item is a text item and get its TextModel.
	InterfacePtr<IGraphicFrameData> graphicFrameData(newItem, UseDefaultIID());
	if (!graphicFrameData)
		return;
	InterfacePtr<IMultiColumnTextFrame> mcf(newItem.GetDataBase(), graphicFrameData->GetTextContentUID(), UseDefaultIID());
	if (!mcf)
		return;
	InterfacePtr<ITextModel> textModel(mcf->QueryTextModel());
	if (!textModel)
		return;

	// Clear the text model's changed state.
	InterfacePtr<ICommand> linkChangedCmd(CmdUtils::CreateCommand(kLinkChangedCmdBoss));
	InterfacePtr<IBoolData>	hasChanges(linkChangedCmd, UseDefaultIID());
	hasChanges->Set(kFalse);
	InterfacePtr<IUIDData>	storyUIDData(linkChangedCmd, UseDefaultIID());
	storyUIDData->Set(textModel);
	CmdUtils::ProcessCommand(linkChangedCmd);
}


UIDRef CPathCreationTracker::GetParent()
{
	ASSERT_MSG(Utils<ILayoutUIUtils>()->GetFrontDocument() != nil, "CPathCreationTracker::GetParent() on nil front document!");
	
	IDataBase *db = ::GetDataBase(Utils<ILayoutUIUtils>()->GetFrontDocument());
	InterfacePtr<ILayoutControlData> viewLayerMgr(fControlView, IID_ILAYOUTCONTROLDATA);
	UID parent = kInvalidUID;

	
	// [RCR] ASSERT_MSG(fItemContext != nil, "Missing item context in CPathCreationTracker::GetParent()");
	if (fItemContext)
	{
		InterfacePtr<IHierarchy> creationParent(fItemContext->QueryNewItemParent(fControlView));
		if (creationParent)
			parent = ::GetUID(creationParent);	
	}
#ifdef DEBUG
	if (ts_SmartLayoutItemUID != kInvalidUID)
		parent = ts_SmartLayoutItemUID;
#endif
	if (parent == kInvalidUID)
		parent = viewLayerMgr->GetActiveLayerUID();


#if DEBUG && MACINTOSH
	DebugClassUtilsBuffer classBuf;
	char buf[1024];
	InterfacePtr<IPMUnknown> p( UIDRef(db, parent), IID_IUNKNOWN);
	::snprintf( buf, 1024, "%s", DebugClassUtils::GetIDName( &classBuf, ::GetClass(p)));
#endif




	return UIDRef(db, parent);
}

CPathCreationTracker::CursorOptions CPathCreationTracker::GetCursorOption(void) const
{
	return kDefaultCursor;
}

bool16 CPathCreationTracker::DrawingCursorFeedback()
{
	//This is a fallback mechanism
	//In case required interfaces are not available then keep 
	//drawing old feedback window on cursor

	InterfacePtr<IPMPointData> pmPointData(this, UseDefaultIID());
	if (!pmPointData)
		return kTrue;

	InterfacePtr<IPMRectData> rectData(this, UseDefaultIID());	//Used in GetTrackerBounds() in sprite
	if (!rectData)
		return kTrue;

	InterfacePtr<IIntData> cursorOption(this, UseDefaultIID());
	if (!cursorOption)
		return kTrue;

	if (Utils<IUIFeedbackUtils>()->IsDrawingCursorFeedback())
		return kTrue;

	return kFalse;
}

PMPointList CPathCreationTracker::GetEffectiveBoundsUsingObjectStyle(const PMPointList& currentPoints, const UIDRef pageItem)
{
	PMRect effectiveBounds = Utils<ILayoutAttrsHelperUtils>()->GetEffectinveBoundingBoxForPageItem(currentPoints, pageItem);
	PMPointList pointList;
	pointList.push_back(effectiveBounds.LeftTop());
	pointList.push_back(effectiveBounds.RightBottom());
	return pointList;
}
