//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/LinguisticID.h $
//  
//  Owner: Eric Menninga
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

#ifndef __LinguisticID__
#define __LinguisticID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"
//#include "FormatNumber.h"


// StringTable IDs
// String resource id
#define kLinguisticStringsRsrcID	 		500
#define kLinguisticStringsNoTransRsrcID	600
#define kLinguisticsErrorStringTableRsrcID	700

// kLinguisticConfig indices
#define kLinguisticDefaultProviderName		"LILO"

#define kLinguisticPrefix	 RezLong(0x2D00) // = 11520

// Conversion
// For pub conversion constants see LinguisticConversionID.h

// <Start IDC>
// PluginID
#define kLinguisticPluginName 						"Linguistics"
DECLARE_PMID(kPlugInIDSpace, kLinguisticPluginID, kLinguisticPrefix + 1)

#define kDefaultUserDictFileName 					"UserDict.udc"

// <Service ID>
// Service ids
DECLARE_PMID(kServiceIDSpace, kLinguisticManagerService, kLinguisticPrefix + 1)
DECLARE_PMID(kServiceIDSpace, kLinguisticService, kLinguisticPrefix + 2)

// <Class ID>
// class ids
DECLARE_PMID(kClassIDSpace, kLinguisticManagerBoss, kLinguisticPrefix + 1)
//gap
DECLARE_PMID(kClassIDSpace, kSimpleLinguisticBoss, kLinguisticPrefix + 3)
DECLARE_PMID(kClassIDSpace, kLinguisticsErrorStringServiceBoss, kLinguisticPrefix + 4)
DECLARE_PMID(kClassIDSpace, kSimpleHyphenationBoss, kLinguisticPrefix + 5)
DECLARE_PMID(kClassIDSpace, kSimpleUserDictBoss, kLinguisticPrefix + 6)
DECLARE_PMID(kClassIDSpace, kLanguageBoss, kLinguisticPrefix + 7)
DECLARE_PMID(kClassIDSpace, kNewLanguageCmdBoss, kLinguisticPrefix + 8)
DECLARE_PMID(kClassIDSpace, kDeleteLanguageCmdBoss, kLinguisticPrefix + 9)
DECLARE_PMID(kClassIDSpace, kLanguageRefConverterBoss, kLinguisticPrefix + 10)

DECLARE_PMID(kClassIDSpace, kInstallLanguagesCmdBoss, kLinguisticPrefix + 11)
DECLARE_PMID(kClassIDSpace, kLanguageWithVendorsBoss, kLinguisticPrefix + 12	/* contains a IID_LANGUAGE and a PersistUIDList with the vendor. */)
DECLARE_PMID(kClassIDSpace, kNewLanguageWithVendorsCmdBoss, kLinguisticPrefix + 13	/* only used internaly */)
DECLARE_PMID(kClassIDSpace, kSetDefaultVendorCmdBoss, kLinguisticPrefix + 14	/* only used internaly */)
DECLARE_PMID(kClassIDSpace, kLanguageWithVendorsRefConverterBoss, kLinguisticPrefix + 15)
DECLARE_PMID(kClassIDSpace, kHyphenateStoryCmdBoss, kLinguisticPrefix + 16	/* DEBUG, LinguisticPlugin.cpp */)
DECLARE_PMID(kClassIDSpace, kSpellCheckStoryCmdBoss, kLinguisticPrefix + 17	/* DEBUG, LinguisticPlugin.cpp */)
//DECLARE_PMID(kClassIDSpace, kInsertHyphExceptionsCmdBoss, kLinguisticPrefix + 18)
//DECLARE_PMID(kClassIDSpace, kScriptTextPreProcessorBoss, kLinguisticPrefix + 19)
//DECLARE_PMID(kClassIDSpace, kScriptTextPostProcessorBoss, kLinguisticPrefix + 20)
DECLARE_PMID(kClassIDSpace, kScriptUserEditCmdResponderBoss, kLinguisticPrefix + 21)
DECLARE_PMID(kClassIDSpace, kSetTypographersQuotesCmdBoss, kLinguisticPrefix + 22)
DECLARE_PMID(kClassIDSpace, kLinguisticIteratorRegBoss, kLinguisticPrefix + 23)
DECLARE_PMID(kClassIDSpace, kLinguisticConversionProviderBoss, kLinguisticPrefix + 24)
DECLARE_PMID(kClassIDSpace, kLanguageScriptProviderBoss, kLinguisticPrefix + 25)

