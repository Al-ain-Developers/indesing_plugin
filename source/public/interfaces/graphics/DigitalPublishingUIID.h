//========================================================================================
//  Owner: Adobe Systems Inc.
//  
//  Copyright 2010-2015 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#ifndef __DigitalPublishingUIID_h__
#define __DigitalPublishingUIID_h__

//----------------------------------------------------------------------------------------
// Plug-in:
//----------------------------------------------------------------------------------------
#define kDigitalPublishingUIPluginName		"DigitalPublishingUI"			// Name of this plug-in.
#define kDigitalPublishingUIPrefixNumber	0x22a00 						// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).

#define kDigitalPublishingUIPrefix			RezLong(kDigitalPublishingUIPrefixNumber)	// The unique numeric prefix for all object model IDs for this plug-in.

//----------------------------------------------------------------------------------------
// Missing plug-in: (see ExtraPluginInfo resource)
//----------------------------------------------------------------------------------------
//sdk #define kDigitalPublishingUIMissingPluginURLValue		kSDKDefPartnersStandardValue_enUS // URL displayed in Missing Plug-in dialog
//sdk #define kDigitalPublishingUIMissingPluginAlertValue	kSDKDefMissingPluginAlertValue // Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem

//----------------------------------------------------------------------------------------
// PluginID:
//----------------------------------------------------------------------------------------
DECLARE_PMID(kPlugInIDSpace, kDigitalPublishingUIPluginID, kDigitalPublishingUIPrefix + 0)

//----------------------------------------------------------------------------------------
// ClassIDs:
//----------------------------------------------------------------------------------------

// Export
DECLARE_PMID(kClassIDSpace, kDigitalPublishingExportDialogBoss, kDigitalPublishingUIPrefix + 1)

// Target Device Dimensions
DECLARE_PMID(kClassIDSpace, kDPSArticleExportTargetDeviceDialogBoss, kDigitalPublishingUIPrefix + 24)

#ifdef DEBUG
DECLARE_PMID(kClassIDSpace, kDPSArticleTestMenuBoss, kDigitalPublishingUIPrefix + 30)
#endif

// Overlay Creator Panel
DECLARE_PMID(kClassIDSpace, kDigitalPublishingUIActionComponentBoss, kDigitalPublishingUIPrefix + 100)
DECLARE_PMID(kClassIDSpace, kDigitalPublishingUIPanelBoss, kDigitalPublishingUIPrefix + 101)
DECLARE_PMID(kClassIDSpace, kDigitalPublishingUIPanelTreeWidgetBoss, kDigitalPublishingUIPrefix + 102)
DECLARE_PMID(kClassIDSpace, kDigitalPublishingUIOverlayOptionsPanelWidgetBoss, kDigitalPublishingUIPrefix + 103)
DECLARE_PMID(kClassIDSpace, kDigitalPublishingUIOverlayTreeNodeWidgetBoss, kDigitalPublishingUIPrefix + 104)
DECLARE_PMID(kClassIDSpace, kDigitalPublishingUIPreviewButtonBoss, kDigitalPublishingUIPrefix + 105)
DECLARE_PMID(kClassIDSpace, kDigitalPublishingUIDeleteButtonBoss, kDigitalPublishingUIPrefix + 106)
DECLARE_PMID(kClassIDSpace, kDigitalPublishingUIResetButtonBoss, kDigitalPublishingUIPrefix + 107)

