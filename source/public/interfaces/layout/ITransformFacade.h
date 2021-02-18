//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ITransformFacade.h $
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
#ifndef __ITransformFacade__
#define __ITransformFacade__

#include "TransformTypes.h"
#include "GenericID.h"
#include "IScaleObject.h"

class AutomationContext;
class AutomationTargetingData;
class ISelectionManager;
class PathSelectionList;
class IScriptRequestData;

namespace Facade
	{
	class ITransformFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_ITRANSFORMFACADE };

		
		
		/**	Do the page items have the requested transform values
			@param items - the items to check 
			@param valuesOfInterest - one or more of {Transform::kScaleXValue, Transform::kScaleYValue, Transform::kSkewValue, Transform::kRotationValue, Transform::kTranslationXValue, Transform::kTranslationYValue} OR'd together
			@return whether the items have all of the requested transform values 
		 */
		virtual bool16 ItemsHaveTransformValues( const UIDList& items, const Transform::CoordinateSpace& coordinateSpace, uint32 valuesOfInterest) const = 0;

		/**	Can the page items requested transform values be changed
			@param items - the items to check 
			@param valuesOfInterest - one or more of {Transform::kScaleXValue, Transform::kScaleYValue, Transform::kSkewValue, Transform::kRotationValue, Transform::kTranslationXValue, Transform::kTranslationYValue} OR'd together
			@return whether the items can have all of the requested transform values changed
		 */
		virtual bool16 CanChangeItemsTransformValues( const UIDList& items, const Transform::CoordinateSpace& coordinateSpace, uint32 valuesOfInterest) const = 0;

		/**	Return the x and y scale factors of items.
			@param items - the items to check 
			@param coordinateSpace - one of Transform::PasteboardCoordinates(), Transform::ParentCoordinates(), Transform::InnerCoordinates()
			@param xResults [OUT] the x scale factors
			@param yResults [OUT] the y scale factors
		 */
		virtual void GetItemsScale( const UIDList& items, const Transform::CoordinateSpace& coordinateSpace, K2Vector<PMReal>* xResults, K2Vector<PMReal>* yResults) const = 0;

		/**	Return the x and y scale factors of items.
			@param items - the items to check 
			@param coordinateSpace - one of Transform::PasteboardCoordinates(), Transform::ParentCoordinates(), Transform::InnerCoordinates()
			@param results - the x and y scale factors returned as PMPoint data"
		 */
		virtual void GetItemsScale( const UIDList& items, const Transform::CoordinateSpace& coordinateSpace, K2Vector<PMPoint>& results) const = 0;

		/**	Return the skew angles of items.
			@param items - the items to check 
			@param coordinateSpace - one of Transform::PasteboardCoordinates(), Transform::ParentCoordinates(), Transform::InnerCoordinates()
			@param results [OUT] the skew angles in degrees
		 */
		virtual void GetItemsSkewAngle( const UIDList& items, const Transform::CoordinateSpace& coordinateSpace, K2Vector<PMReal>& results) const = 0;

		/**	Return the rotation angles of items.
			@param items - the items to check 
			@param coordinateSpace - one of Transform::PasteboardCoordinates(), Transform::ParentCoordinates(), Transform::InnerCoordinates()
			@param results [OUT] the rotation angles in degrees
		 */
		virtual void GetItemsRotationAngle( const UIDList& items, const Transform::CoordinateSpace& coordinateSpace, K2Vector<PMReal>& results) const = 0;


		/**	Return the location of the inner origins of items.
			@param items - the items to check 
			@param coordinateSpace - one of Transform::PasteboardCoordinates(), Transform::ParentCoordinates(), Transform::InnerCoordinates()
			@param xResults [OUT] the x locations
			@param yResults [OUT] the y locations
		 */
		virtual void GetItemsTranslation( const UIDList& items, const Transform::CoordinateSpace& coordinateSpace, K2Vector<PMReal>* xResults, K2Vector<PMReal>* yResults) const = 0;

		/**	Return the location of the inner origins of items.
			@param items - the items to check 
			@param coordinateSpace - one of Transform::PasteboardCoordinates(), Transform::ParentCoordinates(), Transform::InnerCoordinates()
			@param results [OUT] the (x,y) locations
		 */
		virtual void GetItemsTranslation( const UIDList& items, const Transform::CoordinateSpace& coordinateSpace, K2Vector<PMPoint>& results) const = 0;

		/**	Return the transformation matrices of items.
			@param items - the items to check 
			@param coordinateSpace - one of Transform::PasteboardCoordinates(), Transform::ParentCoordinates(), Transform::InnerCoordinates()
			@param results [OUT] the transformation matrices
		 */
		virtual void GetItemsTransform( const UIDList& items, const Transform::CoordinateSpace& coordinateSpace, K2Vector<PMMatrix>& results) const = 0;





		/**	Transform page items.
			@param items - the page items to transform 
			@param coordinateSpace - one of Transform::PasteboardCoordinates(), Transform::ParentCoordinates(), Transform::InnerCoordinates()
			@param referencePoint - temporary origin during the transformation
			@param xform - one of the values defined in TransformTypes.h  e.g. Transform::ScaleBy( xscale, yscale)
		 */
		virtual ErrorCode TransformItems
							(
								const UIDList& items,
								const Transform::CoordinateSpace& coordinateSpace,
								const Transform::TransformOrigin& referencePoint, 
								const Transform::TransformValue& xform,
								Transform::ScaleMethod scaleMethod = Transform::ConsultScalingPreference()
							) = 0;


		/**	Transform path points.
			@param pathPoints - the path points to transform 
			@param coordinateSpace - one of Transform::PasteboardCoordinates(), Transform::ParentCoordinates(), Transform::InnerCoordinates()
			@param referencePoint - temporary origin during the transformation
			@param xform - one of the values defined in TransformTypes.h  e.g. Transform::ScaleBy( xscale, yscale)
		 */
		virtual ErrorCode TransformPathPoints
							(
								const PathSelectionList& pathPoints,
								const Transform::CoordinateSpace& coordinateSpace,
								const Transform::TransformOrigin& referencePoint, 
								const Transform::TransformValue& xform
							) = 0;


		/**	Construct a script event for the given transform parameters.
			@param scriptRequestData - a newly created IScriptRequestData
			@param coordinateSpace - see TransformItems
			@param referencePoint - see TransformItems
			@param xform - see TransformItems
		 */
		virtual ErrorCode ConstructTransformScriptMethod
							(
								IScriptRequestData* scriptRequestData,
								const Transform::CoordinateSpace& coordinateSpace,
								const Transform::TransformOrigin& referencePoint,
								const Transform::TransformValue& xform
							) = 0;

