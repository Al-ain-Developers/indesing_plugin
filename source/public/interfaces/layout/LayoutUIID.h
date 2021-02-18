//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/LayoutUIID.h $
//  
//  Owner: Robin_Briggs
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
//  Contains IDs used by the Layout Widget plug-in
//  
//========================================================================================

#ifndef __LayoutUIID_h__
#define __LayoutUIID_h__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kLayoutUIPrefix	 RezLong(0x1d000)
#define kLayoutUI2Prefix RezLong(0x1b800)

// <Start IDC>
// PluginID
#define kLayoutUIPluginName 			"Layout UI"
DECLARE_PMID(kPlugInIDSpace, kLayoutUIPluginID, kLayoutUIPrefix + 1)


// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kLayoutPresentationBoss, kLayoutUIPrefix + 1) // CS4/OWL2 Note: replaces kLayoutWindowBoss
DECLARE_PMID(kClassIDSpace, kGotoPageComboBoxWidgetBoss, kLayoutUIPrefix + 2)
DECLARE_PMID(kClassIDSpace, kLayoutWidgetBoss, kLayoutUIPrefix + 3)
DECLARE_PMID(kClassIDSpace, kLayoutPanelBoss, kLayoutUIPrefix + 4)
DECLARE_PMID(kClassIDSpace, kScrollToSelectionCmdBoss, kLayoutUIPrefix + 5)
DECLARE_PMID(kClassIDSpace, kInvalShapeBoss, kLayoutUIPrefix + 6)		// not a real class ID, just used for messaging
DECLARE_PMID(kClassIDSpace, kZeroPointWidgetBoss, kLayoutUIPrefix + 7)
DECLARE_PMID(kClassIDSpace, kPathSelectionBoss, kLayoutUIPrefix + 8)
DECLARE_PMID(kClassIDSpace, kParentChildFilterBoss, kLayoutUIPrefix + 9)
DECLARE_PMID(kClassIDSpace, kScaleDlgHeightEditBoxWidgetBoss, kLayoutUIPrefix + 10)
DECLARE_PMID(kClassIDSpace, kScaleDlgWidthEditBoxWidgetBoss, kLayoutUIPrefix + 11)
DECLARE_PMID(kClassIDSpace, kRotateTrackerBoss, kLayoutUIPrefix + 12)
DECLARE_PMID(kClassIDSpace, kPointerTrackerBoss, kLayoutUIPrefix + 13)
DECLARE_PMID(kClassIDSpace, kResizeTrackerBoss, kLayoutUIPrefix + 14)
DECLARE_PMID(kClassIDSpace, kMoveTrackerBoss, kLayoutUIPrefix + 15)
DECLARE_PMID(kClassIDSpace, kPointerToolBoss, kLayoutUIPrefix + 16)
DECLARE_PMID(kClassIDSpace, kRotateToolBoss, kLayoutUIPrefix + 17)
DECLARE_PMID(kClassIDSpace, kResizeToolBoss, kLayoutUIPrefix + 18)
DECLARE_PMID(kClassIDSpace, kMoveToolBoss, kLayoutUIPrefix + 19)
DECLARE_PMID(kClassIDSpace, kPathResizeToolBoss, kLayoutUIPrefix + 20)
DECLARE_PMID(kClassIDSpace, kBBoxResizeTrackerBoss, kLayoutUIPrefix + 21)
DECLARE_PMID(kClassIDSpace, kDirectSelectToolBoss, kLayoutUIPrefix + 22)
DECLARE_PMID(kClassIDSpace, kObjectSelectToolBoss, kLayoutUIPrefix + 23)
DECLARE_PMID(kClassIDSpace, kScrollToPointCmdBoss, kLayoutUIPrefix + 24)
DECLARE_PMID(kClassIDSpace, kDirectSelectTrackerBoss, kLayoutUIPrefix + 25)
DECLARE_PMID(kClassIDSpace, kObjectSelectTrackerBoss, kLayoutUIPrefix + 26)
DECLARE_PMID(kClassIDSpace, kGroupSelectTrackerBoss, kLayoutUIPrefix + 27)
DECLARE_PMID(kClassIDSpace, kOpenLayoutCmdBoss, kLayoutUIPrefix + 28)  // CS4/OWL2 Note: was kOpenLayoutWinCmdBoss, renamed since data interface has changed
DECLARE_PMID(kClassIDSpace, kVisibilityHitDrawEventServicesBoss, kLayoutUIPrefix + 29) 
DECLARE_PMID(kClassIDSpace, kLayoutScrollBarWidgetBoss, kLayoutUIPrefix + 30)
DECLARE_PMID(kClassIDSpace, kScrollBarLayoutSyncBoss, kLayoutUIPrefix + 31)
DECLARE_PMID(kClassIDSpace, kBackGroundOffscreenBoss, kLayoutUIPrefix + 32)
DECLARE_PMID(kClassIDSpace, kRotateDialogBoss, kLayoutUIPrefix + 33)
DECLARE_PMID(kClassIDSpace, kMoveDialogBoss, kLayoutUIPrefix + 34)
DECLARE_PMID(kClassIDSpace, kZoomComponentBoss, kLayoutUIPrefix + 35)
DECLARE_PMID(kClassIDSpace, kImageProcessingIdleTaskBoss, kLayoutUIPrefix + 36)
DECLARE_PMID(kClassIDSpace, kGrabberHandToolBoss, kLayoutUIPrefix + 37)
DECLARE_PMID(kClassIDSpace, kGrabberHandTrackerBoss, kLayoutUIPrefix + 38)
DECLARE_PMID(kClassIDSpace, kHiddenLockedFilterBoss, kLayoutUIPrefix + 39)
DECLARE_PMID(kClassIDSpace, kZeroPointTrackerBoss, kLayoutUIPrefix + 40)
DECLARE_PMID(kClassIDSpace, kZeroPointTrackerRegisterBoss, kLayoutUIPrefix + 41)
DECLARE_PMID(kClassIDSpace, kLayoutUIActionBoss, kLayoutUIPrefix + 42)
DECLARE_PMID(kClassIDSpace, kLayoutKeyboardShortcutsBoss, kLayoutUIPrefix + 43)
DECLARE_PMID(kClassIDSpace, kFitPageItemInWindowCmdBoss, kLayoutUIPrefix + 44)
DECLARE_PMID(kClassIDSpace, kNoShadowCBDropDownWidgetBoss, kLayoutUIPrefix + 45)
DECLARE_PMID(kClassIDSpace, kNoShadowCBEditBoxWidgetBoss, kLayoutUIPrefix + 46)
DECLARE_PMID(kClassIDSpace, kScaleDialogBoss, kLayoutUIPrefix + 47)
DECLARE_PMID(kClassIDSpace, kShearDialogBoss, kLayoutUIPrefix + 48)
DECLARE_PMID(kClassIDSpace, kSetPreviewPrefsCmdBoss, kLayoutUIPrefix + 49)
DECLARE_PMID(kClassIDSpace, kGotoPageDialogBoss, kLayoutUIPrefix + 50)
DECLARE_PMID(kClassIDSpace, kSelectionTestMenuBoss, kLayoutUIPrefix + 51)	// DEBUG
DECLARE_PMID(kClassIDSpace, kGenericItemMoveTrackerBoss, kLayoutUIPrefix + 52)
DECLARE_PMID(kClassIDSpace, kMoveReferencePointCmdBoss, kLayoutUIPrefix + 53)
DECLARE_PMID(kClassIDSpace, kReferencePointTrackerBoss, kLayoutUIPrefix + 54)
DECLARE_PMID(kClassIDSpace, kReferencePointTrackerRegisterBoss, kLayoutUIPrefix + 55)
DECLARE_PMID(kClassIDSpace, kReferencePointDrawServicesBoss, kLayoutUIPrefix + 56)
DECLARE_PMID(kClassIDSpace, kScaleTrackerBoss, kLayoutUIPrefix + 57)
DECLARE_PMID(kClassIDSpace, kScaleToolBoss, kLayoutUIPrefix + 58)
DECLARE_PMID(kClassIDSpace, kLayoutSelectionTrackerBoss, kLayoutUIPrefix + 59)
DECLARE_PMID(kClassIDSpace, kLockTrackerBoss, kLayoutUIPrefix + 60)
DECLARE_PMID(kClassIDSpace, kScaleStatusWidgetBoss, kLayoutUIPrefix + 61)
DECLARE_PMID(kClassIDSpace, kPageNavigateWidgetBoss, kLayoutUIPrefix + 62)
DECLARE_PMID(kClassIDSpace, kPageNavigateComboBoxWidgetBoss, kLayoutUIPrefix + 63)
DECLARE_PMID(kClassIDSpace, kFirstPageWidgetBoss, kLayoutUIPrefix + 64)
DECLARE_PMID(kClassIDSpace, kLastPageWidgetBoss, kLayoutUIPrefix + 65)
DECLARE_PMID(kClassIDSpace, kPageNumForwardWidgetBoss, kLayoutUIPrefix + 66)
DECLARE_PMID(kClassIDSpace, kPageNumBackwardWidgetBoss, kLayoutUIPrefix + 67)
DECLARE_PMID(kClassIDSpace, kShearToolBoss, kLayoutUIPrefix + 68)
DECLARE_PMID(kClassIDSpace, kShearTrackerBoss, kLayoutUIPrefix + 69)
DECLARE_PMID(kClassIDSpace, kShearTrackerRegisterBoss, kLayoutUIPrefix + 70)
DECLARE_PMID(kClassIDSpace, kGenericItemResizeTrackerBoss, kLayoutUIPrefix + 71)
DECLARE_PMID(kClassIDSpace, kTransformMenuActionBoss, kLayoutUIPrefix + 72)
DECLARE_PMID(kClassIDSpace, kDV_NoShadowCBDropDownWidgetBoss, kLayoutUIPrefix + 73)
DECLARE_PMID(kClassIDSpace, kDV_PageNavNoShadowCBDropDownWidgetBoss, kLayoutUIPrefix + 74)
//gap
DECLARE_PMID(kClassIDSpace, kScaleDlgEditBoxWidgetBoss, kLayoutUIPrefix + 76)
DECLARE_PMID(kClassIDSpace, kLayoutStartupServiceBoss, kLayoutUIPrefix + 77)
DECLARE_PMID(kClassIDSpace, kDrawingToolBoss, kLayoutUIPrefix + 78)
DECLARE_PMID(kClassIDSpace, kDrawingTrackerBoss, kLayoutUIPrefix + 79)
DECLARE_PMID(kClassIDSpace, kZeroPointComponentBoss, kLayoutUIPrefix + 80)
DECLARE_PMID(kClassIDSpace, kSetDefaultRefPointPositionCmdBoss, kLayoutUIPrefix + 81)
DECLARE_PMID(kClassIDSpace, kLayoutDDSrcPageItemHelperBoss, kLayoutUIPrefix + 82)
DECLARE_PMID(kClassIDSpace, kSetGrabberPrefsCmdBoss, kLayoutUIPrefix + 83)
DECLARE_PMID(kClassIDSpace, kGrabberPrefsScriptProviderBoss, kLayoutUIPrefix + 84)
DECLARE_PMID(kClassIDSpace, kLayoutDDTargetSwatchFlavorHelperBoss, kLayoutUIPrefix + 85)
DECLARE_PMID(kClassIDSpace, kLayoutDDTargetSpreadFlavorHelperBoss, kLayoutUIPrefix + 86)
DECLARE_PMID(kClassIDSpace, kLayoutDDTargetFileFlavorHelperBoss, kLayoutUIPrefix + 87)
DECLARE_PMID(kClassIDSpace, kLayoutDDTargetPageItemFlavorHelperBoss, kLayoutUIPrefix + 88)
DECLARE_PMID(kClassIDSpace, kNormalViewModeToolBoss, kLayoutUIPrefix + 89)
DECLARE_PMID(kClassIDSpace, kPreviewModeToolBoss, kLayoutUIPrefix +90)
DECLARE_PMID(kClassIDSpace, kPreviewNonPrintDrawHandlerBoss, kLayoutUIPrefix + 91)
DECLARE_PMID(kClassIDSpace, kOpenLayoutSignalBoss, kLayoutUIPrefix +92)   // CS4/OWL2 Note: was kOpenLayoutWinSignalBoss, renamed since data interface has changed
DECLARE_PMID(kClassIDSpace, kBleedModeToolBoss, kLayoutUIPrefix + 93)
DECLARE_PMID(kClassIDSpace, kSlugModeToolBoss, kLayoutUIPrefix + 94)
DECLARE_PMID(kClassIDSpace, kTextBBoxResizeTrackerBoss, kLayoutUIPrefix + 95)
DECLARE_PMID(kClassIDSpace, kLayoutGenericPanelBoss, kLayoutUIPrefix + 96)
DECLARE_PMID(kClassIDSpace, kPageNavNoShadowCBDropDownWidgetBoss, kLayoutUIPrefix + 97)
DECLARE_PMID(kClassIDSpace, kImageTrackerRegisterBoss, kLayoutUIPrefix + 98)
DECLARE_PMID(kClassIDSpace, kEPSTrackerRegisterBoss, kLayoutUIPrefix  + 99)
DECLARE_PMID(kClassIDSpace, kGuideCreationTrackerBoss, kLayoutUIPrefix + 100)
DECLARE_PMID(kClassIDSpace, kGuideMoveTrackerBoss, kLayoutUIPrefix + 101)
DECLARE_PMID(kClassIDSpace, kGuideTrackerRegisterBoss, kLayoutUIPrefix + 102)
DECLARE_PMID(kClassIDSpace, kGuideLayoutActionBoss, kLayoutUIPrefix + 103)
DECLARE_PMID(kClassIDSpace, kGuideSelectionFilterBoss, kLayoutUIPrefix + 104)
DECLARE_PMID(kClassIDSpace, kGuidesGuideKeyShortcutsBoss, kLayoutUIPrefix + 105)
DECLARE_PMID(kClassIDSpace, kGuideOptionsDialogBoss, kLayoutUIPrefix + 106)
DECLARE_PMID(kClassIDSpace, kScaleAndNavigatePanelWidgetBoss, kLayoutUIPrefix + 107)
DECLARE_PMID(kClassIDSpace, kPasteGuideCmdBoss, kLayoutUIPrefix + 108)
DECLARE_PMID(kClassIDSpace, kMasterListLayoutActionBoss, kLayoutUIPrefix + 109)
DECLARE_PMID(kClassIDSpace, kMasterPageLayoutActionBoss, kLayoutUIPrefix + 110)
DECLARE_PMID(kClassIDSpace, kPageItemDDTargetSwatchHelperBoss, kLayoutUIPrefix + 111)
DECLARE_PMID(kClassIDSpace, kZOrderLabelTestMenuBoss, kLayoutUIPrefix + 112)	// DEBUG
DECLARE_PMID(kClassIDSpace, kZOrderLabelDrwEvtHandlerBoss, kLayoutUIPrefix + 113)	// DEBUG
DECLARE_PMID(kClassIDSpace, kCenterItemsInViewCmdBoss, kLayoutUIPrefix + 114)
DECLARE_PMID(kClassIDSpace, kPlacePITrackerBoss, kLayoutUIPrefix + 115)
DECLARE_PMID(kClassIDSpace, kVisibilityBoss, kLayoutUIPrefix + 116)
DECLARE_PMID(kClassIDSpace, kPresentationModeToolBoss, kLayoutUIPrefix + 117)
DECLARE_PMID(kClassIDSpace, kSolidGroupHitTestHandlerBoss, kLayoutUIPrefix + 118)
DECLARE_PMID(kClassIDSpace, kSolidMPDDHitTestHandlerBoss, kLayoutUIPrefix + 119)
DECLARE_PMID(kClassIDSpace, kPtrHitTestHandlerBoss, kLayoutUIPrefix + 120)
DECLARE_PMID(kClassIDSpace, kPtrOMPHitTestHandlerBoss, kLayoutUIPrefix + 121)
DECLARE_PMID(kClassIDSpace, kDirSelHitTestHandlerBoss, kLayoutUIPrefix + 122)
DECLARE_PMID(kClassIDSpace, kDirSelOMPHitTestHandlerBoss, kLayoutUIPrefix + 123)
DECLARE_PMID(kClassIDSpace, kSolidHitTestHandlerBoss, kLayoutUIPrefix + 124)
DECLARE_PMID(kClassIDSpace, kSolidTOPHitTestHandlerBoss, kLayoutUIPrefix + 125)
DECLARE_PMID(kClassIDSpace, kSolidTOPMPHitTestHandlerBoss, kLayoutUIPrefix + 126)
DECLARE_PMID(kClassIDSpace, kTOPOnlyPathHitTestHandlerBoss, kLayoutUIPrefix + 127)
DECLARE_PMID(kClassIDSpace, kDirSelMPLLHitTestHandlerBoss, kLayoutUIPrefix + 128)
DECLARE_PMID(kClassIDSpace, kDirSelMPHitTestHandlerBoss, kLayoutUIPrefix + 129)
DECLARE_PMID(kClassIDSpace, kSolidTOPLLHitTestHandlerBoss, kLayoutUIPrefix + 130)
DECLARE_PMID(kClassIDSpace, kSolidMPHitTestHandlerBoss, kLayoutUIPrefix + 131)
DECLARE_PMID(kClassIDSpace, kSolidMPLLHitTestHandlerBoss, kLayoutUIPrefix + 132)
DECLARE_PMID(kClassIDSpace, kPtrSolidTOPOMPHitTestHandlerBoss, kLayoutUIPrefix + 133)
DECLARE_PMID(kClassIDSpace, kGroupHitTestHandlerBoss, kLayoutUIPrefix + 134)
DECLARE_PMID(kClassIDSpace, kDirSelGroupHitTestHandlerBoss, kLayoutUIPrefix + 135)
DECLARE_PMID(kClassIDSpace, kSolidTOPOMPHitTestHandlerBoss, kLayoutUIPrefix + 136)
DECLARE_PMID(kClassIDSpace, kSelectionHitTestHandlerBoss, kLayoutUIPrefix + 137 )
DECLARE_PMID(kClassIDSpace, kDirSelNoGuidesHitTestHandlerBoss, kLayoutUIPrefix + 138 )
DECLARE_PMID(kClassIDSpace, kPageItemActionHitTestHandlerBoss, kLayoutUIPrefix + 139 )
DECLARE_PMID(kClassIDSpace, kGenericTrackerRegisterBoss, kLayoutUIPrefix + 140)
DECLARE_PMID(kClassIDSpace, kArrangeBoss, kLayoutUIPrefix + 141)
DECLARE_PMID(kClassIDSpace, kAlignComponentBoss, kLayoutUIPrefix + 142)
DECLARE_PMID(kClassIDSpace, kStrokeWeightBoss, kLayoutUIPrefix + 143)
DECLARE_PMID(kClassIDSpace, kFillTintBoss, kLayoutUIPrefix + 144 )
DECLARE_PMID(kClassIDSpace, kSelectBoss, kLayoutUIPrefix + 145)
DECLARE_PMID(kClassIDSpace, kObjectSizeKBSCBoss, kLayoutUIPrefix + 146)
DECLARE_PMID(kClassIDSpace, kFrameBoss, kLayoutUIPrefix + 147)
DECLARE_PMID(kClassIDSpace, kLockBoss, kLayoutUIPrefix + 148)
DECLARE_PMID(kClassIDSpace, kGroupComponentBoss, kLayoutUIPrefix + 149)
DECLARE_PMID(kClassIDSpace, kCrossSpreadSelectionFilterBoss, kLayoutUIPrefix + 150)
DECLARE_PMID(kClassIDSpace, kGroupTrackerRegisterBoss, kLayoutUIPrefix + 151)
DECLARE_PMID(kClassIDSpace, kGroupAlertDialogBoss, kLayoutUIPrefix + 152)
DECLARE_PMID(kClassIDSpace, kGroupOverrideableAlertDialogBoss, kLayoutUIPrefix + 153)
DECLARE_PMID(kClassIDSpace, kScriptLayoutObserverBoss, kLayoutUIPrefix + 154)
DECLARE_PMID(kClassIDSpace, kOversetLineCountTestMenuBoss, kLayoutUIPrefix + 155)
DECLARE_PMID(kClassIDSpace, kPageNavCBDropDownWidgetBoss, kLayoutUIPrefix + 156)
DECLARE_PMID(kClassIDSpace, kToggleSplitWindowButtonBoss, kLayoutUIPrefix + 157)
DECLARE_PMID(kClassIDSpace, kMatchPasteBoardToThemeColorMenuActionBoss, kLayoutUIPrefix + 158)
DECLARE_PMID(kClassIDSpace, kDirSelExceptSplinesHitTestHandlerBoss, kLayoutUIPrefix + 159)
DECLARE_PMID(kClassIDSpace, kDirSelExceptSplinesLLHitTestHandlerBoss, kLayoutUIPrefix + 160)
DECLARE_PMID(kClassIDSpace, kSolidLLHitTestHandlerBoss, kLayoutUIPrefix + 161)

