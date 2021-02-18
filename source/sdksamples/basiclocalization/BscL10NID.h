//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basiclocalization/BscL10NID.h $
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
//  Defines IDs used by the BscL10N plug-in.
//  
//========================================================================================

#ifndef __BscL10NID_h__
#define __BscL10NID_h__

#include "SDKDef.h"

// Company:
#define kBscL10NCompanyKey	kSDKDefPlugInCompanyKey // Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kBscL10NCompanyValue	kSDKDefPlugInCompanyValue // Company name displayed externally.

// Plug-in:
#define kBscL10NPluginName	"BasicLocalization" // Name of this plug-in.
#define kBscL10NPrefixNumber	0x61100 	// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kBscL10NVersion		kSDKDefPluginVersionString // Version of this plug-in (for the About Box).
#define kBscL10NAuthor		"Adobe Developer Technologies" // Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kBscL10NPrefixNumber above to modify the prefix.)
#define kBscL10NPrefix		RezLong(kBscL10NPrefixNumber) // The unique numeric prefix for all object model IDs for this plug-in.
#define kBscL10NStringPrefix	SDK_DEF_STRINGIZE(kBscL10NPrefixNumber) // The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kBscL10NPluginID, kBscL10NPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kBscL10NActionComponentBoss, kBscL10NPrefix + 0)
// Obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kBscL10NStringRegisterBoss, kBscL10NPrefix + 1)
// Obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kBscL10NMenuRegisterBoss, kBscL10NPrefix + 2)
// Obsoleted by InDesign3.0 DECLARE_PMID(kClassIDSpace, kBscL10NActionRegisterBoss, kBscL10NPrefix + 3)
DECLARE_PMID(kClassIDSpace, kBscL10NDialogBoss, kBscL10NPrefix + 4)

// InterfaceIDs:
// None in this plug-in.

// Implementation IDs:
DECLARE_PMID(kImplementationIDSpace, kBscL10NActionComponentImpl, kBscL10NPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kBscL10NDialogControllerImpl, kBscL10NPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kBscL10NDialogObserverImpl, kBscL10NPrefix + 2)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kBscL10NAboutActionID, kBscL10NPrefix + 0)
DECLARE_PMID(kActionIDSpace, kBscL10NDialogActionID, kBscL10NPrefix + 1)

// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kBscL10NDialogWidgetID, kBscL10NPrefix + 0)
DECLARE_PMID(kWidgetIDSpace, kBscL10NIconSuiteWidgetID, kBscL10NPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kBscL10NStaticTextWidgetID, kBscL10NPrefix + 2)

// "About Plug-ins" sub-menu:
#define kBscL10NAboutMenuKey			kBscL10NStringPrefix "kBscL10NAboutMenuKey"
#define kBscL10NAboutMenuPath			kSDKDefStandardAboutMenuPath kBscL10NCompanyKey

// "Plug-ins" sub-menu:
#define kBscL10NPluginsMenuKey 		kBscL10NStringPrefix "kBscL10NPluginsMenuKey"
#define kBscL10NPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kBscL10NCompanyKey

// "Plug-ins" sub-menu item keys:
#define kBscL10NDialogMenuItemKey		kBscL10NStringPrefix "kBscL10NDialogMenuItemKey"

// "Plug-ins" sub-menu item positions:
#define kBscL10NDialogMenuItemPosition	1.0

// Other StringKeys:
#define kBscL10NDialogTitleKey		kBscL10NStringPrefix "kBscL10NDialogTitleKey"
#define kBscL10NAboutBoxStringKey		kBscL10NStringPrefix "kBscL10NAboutBoxStringKey"
#define kBscL10NStaticTextStringKey		kBscL10NStringPrefix "kBscL10NStaticTextStringKey"

// Initial data format version numbers
#define kBscL10NFirstMajorFormatNumber  kSDKDef_30_PersistMajorVersionNumber
#define kBscL10NFirstMinorFormatNumber  kSDKDef_30_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kBscL10NCurrentMajorFormatNumber kBscL10NFirstMajorFormatNumber // most recent major format change
#define kBscL10NCurrentMinorFormatNumber kBscL10NFirstMinorFormatNumber // most recent minor format change

#endif // __BscL10NID_h__

// End, BscL10NID.h.




