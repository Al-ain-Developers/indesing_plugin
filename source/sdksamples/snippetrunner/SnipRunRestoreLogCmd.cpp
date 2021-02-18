//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/SnipRunRestoreLogCmd.cpp $
//  
//  Owner: Adobe Developer Technologies
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

#include "VCPlugInHeaders.h"

// General includes
#include "Command.h"

// Project includes
#include "SnipRunID.h"
#include "SnipRunLog.h"

/** When resize of the panel displaying the log starts the text control
	that displays it is cleared because otherwise the text display
	gets messed up and this command is scheduled to run to restore
	the contents of the log. When the user finishes dragging the mouse
	to do the resize this command runs and restores the contents of 
	the log.

	@ingroup snippetrunner
	
 */
class SnipRunRestoreLogCmd : public Command
{
	public:
		/** Constructor.
		*/
		SnipRunRestoreLogCmd(IPMUnknown* boss);

		/** Destructor.
		*/
		virtual ~SnipRunRestoreLogCmd();	

	protected:		
		/** Calls SnipRunLog::ResizeComplete to restore the log contents.
		*/
		void Do();
};

/*
*/
CREATE_PMINTERFACE(SnipRunRestoreLogCmd, kSnipRunRestoreLogCmdImpl)

/*
*/
SnipRunRestoreLogCmd::SnipRunRestoreLogCmd(IPMUnknown* boss) : Command(boss)
{
	this->SetUndoability(kAutoUndo);
	this->SetTarget(Command::kSessionWorkspaceTarget);
}

/*
*/
SnipRunRestoreLogCmd::~SnipRunRestoreLogCmd()
{
}

/*
*/
void SnipRunRestoreLogCmd::Do()
{
	if (SnipRunLog::PeekAtSnipRunLog() != nil) {
		SnipRunLog::Instance()->ResizeComplete();
	}		
}

// End SnipRunRestoreLogCmd.cpp