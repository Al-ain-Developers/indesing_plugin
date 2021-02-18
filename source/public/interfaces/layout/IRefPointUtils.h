//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IRefPointUtils.h $
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
#ifndef __IRefPointUtils__
#define __IRefPointUtils__

#include "AppFrameworkID.h"
#include "IPMUnknown.h"
#include "IReferencePointData.h"
#include "TransformTypes.h"

class UIDList;

/**  Utility interface for functions that computing reference points. The reference point has several components:
	 a pasteboard coordinate, and a position (see @IReferencePointData.h for ReferencePointPosition enum). The reference point
	 is used for displaying information in the transform panel for selected page item coordinates, and as a reference point
	 for certain commands (such as rotation, which is done around a reference point).
	 @ingroup layout_util
	 @see IRefPointUIUtils.h
	 @see ReferencePointPosition
*/
class IRefPointUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IREFPOINTUTILS };

	/**	Returns the reference point in pasteboard coordinates for the specified bounds based on the position.
		@param position [IN] is one of IReferencePointData::ReferencePointPosition. See @IReferencePointData.h
		@param bounds [IN] is the bounds, typically of the selection.
		@return the reference point.
		
	*/
	virtual PBPMPoint CalculateReferencePoint_1(IReferencePointData::ReferencePointPosition position,
											  const PMPolygon4& bounds) = 0; //should probably use a PMRect, PMMatrix pair

	/**	Returns the reference point in pasteboard coordinates for the specified items in the list based on the position.
		@param position [IN] is one of IReferencePointData::ReferencePointPosition. See @IReferencePointData.h
		@param items [IN] the list of items.
		@param referenceFrame [OUT] if not nil, the parent's rect bound is returned.
		@param pUseStroke [IN] if not nil, it use this setting to calculate the reference point. If true, the stroke bounds are used.
		Otherwise the path bound is used. If nil, the current global setting from ITransformPanelPrefs is used.
		@return the reference point.
		@see ITransformPanelPrefs.h
		@see GetShowStrokeBounds
	*/
	virtual PBPMPoint CalculateReferencePoint_2(IReferencePointData::ReferencePointPosition position,
											  const UIDList& items,
											  PBPMRect* referenceFrame /*= nil*/,	// Optionally return parent rect if it exists (e.g. graphic item direct selected)
											  const Geometry::BoundsKind* pUseStroke /*= nil*/,	// Optionally sets setting to indicate whether to use stroke or path bound.
											  const Transform::CoordinateSpace* coordinateSpace /* = nil*/) = 0;

	inline  PBPMPoint CalculateReferencePoint_3( IReferencePointData::ReferencePointPosition position, const UIDList& items)
	{
		return CalculateReferencePoint_2( position, items, nil, nil, nil);
	}

	/**	Returns the reference position given a rect point index.
		@param index [IN] is the point index and is one of PMRect::PointIndex. See @PMRect.h
		@return the reference point position and is one of IReferencePointData::ReferencePointPosition. See @IReferencePointData.h
	*/
	virtual IReferencePointData::ReferencePointPosition MapPointIndexToReferencePoint(PMRect::PointIndex index) = 0;

	/**	Returns the point index position given a reference point position.
		@param position [IN] is the reference position and is one of IReferencePointData::ReferencePointPosition. See @IReferencePointData.h
		@return the point index and is one of PMRect::PointIndex. See @PMRect.h
	*/
	virtual PMRect::PointIndex MapReferencePointToPointIndex(IReferencePointData::ReferencePointPosition position) = 0;

	/**	Converts a reference point position to its equivalent TransformOrigin. 
		e.g. IReferencePointData::kTopLeft converts to Transform::LeftTopLocation()
		@param position [IN] is the reference position and is one of IReferencePointData::ReferencePointPosition. See @IReferencePointData.h
		@return TransformOrigin to match. See @TransformTypes.h
	*/
	virtual Transform::TransformOrigin RefPositionToTransformOrigin(IReferencePointData::ReferencePointPosition position) = 0;

};


#endif	// __IRefPointUtils__
