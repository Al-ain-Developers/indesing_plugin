//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/CustomHttpLink/CustomHttpLinkID.h $
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


#ifndef __CustomHttpLinkID_h__
#define __CustomHttpLinkID_h__

#include "SDKDef.h"

// Company:
#define kCustomHttpLinkCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kCustomHttpLinkCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kCustomHttpLinkPluginName	"CustomHttpLink.sdk"			// Name of this plug-in.
#define kCustomHttpLinkPrefixNumber	0x1DCE00 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kCustomHttpLinkVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kCustomHttpLinkAuthor		"Adobe Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kCustomHttpLinkPrefixNumber above to modify the prefix.)
#define kCustomHttpLinkPrefix		RezLong(kCustomHttpLinkPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kCustomHttpLinkStringPrefix	SDK_DEF_STRINGIZE(kCustomHttpLinkPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// Missing plug-in: (see ExtraPluginInfo resource)
#define kCustomHttpLinkMissingPluginURLValue		kSDKDefPartnersStandardValue_enUS // URL displayed in Missing Plug-in dialog
#define kCustomHttpLinkMissingPluginAlertValue	kSDKDefMissingPluginAlertValue // Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem


// login information keys
#define username_key  "username"
#define password_key  "password"
#define token_key  "token"


// PluginID:
DECLARE_PMID(kPlugInIDSpace, kCustomHttpLinkPluginID, kCustomHttpLinkPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kCusHttpLnkLinkResourceProviderBoss, kCustomHttpLinkPrefix + 3)
DECLARE_PMID(kClassIDSpace, kCusHttpLnkLinkResourceHandlerBoss, kCustomHttpLinkPrefix + 4)
DECLARE_PMID(kClassIDSpace, kCusHttpLnkLinkResourceStateUpdaterBoss, kCustomHttpLinkPrefix + 5)
DECLARE_PMID(kClassIDSpace, kCusHttpLnkLinkResourceHelperBoss, kCustomHttpLinkPrefix + 6)
DECLARE_PMID(kClassIDSpace, kCusHttpLnkLinkResourceServerHelperBoss, kCustomHttpLinkPrefix + 7)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkBoss, kCustomHttpLinkPrefix + 8)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkBoss, kCustomHttpLinkPrefix + 9)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkBoss, kCustomHttpLinkPrefix + 10)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkBoss, kCustomHttpLinkPrefix + 11)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkBoss, kCustomHttpLinkPrefix + 12)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkBoss, kCustomHttpLinkPrefix + 13)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkBoss, kCustomHttpLinkPrefix + 14)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkBoss, kCustomHttpLinkPrefix + 15)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkBoss, kCustomHttpLinkPrefix + 16)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkBoss, kCustomHttpLinkPrefix + 17)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkBoss, kCustomHttpLinkPrefix + 18)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkBoss, kCustomHttpLinkPrefix + 19)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkBoss, kCustomHttpLinkPrefix + 20)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkBoss, kCustomHttpLinkPrefix + 21)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkBoss, kCustomHttpLinkPrefix + 22)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkBoss, kCustomHttpLinkPrefix + 23)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkBoss, kCustomHttpLinkPrefix + 24)
//DECLARE_PMID(kClassIDSpace, kCustomHttpLinkBoss, kCustomHttpLinkPrefix + 25)


