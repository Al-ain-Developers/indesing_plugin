//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IDynamicEventTimingFacade.h $
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
//  ADOBE CONFIDENTIAL
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
#include "DynamicDocumentsID.h"
#include "IDynamicEventTimingMgr.h"

#include "AnimationTypes.h"
#include "UIDList.h"
#include "Utils.h"


namespace Facade
{
	/** This facade provides services for managing one or more timing lists.
		A timing list is a play list consists of targets (page items) triggered by an animation, 
		page event, a MSO object, or button action event. Targets can be animated objects, videos, and sounds.
		Targets can be grouped to play simultaneous or play sequential.
		@see IDynamicEventTimingMgr.h for more detail.

		NOTE: Do not call dynamic event timing related commands directly. All manipulation on the timing manager
		should be called either through this facade or other related facades and utility interfaces. For selection
		related access, use IDynamicEventTimingSuite.h
		@see IDynamicEventTimingSuite.h
	*/

class IDynamicEventTimingFacade : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IDYNAMICEVENTTIMINGFACADE };

		/**	Dynamic target data methods.
		*/
		/**	Construct a DynamicTargetPtr based on the specified UID, role, and action.
			@param ownerRef is the UIDRef of spread, button, or MSO.
			@param targetUID is the targetUID. For button targets, this UID is action UID.
			@param role is the target's role.
			@param action is the target's action.
			@return DynamicTargetPtr for this target.
		*/
		virtual IDynamicEventTimingMgr::DynamicTargetPtr CreateDynamicTarget (const UIDRef& ownerRef, const UIDRef& targetRef, uint32 role = kTimingTargetRoleDefault, uint32 action = kTimingTargetVerbPlay) = 0;
		/**	Construct a DynamicTargetPtr based on another DynamicTarget object.
			@param targetRef is the UIDRef of the target. For button targets, this is the button action UIDRef.
			@param role is the target's role.
			@param action is the target's action.
			@return DynamicTargetPtr for this target.
		*/
		virtual IDynamicEventTimingMgr::DynamicTargetPtr CreateDynamicTarget (const UIDRef& targetRef, uint32 role = kTimingTargetRoleDefault, uint32 action = kTimingTargetVerbPlay) = 0;
		/**	Construct a DynamicTargetPtr from another DynamicTarget
			@param targetOrOwnerRef is a targetRef or ownerRef.
			@param targetPtr is a dynamic target to create from.
			@return DynamicTargetPtr for this target.
		*/
		virtual IDynamicEventTimingMgr::DynamicTargetPtr CreateDynamicTarget (const UIDRef& targetOrOwnerRef, const IDynamicEventTimingMgr::DynamicTargetPtr& targetPtr) = 0;
		/**	Find the specified dynamic target in the list. The target is considered equal if target's UID,
			role, and action are equal.
			@param ownerRef is the UIDRef of spread, button, or MSO.
			@param targetlist is the list of DynamicTarget objects to search.
			@param target is the DynamicTarget object to find. If found, the content of the dynamic target from the list is copied.
			@return the index of the dynamic target in the list. If not found, index is set to -1.
		*/
		virtual int32 FindDynamicTarget (const UIDRef& ownerRef, const IDynamicEventTimingMgr::DynamicTargetList& targetlist, IDynamicEventTimingMgr::DynamicTargetPtr& target) const = 0;

		/**	Spread, MSO, or button events:
		*/

		/**	Return true if specified target is triggered by page load or page click or both page trigger events.
			@param itemRef is the UIDRef of the target.
			@param eventList is the optional list of page trigger events the item is in.
			@return true if target is triggered by page events.
		*/
		virtual bool DynamicTargetTriggeredByPageEvents (const UIDRef& itemRef, std::vector<EventTriggerType>* eventList = nil) const = 0;

		/**	Returns the owner's dynamic event index. 
			@param ownerRef is the UIDRef of spread, button, or MSO.
			@param trigger is the event to find.
			@return the event trigger index or -1 if this event trigger is not found.
		*/
		virtual int32 FindDynamicEvent (const UIDRef& ownerRef, const EventTriggerType& trigger) const = 0;

		/**	Returns the specified owner's dynamic event and all of the items associated with this event. 
			@param ownerRef is the UIDRef of spread, button, or MSO.
			@param trigger is the event to remove.
			@return true if successful otherwise false.
		*/
		virtual bool RemoveDynamicEvent (const UIDRef& ownerRef, const EventTriggerType& trigger) const = 0;

		/**	Get number of dynamic events for the specified owning ref.
			@param ownerRef is the UIDRef of spread, button, or MSO.
			@return the number of event triggers
		*/
		virtual uint32 GetNumDynamicEvents (const UIDRef& ownerRef) const = 0;

		/**	Get nth dynamic events for the specified owning ref.
			@param ownerRef is the UIDRef of spread, button, or MSO.
			@param which is the nth dynamic event to get.
			@return the event trigger.
		*/
		virtual EventTriggerType GetNthDynamicEvent (const UIDRef& ownerRef, uint32 which) const = 0;

		/**	Get number of items in the owner's dynamic event timing list.
			@param ownerRef is the UIDRef of spread, button, or MSO.
			@param trigger is the trigger event the item is in.
			@return the number of items
		*/
		virtual uint32 GetNumGroupsInEvent (const UIDRef& ownerRef, const EventTriggerType& trigger) const = 0;

		/**	Get timing item list the nth position for the owner's dynamic event.
			@param ownerRef is the UIDRef of spread, button, or MSO.
			@param trigger is the trigger event the item is in.
			@param which is the nth item in teh dynamic event timing list to get.
			@param itemList is the list containing one or more target items in nth position of the timing list.
			@return true if successful otherwise return false.
		*/
		virtual bool GetNthGroupItemsInEvent (const UIDRef& ownerRef, const EventTriggerType& trigger, uint32 which, IDynamicEventTimingMgr::DynamicTargetList& itemList) const = 0;

		/** Gets the specified event trigger's nth item's number of plays.
			@note: For items that are targets of button actions, they are referenced directly by the buttons.
			@param ownerRef is the UIDRef of spread, button, or MSO.
			@param whichTrigger is the event trigger to remove.
			@param which is the group item.
			@param numPlays is the number of times this group plays.
			@return true if successful; other retruns false.
		*/
		virtual uint32 GetNthGroupNumPlaysInEvent (const UIDRef& ownerRef, const EventTriggerType& whichTrigger, uint32 which) const = 0;

		/** Gets the specified event trigger's nth item's number of plays.
			@note: For items that are targets of button actions, they are referenced directly by the buttons.
			@param ownerRef is the UIDRef of spread, button, or MSO.
			@param whichTrigger is the event trigger to remove.
			@param which is the group item.
			@param newNumPlays is the new number of times this group should play.
			@return true if successful; other retruns false.
		*/
		virtual bool SetNthGroupNumPlaysInEvent (const UIDRef& ownerRef, const EventTriggerType& whichTrigger, uint32 which, uint32 newNumPlays) = 0;

		/** Gets whether or not the specified event trigger's nth item is looping.
			@note: For items that are targets of button actions, they are referenced directly by the buttons.
			@param ownerRef is the UIDRef of spread, button, or MSO.
			@param whichTrigger is the event trigger to remove.
			@param which is the group item.
			@param playsLoop is true if group loops.
			@return true if successful; other retruns false.
		*/
		virtual bool GetNthGroupPlaysLoopInEvent (const UIDRef& ownerRef, const EventTriggerType& whichTrigger, uint32 which) const = 0;

		/** Sets whether or not the specified event trigger's nth item should loop.
			@note: For items that are targets of button actions, they are referenced directly by the buttons.
			@param ownerRef is the UIDRef of spread, button, or MSO.
			@param whichTrigger is the event trigger to remove.
			@param which is the group item.
			@param playsLoop is true if group loops.
			@return true if successful; other retruns false.
		*/
		virtual bool SetNthGroupPlaysLoopInEvent (const UIDRef& ownerRef, const EventTriggerType& whichTrigger, uint32 which, bool playsLoop) = 0;

		/**	Move the specified owner's nth item for dynamic event to the new position. This item could be a single target item or a group.
			@param ownerRef is the UIDRef of spread, button, or MSO.
			If ownerRef is a spread, itemRef must be on this spread.
			If ownerRef is a button or MSO, then itemRef and button or MSO must be on the same spread.
			@param trigger is the event trigger.
			@param which is the nth item in the event's timing list.
			@param newPosition is the new position to move to. If newPosition is -1, the item is moved to the end.
			@return true if successful otherwise false.
		*/
		virtual bool MoveNthGroupInEvent (const UIDRef& ownerRef, const EventTriggerType& trigger, uint32 which, int32 newPosition) const = 0;

		/**	Remove nth item from the owner's dynamic event. If nth item is a group (has more than one target items),
			then the entire group is removed.
			@param ownerRef is the UIDRef of spread, button, or MSO.
			If ownerRef is a spread, itemRef must be on this spread.
			If ownerRef is a button or MSO, then itemRef and button or MSO must be on the same spread.
			@param trigger is the event trigger.
			@param which is the nth item in the event's timing list to remove.
			@return true if successful otherwise false.
		*/
		virtual bool RemoveNthGroupInEvent (const UIDRef& ownerRef, const EventTriggerType& trigger, uint32 which) const = 0;

		/**	Unlink nth group item in the specified event. The targets in the group are placed as separate items in teh
			event's timing list.
			@param ownerRef is the UIDRef of spread, button, or MSO.
			@param trigger is the trigger event the item is in.
			@param which is the group to unlink. 
			@return true if successful otherwise return false.
		*/
		virtual bool UnlinkNthGroupInEvent (const UIDRef& ownerRef, const EventTriggerType& trigger, uint32 which) const = 0;

		/**	Add target item to the owner's dynamic event. This target item is added at the end of the list.
			@param ownerRef is the UIDRef of spread, button, or MSO.
			If ownerRef is a spread, itemRef must be on this spread.
			If ownerRef is a button or MSO, then itemRef and button or MSO must be on the same spread.
			@param trigger is the event to add target item to.
			@param dynamicTarget is the item to add. If target's delay or data is set, they will be copied.
			@param at is the group (position) to add the item into. Default is -1 which mean to add the item as a new group at the end.
			@return true if successful otherwise return false.
		*/
		virtual bool AddTargetInNthGroup(const UIDRef& ownerRef, const EventTriggerType& trigger, const IDynamicEventTimingMgr::DynamicTargetPtr& dynamicTarget, int32 at = -1) const = 0;

		/**	Replace target item in the owner's dynamic event.
			@param ownerRef is the UIDRef of spread, button, or MSO.
			If ownerRef is a spread, itemRef must be on this spread.
			If ownerRef is a button or MSO, then itemRef and button or MSO must be on the same spread.
			@param trigger is the event to add target item to.
			@param targetToReplace is the target item to replace.
			@param newTarget is the target item to replace with. newTarget's delay and data are copied.
			@param whichGroup is the group in which the targetRef should be replaced.
			@return true if successful otherwise return false.
		*/
		virtual bool ReplaceTargetInNthGroup(const UIDRef& ownerRef, const EventTriggerType& trigger, const IDynamicEventTimingMgr::DynamicTargetPtr& targetToReplace, const IDynamicEventTimingMgr::DynamicTargetPtr& newTarget, uint32 whichGroup) const = 0;

		/**	Remove target item from the owner's dynamic event. If removing from a position where
			there are more than one target item in the group, then this target item is unlinked from the group.
			@param ownerRef is the UIDRef of spread, button, or MSO.
			If ownerRef is a spread, itemRef must be on this spread.
			If ownerRef is a button or MSO, then itemRef and button or MSO must be on the same spread.
			@param trigger is the trigger event to remove item from.
			@param dynamicTarget is the target item within the group at which position.
			Item at which position could be a group or a single item. If a group, dynamicTarget specifies a target item in the group.
			@param which is the position in the timing list to remove from.
			@return true if successful otherwise return false.
		*/
		virtual bool RemoveTargetInNthGroup (const UIDRef& ownerRef, const EventTriggerType& trigger, const IDynamicEventTimingMgr::DynamicTargetPtr& dynamicTarget, uint32 which) const = 0;

		/**	Remove all instances of this target item from the owner's dynamic event.
			@param ownerRef is the UIDRef of spread, button, or MSO.
			If ownerRef is a spread, itemRef must be on this spread.
			If ownerRef is a button or MSO, then itemRef and button or MSO must be on the same spread.
			@param trigger is the trigger event to remove item from.
			@param targetRef is all instances of target item to remove.
			@return true if successful otherwise return false.
		*/
		virtual bool RemoveTargetInEvent (const UIDRef& ownerRef, const EventTriggerType& trigger, const UIDRef& targetRef) const = 0;

		/**	Move target item from the old timing position to before the new timing position for the specified owner's dynamic event.
			If the target item is in a linked group at the old timing position, it is unlinked from the group.
			@param ownerRef is the UIDRef of spread, button, or MSO.
			If ownerRef is a spread, itemRef must be on this spread.
			If ownerRef is a button or MSO, then itemRef and button or MSO must be on the same spread.
			@param trigger is the trigger event to move item from.
			@param dynamicTarget is the target item within the group at oldGroup.
			Item at oldGroup could be a group or a single item. If a group, dynamicTarget specifies a target item in the group.
			@param oldGroup is the timing position of the target item to move from. 
			@param beforeGroup is the timing position of the target item to move before. 
			@return true if successful otherwise return false.
		*/
		virtual bool MoveTargetBeforeNthGroupInEvent (const UIDRef& ownerRef, const EventTriggerType& trigger, const IDynamicEventTimingMgr::DynamicTargetPtr& dynamicTarget, uint32 oldGroup, uint32 beforeGroup) const = 0;

		/**	Move target item from old timing position to after the new timing position for the owner's dynamic event.
			If the target item is in a linked group at the old timing position, it is unlinked from the group.
			@param ownerRef is the UIDRef of spread, button, or MSO.
			If ownerRef is a spread, itemRef must be on this spread.
			If ownerRef is a button or MSO, then dynamicTarget and button or MSO must be on the same spread.
			@param trigger is the trigger event to move item from.
			@param dynamicTarget is the target item within the group at oldGroup.
			Item at oldGroup could be a group or a single item. If a group, dynamicTarget specifies a target item in the group.
			@param old position is the timing position of the target item to move from. 
			@param new position is the timing position of the target item to move after. 
			@return true if successful otherwise return false.
		*/
		virtual bool MoveTargetAfterNthGroupInEvent (const UIDRef& ownerRef, const EventTriggerType& trigger, const IDynamicEventTimingMgr::DynamicTargetPtr& dynamicTarget, uint32 oldGroup, uint32 afterGroup) const = 0;

		/**	Move target item from old timing position to the new timing position for the owner's dynamic event.
			If the target item is in a linked group at the old timing position, it is unlinked from the group.
			If the new position already has a group, then this target item becomes part of the group.
			@param ownerRef is the UIDRef of spread, button, or MSO.
			If ownerRef is a spread, itemRef must be on this spread.
			If ownerRef is a button or MSO, then dynamicTarget and button or MSO must be on the same spread.
			@param trigger is the trigger event to move item from.
			@param dynamicTarget is the target item within the group at oldGroup.
			Item at oldGroup could be a group or a single item. If a group, dynamicTarget specifies a target item in the group.
			@param oldGroup is the timing position of the target item to move from. 
			@param atGroup is the timing position of the target item to move into. 
			@param at is the position within atGroup that the target item is to be moved to. 
			If at is -1, the item is added at the end of the group.
			@return true if successful otherwise return false.
		*/
		virtual bool MoveTargetIntoNthGroupAt (const UIDRef& ownerRef, const EventTriggerType& trigger, const IDynamicEventTimingMgr::DynamicTargetPtr& dynamicTarget, uint32 oldGroup, uint32 atGroup, int32 at = -1) const = 0;

		/**	Set target item delay for the nth item (which group) in the owner's dynamic event timing list.
			@param ownerRef is the UIDRef of spread, button, or MSO.
			If ownerRef is a spread, itemRef must be on this spread.
			If ownerRef is a button or MSO, then dynamicTarget and button or MSO must be on the same spread.
			@param trigger is the trigger event the item is in.
			@param dynamicTarget is the target item within the group in the which group position.
			Item at which could be a group or a single item. If a group, dynamicTarget specifies a target item in the group.
			@param which is the position of the timing item. At this position could be just a single item or a group. 
			@param delay is the time delay to set.
			@return true if successful otherwise return false.
		*/
		virtual bool SetTargetDelayInNthGroup (const UIDRef& ownerRef, const EventTriggerType& trigger, const IDynamicEventTimingMgr::DynamicTargetPtr& dynamicTarget, uint32 which, const PMReal& delay) const = 0;

		/**	Get target item delay for the nth item (which group) in the owner's dynamic event.
			@param ownerRef is the UIDRef of spread, button, or MSO.
			@param trigger is the trigger event the item is in.
			@param dynamicTarget is the target item within the group in the which groupposition.
			Item at which could be a group or a single item. If a group, dynamicTarget specifies a target item in the group.
			@param which is the position of the timing item. At this position could be just a single item or a group. 
			@return the time delay for this target item.
		*/
		virtual PMReal GetTargetDelayInNthGroup (const UIDRef& ownerRef, const EventTriggerType& trigger, const IDynamicEventTimingMgr::DynamicTargetPtr& dynamicTarget, uint32 which) const = 0;

		/**	Get target item data for the nth item (which group) in the owner's dynamic event.
			@param ownerRef is the UIDRef of spread, button, or MSO.
			@param trigger is the trigger event the item is in.
			@param dynamicTarget is the target item within the group in the which position. Dynamic target data is copied here if exists.
			Item at which could be a group or a single item. If a group, dynamicTarget specifies a target item in the group.
			@param which is the position of the timing item. At this position, target could be just a single item or a group. 
			@return bool if successful.
		*/
		virtual IDynamicEventTimingMgr::DynamicTargetPtr GetTargetDataInNthGroup (const UIDRef& ownerRef, const EventTriggerType& trigger, const IDynamicEventTimingMgr::DynamicTargetPtr& dynamicTarget, uint32 which) const = 0;

		/**	Set target item delay for the nth item (which group) in the owner's dynamic event timing list.
			@param ownerRef is the UIDRef of spread, button, or MSO.
			If ownerRef is a spread, itemRef must be on this spread.
			If ownerRef is a button or MSO, then itemRef and button or MSO must be on the same spread.
			@param trigger is the trigger event the item is in.
			@param dynamicTarget is the target item within the group in the which group position.
			Item at which could be a group or a single item. If a group, dynamicTarget specifies a target item in the group.
			@param which is the position of the timing item. At this position could be just a single item or a group. 
			@return true if successful otherwise return false.
		*/
		virtual bool SetTargetDataInNthGroup (const UIDRef& ownerRef, const EventTriggerType& trigger, const IDynamicEventTimingMgr::DynamicTargetPtr& dynamicTarget, uint32 which) const = 0;

		/**	Group targets for the specified dynamic event.
			@param ownerRef is the UIDRef of spread, button, or MSO.
			@param trigger is the trigger event the items are in.
			@param targetList contains a list of targets to be grouped.
			@param newGroup is position for the resulting new group.
			@return true if successful
		*/
		virtual bool GroupTargetsInEvent (const UIDRef& ownerRef, const EventTriggerType& trigger, const IDynamicEventTimingMgr::DynamicTargetList& targetList, int32 newGroup) const = 0;

		/**	Unlink the target in nth group item in the specified event. The target is removed from the group and
			placed as separate items at the end of the timing list.
			@param ownerRef is the UIDRef of spread, button, or MSO.
			@param trigger is the trigger event the item is in.
			@param dynamicTarget is the target item within the group in the nth item position.
			@param which is the group to unlink from. 
			@return true if successful otherwise return false.
		*/
		virtual bool UnlinkTargetInEvent (const UIDRef& ownerRef, const EventTriggerType& trigger, const IDynamicEventTimingMgr::DynamicTargetPtr& dynamicTarget, uint32 which) const = 0;

		/** Find the target in the specified event triggered timing list.
			@param ownerRef is the UIDRef of spread, button, or MSO.
			@param whichTrigger is the event trigger.
			@param dynamicTarget is the target item to find in this triggering event.
			@param itemList is the entire item list at this position. dynamicTarget must be a member of this list. 
			The list reflects the sequence of items for their group.
			@param pItemPosition, if not nil, contains the position of the dynamicTarget in the itemList.
			@returns the position or the nth group in which the dynamicTarget is found. Returns -1 if dynamicTarget is not found in the list.
		*/
		virtual int32 FindTargetInEvent (const UIDRef& ownerRef, const EventTriggerType& whichTrigger, const IDynamicEventTimingMgr::DynamicTargetPtr& dynamicTarget, IDynamicEventTimingMgr::DynamicTargetList& itemList, uint32* pItemPosition = nil) const = 0; 

		/** Find the target in the nth group of the specified event triggered timing list.
			@param ownerRef is the UIDRef of spread, button, or MSO.
			@param whichTrigger is the event trigger.
			@param dynamicTarget is the target item to find in this triggering event.
			@param which is the group to search. 
			@returns the position or the item whithin the specified group. Returns -1 if itemUID is not found in this group.
		*/
		virtual int32 FindTargetInNthGroup (const UIDRef& ownerRef, const EventTriggerType& whichTrigger, const IDynamicEventTimingMgr::DynamicTargetPtr& dynamicTarget, uint32 which) const = 0; 

		/** Reassign the specified targets to the new timing event. If targets were grouped, then the groups are retained.
			Otherwise, the targets are append at the end of the new timing list.
			@param ownerRef is the UIDRef of spread or MSO.
			@param trigger is the event trigger to reassign the targets from.
			If trigger is kNoTriggerEvent, this means the specified targets were unassigned.
			@param newTrigger is the event trigger to reassign the targets to.
			@param targetList is the list of targets to reassign.
			@return true if successful otherwise return false.
		*/
		virtual bool ReassignEventForTargets (const UIDRef& ownerRef, const EventTriggerType& trigger, const EventTriggerType& newTrigger, const IDynamicEventTimingMgr::DynamicTargetList& targetList) const = 0;
		
		/**	Self-click and rollover
		*/
		/**	Returns true if specified object is self-tirggered.
			@param itemRef is the object's UIDRef.
			@return true is item is self-triggered.
		*/
		virtual bool DynamicTargetIsSelfTriggered (const UIDRef& itemRef) const = 0;

		/**	Get ths item's dynamic event if any. This should be one of kOnSelfClcik or kOnSelfRollover.
			These two events are mutually exclusive.
			@param itemRef is the item's UIDRef.
			@return the item's dynamic event if any. If none, then kNoTriggerEvent is returned.
		*/
		virtual EventTriggerType GetSelfClickRolloverItemDynamicEvent (const UIDRef& itemRef) const = 0;

		/**	Add self click or rollover to item. These two events are mutually exclusive.
			If self click is already added, then adding self rollover will replace self click.
			If self rollover is already added, then adding self click will replace self rollover.
			@param itemRef is the item to add.
			@param trigger is the event to add item to.
			@return true if successful otherwise return false.
		*/
		virtual bool AddSelfClickRolloverDynamicEventToItem (const UIDRef& itemRef, const EventTriggerType& trigger) const = 0;

		/**	Remove self click or rollover from item.
			@param itemRef is the item to add.
			@param trigger is the trigger event to remove item from.
			@return true if successful otherwise return false.
		*/
		virtual bool RemoveSelfClickRolloverDynamicEventFromItem (const UIDRef& itemRef, const EventTriggerType& trigger) const = 0;

		/**	Set item delay for the self triggered item.
			@param itemRef is the item to set.
			@param delay is the time delay to set.
			@return true if successful otherwise return false.
		*/
		virtual bool SetSelfClickRolloverItemDelay (const UIDRef& itemRef, const PMReal& delay) const = 0;

		/**	Get item delay for the self triggered item.
			@param itemRef is the item to set.
			@return the time delay.
		*/
		virtual PMReal GetSelfClickRolloverItemDelay (const UIDRef& itemRef) const = 0;

		/**	Set item target data for the self triggered item.
			@param itemRef is the item to set.
			@param dynamicTarget is the target data to set. 
			@return true if successful otherwise return false.
		*/
		virtual bool SetSelfClickRolloverItemTargetData (const UIDRef& itemRef, const IDynamicEventTimingMgr::DynamicTargetPtr& dynamicTarget) const = 0;

		/**	Get item traget data for the self triggered item.
			@param itemRef is the item to set.
			@return the target data.
		*/
		virtual IDynamicEventTimingMgr::DynamicTargetPtr GetSelfClickRolloverItemTargetData (const UIDRef& itemRef) const = 0;
};

};	// namespace