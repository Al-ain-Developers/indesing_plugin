//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ICommand.h $
//  
//  Owner: Roey Horns
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
//  Reviewed:	10/06/98
//  
//========================================================================================

#pragma once
#ifndef __ICOMMAND__
#define __ICOMMAND__

#include "IPMUnknown.h"
#include "CommandID.h"

class PMString;
class UIDList;

/** Design pattern documentation defines the intent of a command as "Encapsulate a request as an object, thereby 
	letting you parameterize clients with different requests, queue or log requests, and support undoable operations";
	within InDesign, commands are used to modify objects that persist in an InDesign database that 
	supports undo. A command can only change data in one database.
	
	Commands are created and processed using the utility CmdUtils. Parameters are passed in and out of the command via:
	<ul>
	<li>data interfaces on the command.
	<li>the item list. Most commands expect the objects to be operated on
		and the InDesign database that contains these objects to be passed via the item list. Some commands 
		are however self targetting and either work on objects from one well known database, or, 
		a database that is passed using a data interface on the command. See ICommand::GetItemList.
	</ul>

	@see CmdUtils::CreateCommand
	@see CmdUtils::ProcessCommand
	@see CmdUtils::ScheduleCommand
	@see CmdUtils
	@see Command the base class used by command implementations; if you add objects that persist in 
		an InDesign database that supports undoable operations you must also add commands that modify 
		these objects.
	@see ICommandMgr
	@see IDataBase
	@ingroup arch_cmd
	@ingroup arch_db
*/
class ICommand : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICOMMAND };

	//====================================================================================
	// methods and typedefs for clients and implementors of commands
	//====================================================================================

	/** Get the name of the command;
		commands with the undoability kRegularUndo must have a name, for use in the undo/redo menu items
		(unless they override IsNameRequired to return kFalse).
		@param name a pointer to the name for the command.
	*/
	virtual void GetName(PMString *name) const = 0;

	/** Set the name of the command.
		@param newName the new name for the command.
	*/
	virtual void SetName(const PMString& newName) = 0;
	
	/** Is command required to have a name?
            By default, the return value is kTrue when undoability 
	    is equal kRegularUndo and kFalse otherwise.
	    Override this virtual function when you have a command with regular undo and 
	    you want to use the name of another command (nested within the scope of 
	    the current one) to appear on the undo menu.
	*/
	virtual bool16 IsNameRequired() const = 0;

	/** Get the a pointer to the item list; the item list references the objects (by UID) the command should work on and 
		the target database (IDataBase) that contains them. If the target to be worked on is not passed to the command
		via this item list then the command must be self targetting (see Command::SetTarget, Command::SetUpTarget).
		@return pointer to a UIDList
	*/
	virtual const UIDList* GetItemList() const = 0;

	/** Get a reference to the item list.
		@return reference to a UIDList
		@see ICommand::GetItemList
	*/
	virtual const UIDList& GetItemListReference() const = 0;

	/** Set the item list.
		@param newItemList reference to item list to be copied into command
		@see ICommand::GetItemList
	*/
	virtual void SetItemList(const UIDList &newItemList) = 0;
	
	/**	Command states.
		The command state tells observers in what execution state the command currently is.
		It is also used by the command processor in order to figure out
		in what way cascading commands relate to each other.
	*/
	typedef enum 
		{
		/** before or while the command is done */
		kNotDone,
		/** during dynamic execution */
		kDoneDynamic,	
		/** after the command is done */
		kDone	
	} CommandState;
	

	/**	Returns the command state; observers (see IObserver::Update) can check this state
		is not yet done (pre-notification) or done.
		@return the command state 
	 */
	virtual CommandState GetCommandState() const = 0;

	/**	Returns kTrue if the command state is kDone or kDoneDynamic, kFalse otherwise.
		@return kTrue if the command state is kDone or kDoneDynamic, kFalse otherwise. 
		@see ICommand::GetCommandState
	 */
	virtual bool16 IsDone() const = 0;
	
	/** Undoability of a command.
		The undoability of a command specifies if it is meant to be a single 
		undo step of it's own (kRegularUndo) or if it needs to be 
		undone/redone with the previous/next undo step (kAutoUndo case).
		*/

	typedef enum
	{
		/** The command does not show up in undo / redo menu items, 
			it is always undone / redone with some other step.
		*/
		kAutoUndo = 0,

		/** Default: The command shows up in undo /redo menu items
		    in its own distinct step (if it is not part of a sequence).
		*/
		kRegularUndo,		

	} Undoability;
	
	/** Returns the undoability of the command.
		@return undoability value
	*/
	virtual Undoability GetUndoability() const = 0;
	
	/** Set the undoability of the command.
		This function allows changing the undoability of a command.
		Typically, SetUndoability is called to override the default undoability. 
		Call this function before the Do() function of the command gets called 
		(we recommend setting the undoability within the constructor of the command 
		interface or within the  implementation of the SetupTarget function).

		@param newUndoability the new undoability value for the command
	*/
	virtual void SetUndoability(Undoability newUndoability) = 0;
		
	/** Unique creator ID.
	*/
	enum {
		/** A magic value that isn't even considered equal to itself */
		kUniqueCreatorID = ~(int32)0,
		/** Special value for a command that is passed through a previewable dialog independent of preview state. 
			WARNING: Should only be used for commands that don't modify persistent data. */
		kPassthroughCreatorID = ~(int32)1 
	}; 
	/** Set the creator ID.
		The creator id is important in the context of a previewable dialog. The dialog
		command interceptor uses it to tell whether two commands are the same.
		@param creatorID the new creator ID to use
	*/
	virtual void SetCreatorID(int32 creatorID) = 0;

	/** Get the creator ID
		@return the creator ID of the command
	*/
	virtual int32 GetCreatorID() const = 0;
	
	/** Command priority.
		Scheduled cmds are processed acording to their priority.
		Cmds with kHighPriority, kHighestPriority are processed at the next possible moment when the
		cmdprocessor has finished all currently processed commands	
	*/
	enum Priority { 
		/** lowest */	kLowestPriority, 
		/** low */		kLowPriority, 
		/**	medium */	kMediumPriority, 
		/** high */		kHighPriority, 
		/** highest */	kHighestPriority };
	
	//====================================================================================
	// methods and typedefs for implementors of commands only
	// (see also the base class Command.h)
	//====================================================================================

	/** Join a command to this command.
		Should return true if the command was able to join the new command pNewCmd.
		@param pNewCmd the command to join with.
		@return kTrue if successful
	*/
	virtual bool16 CanJoin( const ICommand *pNewCmd ) const= 0;
	
	/** Tell whether a command can operate under low memory conditions.
		@return kTrue if the command is able to execute under low memory conditions.
	*/
	virtual bool16 LowMemIsOK() const = 0;
	
	//====================================================================================
	// for internal use only
	//======================================n=============================================
	// Not exposing these to Doc++ since they're for internal use only 
	//====================================================================================
	typedef UIDRef Target;
	
	virtual const Target &GetTarget() const = 0;
 	virtual void DoImmediate(bool16 isDynamic = kFalse) = 0;
 	virtual void LWDoImmediate() = 0;
	virtual void SetActive(bool16 isActive) = 0;
	virtual bool16 IsActive() const = 0;
	virtual bool8 IsLWProcessed() const = 0;
};

#endif 	// __ICOMMAND__

