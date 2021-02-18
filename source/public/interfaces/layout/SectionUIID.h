//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/SectionUIID.h $
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
//  Contains IDs used by the Section UI plug-in
//  
//========================================================================================

#ifndef __SectionUIID__
#define __SectionUIID__
#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kSectionUIPrefix	RezLong(0x5d00) 

// <Start IDC>
// PluginID
#define kSectionUIPluginName 			"Sections UI"
DECLARE_PMID(kPlugInIDSpace, kSectionUIPluginID, kSectionUIPrefix + 1)

// Resource ID for section ui dialog
#define kSectionUIDialogRsrcID		1000

// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kSectionDialogBoss, kSectionUIPrefix + 1)
DECLARE_PMID(kClassIDSpace, kSectionUIMenuActionBoss, kSectionUIPrefix + 2)
DECLARE_PMID(kClassIDSpace, kSectionLayoutActionBoss, kSectionUIPrefix + 3)
//gap
DECLARE_PMID(kClassIDSpace, kBNChapterNumStyleWidgetBoss,	kSectionUIPrefix + 5)

// <Interface ID>
// Interface IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTSECTIONLISTOBSERVER, kSectionUIPrefix + 1)

// <Implementation ID>
// Implementation IIDs
DECLARE_PMID(kImplementationIDSpace, kSectionDialogObserverImpl, kSectionUIPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kSectionUIMenuActionImpl, kSectionUIPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kSectionDialogControllerImpl, kSectionUIPrefix + 12)
//DECLARE_PMID(kImplementationIDSpace, kPageNumberMenuActionImpl, kSectionUIPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kLayoutSectionListObserverImpl, kSectionUIPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kSectionLayoutActionImpl, kSectionUIPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kBNChapterNumStyleObserverImpl, kSectionUIPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kChapterNumStyleClassIDDataImpl, kSectionUIPrefix + 16)

// MessageIDs
DECLARE_PMID(kMessageIDSpace, kCNResetFormatMessage, kSectionUIPrefix + 1)

// <Widget ID>
// Widget IDs for Section Info
DECLARE_PMID(kWidgetIDSpace, kSectionDialogWidgetID, kSectionUIPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kSectionRenumberCheckBoxWidgetID, kSectionUIPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kSectionEditNameWidgetID, kSectionUIPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kSectionStylePopupWidgetID, kSectionUIPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kSectionEditMarkerWidgetID, kSectionUIPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kSectionEditFirstPageWidgetID, kSectionUIPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kSectionInfoGroupWidgetID, kSectionUIPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kSectionContinueNumberingRadioWidgetID, kSectionUIPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kSectionStartNumberingAtRadioWidgetID, kSectionUIPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kSectionNameLabelWidgetId, kSectionUIPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kAutoPageNumLabelWidgetId, kSectionUIPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kStyleLabelWidgetId, kSectionUIPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kSectionUIGroupWidgetId, kSectionUIPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kPageNumberingLabelWidgetId, kSectionUIPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kSectionNumberLabelWidgetId, kSectionUIPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kSectionIncludePrefixCheckBoxWidgetID, kSectionUIPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kStartPageNumLabelWidgetId, kSectionUIPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kChapterNumCheckBoxWidgetID, kSectionUIPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kContChapNumLabelWidgetId, kSectionUIPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kCNNeedUpdationThroughBookPanelWidgetID, kSectionUIPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kBNChapterNumDialogWidgetId, kSectionUIPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kChapterNumberStyleLabelWidgetId, kSectionUIPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kBNChapterNumStyleDDWidgetId, kSectionUIPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kBNUserDefinedChapterNumWidgetID, kSectionUIPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kBNContinueChapterNumFromPrevDocWidgetID, kSectionUIPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kBNSameChapterNumAsPrevDocWidgetID, kSectionUIPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kChapterNumValueWidgetID, kSectionUIPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kCNBookNameLabelWidgetId, kSectionUIPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kCNRadioClusterWidgetID, kSectionUIPrefix + 29)
DECLARE_PMID(kWidgetIDSpace, kStartChapNumLabelWidgetId, kSectionUIPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kSameAsPrevDocChapNumLabelWidgetId, kSectionUIPrefix + 31)
//gap
DECLARE_PMID(kWidgetIDSpace, kOverlappingPagesAlertWidgetID, kSectionUIPrefix + 100)

