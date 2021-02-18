<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
	
    <xsl:output method="xml" indent="yes"/>
    <xsl:template match="/Data/Category">
        <xsl:document href="{$working-dir}{$filesep}Stories{$filesep}Story_Category{@id}.xml" method="xml" indent="yes">			
            <idPkg:Story xmlns:idPkg="http://ns.adobe.com/AdobeInDesign/idml/1.0/packaging" DOMVersion="7.5">
                <Story Self="Category_{@id}_Story">
						<StoryPreference StoryOrientation="Horizontal" StoryDirection="LeftToRightDirection"/>
                        <ParagraphStyleRange AppliedParagraphStyle="ParagraphStyle/[No Paragraph Style]">
                            <CharacterStyleRange AppliedCharacterStyle="CharacterStyle/$ID/[No character style]">
                                <Content><xsl:value-of select="@name"/></Content>
                            </CharacterStyleRange>
                        </ParagraphStyleRange>
                </Story>
            </idPkg:Story>
        </xsl:document>
        <xsl:apply-templates/>
    </xsl:template>
</xsl:stylesheet>