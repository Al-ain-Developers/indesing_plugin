//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IAnimationBehaviorData.h $
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

/** 
 Data interface for Play Animation Behavior.
 
 @see INamedPageItemList (for a way of getting candidates for SetTarget()
 */
class IAnimationBehaviorData : public IBehaviorData
{
public:
	enum Operation
	{
		kPlay = 0,
		kStop,
		kPause,
		kResume,
		
		kReverse,
		kStopAll
	};
	
	/**
	 Set Operation to perform on animation
	 
	 @param operation	One of Operation enum
	 */
	virtual void SetOperation(Operation operation) = 0;

	/**
	 Get Operation to perform on animation
	 
	 @return One of Operation enum
	 */
	virtual Operation GetOperation() const = 0;
	
	/**
	 Set UID of animated page item to target
	 
	 @param target	UID of animated page item to target
	 */
	virtual void SetTarget(UID const &target) = 0;

	/**
	 Get UID of animated page item to target
	 
	 @return UID of animated page item to target
	 */
	virtual UID GetTarget() const = 0;
	
	/**
	 Set whether target animation should reverse itself on roll off
	 
	 @param reverseOnRollOff	Boolean. If true, target should auto-reverse on roll off
	 */
	virtual void SetAutoReverseOnRollOff(bool reverseOnRollOff) = 0;
	
	/**
	 Get whether animation should reverse itself on roll off
	 
	 @return true if target should auto-reverse on roll off
	 */
	virtual bool GetAutoReverseOnRollOff() const = 0;
};
