//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPathInfoUtils.h $
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
#ifndef __IPathInfoUtils__
#define __IPathInfoUtils__

#include "GenericID.h"
#include "IPMUnknown.h"
#include "Utils.h"

#include "PMLine.h"
#include "PMPoint.h"
#include "TransformTypes.h"



class UIDList;
class IGeometry;
class IPathGeometry;
class IPathInfoUtils;

// PathInfo is used to analyze a list of objects to determine if they form a point or straight line

class PathInfo
{
public:

	
		inline	PathInfo():
					fSomePath(kTrue),
					fPointsAreCoLinear(kFalse),
					fPointA(),
					fPointB()
				{
				}

	
	inline bool16 IsStraightLine() const;
		// Points are colinear and there is some visible path
		// i.e. 0----0 0 is considered a line but 0 0 0 is not
		
	inline bool16 IsVerticalLine() const;

	inline bool16 IsHorizontalLine() const;

	inline PMLine GetLine() const;
 // Call IsStraightLine() first

	inline bool16 IsPoint() const;

	inline PMPoint	GetPoint() const; //no callers
	// call IsPoint() first
	
	inline bool16 PointsAreCoLinear() const;

		// True for points or lines
	
	inline PathInfo Combine(const PathInfo& pathInfo1, const PathInfo& pathInfo2) const;

	
private:
	friend class PathInfoUtils;

	PMPoint fPointA;			// First anchor point
	PMPoint fPointB;			// Last anchor point
	bool16  fPointsAreCoLinear; // True if all points, including control points are the same or on the same line
	bool16 	fSomePath; 			// True if 1 or more paths has width or height > 0.
};



/** Utilities related to classifying paths.
	@ingroup layout_util
*/
class IPathInfoUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPATHINFOUTILS };

	virtual bool16 IsStraightLine( const PathInfo& pathInfo ) const = 0;
		// Points are colinear and there is some visible path
		// i.e. 0----0 0 is considered a line but 0 0 0 is not
		
	virtual bool16 IsVerticalLine( const PathInfo& pathInfo ) const = 0;
	virtual bool16 IsHorizontalLine( const PathInfo& pathInfo ) const = 0;
	virtual PMLine GetLine( const PathInfo& pathInfo ) const = 0; // Call IsStraightLine() first

	virtual bool16 IsPoint( const PathInfo& pathInfo ) const = 0;
	virtual PMPoint	GetPoint( const PathInfo& pathInfo ) const = 0;	// call IsPoint() first //no callers
	
	virtual bool16 PointsAreCoLinear( const PathInfo& pathInfo ) const = 0;
		// True for points or lines

	virtual bool16 IsEqual( const PathInfo& pathInfo1, const PathInfo& pathInfo2 ) const = 0;


	// Line testing. (Used by Transform Panel to detect lines, and show Length
	// rather than width and height
	
		
	virtual PathInfo GetPathInfo(IPathGeometry* pathGeometry, const PMMatrix* matrix = nil) const = 0;
		// Determines whether all points of all paths of the specified path geometry
		// are on the same straight line. A matrix value of nil means use pasteboard coordinates.

	virtual PathInfo GetPathInfo(IGeometry* geometry, const PMMatrix* matrix = nil) const = 0;
		// Determines whether all points of all paths of the specified geometry
		// are on the same straight line. Should work for guides and other non-path
		// geometries with 0 width or height A matrix value of nil means use pasteboard coordinates.
		
	virtual PathInfo GetPathInfo(const UIDList& items, const Transform::CoordinateSpace& coordinateSpace = Transform::PasteboardCoordinates()) const = 0;
		// Determines whether all points of all paths of the specified items
		// are on the same straight line. If any item does not have a path geometry
		// PathInfo.fIsStraightLine will be false. All items must have coordinateSpace as
		// a common parent for the result to have any useful meaning. Thus if 
		// coordinateSpace == InnerCoordinates(), the list can contain only contain one item.
		// If coordinateSpace == SpreadCoordinates() or ParentCoordinates(), the items must 
		// all be on the same spread. If coordinateSpace == PageCoordinates, the items must
		// all be on the same page.

	virtual bool16 IsVerticalLine(IGeometry* pageItem) const = 0; //in inner coordinates

	virtual bool16 IsHorizontalLine(IGeometry* pageItem) const = 0; //in inner coordinates
	
	virtual bool16 IsPoint(IGeometry* pageItem) const = 0;
};

inline bool16 operator ==(const PathInfo& a, const PathInfo& b)
{
	return Utils<IPathInfoUtils>()->IsEqual( a, b );
}

inline bool16 operator !=(const PathInfo& a, const PathInfo& b)
{
	return !Utils<IPathInfoUtils>()->IsEqual( a, b );
}

inline bool16 PathInfo::IsStraightLine() const { return Utils<IPathInfoUtils>()->IsStraightLine( *this ); }
inline bool16 PathInfo::IsVerticalLine() const { return Utils<IPathInfoUtils>()->IsVerticalLine( *this ); }
inline bool16 PathInfo::IsHorizontalLine() const { return Utils<IPathInfoUtils>()->IsHorizontalLine( *this ); }
inline PMLine PathInfo::GetLine() const { return Utils<IPathInfoUtils>()->GetLine( *this ); }
inline bool16 PathInfo::IsPoint() const { return Utils<IPathInfoUtils>()->IsPoint( *this ); }
inline PMPoint	PathInfo::GetPoint() const { return Utils<IPathInfoUtils>()->GetPoint( *this ); }
inline bool16 PathInfo::PointsAreCoLinear() const { return Utils<IPathInfoUtils>()->PointsAreCoLinear( *this ); }


#endif	// __IPathInfoUtils__