DECLARE_PMID(kClassIDSpace, kDigitalPublishingUIHyperlinkOverlayPanelWidgetBoss, kDigitalPublishingUIPrefix + 110)
DECLARE_PMID(kClassIDSpace, kDigitalPublishingUISlideshowOverlayPanelWidgetBoss, kDigitalPublishingUIPrefix + 111)
DECLARE_PMID(kClassIDSpace, kDigitalPublishingUIImageSequenceOverlayPanelWidgetBoss, kDigitalPublishingUIPrefix + 112)
DECLARE_PMID(kClassIDSpace, kDigitalPublishingUIAudioOverlayPanelWidgetBoss, kDigitalPublishingUIPrefix + 113)
DECLARE_PMID(kClassIDSpace, kDigitalPublishingUIVideoOverlayPanelWidgetBoss, kDigitalPublishingUIPrefix + 114)
DECLARE_PMID(kClassIDSpace, kDigitalPublishingUIWebContentOverlayPanelWidgetBoss, kDigitalPublishingUIPrefix + 115)
DECLARE_PMID(kClassIDSpace, kDigitalPublishingUIPanZoomOverlayPanelWidgetBoss, kDigitalPublishingUIPrefix + 116)
DECLARE_PMID(kClassIDSpace, kDigitalPublishingUIScrollableFrameOverlayPanelWidgetBoss, kDigitalPublishingUIPrefix + 117)
DECLARE_PMID(kClassIDSpace, kDigitalPublishingUIScrollableFrameDropDownWidgetBoss, kDigitalPublishingUIPrefix + 118)
DECLARE_PMID(kClassIDSpace, kDigitalPublishingUIWebContentIconFieldWidgetBoss, kDigitalPublishingUIPrefix + 119)


//----------------------------------------------------------------------------------------
// Message IDs: note - message ids conflict with class ids.
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// ServiceIDs:
//----------------------------------------------------------------------------------------

// Overlay Creator Panel
DECLARE_PMID(kServiceIDSpace, kDigitalPublishingUIOverlayOptionsPanelWidgetService, kDigitalPublishingUIPrefix + 100)

//----------------------------------------------------------------------------------------
// InterfaceIDs:
//----------------------------------------------------------------------------------------

// Overlay Creator Panel
DECLARE_PMID(kInterfaceIDSpace, IID_IDIGITALPUBLISHINGUIPANELATTRIBUTES, kDigitalPublishingUIPrefix + 100)
DECLARE_PMID(kInterfaceIDSpace, IID_IDIGITALPUBLISHINGUIOVERLAYPROVIDER, kDigitalPublishingUIPrefix + 101)
DECLARE_PMID(kInterfaceIDSpace, IID_IDIGITALPUBLISHINGUISELECTIONSUITE, kDigitalPublishingUIPrefix + 102)


//----------------------------------------------------------------------------------------
// ImplementationIDs:
//----------------------------------------------------------------------------------------

// Export
DECLARE_PMID(kImplementationIDSpace, kDPSArticleExportDialogControllerImpl, kDigitalPublishingUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kDPSArticleExportDialogObserverImpl, kDigitalPublishingUIPrefix + 2)

#ifdef DEBUG
DECLARE_PMID(kImplementationIDSpace, kDPSArticleTestMenuImpl, kDigitalPublishingUIPrefix + 30)
#endif

