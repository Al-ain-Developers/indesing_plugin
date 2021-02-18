//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ITransform.h $
//  
//  Owner: Zak_Williamson
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
//  Defines the interface for a 3x3 transform.
//  
//  Purpose of Interface;
//  A persistant interface containing transformation data for a page item
//  
//========================================================================================

#pragma once
#ifndef __ITRANSFORM__
#define __ITRANSFORM__

#include "IPMUnknown.h"
#include "GenericID.h"
#include "TransformTypes.h"
#include "PMReal.h"

class PMRect;
class PMPoint;
class PMMatrix;
class PMPolygon4;
class IGraphicsPort;

/**
	A persistant interface containing transformation data(3x3 tranform) for a page item.
*/
class ITransform : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITRANSFORM };

	/**
		Get item's x direction scale percentage.
		@return PMReal x scale percentage.
	*/
	virtual PMReal GetItemScaleX() const = 0;

	/**
		Get item's y direction scale percentage.
		@return PMReal y scale percentage.
	*/
	virtual PMReal GetItemScaleY() const = 0;

	/**
		Get item's x direction skew angle.
		@return PMReal the angle ranges from -90 to 90.
	*/
	virtual PMReal GetItemSkewAngle() const = 0;

	/**
		Get item's rotate angle.
		@return PMReal rotate angle ranges from 0 to 360.
	*/
	virtual PMReal GetItemRotationAngle() const = 0;

	/**
		Scale item with certain x/y values based on the given reference point.
		@param xScale [IN] parameter the x value the item scale by.
		@param yScale [IN] parameter the y value the item scale by.
		@param center [IN] parameter the reference point in parent coordinate.
		@return void.
	*/
	virtual void ScaleItemBy( PMReal xScale, PMReal yScale, const PMPoint& center) = 0;

	/**
		Scale item to certain x/y values based on the given reference point.
		@param xScale [IN] parameter the absolute x value the item scale by.
		@param yScale [IN] parameter the absolute y value the item scale by.
		@param center [IN] parameter the reference point in parent coordinate.
		@return void.
	*/
	virtual void ScaleItemTo( PMReal xScale, PMReal yScale, const PMPoint& center) = 0;

	/**
		Skew item to certain angle based on the given reference point.
		We only directly support xSkew but not ySkew. To perform a skew in the y direction,
		skew in the x direction by the angle desired, and then rotate by the same angle.
		@see GetXSkewAngle for more information.
		@param xSkewAngle [IN] parameter the absolute angle the item skew by.
		@param center [IN] parameter the reference point in parent coordinate.
		@return void.
	*/
	virtual void SkewItemTo( PMReal xSkewAngle, const PMPoint& center) = 0;

	/**
		Skew item with certain angle based on the given reference point.
		We only directly support xSkew but not ySkew. To perform a skew in the y direction,
		skew in the x direction by the angle desired, and then rotate by the same angle.
		@see GetXSkewAngle for more information.
		@param xSkewAngle [IN] parameter the angle the item skew by.
		@param center [IN] parameter the reference point in parent coordinate.
		@return void.
	*/
	virtual void SkewItemBy( PMReal xSkewAngle, const PMPoint& center) = 0;

	/**
		Rotate item with certain angle based on the given reference point.
		@param angle [IN] parameter the angle the item rotate by.
		@param center [IN] parameter the reference point in parent coordinate.
		@return void.
	*/
	virtual void RotateItemBy( PMReal angle, const PMPoint& center) = 0;

	/**
		Rotate item to certain angle based on the given reference point.

		@param angle [IN] parameter the absolute angle the item rotate to.
		@param center [IN] parameter the reference point in parent coordinate.
		@return void.
	*/
	virtual void RotateItemTo( PMReal angle, const PMPoint& center) = 0;

	/**
		Move item with delta amount of distance.
		@param delta [IN] parameter the amount of distance in parent coordinate.
		@return void.
	*/
	virtual void TranslateItemBy( const PMPoint& delta) = 0;

	/**
		Move item to the specified location.
		@param location [IN] parameter the place in parent coordinate where the item will move to.
		@return void.
	*/
	virtual void TranslateItemTo( const PMPoint& location) = 0;



	/**
		Re-orient the item relative to its parent with a new transformation matrix.
		@param matrix [IN] parameter the given matrix to be set.
		@return void.
	*/
	virtual void SetInnerToParentMatrix( const PMMatrix& matrix) = 0; //t_SetMatrix

	/**
		Get this item's current inner-to-parent matrix.  Note even though
		the matrix is returned by reference, you must use the result immediately
		or copy the result to another PMMatrix.
		@return const PMMatrix the item's matrix.
	*/
	virtual const PMMatrix& GetInnerToParentMatrix() const = 0;

	/**
		Get this item's current parent-to_inner matrix.  Note even though
		the matrix is returned by reference, you must use the result immediately
		or copy the result to another PMMatrix.

		@return const PMMatrix the item's inverse matrix.
	*/
	virtual const PMMatrix& GetParentToInnerMatrix() const = 0; //t_CurrentInverseMatrix




	/**
		Get the inner to root matrix by walking up the hierarchy. Some items such as inline have
		specific implementations of this interface to compute the matrix differently.
		Some implementations of ITransform may want to cache the result of GetInnerToRootMatrix
		But other implementations of ITransform may be generated dynamically thereby rendering
		all child caches invalid. On items that have dynamic transforms, GetInnerToRootMatrix
		will return kDynamicMatrix and that return value should be passed down the hierarchy.
		kStaticMatrix means the matrix is set via the normal SetMatrix call which will result
		in a parentchanged call. It is OK to cache the matrix when GetInnerToRootMatrix returns kStaticMatrix.
		But you should never cache the matrix when GetInnerToRootMatrix returns kDynamicMatrix.

		@param pMatrix [IN] parameter which is to perform the post concatenate.
		@param pRoot [IN] parameter the root item's transform information.
		@return MatrixType either kStaticMatrix or kDynamicMatrix.
	*/
	enum MatrixType { kDynamicMatrix, kStaticMatrix};
	virtual ITransform::MatrixType GetInnerToRootMatrix( PMMatrix *pMatrix, const ITransform *pRoot = nil ) const = 0;

	/**
		Check whether the item can be transformed independent of its parent or not.
		@return bool16 kTrue if the item is dependent of its parent, otherwise kFalse.
	*/
	virtual bool16 IsTransformParentDependent() const = 0;

	/**
		Return an interface pointer to the "transformational parent" of this item. That
		is, the item whose transformation is concatenated to the current state before ours.
		For a typical pageitem, this would use IHierarchy::QueryParent() and return that item,
		but for some (like inlines and standoffs), it's not so simple.
		Used by TransformUtils::TransformFromRoot().
		@return IPMUnknown* the returned interface and caller should deference the interface.
	*/
	virtual IPMUnknown* QueryTransformParent() = 0;

	/**
		Concatenate this item's transformation, if necessary, into the gPort. Typically this
		is a simple gPort->concat(CurrentMatrix()), but for some it involves an additional
		transform as well, and for others (like standoffs), the transform needs to be ignored.
		Used by TransformUtils::TransformFromRoot().

		@param gPort [IN] parameter the graphics port that does the concatenate.
		@return void.
	*/
	virtual void ConcatItemTransform(IGraphicsPort *gPort) = 0;

};

#endif	// __ITRANSFORM__
