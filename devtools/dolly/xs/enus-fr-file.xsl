<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
	<xsl:import href="global-variables.xsl"/>
        <xsl:import href="standard-adobe-header.xsl"/>
<xsl:import href="standard-footer.xsl"/>

<xsl:output name="cppfile" method="text"/>
<xsl:template match="enus-fr-file">
Generating enUS.fr file from template...
 <xsl:document href="{/code/@source-dir-absolute}{$filesep}{/code/@short-name}_enUS.fr" format="cppfile">
<xsl:call-template name="standard-adobe-header">
<xsl:with-param name="suppress-normal-include" select="1"/>
</xsl:call-template>
 <xsl:call-template name="enus-fr"/>
  <xsl:call-template name="standard-footer"/>
  </xsl:document>
</xsl:template>

<xsl:template match="enus-fr" name="enus-fr">
#ifdef __ODFRC__

// English string table is defined here

resource StringTable (kSDKDefStringsResourceID + index_enUS)
{
        k_enUS,									// Locale Id
        kEuropeanWinToMacEncodingConverter,		// Character encoding converter (irp) I made this WinToMac as we have a bias to generate on Win...
        {
        	 // ----- Menu strings
                k<xsl:value-of select="/code/@short-name"/>CompanyKey,					k<xsl:value-of select="/code/@short-name"/>CompanyValue,
                k<xsl:value-of select="/code/@short-name"/>AboutMenuKey,					k<xsl:value-of select="/code/@short-name"/>PluginName "[US]...",
                k<xsl:value-of select="/code/@short-name"/>PluginsMenuKey,				k<xsl:value-of select="/code/@short-name"/>PluginName "[US]",
<xsl:for-each select="/code/menu-item">                k<xsl:value-of select="/code/@short-name"/><xsl:value-of select="@name"/>MenuItemKey,	"<xsl:value-of select="@name"/>[US]",
</xsl:for-each>
<xsl:if test="/code/generate-dialog">				k<xsl:value-of select="/code/@short-name"/>DialogMenuItemKey,			"Show dialog[US]",
</xsl:if>	
                kSDKDefAboutThisPlugInMenuKey,			kSDKDefAboutThisPlugInMenuValue_enUS,

                // ----- Command strings

                // ----- Window strings

                // ----- Panel/dialog strings
<xsl:if test="/code/generate-panel">                k<xsl:value-of select="/code/@short-name"/>PanelTitleKey,				k<xsl:value-of select="/code/@short-name"/>PluginName "[US]",
                k<xsl:value-of select="/code/@short-name"/>StaticTextKey,				k<xsl:value-of select="/code/@short-name"/>PluginName "[US]",
</xsl:if>
<xsl:if test="/code/generate-dialog">				k<xsl:value-of select="/code/@short-name"/>DialogTitleKey,     k<xsl:value-of select="/code/@short-name"/>PluginName "[US]",
</xsl:if>

<xsl:if test="/code/generate-preflight">
				// ----- Rule description strings
				k<xsl:value-of select="/code/@short-name"/>CategoryKey,				"<xsl:value-of select="/code/@long-name"/> Rule Category [US]",
				k<xsl:value-of select="/code/@short-name"/>RuleDescriptionKey,		"<xsl:value-of select="/code/@long-name"/> Rule Description [US]",
				k<xsl:value-of select="/code/@short-name"/>RuleParameterLabel,		"<xsl:value-of select="/code/@long-name"/> Rule Parameter [US]",
</xsl:if>

		// ----- Misc strings
                k<xsl:value-of select="/code/@short-name"/>AboutBoxStringKey,			k<xsl:value-of select="/code/@short-name"/>PluginName " [US], version " k<xsl:value-of select="/code/@short-name"/>Version " by " k<xsl:value-of select="/code/@short-name"/>Author "\n\n" kSDKDefCopyrightStandardValue "\n\n" kSDKDefPartnersStandardValue_enUS,

		<xsl:for-each select="/code/string-item">		
		"<xsl:value-of select="@string-key"/>", "<xsl:value-of select="@string-default-translation"/>", </xsl:for-each>
        }

};

#endif // __ODFRC__
</xsl:template>
</xsl:stylesheet>
