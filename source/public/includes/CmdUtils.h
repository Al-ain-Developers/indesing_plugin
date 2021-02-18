//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CmdUtils.h $
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
//========================================================================================

#pragma once
#ifndef __CMDUTILS__
#define __CMDUTILS__

// these really shouldn't be here - but a lot of files rely on them (- Roey)
#include "ISession.h"
#include "CreateObject.h"


#include "PMTypes.h" 
#include "CommandID.h"
#include "ICommand.h"
#include "ICommandSequence.h"
#include "ICommandProcessor.h"


#include "CmdUtilsMacros.h"

#pragma export on


/** Utilities for creating and processing commands (see ICommand).

	@ingroup arch_cmd
	@ingroup arch_db

	@see ICommand
	@see ICommandSequence
	@see IAbortableCmdSeq
	@see ErrorUtils
	@see IDataBase
*/
class PUBLIC_DECL CmdUtils {
public:
	// -----------------------------------------
	// command creation
	// -----------------------------------------
	
	/** Create a command of the given class.
		@param cmdType identifies the command to be created.
		@return command on success, nil otherwise.
	*/
	static ICommand *CreateCommand(ClassID cmdType);
	
	// -----------------------------------------
	// command execution
	// -----------------------------------------
	
	/** Process a command using regular cmd processing, the default method for cmd execution;
		remember to check the ErrorCode returned by this call, if you continue to process commands
		while the global error code is set then protective shutdown will occur.
		@param cmd the command to be processed.
		@return kSuccess on success, other ErrorCode otherwise.
		@see ErrorUtils::PMGetGlobalErrorCode
	*/
	static ErrorCode ProcessCommand(ICommand *cmd);
	
	/** Schedule a command to be processed later (depending on their priority) 
		@param cmd the command to be processed.
		@param priority at which the scheduled command should be processed.
		@return kSuccess if the command is scheduled for processing, other ErrorCode otherwise.
	*/
	static ErrorCode ScheduleCommand(ICommand *cmd, ICommand::Priority priority = ICommand::kLowPriority);

	/** DEPRICATED
		Avoid using this function if possible - this is legacy and is deprecated.
		
		Execute a dynamic command
		@param cmd the command to be processed.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	static ErrorCode ExecuteDynamicCommand(ICommand *cmd);
	/** DEPRICATED
		Avoid using this function if possible - this is legacy and is deprecated.

		Execute a dynamic command
		@param cmd the command to be processed.
		@param isActive - pass kFalse to get notification only from the command, eg. when a tracker is in wireframe mode
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	static ErrorCode ExecuteDynamicCommand(ICommand *cmd, bool16 isActive);
	
	/** Flush the command queue, processing scheduled commands
		@param downToPriority controls the priority level that commands are processed down to.  Commands with this priority and higher will be processed.
		@return kTrue if all scheduled commands in the command queue could be processed down to the priority specified without any errors, or kFalse otherwise
	*/
	static bool16 ProcessScheduledCmds(ICommand::Priority downToPriority = ICommand::kLowestPriority);
	
	// -----------------------------------------
	// command sequences
	// -----------------------------------------

	/** Begin a regular command sequence; see ICommandSequence for documentation.
		@param trackingData : string identifier of the caller. This is to help track if any command sequence was lost without EndCommandSequence
		@return the command sequence or nil on error
		@post call CmdUtils::EndCommandSequence(ICommandSequence*) to terminate the sequence.
		@see CmdUtils::SequenceContext and CmdUtils::SequencePtr helper classes
	*/
	static ICommandSequence *BeginCommandSequence(const char* trackingData = nullptr);

	/** End a regular command sequence;
		@param sequence to be ended
		@return kSuccess if the sequence ended successfully, other ErrorCode otherwise.
		@see ErrorUtils::PMGetGlobalErrorCode
	*/
	static ErrorCode EndCommandSequence(ICommandSequence *sequence);
		
