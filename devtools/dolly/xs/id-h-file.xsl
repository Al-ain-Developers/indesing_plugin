<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
<xsl:import href="global-variables.xsl"/>
<xsl:import href="standard-adobe-header.xsl"/>
<xsl:import href="standard-footer.xsl"/>

<xsl:output name="cppfile" method="text"/>
<xsl:template match="id-h-file">
Generating ID.h file from template...
 <xsl:document href="{/code/@id-header-dir-absolute}{$filesep}{/code/@short-name}ID.h" format="cppfile">
<xsl:call-template name="standard-adobe-header">
<xsl:with-param name="suppress-normal-include" select="1"/>
</xsl:call-template>
<xsl:call-template name="id-h"/>
<xsl:call-template name="standard-footer"/>
</xsl:document>
</xsl:template>

<xsl:template match="id-h" name="id-h">
<xsl:variable name="sname" select="/code/@short-name"/>
<xsl:variable name="uppersname" select="translate($sname, 'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>

#ifndef __<xsl:value-of select="/code/@short-name"/>ID_h__
#define __<xsl:value-of select="/code/@short-name"/>ID_h__

#include "SDKDef.h"

// Company:
#define k<xsl:value-of select="/code/@short-name"/>CompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define k<xsl:value-of select="/code/@short-name"/>CompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define k<xsl:value-of select="/code/@short-name"/>PluginName	"<xsl:value-of select='/code/@long-name'/>"			// Name of this plug-in.
#define k<xsl:value-of select="/code/@short-name"/>PrefixNumber	<xsl:value-of select="/code/@prefix-id"/> 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define k<xsl:value-of select="/code/@short-name"/>Version		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define k<xsl:value-of select="/code/@short-name"/>Author		"<xsl:value-of select="/code/@author"/>"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change k<xsl:value-of select="/code/@short-name"/>PrefixNumber above to modify the prefix.)
#define k<xsl:value-of select="/code/@short-name"/>Prefix		RezLong(k<xsl:value-of select="/code/@short-name"/>PrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define k<xsl:value-of select="/code/@short-name"/>StringPrefix	SDK_DEF_STRINGIZE(k<xsl:value-of select="/code/@short-name"/>PrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// Missing plug-in: (see ExtraPluginInfo resource)
#define k<xsl:value-of select="/code/@short-name"/>MissingPluginURLValue		kSDKDefPartnersStandardValue_enUS // URL displayed in Missing Plug-in dialog
#define k<xsl:value-of select="/code/@short-name"/>MissingPluginAlertValue	kSDKDefMissingPluginAlertValue // Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem

// PluginID:
DECLARE_PMID(kPlugInIDSpace, k<xsl:value-of select="/code/@short-name"/>PluginID, k<xsl:value-of select="/code/@short-name"/>Prefix + 0)

// ClassIDs:
<xsl:if test="/code/generate-menu">DECLARE_PMID(kClassIDSpace, k<xsl:value-of select="/code/@short-name"/>ActionComponentBoss, k<xsl:value-of select="/code/@short-name"/>Prefix + 0)
</xsl:if>
<xsl:if test="/code/generate-panel">DECLARE_PMID(kClassIDSpace, k<xsl:value-of select="/code/@short-name"/>PanelWidgetBoss, k<xsl:value-of select="/code/@short-name"/>Prefix + 1)
</xsl:if>
<xsl:if test="/code/generate-dialog">DECLARE_PMID(kClassIDSpace, k<xsl:value-of select="/code/@short-name"/>DialogBoss, k<xsl:value-of select="/code/@short-name"/>Prefix + 2)
</xsl:if>
<xsl:for-each select="/code/boss-item">DECLARE_PMID(kClassIDSpace, <xsl:value-of select="@boss-id"/>, k<xsl:value-of select="/code/@short-name"/>Prefix + <xsl:value-of select="position() + 2"/>)
</xsl:for-each>	
<xsl:call-template name="cascade-pmiids">
	<xsl:with-param name="idspace" select="'kClassIDSpace'"/>
	<xsl:with-param name="iddefaultname" select="concat('k', $sname, 'Boss')"/>
	<xsl:with-param name="idprefix" select="concat('k', $sname, 'Prefix')"/>
	<xsl:with-param name="idnumber" select="count(/code/boss-item) + 3"/>
