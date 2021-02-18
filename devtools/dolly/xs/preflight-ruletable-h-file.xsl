<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
<xsl:import href="global-variables.xsl"/>
<xsl:import href="standard-adobe-header.xsl"/>
<xsl:import href="standard-footer.xsl"/>

<xsl:output name="cppfile" method="text"/>

<xsl:template match="preflight-ruletable-h-file">Generating preflight rule table file...
 <xsl:document href="{/code/@id-header-dir-absolute}{$filesep}{/code/@short-name}RuleTable.h" format="cppfile">
<xsl:call-template name="standard-adobe-header">
<xsl:with-param name="suppress-normal-include" select="1"/>
</xsl:call-template>
<xsl:call-template name="preflight-ruletable-h"/>
<xsl:call-template name="standard-footer"/>
</xsl:document>
</xsl:template>

<xsl:template match="preflight-ruletable-h" name="preflight-ruletable-h">
<xsl:variable name="sname" select="/code/@short-name"/>
<xsl:variable name="uppersname" select="translate($sname, 'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>
//----------------------------------------------------------------------------------------
//
//    An array giving the details of the native rules. We need at least the boss and the
//    rule ID in this table because we need a lookup capability. And might as well throw
//    in the description since it's all kinda parallel.
//
//    In addition to here you need the following for each rule:
//        - A rule boss defined (in PackageAndPreflightID.h)
//        - An implementation ID for the rule (k[rule]RuleImpl)
//        - An implementation of a rule derived from NativeRuleHandlerBase with the impl
//        - An entry in the class.fr file with the rule boss declared
//        - An entry in S4SPControlFactoryList (aka MWHacks) to force the impl to be linked
//        - A string translation of the description string below
//
//========================================================================================

#pragma once

#include "IPreflightRuleData.h"
#include "<xsl:value-of select="$sname"/>ID.h"

typedef struct
{
    ClassID fBossID;
    const char* fStringID;
    const char* fDesc;
} <xsl:value-of select="$sname"/>PreflightRuleInfo;

static const <xsl:value-of select="$sname"/>PreflightRuleInfo k<xsl:value-of select="$sname"/>Rules[] =
{
    { k<xsl:value-of select="$sname"/>PreflightRuleBoss,                "ADBE_<xsl:value-of select="$sname"/>_Rule",                    k<xsl:value-of select="$sname"/>RuleDescriptionKey}
};

const int32 kNum<xsl:value-of select="$sname"/>Rules = sizeof(k<xsl:value-of select="$sname"/>Rules) / sizeof(*k<xsl:value-of select="$sname"/>Rules);
</xsl:template>
</xsl:stylesheet>