// Overlay Creator Panel
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUIActionComponentImpl, kDigitalPublishingUIPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUITreeViewAdapterImpl, kDigitalPublishingUIPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUITreeViewWidgetMgrImpl, kDigitalPublishingUIPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUIPanelTreeObserverImpl, kDigitalPublishingUIPrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUIPanelAttributesImpl, kDigitalPublishingUIPrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUIOverlayOptionsPanelViewImpl, kDigitalPublishingUIPrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUIDefaultPanelServiceImpl, kDigitalPublishingUIPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUISelectionObserverImpl, kDigitalPublishingUIPrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUISuiteASBImpl, kDigitalPublishingUIPrefix + 108)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUISuiteLayoutCSBImpl, kDigitalPublishingUIPrefix + 109)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUITreeRowPanelEHImpl, kDigitalPublishingUIPrefix + 110)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUIDeleteButtonObserverImpl, kDigitalPublishingUIPrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUIPreviewButtonObserverImpl, kDigitalPublishingUIPrefix + 112)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUIResetButtonObserverImpl, kDigitalPublishingUIPrefix + 113)
//gap
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUIHyperlinkOverlayPanelCreatorImpl, kDigitalPublishingUIPrefix + 120)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUIHyperlinkOverlayProviderImpl, kDigitalPublishingUIPrefix + 121)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUIHyperlinkOverlayPanelObseverImpl, kDigitalPublishingUIPrefix + 122)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUISlideshowOverlayPanelCreatorImpl, kDigitalPublishingUIPrefix + 123)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUISlideshowOverlayProviderImpl, kDigitalPublishingUIPrefix + 124)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUISlideshowOverlayPanelObseverImpl, kDigitalPublishingUIPrefix + 125)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUIImageSequenceOverlayPanelCreatorImpl, kDigitalPublishingUIPrefix + 126)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUIImageSequenceOverlayProviderImpl, kDigitalPublishingUIPrefix + 127)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUIImageSequenceOverlayPanelObseverImpl, kDigitalPublishingUIPrefix + 128)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUIAudioOverlayPanelCreatorImpl, kDigitalPublishingUIPrefix + 129)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUIAudioOverlayProviderImpl, kDigitalPublishingUIPrefix + 130)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUIAudioOverlayPanelObseverImpl, kDigitalPublishingUIPrefix + 131)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUIVideoOverlayPanelCreatorImpl, kDigitalPublishingUIPrefix + 132)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUIVideoOverlayProviderImpl, kDigitalPublishingUIPrefix + 133)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUIVideoOverlayPanelObseverImpl, kDigitalPublishingUIPrefix + 134)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUIWebContentOverlayPanelCreatorImpl, kDigitalPublishingUIPrefix + 135)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUIWebContentOverlayProviderImpl, kDigitalPublishingUIPrefix + 136)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUIWebContentOverlayPanelObseverImpl, kDigitalPublishingUIPrefix + 137)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUIPanZoomOverlayPanelCreatorImpl, kDigitalPublishingUIPrefix + 138)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUIPanZoomOverlayProviderImpl, kDigitalPublishingUIPrefix + 139)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUIPanZoomOverlayPanelObseverImpl, kDigitalPublishingUIPrefix + 140)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUIScrollableFrameOverlayPanelCreatorImpl, kDigitalPublishingUIPrefix + 141)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUIScrollableFrameOverlayProviderImpl, kDigitalPublishingUIPrefix + 142)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUIScrollableFrameOverlayPanelObseverImpl, kDigitalPublishingUIPrefix + 143)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUIScrollableFrameOverlayToolTipImpl, kDigitalPublishingUIPrefix + 144)
DECLARE_PMID(kImplementationIDSpace, kDigitalPublishingUIWebContentOverlayToolTipImpl, kDigitalPublishingUIPrefix + 145)

//----------------------------------------------------------------------------------------
// ActionIDs:
//----------------------------------------------------------------------------------------

// Overlay Creator Panel
DECLARE_PMID(kActionIDSpace, kDigitalPublishingUIPanelActionID, kDigitalPublishingUIPrefix + 100)

//----------------------------------------------------------------------------------------
// WidgetIDs:
//----------------------------------------------------------------------------------------
// Export
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingExportDialogWidgetID, kDigitalPublishingUIPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kExportArticleNameTextEditBoxWidgetID, kDigitalPublishingUIPrefix + 2)
//gap

DECLARE_PMID(kWidgetIDSpace, kExportLayoutStringWidgetID, kDigitalPublishingUIPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kExportLayoutDropDownWidgetID, kDigitalPublishingUIPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kExportLayoutInfoIconWidgetID, kDigitalPublishingUIPrefix + 6)

// target device
DECLARE_PMID(kWidgetIDSpace, kExportPageGroupWidgetId, kDigitalPublishingUIPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kExportPageSizeGroupWidgetID, kDigitalPublishingUIPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kPageOrientationBorderWidgetID, kDigitalPublishingUIPrefix + 9)

DECLARE_PMID(kWidgetIDSpace, kExportPageLandscapeIconWidgetID, kDigitalPublishingUIPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kExportPagePortraitIconWidgetID, kDigitalPublishingUIPrefix + 11)

DECLARE_PMID(kWidgetIDSpace, kExportTargetSizeWidthWidgetID, kDigitalPublishingUIPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kExportTargetSizeHeightWidgetID, kDigitalPublishingUIPrefix + 13)

DECLARE_PMID(kWidgetIDSpace, kExportLayoutPanelWidgetID, kDigitalPublishingUIPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kExportTargetDeviceDropDownWidgetID, kDigitalPublishingUIPrefix + 15)


DECLARE_PMID(kWidgetIDSpace, kExportScrollingCheckBoxWidgetID, kDigitalPublishingUIPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kExportScrollingInfoIconWidgetID, kDigitalPublishingUIPrefix + 17)

