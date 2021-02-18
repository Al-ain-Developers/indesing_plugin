//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/linkwatcher/LnkWtchID.h $
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
//  Defines IDs used by the LnkWtch plug-in.
//  
//========================================================================================

#ifndef __LnkWtchID_h__
#define __LnkWtchID_h__

#include "SDKDef.h"

// Comment out the #define below to build with the SDK for the InDesign CS2 Product Family.
// Leave the #define below to build with the SDK for the InDesign CS3 Product Family.
#define SDKAUTOUNDO 1


// Company:
#define kLnkWtchCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kLnkWtchCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kLnkWtchPluginName	"LinkWatcher"			// Name of this plug-in.
#define kLnkWtchPrefixNumber	0xddc00 				// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kLnkWtchVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kLnkWtchAuthor		"Adobe Developer Technologies"				// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kLnkWtchPrefixNumber above to modify the prefix.)
#define kLnkWtchPrefix		RezLong(kLnkWtchPrefixNumber)			// The unique numeric prefix for all object model IDs for this plug-in.
#define kLnkWtchStringPrefix	SDK_DEF_STRINGIZE(kLnkWtchPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kLnkWtchPluginID, kLnkWtchPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kLnkWtchActionComponentBoss,	kLnkWtchPrefix + 0)
DECLARE_PMID(kClassIDSpace, kLnkWtchPanelWidgetBoss,		kLnkWtchPrefix + 1)
DECLARE_PMID(kClassIDSpace, kLnkWtchListBoxWidgetBoss,	kLnkWtchPrefix + 2)
DECLARE_PMID(kClassIDSpace, kLnkWtchTextWidgetBoss,		kLnkWtchPrefix + 3)

DECLARE_PMID(kClassIDSpace, kLnkWtchNewDocResponderBoss,	kLnkWtchPrefix + 10)
DECLARE_PMID(kClassIDSpace, kLnkWtchOpenDocResponderBoss,	kLnkWtchPrefix + 11)
DECLARE_PMID(kClassIDSpace, kLnkWtchCloseDocResponderBoss,	kLnkWtchPrefix + 12)

// <Message ID> // note - message ids conflict with class ids.
DECLARE_PMID(kMessageIDSpace, kLnkWtchCacheChangedMessage,	kLnkWtchPrefix + 20)

// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_ILNKWTCHCACHEMANAGER,	kLnkWtchPrefix + 0)
DECLARE_PMID(kInterfaceIDSpace, IID_ILNKWTCHCACHE,		kLnkWtchPrefix + 1)

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, 	kLnkWtchActionComponentImpl,		kLnkWtchPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, 	kLnkWtchActiveContextObserverImpl,		kLnkWtchPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kLnkWtchDocResponderImpl,		kLnkWtchPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kLnkWtchCacheManagerImpl,		kLnkWtchPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kLnkWtchCacheImpl,		kLnkWtchPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kLnkWtchTreeViewAdapterImpl,		kLnkWtchPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kLnkWtchTreeViewWidgetMgrImpl,		kLnkWtchPrefix + 6)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kLnkWtchPanelWidgetActionID,		kLnkWtchPrefix + 1)
DECLARE_PMID(kActionIDSpace, kLnkWtchPopupAboutThisActionID,		kLnkWtchPrefix + 3)

// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kLnkWtchPanelWidgetID,				kLnkWtchPrefix + 0) 
DECLARE_PMID(kWidgetIDSpace, kLnkWtchTextWidgetID,				kLnkWtchPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kLnkWtchListParentWidgetId,			kLnkWtchPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kLnkWtchListBoxWidgetID,			kLnkWtchPrefix + 3)

// "About Plug-ins" sub-menu:
#define kLnkWtchAboutMenuKey			kLnkWtchStringPrefix "kLnkWtchAboutMenuKey"
#define kLnkWtchTargetMenuPath kLnkWtchInternalPopupMenuNameKey

// Other StringKeys:
#define kLnkWtchAboutBoxStringKey			kLnkWtchStringPrefix "kLnkWtchAboutBoxStringKey"
#define kLnkWtchPanelTitleKey				kLnkWtchStringPrefix	"kLnkWtchPanelTitleKey"
#define kLnkWtchInternalPopupMenuNameKey		kLnkWtchStringPrefix	"kLnkWtchInternalPopupMenuNameKey"
#define kLnkWtchItemBaseKey					kLnkWtchStringPrefix "kLnkWtchItemBaseKey"



// Menu item positions:
#define kLnkWtchAboutThisMenuItemPosition		11.0

// Initial data format version numbers
#define kLnkWtchFirstMajorFormatNumber  kSDKDef_40_PersistMajorVersionNumber
#define kLnkWtchFirstMinorFormatNumber  kSDKDef_40_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kLnkWtchCurrentMajorFormatNumber kLnkWtchFirstMajorFormatNumber // most recent major format change
#define kLnkWtchCurrentMinorFormatNumber kLnkWtchFirstMinorFormatNumber // most recent minor format change

// ResourceIDs:
#define kLnkWtchListElementRsrcID 	1200

#endif // __LnkWtchID_h__

// End, LnkWtchID.h.


