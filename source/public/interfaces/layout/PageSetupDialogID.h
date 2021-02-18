//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/PageSetupDialogID.h $
//  
//  Owner: Tommy Donovan
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
//  Contains IDs used by the page size panel plug-in
//  
//========================================================================================

#ifndef __PageSetupDialogID__
#define __PageSetupDialogID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kPageSetupDialogPrefix	RezLong(0x6100)

// <Start IDC>
// PluginID
#define kPageSetupDialogPluginName 			"Page Setup Dialog"
DECLARE_PMID(kPlugInIDSpace, kPageSetupDialogPluginID, kPageSetupDialogPrefix + 1)

// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kPageSetupDialogBoss, kPageSetupDialogPrefix + 1)
DECLARE_PMID(kClassIDSpace, kNewDocDialogBoss, kPageSetupDialogPrefix + 2)
DECLARE_PMID(kClassIDSpace, kTouchNewDocDialogBoss, kPageSetupDialogPrefix + 3)
DECLARE_PMID(kClassIDSpace, kPageSetupDialogMenuActionBoss, kPageSetupDialogPrefix + 4)
DECLARE_PMID(kClassIDSpace, kTouchNewDocDialogWindowBoss, kPageSetupDialogPrefix + 5)
DECLARE_PMID(kClassIDSpace, kDocSetupPropertiesBoss, kPageSetupDialogPrefix + 6)
DECLARE_PMID(kClassIDSpace, kAdaptiveOptionsDialogBoss, kPageSetupDialogPrefix + 7)

//gap
DECLARE_PMID(kClassIDSpace, kDocSetupDialogCmdBoss, kPageSetupDialogPrefix + 10)
DECLARE_PMID(kClassIDSpace, kMoreOrLessButtonObserverBoss, kPageSetupDialogPrefix + 11)
// gap
DECLARE_PMID(kClassIDSpace, kDocStyleEditMenuActionBoss, kPageSetupDialogPrefix + 14)
DECLARE_PMID(kClassIDSpace, kDocStyleShortcutActionBoss, kPageSetupDialogPrefix + 15)
//gap
DECLARE_PMID(kClassIDSpace, kTouchNewDocPresetButtonBoss, kPageSetupDialogPrefix + 20)
DECLARE_PMID(kClassIDSpace, kTouchMoreOrLessButtonBoss, kPageSetupDialogPrefix + 21)
//gap
DECLARE_PMID(kClassIDSpace, kNewDocumentDialogClosedBoss, kPageSetupDialogPrefix + 25)
DECLARE_PMID(kClassIDSpace, kPSColumnMarginPanelBoss, kPageSetupDialogPrefix + 26)


DECLARE_PMID(kMessageIDSpace, kPageSizePopupSelectionChangeMessage, kPageSetupDialogPrefix + 100) 

// <Interface ID>
// Interface IDs
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGESIZEPOPUPCONTROLLER, kPageSetupDialogPrefix + 34)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGESIZELASTCHOICE, kPageSetupDialogPrefix + 35)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRIGGERPOINTADAPTIVE, kPageSetupDialogPrefix + 36)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOACHMARKSHOWN, kPageSetupDialogPrefix + 37)

// <Implementation ID>
// Implementation IDs
DECLARE_PMID(kImplementationIDSpace, kPageSizePopupControllerImpl, kPageSetupDialogPrefix + 41)
// gap
DECLARE_PMID(kImplementationIDSpace, kPageSetupDialogControllerImpl, kPageSetupDialogPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kPageSetupDialogObserverImpl, kPageSetupDialogPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kPageSetupDialogMenuActionImpl, kPageSetupDialogPrefix + 54)