//gap
DECLARE_PMID(kClassIDSpace, kPageResizeTrackerBoss, kLayoutUIPrefix + 162)
DECLARE_PMID(kClassIDSpace, kDocStatusMenuWidgetBoss, kLayoutUIPrefix + 163)
DECLARE_PMID(kClassIDSpace, kDocStatusMenuActionBoss, kLayoutUIPrefix + 164)
DECLARE_PMID(kClassIDSpace, kScreenViewMenuActionBoss, kLayoutUIPrefix + 165)
DECLARE_PMID(kClassIDSpace, kMasterPageHitTestServicesBoss, kLayoutUIPrefix + 166)
DECLARE_PMID(kClassIDSpace, kMasterPageInvalServicesBoss, kLayoutUIPrefix + 167)
//gap
DECLARE_PMID(kClassIDSpace, kUpdateDocumentUIStateCmdBoss, kLayoutUIPrefix + 170)  // CS4/OWL2 Note: was kUpdateDocWindowStateCmdBoss
DECLARE_PMID(kClassIDSpace, kSpreadSelectionBoss, kLayoutUIPrefix + 171) //SpreadSelectionSuite
DECLARE_PMID(kClassIDSpace, kSpreadSuiteBoss, kLayoutUIPrefix + 172) //SpreadSelectionSuite
DECLARE_PMID(kClassIDSpace, kSpreadSelectionServiceBoss, kLayoutUIPrefix + 173) //SpreadSelectionSuite
DECLARE_PMID(kClassIDSpace, kLiveShapeToolBoss, kLayoutUIPrefix + 174) /* This is not a real boss, just a value to get to the PrePlaceTracker */ 
DECLARE_PMID(kClassIDSpace, kLiveShapeCornerToolBoss, kLayoutUIPrefix + 175) /* This is not a real boss, just a value to get to the PrePlaceTracker */ 
DECLARE_PMID(kClassIDSpace, kLiveModeEnableTrackerBoss, kLayoutUIPrefix + 176)
DECLARE_PMID(kClassIDSpace, kLiveCornerAdornmentTrackerBoss, kLayoutUIPrefix + 177)
//gap
// gap
DECLARE_PMID(kClassIDSpace, kIDGPUSnifferStartupServiceBoss, kLayoutUIPrefix + 183)
DECLARE_PMID(kClassIDSpace, kStockTrackerBoss, kLayoutUIPrefix + 184)
DECLARE_PMID(kClassIDSpace, kStockTrackerRegisterBoss, kLayoutUIPrefix + 185)

//gap
DECLARE_PMID(kClassIDSpace, kLayoutOpenGLWidgetBoss, kLayoutUIPrefix + 186)
DECLARE_PMID(kClassIDSpace, kPlacedStockAssetBoss, kLayoutUIPrefix + 187)/* This is not a real boss, just a value to get StockTracker */
DECLARE_PMID(kClassIDSpace, kSeperatorToolBoss, kLayoutUIPrefix + 188)
DECLARE_PMID(kClassIDSpace, kViewOptionsToolBoss, kLayoutUIPrefix + 189)
DECLARE_PMID(kClassIDSpace, kViewOptionsPopoutCellBoss, kLayoutUIPrefix + 190)
DECLARE_PMID(kClassIDSpace, kViewOptionsToolPopupWindowBoss, kLayoutUIPrefix + 191)
DECLARE_PMID(kClassIDSpace, kViewOptionsPanelBoss, kLayoutUIPrefix + 192)

//gap

