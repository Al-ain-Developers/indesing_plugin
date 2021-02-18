//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PMMatrix.h $
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
//  PMMatrix encapsulates the matrix math used in PM.  It hides both the data type and
//  the corresponding AGM matrix.  It is possible to emulate the matrix math that occurs
//  in AGM using the PMMatrix AGM methods.
//  
//========================================================================================

#pragma once
 #ifndef __PMMatrix__
 #define __PMMatrix__
 #include "K2Vector.h"
 #include "PMPoint.h"
 
//----------------------------------------------------------------------------------------
// Forward declarations
//----------------------------------------------------------------------------------------

class PMMatrix;
class PMRect;
class PMLineSeg;
class PMPolygon4;

 struct _t_BRVFixedMatrix;
 struct BRVCoordMatrix;

namespace dvacore {
  namespace geom {
    template <class T> class ScaleMatrixT;
  }
}


//----------------------------------------------------------------------------------------
// Typedefs
//----------------------------------------------------------------------------------------
 typedef K2Vector<PMMatrix> PMMatrixCollection;

 #pragma export on

/**	C++ class for dealing with matrix operations.
*/
 class PMMatrix
 {
 	public:
		typedef base_type data_type;

		/**	Read/Write this matrix.
			@param s is the stream to read from and write to.
		*/
		PUBLIC_DECL void ReadWrite(IPMStream *s);


//-------------------------------------------------------------------------------------
		/**	Contruct an identity matrix:
			[ 1 0 0]
			[ 0 1 0]
			[ 0 0 1]
		*/
		constexpr PMMatrix() noexcept
			: fa(1.0), fb(0.0), fc(0.0), fd(1.0), fe(0.0), ff(0.0)
		{
		}

		/**	Contruct a matrix with a, b, c, d, e, f as initial values:
			[ a b 0]
			[ c d 0]
			[ e f 1]
		*/
 		constexpr PMMatrix( PMReal a, PMReal b, PMReal c, PMReal d, PMReal e, PMReal f) noexcept
		: fa(a), fb(b), fc(c), fd(d), fe(e), ff(f)
		{
		}

		/**	Construct a matrix with the same perceptible value as m.
		*/
		constexpr PMMatrix(const PMMatrix &m) noexcept = default;
		constexpr PMMatrix(PMMatrix &&m) noexcept = default;

		/**	Construct a PMMatrix from an AGM fixed or float matrix.
			@param m is the AGM matrix.
		*/
		PUBLIC_DECL PMMatrix(const BRVCoordMatrix &m);

		/**	Make *this have the same perceptible value as m.  Returns *this.
		*/
		PMMatrix& operator=(const PMMatrix &m) noexcept = default;
		PMMatrix& operator=(PMMatrix &&m) noexcept = default;


		/**	Set the PMMatrix with an AGM float matrix.
			@param m is the AGM matrix.
		*/
		PUBLIC_DECL void SetMatrix (const BRVCoordMatrix &m);

		/**	Set the PMMatrix with an AGM fixed matrix.
			@param m is the AGM matrix.
		*/
		PUBLIC_DECL void SetMatrix (const _t_BRVFixedMatrix &m);

		/**	Set the PMMatrix with a Drover dvaui::ui::UI_MatrixF32 matrix. (which is a typedef of dvacore::geom::ScaleMatrixT<float>)
			@param m is the Drover matrix.
		*/
		PUBLIC_DECL void SetMatrix (const dvacore::geom::ScaleMatrixT<float> &m);
		
		/**	Create and return an equivalent AGM matrix from this PMMatrix.
			@param retMatrix is the AGM matrix created.
		*/
		PUBLIC_DECL void GetAGMFixedMatrix (_t_BRVFixedMatrix* retMatrix) const;

		/**	Create and return an equivalent AGM float matrix from this PMMatrix.
			@param retMatrix is the AGM matrix created.
		*/
		PUBLIC_DECL void GetAGMFloatMatrix (BRVCoordMatrix* retMatrix) const;

		/**	Return an equivalent Drover dvaui::ui::UI_MatrixF32 matrix from this PMMatrix.
			@param retMatrix is the Drover matrix created.
		*/
		PUBLIC_DECL void GetUIMatrixF32 (dvacore::geom::ScaleMatrixT<float>* retMatrix) const;


		/**	Return kTrue if *this and other have the same perceptible value.
			Otherwise returns kFalse;
		*/
		PUBLIC_DECL bool16 operator==(const PMMatrix& other) const;

		bool16 operator!=(const PMMatrix& other) const
		{
			return !(*this == other);
		}

		/** A partial ordering on matrices for use in sorted containers
		*/
		PUBLIC_DECL bool16 operator<(const PMMatrix& other) const;

//-------------------------------------------------------------------------------------

		/**	Compute the matrix product [ *x  *y  1] * (*this) producing
			the result [ x'  y'  1].  Then write x' back into *x and y' back into *y.
		*/
		PUBLIC_DECL void Transform(PMReal* x, PMReal* y) const;

		void Transform(PMPoint* p) const
		{
			Transform(&p->X(), &p->Y());
		}


		/**	Transforms each of the four points specified in fourPoints 
			independently and writes the results back into the corresponding 
			slots of the same PMPolygon4.
		*/
		PUBLIC_DECL void Transform( PMPolygon4* fourPoints) const;


		/**	Transforms rect and return (back in *rect) the smallest axes-aligned 
			rectangle that contains the transformed rectangle.
		*/
		PUBLIC_DECL void Transform(PMRect* rect) const;


		/**	Transform each of the two points specified in the segment independently,
			and write the results back into the PMLineSeg perhaps in reverse order
			if required to satisfy the invariant of PMLineSeg that segment.Top().Y() be
			no larger than segment.Bottom().Y().
		*/
		PUBLIC_DECL void Transform(PMLineSeg* segment) const;


//-------------------------------------------------------------------------------------
		

		/**	Extract the nth free value of *this as a PMReal. 
			The index must be >= 0 and <= 5.
			In other words consider the following code:
				
				PMReal a,b,c,d,e,f,x,y;

				x = y = 0;
				m.Transform( &x, &y);
				e = x;
				f = y;

				x = 1; y = 0;
				m.Transform( &x, &y);
				a = x - e;
				b = y - f;
				
				x = 0; y = 1;
				m.Transform( &x, &y);
				c = x - e;
				d = y - f;
				
			Then
				m[0] returns a
				m[1] returns b
				m[2] returns c
				m[3] returns d
				m[4] returns e
				m[5] returns f
		
			operator[] is simply more convenient and perhaps more efficient than
			using the above code.  Note that the implementation of PMMatrix need
			not be an array of 6 PMReals even though this operator gives it that
			appearance.

		*/
		PUBLIC_DECL const PMReal operator[](int index) const;


//-------------------------------------------------------------------------------------


		/**	@return kTrue if  m * (*this) == m for all m.  Otherwise return kFalse;
		*/
		PUBLIC_DECL bool16 IsIdentity() const noexcept;
		PUBLIC_DECL bool exactly_identity() const noexcept; //Similar to IsIdentity, except exact comparison of double values is done and check is ordered based on
															//which elements are most likely to reveal non-identity. For all purposes, just use IsIdentity. Leaving this
															//function in place for historical reasons.

		/**	Set this matrix to the identity matrix discarding its previous value.
		*/
		PUBLIC_DECL void ResetToIdentity() noexcept;


		/**	@return the product of x and y scaling. I.e., given m = *this, 
			return m[0]*m[3] - m[1]*m[2] where operator[] is as described above.
		*/
		PUBLIC_DECL PMReal Determinant() const;


		/**	@return whether the product of x and y scaling is zero. Note if
			m.IsSingular() then m has no inverse and m.Invert() will assert.
		*/
		bool16 IsSingular() const { return Determinant() == 0.0; }


		/**	@return kTrue if an axes aligned rectangle (like PMRect) remains
			an axes aligned rectangle when transformed by *this.  That is, *this
			contains no skew component and at most a 90-degree multiple rotation.
			This is equivalent to calling GetTransformValues and checking if 
			skewslope == zero and (costheta == 0 || sintheta == 0) but is perhaps
			more efficient or more convenient.
		*/
		PUBLIC_DECL bool16 PreservesBoxes() const;


		/**	Replace the value of this matrix with its inverse discarding its previous value.
		*/
		PUBLIC_DECL void Invert();

		/**	@return the inverse matrix of this matrix. Original matrix is unchanged.
		*/
		PUBLIC_DECL PMMatrix Inverse() const;



//-------------------------------------------------------------------------------------



		/**	@return the matrix product m1.m2 without affecting the value of m1 or m2.
		*/
	 	friend PUBLIC_DECL PMMatrix operator*( const PMMatrix &m1, const PMMatrix &m2);

		/**	Set *this = m * (*this).
		*/
		PUBLIC_DECL void PreConcat(const PMMatrix &m);

		/**	Set *this = (*this) * m.
		*/
		PUBLIC_DECL void PostConcat(const PMMatrix &m);
	
	
		/** PermuteLeftPast computes m * (*this) * inverse(m) and assigns the result to *this.
			I.e. computes the new value of this such that m * oldthis == newthis * m
		*/
		PUBLIC_DECL void PermuteLeftPast( const PMMatrix& m);

		/** PermuteRigthPast computes inverse(m) * (*this) * m and assigns the result to *this.
			I.e. computes the new value of this such that oldthis * m == m * newthis
		*/
		PUBLIC_DECL void PermuteRightPast( const PMMatrix& m);
		


	
//-------------------------------------------------------------------------------------



		/**	Set *this = PMMatrix(xScale, 0, 0, yScale, 0, 0) * (*this)
		*/
		PUBLIC_DECL void PreScale( PMReal xScale, PMReal yScale);
		
		
		/**	Set *this = (*this) * PMMatrix(xScale, 0, 0, yScale, 0, 0)
		*/
		PUBLIC_DECL void Scale( PMReal xScale, PMReal yScale);


		const PMMatrix& ScaleFrom( const PMPoint& stationaryPoint, PMReal xScale, PMReal yScale)
		{
			Translate( -stationaryPoint.X(), -stationaryPoint.Y());
			Scale( xScale, yScale);
			Translate( stationaryPoint.X(), stationaryPoint.Y());
			return *this;
		}



		/**	Set *this = (*this) * PMMatrix(1, 0, tangent(xSkewAngleInDegrees), 1, 0, 0);
		*/
		PUBLIC_DECL void SkewHorizontal( PMReal xSkewAngleInDegrees);

		/**	Set *this = (*this) * PMMatrix(1, tangent(ySkewAngleInDegrees), 0, 1, 0, 0);
		*/
		PUBLIC_DECL void SkewVertical( PMReal ySkewAngleInDegrees);

		void SkewFrom( const PMPoint& stationaryPoint, PMReal skewAngle, PMReal noSkewDirectionAngle)
		{
			Translate( -stationaryPoint.X(), -stationaryPoint.Y());
			Rotate( -noSkewDirectionAngle);
			SkewHorizontal( skewAngle); //XFIssue LH coordinates
			Rotate( noSkewDirectionAngle);
			Translate( stationaryPoint.X(), stationaryPoint.Y());
		}



		/**	Set *this = PMMatrix( cosine(angleInDegrees), sine(angleInDegrees), -sine(angleInDegrees), cosine(angleInDegrees), 0, 0) * (*this);
		*/
		PUBLIC_DECL void PreRotate( PMReal angleInDegrees);

		/**	Set *this = (*this) * PMMatrix( cosine(angleInDegrees), sine(angleInDegrees), -sine(angleInDegrees), cosine(angleInDegrees), 0, 0);
		*/
		PUBLIC_DECL void Rotate( PMReal angleInDegrees);

		const PMMatrix& RotateAbout( const PMPoint& center,  PMReal angle)
		{
			Translate( -center.X(), -center.Y());
			Rotate( angle); //XFIssue LH coordinates
			Translate( center.X(), center.Y());
			return *this;
		}


		/**	Set *this = PMMatrix( 1, 0, 0, 1, x, y) * (*this);
		*/
		PUBLIC_DECL void PreTranslate( PMReal x, PMReal y);
		inline void PreTranslate( const PMPoint& offset) { PreTranslate( offset.X(), offset.Y());}

		/**	Set *this = (*this) * PMMatrix( 1, 0, 0, 1, x, y);
		*/
		PUBLIC_DECL void Translate( PMReal x, PMReal y);
		inline void Translate( const PMPoint& offset) { Translate( offset.X(), offset.Y());}



//-------------------------------------------------------------------------------------


		/**	Scale the matrix to the specified x and y scale factors.
			@param xScale is the x scale factor to scale to.
			@parma yScale is the y scale factor to scale to.
		*/
		PUBLIC_DECL void ScaleTo( PMReal xScale, PMReal yScale);
		PUBLIC_DECL void ScaleTo( const PMPoint& stationaryPoint, PMReal xScale, PMReal yScale);

		/**	Skew the matrix to the specified x skew angle.
			@param xSkewAngle is the x skew angle.
		*/
		PUBLIC_DECL void SkewTo( PMReal xSkewAngleInDegrees);
		PUBLIC_DECL void SkewTo( const PMPoint& stationaryPoint, PMReal xSkewAngleInDegrees);
		PUBLIC_DECL void SkewToSlope( const PMPoint& stationaryPoint, PMReal skewSlope);

		/**	Rotate the matrix to the specified angle.
			@param theta is the x skew angle.
		*/
		PUBLIC_DECL void RotateTo( PMReal thetaInDegrees);
		PUBLIC_DECL void RotateTo( const PMPoint& stationaryPoint, PMReal thetaInDegrees);
		PUBLIC_DECL void RotateTo( const PMPoint& stationaryPoint, PMReal cosineAngle, PMReal sineAngle);

		/**	Set the origin to x and y.
			@param x is the origin to set to on the x-axis.
			@param y is the origin to set to on the y-axis .
		*/
		PUBLIC_DECL void TranslateTo( PMReal x, PMReal y);
		void SetOrigin( PMReal x, PMReal y){ TranslateTo( x, y);}

		


//-------------------------------------------------------------------------------------

		

		/* An enumeration that specifies the factorization order used by GetMatrixFactors and GetTransformValues.
		   For example, a value of kFactorOrder_SKRT specifies that the matrix should be factored into elementary
		   transformation matrices in the order (scale)*(skew)*(rotate)*(translate).  Note since matrix
		   multiplication is not commutative, the factorization of a matrix depends on the desired factor order.
		   Currently only kFactorOrder_SKRT and kFactorOrder_RKST are implemented.  Passing any other TransformFactorOrder
		   value will return an incorrect result.
		*/
		enum TransformFactorOrder {
			kFactorOrder_SKRT = 0,
//			kFactorOrder_SKTR,
//			kFactorOrder_SRKT,
//			kFactorOrder_SRTK,
//			kFactorOrder_STKR,
//			kFactorOrder_STRK,
//
//			kFactorOrder_KSRT,
//			kFactorOrder_KSTR,
//			kFactorOrder_KRST,
//			kFactorOrder_KRTS,
//			kFactorOrder_KTSR,
//			kFactorOrder_KTRS,
//
//			kFactorOrder_RSKT,
//			kFactorOrder_RSTK,
			kFactorOrder_RKST = 14,
//			kFactorOrder_RKTS,
//			kFactorOrder_RTSK,
//			kFactorOrder_RTKS,
//
//			kFactorOrder_TSKR,
//			kFactorOrder_TSRK,
//			kFactorOrder_TKSR,
//			kFactorOrder_TKRS,
//			kFactorOrder_TRSK,
//			kFactorOrder_TRKS,
			kFactorOrder_End
		};


		static const uint32 kHasNoTransformContent = 0;
		static const uint32 kHasScaleContent = 1;
		static const uint32 kHasSkewContent = 2;
		static const uint32 kHasRotateContent = 4;
		static const uint32 kHasTranslateContent = 8;
		static const uint32 kHasAllTransformContent = (kHasScaleContent | kHasSkewContent | kHasRotateContent | kHasTranslateContent);

		/** GetMatrixFactors asserts if *this is singular.  Otherwise, if scale, skew, 
			rotate, and translate are non-nil pointers, then GetMatrixFactors writes
			matrices to the specified locations such that:
			
				1) scale * skew * rotate * translate == *this if factorOrder == kFactorOrder_SKRT
				   otherwise rotate * skew * scale * translate == *this if factorORder == kFactorOrder_RKST
				2) scale[1] == scale[2] == scale[4] == scale[5] == 0.0
				3) skew[1] == scale[4] == scale[5] == 0.0
				   skew[0] == skew[3] == 1.0
				4) rotate[0] == rotate[3]
				   rotate[1] == -rotate[2]
				   determinant(rotate) == 1.0
				5) translate[0] == translate[3] == 1.0
				   translate[1] == translate[2] == 0.0

			Any nil-pointer passed makes GetMatrixFactors skip writing the 
			corresponding matrix, but this does not change the factorization
			nor have any effect on the matrices whose values are written.
			
			The return value of GetMatrixFactors is a combination of the above
			constants OR'd together as one unsigned value.  If scale[0] or scale[3]
			differ from 1.0, then (result & kHasScaleContent).  If skew[2] differs
			from 0.0 then (result & kHasSkewContent).  If rotate[0] differs from 1.0
			then (result & kHasRotateContent).  And if either translate[4] or
			translate[5] differ from 0.0 then (result & kHasTranslateContent).
			Note the return value from GetMatrixFactors will not have any bits
			set for transform components whose factor was not requested.  For 
			example, GetMatrixFactors( nil, nil, &rotate, nil) will return either
			kHasNoTransformContent or kHasRotateContent even if the matrix has 
			other transform components.
			
			Note that the factorization returned from GetMatrixFactors, as described
			above, is not unique.  In particular, for kFactorOrder_SKRT, if one
			changed the algebraic sign of scale[0], scale[3], rotate[0], rotate[1],
			rotate[2], and rotate[3], then the set of factors would still
			meet all the conditions above.  Currently it is unspecified which
			of the two factorizations is returned.  Code that relies on one or 
			the other is incorrect.
			
			
		*/
		PUBLIC_DECL uint32 GetMatrixFactors( 
					PMMatrix* scale, PMMatrix* skew, 
					PMMatrix* rotate, PMMatrix* translate,
					TransformFactorOrder factorOrder = kFactorOrder_SKRT
				) const;


		/** GetTransformValues writes to its non-nil parameters the free values 
			in the matrices that would have been returned in a call to 
			GetMatrixFactors.  In particular, *xscale == scale[0], *yscale == scale[3],
			*skewslope == skew[2], *costheta == rotate[0], *sintheta == rotate[1],
			*xtranslation == translate[4], and *ytranslation == translate[5].  
			Any nil pointers cause GetTransformValues to skip writing the 
			corresponding return value, with the restriction that the pair of 
			parameters (xscale, yscale) must be both nil or both non-nil.  
			Likewise for the the pair (costheta, sintheta) and the pair 
			(xtranslation, ytranslation).  Callers are not allowed to be 
			"interested in" only one of the pair.  GetTransformValues will 
			assert on such a call.
			
			The return value has the same meaning as the return value of 
			GetMatrixFactors.  And like GetMatrixFactors, the only bits set will
			be those whose corresponding transform values were requested with 
			non-nil pointers.

			And, as described for GetMatrixFactors, the 7-tuple returned from 
			GetTransformValues, is not unique.  In particular, for kFactorOrder_SKRT,
			if one changed the algebraic sign of xscale, yscale, costheta, and sintheta,
			then the set of values would still correctly characterize the matrix.
			Currently it is unspecified which of the two 7-tuples is returned. 
			Code that relies on one or the other is incorrect.
		*/
  
		PUBLIC_DECL uint32 GetTransformValues( 
					PMReal* xscale, PMReal* yscale, 
					PMReal* skewslope, 
					PMReal* costheta, PMReal* sintheta, 
					PMReal* xtranslation, PMReal* ytranslation,
					TransformFactorOrder factorOrder = kFactorOrder_SKRT
				) const;


		/** GetMatrixContent returns the value that would have been returned from
			a call to either GetMatrixFactors or GetTransformValues with all 
			non-nil parameters and TransformFactorOrder == kFactorOrder_SKRT.
			This function is simply more efficient and perhaps more convenient.
		*/
		PUBLIC_DECL uint32 GetMatrixContent() const;



		/**	@returns the x scale factor that would be returned in the first 
			parameter to GetTransformValues with TransformFactorOrder == kFactorOrder_SKRT.
		*/
		PUBLIC_DECL PMReal GetXScale() const;
		
		/**	@returns the y scale factor that would be returned in the second 
			parameter to GetTransformValues with TransformFactorOrder == kFactorOrder_SKRT.
		*/
		PUBLIC_DECL PMReal GetYScale() const;

		/**	@returns the x skew angle in degrees in the range (-90, 90) whose 
			tangent would be returned in the third parameter to GetTransformValues 
			with TransformFactorOrder == kFactorOrder_SKRT.
		*/
		PUBLIC_DECL PMReal GetXSkewAngle() const;

		/**	@returns one of the angles whose sine and cosine would be returned 
			in the fourth and fifth parameters to GetTransformValues with 
			TransformFactorOrder == kFactorOrder_SKRT.  Note the angle 
			measurement returned is in degrees.  The return value will be 
			in the range (-180, 180] if zeroCentered is kTrue, otherwise it will 
			be in the range [0, 360).
		*/
		PUBLIC_DECL PMReal GetRotationAngle( bool16 zeroCentered = kFalse) const;

		/**	@returns the x translation amount that would be returned in the sixth 
			parameter to GetTransformValues with TransformFactorOrder == kFactorOrder_SKRT.
		*/
		PUBLIC_DECL PMReal GetXTranslation() const noexcept
		{
			return fe;
		}

		/**	@returns the y translation amount that would be returned in the seventh 
			parameter to GetTransformValues with TransformFactorOrder == kFactorOrder_SKRT.
		*/
		PUBLIC_DECL PMReal GetYTranslation() const noexcept
		{
			return ff;
		}



		// If you need rotation and any other the other values it is faster to call 
		// the following method instead of each of the above methods. Arguments may
		// be nil for those items you don't care about

		/**	Returns the rotation angle, x skew angle, x and y scale factors represented by this matrix.
			@param rotAngle is the rotation angle of the matrx in the range [0, 360).
			@param xSkewAngle is the x skew angle of the matrx in the range (-90, 90).
			@param xScale is the x scale factor.
			@param yScale is the y scale factor.
		*/
		PUBLIC_DECL void GetMatrixInfo (PMReal* rotAngle, PMReal* xSkewAngle, PMReal* xScale, PMReal* yScale) const;
		

		void SanityCheck() const
		{
#if DEBUG
			SanityCheck_();
#endif
		}

	private:
		PUBLIC_DECL void SanityCheck_() const;
		void RotateTo(double cosine, double sine);
		uint32 GetTransformValues_SKRT(PMReal* xscale, PMReal* yscale, PMReal* skewslope, PMReal* costheta, PMReal* sintheta, PMReal* xtranslation, PMReal* ytranslation) const;
		uint32 GetTransformValues_RKST(PMReal* xscale, PMReal* yscale, PMReal* skewslope, PMReal* costheta, PMReal* sintheta, PMReal* xtranslation, PMReal* ytranslation) const;
		void InternalSkewTo(double k);


		PMReal fa, fb, fc, fd, fe, ff;
 };
 
 
 #pragma export off
 #endif
