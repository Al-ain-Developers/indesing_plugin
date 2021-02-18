//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/inxerrorlogging/INXErrLogScriptProvider.cpp $
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
#include "IStringData.h"

// General includes:
#include "CScriptProvider.h"
#include "Utils.h"
#include "GenericID.h"

// Project includes:
#include "iinxerrlogfacade.h"
#include "INXErrLogID.h"
#include "INXErrLogScriptingDefs.h"



/** From SDK sample; Handles scripting of the InxErrLogScript's attributes properties. See the Provider
	statement for kINXErrLogScriptProviderBoss in INXErrlog.fr for the list of scripting objects.

	@ingroup inxerrorlogging
 */
class INXErrLogScriptProvider : public CScriptProvider
{
public:
	/**	Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	 */
	INXErrLogScriptProvider(IPMUnknown* boss): CScriptProvider(boss) {}

	/**	Destructor.
	 */
	~INXErrLogScriptProvider() {}

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

	ErrorCode AccessINXErrLogPathProperty(ScriptID propID, IScriptRequestData* data, IScript* script);

	ErrorCode AccessINXErrLogOnOffProperty(ScriptID propID, IScriptRequestData* data, IScript* script);
	/** Get the given boolean parameter from the script event data.
        @param value OUT the parameter value
        @param scriptID IN identifies the desired parameter
        @param data IN the script event data
        @param isRequired kTrue if required, kFalse if optional
        @return kSuccess on success, other ErrorCode otherwise
    */
    ErrorCode GetBool(bool16& value, const ScriptID& scriptID, IScriptRequestData* data, bool16 isRequired = kTrue) const;

    /** Get the given string parameter from the script event data.
        @param value OUT the parameter value
        @param scriptID IN identifies the desired parameter
        @param data IN the script event data
        @param isRequired kTrue if required, kFalse if optional
        @return kSuccess on success, other ErrorCode otherwise
    */
    ErrorCode GetPMString(PMString& value, const ScriptID& scriptID, IScriptRequestData* data, bool16 isRequired = kTrue) const;

};

/*	Make the implementation available to the application.
*/
CREATE_PMINTERFACE(INXErrLogScriptProvider, kINXErrLogScriptProviderImpl)

/*
*/
ErrorCode INXErrLogScriptProvider::HandleMethod(ScriptID methodID, IScriptRequestData* data, IScript* script)
{
	// No events.
	return CScriptProvider::HandleMethod(methodID, data, script);
}

/*
*/
ErrorCode INXErrLogScriptProvider::AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;
	do
	{
		switch (propID.Get())
		{
			case p_INXErrLogOnOff:
			{
				result = this->AccessINXErrLogOnOffProperty(propID, data, script);

				break;
			}

			case p_INXErrLogPath:
			{
				result = this->AccessINXErrLogPathProperty(propID, data, script);
				break;
			}


			default:
			{
				result = CScriptProvider::AccessProperty(propID, data, script);
				break;
			}
		}
	} while (false);
	return result;
}

/*
*/
ErrorCode INXErrLogScriptProvider::AccessINXErrLogOnOffProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;

	do {
		bool16 value = kFalse;
		if (data->IsPropertyPut()) {			
			result = this->GetBool(value, propID, data);				
			if (result != kSuccess) {
				break;
			}
			if(value == kTrue){
				Utils<IINXErrLogFacade>()->CreateINXErrorHandler();
			}
			else{
				Utils<IINXErrLogFacade>()->ClearINXErrorHandler();
			}
		}
		else if (data->IsPropertyGet()) {
			Utils<IINXErrLogFacade>()->GetINXErrorHandlerState(value);					
			ScriptData outputData;
			outputData.SetBoolean(value);			
			data->AppendReturnData( script, propID, outputData);
			result = kSuccess;
		}
	} while (false);

	return result;
}


/*
*/
ErrorCode INXErrLogScriptProvider::AccessINXErrLogPathProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;

	do {
		PMString value;
		if (data->IsPropertyPut()) {
			result = this->GetPMString(value, propID, data);	
			Utils<IINXErrLogFacade>()->SetBaseINXErrorHandlerPath(value);
		}
		else if (data->IsPropertyGet()) {
			Utils<IINXErrLogFacade>()->GetBaseINXErrorHandlerPath(value);	
			ScriptData outputData;
			outputData.SetPMString(value);
			data->AppendReturnData( script, propID, outputData);
			result = kSuccess;			
		}		
	} while (false);

	return result;
}

/* GetBool
*/
ErrorCode INXErrLogScriptProvider::GetBool(bool16& value, const ScriptID& scriptID, IScriptRequestData* data, bool16 isRequired) const
{
    ErrorCode result = kFailure;
    do {
        ASSERT(data);
        ScriptData inputdata;
        result = data->ExtractRequestData(scriptID, inputdata);
        if (result != kSuccess) {
            break;
        }
        inputdata.GetBoolean(&value);
    } while(false);
    if (result != kSuccess && isRequired) {
        result = Utils<IScriptErrorUtils>()->SetMissingRequiredParameterErrorData(data, scriptID);
    }
    return result;
}

/* GetPMString
*/
ErrorCode INXErrLogScriptProvider::GetPMString(PMString& value, const ScriptID& scriptID, IScriptRequestData* data, bool16 isRequired) const
{
    ErrorCode result = kFailure;
    do {
        ASSERT(data);
        ScriptData inputdata;
        result = data->ExtractRequestData(scriptID, inputdata);
        if (result != kSuccess) {
            break;
        }
        inputdata.GetPMString(value);
    } while(false);
    if (result != kSuccess && isRequired) {
        result = Utils<IScriptErrorUtils>()->SetMissingRequiredParameterErrorData(data, scriptID);
    }
    return result;
}


// INXErrLogScriptProvider.cpp