//touch related
DECLARE_PMID(kImplementationIDSpace, kTouchCustomFormatButtonObserverImpl, kPageSetupDialogPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kTouchNewDocDialogObserverImpl, kPageSetupDialogPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kTouchNewDocDialogControllerImpl, kPageSetupDialogPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kTouchNewDocPresetButtonViewImpl, kPageSetupDialogPrefix + 58)
//gap
DECLARE_PMID(kImplementationIDSpace, kTouchNewDocDialogWindowImpl, kPageSetupDialogPrefix + 60)

DECLARE_PMID(kImplementationIDSpace, kDocSetupDialogCmdImpl, kPageSetupDialogPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kMoreOrLessButtonObserverImpl, kPageSetupDialogPrefix + 62)

DECLARE_PMID(kImplementationIDSpace, kTouchNewDocMoreOrLessButtonViewImpl, kPageSetupDialogPrefix + 63)
// gap
DECLARE_PMID(kImplementationIDSpace, kDocStyleDynMenuInfoImpl, kPageSetupDialogPrefix + 65)
//gap
DECLARE_PMID(kImplementationIDSpace, kControlStripPageSizePopupControllerImpl, kPageSetupDialogPrefix + 68)

DECLARE_PMID(kImplementationIDSpace, kPageSizePresetDDLEventHandlerImpl, kPageSetupDialogPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kPageSizeLastChoiceImpl, kPageSetupDialogPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kPageSizePresetDDLOpenCloseHandlerImpl, kPageSetupDialogPrefix + 71) // Note: Replaces kPageSizePresetDDLEventHandlerImpl for drover based widget

DECLARE_PMID(kImplementationIDSpace, kDocStyleShortcutActionImpl, kPageSetupDialogPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kDocSetupPropertiesObserverImpl, kPageSetupDialogPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kPropertiesPanelPageSizePopupControllerImpl, kPageSetupDialogPrefix + 74)

DECLARE_PMID(kImplementationIDSpace, kAdaptiveOptionsDialogCreatorImpl, kPageSetupDialogPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kAdaptiveOptionsDialogObserverImpl, kPageSetupDialogPrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kAdaptiveOptionsDialogControllerImpl, kPageSetupDialogPrefix + 77)
DECLARE_PMID(kImplementationIDSpace, kAdaptiveTriggerPointImpl, kPageSetupDialogPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kCoachMarkBoolDataImpl, kPageSetupDialogPrefix + 79)

