//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlist/PstLstScriptProvider.cpp $
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
#include "ICommand.h"
#include "IHierarchy.h"
#include "IIntData.h"
#include "IScript.h"
#include "IScriptRequestData.h"

// Implementation includes:
#include "CmdUtils.h"
#include "CScriptProvider.h"
#include "DebugClassUtils.h"
#include "ScriptingID.h"

// Project includes:
#include "IPstLstData.h"
#include "IPstLstUIDList.h"
#include "PstLstID.h"
#include "PstLstUtils.h"
#include "PstLstScriptingDefs.h"
#include "StringUtils.h"

/** Provides scripting support by means of handling events and property 
 * 	accesses that are delegated by the script manager. 
 * 	@ingroup persistentlist
*/
class PstLstScriptProvider : public RepresentScriptProvider
{
public:
	/**
		Constructor 
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	PstLstScriptProvider(IPMUnknown* boss);

	/**
		Destructor.  
	*/
	virtual ~PstLstScriptProvider();
	/** Handles an event. This call further delegates to private methods.
	 * 	@see IScriptProvider::HandleMethod
	*/
	virtual ErrorCode HandleMethod(ScriptID methodID, IScriptRequestData* data, IScript* script);

	/** Processes a property access. This call further delegates to private methods.
	 * 	@see IScriptProvider::AccessProperty
	 */
	virtual ErrorCode AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script);

protected:  
	/**	Get the number of child objects, as specified by the data, that are contained in the given object.
	 * 	All subclasses must override this method. 
	 * 	NOTE: This method has been modified in InDesign CS2.
	 */
	virtual int32 GetNumObjects( const IScriptRequestData* data, IScript* parent );

	/**	Append the nth child object, as specified by the data, that is contained in the given object.
	 * 	All subclasses must override this method. 
	 * 	n is a 0-based index.
	 * 	NOTE: This method has been modified in InDesign CS2.
	 */
	virtual ErrorCode AppendNthObject( const IScriptRequestData* data, IScript* parent, int32 n, ScriptList& objectList );

private:
	/** Handles the e_Create event. Delegated from HandleMethod. 
	 * 	@see HandleMethod
	 */
	ErrorCode HandleEvent_CreatePstLstData(IScriptRequestData* data, IScript* script);

	/** Handles the e_Delete event. Delegated from HandleMethod. 
	 * 	@see HandleMethod
	 */
	ErrorCode HandleEvent_DeletePstLstData(IScriptRequestData* data, IScript* script);

	/** Accesses the p_Name property. Delegated from AccessProperty. 
	 * 	@see AccessProperty
	*/
    ErrorCode AccessProperty_PstLstDataName(IScriptRequestData* data, IScript* script);

	/** (Debug only) Examines the boss class of a given interface. 
	 * 	@param boss IN Any iterface derived from IPMUnknown.
	 */
	void ExamineClass(IPMUnknown* boss);

	/** The ScriptID for the "current" script object */
	ScriptID fScriptClassID;
	
};


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(PstLstScriptProvider, kPstLstScriptProviderImpl)


/* PstLstScriptProvider Constructor
*/
PstLstScriptProvider::PstLstScriptProvider(IPMUnknown* boss)
: 	RepresentScriptProvider(boss), 
	fScriptClassID(c_PstLstDataItem)
{
	// do nothing
}

/* PstLstScriptProvider Dtor
*/
PstLstScriptProvider::~PstLstScriptProvider()	
{
	// do nothing
}

