//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/dynamicmenu/DynMnuID.h $
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
//  Defines IDs used by the DynMnu plug-in.
//  
//========================================================================================

#ifndef __DynMnuID_h__
#define __DynMnuID_h__

#include "SDKDef.h"

// Company:
#define kDynMnuCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kDynMnuCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kDynMnuPluginName	"DynamicMenu"			// Name of this plug-in.
#define kDynMnuPrefixNumber	0x5C900 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kDynMnuVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kDynMnuAuthor		"Adobe Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kDynMnuPrefixNumber above to modify the prefix.)
#define kDynMnuPrefix		RezLong(kDynMnuPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kDynMnuStringPrefix	SDK_DEF_STRINGIZE(kDynMnuPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kDynMnuPluginID, kDynMnuPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kDynMnuActionComponentBoss,	kDynMnuPrefix + 0)

// InterfaceIDs:
// None in this plug-in.

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kDynMnuActionComponentImpl,		kDynMnuPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kDynMnuDynamicMenuImpl,			kDynMnuPrefix + 1)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kDynMnuAboutActionID,					kDynMnuPrefix + 0)
DECLARE_PMID(kActionIDSpace, kDynMnuStaticMenuActionID,				kDynMnuPrefix + 1)
DECLARE_PMID(kActionIDSpace, kDynMnuPlaceholderActionID,			kDynMnuPrefix + 10) // Placeholder in static resource defs
DECLARE_PMID(kActionIDSpace, kDynMnuSeparatorActionID,				kDynMnuPrefix + 11) // Dyn Sep
DECLARE_PMID(kActionIDSpace, kDynMnuFirstDynamicActionID,			kDynMnuPrefix + 12) // Starting point for dyn actions

// WidgetIDs:
 
// "About Plug-ins" sub-menu:
#define kDynMnuAboutMenuKey			kDynMnuStringPrefix "kDynMnuAboutMenuKey"
#define kDynMnuAboutMenuPath		kSDKDefStandardAboutMenuPath kDynMnuCompanyKey

// "Plug-ins" sub-menu:
#define kDynMnuPluginsMenuKey 		kDynMnuStringPrefix "kDynMnuPluginsMenuKey"
#define kDynMnuPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kDynMnuCompanyKey kSDKDefDelimitMenuPath kDynMnuPluginsMenuKey
#define kDynMnuTargetMenuPath		kDynMnuPluginsMenuPath

// Menu item keys:
#define kDynMnuStaticMenuEntryItemKey			kDynMnuStringPrefix "kDynMnuStaticMenuEntryItemKey"
#define kDynMnuSubMenuStringKey					kDynMnuStringPrefix "kDynMnuSubMenuStringKey"

// Other StringKeys:
#define kDynMnuAboutBoxStringKey				kDynMnuStringPrefix "kDynMnuAboutBoxStringKey"
#define kDynMnuNumSpreadsStringKey				kDynMnuStringPrefix "kDynMnuNumSpreadsStringKey"

#define kDynMnuStaticMenuEntryStringKey			kDynMnuStringPrefix "kDynMnuStaticMenuEntryStringKey"

// Menu item positions:
#define kDynMnuStaticMenuItemPosition			1.0
#define kDynMnuSeparatorPosition				10.0	// Sep for dyn menus
#define kDynMnuItemBasePosition					11.0	// Start pos for dyn menus

// Initial data format version numbers
#define kDynMnuFirstMajorFormatNumber  kSDKDef_30_PersistMajorVersionNumber
#define kDynMnuFirstMinorFormatNumber  kSDKDef_30_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kDynMnuCurrentMajorFormatNumber kDynMnuFirstMajorFormatNumber // most recent major format change
#define kDynMnuCurrentMinorFormatNumber kDynMnuFirstMinorFormatNumber // most recent minor format change

#endif // __DynMnuID_h__

// End, DynMnuID.h.



