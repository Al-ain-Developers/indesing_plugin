//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hiddentexteditor/HidTxtEdID.h $
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

#ifndef __HidTxtEdID_h__
#define __HidTxtEdID_h__

#include "SDKDef.h"

// Company:
#define kHidTxtEdCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kHidTxtEdCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kHidTxtEdPluginName	"HiddenTextEditor"			// Name of this plug-in.
#define kHidTxtEdPrefixNumber	0x670d0 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kHidTxtEdVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kHidTxtEdAuthor		"Adobe Developer Technologies"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kHidTxtEdPrefixNumber above to modify the prefix.)
#define kHidTxtEdPrefix		RezLong(kHidTxtEdPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kHidTxtEdStringPrefix	SDK_DEF_STRINGIZE(kHidTxtEdPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kHidTxtEdPluginID, kHidTxtEdPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kHidTxtEdActionComponentBoss,	kHidTxtEdPrefix + 0)
DECLARE_PMID(kClassIDSpace, kHidTxtEdStringRegisterBoss,	kHidTxtEdPrefix + 1)
DECLARE_PMID(kClassIDSpace, kHidTxtEdMenuRegisterBoss,		kHidTxtEdPrefix + 2)
DECLARE_PMID(kClassIDSpace, kHidTxtEdActionRegisterBoss,	kHidTxtEdPrefix + 3)
DECLARE_PMID(kClassIDSpace, kHidTxtEdPanelWidgetBoss,		kHidTxtEdPrefix + 4)
DECLARE_PMID(kClassIDSpace, kHidTxtEdPanelRegisterBoss,		kHidTxtEdPrefix + 5)

DECLARE_PMID(kClassIDSpace, kHidTxtEdHiddenTextWidgetBoss,	kHidTxtEdPrefix + 6)
DECLARE_PMID(kClassIDSpace, kHidTxtEdDialogBoss,			kHidTxtEdPrefix + 7)

// InterfaceIDs:
// None in this plug-in.

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kHidTxtEdActionComponentImpl,		kHidTxtEdPrefix + 0)

DECLARE_PMID(kImplementationIDSpace, kHidTxtEdSelectionObserverImpl,	kHidTxtEdPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kHidTxtEdDlgControllerImpl,	kHidTxtEdPrefix + 2)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kHidTxtEdAboutActionID,				kHidTxtEdPrefix + 0)
DECLARE_PMID(kActionIDSpace, kHidTxtEdPanelWidgetActionID,			kHidTxtEdPrefix + 1)
DECLARE_PMID(kActionIDSpace, kHidTxtEdSeparator1ActionID,			kHidTxtEdPrefix + 2)
DECLARE_PMID(kActionIDSpace, kHidTxtEdPopupAboutThisActionID,		kHidTxtEdPrefix + 3)
DECLARE_PMID(kActionIDSpace, kHidTxtEdCreateActionID,		kHidTxtEdPrefix + 11)
DECLARE_PMID(kActionIDSpace, kHidTxtEdModifyActionID,		kHidTxtEdPrefix + 12)
DECLARE_PMID(kActionIDSpace, kHidTxtEdDeleteActionID,		kHidTxtEdPrefix + 13)

// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kHidTxtEdPanelWidgetID,						kHidTxtEdPrefix + 0) 
DECLARE_PMID(kWidgetIDSpace, kHidTxtEdDialogWidgetID,						kHidTxtEdPrefix + 1) 
DECLARE_PMID(kWidgetIDSpace, kHidTxtEdDialogEditBoxWidgetID,				kHidTxtEdPrefix + 2)

DECLARE_PMID(kWidgetIDSpace, kHidTxtEdPanelDataLabelWidgetID,			kHidTxtEdPrefix + 3) 
DECLARE_PMID(kWidgetIDSpace, kHidTxtEdPanelDataPanelWidgetID,			kHidTxtEdPrefix + 4) 
DECLARE_PMID(kWidgetIDSpace, kHidTxtEdPanelDataWidgetID,				kHidTxtEdPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kHidTxtEdPanelDataScrollBarWidgetID,		kHidTxtEdPrefix + 6) 

