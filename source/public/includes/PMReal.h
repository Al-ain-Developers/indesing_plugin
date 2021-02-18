//========================================================================================
//
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PMReal.h $
//
//  Owner: jargast
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
#ifndef __PMReal__
#define __PMReal__

#include <math.h>

#include "K2Assert.h"

#ifdef WINDOWS
#include <stdio.h>
#include <float.h>
#endif

#if defined(DEBUG)
#include <limits>
#endif


constexpr double kPMRealEpsilon = 1.0e-8;
constexpr double kPMPi = 3.141592653589793238462643383279502884197169399375105820974944;
constexpr double kPMMaxReal = 8.9884656743115795e+307;


// NOTE: Code Generation 7/24/96
//
// MSFT VC is quite good at inlining things and produces code nearly
// identical to using doubles.
//
// MW's shipping compiler is not as good -- it seems to only inline
// one level deep so that an inline containing an inline is never
// expanded.  There are other compiler back ends for MW that we could
// try.




/**
 Simple wrapper class for a floating point value in InDesign. Analogous to a
 built-in C/C++ double.

 NOTE: Implicit type casting

 Implicit type casting has not been added to PMReal on purpose.
 Leaving out implicit type casting allows the compiler to make
 unambigous choices for math operations containing mixed types.
 Additionally, implicit type casting can be hazardous to your
 coding health, so instead we have provided explicit functions
 for conversion.

 NOTE: Constructor conversions

 We only have one constructor taking a double to avoid
 ambiguous calls.  This does mean that implicit conversion
 happens when going to a PMReal. Be careful in your code.
 To make the class at all useable it had to implicit conversion
 one direction or the other and we chose the constructor.

 NOTE: Why a class?

 Why are we using a class and not a double?  Primarily to hide
 the epsilon comparisons behind operator definitions.  It may
 also help us out in the future if we have to add anything -- It
 will be easier to add to this class than change from a typedef.
 */
class PMReal
{
// ----- Constructors/destructors
public:
	typedef base_type data_type;

	/**
	 default constructor. initialize to 0.0
	 */
	constexpr PMReal() noexcept : fRealValue(0.0)
	{
	}

	/**
	 Copy constructor.

	 @param other		IN The PMReal to initialize this object from
	 */
	constexpr PMReal(const PMReal& ) noexcept = default;
	constexpr PMReal(PMReal&&) noexcept = default;

	/**
	 Constructs this object from the specified double.

	 @param d			IN The value to initialize this object to
	 */
    constexpr PMReal(double d) noexcept : fRealValue(d)
    {
    }

	/**
	 Converts a fixed-point number to a PMReal. Fixed-point numbers use 16/16
	 bit format.

	 @param fx			IN The fixed-point number to convert
	 @return The fixed-point number as a PMReal
	 */
	friend PMReal ToPMReal(Fixed fx);

	// PMREALCLEANUP
	//operator double() { return fRealValue; }
	//operator const double&() const { return fRealValue; }

// ----- Conversion operators
	/**
	 Converts a PMReal to a double.

	 @param r			IN The PMReal to convert
	 @return The PMReal as a double
	 */
	friend  double	ToDouble(const PMReal& r) noexcept;

	/**
	 Converts a PMReal to a float.

	 @param r			IN The PMReal to convert
	 @return The PMReal as a float
	 */
	friend  float	ToFloat(const PMReal& r);

	/**
	 Converts a PMReal to a fixed-point number. Fixed-point numbers use 16/16
	 bit format.

	 @param r			IN The PMReal to convert
	 @return The PMReal as a fixed-point number
	 */
	friend  Fixed	ToFixed(const PMReal& r);

	/**
	 Converts a PMReal to an int16.

	 NOTE: This just casts the PMReal's value to an int16.

	 @param r			IN The PMReal to convert
	 @return The PMReal as an int16 value
	 */
	friend	int16	ToInt16(const PMReal& r);

	/**
	 Converts a PMReal to a uint16.

	 NOTE: This just casts the PMReal's value to a uint16.

	 @param r			IN The PMReal to convert
	 @return The PMReal as a uint16 value
	 */
	friend	uint16	ToUInt16(const PMReal& r);

	/**
	 Converts a PMReal to an int32.

	 NOTE: This just casts the PMReal's value to an int32.

	 @param r			IN The PMReal to convert
	 @return The PMReal as an int32 value
	 */
	friend	int32	ToInt32(const PMReal& r);

	/**
	 Converts a PMReal to a uint16.

	 NOTE: This just casts the PMReal's value to a uint32.

	 @param r			IN The PMReal to convert
	 @return The PMReal as an uint32 value
	 */
	friend	uint32	ToUInt32(const PMReal& r);

// ----- Math operators
	/**
	 Negates a PMReal.

	 @param a			IN The PMReal to negate
	 @return The negated PMReal
	 */
	friend  PMReal	operator -(const PMReal& a);

