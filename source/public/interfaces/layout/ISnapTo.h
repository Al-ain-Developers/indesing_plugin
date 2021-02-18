//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ISnapTo.h $
//  
//  Owner: Paul Sorrick
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
#ifndef __ISNAPTO__
#define __ISNAPTO__

#include "PMTypes.h"
#include "PMPoint.h"
#include "PMRect.h"
#include "PMMatrix.h"

//----------------------------------------------------------------------------------------
// Forward Declarations
//----------------------------------------------------------------------------------------

class IControlView;
class PMPoint;
class IHierarchy;
class UIDList;
class IPathGeometry;

//----------------------------------------------------------------------------------------
// ISnapTo: Abstract interface for doing snap to
//----------------------------------------------------------------------------------------

typedef int32 SnapFlags;
typedef int32 SnapType;
const PMReal kInvalidSnapValue = 10000000.0;

class ISnapTo : public IPMUnknown
{
	public:

		// Snapping flags for SnapFlags data type.
		enum
		{
			kSnapNothing =			0x0000,	// Snap to nothing
			kSnapRulerGuides =		0x0001,	// Snap to ruler guides
			kSnapSmartGuides =		0x0002, // Snap to smart guides
			kSnapMarginGuides =		0x0004,	// Snap to margin guides
			kSnapColumnGuides =		0x0008,	// Snap to column guides on page
			kSnapPage =				0x0010,	// Snap to page outline (and pasteboard)
			kSnapGrid =				0x0020,	// Snap to drawing grid
			kSnapBaselineGrid =		0x0040,	// Snap to baseline grid
			kSnapRulerTickmarks =	0x0080,	// Snap to ruler tick marks	(ruler guides w/ shift key)
			kSnapSelection =		0x0100,	// Snap to selection (reference point)
			kSnapAllGuides =		kSnapRulerGuides + kSnapMarginGuides + kSnapColumnGuides + kSnapSmartGuides,
			kSnapAllGrids =			kSnapGrid + kSnapBaselineGrid,
			kSnapAllPageMarks =		kSnapAllGuides + kSnapAllGrids + kSnapPage,
		};

		// Snapping values for SnapType data type.
		enum
		{
			kSnapNone		= 0x00000000,			// No snapping in any direction
			kSnapX			= 0x00000001,			// Snap along x direction within a test area 
			kSnapY			= 0x00000002,			// Snap along y direction within a test area 
			kSnapXandY		= kSnapX + kSnapY,		// Typical case, snap along x or y coordinate hit within a test area
			kSnapAnyX		= 0x00000004,			// When doing x coordinate snapping, snap along any x coordinate hit (e.g. vertical ruler guide), not just within the test area. Typically specified along with kSnapX.
			kSnapAnyY		= 0x00000008,			// When doing y coordinate snapping, snap along any y coordinate hit (e.g. horizonal ruler guide), not just within the test area. Typically specified along with kSnapY.
			kSnapAllX		= 0x00000004 + kSnapX,	// Snap along all x coordinates hit. Use for point tracking such as guide tracking where client wants snapping along an entire x line.
			kSnapAllY		= 0x00000008 + kSnapY,	// Snap along all y coordinates hit. Use for point tracking such as guide tracking where client wants snapping along an entire y line. 
			kSnapAllXandY	= kSnapAllX + kSnapAllY,// Snap along all x or y coordinates hit. Use for point tracking such as zero point tracking where client wants snapping along an entire x/y crosshair line. 
			kSnapInvalid	= 0x00000010,			// Invalid state
			kSnapSkipCenters = 0x00000020			// For gap tool, don't snap to the centers in x or y
		};

		// Method to Initialize the snapping code. Should be called before SetSnapFlags to
		// clear old settings. Automatically called in trackers derived from CTracker.
		virtual void Init(IControlView* theView) = 0;

		// Methods to get/set item list of items being moved. 
		// List is empty when not moving objects (e.g. resizing, creating a page item)
		virtual const UIDList* GetItemList() const = 0;			
		virtual void SetItemList(const UIDList& itemList) = 0;	

		// Methods to get/set initial point DoSnapTo is called with (usually a mouse point)
		virtual const PMPoint& GetInitialPoint() const = 0;			
		virtual void SetInitialPoint(const PMPoint& initialPoint) = 0;	

		// Methods to get/set the current point index of point passed to ISnapTo::DoSnapToPoint, ISnapToService::FindSnapPoint
		// There are two variations.  The first is the point index adjusted for the items transformation.
		// The second is the items actual point index.
		virtual const PMRect::PointIndex GetPointIndex() const = 0;			
		virtual void SetPointIndex(const PMRect::PointIndex pointIndex) = 0;
		
