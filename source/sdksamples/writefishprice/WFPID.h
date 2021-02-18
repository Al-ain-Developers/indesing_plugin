//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/writefishprice/WFPID.h $
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

#ifndef __WFPID_h__
#define __WFPID_h__

#include "SDKDef.h"

// Company:
#define kWFPCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kWFPCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kWFPPluginName	"WriteFishPrice"			// Name of this plug-in.
#define kWFPPrefixNumber	0x61000 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kWFPVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kWFPAuthor		"Adobe Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kWFPPrefixNumber above to modify the prefix.)
#define kWFPPrefix		RezLong(kWFPPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kWFPStringPrefix	SDK_DEF_STRINGIZE(kWFPPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// Missing plug-in: (see ExtraPluginInfo resource)
#define kWFPMissingPluginURLValue		kSDKDefPartnersStandardValue_enUS // URL displayed in Missing Plug-in dialog
#define kWFPMissingPluginAlertValue	kSDKDefMissingPluginAlertValue // Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kWFPPluginID, kWFPPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kWFPActionComponentBoss, kWFPPrefix + 0)
DECLARE_PMID(kClassIDSpace, kWFPDialogBoss, kWFPPrefix + 2)
//DECLARE_PMID(kClassIDSpace, kWFPBoss, kWFPPrefix + 3)
//DECLARE_PMID(kClassIDSpace, kWFPBoss, kWFPPrefix + 4)
//DECLARE_PMID(kClassIDSpace, kWFPBoss, kWFPPrefix + 5)
//DECLARE_PMID(kClassIDSpace, kWFPBoss, kWFPPrefix + 6)
//DECLARE_PMID(kClassIDSpace, kWFPBoss, kWFPPrefix + 7)
//DECLARE_PMID(kClassIDSpace, kWFPBoss, kWFPPrefix + 8)
//DECLARE_PMID(kClassIDSpace, kWFPBoss, kWFPPrefix + 9)
//DECLARE_PMID(kClassIDSpace, kWFPBoss, kWFPPrefix + 10)
//DECLARE_PMID(kClassIDSpace, kWFPBoss, kWFPPrefix + 11)
//DECLARE_PMID(kClassIDSpace, kWFPBoss, kWFPPrefix + 12)
//DECLARE_PMID(kClassIDSpace, kWFPBoss, kWFPPrefix + 13)
//DECLARE_PMID(kClassIDSpace, kWFPBoss, kWFPPrefix + 14)
//DECLARE_PMID(kClassIDSpace, kWFPBoss, kWFPPrefix + 15)
//DECLARE_PMID(kClassIDSpace, kWFPBoss, kWFPPrefix + 16)
//DECLARE_PMID(kClassIDSpace, kWFPBoss, kWFPPrefix + 17)
//DECLARE_PMID(kClassIDSpace, kWFPBoss, kWFPPrefix + 18)
//DECLARE_PMID(kClassIDSpace, kWFPBoss, kWFPPrefix + 19)
//DECLARE_PMID(kClassIDSpace, kWFPBoss, kWFPPrefix + 20)
//DECLARE_PMID(kClassIDSpace, kWFPBoss, kWFPPrefix + 21)
//DECLARE_PMID(kClassIDSpace, kWFPBoss, kWFPPrefix + 22)
//DECLARE_PMID(kClassIDSpace, kWFPBoss, kWFPPrefix + 23)
//DECLARE_PMID(kClassIDSpace, kWFPBoss, kWFPPrefix + 24)
//DECLARE_PMID(kClassIDSpace, kWFPBoss, kWFPPrefix + 25)


