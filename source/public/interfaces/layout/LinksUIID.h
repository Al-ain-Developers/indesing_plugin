//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/LinksUIID.h $
//  
//  Owner: lance bushore
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

#ifndef __LinksUIID__
#define __LinksUIID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kLinksUIPrefix RezLong(0x20600)	 
#define kProblemLinksDialogResID        900

// <Start IDC>
// PluginID
DECLARE_PMID(kPlugInIDSpace, kLinksUIPluginID, kLinksUIPrefix + 1)

// <Class ID>
DECLARE_PMID(kClassIDSpace, kLinksUIPanelTreeWidgetBoss, kLinksUIPrefix + 1)
DECLARE_PMID(kClassIDSpace, kLinksUITestMenuBoss, kLinksUIPrefix + 2)
DECLARE_PMID(kClassIDSpace, kLinksUILinkTextBoss, kLinksUIPrefix + 3)
#ifdef DEBUG
DECLARE_PMID(kClassIDSpace, kLinkInfoDebugUIDsProviderBoss, kLinksUIPrefix + 4)
#endif
DECLARE_PMID(kClassIDSpace, kLinksUILinkNameTextBoss, kLinksUIPrefix + 5)
DECLARE_PMID(kClassIDSpace, kLinkThumbnailBoss, kLinksUIPrefix + 6)
DECLARE_PMID(kClassIDSpace, kLinkInfoPanelWidgetBoss, kLinksUIPrefix + 7)
DECLARE_PMID(kClassIDSpace, kChooseLinkColumnsDialogBoss, kLinksUIPrefix + 8)
DECLARE_PMID(kClassIDSpace, kLinksUIPanelMenuBoss, kLinksUIPrefix + 9)
DECLARE_PMID(kClassIDSpace, kLinksUIPanelBoss, kLinksUIPrefix + 10)
DECLARE_PMID(kClassIDSpace, kToggleLinkInfoButtonBoss, kLinksUIPrefix + 11)
DECLARE_PMID(kClassIDSpace, kEditOriginalWithMenuComponentBoss, kLinksUIPrefix + 12)
DECLARE_PMID(kClassIDSpace, kEditOriginalSelectionWithMenuComponentBoss, kLinksUIPrefix + 13)
DECLARE_PMID(kClassIDSpace, kLinksUIButtonBoss, kLinksUIPrefix + 14)
DECLARE_PMID(kClassIDSpace, kNextPrevLinkButtonBoss, kLinksUIPrefix + 15)
DECLARE_PMID(kClassIDSpace, kOpenProblemLinksDialogCmdBoss, kLinksUIPrefix + 16)
DECLARE_PMID(kClassIDSpace, kProblemLinksDialogBoss, kLinksUIPrefix + 17)
DECLARE_PMID(kClassIDSpace, kLinksUIColumnHeaderWidgetBoss, kLinksUIPrefix + 18)
DECLARE_PMID(kClassIDSpace, kLinksUITreeSelectionAlteredMsgBoss, kLinksUIPrefix + 19)
DECLARE_PMID(kClassIDSpace, kLinksUITreeRowWidgetBoss, kLinksUIPrefix + 20)
DECLARE_PMID(kClassIDSpace, kLinkInfoIconWidgetBoss, kLinksUIPrefix + 21)
DECLARE_PMID(kClassIDSpace, kLinksUISchemaConversionBoss, kLinksUIPrefix + 22)
DECLARE_PMID(kClassIDSpace, kLinksUIStatusTextWidgetBoss, kLinksUIPrefix + 23)
DECLARE_PMID(kClassIDSpace, kLinksUILinkColumnTextBoss, kLinksUIPrefix + 24)
DECLARE_PMID(kClassIDSpace, kGenerateLinkCaptionDialogBoss, kLinksUIPrefix + 25)
DECLARE_PMID(kClassIDSpace, kAddDeleteCaptionRowButtonBoss, kLinksUIPrefix + 26)
DECLARE_PMID(kClassIDSpace, kLinkColumnHeaderIconWidgetBoss, kLinksUIPrefix + 27)
DECLARE_PMID(kClassIDSpace, kLinkInfoTextLabelWidgetBoss, kLinksUIPrefix + 28)
DECLARE_PMID(kClassIDSpace, kLinksUIPrefTreeStructureChangeMsgBoss, kLinksUIPrefix + 29) // not a real boss, just a message -means that a pref has changed which affects tree structure.
DECLARE_PMID(kClassIDSpace, kLinksUIPrefInfoPaneChangeMsgBoss, kLinksUIPrefix + 30) // not a real boss, just a message - means that a pref has changed which affects the info section
DECLARE_PMID(kClassIDSpace, kLinksUITreeRowChangeMsgBoss, kLinksUIPrefix + 31) // not a real boss, just a message - means that a pref has changed which affects how the rows look.
DECLARE_PMID(kClassIDSpace, kLinksUILinkNamePanelWidgetBoss, kLinksUIPrefix + 32)
//gap
DECLARE_PMID(kClassIDSpace, kLinkCaptionActionComponentBoss, kLinksUIPrefix + 34) 
DECLARE_PMID(kClassIDSpace, kCaptionParaStyleObserverBoss, kLinksUIPrefix + 35) 
DECLARE_PMID(kClassIDSpace, kCaptionLayerObserverBoss, kLinksUIPrefix + 36) 
DECLARE_PMID(kClassIDSpace, kMetadataLabelStaticTextBoss, kLinksUIPrefix + 37) 
DECLARE_PMID(kClassIDSpace, kGoToSourceSelectionWithMenuComponentBoss, kLinksUIPrefix + 38)
DECLARE_PMID(kClassIDSpace, kClosingDocumentsResponderBoss, kLinksUIPrefix + 39)

