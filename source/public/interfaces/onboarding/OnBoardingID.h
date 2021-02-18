//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/onboarding/OnBoardingID.h $
//  
//  Owner: murastog
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
//  Defines IDs used by the BscDlg plug-in.
//  
//========================================================================================

#ifndef __OnBoardingID_h__
#define __OnBoardingID_h__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"
#include "FormatNumber.h"

#define kOnBoardingPrefix	 RezLong(0x23000)

// <Start IDC>
// PluginID
#define kOnBoardingPluginName 				"OnBoarding"
DECLARE_PMID(kPlugInIDSpace, kOnBoardingPluginID, kOnBoardingPrefix + 1)

// <Class ID>
DECLARE_PMID(kClassIDSpace, kContextManagerBoss, kOnBoardingPrefix + 1)
DECLARE_PMID(kClassIDSpace, kContextMangerResponderBoss, kOnBoardingPrefix + 2)
//DECLARE_PMID(kClassIDSpace, kSetNewDocCountCmdBoss, kOnBoardingPrefix + 3)
DECLARE_PMID(kClassIDSpace, kSetOpenDocCountCmdBoss, kOnBoardingPrefix + 4)
DECLARE_PMID(kClassIDSpace, kStockIAMResponderBoss, kOnBoardingPrefix + 5)
DECLARE_PMID(kClassIDSpace, kSetFootnoteIAMShownCmdBoss, kOnBoardingPrefix + 6)
DECLARE_PMID(kClassIDSpace, kFootnoteIAMObserverBoss, kOnBoardingPrefix + 7)
DECLARE_PMID(kClassIDSpace, kFootNoteIAMResponderBoss, kOnBoardingPrefix + 8)
DECLARE_PMID(kClassIDSpace, kCopyPasteIAMObserverBoss, kOnBoardingPrefix + 9)
DECLARE_PMID(kClassIDSpace, kSetCopyPasteIAMShownCmdBoss, kOnBoardingPrefix + 10)
DECLARE_PMID(kClassIDSpace, kSetEndNoteIAMShownCmdBoss, kOnBoardingPrefix + 11)
DECLARE_PMID(kClassIDSpace, kEndNoteIAMResponderBoss, kOnBoardingPrefix + 12)
DECLARE_PMID(kClassIDSpace, kSetParaBorderIAMShownCmdBoss, kOnBoardingPrefix + 13)
DECLARE_PMID(kClassIDSpace, kParaBorderIAMObserverBoss, kOnBoardingPrefix + 14)
DECLARE_PMID(kClassIDSpace, kParaBorderIAMResponderBoss, kOnBoardingPrefix + 15)
DECLARE_PMID(kClassIDSpace, kDudenIAMResponderBoss, kOnBoardingPrefix + 16)
DECLARE_PMID(kClassIDSpace, kSetDudenIAMShownCmdBoss, kOnBoardingPrefix + 17)
DECLARE_PMID(kClassIDSpace, kSetParaBorderIAMforIconShownCmdBoss, kOnBoardingPrefix + 18)
DECLARE_PMID(kClassIDSpace, kSetConsistentShortcutsIAMShownCmdBoss, kOnBoardingPrefix + 19)
DECLARE_PMID(kClassIDSpace, kConsistentShortcutsIAMResponderBoss, kOnBoardingPrefix + 20)
DECLARE_PMID(kClassIDSpace, kOnBoardingObserverBoss, kOnBoardingPrefix + 21)
DECLARE_PMID(kClassIDSpace, kPropsPanelIAMResponderBoss, kOnBoardingPrefix + 22)
DECLARE_PMID(kClassIDSpace, kPropsPanelIAMShownCmdBoss, kOnBoardingPrefix + 23)
DECLARE_PMID(kClassIDSpace, kkAdaptiveLayoutIAMShowCountIncrementCmdBoss, kOnBoardingPrefix + 24)
DECLARE_PMID(kClassIDSpace, kSetImportPDFCommentsIAMShownCmdBoss, kOnBoardingPrefix + 25)
DECLARE_PMID(kClassIDSpace, kImportPDFCommentsIAMResponderBoss, kOnBoardingPrefix + 26)
DECLARE_PMID(kClassIDSpace, kAdaptiveIAMCloseOnAllDocCloseResponderBoss, kOnBoardingPrefix + 27)
DECLARE_PMID(kClassIDSpace, kContentAwareFitIAMResponderBoss, kOnBoardingPrefix + 28)
DECLARE_PMID(kClassIDSpace, kSetContentAwareFitIAMShownCountCmdBoss, kOnBoardingPrefix + 29)
DECLARE_PMID(kClassIDSpace, kOnboardingConversionProviderBoss, kOnBoardingPrefix + 30)
DECLARE_PMID(kClassIDSpace, kSetVariableFontsIAMShownCmdBoss, kOnBoardingPrefix + 31)
DECLARE_PMID(kClassIDSpace, kVariableFontsIAMResponderBoss, kOnBoardingPrefix + 32)
DECLARE_PMID(kClassIDSpace, kReviewCollaborationIAMCmdBoss, kOnBoardingPrefix + 33)
DECLARE_PMID(kClassIDSpace, kReviewCollaborationIAMResponderBoss, kOnBoardingPrefix + 34)
DECLARE_PMID(kClassIDSpace, kSetPdfExportDocListCmdBoss, kOnBoardingPrefix + 35)
DECLARE_PMID(kClassIDSpace, kReviewCollabNewLabelShownCmdBoss, kOnBoardingPrefix + 36)
DECLARE_PMID(kClassIDSpace, kReviewCollabNewDotShownCmdBoss, kOnBoardingPrefix + 37)
DECLARE_PMID(kClassIDSpace, kLocateColorIAMCmdBoss, kOnBoardingPrefix + 38)
DECLARE_PMID(kClassIDSpace, kSetFastEditorModeShownCountCmdBoss, kOnBoardingPrefix + 39)
DECLARE_PMID(kClassIDSpace, kFastEditorIAMResponderBoss, kOnBoardingPrefix + 40)
DECLARE_PMID(kClassIDSpace, kSetFastEditorModeFeedbackIAMShownCmdBoss, kOnBoardingPrefix + 41)
DECLARE_PMID(kClassIDSpace, kSetFastEditorModeFeedbackUIShownCountCmdBoss, kOnBoardingPrefix + 42)
DECLARE_PMID(kClassIDSpace, kNormalModeIAMCmdBoss, kOnBoardingPrefix + 43)
DECLARE_PMID(kClassIDSpace, kTextCommentsIAMCmdBoss, kOnBoardingPrefix + 44)
DECLARE_PMID(kClassIDSpace, kTextCommentsIAMResponderBoss, kOnBoardingPrefix + 45)

