//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PMPoint.h $
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
#ifndef __PMPOINT__
#define __PMPOINT__

#include "PMReal.h"
#include "SystemUtils.h"
#include "K2Vector.h"

//----------------------------------------------------------------------------------------
// Forward declarations
//----------------------------------------------------------------------------------------
class PMPoint;
class PMRect;
class IPMStream;

//----------------------------------------------------------------------------------------
// Typedefs
// The following types are designed primarily for use in parameter lists to aid in
// determining what coordinate space a method or function expects a parameter to be in.
// They are just synonyms for PMPoint
//----------------------------------------------------------------------------------------
typedef PMPoint PBPMPoint;		// point in "Pasteboard" PMRealinates
typedef PMPoint IPMPoint;		// point in "Inner" PMRealinates of page item
typedef K2Vector<PMPoint> PMPointList;
typedef K2Vector<PMPointList*> PMPointListCollection;

//----------------------------------------------------------------------------------------
// PMPoint
//----------------------------------------------------------------------------------------

// Math Operators
PMPoint operator +(const PMPoint& a, const PMPoint& b);
PMPoint operator -(const PMPoint& a, const PMPoint& b);
PMPoint operator -(const PMPoint& a);
PMPoint operator *(const PMReal& c, const PMPoint& pt);
PMPoint operator *(const PMPoint& pt, const PMReal& c);
PMPoint operator *(const PMPoint& a, const PMPoint& b);
PMPoint operator /(const PMPoint& numer, const PMPoint& denom);
PMPoint operator /(const PMPoint& numer, const PMReal& denom);

#pragma export on

/**
 Simple class for representing a point in InDesign. Also used to represent a 
 vector. Many of the operations supported by PMPoint interpret the point as a
 vector - PMPoints may be added together, multiplied by scalar values, have 
 their lengths taken, etc.
 
 @see PMReal
 */
class PMPoint
{
	public:
		typedef base_type data_type;
		
		/**
		 Default constructor. Initializes this point to the origin (0, 0).
		 */
		constexpr PMPoint() noexcept: x(0.0), y(0.0)
			{}
			
		/**
		 Copy/move constructor & assignments. Initializes this point to the same values as the
		 source point.
		 
		 @param aPoint		IN The point to copy
		 */
        constexpr PMPoint(const PMPoint &) noexcept = default;
        constexpr PMPoint(PMPoint &&) noexcept = default;
        PMPoint &operator =(const PMPoint &) noexcept = default;
        PMPoint &operator =(PMPoint &&) noexcept = default;
    
		/**
		 Constructs this point using specified PMReal x- and y-values.
		 
		 @param x_orig		IN The x-value for this point
		 @param y_orig		IN The y-value for this point
		 */
		constexpr PMPoint(const PMReal& x_orig, const PMReal& y_orig) noexcept : x(x_orig), y(y_orig)
			{}
			
		/**
		 Constructs this point from a system point.
		 
		 @param p			IN The system point this point is initialized to
		 */
		constexpr PMPoint(const SysPoint& p) noexcept: x(double(SysPointH(p))), y(double(SysPointV(p)))
			{}

		// Outbound Conversions
		
		/**
		 Converts a PMPoint to a system point.
		 
		 @param pt			IN The PMPoint to convert
		 @return The equivalent system point
		 */
		friend SysPoint ToSys(const PMPoint& pt);

		// Accessor Methods
		
		/**
		 Const-accessor for this point's x-value.
		 
		 @return Const reference to the point's x-value
		 */
		const PMReal& X() const noexcept
			{ return x; }
			
		/**
		 Non-const-accessor for this point's x-value.
		 
		 @return Non-const reference to this point's x-value
		 */
		PMReal& X() noexcept
			{ return x; }
			
		/**
		 Sets the x-value for this point.
		 
		 @param xParam		IN The new x-value for this point
		 */
		void X(const PMReal& xParam) noexcept
			{ x = xParam; }

		/**
		 Const-accessor for this point's y-value.
		 
		 @return Const reference to this point's y-value
		 */
		const PMReal& Y() const noexcept
			{ return y; }

		/**
		 Non-const-accessor for this point's y-value.
		 
		 @return Non-const reference to this point's y-value
		 */
		PMReal& Y() noexcept
			{ return y; }

		/**
		 Sets the y-value for this point.
		 
		 @param yParam		IN The new y-value for this point
		 */
		void Y(const PMReal& yParam) noexcept
			{ y = yParam; }

		/**
		 Returns the distance (a^2 + b^2 = c^2) from this point to the otherPt
		 
		 @param otherPt		IN The other point for the distance calculation
		 @return The scalar distance from this point to the other
		 */
		PMReal Distance (const PMPoint& otherPt) const
		{
			return (otherPt - *this).VectorLength();
		}

