//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/XMLID.h $
//  
//  Owner: Michael Burbidge
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
//  Info:	Contains IDs used by the XML architecture.
//  
//========================================================================================

#ifndef __XMLID__
#define __XMLID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kXMLPrefix	 RezLong(0xBF00)
#define kXMLPrefix2	 RezLong(0x1BC00)

// PluginID
#define kXMLPluginName 					"XML"

START_IDS()
DECLARE_PMID(kPlugInIDSpace, kXMLPluginID, kXMLPrefix + 1)

// <Start IDC>

// <Class ID>
DECLARE_PMID(kClassIDSpace, kXMLReattachElementCmdBoss, kXMLPrefix + 1)
DECLARE_PMID(kClassIDSpace, kPrivateXMLSetExpandLinkElementsCmdBoss, kXMLPrefix + 2)
DECLARE_PMID(kClassIDSpace, kXMLElementScriptProviderBoss, kXMLPrefix + 3)
DECLARE_PMID(kClassIDSpace, kXMLNewDocResponderBoss, kXMLPrefix + 4)
DECLARE_PMID(kClassIDSpace, kXMLAttachElementCmdBoss, kXMLPrefix + 5)
DECLARE_PMID(kClassIDSpace, kXMLSetElementTagCmdBoss, kXMLPrefix + 6)
DECLARE_PMID(kClassIDSpace, kXMLElementBoss, kXMLPrefix + 7)
DECLARE_PMID(kClassIDSpace, kXMLPhase2ConversionBoss, kXMLPrefix + 8)
DECLARE_PMID(kClassIDSpace, kXMLCopyTableElementCmdBoss, kXMLPrefix + 9)
DECLARE_PMID(kClassIDSpace, kXMLExportHandlerBoss, kXMLPrefix + 10)
DECLARE_PMID(kClassIDSpace, kXMLExportProviderBoss, kXMLPrefix + 11)
DECLARE_PMID(kClassIDSpace, kXMLDetachElementCmdBoss, kXMLPrefix + 12)
DECLARE_PMID(kClassIDSpace, kImportXMLFileCmdBoss, kXMLPrefix + 13)
DECLARE_PMID(kClassIDSpace, kXMLImportScriptProviderBoss, kXMLPrefix + 14)
DECLARE_PMID(kClassIDSpace, kXMLDeleteParaStyleCmdResponderBoss, kXMLPrefix + 15)
//DECLARE_PMID(kClassIDSpace, kXMLSpecifierBoss, kXMLPrefix + 16)
DECLARE_PMID(kClassIDSpace, kXMLDocScriptProviderBoss, kXMLPrefix + 17)
DECLARE_PMID(kClassIDSpace, kXMLAttributeScriptProviderBoss, kXMLPrefix + 18)
DECLARE_PMID(kClassIDSpace, kXMLAttributeScriptObjectBoss, kXMLPrefix + 19)
DECLARE_PMID(kClassIDSpace, kXMLCreateAttributeCmdBoss, kXMLPrefix + 20)
DECLARE_PMID(kClassIDSpace, kXMLDeleteAttributeCmdBoss, kXMLPrefix + 21)
DECLARE_PMID(kClassIDSpace, kXMLSetAttributeValueCmdBoss, kXMLPrefix + 22)
DECLARE_PMID(kClassIDSpace, kXMLTagScriptProviderBoss, kXMLPrefix + 23)
DECLARE_PMID(kClassIDSpace, kXMLMoveElementCmdBoss, kXMLPrefix + 24)
DECLARE_PMID(kClassIDSpace, kXMLTagBoss, kXMLPrefix + 25)
DECLARE_PMID(kClassIDSpace, kXMLCreateTagCmdBoss, kXMLPrefix + 26)
DECLARE_PMID(kClassIDSpace, kXMLDeleteTagCmdBoss, kXMLPrefix + 27)
DECLARE_PMID(kClassIDSpace, kXMLSetTagNameCmdBoss, kXMLPrefix + 28)
DECLARE_PMID(kClassIDSpace, kXMLDeleteStoryCmdResponderBoss, kXMLPrefix + 29)
DECLARE_PMID(kClassIDSpace, kXMLCommentBoss, kXMLPrefix + 30)
DECLARE_PMID(kClassIDSpace, kXMLStrandBoss, kXMLPrefix + 31)
DECLARE_PMID(kClassIDSpace, kXMLCreateCommentCmdBoss, kXMLPrefix + 32)
DECLARE_PMID(kClassIDSpace, kPrivateXMLInsertMarkerCmdBoss, kXMLPrefix + 33)
DECLARE_PMID(kClassIDSpace, kXMLDeleteMarkerCmdBoss, kXMLPrefix + 34)
DECLARE_PMID(kClassIDSpace, kXMLStyleToTagScriptProviderBoss, kXMLPrefix + 35)
DECLARE_PMID(kClassIDSpace, kXMLStyleToTagScriptObjectBoss, kXMLPrefix + 36)
DECLARE_PMID(kClassIDSpace, kXMLMapStyleToTagCmdBoss, kXMLPrefix + 37)
DECLARE_PMID(kClassIDSpace, kXMLUnMapStyleToTagCmdBoss, kXMLPrefix + 39)
DECLARE_PMID(kClassIDSpace, kPrivateXMLXferElementCmdBoss, kXMLPrefix + 40)
DECLARE_PMID(kClassIDSpace, kXMLTagToStyleScriptProviderBoss, kXMLPrefix + 41)
DECLARE_PMID(kClassIDSpace, kXMLTagToStyleScriptObjectBoss, kXMLPrefix + 42)
DECLARE_PMID(kClassIDSpace, kXMLMapTagToStyleCmdBoss, kXMLPrefix + 43)
DECLARE_PMID(kClassIDSpace, kXMLUnMapTagToStyleCmdBoss, kXMLPrefix + 44)
DECLARE_PMID(kClassIDSpace, kXMLSchemaConversionProviderBoss, kXMLPrefix + 45)
DECLARE_PMID(kClassIDSpace, kXMLDocumentBoss, kXMLPrefix + 47)
DECLARE_PMID(kClassIDSpace,	kSaveTagListCmdBoss, kXMLPrefix + 48)
DECLARE_PMID(kClassIDSpace,	kLoadTagListCmdBoss, kXMLPrefix + 49)
DECLARE_PMID(kClassIDSpace, kSBOSPageBoss_Obsolete, kXMLPrefix + 50)
DECLARE_PMID(kClassIDSpace, kXMLSetCommentCmdBoss, kXMLPrefix + 51)
DECLARE_PMID(kClassIDSpace, kTextXMLElementBoss, kXMLPrefix + 52)
DECLARE_PMID(kClassIDSpace, kXMLCreateElementCmdBoss, kXMLPrefix + 53)
DECLARE_PMID(kClassIDSpace, kPrivateXMLSetTextIndexIDRangeCmdBoss, kXMLPrefix + 54)
DECLARE_PMID(kClassIDSpace, kXMLLinksChangedResponderBoss, kXMLPrefix + 55)
DECLARE_PMID(kClassIDSpace, kXMLLinkToStructureCmdBoss, kXMLPrefix + 56)
DECLARE_PMID(kClassIDSpace, kXMLDeleteCleanupBoss, kXMLPrefix + 57)
DECLARE_PMID(kClassIDSpace, kXMLTextPreProcessBoss, kXMLPrefix + 58)
DECLARE_PMID(kClassIDSpace, kXMLDeleteElementCmdBoss, kXMLPrefix + 59)
DECLARE_PMID(kClassIDSpace, kXMLCopyStyleToTagMapCmdBoss, kXMLPrefix + 60)
DECLARE_PMID(kClassIDSpace, kXMLCopyTagToStyleMapCmdBoss, kXMLPrefix + 61)
DECLARE_PMID(kClassIDSpace, kXMLNewStoryResponderBoss, kXMLPrefix + 62)
DECLARE_PMID(kClassIDSpace, kXMLCreateXMLDocElemCmdBoss, kXMLPrefix + 63)
DECLARE_PMID(kClassIDSpace, kXMLIteratorRegBoss, kXMLPrefix + 64)
DECLARE_PMID(kClassIDSpace, kXMLScrapHandlerBoss, kXMLPrefix + 65)
DECLARE_PMID(kClassIDSpace, kXMLCreateStyleToTagElementsCmdBoss, kXMLPrefix + 66)
DECLARE_PMID(kClassIDSpace, kChangeXMLExportOptionsCmdBoss, kXMLPrefix + 67)
DECLARE_PMID(kClassIDSpace, kChangeXMLImportOptionsCmdBoss, kXMLPrefix + 68)
DECLARE_PMID(kClassIDSpace, kPrivateXMLNewSBOSIDCmdBoss, kXMLPrefix + 69)
DECLARE_PMID(kClassIDSpace, kXMLTagUIDConverterBoss, kXMLPrefix + 70)
DECLARE_PMID(kClassIDSpace, kXMLDeleteUnusedTagsCmdBoss, kXMLPrefix + 71)
DECLARE_PMID(kClassIDSpace, kXMLPlaceElementCmdBoss, kXMLPrefix + 72)
DECLARE_PMID(kClassIDSpace, kXMLUnplaceElementCmdBoss, kXMLPrefix + 73)
DECLARE_PMID(kClassIDSpace, kXMLErrorStringServiceBoss, kXMLPrefix + 74)
DECLARE_PMID(kClassIDSpace, kXMLSetStyleToTagOptionsCmdBoss, kXMLPrefix + 75)

// XML Structure Selection Type
//DECLARE_PMID(kClassIDSpace, kXMLStructureISuiteBoss, kXMLPrefix + 76)
DECLARE_PMID(kClassIDSpace, kXMLStructureSelectionBoss, kXMLPrefix + 77)
DECLARE_PMID(kClassIDSpace,	kXMLStructureSelectionServiceBoss, kXMLPrefix + 78)
DECLARE_PMID(kClassIDSpace, kXMLRepeatTextElementsMatchMakerServiceBoss, kXMLPrefix + 79)
DECLARE_PMID(kClassIDSpace,	kXMLStructureSuiteBoss, kXMLPrefix + 80)

