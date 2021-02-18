//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/CustomHttpLinkUI/CustomHttpLinkUIID.h $
//  
//  Owner: swagarg
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//
//  ADOBE CONFIDENTIAL
//  
//  Copyright 2019 Adobe
//  All Rights Reserved.
//
//  NOTICE: Adobe permits you to use, modify, and distribute this file in
//  accordance with the terms of the Adobe license agreement accompanying
//  it. If you have received this file from a source other than Adobe,
//  then your use, modification, or distribution of it requires the prior
//  written permission of Adobe. 
//  
//========================================================================================


#ifndef __CustomHttpLinkUIID_h__
#define __CustomHttpLinkUIID_h__

#include "SDKDef.h"

// Company:
#define kCustomHttpLinkUICompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kCustomHttpLinkUICompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kCustomHttpLinkUIPluginName	"CustomHttpLinkUI"			// Name of this plug-in.
#define kCustomHttpLinkUIPrefixNumber	0x1DCD02 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kCustomHttpLinkUIVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kCustomHttpLinkUIAuthor		"Adobe Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kCustomHttpLinkUIPrefixNumber above to modify the prefix.)
#define kCustomHttpLinkUIPrefix		RezLong(kCustomHttpLinkUIPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kCustomHttpLinkUIStringPrefix	SDK_DEF_STRINGIZE(kCustomHttpLinkUIPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// Missing plug-in: (see ExtraPluginInfo resource)
#define kCustomHttpLinkUIMissingPluginURLValue		kSDKDefPartnersStandardValue_enUS // URL displayed in Missing Plug-in dialog
#define kCustomHttpLinkUIMissingPluginAlertValue	kSDKDefMissingPluginAlertValue // Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem


// PluginID:
DECLARE_PMID(kPlugInIDSpace, kCustomHttpLinkUIPluginID, kCustomHttpLinkUIPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kCustomHttpLinkUIActionComponentBoss, kCustomHttpLinkUIPrefix + 0)
DECLARE_PMID(kClassIDSpace, kCustomHttpLinkUIPanelWidgetBoss, kCustomHttpLinkUIPrefix + 1)
DECLARE_PMID(kClassIDSpace, kPlaceButtonBoss, kCustomHttpLinkUIPrefix + 3)
DECLARE_PMID(kClassIDSpace, kCustomHttpLinkUIMenuBoss, kCustomHttpLinkUIPrefix + 4)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkUIBoss, kCustomHttpLinkUIPrefix + 5)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkUIBoss, kCustomHttpLinkUIPrefix + 6)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkUIBoss, kCustomHttpLinkUIPrefix + 7)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkUIBoss, kCustomHttpLinkUIPrefix + 8)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkUIBoss, kCustomHttpLinkUIPrefix + 9)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkUIBoss, kCustomHttpLinkUIPrefix + 10)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkUIBoss, kCustomHttpLinkUIPrefix + 11)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkUIBoss, kCustomHttpLinkUIPrefix + 12)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkUIBoss, kCustomHttpLinkUIPrefix + 13)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkUIBoss, kCustomHttpLinkUIPrefix + 14)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkUIBoss, kCustomHttpLinkUIPrefix + 15)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkUIBoss, kCustomHttpLinkUIPrefix + 16)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkUIBoss, kCustomHttpLinkUIPrefix + 17)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkUIBoss, kCustomHttpLinkUIPrefix + 18)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkUIBoss, kCustomHttpLinkUIPrefix + 19)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkUIBoss, kCustomHttpLinkUIPrefix + 20)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkUIBoss, kCustomHttpLinkUIPrefix + 21)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkUIBoss, kCustomHttpLinkUIPrefix + 22)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkUIBoss, kCustomHttpLinkUIPrefix + 23)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkUIBoss, kCustomHttpLinkUIPrefix + 24)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkUIBoss, kCustomHttpLinkUIPrefix + 25)


