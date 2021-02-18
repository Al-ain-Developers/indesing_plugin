//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IDynamicEventTimingSuite.h $
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
#ifndef __IDynamicEventTimingSuite__
#define __IDynamicEventTimingSuite__

#include "ISelectionMessages.h"
#include "AnimationTypes.h"

#include "DynamicDocumentsID.h"
#include "IDynamicEventTimingMgr.h"

/**	This is the high level dynamic event timing suite for the current selection.
	Dynamic events are event triggers that cause one or more items to do something in
	some ordering. The supported event triggers are:

	For the spread:
		kOnPageLoad
		kOnPageClick

	For the MSO:
		kOnPageLoad (is the same as on state load)

	For normal page items with animation applied:
		kOnSelfClick
		kOnSelfRollover

	For buttons:
		kOnClick
		kOnRelease
		kOnRollover
		kOnRolloff
	
*/
class IDynamicEventTimingSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDYNAMICEVENTTIMINGSUITE};
	

public:

	//________________________________________________________________________________
	//________________________________________________________________________________

	/** Returns true if current selection contains multiple selections.
		This will not be available for multiple selections.
	*/
	virtual bool HasMultipleSelections () const = 0;

	/** Returns true if we can apply event and timing to the current selection.
		We can only show or apply if the current selection is a single selection and that it is a button.
		@return true if we can apply event and timing to current selection.
	*/
	virtual bool CanApply () const = 0;

	/** @return the class ID of the current timing parent.
		Possible types are spread boss, MSO, and button.
	*/
	virtual ClassID GetTimingParentClassID () const = 0;

	/**	Get applicable dynamic events for the selection.
		@param trigger is the trigger event.
		@param eventTriggerTypeList: [OUT] the list of other event triggers that is applicable for the selection that is different from trigger.
	*/
	virtual void GetApplicableDynamicEvents(const EventTriggerType& trigger, std::vector<EventTriggerType>& eventTriggerTypeList) const = 0;

	/**	Get applicable dynamic events for the target selection.
		@param trigger is the trigger event.
		@param itemRef is target.
		@param eventTriggerTypeList: [OUT] the list of other event triggers that is applicable for the target selection that is different from trigger.
	*/
	virtual void GetApplicableDynamicEventsForTarget (const EventTriggerType& trigger, const IDynamicEventTimingMgr::DynamicTargetPtr& dynamicTarget, std::vector<EventTriggerType>& eventTriggerTypeList) const = 0;

	/**	Get number of dynamic events for the selection.
		@return the number of event triggers
	*/
	virtual uint32 GetNumDynamicEvents () const = 0;

	/**	Get nth dynamic events for the selection.
		@param which is the nth dynamic event to get.
		@return the event trigger.
	*/
	virtual EventTriggerType GetNthDynamicEvent (uint32 which) const = 0;

	/**	Get number of items in the selection's dynamic event timing list.
		@param trigger is the trigger event the item is in.
		@return the number of items
	*/
	virtual uint32 GetNumGroupsInEvent (const EventTriggerType& trigger) const = 0;

	/**	Get the nth timing position's item list from the selection's dynamic event.
		@param trigger is the trigger event the item is in.
		@param which is the nth item in the dynamic event timing list to get.
		@param itemList is the list containing one or more items in nth position of the timing list.
		@return true if successful otherwise return false.
	*/
	virtual bool GetNthGroupInEvent (const EventTriggerType& trigger, uint32 which, IDynamicEventTimingMgr::DynamicTargetList& itemList) const = 0;

	/** Gets the specified event trigger's nth item's number of plays.
		@param trigger is the event trigger to remove.
		@param which is the group item.
		@param numPlays is the number of times this group plays.
		@return true if successful; other retruns false.
	*/
	virtual uint32 GetNthGroupNumPlaysInEvent (const EventTriggerType& trigger, uint32 which) const = 0;

	/** Gets the specified event trigger's nth item's number of plays.
		@param trigger is the event trigger to remove.
		@param which is the group item.
		@param newNumPlays is the new number of times this group should play.
		@return true if successful; other retruns false.
	*/
	virtual bool SetNthGroupNumPlaysInEvent (const EventTriggerType& trigger, uint32 which, uint32 newNumPlays) = 0;

	/** Gets whether or not the specified event trigger's nth item is looping.
		@param trigger is the event trigger to remove.
		@param which is the group item.
		@param playsLoop is true if group loops.
		@return true if successful; other retruns false.
	*/
	virtual bool GetNthGroupPlaysLoopInEvent (const EventTriggerType& trigger, uint32 which) const = 0;

	/** Sets whether or not the specified event trigger's nth item should loop.
		@param trigger is the event trigger to remove.
		@param which is the group item.
		@param playsLoop is true if group loops.
		@return true if successful; other retruns false.
	*/
	virtual bool SetNthGroupPlaysLoopInEvent (const EventTriggerType& trigger, uint32 which, bool playsLoop) = 0;

	/**	Unlink the nth group from the selection's dynamic event. This puts the targets in the group as individual items
		in the timing list. If the group only has one item, unlink has no effect.
		@param trigger is the trigger event the item is in.
		@param which is the nth item in the dynamic event timing list to get.
		@param itemList is the list containing one or more items in nth position of the timing list.
		@return true if successful otherwise return false.
	*/
	virtual bool UnlinkNthGroupInEvent (const EventTriggerType& trigger, uint32 which) = 0;
		
	/**	Move the nth group from the selection's dynamic event.
		@param trigger is the trigger event the item is in.
		@param which is the which group in the dynamic event timing list to move.
		@param newGroup is the new position to move the group to.
		If newGroup is set to -1, then the group is moved to the end.
		@return true if successful otherwise return false.
	*/
	virtual bool MoveNthGroupInEvent (const EventTriggerType& trigger, uint32 which, int32 newGroup = -1) = 0;

	/**	Move all the targets in nth group from the selection's dynamic event to another group at the specified position.
		@param trigger is the trigger event the item is in.
		@param which is the which group in the dynamic event timing list to move.
		@param newGroup is the new position to move the group to.
		@param atPosition is the new position in the group to move the items in the group to.
		If atPosition is set to -1, then the items in the group is moved to the end of the new group.
		@return true if successful otherwise return false.
	*/
	virtual bool MoveNthGroupToInEventAt (const EventTriggerType& trigger, uint32 which, uint32 newGroup, int32 atPosition = -1) = 0;

	/**	Add item to the current seleciton dynamic event. If there's no selection,
		spread's dynamic events are used.
		@param trigger is the event to add item to.
		@param dynamicTarget is the target item to add.
		@return true if successful otherwise return false.
	*/
	virtual bool AddTargetInEvent (const EventTriggerType& trigger, const IDynamicEventTimingMgr::DynamicTargetPtr& dynamicTarget) = 0;

	/**	Remove item from the selection's dynamic event.
		@param trigger is the trigger event to remove item from.
		@param dynamicTarget is the target item to add.
		@param whichGroup is the position of the group item from which to remove from.
		@return true if successful otherwise return false.
	*/
	virtual bool RemoveTargetInEvent (const EventTriggerType& trigger, const IDynamicEventTimingMgr::DynamicTargetPtr& dynamicTarget, uint32 whichGroup) = 0;

	/**	Remove all instances of item from the selection's dynamic event.
		@param trigger is the trigger event to remove item from.
		@param dynamicTarget is the target item to remove.
		@return true if successful otherwise return false.
	*/
	virtual bool RemoveTargetInEvent (const EventTriggerType& trigger, const IDynamicEventTimingMgr::DynamicTargetPtr& dynamicTarget) = 0;

	/**	Returns true if we can re-order items in the list.
		@param trigger is the trigger event to move item from.
		@return true if successful otherwise return false.
	*/
	virtual bool CanMoveTargetInEvent (const EventTriggerType& trigger) const = 0;

	/**	Move item from old timing position to before the new timing position for the selection's dynamic event.
		@param trigger is the trigger event to move item from.
		@param dynamicTarget is the target item to move.
		@param oldGroup is the timing position of the item to move from. 
		@param beforeGroup is the timing position of the item to move before. 
		@return true if successful otherwise return false.
	*/
	virtual bool MoveTargetBeforeInEvent (const EventTriggerType& trigger, const IDynamicEventTimingMgr::DynamicTargetPtr& dynamicTarget, uint32 oldGroup, uint32 beforeGroup) = 0;

	/**	Move item from old timing position to after the new timing position for the selection's dynamic event.
		@param trigger is the trigger event to move item from.
		@param dynamicTarget is the target item to move.
		@param oldGroup is the timing position of the item to move from. 
		@param afterGroup is the timing position of the item to move after. 
		@return true if successful otherwise return false.
	*/
	virtual bool MoveTargetAfterInEvent (const EventTriggerType& trigger, const IDynamicEventTimingMgr::DynamicTargetPtr& dynamicTarget, uint32 oldGroup, uint32 afterGroup) = 0;

	/**	Move item from old timing position to the new timing position for the selection's dynamic event.
		@param trigger is the trigger event to move item from.
		@param dynamicTarget is the target item to move.
		@param oldGroup is the timing position of the item to move from. 
		@param atGroup is the timing position of the item to move to. 
		@param at is the position within the atGroup the item is moved to.
		The item is added to the end of the group if at = -1.
		@return true if successful otherwise return false.
	*/
	virtual bool MoveTargetToInEventAt (const EventTriggerType& trigger, const IDynamicEventTimingMgr::DynamicTargetPtr& dynamicTarget, uint32 oldGroup, uint32 atGroup, int32 at) = 0;

	/**	Set item delay for the nth item in the selection's dynamic event.
		@param trigger is the trigger event the item is in.
		@param dynamicTarget is the target item to move.
		@param which is the position of the item to set. 
		@param delay is the time delay to set.
		@return true if successful otherwise return false.
	*/
	virtual bool SetTargetDelayInEvent (const EventTriggerType& trigger, const IDynamicEventTimingMgr::DynamicTargetPtr& dynamicTarget, uint32 which, const PMReal& delay) = 0;

	/**	Get item delay for the nth item in the selection's dynamic event.
		@param trigger is the trigger event the item is in.
		@param dynamicTarget is the target item to move.
		@param which is the position of the item to set. 
		@return the time delay for this item.
	*/
	virtual PMReal GetTargetDelayInEvent (const EventTriggerType& trigger, const IDynamicEventTimingMgr::DynamicTargetPtr& dynamicTarget, uint32 which) const = 0;

	/**	Find the target in the specified trigger event. Returns the group index the target is in and the
		relative position of the target in the group. If it's a single target group, then the target position is 0.
		@param trigger is the trigger event the item is in.
		@param dynamicTarget is the target item to find.
		@param position is the relative position the target is in the group.
		@return the group index. If target is not found, group index is -1.
	*/
	virtual int32 FindTargetInEvent (const EventTriggerType& trigger, const IDynamicEventTimingMgr::DynamicTargetPtr& dynamicTarget, uint32& position) const = 0;

	/**	Unlink the target in group from the selection's dynamic event. This remove the specified target
		in the group and adds it to the end of the timing list for this event.
		@param trigger is the trigger event the item is in.
		@param dynamicTarget is the target item to move.
		@param which is the nth item in teh dynamic event timing list to get.
		@return true if successful otherwise return false.
	*/
	virtual bool UnlinkTargetInEvent (const EventTriggerType& trigger, const IDynamicEventTimingMgr::DynamicTargetPtr& dynamicTarget, uint32 which) = 0;

	/**	Group targets for the specified dynamic event. 
		@param trigger is the trigger event the items are in.
		@param targetList contains a list of targets to be grouped.
		@param newGroup is the new group position.
		@return true if successful
	*/
	virtual bool GroupTargetsInEvent (const EventTriggerType& trigger, const IDynamicEventTimingMgr::DynamicTargetList& targetList, uint32 newGroup) = 0;

	/**	Return a list of unassigned targets for the selection.
		@param unassignedTargetList contains a list of unassigned targets.
		@return true if there are unassigned targets.
	*/
	virtual bool GetUnassignedTargets (std::vector<UID>& unassignedTargetList) const = 0;

	/**	Reassign targets to a different events
		@param trigger is the trigger event the items are in. If trigger is kNoTriggerEvent, this means the specified targets
		were unassigned.
		@param newTrigger is the new trigger event to reassign to.
		@param targetList contains a list of targets to be reassigned.
		@return true if successful
	*/
	virtual bool ReassignEventForTargets (const EventTriggerType& trigger, const EventTriggerType& newTrigger, const IDynamicEventTimingMgr::DynamicTargetList& targetList) const = 0;

};



#endif	// __IDynamicEventTimingSuite__

