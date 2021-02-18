//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/InCopyBridgeUIID.h $
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
//  
//  Contains IDs used by the InCopyBridgeUI
//  
//========================================================================================

#ifndef __InCopyBridgeUIID__
#define __InCopyBridgeUIID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

// double check with AdobePrefix.h
#define kICBridgeUIPrefix			RezLong(0x18F00)  

//----------------------------------------------------------------------------------------
// Plug-in identifier
//----------------------------------------------------------------------------------------

#define kICBridgeUIPluginName 	"InCopy Bridge UI"
DECLARE_PMID(kPlugInIDSpace, kICBridgeUIPluginID, kICBridgeUIPrefix + 1)

//----------------------------------------------------------------------------------------
// Class identifiers
//----------------------------------------------------------------------------------------

DECLARE_PMID(kClassIDSpace,		kICBridgeMenuBoss,				kICBridgeUIPrefix + 1)
DECLARE_PMID(kClassIDSpace,		kICBridgeWarningCmdBoss,		kICBridgeUIPrefix + 2)
DECLARE_PMID(kClassIDSpace,		kICBridgeTextLockAdornmentBoss,	kICBridgeUIPrefix + 3)
DECLARE_PMID(kClassIDSpace,		kICBridgeExportDialogCmdBoss,	kICBridgeUIPrefix + 4)
DECLARE_PMID(kClassIDSpace, 	kICBridgeAdornmentUpdaterBoss,	kICBridgeUIPrefix + 5)
DECLARE_PMID(kClassIDSpace, 	kICBridgeDocChangesAdornmentUpdaterBoss,		kICBridgeUIPrefix + 6)
DECLARE_PMID(kClassIDSpace, 	kICBridgeAppChangesAdornmentUpdaterBoss,		kICBridgeUIPrefix + 7)
//gap
DECLARE_PMID(kClassIDSpace, 	kICBridgeAfterUpdateLinkAdornmentUpdaterBoss,	kICBridgeUIPrefix + 10)
//gap
DECLARE_PMID(kClassIDSpace, 	kICBridgeSetUserNameAdornmentUpdaterBoss,		kICBridgeUIPrefix + 12)
DECLARE_PMID(kClassIDSpace, 	kICBridgeAddLinkAdornmentUpdaterBoss,			kICBridgeUIPrefix + 13)
//gap
DECLARE_PMID(kClassIDSpace, 	kICBridgeRemoveLinksAdornmentUpdaterBoss,		kICBridgeUIPrefix + 15)
DECLARE_PMID(kClassIDSpace, 	kICBridgeLayoutActionBoss,						kICBridgeUIPrefix + 16)
DECLARE_PMID(kClassIDSpace, 	kICBridgeLayoutAdornmentUpdaterBoss,			kICBridgeUIPrefix + 17)
DECLARE_PMID(kClassIDSpace, 	kICBridgeLayoutSignalBoss,						kICBridgeUIPrefix + 18)
DECLARE_PMID(kClassIDSpace, 	kICBridgeStoryLockStateTaskUpdaterBoss,			kICBridgeUIPrefix + 19)
DECLARE_PMID(kClassIDSpace, 	kICStoriesCurrentIdleTaskBoss,					kICBridgeUIPrefix + 20)
DECLARE_PMID(kClassIDSpace,		kICBridgeStartupShutdownBoss,					kICBridgeUIPrefix + 21)
DECLARE_PMID(kClassIDSpace,		kInCopySaveAlertServiceBoss,					kICBridgeUIPrefix + 22)

//----------------------------------------------------------------------------------------
// Interface identifiers
//----------------------------------------------------------------------------------------

DECLARE_PMID(kInterfaceIDSpace,	IID_IUSERNAMEDATA,				kICBridgeUIPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace,	IID_IFILEPATHDATA,				kICBridgeUIPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace,	IID_IDLGRESULTDATA,				kICBridgeUIPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace,	IID_IWARNMSGDATA,				kICBridgeUIPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace,	IID_IBRIDGEADORNMENTUTILS,		kICBridgeUIPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace,	IID_IBRIDGELAYOUTOBSERVER,		kICBridgeUIPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace,	IID_IAPPNAMEDATA,				kICBridgeUIPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace,	IID_IDOCNAMEDATA,				kICBridgeUIPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace,	IID_IINCOPYBRIDGEUIUTILS,		kICBridgeUIPrefix + 9)

//----------------------------------------------------------------------------------------
// Implementation identifiers
//----------------------------------------------------------------------------------------

