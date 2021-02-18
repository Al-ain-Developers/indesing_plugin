//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/GradientUIID.h $
//  
//  Owner: Thanh Nguyen
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

#ifndef __GradientUIID__
#define __GradientUIID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kGradientUIPrefix RezLong(0x5e00)	// define in AdobePrefix.h

// <Start IDC>
// PluginID
#define kGradientPanelPluginName 		"Gradient Panel"
DECLARE_PMID(kPlugInIDSpace, kGradientPanelPluginID, kGradientUIPrefix + 1)

// <Class ID>
// ---------------------------------------------------------------
//  Class IDs
// ---------------------------------------------------------------
//DECLARE_PMID(kClassIDSpace, kGradientUIRegisterBoss, kGradientUIPrefix + 1)
DECLARE_PMID(kClassIDSpace, kGradientPanelWidgetBoss, kGradientUIPrefix + 2)
DECLARE_PMID(kClassIDSpace, kGradientSliderWidgetBoss, kGradientUIPrefix + 3)

DECLARE_PMID(kClassIDSpace, kGradPanelSolidBlockBoss, kGradientUIPrefix + 5)

DECLARE_PMID(kClassIDSpace, kGradientNameEditBoxWidgetBoss, kGradientUIPrefix + 6)
DECLARE_PMID(kClassIDSpace, kGradientColorSpacePopupWidgetBoss, kGradientUIPrefix + 7)
DECLARE_PMID(kClassIDSpace, kGradientTypePopupWidgetBoss, kGradientUIPrefix + 8)
DECLARE_PMID(kClassIDSpace, kGradientOptionDialogBoss, kGradientUIPrefix + 9)
DECLARE_PMID(kClassIDSpace, kGradStopColorPopupWidgetBoss, kGradientUIPrefix + 11)
DECLARE_PMID(kClassIDSpace, kGradientSliderTrackerBoss, kGradientUIPrefix + 12)
DECLARE_PMID(kClassIDSpace, kGradPanelTrackersRegisterBoss, kGradientUIPrefix + 13)

DECLARE_PMID(kClassIDSpace, kMoveThumbCmdBoss, kGradientUIPrefix + 15)
DECLARE_PMID(kClassIDSpace, kGradientProxyWidgetBoss, kGradientUIPrefix + 16)
DECLARE_PMID(kClassIDSpace, kGradAngleEditBoxWidgetBoss, kGradientUIPrefix + 17)
DECLARE_PMID(kClassIDSpace, kGradLocationEditBoxWidgetBoss, kGradientUIPrefix + 18)
//gap
DECLARE_PMID(kClassIDSpace, kGradPanelMenuComponentBoss, kGradientUIPrefix + 20)
DECLARE_PMID(kClassIDSpace, kSwatchesOptionListPanelBoss, kGradientUIPrefix + 21)
DECLARE_PMID(kClassIDSpace, kSwatchesOptionPanelWidgetBoss, kGradientUIPrefix + 22)

DECLARE_PMID(kClassIDSpace, kUpdateAngleMessage, kGradientUIPrefix + 23)
DECLARE_PMID(kClassIDSpace, kGradReverseWidgetBoss, kGradientUIPrefix + 24)
DECLARE_PMID(kClassIDSpace, kGradientOptionPopupBoss, kGradientUIPrefix + 25)

// <Interface ID>
// ---------------------------------------------------------------
// Interface IDs
// ---------------------------------------------------------------
DECLARE_PMID(kInterfaceIDSpace, IID_IGRADIENTCONTROLOBSERVER, (kGradientUIPrefix + 1))
DECLARE_PMID(kInterfaceIDSpace, IID_IGRADIENTSLIDERCONTROLDATA, (kGradientUIPrefix + 2))
DECLARE_PMID(kInterfaceIDSpace, IID_IGRADIENTWIDGETPROVIDER, (kGradientUIPrefix + 3))
//DECLARE_PMID(kInterfaceIDSpace, IID_GRADIENTMETACONVERTER, (kGradientUIPrefix + 4))
DECLARE_PMID(kInterfaceIDSpace, IID_IBOOLVALUE, (kGradientUIPrefix + 5))
DECLARE_PMID(kInterfaceIDSpace, IID_IGRADIENTSLIDEROBSERVER, (kGradientUIPrefix + 6))
DECLARE_PMID(kInterfaceIDSpace, IID_IGRADOPTIONPICKEROBSERVER, (kGradientUIPrefix + 7))
DECLARE_PMID(kInterfaceIDSpace, IID_ISYNGRADOPTIONPICKER, (kGradientUIPrefix + 8) )