		/** 
		 Returns the length of the vector represented by this point
		 
		 @return The scalar length of this point, interpreted as a vector
		 */
		PMReal VectorLength() const
		{
			if( ::ToDouble(x) == 0.) //convert to double to get exact comparison
				return abs(y); //avoid roundof error from sqrt(y*y)
			if( ::ToDouble(y) == 0.)
				return abs(x); //avoid roundof error from sqrt(x*x)
			return PMReal(std::sqrt(::ToDouble(x*x + y*y)));
		}

		/**
		 Returns the angle (in degrees) of this point, interpreted as a vector
		 
		 @return The angle (in degrees) of this point, interpreted as a vector
		 */
		PUBLIC_DECL PMReal VectorAngle() const;
			
		/** 
		 Returns the mirror of this point, using the specified alignment point.
		 
		 @param aligningPoint	IN The point about which the mirror point is calculated
		 @return The mirror of this point
		 */
		PMPoint MirrorPoint(const PMPoint& aligningPoint) const
			{ return PMReal(2.0) * aligningPoint - *this; }

		/**
		 Projects this point to the line defined by pt0, ptA, keeping the 
		 distance to pt0 unchanged.
		 
		 @param pt0		IN The first point defining the line to project to
		 @param ptA		IN The second point defining the line to project to
		 @return The point, projected on to the line defined by pt0 and ptA
		 */
		PUBLIC_DECL PMPoint ProjectOnLine(const PMPoint& pt0, const PMPoint &ptA) const;

		// Math Operators
		
		/**
		 Adds two points: result = PMPoint(a.x + b.x, a.y + b.y)
		 
		 @param a		IN The first point to add
		 @param b		IN The second point to add
		 @return The sum of the two points
		 */
		friend PMPoint operator +(const PMPoint& a, const PMPoint& b);
		
		/**
		 Subtracts two points: result = PMPoint(a.x - b.x, a.y - b.y)
		 
		 @param a		IN The first point to subtract
		 @param b		IN The second point to subtract
		 @return The difference of the two points
		 */
		friend PMPoint operator -(const PMPoint& a, const PMPoint& b);
		
		/**
		 Negates a point: result = PMPoint(-a.x, -a.y)
		 
		 @param a		IN The point to negate
		 @return The negated point
		 */
		friend PMPoint operator -(const PMPoint& a);
		
		/**
		 Multiplies a point by a scalar: result = PMPoint(pt.x * c, pt.y * c)
		 
		 @param c		IN The scalar to multiply by
		 @param pt		IN The point to multiply by
		 @return The product of the point and the scalar
		 */
		friend PMPoint operator *(const PMReal& c, const PMPoint& pt);

		/**
		 Multiplies a point by a scalar: result = PMPoint(pt.x * c, pt.y * c)
		 
		 @param pt		IN The point to multiply by
		 @param c		IN The scalar to multiply by
		 @return The product of the point and the scalar
		 */
		friend PMPoint operator *(const PMPoint& pt, const PMReal& c);
		
		/**
		 Multiplies two points: result = PMPoint(a.x * b.x, a.y * b.y)
		 
		 @param a		IN The first point to multiply
		 @param b		IN The second point to multiply
		 @return The product of the two points
		 */
		friend PMPoint operator *(const PMPoint& a, const PMPoint& b);
		
		/**
		 Divides one point by another: result = PMPoint(numer.x / denom.x, numer.y / denom.y)
		 
		 @param numer	IN The numerator as a PMPoint
		 @param denom	IN The denomination as a PMPoint
		 @return The divided point
		 */
		friend PMPoint operator /(const PMPoint& numer, const PMPoint& denom);
		
		/**
		 Divides a point by a scalar: result = PMPoint(numer.x / denom, numer.y / denom)
		 
		 @param numer	IN The point being divided
		 @param denom	IN The scalar denominator
		 @return The divided point
		 */
		friend PMPoint operator /(const PMPoint& numer, const PMReal& denom);

		// Assignment Operators
		
		/**
		 Increments this point by the specified (vector) point
		 
		 @param a		IN The amount by which to increment (as a vector)
		 */
		void operator +=(const PMPoint& a)
			{ x += a.x; y += a.y; }

		/**
		 Decrements this point by the specified (vector) point
		 
		 @param a		IN The amount by which to decrement (as a vector)
		 */
		void operator -=(const PMPoint& a)
			{ x -= a.x; y -= a.y; }

		// Comparison Operators
		
		/**
		 Compares two points for equality. 
		 
		 @param a		IN First point to compare
		 @param b		IN Second point to compare
		 @return kTrue if x- and y-values match, else kFalse
		 */
		friend bool16 operator ==(const PMPoint& a, const PMPoint& b) noexcept;
		
