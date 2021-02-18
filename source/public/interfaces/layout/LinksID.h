//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/LinksID.h $
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
//========================================================================================

#ifndef __LinksIID__
#define __LinksIID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kLinksPrefix	RezLong(0x8c00)
#define kLinksPrefix2	RezLong(0x23100)

// <Start IDC>
#define kLinksPluginName		 			"Links"
DECLARE_PMID(kPlugInIDSpace, kLinksPluginID, kLinksPrefix + 1)

// <Class ID>
DECLARE_PMID(kClassIDSpace, kDataLinkBoss, kLinksPrefix + 1)
//gap
DECLARE_PMID(kClassIDSpace, kRemoveLinksCmdBoss, kLinksPrefix + 3)
DECLARE_PMID(kClassIDSpace, kSetFlagsCmdBoss, kLinksPrefix + 4)
//gap
DECLARE_PMID(kClassIDSpace, kLinkPrefsScriptProviderBoss, kLinksPrefix + 6)
//gap
DECLARE_PMID(kClassIDSpace, kDataLinkHelperBoss, kLinksPrefix + 10)
DECLARE_PMID(kClassIDSpace, kCoreFilenameBoss, kLinksPrefix + 11)
DECLARE_PMID(kClassIDSpace, kRestoreLinkCmdBoss, kLinksPrefix + 12)
DECLARE_PMID(kClassIDSpace, kMultiLinkBoss, kLinksPrefix + 13)
DECLARE_PMID(kClassIDSpace, kDataLinkRefConverterBoss, kLinksPrefix + 14)
//gap
DECLARE_PMID(kClassIDSpace, kMultiLinkPlaceProviderBoss, kLinksPrefix + 17)
DECLARE_PMID(kClassIDSpace, kMultiLinkStreamReadBoss, kLinksPrefix + 18)
DECLARE_PMID(kClassIDSpace, kCoreFilenameUtilsBoss, kLinksPrefix + 19)
DECLARE_PMID(kClassIDSpace, kAddLinkCmdBoss, kLinksPrefix + 20)
DECLARE_PMID(kClassIDSpace, kLinksErrorStringServiceBoss, kLinksPrefix + 21)
DECLARE_PMID(kClassIDSpace, kXMLLinkObjectReferenceBoss, kLinksPrefix + 22)
DECLARE_PMID(kClassIDSpace, kAddEmbedCmdBoss, kLinksPrefix + 23)
DECLARE_PMID(kClassIDSpace, kMultiLinkRefConverterBoss, kLinksPrefix + 24)
DECLARE_PMID(kClassIDSpace, kAddExtraLinkCmdBoss, kLinksPrefix + 26)
DECLARE_PMID(kClassIDSpace, kRemoveInternalCmdBoss, kLinksPrefix + 27)
DECLARE_PMID(kClassIDSpace, kPlaceDialogPrefsCmdBoss, kLinksPrefix + 28)
DECLARE_PMID(kClassIDSpace, kRemoveEmbedCmdBoss, kLinksPrefix + 29)
DECLARE_PMID(kClassIDSpace, kLinkScriptDocumentResponderServiceBoss, kLinksPrefix + 30)
DECLARE_PMID(kClassIDSpace, kLinksPhase2ConversionBoss, kLinksPrefix + 31)
DECLARE_PMID(kClassIDSpace, kIndexTOCDataBoss, kLinksPrefix + 32)
DECLARE_PMID(kClassIDSpace, kLinksChangedSignalMgrBoss, kLinksPrefix + 33)
DECLARE_PMID(kClassIDSpace, kWorkflowDataLinkBoss, kLinksPrefix + 34)
DECLARE_PMID(kClassIDSpace, kLinkCmdSignalMgrBoss, kLinksPrefix + 35)
DECLARE_PMID(kClassIDSpace, kNewDataLinkCmdBoss, kLinksPrefix + 36)
DECLARE_PMID(kClassIDSpace, kLinksIteratorRegBoss, kLinksPrefix + 37)
DECLARE_PMID(kClassIDSpace, kLinksConversionProviderBoss, kLinksPrefix + 38)
DECLARE_PMID(kClassIDSpace, kXMLImportLinkBoss, kLinksPrefix + 39)
DECLARE_PMID(kClassIDSpace, kLinkScriptEventResponderServiceBoss, kLinksPrefix + 40)
DECLARE_PMID(kClassIDSpace, kLinksCodeConversionProviderBoss, kLinksPrefix + 41)
DECLARE_PMID(kClassIDSpace, kLinkScriptProviderBoss, kLinksPrefix + 42)
DECLARE_PMID(kClassIDSpace, kItemLinkScriptProviderBoss, kLinksPrefix + 43)
DECLARE_PMID(kClassIDSpace, kXMLDataLinkBoss, kLinksPrefix + 44)
DECLARE_PMID(kClassIDSpace, kWorkflowXMLDataLinkBoss, kLinksPrefix + 45)
DECLARE_PMID(kClassIDSpace, kHttpLinkConnectionManagerScriptProviderBoss, kLinksPrefix + 46)
DECLARE_PMID(kClassIDSpace, kLinkInfoInstanceNameProviderBoss, kLinksPrefix + 47)

//gap
DECLARE_PMID(kClassIDSpace, kSPPlaceHolderPageItemBoss, kLinksPrefix + 52)
DECLARE_PMID(kClassIDSpace, kSPDeletePlaceHolderCmdBoss, kLinksPrefix + 53)
//gap
DECLARE_PMID(kClassIDSpace, kMissingLinkBoss, kLinksPrefix + 56)
//gap
DECLARE_PMID(kClassIDSpace, kPageItemUpdateLinkServiceProviderBoss, kLinksPrefix + 58)
DECLARE_PMID(kClassIDSpace, kMissingLinksOpenDocResponderBoss, kLinksPrefix + 59)

//gap
DECLARE_PMID(kClassIDSpace, kFixupConvertDataLinkCmdBoss, kLinksPrefix + 61)
DECLARE_PMID(kClassIDSpace, kMissingLinksINXImportResponderBoss, kLinksPrefix + 62)

