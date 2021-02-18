//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CTool.h $
//  
//  Owner: EricM
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
//  Updated: Frits - Rewrite for widget architecture
//  
//  Helper class for implementing the ITool interface.
//  
//========================================================================================

#pragma once
#ifndef __CTool__
#define __CTool__

#include "ITool.h"
#include "HelperInterface.h"
#include "PMString.h"
#include "PMRect.h"
#include "ScriptingDefs.h"
#include "IControlView.h"

#ifdef WIDGET_BUILD
#pragma export on
#endif
const PMReal kOneToolIconWidth = 30.0;
const PMReal koneToolIconHeight = 24.0;
const PMRect kStandardToolRect(0,0,kOneToolIconWidth,koneToolIconHeight);
const PMRect kMiniToolRect(0,0, 20,20);
const PMRect kMiddleMiniToolRect(0,0,20,20);


/**	Base implementation for tools. Clients implementing a new tool typically subclass CTool and override just the methods they need to.
	Most tool implementations only override a few methods: Init, sometimes DisplayOptions. 
*/
class WIDGET_DECL CTool: public ITool
{
	public:
		CTool(IPMUnknown *boss);
		CTool(IPMUnknown *boss, int32 toolInfo, bool16 isCreation, bool16 isSelection);
		~CTool();
		
		virtual void ReadWrite(IPMStream* s, ImplementationID prop);
		
		/**	CTool does nothing in Init. Custom tool impls typically override this method and call SetName("My Tool") and InitWidget(kMyToolWidgetId, iconID, pluginID);
		*/
		virtual void Init(RsrcID iconID, const PluginID& pluginID);
		
		/**	CTool implements this to initialize the associated control view with the passed in WidgetID & icon/PNG.
		*/
		virtual void InitWidget(const WidgetID& widgetId, RsrcID iconID, const PluginID& pluginID, PMRect toolRect = kStandardToolRect);
		
		/** Subclasses which override this method should call this Select before doing anything -- it notifies the selection that the tool is changing
		*/
		virtual void Select();

		/** Subclasses which override this method should call this Deselect before doing anything -- it notifies the selection that the tool is changing
		*/
		virtual void Deselect();

		/** Returns true if the tool is selected, false otherwise
		*/
		virtual bool IsSelected();

		/** Get the cursor provider for this tool. CTool fully implements this. Usually subclasses don't need to override this.
		*/
		virtual ICursorProvider* GetCursorProvider() const;

		/** Set the cursor provider for this tool. CTool fully implements this. Usually subclasses don't need to override this.
		*/
		virtual void SetCursorProvider(ICursorProvider* newProvider);
		
		/** Check if this tool is a creation tool. Subclasses can specify this in the constructor call to CTool, so CTool is able to implement this fully.
		*/
		virtual bool16 IsCreationTool() const;

		/** Check if this tool is a creation tool. Subclasses can specify this in the constructor call to CTool, so CTool is able to implement this fully.
		*/
		virtual bool16 IsSelectionTool() const;

		/** Check if this tool is a text tool. CTool returns kFalse. Subclasses that are text tools need to override this to return kTrue.
		*/
		virtual bool16 IsTextTool() const;

		/** Get the name of the tool. Fully implemented by CTool. Subclasses usually have no need to override.
		*/
		virtual const PMString& GetName() const;

		/** Set the name of the tool. Fully implemented by CTool. Subclasses usually have no need to override.
		*/
		virtual void SetName(const PMString& newName);
		
		/** Get the tool hint of the tool. 
		*/
		virtual const PMString& GetToolHint() const;

		/** Set the tool hint of the tool. 
		*/
		virtual void SetToolHint(const PMString& newHint);
		
		/** Get the current tool's toolbox icon resource file. 
		*/
		virtual const IDFile& GetToolIconFile() const;

		/**	Get tool type. This type determines which tools are mutually exclusive. The ClassID for the tool type is defined to be the ClassID of the 
			default tool for that type. Traditional tools in the toolbox have a tooltype of kPointerToolBoss. This method is fully implemented by CTool.
			Subclasses usually have no need to override.
		*/
		virtual const ClassID& GetToolType() const;

		/**	Set tool type. This type determines which tools are mutually exclusive. The ClassID for the tool type is defined to be the ClassID of the 
			default tool for that type. Traditional tools in the toolbox have a tooltype of kPointerToolBoss. This method is fully implemented by CTool.
			Subclasses usually have no need to override.
		*/
		virtual void SetToolType(const ClassID& newToolType);

		/**	Get action for shortcut for selecting tool. This method is fully implemented by CTool.
			Subclasses usually have no need to override.
		*/
		virtual ActionID GetActionID() const; 		

		/**	Set action for shortcut for selecting tool. This method is fully implemented by CTool.
			Subclasses usually have no need to override.
		*/
		virtual void SetActionID(ActionID action);
		
		/**	Display some UI for users to choose tool options. CTool does not implement. Subclasses that have options they'd like to display typically implement this method
			to invoke some sort of options dialog.
		*/
		virtual void DisplayOptions();

		/**	Display some UI for users to choose additional tool options. CTool does not implement. Subclasses that have a second set of options they'd like to display typically implement this method
			to invoke some sort of options dialog.
		*/
		virtual void DisplayAltOptions();

		/**	Check if this tool matches the desired type. Implemented by CTool, based on the toolInformation bitfield passed into the constructor by subclasses.
		*/
		virtual bool16 IsToolOfType(ITool::ToolType toolInformation) const;
	
		/** Returns the ScriptID associated with this particular tool such that
		 scripts can ask the toolBox for the ScriptID of the current tool. The
		 list of ScriptIDs for the toolbox tools are defined by en_ToolBoxTools 
		 (kToolBoxEnumScriptElement).
		 @return the ScriptID associated with this tool in the en_ToolBoxTools enumeration
		 */
		virtual ScriptID GetScriptID() const { ASSERT_UNIMPLEMENTED(); return en_None; }

		/**  Returns bool16 whether the tool is this none tool i.e. ITool::kNone
		@return kTrue if the given tool is of  type ITool::kNone
		*/
		virtual bool16 IsToolNone() const;
	
	protected:
		ICursorProvider* fCursorProvider;
		bool16 fIsCreation;
		bool16 fIsSelection;
		ClassID fToolType;
		int32 fToolInformation;			// bit field containing the information about what tool type this is
		bool fSelected;
		virtual PMString BuildHintString(PMString& theDescriptionString, PMString& theShiftHint, PMString& theCommandCtrlHint, PMString& theOptionAltHint, PMString& theArrowsHint, PMString& extrasString);
		virtual PMString BuildHintString(PMString& theDescriptionString, PMString& theShiftHint, PMString& theCommandCtrlHint, PMString& theOptionAltHint, PMString& theArrowsHint, K2Vector<PMString>& theExtraModifiersHint, PMString& extrasString);
	
	private:
		ActionID fActionID;
		PMString fName;
		PMString fToolHint;
		IDFile fToolIconFile;
		int32 fIconID;

DECLARE_HELPER_METHODS()
};

#pragma export off

#endif