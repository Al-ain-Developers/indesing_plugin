<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
	<xsl:import href="global-variables.xsl"/>
        <xsl:import href="standard-adobe-header-jajp.xsl"/>
<xsl:import href="standard-footer.xsl"/>

<xsl:output name="cppfile" method="text"/>
<xsl:template match="jajp-fr-file">
Generating jaJP.FR file from template.
 <xsl:document href="{/code/@source-dir-absolute}{$filesep}{$filesep}{/code/@short-name}_jaJP.fr" format="cppfile">
 <xsl:call-template name="standard-adobe-header-jajp">
<xsl:with-param name="suppress-normal-include" select="1"/>
</xsl:call-template> <xsl:call-template name="jajp-fr"/>
  <xsl:call-template name="standard-footer"/>
  </xsl:document>
</xsl:template>

<xsl:template match="jajp-fr" name="jajp-fr">
#ifdef __ODFRC__


// Japanese string table is defined here

resource StringTable (kSDKDefStringsResourceID + index_jaJP)
{
        k_jaJP,	// Locale Id
        0,		// Character encoding converter

        {
        	// ----- Menu strings
                k<xsl:value-of select="/code/@short-name"/>CompanyKey,					k<xsl:value-of select="/code/@short-name"/>CompanyValue,
                k<xsl:value-of select="/code/@short-name"/>AboutMenuKey,					k<xsl:value-of select="/code/@short-name"/>PluginName "[JP]...",
                k<xsl:value-of select="/code/@short-name"/>PluginsMenuKey,				k<xsl:value-of select="/code/@short-name"/>PluginName "[JP]",
<xsl:for-each select="/code/menu-item">                k<xsl:value-of select="/code/@short-name"/><xsl:value-of select="@name"/>MenuItemKey,	"<xsl:value-of select="@name"/>[JP]",
</xsl:for-each>
<xsl:if test="/code/generate-dialog">				k<xsl:value-of select="/code/@short-name"/>DialogMenuItemKey,			"Show dialog[JP]",
</xsl:if>
                kSDKDefAboutThisPlugInMenuKey,			kSDKDefAboutThisPlugInMenuValue_jaJP,

                // ----- Command strings

                // ----- Window strings

                // ----- Panel/dialog strings
<xsl:if test="/code/generate-panel">                k<xsl:value-of select="/code/@short-name"/>PanelTitleKey,				k<xsl:value-of select="/code/@short-name"/>PluginName "[JP]",
                k<xsl:value-of select="/code/@short-name"/>StaticTextKey,				k<xsl:value-of select="/code/@short-name"/>PluginName "[JP]",
</xsl:if>
 <xsl:if test="/code/generate-dialog">					k<xsl:value-of select="/code/@short-name"/>DialogTitleKey,     k<xsl:value-of select="/code/@short-name"/>PluginName "[JP]",
</xsl:if>
 
<xsl:if test="/code/generate-preflight">
				// ----- Rule description strings
				k<xsl:value-of select="/code/@short-name"/>CategoryKey,				"<xsl:value-of select="/code/@long-name"/> Rule Category [JP]",
				k<xsl:value-of select="/code/@short-name"/>RuleDescriptionKey,		"<xsl:value-of select="/code/@long-name"/> Rule Description [JP]",
				k<xsl:value-of select="/code/@short-name"/>RuleParameterLabel,		"<xsl:value-of select="/code/@long-name"/> Rule Parameter [JP]",
</xsl:if>
              // ----- Error strings

                // ----- Misc strings
                k<xsl:value-of select="/code/@short-name"/>AboutBoxStringKey,			k<xsl:value-of select="/code/@short-name"/>PluginName " [JP], version " k<xsl:value-of select="/code/@short-name"/>Version " by " k<xsl:value-of select="/code/@short-name"/>Author "\n\n" kSDKDefCopyrightStandardValue "\n\n" kSDKDefPartnersStandardValue_jaJP,
<xsl:for-each select="/code/menu-item">                k<xsl:value-of select="/code/@short-name"/><xsl:value-of select="@name"/>StringKey,	"<xsl:value-of select="/code/@long-name"/>::<xsl:value-of select="@name"/>[JP]",
</xsl:for-each>

		<xsl:for-each select="/code/string-item">		
		"<xsl:value-of select="@string-key"/>", "<xsl:value-of select="@string-default-translation"/>", </xsl:for-each>
        }

};

#endif // __ODFRC__
</xsl:template>
</xsl:stylesheet>