DECLARE_PMID(kClassIDSpace, kSetVendorPathListCmdBoss, kLinguisticPrefix + 30)
//DECLARE_PMID(kClassIDSpace, kAppendVendorPathCmdBoss, kLinguisticPrefix + 31)
//DECLARE_PMID(kClassIDSpace, kRemoveVendorPathCmdBoss, kLinguisticPrefix + 32)




//gap
//DECLARE_PMID(kClassIDSpace, kSpellingMementoBoss, kLinguisticPrefix + 32)
DECLARE_PMID(kClassIDSpace, kVOSSpellingObjectBoss, kLinguisticPrefix + 33)
DECLARE_PMID(kClassIDSpace, kSpellingStrandBoss, kLinguisticPrefix + 34)
DECLARE_PMID(kClassIDSpace, kSpellingStrandDiskPageBoss, kLinguisticPrefix + 35)
DECLARE_PMID(kClassIDSpace, kSpellingStrandPastePieceBoss, kLinguisticPrefix + 36)
DECLARE_PMID(kClassIDSpace, kSpellingPhase2ConversionBoss, kLinguisticPrefix + 37)
DECLARE_PMID(kClassIDSpace, kSpellingStrandReplacePieceBoss, kLinguisticPrefix + 38)

DECLARE_PMID(kClassIDSpace, kBackgroundSpellCheckIdleTaskBoss, kLinguisticPrefix + 40)
DECLARE_PMID(kClassIDSpace, kBackgroundSpellCheckStartupShutdownBoss, kLinguisticPrefix + 41)
DECLARE_PMID(kClassIDSpace, kBackgroundSpellCheckCloseDocResponderBoss, kLinguisticPrefix + 42)
DECLARE_PMID(kClassIDSpace, kBackgroundSpellCheckNewStoryResponderBoss, kLinguisticPrefix + 43)
DECLARE_PMID(kClassIDSpace, kBackgroundSpellCheckDeleteStoryResponderBoss, kLinguisticPrefix + 44)
DECLARE_PMID(kClassIDSpace, kBackgroundSpellCheckOpenDocResponderBoss, kLinguisticPrefix + 45)

DECLARE_PMID(kClassIDSpace, kStrandOfBSCObjectsDiskPageBoss, kLinguisticPrefix + 60)

DECLARE_PMID(kClassIDSpace, kAttachStrandToStorySpellingEditBoss, kLinguisticPrefix + 81)
DECLARE_PMID(kClassIDSpace, kDetachStrandFromStorySpellingEditBoss, kLinguisticPrefix + 82)
DECLARE_PMID(kClassIDSpace, kMarkChangeDamageSpellingEditBoss, kLinguisticPrefix + 83)
DECLARE_PMID(kClassIDSpace, kMarkDeleteDamageSpellingEditBoss, kLinguisticPrefix + 84)
DECLARE_PMID(kClassIDSpace, kMarkInsertDamageSpellingEditBoss, kLinguisticPrefix + 85)
DECLARE_PMID(kClassIDSpace, kMarkPasteDamageSpellingEditBoss, kLinguisticPrefix + 86)
DECLARE_PMID(kClassIDSpace, kMarkPostReplaceDamageSpellingEditBoss, kLinguisticPrefix + 87)
DECLARE_PMID(kClassIDSpace, kMarkPreReplaceDamageSpellingEditBoss, kLinguisticPrefix + 88)
DECLARE_PMID(kClassIDSpace, kMarkRegenDamageSpellingEditBoss, kLinguisticPrefix + 89)
DECLARE_PMID(kClassIDSpace, kUndoSpellingRemoveFromDocCmdBoss, kLinguisticPrefix + 90)
DECLARE_PMID(kClassIDSpace, kCreateStoryThreadsSpellingEditBoss, kLinguisticPrefix + 91)
DECLARE_PMID(kClassIDSpace, kInsertStoryThreadSpellingEditBoss, kLinguisticPrefix + 92)
DECLARE_PMID(kClassIDSpace, kJoinStoryThreadsSpellingEditBoss, kLinguisticPrefix + 93)
DECLARE_PMID(kClassIDSpace, kSetDataStateSpellingEditBoss, kLinguisticPrefix + 94)

