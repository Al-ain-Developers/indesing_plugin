//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/pageitems/basicinterfaces/CGeometry.cpp $
//  
//  Owner: Jack Kirstein
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



#include "CGeometry.h"
#include "InterfacePtr.h"
#include "IPMStream.h"
#include "ITransform.h"
#include "PMPolygon4.h"
#include "TransformUtils.h"
#include "IPageItemCache.h"
#include "IPageItemUtils.h"

DEFINE_HELPER_METHODS(CGeometry)

CGeometry::CGeometry(IPMUnknown *boss)
	: HELPER_METHODS_INIT(boss)
{
}
CGeometry::~CGeometry()
{}


PMReal CGeometry::GetStrokeProportion() const
{
	PMRect boundingBox = ((IGeometry*) this)->GetStrokeBoundingBox();
	return boundingBox.Width() / boundingBox.Height();
}

PMReal CGeometry::GetPathProportion() const
{
	PMRect boundingBox = ((IGeometry*) this)->GetPathBoundingBox();
	return boundingBox.Width() / boundingBox.Height();
}

PMRect CGeometry::GetStrokeBoundingBox() const
{
	return ((IGeometry*) this)->GetPathBoundingBox ();
}

PMRect CGeometry::GetStrokeBoundingBox(const PMMatrix& theMatrix) const
{
	return ((IGeometry*) this)->GetPathBoundingBox (theMatrix);
}

ErrorCode CGeometry::SetStrokeBoundingBox(const PMRect& newBBox)
{
	return ((IGeometry*) this)->SetPathBoundingBox(newBBox);
}

ErrorCode CGeometry::SetStrokeBoundingBox(const PMMatrix& theMatrix, const PMRect& newBBox)
{
	return ((IGeometry*) this)->SetPathBoundingBox(theMatrix, newBBox);
}

