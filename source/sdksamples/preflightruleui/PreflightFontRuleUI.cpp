//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/preflightruleui/PreflightFontRuleUI.cpp $
//  
//  Owner: InDesign Developer Technologies
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

#include "CPMUnknown.h"
#include "PreflightRuleConsts.h"
#include "LocaleSetting.h"
#include "RsrcSpec.h"
#include "CoreResTypes.h"

#include "IControlView.h"
#include "IPreflightProfile.h"
#include "IPreflightRuleData.h"
#include "IPreflightRuleUI.h"
#include "IPanelControlData.h"
#include "ITriStateControlData.h"
#include "ITextControlData.h"

#include "PreflightRuleUIID.h"
#include "PreflightRuleDataHelper.h"
#include "SDKRuleTable.h"


static const WidgetID kRuleDataWidgetIDs[] = {
											kPreflightRuleUIDataWidgetID1, 
											kPreflightRuleUIDataWidgetID2, 
											kPreflightRuleUIDataWidgetID3, 
											kPreflightRuleUIDataWidgetID4};

class PreflightFontRuleUI : CPMUnknown<IPreflightRuleUI>
{
public:

    PreflightFontRuleUI(IPMUnknown* iBoss);

	/** See IPreflightRuleUI::HasUI
	*/
	virtual bool HasUI() const {return kTrue;}

	/** See IPreflightRuleUI::CreateCustomUI
	*/
    virtual IControlView* CreateCustomUI (IDataBase* iUIDataBase) const;

	/** See IPreflightRuleUI::ApplyDataToCustomUI
	*/
    virtual bool ApplyDataToCustomUI (IControlView* iCustomUI, IPreflightRuleData* iRuleDataToApply) const;

	//	NOTE: no need to implement any of the following if using custom UI.

	/** See IPreflightRuleUI::GetDataFromCustomUI
	*/
    virtual bool GetDataFromCustomUI (IControlView* iCustomUI, IPreflightRuleData* iRuleData) const;

	/** See IPreflightRuleUI::GetDataParemeterDescription
	*/
    virtual PMString GetDataParemeterDescription (const IPreflightRuleData::Key& key) const;

	/** See IPreflightRuleUI::UnitType
	*/
    virtual IPreflightRuleUI::UnitType GetDataParemeterUnitType (const IPreflightRuleData::Key& key) const;

	/** See IPreflightRuleUI::GetDataParemeterRange
	*/
    virtual bool GetDataParemeterRange (const IPreflightRuleData::Key& key, ScriptData& maxData, ScriptData& minData) const;

	/** See IPreflightRuleUI::ValidateParameterData
	*/
    virtual bool ValidateParameterData (const IPreflightRuleData::Key& key, const ScriptData& newData, PMString& errorString) const;

	/** See IPreflightRuleUI::GetDataParemeterMapping
	*/
    virtual bool GetDataParemeterMapping (const IPreflightRuleData::Key& key, ScriptListData& enumData, ScriptListData& stringData) const;

	/** See IPreflightRuleUI::GetDataParamRoot
	*/
    virtual IPreflightRuleData::Key GetDataParamRoot () const;

	/** See IPreflightRuleUI::GetDataParamParent
	*/
    virtual void GetDataParamParent (const IPreflightRuleData::Key& key, IPreflightRuleData::Key& keyParent) const;
	
	/** See IPreflightRuleUI::GetDataParamDirectChildren
	*/
    virtual bool GetDataParamDirectChildren (const IPreflightRuleData::Key& key, std::vector<IPreflightRuleData::Key>& keyList) const;
	
