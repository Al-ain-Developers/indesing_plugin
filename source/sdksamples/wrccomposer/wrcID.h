//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/wrccomposer/wrcID.h $
//  
//  Owner: Prashant Dahiya
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


#ifndef __wrcID_h__
#define __wrcID_h__

#include "SDKDef.h"

// Company:
#define kwrcCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kwrcCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kwrcPluginName	"WRCComposer"			// Name of this plug-in.
#define kwrcPrefixNumber	0x1D7800 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kwrcVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kwrcAuthor		"Prashant Dahiya"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kwrcPrefixNumber above to modify the prefix.)
#define kwrcPrefix		RezLong(kwrcPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kwrcStringPrefix	SDK_DEF_STRINGIZE(kwrcPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// Missing plug-in: (see ExtraPluginInfo resource)
#define kwrcMissingPluginURLValue		kSDKDefPartnersStandardValue_enUS // URL displayed in Missing Plug-in dialog
#define kwrcMissingPluginAlertValue	kSDKDefMissingPluginAlertValue // Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kwrcPluginID, kwrcPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kWRCParagraphComposerBoss, kwrcPrefix + 3)
//DECLARE_PMID(kClassIDSpace, kwrcBoss, kwrcPrefix + 4)
//DECLARE_PMID(kClassIDSpace, kwrcBoss, kwrcPrefix + 5)
//DECLARE_PMID(kClassIDSpace, kwrcBoss, kwrcPrefix + 6)
//DECLARE_PMID(kClassIDSpace, kwrcBoss, kwrcPrefix + 7)
//DECLARE_PMID(kClassIDSpace, kwrcBoss, kwrcPrefix + 8)
//DECLARE_PMID(kClassIDSpace, kwrcBoss, kwrcPrefix + 9)
//DECLARE_PMID(kClassIDSpace, kwrcBoss, kwrcPrefix + 10)
//DECLARE_PMID(kClassIDSpace, kwrcBoss, kwrcPrefix + 11)
//DECLARE_PMID(kClassIDSpace, kwrcBoss, kwrcPrefix + 12)
//DECLARE_PMID(kClassIDSpace, kwrcBoss, kwrcPrefix + 13)
//DECLARE_PMID(kClassIDSpace, kwrcBoss, kwrcPrefix + 14)
//DECLARE_PMID(kClassIDSpace, kwrcBoss, kwrcPrefix + 15)
//DECLARE_PMID(kClassIDSpace, kwrcBoss, kwrcPrefix + 16)
//DECLARE_PMID(kClassIDSpace, kwrcBoss, kwrcPrefix + 17)
//DECLARE_PMID(kClassIDSpace, kwrcBoss, kwrcPrefix + 18)
//DECLARE_PMID(kClassIDSpace, kwrcBoss, kwrcPrefix + 19)
//DECLARE_PMID(kClassIDSpace, kwrcBoss, kwrcPrefix + 20)
//DECLARE_PMID(kClassIDSpace, kwrcBoss, kwrcPrefix + 21)
//DECLARE_PMID(kClassIDSpace, kwrcBoss, kwrcPrefix + 22)
//DECLARE_PMID(kClassIDSpace, kwrcBoss, kwrcPrefix + 23)
//DECLARE_PMID(kClassIDSpace, kwrcBoss, kwrcPrefix + 24)
//DECLARE_PMID(kClassIDSpace, kwrcBoss, kwrcPrefix + 25)


// InterfaceIDs:
//DECLARE_PMID(kInterfaceIDSpace, IID_IWRCINTERFACE, kwrcPrefix + 0)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWRCINTERFACE, kwrcPrefix + 1)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWRCINTERFACE, kwrcPrefix + 2)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWRCINTERFACE, kwrcPrefix + 3)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWRCINTERFACE, kwrcPrefix + 4)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWRCINTERFACE, kwrcPrefix + 5)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWRCINTERFACE, kwrcPrefix + 6)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWRCINTERFACE, kwrcPrefix + 7)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWRCINTERFACE, kwrcPrefix + 8)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWRCINTERFACE, kwrcPrefix + 9)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWRCINTERFACE, kwrcPrefix + 10)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWRCINTERFACE, kwrcPrefix + 11)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWRCINTERFACE, kwrcPrefix + 12)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWRCINTERFACE, kwrcPrefix + 13)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWRCINTERFACE, kwrcPrefix + 14)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWRCINTERFACE, kwrcPrefix + 15)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWRCINTERFACE, kwrcPrefix + 16)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWRCINTERFACE, kwrcPrefix + 17)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWRCINTERFACE, kwrcPrefix + 18)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWRCINTERFACE, kwrcPrefix + 19)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWRCINTERFACE, kwrcPrefix + 20)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWRCINTERFACE, kwrcPrefix + 21)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWRCINTERFACE, kwrcPrefix + 22)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWRCINTERFACE, kwrcPrefix + 23)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWRCINTERFACE, kwrcPrefix + 24)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWRCINTERFACE, kwrcPrefix + 25)


// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kWRCParagraphComposerServiceProviderImpl, kwrcPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kWRCParagraphComposerImpl, kwrcPrefix + 1)
//DECLARE_PMID(kImplementationIDSpace, kwrcImpl, kwrcPrefix + 2)
//DECLARE_PMID(kImplementationIDSpace, kwrcImpl, kwrcPrefix + 3)
//DECLARE_PMID(kImplementationIDSpace, kwrcImpl, kwrcPrefix + 4)
//DECLARE_PMID(kImplementationIDSpace, kwrcImpl, kwrcPrefix + 5)
//DECLARE_PMID(kImplementationIDSpace, kwrcImpl, kwrcPrefix + 6)
//DECLARE_PMID(kImplementationIDSpace, kwrcImpl, kwrcPrefix + 7)
//DECLARE_PMID(kImplementationIDSpace, kwrcImpl, kwrcPrefix + 8)
//DECLARE_PMID(kImplementationIDSpace, kwrcImpl, kwrcPrefix + 9)
//DECLARE_PMID(kImplementationIDSpace, kwrcImpl, kwrcPrefix + 10)
//DECLARE_PMID(kImplementationIDSpace, kwrcImpl, kwrcPrefix + 11)
//DECLARE_PMID(kImplementationIDSpace, kwrcImpl, kwrcPrefix + 12)
//DECLARE_PMID(kImplementationIDSpace, kwrcImpl, kwrcPrefix + 13)
//DECLARE_PMID(kImplementationIDSpace, kwrcImpl, kwrcPrefix + 14)
//DECLARE_PMID(kImplementationIDSpace, kwrcImpl, kwrcPrefix + 15)
//DECLARE_PMID(kImplementationIDSpace, kwrcImpl, kwrcPrefix + 16)
//DECLARE_PMID(kImplementationIDSpace, kwrcImpl, kwrcPrefix + 17)
//DECLARE_PMID(kImplementationIDSpace, kwrcImpl, kwrcPrefix + 18)
//DECLARE_PMID(kImplementationIDSpace, kwrcImpl, kwrcPrefix + 19)
//DECLARE_PMID(kImplementationIDSpace, kwrcImpl, kwrcPrefix + 20)
//DECLARE_PMID(kImplementationIDSpace, kwrcImpl, kwrcPrefix + 21)
//DECLARE_PMID(kImplementationIDSpace, kwrcImpl, kwrcPrefix + 22)
//DECLARE_PMID(kImplementationIDSpace, kwrcImpl, kwrcPrefix + 23)
//DECLARE_PMID(kImplementationIDSpace, kwrcImpl, kwrcPrefix + 24)
//DECLARE_PMID(kImplementationIDSpace, kwrcImpl, kwrcPrefix + 25)


// ActionIDs:
DECLARE_PMID(kActionIDSpace, kwrcAboutActionID, kwrcPrefix + 0)
//DECLARE_PMID(kActionIDSpace, kwrcActionID, kwrcPrefix + 5)
//DECLARE_PMID(kActionIDSpace, kwrcActionID, kwrcPrefix + 6)
//DECLARE_PMID(kActionIDSpace, kwrcActionID, kwrcPrefix + 7)
//DECLARE_PMID(kActionIDSpace, kwrcActionID, kwrcPrefix + 8)
//DECLARE_PMID(kActionIDSpace, kwrcActionID, kwrcPrefix + 9)
//DECLARE_PMID(kActionIDSpace, kwrcActionID, kwrcPrefix + 10)
//DECLARE_PMID(kActionIDSpace, kwrcActionID, kwrcPrefix + 11)
//DECLARE_PMID(kActionIDSpace, kwrcActionID, kwrcPrefix + 12)
//DECLARE_PMID(kActionIDSpace, kwrcActionID, kwrcPrefix + 13)
//DECLARE_PMID(kActionIDSpace, kwrcActionID, kwrcPrefix + 14)
//DECLARE_PMID(kActionIDSpace, kwrcActionID, kwrcPrefix + 15)
//DECLARE_PMID(kActionIDSpace, kwrcActionID, kwrcPrefix + 16)
//DECLARE_PMID(kActionIDSpace, kwrcActionID, kwrcPrefix + 17)
//DECLARE_PMID(kActionIDSpace, kwrcActionID, kwrcPrefix + 18)
//DECLARE_PMID(kActionIDSpace, kwrcActionID, kwrcPrefix + 19)
//DECLARE_PMID(kActionIDSpace, kwrcActionID, kwrcPrefix + 20)
//DECLARE_PMID(kActionIDSpace, kwrcActionID, kwrcPrefix + 21)
//DECLARE_PMID(kActionIDSpace, kwrcActionID, kwrcPrefix + 22)
//DECLARE_PMID(kActionIDSpace, kwrcActionID, kwrcPrefix + 23)
//DECLARE_PMID(kActionIDSpace, kwrcActionID, kwrcPrefix + 24)
//DECLARE_PMID(kActionIDSpace, kwrcActionID, kwrcPrefix + 25)


