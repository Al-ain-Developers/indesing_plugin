//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IConvertShapeSuite.h $
//  
//  Owner: Shengliu Dai
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
//  Note:
//  
//========================================================================================

#pragma once
	#ifndef __IConvertShapeSuite__
	#define __IConvertShapeSuite__

#include "IPMUnknown.h"
#include "K2Vector.h"

/** Value used as minimal distance between two points in order to perform a "join" operation.
*/
const PMReal kMinimalDistance = 6.00;

/**
	Convert page item shape suite interface
	@ingroup layout_suite  
*/
class IConvertShapeSuite : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_ICONVERTSHAPESUITE };

		typedef enum
		{
			/** 
			Rectangle; other type of rectangle such as 
			kRoundedCornerRectangle ,
			kInverseRoundedCornerRectangle,
			kInsetCornerCornerRectangle,
			kBevelCornerRectangle,
			kFancyCornerRectangle,
			could be acheived by combinition with CornerEffects.
			Triangle and polygon may also have corner effects.
			*/
			kRectangle,   
			kTriangle,
			kPolygonX,
			kOval,
			kEllipse = kOval,
			kClosedPath,
			kOpenPath,
			kLine,
			kOrthogonalLine
		} ShapeType;

		typedef enum
		{
			/**
			Enum describing the types of a path point.
			*/
			kLineEnd,		/** Bezier control handles are in degenerate case--the tangents have collapsed into a point. */
			kCorner,		/** Point with discontinous tangents. For the user, the tangents may be manipulated independently. */
			kSmooth,		/** Point with two Bezier control handles in a continuous tangent, though length of tangents may vary. */
			kSymmetrical	/** Sepcial case of kSmooth in which the two tanguents are continuous and of equal length. */
		} PointType;

		typedef K2Vector<PointType> PointTypeList;

	public:

		/**	Can convert any selected page items' shape?
			@param none
			@return bool16 
		 */
		virtual bool16 CanConvertShape		(void) const = 0;	
	
		/**	Can convert selected points to another type?
			@return bool16 kTrue if selected points can be converted, kFalse otherwise
			*/
		virtual bool16 CanConvertPointType() const = 0;	
	
		/**  GetPointType is used to determine the PointType for the current selection.	
			pointTypeList will be empty if not in path selection mode or if no points are in the path selection.
			@param pointTypeList OUT The list for adding point type values to.
			@param  sortedAndUnique IN If kTrue the list will be sorted and duplicates will be removed.
			@see IPathSelection.h
		*/
		virtual void GetPointType(PointTypeList& pointTypeList, bool16 sortedAndUnique ) const = 0;

		/**	Can join selected points? Path(s) must be open. Differs from Connect in that path points must be very close (kMinimalDistance).
			@param none
			@return bool16 Returns kTrue when one (or two) page item(s) with open path(s) is selected. Need not be in path selection mode.
			*/
		virtual bool16 CanJoinPoints(void) const = 0;	
	
		/**	Can connect selected points? Path(s) must be open. 
			@param none
			@return bool16 Returns kTrue when one (or two) page item(s) with open path(s) is selected. Need not be in path selection mode.
			*/
		virtual bool16 CanConnectPoints(void) const = 0;	

		/** Convert selected page item shape
			@param convertTo ShapeType the selected pageitem want convert to
			@param cornerEffect ClassID of stroke corner effects for the converted page item
			@param cornerRadius PMReal radius value in points for stroke corner effects for the converted page item
			@param numSides number of sides of polygon for the selected pageitem to convert to,
								No effect if ShapeType is not kPolygonX 
			@param starInset amount of star inset for the selected pageitem to convert to,
								No effect if ShapeType is not kPolygonX 
			@return ErrorCode 
		 */
		virtual ErrorCode ConvertPageItemShape(ShapeType convertTo, const ClassID cornerEffect = kInvalidClass, const PMReal& cornerRadius = 12.0, const int32 numSides = 6, const int32 starInset = 0) = 0;

		/** Convert selected point type
			@param convertTo new PointType the selected point want convert to
			@return ErrorCode 
			*/
		virtual ErrorCode ConvertPointType(PointType convertTo) = 0;

		/** Join selected two end points (and replace with a single point)
			@return ErrorCode 
			*/
		virtual ErrorCode JoinPoints(void) = 0;
		
		/** Connect two selected end points with a segment.
			@return ErrorCode 
			*/
		virtual ErrorCode ConnectPoints(void) = 0;
			 
	};

DECLARE_BASE_TYPE(IConvertShapeSuite::PointType);

#endif // __IConvertShapeSuite__
