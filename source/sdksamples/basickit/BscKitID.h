//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basickit/BscKitID.h $
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
//  Defines IDs used by the BscKit plug-in.
//  
//========================================================================================

#ifndef __BscKitID_h__
#define __BscKitID_h__

#include "SDKDef.h"

// Company:
#define kBscKitCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kBscKitCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kBscKitPluginName	"BasicKit"			// Name of this plug-in.
#define kBscKitPrefixNumber	0x78400 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kBscKitVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kBscKitAuthor		"Adobe Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kBscKitPrefixNumber above to modify the prefix.)
#define kBscKitPrefix		RezLong(kBscKitPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kBscKitStringPrefix	SDK_DEF_STRINGIZE(kBscKitPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kBscKitPluginID, kBscKitPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kBscKitActionComponentBoss,	kBscKitPrefix + 0)
DECLARE_PMID(kClassIDSpace, kBscKitWidgetBoss,		kBscKitPrefix + 1)

// InterfaceIDs:
// None in this plug-in.

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kBscKitActionComponentImpl,		kBscKitPrefix + 0)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kBscKitAboutActionID,				kBscKitPrefix + 0)
DECLARE_PMID(kActionIDSpace, kBscKitWidgetActionID,				kBscKitPrefix + 1)
DECLARE_PMID(kActionIDSpace, kBscKitSeparator1ActionID,			kBscKitPrefix + 2)
DECLARE_PMID(kActionIDSpace, kBscKitPopupAboutThisActionID,		kBscKitPrefix + 3)

// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kBscKitWidgetID,							kBscKitPrefix + 0)
DECLARE_PMID(kWidgetIDSpace, kBscKitPanelViewWidgetID,					kBscKitPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kBscKitPanelViewFirstControlSetWidgetID,	kBscKitPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kBscKitPanelViewSecondControlSetWidgetID,	kBscKitPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kBscKitHorzDockBarViewWidgetID,			kBscKitPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kBscKitVertDockBarViewWidgetID,			kBscKitPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kBscKitDockBarViewFirstControlSetWidgetID,	kBscKitPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kBscKitDockBarViewSecondControlSetWidgetID,kBscKitPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kBscKitControl1WidgetID,					kBscKitPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kBscKitControl2WidgetID,					kBscKitPrefix + 9)

// "About Plug-ins" sub-menu:
#define kBscKitAboutMenuKey			kBscKitStringPrefix "kBscKitAboutMenuKey"
#define kBscKitAboutMenuPath		kSDKDefStandardAboutMenuPath kBscKitCompanyKey

// "Plug-ins" sub-menu:
#define kBscKitPluginsMenuKey 		kBscKitStringPrefix "kBscKitPluginsMenuKey"
#define kBscKitPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kBscKitCompanyKey kSDKDefDelimitMenuPath kBscKitPluginsMenuKey

// Menu item keys:

// Other StringKeys:
#define kBscKitAboutBoxStringKey				kBscKitStringPrefix "kBscKitAboutBoxStringKey"
#define kBscKitPanelTitleKey					kBscKitStringPrefix	"kBscKitPanelTitleKey"
#define kBscKitInternalPopupMenuNameKey			kBscKitStringPrefix	"kBscKitInternalPopupMenuNameKey"
#define kBscKitTargetMenuPath					kBscKitInternalPopupMenuNameKey

#define kBscKitFirstControlSetTitleKey			kBscKitStringPrefix	"kBscKitFirstControlSetTitleKey"
#define kBscKitSecondControlSetTitleKey			kBscKitStringPrefix	"kBscKitSecondControlSetTitleKey"

#define kBscKitControl1LabelLongStringKey		kBscKitStringPrefix "kBscKitControl1LabelLongStringKey"
#define kBscKitControl1LabelShortStringKey		kBscKitStringPrefix "kBscKitControl1LabelShortStringKey"
#define kBscKitControl2LabelLongStringKey		kBscKitStringPrefix "kBscKitControl2LabelLongStringKey"
#define kBscKitControl2LabelShortStringKey		kBscKitStringPrefix "kBscKitControl2LabelShortStringKey"

// Menu item positions:
#define	kBscKitSeparator1MenuItemPosition			10.0
#define kBscKitAboutThisMenuItemPosition				11.0

// Initial data format version numbers
#define kBscKitFirstMajorFormatNumber  kSDKDef_30_PersistMajorVersionNumber
#define kBscKitFirstMinorFormatNumber  kSDKDef_30_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kBscKitCurrentMajorFormatNumber kBscKitFirstMajorFormatNumber // most recent major format change
#define kBscKitCurrentMinorFormatNumber kBscKitFirstMinorFormatNumber // most recent minor format change

#endif // __BscKitID_h__

// End, BscKitID.h.