// InterfaceIDs:
//DECLARE_PMID(kInterfaceIDSpace, IID_IWFPINTERFACE, kWFPPrefix + 0)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWFPINTERFACE, kWFPPrefix + 1)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWFPINTERFACE, kWFPPrefix + 2)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWFPINTERFACE, kWFPPrefix + 3)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWFPINTERFACE, kWFPPrefix + 4)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWFPINTERFACE, kWFPPrefix + 5)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWFPINTERFACE, kWFPPrefix + 6)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWFPINTERFACE, kWFPPrefix + 7)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWFPINTERFACE, kWFPPrefix + 8)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWFPINTERFACE, kWFPPrefix + 9)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWFPINTERFACE, kWFPPrefix + 10)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWFPINTERFACE, kWFPPrefix + 11)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWFPINTERFACE, kWFPPrefix + 12)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWFPINTERFACE, kWFPPrefix + 13)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWFPINTERFACE, kWFPPrefix + 14)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWFPINTERFACE, kWFPPrefix + 15)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWFPINTERFACE, kWFPPrefix + 16)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWFPINTERFACE, kWFPPrefix + 17)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWFPINTERFACE, kWFPPrefix + 18)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWFPINTERFACE, kWFPPrefix + 19)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWFPINTERFACE, kWFPPrefix + 20)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWFPINTERFACE, kWFPPrefix + 21)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWFPINTERFACE, kWFPPrefix + 22)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWFPINTERFACE, kWFPPrefix + 23)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWFPINTERFACE, kWFPPrefix + 24)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWFPINTERFACE, kWFPPrefix + 25)


// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kWFPDialogControllerImpl,		kWFPPrefix + 0 )
DECLARE_PMID(kImplementationIDSpace, kWFPDialogObserverImpl,		kWFPPrefix + 1 )
DECLARE_PMID(kImplementationIDSpace, kWFPActionComponentImpl,		kWFPPrefix + 2 )
//DECLARE_PMID(kImplementationIDSpace, kWFPImpl, kWFPPrefix + 3)
//DECLARE_PMID(kImplementationIDSpace, kWFPImpl, kWFPPrefix + 4)
//DECLARE_PMID(kImplementationIDSpace, kWFPImpl, kWFPPrefix + 5)
//DECLARE_PMID(kImplementationIDSpace, kWFPImpl, kWFPPrefix + 6)
//DECLARE_PMID(kImplementationIDSpace, kWFPImpl, kWFPPrefix + 7)
//DECLARE_PMID(kImplementationIDSpace, kWFPImpl, kWFPPrefix + 8)
//DECLARE_PMID(kImplementationIDSpace, kWFPImpl, kWFPPrefix + 9)
//DECLARE_PMID(kImplementationIDSpace, kWFPImpl, kWFPPrefix + 10)
//DECLARE_PMID(kImplementationIDSpace, kWFPImpl, kWFPPrefix + 11)
//DECLARE_PMID(kImplementationIDSpace, kWFPImpl, kWFPPrefix + 12)
//DECLARE_PMID(kImplementationIDSpace, kWFPImpl, kWFPPrefix + 13)
//DECLARE_PMID(kImplementationIDSpace, kWFPImpl, kWFPPrefix + 14)
//DECLARE_PMID(kImplementationIDSpace, kWFPImpl, kWFPPrefix + 15)
//DECLARE_PMID(kImplementationIDSpace, kWFPImpl, kWFPPrefix + 16)
//DECLARE_PMID(kImplementationIDSpace, kWFPImpl, kWFPPrefix + 17)
//DECLARE_PMID(kImplementationIDSpace, kWFPImpl, kWFPPrefix + 18)
//DECLARE_PMID(kImplementationIDSpace, kWFPImpl, kWFPPrefix + 19)
//DECLARE_PMID(kImplementationIDSpace, kWFPImpl, kWFPPrefix + 20)
//DECLARE_PMID(kImplementationIDSpace, kWFPImpl, kWFPPrefix + 21)
//DECLARE_PMID(kImplementationIDSpace, kWFPImpl, kWFPPrefix + 22)
//DECLARE_PMID(kImplementationIDSpace, kWFPImpl, kWFPPrefix + 23)
//DECLARE_PMID(kImplementationIDSpace, kWFPImpl, kWFPPrefix + 24)
//DECLARE_PMID(kImplementationIDSpace, kWFPImpl, kWFPPrefix + 25)


