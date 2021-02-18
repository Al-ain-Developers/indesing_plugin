//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ContentDropperToolID.h $
//  
//  Owner: Shikha Arora
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
//  Contains IDs used by EyeDropper tool plug-in
//  
//========================================================================================

#ifndef __ContentDropperToolID__
#define __ContentDropperToolID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"


#define kContentDropperToolPrefix	 RezLong(0x22400)

//TODO remove double macros
#define CONTENT_DROPPER_DEF_STRINGIZE(s) #s

#define kContentDropperStringPrefix	CONTENT_DROPPER_DEF_STRINGIZE(kContentDropperToolPrefix)

// <Start IDC>
// PluginID
#define kContentDropperToolPluginName 				"ContentDropperTool"
DECLARE_PMID(kPlugInIDSpace, kContentDropperToolPluginID, kContentDropperToolPrefix + 1)

// <Class ID>
DECLARE_PMID(kClassIDSpace, kContentDropperToolBoss, kContentDropperToolPrefix + 1)
DECLARE_PMID(kClassIDSpace, kContentDropperTrackerBoss, kContentDropperToolPrefix + 2)
DECLARE_PMID(kClassIDSpace, kContentDropperTrackerRegisterBoss, kContentDropperToolPrefix + 3)
DECLARE_PMID(kClassIDSpace, kContentDropperDropToolBoss, kContentDropperToolPrefix + 4)
DECLARE_PMID(kClassIDSpace, kContentDropperDropToolTrackerBoss, kContentDropperToolPrefix + 5)
DECLARE_PMID(kClassIDSpace, kContentDropperPITrackerBoss, kContentDropperToolPrefix + 6)
DECLARE_PMID(kClassIDSpace, kContentDropperRibbonWindowBoss, kContentDropperToolPrefix + 7)
DECLARE_PMID(kClassIDSpace, kContentDropperRibbonWidgetBoss, kContentDropperToolPrefix + 8)
DECLARE_PMID(kClassIDSpace, kRibbonOptionsPanelWidgetBoss, kContentDropperToolPrefix + 9)
DECLARE_PMID(kClassIDSpace, kContentDropperCheckBoxWidgetBoss, kContentDropperToolPrefix + 10)
DECLARE_PMID(kClassIDSpace, kContentDropperRibbonDialogBoss, kContentDropperToolPrefix + 11)
DECLARE_PMID(kClassIDSpace, kContentDropperAGMImageViewBoss, kContentDropperToolPrefix + 12)
DECLARE_PMID(kClassIDSpace, kRibbonThumbnailContainerWidgetBoss, kContentDropperToolPrefix + 13)
DECLARE_PMID(kClassIDSpace, kRibbonGripperViewBoss, kContentDropperToolPrefix + 14)
DECLARE_PMID(kClassIDSpace, kRibbonNavigationButtonWidgetBoss, kContentDropperToolPrefix + 15)
DECLARE_PMID(kClassIDSpace, kRibbonCloseButtonBoss, kContentDropperToolPrefix + 16)
DECLARE_PMID(kClassIDSpace, kRibbonThumbnailExpanderWidgetBoss, kContentDropperToolPrefix + 17)
//gap
DECLARE_PMID(kClassIDSpace, kRibbonNoItemCollectedTextWidgetBoss, kContentDropperToolPrefix + 19)
DECLARE_PMID(kClassIDSpace, kContentDropperToolStartupShutdownBoss, kContentDropperToolPrefix + 20)
DECLARE_PMID(kClassIDSpace, kContentDropperEditStyleMappingsWidgetBoss, kContentDropperToolPrefix + 21)
DECLARE_PMID(kClassIDSpace, kRibbonStaticTextWidgetBoss, kContentDropperToolPrefix + 22)
DECLARE_PMID(kClassIDSpace, kRibbonThumbnailCollapseWidgetBoss, kContentDropperToolPrefix + 23)
DECLARE_PMID(kClassIDSpace, kGrabPageRangeDialogBoss, kContentDropperToolPrefix + 24)
DECLARE_PMID(kClassIDSpace, kContentDropperToggleToolActionBoss, kContentDropperToolPrefix + 25)
DECLARE_PMID(kClassIDSpace, kRibbonToolSwitchButtonBoss, kContentDropperToolPrefix + 26)
DECLARE_PMID(kClassIDSpace, kContentDropperGroupButtonPanelBoss, kContentDropperToolPrefix + 27)

