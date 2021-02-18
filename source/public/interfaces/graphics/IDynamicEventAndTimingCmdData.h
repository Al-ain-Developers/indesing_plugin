//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IDynamicEventAndTimingCmdData.h $
//  
//  Owner: SusanCL
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
#ifndef __IDynamicEventAndTimingCmdData__
#define __IDynamicEventAndTimingCmdData__

#include "IPMUnknown.h"
#include "DynamicDocumentsID.h"
#include "IDynamicEventTimingMgr.h"
#include "IAnimationData.h"


class IDynamicEventAndTimingCmdData : public IPMUnknown
{
public:

	enum {kDefaultIID = IID_IEVENTTRIGGERANDTIMINGCMDDATA};

	/**	Set the owner UIDRef that we are affecting.
		If we are affecting the page events (page load and page click) then this
		ownerRef is a spread UIDRef. If these are button events, then the ownerRef
		is the button UIDRef.
		@param ownerRef is the UIDRef of the spread
	*/
	virtual void SetOwnerUIDRef (const UIDRef& ownerRef) = 0;
	
	/**	Get the spread UIDRef that we are affecting.
		@return UIDRef of the spread.
	*/
	virtual UIDRef GetOwnerUIDRef () const = 0;

	/**	Set the affecting event trigger.
		@param trigger is the affected event trigger.
		@see AnimationTypes.h
	*/
	virtual void SetEventTrigger (const EventTriggerType& trigger) = 0;
	
	/**	Get the event trigger
		@return an event trigger.
		@see AnimationTypes.h
	*/
	virtual EventTriggerType GetEventTrigger () const = 0;

	/** Set the target item list.
		NOTE: either the target position or the target list must be specified.
		@param targetList is the list of targets.
	*/
	virtual void SetTargetItemList (const IDynamicEventTimingMgr::DynamicTargetList& targetList) = 0;
	
	/** @return the new target item.
	*/
	virtual const IDynamicEventTimingMgr::DynamicTargetList& GetTargetItemList () const = 0;

	/**	Set the timing group position we want to update. If groupPosition is -1, then all instances of the
		item are affected.
		@param groupPosition is the position of the timing item we want to update.
	*/
	virtual void SetTimingPosition (int32 groupPosition) = 0;
	
	/**	@return the position of the timing group item.
	*/
	virtual int32 GetTimingPosition () const = 0;

	/**	Set the timing target item we want to update. If itemPosition is -1, then all instances of the
		item are affected.
		NOTE: either the target position or the target list must be specified.
		@param targetPosition is the position of the timing item we want to update.
	*/
	virtual void SetTargetPosition (int32 targetPosition) = 0;
	
	/**	@return the position of the timing target item.
	*/
	virtual int32 GetTargetPosition () const = 0;

	/**	This enum specifies how to move the item(s) in the timing list for the specified trigger.
	*/
	enum MoveType {
		/** Specifies no move. */
		kMoveNone,

		/** Specifies the item(s) are moved before the specified posiiton. */
		kMoveBefore, 

		/** Specifies the item(s) are moved to the specified posiiton. */
		kMoveTo, 

		/** Specifies the item(s) are moved after the specified posiiton. */
		kMoveAfter
	};

	/**	Sets the move for this command.
		@param moveType specifes how to move.
		@param newPosition is the position to move before, to, or after.
		@param newPositionInGroup is the new position within group. This is relevant only if move is set to kMoveTo.
		The default is -1 which means to move to the end of the specified group.
	*/
	virtual void SetMove (const MoveType& moveType, uint32 newPosition, int32 newPositionInGroup = -1) = 0;

	/**	@return the move type.
	*/
	virtual MoveType GetMoveType () const = 0;;

	/**	@return the move position.
		If set to -1, the new position is at the end.
	*/
	virtual int32 GetNewTimingPosition () const = 0;

	/**	@return the move position within group
		If set to -1, the new position is at the end.
	*/
	virtual int32 GetNewTimingPositionInGroup () const = 0;

	/** Set the new target item.
	*/
	virtual void SetNewTargetItem (const IDynamicEventTimingMgr::DynamicTargetPtr& newTarget) = 0;
	
	/** @return the new target item.
	*/
	virtual const IDynamicEventTimingMgr::DynamicTargetPtr& GetNewTargetItem () const = 0;

	/** Set the new target item UID.
	*/
	virtual void SetNewTargetItemUID (UID newItemUID) = 0;
	
	/** @return the new target item UID.
	*/
	virtual UID GetNewTargetItemUID () const = 0;

	/**	Set the new time delay for the specified item
		@param delay is the new time delay.
	*/
	virtual void SetTimeDelay (const PMReal& delay) = 0;
	
	/**	Get new time delay
		@return the new time delay.
	*/
	virtual PMReal GetTimeDelay () const = 0;

	/**	@return true if to set new time delay.
	*/
	virtual bool GetTimeDelayIsSet () const = 0;

	/**	For targets triggered by buttons
	*/

	/**	This enum specifies what to do when removing target from a button trigger event.
	*/
	enum RemoveTargetOptions {
		/** Specifies no remove action should be applied to the button action. */
		kNoAction, 
		/** Specifies action to be disabled but leave target in action. 
			This is the default option. */
		kDisableAction, 

		/** Specifies remove action from trigger event and reliquished button action from behavior list. */
		kRemoveAction,

		/** Specifies target to be cleared but leave action in the behavior list. */
		kClearTarget
	};

	/**	Set the new time delay for the specified item
		@param delay is the new time delay.
	*/
	virtual void SetButtonTargetRemoveOption (const RemoveTargetOptions& removeOption) = 0;
	
	/**	Get new time delay
		@return the new time delay.
	*/
	virtual RemoveTargetOptions GetButtonTargetRemoveOption () const = 0;


	/**	The following methods for setting group's play data.
		This includes number of times to play and the looping flag.
	*/
	/**	Set the specified linked group's play data.
		@param setNumPlay is true if numPlays is set.
		@param numPlays is the new number of times to play.
		@param setLooping is true if playsLoop is set.
		@param playsLoop is true if group is set to loop.
	*/
	virtual void SetGroupPlayData (bool setNumPlay, const uint32& numPlays, bool setLooping, bool playsLoop) = 0;
	
	/**	Get the new number of times the specified group should play.
		@param numPlays is the new number of time to play.
		@return true if new number of times to play is set.
	*/
	virtual bool GetNumPlays (uint32& numPlays) const = 0;

	/**	Get the looping flag for the specified group.
		@param playsLoop is true if group should loop.
		@return true if loop flag is set.
	*/
	virtual bool GetPlaysLoop (bool& playsLoop) const = 0;
};

#endif	// __IDynamicEventAndTimingCmdData__