DECLARE_PMID(kWidgetIDSpace, kExportSwipeCheckBoxWidgetID, kDigitalPublishingUIPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kExportSwipeInfoIconWidgetID, kDigitalPublishingUIPrefix + 19)

DECLARE_PMID(kWidgetIDSpace, kExportTargetDeviceStringWidgetID, kDigitalPublishingUIPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kExportTargetWidthStringWidgetID, kDigitalPublishingUIPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kExportTargetHeightStringWidgetID, kDigitalPublishingUIPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kExportTargetInfoIconWidgetID, kDigitalPublishingUIPrefix + 23)

// Overlay Creator Panel
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIPanelWidgetID, kDigitalPublishingUIPrefix + 50)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISplitterPanelWidgetID, kDigitalPublishingUIPrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIInfoOuterPanelWidgetID, kDigitalPublishingUIPrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUITreeOuterPanelWidgetID, kDigitalPublishingUIPrefix + 53)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIHeaderLabelWidgetID, kDigitalPublishingUIPrefix + 54)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIHeaderSeparatorWidgetID, kDigitalPublishingUIPrefix + 55)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIPanelTreeWidgetID, kDigitalPublishingUIPrefix + 56)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIOverlayOptionsLabelWidgetID, kDigitalPublishingUIPrefix + 57)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIOverlayOptionsSeparatorWidgetID, kDigitalPublishingUIPrefix + 58)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIOverlayOptionsPanelWidgetID, kDigitalPublishingUIPrefix + 59)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIScrollBarWidgetID, kDigitalPublishingUIPrefix + 60)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIOverlayTreeNodeWidgetID, kDigitalPublishingUIPrefix + 61)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIOverlayElementWidgetID, kDigitalPublishingUIPrefix + 62)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIControlStripWidgetID, kDigitalPublishingUIPrefix + 63)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIPreviewButtonWidgetID, kDigitalPublishingUIPrefix + 64)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIDeleteButtonWidgetID, kDigitalPublishingUIPrefix + 65)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIResetButtonWidgetID, kDigitalPublishingUIPrefix + 66)
//gap

// Hyperlink overlay sub panel
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIHyperlinkOverlayPanelWidgetID, kDigitalPublishingUIPrefix + 70)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIHyperlinkOverlaySubPanelWidgetID, kDigitalPublishingUIPrefix + 71)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIHyperlinkClusterWidgetID, kDigitalPublishingUIPrefix + 72)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIHyperlinkOpenInFolioWidgetID, kDigitalPublishingUIPrefix + 73)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIHyperlinkOpenInDeviceWidgetID, kDigitalPublishingUIPrefix + 74)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIHyperlinkAskFirstWidgetID, kDigitalPublishingUIPrefix + 75)

