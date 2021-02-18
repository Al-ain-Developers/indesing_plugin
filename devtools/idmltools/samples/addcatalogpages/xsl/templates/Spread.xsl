<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
	
	<xsl:variable name="pageYTranslation" select="$page-height div -2"/>
    <xsl:output method="xml" indent="yes"/>
    <xsl:template match="/Data">
        <xsl:document href="{$working-dir}{$filesep}Spreads{$filesep}Spread_{$spread-id}.xml"
            method="xml" indent="yes">
            <idPkg:Spread xmlns:idPkg="http://ns.adobe.com/AdobeInDesign/idml/1.0/packaging"
                DOMVersion="7.5">
                <Spread Self="{$spread-id}" PageTransitionType="None"
                    PageTransitionDirection="NotApplicable" PageTransitionDuration="Medium"
                    FlattenerOverride="Default" ShowMasterItems="true" PageCount="2"
                    BindingLocation="1" AllowPageShuffle="true">
                    <Page Self="{$spread-id}_Page_1" AppliedTrapPreset="TrapPreset/$ID/kDefaultTrapStyleName" AppliedMaster="{$masterpage-id}" OverrideList="" TabOrder="" GridStartingPoint="TopOutside" UseMasterGrid="true">
                        <Properties>
                            <Descriptor type="list">
                                <ListItem type="string"></ListItem>
                                <ListItem type="enumeration">Arabic</ListItem>
                                <ListItem type="boolean">true</ListItem>
                                <ListItem type="boolean">false</ListItem>
                                <ListItem type="long">2</ListItem>
                                <ListItem type="string"></ListItem>
                            </Descriptor>
                        </Properties>
                        <MarginPreference ColumnCount="1" ColumnGutter="15" Top="59.99976" Bottom="48.002399999999994" Left="18" Right="54" ColumnDirection="Horizontal" ColumnsPositions="0 576"/>
                        <GridDataInformation FontStyle="Regular" PointSize="12" CharacterAki="0" LineAki="9" HorizontalScale="100" VerticalScale="100" LineAlignment="LeftOrTopLineJustify" GridAlignment="AlignEmCenter" CharacterAlignment="AlignEmCenter">
                            <Properties>
                                <AppliedFont type="string">Times</AppliedFont>
                            </Properties>
                        </GridDataInformation>
                    </Page>
                    <Page Self="{$spread-id}_Page_2" AppliedTrapPreset="TrapPreset/$ID/kDefaultTrapStyleName" AppliedMaster="{$masterpage-id}" OverrideList="" TabOrder="" GridStartingPoint="TopOutside" UseMasterGrid="true">
                        <Properties>
                            <Descriptor type="list">
                                <ListItem type="string"></ListItem>
                                <ListItem type="enumeration">Arabic</ListItem>
                                <ListItem type="boolean">true</ListItem>
                                <ListItem type="boolean">false</ListItem>
                                <ListItem type="long">2</ListItem>
                                <ListItem type="string"></ListItem>
                            </Descriptor>
                        </Properties>
                        <MarginPreference ColumnCount="1" ColumnGutter="15" Top="59.99976" Bottom="48.002399999999994" Left="18" Right="54" ColumnDirection="Horizontal" ColumnsPositions="0 576"/>
                        <GridDataInformation FontStyle="Regular" PointSize="12" CharacterAki="0" LineAki="9" HorizontalScale="100" VerticalScale="100" LineAlignment="LeftOrTopLineJustify" GridAlignment="AlignEmCenter" CharacterAlignment="AlignEmCenter">
                            <Properties>
                                <AppliedFont type="string">Times</AppliedFont>
                            </Properties>
                        </GridDataInformation>
                    </Page>


                    <!--    Text Frames    -->
                    <xsl:for-each select="Category">
                        
                        <xsl:variable name="categoryID"><xsl:value-of select="@id"/></xsl:variable>
                        <xsl:variable name="categoryNumber" select="position()"></xsl:variable>
                        <xsl:variable name="adjustedLeft"><xsl:choose><xsl:when test="$categoryNumber > 1">17.5</xsl:when><xsl:otherwise>54</xsl:otherwise></xsl:choose></xsl:variable>
                        <xsl:call-template name="generate-category-textframe">
                            <xsl:with-param name="storyID">Category_<xsl:value-of select="@id"/>_Story</xsl:with-param>
                            <xsl:with-param name="textFrameID">Category_<xsl:value-of select="@id"/>_TextFrame</xsl:with-param>
                            <xsl:with-param name="pageNum">
                                <xsl:value-of select="position() -1"/>
                            </xsl:with-param>
                           	<xsl:with-param name="pageBinding">1</xsl:with-param>
                            <xsl:with-param name="left"><xsl:value-of select="$adjustedLeft"/></xsl:with-param>
                            <xsl:with-param name="top">60</xsl:with-param>
                            <xsl:with-param name="right"><xsl:value-of select="$adjustedLeft + 576"/></xsl:with-param>
                            <xsl:with-param name="bottom">98</xsl:with-param>
                        </xsl:call-template>
                        
                        <xsl:for-each select="Item">
                            
                            <xsl:variable name="zeroBasedPosition" select="position() - 1"/>
                            
                            <xsl:call-template name="generate-item">
                                <xsl:with-param name="id"><xsl:value-of select="@id"/></xsl:with-param>
                                <xsl:with-param name="pageNum">
                                    <xsl:value-of select="$categoryID - 1"/>
                                </xsl:with-param>
                                <xsl:with-param name="left"><xsl:value-of select="($zeroBasedPosition - (floor($zeroBasedPosition div 2) ) *2 ) * 295.5 + $adjustedLeft - 0.5"/></xsl:with-param>
                                <xsl:with-param name="top"><xsl:value-of select="(floor($zeroBasedPosition div 2) )* 159 + 112.5"/></xsl:with-param>
                                <xsl:with-param name="pageBinding">1</xsl:with-param>
                                <xsl:with-param name="imageName"><xsl:value-of select="Image/text()"/></xsl:with-param>
                                
                            </xsl:call-template>
                        </xsl:for-each>
                    </xsl:for-each>
                  


                    
                
                
               
                </Spread>
            </idPkg:Spread>
        </xsl:document>
        <xsl:apply-templates/>
    </xsl:template>


    <xsl:template name="generate-item">
        <!--Parameters-->
        <xsl:param name="id"/>
        <xsl:param name="pageNum"/>
        <xsl:param name="pageBinding"/>
        <xsl:param name="left"/>
        <xsl:param name="top"/>
        <xsl:param name="imageName"/>
        <!-- This variable computes the necessary X Translation this page works to be working in page coordinates.  -->
        <xsl:variable name="pageXTranslation" select="($pageNum - $pageBinding) * $page-width "/>
        
        <!-- These variables create self IDs for various constructs based on the passed in ID. -->
        <xsl:variable name="rectID">Item_<xsl:value-of select="$id"/>_Rect</xsl:variable>
        <xsl:variable name="imageRectID">Item_<xsl:value-of select="$id"/>_ImageRect</xsl:variable>
        <xsl:variable name="imageID">Item_<xsl:value-of select="$id"/>_Image</xsl:variable>
        <xsl:variable name="linkID">Item_<xsl:value-of select="$id"/>_ImageLink</xsl:variable>
        <xsl:variable name="storyID">Item_<xsl:value-of select="$id"/>_Story</xsl:variable>
        <xsl:variable name="textFrameID">Item_<xsl:value-of select="$id"/>_TextFrame</xsl:variable>
        
        <!-- These variables compute the bounds of the various page items based on the passed in top/left. -->
        <xsl:variable name="rectLeft"><xsl:value-of select="$left"/></xsl:variable>
        <xsl:variable name="rectTop"><xsl:value-of select="$top"/></xsl:variable>
        <xsl:variable name="rectRight"><xsl:value-of select="$left + 281.5"/></xsl:variable>
        <xsl:variable name="rectBottom"><xsl:value-of select="$top + 145"/></xsl:variable>
        
        <xsl:variable name="imageRectLeft"><xsl:value-of select="$left"/></xsl:variable>
        <xsl:variable name="imageRectTop"><xsl:value-of select="$top"/></xsl:variable>
        <xsl:variable name="imageRectRight"><xsl:value-of select="$left + 141.25"/></xsl:variable>
        <xsl:variable name="imageRectBottom"><xsl:value-of select="$top + 145"/></xsl:variable>
        
        <xsl:variable name="textFrameLeft"><xsl:value-of select="$left + 140.75"/></xsl:variable>
        <xsl:variable name="textFrameTop"><xsl:value-of select="$top + .5"/></xsl:variable>
        <xsl:variable name="textFrameRight"><xsl:value-of select="$textFrameLeft + 140.25"/></xsl:variable>
        <xsl:variable name="textFrameBottom"><xsl:value-of select="$textFrameTop + 144"/></xsl:variable>
             
        <!--Containing Rectangle-->
        <xsl:call-template name="generate-item-rect">
            <xsl:with-param name="rectID"><xsl:value-of select="$rectID"/></xsl:with-param>
            <xsl:with-param name="pageNum"><xsl:value-of select="$pageNum"/></xsl:with-param>
            <xsl:with-param name="pageBinding"><xsl:value-of select="$pageBinding"/></xsl:with-param>
            <xsl:with-param name="left"><xsl:value-of select="$rectLeft"/></xsl:with-param>
            <xsl:with-param name="top"><xsl:value-of select="$rectTop"/></xsl:with-param>
            <xsl:with-param name="right"><xsl:value-of select="$rectRight"/></xsl:with-param>
            <xsl:with-param name="bottom"><xsl:value-of select="$rectBottom"/></xsl:with-param>
        </xsl:call-template>
        <!--Image-->
        <xsl:call-template name="generate-item-image">
            <xsl:with-param name="rectID"><xsl:value-of select="$imageRectID"/></xsl:with-param>
            <xsl:with-param name="imageID"><xsl:value-of select="$imageID"/></xsl:with-param>
            <xsl:with-param name="linkID"><xsl:value-of select="$linkID"/></xsl:with-param>
            <xsl:with-param name="pageNum"><xsl:value-of select="$pageNum"/></xsl:with-param>
            <xsl:with-param name="pageBinding"><xsl:value-of select="$pageBinding"/></xsl:with-param>
            <xsl:with-param name="left"><xsl:value-of select="$imageRectLeft"/></xsl:with-param>
            <xsl:with-param name="top"><xsl:value-of select="$imageRectTop"/></xsl:with-param>
            <xsl:with-param name="right"><xsl:value-of select="$imageRectRight"/></xsl:with-param>
            <xsl:with-param name="bottom"><xsl:value-of select="$imageRectBottom"/></xsl:with-param>
        </xsl:call-template>
        <!--Item Text Frame-->
        <xsl:call-template name="generate-item-textframe">
            <xsl:with-param name="storyID"><xsl:value-of select="$storyID"/></xsl:with-param>
            <xsl:with-param name="textFrameID"><xsl:value-of select="$textFrameID"/></xsl:with-param>
            <xsl:with-param name="pageNum"><xsl:value-of select="$pageNum"/></xsl:with-param>
            <xsl:with-param name="pageBinding"><xsl:value-of select="$pageBinding"/></xsl:with-param>
            <xsl:with-param name="left"><xsl:value-of select="$textFrameLeft"/></xsl:with-param>
            <xsl:with-param name="top"><xsl:value-of select="$textFrameTop"/></xsl:with-param>
            <xsl:with-param name="right"><xsl:value-of select="$textFrameRight"/></xsl:with-param>
            <xsl:with-param name="bottom"><xsl:value-of select="$textFrameBottom"/></xsl:with-param>
        </xsl:call-template>
        
    </xsl:template>
    
    
    

   <xsl:template name="generate-item-rect">
        <xsl:param name="rectID"></xsl:param>
        <xsl:param name="pageNum"/>
        <xsl:param name="pageBinding">1</xsl:param>
        <xsl:param name="left" select="@left"/>
        <xsl:param name="top" select="@top"/>
        <xsl:param name="right" select="@right"/>
        <xsl:param name="bottom" select="@bottom"/>
        <xsl:variable name="pageXTranslation" select="($pageNum - $pageBinding) * $page-width "/>
       <Rectangle StoryTitle="$ID/" ContentType="Unassigned" StrokeWeight="1"
           MiterLimit="4" EndCap="ButtEndCap" EndJoin="MiterEndJoin"
           StrokeType="StrokeStyle/$ID/Solid" LeftLineEnd="None" RightLineEnd="None"
           StrokeColor="Color/Black" StrokeTint="-1" CornerRadius="12"
           GradientFillStart="0 0" GradientFillLength="0" GradientFillAngle="0"
           GradientStrokeStart="0 0" GradientStrokeLength="0" GradientStrokeAngle="0"
           OverprintStroke="false" GapColor="Swatch/None" GapTint="-1"
           StrokeAlignment="CenterAlignment" ItemLayer="{$text-layer-id}" Locked="false"
           LocalDisplaySetting="Default" GradientFillHiliteLength="0"
           GradientFillHiliteAngle="0" GradientStrokeHiliteLength="0"
           GradientStrokeHiliteAngle="0"
           AppliedObjectStyle="ObjectStyle/catalog%3abackground shadow" CornerOption="None"
           ItemTransform="1 0 0 1 {$pageXTranslation} {$pageYTranslation}">
           <xsl:attribute name="Self">
               <xsl:value-of select="$rectID"/>
           </xsl:attribute>
           <Properties>
               <PathGeometry>
                   <GeometryPathType PathOpen="false">
                       <PathPointArray>
                           <PathPointType Anchor="{$left} {$top}" LeftDirection="{$left} {$top}"
                               RightDirection="{$left} {$top}"/>
                           <PathPointType Anchor="{$left} {$bottom}" LeftDirection="{$left} {$bottom}"
                               RightDirection="{$left} {$bottom}"/>
                           <PathPointType Anchor="{$right} {$bottom}"
                               LeftDirection="{$right} {$bottom}"
                               RightDirection="{$right} {$bottom}"/>
                           <PathPointType Anchor="{$right} {$top}" LeftDirection="{$right} {$top}"
                               RightDirection="{$right} {$top}"/>
                       </PathPointArray>
                   </GeometryPathType>
               </PathGeometry>
           </Properties>
           <TextWrapPreference TextWrapMode="None" Inverse="false"
               ApplyToMasterPageOnly="false" TextWrapSide="BothSides">
               <Properties>
                   <TextWrapOffset Top="0" Left="0" Bottom="0" Right="0"/>
               </Properties>
           </TextWrapPreference>
           <InCopyExportOption IncludeGraphicProxies="true" IncludeAllResources="false"/>
       </Rectangle>
    </xsl:template>

    <xsl:template name="generate-item-image">
        <xsl:param name="rectID"></xsl:param>
        <xsl:param name="imageID"></xsl:param>
        <xsl:param name="linkID"></xsl:param>
        <xsl:param name="pageNum"/>
        <xsl:param name="pageBinding">1</xsl:param>
        <xsl:param name="left" select="@left"/>
        <xsl:param name="top" select="@top"/>
        <xsl:param name="right" select="@right"/>
        <xsl:param name="bottom" select="@bottom"/>
        <xsl:variable name="imageName" select="Image"></xsl:variable>
        <xsl:variable name="pageXTranslation" select="($pageNum - $pageBinding) * $page-width "/>
        <Rectangle StoryTitle="$ID/" ContentType="GraphicType"
            FillColor="Swatch/None" FillTint="-1" StrokeWeight="1" MiterLimit="4"
            EndCap="ButtEndCap" EndJoin="MiterEndJoin" StrokeType="StrokeStyle/$ID/Solid"
            LeftLineEnd="None" RightLineEnd="None" StrokeColor="Color/Black" StrokeTint="-1"
            CornerRadius="12" GradientFillStart="0 0" GradientFillLength="0"
            GradientFillAngle="0" GradientStrokeStart="0 0" GradientStrokeLength="0"
            GradientStrokeAngle="0" OverprintStroke="false" GapColor="Swatch/None"
            GapTint="-1" StrokeAlignment="CenterAlignment" ItemLayer="{$text-layer-id}" Locked="false"
            LocalDisplaySetting="Default" GradientFillHiliteLength="0"
            GradientFillHiliteAngle="0" GradientStrokeHiliteLength="0"
            GradientStrokeHiliteAngle="0"
            AppliedObjectStyle="ObjectStyle/catalog%3at_shirt_drop_shadow"
            CornerOption="None" ItemTransform="1 0 0 1 {$pageXTranslation} {$pageYTranslation}">
            <xsl:attribute name="Self">
                <xsl:value-of select="$rectID"/>
            </xsl:attribute>
            <Properties>
                <PathGeometry>
                    <GeometryPathType PathOpen="false">
                        <PathPointArray>
                            <PathPointType Anchor="{$left} {$top}" LeftDirection="{$left} {$top}"
                                RightDirection="{$left} {$top}"/>
                            <PathPointType Anchor="{$left} {$bottom}" LeftDirection="{$left} {$bottom}"
                                RightDirection="{$left} {$bottom}"/>
                            <PathPointType Anchor="{$right} {$bottom}"
                                LeftDirection="{$right} {$bottom}"
                                RightDirection="{$right} {$bottom}"/>
                            <PathPointType Anchor="{$right} {$top}" LeftDirection="{$right} {$top}"
                                RightDirection="{$right} {$top}"/>
                        </PathPointArray>
                    </GeometryPathType>
                </PathGeometry>
            </Properties>
            <TextWrapPreference TextWrapMode="None" Inverse="false"
                ApplyToMasterPageOnly="false" TextWrapSide="BothSides">
                <Properties>
                    <TextWrapOffset Top="0" Left="0" Bottom="0" Right="0"/>
                </Properties>
                <ContourOption ContourType="SameAsClipping" IncludeInsideEdges="false"
                    ContourPathName="$ID/"/>
            </TextWrapPreference>
            <InCopyExportOption IncludeGraphicProxies="true" IncludeAllResources="false"/>
            <Image Space="$ID/#Links_CMYK" ImageRenderingIntent="UseColorSettings"
                LocalDisplaySetting="Default" ImageTypeName="$ID/Photoshop"
                AppliedObjectStyle="ObjectStyle/$ID/[None]"
                ItemTransform="1 0 0 1 0 0">
                <xsl:attribute name="Self">
                    <xsl:value-of select="$imageID"/>
                </xsl:attribute>
                <Properties>
                    <Profile type="string">$ID/Use Document Default</Profile>
                    
                    <GraphicBounds Left="{$left}" Top="{$top}" Right="{$right}" Bottom="{$bottom}"/>
                </Properties>
                <TextWrapPreference TextWrapMode="None" Inverse="false"
                    ApplyToMasterPageOnly="false" TextWrapSide="BothSides">
                    <Properties>
                        <TextWrapOffset Top="0" Left="0" Bottom="0" Right="0"/>
                    </Properties>
                    <ContourOption ContourType="SameAsClipping" IncludeInsideEdges="false"
                        ContourPathName="$ID/"/>
                </TextWrapPreference>
                
                <Link AssetURL="$ID/" AssetID="$ID/"
                    LinkResourceURI="file:Links/{$imageName}"
                    LinkResourceFormat="$ID/Photoshop" StoredState="Normal"
                    LinkClassID="35906" LinkClientID="257" LinkResourceModified="false"
                    LinkObjectModified="false" ShowInUI="true" CanEmbed="true"
                    CanUnembed="true" CanPackage="true" ImportPolicy="NoAutoImport"
                    ExportPolicy="NoAutoExport"
                    LinkImportStamp="file 128075876700000000 7403516"
                    LinkImportModificationTime="2006-11-09T16:14:30"
                    LinkImportTime="2008-06-16T13:28:53">
                    <xsl:attribute name="Self">
                        <xsl:value-of select="$linkID"/>
                    </xsl:attribute>
                </Link>
                <ImageIOPreference ApplyPhotoshopClippingPath="true"
                    AllowAutoEmbedding="true" AlphaChannelName="$ID/"/>
            </Image>
        </Rectangle>
    </xsl:template>

    <xsl:template name="generate-item-textframe">
        <xsl:param name="storyID"/>
        <xsl:param name="textFrameID"/>
        <xsl:param name="pageNum"/>
        <xsl:param name="pageBinding">1</xsl:param>
        <xsl:param name="left" select="@left"/>
        <xsl:param name="top" select="@top"/>
        <xsl:param name="right" select="@right"/>
        <xsl:param name="bottom" select="@bottom"/>
        <xsl:variable name="pageXTranslation" select="($pageNum - $pageBinding) * $page-width "/>
        <TextFrame ParentStory="{$storyID}" PreviousTextFrame="n" NextTextFrame="n"
            ContentType="TextType" GradientFillStart="189.25 252"
            GradientFillLength="140.25" GradientFillAngle="0"
            GradientStrokeStart="189.25 252" GradientStrokeLength="140.25"
            GradientStrokeAngle="0" ItemLayer="{$text-layer-id}" Locked="false"
            LocalDisplaySetting="Default" GradientFillHiliteLength="0"
            GradientFillHiliteAngle="0" GradientStrokeHiliteLength="0"
            GradientStrokeHiliteAngle="0" AppliedObjectStyle="ObjectStyle/catalog%3atext"
            ItemTransform="1 0 0 1 {$pageXTranslation} {$pageYTranslation}">
            <xsl:attribute name="Self">
                <xsl:value-of select="$textFrameID"/>
            </xsl:attribute>
            <Properties>
                <PathGeometry>
                    <GeometryPathType PathOpen="false">
                        <PathPointArray>
                            <PathPointType Anchor="{$left} {$top}" LeftDirection="{$left} {$top}"
                                RightDirection="{$left} {$top}"/>
                            <PathPointType Anchor="{$left} {$bottom}" LeftDirection="{$left} {$bottom}"
                                RightDirection="{$left} {$bottom}"/>
                            <PathPointType Anchor="{$right} {$bottom}"
                                LeftDirection="{$right} {$bottom}"
                                RightDirection="{$right} {$bottom}"/>
                            <PathPointType Anchor="{$right} {$top}" LeftDirection="{$right} {$top}"
                                RightDirection="{$right} {$top}"/>
                        </PathPointArray>
                    </GeometryPathType>
                </PathGeometry>
            </Properties>
        </TextFrame>
    </xsl:template>
    
    <xsl:template name="generate-category-textframe">
        <xsl:param name="storyID"/>
        <xsl:param name="textFrameID"></xsl:param>
        <xsl:param name="pageNum"/>
        <xsl:param name="pageBinding">1</xsl:param>
        <xsl:param name="left" select="@left"/>
        <xsl:param name="top" select="@top"/>
        <xsl:param name="right" select="@right"/>
        <xsl:param name="bottom" select="@bottom"/>
        <xsl:variable name="pageXTranslation" select="($pageNum - $pageBinding) * $page-width "/>
        <TextFrame ParentStory="{$storyID}" PreviousTextFrame="n" NextTextFrame="n"
            ContentType="TextType" StrokeWeight="0" MiterLimit="4" EndCap="ButtEndCap"
            EndJoin="MiterEndJoin" StrokeType="StrokeStyle/$ID/Solid" LeftLineEnd="None"
            RightLineEnd="None" StrokeColor="Swatch/None" StrokeTint="-1" CornerRadius="12"
            GradientFillStart="0 0" GradientFillLength="0" GradientFillAngle="0"
            GradientStrokeStart="0 0" GradientStrokeLength="0" GradientStrokeAngle="0"
            GapColor="Swatch/None" GapTint="-1" StrokeAlignment="CenterAlignment" ItemLayer="{$text-layer-id}"
            Locked="false" LocalDisplaySetting="Default" GradientFillHiliteLength="0"
            GradientFillHiliteAngle="0" GradientStrokeHiliteLength="0" GradientStrokeHiliteAngle="0"
            AppliedObjectStyle="ObjectStyle/catalog%3aheader" CornerOption="None"
            ItemTransform="1 0 0 1 {$pageXTranslation} {$pageYTranslation}">
            <xsl:attribute name="Self">
                <xsl:value-of select="textFrameID"/>
            </xsl:attribute>
            <Properties>
                <PathGeometry>
                    <GeometryPathType PathOpen="false">
                        <PathPointArray>
                            <PathPointType Anchor="{$left} {$top}" LeftDirection="{$left} {$top}"
                                RightDirection="{$left} {$top}"/>
                            <PathPointType Anchor="{$left} {$bottom}" LeftDirection="{$left} {$bottom}"
                                RightDirection="{$left} {$bottom}"/>
                            <PathPointType Anchor="{$right} {$bottom}"
                                LeftDirection="{$right} {$bottom}"
                                RightDirection="{$right} {$bottom}"/>
                            <PathPointType Anchor="{$right} {$top}" LeftDirection="{$right} {$top}"
                                RightDirection="{$right} {$top}"/>
                        </PathPointArray>
                    </GeometryPathType>
                </PathGeometry>
            </Properties>
        </TextFrame>
    </xsl:template>
    
   

</xsl:stylesheet>
