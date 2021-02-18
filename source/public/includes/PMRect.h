//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PMRect.h $
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
#ifndef __PMRECT__
#define __PMRECT__

#include "PMReal.h"
#include "PMPoint.h"

//----------------------------------------------------------------------------------------
// Forward declarations
//----------------------------------------------------------------------------------------
class PMRect;
class IPMStream;
class PMMatrix;
namespace dvacore {
  namespace geom {
    template <class T> class RectT;
  }
}

//----------------------------------------------------------------------------------------
// Typedefs
// The following types are designed primarily for use in parameter lists to aid in
// determining what coordinate space a method or function expects a parameter to be in.
// They are just synonyms for PMRect
//----------------------------------------------------------------------------------------
typedef PMRect PBPMRect;		// rect in "Pasteboard" coordinates
typedef PMRect IPMRect;		// rect in "Inner" coordinates of page item
typedef K2Vector<PMRect> PMRectCollection;

#ifdef PUBLIC_BUILD
#pragma export on
#endif

extern PUBLIC_DECL const PMRect kEmptyRect;


PUBLIC_DECL SysRect ToSys(const PMRect& r);			
PUBLIC_DECL bool16 Intersect(const PMRect& r1, const PMRect& r2);
PUBLIC_DECL bool16 Intersect(const PMRect& r1, const PMMatrix& r1_to_r2_xform, const PMRect& r2);
PUBLIC_DECL PMRect MakeIntersect(const PMRect& r1, const PMMatrix& r1_to_r2_xform, const PMRect& r2);
PUBLIC_DECL bool16 IntersectOrAbut(const PMRect& r1, const PMRect& r2);
PUBLIC_DECL bool16 IntersectOrAbut(const PMRect& r1, const PMMatrix& r1_to_r2_xform, const PMRect& r2);
PUBLIC_DECL PMRect MakeIntersectOrAbut(const PMRect& r1, const PMMatrix& r1_to_r2_xform, const PMRect& r2);
PUBLIC_DECL PMRect Intersection(const PMRect& r1, const PMRect& r2, const PMRect& emptyRect = kEmptyRect);
PUBLIC_DECL PMRect IntersectionOrAbut(const PMRect& r1, const PMRect& r2, const PMRect& emptyRect = kEmptyRect);
PUBLIC_DECL PMRect Union(const PMRect& r1, const PMRect& r2);
PUBLIC_DECL bool16 UnionIsRect(const PMRect& r1, const PMRect& r2);
//find a rectangle of greatest area centered and contained within the parallelogram formed by transforming rectangle r with matrix m.
PUBLIC_DECL PMRect MaximalInscribedRectangle( const PMRect& r, const PMMatrix& m);
//return the area of r2 contained in the parallelogram you get when r1 is transformed by r1_to_r2_xform
PUBLIC_DECL PMReal IntersectionArea( const PMRect& r1, const PMMatrix& r1_to_r2_xform, const PMRect& r2);

//----------------------------------------------------------------------------------------
// PMRect
//----------------------------------------------------------------------------------------

/**
 Simple rectangle type
 
 @see PMReal
 @see PMPoint
 */
class PUBLIC_DECL PMRect
{
	public:
		typedef base_type data_type;
		
		/**
		 Point types in a PMRect
		 */
		enum PointIndex {
			/// An invalid point index
			kInvalidPoint	= -1,
			/// The first valid point index
			kFirstPoint 	= 0,
			
			/// The point at the middle of the rectangle's top segment
			kMiddleTop		= 0,
			/// The point at the middle of the rectangle's left segment
			kLeftMiddle		= 1,
			/// The point at the middle of the rectangle's bottom segment
			kMiddleBottom	= 2,
			/// The point at the middle of the rectangle's right segment
			kRightMiddle	= 3,
			
			/// The left-top corner point
			kLeftTop		= 4,
			/// The right-top corner point
			kRightTop		= 5,
			/// The right-bottom corner point
			kRightBottom	= 6,
			/// The left-bottom corner point
			kLeftBottom		= 7,
			
			/// The point at the center of the rectangle
			kCenter			= 8,
			
