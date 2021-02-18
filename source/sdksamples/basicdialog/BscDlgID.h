//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicdialog/BscDlgID.h $
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
//  Defines IDs used by the BscDlg plug-in.
//  
//========================================================================================

#ifndef __BscDlgID_h__
#define __BscDlgID_h__

#include "SDKDef.h"

// Company:
#define kBscDlgCompanyKey	kSDKDefPlugInCompanyKey // Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kBscDlgCompanyValue	kSDKDefPlugInCompanyValue // Company name displayed externally.

// Plug-in:
#define kBscDlgPluginName	"BasicDialog" // Name of this plug-in.
#define kBscDlgPrefixNumber	0x48100 	// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kBscDlgVersion		kSDKDefPluginVersionString // Version of this plug-in (for the About Box).
#define kBscDlgAuthor		"Adobe Developer Technologies" // Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kBscDlgPrefixNumber above to modify the prefix.)
#define kBscDlgPrefix			RezLong(kBscDlgPrefixNumber) // The unique numeric prefix for all object model IDs for this plug-in.
#define kBscDlgStringPrefix	SDK_DEF_STRINGIZE(kBscDlgPrefixNumber) // The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
START_IDS()
DECLARE_PMID(kPlugInIDSpace, kBscDlgPluginID, kBscDlgPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kBscDlgActionComponentBoss, kBscDlgPrefix + 0)
//Start from InDesign 3.0, plug-ins no longer need to provide register bosses for menu, string, action, panel and tool tip.

DECLARE_PMID(kClassIDSpace, kBscDlgDialogBoss, kBscDlgPrefix + 4)

// InterfaceIDs:
// None in this plug-in.

// Implementation IDs:
DECLARE_PMID(kImplementationIDSpace, kBscDlgActionComponentImpl, kBscDlgPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kBscDlgDialogControllerImpl, kBscDlgPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kBscDlgDialogObserverImpl, kBscDlgPrefix + 2)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kBscDlgAboutActionID, kBscDlgPrefix + 0)
DECLARE_PMID(kActionIDSpace, kBscDlgDialogActionID, kBscDlgPrefix + 1)

// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kBscDlgDialogWidgetID, kBscDlgPrefix + 0)
DECLARE_PMID(kWidgetIDSpace, kBscDlgIconSuiteWidgetID, kBscDlgPrefix + 1)
END_IDS()

// "About Plug-ins" sub-menu:
#define kBscDlgAboutMenuKey			kBscDlgStringPrefix "kBscDlgAboutMenuKey"
#define kBscDlgAboutMenuPath			kSDKDefStandardAboutMenuPath kBscDlgCompanyKey

// "Plug-ins" sub-menu:
#define kBscDlgPluginsMenuKey 		kBscDlgStringPrefix "kBscDlgPluginsMenuKey"
#define kBscDlgPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kBscDlgCompanyKey

// "Plug-ins" sub-menu item keys:
#define kBscDlgDialogMenuItemKey		kBscDlgStringPrefix "kBscDlgDialogMenuItemKey"

// "Plug-ins" sub-menu item positions:
#define kBscDlgDialogMenuItemPosition	1.0

// Other StringKeys:
#define kBscDlgDialogTitleKey			kBscDlgStringPrefix "kBscDlgDialogTitleKey"
#define kBscDlgAboutBoxStringKey		kBscDlgStringPrefix "kBscDlgAboutBoxStringKey"

// Initial data format version numbers
#define kBscDlgFirstMajorFormatNumber  kSDKDef_30_PersistMajorVersionNumber
#define kBscDlgFirstMinorFormatNumber  kSDKDef_30_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kBscDlgCurrentMajorFormatNumber kBscDlgFirstMajorFormatNumber // most recent major format change
#define kBscDlgCurrentMinorFormatNumber kBscDlgFirstMinorFormatNumber // most recent minor format change

#endif // __BscDlgID_h__

// End, BscDlgID.h.



