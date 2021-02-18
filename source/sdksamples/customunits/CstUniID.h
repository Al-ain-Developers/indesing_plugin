//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customunits/CstUniID.h $
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
//  Defines IDs used by the CstUni plug-in.
//  
//========================================================================================

#ifndef __CstUniID_h__
#define __CstUniID_h__

#include "SDKDef.h"

// Company:
#define kCstUniCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kCstUniCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kCstUniPluginName	"CustomUnits"			// Name of this plug-in.
#define kCstUniPrefixNumber	0x55700 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kCstUniVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kCstUniAuthor		"Adobe Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kCstUniPrefixNumber above to modify the prefix.)
#define kCstUniPrefix		RezLong(kCstUniPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kCstUniStringPrefix	SDK_DEF_STRINGIZE(kCstUniPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// Missing plug-in: (see ExtraPluginInfo resource)
#define kCstUniMissingPluginURLValue		kSDKDefPartnersStandardValue_enUS // URL displayed in Missing Plug-in dialog
#define kCstUniMissingPluginAlertValue		kSDKDefMissingPluginAlertValue // Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem


// PluginID:
DECLARE_PMID(kPlugInIDSpace, kCstUniPluginID, kCstUniPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kCstUniBoss,				kCstUniPrefix + 2)
DECLARE_PMID(kClassIDSpace, kCstUniActionComponentBoss,	kCstUniPrefix + 5)

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kCstUniImpl,				kCstUniPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kCstUniActionComponentImpl,	kCstUniPrefix + 4)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kCstUniAboutActionID,				kCstUniPrefix + 0)
// WidgetIDs:
 
// "About Plug-ins" sub-menu:
#define kCstUniAboutMenuKey			kCstUniStringPrefix "kCstUniAboutMenuKey"
#define kCstUniAboutMenuPath		kSDKDefStandardAboutMenuPath kCstUniCompanyKey

// "Plug-ins" sub-menu:
#define kCstUniPluginsMenuKey 		kCstUniStringPrefix "kCstUniPluginsMenuKey"
#define kCstUniPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kCstUniCompanyKey kSDKDefDelimitMenuPath kCstUniPluginsMenuKey

// Menu item keys:

// Other StringKeys:
#define kCstUniAboutBoxStringKey	kCstUniStringPrefix "kCstUniAboutBoxStringKey"

#define kCstUniString						kCstUniStringPrefix "kCstUniString"
#define kCstUnisString						kCstUniStringPrefix "kCstUnisString"
#define kCstUniAbbrPlaceHolderString		kCstUniStringPrefix "kCstUniAbbrPlaceHolderString"
#define kCstUniAbbrString					kCstUniStringPrefix "kCstUniAbbrString"

// Initial data format version numbers
#define kCstUniFirstMajorFormatNumber  kSDKDef_30_PersistMajorVersionNumber
#define kCstUniFirstMinorFormatNumber  kSDKDef_30_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kCstUniCurrentMajorFormatNumber kCstUniFirstMajorFormatNumber // most recent major format change
#define kCstUniCurrentMinorFormatNumber kCstUniFirstMinorFormatNumber // most recent minor format change

#endif // __CstUniID_h__
// End, CstUniID.h.