// -- these are not really classes! just messages!
// <Message ID>
// Message IDs (start at 200)
#define kLayoutMsgPrefix					(kLayoutUIPrefix + 200)
DECLARE_PMID(kMessageIDSpace, kReferencePointChangedMessage, kLayoutMsgPrefix + 0)
DECLARE_PMID(kMessageIDSpace, kSuspendMessage, kLayoutMsgPrefix + 1)	// i.e. sent by the PageItemFocus::Suspend() at the current Selection, received by CJK.
DECLARE_PMID(kMessageIDSpace, kResumeMessage, kLayoutMsgPrefix + 2)	// i.e. sent by the PageItemFocus::Resume() at the current Selection, received by CJK.
DECLARE_PMID(kMessageIDSpace, kActivateMessage, kLayoutMsgPrefix + 3)
DECLARE_PMID(kMessageIDSpace, kDeactivateMessage, kLayoutMsgPrefix + 4)
DECLARE_PMID(kMessageIDSpace, kLayoutTrackerRegisterBossMessage, kLayoutMsgPrefix + 5)
DECLARE_PMID(kMessageIDSpace, kEndOfMoveMessage, kLayoutMsgPrefix + 6)
DECLARE_PMID(kMessageIDSpace, kStartOfMoveMessage, kLayoutMsgPrefix + 7)
DECLARE_PMID(kMessageIDSpace, kPathSelectionModeChangedMessage, kLayoutMsgPrefix + 8			)
DECLARE_PMID(kMessageIDSpace, kBeginTrackingMessage, kLayoutMsgPrefix + 9)
DECLARE_PMID(kMessageIDSpace, kUpdateButtonMessage, kLayoutMsgPrefix + 10)
DECLARE_PMID(kMessageIDSpace, kActiveSpreadChangedMsg, kLayoutMsgPrefix + 11)
DECLARE_PMID(kMessageIDSpace, kActiveLayerChangedMsg, kLayoutMsgPrefix + 12)
DECLARE_PMID(kMessageIDSpace, kInvalidateContentIndicatorMsg, kLayoutMsgPrefix + 13)
DECLARE_PMID(kMessageIDSpace, kTrackingCompleteMessage, kLayoutMsgPrefix + 14)	// Broadcast on the document subject with IID_ITRACKER protocol
DECLARE_PMID(kMessageIDSpace, kDroppedItemGeometryChangeMessage, kLayoutMsgPrefix + 15)
// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IPATHSELECTIONDATA, kLayoutUIPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ISNAPTOINVALHANDLERHELPER, kLayoutUIPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IINVALSHAPE, kLayoutUIPrefix + 3)		// just used for messaging
DECLARE_PMID(kInterfaceIDSpace, IID_IPATHSELECTION, kLayoutUIPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IDURINGCLOSELAYOUTWINDOW, kLayoutUIPrefix + 5)	// DEBUG
DECLARE_PMID(kInterfaceIDSpace, IID_ISTEPREPEATTOUTPUTDATA, kLayoutUIPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTHIERARCHYOBSERVER, kLayoutUIPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTPAGEITEMOBSERVER, kLayoutUIPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IBACKGROUNDOFFSCREENCHANGED, kLayoutUIPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTVIEWRESPONDER, kLayoutUIPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IINVALHANDLESHAPE, kLayoutUIPrefix + 11)		// just used for messaging
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTCONTROLDATA, kLayoutUIPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTVIEWMGR, kLayoutUIPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRABBERPREFS, kLayoutUIPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IVIEW, kLayoutUIPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IVIEWRESPONDER, kLayoutUIPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTCONTROLVIEWHELPER, kLayoutUIPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTTOOLBOXOBSERVER, kLayoutUIPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_IMOVETRACKERDATA, kLayoutUIPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_IPLACEPISPRITEDATA, kLayoutUIPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTIONFILTER, kLayoutUIPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_IPATHSELECTIONDOCOBSERVER, kLayoutUIPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_IPATHSELECTIONCHANGE, kLayoutUIPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_IINSETSPRITECLIP, kLayoutUIPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTCONTROLLER, kLayoutUIPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_IUPDATETEXTSTATISTICS, kLayoutUIPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGEPROCESSINGQUEUE, kLayoutUIPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_IMOVEREFERENCEPOINTCMDDATA, kLayoutUIPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTREFERENCEPOINTOBSERVER, kLayoutUIPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_IREFERENCEPOINTSELECTIONOBSERVER, kLayoutUIPrefix + 32)
DECLARE_PMID(kInterfaceIDSpace, IID_IREFERENCEPOINTTOOLOBSERVER, kLayoutUIPrefix + 33)
DECLARE_PMID(kInterfaceIDSpace, IID_IREFERENCEPOINTDATA, kLayoutUIPrefix + 34)
DECLARE_PMID(kInterfaceIDSpace, IID_IREFERENCEPOINTSPREADOBSERVER, kLayoutUIPrefix + 35)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTACTION, kLayoutUIPrefix + 36)
DECLARE_PMID(kInterfaceIDSpace, IID_IOPENLAYOUTCMDDATA, kLayoutUIPrefix + 37)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCALEEDITBOXOBSERVER, kLayoutUIPrefix + 38)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCALESTATUSVIEWDATA, kLayoutUIPrefix + 39)
DECLARE_PMID(kInterfaceIDSpace, IID_IDYNAMICTRACKERDATA, kLayoutUIPrefix + 40)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGENAVIGATEEDITBOXOBSERVER, kLayoutUIPrefix + 41)
DECLARE_PMID(kInterfaceIDSpace, IID_IENDOFMOVE, kLayoutUIPrefix + 42)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTARTOFMOVE, kLayoutUIPrefix + 43)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTTRACKERACCESS, kLayoutUIPrefix + 46)
DECLARE_PMID(kInterfaceIDSpace, IID_IPOINTERTOOLMOUSEWATCHER, kLayoutUIPrefix + 47)
DECLARE_PMID(kInterfaceIDSpace, IID_IPOINTERTOOLEVENTWATCHER, kLayoutUIPrefix + 48)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTVIEWOBSERVER, kLayoutUIPrefix + 49)
DECLARE_PMID(kInterfaceIDSpace, IID_IPOINTERTOOLOBSERVER, kLayoutUIPrefix + 50)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEITEMDESELECTOBSERVER, kLayoutUIPrefix + 51)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTINVALOBSERVER, kLayoutUIPrefix + 52)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTMENUOBSERVER, kLayoutUIPrefix + 53)
DECLARE_PMID(kInterfaceIDSpace, IID_IUPDATEBUTTONMESSAGE, kLayoutUIPrefix + 54)
DECLARE_PMID(kInterfaceIDSpace, IID_IPATHSELECTION_SUITE, kLayoutUIPrefix + 56)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRANSFORMUIUTILS, kLayoutUIPrefix + 57)
DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTIONHIGHLIGHTOBSERVER, kLayoutUIPrefix + 58)
DECLARE_PMID(kInterfaceIDSpace, IID_ICURRENTSELECTIONUIDDATA, kLayoutUIPrefix + 59)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTSCROLLINGINFO, kLayoutUIPrefix + 60)
DECLARE_PMID(kInterfaceIDSpace, IID_INAVIGATEWIDGETDATA, kLayoutUIPrefix + 61)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTUIUTILS, kLayoutUIPrefix + 62)
DECLARE_PMID(kInterfaceIDSpace, IID_IGUIDEUIUTILS, kLayoutUIPrefix + 63)
DECLARE_PMID(kInterfaceIDSpace, IID_IGUIDETRACKERDATA, kLayoutUIPrefix + 64)
DECLARE_PMID(kInterfaceIDSpace, IID_IGUIDEZOOMFACTOROBSERVER, kLayoutUIPrefix + 65)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTMASTERLISTOBSERVER, kLayoutUIPrefix + 66)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTMASTERPAGEOBSERVER, kLayoutUIPrefix + 67)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTTEXT_IDLETASK, kLayoutUIPrefix + 68 )
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUT_TEXT_CACHE, kLayoutUIPrefix + 69 )
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTCACHEFOCUSOBSERVER, kLayoutUIPrefix + 70 )
DECLARE_PMID(kInterfaceIDSpace, IID_ICENTERITEMSINVIEWCMDDATA, kLayoutUIPrefix + 71)
DECLARE_PMID(kInterfaceIDSpace, IID_IGENERICHANDLEDRAWUTILS, kLayoutUIPrefix + 72)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCWINDOWPROGRESSBAR, kLayoutUIPrefix + 73)
DECLARE_PMID(kInterfaceIDSpace, IID_IACTIVESPREAD, kLayoutUIPrefix + 74)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEINVIEW, kLayoutUIPrefix + 75)
DECLARE_PMID(kInterfaceIDSpace, IID_IROTATETRACKERSPRITEDATA, kLayoutUIPrefix + 76)
DECLARE_PMID(kInterfaceIDSpace, IID_ISHEARTRACKERSPRITEDATA, kLayoutUIPrefix + 77)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCALETRACKERSPRITEDATA, kLayoutUIPrefix + 78)
DECLARE_PMID(kInterfaceIDSpace, IID_IDYNAMICTRANSFORMDATA, kLayoutUIPrefix + 79)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTVIEWUTILS, kLayoutUIPrefix + 80)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTPOLICYSUITE, kLayoutUIPrefix + 81)
DECLARE_PMID(kInterfaceIDSpace, IID_IKEYOBJECTCHANGED, kLayoutUIPrefix + 82)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGETRACKERACCESS, kLayoutUIPrefix + 83)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCUMENTUISTATE, kLayoutUIPrefix + 84)

DECLARE_PMID(kInterfaceIDSpace, IID_ISPREADSELECTION_ISUITE, kLayoutUIPrefix + 85)	//SpreadSelectionSuite
DECLARE_PMID(kInterfaceIDSpace, IID_ISPREADTARGET, kLayoutUIPrefix + 86)			//SpreadSelectionSuite
DECLARE_PMID(kInterfaceIDSpace, IID_ISPREADCSB_BROADCAST, kLayoutUIPrefix + 87)		//SpreadSelectionSuite
DECLARE_PMID(kInterfaceIDSpace, IID_ILIVESHAPEDATA, kLayoutUIPrefix + 88)
DECLARE_PMID(kInterfaceIDSpace, IID_IITEMSTOPLACEDATA, kLayoutUIPrefix + 89)
DECLARE_PMID(kInterfaceIDSpace, IID_IWANTMASTERSINLIST, kLayoutUIPrefix + 90)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEHITTESTSUITE ,kLayoutUIPrefix + 91)
DECLARE_PMID(kInterfaceIDSpace, IID_IKEYOBJECTCHANGE, kLayoutUIPrefix + 92)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTEXTCHANGEVIACLICKNOTIFICATION, kLayoutUIPrefix + 94)
DECLARE_PMID(kInterfaceIDSpace, IID_IZOOMFACTOR, kLayoutUIPrefix + 95)
//gap 96-97
DECLARE_PMID(kInterfaceIDSpace, IID_IDISABLEAGMGFXCACHEDATA, kLayoutUIPrefix + 98)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTDRAWTHREADSUTILS, kLayoutUIPrefix + 99)
DECLARE_PMID(kInterfaceIDSpace, IID_IDRAWINGTRACKERSTROKESDATA,		kLayoutUIPrefix + 100)
DECLARE_PMID(kInterfaceIDSpace, IID_ISHAPERECOGNIZER,				kLayoutUIPrefix + 101)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTGESTUREPAGEITEMUTILS,	kLayoutUIPrefix + 102)
DECLARE_PMID(kInterfaceIDSpace, IID_IAGMGPUINFO, kLayoutUIPrefix + 103)
DECLARE_PMID(kInterfaceIDSpace, IID_IENABLEDRAWINGMODEBEHAVIORS, kLayoutUIPrefix + 104)
DECLARE_PMID(kInterfaceIDSpace, IID_IWOULDSTARTMARQEEDRAG, kLayoutUIPrefix + 105)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRANSFORMGESTUREINPROGRESS, kLayoutUIPrefix + 106)
// gap 107-110 
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTRENDERER, kLayoutUIPrefix + 110)
DECLARE_PMID(kInterfaceIDSpace, IID_IAGMDOCUMENTCTXDATA, kLayoutUIPrefix + 111)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTOCKASSETINSYNCSTAGE, kLayoutUIPrefix + 112)


