//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IGeometrySuite.h $
//  
//  Owner: Michael Martz
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
//  Note:
//  
//========================================================================================

#pragma once
#ifndef _IGeometrySuite_
#define _IGeometrySuite_
//________________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________________
#include "IPMUnknown.h"
#include "ShuksanID.h"
#include "PMRect.h"
#include "PMPoint.h"
#include "TransformTypes.h"
#include "IReferencePointData.h"

class PathInfo;

/**	IID_IGEOMETRYSUITE interface; this interface involves selections, different selection
	(concrete selection), such as Layout, Text, Table etc. implemention it own, when
	clieent code ask for a method, it check current selection and let each selection CSB do their own.
 */
class IGeometrySuite : public IPMUnknown
{
public:

	enum { kDefaultIID = IID_IGEOMETRYSUITE };
friend class GeometrySuiteASB;

	virtual Transform::CoordinateSpace DefaultMeasurementSpace() const = 0;
	virtual Transform::CoordinateSpace DefaultBoundsSpace() const = 0;

//protected:
	
	virtual int32 GetGeometryItemsCount() const = 0;

	/**	Can any of the CSBs change height?
		@return bool16 
	 */
	virtual bool16 CanChangeSelectionHeight( const Transform::CoordinateSpace& boundsSpace) const = 0;	

	/**	Can any of the CSBs change width?
		@return bool16 
	 */
	virtual bool16 CanChangeSelectionWidth( const Transform::CoordinateSpace& boundsSpace) const = 0;	

	/**	Can any of the CSBs change width?
		@return bool16 
	 */
	virtual bool16 CanChangeSelectionSize( const Transform::CoordinateSpace& boundsSpace) const = 0;	

	/**	Can any of the CSBs change length?
		@return bool16 
	 */
	virtual bool16 CanChangeSelectionLength( const Transform::CoordinateSpace& boundsSpace) const = 0;	

	/**	Is selection a straight line
		@param pathInfo path (points) information see IPathInfoUtils.h
		@return  kTrue if path is a straight line, kFalse otherwise
	 */
public:
	virtual bool16	SelectionIsAStraightLine(PathInfo *pathInfo) const = 0;

	/**	Is path a single point
		@param pathInfo path 
		@return  kTrue if path is a single point, kFalse otherwise
	 */
	virtual bool16	SelectionIsAPoint(PathInfo *pathInfo) const = 0;
//protected:

	/**	Does the selection have a height?
		@return kTrue if selection has a 'height' attribute, kFalse otherwise 
	 */
	virtual bool16 SelectionHasHeight( const Transform::CoordinateSpace& boundsSpace) const = 0;	

	/**	Does the selection have a height?
		@return kTrue if selection has a 'width' attribute, kFalse otherwise 
	 */
	virtual bool16 SelectionHasWidth( const Transform::CoordinateSpace& boundsSpace) const = 0;	

	/**	Does the selection have a height?
		@return kTrue if selection has a 'width' attribute, kFalse otherwise 
	 */
	virtual bool16 SelectionHasSize( const Transform::CoordinateSpace& boundsSpace) const = 0;	


	/**	This routine is used by panels to collect width and height info for a list of page items.
	 It does the same work as GetItemsSize, GetItemsHeight, ItemsHaveWidth and ItemsHaveHeight but
	 more efficiently because it can do it all at the same time.
	 @param boundsSpace [IN] stroke bounds, path bounds, etc
	 @param measurementSpace [IN] inner coordinates, spread coordinates, etc.
	 @param widths [OUT] If non-nil, will contain the width values
	 @param heights [OUT] If non-nil, will contain the height values
	 @param itemsHaveWidth [OUT] If non-nil, will contain whether or not the items have width
	 @param itemsHaveHeight [OUT] If non-nil, will contain whether or not the items have height
	 */
	virtual void GetSelectionDimensions_( const Transform::CoordinateSpace& boundsSpace,
									 Geometry::BoundsKind boundsKind,
									 const Transform::CoordinateSpace& measurementSpace,
									 K2Vector<PMReal>* widths,
									 K2Vector<PMReal>* heights,
									 bool32 *itemsHaveWidth,
									 bool32 *itemsHaveHeight ) const = 0;
	virtual void GetSelectionDimensions_( Geometry::BoundsKind boundsKind,
									 const Transform::CoordinateSpace& measurementSpace,
									 K2Vector<PMReal>* widths,
									 K2Vector<PMReal>* heights,
									 bool32 *itemsHaveWidth,
									 bool32 *itemsHaveHeight ) const = 0;
	