// <Implementation ID>
DECLARE_PMID(kImplementationIDSpace, kLinksUIPanelTreeViewAdapterImpl, kLinksUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kLinksUIPanelTreeViewWidgetMgrImpl, kLinksUIPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kLinksUIPanelTreeObserverImpl, kLinksUIPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kLinksUITestMenuImpl, kLinksUIPrefix + 4)
#ifdef DEBUG
DECLARE_PMID(kImplementationIDSpace, kLinkInfoDebugUIDsProviderImpl, kLinksUIPrefix + 5)
#endif
DECLARE_PMID(kImplementationIDSpace, kLinksUITreeViewControllerImpl, kLinksUIPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kLinksUIPanelPrefsImpl, kLinksUIPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kAddDeleteCaptionRowButtonObserverImpl, kLinksUIPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kLinksUITreePanelControlDataImpl, kLinksUIPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kLinkThumbnailViewImpl, kLinksUIPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoPanelObserverImpl, kLinksUIPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kLinksUIPanelMenuComponentImpl, kLinksUIPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kChooseLinksColumnsDialogControllerImpl, kLinksUIPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kToggleLinkInfoButtonObserverImpl, kLinksUIPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kLinkUIStaticTextViewImpl, kLinksUIPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kEditOriginalWithMenuImpl, kLinksUIPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kEditOriginalWithMenuComponentImpl, kLinksUIPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kEditOriginalSelectionWithMenuImpl, kLinksUIPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kEditOriginalSelectionWithMenuComponentImpl, kLinksUIPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kFilesChangingImpl, kLinksUIPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kEditOriginalResumeObserverImpl, kLinksUIPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kLinksUIPanelSelectionObserverImpl, kLinksUIPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kLinksUIUtilsImpl, kLinksUIPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kLinksUIPanelViewImpl, kLinksUIPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kLinksUIButtonObserverImpl, kLinksUIPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kLinkUILinkNameTipImpl, kLinksUIPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kOpenProblemLinksDialogCmdImpl, kLinksUIPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kProblemLinksDialogControllerImpl, kLinksUIPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kProblemLinksDialogObserverImpl, kLinksUIPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoIconViewImpl, kLinksUIPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kLinksUIColumnHeaderObserverImpl, kLinksUIPrefix + 32) 
DECLARE_PMID(kImplementationIDSpace, kLinksTreeNodeListImpl, kLinksUIPrefix + 33) 
DECLARE_PMID(kImplementationIDSpace, kLinksUITreeRowPanelEHImpl, kLinksUIPrefix + 34) 
DECLARE_PMID(kImplementationIDSpace, kLinksUIPanelXMLGeneratorImpl, kLinksUIPrefix + 35) 
DECLARE_PMID(kImplementationIDSpace, kLinksUIPanelSAXHandlerImpl, kLinksUIPrefix + 36) 
DECLARE_PMID(kImplementationIDSpace, kLinkInfoIconTipImpl, kLinksUIPrefix + 37) 
DECLARE_PMID(kImplementationIDSpace, kLinksUIStatusTextTipImpl, kLinksUIPrefix + 38) 
DECLARE_PMID(kImplementationIDSpace, kLinkInfoPanelPanoramaImpl, kLinksUIPrefix + 39) 

