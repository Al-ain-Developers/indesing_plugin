//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customconditionaltextui/CusCondTxtUIID.h $
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
//========================================================================================

#ifndef __CusCondTxtUIID_h__
#define __CusCondTxtUIID_h__

#include "SDKDef.h"

// Company:
#define kCusCondTxtUICompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kCusCondTxtUICompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kCusCondTxtUIPluginName	"CustomConditionalTextUI"			// Name of this plug-in.
#define kCusCondTxtUIPrefixNumber	0x13e000 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kCusCondTxtUIVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kCusCondTxtUIAuthor		"Adobe Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kCusCondTxtUIPrefixNumber above to modify the prefix.)
#define kCusCondTxtUIPrefix		RezLong(kCusCondTxtUIPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kCusCondTxtUIStringPrefix	SDK_DEF_STRINGIZE(kCusCondTxtUIPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// Missing plug-in: (see ExtraPluginInfo resource)
#define kCusCondTxtMissingPluginURLValue		kSDKDefPartnersStandardValue_enUS // URL displayed in Missing Plug-in dialog
#define kCusCondTxtMissingPluginAlertValue	kSDKDefMissingPluginAlertValue // Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kCusCondTxtUIPluginID, kCusCondTxtUIPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kCusCondTxtUIActionComponentBoss, kCusCondTxtUIPrefix + 0)
DECLARE_PMID(kClassIDSpace, kCusCondTxtUIPanelWidgetBoss, kCusCondTxtUIPrefix + 1)
DECLARE_PMID(kClassIDSpace, kCusCondTxtUITreeViewWidgetBoss, kCusCondTxtUIPrefix + 5)
DECLARE_PMID(kClassIDSpace, kCusCondTxtUIIconBoss, kCusCondTxtUIPrefix + 6)
DECLARE_PMID(kClassIDSpace, kCusCondTxtUITreeViewNodeWidgetBoss, kCusCondTxtUIPrefix + 7)


// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kCusCondTxtUIActionComponentImpl, kCusCondTxtUIPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kCusCondTxtUIPrintVisibleImpl, kCusCondTxtUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kCusCondTxtUIIdmlVisibleImpl, kCusCondTxtUIPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kCusCondTxtUITreeViewHierarchyAdapterImpl, kCusCondTxtUIPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kCusCondTxtUITreeViewWidgetMgrImpl, kCusCondTxtUIPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kCusCondTxtUIIconEventHandlerImpl, kCusCondTxtUIPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kCusCondTxtUIIconTipImpl, kCusCondTxtUIPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kCusCondTxtUITreeViewObserverImpl, kCusCondTxtUIPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kCusCondTxtUITurnOffStateImpl, kCusCondTxtUIPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kCusCondTxtUIPanelViewImpl, kCusCondTxtUIPrefix + 9)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kCusCondTxtUIAboutActionID, kCusCondTxtUIPrefix + 0)
DECLARE_PMID(kActionIDSpace, kCusCondTxtUIPanelWidgetActionID, kCusCondTxtUIPrefix + 1)
DECLARE_PMID(kActionIDSpace, kCusCondTxtUISeparator1ActionID, kCusCondTxtUIPrefix + 2)
DECLARE_PMID(kActionIDSpace, kCusCondTxtUIPopupAboutThisActionID, kCusCondTxtUIPrefix + 3)
DECLARE_PMID(kActionIDSpace, kCusCondTxtUIListConditionsActionID, kCusCondTxtUIPrefix + 4)
DECLARE_PMID(kActionIDSpace, kCusCondTxtUIListHiddenTextActionID, kCusCondTxtUIPrefix + 5)

// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kCusCondTxtPanelWidgetID, kCusCondTxtUIPrefix + 0)
DECLARE_PMID(kWidgetIDSpace, kCusCondTxtInfoPanelWidgetID, kCusCondTxtUIPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kCusCondTxtTreeViewWidgetID, kCusCondTxtUIPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kCusCondTxtTreeNodeWidgetId, kCusCondTxtUIPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kConditionTagIsPrintedStateWidgetId, kCusCondTxtUIPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kConditionTagIsIdmlStateWidgetId, kCusCondTxtUIPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kCusCondTxtMultiLineStaticTextWidgetID, kCusCondTxtUIPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kCusCondTxtInfoScrollBarWidgetID, kCusCondTxtUIPrefix + 9)


// "About Plug-ins" sub-menu:
#define kCusCondTxtUIAboutMenuKey			kCusCondTxtUIStringPrefix "kCusCondTxtUIAboutMenuKey"
#define kCusCondTxtUIAboutMenuPath		kSDKDefStandardAboutMenuPath kCusCondTxtUICompanyKey

// "Plug-ins" sub-menu:
#define kCusCondTxtUIPluginsMenuKey 		kCusCondTxtUIStringPrefix "kCusCondTxtUIPluginsMenuKey"
#define kCusCondTxtUIPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kCusCondTxtUICompanyKey kSDKDefDelimitMenuPath kCusCondTxtUIPluginsMenuKey

// Menu item keys:
#define kCusCondTxtUIListConditionsMenuKey kCusCondTxtUIStringPrefix "kCusCondTxtUIListConditionsMenuKey"
#define kCusCondTxtUIListHiddenTextMenuKey kCusCondTxtUIStringPrefix "kCusCondTxtUIListHiddenTextMenuKey"

// Other StringKeys:
#define kCusCondTxtUIAboutBoxStringKey	kCusCondTxtUIStringPrefix "kCusCondTxtUIAboutBoxStringKey"
#define kCusCondTxtUIPanelTitleKey					kCusCondTxtUIStringPrefix	"kCusCondTxtUIPanelTitleKey"
#define kCusCondTxtUIStaticTextKey kCusCondTxtUIStringPrefix	"kCusCondTxtUIStaticTextKey"
#define kCusCondTxtUIInternalPopupMenuNameKey kCusCondTxtUIStringPrefix	"kCusCondTxtUIInternalPopupMenuNameKey"
#define kCusCondTxtUITargetMenuPath kCusCondTxtUIInternalPopupMenuNameKey
#define kCusCondTxtUIPrintedIconVisibleStringKey	kCusCondTxtUIStringPrefix "kCusCondTxtUIPrintedIconVisibleStringKey"
#define kCusCondTxtUIPrintedIconInvisibleStringKey	kCusCondTxtUIStringPrefix "kCusCondTxtUIPrintedIconInvisibleStringKey"
#define kCusCondTxtUIIdmlIconVisibleStringKey 	kCusCondTxtUIStringPrefix "kCusCondTxtUIIdmlIconVisibleStringKey"
#define kCusCondTxtUIIdmlIconInvisibleStringKey 	kCusCondTxtUIStringPrefix "kCusCondTxtUIIdmlIconInvisibleStringKey"

// Menu item positions:

#define kCusCondTxtUIListConditionsMenuItemPosition 8.0
#define kCusCondTxtUIListHiddenTextMenuItemPosition 9.0
#define	kCusCondTxtUISeparator1MenuItemPosition    10.0
#define kCusCondTxtUIAboutThisMenuItemPosition     11.0


// Initial data format version numbers
#define kCusCondTxtUIFirstMajorFormatNumber  RezLong(1)
#define kCusCondTxtUIFirstMinorFormatNumber  RezLong(0)

// Data format version numbers for the PluginVersion resource 
#define kCusCondTxtUICurrentMajorFormatNumber kCusCondTxtUIFirstMajorFormatNumber
#define kCusCondTxtUICurrentMinorFormatNumber kCusCondTxtUIFirstMinorFormatNumber

#endif // __CusCondTxtUIID_h__

