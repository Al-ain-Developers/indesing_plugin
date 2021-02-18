<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
<xsl:import href="global-variables.xsl"/>
<xsl:output method="xml" indent="yes"/>


<xsl:template match="vcxproj-file">Generating vcxproj file from template...
 <xsl:document href="{/code/@win-project-dir}{$filesep}{/code/@long-name}.vcxproj" method="xml" indent="yes">
  <xsl:call-template name="vcxproj"/>
  </xsl:document>
</xsl:template>

<xsl:template match="vcxproj" name="vcxproj">
<xsl:variable name="lname" select="/code/@long-name"/>
<xsl:variable name="sname" select="/code/@short-name"/>
<xsl:variable name="idheaderdir" select="/code/@win-id-header-dir"/>
<xsl:variable name="sourcedir" select="/code/@win-source-dir"/>
<xsl:variable name="debugintermediatedir" select="/code/@win-debug-intermediate-dir"/>
<xsl:variable name="debugintermediatedirx64" select="/code/@win-debug-intermediate-dir-x64"/>
<xsl:variable name="debugtargetdir" select="/code/@win-debug-target-dir"/>
<xsl:variable name="debugtargetdirx64" select="/code/@win-debug-target-dir-x64"/>
<xsl:variable name="releaseintermediatedir" select="/code/@win-release-intermediate-dir"/>
<xsl:variable name="releaseintermediatedirx64" select="/code/@win-release-intermediate-dir-x64"/>
<xsl:variable name="releasetargetdir" select="/code/@win-release-target-dir"/>
<xsl:variable name="releasetargetdirx64" select="/code/@win-release-target-dir-x64"/>

<xsl:variable name="cpprspfile" select="/code/@win-specific-cpp-rsp-file"/>
<xsl:variable name="odfrcrspfile" select="/code/@win-specific-odfrc-rsp-file"/>

<xsl:variable name="mycpprspfile">
	<xsl:choose>
		<xsl:when test="string-length($cpprspfile) > 0"><xsl:value-of select="$cpprspfile"/></xsl:when>
		<xsl:otherwise><xsl:value-of select="concat($lname, 'cpp.rsp')"/></xsl:otherwise>
	</xsl:choose>
</xsl:variable>

<xsl:variable name="myodfrcrspfile">
	<xsl:choose>
		<xsl:when test="string-length($odfrcrspfile) > 0"><xsl:value-of select="$odfrcrspfile"/></xsl:when>
		<xsl:otherwise><xsl:value-of select="concat($lname, 'odfrc.rsp')"/></xsl:otherwise>
	</xsl:choose>
</xsl:variable>

