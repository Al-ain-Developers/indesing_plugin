<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
<xsl:import href="global-variables.xsl"/>
<xsl:output method="xml" indent="yes"/>


<xsl:template match="ReleaseX64-vsprops-file">Generating ReleaseX64 vsprops file from template...
 <xsl:document href="{/code/@win-project-dir}{$filesep}{/code/@short-name}ReleaseX64.sdk.props" method="xml" indent="yes">
  <xsl:call-template name="ReleaseX64"/>
  </xsl:document>
</xsl:template>

<xsl:template match="ReleaseX64" name="ReleaseX64">
<xsl:variable name="sname" select="/code/@short-name"/>
<xsl:variable name="sdkdir" select="/code/@win-sdk-dir"/>

<Project DefaultTargets="Build" ToolsVersion="4.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <PropertyGroup>
    <xsl:element name="ExecutablePath"><xsl:value-of select="$sdkdir" />\devtools\bin\;$(ExecutablePath)</xsl:element>
  </PropertyGroup>
  <ImportGroup Label="PropertySheets">
    <Import><xsl:attribute name="Project"><xsl:value-of select="$sdkdir" />\build\win\prj\ReleaseX64.props</xsl:attribute></Import>
  </ImportGroup>
  <PropertyGroup Label="UserMacros">
    <_ProjectFileVersion>10.0.40219.1</_ProjectFileVersion>
    <xsl:element name="ID_SDK_DIR"><xsl:value-of select="$sdkdir" /></xsl:element>
  </PropertyGroup>
</Project>
</xsl:template>
</xsl:stylesheet>