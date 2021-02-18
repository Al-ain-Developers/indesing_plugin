//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customconditionaltext/CusCondTxtScriptProvider.cpp $
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
#include "IScriptUtils.h"
#include "IBoolData.h"
#include "IWorkspace.h"
#include "IDocument.h"

// General includes:
#include "CScriptProvider.h"
#include "Utils.h"
#include "GenericID.h"
#include "UIDList.h"

// Project includes:
#include "CusCondTxtID.h"
#include "ICustomConditionTag.h"
#include "CusCondTxtScriptingDefs.h"
#include "CusCondTxtFacade.h"

class CusCondTxtScriptProvider : public CScriptProvider
{
public:
	/**	Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	 */
	CusCondTxtScriptProvider(IPMUnknown* boss);

	/**	Destructor.
	 */
	~CusCondTxtScriptProvider() {}

	/** Called if a provider can handle a property.
		@param propID identifies the ID of the property to handle.
		@param data identifies an interface pointer used to extract data.
		@param script identifies an interface pointer on the script object representing the parent of the application object.
	 */
	virtual ErrorCode  AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script);

private:
	ErrorCode  AccessCustomConditionProperty(ScriptID propID, IScriptRequestData* data, IScript* script);

	ErrorCode GetProperty(ICustomConditionTag* cusCondTag, ScriptID propID, IScriptRequestData* data, IScript* script);

	ErrorCode SetProperty(ICustomConditionTag* cusCondTag, ScriptID propID, IScriptRequestData* data, IScript* script);
};

/*	Make the implementation available to the application.
*/
CREATE_PMINTERFACE(CusCondTxtScriptProvider, kCusCondTxtScriptProviderImpl)

/*	
*/

CusCondTxtScriptProvider::CusCondTxtScriptProvider(IPMUnknown* boss)
	: CScriptProvider(boss) 
{
}

/* AccessProperty
*/
ErrorCode CusCondTxtScriptProvider::AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{
	switch (propID.Get())
	{
		case p_CusCondTxtPrintVisible:
		case p_CusCondTxtIdmlVisible:
			return AccessCustomConditionProperty(propID, data, script);

		default:
			// delegate to parent class
			return CScriptProvider::AccessProperty(propID, data, script);
	}
}

ErrorCode  CusCondTxtScriptProvider::AccessCustomConditionProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{
	UIDRef item = ::GetUIDRef(script);		
	InterfacePtr<ICustomConditionTag> cusCondTag(item, UseDefaultIID());
	ASSERT(cusCondTag);
	if(cusCondTag)
	{
		if (data->IsPropertyPut()) 
		{
			return SetProperty(cusCondTag, propID, data, script);
		}
		else 
		{	
			return GetProperty(cusCondTag, propID, data, script);
		}
	}
	return kFailure;
}

ErrorCode CusCondTxtScriptProvider::GetProperty(ICustomConditionTag* cusCondTag, ScriptID propID, IScriptRequestData* data, IScript* script)
{
	ScriptData scriptData;	
	switch (propID.Get())
	{
		case p_CusCondTxtPrintVisible:
		{
			scriptData.SetBoolean(cusCondTag->IsPrintVisible());
			break;
		}
			
		case p_CusCondTxtIdmlVisible:
		{
			scriptData.SetBoolean(cusCondTag->IsIdmlVisible());
			break;
		}
	}
	
	data->AppendReturnData( script, propID, scriptData ) ;
	return kSuccess;
}

ErrorCode CusCondTxtScriptProvider::SetProperty(ICustomConditionTag* cusCondTag, ScriptID propID, IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;
	
	ScriptData inputdata;
	result = data->ExtractRequestData(propID, inputdata);
	if (result != kSuccess)
	{
		return result;
	}
	
	bool16 scriptValue;
	inputdata.GetBoolean(&scriptValue);
	
	switch (propID.Get())
	{
	case p_CusCondTxtPrintVisible:
		result = Utils<ICusCondTxtFacade>()->SetPrintVisibility(::GetUIDRef(cusCondTag), scriptValue);
		break;

	case p_CusCondTxtIdmlVisible:
		result = Utils<ICusCondTxtFacade>()->SetIDMLVisibility(::GetUIDRef(cusCondTag), scriptValue);
		break;
	}
	return result;
}
// End, CusCondTxtScriptProvider.cpp
