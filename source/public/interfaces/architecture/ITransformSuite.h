//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ITransformSuite.h $
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
#ifndef _ITransformSuite_
#define _ITransformSuite_

#include "IPMUnknown.h"
#include "ShuksanID.h"
#include "IScriptRequestData.h"
#include "TransformTypes.h"

/**	IID_ITRANSFORMSUITE interface; this interface involves selections; There will be 
	an implementation on the ASB which is referred to as the integrator, and different 
	selection format such as Layout, Text, Table and XML implement their own CSB;
	when client code ask for a method, it check current selection and let each selection CSB do their own work.
 */
class ITransformSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITRANSFORMSUITE };

	/**	Return the number of items that will be affected by the transform.
		@return int32 
	 */
	virtual int32 GetTransformItemsCount() const = 0;
	virtual bool16 SelectionHasTransformValues( const Transform::CoordinateSpace& coordinateSpace, uint32 valuesOfInterest) const = 0; 
	virtual bool16 CanChangeSelectionTransformValues( const Transform::CoordinateSpace& coordinateSpace, uint32 valuesOfInterest) const = 0;


	/**	Return all of the scale Xs (sorted and only unique values) in the selection.
		@param coordinateSpace - one of Transform::PasteboardCoordinates(), Transform::ParentCoordinates(), Transform::InnerCoordinates(). 
		@param results [OUT] Return result in "scaleXList"
		@param pbRelative [IN] whether tranform are relative to pasteboard
	 */
	virtual void GetSelectionScale( const Transform::CoordinateSpace& coordinateSpace, K2Vector<PMPoint>& results) const = 0;

	/**	Return all of the scale Xs (sorted and only unique values) in the selection.
		@param coordinateSpace - one of Transform::PasteboardCoordinates(), Transform::ParentCoordinates(), Transform::InnerCoordinates(). 
		@param results [OUT] Return result in "scaleXList"
		@param pbRelative [IN] whether tranform are relative to pasteboard
	 */
	virtual void GetSelectionScaleX( const Transform::CoordinateSpace& coordinateSpace, K2Vector<PMReal>& results) const = 0;

	/**	Return all of the scale Ys (sorted and only unique values) in the selection.
		@param coordinateSpace - one of Transform::PasteboardCoordinates(), Transform::ParentCoordinates(), Transform::InnerCoordinates(). 
		@param results [OUT] Return result in "scaleYList"
		@param pbRelative [IN] whether tranform are relative to pasteboard
	 */
	virtual void GetSelectionScaleY( const Transform::CoordinateSpace& coordinateSpace, K2Vector<PMReal>& results) const = 0;

	/**	Return all of the skew Xs (sorted and only unique values) in the selection.
		@param coordinateSpace - one of Transform::PasteboardCoordinates(), Transform::ParentCoordinates(), Transform::InnerCoordinates(). 
		@param results [OUT] Return result in "skewXList"
		@param pbRelative [IN] whether tranform are relative to pasteboard
	 */
	virtual void GetSelectionSkewAngle( const Transform::CoordinateSpace& coordinateSpace, K2Vector<PMReal>& results) const = 0;

	/**	Return all of the rotations (sorted and only unique values) in the selection.
		@param results [OUT] Return result in "rotationList"
		@param pbRelative [IN] whether tranform are relative to pasteboard
	 */
	virtual void GetSelectionRotationAngle( const Transform::CoordinateSpace& coordinateSpace, K2Vector<PMReal>& results) const = 0;

	/**	Get distinct (x,y) translations; asserts if not HasX() and not HasY()
		@param coordinateSpace - one of Transform::PasteboardCoordinates(), Transform::ParentCoordinates(), Transform::InnerCoordinates(). 
		@param K2Vector<PMPoint>& 
	 */
	virtual void GetSelectionTranslation( const Transform::CoordinateSpace& coordinateSpace, K2Vector<PMPoint>& results) const = 0;

	/**	Get distinct 'x' translations; asserts if not HasX()
		@param coordinateSpace - one of Transform::PasteboardCoordinates(), Transform::ParentCoordinates(), Transform::InnerCoordinates(). 
		@param K2Vector<PMReal>& 
	 */
	virtual void GetSelectionTranslationX( const Transform::CoordinateSpace& coordinateSpace, K2Vector<PMReal>& results) const = 0;

	/**	Get distinct 'y' translations; asserts if not HasY()
		@param coordinateSpace - one of Transform::PasteboardCoordinates(), Transform::ParentCoordinates(), Transform::InnerCoordinates(). 
		@param K2Vector<PMReal>& 
	 */
	virtual void GetSelectionTranslationY( const Transform::CoordinateSpace& coordinateSpace, K2Vector<PMReal>& results) const = 0;


	virtual ErrorCode TransformSelection( const Transform::CoordinateSpace& coordinateSpace, const Transform::TransformOrigin& referencePoint, 
						const Transform::TransformValue& xform, Transform::Target originalOrDuplicate = Transform::OriginalItems()) = 0;





	/**	Can the selection have its transform reset (to 100%)? 
		@param void 
		@return bool16 
	 */
	virtual bool16 CanRedefineSelectionScaling() const = 0;

	/**	Reset selected items to uniform 100% scaling.
		@param void 
		@return Command processing result
	 */
	virtual ErrorCode RedefineSelectionScaling() = 0;

	/**	Can the selection be reset to identity transform (remove rotation, skew and scaling)?
		@param void 
		@return bool16 
	 */
	virtual bool16 CanRemoveSelectionTransformations( const Transform::CoordinateSpace& coordinateSpace) const = 0;

	/**	Reset selected items to identity matrix (remove all rotation, skew and scaling).
		@param void 
		@return Command processing result
	 */
	virtual ErrorCode RemoveSelectionTransformations( const Transform::CoordinateSpace& coordinateSpace) = 0;

	/**	Detect if can copy and transform selected items.
		@param none
		@return bool16
	 */
	virtual bool16 CanCopyTransform() const = 0;

	/**	Can Tranform Again be done?
		@param void 
		@return bool16 
	 */
	virtual bool16 HasTransformAgainAbility() const = 0;

	/**	Can Tranform Last Again be done?
		@param void 
		@return bool16 
	 */
	virtual bool16 HasTransformLastAgainAbility() const = 0;

	/**	Transform Again
		@param iContext the context
		@param scriptTargetHandlingPolicy the script target handling policy
		@return ErrorCode 
	 */
	virtual ErrorCode TransformAgain( IActiveContext* iContext,
							IScriptRequestData::TargetHandlingPolicy scriptTargetHandlingPolicy) = 0;

	/**	Transform Last Again
		@param iContext the context
		@param scriptTargetHandlingPolicy the script target handling policy
		@return ErrorCode 
	 */
	virtual ErrorCode TransformLastAgain( IActiveContext* iContext,
							IScriptRequestData::TargetHandlingPolicy scriptTargetHandlingPolicy) = 0;
						
	/**	Private use only
	 */
	virtual void EnableTransformAgainSelectionObserver() = 0;

	/**	Private use only
	 */
	virtual void DisableTransformAgainSelectionObserver() = 0;

};

#endif // _ITransformSuite_