	/**
	 Adds two PMReals.

	 @param a			IN The first PMReal to add
	 @param b			IN The second PMReal to add
	 @return The sum of the two PMReals
	 */
	friend  PMReal	operator +(const PMReal& a, const PMReal& b);

	/**
	 Subtracts two PMReals.

	 @param a			IN The first PMReal to subtract
	 @param b			IN The second PMReal to subtract
	 @return The difference of the two PMReals
	 */
	friend  PMReal	operator -(const PMReal& a, const PMReal& b);

	/**
	 Multiplies two PMReals.

	 @param a			IN The first PMReal to multiply
	 @param b			IN The second PMReal to multiply
	 @return The sum of the two PMReals
	 */
	friend  PMReal	operator *(const PMReal& a, const PMReal& b);

	/**
	 Divides a PMReal by another.

	 @param a			IN The numerator
	 @param b			IN The denominator
	 @return The result of the division
	 */
	friend  PMReal	operator /(const PMReal& a, const PMReal& b);

// ----- Math functions
	/**
	 Rounds a PMReal to nearest integer value.

	 @param a			IN The PMReal to round
	 @return The rounded value
	 */
	friend  PMReal	Round(const PMReal& a);

	/**
	 Calculates floor of a PMReal by rounding down to integer value.

	 @param a			IN The PMReal to round
	 @return The result of the floor calculation
	 */
	friend  PMReal	Floor(const PMReal& a);

	/**
	 Calculates ceiling of a PMReal by rounding up to integer value.

	 @param a			IN The PMReal to round
	 @return The result of the ceiling calculation
	 */
	friend  PMReal	Ceiling(const PMReal& a);

	/**
	 Calculates absolute value of a PMReal.

	 @param a			IN The PMReal whose absolute value is calculated
	 @return The absolute value of the input value
	 */
	friend  PMReal	abs(const PMReal& a);

	/**
	 Calculates the nearest multiple of factor to a.

	 result = Round(a / factor) * factor

	 @param a			IN The number whose nearest multiple is to be calculated
	 @param factor		IN The factor to use in the calculation
	 @return The nearest multiple of factor to a
	 */
	friend  PMReal	NearestMultiple(const PMReal& a, const PMReal& factor);

	/**
	 Calculates modulo (floating point remainder) of two PMReals.

	 @param a			IN The numerator
	 @param b			IN The denominator
	 @return The modulo of the two input values
	 */
	friend  PMReal	Mod(const PMReal& a, const PMReal& b);

// ----- Assignment Operators
	/**
	 Assigns a value to this object.

	 @param c			IN The value to assign
	 @return A reference to this object, so assignments can be chained
	 */
	PMReal&	operator=(const PMReal &) noexcept = default;
	PMReal&	operator=(PMReal &&) noexcept = default;

	/**
	 Increments this object by a value.

	 @param a			IN The amount to increment by
	 @return A reference to this object, so assignments can be chained
	 */
	PMReal&	operator +=(const PMReal& a);

	/**
	 Decrements this object by a value.

	 @param a			IN The amount to decrement by
	 @return A reference to this object, so assignments can be chained
	 */
	PMReal&	operator -=(const PMReal& a);

	/**
	 Multiples this object by a value.

	 @param a			IN The amount to multiply by
	 @return A reference to this object, so assignments can be chained
	 */
	PMReal&	operator *=(const PMReal& a);

	/**
	 Divides this object by a value.

	 @param a			IN The amount to divide by
	 @return A reference to this object, so assignments can be chained
	 */
	PMReal&	operator /=(const PMReal& a);

// ----- Comparison Operators
	/**
	 Compare two PMReals for equality, using implicit epsilon.

	 @param a			IN The first PMReal to compare
	 @param b			IN The second PMReal to compare
	 @return kTrue if the values are equal, else kFalse
	 */
	friend  bool16	operator ==(const PMReal& a, const PMReal& b) noexcept;

	/**
	 Compare two PMReals for inequality, using implicit epsilon.

	 @param a			IN The first PMReal to compare
	 @param b			IN The second PMReal to compare
	 @return kTrue if the values are not equal, else kFalse if they're equal
	 */
	friend  bool16	operator !=(const PMReal& a, const PMReal& b) noexcept;

	/**
	 Determines if one PMReal is less than another, using implicit epsilon.

	 @param a			IN The first PMReal to compare
	 @param b			IN The second PMReal to compare
	 @return kTrue if first PMReal is less than the second, else kFalse
	 */
	friend  bool16	operator  <(const PMReal& a, const PMReal& b) noexcept;

