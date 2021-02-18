//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IAdornmentVisibility.h $
//  
//  Owner: Heath Lynn
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
//  Sometimes you may want to leave an adornment on a shape.  However, you may
//  not want it to draw.  Add your own implementation of this interface to the
//  shapes boss (along with a unique Interface ID) and have your adornment query
//  for it to check if it should draw.
//  
//  You also may want to have an adornment draw in some circumstances, but not 
//  others.  For instance, we want to allow the user to set grids to draw all in
//  one view regardless of how they appear on screen.			
//  
//========================================================================================

#pragma once
#ifndef __IAdornmentVisibility__
#define __IAdornmentVisibility__

#include "GraphicsData.h"
#include "K2Vector.h"

#include "IPMUnknown.h"
#include "IGraphicsPort.h"

class IAdornmentVisibility : public IPMUnknown
{

public:

	virtual void SetVisible(bool16 isVisible) = 0;

	// Should the adornment be visible in the given gPort?
	// A nil gPort which is the default simply returns a 
	// the value as set.
	// emptyFrames array is expected to come in sorted order
	typedef K2Vector<int32> FrameList;
	virtual bool16 IsVisible(GraphicsData * gd = nil, int32 flags = 0, FrameList * emptyFrames = nil) = 0;

	// emptyFrames array is expected to come in sorted order
	virtual bool16 IsEmpty(K2Vector<int32> * emptyFrames = nil) = 0;
};

#endif
	