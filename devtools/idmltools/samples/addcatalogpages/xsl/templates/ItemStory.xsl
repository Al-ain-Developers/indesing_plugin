<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
	
    <xsl:output method="xml" indent="yes"/>
    <xsl:template match="/Data/Category/Item">
        <xsl:document href="{$working-dir}{$filesep}Stories{$filesep}Story_Item{@id}.xml" method="xml" indent="yes">
            <idPkg:Story xmlns:idPkg="http://ns.adobe.com/AdobeInDesign/idml/1.0/packaging" DOMVersion="7.5">
                <Story Self="Item_{@id}_Story">
						<StoryPreference StoryOrientation="Horizontal" StoryDirection="LeftToRightDirection"/>
                        <ParagraphStyleRange AppliedParagraphStyle="ParagraphStyle/catalog%3aitem_name">
                            <CharacterStyleRange AppliedCharacterStyle="CharacterStyle/$ID/[No character style]">
                                    <Content><xsl:value-of select="Name"/></Content>
                                <Br/>
                            </CharacterStyleRange>
                        </ParagraphStyleRange>
                        <ParagraphStyleRange AppliedParagraphStyle="ParagraphStyle/catalog%3aitem_number">
                            <CharacterStyleRange AppliedCharacterStyle="CharacterStyle/$ID/[No character style]">
                                <Content><xsl:value-of select="Number"/></Content>
                                <Br/>
                            </CharacterStyleRange>
                        </ParagraphStyleRange>
                        <ParagraphStyleRange AppliedParagraphStyle="ParagraphStyle/catalog%3aitem_description">
                            <CharacterStyleRange AppliedCharacterStyle="CharacterStyle/$ID/[No character style]">
                                <Content><xsl:value-of select="Description"/></Content>
                                <Br/>
                            </CharacterStyleRange>
                        </ParagraphStyleRange>
                        <ParagraphStyleRange AppliedParagraphStyle="ParagraphStyle/catalog%3aitem_description_bullets">
                            <CharacterStyleRange AppliedCharacterStyle="CharacterStyle/$ID/[No character style]">
                                <xsl:for-each select="Detail"><Content><xsl:value-of select="text()"/></Content>
                                    <Br/>
                                </xsl:for-each>
                            </CharacterStyleRange>
                        </ParagraphStyleRange>
                        <ParagraphStyleRange AppliedParagraphStyle="ParagraphStyle/catalog%3aitem_price">
                            <CharacterStyleRange AppliedCharacterStyle="CharacterStyle/$ID/[No character style]">
                                    <Content><xsl:value-of select="Price"/></Content>
                                <Br/>
                                    <Content><xsl:value-of select="Size"/></Content>
                                <Br/>
                            </CharacterStyleRange>
                        </ParagraphStyleRange>
                </Story>
            </idPkg:Story>
        </xsl:document>
    </xsl:template>
</xsl:stylesheet>