// Slideshow overlay sub panel
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISlideshowOverlayPanelWidgetID, kDigitalPublishingUIPrefix + 80)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISlideshowOverlaySubPanelWidgetID, kDigitalPublishingUIPrefix + 81)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISlideshowOverlayStaticWidgetID, kDigitalPublishingUIPrefix + 82)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISlideshowAutoPlayWidgetID, kDigitalPublishingUIPrefix + 83)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISlideshowTapToPausePlayWidgetID, kDigitalPublishingUIPrefix + 84)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISlideshowDelayPanelWidgetID, kDigitalPublishingUIPrefix + 85)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISlideshowDelayLabelWidgetID, kDigitalPublishingUIPrefix + 86)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISlideshowDelayNudgeWidgetID, kDigitalPublishingUIPrefix + 87)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISlideshowDelayTextWidgetID, kDigitalPublishingUIPrefix + 88)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISlideshowSecondsLabelWidgetID, kDigitalPublishingUIPrefix + 89)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISlideshowIntervalPanelWidgetID, kDigitalPublishingUIPrefix + 90)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISlideshowIntervalLabelWidgetID, kDigitalPublishingUIPrefix + 91)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISlideshowIntervalNudgeWidgetID, kDigitalPublishingUIPrefix + 92)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISlideshowIntervalTextWidgetID, kDigitalPublishingUIPrefix + 93)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISlideshowIntervalSecLabelWidgetID, kDigitalPublishingUIPrefix + 94)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISlideshowPlayPanelWidgetID, kDigitalPublishingUIPrefix + 95)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISlideshowPlayLabelWidgetID, kDigitalPublishingUIPrefix + 96)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISlideshowPlayNudgeWidgetID, kDigitalPublishingUIPrefix + 97)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISlideshowPlayTextWidgetID, kDigitalPublishingUIPrefix + 98)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISlideshowTimesLabelWidgetID, kDigitalPublishingUIPrefix + 99)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISlideshowLoopWidgetID, kDigitalPublishingUIPrefix + 100)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISlideshowStopAtLastidgetID, kDigitalPublishingUIPrefix + 101)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISlideshowCrossfadeWidgetID, kDigitalPublishingUIPrefix + 102)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISlideshowSpeedPanelWidgetID, kDigitalPublishingUIPrefix + 103)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISlideshowSpeedLabelWidgetID, kDigitalPublishingUIPrefix + 104)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISlideshowSpeedNudgeWidgetID, kDigitalPublishingUIPrefix + 105)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISlideshowSpeedTextWidgetID, kDigitalPublishingUIPrefix + 106)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISlideshowSpeedSecLabelWidgetID, kDigitalPublishingUIPrefix + 107)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISlideshowSwipeWidgetID, kDigitalPublishingUIPrefix + 108)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISlideshowStopAtFirstLastWidgetID, kDigitalPublishingUIPrefix + 709)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISlideshowHideBeforePlayWidgetID, kDigitalPublishingUIPrefix + 110)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISlideshowPlayReverseWidgetID, kDigitalPublishingUIPrefix + 111)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISlideshowFormatLabelWidgetID, kDigitalPublishingUIPrefix + 112)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUISlideshowFormatDropdownWidgetID, kDigitalPublishingUIPrefix + 113)

// Image sequence overlay sub panel
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIImageSequenceOverlayPanelWidgetID, kDigitalPublishingUIPrefix + 120)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIImageSequenceOverlaySubPanelWidgetID, kDigitalPublishingUIPrefix + 121)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIImageSequenceOverlayStaticWidgetID, kDigitalPublishingUIPrefix + 122)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIImSeqFileLabelWidgetID, kDigitalPublishingUIPrefix + 123)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIImSeqFileBrowseWidgetId, kDigitalPublishingUIPrefix + 124)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIImSeqFileTextWidgetID, kDigitalPublishingUIPrefix + 125)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIImSeqShowFirstImageWidgetID, kDigitalPublishingUIPrefix + 126)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIImSeqAutoPlayWidgetID, kDigitalPublishingUIPrefix + 127)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIImSeqTapToPausePlayWidgetID, kDigitalPublishingUIPrefix + 128)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIImSeqDelayPanelWidgetID, kDigitalPublishingUIPrefix + 129)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIImSeqDelayLabelWidgetID, kDigitalPublishingUIPrefix + 130)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIImSeqDelayNudgeWidgetID, kDigitalPublishingUIPrefix + 131)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIImSeqDelayTextWidgetID, kDigitalPublishingUIPrefix + 132)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIImSeqSecondsLabelWidgetID, kDigitalPublishingUIPrefix + 133)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIImSeqSpeedPanelWidgetID, kDigitalPublishingUIPrefix + 134)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIImSeqSpeedLabelWidgetID, kDigitalPublishingUIPrefix + 135)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIImSeqSpeedNudgeWidgetID, kDigitalPublishingUIPrefix + 136)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIImSeqSpeedTextWidgetID, kDigitalPublishingUIPrefix + 137)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIImSeqFpsLabelWidgetID, kDigitalPublishingUIPrefix + 138)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIImSeqPlayPanelWidgetID, kDigitalPublishingUIPrefix + 139)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIImSeqPlayLabelWidgetID, kDigitalPublishingUIPrefix + 140)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIImSeqPlayNudgeWidgetID, kDigitalPublishingUIPrefix + 141)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIImSeqPlayTextWidgetID, kDigitalPublishingUIPrefix + 142)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIImSeqTimesLabelWidgetID, kDigitalPublishingUIPrefix + 143)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIImSeqLoopWidgetID, kDigitalPublishingUIPrefix + 144)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIImSeqStopAtLastidgetID, kDigitalPublishingUIPrefix + 145)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIImSeqSwipeWidgetID, kDigitalPublishingUIPrefix + 146)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIImSeqStopAtFirstLastWidgetID, kDigitalPublishingUIPrefix + 147)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIImSeqPlayReverseWidgetID, kDigitalPublishingUIPrefix + 148)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIImSeqFileAlertWidgetId, kDigitalPublishingUIPrefix + 149)

