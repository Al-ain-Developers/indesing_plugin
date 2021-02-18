<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
	<xsl:output method="xml" indent="yes"/>
	<xsl:template match="/package/fonts">
		<xsl:document href="{$workingdir}{$filesep}Resources{$filesep}Fonts.xml" method="xml" indent="yes">
			<idPkg:Fonts xmlns:idPkg="http://ns.adobe.com/AdobeInDesign/idml/1.0/packaging" DOMVersion="7.5">
				<FontFamily Self="di3e" Name="Times New Roman">
					<Font Self="di3eFontnTimes New Roman Regular" FontFamily="Times New Roman" Name="Times New Roman Regular" PostScriptName="$ID/TimesNewRomanPSMT" Status="Installed" FontStyleName="Regular" FontType="OpenTypeTT" WritingScript="0" FullName="Times New Roman" FullNameNative="Times New Roman" FontStyleNameNative="Regular" PlatformName="$ID/" Version="Version 3.00"/>
					<Font Self="di3eFontnTimes New Roman Italic" FontFamily="Times New Roman" Name="Times New Roman Italic" PostScriptName="$ID/TimesNewRomanPS-ItalicMT" Status="Installed" FontStyleName="Italic" FontType="OpenTypeTT" WritingScript="0" FullName="Times New Roman Italic" FullNameNative="Times New Roman Italic" FontStyleNameNative="Italic" PlatformName="$ID/" Version="Version 2.90"/>
					<Font Self="di3eFontnTimes New Roman Bold" FontFamily="Times New Roman" Name="Times New Roman Bold" PostScriptName="$ID/TimesNewRomanPS-BoldMT" Status="Installed" FontStyleName="Bold" FontType="OpenTypeTT" WritingScript="0" FullName="Times New Roman Bold" FullNameNative="Times New Roman Bold" FontStyleNameNative="Bold" PlatformName="$ID/" Version="Version 3.00"/>
					<Font Self="di3eFontnTimes New Roman Bold Italic" FontFamily="Times New Roman" Name="Times New Roman Bold Italic" PostScriptName="$ID/TimesNewRomanPS-BoldItalicMT" Status="Installed" FontStyleName="Bold Italic" FontType="OpenTypeTT" WritingScript="0" FullName="Times New Roman Bold Italic" FullNameNative="Times New Roman Bold Italic" FontStyleNameNative="Bold Italic" PlatformName="$ID/" Version="Version 2.90"/>
				</FontFamily>
			</idPkg:Fonts>
		</xsl:document>
	</xsl:template>
</xsl:stylesheet>