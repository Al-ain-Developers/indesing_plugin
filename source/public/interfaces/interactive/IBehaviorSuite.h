//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IBehaviorSuite.h $
//  
//  Owner: Michael Brubidge
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
#ifndef __IBehaviorSuite_h__
#define __IBehaviorSuite_h__

#include "IPMUnknown.h"
#include "BehaviorID.h"
#include "BehaviorTypes.h"
#include <vector>

class IBehaviorData;
class IBehaviorEvent;

/** Selection suite for manipulating behaviors on selections that can have behaviors
	(e.g. Form Fields)
	
	This suite also doesn't operate on multiple selections.
	
	@see IBehaviorList
*/
class IBehaviorSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IBEHAVIORSUITE };
	
	/** @return kTrue if the selection can have attached behaviors, i.e. everything has a IBehaviorList
	*/
	virtual bool16 					CanApplyActions() const = 0;

	/** @return kTrue if the selection supports inEvent.  For example, if inEvent is format, and the selection is a form
				field, this would return kTrue for text fields, but kFalse for push button fields.
	*/
	virtual bool16 					IsEventSupported(IBehaviorEvent* inEvent) const = 0;

	/** Tests whether the action can be moved to the new event and new position. Actions that can have 
		targets appear in the action list before actions that do not have targets and they cannot be mixed. 
		
		@param actionToMove UID for action to be moved
		@param newEvent The new event of the action
		@param newPosition The new position within the event of the action.
		@return kTrue if it can be moved or kFalse
	*/
	virtual bool16					CanMoveAction(const UID& actionToMove, const ActionEvent& newEvent, int32 newPosition) = 0;
	
	/** Get a list of actions for a particular event
		@param forEvent Event to examine
		@param db, on exit, the Database of the actions
		@param actions, on exit, a lists of action UIDs that are executed for forEvent
	*/
	virtual void					GetActions(const ActionEvent& forEvent, IDataBase*& db, std::vector<UID>& actions) const = 0;

	/** Get a list of all actions for all events
		@param db, on exit, the Database of the actions
		@param actions, on exit, a lists of action UID/event pairs
	*/
	virtual void					GetEventAndActions(IDataBase*& db, std::vector< std::pair<ActionEvent, UID> >& actions) const = 0;
	
	/** Add an action to an event.
		@param forEvent The event for which the action is to be executed
		@param actionData IBehaviorData interface on action boss to be added.
		@return The result of command execution
	*/
	virtual ErrorCode				AddAction(const ActionEvent& forEvent, IBehaviorData* actionData, UID& newAction) = 0;

	/** Replace one action with another.
		@param forEvent The event for which the action is to be executed
		@param actionToReplace UID for action to be replaced
		@param actionData IBehaviorData interface on the new action
		@return The result of command execution
	*/
	virtual ErrorCode				ReplaceAction(const ActionEvent& forEvent, const UID& actionToReplace, IBehaviorData* actionData) = 0;

	/** Duplicate an action
		@param forEvent The event for which the action is to be executed
		@param actionToDuplicate UID for action to be duplicated
		@return The result of command execution
	*/
	virtual ErrorCode				DuplicateAction(const ActionEvent& forEvent, const UID& actionToDuplicate, UID& newAction) = 0;

	/** Delete an action
		@param actionToDelete UID for action to be deleted
		@return The result of command execution
	*/
	virtual ErrorCode				DeleteAction(const UID& actionToDelete) = 0;

	/** Move an action, either reordering it within its owning event or moving it to
		another event.
		
		@param actionToMove UID for action to be moved
		@param newEvent The new event of the action
		@param newPosition The new position within the event of the action.
		@return The result of command execution
	*/
	virtual ErrorCode				MoveAction(const UID& actionToMove, const ActionEvent& newEvent, int32 newPosition) = 0;

	/** Enable or disable an action for PDF export.  If disabled, the action will show up the behavior UI without a
		checkbox, and will not be exported to the PDF file.
		
		@param actionToEnable UID for action to be enabled or disabled
		@param enable If kTrue, enabled the action, else, disable it
		@return The result of command execution
	*/
	virtual ErrorCode				EnableAction(const UID& actionToEnable, const bool16& enable = kTrue) = 0;

	/** Remove all actions for all events.
		@return The result of command execution
	*/
	virtual ErrorCode				DeleteAllActions() = 0;
};

#endif // __IBehaviorSuite_h__
