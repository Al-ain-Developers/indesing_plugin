//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/singlelinecomposer/SLCID.h $
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
//  Defines IDs used by the SLC plug-in.
//  
//========================================================================================

#ifndef __SLCID_h__
#define __SLCID_h__

#include "SDKDef.h"

// Company:
#define kSLCCompanyKey		kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kSLCCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kSLCPluginName		"SingleLineComposer"			// Name of this plug-in.
#define kSLCPrefixNumber	0x42500 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kSLCVersion			kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kSLCAuthor			"Adobe Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kSLCPrefixNumber above to modify the prefix.)
#define kSLCPrefix			RezLong(kSLCPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kSLCStringPrefix	SDK_DEF_STRINGIZE(kSLCPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// Missing plug-in: (see ExtraPluginInfo resource)
#define kSLCMissingPluginURLValue		kSDKDefPartnersStandardValue_enUS // URL displayed in Missing Plug-in dialog
#define kSLCMissingPluginAlertValue		kSDKDefMissingPluginAlertValue // Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem


// PluginID:
DECLARE_PMID(kPlugInIDSpace, kSLCPluginID, kSLCPrefix + 0)

// ClassIDs:
//DECLARE_PMID(kClassIDSpace, kSLCActionComponentBoss,	kSLCPrefix + 0)// kept here for record keeping purposes (Do not reuse this ID!)
//DECLARE_PMID(kClassIDSpace, kSLCStringRegisterBoss,		kSLCPrefix + 1) // kept for historical reasons - do not reuse
//DECLARE_PMID(kClassIDSpace, kSLCMenuRegisterBoss,		kSLCPrefix + 2) // kept for historical reasons - do not reuse
//DECLARE_PMID(kClassIDSpace, kSLCActionRegisterBoss,		kSLCPrefix + 3) // kept for historical reasons - do not reuse
DECLARE_PMID(kClassIDSpace, kSLCParagraphComposerBoss,	kSLCPrefix + 4)

// InterfaceIDs:
// None in this plug-in.

// ImplementationIDs:
//DECLARE_PMID(kImplementationIDSpace, kSLCActionComponentImpl,		kSLCPrefix + 0)// kept here for record keeping purposes (Do not reuse this ID!)
DECLARE_PMID(kImplementationIDSpace, kSLCServiceProviderImpl,		kSLCPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kSLCParagraphComposerImpl,		kSLCPrefix + 2)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kSLCAboutActionID,				kSLCPrefix + 0)

// WidgetIDs:
// None in this plug-in.
 
// "About Plug-ins" sub-menu:
#define kSLCAboutMenuKey		kSLCStringPrefix "kSLCAboutMenuKey"
#define kSLCAboutMenuPath		kSDKDefStandardAboutMenuPath kSLCCompanyKey

// "Plug-ins" sub-menu:
#define kSLCPluginsMenuKey 		kSLCStringPrefix "kSLCPluginsMenuKey"
#define kSLCPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kSLCCompanyKey kSDKDefDelimitMenuPath kSLCPluginsMenuKey

// Menu item keys:
// none.

// Other StringKeys:
#define kSLCAboutBoxStringKey		kSLCStringPrefix "kSLCAboutBoxStringKey"
#define kSLComposerNameStringKey	kSLCStringPrefix "kSLComposerNameStringKey"

#define kSLCTargetMenuPath 			kSLCPluginsMenuPath

// Initial data format version numbers
#define kSLCFirstMajorFormatNumber  kSDKDef_30_PersistMajorVersionNumber
#define kSLCFirstMinorFormatNumber  kSDKDef_30_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kSLCCurrentMajorFormatNumber kSLCFirstMajorFormatNumber // most recent major format change
#define kSLCCurrentMinorFormatNumber kSLCFirstMinorFormatNumber // most recent minor format change

#endif // __SLCID_h__
// End, SLCID.h.

