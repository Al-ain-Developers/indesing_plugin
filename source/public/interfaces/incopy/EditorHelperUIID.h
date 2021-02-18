//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/EditorHelperUIID.h $
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
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#ifndef __EditorHelperUIID__
#define __EditorHelperUIID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"
//#include "FormatNumber.h"

#define kEditorHelperUIPrefix	 RezLong(0x21100)

//----------------------------------------------------------------------------------------
// Plug-in identifier
//----------------------------------------------------------------------------------------

//PlugInID
#define kEditorHelperUIPlugInName				"EditorHelperUI"
DECLARE_PMID(kPlugInIDSpace, kEditorHelperUIPlugInID, kEditorHelperUIPrefix + 1)

//----------------------------------------------------------------------------------------
// Class identifiers
//----------------------------------------------------------------------------------------

DECLARE_PMID(kClassIDSpace,		kTextMacroPanelWidgetBoss, 				kEditorHelperUIPrefix + 2)
DECLARE_PMID(kClassIDSpace,		kPositionMarkerMenuActionBoss,			kEditorHelperUIPrefix + 3)
DECLARE_PMID(kClassIDSpace,		kPositionMarkerLayoutActionBoss, 		kEditorHelperUIPrefix + 4)
DECLARE_PMID(kClassIDSpace,		kTextMacroMenuComponentBoss, 			kEditorHelperUIPrefix + 5)
DECLARE_PMID(kClassIDSpace,		kMacroListWidgetBoss, 					kEditorHelperUIPrefix + 6)
DECLARE_PMID(kClassIDSpace,		kNewMacroButtonBoss, 					kEditorHelperUIPrefix + 7)
DECLARE_PMID(kClassIDSpace,		kDeleteMacroButtonBoss, 				kEditorHelperUIPrefix + 8)
DECLARE_PMID(kClassIDSpace,		kMacroNameTreeNodeWidgetBoss, 			kEditorHelperUIPrefix + 9)
DECLARE_PMID(kClassIDSpace,		kEditableMacroNameWidgetBoss, 			kEditorHelperUIPrefix + 10)
DECLARE_PMID(kClassIDSpace,		kUnassignSCButtonBoss, 					kEditorHelperUIPrefix + 11)
DECLARE_PMID(kClassIDSpace,		kMacroActionWidgetBoss, 				kEditorHelperUIPrefix + 12)
DECLARE_PMID(kClassIDSpace,		kEditMacroDialogBoss, 					kEditorHelperUIPrefix + 13)
DECLARE_PMID(kClassIDSpace,		kEditMacroButtonBoss, 					kEditorHelperUIPrefix + 14)
DECLARE_PMID(kClassIDSpace,		kRunMacroButtonBoss, 					kEditorHelperUIPrefix + 15)
DECLARE_PMID(kClassIDSpace,		kMacroSCCurrentActionLabelWidgetBoss,	kEditorHelperUIPrefix + 16)
DECLARE_PMID(kClassIDSpace,		kMacroSCCurrentActionTextWidgetBoss, 	kEditorHelperUIPrefix + 17)
DECLARE_PMID(kClassIDSpace,		kMacroWritingWidgetBoss, 				kEditorHelperUIPrefix + 18)
DECLARE_PMID(kClassIDSpace,		kMacroTextTrackerRegisterBoss, 			kEditorHelperUIPrefix + 19)
DECLARE_PMID(kClassIDSpace,		kMacroEditingBorderWidgetBoss, 			kEditorHelperUIPrefix + 20)
DECLARE_PMID(kClassIDSpace,		kMacroWritingScrollSyncBoss, 			kEditorHelperUIPrefix + 21)
DECLARE_PMID(kClassIDSpace,		kMacroSCEditBoxWidgetBoss, 				kEditorHelperUIPrefix + 22)
DECLARE_PMID(kClassIDSpace,		kMacroStyledWidgetBoss,					kEditorHelperUIPrefix + 23)
DECLARE_PMID(kClassIDSpace,		kMacroTopLevelEventBoss,				kEditorHelperUIPrefix + 24)


//----------------------------------------------------------------------------------------
// Interface identifiers
//----------------------------------------------------------------------------------------


DECLARE_PMID(kInterfaceIDSpace,		IID_IPOSITIONMARKERLAYOUTOBSERVER, 	kEditorHelperUIPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace,		IID_IPOSITIONMARKERSUITE, 			kEditorHelperUIPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace,		IID_ITEXTMACROUIUTILS, 				kEditorHelperUIPrefix + 4)



//----------------------------------------------------------------------------------------
// Implementation identifiers
//----------------------------------------------------------------------------------------

