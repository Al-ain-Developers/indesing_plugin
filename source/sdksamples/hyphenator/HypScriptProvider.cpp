//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hyphenator/HypScriptProvider.cpp $
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
//  Copyright 1997-2008 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"
#include "CScriptProvider.h"
#include "HypID.h"


/** Demonstrates extending the Application script object, adding properties
    
    @ingroup hyphenator
*/
class HypScriptProvider : public CScriptProvider
{
public:
	/** Constructor.
	@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	HypScriptProvider(IPMUnknown* boss);

	/** Destructor. Does nothing.
	*/
	~HypScriptProvider() {}

	/** This method is called if a provider can handle a property.
	 @param propID identifies the ID of the property to handle.
	 @param data identifies an interface pointer used to extract data.
	 @param parent identifies an interface pointer on the script object representing the parent of the application object.
	 */
	virtual ErrorCode AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* parent);
	
private:
	virtual ErrorCode GetHyphPerformanceConstant(ScriptID propID, IScriptRequestData* data, IScript* parent);
};


/* CREATE_PMINTERFACE
Binds the C++ implementation class onto its ImplementationID 
making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(HypScriptProvider, kHypScriptProviderImpl)



HypScriptProvider::HypScriptProvider(IPMUnknown* boss) : CScriptProvider(boss) 
{
}


/* AccessProperty
*/
ErrorCode HypScriptProvider::AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* parent)
{
	ErrorCode status = kFailure;

	switch (propID.Get())
	{
		case p_HypMax:
		case p_HypTotal:
			status = GetHyphPerformanceConstant(propID, data, parent);
			break;
		default:
			status = CScriptProvider::AccessProperty(propID, data, parent);
			break;
    }

    return status;

}


ErrorCode HypScriptProvider::GetHyphPerformanceConstant(ScriptID propID, IScriptRequestData* data, IScript* parent)
{
	ErrorCode result = kSuccess;

	if (data && data->IsPropertyGet()) {	
		ScriptData scriptData;

		switch (propID.Get()) 
		{
			// return the value of the performance metric id.  In scripting, you can use
			// the ID value to access the value for the metric.
			case p_HypMax:
				scriptData.SetInt32(kHypMetricMaxID);
				break;
			case p_HypTotal:
				scriptData.SetInt32(kHypMetricTotalID);
				break;
		}
		data->AppendReturnData( parent, propID, scriptData );
	}
	return result;
}