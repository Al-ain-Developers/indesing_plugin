//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/docwatch/DocWchID.h $
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
//  Defines IDs used by the DocWch plug-in.
//  
//========================================================================================

#ifndef __DocWchID_h__
#define __DocWchID_h__

#include "SDKDef.h"

// Company:
#define kDocWchCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kDocWchCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kDocWchPluginName	"DocWatch"				// Name of this plug-in.
#define kDocWchPrefixNumber	0x42B00 				// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kDocWchVersion		kSDKDefPluginVersionString					// Version of this plug-in (for the About Box).
#define kDocWchAuthor		"Adobe Developer Technologies"				// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kDocWchPrefixNumber above to modify the prefix.)
#define kDocWchPrefix		RezLong(kDocWchPrefixNumber)				// Unique numeric prefix for all object model IDs for this plug-in.
#define kDocWchStringPrefix	SDK_DEF_STRINGIZE(kDocWchPrefixNumber)	// String equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kDocWchPluginID, kDocWchPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kDocWchActionComponentBoss,	kDocWchPrefix + 0)
DECLARE_PMID(kClassIDSpace, kDocWchStringRegisterBoss,	kDocWchPrefix + 1)
DECLARE_PMID(kClassIDSpace, kDocWchMenuRegisterBoss,	kDocWchPrefix + 2)
DECLARE_PMID(kClassIDSpace, kDocWchActionRegisterBoss,	kDocWchPrefix + 3)
DECLARE_PMID(kClassIDSpace, kDocWchResponderServiceBoss,	kDocWchPrefix + 4)

// InterfaceIDs:
// None in this plug-in.

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kDocWchActionComponentImpl,	kDocWchPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kDocWchResponderImpl,			kDocWchPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kDocWchServiceProviderImpl,	kDocWchPrefix + 2)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kDocWchAboutActionID,				kDocWchPrefix + 0)
DECLARE_PMID(kActionIDSpace, kDocWchPopupAboutThisActionID,		kDocWchPrefix + 1)
DECLARE_PMID(kActionIDSpace, kDocWchUseResponderActionID,		kDocWchPrefix + 2)

// WidgetIDs:
// None in this plug-in.
 
// "About Plug-ins" sub-menu:
#define kDocWchAboutMenuKey			kDocWchStringPrefix "kDocWchAboutMenuKey"
#define kDocWchAboutMenuPath		kSDKDefStandardAboutMenuPath kDocWchCompanyKey

// "Plug-ins" sub-menu:
#define kDocWchPluginsMenuKey 		kDocWchStringPrefix "kDocWchPluginsMenuKey"
#define kDocWchPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kDocWchCompanyKey kSDKDefDelimitMenuPath kDocWchPluginsMenuKey

// Menu item keys:
#define kDocWchUseResponderMenuItemKey		kDocWchStringPrefix "kDocWchUseResponderMenuItemKey"

// Menu item paths:
#define kDocWchTargetMenuPath kDocWchPluginsMenuPath

// Menu item positions:
#define kDocWchUseResponderMenuItemPosition			1.0

// Other StringKeys:
#define kDocWchAboutBoxStringKey			kDocWchStringPrefix "kDocWchAboutBoxStringKey"

#define kBeforeNewDocSignalStringKey		kDocWchStringPrefix "kBeforeNewDocSignalStringKey"
#define kDuringNewDocSignalStringKey		kDocWchStringPrefix "kDuringNewDocSignalStringKey"
#define kAfterNewDocSignalStringKey			kDocWchStringPrefix "kAfterNewDocSignalStringKey"
#define kBeforeOpenDocSignalStringKey		kDocWchStringPrefix "kBeforeOpenDocSignalStringKey"
#define kDuringOpenDocSignalStringKey		kDocWchStringPrefix "kDuringOpenDocSignalStringKey"
#define kAfterOpenDocSignalStringKey		kDocWchStringPrefix "kAfterOpenDocSignalStringKey"
#define kBeforeSaveDocSignalStringKey		kDocWchStringPrefix "kBeforeSaveDocSignalStringKey"
#define kAfterSaveDocSignalStringKey		kDocWchStringPrefix "kAfterSaveDocSignalStringKey"
#define kBeforeSaveAsDocSignalStringKey		kDocWchStringPrefix "kBeforeSaveAsDocSignalStringKey"
#define kAfterSaveAsDocSignalStringKey		kDocWchStringPrefix "kAfterSaveAsDocSignalStringKey"
#define kBeforeSaveACopyDocSignalStringKey	kDocWchStringPrefix "kBeforeSaveACopyDocSignalStringKey"
#define kDuringSaveACopyDocSignalStringKey	kDocWchStringPrefix "kDuringSaveACopyDocSignalStringKey"
#define kAfterSaveACopyDocSignalStringKey	kDocWchStringPrefix "kAfterSaveACopyDocSignalStringKey"
#define kBeforeRevertDocSignalStringKey		kDocWchStringPrefix "kBeforeRevertDocSignalStringKey"
#define kAfterRevertDocSignalStringKey		kDocWchStringPrefix "kAfterRevertDocSignalStringKey"
#define kBeforeCloseDocSignalStringKey		kDocWchStringPrefix "kBeforeCloseDocSignalStringKey"
#define kAfterCloseDocSignalStringKey		kDocWchStringPrefix "kAfterCloseDocSignalStringKey"

// Initial data format version numbers
#define kDocWchFirstMajorFormatNumber  kSDKDef_30_PersistMajorVersionNumber
#define kDocWchFirstMinorFormatNumber  kSDKDef_30_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kDocWchCurrentMajorFormatNumber kDocWchFirstMajorFormatNumber // most recent major format change
#define kDocWchCurrentMinorFormatNumber kDocWchFirstMinorFormatNumber // most recent minor format change

#endif // __DocWchID_h__

// End, DocWchID.h.


