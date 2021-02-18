//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ITransformPanelPrefsCmdData.h $
//  
//  Owner: Richard Rodseth
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
//  Purpose:	Preferences for the Transform Panel
//  
//========================================================================================

#pragma once
#ifndef __ITransformPanelPrefsCmdData__
#define __ITransformPanelPrefsCmdData__

#include "IPMUnknown.h"
#include "SpreadID.h"
#include "TransformTypes.h"

class ITransformPanelPrefsCmdData : public IPMUnknown
{
public:
	virtual void SetCoordinateSpace(const Transform::CoordinateSpace& newCoordinateSpace) = 0;		
	virtual void SetShowStrokeBounds( Geometry::BoundsKind	showStrokeBounds) = 0;		
	virtual void SetShowContentOffset(bool16 showContentOffset) = 0;		
	virtual void SetScaleStrokes(bool16 scaleStrokes) = 0;		
	virtual void SetScaleUsingLens(bool16) = 0;		
	virtual void SetScaleXPEffects(bool16 scaleXPEffects) = 0;

	virtual Transform::CoordinateSpace GetCoordinateSpace() const = 0;
	virtual Geometry::BoundsKind GetShowStrokeBounds() const = 0;
	virtual bool16 GetShowContentOffset() const = 0;
	virtual bool16 GetScaleStrokes() const = 0;
	virtual bool16 GetScaleUsingLens() const = 0;
	virtual bool16 GetScaleXPEffects() const = 0;

	virtual bool16 GetChangeCoordinateSpace() const = 0;
	virtual bool16 GetChangeShowStrokeBounds() const = 0;
	virtual bool16 GetChangeShowContentOffset() const = 0;
	virtual bool16 GetChangeScaleStrokes() const = 0;
	virtual bool16 GetChangeScaleUsingLens() const = 0;
	virtual bool16 GetChangeScaleXPEffects() const = 0;
};


#endif // __ITransformPanelPrefsCmdData__
