//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicshape/BscShpID.h $
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
//  Defines IDs used by the BscShp plug-in.
//  
//========================================================================================

#ifndef __BscShpID_h__
#define __BscShpID_h__

#include "SDKDef.h"

// Company:
#define kBscShpCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kBscShpCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kBscShpPluginName	"BasicShape"			// Name of this plug-in.
#define kBscShpPrefixNumber	0x5D300 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kBscShpVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kBscShpAuthor		"Adobe Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kBscShpPrefixNumber above to modify the prefix.)
#define kBscShpPrefix		RezLong(kBscShpPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kBscShpStringPrefix	SDK_DEF_STRINGIZE(kBscShpPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kBscShpPluginID, kBscShpPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kBscShpActionComponentBoss,	kBscShpPrefix + 0)
// Obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kBscShpStringRegisterBoss,	kBscShpPrefix + 1)
// Obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kBscShpMenuRegisterBoss,	kBscShpPrefix + 2)
// Obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kBscShpActionRegisterBoss,	kBscShpPrefix + 3)
DECLARE_PMID(kClassIDSpace, kBscShpPageItemBoss,		kBscShpPrefix + 4)
DECLARE_PMID(kClassIDSpace, kBscShpScriptProviderBoss,		kBscShpPrefix + 5)
DECLARE_PMID(kClassIDSpace, kBscShpErrorStringServiceBoss,		kBscShpPrefix + 6)

// InterfaceIDs:
// None in this plug-in.

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kBscShpActionComponentImpl,	kBscShpPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kBscShpShapeImpl,				kBscShpPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kBscShpHandleShapeImpl,		kBscShpPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kBscShpPathHandleShapeImpl,	kBscShpPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kBscShpScriptImpl,	kBscShpPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kBscShpScriptProviderImpl,	kBscShpPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kBscShpErrorStringServiceImpl,	kBscShpPrefix + 6)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kBscShpAboutActionID,				kBscShpPrefix + 0)
DECLARE_PMID(kActionIDSpace, kBscShpPlace_PageItemActionID,		kBscShpPrefix + 11)

// WidgetIDs:
// None in this plug-in.

// ScriptElementIDs:
DECLARE_PMID(kScriptInfoIDSpace, kBasicShapeObjectScriptElement, kBscShpPrefix + 0)
DECLARE_PMID(kScriptInfoIDSpace, kTextBasicShapePropertyScriptElement, kBscShpPrefix + 1)

// ErrorIDs:
DECLARE_PMID(kErrorIDSpace, kBscShpFailureErrorCode,			kBscShpPrefix + 0)
DECLARE_PMID(kErrorIDSpace, kBscShpCreatePageItemErrorCode,		kBscShpPrefix + 1)

// Error string keys:
#define kBscShpFailureErrorCodeErrorCodeStringKey		kBscShpStringPrefix "kBscShpFailureErrorCodeErrorCodeStringKey"
#define kBscShpCreatePageItemErrorCodeStringKey		kBscShpStringPrefix "kBscShpCreatePageItemErrorCodeStringKey"

// "About Plug-ins" sub-menu:
#define kBscShpAboutMenuKey			kBscShpStringPrefix "kBscShpAboutMenuKey"
#define kBscShpAboutMenuPath			kSDKDefStandardAboutMenuPath kBscShpCompanyKey

// "Plug-ins" sub-menu:
#define kBscShpPluginsMenuKey 		kBscShpStringPrefix "kBscShpPluginsMenuKey"
#define kBscShpPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kBscShpCompanyKey kSDKDefDelimitMenuPath kBscShpPluginsMenuKey

// Menu item keys:
#define kBscShpPlace_PageItemMenuItemKey		kBscShpStringPrefix "kBscShpPlace_PageItemMenuItemKey"

// Other StringKeys:
#define kBscShpAboutBoxStringKey				kBscShpStringPrefix "kBscShpAboutBoxStringKey"
#define kBscShpPlace_PageItemStringKey			kBscShpStringPrefix "kBscShpPlace_PageItemStringKey"
#define kLockedLayerAlertMessage				kBscShpStringPrefix "kLockedLayerAlertMessage"

#define kBscShpTargetMenuPath					kBscShpPluginsMenuPath

// Menu item positions:
#define kBscShpPlace_PageItemMenuItemPosition	1.0

// Initial data format version numbers
#define kBscShpFirstMajorFormatNumber  kSDKDef_30_PersistMajorVersionNumber
#define kBscShpFirstMinorFormatNumber  kSDKDef_30_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kBscShpCurrentMajorFormatNumber kBscShpFirstMajorFormatNumber // most recent major format change
#define kBscShpCurrentMinorFormatNumber kBscShpFirstMinorFormatNumber // most recent minor format change

#endif // __BscShpID_h__

// End, BscShpID.h.




