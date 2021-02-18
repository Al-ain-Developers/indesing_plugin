//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/printselection/PrnSelID.h $
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
//========================================================================================

#ifndef __PrnSelID_h__
#define __PrnSelID_h__

#include "SDKDef.h"

// Company:
#define kPrnSelCompanyKey	kSDKDefPlugInCompanyKey // Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kPrnSelCompanyValue	kSDKDefPlugInCompanyValue // Company name displayed externally.

// Plug-in:
#define kPrnSelPluginName	"PrintSelection" // Name of this plug-in.
#define kPrnSelPrefixNumber	0x60B00 	// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kPrnSelVersion		kSDKDefPluginVersionString // Version of this plug-in (for the About Box).
#define kPrnSelAuthor		"Adobe Developer Technologies" // Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kPrnSelPrefixNumber above to modify the prefix.)
#define kPrnSelPrefix		RezLong(kPrnSelPrefixNumber) // Unique numeric prefix for all object model IDs for this plug-in.
#define kPrnSelStringPrefix	SDK_DEF_STRINGIZE(kPrnSelPrefixNumber) // String equivalent of unique prefix number for plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kPrnSelPluginID, kPrnSelPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kPrnSelActionComponentBoss, kPrnSelPrefix + 0)
DECLARE_PMID(kClassIDSpace, kPrnSelDialogBoss_OBSOLETE, kPrnSelPrefix + 1)// obsolete
DECLARE_PMID(kClassIDSpace, kPrnSelDrawServicesBoss, kPrnSelPrefix + 2)
DECLARE_PMID(kClassIDSpace, kPrnSelPrintSetupProviderBoss, kPrnSelPrefix + 3)
DECLARE_PMID(kClassIDSpace, kPrnSelScriptProviderBoss, kPrnSelPrefix + 4)

// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_IPRNSELDATA, kPrnSelPrefix + 0)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRNSELSUITE, kPrnSelPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRNSELUTILS, kPrnSelPrefix + 2)

// Implementation IDs:
DECLARE_PMID(kImplementationIDSpace, kPrnSelActionComponentImpl, kPrnSelPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kPrnSelDialogControllerImpl_OBSOLETE, kPrnSelPrefix + 1) // obsolete
DECLARE_PMID(kImplementationIDSpace, kPrnSelDialogObserverImpl_OBSOLETE, kPrnSelPrefix + 2) // obsolete
DECLARE_PMID(kImplementationIDSpace, kPrnSelDrawHandlerImpl, kPrnSelPrefix + 3)
//gap
DECLARE_PMID(kImplementationIDSpace, kPrnSelPrintSetupProviderImpl, kPrnSelPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kPrnSelDataImpl, kPrnSelPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kPrnSelSuiteASBImpl, kPrnSelPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kPrnSelSuiteLayoutCSBImpl, kPrnSelPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kPrnSelSuiteTableCSBImpl, kPrnSelPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kPrnSelSuiteTextCSBImpl, kPrnSelPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kPrnSelScriptProviderImpl, kPrnSelPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kPrnSelUtilsImpl, kPrnSelPrefix + 12)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kPrnSelAboutActionID, kPrnSelPrefix + 0)
DECLARE_PMID(kActionIDSpace, kPrnSelPrintSelectionActionID, kPrnSelPrefix + 1)

// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kPrnSelDialogWidgetID_OBSOLETE, kPrnSelPrefix + 0) // obsolete
DECLARE_PMID(kWidgetIDSpace, kPrnSelSelectionCheckboxWidgetID_OBSOLETE, kPrnSelPrefix + 1)// obsolete

// Scripting IDs
//Objects
DECLARE_PMID(kScriptInfoIDSpace, kPrintSelectionObjectScriptElement, kPrnSelPrefix + 0)
//Properties
DECLARE_PMID(kScriptInfoIDSpace, kPrintSelectionPropertyScriptElement, kPrnSelPrefix + 10)
DECLARE_PMID(kScriptInfoIDSpace, kSuppressPrintSelectionDialogPropertyScriptElement, kPrnSelPrefix + 11)
DECLARE_PMID(kScriptInfoIDSpace, kPrintSelectionObjectPropertyScriptElement, kPrnSelPrefix + 12)

// "About Plug-ins" sub-menu:
#define kPrnSelAboutMenuKey		kPrnSelStringPrefix "kPrnSelAboutMenuKey"
#define kPrnSelAboutMenuPath	kSDKDefStandardAboutMenuPath kPrnSelCompanyKey
#define kPrnSelPluginsMenuKey 	kPrnSelStringPrefix "kPrnSelPluginsMenuKey"
#define kPrnSelPluginsMenuPath kSDKDefPlugInsStandardMenuPath kPrnSelCompanyKey kSDKDefDelimitMenuPath kPrnSelPluginsMenuKey


// "Plug-ins" sub-menu:

// "Plug-ins" sub-menu item keys:
#define kPrnSelPrintSelectionMenuKey kPrnSelStringPrefix "kPrnSelPrintSelectionMenuKey"

// "Plug-ins" sub-menu item positions:

// Other StringKeys:
#define kPrnSelAboutBoxStringKey		kPrnSelStringPrefix "kPrnSelAboutBoxStringKey"
#define kPrnSelTargetMenuPath kPrnSelPluginsMenuPath


// Initial data format version numbers
#define kPrnSelFirstMajorFormatNumber  kSDKDef_30_PersistMajorVersionNumber
#define kPrnSelFirstMinorFormatNumber  kSDKDef_30_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kPrnSelCurrentMajorFormatNumber kPrnSelFirstMajorFormatNumber // most recent major format change
#define kPrnSelCurrentMinorFormatNumber kPrnSelFirstMinorFormatNumber // most recent minor format change

#endif // __PrnSelID_h__

// End, PrnSelID.h.


