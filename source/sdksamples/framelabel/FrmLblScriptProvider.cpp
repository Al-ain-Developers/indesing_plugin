//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/framelabel/FrmLblScriptProvider.cpp $
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
#include "IScriptErrorUtils.h"
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
#include "IFrmLblDataFacade.h"
#include "FrmLblID.h"
#include "FrmLblType.h"
#include "FrmLblScriptingDefs.h"
#include "FrmLblScriptsUtils.h"


/** From SDK sample; Handles scripting of the FrameLabel properties.
	See the Provider statement for kFrmLblScriptProviderBoss in FrmLbl.fr 
	for the list of scripting objects
	on which the FrameLabel properties is available.

	@ingroup framelabel
 */

class FrmLblScriptProvider : public CScriptProvider
{
public:
	/**	Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	 */
	FrmLblScriptProvider(IPMUnknown* boss);

	/**	Destructor.
	 */
	~FrmLblScriptProvider() {}

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
	/** Set or get the value of kFrmLblAttrBoss.
		@param propID identifies the ID of the property to handle (p_FrmLblData).
		@param data identifies an interface pointer used to extract parameter data.
		@param script identifies an interface pointer on a type of page item script object.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode AccessFrameLabelProperty(ScriptID propID, IScriptRequestData* data, IScript* script);
	

};

/*	Make the implementation available to the application.
*/
CREATE_PMINTERFACE(FrmLblScriptProvider, kFrmLblScriptProviderImpl)

/*	
*/

FrmLblScriptProvider::FrmLblScriptProvider(IPMUnknown* boss)
	: CScriptProvider(boss) 
{
}
/* HandleMethod
*/
ErrorCode FrmLblScriptProvider::HandleMethod(ScriptID methodID, IScriptRequestData* data, IScript* script)
{
	// No events to handle in this script provider - delegate to parent class.
	return CScriptProvider::HandleMethod(methodID, data, script);
}

/* AccessProperty
*/
ErrorCode FrmLblScriptProvider::AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;
	do
	{
		switch (propID.Get())
		{
			case p_FrmLblString:
			case p_FrmLblSize:
			case p_FrmLblVisibility:
			case p_FrmLblFontColor:
			case p_FrmLblPosition:			
			{
				result = this->AccessFrameLabelProperty(propID, data, script);
				break;
			}

			default:
			{
				// delegate to parent class
				result = CScriptProvider::AccessProperty(propID, data, script);
				break;
			}
		}
	} while (false);

	if (result != kSuccess) 
	{
		result = kFrmLblFailureErrorCode;
	}
	return result;
}

/* AccessFrameLabelProperty
*/
ErrorCode FrmLblScriptProvider::AccessFrameLabelProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;
	do 
	{
		if (script == nil)
		{
			ASSERT_FAIL("FrmLblScriptProvider::AccessFrameLabelProperty - script is nil, so we cannot proceed.");
			break;
		}

		UIDRef item = GetUIDRef(script);
		InterfacePtr<IDocument>	iDoc(item.GetDataBase(), item.GetDataBase()->GetRootUID(), IID_IDOCUMENT);
		ASSERT(iDoc);
		if(!iDoc)
		{
			break;
		}


		// get the current properties
		FrmLblInfo frmLblInfo;
		Utils<IFrmLblDataFacade>()->GetFrameLabelProperties(item, frmLblInfo);		
		
		if (data->IsPropertyPut()) 
		{

			result = FrmLblScriptsUtils::PutScriptFrmLblInfo(frmLblInfo, propID, data, script);

			if (result != kSuccess)
			{
				break;
			}
			else
			{
				// update all properties
				result = Utils<IFrmLblDataFacade>()->UpdateFrameLabelProperties(item, frmLblInfo);
			}
		}
		else if (data->IsPropertyGet()) 
		{	
			FrmLblScriptsUtils::GetScriptFrmLblInfo(iDoc, frmLblInfo, propID, data, script);
			result = kSuccess;
		}
	} while (false);

	if (result != kSuccess) 
	{
		result = kFrmLblFailureErrorCode;
	}
	return result;
}

// End, FrmLblScriptProvider.cpp
