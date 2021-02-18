//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ColorPickerID.h $
//  
//  Owner: SusanCL
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

#ifndef __ColorPickerID__
#define __ColorPickerID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kColorPickerPrefix			RezLong(0x7200)		// Registered in DeveloperPrefix.h

// <Start IDC>
// PluginID
#define kColorPickerPluginName 			"Color Picker Panel"
DECLARE_PMID(kPlugInIDSpace, kColorPickerPluginID, kColorPickerPrefix + 1)

// <Class ID>
// ---------------------------------------------------------------
//  Class IDs
// ---------------------------------------------------------------
DECLARE_PMID(kClassIDSpace, kColorPickerPanelWidgetBoss, kColorPickerPrefix + 1)
DECLARE_PMID(kClassIDSpace, kModelessColorPickerPanelWidgetBoss, kColorPickerPrefix + 2)
DECLARE_PMID(kClassIDSpace, kColorPickerPanelRegisterBoss, kColorPickerPrefix + 3)
DECLARE_PMID(kClassIDSpace, kFillStrokeColorControlStripBoss, kColorPickerPrefix + 4)
DECLARE_PMID(kClassIDSpace, kColorSliderWidgetBoss, kColorPickerPrefix + 5)
DECLARE_PMID(kClassIDSpace, kColorIntEditBoxWidgetBoss, kColorPickerPrefix + 6)
DECLARE_PMID(kClassIDSpace, kColorRealEditBoxWidgetBoss, kColorPickerPrefix + 7)

DECLARE_PMID(kClassIDSpace, kColorPickerPanelMenuComponentBoss, kColorPickerPrefix + 8)
DECLARE_PMID(kClassIDSpace, kSpectrumWidgetBoss, kColorPickerPrefix + 9)
DECLARE_PMID(kClassIDSpace, kProxyWidgetBoss, kColorPickerPrefix + 10)
DECLARE_PMID(kClassIDSpace, kTintProxyWidgetBoss, kColorPickerPrefix + 11)
DECLARE_PMID(kClassIDSpace, kColorProxyWidgetBoss, kColorPickerPrefix + 12)
DECLARE_PMID(kClassIDSpace, kTintSpectrumWidgetBoss, kColorPickerPrefix + 13)

DECLARE_PMID(kClassIDSpace, kColorSliderTrackerBoss, kColorPickerPrefix + 14)
DECLARE_PMID(kClassIDSpace, kSpectrumTrackerBoss, kColorPickerPrefix + 15)
DECLARE_PMID(kClassIDSpace, kColorPickerTrackersRegisterBoss, kColorPickerPrefix + 16)
DECLARE_PMID(kClassIDSpace, kColorPickerPanelControlStripIconPopUpBoss, kColorPickerPrefix + 17)

DECLARE_PMID(kClassIDSpace, kNoneWidgetBoss, kColorPickerPrefix + 18)
DECLARE_PMID(kClassIDSpace, kHouseWidgetBoss, kColorPickerPrefix + 19)
DECLARE_PMID(kClassIDSpace, kGamutAlertWidgetBoss, kColorPickerPrefix + 20)
DECLARE_PMID(kClassIDSpace, kGamutProxyWidgetBoss, kColorPickerPrefix + 21)

DECLARE_PMID(kClassIDSpace, kGenericColorPickerWidgetBoss, kColorPickerPrefix + 22)
DECLARE_PMID(kClassIDSpace, kTintColorPickerWidgetBoss, kColorPickerPrefix + 23)
DECLARE_PMID(kClassIDSpace, kRgbColorPickerWidgetBoss, kColorPickerPrefix + 24)
DECLARE_PMID(kClassIDSpace, kCmykColorPickerWidgetBoss, kColorPickerPrefix + 25)
DECLARE_PMID(kClassIDSpace, kLabColorPickerWidgetBoss, kColorPickerPrefix + 26)

DECLARE_PMID(kClassIDSpace, kTintSliderWidgetBoss, kColorPickerPrefix + 27)
DECLARE_PMID(kClassIDSpace, kTintEditBoxWidgetBoss, kColorPickerPrefix + 28)
DECLARE_PMID(kClassIDSpace, kTintBaseColorNameWidgetBoss, kColorPickerPrefix + 29)
DECLARE_PMID(kClassIDSpace, kTintColorInfoWidgetBoss, kColorPickerPrefix + 30)

DECLARE_PMID(kClassIDSpace, kK2ColorPickerPanelWidgetBoss, kColorPickerPrefix + 31)
DECLARE_PMID(kClassIDSpace, kColorPickerStrokeFillWidgetBoss, kColorPickerPrefix + 32)
DECLARE_PMID(kClassIDSpace, kColorProxyPanelWidgetBoss, kColorPickerPrefix + 33)
DECLARE_PMID(kClassIDSpace, kColorProxyIconWidgetBoss, kColorPickerPrefix + 34)
DECLARE_PMID(kClassIDSpace, kSimpleColorProxyWidgetBoss, kColorPickerPrefix + 35)

DECLARE_PMID(kClassIDSpace, kCmykColorSliderWidgetBoss, kColorPickerPrefix + 36)
DECLARE_PMID(kClassIDSpace, kRgbColorSliderWidgetBoss, kColorPickerPrefix + 37)
DECLARE_PMID(kClassIDSpace, kCmykColorRealEditBoxWidgetBoss, kColorPickerPrefix + 38)
DECLARE_PMID(kClassIDSpace, kRgbColorIntEditBoxWidgetBoss, kColorPickerPrefix + 39)


DECLARE_PMID(kClassIDSpace, kCmykColorSliderTrackerBoss, kColorPickerPrefix + 40)
DECLARE_PMID(kClassIDSpace, kLabColorSliderWidgetBoss, kColorPickerPrefix + 41)
DECLARE_PMID(kClassIDSpace, kLabColorSliderTrackerBoss, kColorPickerPrefix + 42)

DECLARE_PMID(kClassIDSpace, kGamutProxyBaseWidgetBoss, kColorPickerPrefix + 43)
//gap
DECLARE_PMID(kClassIDSpace, kColorPickerActionRegisterBoss, kColorPickerPrefix + 46)

DECLARE_PMID(kClassIDSpace, kColorPickerObjectTextProxyIconBoss, kColorPickerPrefix + 47)

DECLARE_PMID(kClassIDSpace, kColorPickerColorRenderBoss, kColorPickerPrefix + 48)

