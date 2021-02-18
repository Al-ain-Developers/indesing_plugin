//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/wavetool/WaveTracker.h $
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

#ifndef __WaveTracker__
#define __WaveTracker__

#include "CPathCreationTracker.h"
#include "PMPathPoint.h"

/** Base implementation for the trackers in this plug-in. Functionality common
	to all trackers chould be added here.
	
	@ingroup wavetool
*/
class WaveTracker : public CPathCreationTracker
{
public:
	/** Constructor.
	 */ 
 	WaveTracker(IPMUnknown *boss);
	
	/** Destructor
	 */
 	~WaveTracker();

	/** When the shift key is pressed constrain the line along 
		which the user is dragging to be a multiple of 45 degrees.	
	
		@param convertedPoint the resulting location of the mouse when the point is constrained.   
	 */
	virtual void ShiftConstrainPoint(PMPoint &convertedPoint);

	/** Adjusts the bounding box of the page item. 
		The CPathCreationTracker implementation of SetBoundingBox
		assumes the page item is created within the bounds of the
		box dragged by the mouse. Our wave paths may extend above
		or below this box. So we override this method and adjust
		the bounds to the bounding box of our wave.
		
		@param newItem	the new item that is created by the wave tool
		@param parent	the new item's parent
		@param points	default bounds described by point list containing top left and bottom right points.  
	*/
	virtual void SetBoundingBox (const UIDRef& newItem, const UIDRef& parent, const PMPointList& points);

protected:
	/** Transforms the supplied path.
		\li translates the origin to the point at which the user did 
		mouse down
		\li rotates the axis to align with the line on which the user 
		is dragging the mouse
		\li scales proportional to distance between start point and
		end point

		@param endPoint	the last point in the path to be transformed.
		@param pathLength the length of the path to be transformed
		@param pathGeometry the path to be transformed.
	 */
	void Transform(const PMPoint& endPoint, const PMReal pathLength, IPathGeometry* pathGeometry);
};

#endif




