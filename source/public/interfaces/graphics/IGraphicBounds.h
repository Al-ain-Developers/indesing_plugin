//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGraphicBounds.h $
//  
//  Owner: Dave Stephens
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
//  Purpose of Interface:
//  This interface is used to set the intrinsic bounds of an imported
//  image, EPS, PDF, or similar graphic.  The bounds are then used by
//  IGeometry whenever it needs to obtain the intrinsic bounds of the graphic.
//  
//========================================================================================

#pragma once
#ifndef __IGraphicBounds__
#define __IGraphicBounds__

#include "IPMUnknown.h"
#include "PMRect.h"
#include "GraphicsID.h"

/**
	This interface is used to set the intrinsic bounds of an imported
	image, EPS, PDF, or similar graphic. The bounds are then used by
	IGeometry whenever it needs to obtain the intrinsic bounds of the graphic. 
	Sometime we want to use the graphic bounds since it guarantees to be 
	the entire image while geometry bounds may only report the visible portion 
	of the image.
*/
class IGraphicBounds : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IGRAPHICBOUNDS };

	/**
		Set the intrinsic bounds.

		@param bounds [IN] parameter the new bounds to use.
		@return void.
	*/
	virtual void Set(const PMRect &bounds) = 0;

	/**
		Get the intrinsic bounds.

		@return PMRect the intrinsic bound of the item. 
	*/
	virtual PMRect Get(void) const = 0;
};

#endif