//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IReferencePointData.h $
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
//========================================================================================

#pragma once
#ifndef __IReferencePointData__
#define __IReferencePointData__

#include "LayoutUIID.h"
#include "PMTypes.h"
#include "PMReal.h"
#include "PMPoint.h"
#include "PMRect.h"
#include "PMPolygon4.h"

/**
	Data interface for holding information about the reference point. Each layout view
	has its own a reference point. In general, you should control the reference point via
	IRefPointUIUtils, or even at a suite level in IReferencePointSuite, instead of calling these
	interfaces directly.
	@ingroup layout_suite
	@see IRefPointUIUtils.h
	@see IReferencePointSuite.h
*/
class IReferencePointData : public IPMUnknown
{
public:
	friend class RefPointUIUtilsImpl;

	/** Enum for describing the reference point position. */
	enum ReferencePointPosition
	{
		/** Top left position */
		kTopLeftReferencePoint = 0,
		/** Synonym for kTopLeft. Useful for loops over all the positions. */
		kFirstReferencePointPosition = kTopLeftReferencePoint,
		/** Top center position */
		kTopCenterReferencePoint = 1,
		/** Top right position */
		kTopRightReferencePoint = 2,
		/** Left center position */
		kLeftCenterReferencePoint = 3,
		/** Center position */
		kCenterReferencePoint = 4,
		/** Right center position */
		kRightCenterReferencePoint = 5,
		/** Bottom left position */
		kBottomLeftReferencePoint = 6,
		/** Bottom center position */
		kBottomCenterReferencePoint = 7,
		/** Bottom right position */
		kBottomRightReferencePoint = 8,
		/** Synonym for kBottomRight. Useful for loops over all the positions. */
		kLastReferencePointPosition = kBottomRightReferencePoint,
		/** Not one of the standard nine points, user has dragged to a custom location. */
		kOtherReferencePointPosition = 9,
		/** No current reference position. */
		kUninitializedReferencePointPosition = 10
	};
	
	/** What is the current appearance of the reference point proxy. */
	enum ReferenceAppearance
	{
		/** All nine points */
		kNinePoint = 0,
		/** A line appearance with three points. Could be horizontal, vertical, or diagonal. */
		kLine = 1,
		/** A horizontal line appearance with just a center point */
		kPoint = 2,
		/** A horizontal line appearance with just a center point */
		kHorizontalGuide = kPoint,	
		/** A vertical line appearance with just a center point */
		kVerticalGuide = 3,	
		/** Same as the nine point appearance */
		kCursor = 4,
		/** Use for a disabled look. Was previously (InDesign 2.0 era) used for no-pub state. */
		kDisabled = 5,
		/** Use for a row only appearance */
		kRow = 6,
		/** Use for a column only appearance*/
		kColumn = 7,
	};

public:
	enum { kDefaultIID =  IID_IREFERENCEPOINTDATA };

private:
	/**	Show or hide the reference point.
		@param shown [IN] kTrue to show, kFalse to hide.
		@see RefPointUIUtils::ShowReferencePoint  
	 */
	virtual void		SetShown__(bool16 shown) = 0;

	/**	Is the reference point shown?
		@see RefPointUIUtils::IsReferencePointShown  
	 */
	virtual bool16		IsShown__() = 0;

public:
	/**	Set the position in the data interface.
		@param position [IN] the reference position to set.
		@see ReferencePointPosition
	 */
	/**	Set the reference point in the data interface.
		@param point [IN] the new reference point in global pasteboard coordinates.
		@see ChangeReferencePoint
	 */
	virtual void SetReferencePointData( const ReferencePointPosition& position, const PBPMPoint& point) = 0;


	/**	Return the value of the reference point
		@return ReferencePointPosition 
	 */
	virtual ReferencePointPosition GetPosition__() = 0; //hmm

private:
	/**	Get the actual reference point
		@return PBPMPoint the reference point in global pasteboard space.
		@see GetReferencePoint
	 */
	virtual PBPMPoint	GetPoint__() = 0;

	/**	Lock or unlock the reference point. When locked, we won't change it during selection changes.
		Used during certain command sequences to prevent reference point from changing.
		@param locked [IN] the new lock state for the data interface, kTrue to lock, kFalse to unlock
		@see LockReferencePoint
	 */
	virtual void		SetRefPointLocked__(bool16 locked) = 0;

	/**	Is the reference point locked? When locked, we won't change it during selection changes.
		Used during certain command sequences to prevent reference point from changing.
		@return bool16 the lock state of the reference point, kTrue if locked, kFalse if unlocked.
		@see IsReferencePointLocked
	 */
	virtual bool16      IsRefPointLocked__() = 0;
	
	/**	Show or hide the reference point.
		@param visible [IN] the new visible state for the data interface
		@see SetReferencePointVisible
	 */
	virtual void		SetVisible__(bool16 visible) = 0;

	/**	Is the reference point visible?
		@return bool16 kTrue for visible, kFalse for hidden
		@see IsReferencePointShown
	 */
	virtual bool16      IsVisible__() = 0;

	/**	Obsolete, do not use. */
	virtual PBPMPoint	GetOffsetFromCenter__() = 0;

	/**	Obsolete, do not use. */
	virtual void    	SetOffsetFromCenter__(const PBPMPoint& newPoint) = 0;
		
	/**	Return the value of the reference frame.
		@return PBPMRect the reference frame of the parent rectangle, kZeroRect if not relevent
		@see GetReferenceFrame
	 */
	virtual PBPMRect	GetReferenceFrame__() = 0;

	/**	Set the value of the reference frame.
		@param referenceFrame [IN] the rect in global pasteboard coordinates for the reference frame.
		@see SetReferenceFrame
	 */
	virtual void    	SetReferenceFrame__(const PBPMRect& referenceFrame) = 0;
};

/**
	Helper data class for holding several reference point related values in one structure.
	Several transform suite commands require this class as a parameter.
	@ingroup layout_suite
	@see IRefPointUIUtils.h
	@see IReferencePointSuite.h
	@see ITransformSuite_New.h
*/
class ReferencePointLocation
{
public:
	PBPMPoint 										referencePoint;
	IReferencePointData::ReferencePointPosition 	referencePosition;
};

#endif

