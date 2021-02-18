//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PreflightRuleDataHelper.h $
//  
//  Owner: Matt Phillips
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

#include "IPreflightRuleData.h"


/** This helper class provides utilities for reading and writing parameters from 
	a rule's IPreflightRuleData. That interface stores rule parameters in a key-value
	dictionary. Most of the time you just want to grab a parameter without multiple
	steps that are required if you use the interface directly.

	Typical use (in an IPreflightRuleVisitor implementation):

		PreflightRuleDataHelper params(this);

		if (params.GetBoolParam("check_small_text"))
		{
			if (text_size < params.GetRealParam("min_text_size"))
			{
				// Record an error
			}
		}

	or, a typical application in UpdateRuleData():

		PreflightRuleDataHelper params(this);

		// Ensure my parameters exist and establish default values if they don't
		params.SetBoolParamDefault("check_small_text", kTrue);
		params.SetRealParamDefault("min_text_size", 6.0);
		
*/
class PreflightRuleDataHelper
{
private:
	InterfacePtr<IPreflightRuleData> fData;

public:
	/** Constructor.
		@param iUnk IN An interface on the boss from which we can query IPreflightRuleData.
	*/
	PreflightRuleDataHelper(const IPMUnknown* iUnk)
	{
		fData.reset((IPreflightRuleData*)iUnk->QueryInterface(IID_IPREFLIGHTRULEDATA));
		ASSERT(fData);
	}

	/** @return true iff we were able to get the necessary data interface.
	*/
	bool IsValid() const
	{
		return fData != nil;
	}

	/** Given a key, get the associated PMReal. Asserts if the data type is not compatible
		with PMReal, or if the key does not exist. In these cases the specified default 
		value is used.

		@param param IN The parameter key.
		@param defaultValue IN The default value to return if an error occurs.
		@return The parameter value, or default value if an error occurred.
	*/
	PMReal GetRealParam(const char* param, PMReal defaultValue = 0) const
	{
		if (!fData) return defaultValue;
		bool exists;
		ScriptData scriptData;
		fData->GetData(param, ScriptData(defaultValue), scriptData, &exists);

		ASSERT_MSG(exists, "Warning: Missing a rule parameter; using default value.");

		PMReal value;
		if (exists && scriptData.GetType () == ScriptData::s_double)
		{
			scriptData.GetPMReal(&value);
		}
		else
		{
			ASSERT_FAIL("Warning: Rule parameter present, but wrong type. Using default value.");
			value = defaultValue;
		}

		return value;
	}

	/** Given a key and value, set the value for the key in the dictionary. 

		@param param IN The key to set.
		@param newValue IN The value to set.
	*/
	void SetRealParam(const char* param, PMReal newValue) const
	{
		if (!fData) return;
		fData->SetData(param, ScriptData(newValue));
	}

	/** Given a key and value, sets the value for the key in the dictionary ONLY IF the key does
		not currently exist. This method is typically used in UpdateRuleData to ensure that the 
		keys that the rule uses exist, without changing any parameters that are already configured.

		@param param IN The key to set.
		@param newValue IN The value to set.
	*/
	void SetRealParamDefault(const char* param, PMReal newValue) const
	{
		if (!DataExists(param)) SetRealParam(param, newValue);
		else if (fData && fData->GetValueType(param) != ScriptData::s_double)
		{
			fData->RemoveKey(param);
			SetRealParam(param, newValue);
		}
	}

	/** Given a key, get the associated bool. Asserts if the data type is not compatible
		with bool, or if the key does not exist. In these cases the specified default 
		value is used.

		@param param IN The parameter key.
		@param defaultValue IN The default value to return if an error occurs.
		@return The parameter value, or default value if an error occurred.
	*/
	bool GetBoolParam(const char* param, bool defaultValue = kFalse) const
	{
		if (!fData) return defaultValue;
		bool exists;
		ScriptData scriptData;
		fData->GetData(param, ScriptData((bool16)defaultValue), scriptData, &exists);

		ASSERT_MSG(exists, "Warning: Missing a rule parameter; using default value.");

		bool16 value;
		if (exists && (scriptData.GetType () == ScriptData::s_boolean || scriptData.GetType() == ScriptData::s_shortint))
		{
			// Note that scriptdata appears to coerce properly for us..
			scriptData.GetBoolean(&value);
		}
		else
		{
			ASSERT_FAIL("Warning: Rule parameter present, but wrong type. Using default value.");
			value = defaultValue;
		}

		return value;
	}

	/** Given a key and value, set the value for the key in the dictionary. 

		@param param IN The key to set.
		@param newValue IN The value to set.
	*/
	void SetBoolParam(const char* param, bool newValue) const
	{
		bool exists;
		ScriptData scriptData;
		fData->GetData(param, ScriptData(), scriptData, &exists);

		if (exists)
		{
			if (exists && scriptData.GetType () == ScriptData::s_boolean)
				scriptData.SetBoolean((bool16)newValue);
			else
				ASSERT_FAIL ("SetBoolParam, expect real data but got something else.");
		}
		else
		{
			scriptData.SetBoolean((bool16)newValue);
		}
		fData->SetData(param, scriptData);
	}

	/** Given a key and value, sets the value for the key in the dictionary ONLY IF the key does
		not currently exist. This method is typically used in UpdateRuleData to ensure that the 
		keys that the rule uses exist, without changing any parameters that are already configured.

		@param param IN The key to set.
		@param newValue IN The value to set.
	*/
	void SetBoolParamDefault(const char* param, bool newValue) const
	{
		if (!DataExists(param)) SetBoolParam(param, newValue);
		else if (fData && fData->GetValueType(param) != ScriptData::s_boolean)
		{
			fData->RemoveKey(param);
			SetBoolParam(param, newValue);
		}
	}