</xsl:call-template>

// InterfaceIDs:
<xsl:for-each select="/code/interface-item">DECLARE_PMID(kInterfaceIDSpace, <xsl:value-of select="@interface-id"/>, k<xsl:value-of select="/code/@short-name"/>Prefix + <xsl:value-of select="position() - 1"/>)
</xsl:for-each>
<xsl:call-template name="cascade-pmiids">
	<xsl:with-param name="idspace" select="'kInterfaceIDSpace'"/>
	<xsl:with-param name="iddefaultname" select="concat('IID_I', $uppersname, 'INTERFACE')"/>
	<xsl:with-param name="idprefix" select="concat('k', $sname, 'Prefix')"/>
	<xsl:with-param name="idnumber" select="count(/code/interface-item)"/>
</xsl:call-template>

// ImplementationIDs:
<xsl:for-each select="/code/impl-item[@impl-id]">DECLARE_PMID(kImplementationIDSpace, <xsl:value-of select="@impl-id"/>, k<xsl:value-of select="/code/@short-name"/>Prefix + <xsl:value-of select="position()-1"/> )
</xsl:for-each>
<xsl:call-template name="cascade-pmiids">
	<xsl:with-param name="idspace" select="'kImplementationIDSpace'"/>
	<xsl:with-param name="iddefaultname" select="concat('k', $sname, 'Impl')"/>
	<xsl:with-param name="idprefix" select="concat('k', $sname, 'Prefix')"/>
	<xsl:with-param name="idnumber" select="count(/code/impl-item)"/>
</xsl:call-template>

// ActionIDs:
DECLARE_PMID(kActionIDSpace, k<xsl:value-of select="/code/@short-name"/>AboutActionID, k<xsl:value-of select="/code/@short-name"/>Prefix + 0)
<xsl:if test="/code/generate-panel">DECLARE_PMID(kActionIDSpace, k<xsl:value-of select="/code/@short-name"/>PanelWidgetActionID, k<xsl:value-of select="/code/@short-name"/>Prefix + 1)
DECLARE_PMID(kActionIDSpace, k<xsl:value-of select="/code/@short-name"/>Separator1ActionID, k<xsl:value-of select="/code/@short-name"/>Prefix + 2)
DECLARE_PMID(kActionIDSpace, k<xsl:value-of select="/code/@short-name"/>PopupAboutThisActionID, k<xsl:value-of select="/code/@short-name"/>Prefix + 3)</xsl:if>
<xsl:if test="/code/generate-dialog">
DECLARE_PMID(kActionIDSpace, k<xsl:value-of select="/code/@short-name"/>DialogActionID, k<xsl:value-of select="/code/@short-name"/>Prefix + 4)
</xsl:if>
<xsl:for-each select="/code/action-item">DECLARE_PMID(kActionIDSpace, <xsl:value-of select="@action-id"/>, k<xsl:value-of select="/code/@short-name"/>Prefix + <xsl:value-of select="position()+4"/> )
</xsl:for-each>
<xsl:call-template name="cascade-pmiids">
	<xsl:with-param name="idspace" select="'kActionIDSpace'"/>
	<xsl:with-param name="iddefaultname" select="concat('k', $sname, 'ActionID')"/>
	<xsl:with-param name="idprefix" select="concat('k', $sname, 'Prefix')"/>
	<xsl:with-param name="idnumber" select="count(/code/action-item) + 5"/>
</xsl:call-template>

// WidgetIDs:
<xsl:if test="/code/generate-panel">DECLARE_PMID(kWidgetIDSpace, k<xsl:value-of select="/code/@short-name"/>PanelWidgetID, k<xsl:value-of select="/code/@short-name"/>Prefix + 0)
</xsl:if>
<xsl:if test="/code/generate-dialog">DECLARE_PMID(kWidgetIDSpace, k<xsl:value-of select="/code/@short-name"/>DialogWidgetID, k<xsl:value-of select="/code/@short-name"/>Prefix + 1)
</xsl:if>
<xsl:for-each select="/code/widget-item">DECLARE_PMID(kWidgetIDSpace, <xsl:value-of select="@widget-id"/>, k<xsl:value-of select="/code/@short-name"/>Prefix + <xsl:value-of select="position()+1"/> )
</xsl:for-each>
<xsl:call-template name="cascade-pmiids">
	<xsl:with-param name="idspace" select="'kWidgetIDSpace'"/>
	<xsl:with-param name="iddefaultname" select="concat('k', $sname, 'WidgetID')"/>
	<xsl:with-param name="idprefix" select="concat('k', $sname, 'Prefix')"/>
	<xsl:with-param name="idnumber" select="count(/code/widget-item) + 2"/>
