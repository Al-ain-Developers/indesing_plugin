//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/IActionStateList.h $
//  
//  Owner: lance bushore
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
//  This interface is used for action components to update the state of their actions.
//  It is NOT a standard boss interface - it does not inherit from IPMUnknown!
//  
//========================================================================================

#pragma once
#ifndef __IActionStateList__
#define __IActionStateList__

/** kDisabled_Unselected indicates the action is not doable, and not selected */
const int16 kDisabled_Unselected 	=	0;

/** kEnabledAction indicates the action is doable */
const int16 kEnabledAction			=	1;

/** kSelectedAction indicates the action is selected(checked for menus) */
const int16 kSelectedAction			=	2;	

/** kMultiSelectedAction indicates the action is mutiple-selected(dashed(multi-checked) for menus) */
const int16 kMultiSelectedAction	=	4;

/** kAltSelectedAction indicates the action is alternate-selected(underline for menus) */
const int16 kAltSelectedAction		=	8;

/** Class used to pass/update state of multiple actions at once.
*/
class IActionStateList INHERITFROM 
{
	public:
		virtual ~IActionStateList(){}
		
		/**  Get the count of actions in this list
			@return count
		*/
		virtual int32 Length() const = 0;
		
		/**  Get the nth action from this list
			@param index which action
			@return nth ActionID
		*/		
		virtual ActionID GetNthAction(int32 index) const = 0;

		/**  Set the enable/selected state for the nth action in this list. Enable state for all actions defaults to kDisabled_Unselected
			@param index which action
			@param state new state for this action. Some combination of kDisabled_Unselected,kEnabledAction,kSelectedAction,kMultiSelectedAction,kAltSelectedAction
		*/		
		virtual void SetNthActionState(int32 index, int16 state) = 0;
		/**  Get the enable/selected state for the nth action in this list
			@param index which action
			@return state for this action. Some combination of kDisabled_Unselected,kEnabledAction,kSelectedAction,kMultiSelectedAction,kAltSelectedAction
		*/		
		virtual int16 GetNthActionState(int32 index) const = 0;

		/**  Set the name for the nth action in this list. This only needs to be done if the name of the action is changing.
			@param index which action
			@param name new name for this action. Typically used to dynamically change the name of a menu item that does different things based on some state.
		*/		
		virtual void SetNthActionName(int32 index, const PMString& name) = 0;
		/**  Get the name for the nth action in this list
			@param index which action
			@return name for this action. 
		*/		
		virtual const PMString& GetNthActionName(int32 index) const = 0;
};

#endif // __IActionStateList__