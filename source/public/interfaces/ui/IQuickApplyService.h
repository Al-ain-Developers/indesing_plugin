//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IQuickApplyService.h $
//  
//  Owner: Kevin Van Wiel
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
#ifndef __IQuickApplyService__
#define __IQuickApplyService__

#include <list>

#include "IIdleTask.h" // for IdleTimer include
#include "QuickApplyFindListNode.h"

#include "FindChangeID.h"
#include "IPMUnknown.h"

class IActiveContext;
class IEvent;


/** This class is used to return item type information. An implementation of IQuickApplyService
	is responsible for managing a certain class (type) of item in the quick apply dialog. For example, there
	is an IQuickApplyService provider implementation that handles character styles. When the method GetItemTypesHandled()
	is called it returns this record filled out that tells the quick apply dialog what it's character
	style items look like in the dialog display list so that the core dialog can know which service provider to ask to handle
	the apply action when the item is selected in the dialog later (and for other reasons). A service provider is 
	allowed to handle more than one type of item so the routine GetItemTypesHandled() returns a list.
	@author Kevin Van Wiel
*/
class QuickApplyItemRecord
{
public:
	/** Tells the dialog what name to use for this type item in any quick apply dialog ui. */
	PMString fItemUIName;
	
	/** Tells the dialog the prefix key the user can type to limit the list to only items of this type. Must be unique see GetItemTypesHandled() for how to determine uniqueness. */
	PMString fPrefixKeyString;
	
	/** A unique id that can be used to identify this type item. Define via action id definitions see GetItemTypesHandled() */
	uint32 fItemID;
	
	/** Set to true if the type item referenced in this class should be shown in the quick apply dialog. When a service provider is called via GetItemTypesHandled() it should fill in the items default value for this. */
	bool16 fActive;
};

/** Definition for a list of item types. Each entry is a pair type UI name and an item id. */
typedef std::list<QuickApplyItemRecord>  TypesHandledList;

/** Definition for a list of id types */
typedef std::list<uint32> TypesIDList;


/** An interface used to provide items to the quick apply dialog. Parties who want
	to add new types of items to the quick apply dialog are expected to make an
	service provider with their item described via this interface.
	@author Kevin Van Wiel
*/
class IQuickApplyService : public IPMUnknown
{
public:
	/** Standard enum to for use with GetDefaultIID() method.
	*/
	enum { kDefaultIID = IID_IQUICKAPPLYSERVICE };
	
	/**
		This is called just after the quick apply dialog opens to give the service provider a chance to initialize 
		any activity it needs to.
		@param allocator class to allocate id types for the service provider. 
		@return none
	*/
	virtual void BeginServiceSession() = 0;
	
	/**
		This is called just before the quick apply dialog closes to give the service provider a chance to clean up any data 
		storage it has allocated.
		@return none
	*/
	virtual void EndServiceSession() = 0;
	
	/**
		When this routine is called the service provider should return a list of the types of items it is responsible for.
		@param existingItemTypes A list of types already known up to the point when this routine is called. You may not return a prefix key that is already existing. Use this to make sure new prefix keys are unique.
		@return TypesHandledList which is a list of pairs. The elements are the UI name of the type(s) handled and it's cooresponding id which must be unique. It's recommended to achieve
		uniqueness that the id be defined via a widgetid for example DECLARE_PMID(kActionIDSpace, kQuickApplyCharacterStylesPrefActionID, kFindChangePrefix + 253) is how the service provider actions defines
		it's QuickApplyItemRecord.fItemID data type.
	*/	
	virtual TypesHandledList GetItemTypesHandled(const TypesHandledList &existingItemTypes) = 0;

	/**
		The implementor of this routine should append a list of items to be displayed in quick apply dialog
		through the masterList parameter. Note Items may already be present in the master list don't delete
		existing items!
		@param ac the active context for the application (useful to determine what items should be loaded).
		@param masterList this is a return parameter this routine will append new items (if any) to the end of this list.
		@param timeCheck if timecheck is not nil then an implementation of this method should save it's state a return when this timeCheck reaches 0.
		@param itemTypeToLoad the type of items to load.
		@return none;
	*/
	virtual void LoadItems(IActiveContext *ac, K2Vector<QuickApplyFindListNode> *masterList, IdleTimer *timeCheck, uint32 itemTypeToLoad) = 0;
	
	/**
		Each provider is expected to know whether it has completed loading of it's items or not. This is to support the partial
		loading of sort items for those that may take extended times to load. The LoadItems() routine may be called multiple times
		(called via an idle task) and during each one those some (or all) items will be loaded in the quick apply dialog. This let's the
		dialog open instantly although the loading of all items may take some short amount of time to all load after that. The user
		can start typing immediatly and by the time he finishes (or sooner) typically all items will be loaded. Providing a smooth
		studder free experience. At BeginServiceSession() time you should clear whatever flag(s) are used to indicate whether the
		LoadItemsIsComplete() then set them as necessary after LoadItems() is called.
		@return none
	*/
	virtual bool16 LoadItemsIsComplete(uint32 idType) = 0;
	
	/**
		When the user selects an item from the quick apply dialog and does the apply action this routine will
		be called. If the item passed in is one that your implementation owns then it should do it's apply action
		for that item.
		@param ac active context to apply item into.
		@param itemToApply item in the quick apply dialog that was selected when apply was selected.
		@param e (may be nil) an event which can be used to determine any special types of apply that may happen. For example, if the option key is held down paragraph styles will apply differently than if no modifiers are active.
		@param edit open up an edit dialog rather than apply where applicable (i.e. styles).
		@return kTrue if the itemToApply was of a type that the routine handled.
	*/
	virtual bool16 ApplyItem(IActiveContext *ac, const QuickApplyFindListNode &itemToApply, IEvent *e, bool16 edit) = 0;
	
	/**
		The dialog can at certain infrequent times ask a service provider to reset. What this means is the that the service implimentor
		should prepare itself to have the LoadItems() routine called again like it does when the dialog opens. Typically this would
		be called in the case of a item type being activated/deactivated.
		@return none
	*/
	virtual void ResetProvider() = 0;
};


#endif // __IQuickApplyService__