</xsl:call-template>

<xsl:if test="/code/generate-scriptprovider">
//Script Element IDs

DECLARE_PMID(kScriptInfoIDSpace, k<xsl:value-of select="/code/@short-name"/>MethodScriptElement, k<xsl:value-of select="/code/@short-name"/>Prefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, k<xsl:value-of select="/code/@short-name"/>PropertyScriptElement, k<xsl:value-of select="/code/@short-name"/>Prefix + 2)
</xsl:if>
<xsl:for-each select="/code/scriptinfo-item">DECLARE_PMID(kScriptInfoIDSpace, <xsl:value-of select="@script-element"/>, k<xsl:value-of select="/code/@short-name"/>Prefix + <xsl:value-of select="position()+2"/>)
</xsl:for-each>

// "About Plug-ins" sub-menu:
#define k<xsl:value-of select="/code/@short-name"/>AboutMenuKey			k<xsl:value-of select="/code/@short-name"/>StringPrefix "k<xsl:value-of select="/code/@short-name"/>AboutMenuKey"
#define k<xsl:value-of select="/code/@short-name"/>AboutMenuPath		kSDKDefStandardAboutMenuPath k<xsl:value-of select="/code/@short-name"/>CompanyKey

// "Plug-ins" sub-menu:
#define k<xsl:value-of select="/code/@short-name"/>PluginsMenuKey 		k<xsl:value-of select="/code/@short-name"/>StringPrefix "k<xsl:value-of select="/code/@short-name"/>PluginsMenuKey"
#define k<xsl:value-of select="/code/@short-name"/>PluginsMenuPath		kSDKDefPlugInsStandardMenuPath k<xsl:value-of select="/code/@short-name"/>CompanyKey kSDKDefDelimitMenuPath k<xsl:value-of select="/code/@short-name"/>PluginsMenuKey

// Menu item keys:
<xsl:for-each select="/code/menu-item">#define k<xsl:value-of select="/code/@short-name"/><xsl:value-of select="@name"/>MenuItemKey		k<xsl:value-of select="/code/@short-name"/>StringPrefix "k<xsl:value-of select="/code/@short-name"/><xsl:value-of select="@name"/>MenuItemKey"
</xsl:for-each>
// Other StringKeys:
#define k<xsl:value-of select="/code/@short-name"/>AboutBoxStringKey	k<xsl:value-of select="/code/@short-name"/>StringPrefix "k<xsl:value-of select="/code/@short-name"/>AboutBoxStringKey"
<xsl:for-each select="/code/menu-item">#define k<xsl:value-of select="/code/@short-name"/><xsl:value-of select="@name"/>StringKey			k<xsl:value-of select="/code/@short-name"/>StringPrefix "k<xsl:value-of select="/code/@short-name"/><xsl:value-of select="@name"/>StringKey"
</xsl:for-each>
<xsl:if test="/code/generate-panel">#define k<xsl:value-of select="/code/@short-name"/>PanelTitleKey					k<xsl:value-of select="/code/@short-name"/>StringPrefix	"k<xsl:value-of select="/code/@short-name"/>PanelTitleKey"
#define k<xsl:value-of select="/code/@short-name"/>StaticTextKey k<xsl:value-of select="/code/@short-name"/>StringPrefix	"k<xsl:value-of select="/code/@short-name"/>StaticTextKey"
#define k<xsl:value-of select="/code/@short-name"/>InternalPopupMenuNameKey k<xsl:value-of select="/code/@short-name"/>StringPrefix	"k<xsl:value-of select="/code/@short-name"/>InternalPopupMenuNameKey"
#define k<xsl:value-of select="/code/@short-name"/>TargetMenuPath k<xsl:value-of select="/code/@short-name"/>InternalPopupMenuNameKey</xsl:if>

