<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
<xsl:import href="global-variables.xsl"/>
<xsl:import href="standard-adobe-header.xsl"/>
<xsl:import href="standard-footer.xsl"/>

<xsl:output name="cppfile" method="text"/>
<xsl:template match="fr-file">
Generating .FR file from template...
 <xsl:document href="{/code/@source-dir-absolute}{$filesep}{/code/@short-name}.fr" format="cppfile">
  <xsl:call-template name="standard-adobe-header"/>
  <xsl:call-template name="fr"/>
  <xsl:call-template name="standard-footer"/>
  </xsl:document>
</xsl:template>
<xsl:template match="fr" name="fr">
// General includes:
#include "MenuDef.fh"
#include "ActionDef.fh"
#include "ActionDefs.h"
#include "AdobeMenuPositions.h"
#include "LocaleIndex.h"
#include "PMLocaleIds.h"
#include "StringTable.fh"
#include "ObjectModelTypes.fh"
#include "ShuksanID.h"
#include "ActionID.h"
#include "CommandID.h"
#include "WorkspaceID.h"
#include "WidgetID.h"
#include "BuildNumber.h"
#include "PlugInModel_UIAttributes.h"
<xsl:if test="/code/generate-panel">#include "PanelList.fh"</xsl:if>
<xsl:if test="(/code/generate-panel) or (/code/generate-dialog)">
#include "InterfaceColorDefines.h"
#include "IControlViewDefs.h"
#include "SysControlIDs.h"
#include "Widgets.fh"	// for PalettePanelWidget or DialogBoss
</xsl:if>
<xsl:if test="/code/generate-dialog">
#include "EveInfo.fh"	// Required when using EVE for dialog layout/widget placement
</xsl:if>
<xsl:if test="/code/generate-scriptprovider">
#include "ScriptInfoTypes.fh"
#include "AppFrameworkID.h"
</xsl:if>
// Project includes:
#include "<xsl:value-of select="/code/@short-name"/>ID.h"
#include "GenericID.h"
#include "ShuksanID.h"
#include "TextID.h"
<xsl:if test="/code/generate-scriptprovider">
#include "<xsl:value-of select="/code/@short-name"/>ScriptingDefs.h"
</xsl:if>
<xsl:if test="/code/generate-preflight">
#include "PackageAndPreflightID.h"
#include "PackageAndPreflightUIID.h"
</xsl:if>

#ifdef __ODFRC__

/*  
 * Plugin version definition.
 */
resource PluginVersion (kSDKDefPluginVersionResourceID)
{
	kTargetVersion,
	k<xsl:value-of select="/code/@short-name"/>PluginID,
	kSDKDefPlugInMajorVersionNumber, kSDKDefPlugInMinorVersionNumber,
	kSDKDefHostMajorVersionNumber, kSDKDefHostMinorVersionNumber,
	k<xsl:value-of select="/code/@short-name"/>CurrentMajorFormatNumber, k<xsl:value-of select="/code/@short-name"/>CurrentMinorFormatNumber,
	{ <xsl:value-of select="/code/@product-type"/> },
	{ kWildFS },
	<xsl:value-of select="/code/@plugin-type"/>,
	k<xsl:value-of select="/code/@short-name"/>Version
};

/*  
 * The ExtraPluginInfo resource adds extra information to the Missing Plug-in dialog
 * that is popped when a document containing this plug-in's data is opened when
 * this plug-in is not present. These strings are not translatable strings
 * since they must be available when the plug-in isn't around. They get stored
 * in any document that this plug-in contributes data to.
 */
resource ExtraPluginInfo(1)
{
	k<xsl:value-of select="/code/@short-name"/>CompanyValue,			// Company name
	k<xsl:value-of select="/code/@short-name"/>MissingPluginURLValue,	// URL 
	k<xsl:value-of select="/code/@short-name"/>MissingPluginAlertValue,	// Missing plug-in alert text
};

/* 
 * Boss class definitions.
 */