<Project DefaultTargets="Build" ToolsVersion="15.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <ItemGroup Label="ProjectConfigurations">
    <ProjectConfiguration Include="Debug|Win32">
      <Configuration>Debug</Configuration>
      <Platform>Win32</Platform>
    </ProjectConfiguration>
    <ProjectConfiguration Include="Debug|x64">
      <Configuration>Debug</Configuration>
      <Platform>x64</Platform>
    </ProjectConfiguration>
    <ProjectConfiguration Include="Release|Win32">
      <Configuration>Release</Configuration>
      <Platform>Win32</Platform>
    </ProjectConfiguration>
    <ProjectConfiguration Include="Release|x64">
      <Configuration>Release</Configuration>
      <Platform>x64</Platform>
    </ProjectConfiguration>
  </ItemGroup>
  <PropertyGroup Label="Globals">
    <xsl:element name="ProjectName">      <xsl:value-of select="$lname" />    </xsl:element>
    <WindowsTargetPlatformVersion>10.0.15063.0</WindowsTargetPlatformVersion>
  </PropertyGroup>
  <Import Project="$(VCTargetsPath)\Microsoft.Cpp.Default.props" />
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'" Label="Configuration">
    <ConfigurationType>DynamicLibrary</ConfigurationType>
	<PlatformToolset>v141</PlatformToolset>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'" Label="Configuration">
    <ConfigurationType>DynamicLibrary</ConfigurationType>
	<PlatformToolset>v141</PlatformToolset>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|x64'" Label="Configuration">
    <ConfigurationType>DynamicLibrary</ConfigurationType>
	<PlatformToolset>v141</PlatformToolset>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|x64'" Label="Configuration">
    <ConfigurationType>DynamicLibrary</ConfigurationType>
	<PlatformToolset>v141</PlatformToolset>
  </PropertyGroup>
  <Import Project="$(VCTargetsPath)\Microsoft.Cpp.props" />
  <ImportGroup Label="ExtensionSettings">
  </ImportGroup>
  <ImportGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'" Label="PropertySheets">
    <Import Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
    <Import><xsl:attribute name="Project"><xsl:value-of select="$sname" />ReleaseWin32.sdk.props</xsl:attribute></Import>
  </ImportGroup>
  <ImportGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'" Label="PropertySheets">
    <Import Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
    <Import><xsl:attribute name="Project"><xsl:value-of select="$sname" />DebugWin32.sdk.props</xsl:attribute></Import>
  </ImportGroup>
  <ImportGroup Condition="'$(Configuration)|$(Platform)'=='Release|x64'" Label="PropertySheets">
    <Import Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
    <Import><xsl:attribute name="Project"><xsl:value-of select="$sname" />ReleaseX64.sdk.props</xsl:attribute></Import>
  </ImportGroup>
  <ImportGroup Condition="'$(Configuration)|$(Platform)'=='Debug|x64'" Label="PropertySheets">
    <Import Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
    <Import><xsl:attribute name="Project"><xsl:value-of select="$sname" />DebugX64.sdk.props</xsl:attribute></Import>
  </ImportGroup>
  <PropertyGroup Label="UserMacros" />
  <PropertyGroup>
    <_ProjectFileVersion>10.0.40219.1</_ProjectFileVersion>
    <xsl:element name="OutDir"><xsl:attribute name="Condition">'$(Configuration)|$(Platform)'=='Debug|Win32'</xsl:attribute><xsl:value-of select="$debugtargetdir"/>\</xsl:element>
    <xsl:element name="IntDir"><xsl:attribute name="Condition">'$(Configuration)|$(Platform)'=='Debug|Win32'</xsl:attribute><xsl:value-of select="$debugintermediatedir"/>\<xsl:value-of select="$lname"/>\</xsl:element>
    <xsl:element name="OutDir"><xsl:attribute name="Condition">'$(Configuration)|$(Platform)'=='Debug|x64'</xsl:attribute><xsl:value-of select="$debugtargetdirx64"/>\</xsl:element>
    <xsl:element name="IntDir"><xsl:attribute  name="Condition">'$(Configuration)|$(Platform)'=='Debug|x64'</xsl:attribute><xsl:value-of select="$debugintermediatedirx64"/>\<xsl:value-of select="$lname"/>\</xsl:element>
    <xsl:element name="OutDir"><xsl:attribute name="Condition">'$(Configuration)|$(Platform)'=='Release|Win32'</xsl:attribute><xsl:value-of select="$releasetargetdir"/>\</xsl:element>
    <xsl:element name="IntDir"><xsl:attribute name="Condition">'$(Configuration)|$(Platform)'=='Release|Win32'</xsl:attribute><xsl:value-of select="$releaseintermediatedir"/>\<xsl:value-of select="$lname"/>\</xsl:element>
    <xsl:element name="OutDir"><xsl:attribute name="Condition">'$(Configuration)|$(Platform)'=='Release|x64'</xsl:attribute><xsl:value-of select="$releasetargetdirx64"/>\</xsl:element>
    <xsl:element name="IntDir"><xsl:attribute name="Condition">'$(Configuration)|$(Platform)'=='Release|x64'</xsl:attribute><xsl:value-of select="$releaseintermediatedirx64"/>\<xsl:value-of select="$lname"/>\</xsl:element>
    
    <TargetName Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">$(ProjectName).sdk</TargetName>
    <TargetName Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">$(ProjectName).sdk</TargetName>
    <TargetName Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">$(ProjectName).sdk</TargetName>
    <TargetName Condition="'$(Configuration)|$(Platform)'=='Release|x64'">$(ProjectName).sdk</TargetName>
    <TargetExt Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">.pln</TargetExt>
    <TargetExt Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">.pln</TargetExt>
    <TargetExt Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">.pln</TargetExt>
    <TargetExt Condition="'$(Configuration)|$(Platform)'=='Release|x64'">.pln</TargetExt>
  </PropertyGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">
    <Midl>
      <PreprocessorDefinitions>_CRT_SECURE_NO_DEPRECATE;_DEBUG;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <MkTypLibCompatible>true</MkTypLibCompatible>
      <TargetEnvironment>Win32</TargetEnvironment>
      <xsl:element name="TypeLibraryName">$(IntDir)<xsl:value-of select="$lname"/>.tlb</xsl:element>
      <HeaderFileName>
      </HeaderFileName>
    </Midl>
    <ClCompile>
      <xsl:element name="AdditionalOptions">/vmg @&quot;<xsl:value-of select="$mycpprspfile"/>&quot;</xsl:element>
      <xsl:element name="PrecompiledHeaderOutputFile">$(IntDir)<xsl:value-of select="$lname"/>.pch</xsl:element>
      <PreprocessorDefinitions>_CRT_SECURE_NO_DEPRECATE;BOOST_SYSTEM_NO_DEPRECATED;DEBUG;STRICT;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <PrecompiledHeader>Use</PrecompiledHeader>
      <PrecompiledHeaderFile>VCPlugInHeaders.h</PrecompiledHeaderFile>
      <ObjectFileName>$(IntDir)</ObjectFileName>
    </ClCompile>
    <ResourceCompile>
      <PreprocessorDefinitions>_CRT_SECURE_NO_DEPRECATE;DEBUG;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <Culture>0x0409</Culture>
    </ResourceCompile>
    <PreLinkEvent>
      <xsl:element name="Command">merge_res.cmd &quot;$(IntDir)&quot;  <xsl:value-of select="$sname"/> &amp; echo Deleting old resources... &amp; del /f /s "$(TargetDir)($(TargetName) Resources)\"*.idrc &gt; $(IntDir)prevDeletedResources.txt &amp;  xcopy /Q /E &quot;$(IntDir)&quot;*.idrc &quot;$(TargetDir)($(TargetName) Resources)\&quot; /Y</xsl:element>
    </PreLinkEvent>
    <Link>
      <xsl:element name="AdditionalDependencies">$(ID_SDK_DIR)\build\win\objd\PMRuntime.lib; $(ID_SDK_DIR)\build\win\objd\Public.lib; <xsl:if test="not(contains(string(/code/@plugin-type),'kModelPlugIn'))">$(ID_SDK_DIR)\build\win\objd\WidgetBin.lib</xsl:if></xsl:element>
      <OutputFile>$(OutDir)$(TargetName)$(TargetExt)</OutputFile>
      <xsl:element name="ProgramDatabaseFile"><xsl:value-of select="$debugtargetdir"/>\<xsl:value-of select="$lname"/>.pdb</xsl:element>
			<xsl:element name="ImportLibrary">$(LIB_DIR)\<xsl:value-of select="$lname"/>/<xsl:value-of select="$lname"/>.lib</xsl:element>
    </Link>
    <PostBuildEvent>
      <xsl:element name="Command">restore_res.cmd &quot;$(IntDir)&quot;  <xsl:value-of select="$sname"/></xsl:element>
    </PostBuildEvent>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">
    <Midl>
      <PreprocessorDefinitions>_CRT_SECURE_NO_DEPRECATE;_DEBUG;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <MkTypLibCompatible>true</MkTypLibCompatible>
      <TargetEnvironment>X64</TargetEnvironment>
      <xsl:element name="TypeLibraryName">$(IntDir)<xsl:value-of select="$lname"/>.tlb</xsl:element>
      <HeaderFileName>
      </HeaderFileName>
    </Midl>
    <ClCompile>
      <xsl:element name="AdditionalOptions">/vmg @&quot;<xsl:value-of select="$mycpprspfile"/>&quot;</xsl:element>
      <PreprocessorDefinitions>_CRT_SECURE_NO_DEPRECATE;BOOST_SYSTEM_NO_DEPRECATED;DEBUG;STRICT;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <PrecompiledHeader>Use</PrecompiledHeader>
      <PrecompiledHeaderFile>VCPlugInHeaders.h</PrecompiledHeaderFile>
      <xsl:element name="PrecompiledHeaderOutputFile">$(IntDir)<xsl:value-of select="$lname"/>.pch</xsl:element>
      <ObjectFileName>$(IntDir)</ObjectFileName>
    </ClCompile>
    <ResourceCompile>
      <PreprocessorDefinitions>_CRT_SECURE_NO_DEPRECATE;DEBUG;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <Culture>0x0409</Culture>
    </ResourceCompile>
    <PreLinkEvent>
      <xsl:element name="Command">merge_res.cmd &quot;$(IntDir)&quot;  <xsl:value-of select="$sname"/> &amp; echo Deleting old resources... &amp; del /f /s "$(TargetDir)($(TargetName) Resources)\"*.idrc &gt; $(IntDir)prevDeletedResources.txt &amp;  xcopy /Q /E &quot;$(IntDir)&quot;*.idrc &quot;$(TargetDir)($(TargetName) Resources)\&quot; /Y</xsl:element>
    </PreLinkEvent>
    <Link>
      <xsl:element name="AdditionalDependencies">$(ID_SDK_DIR)\build\win\objdx64\PMRuntime.lib; $(ID_SDK_DIR)\build\win\objdx64\Public.lib; <xsl:if test="not(contains(string(/code/@plugin-type),'kModelPlugIn'))">$(ID_SDK_DIR)\build\win\objdx64\WidgetBin.lib</xsl:if></xsl:element>
      <OutputFile>$(OutDir)$(TargetName)$(TargetExt)</OutputFile>
      <xsl:element name="ProgramDatabaseFile"><xsl:value-of select="$debugtargetdirx64"/>\<xsl:value-of select="$lname"/>.pdb</xsl:element>
      <xsl:element name="ImportLibrary">$(LIB_DIR)\<xsl:value-of select="$lname"/>/<xsl:value-of select="$lname"/>.lib</xsl:element>
    </Link>
    <PostBuildEvent>
      <xsl:element name="Command">restore_res.cmd &quot;$(IntDir)&quot;  <xsl:value-of select="$sname"/></xsl:element>
    </PostBuildEvent>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">
    <Midl>
      <PreprocessorDefinitions>_CRT_SECURE_NO_DEPRECATE;NDEBUG;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <MkTypLibCompatible>true</MkTypLibCompatible>
      <TargetEnvironment>Win32</TargetEnvironment>
      <xsl:element name="TypeLibraryName">$(IntDir)<xsl:value-of select="$lname"/>.tlb</xsl:element>
      <HeaderFileName>
      </HeaderFileName>
    </Midl>
    <ClCompile>
      <xsl:element name="AdditionalOptions">/vmg @&quot;<xsl:value-of select="$mycpprspfile"/>&quot;</xsl:element>
      <PreprocessorDefinitions>_CRT_SECURE_NO_DEPRECATE;BOOST_SYSTEM_NO_DEPRECATED;STRICT;NDEBUG;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <StringPooling>true</StringPooling>
      <PrecompiledHeader>Use</PrecompiledHeader>
      <PrecompiledHeaderFile>VCPlugInHeaders.h</PrecompiledHeaderFile>
      <xsl:element name="PrecompiledHeaderOutputFile">$(IntDir)<xsl:value-of select="$lname"/>.pch</xsl:element>
      <ObjectFileName>$(IntDir)</ObjectFileName>
    </ClCompile>
    <ResourceCompile>
      <PreprocessorDefinitions>_CRT_SECURE_NO_DEPRECATE;NDEBUG;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <Culture>0x0409</Culture>
    </ResourceCompile>
    <PreLinkEvent>
      <xsl:element name="Command">merge_res.cmd &quot;$(IntDir)&quot;  <xsl:value-of select="$sname"/> &amp; echo Deleting old resources... &amp; del /f /s "$(TargetDir)($(TargetName) Resources)\"*.idrc &gt; $(IntDir)prevDeletedResources.txt &amp;  xcopy /Q /E &quot;$(IntDir)&quot;*.idrc &quot;$(TargetDir)($(TargetName) Resources)\&quot; /Y</xsl:element>
    </PreLinkEvent>
    <Link>
      <AdditionalOptions>/IGNORE:4089 %(AdditionalOptions)</AdditionalOptions>
      <xsl:element name="AdditionalDependencies">$(ID_SDK_DIR)\build\win\objr\PMRuntime.lib; $(ID_SDK_DIR)\build\win\objr\Public.lib; <xsl:if test="not(contains(string(/code/@plugin-type),'kModelPlugIn'))">$(ID_SDK_DIR)\build\win\objr\WidgetBin.lib</xsl:if></xsl:element>
      <OutputFile>$(OutDir)$(TargetName)$(TargetExt)</OutputFile>
      <xsl:element name="ProgramDatabaseFile"><xsl:value-of select="$releasetargetdir"/>\<xsl:value-of select="$lname"/>.pdb</xsl:element>
      <xsl:element name="ImportLibrary">$(LIB_DIR)\<xsl:value-of select="$lname"/>/<xsl:value-of select="$lname"/>.lib</xsl:element>
    </Link>
    <PostBuildEvent>
      <xsl:element name="Command">restore_res.cmd &quot;$(IntDir)&quot;  <xsl:value-of select="$sname"/></xsl:element>
    </PostBuildEvent>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Release|x64'">
    <Midl>
      <PreprocessorDefinitions>_CRT_SECURE_NO_DEPRECATE;NDEBUG;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <MkTypLibCompatible>true</MkTypLibCompatible>
      <TargetEnvironment>X64</TargetEnvironment>
      <xsl:element name="TypeLibraryName">$(IntDir)<xsl:value-of select="$lname"/>.tlb</xsl:element>
      <HeaderFileName>
      </HeaderFileName>
    </Midl>
    <ClCompile>
      <xsl:element name="AdditionalOptions">/vmg @&quot;<xsl:value-of select="$mycpprspfile"/>&quot;</xsl:element>
      <PreprocessorDefinitions>_CRT_SECURE_NO_DEPRECATE;BOOST_SYSTEM_NO_DEPRECATED;STRICT;NDEBUG;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <StringPooling>true</StringPooling>
      <PrecompiledHeader>Use</PrecompiledHeader>
      <PrecompiledHeaderFile>VCPlugInHeaders.h</PrecompiledHeaderFile>
      <xsl:element name="PrecompiledHeaderOutputFile">$(IntDir)<xsl:value-of select="$lname"/>.pch</xsl:element>
      <ObjectFileName>$(IntDir)</ObjectFileName>
    </ClCompile>
    <ResourceCompile>
      <PreprocessorDefinitions>_CRT_SECURE_NO_DEPRECATE;NDEBUG;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <Culture>0x0409</Culture>
    </ResourceCompile>
    <PreLinkEvent>
      <xsl:element name="Command">merge_res.cmd &quot;$(IntDir)&quot;  <xsl:value-of select="$sname"/> &amp; echo Deleting old resources... &amp; del /f /s "$(TargetDir)($(TargetName) Resources)\"*.idrc &gt; $(IntDir)prevDeletedResources.txt &amp;  xcopy /Q /E &quot;$(IntDir)&quot;*.idrc &quot;$(TargetDir)($(TargetName) Resources)\&quot; /Y</xsl:element>
    </PreLinkEvent>
    <Link>
      <AdditionalOptions>/IGNORE:4089 %(AdditionalOptions)</AdditionalOptions>
      <xsl:element name="AdditionalDependencies">$(ID_SDK_DIR)\build\win\objrx64\PMRuntime.lib; $(ID_SDK_DIR)\build\win\objrx64\Public.lib; <xsl:if test="not(contains(string(/code/@plugin-type),'kModelPlugIn'))">$(ID_SDK_DIR)\build\win\objrx64\WidgetBin.lib</xsl:if></xsl:element>
      <OutputFile>$(OutDir)$(TargetName)$(TargetExt)</OutputFile>
      <xsl:element name="ProgramDatabaseFile"><xsl:value-of select="$releasetargetdirx64"/>\<xsl:value-of select="$lname"/>.pdb</xsl:element>
      <xsl:element name="ImportLibrary">$(LIB_DIR)\<xsl:value-of select="$lname"/>/<xsl:value-of select="$lname"/>.lib</xsl:element>
    </Link>
    <PostBuildEvent>
      <xsl:element name="Command">restore_res.cmd &quot;$(IntDir)&quot;  <xsl:value-of select="$sname"/></xsl:element>
    </PostBuildEvent>
  </ItemDefinitionGroup>
  <ItemGroup>
    <xsl:for-each select="/code/*[@impl-name]">
      <xsl:element name="ClCompile">
        <xsl:attribute name="Include"><xsl:value-of select="$sourcedir"/>\<xsl:value-of select="@impl-name"/>.cpp</xsl:attribute>
      </xsl:element>   
    </xsl:for-each>
    <xsl:element name="ClCompile">
      <xsl:attribute name="Include">$(id_sdk_dir)\source\public\libs\publiclib\statics\PlugInStatics.cpp</xsl:attribute>
    </xsl:element>
    
    <xsl:element name="ClCompile">
      <xsl:attribute name="Include">$(ID_SDK_DIR)\source\sdksamples\common\SDKPlugInEntrypoint.cpp</xsl:attribute>
    </xsl:element>

    <xsl:element name="ClCompile">
      <xsl:attribute name="Include"><xsl:value-of select="$sourcedir"/>\<xsl:value-of select="$sname"/>ID.cpp</xsl:attribute>
    </xsl:element>
    
    <xsl:element name="ClCompile">
      <xsl:attribute name="Include"><xsl:value-of select="$sourcedir"/>\<xsl:value-of select="$sname"/>NoStrip.cpp</xsl:attribute>
    </xsl:element>
    
    <xsl:element name="ClCompile">
      <xsl:attribute name="Include"><xsl:value-of select="$sourcedir"/>\TriggerResourceDeps.cpp</xsl:attribute>
    </xsl:element>    
    
    <ClCompile Include="$(id_sdk_dir)\source\precomp\msvc\VCPlugInHeaders.cpp">
      <PrecompiledHeader Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">Create</PrecompiledHeader>
      <PrecompiledHeader Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">Create</PrecompiledHeader>
      <PrecompiledHeader Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">Create</PrecompiledHeader>
      <PrecompiledHeader Condition="'$(Configuration)|$(Platform)'=='Release|x64'">Create</PrecompiledHeader>
    </ClCompile>
  </ItemGroup>
  
  <ItemGroup>
    <xsl:for-each select="/code/*[@header-file]">
      <xsl:element name="ClInclude">
        <xsl:attribute name="Include"><xsl:value-of select="$idheaderdir"/>\<xsl:value-of select="@header-file"/></xsl:attribute>
      </xsl:element>
    </xsl:for-each>
		
    <xsl:element name="ClInclude">
      <xsl:attribute name="Include"><xsl:value-of select="$sourcedir"/>\<xsl:value-of select="$sname"/>ID.h</xsl:attribute>
    </xsl:element>
    
    <xsl:element name="ClInclude">
      <xsl:attribute name="Include"><xsl:value-of select="$sourcedir"/>\<xsl:value-of select="$sname"/>FactoryList.h</xsl:attribute>
    </xsl:element>

  </ItemGroup>
  <ItemGroup>
    <xsl:element name="CustomBuild">
      <xsl:attribute name="Include"><xsl:value-of select="$sourcedir"/>\<xsl:value-of select="$sname"/>.fr</xsl:attribute>
      
      <xsl:element name="Command">
        <xsl:attribute name="Condition">'$(Configuration)|$(Platform)'=='Debug|Win32'</xsl:attribute>
        odfrc $(ODFRC_ADDITIONAL_FLAGS) &quot;%(FullPath)&quot; -o &quot;$(IntDir)%(Filename).fres&quot; -d DEBUG  -i &quot;<xsl:value-of select="$sourcedir"/>&quot; @&quot;<xsl:value-of select="$myodfrcrspfile"/>&quot;
      </xsl:element>
      <AdditionalInputs Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">$(IntDir)TriggerResourceDeps.obj;%(AdditionalInputs)</AdditionalInputs>
      <Outputs Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">$(IntDir)%(Filename).fres;%(Outputs)</Outputs>
      
      <xsl:element name="Command">
        <xsl:attribute name="Condition">'$(Configuration)|$(Platform)'=='Debug|x64'</xsl:attribute>
        odfrc $(ODFRC_ADDITIONAL_FLAGS) &quot;%(FullPath)&quot; -o &quot;$(IntDir)%(Filename).fres&quot; -d DEBUG  -i &quot;<xsl:value-of select="$sourcedir"/>&quot; @&quot;<xsl:value-of select="$myodfrcrspfile"/>&quot;
      </xsl:element>
      <AdditionalInputs Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">$(IntDir)TriggerResourceDeps.obj;%(AdditionalInputs)</AdditionalInputs>
      <Outputs Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">$(IntDir)%(Filename).fres;%(Outputs)</Outputs>
      
      <xsl:element name="Command">
        <xsl:attribute name="Condition">'$(Configuration)|$(Platform)'=='Release|Win32'</xsl:attribute>
        odfrc $(ODFRC_ADDITIONAL_FLAGS) &quot;%(FullPath)&quot; -o &quot;$(IntDir)%(Filename).fres&quot; -i &quot;<xsl:value-of select="$sourcedir"/>&quot; @&quot;<xsl:value-of select="$myodfrcrspfile"/>&quot;
      </xsl:element>
      <AdditionalInputs Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">$(IntDir)TriggerResourceDeps.obj;%(AdditionalInputs)</AdditionalInputs>
      <Outputs Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">$(IntDir)%(Filename).fres;%(Outputs)</Outputs>
      
      <xsl:element name="Command">
        <xsl:attribute name="Condition">'$(Configuration)|$(Platform)'=='Release|x64'</xsl:attribute>
        odfrc $(ODFRC_ADDITIONAL_FLAGS) &quot;%(FullPath)&quot; -o &quot;$(IntDir)%(Filename).fres&quot; -i &quot;<xsl:value-of select="$sourcedir"/>&quot; @&quot;<xsl:value-of select="$myodfrcrspfile"/>&quot;
      </xsl:element>
      <AdditionalInputs Condition="'$(Configuration)|$(Platform)'=='Release|x64'">$(IntDir)TriggerResourceDeps.obj;%(AdditionalInputs)</AdditionalInputs>
      <Outputs Condition="'$(Configuration)|$(Platform)'=='Release|x64'">$(IntDir)%(Filename).fres;%(Outputs)</Outputs>
    </xsl:element>
  </ItemGroup>
  
  <ItemGroup>   
    <xsl:element name="ResourceCompile">
      <xsl:attribute name="Include"><xsl:value-of select="$sourcedir"/>\<xsl:value-of select="$sname"/>.rc</xsl:attribute>
      <PreprocessorDefinitions Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">_CRT_SECURE_NO_DEPRECATE;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <Culture Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">0x0809</Culture>
      <xsl:element name="AdditionalIncludeDirectories">
        <xsl:attribute name="Condition">'$(Configuration)|$(Platform)'=='Debug|Win32'</xsl:attribute>
        <xsl:value-of select="$idheaderdir"/>;<xsl:value-of select="$sourcedir"/>;$(ID_SDK_DIR)\source\precomp\msvc;$(ID_SDK_DIR)\source\public\includes;$(ID_SDK_DIR)\source\sdksamples\common;%(AdditionalIncludeDirectories)
      </xsl:element>
     
      <PreprocessorDefinitions Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">_CRT_SECURE_NO_DEPRECATE;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <Culture Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">0x0809</Culture>
      <xsl:element name="AdditionalIncludeDirectories">
        <xsl:attribute name="Condition">'$(Configuration)|$(Platform)'=='Debug|x64'</xsl:attribute>
        <xsl:value-of select="$idheaderdir"/>;<xsl:value-of select="$sourcedir"/>;$(ID_SDK_DIR)\source\precomp\msvc;$(ID_SDK_DIR)\source\public\includes;$(ID_SDK_DIR)\source\sdksamples\common;%(AdditionalIncludeDirectories)
      </xsl:element>
     
      <PreprocessorDefinitions Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">_CRT_SECURE_NO_DEPRECATE;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <Culture Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">0x0809</Culture>
      <xsl:element name="AdditionalIncludeDirectories">
        <xsl:attribute name="Condition">'$(Configuration)|$(Platform)'=='Release|Win32'</xsl:attribute>
        <xsl:value-of select="$idheaderdir"/>;<xsl:value-of select="$sourcedir"/>;$(ID_SDK_DIR)\source\precomp\msvc;$(ID_SDK_DIR)\source\public\includes;$(ID_SDK_DIR)\source\sdksamples\common;%(AdditionalIncludeDirectories)
      </xsl:element>
      
      <PreprocessorDefinitions Condition="'$(Configuration)|$(Platform)'=='Release|x64'">_CRT_SECURE_NO_DEPRECATE;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <Culture Condition="'$(Configuration)|$(Platform)'=='Release|x64'">0x0809</Culture>
      <xsl:element name="AdditionalIncludeDirectories">
        <xsl:attribute name="Condition">'$(Configuration)|$(Platform)'=='Release|x64'</xsl:attribute>
        <xsl:value-of select="$idheaderdir"/>;<xsl:value-of select="$sourcedir"/>;$(ID_SDK_DIR)\source\precomp\msvc;$(ID_SDK_DIR)\source\public\includes;$(ID_SDK_DIR)\source\sdksamples\common;%(AdditionalIncludeDirectories)
      </xsl:element>
    </xsl:element>
  </ItemGroup>
  <Import Project="$(VCTargetsPath)\Microsoft.Cpp.targets" />
  <ImportGroup Label="ExtensionTargets">
  </ImportGroup>
</Project>

	</xsl:template>
	
</xsl:stylesheet>