//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/chmlfilter/CHMLFiltID.h $
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

#ifndef __CHMLFiltID_h__
#define __CHMLFiltID_h__

#include "SDKDef.h"


// Company:
#define kCHMLFiltCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kCHMLFiltCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kCHMLFiltPluginName	"CHMLFilter"			// Name of this plug-in.
#define kCHMLFiltPrefixNumber	0x48000 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kCHMLFiltVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kCHMLFiltAuthor		"Adobe Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kCHMLFiltPrefixNumber above to modify the prefix.)
#define kCHMLFiltPrefix		RezLong(kCHMLFiltPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kCHMLFiltStringPrefix	SDK_DEF_STRINGIZE(kCHMLFiltPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kCHMLFiltPluginID, 			kCHMLFiltPrefix + 1)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kCHMLFiltImportProviderBoss,	kCHMLFiltPrefix + 0)
//DECLARE_PMID(kClassIDSpace, kCHMLFiltActionComponentBoss,	kCHMLFiltPrefix + 1)// kept here for record keeping purposes (Do not reuse this ID!)
DECLARE_PMID(kClassIDSpace, kCHMLFiltExportProviderBoss,	kCHMLFiltPrefix + 2)

// InterfaceIDs:
// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kCHMLFiltImportProviderImpl,			kCHMLFiltPrefix +	0)
//DECLARE_PMID(kImplementationIDSpace, kCHMLFiltActionComponentImpl,	kCHMLFiltPrefix + 1)// kept here for record keeping purposes (Do not reuse this ID!)
DECLARE_PMID(kImplementationIDSpace, kCHMLFiltExportProviderImpl,	kCHMLFiltPrefix + 2)
// ActionIDs:
DECLARE_PMID(kActionIDSpace, kCHMLFiltAboutActionID,		kCHMLFiltPrefix + 0)
// WidgetIDs:

// "About Plug-ins" sub-menu:
#define kCHMLFiltAboutMenuKey			kCHMLFiltStringPrefix "kCHMLFiltAboutMenuKey"
#define kCHMLFiltAboutMenuPath		kSDKDefStandardAboutMenuPath kCHMLFiltCompanyKey

// "Plug-ins" sub-menu:
// Other StringKeys:
#define kCHMLFiltAboutBoxStringKey		kCHMLFiltStringPrefix "kCHMLFiltAboutBoxStringKey"
#define kCHMLFiltMissingFontStringKey		kCHMLFiltStringPrefix "kCHMLFiltMissingFontStringKey"

// No translation needed 
#define kCHMLFiltFileExtensionKey			"chml"

// File types:
// Not translated
#define kCHMLFiltFormatNameKey				kCHMLFiltStringPrefix "kCHMLFiltFormatNameKey"
#define kCHMLFiltExportFormatNameKey				kCHMLFiltStringPrefix "kCHMLFiltExportFormatNameKey"
#define kCHMLFiltFile_Type				'TEXT'

// Initial data format version numbers
#define kCHMLFiltFirstMajorFormatNumber  kSDKDef_30_PersistMajorVersionNumber
#define kCHMLFiltFirstMinorFormatNumber  kSDKDef_30_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kCHMLFiltCurrentMajorFormatNumber kCHMLFiltFirstMajorFormatNumber // most recent major format change
#define kCHMLFiltCurrentMinorFormatNumber kCHMLFiltFirstMinorFormatNumber // most recent minor format change

#endif // __CHMLFiltID_h__

// End, CHMLFiltID.h.