	/** See IPreflightRuleUI::GetSubpartName
	*/
	virtual PMString GetSubpartName(ClassID subpartID) const;
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(PreflightFontRuleUI, kPreflightFontUIImpl)

PreflightFontRuleUI::PreflightFontRuleUI(IPMUnknown* iBoss) : CPMUnknown<IPreflightRuleUI>(iBoss) 
{
}

IControlView* PreflightFontRuleUI::CreateCustomUI (IDataBase* iUIDataBase) const
{
	IControlView* iCustomUI = static_cast<IControlView *>(::CreateObject (
									iUIDataBase,
									RsrcSpec(LocaleSetting::GetLocale(), kPreflightRuleUIPluginID, kViewRsrcType, kPreflightRuleUIDataPanelRsrcID),
									IID_ICONTROLVIEW));
	return iCustomUI;
}

bool PreflightFontRuleUI::ApplyDataToCustomUI (IControlView* iCustomUI, IPreflightRuleData* iRuleDataToApply) const
{
	bool handled = false;

    InterfacePtr<IPreflightRuleData> iUIRuleData (iCustomUI, UseDefaultIID ());
	iUIRuleData->CopyFrom (iRuleDataToApply);

    InterfacePtr<IPanelControlData> iPanelData (iCustomUI, UseDefaultIID ());
	if(!iPanelData)
		return false;

	for(size_t i = 0; i < sizeof(kRuleDataWidgetIDs) / sizeof(WidgetID); ++i)
	{
		IControlView* iWidget = iPanelData->FindWidget(kRuleDataWidgetIDs[i]);
		if(!iWidget)
		{
			continue;
		}
				
		InterfacePtr<ITriStateControlData> iTriStateControlData(iWidget, UseDefaultIID());
		ASSERT(iTriStateControlData);
		if(!iTriStateControlData)
		{
			continue;
		}
		
		InterfacePtr<ITextControlData> iTextControlData(iWidget, UseDefaultIID());
		ASSERT(iTextControlData);
		if(!iTextControlData)
		{
			continue;
		}
		
		//	Dont notify when the rule UI is ask to update view to match data.
		PMString fontName = iTextControlData->GetString();
		fontName.Translate();
		WideString wsFontName(fontName);
		if(PreflightRuleDataHelper::IsAllowed(iUIRuleData, wsFontName))
		{
			iTriStateControlData->Deselect(kTrue, kFalse);
		}
		else
		{
			iTriStateControlData->Select(kTrue, kFalse);
		}
	}
	return true;
}

bool PreflightFontRuleUI::GetDataFromCustomUI (IControlView* iCustomUI, IPreflightRuleData* iRuleData) const
{
	bool handled = true;

    InterfacePtr<IPanelControlData> iPanelData (iCustomUI, UseDefaultIID ());
	if(!iPanelData)
		return handled;


	for(size_t i = 0; i < sizeof(kRuleDataWidgetIDs) / sizeof(WidgetID); ++i)
	{
		IControlView* iWidget = iPanelData->FindWidget(kRuleDataWidgetIDs[i]);
		if(!iWidget)
		{
			continue;
		}
				
		InterfacePtr<ITriStateControlData> iTriStateControlData(iWidget, UseDefaultIID());
		ASSERT(iTriStateControlData);
		if(!iTriStateControlData)
		{
			continue;
		}
		
		InterfacePtr<ITextControlData> iTextControlData(iWidget, UseDefaultIID());
		ASSERT(iTextControlData);
		if(!iTextControlData)
		{
			continue;
		}
		
		PMString fontName = iTextControlData->GetString();
		fontName.Translate();
		WideString wsFontName(fontName); 
		if (iTriStateControlData->IsSelected())
		{
			PreflightRuleDataHelper::DisallowFont(iRuleData, wsFontName);
		}
		else
		{
			PreflightRuleDataHelper::AllowFont(iRuleData, wsFontName);
		}
	}

	return handled;
}

PMString PreflightFontRuleUI::GetDataParemeterDescription (const IPreflightRuleData::Key& key) const
{
	if (key == kSDKFontRuleParameter)
	{
		return PMString (kSDKFontRuleLabel);
	}
	else
	{
		PMString	keyString (key);
		ASSERT_FAIL(FORMAT_ARGS("Unrecognized key (%s)", keyString.GetUTF8String().c_str()));
		return keyString;
	}
}

IPreflightRuleUI::UnitType PreflightFontRuleUI::GetDataParemeterUnitType (const IPreflightRuleData::Key& key) const
{
    return IPreflightRuleUI::kDefaultUnit;
}

bool PreflightFontRuleUI::GetDataParemeterRange (const IPreflightRuleData::Key& key, ScriptData& maxData, ScriptData& minData) const
{
	return kFalse;
}

bool PreflightFontRuleUI::ValidateParameterData (const IPreflightRuleData::Key& key, const ScriptData& newData, PMString& errorString) const
{
	return kFalse;
}

bool PreflightFontRuleUI::GetDataParemeterMapping (const IPreflightRuleData::Key& key, ScriptListData& enumData, ScriptListData& stringData) const
{
	return kFalse;
}

IPreflightRuleData::Key PreflightFontRuleUI::GetDataParamRoot () const
{
    IPreflightRuleData::Key rootKey ("");
    return rootKey;
}

void PreflightFontRuleUI::GetDataParamParent (const IPreflightRuleData::Key& key, IPreflightRuleData::Key& keyParent) const
{
	keyParent = GetDataParamRoot ();
}

bool PreflightFontRuleUI::GetDataParamDirectChildren (const IPreflightRuleData::Key& key, std::vector<IPreflightRuleData::Key>& keyList) const
{
	if (key == GetDataParamRoot ())
	{
		InterfacePtr<IPreflightRuleData>	iRuleData (this, UseDefaultIID ());
		iRuleData->GetAllKeys (keyList);
		return keyList.size () > 0;
	}
	else
	{
		return kFalse;
	}
}

PMString PreflightFontRuleUI::GetSubpartName(ClassID subpartID) const
{
	return PMString();
}

