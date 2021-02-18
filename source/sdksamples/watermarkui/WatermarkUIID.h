//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/watermarkui/WatermarkUIID.h $
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

#ifndef __WatermarkUIID_h__
#define __WatermarkUIID_h__

#include "SDKDef.h"


// Company:
#define kWatermarkUICompanyKey		kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kWatermarkUICompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kWatermarkUIPluginName		"WatermarkUI"					// Name of this plug-in.
#define kWatermarkUIPrefixNumber	0x105c00 						// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kWatermarkUIVersion			kSDKDefPluginVersionString		// Version of this plug-in (for the About Box).
#define kWatermarkUIAuthor			"Adobe Developer Technologies"	// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kWatermarkUIPrefixNumber above to modify the prefix.)
#define kWatermarkUIPrefix			RezLong(kWatermarkUIPrefixNumber)			// The unique numeric prefix for all object model IDs for this plug-in.
#define kWatermarkUIStringPrefix	SDK_DEF_STRINGIZE(kWatermarkUIPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// Missing plug-in: (see ExtraPluginInfo resource)
#define kWatermarkUIMissingPluginURLValue		kSDKDefPartnersStandardValue_enUS	// URL displayed in Missing Plug-in dialog
#define kWatermarkUIMissingPluginAlertValue		kSDKDefMissingPluginAlertValue		// Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kWatermarkUIPluginID, kWatermarkUIPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kWatermarkUIActionComponentBoss, kWatermarkUIPrefix + 0)
DECLARE_PMID(kClassIDSpace, kWatermarkUIDialogBoss, kWatermarkUIPrefix + 2)
DECLARE_PMID(kClassIDSpace, kAnglePopupSliderComboWidgetBoss, kWatermarkUIPrefix + 3)
DECLARE_PMID(kClassIDSpace, kPreviewableColorListDropDownWidgetBoss, kWatermarkUIPrefix + 4)


// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_IPREVIEWABLECOLORLISTOBSERVER, kWatermarkUIPrefix + 0)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWATERMARKUIINTERFACE, kWatermarkUIPrefix + 1)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWATERMARKUIINTERFACE, kWatermarkUIPrefix + 2)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWATERMARKUIINTERFACE, kWatermarkUIPrefix + 3)
//DECLARE_PMID(kInterfaceIDSpace, IID_IWATERMARKUIINTERFACE, kWatermarkUIPrefix + 4)


// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kWatermarkUIActionComponentImpl, kWatermarkUIPrefix + 0 )
DECLARE_PMID(kImplementationIDSpace, kWatermarkUIDialogControllerImpl, kWatermarkUIPrefix + 1 )
DECLARE_PMID(kImplementationIDSpace, kWatermarkUIDialogObserverImpl, kWatermarkUIPrefix + 2 )
DECLARE_PMID(kImplementationIDSpace, kPreviewableColorListObserverImpl, kWatermarkUIPrefix + 3)
//DECLARE_PMID(kImplementationIDSpace, kWatermarkUIImpl, kWatermarkUIPrefix + 4)
//DECLARE_PMID(kImplementationIDSpace, kWatermarkUIImpl, kWatermarkUIPrefix + 5)


// ActionIDs:
DECLARE_PMID(kActionIDSpace, kWatermarkUIAboutActionID, kWatermarkUIPrefix + 0)
DECLARE_PMID(kActionIDSpace, kWatermarkUIDialogActionID, kWatermarkUIPrefix + 4)
//DECLARE_PMID(kActionIDSpace, kWatermarkUIActionID, kWatermarkUIPrefix + 5)
//DECLARE_PMID(kActionIDSpace, kWatermarkUIActionID, kWatermarkUIPrefix + 6)
//DECLARE_PMID(kActionIDSpace, kWatermarkUIActionID, kWatermarkUIPrefix + 7)
//DECLARE_PMID(kActionIDSpace, kWatermarkUIActionID, kWatermarkUIPrefix + 8)
//DECLARE_PMID(kActionIDSpace, kWatermarkUIActionID, kWatermarkUIPrefix + 9)


// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kWatermarkUIDialogWidgetID, kWatermarkUIPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kWatermarkUIEditBoxWidgetID, kWatermarkUIPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kWatermarkUIRotationWidgetID, kWatermarkUIPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kWatermarkUIHPosDropDownWidgetID, kWatermarkUIPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kWatermarkUIVPosDropDownWidgetID, kWatermarkUIPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kWatermarkUIColorDropDownWidgetID, kWatermarkUIPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kWatermarkUIShowWatermarkCheckBoxWidgetID, kWatermarkUIPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kWatermarkUIDoPrintCheckBoxWidgetID, kWatermarkUIPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kWatermarkUIVOffsetWidgetID, kWatermarkUIPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kWatermarkUIHOffsetWidgetID, kWatermarkUIPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kWatermarkUIOpacityWidgetID, kWatermarkUIPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kWatermarkUIInfoGroupLabelWidgetID, kWatermarkUIPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kWatermarkUIVerticalGroupLabelWidgetID, kWatermarkUIPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kWatermarkUIHorizontalGroupLabelWidgetID, kWatermarkUIPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kWatermarkUICharFontTextWidgetId, kWatermarkUIPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kWatermarkUICharFontFamilyDropDownWidgetId, kWatermarkUIPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kWatermarkUICharPanelStaticTextWidgetId, kWatermarkUIPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kWatermarkUICharFontStyleDropDownWidgetId, kWatermarkUIPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kWatermarkUIFontSizeWidgetID, kWatermarkUIPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kWatermarkUIFontSizeNudgeWidgetID, kWatermarkUIPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kWatermarkUIFontSizeStaticWidgetID, kWatermarkUIPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kWatermarkUICharacterGroupLabelWidgetID, kWatermarkUIPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kWatermarkUIDrawInBackCheckBoxWidgetID, kWatermarkUIPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kWatermarkUIHOffsetNudgeWidgetID, kWatermarkUIPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kWatermarkUIVOffsetNudgeWidgetID, kWatermarkUIPrefix + 26)