// new link architecture
DECLARE_PMID(kClassIDSpace, kLinksStartupShutdownBoss, kLinksPrefix + 63)
DECLARE_PMID(kClassIDSpace, kLinkResourceFindMissingCmdBoss, kLinksPrefix + 64)
DECLARE_PMID(kClassIDSpace, kLinkResourceBoss, kLinksPrefix + 65)
DECLARE_PMID(kClassIDSpace, kImportLinkBoss, kLinksPrefix + 66)
DECLARE_PMID(kClassIDSpace, kExportLinkBoss, kLinksPrefix + 67)
DECLARE_PMID(kClassIDSpace, kBidirectionalLinkBoss, kLinksPrefix + 68)
DECLARE_PMID(kClassIDSpace, kChildLinkBoss, kLinksPrefix + 69)
DECLARE_PMID(kClassIDSpace, kINXImportedLinkBoss, kLinksPrefix + 70)
DECLARE_PMID(kClassIDSpace, kDefaultLinkResourceHandlerBoss, kLinksPrefix + 71)
DECLARE_PMID(kClassIDSpace, kDefaultLinkResourceProviderBoss, kLinksPrefix + 72)
DECLARE_PMID(kClassIDSpace, kFileLinkResourceHandlerBoss, kLinksPrefix + 73)
DECLARE_PMID(kClassIDSpace, kFileLinkResourceProviderBoss, kLinksPrefix + 74)
DECLARE_PMID(kClassIDSpace, kLinkManagerDBPagedSetStorageBoss, kLinksPrefix + 75)
DECLARE_PMID(kClassIDSpace, kLinksNewDocResponderBoss, kLinksPrefix + 76)
DECLARE_PMID(kClassIDSpace, kLinksOpenDocResponderBoss, kLinksPrefix + 77)
DECLARE_PMID(kClassIDSpace, kLinksCloseDocResponderBoss, kLinksPrefix + 78)
DECLARE_PMID(kClassIDSpace, kLinkResourceCreateCmdBoss, kLinksPrefix + 79)
DECLARE_PMID(kClassIDSpace, kLinkResourceDeleteCmdBoss, kLinksPrefix + 80)
DECLARE_PMID(kClassIDSpace, kLinkResourceStateUpdateCmdBoss, kLinksPrefix + 81)
DECLARE_PMID(kClassIDSpace, kLinkResourceUndoRedoStateUpdateCmdBoss, kLinksPrefix + 82)
DECLARE_PMID(kClassIDSpace, kLinkAttachCmdBoss, kLinksPrefix + 83)
DECLARE_PMID(kClassIDSpace, kLinkCreateCmdBoss, kLinksPrefix + 84)
DECLARE_PMID(kClassIDSpace, kLinkDeleteCmdBoss, kLinksPrefix + 85)
DECLARE_PMID(kClassIDSpace, kLinkEmbedCmdBoss, kLinksPrefix + 86)
DECLARE_PMID(kClassIDSpace, kLinkUnembedCmdBoss, kLinksPrefix + 87)
//gap
DECLARE_PMID(kClassIDSpace, kLinkUpdateCmdBoss, kLinksPrefix + 89)
DECLARE_PMID(kClassIDSpace, kLinkCopyToFolderCmdBoss, kLinksPrefix + 90)
DECLARE_PMID(kClassIDSpace, kCopyLinkToLinkObjectCmdBoss, kLinksPrefix + 91)
DECLARE_PMID(kClassIDSpace, kLinkReferenceConverterBoss, kLinksPrefix + 92)
DECLARE_PMID(kClassIDSpace, kFixupConvertLinkCmdBoss, kLinksPrefix + 93)
DECLARE_PMID(kClassIDSpace, kLinkModelChangeStart, kLinksPrefix + 94)
DECLARE_PMID(kClassIDSpace, kLinkModelChangeEnd, kLinksPrefix + 95)
DECLARE_PMID(kClassIDSpace, kLinkModelChangeAbort, kLinksPrefix + 96)
DECLARE_PMID(kClassIDSpace, kLinkUpdateStateCmdBoss, kLinksPrefix + 97)
DECLARE_PMID(kClassIDSpace, kLinkRelinkToFolderCmdBoss, kLinksPrefix + 98)
DECLARE_PMID(kClassIDSpace, kLinkPrefsCmdBoss, kLinksPrefix + 99)
DECLARE_PMID(kClassIDSpace, kLinkInfoNameProviderBoss, kLinksPrefix + 100)
DECLARE_PMID(kClassIDSpace, kLinkInfoFormatTypeProviderBoss, kLinksPrefix + 101)
DECLARE_PMID(kClassIDSpace, kLinkInfoPageNumberProviderBoss, kLinksPrefix + 102)
DECLARE_PMID(kClassIDSpace, kLinkInfoColorSpaceProviderBoss, kLinksPrefix + 103)
DECLARE_PMID(kClassIDSpace, kLinkInfoStatusProviderBoss, kLinksPrefix + 104)
DECLARE_PMID(kClassIDSpace, kLinkInfoSizeProviderBoss, kLinksPrefix + 105)
DECLARE_PMID(kClassIDSpace, kScrapLinkManagerDBPagedSetStorageBoss, kLinksPrefix + 106)
DECLARE_PMID(kClassIDSpace, kLinkResourceReferenceConverterBoss, kLinksPrefix + 107)
DECLARE_PMID(kClassIDSpace, kLinkRelinkExtensionCmdBoss, kLinksPrefix + 108)
DECLARE_PMID(kClassIDSpace, kLinkInfoColorProfileProviderBoss, kLinksPrefix + 109)
DECLARE_PMID(kClassIDSpace, kLinkInfoLayerOverrideProviderBoss, kLinksPrefix + 110)
DECLARE_PMID(kClassIDSpace, kLinkInfoLinkTypeProviderBoss, kLinksPrefix + 111)
DECLARE_PMID(kClassIDSpace, kLinkInfoPPIProviderBoss, kLinksPrefix + 112)
DECLARE_PMID(kClassIDSpace, kLinkInfoEffectivePPIProviderBoss, kLinksPrefix + 113)
DECLARE_PMID(kClassIDSpace, kLinkInfoPixelSizeProviderBoss, kLinksPrefix + 114)
DECLARE_PMID(kClassIDSpace, kLinkInfoXMPAuthorProviderBoss, kLinksPrefix + 115)
DECLARE_PMID(kClassIDSpace, kLinkInfoXMPTitleProviderBoss, kLinksPrefix + 116)
DECLARE_PMID(kClassIDSpace, kLinkInfoXMPCreatorToolProviderBoss, kLinksPrefix + 117)
DECLARE_PMID(kClassIDSpace, kLinkInfoPlaceDateProviderBoss, kLinksPrefix + 118)
DECLARE_PMID(kClassIDSpace, kLinkInfoLayerNameProviderBoss, kLinksPrefix + 119)
DECLARE_PMID(kClassIDSpace, kLinkInfoXMPCopyrightProviderBoss, kLinksPrefix + 120)
DECLARE_PMID(kClassIDSpace, kLinkInfoModDateProviderBoss, kLinksPrefix + 121)
DECLARE_PMID(kClassIDSpace, kLinkInfoFullPathProviderBoss, kLinksPrefix + 122)
DECLARE_PMID(kClassIDSpace, kLinkInfoChildLinksProviderBoss, kLinksPrefix + 123)
DECLARE_PMID(kClassIDSpace, kLinkInfoXMPCreateDateProviderBoss, kLinksPrefix + 124)
DECLARE_PMID(kClassIDSpace, kLinkInfoScaleProviderBoss, kLinksPrefix + 125)
DECLARE_PMID(kClassIDSpace, kLinkInfoTransparencyProviderBoss, kLinksPrefix + 126)
DECLARE_PMID(kClassIDSpace, kLinkInfoSkewProviderBoss, kLinksPrefix + 127)
DECLARE_PMID(kClassIDSpace, kLinkInfoRotationProviderBoss, kLinksPrefix + 128)
DECLARE_PMID(kClassIDSpace, kAemStartupShutdownBoss, kLinksPrefix + 129)
//gap
DECLARE_PMID(kClassIDSpace, kDefaultNewLinkConverterBoss, kLinksPrefix + 131)
//gap
DECLARE_PMID(kClassIDSpace, kLinkInfoFolder0ProviderBoss, kLinksPrefix + 135)
DECLARE_PMID(kClassIDSpace, kLinkInfoFolder1ProviderBoss, kLinksPrefix + 136)
DECLARE_PMID(kClassIDSpace, kLinkInfoFolder2ProviderBoss, kLinksPrefix + 137)
DECLARE_PMID(kClassIDSpace, kLinkInfoFolder3ProviderBoss, kLinksPrefix + 138)
DECLARE_PMID(kClassIDSpace, kLinkInfoFolder4ProviderBoss, kLinksPrefix + 139)
DECLARE_PMID(kClassIDSpace, kLinkInfoFolder5ProviderBoss, kLinksPrefix + 140)
DECLARE_PMID(kClassIDSpace, kLinkInfoFolder6ProviderBoss, kLinksPrefix + 141)
DECLARE_PMID(kClassIDSpace, kLinkInfoFolder7ProviderBoss, kLinksPrefix + 142)
DECLARE_PMID(kClassIDSpace, kLinkInfoFolder8ProviderBoss, kLinksPrefix + 143)
DECLARE_PMID(kClassIDSpace, kLinkInfoVolumeNameProviderBoss, kLinksPrefix + 144)
DECLARE_PMID(kClassIDSpace, kLinkInfoStoryModifiedProviderBoss, kLinksPrefix + 145)
DECLARE_PMID(kClassIDSpace, kLinkDispatchScriptEventCmdBoss, kLinksPrefix + 146)
DECLARE_PMID(kClassIDSpace, kLinkResourceOpenDocResponderBoss, kLinksPrefix  + 147)
DECLARE_PMID(kClassIDSpace, kLinkResourceNewDocResponderBoss, kLinksPrefix  + 148)
DECLARE_PMID(kClassIDSpace, kLinkInfoStoryNoteCountProviderBoss, kLinksPrefix  + 149)
DECLARE_PMID(kClassIDSpace, kLinkInfoStoryTrackChangesProviderBoss, kLinksPrefix  + 150)
DECLARE_PMID(kClassIDSpace, kLinkInfoStoryLabelProviderBoss, kLinksPrefix  + 151)
DECLARE_PMID(kClassIDSpace, kLinkInfoStoryAssignmentProviderBoss, kLinksPrefix  + 152)
DECLARE_PMID(kClassIDSpace, kLinkInfoStoryAssignedToProviderBoss, kLinksPrefix  + 153)
DECLARE_PMID(kClassIDSpace, kLinkM2MListenerServiceBoss, kLinksPrefix  + 154)
DECLARE_PMID(kClassIDSpace, kLinkObjectPIM2MListenerServiceBoss, kLinksPrefix  + 155)
DECLARE_PMID(kClassIDSpace, kSetLinkCaptionPrefsCmdBoss, kLinksPrefix + 156) 
DECLARE_PMID(kClassIDSpace, kGenerateLinkCaptionCmdBoss, kLinksPrefix + 157) 
DECLARE_PMID(kClassIDSpace, kCaptionPrefsNewDocResponderBoss, kLinksPrefix + 158)
DECLARE_PMID(kClassIDSpace, kLinkUpdateRecursivelyCmdBoss, kLinksPrefix + 159)
DECLARE_PMID(kClassIDSpace, kLinkObjectAfterAddEmbedResponderBoss, kLinksPrefix  + 160)
DECLARE_PMID(kClassIDSpace, kLinkObjectAfterRemoveEmbedResponderBoss, kLinksPrefix  + 161)
DECLARE_PMID(kClassIDSpace, kObsoleteBuzzwordLinkResourceProviderBoss, kLinksPrefix  + 162)
DECLARE_PMID(kClassIDSpace, kObsoleteBuzzwordLinkResourceHandlerBoss, kLinksPrefix  + 163)
DECLARE_PMID(kClassIDSpace, kCloudAssetLinkResourceHandlerBoss, kLinksPrefix + 164)
DECLARE_PMID(kClassIDSpace, kCloudAssetLinkResourceProviderBoss, kLinksPrefix + 165)
DECLARE_PMID(kClassIDSpace, kCCLibrariesAccessorStartupShutdownBoss, kLinksPrefix + 166)
DECLARE_PMID(kClassIDSpace, kAutoRelinkCloudAssetLinkCmdBoss, kLinksPrefix + 167)
DECLARE_PMID(kClassIDSpace, kUpdateLinkWithNoHistoryCmdBoss, kLinksPrefix + 168)
DECLARE_PMID(kClassIDSpace, kExternalActionIdleTaskBoss, kLinksPrefix + 169)
DECLARE_PMID(kClassIDSpace, kCloudTextLinkBoss, kLinksPrefix + 170)
DECLARE_PMID(kClassIDSpace, kCloudTextUpdateLinkServiceProviderBoss, kLinksPrefix + 171)
DECLARE_PMID(kClassIDSpace, kHTTPAssetLinkResourceHandlerBoss, kLinksPrefix + 172)
DECLARE_PMID(kClassIDSpace, kHTTPAssetLinkResourceProviderBoss, kLinksPrefix + 173)
DECLARE_PMID(kClassIDSpace, kHTTPAssetLinkResourceHelperBoss, kLinksPrefix + 174)
DECLARE_PMID(kClassIDSpace, kHTTPLinkSubsystemObjectProviderBoss, kLinksPrefix + 175)
DECLARE_PMID(kClassIDSpace, kHTTPAssetLinkResourceServerHelperBoss, kLinksPrefix + 176)
DECLARE_PMID(kClassIDSpace, kHTTPAssetLinkResourceStateUpdaterBoss, kLinksPrefix + 177)
DECLARE_PMID(kClassIDSpace, kLinkResourceSetRenditionDataCmdBoss, kLinksPrefix + 178)
DECLARE_PMID(kClassIDSpace, kMissingLinksAfterOpenDocResponderBoss, kLinksPrefix + 179)
DECLARE_PMID(kClassIDSpace, kTextFragmentLinkServiceProviderBoss, kLinksPrefix + 180)
DECLARE_PMID(kClassIDSpace, kSetHTTPLinksRenditionDataCmdBoss, kLinksPrefix + 181)
DECLARE_PMID(kClassIDSpace, kSetHTTPLinksAutoTagAssetsPrefCmdBoss, kLinksPrefix + 182)
DECLARE_PMID(kClassIDSpace, kLinkResourceResetURICmdBoss, kLinksPrefix + 183)
DECLARE_PMID(kClassIDSpace, kAEMMetadataLinkObjectReferenceBoss_obsolete, kLinksPrefix + 185)
DECLARE_PMID(kClassIDSpace, kTextFragmentLinkObjectReferenceBoss, kLinksPrefix + 186)

//AEM
DECLARE_PMID(kClassIDSpace, kAEMLinkSubsystemObjectProviderBoss, kLinksPrefix + 187)
DECLARE_PMID(kClassIDSpace, kAEMAssetLinkResourceHelperBoss, kLinksPrefix + 188)
DECLARE_PMID(kClassIDSpace, kAEMAssetLinkResourceHandlerBoss, kLinksPrefix + 189)
DECLARE_PMID(kClassIDSpace, kAEMAssetLinkResourceStateUpdaterBoss, kLinksPrefix + 190)
DECLARE_PMID(kClassIDSpace, kAEMAssetLinkResourceServerHelperBoss, kLinksPrefix + 191)
DECLARE_PMID(kClassIDSpace, kUserSigninStatusWchResponderServiceBoss, kLinksPrefix + 192)
DECLARE_PMID(kClassIDSpace, kScrapDBLinksStartupShutdownBoss, kLinksPrefix + 193)