// InterfaceIDs:
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKINTERFACE, kCustomHttpLinkPrefix + 0)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKINTERFACE, kCustomHttpLinkPrefix + 1)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKINTERFACE, kCustomHttpLinkPrefix + 2)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKINTERFACE, kCustomHttpLinkPrefix + 3)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKINTERFACE, kCustomHttpLinkPrefix + 4)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKINTERFACE, kCustomHttpLinkPrefix + 5)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKINTERFACE, kCustomHttpLinkPrefix + 6)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKINTERFACE, kCustomHttpLinkPrefix + 7)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKINTERFACE, kCustomHttpLinkPrefix + 8)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKINTERFACE, kCustomHttpLinkPrefix + 9)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKINTERFACE, kCustomHttpLinkPrefix + 10)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKINTERFACE, kCustomHttpLinkPrefix + 11)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKINTERFACE, kCustomHttpLinkPrefix + 12)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKINTERFACE, kCustomHttpLinkPrefix + 13)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKINTERFACE, kCustomHttpLinkPrefix + 14)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKINTERFACE, kCustomHttpLinkPrefix + 15)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKINTERFACE, kCustomHttpLinkPrefix + 16)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKINTERFACE, kCustomHttpLinkPrefix + 17)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKINTERFACE, kCustomHttpLinkPrefix + 18)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKINTERFACE, kCustomHttpLinkPrefix + 19)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKINTERFACE, kCustomHttpLinkPrefix + 20)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKINTERFACE, kCustomHttpLinkPrefix + 21)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKINTERFACE, kCustomHttpLinkPrefix + 22)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKINTERFACE, kCustomHttpLinkPrefix + 23)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKINTERFACE, kCustomHttpLinkPrefix + 24)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMHTTPLINKINTERFACE, kCustomHttpLinkPrefix + 25)


// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kCusHttpLnkLinkResourceFactoryImpl, kCustomHttpLinkPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kCusHttpLnkLinkResourceHandlerImpl, kCustomHttpLinkPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kCusHttpLnkLinkResourceStateUpdaterImpl, kCustomHttpLinkPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kCusHttpLnkLinkResourceConnectionImpl, kCustomHttpLinkPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kCusHttpLnkLinkResourceStateBatchUpdaterImpl, kCustomHttpLinkPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kCusHttpLnkResourceServerAPIWrapperImpl, kCustomHttpLinkPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kCusHttpLnkLinkResourceHelperHandlerImpl, kCustomHttpLinkPrefix + 6)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkImpl, kCustomHttpLinkPrefix + 8)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkImpl, kCustomHttpLinkPrefix + 9)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkImpl, kCustomHttpLinkPrefix + 10)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkImpl, kCustomHttpLinkPrefix + 11)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkImpl, kCustomHttpLinkPrefix + 12)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkImpl, kCustomHttpLinkPrefix + 13)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkImpl, kCustomHttpLinkPrefix + 14)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkImpl, kCustomHttpLinkPrefix + 15)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkImpl, kCustomHttpLinkPrefix + 16)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkImpl, kCustomHttpLinkPrefix + 17)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkImpl, kCustomHttpLinkPrefix + 18)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkImpl, kCustomHttpLinkPrefix + 19)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkImpl, kCustomHttpLinkPrefix + 20)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkImpl, kCustomHttpLinkPrefix + 21)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkImpl, kCustomHttpLinkPrefix + 22)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkImpl, kCustomHttpLinkPrefix + 23)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkImpl, kCustomHttpLinkPrefix + 24)
//DECLARE_PMID(kImplementationIDSpace, kCustomHttpLinkImpl, kCustomHttpLinkPrefix + 25)


// ActionIDs:
DECLARE_PMID(kActionIDSpace, kCustomHttpLinkAboutActionID, kCustomHttpLinkPrefix + 0)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkActionID, kCustomHttpLinkPrefix + 5)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkActionID, kCustomHttpLinkPrefix + 6)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkActionID, kCustomHttpLinkPrefix + 7)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkActionID, kCustomHttpLinkPrefix + 8)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkActionID, kCustomHttpLinkPrefix + 9)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkActionID, kCustomHttpLinkPrefix + 10)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkActionID, kCustomHttpLinkPrefix + 11)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkActionID, kCustomHttpLinkPrefix + 12)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkActionID, kCustomHttpLinkPrefix + 13)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkActionID, kCustomHttpLinkPrefix + 14)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkActionID, kCustomHttpLinkPrefix + 15)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkActionID, kCustomHttpLinkPrefix + 16)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkActionID, kCustomHttpLinkPrefix + 17)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkActionID, kCustomHttpLinkPrefix + 18)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkActionID, kCustomHttpLinkPrefix + 19)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkActionID, kCustomHttpLinkPrefix + 20)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkActionID, kCustomHttpLinkPrefix + 21)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkActionID, kCustomHttpLinkPrefix + 22)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkActionID, kCustomHttpLinkPrefix + 23)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkActionID, kCustomHttpLinkPrefix + 24)
//DECLARE_PMID(kActionIDSpace, kCustomHttpLinkActionID, kCustomHttpLinkPrefix + 25)


