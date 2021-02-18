//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicdrwevthandler/BscDEHID.h $
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
//  Defines IDs used by the BscDEH plug-in.
//  
//========================================================================================

#ifndef __BscDEHID_h__
#define __BscDEHID_h__

#include "SDKDef.h"

// Company:
#define kBscDEHCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kBscDEHCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kBscDEHPluginName	"BasicDrwEvtHandler"		// Name of this plug-in.
#define kBscDEHPrefixNumber	0x5D100 					// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kBscDEHVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kBscDEHAuthor		"Adobe Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kBscDEHPrefixNumber above to modify the prefix.)
#define kBscDEHPrefix		RezLong(kBscDEHPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kBscDEHStringPrefix	SDK_DEF_STRINGIZE(kBscDEHPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kBscDEHPluginID, kBscDEHPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kBscDEHActionComponentBoss,	kBscDEHPrefix + 0)
// Obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kBscDEHStringRegisterBoss,	kBscDEHPrefix + 1)
// Obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kBscDEHMenuRegisterBoss,	kBscDEHPrefix + 2)
// Obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kBscDEHActionRegisterBoss,	kBscDEHPrefix + 3)
DECLARE_PMID(kClassIDSpace, kBscDEHServiceBoss,			kBscDEHPrefix + 4)

// InterfaceIDs:
// None in this plug-in.

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kBscDEHActionComponentImpl,	kBscDEHPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kBscDEHDrwEvtHandlerImpl,		kBscDEHPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kBscDEHDrwEvtSrvcImpl,			kBscDEHPrefix + 2)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kBscDEHAboutActionID,	kBscDEHPrefix + 0)

// WidgetIDs:
 
// "About Plug-ins" sub-menu:
#define kBscDEHAboutMenuKey			kBscDEHStringPrefix "kBscDEHAboutMenuKey"
#define kBscDEHAboutMenuPath		kSDKDefStandardAboutMenuPath kBscDEHCompanyKey

// Menu item keys:

// Other StringKeys:
#define kBscDEHAboutBoxStringKey	kBscDEHStringPrefix "kBscDEHAboutBoxStringKey"
#define kBscDEHTargetMenuPath		kBscDEHPluginsMenuPath

// Initial data format version numbers
#define kBscDEHFirstMajorFormatNumber  kSDKDef_30_PersistMajorVersionNumber
#define kBscDEHFirstMinorFormatNumber  kSDKDef_30_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kBscDEHCurrentMajorFormatNumber kBscDEHFirstMajorFormatNumber // most recent major format change
#define kBscDEHCurrentMinorFormatNumber kBscDEHFirstMinorFormatNumber // most recent minor format change

#endif // __BscDEHID_h__

// End, BscDEHID.h.