DECLARE_PMID(kClassIDSpace, kXMLMergeStoriesResponderBoss, kXMLPrefix + 81)
DECLARE_PMID(kClassIDSpace, kXMLExportPrefsScriptProviderBoss, kXMLPrefix + 82)
DECLARE_PMID(kClassIDSpace, kXMLSetPICmdBoss, kXMLPrefix + 83)
DECLARE_PMID(kClassIDSpace, kXMLImportPrefsScriptProviderBoss, kXMLPrefix + 84)
DECLARE_PMID(kClassIDSpace, kXMLSetDOCTYPERootCmdBoss, kXMLPrefix + 85)
DECLARE_PMID(kClassIDSpace, kPrivateXMLSetElementEndMarkerCmdBoss, kXMLPrefix + 86)
DECLARE_PMID(kClassIDSpace, kXMLPrivateCopyFrameCmdBoss, kXMLPrefix + 87)
DECLARE_PMID(kClassIDSpace, kXMLDeleteTextResponderBoss, kXMLPrefix + 88)
DECLARE_PMID(kClassIDSpace, kXMLUserEditTextResponderBoss, kXMLPrefix + 89)
DECLARE_PMID(kClassIDSpace, kXMLValidationErrorScriptBoss, kXMLPrefix + 90)
DECLARE_PMID(kClassIDSpace, kXMLApplyTagToStyleMappingCmdBoss, kXMLPrefix + 91)
DECLARE_PMID(kClassIDSpace, kXMLCodeConversionBoss, kXMLPrefix + 92)
DECLARE_PMID(kClassIDSpace, kXMLTagListScriptProviderBoss, kXMLPrefix + 93)
DECLARE_PMID(kClassIDSpace, kXMLStrandPastePieceBoss, kXMLPrefix + 94)
DECLARE_PMID(kClassIDSpace, kXMLDTDPkgContentHandlerBoss, kXMLPrefix + 95)
DECLARE_PMID(kClassIDSpace, kXMLDuplicateElementsCmdBoss, kXMLPrefix + 96)
DECLARE_PMID(kClassIDSpace, kXMLDeleteElementAndContentCmdBoss, kXMLPrefix + 97)
DECLARE_PMID(kClassIDSpace, kChangeXMLExportSOptionsCmdBoss, kXMLPrefix + 98)
DECLARE_PMID(kClassIDSpace, kAssociatedXMLScriptProviderBoss, kXMLPrefix + 99)
DECLARE_PMID(kClassIDSpace, kXMLSetAttributeNameCmdBoss, kXMLPrefix + 100)
DECLARE_PMID(kClassIDSpace, kPrivateXMLSetContentItemCmdBoss, kXMLPrefix + 101)
DECLARE_PMID(kClassIDSpace, kPrivateXMLSetXMLReferenceDataCmdBoss, kXMLPrefix + 102)
DECLARE_PMID(kClassIDSpace, kPrivateXMLElementToInlineCmdBoss, kXMLPrefix + 103)
DECLARE_PMID(kClassIDSpace, kXMLOutFileStreamBoss, kXMLPrefix + 104)
DECLARE_PMID(kClassIDSpace, kXMLOutPMStreamBoss, kXMLPrefix + 105)
DECLARE_PMID(kClassIDSpace, kXMLTextLinkResponderBoss, kXMLPrefix + 106)
DECLARE_PMID(kClassIDSpace, kXMLDuplicateTagsCmdBoss, kXMLPrefix + 107)
DECLARE_PMID(kClassIDSpace, kXMLCreateTableElementCmdBoss, kXMLPrefix + 108)
DECLARE_PMID(kClassIDSpace, kXMLCreatePICmdBoss, kXMLPrefix + 109)
DECLARE_PMID(kClassIDSpace, kXMLLinkCmdResponderBoss, kXMLPrefix + 110)
DECLARE_PMID(kClassIDSpace, kXMLPIBoss, kXMLPrefix + 111)
DECLARE_PMID(kClassIDSpace, kXMLRangeDeleteElementCmdBoss, kXMLPrefix + 112)
DECLARE_PMID(kClassIDSpace, kXMLPasteElementMsg, kXMLPrefix + 113) //On broadcast, changedBy is XMLReference* of new element
DECLARE_PMID(kClassIDSpace, kXMLSetTagColorCmdBoss, kXMLPrefix + 114)
//gap
DECLARE_PMID(kClassIDSpace, kXMLItemProxyScriptObjectBoss, kXMLPrefix + 116)
DECLARE_PMID(kClassIDSpace, kXMLCountElementsHandlerBoss, kXMLPrefix + 117)
DECLARE_PMID(kClassIDSpace, kXMLImageHandlerBoss, kXMLPrefix + 118)
DECLARE_PMID(kClassIDSpace, kXMLMementoBoss, kXMLPrefix + 119)
DECLARE_PMID(kClassIDSpace, kXMLMergeStoriesPreCmdBoss, kXMLPrefix + 120)
DECLARE_PMID(kClassIDSpace, kXMLMergeStoriesPostCmdBoss, kXMLPrefix + 121)
//DECLARE_PMID(kClassIDSpace, kMyFancyNewBoss, kXMLPrefix + 122)
DECLARE_PMID(kClassIDSpace, kSAXDocumentHandlerBoss, kXMLPrefix + 123)
DECLARE_PMID(kClassIDSpace, kSAXTagListHandlerBoss, kXMLPrefix + 124)
DECLARE_PMID(kClassIDSpace, kXMLCommentScriptProviderBoss, kXMLPrefix + 125)
DECLARE_PMID(kClassIDSpace, kXMLSetTableCellXMLRefDataCmdLetBoss, kXMLPrefix + 126)
DECLARE_PMID(kClassIDSpace, kXMLDeleteCharStyleCmdResponderBoss, kXMLPrefix + 127)
DECLARE_PMID(kClassIDSpace, kXMLLoadDTDCmdBoss, kXMLPrefix + 128)
DECLARE_PMID(kClassIDSpace, kXMLLoadDTDCmdDataBoss, kXMLPrefix + 129)
DECLARE_PMID(kClassIDSpace, kXMLLoadDTDHandlerBoss, kXMLPrefix + 130)
DECLARE_PMID(kClassIDSpace, kXMLDTDBoss, kXMLPrefix + 131)
DECLARE_PMID(kClassIDSpace, kXMLCreateDTDCmdBoss, kXMLPrefix + 132)
DECLARE_PMID(kClassIDSpace, kXMLCreateDTDCmdDataBoss, kXMLPrefix + 133)
DECLARE_PMID(kClassIDSpace, kXMLSetDFAStateCmdBoss, kXMLPrefix + 134)
DECLARE_PMID(kClassIDSpace, kXMLDTDTokenHandlerBoss, kXMLPrefix + 135)
DECLARE_PMID(kClassIDSpace, kXMLReplaceDTDCmdBoss, kXMLPrefix + 136)
DECLARE_PMID(kClassIDSpace, kXMLRubyBoss, kXMLPrefix + 137)
DECLARE_PMID(kClassIDSpace, kXMLValidationErrorScriptProviderBoss, kXMLPrefix + 138)
DECLARE_PMID(kClassIDSpace, kXMLImportDTDPkgXMLCmdBoss, kXMLPrefix + 139)
DECLARE_PMID(kClassIDSpace, kXMLTableContentHandlerBoss, kXMLPrefix + 140)
DECLARE_PMID(kClassIDSpace, kXMLRubyContentHandlerBoss, kXMLPrefix + 141)
DECLARE_PMID(kClassIDSpace, kXMLPIScriptProviderBoss, kXMLPrefix + 142)
DECLARE_PMID(kClassIDSpace, kXMLDTDPkgEntityResolverBoss, kXMLPrefix + 143)
DECLARE_PMID(kClassIDSpace, kXMLMapTagToStyleMappingCmdBoss, kXMLPrefix + 144)
DECLARE_PMID(kClassIDSpace, kXMLContentScriptProviderBoss, kXMLPrefix + 145)
DECLARE_PMID(kClassIDSpace, SetDTDEncodeingSettingCmdBoss, kXMLPrefix + 146)
DECLARE_PMID(kClassIDSpace, kXMLDTDScriptProviderBoss, kXMLPrefix + 147)
DECLARE_PMID(kClassIDSpace, kXMLStoryScriptProviderBoss, kXMLPrefix + 148)
DECLARE_PMID(kClassIDSpace, kXMLTableTagContentHandlerBoss, kXMLPrefix + 149)
DECLARE_PMID(kClassIDSpace, kXMLMoveElementMarkersCmdBoss, kXMLPrefix + 150)
DECLARE_PMID(kClassIDSpace, kXMLPostPasteFixupCmdBoss, kXMLPrefix + 151)
DECLARE_PMID(kClassIDSpace, kXMLDeleteTextCmdBoss, kXMLPrefix + 152)
DECLARE_PMID(kClassIDSpace, kXMLUpdateLinkServiceProviderBoss, kXMLPrefix + 153)
DECLARE_PMID(kClassIDSpace, kXMLSetTableXMLRefDataCmdLetBoss, kXMLPrefix + 154)
DECLARE_PMID(kClassIDSpace, kXMLImportDefaultMatchMakerServiceBoss, kXMLPrefix + 155)
DECLARE_PMID(kClassIDSpace, kImportXMLDataBoss, kXMLPrefix + 156)
DECLARE_PMID(kClassIDSpace, kXMLAcquirerTextFilterServiceProviderBoss, kXMLPrefix + 157)
DECLARE_PMID(kClassIDSpace, kXMLImporterBoss, kXMLPrefix + 158)
DECLARE_PMID(kClassIDSpace, kXMLPostImportIterationServiceBoss, kXMLPrefix + 159)
DECLARE_PMID(kClassIDSpace, kXMLImporterPostImportMappingBoss, kXMLPrefix + 160)
DECLARE_PMID(kClassIDSpace, kXMLImporterPostImportSignalMgrBoss, kXMLPrefix + 161)
DECLARE_PMID(kClassIDSpace, kXMLLinkingPostImportResponderBoss, kXMLPrefix + 162)
DECLARE_PMID(kClassIDSpace, kXMLElementBaseBoss, kXMLPrefix + 163)
// DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 164)
DECLARE_PMID(kClassIDSpace, kXMLThrowAwayUnmatchedRightMatchMakerServiceBoss, kXMLPrefix + 165)
DECLARE_PMID(kClassIDSpace, kXMLThrowAwayUnmatchedLeftMatchMakerServiceBoss, kXMLPrefix + 166)
DECLARE_PMID(kClassIDSpace, kXMLStripWhitespacesTransformServiceBoss, kXMLPrefix + 167)
DECLARE_PMID(kClassIDSpace, kXMLCellContentMgrNotificationsPasteCmdBoss, kXMLPrefix + 168)
DECLARE_PMID(kClassIDSpace, kXMLImportTreeTransRuleProcBoss, kXMLPrefix + 169)
DECLARE_PMID(kClassIDSpace, kXMLTableMatchMakerServiceBoss, kXMLPrefix + 170)
DECLARE_PMID(kClassIDSpace, kXMLImportOptionsPoolContentHandlerBoss, kXMLPrefix + 171)
DECLARE_PMID(kClassIDSpace, kXMLDeleteElementContentCmdBoss, kXMLPrefix + 172)
DECLARE_PMID(kClassIDSpace, kSetBoolValueCmdBoss, kXMLPrefix + 173)
DECLARE_PMID(kClassIDSpace, kXMLSnippetMatchMakerServiceBoss, kXMLPrefix + 174)
DECLARE_PMID(kClassIDSpace, kXSLTransformerPIBoss, kXMLPrefix + 175)
DECLARE_PMID(kClassIDSpace, kXMLTableMementoPieceTransferToCmdBoss, kXMLPrefix + 176)
DECLARE_PMID(kClassIDSpace, kSetGeneralXMLPreferencesCmdBoss, kXMLPrefix + 177)
DECLARE_PMID(kClassIDSpace, kXMLRulesProcessorScriptProviderBoss, kXMLPrefix + 178)
DECLARE_PMID(kClassIDSpace, kXMLPreferencesScriptProviderBoss, kXMLPrefix + 179)
DECLARE_PMID(kClassIDSpace, kXMLPrivateAdjustGridCmdBoss, kXMLPrefix + 180)
DECLARE_PMID(kClassIDSpace, kXMLSetTableTagPreferenceCmdBoss, kXMLPrefix + 181)
DECLARE_PMID(kClassIDSpace, kXMLSparseImportOptionsServiceBoss, kXMLPrefix + 182)
DECLARE_PMID(kClassIDSpace, kXMLRubyAndDtTableMatchMakerServiceBoss, kXMLPrefix + 183)
DECLARE_PMID(kClassIDSpace, kRuleSetListBoss, kXMLPrefix + 184)
DECLARE_PMID(kClassIDSpace, kXMLRulesProcessorBoss, kXMLPrefix + 185)
DECLARE_PMID(kClassIDSpace, kXMLTestExportHandlerBoss, kXMLPrefix + 186)
DECLARE_PMID(kClassIDSpace, kXMLSampleRuleSetListBoss, kXMLPrefix + 187)
DECLARE_PMID(kClassIDSpace, kXMLRulesCloseDocResponderBoss, kXMLPrefix + 188)

// For table/cell styles

DECLARE_PMID(kClassIDSpace, kXMLDeleteCellStyleCmdResponderBoss, kXMLPrefix + 189)
DECLARE_PMID(kClassIDSpace, kXMLDeleteTableStyleCmdResponderBoss, kXMLPrefix + 190)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 191)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 192)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 193)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 194)
DECLARE_PMID(kClassIDSpace, kXMLPostImportApplyRuleSetResponderBoss, kXMLPrefix + 195)

DECLARE_PMID(kClassIDSpace, kTestParserContentHandlerBoss, kXMLPrefix + 196)
DECLARE_PMID(kClassIDSpace,		kDropXMLElementCmdBoss,				kXMLPrefix + 197)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 198)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 199)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 200)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 201)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 202)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 203)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 204)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 205)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 206)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 207)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 208)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 209)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 210)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 211)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 212)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 213)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 214)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 215)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 216)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 217)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 218)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 219)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 220)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 221)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 222)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 223)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 224)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 225)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 226)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 227)
//DECLARE_PMID(kClassIDSpace, kXMLFutureBoss, kXMLPrefix + 228)
DECLARE_PMID(kClassIDSpace, kXSLTDTDContentHandlerBoss, kXMLPrefix + 229)
DECLARE_PMID(kClassIDSpace, kXMLRuleMatchDataScriptProviderBoss, kXMLPrefix + 230)
DECLARE_PMID(kClassIDSpace, kXMLRuleMatchDataScriptBoss, kXMLPrefix + 231)
DECLARE_PMID(kClassIDSpace, kXMLRulesElementScriptProviderBoss, kXMLPrefix + 232)
DECLARE_PMID(kClassIDSpace, kXMLConvertElementToInlineCmdBoss, kXMLPrefix + 233)
DECLARE_PMID(kClassIDSpace, kExportForWebScript50ProviderBoss, kXMLPrefix + 234)
DECLARE_PMID(kClassIDSpace, kExportForWebPrefsScriptProviderBoss, kXMLPrefix + 235)
DECLARE_PMID(kClassIDSpace, kXMLSetTagRoleCmdBoss, kXMLPrefix + 236)
DECLARE_PMID(kClassIDSpace, kXMLConvertElementToTableCmdBoss, kXMLPrefix + 237)
DECLARE_PMID(kClassIDSpace, kXMLRelinkContentCmdBoss, kXMLPrefix + 238)
DECLARE_PMID(kClassIDSpace, kItemAndBelowPrintDrawEventBoss, kXMLPrefix + 239)
DECLARE_PMID(kClassIDSpace, kSetDeleteElementOnContentDeletePrefCmdBoss, kXMLPrefix + 240)

// <Interface ID>
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLCREATETABLEELEMENTCMDDATA, kXMLPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLCOMMENTBODYSTRINGDATA, kXMLPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLCREATETAGCMDDATA, kXMLPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLSETELEMENTTAGCMDDATA, kXMLPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLCREATEELEMENTCMDDATA, kXMLPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLHIERARCHYCMDDATA, kXMLPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IIDXMLELEMENT, kXMLPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLREFERENCEDATA, kXMLPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLHANDLER, kXMLPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLGENERATOR, kXMLPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLACCESS, kXMLPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLTAGLIST, kXMLPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLATTRIBUTECMDDATA, kXMLPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLSTRAND, kXMLPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLSTRANDCONTROLLER, kXMLPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_ILSIDMANAGER, kXMLPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IXREFERENCELSID, kXMLPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLDELETEELEMENTCMDDATA, kXMLPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLSOURCEELEMENT, kXMLPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLSAVEELEMENT, kXMLPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLTAG, kXMLPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLSTYLETOTAGMAP, kXMLPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLMAPPINGCMDDATA, kXMLPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLTAGTOSTYLEMAP, kXMLPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOMHANDLER, kXMLPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLREFERENCEDATA2, kXMLPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLLOADDTDCMDDATA, kXMLPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLEXPORTALERTSTATE, kXMLPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLUTILS, kXMLPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLREFERENCELISTDATA, kXMLPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLSCRIPTUTILS, kXMLPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRAPXMLELEMENTUIDDATA, kXMLPrefix + 32)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLXFERELEMENTCMDDATA, kXMLPrefix + 33)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLCREATESTYLETOTAGELEMENTSCMDDATA, kXMLPrefix + 34)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLMOVEELEMENTCMDDATA, kXMLPrefix + 35)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLTARGET, kXMLPrefix + 36)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLEXPORTOPTIONS, kXMLPrefix + 37)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLEXPORTHANDLERDATA, kXMLPrefix + 38)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLIMPORTOPTIONS, kXMLPrefix + 39)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLNODETARGET, kXMLPrefix + 40)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLNODESELECTIONSUITE, kXMLPrefix + 41)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLNODELISTDATA, kXMLPrefix + 42)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLCONTROLDATA, kXMLPrefix + 43)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLSTRUCTURESUITE, kXMLPrefix + 44)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLEXPANDLINKELEMENTCONTENT, kXMLPrefix + 45)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTSCRAPHANDLER, kXMLPrefix + 46)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEITEMSCRAPHANDLER, kXMLPrefix + 47)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLELEMENTCOMMANDS, kXMLPrefix + 48)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLELEMENTPRIVATECOMMANDS, kXMLPrefix + 49)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLDUPELEMENTSCMDDATA, kXMLPrefix + 50)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLEXPORTSESSIONOPTIONS, kXMLPrefix + 51)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLOUTSTREAM, kXMLPrefix + 52)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLSTREAMUTILS, kXMLPrefix + 53)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORPERSISTUIDDATA, kXMLPrefix + 54)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLPRIVATEUTILS, kXMLPrefix + 55)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLVALIDATIONERROR, kXMLPrefix + 56)
DECLARE_PMID(kInterfaceIDSpace, IID_IPMSTRINGMAPDATA, kXMLPrefix + 57)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLPITARGET, kXMLPrefix + 58)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLPIDATA, kXMLPrefix + 59)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLATTRIBUTECOMMANDS, kXMLPrefix + 60)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLTAGCOMMANDS, kXMLPrefix + 61)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLDELETETAGCMDDATA, kXMLPrefix + 62)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLMAPPINGCOMMANDS, kXMLPrefix + 63)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLCOPYMAPPINGCMDDATA, kXMLPrefix + 64)
DECLARE_PMID(kInterfaceIDSpace, IID_ICURRENTTAGCOLORINTDATA, kXMLPrefix + 65)
DECLARE_PMID(kInterfaceIDSpace, IID_XMLCOPYMAP, kXMLPrefix + 66)
DECLARE_PMID(kInterfaceIDSpace, IID_XMLOPTIMIZEDMAP, kXMLPrefix + 67)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLFORMATTEDMAPDATA, kXMLPrefix + 68)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLEXPORTUTILS, kXMLPrefix + 69)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRAPXMLELEMENTUIDDATA2, kXMLPrefix + 70)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLIMAGEHANDLERDATA, kXMLPrefix + 71)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLSTRANDDELETEBOOLDATA, kXMLPrefix + 72)
DECLARE_PMID(kInterfaceIDSpace, IID_ISAXDOCUMENTHANDLERDATA, kXMLPrefix + 73)
DECLARE_PMID(kInterfaceIDSpace, IID_IVERIFYCOMMAND, kXMLPrefix + 74)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLDTDPRIVATE, kXMLPrefix + 75)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLIMPORTMATCHDRIVER, kXMLPrefix + 76)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLCREATEDTDCMDDATA, kXMLPrefix + 77)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLELEMENTDTDINFO, kXMLPrefix + 78)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLDTDXMLREFERENCEDATA, kXMLPrefix + 79)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLDTDINSERTELEMENTLISTDATA, kXMLPrefix + 80)
DECLARE_PMID(kInterfaceIDSpace, IID_IERRORSTATEDATA, kXMLPrefix + 81)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLDTDREPLACEELEMENTLISTDATA, kXMLPrefix + 82)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLTESTSUITE, kXMLPrefix + 83)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLTABLEPARSINGCONTEXT, kXMLPrefix + 84)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLEXPORTIMAGEOPTIONSIID, kXMLPrefix + 85)	// used in ChangeXMLExportOptionsCmd for kInterfaceDataImpl.
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLEXPORTVIEWEROPTIONSIID, kXMLPrefix + 86)	// used in ChangeXMLExportSOptionsCmd for kInterfaceDataImpl.
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLVALIDATOR, kXMLPrefix + 87)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTYLESHEETDATA, kXMLPrefix + 88)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLDTDPKGCONTENTDATA, kXMLPrefix + 89)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLINTERNALSUBSETSTRING, kXMLPrefix + 90)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLEXTERNALSUBSETSTRING, kXMLPrefix + 91)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLEXPORTPREFSSCRIPTOBJECTID, kXMLPrefix + 92)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLEXPORTPREFSSCRIPTPROPID, kXMLPrefix + 93)
DECLARE_PMID(kInterfaceIDSpace, IID_ISOURCEXMLTAGSDATA, kXMLPrefix + 94)
DECLARE_PMID(kInterfaceIDSpace, IID_IDESTXMLTAGSDATA, kXMLPrefix + 95)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMPORTXMLDATA, kXMLPrefix + 96)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLACQUIRERFILTER, kXMLPrefix + 97)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLIMPORTMATCHRECORDER, kXMLPrefix + 98)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLIMPORTER, kXMLPrefix + 99)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLTRANSFORMER, kXMLPrefix + 100)
DECLARE_PMID(kInterfaceIDSpace, IID_IPOSTIMPORTRESPONDERDATA, kXMLPrefix + 101)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLIMPORTMATCHMAKER, kXMLPrefix + 102)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLPOSTIMPORTITERATION, kXMLPrefix + 103)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLIMPORTOPTIONSPOOL, kXMLPrefix + 104)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLCELLCONTENTMGRNOTIFICATIONSPASTECMDDATA, kXMLPrefix + 105)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLIMPORTPREFERENCES, kXMLPrefix + 106)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLTEST, kXMLPrefix + 107)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLCSB_BROADCAST, kXMLPrefix + 108)		// Broadcast only
DECLARE_PMID(kInterfaceIDSpace, IID_IGENERALXMLPREFERENCES, kXMLPrefix + 109)
DECLARE_PMID(kInterfaceIDSpace, IID_ISHOWIMPORTOPTIONSBOOL, kXMLPrefix + 110)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETBOOLCMDDATA, kXMLPrefix + 111)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLTARIMPORTPREFERENCES, kXMLPrefix + 112)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLIMPORTERDOM, kXMLPrefix + 113)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLIMPORTPREFERENCES2, kXMLPrefix + 114)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLRULESPROCESSORMGR, kXMLPrefix + 115)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLEXPORTHANDLER, kXMLPrefix + 116)
DECLARE_PMID(kInterfaceIDSpace, IID_IIDXMLATTRIBUTE, kXMLPrefix + 117)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLADJUSTGRIDCMDDATA, kXMLPrefix + 118)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLTABLETAGPREFERENCEDATA, kXMLPrefix + 120)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLRELINKCONTENTCMDDATA, kXMLPrefix + 121)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLCONVERTELEMENTTOINLINECMDDATA, kXMLPrefix + 122)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLCONVERTELEMENTTOTABLECMDDATA, kXMLPrefix + 123)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLDELETEELEMENTOBJECTBOOLDATA, kXMLPrefix + 124)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLSTYLETOTAGOPTIONSDATA, kXMLPrefix + 125)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLRULESPROCESSOR, kXMLPrefix + 126)
DECLARE_PMID(kInterfaceIDSpace, IID_ITESTPARSERLOG, kXMLPrefix + 127)
//DECLARE_PMID(kInterfaceIDSpace, IID_IXMLFUTUREINTERFACE, kXMLPrefix + 128)
DECLARE_PMID(kInterfaceIDSpace, IID_IRULEACTIONLIST, kXMLPrefix + 129)
DECLARE_PMID(kInterfaceIDSpace, IID_ICREATERULESETCMDDATA, kXMLPrefix + 130)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLIMPORTCALSPREFERENCES, kXMLPrefix + 131)
//DECLARE_PMID(kInterfaceIDSpace, IID_IXMLFUTUREINTERFACE, kXMLPrefix + 132)
//DECLARE_PMID(kInterfaceIDSpace, IID_IXMLFUTUREINTERFACE, kXMLPrefix + 133)
//DECLARE_PMID(kInterfaceIDSpace, IID_IXMLFUTUREINTERFACE, kXMLPrefix + 134)
//DECLARE_PMID(kInterfaceIDSpace, IID_IXMLFUTUREINTERFACE, kXMLPrefix + 135)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLCONDITIONREPORT, kXMLPrefix + 136)
//DECLARE_PMID(kInterfaceIDSpace, IID_IXMLFUTUREINTERFACE, kXMLPrefix + 137)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLRULESCHANGED, kXMLPrefix + 138)
//DECLARE_PMID(kInterfaceIDSpace, IID_IXMLFUTUREINTERFACE, kXMLPrefix + 139)
//DECLARE_PMID(kInterfaceIDSpace, IID_IXMLFUTUREINTERFACE, kXMLPrefix + 140)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLSTRUCTUREITERATORMANAGER, kXMLPrefix + 141)


