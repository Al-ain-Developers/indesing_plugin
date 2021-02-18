//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGeometry.h $
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
//  Purpose of Interface:
//  IGeometry is designed to be a "geometry independent" way of defining
//  an object, meaning that nothing in the interface makes any assumption as
//  to the item being rectangular, linear, etc.
//  
//  PageItems are defined by one or more points. It is up to the implementer to
//  decide how to interpret these point in order to get a BoundingBox, etc.
//  As a convenience there are two sets of methods, one for bounding box
//  with stroke and one for bounding box without stroke. For certain pageitems,
//  such as images, the path bounds and stroke bounds will be the same.
//  
//  Note: IGeometry does NOT draw. IShape is used for drawing and is implemented in
//  terms of IGeometry.
//  
//  IGeometry is a required interface of page items.
//  
//========================================================================================

#pragma once
#ifndef __IGeometry__
#define __IGeometry__

#include "IPMUnknown.h"
#include "PMReal.h"
#include "PMPoint.h"
#include "PMRect.h"
#include "PMMatrix.h"
#include "GraphicsID.h"
#include "TransformTypes.h"

/**
	IGeometry is designed to be a "geometry independent" way of defining
	an object, meaning that nothing in the interface makes any assumption as
	to the item being rectangular, linear, etc.
  
	PageItems are defined by one or more points. It is up to the implementer to
	decide how to interpret these point in order to get a BoundingBox, etc.
	As a convenience there are two sets of methods, one for bounding box
	with stroke and one for bounding box without stroke. For certain pageitems,
	such as images, the path bounds and stroke bounds will be the same.
  
	Note: IGeometry does NOT draw. IShape is used for drawing and is implemented in
	terms of IGeometry.
  
	IGeometry is a required interface of page items.
*/
class IGeometry : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IGEOMETRY };

	/**
		Get the bounding box that include stroke.
	
		@param theMatrix [In] parameter used to transform the BBox before returning. 
		For example, if you want a PasteBoardBBox, pass in an InnerToPasteboard Matrix.
		@return PMRect the result bounding box.
	*/
	virtual PMRect GetStrokeBoundingBox(const PMMatrix& theMatrix) const  = 0;

	/**
		Get the bounding box that include stroke but with no transformations done. 
		Bounding box returned is in inner coordinates.
	
		@return PMRect the result bounding box.
	*/
	virtual PMRect GetStrokeBoundingBox() const = 0;
	
	/**
		Set the bounding box with stroke in inner coordinates.
	
		@param newBBox [In] parameter used to set the new bounding box.
		@param whichAction [In] parameter used to specify the action for children when doing this operation.
		@return ErrorCode indicates the result of operation.
	*/
	virtual ErrorCode SetStrokeBoundingBox(const PMRect& newBBox /*, SetAction whichAction*/) = 0;
	
	/**
		Set the bounding box with stroke.
	
		@param theMatrix [In] parameter that may change the transform of the item depending on the implementation of IGeometry
		@param newBBox [In] parameter used to set the new bounding box.
		@param whichAction [In] parameter used to specify the action for children when doing this operation.
		@return ErrorCode indicates the result of operation.
	*/
	virtual ErrorCode SetStrokeBoundingBox(const PMMatrix& theMatrix, const PMRect& newBBox/*, SetAction whichAction*/) = 0;
	 
	/**
		Get the bounding box that exclude stroke but with no transformations done. 
	
		@param theMatrix [In] parameter used to transform the BBox before returning.
		For example, if you want a PasteBoardBBox, pass in an InnerToPasteboard Matrix.
		@return PMRect the result bounding box.
	*/
	virtual PMRect GetPathBoundingBox(const PMMatrix& theMatrix) const  = 0;

	/**
		Get the bounding box that exclude stroke. Bounding box returned is in inner coordinates.
	
		@return PMRect the result bounding box.
	*/
	virtual PMRect GetPathBoundingBox() const = 0;
	
	/**
		Set the bounding box without stroke in inner coordinates.
	
		@param newBBox [In] parameter used to set the new bounding box.
		@param whichAction [In] parameter used to specify the action for children when doing this operation.
		@return ErrorCode indicates the result of operation.
	*/
	virtual ErrorCode SetPathBoundingBox(const PMRect& newBBox/*, SetAction whichAction*/) = 0;
	
	/**
		Set the bounding box without stroke.
	
		@param theMatrix [In] parameter that may change the transform of the item depending on the implementation of IGeometry
		@param newBBox [In] parameter used to set the new bounding box.
		@param whichAction [In] parameter used to specify the action for children when doing this operation.
		@return ErrorCode indicates the result of operation.
	*/
	virtual ErrorCode SetPathBoundingBox(const PMMatrix& theMatrix, const PMRect& newBBox/*, SetAction whichAction*/) = 0;
	
	/**
		Get the proportion(width/height) including stroke. This is a helper method for constraining.

		@return PMReal by default this is the width of the bounding box divided by its height.
	*/
	virtual PMReal GetStrokeProportion() const = 0;
	
	/**
		Get the proportion(width/height) excluding stroke. This is a helper method for constraining.

		@return PMReal by default this is the width of the bounding box divided by its height.
	*/
	virtual PMReal GetPathProportion() const = 0;



	//These will need to be reworked when Geometry::InnerStrokeBounds() is added
	PMRect GetBoundingBox( Geometry::BoundsKind kind, const PMMatrix& theMatrix) const
	{
		kind = Geometry::ResolvePreferredBounds( kind);
		if( kind == Geometry::PathBounds()){ //BoundsKindCompare
			return GetPathBoundingBox( theMatrix);
		}else if( kind == Geometry::OuterStrokeBounds()){
			return GetStrokeBoundingBox( theMatrix);
		}else{
			ASSERT_UNIMPLEMENTED();
			return PMRect();
		}
	}

	PMRect GetBoundingBox( Geometry::BoundsKind kind) const
	{
		kind = Geometry::ResolvePreferredBounds( kind);
		if( kind == Geometry::PathBounds()){ //BoundsKindCompare
			return GetPathBoundingBox();
		}else if( kind == Geometry::OuterStrokeBounds()){
			return GetStrokeBoundingBox();
		}else{
			ASSERT_UNIMPLEMENTED();
			return PMRect();
		}
	}

	ErrorCode SetBoundingBox( Geometry::BoundsKind kind, const PMRect& newBBox)
	{
		kind = Geometry::ResolvePreferredBounds( kind);
		if( kind == Geometry::PathBounds()){ //BoundsKindCompare
			return SetPathBoundingBox( newBBox);
		}else if( kind == Geometry::OuterStrokeBounds()){
			return SetStrokeBoundingBox( newBBox);
		}else{
			ASSERT_UNIMPLEMENTED();
			return kFailure;
		}
	}

	ErrorCode SetBoundingBox( Geometry::BoundsKind kind, const PMMatrix& theMatrix, const PMRect& newBBox)
	{
		kind = Geometry::ResolvePreferredBounds( kind);
		if( kind == Geometry::PathBounds()){ //BoundsKindCompare
			return SetPathBoundingBox( theMatrix, newBBox);
		}else if( kind == Geometry::OuterStrokeBounds()){
			return SetStrokeBoundingBox( theMatrix, newBBox);
		}else{
			ASSERT_UNIMPLEMENTED();
			return kFailure;
		}
	}
				
};


#endif
