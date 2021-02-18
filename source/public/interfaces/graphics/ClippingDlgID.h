//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ClippingDlgID.h $
//  
//  Owner: Dave Stephens
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

#ifndef __ClippingDlgID__
#define __ClippingDlgID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kClippingDlgPrefix	 RezLong(0x8800)

// Conversion
// For pub conversion constants see ClippingDlgConversionID.h

// <Start IDC>
// PluginID
#define kClippingDlgPluginName 				"Clipping Path Dialog"
DECLARE_PMID(kPlugInIDSpace, kClippingDlgPluginID, kClippingDlgPrefix + 1)

// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kClippingDlgBoss, kClippingDlgPrefix + 2)
//gap
DECLARE_PMID(kClassIDSpace, kThresholdSliderWidgetBoss, kClippingDlgPrefix + 4)
DECLARE_PMID(kClassIDSpace, kThresholdEditBoxWidgetBoss, kClippingDlgPrefix + 5)
DECLARE_PMID(kClassIDSpace, kToleranceSliderWidgetBoss, kClippingDlgPrefix + 6)
DECLARE_PMID(kClassIDSpace, kToleranceEditBoxWidgetBoss, kClippingDlgPrefix + 7)
DECLARE_PMID(kClassIDSpace, kThresholdSliderTrackerBoss, kClippingDlgPrefix + 8)
DECLARE_PMID(kClassIDSpace, kClippingTrackersRegisterBoss, kClippingDlgPrefix + 9)
DECLARE_PMID(kClassIDSpace, kClipButtonObserverWidgetBoss, kClippingDlgPrefix + 10)
// gap
DECLARE_PMID(kClassIDSpace, kClippingDlgWidgetBoss, kClippingDlgPrefix + 12)
DECLARE_PMID(kClassIDSpace, kClipCreatorID, kClippingDlgPrefix + 13)
DECLARE_PMID(kClassIDSpace, kClippingMenuBoss, kClippingDlgPrefix + 14)

// <Implementation ID>
// Implementation IIDs
DECLARE_PMID(kImplementationIDSpace, kClippingDlgObserverImpl, kClippingDlgPrefix + 1)
//DECLARE_PMID(kImplementationIDSpace, kClippingDlgViewImpl, kClippingDlgPrefix + 2) //available
// gap
DECLARE_PMID(kImplementationIDSpace, kThresholdSliderTrackerImpl, kClippingDlgPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kThresholdSliderEHImpl, kClippingDlgPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kThresholdSliderViewImpl, kClippingDlgPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kThresholdEditBoxObserverImpl, kClippingDlgPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kThresholdSliderObserverImpl, kClippingDlgPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kToleranceEditBoxObserverImpl, kClippingDlgPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kToleranceSliderObserverImpl, kClippingDlgPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kClipButtonObserverImpl, kClippingDlgPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kClippingDlgTrackerEHImpl, kClippingDlgPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kClippingTrackersRegisterImpl, kClippingDlgPrefix + 13)
//DECLARE_PMID(kImplementationIDSpace, kToleranceSliderViewImpl, kClippingDlgPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kToleranceSliderEHImpl, kClippingDlgPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kClippingDlgControllerImpl, kClippingDlgPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kClippingPathMenuAction, kClippingDlgPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kClipSettingsImpl_Obsolete, kClippingDlgPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kDocumentClipSettingsImpl_Obsolete, kClippingDlgPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kSessionClipSettingsImpl_Obsolete, kClippingDlgPrefix + 23)

// <Widget ID>
// ---------------------------------------------------------------
//  Widget IDs
// ---------------------------------------------------------------
DECLARE_PMID(kWidgetIDSpace, kThresholdEditBoxWidgetId, kClippingDlgPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kThresholdSliderWidgetId, kClippingDlgPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kToleranceEditBoxWidgetId, kClippingDlgPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kToleranceSliderWidgetId, kClippingDlgPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kToleranceTitleWidgetId, kClippingDlgPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kThresholdTitleWidgetId, kClippingDlgPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kClippingDlgWidgetId, kClippingDlgPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kAllowHolesCheckBoxWidgetId, kClippingDlgPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kUseHighResCheckBoxWidgetId, kClippingDlgPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kInvertCheckBoxWidgetId, kClippingDlgPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kInsetFrameEditBoxWidgetId, kClippingDlgPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kInsetFrameTitleWidgetId, kClippingDlgPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kInfoPart1StaticTextBoxWidgetId, kClippingDlgPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kInfoPart2StaticTextBoxWidgetId, kClippingDlgPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kInfoPart3StaticTextBoxWidgetId, kClippingDlgPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kInfoFrameWidgetId, kClippingDlgPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kClipTypePopupWidgetId, kClippingDlgPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kClipTypeTitleWidgetId, kClippingDlgPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kRestrictToBoxCheckboxWidgetId, kClippingDlgPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kSubAlphaPopupWidgetId, kClippingDlgPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kSubAlphaTitleWidgetId, kClippingDlgPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kSubPathPopupWidgetId, kClippingDlgPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kSubPathTitleWidgetId, kClippingDlgPrefix + 23)

// <Interface ID>
// ---------------------------------------------------------------
// Interface IDs
// ---------------------------------------------------------------
DECLARE_PMID(kInterfaceIDSpace, IID_ITHRESHOLDCONTROLOBSERVER, kClippingDlgPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ICLIPSETTINGS, kClippingDlgPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETCLIPVALUESCMDDATA, kClippingDlgPrefix + 3)

// <Action ID>
DECLARE_PMID(kActionIDSpace, kClipPathActionID, kClippingDlgPrefix + 1)
DECLARE_PMID(kActionIDSpace, kClipToFrameActionID, kClippingDlgPrefix + 2)

// Don't show again warning IDs
#define kPhotoshopEPSClipPathWarning                          (kClippingDlgPrefix + 1)

#endif // __ClippingDlgID__
