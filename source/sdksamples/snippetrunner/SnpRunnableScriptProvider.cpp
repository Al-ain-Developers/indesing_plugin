//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/SnpRunnableScriptProvider.cpp $
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

// Interface includes
#include "IScript.h"
#include "IScriptEngine.h"
#include "IScriptRequestData.h"
#include "IScriptPreferences.h"
#include "IScriptUtils.h"
#include "ISelectionUtils.h"
#include "IStringData.h"
#include "IStringListData.h"

// General includes
#include "ScriptData.h" // also has typedef for ScriptListData
#include "CScriptProvider.h" // for RepresentScriptProvider

// Project includes
#include "SnipRunID.h"
#include "SnipRunLog.h"
#include "SnipRunScriptingDefs.h"
#include "ISnipRunSuite.h"

/** Script provider for the SDK code snippet script object.

	@ingroup snippetrunner
	@author Ken Sadahiro
*/
class SnpRunnableScriptProvider : public RepresentScriptProvider
{
public:
	/** Constructor.
	 */
	SnpRunnableScriptProvider(IPMUnknown* boss);
	/** Destructor
	 */
	virtual ~SnpRunnableScriptProvider(void);

	/** Handles an event. This call further delegates to private methods.
	 * 	@see IScriptProvider::HandleMethod
	 */
	virtual ErrorCode HandleMethod(ScriptID methodID, IScriptRequestData* data, IScript* script);

	/** Processes a property access. This call further delegates to private methods.
	 * 	@see IScriptProvider::AccessProperty
	 */
	virtual ErrorCode AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script);

protected:  
	/** Returns the number of objects (managed by this provider) of a specific type. 
	 * 	@see RepresentScriptProvider::GetNumObjects
	 */
	virtual int32 GetNumObjects( const IScriptRequestData* data, IScript* parent );

	/** Returns the Nth object (managed by this provider) of a specific type. 
	 * 	@see RepresentScriptProvider::AppendNthObject
	 */
	virtual ErrorCode AppendNthObject( const IScriptRequestData* data, IScript* parent, int32 n, ScriptList& objectList );

	/**  
	 * 	@see RepresentScriptProvider::GetObjectByName
	 */
	virtual ErrorCode GetObjectByName( IScriptRequestData* data, IScript* parent );

private: 

	/* Methods called by HandleMethod */

	/** HandleMethod calls this method to delegate the e_SnpRunnableCanRunSnippet event. 
	 * 	@see HandleMethod
	 */
	ErrorCode HandleEvent_CanRunSnippet(IScriptRequestData* data, IScript* script);
	
	/** HandleMethod calls this method to delegate the e_SnpRunnableRunSnippet event. 
	 * 	@see HandleMethod
	 */
	ErrorCode HandleEvent_RunSnippet(IScriptRequestData* data, IScript* script);
	
	/** HandleMethod calls this method to delegate the e_SnpRunnableSetupContext event. 
	 * 	@see HandleMethod
	 */
	ErrorCode HandleEvent_SetupContext(IScriptRequestData* data, IScript* script);
	
	/* Methods called by AccessProperty */

	/** AccessProperty calls this method to delegate access to the p_SnpRunnableName property.
	 * 	@see AccessProperty
	 */
	ErrorCode AccessProperty_SnpRunnableName(IScriptRequestData* data, IScript* script);

	/** AccessProperty calls this method to delegate access to the p_SnpRunnableCategories property.
	 * 	@see AccessProperty
	 */
	ErrorCode AccessProperty_SnpRunnableCategories(IScriptRequestData* data, IScript* script);

	/** AccessProperty calls this method to delegate access to the p_SnpRunnableDescription property.
	 * 	@see AccessProperty
	 */
	ErrorCode AccessProperty_SnpRunnableDescription(IScriptRequestData* data, IScript* script);

	/** AccessProperty calls this method to delegate access to the p_SnpRunnablePreconditions property.
	 * 	@see AccessProperty
	 */
	ErrorCode AccessProperty_SnpRunnablePreconditions(IScriptRequestData* data, IScript* script);

	
	/* Other helper methods */

	/** Get the snippet name property from the SDK code snippet script object.
	 * 	@param script IN The script object. Should be on kSnpRunnableScriptObjectBoss.
	 * 	@return The name of the SDK code snippet.
	*/
	PMString GetSnippetNameFromScript(IScript* script);

	/** Get the snippet parameters property from the event data.
	 * 	@param data IN The script event data passed into HandleMethod.
	 * 	@return The SnpRunnable parameters for this event.
	*/
	PMString GetSnippetParametersFromEventData(IScriptRequestData* data);


	/** The ScriptID of the object represented by this 
	 * 	RepresentScriptProvider implementation.
	 */
	ScriptID fScriptClassID;

	/** The ClassID of the boss class that has the IScript implementation 
	 * 	for the script object identified by fScriptClassID.
	 */
	ClassID  fProviderClassID;
};

