//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/pageitems/basicinterfaces/CTransform.cpp $
//  
//  Owner: jack_kirstein
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

#include "VCPublicHeaders.h"

#include "CTransform.h"

#include "IHierarchy.h"
#include "IGraphicsPort.h"

const PMReal kTranslationTooLarge = 1e+20;	// Value to large for "normal" translations in our model. See bug #2539167, trying to capture when this case has been triggered.

//========================================================================================
// CLASS CTransform
//========================================================================================

//----------------------------------------------------------------------------------------
// CTransform constructor
//----------------------------------------------------------------------------------------

CTransform::CTransform(IPMUnknown * boss) :
	CPMUnknown<ITransform>(boss),
	fCTM(),
	fInverseCTM(),
	fInverseIsCurrent(kFalse)
{}

//----------------------------------------------------------------------------------------
// CTransform destructor
//----------------------------------------------------------------------------------------

CTransform::~CTransform()
{}

bool16 CTransform::IsTransformParentDependent() const
{
	return kFalse;
}

//----------------------------------------------------------------------------------------
// CTransform::MoveRelative
//----------------------------------------------------------------------------------------


void CTransform::TranslateItemBy(const PBPMPoint& delta)
{
	PMMatrix ctm = GetInnerToParentMatrix();
	ctm.Translate (delta.X(), delta.Y());
	SetInnerToParentMatrix (ctm);
}

//----------------------------------------------------------------------------------------
// CTransform::MoveTo
//----------------------------------------------------------------------------------------

void CTransform::TranslateItemTo(const PBPMPoint& location)
{
	PMMatrix ctm = GetInnerToParentMatrix();
	ctm.SetOrigin(location.X(), location.Y());
	SetInnerToParentMatrix (ctm);
}

//----------------------------------------------------------------------------------------
// CTransform::Rotate
//----------------------------------------------------------------------------------------

void CTransform::RotateItemBy(PMReal angle, const PBPMPoint& center)
{
	PMMatrix ctm = GetInnerToParentMatrix();
	ctm.RotateAbout (center, angle);
	SetInnerToParentMatrix (ctm);
}

//----------------------------------------------------------------------------------------
// CTransform::Scale
//----------------------------------------------------------------------------------------

void CTransform::ScaleItemBy(PMReal xScale, PMReal yScale, const PMPoint& center)
{
	PMMatrix ctm = GetInnerToParentMatrix();
	ctm.ScaleFrom( center, xScale, yScale);
	SetInnerToParentMatrix (ctm);
}

//----------------------------------------------------------------------------------------
// CTransform::Skew
//----------------------------------------------------------------------------------------

void CTransform::SkewItemBy(PMReal xSkewAngle, const PMPoint& center)
{
	PMMatrix ctm = GetInnerToParentMatrix();
	ctm.SkewFrom (center, xSkewAngle, 0.0);
	SetInnerToParentMatrix (ctm);
}

//----------------------------------------------------------------------------------------
// CTransform::Rotate
//----------------------------------------------------------------------------------------

void CTransform::RotateItemTo(PMReal angle, const PBPMPoint& center)
{
	PMMatrix ctm = GetInnerToParentMatrix();
	ctm.Translate (-center.X(), -center.Y());
	ctm.RotateTo (angle);
	ctm.Translate (center.X(), center.Y());
	SetInnerToParentMatrix (ctm);

	fInverseIsCurrent = kFalse;
}

//----------------------------------------------------------------------------------------
// CTransform::Scale
//----------------------------------------------------------------------------------------

void CTransform::ScaleItemTo(PMReal xScale, PMReal yScale, const PMPoint& center)
{
	PMMatrix ctm = GetInnerToParentMatrix();
	ctm.Translate (-center.X(), -center.Y());
	ctm.ScaleTo (xScale, yScale);
	ctm.Translate (center.X(), center.Y());
	SetInnerToParentMatrix (ctm);

	fInverseIsCurrent = kFalse;
}

//----------------------------------------------------------------------------------------
// CTransform::Skew
//----------------------------------------------------------------------------------------

void CTransform::SkewItemTo(PMReal xSkewAngle, const PMPoint& center)
{
	PMMatrix ctm = GetInnerToParentMatrix();
	ctm.Translate (-center.X(), -center.Y());
	ctm.SkewTo( xSkewAngle);
	ctm.Translate (center.X(), center.Y());
	SetInnerToParentMatrix (ctm);

	fInverseIsCurrent = kFalse;
}