// <Implementation ID>
DECLARE_PMID(kImplementationIDSpace, kOnBoardingManagerImpl, kOnBoardingPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kContextManagerStartupShutdownImpl, kOnBoardingPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kContextManagerObserverImpl, kOnBoardingPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kContextManagerSignalRespServiceImpl, kOnBoardingPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kContextManagerResponderImpl, kOnBoardingPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kNewDocCountIntDataImpl_Obsolete, kOnBoardingPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kNewDocCountCmdImpl_Obsolete, kOnBoardingPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kOnBoardingExtensionEventsWrapperImpl, kOnBoardingPrefix + 12)

DECLARE_PMID(kImplementationIDSpace, kActiveIAMUniqueIDDataImpl, kOnBoardingPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kCopyPasteIAMObserverImpl, kOnBoardingPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kCopyPasteIAMStartupShutdownImpl, kOnBoardingPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kCopyPasteIAMShownCmdImpl, kOnBoardingPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kCopyPasteIAMShownBoolDataImpl_Obsolete, kOnBoardingPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kEndNoteIAMShownBoolDataImpl_Obsolete, kOnBoardingPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kEndnoteIAMCountIntDataImpl_Obsolete, kOnBoardingPrefix + 29)
//gap
DECLARE_PMID(kImplementationIDSpace, kIsFinalIAMImpl, kOnBoardingPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kIsEventFromPageOrSpreadCreateImpl, kOnBoardingPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kParaBorderIAMShownBoolDataImpl_Obsolete, kOnBoardingPrefix + 34)
//gap
DECLARE_PMID(kImplementationIDSpace, kDisableEndnoteIAMForDataMergeImpl_Obsolete, kOnBoardingPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kContentAwareWrapIAMUtilsImpl, kOnBoardingPrefix + 41)
//gap
DECLARE_PMID(kImplementationIDSpace, kDudenIAMShownBoolDataImpl_Obsolete, kOnBoardingPrefix + 43)
//gap
DECLARE_PMID(kImplementationIDSpace, kParaBorderIAMforIconShownBoolDataImpl_Obsolete, kOnBoardingPrefix + 45)
//gap
DECLARE_PMID(kImplementationIDSpace, kConsistentShortcutsIAMShownBoolDataImpl_Obsolete, kOnBoardingPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kOnBoardingStartupShutdownImpl, kOnBoardingPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kOnBoardingObserverImpl, kOnBoardingPrefix + 54)

