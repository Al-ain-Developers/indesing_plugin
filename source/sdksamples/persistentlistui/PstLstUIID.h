//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlistui/PstLstUIID.h $
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
//  Defines IDs used by the PstLstUI plug-in.
//  
//========================================================================================

#ifndef __PstLstUIID_h__
#define __PstLstUIID_h__

#include "SDKDef.h"

// Company:
#define kPstLstUICompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kPstLstUICompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kPstLstUIPluginName		"PersistentListUI"			// Name of this plug-in.
#define kPstLstUIPrefixNumber	0xB3100 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kPstLstUIVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kPstLstUIAuthor			"Adobe Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kPstLstUIPrefixNumber above to modify the prefix.)
#define kPstLstUIPrefix			RezLong(kPstLstUIPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kPstLstUIStringPrefix	SDK_DEF_STRINGIZE(kPstLstUIPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

START_IDS()

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kPstLstUIPluginID, kPstLstUIPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kPstLstUIActionComponentBoss,		kPstLstUIPrefix + 0)
DECLARE_PMID(kClassIDSpace, kPstLstUIPanelWidgetBoss,			kPstLstUIPrefix + 1)
DECLARE_PMID(kClassIDSpace, kPstLstUIDialogBoss,				kPstLstUIPrefix + 2)
DECLARE_PMID(kClassIDSpace, kPstLstUITreeViewWidgetBoss,		kPstLstUIPrefix + 3)

// InterfaceIDs:
// NONE. 

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kPstLstUIActionComponentImpl,		kPstLstUIPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kPstLstUIDlgControllerImpl,			kPstLstUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kPstLstUIDlgObserverImpl,			kPstLstUIPrefix + 2) 
DECLARE_PMID(kImplementationIDSpace, kPstLstUISelectionObserverImpl,		kPstLstUIPrefix + 3) 
DECLARE_PMID(kImplementationIDSpace, kPstLstUITVWidgetMgrImpl,		kPstLstUIPrefix + 4) 
DECLARE_PMID(kImplementationIDSpace, kPstLstUITVHierarchyAdapterImpl,		kPstLstUIPrefix + 5) 

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kPstLstUIAboutActionID,			kPstLstUIPrefix + 0)
DECLARE_PMID(kActionIDSpace, kPstLstUIPanelWidgetActionID,	kPstLstUIPrefix + 1)
DECLARE_PMID(kActionIDSpace, kPstLstUISeparator1ActionID,		kPstLstUIPrefix + 2)
DECLARE_PMID(kActionIDSpace, kPstLstUIPopupAboutThisActionID,	kPstLstUIPrefix + 3)
DECLARE_PMID(kActionIDSpace, kPstLstUINewActionID,			kPstLstUIPrefix + 11)
DECLARE_PMID(kActionIDSpace, kPstLstUIModifyActionID,			kPstLstUIPrefix + 12)
DECLARE_PMID(kActionIDSpace, kPstLstUIDeleteActionID,			kPstLstUIPrefix + 13)

// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kPstLstUIPanelWidgetID,			kPstLstUIPrefix + 0) 
DECLARE_PMID(kWidgetIDSpace, kPstLstUIDialogWidgetID,			kPstLstUIPrefix + 1) 
DECLARE_PMID(kWidgetIDSpace, kPstLstUIListWidgetID,			kPstLstUIPrefix + 2) 
DECLARE_PMID(kWidgetIDSpace, kPstLstUIIconSuiteWidgetID_obsolete,	kPstLstUIPrefix + 3) 
DECLARE_PMID(kWidgetIDSpace, kPstLstUIStaticTextWidgetID,		kPstLstUIPrefix + 4) 
DECLARE_PMID(kWidgetIDSpace, kPstLstUIEditBoxWidgetID,		kPstLstUIPrefix + 5) 
//DECLARE_PMID(kWidgetIDSpace, kPstLstUILabelWidgetID,			kPstLstUIPrefix + 6) 
//DECLARE_PMID(kWidgetIDSpace, kPstLstUIListLabelWidgetID,		kPstLstUIPrefix + 7) 
//DECLARE_PMID(kWidgetIDSpace, kPstLstUIListBoxWidgetID,		kPstLstUIPrefix + 8) 

#define kPstLstUIListElementRsrcID (kSDKDefPanelResourceID + 751)

DECLARE_PMID(kWidgetIDSpace, kPstLstUIListParentWidgetId,		kPstLstUIPrefix + 10) 
DECLARE_PMID(kWidgetIDSpace, kPstLstUITextWidgetID,			kPstLstUIPrefix + 11) 
DECLARE_PMID(kWidgetIDSpace, kPstLstUITreeViewWidgetID,			kPstLstUIPrefix + 12) 
 
// ScriptIDs:
// NONE.

// Error codes:
// NONE.

END_IDS()

