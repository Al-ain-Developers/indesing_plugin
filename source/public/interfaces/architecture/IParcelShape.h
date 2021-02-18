//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IParcelShape.h $
//  
//  Owner: Jesse Jones (jejones)
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
//  Purpose: Interface used to draw parcels.
//  
//========================================================================================

#pragma once
#ifndef __IParcelShape__
#define __IParcelShape__

#include "IPMUnknown.h"
#include "DrawPassInfo.h"

class GraphicsData;
class PMMatrix;
class PMRect;
class ICallback;


class IParcelShape : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPARCELSHAPE };
	
	/**
	InkBounds are in Parcel coordinates. Implementations are expected to
	cache this information when first asked.
	*/
	virtual void 			GetInkBounds(PMRect *inkBounds) const = 0;

#ifdef ID_DEPRECATED
	//
	// Invalidate cached state for the Parcel Shape including the ink bounds.
	// ## Invalidations will be handled in the future through
	// ITextParcelListData::InvalidateParcelComposedState().
	//
	virtual void			Invalidate() = 0;
#endif

	//
	// areaToDraw is in Frame coordinates.
	//
	virtual void 			Draw(GraphicsData* gd, int32 iShapeFlags,
									const PMRect* areaToDraw) = 0;

	//
    // call callbackInfo->callback for each item in this shape's hierarchy
	//
    virtual void			IterateParcelShapeDrawOrder( const PMMatrix *xform,
									ICallback *callbackInfo,
									int32 iShapeFlags = 0) = 0;

	/**
	Returns kTrue if the Parcel has cached InkBounds.
	*/
	virtual bool16			GetHasCachedData() const = 0;

};

#endif // __IParcelShape__