resource ClassDescriptionTable(kSDKDefClassDescriptionTableResourceID)
{{{
<xsl:if test="/code/generate-menu">
	/*
	 * This boss class supports two interfaces:
	 * IActionComponent and IPMPersist.
     *
	 * <xsl:variable name="groupname" select="translate(/code/@long-name, 'ABCDEFGHIJKLMNOPQRSTUVWXYZ', 'abcdefghijklmnopqrstuvwxyz')"/>
	 * @ingroup <xsl:value-of select="$groupname"/>
	 */
	Class
	{
		k<xsl:value-of select="/code/@short-name"/>ActionComponentBoss,
		kInvalidClass,
		{
			// Handle the actions from the menu.
			IID_IACTIONCOMPONENT, k<xsl:value-of select="/code/@short-name"/>ActionComponentImpl,
			// Persist the state of the menu across application instantiation. Implementation provided by the API.
			IID_IPMPERSIST, kPMPersistImpl
		}
	},
</xsl:if>
<xsl:if test="/code/generate-panel">
    /*
	 * This boss class inherits from an API panel boss class, and
	 * adds an interface to control a pop-up menu on the panel.
	 * The implementation for this interface is provided by the API.
     *
	 * <xsl:variable name="groupname" select="translate(/code/@long-name, 'ABCDEFGHIJKLMNOPQRSTUVWXYZ', 'abcdefghijklmnopqrstuvwxyz')"/>
	 * @ingroup <xsl:value-of select="$groupname"/>
	 */
	Class
	{
		k<xsl:value-of select="/code/@short-name"/>PanelWidgetBoss,
		kPalettePanelWidgetBoss,
		{
			/*
			 * The plug-in's implementation of ITextControlData with an exotic IID of IID_IPANELMENUDATA.
			 * Implementation provided by the API.
			 */
			IID_IPANELMENUDATA, kCPanelMenuDataImpl,
		}
	},
</xsl:if>
<xsl:if test="/code/generate-dialog">
	/*
	 * This boss class implements the dialog for this plug-in. All
	 * dialogs must implement IDialogController. Specialisation of
	 * IObserver is only necessary if you want to handle widget
	 * changes dynamically rather than just gathering their values
	 * and applying in the IDialogController implementation.
	 * In this implementation IObserver is specialised so that the
	 * plug-in's about box is popped when the info button widget
	 * is clicked.
     *
	 * <xsl:variable name="groupname" select="translate(/code/@long-name, 'ABCDEFGHIJKLMNOPQRSTUVWXYZ', 'abcdefghijklmnopqrstuvwxyz')"/>
	 * @ingroup <xsl:value-of select="$groupname"/>
	 */
	Class
	{
		k<xsl:value-of select="/code/@short-name"/>DialogBoss,
		kDialogBoss,
		{
			// Provides management and control over the dialog.
			IID_IDIALOGCONTROLLER, k<xsl:value-of select="/code/@short-name"/>DialogControllerImpl,
			
			// Allows dynamic processing of dialog changes.
			IID_IOBSERVER, k<xsl:value-of select="/code/@short-name"/>DialogObserverImpl,
		}
	},
</xsl:if>
<xsl:for-each select="/code/boss-item">		
	Class
	{
		<xsl:value-of select="@boss-id"/>,
		<xsl:value-of select="@boss-parent"/>,
		{
			<xsl:for-each select="boss-impl-pair">	
			<xsl:value-of select="@interface-id"/>,<xsl:value-of select="@impl-id"/>,
			</xsl:for-each>
		}
	},
	
</xsl:for-each>
<xsl:for-each select="/code/boss-addin">		
	AddIn
	{
		<xsl:value-of select="@boss-id"/>,
		kInvalidClass,
		{
			<xsl:for-each select="boss-impl-pair">	
			<xsl:value-of select="@interface-id"/>,<xsl:value-of select="@impl-id"/>,
			</xsl:for-each>
		}
	},
</xsl:for-each>
}}};

/*  
 * Implementation definition.
 */
resource FactoryList (kSDKDefFactoryListResourceID)
{
	kImplementationIDSpace,
	{
		#include "<xsl:value-of select="/code/@short-name"/>FactoryList.h"
	}
};
<xsl:if test="/code/generate-menu">
/*  
 * Menu definition.
 */