//gap
DECLARE_PMID(kImplementationIDSpace,		kTextMacroPanelWidgetImpl, 			kEditorHelperUIPrefix + 2)
DECLARE_PMID(kImplementationIDSpace,		kPositionMarkerMenuActionImpl,	 	kEditorHelperUIPrefix + 3)
DECLARE_PMID(kImplementationIDSpace,		kTextMacroMenuComponentImpl, 		kEditorHelperUIPrefix + 4)
DECLARE_PMID(kImplementationIDSpace,		kPositionMarkerLayoutActionImpl,	kEditorHelperUIPrefix + 5)
DECLARE_PMID(kImplementationIDSpace,		kTextMacroPanelTreeViewAdapterImpl, kEditorHelperUIPrefix + 6)
DECLARE_PMID(kImplementationIDSpace,		kPositionMarkerLayoutObserverImpl, 	kEditorHelperUIPrefix + 7)
DECLARE_PMID(kImplementationIDSpace,		kTextMacroTreeViewWidgetMgrImpl, 	kEditorHelperUIPrefix + 8)
DECLARE_PMID(kImplementationIDSpace,		kMacroSelectionObserverImpl,		kEditorHelperUIPrefix + 9)
DECLARE_PMID(kImplementationIDSpace,		kPositionMarkerSuiteASBImpl,		kEditorHelperUIPrefix + 10)
DECLARE_PMID(kImplementationIDSpace,		kPositionMarkerSuiteTextCSBImpl,	kEditorHelperUIPrefix + 11)
DECLARE_PMID(kImplementationIDSpace,		kMacroListObserverImpl,				kEditorHelperUIPrefix + 12)
DECLARE_PMID(kImplementationIDSpace,		kMacroNameTipImpl,					kEditorHelperUIPrefix + 13)
DECLARE_PMID(kImplementationIDSpace,		kNewMacroButtonObserverImpl,		kEditorHelperUIPrefix + 14)
DECLARE_PMID(kImplementationIDSpace,		kDeleteMacroButtonObserverImpl,		kEditorHelperUIPrefix + 15)
DECLARE_PMID(kImplementationIDSpace,		kEditMacroButtonObserverImpl,		kEditorHelperUIPrefix + 16)
DECLARE_PMID(kImplementationIDSpace,		kEditMacroDialogPanelImpl,			kEditorHelperUIPrefix + 17)
DECLARE_PMID(kImplementationIDSpace,		kEditMacroDlgControllerImpl, 		kEditorHelperUIPrefix + 18)
DECLARE_PMID(kImplementationIDSpace,		kMacroActionContextCheckerImpl,		kEditorHelperUIPrefix + 19)
DECLARE_PMID(kImplementationIDSpace,		kUnassignSCButtonObserverImpl, 		kEditorHelperUIPrefix + 20)
DECLARE_PMID(kImplementationIDSpace,		kTextMacroUIUtilsImpl, 				kEditorHelperUIPrefix + 21)
DECLARE_PMID(kImplementationIDSpace,		kTextMacroPanelViewImpl, 			kEditorHelperUIPrefix + 22)
DECLARE_PMID(kImplementationIDSpace,		kRunMacroButtonObserverImpl,		kEditorHelperUIPrefix + 23)
DECLARE_PMID(kImplementationIDSpace,		kMacroSCActionTextObserverImpl,		kEditorHelperUIPrefix + 24)
DECLARE_PMID(kImplementationIDSpace,		kMacroEditingControlViewImpl,		kEditorHelperUIPrefix + 25)
DECLARE_PMID(kImplementationIDSpace,		kMacroEditingEventHandlerImpl,		kEditorHelperUIPrefix + 26)
DECLARE_PMID(kImplementationIDSpace,		kMacroStoryRefDataImpl,				kEditorHelperUIPrefix + 27)
DECLARE_PMID(kImplementationIDSpace,		kMacroStoryThreadDataImpl,			kEditorHelperUIPrefix + 28)
DECLARE_PMID(kImplementationIDSpace,		kMacroTextCaretImpl,				kEditorHelperUIPrefix + 29)
DECLARE_PMID(kImplementationIDSpace,		kMacroEditingDisplayDataImpl,		kEditorHelperUIPrefix + 30)
DECLARE_PMID(kImplementationIDSpace,		kMacroEditingScrollDataImpl,		kEditorHelperUIPrefix + 31)
DECLARE_PMID(kImplementationIDSpace,		kMacroEditingObserverImpl,			kEditorHelperUIPrefix + 32)
DECLARE_PMID(kImplementationIDSpace,		kMacroEditingPanoramaImpl,			kEditorHelperUIPrefix + 33)
DECLARE_PMID(kImplementationIDSpace,		kMacroViewSelectionImpl,			kEditorHelperUIPrefix + 34)
DECLARE_PMID(kImplementationIDSpace,		kMacroTextTrackerRegisterImpl,		kEditorHelperUIPrefix + 35)
DECLARE_PMID(kImplementationIDSpace,		kMacroTextCaretThreadImpl,			kEditorHelperUIPrefix + 36)
DECLARE_PMID(kImplementationIDSpace,		kMacroEditingBorderWidgetImpl,		kEditorHelperUIPrefix + 37)
DECLARE_PMID(kImplementationIDSpace,		kMacroSCEditBoxEHImpl,				kEditorHelperUIPrefix + 38)
DECLARE_PMID(kImplementationIDSpace,		kMacroNameTreeNodeEHImpl,			kEditorHelperUIPrefix + 39)
DECLARE_PMID(kImplementationIDSpace,		kTMDialogShortcutContextImpl,		kEditorHelperUIPrefix + 40)
DECLARE_PMID(kImplementationIDSpace,		kFakeyMacroEditBoxAttributesImpl,	kEditorHelperUIPrefix + 41)
DECLARE_PMID(kImplementationIDSpace,		kMacroStyledTipImpl,				kEditorHelperUIPrefix + 42)
DECLARE_PMID(kImplementationIDSpace,		kMacroTopLevelEventHandlerImpl,		kEditorHelperUIPrefix + 43)