			/// The last valid point index
			kLastPoint		= kCenter
		}; 
		
		/**
		 Constructs an empty PMRect situated at origin. The resulting rectangle
		 has its components all set to zero and has zero width and height.
		 */
        constexpr PMRect() noexcept : left(0.0), top(0.0), right(0.0), bottom(0.0)
        {
        }
		
		/**
		 Constructs an empty PMRect situated at the specified point. The 
		 rectangle's left and right are set to point's X component, and its
		 top and bottom are set to point's Y component.
		 
		 @param point	IN The point at which the rectangle is situated
		 */
		explicit PMRect(const PMPoint& point) noexcept;
		
		/**
		 Constructs a PMRect with the specified opposing corners.
		 
		 @param one_corner		IN One corner of the rectangle
		 @param opposing_corner		IN The corner of the rectangle opposite one_corner
		 */
		PMRect(const PMPoint& one_corner, const PMPoint& opposing_corner) noexcept;
		
		/**
		 Constructs a PMRect with the specified top-left and bottom-right.
		 Note since the constructed rectangle is normalized, l and r can
		 be passed in swapped, as can t and b.
		 @param l		IN The left component for the rectangle
		 @param t		IN The top component for the rectangle
		 @param r		IN The right component for the rectangle
		 @param b		IN The bottom component for the rectangle
		 */
		PMRect(const PMReal& l, const PMReal& t, const PMReal& r, const PMReal& b) noexcept;
		
		/**
		 Constructs a PMRect based on the specified system rectangle.
		 
		 @param r		IN The system rectangle on which the rectangle is based
		 */
		PMRect(const SysRect& r) noexcept;


		/**
		 Constructs a PMRect based on the drover rectangle.
		 
		 @param r		IN The drover rectangle on which the rectangle is based
		 */
		explicit PMRect( const dvacore::geom::RectT<float>& r) noexcept;


#if MACINTOSH //on Windows, an Int32Rect is a SysRect

		/**
		 Constructs a PMRect based on an Int32Rect rectangle.
		 
		 @param r		IN The Int32Rect rectangle on which the rectangle is based
		 */
		explicit PMRect( const Int32Rect& r) noexcept;
#endif

        constexpr PMRect(const PMRect &) noexcept = default;
        constexpr PMRect(PMRect &&) noexcept = default;
        PMRect &operator =(const PMRect &) noexcept = default;
        PMRect &operator =(PMRect &&) noexcept = default;
    
		// Outbound Conversions
		
		/**
		 Converts a PMRect to a system rectangle
		 
		 @param r		IN The PMRect to convert
		 @return The equivalent system rectangle
		 */
		friend PUBLIC_DECL SysRect ToSys(const PMRect& r);			

		/**
		 Converts a PMRect to a drover rectangle
		 
		 @param r		IN The PMRect to convert
		 @return The equivalent drover rectangle
		 */
		friend PUBLIC_DECL dvacore::geom::RectT<float> ToRectF32_(const PMRect& r);


		/**
		 Converts a PMRect to a Int32Rect rectangle
		 
		 @param r		IN The PMRect to convert
		 @return The equivalent Int32Rect rectangle
		 */
		friend PUBLIC_DECL Int32Rect ToInt32Rect_(const PMRect& r);


		// Query Methods
		
		/**
		 Determines whether rectangle is empty. A rectangle is empty if its
		 left and right or top and bottom components are equal.
		 
		 @return kTrue if the rectangle is empty, else kFalse
		 */
		bool16 IsEmpty() const noexcept;
		
		/**
		 Determines whether specified point index identifies a corner point.
		 
		 @param whichPoint	IN The point index to test
		 */
		bool16 IsCorner(PointIndex whichPoint) const noexcept;
		
		/**
		 Determines whether specified point index identifies a middle point.
		 
		 @param whichPoint	IN The point index to test
		 */
		bool16 IsMiddle(PointIndex whichPoint) const noexcept;

		/**
		 Determines whether the specified point falls within this rectangle
		 
		 @param pt			IN The point to test
		 @return kTrue if the point falls within the rectangle, else kFalse
		 */
		bool16 PointIn(const PMPoint& pt) const noexcept;