<xsl:if test="not(/code/generate-panel)">#define k<xsl:value-of select="/code/@short-name"/>TargetMenuPath k<xsl:value-of select="/code/@short-name"/>PluginsMenuPath</xsl:if>

<xsl:if test="/code/generate-preflight">
// Rule description key
#define k<xsl:value-of select="/code/@short-name"/>CategoryKey					k<xsl:value-of select="/code/@short-name"/>StringPrefix	"k<xsl:value-of select="/code/@short-name"/>CategoryKey"
#define k<xsl:value-of select="/code/@short-name"/>RuleDescriptionKey					k<xsl:value-of select="/code/@short-name"/>StringPrefix	"k<xsl:value-of select="/code/@short-name"/>RuleDescriptionKey"
#define k<xsl:value-of select="/code/@short-name"/>RuleParameterLabel					k<xsl:value-of select="/code/@short-name"/>StringPrefix	"k<xsl:value-of select="/code/@short-name"/>RuleParameterLabel"
</xsl:if>

// Menu item positions:
<xsl:for-each select="/code/menu-item">
#define k<xsl:value-of select="/code/@short-name"/><xsl:value-of select="@name"/>MenuItemPosition <xsl:value-of select="position()"/>
</xsl:for-each>
<!-- Note we're assuming we have less than 10 menu entries... some UI if we don't have -->
<xsl:if test="/code/generate-panel">
#define	k<xsl:value-of select="/code/@short-name"/>Separator1MenuItemPosition		10.0
#define k<xsl:value-of select="/code/@short-name"/>AboutThisMenuItemPosition		11.0
</xsl:if>
<xsl:if test="/code/generate-dialog">
#define k<xsl:value-of select="/code/@short-name"/>DialogTitleKey k<xsl:value-of select="/code/@short-name"/>StringPrefix "k<xsl:value-of select="/code/@short-name"/>DialogTitleKey"
// "Plug-ins" sub-menu item key for dialog:
#define k<xsl:value-of select="/code/@short-name"/>DialogMenuItemKey k<xsl:value-of select="/code/@short-name"/>StringPrefix "k<xsl:value-of select="/code/@short-name"/>DialogMenuItemKey"
// "Plug-ins" sub-menu item position for dialog:
#define k<xsl:value-of select="/code/@short-name"/>DialogMenuItemPosition	12.0
</xsl:if>

// Initial data format version numbers
#define k<xsl:value-of select="/code/@short-name"/>FirstMajorFormatNumber  RezLong(1)
#define k<xsl:value-of select="/code/@short-name"/>FirstMinorFormatNumber  RezLong(0)

// Data format version numbers for the PluginVersion resource 
#define k<xsl:value-of select="/code/@short-name"/>CurrentMajorFormatNumber k<xsl:value-of select="/code/@short-name"/>FirstMajorFormatNumber
#define k<xsl:value-of select="/code/@short-name"/>CurrentMinorFormatNumber k<xsl:value-of select="/code/@short-name"/>FirstMinorFormatNumber

#endif // __<xsl:value-of select="/code/@short-name"/>ID_h__
</xsl:template>

<xsl:template name="cascade-pmiids"> 
	<xsl:param name="idspace"/>
	<xsl:param name="iddefaultname"/>
	<xsl:param name="idprefix"/>
	<xsl:param name="idnumber"/>
	<xsl:choose><xsl:when test="$idnumber &lt; 26"
>//DECLARE_PMID(<xsl:value-of select="$idspace"/>, <xsl:value-of select="$iddefaultname"/>, <xsl:value-of select="$idprefix"/> + <xsl:value-of select="$idnumber"/>)
<xsl:call-template name="cascade-pmiids">
			<xsl:with-param name="idnumber" select = "$idnumber + 1"/>
			<xsl:with-param name="idspace" select = "$idspace"/>
			<xsl:with-param name="iddefaultname" select = "$iddefaultname"/>
			<xsl:with-param name="idprefix" select = "$idprefix"/>
</xsl:call-template>
		</xsl:when>  
	</xsl:choose>
	
</xsl:template>
</xsl:stylesheet>
