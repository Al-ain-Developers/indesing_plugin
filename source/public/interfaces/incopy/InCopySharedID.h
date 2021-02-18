//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/InCopySharedID.h $
//  
//  Owner: 
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

#ifndef __INCOPYSHAREDID__
#define __INCOPYSHAREDID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"
#include "FormatNumber.h"

#define kInCopySharedPrefix	 RezLong(0xa400)	// reserved in AdobePrefix.h

// <PlugInID>
//---------------------------------------------------------------
//	PlugInID
//---------
#define kInCopySharedPlugInName					"InCopyShared"
DECLARE_PMID(kPlugInIDSpace, kInCopySharedPlugInID, kInCopySharedPrefix + 1)

// <Class ID>
//---------------------------------------------------------------
//	ClassIDs
//---------------------------------------------------------------
//gap
DECLARE_PMID(kClassIDSpace, kTextLockAdornmentBoss, kInCopySharedPrefix + 2)
DECLARE_PMID(kClassIDSpace, kICSharedOpenDocResponderBoss, kInCopySharedPrefix + 3)
DECLARE_PMID(kClassIDSpace, kBaseTextLockAdornmentBoss, kInCopySharedPrefix + 4)
DECLARE_PMID(kClassIDSpace, kICSharedPageItemResponderBoss, kInCopySharedPrefix + 5)
DECLARE_PMID(kClassIDSpace, kICSharedErrorStringServiceBoss, kInCopySharedPrefix + 6)
DECLARE_PMID(kClassIDSpace, kInCopyInterchangeExportOptionsScriptProviderBoss, kInCopySharedPrefix + 7)
DECLARE_PMID(kClassIDSpace, kPvtUpdateTextCmdBoss, kInCopySharedPrefix + 8)
DECLARE_PMID(kClassIDSpace, kICSharedIteratorRegBoss, kInCopySharedPrefix + 9)
DECLARE_PMID(kClassIDSpace, kDeletedTextBoss, kInCopySharedPrefix + 10)
DECLARE_PMID(kClassIDSpace, kDeletedTextModelMementoBoss, kInCopySharedPrefix + 11)
DECLARE_PMID(kClassIDSpace, kNewStoryThreadCmdBoss, kInCopySharedPrefix + 12)
DECLARE_PMID(kClassIDSpace, kSetDeletedTextOwnedUIDCmdBoss, kInCopySharedPrefix + 13)
DECLARE_PMID(kClassIDSpace, kRedlineScriptBoss, kInCopySharedPrefix + 14)
DECLARE_PMID(kClassIDSpace, kRedlineScriptProviderBoss, kInCopySharedPrefix + 15)
DECLARE_PMID(kClassIDSpace, kRemoveDeletedTextCmdBoss, kInCopySharedPrefix + 16)
DECLARE_PMID(kClassIDSpace, kTCPrefsScriptProviderBoss, kInCopySharedPrefix + 17)
DECLARE_PMID(kClassIDSpace, kRedlineNewStoryResponderBoss, kInCopySharedPrefix + 18)
DECLARE_PMID(kClassIDSpace, kSetRedlineTrackingCmdBoss, kInCopySharedPrefix + 21)
DECLARE_PMID(kClassIDSpace, kCopyDeletedTextCmdBoss, kInCopySharedPrefix + 22)
DECLARE_PMID(kClassIDSpace, kDoSaveWrapperCmdBoss, kInCopySharedPrefix + 23)
DECLARE_PMID(kClassIDSpace, kSetStoryLabelCmdBoss, kInCopySharedPrefix + 24)
DECLARE_PMID(kClassIDSpace, kSetUserNameCmdBoss, kInCopySharedPrefix + 25)
DECLARE_PMID(kClassIDSpace, kChangeStateTransition, kInCopySharedPrefix + 26/*Not a boss, just a message */)
DECLARE_PMID(kClassIDSpace, kSetUserColorCmdBoss, kInCopySharedPrefix + 27)
DECLARE_PMID(kClassIDSpace, kAddedInCopyDocUserListUserMsg, kInCopySharedPrefix + 28)
DECLARE_PMID(kClassIDSpace, kReplacedInCopyDocUserListColorMsg, kInCopySharedPrefix + 29)
//gap
DECLARE_PMID(kClassIDSpace, kRedlinePreProcessDoAddTextCmdBoss,		kInCopySharedPrefix + 32)
//gap
DECLARE_PMID(kClassIDSpace, kInCopyDeleteStoryThreadCmdBoss, kInCopySharedPrefix + 34)
DECLARE_PMID(kClassIDSpace, kSetUserColorsCmdBoss, kInCopySharedPrefix + 35)
DECLARE_PMID(kClassIDSpace, kICSharedNewDocResponderBoss, kInCopySharedPrefix + 36)
DECLARE_PMID(kClassIDSpace, kStoryPropScriptProviderBoss, kInCopySharedPrefix + 37)
//gap
DECLARE_PMID(kClassIDSpace, kImportSetDeleteOwnedItemCmdBoss, kInCopySharedPrefix + 40)
DECLARE_PMID(kClassIDSpace, kNoteDataBoss, kInCopySharedPrefix + 41)
DECLARE_PMID(kClassIDSpace, kNoteDataTextModelMementoBoss, kInCopySharedPrefix + 42)
DECLARE_PMID(kClassIDSpace,	kILPlaceHolderPageItemBoss, kInCopySharedPrefix + 43)
DECLARE_PMID(kClassIDSpace,	kICSharedConversionProviderBoss, kInCopySharedPrefix + 44)
// gap
DECLARE_PMID(kClassIDSpace, kRedlinePreserveDeletionCmdBoss, kInCopySharedPrefix + 46)
DECLARE_PMID(kClassIDSpace, kCreateUserCmdBoss, kInCopySharedPrefix + 47)
DECLARE_PMID(kClassIDSpace, kDeletedTextInsertCmdBoss, kInCopySharedPrefix + 48)
DECLARE_PMID(kClassIDSpace, kDeletedTextPasteCmdBoss, kInCopySharedPrefix + 49)
DECLARE_PMID(kClassIDSpace, kDeletedTextTypeCmdBoss, kInCopySharedPrefix + 50)
//DECLARE_PMID(kClassIDSpace, kSetShowInfoColumnCmdBoss, kInCopySharedPrefix + 51)
DECLARE_PMID(kClassIDSpace, kSetOwnedUIDCmdBoss, kInCopySharedPrefix + 52)
DECLARE_PMID(kClassIDSpace, kDeleteNoteHelperCmdBoss, kInCopySharedPrefix + 53)
DECLARE_PMID(kClassIDSpace, kCopyNoteHelperCmdBoss, kInCopySharedPrefix + 54)
//DECLARE_PMID(kClassIDSpace, kSetUserNoteColorCmdBoss, kInCopySharedPrefix + 55)
DECLARE_PMID(kClassIDSpace, kDeletedTextDeleteCmdBoss, kInCopySharedPrefix + 56)

