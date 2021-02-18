//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IAdornmentFlattenerUsage.h $
//  
//  Owner: Matt Phillips
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
#ifndef __IAdornmnentFlattenerUsage__
#define __IAdornmnentFlattenerUsage__

#include "IPMUnknown.h"

class IAdornmentFlattenerUsage : public IPMUnknown
{
public:
	// certain adornment usage's need to do a IterateDrawOrder internally.  The new default params
	// allow them to do so
	virtual bool32 IsFlattenerRequired_(IPMUnknown* iThing, const PMMatrix* masterSpread2LayoutSpreadMatrix, int32 nFlags) = 0;
	bool32 IsFlattenerRequired(IPMUnknown* iThing)
	{
		return IsFlattenerRequired_( iThing, nil, 0);
	}
};

#endif
