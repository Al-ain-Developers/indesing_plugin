//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/BNCoreID.h $
//  
//  Owner: vbatra
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

#ifndef __BNCoreID__
#define __BNCoreID__

#include "BNTextAttrID.h"

#define BN_NUMBER_BY_PAGE
#define BN_SUPPRESS_FOR_HIDDEN_LAYERS

// Class IDs:
DECLARE_PMID(kClassIDSpace, kBNFormatConversionBoss, kBNCorePrefix + 101)
DECLARE_PMID(kClassIDSpace, kBNNewWorkspaceResponderBoss, kBNCorePrefix + 102)
DECLARE_PMID(kClassIDSpace, kBNNewDocResponderBoss, kBNCorePrefix + 103)
DECLARE_PMID(kClassIDSpace, kBNPhase2ConverterBoss, kBNCorePrefix + 104)
DECLARE_PMID(kClassIDSpace, kBNListInvalServiceBoss, kBNCorePrefix + 105)
DECLARE_PMID(kClassIDSpace, kBNTextPropsINXProviderBoss, kBNCorePrefix + 106)
DECLARE_PMID(kClassIDSpace, kBNTextPropsScriptProviderBoss, kBNCorePrefix + 107)
DECLARE_PMID(kClassIDSpace, kBNBulletCharacterScriptProviderBoss, kBNCorePrefix + 108)
DECLARE_PMID(kClassIDSpace, kBNFontINXProvider40Boss, kBNCorePrefix + 109)
DECLARE_PMID(kClassIDSpace, kBNFontScriptProvider40Boss, kBNCorePrefix + 110)
DECLARE_PMID(kClassIDSpace, kBNEventScriptProviderBoss, kBNCorePrefix + 111)
DECLARE_PMID(kClassIDSpace, kBNWritePreferencesCmdBoss, kBNCorePrefix + 112)
DECLARE_PMID(kClassIDSpace, kBNCodeConversionProviderBoss, kBNCorePrefix + 113)
// New numbering style bosses. Please do not change these IDs, since they form part of
// persistent data in a document.
DECLARE_PMID(kClassIDSpace, kKanjiParaNumberingStyleServiceBoss, kBNCorePrefix + 114)
DECLARE_PMID(kClassIDSpace, kDoubleZeroParaNumberingStyleServiceBoss, kBNCorePrefix + 115)
DECLARE_PMID(kClassIDSpace, kTripleZeroParaNumberingStyleServiceBoss, kBNCorePrefix + 116)
DECLARE_PMID(kClassIDSpace, kKatakanaModernParaNumberingStyleServiceBoss, kBNCorePrefix + 117)
DECLARE_PMID(kClassIDSpace, kKatakanaTraditionalParaNumberingStyleServiceBoss, kBNCorePrefix + 118)
DECLARE_PMID(kClassIDSpace, kArabicParaNumberingStyleServiceBoss, kBNCorePrefix + 119)
DECLARE_PMID(kClassIDSpace, kRomanUpperParaNumberingStyleServiceBoss, kBNCorePrefix + 120)
DECLARE_PMID(kClassIDSpace, kRomanLowerParaNumberingStyleServiceBoss, kBNCorePrefix + 121)
DECLARE_PMID(kClassIDSpace, kLettersUpperParaNumberingStyleServiceBoss, kBNCorePrefix + 122)
DECLARE_PMID(kClassIDSpace, kLettersLowerParaNumberingStyleServiceBoss, kBNCorePrefix + 123)

DECLARE_PMID(kClassIDSpace, kBNConvertToTextCmdBoss, kBNCorePrefix + 124)
DECLARE_PMID(kClassIDSpace, kBNStyleConvertToTextCmdBoss, kBNCorePrefix + 125)
DECLARE_PMID(kClassIDSpace, kBNTableEventScriptProviderBoss, kBNCorePrefix + 126)
DECLARE_PMID(kClassIDSpace, kBNParaStyleEventScriptProviderBoss, kBNCorePrefix + 127)
DECLARE_PMID(kClassIDSpace, kBNErrorStringServiceBoss, kBNCorePrefix + 128)

// Bullet Collection
DECLARE_PMID(kClassIDSpace, kBNBulletCollectionScriptProviderBoss, kBNCorePrefix + 129)
DECLARE_PMID(kClassIDSpace, kBNBulletCollectionScriptObjectBoss, kBNCorePrefix + 130)

