//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/InCopyPrintUIID.h $
//  
//  Owner: Michael Easter
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
//  Contains IDs used by the printing plug-in
//  
//========================================================================================

#ifndef __INCOPYPRINTUIID__
#define __INCOPYPRINTUIID__

// ----- Includes -----

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kInCopyPrintUIPrefix	 RezLong(0x18900)

//_______________________________________________________________________________________
// <Start IDC>
// PluginID
//_______________________________________________________________________________________
#define kInCopyPrintUIPluginName 					"InCopyPrintUI"
DECLARE_PMID(kPlugInIDSpace, kInCopyPrintUIPluginID, kInCopyPrintUIPrefix + 1)


//_______________________________________________________________________________________
// <Class ID>
// ClassIDs
//_______________________________________________________________________________________
// InCopy
DECLARE_PMID(kClassIDSpace, kInCopyPrintDialogBoss, kInCopyPrintUIPrefix + 1)
DECLARE_PMID(kClassIDSpace, kLayoutPrintPanelBoss, kInCopyPrintUIPrefix + 2)
DECLARE_PMID(kClassIDSpace, kGalleyPrintPanelBoss, kInCopyPrintUIPrefix + 3)
DECLARE_PMID(kClassIDSpace, kPrintPanelPickerWidgetBoss, kInCopyPrintUIPrefix + 4)
DECLARE_PMID(kClassIDSpace, kInCopyPrintDialogCmdBoss, kInCopyPrintUIPrefix + 5)
DECLARE_PMID(kClassIDSpace, kLineRangeEditBoxWidgetBoss, kInCopyPrintUIPrefix + 7)
DECLARE_PMID(kClassIDSpace, kInCopyTempPrintDataBoss, kInCopyPrintUIPrefix + 8)

//_______________________________________________________________________________________
// <Interface ID>
// IIDs
//_______________________________________________________________________________________
//galley
DECLARE_PMID(kInterfaceIDSpace, IID_IINCOPYPRINTDIALOGCMDDATA, kInCopyPrintUIPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IINCOPYPRINTDIALOGDATA, kInCopyPrintUIPrefix + 2)

//_______________________________________________________________________________________
// <Implementation ID>
// ImplementationIDs
//_______________________________________________________________________________________
//InCopy
DECLARE_PMID(kImplementationIDSpace, kPrintPanelPickerServiceImpl, kInCopyPrintUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kInCopyPrintDialogCmdDataImpl, kInCopyPrintUIPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kInCopyPrintDialogDataImpl, kInCopyPrintUIPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kInCopyPrintDialogControllerImpl, kInCopyPrintUIPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kInCopyPrintDialogCreatorImpl, kInCopyPrintUIPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kInCopyPrintDialogObserverImpl, kInCopyPrintUIPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kInCopyPrintDialogCmdImpl, kInCopyPrintUIPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kGalleyPrintPanelControllerImpl, kInCopyPrintUIPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kGalleyPrintPanelCreatorImpl, kInCopyPrintUIPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kGalleyPrintPanelObserverImpl, kInCopyPrintUIPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kLayoutPrintPanelControllerImpl, kInCopyPrintUIPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kLayoutPrintPanelCreatorImpl, kInCopyPrintUIPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kLayoutPrintPanelObserverImpl, kInCopyPrintUIPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kLineRangeTextValidationImpl, kInCopyPrintUIPrefix + 14)

//_______________________________________________________________________________________
// <Widget ID>
//	Widget IDs
//_______________________________________________________________________________________
//galley general panel
DECLARE_PMID(kWidgetIDSpace, kInCopyPrintDialogWidgetID,				kInCopyPrintUIPrefix + 0)

DECLARE_PMID(kWidgetIDSpace, kInCopyPrinterLabelWidgetID,				kInCopyPrintUIPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kPrintPanelPickerTitleGroupWidgetID,	kInCopyPrintUIPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kPrintPanelPickerPopupWidgetID,		kInCopyPrintUIPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kPrintPanelPickerWidgetID,				kInCopyPrintUIPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kSaveSettingButtonWidgetID,			kInCopyPrintUIPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kLayoutPrintPanelWidgetID,				kInCopyPrintUIPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kPageAllRadioButtonWidgetID,			kInCopyPrintUIPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kPageRangeRadioButtonWidgetID,			kInCopyPrintUIPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kGalleyPrintPanelWidgetID,				kInCopyPrintUIPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kFillCheckBoxWidgetID,					kInCopyPrintUIPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kCurrentSettingRadioButtonWidgetID,	kInCopyPrintUIPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kOverrideSettingRadioButtonWidgetID,	kInCopyPrintUIPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kParaStylesCheckBoxWidgetID,			kInCopyPrintUIPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kLineNumberCheckBoxWidgetID,			kInCopyPrintUIPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kALECheckBoxWidgetID,					kInCopyPrintUIPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kNotesCheckBoxWidgetID,				kInCopyPrintUIPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kTrackChangesCheckBoxWidgetID,			kInCopyPrintUIPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kLinesLabelWidgetID,					kInCopyPrintUIPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kLineClusterPanelWidgetID,				kInCopyPrintUIPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kLineAllRadioButtonWidgetID,			kInCopyPrintUIPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kLineRangeRadioButtonWidgetID,			kInCopyPrintUIPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kScopeLabelWidgetID,					kInCopyPrintUIPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kSettingClusterPanelWidgetID,			kInCopyPrintUIPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kTrackChangesTypePopupWidgetID,		kInCopyPrintUIPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kNotesTypePopupWidgetID,				kInCopyPrintUIPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kReverseCheckBoxWidgetID,				kInCopyPrintUIPrefix + 29)
DECLARE_PMID(kWidgetIDSpace, kStoryInfoCheckBoxWidgetID,			kInCopyPrintUIPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kNotesBackgroundCheckBoxWidgetID,		kInCopyPrintUIPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kContributorCheckBoxWidgetID,			kInCopyPrintUIPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kPagesInfoCheckBoxWidgetID,			kInCopyPrintUIPrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kColumnsLabelWidgetID,					kInCopyPrintUIPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kColumnsEditWidgetID,					kInCopyPrintUIPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kSettingGroupWidgetID,					kInCopyPrintUIPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kSettingOptionWidgetID,				kInCopyPrintUIPrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kFontLabelWidgetID,					kInCopyPrintUIPrefix + 38)
DECLARE_PMID(kWidgetIDSpace, kFontNameDropDownWidgetID,				kInCopyPrintUIPrefix + 41)
DECLARE_PMID(kWidgetIDSpace, kFontSizeDropDownWidgetID,				kInCopyPrintUIPrefix + 42)
DECLARE_PMID(kWidgetIDSpace, kFontSizeNudgeWidgetId,				kInCopyPrintUIPrefix + 43)

