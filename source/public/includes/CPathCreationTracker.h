//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CPathCreationTracker.h $
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
#ifndef __CPathCreationTracker__
#define __CPathCreationTracker__

#include "CTracker.h"
#include "IPlaceBehavior.h"
#include "IDynamicTrackerData.h"
#include "PMPoint.h"
#include "PMRect.h"
#include "UIDRef.h"
#include "TransformTypes.h"

//----------------------------------------------------------------------------------------
// Forward Declarations
//----------------------------------------------------------------------------------------

class ICommand;
class PMPoint;
class IPathGeometry;
class ICmdCollection;

//----------------------------------------------------------------------------------------
// CPathCreationTracker: Tracker for creating new page items
//----------------------------------------------------------------------------------------

#pragma export on

/**  Tracker for creating new page items.
	This tracker has the ability to create a grid of items when the user presses the arrow keys
	to increase the number of rows or columns in the grid. To enable this functionality, the
	tracker's boss must contain the following 2 interfaces:
			IID_ITRACKERKEYDATA, kIntDataImpl,   // Used for storing key presses in event handler so tracker can access for altering polygon sides and star inset or grid attributes
			IID_IDYNAMICTRACKERDATA, kDynamicTrackerDataImpl,	// Used for storing information about the grid and other dynamic information
			IID_ISPRITE, kNoHandleSpriteImpl,
	You could, of course, implement your own versions of any of these interfaces. However, these particular ones are
	already 'grid' savy.
*/
class WIDGET_DECL CPathCreationTracker : public CTracker
{
	public:
		// Dynamic cursor options for specifying what gets drawn in the cursor while tracking
		enum CursorOptions
		{
			kDefaultCursor = 0,	// do not modify the cursor
			kShowWidthHeight,	// Add width/height information to cursor
			kShowXPosition,		// Add X Position information to cursor (useful for vertical guides)
			kShowYPosition,		// Add Y Position information to cursor (useful for horizontal guides)
			kShowXYPosition,	// Add X,Y Position information to cursor
			kShowLineLength,	// Add Line length information to cursor
			kShowScale			// Add Scale information to cursor
		};

		/** Constructor 
			@param boss refers to object on which this interface is aggregated	
		*/
		CPathCreationTracker(IPMUnknown *boss);

		/** Destructor. */
		virtual ~CPathCreationTracker();
		
		/** Start tracking the mouse.  Usually called as the result of a mouse down event.
			@param theEvent event associated 
		*/
		virtual bool16 BeginTracking(IEvent* theEvent);
		
		/** Called after BeginTracking and before EndTracking.  ContinueTracking is called 
			repeatedly even when the mouse is not moving (to support things like auto scrolling).

			@param where location of mouse
			@param mouseDidMove specifies whether mouse-move event is behind this call
		*/
		virtual void ContinueTracking(const PBPMPoint& where, bool16 mouseDidMove);
	
		/** Called when tracking is completed.  Clean up any loose ends and post any dynamic commands.
			@param theEvent event associated 
		*/
		virtual bool16 EndTracking(IEvent* theEvent);

		/** Immediately terminate tracking.
			@param theEvent event associated 
		*/
		virtual void AbortTracking(IEvent* theEvent);
		
	protected:
		/** Destroy sprite and do general cleanup for EndTracking and AbortTracking cases.
		 */
		virtual void CleanupTracking();

		/** Override this method to make the cursor show dynamic metric info. */
		virtual CursorOptions GetCursorOption(void) const;

		/** 
			@param where
		*/
		virtual void HandleMove(PMPoint& where);
		/** 
			@param scrollBy
			@param scrolledPoint
		*/
		virtual PMPoint AutoScroll(const PMPoint& scrollBy, const PMPoint& scrolledPoint);

		/** 
			@param startPt
			@param endPoint
			@param pathGeometry
		*/
		virtual void MakePath (const PMPoint& startPt, const PMPoint& endPoint, IPathGeometry* pathGeometry);
		
		/** 
			@param where
		*/
		virtual void ShiftConstrainPoint(PMPoint& where);

		
		/** Returns kTrue if the distance between the first screen point and the most recent 
			screen point is greater than the min drag distance.  The pb point here gets
			converted to global coordinates inside the method.
			@param newLocation
			@return kTrue if the distance between the first screen point and the most recent 
			screen point is greater than the min drag distance, kFalse otherwise
		*/
		virtual bool16 MovedMinimumDistance (const PBPMPoint& newLocation);
		
		
		/** Clients should override this and return kTrue if they want to be graphic frames		
		*/
		virtual bool16 IsGraphicFrame();
		
		
		/** Clients should override this method if the
			client needs to perform special additional commands.
		*/
		virtual void ProcessAdditionalCreationCommands (const UIDRef& newItem, const UIDRef& parent, const PMPointList& points, IPlaceBehavior::eAfterPlace afterPlace);
					
