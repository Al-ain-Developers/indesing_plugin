<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
	<xsl:output method="xml" indent="yes"/>
	<xsl:template match="/package/backingstory">
		<xsl:document href="{$workingdir}{$filesep}XML{$filesep}BackingStory.xml" method="xml" indent="yes">		
<idPkg:BackingStory xmlns:idPkg="http://ns.adobe.com/AdobeInDesign/idml/1.0/packaging">
	<XmlStory Self="u9c" AppliedTOCStyle="n" TrackChanges="false" StoryTitle="$ID/" AppliedNamedGrid="n">
		<Properties>
			<ExcelImportPreferences type="list">
			</ExcelImportPreferences>
			<WordRTFImportPreferences type="list">
			</WordRTFImportPreferences>
			<TextImportPreferences type="list">
			</TextImportPreferences>
			<StyleMappingPreferences type="list">
				<ListItem type="list">
				</ListItem>
				<ListItem type="list">
				</ListItem>
			</StyleMappingPreferences>
		</Properties>
		<StoryPreference OpticalMarginAlignment="false" OpticalMarginSize="12" FrameType="TextFrameType" StoryOrientation="Horizontal" StoryDirection="LeftToRightDirection"/>
		<MetadataPacketPreference>
			<Properties>
				<Contents><![CDATA[]]></Contents>
			</Properties>
		</MetadataPacketPreference>
		<ParagraphStyleRange AppliedParagraphStyle="ParagraphStyle/$ID/NormalParagraphStyle">
			<CharacterStyleRange AppliedCharacterStyle="CharacterStyle/$ID/[No character style]">
				<Content>﻿</Content>
				<XMLElement Self="di2" MarkupTag="XMLTag/Root"/>
				<Content>﻿</Content>
			</CharacterStyleRange>
		</ParagraphStyleRange>
	</XmlStory>
</idPkg:BackingStory>
</xsl:document>
</xsl:template>
</xsl:stylesheet>