/*  Make the implementation available to the application.
*/
CREATE_PMINTERFACE(SnpRunnableScriptProvider, kSnpRunnableScriptProviderImpl)


/* Constructor
*/
SnpRunnableScriptProvider::SnpRunnableScriptProvider(IPMUnknown* boss) : 
	RepresentScriptProvider(boss), 
	fScriptClassID(c_SnpRunnable),
	fProviderClassID(kSnpRunnableScriptObjectBoss) 
{
	// Do nothing
}

/* Destructor
*/
SnpRunnableScriptProvider::~SnpRunnableScriptProvider(void)	
{
	// Do nothing
}


/* HandleMethod
*/
ErrorCode SnpRunnableScriptProvider::HandleMethod(ScriptID methodID, IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;
	do
	{
		switch (methodID.Get())
		{
		case e_SnpRunnableCanRunSnippet:
			result = this->HandleEvent_CanRunSnippet(data, script);
			break;
		case e_SnpRunnableRunSnippet:
			result = this->HandleEvent_RunSnippet(data, script);
			break;
		case e_SnpRunnableSetupContext:
			result = this->HandleEvent_SetupContext(data, script);
			break;

		default:
			/* NOTE: 
			//	These events are handled in the superclass RepresentScriptProvider
			//	(See CScriptProvider.cpp)
			//	* e_Count (kCountMethodScriptElement) 
			*/
			result = RepresentScriptProvider::HandleMethod(methodID, data, script);
			break;
		}
	} while (false);
	// if kFailure, we need to change the error code so that we own the error string.
	if (result == kFailure)
	{
		result = kSnipRunInternalError;
	}
	return result;
}

/* AccessProperty
*/
ErrorCode SnpRunnableScriptProvider::AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;
	do
	{
		if (data->IsPropertyPut())
		{
			// all of these properties are read only - reject this
			ASSERT_FAIL("all of these properties are read only!");
			result = Utils<IScriptErrorUtils>()->SetReadOnlyPropertyErrorData( data, propID );
			break;
		}
		switch (propID.Get())
		{
		case p_SnpRunnableName:
			result = this->AccessProperty_SnpRunnableName(data, script);
			break;
		case p_SnpRunnableCategories:
			result = this->AccessProperty_SnpRunnableCategories(data, script);
			break;
		case p_SnpRunnableDescription:
			result = this->AccessProperty_SnpRunnableDescription(data, script);
			break;
		case p_SnpRunnablePreconditions:
			result = this->AccessProperty_SnpRunnablePreconditions(data, script);
			break;
		default:
			/* NOTE:
			// The following properties are handled in the 
			// super class RepresentScriptProvider (See CScriptProvider.cpp):
			// * p_Index (kIndexPropertyScriptElement)
			// * p_Parent (kParentPropertyScriptElement)
			// * p_Properties (kPropertiesPropertyScriptElement)
			*/
			result = RepresentScriptProvider::AccessProperty(propID, data, script);
			break;
		}

	} while (false);
	// if kFailure, we need to change the error code so that we own the error string.
	if (result == kFailure)
	{
		result = kSnipRunInternalError;
	}
	return result;
}
/* GetNumObjects
*/
int32 SnpRunnableScriptProvider::GetNumObjects( const IScriptRequestData* data, IScript* parent )
{
	int32 numObjects = 0;
	do
	{   
		// check input parameters
		if (data == nil || parent == nil)
		{
			ASSERT_FAIL("one of the input parameters is nil");
			break;
		}
		// ASSERT that we are getting the object ID we are expecting
		ScriptID objectType = data->GetDesiredType();
		if (objectType != fScriptClassID)
		{
			ASSERT_FAIL("we have been asked to get the count of an objectType we don't support");
			// we don't care about other objects
			break;
		}
		// get the number of snippets
		ISnipRunSuite::SnippetNames snippetNames;
		InterfacePtr<ISnipRunSuite> snipRunSuite((ISnipRunSuite*)Utils<ISelectionUtils>()->QuerySuite(ISnipRunSuite::kDefaultIID));
		if (snipRunSuite == nil)
		{
			ASSERT_FAIL("Cannot query ISnipRunSuite!");
			break;
		}
		snipRunSuite->GetSnippetNames(snippetNames);
		numObjects = snippetNames.size(); 

	} while (false);
	return numObjects;
}

