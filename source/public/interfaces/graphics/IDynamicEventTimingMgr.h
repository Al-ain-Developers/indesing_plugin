//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IDynamicEventTimingMgr.h $
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
#ifndef __IDynamicEventTimingMgr__
#define __IDynamicEventTimingMgr__

#include "DynamicDocumentsID.h"
#include "IPMUnknown.h"
#include "AnimationTypes.h"
#include "vector"
#include "ScriptData.h"

/**
	This is a persistent data interface for the timing lists. Timing list is a list of targets (page items) 
	triggered by an animation, page event, or button action event. Objects that can be targets of event triggers 
	are media items (movies, sounds, SWFs), and page item with animation. Objects that can trigger other 
	objects are spreads, page item with animation, and buttons. There can be one or more timing lists
	per triggering object. Spreads has both page load and page click events. 
	Animation can be self clicked or self rollover only. They must be mutually exclusive, however. Buttons can have 
	object click, release, object rollover, and rolloff.
	@see AnimationTypes.h

	Items in the timing list can be re-ordered. One or more items can be grouped to play at the same time.
	Each item in the group can have its own time delay. Time delay is cumulative.
	The first target delay within a group specified the time delay from the time the group starts to play.
	The next target within the same group is delayed by cumulative delay for the group so far plus its own.
	If there are no delay specified, then the items in the group played simultaneously.

	On a high-level, the data in the timing manager has this relationship:

	For each triggering event:
		Group 0,
			(target x, target x delay)
		Group 1,
			(target y, target y delay)
		...
		Group n,
			(target 1, target 1 delay), (target 2, target 2 delay), ... (target n, target n delay)
		...
		Group z
			...

	Additionally, there're group-level play attributes. Each group can be set to play in loop or play one or more times.
	Group level play attributes will trump individual animation's loop but will not affect individual multiple plays.
	For single target group, the group-level play attributes are ignored.

*/

class IDynamicEventTimingMgr : public IPMUnknown
{	
public:
	enum {kDefaultIID = IID_IDYNAMICEVENTTIMINGMGR};

	/**	Data definition for timing target.

		The target for the timing list is a simple ref-counted virtual c++ object, DynamicTarget.
		The attributes which represents a timing target are the item's UID, which role does this item
		represents, and what actions. In addition, it may also contain one or more pieces of data such
		as video navigation points, whether to play an animation in reverse, and others. These data are
		represented by an ID, and a data values.

		To create a dynamic target, use one of the two CreateDynamicTarget method provided.
		To find a dynamic target in a list of dynamic targets, use FindDynamicTarget. It considers
		that two dynamic targets are equivalent if at least, its UID, role, and action are equal.
		They are completely equals if UID, role, action, and all data values are equal.
	*/

	/**	type definition for dynamic target data values.
	*/
	typedef ScriptData TargetDataType;

	class DynamicTarget : boost::noncopyable
	{
		friend class DynamicTargetImpl;
		
		virtual ~DynamicTarget() {}
		
		virtual void AddRef() const = 0;
		virtual void Release() const = 0;
		
	public:
		/** @return the target's UID. For button, this UID is the action UID.
		*/
		virtual UID GetTargetUID () const = 0;
		
		/** @return the target's role. Current values are:
				kTimingTargetRoleVideo
				kTimingTargetRoleAnimation
				kTimingTargetRoleSound
			@see DynamicDocumentsID.h
		*/
		virtual uint32 GetRole () const = 0;

		/** @return the target's action. Current values are:
				kTimingTargetVerbPlay
				kTimingTargetVerbStop
				kTimingTargetVerbPause
				kTimingTargetVerbResume
			@see DynamicDocumentsID.h
		*/
		virtual uint32 GetAction () const = 0;

		/** Set target's action.
			@param targetAction is one of these values:
				kTimingTargetVerbPlay
				kTimingTargetVerbStop
				kTimingTargetVerbPause
				kTimingTargetVerbResume
			@see DynamicDocumentsID.h
		*/
		virtual void SetAction (uint32 targetAction) = 0;

		/** @return the target's delay.
		*/
		virtual PMReal GetDelay () const = 0;

		/** Set target's delay.
			@param targetDelay is target delay to set.
		*/
		virtual void SetDelay (const PMReal& targetDelay) = 0;