// <Widget ID>
// Widget IDs
DECLARE_PMID(kWidgetIDSpace, kPageBindingContainerWidgetID, kPageSetupDialogPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kIDPageSizePopupWidgetID, kPageSetupDialogPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kPageSizeEditWidthWidgetID, kPageSetupDialogPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kIDPageSizeWidthNudgeWidgetID, kPageSetupDialogPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kPageSizeEditLengthWidgetID, kPageSetupDialogPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kPageSizeLengthNudgeWidgetID, kPageSetupDialogPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kPageSizeEditNumPagesWidgetID, kPageSetupDialogPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kRestartPageNumCheckBoxWidgetID, kPageSetupDialogPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kPageTallIconWidgetID, kPageSetupDialogPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kPageWideIconWidgetID, kPageSetupDialogPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kPageBindingRightToLeftIconWidgetID, kPageSetupDialogPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kPageBindingLeftToRightIconWidgetID, kPageSetupDialogPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kIDPageSizePanelWidgetID, kPageSetupDialogPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kMarginPanelWidgetID, kPageSetupDialogPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kPSMarginTopTextWidgetID, kPageSetupDialogPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kPSMarginTopEditWidgetID, kPageSetupDialogPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kPSMarginTopNudgeWidgetID, kPageSetupDialogPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kPSMarginInsideTextWidgetID, kPageSetupDialogPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kPSMarginLeftTextWidgetID, kPageSetupDialogPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kPSMarginInsideEditWidgetID, kPageSetupDialogPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kPSMarginLeftInsideNudgeWidgetID, kPageSetupDialogPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kPSMarginBottomTextWidgetID, kPageSetupDialogPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kPSMarginBottomEditWidgetID, kPageSetupDialogPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kPSMarginBottomNudgeWidgetID, kPageSetupDialogPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kPSMarginOutsideTextWidgetID, kPageSetupDialogPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kPSMarginRightTextWidgetID, kPageSetupDialogPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kPSMarginOutsideEditWidgetID, kPageSetupDialogPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kPSMarginRightOutsideNudgeWidgetID, kPageSetupDialogPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kPSColumnPanelWidgetID, kPageSetupDialogPrefix + 29)
DECLARE_PMID(kWidgetIDSpace, kPSColumnNumberTextWidgetID, kPageSetupDialogPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kPSColumnNumberEditWidgetID, kPageSetupDialogPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kPSColumnNumberNudgeWidgetID, kPageSetupDialogPrefix + 32)
#ifdef PPI_PAGESIZE_WIDGET
DECLARE_PMID(kWidgetIDSpace, kPageSizeEditPPIWidgetID, kPageSetupDialogPrefix + 33)
#endif
DECLARE_PMID(kWidgetIDSpace, kPSColumnGutterTextWidgetID, kPageSetupDialogPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kPSColumnHGutterEditWidgetID, kPageSetupDialogPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kPSColumnVGutterEditWidgetID, kPageSetupDialogPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kPSColumnGutterNudgeWidgetID, kPageSetupDialogPrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kPSColumnHorzIconWidgetID, kPageSetupDialogPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kPSColumnVertIconWidgetID, kPageSetupDialogPrefix + 39)
#ifdef PPI_PAGESIZE_WIDGET
DECLARE_PMID(kWidgetIDSpace, kIDPageSizePPINudgeWidgetID, kPageSetupDialogPrefix + 40)
#endif
DECLARE_PMID(kWidgetIDSpace, kPSAutoTextFrameCheckBoxWidgetID, kPageSetupDialogPrefix + 41)
DECLARE_PMID(kWidgetIDSpace, kPSNumPagesTextWidgetId, kPageSetupDialogPrefix + 42)
DECLARE_PMID(kWidgetIDSpace, kPSIntentDropDownWidgetID, kPageSetupDialogPrefix + 43)
DECLARE_PMID(kWidgetIDSpace, kPSWidthTextWidgetId, kPageSetupDialogPrefix + 44)
DECLARE_PMID(kWidgetIDSpace, kPSHeightTextWidgetId, kPageSetupDialogPrefix + 45)
DECLARE_PMID(kWidgetIDSpace, kPSOrientationTextWidgetId, kPageSetupDialogPrefix + 46)
DECLARE_PMID(kWidgetIDSpace, kPSPanelTextWidgetId, kPageSetupDialogPrefix + 47)
DECLARE_PMID(kWidgetIDSpace, kPSStartPageNumberTextWidgetId, kPageSetupDialogPrefix + 48)
DECLARE_PMID(kWidgetIDSpace, kPSStartPageNumberEditWidgetID, kPageSetupDialogPrefix + 49)
DECLARE_PMID(kWidgetIDSpace, kPSPageGroupWidgetId, kPageSetupDialogPrefix + 50)
DECLARE_PMID(kWidgetIDSpace, kPSMarginGroupWidgetId, kPageSetupDialogPrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kPSColumnGroupWidgetId, kPageSetupDialogPrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kPageSetupDialogWidgetId, kPageSetupDialogPrefix + 53)
DECLARE_PMID(kWidgetIDSpace, kNewDocDialogWidgetId, kPageSetupDialogPrefix + 54)
DECLARE_PMID(kWidgetIDSpace, kPSPageSizeGroupWidgetID, kPageSetupDialogPrefix + 55)
DECLARE_PMID(kWidgetIDSpace, kPSFacingPagesCheckBoxWidgetID, kPageSetupDialogPrefix + 56)
DECLARE_PMID(kWidgetIDSpace, kPageOrientationHiliteBorderWidgetID, kPageSetupDialogPrefix + 57)

