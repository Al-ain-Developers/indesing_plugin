//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/gotolasttextedit/GTTxtEdtID.h $
//  
//  Owner: Adrian O'Lenskie
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

#ifndef __GTTxtEdtID_h__
#define __GTTxtEdtID_h__

#include "SDKDef.h"

// Company:
#define kGTTxtEdtCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kGTTxtEdtCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kGTTxtEdtPluginName	"GoToLastTextEdit"			// Name of this plug-in.
#define kGTTxtEdtPrefixNumber	0xddb00 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kGTTxtEdtVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kGTTxtEdtAuthor		"Adobe Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kGTTxtEdtPrefixNumber above to modify the prefix.)
#define kGTTxtEdtPrefix		RezLong(kGTTxtEdtPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kGTTxtEdtStringPrefix	SDK_DEF_STRINGIZE(kGTTxtEdtPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// Missing plug-in: (see ExtraPluginInfo resource)
#define kGTTxtEdtMissingPluginURLValue		kSDKDefPartnersStandardValue_enUS // URL displayed in Missing Plug-in dialog
#define kGTTxtEdtMissingPluginAlertValue	kSDKDefMissingPluginAlertValue // Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kGTTxtEdtPluginID, kGTTxtEdtPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kGTTxtEdtActionComponentBoss, kGTTxtEdtPrefix + 0)
DECLARE_PMID(kClassIDSpace, kGTTxtEdtControlStripRegisterBoss, kGTTxtEdtPrefix + 1)
DECLARE_PMID(kClassIDSpace, kGTTxtEdtGoToTextButtonBoss, kGTTxtEdtPrefix + 4)
DECLARE_PMID(kClassIDSpace, kGTTxtEdtResponderServiceBoss, kGTTxtEdtPrefix + 5)
//DECLARE_PMID(kClassIDSpace, kGTTxtEdtBoss, kGTTxtEdtPrefix + 6)
//DECLARE_PMID(kClassIDSpace, kGTTxtEdtBoss, kGTTxtEdtPrefix + 7)
//DECLARE_PMID(kClassIDSpace, kGTTxtEdtBoss, kGTTxtEdtPrefix + 8)
//DECLARE_PMID(kClassIDSpace, kGTTxtEdtBoss, kGTTxtEdtPrefix + 9)
//DECLARE_PMID(kClassIDSpace, kGTTxtEdtBoss, kGTTxtEdtPrefix + 10)
//DECLARE_PMID(kClassIDSpace, kGTTxtEdtBoss, kGTTxtEdtPrefix + 11)
//DECLARE_PMID(kClassIDSpace, kGTTxtEdtBoss, kGTTxtEdtPrefix + 12)
//DECLARE_PMID(kClassIDSpace, kGTTxtEdtBoss, kGTTxtEdtPrefix + 13)
//DECLARE_PMID(kClassIDSpace, kGTTxtEdtBoss, kGTTxtEdtPrefix + 14)
//DECLARE_PMID(kClassIDSpace, kGTTxtEdtBoss, kGTTxtEdtPrefix + 15)
//DECLARE_PMID(kClassIDSpace, kGTTxtEdtBoss, kGTTxtEdtPrefix + 16)
//DECLARE_PMID(kClassIDSpace, kGTTxtEdtBoss, kGTTxtEdtPrefix + 17)
//DECLARE_PMID(kClassIDSpace, kGTTxtEdtBoss, kGTTxtEdtPrefix + 18)
//DECLARE_PMID(kClassIDSpace, kGTTxtEdtBoss, kGTTxtEdtPrefix + 19)
//DECLARE_PMID(kClassIDSpace, kGTTxtEdtBoss, kGTTxtEdtPrefix + 20)
//DECLARE_PMID(kClassIDSpace, kGTTxtEdtBoss, kGTTxtEdtPrefix + 21)
//DECLARE_PMID(kClassIDSpace, kGTTxtEdtBoss, kGTTxtEdtPrefix + 22)
//DECLARE_PMID(kClassIDSpace, kGTTxtEdtBoss, kGTTxtEdtPrefix + 23)
//DECLARE_PMID(kClassIDSpace, kGTTxtEdtBoss, kGTTxtEdtPrefix + 24)
//DECLARE_PMID(kClassIDSpace, kGTTxtEdtBoss, kGTTxtEdtPrefix + 25)


// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_IGTTXTEDTCONTROLSTRIPSUITE, kGTTxtEdtPrefix + 0)
DECLARE_PMID(kInterfaceIDSpace, IID_IGTTXTEDTSNAPSHOTINTERFACE, kGTTxtEdtPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IGTTXTEDTUTILS, kGTTxtEdtPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IGTTXTEDTSTORYOBSERVER, kGTTxtEdtPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IGTTXTEDTSTORYCREATEDELETEOBSERVER, kGTTxtEdtPrefix + 4)
//DECLARE_PMID(kInterfaceIDSpace, IID_IGTTXTEDTINTERFACE, kGTTxtEdtPrefix + 5)
//DECLARE_PMID(kInterfaceIDSpace, IID_IGTTXTEDTINTERFACE, kGTTxtEdtPrefix + 6)
//DECLARE_PMID(kInterfaceIDSpace, IID_IGTTXTEDTINTERFACE, kGTTxtEdtPrefix + 7)
//DECLARE_PMID(kInterfaceIDSpace, IID_IGTTXTEDTINTERFACE, kGTTxtEdtPrefix + 8)
//DECLARE_PMID(kInterfaceIDSpace, IID_IGTTXTEDTINTERFACE, kGTTxtEdtPrefix + 9)
//DECLARE_PMID(kInterfaceIDSpace, IID_IGTTXTEDTINTERFACE, kGTTxtEdtPrefix + 10)
//DECLARE_PMID(kInterfaceIDSpace, IID_IGTTXTEDTINTERFACE, kGTTxtEdtPrefix + 11)
//DECLARE_PMID(kInterfaceIDSpace, IID_IGTTXTEDTINTERFACE, kGTTxtEdtPrefix + 12)
//DECLARE_PMID(kInterfaceIDSpace, IID_IGTTXTEDTINTERFACE, kGTTxtEdtPrefix + 13)
//DECLARE_PMID(kInterfaceIDSpace, IID_IGTTXTEDTINTERFACE, kGTTxtEdtPrefix + 14)
//DECLARE_PMID(kInterfaceIDSpace, IID_IGTTXTEDTINTERFACE, kGTTxtEdtPrefix + 15)
//DECLARE_PMID(kInterfaceIDSpace, IID_IGTTXTEDTINTERFACE, kGTTxtEdtPrefix + 16)
//DECLARE_PMID(kInterfaceIDSpace, IID_IGTTXTEDTINTERFACE, kGTTxtEdtPrefix + 17)
//DECLARE_PMID(kInterfaceIDSpace, IID_IGTTXTEDTINTERFACE, kGTTxtEdtPrefix + 18)
//DECLARE_PMID(kInterfaceIDSpace, IID_IGTTXTEDTINTERFACE, kGTTxtEdtPrefix + 19)
//DECLARE_PMID(kInterfaceIDSpace, IID_IGTTXTEDTINTERFACE, kGTTxtEdtPrefix + 20)
//DECLARE_PMID(kInterfaceIDSpace, IID_IGTTXTEDTINTERFACE, kGTTxtEdtPrefix + 21)
//DECLARE_PMID(kInterfaceIDSpace, IID_IGTTXTEDTINTERFACE, kGTTxtEdtPrefix + 22)
//DECLARE_PMID(kInterfaceIDSpace, IID_IGTTXTEDTINTERFACE, kGTTxtEdtPrefix + 23)
//DECLARE_PMID(kInterfaceIDSpace, IID_IGTTXTEDTINTERFACE, kGTTxtEdtPrefix + 24)
//DECLARE_PMID(kInterfaceIDSpace, IID_IGTTXTEDTINTERFACE, kGTTxtEdtPrefix + 25)


// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kGTTxtEdtActionComponentImpl,		kGTTxtEdtPrefix + 0 )
DECLARE_PMID(kImplementationIDSpace, kGTTxtEdtControlStripRegisterImpl, kGTTxtEdtPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kGTTxtEdtControlStripSuiteImpl,	kGTTxtEdtPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kGTTxtEdtGoToTextButtonObserverImpl, kGTTxtEdtPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kGTTxtEdtSnapshotInterfaceImpl, kGTTxtEdtPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kGTTxtEdtUtilsImpl, kGTTxtEdtPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kGTTxtEdtStoryObserverImpl, kGTTxtEdtPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kGTTxtEdtServiceProviderImpl, kGTTxtEdtPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kGTTxtEdtResponderImpl, kGTTxtEdtPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kGTTxtEdtNewDeleteStoryObserverImpl, kGTTxtEdtPrefix + 9)
//DECLARE_PMID(kImplementationIDSpace, kGTTxtEdtImpl, kGTTxtEdtPrefix + 10)
//DECLARE_PMID(kImplementationIDSpace, kGTTxtEdtImpl, kGTTxtEdtPrefix + 11)
//DECLARE_PMID(kImplementationIDSpace, kGTTxtEdtImpl, kGTTxtEdtPrefix + 12)
//DECLARE_PMID(kImplementationIDSpace, kGTTxtEdtImpl, kGTTxtEdtPrefix + 13)
//DECLARE_PMID(kImplementationIDSpace, kGTTxtEdtImpl, kGTTxtEdtPrefix + 14)
//DECLARE_PMID(kImplementationIDSpace, kGTTxtEdtImpl, kGTTxtEdtPrefix + 15)
//DECLARE_PMID(kImplementationIDSpace, kGTTxtEdtImpl, kGTTxtEdtPrefix + 16)
//DECLARE_PMID(kImplementationIDSpace, kGTTxtEdtImpl, kGTTxtEdtPrefix + 17)
//DECLARE_PMID(kImplementationIDSpace, kGTTxtEdtImpl, kGTTxtEdtPrefix + 18)
//DECLARE_PMID(kImplementationIDSpace, kGTTxtEdtImpl, kGTTxtEdtPrefix + 19)
//DECLARE_PMID(kImplementationIDSpace, kGTTxtEdtImpl, kGTTxtEdtPrefix + 20)
//DECLARE_PMID(kImplementationIDSpace, kGTTxtEdtImpl, kGTTxtEdtPrefix + 21)
//DECLARE_PMID(kImplementationIDSpace, kGTTxtEdtImpl, kGTTxtEdtPrefix + 22)
//DECLARE_PMID(kImplementationIDSpace, kGTTxtEdtImpl, kGTTxtEdtPrefix + 23)
//DECLARE_PMID(kImplementationIDSpace, kGTTxtEdtImpl, kGTTxtEdtPrefix + 24)
//DECLARE_PMID(kImplementationIDSpace, kGTTxtEdtImpl, kGTTxtEdtPrefix + 25)


// ActionIDs:
DECLARE_PMID(kActionIDSpace, kGTTxtEdtAboutActionID,				kGTTxtEdtPrefix + 0)
DECLARE_PMID(kActionIDSpace, kGTTxtEdtLastUsedActionID,				kGTTxtEdtPrefix + 1)

