//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/paneltreeview/PnlTrvScriptProvider.cpp $
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

#include "VCPlugInHeaders.h"
#include "PrefsScriptProvider.h"
#include "PnlTrvScriptingDefs.h"
#include "ScriptingDefs.h"
#include "ScriptingID.h"
#include "CmdUtils.h"
#include "PnlTrvUtils.h"
#include "UIDList.h"

#include "ICommand.h"
#include "IPnlTrvOptions.h"
#include "IPnlTrvChangeOptionsCmdData.h"
#include "IScript.h"
#include "IScriptRequestData.h"
#include "IWorkspace.h"

#include "PnlTrvID.h"

/** Provides scripting support by means of handling events and property 
 * 	accesses that are delegated by the script manager. 
 * 	@ingroup persistentlist
*/
class PnlTrvScriptProvider : public PrefsScriptProvider
{
public:

	/**
		Constructor 
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	PnlTrvScriptProvider(IPMUnknown *boss);

	/**
		Destructor.  
	*/
	~PnlTrvScriptProvider();

	/** Processes a property access. This call further delegates to the private method AccessFolder.
	 * 	@see IScriptProvider::AccessProperty
	 */
	int32 AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script);

private:

	/** Gets or sets the the panel tree view folder option. 
	 */
	int32 AccessFolder(IScriptRequestData* data, IScript* script);

};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(PnlTrvScriptProvider, kPnlTrvScriptProviderImpl);

/* PnlTrvScriptProvider Constructor
*/
PnlTrvScriptProvider::PnlTrvScriptProvider(IPMUnknown *boss) : 
	PrefsScriptProvider(boss)
{
	DefinePreference( c_PnlTrvPreferences, p_PnlTrvPreferences ) ;
}

/* PnlTrvScriptProvider Destructor
*/
PnlTrvScriptProvider::~PnlTrvScriptProvider()
{
}

/* AccessProperty
*/
int32 PnlTrvScriptProvider::AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{
	int32 result=kSuccess;

	switch (propID.Get())
	{

	case p_Path:
			result = AccessFolder(data, script);
			break;
		
		default:
			return PrefsScriptProvider::AccessProperty(propID, data, script);
	}

	return result;
}

/* AccessFolder
*/
int32 PnlTrvScriptProvider::AccessFolder(IScriptRequestData* data, IScript* script)
{
	ScriptData scriptData;

	if (data->IsPropertyGet())
	{
		// Get the property from the options
		PMString folderRootPath = PnlTrvUtils::GetFolderSelectedPath();
		if(folderRootPath.empty()) {
			return kPnlTrvFolderNotSetError;
		}
		
		// stuff it into the return data
		scriptData.SetPMString( folderRootPath );
		data->AppendReturnData( script, p_Path, scriptData ) ;
	}
	else if (data->IsPropertyPut())
	{
		// extract the path from the event data
		WideString newFolder;
		ErrorCode err = data->ExtractRequestData(p_Path, scriptData);
		err = scriptData.GetWideString(newFolder);
		if (err != kSuccess)
			return err;

		// query for the IPnlTrvOptions which controls the panels folder option
		InterfacePtr<IWorkspace>
			iSessionWorkspace(GetExecutionContextSession()->QueryWorkspace());
		InterfacePtr<IPnlTrvOptions>
			iOptions(iSessionWorkspace, UseDefaultIID());
		ASSERT(iOptions);
		if(!iOptions)
		{
			return kFailure;
		}

		// Process a command to set the options
		InterfacePtr<ICommand>
			modOptionsCmd (CmdUtils::CreateCommand(kPnlTrvChangeOptionsCmdBoss));
		ASSERT(modOptionsCmd);
		if(!modOptionsCmd)
		{
			return kFailure;
		}	
		modOptionsCmd->SetItemList(UIDList(iSessionWorkspace));

		InterfacePtr<IPnlTrvChangeOptionsCmdData>
			cmdData (modOptionsCmd, UseDefaultIID());
		ASSERT(cmdData);
		if (cmdData == nil)
		{
			return kFailure;
		}
		cmdData->AddOption(newFolder);	// template path
		
		return CmdUtils::ProcessCommand(modOptionsCmd);
	}
	return kSuccess;
}

