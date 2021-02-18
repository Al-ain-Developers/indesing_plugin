//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/printmemorystream/PrtMemID.h $
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

#ifndef __PrtMemID_h__
#define __PrtMemID_h__

#include "SDKDef.h"

// Company:
#define kPrtMemCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kPrtMemCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kPrtMemPluginName	"PrintMemoryStream"			// Name of this plug-in.
#define kPrtMemPrefixNumber	0xb3c80 					// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kPrtMemVersion		kSDKDefPluginVersionString	// Version of this plug-in (for the About Box).
#define kPrtMemAuthor		"Adobe Developer Technologies"	// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kPrtMemPrefixNumber above to modify the prefix.)
#define kPrtMemPrefix		RezLong(kPrtMemPrefixNumber)	// The unique numeric prefix for all object model IDs for this plug-in.
#define kPrtMemStringPrefix	SDK_DEF_STRINGIZE(kPrtMemPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kPrtMemPluginID, kPrtMemPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kPrtMemActionComponentBoss,					kPrtMemPrefix + 0)
DECLARE_PMID(kClassIDSpace, kPrtMemCustomStreamBoss, 					kPrtMemPrefix + 1)
DECLARE_PMID(kClassIDSpace, kPrtMemPrintSetupProviderBoss,				kPrtMemPrefix + 2)
DECLARE_PMID(kClassIDSpace, kPrtMemPrintDataHelperStrategyProviderBoss,	kPrtMemPrefix + 3)
DECLARE_PMID(kClassIDSpace, kPrtMemPrintInsertPSProcProviderBoss,		kPrtMemPrefix + 4)

// InterfaceIDs:
// none.

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kPrtMemActionComponentImpl,		kPrtMemPrefix + 0 )
DECLARE_PMID(kImplementationIDSpace, kPrtMemWriteStreamImpl, 			kPrtMemPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kPrtMemPrintSetupProviderImpl,		kPrtMemPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kPrtMemPrintDataHelperStrategyImpl,	kPrtMemPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kPrtMemHelperStrategyServiceImpl,	kPrtMemPrefix + 4)
//gap
DECLARE_PMID(kImplementationIDSpace, kPrtMemPrintInsertPSProcProviderImpl,	kPrtMemPrefix + 6)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kPrtMemAboutActionID,						kPrtMemPrefix + 0)
DECLARE_PMID(kActionIDSpace, kPrtMemPrintToMemoryActionID,				kPrtMemPrefix + 1)


// WidgetIDs:
// none.

// "About Plug-ins" sub-menu:
#define kPrtMemAboutMenuKey			kPrtMemStringPrefix "kPrtMemAboutMenuKey"
#define kPrtMemAboutMenuPath		kSDKDefStandardAboutMenuPath kPrtMemCompanyKey

// "Plug-ins" sub-menu:
#define kPrtMemPluginsMenuKey 		kPrtMemStringPrefix "kPrtMemPluginsMenuKey"
#define kPrtMemPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kPrtMemCompanyKey kSDKDefDelimitMenuPath kPrtMemPluginsMenuKey

// Menu item keys:
#define kPrtMemPrintToMemoryMenuItemKey		kPrtMemStringPrefix "kPrtMemPrintToMemoryMenuItemKey"

// Other StringKeys:
#define kPrtMemAboutBoxStringKey	kPrtMemStringPrefix "kPrtMemAboutBoxStringKey"
#define kPrtMemTargetMenuPath 		kPrtMemPluginsMenuPath

// Menu item positions:
#define kPrtMemPrintFrontMenuItemPosition 1
#define kPrtMemPrintToMemoryMenuItemPosition 2

// Initial data format version numbers
#define kPrtMemFirstMajorFormatNumber  RezLong(1)
#define kPrtMemFirstMinorFormatNumber  RezLong(0)

// Data format version numbers for the PluginVersion resource 
#define kPrtMemCurrentMajorFormatNumber kPrtMemFirstMajorFormatNumber
#define kPrtMemCurrentMinorFormatNumber kPrtMemFirstMinorFormatNumber
#endif // __PrtMemID_h__

//  Code generated by DollyXS code generator