	/**
		ResizeSelection changes the size of every selected item according to the 
		given newSize parameter.  The change is made in coordinateSpace coordinates 
		relative to referencePoint.  The boundsKind parameter specifies whether
		the target size is for the bounding box of the mathematical path of each 
		selected item or the potentially larger stroke bounds.
		
		Note that resizing a selected page item does not, in general, reposition 
		any content within that page item that doesn't automatically reflow on 
		its own (like text or the children of a group). In particular, an image 
		within a graphic frame will be cropped by the newly sized frame.  The pixels 
		themselves will not change in size or move on the page.  (If one resizes
		the image itself, rather than the graphic frame, the pixels are simply
		scaled so that the image fills the new frame.)

		@coordinateSpace is one of Transform::PasteboardCoordinates() or Transform::InnerCoordinates()
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
				
		@boundsKind is one of Geometry::OuterStrokeBounds() or Geometry::PathBounds()
	*/

	virtual ErrorCode ResizeSelection(
				const Transform::CoordinateSpace& boundsSpace,
				Geometry::BoundsKind boundsKind,
				const Transform::TransformOrigin& referencePoint,
				const Geometry::ResizeValue& newSize,
				Transform::Target duplicate = Transform::OriginalItems()) = 0;

	virtual ErrorCode ResizeSelection(
				Geometry::BoundsKind boundsKind,
				const Transform::TransformOrigin& referencePoint,
				const Geometry::ResizeValue& newSize,
				Transform::Target duplicate = Transform::OriginalItems()) = 0;

	/**	Return the height of the selection.
		@coordinateSpace is one of Transform::PasteboardCoordinates() or Transform::InnerCoordinates()
		@boundsKind is one of Geometry::OuterStrokeBounds() or Geometry::PathBounds()
		@param K2Vector<PMReal>& 
	 */
	virtual void GetSelectionHeight( const Transform::CoordinateSpace& boundsSpace, Geometry::BoundsKind boundsKind, const Transform::CoordinateSpace& measurementSpace, K2Vector<PMReal>& results) const = 0;	
	virtual void GetSelectionHeight( Geometry::BoundsKind boundsKind, const Transform::CoordinateSpace& measurementSpace, K2Vector<PMReal>& results) const = 0;	

	/**	Get the width of the selection.
		@coordinateSpace is one of Transform::PasteboardCoordinates() or Transform::InnerCoordinates()
		@boundsKind is one of Geometry::OuterStrokeBounds() or Geometry::PathBounds()
		@param K2Vector<PMReal>& 
	 */
	virtual void GetSelectionWidth( const Transform::CoordinateSpace& boundsSpace, Geometry::BoundsKind boundsKind, const Transform::CoordinateSpace& measurementSpace, K2Vector<PMReal>& results) const = 0;
	virtual void GetSelectionWidth( Geometry::BoundsKind boundsKind, const Transform::CoordinateSpace& measurementSpace, K2Vector<PMReal>& results) const = 0;	

	/**	Get the length of the selected items (note, it is not number of selected items)
		@coordinateSpace is one of Transform::PasteboardCoordinates() or Transform::InnerCoordinates()
		@boundsKind is one of Geometry::OuterStrokeBounds() or Geometry::PathBounds()
		@param K2Vector<PMReal>& 
	 */
	virtual void GetSelectionLength( const Transform::CoordinateSpace& boundsSpace, Geometry::BoundsKind boundsKind, const Transform::CoordinateSpace& measurementSpace, K2Vector<PMReal>& results) const = 0;
	virtual void GetSelectionLength( Geometry::BoundsKind boundsKind, const Transform::CoordinateSpace& measurementSpace, K2Vector<PMReal>& results) const = 0;

