//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IAppearanceItemFacade.h $
//  
//  Owner: Mitch Coleman
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
#ifndef __IAppearanceItemFacade__ 
#define __IAppearanceItemFacade__

#include "IPMUnknown.h"
#include "IAppearanceList.h"
#include "INewStateCmdData.h"

#include "FormFieldTypes.h"
#include "FormFieldID.h"

namespace Facade 
{
	class IAppearanceItemFacade : public IPMUnknown
	{ 
	public: 

		enum { kDefaultIID = IID_IAPPEARANCEITEMFACADE };

		enum CopyItemsFlag { 
			kCopyItems		= kTrue, 
			kDoNotCopyItems = kFalse 
		};

		enum { kInvalidIndex = -1 };

		/** Creates a new appearance item of the specified class.
			Appearance items are created from already-existing
			page items. The page items that are passed into this method
			are used to define the how states of the appearance item look.
			If inAppearanceItemClass is kPushButtonItemBoss, then each of the
			items created will be individual buttons; if kMultiStateObjectItemBoss,
			then each of the items will be used to create individual states of a
			single Multi-State Object.
			@param inItems the page items to use to create the appearance item(s)
			@param inAppearanceItemClass the class of the desired page item: 
					either kMultiStateObjectItemBoss or kPushButtonItemBoss.
			@param outAppearanceItem a UIDList of the items that were created
			@return ErrorCode
		*/
		virtual ErrorCode CreateAppearanceItem (
			const UIDList& inItems,
			const ClassID& inAppearanceItemClass,
			UIDList* outAppearanceItems = nil
			) const = 0;

		/** Creates a new state on a page item that supports states.
			@param inItems the item(s) to create the new state on
			@param inState the AppearanceState to create on the items
			@param inPosition the position in the ordering of states to create the state at
			@param inCopyItems whether to page items into the new state. 
							   for buttons, these come from the normal state.
							   for multi-state objects, these come from the active state
			@param inNamePolicy the policy to use for assigning a name to the state
			@param inNameString if inNamePolicy is set to kBaseNameOnString, then this 
								parameter is used as the string to base the name on
			@return ErrorCode
		*/
		virtual ErrorCode CreateNewState(
		   const UIDList& inItems,
		   Form::AppearanceState inState,
		   int32 inPosition = IAppearanceList::kLastInOrder,
		   CopyItemsFlag inCopyItems = kCopyItems,
		   INewStateCmdData::NamePolicy inNamePolicy = INewStateCmdData::kUseDefaultName,
		   const PMString* inNameString = nil
		   ) const = 0;

		/** Move a state to a new position in the state ordering on its parent page item. 
			Can be used on multiple page items, simultaneously.
			@param inAppearanceItems the page items whose states to move
			@param inState the state to move
			@param inPosition the new position for the state
			@return ErrorCode
		*/
		virtual ErrorCode MoveState (
			const UIDList& inAppearanceItems,
			Form::AppearanceState inState,
			int32 inPosition
			) const = 0;

		/** Deletes a state on one or more page items.
			@param inAppearanceItems the page items whose states to delete
			@param inState the state to delete on the items
			@return ErrorCode
		*/
		virtual ErrorCode DeleteState(
			const UIDList& inAppearanceItems, 
			Form::AppearanceState inState
			) const = 0;

		/** Deletes a contents of a state on one or more page items. 
			@param inAppearanceItems the page items whose states to delete
			@param inState the state to delete on the items
			@return ErrorCode
		*/
		virtual ErrorCode DeleteAppearance(
			const UIDList& inAppearanceItems, 
			Form::AppearanceState inState
			) const = 0;

		/** Changes the active state of one or more appearance items.
			@param inAppearanceItems the appearance items to change
			@param inState the new state to set as active
			@return ErrorCode
		*/
		virtual ErrorCode SetActiveState(
			const UIDList& inAppearanceItems, 
			Form::AppearanceState inState
			) const = 0;

		/** Move a state to a new position in the state ordering on its parent page item. 
			Can be used on multiple page items, simultaneously.
			@param inAppearanceItems the page items whose states to move
			@param inState the state to move
			@param inPosition the new position for the state
			@return ErrorCode
		*/

		virtual ErrorCode AddItemsToAppearance(
			const UIDRef& inAppearanceItem, 
			const UIDList& inItemsToAdd, 
			Form::AppearanceState inState
			) const = 0;

		/** Create a new state on an appearance item, and add page items to that state's appearance.
			@param inAppearanceItem the appearance item to which a state is being added
			@param inItemsToAdd the page items to add to the state's appearance
			@param inState  the new state to be created
			@return ErrorCode
		*/

		virtual ErrorCode AddItemsAsState( 
			const UIDRef& inAppearanceItem, 
			const UIDList& inItemsToAdd,
			Form::AppearanceState inState
			) const = 0;

