//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/wavetool/WaveTracker.cpp $
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
#include "IPathGeometry.h"
#include "IGeometry.h"
#include "IGeometryFacade.h"

// General incldues:
#include "PMMatrix.h"
#include "Trace.h"
#include "TransformUtils.h"
#include "Utils.h"

// Project includes:
#include "WaveTracker.h"

/*
*/
WaveTracker::WaveTracker(IPMUnknown * boss) : CPathCreationTracker(boss)
{
}

/*
*/
WaveTracker::~WaveTracker()
{
}

/*
// When the shift key is pressed we constrain the line along 
// which the user is dragging to be a multiple of 45 degrees.
*/
void WaveTracker::ShiftConstrainPoint(PMPoint& convertedPoint)
{
	PMPoint delta(convertedPoint);
	delta -= fStartPnt;

	if (abs(delta.X()) > abs(delta.Y()))
	{
		// greater change in x
		if ((ToInt16(delta.Y()) == 0) || (abs(delta.X() / delta.Y()) > 2))
		{
			convertedPoint.X(fStartPnt.X() + delta.X());
			convertedPoint.Y(fStartPnt.Y());
		}
		else
		{
			PMReal newX(delta.X() > 0 ? abs(delta.Y()) : -abs(delta.Y()));
			convertedPoint.X(fStartPnt.X() + newX);
		}
	}
	else
	{
		if ((ToInt16(delta.X()) == 0) || (abs(delta.Y() / delta.X()) > 2))
		{
			convertedPoint.X(fStartPnt.X());
			convertedPoint.Y(fStartPnt.Y() + delta.Y());
		}
		else
		{
			PMReal newY(delta.Y() > 0 ? abs(delta.X()) : -abs(delta.X()));
			convertedPoint.Y(fStartPnt.Y() + newY);
		}
	}
}

	
/*
// The CPathCreationTracker implementation of SetBoundingBox
// assumes the page item is created within the bounds of the
// box dragged by the mouse. Our wave paths may extend above
// or below this box. So we override this method and adjust
// the bounds to the bounding box of our wave.
*/
void WaveTracker::SetBoundingBox(const UIDRef& newItem, const UIDRef& parent,const PMPointList& points)
{
	// We use do/while(false) and break out on error.
	do
	{
		// Get the bounds of the item in Pasteboard co-ordinates.
		PBPMRect bBox = Utils<Facade::IGeometryFacade>()->GetItemBounds( newItem, Transform::PasteboardCoordinates(), Geometry::PathBounds());

		// Call parent to set the adjusted bounds.
		PMPointList bBoxPoints;
		bBoxPoints.push_back(bBox.LeftTop());
		bBoxPoints.push_back(bBox.RightBottom());
		CPathCreationTracker::SetBoundingBox(newItem, parent, bBoxPoints);

	} while (false); // only do once
}

/*
// Transforms the supplied path as follows:
// -translates the origin to the point at which the user did 
//  mouse down
// -rotates the axis to align with the line on which the user 
//  is dragging the mouse
// -scales proportional to distance between start point and
//  end point
*/
void WaveTracker::Transform(const PMPoint& endPoint, const PMReal pathLength, IPathGeometry* pathGeometry)
{
	// Translate to where the user did mouse down
	PMMatrix translationMatrix(1, 0, 0, 1, fFirstPoint.X(), fFirstPoint.Y());

	// Rotate along line of mouse drag from start to end points
	PMReal dY = endPoint.Y() - fFirstPoint.Y();
	PMReal dX = endPoint.X() - fFirstPoint.X();
	PMReal theta = (PMReal) std::atan2(ToDouble(dY),::ToDouble(dX));
	PMReal cosTheta = (PMReal)std::cos(::ToDouble(theta));
	PMReal sinTheta = (PMReal)std::sin(::ToDouble(theta));
	PMMatrix rotationMatrix(cosTheta, sinTheta, -sinTheta, cosTheta, 0, 0);

	// Scale based on distance between start and end points
	PMReal scale = (fFirstPoint.Distance(endPoint)) / pathLength;
	PMMatrix scaleMatrix(scale,0,0,scale,0,0);

	// Apply the transformation M' = MtM (1)translate 2)rotate 3)scale
	PMMatrix myMatrix = rotationMatrix*translationMatrix;
	myMatrix = scaleMatrix*myMatrix;
	pathGeometry->TransformPath(myMatrix);
	TRACE("WaveTracker::Transform:fFirstPoint=%f,%f:endPoint=%f,%f:distance=%f:angle=%f\n",
		::ToDouble(fFirstPoint.X()),::ToDouble(fFirstPoint.Y()),
		::ToDouble(endPoint.X()),::ToDouble(endPoint.Y()),
		::ToDouble(fFirstPoint.Distance(endPoint)),
		::ToDouble(theta));
}

// End WaveTracker.cpp.