		/** Return true if target has additional data.
			@param pDataIDList contains the data IDs if set.
			@return true if target has additional data.
		*/
		virtual bool HasData (std::vector<uint32>* pDataIDList = nil) const = 0;

		/** Get the data value for the specified data ID.
			@param dataID is the data ID to get.
			@param data is the value for this data ID.
			@return true if target has this data.
		*/
		virtual bool GetData (uint32 dataID, TargetDataType& data) const = 0;
		/** Add data for the specified data ID.
			@param dataID is the data ID to add.
			@param data is the value for this data ID.
			@return true if successful.
		*/
		virtual bool AddData (uint32 dataID, const TargetDataType& data) = 0;

		/** Remove the data value associated with specified data ID.
			@param dataID is the data ID to remove.
			@return true if successful.
		*/
		virtual bool RemoveData (uint32 dataID) = 0;

	public:
		
		friend void intrusive_ptr_add_ref(DynamicTarget *t)
		{
			t->AddRef();
		}
		
		friend void intrusive_ptr_release(DynamicTarget *t)
		{
			t->Release();
		}
	};
	
	typedef boost::intrusive_ptr<DynamicTarget> DynamicTargetPtr;
	typedef std::vector<DynamicTargetPtr> DynamicTargetList;

	enum {kInvalidTimingPosition = 0xffffffff};

	/**	Construct a DynamicTargetPtr based on the specified UID, role, and action.
		@param targetUID is the targetUID. For button targets, this UID is action UID.
		@param role is the target's role.
		@param action is the target's action.
		@return DynamicTargetPtr for this target.
	*/
	virtual DynamicTargetPtr CreateDynamicTarget (UID targetUID, uint32 role = kTimingTargetRoleDefault, uint32 action = kTimingTargetVerbPlay) = 0;
	/**	Construct a DynamicTargetPtr based on another DynamicTarget object.
		@param target is the source DynamicTarget object.
		@return DynamicTargetPtr for this target.
	*/
	virtual DynamicTargetPtr CreateDynamicTarget (const DynamicTargetPtr& target) = 0;
	/**	Find the specified dynamic target in the list. The target is considered equal if target's UID,
		role, and action are equal.
		@param targetlist is the list of DynamicTarget objects to search.
		@param target is the DynamicTarget object to find. If found, the content of the dynamic target from the list is copied.
		@return the index of the dynamic target in the list. If not found, index is set to -1.
	*/
	virtual int32 FindDynamicTarget (const DynamicTargetList& targetlist, DynamicTargetPtr& target) const = 0;

	/**	Find the first specified dynamic target UID in the list. The target UID is the actual target's UID.
		@param targetlist is the list of DynamicTarget objects to search.
		@param targetUID is the target UID to find. If found, the content of that dynamic target from the list is copied.
		@return the index of the first dynamic target matching the target UID in the list. If not found, index is set to -1.
	*/
	virtual int32 FindDynamicTarget (const DynamicTargetList& targetList, UID targetUID, DynamicTargetPtr& target) const = 0;
	
	/** Methods for events.
	*/

	/**	Returns the number of event triggers.
		@return the number of event triggers.
	*/
	virtual uint32 GetNumDynamicEvents () const = 0;

	/**	Add the specified event trigger
		@param newEventTrigger is the event trigger to add.
		@return true if successful; otherwise false.
	*/
	virtual bool AddDynamicEvent (const EventTriggerType& newEventTrigger) = 0;

	/**	Remove the specified event trigger
		@param whichTrigger is the event trigger to remove.
		@return true if successful; otherwise false.
	*/
	virtual bool RemoveDynamicEvent (const EventTriggerType& whichTrigger) = 0;

	/**	Returns the nth event trigger
		@param which is the nth event trigger to get.
		@return the nth event trigger.
	*/
	virtual EventTriggerType GetNthDynamicEvent (uint32 which) const = 0;

	/** Methods for group items in a event-based timing list.
	*/

	/** Remove the specified event trigger's nth item
		@note: For items that are targets of button actions, they are referenced directly by the buttons.
		@param whichTrigger is the event trigger to remove.
		@param which is the position to remove.
		@return true if successful; other retruns false.
	*/
	virtual bool RemoveNthGroup (const EventTriggerType& whichTrigger, uint32 which) = 0;