		/**
		 Determines whether the specified point falls within this rectangle
		 or on its border.  Unlike PointIn, ContainsPoint uses exact machine
		 double comparisons, not fuzzy PMReal comparisons.
		 
		 @param pt			IN The point to test
		 @return kTrue if the point falls within the rectangle, else kFalse
		 */
		bool16 ContainsPoint(const PMPoint& pt) const noexcept;
		
		/**
		 Determines whether the passed in rectangle r is contained with 'this'
		 rectangle.
		 
		 @param r			IN The rectangle to test
		 @return kTrue if the rectangle r is contained with this rectangle, else kFalse
		 */
		bool16 RectIn(const PMRect& r) const noexcept;

		/**
		 Determines whether the passed in rectangle r is contained with 'this'
		 rectangle. Unlike RectIn, ContainsRect uses exact machine
		 double comparisons, not fuzzy PMReal comparisons.
		 
		 @param r			IN The rectangle to test
		 @return kTrue if the rectangle r is contained with this rectangle, else kFalse
		 */
		bool16 ContainsRect( const PMRect& r) const noexcept;

		/**
		 Determines whether the passed in rectangle r when transformed by r_to_this_xform
		 is contained with 'this' rectangle.
		 
		 @param r			IN The rectangle to test
		 @param r_to_this_xform			IN the matrix that brings r into the coordinate space of this
		 @return kTrue if the rectangle r is contained with this rectangle, else kFalse
		 */
		bool16 ContainsRect( const PMRect& r, const PMMatrix& r_to_this_xform) const;
		
		/**
		 Calculates the aspect ratio for the rectangle. The aspect ratio is 
		 calculated as the ratio of the rectangle's height to its width. If the
		 rectangle is empty, zero is returned.
		 
		 @return The aspect ratio for the rectangle
		 */		 
		PMReal AspectRatio() const;
		
		/**
		 Calculates the distance from the specified point to one of the 
		 rectangle's edges.
		 
		 @param pt			IN The point to test
		 @return The distance from the specified point to the rectangle
		 */
		PMReal DistanceTo(const PMPoint& pt) const;
		
		/**
		 Determines if two rectangles intersect. True if rectangles intersect 
		 in both x and y directions, but false if only a side is shared (ie.,
		 rectangles must strictly intersect).
		 
		 @param r1			IN The first rectangle to test
		 @param r2			IN The second rectangle to test
		 @return kTrue if the two rectangles strictly intersect, else kFalse
		 */
		friend PUBLIC_DECL bool16 Intersect(const PMRect& r1, const PMRect& r2);
		friend PUBLIC_DECL bool16 Intersect_exact( const PMRect&r1, const PMRect& r2);
		friend PUBLIC_DECL bool16 Intersect(const PMRect& r1, const PMMatrix& xform, const PMRect& r2);
		friend PUBLIC_DECL PMRect MakeIntersect(const PMRect& r1, const PMMatrix& xform, const PMRect& r2);

		/**
		 Determines if two rectangles intersect or abut. True if rectangles 
		 intersect in both x and y directions or if they share a side.
		 
		 @param r1			IN The first rectangle to test
		 @param r2			IN The second rectangle to test
		 @return kTrue if the two rectangles intersect or abut, else kFalse
		 */
		friend PUBLIC_DECL bool16 IntersectOrAbut(const PMRect& r1, const PMRect& r2);
		friend PUBLIC_DECL bool16 IntersectOrAbut_exact(const PMRect&r1, const PMRect& r2);
		friend PUBLIC_DECL bool16 IntersectOrAbut(const PMRect& r1, const PMMatrix& xform, const PMRect& r2);
		friend PUBLIC_DECL PMRect MakeIntersectOrAbut(const PMRect& r1, const PMMatrix& xform, const PMRect& r2);
		
		/**
		 Calculates the intersection of two rectangles. If the rectangles do not
		 strictly intersect, the specified empty rectangle is returned.
		 
		 @param r1			IN The first rectangle to intersect
		 @param r2			IN The second rectangle to intersect
		 @param emptyRect	IN Used as return value if rectangles do not intersect
		 @return The intersection of the two rectangles, or an empty rectangle
		 */
		friend PUBLIC_DECL PMRect Intersection(const PMRect& r1, const PMRect& r2, const PMRect& emptyRect);