//List
DECLARE_PMID(kClassIDSpace, kListStyleBoss,						kBNCorePrefix + 131)
DECLARE_PMID(kClassIDSpace, kNumberedListBlockBoss,				kBNCorePrefix + 132)
// Gap 133
DECLARE_PMID(kClassIDSpace, kCreateListStyleCmdBoss,			kBNCorePrefix + 134)
DECLARE_PMID(kClassIDSpace, kEditListStyleCmdBoss,				kBNCorePrefix + 135)
DECLARE_PMID(kClassIDSpace, kDeleteListStyleCmdBoss,			kBNCorePrefix + 136)
DECLARE_PMID(kClassIDSpace, kNumberedListTrackerBoss,			kBNCorePrefix + 137)
DECLARE_PMID(kClassIDSpace, kNumberedListMgrIndexStorageBoss,	kBNCorePrefix + 138)
DECLARE_PMID(kClassIDSpace, kCopyListStyleCmdBoss,				kBNCorePrefix + 139)
DECLARE_PMID(kClassIDSpace, kListStyleRefConverterBoss,			kBNCorePrefix + 140)
DECLARE_PMID(kClassIDSpace, kListStyleNewDocResponderBoss,		kBNCorePrefix + 141)
DECLARE_PMID(kClassIDSpace, kListStyleNewWSResponderBoss,		kBNCorePrefix + 142)
DECLARE_PMID(kClassIDSpace, kLoadListStylesCmdBoss,				kBNCorePrefix + 143)
DECLARE_PMID(kClassIDSpace, kBNNewScrapDocResponderBoss,		kBNCorePrefix + 144)
DECLARE_PMID(kClassIDSpace, kListStyleNewScrapDocResponderBoss,		kBNCorePrefix + 145)

// Advanced Numbering
DECLARE_PMID(kClassIDSpace, kBNTextPropsINXProvider50Boss, kBNCorePrefix + 146)
DECLARE_PMID(kClassIDSpace, kBNTextPropsScriptProvider50Boss, kBNCorePrefix + 147)
DECLARE_PMID(kClassIDSpace, kBNListCollectionScriptProviderBoss, kBNCorePrefix + 148)
DECLARE_PMID(kClassIDSpace, kBNRestartPolicyScriptProviderBoss, kBNCorePrefix + 149)
DECLARE_PMID(kClassIDSpace, kBNRestartPolicyScriptObjectBoss, kBNCorePrefix + 150)
// Single Zero Numbering Style to be added.
DECLARE_PMID(kClassIDSpace, kSingleZeroParaNumberingStyleServiceBoss, kBNCorePrefix + 151)
DECLARE_PMID(kClassIDSpace, kModifyChapterNumPrefCmdBoss, kBNCorePrefix + 152)
DECLARE_PMID(kClassIDSpace, kBNChapterNumPrefsScriptProviderBoss, kBNCorePrefix + 153)
DECLARE_PMID(kClassIDSpace, kBNOpenDocResponderBoss, kBNCorePrefix + 154)
DECLARE_PMID(kClassIDSpace, kBNCloseDocResponderBoss, kBNCorePrefix + 155)
DECLARE_PMID(kClassIDSpace, kBNListStylesSyncBoss, kBNCorePrefix + 156)
DECLARE_PMID(kClassIDSpace, kNumberedListBookDataHolderBoss, kBNCorePrefix + 157)
// gap 158-160
// Korean Numbering Styles
// New numbering style bosses. Please do not change these IDs, since they form part of
// persistent data in a document.
DECLARE_PMID(kClassIDSpace, kKoreanNumbering1StyleServiceBoss, kBNCorePrefix + 161)
DECLARE_PMID(kClassIDSpace, kKoreanNumbering2StyleServiceBoss, kBNCorePrefix + 162)
DECLARE_PMID(kClassIDSpace, kKoreanDoubleByteNumbering2StyleServiceBoss, kBNCorePrefix + 163)

// Chinese/Taiwanese
DECLARE_PMID(kClassIDSpace, kChineseNumbering4StyleServiceBoss, kBNCorePrefix + 166)
DECLARE_PMID(kClassIDSpace, kCircleNumberingStyleServiceBoss, kBNCorePrefix + 167)
DECLARE_PMID(kClassIDSpace, kChineseZodiacNumbering1StyleServiceBoss, kBNCorePrefix + 168)
DECLARE_PMID(kClassIDSpace, kChineseZodiacNumbering2StyleServiceBoss, kBNCorePrefix + 169)
DECLARE_PMID(kClassIDSpace, kTaiwaneseDoubleByteNumbering2StyleServiceBoss, kBNCorePrefix + 170)




// Interface IDs:
//Model-UI Separation
DECLARE_PMID(kInterfaceIDSpace, IID_IBNPREFERENCES, kBNCorePrefix + 10)
//list
DECLARE_PMID(kInterfaceIDSpace, IID_ILISTSTYLEINFO,				kBNCorePrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_ILISTSTYLENAMETABLE,		kBNCorePrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_INUMBEREDLISTBLOCK,			kBNCorePrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_INUMBEREDLISTSERVICE,		kBNCorePrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_INUMBEREDLISTSTORAGEMGR,	kBNCorePrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_INUMBERINGUTILS,			kBNCorePrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_ILISTSTYLETOSTORAGEMGRMAP,	kBNCorePrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_ICHAPTERNUMBERPREFERENCES,	kBNCorePrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_ICHAPTERNUMBERDATA,			kBNCorePrefix + 19)

DECLARE_PMID(kInterfaceIDSpace, IID_IBNLAYOUTOBSERVER,			kBNCorePrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_INUMBEREDLISTBOOKDATA,		kBNCorePrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTORYNUMBERINGINFO,		kBNCorePrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRACKERSTORYLIST,			kBNCorePrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_INUMBEREDSTORYLIST,			kBNCorePrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_IBNCONVERSIONUTILS,			kBNCorePrefix + 25)