DECLARE_PMID(kInterfaceIDSpace, IID_IXMLRULEMATCHDATA, kXMLPrefix + 142)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLRULEACTIONFACADE, kXMLPrefix + 143)
DECLARE_PMID(kInterfaceIDSpace, IID_IEXPORTFORWEBPREFERENCES, kXMLPrefix + 144)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLEXPORTSPREFSCRIPTPROVIDER, kXMLPrefix + 145)
DECLARE_PMID(kInterfaceIDSpace, IID_IDELETE_ELEMENT_ON_CONTENT_DELETE_PREF, kXMLPrefix + 146)

//DECLARE_PMID(kInterfaceIDSpace, IID_IXMLFUTUREINTERFACE, kXMLPrefix + 147)
//DECLARE_PMID(kInterfaceIDSpace, IID_IXMLFUTUREINTERFACE, kXMLPrefix + 148)
//DECLARE_PMID(kInterfaceIDSpace, IID_IXMLFUTUREINTERFACE, kXMLPrefix + 149)
//DECLARE_PMID(kInterfaceIDSpace, IID_IXMLFUTUREINTERFACE, kXMLPrefix + 150)

// <Service ID>
DECLARE_PMID(kServiceIDSpace, kXMLContentHandlerService, kXMLPrefix + 1)
DECLARE_PMID(kServiceIDSpace, kXMLTagHandlerService, kXMLPrefix + 2)
DECLARE_PMID(kServiceIDSpace, kAcquireXMLService, kXMLPrefix + 3)
DECLARE_PMID(kServiceIDSpace, kXMLImporterTransformerService, kXMLPrefix + 4)
DECLARE_PMID(kServiceIDSpace, kXMLImporterPostImportMappingService, kXMLPrefix + 5)
DECLARE_PMID(kServiceIDSpace, kXMLImporterPostImportService, kXMLPrefix + 6)
DECLARE_PMID(kServiceIDSpace, kXMLImportMatchMakerSignalService, kXMLPrefix + 7)
DECLARE_PMID(kServiceIDSpace, kXMLPostImportIterationService, kXMLPrefix + 8)
DECLARE_PMID(kServiceIDSpace, kXMLExportHandlerSignalService, kXMLPrefix + 9)
//DECLARE_PMID(kServiceIDSpace, kXMLFutureService, kXMLPrefix + 10)
DECLARE_PMID(kServiceIDSpace, kRuleConditionService, kXMLPrefix + 11)
DECLARE_PMID(kServiceIDSpace, kRuleActionService, kXMLPrefix + 12)
//DECLARE_PMID(kServiceIDSpace, kXMLFutureService, kXMLPrefix + 13)
//DECLARE_PMID(kServiceIDSpace, kXMLFutureService, kXMLPrefix + 14)
//DECLARE_PMID(kServiceIDSpace, kXMLFutureService, kXMLPrefix + 15)
//DECLARE_PMID(kServiceIDSpace, kXMLFutureService, kXMLPrefix + 16)
//DECLARE_PMID(kServiceIDSpace, kXMLFutureService, kXMLPrefix + 17)
//DECLARE_PMID(kServiceIDSpace, kXMLFutureService, kXMLPrefix + 18)
//DECLARE_PMID(kServiceIDSpace, kXMLFutureService, kXMLPrefix + 19)
//DECLARE_PMID(kServiceIDSpace, kXMLFutureService, kXMLPrefix + 20)
//DECLARE_PMID(kServiceIDSpace, kXMLFutureService, kXMLPrefix + 21)
//DECLARE_PMID(kServiceIDSpace, kXMLFutureService, kXMLPrefix + 22)
//DECLARE_PMID(kServiceIDSpace, kXMLFutureService, kXMLPrefix + 23)
//DECLARE_PMID(kServiceIDSpace, kXMLFutureService, kXMLPrefix + 24)
//DECLARE_PMID(kServiceIDSpace, kXMLFutureService, kXMLPrefix + 25)


// <Implementation ID>
DECLARE_PMID(kImplementationIDSpace, kXMLDTDGeneratorImpl, kXMLPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kXMLSetExpandLinkElementsCmdImpl, kXMLPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kXMLScriptUtilsImpl, kXMLPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kXMLPhase2ConversionImpl, kXMLPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kXMLCommentGeneratorImpl, kXMLPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kXMLCopyTableElementCmdImpl, kXMLPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kXMLCreateCommentCmdImpl, kXMLPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kXMLInsertMarkerCmdImpl, kXMLPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kXMLExportProviderImpl, kXMLPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kXMLExportHandlerImpl, kXMLPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kXMLCreateElementCmdDataImpl, kXMLPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kXMLCreateXMLDocElemCmdImpl, kXMLPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kXMLElementImpl, kXMLPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kXMLHierarchyCmdDataImpl, kXMLPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kXMLSetElementTagCmdImpl, kXMLPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kXMLSetElementTagCmdDataImpl, kXMLPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kXMLAttachElementCmdImpl, kXMLPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kXMLDocElemGeneratorImpl, kXMLPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kXMLNewDocResponderImpl, kXMLPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kXMLReferenceDataImpl, kXMLPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kXMLAccessImpl, kXMLPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kXMLDetachElementCmdImpl, kXMLPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kXMLMoveElementCmdImpl, kXMLPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kXMLElementScriptProviderImpl, kXMLPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kXMLElementScriptImpl, kXMLPrefix + 25)	// persistent implID required for conversion
DECLARE_PMID(kImplementationIDSpace, kImportXMLFileCmdImpl, kXMLPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kXMLImportScriptProviderImpl, kXMLPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kXMLDeleteParaStyleCmdResponderImpl, kXMLPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kXMLPrivateUtilsImpl, kXMLPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kXMLDocScriptProviderImpl, kXMLPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kXMLDeleteMarkerCmdImpl, kXMLPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kXMLTextGeneratorImpl, kXMLPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kXMLTagListImpl, kXMLPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kXMLAttributeScriptProviderImpl, kXMLPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kXMLCreateAttributeCmdImpl, kXMLPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kXMLDeleteAttributeCmdImpl, kXMLPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kXMLSetAttributeValueCmdImpl, kXMLPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kXMLAttributeCmdDataImpl, kXMLPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kXMLTagScriptProviderImpl, kXMLPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kXMLCreateTagCmdImpl, kXMLPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kXMLDeleteTagCmdImpl, kXMLPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kXMLSetTagNameCmdImpl, kXMLPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kXMLReferenceData2Impl, kXMLPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kXMLSetCommentCmdImpl, kXMLPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kXMLDeleteCharStyleCmdResponderImpl, kXMLPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kXMLDeleteStoryCmdResponderImpl, kXMLPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kXMLTagImpl, kXMLPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kXMLTagScriptImpl, kXMLPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kXMLStrandImpl, kXMLPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kXMLCommentBodyStringDataImpl, kXMLPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kXMLCreateTagCmdDataImpl, kXMLPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kXMLIteratorRegImpl, kXMLPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kXMLDeleteElementCmdDataImpl, kXMLPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kXMLMoveElementCmdDataImpl, kXMLPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kXMLCreateStyleToTagElementsCmdImpl, kXMLPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kXMLNewSBOSIDCmdImpl, kXMLPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kXMLSetPICmdImpl, kXMLPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kSaveXMLElementImpl, kXMLPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kSourceXMLElementImpl, kXMLPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kXMLTagUIDConverterImpl, kXMLPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kXMLStyleToTagMapImpl, kXMLPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kXMLStyleToTagScriptProviderImpl, kXMLPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kXMLSetDOCTYPERootCmdImpl, kXMLPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kXMLTagListScriptProviderImpl, kXMLPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kXMLMapStyleToTagCmdImpl, kXMLPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kXMLUnMapStyleToTagCmdImpl, kXMLPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kXMLXferElementCmdImpl, kXMLPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kXMLMappingCmdDataImpl, kXMLPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kXMLTagToStyleMapImpl, kXMLPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kXMLTagToStyleScriptProviderImpl, kXMLPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kXMLValidationErrorScriptProviderImpl, kXMLPrefix + 71)
//gap
DECLARE_PMID(kImplementationIDSpace, kXMLMapTagToStyleCmdImpl, kXMLPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kXMLUnMapTagToStyleCmdImpl, kXMLPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kXMLXferElementCmdDataImpl, kXMLPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kXMLElementCSB_ScriptSuiteImpl, kXMLPrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kXMLDeleteUnusedTagsCmdImpl, kXMLPrefix + 77)
DECLARE_PMID(kImplementationIDSpace, kXMLTableGeneratorImpl, kXMLPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kGeneralXMLPreferencesImpl, kXMLPrefix + 79)
DECLARE_PMID(kImplementationIDSpace, kSaveTagListCmdImpl, kXMLPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kLoadTagListCmdImpl, kXMLPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kSBOSMgrImpl_Obsolete, kXMLPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kSBOSPageImpl_Obsolete, kXMLPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kXMLLinkToStructureCmdImpl, kXMLPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kXMLCreateElementCmdImpl, kXMLPrefix + 85)
DECLARE_PMID(kImplementationIDSpace, kXMLTextBasedGeneratorImpl, kXMLPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kXMLReferenceListDataImpl, kXMLPrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kXMLSetTextIndexIDRangeCmdImpl, kXMLPrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kXMLContentScriptProviderImpl, kXMLPrefix + 89)
DECLARE_PMID(kImplementationIDSpace, kXMLErrorStringServiceImpl, kXMLPrefix + 90)
DECLARE_PMID(kImplementationIDSpace, kXMLLinksChangedResponderImpl, kXMLPrefix + 91)
DECLARE_PMID(kImplementationIDSpace, kXMLDeleteCleanupImpl, kXMLPrefix + 92)
DECLARE_PMID(kImplementationIDSpace, kXMLUtilsImpl, kXMLPrefix + 93)
DECLARE_PMID(kImplementationIDSpace, kScrapXMLElementUIDDataImpl, kXMLPrefix + 94)
DECLARE_PMID(kImplementationIDSpace, kXMLTextPreProcessImpl, kXMLPrefix + 95)
DECLARE_PMID(kImplementationIDSpace, kXMLDeleteElementCmdImpl, kXMLPrefix + 96)
DECLARE_PMID(kImplementationIDSpace, kXMLCopyStyleToTagMapCmdImpl, kXMLPrefix + 97)
DECLARE_PMID(kImplementationIDSpace, kXMLCopyTagToStyleMapCmdImpl, kXMLPrefix + 98)
DECLARE_PMID(kImplementationIDSpace, kXMLStyleToTagMapNPImpl, kXMLPrefix + 99)
DECLARE_PMID(kImplementationIDSpace, kXMLTagToStyleMapNPImpl, kXMLPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kXMLNewStoryResponderImpl, kXMLPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kXMLScrapHandlerImpl, kXMLPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kSetGeneralXMLPreferencesCmdImpl, kXMLPrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kXMLExportOptionsImpl, kXMLPrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kChangeXMLExportOptionsCmdImpl, kXMLPrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kXMLExportHandlerDataImpl, kXMLPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kXMLImportOptionsImpl, kXMLPrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kChangeXMLImportOptionsCmdImpl, kXMLPrefix + 108)
DECLARE_PMID(kImplementationIDSpace, kXMLPlaceElementCmdImpl, kXMLPrefix + 109)
DECLARE_PMID(kImplementationIDSpace, kXMLUnplaceElementCmdImpl, kXMLPrefix + 110)
DECLARE_PMID(kImplementationIDSpace, kXMLSetStoryLockStateCmdImpl, kXMLPrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kXMLMergeStoriesResponderImpl, kXMLPrefix + 112)

