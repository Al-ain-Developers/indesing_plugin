//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IGeometryFacade.h $
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
#ifndef _IGeometry_Facade_
#define _IGeometry_Facade_

#include "GenericID.h"
#include "Utils.h"
#include "IReferencePointData.h"
#include "TransformTypes.h"
	
class AutomationContext;
class AutomationTargetingData;
class IScriptRequestData;

namespace Facade
	{
	class IGeometryFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_IGEOMETRYFACADE };

		virtual int32 GetGeometryItemsCount( const UIDList& items) const = 0;

		/**	Can any of the items change height?
			@return bool16 
		 */
		virtual bool16 CanChangeItemsHeight( const UIDList& items, const Transform::CoordinateSpace& boundsSpace) const = 0;	

		/**	Can any of the items change width?
			@return bool16 
		 */
		virtual bool16 CanChangeItemsWidth( const UIDList& items, const Transform::CoordinateSpace& boundsSpace) const = 0;	

		/**	Can any of the items change length?
			@return bool16 
		 */
		virtual bool16 CanChangeItemsLength( const UIDList& items, const Transform::CoordinateSpace& boundsSpace) const = 0;	


		/**	Does the UIDList have a height?
			@return kTrue if selection has a 'height' attribute, kFalse otherwise 
		 */
		virtual bool16 ItemsHaveHeight( const UIDList& items, const Transform::CoordinateSpace& boundsSpace) const = 0;	

		/**	Does the UIDList have a height?
			@return kTrue if selection has a 'width' attribute, kFalse otherwise 
		 */
		virtual bool16 ItemsHaveWidth( const UIDList& items, const Transform::CoordinateSpace& boundsSpace) const = 0;	


		/**	Return the height of the selection.
			@param K2Vector<PMReal>& 
			@param useStroke if kTrue GetStrokeDimensions, otherwise, GetPathDimensions
		 */
		virtual void GetItemsHeight( const UIDList& items, 
						const Transform::CoordinateSpace& boundsSpace,
						Geometry::BoundsKind boundsKind,
						const Transform::CoordinateSpace& measurementSpace,
						K2Vector<PMReal>& results) const = 0;	

		/**	Get the width of the selection.
			@param K2Vector<PMReal>& 
			@param useStroke if kTrue GetStrokeDimensions, otherwise, GetPathDimensions
		 */
		virtual void GetItemsWidth( const UIDList& items, 
						const Transform::CoordinateSpace& boundsSpace,
						Geometry::BoundsKind boundsKind,
						const Transform::CoordinateSpace& measurementSpace,
						K2Vector<PMReal>& results) const = 0;	

		/**	Get the width of the selection.
			@param K2Vector<PMReal>& 
			@param useStroke if kTrue GetStrokeDimensions, otherwise, GetPathDimensions
		 */
		virtual void GetItemsSize( const UIDList& items, 
						const Transform::CoordinateSpace& boundsSpace,
						Geometry::BoundsKind boundsKind,
						const Transform::CoordinateSpace& measurementSpace,
						K2Vector<PMPoint>& results) const = 0;	

		/**	Get the length of the selected items (note, it is not number of selected items)
			@param K2Vector<PMReal>& 
			@param useStroke if kTrue GetStrokeDimensions, otherwise, GetPathDimensions
		 */
		virtual void GetItemsLength( const UIDList& items,
						const Transform::CoordinateSpace& boundsSpace,
						Geometry::BoundsKind boundsKind,
						const Transform::CoordinateSpace& measurementSpace,
						K2Vector<PMReal>& results) const = 0;


		/**	This routine is used by panels to collect width and height info for a list of page items.
			It does the same work as GetItemsSize, GetItemsHeight, ItemsHaveWidth and ItemsHaveHeight but
			more efficiently because it can do it all at the same time.
			 @param K2Vector<PMReal>& [IN] the source page items
			 @param boundsSpace [IN] stroke bounds, path bounds, etc
			 @param measurementSpace [IN] inner coordinates, spread coordinates, etc.
			 @param widths [OUT] If non-nil, will contain the width values
			 @param heights [OUT] If non-nil, will contain the height values
			 @param itemsHaveWidth [OUT] If non-nil, will contain whether or not the items have width
			 @param itemsHaveHeight [OUT] If non-nil, will contain whether or not the items have height
		 */
		virtual void GetItemsDimensions ( const UIDList& items,
									 const Transform::CoordinateSpace& boundsSpace,
									 Geometry::BoundsKind boundsKind,
									 const Transform::CoordinateSpace& measurementSpace,
									 K2Vector<PMReal>* widths,
									 K2Vector<PMReal>* heights,
									 bool32 *itemsHaveWidth,
									 bool32 *itemsHaveHeight ) const = 0;

		/**
			ResizeItems changes the size of every item in items according to the given
			newSize parameter.  The change is made in coordinateSpace coordinates 
			relative to referencePoint.  The boundsKind parameter specifies whether
			the target size is for the bounding box of the mathematical path of each 
			item or the potentially larger stroke bounds.
			
			ResizeItems has the same effect as ReframeItems with respect to the page
			items contents.  (See the notes on ReframeItems below.)

			@param items is the list of page items to resize
			@param coordinateSpace is one of Transform::PasteboardCoordinates() or Transform::InnerCoordinates()
			@param referencePoint is the stationary point of the resize operation
			@param newSize is one of the following:
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
					
			@param boundsKind is one of Geometry::OuterStrokeBounds() or Geometry::PathBounds()
		*/
		virtual ErrorCode ResizeItems(
					const UIDList& items,
					const Transform::CoordinateSpace& boundsSpace,
					Geometry::BoundsKind boundsKind,
					const Transform::TransformOrigin& referencePoint, 
					const Geometry::ResizeValue& newSize) = 0;

		/**
			SetItemsBounds changes the bounding box of each item in items to the
			corresponding rectangle in newFrames.  The parameter coordinateSpace
			gives the coordinate system for every rectangle in newFrames.  The 
			parameter boundsKind specifies whether the rectangles are the target
			bounding boxes for the item's mathematical paths or the visible strokes.
			
			Note that changing the bounding box of a page item does not, in general,
			reposition any content within that page item that doesn't automatically 
			reflow on its own (like text or the children of a group do). In particular,
			an image within a graphic frame will be cropped by the new frame.  The pixels 
			themselves will not change in size or move on the page.  (If one reframes
			the image itself, rather than the graphic frame, the pixels are simply
			scaled so that the image fills the new size and position.)

			@param items is the list of page items to reframe
			@param coordinateSpace is one of Transform::PasteboardCoordinates() or Transform::InnerCoordinates()
			@param newFrames is the list of new frames--one corresponding te each item in items.
			@param boundsKind is one of Geometry::OuterStrokeBounds() or Geometry::PathBounds()
		*/

		virtual ErrorCode SetItemsBounds(
					const UIDList& items,
					const Transform::CoordinateSpace& coordinateSpace,
					Geometry::BoundsKind boundsKind,
					PMRectCollection& newFrames
					) = 0;


		/**
			@param itemRef is the page item to measure
			@param coordinateSpace is one of Transform::PasteboardCoordinates(), Transform::ParentCoordinates() or Transform::InnerCoordinates()
			@param boundsKind is one of Geometry::OuterStrokeBounds() or Geometry::PathBounds()
		*/
		virtual PMRect GetItemBounds( const UIDRef& itemRef, const Transform::CoordinateSpace& coordinateSpace, Geometry::BoundsKind kind) const = 0;

		/**
			@param items is the list of page items to measure
			@param coordinateSpace is one of Transform::PasteboardCoordinates() or Transform::ParentCoordinates()
			@param boundsKind is one of Geometry::OuterStrokeBounds() or Geometry::PathBounds()
		*/
		virtual PMRect GetItemsBounds( const UIDList& items, const Transform::CoordinateSpace& coordinateSpace, Geometry::BoundsKind kind) const = 0;


		/**	Construct a script event for the given resize parameters.
			@param scriptRequestData - a newly created IScriptRequestData
			@param boundsSpace - see ResizeItems
			@param boundsKind - see ResizeItems
			@param referencePoint - see ResizeItems
			@param newSize - see ResizeItems
		 */

		virtual ErrorCode ConstructResizeScriptMethod(
					IScriptRequestData* scriptRequestData,
					const Transform::CoordinateSpace& boundsSpace, 
					Geometry::BoundsKind boundsKind, 
					const Transform::TransformOrigin& referencePoint, 
					const Geometry::ResizeValue& newSize
				) = 0;