// <Implementation ID>
DECLARE_PMID(kImplementationIDSpace, kContentDropperToolPrivateUtilsImpl, kContentDropperToolPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kContentDropperToolImpl, kContentDropperToolPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kContentDropperTrackerImpl, kContentDropperToolPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kContentDropperTrackerRegisterImpl, kContentDropperToolPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kContentDropperToolCheckBoxObserverImpl, kContentDropperToolPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kContentDropperToolEventWatcherImpl, kContentDropperToolPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kContentDropperDropToolImpl, kContentDropperToolPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kPlaceFromContentDropperPlaceHeadImpl, kContentDropperToolPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kRibbonThumbnailExpanderObserverImpl, kContentDropperToolPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kContentDropperRibbonWindowImpl, kContentDropperToolPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kContentDropperRibbonControlViewImpl, kContentDropperToolPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kContentDropperRibbonDlgControllerImpl, kContentDropperToolPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kContentDropperRibbonDlgObserverImpl, kContentDropperToolPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kRibbonElementViewImpl, kContentDropperToolPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kRibbonTextLineBreakerImpl, kContentDropperToolPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kRibbonControllerImpl, kContentDropperToolPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kRibbonObserverImpl, kContentDropperToolPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kContentDropperCursorProviderImpl, kContentDropperToolPrefix + 18)
//gap
DECLARE_PMID(kImplementationIDSpace, kContentDropperAGMImageViewImpl, kContentDropperToolPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kRibbonPreviewImageDataImpl, kContentDropperToolPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kRibbonDialogEventHandlerImpl, kContentDropperToolPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kRibbonThumbnailContainerViewImpl, kContentDropperToolPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kRibbonMgrImpl, kContentDropperToolPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kRibbonGripperViewImpl, kContentDropperToolPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kRibbonGripperEHImpl, kContentDropperToolPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kRibbonThumbnailExpanderViewImpl, kContentDropperToolPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kRibbonNavigationButtonObserverImpl, kContentDropperToolPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kRibbonCloseButtonEHImpl, kContentDropperToolPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kRibbonPanelViewImpl, kContentDropperToolPrefix + 30)
//gap
DECLARE_PMID(kImplementationIDSpace, kRibbonNoItemCollectedTextViewImpl, kContentDropperToolPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kContentDropperDropCursorProviderImpl, kContentDropperToolPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kContentDropperToolObserverImpl, kContentDropperToolPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kContentDropperToolStartupShutdownImpl, kContentDropperToolPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kRibbonDataImpl, kContentDropperToolPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kRibbonOptionsPanelViewImpl, kContentDropperToolPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kContentDropperToolEditStyleMappingsObserverImpl, kContentDropperToolPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kRibbonCloseButtonViewImpl, kContentDropperToolPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kRibbonThumbnailContainerObserverImpl, kContentDropperToolPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kRibbonThumbnailCollapseViewImpl, kContentDropperToolPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kGrabPageRangeDialogControllerImpl, kContentDropperToolPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kGrabPageRangeDialogObserverImpl, kContentDropperToolPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kContentDropperToggleToolActionImpl, kContentDropperToolPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kContentDropperToolTipImpl, kContentDropperToolPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kCollectorMouseWatcherImpl, kContentDropperToolPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kRibbonThumbnailExpanderTipImpl, kContentDropperToolPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kContentToolSizerImpl, kContentDropperToolPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kCollectorMouseObserverImpl, kContentDropperToolPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kRibbonModelessWindowEHImpl, kContentDropperToolPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kRibbonToolSwitchButtonTipImpl, kContentDropperToolPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kRibbonStateImpl, kContentDropperToolPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kContentDropperToolCheckBoxEHImpl, kContentDropperToolPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kContentDropperGroupButtonPanelEHImpl, kContentDropperToolPrefix + 54)

