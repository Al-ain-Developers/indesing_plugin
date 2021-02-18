//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/strokeweightmutator/StrMutID.h $
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

#ifndef __StrMutID_h__
#define __StrMutID_h__

#include "SDKDef.h"

// Company:
#define kStrMutCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kStrMutCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kStrMutPluginName	"StrokeWeightMutator"			// Name of this plug-in.
#define kStrMutPrefixNumber	0x79720							// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kStrMutVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kStrMutAuthor		"Adobe Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kStrMutPrefixNumber above to modify the prefix.)
#define kStrMutPrefix		RezLong(kStrMutPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kStrMutStringPrefix	SDK_DEF_STRINGIZE(kStrMutPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kStrMutPluginID, kStrMutPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kStrMutActionComponentBoss,	kStrMutPrefix + 0)
DECLARE_PMID(kClassIDSpace, kStrMutPanelWidgetBoss,		kStrMutPrefix + 1)

// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_ISTRMUTSELECTIONOBSERVER,	kStrMutPrefix + 0)

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kStrMutActionComponentImpl,		kStrMutPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kStrMutSelectionObserverImpl,	kStrMutPrefix + 1)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kStrMutAboutActionID,				kStrMutPrefix + 0)
DECLARE_PMID(kActionIDSpace, kStrMutPanelWidgetActionID,			kStrMutPrefix + 1)
DECLARE_PMID(kActionIDSpace, kStrMutPopupAboutThisActionID,		kStrMutPrefix + 2)

// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kStrMutPanelWidgetID,				kStrMutPrefix + 0) 
DECLARE_PMID(kWidgetIDSpace, kStrMutStrokeWeightWidgetID,	kStrMutPrefix + 1) 
DECLARE_PMID(kWidgetIDSpace, kStrMutStrokeWeightNudgeWidgetID,	kStrMutPrefix + 2)

// "About Plug-ins" sub-menu:
#define kStrMutAboutMenuKey			kStrMutStringPrefix "kStrMutAboutMenuKey"
#define kStrMutAboutMenuPath			kSDKDefStandardAboutMenuPath kStrMutCompanyKey

// "Plug-ins" sub-menu:
#define kStrMutPluginsMenuKey 		kStrMutStringPrefix "kStrMutPluginsMenuKey"
#define kStrMutPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kStrMutCompanyKey kSDKDefDelimitMenuPath kStrMutPluginsMenuKey

// Menu item keys:

// Other StringKeys:
#define kStrMutAboutBoxStringKey				kStrMutStringPrefix "kStrMutAboutBoxStringKey"
#define kStrMutPanelTitleKey					kStrMutStringPrefix	"kStrMutPanelTitleKey"
#define kStrMutStaticTextKey					kStrMutStringPrefix	"kStrMutStaticTextKey"
#define kStrMutInternalPopupMenuNameKey		kStrMutStringPrefix	"kStrMutInternalPopupMenuNameKey"
#define kStrMutTargetMenuPath kStrMutInternalPopupMenuNameKey

// Menu item positions:
#define	kStrMutSeparator1MenuItemPosition			10.0
#define kStrMutAboutThisMenuItemPosition				11.0

// Initial data format version numbers
#define kStrMutFirstMajorFormatNumber  kSDKDef_30_PersistMajorVersionNumber
#define kStrMutFirstMinorFormatNumber  kSDKDef_30_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kStrMutCurrentMajorFormatNumber kStrMutFirstMajorFormatNumber // most recent major format change
#define kStrMutCurrentMinorFormatNumber kStrMutFirstMinorFormatNumber // most recent minor format change

#endif // __StrMutID_h__

// End, StrMutID.h.

