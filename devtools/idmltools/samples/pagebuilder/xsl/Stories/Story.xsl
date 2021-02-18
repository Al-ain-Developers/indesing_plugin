<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
	<xsl:output method="xml" indent="yes"/>
	<xsl:template match="/package/pagebuilder/story">
		<xsl:document href="{$workingdir}{$filesep}Stories{$filesep}Story_{@id}.xml" method="xml" indent="yes">			
<idPkg:Story xmlns:idPkg="http://ns.adobe.com/AdobeInDesign/idml/1.0/packaging" DOMVersion="7.5">
	<Story Self="{@id}">
		<ParagraphStyleRange AppliedParagraphStyle="ParagraphStyle/title">
			<CharacterStyleRange AppliedCharacterStyle="CharacterStyle/$ID/[No character style]">
				<Content><xsl:value-of select="title/text()"/></Content>
				<Br/>
			</CharacterStyleRange>
		</ParagraphStyleRange>
		<ParagraphStyleRange AppliedParagraphStyle="ParagraphStyle/body">
			<CharacterStyleRange AppliedCharacterStyle="CharacterStyle/$ID/[No character style]">
				<xsl:for-each select="body/p">
				<Content><xsl:value-of select="./text()"/></Content>
				<Br/>
				</xsl:for-each>
			</CharacterStyleRange>
		</ParagraphStyleRange>
	</Story>
</idPkg:Story>
</xsl:document>
</xsl:template>
</xsl:stylesheet>