//XML Selection
DECLARE_PMID(kImplementationIDSpace, kXMLISelectionImpl, kXMLPrefix + 113)
DECLARE_PMID(kImplementationIDSpace, kXMLNodeSelectionSuiteImpl, kXMLPrefix + 114)
DECLARE_PMID(kImplementationIDSpace, kXMLDuplicateTagsCmdImpl, kXMLPrefix + 115)
DECLARE_PMID(kImplementationIDSpace, kXMLReattachElementCmdImpl, kXMLPrefix + 116)
DECLARE_PMID(kImplementationIDSpace, kXMLStructureSuiteASBImpl, kXMLPrefix +117)
DECLARE_PMID(kImplementationIDSpace, kXMLStructureSuiteCSBImpl, kXMLPrefix + 118)
DECLARE_PMID(kImplementationIDSpace, kXMLStrandDeleteBoolDataImpl, kXMLPrefix + 119)
DECLARE_PMID(kImplementationIDSpace, kXMLNodeListDataImpl, kXMLPrefix + 120)
DECLARE_PMID(kImplementationIDSpace, kXMLControlDataImpl, kXMLPrefix +121)
DECLARE_PMID(kImplementationIDSpace, kXMLNodeTargetImpl, kXMLPrefix + 122)
DECLARE_PMID(kImplementationIDSpace, kXMLExportPrefsScriptProviderImpl, kXMLPrefix + 123)
DECLARE_PMID(kImplementationIDSpace, kXMLExportAlertStateImpl, kXMLPrefix + 124)
DECLARE_PMID(kImplementationIDSpace, kXMLImportPrefsScriptProviderImpl, kXMLPrefix + 125)
DECLARE_PMID(kImplementationIDSpace, kXMLItemScriptImpl, kXMLPrefix + 126)
DECLARE_PMID(kImplementationIDSpace, kXMLExpandLinkElementContentImpl, kXMLPrefix + 127)
DECLARE_PMID(kImplementationIDSpace, kXMLSetElementEndMarkerCmdImpl, kXMLPrefix + 128)
DECLARE_PMID(kImplementationIDSpace, kXMLPrivateCopyFrameCmdImpl, kXMLPrefix + 129)
DECLARE_PMID(kImplementationIDSpace, kXMLDeleteTextResponderImpl, kXMLPrefix + 130)
DECLARE_PMID(kImplementationIDSpace, kXMLMappingScriptImpl, kXMLPrefix + 131)
DECLARE_PMID(kImplementationIDSpace, kXMLAttributeScriptImpl, kXMLPrefix + 132)
DECLARE_PMID(kImplementationIDSpace, kXMLCommentScriptProviderImpl, kXMLPrefix + 133)
DECLARE_PMID(kImplementationIDSpace, kXMLApplyTagToStyleMappingCmdImpl, kXMLPrefix + 134)
DECLARE_PMID(kImplementationIDSpace, kXMLElementCommandsImpl, kXMLPrefix + 135)
DECLARE_PMID(kImplementationIDSpace, kVerifyCommandImpl, kXMLPrefix + 136)
DECLARE_PMID(kImplementationIDSpace, kXMLConversionProviderImpl, kXMLPrefix + 137)
DECLARE_PMID(kImplementationIDSpace, kSAXEntityResolverImpl, kXMLPrefix + 138)
DECLARE_PMID(kImplementationIDSpace, kXMLStrandPastePieceImpl, kXMLPrefix + 139)
DECLARE_PMID(kImplementationIDSpace, kXMLDTDPkgContentHandlerImpl, kXMLPrefix + 140)
DECLARE_PMID(kImplementationIDSpace, kXMLDuplicateElementsCmdImpl, kXMLPrefix + 141)
DECLARE_PMID(kImplementationIDSpace, kXMLElementPrivateCommandsImpl, kXMLPrefix + 142)
DECLARE_PMID(kImplementationIDSpace, kXMLDeleteElementAndContentCmdImpl, kXMLPrefix + 143)
DECLARE_PMID(kImplementationIDSpace, kXMLExportSessionOptionsImpl, kXMLPrefix + 144)
DECLARE_PMID(kImplementationIDSpace, kScrapXMLElementPersistUIDDataImpl, kXMLPrefix + 145)
DECLARE_PMID(kImplementationIDSpace, kXMLDupElementsCmdDataImpl, kXMLPrefix + 146)
DECLARE_PMID(kImplementationIDSpace, kChangeXMLExportSOptionsCmdImpl, kXMLPrefix + 147)
DECLARE_PMID(kImplementationIDSpace, kAssociatedXMLScriptProviderImpl, kXMLPrefix + 148)
DECLARE_PMID(kImplementationIDSpace, kXMLSetContentItemCmdImpl, kXMLPrefix + 149)
DECLARE_PMID(kImplementationIDSpace, kXMLSetAttributeNameCmdImpl, kXMLPrefix + 150)
DECLARE_PMID(kImplementationIDSpace, kXMLAttributeCommandsImpl, kXMLPrefix + 151)
DECLARE_PMID(kImplementationIDSpace, kXMLTagCommandsImpl, kXMLPrefix + 152)
DECLARE_PMID(kImplementationIDSpace, kXMLDeleteTagCmdDataImpl, kXMLPrefix + 153)
DECLARE_PMID(kImplementationIDSpace, kXMLMappingCommandsImpl, kXMLPrefix + 154)
DECLARE_PMID(kImplementationIDSpace, kXMLCopyMappingCmdDataImpl, kXMLPrefix + 155)
DECLARE_PMID(kImplementationIDSpace, kXMLOutFileStreamImpl, kXMLPrefix + 156)
DECLARE_PMID(kImplementationIDSpace, kXMLOutPMStreamImpl, kXMLPrefix + 157)
DECLARE_PMID(kImplementationIDSpace, kXMLStreamUtilsImpl, kXMLPrefix + 158)
DECLARE_PMID(kImplementationIDSpace, kXMLSetXMLReferenceDataCmdImpl, kXMLPrefix + 159)
DECLARE_PMID(kImplementationIDSpace, kXMLElementToInlineCmdImpl, kXMLPrefix + 160)
DECLARE_PMID(kImplementationIDSpace, kXMLTextLinkResponderImpl, kXMLPrefix + 161)
DECLARE_PMID(kImplementationIDSpace, kXMLPIGeneratorImpl, kXMLPrefix + 162)
DECLARE_PMID(kImplementationIDSpace, kXMLCreateStyleToTagElementsCmdDataImpl, kXMLPrefix + 163)
DECLARE_PMID(kImplementationIDSpace, kXMLPITargetImpl, kXMLPrefix + 164)
DECLARE_PMID(kImplementationIDSpace, kXMLPIDataImpl, kXMLPrefix + 165)
DECLARE_PMID(kImplementationIDSpace, kXMLRangeDeleteElementCmdImpl, kXMLPrefix + 166)
DECLARE_PMID(kImplementationIDSpace, kSourceXMLTagsDataImpl, kXMLPrefix + 167)
DECLARE_PMID(kImplementationIDSpace, kDestXMLTagsDataImpl, kXMLPrefix + 168)
DECLARE_PMID(kImplementationIDSpace, kXMLCreatePICmdImpl, kXMLPrefix + 169)
DECLARE_PMID(kImplementationIDSpace, kXMLSetTagColorCmdImpl, kXMLPrefix + 170)
DECLARE_PMID(kImplementationIDSpace, kCurrentTagColorPersIntDataImpl, kXMLPrefix + 171)
DECLARE_PMID(kImplementationIDSpace, kScrapXMLElementPersistUIDData2Impl, kXMLPrefix + 172)
DECLARE_PMID(kImplementationIDSpace, kPMStringMapDataImpl, kXMLPrefix + 173)
DECLARE_PMID(kImplementationIDSpace, kXMLFormattedMapDataImpl, kXMLPrefix + 174)
DECLARE_PMID(kImplementationIDSpace, kXMLExportUtilsImpl, kXMLPrefix + 175)
DECLARE_PMID(kImplementationIDSpace, kXMLCountElementsHandlerImpl, kXMLPrefix + 176)
DECLARE_PMID(kImplementationIDSpace, kXMLImageHandlerImpl, kXMLPrefix + 177)
DECLARE_PMID(kImplementationIDSpace, kXMLImageHandlerDataImpl, kXMLPrefix + 178)
DECLARE_PMID(kImplementationIDSpace, kXMLExportOptionsImpl2_Obsolete, kXMLPrefix + 179)	// persistent implID required for conversion
DECLARE_PMID(kImplementationIDSpace, kXMLMergeStoriesPreCmdImpl, kXMLPrefix + 180)
DECLARE_PMID(kImplementationIDSpace, kXMLMergeStoriesPostCmdImpl, kXMLPrefix + 181)
DECLARE_PMID(kImplementationIDSpace, kXMLElementTextObjectParentImpl, kXMLPrefix + 182)
DECLARE_PMID(kImplementationIDSpace, kSAXDocumentHandlerImpl, kXMLPrefix + 183)
DECLARE_PMID(kImplementationIDSpace, kSAXDocumentHandlerDataImpl, kXMLPrefix + 184)
DECLARE_PMID(kImplementationIDSpace, kSAXTagListHandlerImpl, kXMLPrefix + 185)
DECLARE_PMID(kImplementationIDSpace, kXMLPIScriptProviderImpl, kXMLPrefix + 186)
DECLARE_PMID(kImplementationIDSpace, kXMLDTDPkgContentDataImpl, kXMLPrefix + 187)
DECLARE_PMID(kImplementationIDSpace, kXMLCreateTableElementCmdImpl, kXMLPrefix + 188)
DECLARE_PMID(kImplementationIDSpace, kXMLCreateDTDCmdImpl, kXMLPrefix + 189)
DECLARE_PMID(kImplementationIDSpace, kXMLCreateDTDCmdDataImpl, kXMLPrefix + 190)
DECLARE_PMID(kImplementationIDSpace, kXMLElementDTDInfoImpl, kXMLPrefix + 191)
DECLARE_PMID(kImplementationIDSpace, kXMLDTDXMLReferenceDataImpl, kXMLPrefix + 192)
DECLARE_PMID(kImplementationIDSpace, kXMLDTDInsertElementListDataImpl, kXMLPrefix + 193)
DECLARE_PMID(kImplementationIDSpace, kXMLSetDFAStateCmdImpl, kXMLPrefix + 194)
DECLARE_PMID(kImplementationIDSpace, kXMLDTDTokenHandlerImpl, kXMLPrefix + 195)
DECLARE_PMID(kImplementationIDSpace, kXMLDTDReplaceElementListDataImpl, kXMLPrefix + 196)
DECLARE_PMID(kImplementationIDSpace, kXMLDTDPrivateImpl, kXMLPrefix + 197)
DECLARE_PMID(kImplementationIDSpace, kXMLTestSuiteASBImpl, kXMLPrefix + 198)
DECLARE_PMID(kImplementationIDSpace, kXMLTestSuiteTextCSBImpl, kXMLPrefix + 199)
DECLARE_PMID(kImplementationIDSpace, kXMLTestSuiteLayoutCSBImpl, kXMLPrefix + 200)
DECLARE_PMID(kImplementationIDSpace, kXMLContentServiceProviderImpl, kXMLPrefix + 201)
DECLARE_PMID(kImplementationIDSpace, kXMLTableContentHandlerImpl, kXMLPrefix + 202)
DECLARE_PMID(kImplementationIDSpace, kXMLTableParsingContextImpl, kXMLPrefix + 203)
DECLARE_PMID(kImplementationIDSpace, kXMLExportImageOptionsIIDImpl, kXMLPrefix + 204)	// used in ChangeXMLExportOptionsCmd as alias of kInterfaceDataImpl.
DECLARE_PMID(kImplementationIDSpace, kXMLExportViewerOptionsIIDImpl, kXMLPrefix + 205)	// used in ChangeXMLExportOptionsCmd as alias of kInterfaceDataImpl.
DECLARE_PMID(kImplementationIDSpace, kXMLRubyGeneratorImpl, kXMLPrefix + 206)
DECLARE_PMID(kImplementationIDSpace, kXMLRubyContentHandlerImpl, kXMLPrefix + 207)
DECLARE_PMID(kImplementationIDSpace, kXMLValidationErrorImpl, kXMLPrefix + 208)
DECLARE_PMID(kImplementationIDSpace, kXMLLoadDTDCmdImpl, kXMLPrefix + 209)
DECLARE_PMID(kImplementationIDSpace, kXMLLoadDTDCmdDataImpl, kXMLPrefix + 210)
DECLARE_PMID(kImplementationIDSpace, kXMLLoadDTDHandlerImpl, kXMLPrefix + 211)
DECLARE_PMID(kImplementationIDSpace, kXMLValidatorImpl, kXMLPrefix + 212)
DECLARE_PMID(kImplementationIDSpace, kXMLImportDTDPkgXMLCmdImpl, kXMLPrefix + 213)
DECLARE_PMID(kImplementationIDSpace, kXMLDTDPkgEntityResolverImpl, kXMLPrefix + 214)
DECLARE_PMID(kImplementationIDSpace, kXMLInternalSubsetStringImpl, kXMLPrefix + 215)
DECLARE_PMID(kImplementationIDSpace, kXMLExternalSubsetStringImpl, kXMLPrefix + 216)
DECLARE_PMID(kImplementationIDSpace, kXMLReplaceDTDCmdImpl, kXMLPrefix + 217)
DECLARE_PMID(kImplementationIDSpace, kXMLMementoImpl, kXMLPrefix + 218)
DECLARE_PMID(kImplementationIDSpace, kStylesheetDataImpl, kXMLPrefix + 219)
DECLARE_PMID(kImplementationIDSpace, kXMLViewSelectionImpl, kXMLPrefix + 220)
DECLARE_PMID(kImplementationIDSpace, kXMLTableTagContentHandlerImpl, kXMLPrefix + 221)
DECLARE_PMID(kImplementationIDSpace, kXMLTagServiceProviderImpl, kXMLPrefix + 222)
DECLARE_PMID(kImplementationIDSpace, kXMLMoveElementMarkersCmdImpl, kXMLPrefix + 223)
DECLARE_PMID(kImplementationIDSpace, kXMLPostPasteFixupCmdImpl, kXMLPrefix + 224)
DECLARE_PMID(kImplementationIDSpace, kXMLDeleteTextCmdImpl, kXMLPrefix + 225)
DECLARE_PMID(kImplementationIDSpace, kXMLCreateTableElementCmdDataImpl, kXMLPrefix + 226)
DECLARE_PMID(kImplementationIDSpace, kXMLStoryScriptProviderImpl, kXMLPrefix + 227)
DECLARE_PMID(kImplementationIDSpace, kXMLDTDScriptProviderImpl, kXMLPrefix + 228)
DECLARE_PMID(kImplementationIDSpace, kXMLApplyMapTagToStyleMappingCmdImpl, kXMLPrefix + 229)
DECLARE_PMID(kImplementationIDSpace, kXMLUpdateLinkServiceImpl, kXMLPrefix + 230)
DECLARE_PMID(kImplementationIDSpace, kXMLReferenceDataTableCellImpl, kXMLPrefix + 231)
DECLARE_PMID(kImplementationIDSpace, kXMLSetTableXMLRefDataCmdLetImpl, kXMLPrefix + 232)
DECLARE_PMID(kImplementationIDSpace, kXMLSetTableCellXMLRefDataCmdLetImpl, kXMLPrefix + 233)
DECLARE_PMID(kImplementationIDSpace, kXMLTestSuiteXMLCSBImpl, kXMLPrefix + 234)
DECLARE_PMID(kImplementationIDSpace, kXMLTestSuiteTablesCSBImpl, kXMLPrefix + 235)
DECLARE_PMID(kImplementationIDSpace, kXMLStructureUniformTargetFactoryImpl, kXMLPrefix + 236)
DECLARE_PMID(kImplementationIDSpace, kXMLCellContentMgrNotificationsImpl, kXMLPrefix + 237)
DECLARE_PMID(kImplementationIDSpace, kImportXMLDataImpl, kXMLPrefix + 238)
DECLARE_PMID(kImplementationIDSpace, kXMLFilterServiceProviderImpl, kXMLPrefix + 239)
DECLARE_PMID(kImplementationIDSpace, kXMLLinkingPostImportResponderImpl, kXMLPrefix + 240)
DECLARE_PMID(kImplementationIDSpace, kXMLAcquirerTextFileFilterImpl, kXMLPrefix + 241)
DECLARE_PMID(kImplementationIDSpace, kXMLImporterImpl, kXMLPrefix + 242)
DECLARE_PMID(kImplementationIDSpace, kXMLImportMatchRecorderImpl, kXMLPrefix + 243)
DECLARE_PMID(kImplementationIDSpace, kXMLRepeatTextElementsMatchMakerImpl, kXMLPrefix + 244)
DECLARE_PMID(kImplementationIDSpace, kXMLImporterPostImportMappingImpl, kXMLPrefix + 245)
DECLARE_PMID(kImplementationIDSpace, kXMLImporterPostImportSvcProvImpl, kXMLPrefix + 246)
DECLARE_PMID(kImplementationIDSpace, kPostImportResponderDataImpl, kXMLPrefix + 247)
DECLARE_PMID(kImplementationIDSpace, kXMLImporterDOMImpl, kXMLPrefix + 248)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix + 249)
DECLARE_PMID(kImplementationIDSpace, kXMLImportMatchMakerSignalServiceImpl, kXMLPrefix + 250)
DECLARE_PMID(kImplementationIDSpace, kXMLImportDefaultMatchMakerSignalServiceImpl, kXMLPrefix + 251)
DECLARE_PMID(kImplementationIDSpace, kXMLImportMatchDriverImpl, kXMLPrefix + 252)
DECLARE_PMID(kImplementationIDSpace, kXMLImportDefaultMatchMakerImpl, kXMLPrefix + 253)
DECLARE_PMID(kImplementationIDSpace, kPropertyListImpl, kXMLPrefix + 254)
DECLARE_PMID(kImplementationIDSpace, kPersistPropertyListImpl, kXMLPrefix + 255)

