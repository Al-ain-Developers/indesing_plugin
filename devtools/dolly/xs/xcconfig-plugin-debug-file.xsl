<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">

<xsl:import href="global-variables.xsl"/>

<xsl:output method="xml" indent="yes"/>



<xsl:template match="xcconfig-plugin-debug-file">

<xsl:if test="not(string(/code/@mac-specific-debug-xcconfig-file))">Generating Plugin_debug.xcconfig from template...

<xsl:document href="{/code/@mac-project-dir}{$filesep}{/code/@long-name}Plugin_debug.xcconfig" method="text" indent="yes">

<xsl:call-template name="xcconfig-plugin-debug"/>

</xsl:document>

</xsl:if>

</xsl:template>



<xsl:template match="xcconfig-plugin-debug" name="xcconfig-plugin-debug"><xsl:variable name="sdkdir" select="/code/@mac-sdk-dir"/>
ID_BUILD_CONFIG_PLUGIN_DEBUG = YES

// InDesign core library build settings (based on common build settings)
#include "<xsl:value-of select="$sdkdir"/>/build/mac/prj/_shared_build_settings/common_debug.xcconfig"

FRAMEWORK_SEARCH_PATHS = $(ID_SDK_ROOT)/build/mac/debug_cocoa64/packagefolder/contents/macos $(ID_SDK_ROOT)/build/mac/debug_cocoa64/packagefolder/contents/Frameworks

LIBRARY_SEARCH_PATHS = $(ID_SDK_ROOT)/build/mac/debug_cocoa64/packagefolder/contents/macos/libs
</xsl:template>

</xsl:stylesheet>




