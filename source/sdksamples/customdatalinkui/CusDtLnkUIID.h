//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalinkui/CusDtLnkUIID.h $
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

#ifndef __CusDtLnkUIID_h__
#define __CusDtLnkUIID_h__

#include "SDKDef.h"
#include "AdobeMenuPositions.h"

// Company:
#define kCusDtLnkUICompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kCusDtLnkUICompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kCusDtLnkUIPluginName	"CustomDataLinkUI"			// Name of this plug-in.
#define kCusDtLnkUIPrefixNumber	0xb3380 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kCusDtLnkUIVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kCusDtLnkUIAuthor		"Adobe Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kCusDtLnkUIPrefixNumber above to modify the prefix.)
#define kCusDtLnkUIPrefix		RezLong(kCusDtLnkUIPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kCusDtLnkUIStringPrefix	SDK_DEF_STRINGIZE(kCusDtLnkUIPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kCusDtLnkUIPluginID, kCusDtLnkUIPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kCusDtLnkUIActionComponentBoss, kCusDtLnkUIPrefix + 0)
DECLARE_PMID(kClassIDSpace, kCusDtLnkUIPalettePanelWidgetBoss, kCusDtLnkUIPrefix + 1)
DECLARE_PMID(kClassIDSpace, kCusDtLnkUITreeViewWidgetBoss, kCusDtLnkUIPrefix + 4)
DECLARE_PMID(kClassIDSpace, kCusDtLnkUITreeNodeWidgetBoss, kCusDtLnkUIPrefix + 5)
DECLARE_PMID(kClassIDSpace, kCusDtLnkUITreeCViewPanelWidgetBoss, kCusDtLnkUIPrefix + 6)
DECLARE_PMID(kClassIDSpace, kCusDtLnkUIBrowsDialogBoss, kCusDtLnkUIPrefix + 7)
DECLARE_PMID(kClassIDSpace, kCusDtLnkUIDragTargetFlavorHelperBoss, kCusDtLnkUIPrefix + 8)
DECLARE_PMID(kClassIDSpace, kCusDtLnkUIDataExchangeHandlerBoss, kCusDtLnkUIPrefix + 9)
DECLARE_PMID(kClassIDSpace, kCusDtLnkUIPlaceFileDialogBoss, kCusDtLnkUIPrefix + 10)

// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_ICUSDTLNKUIWIDGETOBSERVER, kCusDtLnkUIPrefix + 0)
DECLARE_PMID(kInterfaceIDSpace, IID_ICUSDTLNKUITREESHADOWEVENTHANDLER, kCusDtLnkUIPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ICUSDTLNKUITREEDATAMODEL, kCusDtLnkUIPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ICUSDTLNKUIUNIQUEKEYSTRINGDATA, kCusDtLnkUIPrefix + 3)

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkUIActionComponentImpl, kCusDtLnkUIPrefix + 0 )
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkUITVWidgetMgrImpl, kCusDtLnkUIPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkUITreeObserverImpl, kCusDtLnkUIPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkUITVHierarchyAdapterImpl, kCusDtLnkUIPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkUITreeNodeEHImpl, kCusDtLnkUIPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkUITreeNodeObserverImpl, kCusDtLnkUIPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkUICustomViewImpl, kCusDtLnkUIPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkUITreeDataModelImpl, kCusDtLnkUIPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkUIBrowsDialogObserverImpl, kCusDtLnkUIPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkUIBrowsDialogControllerImpl, kCusDtLnkUIPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkUIDragDropSourceImpl, kCusDtLnkUIPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkUIDataExchangeHandlerImpl, kCusDtLnkUIPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kCusDtLnkUIDDTargetFlavorHelperImpl, kCusDtLnkUIPrefix + 17)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kCusDtLnkUIAboutActionID, kCusDtLnkUIPrefix + 0)
DECLARE_PMID(kActionIDSpace, kCusDtLnkUIPalettePanelWidgetActionID, kCusDtLnkUIPrefix + 5)
DECLARE_PMID(kActionIDSpace, kCusDtLnkUISyncViewActionID, kCusDtLnkUIPrefix + 6)
DECLARE_PMID(kActionIDSpace, kCusDtLnkUIAddNewDBActionID, kCusDtLnkUIPrefix + 7)
DECLARE_PMID(kActionIDSpace, kCusDtLnkUISeparator1ActionID, kCusDtLnkUIPrefix + 8)
DECLARE_PMID(kActionIDSpace, kCusDtLnkUIPopupAboutThisActionID, kCusDtLnkUIPrefix + 9)
DECLARE_PMID(kActionIDSpace, kCusDtLnkUIPlaceFromCSVActionID, kCusDtLnkUIPrefix + 10)
DECLARE_PMID(kActionIDSpace, kCusDtLnkUIRelinkActionID, kCusDtLnkUIPrefix + 11)

// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kCusDtLnkUITreeViewWidgetID, kCusDtLnkUIPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kCusDtLnkUITreeNodeWidgetId, kCusDtLnkUIPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kCusDtLnkUITreeNodeNameWidgetID, kCusDtLnkUIPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kCusDtLnkUITreeElementWidgetId, kCusDtLnkUIPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kCusDtLnkUITreeIconWidgetId, kCusDtLnkUIPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kCusDtLnkUITreeCustomPanelViewWidgetID, kCusDtLnkUIPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kCusDtLnkUITreeTextMessageWidgetID, kCusDtLnkUIPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kCusDtLnkUIPalettePanelWidgetID, kCusDtLnkUIPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kCusDtLnkUIBrowsDialogWidgetID, kCusDtLnkUIPrefix + 17)