	/** move the specified event trigger's nth item to a new position
		@note: For items that are targets of button actions, they are referenced directly by the buttons.
		@param whichTrigger is the event trigger to remove.
		@param which is the position to move.
		@param newPosition is the new position to move to. If newPosition is -1, then move to the end of the list.
		@return true if successful; other retruns false.
	*/
	virtual bool MoveNthGroup (const EventTriggerType& whichTrigger, uint32 which, int32 newPosition) = 0;

	/** Gets the specified event trigger's nth item's number of plays.
		@note: For items that are targets of button actions, they are referenced directly by the buttons.
		@param whichTrigger is the event trigger to remove.
		@param which is the group item.
		@param numPlays is the number of times this group plays.
		@return true if successful; other retruns false.
	*/
	virtual bool GetNthGroupNumPlays (const EventTriggerType& whichTrigger, uint32 which, uint32& numPlays) const = 0;

	/** Gets the specified event trigger's nth item's number of plays.
		@note: For items that are targets of button actions, they are referenced directly by the buttons.
		@param whichTrigger is the event trigger to remove.
		@param which is the group item.
		@param newNumPlays is the new number of times this group should play.
		@return true if successful; other retruns false.
	*/
	virtual bool SetNthGroupNumPlays (const EventTriggerType& whichTrigger, uint32 which, uint32 newNumPlays) = 0;

	/** Gets whether or not the specified event trigger's nth item is looping.
		@note: For items that are targets of button actions, they are referenced directly by the buttons.
		@param whichTrigger is the event trigger to remove.
		@param which is the group item.
		@param playsLoop is true if group loops.
		@return true if successful; other retruns false.
	*/
	virtual bool GetNthGroupPlaysLoop (const EventTriggerType& whichTrigger, uint32 which, bool& playsLoop) const = 0;

	/** Sets whether or not the specified event trigger's nth item should loop.
		@note: For items that are targets of button actions, they are referenced directly by the buttons.
		@param whichTrigger is the event trigger to remove.
		@param which is the group item.
		@param playsLoop is true if group loops.
		@return true if successful; other retruns false.
	*/
	virtual bool SetNthGroupPlaysLoop (const EventTriggerType& whichTrigger, uint32 which, bool playsLoop) = 0;

	/** Get the number of timing items for the specified trigger event.
	*/
	virtual uint32 GetNumGroups (const EventTriggerType& whichTrigger) const = 0;

	/** Get the dynamic items for the specified timing position and trigger event.
		@param eventTrigger is the event trigger interested.
		@param whichGroup is the timing position.
		@param itemList contains a list of items for this position and trigger event.
		@return true if successful; otherwise retruns false.
	*/
	virtual bool GetNthGroupItems (const EventTriggerType& whichTrigger, uint32 whichGroup, DynamicTargetList& itemList) const = 0;

	/** Add the target in the specified event triggered timing list.
		If atGroup = -1, add target at the end of the list; otherwise add target in the nth group.
		@note: For items that are targets of button actions, itemUID is the action UID.
		@param whichTrigger is the event trigger.
		@param targetItem is the dynamic target item to add to this triggering event.
		@param atGroup is the group (position) to add the item into. Default is -1 which mean to add the item as a new group at the end.
		@return true if successful; otherwise retruns false.
	*/
	virtual bool AddTargetInNthGroup (const EventTriggerType& whichTrigger, const DynamicTargetPtr& targetItem, int32 atGroup = -1) = 0;

	/** Find the target in the specified event triggered timing list.
		This assumes targets are unique in the list.
		@note: For items that are targets of button actions, itemUID is the action UID.
		@param whichTrigger is the event trigger.
		@param targetItem is the dynamic target item to find in this triggering event.
		@param itemList is the entire item list at this position.
		@param pItemPosition, if not nil, contains the position of the itemUID in the itemList.
		@returns the position or the nth group in which the itemUID is found. Returns -1 if itemUID is not found in the list.
	*/
	virtual int32 FindTargetInEvent (const EventTriggerType& whichTrigger, const DynamicTargetPtr& targetItem, DynamicTargetList& itemList, uint32* pItemPosition = nil) const = 0; 

	/** Remove target at this position from the specified event trigger.
		@note: For items that are targets of button actions, itemUID is the action UID.
		@param whichTrigger is the event trigger to remove.
		@param targetItem is the item that is the target for this triggering event.
		@param which is the position from which to remove the item.
		@return true if successful; other retruns false.
	*/
	virtual bool RemoveTargetInNthGroup (const EventTriggerType& whichTrigger, const DynamicTargetPtr& targetItem, uint32 which) = 0;

