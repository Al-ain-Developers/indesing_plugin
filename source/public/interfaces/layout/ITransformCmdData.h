//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ITransformCmdData.h $
//  
//  Owner: Lin Xia
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
//  Data interface for generic transform command. 
//  Caller of the command should set a transform matrix and the type of the transformation,
//  which can be a combination of move, rotate, scale, and skew.
//  Note transform context and if it is absolute is implied in the transformation matrix.
//  
//========================================================================================

#pragma once
#ifndef __ITransformCmdData__
#define __ITransformCmdData__

#include "IPMUnknown.h"
#include "ITransform.h"
#include "GenericID.h"
#include "PMPoint.h"
#include "PMMatrix.h"

class ITransformCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITRANSFORMCMDDATA };


	/**	SetTransformData sets up the command data for tranform commands.
		@param coordinateSpace - one of Transform::PasteboardCoordinates(), Transform::ParentCoordinates(), Transform::InnerCoordinates()
		@param referencePoint - temporary origin during the transformation
		@param xform - one of the values defined in TransformTypes.h  e.g. Transform::ScaleBy( xscale, yscale)
		@param scaleMethod - one of the Transform::UseLensScaling(), Transform::UseContentScaling(), or Transform::ConsultScalingPreference()
	 */
	virtual void SetTransformData(
						const Transform::CoordinateSpace &coordinateSpace,
						const Transform::TransformOrigin& referencePoint,
						const Transform::TransformValue& xform,
						Transform::ScaleMethod scaleMethod = Transform::ConsultScalingPreference()) = 0;

	/**	GetTransformCoordinates returns the CoordinateSpace parameter set by SetTransformData.
	 */
	virtual Transform::CoordinateSpace GetTransformCoordinates() const = 0;

	/**	GetTransformReferencePoint returns the TransformOrigin parameter set by SetTransformData.
	 */
	virtual Transform::TransformOrigin GetTransformReferencePoint() const = 0;

	/**	GetTransformValue returns the TransformValue parameter set by SetTransformData.
	 */
	virtual Transform::TransformValue GetTransformValue() const = 0;

	/**	GetTransformContent returns the matrix content of the TransformValue parameter set by SetTransformData. (see PMMatrix::GetMatrixContent).
	 */
	virtual uint32 GetTransformContent() const = 0;

	/**	GetScaleMethod returns the ScaleMethod parameter set by SetTransformData.
	 */
	virtual Transform::ScaleMethod GetScaleMethod() const = 0;
	
	/**	SetTransformValue resets the TransformValue parameter previously set by SetTransformData. (see SetTransformData)
	 */
	virtual void SetTransformValue( const Transform::TransformValue& xform) = 0;

};


#endif