	/**
	 Determines if one PMReal is greater than another, using implicit epsilon.

	 @param a			IN The first PMReal to compare
	 @param b			IN The second PMReal to compare
	 @return kTrue if first PMReal is greater than the second, else kFalse
	 */
	friend  bool16	operator  >(const PMReal& a, const PMReal& b) noexcept;

	/**
	 Determines if one PMReal is less than or equal to another, using implicit
	 epsilon.

	 @param a			IN The first PMReal to compare
	 @param b			IN The second PMReal to compare
	 @return kTrue if first PMReal is less than or equal to the second, else kFalse
	 */
	friend  bool16	operator <=(const PMReal& a, const PMReal& b) noexcept;

	/**
	 Determines if one PMReal is greater than or equal to another, using
	 implicit epsilon.

	 @param a			IN The first PMReal to compare
	 @param b			IN The second PMReal to compare
	 @return kTrue if first PMReal is greater than or equal to the second, else kFalse
	 */
	friend  bool16	operator >=(const PMReal& a, const PMReal& b) noexcept;

	/**
	 Convenience operator for comparing two angles (in degrees) with implicit
	 epsilon.

	 Note: For the purposes of the comparison treats 360 as equal to zero.

	 @param a			IN The first angle to compare
	 @param b			IN The second angle to compare
	 @return kTrue if the values are equal, else kFalse
	 */
	friend	bool16	AnglesEqual(const PMReal& a, const PMReal& b) noexcept;

	/**
	Function for comparing two PMReal values using a custom epsilon value.

	@param a			IN the first PMReal to compare
	@param b			IN the second PMReal to compare
	@param epsilon		IN the epsilon value used to compare the two PMReal values.
	@return kTrue if the values are equal, else kFalse
	*/
	friend  bool16  EqualsWithEpsilon(const PMReal& a, const PMReal& b, double epsilon) noexcept;

private:
	double		fRealValue;
};


/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/

// Math operators
inline PMReal operator-(const PMReal& r)
{
#ifdef WINDOWS
	// Verify that exception handling is what we expect.
	ASSERT_MSG(kDefaultFPUExceptions == _controlfp(0, 0), FORMAT_ARGS("Unexpected floating point control word! You may see floating point exceptions (actual:0x%8.8X expected:0x%8.8X)",_controlfp(0, 0), kDefaultFPUExceptions));
#endif

	return -r.fRealValue;
}

inline PMReal operator+(const PMReal& a, const PMReal& b)
{
#ifdef WINDOWS
	// Verify that exception handling is what we expect.
	ASSERT_MSG(kDefaultFPUExceptions == _controlfp(0, 0), FORMAT_ARGS("Unexpected floating point control word! You may see floating point exceptions (actual:0x%8.8X expected:0x%8.8X)",_controlfp(0, 0), kDefaultFPUExceptions));
#endif

	return a.fRealValue + b.fRealValue;
}

inline PMReal operator-(const PMReal& a, const PMReal& b)
{
#ifdef WINDOWS
	// Verify that exception handling is what we expect.
	ASSERT_MSG(kDefaultFPUExceptions == _controlfp(0, 0), FORMAT_ARGS("Unexpected floating point control word! You may see floating point exceptions (actual:0x%8.8X expected:0x%8.8X)",_controlfp(0, 0), kDefaultFPUExceptions));
#endif

	return a.fRealValue - b.fRealValue;
}

inline PMReal operator*(const PMReal& a, const PMReal& b)
{
#ifdef WINDOWS
	// Verify that exception handling is what we expect.
	ASSERT_MSG(kDefaultFPUExceptions == _controlfp(0, 0), FORMAT_ARGS("Unexpected floating point control word! You may see floating point exceptions (actual:0x%8.8X expected:0x%8.8X)",_controlfp(0, 0), kDefaultFPUExceptions));
#endif

	return a.fRealValue * b.fRealValue;
}

inline PMReal operator/(const PMReal& a, const PMReal& b)
{
#ifdef WINDOWS
	// Verify that exception handling is what we expect.
	ASSERT_MSG(kDefaultFPUExceptions == _controlfp(0, 0), FORMAT_ARGS("Unexpected floating point control word! You may see floating point exceptions (actual:0x%8.8X expected:0x%8.8X)",_controlfp(0, 0), kDefaultFPUExceptions));
#endif

	return a.fRealValue / b.fRealValue;
}


// Math functions
inline PMReal Floor(const PMReal& a)
{
	//return (a.fRealValue < 0.0 && a.fRealValue != double(int32(a.fRealValue)) ? int32(a.fRealValue - 1.0) : int32(a.fRealValue));
	return ::floor (a.fRealValue);
}

