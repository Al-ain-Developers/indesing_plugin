<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
	<xsl:output method="xml" indent="yes"/>
	<xsl:template match="/package/designmap">
		<xsl:document href="{$workingdir}{$filesep}designmap.xml" method="xml" indent="yes">
			
<xsl:processing-instruction name="aid">style="50" type="document" readerVersion="6.0" featureSet="257" product="6.0(285)"</xsl:processing-instruction>
<Document xmlns:idPkg="http://ns.adobe.com/AdobeInDesign/idml/1.0/packaging" DOMVersion="6.0" Self="d">
	<Language Self="Language/$ID/[No Language]" Name="$ID/[No Language]" SingleQuotes="&apos;&apos;" DoubleQuotes="&quot;&quot;" PrimaryLanguageName="$ID/[No Language]" SublanguageName="$ID/[No Language]" Id="0" HyphenationVendor="$ID/" SpellingVendor="$ID/"/>
	<idPkg:Graphic src="Resources/Graphic.xml"/>
	<idPkg:Fonts src="Resources/Fonts.xml"/>
	<idPkg:Styles src="Resources/Styles.xml"/>
	<Layer Self="ub3" Name="Layer 1" Visible="true" Locked="false" IgnoreWrap="false" ShowGuides="true" LockGuides="false" UI="true" Expendable="true" Printable="true">
		<Properties>
			<LayerColor type="enumeration">LightBlue</LayerColor>
		</Properties>
	</Layer>
	<idPkg:MasterSpread src="MasterSpreads/MasterSpread_A.xml"/>
	
	<xsl:for-each select="/package/pagebuilder/spread">
		<idPkg:Spread src="Spreads/Spread_{@id}.xml"/>
	</xsl:for-each>
	<xsl:for-each select="/package/pagebuilder/story">
		<idPkg:Story src="Stories/Story_{@id}.xml"/>
	</xsl:for-each>
	
</Document>
</xsl:document>	
</xsl:template>
</xsl:stylesheet>
