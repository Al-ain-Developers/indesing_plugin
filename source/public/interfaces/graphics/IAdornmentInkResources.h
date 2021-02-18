//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IAdornmentInkResources.h $
//  
//  Owner: blecheva
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
//  Purpose:
//  This is the interface used to add adornments to page items.  For an example see...
//  
//========================================================================================

#pragma once
#ifndef __IAdornmentInkResources__
#define __IAdornmentInkResources__

#include "IPMUnknown.h"
#include "IInkResourceData.h"
#include "IShape.h"

class IAdornmentInkResources : public IPMUnknown
{

public:
	virtual void GetUsedInks (
				IPMUnknown* 		iOwningPI,			// owning page item
				IInkResourceData*	inkResourceData
				) = 0;
	
};

#endif
