//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/transparencyeffect/TranFxConvolutionFilter.cpp $
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

// Interface includes
// None

// Other API includes
#include "GraphicsExternal.h"	// _t_AGM...
#include "AGMImageAccessor.h"
#include "ImageTypes.h"

// Project includes
#include "TranFxConvolutionFilter.h"
#include "TranFxID.h"

// Color space family from AGM, subsetted to meet our needs here.
enum SubsettedAGMColorSpaceFamily 
{
	kAGMCsGray  
};

/*
*/
TranFxConvolutionFilter::Kernel::Kernel(int32 width, int32 height, const float* coefficients) :
	fWidth(width), 
	fHeight(height), 
	fCoefficients(coefficients),
	fXOrigin((width-1)/2), 
	fYOrigin((height-1)/2)
{
	ASSERT(width > 0);
	ASSERT(height > 0);
}

/*
*/
TranFxConvolutionFilter::TranFxConvolutionFilter(AGMImageAccessor* input, const bool16 invertGrey, const bool16 applyAlpha)
	: fInput(nil), fWidth(0), fHeight(0), fOutput(nil)
{
	do
	{
		// Validate that we can handle the data found in the input image.
		ASSERT(input != nil);
		ASSERT(input->GetPMColorFamily() == kPMGrayColorSpace);
		if (!(input->GetPMColorFamily() == kPMGrayColorSpace))
		{
			break;
		}
		fInputBytesPerPixel = input->GetBitsPerPixel()/8;
		ASSERT_MSG(fInputBytesPerPixel == 2, "TranFxConvolutionFilter requires two channels, greyscale+alpha");
		if (fInputBytesPerPixel != 2)
		{
			// We require two channels, greyscale and alpha.
			break;
		}
		fWidth  = std::abs(input->GetBounds().right - input->GetBounds().left);
		fHeight = std::abs(input->GetBounds().bottom - input->GetBounds().top);
		ASSERT(fWidth >= 1 && fHeight >= 1);

		// We do all our image processing the buffer fOutput.
		// Allocate the necessary memory for the image.
		fOutput = new TranFxConvolutionFilter::Pixel[fWidth*fHeight];
		ASSERT(fOutput);
		if (fOutput == nil)
		{
			break;
		}
		memset(fOutput, 0x0, fWidth*fHeight*sizeof(TranFxConvolutionFilter::Pixel));

		// Extract the greyscale values from input into our buffer, fOutput.
		// Invert on the way through if requested.
		uint32 bufferSize = (fWidth*fHeight*fInputBytesPerPixel);
		uint8* base = (uint8*)input->GetBaseAddr();
		TranFxConvolutionFilter::Pixel* outPixel = fOutput;
		for (uint8* in = base; in < base + bufferSize; in += fInputBytesPerPixel)
		{
			// in[0] is alpha value, in[1] is greyscale value.
			if (invertGrey)
			{
				*outPixel = 255 - in[1];
			}
			else
			{
				*outPixel = in[1];
			}
			outPixel++;
		}

		fInput = input;

		// Apply alpha channel to the image in fOutput if requested.
		if (applyAlpha)
		{
			uint8* inAlpha = (uint8*)fInput->GetBaseAddr();
			for (TranFxConvolutionFilter::Pixel* out = fOutput; out < (fOutput + (fWidth*fHeight)); out++)
			{
				TranFxConvolutionFilter::Pixel data = *out;
				// The value of an alpha channel value versus
				// the opacity it represents is given below:
				// Opacity	vs	alpha
				//	100%		0xFF (255)
				//	50%			0x80 (128)
				//	0%			0x00
				// So a value of 255 means the associated pixel is opaque
				// and a value of 0 means it is transparent.	
				*out = *out * ((*inAlpha)/255.0);
				//TRACEFLOW("TransparencyEffect", "%f, %d, %f\n",
				//	data,
				//	*inAlpha,
				//	*out);
				inAlpha += fInputBytesPerPixel;
			}
		}

	} while (false);
}

/*
*/
TranFxConvolutionFilter::~TranFxConvolutionFilter()	
{
	if (fInput)
	{
		delete fInput;
	}
	if (fOutput)
	{
		delete [] fOutput;
	}
}

/*
*/
AGMImageAccessor* TranFxConvolutionFilter::CreateOutputAccessor(AGMImageRecord& output)
{
	AGMImageAccessor* result = nil;
	do
	{
		// Initialise output image.
		memset(&output, 0x0, sizeof(AGMImageRecord));
		output.bounds.xMin = fInput->GetBounds().left;
		output.bounds.xMax = fInput->GetBounds().right;
		output.bounds.yMin = fInput->GetBounds().top;
		output.bounds.yMax = fInput->GetBounds().bottom;
		output.bitsPerPixel = 8;
		output.decodeArray = 0;
		output.colorTab.numColors = 0;
		output.colorTab.theColors = nil;
		output.colorSpace = kAGMCsGray;
		output.byteWidth = (output.bounds.xMax - output.bounds.xMin); // number of bytes in a row at 1 byte per pixel
		uint32 bufferSize = output.byteWidth * (output.bounds.yMax - output.bounds.yMin);
		uint8* newBuffer = new uint8[bufferSize];
		ASSERT(newBuffer);
		if (newBuffer == nil)
		{
			break;
		}
		memset(newBuffer, 0, bufferSize);
		output.baseAddr = newBuffer;

		// Copy fOutput image data into output buffer.
		TranFxConvolutionFilter::Pixel* in = fOutput;
		for (uint8* out = newBuffer; out < newBuffer + bufferSize; out++)
		{
			if (*in > 255.0)
			{
				*out = 255;
			}
			else if (*in < 0.0)
			{
				*out = 0;
			}
			else
			{
				*out = (uint8)(*in);
			}
			in++;
		}

		// return the result to the caller.
		result = ::CreateAGMImageAccessor(output);

	} while (false);
	return result;
}