DECLARE_PMID(kClassIDSpace, kNChannelPickerPanelWidgetBoss, kColorPickerPrefix + 49)
DECLARE_PMID(kClassIDSpace, kNChannelTreeViewWidgetBoss, kColorPickerPrefix + 50)
DECLARE_PMID(kClassIDSpace, kNChannelListElementBoss, kColorPickerPrefix + 51)
DECLARE_PMID(kClassIDSpace, kInkItemTintSliderPanelBoss, kColorPickerPrefix + 52)
DECLARE_PMID(kClassIDSpace, kNChannelProxyWidgetBoss, kColorPickerPrefix + 53)

DECLARE_PMID(kClassIDSpace, kCommonColorPickerDialogBoss, kColorPickerPrefix + 54)
DECLARE_PMID(kClassIDSpace, kCommonColorFieldWidgetBoss, kColorPickerPrefix + 55)
DECLARE_PMID(kClassIDSpace, kCommonColorSliderWidgetBoss, kColorPickerPrefix + 56)
DECLARE_PMID(kClassIDSpace, kCommonColorFieldTrackerBoss, kColorPickerPrefix + 57)
DECLARE_PMID(kClassIDSpace, kCommonColorProxyWidgetBoss, kColorPickerPrefix + 58)
DECLARE_PMID(kClassIDSpace, kCommonColorSliderTrackerBoss, kColorPickerPrefix + 59)

DECLARE_PMID(kClassIDSpace, kColorPickerPopupPanelBoss, kColorPickerPrefix + 60)
DECLARE_PMID(kClassIDSpace, kColorPickerTouchPanelBoss, kColorPickerPrefix + 61)
DECLARE_PMID(kClassIDSpace, kTouchSpectrumWidgetBoss, kColorPickerPrefix + 62)
DECLARE_PMID(kClassIDSpace, kTouchSpectrumTrackerBoss, kColorPickerPrefix + 63)
DECLARE_PMID(kClassIDSpace, kColorPickerTouchContainerWidgetBoss, kColorPickerPrefix + 64)
DECLARE_PMID(kClassIDSpace, kRgbColorTouchPickerWidgetBoss, kColorPickerPrefix + 65)
DECLARE_PMID(kClassIDSpace, kCmykColorTouchPickerWidgetBoss, kColorPickerPrefix + 66)
DECLARE_PMID(kClassIDSpace, kColorPickerStrokeFillWithAssociatedWidgetBoss, kColorPickerPrefix + 67)
DECLARE_PMID(kClassIDSpace, kHsbColorTouchPickerWidgetBoss, kColorPickerPrefix + 68)
DECLARE_PMID(kClassIDSpace, kRecentColorProxyWidgetBoss, kColorPickerPrefix + 69)
DECLARE_PMID(kClassIDSpace, kSwatchTouchPanelBoss, kColorPickerPrefix + 70)
DECLARE_PMID(kClassIDSpace, kColorPickerSwatchTouchPanelBoss, kColorPickerPrefix + 71)
DECLARE_PMID(kClassIDSpace, kHexColorEditBoxWidgetBoss, kColorPickerPrefix + 72)
DECLARE_PMID(kClassIDSpace, kPopupStrokeFillWidgetBoss, kColorPickerPrefix + 73)
DECLARE_PMID(kClassIDSpace, kColorPopupPanelBoss, kColorPickerPrefix + 74)
DECLARE_PMID(kClassIDSpace, kRgbColorPopupWidgetBoss, kColorPickerPrefix + 75)
DECLARE_PMID(kClassIDSpace, kCmykColorPopupWidgetBoss, kColorPickerPrefix + 76)
DECLARE_PMID(kClassIDSpace, kLabColorPopupWidgetBoss, kColorPickerPrefix + 77)
DECLARE_PMID(kClassIDSpace, kTintColorPopupWidgetBoss, kColorPickerPrefix + 78)
DECLARE_PMID(kClassIDSpace, kColorPopupStrokeFillTintWidgetBoss, kColorPickerPrefix + 79)
DECLARE_PMID(kClassIDSpace, kColorPopupWindowDialogBoss, kColorPickerPrefix + 80)
DECLARE_PMID(kClassIDSpace, kTintColorProxyWidgetBoss, kColorPickerPrefix + 81)
DECLARE_PMID(kClassIDSpace, kPropertiesPanelColorPickerPanelWidgetBoss, kColorPickerPrefix + 82)
//gap
DECLARE_PMID(kClassIDSpace, kPopupColorProxyWidgetBoss, kColorPickerPrefix + 86)
DECLARE_PMID(kClassIDSpace, kColorPopupNoneWidgetBoss, kColorPickerPrefix + 87)


DECLARE_PMID(kClassIDSpace, kHsbColorPickerWidgetBoss, kColorPickerPrefix + 88)
DECLARE_PMID(kClassIDSpace, kHsbColorSliderWidgetBoss, kColorPickerPrefix + 89)
DECLARE_PMID(kClassIDSpace, kHsbColorIntEditBoxWidgetBoss, kColorPickerPrefix + 90)
DECLARE_PMID(kClassIDSpace, kHsbColorPopupWidgetBoss, kColorPickerPrefix + 91)
//kHsbColorPopupWidgetBos
// <Interface ID>
// ---------------------------------------------------------------
// Interface IDs
// ---------------------------------------------------------------
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORPICKERWIDGETPROVIDER, kColorPickerPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORCONTROLOBSERVER, kColorPickerPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ISPECTRUMDATA, kColorPickerPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORMETADATAOBSERVER, kColorPickerPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_ISPECTRUMATTRIBUTES, kColorPickerPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORPICKERPANELATTRIBUTES, kColorPickerPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORPICKERPANELHELPER, kColorPickerPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORCONTROLDATARANGEMAPPER, kColorPickerPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORPICKERPANELOPTIONDATA, kColorPickerPrefix + 9)

//DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORPICKERPANELMODKEYSTATE, kColorPickerPrefix + 11)
// This interface has been combined with IID_ICOLORPICKERPANELMODKEYSTATEDATA
// Changed for Sherpa to implement shift-click

DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORPICKERPANELMODKEYSTATEDATA, kColorPickerPrefix + 10)
// This data interface stores a mod key state and also keeps track for the global swatch 
// associated with color definition changes due to shift-click
// Key state for the ColorPicker panel is stored as an int32.
// We save modifier key state only if they are relevant to the panel's observers.
// Starting with the lowest bit position:
//		bit 0 = 1 if shift key pressed when mouse down
//		bit 1 = 1 if command key pressed when mouse down
//		bit 2 = 1 if alt/option key pressed when mouse down
// The data includes:
//		boolean to indicate whether it starts with a global swatch
//		UID of the global swatch
//		Tint% of the global swatch if swatch was a base color				

DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORBARCURSORPROVIDER, kColorPickerPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTROKEFILLPROXYMETADATAOBSERVER, kColorPickerPrefix + 12)

// ---------------------------------------------------------------
// Helper message protocols
// ---------------------------------------------------------------
DECLARE_PMID(kInterfaceIDSpace, IID_ISYNCHGS_COLORPICKERMETADATA, kColorPickerPrefix + 13)

DECLARE_PMID(kInterfaceIDSpace, IID_INCHANNELLISTPANEL_ATTACHOBSERVER, kColorPickerPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_INCHANNELPICKERPANELOBSERVER, kColorPickerPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMMONCOLORFIELDDATA, kColorPickerPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMMONCOLORPICKERUTILS, kColorPickerPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_ISWITCHTOGUIDE, kColorPickerPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_IRECENTCOLORDATA, kColorPickerPrefix + 19)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORPOPUPANCHORDATA, kColorPickerPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTROKEFILLRECTDATA, kColorPickerPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_IPOPUPDIMENSIONS, kColorPickerPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_IMINMAXSWATCHESUIDLISTDATA, kColorPickerPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_IBASESWATCHUIDDATA, kColorPickerPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_IHIDEPOPUPWINDOW, kColorPickerPrefix + 24)


// <Implementation ID>
// ---------------------------------------------------------------
// Implementation IDs
// ---------------------------------------------------------------
//DECLARE_PMID(kImplementationIDSpace, kColorPickerPanelRegisterImpl, kColorPickerPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kColorPickerPanelImpl, kColorPickerPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kColorPickerPanelMenuComponentImpl, kColorPickerPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kColorSliderTrackerImpl, kColorPickerPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kColorSliderEHImpl, kColorPickerPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kColorSliderViewImpl, kColorPickerPrefix + 6)

DECLARE_PMID(kImplementationIDSpace, kProxyEHImpl, kColorPickerPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kProxyViewImpl, kColorPickerPrefix + 8)

DECLARE_PMID(kImplementationIDSpace, kSpectrumEHImpl, kColorPickerPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kSpectrumViewImpl, kColorPickerPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kSpectrumDataImpl, kColorPickerPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kSpectrumTrackerImpl, kColorPickerPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kColorPickerTrackersRegisterImpl, kColorPickerPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kColorPickerTrackerEHImpl, kColorPickerPrefix + 14)
//gap
DECLARE_PMID(kImplementationIDSpace, kHouseProxyViewImpl, kColorPickerPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kGamutControlEHImpl, kColorPickerPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kNoneControlEHImpl, kColorPickerPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kColorProxyViewImpl, kColorPickerPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kNoneProxyViewImpl, kColorPickerPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kSpectrumAttributesImpl, kColorPickerPrefix + 21)

DECLARE_PMID(kImplementationIDSpace, kColorEditBoxViewImpl, kColorPickerPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kColorEditBoxObserverImpl, kColorPickerPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kColorSliderObserverImpl, kColorPickerPrefix + 24)

// Color Picker panel service providers
DECLARE_PMID(kImplementationIDSpace, kColorPickerWidgetServiceImpl, kColorPickerPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kColorPickerWidgetProviderImpl, kColorPickerPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kRgbColorPickerWidgetProviderImpl, kColorPickerPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kCmykColorPickerWidgetProviderImpl, kColorPickerPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kLabColorPickerWidgetProviderImpl, kColorPickerPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kTintColorPickerWidgetProviderImpl, kColorPickerPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kRgbPickerPanelCreatorImpl, kColorPickerPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kCmykPickerPanelCreatorImpl, kColorPickerPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kLabPickerPanelCreatorImpl, kColorPickerPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kTintPickerPanelCreatorImpl, kColorPickerPrefix + 34)


DECLARE_PMID(kImplementationIDSpace, kProxyMetaDataObserverImpl, kColorPickerPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kSliderMetaDataObserverImpl, kColorPickerPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kEditBoxMetaDataObserverImpl, kColorPickerPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kPickerGraphicStateObserverImpl, kColorPickerPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kPanelMetaDataObserverImpl, kColorPickerPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kPickerGfxStateDefnObserverImpl, kColorPickerPrefix + 40)

DECLARE_PMID(kImplementationIDSpace, kColorPickerPanelAttributesImpl, kColorPickerPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kColorPickerPanelHelperImpl, kColorPickerPrefix + 42)

DECLARE_PMID(kImplementationIDSpace, kSolidPanelDataImpl, kColorPickerPrefix + 43)

DECLARE_PMID(kImplementationIDSpace, kTintBaseColorNameViewImpl, kColorPickerPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kTintSliderObserverImpl, kColorPickerPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kTintEditBoxObserverImpl, kColorPickerPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kColorAttributeObserverImpl, kColorPickerPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kProxyColorAttributeObserverImpl, kColorPickerPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kTintColorInfoViewImpl, kColorPickerPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kSpectrumViewTipsImpl, kColorPickerPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kStrokeFillProxyMetaDataObserverImpl, kColorPickerPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kColorProxyEHImpl, kColorPickerPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kProxyViewTipsImpl, kColorPickerPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kTintSliderEHImpl, kColorPickerPrefix + 54)

DECLARE_PMID(kImplementationIDSpace, kColorSliderDataRangeMapperImpl, kColorPickerPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kColorEditDataRangeMapperImpl, kColorPickerPrefix + 56)

DECLARE_PMID(kImplementationIDSpace, kPickerOptionDataObserverImpl, kColorPickerPrefix + 57)

DECLARE_PMID(kImplementationIDSpace, kColorPickerDetailControllerImpl, kColorPickerPrefix + 58)

DECLARE_PMID(kImplementationIDSpace, kCmykColorSliderTrackerImpl, kColorPickerPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kLabColorSliderTrackerImpl, kColorPickerPrefix + 60)

//DECLARE_PMID(kImplementationIDSpace, kColorProxyIconViewImpl, kColorPickerPrefix + 61)

DECLARE_PMID(kImplementationIDSpace, kColorPickerPanelModKeyStateDataImpl, kColorPickerPrefix + 62)

DECLARE_PMID(kImplementationIDSpace, kSimpleColorDDSourceImpl, kColorPickerPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kColorDDSourceImpl, kColorPickerPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kNoneDDSourceImpl, kColorPickerPrefix + 65)

