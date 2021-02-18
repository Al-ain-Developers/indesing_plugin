//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ITool.h $
//  
//  Owner: EricM,Frits
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
#ifndef __ITOOL__
#define __ITOOL__

#include "PMTypes.h" 
#include "IPMUnknown.h"
#include "ShuksanID.h"

class IEventHandler;
class PMString;
class IPanelControlData;
class ICursorProvider;

/** Basic tool interface. Provides methods to get/set information about a tool,
	as well as displaying options, selecting and deselecting.
*/
class ITool: public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITOOL };
		
		/** These are the types a tool will support.

			A tool can be one of more of the following types depending on what the tool does
			This is not to be confused with the tool type which is a ClassID as to what group 
			the tool is in
		*/
		enum ToolType
		{	
			/** */ 
			kNone = 0,
			/** */ 
			kLayoutSelectionTool = 1,
			/** */ 
			kTextSelectionTool = 2,
			/** */ 
			kTableSelectionTool = 4,
			/** */ 
			kLayoutManipulationTool = 8,
			/** */ 
			kTextManipulationTool = 16,
			/** */ 
			kTableManipulationTool = 32,
			/** */ 
			kLayoutCreationTool = 64,
			/** */ 
			kTextCreationTool = 128,
			/** */ 
			kTableCreationTool = 256,
			/** */ 
			kPathManipulationTool = 512,
			/** */ 
			kViewModificationTool = 1024,
			/** */ 
			kJGridTool = 2048,
			/** */ 
			kPageSelectionTool = 4096
		};

		/** Called to initialize tool. Tool should set the icon for it's view, and
			do any other needed initialization.
			@param iconID resource ID for the icon associated with the tool's view
			@param pluginID plugin that contains this resource
		*/
		virtual void Init(RsrcID iconID, const PluginID& pluginID) = 0;
		
		/** Called when tool is selected. 
		*/
		virtual void Select() = 0;
		
		/** Called when tool is deselected.
		*/
		virtual void Deselect() = 0;

		/** Returns true if the tool is selected, false otherwise
		*/
		virtual bool IsSelected() = 0;
			
	
		/** Get cursor provider for this tool.
			@return this tool's cursor provider
		*/
		virtual ICursorProvider* GetCursorProvider() const = 0;

		/** Set cursor provider for this tool
			@param newProvider specifies ICursorProvider for the tool
		*/
		virtual void SetCursorProvider(ICursorProvider* newProvider) = 0;
		
		/** Mutator for name of tool.
			@return name of tool
		*/
		virtual const PMString& GetName() const = 0;
		/** Accessor for name
			@param newName
		*/
		virtual void SetName(const PMString& newName) = 0;
		
		/** Mutator for hint text of tool.
			@return hint text of tool
		*/
		virtual const PMString& GetToolHint() const = 0;
		/** Accessor for tool hint
			@param newHint
		*/
		virtual void SetToolHint(const PMString& newHint) = 0;
		
		/** Get the current tool's toolbox icon resource file. 
		*/
		virtual const IDFile& GetToolIconFile() const = 0;

		//
		/** GetActionID for selecting tool
			@return action identifier for selecting tool
		*/
		virtual ActionID GetActionID() const = 0; 
		
		/** Set ActionID for selecting tool
			@param actionID new action identifier
		*/
		virtual void SetActionID(ActionID actionID) = 0;
		
		/** Get tool type. This type determines which tools are mutually exclusive
			@return ClassID of tool
		*/
		virtual const ClassID& GetToolType() const= 0;

		/** Set tool type. This type determines which tools are mutually exclusive
			@param newToolType new ClassID for tool
		*/
		virtual void SetToolType(const ClassID& newToolType) = 0;

	 			
		/** Called to display tool options(usually a dialog or nothing)	 
		*/
		virtual void DisplayOptions() = 0;
		
		/** Called to display alternate tool options(usually a dialog or nothing)
		*/
		virtual void DisplayAltOptions() = 0;
		
		
		/** Does this tool create items?
			@param kTrue if items are created, kFalse otherwise
		*/
		virtual bool16 IsCreationTool() const = 0;
		
		
		/** Does this tool select items? (i.e. kPointerToolBoss, kDirectSelectToolBoss, kCropToolBoss).
			@param kTrue if tool selects items, kFalse otherwise
		*/
		virtual bool16 IsSelectionTool() const = 0;

		
		/** Does this tool select text? This function could be more accurately be called
			DoesToolDeactivateTextEditor. For example, in addition to the kIBeamToolBoss, the kZoomToolBoss, 
			kGradientToolBoss, kGrabberHandToolBoss also return kTrue for this function. Use IsToolOfType
			in conjuction with kTextSelectionTool for traditional "text" tools that select text.
		*/
		virtual bool16 IsTextTool() const = 0;

		
		/**  Returns bool16 whether the tool is this type of tool
			@param type specifies type to compare this tool against
			@return kTrue if the given 'type' is the same type as this tool
		*/
		virtual bool16 IsToolOfType(ITool::ToolType type) const = 0;
	
		/** Returns the ScriptID associated with this particular tool such that
			scripts can ask the toolBox for the ScriptID of the current tool. The
			list of ScriptIDs for the toolbox tools are defined by en_ToolBoxTools 
			(kToolBoxEnumScriptElement). That is, when adding a new to to the Tool Box,
			you must first define a new ScriptID and then add it to kToolBoxEnumScriptElement. For
			example, to add scripting support for the pumpkin tool:
			1. Define a ScriptID to represent the tool.
				en_PumpkinTool =				'pmpk',
			2. Add the new constant to the kToolBoxEnumScriptElement by adding the following to your
			   plugin's ScriptInfo.fr file.
				 resource VersionedScriptElementInfo( 10 )
				 {
					 //Contexts
					 {
						kCS5ScriptVersion, kCoreScriptManagerBoss, kInDesignAllLanguagesFS, k_Wild,
					 }
					 //Elements
					 {
						 Enumerator
						 {
							 kToolBoxEnumScriptElement,
							 {
								en_PumpkinTool, "pumpkin tool", "The pumpkin tool",
							 }
						 }
					 }
				 } ;
			3. Return 'en_PumpkingTool' from the GetScriptID method of the ITool implementation for the pumpkin tool.
		 
			@return the ScriptID associated with this tool in the en_ToolBoxTools enumeration
		*/
		virtual ScriptID GetScriptID() const = 0;

		/**  Returns bool16 whether the tool is this none tool i.e. ITool::kNone
		@return kTrue if the given tool is of  type ITool::kNone
		*/
		virtual bool16 IsToolNone() const = 0;
};


#endif