// <Implementation ID>
DECLARE_PMID(kImplementationIDSpace, kLinksManagerImpl, kLinksPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kLinksPrefsScriptProviderImpl, kLinksPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kDirListImpl, kLinksPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kDataLinkImpl, kLinksPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kDataLinkServiceImpl, kLinksPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kTestDataFilenameImpl, kLinksPrefix + 6)
// gap
DECLARE_PMID(kImplementationIDSpace, kSetHTTPLinksRenditionDataCmdImpl, kLinksPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kSetLinkCaptionPrefsCmdImpl, kLinksPrefix + 10) 
DECLARE_PMID(kImplementationIDSpace, kGenerateLinkCaptionCmdImpl, kLinksPrefix + 11) 
DECLARE_PMID(kImplementationIDSpace, kRemoveLinksCmdImpl, kLinksPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kSetFlagsCmdImpl, kLinksPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kSetFlagsCmdDataImpl, kLinksPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kGenerateCaptionCmdDataImpl, kLinksPrefix + 15) 
DECLARE_PMID(kImplementationIDSpace, kCaptionPrefsNewDocResponderImpl, kLinksPrefix + 16)  
DECLARE_PMID(kImplementationIDSpace, kLinkM2MListenerImpl, kLinksPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kMultiLinkRefConverterImpl, kLinksPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kLinkObjectPIM2MListenerImpl, kLinksPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kLinkCaptionPrefsImpl, kLinksPrefix + 20) 
DECLARE_PMID(kImplementationIDSpace, kDataLinkHelperImpl, kLinksPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kCoreFilenameImpl, kLinksPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kRestoreLinkCmdImpl, kLinksPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kRestoreLinkCmdDataImpl, kLinksPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kMultiLinkImpl, kLinksPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kIndexTOCReferencesImpl, kLinksPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kDataLinkReferenceImpl, kLinksPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kDataLinkRefConverterImpl, kLinksPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kDataLinkListReferenceImpl, kLinksPrefix + 29)
//gap
DECLARE_PMID(kImplementationIDSpace, kStoreInternalImpl, kLinksPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kLinkStateImpl, kLinksPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kMultiLinkImportProviderImpl, kLinksPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kMultiLinkPlaceServiceImpl, kLinksPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kMultiLinkStreamImpl, kLinksPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kLinkedStreamImpl, kLinksPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kMultiLinkStreamReadImpl, kLinksPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kPageItemLinkObjctReferenceImpl, kLinksPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kCoreFilenameUtilsImpl, kLinksPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kFormatTypeImpl, kLinksPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kAddLinkCmdImpl, kLinksPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kDataLinkFormatTypeImpl, kLinksPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kAddLinkCmdDataImpl, kLinksPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kShowPageItemUtilsImpl, kLinksPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kLinkScriptObserverImpl, kLinksPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kXMLLinkObjectReferenceImpl, kLinksPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kDataLinkReferenceDebugImpl, kLinksPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kLinksErrorStringServiceImpl, kLinksPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kAddEmbedCmdImpl, kLinksPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kDataLinkConvertProviderImpl, kLinksPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kAddExtraLinkCmdImpl, kLinksPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kRemoveInternalCmdImpl, kLinksPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kPlaceDialogPrefsImpl, kLinksPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kPlaceDialogPrefsCmdImpl, kLinksPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kPlaceDialogPrefsCmdDataImpl, kLinksPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kRemoveEmbedCmdImpl, kLinksPrefix + 60)
//gap
DECLARE_PMID(kImplementationIDSpace, kLinksPhase2ConversionImpl, kLinksPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kLinksManagerSortedImpl, kLinksPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kTOCIndexDataRefImpl, kLinksPrefix + 64) // was kGenericDataLinkRefsImpl
DECLARE_PMID(kImplementationIDSpace, kLinksChangedSignalServiceImpl, kLinksPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kWFDataLinkAnnexImpl, kLinksPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kLinkCmdSignalDataImpl, kLinksPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kWFDataLinkImpl, kLinksPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kNewDataLinkCmdImpl, kLinksPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kBeforeAddLinkSignalRespServiceImpl, kLinksPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kAfterAddLinkSignalRespServiceImpl, kLinksPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kLinkScriptEventServiceProviderImpl, kLinksPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kLinkScriptEventResponderImpl, kLinksPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kLinkScriptDocumentServiceProviderImpl, kLinksPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kLinkScriptDocumentResponderImpl, kLinksPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kBeforeAddExtraLinkSignalRespServiceImpl, kLinksPrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kAfterAddExtraLinkSignalRespServiceImpl, kLinksPrefix + 77)
//gap
DECLARE_PMID(kImplementationIDSpace, kBeforeAttachDataLinkSignalRespServiceImpl, kLinksPrefix + 79)
DECLARE_PMID(kImplementationIDSpace, kAfterAttachDataLinkSignalRespServiceImpl, kLinksPrefix + 80)
//gap
DECLARE_PMID(kImplementationIDSpace, kBeforeRemoveLinksSignalRespServiceImpl, kLinksPrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kAfterRemoveLinksSignalRespServiceImpl, kLinksPrefix + 89)
//gap
DECLARE_PMID(kImplementationIDSpace, kBeforeRestoreLinkSignalRespServiceImpl, kLinksPrefix + 91)
DECLARE_PMID(kImplementationIDSpace, kAfterRestoreLinkSignalRespServiceImpl, kLinksPrefix + 92)
//gap
DECLARE_PMID(kImplementationIDSpace, kBeforeUpdateLinkSignalRespServiceImpl, kLinksPrefix + 94)
DECLARE_PMID(kImplementationIDSpace, kAfterUpdateLinkSignalRespServiceImpl, kLinksPrefix + 95)
//gap
DECLARE_PMID(kImplementationIDSpace, kBeforeAddEmbedSignalRespServiceImpl, kLinksPrefix + 97)
DECLARE_PMID(kImplementationIDSpace, kAfterAddEmbedSignalRespServiceImpl, kLinksPrefix + 98)
//gap
DECLARE_PMID(kImplementationIDSpace, kBeforeRemoveEmbedSignalRespServiceImpl, kLinksPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kAfterRemoveEmbedSignalRespServiceImpl, kLinksPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kLinksIteratorRegImpl, kLinksPrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kLinksCodeConversionProviderImpl, kLinksPrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kAddRemoveProviderIDDataImpl, kLinksPrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kLinkScriptProviderImpl, kLinksPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kLinkScriptImpl, kLinksPrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kPrivateLinkUtilsImpl, kLinksPrefix + 108)
DECLARE_PMID(kImplementationIDSpace, kItemLinkScriptProviderImpl, kLinksPrefix + 109)
DECLARE_PMID(kImplementationIDSpace, kPageItemDataLinkActionImpl, kLinksPrefix + 110)
DECLARE_PMID(kImplementationIDSpace, kXMLDataLinkActionImpl, kLinksPrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kStockAssetManagerImpl, kLinksPrefix + 112)
//gap
DECLARE_PMID(kImplementationIDSpace, kLinkItemSuiteASBImpl, kLinksPrefix + 113)
DECLARE_PMID(kImplementationIDSpace, kLinkItemSuiteLayoutCSBImpl, kLinksPrefix + 114)
DECLARE_PMID(kImplementationIDSpace, kExternalActionIdleTaskImpl, kLinksPrefix + 115)
DECLARE_PMID(kImplementationIDSpace, kCloudAssetLinkResourceFactoryImpl, kLinksPrefix + 116)
DECLARE_PMID(kImplementationIDSpace, kCloudAssetLinkResourceHandlerImpl, kLinksPrefix + 117)
DECLARE_PMID(kImplementationIDSpace, kCloudAssetLinkResourceStateUpdaterImpl, kLinksPrefix + 118)
DECLARE_PMID(kImplementationIDSpace, kCloudLibraryLinkedAssetUtilsImpl, kLinksPrefix + 119)
DECLARE_PMID(kImplementationIDSpace, kCCLibrariesAccessorStartupShutdownImpl, kLinksPrefix + 120)
DECLARE_PMID(kImplementationIDSpace, kStockLicenseTypeDataImpl, kLinksPrefix + 121)
DECLARE_PMID(kImplementationIDSpace, kAutoRelinkCloudAssetLinkCmdImpl, kLinksPrefix + 122)
DECLARE_PMID(kImplementationIDSpace, kUpdateLinkWithNoHistoryCmdImpl, kLinksPrefix + 123)

