<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
<xsl:import href="global-variables.xsl"/>

<xsl:template match="rsp-cpp-file">
<xsl:if test="not(string(/code/@win-specific-cpp-rsp-file))">Generating rspcpp file from template...
 <xsl:document href="{/code/@win-project-dir}{$filesep}{/code/@long-name}CPP.rsp" method="text" indent="yes">
  <xsl:call-template name="rspcppfile"/>
  </xsl:document>
</xsl:if>
</xsl:template>

<xsl:template match="rspcppfile" name="rspcppfile"><xsl:variable name="sdkdir" select="/code/@win-sdk-dir"/>
/I "<xsl:value-of select="$sdkdir"/>\source\precomp\msvc"
/I "<xsl:value-of select="$sdkdir"/>\source\public\interfaces\xmedia"
/I "<xsl:value-of select="$sdkdir"/>\source\public\interfaces\preflight"
/I "<xsl:value-of select="$sdkdir"/>\source\public\interfaces\ui"
/I "<xsl:value-of select="$sdkdir"/>\source\public\interfaces\tables"
/I "<xsl:value-of select="$sdkdir"/>\source\public\interfaces\text"
/I "<xsl:value-of select="$sdkdir"/>\source\public\interfaces\graphics"
/I "<xsl:value-of select="$sdkdir"/>\source\public\libs\widgetbin\includes"
/I "<xsl:value-of select="$sdkdir"/>\source\public\interfaces\workgroup"
/I "<xsl:value-of select="$sdkdir"/>\source\public\interfaces\interactive"
/I "<xsl:value-of select="$sdkdir"/>\source\public\interfaces\interactive\ui"
/I "<xsl:value-of select="$sdkdir"/>\source\public\interfaces\colormgmt"
/I "<xsl:value-of select="$sdkdir"/>\source\public\interfaces\utils"
/I "<xsl:value-of select="$sdkdir"/>\source\public\interfaces\incopy"
/I "<xsl:value-of select="$sdkdir"/>\source\public\interfaces\layout"
/I "<xsl:value-of select="$sdkdir"/>\source\public\interfaces\architecture"
/I "<xsl:value-of select="$sdkdir"/>\source\public\interfaces\cjk"
/I "<xsl:value-of select="$sdkdir"/>\source\public\interfaces\preflight"
/I "<xsl:value-of select="$sdkdir"/>\source\public\facades\graphics"
/I "<xsl:value-of select="$sdkdir"/>\source\public\facades\text"
/I "<xsl:value-of select="$sdkdir"/>\source\public\facades\layout"
/I "<xsl:value-of select="$sdkdir"/>\source\precomp\common"
/I "<xsl:value-of select="$sdkdir"/>\source\public\includes"
/I "<xsl:value-of select="$sdkdir"/>\source\public\libs\publiclib\plugins"
/I "<xsl:value-of select="$sdkdir"/>\source\public\libs\publiclib\files"
/I "<xsl:value-of select="$sdkdir"/>\source\public\libs\publiclib\objectmodel"
/I "<xsl:value-of select="$sdkdir"/>\source\sdksamples\common"
/I "<xsl:value-of select="$sdkdir"/>\external\afl\includes"
/I "<xsl:value-of select="$sdkdir"/>\external\dva\third_party\boost_libraries"
/I "<xsl:value-of select="$sdkdir"/>\external\dva\third_party\adobe_source_libraries"
/I "<xsl:value-of select="$sdkdir"/>\external\asl\intel_tbb_libraries\include"
/I "<xsl:value-of select="$sdkdir"/>\external\icu\include"

<xsl:if test="/code/@win-id-header-dir != /code/@win-source-dir">/I "<xsl:value-of select="/code/@win-id-header-dir"/>"</xsl:if>
</xsl:template>
</xsl:stylesheet>