// Implementation IDs:
DECLARE_PMID(kImplementationIDSpace, kBNListTypeAttributeImpl, kBNCorePrefix + 1)

DECLARE_PMID(kImplementationIDSpace, kBNFontUIDAttributeImpl_obsolete, kBNCorePrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kBNFontStyleAttributeImpl_obsolete, kBNCorePrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kBNConversionUtilsImpl, kBNCorePrefix + 4)

// Gap 5

DECLARE_PMID(kImplementationIDSpace, kBNBulletCharacterAttributeImpl, kBNCorePrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kBNNumberStartAtAttributeImpl, kBNCorePrefix + 7)
// Gap 8-10
DECLARE_PMID(kImplementationIDSpace, kBNNumberingStyleAttributeImpl, kBNCorePrefix + 11)

//DECLARE_PMID(kImplementationIDSpace, kBNListTypeAttrImpExpImpl, kBNCorePrefix + 12)
//DECLARE_PMID(kImplementationIDSpace, kBNNumberingStyleAttrImpExpImpl, kBNCorePrefix + 13)
//DECLARE_PMID(kImplementationIDSpace, kBNBulletCharAttrImpExpImpl, kBNCorePrefix + 14)
//DECLARE_PMID(kImplementationIDSpace, kBNFontStyleAttrImpExpImpl, kBNCorePrefix + 15)
//DECLARE_PMID(kImplementationIDSpace, kBNFontUIDAttrImpExpImpl, kBNCorePrefix + 16)
//DECLARE_PMID(kImplementationIDSpace, kBNSizeAttrImpExpImpl_obsolete, kBNCorePrefix + 17)
//DECLARE_PMID(kImplementationIDSpace, kBNColorAttrImpExpImpl_obsolete, kBNCorePrefix + 18)
//DECLARE_PMID(kImplementationIDSpace, kBNNumberStartAtAttrImpExpImpl, kBNCorePrefix + 19)
//DECLARE_PMID(kImplementationIDSpace, kBNNumberSeparatorAttrImpExpImpl_obsolete, kBNCorePrefix + 20)

DECLARE_PMID(kImplementationIDSpace, kBNLayoutObserverImpl, kBNCorePrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kBNOpenDocResponderImpl, kBNCorePrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kBNCloseDocResponderImpl, kBNCorePrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kBNStoryNumberingInfoImpl, kBNCorePrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kBNTrackerStoryListImpl, kBNCorePrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kBNNumberedStoryListImpl, kBNCorePrefix + 17)

DECLARE_PMID(kImplementationIDSpace, kTextAttrNumberingStyleImpl, kBNCorePrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kTextAttrListTypeImpl, kBNCorePrefix + 22)

DECLARE_PMID(kImplementationIDSpace, kBNInCopyXMLValueListTypeImpl, kBNCorePrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kBNInCopyXMLValueNumStyleImpl, kBNCorePrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kBNInCopyXMLValueBulletCharImpl, kBNCorePrefix + 25)

DECLARE_PMID(kImplementationIDSpace, kBNInCopyXMLValueFontStyleImpl_obsolete, kBNCorePrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kBNInCopyXMLValueFontUIDImpl_obsolete, kBNCorePrefix + 27)

DECLARE_PMID(kImplementationIDSpace, kBNInCopyXMLValueSizeImpl_obsolete, kBNCorePrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kBNInCopyXMLValueColorImpl_obsolete, kBNCorePrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kBNInCopyXMLValueNumStartAtImpl, kBNCorePrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kBNInCopyXMLValueNumSeparatorImpl_obsolete, kBNCorePrefix + 31)

DECLARE_PMID(kImplementationIDSpace, kBNNumberProviderClassIDImpl, kBNCorePrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kBNTextAttrBulletCharImpl, kBNCorePrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kBNTextAttrNumSeparatorImpl_obsolete, kBNCorePrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kBNTextAttrSizeImpl_obsolete, kBNCorePrefix + 53)

DECLARE_PMID(kImplementationIDSpace, kBNDrawingStyleImpl, kBNCorePrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kBNNewDocResponderImpl, kBNCorePrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kBNTextAttrSizeScalableMeasureImpl_obsolete, kBNCorePrefix + 72)

DECLARE_PMID(kImplementationIDSpace, kBNTextPropsINXProviderImpl, kBNCorePrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kBNTextPropsScriptProviderImpl, kBNCorePrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kBNBulletCharacterScriptProviderImpl, kBNCorePrefix + 102)

DECLARE_PMID(kImplementationIDSpace, kBNIteratorRegImpl, kBNCorePrefix + 112)
// Gap

DECLARE_PMID(kImplementationIDSpace, kBNBulletFontUIDAttributeImpl, kBNCorePrefix + 120)
DECLARE_PMID(kImplementationIDSpace, kBNBulletFontStyleAttributeImpl, kBNCorePrefix + 121)
// Gap 122-124