DECLARE_PMID(kImplementationIDSpace, kUpdateLinkImpl, kLinksPrefix + 124)
DECLARE_PMID(kImplementationIDSpace, kLinkObjectEmbedCmdResponderImpl, kLinksPrefix + 125)
DECLARE_PMID(kImplementationIDSpace, kSPPlaceHolderScrapImpl, kLinksPrefix + 126)
DECLARE_PMID(kImplementationIDSpace, kSPPlaceHolderShapeImpl, kLinksPrefix + 127)
DECLARE_PMID(kImplementationIDSpace, kSPDeletePlaceHolderCmdImpl, kLinksPrefix + 128)
DECLARE_PMID(kImplementationIDSpace, kLinkRelinkExtensionCmdImpl, kLinksPrefix + 129)
DECLARE_PMID(kImplementationIDSpace, kLinkRelinkExtensionCmdDataImpl, kLinksPrefix + 130)
DECLARE_PMID(kImplementationIDSpace, kLinkDispatchScriptEventCmdImpl, kLinksPrefix + 131)
DECLARE_PMID(kImplementationIDSpace, kLinkDispatchScriptEventCmdDataImpl, kLinksPrefix + 132)
DECLARE_PMID(kImplementationIDSpace, kLinksStartupShutdownImpl, kLinksPrefix + 133)
DECLARE_PMID(kImplementationIDSpace, kLinkStateUpdateIdleTaskImpl, kLinksPrefix + 134)
DECLARE_PMID(kImplementationIDSpace, kMissingLinkImpl, kLinksPrefix + 135)
DECLARE_PMID(kImplementationIDSpace, kLinkItemSuiteTextCSBImpl, kLinksPrefix + 136)
DECLARE_PMID(kImplementationIDSpace, kUpdateLinkProviderImpl, kLinksPrefix + 137)
DECLARE_PMID(kImplementationIDSpace, kPageItemUpdateLinkServiceImpl, kLinksPrefix + 138)
DECLARE_PMID(kImplementationIDSpace, kMissingLinksOpenDocResponderImpl, kLinksPrefix + 139)
DECLARE_PMID(kImplementationIDSpace, kLinkItemSuiteStructureCSBImpl, kLinksPrefix + 140)
DECLARE_PMID(kImplementationIDSpace, kLinkUpdateRecursivelyCmdImpl, kLinksPrefix + 141)
DECLARE_PMID(kImplementationIDSpace, kFixupConvertDataLinkCmdImpl, kLinksPrefix + 142)
DECLARE_PMID(kImplementationIDSpace, kMissingLinksINXImportResponderImpl, kLinksPrefix + 143)
// new link architecture
DECLARE_PMID(kImplementationIDSpace, kLinkFacadeImpl, kLinksPrefix + 144)
DECLARE_PMID(kImplementationIDSpace, kLinkManagerImpl, kLinksPrefix + 145)
DECLARE_PMID(kImplementationIDSpace, kLinkResourceImpl, kLinksPrefix + 146)
DECLARE_PMID(kImplementationIDSpace, kLinkResourceServiceImpl, kLinksPrefix + 147)
DECLARE_PMID(kImplementationIDSpace, kDefaultLinkResourceFactoryImpl, kLinksPrefix + 148)
DECLARE_PMID(kImplementationIDSpace, kDefaultLinkResourceHandlerImpl, kLinksPrefix + 149)
DECLARE_PMID(kImplementationIDSpace, kDefaultLinkResourceServiceImpl, kLinksPrefix + 150)
DECLARE_PMID(kImplementationIDSpace, kFileLinkResourceFactoryImpl, kLinksPrefix + 151)
DECLARE_PMID(kImplementationIDSpace, kFileLinkResourceHandlerImpl, kLinksPrefix + 152)
DECLARE_PMID(kImplementationIDSpace, kFileLinkResourceStateUpdaterImpl, kLinksPrefix + 153)
DECLARE_PMID(kImplementationIDSpace, kFileLinkResourceStateProcessorFactoryImpl, kLinksPrefix + 154)
DECLARE_PMID(kImplementationIDSpace, kImportLinkImpl, kLinksPrefix + 155)
DECLARE_PMID(kImplementationIDSpace, kExportLinkImpl, kLinksPrefix + 156)
DECLARE_PMID(kImplementationIDSpace, kBidirectionalLinkImpl, kLinksPrefix + 157)
DECLARE_PMID(kImplementationIDSpace, kChildLinkImpl, kLinksPrefix + 158)
DECLARE_PMID(kImplementationIDSpace, kINXImportedLinkImpl, kLinksPrefix + 159)
DECLARE_PMID(kImplementationIDSpace, kLinkManagerDBPagedSetStorageImpl, kLinksPrefix + 160)
DECLARE_PMID(kImplementationIDSpace, kLinksOpenDocResponderImpl, kLinksPrefix + 161)
DECLARE_PMID(kImplementationIDSpace, kLinksCloseDocResponderImpl, kLinksPrefix + 162)
DECLARE_PMID(kImplementationIDSpace, kLinksAppResumeObserverImpl, kLinksPrefix + 163)
DECLARE_PMID(kImplementationIDSpace, kLinkCmdSuiteImpl, kLinksPrefix + 164)
DECLARE_PMID(kImplementationIDSpace, kLinkResourceCreateCmdImpl, kLinksPrefix + 165)
DECLARE_PMID(kImplementationIDSpace, kLinkResourceCreateCmdDataImpl, kLinksPrefix + 166)
DECLARE_PMID(kImplementationIDSpace, kLinkResourceDeleteCmdImpl, kLinksPrefix + 167)
DECLARE_PMID(kImplementationIDSpace, kLinkResourceStateUpdateCmdImpl, kLinksPrefix + 168)
DECLARE_PMID(kImplementationIDSpace, kLinkResourceStateUpdateCmdDataImpl, kLinksPrefix + 169)
DECLARE_PMID(kImplementationIDSpace, kLinkResourceUndoRedoStateUpdateCmdImpl, kLinksPrefix + 170)
DECLARE_PMID(kImplementationIDSpace, kLinkAttachCmdImpl, kLinksPrefix + 171)
DECLARE_PMID(kImplementationIDSpace, kLinkAttachCmdDataImpl, kLinksPrefix + 172)
DECLARE_PMID(kImplementationIDSpace, kLinkCreateCmdImpl, kLinksPrefix + 173)
DECLARE_PMID(kImplementationIDSpace, kLinkCreateCmdDataImpl, kLinksPrefix + 174)
DECLARE_PMID(kImplementationIDSpace, kLinkDeleteCmdImpl, kLinksPrefix + 175)
DECLARE_PMID(kImplementationIDSpace, kLinkDeleteCmdDataImpl, kLinksPrefix + 176)
DECLARE_PMID(kImplementationIDSpace, kLinkEmbedCmdImpl, kLinksPrefix + 177)
DECLARE_PMID(kImplementationIDSpace, kLinkUnembedCmdImpl, kLinksPrefix + 178)
DECLARE_PMID(kImplementationIDSpace, kLinkUnembedCmdDataImpl, kLinksPrefix + 179)
DECLARE_PMID(kImplementationIDSpace, kCaptionSelectionSuiteLayoutCSBImpl, kLinksPrefix + 180)
DECLARE_PMID(kImplementationIDSpace, kCaptionSelectionSuiteASBImpl, kLinksPrefix + 181)
DECLARE_PMID(kImplementationIDSpace, kLinkUpdateCmdImpl, kLinksPrefix + 182)
DECLARE_PMID(kImplementationIDSpace, kLinkUpdateCmdDataImpl, kLinksPrefix + 183)
DECLARE_PMID(kImplementationIDSpace, kLinkCopyToFolderCmdImpl, kLinksPrefix + 184)
DECLARE_PMID(kImplementationIDSpace, kLinkCopyToFolderCmdDataImpl, kLinksPrefix + 185)
DECLARE_PMID(kImplementationIDSpace, kCopyLinkToLinkObjectCmdImpl, kLinksPrefix + 186)
DECLARE_PMID(kImplementationIDSpace, kCopyLinkToLinkObjectCmdDataImpl, kLinksPrefix + 187)
DECLARE_PMID(kImplementationIDSpace, kPageItemLinkObjectImpl, kLinksPrefix + 188)
DECLARE_PMID(kImplementationIDSpace, kUpdateImportLinkImpl, kLinksPrefix + 189)
DECLARE_PMID(kImplementationIDSpace, kLinkUtilsImpl, kLinksPrefix + 190)
DECLARE_PMID(kImplementationIDSpace, kLinkReferenceConverterImpl, kLinksPrefix + 191)
DECLARE_PMID(kImplementationIDSpace, kFixupConvertLinkCmdImpl, kLinksPrefix + 192)
DECLARE_PMID(kImplementationIDSpace, kLinkUpdateStateCmdImpl, kLinksPrefix + 193)
DECLARE_PMID(kImplementationIDSpace, kUpdateBidirectionalLinkImpl, kLinksPrefix + 194)
DECLARE_PMID(kImplementationIDSpace, kLinkRelinkToFolderCmdImpl, kLinksPrefix + 195)
DECLARE_PMID(kImplementationIDSpace, kLinkRelinkToFolderCmdDataImpl, kLinksPrefix + 196)
DECLARE_PMID(kImplementationIDSpace, kDocLinkPrefsImpl_obsolete, kLinksPrefix + 197)	// now only a session pref
DECLARE_PMID(kImplementationIDSpace, kLinkPrefsImpl, kLinksPrefix + 198)
DECLARE_PMID(kImplementationIDSpace, kLinkPrefsCmdImpl, kLinksPrefix + 199)
DECLARE_PMID(kImplementationIDSpace, kLinkPrefsCmdDataImpl, kLinksPrefix + 200)
DECLARE_PMID(kImplementationIDSpace, kDefaultNewLinkConverterImpl, kLinksPrefix + 201)
DECLARE_PMID(kImplementationIDSpace, kDataLinkToLinkResourceConverterImpl, kLinksPrefix + 202)
DECLARE_PMID(kImplementationIDSpace, kDataLinkToLinkConverterImpl, kLinksPrefix + 203)
DECLARE_PMID(kImplementationIDSpace, kRelinkOptionsImpl_obsolete, kLinksPrefix + 204)	// old link architecture
DECLARE_PMID(kImplementationIDSpace, kInDesignLinkEditActionImpl, kLinksPrefix + 205)
DECLARE_PMID(kImplementationIDSpace, kLinkResourceFindMissingCmdImpl, kLinksPrefix + 206)
DECLARE_PMID(kImplementationIDSpace, kLinkResourceFindMissingCmdDataImpl, kLinksPrefix + 207)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoServiceImpl, kLinksPrefix + 208)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoNameProviderImpl, kLinksPrefix + 209)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoSizeProviderImpl, kLinksPrefix + 210)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoStatusProviderImpl, kLinksPrefix + 211)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoFormatTypeProviderImpl, kLinksPrefix + 212)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoPageNumberProviderImpl, kLinksPrefix + 213)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoColorSpaceProviderImpl, kLinksPrefix + 214)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoColorProfileProviderImpl, kLinksPrefix + 215)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoLayerOverrideProviderImpl, kLinksPrefix + 216)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoLinkTypeProviderImpl, kLinksPrefix + 217)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoPPIProviderImpl, kLinksPrefix + 218)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoEffectivePPIProviderImpl, kLinksPrefix + 219)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoPixelSizeProviderImpl, kLinksPrefix + 220)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoXMPAuthorProviderImpl, kLinksPrefix + 221)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoXMPCreatorToolProviderImpl, kLinksPrefix + 222)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoXMPTitleProviderImpl, kLinksPrefix + 223)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoPlaceDateProviderImpl, kLinksPrefix + 224)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoLayerNameProviderImpl, kLinksPrefix + 225)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoXMPCopyrightProviderImpl, kLinksPrefix + 226)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoModDateProviderImpl, kLinksPrefix + 227)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoFullPathProviderImpl, kLinksPrefix + 228)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoChildLinksProviderImpl, kLinksPrefix + 229)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoXMPCreateDateProviderImpl, kLinksPrefix + 230)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoScaleProviderImpl, kLinksPrefix + 231)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoTransparencyProviderImpl, kLinksPrefix + 232)
DECLARE_PMID(kImplementationIDSpace, kLinkObjectPersistUIDDataImpl, kLinksPrefix + 233)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoFolder0ProviderImpl, kLinksPrefix + 234)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoFolder1ProviderImpl, kLinksPrefix + 235)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoFolder2ProviderImpl, kLinksPrefix + 236)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoFolder3ProviderImpl, kLinksPrefix + 237)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoFolder4ProviderImpl, kLinksPrefix + 238)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoFolder5ProviderImpl, kLinksPrefix + 239)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoFolder6ProviderImpl, kLinksPrefix + 240)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoFolder7ProviderImpl, kLinksPrefix + 241)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoFolder8ProviderImpl, kLinksPrefix + 242)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoVolumeNameProviderImpl, kLinksPrefix + 243)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoSkewProviderImpl, kLinksPrefix + 244)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoRotationProviderImpl, kLinksPrefix + 245)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoStoryModifiedProviderImpl, kLinksPrefix + 246)
DECLARE_PMID(kImplementationIDSpace, kLinkResourceReferenceConverterImpl, kLinksPrefix + 247)
DECLARE_PMID(kImplementationIDSpace, kLinkResourceDocResponderImpl, kLinksPrefix + 248)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoStoryNoteCountImpl, kLinksPrefix + 249)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoStoryTrackChangesImpl, kLinksPrefix + 250)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoStoryLabelImpl, kLinksPrefix + 251)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoStoryAssignmentImpl, kLinksPrefix + 252)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoStoryAssignedToImpl, kLinksPrefix + 253)
DECLARE_PMID(kImplementationIDSpace, kScrapLinkManagerImpl, kLinksPrefix + 254)
DECLARE_PMID(kImplementationIDSpace, kScrapLinkManagerDBPagedSetStorageImpl, kLinksPrefix + 255)