DECLARE_PMID(kImplementationIDSpace, kColorBarCursorProviderImpl, kColorPickerPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kColorPickerActionRegisterImpl, kColorPickerPrefix + 67)

DECLARE_PMID(kImplementationIDSpace, kColorPickerRenderObjectImpl, kColorPickerPrefix + 68)

DECLARE_PMID(kImplementationIDSpace, kNChannelInkListAttachObserverImpl, kColorPickerPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kNChannelPickerPanelObserverImpl, kColorPickerPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kInkItemTintSliderPanelObserverImpl, kColorPickerPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kNChannelColorProxyViewImpl, kColorPickerPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kNChannelPickerPanelCreatorImpl, kColorPickerPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kNChannelPickerWidgetProviderImpl, kColorPickerPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kInkListTreeViewAdapterImpl, kColorPickerPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kInkListTreeViewWidgetMgrImpl, kColorPickerPrefix + 76)

DECLARE_PMID(kImplementationIDSpace, kCommonColorPickerDialogControllerImpl, kColorPickerPrefix + 77)
DECLARE_PMID(kImplementationIDSpace, kCommonColorPickerDialogObserverImpl, kColorPickerPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kCommonColorPickerUtilsImpl, kColorPickerPrefix + 79)
DECLARE_PMID(kImplementationIDSpace, kCommonColorFieldDataImpl, kColorPickerPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kCommonColorFieldEHImpl, kColorPickerPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kCommonColorFieldTrackerImpl, kColorPickerPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kCommonColorFieldViewImpl, kColorPickerPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kCommonColorProxyViewImpl, kColorPickerPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kCommonColorSliderDataRangeMapperImpl, kColorPickerPrefix + 85)
DECLARE_PMID(kImplementationIDSpace, kCommonColorSliderEHImpl, kColorPickerPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kCommonColorSliderObserverImpl, kColorPickerPrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kCommonColorSliderViewImpl, kColorPickerPrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kCommonSliderMetaDataObserverImpl, kColorPickerPrefix + 89)
DECLARE_PMID(kImplementationIDSpace, kCommonColorSliderTrackerImpl, kColorPickerPrefix + 90)
DECLARE_PMID(kImplementationIDSpace, kCommonColorProxyEHImpl, kColorPickerPrefix + 91)
DECLARE_PMID(kImplementationIDSpace, kColorPickerTouchPanelObserverImpl, kColorPickerPrefix + 92)
DECLARE_PMID(kImplementationIDSpace, kTouchPanelMetaDataObserverImpl, kColorPickerPrefix + 93)
DECLARE_PMID(kImplementationIDSpace, kTouchColorPickerGSObserverImpl, kColorPickerPrefix + 94)
DECLARE_PMID(kImplementationIDSpace, kTouchSpectrumEHImpl,			  kColorPickerPrefix + 95)
DECLARE_PMID(kImplementationIDSpace, kTouchSpectrumTrackerImpl, kColorPickerPrefix + 96)
DECLARE_PMID(kImplementationIDSpace, kColorPickerTouchContainerViewImpl, kColorPickerPrefix + 97)
DECLARE_PMID(kImplementationIDSpace, kColorPickerTouchContainerObsImpl, kColorPickerPrefix + 98)
DECLARE_PMID(kImplementationIDSpace, kColorPickerTouchWidgetServiceImpl, kColorPickerPrefix + 99)
DECLARE_PMID(kImplementationIDSpace, kCmykColorPickerTouchWidgetProviderImpl, kColorPickerPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kRgbColorPickerTouchWidgetProviderImpl, kColorPickerPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kRgbPickerTouchPanelCreatorImpl, kColorPickerPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kCmykPickerTouchPanelCreatorImpl, kColorPickerPrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kColorPickerTouchPanelViewImpl, kColorPickerPrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kHsbColorPickerTouchWidgetProviderImpl, kColorPickerPrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kHsbPickerTouchPanelCreatorImpl, kColorPickerPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kRecentColorProxyViewImpl, kColorPickerPrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kRecentColorProxyEHImpl, kColorPickerPrefix + 108)
DECLARE_PMID(kImplementationIDSpace, kColorPickerSwatchTouchPanelViewImpl, kColorPickerPrefix + 109)
DECLARE_PMID(kImplementationIDSpace, kHexColorDataValidationImpl, kColorPickerPrefix + 110)
DECLARE_PMID(kImplementationIDSpace, kHexColorEditBoxObserverImpl, kColorPickerPrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kHexColorEBMetaDataObserverImpl, kColorPickerPrefix + 112)
//gap
DECLARE_PMID(kImplementationIDSpace, kColorPopupWidgetServiceImpl, kColorPickerPrefix + 116)
DECLARE_PMID(kImplementationIDSpace, kColorPopupObserverImpl, kColorPickerPrefix + 117)
DECLARE_PMID(kImplementationIDSpace, kColorPopupViewImpl, kColorPickerPrefix + 118)
//gap
DECLARE_PMID(kImplementationIDSpace, kTintColorProxyEHImpl, kColorPickerPrefix + 120)
DECLARE_PMID(kImplementationIDSpace, kPropertiesPanelColorPickerViewImpl, kColorPickerPrefix + 121)
DECLARE_PMID(kImplementationIDSpace, kColorPopupDialogViewImpl, kColorPickerPrefix + 122)
DECLARE_PMID(kImplementationIDSpace, kPopupColorProxyViewImpl, kColorPickerPrefix + 123)
DECLARE_PMID(kImplementationIDSpace, kColorPopupNoneProxyViewImpl, kColorPickerPrefix + 124)
DECLARE_PMID(kImplementationIDSpace, kColorPopupEventHandlerImpl, kColorPickerPrefix + 125)

DECLARE_PMID(kImplementationIDSpace, kHsbPickerPanelCreatorImpl, kColorPickerPrefix + 126)
DECLARE_PMID(kImplementationIDSpace, kHsbColorPickerWidgetProviderImpl, kColorPickerPrefix + 127)

// <Widget ID>
// ---------------------------------------------------------------
//  Widget IDs
// ---------------------------------------------------------------
DECLARE_PMID(kWidgetIDSpace, kSpectrumWidgetId, kColorPickerPrefix + 1)

// These widget ID groups need to be contiguous within each group
DECLARE_PMID(kWidgetIDSpace, kRedEditBoxWidgetId, kColorPickerPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kGreenEditBoxWidgetId, kColorPickerPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kBlueEditBoxWidgetId, kColorPickerPrefix + 4)