// "About Plug-ins" sub-menu:
#define kHidTxtEdAboutMenuKey			kHidTxtEdStringPrefix "kHidTxtEdAboutMenuKey"
#define kHidTxtEdAboutMenuPath			kSDKDefStandardAboutMenuPath kHidTxtEdCompanyKey

// "Plug-ins" sub-menu:
#define kHidTxtEdPluginsMenuKey 		kHidTxtEdStringPrefix "kHidTxtEdPluginsMenuKey"
#define kHidTxtEdPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kHidTxtEdCompanyKey kSDKDefDelimitMenuPath kHidTxtEdPluginsMenuKey

// Menu item keys:
#define kHidTxtEdCreateMenuItemKey		kHidTxtEdStringPrefix "kHidTxtEdCreateMenuItemKey"
#define kHidTxtEdModifyMenuItemKey		kHidTxtEdStringPrefix "kHidTxtEdModifyMenuItemKey"
#define kHidTxtEdDeleteMenuItemKey		kHidTxtEdStringPrefix "kHidTxtEdDeleteMenuItemKey"

// Error string keys:
#define kHidTxtEdCreateFailedStringKey	kHidTxtStringPrefix "kHidTxtEdCreateFailedStringKey"
#define kHidTxtEdModifyFailedStringKey	kHidTxtStringPrefix "kHidTxtEdModifyFailedStringKey"
#define kHidTxtEdDeleteFailedStringKey	kHidTxtStringPrefix "kHidTxtEdDeleteFailedStringKey"

// Panel string keys:
#define kHidTxtEdPanelTitleKey					kHidTxtEdStringPrefix	"kHidTxtEdPanelTitleKey"
#define kHidTxtEdHiddenTextLabelKey					kHidTxtEdStringPrefix	"kHidTxtEdHiddenTextLabelKey"

// Dialog string keys:
#define kHidTxtEdDialogTitleKey					kHidTxtEdStringPrefix	"kHidTxtEdDialogTitleKey"
#define kHidTxtEdCreateDialogTitleKey			kHidTxtEdStringPrefix	"kHidTxtEdCreateDialogTitleKey"
#define kHidTxtEdModifyDialogTitleKey			kHidTxtEdStringPrefix	"kHidTxtEdModifyDialogTitleKey"

// Other StringKeys:
#define kHidTxtEdAboutBoxStringKey				kHidTxtEdStringPrefix "kHidTxtEdAboutBoxStringKey"
#define kHidTxtEdInternalPopupMenuNameKey		kHidTxtEdStringPrefix	"kHidTxtEdInternalPopupMenuNameKey"
#define kHidTxtEdTargetMenuPath kHidTxtEdInternalPopupMenuNameKey

// Menu item positions:
#define kHidTxtEdCreateMenuItemPosition			1.0
#define kHidTxtEdModifyMenuItemPosition			2.0	
#define kHidTxtEdDeleteMenuItemPosition			3.0
#define	kHidTxtEdSeparator1MenuItemPosition			10.0
#define kHidTxtEdAboutThisMenuItemPosition				11.0

#define kHidTxtEdCreate 1
#define kHidTxtEdModify 2

// Initial data format version numbers
#define kHidTxtEdFirstMajorFormatNumber  kSDKDef_30_PersistMajorVersionNumber
#define kHidTxtEdFirstMinorFormatNumber  kSDKDef_30_PersistMinorVersionNumber

// Data format version numbers for the PluginVersion resource 
#define kHidTxtEdCurrentMajorFormatNumber kHidTxtEdFirstMajorFormatNumber // most recent major format change
#define kHidTxtEdCurrentMinorFormatNumber kHidTxtEdFirstMinorFormatNumber // most recent minor format change

#endif // __HidTxtEdID_h__

// End, HidTxtEdID.h.