DECLARE_PMID(kImplementationIDSpace, kLinkInfoPanelViewImpl, kLinksUIPrefix + 40) 
DECLARE_PMID(kImplementationIDSpace, kNextPrevLinkButtonObserverImpl, kLinksUIPrefix + 41) 
DECLARE_PMID(kImplementationIDSpace, kLinkInfoPanelEHImpl, kLinksUIPrefix + 42) 
DECLARE_PMID(kImplementationIDSpace, kLinksUIStatusTextObserverImpl, kLinksUIPrefix + 43) 
DECLARE_PMID(kImplementationIDSpace, kLinkInfoIconEHImpl, kLinksUIPrefix + 44) 
DECLARE_PMID(kImplementationIDSpace, kLinkCaptionActionComponentImpl, kLinksUIPrefix + 45) 
DECLARE_PMID(kImplementationIDSpace, kCaptionParaStyleObserverImpl, kLinksUIPrefix + 46) 
DECLARE_PMID(kImplementationIDSpace, kLinkInfoTextLabelEHImpl, kLinksUIPrefix + 47) 
DECLARE_PMID(kImplementationIDSpace, kLinksUIButtonTipsImpl, kLinksUIPrefix + 48) 
DECLARE_PMID(kImplementationIDSpace, kGenerateLinkCaptionDialogControllerImpl, kLinksUIPrefix + 49)

DECLARE_PMID(kImplementationIDSpace, kLinksUIRowElementCursorProviderImpl, kLinksUIPrefix + 50) 
DECLARE_PMID(kImplementationIDSpace, kLinksTreeViewTypeAheadImpl, kLinksUIPrefix + 51) 
DECLARE_PMID(kImplementationIDSpace, kLinksUILinkNamePanelViewImpl, kLinksUIPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kLinksUIPanelViewObserverImpl, kLinksUIPrefix + 53)

DECLARE_PMID(kImplementationIDSpace, kCaptionLayerObserverImpl, kLinksUIPrefix + 55) 
DECLARE_PMID(kImplementationIDSpace, kMetadataLabelEVEInfoImpl, kLinksUIPrefix + 56) 
DECLARE_PMID(kImplementationIDSpace, kClosingDocumentsResponderImpl, kLinksUIPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kClosingDocumentsServiceProviderImpl, kLinksUIPrefix + 58)

// ---------------------------------------- <Widget ID> ------------------------------------
DECLARE_PMID(kWidgetIDSpace, kLinksUIPanelWidgetID, kLinksUIPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kLinksUIPanelTreeWidgetID, kLinksUIPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kLinksUIElementRowWidgetID, kLinksUIPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kLinksUIInfoHeaderLabelWidgetID, kLinksUIPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kLinksUIDynamicTextWidgetID, kLinksUIPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kLinksUIColumnHeaderRowWidgetID, kLinksUIPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kLinkHeaderTextWidgetID, kLinksUIPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kLinksUIInfoLabelWidgetID, kLinksUIPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kLinksUIInfoValueWidgetID, kLinksUIPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kLinkInfoLabelColumnWidgetID, kLinksUIPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kLinkInfoValueColumnWidgetID, kLinksUIPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kLinksUIPanelStatusWidgetID, kLinksUIPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kLinksUILinkInfoThumbnailWidgetID, kLinksUIPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kLinksUILinkThumbnailWidgetID, kLinksUIPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kLinkInfoPanelWidgetID, kLinksUIPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kLinkUISplitterPanelWidgetID, kLinksUIPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kLinkInfoOuterPanelWidgetID, kLinksUIPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kLinksUIPrefsDialogWidgetID, kLinksUIPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kLinksUINameEntryWidgetID, kLinksUIPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kLinkUIPrefLabelsPanelWidgetID, kLinksUIPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kLinksUIPrefShowColumnLabelWidgetID, kLinksUIPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kLinkUIPrefButtonPanelWidgetID, kLinksUIPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kToggleLinkInfoButtonWidgetID, kLinksUIPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kLinkUITreeOuterPanelWidgetID, kLinksUIPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kLinkColumnsTopSectionWidgetID, kLinksUIPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kLinksUIPrefShowInfoLabelWidgetID, kLinksUIPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kLinksUIRowSizeDropDownWidgetID, kLinksUIPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kLinkColumnSeparatorWidgetID, kLinksUIPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kLinksUIShowThumbnailCheckboxWidgetID, kLinksUIPrefix + 29)
DECLARE_PMID(kWidgetIDSpace, kRelinkButtonWidgetID, kLinksUIPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kUpdateLinkButtonWidgetID, kLinksUIPrefix + 31)

