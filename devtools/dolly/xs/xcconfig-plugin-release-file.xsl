<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">

<xsl:import href="global-variables.xsl"/>



<xsl:template match="xcconfig-plugin-release-file">

<xsl:if test="not(string(/code/@mac-specific-release-xcconfig-file))">Generating Plugin_release.xcconfig from template...

<xsl:document href="{/code/@mac-project-dir}{$filesep}{/code/@long-name}Plugin_release.xcconfig" method="text" indent="yes">

<xsl:call-template name="xcconfig-plugin-release"/>

</xsl:document>

</xsl:if>

</xsl:template>



<xsl:template match="xcconfig-plugin-release" name="xcconfig-plugin-release"><xsl:variable name="sdkdir" select="/code/@mac-sdk-dir"/>
ID_BUILD_CONFIG_PLUGIN_RELEASE = YES

// InDesign core library build settings (based on common build settings)
#include "<xsl:value-of select="$sdkdir"/>/build/mac/prj/_shared_build_settings/common_release.xcconfig"

FRAMEWORK_SEARCH_PATHS = $(ID_SDK_ROOT)/build/mac/release_cocoa64/packagefolder/contents/macos $(ID_SDK_ROOT)/build/mac/release_cocoa64/packagefolder/contents/Frameworks

LIBRARY_SEARCH_PATHS = $(ID_SDK_ROOT)/build/mac/release_cocoa64/packagefolder/contents/macos/libs
</xsl:template>

</xsl:stylesheet>
