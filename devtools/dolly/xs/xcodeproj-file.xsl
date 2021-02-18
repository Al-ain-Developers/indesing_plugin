<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
	<xsl:output method="text" indent="yes"/>
	
<xsl:template match="xcodeproj-file">
Generating xcodeproj file from template...
 <xsl:document href="{/code/@mac-project-dir}{$filesep}{/code/@long-name}.xcodeproj/project.pbxproj" method="text" indent="yes">
			<xsl:call-template name="pbx-file"/>
		</xsl:document>
	</xsl:template>

<xsl:variable name="lname" select="/code/@long-name"/>
	<xsl:variable name="sname" select="/code/@short-name"/>
	<xsl:variable name="iddir" select="/code/@mac-id-header-dir"/>
	<xsl:variable name="iddir-escaped" select="/code/@mac-id-header-dir-escaped"/>
	<xsl:variable name="sdkdir" select="/code/@mac-sdk-dir"/>
	<xsl:variable name="sdkdir-escaped" select="/code/@mac-sdk-dir-escaped"/>
	<xsl:variable name="sourcedir" select="/code/@mac-source-dir"/>
	<xsl:variable name="debugtargetdir" select="/code/@mac-debug-target-dir"/>
	<xsl:variable name="releasetargetdir" select="/code/@mac-release-target-dir"/>
	<xsl:variable name="plugintype" select="/code/@plugin-type"/>
	<xsl:variable name="indesignframework">
		<xsl:choose>
			<xsl:when test="contains($plugintype, 'kModelPlugIn')">InDesignModel</xsl:when>
			<xsl:otherwise>InDesignModelAndUI</xsl:otherwise>
		</xsl:choose>
	</xsl:variable>

	<xsl:variable name="xcconfigfile" select="/code/@mac-specific-xcconfig-file"/>
	<xsl:variable name="debugxcconfigfile" select="/code/@mac-specific-debug-xcconfig-file"/>
	<xsl:variable name="releasexcconfigfile" select="/code/@mac-specific-release-xcconfig-file"/>

	<xsl:variable name="myxcconfigfile">
		<xsl:choose>
			<xsl:when test="string-length($xcconfigfile) > 0"><xsl:value-of select="$xcconfigfile"/></xsl:when>
			<xsl:otherwise><xsl:value-of select="concat($lname, 'Plugin.xcconfig')"/></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>

	<xsl:variable name="mydebugxcconfigfile">
		<xsl:choose>
			<xsl:when test="string-length($debugxcconfigfile) > 0"><xsl:value-of select="$debugxcconfigfile"/></xsl:when>
			<xsl:otherwise><xsl:value-of select="concat($lname, 'Plugin_debug.xcconfig')"/></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>

	<xsl:variable name="myreleasexcconfigfile">
		<xsl:choose>
			<xsl:when test="string-length($releasexcconfigfile) > 0"><xsl:value-of select="$releasexcconfigfile"/></xsl:when>
			<xsl:otherwise><xsl:value-of select="concat($lname, 'Plugin_release.xcconfig')"/></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