		/**
		 Calculates the intersection of two rectangles. The rectangles do not
		 need to strictly intersect, but may abut. If the two rectangles do not
		 intersect or abut, the specified empty rectangle is returned.
		 
		 @param r1			IN The first rectangle to intersect
		 @param r2			IN The second rectangle to intersect
		 @param emptyRect	IN Used as return value if rectangles do not intersect or abut
		 @return The intersection of the two rectangles, or an empty rectangle
		 */
		friend PUBLIC_DECL PMRect IntersectionOrAbut(const PMRect& r1, const PMRect& r2, const PMRect& emptyRect);

		// Accessor Methods
		
		/** 
		 Returns a const reference to the rectangle's left component.
		 
		 @return The rectangle's left component
		 */
		const PMReal& Left() const noexcept;
		
		/** 
		 Returns a reference to the rectangle's left component.
		 
		 @return The rectangle's left component
		 */
		PMReal& Left() noexcept;

		/** 
		 Sets the rectangle's left component.
		 
		 @param c	IN The rectangle's new left component
		 */
		void Left(const PMReal& c) noexcept;
		
		/** 
		 Returns a const reference to the rectangle's top component.
		 
		 @return The rectangle's top component
		 */
		const PMReal& Top() const noexcept;

		/** 
		 Returns a reference to the rectangle's top component.
		 
		 @return The rectangle's top component
		 */
		PMReal& Top() noexcept;

		/** 
		 Sets the rectangle's top component.
		 
		 @param c	IN The rectangle's new top component
		 */
		void Top(const PMReal& c) noexcept;
		
		/** 
		 Returns a const reference to the rectangle's right component.
		 
		 @return The rectangle's right component
		 */
		const PMReal& Right() const noexcept;

		/** 
		 Returns a reference to the rectangle's right component.
		 
		 @return The rectangle's right component
		 */
		PMReal& Right() noexcept;

		/** 
		 Sets the rectangle's right component.
		 
		 @param c	IN The rectangle's new right component
		 */
		void Right(const PMReal& c) noexcept;
		
		/**
		 Returns a const reference to the rectangle's bottom component.
		 
		 @return The rectangle's bottom component
		 */
		const PMReal& Bottom() const noexcept;

		/**
		 Returns a reference to the rectangle's bottom component.
		 
		 @return The rectangle's bottom component
		 */
		PMReal& Bottom() noexcept;

		/** 
		 Sets the rectangle's bottom component.
		 
		 @param c	IN The rectangle's new bottom component
		 */
		void Bottom(const PMReal& c) noexcept;
		
		/**
		 Returns the rectangle's top-left point.
		 
		 @return The rectangle's top-left point
		 */
		PMPoint LeftTop(void) const noexcept;

		/**
		 Sets the rectangle's top-left point.
		 
		 @param pt	IN The rectangle's new top-left point
		 */
		void LeftTop(const PMPoint& pt) noexcept;
		
		/**
		 Returns the rectangle's bottom-right point.
		 
		 @return The rectangle's bottom-right point
		 */
		PMPoint RightBottom(void) const noexcept;

		/**
		 Sets the rectangle's bottom-right point.
		 
		 @param pt	IN The rectangle's new bottom-right point
		 */
		void RightBottom(const PMPoint& pt) noexcept;
		
		/**
		 Returns the rectangle's top-right point.
		 
		 @return The rectangle's top-right point
		 */
		PMPoint RightTop(void) const noexcept;

		/**
		 Sets the rectangle's top-right point.
		 
		 @param pt	IN The rectangle's new top-right point
		 */
		void RightTop(const PMPoint& pt) noexcept;
		
		/**
		 Returns the rectangle's bottom-left point.
		 
		 @return The rectangle's bottom-left point
		 */
		PMPoint LeftBottom(void) const noexcept;