DECLARE_PMID(kImplementationIDSpace, kXMLPostImportIterationServiceProviderImpl, kXMLPrefix2 + 1)
DECLARE_PMID(kImplementationIDSpace, kXMLPostImportIterationResponderImpl, kXMLPrefix2 + 2)
DECLARE_PMID(kImplementationIDSpace, kXMLDeleteElementContentCmdImpl, kXMLPrefix2 + 3)
DECLARE_PMID(kImplementationIDSpace, kXMLThrowAwayUnmatchedRightMatchMakerImpl, kXMLPrefix2 + 4)
DECLARE_PMID(kImplementationIDSpace, kXMLThrowAwayUnmatchedLeftMatchMakerImpl, kXMLPrefix2 + 5)
DECLARE_PMID(kImplementationIDSpace, kXMLImportTransformerSignalServiceImpl, kXMLPrefix2 + 6)
DECLARE_PMID(kImplementationIDSpace, kXMLStripWhitespacesTransformerImpl, kXMLPrefix2 + 7)
DECLARE_PMID(kImplementationIDSpace, kXMLCellContentMgrNotificationsPasteCmdDataImpl, kXMLPrefix2 + 8)
DECLARE_PMID(kImplementationIDSpace, kXMLRuleProcTransformerImpl, kXMLPrefix2 + 9)
DECLARE_PMID(kImplementationIDSpace, kXMLTableMatchMakerImpl, kXMLPrefix2 + 10)
DECLARE_PMID(kImplementationIDSpace, kXMLImportOptionsPoolImpl, kXMLPrefix2 + 11)
DECLARE_PMID(kImplementationIDSpace, kXMLImportOptionsPoolContentHandlerImpl, kXMLPrefix2 + 12)
DECLARE_PMID(kImplementationIDSpace, kXMLCellContentMgrNotificationsPasteCmdImpl, kXMLPrefix2 + 13)
DECLARE_PMID(kImplementationIDSpace, kXMLinkToIncomingXMLPrefImpl, kXMLPrefix2 + 14)
DECLARE_PMID(kImplementationIDSpace, kXMLMappingPrefImpl, kXMLPrefix2 + 15)
DECLARE_PMID(kImplementationIDSpace, kXMLStripWhitespacePrefImpl, kXMLPrefix2 + 16)
DECLARE_PMID(kImplementationIDSpace, kXMLRepeatTextElementsPrefImpl, kXMLPrefix2 + 17)
DECLARE_PMID(kImplementationIDSpace, kXMLThrowAwayUnmatchedRightPrefImpl, kXMLPrefix2 + 18)
DECLARE_PMID(kImplementationIDSpace, kXMLThrowAwayUnmatchedLeftPrefImpl, kXMLPrefix2 + 19)
DECLARE_PMID(kImplementationIDSpace, kXMLTestImpl, kXMLPrefix2 + 20)
DECLARE_PMID(kImplementationIDSpace, kXMLSnippetMatchMakerImpl, kXMLPrefix2 + 21)
DECLARE_PMID(kImplementationIDSpace, kXMLSparseImportPrefImpl, kXMLPrefix2 + 22)
DECLARE_PMID(kImplementationIDSpace, kSetBoolValueCmdImpl, kXMLPrefix2 + 23)
DECLARE_PMID(kImplementationIDSpace, kSetBoolCmdDataImpl, kXMLPrefix2 + 24)
DECLARE_PMID(kImplementationIDSpace, kShowImportOptionsBoolImpl, kXMLPrefix2 + 25)
DECLARE_PMID(kImplementationIDSpace, kXMLPreferencesScriptProviderImpl, kXMLPrefix2 + 26)
DECLARE_PMID(kImplementationIDSpace, kXSLTransformerPIImpl, kXMLPrefix2 + 27)
DECLARE_PMID(kImplementationIDSpace, kXMLTableTagPreferenceDataImpl, kXMLPrefix2 + 28)
DECLARE_PMID(kImplementationIDSpace, kXMLTableMementoPieceTransferToCmdImpl, kXMLPrefix2 + 29)
DECLARE_PMID(kImplementationIDSpace, kXMLAdjustGridCmdImpl, kXMLPrefix2 + 30)
DECLARE_PMID(kImplementationIDSpace, kXMLAdjustGridCmdDataImpl, kXMLPrefix2 + 31)
DECLARE_PMID(kImplementationIDSpace, kXMLSetTableTagPreferenceCmdImpl, kXMLPrefix2 + 32)
DECLARE_PMID(kImplementationIDSpace, kXMLStyleToTagOptionsDataImpl, kXMLPrefix2 + 33)
DECLARE_PMID(kImplementationIDSpace, kXMLRubyAndDtTableMatchMakerImpl, kXMLPrefix2 + 34)
DECLARE_PMID(kImplementationIDSpace, kXMLRuleProcTransformerPrefImpl, kXMLPrefix2 + 35)
DECLARE_PMID(kImplementationIDSpace, kXSLTransformerPIPrefImpl, kXMLPrefix2 + 36)
DECLARE_PMID(kImplementationIDSpace, kXMLMatchTextToTablePrefImpl, kXMLPrefix2 + 37)
DECLARE_PMID(kImplementationIDSpace, kXMLForceMergePrefImpl, kXMLPrefix2 + 38)
DECLARE_PMID(kImplementationIDSpace, kXMLRulesProcessorScriptProviderImpl, kXMLPrefix2 + 39)
DECLARE_PMID(kImplementationIDSpace, kXMLTestExportHandlerImpl, kXMLPrefix2 + 40)
DECLARE_PMID(kImplementationIDSpace, kXMLRulesProcessorMgrImpl, kXMLPrefix2 + 41)
DECLARE_PMID(kImplementationIDSpace, kXMLStructureSuiteCSBExtImpl, kXMLPrefix2 + 42)
DECLARE_PMID(kImplementationIDSpace, kXMLExportServiceImpl, kXMLPrefix2 + 43)
DECLARE_PMID(kImplementationIDSpace, kXMLRulesProcessorScriptImpl, kXMLPrefix2 + 44)
DECLARE_PMID(kImplementationIDSpace, kXMLRulesCloseDocResponderImpl, kXMLPrefix2 + 45)
DECLARE_PMID(kImplementationIDSpace, kXMLSampleRuleSetListImpl, kXMLPrefix2 + 46)
DECLARE_PMID(kImplementationIDSpace, kXMLSampleRuleSetImpl, kXMLPrefix2 + 47)
DECLARE_PMID(kImplementationIDSpace, kXMLSampleRuleImpl, kXMLPrefix2 + 48)
DECLARE_PMID(kImplementationIDSpace, kXMLSampleConditionImpl, kXMLPrefix2 + 49)
DECLARE_PMID(kImplementationIDSpace, kXMLSampleActionImpl, kXMLPrefix2 + 50)
DECLARE_PMID(kImplementationIDSpace, kXMLSetStyleToTagOptionsCmdImpl, kXMLPrefix2 + 51)
DECLARE_PMID(kImplementationIDSpace, kXMLTextVariableGeneratorImpl, kXMLPrefix2 + 52)
DECLARE_PMID(kImplementationIDSpace, kXMLRelinkContentCmdImpl, kXMLPrefix2 + 53)
DECLARE_PMID(kImplementationIDSpace, kXMLConvertElementToInlineCmdDataImpl, kXMLPrefix2 + 54)
DECLARE_PMID(kImplementationIDSpace, kDropXMLElementCommandImpl, kXMLPrefix2 + 55)
DECLARE_PMID(kImplementationIDSpace, kXMLConvertElementToTableCmdDataImpl, kXMLPrefix2 + 56)
DECLARE_PMID(kImplementationIDSpace, kExportForWebScriptProviderImpl, kXMLPrefix2 + 57)
DECLARE_PMID(kImplementationIDSpace, kExportForWebPrefsScriptProviderImpl, kXMLPrefix2 + 58)
DECLARE_PMID(kImplementationIDSpace, kExportForWebPrefsImpl, kXMLPrefix2 + 59)
DECLARE_PMID(kImplementationIDSpace, kXMLRelinkContentCmdDataImpl, kXMLPrefix2 + 60)
DECLARE_PMID(kImplementationIDSpace, kTestParserContentHandlerImpl, kXMLPrefix2 + 61)
DECLARE_PMID(kImplementationIDSpace, kTestParserDTDHandlerImpl, kXMLPrefix2 + 62)
DECLARE_PMID(kImplementationIDSpace, kXMLRulesProcessorImpl, kXMLPrefix2 + 63)
DECLARE_PMID(kImplementationIDSpace, kXMLImportCALSTablePrefImpl, kXMLPrefix2 + 64)
DECLARE_PMID(kImplementationIDSpace, kXMLPostImportRuleResponderImpl, kXMLPrefix2 + 65)
DECLARE_PMID(kImplementationIDSpace, kXMLPostImportRulePrefImpl, kXMLPrefix2 + 66)

// For Table/Cell styles
DECLARE_PMID(kImplementationIDSpace, kXMLDeleteTableStyleCmdResponderImpl, kXMLPrefix2 + 67)
DECLARE_PMID(kImplementationIDSpace, kXMLDeleteCellStyleCmdResponderImpl, kXMLPrefix2 + 68)

DECLARE_PMID(kImplementationIDSpace, kTestParserLogImpl, kXMLPrefix2 + 69)
DECLARE_PMID(kImplementationIDSpace, kTestParserDTDTokenHandlerImpl, kXMLPrefix2 + 70)
// For XML linking in new arch
DECLARE_PMID(kImplementationIDSpace, kXMLLinkObjectPersistUIDDataImpl, kXMLPrefix2 + 71)
DECLARE_PMID(kImplementationIDSpace, kXMLElementLinkObjectImpl, kXMLPrefix2 + 72)

//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 73)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 74)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 75)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 76)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 77)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 78)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 79)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 80)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 81)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 82)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 83)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 84)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 85)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 86)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 87)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 88)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 89)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 90)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 91)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 92)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 93)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 94)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 95)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 96)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 97)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 98)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 99)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 100)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 101)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 102)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 103)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 104)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 105)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 106)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 107)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 108)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 109)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 110)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 111)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 112)
//DECLARE_PMID(kImplementationIDSpace, kXMLFutureImpl, kXMLPrefix2 + 113)
DECLARE_PMID(kImplementationIDSpace, kXSLTDTDContentHandlerImpl, kXMLPrefix2 + 114)
DECLARE_PMID(kImplementationIDSpace, kXMLStructureIteratorManagerImpl, kXMLPrefix2 + 115)
DECLARE_PMID(kImplementationIDSpace, kXMLRuleMatchDataScriptProviderImpl, kXMLPrefix2 + 116)
DECLARE_PMID(kImplementationIDSpace, kXMLRuleMatchDataImpl, kXMLPrefix2 + 117)
DECLARE_PMID(kImplementationIDSpace, kXMLRuleActionCommandsImpl, kXMLPrefix2 + 118)
DECLARE_PMID(kImplementationIDSpace, kXMLRulesElementScriptProviderImpl, kXMLPrefix2 + 119)
DECLARE_PMID(kImplementationIDSpace, kXMLConvertElementToInlineCmdImpl, kXMLPrefix2 + 120)
DECLARE_PMID(kImplementationIDSpace, kXMLSetTagRoleCmdImpl, kXMLPrefix2 + 121)
DECLARE_PMID(kImplementationIDSpace, kXMLConvertElementToTableCmdImpl, kXMLPrefix2 + 122)

DECLARE_PMID(kImplementationIDSpace, kItemAndBelowPrintDrawEventHandlerImpl, kXMLPrefix2 + 123)
DECLARE_PMID(kImplementationIDSpace, kSetDeleteElementOnContentDeletePrefCmdImpl, kXMLPrefix2 + 124)
DECLARE_PMID(kImplementationIDSpace, kDeleteElementOnContentDeletePrefImpl, kXMLPrefix2 + 125)

// <Error ID>
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLPrefix + 160)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLPrefix + 161)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLPrefix + 162)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLPrefix + 163)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLPrefix + 164)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLPrefix + 165)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLPrefix + 166)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLPrefix + 167)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLPrefix + 168)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLPrefix + 169)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLPrefix + 170)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLPrefix + 171)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLPrefix + 172)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLPrefix + 173)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLPrefix + 174)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLPrefix + 175)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLPrefix + 176)
//DECLARE_PMID(kErrorIDSpace, kXMLFutureErr, kXMLPrefix + 177)
DECLARE_PMID(kErrorIDSpace, kXMLCannotTagEndnoteTextErr, kXMLPrefix + 178)

