//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicmenu/BscMnuID.h $
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
//  Defines IDs used by the BscMnu plug-in.
//  
//========================================================================================

#ifndef __BscMnuID_h__
#define __BscMnuID_h__

#include "SDKDef.h"

// Company:
#define kBscMnuCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kBscMnuCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kBscMnuPluginName	"BasicMenu"			// Name of this plug-in.
#define kBscMnuPrefixNumber	0x57200 			// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kBscMnuVersion		kSDKDefPluginVersionString				// Version of this plug-in (for the About Box).
#define kBscMnuAuthor		"Adobe Developer Technologies"			// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kBscMnuPrefixNumber above to modify the prefix.)
#define kBscMnuPrefix		RezLong(kBscMnuPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kBscMnuStringPrefix	SDK_DEF_STRINGIZE(kBscMnuPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kBscMnuPluginID, kBscMnuPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kBscMnuActionComponentBoss,	kBscMnuPrefix + 0)
// Obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kBscMnuStringRegisterBoss,	kBscMnuPrefix + 1)
// Obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kBscMnuPanelRegisterBoss,	kBscMnuPrefix + 2)
// Obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kBscMnuMenuRegisterBoss,	kBscMnuPrefix + 3)
// Obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kBscMnuActionRegisterBoss,	kBscMnuPrefix + 4)
DECLARE_PMID(kClassIDSpace, kBscMnuPanelWidgetBoss,		kBscMnuPrefix + 5)

// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_IBSCMNU_ISUITE, kBscMnuPrefix + 1)	

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kBscMnuActionComponentImpl,		kBscMnuPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kBscMnuSuiteASBImpl,		kBscMnuPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kBscMnuSuiteLayoutCSBImpl,		kBscMnuPrefix + 2)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kBscMnuAboutActionID,				kBscMnuPrefix + 0)
DECLARE_PMID(kActionIDSpace, kBscMnuPanelWidgetActionID,		kBscMnuPrefix + 1)
DECLARE_PMID(kActionIDSpace, kBscMnuSeparator1ActionID,			kBscMnuPrefix + 2)
DECLARE_PMID(kActionIDSpace, kBscMnuPopupAboutThisActionID,		kBscMnuPrefix + 3)
DECLARE_PMID(kActionIDSpace, kBscMnuAlwaysOnActionID,			kBscMnuPrefix + 11)
DECLARE_PMID(kActionIDSpace, kBscMnuOnIfFrontDocActionID,		kBscMnuPrefix + 12)
DECLARE_PMID(kActionIDSpace, kBscMnuNeedsSelectionActionID,		kBscMnuPrefix + 13)
// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kBscMnuPanelWidgetID,				kBscMnuPrefix + 0) 
 
// "About Plug-ins" sub-menu:
#define kBscMnuAboutMenuKey				kBscMnuStringPrefix "kBscMnuAboutMenuKey"
#define kBscMnuAboutMenuPath			kSDKDefStandardAboutMenuPath kBscMnuCompanyKey

// "Plug-ins" sub-menu:
#define kBscMnuPluginsMenuKey 			kBscMnuStringPrefix "kBscMnuPluginsMenuKey"
#define kBscMnuPluginsMenuPath			kSDKDefPlugInsStandardMenuPath kBscMnuCompanyKey kSDKDefDelimitMenuPath kBscMnuPluginsMenuKey

// Menu item keys:
#define kBscMnuAlwaysOnMenuItemKey			kBscMnuStringPrefix "kBscMnuAlwaysOnMenuItemKey"
#define kBscMnuOnIfFrontDocMenuItemKey		kBscMnuStringPrefix "kBscMnuOnIfFrontDocMenuItemKey"
#define kBscMnuNeedsSelectionMenuItemKey	kBscMnuStringPrefix "kBscMnuNeedsSelectionMenuItemKey"

// Other StringKeys:
#define kBscMnuAboutBoxStringKey				kBscMnuStringPrefix "kBscMnuAboutBoxStringKey"
#define kBscMnuAlwaysOnStringKey				kBscMnuStringPrefix "kBscMnuAlwaysOnStringKey"
#define kBscMnuOnIfFrontDocStringKey			kBscMnuStringPrefix "kBscMnuOnIfFrontDocStringKey"
#define kBscMnuNeedsSelectionStringKey			kBscMnuStringPrefix "kBscMnuNeedsSelectionStringKey_"

#define kBscMnuTargetMenuPath kBscMnuPluginsMenuPath

// Menu item positions:
#define kBscMnuAlwaysOnMenuItemPosition			1.0
#define kBscMnuOnIfFrontDocMenuItemPosition		2.0	
#define kBscMnuNeedsSelectionMenuItemPosition	3.0

// Initial data format version numbers
#define kBscMnuFirstMajorFormatNumber  kSDKDef_30_PersistMajorVersionNumber
#define kBscMnuFirstMinorFormatNumber  kSDKDef_30_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kBscMnuCurrentMajorFormatNumber kBscMnuFirstMajorFormatNumber // most recent major format change
#define kBscMnuCurrentMinorFormatNumber kBscMnuFirstMinorFormatNumber // most recent minor format change

#endif // __BscMnuID_h__

// End, BscMnuID.h.