DECLARE_PMID(kClassIDSpace, kSetSpellingDataStateCmdBoss, kLinguisticPrefix + 100)
DECLARE_PMID(kClassIDSpace, kBackgroundSpellCheckNewDocResponderBoss, kLinguisticPrefix + 101)

DECLARE_PMID(kClassIDSpace, kSetUseNativeDigitsCmdBoss, kLinguisticPrefix + 102)


DECLARE_PMID(kClassIDSpace, kSetVendorPathListCmdImpl, kLinguisticPrefix + 110)
DECLARE_PMID(kClassIDSpace, kAppendVendorPathCmdImpl, kLinguisticPrefix + 111)
DECLARE_PMID(kClassIDSpace, kRemoveVendorPathCmdImpl, kLinguisticPrefix + 112)

DECLARE_PMID(kClassIDSpace, kBootStrapSpellTaskImpl, kLinguisticPrefix + 113)

DECLARE_PMID(kClassIDSpace, kSetDefaultSpellingCmdBoss, kLinguisticPrefix + 120)
DECLARE_PMID(kClassIDSpace, kSetDefaultHyphenationCmdBoss, kLinguisticPrefix + 121)

DECLARE_PMID(kClassIDSpace, kMissingServiceOpenDocResponderBoss, kLinguisticPrefix + 130)
DECLARE_PMID(kClassIDSpace, kLanguageNewWSResponderBoss, kLinguisticPrefix + 131)
DECLARE_PMID(kClassIDSpace, kLinguisticStartupShutdownBoss, kLinguisticPrefix + 132)


// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_ILINGUISTICMGR, kLinguisticPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINGUISTICDATA, kLinguisticPrefix + 2)

DECLARE_PMID(kInterfaceIDSpace, IID_IHYPHENATIONMGR, kLinguisticPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IHYPHENATIONSERVICE, kLinguisticPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_ISPELLINGMGR, kLinguisticPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_ISPELLINGSERVICE, kLinguisticPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IPHONETICMGR, kLinguisticPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IPHONETICSERVICE, kLinguisticPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IUSERDICTMGR, kLinguisticPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IUSERDICTSERVICE, kLinguisticPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IUSERDICTITERATOR, kLinguisticPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_ILANGUAGE, kLinguisticPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_ILANGUAGELIST, kLinguisticPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IVENDORLIST, kLinguisticPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IHYPHVENDORLIST, kLinguisticPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_ISPELLVENDORLIST, kLinguisticPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IINSTALLEDBOOLDATA, kLinguisticPrefix + 17	/* IBoolData using ISession::GetStartupTime() */)
DECLARE_PMID(kInterfaceIDSpace, IID_IVENDORCMDDATA, kLinguisticPrefix + 18	)
DECLARE_PMID(kInterfaceIDSpace, IID_IINSERTHYPHEXCEPTIONSCMDDATA, kLinguisticPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTPREFS, kLinguisticPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_IUSERDICT, kLinguisticPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_IQUOTETABLE, kLinguisticPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_IQUOTEDATA, kLinguisticPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_IQUOTES, kLinguisticPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTLOCKINGDATA, kLinguisticPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_ITHESAURUSMGR, kLinguisticPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_ITHESAURUSSERVICE, kLinguisticPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_ITHESAURUSVENDORLIST, kLinguisticPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_IDICTIONARYUTILS, kLinguisticPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_ISPELLINGUTILS, kLinguisticPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_ISPELLINGDATASTRAND, kLinguisticPrefix + 31)

DECLARE_PMID(kInterfaceIDSpace, IID_IBACKGROUNDSPELLINGRANGEDATA, kLinguisticPrefix + 40)
DECLARE_PMID(kInterfaceIDSpace, IID_IBACKGROUNDSPELLINGIDLETASK, kLinguisticPrefix + 41)
DECLARE_PMID(kInterfaceIDSpace, IID_IBACKGROUNDSPELLINGKILLIDLETHREADFLAG, kLinguisticPrefix + 42)
DECLARE_PMID(kInterfaceIDSpace, IID_IBACKGROUNDSPELLCHECKTEXTMODELLIST, kLinguisticPrefix + 44)

