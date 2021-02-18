//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/scriptingcomms/SCScriptProvider.cpp $
//  
//  Owner: Timothy Brand-Spencer
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2012 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IScript.h"
#include "IScriptRequestData.h"
#include "IWorkspace.h"

// General includes:
#include "CAlert.h"
#include "CScriptProvider.h"

// Project includes:
#include "SCScriptingDefs.h"
#include "SCID.h"

/** Demonstrates extending the Application script object, adding both a method and a property.

    To see the interaction between a script and this plug-in, use the following extendscript:

    var said = "hello";
    app.speak(said);
    var yourresponse = app.response;
    app.speak(yourresponse);
*/
class SCScriptProvider : public CScriptProvider
{
public:
	/** Constructor.
	@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	SCScriptProvider(IPMUnknown* boss) : CScriptProvider(boss) {};

	/** Destructor. Does nothing.
	*/
	~SCScriptProvider() {}

	/** This method is called if a provider can handle an method.
	@param methodID identifies the ID of the method to handle.
	@param data identifies an interface pointer used to extract data.
	@param parent identifies an interface pointer on the script object representing the parent of the application object.
	*/
	virtual ErrorCode HandleMethod(ScriptID methodID, IScriptRequestData* data, IScript* parent);

	/** This method is called if a provider can handle a property.
	@param propID identifies the ID of the property to handle.
	@param data identifies an interface pointer used to extract data.
	@param parent identifies an interface pointer on the script object 		representing the parent of the application object.
	*/
	virtual ErrorCode AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* parent);

private:
	/** This method delegated to handle the e_Speak method, which extracts the p_Said property and displays its string content in a dialog. 
	@param data identifies an interface pointer used to extract data.
	@param parent identifies an interface pointer on the script object representing the parent of the application object.
	*/
	virtual ErrorCode Speak(IScriptRequestData* data, IScript* parent);

	/** This method delegated to handle the p_Response property. 
	@param data identifies an interface pointer used to extract data.
	@param parent identifies an interface pointer on the script object 		representing the parent of the application object.
	*/
	virtual ErrorCode AccessResponse(ScriptID propID, IScriptRequestData* data, IScript* parent);
};

/* CREATE_PMINTERFACE
Binds the C++ implementation class onto its ImplementationID 
making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(SCScriptProvider, kSCScriptProviderImpl)

/* HandleMethod */
ErrorCode SCScriptProvider::HandleMethod(ScriptID methodID, IScriptRequestData* data, IScript* parent)
{
	ErrorCode status = kFailure;

	switch (methodID.Get())
	{
	case e_Speak:
		status = Speak(data, parent);
		break;

	default:
		status = CScriptProvider::HandleMethod(methodID, data, parent);
	}

    return status;
}

/* AccessProperty
*/
ErrorCode SCScriptProvider::AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* parent)
{
	ErrorCode status = kFailure;

	switch (propID.Get())
	{
	case p_Response:
		status = AccessResponse(propID, data, parent);
		break;

    default:
		status = CScriptProvider::AccessProperty(propID, data, parent);
    }

    return status;
}

/* Speak
*/
ErrorCode SCScriptProvider::Speak(IScriptRequestData* data, IScript* parent)
{
	ErrorCode status = kFailure;

	ScriptData scriptData;
	status = data->ExtractRequestData(p_Said, scriptData);
	if (status == kSuccess)
	{
		PMString said;
		status = scriptData.GetPMString(said);
		said.SetTranslatable(kFalse);
		CAlert::InformationAlert(said);
	}

	return status;
}

/* AccessResponse
*/
ErrorCode SCScriptProvider::AccessResponse(ScriptID propID, IScriptRequestData* data, IScript* parent)
{
	ErrorCode status = kFailure;
	if (data->IsPropertyGet())
	{
		ScriptData scriptData;
		scriptData.SetWideString(WideString("Hello from CPP!"));
		data->AppendReturnData( parent, propID, scriptData ) ;
		status = kSuccess;
	}

	return status;
}