		/** Add page items to new states on an appearance item. Each page item in inItemsToAdd
			will be placed into its own new state on inAppearanceItem.
			@param inAppearanceItem the appearance item to which a states are being added
			@param inItemsToAdd the page items to add as states
			@return ErrorCode
		*/
		virtual ErrorCode AddItemsAsStates( 
			const UIDRef& inAppearanceItem, 
			const UIDList& inItemsToAdd 
			) const = 0;

		/** Deletes a state and places the objects that made up that state's appearance onto the spread.
			@param inAppearanceItem the appearance item whose state is to be released
			@param inState the state to release to the spread
			@return ErrorCode
		*/
		virtual ErrorCode ReleaseAppearanceAsObject( 
			const UIDList& inAppearanceItems,
			Form::AppearanceState inState 
			) const = 0;

		/** Deletes the appearance item and places all of the objects that made up
			the appearances of that item's states onto the spread.
			@param inAppearanceItem the appearance item whose state is to be released
			@param inState the state to release to the spread
			@return ErrorCode
		*/
		virtual ErrorCode ReleaseAllAppearancesAsObjects( 
			const UIDList& inAppearanceItems
			) const = 0;

		/** Gets the currently active state of the appearance item.
			@param inAppearanceItem the appearance item in question
			@return the active state of inAppearanceItem
		*/
		virtual Form::AppearanceState GetActiveState(
			const UIDRef& inAppearanceItem
			) const = 0;

		/** Gets the nth state of the appearance item.
			@param inAppearanceItem the appearance item in question
			@param inStateIndex the index of the state to be retrieved
			@return the nth state of inAppearanceItem
		*/
		virtual Form::AppearanceState GetNthState(
			const UIDRef& inAppearanceItem,
			int32 inStateIndex 
			) const = 0;

		/** Gets next valid state that can be added to the page item.
			@param inAppearanceItem the appearance item in question
			@return if one the appearance item has valid states available, 
					then the next valid state; otherwise kStateInvalid
		*/
		virtual Form::AppearanceState GetNextAvailableState(
			const UIDRef& inAppearanceItem
			) const = 0;

		/** Sets the name of a state on an appearance item.
			@param inAppearanceItem the appearance item that owns the state
			@param inState the state whose name to modify
			@param inName the new name for the state
			@return ErrorCode
		*/
		virtual ErrorCode SetStateName(
			const UIDRef& inAppearanceItem, 
			Form::AppearanceState inState, 
			const PMString& inName
			) const = 0;

		/** Gets the name of a state on an appearance item.
			@param inAppearanceItem the appearance item that owns the state
			@param inState the state whose name to get
			@return the name of the state, if it exists; otherwise an empty string
		*/
		virtual PMString GetStateName(
			const UIDRef& inAppearanceItem,
			Form::AppearanceState inState
			) const = 0;

		/** Gets the number of states that an appearance item has.
			@param inAppearanceItem the appearance item in question
			@return the number of states that inAppearanceItem has
		*/
		virtual int32 GetNumStates(
			const UIDRef& inAppearanceItem
			) const = 0;

		/** Gets the the position of a state in an appearance item's state ordering.
			@param inAppearanceItem the appearance item in question
			@param inState the state whose position to get
			@return the index of the state in the state ordering, or kInvalidIndex
		*/
		virtual int32 GetStatePosition(
			const UIDRef& inAppearanceItem, 
			Form::AppearanceState inState
			) const = 0;

		/** Determines if an appearance item has a specific state defined.
			@param inAppearanceItem the appearance item in question
			@param inState the state in question
			@return whether inAppearanceItem has a state identified by inState
		*/
		virtual bool16 HasState(  
			const UIDRef& inAppearanceItem, 
			Form::AppearanceState inState 
			) const = 0;

		/** Determines if a state is both supported and not already created.
			@param inAppearanceItem the appearance item in question
			@param inState the state in question
			@return whether inState can be added to inAppearanceItem
		*/
		virtual bool16 CanAddState(  
			const UIDRef& inAppearanceItem,
			Form::AppearanceState inState
			) const = 0;

		/** Paste the currently copied item(s) into the specified state of the specified appearance item
			@param inAppearanceItem the appearance item to paste into
			@param inState the state to paste into
			@param outPastedItems an optional list to fill with the UIDs of the newly pasted items
			@return ErrorCode
		*/
		virtual ErrorCode PasteIntoState(
		   const UIDRef& inAppearanceItem, 
		   Form::AppearanceState inState,
		   UIDList* outPastedItems = nil
		   ) const = 0;

		/** Gets whether a appearance item is hidden when exported to SWF/PDF.
			@param inItem the appearance item
			@return whether this item is hidden when exported to SWF
		*/
		virtual bool16 GetIsInitiallyHidden(
		   const UIDRef& inItem
		   ) const = 0;

		/** Sets whether an appearance item is hidden when exported to SWF/PDF.
			@param inItem the appearance item
			@param inHidden whether or not this object should be hidden
			@return ErrrorCode
		*/
		virtual ErrorCode SetIsInitiallyHidden(
		   const UIDRef& inItem,			
		   bool16 inHidden
		   ) const = 0;

	};

};


#endif // __IAppearanceItemFacade
