//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicpanel/BscPnlID.h $
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
//  Defines IDs used by the BscPnl plug-in.
//  
//========================================================================================

#ifndef __BscPnlID_h__
#define __BscPnlID_h__

#include "SDKDef.h"

// Company:
#define kBscPnlCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kBscPnlCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kBscPnlPluginName	"BasicPanel"	// Name of this plug-in.
#define kBscPnlPrefixNumber	0x40300 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kBscPnlVersion		kSDKDefPluginVersionString			// Version of this plug-in (for the About Box).
#define kBscPnlAuthor		"Adobe Developer Technologies"		// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kBscPnlPrefixNumber above to modify the prefix.)
#define kBscPnlPrefix		RezLong(kBscPnlPrefixNumber)			// The unique numeric prefix for all object model IDs for this plug-in.
#define kBscPnlStringPrefix	SDK_DEF_STRINGIZE(kBscPnlPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kBscPnlPluginID, kBscPnlPrefix + 0)

// ClassIDs:
// Obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kBscPnlPanelRegisterBoss,	kBscPnlPrefix + 0)
// Obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kBscPnlStringRegisterBoss,	kBscPnlPrefix + 1)
DECLARE_PMID(kClassIDSpace, kBscPnlActionComponentBoss,	kBscPnlPrefix + 2)
DECLARE_PMID(kClassIDSpace, kBscPnlPanelWidgetBoss,		kBscPnlPrefix + 3)
// Obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kBscPnlMenuRegisterBoss,	kBscPnlPrefix + 4)
// Obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kBscPnlActionRegisterBoss,	kBscPnlPrefix + 5)

// InterfaceIDs:
// None in this plug-in.

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kBscPnlActionComponentImpl,		kBscPnlPrefix + 0)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kBscPnlAboutActionID,				kBscPnlPrefix + 0)
DECLARE_PMID(kActionIDSpace, kBscPnlPanelWidgetActionID,		kBscPnlPrefix + 1)
DECLARE_PMID(kActionIDSpace, kBscPnlSeparator1ActionID,			kBscPnlPrefix + 2)
DECLARE_PMID(kActionIDSpace, kBscPnlPopupAboutThisActionID,		kBscPnlPrefix + 3)
DECLARE_PMID(kActionIDSpace, kBscPnlGoesNowhereActionID,		kBscPnlPrefix + 11)
DECLARE_PMID(kActionIDSpace, kBscPnlDoesNothingActionID,		kBscPnlPrefix + 12)

// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kBscPnlPanelWidgetID,				kBscPnlPrefix + 0) 
 
// "About Plug-ins" sub-menu:
#define kBscPnlAboutMenuKey			kBscPnlStringPrefix "kBscPnlAboutMenuKey_a"
#define kBscPnlAboutMenuPath		kSDKDefStandardAboutMenuPath kBscPnlCompanyKey

// "Plug-ins" sub-menu:
#define kBscPnlPluginsMenuKey 		kBscPnlStringPrefix "kBscPnlPluginsMenuKey_b"
#define kBscPnlPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kBscPnlCompanyKey kSDKDefDelimitMenuPath kBscPnlPluginsMenuKey

// Menu item keys:
#define kBscPnlGoesNowhereMenuItemKey		kBscPnlStringPrefix "kBscPnlGoesNowhereMenuItemKey_c"
#define kBscPnlDoesNothingMenuItemKey		kBscPnlStringPrefix "kBscPnlDoesNothingMenuItemKey_d"

// Other StringKeys:
#define kBscPnlAboutBoxStringKey			kBscPnlStringPrefix "kBscPnlAboutBoxStringKey_e"
#define kBscPnlGoesNowhereStringKey			kBscPnlStringPrefix "kBscPnlGoesNowhereStringKey_f"
#define kBscPnlDoesNothingStringKey			kBscPnlStringPrefix "kBscPnlDoesNothingStringKey_g"
#define kBscPnlPanelTitleKey				kBscPnlStringPrefix	"kBscPnlPanelTitleKey_h"
#define kBscPnlStaticTextKey				kBscPnlStringPrefix	"kBscPnlStaticTextKey_i"
#define kBscPnlInternalPopupMenuNameKey		kBscPnlStringPrefix	"kBscPnlInternalPopupMenuNameKey_j"
#define kBscPnlTargetMenuPath				kBscPnlInternalPopupMenuNameKey

// Menu item positions:
#define kBscPnlGoesNowhereMenuItemPosition			1.0
#define kBscPnlDoesNothingMenuItemPosition			2.0	
#define	kBscPnlSeparator1MenuItemPosition			10.0
#define kBscPnlAboutThisMenuItemPosition			11.0

// Initial data format version numbers
#define kBscPnlFirstMajorFormatNumber  kSDKDef_30_PersistMajorVersionNumber
#define kBscPnlFirstMinorFormatNumber  kSDKDef_30_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kBscPnlCurrentMajorFormatNumber kBscPnlFirstMajorFormatNumber // most recent major format change
#define kBscPnlCurrentMinorFormatNumber kBscPnlFirstMinorFormatNumber // most recent minor format change

#endif // __BscPnlID_h__

// End, BscPnlID.h.



