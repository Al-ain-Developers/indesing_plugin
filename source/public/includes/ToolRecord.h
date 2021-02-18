//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/ToolRecord.h $
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
//========================================================================================

#pragma once
#ifndef __ToolRecord__
#define __ToolRecord__

class ITool;
#pragma export on

/** Class which maintains information about tool positions in toolbox.
*/
class WIDGET_DECL ToolRecord
{
	public:	// note: holds a ref on the interface.
   		typedef base_type data_type;
		ToolRecord(ITool* face, int32 groupNum, int32 toolNum, ClassID parentTool, int32 subToolNum, RsrcID iconID, const PluginID& pluginID);
		ToolRecord(const ToolRecord& rec);
		ToolRecord(); 
		~ToolRecord();
		
		void ReadWrite(IPMStream *s);

		/**  Query the tool from the ToolRecord. This does an AddRef() caller should Release() the returned ITool*
			@return the tool
		*/
		ITool* QueryTool();
		
		/**  Gets the toolbox group number this tool belongs in. Ignored if this is a subtool. This is used for positioning the tool in the toolbox. @see ToolBoxDefs.h
			@return the toolbox group number
		*/
		int32 GetGroupNum() const;

		/**  Gets the tool number within a group. Ignored if this is a subtool. This is used for positioning the tool in the toolbox. @see ToolBoxDefs.h
			@return the toolbox group number
		*/
		int32 GetToolNum() const;

		/**  Gets the parent tool of this tool. This is used for positioning the tool in the toolbox. If a tool has a parent tool, then by default it is hidden 'under' that tool in the toolbox.
			Tools which have a parent tool are sometimes called subtools. @see ToolBoxDefs.h
			@return the parent tool ClassID
		*/
		ClassID GetParentTool() const;
		
		/**  Gets the subtool number of this tool. Ignored if this is not a subtool. This is used for positioning the subtool in the toolbox flyout. @see ToolBoxDefs.h
			@return the toolbox group number
		*/
		int32 GetSubToolNum() const;
		
		/**  Gets the resource id of the icon for this tool
			@return the icon resource id
		*/
		RsrcID GetIconID();

		/**  Gets the plugin id of the icon for this tool
			@return the plugin id
		*/
		PluginID GetIconPluginID();
		

		/**  Sets the group number for positioning this tool. Rarely used. No effect after the toolbox has been built.
			@param newGroup which group to move the tool into.
		*/
		void SetGroupNum(int32 newGroup);
		
		PUBLIC_DECL friend bool16 operator ==(const ToolRecord& a, const ToolRecord& b);

	private:
		UID fToolUID;
		int32 fGroupNum;
		int32 fToolNum;
		ClassID fParentTool;
		int32 fSubToolNum;
		RsrcID fIconID;
		PluginID fIconPluginID;
		
};


WIDGET_DECL bool16 ToolRecordCompare(const ToolRecord &toolRec1, const ToolRecord &toolRec2);
WIDGET_DECL bool16 SubToolRecordCompare(const ToolRecord &toolRec1, const ToolRecord &toolRec2);

#pragma export off
#endif