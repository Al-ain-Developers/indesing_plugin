<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
<xsl:import href="global-variables.xsl"/>
<xsl:import href="standard-adobe-header.xsl"/>
<xsl:import href="standard-footer.xsl"/>
<xsl:output name="cppfile" method="text"/>

<xsl:template match="impl-item[@impl-file = 'preflight-ruleui-impl-file']">
Generating <xsl:value-of select="@impl-name"/>
<xsl:document href="{/code/@source-dir-absolute}{$filesep}{@impl-name}.cpp" format="cppfile">
<xsl:call-template name="standard-adobe-header"/>
  <xsl:call-template name="preflight-ruleui"/>
  <xsl:call-template name="standard-footer"/>
 </xsl:document>
</xsl:template>

<xsl:template name="preflight-ruleui" match="preflight-ruleui">
<xsl:variable name="sname" select="/code/@short-name"/>
<xsl:variable name="uppersname" select="translate($sname, 'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>

#include "IPreflightProfile.h"
#include "IPreflightRuleData.h"
#include "IPreflightRuleUI.h"
#include "CPMUnknown.h"
#include "<xsl:value-of select="/code/@short-name"/>PreflightConsts.h"
#include "<xsl:value-of select="/code/@short-name"/>ID.h"

/**
    <xsl:variable name="groupname" select="translate(/code/@long-name, 'ABCDEFGHIJKLMNOPQRSTUVWXYZ', 'abcdefghijklmnopqrstuvwxyz')"/>
    @ingroup <xsl:value-of select="$groupname"/>
*/
class <xsl:value-of select="@impl-name"/> : CPMUnknown&lt;IPreflightRuleUI&gt;
{
private:

public:
    <xsl:value-of select="@impl-name"/>(IPMUnknown* iBoss)
        : CPMUnknown&lt;IPreflightRuleUI&gt;(iBoss) {}

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
    virtual PMString GetDataParemeterDescription (const IPreflightRuleData::Key&amp; key) const;

	/** See IPreflightRuleUI::UnitType
	*/
    virtual IPreflightRuleUI::UnitType GetDataParemeterUnitType (const IPreflightRuleData::Key&amp; key) const;

	/** See IPreflightRuleUI::GetDataParemeterRange
	*/
    virtual bool GetDataParemeterRange (const IPreflightRuleData::Key&amp; key, ScriptData&amp; maxData, ScriptData&amp; minData) const;

	/** See IPreflightRuleUI::ValidateParameterData
	*/
    virtual bool ValidateParameterData (const IPreflightRuleData::Key&amp; key, const ScriptData&amp; newData, PMString&amp; errorString) const;

	/** See IPreflightRuleUI::GetDataParemeterMapping
	*/
    virtual bool GetDataParemeterMapping (const IPreflightRuleData::Key&amp; key, ScriptListData&amp; enumData, ScriptListData&amp; stringData) const;

	/** See IPreflightRuleUI::GetDataParamRoot
	*/
    virtual IPreflightRuleData::Key GetDataParamRoot () const;

	/** See IPreflightRuleUI::GetDataParamParent
	*/
    virtual void GetDataParamParent (const IPreflightRuleData::Key&amp; key, IPreflightRuleData::Key&amp; keyParent) const;
	
	/** See IPreflightRuleUI::GetDataParamDirectChildren
	*/
    virtual bool GetDataParamDirectChildren (const IPreflightRuleData::Key&amp; key, std::vector&lt;IPreflightRuleData::Key&gt; &amp; keyList) const;
	
	/** See IPreflightRuleUI::GetSubpartName
	*/
	virtual PMString GetSubpartName(ClassID subpartID) const;
};

CREATE_PMINTERFACE(<xsl:value-of select="@impl-name"/>, <xsl:value-of select="@impl-id"/>);


IControlView* <xsl:value-of select="@impl-name"/>::CreateCustomUI (IDataBase* iUIDataBase) const
{
	// In most cases, auto generated UI is good enough, but you can supply your own UI.  In order to create the custom UI, you will have to create the usual
	// panel for it in your .fr file, then you initialize it using the IPrefightRuleData on the same rule boss as this interface to set up the
	// widgets.  e.g.
	/*
        IControlView*    iPanel = static_cast&lt;IControlView *&gt;(::CreateObject (
                                        iUIDataBase,
                                        RsrcSpec(LocaleSetting::GetLocale(), kPackageAndPreflightUIPlugInID, kViewRsrcType, kProfileDlgLinksRulePanelRsrcID),
                                        IID_ICONTROLVIEW));
        if (iPanel != nil)
        {
            InterfacePtr&lt;IPreflightRuleData&gt; iRuleData (this, UseDefaultIID ());
            InterfacePtr&lt;IPanelControlData&gt;    iPanelData (iPanel, UseDefaultIID ());

            bool16        doMissingLinks = GetDataParam (iRuleData, "missing");
            bool16        doModifiedLinks = GetDataParam (iRuleData, "modified");;

            SetCheckbox (iPanelData, kProfileDlgRuleMissingLinkCheckBoxWID, doMissingLinks);
            SetCheckbox (iPanelData, kProfileDlgRuleModifiedLinkCheckBoxWID, doModifiedLinks);
        }

        return iPanel;
  	
	*/
	return nil;
}

