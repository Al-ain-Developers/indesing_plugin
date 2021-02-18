//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/framelabel/FrmLblScriptsUtils.cpp $
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
#include "IDocument.h"
#include "iuicolorutils.h"
#include "IScript.h"

// General includes:
#include "Utils.h"

// Project includes:
#include "FrmLblScriptingDefs.h"
#include "IFrmLblDataSuite.h"
#include "FrmLblScriptsUtils.h"

/*
*/
ErrorCode FrmLblScriptsUtils::PutScriptFrmLblInfo(FrmLblInfo& frmLblInfo, const ScriptID& propID, IScriptRequestData* data, IScript* script) 
{
	
	ErrorCode result = kFailure;
	do {
		ASSERT(data);
		if (!data)
		{
			break;
		}

		ScriptData inputdata;
		switch (propID.Get())
		{
		case p_FrmLblString:
			{
				// get the label string from the script data
				result = data->ExtractRequestData(propID, inputdata);
				if (result != kSuccess)
				{
					break; 
				}
				inputdata.GetWideString(frmLblInfo.label);
				break;
			}

		case p_FrmLblFontColor:
			{
				// get the font color from the script data	
				UID colorUID = kInvalidUID;
				result = Utils<IUIColorUtils>()->SetUIColor(data, script, propID, &colorUID);
				frmLblInfo.fontColor = colorUID;
				break;
			}

		case p_FrmLblSize:
			{
				// get the size from the script data				
				result = data->ExtractRequestData(propID, inputdata);
				if (result != kSuccess)
				{
					break; 
				}
				inputdata.GetInt32(&frmLblInfo.pointSize);
				break;
			}

		case p_FrmLblVisibility:
			{
				// get the visibility from the script data
				result = data->ExtractRequestData(propID, inputdata);
				if (result != kSuccess)
				{
					break; 
				}
				inputdata.GetBoolean(&frmLblInfo.visibility);
				break;
			}

		case p_FrmLblPosition:
			{
				result = GetPosition(frmLblInfo.position, propID, data);
				break;
			}	
		}

	} while(false);

	return result;
}

/*
*/
void FrmLblScriptsUtils::GetScriptFrmLblInfo(IDocument* doc, FrmLblInfo& frmLblInfo, const ScriptID& propID, IScriptRequestData* data, IScript* script) 
{
	ScriptData scriptData;
	switch (propID.Get())
	{
	case p_FrmLblString:
		{
			// return the label string
			scriptData.SetWideString(frmLblInfo.label);					
			break;
		}

	case p_FrmLblFontColor:
		{
			// return the color
			int32 colorIndex = Utils<IUIColorUtils>()->GetUIColorIndex(frmLblInfo.fontColor, doc);
			if(colorIndex<0)
			{
				Utils<IUIColorUtils>()->GetUIColor(data, script, propID, kInvalidUID, IUIColorUtils::kStockUIPink);
			}
			else
			{
				Utils<IUIColorUtils>()->GetUIColor(data, script, propID, kInvalidUID, colorIndex);
			}
			return;
		}

	case p_FrmLblSize:
		{
			// return the point size
			scriptData.SetInt32(frmLblInfo.pointSize);
			break;
		}

	case p_FrmLblVisibility:
		{
			// return the visibility
			scriptData.SetBoolean(frmLblInfo.visibility);
			break;
		}

	case p_FrmLblPosition:
		{
			// return the position
			ScriptID propertyValue;
			switch(frmLblInfo.position)
			{
			case kFrmLblLeft:
				propertyValue = en_FrmLblLeft;
				break;
			case kFrmLblRight:
				propertyValue = en_FrmLblRight;
				break;
			case kFrmLblTop:
				propertyValue = en_FrmLblTop;
				break;
			case kFrmLblBottom:
				propertyValue = en_FrmLblBottom;
				break;
			}
			scriptData.SetEnumeration(propertyValue);
			break;
		}
	}
	data->AppendReturnData( script, propID, scriptData ) ;
}

/*
*/
ErrorCode FrmLblScriptsUtils::GetPosition(FrmLblPosition& position, const ScriptID& scriptID, IScriptRequestData* data) 	
{
	ErrorCode result = kFailure;
	do {
		ASSERT(data);
		ScriptData inputdata;
		result = data->ExtractRequestData(scriptID, inputdata);
		if (result != kSuccess) {
			break;
		}
		ScriptID propertyValue;
		inputdata.GetEnumeration(&propertyValue);

		switch(propertyValue.Get())
		{
		case en_FrmLblLeft:
			position = kFrmLblLeft;
			break;
		case en_FrmLblRight:
			position = kFrmLblRight;
			break;
		case en_FrmLblTop:
			position = kFrmLblTop;
			break;
		case en_FrmLblBottom:
			position = kFrmLblBottom;
			break;
		}

	} while(false);
	if (result != kSuccess ) {
		result = Utils<IScriptErrorUtils>()->SetMissingRequiredParameterErrorData(data, scriptID);
	}
	return result;
}


