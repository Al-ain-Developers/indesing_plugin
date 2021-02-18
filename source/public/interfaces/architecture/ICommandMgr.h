//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ICommandMgr.h $
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
#ifndef __ICOMMANDMGR__
#define __ICOMMANDMGR__

#include "IPMUnknown.h"
#include "CommandID.h"

class ICommand;
class PMString;
class IDataBase;

/** Targets an an InDesign database (see IDataBase) and executes commands on it; you should not need 
	to call any methods of this interface from client code, to process  commands use CmdUtils.

	@see CmdUtils
	@see ICommand
	@see IDataBase
	@see ICmdHistory
	@ingroup arch_cmd
	@ingroup arch_db
*/
class ICommandMgr : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICOMMANDMGR };
		
	/** Execute the cmd */
	virtual void Do(ICommand * cmd) = 0;
		
	/** Execute the cmd immediately */
	virtual void ExecuteImmediate(ICommand *cmd) = 0;
	
	/** DEPRICATED
		Avoid using this function if possible - this is legacy and is deprecated.
		Execute the cmd dynamically */
	virtual void ExecuteDynamic(ICommand *cmd) = 0;
			
	/** direct notifications that tell the commandmgr
	 about changes to its cmdhistory */
	virtual void DiscardedHistorySteps() = 0;
	/** Direct notification to the commandmgr to start a history sequence */
	virtual void StartHistorySequence() = 0;


	/** Direct notification to the commandmgr that a history step was added */
	virtual void AddedHistoryStep() = 0;

	/** Direct notification to the commandmgr that history steps were undone */
	virtual void UndidHistorySteps() = 0;
	/** Direct notification to the commandmgr that history steps were redone */
	virtual void RedidHistorySteps() = 0;
	/** Direct notification to the commandmgr to end a history sequence */
	virtual void EndHistorySequence() = 0;
	
	/** Get the database of the commandmgr */
	virtual IDataBase *GetTargetDB() const = 0;
	
	/** Set the database of the commandmgr */
	virtual void SetTargetDB(IDataBase* db) = 0;
	
	/** For internal use only*/
	virtual bool16 SetUndoSupport(bool16 on) = 0;	

};

#endif