#ifdef PPI_PAGESIZE_WIDGET
DECLARE_PMID(kWidgetIDSpace, kPSPPITextWidgetId, kPageSetupDialogPrefix +58)
#endif
DECLARE_PMID(kWidgetIDSpace, kPSIntentStaticTextWidgetID, kPageSetupDialogPrefix + 59)
DECLARE_PMID(kWidgetIDSpace, kPSBindingTextWidgetId, kPageSetupDialogPrefix + 60)	// Hotaka (K2J)
DECLARE_PMID(kWidgetIDSpace, kPSTitleClusterWidgetId, kPageSetupDialogPrefix + 61)	// Hotaka (K2J)
DECLARE_PMID(kWidgetIDSpace, kPSColumnDirectionTextWidgetID, kPageSetupDialogPrefix + 62)	// Hotaka (K2J)
DECLARE_PMID(kWidgetIDSpace, kPSColumnDirectionClusterWidgetID, kPageSetupDialogPrefix + 63)	// Hotaka (K2J)
DECLARE_PMID(kWidgetIDSpace, kPSRadioButtonGroupWidgetID, kPageSetupDialogPrefix + 64)	// Hotaka (K2J)
DECLARE_PMID(kWidgetIDSpace, kPSLayoutGridButtonWidgetID, kPageSetupDialogPrefix + 65)	// Hotaka (K2J)
DECLARE_PMID(kWidgetIDSpace, kPSLayoutGridDefaultButtonWidgetID, kPageSetupDialogPrefix + 66)	// Hotaka (K2J)
DECLARE_PMID(kWidgetIDSpace, kPSMarginsColumnsButtonWidgetID, kPageSetupDialogPrefix + 67)	// Hotaka (K2J)
DECLARE_PMID(kWidgetIDSpace, kPSMarginsColumnsDefaultButtonWidgetID, kPageSetupDialogPrefix + 68)	// Hotaka (K2J)
DECLARE_PMID(kWidgetIDSpace, kPSCreateDocumentTextWidgetID, kPageSetupDialogPrefix + 69)	// Hotaka (K2J)
DECLARE_PMID(kWidgetIDSpace, kCJKNewDocDialogWidgetId, kPageSetupDialogPrefix + 70)	// Hotaka (K2J)
DECLARE_PMID(kWidgetIDSpace, kPageBindingHiliteBorderWidgetID, kPageSetupDialogPrefix + 71) // Hotaka
#ifdef PPI_PAGESIZE_WIDGET
DECLARE_PMID(kWidgetIDSpace, kPageSizePPINudgeWidgetID, kPageSetupDialogPrefix + 72)
DECLARE_PMID(kWidgetIDSpace, kPPIEditPanelWidgetID, kPageSetupDialogPrefix + 73)
DECLARE_PMID(kWidgetIDSpace, kPPIScaleStaticWidgetId, kPageSetupDialogPrefix + 74)
#endif
DECLARE_PMID(kWidgetIDSpace, kPSMarginsColumnsButtonParentWidgetID, kPageSetupDialogPrefix + 75)
DECLARE_PMID(kWidgetIDSpace, kPSMarginsColumnsDefaultButtonParentWidgetID, kPageSetupDialogPrefix + 76)
DECLARE_PMID(kWidgetIDSpace, kPSLayoutGridButtonParentWidgetID, kPageSetupDialogPrefix + 77)
DECLARE_PMID(kWidgetIDSpace, kPSLayoutGridDefaultButtonParentWidgetID, kPageSetupDialogPrefix + 78)
// gap
DECLARE_PMID(kWidgetIDSpace, kPSSaveStyleButtonWidgetID, kPageSetupDialogPrefix + 80)
DECLARE_PMID(kWidgetIDSpace, kPSMoreLessButtonWidgetID, kPageSetupDialogPrefix + 81)
DECLARE_PMID(kWidgetIDSpace, kPSExpandedGroupWidgetID, kPageSetupDialogPrefix + 82)
DECLARE_PMID(kWidgetIDSpace, kLayoutGroupWidgetId, kPageSetupDialogPrefix + 83)
DECLARE_PMID(kWidgetIDSpace, kPSLayoutGroupTextWidgetId, kPageSetupDialogPrefix + 84)
DECLARE_PMID(kWidgetIDSpace, kPSLayoutTopTextWidgetId, kPageSetupDialogPrefix + 85)
DECLARE_PMID(kWidgetIDSpace, kPSLayoutBottomTextWidgetId, kPageSetupDialogPrefix + 86)
DECLARE_PMID(kWidgetIDSpace, kPSLayoutInsideTextWidgetId, kPageSetupDialogPrefix + 87)
DECLARE_PMID(kWidgetIDSpace, kPSLayoutOutsideTextWidgetId, kPageSetupDialogPrefix + 88)
DECLARE_PMID(kWidgetIDSpace, kPSLayoutBleedTextWidgetId, kPageSetupDialogPrefix + 89)
DECLARE_PMID(kWidgetIDSpace, kPSLayoutSlugTextWidgetId, kPageSetupDialogPrefix + 90)
DECLARE_PMID(kWidgetIDSpace, kPSLayoutBleedChainWidgetId, kPageSetupDialogPrefix + 91)
DECLARE_PMID(kWidgetIDSpace, kPSLayoutSlugChainWidgetId, kPageSetupDialogPrefix + 92)
DECLARE_PMID(kWidgetIDSpace, kPSBleedAndSlugGroupHeaderWidgetID, kPageSetupDialogPrefix + 93)
DECLARE_PMID(kWidgetIDSpace, kPSBleedTopEditWidgetID, kPageSetupDialogPrefix + 94)
DECLARE_PMID(kWidgetIDSpace, kPSBleedBottomEditWidgetID, kPageSetupDialogPrefix + 95)
DECLARE_PMID(kWidgetIDSpace, kPSBleedInsideEditWidgetID, kPageSetupDialogPrefix + 96)
DECLARE_PMID(kWidgetIDSpace, kPSBleedOutsideEditWidgetID, kPageSetupDialogPrefix + 97)
DECLARE_PMID(kWidgetIDSpace, kPSSlugTopEditWidgetID, kPageSetupDialogPrefix + 98)
DECLARE_PMID(kWidgetIDSpace, kPSSlugBottomEditWidgetID, kPageSetupDialogPrefix + 99)
DECLARE_PMID(kWidgetIDSpace, kPSSlugInsideEditWidgetID, kPageSetupDialogPrefix + 100)
DECLARE_PMID(kWidgetIDSpace, kPSSlugOutsideEditWidgetID, kPageSetupDialogPrefix + 101)
DECLARE_PMID(kWidgetIDSpace, kPSLayoutLeftTextWidgetId, kPageSetupDialogPrefix + 102)
DECLARE_PMID(kWidgetIDSpace, kPSLayoutRightTextWidgetId, kPageSetupDialogPrefix + 103)
DECLARE_PMID(kWidgetIDSpace, kPSLayoutMarginsChainWidgetId, kPageSetupDialogPrefix + 104)
DECLARE_PMID(kWidgetIDSpace, kPSJButtonsGroupWidgetID, kPageSetupDialogPrefix + 105)
DECLARE_PMID(kWidgetIDSpace, kDocumentStylePopupWidgetID, kPageSetupDialogPrefix + 106)
DECLARE_PMID(kWidgetIDSpace, kDocumentStyleLabelWidgetID, kPageSetupDialogPrefix + 107)
DECLARE_PMID(kWidgetIDSpace, kDocumentStyleNameWidgetID, kPageSetupDialogPrefix + 108)