// "About Plug-ins" sub-menu:
#define kCusDtLnkUIAboutMenuKey			kCusDtLnkUIStringPrefix "kCusDtLnkUIAboutMenuKey"
#define kCusDtLnkUIAboutMenuPath			kSDKDefStandardAboutMenuPath kCusDtLnkUICompanyKey

// "Plug-ins" sub-menu:
#define kCusDtLnkUIPluginsMenuKey 		kCusDtLnkUIStringPrefix "kCusDtLnkUIPluginsMenuKey"
#define kCusDtLnkUIPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kCusDtLnkUICompanyKey kSDKDefDelimitMenuPath kCusDtLnkUIPluginsMenuKey
#define kCusDtLnkUIRelinkPopupMenuPath 	"#LinksUIPanelMenu"
#define kCusDtLnkUIRelinkContextualMenuPath		"RtMenuLinksUILinkItem"
// Menu item keys:
#define kCusDtLnkUISetOptionsMenuItemKey				kCusDtLnkUIStringPrefix "kCusDtLnkUISetOptionsMenuItemKey"
#define kCusDtLnkUIInternalPopupMenuNameKey kCusDtLnkUIStringPrefix "kCusDtLnkUIInternalPopupMenuNameKey"
#define kCusDtLnkUITargetMenuPath kCusDtLnkUIInternalPopupMenuNameKey
#define kCusDtLnkUISyncViewMenuItemKey				kCusDtLnkUIStringPrefix "kCusDtLnkUISyncViewMenuItemKey"
#define kCusDtLnkUIAddNewDBMenuItemKey				kCusDtLnkUIStringPrefix "kCusDtLnkUIAddNewDBMenuItemKey"
#define kCusDtLnkUIPlaceFromCSVMenuItemKey				kCusDtLnkUIStringPrefix "kCusDtLnkUIPlaceFromCSVMenuItemKey"
#define kCusDtLnkUIRelinkMenuItemKey				kCusDtLnkUIStringPrefix "kCusDtLnkUIRelinkMenuItemKey"

// Other StringKeys:
#define kCusDtLnkUIAboutBoxStringKey				kCusDtLnkUIStringPrefix "kCusDtLnkUIAboutBoxStringKey"
#define kCusDtLnkUIPanelTitleKey					kCusDtLnkUIStringPrefix	"kCusDtLnkUIPanelTitleKey"
#define kCusDtLnkUIStaticTextKey kCusDtLnkUIStringPrefix	"kCusDtLnkUIStaticTextKey"
// Widget label keys
#define kCusDtLnkUIUseCustomDataLinkWidgetKey kCusDtLnkUIStringPrefix "kCusDtLnkUIUseCustomDataLinkWidgetKey"
#define kCusDtLnkUIBaseSettingsTitleTextWidgetKey kCusDtLnkUIStringPrefix "kCusDtLnkUIBaseSettingsTitleTextWidgetKey"

#define kCusDtLnkUIAliasDBFilterStringKey kCusDtLnkUIStringPrefix "kCusDtLnkUIAliasDBFilterStringKey"
#define kCusDtLnkUIChooseFileStringKey kCusDtLnkUIStringPrefix "kCusDtLnkUIChooseFileStringKey"
#define kCusDtLnkUIBrowsDialogTitleKey kCusDtLnkUIStringPrefix "kCusDtLnkUIBrowsDialogTitleKey"
// Menu item positions:

#define kCusDtLnkUIPrefMenuPosition			1540.0

// Separator for 'Main:Edit:Preferences'
// On popup menu
#define kCusDtLnkUISyncViewMenuPosition			1.0
#define kCusDtLnkUIAddNewDBMenuPosition			2.0
#define kCusDtLnkUISeparator1MenuItemPosition	3.0
#define kCusDtLnkUIAboutThisMenuItemPosition	4.0
#define kCusDtLnkUIPlaceFromCSVMenuPosition		5.0
                
#define kCusDtLnkUITreeNodeWidgetRsrcID 	1200

#define kCusDtLnkUILockedPencilIconRsrcID			1512
#define kCusDtLnkUIPenIconRsrcID				1514
#define kCusDtLnkUIBlankIconRsrcID				1515
#define kCusDtLnkUIPenLockedIconRsrcID		1516
// If we add detail control then we can use these
#define kCusDtLnkUIPenSmallIconRsrcID		1517
#define kCusDtLnkUIPenLockedSmallIconRsrcID 1518

// Initial data format version numbers
#define kCusDtLnkUIFirstMajorFormatNumber  RezLong(1)
#define kCusDtLnkUIFirstMinorFormatNumber  RezLong(0)

// Data format version numbers for the PluginVersion resource 
#define kCusDtLnkUICurrentMajorFormatNumber kCusDtLnkUIFirstMajorFormatNumber
#define kCusDtLnkUICurrentMinorFormatNumber kCusDtLnkUIFirstMinorFormatNumber
//
//#define kCusDtLnkUISelecPanelResourceID kSDKDefMenuResourceID + 822
#define kCusDtLnkUIBrowsDialogResourceID kSDKDefMenuResourceID + 832

#define kCusDtLnkUIDragDropCustomFlavor PMFlavor('CDUI')

const int32 kPlaceDialog = 1;
const int32 kRelinkDialog = 2;

#define NEW_LINK_ARCHITECTURE	1
#endif // __CusDtLnkUIID_h__