	/** Replace the target at this position from the specified event trigger with the new one.
		@note: For items that are targets of button actions, itemUID is the action UID.
		@param whichTrigger is the event trigger to remove.
		@param targetItemToReplace is the item that is to be replaced.
		@param newTargetItem is the new dynamic target item to replace with.
		@param which is the nth group in which to replace the item.
		@return true if successful; other retruns false.
	*/
	virtual bool ReplaceTargetInNthGroup (const EventTriggerType& whichTrigger, const DynamicTargetPtr& targetItemToReplace, const DynamicTargetPtr& newTargetItem, uint32 which) = 0;

	/** Replace the target at the nth position in the specified event trigger with the new one.
		@note: For items that are targets of button actions, itemUID is the action UID.
		@param whichTrigger is the event trigger to remove.
		@param which is the nth group in which to replace the item.
		@param whichTarget is the nth target in the nth group to replace the item.
		@param newTargetItem is the new dynamic target item to replace with.
		@return true if successful; other retruns false.
	*/
	virtual bool ReplaceNthTargetInNthGroup (const EventTriggerType& whichTrigger, uint32 which, uint32 whichTarget, const DynamicTargetPtr& newTargetItem) = 0;

	/**	Remove all instances of item from the owner's dynamic event.
		@param trigger is the trigger event to remove item from.
		@param targetItem is the item to remove.
		@return true if successful otherwise return false.
	*/
	virtual bool RemoveTargetInEvent (const EventTriggerType& trigger, const DynamicTargetPtr& targetItem) = 0;

	/** Remove the item from all event trigger timing lists.
		For the spread, we are only tracking items that are triggered by page load or page click.
		Targets will be removed Permanently from all timing lists.
		@note: For items that are targets of button actions, itemUID is the action UID.
		@param itemUID is the item that may be the target for one or more triggering events.
		@return true if successful; other retruns false.
	*/
	virtual bool RemoveTargetForAllEvents (UID itemUID) = 0;

	/** Move item's timing position from old position to a position before the specified position for this trigger.
		@note items that have the same timing position play at the same time.
		@param whichTrigger is the event trigger to operate on.
		@param targetItem is the item to move.
		@param oldGroup is the item's old group.
		@param beforeGroup is the position to move the item before.
		@return true if successful; otherwise retruns false.
	*/
	virtual bool MoveTargetBeforeNthGroup (const EventTriggerType& whichTrigger, const DynamicTargetPtr& targetItem, uint32 oldGroup, uint32 beforeGroup) = 0;

	/** Move item's timing position from old position to a position after the specified position for this trigger.
		@note items that have the same timing position play at the same time.
		@param targetItem is the item to move.
		@param whichTrigger is the event trigger to operate on.
		@param oldGroup is the item's old group.
		@param afterGroup is the position to move the item after.
		@return true if successful; otherwise retruns false.
	*/
	virtual bool MoveTargetAfterNthGroup (const EventTriggerType& whichTrigger, const DynamicTargetPtr& targetItem, uint32 oldPosition, uint32 afterGroup) = 0;

	/** Move item's timing position from old position to the specified for this trigger.
		@note items that have the same timing position play at the same time.
		@param whichTrigger is the event trigger to operate on.
		@param targetItem is the item to move.
		@param oldGroup is the item's old group.
		@param atGroup is the group to move the item to.
		@param atPosition is the position within the group to move the item to.
		If atPosition = -1, then move the item to the end of the gorup.
		@return true if successful; otherwise retruns false.
	*/
	virtual bool MoveTargetIntoNthGroupAt (const EventTriggerType& whichTrigger, const DynamicTargetPtr& targetItem, uint32 oldGroup, uint32 atGroup, int32 atPosition = -1) = 0;

	/** Move item's timing position from old position to the new position for this trigger.
		@note items that have the same timing position play at the same time.
		@param whichTrigger is the event trigger to operate on.
		@param oldGroup is the item's old group.
		@param whichTarget is the nth item to move.
		@param atGroup is the new group to move the item to.
		@param atPosition is the position within the new group to move the item to.
		If atPosition = -1, then move the item to the end of the gorup.
		@return true if successful; otherwise retruns false.
	*/
	virtual bool MoveNthTargetIntoNthGroupAt (const EventTriggerType& whichTrigger, uint32 oldGroup, uint32 whichTarget, uint32 atGroup, int32 atPosition = -1) = 0;

