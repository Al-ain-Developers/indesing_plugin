//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CommandFactory.h $
//  
//  Owner: Michael Burbidge
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

#ifndef __CommandFactory_h__
#define __CommandFactory_h__

#include "ICommandFactory.h"
#include "IBehaviorData.h"
#include "CmdUtils.h"
#include "CPMUnknown.h"
#include "BehaviorID.h"

/**	CommandFactory is a template that can be used to declare a command factory
	for interactive behaviors. When a new interactive behavior is created
	there must be a command factory declared.
*/

template <int32 CreateCmd, int32 EditCmd, int32 DeleteCmd, int32 DeferredScrapCmd>
class CommandFactory : public CPMUnknown<ICommandFactory>
{
public:
	/** CommandFactory constructor
		@param boss
	*/
	CommandFactory(IPMUnknown *boss) : 
		CPMUnknown<ICommandFactory>(boss) { }
		
	/** CommandFactory destructor
	*/
	virtual ~CommandFactory() { }
	
	/** CreateCreateCommand creates a creation command
		@return the command.
	*/
	virtual ICommand*	CreateCreateCommand() const
	{
		ICommand* cmd = CmdUtils::CreateCommand (CreateCmd);
		
		InterfacePtr<IBehaviorData> actionData(this, UseDefaultIID());
		InterfacePtr<IBehaviorData> cmdActionData(cmd, UseDefaultIID());
		
		cmdActionData->Copy(actionData);
		
		return cmd;
	}
	
	/** CreateCreateCommand creates an edit command
		@return the command.
	*/
	virtual ICommand*	CreateEditCommand() const
	{
		ICommand* cmd = CmdUtils::CreateCommand (EditCmd);
		
		InterfacePtr<IBehaviorData> actionData(this, UseDefaultIID());
		InterfacePtr<IBehaviorData> cmdActionData(cmd, UseDefaultIID());
		
		cmdActionData->Copy(actionData);
		
		return cmd;
	}
	
	/** CreateCreateCommand creates a delete command
		@return the command.
	*/
	virtual ICommand*	CreateDeleteCommand() const
	{
		ICommand* cmd = CmdUtils::CreateCommand (DeleteCmd);		
		return cmd;
	}
	
	/** CreateCreateCommand creates a deffered scrap command
		@return the command.
	*/
	virtual ICommand*	CreateDeferredScrapCommand() const
	{
		ICommand* cmd = nil;
		
		if (DeferredScrapCmd != kNoOpCmdBoss)
			cmd = CmdUtils::CreateCommand (DeferredScrapCmd);
	
		return cmd;
	}
};

#endif // __CommandFactory_h__