//DECLARE_PMID(kImplementationIDSpace, kBNBulletFontStyleAttrImpExpImpl, kBNCorePrefix + 124)
DECLARE_PMID(kImplementationIDSpace, kBNInCopyXMLValueBulletFontStyleImpl, kBNCorePrefix + 125)
//DECLARE_PMID(kImplementationIDSpace, kBNNumberingFontStyleAttrImpExpImpl_obsolete, kBNCorePrefix + 126)
DECLARE_PMID(kImplementationIDSpace, kBNInCopyXMLValueNumberingFontStyleImpl_obsolete, kBNCorePrefix + 127)
//DECLARE_PMID(kImplementationIDSpace, kBNNumberingFontUIDAttrImpExpImpl_obsolete, kBNCorePrefix + 128)
DECLARE_PMID(kImplementationIDSpace, kBNInCopyXMLValueNumberingFontUIDImpl_obsolete, kBNCorePrefix + 129)
//DECLARE_PMID(kImplementationIDSpace, kBNBulletFontUIDAttrImpExpImpl, kBNCorePrefix + 130)
DECLARE_PMID(kImplementationIDSpace, kBNInCopyXMLValueBulletFontUIDImpl, kBNCorePrefix + 131)

DECLARE_PMID(kImplementationIDSpace, kBNFontINXProvider40Impl, kBNCorePrefix + 133)

DECLARE_PMID(kImplementationIDSpace, kBNFontUIDElementV3CompatHandlerImpl, kBNCorePrefix + 134)
DECLARE_PMID(kImplementationIDSpace, kBNFontStyleElementV3CompatHandlerImpl, kBNCorePrefix + 135)

// Model-UI separation - moving preferences. The implementation ID for preferences should not be changed
// as it is persistent data.
DECLARE_PMID(kImplementationIDSpace, kBNPreferencesImpl, kBNCorePrefix + 136)

DECLARE_PMID(kImplementationIDSpace, kBNWritePreferencesImpl, kBNCorePrefix + 137)
DECLARE_PMID(kImplementationIDSpace, kBNNewWorkspaceResponderImpl, kBNCorePrefix + 138)
DECLARE_PMID(kImplementationIDSpace, kBNPhase2ConverterImpl, kBNCorePrefix + 139)
DECLARE_PMID(kImplementationIDSpace, kBNFontScriptProvider40Impl, kBNCorePrefix + 140)
DECLARE_PMID(kImplementationIDSpace, kBNEventScriptProviderImpl, kBNCorePrefix + 141)
DECLARE_PMID(kImplementationIDSpace, kBNCodeConversionProviderImpl, kBNCorePrefix + 142)
DECLARE_PMID(kImplementationIDSpace, kBNParagraphNumberingStylesService, kBNCorePrefix + 143)
DECLARE_PMID(kImplementationIDSpace, kBNDefaultParaNumberingStylesService, kBNCorePrefix + 144)

DECLARE_PMID(kImplementationIDSpace, kBNConvertToTextCmdImpl, kBNCorePrefix + 145)
DECLARE_PMID(kImplementationIDSpace, kBNStyleConvertToTextCmdImpl, kBNCorePrefix + 146)
DECLARE_PMID(kImplementationIDSpace, kBulletsAndNumberingSuiteASBImpl, kBNCorePrefix + 147)
DECLARE_PMID(kImplementationIDSpace, kBulletsAndNumberingSuiteCSBImpl, kBNCorePrefix + 148)

DECLARE_PMID(kImplementationIDSpace, kBNTableEventScriptProviderImpl, kBNCorePrefix + 149)
DECLARE_PMID(kImplementationIDSpace, kBNParaStyleEventScriptProviderImpl, kBNCorePrefix + 150)
DECLARE_PMID(kImplementationIDSpace, kBNErrorStringServiceImpl, kBNCorePrefix + 151)

// Bullet Collection
DECLARE_PMID(kImplementationIDSpace, kBNBulletCollectionScriptImpl,		kBNCorePrefix + 152)
DECLARE_PMID(kImplementationIDSpace, kBNBulletCollectionScriptProviderImpl,		kBNCorePrefix + 153)

