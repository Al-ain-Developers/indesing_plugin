//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xdocbookworkflow/XDocBkPrefsScriptProvider.cpp $
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
#include "IXDocBkFacade.h"

// General includes:
#include "PrefsScriptProvider.h"

#include "Utils.h"

#include "XDocBkScriptingDefs.h"

/** From SDK sample; shows how to implement a script provider for xdocbkworkflow preference,
 
 See Scripting Resources defined in the plug-in's .fr file.
 
 @see kXDocBkPrefsScriptProviderBoss - the scriptable boss
 @see kXDocBkPrefObjectScriptElement - the script object that exposes kXDocBkPrefsScriptProviderBoss in the Scripting DOM
 @see XDocBk.fr
 @ingroup xdocbookworkflow
 */
class XDocBkPrefsScriptProvider : public PrefsScriptProvider
{
	public:
		/**	Constructor.
		 @param boss interface pointer from boss object on which this interface is aggregated.
		 */
		XDocBkPrefsScriptProvider(IPMUnknown* boss);
		
		/**	Destructor.
		 */
		~XDocBkPrefsScriptProvider();
		
		/** Called if a provider can handle a property.
		 @param propID identifies the ID of the property to handle.
		 @param data identifies an interface pointer used to extract data.
		 @param script identifies an interface pointer on a script object.
		 */
		virtual ErrorCode  AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script);
		
	private:
		
		ErrorCode AccessXDocPrefsData(ScriptID propID, IScriptRequestData* data, IScript* script);	
		ErrorCode GetBoolean(bool16& value, const ScriptID& scriptID, IScriptRequestData* data, bool16 isRequired = kTrue) const;
		ErrorCode GetScriptListData(ScriptListData& value, const ScriptID& scriptID, IScriptRequestData* data, bool16 isRequired = kTrue) const;
};

/*	Make the implementation available to the application.
 */
CREATE_PMINTERFACE(XDocBkPrefsScriptProvider, kXDocBkPrefsScriptProviderImpl)
/*
 */
XDocBkPrefsScriptProvider::XDocBkPrefsScriptProvider(IPMUnknown* boss) : PrefsScriptProvider(boss)
{
	// Make the base class aware of the XDocBkWorkflow's preferences scripting object.
	// The based will take care of creating a proxy script object when the preference
	// object is accessed.
	DefinePreference(c_XDocBkPref, p_XDocPref);
}
/*
*/
XDocBkPrefsScriptProvider::~XDocBkPrefsScriptProvider()
{
}
/*
 */
ErrorCode XDocBkPrefsScriptProvider::AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;
	do {
		switch (propID.Get())
		{
			case p_XDocSetOption:
			case p_XDocUseImportIt:
			case p_XDocUseXMLTsf:
			case p_XDocUseCALSContentHndl:
			case p_XDocSuppliedXSLOverridingPI:
			{
				result = this->AccessXDocPrefsData(propID, data, script);
				break;
			}
			
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
ErrorCode XDocBkPrefsScriptProvider::AccessXDocPrefsData(ScriptID propID, IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;
	do {
		// Preferences are stored on the workspace so check we have a workspace.
		InterfacePtr<IWorkspace> workspace(Utils<IScriptUtils>()->QueryWorkspaceFromScript(script, data->GetRequestContext()));
		ASSERT(workspace);
		if (!workspace) 
		{
			result = kInvalidScriptTargetError;
			break;
		}
		Utils<IXDocBkFacade> facade;
		ASSERT(facade);
		if(!facade)
		{
			result = kInvalidScriptTargetError;
			break;
		}
		bool16 value;
		if(data->IsPropertyPut())
		{
			switch(propID.Get())
			{
				case p_XDocSetOption:
				{
					ScriptListData dataList;
					result = this->GetScriptListData(dataList, propID, data);
					K2Vector<WideString> templatePaths;
					for (const auto &data : dataList)
					{
						WideString templatePath;
						data.GetWideString(templatePath);
						templatePaths.push_back(templatePath);
					}
					facade->SetOptions(templatePaths);
					break;
				}
				case p_XDocUseImportIt:
				{
					result = this->GetBoolean(value, propID, data);
					facade->SetUsePostImportIterator(value);
					break;
				}
				case p_XDocUseXMLTsf:
				{
					result = this->GetBoolean(value, propID, data);
					facade->SetUseXMLTransformer(value);
					break;
				}
				case p_XDocUseCALSContentHndl:
				{
					result = this->GetBoolean(value, propID, data);
					facade->SetUseCALSContentHandler(value);
					break;
				}
				case p_XDocSuppliedXSLOverridingPI:
				{
					result = this->GetBoolean(value, propID, data);
					facade->SetSuppliedXSLOverridingPI(value);
					break;
				}

			}
			
		}
		
		else if(data->IsPropertyGet())
		{
			ScriptData outputData;
			switch(propID.Get())
			{
				case p_XDocSetOption:
				{
					ScriptListData templatePaths;
					outputData.SetWideString((WideString)facade->GetTemplatePath());
					templatePaths.push_back(outputData);
					outputData.SetWideString((WideString)facade->GetStylesheetPath());
					templatePaths.push_back(outputData);
					outputData.SetList(templatePaths);
					break;
				}
				case p_XDocUseImportIt:
				{
					value = facade->IsUsingPostImportIterator();
					outputData.SetBoolean(value);
					break;
				}
				case p_XDocUseXMLTsf:
				{
					value = facade->IsUsingXMLTransformer();
					outputData.SetBoolean(value);
					break;
				}
				case p_XDocUseCALSContentHndl:
				{
					value = facade->IsUsingCALSContentHandler();
					outputData.SetBoolean(value);
					break;
				}
				case p_XDocSuppliedXSLOverridingPI:
				{
					value = facade->IsSuppliedXSLOverridingPI();
					outputData.SetBoolean(value);
					break;
				}
			}
			data->AppendReturnData( script, propID, outputData ) ;
		}

	}while(false);
		
	return kSuccess;
}
/*
 */
ErrorCode XDocBkPrefsScriptProvider::GetBoolean(bool16& value, const ScriptID& scriptID, IScriptRequestData* data, bool16 isRequired) const
{
	ErrorCode result = kFailure;
	do {
		ASSERT(data);
		ScriptData inputdata;
		result = data->ExtractRequestData(scriptID, inputdata);
		if (result != kSuccess) {
			break;
		}
		result = inputdata.GetBoolean(&value);
	} while(false);
	if (result != kSuccess && isRequired) {
		result = Utils<IScriptErrorUtils>()->SetMissingRequiredParameterErrorData(data, scriptID);
	}
	return result;
}
/*
 */
ErrorCode XDocBkPrefsScriptProvider::GetScriptListData(ScriptListData& value, const ScriptID& scriptID, IScriptRequestData* data, bool16 isRequired) const
{
	ErrorCode result = kFailure;
	do {
		ASSERT(data);
		ScriptData inputdata;
		result = data->ExtractRequestData(scriptID, inputdata);
		if (result != kSuccess) {
			break;
		}
		result = inputdata.GetList(value);
	} while(false);
	if (result != kSuccess && isRequired) {
		result = Utils<IScriptErrorUtils>()->SetMissingRequiredParameterErrorData(data, scriptID);
	}
	return result;
}

//End, XDocBkPrefsScriptProvider.cpp