// PDF review notes
/*
DECLARE_PMID(kClassIDSpace, kInsertNoteBoss, kInCopySharedPrefix + 60)
DECLARE_PMID(kClassIDSpace, kCommentNoteBoss, kInCopySharedPrefix + 61)
DECLARE_PMID(kClassIDSpace, kCrossoutNoteBoss, kInCopySharedPrefix + 62)
DECLARE_PMID(kClassIDSpace, kHighlightNoteBoss, kInCopySharedPrefix + 63)
DECLARE_PMID(kClassIDSpace, kUnderlineNoteBoss, kInCopySharedPrefix + 64)
DECLARE_PMID(kClassIDSpace, kReplaceNoteBoss, kInCopySharedPrefix + 65)
DECLARE_PMID(kClassIDSpace, kNoteEndMarkerBoss, kInCopySharedPrefix + 66)
DECLARE_PMID(kClassIDSpace, kNoteEndMarkerOwnedItemMementoBoss, kInCopySharedPrefix + 67)
DECLARE_PMID(kClassIDSpace, kChangeNoteMarkerCmdBoss, kInCopySharedPrefix + 68)
*/

// gap
DECLARE_PMID(kClassIDSpace, kRedlineStrandBoss, kInCopySharedPrefix + 101)
DECLARE_PMID(kClassIDSpace, kVOSRedlineObjectBoss, kInCopySharedPrefix + 102)
DECLARE_PMID(kClassIDSpace, kRedlinePreprocessorBoss, kInCopySharedPrefix + 103)
DECLARE_PMID(kClassIDSpace, kActivateRedlineCmdBoss, kInCopySharedPrefix + 104)
DECLARE_PMID(kClassIDSpace, kDeactivateRedlineCmdBoss, kInCopySharedPrefix + 105)
DECLARE_PMID(kClassIDSpace, kSyncRedlineCmdBoss, kInCopySharedPrefix + 106)
DECLARE_PMID(kClassIDSpace, kAcceptRedlineCmdBoss, kInCopySharedPrefix + 107)
DECLARE_PMID(kClassIDSpace, kRejectRedlineCmdBoss, kInCopySharedPrefix + 108)
DECLARE_PMID(kClassIDSpace, kRejectAllRedlineCmdBoss, kInCopySharedPrefix + 109)
// gap 110-111
DECLARE_PMID(kClassIDSpace, kUnregisterRedlineStrandCmdBoss, kInCopySharedPrefix + 112)
// gap 113
DECLARE_PMID(kClassIDSpace, kPushRedlinePhaseCmdBoss, kInCopySharedPrefix + 114)
DECLARE_PMID(kClassIDSpace, kPopRedlinePhaseCmdBoss, kInCopySharedPrefix + 115)
DECLARE_PMID(kClassIDSpace, kAcceptAllRedlineCmdBoss, kInCopySharedPrefix + 116)
//DECLARE_PMID(kClassIDSpace, kRedlineConversionProviderBoss, kInCopySharedPrefix + 117)
DECLARE_PMID(kClassIDSpace, kSetInCopyInterchangeExportOptionsCmdBoss, kInCopySharedPrefix + 118)
DECLARE_PMID(kClassIDSpace, kRedlineStrandReplacePieceBoss, kInCopySharedPrefix + 119)
DECLARE_PMID(kClassIDSpace, kAcceptRangeRedlineCmdBoss, kInCopySharedPrefix + 120)
DECLARE_PMID(kClassIDSpace, kRejectRangeRedlineCmdBoss, kInCopySharedPrefix + 121)
DECLARE_PMID(kClassIDSpace, kMoveRedlineChangeCmdBoss, kInCopySharedPrefix + 122)
DECLARE_PMID(kClassIDSpace, kSetRedlineScrapDataBoss, kInCopySharedPrefix + 123)
DECLARE_PMID(kClassIDSpace, kRedlineStrandPastePieceBoss, kInCopySharedPrefix + 124)
DECLARE_PMID(kClassIDSpace, kRedlineStrandDiskPageBoss, kInCopySharedPrefix + 125)
DECLARE_PMID(kClassIDSpace, kReplaceDeleteChangeDataCmdBoss, kInCopySharedPrefix + 126)
DECLARE_PMID(kClassIDSpace, kCollapseStateCmdBoss, kInCopySharedPrefix + 127)
DECLARE_PMID(kClassIDSpace, kSplitNoteCmdBoss, kInCopySharedPrefix + 128)
DECLARE_PMID(kClassIDSpace, kNoteModifiedTimeCmdBoss, kInCopySharedPrefix + 129)
DECLARE_PMID(kClassIDSpace, kAddNoteDataCmdBoss, kInCopySharedPrefix + 130)
DECLARE_PMID(kClassIDSpace, kNoteCopyStoryCmdBoss, kInCopySharedPrefix + 131)
DECLARE_PMID(kClassIDSpace, kCreateNoteCmdBoss, kInCopySharedPrefix + 132)
DECLARE_PMID(kClassIDSpace, kConvertNoteHelperCmdImplBoss, kInCopySharedPrefix + 133)
DECLARE_PMID(kClassIDSpace, kDeleteNoteDataCmdBoss, kInCopySharedPrefix + 134)
DECLARE_PMID(kClassIDSpace, kConvertNoteToTextCmdBoss, kInCopySharedPrefix + 135)
DECLARE_PMID(kClassIDSpace, kCopyNoteDataCmdBoss, kInCopySharedPrefix + 136)
DECLARE_PMID(kClassIDSpace,	kInCopyRevertStoryCmdBoss, kInCopySharedPrefix + 137)
DECLARE_PMID(kClassIDSpace, kInCopySaveStoryCmdBoss, kInCopySharedPrefix + 138)
DECLARE_PMID(kClassIDSpace, kRedlinePhase2ConversionBoss, kInCopySharedPrefix + 139)
DECLARE_PMID(kClassIDSpace, kSetTrackChangesPrefsCmdBoss, kInCopySharedPrefix + 140)
DECLARE_PMID(kClassIDSpace,	kAppPropScriptProviderBoss,	kInCopySharedPrefix + 141)
DECLARE_PMID(kClassIDSpace, kInCopyDocUserListScriptProviderBoss, kInCopySharedPrefix + 142)
DECLARE_PMID(kClassIDSpace, kInCopyDocUserListScriptBoss, kInCopySharedPrefix + 143)
DECLARE_PMID(kClassIDSpace, kInlineRefConverterBoss, kInCopySharedPrefix + 144)
DECLARE_PMID(kClassIDSpace, kNoteScriptProviderBoss, kInCopySharedPrefix + 145)
DECLARE_PMID(kClassIDSpace, kSetHideNoteStateCmdBoss, kInCopySharedPrefix + 146)
DECLARE_PMID(kClassIDSpace, kSetNoteDataCmdBoss, kInCopySharedPrefix + 147)
DECLARE_PMID(kClassIDSpace, kStoryListFileBoss, kInCopySharedPrefix + 148)
DECLARE_PMID(kClassIDSpace, kICSharedCloseDocResponderBoss, kInCopySharedPrefix + 149)
DECLARE_PMID(kClassIDSpace, kDeletedTextPhase2ConversionBoss, kInCopySharedPrefix + 150)
DECLARE_PMID(kClassIDSpace, kStoryUpdateLinkServiceProviderBoss, kInCopySharedPrefix + 151)
DECLARE_PMID(kClassIDSpace, kSetShowTrackChangesPrefsCmdBoss, kInCopySharedPrefix + 152)