DECLARE_PMID(kImplementationIDSpace, kObsoleteBuzzwordLinkResourceFactoryImpl, kLinksPrefix2 + 0)
DECLARE_PMID(kImplementationIDSpace, kObsoleteBuzzwordLinkResourceStateUpdaterImpl, kLinksPrefix2 + 1)
DECLARE_PMID(kImplementationIDSpace, kHTTPAssetLinkResourceFactoryImpl, kLinksPrefix2 + 3)
DECLARE_PMID(kImplementationIDSpace, kHTTPAssetLinkResourceHandlerImpl, kLinksPrefix2 + 4)
DECLARE_PMID(kImplementationIDSpace, kHTTPAssetLinkResourceStateUpdaterImpl, kLinksPrefix2 + 5)
DECLARE_PMID(kImplementationIDSpace, kHTTPLinkResourceServerCacheImpl, kLinksPrefix2 + 6)
DECLARE_PMID(kImplementationIDSpace, kHTTPLinkResourceConnectionImpl, kLinksPrefix2 + 7)
DECLARE_PMID(kImplementationIDSpace, kLinkResourceSetRenditionDataCmdImpl, kLinksPrefix2 + 8)
DECLARE_PMID(kImplementationIDSpace, kLinkResourceResetURICmdImpl, kLinksPrefix2 + 9)
DECLARE_PMID(kImplementationIDSpace, kHTTPLinkConnectionManagerImpl, kLinksPrefix2 + 10)
DECLARE_PMID(kImplementationIDSpace, kHTTPLinkUtilsImpl, kLinksPrefix2 + 11)
DECLARE_PMID(kImplementationIDSpace, kHTTPServerInfoImpl, kLinksPrefix2 + 12)
DECLARE_PMID(kImplementationIDSpace, kHTTPLinkSubsystemObjectProviderImpl, kLinksPrefix2 + 13)
DECLARE_PMID(kImplementationIDSpace, kHTTPLinkSubsystemObjectFactoryImpl, kLinksPrefix2 + 14)
DECLARE_PMID(kImplementationIDSpace, kHTTPLinkResourceServerAPIWrapperImpl, kLinksPrefix2 + 15)
DECLARE_PMID(kImplementationIDSpace, kHTTPLinkManagerImpl, kLinksPrefix2 + 16)
DECLARE_PMID(kImplementationIDSpace, kHTTPLinkPreferencesImpl, kLinksPrefix2 + 17)
DECLARE_PMID(kImplementationIDSpace, kHTTPAssetDownloadManagerImpl, kLinksPrefix2 + 18)
DECLARE_PMID(kImplementationIDSpace, kLinkResourceHelperImpl, kLinksPrefix2 + 19)
DECLARE_PMID(kImplementationIDSpace, kFileLinkResourceHelperHandlerImpl, kLinksPrefix2 + 20)
DECLARE_PMID(kImplementationIDSpace, kCloudAssetLinkResourceHelperHandlerImpl, kLinksPrefix2 + 21)
DECLARE_PMID(kImplementationIDSpace, kHTTPAssetLinkResourceHelperHandlerImpl, kLinksPrefix2 + 22)
DECLARE_PMID(kImplementationIDSpace, kTextFragmentUpdateLinkServiceImpl, kLinksPrefix2 + 23)
DECLARE_PMID(kImplementationIDSpace, kHttpLinkConnectionManagerScriptProviderImpl, kLinksPrefix2 + 24)
DECLARE_PMID(kImplementationIDSpace, kHTTPAssetLinkResourceStateBatchUpdaterImpl, kLinksPrefix2 + 25)
DECLARE_PMID(kImplementationIDSpace, kSetHTTPLinksAutoTagAssetsPrefCmdImpl, kLinksPrefix2 + 26)
DECLARE_PMID(kImplementationIDSpace, kTextFragmentLinkFacadeImpl, kLinksPrefix2 + 27)
DECLARE_PMID(kImplementationIDSpace, kFileEditorAppsUtilsImpl, kLinksPrefix2 + 28)
DECLARE_PMID(kImplementationIDSpace, kLinkResourceRenditionDataImpl, kLinksPrefix2 + 29)

DECLARE_PMID(kImplementationIDSpace, kAEMLinkSubsystemObjectFactoryImpl, kLinksPrefix2 + 30)
DECLARE_PMID(kImplementationIDSpace, kAEMLinkResourceConnectionImpl, kLinksPrefix2 + 31)
DECLARE_PMID(kImplementationIDSpace, kAEMAssetLinkResourceHandlerImpl, kLinksPrefix2 + 32)
DECLARE_PMID(kImplementationIDSpace, kAEMAssetLinkResourceHelperHandlerImpl, kLinksPrefix2 + 33)
DECLARE_PMID(kImplementationIDSpace, kAEMAssetLinkResourceStateUpdaterImpl, kLinksPrefix2 + 34)
DECLARE_PMID(kImplementationIDSpace, kAEMLinkResourceServerAPIWrapperImpl, kLinksPrefix2 + 35)
DECLARE_PMID(kImplementationIDSpace, kAEMCurrentServerInfoImpl, kLinksPrefix2 + 37)
DECLARE_PMID(kImplementationIDSpace, kAEMLinkUtilsImpl, kLinksPrefix2 + 38)
DECLARE_PMID(kImplementationIDSpace, kAEMAssetLinkResourceStateBatchUpdaterImpl, kLinksPrefix2 + 39)

DECLARE_PMID(kImplementationIDSpace, kTextFragmentXMLElementLinkObjectImpl, kLinksPrefix2 + 40)
DECLARE_PMID(kImplementationIDSpace, kHTTPLinksAutoTagAssetPreferenceImpl, kLinksPrefix2 + 41)
DECLARE_PMID(kImplementationIDSpace, kCloudTextAssetUpdateManagerImpl, kLinksPrefix2 + 42)
DECLARE_PMID(kImplementationIDSpace, kElementRefDataImpl, kLinksPrefix2 + 43)
DECLARE_PMID(kImplementationIDSpace, kSnippetPathDataImpl, kLinksPrefix2 + 44)
DECLARE_PMID(kImplementationIDSpace, kGUIDDataImpl, kLinksPrefix2 + 45)


DECLARE_PMID(kImplementationIDSpace, kAemStartupShutdownImpl, kLinksPrefix2 + 46)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoInstanceNameImpl, kLinksPrefix2 + 49)
DECLARE_PMID(kImplementationIDSpace, kUserSigninStatusWchResponderImpl, kLinksPrefix2 + 50)
DECLARE_PMID(kImplementationIDSpace, kUserSigninStatusWchServiceProviderImpl, kLinksPrefix2 + 51)

DECLARE_PMID(kImplementationIDSpace, kHTTPLinkAssetURIPreprocessorImpl, kLinksPrefix2 + 146)
DECLARE_PMID(kImplementationIDSpace, kHTTPLinkResourceServerCacheStorageImpl, kLinksPrefix2 + 147)
DECLARE_PMID(kImplementationIDSpace, kHTTPCacheIdleTaskImpl, kLinksPrefix2 + 148)
DECLARE_PMID(kImplementationIDSpace, kSqliteUtilsImpl, kLinksPrefix2 + 149)

//gap
DECLARE_PMID(kImplementationIDSpace, kCloudTextUpdateLinkServiceImpl, kLinksPrefix2 + 255)

// <Interface ID>
DECLARE_PMID(kInterfaceIDSpace, IID_IDATALINK, kLinksPrefix + 1)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_ISETFLAGSCMDDATA, kLinksPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IATTACHDATALINKCMDDATA, kLinksPrefix + 5)
								// On document, ListLazyNotificationData of
								// PageItems having position changes 
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKOBJECTPI_POSITIONCHANGED, kLinksPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IDIRLIST, kLinksPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKSMANAGER, kLinksPrefix + 8)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IDATALINKHELPER, kLinksPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOREFILENAME, kLinksPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IRESTORELINKCMDDATA, kLinksPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IDATALINKREFERENCE, kLinksPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_DATALINKLISTREFERENCE, kLinksPrefix + 16)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_ISTOREINTERNAL, kLinksPrefix + 19)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKSTATE, kLinksPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKEDSTREAM, kLinksPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOREFILENAMEUTILS, kLinksPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_IFORMATTYPE, kLinksPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_IADDLINKCMDDATA, kLinksPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_ISHOWPAGEITEMUTILS, kLinksPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKSCRIPTOBSERVER, kLinksPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_IUPDATELINK, kLinksPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_IREFERENCECONVERTER2, kLinksPrefix + 30) // IID_IREFERENCECONVERTER
DECLARE_PMID(kInterfaceIDSpace, IID_IPLACEDIALOGPREFS, kLinksPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_IPLACEDIALOGPREFSCMDDATA, kLinksPrefix + 32)
DECLARE_PMID(kInterfaceIDSpace, IID_IEMBEDMANAGER, kLinksPrefix + 33) // same as IID_ILINKSMANAGER
DECLARE_PMID(kInterfaceIDSpace, IID_INEEDEMBEDLIST, kLinksPrefix + 34) // same as IID_IBOOLDATA
DECLARE_PMID(kInterfaceIDSpace, IID_IINDEXTOCDATAREF, kLinksPrefix + 35) // same as IID_IPERSISTUIDDATA. Previously named IID_IGENERICDATALINKREFS
DECLARE_PMID(kInterfaceIDSpace, IID_IINDEXTOCDATASERVICE, kLinksPrefix + 36)
DECLARE_PMID(kInterfaceIDSpace, IID_IWFDATALINKANNEX, kLinksPrefix + 37)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKCMDSIGNALDATA, kLinksPrefix + 38)
DECLARE_PMID(kInterfaceIDSpace, IID_INEWDATALINK, kLinksPrefix + 39)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IDATALINKACTION, kLinksPrefix + 42)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKITEMSUITE, kLinksPrefix + 43)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKOBJECTREFERENCE, kLinksPrefix + 46)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IURLDDDATA, kLinksPrefix + 49)
DECLARE_PMID(kInterfaceIDSpace, IID_IMISSINGLINK, kLinksPrefix + 50)
DECLARE_PMID(kInterfaceIDSpace, IID_ISYNCHRONIZEDATALINK, kLinksPrefix + 51)
DECLARE_PMID(kInterfaceIDSpace, IID_IGETWORKGROUPSTATE, kLinksPrefix + 52)
DECLARE_PMID(kInterfaceIDSpace, IID_IUPDATELINKSERVICE, kLinksPrefix + 53)
DECLARE_PMID(kInterfaceIDSpace, IID_IDEBUGLINKSSLOWDOWN, kLinksPrefix + 54)
DECLARE_PMID(kInterfaceIDSpace, IID_IDEBUGMISSINGLINKSCACHE, kLinksPrefix + 55)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IINDEXTOCREFERENCES, kLinksPrefix + 57) // previously used IID_ILINKSMANAGER. Now uses own interface.

