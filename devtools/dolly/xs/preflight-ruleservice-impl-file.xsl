<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
<xsl:import href="global-variables.xsl"/>
<xsl:import href="standard-adobe-header.xsl"/>
<xsl:import href="standard-footer.xsl"/>
<xsl:output name="cppfile" method="text"/>

<xsl:template match="impl-item[@impl-file = 'preflight-ruleservice-impl-file']">
Generating <xsl:value-of select="@impl-name"/>
<xsl:document href="{/code/@source-dir-absolute}{$filesep}{@impl-name}.cpp" format="cppfile">
<xsl:call-template name="standard-adobe-header"/>
  <xsl:call-template name="preflight-ruleservice"/>
  <xsl:call-template name="standard-footer"/>
 </xsl:document>
</xsl:template>

<xsl:template name="preflight-ruleservice" match="preflight-ruleservice">
<xsl:variable name="sname" select="/code/@short-name"/>
<xsl:variable name="uppersname" select="translate($sname, 'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>

// Interface includes:

#include "IPreflightProfile.h"
#include "IPreflightRuleData.h"
#include "IPreflightRuleService.h"
#include "IPreflightRuleVisitor.h"

#include "CPMUnknown.h"
#include "IPMStream.h"
#include "CreateObject.h"
#include "<xsl:value-of select="$sname"/>RuleTable.h"

/**
    <xsl:variable name="groupname" select="translate(/code/@long-name, 'ABCDEFGHIJKLMNOPQRSTUVWXYZ', 'abcdefghijklmnopqrstuvwxyz')"/>
    @ingroup <xsl:value-of select="$groupname"/>
*/
class <xsl:value-of select="@impl-name"/> : CPMUnknown&lt;IPreflightRuleService&gt;
{
public:
    <xsl:value-of select="@impl-name"/>(IPMUnknown* iBoss);

	 	/** See IPreflightRuleService::GetAllRules
		*/
	   virtual PreflightRuleIDVector GetAllRules() const;

	 	/** See IPreflightRuleService::CreateRule
		*/
	   virtual IPreflightRuleInfo* CreateRule(const PreflightRuleID&amp; ruleID, IDataBase* db) const;

		/** See IPreflightRuleService::GetRuleCategory
		*/
		virtual PMString GetRuleCategory(const PreflightRuleID&amp; ruleID) const;

		/** See IPreflightRuleService::GetRuleSortValue
		*/
		virtual PMString GetRuleSortValue(const PreflightRuleID&amp; ruleID) const;
};

CREATE_PMINTERFACE(<xsl:value-of select="@impl-name"/>, <xsl:value-of select="@impl-id"/>);

<xsl:value-of select="@impl-name"/>::<xsl:value-of select="@impl-name"/>(IPMUnknown* iBoss)
: CPMUnknown&lt;IPreflightRuleService&gt;(iBoss)
{
}

PreflightRuleIDVector <xsl:value-of select="@impl-name"/>::GetAllRules() const
{
	// Note: We're typically called only once per session for this list so there's no
	// sense in trying to cache the result..

	PreflightRuleIDVector rules;

	for(int32 n = 0; n &lt; kNum<xsl:value-of select="$sname"/>Rules; n++)
	{
		rules.push_back(PreflightRuleID(k<xsl:value-of select="$sname"/>Rules[n].fStringID));
	}

	return rules;
}

IPreflightRuleInfo* <xsl:value-of select="@impl-name"/>::CreateRule(const PreflightRuleID&amp; ruleID, IDataBase* db) const
{
	PMString desc, plugin;
	ClassID bossID = 0;

	for(int32 n = 0; n &lt; kNum<xsl:value-of select="$sname"/>Rules; n++)
	{
		if (ruleID == PreflightRuleID(k<xsl:value-of select="$sname"/>Rules[n].fStringID))
		{
			desc = k<xsl:value-of select="$sname"/>Rules[n].fDesc;
			bossID = k<xsl:value-of select="$sname"/>Rules[n].fBossID;
			break;
		}
	}

	if (bossID == 0)
	{
		ASSERT_FAIL("<xsl:value-of select="@impl-name"/>::CreateRule: This rule ID isn't one I recognize.");
		return nil;
	}

	IPreflightRuleInfo* iRule = (IPreflightRuleInfo*)CreateObject(db, bossID, IID_IPREFLIGHTRULEINFO);
	if (!iRule)
	{
		ASSERT_FAIL("Unable to create SDK rule boss. OK to continue but something's amiss in preflight.");
		return iRule;
	}

	iRule->SetRuleID(ruleID);

	plugin = "InDesign SDK Rule Set";

	iRule->SetRuleDescription(desc);
	iRule->SetPluginDescription(plugin);

	// Initialize defaults via the visitor.

	InterfacePtr&lt;IPreflightRuleVisitor&gt; ruleVisitor(iRule, UseDefaultIID());
	if(ruleVisitor)
	{
		ruleVisitor->UpdateRuleData();
	}

	return iRule;
}

PMString <xsl:value-of select="@impl-name"/>::GetRuleCategory(const PreflightRuleID&amp; ruleID) const
{
	return PMString(k<xsl:value-of select="/code/@short-name"/>CategoryKey);
}

PMString <xsl:value-of select="@impl-name"/>::GetRuleSortValue(const PreflightRuleID&amp; ruleID) const
{
	return PMString("");
}
</xsl:template>
</xsl:stylesheet>