//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmlmarkupinjector/XMLMrkID.h $
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
//  Defines IDs used by the XMLMrk plug-in.
//  
//========================================================================================

#ifndef __XMLMrkID_h__
#define __XMLMrkID_h__

#include "SDKDef.h"

// Company:
#define kXMLMrkCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kXMLMrkCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kXMLMrkPluginName	"XMLMarkupInjector"			// Name of this plug-in.
#define kXMLMrkPrefixNumber	0x5c360 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kXMLMrkVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kXMLMrkAuthor		"Adobe Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kXMLMrkPrefixNumber above to modify the prefix.)
#define kXMLMrkPrefix		RezLong(kXMLMrkPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kXMLMrkStringPrefix	SDK_DEF_STRINGIZE(kXMLMrkPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kXMLMrkPluginID, kXMLMrkPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kXMLMrkActionComponentBoss,	kXMLMrkPrefix + 0)
// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLMrkSUITE,		kXMLMrkPrefix + 0)
// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kXMLMrkActionComponentImpl,		kXMLMrkPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kXMLMrkSuiteASBImpl,				kXMLMrkPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kXMLMrkSuiteTextCSBImpl,			kXMLMrkPrefix + 2)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kXMLMrkAboutActionID,					kXMLMrkPrefix + 0)
DECLARE_PMID(kActionIDSpace, kXMLMrkCompoundSectionActionID,		kXMLMrkPrefix + 11)
DECLARE_PMID(kActionIDSpace, kXMLMrkCompoundTableActionID,			kXMLMrkPrefix + 12)
DECLARE_PMID(kActionIDSpace, kXMLMrkCompoundItemizedListActionID,	kXMLMrkPrefix + 13)
DECLARE_PMID(kActionIDSpace, kXMLMrkCompoundMediaObjectActionID,	kXMLMrkPrefix + 14)
DECLARE_PMID(kActionIDSpace, kXMLMrkCompoundKeywordSetActionID,		kXMLMrkPrefix + 15)
// WidgetIDs:
 
// "About Plug-ins" sub-menu:
#define kXMLMrkAboutMenuKey			kXMLMrkStringPrefix "kXMLMrkAboutMenuKey"
#define kXMLMrkAboutMenuPath		kSDKDefStandardAboutMenuPath kXMLMrkCompanyKey

// "Plug-ins" sub-menu:
#define kXMLMrkPluginsMenuKey 		kXMLMrkStringPrefix "kXMLMrkPluginsMenuKey"
#define kXMLMrkPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kXMLMrkCompanyKey kSDKDefDelimitMenuPath kXMLMrkPluginsMenuKey

// Menu item keys:
#define kXMLMrkCompoundSectionMenuItemKey			kXMLMrkStringPrefix "kXMLMrkCompoundSectionMenuItemKey"
#define kXMLMrkCompoundTableMenuItemKey				kXMLMrkStringPrefix "kXMLMrkCompoundTableMenuItemKey"
#define kXMLMrkCompoundItemizedListMenuItemKey		kXMLMrkStringPrefix "kXMLMrkCompoundItemizedListMenuItemKey"
#define kXMLMrkCompoundMediaObjectMenuItemKey		kXMLMrkStringPrefix "kXMLMrkCompoundMediaObjectMenuItemKey"
#define kXMLMrkCompoundKeywordSetMenuItemKey		kXMLMrkStringPrefix "kXMLMrkCompoundKeywordSetMenuItemKey"

// Other StringKeys:
#define kXMLMrkAboutBoxStringKey				kXMLMrkStringPrefix "kXMLMrkAboutBoxStringKey"
// The target menu path is determined by where the XMedia UI plug-in creates it entries
// If you didn't have the XMedia UI plug-in installed, you'd see no entries I guess
#define kXMLMrkTargetMenuPath "RtMouseText:TagTextPopup"

// Menu item positions:
#define kXMLMrkCompoundSectionMenuItemPosition				1.0
#define kXMLMrkCompoundTableMenuItemPosition				2.0	
#define kXMLMrkCompoundItemizedListMenuItemPosition			3.0
#define kXMLMrkCompoundMediaObjectMenuItemPosition			4.0	
#define kXMLMrkCompoundKeywordSetMenuItemPosition			5.0

// Initial data format version numbers
#define kXMLMrkFirstMajorFormatNumber  kSDKDef_30_PersistMajorVersionNumber
#define kXMLMrkFirstMinorFormatNumber  kSDKDef_30_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kXMLMrkCurrentMajorFormatNumber kXMLMrkFirstMajorFormatNumber // most recent major format change
#define kXMLMrkCurrentMinorFormatNumber kXMLMrkFirstMinorFormatNumber // most recent minor format change

#endif // __XMLMrkID_h__

// End, XMLMrkID.h.




