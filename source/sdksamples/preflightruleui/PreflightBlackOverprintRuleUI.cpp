//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/preflightruleui/PreflightBlackOverprintRuleUI.cpp $
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

class PreflightBlackOverprintRuleUI : CPMUnknown<IPreflightRuleUI>
{
public:

    PreflightBlackOverprintRuleUI(IPMUnknown* iBoss);

	/** See IPreflightRuleUI::HasUI
	*/
	virtual bool HasUI() const {return kFalse;}

	/** See IPreflightRuleUI::CreateCustomUI
	*/
    virtual IControlView* CreateCustomUI (IDataBase* iUIDataBase) const;

	/** See IPreflightRuleUI::ApplyDataToCustomUI
	*/
    virtual bool ApplyDataToCustomUI (IControlView* iCustomUI, IPreflightRuleData* iRuleDataToApply) const;

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
CREATE_PMINTERFACE(PreflightBlackOverprintRuleUI, kPreflightBlackOverprintUIImpl)

PreflightBlackOverprintRuleUI::PreflightBlackOverprintRuleUI(IPMUnknown* iBoss) : CPMUnknown<IPreflightRuleUI>(iBoss) 
{
}

IControlView* PreflightBlackOverprintRuleUI::CreateCustomUI (IDataBase* iUIDataBase) const
{
	return nil;
}

bool PreflightBlackOverprintRuleUI::ApplyDataToCustomUI (IControlView* iCustomUI, IPreflightRuleData* iRuleDataToApply) const
{
	return false;
}

bool PreflightBlackOverprintRuleUI::GetDataFromCustomUI (IControlView* iCustomUI, IPreflightRuleData* iRuleData) const
{
	return false;
}

PMString PreflightBlackOverprintRuleUI::GetDataParemeterDescription (const IPreflightRuleData::Key& key) const
{
	if (key == kSDKBlackOverprintRuleParameter)
	{
		return PMString (kSDKBlackOverprintRuleLabel);
	}
	else
	{
		PMString	keyString (key);
		ASSERT_FAIL(FORMAT_ARGS("Unrecognized key (%s)", keyString.GetUTF8String().c_str()));
		return keyString;
	}
}

IPreflightRuleUI::UnitType PreflightBlackOverprintRuleUI::GetDataParemeterUnitType (const IPreflightRuleData::Key& key) const
{
    return IPreflightRuleUI::kDefaultUnit;
}

bool PreflightBlackOverprintRuleUI::GetDataParemeterRange (const IPreflightRuleData::Key& key, ScriptData& maxData, ScriptData& minData) const
{
	return kFalse;
}

bool PreflightBlackOverprintRuleUI::ValidateParameterData (const IPreflightRuleData::Key& key, const ScriptData& newData, PMString& errorString) const
{
	return kFalse;
}

bool PreflightBlackOverprintRuleUI::GetDataParemeterMapping (const IPreflightRuleData::Key& key, ScriptListData& enumData, ScriptListData& stringData) const
{
	return kFalse;
}

IPreflightRuleData::Key PreflightBlackOverprintRuleUI::GetDataParamRoot () const
{
    IPreflightRuleData::Key rootKey ("");
    return rootKey;
}

void PreflightBlackOverprintRuleUI::GetDataParamParent (const IPreflightRuleData::Key& key, IPreflightRuleData::Key& keyParent) const
{
	keyParent = GetDataParamRoot ();
}

bool PreflightBlackOverprintRuleUI::GetDataParamDirectChildren (const IPreflightRuleData::Key& key, std::vector<IPreflightRuleData::Key>& keyList) const
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

PMString PreflightBlackOverprintRuleUI::GetSubpartName(ClassID subpartID) const
{
	return PMString();
}

