//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/paneltreeview/PnlTrvID.h $
//  
//  Owner: Adobe Developer Technologies
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//  
//  Defines IDs used by the PnlTrv plug-in.
//  
//========================================================================================

#ifndef __PnlTrvID_h__
#define __PnlTrvID_h__

#include "SDKDef.h"

// Company:
#define kPnlTrvCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kPnlTrvCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kPnlTrvPluginName	"PanelTreeView"			// Name of this plug-in.
#define kPnlTrvPrefixNumber	0x5c110 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kPnlTrvVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kPnlTrvAuthor		"Adobe Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kPnlTrvPrefixNumber above to modify the prefix.)
#define kPnlTrvPrefix		RezLong(kPnlTrvPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kPnlTrvStringPrefix	SDK_DEF_STRINGIZE(kPnlTrvPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kPnlTrvPluginID, kPnlTrvPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kPnlTrvActionComponentBoss,	kPnlTrvPrefix + 0)
DECLARE_PMID(kClassIDSpace, kPnlTrvStringRegisterBoss,	kPnlTrvPrefix + 1)
DECLARE_PMID(kClassIDSpace, kPnlTrvMenuRegisterBoss,	kPnlTrvPrefix + 2)
DECLARE_PMID(kClassIDSpace, kPnlTrvActionRegisterBoss,	kPnlTrvPrefix + 3)
DECLARE_PMID(kClassIDSpace, kPnlTrvPanelWidgetBoss,		kPnlTrvPrefix + 4)
DECLARE_PMID(kClassIDSpace, kPnlTrvPanelRegisterBoss,	kPnlTrvPrefix + 5)
DECLARE_PMID(kClassIDSpace, kPnlTrvTreeViewWidgetBoss,	kPnlTrvPrefix + 6)
DECLARE_PMID(kClassIDSpace, kPnlTrvNodeWidgetBoss,		kPnlTrvPrefix + 7)
DECLARE_PMID(kClassIDSpace, kPnlTrvChangeOptionsCmdBoss,kPnlTrvPrefix + 8)
DECLARE_PMID(kClassIDSpace, kPnlTrvStartupShutdownBoss,	kPnlTrvPrefix + 9)
DECLARE_PMID(kClassIDSpace, kPnlTrvCViewPanelWidgetBoss,	kPnlTrvPrefix + 10)
DECLARE_PMID(kClassIDSpace, kPnlTrvScriptProviderBoss,	kPnlTrvPrefix + 11)
DECLARE_PMID(kClassIDSpace, kPnlTrvErrorStringServiceBoss,	kPnlTrvPrefix + 12)
DECLARE_PMID(kClassIDSpace, kPnlTrvConversionProviderBoss,	kPnlTrvPrefix + 13)

// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_IPNLTRVSHADOWEVENTHANDLER,	kPnlTrvPrefix + 0)
DECLARE_PMID(kInterfaceIDSpace, IID_IPNLTRVOPTIONS,				kPnlTrvPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IPNLTRVCHANGEOPTIONSCMDDATA,	kPnlTrvPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IPNLTRVIDLETASK,				kPnlTrvPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IPNLTRVDATAMODEL,				kPnlTrvPrefix + 5)

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kPnlTrvActionComponentImpl,			kPnlTrvPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kPnlTrvTVWidgetMgrImpl,				kPnlTrvPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kPnlTrvTreeObserverImpl,				kPnlTrvPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kPnlTrvTVHierarchyAdapterImpl,		kPnlTrvPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kPnlTrvNodeEHImpl,					kPnlTrvPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kPnlTrvChangeOptionsCmdImpl,		kPnlTrvPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kPnlTrvOptionsImpl,					kPnlTrvPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kPnlTrvChangeOptionsCmdDataImpl,	kPnlTrvPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kPnlTrvNodeObserverImpl,			kPnlTrvPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kPnlTrvIdleTaskImpl,				kPnlTrvPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kPnlTrvStartupShutdownImpl,		kPnlTrvPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kPnlTrvCustomViewImpl, kPnlTrvPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kPnlTrvDragDropSourceImpl, kPnlTrvPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kPnlTrvDataModelImpl, kPnlTrvPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kPnlTrvScriptProviderImpl, kPnlTrvPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kPnlTrvErrorStringServiceImpl, kPnlTrvPrefix + 16)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kPnlTrvAboutActionID,				kPnlTrvPrefix + 0)
DECLARE_PMID(kActionIDSpace, kPnlTrvPanelWidgetActionID,		kPnlTrvPrefix + 1)
DECLARE_PMID(kActionIDSpace, kPnlTrvSeparator1ActionID,			kPnlTrvPrefix + 2)
DECLARE_PMID(kActionIDSpace, kPnlTrvPopupAboutThisActionID,		kPnlTrvPrefix + 3)
DECLARE_PMID(kActionIDSpace, kPnlTrvRefreshActionID,			kPnlTrvPrefix + 11)
DECLARE_PMID(kActionIDSpace, kPnlTrvSetOptionsActionID,			kPnlTrvPrefix + 12)

// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kPnlTrvPanelWidgetID,					kPnlTrvPrefix + 0) 
DECLARE_PMID(kWidgetIDSpace, kPnlTrvTreeViewWidgetID,				kPnlTrvPrefix + 1) 
DECLARE_PMID(kWidgetIDSpace, kPnlTrvNodeWidgetId,					kPnlTrvPrefix + 2) 
DECLARE_PMID(kWidgetIDSpace, kPnlTrvNodeNameWidgetID,				kPnlTrvPrefix + 3) 
DECLARE_PMID(kWidgetIDSpace, kPnlTrvElementWidgetId,				kPnlTrvPrefix + 4) 
DECLARE_PMID(kWidgetIDSpace, kPnlTrvIconWidgetId,					kPnlTrvPrefix + 5) 
DECLARE_PMID(kWidgetIDSpace, kPnlTrvCustomPanelViewWidgetID,		kPnlTrvPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kPnlTrvTextMessageWidgetID,			kPnlTrvPrefix + 7)

// ScriptElement IDs:
DECLARE_PMID(kScriptInfoIDSpace, kPnlTrvPreferencesObjectScriptElement,	kPnlTrvPrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kPnlTrvPreferencesPropertyScriptElement,	kPnlTrvPrefix + 2)
DECLARE_PMID(kScriptInfoIDSpace, kPnlTrvFolderPropertyScriptElement,	kPnlTrvPrefix + 3)

// Error codes:
DECLARE_PMID(kErrorIDSpace, kPnlTrvFolderNotSetError, kPnlTrvPrefix + 0)

// Error Codes
#define kPnlTrvFolderNotSetErrorStringKey kPnlTrvStringPrefix "kPnlTrvFolderNotSetErrorStringKey"

// "About Plug-ins" sub-menu:
#define kPnlTrvAboutMenuKey			kPnlTrvStringPrefix "kPnlTrvAboutMenuKey"
#define kPnlTrvAboutMenuPath		kSDKDefStandardAboutMenuPath kPnlTrvCompanyKey

// "Plug-ins" sub-menu:
#define kPnlTrvPluginsMenuKey 		kPnlTrvStringPrefix "kPnlTrvPluginsMenuKey"
#define kPnlTrvPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kPnlTrvCompanyKey kSDKDefDelimitMenuPath kPnlTrvPluginsMenuKey

// Menu item keys:
#define kPnlTrvRefreshMenuItemKey				kPnlTrvStringPrefix "kPnlTrvRefreshMenuItemKey"
#define kPnlTrvSetOptionsMenuItemKey			kPnlTrvStringPrefix "kPnlTrvSetOptionsMenuItemKey"

// Other StringKeys:
#define kPnlTrvAboutBoxStringKey				kPnlTrvStringPrefix "kPnlTrvAboutBoxStringKey"
#define kPnlTrvRefreshStringKey					kPnlTrvStringPrefix "kPnlTrvRefreshStringKey"
#define kPnlTrvPanelTitleKey					kPnlTrvStringPrefix	"kPnlTrvPanelTitleKey"
#define kPnlTrvStaticTextKey					kPnlTrvStringPrefix	"kPnlTrvStaticTextKey"
#define kPnlTrvInternalPopupMenuNameKey			kPnlTrvStringPrefix	"kPnlTrvInternalPopupMenuNameKey"
#define kPnlTrvTargetMenuPath kPnlTrvInternalPopupMenuNameKey
#define kPnlTrvSetOption1StringKey kPnlTrvStringPrefix "kPnlTrvSetOption1StringKey"
#define kPnlTrvChangeOptionsCmdKey kPnlTrvStringPrefix "kPnlTrvChangeOptionsCmdKey"
#define kPnlTrvIdleTaskKey						kPnlTrvStringPrefix "kPnlTrvIdleTaskKey"

// Menu item positions:
#define kPnlTrvSetOptionsMenuItemPosition			1.0
#define kPnlTrvRefreshMenuItemPosition				2.0
#define	kPnlTrvSeparator1MenuItemPosition			10.0
#define kPnlTrvAboutThisMenuItemPosition			11.0

#define kPnlTrvNodeWidgetRsrcID 	1200


// See. the platform resource file where these are used!
#define kPnlTrvEyeBallIconRsrcID			1510
#define kPnlTrvLockPenIconRsrcID			1512
#define kPnlTrvPenIconRsrcID				1514


// Initial Data format IDs of the persistent data was first introduced in InDesign 2.0
#define kPnlTrvInitialMajorFormat		kSDKDef_20_PersistMajorVersionNumber
#define kPnlTrvInitialMinorFormat		kSDKDef_20_PersistMinorVersionNumber
// Note: The data format has not been changed since InDesign 2.0.

#define kPnlTrvStoreWideStringMajorFormat		kSDKDef_50_PersistMajorVersionNumber
#define kPnlTrvStoreWideStringMinorFormat		RezLong(1)

// Format IDs for the PluginVersion resource 
#define kPnlTrvLastMajorFormatChange	kPnlTrvStoreWideStringMajorFormat		// Last major format change
#define kPnlTrvLastMinorFormatChange	kPnlTrvStoreWideStringMinorFormat		// Last minor format change


#endif // __PnlTrvID_h__

//  Generated by Dolly build 17: template "IfPanelMenu".
// End, PnlTrvID.h.