		/**
		 Sets the rectangle's bottom-left point.
		 
		 @param pt	IN The rectangle's new bottom-left point
		 */
		void LeftBottom(const PMPoint& pt) noexcept;
		
		/**
		 Returns the height of the rectangle.
		 
		 NOTE: This assumes the rect is normalized.
		 
		 @return The height of the rectangle
		 */
		PMReal Height() const noexcept;

		/**
		 Returns the width of the rectangle.
		 
		 NOTE: This assumes the rect is normalized.
		 
		 @return The width of the rectangle
		 */
		PMReal Width() const noexcept;

		/**
		 Returns the dimensions of the rectangle as a PMPoint.
		 
		 NOTE: This assumes the rect is normalized.
		 
		 @return The dimensions of the rectangle
		 */
		PMPoint Dimensions() const noexcept;
		
		/**
		 Sets the height of the rectangle by adjusting its bottom component.
		 The height is assumed to be positive.
		 
		 @param height		IN The new height for the rectangle
		 */
		void SetHeight(const PMReal& height);
		
		/**
		 Sets the width of the rectangle by adjusting its right component.
		 The width is assumed to be positive.
		 
		 @param width		IN The new width for the rectangle
		 */
		void SetWidth(const PMReal& width);

		/**
		 Sets the dimensions of the rectangle by adjusting its bottom and right
		 components. The width and height are assumed to be positive.
		 
		 @param width		IN The new width for the rectangle
		 @param height		IN The new height for the rectangle
		 */
		void SetDimensions(const PMReal& width, const PMReal& height);
		
		/**
		 Returns the horizontal center of the rectangle.
		 
		 @return The horizontal center of the rectangle
		 */
		PMReal GetHCenter() const;

		/**
		 Returns the vertical center of the rectangle.
		 
		 @return The vertical center of the rectangle
		 */
		PMReal GetVCenter() const;

		/**
		 Returns the center of the rectangle.
		 
		 @return The center of the rectangle
		 */
		PMPoint GetCenter() const;
	
		/**
		 Retrieves the specified point in the rectangle.
		 
		 @return The specified point
		 */
		PMPoint GetPoint(PointIndex whichPoint) const;
		
		/**
		 Retrieves the point index for the specified point. If the point does
		 not correspond to any of enumerated points, kInvalidPoint is returned.
		 
		 @param aPoint	IN The point to test
		 @return The index of the point, or kInvalidPoint if the point doesn't match any of the enumerated indices
		 */
		PointIndex GetPointIndex(const PMPoint& aPoint) const;
		
		/**
		 Retrieves the point opposite to the specified point in the rectangle.
		 
		 @return The point opposite the specified point
		 */
		PMPoint GetOppositePoint(PointIndex whichPoint) const;
		
		/**
		 Retrieves the index of the point opposite the specified point in the 
		 rectangle.
		 
		 @param whichPoint	IN The index of the point whose opposite is to be returned
		 @return The index of the point opposite the specified point index
		 */
		PointIndex GetOppositePointIndex(PointIndex whichPoint) const;
			
		// Manipulation Methods
		
		/**
		 Makes the rectangle empty by setting its right and bottom components
		 equal to its left and top components, respectively.
		 
		 @return A reference to this rectangle
		 */
		PMRect& SetEmpty() noexcept;
		
		/**
		 Normalizes this rectangle so that its right component is greater than
		 its left, and its bottom greater than its top.
		 
		 @return kTrue if the components of the rectangle were adjusted during normalization, else kFalse if it was already normalized
		 */
		bool16 Normalize() noexcept;
		
		/**
		 Adjusts the components of the rectangle by rounding them to the 
		 nearest integer value.
		 
		 @return A reference to this rectangle
		 */
		PMRect& Round();
		
		/**
		 Moves the given point to the new location and returns the (possibly 
		 changed) index of the moved point.
		 
		 NOTE: MidPoints will only move perpendicular to their side of the 
		 rectangle. Only the height or width will change, not both.
		 
		 @param whichPoint		IN The index of the point to move
		 @param toPt			IN The new location for the specified point
		 @return The index of the moved point
		 */
		PointIndex MovePointTo(PointIndex whichPoint, const PMPoint& toPt);