	/**	Get the rectangular size of the selection.
		@coordinateSpace is one of Transform::PasteboardCoordinates() or Transform::InnerCoordinates()
		@boundsKind is one of Geometry::OuterStrokeBounds() or Geometry::PathBounds()
		@param K2Vector<PMReal>& 
	 */
	virtual void GetSelectionSize( const Transform::CoordinateSpace& boundsSpace, Geometry::BoundsKind boundsKind, const Transform::CoordinateSpace& measurementSpace, K2Vector<PMPoint>& results) const = 0;
	virtual void GetSelectionSize( Geometry::BoundsKind boundsKind, const Transform::CoordinateSpace& measurementSpace, K2Vector<PMPoint>& results) const = 0;


	/**	Get the bounds of the selected items
		@coordinateSpace is one of Transform::PasteboardCoordinates() or Transform::InnerCoordinates()
		@boundsKind is one of Geometry::OuterStrokeBounds() or Geometry::PathBounds()
	 */
	virtual PMRect GetSelectionBounds( const Transform::CoordinateSpace& boundsSpace, Geometry::BoundsKind kind) const = 0;

	/**	Fill out the path info for the selection.
		@param pathInfo 
	 */
public:
	virtual void GetSelectionPathInfo( PathInfo *pathInfo) const = 0;




	inline bool16 CanChangeSelectionHeight() const
	{
		return CanChangeSelectionHeight( DefaultBoundsSpace());
	}
	inline bool16 CanChangeSelectionWidth() const
	{
		return CanChangeSelectionWidth( DefaultBoundsSpace());
	}
	inline bool16 CanChangeSelectionSize() const
	{
		return CanChangeSelectionSize( DefaultBoundsSpace());
	}
	inline bool16 CanChangeSelectionLength() const
	{
		return CanChangeSelectionLength( DefaultBoundsSpace());
	}
	inline bool16 SelectionHasHeight() const
	{
		return SelectionHasHeight( DefaultBoundsSpace());
	}
	inline bool16 SelectionHasWidth() const
	{
		return SelectionHasWidth( DefaultBoundsSpace());
	}
	inline bool16 SelectionHasSize() const
	{
		return SelectionHasSize( DefaultBoundsSpace());
	}
	inline void GetSelectionHeight( Geometry::BoundsKind boundsKind, K2Vector<PMReal>& results) const
	{
		return GetSelectionHeight( DefaultBoundsSpace(), boundsKind, DefaultMeasurementSpace(), results);
	}
	inline void GetSelectionWidth( Geometry::BoundsKind boundsKind, K2Vector<PMReal>& results) const
	{
		return GetSelectionWidth( DefaultBoundsSpace(), boundsKind, DefaultMeasurementSpace(), results);
	}
	inline void GetSelectionLength( Geometry::BoundsKind boundsKind, K2Vector<PMReal>& results) const
	{
		return GetSelectionLength( DefaultBoundsSpace(), boundsKind, DefaultMeasurementSpace(), results);
	}
	inline void GetSelectionSize( Geometry::BoundsKind boundsKind, K2Vector<PMPoint>& results) const
	{
		return GetSelectionSize( DefaultBoundsSpace(), boundsKind, DefaultMeasurementSpace(), results);
	}
	inline void GetSelectionDimensions_( Geometry::BoundsKind boundsKind, K2Vector<PMReal>* widths, K2Vector<PMReal>* heights, bool32 *itemsHaveWidth, bool32 *itemsHaveHeight) const
	{
		return GetSelectionDimensions_( DefaultBoundsSpace(), boundsKind, DefaultMeasurementSpace(), widths, heights, itemsHaveWidth, itemsHaveHeight);
	}


};

#endif // _IGeometrySuite_
