<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
<xsl:import href="global-variables.xsl"/>
<xsl:output method="xml" indent="yes"/>


<xsl:template match="rsp-odfrc-file">
<xsl:if test="not(string(/code/@win-specific-odfrc-rsp-file))">
Generating rspodfrc file from template...
 <xsl:document href="{/code/@win-project-dir}{$filesep}{/code/@long-name}ODFRC.rsp" method="text" indent="yes">
  <xsl:call-template name="rspodfrcfile"/>
  </xsl:document>
</xsl:if>
</xsl:template>
<xsl:template match="rspodfrcfile" name="rspodfrcfile">
<xsl:variable name="sdkdir" select="/code/@win-sdk-dir"/>
-i "<xsl:value-of select="$sdkdir"/>\source\precomp\msvc"
-i "<xsl:value-of select="$sdkdir"/>\source\public\interfaces\xmedia"
-i "<xsl:value-of select="$sdkdir"/>\source\public\interfaces\preflight"
-i "<xsl:value-of select="$sdkdir"/>\source\public\interfaces\ui"
-i "<xsl:value-of select="$sdkdir"/>\source\public\interfaces\tables"
-i "<xsl:value-of select="$sdkdir"/>\source\public\interfaces\text"
-i "<xsl:value-of select="$sdkdir"/>\source\public\interfaces\graphics"
-i "<xsl:value-of select="$sdkdir"/>\source\public\libs\widgetbin\includes"
-i "<xsl:value-of select="$sdkdir"/>\source\public\interfaces\workgroup"
-i "<xsl:value-of select="$sdkdir"/>\source\public\interfaces\interactive"
-i "<xsl:value-of select="$sdkdir"/>\source\public\interfaces\interactive\ui"
-i "<xsl:value-of select="$sdkdir"/>\source\public\interfaces\colormgmt"
-i "<xsl:value-of select="$sdkdir"/>\source\public\interfaces\utils"
-i "<xsl:value-of select="$sdkdir"/>\source\public\interfaces\incopy"
-i "<xsl:value-of select="$sdkdir"/>\source\public\interfaces\layout"
-i "<xsl:value-of select="$sdkdir"/>\source\public\interfaces\architecture"
-i "<xsl:value-of select="$sdkdir"/>\source\public\interfaces\cjk"
-i "<xsl:value-of select="$sdkdir"/>\source\public\interfaces\preflight"
-i "<xsl:value-of select="$sdkdir"/>\source\public\facades\text"
-i "<xsl:value-of select="$sdkdir"/>\source\public\facades\graphics"
-i "<xsl:value-of select="$sdkdir"/>\source\public\facades\layout"
-i "<xsl:value-of select="$sdkdir"/>\source\precomp\common"
-i "<xsl:value-of select="$sdkdir"/>\source\public\includes"
-i "<xsl:value-of select="$sdkdir"/>\source\public\widget\includes"
-i "<xsl:value-of select="$sdkdir"/>\source\public\libs\publiclib\plugins"
-i "<xsl:value-of select="$sdkdir"/>\source\public\libs\publiclib\files"
-i "<xsl:value-of select="$sdkdir"/>\source\public\libs\publiclib\objectmodel"
-i "<xsl:value-of select="$sdkdir"/>\source\sdksamples\common"


<xsl:if test="/code/@win-id-header-dir != /code/@win-source-dir">-i "<xsl:value-of select="/code/@win-id-header-dir"/>"</xsl:if>
</xsl:template>
</xsl:stylesheet>