		PMRect& MoveRel(const PMReal& dx, const PMReal& dy);
		PMRect& MoveRel(const PMPoint& point);
		PMRect& MoveTo(const PMReal& dx, const PMReal& dy);
		PMRect& MoveTo(const PMPoint& point);
		PMRect& CenterOn(const PMReal& dx, const PMReal& dy);
		PMRect& CenterOn(const PMPoint& point);
		
		/**
		 Contracts the rectangle by (dx, dy) on all sides. Positive values 
		 contract the rectangle, negative values enlarge it.
		 
		 @param dx			IN The amount by which the left and right components are adjusted
		 @param dy			IN The amount by which the top and bottom components are adjusted
		 @return A reference to this rectangle
		 */
		PMRect& Inset(const PMReal& dx, const PMReal& dy);
	
		/**
		 Constrains the specified rectangle to the bounds of this rectangle.
		 
		 @param constrainedRect	IN/OUT The rectangle to be constrained
		 @return kTrue if any of the input rectangle's components were changed, else kFalse if it was already constrained
		 */
		bool16 ConstrainTo(PMRect& constrainedRect);
	
		/**
		 Unions this rectangle with another.
		 Note this member function differs from the friend Union(r1, r2) declared
		 below in the behavior of rectangles with zero-area (those for which IsEmpty()
		 returns true). This member function deliberately ignores any contribution from 
		 zero-area rectangles. So if rhs.IsEmpty(), then Union returns immediately with
		 *this not modified. Otherwise if this->IsEmpty(), then rhs is copied to *this.
		 Otherwise *this is extended to be the smallest rectangle enclosing rhs and the
		 current value of *this. Contrast this with the quite different behavior toward
		 zero-area rectangles used by the friend function described below.
		 Consider the following example:
			PMRect justOrigin(); //left == top == right == bottom == 0
			PMRect justSegment(1,-1,3,-1); //just a line segment from (1,-1) to (3,-1)
			PMRect someArea(1,1,2,2); //a square
			someArea.Union(justSegment);
			someArea.Union(justOrigin);
		 Here someArea would not have changed from its constructed value.
		 Contrast that with the example for the friend function.
		 
		 @param rhs			IN The rectangle with which this one is unioned
		 */
		void Union (const PMRect& rhs);
		
		/**
		 Expands this rectangle so that it is large enough to contain the 
		 specified point. Identical to Union with a rectangle that encompasses 
		 the point.
		 
		 @param pt			IN The point used in the expansion
		 */
		void Expand (const PMPoint& pt);
		
		/**
		 Union two rectangles together, returning the resulting rectangle.
		 Note this friend function differs from the member Union(rhs) declared
		 above in the behavior of rectangles with zero-area (those for which IsEmpty()
		 returns true). In partcular, r1 and r2 are never considered empty--even
		 if they enclose zero-area. So be careful. Consider the following example:
			PMRect justOrigin(); //left == top == right == bottom == 0
			PMRect justSegment(1,-1,3,-1); //just a line segment from (1,-1) to (3,-1)
			PMRect someArea(1,1,2,2); //a square
			PMRect result = Union( Union(someArea, justSegment), justOrigin);
		 Here result would be left == 0, top == -1, right == 3, bottom == 2.
		 Contrast that with the example for the member function.

		 @param r1			IN The first rectangle to union
		 @param r2			IN The second rectangle to union
		 @return The union of the two rectangles
		 */
		friend PUBLIC_DECL PMRect Union(const PMRect& r1, const PMRect& r2);
		friend PUBLIC_DECL bool16 UnionIsRect(const PMRect& r1, const PMRect& r2);
	
		// Comparison Operators
		
		/**
		 Compares two rectangles for equality. All four components must match.
		 
		 Note: This implicitly uses an epsilon comparison.
		 
		 @param a			IN The first rectangle to compare
		 @param b			IN The second rectangle to compare
		 @return kTrue if the components of the two rectangles match, else kFalse
		 */
		friend PUBLIC_DECL bool16 operator ==(const PMRect& a, const PMRect& b) noexcept;
		