DECLARE_PMID(kWidgetIDSpace, kProblemParentWidgetId, kLinksUIPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kLinksPanelWidgetID1, kLinksUIPrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kProblemLinkMultilineTextWidgetId, kLinksUIPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kMissingLinksStaticWidgetID, kLinksUIPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kModifiedLinksStaticWidgetID, kLinksUIPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kProblemDialogButtonPanelWidgetID, kLinksUIPrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kProblemDialogIconTextPanelWidgetID, kLinksUIPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kProblemDialogTextPanelWidgetID, kLinksUIPrefix + 39)
DECLARE_PMID(kWidgetIDSpace, kInaccessibleLinksStaticWidgetID, kLinksUIPrefix + 40)
DECLARE_PMID(kWidgetIDSpace, kCaptionBeforeMetaCharButtonWidgetID, kLinksUIPrefix + 41)
DECLARE_PMID(kWidgetIDSpace, kFixLinksButtonWidgetID, kLinksUIPrefix + 42)
DECLARE_PMID(kWidgetIDSpace, kLinkInfoDynamicIconWidgetID, kLinksUIPrefix + 43)
DECLARE_PMID(kWidgetIDSpace, kLinkInfoSectionScrollBarWidgetID, kLinksUIPrefix + 44)
DECLARE_PMID(kWidgetIDSpace, kLinksUIPrefSpacerLabelWidgetID, kLinksUIPrefix + 45)
DECLARE_PMID(kWidgetIDSpace, kLinksUIPrefTreeWidgetID, kLinksUIPrefix + 46)
DECLARE_PMID(kWidgetIDSpace, kLinksUIPrefRowPanelWidgetID, kLinksUIPrefix + 47)
DECLARE_PMID(kWidgetIDSpace, kLinksUIPrefRowLabelWidgetID, kLinksUIPrefix + 48)
DECLARE_PMID(kWidgetIDSpace, kLinksUIPrefRowShowColumnCheckboxWidgetID, kLinksUIPrefix + 49)
DECLARE_PMID(kWidgetIDSpace, kLinksUIPrefRowShowInfoCheckboxWidgetID, kLinksUIPrefix + 50)
DECLARE_PMID(kWidgetIDSpace, kLinkUIPrefRowSizePanelWidgetID, kLinksUIPrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kGotoLinkButtonWidgetID, kLinksUIPrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kEditOriginalButtonWidgetID, kLinksUIPrefix + 53)
DECLARE_PMID(kWidgetIDSpace, kLinkUIThumbnailPrefPanelWidgetID, kLinksUIPrefix + 54)
DECLARE_PMID(kWidgetIDSpace, kShowLinkInfoThumbnailCheckboxWidgetID, kLinksUIPrefix + 55)
DECLARE_PMID(kWidgetIDSpace, kLinkInfoSeparatorWidgetID, kLinksUIPrefix + 56)
DECLARE_PMID(kWidgetIDSpace, kLinksUIOptionsGroupboxLabelWidgetID, kLinksUIPrefix + 57)
DECLARE_PMID(kWidgetIDSpace, kLinksUIThumbnailPrefLabelWidgetID, kLinksUIPrefix + 58)
DECLARE_PMID(kWidgetIDSpace, kLinksUIRowSizeLabelWidgetID, kLinksUIPrefix + 59)
DECLARE_PMID(kWidgetIDSpace, kSelectNextLinkButtonWidgetID, kLinksUIPrefix + 60)
DECLARE_PMID(kWidgetIDSpace, kSelectPrevLinkButtonWidgetID, kLinksUIPrefix + 61)
DECLARE_PMID(kWidgetIDSpace, kLinkHeaderIconWidgetID, kLinksUIPrefix + 62)
DECLARE_PMID(kWidgetIDSpace, kLinksUINameTextWidgetID, kLinksUIPrefix + 63)
DECLARE_PMID(kWidgetIDSpace, kGenerateCaptionDialogWidgetID, kLinksUIPrefix + 64)
DECLARE_PMID(kWidgetIDSpace, kCaptionHeaderPanelWidgetID, kLinksUIPrefix + 65)
DECLARE_PMID(kWidgetIDSpace, kCaptionBeforeMetadataLabelWidgetID, kLinksUIPrefix + 66)
DECLARE_PMID(kWidgetIDSpace, kCaptionMetadataLabelWidgetID, kLinksUIPrefix + 67)
DECLARE_PMID(kWidgetIDSpace, kCaptionAfterMetadataLabelWidgetID, kLinksUIPrefix + 68)
DECLARE_PMID(kWidgetIDSpace, kCaptionBeforeMetadataEditWidgetID, kLinksUIPrefix + 69)
DECLARE_PMID(kWidgetIDSpace, kCaptionMetadataDropDownWidgetID, kLinksUIPrefix + 70)
DECLARE_PMID(kWidgetIDSpace, kCaptionAfterMetadataEditWidgetID, kLinksUIPrefix + 71)
DECLARE_PMID(kWidgetIDSpace, kCaptionButtonPanelWidgetID, kLinksUIPrefix + 72)
DECLARE_PMID(kWidgetIDSpace, kLinksUIPrefsCollapseMultipleCheckboxWidgetID, kLinksUIPrefix + 73)
DECLARE_PMID(kWidgetIDSpace, kCaptionAddRowWidgetID, kLinksUIPrefix + 74)
DECLARE_PMID(kWidgetIDSpace, kCaptionDeleteRowWidgetID, kLinksUIPrefix + 75)
DECLARE_PMID(kWidgetIDSpace, kSelectCaptionRowsPanelWidgetID, kLinksUIPrefix + 76)
DECLARE_PMID(kWidgetIDSpace, kDynamicCaptionRowWidgetID, kLinksUIPrefix + 77)
DECLARE_PMID(kWidgetIDSpace, kCaptionMetaCharBorderWidgetID, kLinksUIPrefix + 78)
DECLARE_PMID(kWidgetIDSpace, kCaptionAfterMetaCharButtonWidgetID, kLinksUIPrefix + 79)
DECLARE_PMID(kWidgetIDSpace, kCaptionTopSectionPanelWidgetID, kLinksUIPrefix + 80)
DECLARE_PMID(kWidgetIDSpace, kCaptionBottomSectionPanelWidgetID, kLinksUIPrefix + 81)
DECLARE_PMID(kWidgetIDSpace, kCaptionTopSectionLabelWidgetID, kLinksUIPrefix + 82)
DECLARE_PMID(kWidgetIDSpace, kCaptionBottomSectionLabelWidgetID, kLinksUIPrefix + 83)
DECLARE_PMID(kWidgetIDSpace, kCaptionBottomLabelPanel1WidgetID, kLinksUIPrefix + 84)
DECLARE_PMID(kWidgetIDSpace, kCaptionOffsetLabelWidgetID, kLinksUIPrefix + 85)
DECLARE_PMID(kWidgetIDSpace, kCaptionParastyleLabelWidgetID, kLinksUIPrefix + 86)
DECLARE_PMID(kWidgetIDSpace, kCaptionParaStyleDropDownWidgetID, kLinksUIPrefix + 87)
DECLARE_PMID(kWidgetIDSpace, kCaptionOffsetNudgeWidgetID, kLinksUIPrefix + 88)
DECLARE_PMID(kWidgetIDSpace, kCaptionOffsetEditWidgetID, kLinksUIPrefix + 89)
DECLARE_PMID(kWidgetIDSpace, kCaptionBottomControlsPanel1WidgetID, kLinksUIPrefix + 90)
DECLARE_PMID(kWidgetIDSpace, kCaptionLayerLabelWidgetID, kLinksUIPrefix + 91)
DECLARE_PMID(kWidgetIDSpace, kCaptionLayerDropDownWidgetID, kLinksUIPrefix + 92)
DECLARE_PMID(kWidgetIDSpace, kCaptionBottomLabelPanel2WidgetID, kLinksUIPrefix + 93)
DECLARE_PMID(kWidgetIDSpace, kCaptionBottomControlsPanel2WidgetID, kLinksUIPrefix + 94)
DECLARE_PMID(kWidgetIDSpace, kCaptionAlignmentLabelWidgetID, kLinksUIPrefix + 95)
DECLARE_PMID(kWidgetIDSpace, kCaptionAlignmentDropDownWidgetID, kLinksUIPrefix + 96)
DECLARE_PMID(kWidgetIDSpace, kCaptionGroupWithImageCheckboxWidgetID, kLinksUIPrefix + 97)
DECLARE_PMID(kWidgetIDSpace, kLinkHeaderNameTextWidgetID, kLinksUIPrefix + 98)
DECLARE_PMID(kWidgetIDSpace, kCCRelinkButtonWidgetID, kLinksUIPrefix + 99)
DECLARE_PMID(kWidgetIDSpace, kAALRelinkButtonWidgetID, kLinksUIPrefix + 100)
DECLARE_PMID(kWidgetIDSpace, kRelinkWidgetsWithoutAALID, kLinksUIPrefix + 101)
DECLARE_PMID(kWidgetIDSpace, kRelinkWidgetsWithAALID, kLinksUIPrefix + 102)