DECLARE_PMID(kImplementationIDSpace, kICBridgeMenuActionImpl,			kICBridgeUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kICBridgeWarningCmdImpl,			kICBridgeUIPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kICBridgeUserNameDataImpl,			kICBridgeUIPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kICBridgeFilePathDataImpl,			kICBridgeUIPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kICBridgeDlgResultImpl,			kICBridgeUIPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kICBridgeWarnMsgImpl,				kICBridgeUIPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kICBridgeTextLockAdornmentImpl,	kICBridgeUIPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kLiveEditLinksPaletteSuiteImpl,	kICBridgeUIPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kICBridgeExportDialogCmdImpl,		kICBridgeUIPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kICBridgeTextLockTipImpl,			kICBridgeUIPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kICBridgeFrameTipImpl,				kICBridgeUIPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kICBridgeAdornmentVisitorImpl,		kICBridgeUIPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kICBridgeAdornmentUtilsImpl,		kICBridgeUIPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kICBridgeAdornmentUpdaterImpl,		kICBridgeUIPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kICBridgeLayoutObserverImpl,		kICBridgeUIPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kICBridgeLayoutActionImpl,			kICBridgeUIPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kICBridgeLayoutRespServiceImpl,	kICBridgeUIPrefix + 17)	
DECLARE_PMID(kImplementationIDSpace, kICBridgeStoryLockRespServiceImpl,	kICBridgeUIPrefix + 18) 
DECLARE_PMID(kImplementationIDSpace, kICBridgeAppNameDataImpl,			kICBridgeUIPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kICBridgeDocNameDataImpl,			kICBridgeUIPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kInCopyBridgeUIUtilsImpl,			kICBridgeUIPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kICStoriesCurrentIdleTaskImpl,		kICBridgeUIPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kICBridgeStartupShutdownImpl,		kICBridgeUIPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kInCopyUISPImpl,					kICBridgeUIPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kInCopySaveAlertServiceImpl,		kICBridgeUIPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kICWorkgroupUIUtilsImpl,			kICBridgeUIPrefix + 26)

//----------------------------------------------------------------------------------------
// Widget identifiers
//----------------------------------------------------------------------------------------
#define kICBDontShowAgainContinueWithoutUndoWidgetID	kICBridgeUIPrefix + 1		// really an id for a don't-show alert

//----------------------------------------------------------------------------------------
// Action identifiers
//----------------------------------------------------------------------------------------

DECLARE_PMID(kActionIDSpace,	kICBridgeSeperatorActionID,				kICBridgeUIPrefix + 1)
DECLARE_PMID(kActionIDSpace,	kICBridgeEditInPlaceActionID,			kICBridgeUIPrefix + 2)
DECLARE_PMID(kActionIDSpace,	kICBridgeRevertActionID,				kICBridgeUIPrefix + 3)
DECLARE_PMID(kActionIDSpace,	kICBridgeSubmitActionID,				kICBridgeUIPrefix + 4)
DECLARE_PMID(kActionIDSpace,	kICBridgeEditInPlaceSelActionID,		kICBridgeUIPrefix + 5)
DECLARE_PMID(kActionIDSpace,	kICBridgeRevertSelActionID,				kICBridgeUIPrefix + 6)
DECLARE_PMID(kActionIDSpace,	kICBridgeSubmitSelActionID,				kICBridgeUIPrefix + 7)
DECLARE_PMID(kActionIDSpace,	kICBridgeExportSelContextActionID,		kICBridgeUIPrefix + 8)
//DECLARE_PMID(kActionIDSpace,	kICBridgeUnembedSelActionID,			kICBridgeUIPrefix + 9)
DECLARE_PMID(kActionIDSpace,	kICBridgeSaveVersionSelActionID,		kICBridgeUIPrefix + 10)
DECLARE_PMID(kActionIDSpace,	kICBridgeRelinkSelActionID,				kICBridgeUIPrefix + 11)
DECLARE_PMID(kActionIDSpace,	kICBridgeSubmitAllActionID,				kICBridgeUIPrefix + 12)
DECLARE_PMID(kActionIDSpace,	kICBridgeSLEditInPlaceActionID,			kICBridgeUIPrefix + 13)
DECLARE_PMID(kActionIDSpace,	kICBridgeSLRevertActionID,				kICBridgeUIPrefix + 14)
DECLARE_PMID(kActionIDSpace,	kICBridgeSLSubmitActionID,				kICBridgeUIPrefix + 15)
DECLARE_PMID(kActionIDSpace,	kICBridgeSLSubmitAllActionID,			kICBridgeUIPrefix + 16)
DECLARE_PMID(kActionIDSpace,	kICBridgeSLRelinkActionID,				kICBridgeUIPrefix + 17)
DECLARE_PMID(kActionIDSpace,	kICBridgeExportSelMenuActionID,			kICBridgeUIPrefix + 18)
DECLARE_PMID(kActionIDSpace,	kICBridgeSaveSepActionID,				kICBridgeUIPrefix + 19)
DECLARE_PMID(kActionIDSpace,	kICBridgeSeperator2ActionID,			kICBridgeUIPrefix + 20)
DECLARE_PMID(kActionIDSpace,	kICBridgeSeperator3ActionID,			kICBridgeUIPrefix + 21)
DECLARE_PMID(kActionIDSpace,	kICBridgeSeperator4ActionID,			kICBridgeUIPrefix + 22)

//----------------------------------------------------------------------------------------
// Service Provider IDs
//----------------------------------------------------------------------------------------