DECLARE_PMID(kInterfaceIDSpace, IID_ISPELLINGSTATECMDDATA, kLinguisticPrefix + 50)
DECLARE_PMID(kInterfaceIDSpace, IID_IBOOTSTRAPIDLETASK, kLinguisticPrefix + 52)

DECLARE_PMID(kInterfaceIDSpace, IID_IDIGITINPUTPREFS, kLinguisticPrefix + 60)

// <Implementation ID>
// ImplementationIDs

DECLARE_PMID(kImplementationIDSpace, kLinguisticMgrImpl, kLinguisticPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kLinguisticMgrServiceImpl, kLinguisticPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kLinguisticServiceDataImpl, kLinguisticPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kLinguisticServiceProviderImpl, kLinguisticPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kLinguisticStartupShutdownImpl, kLinguisticPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kLinguisticsErrorStringServiceImpl, kLinguisticPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kLinguisticLowMemoryImpl, kLinguisticPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kSimpleHyphenationMgrImpl, kLinguisticPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kSimpleSpellingMgrImpl, kLinguisticPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kSimplePhoneticMgrImpl, kLinguisticPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kSimpleUserDictMgrImpl, kLinguisticPrefix + 11)
//gap
DECLARE_PMID(kImplementationIDSpace, kSimpleHyphenationImpl, kLinguisticPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kSimpleUserDictImpl, kLinguisticPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kLanguageImpl, kLinguisticPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kLanguageListImpl, kLinguisticPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kNewLanguageCmdImpl, kLinguisticPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kDeleteLanguageCmdImpl, kLinguisticPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kLanguageRefConverterImpl, kLinguisticPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kInstallLanguagesCmdImpl, kLinguisticPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kHyphenationVendorListImpl, kLinguisticPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kSpellingVendorListImpl, kLinguisticPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kInstalledBoolDataImpl, kLinguisticPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kNewLanguageWithVendorsCmdImpl, kLinguisticPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kSetDefaultVendorCmdImpl, kLinguisticPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kSetVendorCmdDataImpl, kLinguisticPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kLanguageWithVendorsRefConverterImpl, kLinguisticPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kHyphenateStoryCmdImpl, kLinguisticPrefix + 28	/* DEBUG, LinguisticPlugin.cpp */)
DECLARE_PMID(kImplementationIDSpace, kHyphenateStoryWalkerImpl, kLinguisticPrefix + 29	/* DEBUG, LinguisticPlugin.cpp */)
DECLARE_PMID(kImplementationIDSpace, kSpellCheckStoryCmdImpl, kLinguisticPrefix + 30	/* DEBUG, LinguisticPlugin.cpp */)
DECLARE_PMID(kImplementationIDSpace, kSpellCheckStoryWalkerImpl, kLinguisticPrefix + 31	/* DEBUG, LinguisticPlugin.cpp */)

//DECLARE_PMID(kImplementationIDSpace, kInsertHyphExceptionsCmdImpl, kLinguisticPrefix + 32)
//DECLARE_PMID(kImplementationIDSpace, kInsertHyphExceptionsCmdDataImpl, kLinguisticPrefix + 33)
//DECLARE_PMID(kImplementationIDSpace, kHyphExceptionsWalkerImpl, kLinguisticPrefix + 34)

DECLARE_PMID(kImplementationIDSpace, kScriptPrefsImpl, kLinguisticPrefix + 35)
//DECLARE_PMID(kImplementationIDSpace, kScriptTextPreProcessorImpl, kLinguisticPrefix + 36)
//DECLARE_PMID(kImplementationIDSpace, kScriptTextPostProcessorImpl, kLinguisticPrefix + 37)

DECLARE_PMID(kImplementationIDSpace, kQuotesImpl, kLinguisticPrefix + 38)
// Conflicting implementation from Hotaka merge %brycem%
DECLARE_PMID(kImplementationIDSpace, kFontLockingDataImpl, kLinguisticPrefix + 39)
//DECLARE_PMID(kImplementationIDSpace, kQuoteTableImpl, kLinguisticPrefix + 39) moved to 43 15/Dec/00 %brycem%
DECLARE_PMID(kImplementationIDSpace, kQuoteDataImpl, kLinguisticPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kSetTypographersQuotesCmdImpl, kLinguisticPrefix + 41)

