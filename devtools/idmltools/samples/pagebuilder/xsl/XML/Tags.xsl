<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
	<xsl:output method="xml" indent="yes"/>
	<xsl:template match="/package/tags">
		<xsl:document href="{$workingdir}{$filesep}XML{$filesep}Tags.xml" method="xml" indent="yes">		
<idPkg:Tags xmlns:idPkg="http://ns.adobe.com/AdobeInDesign/idml/1.0/packaging">
	<XMLTag Self="XMLTag/Root" Name="Root">
		<Properties>
			<TagColor type="enumeration">LightBlue</TagColor>
		</Properties>
	</XMLTag>
</idPkg:Tags>
</xsl:document>	
</xsl:template>
</xsl:stylesheet>