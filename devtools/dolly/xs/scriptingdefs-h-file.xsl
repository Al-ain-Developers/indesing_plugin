<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
<xsl:import href="global-variables.xsl"/>
<xsl:import href="standard-adobe-header.xsl"/>
<xsl:import href="standard-footer.xsl"/>

<xsl:output name="cppfile" method="text"/>

<xsl:template match="scriptingdefs-h-file">Generating scriptingdefs.h file from template...
 <xsl:document href="{/code/@id-header-dir-absolute}{$filesep}{/code/@short-name}ScriptingDefs.h" format="cppfile">
<xsl:call-template name="standard-adobe-header">
<xsl:with-param name="suppress-normal-include" select="1"/>
</xsl:call-template>
<xsl:call-template name="scriptingdefs-h"/>
<xsl:call-template name="standard-footer"/>
</xsl:document>
</xsl:template>

<xsl:template match="scriptingdefs-h" name="scriptingdefs-h">

#ifndef __<xsl:value-of select="/code/@short-name"/>ScriptingDefs_h__
#define __<xsl:value-of select="/code/@short-name"/>ScriptingDefs_h__

#define kCPrefs_CLSID { 0x8d448fe0, 0x8194, 0x11d3, { 0xa6, 0x53, 0x0, 0xe0, 0x98, 0x71, 0xa, 0x6f } }
DECLARE_GUID(CPrefs_CLSID, kCPrefs_CLSID);

// Note: 4-char IDs below must be unique.
// See ScriptingDefs.h for further information.

// Method IDs
enum <xsl:value-of select="/code/@short-name"/>ScriptEvents
{
	e_Speak		= 'eSpk'
};

// Property IDs
enum <xsl:value-of select="/code/@short-name"/>ScriptProperties
{
	p_Said		= 'pSed',
	p_Response		= 'pRsp'
};


#endif // __<xsl:value-of select="/code/@short-name"/>ScriptingDefs_h__
</xsl:template>
</xsl:stylesheet>