//----------------------------------------------------------------------------------------
// CTransform::CurrentMatrix
//----------------------------------------------------------------------------------------

const PMMatrix& CTransform::GetInnerToParentMatrix() const
{
	return fCTM;
}

//----------------------------------------------------------------------------------------
// CTransform::CurrentInverseMatrix
//----------------------------------------------------------------------------------------

const PMMatrix& CTransform::GetParentToInnerMatrix() const
{
	this->UpdateInverseCTM();
	return fInverseCTM;
}

//----------------------------------------------------------------------------------------
// CTransform::MoveAndPositiveScaleOnly
//----------------------------------------------------------------------------------------

bool16 CTransform::MoveAndPositiveScaleOnly(void) const
{
	const PMMatrix& curMatrix = GetInnerToParentMatrix();
	return ((curMatrix[0] > 0) && (curMatrix[1] == 0) && (curMatrix[2] == 0) && (curMatrix[3] > 0));
}

//----------------------------------------------------------------------------------------
// CTransform::SetMatrix
//----------------------------------------------------------------------------------------

void CTransform::SetInnerToParentMatrix(const PMMatrix& matrix)
{
	if ( !matrix.IsSingular() )
	{
		fCTM = matrix;

		ASSERT_MSG(std::fabs(::ToDouble(matrix.GetXTranslation())) < kTranslationTooLarge && std::fabs(::ToDouble(matrix.GetYTranslation())) < kTranslationTooLarge, "Setting InnerToParentMatrix with huge translation values, is this what you want? (See bug #2539167, please note what you did to get trigger this assert.)");

		fInverseIsCurrent = kFalse;
	}
}


//----------------------------------------------------------------------------------------
// CTransform::UpdateInverseCTM
//----------------------------------------------------------------------------------------

void CTransform::UpdateInverseCTM() const
{
	if (!fInverseIsCurrent)
	{
		// fake out const since this doesn't logically change this
		CTransform *fakeThis = (CTransform*)this;
		fakeThis->fInverseCTM = fakeThis->GetInnerToParentMatrix();
		fakeThis->fInverseCTM.Invert();
		fakeThis->fInverseIsCurrent = kTrue;
	}
}



//----------------------------------------------------------------------------------------
// CTransform::GetRotationAngle
//----------------------------------------------------------------------------------------

PMReal CTransform::GetItemRotationAngle() const
{

	return GetInnerToParentMatrix().GetRotationAngle();
}

//----------------------------------------------------------------------------------------
// CTransform::GetXSkewAngle
//----------------------------------------------------------------------------------------

PMReal CTransform::GetItemSkewAngle() const
{
	return GetInnerToParentMatrix().GetXSkewAngle();
}

//----------------------------------------------------------------------------------------
// CTransform::GetXScale
//----------------------------------------------------------------------------------------

PMReal CTransform::GetItemScaleX() const
{
	return GetInnerToParentMatrix().GetXScale();
}

//----------------------------------------------------------------------------------------
// CTransform::GetYScale
//----------------------------------------------------------------------------------------

PMReal CTransform::GetItemScaleY() const
{
	return GetInnerToParentMatrix().GetYScale();
}

//----------------------------------------------------------------------------------------
// CTransform::GetInnerToRootMatrix
//----------------------------------------------------------------------------------------

ITransform::MatrixType CTransform::GetInnerToRootMatrix( PMMatrix *, const ITransform * ) const
{
	return ITransform::kStaticMatrix;
}

//----------------------------------------------------------------------------------------
// CTransform::QueryTransformParent
//----------------------------------------------------------------------------------------

IPMUnknown* CTransform::QueryTransformParent()
{
	// Normal case -- use the hierarchy to determine where the parent's transform is
	InterfacePtr<IHierarchy> ourSelf(this, UseDefaultIID());
	if( ourSelf )
	{
		InterfacePtr<IHierarchy> ourParent(ourSelf->QueryParent());
		if( ourParent )
			return ourParent.forget();
	}
	return nil;
}

//----------------------------------------------------------------------------------------
// CTransform::ConcatTransform
//----------------------------------------------------------------------------------------
void CTransform::ConcatItemTransform(IGraphicsPort *gPort)
{
	if (gPort)
		gPort->concat(GetInnerToParentMatrix());
}