//list
DECLARE_PMID(kImplementationIDSpace, kListStyleInfoImpl,				kBNCorePrefix + 154)
DECLARE_PMID(kImplementationIDSpace, kListStyleNameTableImpl,			kBNCorePrefix + 155)
DECLARE_PMID(kImplementationIDSpace, kNumberedListBlockImpl,			kBNCorePrefix + 156)
DECLARE_PMID(kImplementationIDSpace, kNumberedListParagraphTrackerImpl,	kBNCorePrefix + 157)
DECLARE_PMID(kImplementationIDSpace, kBNListStylesSyncServiceImpl,		kBNCorePrefix + 158)
DECLARE_PMID(kImplementationIDSpace, kNumberedListBookDataImpl,			kBNCorePrefix + 159)
DECLARE_PMID(kImplementationIDSpace, kNumberedListBookDataHolderImpl,	kBNCorePrefix + 160)
DECLARE_PMID(kImplementationIDSpace, kCreateListStyleCmdImpl,			kBNCorePrefix + 161)
DECLARE_PMID(kImplementationIDSpace, kBNListStyleUIDAttributeImpl,		kBNCorePrefix + 162)
DECLARE_PMID(kImplementationIDSpace, kBNListLevelAttributeImpl,			kBNCorePrefix + 163)
DECLARE_PMID(kImplementationIDSpace, kBNNumberingCFPreviousAttributeImpl,kBNCorePrefix + 164)
DECLARE_PMID(kImplementationIDSpace, kBNRestartPolicyAttributeImpl,		kBNCorePrefix + 165)
DECLARE_PMID(kImplementationIDSpace, kTextAttrRestartPolicyImpl,		kBNCorePrefix + 166)
DECLARE_PMID(kImplementationIDSpace, kNumberingUtilsImpl,				kBNCorePrefix + 167)
DECLARE_PMID(kImplementationIDSpace, kBNBulletCharStyleAttributeImpl,	kBNCorePrefix + 168)
DECLARE_PMID(kImplementationIDSpace, kBNNumberCharStyleAttributeImpl,	kBNCorePrefix + 169)
DECLARE_PMID(kImplementationIDSpace, kBNBulletAlignmentAttributeImpl,	kBNCorePrefix + 170)
DECLARE_PMID(kImplementationIDSpace, kTextAttrBulletAlignmentImpl,		kBNCorePrefix + 171)
DECLARE_PMID(kImplementationIDSpace, kBNNumberAlignmentAttributeImpl,	kBNCorePrefix + 172)
DECLARE_PMID(kImplementationIDSpace, kTextAttrNumberAlignmentImpl,		kBNCorePrefix + 173)
DECLARE_PMID(kImplementationIDSpace, kBNNumberingNumberAttributeImpl,	kBNCorePrefix + 174)
DECLARE_PMID(kImplementationIDSpace, kBNBulletTextAfterAttributeImpl,	kBNCorePrefix + 175)
DECLARE_PMID(kImplementationIDSpace, kEditListStyleCmdImpl,				kBNCorePrefix + 176)
DECLARE_PMID(kImplementationIDSpace, kDeleteListStyleCmdImpl,			kBNCorePrefix + 177)
DECLARE_PMID(kImplementationIDSpace, kBNShouldRestartAttributeImpl,		kBNCorePrefix + 178)
DECLARE_PMID(kImplementationIDSpace, kNumberedListStorageMgrImpl,		kBNCorePrefix + 179)
DECLARE_PMID(kImplementationIDSpace, kNumberedListMgrIndexStorageImpl,	kBNCorePrefix + 180)
DECLARE_PMID(kImplementationIDSpace, kListStyleToStorageMgrMapImpl,		kBNCorePrefix + 181)
DECLARE_PMID(kImplementationIDSpace, kCopyListStyleCmdImpl,				kBNCorePrefix + 182)
DECLARE_PMID(kImplementationIDSpace, kListStyleRefConverterImpl,		kBNCorePrefix + 183)
DECLARE_PMID(kImplementationIDSpace, kListStyleNewWSResponderImpl,		kBNCorePrefix + 184)
DECLARE_PMID(kImplementationIDSpace, kListStyleNewDocResponderImpl,		kBNCorePrefix + 185)
DECLARE_PMID(kImplementationIDSpace, kLoadListStylesCmdImpl,			kBNCorePrefix + 186)
DECLARE_PMID(kImplementationIDSpace, kTextAttrNumberStringImpl,			kBNCorePrefix + 187)
DECLARE_PMID(kImplementationIDSpace, kTextAttrTextAfterStringImpl,		kBNCorePrefix + 188)
DECLARE_PMID(kImplementationIDSpace, kBNNewScrapDocResponderImpl,		kBNCorePrefix + 189)
DECLARE_PMID(kImplementationIDSpace, kListStyleNewScrapDocResponderImpl,kBNCorePrefix + 190)
// Advanced Numbering
DECLARE_PMID(kImplementationIDSpace, kBNTextPropsINXProvider50Impl, kBNCorePrefix + 191)
DECLARE_PMID(kImplementationIDSpace, kBNTextPropsScriptProvider50Impl, kBNCorePrefix + 192)
DECLARE_PMID(kImplementationIDSpace, kBNListCollectionScriptProviderImpl, kBNCorePrefix + 193)
DECLARE_PMID(kImplementationIDSpace, kBNRestartPolicyScriptProviderImpl, kBNCorePrefix + 194)
DECLARE_PMID(kImplementationIDSpace, kBNListStyleScriptImpl,        kBNCorePrefix + 195)
DECLARE_PMID(kImplementationIDSpace, kBNChapterNumberPrefImpl,			kBNCorePrefix + 196)
DECLARE_PMID(kImplementationIDSpace, kModifyChapterNumPrefCmdImpl,		kBNCorePrefix + 197)
DECLARE_PMID(kImplementationIDSpace, kBNChapterNumPrefsScriptProviderImpl,kBNCorePrefix + 198)
// New Locale Independent Single Zero Number Converter
DECLARE_PMID(kImplementationIDSpace, kSingleZeroIndependentNumberConverterImpl,  kBNCorePrefix + 199)
// Implementaion ID range 200 onwards is in BNTextAttrID.h