	/** Set time delay in second for target item at nth item in the specified trigger.
		@param whichTrigger is the event trigger.
		@param targetItem is the targe item to get.
		@param whichGroup is the position in the timing list for this target.
		@param delay is the time delay to set for this item in the timing list.
		@return true if successful; otherwise retruns false.
	*/
	virtual bool SetTargetDelayInNthGroup (const EventTriggerType& trigger, const DynamicTargetPtr& targetItem, uint32 whichGroup, const PMReal& delay) = 0;

	/** Set time delay in second for nth target item of the nth group in the specified trigger.
		@param whichTrigger is the event trigger.
		@param whichGroup is the nth group in the timing list for this target.
		@param whichTarget is the nth targe item to get.
		@param delay is the time delay to set for this item in the timing list.
		@return true if successful; otherwise retruns false.
	*/
	virtual bool SetNthTargetDelayInNthGroup (const EventTriggerType& trigger, uint32 whichGroup, uint32 whichTarget, const PMReal& delay) = 0;

	/** Get the dynamic target data at nth group in the specified trigger.
		@param newEventTrigger is the event trigger.
		@param targetItem is the targe item to get.
		@param whichGroup is the position in the timing list for this target.
		@param delay is the time delay to get for this target item in the timing list.
		@return true if successful; otherwise retruns false.
	*/
	virtual bool GetTargetDelayInNthGroup (const EventTriggerType& trigger, const DynamicTargetPtr& targetItem, uint32 whichGroup, PMReal& delay) const = 0;

	/** Set dynamic target data for target item at nth item in the specified trigger.
		@param whichTrigger is the event trigger.
		@param targetItem is the targe item to set. 
		@param whichGroup is the position in the timing list for this trigger.
		@return true if successful; otherwise retruns false.
	*/
	virtual bool SetTargetDataInNthGroup (const EventTriggerType& trigger, const DynamicTargetPtr& targetItem, uint32 whichGroup) = 0;

	/** Set dynamic target data for target item at the nth item in the specified trigger.
		@param whichTrigger is the event trigger.
		@param whichGroup is the nth group in the timing list for this trigger.
		@param whichTarget is the nth targe item to set. 
		@param newTargetData is the new data to set.
		@return true if successful; otherwise retruns false.
	*/
	virtual bool SetNthTargetDataInNthGroup (const EventTriggerType& trigger, uint32 whichGroup, uint32 whichTarget,const DynamicTargetPtr& newTargetData) = 0;

	/** Get target data for target item of the nth group in the specified trigger.
		@param newEventTrigger is the event trigger.
		@param targetItem is the targe item to get.
		@param whichGroup is the position in the timing list for this target.
		@return DynamicTarget if successful; otherwise retruns nil dynamic target pointer.
	*/
	virtual IDynamicEventTimingMgr::DynamicTargetPtr GetTargetDataInNthGroup (const EventTriggerType& trigger, const DynamicTargetPtr& targetItem, uint32 whichGroup) const = 0;

	/** Get target data for nth target item of nth group in the specified trigger.
		@param newEventTrigger is the event trigger.
		@param whichGroup is the group position in the timing list for this target.
		@param whichTarget is the position in nth group for this target.
		@return DynamicTarget if successful; otherwise retruns nil dynamic target pointer.
	*/
	virtual IDynamicEventTimingMgr::DynamicTargetPtr GetNthTargetDataInNthGroup (const EventTriggerType& trigger, uint32 whichGroup, uint32 whichTarget) const = 0;

	/** Invalidate specified targets. This can occur if targets were deleted, moved, or converted, etc.
		@param targetList is the target list to invalidate.
		@return true if successful; otherwise retruns false.
	*/
	virtual void InvalidateTargets (const UIDList& targetList) = 0;

	/** Validate event trigger.
		@param whichTrigger is the trigger to validate
		@return returns the valid trigger or kNoTriggerEvent if trigger is not valid for this timing manager.
	*/
	virtual EventTriggerType ValidateTriggerType (const EventTriggerType& whichTrigger) const = 0;
};

#endif // __IDynamicEventTimingMgr__
