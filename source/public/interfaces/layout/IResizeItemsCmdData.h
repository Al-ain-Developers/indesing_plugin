//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IResizeItemsCmdData.h $
//  
//  Owner: Richard Rodseth
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
//  Purpose: 	Provide three different ways for setting data to ResizeItemsCmd:
//  1.	horizontal and vertical resize factor, and reference point
//  2.	delta x (width) and delat y (height) amount, and reference point
//  3.	absolute horizontal and vertical amount, and reference point
//  
//  Used when changing Width or Height in the Transform panel
//  Used by scripting real resize event
//  Will be used when resizing a group.
//  
//========================================================================================

#pragma once
#ifndef __IResizeItemsCmdData__
#define __IResizeItemsCmdData__

#include "IPMUnknown.h"
#include "GenericID.h"
#include "PMPoint.h"
#include "TransformTypes.h"

class IResizeItemsCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IRESIZEITEMSCMDDATA};
	enum ResizeMultiple { kAdjustInnerItemSpacing, kAdjustIndividualSizes};

	/**
		kResizeItemsCmdBoss changes the size of every item in its item list according 
		to the given newSize parameter.  The change is made in boundsSpace coordinates 
		relative to referencePoint.  The boundsKind parameter specifies whether
		the target size is for the bounding box of the mathematical path of each 
		item or the potentially larger stroke bounds.
		
		@boundsSpace is one of Transform::PasteboardCoordinates(), Transform::ParentCoordinates(), or Transform::InnerCoordinates()
		@boundsKind is one of Geometry::OuterStrokeBounds() or Geometry::PathBounds()
		@referencePoint is the stationary point of the resize operation
		@newSize is one of the following:
				Geometry::AddTo( Geometry::KeepCurrentValue(), y_delta)
				Geometry::AddTo( x_delta, Geometry::KeepCurrentValue())
				Geometry::AddTo( Geometry::KeepCurrentProportions(), y_delta)
				Geometry::AddTo( x_delta, Geometry::KeepCurrentProportions())
				Geometry::AddTo( x_delta, y_delta)

				Geometry::MultiplyBy( Geometry::KeepCurrentValue(), y_factor)
				Geometry::MultiplyBy( x_factor, Geometry::KeepCurrentValue())
				Geometry::MultiplyBy( Geometry::KeepCurrentProportions(), y_factor)
				Geometry::MultiplyBy( x_factor, Geometry::KeepCurrentProportions())
				Geometry::MultiplyBy( x_factor, y_factor)

				Geometry::ResizeTo( Geometry::KeepCurrentValue(), y_value)
				Geometry::ResizeTo( x_value, Geometry::KeepCurrentValue())
				Geometry::ResizeTo( Geometry::KeepCurrentProportions(), y_value)
				Geometry::ResizeTo( x_value, Geometry::KeepCurrentProportions())
				Geometry::ResizeTo( x_value, y_value)
				
		@resizeMultiple is one of the following: kAdjustInnerItemSpacing, kAdjustIndividualSizes
	*/

	virtual void SetResizeData(
				const Transform::CoordinateSpace &boundsSpace,
				Geometry::BoundsKind boundsKind,
				const Transform::TransformOrigin& referencePoint,
				const Geometry::ResizeValue& newSize,
				ResizeMultiple resizeMultiple = kAdjustInnerItemSpacing
			) = 0;


	/**
		GetBoundsSpace returns the boundsSpace specified by SetResizeData.
	*/
	virtual Transform::CoordinateSpace GetBoundsSpace() const = 0;

	/**
		GetBoundsKind returns the boundsKind specified by SetResizeData.
	*/
	virtual Geometry::BoundsKind GetBoundsKind() const = 0;

	/**
		GetResizeReferencePoint returns the referencePoint specified by SetResizeData.
	*/
	virtual Transform::TransformOrigin GetResizeReferencePoint() const = 0;

	/**
		GetResizeValue returns the newSize specified by SetResizeData.
	*/
	virtual Geometry::ResizeValue GetResizeValue() const = 0;

	/**
		GetResizeMultiple returns the resizeMultiple specified by SetResizeData.
	*/
	virtual ResizeMultiple GetResizeMultiple() const = 0;
};

#endif