// ActionIDs:

// WidgetIDs:

// Error IDs:
DECLARE_PMID(kErrorIDSpace, kBNCharAndTypeRequiredError,		kBNCorePrefix + 1)
DECLARE_PMID(kErrorIDSpace, kBNFontReqdForUnicodeWithFontError,	kBNCorePrefix + 2)
DECLARE_PMID(kErrorIDSpace, kBNFontReqdForGlyphWithFontError,	kBNCorePrefix + 3)
DECLARE_PMID(kErrorIDSpace, kBNTextFontStyleForNonTextFontError,kBNCorePrefix + 4)
DECLARE_PMID(kErrorIDSpace, kBNMissingFontStyleForFontError,	kBNCorePrefix + 5)
DECLARE_PMID(kErrorIDSpace, kBNNegativeLeftIndentError,			kBNCorePrefix + 6)
DECLARE_PMID(kErrorIDSpace, kBNNeedLIAndFLIError,				kBNCorePrefix + 7)
DECLARE_PMID(kErrorIDSpace, kBNNegativeLIPlusFLIError,			kBNCorePrefix + 8)
DECLARE_PMID(kErrorIDSpace, kBNNeedTabBetweenLIAndFLIError,		kBNCorePrefix + 9)
DECLARE_PMID(kErrorIDSpace, kBNNeedTabAfterFLIError,			kBNCorePrefix + 10)
DECLARE_PMID(kErrorIDSpace, kBNLIMustBeAtLeast18pError,			kBNCorePrefix + 11)
DECLARE_PMID(kErrorIDSpace, kBNInvalidNumberingStyleError,		kBNCorePrefix + 12)
DECLARE_PMID(kErrorIDSpace, kBNFindChangeListNoneError,			kBNCorePrefix + 13)
DECLARE_PMID(kErrorIDSpace, kBNFindChangeListBulletError,		kBNCorePrefix + 14)
DECLARE_PMID(kErrorIDSpace, kBNFindChangeListNumberError,		kBNCorePrefix + 15)
DECLARE_PMID(kErrorIDSpace, kInvalidLevelInPolicyError,			kBNCorePrefix + 16)
DECLARE_PMID(kErrorIDSpace, kPolicyCannotBeBlankError,			kBNCorePrefix + 17)
DECLARE_PMID(kErrorIDSpace, kBNDeleteDefaultListStyleError,		kBNCorePrefix + 18)
DECLARE_PMID(kErrorIDSpace, kBNModifyDefaultListStyleError,		kBNCorePrefix + 19)
DECLARE_PMID(kErrorIDSpace, kBNInvalidTextAfterTabSpaceError,	kBNCorePrefix + 20)
DECLARE_PMID(kErrorIDSpace, kBNInvalidNumberLevelPlaceholdersError,	kBNCorePrefix + 21)
DECLARE_PMID(kErrorIDSpace, kBNInvalidNumberFormatNoneError,	kBNCorePrefix + 22)
DECLARE_PMID(kErrorIDSpace, kBNInvalidNumberTabSpaceError,		kBNCorePrefix + 23)
DECLARE_PMID(kErrorIDSpace, kBNEmptyListStyleNameError,			kBNCorePrefix + 24)
DECLARE_PMID(kErrorIDSpace, kBNExistingListStyleNameError,		kBNCorePrefix + 25)
DECLARE_PMID(kErrorIDSpace, kBNChapterNumberNotUserDefinedError,kBNCorePrefix + 26)
DECLARE_PMID(kErrorIDSpace, kBNDocIsNotContentOfBookError,		kBNCorePrefix + 27)
DECLARE_PMID(kErrorIDSpace, kBNInvalidListError,				kBNCorePrefix + 28)


//
// ScriptElementIDs:
//

//awahi - Restored bullet char elements
////vbatra - As a fix for Bug# 624035, Bullet character object and the associated child properties have been
////moved over to BNUI project (as these properties are used only by external scripting e.g. vbscript, jscript). For
////inx roundtripping BNBulletCharacter attributed is a record-type object.
////Also commented declaration of kBNBulletCharacterTypePropertyScriptElement and kBNBulletCharacterValuePropertyScriptElement

// Objects
DECLARE_PMID(kScriptInfoIDSpace, kBNBulletCharacterObjectScriptElement,	kBNCorePrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kBNBulletCollectionObjectScriptElement, kBNCorePrefix + 2)

