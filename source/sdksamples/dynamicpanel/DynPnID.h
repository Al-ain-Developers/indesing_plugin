//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/dynamicpanel/DynPnID.h $
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

#ifndef __DynPnID_h__
#define __DynPnID_h__

#include "SDKDef.h"

// Company:
#define kDynPnCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kDynPnCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kDynPnPluginName	"DynamicPanel"			// Name of this plug-in.
#define kDynPnPrefixNumber	0x5c2a0 				// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kDynPnVersion		kSDKDefPluginVersionString					// Version of this plug-in (for the About Box).
#define kDynPnAuthor		"Adobe Developer Technologies"				// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kDynPnPrefixNumber above to modify the prefix.)
#define kDynPnPrefix		RezLong(kDynPnPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kDynPnStringPrefix	SDK_DEF_STRINGIZE(kDynPnPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kDynPnPluginID, kDynPnPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kDynPnActionComponentBoss,		kDynPnPrefix + 0)
DECLARE_PMID(kClassIDSpace, kDynPnPanelWidgetBoss,			kDynPnPrefix + 4)
DECLARE_PMID(kClassIDSpace, kDynPnMgrActionComponentBoss,	kDynPnPrefix + 6)
DECLARE_PMID(kClassIDSpace, kDynPnPanelManagerBoss,			kDynPnPrefix + 7)

// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_IDynPnPANELMANAGER,	kDynPnPrefix + 0)
DECLARE_PMID(kInterfaceIDSpace,IID_IDynPnPERSISTUIDDATA,	kDynPnPrefix + 1)

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kDynPnActionComponentImpl,			kDynPnPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kDynPnMgrActionComponentImpl,		kDynPnPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kDynPnPanelManagerImpl,			kDynPnPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kDynPnPersistUIDRefDataImpl,		kDynPnPrefix + 3)
  
// ActionIDs:
DECLARE_PMID(kActionIDSpace, kDynPnAboutActionID,				kDynPnPrefix + 0)
DECLARE_PMID(kActionIDSpace, kDynPnPanelWidgetActionID,			kDynPnPrefix + 1)
DECLARE_PMID(kActionIDSpace, kDynPnSeparator1ActionID,			kDynPnPrefix + 2)
DECLARE_PMID(kActionIDSpace, kDynPnPopupAboutThisActionID,		kDynPnPrefix + 3)
DECLARE_PMID(kActionIDSpace, kDynPnSomethingActionID,			kDynPnPrefix + 4)
DECLARE_PMID(kActionIDSpace, kDynPnMgrNewPanelActionID,			kDynPnPrefix + 5)
DECLARE_PMID(kActionIDSpace, kDynPnMgrClosePanelActionID,		kDynPnPrefix + 6)
DECLARE_PMID(kActionIDSpace, kDynPnMenuSeparatorActionID,		kDynPnPrefix + 7)
DECLARE_PMID(kActionIDSpace, kDynPnFirstPanelActionID,			kDynPnPrefix + 8)

// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kDynPnPanelWidgetID,				kDynPnPrefix + 0) 
 
// "About Plug-ins" sub-menu:
#define kDynPnAboutMenuKey			kDynPnStringPrefix "kDynPnAboutMenuKey"
#define kDynPnAboutMenuPath			kSDKDefStandardAboutMenuPath kDynPnCompanyKey

// "Plug-ins" sub-menu:
#define kDynPnPluginsMenuKey 		kDynPnStringPrefix "kDynPnPluginsMenuKey"
#define kDynPnPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kDynPnCompanyKey kSDKDefDelimitMenuPath kDynPnPluginsMenuKey

// Menu item keys:
#define kDynPnSomethingMenuItemKey			kDynPnStringPrefix "kDynPnSomethingMenuItemKey"
#define kDynPnMgrNewPanelMenuItemKey		kDynPnStringPrefix "kDynPnMgrNewPanelMenuItemKey"
#define kDynPnMgrClosePanelMenuItemKey		kDynPnStringPrefix "kDynPnMgrClosePanelMenuItemKey"

// Other StringKeys:
#define kDynPnAboutBoxStringKey				kDynPnStringPrefix "kDynPnAboutBoxStringKey"
#define kDynPnSomethingStringKey			kDynPnStringPrefix "kDynPnSomethingStringKey"
#define kDynPnPanelTitleKey					kDynPnStringPrefix	"kDynPnPanelTitleKey"
#define kDynPnStaticTextKey					kDynPnStringPrefix	"kDynPnStaticTextKey"
#define kDynPnInternalPopupMenuNameKey		kDynPnStringPrefix	"kDynPnInternalPopupMenuNameKey"
#define kDynPnTargetMenuPath				kDynPnInternalPopupMenuNameKey
#define kDynPnMgrPluginsMenuPath			kSDKDefPlugInsStandardMenuPath kDynPnCompanyKey kSDKDefDelimitMenuPath kDynPnPluginsMenuKey
#define kDynPnMgrTargetMenuPath kDynPnMgrPluginsMenuPath

// Menu item positions: these are the ones on the Plug-ins menu
#define kDynPnSomethingMenuItemPosition			1.0
#define kDynPnSeparator1MenuItemPosition		10.0
#define kDynPnAboutThisMenuItemPosition			11.0
#define kDynPnMgrNewPanelMenuItemPosition		1.0
#define kDynPnMgrClosePanelMenuItemPosition		2.0
// Positions on the Windows menu
#define kDynPnMenuSeparatorPosition kWindowLastPanelMenuPosition + 1.0
#define kDynPnMenuPosition kWindowLastPanelMenuPosition + 2.0
#define kDynPnDynamicPanelNameStart "DynaPanel "

// On Windows menu...

// Initial Data format IDs of the persistent data was first introduced in InDesign 2.0
#define kDynPnInitialMajorFormat		kSDKDef_20_PersistMajorVersionNumber
#define kDynPnInitialMinorFormat		kSDKDef_20_PersistMinorVersionNumber
// Note: The data format has not been changed since InDesign 2.0.

// Format IDs for the PluginVersion resource 
#define kDynPnLastMajorFormatChange	kDynPnInitialMajorFormat		// Last major format change
#define kDynPnLastMinorFormatChange	kDynPnInitialMinorFormat		// Last minor format change


#endif // __DynPnID_h__
//  Generated by Dolly build 17: template "IfPanelMenu".
// End, DynPnID.h.



