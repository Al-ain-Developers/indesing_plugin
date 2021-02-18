//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IToolCmdData.h $
//  
//  Owner: Lonnie Millett
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
#ifndef __ITOOLCMDDATA__
#define __ITOOLCMDDATA__

#include "IPMUnknown.h"
#include "CommandID.h"

class ITool;

/** Interface responsible for maintaining data for tool cmds
*/
class IToolCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITOOLCMDDATA };
		
	/**  Set the data for the tool cmd
		@param theTool which tool to use for this command.
		@param toolType the tool type for the command. Tool type is used to identify mutually exclusive tools. The traditional tools
		in the toolbox are all of type 'kPointerToolBoss'
	*/
		virtual void Set(ITool* theTool,ClassID toolType) = 0;

	/**  Get the tool  for the command. 
		@return the tool for this command
	*/
		virtual ITool* GetTool() const = 0;
	
	/**  Get the tool type for the command. Tool type is used to identify mutually exclusive tools. The traditional tools
		in the toolbox are all of type 'kPointerToolBoss'
		@return the tool type
	*/
		virtual ClassID GetToolType() const = 0;
};

//----------------------------------------------------------------------------------------
// Inlines:
//----------------------------------------------------------------------------------------

#endif