// ActionIDs:
DECLARE_PMID(kActionIDSpace, kWFPAboutActionID, kWFPPrefix + 0)

DECLARE_PMID(kActionIDSpace, kWFPDialogActionID, kWFPPrefix + 4)
//DECLARE_PMID(kActionIDSpace, kWFPActionID, kWFPPrefix + 5)
//DECLARE_PMID(kActionIDSpace, kWFPActionID, kWFPPrefix + 6)
//DECLARE_PMID(kActionIDSpace, kWFPActionID, kWFPPrefix + 7)
//DECLARE_PMID(kActionIDSpace, kWFPActionID, kWFPPrefix + 8)
//DECLARE_PMID(kActionIDSpace, kWFPActionID, kWFPPrefix + 9)
//DECLARE_PMID(kActionIDSpace, kWFPActionID, kWFPPrefix + 10)
//DECLARE_PMID(kActionIDSpace, kWFPActionID, kWFPPrefix + 11)
//DECLARE_PMID(kActionIDSpace, kWFPActionID, kWFPPrefix + 12)
//DECLARE_PMID(kActionIDSpace, kWFPActionID, kWFPPrefix + 13)
//DECLARE_PMID(kActionIDSpace, kWFPActionID, kWFPPrefix + 14)
//DECLARE_PMID(kActionIDSpace, kWFPActionID, kWFPPrefix + 15)
//DECLARE_PMID(kActionIDSpace, kWFPActionID, kWFPPrefix + 16)
//DECLARE_PMID(kActionIDSpace, kWFPActionID, kWFPPrefix + 17)
//DECLARE_PMID(kActionIDSpace, kWFPActionID, kWFPPrefix + 18)
//DECLARE_PMID(kActionIDSpace, kWFPActionID, kWFPPrefix + 19)
//DECLARE_PMID(kActionIDSpace, kWFPActionID, kWFPPrefix + 20)
//DECLARE_PMID(kActionIDSpace, kWFPActionID, kWFPPrefix + 21)
//DECLARE_PMID(kActionIDSpace, kWFPActionID, kWFPPrefix + 22)
//DECLARE_PMID(kActionIDSpace, kWFPActionID, kWFPPrefix + 23)
//DECLARE_PMID(kActionIDSpace, kWFPActionID, kWFPPrefix + 24)
//DECLARE_PMID(kActionIDSpace, kWFPActionID, kWFPPrefix + 25)


// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kWFPDialogWidgetID, kWFPPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kWFPDropDownListWidgetID, kWFPPrefix + 2) // STEP 2.1: DropDownList widget ID
DECLARE_PMID(kWidgetIDSpace, kWFPTextEditBoxWidgetID, kWFPPrefix + 3) // STEP 3.1: TextEditBox widget ID
DECLARE_PMID(kWidgetIDSpace, kWFPStaticTextWidgetID, kWFPPrefix + 4) // STEP 4.1: StaticText widget ID
//DECLARE_PMID(kWidgetIDSpace, kWFPWidgetID, kWFPPrefix + 5)
//DECLARE_PMID(kWidgetIDSpace, kWFPWidgetID, kWFPPrefix + 6)
//DECLARE_PMID(kWidgetIDSpace, kWFPWidgetID, kWFPPrefix + 7)
//DECLARE_PMID(kWidgetIDSpace, kWFPWidgetID, kWFPPrefix + 8)
//DECLARE_PMID(kWidgetIDSpace, kWFPWidgetID, kWFPPrefix + 9)
//DECLARE_PMID(kWidgetIDSpace, kWFPWidgetID, kWFPPrefix + 10)
//DECLARE_PMID(kWidgetIDSpace, kWFPWidgetID, kWFPPrefix + 11)
//DECLARE_PMID(kWidgetIDSpace, kWFPWidgetID, kWFPPrefix + 12)
//DECLARE_PMID(kWidgetIDSpace, kWFPWidgetID, kWFPPrefix + 13)
//DECLARE_PMID(kWidgetIDSpace, kWFPWidgetID, kWFPPrefix + 14)
//DECLARE_PMID(kWidgetIDSpace, kWFPWidgetID, kWFPPrefix + 15)
//DECLARE_PMID(kWidgetIDSpace, kWFPWidgetID, kWFPPrefix + 16)
//DECLARE_PMID(kWidgetIDSpace, kWFPWidgetID, kWFPPrefix + 17)
//DECLARE_PMID(kWidgetIDSpace, kWFPWidgetID, kWFPPrefix + 18)
//DECLARE_PMID(kWidgetIDSpace, kWFPWidgetID, kWFPPrefix + 19)
//DECLARE_PMID(kWidgetIDSpace, kWFPWidgetID, kWFPPrefix + 20)
//DECLARE_PMID(kWidgetIDSpace, kWFPWidgetID, kWFPPrefix + 21)
//DECLARE_PMID(kWidgetIDSpace, kWFPWidgetID, kWFPPrefix + 22)
//DECLARE_PMID(kWidgetIDSpace, kWFPWidgetID, kWFPPrefix + 23)
//DECLARE_PMID(kWidgetIDSpace, kWFPWidgetID, kWFPPrefix + 24)
//DECLARE_PMID(kWidgetIDSpace, kWFPWidgetID, kWFPPrefix + 25)