resource MenuDef (kSDKDefMenuResourceID)
{
	{
		// The About sub-menu item for this plug-in.
		k<xsl:value-of select="/code/@short-name"/>AboutActionID,			// ActionID (kInvalidActionID for positional entries)
		k<xsl:value-of select="/code/@short-name"/>AboutMenuPath,			// Menu Path.
		kSDKDefAlphabeticPosition,											// Menu Position.
		kSDKDefIsNotDynamicMenuFlag,										// kSDKDefIsNotDynamicMenuFlag or kSDKDefIsDynamicMenuFlag
<xsl:for-each select="/code/menu-item">		k<xsl:value-of select="/code/@short-name"/><xsl:value-of select="@name"/>ActionID,
		k<xsl:value-of select="/code/@short-name"/>TargetMenuPath,
		k<xsl:value-of select="/code/@short-name"/><xsl:value-of select="@name"/>MenuItemPosition,
		kSDKDefIsNotDynamicMenuFlag,
</xsl:for-each>
<xsl:if test="/code/generate-panel">
		// Separator for the popup menu on the panel
		k<xsl:value-of select="/code/@short-name"/>Separator1ActionID,
		k<xsl:value-of select="/code/@short-name"/>InternalPopupMenuNameKey kSDKDefDelimiterAndSeparatorPath,	// :- to mark an item as a separator.
		k<xsl:value-of select="/code/@short-name"/>Separator1MenuItemPosition,
		kSDKDefIsNotDynamicMenuFlag,

		// About this plug-in sub-menu for the popup menu on the panel
		k<xsl:value-of select="/code/@short-name"/>PopupAboutThisActionID,
		k<xsl:value-of select="/code/@short-name"/>TargetMenuPath
		k<xsl:value-of select="/code/@short-name"/>AboutThisMenuItemPosition,
		kSDKDefIsNotDynamicMenuFlag,
</xsl:if>
<xsl:if test="/code/generate-dialog">
		// The Plug-ins menu sub-menu items for this plug-in.
		k<xsl:value-of select="/code/@short-name"/>DialogActionID,
		k<xsl:value-of select="/code/@short-name"/>PluginsMenuPath,
		k<xsl:value-of select="/code/@short-name"/>DialogMenuItemPosition,
		kSDKDefIsNotDynamicMenuFlag,
</xsl:if>
	}
};

/* 
 * Action definition.
 */
resource ActionDef (kSDKDefActionResourceID)
{
	{
		k<xsl:value-of select="/code/@short-name"/>ActionComponentBoss, 		// ClassID of boss class that implements the ActionID.
		k<xsl:value-of select="/code/@short-name"/>AboutActionID,	// ActionID.
		k<xsl:value-of select="/code/@short-name"/>AboutMenuKey,	// Sub-menu string.
		kOtherActionArea,				// Area name (see ActionDefs.h).
		kNormalAction,					// Type of action (see ActionDefs.h).
		kDisableIfLowMem,				// Enabling type (see ActionDefs.h).
		kInvalidInterfaceID,			// Selection InterfaceID this action cares about or kInvalidInterfaceID.
		kSDKDefInvisibleInKBSCEditorFlag, // kSDKDefVisibleInKBSCEditorFlag or kSDKDefInvisibleInKBSCEditorFlag.
<xsl:for-each select="/code/menu-item">		k<xsl:value-of select="/code/@short-name"/>ActionComponentBoss,
		k<xsl:value-of select="/code/@short-name"/><xsl:value-of select="@name"/>ActionID,
		k<xsl:value-of select="/code/@short-name"/><xsl:value-of select="@name"/>MenuItemKey,
		kOtherActionArea,
		kNormalAction,
		kDisableIfLowMem,
		kInvalidInterfaceID,
		kSDKDefInvisibleInKBSCEditorFlag,
</xsl:for-each>
<xsl:if test="/code/generate-panel">
		k<xsl:value-of select="/code/@short-name"/>ActionComponentBoss,
		k<xsl:value-of select="/code/@short-name"/>PopupAboutThisActionID,
		kSDKDefAboutThisPlugInMenuKey,	// Key to the name of this action
		kOtherActionArea,
		kNormalAction,
		kDisableIfLowMem,
		kInvalidInterfaceID,
		kSDKDefInvisibleInKBSCEditorFlag,
</xsl:if>
<xsl:if test="/code/generate-dialog">
		k<xsl:value-of select="/code/@short-name"/>ActionComponentBoss,
		k<xsl:value-of select="/code/@short-name"/>DialogActionID,		
		k<xsl:value-of select="/code/@short-name"/>DialogMenuItemKey,		
		kOtherActionArea,			
		kNormalAction,				
		kDisableIfLowMem,	
		kInvalidInterfaceID,		
		kSDKDefVisibleInKBSCEditorFlag,
</xsl:if>
	}
};
</xsl:if>

/*  
 * Locale Indicies.
 * The LocaleIndex should have indicies that point at your
 * localizations for each language system that you are localized for.
 */

/*  
 * String LocaleIndex.
 */