/* AppendNthObject
*/
ErrorCode SnpRunnableScriptProvider::AppendNthObject( const IScriptRequestData* data, IScript* parent, int32 n, ScriptList& objectList )
{
	ErrorCode result = kFailure;
	do
	{
		// check input parameters
		if (data == nil || parent == nil)
		{
			ASSERT_FAIL("one of the input parameters is nil");
			break;
		}
		// ASSERT that we are getting the object ID we are expecting
		ScriptID objectType = data->GetDesiredType();
		if (objectType != fScriptClassID)
		{
			ASSERT_FAIL("we have been asked to get the count of an objectType we don't support");
			// we don't care about other objects
			break;
		}
		
		// create a proxy script object
		InterfacePtr<IScript> script(Utils<IScriptUtils>()->CreateProxyScriptObject(data->GetRequestContext(), fProviderClassID, fScriptClassID, parent));
		if (script == nil)
		{
			ASSERT_FAIL("CreateProxyScriptObject failed!");
			break;
		}

		// Get registered snippet names
		ISnipRunSuite::SnippetNames snippetNames;
		InterfacePtr<ISnipRunSuite> snipRunSuite((ISnipRunSuite*)Utils<ISelectionUtils>()->QuerySuite(ISnipRunSuite::kDefaultIID));
		if (snipRunSuite == nil)
		{
			ASSERT_FAIL("Cannot query ISnipRunSuite!");
			break; 
		}
		snipRunSuite->GetSnippetNames(snippetNames);
		if (n >= snippetNames.size())
		{
			//ASSERT_FAIL("snippet index is invalid!");
			result = kSnipRunSnippetNotFoundErrorCode;
			break;
		}

		PMString snippetName = snippetNames[n];
		ASSERT(snipRunSuite->IsRegistered(snippetName) == kTrue);

		// query for data interfaces
		InterfacePtr<IStringData> snippetNameData(script, IID_ISNIPPETNAME);
		InterfacePtr<IStringListData> snippetCategoriesData(script, IID_ISNIPPETCATEGORIES);
		InterfacePtr<IStringData> snippetDescriptionData(script, IID_ISNIPPETDESCRIPTION);
		InterfacePtr<IStringData> snippetPreconditionsData(script, IID_ISNIPPETPRECONDITIONS);
		if (snippetNameData == nil || 
			snippetCategoriesData == nil || 
			snippetDescriptionData == nil || 
			snippetPreconditionsData == nil)
		{
			ASSERT_FAIL("could not query one or more of the data interfaces on this script object!");
			break; 
		}

		// set the name
		snippetNameData->Set(snippetName);

		// set the categories
		ISnipRunSuite::Categories categories;
		snipRunSuite->GetCategories(snippetName, categories);
		snippetCategoriesData->SetStringList(categories);

		// set the description
		PMString description;
		snipRunSuite->GetDescription(snippetName, description);
		snippetDescriptionData->Set(description);

		// set the preconditions
		PMString preconditions;
		snipRunSuite->GetPreconditions(snippetName, preconditions);
		snippetPreconditionsData->Set(preconditions);

		// add the object to the list
		objectList.push_back(script);
		result = kSuccess;

	} while (false);
	return result;
}