DECLARE_PMID(kServiceIDSpace,	kICBridgeLayoutResponderService,		kICBridgeUIPrefix + 1)
DECLARE_PMID(kServiceIDSpace,	kICBridgeStoryLockStateResponderService,kICBridgeUIPrefix + 2)

//Message IDs
DECLARE_PMID(kMessageIDSpace, kExportAllStoriesMsgID, kICBridgeUIPrefix + 1)
//----------------------------------------------------------------------------------------
// Error Codes
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Strings
//----------------------------------------------------------------------------------------

#define kICBridgeUIStringsRsrcID 					1000
#define kICBridgeUIStringsNoTransRsrcID 			1100
#define kICBridgeActionRsrcID 						1200
#define kICBridgeMenuRsrcID 						1300

#define kInCopyAlertPermissionDenied		"InCopyAlertPermissionDenied"
#define kInCopyAlertPermissionDeniedLong	"InCopyAlertPermissionDeniedLong"
#define kInCopyAlertExportUpdated			"InCopyAlertExportUpdated"
#define kInCopyAlertEditInPlaceInUse		"InCopyAlertEditInPlaceInUse"
#define kInCopyAlertSubmitNotCheckedOut		"InCopyAlertSubmitNotCheckedOut"
#define kInCopyAlertSubmitUpdated			"InCopyAlertSubmitUpdated"
#define kInCopyAlertRevertNotCheckedOut		"InCopyAlertRevertNotCheckedOut"
#define kInCopyAlertRevertUpdated			"InCopyAlertRevertUpdated"
#define kInCopyAlertEditInPlaceOverride		"InCopyAlertEditInPlaceOverride"
#define kInCopyAlertEditInPlaceOverrideLong	"InCopyAlertEditInPlaceOverrideLong"
#define kInCopyAlertSubmitOverride			"InCopyAlertSubmitOverride"
#define kInCopyAlertSubmitOverrideLong		"InCopyAlertSubmitOverrideLong"
#define kInCopyAlertEditInPlaceOutOfDate	"InCopyAlertEditInPlaceOutOfDate"
#define kInCopyAlertUnembedSave				"InCopyAlertUnembedSave"

#define kInCopyAlertChoiceYes				"Yes"
#define kInCopyAlertChoiceNo				"No"
#define kInCopyAlertChoiceCancel			"Cancel"
#define kInCopyAlertChoiceReplace			"Replace"
#define kInCopyAlertChoiceUnlink			"Unlink"
#define kInCopyAlertChoiceEmbed				"Embed"
#define kInCopyAlertChoiceDiscard			"Discard Changes"
#define kInCopyAlertChoiceContinue			"Continue Editing"
#define kInCopyAlertChoiceSubmit			"Submit Changes"
#define kInCopyAlertChoiceOverride			"Override"
#define kInCopyAlertChoiceSave				"Save to New File..."
#define kInCopyAlertChoiceRevert			"Revert Changes"
#define kInCopyAlertChoiceOverrideSave		"Override & Save Version"
#define kInCopyAlertChoiceContinueWithoutUndo	"Continue without undo?"

// tip strings...
#define kInCopyTipCheckedIn					"InCopyTipCheckedIn"
#define kInCopyTipCheckedOut				"InCopyTipCheckedOut"
#define kInCopyTipCheckedOutLong			"InCopyTipCheckedOutLong"
#define kInCopyTipCheckedOutByYou			"InCopyTipCheckedOutByYou"
#define kInCopyTipCheckedOutByYouElsewhere	"InCopyTipCheckedOutByYouElsewhere"
#define kInCopyTipLocked					"InCopyTipLocked"
#define kInCopyTipLockedLong				"InCopyTipLockedLong"
#define kInCopyTipEmbedded					"InCopyTipEmbedded"
#define kInCopyTipMissing					"InCopyTipMissing"
#define kInCopyTipOutOfDate					"InCopyTipOutOfDate"
#define kInCopyTipCheckedInOutOfDate		"InCopyTipCheckedInOutOfDate"
#define kInCopyTipCheckedOutOutOfDate		"InCopyTipCheckedOutOutOfDate"
#define kInCopyTipCheckedOutOutOfDateLong	"InCopyTipCheckedOutOutOfDateLong"
#define kInCopyTipCheckedOutByYouOutOfDate	"InCopyTipCheckedOutByYouOutOfDate"
#define kInCopyTipLockedOutOfDate			"InCopyTipLockedOutOfDate"
#define kInCopyTipLockedOutOfDateLong		"InCopyTipLockedOutOfDateLong"
#define kInCopyTipEmbeddedOutOfDate			"InCopyTipEmbeddedOutOfDate"

#define kInCopyTipEditInPlace				"Edit Story In Place"
#define kInCopyTipSubmit					"Submit Story"
#define kInCopyTipRevert					"Revert Story Changes"
#define kInCopyTipEmbed						"Embed Story"
#define kInCopyTipUnembed					"Unembed Story"
#define kInCopyTipRelink					"Relink"
#define kInCopyTipNotInAssignment			"InCopyTipNotInAssignment"
#define kICBridgeUpdateAdornmentSleep 		1000

#endif // __InCopyBridgeUIID__