// <Ignore>
//========================================================================================
// ----- Tree Node ID types -----
//========================================================================================
#define kMacroNodeID					kEditorHelperUIPrefix + 1



//----------------------------------------------------------------------------------------
// Action identifiers
//----------------------------------------------------------------------------------------
DECLARE_PMID(kActionIDSpace,		kEditorHelperUIActionID, 	kEditorHelperUIPrefix + 1)
DECLARE_PMID(kActionIDSpace,		kAddMacroActionID, 			kEditorHelperUIPrefix + 2)
DECLARE_PMID(kActionIDSpace,		kSwapMacroActionID, 		kEditorHelperUIPrefix + 3)
DECLARE_PMID(kActionIDSpace,		kEditMacroActionID, 		kEditorHelperUIPrefix + 4)
DECLARE_PMID(kActionIDSpace,		kDuplicateMacroActionID, 	kEditorHelperUIPrefix + 5)
DECLARE_PMID(kActionIDSpace,		kDeleteMacroActionID, 		kEditorHelperUIPrefix + 6)
DECLARE_PMID(kActionIDSpace,		kRunMacroActionID, 			kEditorHelperUIPrefix + 7)
DECLARE_PMID(kActionIDSpace,		kMacroPopupSep1ActionID, 	kEditorHelperUIPrefix + 8)
DECLARE_PMID(kActionIDSpace,		kMacroPopupSep2ActionID, 	kEditorHelperUIPrefix + 9)
DECLARE_PMID(kActionIDSpace,		kExecuteMacroActionID, 		kEditorHelperUIPrefix + 10)
DECLARE_PMID(kActionIDSpace,		kSetPositionMarkerActionID,	kEditorHelperUIPrefix + 11)
DECLARE_PMID(kActionIDSpace,		kClearPositionMarkerActionID,	kEditorHelperUIPrefix + 12)
DECLARE_PMID(kActionIDSpace,		kGotoPositionMarkerActionID,	kEditorHelperUIPrefix + 13)
DECLARE_PMID(kActionIDSpace,		kPositionMarkerSep1ActionID,	kEditorHelperUIPrefix + 14)
DECLARE_PMID(kActionIDSpace,		kPositionMarkerSep2ActionID,	kEditorHelperUIPrefix + 15)
DECLARE_PMID(kActionIDSpace,		kAutoTextMacroActionID,		kEditorHelperUIPrefix + 16)
DECLARE_PMID(kActionIDSpace,		kMacroPopupSep3ActionID, 	kEditorHelperUIPrefix + 17)

DECLARE_PMID(kActionIDSpace,		kRunMacroBaseActionID, 		kEditorHelperUIPrefix + 100)