// <Interface ID>
//---------------------------------------------------------------
//	IIDs
//---------------------------------------------------------------
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IACCEPTREDLINEINHIDDENTEXTDATA, kInCopySharedPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_IINCOPYIMPORTSKIPPLACEGUN, kInCopySharedPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_IRESTORESELECTIONDATA, kInCopySharedPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_ISRCDELDATA, kInCopySharedPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_IDESTDELDATA, kInCopySharedPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_IREDLINEUTILS, kInCopySharedPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_IINCOPYSCRIPTUTILS, kInCopySharedPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_ITLADORNUTILS, kInCopySharedPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_IINCOPYINTERCHANGEEXPORTOPTIONS, kInCopySharedPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRACKCHANGEUTILS, kInCopySharedPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_IDELETEDTEXTDATA, kInCopySharedPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRACKCHANGEAPPSETTINGS, kInCopySharedPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRACKCHANGESTORYSETTINGS, kInCopySharedPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOPYDELETEDTEXTCMDDATA, kInCopySharedPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_IINCOPYUICOLORS, kInCopySharedPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_IREDLINESCRAPDATA, kInCopySharedPrefix + 32)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTORYLABEL, kInCopySharedPrefix + 33)
DECLARE_PMID(kInterfaceIDSpace, IID_IINCOPYDOCUSERLIST,	kInCopySharedPrefix + 34)
DECLARE_PMID(kInterfaceIDSpace, IID_IPVTREJECTRANGEEXTRA,	kInCopySharedPrefix + 35)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRIVATENOTEDATA, kInCopySharedPrefix + 36)
//DECLARE_PMID(kInterfaceIDSpace, IID_IINCLUDEGRAPHICPROXYDATA, kInCopySharedPrefix + 37) replaced by IID_IINCOPYINTERCHANGEEXPORTOPTIONSCMDDATA
DECLARE_PMID(kInterfaceIDSpace, IID_ITRACKCHANGESTORYSETTINGS_DOCUMENT, kInCopySharedPrefix + 38)
DECLARE_PMID(kInterfaceIDSpace, IID_IINCOPYINTERCHANGEEXPORTOPTIONSCMDDATA, kInCopySharedPrefix + 39)
DECLARE_PMID(kInterfaceIDSpace, IID_ISHOWTRACKCHANGESPREFS, kInCopySharedPrefix + 40)
DECLARE_PMID(kInterfaceIDSpace, IID_IUSERINFO, kInCopySharedPrefix + 41)
DECLARE_PMID(kInterfaceIDSpace, IID_ICHANGESTATETRANSITION, kInCopySharedPrefix + 42)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_ISETUSERCOLORSCMDDATA, kInCopySharedPrefix + 44)
DECLARE_PMID(kInterfaceIDSpace, IID_INOTEDATA, kInCopySharedPrefix + 45)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IORIGINALINLINE, kInCopySharedPrefix + 47)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRACKCHANGESETTINGSSUITE, kInCopySharedPrefix + 48)
DECLARE_PMID(kInterfaceIDSpace, IID_INOTEHELPERCMD, kInCopySharedPrefix + 49)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRACKCHANGESUITE, kInCopySharedPrefix + 50)

DECLARE_PMID(kInterfaceIDSpace, IID_ICHANGELIST, kInCopySharedPrefix + 101)
DECLARE_PMID(kInterfaceIDSpace, IID_IREDLINEDATASTRAND, kInCopySharedPrefix + 102)
DECLARE_PMID(kInterfaceIDSpace, IID_IREDLINECHANGEDATA, kInCopySharedPrefix + 103)
DECLARE_PMID(kInterfaceIDSpace, IID_ICREATEREDLINECHANGEDATA, kInCopySharedPrefix + 104)

