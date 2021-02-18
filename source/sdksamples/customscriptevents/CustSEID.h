//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customscriptevents/CustSEID.h $
//  
//  Owner: Heath Lynn
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
//========================================================================================

#ifndef __CustSEID_h__
#define __CustSEID_h__

#include "SDKDef.h"

// Company:
#define kCustSECompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kCustSECompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kCustSEPluginName	"CustomScriptEvents"			// Name of this plug-in.
#define kCustSEPrefixNumber	0x146e00 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kCustSEVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kCustSEAuthor		"Heath Lynn"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kCustSEPrefixNumber above to modify the prefix.)
#define kCustSEPrefix		RezLong(kCustSEPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kCustSEStringPrefix	SDK_DEF_STRINGIZE(kCustSEPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// Missing plug-in: (see ExtraPluginInfo resource)
#define kCustSEMissingPluginURLValue		kSDKDefPartnersStandardValue_enUS // URL displayed in Missing Plug-in dialog
#define kCustSEMissingPluginAlertValue	kSDKDefMissingPluginAlertValue // Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kCustSEPluginID, kCustSEPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kCustSEScriptObserverBoss, kCustSEPrefix + 0)
//DECLARE_PMID(kClassIDSpace, kCustSEBoss, kCustSEPrefix + 1)
//DECLARE_PMID(kClassIDSpace, kCustSEBoss, kCustSEPrefix + 2)
//DECLARE_PMID(kClassIDSpace, kCustSEBoss, kCustSEPrefix + 3)
//DECLARE_PMID(kClassIDSpace, kCustSEBoss, kCustSEPrefix + 4)
//DECLARE_PMID(kClassIDSpace, kCustSEBoss, kCustSEPrefix + 5)


// InterfaceIDs:
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTSEINTERFACE, kCustSEPrefix + 0)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTSEINTERFACE, kCustSEPrefix + 1)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTSEINTERFACE, kCustSEPrefix + 2)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTSEINTERFACE, kCustSEPrefix + 3)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTSEINTERFACE, kCustSEPrefix + 4)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTSEINTERFACE, kCustSEPrefix + 5)


// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kCustSEObserverImpl, kCustSEPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kCustSEStartupShutdownImpl, kCustSEPrefix + 1)
//DECLARE_PMID(kImplementationIDSpace, kCustSEImpl, kCustSEPrefix + 2)
//DECLARE_PMID(kImplementationIDSpace, kCustSEImpl, kCustSEPrefix + 3)
//DECLARE_PMID(kImplementationIDSpace, kCustSEImpl, kCustSEPrefix + 4)
//DECLARE_PMID(kImplementationIDSpace, kCustSEImpl, kCustSEPrefix + 5)


// ActionIDs:
//DECLARE_PMID(kActionIDSpace, kCustSEActionID, kCustSEPrefix + 1)
//DECLARE_PMID(kActionIDSpace, kCustSEActionID, kCustSEPrefix + 2)
//DECLARE_PMID(kActionIDSpace, kCustSEActionID, kCustSEPrefix + 3)
//DECLARE_PMID(kActionIDSpace, kCustSEActionID, kCustSEPrefix + 4)
//DECLARE_PMID(kActionIDSpace, kCustSEActionID, kCustSEPrefix + 5)


// ScriptInfoIDs:
DECLARE_PMID(kScriptInfoIDSpace, kParaStyleListChangedScriptElement, kCustSEPrefix + 0)
DECLARE_PMID(kScriptInfoIDSpace, kCharStyleListChangedScriptElement, kCustSEPrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kSpreadListChangedScriptElement, kCustSEPrefix + 2)


// "About Plug-ins" sub-menu:
#define kCustSEAboutMenuKey			kCustSEStringPrefix "kCustSEAboutMenuKey"
#define kCustSEAboutMenuPath		kSDKDefStandardAboutMenuPath kCustSECompanyKey

// "Plug-ins" sub-menu:
#define kCustSEPluginsMenuKey 		kCustSEStringPrefix "kCustSEPluginsMenuKey"
#define kCustSEPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kCustSECompanyKey kSDKDefDelimitMenuPath kCustSEPluginsMenuKey

// Menu item keys:

// Other StringKeys:
#define kCustSEAboutBoxStringKey	kCustSEStringPrefix "kCustSEAboutBoxStringKey"
#define kCustSETargetMenuPath kCustSEPluginsMenuPath

// Menu item positions:


// Initial data format version numbers
#define kCustSEFirstMajorFormatNumber  RezLong(1)
#define kCustSEFirstMinorFormatNumber  RezLong(0)

// Data format version numbers for the PluginVersion resource 
#define kCustSECurrentMajorFormatNumber kCustSEFirstMajorFormatNumber
#define kCustSECurrentMinorFormatNumber kCustSEFirstMinorFormatNumber

#endif // __CustSEID_h__

//  Code generated by DollyXs code generator