		virtual const PMRect::PointIndex GetActualPointIndex() const = 0;			
		virtual void SetActualPointIndex(const PMRect::PointIndex pointIndex) = 0;

		// Methods to get/set whether snapping is currently enabled for this tracker.
		virtual bool16 GetSnappingEnabled() const = 0;			
		virtual void SetSnappingEnabled(bool16 enabled) = 0;	

		// Get/Set methods for what snapping flags are currently set (what we are snapping to)
		virtual SnapFlags GetSnapFlags() const = 0;
		virtual void SetSnapFlags(IControlView* theView, SnapFlags flags) = 0;

		// Get/Set the type for desired x or y direction(s) snapping. Used for calls to DoSnapTo in CTracker.cpp.
		virtual SnapType GetSnapType() const = 0;
		virtual void SetSnapType(SnapType flags) = 0;

		// Method to actually do snapping. Returns how the point/rect was snapped.
		virtual SnapType DoSnapTo(IControlView* theView, 			// View to snap in
								PMPoint& thePoint, 					// Point to snap (or mouse point when snapping a rect)
								PMRect* theRect = nil, 				// Rectangle to snap, used when moving objects
								SnapType snapType = kSnapXandY) = 0;// How to snap the point(s)

		// Sub methods called from DoSnapTo based on point or rect.
		// These methods call each method below if its flag is turned on.
		// Returns how the point was snapped.
		virtual SnapType DoSnapToPoint(IControlView* theView, 		// View to snap in
							PMPoint& thePoint, 						// Point to snap
							PMRect* theRect, 						// Rect being snapped (might be nil)
							SnapType snapType = kSnapXandY) = 0;	// How to snap the point
							
		// Returns how the rect was snapped.
		virtual SnapType DoSnapToRect(IControlView* theView, 		// View to snap in
							PMPoint& thePoint, 						// Mouse point at time of call to DoSnapTo
							PMRect* theRect, 						// Rectangle being snapped
							SnapType snapType = kSnapXandY) = 0;	// How to snap the rectangle

		// Various types of snapping, called when the corresponding flag is set. Returns how the point was snapped.
		virtual SnapType SnapToRulerTickmarks(IControlView* theView, PMPoint& thePoint, SnapType snapType = kSnapXandY) = 0;
		virtual SnapType SnapToRulerGuides(IControlView* theView, PMPoint& thePoint, SnapType snapType = kSnapXandY) = 0;
		virtual SnapType SnapToMarginGuides(IControlView* theView, PMPoint& thePoint, SnapType snapType = kSnapXandY) = 0;
		virtual SnapType SnapToColumnGuides(IControlView* theView, PMPoint& thePoint, SnapType snapType = kSnapX) = 0;
		virtual SnapType SnapToGrid(IControlView* theView, PMPoint& thePoint, SnapType snapType = kSnapXandY) = 0;
		virtual SnapType SnapToBaselineGrid(IControlView* theView, PMPoint& thePoint, SnapType snapType = kSnapY) = 0;
		virtual SnapType SnapToPage(IControlView* theView, PMPoint& thePoint, SnapType snapType = kSnapY) = 0;
		
		// Method used when collecting guides on the page and master page.
		// Used privately within a callback within SnapToRulerGuides to collect guides.
		virtual void Add( const PMMatrix &rXform, IHierarchy *pPageItem ) = 0;

		// Helper methods
		virtual bool16 MouseOverPage(IControlView* theView, PMPoint& thePoint, PMRect& pageRect, int32& pageIndex) = 0;

		// Performance Optimization for Layout view dragging:
		//	LayoutWidget asks SnapTo client to decide if a particular mouse move should trigger snapping
		//	Default behavior is to only snap when mouse movement is relatively slow - otherwise the hittest overhead can slow down the drag appreciably
		enum eShouldSnap
		{
			kShouldSnapDrag_UseDefault	= -1,	// Use default behavior of layoutView (only snaps when movement is "slow")
			kShouldSnapDrag_No			= 0,			// Do not snap this time
			kShouldSnapDrag_Yes		= 1			// Do snapping
		};

		// Should snap at this time? Return kShouldSnapDrag_UseDefault to get pre-2.0 behavior.
		virtual eShouldSnap ShouldSnapDragOverLayoutView(IControlView* layoutView, 			// View to snap in
								const PMPoint& thePoint, 																		// Raw mouse point
								const PMPoint& theConstrainedPoint,  													// Constrained mouse point
								const PMPoint& thePreviousPoint, 														// Previous raw mouse point
								const PMReal zoomFactor, 																	// zoom factor of layout view
								const PMRect& theRect) const = 0; 														// item bounds
								
};

#endif
