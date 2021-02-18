<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
	<xsl:output method="xml" indent="yes"/>
	<xsl:template match="/package/pagebuilder/spread">
		<xsl:variable name="spreadNumber" select="count(preceding-sibling::spread)"></xsl:variable>
		<xsl:variable name="pageHeight" select="/package/pagebuilder/@pageHeight"/>
		<xsl:variable name="pageBorder" select="/package/pagebuilder/@pageBorder"/>
		<xsl:variable name="yTranslation" select="$spreadNumber * ($pageHeight + $pageBorder * 2 + 36)"/>
		<xsl:variable name="pageYTranslation" select="$pageHeight div -2"/>
		<xsl:variable name="pageBinding" select="@binding"></xsl:variable>
		<xsl:document href="{$workingdir}{$filesep}Spreads{$filesep}Spread_{@id}.xml" method="xml" indent="yes">		
<idPkg:Spread xmlns:idPkg="http://ns.adobe.com/AdobeInDesign/idml/1.0/packaging" DOMVersion="7.5">
	<Spread Self="{@id}" PageTransitionType="None" PageTransitionDirection="NotApplicable" PageTransitionDuration="Medium" FlattenerOverride="Default" ShowMasterItems="true" PageCount="1" BindingLocation="{@binding}" AllowPageShuffle="true" ItemTransform="1 0 0 1 0 {$yTranslation}">
	<xsl:variable name="spreadID"><xsl:value-of select="@id"/></xsl:variable>
	<xsl:for-each select="page">
		<Page Self="{$spreadID}_page_{position()}"  AppliedMaster="MasterSpread_A">
			<MarginPreference ColumnCount="1" ColumnGutter="12" Top="36" Bottom="36" Left="36" Right="36" ColumnDirection="Horizontal" ColumnsPositions="0 540"/>
			<GridDataInformation FontStyle="Regular" PointSize="12" CharacterAki="0" LineAki="9" HorizontalScale="100" VerticalScale="100" LineAlignment="LeftOrTopLineJustify" GridAlignment="AlignEmCenter" CharacterAlignment="AlignEmCenter">
				<Properties>
					<AppliedFont type="string">Times New Roman</AppliedFont>
				</Properties>
			</GridDataInformation>
		</Page>
	</xsl:for-each>
	
	<xsl:for-each select="page/text">
		<xsl:call-template name="generate-textframe">
			<xsl:with-param name="pageBinding" select="$pageBinding"/>
			<xsl:with-param name="pageYTranslation" select="$pageYTranslation"/>
		</xsl:call-template>
	</xsl:for-each>
	
	<xsl:for-each select="page/image">
		<xsl:call-template name="generate-image">
			<xsl:with-param name="pageBinding" select="$pageBinding"/>
			<xsl:with-param name="pageYTranslation" select="$pageYTranslation"/>
		</xsl:call-template>
	</xsl:for-each>
		
	</Spread>
	
</idPkg:Spread>
</xsl:document>
</xsl:template>

<xsl:template name="generate-image"> 
		<xsl:param name="pageBinding"/>
		<xsl:param name="pageYTranslation"/>
		<xsl:variable name="left" select="@left"/>
		<xsl:variable name="top" select="@top"/>
		<xsl:variable name="right" select="@right"/>
		<xsl:variable name="bottom" select="@bottom"/>
		<xsl:variable name="pageWidth" select="/package/pagebuilder/@pageWidth"></xsl:variable>
		<xsl:variable name="pageNum" select="count(../preceding-sibling::page)"/>
		
	<xsl:variable name="pageXTranslation" select="($pageNum - $pageBinding) * $pageWidth "></xsl:variable>
	<Rectangle AppliedObjectStyle="ObjectStyle/$ID/[None]" StoryTitle="$ID/" ContentType="GraphicType" GradientFillStart="0 0" GradientFillLength="0" GradientFillAngle="0" GradientStrokeStart="0 0" GradientStrokeLength="0" GradientStrokeAngle="0" ItemLayer="ub3" Locked="false" LocalDisplaySetting="Default" GradientFillHiliteLength="0" GradientFillHiliteAngle="0" GradientStrokeHiliteLength="0" GradientStrokeHiliteAngle="0"  ItemTransform="1 0 0 1 {$pageXTranslation} {$pageYTranslation}">
	<xsl:attribute name="Self">ImageRectangle_<xsl:value-of select="generate-id(.)"/></xsl:attribute>
		<Properties>
			<PathGeometry>
				<GeometryPath PathOpen="false">
						<PathPointArray>
							<PathPoint Anchor="{$left} {$top}" LeftDirection="{$left} {$top}" RightDirection="{$left} {$top}"/>
							<PathPoint Anchor="{$left} {$bottom}" LeftDirection="{$left} {$bottom}" RightDirection="{$left} {$bottom}"/>
							<PathPoint Anchor="{$right} {$bottom}" LeftDirection="{$right} {$bottom}" RightDirection="{$right} {$bottom}"/>
							<PathPoint Anchor="{$right} {$top}" LeftDirection="{$right} {$top}" RightDirection="{$right} {$top}"/>
						</PathPointArray>
					</GeometryPath>
			</PathGeometry>
		</Properties>
		<TextWrapPreference TextWrapMode="None" Inverse="false" ApplyToMasterPageOnly="false" TextWrapSide="BothSides">
			<Properties>
				<TextWrapOffset Top="0" Left="0" Bottom="0" Right="0"/>
			</Properties>
			<ContourOption ContourType="SameAsClipping" IncludeInsideEdges="false" ContourPathName="$ID/"/>
		</TextWrapPreference>
		<InCopyExportOption IncludeGraphicProxies="true"/>
		<Image AppliedObjectStyle="ObjectStyle/$ID/[None]" Space="$ID/#Links_RGB" ActualPpi="72 72" EffectivePpi="216 216" ImageRenderingIntent="UseColorSettings" LocalDisplaySetting="Default" ImageTypeName="JPEG" ItemTransform="1 0 0 1 0 0">
			<xsl:attribute name="Self">Image_<xsl:value-of select="generate-id(.)"/></xsl:attribute>
			<Properties>
				<GraphicBounds Left="{$left}" Top="{$top}" Right="{$right}" Bottom="{$bottom}"/>
				<Profile type="string">$ID/Embedded</Profile>
			</Properties>
			<Link AssetURL="$ID/" AssetID="$ID/" LinkResourceURI="{@src}" LinkResourceFormat="$ID/JPEG" StoredState="Normal" LinkClassID="35906" LinkClientID="257" LinkResourceModified="false" LinkObjectModified="false" ShowInUI="true" CanEmbed="true" CanUnembed="true" CanPackage="true" ImportPolicy="NoAutoImport" ExportPolicy="NoAutoExport">
			<xsl:attribute name="Self">ImageLink_<xsl:value-of select="generate-id(.)"/></xsl:attribute>
			</Link>
			<ClippingPathSettings ClippingType="None" InvertPath="false" IncludeInsideEdges="false" RestrictToFrame="false" UseHighResolutionImage="true" Threshold="25" Tolerance="2" InsetFrame="0" AppliedPathName="$ID/" Index="-1"/>
			<ImageIOPreference ApplyPhotoshopClippingPath="true" AllowAutoEmbedding="true" AlphaChannelName="$ID/"/>
		</Image>
	</Rectangle>
	</xsl:template>
	
