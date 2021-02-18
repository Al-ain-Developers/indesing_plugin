//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IGoToZoomBehaviorData.h $
//  
//  Owner: Michael Brubidge
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
#ifndef __IGoToZoomBehaviorData_h__
#define __IGoToZoomBehaviorData_h__

#include "IBehaviorData.h"

//========================================================================================
// CLASS IGoToZoomBehaviorData
//========================================================================================

/** Data interface for Go To Zoom Behavior */
class IGoToZoomBehaviorData : public IBehaviorData
{
public:
	typedef int32 Zoom;
	enum ZoomConstants { kInherit = 0, kActualSize, kFitInWindow, kFitWidth, kFitVisible };
	
	/** Set the zoom type ( kInherit , kActualSize, kFitInWindow, kFitWidth, or kFitVisible ) */
	virtual void		SetZoom(const Zoom& view) = 0;

	/** Get the zoom type ( kInherit , kActualSize, kFitInWindow, kFitWidth, or kFitVisible ) */
	virtual Zoom		GetZoom() const = 0;
};

#endif // __IGoToZoomBehaviorData_h__
