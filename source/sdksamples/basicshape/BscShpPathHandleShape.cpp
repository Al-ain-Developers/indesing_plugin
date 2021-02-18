//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicshape/BscShpPathHandleShape.cpp $
//  
//  Owner: Adobe Developer Technologies
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

#include "VCPlugInHeaders.h"

// Interface includes:

// General includes:
#include "PathHandleShape.h"

// Project includes:
#include "BscShpID.h"


/** BscShpPathHandleShape
	Responsible for drawing selection handles and path for objects with a clipping path.

	This override is necessary because Utils<IPathUtils>()->QueryHandleShape() may
	preferentially query for the IPathHandleShape interface instead of
	IHandleShape.  (This happens when an item has a clipping path.)
	In that case, we want to be sure and return a bounding
	box that includes the selection handle dimensions.  The default
	implementation for a spline item doesn't -- it assumes standard
	selection handles.  For non-standard handles, this causes redraw 
	problems.

	BscShpPathHandleShape implements IPathHandleShape based on
	the partial implementation PathHandleShape2.

	@ingroup basicshape
	
*/


class  BscShpPathHandleShape : public PathHandleShape
{
	public:

		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		BscShpPathHandleShape(IPMUnknown* boss);

		/**
			Responsible for returning the bounding box of the page item including the selection handles.
			@param pbtoview Inner coords to drawing device (port) transform.
			@return Bounding PMRect in drawing device coordinates.
		*/
		virtual PMRect GetPaintedHandleBounds( const PMMatrix& pbtoview);

	
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(BscShpPathHandleShape, kBscShpPathHandleShapeImpl)

/* BscShpPathHandleShape Constructor
*/
BscShpPathHandleShape::BscShpPathHandleShape(IPMUnknown* boss)
	: PathHandleShape(boss)
{
}


/* GetPaintedBBox
*/
PMRect BscShpPathHandleShape::GetPaintedHandleBounds( const PMMatrix& theMatrix)
{
	PMRect pathBounds(0,0,0,0);

	InterfacePtr<IHandleShape> handleShape (this, IID_IHANDLESHAPE);

	if ( handleShape != nil)
	{
		// If possible use the IHandleShape interface to account for 
		// accurate selection handle size.
		pathBounds = handleShape->GetPaintedHandleBounds( theMatrix);
	}
	else
	{
		// No IHandleShape available, so use the base class approach
		// of assuming selection handles take no more than 
		// a 5 pt buffer around the control point bounding box.
		pathBounds = PathHandleShape::GetPaintedHandleBounds( theMatrix);
	}

	return pathBounds;
}

// End, BscShpPathHandleShape.cpp.