// Properties
DECLARE_PMID(kScriptInfoIDSpace, kBNListTypePropertyScriptElement,	kBNCorePrefix + 101)
DECLARE_PMID(kScriptInfoIDSpace, kBNNumberingStylePropertyScriptElement,  kBNCorePrefix + 102)
DECLARE_PMID(kScriptInfoIDSpace, kBNBulletCharacterPropertyScriptElement, kBNCorePrefix + 103)
DECLARE_PMID(kScriptInfoIDSpace, kBNFontUIDPropertyScriptElement,  	kBNCorePrefix + 104)
DECLARE_PMID(kScriptInfoIDSpace, kBNFontStylePropertyScriptElement,  	kBNCorePrefix + 105)
DECLARE_PMID(kScriptInfoIDSpace, kBNSizePropertyScriptElement,  kBNCorePrefix + 106)
DECLARE_PMID(kScriptInfoIDSpace, kBNColorPropertyScriptElement, kBNCorePrefix + 107)
DECLARE_PMID(kScriptInfoIDSpace, kBNNumberStartAtPropertyScriptElement,  kBNCorePrefix + 108)
DECLARE_PMID(kScriptInfoIDSpace, kBNNumberSeparatorPropertyScriptElement,kBNCorePrefix + 109)
DECLARE_PMID(kScriptInfoIDSpace, kBNBulletCharacterTypePropertyScriptElement,kBNCorePrefix + 110)
DECLARE_PMID(kScriptInfoIDSpace, kBNBulletCharacterValuePropertyScriptElement,kBNCorePrefix + 111)
DECLARE_PMID(kScriptInfoIDSpace, kBNBulletFontUIDPropertyScriptElement,  	kBNCorePrefix + 112)
DECLARE_PMID(kScriptInfoIDSpace, kBNBulletFontStylePropertyScriptElement,  	kBNCorePrefix + 113)
DECLARE_PMID(kScriptInfoIDSpace, kBNNumberingFontUIDPropertyScriptElement,  	kBNCorePrefix + 114)
DECLARE_PMID(kScriptInfoIDSpace, kBNNumberingFontStylePropertyScriptElement,  	kBNCorePrefix + 115)

//Scripting Events
DECLARE_PMID(kScriptInfoIDSpace, kCreateListMethodScriptElement,  	kBNCorePrefix + 175)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kBNListTypeEnumScriptElement, 	kBNCorePrefix + 200)
DECLARE_PMID(kScriptInfoIDSpace, kBNBulletCharacterTypeEnumScriptElement, 	kBNCorePrefix + 201)
DECLARE_PMID(kScriptInfoIDSpace, kBNNumberingStyleEnumScriptElement, 	kBNCorePrefix + 202)
DECLARE_PMID(kScriptInfoIDSpace, kBNAutoFontUIDEnumScriptElement, kBNCorePrefix  + 203)
DECLARE_PMID(kScriptInfoIDSpace, kBNAutoFontStyleEnumScriptElement, kBNCorePrefix  + 204)
DECLARE_PMID(kScriptInfoIDSpace, kBNAutoColorEnumScriptElement, kBNCorePrefix  + 205)
DECLARE_PMID(kScriptInfoIDSpace, kBNAutoSizeEnumScriptElement, kBNCorePrefix  + 206)
//gap
DECLARE_PMID(kScriptInfoIDSpace, kBNRestartPolicyEnumScriptElement, kBNCorePrefix  + 208)
//gap
DECLARE_PMID(kScriptInfoIDSpace, kBNApplyBulletsMethodScriptElement, kBNCorePrefix  + 210)
DECLARE_PMID(kScriptInfoIDSpace, kBNApplyNumbersMethodScriptElement, kBNCorePrefix  + 211)
DECLARE_PMID(kScriptInfoIDSpace, kBNRemoveBulletsNumbersMethodScriptElement, kBNCorePrefix  + 212)
DECLARE_PMID(kScriptInfoIDSpace, kBNAlignmentEnumScriptElement, kBNCorePrefix  + 213)
DECLARE_PMID(kScriptInfoIDSpace, kBNConvertBNToTextMethodScriptElement, kBNCorePrefix  + 214)
DECLARE_PMID(kScriptInfoIDSpace, kBNBulletTextAfterPropertyScriptElement, kBNCorePrefix  + 215)
DECLARE_PMID(kScriptInfoIDSpace, kBNBulletCharStylePropertyScriptElement, kBNCorePrefix  + 216)
DECLARE_PMID(kScriptInfoIDSpace, kBNBulletAlignmentPropertyScriptElement, kBNCorePrefix  + 217)
DECLARE_PMID(kScriptInfoIDSpace, kBNListPropertyScriptElement, kBNCorePrefix  + 218)
DECLARE_PMID(kScriptInfoIDSpace, kBNLevelPropertyScriptElement, kBNCorePrefix  + 219)
DECLARE_PMID(kScriptInfoIDSpace, kBNFormatPropertyScriptElement, kBNCorePrefix  + 220)
DECLARE_PMID(kScriptInfoIDSpace, kBNNumberExpressionPropertyScriptElement, kBNCorePrefix  + 221)
DECLARE_PMID(kScriptInfoIDSpace, kBNNumberCharStylePropertyScriptElement, kBNCorePrefix  + 222)
DECLARE_PMID(kScriptInfoIDSpace, kBNContinueFromPreviousNumberPropertyScriptElement, kBNCorePrefix  + 223)
DECLARE_PMID(kScriptInfoIDSpace, kBNNumberingStartAtPropertyScriptElement, kBNCorePrefix  + 224)
DECLARE_PMID(kScriptInfoIDSpace, kBNApplyRestartPolicyPropertyScriptElement, kBNCorePrefix  + 225)
DECLARE_PMID(kScriptInfoIDSpace, kBNRestartPolicyObjectScriptElement, kBNCorePrefix  + 226)
DECLARE_PMID(kScriptInfoIDSpace, kBNRestartPolicyPropertyScriptElement, kBNCorePrefix  + 227)
DECLARE_PMID(kScriptInfoIDSpace, kBNRestartPolicyEnumPropertyScriptElement, kBNCorePrefix  + 228)
DECLARE_PMID(kScriptInfoIDSpace, kBNRestartPolicyLowerLevelPropertyScriptElement, kBNCorePrefix  + 229)
DECLARE_PMID(kScriptInfoIDSpace, kBNRestartPolicyUpperLevelPropertyScriptElement, kBNCorePrefix  + 230)
DECLARE_PMID(kScriptInfoIDSpace, kBNNumberAlignmentPropertyScriptElement, kBNCorePrefix  + 231)
DECLARE_PMID(kScriptInfoIDSpace, kBNListNamePropertyScriptElement, kBNCorePrefix  + 232)
DECLARE_PMID(kScriptInfoIDSpace, kBNListContinueNumbersAcrossStoriesPropertyScriptElement, kBNCorePrefix  + 233)
DECLARE_PMID(kScriptInfoIDSpace, kBNListCollectionObjectScriptElement, kBNCorePrefix  + 234)
DECLARE_PMID(kScriptInfoIDSpace, kBNChapterNumberSourceEnumScriptElement, kBNCorePrefix  + 235)
DECLARE_PMID(kScriptInfoIDSpace, kBNChapterNumPrefsObjectScriptElement, kBNCorePrefix  + 236)
DECLARE_PMID(kScriptInfoIDSpace, kBNChapterNumPrefsPropertyScriptElement, kBNCorePrefix  + 237)
DECLARE_PMID(kScriptInfoIDSpace, kBNChapterNumberPropertyScriptElement, kBNCorePrefix  + 238)
DECLARE_PMID(kScriptInfoIDSpace, kBNChapterNumberSourcePropertyScriptElement, kBNCorePrefix  + 239)
DECLARE_PMID(kScriptInfoIDSpace, kBNChapterNumFormatPropertyScriptElement, kBNCorePrefix  + 240)
//DECLARE_PMID(kScriptInfoIDSpace, kBNChapterNumEnabledPropertyScriptElement, kBNCorePrefix  + 241)
DECLARE_PMID(kScriptInfoIDSpace, kBNListContinueNumbersAcrossDocumentsPropertyScriptElement, kBNCorePrefix  + 242)
DECLARE_PMID(kScriptInfoIDSpace, kDeleteListMethodScriptElement, kBNCorePrefix  + 243)
DECLARE_PMID(kScriptInfoIDSpace, kBNBulletAndNumberingResultTextPropertyScriptElement, kBNCorePrefix  + 244)
DECLARE_PMID(kScriptInfoIDSpace, kBNNumberingResultNumberPropertyScriptElement, kBNCorePrefix  + 245)