bool <xsl:value-of select="@impl-name"/>::ApplyDataToCustomUI (IControlView* iCustomUI, IPreflightRuleData* iRuleDataToApply) const
{
	// This should be similiar to CreateCustomUI, except you set the widget values on the custom UI based on the IPreflightRuleData parameter passed in to you.
	/*
		bool	handled = kFalse;
        IControlView*    iLinksRuleUI = nil;;
        InterfacePtr&lt;IPanelControlData&gt;    iPanelData (iCustomUI, UseDefaultIID ());
        if (iCustomUI != nil &amp;&amp; iPanelData != nil &amp;&amp;
            iCustomUI->GetWidgetID () != kProfileDlgRuleLinksRulePanelWID)
        {
            iLinksRuleUI = iPanelData->FindWidget (kProfileDlgRuleLinksRulePanelWID);
        }
        else if (iCustomUI != nil)
        {
            iLinksRuleUI = iCustomUI;
        }

        if (iLinksRuleUI != nil)
        {
            handled = kTrue;

            bool16        doMissingLinks = GetDataParam (iRuleDataToApply, "missing");
            bool16        doModifiedLinks = GetDataParam (iRuleDataToApply, "modified");;

            InterfacePtr&lt;IPanelControlData&gt;    iiLinksRulePanelData (iLinksRuleUI, UseDefaultIID ());
            SetCheckbox (iPanelData, kProfileDlgRuleMissingLinkCheckBoxWID, doMissingLinks);
            SetCheckbox (iPanelData, kProfileDlgRuleModifiedLinkCheckBoxWID, doModifiedLinks);
        }

        return handled;	
	*/
	return kFalse;
}

bool <xsl:value-of select="@impl-name"/>::GetDataFromCustomUI (IControlView* iCustomUI, IPreflightRuleData* iRuleData) const
{
	return kFalse;
}

PMString <xsl:value-of select="@impl-name"/>::GetDataParemeterDescription (const IPreflightRuleData::Key&amp; key) const
{
	if (key == k<xsl:value-of select="/code/@short-name"/>RuleParameter)
		return PMString (k<xsl:value-of select="/code/@short-name"/>RuleParameterLabel);
	else
	{
		PMString	keyString (key);
		ASSERT_FAIL (FORMAT_ARGS ("Unrecognized key (%s)", keyString.GetPlatformString ().c_str ()));
		return keyString;
	}
}

IPreflightRuleUI::UnitType <xsl:value-of select="@impl-name"/>::GetDataParemeterUnitType (const IPreflightRuleData::Key&amp; key) const
{
    return IPreflightRuleUI::kDefaultUnit;
}

bool <xsl:value-of select="@impl-name"/>::GetDataParemeterRange (const IPreflightRuleData::Key&amp; key, ScriptData&amp; maxData, ScriptData&amp; minData) const
{
	return kFalse;
}

bool <xsl:value-of select="@impl-name"/>::ValidateParameterData (const IPreflightRuleData::Key&amp; key, const ScriptData&amp; newData, PMString&amp; errorString) const
{
	return kFalse;
}

bool <xsl:value-of select="@impl-name"/>::GetDataParemeterMapping (const IPreflightRuleData::Key&amp; key, ScriptListData&amp; enumData, ScriptListData&amp; stringData) const
{
	return kFalse;
}

IPreflightRuleData::Key <xsl:value-of select="@impl-name"/>::GetDataParamRoot () const
{
    IPreflightRuleData::Key    rootKey ("");
    return rootKey;
}

void <xsl:value-of select="@impl-name"/>::GetDataParamParent (const IPreflightRuleData::Key&amp; key, IPreflightRuleData::Key&amp; keyParent) const
{
	keyParent = GetDataParamRoot ();
}
bool <xsl:value-of select="@impl-name"/>::GetDataParamDirectChildren (const IPreflightRuleData::Key&amp; key, std::vector&lt;IPreflightRuleData::Key&gt; &amp; keyList) const
{
	if (key == GetDataParamRoot ())
	{
		InterfacePtr&lt;IPreflightRuleData&gt;	iRuleData (this, UseDefaultIID ());
		iRuleData->GetAllKeys (keyList);
		return keyList.size () &gt; 0;
	}
	else
	{
		return kFalse;
	}
}

PMString <xsl:value-of select="@impl-name"/>::GetSubpartName(ClassID subpartID) const
{
	return PMString();
}


</xsl:template>
</xsl:stylesheet>