// "About Plug-ins" sub-menu:
#define kWatermarkUIAboutMenuKey		kWatermarkUIStringPrefix "kWatermarkUIAboutMenuKey"
#define kWatermarkUIAboutMenuPath		kSDKDefStandardAboutMenuPath kWatermarkUICompanyKey

// "Plug-ins" sub-menu:
#define kWatermarkUIPluginsMenuKey 		kWatermarkUIStringPrefix "kWatermarkUIPluginsMenuKey"
#define kWatermarkUIPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kWatermarkUICompanyKey

// "Plug-ins" sub-menu item key for dialog:
#define kWatermarkUIDialogMenuItemKey	kWatermarkUIStringPrefix "kWatermarkUIDialogMenuItemKey"

// "Plug-ins" sub-menu item position for dialog:
#define kWatermarkUIDialogMenuItemPosition	12.0

// About StringKeys:
#define kWatermarkUIAboutBoxStringKey		kWatermarkUIStringPrefix "kWatermarkUIAboutBoxStringKey"

// Dialog StringKeys:
#define kWatermarkUIDialogTitleKey	kWatermarkUIStringPrefix "kWatermarkUIDialogTitleKey"
#define kWatermarkUIShowWatermarkStringKey "kWatermarkUIShowWatermarkStringKey"
#define kWatermarkUIDoPrintWatermarkStringKey "kWatermarkUIDoPrintWatermarkStringKey"
#define kWatermarkUIVPosCenterDropDownItemKey "kWatermarkUIVPosCenterDropDownItemKey"
#define kWatermarkUIVPosTopDropDownItemKey "kWatermarkUIVPosTopDropDownItemKey"
#define kWatermarkUIVPosBottomDropDownItemKey "kWatermarkUIVPosBottomDropDownItemKey"          
#define kWatermarkUIHPosCenterDropDownItemKey "kWatermarkUIHPosCenterDropDownItemKey"
#define kWatermarkUIHPosLeftDropDownItemKey	"kWatermarkUIHPosLeftDropDownItemKey"
#define kWatermarkUIHPosRightDropDownItemKey "kWatermarkUIHPosRightDropDownItemKey"
#define kWatermarkUIRotationLabelItemKey "kWatermarkUIRotationLabelItemKey"
#define kWatermarkUIOpacityLabelItemKey "kWatermarkUIOpacityLabelItemKey"
#define kWatermarkUIWmkTextLabelItemKey "kWatermarkUIWmkTextLabelItemKey"
#define kWatermarkUIColorLabelItemKey "kWatermarkUIColorLabelItemKey"
#define kWatermarkUIVPosLabelItemKey "kWatermarkUIVPosLabelItemKey"
#define kWatermarkUIHPosLabelItemKey "kWatermarkUIHPosLabelItemKey"
#define kWatermarkUIOffsetLabelItemKey "kWatermarkUIOffsetLabelItemKey"
#define kWatermarkUIInfoLabelItemKey "kWatermarkUIInfoLabelItemKey"
#define kWatermarkUICharacterLabelItemKey "kWatermarkUICharacterLabelItemKey"
#define kWatermarkUIFamilyLabelItemKey "kWatermarkUIFamilyLabelItemKey"
#define kWatermarkUIStyleLabelItemKey "kWatermarkUIStyleLabelItemKey"
#define kWatermarkUISizeLabelItemKey "kWatermarkUISizeLabelItemKey"
#define kWatermarkUIDrawInBackWatermarkStringKey "kWatermarkUIDrawInBackWatermarkStringKey"

// Initial data format version numbers
#define kWatermarkUIFirstMajorFormatNumber  RezLong(1)
#define kWatermarkUIFirstMinorFormatNumber  RezLong(0)

// Data format version numbers for the PluginVersion resource 
#define kWatermarkUICurrentMajorFormatNumber kWatermarkUIFirstMajorFormatNumber
#define kWatermarkUICurrentMinorFormatNumber kWatermarkUIFirstMinorFormatNumber


#endif // __WatermarkUIID_h__

//  Code generated by DollyXs code generator