		/**
		 Compares two points for inequality.
		 
		 @param a		IN First point to compare
		 @param b		IN Second point to compare
		 @return kTrue if x- and y-values do not match, else kFalse
		 */
		friend bool16 operator !=(const PMPoint& a, const PMPoint& b) noexcept;


		/**
			Define a partial ordering on PMPoints so they can
			be used in associative containers
		*/
		bool operator<( const PMPoint& rhs) const noexcept
		{
			return x == rhs.x
				? y < rhs.y
				: x < rhs.x;
		}



		// Manipulation Methods
		
		/**
		 Constrains this point to the specified rectangle
		 
		 @param r		IN The rectangle to constrain to
		 @return kTrue if this point was modified while being constrained, else kFalse if the point was already constrained
		 */
		PUBLIC_DECL bool16 ConstrainTo(const PMRect& r);
		
		/**
		 Rounds this point's x- and y-values.
		 */
		void Round()
			{ x = ::Round(x); y = ::Round(y); }

		// Streaming
		
		/**
		 Streams this point to an IPMStream. The point is written out if the
		 stream is writing, and is read in if the stream is reading.
		 
		 @param iPMStream	IN The stream to which this point is written or read
		 */
		PUBLIC_DECL void ReadWrite (IPMStream* iPMStream);

	private:
		PMReal x, y;
		friend class PMRect;
};

constexpr PMPoint kZeroPoint(0, 0);
constexpr PMPoint kInvalidPoint(kPMMaxReal, kPMMaxReal);

#pragma export off



//----------------------------------------------------------------------------------------
// operator +
//----------------------------------------------------------------------------------------

inline PMPoint operator +(const PMPoint& a, const PMPoint& b)
{
	return PMPoint(a.x + b.x, a.y + b.y);
}

//----------------------------------------------------------------------------------------
// operator -
//----------------------------------------------------------------------------------------

inline PMPoint operator -(const PMPoint& a, const PMPoint& b)
{
	return PMPoint(a.x - b.x, a.y - b.y);
}

//----------------------------------------------------------------------------------------
// operator -
//----------------------------------------------------------------------------------------

inline PMPoint operator -(const PMPoint& a)
{
	return PMPoint(-a.x, -a.y);
}

//----------------------------------------------------------------------------------------
// operator *
//----------------------------------------------------------------------------------------

inline PMPoint operator *(const PMReal& c, const PMPoint& pt)
{
	return PMPoint(c * pt.x, c * pt.y);
}

//----------------------------------------------------------------------------------------
// operator *
//----------------------------------------------------------------------------------------

inline PMPoint operator *(const PMPoint& pt, const PMReal& c)
{
	return PMPoint(c * pt.x, c * pt.y);
}

//----------------------------------------------------------------------------------------
// operator *
//----------------------------------------------------------------------------------------

inline PMPoint operator *(const PMPoint& a, const PMPoint& b)
{
	return PMPoint(a.x * b.x, a.y * b.y);
}

//----------------------------------------------------------------------------------------
// operator /
//----------------------------------------------------------------------------------------

inline PMPoint operator /(const PMPoint& numer, const PMPoint& denom)
{
	return PMPoint(numer.x/denom.x, numer.y/denom.y);
}

//----------------------------------------------------------------------------------------
// operator /
//----------------------------------------------------------------------------------------

inline PMPoint operator /(const PMPoint& numer, const PMReal& denom)
{
	return PMPoint(numer.x/denom, numer.y/denom);
}


//----------------------------------------------------------------------------------------
// PMPoint::operator ==
//----------------------------------------------------------------------------------------

inline bool16 operator ==(const PMPoint& a, const PMPoint& b) noexcept
{
	return a.x == b.x && a.y == b.y;
}

//----------------------------------------------------------------------------------------
// PMPoint::operator !=
//----------------------------------------------------------------------------------------

inline bool16 operator !=(const PMPoint& a, const PMPoint& b) noexcept
{
	return a.x != b.x || a.y != b.y;
}

inline SysPoint ToSys(const PMPoint& pt)
{
	SysPoint sysPt;
#if MACINTOSH
	// Convert to the native coordinate system, but keep the coordinates integral
	// (djb - this is assumed to happen in many places currently)
	SysPointH(sysPt) = ::ToFloat(::Floor(pt.x));
	SysPointV(sysPt) = ::ToFloat(::Floor(pt.y));
#else
	SysPointH(sysPt) = ToInt32(pt.x);
	SysPointV(sysPt) = ToInt32(pt.y);
#endif
	return sysPt;
}


#endif