DECLARE_PMID(kInterfaceIDSpace, IID_IINCOPYSHAREDUTILS, kInCopySharedPrefix + 105)
//Note Suite
DECLARE_PMID(kInterfaceIDSpace, IID_INOTESUITE, kInCopySharedPrefix + 110)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONVERTNOTETOTEXTCMDDATA, kInCopySharedPrefix + 111)
DECLARE_PMID(kInterfaceIDSpace, IID_INOTESUITEUTILS, kInCopySharedPrefix + 112)

DECLARE_PMID(kInterfaceIDSpace, IID_INOTEFINDCHANGESPELLING, kInCopySharedPrefix + 113)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRACKCHANGESPREFSCMDDATA, kInCopySharedPrefix + 114)
DECLARE_PMID(kInterfaceIDSpace, IID_INOTESETTINGS,	kInCopySharedPrefix + 115)

DECLARE_PMID(kInterfaceIDSpace, IID_INOTEREVIEW, kInCopySharedPrefix + 121)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETNOTEDATACMDDATA, kInCopySharedPrefix + 122)

DECLARE_PMID(kInterfaceIDSpace, IID_ISTORYLISTFILE, kInCopySharedPrefix + 123)
DECLARE_PMID(kInterfaceIDSpace, IID_IOWNEDITEMUTILS, kInCopySharedPrefix + 124)

DECLARE_PMID(kInterfaceIDSpace, IID_ISTORYORDEROBSERVER, kInCopySharedPrefix + 125)
DECLARE_PMID(kInterfaceIDSpace, IID_IREORDERSTORIESPROTOCOL, kInCopySharedPrefix + 126)
DECLARE_PMID(kInterfaceIDSpace, IID_IGALLEYTABLEDISPLAYSETTINGS, kInCopySharedPrefix + 127)

DECLARE_PMID(kInterfaceIDSpace, IID_ISTORYUTILS, kInCopySharedPrefix + 128)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTORYVIEWTABLEFACADE, kInCopySharedPrefix + 129)
DECLARE_PMID(kInterfaceIDSpace, IID_IUSERINFOUTILS, kInCopySharedPrefix + 130)


//PDF review notes
/*
DECLARE_PMID(kInterfaceIDSpace, IID_INOTEMARKER, kInCopySharedPrefix + 122)
DECLARE_PMID(kInterfaceIDSpace, IID_ICHANGENOTEMARKERCMDDATA, kInCopySharedPrefix + 123)
*/