//GUIDS
// {F35B78C0-5836-4869-B44D-3ED804D6FDD2}
#define kBNBulletCharacter_CLSID { 0xf35b78c0, 0x5836, 0x4869, { 0xb4, 0x4d, 0x3e, 0xd8, 0x4, 0xd6, 0xfd, 0xd2 } }
// {DFE17538-3FF6-46e2-A988-35FCA24D8A91}
#define kBNABulletCharacter_CLSID { 0xdfe17538, 0x3ff6, 0x46e2, { 0xa9, 0x88, 0x35, 0xfc, 0xa2, 0x4d, 0x8a, 0x91 } }
// {DE5B6B52-B48A-4c1b-A493-9A5E60E65C3B}
#define kBNBulletCharacters_CLSID { 0xde5b6b52, 0xb48a, 0x4c1b, { 0xa4, 0x93, 0x9a, 0x5e, 0x60, 0xe6, 0x5c, 0x3b } }
// {9292BE9C-759D-44c0-A8ED-C5D82C3AE8CC}
#define kBNRestartPolicy_CLSID { 0x9292be9c, 0x759d, 0x44c0, { 0xa8, 0xed, 0xc5, 0xd8, 0x2c, 0x3a, 0xe8, 0xcc } }
// {3419E800-6AA3-48c5-A9F4-6A39261D900D}
#define kBNList_CLSID { 0x3419e800, 0x6aa3, 0x48c5, { 0xa9, 0xf4, 0x6a, 0x39, 0x26, 0x1d, 0x90, 0xd } }
// {26A8AFD0-7863-4d09-941C-948795428592}
#define kBNLists_CLSID { 0x26a8afd0, 0x7863, 0x4d09, { 0x94, 0x1c, 0x94, 0x87, 0x95, 0x42, 0x85, 0x92 } }

//{F18E8E73-F8EC-4894-813C-ACD90C309AC9}
#define kBNChapterNumPref_CLSID { 0xf18e8e73, 0xf8ec, 0x4894, { 0x81, 0x3c, 0xac, 0xd9, 0xc, 0x30, 0x9a, 0xc9 } }

#endif // __BNCoreID__
