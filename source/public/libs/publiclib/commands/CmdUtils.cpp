//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/commands/CmdUtils.cpp $
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
//========================================================================================

#include "VCPublicHeaders.h"

#include "CmdUtils.h"
#include "ErrorUtils.h"
#include "InterfacePtr.h"
#include "ICommand.h"
#include "ICommandProcessor.h"
#include "ICmdQueue.h"
#include "IDocument.h"
#include "PersistUtils.h"
#include "IApplication.h"
#include "IWorkspace.h"

		// command creation
		
ICommand* CmdUtils::CreateCommand(ClassID cmdType)
{ 
	ICommand* cmd =  (ICommand*)::CreateObject(cmdType, IID_ICOMMAND);
	if (cmd != nil)
		cmd->SetCreatorID(cmdType.Get());	// IDType ISSUE: change param to TypeID?
	return cmd; 
}
	  
		// regular command processing, affecting undo/redo stacks

ErrorCode CmdUtils::ProcessCommand(ICommand *cmd)
{
	ErrorCode err = kSuccess;
	
	if (cmd)
	{
		InterfacePtr<ICommandProcessor>cmdProc(GetExecutionContextSession()->QueryCommandProcessor());
		if (cmdProc)
			err = cmdProc->ProcessCommand(cmd);
		else
			err = kFailure;
	}
	
	return err;
}

ErrorCode CmdUtils::ScheduleCommand(ICommand *cmd, ICommand::Priority priority)
{
	ErrorCode err = kSuccess;
	
	if (cmd)
	{
		InterfacePtr<ICommandProcessor>cmdProc(GetExecutionContextSession()->QueryCommandProcessor());
		if (cmdProc)
		{
			InterfacePtr<ICmdQueue> queue(cmdProc, IID_ICMDQUEUE);
			err = queue->ScheduleCommand(cmd, priority);
		}
		else
			err = kFailure;
	}
	return err;
}

bool16 CmdUtils::ProcessScheduledCmds(ICommand::Priority downToPriority)
{
	InterfacePtr<ICommandProcessor>cmdProc(GetExecutionContextSession()->QueryCommandProcessor());
	if (cmdProc)
	{
		InterfacePtr<ICmdQueue> queue(cmdProc, IID_ICMDQUEUE);
		return queue->ProcessScheduledCmds(downToPriority);
	}
	else
		return kFalse;

}

		// direct command execution, bypassing undo/redo stacks

ErrorCode CmdUtils::ExecuteCommand(ICommand *cmd)
{
	ErrorCode err = kSuccess;
	
	if (cmd)
	{
		InterfacePtr<ICommandProcessor>cmdProc(GetExecutionContextSession()->QueryCommandProcessor());
		if (cmdProc)
			err = cmdProc->ExecuteImmediate(cmd);
		else
			err = kFailure;
	}
	
	return err;
}


// DEPRICATED
// Avoid using this function if possible - this is legacy and is deprecated.
ErrorCode CmdUtils::ExecuteDynamicCommand(ICommand *cmd)
{
	ErrorCode err = kSuccess;
	
	if (cmd)
	{
		InterfacePtr<ICommandProcessor>cmdProc(GetExecutionContextSession()->QueryCommandProcessor());
		if (cmdProc)
			err = cmdProc->ExecuteDynamic(cmd);
		else
			err = kFailure;
	}
	return err;
}

// DEPRICATED
// Avoid using this function if possible - this is legacy and is deprecated.
ErrorCode CmdUtils::ExecuteDynamicCommand(ICommand *cmd, bool16 isActive)
{
	ErrorCode err = kSuccess;
	
	if (cmd)
	{
		bool16 wasActive = cmd->IsActive();
		cmd->SetActive(isActive);
	
		InterfacePtr<ICommandProcessor>cmdProc(GetExecutionContextSession()->QueryCommandProcessor());
		if (cmdProc)
			err = cmdProc->ExecuteDynamic(cmd);
		else
			err = kFailure;
		cmd->SetActive(wasActive);
	}
	return err;
}

// command sequences
ICommandSequence *CmdUtils::BeginCommandSequence(const char* trackingData)
{
	InterfacePtr<ICommandProcessor>cmdProc(GetExecutionContextSession()->QueryCommandProcessor());
	if (cmdProc)
		return cmdProc->BeginCommandSequence(trackingData);
	else
		return nil;
}

ErrorCode CmdUtils::EndCommandSequence(ICommandSequence *sequence)
{	
	InterfacePtr<ICommandProcessor>cmdProc(GetExecutionContextSession()->QueryCommandProcessor());
	if (cmdProc)
		return cmdProc->EndCommandSequence(sequence);
	else
		return kFailure;
}

int32 CmdUtils::GetMaxStackHeight()
{	
	return kMaxStackHeight;
}


ErrorCode CmdUtils::LWProcessCommand(ICommand *cmd)
{
	ErrorCode err = kSuccess;
	
	if (cmd)
	{
		InterfacePtr<ICommandProcessor>cmdProc(GetExecutionContextSession()->QueryCommandProcessor());
		if (cmdProc)
			err = cmdProc->LWProcessCommand(cmd);
		else
			err = kFailure;
	}	
	return err;
}