// <Implementation ID>
//---------------------------------------------------------------
//	ImplementationIDs
//---------------------------------------------------------------
//gap
DECLARE_PMID(kImplementationIDSpace, kICSharedErrorStringServiceImpl, kInCopySharedPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kInCopyScriptUtilsImpl, kInCopySharedPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kRedlineUtilsImpl, kInCopySharedPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kInCopyImportSkipPlaceGunImpl, kInCopySharedPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kDoSaveWrapperCmdImpl, kInCopySharedPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kInCopyInterchangeExportOptionsImpl, kInCopySharedPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kNoteVisitorHelperImpl, kInCopySharedPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kNoteAnchorTransformImpl, kInCopySharedPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kNoteOwnedItemImpl,	kInCopySharedPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kNoteDataScrapImpl, kInCopySharedPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kNoteDataStoryThreadImpl,	 kInCopySharedPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kNoteDataStoryThreadDictImpl, kInCopySharedPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kNoteDataParcelListImpl, kInCopySharedPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kNoteDataTextPLDataImpl, kInCopySharedPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kNoteDataTextPLComposerImpl, kInCopySharedPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kNoteScriptImpl, kInCopySharedPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kNoteDataImpl, kInCopySharedPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kNoteDataTextModelMementoImpl, kInCopySharedPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kStoryMetaDataUIDImpl, kInCopySharedPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kILPlaceHolderShapeImpl, kInCopySharedPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kOriginalInlineImpl, kInCopySharedPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kTrackChangeSettingsASBImpl, kInCopySharedPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kTrackChangeSettingsTextCSBImpl, kInCopySharedPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kTrackChangeSuiteASBImpl, kInCopySharedPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kTrackChangeSuiteGalleyCSBImpl, kInCopySharedPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kTrackChangeSuiteLayoutCSBImpl, kInCopySharedPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kPvtRejectRangeExtraImpl, kInCopySharedPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kPrivateNoteDataImpl,	kInCopySharedPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kIncludeGraphicProxyDataImpl,	kInCopySharedPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kInCopyInterchangeExportOptionsScriptProviderImpl,	kInCopySharedPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kTextLockAdornmentImpl, kInCopySharedPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kInCopyInterchangeExportOptionsCmdDataImpl, kInCopySharedPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kTCPrefsScriptProviderImpl, kInCopySharedPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kICSharedNewOpenDocResponderImpl, kInCopySharedPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kDeletedTextDeleteCmdImpl, kInCopySharedPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kICSharedPageItemResponderImpl, kInCopySharedPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kDeletedTextInsertCmdImpl, kInCopySharedPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kDeletedTextPasteCmdImpl, kInCopySharedPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kDeletedTextTypeCmdImpl, kInCopySharedPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kPvtUpdateTextCmdImpl, kInCopySharedPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kICSharedIteratorRegImpl, kInCopySharedPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kNewStoryThreadCmdImpl, kInCopySharedPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kSetDeletedTextOwnedUIDCmdImpl, kInCopySharedPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kDeletedTextOwnedItemImpl, kInCopySharedPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kDeletedTextModelMementoImpl, kInCopySharedPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kDeletedTextStoryRefDataImpl, kInCopySharedPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kDeletedTextStoryThreadImpl, kInCopySharedPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kDeletedTextStoryThreadDictImpl, kInCopySharedPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kDeletedTextParcelListImpl, kInCopySharedPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kDeletedTextPLDataImpl, kInCopySharedPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kRedlineScriptImpl, kInCopySharedPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kRedlineScriptProviderImpl, kInCopySharedPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kRemoveDeletedTextCmdImpl, kInCopySharedPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kTrackChangeUtilsImpl, kInCopySharedPrefix + 56)	// on kUtilsBoss
DECLARE_PMID(kImplementationIDSpace, kTLAdornmentUtilsImpl, kInCopySharedPrefix + 57)	// on kUtilsBoss
DECLARE_PMID(kImplementationIDSpace, kDeletedTextDataImpl, kInCopySharedPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kSetUserNameCmdRespServiceImpl, kInCopySharedPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kChangeTextObjectParentImpl, kInCopySharedPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kRedlineNewStoryResponderImpl, kInCopySharedPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kCreateUserCmdImpl, kInCopySharedPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kShowTrackChangesPrefsImpl, kInCopySharedPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kSetShowTrackChangesPrefsCmdImpl, kInCopySharedPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kTrackChangeAppSettingsImpl, kInCopySharedPrefix + 65)	// on kWorkspaceBoss
DECLARE_PMID(kImplementationIDSpace, kTrackChangeStorySettingsImpl, kInCopySharedPrefix + 66)	// on kTextStoryBoss
DECLARE_PMID(kImplementationIDSpace, kInCopyDocUserListImpl, kInCopySharedPrefix + 67)
//gap
DECLARE_PMID(kImplementationIDSpace, kSetRedlineTrackingCmdImpl, kInCopySharedPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kCopyDeletedTextCmdImpl, kInCopySharedPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kCopyDeletedTextCmdDataImpl, kInCopySharedPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kInCopyUIColorsImpl, kInCopySharedPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kRedlineScrapDataImpl, kInCopySharedPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kSetInCopyInterchangeExportOptionsCmdImpl, kInCopySharedPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kSetStoryLabelCmdImpl, kInCopySharedPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kStoryLabelImpl, kInCopySharedPrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kSetOwnedUIDCmdImpl, kInCopySharedPrefix + 77)
DECLARE_PMID(kImplementationIDSpace, kDeleteNoteHelperCmdImpl, kInCopySharedPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kCopyNoteHelperCmdImpl, kInCopySharedPrefix + 79)
//gap
DECLARE_PMID(kImplementationIDSpace, kInCopyExportOptionsPersistImpl, kInCopySharedPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kUserInfoImpl, kInCopySharedPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kSetUserNameCmdImpl, kInCopySharedPrefix + 82)
// gap
DECLARE_PMID(kImplementationIDSpace, kSetUserColorCmdImpl, kInCopySharedPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kDeletedTextPLComposerImpl, kInCopySharedPrefix + 85)
//gap
DECLARE_PMID(kImplementationIDSpace, kRedlinePreProcessDoAddTextCmdImpl, kInCopySharedPrefix + 89)
//gap
DECLARE_PMID(kImplementationIDSpace, kInCopyDeleteStoryThreadCmdImpl, kInCopySharedPrefix + 92)
DECLARE_PMID(kImplementationIDSpace, kSetUserColorsCmdImpl, kInCopySharedPrefix + 93)
DECLARE_PMID(kImplementationIDSpace, kSetUserColorsCmdDataImpl, kInCopySharedPrefix + 94)
DECLARE_PMID(kImplementationIDSpace, kStoryPropScriptProviderImpl, kInCopySharedPrefix + 95)
DECLARE_PMID(kImplementationIDSpace, kRedlineTextScriptProviderImpl, kInCopySharedPrefix + 96)
//DECLARE_PMID(kImplementationIDSpace, kSetShowInfoColumnCmdImpl,	kInCopySharedPrefix + 97)
DECLARE_PMID(kImplementationIDSpace, kImportSetDeleteOwnedItemCmdImpl, kInCopySharedPrefix + 99)
DECLARE_PMID(kImplementationIDSpace, kRedlinePreserveDeletionCmdImpl, kInCopySharedPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kRedlineDataStrandImpl, kInCopySharedPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kRedlineStrandImpl, kInCopySharedPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kRedlineAttrStrandImpl_Reuse, kInCopySharedPrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kRedlinePreProcessorImpl, kInCopySharedPrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kActivateRedlineCmdImpl, kInCopySharedPrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kDeactivateRedlineCmdImpl, kInCopySharedPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kSyncRedlineCmdImpl, kInCopySharedPrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kAcceptRedlineCmdImpl, kInCopySharedPrefix + 108)
DECLARE_PMID(kImplementationIDSpace, kRejectRedlineCmdImpl, kInCopySharedPrefix + 109)
DECLARE_PMID(kImplementationIDSpace, kRejectAllRedlineCmdImpl, kInCopySharedPrefix + 110)
DECLARE_PMID(kImplementationIDSpace, kRedlineChangeDataImpl, kInCopySharedPrefix + 111)
// gap 112-113
DECLARE_PMID(kImplementationIDSpace, kUnregisterRedlineStrandCmdImpl, kInCopySharedPrefix + 114)
// gap 115
DECLARE_PMID(kImplementationIDSpace, kPushRedlinePhaseCmdImpl, kInCopySharedPrefix + 116)
DECLARE_PMID(kImplementationIDSpace, kPopRedlinePhaseCmdImpl, kInCopySharedPrefix + 117)
DECLARE_PMID(kImplementationIDSpace, kAcceptAllRedlineCmdImpl, kInCopySharedPrefix + 118)
//DECLARE_PMID(kImplementationIDSpace, kRedlineConversionProviderImpl, kInCopySharedPrefix + 119)
// gap 120
DECLARE_PMID(kImplementationIDSpace, kRedlineStrandReplacePieceImpl, kInCopySharedPrefix + 121)
DECLARE_PMID(kImplementationIDSpace, kAcceptRangeRedlineCmdImpl, kInCopySharedPrefix + 122)
DECLARE_PMID(kImplementationIDSpace, kRejectRangeRedlineCmdImpl, kInCopySharedPrefix + 123)
DECLARE_PMID(kImplementationIDSpace, kMoveRedlineChangeCmdImpl, kInCopySharedPrefix + 124)
DECLARE_PMID(kImplementationIDSpace, kSetRedlineScrapDataCmdImpl, kInCopySharedPrefix + 125)
DECLARE_PMID(kImplementationIDSpace, kRedlineStrandPastePieceImpl, kInCopySharedPrefix + 126)
DECLARE_PMID(kImplementationIDSpace, kReplaceDeleteChangeDataCmdImpl, kInCopySharedPrefix + 127)
DECLARE_PMID(kImplementationIDSpace, kCollapseStateCmdImpl, kInCopySharedPrefix + 128)
DECLARE_PMID(kImplementationIDSpace, kSplitNoteCmdImpl, kInCopySharedPrefix + 129)
DECLARE_PMID(kImplementationIDSpace, kNoteModifiedTimeCmdImpl, kInCopySharedPrefix + 130)
DECLARE_PMID(kImplementationIDSpace, kAddNoteDataCmdImpl, kInCopySharedPrefix + 131)
DECLARE_PMID(kImplementationIDSpace, kCreateNoteCmdDataImpl, kInCopySharedPrefix + 132)
DECLARE_PMID(kImplementationIDSpace, kNoteCopyStoryCmdImpl, kInCopySharedPrefix + 133)
DECLARE_PMID(kImplementationIDSpace, kCreateNoteCmdImpl, kInCopySharedPrefix + 134)
DECLARE_PMID(kImplementationIDSpace, kAddNoteDataCmdDataImpl, kInCopySharedPrefix + 135)
DECLARE_PMID(kImplementationIDSpace, kConvertNoteHelperCmdImpl, kInCopySharedPrefix + 136)
DECLARE_PMID(kImplementationIDSpace, kDeleteNoteDataCmdImpl, kInCopySharedPrefix + 137)
//DECLARE_PMID(kImplementationIDSpace, kCopyToNewNoteCmdDataImpl, kInCopySharedPrefix + 138)	// unused
DECLARE_PMID(kImplementationIDSpace, kCopyNoteDataCmdDataImpl, kInCopySharedPrefix + 139)
DECLARE_PMID(kImplementationIDSpace, kConvertNoteToTextCmdImpl, kInCopySharedPrefix + 140)
DECLARE_PMID(kImplementationIDSpace, kCopyNoteDataCmdImpl, kInCopySharedPrefix + 141)
DECLARE_PMID(kImplementationIDSpace, kEditNoteAttributeCmdDataImpl, kInCopySharedPrefix + 142)
DECLARE_PMID(kImplementationIDSpace, kInCopySharedUtilsImpl, kInCopySharedPrefix + 143)