/* GetObjectByName
*/
ErrorCode SnpRunnableScriptProvider::GetObjectByName( IScriptRequestData* data, IScript* parent )
{
	ErrorCode result = kFailure;
	do
	{
		// check input parameters
		if (data == nil || parent == nil)
		{
			ASSERT_FAIL("one of the input parameters is nil");
			break;
		}

		// ASSERT that we are getting the object ID we are expecting
		ScriptID objectType = data->GetDesiredType();
		if (objectType != fScriptClassID)
		{
			ASSERT_FAIL("we have been asked to get the count of an objectType we don't support");
			// we don't care about other objects
			break;
		}

		PMString snippetName ;
		ErrorCode err = data->GetAccessorData().GetPMString(snippetName);
		if (err != kSuccess)
		{
			ASSERT_FAIL("Cannot get the name from the script data!");
			break; 
		}

		// Get registered snippet names
		ISnipRunSuite::SnippetNames snippetNames;
		InterfacePtr<ISnipRunSuite> snipRunSuite((ISnipRunSuite*)Utils<ISelectionUtils>()->QuerySuite(ISnipRunSuite::kDefaultIID));
		if (snipRunSuite == nil)
		{
			ASSERT_FAIL("Cannot query ISnipRunSuite!");
			break; 
		}
		
		snipRunSuite->GetSnippetNames(snippetNames);
		
		//Find the snippet by name
		K2Vector<PMString>::const_iterator keyIter = std::find(snippetNames.begin(), snippetNames.end(), snippetName);
		if (keyIter == snippetNames.end())
		{
			result = kSnipRunSnippetNotFoundErrorCode;
			break;
		}

		ASSERT(snipRunSuite->IsRegistered(snippetName) == kTrue);
		//if (! snipRunSuite->IsRegistered(snippetName))
		//{
		//	result = kSnipRunSnippetNotRegisteredErrorCode;
		//	break;
		//}

		// create a proxy script object
		InterfacePtr<IScript> script(Utils<IScriptUtils>()->CreateProxyScriptObject(data->GetRequestContext(), fProviderClassID, fScriptClassID, parent));
		if (script == nil)
		{
			ASSERT_FAIL("CreateProxyScriptObject failed!");
			break;
		}

		// query for data interfaces
		InterfacePtr<IStringData> snippetNameData(script, IID_ISNIPPETNAME);
		InterfacePtr<IStringListData> snippetCategoriesData(script, IID_ISNIPPETCATEGORIES);
		InterfacePtr<IStringData> snippetDescriptionData(script, IID_ISNIPPETDESCRIPTION);
		InterfacePtr<IStringData> snippetPreconditionsData(script, IID_ISNIPPETPRECONDITIONS);
		if (snippetNameData == nil || 
			snippetCategoriesData == nil || 
			snippetDescriptionData == nil || 
			snippetPreconditionsData == nil)
		{
			ASSERT_FAIL("could not query one or more of the data interfaces on this script object!");
			break; 
		}

		// set the name
		snippetNameData->Set(snippetName);

		// set the categories
		ISnipRunSuite::Categories categories;
		snipRunSuite->GetCategories(snippetName, categories);
		snippetCategoriesData->SetStringList(categories);

		// set the description
		PMString description;
		snipRunSuite->GetDescription(snippetName, description);
		snippetDescriptionData->Set(description);

		// set the preconditions
		PMString preconditions;
		snipRunSuite->GetPreconditions(snippetName, preconditions);
		snippetPreconditionsData->Set(preconditions);

 		// set return data (script object)
		data->AppendReturnData( parent, data->GetRequestInfo()->GetScriptID(), ScriptData( script ) ) ;
		result = kSuccess;

	} while (false);

	return result;
}

/* HandleEvent_CanRunSnippet
*/
ErrorCode SnpRunnableScriptProvider::HandleEvent_CanRunSnippet(IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;
	ScriptData returnData;
	bool16 canRun = kFalse;
	do
	{
		if (script == nil || data == nil)
		{
			ASSERT_FAIL("Either script or data is nil");
			break;
		}
		PMString snippetName = this->GetSnippetNameFromScript(script);
		ASSERT(snippetName.empty() == kFalse);

		InterfacePtr<ISnipRunSuite> snipRunSuite((ISnipRunSuite*)Utils<ISelectionUtils>()->QuerySuite(ISnipRunSuite::kDefaultIID));
		if (snipRunSuite == nil)
		{
			ASSERT_FAIL("Cannot query ISnipRunSuite!");
			break;
		}

		canRun = snipRunSuite->CanRun(snippetName);
		result = kSuccess;
	} while (false);
	// set return data
	returnData.SetBoolean(canRun);
	data->AppendReturnData( script, e_SnpRunnableCanRunSnippet, returnData ) ;

	return result;
}

