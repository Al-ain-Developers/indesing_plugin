<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
<xsl:import href="global-variables.xsl"/>
<xsl:import href="standard-adobe-header.xsl"/>
<xsl:import href="standard-footer.xsl"/>

<xsl:output name="cppfile" method="text"/>
<xsl:template match="factorylist-file">Generating FactoryList.h file from template...
<xsl:document href="{/code/@source-dir-absolute}{$filesep}{/code/@short-name}FactoryList.h" format="cppfile">
<xsl:call-template name="standard-adobe-header">
 <xsl:with-param name="suppress-normal-include" select="1"/>
</xsl:call-template>
<xsl:call-template name="factorylist"/>
<xsl:call-template name="standard-footer"/>
</xsl:document>
</xsl:template>

<xsl:template match="factorylist" name="factorylist">
<xsl:for-each select="/code/impl-item[@impl-id]">REGISTER_PMINTERFACE(<xsl:value-of select="@impl-name"/>, <xsl:value-of select="@impl-id"/>)
</xsl:for-each>
</xsl:template>
</xsl:stylesheet>