// Audio overlay sub panel
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIAudioOverlayPanelWidgetID, kDigitalPublishingUIPrefix + 150)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIAudioOverlaySubPanelWidgetID, kDigitalPublishingUIPrefix + 151)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIAudioURLFileLabelWidgetID, kDigitalPublishingUIPrefix + 152)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIAudioURLFileTextWidgetID, kDigitalPublishingUIPrefix + 153)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIAudioControllerFileLabelWidgetID, kDigitalPublishingUIPrefix + 154)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIAudioControllerFileTextWidgetID, kDigitalPublishingUIPrefix + 155)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIAudioShowFirstImageWidgetID, kDigitalPublishingUIPrefix + 156)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIAudioPanelWidgetID, kDigitalPublishingUIPrefix + 157)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIAudioAutoPlayWidgetID, kDigitalPublishingUIPrefix + 158)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIAudioDelayPanelWidgetID, kDigitalPublishingUIPrefix + 159)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIAudioDelayLabelWidgetID, kDigitalPublishingUIPrefix + 160)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIAudioDelayNudgeWidgetID, kDigitalPublishingUIPrefix + 161)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIAudioDelayTextWidgetID, kDigitalPublishingUIPrefix + 162)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIAudioSecondsLabelWidgetID, kDigitalPublishingUIPrefix + 163)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIAudioPlayInBackgroundWidgetID, kDigitalPublishingUIPrefix + 164)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIAudioFileAlertWidgetId, kDigitalPublishingUIPrefix + 165)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIAudioFileBrowseWidgetId, kDigitalPublishingUIPrefix + 166)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIAudioControllerBrowseWidgetId, kDigitalPublishingUIPrefix + 167)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIAudioControllerFilePanelWidgetID, kDigitalPublishingUIPrefix + 168)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIAudioControllerFileAlertWidgetId, kDigitalPublishingUIPrefix + 169)

// Video overlay sub panel
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIVideoOverlayPanelWidgetID, kDigitalPublishingUIPrefix + 170)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIVideoOverlaySubPanelWidgetID, kDigitalPublishingUIPrefix + 171)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIVideoOverlayStaticWidgetID, kDigitalPublishingUIPrefix + 172)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIVideoURLFileLabelWidgetID, kDigitalPublishingUIPrefix + 173)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIVideoURLFileTextWidgetID, kDigitalPublishingUIPrefix + 174)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIVideoFileBrowseWidgetId, kDigitalPublishingUIPrefix + 175)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIVideoAutoPlayWidgetID, kDigitalPublishingUIPrefix + 176)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIVideoDelayPanelWidgetID, kDigitalPublishingUIPrefix + 177)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIVideoDelayLabelWidgetID, kDigitalPublishingUIPrefix + 178)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIVideoDelayNudgeWidgetID, kDigitalPublishingUIPrefix + 179)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIVideoDelayTextWidgetID, kDigitalPublishingUIPrefix + 180)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIVideoSecondsLabelWidgetID, kDigitalPublishingUIPrefix + 181)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIVideoPlayFullScreenWidgetID, kDigitalPublishingUIPrefix + 182)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIVideoTapToViewControllerWidgetID, kDigitalPublishingUIPrefix + 183)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIVideoDoNotAllowPauseWidgetID, kDigitalPublishingUIPrefix + 184)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIVideoStopOnLastFrameWidgetID, kDigitalPublishingUIPrefix + 185)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIVideoFileAlertWidgetId, kDigitalPublishingUIPrefix + 186)