DECLARE_PMID(kWidgetIDSpace, kDocumentStyleSaveButtonWidgetID, kPageSetupDialogPrefix + 109)
DECLARE_PMID(kWidgetIDSpace, kDocumentStyleDeleteButtonWidgetID, kPageSetupDialogPrefix + 110)
DECLARE_PMID(kWidgetIDSpace, kDocumentDirectionWidgetID, kPageSetupDialogPrefix + 111)
DECLARE_PMID(kWidgetIDSpace, kDocumentShowLayoutGridWidgetID, kPageSetupDialogPrefix + 112)
DECLARE_PMID(kWidgetIDSpace, kDocumentLayoutGridSettingsWidgetID, kPageSetupDialogPrefix + 113)
DECLARE_PMID(kWidgetIDSpace, kBleedSpacerWidgetID, kPageSetupDialogPrefix + 114)
DECLARE_PMID(kWidgetIDSpace, kMarginTypeDropDownWidgetID, kPageSetupDialogPrefix + 115)
DECLARE_PMID(kWidgetIDSpace, kPSMarginInsideOutsidePanelWidgetID, kPageSetupDialogPrefix + 116)
DECLARE_PMID(kWidgetIDSpace, kPSMarginLeftRightPanelWidgetID, kPageSetupDialogPrefix + 117)
DECLARE_PMID(kWidgetIDSpace, kPSLayoutInsideOutsidePanelWidgetID, kPageSetupDialogPrefix + 118)
DECLARE_PMID(kWidgetIDSpace, kPSLayoutLeftRightPanelWidgetID, kPageSetupDialogPrefix + 119)
DECLARE_PMID(kWidgetIDSpace, kMarginAndColumnWidgetID, kPageSetupDialogPrefix + 120)
DECLARE_PMID(kWidgetIDSpace, kPSColumnHGutterNudgeWidgetID, kPageSetupDialogPrefix + 121)
DECLARE_PMID(kWidgetIDSpace, kPSColumnVGutterNudgeWidgetID, kPageSetupDialogPrefix + 122)
DECLARE_PMID(kWidgetIDSpace, kAlignObjectsCheckBoxWidgetID, kPageSetupDialogPrefix + 123)