// "About Plug-ins" sub-menu:
#define kPstLstUIAboutMenuKey			kPstLstUIStringPrefix "kPstLstUIAboutMenuKey"
#define kPstLstUIAboutMenuPath			kSDKDefStandardAboutMenuPath kPstLstUICompanyKey

// "Plug-ins" sub-menu:
#define kPstLstUIPluginsMenuKey 		kPstLstUIStringPrefix "kPstLstUIPluginsMenuKey"
#define kPstLstUIPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kPstLstUICompanyKey kSDKDefDelimitMenuPath kPstLstUIPluginsMenuKey

// Menu item keys:
#define kPstLstUINewMenuItemKey		kPstLstUIStringPrefix "kPstLstUINewMenuItemKey"
#define kPstLstUINewAllMenuItemKey		kPstLstUIStringPrefix "kPstLstUINewAllMenuItemKey"
#define kPstLstUIModifyMenuItemKey		kPstLstUIStringPrefix "kPstLstUIModifyMenuItemKey"
#define kPstLstUIDeleteMenuItemKey		kPstLstUIStringPrefix "kPstLstUIDeleteMenuItemKey"

// Panel item keys:
#define kPstLstUIPanelTitleKey					kPstLstUIStringPrefix	"kPstLstUIPanelTitleKey"

// Dialog item keys:
#define kPstLstUIDlgTitleKey					kPstLstUIStringPrefix	"kPstLstUIDlgTitleKey"

// Error string keys: 
// NONE.

// Other StringKeys:
// TODO - eliminate the ones that we don't need.
#define kPstLstUIAboutBoxStringKey				kPstLstUIStringPrefix "kPstLstUIAboutBoxStringKey"
//#define kPstLstUINewStringKey			kPstLstUIStringPrefix "kPstLstUINewStringKey"
//#define kPstLstUIModifyStringKey			kPstLstUIStringPrefix "kPstLstUIModifyStringKey"
//#define kPstLstUIDeleteStringKey			kPstLstUIStringPrefix "kPstLstUIDeleteStringKey"
//#define kPstLstUISelectStringKey							kPstLstUIStringPrefix	"kPstLstUISelectStringKey"
#define kPstLstUIStaticTextKey					kPstLstUIStringPrefix	"kPstLstUIStaticTextKey"
#define kPstLstUIInternalPopupMenuNameKey		kPstLstUIStringPrefix	"kPstLstUIInternalPopupMenuNameKey"
#define kPstLstUITargetMenuPath kPstLstUIInternalPopupMenuNameKey
#define kPstLstUIDataStaticTextKey					kPstLstUIStringPrefix	"kPstLstUIDataStaticTextKey"
//#define kPstLstUINoValidPageItemsSelectedKey			kPstLstUIStringPrefix	"kPstLstUINoValidPageItemsSelectedKey"
#define kPstLstUINewCmdFailedKey			kPstLstUIStringPrefix	"kPstLstUINewCmdFailedKey"
#define kPstLstUIDeleteCmdFailedKey			kPstLstUIStringPrefix	"kPstLstUIDeleteCmdFailedKey"
#define kPstLstUIModifyCmdFailedKey			kPstLstUIStringPrefix	"kPstLstUIModifyCmdFailedKey"
#define kPstLstUIDeleteItemCmdFailedKey			kPstLstUIStringPrefix	"kPstLstUIDeleteItemCmdFailedKey"
#define kPstLstUISelectCmdFailedKey			kPstLstUIStringPrefix	"kPstLstUISelectCmdFailedKey"
#define kPstLstUINoDataTextKey							kPstLstUIStringPrefix	"kPstLstUINoDataTextKey"
#define kPstLstUIListLabelTextKey							kPstLstUIStringPrefix	"kPstLstUIListLabelTextKey"

// Menu item positions:
#define kPstLstUINewMenuItemPosition			1.0
#define kPstLstUIModifyMenuItemPosition			2.0	
#define kPstLstUIDeleteMenuItemPosition			3.0
#define	kPstLstUISeparator1MenuItemPosition			10.0
#define kPstLstUIAboutThisMenuItemPosition				11.0

// Initial Data format IDs of the persistent data was first introduced in InDesign CS 2
// we will arbitrarily call the format number "1.0"
#define kPstLstUIInitialMajorFormat		1
#define kPstLstUIInitialMinorFormat		0
// Note: The data format has not been changed since InDesign CS2

// Format IDs for the PluginVersion resource 
#define kPstLstUILastMajorFormatChange	kPstLstUIInitialMajorFormat		// Last major format change
#define kPstLstUILastMinorFormatChange	kPstLstUIInitialMinorFormat		// Last minor format change

#endif // __PstLstUIID_h__
//  Generated by Dolly build 17: template "IfPanelMenu".
// End, PstLstUIID.h.