		// 
		/** Clients should override this method if the item is not a kSplineItemBoss 
			@param parent

		*/
		virtual UIDRef CreatePageItem (const UIDRef& parent, const PMPointList& points, const IEvent& theEvent, IPlaceBehavior::eAfterPlace *afterPlace = nil);
		
		
		/** Clients should override this method if the
			client needs to make the item a special size. By default a SetBoundingBoxCmd is issued
			to set the stroke bounding box to be 'points'.
			@param newItem
			@param parent
			@param points
		*/
		virtual void SetBoundingBox (const UIDRef& newItem, const UIDRef& parent, const PMPointList& points);

		 
		/** Clients should override this method if they want a different behavior for adding to
			the hierarchy
			@param parent
			@param newItem
		*/
		virtual void AddToHierarchy (const UIDRef& parent, const UIDRef& newItem);
				
		 
		/** Clients should override this method if client needs special selection (i.e. no selection).
			By default, path item created will be selected. Note that this method will not be called
			if in grid mode (i.e. we are creating multiple items in this one tracking session.)
			@param newItem
		*/
		virtual void  ProcessAdditionalSelectionCommands (const UIDRef& newItem);

		/** Clients should override this method if client needs special selection (i.e. no selection).
			when in 'grid' mode (i.e. we are creating multiple items in this one tracking session.)
			By default, this method will perform a layout selection on all newly created page items.
			@param newItem
		*/
		virtual void ProcessAddToSelectionCommand(IControlView *view, const UIDRef& newItem);

		/** Do the whole thing - typically not overridden
			@param theEvent
		*/
		virtual void CompletelyCreateItem(IEvent* theEvent);

	
		/** Gives the chance to restrict creation. Must be true to create.
			Default returns true if both points are not equal.
			@param points 
			@return kTrue
		*/
		virtual bool16 SufficientSize(const PMPointList& points);

		/** 
		*/
		virtual void ConvertToPasteboardConstrained(PMPoint thePoint, PMPoint& convertedPoint);
		/** 
		*/
		virtual void ConvertToPasteboardConstrained(GSysPoint thePoint, PMPoint& convertedPoint);
		
		virtual void SetUpParentTransforms(PMPoint *endPoint);
		
		virtual UIDRef GetParent();
		
	private:
		
		/**
			For internal use only
		*/
		bool16 DrawingCursorFeedback();
		PMPointList GetEffectiveBoundsUsingObjectStyle(const PMPointList& currentPoints, const UIDRef pageItem);
	protected:
		/**
		This method is called from ConvertToPasteboardConstrained() to do
		SmartDimensions snapping.
		*/
		virtual void CheckSmartDimensions(PBPMPoint& endPoint,
											PBPMPoint& startPoint,
											SnapType& snapType,
											const IControlView* view);
		virtual Geometry::BoundsKind GetPathCreationBoundsKind();

		ClassID fClassID; 				// the class of the item we're creating
		PMPoint fStartPnt;				// location of first mouse down, constrained to paste board
		PMPoint fStartGlobalPt;			// stored global location of first mouse down.
		PMRect fPasteBoardBoundaries;
		PMRect fPasteBoardBoundsSpreadCoordinates;
		bool16 fShiftKeyPressed;			// True if shift key is currently pressed
		bool16 fShownFirstTime;
		bool16 fOptionAltKeyPressed;	// True if option/alt key is currently pressed
		bool16 fCmdCtrlKeyPressed;		// True if command/control key is currently pressed
		bool16 fCreatingFromCenter;		// True when user has option/alt key pressed
		PMMatrix fSpreadToPasteboardMatrix;
		PMMatrix fPasteboardToSpreadMatrix;
		PMMatrix fTransformMatrix;
		PMMatrix fBackTransformMatrix;
		IAbortableCmdSeq* fTrackerSequence;

		PMRect	fGraphicBBox;
		bool32	fCreateMultiple;
		int32	fRows;
		int32	fColumns;
		static PMReal	fHSpacing;
		static PMReal	fVSpacing;
};

#pragma export off

#endif