//gap
//touch related
DECLARE_PMID(kWidgetIDSpace, kTouchNewDocDialogWidgetId, kPageSetupDialogPrefix + 125)
DECLARE_PMID(kWidgetIDSpace, kNewDocPresetIPhone5IconWidgetID, kPageSetupDialogPrefix + 126)
DECLARE_PMID(kWidgetIDSpace, kNewDocPresetIPhone6IconWidgetID, kPageSetupDialogPrefix + 127)
DECLARE_PMID(kWidgetIDSpace, kNewDocPresetIPhone6PlusIconWidgetID, kPageSetupDialogPrefix + 128)
DECLARE_PMID(kWidgetIDSpace, kNewDocPresetIPadPortraitIconWidgetID, kPageSetupDialogPrefix + 129)
DECLARE_PMID(kWidgetIDSpace, kNewDocPresetIPadLandscapeIconWidgetID, kPageSetupDialogPrefix + 130)
DECLARE_PMID(kWidgetIDSpace, kNewDocPresetLetterIconWidgetID, kPageSetupDialogPrefix + 131)
DECLARE_PMID(kWidgetIDSpace, kNewDocPresetA4PortraitIconWidgetID, kPageSetupDialogPrefix + 132)
DECLARE_PMID(kWidgetIDSpace, kNewDocPresetA4LandscapeIconWidgetID, kPageSetupDialogPrefix + 133)
DECLARE_PMID(kWidgetIDSpace, kNewDocPresetTabloidIconWidgetID, kPageSetupDialogPrefix + 134)
DECLARE_PMID(kWidgetIDSpace, kNewDocPresetBusinessCardIconWidgetID, kPageSetupDialogPrefix + 135)
DECLARE_PMID(kWidgetIDSpace, kNewDocPresetWebIconWidgetID, kPageSetupDialogPrefix + 136)
DECLARE_PMID(kWidgetIDSpace, kNewDocPresetWebCommonIconWidgetID, kPageSetupDialogPrefix + 137)
DECLARE_PMID(kWidgetIDSpace, kTouchNewDocFormatsGroupWidgetId, kPageSetupDialogPrefix + 138)
DECLARE_PMID(kWidgetIDSpace, kTouchNewDocPanelWidgetId, kPageSetupDialogPrefix + 139)
DECLARE_PMID(kWidgetIDSpace, kTouchNewDocFormatNameWidgetID, kPageSetupDialogPrefix + 140)
DECLARE_PMID(kWidgetIDSpace, kTouchOKCancelGroupWidgetId, kPageSetupDialogPrefix + 141)
DECLARE_PMID(kWidgetIDSpace, kCustomFormatSpacerWidgetID, kPageSetupDialogPrefix + 142)
DECLARE_PMID(kWidgetIDSpace, kTouchCustomFormatGroupHeaderWidgetID, kPageSetupDialogPrefix + 143)
DECLARE_PMID(kWidgetIDSpace, kTouchWidthTextWidgetId, kPageSetupDialogPrefix + 144)
DECLARE_PMID(kWidgetIDSpace, kTouchHeightTextWidgetId, kPageSetupDialogPrefix + 145)
DECLARE_PMID(kWidgetIDSpace, kTouchPageSizeEditWidthWidgetID, kPageSetupDialogPrefix + 146)
DECLARE_PMID(kWidgetIDSpace, kTouchPageSizeEditLengthWidgetID, kPageSetupDialogPrefix + 147)
DECLARE_PMID(kWidgetIDSpace, kTouchIDPageSizeWidthNudgeWidgetID, kPageSetupDialogPrefix + 148)
DECLARE_PMID(kWidgetIDSpace, kTouchPageSizeLengthNudgeWidgetID, kPageSetupDialogPrefix + 149)
DECLARE_PMID(kWidgetIDSpace, kTouchOrientationTextWidgetId, kPageSetupDialogPrefix + 150)
DECLARE_PMID(kWidgetIDSpace, kTouchPageOrientationHiliteBorderWidgetID, kPageSetupDialogPrefix + 151)
DECLARE_PMID(kWidgetIDSpace, kTouchPSPanelTextWidgetId, kPageSetupDialogPrefix + 152)
DECLARE_PMID(kWidgetIDSpace, kTouchPageTallIconWidgetID, kPageSetupDialogPrefix + 153)
DECLARE_PMID(kWidgetIDSpace, kTouchPageWideIconWidgetID, kPageSetupDialogPrefix + 154)
DECLARE_PMID(kWidgetIDSpace, kTouchNewDocAlignmentAdjustWidgetID, kPageSetupDialogPrefix + 155)
DECLARE_PMID(kWidgetIDSpace, kTouchNewDocShowMoreButtonWidgetID, kPageSetupDialogPrefix + 156)
DECLARE_PMID(kWidgetIDSpace, kTouchNewDocShowLessButtonWidgetID, kPageSetupDialogPrefix + 157)
DECLARE_PMID(kWidgetIDSpace, kEnableAdaptiveLayoutButtonWidgetID, kPageSetupDialogPrefix + 158)
DECLARE_PMID(kWidgetIDSpace, kAdaptiveOptionButtonWidgetID, kPageSetupDialogPrefix + 159)
DECLARE_PMID(kWidgetIDSpace, kAdaptiveOptionsDialogWidgetID, kPageSetupDialogPrefix + 160)
DECLARE_PMID(kWidgetIDSpace, kScaleFontSizeLeadingButtonWidgetID, kPageSetupDialogPrefix + 161)
DECLARE_PMID(kWidgetIDSpace, kScaleLockedContentButtonWidgetID, kPageSetupDialogPrefix + 162)
DECLARE_PMID(kWidgetIDSpace, kSetFontSizeLimitButtonWidgetID, kPageSetupDialogPrefix + 163)
DECLARE_PMID(kWidgetIDSpace, kMinimumEditBoxWidgetID, kPageSetupDialogPrefix + 164)
DECLARE_PMID(kWidgetIDSpace, kMaximumEditBoxWidgetID, kPageSetupDialogPrefix + 165)
DECLARE_PMID(kWidgetIDSpace, kFontSizeParentWidgetID, kPageSetupDialogPrefix + 166)
DECLARE_PMID(kWidgetIDSpace, kMinMaxParentWidgetID, kPageSetupDialogPrefix + 167)
DECLARE_PMID(kWidgetIDSpace, kLayoutAdjustmentGroupWidgetId, kPageSetupDialogPrefix + 168)
DECLARE_PMID(kWidgetIDSpace, kLayoutAdjustmentPanelWidgetID, kPageSetupDialogPrefix + 169)
DECLARE_PMID(kWidgetIDSpace, kMaxFontSizeNudgeWidgetID, kPageSetupDialogPrefix + 170)
DECLARE_PMID(kWidgetIDSpace, kMinFontSizeNudgeWidgetID, kPageSetupDialogPrefix + 171)
DECLARE_PMID(kWidgetIDSpace, kAutoAdjustMarginWidgetID, kPageSetupDialogPrefix + 172)
DECLARE_PMID(kWidgetIDSpace, kMarginOrigWidgetGroupWidgetID, kPageSetupDialogPrefix + 173)
DECLARE_PMID(kWidgetIDSpace, kAdaptiveLayoutPropPanelWidgetID, kPageSetupDialogPrefix + 174)
DECLARE_PMID(kWidgetIDSpace, kAdaptiveInformationTextWidgetID, kPageSetupDialogPrefix + 175)
DECLARE_PMID(kWidgetIDSpace, kPSNumPagesIconWidgetId, kPageSetupDialogPrefix + 176)
DECLARE_PMID(kWidgetIDSpace, kPSWidthStaticTextWidgetId, kPageSetupDialogPrefix + 177)
DECLARE_PMID(kWidgetIDSpace, kPSHeightStaticTextWidgetId, kPageSetupDialogPrefix + 178)




