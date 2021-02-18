//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/pageitems/basicinterfaces/CPathShape.cpp $
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
#include "CPathShape.h"

#include "TransformUtils.h"
#include "TransformUtilsPrivate.h"

#include "IGraphicsPort.h"
#include "IPageItemCache.h"
#include "IPathPageItem.h"
#include "IViewPort.h"


#ifdef DEBUG
// Defined in DebugCacheGlobal.cpp
extern bool16 ts_DebugCachesOn;
#endif

// BP 05/03/01: moved to  .../source/components/public/PublicImpl.cpp
// CREATE_PMINTERFACE(CPathShape, kCPathShapeImpl)

CPathShape::CPathShape(IPMUnknown *boss) :
	CShape(boss)
{
	fPathPageItem = (IPathPageItem*) QueryInterface (IID_IPATHPAGEITEM);
	if ( fPathPageItem )
		fPathPageItem->Release();
}

CPathShape::~CPathShape()
{
}


PMRect CPathShape::GetPaintedBBox(const PMMatrix& theMatrix, const Transform::CoordinateSpace& coordinateSpace)
{
	PMMatrix innertoview = ::InnerToOuterMatrix( coordinateSpace, this);
	
	innertoview.PostConcat (theMatrix);
	
	if ( !IsCacheValid() )
	{
		fPaintedBounds = fPathPageItem->GetPaintedBoundingBox( PMMatrix() ) ;
						
		if ( fPageItemCache )
			fPageItemCache->SetShapeCacheValid (kTrue);
	}
#ifdef DEBUG
	else if ( ts_DebugCachesOn )
	{				
		PMRect theBounds = fPathPageItem->GetPaintedBoundingBox( PMMatrix() ) ;
						
		ASSERT_MSG (fPaintedBounds == theBounds, "Cached painted bounds bad");
	}
#endif
	
	// Convert to the matrix coords
	PMRect retBounds (fPaintedBounds);
	
	innertoview.Transform (&retBounds);

	// Outset for any possible rounding
	if ( retBounds != kZeroRect ) //could be a single-point spline
		retBounds.Inset (-1, -1);

	UnionPageItemAdornmentPaintedBBox(retBounds, innertoview);

	return retBounds;
}

/*-------------------------------------------------------------------------------------------------*/
/* Protected methods 																			   */
/*-------------------------------------------------------------------------------------------------*/
void CPathShape::DrawShape(GraphicsData* gd, int32 flags)
{
	IGraphicsPort* gPort = gd->GetGraphicsPort();
	
	fPathPageItem->CopyPath( gPort ) ;

	DrawPageItemAdornments(gd, flags, IAdornmentShape::kBeforeStroke);

	fPathPageItem->Stroke( gPort ) ;
	
	DrawPageItemAdornments(gd, flags, IAdornmentShape::kAfterStroke);
}


