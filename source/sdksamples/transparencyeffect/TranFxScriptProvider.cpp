//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/transparencyeffect/TranFxScriptProvider.cpp $
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

// General includes:
#include "PrefsScriptProvider.h"

#include "Utils.h"
#include "UIDList.h" // UIDList
// Project includes:
#include "TranFxID.h"
#include "TranFxScriptingDefs.h"
#include "TranFxUtils.h"
#include "ITranFxSuite.h"
#include "IGraphicFrameData.h"
#ifdef DEBUG
#include "DebugClassUtils.h"
#endif

/** From SDK sample, implements IScriptProvider.

	@ingroup transparencyeffect
 */
class TranFxScriptProvider : public PrefsScriptProvider
{
public:
	/**	Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	 */
	TranFxScriptProvider(IPMUnknown* boss);

	/**	Destructor.
	 */
	~TranFxScriptProvider() {}

	/** Called if a provider can handle a property.
		@param propID identifies the ID of the property to handle.
		@param data identifies an interface pointer used to extract data.
		@param script identifies an interface pointer on the script object representing the parent of the application object.
	 */
	virtual ErrorCode  AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script);

	
	
protected:
	ErrorCode GetTransparencyEffectProperty(IScript*script, const ScriptID& propID, IScriptRequestData* data);
	ErrorCode SetTransparencyEffectProperty(IScript*script, const ScriptID& propID, IScriptRequestData* data);
	/** Get the given boolean parameter from the script event data.
		@param value OUT the parameter value
		@param scriptID IN identifies the desired parameter
		@param data IN the script event data
		@param isRequired kTrue if required, kFalse if optional
		@return kSuccess on success, other ErrorCode otherwise
	*/
	ErrorCode GetBool(bool16& value, const ScriptID& scriptID, IScriptRequestData* data, bool16 isRequired = kTrue) const;
	ErrorCode GetPMReal(PMReal& outValue, const ScriptID& scriptID, IScriptRequestData* data, bool16 isRequired = kTrue) const;
	ErrorCode GetEnumeration(ScriptID& outValue, const ScriptID& scriptID, IScriptRequestData* data, bool16 isRequired = kTrue) const;

	/** Return the IScript interface of the given object parameter in the script event data.
		@param scriptID identifies the desired parameter
		@param data the script event data
		@param isRequired kTrue if required, kFalse if optional
		@return IScript interface of the desired object, nil if not found in the script data.
	*/
	IScript* QueryScript(const ScriptID& scriptID, IScriptRequestData* data, bool16 isRequired = kTrue) const;

};

/*	Make the implementation available to the application.
*/
CREATE_PMINTERFACE(TranFxScriptProvider, kTranFxScriptProviderImpl)

TranFxScriptProvider::TranFxScriptProvider(IPMUnknown* boss) : PrefsScriptProvider(boss)
{
	// Make the base class aware of the tranfx-settings scripting object.
	// The base class will take care of creating the object associated with ScriptID
	// p_TranFxSettings when this property when is accessed.
	DefinePreference(c_TranFxSettings, p_TranFxSettings);
}



/*
*/
ErrorCode TranFxScriptProvider::AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{
	
	ErrorCode result = kFailure;
	do
	{
	
#ifdef DEBUG  
		ASSERT(script);
		if(!script) {
			break;
		}
		InterfacePtr<IScript> parentScript((IScript*)script->QueryParent(IScript::kDefaultIID, data->GetRequestContext() ));
		ASSERT(parentScript);
		if(!parentScript) {
			break;
		}
		
         {
             DebugClassUtilsBuffer classBuf;
             const char* className = 
                 DebugClassUtils::GetIDName(&classBuf, ::GetClass(script));
            TRACEFLOW(kTranFxPluginName, 
				"\t\t==> TranFxScriptProvider::AccessProperty Script obj class=%s\n", className); 
         }
		 {
             DebugClassUtilsBuffer classBuf;
             const char* className = 
                 DebugClassUtils::GetIDName(&classBuf, ::GetClass(parentScript));
            TRACEFLOW(kTranFxPluginName, 
				"\t\t==> TranFxScriptProvider::AccessProperty parentScript class=%s\n", className); 
         }

		 {
			 PMString fcc = Utils<IScriptUtils>()->GetScriptID(propID);

		TRACEFLOW(kTranFxPluginName, 
			"\t\t==> TranFxScriptProvider::AccessProperty ScriptID (fcc) = %s\n", fcc.GetUTF8String().c_str());
		 }
 #endif		
		switch (propID.Get())
		{
			
			case p_TranFxMode:
			case p_TranFxOffsetX:
			case p_TranFxOffsetY:
			case p_TranFxUseBlackAsOpaque:
			case p_TranFxUseAlpha:
			case p_TranFxUseBlur:
			{
				ASSERT(data);
				if(!data) {
					break;
				}
				if (data->IsPropertyGet())
				{
					result = this->GetTransparencyEffectProperty(script, propID, data);
				}	
				else if (data->IsPropertyPut())
				{
					result = this->SetTransparencyEffectProperty(script, propID, data);
						
				}
			} 
			break;

			default:
			{
				result = PrefsScriptProvider::AccessProperty(propID, data, script);
				break;
			}
		}
	} while (false);
	return result;
}