//note suite
DECLARE_PMID(kImplementationIDSpace, kNoteSuiteGalleyCSBImpl, 				kInCopySharedPrefix + 144)
DECLARE_PMID(kImplementationIDSpace, kNoteSuiteLayoutCSBImpl, 				kInCopySharedPrefix + 145)
DECLARE_PMID(kImplementationIDSpace, kNoteSuitePaletteCSBImpl, 				kInCopySharedPrefix + 146)
DECLARE_PMID(kImplementationIDSpace, kNoteSuiteASBImpl, 					kInCopySharedPrefix + 147)
DECLARE_PMID(kImplementationIDSpace, kConvertNoteToTextCmdDataImpl,			kInCopySharedPrefix + 148)
DECLARE_PMID(kImplementationIDSpace, kNoteSuiteUtilsImpl,					kInCopySharedPrefix + 149)

DECLARE_PMID(kImplementationIDSpace, kNoteFindChangeSpellingImpl,			kInCopySharedPrefix + 150)
//DECLARE_PMID(kImplementationIDSpace, kSetUserNoteColorCmdImpl,				kInCopySharedPrefix + 151)
DECLARE_PMID(kImplementationIDSpace, kInCopyRevertStoryCmdImpl,				kInCopySharedPrefix + 152)
DECLARE_PMID(kImplementationIDSpace, kInCopySaveStoryCmdImpl,				kInCopySharedPrefix + 153)
DECLARE_PMID(kImplementationIDSpace, kRedlinePhase2ConversionImpl,			kInCopySharedPrefix + 154)
DECLARE_PMID(kImplementationIDSpace, kTrackChangesPrefsCmdDataImpl,			kInCopySharedPrefix + 155)
DECLARE_PMID(kImplementationIDSpace, kSetTrackChangesPrefsCmdImpl,			kInCopySharedPrefix + 156)
DECLARE_PMID(kImplementationIDSpace, kInlineRefConverterImpl,				kInCopySharedPrefix + 157)
DECLARE_PMID(kImplementationIDSpace, kNoteScriptProviderImpl, 				kInCopySharedPrefix + 158)
DECLARE_PMID(kImplementationIDSpace, kAppPropScriptProviderImpl,			kInCopySharedPrefix + 159)
DECLARE_PMID(kImplementationIDSpace, kInCopyDocUserListScriptProviderImpl,	kInCopySharedPrefix + 160)
DECLARE_PMID(kImplementationIDSpace, kInCopyDocUserListScriptImpl,			kInCopySharedPrefix + 161)
DECLARE_PMID(kImplementationIDSpace, kNoteSettingsImpl,						kInCopySharedPrefix + 162)
DECLARE_PMID(kImplementationIDSpace, kSetHideNoteStateCmdImpl, 				kInCopySharedPrefix + 163)
DECLARE_PMID(kImplementationIDSpace, kSetNoteDataCmdImpl,					kInCopySharedPrefix + 164)
DECLARE_PMID(kImplementationIDSpace, kSetNoteDataCmdDataImpl,				kInCopySharedPrefix + 165)
DECLARE_PMID(kImplementationIDSpace, kStoryListFileImpl,					kInCopySharedPrefix + 166)
DECLARE_PMID(kImplementationIDSpace, kStoryListContentHandlerImpl,			kInCopySharedPrefix + 167)
DECLARE_PMID(kImplementationIDSpace, kOwnedItemUtilsImpl,					kInCopySharedPrefix + 168)

DECLARE_PMID(kImplementationIDSpace, kStoryOrderObserverImpl, 				kInCopySharedPrefix + 169)
DECLARE_PMID(kImplementationIDSpace, kGalleyTableDisplaySettingsImpl,		kInCopySharedPrefix + 170)