<xsl:template name="generate-textframe"> 
	<xsl:param name="pageBinding"/>
	<xsl:param name="pageYTranslation"/>
	<xsl:variable name="left" select="@left"/>
	<xsl:variable name="top" select="@top"/>
	<xsl:variable name="right" select="@right"/>
	<xsl:variable name="bottom" select="@bottom"/>
	<xsl:variable name="pageWidth" select="/package/pagebuilder/@pageWidth"></xsl:variable>
	<xsl:variable name="pageNum" select="count(../preceding-sibling::page)"/>
	<xsl:variable name="pageXTranslation" select="($pageNum - $pageBinding) * $pageWidth "></xsl:variable>
	<TextFrame Self="{@id}" AppliedObjectStyle="ObjectStyle/$ID/[Normal Text Frame]" ParentStory="{@story}" ContentType="TextType" GradientFillStart="0 0" GradientFillLength="0" GradientFillAngle="0" GradientStrokeStart="0 0" GradientStrokeLength="0" GradientStrokeAngle="0" ItemLayer="ub3" Locked="false" LocalDisplaySetting="Default" GradientFillHiliteLength="0" GradientFillHiliteAngle="0" GradientStrokeHiliteLength="0" GradientStrokeHiliteAngle="0" ItemTransform="1 0 0 1 {$pageXTranslation} {$pageYTranslation}">
	<xsl:variable name="tfID" select="@id"></xsl:variable>
	<xsl:choose>
		<xsl:when test="//text[@next  = $tfID]"><xsl:attribute name="PreviousTextFrame"><xsl:value-of select="//text[@next  = $tfID]/@id"/></xsl:attribute></xsl:when>
		<xsl:otherwise><xsl:attribute name="PreviousTextFrame">n</xsl:attribute></xsl:otherwise>
	</xsl:choose>
	<xsl:choose>
		<xsl:when test="@next"><xsl:attribute name="NextTextFrame"><xsl:value-of select="@next"/></xsl:attribute></xsl:when>
		<xsl:otherwise><xsl:attribute name="NextTextFrame">n</xsl:attribute></xsl:otherwise>
	</xsl:choose>
		<Properties>
			<PathGeometry>
				<GeometryPath PathOpen="false">
						<PathPointArray>
							<PathPoint Anchor="{$left} {$top}" LeftDirection="{$left} {$top}" RightDirection="{$left} {$top}"/>
							<PathPoint Anchor="{$left} {$bottom}" LeftDirection="{$left} {$bottom}" RightDirection="{$left} {$bottom}"/>
							<PathPoint Anchor="{$right} {$bottom}" LeftDirection="{$right} {$bottom}" RightDirection="{$right} {$bottom}"/>
							<PathPoint Anchor="{$right} {$top}" LeftDirection="{$right} {$top}" RightDirection="{$right} {$top}"/>
						</PathPointArray>
					</GeometryPath>
			</PathGeometry>
		</Properties>
	</TextFrame>
</xsl:template>
</xsl:stylesheet>