DECLARE_PMID(kWidgetIDSpace, kRedSliderWidgetId, kColorPickerPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kGreenSliderWidgetId, kColorPickerPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kBlueSliderWidgetId, kColorPickerPrefix + 7)

DECLARE_PMID(kWidgetIDSpace, kCyanEditBoxWidgetId, kColorPickerPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kMagentaEditBoxWidgetId, kColorPickerPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kYellowEditBoxWidgetId, kColorPickerPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kBlackEditBoxWidgetId, kColorPickerPrefix + 11)

DECLARE_PMID(kWidgetIDSpace, kCyanSliderWidgetId, kColorPickerPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kMagentaSliderWidgetId, kColorPickerPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kYellowSliderWidgetId, kColorPickerPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kBlackSliderWidgetId, kColorPickerPrefix + 15)

DECLARE_PMID(kWidgetIDSpace, kLabLEditBoxWidgetId, kColorPickerPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kLabAEditBoxWidgetId, kColorPickerPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kLabBEditBoxWidgetId, kColorPickerPrefix + 18)

DECLARE_PMID(kWidgetIDSpace, kLabLSliderWidgetId, kColorPickerPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kLabASliderWidgetId, kColorPickerPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kLabBSliderWidgetId, kColorPickerPrefix + 21)

DECLARE_PMID(kWidgetIDSpace, kColorProxyWidgetId, kColorPickerPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kLastColorIconWidgetId, kColorPickerPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kColorPickerControlStripIconPopUpWidgetID, kColorPickerPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kColorPickerPanelWidgetId, kColorPickerPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kTintColorPickerWidgetId, kColorPickerPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kRgbColorPickerWidgetId, kColorPickerPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kCmykColorPickerWidgetId, kColorPickerPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kLabColorPickerWidgetId, kColorPickerPrefix + 29)

DECLARE_PMID(kWidgetIDSpace, kNoneWidgetId, kColorPickerPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kHouseWidgetId, kColorPickerPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kGamutAlertWidgetId, kColorPickerPrefix + 32)

DECLARE_PMID(kWidgetIDSpace, kControlStripFillProxyPanelWidgetId, kColorPickerPrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kControlStripStrokeProxyPanelWidgetId, kColorPickerPrefix + 34)

DECLARE_PMID(kWidgetIDSpace, kTintEditBoxWidgetId, kColorPickerPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kTintSliderWidgetId, kColorPickerPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kTintBaseColorNameWidgetId, kColorPickerPrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kTintColorInfoWidgetId, kColorPickerPrefix + 38)

DECLARE_PMID(kWidgetIDSpace, kColorStrokeFillPanelWidgetId, kColorPickerPrefix + 39)
DECLARE_PMID(kWidgetIDSpace, kGradStopColorPanelWidgetId, kColorPickerPrefix + 40)
DECLARE_PMID(kWidgetIDSpace, kGamutPanelWidgetId, kColorPickerPrefix + 41)
DECLARE_PMID(kWidgetIDSpace, kLastColorPanelWidgetId, kColorPickerPrefix + 42)

DECLARE_PMID(kWidgetIDSpace, kRedTextWidgetId, kColorPickerPrefix + 43)
DECLARE_PMID(kWidgetIDSpace, kGreenTextWidgetId, kColorPickerPrefix + 44)
DECLARE_PMID(kWidgetIDSpace, kBlueTextWidgetId, kColorPickerPrefix + 45)

DECLARE_PMID(kWidgetIDSpace, kCyanTextWidgetId, kColorPickerPrefix + 46)
DECLARE_PMID(kWidgetIDSpace, kMagentaTextWidgetId, kColorPickerPrefix + 47)
DECLARE_PMID(kWidgetIDSpace, kYellowTextWidgetId, kColorPickerPrefix + 48)
DECLARE_PMID(kWidgetIDSpace, kBlackTextWidgetId, kColorPickerPrefix + 49)

DECLARE_PMID(kWidgetIDSpace, kCyanPercentTextWidgetId, kColorPickerPrefix + 50)
DECLARE_PMID(kWidgetIDSpace, kMagentaPercentTextWidgetId, kColorPickerPrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kYellowPercentTextWidgetId, kColorPickerPrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kBlackPercentTextWidgetId, kColorPickerPrefix + 53)

DECLARE_PMID(kWidgetIDSpace, kLabLTextWidgetId, kColorPickerPrefix + 54)
DECLARE_PMID(kWidgetIDSpace, kLabATextWidgetId, kColorPickerPrefix + 55)
DECLARE_PMID(kWidgetIDSpace, kLabBTextWidgetId, kColorPickerPrefix + 56)

DECLARE_PMID(kWidgetIDSpace, kColorPickerParentWidgetId, kColorPickerPrefix + 57)
DECLARE_PMID(kWidgetIDSpace, kColorDummyWidgetId, kColorPickerPrefix + 58)
DECLARE_PMID(kWidgetIDSpace, kColorDummy2WidgetId, kColorPickerPrefix + 59)
DECLARE_PMID(kWidgetIDSpace, kColorDummy3WidgetId, kColorPickerPrefix + 60)
DECLARE_PMID(kWidgetIDSpace, kColorDummy4WidgetId, kColorPickerPrefix + 61)

DECLARE_PMID(kWidgetIDSpace, kRgbColorProxyWidgetId, kColorPickerPrefix + 62)
DECLARE_PMID(kWidgetIDSpace, kCmykColorProxyWidgetId, kColorPickerPrefix + 63)
DECLARE_PMID(kWidgetIDSpace, kLabColorProxyWidgetId, kColorPickerPrefix + 64)

DECLARE_PMID(kWidgetIDSpace, kREditTextWidgetId, kColorPickerPrefix + 65)
DECLARE_PMID(kWidgetIDSpace, kGEditTextWidgetId, kColorPickerPrefix + 66)
DECLARE_PMID(kWidgetIDSpace, kBEditTextWidgetId, kColorPickerPrefix + 67)

DECLARE_PMID(kWidgetIDSpace, kCEditTextWidgetId, kColorPickerPrefix + 68)
DECLARE_PMID(kWidgetIDSpace, kMEditTextWidgetId, kColorPickerPrefix + 69)
DECLARE_PMID(kWidgetIDSpace, kYEditTextWidgetId, kColorPickerPrefix + 70)
DECLARE_PMID(kWidgetIDSpace, kKEditTextWidgetId, kColorPickerPrefix + 71)

