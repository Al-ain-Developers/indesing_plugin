//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IBoundsData.h $
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
//  Purpose: 	This interface is attached to commands which alter the dimensions of page items. It
//  is used to determine the size of the area (usually the pasteboard) which contains the
//  affected page items, and whether the items should be completely contained within the
//  area, or simply intersect it.
//  
//  IBoundsData
//  
//========================================================================================

#pragma once
#ifndef __IBOUNDSDATA__
#define __IBOUNDSDATA__

#include "IPMUnknown.h"

#include "LayoutUIID.h"
#include "LayoutID.h"
#include "PMRect.h"
#include "TransformTypes.h"

class ITransform;

class IBoundsData : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_IBOUNDSDATA };

	enum ContainmentType
	{
		kNoBoundsChecking = 0,
		kNoItemsCompletelyOutside = 1,
		kAllItemsCompletelyInside = 2,
		kUseDefaultBoundsChecking = 3,
	};


	/** SetBoundsChecking specifies how and within what rectangle a page item is to 
	    be constrained during resize and transform commands.
		@param containmentType - one of kNoBoundsChecking, kNoItemsCompletelyOutside, kAllItemsCompletelyInside, kUseDefaultBoundsChecking
		@param bounds - the rectangle within which the items are constrained
		@param coordinateSpace - the coordinate space of bounds - usually Transform::SpreadCoordinates()
		Note for kNoItemsCompletelyOutside or kAllItemsCompletelyInside, bounds must be non-nil, for
		kNoBoundsChecking or kUseDefaultBoundsChecking bounds is stored, but ignored.
	*/
	virtual void SetBoundsChecking( ContainmentType containmentType, const PMRect* bounds, const Transform::CoordinateSpace &coordinateSpace) = 0;

	/** SetDefaultBoundsChecking specifies that the default bounds checking should be used for
	    each item.  Typically this means that inlines are constrained within their text frames
		and other page items are constrained within the pasteboard.
	*/
	inline void SetDefaultBoundsChecking(){ SetBoundsChecking( kUseDefaultBoundsChecking, nil, Transform::SpreadCoordinates());}

	/** SetNoBoundsChecking turns off all bounds checking during execution of the command.
	*/
	inline void SetNoBoundsChecking(){ SetBoundsChecking( kNoBoundsChecking, nil, Transform::SpreadCoordinates());}

	/** GetBoundsChecking returns the values passed to SetBoundsChecking.
		@param bounds - the rectangle passed to SetBoundsChecking
		@param coordinateSpace - the coordinate space passed to SetBoundsChecking
		@return returns the ContainmentType passed to SetBoundsChecking
	*/
	virtual ContainmentType GetBoundsChecking( PMRect* bounds, Transform::CoordinateSpace* coordinateSpace) const = 0;

	/** CalculateBoundsChecking returns the bounds checking used for a particular page item.  Note that
	    kUseDefaultBoundsChecking is resolved to a rectangle and one of kNoItemsCompletelyOutside
		or kAllItemsCompletelyInside. The parameter rectParent returns the ancestor of item in
		which coordinate system rect is defined.
	*/
	virtual ContainmentType CalculateBoundsChecking( const UIDRef& item, PMRect* rect, UIDRef* rectParent) = 0;

};

#endif // __IBOUNDSDATA__