// <Message ID>
DECLARE_PMID(kMessageIDSpace, kPendingDocumentsClosedMsg, kLinksUIPrefix + 6)

// <Interface ID>
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKSUIPANELPREFS, kLinksUIPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ITOTALINFOAREAHEIGHT, kLinksUIPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IEDITORIGINALRESUMEOBSERVER, kLinksUIPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IFILESCHANGING, kLinksUIPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKSUIUTILS, kLinksUIPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKSTREENODELIST, kLinksUIPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IMISSINGCOUNT, kLinksUIPrefix + 7) // IID_INTDATA
DECLARE_PMID(kInterfaceIDSpace, IID_IOUTOFDATECOUNT, kLinksUIPrefix + 8) // IID_INTDATA
DECLARE_PMID(kInterfaceIDSpace, IID_IFIXLINKS, kLinksUIPrefix + 9) // IID_IBOOLDATA
DECLARE_PMID(kInterfaceIDSpace, IID_IFIXLINKSSELECTED, kLinksUIPrefix + 10) // IID_IBOOLDATA
DECLARE_PMID(kInterfaceIDSpace, IID_LINKSPANELDRAWINGDISABLED, kLinksUIPrefix + 11) // IID_IBOOLDATA
DECLARE_PMID(kInterfaceIDSpace, IID_LINKINFOPROVIDERINDEX, kLinksUIPrefix + 12) // IID_IINTDATA
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKSROWELEMENTCURSORPROVIDER, kLinksUIPrefix + 13) 
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IINACCESSIBLECOUNT, kLinksUIPrefix + 15) 
DECLARE_PMID(kInterfaceIDSpace, IID_IDYNAMICLINKINFOCHANGE, kLinksUIPrefix + 16)  // message protocol only
DECLARE_PMID(kInterfaceIDSpace, IID_ISAVEDINFOPANESIZE, kLinksUIPrefix + 17) // IID_IINTDATA
DECLARE_PMID(kInterfaceIDSpace, IID_LINKSPANELSHOULDINVALDATA, kLinksUIPrefix + 18) // IID_IBOOLDATA
DECLARE_PMID(kInterfaceIDSpace, IID_IALTEVEINFO, kLinksUIPrefix + 19) // IID_IEVEINFO
DECLARE_PMID(kInterfaceIDSpace, IID_IHTTPLINKS, kLinksUIPrefix + 20) // IID_IEVEINFO