<xsl:template match="pbx-file" name="pbx-file">
// !$*UTF8*$!
{
	archiveVersion = 1;
	classes = {
	};
	objectVersion = 46;
	objects = {

/* Begin PBXBuildFile section */
		<xsl:for-each select="/code/*[@impl-name]">
		<xsl:call-template name="add-PBXBuildFile">
		<xsl:with-param name="implnumber" select="position()"/>
		</xsl:call-template>
		</xsl:for-each>	
		F957085215C90B3B00C95573 /* <xsl:value-of select="$sname"/>.fr in Sources */ = {isa = PBXBuildFile; fileRef = 4B05EED108840E9500D809E1 /* <xsl:value-of select="$sname"/>.fr */; };
		F957085415C90B3B00C95573 /* <xsl:value-of select="$sname"/>NoStrip.cpp in Sources */ = {isa = PBXBuildFile; fileRef = 4B05EECD08840E9300D809E1 /* <xsl:value-of select="$sname"/>NoStrip.cpp */; };
		F957085515C90B3B00C95573 /* <xsl:value-of select="$sname"/>ID.cpp in Sources */ = {isa = PBXBuildFile; fileRef = 4B05EECE08840E9400D809E1 /* <xsl:value-of select="$sname"/>ID.cpp */; };
		F957085815C90B3B00C95573 /* SDKPlugInEntrypoint.cpp in Sources */ = {isa = PBXBuildFile; fileRef = 4B05EECC08840E9200D809E1 /* SDKPlugInEntrypoint.cpp */; };
		F957086415C90B3E00C95573 /* <xsl:value-of select="$sname"/>.fr in Sources */ = {isa = PBXBuildFile; fileRef = 4B05EED108840E9500D809E1 /* <xsl:value-of select="$sname"/>.fr */; };
		F957086615C90B3E00C95573 /* <xsl:value-of select="$sname"/>NoStrip.cpp in Sources */ = {isa = PBXBuildFile; fileRef = 4B05EECD08840E9300D809E1 /* <xsl:value-of select="$sname"/>NoStrip.cpp */; };
		F957086715C90B3E00C95573 /* <xsl:value-of select="$sname"/>ID.cpp in Sources */ = {isa = PBXBuildFile; fileRef = 4B05EECE08840E9400D809E1 /* <xsl:value-of select="$sname"/>ID.cpp */; };
		F957086A15C90B3E00C95573 /* SDKPlugInEntrypoint.cpp in Sources */ = {isa = PBXBuildFile; fileRef = 4B05EECC08840E9200D809E1 /* SDKPlugInEntrypoint.cpp */; };
		F957087415C90B5100C95573 /* <xsl:value-of select="$indesignframework"/>.framework in Frameworks */ = {isa = PBXBuildFile; fileRef = F957084D15C90B2D00C95573 /* InDesignModelAndUI.framework */; };
		F957087515C90B5100C95573 /* libPublicPlugIn.a in Frameworks */ = {isa = PBXBuildFile; fileRef = F957084E15C90B2D00C95573 /* libPublicPlugIn.a */; };
		F957087615C90B5D00C95573 /* <xsl:value-of select="$indesignframework"/>.framework in Frameworks */ = {isa = PBXBuildFile; fileRef = F957084B15C90B2D00C95573 /* InDesignModelAndUI.framework */; };
		F957087715C90B5D00C95573 /* libPublicPlugIn.a in Frameworks */ = {isa = PBXBuildFile; fileRef = F957084C15C90B2D00C95573 /* libPublicPlugIn.a */; };
/* End PBXBuildFile section */

/* Begin PBXBuildRule section */
		F957085D15C90B3B00C95573 /* PBXBuildRule */ = {
			isa = PBXBuildRule;
			compilerSpec = com.apple.compilers.proxy.script;
			filePatterns = "*.fr";
			fileType = pattern.proxy;
			isEditable = 1;
			outputFiles = (
				"$(REZ_COLLECTOR_DIR)/$(INPUT_FILE_NAME).rsrc",
			);
			script = "$ID_SDK_ROOT/devtools/bin/odfrc-cmd -d DEBUG $ODFRC_ADDITIONAL_FLAGS -o \"$REZ_COLLECTOR_DIR/$INPUT_FILE_NAME.rsrc\" \"$INPUT_FILE_PATH\"";
		};
		F957086F15C90B3E00C95573 /* PBXBuildRule */ = {
			isa = PBXBuildRule;
			compilerSpec = com.apple.compilers.proxy.script;
			filePatterns = "*.fr";
			fileType = pattern.proxy;
			isEditable = 1;
			outputFiles = (
				"$(REZ_COLLECTOR_DIR)/$(INPUT_FILE_NAME).rsrc",
			);
			script = "$ID_SDK_ROOT/devtools/bin/odfrc-cmd -d RELEASE $ODFRC_ADDITIONAL_FLAGS -o \"$REZ_COLLECTOR_DIR/$INPUT_FILE_NAME.rsrc\" \"$INPUT_FILE_PATH\"";
		};
/* End PBXBuildRule section */

/* Begin PBXFileReference section */
		<xsl:for-each select="/code/*[@impl-name]">
		<xsl:call-template name="add-PBXFileReference">
		<xsl:with-param name="implnumber" select="position()"/>
		</xsl:call-template>
		</xsl:for-each>
		4B05EECC08840E9200D809E1 /* SDKPlugInEntrypoint.cpp */ = {isa = PBXFileReference; lastKnownFileType = sourcecode.cpp.cpp; name = SDKPlugInEntrypoint.cpp; path = $ID_SDK_ROOT/source/sdksamples/common/SDKPlugInEntrypoint.cpp; sourceTree = SOURCE_ROOT; };
		4B05EECD08840E9300D809E1 /* <xsl:value-of select="$sname"/>NoStrip.cpp */ = {isa = PBXFileReference; lastKnownFileType = sourcecode.cpp.cpp; name = <xsl:value-of select="$sname"/>NoStrip.cpp; path = <xsl:value-of select="$iddir"/>/<xsl:value-of select="$sname"/>NoStrip.cpp; sourceTree = SOURCE_ROOT; };
		4B05EECE08840E9400D809E1 /* <xsl:value-of select="$sname"/>ID.cpp */ = {isa = PBXFileReference; lastKnownFileType = sourcecode.cpp.cpp; name = <xsl:value-of select="$sname"/>ID.cpp; path = <xsl:value-of select="$iddir"/>/<xsl:value-of select="$sname"/>ID.cpp; sourceTree = SOURCE_ROOT; };
		4B05EECF08840E9400D809E1 /* <xsl:value-of select="$sname"/>ID.h */ = {isa = PBXFileReference; lastKnownFileType = sourcecode.c.h; name = <xsl:value-of select="$sname"/>ID.h; path = <xsl:value-of select="$iddir"/>/<xsl:value-of select="$sname"/>ID.h; sourceTree = SOURCE_ROOT; };
		4B05EED108840E9500D809E1 /* <xsl:value-of select="$sname"/>.fr */ = {isa = PBXFileReference; lastKnownFileType = text; name = <xsl:value-of select="$sname"/>.fr; path = <xsl:value-of select="$iddir"/>/<xsl:value-of select="$sname"/>.fr; sourceTree = SOURCE_ROOT; };
		77355572120250EF00E6FC19 /* Info.plist */ = {isa = PBXFileReference; fileEncoding = 4; lastKnownFileType = text.plist.xml; name = Info.plist; path = $ID_SDK_ROOT/source/sdksamples/common/Info.plist; sourceTree = SOURCE_ROOT; };
		77D687F1113861B500D56A9C /* _shared_build_settings/cocoa_ui_debug.xcconfig */ = {isa = PBXFileReference; fileEncoding = 4; lastKnownFileType = text.xcconfig; path = _shared_build_settings/cocoa_ui_debug.xcconfig; sourceTree = "&lt;group&gt;"; };
		77D687F2113861B500D56A9C /* _shared_build_settings/cocoa_ui_release.xcconfig */ = {isa = PBXFileReference; fileEncoding = 4; lastKnownFileType = text.xcconfig; path = _shared_build_settings/cocoa_ui_release.xcconfig; sourceTree = "&lt;group&gt;"; };
		77D687F3113861B500D56A9C /* <xsl:value-of select="$mydebugxcconfigfile"/> */ = {isa = PBXFileReference; fileEncoding = 4; lastKnownFileType = text.xcconfig; path = <xsl:value-of select="$mydebugxcconfigfile"/>; sourceTree = "&lt;group&gt;"; };
		77D687F4113861B500D56A9C /* <xsl:value-of select="$myreleasexcconfigfile"/> */ = {isa = PBXFileReference; fileEncoding = 4; lastKnownFileType = text.xcconfig; path = <xsl:value-of select="$myreleasexcconfigfile"/>; sourceTree = "&lt;group&gt;"; };
		7FE5845808AD6DB8007DB654 /* _shared_build_settings/common_release.xcconfig */ = {isa = PBXFileReference; fileEncoding = 30; lastKnownFileType = text.xcconfig; path = _shared_build_settings/common_release.xcconfig; sourceTree = SOURCE_ROOT; };
		7FE5845908AD6DB8007DB654 /* _shared_build_settings/common_debug.xcconfig */ = {isa = PBXFileReference; fileEncoding = 30; lastKnownFileType = text.xcconfig; path = _shared_build_settings/common_debug.xcconfig; sourceTree = SOURCE_ROOT; };
		7FE5845A08AD6DB8007DB654 /* <xsl:value-of select="$myxcconfigfile"/> */ = {isa = PBXFileReference; fileEncoding = 30; lastKnownFileType = text.xcconfig; path = <xsl:value-of select="$myxcconfigfile"/>; sourceTree = SOURCE_ROOT; };
		F957084B15C90B2D00C95573 /* <xsl:value-of select="$indesignframework"/>.framework */ = {isa = PBXFileReference; lastKnownFileType = wrapper.framework; name = <xsl:value-of select="$indesignframework"/>.framework; path = <xsl:value-of select="$sdkdir"/>/build/mac/debug_cocoa64/packagefolder/contents/macos/<xsl:value-of select="$indesignframework"/>.framework; sourceTree = SOURCE_ROOT; };
		F957084C15C90B2D00C95573 /* libPublicPlugIn.a */ = {isa = PBXFileReference; lastKnownFileType = archive.ar; name = libPublicPlugIn.a; path = ../debug_cocoa64/packagefolder/contents/macos/libs/libPublicPlugIn.a; sourceTree = SOURCE_ROOT; };
		F957084D15C90B2D00C95573 /* <xsl:value-of select="$indesignframework"/>.framework */ = {isa = PBXFileReference; lastKnownFileType = wrapper.framework; name = <xsl:value-of select="$indesignframework"/>.framework; path = <xsl:value-of select="$sdkdir"/>/build/mac/release_cocoa64/packagefolder/contents/macos/<xsl:value-of select="$indesignframework"/>.framework; sourceTree = SOURCE_ROOT; };
		F957084E15C90B2D00C95573 /* libPublicPlugIn.a */ = {isa = PBXFileReference; lastKnownFileType = archive.ar; name = libPublicPlugIn.a; path = ../release_cocoa64/packagefolder/contents/macos/libs/libPublicPlugIn.a; sourceTree = SOURCE_ROOT; };
		F957086015C90B3B00C95573 /* <xsl:value-of select="$lname"/>.InDesignPlugin */ = {isa = PBXFileReference; explicitFileType = wrapper.framework; includeInIndex = 0; path = <xsl:value-of select="$lname"/>.InDesignPlugin; sourceTree = BUILT_PRODUCTS_DIR; };
		F957087215C90B3E00C95573 /* <xsl:value-of select="$lname"/>.InDesignPlugin */ = {isa = PBXFileReference; explicitFileType = wrapper.framework; includeInIndex = 0; path = <xsl:value-of select="$lname"/>.InDesignPlugin; sourceTree = BUILT_PRODUCTS_DIR; };
/* End PBXFileReference section */

/* Begin PBXFrameworksBuildPhase section */
		F957085915C90B3B00C95573 /* Frameworks */ = {
			isa = PBXFrameworksBuildPhase;
			buildActionMask = 2147483647;
			files = (
				F957087615C90B5D00C95573 /* <xsl:value-of select="$indesignframework"/>.framework in Frameworks */,
				F957087715C90B5D00C95573 /* libPublicPlugIn.a in Frameworks */,
			);
			runOnlyForDeploymentPostprocessing = 0;
		};
		F957086B15C90B3E00C95573 /* Frameworks */ = {
			isa = PBXFrameworksBuildPhase;
			buildActionMask = 2147483647;
			files = (
				F957087415C90B5100C95573 /* <xsl:value-of select="$indesignframework"/>.framework in Frameworks */,
				F957087515C90B5100C95573 /* libPublicPlugIn.a in Frameworks */,
			);
			runOnlyForDeploymentPostprocessing = 0;
		};
/* End PBXFrameworksBuildPhase section */

/* Begin PBXGroup section */
		4B05EEAD08840E8D00D809E1 = {
			isa = PBXGroup;
			children = (
				4B05EEC708840E8D00D809E1 /* Source */,
				4B05EED008840E9400D809E1 /* Resources */,
				7F52248408AFCE1F00139994 /* xcconfig */,
				F957084215C90B2D00C95573 /* InDesign Libraries */,
				4B05EEBB08840E8D00D809E1 /* Products */,
				77355572120250EF00E6FC19 /* Info.plist */,
			);
			sourceTree = "&lt;group&gt;";
		};
		4B05EEBB08840E8D00D809E1 /* Products */ = {
			isa = PBXGroup;
			children = (
				F957086015C90B3B00C95573 /* <xsl:value-of select="$lname"/>.InDesignPlugin */,
				F957087215C90B3E00C95573 /* <xsl:value-of select="$lname"/>.InDesignPlugin */,
			);
			name = Products;
			sourceTree = "&lt;group&gt;";
		};
		4B05EEC708840E8D00D809E1 /* Source */ = {
			isa = PBXGroup;
			children = (
				<xsl:for-each select="/code/*[@impl-name]">
				<xsl:call-template name="add-PBXGroup">
				<xsl:with-param name="implnumber" select="position()"/>
				</xsl:call-template>
				</xsl:for-each>
				4B05EECB08840E9100D809E1 /* Plugin */,
			);
			name = Source;
			sourceTree = "&lt;group&gt;";
		};
		4B05EECB08840E9100D809E1 /* Plugin */ = {
			isa = PBXGroup;
			children = (
				4B05EECC08840E9200D809E1 /* SDKPlugInEntrypoint.cpp */,
				4B05EECD08840E9300D809E1 /* <xsl:value-of select="$sname"/>NoStrip.cpp */,
				4B05EECF08840E9400D809E1 /* <xsl:value-of select="$sname"/>ID.h */,
				4B05EECE08840E9400D809E1 /* <xsl:value-of select="$sname"/>ID.cpp */,
			);
			name = Plugin;
			sourceTree = "&lt;group&gt;";
		};
		4B05EED008840E9400D809E1 /* Resources */ = {
			isa = PBXGroup;
			children = (
				4B05EED108840E9500D809E1 /* <xsl:value-of select="$sname"/>.fr */,
			);
			name = Resources;
			sourceTree = "&lt;group&gt;";
		};
		7F52248408AFCE1F00139994 /* xcconfig */ = {
			isa = PBXGroup;
			children = (
				7FE5845808AD6DB8007DB654 /* _shared_build_settings/common_release.xcconfig */,
				7FE5845908AD6DB8007DB654 /* _shared_build_settings/common_debug.xcconfig */,
				7FE5845A08AD6DB8007DB654 /* <xsl:value-of select="$myxcconfigfile"/> */,
				77D687F1113861B500D56A9C /* _shared_build_settings/cocoa_ui_debug.xcconfig */,
				77D687F2113861B500D56A9C /* _shared_build_settings/cocoa_ui_release.xcconfig */,
				77D687F3113861B500D56A9C /* <xsl:value-of select="$mydebugxcconfigfile"/> */,
				77D687F4113861B500D56A9C /* <xsl:value-of select="$myreleasexcconfigfile"/> */,
			);
			name = xcconfig;
			sourceTree = "&lt;group&gt;";
		};
		F957084215C90B2D00C95573 /* InDesign Libraries */ = {
			isa = PBXGroup;
			children = (
				F957084915C90B2D00C95573 /* For Cocoa64 */,
			);
			name = "InDesign Libraries";
			sourceTree = "&lt;group&gt;";
		};
		F957084915C90B2D00C95573 /* For Cocoa64 */ = {
			isa = PBXGroup;
			children = (
				F957084D15C90B2D00C95573 /* <xsl:value-of select="$indesignframework"/>.framework */,
				F957084E15C90B2D00C95573 /* libPublicPlugIn.a */,
				F957084A15C90B2D00C95573 /* Debug */,
			);
			name = "For Cocoa64";
			sourceTree = "&lt;group&gt;";
		};
		F957084A15C90B2D00C95573 /* Debug */ = {
			isa = PBXGroup;
			children = (
				F957084B15C90B2D00C95573 /* <xsl:value-of select="$indesignframework"/>.framework */,
				F957084C15C90B2D00C95573 /* libPublicPlugIn.a */,
			);
			name = Debug;
			sourceTree = "&lt;group&gt;";
		};
/* End PBXGroup section */

/* Begin PBXNativeTarget section */
		F957085015C90B3B00C95573 /* Debug_Cocoa64 */ = {
			isa = PBXNativeTarget;
			buildConfigurationList = F957085E15C90B3B00C95573 /* Build configuration list for PBXNativeTarget "Debug_Cocoa64" */;
			buildPhases = (
				F957085115C90B3B00C95573 /* Sources */,
				F957085915C90B3B00C95573 /* Frameworks */,
				F957085A15C90B3B00C95573 /* Rez */,
				F957085B15C90B3B00C95573 /* Resources */,
				F957085C15C90B3B00C95573 /* ShellScript */,
			);
			buildRules = (
				F957085D15C90B3B00C95573 /* PBXBuildRule */,
			);
			dependencies = (
			);
			name = Debug_Cocoa64;
			productName = Debug;
			productReference = F957086015C90B3B00C95573 /* <xsl:value-of select="$lname"/>.InDesignPlugin */;
			productType = "com.apple.product-type.framework";
		};
		F957086215C90B3E00C95573 /* Release_Cocoa64 */ = {
			isa = PBXNativeTarget;
			buildConfigurationList = F957087015C90B3E00C95573 /* Build configuration list for PBXNativeTarget "Release_Cocoa64" */;
			buildPhases = (
				F957086315C90B3E00C95573 /* Sources */,
				F957086B15C90B3E00C95573 /* Frameworks */,
				F957086C15C90B3E00C95573 /* Rez */,
				F957086D15C90B3E00C95573 /* Resources */,
				F957086E15C90B3E00C95573 /* ShellScript */,
			);
			buildRules = (
				F957086F15C90B3E00C95573 /* PBXBuildRule */,
			);
			dependencies = (
			);
			name = Release_Cocoa64;
			productName = Release;
			productReference = F957087215C90B3E00C95573 /* <xsl:value-of select="$lname"/>.InDesignPlugin */;
			productType = "com.apple.product-type.framework";
		};
/* End PBXNativeTarget section */

/* Begin PBXProject section */
		4B05EEAF08840E8D00D809E1 /* Project object */ = {
			isa = PBXProject;
			buildConfigurationList = 4B05EEB008840E8D00D809E1 /* Build configuration list for PBXProject "<xsl:value-of select="$lname"/>" */;
			compatibilityVersion = "Xcode 3.2";
			developmentRegion = English;
			hasScannedForEncodings = 0;
			knownRegions = (
				English,
				Japanese,
				French,
				German,
			);
			mainGroup = 4B05EEAD08840E8D00D809E1;
			productRefGroup = 4B05EEBB08840E8D00D809E1 /* Products */;
			projectDirPath = "";
			projectRoot = "";
			targets = (
				F957085015C90B3B00C95573 /* Debug_Cocoa64 */,
				F957086215C90B3E00C95573 /* Release_Cocoa64 */,
			);
		};
/* End PBXProject section */

/* Begin PBXResourcesBuildPhase section */
		F957085B15C90B3B00C95573 /* Resources */ = {
			isa = PBXResourcesBuildPhase;
			buildActionMask = 2147483647;
			files = (
			);
			runOnlyForDeploymentPostprocessing = 0;
		};
		F957086D15C90B3E00C95573 /* Resources */ = {
			isa = PBXResourcesBuildPhase;
			buildActionMask = 2147483647;
			files = (
			);
			runOnlyForDeploymentPostprocessing = 0;
		};
/* End PBXResourcesBuildPhase section */

/* Begin PBXRezBuildPhase section */
		F957085A15C90B3B00C95573 /* Rez */ = {
			isa = PBXRezBuildPhase;
			buildActionMask = 2147483647;
			files = (
			);
			runOnlyForDeploymentPostprocessing = 0;
		};
		F957086C15C90B3E00C95573 /* Rez */ = {
			isa = PBXRezBuildPhase;
			buildActionMask = 2147483647;
			files = (
			);
			runOnlyForDeploymentPostprocessing = 0;
		};
/* End PBXRezBuildPhase section */

/* Begin PBXShellScriptBuildPhase section */
		F957085C15C90B3B00C95573 /* ShellScript */ = {
			isa = PBXShellScriptBuildPhase;
			buildActionMask = 2147483647;
			files = (
			);
			inputPaths = (
			);
			outputPaths = (
			);
			runOnlyForDeploymentPostprocessing = 0;
			shellPath = /bin/sh;
			shellScript = $ID_SDK_ROOT/build/mac/packagescripts/copyResources.sh;
			showEnvVarsInLog = 0;
		};
		F957086E15C90B3E00C95573 /* ShellScript */ = {
			isa = PBXShellScriptBuildPhase;
			buildActionMask = 2147483647;
			files = (
			);
			inputPaths = (
			);
			outputPaths = (
			);
			runOnlyForDeploymentPostprocessing = 0;
			shellPath = /bin/sh;
			shellScript = $ID_SDK_ROOT/build/mac/packagescripts/copyResources.sh;
			showEnvVarsInLog = 0;
		};
/* End PBXShellScriptBuildPhase section */

/* Begin PBXSourcesBuildPhase section */
		F957085115C90B3B00C95573 /* Sources */ = {
			isa = PBXSourcesBuildPhase;
			buildActionMask = 2147483647;
			files = (
				<xsl:for-each select="/code/*[@impl-name]">
				<xsl:call-template name="add-PBXSourcesBuildPhase">
				<xsl:with-param name="implnumber" select="position()"/>
				<xsl:with-param name="idadjustment" select="0"/>
				</xsl:call-template>
				</xsl:for-each>	
				F957085215C90B3B00C95573 /* <xsl:value-of select="$sname"/>.fr in Sources */,
				F957085415C90B3B00C95573 /* <xsl:value-of select="$sname"/>NoStrip.cpp in Sources */,
				F957085515C90B3B00C95573 /* <xsl:value-of select="$sname"/>ID.cpp in Sources */,
				F957085815C90B3B00C95573 /* SDKPlugInEntrypoint.cpp in Sources */,
			);
			runOnlyForDeploymentPostprocessing = 0;
		};
		F957086315C90B3E00C95573 /* Sources */ = {
			isa = PBXSourcesBuildPhase;
			buildActionMask = 2147483647;
			files = (
				<xsl:for-each select="/code/*[@impl-name]">
				<xsl:call-template name="add-PBXSourcesBuildPhase">
				<xsl:with-param name="implnumber" select="position()"/>
				<xsl:with-param name="idadjustment" select="1"/>
				</xsl:call-template>
				</xsl:for-each>	
				F957086415C90B3E00C95573 /* <xsl:value-of select="$sname"/>.fr in Sources */,
				F957086615C90B3E00C95573 /* <xsl:value-of select="$sname"/>NoStrip.cpp in Sources */,
				F957086715C90B3E00C95573 /* <xsl:value-of select="$sname"/>ID.cpp in Sources */,
				F957086A15C90B3E00C95573 /* SDKPlugInEntrypoint.cpp in Sources */,
			);
			runOnlyForDeploymentPostprocessing = 0;
		};
/* End PBXSourcesBuildPhase section */

/* Begin XCBuildConfiguration section */
		4B05EEB108840E8D00D809E1 /* Default */ = {
			isa = XCBuildConfiguration;
			baseConfigurationReference = 7FE5845A08AD6DB8007DB654 /* <xsl:value-of select="$myxcconfigfile"/> */;
			buildSettings = {
				BUILT_PRODUCTS_DIR = "$(ID_BUILT_SDK_SAMPLES_DIR)";
				GCC_WARN_UNUSED_PARAMETER = YES;
				HEADER_SEARCH_PATHS = (
					"$(HEADER_SEARCH_PATHS)",
					$ID_SDK_ROOT/source/public/interfaces/tables,					
					<xsl:if test="not(contains(string(/code/@plugin-type),'InDesignServerProduct'))">$ID_SDK_ROOT/source/public/components/widgetbin/includes,</xsl:if>    
					$ID_SDK_ROOT/source/public/interfaces/workgroup,
					$ID_SDK_ROOT/source/public/interfaces/interactive,
					$ID_SDK_ROOT/source/public/interfaces/interactive/ui,
					$ID_SDK_ROOT/source/public/interfaces/colormgmt,
					$ID_SDK_ROOT/source/public/interfaces/incopy,
					$ID_SDK_ROOT/source/public/interfaces/cjk,
                    $ID_SDK_ROOT/source/public/interfaces/preflight,
					$ID_SDK_ROOT/source/public/facades/graphics,
					$ID_SDK_ROOT/source/public/facades/text,
					$ID_SDK_ROOT/source/public/facades/layout,
					$ID_SDK_ROOT/source/public/components/publiclib/plugins,
					$ID_SDK_ROOT/source/public/components/publiclib/files,
					$ID_SDK_ROOT/source/public/components/publiclib/objectmodel,
					$ID_SDK_ROOT/source/sdksamples/common,
					$ID_SDK_ROOT/external/afl/includes,
					<xsl:value-of select="$iddir-escaped"/>,
				);
				INFOPLIST_FILE = $ID_SDK_ROOT/source/sdksamples/common/Info.plist;
				INFOPLIST_PREPROCESS = YES;
				PLC_OUTPUT_TYPE = InDa;
				PRODUCT_NAME = <xsl:value-of select="$lname"/>;
			};
			name = Default;
		};
		F957085F15C90B3B00C95573 /* Default */ = {
			isa = XCBuildConfiguration;
			baseConfigurationReference = 77D687F3113861B500D56A9C /* <xsl:value-of select="$mydebugxcconfigfile"/> */;
			buildSettings = {
				PLC_GENERATE_PKGINFO_FILE = "$(inherited)";
			};
			name = Default;
		};
		F957087115C90B3E00C95573 /* Default */ = {
			isa = XCBuildConfiguration;
			baseConfigurationReference = 77D687F4113861B500D56A9C /* <xsl:value-of select="$myreleasexcconfigfile"/> */;
			buildSettings = {
			};
			name = Default;
		};
/* End XCBuildConfiguration section */

/* Begin XCConfigurationList section */
		4B05EEB008840E8D00D809E1 /* Build configuration list for PBXProject "<xsl:value-of select="$lname"/>" */ = {
			isa = XCConfigurationList;
			buildConfigurations = (
				4B05EEB108840E8D00D809E1 /* Default */,
			);
			defaultConfigurationIsVisible = 1;
			defaultConfigurationName = Default;
		};
		F957085E15C90B3B00C95573 /* Build configuration list for PBXNativeTarget "Debug_Cocoa64" */ = {
			isa = XCConfigurationList;
			buildConfigurations = (
				F957085F15C90B3B00C95573 /* Default */,
			);
			defaultConfigurationIsVisible = 0;
			defaultConfigurationName = Default;
		};
		F957087015C90B3E00C95573 /* Build configuration list for PBXNativeTarget "Release_Cocoa64" */ = {
			isa = XCConfigurationList;
			buildConfigurations = (
				F957087115C90B3E00C95573 /* Default */,
			);
			defaultConfigurationIsVisible = 0;
			defaultConfigurationName = Default;
		};
/* End XCConfigurationList section */
	};
	rootObject = 4B05EEAF08840E8D00D809E1 /* Project object */;
}
</xsl:template>