inline PMReal Ceiling(const PMReal& a)
{
	return (a.fRealValue > 0.0 && a.fRealValue != double(int32(a.fRealValue)) ? int32(a.fRealValue + 1.0) : int32(a.fRealValue));
}

inline PMReal Round(const PMReal& a)
{
	PMReal r(a.fRealValue + 0.5);

	return ::Floor(r);
}

inline PMReal abs(const PMReal& a)
{
// NOTE: Implicit construction on return
	return ::fabs(a.fRealValue);
}

inline PMReal NearestMultiple(const PMReal&a, const PMReal& factor)
{
	return ::Round (a / factor) * factor;
}

inline PMReal Mod(const PMReal& a, const PMReal& b)
{
// NOTE: Implicit construction on return
	return ::fmod(a.fRealValue, b.fRealValue);
}

// Conversion operators
inline Fixed ToFixed(const PMReal& r)
{
	ASSERT(static_cast<int32>(r.fRealValue) >= kMinInt16);
	ASSERT(static_cast<int32>(r.fRealValue) <= kMaxInt16);

	PMReal a(::Round(r * 65536.0));
	return int32(a.fRealValue);
}

inline double ToDouble (const PMReal& r) noexcept
{
	return r.fRealValue;
}

inline float ToFloat (const PMReal& r)
{
	return (float) r.fRealValue;
}

inline int16 ToInt16 (const PMReal& r)
{
	ASSERT(r.fRealValue >= kMinInt16);
	ASSERT(r.fRealValue <= kMaxInt16);

	return (int16) r.fRealValue;
}

inline uint16 ToUInt16 (const PMReal& r)
{
	ASSERT(r.fRealValue >= 0.0);
	ASSERT(r.fRealValue <= kMaxUInt16);

	return (uint16) r.fRealValue;
}

inline int32 ToInt32 (const PMReal& r)
{
	ASSERT_MSG(r.fRealValue >= kMinInt32, FORMAT_ARGS("Value %4.4f is too small to convert to int32",r.fRealValue));
	ASSERT_MSG(r.fRealValue <= kMaxInt32, FORMAT_ARGS("Value %4.4f is too large to convert to int32",r.fRealValue));

	return (int32) r.fRealValue;
}

inline uint32 ToUInt32 (const PMReal& r)
{
	ASSERT(r.fRealValue >= 0.0);
	ASSERT(r.fRealValue <= kMaxUInt32);

	return (uint32) r.fRealValue;
}

inline PMReal ToPMReal (Fixed fx)
{
	// NOTE: Implicit construction on return
	return double(fx) * 0.0000152587890625;		// 1/65536
}

inline PMReal& PMReal::operator+=(const PMReal& a)
{
	fRealValue += a.fRealValue;

	return *this;
}

inline PMReal& PMReal::operator-=(const PMReal& a)
{
	fRealValue -= a.fRealValue;

	return *this;
}

inline PMReal& PMReal::operator*=(const PMReal& a)
{
	fRealValue *= a.fRealValue;

	return *this;
}

inline PMReal& PMReal::operator/=(const PMReal& a)
{
	fRealValue /= a.fRealValue;

	return *this;
}


// Comparison operators
inline bool16 operator<(const PMReal& a, const PMReal& b) noexcept
{
	return a.fRealValue < (b.fRealValue - kPMRealEpsilon);
}

inline bool16 operator>(const PMReal& a, const PMReal& b) noexcept
{
	return a.fRealValue > (b.fRealValue + kPMRealEpsilon);
}

inline bool16 operator<=(const PMReal& a, const PMReal& b) noexcept
{
	return a.fRealValue <= (b.fRealValue + kPMRealEpsilon);
}

inline bool16 operator>=(const PMReal& a, const PMReal& b) noexcept
{
	return a.fRealValue >= (b.fRealValue - kPMRealEpsilon);
}

inline bool16 operator==(const PMReal& a, const PMReal& b) noexcept
{
	return ::fabs(a.fRealValue - b.fRealValue) < kPMRealEpsilon;
}

inline bool16 operator!=(const PMReal& a, const PMReal& b) noexcept
{
	return !(a == b);
}

	// allow epsilon compare with angles in degress (360 == 0)
inline bool16 AnglesEqual(const PMReal& a, const PMReal& b) noexcept
{
	if (a == b)
		return kTrue;
	else if (a > b)
		return ::fabs((a.fRealValue - 360.0) - b.fRealValue) < kPMRealEpsilon;
	else
		return ::fabs(a.fRealValue - (b.fRealValue - 360.0)) < kPMRealEpsilon;
}

inline bool16 EqualsWithEpsilon(const PMReal& a, const PMReal& b, double epsilon) noexcept
{
	return ::fabs(a.fRealValue - b.fRealValue) < epsilon;
}
#endif