DECLARE_PMID(kWidgetIDSpace, kCPerEditTextWidgetId, kColorPickerPrefix + 72)
DECLARE_PMID(kWidgetIDSpace, kMPerEditTextWidgetId, kColorPickerPrefix + 73)
DECLARE_PMID(kWidgetIDSpace, kYPerEditTextWidgetId, kColorPickerPrefix + 74)
DECLARE_PMID(kWidgetIDSpace, kBPerEditTextWidgetId, kColorPickerPrefix + 75)

DECLARE_PMID(kWidgetIDSpace, kLabLEditTextWidgetId, kColorPickerPrefix + 76)
DECLARE_PMID(kWidgetIDSpace, kLabAEditTextWidgetId, kColorPickerPrefix + 77)
DECLARE_PMID(kWidgetIDSpace, kLabBEditTextWidgetId, kColorPickerPrefix + 78)
DECLARE_PMID(kWidgetIDSpace, kTintPerEditTextWidgetId, kColorPickerPrefix + 79)

//gap
DECLARE_PMID(kWidgetIDSpace, kTintEditTextWidgetId, kColorPickerPrefix + 81)

DECLARE_PMID(kWidgetIDSpace, kNChannelPickerWidgetID, kColorPickerPrefix + 82)
DECLARE_PMID(kWidgetIDSpace, kNChannelColorProxyWidgetID, kColorPickerPrefix + 83)
DECLARE_PMID(kWidgetIDSpace, kNChannelTreeViewWidgetID, kColorPickerPrefix + 84)
DECLARE_PMID(kWidgetIDSpace, kNChannelInkListElementWidgetID, kColorPickerPrefix + 85)
DECLARE_PMID(kWidgetIDSpace, kInkNameWidgetID, kColorPickerPrefix + 86)
DECLARE_PMID(kWidgetIDSpace, kInkItemTintSliderPanelWidgetID, kColorPickerPrefix + 87)
DECLARE_PMID(kWidgetIDSpace, kInkItemTintSliderWidgetID, kColorPickerPrefix + 88)
DECLARE_PMID(kWidgetIDSpace, kInkItemTintEditBoxWidgetID, kColorPickerPrefix + 89)
DECLARE_PMID(kWidgetIDSpace, kInkItemPercentTextWidgetID, kColorPickerPrefix + 90)
DECLARE_PMID(kWidgetIDSpace, kInkItemColorProxyWidgetID, kColorPickerPrefix + 91)

// Common Color Picker
DECLARE_PMID(kWidgetIDSpace, kCommonColorPickerDialogWidgetID, kColorPickerPrefix + 92)
DECLARE_PMID(kWidgetIDSpace, kSpaceWidgetID, kColorPickerPrefix + 93)

DECLARE_PMID(kWidgetIDSpace, kRGB_R_RadioButtonWidgetID, kColorPickerPrefix + 94)
DECLARE_PMID(kWidgetIDSpace, kRGB_G_RadioButtonWidgetID, kColorPickerPrefix + 95)
DECLARE_PMID(kWidgetIDSpace, kRGB_B_RadioButtonWidgetID, kColorPickerPrefix + 96)
DECLARE_PMID(kWidgetIDSpace, kLAB_L_RadioButtonWidgetID, kColorPickerPrefix + 97)
DECLARE_PMID(kWidgetIDSpace, kLAB_A_RadioButtonWidgetID, kColorPickerPrefix + 98)
DECLARE_PMID(kWidgetIDSpace, kLAB_B_RadioButtonWidgetID, kColorPickerPrefix + 99)

DECLARE_PMID(kWidgetIDSpace, kRGB_R_EditBoxWidgetId, kColorPickerPrefix + 100)
DECLARE_PMID(kWidgetIDSpace, kRGB_G_EditBoxWidgetId, kColorPickerPrefix + 101)
DECLARE_PMID(kWidgetIDSpace, kRGB_B_EditBoxWidgetId, kColorPickerPrefix + 102)
DECLARE_PMID(kWidgetIDSpace, kLAB_L_EditBoxWidgetId, kColorPickerPrefix + 103)
DECLARE_PMID(kWidgetIDSpace, kLAB_A_EditBoxWidgetId, kColorPickerPrefix + 104)
DECLARE_PMID(kWidgetIDSpace, kLAB_B_EditBoxWidgetId, kColorPickerPrefix + 105)
DECLARE_PMID(kWidgetIDSpace, kCMYK_C_EditBoxWidgetId, kColorPickerPrefix + 106)
DECLARE_PMID(kWidgetIDSpace, kCMYK_M_EditBoxWidgetId, kColorPickerPrefix + 107)
DECLARE_PMID(kWidgetIDSpace, kCMYK_Y_EditBoxWidgetId, kColorPickerPrefix + 108)
DECLARE_PMID(kWidgetIDSpace, kCMYK_K_EditBoxWidgetId, kColorPickerPrefix + 109)

DECLARE_PMID(kWidgetIDSpace, kCommonColorFieldGroupColumnWidgetID, kColorPickerPrefix + 110)
DECLARE_PMID(kWidgetIDSpace, kCommonColorFieldWidgetID, kColorPickerPrefix + 111)

DECLARE_PMID(kWidgetIDSpace, kColorSliderGroupColumnWidgetID, kColorPickerPrefix + 112)
DECLARE_PMID(kWidgetIDSpace, kCommonColorSliderWidgetID, kColorPickerPrefix + 113)

DECLARE_PMID(kWidgetIDSpace, kColorProxyGroupColumnWidgetID, kColorPickerPrefix + 114)
DECLARE_PMID(kWidgetIDSpace, kCCP_ProxyPanelWidgetID, kColorPickerPrefix + 115)
DECLARE_PMID(kWidgetIDSpace, kCCP_ProxyWidgetId, kColorPickerPrefix + 116)
DECLARE_PMID(kWidgetIDSpace, kRGB_InfoWidgetID, kColorPickerPrefix + 117)
DECLARE_PMID(kWidgetIDSpace, kRGB_GroupWidgetID, kColorPickerPrefix + 118)
DECLARE_PMID(kWidgetIDSpace, kRGB_EditBoxesWidgetID, kColorPickerPrefix + 119)

DECLARE_PMID(kWidgetIDSpace, kButtonColumnWidgetID, kColorPickerPrefix + 120)
DECLARE_PMID(kWidgetIDSpace, kButtonGroupWidgetID, kColorPickerPrefix + 121)
DECLARE_PMID(kWidgetIDSpace, kAddToSwatchesWidgetID, kColorPickerPrefix + 122)

