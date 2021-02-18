//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IMultiStateObjectBehaviorData.h $
//  
//  Owner: Greg St. Pierre
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

#include "IBehaviorData.h"
#include "BehaviorID.h"
#include "FormFieldTypes.h"

/** 
 Data interface for Switch Multi-state Object (MSO) Behavior.
 
 @see INamedPageItemList (for a way of getting candidates for SetTarget())
 */
class IMultiStateObjectBehaviorData : public IBehaviorData
{
public:
	enum Position
	{
		kExplicitPosition,
		
		kNextPosition,
		kPreviousPosition
	};
	
	/**
	 Get Position for this MSO state behavior
	 
	 Note: This is an intrinsic property of the behavior and cannot be changed.
	 
	 @return One of Position enum
	 */
	virtual Position GetPosition() const = 0;
	
	/**
	 Set UID of MSO page item to target
	 
	 @param target	UID of MSO page item to target
	 */
	virtual void SetTarget(UID const &target) = 0;

	/**
	 Get UID of MSO page item to target
	 
	 @return UID of MSO page item to target
	 */
	virtual UID GetTarget() const = 0;
	
	/**
	 Set the MSO state to switch to
	 
	 @param state	The MSO state to switch to
	 */
	virtual void SetState(Form::AppearanceState state) = 0;
	
	/**
	 Get the MSO state to switch to
	 
	 @return The MSO state to switch to
	 */
	virtual Form::AppearanceState GetState() const = 0;
	
	/**
	 Set whether target MSO should switch back to its prior state on roll off
	 
	 Note: This only has meaning if this behavior is assigned to the roll over state
	 
	 @param revertOnRollOff	Boolean. If true, target should switch back to its prior state on roll off
	 */
	virtual void SetSwitchToPriorStateOnRollOff(bool revertOnRollOff) = 0;
	
	/**
	 Get whether target MSO should switch back to its prior state on roll off
	 
	 Note: This only has meaning if this behavior is assigned to the roll over state

	 @return true if target should switch back to its prior state on roll off
	 */
	virtual bool GetSwitchToPriorStateOnRollOff() const = 0;
	
	/**
	 Set whether target MSO should loop to the beginning or end when position is
	 either next or previous respectively

	 Note: This has no meaning if position is explicit

	 @param loopsAtBeginningOrEnd	Boolean. If true, target should loop on next or previous
	 */
	virtual void SetLoopAtBeginningOrEnd(bool loopsAtBeginningOrEnd) = 0;
	
	/**
	 Get whether target MSO should loop to the beginning or end when position is
	 either next or previous respectively
	 
	 Note: This has no meaning if position is explicit

	 @return true if target should loop on next or previous
	 */
	virtual bool GetLoopAtBeginningOrEnd() const = 0;
};