// WidgetIDs:
//DECLARE_PMID(kWidgetIDSpace, kwrcWidgetID, kwrcPrefix + 2)
//DECLARE_PMID(kWidgetIDSpace, kwrcWidgetID, kwrcPrefix + 3)
//DECLARE_PMID(kWidgetIDSpace, kwrcWidgetID, kwrcPrefix + 4)
//DECLARE_PMID(kWidgetIDSpace, kwrcWidgetID, kwrcPrefix + 5)
//DECLARE_PMID(kWidgetIDSpace, kwrcWidgetID, kwrcPrefix + 6)
//DECLARE_PMID(kWidgetIDSpace, kwrcWidgetID, kwrcPrefix + 7)
//DECLARE_PMID(kWidgetIDSpace, kwrcWidgetID, kwrcPrefix + 8)
//DECLARE_PMID(kWidgetIDSpace, kwrcWidgetID, kwrcPrefix + 9)
//DECLARE_PMID(kWidgetIDSpace, kwrcWidgetID, kwrcPrefix + 10)
//DECLARE_PMID(kWidgetIDSpace, kwrcWidgetID, kwrcPrefix + 11)
//DECLARE_PMID(kWidgetIDSpace, kwrcWidgetID, kwrcPrefix + 12)
//DECLARE_PMID(kWidgetIDSpace, kwrcWidgetID, kwrcPrefix + 13)
//DECLARE_PMID(kWidgetIDSpace, kwrcWidgetID, kwrcPrefix + 14)
//DECLARE_PMID(kWidgetIDSpace, kwrcWidgetID, kwrcPrefix + 15)
//DECLARE_PMID(kWidgetIDSpace, kwrcWidgetID, kwrcPrefix + 16)
//DECLARE_PMID(kWidgetIDSpace, kwrcWidgetID, kwrcPrefix + 17)
//DECLARE_PMID(kWidgetIDSpace, kwrcWidgetID, kwrcPrefix + 18)
//DECLARE_PMID(kWidgetIDSpace, kwrcWidgetID, kwrcPrefix + 19)
//DECLARE_PMID(kWidgetIDSpace, kwrcWidgetID, kwrcPrefix + 20)
//DECLARE_PMID(kWidgetIDSpace, kwrcWidgetID, kwrcPrefix + 21)
//DECLARE_PMID(kWidgetIDSpace, kwrcWidgetID, kwrcPrefix + 22)
//DECLARE_PMID(kWidgetIDSpace, kwrcWidgetID, kwrcPrefix + 23)
//DECLARE_PMID(kWidgetIDSpace, kwrcWidgetID, kwrcPrefix + 24)
//DECLARE_PMID(kWidgetIDSpace, kwrcWidgetID, kwrcPrefix + 25)


// "About Plug-ins" sub-menu:
#define kwrcAboutMenuKey			kwrcStringPrefix "kwrcAboutMenuKey"
#define kwrcAboutMenuPath		kSDKDefStandardAboutMenuPath kwrcCompanyKey

// "Plug-ins" sub-menu:
#define kwrcPluginsMenuKey 		kwrcStringPrefix "kwrcPluginsMenuKey"
#define kwrcPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kwrcCompanyKey kSDKDefDelimitMenuPath kwrcPluginsMenuKey

// Menu item keys:

// Other StringKeys:
#define kwrcAboutBoxStringKey	kwrcStringPrefix "kwrcAboutBoxStringKey"
#define kwrcTargetMenuPath kwrcPluginsMenuPath
#define kWRCParagraphComposerNameStringKey	kwrcStringPrefix "kWRCParagraphComposerNameStringKey"

// Menu item positions:


// Initial data format version numbers
#define kwrcFirstMajorFormatNumber  RezLong(1)
#define kwrcFirstMinorFormatNumber  RezLong(0)

// Data format version numbers for the PluginVersion resource 
#define kwrcCurrentMajorFormatNumber kwrcFirstMajorFormatNumber
#define kwrcCurrentMinorFormatNumber kwrcFirstMinorFormatNumber

#endif // __wrcID_h__

//  Code generated by DollyXs code generator