DECLARE_PMID(kImplementationIDSpace, kScriptUserEditCmdRespImpl, kLinguisticPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kQuoteTableImpl, kLinguisticPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kThesaurusVendorListImpl, kLinguisticPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kLinguisticIteratorRegImpl, kLinguisticPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kDictionaryUtilsImpl, kLinguisticPrefix + 46)

DECLARE_PMID(kImplementationIDSpace, kLanguageScriptProviderImpl, kLinguisticPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kLanguageScriptImpl, kLinguisticPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kVendorLanguageScriptImpl, kLinguisticPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kSpellingUtilsImpl, kLinguisticPrefix + 50)

DECLARE_PMID(kImplementationIDSpace, kSpellingStrandImpl, kLinguisticPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kSpellingDataStrandImpl, kLinguisticPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kSpellingStrandPastePieceImpl, kLinguisticPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kSpellingMementoImpl, kLinguisticPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kSpellingAttrStrandImpl, kLinguisticPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kSpellingPhase2ConversionImpl, kLinguisticPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kSpellingStrandReplacePieceImpl, kLinguisticPrefix + 67)

DECLARE_PMID(kImplementationIDSpace, kBackgroundSpellCheckIdleTaskImpl, kLinguisticPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kBackgroundSpellCheckStartupShutdownImpl, kLinguisticPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kBackgroundSpellCheckCloseDocResponderImpl, kLinguisticPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kBackgroundSpellCheckNewStoryResponderImpl, kLinguisticPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kBackgroundSpellCheckDeleteStoryResponderImpl, kLinguisticPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kBackgroundSpellCheckModelObserverImpl, kLinguisticPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kBackgroundSpellCheckOpenDocResponderImpl, kLinguisticPrefix + 76)

DECLARE_PMID(kImplementationIDSpace, kAttachStrandToStorySpellingEditImpl, kLinguisticPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kDetachStrandFromStorySpellingEditImpl, kLinguisticPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kMarkChangeDamageSpellingEditImpl, kLinguisticPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kMarkDeleteDamageSpellingEditImpl, kLinguisticPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kMarkInsertDamageSpellingEditImpl, kLinguisticPrefix + 85)
DECLARE_PMID(kImplementationIDSpace, kMarkPasteDamageSpellingEditImpl, kLinguisticPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kMarkPostReplaceDamageSpellingEditImpl, kLinguisticPrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kMarkPreReplaceDamageSpellingEditImpl, kLinguisticPrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kMarkRegenDamageSpellingEditImpl, kLinguisticPrefix + 89)
DECLARE_PMID(kImplementationIDSpace, kUndoSpellingRemoveFromDocCmdImpl, kLinguisticPrefix + 90)
DECLARE_PMID(kImplementationIDSpace, kCreateStoryThreadsSpellingEditImpl, kLinguisticPrefix + 91)
DECLARE_PMID(kImplementationIDSpace, kInsertStoryThreadSpellingEditImpl, kLinguisticPrefix + 92)
DECLARE_PMID(kImplementationIDSpace, kJoinStoryThreadsSpellingEditImpl, kLinguisticPrefix + 93)
DECLARE_PMID(kImplementationIDSpace, kSetDataStateSpellingEditImpl, kLinguisticPrefix + 94)

DECLARE_PMID(kImplementationIDSpace, kSetSpellingDataStateCmdImpl, kLinguisticPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kSpellingStateCmdDataImpl, kLinguisticPrefix + 101)

DECLARE_PMID(kImplementationIDSpace, kSetDefaultSpellingCmdImpl, kLinguisticPrefix + 120)
DECLARE_PMID(kImplementationIDSpace, kSetDefaultHyphenationCmdImpl, kLinguisticPrefix + 121)

DECLARE_PMID(kImplementationIDSpace, kMissingServiceOpenDocResponderImpl, kLinguisticPrefix + 130)
DECLARE_PMID(kImplementationIDSpace, kLanguageNewWSResponderImpl, kLinguisticPrefix + 131)