// WidgetIDs:
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkWidgetID, kCustomHttpLinkPrefix + 2)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkWidgetID, kCustomHttpLinkPrefix + 3)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkWidgetID, kCustomHttpLinkPrefix + 4)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkWidgetID, kCustomHttpLinkPrefix + 5)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkWidgetID, kCustomHttpLinkPrefix + 6)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkWidgetID, kCustomHttpLinkPrefix + 7)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkWidgetID, kCustomHttpLinkPrefix + 8)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkWidgetID, kCustomHttpLinkPrefix + 9)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkWidgetID, kCustomHttpLinkPrefix + 10)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkWidgetID, kCustomHttpLinkPrefix + 11)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkWidgetID, kCustomHttpLinkPrefix + 12)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkWidgetID, kCustomHttpLinkPrefix + 13)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkWidgetID, kCustomHttpLinkPrefix + 14)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkWidgetID, kCustomHttpLinkPrefix + 15)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkWidgetID, kCustomHttpLinkPrefix + 16)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkWidgetID, kCustomHttpLinkPrefix + 17)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkWidgetID, kCustomHttpLinkPrefix + 18)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkWidgetID, kCustomHttpLinkPrefix + 19)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkWidgetID, kCustomHttpLinkPrefix + 20)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkWidgetID, kCustomHttpLinkPrefix + 21)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkWidgetID, kCustomHttpLinkPrefix + 22)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkWidgetID, kCustomHttpLinkPrefix + 23)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkWidgetID, kCustomHttpLinkPrefix + 24)
//DECLARE_PMID(kWidgetIDSpace, kCustomHttpLinkWidgetID, kCustomHttpLinkPrefix + 25)


// "About Plug-ins" sub-menu:
#define kCustomHttpLinkAboutMenuKey			kCustomHttpLinkStringPrefix "kCustomHttpLinkAboutMenuKey"
#define kCustomHttpLinkAboutMenuPath		kSDKDefStandardAboutMenuPath kCustomHttpLinkCompanyKey

// "Plug-ins" sub-menu:
#define kCustomHttpLinkPluginsMenuKey 		kCustomHttpLinkStringPrefix "kCustomHttpLinkPluginsMenuKey"
#define kCustomHttpLinkPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kCustomHttpLinkCompanyKey kSDKDefDelimitMenuPath kCustomHttpLinkPluginsMenuKey

// Menu item keys:

// Other StringKeys:
#define kCustomHttpLinkAboutBoxStringKey	kCustomHttpLinkStringPrefix "kCustomHttpLinkAboutBoxStringKey"
#define kCustomHttpLinkTargetMenuPath kCustomHttpLinkPluginsMenuPath

// Menu item positions:


// Initial data format version numbers
#define kCustomHttpLinkFirstMajorFormatNumber  RezLong(1)
#define kCustomHttpLinkFirstMinorFormatNumber  RezLong(0)

// Data format version numbers for the PluginVersion resource 
#define kCustomHttpLinkCurrentMajorFormatNumber kCustomHttpLinkFirstMajorFormatNumber
#define kCustomHttpLinkCurrentMinorFormatNumber kCustomHttpLinkFirstMinorFormatNumber

#define kCusHttpLnkScheme       "myhost"
#define kCusHttpLnkAuthority    "localhost:3000"
#define kCusHttpLnkServerURL    "http://localhost:3000"

#endif // __CustomHttpLinkID_h__