//----------------------------------------------------------------------------------------
// Widget identifiers
//----------------------------------------------------------------------------------------
DECLARE_PMID(kWidgetIDSpace,		kTextMacroPanelWidgetId, 			kEditorHelperUIPrefix + 1)
// gap
DECLARE_PMID(kWidgetIDSpace,		kMacroNameStaticWidgetID, 			kEditorHelperUIPrefix + 3)
DECLARE_PMID(kWidgetIDSpace,		kMacroTextStaticWidgetID, 			kEditorHelperUIPrefix + 4)
DECLARE_PMID(kWidgetIDSpace,		kAddMacroNameWidgetID, 				kEditorHelperUIPrefix + 5)
DECLARE_PMID(kWidgetIDSpace,		kAddMacroTextWidgetID, 				kEditorHelperUIPrefix + 6)
DECLARE_PMID(kWidgetIDSpace,		kMacroListWidgetID, 				kEditorHelperUIPrefix + 7)
DECLARE_PMID(kWidgetIDSpace,		kMacroNameNodeWidgetId, 			kEditorHelperUIPrefix + 8)
DECLARE_PMID(kWidgetIDSpace,		kMacroNodeEditWidgetID, 			kEditorHelperUIPrefix + 9)
DECLARE_PMID(kWidgetIDSpace,		kTextMacroControlStripWidgetId, 	kEditorHelperUIPrefix + 10)
DECLARE_PMID(kWidgetIDSpace,		kNewMacroButtonWidgetID, 			kEditorHelperUIPrefix + 11)
DECLARE_PMID(kWidgetIDSpace,		kDeleteMacroButtonWidgetID, 		kEditorHelperUIPrefix + 12)
DECLARE_PMID(kWidgetIDSpace,		kUnassignButtonWidgetID, 			kEditorHelperUIPrefix + 13)
DECLARE_PMID(kWidgetIDSpace,		kMacroActionWidgetID, 				kEditorHelperUIPrefix + 14)
DECLARE_PMID(kWidgetIDSpace,		kEditMacroDialogId, 				kEditorHelperUIPrefix + 15)
DECLARE_PMID(kWidgetIDSpace,		kEditTextScrollWidgetID, 			kEditorHelperUIPrefix + 16)
DECLARE_PMID(kWidgetIDSpace,		kEditMacroButtonWidgetID, 			kEditorHelperUIPrefix + 17)
DECLARE_PMID(kWidgetIDSpace,		kRunMacroButtonWidgetID, 			kEditorHelperUIPrefix + 18)
DECLARE_PMID(kWidgetIDSpace,		kShortcutLabelWidgetId, 			kEditorHelperUIPrefix + 19)
DECLARE_PMID(kWidgetIDSpace,		kMacroSCEditBoxWidgetId, 			kEditorHelperUIPrefix + 20)
DECLARE_PMID(kWidgetIDSpace,		kMacroSCCurrentActionLabelWidgetId,	kEditorHelperUIPrefix + 21)
DECLARE_PMID(kWidgetIDSpace,		kMacroSCCurrentActionTextWidgetId,  kEditorHelperUIPrefix + 22)
DECLARE_PMID(kWidgetIDSpace,		kMacroSCCurrentActionPanelWidgetId, kEditorHelperUIPrefix + 23)
DECLARE_PMID(kWidgetIDSpace,		kMacroSCWarningIconWidgetID,		kEditorHelperUIPrefix + 24)
DECLARE_PMID(kWidgetIDSpace,		kMacroEditingBorderWidgetID,		kEditorHelperUIPrefix + 25)
DECLARE_PMID(kWidgetIDSpace,		kStyledMacroGroupWidgetID,			kEditorHelperUIPrefix + 26)
//DECLARE_PMID(kWidgetIDSpace,		kStyledMacroButtonWidgetID,			kEditorHelperUIPrefix + 27)
//DECLARE_PMID(kWidgetIDSpace,		kNoStyledMacroButtonWidgetID,		kEditorHelperUIPrefix + 28)
DECLARE_PMID(kWidgetIDSpace,		kStyledMacroCheckBoxWidgetID,		kEditorHelperUIPrefix + 29)
DECLARE_PMID(kWidgetIDSpace,		kMacroStyledWidgetID,				kEditorHelperUIPrefix + 30)
DECLARE_PMID(kWidgetIDSpace,		kEHGenericPanel1WidgetID,			kEditorHelperUIPrefix + 31)

//----------------------------------------------------------------------------------------
// Scripting
//----------------------------------------------------------------------------------------

//DECLARE_PMID(kErrorIDSpace, kMacroExists,			kEditorHelperUIPrefix + 1)



#define kEditorHelperInCopy2Format	(kAnnaInitialMinorFormatNumber + 1)
#define kEditorHelperInCopy3Format	(kDragontailInitialMinorFormatNumber + 1)
#define kEditorHelperInCopy4Format	(kFiredrakeInitialMinorFormatNumber + 1)
#define kEditorHelperUILastFormatChange		kEditorHelperInCopy4Format

// Overall
#define kEditorHelperUILastMajorFormatChange			kEditorHelperUILastFormatChange //kFiredrakeMajorFormatNumber
#define kEditorHelperUILastMinorFormatChange			kEditorHelperUILastFormatChange

#define kEditorHelperUIErrorRsrcID 	5000

#endif // __AlignPanelID__