	/** Given a key, get the associated string. Asserts if the data type is not compatible
		with PMString, or if the key does not exist. In these cases the specified default 
		value is used.

		@param param IN The parameter key.
		@param defaultValue IN The default value to return if an error occurs.
		@return The parameter value, or default value if an error occurred.
	*/
	PMString GetStringParam(const char* param, const PMString& defaultValue = PMString()) const
	{
		if (!fData) return defaultValue;

		bool exists;
		ScriptData scriptData;
		fData->GetData(param, ScriptData(defaultValue), scriptData, &exists);

		ASSERT_MSG(exists, "Warning: Missing a rule parameter; using default value.");

		PMString value;
		if (exists && scriptData.GetType () == ScriptData::s_string)
		{
			scriptData.GetPMString(value);
		}
		else
		{
			ASSERT_FAIL("Warning: Rule parameter present, but wrong type. Using default value.");
			value = defaultValue;
		}

		return value;
	}

	/** Given a key and value, set the value for the key in the dictionary. 

		@param param IN The key to set.
		@param newValue IN The value to set.
	*/
	void SetStringParam(const char* param, const PMString& newValue) const
	{
		if (!fData) return;

		bool exists;
		ScriptData scriptData;
		fData->GetData(param, ScriptData(), scriptData, &exists);

		if (exists)
		{
			if (exists && scriptData.GetType () == ScriptData::s_string)
				scriptData.SetPMString(newValue);
			else
				ASSERT_FAIL ("SetBoolParam, expect string data but got something else.");
		}
		else
		{
			scriptData.SetPMString(newValue);
		}
		fData->SetData(param, scriptData);
	}

	/** Given a key and value, sets the value for the key in the dictionary ONLY IF the key does
		not currently exist. This method is typically used in UpdateRuleData to ensure that the 
		keys that the rule uses exist, without changing any parameters that are already configured.

		@param param IN The key to set.
		@param newValue IN The value to set.
	*/
	void SetStringParamDefault(const char* param, const PMString& newValue) const
	{
		if (!DataExists(param)) SetStringParam(param, newValue);
		else if (fData && fData->GetValueType(param) != ScriptData::s_string)
		{
			fData->RemoveKey(param);
			SetStringParam(param, newValue);
		}
	}

	/** Given a key, get the associated integer. Asserts if the data type is not compatible
		with int32, or if the key does not exist. In these cases the specified default 
		value is used.

		@param param IN The parameter key.
		@param defaultValue IN The default value to return if an error occurs.
		@return The parameter value, or default value if an error occurred.
	*/
	int32 GetIntParam(const char* param, int32 defaultValue = 0) const
	{
		if (!fData) return defaultValue;

		bool exists;
		ScriptData scriptData;
		fData->GetData(param, ScriptData(defaultValue), scriptData, &exists);

		ASSERT_MSG(exists, "Warning: Missing a rule parameter; using default value.");

		int32 value;
		if (exists && scriptData.GetType () == ScriptData::s_longint)
		{
			scriptData.GetInt32(&value);
		}
		else if (exists && scriptData.GetType () == ScriptData::s_double)
		{
			PMReal tmp;
			scriptData.GetPMReal(&tmp);
			value = ::ToInt32(tmp);
		}
		else
		{
			ASSERT_FAIL("Warning: Rule parameter present, but wrong type. Using default value.");
			value = defaultValue;
		}

		return value;
	}

	/** Given a key and value, set the value for the key in the dictionary. 

		@param param IN The key to set.
		@param newValue IN The value to set.
	*/
	void SetIntParam(const char* param, int32 newValue) const
	{
		if (!fData) return;

		bool exists;
		ScriptData scriptData;
		fData->GetData(param, ScriptData(), scriptData, &exists);

		if (exists)
		{
			if (scriptData.GetType () == ScriptData::s_longint)
				scriptData.SetInt32(newValue);
			else
				ASSERT_FAIL ("SetRealParam, expect real data but got something else.");
		}
		else
		{
			scriptData.SetInt32(newValue);
		}

		fData->SetData(param, scriptData);
	}

	/** Given a key and value, sets the value for the key in the dictionary ONLY IF the key does
		not currently exist. This method is typically used in UpdateRuleData to ensure that the 
		keys that the rule uses exist, without changing any parameters that are already configured.

		@param param IN The key to set.
		@param newValue IN The value to set.
	*/
	void SetIntParamDefault(const char* param, int32 newValue) const
	{
		if (!DataExists(param)) SetIntParam(param, newValue);
		else if (fData && fData->GetValueType(param) != ScriptData::s_longint)
		{
			fData->RemoveKey(param);
			SetIntParam(param, newValue);
		}
	}

	/** @return true if the parameter exists, false if not.
	*/
	bool DataExists(const char* param) const
	{
		if (!fData) return kFalse;
		return fData->KeyExists(param);
	}

	/** Removes a parameter that's no longer used. Does nothing if the parameter does not exist.

		@param param IN The parameter (key) you want to remove.
	*/
	void RemoveObsoleteDataParam (const char* param) const
	{
		if (!fData) return;

		if (DataExists (param))
		{
			fData->RemoveKey (param);
		}
	}
};


