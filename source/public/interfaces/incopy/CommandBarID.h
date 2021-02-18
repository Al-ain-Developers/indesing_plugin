//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/CommandBarID.h $
//  
//  Owner: Bruce Linker
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

#ifndef __CommandBarID__
#define __CommandBarID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kCommandBarPrefix	 RezLong(0xb500)	// reserved in AdobePrefix.h

//PlugInID
#define kCommandBarPlugInName				"CommandBar"
#define kCommandBarPlugInID				kCommandBarPrefix + 1

//========================================================================================
// ----- Class IDs -----
//========================================================================================
DECLARE_PMID(kClassIDSpace, kCommandBarRegisterBoss, kCommandBarPrefix + 1)
//gap
DECLARE_PMID(kClassIDSpace, kCommandBarBoss, kCommandBarPrefix + 3)
DECLARE_PMID(kClassIDSpace, kInCopyToolbarBoss_Reuse, kCommandBarPrefix + 4)
DECLARE_PMID(kClassIDSpace, kInCopyToolGroupBoss_Reuse, kCommandBarPrefix + 5)
DECLARE_PMID(kClassIDSpace, kInCopyToolSubGroupBoss_Reuse, kCommandBarPrefix + 6)
DECLARE_PMID(kClassIDSpace, kInCopyPopoutToolPanelBoss_Reuse, kCommandBarPrefix + 7)
DECLARE_PMID(kClassIDSpace, kInCopyToolActionBoss_Reuse, kCommandBarPrefix + 8)
DECLARE_PMID(kClassIDSpace, kInCopySubtoolActionBoss_Reuse, kCommandBarPrefix + 9)

DECLARE_PMID(kClassIDSpace, kNewButtonBoss, kCommandBarPrefix + 11)
DECLARE_PMID(kClassIDSpace, kOpenButtonBoss, kCommandBarPrefix + 12)
DECLARE_PMID(kClassIDSpace, kSaveButtonBoss, kCommandBarPrefix + 13)
DECLARE_PMID(kClassIDSpace, kPrintButtonBoss, kCommandBarPrefix + 14)
DECLARE_PMID(kClassIDSpace, kSpellingButtonBoss, kCommandBarPrefix + 15)
DECLARE_PMID(kClassIDSpace, kFindButtonBoss, kCommandBarPrefix + 16)
// available
// available
DECLARE_PMID(kClassIDSpace, kShowChangeButtonBoss_Reuse, kCommandBarPrefix + 19)
DECLARE_PMID(kClassIDSpace, kAcceptChangeButtonBoss_Reuse, kCommandBarPrefix + 20)
DECLARE_PMID(kClassIDSpace, kRejectChangeButtonBoss_Reuse, kCommandBarPrefix + 21)
DECLARE_PMID(kClassIDSpace, kPrevChangeButtonBoss_Reuse, kCommandBarPrefix + 22)
DECLARE_PMID(kClassIDSpace, kNextChangeButtonBoss_Reuse, kCommandBarPrefix + 23)
DECLARE_PMID(kClassIDSpace, kShowLineNumButtonBoss, kCommandBarPrefix + 28)
DECLARE_PMID(kClassIDSpace, kShowHiddenButtonBoss, kCommandBarPrefix + 29)
DECLARE_PMID(kClassIDSpace, kFontNameComboBoss_Reuse, kCommandBarPrefix + 30)
DECLARE_PMID(kClassIDSpace, kFontStyleComboBoss_Reuse, kCommandBarPrefix + 31)
DECLARE_PMID(kClassIDSpace, kFontSizeComboBoss_Reuse, kCommandBarPrefix + 32)
DECLARE_PMID(kClassIDSpace, kCommandBarMenuBoss_Reuse, kCommandBarPrefix + 33)

DECLARE_PMID(kClassIDSpace, kShowNoteAnchorObserverBoss_Reuse, kCommandBarPrefix + 34)
DECLARE_PMID(kClassIDSpace, kShowNoteWindowObserverBoss_Reuse, kCommandBarPrefix + 35)
DECLARE_PMID(kClassIDSpace, kNextNoteButtonObserverBoss_Reuse, kCommandBarPrefix + 36)
DECLARE_PMID(kClassIDSpace, kPrevNoteButtonObserverBoss_Reuse, kCommandBarPrefix + 37)

DECLARE_PMID(kClassIDSpace, kCopyButtonBoss, kCommandBarPrefix + 38)
DECLARE_PMID(kClassIDSpace, kCutButtonBoss, kCommandBarPrefix + 39)
DECLARE_PMID(kClassIDSpace, kPasteButtonBoss, kCommandBarPrefix + 40)
DECLARE_PMID(kClassIDSpace, kUndoButtonBoss, kCommandBarPrefix + 41)
DECLARE_PMID(kClassIDSpace, kRedoButtonBoss, kCommandBarPrefix + 42)