// Uncomment later for Vantive #1841934.
DECLARE_PMID(kErrorIDSpace, kXMLEmptyImageSkipped, kXMLPrefix + 179)
DECLARE_PMID(kErrorIDSpace, kXMLCannotTagPartialHyperlinkErr, kXMLPrefix + 180)
DECLARE_PMID(kErrorIDSpace, kPropertyHasNoCurrentValueError, kXMLPrefix + 181)
DECLARE_PMID(kErrorIDSpace, kNoSuchAttributeError, kXMLPrefix + 182)
DECLARE_PMID(kErrorIDSpace, kXMLCannotRelinkErr, kXMLPrefix + 183)
DECLARE_PMID(kErrorIDSpace, kLoadTagListErr, kXMLPrefix + 184)
DECLARE_PMID(kErrorIDSpace, kInvalidXMLElementErr, kXMLPrefix + 185)
DECLARE_PMID(kErrorIDSpace, kXMLCannotAutoTagErr, kXMLPrefix + 186)
DECLARE_PMID(kErrorIDSpace, kAlreadyProcessingRulesErr, kXMLPrefix + 187)
DECLARE_PMID(kErrorIDSpace, kStructureIteratorInvalidErr, kXMLPrefix + 188)
DECLARE_PMID(kErrorIDSpace, kXMLCantProcessXPathFragmentErr, kXMLPrefix + 189)
DECLARE_PMID(kErrorIDSpace, kXMLSetContentOnNonGraphicFrameErr, kXMLPrefix + 190)
DECLARE_PMID(kErrorIDSpace, kXMLPlaceIntoCopyInvalidDBErr, kXMLPrefix + 191)
DECLARE_PMID(kErrorIDSpace, kXMLImportTableErr, kXMLPrefix + 192)
DECLARE_PMID(kErrorIDSpace, kXMLDuplicateTagNameErr, kXMLPrefix + 193)
DECLARE_PMID(kErrorIDSpace, kXMLInvalidRubyElementErr, kXMLPrefix + 194)
DECLARE_PMID(kErrorIDSpace, kXMLContentAlreadyTaggedErr, kXMLPrefix + 195)
DECLARE_PMID(kErrorIDSpace, kXMLCannotTagFootnoteTextErr, kXMLPrefix + 196)
DECLARE_PMID(kErrorIDSpace, kXMLNonExistAttributeErr, kXMLPrefix + 197)
DECLARE_PMID(kErrorIDSpace, kXMLTableAlreadyTaggedErr, kXMLPrefix + 198)
DECLARE_PMID(kErrorIDSpace, kXMLInvalidAttributeNameErr, kXMLPrefix + 199)
DECLARE_PMID(kErrorIDSpace, kCannotPlaceContentAlreadyPlacedErr, kXMLPrefix + 200)
DECLARE_PMID(kErrorIDSpace, kXMLPlaceElementInvalidGraphicFrameErr, kXMLPrefix + 201)
DECLARE_PMID(kErrorIDSpace, kXMLPlaceFrameAlreadyHasContentErr, kXMLPrefix + 202)
DECLARE_PMID(kErrorIDSpace, kXMLElementHrefImportErr, kXMLPrefix + 203)
DECLARE_PMID(kErrorIDSpace, kXMLPlaceFrameAlreadyTaggedErr, kXMLPrefix + 204)
DECLARE_PMID(kErrorIDSpace, kXMLLockedElement_ModifyErr, kXMLPrefix + 205)
DECLARE_PMID(kErrorIDSpace, kXMLLockedElement_DeleteErr, kXMLPrefix + 206)
DECLARE_PMID(kErrorIDSpace, kXMLLockedElement_MoveErr, kXMLPrefix + 207)
DECLARE_PMID(kErrorIDSpace, kXMLLockedElement_MoveToErr, kXMLPrefix + 208)
DECLARE_PMID(kErrorIDSpace, kXMLMoveElementTargetInSourceErr, kXMLPrefix + 209)
DECLARE_PMID(kErrorIDSpace, kXMLInvalidTagNameErr, kXMLPrefix + 210)
DECLARE_PMID(kErrorIDSpace, kXMLCannotTagCellContentsErr, kXMLPrefix + 211)
DECLARE_PMID(kErrorIDSpace, kXMLAttributeAlreadyExistsErr, kXMLPrefix + 212)
DECLARE_PMID(kErrorIDSpace, kXMLFrameContentNotTaggableErr, kXMLPrefix + 213)
DECLARE_PMID(kErrorIDSpace, kXMLObjectNotTaggableErr, kXMLPrefix + 214)
DECLARE_PMID(kErrorIDSpace, kXMLInvalidTableElementErr, kXMLPrefix + 215)
DECLARE_PMID(kErrorIDSpace, kXMLInvalidAssetURLErr, kXMLPrefix + 216)
DECLARE_PMID(kErrorIDSpace, kXMLInvalidCommentPIOperationErr, kXMLPrefix + 217)
DECLARE_PMID(kErrorIDSpace, kXMLPlaceIntoInlineErr, kXMLPrefix + 218)
DECLARE_PMID(kErrorIDSpace, kXMLMoveMultiTaggedInlineErr, kXMLPrefix + 219)
DECLARE_PMID(kErrorIDSpace, kXMLCannotTagWithinRubyErr, kXMLPrefix + 220)
DECLARE_PMID(kErrorIDSpace, kXMLCopyToImageSubFolderErr, kXMLPrefix + 221)
DECLARE_PMID(kErrorIDSpace, kXMLConvertOptimizedImageErr, kXMLPrefix + 222)
DECLARE_PMID(kErrorIDSpace, kXMLConvertFormattedImageErr, kXMLPrefix + 223)
DECLARE_PMID(kErrorIDSpace, kXMLParentElemCantContainChildErr, kXMLPrefix + 224)
DECLARE_PMID(kErrorIDSpace, kXMLDTDAlreadyExistsErr, kXMLPrefix + 225)
DECLARE_PMID(kErrorIDSpace, kXMLCannotDeleteElementErr, kXMLPrefix + 226)
DECLARE_PMID(kErrorIDSpace, kXMLInvalidDTDXMLReferenceErr, kXMLPrefix + 227)
DECLARE_PMID(kErrorIDSpace, kXMLNILDTDErr, kXMLPrefix + 228)
DECLARE_PMID(kErrorIDSpace, kXMLInvalidNMTokenErr, kXMLPrefix + 229)
DECLARE_PMID(kErrorIDSpace, kXMLInvalidIDNameErr, kXMLPrefix + 230)
DECLARE_PMID(kErrorIDSpace, kXMLBadRootElementTypeErr, kXMLPrefix + 231)
DECLARE_PMID(kErrorIDSpace, kXMLEMPTYElementWithContentErr, kXMLPrefix + 232)
DECLARE_PMID(kErrorIDSpace, kXMLUnexpectedElementErr, kXMLPrefix + 233)
DECLARE_PMID(kErrorIDSpace, kXMLMissingElementErr, kXMLPrefix + 234)
DECLARE_PMID(kErrorIDSpace, kXMLUndeclaredElementErr, kXMLPrefix + 235)
DECLARE_PMID(kErrorIDSpace, kXMLMissingRequiredAttributeErr, kXMLPrefix + 236)
DECLARE_PMID(kErrorIDSpace, kXMLExtraAttributeErr, kXMLPrefix + 237)
DECLARE_PMID(kErrorIDSpace, kXMLNotUnparsedEntityInAttValueErr, kXMLPrefix + 238)
DECLARE_PMID(kErrorIDSpace, kXMLUndeclaredEntityInAttValueErr, kXMLPrefix + 239)
DECLARE_PMID(kErrorIDSpace, kXMLUndeclaredNotationInAttValueErr, kXMLPrefix + 240)
DECLARE_PMID(kErrorIDSpace, kXMLAttValueNotInEnumErr, kXMLPrefix + 241)
DECLARE_PMID(kErrorIDSpace, kXMLDuplicateIDAttValueErr, kXMLPrefix + 242)
DECLARE_PMID(kErrorIDSpace, kXMLFixedAttributeDefaultErr, kXMLPrefix + 243)
DECLARE_PMID(kErrorIDSpace, kXMLIDNotFoundErr, kXMLPrefix + 244)
DECLARE_PMID(kErrorIDSpace, kXMLMissingReplacementTagErr, kXMLPrefix + 245)
DECLARE_PMID(kErrorIDSpace, kXMLTagNameLockedErr, kXMLPrefix + 246)
DECLARE_PMID(kErrorIDSpace, kXMLIllegalElementMoveErr, kXMLPrefix + 247)
DECLARE_PMID(kErrorIDSpace, kXMLNoContentModelErr, kXMLPrefix + 248)
DECLARE_PMID(kErrorIDSpace, kXMLChildrenContentModelWithContentErr, kXMLPrefix + 249)
DECLARE_PMID(kErrorIDSpace, kXMLAddElementToDocErr, kXMLPrefix + 250)
DECLARE_PMID(kErrorIDSpace, kXMLInvalidENTITYNameErr, kXMLPrefix + 251)
DECLARE_PMID(kErrorIDSpace, kXMLInvalidNOTATIONNameErr, kXMLPrefix + 252)
DECLARE_PMID(kErrorIDSpace, kXMLLockedContent_ModifyErr, kXMLPrefix + 253)
DECLARE_PMID(kErrorIDSpace, kXMLCannotTagDeletedTextErr, kXMLPrefix + 254)
DECLARE_PMID(kErrorIDSpace, kXMLCannotTagNoteTextErr, kXMLPrefix + 255)


// Messages
//DECLARE_PMID(kMessageIDSpace, kUseMe, kXMLPrefix + 1)
//DECLARE_PMID(kMessageIDSpace, kUseMe, kXMLPrefix + 2)
DECLARE_PMID(kMessageIDSpace, kXMLExportTransparencyAlert, kXMLPrefix + 3)
DECLARE_PMID(kMessageIDSpace, kXMLExportTableAlert, kXMLPrefix + 4)
DECLARE_PMID(kMessageIDSpace, kXMLExportRubyAlert, kXMLPrefix + 5)
DECLARE_PMID(kMessageIDSpace, kXMLExportSelectedDTDAlert, kXMLPrefix + 6)
DECLARE_PMID(kMessageIDSpace, kXMLBackingStoreUnmutedMsg, kXMLPrefix + 7)
DECLARE_PMID(kMessageIDSpace, kXMLAssociatedPageItemDeletedMsg, kXMLPrefix + 8)
//DECLARE_PMID(kMessageIDSpace, kXMLFutureMsg, kXMLPrefix + 9)
//DECLARE_PMID(kMessageIDSpace, kXMLFutureMsg, kXMLPrefix + 10)
//DECLARE_PMID(kMessageIDSpace, kXMLFutureMsg, kXMLPrefix + 11)
//DECLARE_PMID(kMessageIDSpace, kXMLFutureMsg, kXMLPrefix + 12)
//DECLARE_PMID(kMessageIDSpace, kXMLFutureMsg, kXMLPrefix + 13)
//DECLARE_PMID(kMessageIDSpace, kXMLFutureMsg, kXMLPrefix + 14)
//DECLARE_PMID(kMessageIDSpace, kXMLFutureMsg, kXMLPrefix + 15)
//DECLARE_PMID(kMessageIDSpace, kXMLFutureMsg, kXMLPrefix + 16)
//DECLARE_PMID(kMessageIDSpace, kXMLFutureMsg, kXMLPrefix + 17)
//DECLARE_PMID(kMessageIDSpace, kXMLFutureMsg, kXMLPrefix + 18)
//DECLARE_PMID(kMessageIDSpace, kXMLFutureMsg, kXMLPrefix + 19)
//DECLARE_PMID(kMessageIDSpace, kXMLFutureMsg, kXMLPrefix + 20)

//
//Script Element IDs
//

//Suites
DECLARE_PMID(kScriptInfoIDSpace, kXMLSuiteScriptElement,						kXMLPrefix + 1)

// typedef
DECLARE_PMID(kScriptInfoIDSpace, kNameValuePairTypeDefScriptElement,			kXMLPrefix + 9)

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kXMLElementObjectScriptElement,				kXMLPrefix + 10)
DECLARE_PMID(kScriptInfoIDSpace, kXMLAttributeObjectScriptElement,				kXMLPrefix + 11)
DECLARE_PMID(kScriptInfoIDSpace, kXMLTagObjectScriptElement,					kXMLPrefix + 12)
//DECLARE_PMID(kScriptInfoIDSpace, kXMLFutureScriptInfoID,						kXMLPrefix + 13)
DECLARE_PMID(kScriptInfoIDSpace, kXMLImportPrefsObjectScriptElement,			kXMLPrefix + 14)
DECLARE_PMID(kScriptInfoIDSpace, kXMLExportPrefsObjectScriptElement,			kXMLPrefix + 15)
DECLARE_PMID(kScriptInfoIDSpace, kXMLImportMapObjectScriptElement,				kXMLPrefix + 16)
DECLARE_PMID(kScriptInfoIDSpace, kXMLExportMapObjectScriptElement,				kXMLPrefix + 17)
DECLARE_PMID(kScriptInfoIDSpace, kXMLValidationErrorObjectScriptElement,		kXMLPrefix + 18)
DECLARE_PMID(kScriptInfoIDSpace, kXMLCommentObjectScriptElement,				kXMLPrefix + 19)
DECLARE_PMID(kScriptInfoIDSpace, kXMLPIObjectScriptElement,						kXMLPrefix + 20)
DECLARE_PMID(kScriptInfoIDSpace, kXMLItemObjectScriptElement,					kXMLPrefix + 21)
DECLARE_PMID(kScriptInfoIDSpace, kXMLDTDObjectScriptElement,					kXMLPrefix + 22)
DECLARE_PMID(kScriptInfoIDSpace, kXMLStoryObjectScriptElement,					kXMLPrefix + 23)
DECLARE_PMID(kScriptInfoIDSpace, kXMLPreferencesObjectScriptElement,			kXMLPrefix + 24)
DECLARE_PMID(kScriptInfoIDSpace, kXMLRulesProcessorObjectScriptElement,			kXMLPrefix + 25)
DECLARE_PMID(kScriptInfoIDSpace, kXMLRuleMatchDataObjectScriptElement,			kXMLPrefix + 26)
DECLARE_PMID(kScriptInfoIDSpace, kExportForWebPrefsObjectScriptElement,			kXMLPrefix + 27)