DECLARE_PMID(kImplementationIDSpace, kStoryUtilsImpl,						kInCopySharedPrefix + 171)
DECLARE_PMID(kImplementationIDSpace, kStoryViewTableFacadeImpl,				kInCopySharedPrefix + 172)
DECLARE_PMID(kImplementationIDSpace, kDeletedTextPhase2ConversionImpl,	kInCopySharedPrefix + 173)
DECLARE_PMID(kImplementationIDSpace, kStoryUpdateLinkServiceImpl,			kInCopySharedPrefix + 174)
DECLARE_PMID(kImplementationIDSpace, kUserInfoUtilsImpl,					kInCopySharedPrefix + 175)

/* PDF reivew notes
DECLARE_PMID(kImplementationIDSpace, kInsertNoteReviewImpl,							kInCopySharedPrefix + 206)
DECLARE_PMID(kImplementationIDSpace, kCommentNoteReviewImpl,						kInCopySharedPrefix + 207)
DECLARE_PMID(kImplementationIDSpace, kCrossoutNoteReviewImpl,						kInCopySharedPrefix + 208)
DECLARE_PMID(kImplementationIDSpace, kHighlightNoteReviewImpl,						kInCopySharedPrefix + 209)
DECLARE_PMID(kImplementationIDSpace, kUnderlineNoteReviewImpl,						kInCopySharedPrefix + 210)
DECLARE_PMID(kImplementationIDSpace, kReplaceNoteReviewImpl,						kInCopySharedPrefix + 211)
DECLARE_PMID(kImplementationIDSpace, kNoteMarkerImpl,								kInCopySharedPrefix + 212)
DECLARE_PMID(kImplementationIDSpace, kNoteEndMarkerOwnedItemImpl,					kInCopySharedPrefix + 213)
DECLARE_PMID(kImplementationIDSpace, kNoteEndMarkerOwnedItemMementoImpl,			kInCopySharedPrefix + 214)
DECLARE_PMID(kImplementationIDSpace, kNoteEndMarkerScrapImpl,			kInCopySharedPrefix + 215)
DECLARE_PMID(kImplementationIDSpace, kChangeNoteMarkerCmdImpl,			kInCopySharedPrefix + 216)
DECLARE_PMID(kImplementationIDSpace, kChangeNoteMarkerCmdDataImpl,			kInCopySharedPrefix + 217)
*/

// <other #defines>
//---------------------------------------------------------------
//	other #defines
//---------------------------------------------------------------
#define kInCopySharedStringsRsrcID				3000
#define kInCopySharedErrorStringsRsrcID			4000

// <Error ID's>
//---------------------------------------------------------------
//	Error ID's
//---------------------------------------------------------------
DECLARE_PMID(kErrorIDSpace, kICMissingStoryError, kInCopySharedPrefix + 1)	// story missing on update design
DECLARE_PMID(kErrorIDSpace, kICUnableToConvertError, kInCopySharedPrefix + 2)	// unable to convert document to standalone
DECLARE_PMID(kErrorIDSpace, kICBadStoryError, kInCopySharedPrefix + 3)	// bad story on update design
DECLARE_PMID(kErrorIDSpace, kICInCompatibleFileError, kInCopySharedPrefix + 4)	// trying to open wrong file type
DECLARE_PMID(kErrorIDSpace, kICMissingFileError, kInCopySharedPrefix + 5)	// trying to open a missing file
DECLARE_PMID(kErrorIDSpace, kObjectCreationLocationError, kInCopySharedPrefix + 6) // trying to insert an object at a bad incompatible location
DECLARE_PMID(kErrorIDSpace, kCantFindPrefsError, kInCopySharedPrefix + 7) // preferences asked for are not available
DECLARE_PMID(kErrorIDSpace, kNoTargetOrTextModel, kInCopySharedPrefix + 8) // No valid text target or text model to perform operation
DECLARE_PMID(kErrorIDSpace, kInvalidUserNameError, kInCopySharedPrefix + 9) // Trying to set invalid user name
DECLARE_PMID(kErrorIDSpace, kICCheckoutError, kInCopySharedPrefix + 10) // Unable to checkout (as during undo/redo)
DECLARE_PMID(kErrorIDSpace, kObjectNotEditableInCopyError, kInCopySharedPrefix + 11)
DECLARE_PMID(kErrorIDSpace, kICCheckOutINCDError, kInCopySharedPrefix + 12) // CS4 doesn't allow check out since INCD export is removed
DECLARE_PMID(kErrorIDSpace, kLockedInCopyStoryError, kInCopySharedPrefix + 13)	// try to update locked story
DECLARE_PMID(kErrorIDSpace, kNotAInCopyStoryError, kInCopySharedPrefix + 14)	// try to update a non incopy story
DECLARE_PMID(kErrorIDSpace, kNoteXMLPartialHyperlinkError, kInCopySharedPrefix + 15)	// try to update a non incopy story

// <Message ID>
//---------------------------------------------------------------
//	MessageIDs
//---------------------------------------------------------------

DECLARE_PMID(kMessageIDSpace,	kAcceptAllChangesMsgID,				kInCopySharedPrefix + 0)
DECLARE_PMID(kMessageIDSpace,	kAcceptAllSomeHiddenChangesMsgID,	kInCopySharedPrefix + 1)
DECLARE_PMID(kMessageIDSpace,	kRejectAllChangesMsgID,				kInCopySharedPrefix + 2)
DECLARE_PMID(kMessageIDSpace,	kRejectAllSomeHiddenChangesMsgID,	kInCopySharedPrefix + 3)
DECLARE_PMID(kMessageIDSpace,	kEnableTrackChangesMsg,				kInCopySharedPrefix + 4)
DECLARE_PMID(kMessageIDSpace,	kDisableTrackChangesMsg,			kInCopySharedPrefix + 5)
DECLARE_PMID(kMessageIDSpace, 	kCollapseTableMsg, 					kInCopySharedPrefix + 6)
DECLARE_PMID(kMessageIDSpace,	kTableDisplayOrderMsg, 				kInCopySharedPrefix + 7)
DECLARE_PMID(kMessageIDSpace,	kAcceptAllDocChangesMsgID, 				kInCopySharedPrefix + 8)
DECLARE_PMID(kMessageIDSpace,	kAcceptAllDocSomeHiddenChangesMsgID, 				kInCopySharedPrefix + 9)
DECLARE_PMID(kMessageIDSpace,	kRejectAllDocChangesMsgID, 				kInCopySharedPrefix + 10)
DECLARE_PMID(kMessageIDSpace,	kRejectAllDocSomeHiddenChangesMsgID, 				kInCopySharedPrefix + 11)