/*
*/
ErrorCode TranFxScriptProvider::GetBool(bool16& value, const ScriptID& scriptID, IScriptRequestData* data, bool16 isRequired) const
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
ErrorCode TranFxScriptProvider::GetPMReal(PMReal& outValue, const ScriptID& scriptID, IScriptRequestData* data, bool16 isRequired) const
{
	ErrorCode result = kFailure;
	do {
		ASSERT(data);
		ScriptData inputdata;
		result = data->ExtractRequestData(scriptID, inputdata);
		if (result != kSuccess) {
			break;
		}
		inputdata.GetPMReal(&outValue);
	} while(false);
	if (result != kSuccess && isRequired) {
		result = Utils<IScriptErrorUtils>()->SetMissingRequiredParameterErrorData(data, scriptID);
	}
	return result;
}


/*
*/
ErrorCode TranFxScriptProvider::GetEnumeration(ScriptID& value, const ScriptID& scriptID, IScriptRequestData* data, bool16 isRequired) const
{
	ErrorCode result = kFailure;
	do {
		ASSERT(data);
		ScriptData inputdata;
		result = data->ExtractRequestData(scriptID, inputdata);
		if (result != kSuccess) {
			break;
		}
		result = inputdata.GetEnumeration(&value);
	} while(false);
	if (result != kSuccess && isRequired) {
		result = Utils<IScriptErrorUtils>()->SetMissingRequiredParameterErrorData(data, scriptID);
	}
	return result;

}
/*
*/
IScript* TranFxScriptProvider::QueryScript(const ScriptID& scriptID, IScriptRequestData* data, bool16 isRequired) const
{
	InterfacePtr<IScript> result;
	if (data != nil) {
		ScriptData inputdata;
		if (data->ExtractRequestData(scriptID, inputdata) == kSuccess) {
			result.reset(inputdata.QueryObject());
		}
	}
	if (result == nil && isRequired) {
		Utils<IScriptErrorUtils>()->SetMissingRequiredParameterErrorData(data, scriptID);
	}
	return result.forget();
}


