//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IToolBoxUtils.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __IToolBoxUtils__
#define __IToolBoxUtils__

#include "ToolboxID.h"
#include "IPMUnknown.h"
#include "Utils.h"
#include "LayoutUIID.h"

class ITool;

/** This interface provides utility routines for dealing with tools.
	i.e. Utils<IToolBoxUtils>()->SetActiveTool( ... ) ;
*/
class IToolBoxUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITOOLBOXUTILS };

	/** Sets the currently active tool. Tool can be set to nil.
		@param itool The tool to set active
		@param toolType the type of the tool. Tools of the same type are mutually exclusive. 
			"Traditional" tools(creation, selection,...) are of type kPointerToolBoss
		@return kTrue if tool could be set ok.
	*/
	virtual bool16 SetActiveTool( ITool* itool,ClassID toolType = kPointerToolBoss) = 0; 

	/** Retrieves the currently active tool. 
		@param toolType the type of the tool you're interested in. Tools of the same type are mutually exclusive. 
			"Traditional" tools(creation, selection,...) are of type kPointerToolBoss
		@return the active tool for the passed in toolType. Callers should Release() this pointer when done.
	*/
	virtual ITool* QueryActiveTool(ClassID toolType = kPointerToolBoss) = 0;

	/** Retrieves the previous active tool. 
		@param toolType the type of the tool you're interested in. Tools of the same type are mutually exclusive. 
			"Traditional" tools(creation, selection,...) are of type kPointerToolBoss
		@return the toolvfor the passed in toolType, which was active before the current one. Callers should Release() this pointer when done.
	*/
	virtual ITool* QueryPreviousActiveTool(ClassID toolType = kPointerToolBoss) = 0;

	/** Retrieves the most recently active tool which is classified as a selection tool. 
		@return the most recent selection tool. Callers should Release() this pointer when done.
	*/
	virtual ITool* QueryMostRecentSelectionTool() = 0;

	/** Retrieves the most recently active tool which is classified as a creation tool. 
		@return the most recent creation tool. Callers should Release() this pointer when done.
	*/
	virtual ITool* QueryMostRecentCreationTool() = 0;

	/** Retrieves the pointer to the tool with the given ClassID 
		@param toolClass the boss ID of the tool you're interested in
		@return the requested tool. Callers should Release() this pointer when done.
	*/
	virtual ITool* QueryTool(ClassID toolClass) = 0;

	/** Counts the number of tools that live in the toolbox. This includes tools in the main toolbox, and 'subtools' which are accessible 'under' a toolbox tool.
		@return the count of tools
	*/
	virtual int32 GetNumTools() = 0;

	/** Gets the nth tool from the toolbox
		@param index which tool you're interested in
		@return the requested tool. Callers should Release() this pointer when done.
	*/
	virtual ITool* QueryNthTool(int32 index) = 0;

	/** Enables/disables tools in the toolbox based on the classID of the passed in view. Tools which don't work in this view are disabled.
		@param theClass The class of the view you want to base tool enabling on.
	*/
	virtual void EnableToolsForViewClass(ClassID theClass) = 0;

	/** Tests to see if a tool in the tool panel is enabled. This returns kTrue if the tool panel is hidden.
		@param itool the tool to test.
		@return kTrue if the tool is enabled. kFalse if the tool is disabled and the panel is visible.
	*/
	virtual bool16 IsToolEnabled(ITool* itool) = 0;
};


#endif	// __IToolBoxUtils__


