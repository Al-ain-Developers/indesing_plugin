<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<xsl:stylesheet 
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1"
    xmlns:xhtml="http://www.w3.org/1999/xhtml">
   
   <xsl:param name="output"/>
    <xsl:param name="table-width">540</xsl:param>
    
    <xsl:variable name="filesep" select="system-property('file.separator')" />
    
    
    <xsl:template 
        match="*|@*|comment()|processing-instruction()|text()">
                <xsl:apply-templates
                select="*|@*|comment()|processing-instruction()|text()"/>
    </xsl:template>
    
    <xsl:template match="xhtml:body">
            <xsl:processing-instruction name="aid">style="50" type="snippet" readerVersion="6.0" featureSet="257" product="6.0(352)"</xsl:processing-instruction>
            <xsl:processing-instruction name="aid">SnippetType="InCopyInterchange"</xsl:processing-instruction>
            <Document DOMVersion="7.5" Self="d">
                <Color Self="Color/My Swatch 1" Model="Process" Space="CMYK" ColorValue="59 0 7.000000000000001 7.000000000000001" ColorOverride="Normal" AlternateSpace="NoAlternateColor" AlternateColorValue="" Name="My Swatch 1" ColorEditable="true" ColorRemovable="true" Visible="true" SwatchCreatorID="7937"/>
                <FontFamily Self="diec" Name="Adobe Garamond Pro">
                    <Font Self="diecFontnAdobe Garamond Pro Regular" FontFamily="Adobe Garamond Pro" Name="Adobe Garamond Pro Regular" PostScriptName="$ID/AGaramondPro-Regular" Status="Installed" FontStyleName="Regular" FontType="OpenTypeCFF" WritingScript="0" FullName="Adobe Garamond Pro" FullNameNative="Adobe Garamond Pro" FontStyleNameNative="Regular" PlatformName="$ID/" Version="OTF 1.007;PS 001.000;Core 1.0.30;makeotf.lib1.4.1030"/>
                    <Font Self="diecFontnAdobe Garamond Pro Italic" FontFamily="Adobe Garamond Pro" Name="Adobe Garamond Pro Italic" PostScriptName="$ID/AGaramondPro-Italic" Status="Installed" FontStyleName="Italic" FontType="OpenTypeCFF" WritingScript="0" FullName="Adobe Garamond Pro Italic" FullNameNative="Adobe Garamond Pro Italic" FontStyleNameNative="Italic" PlatformName="$ID/" Version="OTF 1.007;PS 001.000;Core 1.0.30;makeotf.lib1.4.1030"/>
                    <Font Self="diecFontnAdobe Garamond Pro Bold" FontFamily="Adobe Garamond Pro" Name="Adobe Garamond Pro Bold" PostScriptName="$ID/AGaramondPro-Bold" Status="Installed" FontStyleName="Bold" FontType="OpenTypeCFF" WritingScript="0" FullName="Adobe Garamond Pro Bold" FullNameNative="Adobe Garamond Pro Bold" FontStyleNameNative="Bold" PlatformName="$ID/" Version="OTF 1.007;PS 001.000;Core 1.0.30;makeotf.lib1.4.1030"/>
                    <Font Self="diecFontnAdobe Garamond Pro Bold Italic" FontFamily="Adobe Garamond Pro" Name="Adobe Garamond Pro Bold Italic" PostScriptName="$ID/AGaramondPro-BoldItalic" Status="Installed" FontStyleName="Bold Italic" FontType="OpenTypeCFF" WritingScript="0" FullName="Adobe Garamond Pro Bold Italic" FullNameNative="Adobe Garamond Pro Bold Italic" FontStyleNameNative="Bold Italic" PlatformName="$ID/" Version="OTF 1.007;PS 001.000;Core 1.0.30;makeotf.lib1.4.1030"/>
                </FontFamily>
                <RootParagraphStyleGroup Self="u6d">
                    <ParagraphStyle Self="ParagraphStyle/h1" Name="h1" Imported="false" NextStyle="ParagraphStyle/h1" KeyboardShortcut="0 0" FontStyle="Bold" PointSize="16" Justification="CenterAlign">
                        <Properties>
                            <BasedOn type="object">ParagraphStyle/Story Body</BasedOn>
                            <PreviewColor type="enumeration">Nothing</PreviewColor>
                        </Properties>
                    </ParagraphStyle>
                    <ParagraphStyle Self="ParagraphStyle/h2" Name="h2" Imported="false" NextStyle="ParagraphStyle/h2" KeyboardShortcut="0 0" PointSize="14">
                        <Properties>
                            <BasedOn type="object">ParagraphStyle/h1</BasedOn>
                            <PreviewColor type="enumeration">Nothing</PreviewColor>
                        </Properties>
                    </ParagraphStyle>
                    <ParagraphStyle Self="ParagraphStyle/h3" Name="h3" Imported="false" NextStyle="ParagraphStyle/h3" KeyboardShortcut="0 0" PointSize="12">
                        <Properties>
                            <BasedOn type="object">ParagraphStyle/h2</BasedOn>
                            <PreviewColor type="enumeration">Nothing</PreviewColor>
                        </Properties>
                    </ParagraphStyle>
                    <ParagraphStyle Self="ParagraphStyle/Story Body" Name="Story Body" Imported="false" NextStyle="ParagraphStyle/Story Body" KeyboardShortcut="0 0" PointSize="10">
                        <Properties>
                            <BasedOn type="string">$ID/[No paragraph style]</BasedOn>
                            <PreviewColor type="enumeration">Nothing</PreviewColor>
                            <AppliedFont type="string">Adobe Garamond Pro</AppliedFont>
                        </Properties>
                    </ParagraphStyle>
                </RootParagraphStyleGroup>
				
				<RootCellStyleGroup Self="u7b">
					<CellStyle Self="CellStyle/$ID/[None]" AppliedParagraphStyle="ParagraphStyle/$ID/[No paragraph style]" Name="$ID/[None]"/>
				</RootCellStyleGroup>
				<RootTableStyleGroup Self="u7d">
					<TableStyle Self="TableStyle/$ID/[Basic Table]" Name="$ID/[Basic Table]" KeyboardShortcut="0 0">
						<Properties>
							<BasedOn type="string">$ID/[No table style]</BasedOn>
						</Properties>
					</TableStyle>
				</RootTableStyleGroup>

                <Story Self="ud4" AppliedTOCStyle="n" TrackChanges="false" StoryTitle="MyStory" AppliedNamedGrid="n">
                    <StoryPreference OpticalMarginAlignment="false" OpticalMarginSize="12" FrameType="TextFrameType" StoryOrientation="Horizontal" StoryDirection="LeftToRightDirection"/>
                    <InCopyExportOption IncludeGraphicProxies="true" IncludeAllResources="false"/>
                    
                    <xsl:apply-templates/>
                 
                </Story>
            </Document>
    </xsl:template>
    
    
    <xsl:template match="xhtml:h1|xhtml:h2|xhtml:h3">
        <ParagraphStyleRange>
            <xsl:attribute name="AppliedParagraphStyle">ParagraphStyle/<xsl:value-of select="name()"/></xsl:attribute>
            <CharacterStyleRange AppliedCharacterStyle="CharacterStyle/$ID/[No character style]">
                <Content><xsl:value-of select="text()"/></Content>
                <Br/>
            </CharacterStyleRange>
        </ParagraphStyleRange>
    </xsl:template>
    
    <xsl:template match="xhtml:p">
        <ParagraphStyleRange AppliedParagraphStyle="ParagraphStyle/Story Body">
        <xsl:for-each select="*|text()">
            <xsl:choose>
                <xsl:when test="self::xhtml:em">
                    <CharacterStyleRange AppliedCharacterStyle="CharacterStyle/$ID/[No character style]" FontStyle="Italic">
                        <Content><xsl:value-of select="normalize-space(text())"/><xsl:if test="position() != last()"><xsl:text> </xsl:text></xsl:if></Content>
                    </CharacterStyleRange>
                </xsl:when>
                <xsl:when test="self::text()">
                    <CharacterStyleRange AppliedCharacterStyle="CharacterStyle/$ID/[No character style]">
                        <Content><xsl:value-of select="normalize-space(.)"/><xsl:if test="position() != last()"><xsl:text> </xsl:text></xsl:if></Content>
                    </CharacterStyleRange>
                </xsl:when>
                </xsl:choose>
        </xsl:for-each>
            <Br/>
        </ParagraphStyleRange>
    </xsl:template>
    
    <xsl:template match="xhtml:table">
        <ParagraphStyleRange AppliedParagraphStyle="ParagraphStyle/Story Body">
            <CharacterStyleRange AppliedCharacterStyle="CharacterStyle/$ID/[No character style]">
                <Br/>
                <Table Self="udt1" HeaderRowCount="1" FooterRowCount="1" AppliedTableStyle="TableStyle/$ID/[Basic Table]" TableDirection="LeftToRightDirection">
                    <xsl:attribute name="BodyRowCount"><xsl:value-of select="count(child::xhtml:tr)"/></xsl:attribute>
                    <xsl:attribute name="ColumnCount"><xsl:value-of select="count(child::xhtml:tr[1]/xhtml:td)"/></xsl:attribute>
                    <xsl:variable name="columnWidth" select="$table-width div count(xhtml:tr[1]/xhtml:td)"/>
                    <xsl:for-each select="xhtml:tr[1]/xhtml:td">
                        <Column Self="" Name="{position() - 1}" SingleColumnWidth="{$columnWidth}"/>
                    </xsl:for-each>
                    
                    <xsl:for-each select="xhtml:tr">
                        <xsl:variable name="rowNum" select="position() - 1"/>
                        <xsl:for-each select="xhtml:td">
                            <xsl:variable name="colNum" select="position() - 1"/>
                            <Cell Self="utd1c{$colNum}r{$rowNum}" Name="{$colNum}:{$rowNum}" RowSpan="1" ColumnSpan="1" AppliedCellStyle="CellStyle/$ID/[None]" AppliedCellStylePriority="0">
                                <ParagraphStyleRange AppliedParagraphStyle="ParagraphStyle/$ID/NormalParagraphStyle">
                                    <CharacterStyleRange AppliedCharacterStyle="CharacterStyle/$ID/[No character style]">
                                        <Content><xsl:value-of select="text()"/></Content>
                                    </CharacterStyleRange>
                                </ParagraphStyleRange>
                            </Cell>
                        </xsl:for-each>
                    </xsl:for-each>
                </Table>
            </CharacterStyleRange>
            </ParagraphStyleRange>
    </xsl:template>
    
            
     <xsl:template match="xhtml:tr"><xsl:if test="position() > 2"><Br/></xsl:if></xsl:template>
    <xsl:template match="xhtml:td"><xsl:if test="position() > 2"><Br/></xsl:if></xsl:template>
    
    <xsl:template match="xhtml:ol">
        <ParagraphStyleRange AppliedParagraphStyle="ParagraphStyle/Story Body" LeftIndent="18" FirstLineIndent="-18" BulletsAndNumberingListType="NumberedList">
            <CharacterStyleRange AppliedCharacterStyle="CharacterStyle/$ID/[No character style]">
                <xsl:for-each select="xhtml:li">
                    <Content><xsl:value-of select="text()"/></Content>
                    <Br/>
                </xsl:for-each>
            </CharacterStyleRange>
        </ParagraphStyleRange>
    </xsl:template>
    
    <xsl:template match="xhtml:ul">
        <ParagraphStyleRange AppliedParagraphStyle="ParagraphStyle/Story Body" LeftIndent="18" FirstLineIndent="-18" BulletsAndNumberingListType="BulletList">
        <CharacterStyleRange AppliedCharacterStyle="CharacterStyle/$ID/[No character style]">
            <xsl:for-each select="xhtml:li">
                <Content><xsl:value-of select="text()"/></Content>
                <Br/>
            </xsl:for-each>
        </CharacterStyleRange>
        </ParagraphStyleRange>
    </xsl:template>
    
</xsl:stylesheet>