// TTN_DEBUB...07.30.98

//DECLARE_PMID(kInterfaceIDSpace, IID_IGRADIENTPANELSELECTIONOBSERVER, (kGradientUIPrefix + 12))

//DECLARE_PMID(kInterfaceIDSpace, IID_IGRADPANELTEXTSELECTIONOBSERVER, (kGradientUIPrefix + 14))
//DECLARE_PMID(kInterfaceIDSpace, IID_IGRADIENTANGLECHANGEHANDLER, (kGradientUIPrefix + 15))

DECLARE_PMID(kInterfaceIDSpace, IID_IGRADOPTIONDIALOGOBSERVER, (kGradientUIPrefix + 16))
DECLARE_PMID(kInterfaceIDSpace, IID_IGRADOPTIONTYPEOBSERVER, (kGradientUIPrefix + 18))
DECLARE_PMID(kInterfaceIDSpace, IID_IGRADIENTPANELOPTIONS, (kGradientUIPrefix + 19))
DECLARE_PMID(kInterfaceIDSpace, IID_IGRADANGLEVIEWOBSERVER, (kGradientUIPrefix + 20))
DECLARE_PMID(kInterfaceIDSpace, IID_IGRADFILLGFXSTATEDATA, (kGradientUIPrefix + 21))
//DECLARE_PMID(kInterfaceIDSpace, IID_IUPDATEANGLEMESSAGE, (kGradientUIPrefix + 22))
//DECLARE_PMID(kInterfaceIDSpace, IID_IGRADIENTINVERTPREFERENCE, (kGradientUIPrefix + 23))
DECLARE_PMID(kInterfaceIDSpace, IID_GRADREVERSEOBSERVER, (kGradientUIPrefix + 24))


// <Implementation ID>
// ---------------------------------------------------------------
//  Implementation IDs
// ---------------------------------------------------------------
// gap
DECLARE_PMID(kImplementationIDSpace, kGradientSliderViewImpl, kGradientUIPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kCGradientSliderControlDataImpl, kGradientUIPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kGradientSliderEHImpl, kGradientUIPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kGradientMetaDataObserverImpl, kGradientUIPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kGradientSliderStateObserverImpl, kGradientUIPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kGradientSliderObserverImpl, kGradientUIPrefix + 8)

DECLARE_PMID(kImplementationIDSpace, kGradPanelMetaDataObserverImpl, kGradientUIPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kGradPanelSetSolidBlockCmdImpl, kGradientUIPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kGradientDialogControllerImpl, kGradientUIPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kGradientPanelDataImpl, kGradientUIPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kGradientDialogCreatorImpl, kGradientUIPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kGradStopColorPopupObserverImpl, kGradientUIPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kGradOptionDialogObserverImpl, kGradientUIPrefix + 17)

DECLARE_PMID(kImplementationIDSpace, kGradientOptionPanelObserverImpl, kGradientUIPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kGradOptionPickerObserverImpl, kGradientUIPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kMessageBoolDataImpl, kGradientUIPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kGradientSliderTrackerImpl, kGradientUIPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kGradientSliderTrackerEHImpl, kGradientUIPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kGradPanelTrackersRegisterImpl, kGradientUIPrefix + 24)

DECLARE_PMID(kImplementationIDSpace, kMoveThumbCmdImpl, kGradientUIPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kGradientProxyViewImpl, kGradientUIPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kGradientProxyEHImpl, kGradientUIPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kGradTypeSelectionObserverImpl, kGradientUIPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kGradAngleEditBoxObserverImpl, kGradientUIPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kGradLocationEditBoxObserverImpl, kGradientUIPrefix + 32)
// gap
DECLARE_PMID(kImplementationIDSpace, kGradientPanelHelperImpl, kGradientUIPrefix + 34)

