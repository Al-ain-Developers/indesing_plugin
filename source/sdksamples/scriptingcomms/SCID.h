//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/scriptingcomms/SCID.h $
//  
//  Owner: Timothy Brand-Spencer
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2012 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================


#ifndef __SCID_h__
#define __SCID_h__

#include "SDKDef.h"

// Company:
#define kSCCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kSCCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kSCPluginName	"ScriptingComms.sdk"			// Name of this plug-in.
#define kSCPrefixNumber	0x1D7900 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kSCVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kSCAuthor		"Timothy Brand-Spencer"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kSCPrefixNumber above to modify the prefix.)
#define kSCPrefix		RezLong(kSCPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kSCStringPrefix	SDK_DEF_STRINGIZE(kSCPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// Missing plug-in: (see ExtraPluginInfo resource)
#define kSCMissingPluginURLValue		kSDKDefPartnersStandardValue_enUS // URL displayed in Missing Plug-in dialog
#define kSCMissingPluginAlertValue	kSDKDefMissingPluginAlertValue // Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kSCPluginID, kSCPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kSCScriptProviderBoss, kSCPrefix + 3)
DECLARE_PMID(kClassIDSpace, kSCStartupShutdownServiceBoss, kSCPrefix + 4)

// InterfaceIDs:
//DECLARE_PMID(kInterfaceIDSpace, IID_ISCINTERFACE, kSCPrefix + 0)

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kSCScriptProviderImpl, kSCPrefix + 0 )
DECLARE_PMID(kImplementationIDSpace, kSCStartupShutdownImpl, kSCPrefix + 1)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kSCAboutActionID, kSCPrefix + 0)

// WidgetIDs:
//DECLARE_PMID(kWidgetIDSpace, kSCWidgetID, kSCPrefix + 2)

//Script Element IDs
DECLARE_PMID(kScriptInfoIDSpace, kSCMethodScriptElement, kSCPrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kSCPropertyScriptElement, kSCPrefix + 2)

// "About Plug-ins" sub-menu:
#define kSCAboutMenuKey			kSCStringPrefix "kSCAboutMenuKey"
#define kSCAboutMenuPath		kSDKDefStandardAboutMenuPath kSCCompanyKey

// "Plug-ins" sub-menu:
#define kSCPluginsMenuKey 		kSCStringPrefix "kSCPluginsMenuKey"
#define kSCPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kSCCompanyKey kSDKDefDelimitMenuPath kSCPluginsMenuKey

// Menu item keys:

// Other StringKeys:
#define kSCAboutBoxStringKey	kSCStringPrefix "kSCAboutBoxStringKey"
#define kSCTargetMenuPath		kSCPluginsMenuPath
#define kSCMessageStringKey		kSCStringPrefix "kSCMessageStringKey"

// Initial data format version numbers
#define kSCFirstMajorFormatNumber  RezLong(1)
#define kSCFirstMinorFormatNumber  RezLong(0)

// Data format version numbers for the PluginVersion resource 
#define kSCCurrentMajorFormatNumber kSCFirstMajorFormatNumber
#define kSCCurrentMinorFormatNumber kSCFirstMinorFormatNumber

#endif // __SCID_h__