/* HandleEvent_RunSnippet
*/
ErrorCode SnpRunnableScriptProvider::HandleEvent_RunSnippet(IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;
	ErrorCode snipResult = kFailure;
	ScriptData returnData;
	do
	{
		if (script == nil || data == nil)
		{
			ASSERT_FAIL("Either script or data is nil");
			break;
		}
		PMString snippetName = this->GetSnippetNameFromScript(script);
		ASSERT(snippetName.empty() == kFalse);

		InterfacePtr<ISnipRunSuite> snipRunSuite((ISnipRunSuite*)Utils<ISelectionUtils>()->QuerySuite(ISnipRunSuite::kDefaultIID));
		if (snipRunSuite == nil)
		{
			ASSERT_FAIL("Cannot query ISnipRunSuite!");
			break;
		}
		bool16 canRun = snipRunSuite->CanRun(snippetName);
		if (canRun == kFalse)
		{
			//ASSERT_FAIL("Can't run this snippet at this time");
			result = kSnipRunCannotRunSnippetErrorCode;
			break; 
		}

		PMString parameters = this->GetSnippetParametersFromEventData(data);

		bool16 enableParameterDialog = kTrue;

		// get the current user interaction level
		InterfacePtr<IScriptEngine> scriptEngine(data->GetRequestContext().QueryScriptEngine()) ;
		if (scriptEngine == nil)
		{
			ASSERT_FAIL("Can't query the script engine");
			break;
		}
		// See IScriptPreferences.h for the InteractionLevel enum 
		InterfacePtr<IScriptPreferences> scriptPrefs(scriptEngine, UseDefaultIID());
		if (scriptPrefs == nil)
		{
			ASSERT_FAIL("Can't query the script preferences");
			break;
		}
		ScriptID userInteraction = scriptPrefs->GetInteractionLevel();
		// check for en_NeverInteract
		if (userInteraction.Get() == en_NeverInteract)
		{
			enableParameterDialog = kFalse;
		}
		else
		{
			// get the enableParameterDialog parameter
			ScriptData scriptData;
			result = data->ExtractRequestData(p_SnpRunnableEnableParameterDialog, scriptData);
			if (result != kSuccess)
			{
				ASSERT_FAIL("Could not get event data");
				break;
			}
			scriptData.GetBoolean(&enableParameterDialog);
		}

		// run the snippet
		snipResult = snipRunSuite->Run(snippetName, parameters, enableParameterDialog);
		result = kSuccess;

	} while (false);
	// set return data
	returnData.SetInt32(snipResult);
	data->AppendReturnData( script, e_SnpRunnableRunSnippet, returnData ) ;
	
	ASSERT(result != kFailure);
	return result;
}


/** HandleEvent_SetupContext
 */
ErrorCode SnpRunnableScriptProvider::HandleEvent_SetupContext(IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;
	ScriptData returnData;
	bool16 setupContext = kFalse;
	do
	{
		if (script == nil || data == nil)
		{
			ASSERT_FAIL("Either script or data is nil");
			break;
		}
		PMString snippetName = this->GetSnippetNameFromScript(script);
		ASSERT(snippetName.empty() == kFalse);

		InterfacePtr<ISnipRunSuite> snipRunSuite((ISnipRunSuite*)Utils<ISelectionUtils>()->QuerySuite(ISnipRunSuite::kDefaultIID));
		if (snipRunSuite == nil)
		{
			ASSERT_FAIL("Cannot query ISnipRunSuite!");
			break;
		}

		setupContext = snipRunSuite->SetupContext(snippetName);
		
		result = kSuccess;
	} while (false);
	// set return data

	returnData.SetBoolean(setupContext);
	data->AppendReturnData( script, e_SnpRunnableSetupContext, returnData ) ;

	return result;
}


/* AccessProperty_SnpRunnableName
*/
ErrorCode SnpRunnableScriptProvider::AccessProperty_SnpRunnableName(IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;
	do
	{
		if (script == nil || data == nil)
		{
			ASSERT_FAIL("Either script or data is nil");
			break;
		}
		ASSERT(data->IsPropertyGet());

		ScriptData returnData;
		// get the snippet name
		PMString snippetName = this->GetSnippetNameFromScript(script);
		ASSERT(snippetName.empty() == kFalse);

		// put it into the event data
		returnData.SetPMString(snippetName);
		data->AppendReturnData( script, p_SnpRunnableName, returnData ) ;
		result = kSuccess;
	} while (false);
	return result;
}

