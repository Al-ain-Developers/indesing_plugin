//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IRefPointUIUtils.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __IRefPointUIUtils__
#define __IRefPointUIUtils__

#include "AppUIID.h"
#include "IPMUnknown.h"
#include "Utils.h"

#include "PMString.h"
#include "PMPoint.h"
#include "PMPolygon4.h"
#include "IReferencePointData.h"
#include "TransformTypes.h"

class UIDList;
class ISpread;
class IControlView;
class ILayoutControlData;
class IGraphicsPort;
class IGraphicsContext;

/**  Utility interface for dealing with the reference point. Each layout view has its own reference point, which
	 is indicated in the Transform Panel/Control Panel as a nine-point proxy. The reference point has several components:
	 a pasteboard coordinate, and a position (see @IReferencePointData.h for ReferencePointPosition enum). The reference point
	 is used for displaying information in the transform panel for selected page item coordinates, and as a reference point
	 for certain commands (such as rotation, which is done around a reference point).

	 @ingroup layout_util
	 @see IRefPointUtils.h
	 @see ReferencePointPosition
*/
class IRefPointUIUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IREFPOINTUIUTILS };

	/**	Query the IRefencePointData interface for this layout view.
		@param layoutData [IN] the ILayoutControlData for the view.
		@return IReferencePointData*, caller must release. 
	 */
	virtual IReferencePointData* QueryRefPointData(ILayoutControlData* layoutData) = 0;

	/**	Show the refence point for the layout view.
		@param layoutData [IN] the ILayoutControlData for the view.
	 */
	virtual void ShowReferencePoint(ILayoutControlData* layoutData) = 0;

	/**	Hide the reference point for the layout view.
		@param layoutData [IN] the ILayoutControlData for the view.
	 */
	virtual void HideReferencePoint(ILayoutControlData* layoutData) = 0;

	/**	Invalidate the screen location of the reference point for the layout view.
		This is automatically called when the reference point is hidden or show or moved,
		so it shouldn't be required in most cases.
		@param layoutData [IN] the ILayoutControlData for the view.
		@param forceInval[IN] kTrue to force the invalidation even if the reference point is hidden, kFalse to only invalidate when shown. 
	 */
	virtual void InvalidateReferencePoint(ILayoutControlData* layoutData, bool16 forceInval = kFalse) = 0;

	/**	Is the reference point shown for the layout view? Note that the reference point will
		actually only be drawn when it is shown and visible.
		@param layoutData [IN] the ILayoutControlData for the view.
		@return bool16 kTrue if shown, kFalse is hidden.
	 */
	virtual bool16 IsReferencePointShown(ILayoutControlData* layoutData) = 0;

	/**	Is the reference point locked for the layout view. When locked, reference point
		will not be updated during selection changes.
		@param layoutData [IN] the ILayoutControlData for the view.
		@return bool16 kTrue if locked, kFalse if unlocked.
	 */
	virtual bool16 IsReferencePointLocked(ILayoutControlData* layoutData) = 0;

	/**	Lock the reference point for the layout view.
		@param layoutData [IN] the ILayoutControlData for the view.
	 */
	virtual void LockReferencePoint(ILayoutControlData* layoutData) = 0;

	/**	Unlock the reference point for the layout view.
		@param layoutData [IN] the ILayoutControlData for the view.
	 */
	virtual void UnlockReferencePoint(ILayoutControlData* layoutData) = 0;

	/**	Does the current selection have a visible reference point?
		@param layoutData [IN] the ILayoutControlData for the view.
		@see IReferencePointSuite.h
	 */
	virtual void SetReferencePointVisible(ILayoutControlData* layoutData) = 0;

	/**	Does the current selection have a hidden reference point?
		@param layoutData [IN] the ILayoutControlData for the view.
		@see IReferencePointSuite.h
	 */
	virtual void SetReferencePointInvisible(ILayoutControlData* layoutData) = 0;

	/**	Is the reference point visible/drawn for the layout view and selection?
		@param layoutData [IN] the ILayoutControlData for the view.
		@return bool16 kTrue if reference point drawn, kFalse if not.
		@see IReferencePointSuite.h
	 */
	virtual bool16 IsReferencePointVisible(ILayoutControlData* layoutData) = 0;

	/**	Change the reference point for the layout view to the new values. Helper interface
		for generating and processing a kMoveReferencePointCmdBoss.
		@param layoutData [IN] the ILayoutControlData for the view.
		@param newPosition [IN] the new reference position
		@param newPoint [IN] the new point in pasteboard coordinates
		@param referenceFrame [IN] the new reference point. Use kZeroRect if not relevant. 
		@return ErrorCode the result of the command.
		@see GetReferenceFrame
		@see kMoveReferencePointCmdBoss
	 */
	virtual ErrorCode ChangeReferencePoint(ILayoutControlData* layoutData, 
									 IReferencePointData::ReferencePointPosition newPosition,
									 const PMPoint& newPoint,
									 const PBPMRect& referenceFrame = kZeroRect) = 0;

	/**	Change just the position of the reference point for the layout view given a set of page items.
		@param layoutData [IN] the ILayoutControlData for the view.
		@param newPosition [IN] the new reference point position
		@param items [IN] a UIDList reference to the list of page items to use for computing the reference point position of.
		@return ErrorCode the result of the command
		@see kMoveReferencePointCmdBoss
	 */
	virtual ErrorCode ChangeReferencePoint(ILayoutControlData* layoutData,
										IReferencePointData::ReferencePointPosition newPosition,
										 const UIDList& items) = 0;

	/**	Set the reference position and point for the layout view. This is a helper function
		used by the move reference point command and shouldn't be used directly.
		@param layoutData [IN] the ILayoutControlData for the view.
		@param position [IN] the new reference position
		@param point [IN] the new reference point in global pasteboard coordinates.
		@see ChangeReferencePoint
		@see kMoveReferencePointCmdBoss
	 */
	virtual void SetReferencePositionAndPoint(ILayoutControlData* layoutData, 
											 IReferencePointData::ReferencePointPosition position,
											 const PBPMPoint& point) = 0;

	/**	Return the reference point for the layout view.
		@param layoutData [IN] the ILayoutControlData for the view.
		@return PBPMPoint the reference point in pasteboard coordinates.
	 */
	virtual PBPMPoint GetPasteboardReferencePoint( ILayoutControlData* layoutData) = 0;


	/**	Test to see if the given point "hits" the reference point. Used by trackers and includes a small slop rect.
		@param layoutData [IN] the ILayoutControlData for the view.
		@param point [IN] the point in pasteboard coordinates to use for hittesting.
		@return bool16 kTrue if hit within a small slop value of reference point, kFalse if not.
	 */
	virtual bool16 PointInActiveReferencePoint(ILayoutControlData* layoutData, const PBPMPoint& point) = 0;

	/**	Test to see if the given point "hits" the reference point. Used by trackers and includes a small slop rect.
		@param layoutData [IN] the ILayoutControlData for the view.
		@param point [IN] the point in local window coordinates to use for hittesting.
		@return bool16 kTrue if hit within a small slop value of reference point, kFalse if not.
	 */
	virtual bool16 WindowPointInActiveReferencePoint(ILayoutControlData* layoutData, const PMPoint& point) = 0;
	
	/**	Recompute the reference point for the layout window based on the selection and change it. 
		Called in response to selection changes and updates the reference point to the same reference
		position on the new selection. Also saves the reference position as the new session default,
		since the last-user set position is always the new default position for new views and documents.
		Session preference is stored in IID_IDEFAULTREFPOINTPOSITION on kWorkspaceBoss.
		@param layoutData [IN] the ILayoutControlData for the view.
		@see CalculateReferencePoint
		@see ChangeReferencePoint
	 */
	virtual void SetDefaultState(ILayoutControlData* layoutData) = 0;

	/**	Obsolete, do not use. */
	virtual void SetDefaultPosition(ILayoutControlData* layoutData) = 0;

	/**	Obsolete, do not use.
		Set the reference point offset for the layout view. Used when the position is kOther and value
		is relative to the center.
		@param layoutData [IN] the ILayoutControlData for the view.
		@param offset [IN] the value in global pasteboard coordinates.
	 */
	virtual void SetReferencePointOffset(ILayoutControlData* layoutData, const PBPMPoint& offset) = 0;

	/**	Obsolete, do not use.
		Get the reference point offset for the layout view. Used when the position is kOther and value
		is relative to the center. Currently unused.
		@param layoutData [IN] the ILayoutControlData for the view.
		@return PBPMPoint the offset value in pasteboard coordinates.
	 */
	virtual PBPMPoint GetReferencePointOffset(ILayoutControlData* layoutData) = 0;

	/**	Set the reference frame for the layout view. A reference frame is a rectangle relative
		to which offset values are displayed in the transform palette/control strip when the content offset
		preference is set. Comes into play when a page item inside another is selected (e.g. an image). The reference
		frame is the parent frame.
		@param layoutData [IN] the ILayoutControlData for the view.
		@param referenceFrame [IN] in global pasteboard coordinates
	 */
	virtual void SetReferenceFrame(ILayoutControlData* layoutData, const PBPMRect& referenceFrame) = 0;

	/**	Return the reference frame for the layout view. A reference frame is a rectangle relative
		to which offset values are displayed in the transform palette/control strip when the content offset
		preference is set. Comes into play when a page item inside another is selected (e.g. an image). The reference
		frame is the parent frame.
		@param layoutData [IN] the ILayoutControlData for the view.
		@return PBPMRect the reference frame in global pasteboard coordinates.
		@see ITransformPanelPrefs.h
		@see GetShowContentOffset
	 */
	virtual PBPMRect GetReferenceFrame(ILayoutControlData* layoutData) = 0;

	/**	Return the current reference point location for the layout view.
		@param layoutData [IN] the ILayoutControlData for the view.
		@return ReferencePointLocation a structure describing reference point location, position and spread offset.
		@see ReferencePointLocation
	 */
	virtual Transform::TransformOrigin GetReferencePointTransformOrigin( ILayoutControlData* layoutData) = 0;
	
	//move callers to GetReferencePointTransformOrigin
	virtual IReferencePointData::ReferencePointPosition GetReferencePointPosition( ILayoutControlData* layoutData) = 0;

};


#endif	// __IRefPointUIUtils__