DECLARE_PMID(kImplementationIDSpace, kGradientProxyDDSourceImpl, kGradientUIPrefix + 35)

// TTN_DEBUG... 07.30.98

//DECLARE_PMID(kImplementationIDSpace, kGradPanelSelectionObserverImpl, kGradientUIPrefix + 36)

//DECLARE_PMID(kImplementationIDSpace, kGradTextSelectionObserverImpl, kGradientUIPrefix + 38)
//DECLARE_PMID(kImplementationIDSpace, kGradAngleChangeHandlerImpl, kGradientUIPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kGradOptionDialogObserverImp, kGradientUIPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kSwatchesGradStopObserverImpl, kGradientUIPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kGradOptionTypeObserverImpl, kGradientUIPrefix + 42)
// panel menu
DECLARE_PMID(kImplementationIDSpace, kGradPanelMenuComponentImpl, kGradientUIPrefix + 43)


//DECLARE_PMID(kImplementationIDSpace, kGradGfxStateDefnObserverImpl, kGradientUIPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kGradAngleViewObserverImpl, kGradientUIPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kGradFillGfxStateObserverImpl, kGradientUIPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kGradFillGraphicStateDataImpl, kGradientUIPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kGradReverseObserverImpl, kGradientUIPrefix + 49)

DECLARE_PMID(kImplementationIDSpace, kGradientSliderDDTargetImpl, kGradientUIPrefix + 50)

//gap

// <Widget ID>
// ---------------------------------------------------------------
//  Widget IDs
// ---------------------------------------------------------------
DECLARE_PMID(kWidgetIDSpace, kGradientPanelWidgetId, kGradientUIPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kDefaultGradientWidgetId, kGradientUIPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kGradientSliderWidgetId, kGradientUIPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kGradientOptionPanelWidgetId, kGradientUIPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kGradientTypeStaticWidgetId, kGradientUIPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kGradientTypePopupWidgetId, kGradientUIPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kStopColorPopupWidgetId, kGradientUIPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kDefaultGradientOptionWidgetId, kGradientUIPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kDefaultColorListWidgetId, kGradientUIPrefix + 9)

DECLARE_PMID(kWidgetIDSpace, kGradStopColorPopupWidgetId, kGradientUIPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kDefaultGradColorPickerWidgetId, kGradientUIPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kGradientStopStaticWidgetId, kGradientUIPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kDefaultGradSliderWidgetId, kGradientUIPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kDefaultGradWidgetId, kGradientUIPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kGradientProxyWidgetId, kGradientUIPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kGradAngleEditBoxWidgetId, kGradientUIPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kGradientAngleStaticWidgetId, kGradientUIPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kGradientPercentageStaticWidgetId, kGradientUIPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kGradientLocationStaticWidgetId, kGradientUIPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kGradLocationEditBoxWidgetId, kGradientUIPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kSwatchesOptionPanelWidgetId, kGradientUIPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kGradientAngleSignStaticWidgetId, kGradientUIPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kGradStopColorPopupGroupWidgetId, kGradientUIPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kGradientRampStaticWidgetId, kGradientUIPrefix + 24)

DECLARE_PMID(kWidgetIDSpace, kGradientControlWidgetId, kGradientUIPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kSpacerGradientWidgetId, kGradientUIPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kGradReverseWidgetId, kGradientUIPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kGradientOptionPopupWidgetId, kGradientUIPrefix + 28)

// <Service ID>
// ---------------------------------------------------------------
// ----- Service IDs -----
// ---------------------------------------------------------------
DECLARE_PMID(kServiceIDSpace, kGradientOptionDialogService, kGradientUIPrefix + 1)
DECLARE_PMID(kServiceIDSpace, kGradientColorOptionPanelService, kGradientUIPrefix + 2)
DECLARE_PMID(kServiceIDSpace, kGradientColorOptionPopupService, kGradientUIPrefix + 3)

// <Action ID>
DECLARE_PMID(kActionIDSpace, kShowGradOptionsActionID, kGradientUIPrefix + 1)
DECLARE_PMID(kActionIDSpace, kGradientPanelActionID, kGradientUIPrefix + 2)

#endif // __GradientUIID__

