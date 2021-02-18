//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ICommandSequence.h $
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
//  Reviewed: 	10/5/98
//  
//========================================================================================

#pragma once
#ifndef __ICOMMANDSEQUENCE__
#define __ICOMMANDSEQUENCE__
#include "K2SmartPtr.h"
class PMString;

struct Opaque_SequenceMarkInfo
{
	virtual ~Opaque_SequenceMarkInfo(){};
	virtual bool IsValid() const = 0;
};

typedef boost::shared_ptr<Opaque_SequenceMarkInfo> SequenceMark;

/**	Abstract base class for command sequences.

	The type of command sequence that meets most needs is ICommandSequence. 
	If you need more sophisticated error handling and retry behaviour within your
	sequence consider using IAbortableCmdSeq.

	THIS IS NOT A STANDARD BOSS CLASS INTERFACE; that is, it doesn't support
	the IPMUnknown protocol and can't be wrapped in an InterfacePtr.

	@ingroup arch_cmd
*/
class I_Base_CommandSequence INHERITFROM	// regular c++ class - not a K2 boss
{	
	public:	
		/** Returns the undoability of this command sequence
			@return the undoability of this command sequence
			@see ICommand
		*/
		virtual ICommand::Undoability GetUndoability() const = 0;

		/** Set the undoability of this command sequence
			@param newUndoability the undoability of this command sequence
			@see ICommand
		*/
		virtual void SetUndoability(ICommand::Undoability newUndoability) = 0;
	
		/** Gets the name of this command sequence
			@param name returned as the name to show in the undo/redo menu items.
			@see ICommand
		*/
		virtual void GetName(PMString *name) const = 0;

		/** Set the name of this command sequence
			@param newName the name to show in the undo/redo menu items.
			@see ICommand
		*/
		virtual void SetName(const PMString& newName) = 0;

		/** Increase the ref count on this command sequence by one. 
		*/
		virtual void AddReference() = 0;

		/** Decrease the ref count on this command sequence by one. 
		*/
		virtual void ReleaseReference() = 0;
		
		/** For internal use only*/
		
		virtual const char* GetTrackingData() = 0;

};

/** A regular command sequence groups any number of commands to a single undoable 
	step in the command history. When the sequence ends, the changes made by 
	the commands within the sequence are committed if the global error code is 
	kSuccess, otherwise the database is rolled back to its state before the 
	sequence started.

	Stack-based helper classes CmdUtils::SequencePtr and CmdUtils::SequenceContext
	make it easier to write a sequence and avoid having to call
	CmdUtils::BeginCommandSequence() and CmdUtils::EndCommandSequence(ICommandSequence *)
	yourself. For example:
	<pre>
	{
		// The SequencePtr constructor creates a new sequence.
		SequencePtr seq;
		seq->SetName(PMString("Your Sequence Name"));
		if (ProcessFirstCommand() == kSuccess))
		{
			ProcessSecondCommand();
		}
		// When the SequencePtr object goes out of scope the destructor ends the sequence.
	}
	</pre>

	Alternatively call CmdUtils::BeginCommandSequence() to create a new
	sequence. After you are done with processing commands 
	call CmdUtils::EndCommandSequence(ICommandSequence *). 
	Do not use the sequence again afterwards.

	@see CmdUtils::SequenceContext
	@see CmdUtils::SequencePtr
	@see CmdUtils::BeginCommandSequence
	@see CmdUtils::EndCommandSequence(ICommandSequence *)
	@see ErrorUtils::PMGetGlobalErrorCode
	@see ICmdHistory
	@see ICommand
	@see CmdUtils
	@ingroup arch_cmd
*/
class ICommandSequence : public I_Base_CommandSequence
{	
};

/**	An abortable command sequence groups any number of commands to a single undoable 
	step in the command history. The sequence can be aborted by client code and can 
	have sequence marks that allow the client code to roll back to designated points 
	when failure occurs. This allows client code to implement sophisticated error
	handling and retry strategies within a sequence. Abortable command sequences 
	should only be used where absolutely necessary since they incur a heavy performance 
	overhead. For example, when refreshing links you might find that a linked file is missing
	and allow the user to browse for the missing link and then proceed. This kind of
	error handling needs and abortable command sequence. 
	
	Regular command sequences (ICommandSequence) cannot do this kind of error handling.
	Their changes are committed or rolled back dependent on the global error code status 
	when the sequence ends.

	Call CmdUtils::BeginAbortableCmdSeq() to create a new abortable
	sequence. After you are done with processing commands call 
	CmdUtils::EndAbortableCmdSeq(IAbortableCmdSeq *)
	to end your sequence on success, or CmdUtils::AbortCommandSequence(IAbortableCmdSeq *)
	to abort the sequence. 	Do not use the sequence again afterwards.

	@see CmdUtils::BeginAbortableCmdSeq
	@see CmdUtils::SetSequenceMark
	@see CmdUtils::RollBackCommandSequence
	@see CmdUtils::EndCommandSequence(IAbortableCmdSeq *)
	@see ErrorUtils::PMGetGlobalErrorCode
	@see ICmdHistory
	@see ICommand
	@see CmdUtils
	@ingroup arch_cmd
*/
class IAbortableCmdSeq : public I_Base_CommandSequence	// regular c++ class - not a K2 boss
{
};

/** An auto undo sequence wraps a set of changes targeted to a database and implements undo behavior 
	identical to that of a command that has kAutoUndo undoability.

	Use an auto undo sequence when your changes can never appear in an individual step
	on the undo menu (i.e. your changes always tag along with other changes that do appear on the 
	undo menu).

	To wrap a set of changes in an auto undo sequence use CmdUtils::BeginAutoUndoSequence to create 
	the sequence before the changes are started and CmdUtils::EndAutoUndoSequence to end the sequence
	after the changes are done. You must provide a database target when creating the autoundo sequence.

	@see CmdUtils::AutoUndoSequencePtr helper class for wrapping an auto undo sequence.
*/
class IAutoUndoSequence
{
	public:
		/** For internal use only*/
		virtual const char* GetTrackingData() = 0;
};


#endif // __ICOMMANDSEQUENCE__