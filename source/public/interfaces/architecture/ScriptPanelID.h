//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ScriptPanelID.h $
//  
//  Owner: Jonathan W. Brown
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
//========================================================================================

#ifndef __SCRIPTPANELID__
#define __SCRIPTPANELID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kScriptPanelPrefix	 RezLong(0xcc00)

#define kScriptPanelActionPrefixFirst	RezLong(0xff000000)
#define kScriptPanelActionPrefixLast	RezLong(0xff001F00)


// plug-in ID
#define kScriptPanelPluginName 					"ScriptPanel"
DECLARE_PMID(kPlugInIDSpace, kScriptPanelPluginID,						kScriptPanelPrefix + 1)

// <Start IDC>
// <Class ID>
// Bosses
DECLARE_PMID(kClassIDSpace, kScriptPanelBoss,							kScriptPanelPrefix + 1)
DECLARE_PMID(kClassIDSpace, kScriptPanelActionComponentBoss,			kScriptPanelPrefix + 2)
DECLARE_PMID(kClassIDSpace, kScriptShortcutBoss,						kScriptPanelPrefix + 3)
DECLARE_PMID(kClassIDSpace, kScriptNodeWidgetBoss,						kScriptPanelPrefix + 4)
DECLARE_PMID(kClassIDSpace, kScriptNameBoss,							kScriptPanelPrefix + 5)
DECLARE_PMID(kClassIDSpace, kScriptTreeViewWidgetBoss,					kScriptPanelPrefix + 6)
DECLARE_PMID(kClassIDSpace, kScriptPanelKBSCPreActionBoss,				kScriptPanelPrefix + 7)
DECLARE_PMID(kClassIDSpace, kScriptPanelKBSCPostActionBoss,				kScriptPanelPrefix + 8)
DECLARE_PMID(kClassIDSpace, kScriptPanelKBSCDismissObsrvBoss,			kScriptPanelPrefix + 9)
DECLARE_PMID(kClassIDSpace, kScriptPanelMenuBoss,						kScriptPanelPrefix + 10)
DECLARE_PMID(kClassIDSpace, kScriptingTestMenuBoss,						kScriptPanelPrefix + 11)
DECLARE_PMID(kClassIDSpace, kScriptPanelStartupShutdownBoss,			kScriptPanelPrefix + 12)
DECLARE_PMID(kClassIDSpace, kChangeScriptPanelPreferencesCmdBoss,		kScriptPanelPrefix + 13)
DECLARE_PMID(kClassIDSpace, kScriptPanelInfoIconButtonBoss,             kScriptPanelPrefix + 14)

// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTPANELPREFERENCES,			kScriptPanelPrefix + 1)

// <Implementation ID>
// Implementation IDs
DECLARE_PMID(kImplementationIDSpace, kScriptPanelViewImpl,					kScriptPanelPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kScriptNameEHImpl,						kScriptPanelPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kScriptTreeObserverImpl,				kScriptPanelPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kScriptPanelTipImpl,					kScriptPanelPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kScriptTreeViewAdapterImpl,			kScriptPanelPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kScriptTreeViewWidgetMgrImpl,			kScriptPanelPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kScriptPanelActionComponentImpl,		kScriptPanelPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kScriptPanelKBSCPreActionImpl,			kScriptPanelPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kScriptPanelKBSCPostActionImpl,		kScriptPanelPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kScriptPanelKBSCDismissObsrvImpl,		kScriptPanelPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kScriptsDynamicMenuImpl,				kScriptPanelPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kScriptPanelMenuImpl,					kScriptPanelPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kScriptingTestMenuImpl,				kScriptPanelPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kScriptPanelShortcutSetObserverImpl,	kScriptPanelPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kScriptPanelStartupShutdownImpl,		kScriptPanelPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kScriptPanelPreferencesImpl,			kScriptPanelPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kChangeScriptPanelPreferencesCmdImpl,	kScriptPanelPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kScriptPanelInfoTipImpl,               kScriptPanelPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kScriptPanelInfoObserverImpl,          kScriptPanelPrefix + 19)