/* AccessProperty_SnpRunnableCategories
*/
ErrorCode SnpRunnableScriptProvider::AccessProperty_SnpRunnableCategories(IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;
	do
	{
		if (script == nil || data == nil)
		{
			ASSERT_FAIL("Either script or data is nil");
			break;
		}
		ASSERT(data->IsPropertyGet());

		ScriptData returnData;
		// get the snippet categories
		InterfacePtr<IStringListData> snippetCategoriesData(script, IID_ISNIPPETCATEGORIES);
		ASSERT(snippetCategoriesData);
		if (snippetCategoriesData == nil)
		{
			break;
		}
		ISnipRunSuite::Categories categories = snippetCategoriesData->GetStringList();

		// put it into the event data
		ScriptListData scriptCategoriesList;
		ScriptData categoryData;
		for (int32 i = 0; i < categories.size(); ++i)
		{
			categoryData.SetPMString(categories[i]);
			scriptCategoriesList.push_back(categoryData);
		}

		returnData.SetList(scriptCategoriesList);
		data->AppendReturnData( script, p_SnpRunnableCategories, returnData ) ;
		result = kSuccess;
	} while (false);
	return result;
}

/* AccessProperty_SnpRunnableDescription
*/
ErrorCode SnpRunnableScriptProvider::AccessProperty_SnpRunnableDescription(IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;
	do
	{
		if (script == nil || data == nil)
		{
			ASSERT_FAIL("Either script or data is nil");
			break;
		}
		ASSERT(data->IsPropertyGet());

		ScriptData returnData;
		// get the snippet description
		InterfacePtr<IStringData> snippetDescriptionData(script, IID_ISNIPPETDESCRIPTION);
		ASSERT(snippetDescriptionData);
		if (snippetDescriptionData == nil)
		{
			break;
		}
		PMString snippetDescription = snippetDescriptionData->Get();
		// put it into the event data
		returnData.SetPMString(snippetDescription);
		data->AppendReturnData( script, p_SnpRunnableDescription, returnData ) ;
		result = kSuccess;
	} while (false);
	return result;
}

/* AccessProperty_SnpRunnablePreconditions
*/
ErrorCode SnpRunnableScriptProvider::AccessProperty_SnpRunnablePreconditions(IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;
	do
	{
		if (script == nil || data == nil)
		{
			ASSERT_FAIL("Either script or data is nil");
			break;
		}
		ASSERT(data->IsPropertyGet());

		ScriptData returnData;
		// get the snippet precondition
		InterfacePtr<IStringData> snippetPreconditionsData(script, IID_ISNIPPETPRECONDITIONS);
		ASSERT(snippetPreconditionsData);
		if (snippetPreconditionsData == nil)
		{
			break;
		}
		PMString snippetPreconditions = snippetPreconditionsData->Get();
		// put it into the event data
		returnData.SetPMString(snippetPreconditions);
		data->AppendReturnData( script, p_SnpRunnablePreconditions, returnData ) ;
		result = kSuccess;
	} while (false);
	return result;
}

/* GetSnippetNameFromScript
*/
PMString SnpRunnableScriptProvider::GetSnippetNameFromScript(IScript* script)
{
	PMString name = "";
	do
	{
		if (script == nil)
		{
			break;
		}
		InterfacePtr<IStringData> snippetNameData(script, IID_ISNIPPETNAME);
		if (snippetNameData == nil)
		{
			break;
		}
		name = snippetNameData->Get();
	} while (false);
	return name;
}

/* GetSnippetParametersFromEventData
*/
PMString SnpRunnableScriptProvider::GetSnippetParametersFromEventData(IScriptRequestData* data)
{
	PMString params = "";
	do
	{
		if (data == nil)
		{
			break;
		}
		// get the string parameter in the event, then get it here

		ScriptData scriptData;
		ErrorCode result = data->ExtractRequestData(p_SnpRunnableParameters, scriptData);
		if (result != kSuccess)
		{
			ASSERT_FAIL("Could not get event data");
			break;
		}
		scriptData.GetPMString(params);
	} while (false);
	return params;
}
// End, SnpRunnableScriptProvider.cpp.