DECLARE_PMID(kWidgetIDSpace, kCMYKInfoWidgetID, kColorPickerPrefix + 123)
DECLARE_PMID(kWidgetIDSpace, kCMYK_C_GroupWidgetID, kColorPickerPrefix + 124)
DECLARE_PMID(kWidgetIDSpace, kCMYK_C_LabelWidgetId, kColorPickerPrefix + 125)
DECLARE_PMID(kWidgetIDSpace, kCMYK_M_GroupWidgetID, kColorPickerPrefix + 126)
DECLARE_PMID(kWidgetIDSpace, kCMYK_M_LabelWidgetId, kColorPickerPrefix + 127)
DECLARE_PMID(kWidgetIDSpace, kCMYK_Y_GroupWidgetID, kColorPickerPrefix + 128)
DECLARE_PMID(kWidgetIDSpace, kCMYK_Y_LabelWidgetId, kColorPickerPrefix + 129)
DECLARE_PMID(kWidgetIDSpace, kCMYK_K_GroupWidgetID, kColorPickerPrefix + 130)
DECLARE_PMID(kWidgetIDSpace, kCMYK_K_LabelWidgetId, kColorPickerPrefix + 131)
DECLARE_PMID(kWidgetIDSpace, kPercentWidgetID, kColorPickerPrefix + 132)
DECLARE_PMID(kWidgetIDSpace, kColorSpaceViewStrWidgetID, kColorPickerPrefix + 133)


DECLARE_PMID(kWidgetIDSpace, kColorPickerGenericPanel1WidgetID, kColorPickerPrefix + 134)
DECLARE_PMID(kWidgetIDSpace, kControlStripFillDropDownWidgetId, kColorPickerPrefix + 135)
DECLARE_PMID(kWidgetIDSpace, kControlStripStrokeDropDownWidgetId, kColorPickerPrefix + 136)

DECLARE_PMID(kWidgetIDSpace, kHexColorEditPanelWidgetID,		kColorPickerPrefix + 137)
DECLARE_PMID(kWidgetIDSpace, kHexColorValueEditWidgetID,		kColorPickerPrefix + 138)
DECLARE_PMID(kWidgetIDSpace, kColorHSBSelectorWidgetId, kColorPickerPrefix + 139)
DECLARE_PMID(kWidgetIDSpace, kRGBColorEditorWidgetId, kColorPickerPrefix + 140)
DECLARE_PMID(kWidgetIDSpace, kCMYKColorEditorWidgetId, kColorPickerPrefix + 141)
DECLARE_PMID(kWidgetIDSpace, kTouchSpectrumWidgetId, kColorPickerPrefix + 142)
DECLARE_PMID(kWidgetIDSpace, kColorPickerTouchPanelWidgetId, kColorPickerPrefix + 143)
DECLARE_PMID(kWidgetIDSpace, kColorPickerTouchWidgetID, kColorPickerPrefix + 144)
//DECLARE_PMID(kWidgetIDSpace, kColorPickerSwitcherWidgetID, kColorPickerPrefix + 145)
DECLARE_PMID(kWidgetIDSpace, kCmykColorTouchPickerWidgetId, kColorPickerPrefix + 145)
DECLARE_PMID(kWidgetIDSpace, kRgbColorTouchPickerWidgetId, kColorPickerPrefix + 146)
DECLARE_PMID(kWidgetIDSpace, kColorPickerSwitcherWidgetID, kColorPickerPrefix + 147)
DECLARE_PMID(kWidgetIDSpace, kHsbColorTouchPickerWidgetId, kColorPickerPrefix + 148)
DECLARE_PMID(kWidgetIDSpace, kColorModeWidgetId, kColorPickerPrefix + 149)
DECLARE_PMID(kWidgetIDSpace, kAddToSwatchWidgetId, kColorPickerPrefix + 150)
DECLARE_PMID(kWidgetIDSpace, kRecentTextWidgetId, kColorPickerPrefix + 151)
DECLARE_PMID(kWidgetIDSpace, kRecentColorSectionWidgetId, kColorPickerPrefix + 153)
DECLARE_PMID(kWidgetIDSpace, kColorPickerTouchViewWidgetId, kColorPickerPrefix + 154)
DECLARE_PMID(kWidgetIDSpace, kToggleWidgetId, kColorPickerPrefix + 155)
DECLARE_PMID(kWidgetIDSpace, kColorPickerTouchSwatchViewWidgetId, kColorPickerPrefix + 156)
DECLARE_PMID(kWidgetIDSpace, kSwatchTouchViewWidgetId, kColorPickerPrefix + 157)
DECLARE_PMID(kWidgetIDSpace, kSwatchGridSwitchWidgetId, kColorPickerPrefix + 158)
DECLARE_PMID(kWidgetIDSpace, kSwatchListSwitchWidgetId, kColorPickerPrefix + 159)
DECLARE_PMID(kWidgetIDSpace, kSwatchViewModeClusterWidgetId, kColorPickerPrefix + 160)
DECLARE_PMID(kWidgetIDSpace, kNoneSwatchWidgetId, kColorPickerPrefix + 161)
DECLARE_PMID(kWidgetIDSpace, kWhiteSwatchWidgetId, kColorPickerPrefix + 162)
DECLARE_PMID(kWidgetIDSpace, kBlackSwatchWidgetId, kColorPickerPrefix + 163)
DECLARE_PMID(kWidgetIDSpace, kFillLabelWidgetID, kColorPickerPrefix + 164)
DECLARE_PMID(kWidgetIDSpace, kStrokeLabelWidgetID, kColorPickerPrefix + 165)
DECLARE_PMID(kWidgetIDSpace, kColorPopUpScalingWidgetID, kColorPickerPrefix + 166)
DECLARE_PMID(kWidgetIDSpace, kColorPopupButtonBarWidgetID, kColorPickerPrefix + 167)
DECLARE_PMID(kWidgetIDSpace, kColorPopupContainerWidgetID, kColorPickerPrefix + 168)
DECLARE_PMID(kWidgetIDSpace, kLayoutTextSwitchDropDownWidgetID, kColorPickerPrefix + 169)
DECLARE_PMID(kWidgetIDSpace, kTargetLabelWidgetID, kColorPickerPrefix + 170)
DECLARE_PMID(kWidgetIDSpace, kColorPopupMenuButtonWidgetID, kColorPickerPrefix + 171)
DECLARE_PMID(kWidgetIDSpace, kStrokeFillTintPanelWidgetID, kColorPickerPrefix + 172)
DECLARE_PMID(kWidgetIDSpace, kAppearancePanelColorPopupWidgetID, kColorPickerPrefix + 173)
DECLARE_PMID(kWidgetIDSpace, kGradientTargetLabelWidgetID, kColorPickerPrefix + 174)