#ifdef ID_DEPRECATED
		/**	Record resize action.
			@param pAutomationContext - the automation context in which to record the action.
			@param boundsSpace - see ResizeItems
			@param boundsKind - see ResizeItems
			@param referencePoint - see ResizeItems
			@param newSize - see ResizeItems
			@param target - one of Transform::OriginalItems(), Transform::DuplicateItems()
		 */
		virtual ErrorCode RecordResize(
						AutomationContext* pAutomationContext,
						const Transform::CoordinateSpace& boundsSpace,
						Geometry::BoundsKind boundsKind,
						const Transform::TransformOrigin& referencePoint, 
						const Geometry::ResizeValue& newSize,
						Transform::Target target = Transform::OriginalItems()
					) = 0;


		/**	Add a resize user action atom.
			@param pAutomationContext - the automation context in which to record the action.
			@param boundsSpace - see ResizeItems
			@param boundsKind - see ResizeItems
			@param referencePoint - see ResizeItems
			@param newSize - see ResizeItems
			@param pAtomTargetData the desired user action targeting data.
		 */
		virtual ErrorCode AddResizeActionAtom(
					AutomationContext*	pAutomationContext,
					const Transform::CoordinateSpace& boundsSpace,
					Geometry::BoundsKind boundsKind,
					const Transform::TransformOrigin& referencePoint, 
					const Geometry::ResizeValue& newSize,
					AutomationTargetingData* pAtomTargetData = nil
					) = 0;
#endif
	};
}
#endif // _IGeometry_Facade_
