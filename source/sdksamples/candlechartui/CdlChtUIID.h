//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/candlechartui/CdlChtUIID.h $
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

#ifndef __CdlChtUIID_h__
#define __CdlChtUIID_h__

#include "SDKDef.h"

// Company:
#define kCdlChtUICompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kCdlChtUICompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kCdlChtUIPluginName	"CandleChartUI"			// Name of this plug-in.
#define kCdlChtUIPrefixNumber	0x101700 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kCdlChtUIVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kCdlChtUIAuthor		"Adobe Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kCdlChtUIPrefixNumber above to modify the prefix.)
#define kCdlChtUIPrefix		RezLong(kCdlChtUIPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kCdlChtUIStringPrefix	SDK_DEF_STRINGIZE(kCdlChtUIPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// Missing plug-in: (see ExtraPluginInfo resource)
#define kCdlChtUIMissingPluginURLValue		kSDKDefPartnersStandardValue_enUS // URL displayed in Missing Plug-in dialog
#define kCdlChtUIMissingPluginAlertValue	kSDKDefMissingPluginAlertValue // Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kCdlChtUIPluginID, kCdlChtUIPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kCdlChtUIActionComponentBoss, kCdlChtUIPrefix + 0)
DECLARE_PMID(kClassIDSpace, kCdlChtUIPanelWidgetBoss, kCdlChtUIPrefix + 1)



// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_ICdlChtUISELECTIONOBSERVER,		kCdlChtUIPrefix + 0)
DECLARE_PMID(kInterfaceIDSpace, IID_ICdlChtUIWIDGETOBSERVER, kCdlChtUIPrefix + 1)



// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kCdlChtUIActionComponentImpl, kCdlChtUIPrefix + 0 )
DECLARE_PMID(kImplementationIDSpace, kCdlChtUISelectionObserverImpl, kCdlChtUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kCdlChtUISuiteLayoutSelectionExtImpl, kCdlChtUIPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kCdlChtUIWidgetObserverImpl, kCdlChtUIPrefix + 3)


// ActionIDs:
DECLARE_PMID(kActionIDSpace, kCdlChtUIAboutActionID, kCdlChtUIPrefix + 0)
DECLARE_PMID(kActionIDSpace, kCdlChtUIPanelWidgetActionID, kCdlChtUIPrefix + 1)
DECLARE_PMID(kActionIDSpace, kCdlChtUISeparator1ActionID, kCdlChtUIPrefix + 2)
DECLARE_PMID(kActionIDSpace, kCdlChtUIPopupAboutThisActionID, kCdlChtUIPrefix + 3)
DECLARE_PMID(kActionIDSpace, kCdlChtUINewCandleChartActionID, kCdlChtUIPrefix + 4)



// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kCdlChtUIPanelWidgetID, kCdlChtUIPrefix + 0)
DECLARE_PMID(kWidgetIDSpace, kCdlChtUINameWidgetID, kCdlChtUIPrefix + 1)


// "About Plug-ins" sub-menu:
#define kCdlChtUIAboutMenuKey			kCdlChtUIStringPrefix "kCdlChtUIAboutMenuKey"
#define kCdlChtUIAboutMenuPath		kSDKDefStandardAboutMenuPath kCdlChtUICompanyKey

// "Plug-ins" sub-menu:
#define kCdlChtUIPluginsMenuKey 		kCdlChtUIStringPrefix "kCdlChtUIPluginsMenuKey"
#define kCdlChtUIPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kCdlChtUICompanyKey kSDKDefDelimitMenuPath kCdlChtUIPluginsMenuKey

// Menu item keys:
#define kCdlChtUINewCandleChartMenuItemKey		kCdlChtUIStringPrefix "NewCandleChartMenuItemKey_3"

// Other StringKeys:
#define kCdlChtUIAboutBoxStringKey			kCdlChtUIStringPrefix "kCdlChtUIAboutBoxStringKey"
#define kCdlChtUIPanelTitleKey				kCdlChtUIStringPrefix	"kCdlChtUIPanelTitleKey"
#define kCdlChtUIStaticTextKey				kCdlChtUIStringPrefix	"kCdlChtUIStaticTextKey"
#define kCdlChtUIInternalPopupMenuNameKey	kCdlChtUIStringPrefix	"kCdlChtUIInternalPopupMenuNameKey"
#define kCdlChtUITargetMenuPath				kCdlChtUIInternalPopupMenuNameKey
#define kCdlChtUIErrorNoLayoutStringKey		kCdlChtUIStringPrefix "kCdlChtUIErrorNoLayoutStringKey_10"
#define kCdlChtUICSVFilterStringKey			kCdlChtUIStringPrefix "kCdlChtUICSVFilterStringKey_11"
#define kCdlChtUISelectDataFileStringKey	kCdlChtUIStringPrefix "kCdlChtUISelectDataFileStringKey_12"
#define kModifyCdlChtUICmdStringKey			kCdlChtUIStringPrefix "kModifyCdlChtUICmdStringKey_13"

// Menu item positions:

#define kCdlChtUINewCandleChartMenuItemPosition 1
#define	kCdlChtUISeparator1MenuItemPosition		10.0
#define kCdlChtUIAboutThisMenuItemPosition		11.0


// Initial data format version numbers
#define kCdlChtUIFirstMajorFormatNumber  RezLong(1)
#define kCdlChtUIFirstMinorFormatNumber  RezLong(0)

// Data format version numbers for the PluginVersion resource 
#define kCdlChtUICurrentMajorFormatNumber kCdlChtUIFirstMajorFormatNumber
#define kCdlChtUICurrentMinorFormatNumber kCdlChtUIFirstMinorFormatNumber

#endif // __CdlChtUIID_h__

//  Code generated by DollyXs code generator
