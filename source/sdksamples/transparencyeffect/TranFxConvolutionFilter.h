//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/transparencyeffect/TranFxConvolutionFilter.h $
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

#ifndef __TranFxConvolutionFilter_H_DEFINED__
#define __TranFxConvolutionFilter_H_DEFINED__

class AGMImageAccessor;
#include "K2Vector.h"
#include "K2Vector.tpp"

/** Image processing helper class.

	Convolution filtering is often used for image processing such as blurring, sharpening and edge detection.
	It operates on a group of input pixels surrounding a center pixel. The surrounding pixels provide information 
	about brightness trends (light to dark,dark to light) in the area of the pixel being processed. 
	It is implemented by sliding a matrix of coeffiecients
	(see TranFxConvolutionFilter::Kernel) across the input image, pixel by pixel, and applying the coefficients
	to the surrounding pixels. A new value for the pixel in the center of the kernel is calculated and
	saved in the output image. The resulting brightness of each output pixel depends on the group of pixels 
	surrounding the input pixel and the value of the coefficients in the kernel.

	
	@ingroup transparencyeffect
	@see Computer Graphics Principles and Practice
	@see http://java.sun.com/products/java-media/jai/forDevelopers/jai1_0_1guide-unc/Image-enhance.doc.html
	@see http://www.dai.ed.ac.uk/CVonline/LOCAL_COPIES/YOUNG/vision1.html

*/
class TranFxConvolutionFilter
{
public:
	/** Data type this class uses to manipulate pixel values.
	 */
	typedef float Pixel;

public:

	/** Convolution kernel that contains
		a matrix of coefficients used to compute a value for a pixel based on the 
		value of surrounding pixels.

		
		@ingroup transparencyeffect
	 */
	class Kernel
	{
	public:
		/** Constructs kernel from an array containing a 
			a matrix of co-efficients of the given width and height.
			@param width of matrix
			@param height of matrix
			@param coefficients matrix of coefficients as an array in row major order.
		 */
		Kernel(int32 width, int32 height, const float* coefficients);

		/** Destructor.
		 */
		virtual ~Kernel() {}

	public:
		/** Return the width of this filter.
			@return the width of this filter.
		 */
		uint32                      GetWidth() const {return fWidth;}

		/** Return the height of this filter.
			@return the height of this filter.
		 */
		uint32                      GetHeight() const {return fHeight;}

		/** Return the x origin of this filter. This identifies the x component
			of the pixel position whose output value is being computed by this filter.
			@return the x origin of this filter.
		 */
		int32                       GetXOrigin() const {return fXOrigin;}

		/** Return the y origin of this filter. This identifies the x component
			of the pixel position whose output value is being computed by this filter.
			@return the y origin of this filter.
		 */
		int32                       GetYOrigin() const {return fYOrigin;}

		/** Return the filter matrix in row major order.
			@return the filter matrix in row major order.
		 */
		const float*                GetCoefficients() const {return fCoefficients;}

	public:
		/** Sub-classes can specialise this to change the computed output
			value in some way. Values might require to be normalised for
			example.
			@param sum computed output value for the current pixel.
		 */
		virtual void                ApplySum(TranFxConvolutionFilter::Pixel& sum) {}

	private:
		uint32                      fWidth;
		uint32                      fHeight;
		int32                       fXOrigin;
		int32                       fYOrigin;
		const float*                fCoefficients;
	};

public:
	/** Constructor copies image data out of the given agmImage and into this
		objects fOutput buffer for subsequent processing.
		@param agmImage	IN	image to be processed. Must be a greyscale image with
			an alpha channel.
		@param invertGrey IN if kTrue then greyscale values ar flipped(black(0) becomes
			white(255) and white becomes black.
		@param applyAlpha IN if kTrue then the alpha channel values for each greyscale
			pixel are applied.
	 */
	TranFxConvolutionFilter(AGMImageAccessor* agmImage, const bool16 invertGrey, const bool16 applyAlpha);

	/** Destructor deletes fOutput buffer and tidies up.
	 */
	virtual ~TranFxConvolutionFilter();

public:
	// General purpose member functions.

	/** Convolve the image with the given kernel.
		@param kernel containing coeffients to be used.
	 */
	void                    Convolve(Kernel& kernel);

	/** Return the processed image in the given AGMImageRecord.
		@return accessor for the processed image pixels.
	 */
	AGMImageAccessor*       CreateOutputAccessor(AGMImageRecord& output);

public:
	// Canned effects.

	/** Apply a slight blur and reduce the intensity of the image.
	 */
	void                    ApplyBlur();

private:
	AGMImageAccessor*       fInput;
	uint32                  fInputBytesPerPixel;
	uint32                  fWidth;
	uint32                  fHeight;
	TranFxConvolutionFilter::Pixel*   fOutput;
};

#endif // __TranFxConvolutionFilter_H_DEFINED__