DECLARE_PMID(kImplementationIDSpace, kPropsPanelIAMSignalRespServiceImpl, kOnBoardingPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kPropsPanelIAMResponderImpl, kOnBoardingPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kPropsPanelIAMShownCmdImpl, kOnBoardingPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kPropsPanelIAMShownBoolDataImpl, kOnBoardingPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kWorkspaceBasicsFTUEUtilsImpl, kOnBoardingPrefix + 59)
//gap
//gap
DECLARE_PMID(kImplementationIDSpace, kAdaptiveLayoutCoachMarkShowCountImpl_Obsolete, kOnBoardingPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kAdaptiveLayoutToastShowCountImpl_Obsolete, kOnBoardingPrefix + 63)
//gap
//gap
//gap
DECLARE_PMID(kImplementationIDSpace, kImportPDFCommentsIAMShownBoolDataImpl_Obsolete, kOnBoardingPrefix + 67)
//gap
//gap
//gap
DECLARE_PMID(kImplementationIDSpace, kContentAwareFitIAMShownCountIntDataImpl_Obsolete, kOnBoardingPrefix + 71)
//gap
DECLARE_PMID(kImplementationIDSpace, kPropsPanelIAMThreadImpl, kOnBoardingPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kVariableFontsIAMResponderImpl, kOnBoardingPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kVariableFontsIAMSignalRespServiceImpl, kOnBoardingPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kVariableFontsIAMShownCmdImpl, kOnBoardingPrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kVariableFontsIAMShownBoolDataImpl, kOnBoardingPrefix + 77)

DECLARE_PMID(kImplementationIDSpace, kReviewCollaborationIAMSessionCountIntDataImpl, kOnBoardingPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kReviewCollaborationIAMShownInSessionBoolDataImpl, kOnBoardingPrefix + 79)
DECLARE_PMID(kImplementationIDSpace, kReviewCollaborationIAMCmdImpl, kOnBoardingPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kPdfExportDocsListDataImpl, kOnBoardingPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kReviewCollaborationIAMServiceProviderImpl, kOnBoardingPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kReviewCollaborationIAMResponderImpl, kOnBoardingPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kSetPdfExportDocListCmdImpl, kOnBoardingPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kReviewCollabNewLabelShownBoolDataImpl, kOnBoardingPrefix + 85)
DECLARE_PMID(kImplementationIDSpace, kReviewCollabNewLabelShownCmdImpl, kOnBoardingPrefix +86)
DECLARE_PMID(kImplementationIDSpace, kReviewCollabNewDotShownBoolDataImpl, kOnBoardingPrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kReviewCollabNewDotShownCmdImpl, kOnBoardingPrefix +88)
DECLARE_PMID(kImplementationIDSpace, kReviewCollabIAMIdleTaskImpl, kOnBoardingPrefix +89)
DECLARE_PMID(kImplementationIDSpace, kFastEditorModeIAMUtilsImpl, kOnBoardingPrefix + 90)
DECLARE_PMID(kImplementationIDSpace, kFastEditorModeShownCountIntDataImpl, kOnBoardingPrefix + 91)
DECLARE_PMID(kImplementationIDSpace, kFastEditorModeShownCountCmdImpl, kOnBoardingPrefix + 92)
DECLARE_PMID(kImplementationIDSpace, kFastEditorSignalRespServiceImpl, kOnBoardingPrefix + 93)
DECLARE_PMID(kImplementationIDSpace, kFastEditorIAMResponderImpl, kOnBoardingPrefix + 94)
DECLARE_PMID(kImplementationIDSpace, kFastEditorModeFeedbackUIToShowCountIntDataImpl, kOnBoardingPrefix + 95)
DECLARE_PMID(kImplementationIDSpace, kFastEditorModeFeedbackIAMShownBoolDataImpl, kOnBoardingPrefix + 96)
DECLARE_PMID(kImplementationIDSpace, kFastEditorModeFeedbackUIShownCountCmdImpl, kOnBoardingPrefix + 97)
DECLARE_PMID(kImplementationIDSpace, kFastEditorModeFeedbackIAMShownCmdImpl, kOnBoardingPrefix + 98)

