<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
	<xsl:output method="xml" indent="yes"/>
	<xsl:template match="/package/masterspreads">
		<xsl:document href="{$workingdir}{$filesep}MasterSpreads{$filesep}MasterSpread_A.xml" method="xml" indent="yes">
			
			<idPkg:MasterSpread xmlns:idPkg="http://ns.adobe.com/AdobeInDesign/idml/1.0/packaging" DOMVersion="7.5">
				<MasterSpread Self="MasterSpread_A" ItemTransform="1 0 0 1 0 0" Name="A-Master" NamePrefix="A" BaseName="Master" ShowMasterItems="true" PageCount="2" OverriddenPageItemProps="">
					<Page Self="MasterSpread_A_Page_1" Name="A" AppliedTrapPreset="TrapPreset/$ID/kDefaultTrapStyleName" AppliedMaster="n" OverrideList="" TabOrder="" GridStartingPoint="TopOutside" UseMasterGrid="true">
						<MarginPreference ColumnCount="1" ColumnGutter="12" Top="36" Bottom="36" Left="36" Right="36" ColumnDirection="Horizontal" ColumnsPositions="0 540"/>
						<GridDataInformation FontStyle="Regular" PointSize="12" CharacterAki="0" LineAki="9" HorizontalScale="100" VerticalScale="100" LineAlignment="LeftOrTopLineJustify" GridAlignment="AlignEmCenter" CharacterAlignment="AlignEmCenter">
							<Properties>
								<AppliedFont type="string">Times New Roman</AppliedFont>
							</Properties>
						</GridDataInformation>
					</Page>
					<Page Self="MasterSpread_A_Page_2" Name="A" AppliedTrapPreset="TrapPreset/$ID/kDefaultTrapStyleName" AppliedMaster="n" OverrideList="" TabOrder="" GridStartingPoint="TopOutside" UseMasterGrid="true">
						<MarginPreference ColumnCount="1" ColumnGutter="12" Top="36" Bottom="36" Left="36" Right="36" ColumnDirection="Horizontal" ColumnsPositions="0 540"/>
						<GridDataInformation FontStyle="Regular" PointSize="12" CharacterAki="0" LineAki="9" HorizontalScale="100" VerticalScale="100" LineAlignment="LeftOrTopLineJustify" GridAlignment="AlignEmCenter" CharacterAlignment="AlignEmCenter">
							<Properties>
								<AppliedFont type="string">Times New Roman</AppliedFont>
							</Properties>
						</GridDataInformation>
					</Page>
				</MasterSpread>
			</idPkg:MasterSpread>
		</xsl:document>
	</xsl:template>
</xsl:stylesheet>