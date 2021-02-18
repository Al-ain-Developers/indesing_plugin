//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicpersistinterface/BPIPrefsScriptProvider.cpp $
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

// Interface includes:
#include "IScriptRequestData.h"
#include "IDocument.h"
#include "IScriptUtils.h"
#include "IWorkspace.h"

// General includes:
#include "PrefsScriptProvider.h"

#include "Utils.h"

// Project includes:
#include "BPIID.h"
#include "BPIScriptingDefs.h"
#include "IBPISuite.h"

/** From SDK sample; Handles scripting of BasicPersistInterface preference
	that stores the default value of the p_BPIData property used to label
	page items. The Provider statement for kBPIPrefsScriptProviderBoss 
	in BPI.fr adds the preferences into the application and the document
	scripting objects. Consequently this script provider is passed an IScript interface
	on a kWorkspaceBoss or kDocWorkspaceBoss.

	@ingroup basicpersistinterface
 */
class BPIPrefsScriptProvider : public PrefsScriptProvider
{
public:
	/**	Constructor.
		@param boss interface pointer from boss object on which this interface is aggregated.
	 */
	BPIPrefsScriptProvider(IPMUnknown* boss);

	/**	Destructor.
	 */
	~BPIPrefsScriptProvider() {}

	/** Called if a provider can handle a property.
		@param propID identifies the ID of the property to handle.
		@param data identifies an interface pointer used to extract data.
		@param script identifies an interface pointer on a script object.
	 */
	virtual ErrorCode  AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script);
 
private:

	/** Set or get the value of IBPIData preference.
		@param propID identifies the ID of the property to handle (p_BPIData).
		@param data identifies an interface pointer used to extract parameter data.
		@param script identifies an interface pointer on a workspace script object.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode AccessBPIDataProperty(ScriptID propID, IScriptRequestData* data, IScript* script);	
	
private:
	/** Get the given WideString parameter from the script event data.
		@param value OUT the parameter value
		@param scriptID IN identifies the desired parameter
		@param data IN the script event data
		@param isRequired kTrue if required, kFalse if optional
		@return kSuccess on success, other ErrorCode otherwise
	*/
	ErrorCode GetWideString(WideString& value, const ScriptID& scriptID, IScriptRequestData* data, bool16 isRequired = kTrue) const;
};

/*	Make the implementation available to the application.
*/
CREATE_PMINTERFACE(BPIPrefsScriptProvider, kBPIPrefsScriptProviderImpl)

/*
*/
BPIPrefsScriptProvider::BPIPrefsScriptProvider(IPMUnknown* boss) : PrefsScriptProvider(boss)
{
	// Make the base class aware of the BasicPersistInterface's preferences scripting object.
	// The based will take care of creating a proxy script object when the preference
	// object is accessed.
	DefinePreference(c_BPIPref, p_BPIPref);
}

/*
*/
ErrorCode BPIPrefsScriptProvider::AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;
	do {
		switch (propID.Get())
		{
			case p_BPIData:
			{
				result = this->AccessBPIDataProperty(propID, data, script);
				break;
			}
				
			default:
			{
				result = PrefsScriptProvider::AccessProperty(propID, data, script);
				break;
			}
		}
	} while (false);
	if (result == kFailure) {
		result = kBPIFailureErrorCode;
	}
	return result;
}

/*
*/
ErrorCode BPIPrefsScriptProvider::AccessBPIDataProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;
	do {
		// Preferences are stored on the workspace so check we have a workspace.
		InterfacePtr<IWorkspace> workspace(Utils<IScriptUtils>()->QueryWorkspaceFromScript( script, data->GetRequestContext() ));
		ASSERT(workspace);
		if (!workspace) {
			result = kInvalidScriptTargetError;
			break;
		}
		// IBPISuite should be available on a workspace.
		// We added it in to kApplicationDefaultSuiteBoss and kDocumentDefaultSuiteBoss,
		// The workspace boss classes sub-class these suite boss clases so we
		// acquire a reference to IBPISuite and use it to change BasicPersistInterface preferences.
		InterfacePtr<IBPISuite> bpiSuite(workspace, UseDefaultIID());
		ASSERT(bpiSuite);
		if (!bpiSuite) {
			result = kInvalidScriptTargetError;
			break;
		}	
		if (data->IsPropertyPut())
		{
			// Get the IBPIData value passed by the script.
			WideString value;
			result = this->GetWideString(value, propID, data);
			if (result == kSuccess) {
				// Set the default IBPIData string value in the preferences.
				if (bpiSuite->CanApplyBPIData()) {
					result = bpiSuite->ApplyBPIData(value);
				}
				else {
					result = kBPIDataAccessErrorCode;
				}
			}
		}
		else if (data->IsPropertyGet()) 
		{
			// Get the default IBPIData string value from the preferences.
			WideString value;
			if (bpiSuite->CanGetBPIData()) {
				K2Vector<WideString> values;
				bpiSuite->GetBPIData(values);
				if (values.size() > 0) {
					value = values [0];
					
				}
			}
			else {
				value = WideString(" ");
			}
			// Pass the default IBPIData value back to the caller.
			ScriptData outputData;
			outputData.SetWideString(value);
			data->AppendReturnData( script, propID, outputData ) ;
			result = kSuccess;
		}
	} while(false);
	return result;
}

/*
*/
ErrorCode BPIPrefsScriptProvider::GetWideString(WideString& value, const ScriptID& scriptID, IScriptRequestData* data, bool16 isRequired) const
{
	ErrorCode result = kFailure;
	do {
		ASSERT(data);
		ScriptData inputdata;
		result = data->ExtractRequestData(scriptID, inputdata);
		if (result != kSuccess) {
			break;
		}
		result = inputdata.GetWideString(value);
	} while(false);
	if (result != kSuccess && isRequired) {
		result = Utils<IScriptErrorUtils>()->SetMissingRequiredParameterErrorData(data, scriptID);
	}
	return result;
}

// BPIPrefsScriptProvider.cpp