// <Implementation ID>
// Implementation IIDs
DECLARE_PMID(kImplementationIDSpace, kZoomComponentImpl, kLayoutUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kImageImportPreviewImpl, kLayoutUIPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kImageProcessingIdleTaskImpl, kLayoutUIPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kPathSelectionDocObserverImpl, kLayoutUIPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kCLayoutCommandMgrObserverImpl, kLayoutUIPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kCLayoutHierarchyObserverImpl, kLayoutUIPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kCLayoutPageItemObserverImpl, kLayoutUIPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kCLayoutToolBoxObserverImpl, kLayoutUIPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kLayoutEventHandlerImpl, kLayoutUIPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kGrabberHandTrackerEHImpl, kLayoutUIPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kToolCursorRegionImpl, kLayoutUIPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kLayoutControlViewImpl, kLayoutUIPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kLayoutControlDataImpl, kLayoutUIPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kLayoutPanelImpl, kLayoutUIPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kLayoutControlViewHelperImpl, kLayoutUIPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kLayoutPanoramaImpl, kLayoutUIPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kScrollToSelectionCmdImpl, kLayoutUIPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kParentChildSelectionFilterImpl, kLayoutUIPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kImageProcessingQueueImpl, kLayoutUIPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kVisibilityComponentImpl, kLayoutUIPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kTransformUIUtilsImpl, kLayoutUIPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kPageItemDeselectObserverImpl, kLayoutUIPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kPointerToolImpl, kLayoutUIPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kRotateToolImpl, kLayoutUIPrefix + 24	)
DECLARE_PMID(kImplementationIDSpace, kPointerTrackerImpl, kLayoutUIPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kGrabberHandSpriteImpl, kLayoutUIPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kMoveTrackerDataImpl, kLayoutUIPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kRotateTrackerImpl, kLayoutUIPrefix + 28	)
DECLARE_PMID(kImplementationIDSpace, kZeroPointViewImpl, kLayoutUIPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kZeroPointTrackerImpl, kLayoutUIPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kZeroPointTrackerRegisterImpl, kLayoutUIPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kZeroPointEventHandlerImpl, kLayoutUIPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kScrollBarLayoutSyncImpl, kLayoutUIPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kScrollBarLayoutSyncObserverImpl, kLayoutUIPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kGrabberHandToolImpl, kLayoutUIPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kGrabberHandTrackerImpl, kLayoutUIPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kHiddenLockedSelectionFilterImpl, kLayoutUIPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kLayoutSpriteImpl, kLayoutUIPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kLayoutTrackerRegisterImpl, kLayoutUIPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kLayoutScrollBarEHImpl, kLayoutUIPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kCrossSpreadSelectionFilterImpl, kLayoutUIPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kScrollToPointCmdImpl, kLayoutUIPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kLayoutControllerImpl, kLayoutUIPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kDirectSelectToolImpl, kLayoutUIPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kGroupSelectToolImpl, kLayoutUIPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kPathSelectionDataImpl, kLayoutUIPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kDirectSelectTrackerImpl, kLayoutUIPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kPathSelectionListImpl, kLayoutUIPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kGroupSelectTrackerImpl, kLayoutUIPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kLayoutSelectFilterServiceImpl, kLayoutUIPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kSetDefaultRefPointPositionCmdImpl, kLayoutUIPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kZeroPointPopupMenuActionImpl, kLayoutUIPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kGrabberHandCursorProviderImpl, kLayoutUIPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kPageNavigationWidgetTipImpl, kLayoutUIPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kClipHandleShapeImpl, kLayoutUIPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kImageEventActionImpl, kLayoutUIPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kSnapToInvalHandlerHelperImpl, kLayoutUIPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kSetGrabberPrefsCmdImpl, kLayoutUIPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kGrabberPrefsImpl, kLayoutUIPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kGrabberPrefsScriptProviderImpl, kLayoutUIPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kSetPreviewPrefsCmdImpl, kLayoutUIPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kLayoutPreviewImpl, kLayoutUIPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kNormalViewModeToolImpl, kLayoutUIPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kPreviewModeToolImpl, kLayoutUIPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kPreviewModeToolObserverImpl, kLayoutUIPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kViewModeToolSizerImpl, kLayoutUIPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kPreviewNonPrintDrawHandlerImpl, kLayoutUIPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kPreviewNonPrintDrawServiceImpl, kLayoutUIPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kViewModeToolTipImpl, kLayoutUIPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kReferencePointSuiteDefaultCSBImpl, kLayoutUIPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kReferencePointSuiteLayoutCSBImpl, kLayoutUIPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kReferencePointSuiteTextCSBImpl, kLayoutUIPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kLayoutDrawOptionsSetIDImpl, kLayoutUIPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kZeroPointToolImpl, kLayoutUIPrefix + 75)	// used for zero point tracking b/c it's not specific to a tool
DECLARE_PMID(kImplementationIDSpace, kLayoutViewObserverImpl, kLayoutUIPrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kSelectionTestMenuImpl, kLayoutUIPrefix + 77)	// DEBUG
DECLARE_PMID(kImplementationIDSpace, kDragDropSourceSuiteCSBImpl, kLayoutUIPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kLockAdornmentImpl, kLayoutUIPrefix + 79)
DECLARE_PMID(kImplementationIDSpace, kLayoutSelectionSnapshotImpl, kLayoutUIPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kMoveReferencePointCmdImpl, kLayoutUIPrefix + 81	)
DECLARE_PMID(kImplementationIDSpace, kMoveReferencePointCmdDataImpl, kLayoutUIPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kReferencePointTrackerImpl, kLayoutUIPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kReferencePointTrackerRegisterImpl, kLayoutUIPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kLayoutReferencePointObserverImpl, kLayoutUIPrefix + 85)
DECLARE_PMID(kImplementationIDSpace, kReferencePointSelectionObserverImpl, kLayoutUIPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kReferencePointToolObserverImpl, kLayoutUIPrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kLayoutUIActionImpl, kLayoutUIPrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kReferencePointDrawServiceImpl, kLayoutUIPrefix + 89)
DECLARE_PMID(kImplementationIDSpace, kReferencePointDrawHandlerImpl, kLayoutUIPrefix + 90)
DECLARE_PMID(kImplementationIDSpace, kReferencePointSpreadObserverImpl, kLayoutUIPrefix + 91)
DECLARE_PMID(kImplementationIDSpace, kLayoutTrackerAccessImpl, kLayoutUIPrefix + 92)
DECLARE_PMID(kImplementationIDSpace, kFitPageItemInWindowCmdImpl, kLayoutUIPrefix + 93)
DECLARE_PMID(kImplementationIDSpace, kLayoutKeyboardShortcutsImpl, kLayoutUIPrefix + 94)
DECLARE_PMID(kImplementationIDSpace, kScaleTrackerImpl, kLayoutUIPrefix + 95)
DECLARE_PMID(kImplementationIDSpace, kScaleToolImpl, kLayoutUIPrefix + 96)
DECLARE_PMID(kImplementationIDSpace, kLayoutSelectionTrackerImpl, kLayoutUIPrefix + 97)
DECLARE_PMID(kImplementationIDSpace, kLayoutSelectionToolImpl, kLayoutUIPrefix + 98)
DECLARE_PMID(kImplementationIDSpace, kReferencePointToolImpl, kLayoutUIPrefix + 99) // Just for registering tracker
DECLARE_PMID(kImplementationIDSpace, kLayoutActionProviderImpl, kLayoutUIPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kLayoutLockToolImpl, kLayoutUIPrefix + 101) // Just for registering tracker
DECLARE_PMID(kImplementationIDSpace, kLockTrackerImpl, kLayoutUIPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kImageTrackerRegister, kLayoutUIPrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kEPSTrackerRegisterImpl, kLayoutUIPrefix  + 104)
DECLARE_PMID(kImplementationIDSpace, kOpenLayoutPresentationCmdImpl, kLayoutUIPrefix + 105) // CS4/OWL2 Note: was kOpenLayoutWinCmdImpl
DECLARE_PMID(kImplementationIDSpace, kOpenLayoutPresentationCmdDataImpl, kLayoutUIPrefix + 106) // CS4/OWL2 Note: was kOpenLayoutWinCmdDataImpl
DECLARE_PMID(kImplementationIDSpace, kVisibilityHitDrawEventHandlerImpl, kLayoutUIPrefix + 107) 
DECLARE_PMID(kImplementationIDSpace, kScaleStatusViewObserverImpl, kLayoutUIPrefix + 108)
DECLARE_PMID(kImplementationIDSpace, kScaleEditBoxObserverImpl, kLayoutUIPrefix + 109)
DECLARE_PMID(kImplementationIDSpace, kScaleStatusViewDataImpl, kLayoutUIPrefix + 110)
DECLARE_PMID(kImplementationIDSpace, kPointerToolMouseWatcherImpl, kLayoutUIPrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kDynamicTrackerDataImpl, kLayoutUIPrefix + 112)
DECLARE_PMID(kImplementationIDSpace, kLayoutScrollBarViewImpl, kLayoutUIPrefix + 113)
DECLARE_PMID(kImplementationIDSpace, kPageNavigateViewObserverImpl, kLayoutUIPrefix + 114)
DECLARE_PMID(kImplementationIDSpace, kPageNavigateEditBoxObserverImpl, kLayoutUIPrefix + 115)
DECLARE_PMID(kImplementationIDSpace, kScaleStatusHideShowObserverImpl, kLayoutUIPrefix + 116)
DECLARE_PMID(kImplementationIDSpace, kOversetLineCountTestMenuImpl, kLayoutUIPrefix + 117)
DECLARE_PMID(kImplementationIDSpace, kPlacePISpriteImpl, kLayoutUIPrefix + 118)
DECLARE_PMID(kImplementationIDSpace, kPlacePISpriteDataImpl, kLayoutUIPrefix + 119)
DECLARE_PMID(kImplementationIDSpace, kBoundsDataImpl, kLayoutUIPrefix + 120)
DECLARE_PMID(kImplementationIDSpace, kCPageNavigateObserverImpl, kLayoutUIPrefix + 121)
DECLARE_PMID(kImplementationIDSpace, kPointerToolEventWatcherImpl, kLayoutUIPrefix + 122)
DECLARE_PMID(kImplementationIDSpace, kDirectSelectCursorProviderImpl, kLayoutUIPrefix + 123)
DECLARE_PMID(kImplementationIDSpace, kSelectCursorProviderImpl, kLayoutUIPrefix + 124)
DECLARE_PMID(kImplementationIDSpace, kShearToolImpl, kLayoutUIPrefix + 125)
DECLARE_PMID(kImplementationIDSpace, kShearTrackerImpl, kLayoutUIPrefix + 126 )
DECLARE_PMID(kImplementationIDSpace, kVisibilityHitDrawEventServiceImpl, kLayoutUIPrefix + 127)
DECLARE_PMID(kImplementationIDSpace, kScriptLayoutActionImpl, kLayoutUIPrefix + 128)
DECLARE_PMID(kImplementationIDSpace, kScriptLayoutObserverImpl, kLayoutUIPrefix + 129)
DECLARE_PMID(kImplementationIDSpace, kTransformToolCursorProviderImpl, kLayoutUIPrefix + 130)
DECLARE_PMID(kImplementationIDSpace, kTransformPercentageWidthTextValueImpl, kLayoutUIPrefix + 131)
DECLARE_PMID(kImplementationIDSpace, kTransformPercentageHeightTextValueImpl, kLayoutUIPrefix + 132)
DECLARE_PMID(kImplementationIDSpace, kTransformPreviewDialogErrorHandlerImpl, kLayoutUIPrefix + 133)
DECLARE_PMID(kImplementationIDSpace, kPointerToolObserverImpl, kLayoutUIPrefix + 134)
DECLARE_PMID(kImplementationIDSpace, kLayoutPageObserverImpl, kLayoutUIPrefix + 135)
DECLARE_PMID(kImplementationIDSpace, kNoShadowComboBoxDDLViewImpl, kLayoutUIPrefix + 136)
DECLARE_PMID(kImplementationIDSpace, kLayoutViewUtilsImpl, kLayoutUIPrefix + 138)
DECLARE_PMID(kImplementationIDSpace, kLayoutInvalObserverImpl, kLayoutUIPrefix + 139)
DECLARE_PMID(kImplementationIDSpace, kLayoutStartupServiceImpl, kLayoutUIPrefix + 140)
DECLARE_PMID(kImplementationIDSpace, kLayoutMenuObserverImpl, kLayoutUIPrefix + 141)
DECLARE_PMID(kImplementationIDSpace, kRotateDialogControllerImpl, kLayoutUIPrefix + 142)
DECLARE_PMID(kImplementationIDSpace, kRotateDialogObserverImpl, kLayoutUIPrefix + 143)
DECLARE_PMID(kImplementationIDSpace, kMoveDialogObserverImpl, kLayoutUIPrefix + 144)
DECLARE_PMID(kImplementationIDSpace, kMoveDialogControllerImpl, kLayoutUIPrefix + 145)
DECLARE_PMID(kImplementationIDSpace, kScaleDialogObserverImpl, kLayoutUIPrefix + 146)
DECLARE_PMID(kImplementationIDSpace, kScaleDialogControllerImpl, kLayoutUIPrefix + 147)
DECLARE_PMID(kImplementationIDSpace, kShearDialogObserverImpl, kLayoutUIPrefix + 148)
DECLARE_PMID(kImplementationIDSpace, kShearDialogControllerImpl, kLayoutUIPrefix + 149)
DECLARE_PMID(kImplementationIDSpace, kTransformMenuActionImpl, kLayoutUIPrefix + 150)
DECLARE_PMID(kImplementationIDSpace, kGotoPageDialogControllerImpl, kLayoutUIPrefix + 151)
DECLARE_PMID(kImplementationIDSpace, kLayoutPanelEHImpl, kLayoutUIPrefix + 152)
DECLARE_PMID(kImplementationIDSpace, kPageResizeTrackerImpl, kLayoutUIPrefix + 153)
DECLARE_PMID(kImplementationIDSpace, kLayoutDDSrcHelperProviderImpl, kLayoutUIPrefix + 154)
DECLARE_PMID(kImplementationIDSpace, kLayoutDDSrcPageItemHelperImpl, kLayoutUIPrefix + 155)
DECLARE_PMID(kImplementationIDSpace, kPathSelectionSuiteImpl, kLayoutUIPrefix + 156)
DECLARE_PMID(kImplementationIDSpace, kPageTrackerAccessImpl, kLayoutUIPrefix + 157)
DECLARE_PMID(kImplementationIDSpace, kFwdPathSelectionImpl, kLayoutUIPrefix + 158)
DECLARE_PMID(kImplementationIDSpace, kLayoutDDTargHelperProviderImpl, kLayoutUIPrefix + 159)
DECLARE_PMID(kImplementationIDSpace, kLayoutDDTargetSwatchFlavorHelperImpl, kLayoutUIPrefix + 160)
DECLARE_PMID(kImplementationIDSpace, kLayoutDDTargetSpreadFlavorHelperImpl, kLayoutUIPrefix + 161)
DECLARE_PMID(kImplementationIDSpace, kLayoutDDTargetFileFlavorHelperImpl, kLayoutUIPrefix + 162)
DECLARE_PMID(kImplementationIDSpace, kLayoutDDTargetPageItemFlavorHelperImpl, kLayoutUIPrefix + 163)
DECLARE_PMID(kImplementationIDSpace, kSelectionHighlightObserverImpl, kLayoutUIPrefix + 164)
DECLARE_PMID(kImplementationIDSpace, kGotoPageComboboxAttributesImpl, kLayoutUIPrefix + 165)
DECLARE_PMID(kImplementationIDSpace, kCurrentSelectionUIDDataImpl, kLayoutUIPrefix + 166)
DECLARE_PMID(kImplementationIDSpace, kOpenLayoutSignalRespServiceImpl, kLayoutUIPrefix + 167)   // CS4/OWL2 Note: was kOpenLayoutWinSignalRespServiceImpl
DECLARE_PMID(kImplementationIDSpace, kSWFLItemResizeTrackerImpl, kLayoutUIPrefix + 168)
DECLARE_PMID(kImplementationIDSpace, kSlugModeToolImpl, kLayoutUIPrefix + 169)
DECLARE_PMID(kImplementationIDSpace, kEyeDropperSuiteLayoutImpl, kLayoutUIPrefix + 170)
DECLARE_PMID(kImplementationIDSpace, kLayoutPanelObserverImpl, kLayoutUIPrefix + 171)
DECLARE_PMID(kImplementationIDSpace, kBleedModeToolImpl, kLayoutUIPrefix + 172)
DECLARE_PMID(kImplementationIDSpace, kPresentationModeToolImpl, kLayoutUIPrefix + 173)
DECLARE_PMID(kImplementationIDSpace, kLayoutOffscreenViewPortCacheImpl, kLayoutUIPrefix + 174)
DECLARE_PMID(kImplementationIDSpace, kTextBBoxResizeTrackerImpl, kLayoutUIPrefix + 175)
DECLARE_PMID(kImplementationIDSpace, kLayoutScrollingInfoImpl, kLayoutUIPrefix + 176)
DECLARE_PMID(kImplementationIDSpace, kLayoutWindowTitleImpl, kLayoutUIPrefix + 177)
DECLARE_PMID(kImplementationIDSpace, kPageNavigateWidgetDataImpl, kLayoutUIPrefix + 178)
DECLARE_PMID(kImplementationIDSpace, kPageNavigateWidgetControlViewImpl, kLayoutUIPrefix + 179)
//gap
DECLARE_PMID(kImplementationIDSpace, kLayoutUIUtilsImpl, kLayoutUIPrefix + 181)
DECLARE_PMID(kImplementationIDSpace, kGuideUIUtilsImpl, kLayoutUIPrefix + 182)
DECLARE_PMID(kImplementationIDSpace, kGuideCreationTrackerImpl, kLayoutUIPrefix + 183)
DECLARE_PMID(kImplementationIDSpace, kGuideTrackerDataImpl, kLayoutUIPrefix + 184)
DECLARE_PMID(kImplementationIDSpace, kGuideMoveTrackerImpl, kLayoutUIPrefix + 185)
DECLARE_PMID(kImplementationIDSpace, kGuideTrackerRegisterImpl, kLayoutUIPrefix + 186)
DECLARE_PMID(kImplementationIDSpace, kGuideZoomFactorObserverImpl, kLayoutUIPrefix + 187)
DECLARE_PMID(kImplementationIDSpace, kGuideLayoutActionImpl, kLayoutUIPrefix + 188)
DECLARE_PMID(kImplementationIDSpace, kGuideSelectionFilterImpl, kLayoutUIPrefix + 189)
DECLARE_PMID(kImplementationIDSpace, kGuidesKeyboardShortcutsImpl, kLayoutUIPrefix + 190)
DECLARE_PMID(kImplementationIDSpace, kGuideOptionsDialogControllerImpl, kLayoutUIPrefix + 191)
DECLARE_PMID(kImplementationIDSpace, kGroupOverrideableAlertDialogControllerImpl, kLayoutUIPrefix + 192)
DECLARE_PMID(kImplementationIDSpace, kGroupOverrideableAlertDialogObserverImpl, kLayoutUIPrefix + 193)
DECLARE_PMID(kImplementationIDSpace, kPasteGuideCmdImpl, kLayoutUIPrefix + 194)
DECLARE_PMID(kImplementationIDSpace, kCLayoutMasterListObserverImpl, kLayoutUIPrefix + 195)
DECLARE_PMID(kImplementationIDSpace, kLayoutMasterPageObserverImpl, kLayoutUIPrefix + 196)
DECLARE_PMID(kImplementationIDSpace, kMasterListLayoutActionImpl, kLayoutUIPrefix + 197)
DECLARE_PMID(kImplementationIDSpace, kMasterPageLayoutActionImpl, kLayoutUIPrefix + 198)
DECLARE_PMID(kImplementationIDSpace, kLayoutSelectionFactoryImpl, kLayoutUIPrefix + 199)
DECLARE_PMID(kImplementationIDSpace, kTextFrameOptionsLayoutCSBImpl, kLayoutUIPrefix + 200)
DECLARE_PMID(kImplementationIDSpace, kLayoutSelectionHighlighterImpl, kLayoutUIPrefix + 201)
DECLARE_PMID(kImplementationIDSpace, kSelectionDataSuiteLayoutCSBImpl, kLayoutUIPrefix + 202)
DECLARE_PMID(kImplementationIDSpace, kSelectionSnapshotLayoutCSBImpl, kLayoutUIPrefix + 203)
DECLARE_PMID(kImplementationIDSpace, kToolChangeSuiteLayoutCSBImpl, kLayoutUIPrefix + 204)
DECLARE_PMID(kImplementationIDSpace, kContextMenuSuiteLayoutCSBImpl, kLayoutUIPrefix + 205)
DECLARE_PMID(kImplementationIDSpace, kStepAndRepeatSuiteLayoutCSBImpl, kLayoutUIPrefix + 206 )
DECLARE_PMID(kImplementationIDSpace, kSolidGroupHitTestHandlerImpl, kLayoutUIPrefix + 207 )
DECLARE_PMID(kImplementationIDSpace, kLayoutCSB_ScriptSuiteImpl, kLayoutUIPrefix + 208)
DECLARE_PMID(kImplementationIDSpace, kZOrderSelectSuiteLayoutCSBImpl, kLayoutUIPrefix + 209 )
DECLARE_PMID(kImplementationIDSpace, kDocumentLayoutSuiteLayCSBImpl, kLayoutUIPrefix + 210 )
DECLARE_PMID(kImplementationIDSpace, kSelectionBoxHandleShapeSuiteLayoutCSBImpl, kLayoutUIPrefix + 211 )
DECLARE_PMID(kImplementationIDSpace, kZOrderSelectSuiteDefaultCSBImpl, kLayoutUIPrefix + 213 )
DECLARE_PMID(kImplementationIDSpace, kConcreteLayoutSelectionImpl, kLayoutUIPrefix + 214)
DECLARE_PMID(kImplementationIDSpace, kLayoutSelectionAttributeObserverImpl, kLayoutUIPrefix + 215)
DECLARE_PMID(kImplementationIDSpace, kLayoutHitTestSuiteImpl, kLayoutUIPrefix + 216)
DECLARE_PMID(kImplementationIDSpace, kLayoutTextFocusListImpl, kLayoutUIPrefix + 217 )
DECLARE_PMID(kImplementationIDSpace, kLayoutTextIdleTaskImpl, kLayoutUIPrefix + 218 )
DECLARE_PMID(kImplementationIDSpace, kLayoutTextCacheImpl, kLayoutUIPrefix + 219 )
DECLARE_PMID(kImplementationIDSpace, kTextCacheFocusObserverImpl, kLayoutUIPrefix + 220 )
DECLARE_PMID(kImplementationIDSpace, kLayoutSelectionSuiteImpl, kLayoutUIPrefix + 221)
DECLARE_PMID(kImplementationIDSpace, kPageItemDDTargetHelperProviderImpl, kLayoutUIPrefix + 222)
DECLARE_PMID(kImplementationIDSpace, kPageItemDDTargetSwatchFlavorHelperImpl, kLayoutUIPrefix + 223)
DECLARE_PMID(kImplementationIDSpace, kZOrderLabelTestMenuImpl, kLayoutUIPrefix + 224)	// DEBUG
DECLARE_PMID(kImplementationIDSpace, kZOrderLabelDrwEvtHandlerImpl, kLayoutUIPrefix + 225)	// DEBUG
DECLARE_PMID(kImplementationIDSpace, kCenterItemsInViewCmdImpl, kLayoutUIPrefix + 226)
DECLARE_PMID(kImplementationIDSpace, kCenterItemsInViewCmdDataImpl, kLayoutUIPrefix + 227)
DECLARE_PMID(kImplementationIDSpace, kPlacePITrackerImpl, kLayoutUIPrefix + 228)
DECLARE_PMID(kImplementationIDSpace, kFootnoteOptionsLayoutCSBImpl, kLayoutUIPrefix + 229)
DECLARE_PMID(kImplementationIDSpace, kTextVariableLayoutCSBImpl, kLayoutUIPrefix + 230)
DECLARE_PMID(kImplementationIDSpace, kTextVariableLayoutCSBSelectionExtImpl, kLayoutUIPrefix + 231)
DECLARE_PMID(kImplementationIDSpace, kSolidMPDDHitTestHandlerImpl, kLayoutUIPrefix + 232)
DECLARE_PMID(kImplementationIDSpace, kBaseHitTestHandlerImpl, kLayoutUIPrefix + 233)
DECLARE_PMID(kImplementationIDSpace, kPtrHitTestHandlerImpl, kLayoutUIPrefix + 234)
DECLARE_PMID(kImplementationIDSpace, kPtrOMPHitTestHandlerImpl, kLayoutUIPrefix + 235)
DECLARE_PMID(kImplementationIDSpace, kDirSelHitTestHandlerImpl, kLayoutUIPrefix + 236)
DECLARE_PMID(kImplementationIDSpace, kDirSelOMPHitTestHandlerImpl, kLayoutUIPrefix + 237)
DECLARE_PMID(kImplementationIDSpace, kSolidHitTestHandlerImpl, kLayoutUIPrefix + 238)
DECLARE_PMID(kImplementationIDSpace, kSolidTOPHitTestHandlerImpl, kLayoutUIPrefix + 239)
DECLARE_PMID(kImplementationIDSpace, kSolidTOPMPHitTestHandlerImpl, kLayoutUIPrefix + 241)
DECLARE_PMID(kImplementationIDSpace, kTOPOnlyPathHitTestHandlerImpl, kLayoutUIPrefix + 242)
DECLARE_PMID(kImplementationIDSpace, kDirSelMPLLHitTestHandlerImpl, kLayoutUIPrefix + 243)
DECLARE_PMID(kImplementationIDSpace, kDirSelMPHitTestHandlerImpl, kLayoutUIPrefix + 244)
DECLARE_PMID(kImplementationIDSpace, kSolidTOPLLHitTestHandlerImpl, kLayoutUIPrefix + 245)
DECLARE_PMID(kImplementationIDSpace, kSolidMPHitTestHandlerImpl, kLayoutUIPrefix + 246)
DECLARE_PMID(kImplementationIDSpace, kSolidMPLLHitTestHandlerImpl, kLayoutUIPrefix + 247)
DECLARE_PMID(kImplementationIDSpace, kPtrSolidTOPOMPHitTestHandlerImpl, kLayoutUIPrefix + 248)
DECLARE_PMID(kImplementationIDSpace, kGroupHitTestHandlerImpl, kLayoutUIPrefix + 249)
DECLARE_PMID(kImplementationIDSpace, kDirSelGroupHitTestHandlerImpl, kLayoutUIPrefix + 250)
DECLARE_PMID(kImplementationIDSpace, kSolidTOPOMPHitTestHandlerImpl, kLayoutUIPrefix + 251)
DECLARE_PMID(kImplementationIDSpace, kSelectionHitTestHandlerImpl, kLayoutUIPrefix + 252 )
DECLARE_PMID(kImplementationIDSpace, kDirSelNoGuidesHitTestHandlerImpl, kLayoutUIPrefix + 253 )
DECLARE_PMID(kImplementationIDSpace, kPageItemActionHitTestHandlerImpl, kLayoutUIPrefix + 254 )
DECLARE_PMID(kImplementationIDSpace, kBaseSelectionHandlerDataImpl, kLayoutUIPrefix + 255)