resource LocaleIndex ( kSDKDefStringsResourceID)
{
	kStringTableRsrcType,
	{
		kWildFS, k_enUS, kSDKDefStringsResourceID + index_enUS
		kWildFS, k_enGB, kSDKDefStringsResourceID + index_enUS
		kWildFS, k_deDE, kSDKDefStringsResourceID + index_enUS
		kWildFS, k_frFR, kSDKDefStringsResourceID + index_enUS
		kWildFS, k_esES, kSDKDefStringsResourceID + index_enUS
		kWildFS, k_ptBR, kSDKDefStringsResourceID + index_enUS
		kWildFS, k_svSE, kSDKDefStringsResourceID + index_enUS
		kWildFS, k_daDK, kSDKDefStringsResourceID + index_enUS
		kWildFS, k_nlNL, kSDKDefStringsResourceID + index_enUS
		kWildFS, k_itIT, kSDKDefStringsResourceID + index_enUS
		kWildFS, k_nbNO, kSDKDefStringsResourceID + index_enUS
		kWildFS, k_fiFI, kSDKDefStringsResourceID + index_enUS
		kInDesignJapaneseFS, k_jaJP, kSDKDefStringsResourceID + index_jaJP
	}
};

resource LocaleIndex (kSDKDefStringsNoTransResourceID)
{
	kStringTableRsrcType,
	{
		kWildFS, k_Wild, kSDKDefStringsNoTransResourceID + index_enUS
	}
};

// Strings not being localized
resource StringTable (kSDKDefStringsNoTransResourceID + index_enUS)
{
	k_enUS,									// Locale Id
	kEuropeanMacToWinEncodingConverter,		// Character encoding converter
	{<xsl:if test="/code/generate-panel">
		k<xsl:value-of select="/code/@short-name"/>InternalPopupMenuNameKey,	k<xsl:value-of select="/code/@short-name"/>InternalPopupMenuNameKey,		// No need to translate, internal menu name.
	</xsl:if>
	}
};
<xsl:if test="/code/generate-panel">
/*  
 * Panel LocaleIndex.
 */
resource LocaleIndex (kSDKDefPanelResourceID)
{
	kViewRsrcType,
	{
		kWildFS, k_Wild, 	kSDKDefPanelResourceID + index_enUS
	}
};

/*  
 * Type definition.
 */
type <xsl:value-of select="/code/@short-name"/>PanelWidget(kViewRsrcType) : PalettePanelWidget(ClassID = k<xsl:value-of select="/code/@short-name"/>PanelWidgetBoss)
{
	CPanelMenuData;
};

/*  
 * PanelList definition.
 */
resource PanelList (kSDKDefPanelResourceID)
{
	{
		// 1st panel in the list
		kSDKDefPanelResourceID,		// Resource ID for this panel (use SDK default rsrc ID)
		k<xsl:value-of select="/code/@short-name"/>PluginID,			// ID of plug-in that owns this panel
		kIsResizable,
		k<xsl:value-of select="/code/@short-name"/>PanelWidgetActionID,	// Action ID to show/hide the panel
		k<xsl:value-of select="/code/@short-name"/>PanelTitleKey,	// Shows up in the Window list.
		"",							// Alternate menu path of the form "Main:Foo" if you want your palette menu item in a second place
		0.0,						// Alternate Menu position Alternate Menu position for determining menu order
		0,0,						// Rsrc ID, Plugin ID for a PNG icon resource to use for this palette
		c_Panel
	}
};

/* 
 * PanelView definition.
 * Note: it is not necessary to use EVE for panels.
 * The view is not currently localised: therefore, it can reside here.
 * However, if you wish to localise it, it is recommended to locate it in one of
 * the localised framework resource files (i.e. <xsl:value-of select="/code/@short-name"/>_enUS.fr etc.).
 */
resource <xsl:value-of select="/code/@short-name"/>PanelWidget(kSDKDefPanelResourceID + index_enUS)
{
	__FILE__, __LINE__,					// Localization macro
	k<xsl:value-of select="/code/@short-name"/>PanelWidgetID,					// WidgetID
	kPMRsrcID_None,						// RsrcID
	kBindNone,							// Binding (0=none)
	Frame(0, 0, 207, 32),				// Frame: left, top, right, bottom.
	kTrue, kTrue,						// Visible, Enabled
	kFalse,								// Erase background
	kInterfacePaletteFill,				// Erase to color
	kFalse,								// Draw dropshadow
	k<xsl:value-of select="/code/@short-name"/>PanelTitleKey,					// Panel name
	{
		// Replace this text widget with your panel content.
		StaticTextWidget
		(
			0,								 // WidgetId (default=0)
			kSysStaticTextPMRsrcId,			 // RsrcId
			kBindNone,						 // Frame binding
			Frame(5, 10, 202, 27),			 // Frame: left, top, right, bottom.
			kTrue, kTrue,					 // Visible, Enabled
			kAlignLeft, kEllipsizeEnd, kTrue // Alignment, ellipsize style, convert ampersands
			k<xsl:value-of select="/code/@short-name"/>StaticTextKey,				// Initial text.
			0								// No associated widget
		),
	}

	k<xsl:value-of select="/code/@short-name"/>InternalPopupMenuNameKey		// Popup menu name (internal)
};
</xsl:if>
<xsl:if test="/code/generate-dialog">
/*  
 * Dialog LocaleIndex.
 */
