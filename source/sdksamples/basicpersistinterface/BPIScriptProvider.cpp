//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicpersistinterface/BPIScriptProvider.cpp $
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
#include "ILayoutTarget.h"

// General includes:
#include "CScriptProvider.h"

#include "Utils.h"
#include "GenericID.h"

// Project includes:
#include "BPIID.h"
#include "BPIScriptingDefs.h"
#include "BPIHelper.h"

/** From SDK sample; Handles scripting of the BasicPersistInterface's data property
	(p_BPIData) added onto page items in interface IBPIData. See the Provider
	statement for kBPIScriptProviderBoss in BPI.fr for the list of scripting objects
	on which the p_BPIData property is available.

	@ingroup basicpersistinterface
 */
class BPIScriptProvider : public CScriptProvider
{
public:
	/**	Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	 */
	BPIScriptProvider(IPMUnknown* boss): CScriptProvider(boss) {}

	/**	Destructor.
	 */
	~BPIScriptProvider() {}

	/** Called if a provider can handle a method/event.
		@param methodID identifies the ID of the method/event to handle.
		@param data identifies an interface pointer used to extract data.
		@param script identifies an interface pointer on the script object representing the parent of the application object.
	 */
	virtual ErrorCode  HandleMethod(ScriptID methodID, IScriptRequestData* data, IScript* script);    

	/** Called if a provider can handle a property.
		@param propID identifies the ID of the property to handle.
		@param data identifies an interface pointer used to extract data.
		@param script identifies an interface pointer on the script object representing the parent of the application object.
	 */
	virtual ErrorCode  AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script);

private:
	/** Set or get the value of IBPIData on a page item.
		@param propID identifies the ID of the property to handle (p_BPIData).
		@param data identifies an interface pointer used to extract parameter data.
		@param script identifies an interface pointer on a type of page item script object.
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
CREATE_PMINTERFACE(BPIScriptProvider, kBPIScriptProviderImpl)

/*
*/
ErrorCode BPIScriptProvider::HandleMethod(ScriptID methodID, IScriptRequestData* data, IScript* script)
{
	// No events.
	return CScriptProvider::HandleMethod(methodID, data, script);
}

/*
*/
ErrorCode BPIScriptProvider::AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;
	do
	{
		switch (propID.Get())
		{
			case p_BPIData:
			{
				result = this->AccessBPIDataProperty(propID, data, script);
				break;
			}

			default:
			{
				result = CScriptProvider::AccessProperty(propID, data, script);
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
ErrorCode BPIScriptProvider::AccessBPIDataProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;
	do {
		// The script object identifies the page item whose IBPIData is to be changed.
		UIDList target(script);
		BPIHelper bpiHelper;
		if (!bpiHelper.HasBPIData(target)) {
			result = kInvalidScriptTargetError;
			break;
		}
		if (data->IsPropertyPut()) {
			// Get the IBPIData value passed by the script.
			WideString value;
			result = this->GetWideString(value, propID, data);
			if (result == kSuccess) {
				// Set the IBPIData value.
				result = bpiHelper.ProcessBPISetDataCmd(target, value);
			}
		}
		else if (data->IsPropertyGet()) {
			// Get the IBPIData value.
			WideString value;
			K2Vector<WideString> values;
			bpiHelper.GetBPIData(target, values);
			if (values.size() > 0) {
				value = values [0];
				
			}
			else {
				value = WideString(" ");
			}
			// Return the value to the caller.
			ScriptData outputData;
			outputData.SetWideString(value);
			data->AppendReturnData( script, propID, outputData ) ;	
			result = kSuccess;
		}
	} while (false);
	if (result == kFailure) {
		result = kBPIFailureErrorCode;
	}
	return result;
}


/*
*/
ErrorCode BPIScriptProvider::GetWideString(WideString& value, const ScriptID& scriptID, IScriptRequestData* data, bool16 isRequired) const
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

// BPIScriptProvider.cpp