// <Action ID>
// Action IDs
DECLARE_PMID(kActionIDSpace, kLinksUIPanelActionID, kLinksUIPrefix + 1)
DECLARE_PMID(kActionIDSpace, kLinksUIUpdateLinkActionID, kLinksUIPrefix + 2)
DECLARE_PMID(kActionIDSpace, kLinksUIEmbedLinkActionID, kLinksUIPrefix + 3)
DECLARE_PMID(kActionIDSpace, kLinksUICopyPlatformPathActionID, kLinksUIPrefix + 4)
DECLARE_PMID(kActionIDSpace, kLinksUIEditOriginalActionID, kLinksUIPrefix + 5)
DECLARE_PMID(kActionIDSpace, kLinksUIEditColumnsActionID, kLinksUIPrefix + 6)
DECLARE_PMID(kActionIDSpace, kCopyLinksActionID, kLinksUIPrefix + 7)
DECLARE_PMID(kActionIDSpace, kAutosizeLinkInfoActionID, kLinksUIPrefix + 8)
DECLARE_PMID(kActionIDSpace, kShowHideLinkInfoActionID, kLinksUIPrefix + 9)
DECLARE_PMID(kActionIDSpace, kCopyAllLinkInfoActionID, kLinksUIPrefix + 10)
DECLARE_PMID(kActionIDSpace, kGenerateLinkReportActionID, kLinksUIPrefix + 11)
DECLARE_PMID(kActionIDSpace, kRevealLinkInOSSelectionActionID, kLinksUIPrefix + 12)
DECLARE_PMID(kActionIDSpace, kLinksUIPanelMenuSepActionID, kLinksUIPrefix + 13)
DECLARE_PMID(kActionIDSpace, kLinksUIPanelFileXMPInfoActionID, kLinksUIPrefix + 14)
DECLARE_PMID(kActionIDSpace, kLinksUICopyPathActionID, kLinksUIPrefix + 15)
DECLARE_PMID(kActionIDSpace, kEditOriginalOtherAppActionID, kLinksUIPrefix + 16)
DECLARE_PMID(kActionIDSpace, kEditOriginalSepActionID, kLinksUIPrefix + 17)
DECLARE_PMID(kActionIDSpace, kEditOriginalOtherAppSepActionID, kLinksUIPrefix + 18)
DECLARE_PMID(kActionIDSpace, kEditOriginalWithActionID, kLinksUIPrefix + 19)
DECLARE_PMID(kActionIDSpace, kEditOriginalSelectionWithActionID, kLinksUIPrefix + 20)
DECLARE_PMID(kActionIDSpace, kGotoLinkActionID, kLinksUIPrefix + 21)
DECLARE_PMID(kActionIDSpace, kRevealLinkInOSActionID, kLinksUIPrefix + 22)
DECLARE_PMID(kActionIDSpace, kRevealLinkInBridgeActionID, kLinksUIPrefix + 23)
DECLARE_PMID(kActionIDSpace, kLinksUIRemoveColumnActionID, kLinksUIPrefix + 24)
DECLARE_PMID(kActionIDSpace, kUpdateAllOutOfDateLinksActionID, kLinksUIPrefix + 25)
DECLARE_PMID(kActionIDSpace, kAutoFindAllMissingLinksActionID, kLinksUIPrefix + 26)   // used as id for dont show again alert, and also as a real ActionID
DECLARE_PMID(kActionIDSpace, kLinksUIHideShowInfoThumbnailActionID, kLinksUIPrefix + 27)
DECLARE_PMID(kActionIDSpace, kLinksUIHideShowThumbnailActionID, kLinksUIPrefix + 28)
DECLARE_PMID(kActionIDSpace, kLinksUIRelinkActionID, kLinksUIPrefix + 29)
DECLARE_PMID(kActionIDSpace, kLinksUIPanelMenuSep1ActionID, kLinksUIPrefix + 30)
DECLARE_PMID(kActionIDSpace, kLinksUIPanelMenuSep2ActionID, kLinksUIPrefix + 31)
DECLARE_PMID(kActionIDSpace, kLinksUIPanelMenuSep3ActionID, kLinksUIPrefix + 32)
DECLARE_PMID(kActionIDSpace, kLinksUIPanelMenuSep4ActionID, kLinksUIPrefix + 33)
DECLARE_PMID(kActionIDSpace, kGenerateCaptionPrefsDialogActionID, kLinksUIPrefix + 34)
DECLARE_PMID(kActionIDSpace, kGenerateLiveCaptionForLinkActionID, kLinksUIPrefix + 35)
DECLARE_PMID(kActionIDSpace, kGenerateLiveCaptionForLinkSelectionActionID, kLinksUIPrefix + 36)
DECLARE_PMID(kActionIDSpace, kRevealLinkInBridgeSelectionActionID, kLinksUIPrefix + 37)
DECLARE_PMID(kActionIDSpace, kEditOriginalLayoutSelectionActionID, kLinksUIPrefix + 38)
DECLARE_PMID(kActionIDSpace, kLinksUIRelinkToFolderActionID, kLinksUIPrefix + 39)
DECLARE_PMID(kActionIDSpace, kSearchFoundLinksAlertMsgActionID, kLinksUIPrefix + 40) // used as id for dont show again alert
DECLARE_PMID(kActionIDSpace, kCopySingleLinkInfoFieldActionID, kLinksUIPrefix + 41)
DECLARE_PMID(kActionIDSpace, kLinksUIRelinkFileExtensionActionID, kLinksUIPrefix + 42)
DECLARE_PMID(kActionIDSpace, kGenerateStaticCaptionForLinkSelectionActionID, kLinksUIPrefix + 43)
DECLARE_PMID(kActionIDSpace, kGenerateStaticCaptionForLinkActionID, kLinksUIPrefix + 44)
//gap
DECLARE_PMID(kActionIDSpace, kConvertLiveCaptionToTextActionID, kLinksUIPrefix + 47)