//<Interface ID>
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTENTDROPPERTOOLPRIVATEUTILS, kContentDropperToolPrefix + 0)
DECLARE_PMID(kInterfaceIDSpace, IID_ITHUMBNAILSCOUNTDATA, kContentDropperToolPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IRIBBONMGR, kContentDropperToolPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IRIBBONDATA, kContentDropperToolPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IRIBBONPREVIEWIMAGEDATA, kContentDropperToolPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLLECTORACTIVETOOL, kContentDropperToolPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLLECTORMOUSEWATCHER, kContentDropperToolPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLLECTORMOUSEOBSERVER, kContentDropperToolPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IRIBBONSHOWN, kContentDropperToolPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IRIBBONSTATE, kContentDropperToolPrefix + 12)

// <Widget ID>
// Character attribute widgets <1-50>
DECLARE_PMID(kWidgetIDSpace, kContentDropperRibbonDlgWidgetId, kContentDropperToolPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kCDThumbnailAndOptionsPanelWidgetID, kContentDropperToolPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kCDOptionsPanelWidgetID, kContentDropperToolPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kRibbonThumbnailElementWidgetID, kContentDropperToolPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kRibbonDlgDialogWidgetID, kContentDropperToolPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kCDCreateLinkCheckBoxWidgetID, kContentDropperToolPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kRibbonThumbnailContainerWidgetID, kContentDropperToolPrefix +7)
DECLARE_PMID(kWidgetIDSpace, kCDGripperWidgetID, kContentDropperToolPrefix +8)
DECLARE_PMID(kWidgetIDSpace, kCDToolButtonsPanelWidgetID, kContentDropperToolPrefix +9)
DECLARE_PMID(kWidgetIDSpace, kCDGrabToolButtonWidgetID, kContentDropperToolPrefix +10)
DECLARE_PMID(kWidgetIDSpace, kCDDropToolButtonWidgetID, kContentDropperToolPrefix +11)
DECLARE_PMID(kWidgetIDSpace, kCDGripperNCloseContainerWidgetID, kContentDropperToolPrefix +12)
DECLARE_PMID(kWidgetIDSpace, kCDCloseButtonWidgetID, kContentDropperToolPrefix +13)
DECLARE_PMID(kWidgetIDSpace, kRibbonElementWidgetID, kContentDropperToolPrefix +14)
DECLARE_PMID(kWidgetIDSpace, kCDMapStylesCheckBoxWidgetID, kContentDropperToolPrefix +15)
DECLARE_PMID(kWidgetIDSpace, kCDNoItemCollectedTextPanelWidgetID, kContentDropperToolPrefix +16)
DECLARE_PMID(kWidgetIDSpace, kRibbonThumbnailExpanderWidgetID, kContentDropperToolPrefix +17)
DECLARE_PMID(kWidgetIDSpace, kCDFastNavigateLeftWidgetID, kContentDropperToolPrefix +18)
DECLARE_PMID(kWidgetIDSpace, kCDNavigateLeftWidgetID, kContentDropperToolPrefix +19)
DECLARE_PMID(kWidgetIDSpace, kCDNavigateRightWidgetID, kContentDropperToolPrefix +20)
DECLARE_PMID(kWidgetIDSpace, kCDFastNavigateRightWidgetID, kContentDropperToolPrefix +21)
DECLARE_PMID(kWidgetIDSpace, kRibbonThumbnailCollapseWidgetID, kContentDropperToolPrefix +22)
DECLARE_PMID(kWidgetIDSpace, kCDNavigateGroupWidgetID, kContentDropperToolPrefix +23)
DECLARE_PMID(kWidgetIDSpace, kEditStyleMappingsWidgetID, kContentDropperToolPrefix +24)
DECLARE_PMID(kWidgetIDSpace, kCDHeadDescriptionWidgetID, kContentDropperToolPrefix +25)
DECLARE_PMID(kWidgetIDSpace, kCDDropOptionsPanelWidgetID, kContentDropperToolPrefix +26)
DECLARE_PMID(kWidgetIDSpace, kCDDropOptionButtonsPanelWidgetID, kContentDropperToolPrefix +27)
DECLARE_PMID(kWidgetIDSpace, kCDDropOptionRemoveItemWidgetID, kContentDropperToolPrefix +28)
DECLARE_PMID(kWidgetIDSpace, kCDDropOptionRetainWidgetID, kContentDropperToolPrefix +29)
DECLARE_PMID(kWidgetIDSpace, kCDDropOptionRetainAndMoveWidgetID, kContentDropperToolPrefix +30)
DECLARE_PMID(kWidgetIDSpace, kRibbonLastThumbnailMarkerWidgetID, kContentDropperToolPrefix +31)
DECLARE_PMID(kWidgetIDSpace, kCDNoItemCollectedTextLine1WidgetID, kContentDropperToolPrefix +32)
DECLARE_PMID(kWidgetIDSpace, kCDNoItemCollectedTextLine2WidgetID, kContentDropperToolPrefix +33)
DECLARE_PMID(kWidgetIDSpace, kCDGrabPagesWidgetID, kContentDropperToolPrefix +34)
DECLARE_PMID(kWidgetIDSpace, kCDGrabPagesDialogWidgetID, kContentDropperToolPrefix +35)
DECLARE_PMID(kWidgetIDSpace, kCDGrabPageSelectedWidgetID, kContentDropperToolPrefix +36)
DECLARE_PMID(kWidgetIDSpace, kCDGrabPagesRangeWidgetID, kContentDropperToolPrefix +37)
DECLARE_PMID(kWidgetIDSpace, kCDGrabPagesAllWidgetID, kContentDropperToolPrefix +38)
DECLARE_PMID(kWidgetIDSpace, kCDCreateSetsByPageWidgetID, kContentDropperToolPrefix +39)
DECLARE_PMID(kWidgetIDSpace, kCDPageRangeWidgetID, kContentDropperToolPrefix +40)
DECLARE_PMID(kWidgetIDSpace, kCDGrabOptionsClusterPanelWidgetID, kContentDropperToolPrefix +41)
DECLARE_PMID(kWidgetIDSpace, kCDGrabPageRangeOptionPanelWidgetID, kContentDropperToolPrefix +42)
DECLARE_PMID(kWidgetIDSpace, kCDGrabOptionsPanelWidgetID, kContentDropperToolPrefix +43)
DECLARE_PMID(kWidgetIDSpace, kCDGrabAllThreadedFrameWidgetID, kContentDropperToolPrefix +44)
DECLARE_PMID(kWidgetIDSpace, kCDContentToolWidgetID, kContentDropperToolPrefix +45)
DECLARE_PMID(kWidgetIDSpace, kCDDropToolWidgetID, kContentDropperToolPrefix +46)
DECLARE_PMID(kWidgetIDSpace, kCDDropOptions2PanelWidgetID, kContentDropperToolPrefix +47)

// Other StringKeys:
#define kRibbonDlgAboutBoxStringKey	kContentDropperStringPrefix "kRibbonDlgAboutBoxStringKey"

// <Message ID>
DECLARE_PMID(kMessageIDSpace, kRibbonVisibilityChangeMsg, kContentDropperToolPrefix + 1)
DECLARE_PMID(kMessageIDSpace, kRibbonCreateThumbnailsMsg, kContentDropperToolPrefix + 2)
// <Service ID>
// Service IDs
//DECLARE_PMID(kServiceIDSpace, kContentDropperPrefsPanelServiceImpl, kContentDropperToolPrefix + 1)

// <Action ID>
// Action IDs
DECLARE_PMID(kActionIDSpace, kToggleContentDropperModeActionID, kContentDropperToolPrefix + 1)

#endif
