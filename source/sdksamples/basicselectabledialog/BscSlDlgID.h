//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicselectabledialog/BscSlDlgID.h $
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
//  Defines IDs used by the BscSlDlg plug-in.
//  
//========================================================================================

#ifndef __BscSlDlgID_h__
#define __BscSlDlgID_h__

#include "SDKDef.h"

// Company:
#define kBscSlDlgCompanyKey	kSDKDefPlugInCompanyKey // Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kBscSlDlgCompanyValue	kSDKDefPlugInCompanyValue // Company name displayed externally.

// Plug-in:
#define kBscSlDlgPluginName	"BasicSelectableDialog" // Name of this plug-in.
#define kBscSlDlgPrefixNumber	0x1D7A00 	// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kBscSlDlgVersion		kSDKDefPluginVersionString // Version of this plug-in (for the About Box).
#define kBscSlDlgAuthor		"Adobe Developer Technologies" // Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kBscSlDlgPrefixNumber above to modify the prefix.)
#define kBscSlDlgPrefix		RezLong(kBscSlDlgPrefixNumber) // The unique numeric prefix for all object model IDs for this plug-in.
#define kBscSlDlgStringPrefix	SDK_DEF_STRINGIZE(kBscSlDlgPrefixNumber) // The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kBscSlDlgPluginID, kBscSlDlgPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kBscSlDlgActionComponentBoss, kBscSlDlgPrefix + 0)
DECLARE_PMID(kClassIDSpace, kBscSlDlgStringRegisterBoss, kBscSlDlgPrefix + 1)
DECLARE_PMID(kClassIDSpace, kBscSlDlgMenuRegisterBoss, kBscSlDlgPrefix + 2)
DECLARE_PMID(kClassIDSpace, kBscSlDlgActionRegisterBoss, kBscSlDlgPrefix + 3)
DECLARE_PMID(kClassIDSpace, kBscSlDlgDialogBoss, kBscSlDlgPrefix + 4)
DECLARE_PMID(kClassIDSpace, kBscSlDlgTabDialogBoss, kBscSlDlgPrefix + 5)
DECLARE_PMID(kClassIDSpace, kYinPanelBoss, kBscSlDlgPrefix + 6)
DECLARE_PMID(kClassIDSpace, kYangPanelBoss, kBscSlDlgPrefix + 7)
DECLARE_PMID(kClassIDSpace, kBscSlDlgIconSuiteButtonWidgetBoss, kBscSlDlgPrefix + 8)
DECLARE_PMID(kClassIDSpace, kBscSlDlgTreeViewWidgetBoss, kBscSlDlgPrefix + 9)

// InterfaceIDs:
// None in this plug-in.

// Implementation IDs:
DECLARE_PMID(kImplementationIDSpace, kBscSlDlgActionComponentImpl, kBscSlDlgPrefix + 0)
//DECLARE_PMID(kImplementationIDSpace, kBscSlDlgDialogControllerImpl, kBscSlDlgPrefix + 1) // obsoleted
DECLARE_PMID(kImplementationIDSpace, kBscSlDlgDialogObserverImpl, kBscSlDlgPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kBscSlDlgDialogCreatorImpl, kBscSlDlgPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kYinPanelCreatorImpl, kBscSlDlgPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kYangPanelCreatorImpl, kBscSlDlgPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kBscSlDlgTabDialogObserverImpl, kBscSlDlgPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kBscSlDlgTabDialogCreatorImpl, kBscSlDlgPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kBscSlDlgTreeViewDlgSwitcherImpl, kBscSlDlgPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kBscSlDlgTreeViewWidgetMgrImpl, kBscSlDlgPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kBscSlDlgTreeViewAdapterImpl, kBscSlDlgPrefix + 10)


// ActionIDs:
DECLARE_PMID(kActionIDSpace, kBscSlDlgAboutActionID, kBscSlDlgPrefix + 0)
DECLARE_PMID(kActionIDSpace, kBscSlDlgDialogActionID, kBscSlDlgPrefix + 1)
DECLARE_PMID(kActionIDSpace, kBscSlDlgTabDialogActionID, kBscSlDlgPrefix + 2)

// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kBscSlDlgDialogWidgetID, kBscSlDlgPrefix + 0)
DECLARE_PMID(kWidgetIDSpace, kBscSlDlgIconSuiteWidgetID, kBscSlDlgPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kYinPanelWidgetID, kBscSlDlgPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kYinPanelStaticTextWidgetID, kBscSlDlgPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kYangPanelWidgetID, kBscSlDlgPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kYangPanelStaticTextWidgetID, kBscSlDlgPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kBscSlDlgTabDialogWidgetID, kBscSlDlgPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kBscSlDlgTreeNodeWidgetID, kBscSlDlgPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kBscSlDlgTreeNodeNameWidgetID, kBscSlDlgPrefix + 8)

// Service IDs
DECLARE_PMID(kServiceIDSpace, kBscSlDlgService, kBscSlDlgPrefix + 0)

// "About Plug-ins" sub-menu:
#define kBscSlDlgAboutMenuKey			kBscSlDlgStringPrefix "kBscSlDlgAboutMenuKey"
#define kBscSlDlgAboutMenuPath			kSDKDefStandardAboutMenuPath kBscSlDlgCompanyKey

// "Plug-ins" sub-menu:
#define kBscSlDlgPluginsMenuKey 		kBscSlDlgStringPrefix "kBscSlDlgPluginsMenuKey"
#define kBscSlDlgPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kBscSlDlgCompanyKey kSDKDefDelimitMenuPath kBscSlDlgPluginsMenuKey

// "Plug-ins" sub-menu item keys:
#define kBscSlDlgDialogMenuItemKey		kBscSlDlgStringPrefix "kBscSlDlgDialogMenuItemKey"
#define kBscSlDlgTabDialogMenuItemKey		kBscSlDlgStringPrefix "kBscSlDlgTabDialogMenuItemKey"

// "Plug-ins" sub-menu item positions:
#define kBscSlDlgDialogMenuItemPosition		1.0
#define kBscSlDlgTabDialogMenuItemPosition	2.0

// Other StringKeys:
#define kBscSlDlgAboutBoxStringKey		kBscSlDlgStringPrefix "kBscSlDlgAboutBoxStringKey"
#define kBscSlDlgDialogTitleKey			kBscSlDlgStringPrefix "kBscSlDlgDialogTitleKey"
#define kYinPanelTitleKey				kBscSlDlgStringPrefix "kYinPanelTitleKey"
#define kYinPanelStaticTextKey		kBscSlDlgStringPrefix "kYinPanelStaticTextKey"
#define kYangPanelTitleKey				kBscSlDlgStringPrefix "kYangPanelTitleKey"
#define kYangPanelStaticTextKey		kBscSlDlgStringPrefix "kYangPanelStaticTextKey"

#define kBscSlDlgPanelOrderingResourceID	700
#define kBscSlDlgDialogResourceID			710
#define kBscSlDlgTabDialogResourceID		711
#define kYinPanelResourceID				720
#define kYinPanelCreatorResourceID		730
#define kYangPanelResourceID				740
#define kYangPanelCreatorResourceID		750

#define kBscSlDlgTreeNodeTreeStyle		800
#define kBscSlDlgTreeNodeRsrcID		810

// Initial data format version numbers
#define kBscSlDlgFirstMajorFormatNumber  kSDKDef_30_PersistMajorVersionNumber
#define kBscSlDlgFirstMinorFormatNumber  kSDKDef_30_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kBscSlDlgCurrentMajorFormatNumber kBscSlDlgFirstMajorFormatNumber // most recent major format change
#define kBscSlDlgCurrentMinorFormatNumber kBscSlDlgFirstMinorFormatNumber // most recent minor format change

#endif // __BscSlDlgID_h__

// End, BscSlDlgID.h.