// new link architecture
DECLARE_PMID(kInterfaceIDSpace, IID_ILINK, kLinksPrefix + 60)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKRESOURCE, kLinksPrefix + 61)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKRESOURCEFACTORY, kLinksPrefix + 62)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKRESOURCEHANDLER, kLinksPrefix + 63)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKRESOURCESTATEUPDATER, kLinksPrefix + 64)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKMANAGER, kLinksPrefix + 65)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKOBJECT, kLinksPrefix + 66)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKCMDSUITE, kLinksPrefix + 67)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKRESOURCECREATECMDDATA, kLinksPrefix + 68)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKRESOURCESTATEUPDATECMDDATA, kLinksPrefix + 69)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKCREATECMDDATA, kLinksPrefix + 70)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKDELETECMDDATA, kLinksPrefix + 71)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKUNEMBEDCMDDATA, kLinksPrefix + 72)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKDISPATCHSCRIPTEVENTCMDDATA, kLinksPrefix + 73)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKUPDATECMDDATA, kLinksPrefix + 74)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKCOPYTOFOLDERCMDDATA, kLinksPrefix + 75)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOPYLINKTOLINKOBJECTCMDDATA, kLinksPrefix + 76)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKUTILS, kLinksPrefix + 77)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKEDITACTION, kLinksPrefix + 78)
DECLARE_PMID(kInterfaceIDSpace, IID_INEWLINKCONVERTER, kLinksPrefix + 79)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKINFOPROVIDER, kLinksPrefix + 80)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRIVATELINKUTILS, kLinksPrefix + 81)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKATTACHCMDDATA, kLinksPrefix + 82)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKOBJECTPERSISTUIDDATA, kLinksPrefix + 83)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKRELINKTOFOLDERCMDDATA, kLinksPrefix + 84)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKPREFS, kLinksPrefix + 85)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKPREFSCMDDATA, kLinksPrefix + 86)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKFACADE, kLinksPrefix + 87)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKRESOURCEFINDMISSINGCMDDATA, kLinksPrefix + 88)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKRELINKEXTENSIONCMDDATA, kLinksPrefix + 89)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKCOPYTOFOLDER_DOCUMENT, kLinksPrefix + 90)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKRESOURCEFPO, kLinksPrefix + 91)
DECLARE_PMID(kInterfaceIDSpace, IID_IISTEXTFRAGMENTLINKOBJECT, kLinksPrefix + 92)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTFRAGMENTLINKFACADE, kLinksPrefix + 93)
DECLARE_PMID(kInterfaceIDSpace, IID_IFILEEDITORAPPSUTILS, kLinksPrefix + 94)
// These four are synthetic M2M messages
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKRESOURCE_ADDED, kLinksPrefix + 95)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKRESOURCE_DELETING, kLinksPrefix + 961)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINK_ADDED, kLinksPrefix + 97)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINK_DELETING, kLinksPrefix + 98)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKDATA_CHANGED, kLinksPrefix + 99)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKCAPTIONPREFS, kLinksPrefix + 100) 
DECLARE_PMID(kInterfaceIDSpace, IID_IGENERATECAPTIONCMDDATA, kLinksPrefix + 101) 
DECLARE_PMID(kInterfaceIDSpace, IID_ICAPTIONSELECTIONSUITE, kLinksPrefix + 102) 
DECLARE_PMID(kInterfaceIDSpace, IID_IHTTPASSETDOWNLOADMANAGER, kLinksPrefix + 103)
DECLARE_PMID(kInterfaceIDSpace, IID_ICLOUDLIBRARYLINKEDASSETUTILS, kLinksPrefix + 104)
DECLARE_PMID(kInterfaceIDSpace, IID_STOCKLICENSETYPEDATA, kLinksPrefix + 105)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTOCKASSETMANAGER, kLinksPrefix + 106)
DECLARE_PMID(kInterfaceIDSpace, IID_IHTTPLINKPREFERENCES, kLinksPrefix + 107)
DECLARE_PMID(kInterfaceIDSpace, IID_IHTTPLINKRESOURCESERVERCACHE, kLinksPrefix + 108)
DECLARE_PMID(kInterfaceIDSpace, IID_IHTTPLINKRESOURCECONNECTION, kLinksPrefix + 109)
DECLARE_PMID(kInterfaceIDSpace, IID_IHTTPLINKRESOURCESTATEBATCHUPDATER, kLinksPrefix + 110)
DECLARE_PMID(kInterfaceIDSpace, IID_IHTTPLINKCONNECTIONMANGER, kLinksPrefix + 111)
DECLARE_PMID(kInterfaceIDSpace, IID_IHTTPLINKUTILS, kLinksPrefix + 112)
DECLARE_PMID(kInterfaceIDSpace, IID_IHTTPSERVERINFO, kLinksPrefix + 113)
DECLARE_PMID(kInterfaceIDSpace, IID_IHTTPLINKSUBSYSTEMOBJECTFACTORY, kLinksPrefix + 114)
DECLARE_PMID(kInterfaceIDSpace, IID_IHTTPLINKRESOURCESERVERAPIWRAPPER, kLinksPrefix + 115)
DECLARE_PMID(kInterfaceIDSpace, IID_IHTTPLINKMANGER, kLinksPrefix + 116)
DECLARE_PMID(kInterfaceIDSpace, IID_ICLOUDTEXTASSETUPDATEMANAGER, kLinksPrefix + 117)
DECLARE_PMID(kInterfaceIDSpace, IID_ISNIPPETPATHDATA, kLinksPrefix + 118)
DECLARE_PMID(kInterfaceIDSpace, IID_IELEMENTDATA, kLinksPrefix + 119)
DECLARE_PMID(kInterfaceIDSpace, IID_IGUIDDATA, kLinksPrefix + 120)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKRESOURCERENDITIONDATA, kLinksPrefix + 122)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKRESOURCEHELPER, kLinksPrefix + 123)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKRESOURCEHELPERHANDLER, kLinksPrefix + 124)
DECLARE_PMID(kInterfaceIDSpace, IID_IHTTPINACCESSIBLEACTION, kLinksPrefix + 125)

//Following two are synthetic M2M messages to trigger Links UI status change
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKRESOURCE_ORIGINAL_DOWNLOADING_BEGIN, kLinksPrefix + 126)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKRESOURCE_ORIGINAL_DOWNLOADING_END, kLinksPrefix + 127)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKRESOURCE_ORIGINAL_AVAILABLE_BEGIN, kLinksPrefix + 128)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKRESOURCE_ORIGINAL_AVAILABLE_END, kLinksPrefix + 129)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKRESOURCE_DELETING_ON_INIT, kLinksPrefix + 130)
DECLARE_PMID(kInterfaceIDSpace, IID_IS_XML_OBJECT_GETTING_DELETED, kLinksPrefix + 131)
DECLARE_PMID(kInterfaceIDSpace, IID_IHTTPLINKS_AUTO_TAG_ASSET_PREFERENCE, kLinksPrefix + 132)
DECLARE_PMID(kInterfaceIDSpace, IID_IHTTPLINKASSETURIPREPROCESSOR, kLinksPrefix + 133)
DECLARE_PMID(kInterfaceIDSpace, IID_IUPDATE_XML_REFERENCE, kLinksPrefix + 134)
DECLARE_PMID(kInterfaceIDSpace, IID_IAEMCURRENTSERVERINFO, kLinksPrefix + 135)
DECLARE_PMID(kInterfaceIDSpace, IID_IAEMCURRENTSERVERINFODATA, kLinksPrefix + 136)
DECLARE_PMID(kInterfaceIDSpace, IID_IAEMLINKUTILS, kLinksPrefix + 137)
DECLARE_PMID(kInterfaceIDSpace, IID_IHTTPLINKRESOURCESERVERCACHESTORAGE, kLinksPrefix + 138)
DECLARE_PMID(kInterfaceIDSpace, IID_IHTTPCACHEIDLETASK, kLinksPrefix + 139)
DECLARE_PMID(kInterfaceIDSpace, IID_ISQLITEUTILS, kLinksPrefix + 140)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKRESOURCE_ORIGINAL_DELETED_BEGIN, kLinksPrefix + 141)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKRESOURCE_ORIGINAL_DELETED_END, kLinksPrefix + 142)
DECLARE_PMID(kInterfaceIDSpace, IID_IASYNCDOWNLOADEDASSETS, kLinksPrefix + 143)

// <Widget ID>
DECLARE_PMID(kWidgetIDSpace, kNewLayersAddedWarningWidgetId, kLinksPrefix + 1)

// <Service ID>
DECLARE_PMID(kServiceIDSpace, kIDataLinkService, kLinksPrefix + 1)
DECLARE_PMID(kServiceIDSpace, kIndexTOCDataService, kLinksPrefix + 2)
DECLARE_PMID(kServiceIDSpace, kLinksChangedSignalService, kLinksPrefix + 3)
DECLARE_PMID(kServiceIDSpace, kUpdateLinkService, kLinksPrefix + 4)
DECLARE_PMID(kServiceIDSpace, kLinkInfoService, kLinksPrefix + 5)
//gap
DECLARE_PMID(kServiceIDSpace, kBeforeAddLinkSignalResponderService, kLinksPrefix + 10)
DECLARE_PMID(kServiceIDSpace, kAfterAddLinkSignalResponderService, kLinksPrefix + 11)
//gap
DECLARE_PMID(kServiceIDSpace, kBeforeAddExtraLinkSignalResponderService, kLinksPrefix + 16)
DECLARE_PMID(kServiceIDSpace, kAfterAddExtraLinkSignalResponderService, kLinksPrefix + 17)
//gap
DECLARE_PMID(kServiceIDSpace, kBeforeAttachDataLinkSignalResponderService, kLinksPrefix + 19)
DECLARE_PMID(kServiceIDSpace, kAfterAttachDataLinkSignalResponderService, kLinksPrefix + 20)
//gap
DECLARE_PMID(kServiceIDSpace, kBeforeRemoveLinksSignalResponderService, kLinksPrefix + 28)
DECLARE_PMID(kServiceIDSpace, kAfterRemoveLinksSignalResponderService, kLinksPrefix + 29)
//gap
DECLARE_PMID(kServiceIDSpace, kBeforeRestoreLinkSignalResponderService, kLinksPrefix + 31)
DECLARE_PMID(kServiceIDSpace, kAfterRestoreLinkSignalResponderService, kLinksPrefix + 32)
//gap
DECLARE_PMID(kServiceIDSpace, kBeforeUpdateLinkSignalResponderService, kLinksPrefix + 34)
DECLARE_PMID(kServiceIDSpace, kAfterUpdateLinkSignalResponderService, kLinksPrefix + 35)
//gap
DECLARE_PMID(kServiceIDSpace, kBeforeAddEmbedSignalResponderService, kLinksPrefix + 37)
DECLARE_PMID(kServiceIDSpace, kAfterAddEmbedSignalResponderService, kLinksPrefix + 38)
//gap
DECLARE_PMID(kServiceIDSpace, kBeforeRemoveEmbedSignalResponderService, kLinksPrefix + 40)
DECLARE_PMID(kServiceIDSpace, kAfterRemoveEmbedSignalResponderService, kLinksPrefix + 41)
//gap
DECLARE_PMID(kServiceIDSpace, kLinkResourceService, kLinksPrefix + 50)
//gap
DECLARE_PMID(kServiceIDSpace, kHTTPLinkSubsystemObjectProvider, kLinksPrefix + 60)

// <Error ID>
// Error Codes
// NOTE:  The offset is used to find the corresponding error string in the UserErrorTable resource
DECLARE_PMID(kErrorIDSpace, kNoAssociatedPageItemError, kLinksPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kLinkMissingError, kLinksPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kOPIOrDCSLinkError, kLinksPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kHiddenPageItemError, kLinksPrefix + 4)
DECLARE_PMID(kErrorIDSpace, kLinkFileNameError, kLinksPrefix + 5)
DECLARE_PMID(kErrorIDSpace, kNotSystemFileLinkError, kLinksPrefix + 6)
DECLARE_PMID(kErrorIDSpace, kUnableToBringAppToFrontError, kLinksPrefix + 7)
DECLARE_PMID(kErrorIDSpace, kEditorNotFoundError, kLinksPrefix + 8)
DECLARE_PMID(kErrorIDSpace, kInvalidParameterErr, kLinksPrefix + 9)
DECLARE_PMID(kErrorIDSpace, kOutOfMemoryError, kLinksPrefix + 10)
DECLARE_PMID(kErrorIDSpace, kOverSetGraphicError, kLinksPrefix + 11)
DECLARE_PMID(kErrorIDSpace, kUnableToCreateFileError, kLinksPrefix + 12)
DECLARE_PMID(kErrorIDSpace, kDiskFullError, kLinksPrefix + 13)
DECLARE_PMID(kErrorIDSpace, kFileLockedError, kLinksPrefix + 14)
DECLARE_PMID(kErrorIDSpace, kLinksUserCanceled, kLinksPrefix + 15)
DECLARE_PMID(kErrorIDSpace, kHiddenFormFieldStateError, kLinksPrefix + 16)
DECLARE_PMID(kErrorIDSpace, kLinkIsNotEmbeddedError, kLinksPrefix + 17)
DECLARE_PMID(kErrorIDSpace, kLinkOutOfDateError, kLinksPrefix + 18)
DECLARE_PMID(kErrorIDSpace, kCantLinkToSnippetFileError, kLinksPrefix + 19)
DECLARE_PMID(kErrorIDSpace, kLinkIsEmbeddedError, kLinksPrefix + 20)
DECLARE_PMID(kErrorIDSpace, kLinkFileAlreadyExistsError, kLinksPrefix + 21)
DECLARE_PMID(kErrorIDSpace, kLinkCopyFileTypeError, kLinksPrefix + 22)
DECLARE_PMID(kErrorIDSpace, kDeletedTextGraphicError, kLinksPrefix + 23)
DECLARE_PMID(kErrorIDSpace, kXMLNotInLayoutGraphicError, kLinksPrefix + 24)
DECLARE_PMID(kErrorIDSpace, kHiddenTextGraphicError, kLinksPrefix + 25)
DECLARE_PMID(kErrorIDSpace, kHiddenMSOStateError, kLinksPrefix + 26)
DECLARE_PMID(kErrorIDSpace, kInvalidChildLinkOpError, kLinksPrefix + 27)
//DECLARE_PMID(kErrorIDSpace, kBWLinkDownloadFailedError, kLinksPrefix + 28) Obsolete in CS6
DECLARE_PMID(kErrorIDSpace, kCantCreateResourceError, kLinksPrefix + 29)
DECLARE_PMID(kErrorIDSpace, kCantDownloadResourceError, kLinksPrefix + 30)
DECLARE_PMID(kErrorIDSpace, kUnableToGetConnectionError, kLinksPrefix + 31)
DECLARE_PMID(kErrorIDSpace, kCantReplaceResourceError, kLinksPrefix + 32)
DECLARE_PMID(kErrorIDSpace, kCantCreateTextFragMetadataLinkOnLockedOrHiddenLayerError, kLinksPrefix + 33)
DECLARE_PMID(kErrorIDSpace, kCantInsertAndCreateError, kLinksPrefix + 34)
DECLARE_PMID(kErrorIDSpace, kCantPlaceMetadataError, kLinksPrefix + 35)
DECLARE_PMID(kErrorIDSpace, kCantPlaceTextFragmentLinkError, kLinksPrefix + 36)