ErrorCode TranFxScriptProvider::GetTransparencyEffectProperty(IScript* script, 
															  const ScriptID& propID, 
															  IScriptRequestData* data)
{
	ErrorCode result = kFailure;
	do {
		ASSERT(script);
		if(!script) {
			break;
		}
		InterfacePtr<IScript> parentScript((IScript*)script->QueryParent(IScript::kDefaultIID, data->GetRequestContext() ));
		ASSERT(parentScript);
		if(!parentScript) {
			break;
		}
#ifdef DEBUG    
         {
             DebugClassUtilsBuffer classBuf;
             const char* className = 
                 DebugClassUtils::GetIDName(&classBuf, ::GetClass(script));
            TRACEFLOW(kTranFxPluginName, 
				"\t\t==> TranFxScriptProvider::GetTransparencyEffectProperty Script obj class=%s\n", className); 
         }
		 {
             DebugClassUtilsBuffer classBuf;
             const char* className = 
                 DebugClassUtils::GetIDName(&classBuf, ::GetClass(parentScript));
            TRACEFLOW(kTranFxPluginName, 
				"\t\t==> TranFxScriptProvider::GetTransparencyEffectProperty parentScript class=%s\n", className); 
         }
 #endif		

		TranFxUtils fxUtils;
		switch(propID.Get())
		{
			
			case p_TranFxMode:
			{
				UIDList itemList(parentScript);
				bool16 hasOurAdornment = fxUtils.HasAdornment(itemList);
				ScriptData outputData;
				outputData.SetBoolean(hasOurAdornment);
				data->AppendReturnData( script, propID, outputData ) ;
				result = kSuccess;
				TRACEFLOW(kTranFxPluginName, 
					"\t\t==> TranFxScriptProvider::GetTransparencyEffectProperty (p_TranFxMode)\n");
			}
			break;

			case p_TranFxOffsetX:
			{
				UIDList itemList(parentScript);
				PMReal xOffset(0.0);
				TranFxUtils::AttrState state = fxUtils.HasXOffset(itemList, xOffset);
				if(state != TranFxUtils::eCommonValue) {
					xOffset = 0.0;
				}
				ScriptData outputData;
				outputData.SetPMReal(xOffset);
				data->AppendReturnData( script, propID, outputData ) ;
				result = kSuccess;
				TRACEFLOW(kTranFxPluginName, 
					"\t\t==> TranFxScriptProvider::GetTransparencyEffectProperty (p_TranFxOffsetX)\n");
				
			}
			break;

			case p_TranFxOffsetY:
			{
				UIDList itemList(parentScript);
				PMReal yOffset(0.0);
				TranFxUtils::AttrState state = fxUtils.HasYOffset(itemList, yOffset);
				if(state != TranFxUtils::eCommonValue) {
					yOffset = 0.0;
				}
				ScriptData outputData;
				outputData.SetPMReal(yOffset);
				data->AppendReturnData( script, propID, outputData ) ;
				result = kSuccess;
				TRACEFLOW(kTranFxPluginName, 
					"\t\t==> TranFxScriptProvider::GetTransparencyEffectProperty (p_TranFxOffsetY)\n");
			
			}
			break;

			case p_TranFxUseBlackAsOpaque:
			{
				UIDList itemList(parentScript);
				bool16 useBlack = kFalse;
				TranFxUtils::AttrState state = fxUtils.HasUseBlackAsOpaque(itemList, useBlack);
				if(state != TranFxUtils::eCommonValue) {
					useBlack = kFalse;
				}
				ScriptData outputData;
				outputData.SetBoolean(useBlack);
				data->AppendReturnData( script, propID, outputData ) ;
				result = kSuccess;
				TRACEFLOW(kTranFxPluginName, 
					"\t\t==> TranFxScriptProvider::GetTransparencyEffectProperty (p_TranFxUseBlackAsOpaque)\n");
			}
			break;

			case p_TranFxUseAlpha:
			{
				UIDList itemList(parentScript);
				bool16 useAlpha = kFalse;
				TranFxUtils::AttrState state = fxUtils.HasUseAlpha(itemList, useAlpha);
				if(state != TranFxUtils::eCommonValue) {
					useAlpha = kFalse;
				}
				ScriptData outputData;
				outputData.SetBoolean(useAlpha);
				data->AppendReturnData( script, propID, outputData ) ;
				result = kSuccess;
				TRACEFLOW(kTranFxPluginName, 
					"\t\t==> TranFxScriptProvider::GetTransparencyEffectProperty (p_TranFxUseAlpha)\n");

			}
			break;

			case p_TranFxUseBlur:
			{
				UIDList itemList(parentScript);
				bool16 useBlur = kFalse;
				TranFxUtils::AttrState state = fxUtils.HasUseBlur(itemList, useBlur);
				if(state != TranFxUtils::eCommonValue) {
					useBlur = kFalse;
				}
				ScriptData outputData;
				outputData.SetBoolean(useBlur);
				data->AppendReturnData( script, propID, outputData ) ;
				result = kSuccess;
				TRACEFLOW(kTranFxPluginName, 
					"\t\t==> TranFxScriptProvider::GetTransparencyEffectProperty (p_TranFxUseBlur)\n");
			}
			break;

			
		}
	} while(kFalse);

	return result;
}