/* HandleMethod
*/
ErrorCode PstLstScriptProvider::HandleMethod(ScriptID methodID, IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;
	do
	{
		// Check input parameters
		if (data == nil || script == nil)
		{
			ASSERT_FAIL("one of the input parameters is nil");
			result = kPstLstScriptProviderPreconditionError;
			break;
		}

		// make sure we are being asked for the right object
		ScriptID desiredObjectID = data->GetDesiredType();
		// this method should be expected to return a persistent list data item
		if (desiredObjectID != fScriptClassID)
		{
			ASSERT_FAIL("We have been asked for an object we don't support");
			result = kPstLstUnsupportedObjectRequestedError;
			break;
		}


		switch (methodID.Get())
		{
		case e_Create:
			result = HandleEvent_CreatePstLstData(data, script);
			break;
		case e_Delete:
			result = HandleEvent_DeletePstLstData(data, script);
			break;
		default:
			/* NOTE: 
			//	The count event is handled in the super class RepresentScriptProvider
			//	(See CScriptProvider.cpp)
			//	* e_Count (kCountMethodScriptElement) 
			//	These events are added by the base script object (kUIDBasedObjectScriptElement)
			//	and are handled in RepresentScriptProvider also.
			//	* e_ExtractLabel (kExtractLabelMethodScriptElement)
			//	* e_InsertLabel (kInsertLabelMethodScriptElement)
			*/
			result = RepresentScriptProvider::HandleMethod(methodID, data, script);
			break;
		}
	} while (false);

	// if kFailure, we need to change the error code so that we own the error string.
	if (result == kFailure)
	{
		result = kPstLstInternalError;
	}
	return result;
}


/* AccessProperty
*/
ErrorCode PstLstScriptProvider::AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;
	do
	{
		// Check input parameters
		if (data == nil || script == nil)
		{
			ASSERT_FAIL("one of the input parameters is nil");
            result = kPstLstScriptProviderPreconditionError;
			break;
		}
		
		switch (propID.Get())
		{
		case p_Name:
			result = AccessProperty_PstLstDataName(data, script);
			break;
		default:
			/* NOTE: 
			//	These properties are handled in the super class RepresentScriptProvider
			//	(See CScriptProvider.cpp)
			// 	* p_ID (kIDPropertyScriptElement)
			// 	* p_Index (kIndexPropertyScriptElement)
			// 	* p_Tag (kLabelPropertyScriptElement)
			// 	* p_Class (kClassPropertyScriptElement - AppleScript only)
			// 	* p_Properties (kPropertiesPropertyScriptElement)
			// 	* p_ObjectSpecifier (kObjectReferencePropertyScriptElement)
			// 	* p_Parent (kParentPropertyScriptElement)
			*/
			result = RepresentScriptProvider::AccessProperty(propID, data, script);
			break;
		}
	} while (false);

	// if kFailure, we need to change the error code so that we own the error string.
	if (result == kFailure)
	{
		result = kPstLstInternalError;
	}
	return result;
}

/* GetNumObjects
*/
int32 PstLstScriptProvider::GetNumObjects( const IScriptRequestData* data, IScript* parent )
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
		this->ExamineClass(parent);

		// check if the desired object type is the one we are ready to serve.
		ScriptID desiredObjectID = data->GetDesiredType();
		if (desiredObjectID != fScriptClassID)
		{
			ASSERT_FAIL("We have been asked for an object we don't support");
			break;
		}
		
		// get the number of kPstLstDataBoss objects hanging off of the parent. 
		InterfacePtr<IPstLstUIDList> pstLstUIDList(parent, UseDefaultIID());
		if (pstLstUIDList == nil)
		{
			ASSERT_FAIL("The parent does not have IPstLstUIDList! Is the parent really a subclass of kDrawablePageItemBoss?");
			break;
		}
		const UIDList* uidList = pstLstUIDList->GetUIDList();
		if (uidList == nil)
		{
			ASSERT_FAIL("the UIDList is nil!");
			break;
		}
		numObjects = uidList->Length();
		ASSERT(numObjects >= 0);

	} while (false);
	return numObjects;
}