DECLARE_PMID(kClassIDSpace, kCommandBarServiceProviderBoss, kCommandBarPrefix + 60)
DECLARE_PMID(kClassIDSpace, kCommandBarMenuRegisterBoss_Reuse, kCommandBarPrefix + 61)
DECLARE_PMID(kClassIDSpace, kCommandBarActionRegisterBoss_Reuse, kCommandBarPrefix + 62)
//gap
DECLARE_PMID(kClassIDSpace, kCBBridgeChangeResponderBoss, kCommandBarPrefix + 70)

//========================================================================================
// ----- Interface IDs -----
//========================================================================================
DECLARE_PMID(kInterfaceIDSpace, IID_ICBDBOBSERVER, kCommandBarPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IUPDATESAVEBUTTON, kCommandBarPrefix + 2)

//========================================================================================
// ----- Implementation IDs -----
//========================================================================================
DECLARE_PMID(kImplementationIDSpace, kCommandBarRegisterImpl_Reuse, kCommandBarPrefix + 1)
//gap
DECLARE_PMID(kImplementationIDSpace, kInCopyPopoutPanelEHImpl_Reuse, kCommandBarPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kInCopyToolbarObserverImpl_Reuse, kCommandBarPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kInCopyToolbarSetupImpl_Reuse, kCommandBarPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kInCopyToolbarEHImpl_Reuse, kCommandBarPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kInCopyToolTipImpl_Reuse, kCommandBarPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kInCopyToolActionComponentImpl_Reuse, kCommandBarPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kInCopySubtoolActionComponentImpl_Reuse, kCommandBarPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kNewCBButtonObserverImpl, kCommandBarPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kOpenButtonObserverImpl, kCommandBarPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kSaveButtonObserverImpl, kCommandBarPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kPrintButtonObserverImpl, kCommandBarPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kSpellingButtonObserverImpl, kCommandBarPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kCBFindButtonObserverImpl, kCommandBarPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kGalleyButtonObserverImpl, kCommandBarPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kLayoutButtonObserverImpl, kCommandBarPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kShowChangeButtonObserverImpl_Reuse, kCommandBarPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kAcceptChangeButtonObserverImpl_Reuse, kCommandBarPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kRejectChangeButtonObserverImpl_Reuse, kCommandBarPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kPrevChangeButtonObserverImpl_Reuse, kCommandBarPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kNextChangeButtonObserverImpl_Reuse, kCommandBarPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kShowLineNumButtonObserverImpl, kCommandBarPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kShowHiddenButtonObserverImpl, kCommandBarPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kInCopyCmdBarViewImpl_Reuse, kCommandBarPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kCommandBarMenuImpl_Reuse, kCommandBarPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kCommandBarTipImpl, kCommandBarPrefix + 31)
// gap
DECLARE_PMID(kImplementationIDSpace, kShowNoteAnchorObserverImpl_Reuse, kCommandBarPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kShowNoteWindowObserverImpl_Reuse, kCommandBarPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kNextNoteButtonObserverImpl_Reuse, kCommandBarPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kPrevNoteButtonObserverImpl_Reuse, kCommandBarPrefix + 36)

DECLARE_PMID(kImplementationIDSpace, kCopyButtonObserverImpl, kCommandBarPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kCutButtonObserverImpl, kCommandBarPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kPasteButtonObserverImpl, kCommandBarPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kUndoButtonObserverImpl, kCommandBarPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kRedoButtonObserverImpl, kCommandBarPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kShowHiddenButtonTipImpl, kCommandBarPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kCommandBarDBObserverImpl, kCommandBarPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kCBBridgeChangeResponderImpl, kCommandBarPrefix + 44)


//========================================================================================
// ----- Action IDs -----
//========================================================================================

DECLARE_PMID(kActionIDSpace, kShowHideWidgetBarsSeparatorID_Reuse, kCommandBarPrefix + 1)
DECLARE_PMID(kActionIDSpace, kShowHideToolbarActionID_Reuse, kCommandBarPrefix + 2)
DECLARE_PMID(kActionIDSpace, kShowHideCommandbarActionID_Reuse, kCommandBarPrefix + 3)
DECLARE_PMID(kActionIDSpace, kCommandBarPanelActionID, kCommandBarPrefix + 4)

//========================================================================================
// ----- Widget IDs -----
//========================================================================================

DECLARE_PMID(kWidgetIDSpace, kCommandBarPanelWidgetID, kCommandBarPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kInCopyToolbarPanelWidgetID_Reuse, kCommandBarPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kInCopyToolbarGroupWidgetId_Reuse, kCommandBarPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kInCopyToolbarPopoutWidgetId_Reuse, kCommandBarPrefix + 4)