DECLARE_PMID(kWidgetIDSpace, kStoryInfoGroupWidgetID,				kInCopyPrintUIPrefix + 45)
DECLARE_PMID(kWidgetIDSpace, kStoryInfoOptionWidgetID,				kInCopyPrintUIPrefix + 46)
DECLARE_PMID(kWidgetIDSpace, kSetupButtonWidgetID,					kInCopyPrintUIPrefix + 47)
DECLARE_PMID(kWidgetIDSpace, kImageCheckBoxWidgetID,				kInCopyPrintUIPrefix + 48)
DECLARE_PMID(kWidgetIDSpace, kSpreadCheckBoxWidgetID,				kInCopyPrintUIPrefix + 49)
DECLARE_PMID(kWidgetIDSpace, kTrackChangesBackgroundCheckBoxWidgetID,			kInCopyPrintUIPrefix + 50)
DECLARE_PMID(kWidgetIDSpace, kScopePopupWidgetID,					kInCopyPrintUIPrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kFontStyleDropDownWidgetId,			kInCopyPrintUIPrefix + 53)
DECLARE_PMID(kWidgetIDSpace, kFontSizeDropDownWidgetId,				kInCopyPrintUIPrefix + 54)
DECLARE_PMID(kWidgetIDSpace, kFontLeadingDropDownWidgetId,			kInCopyPrintUIPrefix + 55)
DECLARE_PMID(kWidgetIDSpace, kGalleyPaperSizeLabelWidgetID,			kInCopyPrintUIPrefix + 56)
DECLARE_PMID(kWidgetIDSpace, kGalleyPaperSizePopupWidgetID,			kInCopyPrintUIPrefix + 57)
DECLARE_PMID(kWidgetIDSpace, kAllStoriesRadioButtonWidgetID,		kInCopyPrintUIPrefix + 58)
DECLARE_PMID(kWidgetIDSpace, kCurrentStoryRadioButtonWidgetID,		kInCopyPrintUIPrefix + 59)
DECLARE_PMID(kWidgetIDSpace, kPrintViewLabelWidgetID,				kInCopyPrintUIPrefix + 60)
DECLARE_PMID(kWidgetIDSpace, kColumnWidthTypePopupWidgetID,			kInCopyPrintUIPrefix + 61)
DECLARE_PMID(kWidgetIDSpace, kScopeClusterWidgetId,					kInCopyPrintUIPrefix + 62)
DECLARE_PMID(kWidgetIDSpace, kPageRangeEditWidgetID,				kInCopyPrintUIPrefix + 63)
DECLARE_PMID(kWidgetIDSpace, kExpandedStoryRadioButtonWidgetID,		kInCopyPrintUIPrefix + 64)
DECLARE_PMID(kWidgetIDSpace, kDisplayStoryCollapsedWarningID,		kInCopyPrintUIPrefix + 70)
DECLARE_PMID(kWidgetIDSpace, kDisplayContentsExceedWarningID,		kInCopyPrintUIPrefix + 71)
DECLARE_PMID(kWidgetIDSpace, kCustomUnitEditWidgetID,				kInCopyPrintUIPrefix + 72)
DECLARE_PMID(kWidgetIDSpace, kCustomUnitLabelWidgetID,				kInCopyPrintUIPrefix + 73)

//_______________________________________________________________________________________
// <Service ID>
//	Service IDs
//________________________________________________________________________________
//InCopy
DECLARE_PMID(kServiceIDSpace, kPrintPanelPickerService, kInCopyPrintUIPrefix + 10)
DECLARE_PMID(kServiceIDSpace, kInCopyPrintDialogService, kInCopyPrintUIPrefix + 11)


//_______________________________________________________________________________________
// <Error ID>
//	Error IDs
//_______________________________________________________________________________________


//_______________________________________________________________________________________
// <Action ID>
// ActionIDs
//_______________________________________________________________________________________

//_______________________________________________________________________________________
// <ViewPortAttr ID>
// ViewPortAttrIDs
//_______________________________________________________________________________________

//Script Element IDs
//

//Suites

//Properties

//Enums

// Miscellaneous defines

#endif // __PrintID__

// End, PrintID.h.