/* AppendNthObject
*/
ErrorCode PstLstScriptProvider::AppendNthObject( const IScriptRequestData* data, IScript* parent, int32 n, ScriptList& objectList )
{
	ErrorCode result = kFailure;
	do
	{
		// check input parameters
		if (data == nil || parent == nil)
		{
			ASSERT_FAIL("One of the input parameters to the PersistentList plug-in script provider is nil.");
			result = kPstLstScriptProviderPreconditionError;
			break;
		}
		this->ExamineClass(parent);

		// check if the desired object type is the one we are ready to serve.
		ScriptID desiredObjectID = data->GetDesiredType();
		if (desiredObjectID != fScriptClassID)
		{
			ASSERT_FAIL("We have been asked for an object we don't support");
			result = kPstLstUnsupportedObjectRequestedError;
			break;
		}

		// Get the actual PstLstData object via the parent.
		InterfacePtr<IPstLstUIDList> pstLstUIDList(parent, UseDefaultIID());
		if (pstLstUIDList == nil)
		{
			ASSERT_FAIL("The parent does not have IPstLstUIDList! Is the parent really a subclass of kDrawablePageItemBoss?");
			result = kPstLstInternalError;
			break;
		}
		const UIDList* uidList = pstLstUIDList->GetUIDList();
		if (uidList == nil)
		{
			ASSERT_FAIL("the UIDList is nil!");
			result = kPstLstInternalError;
			break;
		}
		if (uidList->Length() < n)
		{
			ASSERT_FAIL("the UIDList does not have enough items!");
			result = kPstListParentUIDListHasInsufficientNumberOfItemsError;
			break;
		}
		UIDRef pstLstItemRef = pstLstUIDList->GetRef(n);
		InterfacePtr<IScript> pstLstDataItemScript(pstLstItemRef, UseDefaultIID());
		if (pstLstDataItemScript == nil)
		{
			ASSERT_FAIL("the item does not have IScript! Is this really a kPstLstDataBoss?");
			result = kPstLstInternalError;
			break;
		}
		
		// sanity-check the class ID
		ClassID pstLstDataClassID = ::GetClass(pstLstDataItemScript);
		ASSERT(pstLstDataClassID == kPstLstDataBoss);
		
		// add the script object to the list and pass it back
		objectList.push_back(pstLstDataItemScript);
		result = kSuccess;
	
	} while (false);

	// if kFailure, we need to change the error code so that we own the error string.
	if (result == kFailure)
	{
		result = kPstLstInternalError;
	}
	return result;
}

/* HandleEvent_CreatePstLstData
*/
ErrorCode PstLstScriptProvider::HandleEvent_CreatePstLstData(IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;
	ScriptData scriptData;
	ScriptData returnData;
	do
	{
		// the passed-in script should be a "page item" 
		// since this is a collection event
		this->ExamineClass(script);

		InterfacePtr<IPstLstUIDList> pstLstUIDList(script, UseDefaultIID());
        ASSERT_MSG(pstLstUIDList, "Cannot query IPstLstUIDList - Something's wrong with this item");
		InterfacePtr<IHierarchy> scriptHier(script, UseDefaultIID()); 
		ASSERT_MSG(scriptHier, "Cannot query IHierarchy - Something's wrong with this item");
		UIDList itemList(script);
		
		// default value for the persistent list data item
		WideString name(kPstLstDataItemNameDefault);

		// get the parameters from the event
		result = data->ExtractRequestData(p_Name, scriptData);
		if (result == kSuccess)
		{
			// This means that there was a parameter passed in.  Get the parameter.
			if (scriptData.GetType() == ScriptData::s_string)
			{
				// the parameter was a string
				// get the string
				result = scriptData.GetWideString(name);
				ASSERT(result == kSuccess);
			}
		} // if (result == kSuccess);
		else
		{
			std::string msg;
			StringUtils::ConvertWideStringToUTF8(name, msg);
			TRACEFLOW(kPstLstPluginName, "PstLstScriptProvider::HandleEvent_CreatePstLstData: no parameters passed in, using default (\"%s\").\n", msg.c_str());
		}

		// create a new persistent list data item
		UIDList returnedItemList(itemList.GetDataBase());
		result = PstLstUtils::DoCreateNewData(itemList, name, returnedItemList);
		// Check for errors, issue warning if so:
		if (result != kSuccess)
		{
			ASSERT_FAIL("PstLstNewDataCmd failed");
			break;
		}
		
		// get the newly created persistent list data item (kPstLstDataBoss) object
		// NOTE: We are only passing in one item, so we should only get one item back
		UIDRef newItemRef = returnedItemList.GetRef(0);
		ASSERT(newItemRef.ExistsInDB() == kTrue);
		
		// get the IScript interface in this item
		InterfacePtr<IScript> newItemScript(newItemRef, UseDefaultIID());
		if (newItemScript == nil)
		{
			ASSERT_FAIL("Could not obtain the newly created item");
			result = kPstLstInternalError;
			break;
		}
		// sanity check - make sure we have the right boss class
		ClassID newItemClass = ::GetClass(newItemScript);
		ASSERT(newItemClass == kPstLstDataBoss);
		
		// set the return data - pass back the new script object
		data->AppendReturnData( script, e_Create, ScriptData( newItemScript ) ) ;


		// if we got here, we are ok. 
		result = kSuccess;

	} while (false);
	return result;
}