resource LocaleIndex (kSDKDefDialogResourceID)
{
   kViewRsrcType,
	{
		kWildFS, k_Wild, kSDKDefDialogResourceID + index_enUS
	}
};

/*  
 * Type definition.
 */
type <xsl:value-of select="/code/@short-name"/>DialogWidget(kViewRsrcType) : DialogBoss(ClassID = k<xsl:value-of select="/code/@short-name"/>DialogBoss)
{
	WidgetEveInfo;
};

/*  
 * Dialog definition.
 * Use EVE for laying our dialogs.
 *
 * This view is not localised: therefore, it can reside here.
 * However, if you wish to localise it, it is recommended to locate it in one of
 * the localised framework resource files (i.e. <xsl:value-of select="/code/@short-name"/>_enUS.fr etc.) and
 * update your Dialog LocaleIndex accordingly.
 */
resource <xsl:value-of select="/code/@short-name"/>DialogWidget (kSDKDefDialogResourceID + index_enUS)
{
	__FILE__, __LINE__,
	k<xsl:value-of select="/code/@short-name"/>DialogWidgetID,	// WidgetID
	kPMRsrcID_None,				// RsrcID
	kBindNone,					// Binding
	0, 0, 388,112,				// Frame (l,t,r,b)
	kTrue, kTrue,				// Visible, Enabled
	k<xsl:value-of select="/code/@short-name"/>DialogTitleKey,	// Dialog name
	{
		// This a spacer widget to simulate the dialog having content.
		// This is necessary because EVE will auto-size the dialog according
		// to its contents. Therefore, if it only has the OK and Cancel buttons,
		// the dialog will appear very small.
		// You should replace this widget with your own dialog content.
		StaticTextWidget
		(
			0,								 // WidgetId (default=0)
			kSysStaticTextPMRsrcId,			 // RsrcId
			kBindNone,						 // Frame binding
			Frame(0, 0, 270, 5),			 // Frame: left, top, right, bottom.
			kTrue, kTrue,					 // Visible, Enabled
			kAlignLeft, kEllipsizeEnd, kTrue // Alignment, ellipsize style, convert ampersands
			"",								 // Initial text.
			0,
		),

		// OK and Cancel buttons
		EVEGenericPanelWidget
		(
			kInvalidWidgetID,		// WidgetId
			0						// RsrcId
			0,
			kBindNone,				// Frame binding
			Frame(0, 0, 0, 0),		// No need to specify dimensions of GenericPanelWidget
			kTrue,					// Visible
			kTrue,					// Enabled
			kEVEAlignLeft | kEVERegularSpaceAfter | kEVEArrangeChildrenInColumn,
			{
				EVEDefaultButtonWidget
				(
					kOKButtonWidgetID,				// WidgetID
					kSysButtonPMRsrcId,				// RsrcID
					kBindNone,						// Binding
					Frame(0, 0, 0, 0),				// Frame (l,t,r,b)
					kTrue, kTrue,					// Visible, Enabled
					kSDKDefOKButtonApplicationKey,	// Button text
					kEVELargeSpaceAfter,
				),
		
				EVECancelButtonWidget
				(
					kCancelButton_WidgetID,				// WidgetID
					kSysButtonPMRsrcId,					// RsrcID
					kBindNone,							// Binding
					Frame(0, 0, 0, 0),					// Frame (l,t,r,b)
					kTrue, kTrue,						// Visible, Enabled
					kSDKDefCancelButtonApplicationKey,	// Button name
					kTrue,								// Change to Reset on option-click.
					kEVELargeSpaceAfter,
				),
			}
		),
	},

	kEVEArrangeChildrenInRow | kEVESmallMargin,
};
</xsl:if>
<xsl:if test="/code/generate-scriptprovider">
	<xsl:call-template name="script-element-info"/>
</xsl:if>
#endif // __ODFRC__

#include "<xsl:value-of select="/code/@short-name"/>_enUS.fr"
#include "<xsl:value-of select="/code/@short-name"/>_jaJP.fr"
</xsl:template>
</xsl:stylesheet>