<!-- These are tabbed over for output formatting --> 

		<xsl:template name="add-PBXBuildFile"> 
		<xsl:param name="implnumber"/>
		<xsl:variable name="hexID1"><xsl:call-template name="convert-to-12char-hex"><xsl:with-param name="decimal" select="2 * $implnumber - 1"/></xsl:call-template></xsl:variable>
		<xsl:variable name="hexID2"><xsl:call-template name="convert-to-12char-hex"><xsl:with-param name="decimal" select="2 * $implnumber"/></xsl:call-template></xsl:variable>
		<xsl:variable name="hexIDRef"><xsl:call-template name="convert-to-12char-hex"><xsl:with-param name="decimal" select="65536 -$implnumber"/></xsl:call-template></xsl:variable>
		<xsl:value-of select="$hexID1"/> /* <xsl:value-of select="@impl-name"/>.cpp */ = {isa = PBXBuildFile; fileRef = <xsl:value-of select="$hexIDRef"/> /* <xsl:value-of select="@impl-name"/>.cpp */; };
		<xsl:value-of select="$hexID2"/> /* <xsl:value-of select="@impl-name"/>.cpp */ = {isa = PBXBuildFile; fileRef = <xsl:value-of select="$hexIDRef"/> /* <xsl:value-of select="@impl-name"/>.cpp */; };	
		</xsl:template>


		<xsl:template name="add-PBXSourcesBuildPhase"> 
		<xsl:param name="implnumber"/>
		<xsl:param name="idadjustment"/>
		<xsl:variable name="hexID"><xsl:call-template name="convert-to-12char-hex"><xsl:with-param name="decimal" select="2 * $implnumber - $idadjustment"/></xsl:call-template></xsl:variable>
		<xsl:value-of select="$hexID"/> /* <xsl:value-of select="@impl-name"/>.cpp in Sources*/,
		</xsl:template>


		<xsl:template name="add-PBXFileReference"> 
		<xsl:param name="implnumber"/>
		<xsl:variable name="hexIDRef"><xsl:call-template name="convert-to-12char-hex"><xsl:with-param name="decimal" select="65536 -$implnumber"/></xsl:call-template></xsl:variable>
		<xsl:value-of select="$hexIDRef"/> /* <xsl:value-of select="@impl-name"/>.cpp */ = {isa = PBXFileReference; lastKnownFileType = sourcecode.cpp.cpp; name = <xsl:value-of select="@impl-name"/>.cpp; path = "<xsl:value-of select="$sourcedir"/>/<xsl:value-of select="@impl-name"/>.cpp"; sourceTree = <xsl:choose><xsl:when test="starts-with($sourcedir, '/')">"&lt;absolute&gt;"</xsl:when><xsl:otherwise>SOURCE_ROOT</xsl:otherwise></xsl:choose>; };
		</xsl:template>

				<xsl:template name="add-PBXGroup"> 
				<xsl:param name="implnumber"/>
				<xsl:variable name="hexIDRef"><xsl:call-template name="convert-to-12char-hex"><xsl:with-param name="decimal" select="65536 -$implnumber"/></xsl:call-template></xsl:variable>
				<xsl:value-of select="$hexIDRef"/> /* <xsl:value-of select="@impl-name"/>.cpp */,		
				</xsl:template>

