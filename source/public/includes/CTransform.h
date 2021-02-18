//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CTransform.h $
//  
//  Owner:
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

#pragma once
#ifndef __TRANSFORM__
#define __TRANSFORM__

#include "ITransform.h"
#include "PMMatrix.h"
#include "CPMUnknown.h"
#include "PMPoint.h"


#pragma export on

class PUBLIC_DECL CTransform : public CPMUnknown<ITransform>
{
public:

	CTransform(IPMUnknown * boss = nil);
	virtual ~CTransform();

	virtual PMReal GetItemScaleX() const;
	virtual PMReal GetItemScaleY() const;
	virtual PMReal GetItemSkewAngle() const;
	virtual PMReal GetItemRotationAngle() const;

	virtual void ScaleItemBy( PMReal xScale, PMReal yScale, const PMPoint& center);
	virtual void ScaleItemTo( PMReal xScale, PMReal yScale, const PMPoint& center);
	virtual void SkewItemBy( PMReal xSkew, const PMPoint& center);
	virtual void SkewItemTo( PMReal xSkew, const PMPoint& center);
	virtual void RotateItemBy( PMReal angle, const PBPMPoint& center);
	virtual void RotateItemTo( PMReal angle, const PBPMPoint& center);
	virtual void TranslateItemBy( const PBPMPoint& delta);
	virtual void TranslateItemTo( const PBPMPoint& location);

	virtual void SetInnerToParentMatrix(const PMMatrix& matrix);
	virtual const PMMatrix& GetInnerToParentMatrix() const;
	virtual const PMMatrix& GetParentToInnerMatrix() const;
	virtual ITransform::MatrixType GetInnerToRootMatrix( PMMatrix *pMatrix, const ITransform *pRoot = nil ) const;

	virtual bool16 IsTransformParentDependent() const;

	virtual IPMUnknown* QueryTransformParent();
	virtual void ConcatItemTransform(IGraphicsPort *gPort);

	protected:
		bool16 MoveAndPositiveScaleOnly(void) const;

		// this data is read/written by subclass persisttransform
		PMMatrix fCTM;

		void UpdateInverseCTM() const;

		PMMatrix fInverseCTM;
		bool16 fInverseIsCurrent;
};

#pragma export off

#endif