// <Widget ID>
// Widget ids
DECLARE_PMID(kWidgetIDSpace, kScriptTreeWidgetID,						kScriptPanelPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kScriptControlStripWidgetID,				kScriptPanelPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kScriptListWidgetID,						kScriptPanelPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kScriptListSmallWidgetID,					kScriptPanelPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kScriptPanelWidgetId,						kScriptPanelPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kScriptNodeNameWidgetID,					kScriptPanelPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kScriptNodeWidgetId,						kScriptPanelPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kScriptIconWidgetId,						kScriptPanelPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kScriptListElementWidgetId,				kScriptPanelPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kScriptNodeShortcutWidgetID,				kScriptPanelPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kScriptPanelInfoWidgetID,                  kScriptPanelPrefix + 11)

// <Action ID>
DECLARE_PMID(kActionIDSpace, kScriptPanelActionID,						kScriptPanelPrefix + 0)
DECLARE_PMID(kActionIDSpace, kNewScriptActionID,						kScriptPanelPrefix + 1)
DECLARE_PMID(kActionIDSpace, kScriptPanelSep1ActionID,					kScriptPanelPrefix + 2)
DECLARE_PMID(kActionIDSpace, kRunScriptActionID,						kScriptPanelPrefix + 3)
DECLARE_PMID(kActionIDSpace, kEditScriptActionID,						kScriptPanelPrefix + 4)
DECLARE_PMID(kActionIDSpace, kScriptPanelSep2ActionID,					kScriptPanelPrefix + 5)
DECLARE_PMID(kActionIDSpace, kShowScriptActionID,						kScriptPanelPrefix + 6)
DECLARE_PMID(kActionIDSpace, kDeleteScriptActionID,						kScriptPanelPrefix + 7)
DECLARE_PMID(kActionIDSpace, kScriptPanelSep3ActionID,					kScriptPanelPrefix + 8)
DECLARE_PMID(kActionIDSpace, kRedrawScriptActionID,						kScriptPanelPrefix + 9)
DECLARE_PMID(kActionIDSpace, kScriptPanelSep4ActionID,					kScriptPanelPrefix + 10)
DECLARE_PMID(kActionIDSpace, kDebugScriptActionID,						kScriptPanelPrefix + 11)
DECLARE_PMID(kActionIDSpace, kEnableAttachedScriptsActionID,			kScriptPanelPrefix + 12)
DECLARE_PMID(kActionIDSpace, kScriptsMainMenuActionID,					kScriptPanelPrefix + 13)
//gap
DECLARE_PMID(kActionIDSpace, kDisplayUnsupportedFilesActionID,			kScriptPanelPrefix + 15)

DECLARE_PMID(kActionIDSpace, kFirstScriptPanelActionID,					kScriptPanelActionPrefixFirst + 0)
//intervening Action IDs are allocated dynamically in ScriptPanelFile::SetActionID
DECLARE_PMID(kActionIDSpace, kLastScriptPanelActionID,					kScriptPanelActionPrefixLast + 255)

// <Ignore>
// Resource IDs
#define kScriptPanelResourceID				2100
#define kScriptPanelStringResID				2200
#define kScriptNodeWidgetRsrcID				2300
//#define kScriptListSmallElementRsrcID		2400
#define kScriptPanelIconRsrcID				2500
#define kScriptPaletteIconRsrcID			2501
#define kScriptPanelListRsrcID				2600
#define kScriptPanelStringsNoTransRsrcID	2700
#define kScriptPanelInfoIconRsrcID          2800

// Defines for the look of the panel
#define	kMinLayerPalWidth					240
#define	kMaxLayerPalWidth					10000
#define	kMinLayerPalHeight					(22 * 2) + 24
#define	kMaxLayerPalHeight					10000

#define kScriptPanelActionsResID			1000
#define kScriptPanelMenuActionsResID		1100

#endif //__SCRIPTNPANELID__