ErrorCode TranFxScriptProvider::SetTransparencyEffectProperty(IScript* proxyScript, 
															  const ScriptID& propID, 
															  IScriptRequestData* data)
{
	ErrorCode result = kFailure;
	do {
		ASSERT(proxyScript);
		if(!proxyScript) {
			break;
		}	
		InterfacePtr<IScript> script((IScript*)proxyScript->QueryParent(IScript::kDefaultIID, data->GetRequestContext() ));
		
		ASSERT(script);
		if(!script) {
			break;
		}	
		
#ifdef DEBUG 
		// check what class this IScript impl came from
         {
             DebugClassUtilsBuffer classBuf;
             const char* className = 
                 DebugClassUtils::GetIDName(&classBuf, ::GetClass(script));
            TRACEFLOW(kTranFxPluginName, 
				"\t\t==> TranFxScriptProvider::SetTransparencyEffectProperty Script obj class=%s\n", className); 
         }
		 {
             DebugClassUtilsBuffer classBuf;
             const char* className = 
                 DebugClassUtils::GetIDName(&classBuf, ::GetClass(proxyScript));
            TRACEFLOW(kTranFxPluginName, 
				"\t\t==> TranFxScriptProvider::SetTransparencyEffectProperty proxyscript (parent) obj class=%s\n", className); 
         }
 #endif		
		
		TranFxUtils fxUtils;
		switch(propID.Get())
		{
			
			case p_TranFxMode:
			{
				UIDList targetItemList(script);
				bool16 needsOurAdornment = kFalse;
				result = this->GetBool(needsOurAdornment, propID, data);
				ASSERT(result == kSuccess);
				if(result != kSuccess) {
					break;
				}
				
				if(fxUtils.CanApplyAdornment(targetItemList)) {
					result = fxUtils.ApplyAdornment(targetItemList, needsOurAdornment); 
				}
				TRACEFLOW(kTranFxPluginName, 
					"\t\t==> TranFxScriptProvider::SetTransparencyEffectProperty (p_TranFxMode)\n");
			}
			break;

			case p_TranFxOffsetX:
			{
				UIDList targetItemList(script);
				PMReal newValue(0.0);
				result = this->GetPMReal(newValue, propID, data);
				if(result != kSuccess) {
					break;
				}
				if(fxUtils.CanApplyXOffset(targetItemList)) {
					result = fxUtils.ApplyXOffset(targetItemList, newValue); 
				}
				TRACEFLOW(kTranFxPluginName, 
					"\t\t==> TranFxScriptProvider::SetTransparencyEffectProperty (p_TranFxOffsetX)\n");
			}
			break;

			case p_TranFxOffsetY:
			{
				UIDList targetItemList(script);
				PMReal newValue(0.0);
				result = this->GetPMReal(newValue, propID, data);
				if(result != kSuccess) {
					break;
				}
				if(fxUtils.CanApplyYOffset(targetItemList)) {
					result = fxUtils.ApplyYOffset(targetItemList, newValue); 
				}
				TRACEFLOW(kTranFxPluginName, 
					"\t\t==> TranFxScriptProvider::SetTransparencyEffectProperty (p_TranFxOffsetY)\n");
			}
			break;

			case p_TranFxUseBlackAsOpaque:
			{
				UIDList targetItemList(script);
				bool16 newValue = kFalse;
				result = this->GetBool(newValue, propID, data);
				if(result != kSuccess) {
					break;
				}
				if(fxUtils.CanApplyUseBlackAsOpaque(targetItemList)) {
					result = fxUtils.ApplyUseBlackAsOpaque(targetItemList, newValue); 
				}
				TRACEFLOW(kTranFxPluginName, 
					"\t\t==> TranFxScriptProvider::SetTransparencyEffectProperty (p_TranFxUseBlackAsOpaque)\n");
			}
			break;

			case p_TranFxUseAlpha:
			{
				UIDList targetItemList(script);
				bool16 newValue = kFalse;
				result = this->GetBool(newValue, propID, data);
				if(result != kSuccess) {
					break;
				}
				if(fxUtils.CanApplyUseAlpha(targetItemList)) {
					result = fxUtils.ApplyUseAlpha(targetItemList, newValue); 
				}
				TRACEFLOW(kTranFxPluginName, 
					"\t\t==> TranFxScriptProvider::SetTransparencyEffectProperty (p_TranFxUseAlpha)\n");
			}
			break;

			case p_TranFxUseBlur:
			{
				UIDList targetItemList(script);
				bool16 newValue = kFalse;
				result = this->GetBool(newValue, propID, data);
				if(result != kSuccess) {
					break;
				}
				if(fxUtils.CanApplyUseBlur(targetItemList)) {
					result = fxUtils.ApplyUseBlur(targetItemList, newValue); 
				}
				TRACEFLOW(kTranFxPluginName, 
					"\t\t==> TranFxScriptProvider::SetTransparencyEffectProperty (p_TranFxUseBlur)\n");
			}
			break;

			
			
		}
	} while(kFalse);

	return result;
}

// TranFxScriptProvider.cpp