/*
*/
void TranFxConvolutionFilter::Convolve(TranFxConvolutionFilter::Kernel& kernel)
{
	// The matrix of coefficients in the supplied kernel slides from left
	// to right across the image data and a value is computed for an output
	// pixel based on the value of surrounding pixels. Once a complete
	// row is processed the kernel is moved down to the next row and again
	// slides across the image data.
	//
	// For example, say you have an 
	// image that is 12 pixels wide(12 columns indices 0..11) and 6 
	// pixels high(6 rows indices 0..5).
	// Say the kernel of coefficients contains 3 columns (indices 0..2)
	// and 3 rows (indices 0..2). The origin of the kernel used to derive
	// the output pixel co-ordinate will be at location (1,1) in the kernel.
	// So the algorithm below will calculate values
	// (1, 1), (1,2), (1,3)...(1,10)
	// (2, 1), (2,2), (2,3)...(2,10)
	// ...
	// (4, 1), (4,2), (4,3)...(4,10)
	//
	// The boundary pixels at the edge of the image are not calculated.
	// In the example above you can see that (0,0) the top left pixel
	// and (5,11) the bottom right pixel values are not calculated.
	// If they are required must be calculated by the caller. This is lame
	// and should be improved at some point.

	const TranFxConvolutionFilter::Pixel* coefficients = kernel.GetCoefficients();
	int32 rowMax = fHeight - kernel.GetHeight();
	int32 colMax = fWidth - kernel.GetWidth();
	for (int32 row = 0; row <= rowMax; row++)
	{ 	// y runs down the rows(top to bottom).
		for (int32 col = 0; col <= colMax; col++)
		{ 	// x runs across the columns in the row(left to right).
			float sum = 0.0;
			for (int32 kernelRow = 0; kernelRow < kernel.GetHeight(); kernelRow++)
			{
				const TranFxConvolutionFilter::Pixel* inRowBase = fOutput + ((row+kernelRow) * fWidth);               
				for (int32 kernelCol = 0; kernelCol < kernel.GetWidth(); kernelCol++)
				{
					const TranFxConvolutionFilter::Pixel data = inRowBase [col + kernelCol];
					const float kernelValue = coefficients [kernelRow*kernel.GetWidth() + kernelCol];
					sum += data*kernelValue;
				}
			}
			// Give the kernel a chance to make some adjustment to the sum.
			kernel.ApplySum(sum);
			TranFxConvolutionFilter::Pixel* outRowBase = fOutput + ((row + kernel.GetYOrigin()) * fWidth);

			// Store the sum in the output image.
			outRowBase [col + kernel.GetXOrigin()] = sum;
		}
	}
}   

/*
*/
void    TranFxConvolutionFilter::ApplyBlur()
{
	// Set up a matrix of coefficients used to compute a weighted average
	// of surrounding pixel values. The matrix below blurs the image slightly.
	const float kSumOfWeights = 16.0;
	TranFxConvolutionFilter::Pixel coefficients [3] [3] =
	{
		{(float)(1.0/kSumOfWeights), (float)(2.0/kSumOfWeights), (float)(1.0/kSumOfWeights)},
		{(float)(2.0/kSumOfWeights), (float)(4.0/kSumOfWeights), (float)(2.0/kSumOfWeights)},
		{(float)(1.0/kSumOfWeights), (float)(2.0/kSumOfWeights), (float)(1.0/kSumOfWeights)}
	};

	// Reduce the intensity of the image by applying a factor to each co-effient.
	const float kIntensityFactor = (float) (1.0/3.0);
	for (int32 row = 0; row < 3; row++)
	{
		for (int32 col = 0; col < 3; col++)
		{	
			coefficients [row] [col] *= kIntensityFactor;
		}
	}

	// Create a convolution kernel from the coefficients.
	TranFxConvolutionFilter::Kernel kernel(3, 3, coefficients[0]);
	if (fWidth >= kernel.GetWidth() && fHeight >= kernel.GetHeight())
	{
		this->Convolve(kernel);
	}

	// Calculate some edge pixel values.
	// The convolution above leaves the top and bottom
	// rows and the left and right column pixel values
	// untouched.
	const float edgeFactor = (float)(1.0/(kSumOfWeights*kIntensityFactor*2));

	// Adjust top & bottom rows.
	TranFxConvolutionFilter::Pixel* topRow = fOutput;
	const TranFxConvolutionFilter::Pixel* nextRow = topRow + fWidth;
	TranFxConvolutionFilter::Pixel* bottomRow = fOutput + ((fHeight-1) * fWidth);
	const TranFxConvolutionFilter::Pixel* previousRow = bottomRow - fWidth;
	for (int32 col = 0; col < fWidth; col++)
	{ // move right across the columns
		topRow [col] = ((topRow [col]*edgeFactor) + nextRow [col]) * 0.5;
		bottomRow [col] = ((bottomRow [col]*edgeFactor) + previousRow [col]) * 0.5;
	}

	// Adjust left & right columns.
	for (int32 row = 0; row < fHeight; row++)
	{ // move down the rows
		TranFxConvolutionFilter::Pixel* rowBase = fOutput + (row * fWidth);   
		rowBase [0] = ((rowBase [0]*edgeFactor) + rowBase [1]) * 0.5;
		rowBase [fWidth-1] = ((rowBase [fWidth - 1]*edgeFactor) + rowBase [fWidth-2]) * 0.5;
	}
}

// End, TranFxConvolutionFilter.cpp