//suites
DECLARE_PMID(kScriptInfoIDSpace, kLinkSuiteScriptElement,			kLinksPrefix + 1)

//objects
DECLARE_PMID(kScriptInfoIDSpace, kLinkObjectScriptElement,			kLinksPrefix + 10)
DECLARE_PMID(kScriptInfoIDSpace, kHttpLinkConnectionManagerObjectScriptElement, kLinksPrefix + 11)

//properties
DECLARE_PMID(kScriptInfoIDSpace, kHttpLinkConnectionManagerPropertyScriptElement, kLinksPrefix + 16)
DECLARE_PMID(kScriptInfoIDSpace, kLinkResourceRenditionTypePropertyScriptElement, kLinksPrefix + 17)
DECLARE_PMID(kScriptInfoIDSpace, kLinkStockStatePropertyScriptElement,	kLinksPrefix + 18)
DECLARE_PMID(kScriptInfoIDSpace, kLinkParentPropertyScriptElement,		kLinksPrefix + 19)
DECLARE_PMID(kScriptInfoIDSpace, kLinkIndexPropertyScriptElement,		kLinksPrefix + 20)
DECLARE_PMID(kScriptInfoIDSpace, kLinkEditedPropertyScriptElement,		kLinksPrefix + 21)
DECLARE_PMID(kScriptInfoIDSpace, kLinkTypePropertyScriptElement,		kLinksPrefix + 22)
DECLARE_PMID(kScriptInfoIDSpace, kLinkNeededPropertyScriptElement,		kLinksPrefix + 23)
DECLARE_PMID(kScriptInfoIDSpace, kLinkEtagPropertyScriptElement,		kLinksPrefix + 24)
DECLARE_PMID(kScriptInfoIDSpace, kLinkAssetIDPropertyScriptElement,		kLinksPrefix + 25)
DECLARE_PMID(kScriptInfoIDSpace, kLinkStatusPropertyScriptElement,		kLinksPrefix + 26)
DECLARE_PMID(kScriptInfoIDSpace, kItemLinkPropertyScriptElement,		kLinksPrefix + 27)
DECLARE_PMID(kScriptInfoIDSpace, kLinkUrlPropertyScriptElement,			kLinksPrefix + 28)
DECLARE_PMID(kScriptInfoIDSpace, kLinkInfoPropertyScriptElement,		kLinksPrefix + 29)

//methods
DECLARE_PMID(kScriptInfoIDSpace, kLinkEditOriginalMethodScriptElement,	kLinksPrefix + 30)
DECLARE_PMID(kScriptInfoIDSpace, kLinkRelinkMethodScriptElement,			kLinksPrefix + 31)
DECLARE_PMID(kScriptInfoIDSpace, kLinkShowMethodScriptElement,			kLinksPrefix + 32)
DECLARE_PMID(kScriptInfoIDSpace, kLinkUnlinkMethodScriptElement,			kLinksPrefix + 33)
DECLARE_PMID(kScriptInfoIDSpace, kLinkUpdateMethodScriptElement,			kLinksPrefix + 34)
DECLARE_PMID(kScriptInfoIDSpace, kLinkUnembedMethodScriptElement,		kLinksPrefix + 35)
DECLARE_PMID(kScriptInfoIDSpace, kLinkRevealInOSMethodScriptElement,		kLinksPrefix + 36)
DECLARE_PMID(kScriptInfoIDSpace, kLinkRevealInBrowserMethodScriptElement,kLinksPrefix + 37)
DECLARE_PMID(kScriptInfoIDSpace, kLinkCopyLinkMethodScriptElement,		kLinksPrefix + 38)
DECLARE_PMID(kScriptInfoIDSpace, kLinkReplaceWithOriginalMethodScriptElement, kLinksPrefix + 39)


DECLARE_PMID(kScriptInfoIDSpace, kURLConnectMethodScriptElement, kLinksPrefix2 + 38)
DECLARE_PMID(kScriptInfoIDSpace, kURLisConnectedMethodScriptElement, kLinksPrefix2 + 39)
DECLARE_PMID(kScriptInfoIDSpace, kURLLogoutMethodScriptElement, kLinksPrefix2 + 40)
DECLARE_PMID(kScriptInfoIDSpace, kCreateTextFragmentLinkMethodScriptElement, kLinksPrefix2 + 41)
DECLARE_PMID(kScriptInfoIDSpace, kRelinkTextFragmentLinkMethodScriptElement, kLinksPrefix2 + 42)
DECLARE_PMID(kScriptInfoIDSpace, kReinitLinkMethodScriptElement, kLinksPrefix2 + 43)

//enums
DECLARE_PMID(kScriptInfoIDSpace, kLinkStatusEnumScriptElement,					kLinksPrefix + 40)
DECLARE_PMID(kScriptInfoIDSpace, kLinkStockStateEnumScriptElement,				kLinksPrefix + 41)
DECLARE_PMID(kScriptInfoIDSpace, kLinkResourceStoreStateEnumScriptElement,		kLinksPrefix + 42)
DECLARE_PMID(kScriptInfoIDSpace, kLinkResourceModifiedEnumScriptElement,		kLinksPrefix + 43)
DECLARE_PMID(kScriptInfoIDSpace, kLinkObjectModifiedEnumScriptElement,			kLinksPrefix + 44)
DECLARE_PMID(kScriptInfoIDSpace, kLinkImportPolicyEnumScriptElement,			kLinksPrefix + 45)
DECLARE_PMID(kScriptInfoIDSpace, kLinkExportPolicyEnumScriptElement,			kLinksPrefix + 46)
DECLARE_PMID(kScriptInfoIDSpace, kLinkResourceRenditionTypeEnumScriptElement, kLinksPrefix + 47)


//CS4 INX properties
DECLARE_PMID(kScriptInfoIDSpace, kLinkResourceURIPropertyScriptElement,			kLinksPrefix + 60)
DECLARE_PMID(kScriptInfoIDSpace, kLinkResourceFormatPropertyScriptElement,		kLinksPrefix + 61)
DECLARE_PMID(kScriptInfoIDSpace, kLinkResourceStoreStatePropertyScriptElement,	kLinksPrefix + 62)
DECLARE_PMID(kScriptInfoIDSpace, kLinkClassIDPropertyScriptElement,				kLinksPrefix + 63)
DECLARE_PMID(kScriptInfoIDSpace, kLinkClientIDPropertyScriptElement,			kLinksPrefix + 64)
DECLARE_PMID(kScriptInfoIDSpace, kLinkResourceModStatePropertyScriptElement,	kLinksPrefix + 65)
DECLARE_PMID(kScriptInfoIDSpace, kLinkObjectModStatePropertyScriptElement,		kLinksPrefix + 66)
DECLARE_PMID(kScriptInfoIDSpace, kLinkShowInUIPropertyScriptElement,			kLinksPrefix + 67)
DECLARE_PMID(kScriptInfoIDSpace, kLinkCanEmbedPropertyScriptElement,			kLinksPrefix + 68)
DECLARE_PMID(kScriptInfoIDSpace, kLinkCanUnembedPropertyScriptElement,			kLinksPrefix + 69)
DECLARE_PMID(kScriptInfoIDSpace, kLinkCanPackagePropertyScriptElement,			kLinksPrefix + 70)
DECLARE_PMID(kScriptInfoIDSpace, kLinkImportPolicyPropertyScriptElement,		kLinksPrefix + 71)
DECLARE_PMID(kScriptInfoIDSpace, kLinkExportPolicyPropertyScriptElement,		kLinksPrefix + 72)
DECLARE_PMID(kScriptInfoIDSpace, kLinkImportStampPropertyScriptElement,			kLinksPrefix + 73)
DECLARE_PMID(kScriptInfoIDSpace, kLinkImportModTimePropertyScriptElement,		kLinksPrefix + 74)
DECLARE_PMID(kScriptInfoIDSpace, kLinkImportTimePropertyScriptElement,			kLinksPrefix + 75)
DECLARE_PMID(kScriptInfoIDSpace, kLinkExportTimePropertyScriptElement,			kLinksPrefix + 76)
DECLARE_PMID(kScriptInfoIDSpace, kCreateLinkMethodScriptElement,				kLinksPrefix + 77)
DECLARE_PMID(kScriptInfoIDSpace, kCheckLinksAtOpenPropertyScriptElement,		kLinksPrefix + 78)
DECLARE_PMID(kScriptInfoIDSpace, kFindMissingLinksAtOpenPropertyScriptElement,	kLinksPrefix + 79)
DECLARE_PMID(kScriptInfoIDSpace, kLinksPrefsObjectScriptElement,				kLinksPrefix + 80)
DECLARE_PMID(kScriptInfoIDSpace, kLinksPrefsPropertyScriptElement,				kLinksPrefix + 81)
DECLARE_PMID(kScriptInfoIDSpace, kLinkResourceSizePropertyScriptElement,        kLinksPrefix + 82)
DECLARE_PMID(kScriptInfoIDSpace, kHTTPLinksRenditionTypePropertyScriptElement,   kLinksPrefix + 83)
DECLARE_PMID(kScriptInfoIDSpace, kHTTPLinksAutoTagAssetPropertyScriptElement, kLinksPrefix + 84)

