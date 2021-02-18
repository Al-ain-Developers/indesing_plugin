//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/wavetool/SawWaveTool.cpp $
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

// General includes:
#include "CTool.h"
#include "WavTlScriptingDefs.h"

// Project includes:
#include "WavTlID.h"

/** Provides the behaviour of the saw wave tool's button.
	
	@ingroup wavetool
*/
class SawWaveTool: public CTool
{
	public:
		/** Constructor. 
		 */
		SawWaveTool(IPMUnknown *boss);
		/** Set the tool's name and initialise the tool's button widget.
		 */
		virtual void Init(RsrcID iconID, const PluginID& pluginID);

		/** Returns a ScriptID that identifies the tool.
		*/
		virtual ScriptID GetScriptID() const;
};

/* Make the implementation available to the application.
*/
CREATE_PERSIST_PMINTERFACE(SawWaveTool, kSawWaveToolImpl)

/*
*/
SawWaveTool::SawWaveTool(IPMUnknown *boss) : CTool(boss, 
		kLayoutCreationTool,	// ITool::ToolType
		kTrue,					// isCreation
		kFalse)					// isSelection
{
}

/*
*/
void SawWaveTool::Init(RsrcID iconID, const PluginID& pluginID)
{	
	this->SetName(kSawWaveToolStringKey);
	this->InitWidget(kSawWaveToolWidgetID, iconID, pluginID);
}

ScriptID SawWaveTool::GetScriptID() const 
{
	return en_SawWaveTl; 
}


// End, SawWaveTool.cpp.