DECLARE_PMID(kImplementationIDSpace, kGenericTrackerRegisterImpl, kLayoutUI2Prefix + 0)
DECLARE_PMID(kImplementationIDSpace, kArrangeComponentImpl, kLayoutUI2Prefix + 1)
DECLARE_PMID(kImplementationIDSpace, kAlignComponentImpl, kLayoutUI2Prefix + 2)
DECLARE_PMID(kImplementationIDSpace, kStrokeWeightImpl, kLayoutUI2Prefix + 3)
DECLARE_PMID(kImplementationIDSpace, kDynamicStrokeWeightMenuImpl, kLayoutUI2Prefix + 4)
DECLARE_PMID(kImplementationIDSpace, kFillTintImpl, kLayoutUI2Prefix + 5)
DECLARE_PMID(kImplementationIDSpace, kSelectComponentImpl, kLayoutUI2Prefix + 6)
DECLARE_PMID(kImplementationIDSpace, kObjectSizeComponentImpl, kLayoutUI2Prefix + 7)
DECLARE_PMID(kImplementationIDSpace, kFrameComponentImpl, kLayoutUI2Prefix + 8)
DECLARE_PMID(kImplementationIDSpace, kLockComponentImpl, kLayoutUI2Prefix + 9)
DECLARE_PMID(kImplementationIDSpace, kGenericHandleDrawUtilsImpl, kLayoutUI2Prefix + 10)
DECLARE_PMID(kImplementationIDSpace, kGroupComponentImpl, kLayoutUI2Prefix + 11)
DECLARE_PMID(kImplementationIDSpace, kGroupHandleShapeImpl, kLayoutUI2Prefix + 12)
DECLARE_PMID(kImplementationIDSpace, kSplitWindowButtonObserverImpl, kLayoutUI2Prefix + 13)
DECLARE_PMID(kImplementationIDSpace, kGroupTrackerRegisterImpl, kLayoutUI2Prefix + 14)
DECLARE_PMID(kImplementationIDSpace, kGroupAlertDialogControllerImpl, kLayoutUI2Prefix + 15)
DECLARE_PMID(kImplementationIDSpace, kGroupAlertDialogObserverImpl, kLayoutUI2Prefix + 16)
DECLARE_PMID(kImplementationIDSpace, kGroupRectHandleShapeImpl, kLayoutUI2Prefix + 17)
DECLARE_PMID(kImplementationIDSpace, kDocWindowProgressBarImpl, kLayoutUI2Prefix + 18)
DECLARE_PMID(kImplementationIDSpace, kLayoutWidgetDDSourceImpl, kLayoutUI2Prefix + 19)
DECLARE_PMID(kImplementationIDSpace, kLayoutWidgetDDTargetImpl, kLayoutUI2Prefix + 20)
DECLARE_PMID(kImplementationIDSpace, kPageItemDDTargetImpl, kLayoutUI2Prefix + 21)
DECLARE_PMID(kImplementationIDSpace, kDDMoveTrackerImpl, kLayoutUI2Prefix + 22)
DECLARE_PMID(kImplementationIDSpace, kGenericItemDDMoveTrackerImpl, kLayoutUI2Prefix + 23)
DECLARE_PMID(kImplementationIDSpace, kStandOffHandleShapeImpl, kLayoutUI2Prefix + 24)
DECLARE_PMID(kImplementationIDSpace, kTextInsetHandleShapeImpl, kLayoutUI2Prefix + 25)
DECLARE_PMID(kImplementationIDSpace, kSplitWindowButtonTipImpl, kLayoutUI2Prefix + 26)
DECLARE_PMID(kImplementationIDSpace, kSplitWindowButtonEHImpl, kLayoutUI2Prefix + 27)
DECLARE_PMID(kImplementationIDSpace, kDocStatusMenuComponentImpl, kLayoutUI2Prefix + 32)
DECLARE_PMID(kImplementationIDSpace, kDocStatusWidgetTipImpl, kLayoutUI2Prefix + 33)
DECLARE_PMID(kImplementationIDSpace, kScreenViewMenuComponentImpl, kLayoutUI2Prefix + 34)
DECLARE_PMID(kImplementationIDSpace, kMasterPageHitTestServiceImpl, kLayoutUI2Prefix + 35)
DECLARE_PMID(kImplementationIDSpace, kMasterPageHitTestHandlerImpl, kLayoutUI2Prefix + 36)
DECLARE_PMID(kImplementationIDSpace, kMasterPageInvalServiceImpl, kLayoutUI2Prefix + 37)
DECLARE_PMID(kImplementationIDSpace, kMasterPageInvalHandlerImpl, kLayoutUI2Prefix + 38)
DECLARE_PMID(kImplementationIDSpace, kRotateTrackerSpriteImpl, kLayoutUI2Prefix + 39)
DECLARE_PMID(kImplementationIDSpace, kRotateTrackerSpriteDataImpl, kLayoutUI2Prefix + 40)
DECLARE_PMID(kImplementationIDSpace, kShearTrackerSpriteImpl, kLayoutUI2Prefix + 41)
DECLARE_PMID(kImplementationIDSpace, kShearTrackerSpriteDataImpl, kLayoutUI2Prefix + 42)
DECLARE_PMID(kImplementationIDSpace, kScaleTrackerSpriteImpl, kLayoutUI2Prefix + 43)
DECLARE_PMID(kImplementationIDSpace, kScaleTrackerSpriteDataImpl, kLayoutUI2Prefix + 44)
DECLARE_PMID(kImplementationIDSpace, kGuideItemEventActionImpl, kLayoutUI2Prefix + 45)
DECLARE_PMID(kImplementationIDSpace, kDynamicTransformDataImpl, kLayoutUI2Prefix + 46)
DECLARE_PMID(kImplementationIDSpace, kScalePercentageEditBoxEHImpl, kLayoutUI2Prefix + 47)
DECLARE_PMID(kImplementationIDSpace, kScalePercentageHasFocusImpl, kLayoutUI2Prefix + 48)
DECLARE_PMID(kImplementationIDSpace, kLayoutPolicySuiteASBImpl, kLayoutUI2Prefix + 49)
DECLARE_PMID(kImplementationIDSpace, kLayoutPolicySuiteLayoutCSBImpl, kLayoutUI2Prefix + 50)
DECLARE_PMID(kImplementationIDSpace, kLayoutPolicySuiteDefaultCSBImpl, kLayoutUI2Prefix + 51)
DECLARE_PMID(kImplementationIDSpace, kLayoutPolicySuiteSpreadCSBImpl, kLayoutUI2Prefix + 52)
DECLARE_PMID(kImplementationIDSpace, kPageHitTestSuiteImpl, kLayoutUI2Prefix + 53)
DECLARE_PMID(kImplementationIDSpace, kContentDropperDropToolSpriteImpl, kLayoutUI2Prefix + 54)
DECLARE_PMID(kImplementationIDSpace, kLiveShapeModeHandleTipImpl, kLayoutUI2Prefix + 55)
DECLARE_PMID(kImplementationIDSpace, kMatchPasteBoardToThemeColorMenuComponentImpl, kLayoutUI2Prefix + 56)
// gap
DECLARE_PMID(kImplementationIDSpace, kContextMenuSuiteSpreadCSBImpl, kLayoutUI2Prefix + 58)	//SpreadSelectionSuite
DECLARE_PMID(kImplementationIDSpace, kToolChangeSuiteSpreadCSBImpl, kLayoutUI2Prefix + 59)	//SpreadSelectionSuite
DECLARE_PMID(kImplementationIDSpace, kLayoutPresentationImpl, kLayoutUI2Prefix + 60)
DECLARE_PMID(kImplementationIDSpace, kSpreadSelectionAttributeObserverImpl, kLayoutUI2Prefix + 61)	//SpreadSelectionSuite
DECLARE_PMID(kImplementationIDSpace, kUpdateDocumentUIStateCmdImpl, kLayoutUI2Prefix + 62)
DECLARE_PMID(kImplementationIDSpace, kSpreadSelectionSuiteImpl, kLayoutUI2Prefix + 63) //SpreadSelectionSuite
DECLARE_PMID(kImplementationIDSpace, kSpreadTargetImpl, kLayoutUI2Prefix + 64) //SpreadSelectionSuite
DECLARE_PMID(kImplementationIDSpace, kSpreadScriptSelectionSuiteImpl, kLayoutUI2Prefix + 65) //SpreadSelectionSuite
DECLARE_PMID(kImplementationIDSpace, kSelectionDataSuiteSpreadCSBImpl, kLayoutUI2Prefix + 66) //SpreadSelectionSuite
DECLARE_PMID(kImplementationIDSpace, kSpreadSelectionHighlighterImpl, kLayoutUI2Prefix + 67) //SpreadSelectionSuite
DECLARE_PMID(kImplementationIDSpace, kConcreteSpreadSelectionImpl, kLayoutUI2Prefix + 68) //SpreadSelectionSuite
DECLARE_PMID(kImplementationIDSpace, kSpreadUniformTargetFactoryImpl, kLayoutUI2Prefix + 69) //SpreadSelectionSuite
DECLARE_PMID(kImplementationIDSpace, kSpreadSelectionFactoryImpl, kLayoutUI2Prefix + 70) //SpreadSelectionSuite
DECLARE_PMID(kImplementationIDSpace, kReferencePointSuiteSpreadCSBImpl, kLayoutUI2Prefix + 71) //SpreadSelectionSuite
DECLARE_PMID(kImplementationIDSpace, kGeometrySuiteSpreadCSBImpl, kLayoutUI2Prefix + 72) //SpreadSelectionSuite
DECLARE_PMID(kImplementationIDSpace, kTransformSuiteSpreadCSBImpl, kLayoutUI2Prefix + 73) //SpreadSelectionSuite
DECLARE_PMID(kImplementationIDSpace, kScrapSuiteSpreadCSBImpl, kLayoutUI2Prefix + 74) //SpreadSelectionSuite
DECLARE_PMID(kImplementationIDSpace, kPointerToolModeImpl, kLayoutUI2Prefix + 75)
DECLARE_PMID(kImplementationIDSpace, kLiveModeEnableTrackerImpl, kLayoutUI2Prefix + 76)
DECLARE_PMID(kImplementationIDSpace, kLiveShapeDataImpl, kLayoutUI2Prefix + 77)
DECLARE_PMID(kImplementationIDSpace, kLiveCornerAdornmentTrackerImpl, kLayoutUI2Prefix + 78)
DECLARE_PMID(kImplementationIDSpace, kLiveCornerAdornmentSpriteImpl, kLayoutUI2Prefix + 79)
DECLARE_PMID(kImplementationIDSpace, kAlignAndDistributeSuiteSpreadCSBImpl, kLayoutUI2Prefix + 80)
DECLARE_PMID(kImplementationIDSpace, kPlaceItemFromPlaceGunImpl, kLayoutUI2Prefix + 81)
DECLARE_PMID(kImplementationIDSpace, kContentDropperDropToolTrackerImpl, kLayoutUI2Prefix + 82)
DECLARE_PMID(kImplementationIDSpace, kDirSelExceptSplinesHitTestHandlerImpl, kLayoutUI2Prefix + 83)
DECLARE_PMID(kImplementationIDSpace, kDirSelExceptSplinesLLHitTestHandlerImpl, kLayoutUI2Prefix + 84)
DECLARE_PMID(kImplementationIDSpace, kSolidLLHitTestHandlerImpl, kLayoutUI2Prefix + 85)
DECLARE_PMID(kImplementationIDSpace, kFormFieldMissingFontAdornmentImpl, kLayoutUI2Prefix + 86)
DECLARE_PMID(kImplementationIDSpace, kFormFieldMissingFontAdornmentTipImpl, kLayoutUI2Prefix + 87)
//gap
DECLARE_PMID(kImplementationIDSpace, kDV_NoShadowCBAttributesImpl,				kLayoutUI2Prefix + 100)
DECLARE_PMID(kImplementationIDSpace, kDV_LayoutOffscreenViewPortCacheImpl,		kLayoutUI2Prefix + 101)
//gap
//depreceated -- replaced by kNoShadowComboBoxDDLViewImpl -- DECLARE_PMID(kImplementationIDSpace, kDV_NoShadowComboBoxDDLViewImpl,			kLayoutUI2Prefix + 105)
DECLARE_PMID(kImplementationIDSpace, kDV_PageNavNoShadowCBAttributesImpl,		kLayoutUI2Prefix + 106)
DECLARE_PMID(kImplementationIDSpace, kDV_PageNavigateDDLOpenCloseHandlerImpl,	kLayoutUI2Prefix + 107)

