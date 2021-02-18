//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/transparencyeffectui/TranFxUIID.h $
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
//  Defines IDs used by the TranFxUI plug-in.
//  
//========================================================================================

#ifndef __TranFxUIID_h__
#define __TranFxUIID_h__

#include "SDKDef.h"

// Company:
#define kTranFxUICompanyKey		kSDKDefPlugInCompanyKey // Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kTranFxUICompanyValue	kSDKDefPlugInCompanyValue // Company name displayed externally.

// Plug-in:
#define kTranFxUIPluginName		"TransparencyEffectUI" // Name of this plug-in.
#define kTranFxUIPrefixNumber	0x5c190 	// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kTranFxUIVersion		kSDKDefPluginVersionString // Version of this plug-in (for the About Box).
#define kTranFxUIAuthor			"Adobe Developer Technologies" // Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kTranFxUIPrefixNumber above to modify the prefix.)
#define kTranFxUIPrefix			RezLong(kTranFxUIPrefixNumber) // The unique numeric prefix for all object model IDs for this plug-in.
#define kTranFxUIStringPrefix	SDK_DEF_STRINGIZE(kTranFxUIPrefixNumber) // The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kTranFxUIPluginID, kTranFxUIPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kTranFxUIActionComponentBoss,	kTranFxUIPrefix + 0)
DECLARE_PMID(kClassIDSpace, kTranFxUIDialogBoss,			kTranFxUIPrefix + 2)

// InterfaceIDs:
// None in this plug-in.

// Implementation IDs:
DECLARE_PMID(kImplementationIDSpace, kTranFxUIActionComponentImpl,	kTranFxUIPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kTranFxUIDialogControllerImpl,	kTranFxUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kTranFxUIDialogObserverImpl,	kTranFxUIPrefix + 2)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kTranFxUIAboutActionID,	kTranFxUIPrefix + 0)
DECLARE_PMID(kActionIDSpace, kTranFxUIDialogActionID,	kTranFxUIPrefix + 1)

// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kTranFxUIDialogWidgetID,			kTranFxUIPrefix + 0)
DECLARE_PMID(kWidgetIDSpace, kTranFxUIIconSuiteWidgetID,		kTranFxUIPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kTranFxUIOptionsWidgetID,			kTranFxUIPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kTranFxUIApplyWidgetID,			kTranFxUIPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kTranFxUIApplyEffectWidgetID,		kTranFxUIPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kTranFxUIXOffsetWidgetID,			kTranFxUIPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kTranFxUIXOffsetEditBoxWidgetID,	kTranFxUIPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kTranFxUIYOffsetWidgetID,			kTranFxUIPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kTranFxUIYOffsetEditBoxWidgetID,	kTranFxUIPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kTranFxUIUseBlackAsOpaqueWidgetID,	kTranFxUIPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kTranFxUIUseAlphaWidgetID,			kTranFxUIPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kTranFxUIUseBlurWidgetID,			kTranFxUIPrefix + 11)

// "About Plug-ins" sub-menu:
#define kTranFxUIAboutMenuKey			kTranFxUIStringPrefix "kTranFxUIAboutMenuKey"
#define kTranFxUIAboutMenuPath			kSDKDefStandardAboutMenuPath kTranFxUICompanyKey

// "Plug-ins" sub-menu:
#define kTranFxUIPluginsMenuKey 		kTranFxUIStringPrefix "kTranFxUIPluginsMenuKey"
#define kTranFxUIPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kTranFxUICompanyKey

// "Plug-ins" sub-menu item keys:
#define kTranFxUIDialogMenuItemKey		kTranFxUIStringPrefix "kTranFxUIDialogMenuItemKey"

// "Plug-ins" sub-menu item positions:
#define kTranFxUIDialogMenuItemPosition	1.0

// Other StringKeys:
#define kTranFxUIDialogTitleKey				kTranFxUIStringPrefix "kTranFxUIDialogTitleKey"
#define kTranFxUIAboutBoxStringKey			kTranFxUIStringPrefix "kTranFxUIAboutBoxStringKey"
#define kTranFxUIXOffsetLabelStringKey		kTranFxUIStringPrefix "kTranFxUIXOffsetLabelStringKey"
#define kTranFxUIYOffsetLabelStringKey		kTranFxUIStringPrefix "kTranFxUIYOffsetLabelStringKey"
#define kTranFxUIUseBlackAsOpaqueWidgetKey	kTranFxUIStringPrefix "kTranFxUIUseBlackAsOpaqueWidgetKey"
#define kTranFxUIUseAlphaWidgetKey			kTranFxUIStringPrefix "kTranFxUIUseAlphaWidgetKey"
#define kTranFxUIUseBlurWidgetKey			kTranFxUIStringPrefix "kTranFxUIUseBlurWidgetKey"

// Initial data format version numbers
#define kTranFxUIFirstMajorFormatNumber  kSDKDef_30_PersistMajorVersionNumber
#define kTranFxUIFirstMinorFormatNumber  kSDKDef_30_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kTranFxUICurrentMajorFormatNumber kTranFxUIFirstMajorFormatNumber // most recent major format change
#define kTranFxUICurrentMinorFormatNumber kTranFxUIFirstMinorFormatNumber // most recent minor format change

#endif // __TranFxUIID_h__

// End, TranFxUIID.h.


