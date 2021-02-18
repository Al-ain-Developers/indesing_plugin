//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ISetBoundingBoxCmdData.h $
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
//  
//  Purpose: 	Holds the new bounding boxes, indicates whether bounds are in 
//  pasteboard or inner coordinates, and sets the action that the
//  pageitem should take regarding the set bounding box cmd. 
//  See IGeometry for a description of SetAction.
//  
//========================================================================================

#pragma once
#ifndef __ISetBoundingBoxCmdData__
#define __ISetBoundingBoxCmdData__

#include "IPMUnknown.h"
#include "TransformTypes.h"
#include "GenericID.h"
#include "PMRect.h"

class ISetBoundingBoxCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISETBOUNDINGBOXCMDDATA };
	
	/**	SetBoundingBoxData sets up the command data for set bounding box commands.
		@rectCollection is the list of new frames--one corresponding te each item in the commands item list.
		@coordinateSpace is one of Transform::PasteboardCoordinates() or Transform::InnerCoordinates()
		@boundsKind is one of Geometry::OuterStrokeBounds() or Geometry::PathBounds()
	*/
	virtual void SetBoundingBoxData
		(
			const PMRectCollection& rectCollection,
			const Transform::CoordinateSpace	&coordinateSpace,
			Geometry::BoundsKind boundsKind
		) = 0;

	/**	GetRectList returns the PMRectCollection parameter set by SetBoundingBoxData.
	 */
	virtual const PMRectCollection& GetRectList() const = 0;

	/**	GetCoordinateSpace returns the CoordinateSpace parameter set by SetBoundingBoxData.
	 */
	virtual Transform::CoordinateSpace GetCoordinateSpace() const = 0;

	/**	GetBoundsKind returns the BoundsKind parameter set by SetBoundingBoxData.
	 */
	virtual Geometry::BoundsKind GetBoundsKind() const = 0;
};

#endif
