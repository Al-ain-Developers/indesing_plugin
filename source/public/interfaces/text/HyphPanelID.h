//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/HyphPanelID.h $ 
//  
//  Owner: Bernd Paradies
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

#ifndef __HyphPanelID__
#define __HyphPanelID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

//----------------------------------------------------------------------------------------
// Resource IDs
//----------------------------------------------------------------------------------------

// Resource ID of Panel Windows
#define kHyphPanelRsrcID			1000
#define kHyphDialogRsrcID 		1100
#define kHyphCoreDialogRsrcID 	1200

#define kHyphDialogSelRsrcID 		1300
#define kHyphCoreDialogSelRsrcID 	1400
#define kHyphPanelStringsRsrcID 	1500
#define kHyphPanelStringsNoTransRsrcID 	1600

// Prefix
#define kHyphPanelPrefix	RezLong(0x3200) 	/* doublecheck with DeveloperPrefix.h */
// 0x3200 Hex == 12800 Dec

// PluginID
#define kHyphPanelPluginName	 			"Hyphenation Panel"
START_IDS()

DECLARE_PMID(kPlugInIDSpace, kHyphPanelPluginID, kHyphPanelPrefix + 1)

// <Start IDC>
// <Class ID>
//----------------------------------------------------------------------------------------
// Boss IDs
//----------------------------------------------------------------------------------------

// Panel: 0 to 9
// gap
DECLARE_PMID(kClassIDSpace, kHyphDialogBoss, kHyphPanelPrefix + 2)	// starts the dialog
DECLARE_PMID(kClassIDSpace, kHyphDialogHookBoss, kHyphPanelPrefix + 3)	// hooks the HyphStyleDialog into the HyphDialog and the StyleDialog
DECLARE_PMID(kClassIDSpace, kHyphTestMenuBoss, kHyphPanelPrefix + 4)
DECLARE_PMID(kClassIDSpace, kHyphDialogWidgetBoss, kHyphPanelPrefix + 5)
//gap

// Hyph Panel ObserverBoss, EditFields: 40 to 69
DECLARE_PMID(kClassIDSpace, kHYPBeforeObserverBoss, kHyphPanelPrefix + 40)
DECLARE_PMID(kClassIDSpace, kHYPAfterObserverBoss, kHyphPanelPrefix + 41)
DECLARE_PMID(kClassIDSpace, kHYPShortestObserverBoss, kHyphPanelPrefix + 42)
DECLARE_PMID(kClassIDSpace, kHYPConsecutiveObserverBoss, kHyphPanelPrefix + 43)
DECLARE_PMID(kClassIDSpace, kHYPZoneObserverBoss, kHyphPanelPrefix + 44)

// Hyph Panel ObserverBoss, checkbox: 70 to 99
DECLARE_PMID(kClassIDSpace, kHYPCapObserverBoss, kHyphPanelPrefix + 70)
DECLARE_PMID(kClassIDSpace, kHYPLastObserverBoss, kHyphPanelPrefix + 71)
DECLARE_PMID(kClassIDSpace, kCrossFrameHyphenObserverBoss, kHyphPanelPrefix + 72)

// Hyph Panel penalty slider boss: 100 to 110
DECLARE_PMID(kClassIDSpace, kHYPPenaltyObserverBoss, kHyphPanelPrefix + 100)
DECLARE_PMID(kClassIDSpace, kHYPPenaltySliderTrackerBoss, kHyphPanelPrefix + 101)
DECLARE_PMID(kClassIDSpace, kHYPPenaltySliderTrackerRegisterBoss, kHyphPanelPrefix + 102)
DECLARE_PMID(kClassIDSpace, kHYPProviderHyphStyleObserverBoss, kHyphPanelPrefix + 103)

// <Interface ID>
//----------------------------------------------------------------------------------------
// Interface IDs
//----------------------------------------------------------------------------------------
//DECLARE_PMID(kInterfaceIDSpace, IID_IPANELOBSERVERDATA, kHyphPanelPrefix + 0)
DECLARE_PMID(kInterfaceIDSpace, IID_IHYPLANGUAGEOBSERVER, kHyphPanelPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IHYPHPANELMSG, kHyphPanelPrefix + 2)

// <Implementation ID>
//----------------------------------------------------------------------------------------
// Implementation IDs
//----------------------------------------------------------------------------------------

// Hyph Panel Observer, EditFields: 40 to 69
DECLARE_PMID(kImplementationIDSpace, kHYPBeforeObserverImpl, kHyphPanelPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kHYPAfterObserverImpl, kHyphPanelPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kHYPShortestObserverImpl, kHyphPanelPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kHYPConsecutiveObserverImpl, kHyphPanelPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kHYPZoneObserverImpl, kHyphPanelPrefix + 44)


