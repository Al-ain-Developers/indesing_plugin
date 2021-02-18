<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
<xsl:import href="global-variables.xsl"/>
<xsl:import href="standard-adobe-header.xsl"/>
<xsl:import href="standard-footer.xsl"/>

<xsl:output name="cppfile" method="text"/>

<xsl:template match="preflight-const-h-file">Generating preflight const file...
 <xsl:document href="{/code/@id-header-dir-absolute}{$filesep}{/code/@short-name}PreflightConsts.h" format="cppfile">
<xsl:call-template name="standard-adobe-header">
<xsl:with-param name="suppress-normal-include" select="1"/>
</xsl:call-template>
<xsl:call-template name="preflight-const-h"/>
<xsl:call-template name="standard-footer"/>
</xsl:document>
</xsl:template>

<xsl:template match="preflight-const-h" name="preflight-const-h">
<xsl:variable name="sname" select="/code/@short-name"/>
<xsl:variable name="uppersname" select="translate($sname, 'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>
#pragma once
static const char* k<xsl:value-of select="/code/@short-name"/>RuleParameter = "k<xsl:value-of select="/code/@short-name"/>RuleParameter";
</xsl:template>
</xsl:stylesheet>