// <Action ID>
// Action IDs for Section Info
DECLARE_PMID(kActionIDSpace, kSectionOptionsActionID, kSectionUIPrefix + 1)
DECLARE_PMID(kActionIDSpace, kDeleteSectionActionID, kSectionUIPrefix + 2)
//gap
DECLARE_PMID(kActionIDSpace, kInsertPageNumberActionID, kSectionUIPrefix + 4)
//gap
DECLARE_PMID(kActionIDSpace, kSectionNameActionID, kSectionUIPrefix + 6)
DECLARE_PMID(kActionIDSpace, kNextPageNumberActionID, kSectionUIPrefix + 7)
DECLARE_PMID(kActionIDSpace, kPrevPageNumberActionID, kSectionUIPrefix + 8)

DECLARE_PMID(kActionIDSpace, kNumAndSectionSepActionID, kSectionUIPrefix + 9)
DECLARE_PMID(kActionIDSpace, kNumAndSectionActionID, kSectionUIPrefix + 10)

/*
DECLARE_PMID(kActionIDSpace, kTextSpecialCharSep1ActionID, kSectionUIPrefix + 9)
DECLARE_PMID(kActionIDSpace, kBulletActionID, kSectionUIPrefix + 10)
DECLARE_PMID(kActionIDSpace, kCopyRightActionID, kSectionUIPrefix + 11)
DECLARE_PMID(kActionIDSpace, kDegreeSignActionID, kSectionUIPrefix + 12)
DECLARE_PMID(kActionIDSpace, kEllipseActionID, kSectionUIPrefix + 13)
DECLARE_PMID(kActionIDSpace, kNewLineActionID, kSectionUIPrefix + 14)
DECLARE_PMID(kActionIDSpace, kParaActionID, kSectionUIPrefix + 15)
DECLARE_PMID(kActionIDSpace, kRegisterActionID, kSectionUIPrefix + 16)
DECLARE_PMID(kActionIDSpace, kSectionActionID, kSectionUIPrefix + 17)
DECLARE_PMID(kActionIDSpace, kTrademarkActionID, kSectionUIPrefix + 18)
DECLARE_PMID(kActionIDSpace, kTextSpecialCharSep2ActionID, kSectionUIPrefix + 19)
DECLARE_PMID(kActionIDSpace, kRightEdgeTabActionID, kSectionUIPrefix + 20)
DECLARE_PMID(kActionIDSpace, kIndentToHereActionID, kSectionUIPrefix + 21)
//gap
DECLARE_PMID(kActionIDSpace, kMSpaceActionID, kSectionUIPrefix + 23)
DECLARE_PMID(kActionIDSpace, kNSpaceActionID, kSectionUIPrefix + 24)
DECLARE_PMID(kActionIDSpace, kFlushSpaceActionID, kSectionUIPrefix + 25)
DECLARE_PMID(kActionIDSpace, kHairSpaceActionID, kSectionUIPrefix + 26)
DECLARE_PMID(kActionIDSpace, kNonBreakSpaceActionID, kSectionUIPrefix + 27)
DECLARE_PMID(kActionIDSpace, kThinSpaceActionID, kSectionUIPrefix + 28)
DECLARE_PMID(kActionIDSpace, kFigureSpaceActionID, kSectionUIPrefix + 29)
DECLARE_PMID(kActionIDSpace, kPunctuationSpaceActionID, kSectionUIPrefix + 30)
DECLARE_PMID(kActionIDSpace, kTextSpecialCharSep3ActionID, kSectionUIPrefix + 31)
DECLARE_PMID(kActionIDSpace, kEmDashActionID, kSectionUIPrefix + 32)
DECLARE_PMID(kActionIDSpace, kEnDashActionID, kSectionUIPrefix + 33)
DECLARE_PMID(kActionIDSpace, kDiscretHyphenActionID, kSectionUIPrefix + 34)
DECLARE_PMID(kActionIDSpace, kNonBreakHyphenActionID, kSectionUIPrefix + 35)
DECLARE_PMID(kActionIDSpace, kTextSpecialCharSep4ActionID, kSectionUIPrefix + 36)
DECLARE_PMID(kActionIDSpace, kDoubleLeftQuoteActionID, kSectionUIPrefix + 37)
DECLARE_PMID(kActionIDSpace, kDoubleRightQuoteActionID, kSectionUIPrefix + 38)
DECLARE_PMID(kActionIDSpace, kSingleLeftQuoteActionID, kSectionUIPrefix + 39)
DECLARE_PMID(kActionIDSpace, kSingleRightQuoteActionID, kSectionUIPrefix + 40)
*/

#endif // __SectionUIID__