// "About Plug-ins" sub-menu:
#define kWFPAboutMenuKey			kWFPStringPrefix "kWFPAboutMenuKey"
#define kWFPAboutMenuPath		kSDKDefStandardAboutMenuPath kWFPCompanyKey

// "Plug-ins" sub-menu:
#define kWFPPluginsMenuKey 		kWFPStringPrefix "kWFPPluginsMenuKey"
#define kWFPPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kWFPCompanyKey kSDKDefDelimitMenuPath kWFPPluginsMenuKey

// Menu item keys:

// Other StringKeys:
#define kWFPAboutBoxStringKey	kWFPStringPrefix "kWFPAboutBoxStringKey"
#define kWFPMenuItem1StringKey			kWFPStringPrefix "kWFPMenuItem1StringKey"
#define kWFPDropDownItem_1Key	kWFPStringPrefix "kWFPDropDownItem_1Key" // STEP 2.2: DropDownList Item key string
#define kWFPDropDownItem_2Key	kWFPStringPrefix "kWFPDropDownItem_2Key" // STEP 2.2: DropDownList Item key string
#define kWFPDropDownItem_3Key	kWFPStringPrefix "kWFPDropDownItem_3Key" // STEP 2.2: DropDownList Item key string
#define kWFPDropDownItem_4Key	kWFPStringPrefix "kWFPDropDownItem_4Key" // STEP 2.2: DropDownList Item key string
#define kWFPStaticTextKey		kWFPStringPrefix "kWFPStaticTextKey" // STEP 4.2: StaticText string key. (yen or dollar character)

#define kWFPTargetMenuPath kWFPPluginsMenuPath

// Menu item positions:

#define kWFPDialogTitleKey kWFPStringPrefix "kWFPDialogTitleKey"
// "Plug-ins" sub-menu item key for dialog:
#define kWFPDialogMenuItemKey kWFPStringPrefix "kWFPDialogMenuItemKey"
// "Plug-ins" sub-menu item position for dialog:
#define kWFPDialogMenuItemPosition	12.0


// Initial data format version numbers
#define kWFPFirstMajorFormatNumber  kSDKDef_30_PersistMajorVersionNumber
#define kWFPFirstMinorFormatNumber  kSDKDef_30_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kWFPCurrentMajorFormatNumber kWFPFirstMajorFormatNumber // most recent major format change
#define kWFPCurrentMinorFormatNumber kWFPFirstMinorFormatNumber // most recent minor format change

#endif // __WFPID_h__

//  Code generated by DollyXs code generator