//gap
DECLARE_PMID(kImplementationIDSpace, kColorThemeDropperSuiteLayoutImpl,	kLayoutUI2Prefix + 118)
//gap 119-123
DECLARE_PMID(kImplementationIDSpace, kAGMDocumentCtxDataImpl, kLayoutUI2Prefix + 124)
DECLARE_PMID(kImplementationIDSpace, kLayoutDrawThreadUtilsImpl, kLayoutUI2Prefix + 125)
DECLARE_PMID(kImplementationIDSpace, kLayoutOpenGLWidgetImpl, kLayoutUI2Prefix + 126)
DECLARE_PMID(kImplementationIDSpace, kLayoutRendererImpl, kLayoutUI2Prefix + 127)
DECLARE_PMID(kImplementationIDSpace, kAGMGPUInfoImpl, kLayoutUI2Prefix + 128)

DECLARE_PMID(kImplementationIDSpace, kIDGPUSnifferStartupServiceImpl, kLayoutUI2Prefix + 129)
DECLARE_PMID(kImplementationIDSpace, kDrawingToolImpl,					kLayoutUI2Prefix + 130)
DECLARE_PMID(kImplementationIDSpace, kDrawingToolCursorProviderImpl,	kLayoutUI2Prefix + 131)
DECLARE_PMID(kImplementationIDSpace, kDrawingTrackerImpl,				kLayoutUI2Prefix + 132)
DECLARE_PMID(kImplementationIDSpace, kDrawingTrackerEventHandlerImpl,	kLayoutUI2Prefix + 133)
DECLARE_PMID(kImplementationIDSpace, kDrawingTrackerStrokesDataImpl,	kLayoutUI2Prefix + 134)
DECLARE_PMID(kImplementationIDSpace, kDrawingSpriteImpl,				kLayoutUI2Prefix + 135)
DECLARE_PMID(kImplementationIDSpace, kShapeRecognizerImpl,				kLayoutUI2Prefix + 136)
DECLARE_PMID(kImplementationIDSpace, kLayoutGesturePageItemUtilsImpl,	kLayoutUI2Prefix + 137)
DECLARE_PMID(kImplementationIDSpace, kEnableDrawingModeBehaviorsImpl,	kLayoutUI2Prefix + 138)
DECLARE_PMID(kImplementationIDSpace, kWouldStartMarqueeDragImpl,		kLayoutUI2Prefix + 139)
DECLARE_PMID(kImplementationIDSpace, kZeroPointSpriteImpl,              kLayoutUI2Prefix + 140)
DECLARE_PMID(kImplementationIDSpace, kReferencePointSpriteImpl,         kLayoutUI2Prefix + 141)
DECLARE_PMID(kImplementationIDSpace, kStockAdornmentImpl, kLayoutUI2Prefix + 142)
DECLARE_PMID(kImplementationIDSpace, kStockTrackerImpl, kLayoutUI2Prefix + 143)
DECLARE_PMID(kImplementationIDSpace, kStockTrackerRegisterImpl, kLayoutUI2Prefix + 144)
DECLARE_PMID(kImplementationIDSpace, kStockPurchaseCartHandleTipImpl, kLayoutUI2Prefix + 145)
DECLARE_PMID(kImplementationIDSpace, kEndnoteOptionsLayoutCSBImpl, kLayoutUI2Prefix + 146)
DECLARE_PMID(kImplementationIDSpace, kSeperatorModeToolImpl, kLayoutUI2Prefix + 147)
DECLARE_PMID(kImplementationIDSpace, kViewOptionsToolImpl, kLayoutUI2Prefix + 148)
DECLARE_PMID(kImplementationIDSpace, kViewOptionsToolIconViewImpl, kLayoutUI2Prefix + 149)
DECLARE_PMID(kImplementationIDSpace, kViewOptionsToolEventHandlerImpl, kLayoutUI2Prefix + 150)
DECLARE_PMID(kImplementationIDSpace, kViewOptionsCellMouseRollOverImpl, kLayoutUI2Prefix + 151)
DECLARE_PMID(kImplementationIDSpace, kViewOptionsCellEventHandlerImpl, kLayoutUI2Prefix + 152)
DECLARE_PMID(kImplementationIDSpace, kViewOptionsToolPopupWindowImpl, kLayoutUI2Prefix + 153)

// <Service ID>
// Service Providers
DECLARE_PMID(kServiceIDSpace, kSelectionFilterService, kLayoutUIPrefix + 1)
DECLARE_PMID(kServiceIDSpace, kLayoutActionService, kLayoutUIPrefix + 2)
DECLARE_PMID(kServiceIDSpace, kLayoutDDSrcContentHelperService, kLayoutUIPrefix + 3)
DECLARE_PMID(kServiceIDSpace, kLayoutDDTargetFlavorHelperService, kLayoutUIPrefix + 4)
DECLARE_PMID(kServiceIDSpace, kOpenLayoutSignalServiceID, kLayoutUIPrefix + 5)     // CS4/OWL2 Note: was kOpenLayoutWinSignalServiceID
DECLARE_PMID(kServiceIDSpace, kPageItemDDTargetFlavorHelperService, kLayoutUIPrefix + 6)


// <Widget ID>
// Widget IDs
DECLARE_PMID(kWidgetIDSpace, kVertScrollBarWidgetID, kLayoutUIPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kHorzScrollBarWidgetID, kLayoutUIPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kLayoutWidgetID, kLayoutUIPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kHorzRulerWidgetID, kLayoutUIPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kVertRulerWidgetID, kLayoutUIPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kZeroPointWidgetID, kLayoutUIPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kScaleStatusWidgetID, kLayoutUIPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kPageNavigateWidgetID, kLayoutUIPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kPageNavigateEditBoxWidgetID, kLayoutUIPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kFirstPageIconWidgetID, kLayoutUIPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kLastPageIconWidgetID, kLayoutUIPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kPageNumForwardIconWidgetID, kLayoutUIPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kPageNumBackwardIconWidgetID, kLayoutUIPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kLayoutPanelParentWidgetId, kLayoutUIPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kDirectSelectToolWidgetId, kLayoutUIPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kGrabberHandToolWidgetId, kLayoutUIPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kPointerToolWidgetId, kLayoutUIPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kRotateToolWidgetId, kLayoutUIPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kScaleToolWidgetId, kLayoutUIPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kShearToolWidgetId, kLayoutUIPrefix + 20)

