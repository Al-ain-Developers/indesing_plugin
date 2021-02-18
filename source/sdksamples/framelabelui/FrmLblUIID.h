//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/framelabelui/FrmLblUIID.h $
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

#ifndef __FrmLblUIID_h__
#define __FrmLblUIID_h__

#include "SDKDef.h"

// Company:
#define kFrmLblUICompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kFrmLblUICompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kFrmLblUIPluginName	"FrameLabelUI"			// Name of this plug-in.
#define kFrmLblUIPrefixNumber	0x100c00 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kFrmLblUIVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kFrmLblUIAuthor		" "					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kFrmLblUIPrefixNumber above to modify the prefix.)
#define kFrmLblUIPrefix		RezLong(kFrmLblUIPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kFrmLblUIStringPrefix	SDK_DEF_STRINGIZE(kFrmLblUIPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// Missing plug-in: (see ExtraPluginInfo resource)
#define kFrmLblUIMissingPluginURLValue		kSDKDefPartnersStandardValue_enUS // URL displayed in Missing Plug-in dialog
#define kFrmLblUIMissingPluginAlertValue	kSDKDefMissingPluginAlertValue // Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kFrmLblUIPluginID, kFrmLblUIPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kFrmLblUIActionComponentBoss, kFrmLblUIPrefix + 0)
DECLARE_PMID(kClassIDSpace, kFrmLblUIDialogBoss, kFrmLblUIPrefix + 1)

// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kFrmLblUIActionComponentImpl, kFrmLblUIPrefix + 0 )
DECLARE_PMID(kImplementationIDSpace, kFrmLblUIDialogControllerImpl, kFrmLblUIPrefix + 1 )

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kFrmLblUIAboutActionID, kFrmLblUIPrefix + 0)
DECLARE_PMID(kActionIDSpace, kFrmLblUIDialogActionID, kFrmLblUIPrefix + 1)
DECLARE_PMID(kActionIDSpace, kFrmLblUIPrintFrmLblActionID, kFrmLblUIPrefix + 2)

// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kFrmLblUIDialogWidgetID, kFrmLblUIPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kFrmLblUIColorDropDownWidgetID, kFrmLblUIPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kFrmLblUIAdornmentTextEditBoxWidgetID, kFrmLblUIPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kFrmLblUIShowLabelCheckBoxWidgetID, kFrmLblUIPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kFrmLblUILabelPosDropDownWidgetID, kFrmLblUIPrefix + 5)

// "About Plug-ins" sub-menu:
#define kFrmLblUIAboutMenuKey			kFrmLblUIStringPrefix "kFrmLblUIAboutMenuKey"
#define kFrmLblUIAboutMenuPath		kSDKDefStandardAboutMenuPath kFrmLblUICompanyKey

// "Plug-ins" sub-menu:
#define kFrmLblUIPluginsMenuKey 		kFrmLblUIStringPrefix "kFrmLblUIPluginsMenuKey"
#define kFrmLblUIPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kFrmLblUICompanyKey kSDKDefDelimitMenuPath kFrmLblUIPluginsMenuKey

// Other StringKeys:
#define kFrmLblUIAboutBoxStringKey	kFrmLblUIStringPrefix "kFrmLblUIAboutBoxStringKey"
#define kFrmLblUITargetMenuPath kFrmLblUIPluginsMenuPath
#define kFrmLblUILabelPosTopDropDownItemKey "kFrmLblUILabelPosTopDropDownItemKey"
#define kFrmLblUILabelPosBottomDropDownItemKey "kFrmLblUILabelPosBottomDropDownItemKey"
#define kFrmLblUILabelPosRightDropDownItemKey "kFrmLblUILabelPosRightDropDownItemKey"
#define kFrmLblUILabelPosLeftDropDownItemKey "kFrmLblUILabelPosLeftDropDownItemKey"
#define kFrmLblUIShowLabelStringKey "kFrmLblUIShowLabelStringKey"
#define kFrmLblUIAdornmentLabelStringKey kFrmLblUIStringPrefix "kFrmLblUIAdomentLabelStringKey"
#define kFrmLblUIFontColorStringKey kFrmLblUIStringPrefix "kFrmLblUIFontColorStringKey"
#define kFrmLblUIFonPositionStringKey kFrmLblUIStringPrefix "kFrmLblUIFonPositionStringKey"
#define kFrmLblUIDepChkErrorStringKey kFrmLblUIStringPrefix "kFrmLblUIDepChkErrorStringKey"

// Menu item positions:
#define kFrmLblUIDialogTitleKey kFrmLblUIStringPrefix "kFrmLblUIDialogTitleKey"

// "Plug-ins" sub-menu item key for dialog:
#define kFrmLblUIDialogMenuItemKey kFrmLblUIStringPrefix "kFrmLblUIDialogMenuItemKey"
#define kFrmLblUIPrintFrmLblMenuItemKey kFrmLblUIStringPrefix"kFrmLblUIPrintFrmLblMenuItemKey"

// "Plug-ins" sub-menu item position for dialog:
#define kFrmLblUIDialogMenuItemPosition	12.0
#define kFrmLblUIUIPrintFrmLblMenuItemPosition 13.0

// Initial data format version numbers
#define kFrmLblUIFirstMajorFormatNumber  RezLong(1)
#define kFrmLblUIFirstMinorFormatNumber  RezLong(0)

// Data format version numbers for the PluginVersion resource 
#define kFrmLblUICurrentMajorFormatNumber kFrmLblUIFirstMajorFormatNumber
#define kFrmLblUICurrentMinorFormatNumber kFrmLblUIFirstMinorFormatNumber

#endif // __FrmLblUIID_h__