	/** Begin an abortable command sequence; see IAbortableCmdSeq for documentation
		(if you are unsure which type of command sequence you need, use ICommandSequence
		rather than IAbortableCmdSeq).
		@param trackingData : string identifier of the caller. This is to help track if any abortable command sequence was lost without EndCommandSequence or AbortCommandSequence
		@return pointer to the abortable command sequence or nil on error.
		@post call CmdUtils::EndCommandSequence(IAbortableCmdSeq*) or 
			CmdUtils::AbortCommandSequence(IAbortableCmdSeq*) to terminate sequence.
	*/
	static IAbortableCmdSeq *BeginAbortableCmdSeq(const char* trackingData = nullptr);

	/** End an abortable command sequence.
		@param sequence to be ended
		@return kSuccess if the sequence ended successfully, other ErrorCode otherwise.
		@post don't access the sequence again after calling this method.
	*/
	static ErrorCode EndCommandSequence(IAbortableCmdSeq *sequence);

	/** Abort an abortable command sequence.
		@param sequence the sequence to be aborted.
		@return kSuccess if the sequence was successfully aborted, other ErrorCode otherwise.
		@post don't access the sequence again after calling this method.
	*/
	static ErrorCode AbortCommandSequence(IAbortableCmdSeq *sequence);

	/**	Mark a point in an abortable command sequence to roll back to later on 
		before the sequence is ended or aborted.
		@param sequence in which you want to set the mark
		@return 0 on failure, sequence mark value otherwise
	*/
	static SequenceMark SetSequenceMark(const IAbortableCmdSeq *sequence);

	/**	Roll back an abortable command sequence to a particular sequence mark.
		@pre CmdUtils::SetSequenceMark was used to set the mark.
		@param sequence to be rolled back.
		@param upToMark sequennce mark to roll back to.
	*/
	static ErrorCode RollBackCommandSequence(const IAbortableCmdSeq *sequence, SequenceMark upToMark = SequenceMark());

	/**	Turn on or off automatic busy cursor support during commands and sequences.
		@param bEnable kTrue to turn on (the default) or kFalse to turn off busy cursor.
	 */
	static void EnableBusyCursor(bool16 bEnable);

	/**	Is automatic busy cursor support on or off.
		@param none
		@return bool16 kTrue if busy cursor support is turned on (the default), or kFalse if off
	 */

	static bool16 IsBusyCursorEnabled();

	/**	Return the maximum sequence length.
		@return the maximum sequence length.
	*/
	static int32 GetMaxStackHeight();
	
	/**	Stack based helper class that encapsulates a command sequence (ICommandSequence); if 
		a sequence already exists this class does nothing
		(the commands you process join the existing sequence), otherwise
		a new sequence is created and ended by this class. The changes made by commands 
		processed within the sequence are commited if the global error code is
		kSuccess when this helper class goes out of scope, otherwise the database 
		is rolled back to its state before the sequence started
		(see CmdUtils::EndCommandSequence(ICommandSequence *)).

		The difference between this class and CmdUtils::SequencePtr is that this class
		does not create a new sequence if one already exists.
		
		@see ICommandSequence
		@see CmdUtils::SequencePtr
	*/
	class SequenceContext INHERITFROM
	{
		public:
			/** Creates a sequence (ICommandSequence) if there isn't already one.
				@param name for the sequence or nil if the name of the sequence should not be set.
			*/
			PUBLIC_DECL				SequenceContext(const PMString *name = nil);
			/** Ends the sequence.
			*/
			PUBLIC_DECL				~SequenceContext();
			/**	Returns kTrue if the error state is kSuccess
			*/
			bool16					Success() 						{ return kSuccess == State(); }
			/** Get the error state
				@return the global error code
				@see ErrorUtils::PMGetGlobalErrorCode
			*/
			PUBLIC_DECL ErrorCode	State();

		private:
			ICommandSequence*		fSequence;	
	};
	