//Events
DECLARE_PMID(kScriptInfoIDSpace, kAfterLinksChangedEventScriptElement,			kLinksPrefix + 200)
DECLARE_PMID(kScriptInfoIDSpace, kAfterNewLinkEventScriptElement,				kLinksPrefix + 201)
DECLARE_PMID(kScriptInfoIDSpace, kBeforeDeleteLinkEventScriptElement,			kLinksPrefix + 202)
DECLARE_PMID(kScriptInfoIDSpace, kAfterDeleteLinkEventScriptElement,			kLinksPrefix + 203)
DECLARE_PMID(kScriptInfoIDSpace, kBeforeUpdateLinkEventScriptElement,			kLinksPrefix + 204)
DECLARE_PMID(kScriptInfoIDSpace, kAfterUpdateLinkEventScriptElement,			kLinksPrefix + 205)
DECLARE_PMID(kScriptInfoIDSpace, kBeforeEmbedLinkEventScriptElement,			kLinksPrefix + 206)
DECLARE_PMID(kScriptInfoIDSpace, kAfterEmbedLinkEventScriptElement,				kLinksPrefix + 207)
DECLARE_PMID(kScriptInfoIDSpace, kBeforeUnembedLinkEventScriptElement,			kLinksPrefix + 208)
DECLARE_PMID(kScriptInfoIDSpace, kAfterUnembedLinkEventScriptElement,			kLinksPrefix + 209)
DECLARE_PMID(kScriptInfoIDSpace, kBeforeMoveLinkEventScriptElement,				kLinksPrefix + 210)
DECLARE_PMID(kScriptInfoIDSpace, kAfterMoveLinkEventScriptElement,				kLinksPrefix + 211)

// More methods for CS6.
DECLARE_PMID(kScriptInfoIDSpace, kLinkGoToSourceMethodScriptElement, kLinksPrefix + 212)

//GUIDS
// {77617589-D3DE-11d1-AAA6-00C04FA349C7}
#define kLink_CLSID { 0x77617589, 0xd3de, 0x11d1, { 0xaa, 0xa6, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {7761758A-D3DE-11d1-AAA6-00C04FA349C7}
#define kLinks_CLSID { 0x7761758a, 0xd3de, 0x11d1, { 0xaa, 0xa6, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }

// {8F7AED4D-37D3-4610-BD32-504CB5908F32}
#define kLinksPref_CLSID { 0x8F7AED4D, 0x37D3, 0x4610, {0xBD, 0x32, 0x50, 0x4C, 0xB5, 0x90, 0x8F, 0x32}}

// {43CDA0D0-E2B1-42AF-96FA-3910C63F6ED7}
#define kHttpLinkConnectionManager_CLSID {0x43cda0d0, 0xe2b1, 0x42af, {0x96, 0xfa, 0x39, 0x10, 0xc6, 0x3f, 0x6e, 0xd7} }

enum LinkScriptIDs
{
	s_LinkSuite =				'K2LK',
	c_Link =					'clnk',
	c_Links =					'lnks',
	c_HttpLinkConnectionManager =          'cmgr',
	p_Link =					'plnk',
	p_Edited =					'lked',
	p_Needed =					'lknd',
	p_LinkType =				'lnkt',
	p_LinkUrl =					'lURL',
	p_LinkEtag =				'letg',
	p_LinkAssetID =				'laID',
	p_LinkInfo =				'LnkI',
	p_LinkMetadata = 			'lXMP',
	p_LinkStock =				'lstk',
	p_LinkResourceURI =			'lURI',
	p_LinkResourceFormat =		'lrfo',
	p_LinkResourceRenditionType = 'lRen',
	p_HttpLinkConnectionManager =      'hcmr',
	p_LinkResourceStoreState =	'lrss',
	p_LinkResourceSize =		'lrsi',
	p_LinkClassID =				'lCID',
	p_LinkClientID =			'lcID',
	p_LinkResourceModState =	'lrms',
	p_LinkObjectModState =		'loms',
	p_LinkShowInUI =			'lsui',
	p_LinkCanEmbed =			'lcem',
	p_LinkCanUnembed =			'lcue',
	p_LinkCanPackage =			'lcpa',
	p_LinkImportPolicy =		'lipo',
	p_LinkExportPolicy =		'lepo',
	p_LinkImportStamp =			'list',
	p_LinkImportModTime =		'limt',
	p_LinkImportTime =			'liti',
	p_LinkExportTime =			'leti',
	en_LinkStatus =				'stte',
	en_LinkNormal =				'norm',	// same as en_Normal
	en_LinkOutOfDate =			'lood',
	en_LinkMissing =			'lmis',
	en_LinkInaccessible =			'lina',
	en_LinkEmbedded =			'Lmbd',
	en_LinkResourceStoreState =	'lrse',
	en_LinkResourceNormal  =	'norm',	// same as en_LinkNormal
	en_LinkResourceCached =		'lrca',
	en_LinkResourceContained =	'lrco',
	en_LinkResourceEmbedded =	'Lrem',	// same as en_LinkEmbedded
	en_LinkResourceRenditionType = 'LrRT',
	en_LinkResourceFPO      =   'Lfpo', // FPO
	en_LinkResourceOriginal =   'Lori', //Original
	en_LinkImportPolicy	=		'lipe',
	en_LinkNoAutoImport	=		'lnai',
	en_LinkImportOnModify =		'liom',
	en_LinkExportPolicy	=		'lepe',
	en_LinkNoAutoExport	=		'lnae',
	en_LinkExportOnModify =		'leom',
	en_LinkExportOnClose =		'leoc',
	en_LinkExportOnSave	=		'leos',
	en_LinkStockState =			'lsks',
	en_LinkNotStock = 			'lnsk',
	en_LinkStockComp = 			'lskc',
	en_LinkStockHiRes = 		'lskh',
	e_BeforeUpdate =			'BfUp',
	e_AfterUpdate =				'AfUp',
	e_BeforeEmbed =				'BfEm',
	e_AfterEmbed =				'AfEm',
	e_BeforeUnembed =			'BfUE',
	e_AfterUnembed =			'AfUE',
	e_AfterLinksChanged =		'AfLk',
	e_HttpConnect =             'hcon',
	e_ReplaceWithOriginal =     'ReOr',

	//method parameters
	p_ServerUrl =               'surl',
	p_JsonData =                'jsnd',
};

// <Ignore>
// Resources with LocaleIndex set.
#define kLinksStringsRsrcID				100
#define kLinksStringsNoTransRsrcID		200
#define kLinksErrorStringTableRsrcID	300

// icon rsrc ids.
// link info column header rsrcs
#define kLinkInfoPageColumnHeaderIconResID			400
#define kLinkInfoLayerOverrideColumnHeaderIconResID	401
#define kLinkInfoColorspaceColumnHeaderIconResID	402
#define kLinkInfoTransparencyColumnHeaderIconResID	403
#define kLinkInfoScaleColumnHeaderIconResID			404
#define kLinkInfoEffectivePPIColumnHeaderIconResID	405
#define kLinkInfoActualPPIColumnHeaderIconResID		406
#define kLinksStatusColumnHeaderIconResID			407

// link status icon rsrcs. Note that the values of these has a dual meaning. Meaning 1: the rsrc id for the icon. Meaning 2: these values are used for sorting the link status column, so keep them in an order that makes sense!
#define kLinksInaccessibleStatusIconResID		500
#define kLinksMissingStatusIconResID			502
#define kLinksStatusChildMissingResID			504
#define kLinksOutOfDateStatusIconResID			506
#define kLinksStatusInstanceOutOfDateResID		508
#define kLinksStatusChildOutOfDateResID			510
#define kLinksEmbeddedStatusIconResID			512
#define kLinksCachedStatusIconResID				514
#define kLinksPendingStatusIconResID			516
#define kLinksUnknownStatusIconResID			518
#define kLinksStatusOKResID						520
#define kCCLinkMissingIconResID					524
#define kCCLinkModifiedIconResID				526
#define kCCLinkedResID							528
#define kStockCartIconResID						530
#define kStockSyncProgressIconResID				532
#define kHTTPFPOLinkInaccessibleIconResID       534
#define kHTTPLinkInaccessibleIconResID          536
#define kHTTPMetadataLinkInaccessibleIconResID  538
#define kHTTPFPOLinkMissingIconResID			540
#define kHTTPLinkMissingIconResID				542
#define kHTTPMetadataLinkMissingIconResID	    544
#define kHTTPFPOLinkModifiedIconResID			546
#define kHTTPLinkModifiedIconResID				548
#define kHTTPMetadataLinkModifiedIconResID      550
#define kHTTPFPOLinkedResID						552
#define kHTTPOriginalAssetAvailableIconResID    554
#define kHTTPAssetDownloadingIconResID	        556
#define kHTTPLinkedResID						558
#define kHTTPMetadataLinkedResID	            560

#define kAALFPOLinkInaccessibleIconResID            570
#define kAALLinkInaccessibleIconResID               572
#define kAALFPOLinkMissingIconResID                 574
#define kAALLinkMissingIconResID                    576
#define kAALFPOLinkModifiedIconResID                578
#define kAALLinkModifiedIconResID                   580
#define kAALLinkedResID                             582
#define kAALFPOLinkedResID                          584
#define kAALOriginalAssetAvailableIconResID         586
#define kAALAssetDownloadingIconResID               588

//Icons for Page Item adornment.
#define kPageItemAdornmentLinkObjectIconRsrcID							1000
#define kPageItemAdornmentLinkObjectOutOfDateIconRsrcID					1010
#define kPageItemAdornmentLinkObjectMissingStatusIconRsrcID				1020

#define kPageItemAdornmentCCLinkedIconRsrcID							1030
#define kPageItemAdornmentCCLinkModifiedIconRsrcID						1040
#define kPageItemAdornmentCCLinkMissingStatusIconRsrcID					1050

#define kPageItemAdornmentHTTPLinkedIconRsrcID							1060
#define kPageItemAdornmentHTTPLinkModifiedIconRsrcID					1070
#define kPageItemAdornmentHTTPLinkMissingStatusIconRsrcID				1080
#define kPageItemAdornmentHTTPFPOLinkedIconRsrcID						1090
#define kPageItemAdornmentHTTPFPOLinkModifiedIconRsrcID					1100
#define kPageItemAdornmentHTTPFPOLinkMissingStatusIconRsrcID			1110
#define kPageItemAdornmentHTTPOriginalAssetAvailableIconRsrcID          1120
#define kPageItemAdornmentHTTPFPOLinkInaccessibleStatusIconRsrcID       1130
#define kPageItemAdornmentHTTPLinkInaccessibleStatusIconRsrcID			1140

#define kPageItemAdornmentAALLinkedIconRsrcID                           1160
#define kPageItemAdornmentAALLinkModifiedIconRsrcID                     1170
#define kPageItemAdornmentAALLinkMissingStatusIconRsrcID                1180
#define kPageItemAdornmentAALLinkInaccessibleStatusIconRsrcID           1190
#define kPageItemAdornmentAALFPOLinkedIconRsrcID                        1200
#define kPageItemAdornmentAALFPOLinkModifiedIconRsrcID                  1210
#define kPageItemAdornmentAALFPOLinkMissingStatusIconRsrcID             1220
#define kPageItemAdornmentAALOriginalAssetAvailableIconRsrcID           1230
#define kPageItemAdornmentAALFPOLinkInaccessibleStatusIconRsrcID        1240
#define kPageItemAdornmentAALOriginalAssetDownloadingIconRsrcID        	1250
//---------------------------------------------------
// InvalHandlerTypeID
//---------------------------------------------------
DECLARE_PMID(kInvalHandlerIDSpace, kLinkResourceInvalHandlerID, kLinksPrefix + 1 )
#endif // __LinksIID__