<!-- The templates used to convert a decimal number to a 12 character hex string--> 
<xsl:template name="convert-to-12char-hex">
   <xsl:param name="decimal" />
   	<xsl:variable name="hexNumber">
		<xsl:call-template name="convert-to-hex">
         	<xsl:with-param name="decimal" select="$decimal" />
      		</xsl:call-template>	
	</xsl:variable>
	
	<xsl:call-template name="add-leading-zeros">
   	<xsl:with-param name="hexNumber" select="$hexNumber" />
   	</xsl:call-template>
   
</xsl:template>


<xsl:variable name="hexDigits" select="'0123456789ABCDEF'" />
<xsl:template name="convert-to-hex">
   <xsl:param name="decimal" />
   <xsl:if test="$decimal > 16">
      <xsl:call-template name="convert-to-hex">
         <xsl:with-param name="decimal"
                         select="floor($decimal div 16)" />
      </xsl:call-template>
   </xsl:if>

   <xsl:value-of select="substring($hexDigits, ($decimal mod 16) + 1, 1)" />
</xsl:template>

<!-- This is used to add leading zeros to a hex number --> 
<xsl:template name="add-leading-zeros">
<xsl:param name="hexNumber" />
<xsl:choose>
	<xsl:when test="string-length($hexNumber) &lt;  24">
		<xsl:call-template name="add-leading-zeros">
		<xsl:with-param name="hexNumber" select="concat( '0', $hexNumber)" />
		</xsl:call-template>
	</xsl:when>
	<xsl:otherwise>
		<xsl:value-of select="$hexNumber" />
	</xsl:otherwise>
</xsl:choose>
</xsl:template>

</xsl:stylesheet>