DECLARE_PMID(kImplementationIDSpace, kDigitInputBoolDataImpl, kLinguisticPrefix + 140)
DECLARE_PMID(kImplementationIDSpace, kSetUseNativeDigitsCmdImpl, kLinguisticPrefix + 141)


//Errors
DECLARE_PMID(kErrorIDSpace, kUnknownVendorError,	 kLinguisticPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kBadQuoteStringError,	 kLinguisticPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kAddDictionaryPathError,	 kLinguisticPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kRemoveDictionaryPathError,	 kLinguisticPrefix + 4)

//
//Script Element IDs
//

//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kLanguageObjectScriptElement,				kLinguisticPrefix + 10)
DECLARE_PMID(kScriptInfoIDSpace, kVendorLanguageObjectScriptElement,		kLinguisticPrefix + 11)

//Events
DECLARE_PMID(kScriptInfoIDSpace, kAddDictionaryPathMethodScriptElement,		kLinguisticPrefix + 20)
DECLARE_PMID(kScriptInfoIDSpace, kRemoveDictionaryPathMethodScriptElement,	kLinguisticPrefix+ 21)
//DECLARE_PMID(kScriptInfoIDSpace, kNewDictionaryPathMethodScriptElement,		kLinguisticPrefix+ 22)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kHyphenationVendorPropertyScriptElement,	kLinguisticPrefix + 30)
DECLARE_PMID(kScriptInfoIDSpace, kSpellingVendorPropertyScriptElement,		kLinguisticPrefix + 31)
DECLARE_PMID(kScriptInfoIDSpace, kThesaurusVendorPropertyScriptElement,		kLinguisticPrefix + 32)
//gap
DECLARE_PMID(kScriptInfoIDSpace, kDoubleQuotesPropertyScriptElement,		kLinguisticPrefix + 35)
DECLARE_PMID(kScriptInfoIDSpace, kSingleQuotesPropertyScriptElement,		kLinguisticPrefix + 36)
DECLARE_PMID(kScriptInfoIDSpace, kPrimaryLanguageNamePropertyScriptElement,	kLinguisticPrefix + 37)
DECLARE_PMID(kScriptInfoIDSpace, kSubLanguageNamePropertyScriptElement,		kLinguisticPrefix + 38)
DECLARE_PMID(kScriptInfoIDSpace, kDictPathsPropertyScriptElement,			kLinguisticPrefix + 39)

DECLARE_PMID(kScriptInfoIDSpace, kHyphenationVendorListPropertyScriptElement,	kLinguisticPrefix + 40)
DECLARE_PMID(kScriptInfoIDSpace, kSpellingVendorListPropertyScriptElement,		kLinguisticPrefix + 41)
DECLARE_PMID(kScriptInfoIDSpace, kThesaurusVendorListPropertyScriptElement,		kLinguisticPrefix + 42)

DECLARE_PMID(kScriptInfoIDSpace, kICULocaleNamePropertyScriptElement,		kLinguisticPrefix + 43)

DECLARE_PMID(kScriptInfoIDSpace, kUntranslatedNamePropertyScriptElement,		kLinguisticPrefix + 44)


//GUIDS
// {EE964067-06C6-11d2-AAC9-00C04FA349C7}
#define kLanguage_CLSID { 0xee964067, 0x6c6, 0x11d2, { 0xaa, 0xc9, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {496F0BDF-7834-11d2-AAF0-00C04FA37726}
#define kLanguages_CLSID { 0x496f0bdf, 0x7834, 0x11d2, { 0xaa, 0xf0, 0x0, 0xc0, 0x4f, 0xa3, 0x77, 0x26 } }
// {93440FEF-D0AE-4464-9081-002804DD8C49}
#define kVendorLanguage_CLSID { 0x93440fef, 0xd0ae, 0x4464, { 0x90, 0x81, 0x0, 0x28, 0x4, 0xdd, 0x8c, 0x49 } }
// {D82396B6-0E61-4e10-B9B9-5A881A7AAF82}
#define kVendorLanguages_CLSID { 0xd82396b6, 0xe61, 0x4e10, { 0xb9, 0xb9, 0x5a, 0x88, 0x1a, 0x7a, 0xaf, 0x82 } }


#endif
