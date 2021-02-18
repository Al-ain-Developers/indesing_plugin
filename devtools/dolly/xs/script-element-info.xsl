<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
	<xsl:import href="global-variables.xsl"/>
<xsl:output method="text"/>
	<xsl:template match="script-element-info" name="script-element-info"><xsl:param name="suppress-normal-include"/>/*

/*  Scripting definition
	In InDesign/InCopy, scripting resources are defined via ODFRez statements for cross-platform compatibility.
*/
resource VersionedScriptElementInfo(2)
{
	// Contexts
	{
        kFiredrakeScriptVersion, kCoreScriptManagerBoss, kInDesignAllLanguagesFS, k_Wild,
		kFiredrakeScriptVersion, kCoreScriptManagerBoss, kInCopyAllLanguagesFS, k_Wild,
		<xsl:if test="contains(string(/code/@product-type),'InDesignServerProduct')">kFiredrakeScriptVersion, kCoreScriptManagerBoss, kInDesignServerAllLanguagesFS, k_Wild,</xsl:if>
	}
	
	// Elements
	{
		// Specifies an Method
		Method
		{
			k<xsl:value-of select="/code/@short-name"/>MethodScriptElement,
			e_Speak,
			"speak",
			"Displays what you say in dialog",
			VoidType,
			{
				p_Said, "said", "Holds a string", StringType, kRequired,
			}
		}

		// Specifies a property
		Property
		{
			k<xsl:value-of select="/code/@short-name"/>PropertyScriptElement,
			p_Response,
			"response",
			"Describes user response to dialog",
			StringType,
			{}
			kNoAttributeClass,
		}
		
		// Connects this plug-in's methods and properties to scripting.
		Provider
		{
			k<xsl:value-of select="/code/@short-name"/>ScriptProviderBoss,	// provider boss ID
			{
				Object{ kApplicationObjectScriptElement },
				Method{ k<xsl:value-of select="/code/@short-name"/>MethodScriptElement },
				Property{ k<xsl:value-of select="/code/@short-name"/>PropertyScriptElement, kReadOnly },
			}
		}
	}
};

	</xsl:template>
</xsl:stylesheet>