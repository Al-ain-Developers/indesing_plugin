//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ICommandProcessor.h $
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
//  Purpose:	Global interface for execution of commands.
//  In order to use commands and/or command sequences
//  please refer to CmdUtils.h.
//  
//========================================================================================

#pragma once
#ifndef __ICOMMANDPROCESSSOR__
#define __ICOMMANDPROCESSSOR__

#include "CommandID.h"
#include "IPMUnknown.h"
#include "ICommand.h"
#include "ICommandSequence.h"

class ICommandInterceptor;
class WideString;

#define NEW_TARGET

/** Global command processor; client code should not need to call methods of this interface directly, 
	to process commands use CmdUtils.

	@see CmdUtils
	@see ICommand
	@see IDataBase
	@ingroup arch_cmd
*/
class ICommandProcessor : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ICOMMANDPROCESSOR };
	
		// regular cmd processing = default method for cmd execution
		virtual ErrorCode ProcessCommand(ICommand * cmd) = 0;
		virtual ErrorCode LWProcessCommand(ICommand * cmd) = 0;
		
		// command sequences
		//@param trackingData : string identifier of the caller. This is to help track if any command sequence was lost without EndCommandSequence
		virtual ICommandSequence *BeginCommandSequence(const char* trackingData = nullptr) = 0;
		virtual ErrorCode EndCommandSequence(ICommandSequence *sequence) = 0;
								
		// Abortable command sequences
		// @param trackingData : string identifier of the caller. This is to help track if any abortable command sequence was lost without EndCommandSequence or AbortCommandSequence

		virtual IAbortableCmdSeq *BeginAbortableCmdSeq(const char* trackingData = nullptr) = 0;
		virtual ErrorCode EndCommandSequence(IAbortableCmdSeq *sequence) = 0;
		virtual ErrorCode AbortCommandSequence(IAbortableCmdSeq *sequence) = 0;
		
		// use sequence marks to define points in your sequence where
		// you might want to roll back to later (before you end or abort the sequence).
		virtual SequenceMark SetSequenceMark(const IAbortableCmdSeq *sequence) = 0;
		virtual ErrorCode RollBackCommandSequence(const IAbortableCmdSeq *sequence, SequenceMark upToMark = SequenceMark()) = 0;	// will undo all cmds up to and including upToMark


		/**	Turn on or off automatic busy cursor support during commands and sequences.
			@param bEnable kTrue to turn on (the default) or kFalse to turn off busy cursor.
		 */
		virtual void EnableBusyCursor(bool16 bEnable) = 0;

		/**	Is automatic busy cursor support on or off.
			@param none
			@return bool16 kTrue if busy cursor support is turned on (the default), or kFalse if off
		 */
		virtual bool16 IsBusyCursorEnabled() const = 0;

		/** DEPRICATED
			Avoid using this function if possible - this is legacy and is deprecated.
		*/
		// execute cmds dynamically
		virtual ErrorCode ExecuteDynamic(ICommand * cmd) = 0;
		// these methods will eventually go away
		virtual ErrorCode ExecuteImmediate(ICommand * cmd) = 0;
		
		// support for command interception
		// there can be more than one cmd interceptor at once
		// see ICommandInterceptor.h for details
		virtual void InstallInterceptor(ICommandInterceptor *newInterceptor) = 0;
		virtual void DeinstallInterceptor(ICommandInterceptor *theInterceptor) = 0;
		
		// 
		// for internal use only
		virtual bool16 InterceptScheduledCmd(ICommand *cmd) = 0;
		virtual void PartialPurge() = 0;
		virtual I_Base_CommandSequence *GetCurrentCommandSequence() const = 0;		
		virtual ICommand*GetCurrentCommand() const = 0;
		virtual bool8 IsProcessorStackEmpty() const = 0;		

#ifdef DEBUG
		virtual void EnableCmdBehaviorMonitor(bool8 ) = 0;
		virtual bool8 IsCmdBehaviorMonitorEnabled() const = 0;
#endif
		// @param trackingData : string identifier of the caller. This is to help track if any auto undo sequence was lost without EndAutoUndoSequence
		virtual IAutoUndoSequence *BeginAutoUndoSequence(IDataBase* target, const char* trackingData = nullptr) = 0;
		virtual ErrorCode EndAutoUndoSequence(IAutoUndoSequence *arg) = 0;

};

// For private use only
#define kInterfaceSnapshotTrace "AutoUndo Trace"

#endif // __ICOMMANDPROCESSSOR__