DECLARE_PMID(kWidgetIDSpace, kNewCBButtonWidgetID, kCommandBarPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kOpenCBButtonWidgetID, kCommandBarPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kSaveCBButtonWidgetID, kCommandBarPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kPrintButtonWidgetID, kCommandBarPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kSpellingButtonWidgetID, kCommandBarPrefix + 9)
DECLARE_PMID(kWidgetIDSpace, kCBFindButtonWidgetID, kCommandBarPrefix + 10)
DECLARE_PMID(kWidgetIDSpace, kGalleyButtonWidgetID, kCommandBarPrefix + 11)
DECLARE_PMID(kWidgetIDSpace, kLayoutButtonWidgetID, kCommandBarPrefix + 12)
DECLARE_PMID(kWidgetIDSpace, kShowChangeButtonWidgetID_Reuse, kCommandBarPrefix + 13)
DECLARE_PMID(kWidgetIDSpace, kAcceptChangeButtonWidgetID_Reuse, kCommandBarPrefix + 14)
DECLARE_PMID(kWidgetIDSpace, kRejectChangeButtonWidgetID_Reuse, kCommandBarPrefix + 15)
DECLARE_PMID(kWidgetIDSpace, kPrevChangeButtonWidgetID_Reuse, kCommandBarPrefix + 16)
DECLARE_PMID(kWidgetIDSpace, kNextChangeButtonWidgetID_Reuse, kCommandBarPrefix + 17)
DECLARE_PMID(kWidgetIDSpace, kNotesButtonWidgetID_Reuse, kCommandBarPrefix + 18)
DECLARE_PMID(kWidgetIDSpace, kCloseNotesButtonWidgetID_Reuse, kCommandBarPrefix + 19)
DECLARE_PMID(kWidgetIDSpace, kPrevNoteButtonWidgetID_Reuse, kCommandBarPrefix + 20)
DECLARE_PMID(kWidgetIDSpace, kNextNoteButtonWidgetID_Reuse, kCommandBarPrefix + 21)
DECLARE_PMID(kWidgetIDSpace, kShowLineNumButtonWidgetID, kCommandBarPrefix + 22)
DECLARE_PMID(kWidgetIDSpace, kShowHiddenButtonWidgetID, kCommandBarPrefix + 23)
DECLARE_PMID(kWidgetIDSpace, kFontNameComboWidgetID_Reuse, kCommandBarPrefix + 24)
DECLARE_PMID(kWidgetIDSpace, kFontStyleComboWidgetID_Reuse, kCommandBarPrefix + 25)
DECLARE_PMID(kWidgetIDSpace, kFontSizeComboWidgetID_Reuse, kCommandBarPrefix + 26)
DECLARE_PMID(kWidgetIDSpace, kFontSizeNudgeWidgetID_Reuse, kCommandBarPrefix + 27)
DECLARE_PMID(kWidgetIDSpace, kInCopyButtonGroupWidgetID_Reuse, kCommandBarPrefix + 28)
DECLARE_PMID(kWidgetIDSpace, kViewClusterWidgetId, kCommandBarPrefix + 29)
DECLARE_PMID(kWidgetIDSpace, kCBCopyButtonWidgetID, kCommandBarPrefix + 30)
DECLARE_PMID(kWidgetIDSpace, kCBCutButtonWidgetID, kCommandBarPrefix + 31)
DECLARE_PMID(kWidgetIDSpace, kCBPasteButtonWidgetID, kCommandBarPrefix + 32)
DECLARE_PMID(kWidgetIDSpace, kCBUndoButtonWidgetID, kCommandBarPrefix + 33)
DECLARE_PMID(kWidgetIDSpace, kCBRedoButtonWidgetID, kCommandBarPrefix + 34)

DECLARE_PMID(kWidgetIDSpace, kFileControlSetWidgetID, kCommandBarPrefix + 50)
DECLARE_PMID(kWidgetIDSpace, kPrintControlSetWidgetID, kCommandBarPrefix + 51)
DECLARE_PMID(kWidgetIDSpace, kTypeControlSetWidgetID, kCommandBarPrefix + 52)
DECLARE_PMID(kWidgetIDSpace, kProofControlSetWidgetID, kCommandBarPrefix + 53)
DECLARE_PMID(kWidgetIDSpace, kScrapControlSetWidgetID, kCommandBarPrefix + 54)
DECLARE_PMID(kWidgetIDSpace, kUndoRedoControlSetWidgetID, kCommandBarPrefix + 55)
DECLARE_PMID(kWidgetIDSpace, kViewControlSetWidgetID, kCommandBarPrefix + 56)

DECLARE_PMID(kWidgetIDSpace, kCommandBarHBarViewWidgetID, kCommandBarPrefix + 70)
DECLARE_PMID(kWidgetIDSpace, kCommandBarTablessViewWidgetID, kCommandBarPrefix + 71)
DECLARE_PMID(kWidgetIDSpace, kCommandBarVBarViewWidgetID, kCommandBarPrefix + 72)

#endif

