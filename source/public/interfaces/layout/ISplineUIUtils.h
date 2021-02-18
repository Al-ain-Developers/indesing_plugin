//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ISplineUIUtils.h $
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
#ifndef __ISplineUIUtils__
#define __ISplineUIUtils__

#include "SplineUIID.h"
#include "IPMUnknown.h"
#include "Utils.h"

#include "IShape.h"
#include "PMPathPoint.h"
#include "PMRect.h"
#include "HitTestDragConstants.h"
#include "CursorSpec.h"
#include "ISplineState.h"

class ICommand;
class IControlView;
class IPathGeometry;
class UIDList;

#define kInvalidParameter -1.0		//valid values for spline curve parameter are 0 <= u <= 1.0

/** Helper constants for SetSplineState */
const bool16 kUpdateMotion = kTrue;
const bool16 kDontUpdateMotion = kFalse;
const bool16 kDeleteMotion = kTrue;
const bool16 kDontDeleteMotion = kFalse;

/** UI-related utilities for creating splines, mostly used by spline tool.
	@ingroup layout_util
	@see ISplineState.h
*/
class ISplineUIUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISPLINEUIUTILS };

	//Hit testing for cursor providers and trackers
	typedef enum {
		kDontCheckSelection = 0,	//Check all path objects in the spread hierarchy, some of which may be selected (excludes standoffs)
		kDoCheckSelection,			//Check the selection first (in order to include their standoffs), as well as the hierarchy
		kOnlyCheckSelection,		//Check only selected path objects (includes standoffs)
		kExcludeSelection			//Check only path objects that aren't selected (excludes standoffs)
	} CheckOption;

	/**	Return state of spline tool creation/editing 
		@param nil control view to check (will check the document corresponding to this view)
		@return SplineState enum value, can be kOff, kCreation, kMotion
	 */
	virtual ISplineState::SplineState GetSplineState( IControlView* view = nil ) = 0;

	/**	Fire a command to set the document in edit/creation state (SplineTool) if values are passed,
		or to turn off spline edit/creation state if all default values are used.
		@param document the document to use
		@param view, the control view to check
		@param pathItem which page item and is being modified
		@param motionItem which motion page item and is being modified
		@param motionOwnerItem which item does the motion page item belong to
		@param pathIndex the index of the path on the pathItem that is being modified 
		@param pointIndex the index of the point being modified
		@param bUpdateMotionItem kTrue to take motion item points an store back to main item, kFalse to skip this. When motionItem us UIDRef::gNull, uses previous motion item to update animation data.
		@param bDeleteMotionItem kTrue to delete motion item, kFalse to leave it. When motionItem us UIDRef::gNull, deletes any previous motion item.
		@return ErrorCode, the result of the ProcessCommand to change the spline state.
	 */
	virtual ErrorCode SetSplineState( const UIDRef& document,
										IControlView* view = nil,
										const UIDRef& pathItem = UIDRef::gNull,
										const UIDRef& motionItem = UIDRef::gNull,
										const UIDRef& motionOwnerItem = UIDRef::gNull,
										int32 pathIndex = -1,
										int32 pointIndex = -1,
										bool16 bUpdateMotionItem = kUpdateMotion,
										bool16 bDeleteMotionItem = kDeleteMotion,
										bool16 bScheduleCmd = kFalse) = 0;

	virtual ISplineState* QueryDocSplineState( IControlView* view = nil ) = 0;

	virtual bool16 HitTestCurrentPathBeginPoint( const SysPoint& globalLocation ) = 0;

	virtual bool16 HitTestCurrentPathEndPoint( const SysPoint& globalLocation ) = 0;

	virtual bool16 HitTestOtherPathEndPoints( const SysPoint& globalLocation,
											 UIDRef* pathItem = nil,
											 int32* pathIndex = nil,
											 int32* pointIndex = nil ) = 0;

	virtual bool16 HitTestAnyPathEndPoints( const SysPoint& globalLocation,	//Includes a closed, single-point path
		                                   UIDRef* pathItem= nil,
										   int32* pathIndex = nil,
										   int32* pointIndex = nil,
										   int32 hitTestFlags = IShape::kDirectSelect,
										   bool16 allVisibleSpreads = kTrue, //if kFalse, check only current spread
										   int32 tolerance = kHitTestTolerance) = 0;	

	virtual bool16 HitTestAnyPathMidPoints( const SysPoint& globalLocation,	//Includes all points on a closed, multi-point path
										   CheckOption checkOpt,
										   UIDRef* pathItem = nil,
										   int32* pathIndex = nil,
										   int32* pointIndex = nil,
										   int32 hitTestFlags = IShape::kDirectSelect,
										   bool16 allVisibleSpreads = kTrue ) = 0;	//if kFalse, check only current spread

	virtual bool16 HitTestAnyPathPoints( const SysPoint& globalLocation,
									    CheckOption checkOpt,
										UIDRef* pathItem = nil,
										int32* pathIndex = nil,
										int32* pointIndex = nil,
										int32 hitTestFlags = IShape::kDirectSelect,
										bool16 allVisibleSpreads = kTrue, //if kFalse, check only current spread
										int32 tolerance = kHitTestTolerance) = 0;	

	virtual bool16 HitTestAnyPathHandles( const SysPoint& globalLocation,
									     CheckOption checkOpt,
										 UIDRef* pathItem,
										 PointSelector* selector,
										 int32 hitTestFlags = IShape::kDirectSelect,
										 bool16 allVisibleSpreads = kTrue,		//if kFalse, check only current spread
										 bool16 testTextFrameHandles = kFalse ) = 0;	//TODO: Would be better if text frame handles were adornments to avoid special case

	virtual bool16 HitTestAnyPathSegments( const SysPoint& globalLocation,
										  CheckOption checkOpt,
										  UIDRef* pathItem = nil,
										  int32* pathIndex = nil,
										  int32* segmentIndex = nil,
										  PMReal* curveParameter = nil,
										  int32 hitTestFlags = IShape::kDirectSelect,
										  bool16 allVisibleSpreads = kTrue, //if kFalse, check only current spread
										  int32 tolerance = kHitTestTolerance) = 0;	

	//check for hit on parts of a particular item
	virtual bool16 HitTestPathEndPoints( const SysPoint& globalLocation, IPMUnknown* pageItem, int32* pathIndex, int32* pointIndex, int32 tolerance = kHitTestTolerance ) = 0;
	virtual bool16 HitTestPathMidPoints( const SysPoint& globalLocation, IPMUnknown* pageItem, int32* pathIndex, int32* pointIndex ) = 0;
	virtual bool16 HitTestPathPoints( const SysPoint& globalLocation, IPMUnknown* pageItem, int32* pathIndex, int32* pointIndex, int32 tolerance = kHitTestTolerance ) = 0;
	virtual bool16 HitTestPathPoint( const SysPoint& globalLocation, const PBPMPathPoint& pathPoint, int32 tolerance = kHitTestTolerance ) = 0;
	virtual bool16 HitTestPathHandles( const SysPoint& globalLocation, IPMUnknown* pageItem, PointSelector* selector ) = 0;
	virtual bool16 HitTestPathHandle( const SysPoint& globalLocation, PBPMPathPoint pathPoint, PathPointIndex& handleHit, int32 tolerance = kHitTestTolerance ) = 0;
	virtual bool16 HitTestPathSegments( const SysPoint& globalLocation, IPMUnknown* pageItem, int32* pathIndex, int32* segmentIndex, PMReal* curveParameter, int32 tolerance = kHitTestTolerance ) = 0;

	virtual bool16 HitTestPathFills( const PBPMPoint& location, IPMUnknown* pageItem, int32* pathIndex ) = 0;

	//check for hit on a particular segment
	virtual bool16 HitTestPathSegment( const PBPMPoint& location, IPMUnknown* pageItem, int32 pathIndex, int32 segmentIndex, PMReal* curveParameter ) = 0;
	virtual bool16 HitTestPathSegment( const PBPMRect& r, IPMUnknown* pageItem, int32 pathIndex, int32 segmentIndex ) = 0;

	/* Return kTrue if item has a "fake" center point handle, kFalse if not.
		@param pageItem [IN] The geometry for the page item to possibly draw center handle for.
	 */
	virtual bool16 HasCenterPoint(IGeometry* pageItem) = 0;

	/* Check for hit on center point of a particular item. Center point is only draw for spline shapes with no 'X' drawn and no center point.
		@param pageItem [IN] The geometry for the page item to hit test.
		@param centerPoint [IN] Pasteboard coordinates of point to test.
		@param tolerance [IN] The hit test slop to use, typically kHitTestTolerance.
	 */
	virtual bool16 HitTestCenterPoint(IControlView* view, IGeometry* pageItem, const PBPMPoint& where, int16 tolerance) = 0;

	/** Given and point and a center reference point, compute a cursor. Used in conjunction with handle hittesting to return
		a cursor that indicates that a handle will rotate around a center point.
		@param where [IN] Pasteboard coordinates of point to test. Typically the point that hits a handle.
		@param centerPoint [IN] Pasteboard coordinates of point to rotate around. Typically the center point of the selection.
		@param spec [OUT] The cursor spec for the rotation cursor.
	*/
	virtual void GetRotationCursor(const PBPMPoint& where, const PBPMPoint& centerPoint, CursorSpec& spec) = 0;

	//Used by add point trackers to get the revised path points
	virtual void GetNewPathPoints( IPathGeometry* pathGeom,
									int32 pathIndex,
									int32 pointIndex,
									const PMReal& curveParameter,
									PBPMPathPoint& newPathPtBefore,
									PBPMPathPoint& newPathPtAt,
									PBPMPathPoint& newPathPtAfter ) = 0;

	//Tests whether another anchor point in theItem's path geometry intersects pbBounds (typically
	// used to ensure an object will remain on the pasteboard even if currentPt is moved off it)
	virtual bool16 AnotherAnchorPointIntersects( const UIDRef& theItem, const PointSelector& currentPt, const PBPMRect& pbBounds ) = 0;

	// Tests whether an item can be broken into two separate page items. Scissors tool uses this when operating on open paths.
	virtual bool16 IsSplitAllowed( const UIDRef& item ) = 0;
};


#endif	// __ISplineUIUtils__
