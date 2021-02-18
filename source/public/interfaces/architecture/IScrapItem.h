//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IScrapItem.h $
//  
//  Owner: Robin_Briggs
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
//  This is the clipboard interface for all selectable objects. It 
//  supports the generic commands DeleteCmd, PasteCmd, CopyCmd. Each
//  object on the selection list will be requested to return an
//  IScrapItem interface. The interface is used to get a command that
//  can delete, copy, or paste the item.
//  
//========================================================================================

#pragma once
#ifndef __ISCRAPITEM__
#define __ISCRAPITEM__

#include "IPMUnknown.h"
#include "GenericID.h"
#include "PMPoint.h"

class ICommand;
class UIDList;

/**
	This interface is used to get copy/paste/delete command for the items that could be on clipboard. 
*/
class IScrapItem : public IPMUnknown	{
public:
	/**
		Define the default IID for IScrapItem.
	*/
	enum { kDefaultIID = IID_ISCRAPITEM };

	/**
		Get a command that can delete the object.

		@param includeRegisteredItems indicating if we need to get delete command for those registered items too. 
		The default value is kTrue.
		@return ICommand the delete command.
	*/
	virtual ICommand *GetDeleteCmd(bool16 includeRegisteredItems = kTrue) = 0;
		
	/**
		Get a command that can copy the object into the specified area of the destination target(document).
		
		@param cmd refers to the root command, usually it could pass as nil and will be initialized as current copy command.
		@param destinationDB refers to the database of target.
		@param destParent refers to the parent which the item will be copied to such as layer. 
		@param offset refers to the specified area the item will be on. The default value is nil.
		@param includeRegisteredItems refers to if we need to include registered items when do copy operation. The default value is kTrue.
		@return ICommand the copy command.
	*/
	virtual ICommand *GetCopyCmd(ICommand *cmd, IDataBase *destinationDB, UID destParent, PMPoint* offset = nil, bool16 includeRegisteredItems = kTrue) = 0;
		
	/**
		Get a command that can paste the object into the specified area such as active layer, text sub-selection of the destination target(document).
		
		@param cmd refers to the root command, usually it could pass as nil and will be initialized as current copy command.
		@param destinationDB refers to the database of target.
		@param destParent refers to the parent which the item will be copied to such as layer. 
		@param offset refers to the specified area the item will be on. The default value is nil.
		@param includeRegisteredItems refers to if we need to include registered items when do copy operation. The default value is kTrue.
		@return ICommand the paste command.
	*/
	virtual ICommand *GetPasteCmd(ICommand *cmd, IDataBase *destinationDB, UID destParent, PMPoint* offset = nil, bool16 includeRegisteredItems = kTrue) = 0;
		

	/**
		Get a command that is created by iterating over the services registered for pre delete and prepend those commands
		to the delete command.

		@param cmd which seems not been used in current code(dragontail).
		@return ICommand the predelete command. It could be a CompoundSequenceCmd.
	*/
	virtual ICommand *GetPreDeleteCleanupCommands(ICommand *cmd) = 0;
	
	/**
		Get a command that is created by iterating over the services registered for post delete and append those commands
		to the delete command.

		@param cmd which seems not been used in current code(dragontail).
		@return ICommand the predelete command. It could be a CompoundSequenceCmd.
	*/
	virtual ICommand *GetPostDeleteCleanupCommands(ICommand *cmd) = 0;
		

	/**
		Register other scrap items to a scrap item. If you do so the Get***Cmd
		will return a CompoundSequenceCmd that contain the Get***Cmd of all registered scrap items.
		The order of the command collection is: first the registered items then this item.
		
		@param nOtherItem specifies the other item to be registered.
		@return bool16 kTrue if the other item has been successfully registered, otherwise kFalse.
	*/
	virtual	bool16	RegisterScrapItem( UID nOtherItem ) = 0;
		
	/**
		Unregister other scrap items from a scrap item. 
		
		@param nOtherItem specifies the other item to be unregistered.
		@return bool16 kTrue if the other item has been unregistered, otherwise kFalse.
	*/
	virtual	bool16	UnregisterScrapItem( UID nOtherItem ) = 0;	

	/**
		Check whether the other scrap item has been registered or not. 
		
		@param nOtherItem specifies the other item.
		@return bool16 kTrue if the other item has been registered, otherwise kFalse.
	*/
	virtual	bool16	IsRegistered( UID nOtherItem ) const = 0;	
		

	/**
		Check whether any items have been registered or not. 
		
		@return bool16 kTrue if there are items registered, otherwise kFalse.
	*/
	virtual	bool16	HasRegisteredItems() const = 0;	
		

	/**
		Get the item list that has registered.

		@return const UIDList* items that are registered.
	*/
	virtual	const UIDList* GetRegisteredItemsList() const = 0;
};

#endif // __ISCRAPITEM__