DECLARE_PMID(kImplementationIDSpace, kLocateColorTabOnBoardingBlueDotImpl, kOnBoardingPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kLocateColorIAMCmdImpl, kOnBoardingPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kNormalModeIAMCmdImpl, kOnBoardingPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kNormalModeIAMSessionDocShownImpl, kOnBoardingPrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kTextCommentsIAMSessionDocShownImpl, kOnBoardingPrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kTextCommentsIAMResponderImpl, kOnBoardingPrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kTextCommentsServiceProviderImpl, kOnBoardingPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kTextCommentsIAMCmdImpl, kOnBoardingPrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kTextCommentsIAMIdleTaskImpl, kOnBoardingPrefix + 108)
DECLARE_PMID(kImplementationIDSpace, kArtifactURNImpl, kOnBoardingPrefix + 109)
//<Interface ID>

DECLARE_PMID(kInterfaceIDSpace, IID_IONBOARDINGMANAGER, kOnBoardingPrefix + 1)
//DECLARE_PMID(kInterfaceIDSpace, IID_INEWDOCCMDCOUNT, kOnBoardingPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCOPENCMDCOUNT, kOnBoardingPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IONBOARDINGEXTENSIONEVENTWRAPPER, kOnBoardingPrefix + 4)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICONTEXTMANAGEROBSERVER, kOnBoardingPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IFOOTNOTEIAMSHOWN, kOnBoardingPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IACTIVEIAM, kOnBoardingPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOPYPASTEIAMOBSERVER, kOnBoardingPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOPYPASTEIAMSHOWN, kOnBoardingPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IENDNOTEIAMSHOWN, kOnBoardingPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IENDNOTEIAMCOUNT, kOnBoardingPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IENDNOTEIAMUTILS, kOnBoardingPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IENDNOTEIAMOBSERVER, kOnBoardingPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IFINALIAM, kOnBoardingPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IEVENTFROMPAGEORSPREADCREATE, kOnBoardingPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IPARABORDERIAMSHOWN, kOnBoardingPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IDUDENIAMSHOWN, kOnBoardingPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_IPARABORDERIAMFORICONSHOWN, kOnBoardingPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONSISTENTSHORTCUTSIAMOBSERVER, kOnBoardingPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONSISTENTSHORTCUTSIAMSHOWN, kOnBoardingPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONSISTENTSHORTCUTSIAMUTILS, kOnBoardingPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_IONBOARDINGOBSERVER, kOnBoardingPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_IFILENEWCOMPLETENOTIFIER, kOnBoardingPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_ILEARNPANELCLOSENOTIFIER, kOnBoardingPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_IPROPSPANELIAMSHOWN, kOnBoardingPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_IWORKSPACEBASICSFTUEUTILS, kOnBoardingPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_IPROPSPANELIAMSHOWNINSESSION, kOnBoardingPrefix + 28)

DECLARE_PMID(kInterfaceIDSpace, IID_IADAPTIVELAYOUTIAMUTILS, kOnBoardingPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_IADAPTIVELAYOUTCOACHMARKSHOWCOUNT, kOnBoardingPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_IADAPTIVELAYOUTTOASTSHOWCOUNT, kOnBoardingPrefix + 31)

