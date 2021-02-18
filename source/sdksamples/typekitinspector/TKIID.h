//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/typekitinspector/TKIID.h $
//  
//  Owner: Timothy Brand-Spencer
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2012 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#ifndef __TKIID_h__
#define __TKIID_h__

#include "SDKDef.h"

// Company:
#define kTKICompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kTKICompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kTKIPluginName	"TypekitInspector"			// Name of this plug-in.
#define kTKIPrefixNumber	0x1D7700 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kTKIVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kTKIAuthor		"Timothy Brand-Spencer"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kTKIPrefixNumber above to modify the prefix.)
#define kTKIPrefix		RezLong(kTKIPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kTKIStringPrefix	SDK_DEF_STRINGIZE(kTKIPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// Missing plug-in: (see ExtraPluginInfo resource)
#define kTKIMissingPluginURLValue		kSDKDefPartnersStandardValue_enUS // URL displayed in Missing Plug-in dialog
#define kTKIMissingPluginAlertValue	kSDKDefMissingPluginAlertValue // Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kTKIPluginID, kTKIPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kTKIActionComponentBoss, kTKIPrefix + 0)
DECLARE_PMID(kClassIDSpace, kTKIPanelWidgetBoss, kTKIPrefix + 1)
DECLARE_PMID(kClassIDSpace, kTKITextListWidgetBoss, kTKIPrefix + 2)
DECLARE_PMID(kClassIDSpace, kTKITreeNodeWidgetBoss, kTKIPrefix + 3)

// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_ITKISTRINGLISTDATA, kTKIPrefix + 0)

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kTKIActionComponentImpl, kTKIPrefix + 0 )
DECLARE_PMID(kImplementationIDSpace, kTKIPanelWidgetObserverImpl, kTKIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kTKITreeViewWidgetMgrImpl, kTKIPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kTKITreeViewHierarchyAdapterImpl, kTKIPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kTKITreeWidgetObserverImpl, kTKIPrefix + 4) 
DECLARE_PMID(kImplementationIDSpace, kTKIStringListDataImpl, kTKIPrefix + 5)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kTKIAboutActionID, kTKIPrefix + 0)
DECLARE_PMID(kActionIDSpace, kTKIPanelWidgetActionID, kTKIPrefix + 1)
DECLARE_PMID(kActionIDSpace, kTKISeparator1ActionID, kTKIPrefix + 2)
DECLARE_PMID(kActionIDSpace, kTKIPopupAboutThisActionID, kTKIPrefix + 3)

// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kTKIPanelWidgetID, kTKIPrefix + 0)
DECLARE_PMID(kWidgetIDSpace, kTKIUsageSampleWidgetID, kTKIPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kTKIGetFontsButtonWidgetID, kTKIPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kTKIRefreshFontsButtonWidgetID, kTKIPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kTKITextListWidgetID, kTKIPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kTKITreeNodeWidgetId, kTKIPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kTKITreeNodeTextWidgetID, kTKIPrefix + 7)

#define kTKIAboutMenuKey				kTKIStringPrefix "kTKIAboutMenuKey"
#define kTKIAboutMenuPath				kSDKDefStandardAboutMenuPath kTKICompanyKey
#define kTKIPluginsMenuKey 				kTKIStringPrefix "kTKIPluginsMenuKey"
#define kTKIPluginsMenuPath				kSDKDefPlugInsStandardMenuPath kTKICompanyKey kSDKDefDelimitMenuPath kTKIPluginsMenuKey
#define kTKIAboutBoxStringKey			kTKIStringPrefix "kTKIAboutBoxStringKey"
#define kTKIPanelTitleKey				kTKIStringPrefix "kTKIPanelTitleKey"
#define kTKIStaticTextKey				kTKIStringPrefix "kTKIStaticTextKey"
#define kTKIInternalPopupMenuNameKey	kTKIStringPrefix "kTKIInternalPopupMenuNameKey"
#define kTKITargetMenuPath				kTKIInternalPopupMenuNameKey
#define kTKIGetFontsButtonKey			kTKIStringPrefix "kTKIGetFontsButtonKey"
#define kTKIFontComboDefaultTextKey		kTKIStringPrefix "kTKIFontComboDefaultTextKey"
#define kTKIRefreshFontsButtonKey		kTKIStringPrefix "kTKIRefreshFontsButtonKey"

// Menu item positions:
#define	kTKISeparator1MenuItemPosition		10.0
#define kTKIAboutThisMenuItemPosition		11.0

// Initial data format version numbers
#define kTKIFirstMajorFormatNumber  RezLong(1)
#define kTKIFirstMinorFormatNumber  RezLong(0)

// Data format version numbers for the PluginVersion resource 
#define kTKICurrentMajorFormatNumber kTKIFirstMajorFormatNumber
#define kTKICurrentMinorFormatNumber kTKIFirstMinorFormatNumber

#define kTKITreeViewNodeWidgetRsrcID 	1210

#endif // __TKIID_h__
