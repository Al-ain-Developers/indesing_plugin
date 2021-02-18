//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicpersistinterfaceui/BPIUIID.h $
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
//  Defines IDs used by the BPI plug-in.
//  
//========================================================================================

#ifndef __BPIUIID_h__
#define __BPIUIID_h__

#include "SDKDef.h"

// Company:
#define kBPIUICompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kBPIUICompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kBPIUIPluginName	"BasicPersistInterfaceUI"			// Name of this plug-in.
#define kBPIUIPrefixNumber	0x13de00 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kBPIUIVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kBPIUIAuthor		"Adobe Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kBPIUIPrefixNumber above to modify the prefix.)
#define kBPIUIPrefix		RezLong(kBPIUIPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kBPIUIStringPrefix	SDK_DEF_STRINGIZE(kBPIUIPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kBPIUIPluginID, kBPIUIPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kBPIUIActionComponentBoss,	kBPIUIPrefix + 0)
DECLARE_PMID(kClassIDSpace, kBPIUIPanelWidgetBoss,		kBPIUIPrefix + 1)
DECLARE_PMID(kClassIDSpace, kBPIUIDialogBoss,	kBPIUIPrefix + 2)

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kBPIUIActionComponentImpl,		kBPIUIPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kBPIUIDlgControllerImpl, kBPIUIPrefix + 1)	
// No dialog widgets really need dynamic handling DECLARE_PMID(kImplementationIDSpace, kBPIDlgObserverImpl, kBPIUIPrefix + 2)	
DECLARE_PMID(kImplementationIDSpace, kBPIUISelectionObserverImpl, kBPIUIPrefix + 2)	

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kBPIUIAboutActionID,				kBPIUIPrefix + 0)
DECLARE_PMID(kActionIDSpace, kBPIUIPanelWidgetActionID,			kBPIUIPrefix + 1)
DECLARE_PMID(kActionIDSpace, kBPIUISeparator1ActionID,			kBPIUIPrefix + 2)
DECLARE_PMID(kActionIDSpace, kBPIUIPopupAboutThisActionID,		kBPIUIPrefix + 3)
DECLARE_PMID(kActionIDSpace, kBPIUISetBPIDataActionID,			kBPIUIPrefix + 4)

// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kBPIUIPanelWidgetID,			kBPIUIPrefix + 0) 
DECLARE_PMID(kWidgetIDSpace, kBPIUIDialogWidgetID,			kBPIUIPrefix + 1) 
DECLARE_PMID(kWidgetIDSpace, kBPIUIIconSuiteWidgetID,		kBPIUIPrefix + 2) 
DECLARE_PMID(kWidgetIDSpace, kBPIUIStaticTextWidgetID,		kBPIUIPrefix + 3) 
DECLARE_PMID(kWidgetIDSpace, kBPIUIEditBoxWidgetID,			kBPIUIPrefix + 4) 
DECLARE_PMID(kWidgetIDSpace, kBPIUILabelWidgetID,				kBPIUIPrefix + 5) 
DECLARE_PMID(kWidgetIDSpace, kBPIUIDataWidgetID,				kBPIUIPrefix + 6) 
DECLARE_PMID(kWidgetIDSpace, kBPIUIDataScrollBarWidgetID,		kBPIUIPrefix + 7) //sa3.0+

// "About Plug-ins" sub-menu:
#define kBPIUIAboutMenuKey			kBPIUIStringPrefix "kBPIUIAboutMenuKey"
#define kBPIUIAboutMenuPath			kSDKDefStandardAboutMenuPath kBPIUICompanyKey

// "Plug-ins" sub-menu:
#define kBPIUIPluginsMenuKey 		kBPIUIStringPrefix "kBPIUIPluginsMenuKey"
#define kBPIUIPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kBPIUICompanyKey kSDKDefDelimitMenuPath kBPIUIPluginsMenuKey

// Menu item keys:
#define kBPIUISetBPIDataMenuItemKey		kBPIUIStringPrefix "kBPIUISetBPIDataMenuItemKey"
//#define kBPIUICommandStringKey			kBPIUIStringPrefix "kBPIUICommandStringKey"

// Other StringKeys:
#define kBPIUIAboutBoxStringKey				kBPIUIStringPrefix "kBPIUIAboutBoxStringKey"
#define kBPIUISetBPIDataStringKey			kBPIUIStringPrefix "kBPIUISetBPIDataStringKey"
#define kBPIUIPanelTitleKey					kBPIUIStringPrefix	"kBPUIIPanelTitleKey"
#define kBPIUIInternalPopupMenuNameKey		kBPIUIStringPrefix	"kBPIUIInternalPopupMenuNameKey"
#define kBPIUITargetMenuPath kBPIUIInternalPopupMenuNameKey
#define kBPIUIDlgTitleKey					kBPIUIStringPrefix	"kBPIUIDlgTitleKey"
#define kBPIUIDataStaticTextKey					kBPIUIStringPrefix	"kBPIUIDataStaticTextKey"
#define kBPIUINoValidPageItemsSelectedKey		kBPIUIStringPrefix "kBPIUINoValidPageItemsSelectedKey"
#define kBPIUISetBPIDataCmdFailedKey		kBPIUIStringPrefix "kBPIUISetBPIDataCmdFailedKey"
#define kBPIUIDefaultStringKey		kBPIUIStringPrefix "kBPIUISetBPIDefaultStringKey"

// Menu item positions:
#define kBPIUISetBPIDataMenuItemPosition			1.0
#define	kBPIUISeparator1MenuItemPosition			10.0
#define kBPIUIAboutThisMenuItemPosition				11.0


// InDesign CS4 format changes
#define kBPIUIStoreWideStringMajorFormat		kSDKDef_50_PersistMajorVersionNumber
#define kBPIUIStoreWideStringMinorFormat		1

// Data format version numbers for the PluginVersion resource 
#define kBPIUILastMajorFormatChange	kBPIUIStoreWideStringMajorFormat		// Most recent major format change
#define kBPIUILastMinorFormatChange	kBPIUIStoreWideStringMinorFormat		// Most recent minor format change


#endif // __BPIUIID_h__
//  Generated by Dolly build 11: template "IfPanelMenu".

// End, BPIUIID.h.