//Events
DECLARE_PMID(kScriptInfoIDSpace, kPlaceIntoCopyMethodScriptElement,				kXMLPrefix + 60)
DECLARE_PMID(kScriptInfoIDSpace, kPlaceIntoInlineFrameMethodScriptElement,		kXMLPrefix + 61)
DECLARE_PMID(kScriptInfoIDSpace, kPlaceIntoInlineCopyMethodScriptElement,		kXMLPrefix + 62)
DECLARE_PMID(kScriptInfoIDSpace, kSetContentMethodScriptElement,					kXMLPrefix + 63)
DECLARE_PMID(kScriptInfoIDSpace, kXMLPlaceOntoPageMethodScriptElement,			kXMLPrefix + 64)
DECLARE_PMID(kScriptInfoIDSpace, kApplyTableStyleToElementMethodScriptElement,	kXMLPrefix + 65)
DECLARE_PMID(kScriptInfoIDSpace, kApplyCellStyleToElementMethodScriptElement,	kXMLPrefix + 66)
DECLARE_PMID(kScriptInfoIDSpace, kExportForWebMethodScriptElement,				kXMLPrefix + 67)
//gap
DECLARE_PMID(kScriptInfoIDSpace, kMoveXMLElementMethodScriptElement,				kXMLPrefix + 80)
DECLARE_PMID(kScriptInfoIDSpace, kXMLMarkupMethodScriptElement,					kXMLPrefix + 81)
DECLARE_PMID(kScriptInfoIDSpace, kUntagXMLElementMethodScriptElement,			kXMLPrefix + 82)
DECLARE_PMID(kScriptInfoIDSpace, kCreateXMLElementMethodScriptElement,			kXMLPrefix + 83)
DECLARE_PMID(kScriptInfoIDSpace, kCreateXMLAttributeMethodScriptElement,			kXMLPrefix + 84)
DECLARE_PMID(kScriptInfoIDSpace, kDeleteXMLTagMethodScriptElement,				kXMLPrefix + 85)
DECLARE_PMID(kScriptInfoIDSpace, kCreateXMLTagMethodScriptElement,				kXMLPrefix + 86)
DECLARE_PMID(kScriptInfoIDSpace, kDeleteUnusedTagsMethodScriptElement,			kXMLPrefix + 87)
DECLARE_PMID(kScriptInfoIDSpace, kAutoTagMethodScriptElement,					kXMLPrefix + 88)
DECLARE_PMID(kScriptInfoIDSpace, kCreateXMLExportMapMethodScriptElement,			kXMLPrefix + 89)
DECLARE_PMID(kScriptInfoIDSpace, kCreateXMLImportMapMethodScriptElement,			kXMLPrefix + 90)
DECLARE_PMID(kScriptInfoIDSpace, kImportXMLMethodScriptElement,					kXMLPrefix + 91)
DECLARE_PMID(kScriptInfoIDSpace, kAutoStyleMethodScriptElement,					kXMLPrefix + 92)
DECLARE_PMID(kScriptInfoIDSpace, kImportDTDMethodScriptElement,					kXMLPrefix + 93)
DECLARE_PMID(kScriptInfoIDSpace, kValidateXMLMethodScriptElement,				kXMLPrefix + 94)
DECLARE_PMID(kScriptInfoIDSpace, kImportXMLTagsMethodScriptElement,				kXMLPrefix + 95)
DECLARE_PMID(kScriptInfoIDSpace, kExportXMLTagsMethodScriptElement,				kXMLPrefix + 96)
DECLARE_PMID(kScriptInfoIDSpace, kCreateXMLCommentMethodScriptElement,			kXMLPrefix + 97)
DECLARE_PMID(kScriptInfoIDSpace, kCreateXMLPIMethodScriptElement,				kXMLPrefix + 98)
DECLARE_PMID(kScriptInfoIDSpace, kXMLPlaceMethodScriptElement,					kXMLPrefix + 99)
DECLARE_PMID(kScriptInfoIDSpace, kXMLMarkupObjectMethodScriptElement,			kXMLPrefix + 100)
DECLARE_PMID(kScriptInfoIDSpace, kXMLPlaceObjectMethodScriptElement,				kXMLPrefix + 101)
DECLARE_PMID(kScriptInfoIDSpace, kCreateXMLDTDMethodScriptElement,				kXMLPrefix + 102)
DECLARE_PMID(kScriptInfoIDSpace, kInsertTextAsContentMethodScriptElement,		kXMLPrefix + 103)
DECLARE_PMID(kScriptInfoIDSpace, kXMLRulesStartProcessMethodScriptElement,		kXMLPrefix + 104)
DECLARE_PMID(kScriptInfoIDSpace, kXMLRulesFindNextMatchMethodScriptElement,		kXMLPrefix + 105)
DECLARE_PMID(kScriptInfoIDSpace, kXMLRulesStartSubtreeMethodScriptElement,		kXMLPrefix + 106)
DECLARE_PMID(kScriptInfoIDSpace, kXMLRulesSkipChildrenMethodScriptElement,		kXMLPrefix + 107)
DECLARE_PMID(kScriptInfoIDSpace, kXMLRulesEndProcessMethodScriptElement,			kXMLPrefix + 108)
DECLARE_PMID(kScriptInfoIDSpace, kApplyParaStyleToElementMethodScriptElement,	kXMLPrefix + 109)
DECLARE_PMID(kScriptInfoIDSpace, kApplyCharStyleToElementMethodScriptElement,	kXMLPrefix + 110)
DECLARE_PMID(kScriptInfoIDSpace, kApplyObjectStyleToElementMethodScriptElement,	kXMLPrefix + 111)
DECLARE_PMID(kScriptInfoIDSpace, kPlaceIntoFrameMethodScriptElement,				kXMLPrefix + 112)
DECLARE_PMID(kScriptInfoIDSpace, kXMLRulesHaltMethodScriptElement,				kXMLPrefix + 113)
// gap
DECLARE_PMID(kScriptInfoIDSpace, kCreateXMLRuleProcessorScriptElement,			kXMLPrefix + 115)
DECLARE_PMID(kScriptInfoIDSpace, kConvertElementToAttributeMethodScriptElement,	kXMLPrefix + 116)
DECLARE_PMID(kScriptInfoIDSpace, kConvertAttributeToElementMethodScriptElement,	kXMLPrefix + 117)
DECLARE_PMID(kScriptInfoIDSpace, kConvertElementToTableMethodScriptElement,		kXMLPrefix + 118)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kAssociatedObjectPropertyScriptElement,		kXMLPrefix + 120)
DECLARE_PMID(kScriptInfoIDSpace, kXMLTagPropertyScriptElement,					kXMLPrefix + 121)
DECLARE_PMID(kScriptInfoIDSpace, kValuePropertyScriptElement,					kXMLPrefix + 122)
DECLARE_PMID(kScriptInfoIDSpace, kAssociatedXMLElementPropertyScriptElement,	kXMLPrefix + 123)
DECLARE_PMID(kScriptInfoIDSpace, kAssociatedXMLElementsPropertyScriptElement,	kXMLPrefix + 124)
DECLARE_PMID(kScriptInfoIDSpace, kViewAfterExportPropertyScriptElement,			kXMLPrefix + 126)
DECLARE_PMID(kScriptInfoIDSpace, kPreferredBrowserPropertyScriptElement,		kXMLPrefix + 127)
DECLARE_PMID(kScriptInfoIDSpace, kXMLImportPrefsPropertyScriptElement,			kXMLPrefix + 128)
DECLARE_PMID(kScriptInfoIDSpace, kImportToSelectedPropertyScriptElement,		kXMLPrefix + 129)
DECLARE_PMID(kScriptInfoIDSpace, kImportStylePropertyScriptElement,				kXMLPrefix + 130)
DECLARE_PMID(kScriptInfoIDSpace, kXMLExportPrefsPropertyScriptElement,			kXMLPrefix + 131)
DECLARE_PMID(kScriptInfoIDSpace, kExportFromSelectedPropertyScriptElement,		kXMLPrefix + 132)
DECLARE_PMID(kScriptInfoIDSpace, kFileEncodingPropertyScriptElement,			kXMLPrefix + 133)
DECLARE_PMID(kScriptInfoIDSpace, kExportRubyPropertyScriptElement,				kXMLPrefix + 134)
DECLARE_PMID(kScriptInfoIDSpace, kExcludeDTDPropertyScriptElement,				kXMLPrefix + 135)
DECLARE_PMID(kScriptInfoIDSpace, kXMLElementPropertyScriptElement,				kXMLPrefix + 136)
DECLARE_PMID(kScriptInfoIDSpace, kXMLAttributeNamePropertyScriptElement,		kXMLPrefix + 137)
DECLARE_PMID(kScriptInfoIDSpace, kCopyOriginalImagesPropertyScriptElement,		kXMLPrefix + 138)
DECLARE_PMID(kScriptInfoIDSpace, kCopyOptimizedImagesPropertyScriptElement,		kXMLPrefix + 139)
DECLARE_PMID(kScriptInfoIDSpace, kCopyFormattedImagesPropertyScriptElement,		kXMLPrefix + 140)
DECLARE_PMID(kScriptInfoIDSpace, kImageConversionPropertyScriptElement,			kXMLPrefix + 141)
DECLARE_PMID(kScriptInfoIDSpace, kGIFOptionsPalettePropertyScriptElement,		kXMLPrefix + 142)
DECLARE_PMID(kScriptInfoIDSpace, kGIFOptionsInterlacedPropertyScriptElement,	kXMLPrefix + 143)
DECLARE_PMID(kScriptInfoIDSpace, kJPEGOptionsQualityPropertyScriptElement,		kXMLPrefix + 144)
DECLARE_PMID(kScriptInfoIDSpace, kJPEGOptionsFormatPropertyScriptElement,		kXMLPrefix + 145)
DECLARE_PMID(kScriptInfoIDSpace, kMappedStylePropertyScriptElement,				kXMLPrefix + 146)
DECLARE_PMID(kScriptInfoIDSpace, kXMLTagColorPropertyScriptElement,				kXMLPrefix + 147)
DECLARE_PMID(kScriptInfoIDSpace, kValidationErrorPropertyScriptElement,			kXMLPrefix + 148)
DECLARE_PMID(kScriptInfoIDSpace, kXMLCommentValuePropertyScriptElement,			kXMLPrefix + 149)
DECLARE_PMID(kScriptInfoIDSpace, kXMLPITargetPropertyScriptElement,				kXMLPrefix + 150)
DECLARE_PMID(kScriptInfoIDSpace, kXMLPIDataPropertyScriptElement,				kXMLPrefix + 151)
DECLARE_PMID(kScriptInfoIDSpace, kStyleSheetPropertyScriptElement,				kXMLPrefix + 152)
DECLARE_PMID(kScriptInfoIDSpace, kDTDRootTagPropertyScriptElement,				kXMLPrefix + 153)
DECLARE_PMID(kScriptInfoIDSpace, kDTDSystemLiteralPropertyScriptElement,		kXMLPrefix + 154)
DECLARE_PMID(kScriptInfoIDSpace, kDTDPublicIDPropertyScriptElement,				kXMLPrefix + 155)
DECLARE_PMID(kScriptInfoIDSpace, kXMLContentPropertyScriptElement,				kXMLPrefix + 156)
DECLARE_PMID(kScriptInfoIDSpace, kCreateLinkPropertyScriptElement,				kXMLPrefix + 157)
DECLARE_PMID(kScriptInfoIDSpace, kRepeatingTextPropertyScriptElement,			kXMLPrefix + 158)
DECLARE_PMID(kScriptInfoIDSpace, kDeleteNamespacePropertyScriptElement,			kXMLPrefix + 159)
DECLARE_PMID(kScriptInfoIDSpace, kIgnoreUnmatchedIncomingPropertyScriptElement,	kXMLPrefix + 160)
DECLARE_PMID(kScriptInfoIDSpace, kDeleteUnmatchedExistingPropertyScriptElement,	kXMLPrefix + 161)
DECLARE_PMID(kScriptInfoIDSpace, kDefaultStoryTagNamePropertyScriptElement,		kXMLPrefix + 162)
DECLARE_PMID(kScriptInfoIDSpace, kDefaultStoryTagColorPropertyScriptElement,	kXMLPrefix + 163)
DECLARE_PMID(kScriptInfoIDSpace, kDefaultTableTagNamePropertyScriptElement,		kXMLPrefix + 164)
DECLARE_PMID(kScriptInfoIDSpace, kDefaultTableTagColorPropertyScriptElement,	kXMLPrefix + 165)
DECLARE_PMID(kScriptInfoIDSpace, kDefaultCellTagNamePropertyScriptElement,		kXMLPrefix + 166)
DECLARE_PMID(kScriptInfoIDSpace, kDefaultCellTagColorPropertyScriptElement,		kXMLPrefix + 167)
DECLARE_PMID(kScriptInfoIDSpace, kXMLPreferencesPropertyScriptElement,			kXMLPrefix + 168)
DECLARE_PMID(kScriptInfoIDSpace, kImportTextIntoTablesPropertyScriptElement,	kXMLPrefix + 169)
DECLARE_PMID(kScriptInfoIDSpace, kIgnoreWhitespacePropertyScriptElement,		kXMLPrefix + 170)
DECLARE_PMID(kScriptInfoIDSpace, kDefaultRowTagNamePropertyScriptElement,		kXMLPrefix + 171)
DECLARE_PMID(kScriptInfoIDSpace, kDefaultRowTagColorPropertyScriptElement,		kXMLPrefix + 172)
DECLARE_PMID(kScriptInfoIDSpace, kDefaultImageTagNamePropertyScriptElement,		kXMLPrefix + 173)
DECLARE_PMID(kScriptInfoIDSpace, kDefaultImageTagColorPropertyScriptElement,	kXMLPrefix + 174)
DECLARE_PMID(kScriptInfoIDSpace, kMapIncludeMasterPagePropertyScriptElement,	kXMLPrefix + 175)
DECLARE_PMID(kScriptInfoIDSpace, kMapIncludePasteboardPropertyScriptElement,	kXMLPrefix + 176)
DECLARE_PMID(kScriptInfoIDSpace, kMapIncludeEmptyStoriesPropertyScriptElement,	kXMLPrefix + 177)
DECLARE_PMID(kScriptInfoIDSpace, kAllowTransformPropertyScriptElement,			kXMLPrefix + 178)
DECLARE_PMID(kScriptInfoIDSpace, kTransformFileNamePropertyScriptElement,		kXMLPrefix + 179)
DECLARE_PMID(kScriptInfoIDSpace, kExportCharacterReferencesScriptElement,		kXMLPrefix + 180)
DECLARE_PMID(kScriptInfoIDSpace, kExportUntaggedTablesScriptElement,			kXMLPrefix + 181)
DECLARE_PMID(kScriptInfoIDSpace, kImportCALSTablesScriptElement,				kXMLPrefix + 182)
DECLARE_PMID(kScriptInfoIDSpace, kXMLIsHaltedPropertyScriptElement,				kXMLPrefix + 183)
DECLARE_PMID(kScriptInfoIDSpace, kXMLRulesPropertyScriptElement,				kXMLPrefix + 184)
DECLARE_PMID(kScriptInfoIDSpace, kXMLMatchElementPropertyScriptElement,			kXMLPrefix + 185)
DECLARE_PMID(kScriptInfoIDSpace, kXMLElementLocationEnumScriptElement,			kXMLPrefix + 186)
DECLARE_PMID(kScriptInfoIDSpace, kXMLRulePathsPropertyScriptElement,			kXMLPrefix + 187)
DECLARE_PMID(kScriptInfoIDSpace, kExportForWebPrefsPropertyScriptElement,		kXMLPrefix + 188)
DECLARE_PMID(kScriptInfoIDSpace, kTransformParametersPropertyScriptElement,		kXMLPrefix + 189)
DECLARE_PMID(kScriptInfoIDSpace, kXMLElementPositionEnumScriptElement,			kXMLPrefix + 190)
DECLARE_PMID(kScriptInfoIDSpace, kXMLElementNoMarkerEnumScriptElement,			kXMLPrefix + 191)
DECLARE_PMID(kScriptInfoIDSpace, kXMLNoMarkerPropertyScriptElement,				kXMLPrefix + 192)

DECLARE_PMID(kScriptInfoIDSpace, kXMLImportStylesEnumScriptElement,				kXMLPrefix + 220)
DECLARE_PMID(kScriptInfoIDSpace, kXMLFileEncodingEnumScriptElement,				kXMLPrefix + 221)
DECLARE_PMID(kScriptInfoIDSpace, kImageConversionEnumScriptElement,				kXMLPrefix + 222)
DECLARE_PMID(kScriptInfoIDSpace, kGIFOptionsPaletteEnumScriptElement,			kXMLPrefix + 223)
DECLARE_PMID(kScriptInfoIDSpace, kJPEGOptionsQualityEnumScriptElement,			kXMLPrefix + 224)
DECLARE_PMID(kScriptInfoIDSpace, kJPEGOptionsFormatEnumScriptElement,			kXMLPrefix + 225)
DECLARE_PMID(kScriptInfoIDSpace, kDTDFileEncodingEnumScriptElement,				kXMLPrefix + 226)
DECLARE_PMID(kScriptInfoIDSpace, kXMLExportUntaggedTablesEnumScriptElement,		kXMLPrefix + 227)
DECLARE_PMID(kScriptInfoIDSpace, kXMLMapStylesToTagsMethodScriptElement,			kXMLPrefix + 228)
DECLARE_PMID(kScriptInfoIDSpace, kXMLMapTagsToStylesMethodScriptElement,			kXMLPrefix + 229)
DECLARE_PMID(kScriptInfoIDSpace, kXMLTransformFileEnumScriptElement,			kXMLPrefix + 230)

DECLARE_PMID(kScriptInfoIDSpace, kXMLEvaluateXPathMethodScriptElement,			kXMLPrefix + 240)
DECLARE_PMID(kScriptInfoIDSpace, kDeleteElementOnContentDeletePropertyScriptElement, kXMLPrefix + 241)

// <RuleTargetType ID>
DECLARE_PMID(kRuleTargetTypeIDSpace, kXMLImportTreeXformRuleTargetType, kXMLPrefix + 1)
//DECLARE_PMID(kRuleTargetTypeIDSpace, kXMLFutureRuleTargetType, kXMLPrefix + 2)
//DECLARE_PMID(kRuleTargetTypeIDSpace, kXMLFutureRuleTargetType, kXMLPrefix + 3)
//DECLARE_PMID(kRuleTargetTypeIDSpace, kXMLFutureRuleTargetType, kXMLPrefix + 4)
//DECLARE_PMID(kRuleTargetTypeIDSpace, kXMLFutureRuleTargetType, kXMLPrefix + 5)
//DECLARE_PMID(kRuleTargetTypeIDSpace, kXMLFutureRuleTargetType, kXMLPrefix + 6)
//DECLARE_PMID(kRuleTargetTypeIDSpace, kXMLFutureRuleTargetType, kXMLPrefix + 7)
//DECLARE_PMID(kRuleTargetTypeIDSpace, kXMLFutureRuleTargetType, kXMLPrefix + 8)
//DECLARE_PMID(kRuleTargetTypeIDSpace, kXMLFutureRuleTargetType, kXMLPrefix + 9)
//DECLARE_PMID(kRuleTargetTypeIDSpace, kXMLFutureRuleTargetType, kXMLPrefix + 10)
END_IDS()

#ifndef RESOURCE_NUMBER	 //avoid errors in XMLID.fr

enum XMLScriptIDs
{
	s_XMLSuite =				'K2XL',

	c_XMLElement = 		'cXML',
	c_XMLElements =		'sXML',
	c_XMLAttribute =	'attX',
	c_XMLAttributes =	'atsX',
	c_XMLTag =			'tagX',
	c_XMLTags =			'tgsX',
	c_XMLComment =		'cmtX',
	c_XMLComments =		'ctsX',
	c_XMLPI =			'cpiX',
	c_XMLPIs =			'cpsX',
	c_XMLDTD =			'cdtd',
	c_XMLDTDs =			'cdts',
	c_XMLItem =			'cxit',
	c_XMLItems =		'cxis',
	c_XMLStyleToTagMap = 	'stmX',
	c_XMLStyleToTagMaps = 	'stsX',
	c_XMLTagToStyleMap = 	'tsmX',
	c_XMLTagToStyleMaps = 	'tssX',
	c_XMLValidationError = 	'vlde',
	c_XMLValidationErrors = 	'vlds',
	c_XMLStory = 		'cxst',
	c_XMLStories = 		'cxss',
	c_XMLRulesProcessor = 	'cxrp',
	c_XMLRulesProcessors = 	'cxrs',
	c_XMLRuleMatchData = 	'cxrd',