//----------------------------------------------------------------------------------------
// Service Provider IDs
//----------------------------------------------------------------------------------------

DECLARE_PMID(kServiceIDSpace,	kSetUserNameCmdResponderService,	kInCopySharedPrefix + 1)

// <Widget ID>
//----------------------------------------------------------------------------------------
// Widget identifiers
//----------------------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////////
//Script Element IDs
//////////////////////////////////////////////////////////////////////////////

//Types

//Suites
// DECLARE_PMID(kScriptInfoIDSpace, kYourNewSuiteScriptElement,					kInCopySharedPrefix + 1)

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kChangeObjectScriptElement,				kInCopySharedPrefix + 40)
DECLARE_PMID(kScriptInfoIDSpace, kInCopyDocUserObjectScriptElement,			kInCopySharedPrefix + 41)
DECLARE_PMID(kScriptInfoIDSpace, kINCXExportOptionsScriptElement,			kInCopySharedPrefix + 42)
// DECLARE_PMID(kScriptInfoIDSpace, kYourNewObjectScriptElement,			kInCopySharedPrefix + 43)

//Events
DECLARE_PMID(kScriptInfoIDSpace, kAcceptMethodScriptElement,					kInCopySharedPrefix + 80)
DECLARE_PMID(kScriptInfoIDSpace, kRejectMethodScriptElement,					kInCopySharedPrefix + 81)
// DECLARE_PMID(kScriptInfoIDSpace, kYourNewMethodScriptElement,				kInCopySharedPrefix + 82)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kTrackChangesPropertyScriptElement,			kInCopySharedPrefix + 140)
DECLARE_PMID(kScriptInfoIDSpace, kChangeDatePropertyScriptElement,				kInCopySharedPrefix + 141)
DECLARE_PMID(kScriptInfoIDSpace, kKindPropertyScriptElement,					kInCopySharedPrefix + 142)
DECLARE_PMID(kScriptInfoIDSpace, kChangeUserNamePropertyScriptElement,			kInCopySharedPrefix + 143)
DECLARE_PMID(kScriptInfoIDSpace, kChangeStoryOffsetPropertyScriptElement,		kInCopySharedPrefix + 144)
DECLARE_PMID(kScriptInfoIDSpace, kDocUserPropertyScriptElement,					kInCopySharedPrefix + 145)
DECLARE_PMID(kScriptInfoIDSpace, kStoryLabelPropertyScriptElement,				kInCopySharedPrefix + 146)
DECLARE_PMID(kScriptInfoIDSpace, kINCXExportOptionsPropertyScriptElement,		kInCopySharedPrefix + 147)
DECLARE_PMID(kScriptInfoIDSpace, kIncludeGraphicProxyDataPropertyScriptElement,	kInCopySharedPrefix + 148)
DECLARE_PMID(kScriptInfoIDSpace, kStoryTitlePropertyScriptElement,				kInCopySharedPrefix + 149)
DECLARE_PMID(kScriptInfoIDSpace, kIncludeAllResourcesPropertyScriptElement,		kInCopySharedPrefix + 150)
//DECLARE_PMID(kScriptInfoIDSpace, kYourNewPropertyScriptElement,				kInCopySharedPrefix + 151)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kChangeKindsEnumScriptElement,	kInCopySharedPrefix + 220)
// DECLARE_PMID(kScriptInfoIDSpace, kYourNewEnumScriptElement,	kInCopySharedPrefix + 221)

//TypeDefs
DECLARE_PMID(kScriptInfoIDSpace, kInCopyUIColorTypeDefScriptElement, kInCopySharedPrefix + 240)

enum InCopySharedScriptIDs
{
	t_ICUIColorType		= 'ICCT'
} ;

//GUIDs
// {9F322FF0-F874-449e-96C4-6DAA3E28BC76}
#define kChange_CLSID { 0x9f322ff0, 0xf874, 0x449e, { 0x96, 0xc4, 0x6d, 0xaa, 0x3e, 0x28, 0xbc, 0x76 } }
// {00F63BE3-9801-484b-9A32-173EA0EA56AA}
#define kChanges_CLSID { 0xf63be3, 0x9801, 0x484b, { 0x9a, 0x32, 0x17, 0x3e, 0xa0, 0xea, 0x56, 0xaa } }
// {8211CF33-6E6F-46f3-9A36-92834C138F2C}
#define kInCopyDocUser_CLSID { 0x8211cf33, 0x6e6f, 0x46f3, { 0x9a, 0x36, 0x92, 0x83, 0x4c, 0x13, 0x8f, 0x2c } }
// {CF67E40A-0CF5-4e42-95AF-BF1907E3C65B}
#define kInCopyDocUsers_CLSID { 0xcf67e40a, 0xcf5, 0x4e42, { 0x95, 0xaf, 0xbf, 0x19, 0x7, 0xe3, 0xc6, 0x5b } }
// {831D8700-1452-4bbd-8428-D8EA81029028}
#define kICExportPref_CLSID { 0x831d8700, 0x1452, 0x4bbd, { 0x84, 0x28, 0xd8, 0xea, 0x81, 0x2, 0x90, 0x28 } }
// {69F6966D-6716-4b06-8C6D-6344B7182886}
#define kINCXExportOptions_CLSID { 0x69F6966D, 0x6716, 0x4b06, { 0x8C, 0x6D, 0x63, 0x44, 0xB7, 0x18, 0x28, 0x86 } }

#endif // __INCOPYSHAREDID__