// Rotate Dialog
DECLARE_PMID(kWidgetIDSpace, kRotateParentWidgetID, kLayoutUIPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kCopyButtonWidgetID, kLayoutUIPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kRotateAngleTextWidgetId, kLayoutUIPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kRotateAngleEditBoxWidgetID, kLayoutUIPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kRotateDegreeSymbolWidgetId, kLayoutUIPrefix + 25)

DECLARE_PMID(kWidgetIDSpace, kDrawingToolWidgetId, kLayoutUIPrefix + 26)
// gap

// Move Dialog
DECLARE_PMID(kWidgetIDSpace, kMoveDlgParentWidgetID, kLayoutUIPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kMoveDlgPositionGroupWidgetID, kLayoutUIPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kMoveDlgPositionTitleTextWidgetID, kLayoutUIPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kMoveDlgHorizontalTextWidgetID, kLayoutUIPrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kMoveDlgHorizontalEditBoxWidgetID, kLayoutUIPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kMoveDlgVerticalTextWidgetID, kLayoutUIPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kMoveDlgVerticalEditBoxWidgetID, kLayoutUIPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kMoveDlgSeperatorWidgetID, kLayoutUIPrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kMoveDlgDistanceTextWidgetID, kLayoutUIPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kMoveDlgDistanceEditBoxWidgetID, kLayoutUIPrefix + 39)
DECLARE_PMID(kWidgetIDSpace, kMoveDlgAngleTextWidgetID, kLayoutUIPrefix + 40)
DECLARE_PMID(kWidgetIDSpace, kMoveDlgAngleEditBoxWidgetID, kLayoutUIPrefix + 41)
DECLARE_PMID(kWidgetIDSpace, kMoveDlgDegreeSymbolWidgetID, kLayoutUIPrefix + 42)
DECLARE_PMID(kWidgetIDSpace, kMoveDlgCopyButtonWidgetID, kLayoutUIPrefix + 43)
// gap

// Scale Dialog
DECLARE_PMID(kWidgetIDSpace, kScaleDlgParentWidgetID, kLayoutUIPrefix + 50)
DECLARE_PMID(kWidgetIDSpace, kScaleDlgButtonsPanelWidgetID, kLayoutUIPrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kScaleDlgEditBoxPanelWidgetID, kLayoutUIPrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kScaleDlgScaleLabelPanelWidgetID, kLayoutUIPrefix + 53)
DECLARE_PMID(kWidgetIDSpace, kScaleDlgScaleChainPanelWidgetID, kLayoutUIPrefix + 54)
DECLARE_PMID(kWidgetIDSpace, kScalePanelWidgetID, kLayoutUIPrefix + 55)
DECLARE_PMID(kWidgetIDSpace, kScaleDlgChainWidgetID, kLayoutUIPrefix + 56)
//DECLARE_PMID(kWidgetIDSpace, kScaleDlgNonUniformBorderWidgetID, kLayoutUIPrefix + 57)
//DECLARE_PMID(kWidgetIDSpace, kScaleDlgNonUniformRadioWidgetID, kLayoutUIPrefix + 58)
DECLARE_PMID(kWidgetIDSpace, kScaleDlgHorzTextWidgetID, kLayoutUIPrefix + 59)
DECLARE_PMID(kWidgetIDSpace, kScaleDlgHorzEditBoxWidgetID, kLayoutUIPrefix + 60)
DECLARE_PMID(kWidgetIDSpace, kScaleDlgVertTextWidgetID, kLayoutUIPrefix + 61)
DECLARE_PMID(kWidgetIDSpace, kScaleDlgVertEditBoxWidgetID, kLayoutUIPrefix + 62)
DECLARE_PMID(kWidgetIDSpace, kScaleDlgCopyButtonWidgetID, kLayoutUIPrefix + 63)
// gap

// Shear Dialog
DECLARE_PMID(kWidgetIDSpace, kShearDlgParentWidgetID, kLayoutUIPrefix + 70)
DECLARE_PMID(kWidgetIDSpace, kShearDlgCopyButtonWidgetID, kLayoutUIPrefix + 71)
DECLARE_PMID(kWidgetIDSpace, kShearDlgAngleTextWidgetID, kLayoutUIPrefix + 72)
DECLARE_PMID(kWidgetIDSpace, kShearDlgAngleEditBoxWidgetID, kLayoutUIPrefix + 73)
DECLARE_PMID(kWidgetIDSpace, kShearDlgDegreeSymbolWidgetID, kLayoutUIPrefix + 74)
DECLARE_PMID(kWidgetIDSpace, kShearDlgAxisGroupWidgetID, kLayoutUIPrefix + 75)
DECLARE_PMID(kWidgetIDSpace, kShearDlgAxisTitleTextWidgetID, kLayoutUIPrefix + 76)
DECLARE_PMID(kWidgetIDSpace, kShearDlgAxisClusterWidgetID, kLayoutUIPrefix + 77)
DECLARE_PMID(kWidgetIDSpace, kShearDlgAxisHorzRadioWidgetID, kLayoutUIPrefix + 78)
DECLARE_PMID(kWidgetIDSpace, kShearDlgAxisVertRadioWidgetID, kLayoutUIPrefix + 79)
DECLARE_PMID(kWidgetIDSpace, kShearDlgAxisAngleRadioWidgetID, kLayoutUIPrefix + 80)
DECLARE_PMID(kWidgetIDSpace, kShearDlgAxisAngleEditBoxWidgetID, kLayoutUIPrefix + 81)
DECLARE_PMID(kWidgetIDSpace, kShearDlgAxisDegreeSymbolWidgetID, kLayoutUIPrefix + 82	)
// gap
DECLARE_PMID(kWidgetIDSpace, kBlankLayoutButtonWidgetID, kLayoutUIPrefix + 85)
DECLARE_PMID(kWidgetIDSpace, kPageNavigatorAmbiguousPageAlertWidgetID, kLayoutUIPrefix + 86)
DECLARE_PMID(kWidgetIDSpace, kScaleAndNavigateGroupPanelWidgetID, kLayoutUIPrefix + 87)
DECLARE_PMID(kWidgetIDSpace, kLayoutSplitterPanelWidgetID, kLayoutUIPrefix + 88)
DECLARE_PMID(kWidgetIDSpace, kLayoutSecondaryPanelWidgetID, kLayoutUIPrefix + 89)
DECLARE_PMID(kWidgetIDSpace, kNormalViewModeToolWidgetId, kLayoutUIPrefix + 90)
DECLARE_PMID(kWidgetIDSpace, kPreviewModeToolWidgetId, kLayoutUIPrefix + 91)
DECLARE_PMID(kWidgetIDSpace, kLayoutPanelWidgetId, kLayoutUIPrefix + 92)
DECLARE_PMID(kWidgetIDSpace, kBleedModeToolWidgetId, kLayoutUIPrefix + 93)
DECLARE_PMID(kWidgetIDSpace, kSlugModeToolWidgetId, kLayoutUIPrefix + 94)
DECLARE_PMID(kWidgetIDSpace, kLayoutGenericPanelWidgetID, kLayoutUIPrefix + 95)
DECLARE_PMID(kWidgetIDSpace, kDocWinProgressBarWidgetID, kLayoutUIPrefix + 96)
DECLARE_PMID(kWidgetIDSpace, kScaleAndNavigateGroupWidgetID, kLayoutUIPrefix + 97)

DECLARE_PMID(kWidgetIDSpace, kGuideThresholdComboBoxWidgetID, kLayoutUIPrefix + 98)
DECLARE_PMID(kWidgetIDSpace, kGuideColorDropDownWidgetID, kLayoutUIPrefix + 99)
DECLARE_PMID(kWidgetIDSpace, kGuideOptionsParentWidgetId, kLayoutUIPrefix + 100)
DECLARE_PMID(kWidgetIDSpace, kViewLimitTextWidgetId, kLayoutUIPrefix + 101)
DECLARE_PMID(kWidgetIDSpace, kColorTextWidgetId, kLayoutUIPrefix + 102)
DECLARE_PMID(kWidgetIDSpace, kColorGenericPanelWidgetId, kLayoutUIPrefix + 103)
DECLARE_PMID(kWidgetIDSpace, kGuideViewThresTestWidgetId, kLayoutUIPrefix + 104)

DECLARE_PMID(kWidgetIDSpace, kNonOverrideableEntireGroupWidgetID, kLayoutUIPrefix + 105)
DECLARE_PMID(kWidgetIDSpace, kGroupOverrideableAlertParentWidgetID, kLayoutUIPrefix + 106)
DECLARE_PMID(kWidgetIDSpace, kSelectionOverrideableText1WidgetID, kLayoutUIPrefix + 107)
DECLARE_PMID(kWidgetIDSpace, kGroupOverrideableWarningSignWidgetID, kLayoutUIPrefix + 108)
DECLARE_PMID(kWidgetIDSpace, kPresentationModeToolWidgetId, kLayoutUIPrefix + 109)

// ---- Moved from the Group plug-in
DECLARE_PMID(kWidgetIDSpace, kLockEntireGroupWidgetID, kLayoutUIPrefix + 110)
DECLARE_PMID(kWidgetIDSpace, kGroupAlertParentWidgetID, kLayoutUIPrefix + 112)
DECLARE_PMID(kWidgetIDSpace, kSelectionLockedText1WidgetID, kLayoutUIPrefix + 113)
//DECLARE_PMID(kWidgetIDSpace, kSelectionLockedText2WidgetID, kLayoutUIPrefix + 114) //not used
DECLARE_PMID(kWidgetIDSpace, kGroupWarningSignWidgetID, kLayoutUIPrefix + 115)
// ---- end move.

// Go to Page Dialog
DECLARE_PMID(kWidgetIDSpace, kGotoPageDialogWidgetID, kLayoutUIPrefix + 120)
DECLARE_PMID(kWidgetIDSpace, kGotoPageComboBoxWidgetID, kLayoutUIPrefix + 121)
DECLARE_PMID(kWidgetIDSpace, kGotoPageDialogNudgeWidgetID, kLayoutUIPrefix + 122)
DECLARE_PMID(kWidgetIDSpace, kGotoPageDialogPanelWidgetID, kLayoutUIPrefix + 123)

DECLARE_PMID(kWidgetIDSpace, kToggleSplitWindowWidgetID, kLayoutUIPrefix + 124)

DECLARE_PMID(kWidgetIDSpace, kDocStatusPanelWidgetID, kLayoutUIPrefix + 130)
DECLARE_PMID(kWidgetIDSpace, kDocStatusMenuWidgetID, kLayoutUIPrefix + 131)
DECLARE_PMID(kWidgetIDSpace, kScaleAndNavigateRuleWidgetID, kLayoutUIPrefix + 132)
DECLARE_PMID(kWidgetIDSpace, kCloudSyncButtonWidgetID, kLayoutUIPrefix + 133)
DECLARE_PMID(kWidgetIDSpace, kPopupPanelParentWidgetId, kLayoutUIPrefix + 134)
// gap
DECLARE_PMID(kWidgetIDSpace, kResumeBtnPanelWidgetID, kLayoutUIPrefix + 149)
DECLARE_PMID(kWidgetIDSpace, kResumeBtnWidgetID, kLayoutUIPrefix + 150)
DECLARE_PMID(kWidgetIDSpace, kRow4PanelWidgetId, kLayoutUIPrefix + 151)
DECLARE_PMID(kWidgetIDSpace, kApplyBtnPanelWidgetID, kLayoutUIPrefix + 152)
DECLARE_PMID(kWidgetIDSpace, kConflictBtnPanelWidgetID, kLayoutUIPrefix + 153)
DECLARE_PMID(kWidgetIDSpace, kConflictKeepLocalBtnWidgetID, kLayoutUIPrefix + 154)
DECLARE_PMID(kWidgetIDSpace, kConflictSyncRemoteBtnWidgetID, kLayoutUIPrefix + 155)
//DECLARE_PMID(kWidgetIDSpace, kRemeberPrefPanelWidgetID, kLayoutUIPrefix + 156)
DECLARE_PMID(kWidgetIDSpace, kManageSyncSettingsBtnPanelWidgetID, kLayoutUIPrefix + 157)
DECLARE_PMID(kWidgetIDSpace, kManageSyncSettingsBtnWidgetID, kLayoutUIPrefix + 158)
DECLARE_PMID(kWidgetIDSpace, kRetryBtnPanelWidgetID, kLayoutUIPrefix + 159)
DECLARE_PMID(kWidgetIDSpace, kRetryBtnWidgetID, kLayoutUIPrefix + 160)
DECLARE_PMID(kWidgetIDSpace, kRow1OtherTextWidgetID, kLayoutUIPrefix + 161)
DECLARE_PMID(kWidgetIDSpace, kRow2OtherTextWidgetID, kLayoutUIPrefix + 162)
DECLARE_PMID(kWidgetIDSpace, kRow2LongMessageWidgetID, kLayoutUIPrefix + 163)

DECLARE_PMID(kWidgetIDSpace, kLayoutOpenGLWidgetID, kLayoutUIPrefix + 166)
DECLARE_PMID(kWidgetIDSpace, kGPUSoftMessageWidgetID, kLayoutUIPrefix + 167)

DECLARE_PMID(kWidgetIDSpace, kSeperatorModeToolWidgetId, kLayoutUIPrefix + 168)
DECLARE_PMID(kWidgetIDSpace, kViewOptionsToolWidgetID, kLayoutUIPrefix + 169)
DECLARE_PMID(kWidgetIDSpace, kRulersViewOptionsToolWidgetID, kLayoutUIPrefix + 170)
DECLARE_PMID(kWidgetIDSpace, kLeftDummyWidgetID, kLayoutUIPrefix + 171)
DECLARE_PMID(kWidgetIDSpace, kMiddleDummyWidgetID, kLayoutUIPrefix + 172)
DECLARE_PMID(kWidgetIDSpace, kRightDummyWidgetID, kLayoutUIPrefix + 173)