	c_XMLExportPref =	'xePf',
	p_XMLExportPref =	'pxeP',
	c_XMLImportPref =	'xiPf',
	p_XMLImportPref =	'pxiP',
	c_XMLViewPref =		'xvPf',
	p_XMLViewPref =		'pxvP',
	c_XMLPreferences =	'xgPf',
	p_XMLPreferences =	'pxgP',

	// XML
	e_XMLImport =			'XMLi',
	e_XMLStylesToElements = 'Xste',
	e_XMLMapStylesToTags =	'Xmst',
	e_XMLTagsToStyles = 	'Xtts',
	e_XMLMapTagsToStyles = 	'Xmts',
	e_XMLDeleteUnusedTags = 'Xdut',
	e_XMLUntagElement = 	'Xutg',
	e_XMLImportDTD = 		'Xldt',
	e_XMLImportTags = 		'Xltg',
	e_XMLExportTags = 		'Xstg',
	e_XMLValidate = 		'Xvld',
	e_XMLMarkup =			'Xmku',
	e_XMLPlace =			'Xplc',
	e_XMLRulesStartProcess ='Xrsp',
	e_XMLRulesFindNextMatch='Xrfn',
	e_XMLRulesStartSubtree ='Xrss',
	e_XMLRulesSkipChildren ='Xrsc',
	e_XMLRulesEndProcess =	'Xrep',
	e_XMLRulesHalt =		'Xrht',
	e_XMLEvaluateXPath =	'Xexp',
	p_XPathPrefixMapping =	'Xprm',
	e_XMLConvertAttributeToElement = 'Xcae',
	e_XMLConvertElementToAttribute = 'Xcea',
	e_XMLConvertElementToTable = 'Xcet',
	e_XMLPlaceIntoFrame =	'Xpif',
	e_XMLPlaceIntoCopy =	'Xpic',
	e_XMLPlaceIntoInlineFrame =	'Xpii',
	e_XMLPlaceIntoInlineCopy =	'XpiI',
	e_XMLSetContent =	'Xsec',
	e_XMLInsertTextAsContent = 'Xitc',
	e_XMLApplyTableStyle =	'Xats',
	e_XMLApplyCellStyle =	'Xals',

	// XML Properties
	p_XMLTag				= 'XMLt',
	p_XMLMappedStyle = 'Xmps',
	p_XMLAssociatedObject = 'Xapi',
	p_AssociatedXMLElement = 'Xaxn',
	p_AssociatedXMLElements = 'Xans',
	p_XMLTagColor = 'XTCr',
	p_XMLElement = 'Xelm',
	p_XMLValidationError = 'Xvde',
	p_XMLMaxValidationErrors = 'Xmve',
	p_XMLPITarget = 'Xtrg',
	p_XMLPIData = 'Xdta',
	p_XMLContent = 'Xcnt',
	p_DTDRootTag = 'Drtg',
	p_DTDSystem = 'Dsys',
	p_DTDPublicID = 'Dpbi',
	p_XMLRulesIsHalted = 'pXrh',
	en_kXMLElementLocationEnum = 'eXel',
	en_kXMLElementPositionEnum = 'eXep',
	p_RelativePath = 'XRel',
	p_RetainExistingFrame = 'XRCF',
	p_CopyItem = 'CpIt',

	// XML Export properties
	p_XMLExportFromSelected = 'Xefs',
	p_CopyOriginals = 'Xeco',
	p_OptimizedImages = 'Xeoi',
	p_FormatedImages = 'Xefi',
	p_ImageConversion = 'Xeic',
	p_GIFOptionsPalette = 'Xegp',
	p_GIFOptionsInterlaced = 'Xegi',
	p_JPEGOptionsQuality = 'Xejq',
	p_JPEGOptionsFormat = 'Xejf',
	p_XMLViewAfterExport = 'Xvae',
	p_XMLPreferredBrowser = 'Xprb',
	p_XMLExportRuby = 'Xrub',
	p_XMLExcludeDTD = 'Xdtd',
	p_XMLAllowTransform = 'Xalt',
	p_XMLTransformFilename = 'Xtfn',
	p_XMLExportCharReferences = 'Xcrf',
	p_XMLExportUntaggedTables = 'Xeut',


	// XML Import properties
	p_XMLImportToSelected = 'Xits',
	p_XMLImportStyle = 'XMis',
	p_XMLImportStylesheet = 'Xiss',
	p_XMLImportStylesheetParameters = 'Xisp',
	p_XMLImportCreateLink = 'Xicl',
	p_XMLImportRepeatingText = 'XMrt',
	p_XMLImportIgnoreUnmatchedIncoming = 'Xtal',
	p_XMLImportDeleteUnmatchedExisting = 'Xtar',
	p_XMLImportImportTextIntoTables = 'Xtit',
	p_XMLImportIgnoreWhitespace = 'Xiws',
	p_XMLImportCALSTable = 'Xict',
	p_XMLImportApplyRuleSet = 'Xirs',

	// XML view properties
	p_XMLShowStructure = 'Xsts',
	p_XMLShowTagMarkers = 'Xstm',
	p_XMLShowTaggedFrames = 'Xstf',
	p_XMLShowAttributes	= 'Xsat',
	p_XMLShowTextSnippets = 'Xstn',
	p_XMLShowTagOptions = 'Xsto',

	// XML general preferences
	p_XMLPrefsDefaultStoryName = 'XstN',
	p_XMLPrefsDefaultStoryColor = 'XstC',
	p_XMLPrefsDefaultTableName = 'XtaN',
	p_XMLPrefsDefaultTableColor = 'XtaC',
	p_XMLPrefsDefaultCellName = 'XceN',
	p_XMLPrefsDefaultCellColor = 'XceC',
	p_XMLPrefsDefaultRowName = 'XroN',
	p_XMLPrefsDefaultRowColor = 'XroC',
	p_XMLPrefsDefaultImageName = 'XimN',
	p_XMLPrefsDefaultImageColor = 'XimC',
	p_XMLPrefsDeleteElementOnContentDelete = 'XdeC',
	

	// XML mapping properties
	p_XMLMapIncludeMasterPage = 'XinM',
	p_XMLMapIncludePasteboard = 'XinP',
	p_XMLMapIncludeEmptyStories = 'XinE',

	// XML rules properties
	p_XMLRulePaths = 'Xrps',
	p_XMLStartElmemnt = 'Xsel',
	p_XMLRules = 'pxrs',
	p_XMLTableRowTag = 'Xtrt',
	p_XMLTableCellTag = 'Xtct',

	// INX only properties
	p_XMLNoMarker = 'Xnmk',

	// XML Export
	en_XMLFileEncoding 			= 'XMfE',

	// DTD Import
	en_XMLDTDEncoding 			= 'XMdE',

	// XML Import Styles
	en_XMLImportStyles		= 'Xeis',
	en_XMLAppendImport		= 'XMai',
	en_XMLMergeImport			= 'XMmi',

	// XML Export Untagged Tables Format
	en_XMLExportUntaggedTablesFormat = 'Xutf',
	// en_None
	en_XMLExportUntaggedTablesCALS = 'Xtcs',

	// XML location
	p_Located = 'Loca',
	en_Front = 'Xbgn',
	en_Back = 'Xend',

	// XML position
	en_BeforeElement = 'Xbef',
	en_AfterElement = 'Xaft',

	// XML tranform file
	en_XMLTransformFile = 'Xtrf',
	en_StylesheetInXML = 'Xssx',

	// INX-Alt only
	en_XMLNoMarkerValue = 'Xmkv',
	en_XMLNoMarkerTrue = 'Xnmt',

};

#endif //RESOURCE_NUMBER	 //avoid errors in XMLID.fr

// {88E69192-43A2-11d4-BE38-005004B43E1C}
#define kXMLElement_CLSID { 0x88e69192, 0x43a2, 0x11d4, { 0xbe, 0x38, 0x0, 0x50, 0x4, 0xb4, 0x3e, 0x1c } }
// {02D7A301-43A3-11d4-BE38-005004B43E1C}
#define kXMLElements_CLSID { 0x2d7a301, 0x43a3, 0x11d4, { 0xbe, 0x38, 0x0, 0x50, 0x4, 0xb4, 0x3e, 0x1c } }
// {B439E755-2FBF-4d6f-9737-61F455757DF2}
#define kXMLAttribute_CLSID { 0xb439e755, 0x2fbf, 0x4d6f, { 0x97, 0x37, 0x61, 0xf4, 0x55, 0x75, 0x7d, 0xf2 } }
// {D7A8B643-E3C2-4157-A0C8-06697AB5D6DC}
#define kXMLAttributes_CLSID { 0xd7a8b643, 0xe3c2, 0x4157, { 0xa0, 0xc8, 0x6, 0x69, 0x7a, 0xb5, 0xd6, 0xdc } }
// {1DAF831A-ABD6-4de7-8ADF-A93FC2319046}
#define kXMLTag_CLSID { 0x1daf831a, 0xabd6, 0x4de7, { 0x8a, 0xdf, 0xa9, 0x3f, 0xc2, 0x31, 0x90, 0x46 } }
// {1794DA80-BF48-48cd-BB4A-97AD338D6014}
#define kXMLTags_CLSID { 0x1794da80, 0xbf48, 0x48cd, { 0xbb, 0x4a, 0x97, 0xad, 0x33, 0x8d, 0x60, 0x14 } }
// {E4515245-38B8-48b7-8436-0406E252BA2D}
#define kXMLStyleToTagMap_CLSID { 0xe4515245, 0x38b8, 0x48b7, { 0x84, 0x36, 0x4, 0x6, 0xe2, 0x52, 0xba, 0x2d } }
// {53A1FC77-4B92-4ac1-AB09-400E92CD8D08}
#define kXMLStyleToTagMaps_CLSID { 0x53a1fc77, 0x4b92, 0x4ac1, { 0xab, 0x9, 0x40, 0xe, 0x92, 0xcd, 0x8d, 0x8 } }
// {ECA84203-40B9-4026-9224-52B98FBC66C8}
#define kXMLTagToStyleMap_CLSID { 0xeca84203, 0x40b9, 0x4026, { 0x92, 0x24, 0x52, 0xb9, 0x8f, 0xbc, 0x66, 0xc8 } }
// {B15376C3-C411-49b1-97C1-E6E8F48D1AB5}
#define kXMLTagToStyleMaps_CLSID { 0xb15376c3, 0xc411, 0x49b1, { 0x97, 0xc1, 0xe6, 0xe8, 0xf4, 0x8d, 0x1a, 0xb5 } }
// {0302543E-2584-4fdc-B34E-033E184AF06A}
#define kXMLExportPref_CLSID { 0x302543e, 0x2584, 0x4fdc, { 0xb3, 0x4e, 0x3, 0x3e, 0x18, 0x4a, 0xf0, 0x6a } }
// {83B3674C-FBF7-4f30-80D5-3C8CEFCB91F6}
#define kXMLImportPref_CLSID { 0x83b3674c, 0xfbf7, 0x4f30, { 0x80, 0xd5, 0x3c, 0x8c, 0xef, 0xcb, 0x91, 0xf6 } }
// {7C989388-5C97-4334-BA4F-69A68A38EB40}
#define kXMLValidationError_CLSID { 0x7c989388, 0x5c97, 0x4334, { 0xba, 0x4f, 0x69, 0xa6, 0x8a, 0x38, 0xeb, 0x40 } }
// {4549721A-5127-4d04-A648-0012498543AB}
#define kXMLValidationErrors_CLSID { 0x4549721a, 0x5127, 0x4d04, { 0xa6, 0x48, 0x0, 0x12, 0x49, 0x85, 0x43, 0xab } }
// {F424BB97-A03B-45c1-8C22-91B7B9E11156}
#define kXMLComment_CLSID { 0xf424bb97, 0xa03b, 0x45c1, { 0x8c, 0x22, 0x91, 0xb7, 0xb9, 0xe1, 0x11, 0x56 } }
// {378611AB-EBF7-4bfc-9875-ACEC4E9CD2B2}
#define kXMLComments_CLSID { 0x378611ab, 0xebf7, 0x4bfc, { 0x98, 0x75, 0xac, 0xec, 0x4e, 0x9c, 0xd2, 0xb2 } }
// {2FFEDEB5-0697-4915-B9C9-D4F853179344}
#define kXMLPI_CLSID { 0x2ffedeb5, 0x697, 0x4915, { 0xb9, 0xc9, 0xd4, 0xf8, 0x53, 0x17, 0x93, 0x44 } }
// {B6D9CB8E-8BBA-4628-AD3E-C1CCF73306E6}
#define kXMLPIs_CLSID { 0xb6d9cb8e, 0x8bba, 0x4628, { 0xad, 0x3e, 0xc1, 0xcc, 0xf7, 0x33, 0x6, 0xe6 } }
// {A4505025-C720-423c-A71D-C777DF929488}
#define kXMLItem_CLSID { 0xa4505025, 0xc720, 0x423c, { 0xa7, 0x1d, 0xc7, 0x77, 0xdf, 0x92, 0x94, 0x88 } }
// {87562F2F-96F6-460c-9B54-6A4BD939661E}
#define kXMLItems_CLSID { 0x87562f2f, 0x96f6, 0x460c, { 0x9b, 0x54, 0x6a, 0x4b, 0xd9, 0x39, 0x66, 0x1e } }
// {97AF8B10-0453-4708-8292-83B816A779A4}
#define kXMLDTD_CLSID { 0x97af8b10, 0x453, 0x4708, { 0x82, 0x92, 0x83, 0xb8, 0x16, 0xa7, 0x79, 0xa4 } }
// {EE468C23-AB1B-4e99-8BEE-C0E167A2C101}
#define kXMLDTDs_CLSID { 0xee468c23, 0xab1b, 0x4e99, { 0x8b, 0xee, 0xc0, 0xe1, 0x67, 0xa2, 0xc1, 0x1 } }
// {FDA35D92-547E-41e9-8C42-1024E2DF56A9}
#define kXMLStory_CLSID { 0xfda35d92, 0x547e, 0x41e9, { 0x8c, 0x42, 0x10, 0x24, 0xe2, 0xdf, 0x56, 0xa9 } }
// {4818BF5D-BCF7-4bc3-9FE8-04F4F76563CD}
#define kXMLStories_CLSID { 0x4818bf5d, 0xbcf7, 0x4bc3, { 0x9f, 0xe8, 0x4, 0xf4, 0xf7, 0x65, 0x63, 0xcd } }
// {DAE44318-E686-445d-9580-0AE8A6B9B871}
#define kXMLPreferences_CLSID { 0xdae44318, 0xe686, 0x445d, { 0x95, 0x80, 0xa, 0xe8, 0xa6, 0xb9, 0xb8, 0x71 } }
// {0C4CCDE7-00DE-4fdd-92A1-E49BA443991C}
#define kXMLRuleProcessor_CLSID { 0xc4ccde7, 0xde, 0x4fdd, { 0x92, 0xa1, 0xe4, 0x9b, 0xa4, 0x43, 0x99, 0x1c } }
// {8FC2999B-76FE-4d4d-83E8-DE3040D3412A}
#define kXMLRuleMatchData_CLSID { 0x8fc2999b, 0x76fe, 0x4d4d, { 0x83, 0xe8, 0xde, 0x30, 0x40, 0xd3, 0x41, 0x2a } }
// {9168C38C-4BDC-45d7-AC4A-B8A2F9D6FAFA}
#define kXMLRuleProcessors_CLSID { 0x9168c38c, 0x4bdc, 0x45d7, { 0xac, 0x4a, 0xb8, 0xa2, 0xf9, 0xd6, 0xfa, 0xfa } }
// {B7D43298-793B-45c1-BEE2-61F4ADCA1771}
#define kExportForWebPref_CLSID {0xb7d43298, 0x793b, 0x45c1, {0xbe, 0xe2, 0x61, 0xf4, 0xad, 0xca, 0x17, 0x71} }

// Don't show again IDs
#define kDeleteDTDAlertID			kXMLPrefix  + 1
#endif

