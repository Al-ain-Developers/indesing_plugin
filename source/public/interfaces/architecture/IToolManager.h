//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IToolManager.h $
//  
//  Owner: lance bushore
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
//  Purpose of interface:
//  Maintains information about currently selected tools of each type.
//  
//========================================================================================

#pragma once
#ifndef __IToolManager__
#define __IToolManager__

#include "IPMUnknown.h"
#include "ToolRecord.h"

class ITool;
class IEvent;
/** Interface responsible for maintaining a list of tools. Also keeps track of MRU tools of specific types. 
	@see IToolBoxUtils for the most common way to access most of this functionality.
*/
class IToolManager: public IPMUnknown
{
	public:
	/** Sets the active tool. Typically only called by SetToolCmd, which in turn is usually invoked by calling Utils<IToolBoxUtils>()->SetActiveTool( itool, toolType );
		@param newActiveTool the new tool to make active
		@param toolType the 'type' of this tool. Traditional tools are of type kPointerToolBoss. Tools of the same type are mutually exclusive.
	*/
		virtual void SetActiveTool(ITool* newActiveTool,ClassID toolType) = 0;
		
	/** returns the active tool. Most often this is accessed by calling Utils<IToolBoxUtils>()->QueryActiveTool( toolType );
		@param toolType the 'type' of this tool. Traditional tools are of type kPointerToolBoss. Tools of the same type are mutually exclusive.
		@return pointer to the active tool of the desired type.
	*/
		virtual ITool* QueryActiveTool(ClassID toolType) = 0;

	/** returns the previous active tool. If the user is using the rectangle tool, and then switches to the oval tool, calling this would return
		the rectangle tool to you. Most often this is accessed by calling Utils<IToolBoxUtils>()->QueryPreviousActiveTool( toolType );
		@param toolType the 'type' of this tool. Traditional tools are of type kPointerToolBoss. Tools of the same type are mutually exclusive.
		@return pointer to the previous active tool of the desired type. 
	*/
		virtual ITool* QueryPreviousActiveTool(ClassID toolType) = 0;

	/** returns the most recent active selection tool. If the user is using the direct select tool, and then switches to the zoom tool, and then switches to the oval tool, 
		calling this would return the direct select tool to you. 
		@return pointer to the previous active selection tool
	*/
		virtual ITool* QueryMostRecentSelectionTool() = 0;
		
	/** returns the most recent creation tool. If the user is using the oval tool, then switches to the zoom tool,  
		calling this would return the oval tool to you. 
		@return pointer to the previous active selection tool
	*/
		virtual ITool* QueryMostRecentCreationTool() = 0;
		
	/** request the number of tool types. Traditional tools are of type kPointerToolBoss. Tools of the same type are mutually exclusive.
		@return count of unique tool types
	*/
		virtual int32 GetNumToolTypes() = 0;

	/** request the nth tool type. Note that the tool type is a ClassID equal to the ClassID of the default tool for that type.
		@param index the index of the tool type you're interested in.
		@return ClassID of nth tool type
	*/
		virtual ClassID GetNthToolType(int32 index) = 0;
		
	/** Startup the tool manager. Internal use only.
	*/
		virtual void	Startup(const PMLocaleId& localId) = 0;

	/** Shutdown the tool manager. Internal use only.
	*/
		virtual void	Shutdown(const PMLocaleId& localeId) =  0;

	/** Add a new tool to the tool manager. This is only legal to do during startup. 
		Usually this gets called as a result of registering plugins and reading in their ToolDef resources
		@param tool the new tool
		@param groupNum the group number this tool should be in in the toolbox. See ToolboxDefs.h
		@param toolNum the tool number for this tool within its group in the toolbox. See ToolboxDefs.h
		@param parentTool the ClassID of the tool this tool should be 'under' in the toolbox.
		@param subToolNum the subtool number for this tool. Used for relative positioning of subtools. See ToolboxDefs.h
		@param iconID the icon for the toolbox to display for this tool
		@param pluginID the plugin where the tool resource can be found.
	*/
		virtual void AddTool(ITool* tool, int32 groupNum, int32 toolNum, ClassID parentTool, int32 subToolNum, RsrcID iconID, const PluginID& pluginID) = 0;
		
		
	/** Request the nth tool. All these tools live in the main toolbox(i.e. they are not subtools)
		@param index the index of the tool you're interested in.
		@return the requested ToolRecord
	*/
		virtual ToolRecord GetNthTool(int32 index) = 0;
		
	/** Request the nth subtool. None of these tools live in the main toolbox(i.e. they are subtools)
		@param index the index of the subtool you're interested in.
		@return the requested ToolRecord
	*/
		virtual ToolRecord GetNthSubTool(int32 index) = 0;
		
	/** Request the number of tools. All these tools live in the main toolbox(i.e. they are not subtools)
		@return count of tools
	*/
		virtual int32 GetNumTools() = 0;

	/** Request the number of subtools. None of these tools live in the main toolbox(i.e. they are subtools)
		@return count of subtools
	*/
		virtual int32 GetNumSubTools() = 0;
		
		
	/** Request the ToolRecord for the parent tool.
		@param parentClass the ClassID of the parent tool you want to find.
		@param result the requested ToolRecord for the parent tool is copied into the passed in 'result' param
		@return boolean indicating if the parent tool was found
	*/
		virtual bool16 FindParentTool(ClassID parentClass, ToolRecord* result) = 0;

	/** Request the ToolRecord for a tool or subtool
		@param toolClass the ClassID of the tool you want to find.
		@param result the requested ToolRecord for the tool is copied into the passed in 'result' param
		@return boolean indicating if the tool was found
	*/
		virtual bool16 FindTool(ClassID toolClass, ToolRecord* result) = 0; 
		
	/** Sets the selection tool returned by QueryMostRecentSelectionTool to a different selection tool without changing tools.  Used for cmd-tab behavior.
		@param selectionTool the newly used selection tool.
	*/
		virtual void SetMostRecentSelectionTool(ITool* selectionTool) = 0;

	/** Sets the tool that RestoreSpringLoadedTool will restore.
		@param tool tool that should be restored.
	*/
		virtual void SetSpringLoadedTool(ITool * tool) = 0;

	/** Restores the spring loaded tool
	*/
		virtual void RestoreSpringLoadedTool() = 0;

	/** Handles KeyUp events for spring loaded shortcuts
		@param e event from the KeyUp event that fired.
		@return true if the handler did something and watching should stop.
	*/
		virtual bool16 OnKeyUp(IEvent* e) = 0;

	/** Handles KeyDown events for spring loaded shortcuts
		@param e event from the KeyDown event that fired.
		@return true if the handler did something and watching should stop.
	*/
		virtual bool16 OnKeyDown(IEvent* e) = 0;

	/** checks to see if we have a spring loaded tool in the hopper.
		@return true if we have a spring loaded tool.
	*/
		virtual bool16 IsToolSpringLoaded() = 0;
	
#ifdef DEBUG
	/** Debug only method to dump out internal structures.
	*/
		virtual void DumpToolManager() = 0;
#endif
};


#endif