		/**
		 Compares two rectangles for inequality.
		 
		 Note: This implicitly uses an epsilon comparison.
		 
		 @param a			IN The first rectangle to compare
		 @param b			IN The second rectangle to compare
		 @return kTrue if any of the components of the two rectangles do not match, else kFalse
		 */
		friend PUBLIC_DECL bool16 operator !=(const PMRect& a, const PMRect& b) noexcept;

		// Utility functions
		
		/**
		 Converts a PointIndex into an integer. Used internally in some 
		 hit-testing code. Probably not useful for third-party developers.
		 
		 @param ptIndex		IN The point index to convert
		 @return The point index as an integer value
		 */
		static int32 PointIndexToIndex (PMRect::PointIndex ptIndex);

		/**
		 Converts an integer into a PointIndex. Used internally in some 
		 hit-testing code. Probably not useful for third-party developers.
		 
		 @param index		IN The integer value to convert
		 @return The integer as a point index
		 */
		static PMRect::PointIndex IndexToPointIndex (int32 index);
		
		// Streaming
		
		/**
		 Persists this rectangle to the specified stream
		 
		 @param iPMStream		IN The stream to which the rectangle's components are written
		 */
		void ReadWrite (IPMStream* iPMStream);
		
//		VC6 compiler error, CWE
#if (_MSC_VER >= 1200)	// VC6 or greater
	public:
#else
	private:
#endif
		PMReal left;
		PMReal top;
		PMReal right;
		PMReal bottom;
		friend bool16 Intersect_( const PMRect& r1, const PMMatrix& r1_to_r2_xform, const PMRect& r2, PMPoint* p);
		friend bool16 IntersectOrAbut_( const PMRect& r1, const PMMatrix& r1_to_r2_xform, const PMRect& r2, PMPoint* p);

};


#pragma export off

//----------------------------------------------------------------------------------------
// Inlines:
//----------------------------------------------------------------------------------------

inline bool16 PMRect::IsEmpty() const noexcept
{
	return ((left == right) || (top == bottom));
}
			
inline bool16 PMRect::IsCorner(PointIndex whichPoint) const noexcept
{
	ASSERT_MSG(whichPoint >= kFirstPoint && whichPoint <= kLastPoint, "PMRect::IsCorner - whichPoint >= kFirstPoint && whichPoint <= kLastPoint");
	return (whichPoint >= kLeftTop && whichPoint != kCenter);
}

inline bool16 PMRect::IsMiddle(PointIndex whichPoint) const noexcept
{
	ASSERT_MSG(whichPoint >= kFirstPoint && whichPoint <= kLastPoint, "PMRect::IsMiddle - whichPoint >= kFirstPoint && whichPoint <= kLastPoint");
	return (whichPoint >= kMiddleTop && whichPoint <= kRightMiddle);
}

inline bool16 PMRect::PointIn(const PMPoint& pt) const noexcept
{
	return (pt.x >= left) && (pt.x <= right) && (pt.y >= top)  && (pt.y <= bottom);
}

inline bool16 PMRect::ContainsPoint(const PMPoint& pt) const noexcept
{
	return 
		::ToDouble(pt.x) >= ::ToDouble(left)
	&&  ::ToDouble(pt.x) <= ::ToDouble(right)
	&&  ::ToDouble(pt.y) >= ::ToDouble(top)
	&&  ::ToDouble(pt.y) <= ::ToDouble(bottom);
}


inline bool16 PMRect::RectIn(const PMRect& r) const noexcept
{
	return (top <= r.top && bottom >= r.bottom) && (left <= r.left && right >= r.right);
}

inline bool16 PMRect::ContainsRect(const PMRect& r) const noexcept
{
	return
		::ToDouble(top) <= ::ToDouble(r.top)
	&&  ::ToDouble(bottom) >= ::ToDouble(r.bottom)
	&&  ::ToDouble(left) <= ::ToDouble(r.left)
	&&  ::ToDouble(right) >= ::ToDouble(r.right);
}

inline const PMReal& PMRect::Left() const noexcept
{
	return left;
}
			
inline PMReal& PMRect::Left() noexcept
{
	return left;
}

