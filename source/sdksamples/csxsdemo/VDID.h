//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/csxsdemo/VDID.h $
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
//  Copyright 1997-2013 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================


#ifndef __VDID_h__
#define __VDID_h__

#include "SDKDef.h"

// Company:
#define kVDCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kVDCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kVDPluginName	"CSXSDemo.sdk"			// Name of this plug-in.
#define kVDPrefixNumber	0x1D7500 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kVDVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kVDAuthor		"Timothy Brand-Spencer"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kVDPrefixNumber above to modify the prefix.)
#define kVDPrefix		RezLong(kVDPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kVDStringPrefix	SDK_DEF_STRINGIZE(kVDPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// Missing plug-in: (see ExtraPluginInfo resource)
#define kVDMissingPluginURLValue		kSDKDefPartnersStandardValue_enUS // URL displayed in Missing Plug-in dialog
#define kVDMissingPluginAlertValue	kSDKDefMissingPluginAlertValue // Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kVDPluginID, kVDPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kVDActionComponentBoss, kVDPrefix + 0)
DECLARE_PMID(kClassIDSpace, kVDStartupShutdownServiceBoss, kVDPrefix + 3)
//DECLARE_PMID(kClassIDSpace, kVDBoss, kVDPrefix + 4)

// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_IVDSUITE, kVDPrefix + 0)

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kVDActionComponentImpl, kVDPrefix + 0 )
DECLARE_PMID(kImplementationIDSpace, kVDStartupShutdownImpl, kVDPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kVDSuiteASBImpl, kVDPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kVDSuiteCSBImpl, kVDPrefix + 3)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kVDAboutActionID, kVDPrefix + 0)
DECLARE_PMID(kActionIDSpace, kVDContextMenuActionID, kVDPrefix + 1)
//DECLARE_PMID(kActionIDSpace, kVDActionID, kVDPrefix + 5)

// WidgetIDs:
//DECLARE_PMID(kWidgetIDSpace, kVDWidgetID, kVDPrefix + 2)

// "About Plug-ins" sub-menu:
#define kVDAboutMenuKey			kVDStringPrefix "kVDAboutMenuKey"
#define kVDAboutMenuPath		kSDKDefStandardAboutMenuPath kVDCompanyKey

// Context menu
#define kVDContextMenuKey		kVDStringPrefix "kVDContextMenuKey"

// "Plug-ins" sub-menu:
#define kVDPluginsMenuKey 		kVDStringPrefix "kVDPluginsMenuKey"
#define kVDPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kVDCompanyKey kSDKDefDelimitMenuPath kVDPluginsMenuKey

// Menu item keys:
// ..

// String Keys:
#define kVDAboutBoxStringKey	kVDStringPrefix "kVDAboutBoxStringKey"
#define kVDTargetMenuPath kVDPluginsMenuPath
#define kVDPlugPlugInstanceErrorKey	kVDStringPrefix "kVDPlugPlugInstanceErrorKey" // couldnt get plugPlug InterfacePtr
#define kVDPlugPlugDispatchFailKey	kVDStringPrefix "kVDPlugPlugDispatchFailKey" // dispatch plugplug method failed
#define kVDUnsupportedPageItemTypeKey	kVDStringPrefix "kVDUnsupportedPageItemTypeKey" // temp error string


// Menu item positions:
// ...

// Initial data format version numbers
#define kVDFirstMajorFormatNumber  RezLong(1)
#define kVDFirstMinorFormatNumber  RezLong(0)

// Data format version numbers for the PluginVersion resource 
#define kVDCurrentMajorFormatNumber kVDFirstMajorFormatNumber
#define kVDCurrentMinorFormatNumber kVDFirstMinorFormatNumber

#endif // __VDID_h__
