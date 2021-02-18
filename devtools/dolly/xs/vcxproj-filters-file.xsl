<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
<xsl:import href="global-variables.xsl"/>
<xsl:output method="xml" indent="yes"/>


<xsl:template match="vcxproj-filters-file">Generating vcxproj.filters file from template...
 <xsl:document href="{/code/@win-project-dir}{$filesep}{/code/@long-name}.vcxproj.filters" method="xml" indent="yes">
  <xsl:call-template name="filters"/>
  </xsl:document>
</xsl:template>

<xsl:template match="filters" name="filters">
<xsl:variable name="lname" select="/code/@long-name"/>
<xsl:variable name="sname" select="/code/@short-name"/>
<xsl:variable name="idheaderdir" select="/code/@win-id-header-dir"/>
<xsl:variable name="sourcedir" select="/code/@win-source-dir"/>

<Project ToolsVersion="4.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <ItemGroup>
    <Filter Include="Source Files">
      <UniqueIdentifier>{78120e3d-d0ab-4f9e-8a3a-c5e6c5ed0b2c}</UniqueIdentifier>
    </Filter>
    <Filter Include="Source Files\Plugin">
      <UniqueIdentifier>{29e08cac-b659-428b-bf02-c70f84b41ddf}</UniqueIdentifier>
    </Filter>
    <Filter Include="Header Files">
      <UniqueIdentifier>{7b823eb7-8f35-4529-a4c1-555b53468c58}</UniqueIdentifier>
    </Filter>
    <Filter Include="Resource Files">
      <UniqueIdentifier>{4da94837-4922-4930-b2ec-472d16090ed6}</UniqueIdentifier>
    </Filter>
  </ItemGroup>
  <ItemGroup>
    <xsl:for-each select="/code/*[@impl-name]">
      <xsl:element name="ClCompile">
        <xsl:attribute name="Include"><xsl:value-of select="$sourcedir"/>\<xsl:value-of select="@impl-name"/>.cpp</xsl:attribute>
        <Filter>Source Files</Filter>
      </xsl:element>   
    </xsl:for-each>
    
    <xsl:element name="ClCompile">
      <xsl:attribute name="Include">$(id_sdk_dir)\source\public\libs\publiclib\statics\PlugInStatics.cpp</xsl:attribute>
      <Filter>Source Files\Plugin</Filter>
    </xsl:element>
    
    <xsl:element name="ClCompile">
      <xsl:attribute name="Include">$(ID_SDK_DIR)\source\sdksamples\common\SDKPlugInEntrypoint.cpp</xsl:attribute>
      <Filter>Source Files\Plugin</Filter>
    </xsl:element>

    <xsl:element name="ClCompile">
      <xsl:attribute name="Include"><xsl:value-of select="$sourcedir"/>\<xsl:value-of select="$sname"/>ID.cpp</xsl:attribute>
      <Filter>Source Files\Plugin</Filter>
    </xsl:element>
    
    <xsl:element name="ClCompile">
      <xsl:attribute name="Include"><xsl:value-of select="$sourcedir"/>\<xsl:value-of select="$sname"/>NoStrip.cpp</xsl:attribute>
      <Filter>Source Files\Plugin</Filter>
    </xsl:element>
    
    <xsl:element name="ClCompile">
      <xsl:attribute name="Include"><xsl:value-of select="$sourcedir"/>\TriggerResourceDeps.cpp</xsl:attribute>
      <Filter>Source Files\Plugin</Filter>
    </xsl:element>    
    
    <ClCompile Include="$(id_sdk_dir)\source\precomp\msvc\VCPlugInHeaders.cpp">
      <Filter>Source Files\Plugin</Filter>
    </ClCompile>
  </ItemGroup>
  <ItemGroup>
     <xsl:for-each select="/code/*[@header-file]">
      <xsl:element name="ClInclude">
        <xsl:attribute name="Include"><xsl:value-of select="$idheaderdir"/>\<xsl:value-of select="@header-file"/></xsl:attribute>
        <Filter>Header Files</Filter>
      </xsl:element>
    </xsl:for-each>
		
    <xsl:element name="ClInclude">
      <xsl:attribute name="Include"><xsl:value-of select="$sourcedir"/>\<xsl:value-of select="$sname"/>ID.h</xsl:attribute>
      <Filter>Header Files</Filter>
    </xsl:element>
    
    <xsl:element name="ClInclude">
      <xsl:attribute name="Include"><xsl:value-of select="$sourcedir"/>\<xsl:value-of select="$sname"/>FactoryList.h</xsl:attribute>
      <Filter>Header Files</Filter>
    </xsl:element>
  </ItemGroup> 
  
  <ItemGroup>
    <xsl:element name="ResourceCompile">
      <xsl:attribute name="Include"><xsl:value-of select="$sourcedir"/>\<xsl:value-of select="$sname"/>.rc</xsl:attribute>
      <Filter>Resource Files</Filter>
    </xsl:element>
  </ItemGroup>
 
  <ItemGroup>
    <xsl:element name="CustomBuild">
      <xsl:attribute name="Include"><xsl:value-of select="$sourcedir"/>\<xsl:value-of select="$sname"/>.fr</xsl:attribute>
      <Filter>Resource Files</Filter>
    </xsl:element>
  </ItemGroup>
</Project>

</xsl:template>
	
</xsl:stylesheet>