inline void PMRect::Left(const PMReal& c) noexcept
{
	left = c;
}
			
inline const PMReal& PMRect::Top() const noexcept
{
	return top;
}
			
inline PMReal& PMRect::Top() noexcept
{
	return top;
}

inline void PMRect::Top(const PMReal& c) noexcept
{
	top = c;
}
			
inline const PMReal& PMRect::Right() const noexcept
{
	return right;
}
			
inline PMReal& PMRect::Right() noexcept
{
	return right;
}

inline void PMRect::Right(const PMReal& c) noexcept
{
	right = c;
}
			
inline const PMReal& PMRect::Bottom() const noexcept
{
	return bottom;
}
			
inline PMReal& PMRect::Bottom() noexcept
{
	return bottom;
}

inline void PMRect::Bottom(const PMReal& c) noexcept
{
	bottom = c;
}
			
inline PMPoint PMRect::LeftTop() const noexcept
{
	return PMPoint(left, top);
}
			
inline void PMRect::LeftTop(const PMPoint& pt) noexcept
{
 	left = pt.X(); top = pt.Y();
}
			
inline PMPoint PMRect::RightBottom() const noexcept
{
	return PMPoint(right, bottom);
}
			
inline void PMRect::RightBottom(const PMPoint& pt) noexcept
{
 	right = pt.X(); bottom = pt.Y();
}

inline PMPoint PMRect::RightTop() const noexcept
{
	return PMPoint(right, top);
}
			
inline void PMRect::RightTop(const PMPoint& pt) noexcept
{
 	right = pt.X(); top = pt.Y();
}
			
inline PMPoint PMRect::LeftBottom() const noexcept
{
	return PMPoint(left, bottom);
}
			
inline void PMRect::LeftBottom(const PMPoint& pt) noexcept
{
 	left = pt.X(); bottom = pt.Y();
}
			
inline PMReal PMRect::Height() const noexcept
{
	return bottom - top;
}
			
inline PMReal PMRect::Width() const noexcept
{
	return right  - left;
}

inline PMPoint PMRect::Dimensions() const noexcept
{
	return PMPoint(Width(), Height());
}
			
inline PMRect::PointIndex PMRect::GetOppositePointIndex(PointIndex whichPoint) const
{
	return (whichPoint == kCenter) ? kCenter :
		PointIndex((whichPoint + 2) % 4 + (IsCorner(whichPoint) ? 4 : 0));
}
			
			
inline PMPoint PMRect::GetOppositePoint(PointIndex whichPoint) const
{
	return GetPoint(GetOppositePointIndex(whichPoint));
}
			

inline PMRect& PMRect::SetEmpty() noexcept
{
	right = left;
	bottom = top;
	
	return *this;
}

inline PMRect& PMRect::MoveRel(const PMReal& dx, const PMReal& dy)
{
	left += dx; right += dx; top += dy; bottom += dy;
	return *this;
}

inline PMRect& PMRect::MoveRel(const PMPoint& point)
{
	MoveRel(point.X(), point.Y());
	return *this;
}

inline PMRect& PMRect::MoveTo(const PMReal& dx, const PMReal& dy)
{
	 right += (dx - left); bottom += (dy - top); left = dx; top = dy;
	 return *this;
}

inline PMRect& PMRect::MoveTo(const PMPoint& point)
{
	MoveTo(point.X(), point.Y());
	return *this;
}

inline PMRect& PMRect::CenterOn(const PMPoint& point)
{
	CenterOn(point.X(), point.Y());
	return *this;
}

inline PMRect& PMRect::Inset(const PMReal& dx, const PMReal& dy)
{
	left += dx; top += dy; right -= dx; bottom -= dy;
	return *this;
}

inline bool16 operator ==(const PMRect& a, const PMRect& b) noexcept
{
	return (a.left == b.left && a.top == b.top && a.right == b.right && a.bottom == b.bottom);
}

inline bool16 operator !=(const PMRect& a, const PMRect& b) noexcept
{
	return (a.left != b.left || a.top != b.top || a.right != b.right || a.bottom != b.bottom);
}

constexpr PMRect kZeroRect; //zeroed out in default constructor

#endif
