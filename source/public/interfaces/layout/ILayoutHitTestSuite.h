//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ILayoutHitTestSuite.h $
//  
//  Owner: Rich Gartland
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
	#ifndef _ILayoutHitTestSuite_
	#define _ILayoutHitTestSuite_
//________________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________________
	#include "HitTestDragConstants.h"
	#include "IPMUnknown.h"
	#include "ShuksanID.h"
	#include "PMPoint.h"
//================================================================================================
//________________________________________________________________________________________________
//	CLASS FORWARDS
//________________________________________________________________________________________________
class IControlView;
class IGeometry;
class ITracker;
class PointSelector;
class CursorSpec;

//________________________________________________________________________________________________
//	TYPEDEFS
//________________________________________________________________________________________________

//________________________________________________________________________________________________
//	CLASS DECLARATION
//________________________________________________________________________________________________
/**
	Suite interface to support hit-testing on the current layout selection.
	Used to determine whether a given point in a currently-selected item has been hit.
	@ingroup layout_suite
*/
class ILayoutHitTestSuite : public IPMUnknown
	{
	//____________________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_ILAYOUTHITTESTSUITE };

	//____________________________________________________________________________________________
	//	Member functions
	//____________________________________________________________________________________________
	public:
	/** For the currently-selected pageitems in the given view, hit-test a point against selection handles using the hit-test handler boss, returning the appropriate tracker 

		@param view [IN] The view whose selection to test
		@param where [IN] Pasteboard coordinates of point to test
		@param handlerBossClass [IN] Hit-test handler boss to use
		@param bDragging [IN] Whether mouse is being dragged
		@param tolerance [IN] The tolerance for how close 'where' must be to be considered a hit. Defaults to kHitTestTolerance. 

		@return ITracker* for the tracker to use.  Nil if no selected item hit.
		The reference count is incremented. The caller is responsible for calling Release() or embedding the return value in an 
		appropriate InterfacePtr construct.
 
		@see GenericID.h and GenericClass.fr for various kXXXHitTestHandlerBoss definitions
		@see HitTestDragConstants.h for kHitTestTolerance
	*/
	virtual ITracker* QueryHitTestHandlesForTracker(IControlView *view, const PBPMPoint& where, ClassID handlerBossClass, bool16 bDragging = kFalse, int16 tolerance = kHitTestTolerance) = 0;

	/** For the currently-selected pageitems in the given view, hit-test a point against selection handles, returning the item's IGeometry interface,
		and indicating which handle was hit
		
		@param view [IN] The view whose selection to test
		@param where [IN] Pasteboard coordinates of point to test
		@param handleIndex [OUT] Indicates which handle was hit
		@param bDragging [IN] Whether mouse is being dragged
		@param tolerance [IN] The tolerance for how close 'where' must be to be considered a hit. Defaults to kHitTestTolerance. 
		
		@return IGeometry* for the selected pageitem hit.  Nil if no selected item hit.
		The reference count is incremented. The caller is responsible for calling Release() or embedding the return value in an 
		appropriate InterfacePtr construct.
		
		@see HitTestDragConstants.h for kHitTestTolerance
	*/
	virtual IGeometry* QueryHitTestHandles(IControlView *view, const PBPMPoint& where, PointSelector& handleIndex, bool16 bDragging = kFalse, int16 tolerance = kHitTestTolerance ) = 0;

	/** For the currently-selected pageitems in the given view, hit-test a point against item bounding boxes, returning the item's IGeometry interface
		
		@param view [IN] The view whose selection to test
		@param where [IN] Pasteboard coordinates of point to test
		@param tolerance [IN] The tolerance for how close 'where' must be to be considered a hit. Defaults to kHitTestTolerance. 
		
		@return IGeometry* for the selected pageitem hit.  Nil if no selected item hit.
		The reference count is incremented. The caller is responsible for calling Release() or embedding the return value in an 
		appropriate InterfacePtr construct.
		
		@see HitTestDragConstants.h for kHitTestTolerance
	*/
	virtual IGeometry* QueryHitTestBoundingBox(IControlView *view, const PBPMPoint& where, int16 tolerance = kHitTestTolerance) = 0;


	/** For the currently-selected pageitems in the given view, hit-test a point against items using the hit-test handler boss, returning the item's IGeometry interface
		
		@param view [IN] The view whose selection to test
		@param where [IN] Pasteboard coordinates of point to test
		@param handlerBossClass [IN] Hit-test handler boss to use
		@param tolerance [IN] The tolerance for how close 'where' must be to be considered a hit. Defaults to kHitTestTolerance. 
		
		@return IGeometry* for the selected pageitem hit.  Nil if no selected item hit.
		The reference count is incremented. The caller is responsible for calling Release() or embedding the return value in an 
		appropriate InterfacePtr construct.
		
		@see GenericID.h and GenericClass.fr  for various kXXXHitTestHandlerBoss definitions
		@see HitTestDragConstants.h for kHitTestTolerance
	*/
	virtual IGeometry* QueryHitTestItems(IControlView *view, const PBPMPoint& where, ClassID handlerBossClass, int16 tolerance = kHitTestTolerance) = 0;

};

#endif 