// <Service ID>
// Service Provider IDs
DECLARE_PMID(kServiceIDSpace, kNewDocCreatedSignalResponderService, kPageSetupDialogPrefix + 1) 

// <Action ID>
// ActionIDs
DECLARE_PMID(kActionIDSpace, kPageSetupActionID, kPageSetupDialogPrefix + 1)
DECLARE_PMID(kActionIDSpace, kPageSetupSepActionID, kPageSetupDialogPrefix + 2)
DECLARE_PMID(kActionIDSpace, kDocStyleSepActionID, kPageSetupDialogPrefix + 3)
DECLARE_PMID(kActionIDSpace, kDocStyleEditActionID, kPageSetupDialogPrefix + 4)
DECLARE_PMID(kActionIDSpace, kDocStyleMenuDynamicActionID, kPageSetupDialogPrefix + 5)
DECLARE_PMID(kActionIDSpace, kFirstDocStyleActionID, (kPageSetupDialogPrefix + 6))
// ids between kFirstDocStyleActionID and kLastDocStyleActionID are reserved
DECLARE_PMID(kActionIDSpace, kLastDocStyleActionID, (kPageSetupDialogPrefix + 221))
//gap
DECLARE_PMID(kActionIDSpace, kDocStyleMenuDefaultActionID, (kPageSetupDialogPrefix + 222))
DECLARE_PMID(kActionIDSpace, kDocStyleMenuPreset1ActionID, (kPageSetupDialogPrefix + 223))
DECLARE_PMID(kActionIDSpace, kDocStyleMenuPreset2ActionID, (kPageSetupDialogPrefix + 224))
//gap
DECLARE_PMID(kActionIDSpace, kAdaptiveLayoutActionID, kPageSetupDialogPrefix + 250)
#endif // __PageSetupDialogID__