// <Action ID>
// Action IDs
DECLARE_PMID(kActionIDSpace, kZoomInActionID, kLayoutUIPrefix + 1)
DECLARE_PMID(kActionIDSpace, kZoomOutActionID, kLayoutUIPrefix + 2)
DECLARE_PMID(kActionIDSpace, kZoomFitSpreadInWindowActionID, kLayoutUIPrefix +	3)
DECLARE_PMID(kActionIDSpace, kZoomFitPageInWindowActionID, kLayoutUIPrefix + 4)
DECLARE_PMID(kActionIDSpace, kZoomEntirePasteboardActionID, kLayoutUIPrefix +	5)
DECLARE_PMID(kActionIDSpace, kZoomFitSelectionActionID, kLayoutUIPrefix +	6)
DECLARE_PMID(kActionIDSpace, kZoomActualSizeActionID, kLayoutUIPrefix +	7) // zoom to 100%
DECLARE_PMID(kActionIDSpace, kZoom200PercentActionID, kLayoutUIPrefix +	8)	// Zoom to 200%
DECLARE_PMID(kActionIDSpace, kZoom400PercentActionID, kLayoutUIPrefix +	9)	// Zoom to 400%

DECLARE_PMID(kActionIDSpace, kZoom50PercentActionID, kLayoutUIPrefix +	10)	// Zoom to 50%
DECLARE_PMID(kActionIDSpace, kNothingSep1ActionID, kLayoutUIPrefix +	11	)
DECLARE_PMID(kActionIDSpace, kNothingTextSep1ActionID, kLayoutUIPrefix +	12	)
DECLARE_PMID(kActionIDSpace, kGFrameSep1ActionID, kLayoutUIPrefix +	13	)
DECLARE_PMID(kActionIDSpace, kTogglePreviewActionID, kLayoutUIPrefix +	14	)
DECLARE_PMID(kActionIDSpace, kTransformMoveActionID, kLayoutUIPrefix + 15)
DECLARE_PMID(kActionIDSpace, kTransformScaleActionID, kLayoutUIPrefix + 16)
DECLARE_PMID(kActionIDSpace, kTransformRotateActionID, kLayoutUIPrefix + 17)
DECLARE_PMID(kActionIDSpace, kTransformShearActionID, kLayoutUIPrefix + 18)
DECLARE_PMID(kActionIDSpace, kLockZeroPointActionID, kLayoutUIPrefix + 19)

DECLARE_PMID(kActionIDSpace, kZeroPointSep1ActionID, kLayoutUIPrefix + 20)
DECLARE_PMID(kActionIDSpace, kTransformLastAgainActionID, kLayoutUIPrefix + 21)
DECLARE_PMID(kActionIDSpace, kZoomPercentageToggleShortActionID, kLayoutUIPrefix +	22)	// Toggle between last view pct and current pct
DECLARE_PMID(kActionIDSpace, kGotoPageDialogActionID, kLayoutUIPrefix +	23)	// Go to Page... dialog
DECLARE_PMID(kActionIDSpace, kGoToScaleShortActionID, kLayoutUIPrefix +	24)	// Put focus in Layout zoom pct widget
DECLARE_PMID(kActionIDSpace, kZeroPointSep2ActionID, kLayoutUIPrefix + 25)
DECLARE_PMID(kActionIDSpace, kGoToPageShortActionID, kLayoutUIPrefix +	26)	// Put focus in Page Navigation widget
DECLARE_PMID(kActionIDSpace, kRotate180ActionID, kLayoutUIPrefix + 27)
DECLARE_PMID(kActionIDSpace, kRotate90CWActionID, kLayoutUIPrefix + 28)
DECLARE_PMID(kActionIDSpace, kRotate90CCWActionID, kLayoutUIPrefix + 29)

DECLARE_PMID(kActionIDSpace, kFlipHorizontalActionID, kLayoutUIPrefix + 30)
DECLARE_PMID(kActionIDSpace, kPageDownOneScreenKBSCActionID, kLayoutUIPrefix +	31)	// Scroll down one screen amount
DECLARE_PMID(kActionIDSpace, kPageUpOneScreenKBSCActionID, kLayoutUIPrefix +	32)	// Scroll up one screen
DECLARE_PMID(kActionIDSpace, kPreviousSpreadKBSCActionID, kLayoutUIPrefix +	33)	// Goto previous spread
DECLARE_PMID(kActionIDSpace, kNextSpreadKBSCActionID, kLayoutUIPrefix +	34)	// Goto next spread
DECLARE_PMID(kActionIDSpace, kFirstSpreadKBSCActionID, kLayoutUIPrefix +	35)	// Goto first spread
DECLARE_PMID(kActionIDSpace, kLastSpreadKBSCActionID, kLayoutUIPrefix +	36)	// Goto last spread
DECLARE_PMID(kActionIDSpace, kToggleSelectionToolShortActionID, kLayoutUIPrefix +	37)	// Toggle between Select and Direct select tools
DECLARE_PMID(kActionIDSpace, kPointerToolActionID, kLayoutUIPrefix +	38	)
DECLARE_PMID(kActionIDSpace, kDirectSelectToolActionID, kLayoutUIPrefix +	39	)

DECLARE_PMID(kActionIDSpace, kRotateToolActionID, kLayoutUIPrefix +	40	)
DECLARE_PMID(kActionIDSpace, kScaleToolActionID, kLayoutUIPrefix +	41	)
DECLARE_PMID(kActionIDSpace, kGrabberHandToolActionID, kLayoutUIPrefix +	42	)
DECLARE_PMID(kActionIDSpace, kShearToolActionID, kLayoutUIPrefix +	43	)
DECLARE_PMID(kActionIDSpace, kCloseModalessDialogActionID, kLayoutUIPrefix +	44	)
DECLARE_PMID(kActionIDSpace, kNormalViewModeToolActionID, kLayoutUIPrefix +	45	)
DECLARE_PMID(kActionIDSpace, kPreviewModeToolActionID, kLayoutUIPrefix +	46	)
DECLARE_PMID(kActionIDSpace, kTransformMoveGuidesActionID, kLayoutUIPrefix +	47	)
DECLARE_PMID(kActionIDSpace, kGuideOptionsActionID, kLayoutUIPrefix + 48)
DECLARE_PMID(kActionIDSpace, kSelectAllGuidesActionID, kLayoutUIPrefix + 49)

DECLARE_PMID(kActionIDSpace, kRightMouseGuideSep1ActionID, kLayoutUIPrefix + 50)
DECLARE_PMID(kActionIDSpace, kRightMouseGuideSep2ActionID, kLayoutUIPrefix + 51)
DECLARE_PMID(kActionIDSpace, kTransformSubmenuSep1ActionID, kLayoutUIPrefix + 52)
DECLARE_PMID(kActionIDSpace, kTransformAgainActionID, kLayoutUIPrefix + 53)
DECLARE_PMID(kActionIDSpace, kPreviewToBleedModeActionID, kLayoutUIPrefix + 54)
DECLARE_PMID(kActionIDSpace, kPreviewToSlugModeActionID, kLayoutUIPrefix + 55)
DECLARE_PMID(kActionIDSpace, kScreenViewSepActionID, kLayoutUIPrefix + 56)
DECLARE_PMID(kActionIDSpace, kZoomSepActionID, kLayoutUIPrefix + 57)
DECLARE_PMID(kActionIDSpace, kTransformLastIndividuallyAgainActionID, kLayoutUIPrefix + 58)
DECLARE_PMID(kActionIDSpace, kTransformAgainIndividuallyActionID, kLayoutUIPrefix + 59)

// ---- Moved from the Group plug-in
DECLARE_PMID(kActionIDSpace, kGroupActionID, kLayoutUIPrefix + 60)
DECLARE_PMID(kActionIDSpace, kUngroupActionID, kLayoutUIPrefix + 61)
// ---- end move.
DECLARE_PMID(kActionIDSpace, kFlipVerticalActionID, kLayoutUIPrefix + 62)
DECLARE_PMID(kActionIDSpace, kTransformSubmenuSep2ActionID, kLayoutUIPrefix + 63)
DECLARE_PMID(kActionIDSpace, kPageNumSepActionID, kLayoutUIPrefix + 64)
DECLARE_PMID(kActionIDSpace, kRightMouseGuideSep3ActionID, kLayoutUIPrefix + 65)
DECLARE_PMID(kActionIDSpace, kDeleteAllGuidesActionID, kLayoutUIPrefix + 66)
DECLARE_PMID(kActionIDSpace, kClearTransformationsActionID, kLayoutUIPrefix + 67)
DECLARE_PMID(kActionIDSpace, kRedefineScalingActionID, kLayoutUIPrefix + 68)
DECLARE_PMID(kActionIDSpace, kTransformSubmenuSep3ActionID, kLayoutUIPrefix + 69)
DECLARE_PMID(kActionIDSpace, kDocStatusRevealInOSActionID, kLayoutUIPrefix + 70)
DECLARE_PMID(kActionIDSpace, kDocStatusRevealInBrowserActionID, kLayoutUIPrefix + 71)

DECLARE_PMID(kActionIDSpace, kHideActionID, kLayoutUIPrefix + 72)
DECLARE_PMID(kActionIDSpace, kShowAllOnSpreadActionID, kLayoutUIPrefix + 73)
DECLARE_PMID(kActionIDSpace, kToggleLiveEditModeActionID, kLayoutUIPrefix + 74)
DECLARE_PMID(kActionIDSpace, kLeftSpreadKBSCActionID, kLayoutUIPrefix +	75)	// left spread in binding order
DECLARE_PMID(kActionIDSpace, kRightSpreadKBSCActionID, kLayoutUIPrefix +	76)	// right spread in binding order

DECLARE_PMID(kActionIDSpace, kSetPresentationBackgroundBlackActionID, kLayoutUIPrefix + 77)
DECLARE_PMID(kActionIDSpace, kSetPresentationBackgroundGrayActionID, kLayoutUIPrefix + 78)
DECLARE_PMID(kActionIDSpace, kSetPresentationBackgroundWhiteActionID, kLayoutUIPrefix + 79)
DECLARE_PMID(kActionIDSpace, kPresentationModeActionID, kLayoutUIPrefix + 80)
DECLARE_PMID(kActionIDSpace, kPresentationSepActionID, kLayoutUIPrefix + 81)
//gap
DECLARE_PMID(kActionIDSpace, kGuideTypeRulerActionID, kLayoutUIPrefix + 83)
DECLARE_PMID(kActionIDSpace, kGuideTypeLiquidActionID, kLayoutUIPrefix + 84)
DECLARE_PMID(kActionIDSpace, kGuideTypeMagneticActionID, kLayoutUIPrefix + 85)
DECLARE_PMID(kActionIDSpace, kGuideTypeGrowZoneActionID, kLayoutUIPrefix + 86)

DECLARE_PMID(kActionIDSpace, kZoomSep2ActionID,						kLayoutUIPrefix + 87	)
DECLARE_PMID(kActionIDSpace, kMatchPasteboardToThemeColorActionID,	kLayoutUIPrefix + 88)
DECLARE_PMID(kActionIDSpace, kGFrameSep2ActionID,					kLayoutUIPrefix + 89)
//gap
DECLARE_PMID(kActionIDSpace, kSplitWindowActionID, kLayoutUIPrefix + 91)
DECLARE_PMID(kActionIDSpace, kMatchZoomActionID, kLayoutUIPrefix + 92)
DECLARE_PMID(kActionIDSpace, kMatchLocationActionID, kLayoutUIPrefix + 93)
DECLARE_PMID(kActionIDSpace, kMatchZoomAndLocationActionID, kLayoutUIPrefix + 94)
DECLARE_PMID(kActionIDSpace, kSplitSepActionID, kLayoutUIPrefix + 95)
DECLARE_PMID(kActionIDSpace, kAlwaysMatchZoomActionID, kLayoutUIPrefix + 96)
DECLARE_PMID(kActionIDSpace, kAlwaysMatchLocationActionID, kLayoutUIPrefix + 97)

DECLARE_PMID(kActionIDSpace, kDrawingToolActionID, kLayoutUIPrefix + 98)

//
//Script Element IDs
//

//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kGrabberPrefsObjectScriptElement,		kLayoutUIPrefix + 20)

//Events

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kGrabberPrefsPropertyScriptElement,		kLayoutUIPrefix + 120)
DECLARE_PMID(kScriptInfoIDSpace, kGrabberPanningPropertyScriptElement,		kLayoutUIPrefix + 121)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kPanningTypesEnumScriptElement,			kLayoutUIPrefix + 200)

//GUIDS
// {6B77AC97-5342-4f7b-AD1B-F2F9168243BB}
#define kGrabberPref_CLSID { 0x6b77ac97, 0x5342, 0x4f7b, { 0xad, 0x1b, 0xf2, 0xf9, 0x16, 0x82, 0x43, 0xbb } }

//---------------------------------------------------
// InvalHandlerTypeID
//---------------------------------------------------
DECLARE_PMID(kInvalHandlerIDSpace, kSnapToInvalHandlerID, kLayoutUIPrefix + 1)

//----------------------------------------------------------------------------------------
// Don't Show Again Alert IDs
//----------------------------------------------------------------------------------------
#define kPageSizesDontMatchAlertID                  kLayoutUIPrefix + 1
#define kUngroupingGroupsWithEffectsAlertID			kLayoutUIPrefix + 2
#define kDeleteWillTriggerSmartTextReflowAlertID	kLayoutUIPrefix + 3
#define kEndnoteStoryDeletionAlertID				kLayoutUIPrefix + 4

// Resource IDs for Pages Panel dialogs
#define kApplyMasterDialogRsrcID        2800        // Resource ID of New master dialog


#endif // __LayoutUIID_h__
