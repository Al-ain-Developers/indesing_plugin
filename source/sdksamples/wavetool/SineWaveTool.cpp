//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/wavetool/SineWaveTool.cpp $
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

/** Provides the behaviour of the sine wave tool's button.
	@ingroup wavetool
	
 */
class SineWaveTool: public CTool
{
	public:
		/** Constructor.
		 */
		SineWaveTool(IPMUnknown *boss);
		/** Set the tool's name and initialise the tool's
			button icon.
		 */
		virtual void Init(RsrcID iconID, const PluginID& pluginID);

		/** Returns a ScriptID that identifies the tool.
		*/
		virtual ScriptID GetScriptID() const;
};

/*  Make the implementation available to the application.
*/
CREATE_PERSIST_PMINTERFACE(SineWaveTool, kSineWaveToolImpl)

/*
*/
SineWaveTool::SineWaveTool(IPMUnknown *boss) : CTool(boss, 
		kLayoutCreationTool,	// ITool::ToolType
		kTrue,					// isCreation
		kFalse)					// isSelection
{
}

/*
*/
void SineWaveTool::Init(RsrcID iconID, const PluginID& pluginID)
{
	this->SetName(kSineWaveToolStringKey);
	this->InitWidget(kSineWaveToolWidgetID, iconID, pluginID);
}

ScriptID SineWaveTool::GetScriptID() const 
{
	return en_SineWaveTl; 
}

// End, SineWaveTool.cpp.