// InterfaceIDs:
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKUIINTERFACE, kCustomHttpLinkUIPrefix + 0)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKUIINTERFACE, kCustomHttpLinkUIPrefix + 1)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKUIINTERFACE, kCustomHttpLinkUIPrefix + 2)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKUIINTERFACE, kCustomHttpLinkUIPrefix + 3)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKUIINTERFACE, kCustomHttpLinkUIPrefix + 4)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKUIINTERFACE, kCustomHttpLinkUIPrefix + 5)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKUIINTERFACE, kCustomHttpLinkUIPrefix + 6)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKUIINTERFACE, kCustomHttpLinkUIPrefix + 7)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKUIINTERFACE, kCustomHttpLinkUIPrefix + 8)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKUIINTERFACE, kCustomHttpLinkUIPrefix + 9)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKUIINTERFACE, kCustomHttpLinkUIPrefix + 10)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKUIINTERFACE, kCustomHttpLinkUIPrefix + 11)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKUIINTERFACE, kCustomHttpLinkUIPrefix + 12)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKUIINTERFACE, kCustomHttpLinkUIPrefix + 13)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKUIINTERFACE, kCustomHttpLinkUIPrefix + 14)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKUIINTERFACE, kCustomHttpLinkUIPrefix + 15)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKUIINTERFACE, kCustomHttpLinkUIPrefix + 16)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKUIINTERFACE, kCustomHttpLinkUIPrefix + 17)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKUIINTERFACE, kCustomHttpLinkUIPrefix + 18)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKUIINTERFACE, kCustomHttpLinkUIPrefix + 19)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKUIINTERFACE, kCustomHttpLinkUIPrefix + 20)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKUIINTERFACE, kCustomHttpLinkUIPrefix + 21)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKUIINTERFACE, kCustomHttpLinkUIPrefix + 22)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKUIINTERFACE, kCustomHttpLinkUIPrefix + 23)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKUIINTERFACE, kCustomHttpLinkUIPrefix + 24)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKUIINTERFACE, kCustomHttpLinkUIPrefix + 25)


// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkUIActionComponentImpl, kCustomHttpLinkUIPrefix + 0 )
DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkUIPlaceButtonObserverImpl, kCustomHttpLinkUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkUIObserverImpl, kCustomHttpLinkUIPrefix + 2)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkUIImpl, kCustomHttpLinkUIPrefix + 3)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkUIImpl, kCustomHttpLinkUIPrefix + 4)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkUIImpl, kCustomHttpLinkUIPrefix + 5)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkUIImpl, kCustomHttpLinkUIPrefix + 6)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkUIImpl, kCustomHttpLinkUIPrefix + 7)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkUIImpl, kCustomHttpLinkUIPrefix + 8)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkUIImpl, kCustomHttpLinkUIPrefix + 9)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkUIImpl, kCustomHttpLinkUIPrefix + 10)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkUIImpl, kCustomHttpLinkUIPrefix + 11)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkUIImpl, kCustomHttpLinkUIPrefix + 12)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkUIImpl, kCustomHttpLinkUIPrefix + 13)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkUIImpl, kCustomHttpLinkUIPrefix + 14)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkUIImpl, kCustomHttpLinkUIPrefix + 15)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkUIImpl, kCustomHttpLinkUIPrefix + 16)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkUIImpl, kCustomHttpLinkUIPrefix + 17)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkUIImpl, kCustomHttpLinkUIPrefix + 18)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkUIImpl, kCustomHttpLinkUIPrefix + 19)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkUIImpl, kCustomHttpLinkUIPrefix + 20)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkUIImpl, kCustomHttpLinkUIPrefix + 21)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkUIImpl, kCustomHttpLinkUIPrefix + 22)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkUIImpl, kCustomHttpLinkUIPrefix + 23)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkUIImpl, kCustomHttpLinkUIPrefix + 24)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkUIImpl, kCustomHttpLinkUIPrefix + 25)


// ActionIDs:
DECLARE_PMID(kActionIDSpace, kCustomHttpLinkUIAboutActionID, kCustomHttpLinkUIPrefix + 0)
DECLARE_PMID(kActionIDSpace, kCustomHttpLinkUIPanelWidgetActionID, kCustomHttpLinkUIPrefix + 1)
DECLARE_PMID(kActionIDSpace, kCustomHttpLinkUISeparator1ActionID, kCustomHttpLinkUIPrefix + 2)
DECLARE_PMID(kActionIDSpace, kCustomHttpLinkUIPopupAboutThisActionID, kCustomHttpLinkUIPrefix + 3)
DECLARE_PMID(kActionIDSpace, kCustomHttpLinkUILoginActionID, kCustomHttpLinkUIPrefix + 4)
DECLARE_PMID(kActionIDSpace, kCustomHttpLinkUILogoutActionID, kCustomHttpLinkUIPrefix + 5)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkUIActionID, kCustomHttpLinkUIPrefix + 11)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkUIActionID, kCustomHttpLinkUIPrefix + 12)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkUIActionID, kCustomHttpLinkUIPrefix + 13)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkUIActionID, kCustomHttpLinkUIPrefix + 14)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkUIActionID, kCustomHttpLinkUIPrefix + 15)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkUIActionID, kCustomHttpLinkUIPrefix + 16)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkUIActionID, kCustomHttpLinkUIPrefix + 17)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkUIActionID, kCustomHttpLinkUIPrefix + 18)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkUIActionID, kCustomHttpLinkUIPrefix + 19)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkUIActionID, kCustomHttpLinkUIPrefix + 20)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkUIActionID, kCustomHttpLinkUIPrefix + 21)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkUIActionID, kCustomHttpLinkUIPrefix + 22)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkUIActionID, kCustomHttpLinkUIPrefix + 23)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkUIActionID, kCustomHttpLinkUIPrefix + 24)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkUIActionID, kCustomHttpLinkUIPrefix + 25)


// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkUIPanelWidgetID, kCustomHttpLinkUIPrefix + 0)
DECLARE_PMID(kWidgetIDSpace, kChooseFileWidgetID, kCustomHttpLinkUIPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kFileListWidgetID, kCustomHttpLinkUIPrefix + 3)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkUIWidgetID, kCustomHttpLinkUIPrefix + 4)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkUIWidgetID, kCustomHttpLinkUIPrefix + 5)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkUIWidgetID, kCustomHttpLinkUIPrefix + 6)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkUIWidgetID, kCustomHttpLinkUIPrefix + 7)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkUIWidgetID, kCustomHttpLinkUIPrefix + 8)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkUIWidgetID, kCustomHttpLinkUIPrefix + 9)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkUIWidgetID, kCustomHttpLinkUIPrefix + 10)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkUIWidgetID, kCustomHttpLinkUIPrefix + 11)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkUIWidgetID, kCustomHttpLinkUIPrefix + 12)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkUIWidgetID, kCustomHttpLinkUIPrefix + 13)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkUIWidgetID, kCustomHttpLinkUIPrefix + 14)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkUIWidgetID, kCustomHttpLinkUIPrefix + 15)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkUIWidgetID, kCustomHttpLinkUIPrefix + 16)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkUIWidgetID, kCustomHttpLinkUIPrefix + 17)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkUIWidgetID, kCustomHttpLinkUIPrefix + 18)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkUIWidgetID, kCustomHttpLinkUIPrefix + 19)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkUIWidgetID, kCustomHttpLinkUIPrefix + 20)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkUIWidgetID, kCustomHttpLinkUIPrefix + 21)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkUIWidgetID, kCustomHttpLinkUIPrefix + 22)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkUIWidgetID, kCustomHttpLinkUIPrefix + 23)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkUIWidgetID, kCustomHttpLinkUIPrefix + 24)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkUIWidgetID, kCustomHttpLinkUIPrefix + 25)


// "About Plug-ins" sub-menu:
#define kCustomHttpLinkUIAboutMenuKey			kCustomHttpLinkUIStringPrefix "kCustomHttpLinkUIAboutMenuKey"
#define kCustomHttpLinkUIAboutMenuPath		kSDKDefStandardAboutMenuPath kCustomHttpLinkUICompanyKey

// "Plug-ins" sub-menu:
#define kCustomHttpLinkUIPluginsMenuKey 		kCustomHttpLinkUIStringPrefix "kCustomHttpLinkUIPluginsMenuKey"
#define kCustomHttpLinkUIPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kCustomHttpLinkUICompanyKey kSDKDefDelimitMenuPath kCustomHttpLinkUIPluginsMenuKey

// Menu item keys:

// Other StringKeys:
#define kCustomHttpLinkUIAboutBoxStringKey	kCustomHttpLinkUIStringPrefix "kCustomHttpLinkUIAboutBoxStringKey"
#define kCustomHttpLinkUIPanelTitleKey					kCustomHttpLinkUIStringPrefix	"kCustomHttpLinkUIPanelTitleKey"
#define kCustomHttpLinkUIStaticTextKey kCustomHttpLinkUIStringPrefix	"kCustomHttpLinkUIStaticTextKey"
#define kCustomHttpLinkUIInternalPopupMenuNameKey kCustomHttpLinkUIStringPrefix	"kCustomHttpLinkUIInternalPopupMenuNameKey"
#define kCustomHttpLinkUITargetMenuPath kCustomHttpLinkUIInternalPopupMenuNameKey

// Menu item positions:

#define	kCustomHttpLinkUISeparator1MenuItemPosition		10.0
#define kCustomHttpLinkUIAboutThisMenuItemPosition		11.0
#define kCustomHttpLinkUILoginMenuItemPosition          12.0
#define kCustomHttpLinkUILogoutMenuItemPosition         13.0


// Initial data format version numbers
#define kCustomHttpLinkUIFirstMajorFormatNumber  RezLong(1)
#define kCustomHttpLinkUIFirstMinorFormatNumber  RezLong(0)

// Data format version numbers for the PluginVersion resource 
#define kCustomHttpLinkUICurrentMajorFormatNumber kCustomHttpLinkUIFirstMajorFormatNumber
#define kCustomHttpLinkUICurrentMinorFormatNumber kCustomHttpLinkUIFirstMinorFormatNumber

#define kCusHttpLnkScheme "myhost"
#define kCusHttpLnkAuthority "localhost:3000"

#endif // __CustomHttpLinkUIID_h__