	/** Stack based helper class that encapsulates a command sequence (ICommandSequence).
		The difference between this class and CmdUtils::SequenceContext is that this class
		always creates a new sequence. The changes made by commands 
		processed within the sequence are commited if the global error code is
		kSuccess when this helper class goes out of scope, otherwise the database 
		is rolled back to its state before the sequence started
		(see CmdUtils::EndCommandSequence(ICommandSequence *)).

		@see ICommandSequence
		@see CmdUtils::SequenceContext 
	*/
	class SequencePtr INHERITFROM
	{
		public:
			/** Constructor creates a command sequence.
			*/
			explicit				SequencePtr() :
										fSequence(CmdUtils::BeginCommandSequence(CONCAT_NAMES(__FILE__, __LINE__)))
										{}
			/** Destructor ends the sequence.
				@see CmdUtils::EndCommandSequence(ICommandSequence *)
			*/
			PUBLIC_DECL				~SequencePtr();

			/**	Returns kTrue if the error state is kSuccess
			*/
			bool16					Success() 						{ return kSuccess == State(); }
			/** Get the error state.
				@return the global error code
				@see ErrorUtils::PMGetGlobalErrorCode
			*/
			PUBLIC_DECL				ErrorCode				State();
			/**	Get the command sequence.
				@return the command sequence.
			*/
			ICommandSequence*		operator->()					{ return fSequence; }

		private:
			//These are not implemented. They are private to prevent use.
			SequencePtr(const SequencePtr&);
			SequencePtr& operator=(const SequencePtr&);

		private:
			ICommandSequence*		fSequence;
	};

		/** Private; for internal use only: Execute a command */
		static ErrorCode ExecuteCommand(ICommand *cmd);
		/** Private; for internal use only: Light-weight process a command */
		static ErrorCode LWProcessCommand(ICommand *cmd);
		/** Private; for internal use only: Returns kTrue if a command was light-weight processed */
		static bool8 IsCommandLWProcessed(ICommand *cmd);
		
		/** Begin an auto undo sequence; see IAutoUndoSequence for documentation.
			@param target database to be changed by the sequence.
			@param trackingData : string identifier of the caller. This is to help track if any auto undo sequence was lost without EndAutoUndoSequence
			@return pointer to the auto undo sequence or nil on error.
			@post call CmdUtils::EndAutoUndoSequence(IAutoUndoSequence*) to terminate the sequence.
			@see IAutoUndoSequence
			@see CmdUtils::AutoUndoSequencePtr helper class
		 */
		static IAutoUndoSequence *BeginAutoUndoSequence(IDataBase* target, const char* trackingData=nullptr);

		/**	End auto undo sequence
			@param arg 
			@return ErrorCode 
		 */
		static ErrorCode EndAutoUndoSequence(IAutoUndoSequence *arg);

		/**	Stack based helper class had for wrapping changes occurring in a code 
			block in a auto undo sequence. The constructor begins the sequence and the destructor ends it. 
			@see IAutoUndoSequence
		*/
		class  PUBLIC_DECL AutoUndoSequencePtr INHERITFROM
		{
		
		public:
								/**	Begins the sequence.
									@param target database to be changed within the sequence.
								 */
								explicit AutoUndoSequencePtr(IDataBase* target)
								:	fCookie(nil)
								{
									if (target)
										fCookie = CmdUtils::BeginAutoUndoSequence(target, CONCAT_NAMES(__FILE__, __LINE__));
								}
								/**	Ends the sequence.
								 */
								~AutoUndoSequencePtr()
								{
									if (fCookie)
										CmdUtils::EndAutoUndoSequence(fCookie);
								}
					
		private:
			//These are not implemented. They are private to prevent use.
			AutoUndoSequencePtr(const AutoUndoSequencePtr&);
			AutoUndoSequencePtr& operator=(const AutoUndoSequencePtr&);

		private:
			IAutoUndoSequence*	fCookie;
		};

private:
#ifdef DEBUG
	/** */
	enum { kMaxStackHeight = 1500 };
#else
    #ifdef MACINTOSH
    	enum { kMaxStackHeight = 25000 };
    #else 
        #ifdef _M_IX86 
        	enum { kMaxStackHeight = 10000 };
        #else
	        enum { kMaxStackHeight = 25000 };
        #endif
    #endif
#endif
};

#pragma export off

#endif // __CMDUTILS__