/* HandleEvent_DeletePstLstData
*/
ErrorCode PstLstScriptProvider::HandleEvent_DeletePstLstData(IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;
	do
	{
		// query the page item object
		InterfacePtr<IScript> parent((IScript*)script->QueryParent(IScript::kDefaultIID, data->GetRequestContext() ));
		if (parent == nil)
		{
			ASSERT_FAIL("IScript::QueryParent failed");
			result = kPstLstInternalError;
			break;
		}

 		InterfacePtr<IHierarchy> parentHier(parent, UseDefaultIID()); 
		ASSERT_MSG(parentHier, "Cannot query IHierarchy - Something's wrong with this parent");
		// make a UIDList to pass into the commands below.
		UIDRef parentItemRef = ::GetUIDRef(parent);
		UIDList itemList(parentItemRef);
		this->ExamineClass(parent);


		InterfacePtr<ICommand> deleteDataCmd(CmdUtils::CreateCommand(kPstLstDeleteDataCmdBoss));
   		if (deleteDataCmd == nil)
   		{
   			ASSERT_FAIL("kPstLstDeleteDataCmd invalid");
   			break;
   		}
   
        // set the item list
		UIDList item(script);
        deleteDataCmd->SetItemList(item);

        // Finally, the command is processed:
        result = CmdUtils::ProcessCommand(deleteDataCmd);
		
	} while (false);

	return result;
}

/* AccessProperty_PstLstDataName
*/
ErrorCode PstLstScriptProvider::AccessProperty_PstLstDataName(IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;
	ScriptData scriptData;
	ScriptData returnData;
	do
	{
		
		if (data->IsPropertyGet())
		{
			// get the name string from the object
			UIDRef itemRef = ::GetUIDRef(script);
			WideString pstLstDataName;
			result = PstLstUtils::DoGetName(itemRef, pstLstDataName);

			// package it into the return data
			returnData.SetWideString(pstLstDataName);
			data->AppendReturnData( script, p_Name, returnData ) ;
			result = kSuccess;
		}
		else if (data->IsPropertyPut())
		{
			// get the name from the parameter
			data->ExtractRequestData(p_Name, scriptData);
			WideString name;
			result = scriptData.GetWideString(name);
			ASSERT(result == kSuccess);

			// get the UIDRef of the item 
			UIDRef itemRef = ::GetUIDRef(script);
			
			// select and set name
			UIDList itemList(itemRef);
			result = PstLstUtils::DoSetName(itemList, name);
		}
	} while (false);
	return result;
}

/* ExamineClass 
*/
void PstLstScriptProvider::ExamineClass(IPMUnknown* boss)
{
#ifdef DEBUG
	if (boss != nil)
	{
		ClassID classID = ::GetClass(boss);
		DebugClassUtilsBuffer buf;
		DebugClassUtils::GetIDName(&buf, classID);
		TRACEFLOW(kPstLstPluginName, "PstLstScriptProvider::ExamineClass: ClassID=0x%X, Name=\"%s\"\n", classID.Get(), buf);
	}
#else
	// do nothing
#endif
}

// End, PstLstScriptProvider.cpp.