DECLARE_PMID(kActionIDSpace, kLinksUIGoToSourceActionID, kLinksUIPrefix + 48)
DECLARE_PMID(kActionIDSpace, kGoToSourceLayoutSelectionActionID, kLinksUIPrefix + 49)
DECLARE_PMID(kActionIDSpace, kRevealLinkInCloudLibrariesActionID, kLinksUIPrefix + 50)
DECLARE_PMID(kActionIDSpace, kRevealLinkInCloudLibrariesSelectionActionID, kLinksUIPrefix + 51)
DECLARE_PMID(kActionIDSpace, kLinksUIRelinkToCloudAssetActionID, kLinksUIPrefix + 52)
DECLARE_PMID(kActionIDSpace, kLicenseStockAssetActionID, kLinksUIPrefix + 53)
DECLARE_PMID(kActionIDSpace, kRelinkAssetFromPropsPanelActionID, kLinksUIPrefix + 54)
DECLARE_PMID(kActionIDSpace, kEmbedLinkFromPropsPanelActionID, kLinksUIPrefix + 55)
DECLARE_PMID(kActionIDSpace, kUpdateLinkFromPropsPanelActionID, kLinksUIPrefix + 56)
DECLARE_PMID(kActionIDSpace, kUnlinkFromPropPanelActionID, kLinksUIPrefix + 57)
DECLARE_PMID(kActionIDSpace, kLinksUIRelinkToAALAssetActionID, kLinksUIPrefix + 58)
DECLARE_PMID(kActionIDSpace, kReplaceFPOWithOriginalLinkActionID, kLinksUIPrefix + 59)
DECLARE_PMID(kActionIDSpace, kReplaceAllFPOWithOriginalLinksActionID, kLinksUIPrefix + 60)
DECLARE_PMID(kActionIDSpace, kDownloadOriginalLinkActionID, kLinksUIPrefix + 61)
DECLARE_PMID(kActionIDSpace, kDownloadAllOriginalLinksActionID, kLinksUIPrefix + 62)
DECLARE_PMID(kActionIDSpace, kLinksUIPanelMenuSep5ActionID, kLinksUIPrefix + 63)

//gap

// Reserved for the dynamic Edit Original With menu items 150 - 255 (2 dynamic menus, 52 items each, one operates on a link, the other on the layout selection)
DECLARE_PMID(kActionIDSpace, kEditOriginalWithStartID,			kLinksUIPrefix + 150)
DECLARE_PMID(kActionIDSpace, kEditOriginalWithEndID,				kLinksUIPrefix + 202)
DECLARE_PMID(kActionIDSpace, kEditOriginalSelectionWithStartID,		kLinksUIPrefix + 203)
DECLARE_PMID(kActionIDSpace, kEditOriginalSelectionWithEndID,		kLinksUIPrefix + 255)

// <Error ID>
DECLARE_PMID(kErrorIDSpace, kCaptionLayerLockedError, kLinksUIPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kGenerateCaptionError, kLinksUIPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kCaptionCantCreateGroupError, kLinksUIPrefix + 3)

// ----- Tree Node ID types -----
#define kLinkTreeNodeID		kLinksUIPrefix + 1

const int32 kRootDocumentLinksNodeUID = -1;

#endif // __LinksUIID__