DECLARE_PMID(kInterfaceIDSpace, IID_IIMPORTPDFCOMMENTSIAMSHOWN, kOnBoardingPrefix + 32)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMPORTPDFCOMMENTSIAMUTILS, kOnBoardingPrefix + 33)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTENTAWAREFITIAMSHOWNCOUNT, kOnBoardingPrefix + 34)
DECLARE_PMID(kInterfaceIDSpace, IID_IPROPSPANELIAMTHREAD, kOnBoardingPrefix + 35)
DECLARE_PMID(kInterfaceIDSpace, IID_IVARIABLEFONTSIAMSHOWN, kOnBoardingPrefix + 36)

DECLARE_PMID(kInterfaceIDSpace, IID_IREVIEWCOLLBORATIONIAMSESSIONCOUNT, kOnBoardingPrefix + 37)
DECLARE_PMID(kInterfaceIDSpace, IID_IREVIEWCOLLBORATIONIAMSHOWNINSESSION, kOnBoardingPrefix + 38)
DECLARE_PMID(kInterfaceIDSpace, IID_IPDFEXPORTDOCSLISTDATA, kOnBoardingPrefix + 39)
DECLARE_PMID(kInterfaceIDSpace, IID_IREVIEWCOLLABNEWLABELSHOWN, kOnBoardingPrefix + 40)
DECLARE_PMID(kInterfaceIDSpace, IID_IREVIEWCOLLABNEWDOTSHOWN, kOnBoardingPrefix + 41)
DECLARE_PMID(kInterfaceIDSpace, IID_IREVIEWCOLLABIAMIDLETASK, kOnBoardingPrefix + 42)
DECLARE_PMID(kInterfaceIDSpace, IID_IFASTEDITORMODEIAMUTILS, kOnBoardingPrefix + 43)
DECLARE_PMID(kInterfaceIDSpace, IID_IFASTEDITORMODESHOWNCOUNT, kOnBoardingPrefix + 44)
DECLARE_PMID(kInterfaceIDSpace, IID_IFASTEDITORFEEDBACKUITOSHOWCOUNT, kOnBoardingPrefix + 45)
DECLARE_PMID(kInterfaceIDSpace, IID_IFASTEDITORFEEDBACKIAMSHOWN, kOnBoardingPrefix + 46)
DECLARE_PMID(kInterfaceIDSpace, IID_ILOCATECOLORTABONBOARDINGBLUEDOT, kOnBoardingPrefix + 51)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTENTAWAREWRAPIAMUTILS, kOnBoardingPrefix + 52)
DECLARE_PMID(kInterfaceIDSpace, IID_INORMALMODEIAMSESSIONDOCSHOWN, kOnBoardingPrefix + 53)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTCOMMENTSIAMSESSIONDOCSHOWN, kOnBoardingPrefix + 54)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTCOMMENTSIAMIDLETASK, kOnBoardingPrefix + 55)
DECLARE_PMID(kInterfaceIDSpace, IID_IARTIFACTURNDATA, kOnBoardingPrefix + 56)

// <Error ID>
// Error Codes
DECLARE_PMID(kErrorIDSpace, kBadParamterError, kOnBoardingPrefix + 1)


// <Widget ID>
// Character attribute widgets <1-50>

// <Message ID>
// <Message ID> 
DECLARE_PMID(kMessageIDSpace, kFileNewComplete, kOnBoardingPrefix + 1)
DECLARE_PMID(kMessageIDSpace, kLearnPanelClose, kOnBoardingPrefix + 2)  
//DECLARE_PMID(kMessageIDSpace, kItemPickedMessage, kContentDropperPrefix + 1)

// <Service ID>
// Service IDs
//DECLARE_PMID(kServiceIDSpace, kContentDropperPrefsPanelServiceImpl, kContentDropperPrefix + 1)

// <Action ID>
// Action IDs
//DECLARE_PMID(kActionIDSpace, kContentDropperToolActionID, kContentDropperPrefix + 1)

//<Icon IDs>


// Initial data format version numbers
//#define kOnBoardingFirstMajorFormatNumber  RezLong(1)
//#define kOnBoardingFirstMinorFormatNumber  RezLong(0)

// Data format version numbers for the PluginVersion resource
#define kOnBoardingLastMajorFormatNumber kCC15MajorFormatNumber
#define kOnBoardingLastMinorFormatNumber kCC15InitialMinorFormatNumber

#endif