// Hyph Panel Observer, checkbox: 70 to 99
DECLARE_PMID(kImplementationIDSpace, kHYPCapObserverImpl, kHyphPanelPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kHYPLastObserverImpl, kHyphPanelPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kCrossFrameHyphenObserverImpl, kHyphPanelPrefix + 72)

// Hyph Panel penalty slider: 100 to 110
DECLARE_PMID(kImplementationIDSpace, kHYPPenaltyObserverImpl, kHyphPanelPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kHYPPenaltySliderViewImpl, kHyphPanelPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kHYPPenaltySliderTrackerImpl, kHyphPanelPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kHYPPenaltySliderTrackerRegisterImpl, kHyphPanelPrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kHYPPenaltySliderEHImpl, kHyphPanelPrefix + 104)

// Hpyh Panel Provider's Hyphenations Style Observer, Drop Down:
DECLARE_PMID(kImplementationIDSpace, kHYPProviderHyphStyleObserverImpl, kHyphPanelPrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kHyphDialogWidgetObserverImpl, kHyphPanelPrefix + 110)


// <Widget ID>
//----------------------------------------------------------------------------------------
// Widget IDs
//----------------------------------------------------------------------------------------
DECLARE_PMID(kWidgetIDSpace, kHyphPanelWidgetId, kHyphPanelPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kHyphGroupBoxWidgetId, kHyphPanelPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kHyphGroupTextWidgetId, kHyphPanelPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kHyphModeWidgetId, kHyphPanelPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kHyphWordLongerTextWidgetId, kHyphPanelPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kHyphShortestWidgetId, kHyphPanelPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kHyphLettersTextWidgetId, kHyphPanelPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kHyphAfterFirstTextWidgetId, kHyphPanelPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kHyphBeforeWidgetId, kHyphPanelPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kHyphLetters2WidgetId, kHyphPanelPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kHyphBeforeLastTextWidgetId, kHyphPanelPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kHyphAfterWidgetId, kHyphPanelPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kHyphLetters3WidgetId, kHyphPanelPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kHyphLadderLimitTextWidgetId, kHyphPanelPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kHyphConsecutiveWidgetId, kHyphPanelPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kHyphHyphensTextWidgetId, kHyphPanelPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kHyphHyphenZoneTextWidgetId, kHyphPanelPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kHyphHyphZoneWidgetId, kHyphPanelPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kHyphHyphCapWidgetId, kHyphPanelPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kHyphDialogWidgetId, kHyphPanelPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kHyphDialogHookWidgetId, kHyphPanelPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kHyphPanelGroupWidgetId, kHyphPanelPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kHyphModeGroupWidgetId, kHyphPanelPrefix + 23)

DECLARE_PMID(kWidgetIDSpace, kHyphPenaltyWidgetId, kHyphPanelPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kHyphPenaltyLowerTextWidgetId, kHyphPanelPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kHyphPenaltyHigherTextWidgetId, kHyphPanelPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kHyphHyphLastWidgetId, kHyphPanelPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kHyphHyphXFrameWidgetId, kHyphPanelPrefix + 28)

DECLARE_PMID(kWidgetIDSpace, kHyphShortestNudgeWidgetId, kHyphPanelPrefix + 29)
DECLARE_PMID(kWidgetIDSpace, kHyphAfterNudgeWidgetId, kHyphPanelPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kHyphBeforeNudgeWidgetId, kHyphPanelPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kHyphConsecutiveNudgeWidgetId, kHyphPanelPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kHyphHyphenZoneNudgeWidgetId, kHyphPanelPrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kDudenHyphenationStyleWidgetId, kHyphPanelPrefix + 34)
DECLARE_PMID(kWidgetIDSpace, kDudenHyphStylePanelGroupWidgetId, kHyphPanelPrefix + 35)
DECLARE_PMID(kWidgetIDSpace, kDudenHyphenationGroupWidgetId, kHyphPanelPrefix + 36)
DECLARE_PMID(kWidgetIDSpace, kStyleWidgetId, kHyphPanelPrefix + 37)
DECLARE_PMID(kWidgetIDSpace, kStyleDropDownWidgetId, kHyphPanelPrefix + 38)

// <Message ID>
//----------------------------------------------------------------------------------------
// Message IDs
//----------------------------------------------------------------------------------------

DECLARE_PMID(kMessageIDSpace, kHyphHyphenationEnabled, kHyphPanelPrefix + 100	)

END_IDS()

// <Ignore>
// Rest
#define kHyphDialogImpl						kHyphPanelPrefix + 131
#define kHyphDialogRsrcDataImpl				kHyphPanelPrefix + 132	// returns kHyphDialogRsrcID
#define kHyphCoreDialogRsrcDataImpl			kHyphPanelPrefix + 133	// returns kHyphCoreDialogRsrcID
#define kHyphTestMenuImpl					kHyphPanelPrefix + 134

#endif // __HyphPanelID__