#ifdef ID_DEPRECATED
		/**	RecordTransformItems.
			@param automationContext - automation context in which the event is recorded,
			@param coordinateSpace - one of Transform::PasteboardCoordinates(), Transform::ParentCoordinates(), Transform::InnerCoordinates()
			@param referencePoint - temporary origin during the transformation
			@param xform - one of the values defined in TransformTypes.h  e.g. Transform::ScaleBy( xscale, yscale)
			@param doDuplicate - one of Transform::OriginalItems(), Transform::DuplicateItems()
		 */
		virtual ErrorCode RecordTransform
							(
								AutomationContext*	automationContext,
								const Transform::CoordinateSpace& coordinateSpace,
								const Transform::TransformOrigin& referencePoint, 
								const Transform::TransformValue& xform,
								Transform::Target doDuplicate = Transform::OriginalItems()
							) = 0;


		/**	AddTransformItemsActionAtom.
			@param automationContext - automation context in which the event is recorded,
			@param coordinateSpace - one of Transform::PasteboardCoordinates(), Transform::ParentCoordinates(), Transform::InnerCoordinates()
			@param referencePoint - temporary origin during the transformation
			@param xform - one of the values defined in TransformTypes.h  e.g. Transform::ScaleBy( xscale, yscale)
		 */
		virtual ErrorCode AddTransformActionAtom
							(
								AutomationContext*	automationContext,
								const Transform::CoordinateSpace& coordinateSpace,
								const Transform::TransformOrigin& referencePoint, 
								const Transform::TransformValue& xform,
								AutomationTargetingData*
							) = 0;
#endif




		/**	Return the number of items that will be affected by a transform
			@param items - the items in question
			@return Resulting number of items
		 */
		virtual int32 GetTransformItemsCount( const UIDList& items) const = 0;



		/**	Can the item(s) have their scaling reset to 100% by moving the scale effect onto the item's content? 
			@param items - the items in question
			@return True if some of the selected items (or their children) have non-100% scaling transforms
		 */
		virtual bool16 CanRedefineItemsScaling( const UIDList& items) const = 0;

		/**	Can the item(s) have their scaling reset to (xScale,yScale) by moving the scale effect onto the item's content? 
			@param items - the items in question
			@return True if some of the selected items (or their children) have non-(xScale,yScale) scaling transforms
		 */
		virtual bool16 CanRedefineItemsScalingAs( const UIDList& items, PMReal xScale, PMReal yScale) const = 0;

		/**	Reset scaling to 100% by moving the scale effect onto the item's content.
			@param items - the items to modify
			@return Command processing result
		 */
		virtual ErrorCode RedefineItemsScaling( const UIDList& items) = 0;

		/**	Reset selected items to  to the specified scaling -- a generalization of RedefineItemsScaling.
			@param optionalContext - for internal use only, pass in nil
			@param items - the items to modify
			@param xScale - the target horizontal factor
			@param yScale - the target vertical factor
			@return Command processing result
		 */
		virtual ErrorCode RedefineItemsScalingAs( IScaleObject::ScaleContext* optionalContext, const UIDList& items, PMReal xScale, PMReal yScale) = 0;

		/**	Can the item(s) have their transform reset to identity (remove rotation, skew and scaling)? 
			@param items - the items in question
			@return True if some of the selected items can be rotated, skewed, or scaled.
		 */
		virtual bool16 CanRemoveItemsTransformations( const UIDList& items, const Transform::CoordinateSpace& coordinateSpace) const = 0;

		/**	Reset selected items to identity transform matrix (remove rotation, skew and scaling).
			@param items - the items to modify
			@return Command processing result
		 */
		virtual ErrorCode RemoveItemsTransformations( const UIDList& items, const Transform::CoordinateSpace& coordinateSpace) = 0;



		/**	Add a Transform Again Sentinel Command on the stack - private use only
			@param iDataBase - target for the command
			@return ErrorCode 
		 */
		virtual ErrorCode ProcessTransformAgainSentinelCommand( IDataBase* iDataBase) = 0;

		/**	Private use only
		 */
		virtual void EnableTransformAgainSelectionObserver (ISelectionManager*) = 0;

		/**	Private use only
		 */
		virtual void DisableTransformAgainSelectionObserver (ISelectionManager*) = 0;

	};
}
#endif // __ITransformFacade__