// Web Content overlay sub panel
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIWebContentOverlayPanelWidgetID, kDigitalPublishingUIPrefix + 190)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIWebContentOverlaySubPanelWidgetID, kDigitalPublishingUIPrefix + 191)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIWebContentURLFileLabelWidgetID, kDigitalPublishingUIPrefix + 192)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIWebContentURLFileTextWidgetID, kDigitalPublishingUIPrefix + 193)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIWebContentAutoPlayWidgetID, kDigitalPublishingUIPrefix + 194)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIWebContentDelayLabelWidgetID, kDigitalPublishingUIPrefix + 195)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIWebContentDelayNudgeWidgetID, kDigitalPublishingUIPrefix + 196)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIWebContentDelayTextWidgetID, kDigitalPublishingUIPrefix + 197)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIWebContentSecondsLabelWidgetID, kDigitalPublishingUIPrefix + 198)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIWebContentTransparentBackgroundWidgetID, kDigitalPublishingUIPrefix + 199)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIWebContentAllowUserInteractionWidgetID, kDigitalPublishingUIPrefix + 200)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIWebContentScaleContentToFitWidgetID, kDigitalPublishingUIPrefix + 201)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIWebContentAllowAccessEntitlementWidgetID, kDigitalPublishingUIPrefix + 202)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIWebContentPanelWidgetID, kDigitalPublishingUIPrefix + 203)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIWebContentDelayPanelWidgetID, kDigitalPublishingUIPrefix + 204)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIWebContentFileBrowseWidgetId, kDigitalPublishingUIPrefix + 205)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIWebContentFileIconPanelWidgetID, kDigitalPublishingUIPrefix + 206)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIWebContentFileAlertWidgetId, kDigitalPublishingUIPrefix + 207)

// Pan&zoom overlay sub panel
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIPanZoomOverlayPanelWidgetID, kDigitalPublishingUIPrefix + 210)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIPanZoomOverlaySubPanelWidgetID, kDigitalPublishingUIPrefix + 211)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIPanZoomOverlayStaticWidgetID, kDigitalPublishingUIPrefix + 212)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIPanZoomClusterWidgetID, kDigitalPublishingUIPrefix + 213)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIPanZoomOffWidgetID, kDigitalPublishingUIPrefix + 214)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIPanZoomOnWidgetID, kDigitalPublishingUIPrefix + 215)

// Scrollable Frame overlay sub panel
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIScrollableFrameOverlayPanelWidgetID, kDigitalPublishingUIPrefix + 220)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIScrollableFrameOverlaySubPanelWidgetID, kDigitalPublishingUIPrefix + 221)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIScrollableFrameOverlayStaticWidgetID, kDigitalPublishingUIPrefix + 222)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIScrollFrameScrollDirDropdownWidgetID, kDigitalPublishingUIPrefix + 223)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIScrollFrameScrollIndicatorLabelWidgetID, kDigitalPublishingUIPrefix + 224)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIScrollFrameScrollIndicatorCheckboxWidgetID, kDigitalPublishingUIPrefix + 225)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIScrollFrameInitPositionLabelWidgetID, kDigitalPublishingUIPrefix + 226)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIScrollFrameClusterWidgetID, kDigitalPublishingUIPrefix + 227)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIScrollFrameUpperLeftWidgetID, kDigitalPublishingUIPrefix + 228)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIScrollFrameUseDocPositionWidgetID, kDigitalPublishingUIPrefix + 229)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIScrollFrameScrollFormatLabelWidgetID, kDigitalPublishingUIPrefix + 230)
DECLARE_PMID(kWidgetIDSpace, kDigitalPublishingUIScrollFrameScrollFormatDropdownWidgetID, kDigitalPublishingUIPrefix + 231)

//----------------------------------------------------------------------------------------
//Error code
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
//Script Element IDs
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Menu item keys:
//----------------------------------------------------------------------------------------

// Overlay Creator Panel
#define kDigitalPublishingUIOverlayNameNodeID		kDigitalPublishingUIPrefix + 1

//----------------------------------------------------------------------------------------
// Other StringKeys:
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Icon IDs
//----------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------
// Initial data format version numbers
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Data format version numbers for the PluginVersion resource 
//----------------------------------------------------------------------------------------

#endif // __DigitalPublishingUIID_h__

