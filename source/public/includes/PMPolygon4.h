//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PMPolygon4.h $
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
#ifndef __PMPOLYGON4__
#define __PMPOLYGON4__

#ifndef __PMPOINT__
#include "PMPoint.h"
#endif

#ifndef __PMRECT__
#include "PMRect.h"
#endif

//----------------------------------------------------------------------------------------
// Forward declarations
//----------------------------------------------------------------------------------------
class PMPolygon4;

//----------------------------------------------------------------------------------------
// Typedefs
// The following types are designed primarily for use in parameter lists to aid in
// determining what coordinate space a method or function expects a parameter to be in.
// They are just synonyms for PMPolygon4
//----------------------------------------------------------------------------------------
typedef PMPolygon4 VPMPolygon4;		// polygon4 in "View" coordinates
typedef PMPolygon4 PBPMPolygon4;	// polygon4 in "Pasteboard" coordinates
typedef PMPolygon4 IPMPolygon4;		// polygon4 in "Inner" coordinates
typedef PMPolygon4 OPMPolygon4;		// polygon4 in "Outer" coordinates


#pragma export on
//----------------------------------------------------------------------------------------
// PMPolygon4
//----------------------------------------------------------------------------------------

/**	A C++ class for a 4-side polygon. This polygon is defined by 4 points.
*/
class PUBLIC_DECL PMPolygon4
{
	public:
   		typedef base_type data_type;

		/**	Default constructor.
		*/
		PMPolygon4();
		/**	Contstructor a polygon with a given rectangle.
			@param r is the rectangle.
		*/
		PMPolygon4(const PMRect& r);
		/**	Contstructor a polygon with another polygon.
			@param other is the PMPolygon4.
		*/
		PMPolygon4(const PMPolygon4& other);
	
		/**	Set four points for the polygon from the given rectangle.
			@param r is the rectangle.
		*/
		void SetPoints(const PMRect& r);

		/**	@return true if this is an empty polygon.
		*/
		bool16 IsEmpty() const;
		
		/**	Return true if two polygons are equal.
			@param other specifies the other PMPolygon4 to compare with.
			@return true if both are equal.
		*/
		PMPolygon4& operator=(const PMPolygon4& other);

		/**	Returns the nth point of the polygon. 0 is the top left, 1 is top right, 2 is bottom right, 3 is bottom left.
			@param index should be >= 0 and <= 3.
			@return the nth point.
		*/
		PMPoint operator[](int16 index) const;
		
		/**	Returns the nth point of the polygon. 0 is the top left, 1 is top right, 2 is bottom right, 3 is bottom left.
			@param index should be >= 0 and <= 3. 
			@return the nth point.
		*/
		PMPoint& operator[](int16 index);

		/**	@return the smallest rectangle that contains this polygon.
		*/
		PMRect	GetContainingRect() const;
		
	private:
		PMPoint fPolyPt[4];
};

#pragma export off

#endif
