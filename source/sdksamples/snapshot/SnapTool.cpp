//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snapshot/SnapTool.cpp $
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

#include "ISession.h"
#include "IApplication.h"
#include "IDialogMgr.h"
#include "IDialog.h"

// General includes:
#include "CoreResTypes.h"
#include "LocaleSetting.h"
#include "PMLocaleIds.h"
#include "SnapScriptingDefs.h"

#include "RsrcSpec.h"
#include "CTool.h"

#include "SnapID.h"

/**
	The SnapTool's ITool implementation based on the partial implementation of CTool.

	
	@ingroup snapshot
*/
class SnapTool: public CTool
{
	public:
		/** Constructor for the SnapTool */
		SnapTool(IPMUnknown* boss);

		/** Set the tool's name and initialise the tool's button widget */
		virtual void Init(RsrcID iconID, const PluginID& pluginID);

		/** Display a dialog */		
		void DisplayOptions(); 

		/** Returns a ScriptID that identifies the tool.
		*/
		virtual ScriptID GetScriptID() const;
};

/*
 CREATE_PMINTERFACE
 This macro creates a class factory for the given class name
 and registers the ID with the host.
*/
CREATE_PERSIST_PMINTERFACE(SnapTool, kSnapToolImpl)

/*
 Constructor for SnapTool class.
 CTool constructor parameters: boss, tool type, isCreation, isSelection
*/
SnapTool::SnapTool(IPMUnknown* boss) :
	CTool(boss, kLayoutSelectionTool, kFalse, kTrue)
{
}

/*	Init.
	Set the tool's name and initialise the tool's button icon.
*/
void SnapTool::Init(RsrcID iconID, const PluginID& pluginID)
{	
	SetName(kSnapStringKey);
	InitWidget(kSnapWidgetID, iconID, pluginID);
}

/*	DisplayOptions
*/
void SnapTool::DisplayOptions() 
{
	// Get the applicaton interface and the DialogMgr:	
	InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IDialogMgr> dialogMgr(app, IID_IDIALOGMGR);

	// We need to load the plug-ins resource:
	PMLocaleId nLocale = LocaleSetting::GetLocale();
	RsrcSpec dialogSpec
	(
		nLocale,					// Locale index from PMLocaleIDs.h. 
		kSnapPluginID,		// Our Plug-in ID from SnapshotID.h. 
		kViewRsrcType,				// This is the kViewRsrcType.
		kSDKDefDialogResourceID,			// Resource ID for our dialog.
		kTrue						// Initially visible.
	);

	// CreateNewDialog takes the dialogSpec created above, and also
	// the type of dialog being created (kMovableModal).
	IDialog* dialog = dialogMgr->CreateNewDialog(dialogSpec, IDialog::kMovableModal);
	if (dialog == nil)
		ASSERT_FAIL("can't create Dialog");
	else
		dialog->Open();		
}

ScriptID SnapTool::GetScriptID() const 
{
	return en_SnapTool; 
}

// End, SnapTool.cpp.