DECLARE_PMID(kWidgetIDSpace, kHSB_H_RadioButtonWidgetID, kColorPickerPrefix + 175)
DECLARE_PMID(kWidgetIDSpace, kHSB_S_RadioButtonWidgetID, kColorPickerPrefix + 176)
DECLARE_PMID(kWidgetIDSpace, kHSB_B_RadioButtonWidgetID, kColorPickerPrefix + 177)

DECLARE_PMID(kWidgetIDSpace, kHSB_H_EditBoxWidgetId, kColorPickerPrefix + 178)
DECLARE_PMID(kWidgetIDSpace, kHSB_S_EditBoxWidgetId, kColorPickerPrefix + 179)
DECLARE_PMID(kWidgetIDSpace, kHSB_B_EditBoxWidgetId, kColorPickerPrefix + 180)

DECLARE_PMID(kWidgetIDSpace, kHSB_H_GroupWidgetID, kColorPickerPrefix + 181)
DECLARE_PMID(kWidgetIDSpace, kHSB_S_GroupWidgetID, kColorPickerPrefix + 182)
DECLARE_PMID(kWidgetIDSpace, kHSB_B_GroupWidgetID, kColorPickerPrefix + 183)

DECLARE_PMID(kWidgetIDSpace, kRGB_R_GroupWidgetID, kColorPickerPrefix + 184)
DECLARE_PMID(kWidgetIDSpace, kRGB_G_GroupWidgetID, kColorPickerPrefix + 185)
DECLARE_PMID(kWidgetIDSpace, kRGB_B_GroupWidgetID, kColorPickerPrefix + 186)

DECLARE_PMID(kWidgetIDSpace, kHsbColorPickerWidgetId, kColorPickerPrefix + 187)

DECLARE_PMID(kWidgetIDSpace, kHsbColorProxyWidgetId, kColorPickerPrefix + 188)
DECLARE_PMID(kWidgetIDSpace, kHEditTextWidgetId, kColorPickerPrefix + 189)
DECLARE_PMID(kWidgetIDSpace, kSEditTextWidgetId, kColorPickerPrefix + 190)
DECLARE_PMID(kWidgetIDSpace, kHBEditTextWidgetId, kColorPickerPrefix + 191)

DECLARE_PMID(kWidgetIDSpace, kHueEditBoxWidgetId, kColorPickerPrefix + 192)
DECLARE_PMID(kWidgetIDSpace, kSatEditBoxWidgetId, kColorPickerPrefix + 193)
DECLARE_PMID(kWidgetIDSpace, kBriEditBoxWidgetId, kColorPickerPrefix + 194)

DECLARE_PMID(kWidgetIDSpace, kHueSliderWidgetId, kColorPickerPrefix + 195)
DECLARE_PMID(kWidgetIDSpace, kSatSliderWidgetId, kColorPickerPrefix + 196)
DECLARE_PMID(kWidgetIDSpace, kBriSliderWidgetId, kColorPickerPrefix + 197)

DECLARE_PMID(kWidgetIDSpace, kHueTextWidgetId, kColorPickerPrefix + 198)
DECLARE_PMID(kWidgetIDSpace, kSatTextWidgetId, kColorPickerPrefix + 199)
DECLARE_PMID(kWidgetIDSpace, kBriTextWidgetId, kColorPickerPrefix + 200)
DECLARE_PMID(kWidgetIDSpace, kLAB_L_GroupWidgetID, kColorPickerPrefix + 201)
DECLARE_PMID(kWidgetIDSpace, kLAB_A_GroupWidgetID, kColorPickerPrefix + 202)
DECLARE_PMID(kWidgetIDSpace, kLAB_B_GroupWidgetID, kColorPickerPrefix + 203)
DECLARE_PMID(kWidgetIDSpace, kLAB_GroupWidgetID, kColorPickerPrefix + 204)

// <Message ID>
// ---------------------------------------------------------------
//  Messages
// ---------------------------------------------------------------
DECLARE_PMID(kMessageIDSpace, kAllSlidersChangedExternallyMessage, kColorPickerPrefix + 1)
DECLARE_PMID(kMessageIDSpace, kNChannelItemChangedMessage, kColorPickerPrefix + 2)
DECLARE_PMID(kMessageIDSpace, kNChannelItemAddedMessage, kColorPickerPrefix + 3)
DECLARE_PMID(kMessageIDSpace, kNChannelItemRemovedMessage, kColorPickerPrefix + 4)

// <Service ID>
// ---------------------------------------------------------------
//  Services
// ---------------------------------------------------------------
DECLARE_PMID(kServiceIDSpace, kColorPickerPanelService, kColorPickerPrefix + 1)
DECLARE_PMID(kServiceIDSpace, kColorPickerOptionPanelService, kColorPickerPrefix + 2)
DECLARE_PMID(kServiceIDSpace, kColorPickerTouchPanelService, kColorPickerPrefix + 3)
DECLARE_PMID(kServiceIDSpace, kColorPickerTouchSwatchPanelService, kColorPickerPrefix + 4)
DECLARE_PMID(kServiceIDSpace, kReallyBogusPanelService, kColorPickerPrefix + 5)
DECLARE_PMID(kServiceIDSpace, kPropertiesPanelColorPopupService, kColorPickerPrefix + 6)


// <Action ID>
DECLARE_PMID(kActionIDSpace, kPickerPanelOptionsActionID, kColorPickerPrefix + 1)
DECLARE_PMID(kActionIDSpace, kPickerPanelOptionsSepActionID, kColorPickerPrefix + 2)
DECLARE_PMID(kActionIDSpace, kColorPickerPanelActionID, kColorPickerPrefix + 3)
DECLARE_PMID(kActionIDSpace, kFirstColorSpaceActionID, kColorPickerPrefix + 4)
//gap - reserved for dynamic menu actions
DECLARE_PMID(kActionIDSpace, kPickerPanelAddSwatchActionID, kColorPickerPrefix + 23)
DECLARE_PMID(kActionIDSpace, kLastColorSpaceActionID, kColorPickerPrefix + 24)
DECLARE_PMID(kActionIDSpace, kPickerPanelOptionsSep2ActionID, kColorPickerPrefix + 25)

//Action ID/s for Gradient option flyout in color popup. 
DECLARE_PMID(kActionIDSpace, kGradientOptionFirstColorSpaceActionID, kColorPickerPrefix + 26)
//gap - reserved for dynamic menu actions

#endif