//DECLARE_PMID(kActionIDSpace, kGTTxtEdtActionID, kGTTxtEdtPrefix + 5)
//DECLARE_PMID(kActionIDSpace, kGTTxtEdtActionID, kGTTxtEdtPrefix + 6)
//DECLARE_PMID(kActionIDSpace, kGTTxtEdtActionID, kGTTxtEdtPrefix + 7)
//DECLARE_PMID(kActionIDSpace, kGTTxtEdtActionID, kGTTxtEdtPrefix + 8)
//DECLARE_PMID(kActionIDSpace, kGTTxtEdtActionID, kGTTxtEdtPrefix + 9)
//DECLARE_PMID(kActionIDSpace, kGTTxtEdtActionID, kGTTxtEdtPrefix + 10)
//DECLARE_PMID(kActionIDSpace, kGTTxtEdtActionID, kGTTxtEdtPrefix + 11)
//DECLARE_PMID(kActionIDSpace, kGTTxtEdtActionID, kGTTxtEdtPrefix + 12)
//DECLARE_PMID(kActionIDSpace, kGTTxtEdtActionID, kGTTxtEdtPrefix + 13)
//DECLARE_PMID(kActionIDSpace, kGTTxtEdtActionID, kGTTxtEdtPrefix + 14)
//DECLARE_PMID(kActionIDSpace, kGTTxtEdtActionID, kGTTxtEdtPrefix + 15)
//DECLARE_PMID(kActionIDSpace, kGTTxtEdtActionID, kGTTxtEdtPrefix + 16)
//DECLARE_PMID(kActionIDSpace, kGTTxtEdtActionID, kGTTxtEdtPrefix + 17)
//DECLARE_PMID(kActionIDSpace, kGTTxtEdtActionID, kGTTxtEdtPrefix + 18)
//DECLARE_PMID(kActionIDSpace, kGTTxtEdtActionID, kGTTxtEdtPrefix + 19)
//DECLARE_PMID(kActionIDSpace, kGTTxtEdtActionID, kGTTxtEdtPrefix + 20)
//DECLARE_PMID(kActionIDSpace, kGTTxtEdtActionID, kGTTxtEdtPrefix + 21)
//DECLARE_PMID(kActionIDSpace, kGTTxtEdtActionID, kGTTxtEdtPrefix + 22)
//DECLARE_PMID(kActionIDSpace, kGTTxtEdtActionID, kGTTxtEdtPrefix + 23)
//DECLARE_PMID(kActionIDSpace, kGTTxtEdtActionID, kGTTxtEdtPrefix + 24)
//DECLARE_PMID(kActionIDSpace, kGTTxtEdtActionID, kGTTxtEdtPrefix + 25)


// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kGTTxtEdtGoToTextButtonWidgetID,			kGTTxtEdtPrefix + 0)
DECLARE_PMID(kWidgetIDSpace, kGTTxtEdtControlStripClusterWidgetID,		kGTTxtEdtPrefix + 1)
DECLARE_PMID(kActionIDSpace, kGTTxtEdtControlStripPanelWidgetID,	kGTTxtEdtPrefix + 2)
//DECLARE_PMID(kWidgetIDSpace, kGTTxtEdtWidgetID, kGTTxtEdtPrefix + 3)
//DECLARE_PMID(kWidgetIDSpace, kGTTxtEdtWidgetID, kGTTxtEdtPrefix + 4)
//DECLARE_PMID(kWidgetIDSpace, kGTTxtEdtWidgetID, kGTTxtEdtPrefix + 5)
//DECLARE_PMID(kWidgetIDSpace, kGTTxtEdtWidgetID, kGTTxtEdtPrefix + 6)
//DECLARE_PMID(kWidgetIDSpace, kGTTxtEdtWidgetID, kGTTxtEdtPrefix + 7)
//DECLARE_PMID(kWidgetIDSpace, kGTTxtEdtWidgetID, kGTTxtEdtPrefix + 8)
//DECLARE_PMID(kWidgetIDSpace, kGTTxtEdtWidgetID, kGTTxtEdtPrefix + 9)
//DECLARE_PMID(kWidgetIDSpace, kGTTxtEdtWidgetID, kGTTxtEdtPrefix + 10)
//DECLARE_PMID(kWidgetIDSpace, kGTTxtEdtWidgetID, kGTTxtEdtPrefix + 11)
//DECLARE_PMID(kWidgetIDSpace, kGTTxtEdtWidgetID, kGTTxtEdtPrefix + 12)
//DECLARE_PMID(kWidgetIDSpace, kGTTxtEdtWidgetID, kGTTxtEdtPrefix + 13)
//DECLARE_PMID(kWidgetIDSpace, kGTTxtEdtWidgetID, kGTTxtEdtPrefix + 14)
//DECLARE_PMID(kWidgetIDSpace, kGTTxtEdtWidgetID, kGTTxtEdtPrefix + 15)
//DECLARE_PMID(kWidgetIDSpace, kGTTxtEdtWidgetID, kGTTxtEdtPrefix + 16)
//DECLARE_PMID(kWidgetIDSpace, kGTTxtEdtWidgetID, kGTTxtEdtPrefix + 17)
//DECLARE_PMID(kWidgetIDSpace, kGTTxtEdtWidgetID, kGTTxtEdtPrefix + 18)
//DECLARE_PMID(kWidgetIDSpace, kGTTxtEdtWidgetID, kGTTxtEdtPrefix + 19)
//DECLARE_PMID(kWidgetIDSpace, kGTTxtEdtWidgetID, kGTTxtEdtPrefix + 20)
//DECLARE_PMID(kWidgetIDSpace, kGTTxtEdtWidgetID, kGTTxtEdtPrefix + 21)
//DECLARE_PMID(kWidgetIDSpace, kGTTxtEdtWidgetID, kGTTxtEdtPrefix + 22)
//DECLARE_PMID(kWidgetIDSpace, kGTTxtEdtWidgetID, kGTTxtEdtPrefix + 23)
//DECLARE_PMID(kWidgetIDSpace, kGTTxtEdtWidgetID, kGTTxtEdtPrefix + 24)
//DECLARE_PMID(kWidgetIDSpace, kGTTxtEdtWidgetID, kGTTxtEdtPrefix + 25)

// InvalHandlerTypeID
DECLARE_PMID(kInvalHandlerIDSpace, kGTTxtEdtInvalHandlerID, kGTTxtEdtPrefix + 0)

// "About Plug-ins" sub-menu:
#define kGTTxtEdtAboutMenuKey			kGTTxtEdtStringPrefix "kGTTxtEdtAboutMenuKey"
#define kGTTxtEdtAboutMenuPath		kSDKDefStandardAboutMenuPath kGTTxtEdtCompanyKey

// "Plug-ins" sub-menu:
#define kGTTxtEdtPluginsMenuKey 		kGTTxtEdtStringPrefix "kGTTxtEdtPluginsMenuKey"
#define kGTTxtEdtPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kGTTxtEdtCompanyKey kSDKDefDelimitMenuPath kGTTxtEdtPluginsMenuKey

// Menu item keys:

// Other StringKeys:
#define kGTTxtEdtAboutBoxStringKey	kGTTxtEdtStringPrefix "kGTTxtEdtAboutBoxStringKey"
#define kGTTxtEdtTargetMenuPath kGTTxtEdtPluginsMenuPath
#define kGTTxtEdtGoToTextButtonTipKey			kGTTxtEdtStringPrefix "kGTTxtEdtGoToTextButtonTipKey"
#define kNoLastStoryKey			kGTTxtEdtStringPrefix "kNoLastStoryKey"
// Menu item positions:

// control strip priority
const PMReal kGTTxtEdtControlStripPriority = 8047;

// Initial data format version numbers
#define kGTTxtEdtFirstMajorFormatNumber  kSDKDef_50_PersistMajorVersionNumber
#define kGTTxtEdtFirstMinorFormatNumber  kSDKDef_50_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kGTTxtEdtCurrentMajorFormatNumber kGTTxtEdtFirstMajorFormatNumber
#define kGTTxtEdtCurrentMinorFormatNumber kGTTxtEdtFirstMinorFormatNumber

#endif // __GTTxtEdtID_h__

//  Code generated by DollyXs code generator
