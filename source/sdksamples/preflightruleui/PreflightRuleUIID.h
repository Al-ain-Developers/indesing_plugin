//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/preflightruleui/PreflightRuleUIID.h $
//  
//  Owner: John Doe
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

#ifndef __PreflightRuleUIID_h__
#define __PreflightRuleUIID_h__

#include "SDKDef.h"
#include "PreflightRuleRezDefs.h"
// Company:
#define kPreflightRuleUICompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kPreflightRuleUICompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kPreflightRuleUIPluginName	"PreflightRuleUI"			// Name of this plug-in.
#define kPreflightRuleUIPrefixNumber	0x13f700 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kPreflightRuleUIVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kPreflightRuleUIAuthor		"InDesign Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kPreflightRuleUIPrefixNumber above to modify the prefix.)
#define kPreflightRuleUIPrefix		RezLong(kPreflightRuleUIPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kPreflightRuleUIStringPrefix	SDK_DEF_STRINGIZE(kPreflightRuleUIPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// Missing plug-in: (see ExtraPluginInfo resource)
#define kPreflightRuleUIMissingPluginURLValue		kSDKDefPartnersStandardValue_enUS // URL displayed in Missing Plug-in dialog
#define kPreflightRuleUIMissingPluginAlertValue	kSDKDefMissingPluginAlertValue // Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kPreflightRuleUIPluginID, kPreflightRuleUIPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kPreflightRuleUIActionComponentBoss, kPreflightRuleUIPrefix + 0)
DECLARE_PMID(kClassIDSpace, kPreflightRuleUIDataPanelWidgetBoss, kPreflightRuleUIPrefix + 3)
DECLARE_PMID(kClassIDSpace, kPreflightRuleUIDataCheckBoxWidgetBoss, kPreflightRuleUIPrefix + 4)



// InterfaceIDs:

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kPreflightRuleUIActionComponentImpl, kPreflightRuleUIPrefix + 0 )
DECLARE_PMID(kImplementationIDSpace, kPreflightCheckBoxObserverImpl, kPreflightRuleUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kPreflightFontUIImpl, kPreflightRuleUIPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kPreflightBlackOverprintUIImpl, kPreflightRuleUIPrefix + 3)



// ActionIDs:
DECLARE_PMID(kActionIDSpace, kPreflightRuleUIAboutActionID, kPreflightRuleUIPrefix + 0)



// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kPreflightRuleUIDataPanelWidgetID, kPreflightRuleUIPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kPreflightRuleUIDataWidgetID1, kPreflightRuleUIPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kPreflightRuleUIDataWidgetID2, kPreflightRuleUIPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kPreflightRuleUIDataWidgetID3, kPreflightRuleUIPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kPreflightRuleUIDataWidgetID4, kPreflightRuleUIPrefix + 6)



// "About Plug-ins" sub-menu:
#define kPreflightRuleUIAboutMenuKey			kPreflightRuleUIStringPrefix "kPreflightRuleUIAboutMenuKey"
#define kPreflightRuleUIAboutMenuPath		kSDKDefStandardAboutMenuPath kPreflightRuleUICompanyKey

// "Plug-ins" sub-menu:
#define kPreflightRuleUIPluginsMenuKey 		kPreflightRuleUIStringPrefix "kPreflightRuleUIPluginsMenuKey"
#define kPreflightRuleUIPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kPreflightRuleUICompanyKey kSDKDefDelimitMenuPath kPreflightRuleUIPluginsMenuKey

// Menu item keys:

// Other StringKeys:
#define kPreflightRuleUIAboutBoxStringKey	kPreflightRuleUIStringPrefix "kPreflightRuleUIAboutBoxStringKey"
#define kPreflightRuleUITargetMenuPath kPreflightRuleUIPluginsMenuPath

#define kPreflightFontName1					kPreflightRuleUIStringPrefix	"kPreflightFontName1"
#define kPreflightFontName2					kPreflightRuleUIStringPrefix	"kPreflightFontName2"
#define kPreflightFontName3					kPreflightRuleUIStringPrefix	"kPreflightFontName3"
#define kPreflightFontName4					kPreflightRuleUIStringPrefix	"kPreflightFontName4"

#define kSDKFontRuleLabel				kPreflightRuleUIStringPrefix	"kSDKFontRuleLabel"

#define kSDKBlackOverprintRuleLabel		kPreflightRuleUIStringPrefix	"kSDKBlackOverprintRuleLabel"

// Menu item positions:
#define kPreflightSeparator1MenuItemPosition		10.0
#define kPreflightAboutThisMenuItemPosition		11.0

// Initial data format version numbers
#define kPreflightRuleUIFirstMajorFormatNumber  RezLong(1)
#define kPreflightRuleUIFirstMinorFormatNumber  RezLong(0)

// Data format version numbers for the PluginVersion resource 
#define kPreflightRuleUICurrentMajorFormatNumber kPreflightRuleUIFirstMajorFormatNumber
#define kPreflightRuleUICurrentMinorFormatNumber kPreflightRuleUIFirstMinorFormatNumber

#endif // __PreflightRuleUIID_h__

//  Code generated by DollyXs code generator
