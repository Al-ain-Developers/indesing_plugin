//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ICommandChecker.h $
//  
//  Owner: Richard Rodseth
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
#ifndef __ICOMMANDCHECKER__
#define __ICOMMANDCHECKER__

#include "IPMUnknown.h"
#include "CommandID.h"

class ICommand;

/** This interface can be added to a command boss class, and used by "clients" of
	the command such as trackers and panels, as well as within the command.
	Implementations of ICommandChecker (typically derived from CCommandChecker)
	can access the command's item list and the current data in the command's
	data interface in order to validate them. This provides a central place
	for validation that can be shared by trackers, panel UI and the commands
	themselves.
	As long as the command object is around, the error code can be obtained,
	whether or not the command has been executed. The error code can also be
	cached (if requested) to avoid repeating expensive checks.
	To allow finer control, and distinguish between different error 
	conditions, multiple  command checkers (with different interface IDs of
	course) can be added to a command boss. 

	@ingroup arch_cmd
	@see CCommandChecker

*/
class ICommandChecker : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICOMMANDCHECKER };
		
	// This method is called to validate the command data.
	// It can cache the error code if requested.			
	virtual ErrorCode CheckCommand(bool16 saveError) = 0;
	
	virtual void ClearLastError(bool16 saveError) = 0;	
	virtual void SaveLastError() = 0;	
	virtual ErrorCode GetLastError() = 0;
	virtual void SetError(const ErrorCode& error) = 0; 
};
	

#endif // __ICOMMANDCHECKER__