bool8 CmdUtils::IsCommandLWProcessed(ICommand *cmd)
{
	return cmd->IsLWProcessed();
}

//--------------------------------------------------------------------------------------
//  SequencePtr
//--------------------------------------------------------------------------------------

ErrorCode CmdUtils::SequencePtr::State()
{
	return ErrorUtils::PMGetGlobalErrorCode();
}

//--------------------------------------------------------------------------------------
// 	Destructor
//--------------------------------------------------------------------------------------

CmdUtils::SequencePtr::~SequencePtr()
{
	if(fSequence)
		EndCommandSequence(fSequence);
}

//--------------------------------------------------------------------------------------
//  SequenceContext
// stack-based light weight sequence
// checks if there is already a sequence
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// 	Constructor
//--------------------------------------------------------------------------------------

CmdUtils::SequenceContext::SequenceContext(const PMString *name)
									:	fSequence(nil)
{
	InterfacePtr<ICommandProcessor>cmdProc(GetExecutionContextSession()->QueryCommandProcessor());
	
	if(cmdProc && !cmdProc->GetCurrentCommandSequence())
	{
		fSequence = BeginCommandSequence(CONCAT_NAMES(__FILE__, __NAME__));
		if(name != nil)
			fSequence->SetName(*name);
	}
}


//--------------------------------------------------------------------------------------
// 	Destructor
//--------------------------------------------------------------------------------------

CmdUtils::SequenceContext::~SequenceContext()
{
	if(fSequence)
		EndCommandSequence(fSequence);
}

ErrorCode CmdUtils::SequenceContext::State()
{
	return ErrorUtils::PMGetGlobalErrorCode();
}

//-------------------------------------------
// AutoUndo sequences
//---------------------------------
IAutoUndoSequence *CmdUtils::BeginAutoUndoSequence(IDataBase* target, const char* trackingData)
{
	InterfacePtr<ICommandProcessor>cmdProc(GetExecutionContextSession()->QueryCommandProcessor());
	if (cmdProc)
		return cmdProc->BeginAutoUndoSequence(target,trackingData);
	else
		return nil;
}

ErrorCode CmdUtils::EndAutoUndoSequence(IAutoUndoSequence *arg)
{
	InterfacePtr<ICommandProcessor>cmdProc(GetExecutionContextSession()->QueryCommandProcessor());
	if (cmdProc)
		return cmdProc->EndAutoUndoSequence(arg);
	else
		return kFailure;
}

//--------------------------------------------------------------------------------------
// 	Abortable cmd Sequences
//--------------------------------------------------------------------------------------

IAbortableCmdSeq *CmdUtils::BeginAbortableCmdSeq(const char* trackingData)
{
	InterfacePtr<ICommandProcessor>cmdProc(GetExecutionContextSession()->QueryCommandProcessor());
	if (cmdProc)
		return cmdProc->BeginAbortableCmdSeq(trackingData);
	else
		return nil;
}

ErrorCode CmdUtils::EndCommandSequence(IAbortableCmdSeq *sequence)
{	
	InterfacePtr<ICommandProcessor>cmdProc(GetExecutionContextSession()->QueryCommandProcessor());
	if (cmdProc)
		return cmdProc->EndCommandSequence(sequence);
	else
		return kFailure;
}

ErrorCode CmdUtils::AbortCommandSequence(IAbortableCmdSeq *sequence)
{
	InterfacePtr<ICommandProcessor>cmdProc(GetExecutionContextSession()->QueryCommandProcessor());
	if (cmdProc)
		return cmdProc->AbortCommandSequence(sequence);
	else
		return kFailure;
}

SequenceMark CmdUtils::SetSequenceMark(const IAbortableCmdSeq *sequence)
{
	InterfacePtr<ICommandProcessor>cmdProc(GetExecutionContextSession()->QueryCommandProcessor());
	if (cmdProc)
		return cmdProc->SetSequenceMark(sequence);
	else
		return SequenceMark();
}
ErrorCode CmdUtils::RollBackCommandSequence(const IAbortableCmdSeq *sequence, SequenceMark upToMark)
{
	InterfacePtr<ICommandProcessor>cmdProc(GetExecutionContextSession()->QueryCommandProcessor());
	if (cmdProc)
		return cmdProc->RollBackCommandSequence(sequence, upToMark);
	else
		return kFailure;
}

void CmdUtils::EnableBusyCursor(bool16 bEnable)
{
	InterfacePtr<ICommandProcessor>cmdProc(GetExecutionContextSession()->QueryCommandProcessor());
	if (cmdProc)
		return cmdProc->EnableBusyCursor(bEnable);
}

bool16 CmdUtils::IsBusyCursorEnabled()
{
	InterfacePtr<ICommandProcessor>cmdProc(GetExecutionContextSession()->QueryCommandProcessor());
	if (cmdProc)
		return cmdProc->IsBusyCursorEnabled();
	else
		return kFalse;
}

