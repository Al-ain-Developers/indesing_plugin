//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/printselection/PrnSelScriptProvider.cpp $
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

// General includes:
#include "CmdUtils.h"
#include "PrefsScriptProvider.h"
#include "Utils.h"

// Interface includes
#include "ICommand.h"
#include "IDataBase.h"
#include "IDocument.h"
#include "IScript.h"
#include "IScriptRequestData.h"

// Project includes:
#include "PrnSelScriptingDefs.h"
#include "PrnSelID.h"
#include "IPrnSelUtils.h"


/** Adds scripting support for the print selection preference object.
	@ingroup printselection
*/
class PrnSelScriptProvider : public PrefsScriptProvider
{
public:
	/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	PrnSelScriptProvider(IPMUnknown* boss);

	/**
		Destructor. Does nothing.
	*/
	~PrnSelScriptProvider()
	{
	}

	/** This method is called by the script manager if this provider can handle a specific property.
	 * 	@param propID identifies the ID of the property to handle.
	 * 	@param data identifies an interface pointer used to extract data.
	 * 	@param parent identifies an interface pointer on the script object representing the parent of the current object.
	 */
	virtual ErrorCode  AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* parent);

private:
	/** AccessProperty delegates to this method to handle the PrintSelection property. 
	 * 	@param propID identifies the ScriptID of the property to handle.
	 * 	@param data identifies an interface pointer used to extract script event data.
	 * 	@param parent identifies an interface pointer on the script object representing the parent of the current object.
	 */
	virtual ErrorCode  AccessPrintSelectionProperty(ScriptID propID, IScriptRequestData* data, IScript* parent);
};


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(PrnSelScriptProvider, kPrnSelScriptProviderImpl)


/* Constructor
*/
PrnSelScriptProvider::PrnSelScriptProvider(IPMUnknown* boss)
: PrefsScriptProvider(boss)
{
	// Define preference 
	DefinePreference(c_PrintSelection, p_PrintSelectionProperty);
}

/* AccessProperty
*/
ErrorCode PrnSelScriptProvider::AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* parent)
{
	ErrorCode status = kFailure;
	switch (propID.Get())
	{
	case p_PrintSelection:
		status = AccessPrintSelectionProperty(propID, data, parent);
		break;
	default:
		status = PrefsScriptProvider::AccessProperty(propID, data, parent);
	}
	return status;
}

/* AccessPrintSelectionProperty
*/
ErrorCode PrnSelScriptProvider::AccessPrintSelectionProperty(ScriptID propID, IScriptRequestData* data, IScript* parent)
{
	ErrorCode status = kFailure;
	bool16 boolData = kFalse;
	ScriptData scriptData;
	do
	{
		// check parameters
		if (parent == nil || data == nil)
		{
			ASSERT_FAIL("PrnSelScriptProvider::AccessPrintSelectionProperty: One of the input parameters is nil!");
			break;
		}

		// get the database and UID for the corresponding parent boss
		IDataBase* db = parent->GetDataBase( data->GetRequestContext() );
		UID rootUID = db->GetRootUID();

		InterfacePtr<IDocument> doc(db, rootUID, UseDefaultIID());
		if (doc == nil)
		{
			ASSERT_FAIL("PrnSelScriptProvider::AccessPrintSelectionProperty: doc is nil!");
			break;
		}

		// check the access mode
		if (data->IsPropertyGet())
		{
			boolData = Utils<IPrnSelUtils>()->_GetPrintSelectionFlag(doc);

			// set the return data
			scriptData.SetBoolean(boolData);
			data->AppendReturnData( parent, propID, scriptData ) ;

			status = kSuccess;

		}
		else if (data->IsPropertyPut())
		{
			// get the data passed into the script event data
			status = data->ExtractRequestData(propID, scriptData);
			if (status != kSuccess)
			{
				ASSERT_FAIL("Could not get the script data from IScriptRequestData!");
				break;
			}
			status = scriptData.GetBoolean(&boolData);
			if (status != kSuccess)
			{
				ASSERT_FAIL("Could not get the boolean data from the script data!");
				break;
			}

			// set the value
			status = Utils<IPrnSelUtils>()->_SetPrintSelectionFlag(doc, boolData);
		}
	} while (false);
	return status;
}

// End, PrnSelScriptProvider.cpp

