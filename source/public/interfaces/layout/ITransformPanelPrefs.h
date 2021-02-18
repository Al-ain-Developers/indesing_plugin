//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ITransformPanelPrefs.h $
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
#ifndef __ITransformPanelPrefs__
#define __ITransformPanelPrefs__

#include "IPMUnknown.h"
#include "PMPoint.h"
#include "SpreadID.h"
#include "TransformTypes.h"

class ITransformPanelPrefs : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_ITRANSFORMPANELPREFERENCES };

	// Are transformation values local or aggregate values?
	virtual void SetCoordinateSpace(const Transform::CoordinateSpace& coordinateSpace) = 0;
	virtual Transform::CoordinateSpace GetCoordinateSpace() = 0;

	// Is stroke included in dimensions?
	virtual void SetShowStrokeBounds( Geometry::BoundsKind bShowStrokeBounds) = 0;
	virtual Geometry::BoundsKind GetShowStrokeBounds() = 0;

	// Is content displayed with global coordinates or offset coordindates when subselected?
	virtual void SetShowContentOffset(bool16 bShowContentOffset) = 0;
	virtual bool16 GetShowContentOffset() = 0;

	// Are strokes on objects scaled when objects are scaled?
	virtual void SetScaleStrokes(bool16 bScaleStrokes) = 0;
	virtual bool16 GetScaleStrokes() = 0;

	// Are scaling commands implemented via a transform matrix (like a lens)
	// or does the scaling simply pass through to a page item's content?
	virtual void SetScaleUsingLens( bool16 ) = 0;
	virtual bool16 GetScaleUsingLens() = 0;

	// Are transparency effects on objects scaled when objects are scaled?
	virtual void SetScaleXPEffects(bool16 bScaleXPEffects) = 0;
	virtual bool16 GetScaleXPEffects() = 0;
};

#endif
