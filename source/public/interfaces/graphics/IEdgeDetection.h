//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IEdgeDetection.h $
//  
//  Owner: dstephen
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
//  Purpose:
//  Perform edge detection on an image to create a clipping path.  The image is
//  converted to grayscale first, then to black and white using the threshold value,
//  and then edges are created at every transition from white to black and black to white.
//  These transitions form a polygon which are then smoothed into a bezier using the
//  tolerance argument.
//  
//========================================================================================

#pragma once
#ifndef __IEdgeDetection__
#define __IEdgeDetection__

#include "IPMUnknown.h"
#include "ImageDataTypes.h"

class IPathGeometry;
class PMReal;

const uint8  kEdgeDetection_default_threshold = 25;

/** Progress bar callback routine to pass to IEdgeDetection::MaskToPolygon
	@param message - IN: Progress title
	@param percentDone - IN: Value between 0.0 and 1.0
	@return kTrue to continue, kFalse to cancel/abort the edge detection process.
*/

class EdgeDetectionProc
{
public:
	virtual bool8  EdgeDetectionDo(const PMString& message, const PMReal& percentDone ) = 0;
};

typedef EdgeDetectionProc* EdgeDetectionProcPtr;

/** This interface is used by the kEdgeDetectionBoss to create an IPathGeometry
	by performing edge detection on an image.  The image is converted to grayscale,
	then converted to 1-bit using the gray threshold, and edge detection is performed
	on this 1-bit image to create a polygonal path.  The polygon is then smoothed
	to create a spline-based path.
*/
class IEdgeDetection : public IPMUnknown
{
public:

	/** enumeration of flags which client can bitwise or together
	*/
	enum {
		/** Allow subpaths within subpaths
		*/
		kAllowHoles				= 1 << 0,	
		/** Ignore portions of the image outside the containing frame
		*/
		kIntersectWithFrame		= 1 << 1,
		/** Draw the 1-bit bitmap used to detect edges.
		*/
		kDisplayMask 			= 1 << 2,
		/** Forces the full resolution image to be used as the source
		*/
		kForceHighRes			= 1 << 3,
		/** Forces the proxy to be used if it exists
		*/
		kForceProxy				= 1 << 4
	} ;
		
	/** Perform edge detection on an image to create a path.
		@param itemRef - IN: the source image
		@param pNew - OUT: resulting path
		@param channelIndex - IN: 0 = Composite, n = alpha channel number n-1.
		@param resolution - IN: The desired resolution of the path.  Pass zero to indicate source resolution.
		@param flags - IN: Combination of kAllowHoles, kIntersectWithFrame, kDisplayMask, kForceHighRes, kForceProxy.
		@param threshold - IN: Gray threshold between 0 and 255 to determine which pixels become black and which
			become white in the 1-bit stage of the process.
		@param tolerance - IN: How sloppy can we be. 0 will produce unsmoothed polygonal path
		@param minPathSize - IN: Delete all paths with bounding box smaller than this size
		@param progressPtr - IN: Pointer to a progress bar callback.  Can be nil.
		@param imageMaskDataPtr - IN: Optional. Required in case we want to apply edge detection to an image
			mask (for eg. Select Subject mask) rather than the original image. In case this parameter is provided,
			it will take precedence over original image for edge detection.
	*/
	virtual ErrorCode MaskToPolygon
		(
			const UIDRef&	itemRef,	// The image
			IPathGeometry *pNew,		// resulting paths
			int16 channelIndex,			// 0 = Composite, n = alpha channel number n-1.
			int32 resolution,			// The desired resolution of the path.  Pass zero to indicate source resolution.
			uint32	flags,
			uint8 threshold,			// Gray threshold between 0 and 255
			PMReal tolerance,			// How sloppy can we be. 0 will produce unsmoothed polygonal path
			PMReal minPathSize,			// Delete all paths with bounding box smaller than this size
			EdgeDetectionProcPtr progressPtr,
			ImagingTypes::ImageDataPtr imageMaskDataPtr = nullptr		// The image mask
		) const = 0;

};
#endif
