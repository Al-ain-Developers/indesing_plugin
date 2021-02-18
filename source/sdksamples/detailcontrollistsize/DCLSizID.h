//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/detailcontrollistsize/DCLSizID.h $
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
//  Defines IDs used by the DCLSiz plug-in.
//  
//========================================================================================

#ifndef __DCLSizID_h__
#define __DCLSizID_h__

#include "SDKDef.h"

// Company:
#define kDCLSizCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kDCLSizCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kDCLSizPluginName	"DetailControlListSize"		// Name of this plug-in.
#define kDCLSizPrefixNumber	0x57290 					// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kDCLSizVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kDCLSizAuthor		"Adobe Developer Technologies"				// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kDCLSizPrefixNumber above to modify the prefix.)
#define kDCLSizPrefix		RezLong(kDCLSizPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kDCLSizStringPrefix	SDK_DEF_STRINGIZE(kDCLSizPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kDCLSizPluginID, kDCLSizPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kDCLSizActionComponentBoss,	kDCLSizPrefix + 0)
DECLARE_PMID(kClassIDSpace, kDCLSizPanelWidgetBoss,		kDCLSizPrefix + 4)
DECLARE_PMID(kClassIDSpace, kDCLSizListBoxWidgetBoss,	kDCLSizPrefix + 7)

// InterfaceIDs:
// None in this plug-in.
DECLARE_PMID(kInterfaceIDSpace, IID_IDCLSizPanelOptions,		kDCLSizPrefix + 0)

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kDCLSizActionComponentImpl,		kDCLSizPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kDCLSizPalettePanelViewImpl,		kDCLSizPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kDCLSizListBoxObserverImpl,		kDCLSizPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kDCLSizPanelOptionsImpl,		kDCLSizPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kDCLSizPanelXMLGeneratorImpl,		kDCLSizPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kDCLSizPanelSAXHandlerImpl,		kDCLSizPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kDCLSizTreeViewWidgetMgrImpl,		kDCLSizPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kDCLSizTreeViewAdapterImpl,		kDCLSizPrefix + 7)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kDCLSizAboutActionID,				kDCLSizPrefix + 0)
DECLARE_PMID(kActionIDSpace, kDCLSizPanelWidgetActionID,		kDCLSizPrefix + 1)
DECLARE_PMID(kActionIDSpace, kDCLSizSeparator1ActionID,			kDCLSizPrefix + 2)
DECLARE_PMID(kActionIDSpace, kDCLSizPopupAboutThisActionID,		kDCLSizPrefix + 3)
DECLARE_PMID(kActionIDSpace, kDCLSizSmallPaletteRowsActionID,	kDCLSizPrefix + 11)
// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kDCLSizPanelWidgetID,				kDCLSizPrefix + 0) 
DECLARE_PMID(kWidgetIDSpace, kDCLSizListParentWidgetId,			kDCLSizPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kDCLSizTextWidgetID,				kDCLSizPrefix + 2) 
DECLARE_PMID(kWidgetIDSpace, kDCLSizListBoxWidgetID,			kDCLSizPrefix + 3) 
//REMOVED:
//DECLARE_PMID(kWidgetIDSpace, kDCLSizSmallListBoxWidgetID,		kDCLSizPrefix + 4) 

// "About Plug-ins" sub-menu:
#define kDCLSizAboutMenuKey			kDCLSizStringPrefix "kDCLSizAboutMenuKey"
#define kDCLSizAboutMenuPath		kSDKDefStandardAboutMenuPath kDCLSizCompanyKey

// "Plug-ins" sub-menu:
#define kDCLSizPluginsMenuKey 		kDCLSizStringPrefix "kDCLSizPluginsMenuKey"
#define kDCLSizPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kDCLSizCompanyKey kSDKDefDelimitMenuPath kDCLSizPluginsMenuKey

// Menu item keys:
#define kDCLSizSmallPaletteRowsMenuItemKey		kDCLSizStringPrefix "kDCLSizSmallPaletteRowsMenuItemKey"

// Other StringKeys:
#define kDCLSizAboutBoxStringKey				kDCLSizStringPrefix "kDCLSizAboutBoxStringKey"
#define kDCLSizSmallPaletteRowsStringKey		kDCLSizStringPrefix "kDCLSizSmallPaletteRowsStringKey"
#define kDCLSizPanelTitleKey					kDCLSizStringPrefix	"kDCLSizPanelTitleKey"
#define kDCLSizInternalPopupMenuNameKey			kDCLSizStringPrefix	"kDCLSizInternalPopupMenuNameKey"
#define kDCLSizTargetMenuPath 					kDCLSizInternalPopupMenuNameKey
#define kDCLSizItemBaseKey						kDCLSizStringPrefix "kDCLSizItemBaseKey"
#define kDCLSizAddedElementKey					kDCLSizStringPrefix "kDCLSizAddedElementKey"

// panel option xml tag
#define kDCLSizPanelOptionsXMLTag				"dclsizpanel-options"
#define kDCLSizPanelListSizeXMLAttributeName				"largeListSize"

// Menu item positions:
#define kDCLSizSmallPaletteRowsMenuItemPosition			1.0
#define	kDCLSizSeparator1MenuItemPosition				10.0
#define kDCLSizAboutThisMenuItemPosition				11.0

// Misc res defs.
#define kDCLSizListElementRsrcID	1200
#define kDCLSizSmallListElementRsrcID	1400

// Initial data format version numbers
#define kDCLSizFirstMajorFormatNumber  kSDKDef_30_PersistMajorVersionNumber
#define kDCLSizFirstMinorFormatNumber  kSDKDef_30_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kDCLSizCurrentMajorFormatNumber kDCLSizFirstMajorFormatNumber // most recent major format change
#define kDCLSizCurrentMinorFormatNumber kDCLSizFirstMinorFormatNumber // most recent minor format change

#endif // __DCLSizID_h__

// End, DCLSizID.h.

