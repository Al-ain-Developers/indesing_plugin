//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalink/CusDtLnkOptionScriptProvider.cpp $
//  
//  Owner: hhorton
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

#include "IDocument.h"
#include "IScript.h"
#include "IScriptRequestData.h"
#include "IWorkspace.h"
#include "ICusDtLnkOptions.h"
#include "ICusDtLnkFacade.h"

#include "CmdUtils.h"
#include "PrefsScriptProvider.h"
#include "ScriptingDefs.h"

#include "CusDtLnkScriptingDefs.h"
#include "CusDtLnkID.h"

class CusDtLnkOptionScriptProvider : public PrefsScriptProvider
{
public:
	CusDtLnkOptionScriptProvider(IPMUnknown *boss);

    virtual ErrorCode    AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script);

protected:
    ErrorCode AccessCusDtLnkOptionPairList(ScriptID propID, IScriptRequestData*data, IScript*script, const PMIID& prefInterfaceID);
};

CREATE_PMINTERFACE(CusDtLnkOptionScriptProvider, kCusDtLnkOptionScriptProviderImpl);

CusDtLnkOptionScriptProvider::CusDtLnkOptionScriptProvider(IPMUnknown *boss):
	PrefsScriptProvider(boss)
{
	DefinePreference( c_CusDtLnkOption, p_CusDtLnkOption ) ;
}

ErrorCode CusDtLnkOptionScriptProvider::AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{
    switch (propID.Get())
    {
        case p_CusDtLnkOptionDatabasePair:
		{
			return AccessCusDtLnkOptionPairList(propID, data, script, IID_ICUSDTLNKDATABASESASOPTIONS ) ;
		}
        case p_CusDtLnkOptionAssetPair:
		{
			return AccessCusDtLnkOptionPairList(propID, data, script, IID_ICUSDTLNKOPTIONS ) ;
		}
        default:
            return PrefsScriptProvider::AccessProperty(propID, data, script);
    }
}


int32 CusDtLnkOptionScriptProvider::AccessCusDtLnkOptionPairList(ScriptID propID, IScriptRequestData*data, IScript*script,  const PMIID& prefInterfaceID)
{
 

    ScriptData scriptData;
    ScriptListData listData;
    int32 err = kSuccess;

	InterfacePtr<IWorkspace> ws(Utils<IScriptUtils>()->QueryWorkspaceFromScript(script, data->GetRequestContext() ));
	InterfacePtr<ICusDtLnkOptions> cusOptions( ws, prefInterfaceID ) ;

    if (data->IsPropertyGet())
    {
        for (int32 j = 0; j < cusOptions->GetKeyValuePairCount(); j++)
        {
            ScriptListData itemListData;
            ScriptData itemScriptData;

            scriptData.SetWideString(cusOptions->GetNthKey(j));
            itemListData.push_back(scriptData);
            scriptData.SetWideString(cusOptions->GetValueFromKey(cusOptions->GetNthKey(j)));
            itemListData.push_back(scriptData);

            itemScriptData.SetList(itemListData);
            listData.push_back(itemScriptData);
        }

        scriptData.SetList(listData);
        data->AppendReturnData( script, propID, scriptData ) ;
    }
    else if (data->IsPropertyPut())
    {
        err = data->ExtractRequestData(propID.Get(), scriptData ) ;
        if (err != kSuccess) return err ;

		Utils<ICusDtLnkFacade> facade;
        WideString key;
        WideString value;
        err = scriptData.GetList(listData);
        if (err == kSuccess)
        {
            for (int32 i = 0; i < listData.size(); i++)
            {
                ScriptListData itemListData;
                ScriptData itemScriptData = listData[i];
                err = itemScriptData.GetList(itemListData);
                if (err == kSuccess)
                {
                    if (itemListData.size() == 2)
                    {
                        itemListData[0].GetWideString(key);
                        itemListData[1].GetWideString(value);

						err = facade->SetKeyValuePair(ws, key, value, prefInterfaceID);

                   }
                }
            }

        }

    }
    return err;
}

