//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/FontMgrID.h $
//  
//  Owner: emenning
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

#ifndef __FontMgrID__
#define __FontMgrID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kFontMgrPrefix	 RezLong(0x3E00)

// <Start IDC>
// PluginID
#define kFontManagerPluginName 		"Font Manager"
DECLARE_PMID(kPlugInIDSpace, kFontManagerPluginID, kFontMgrPrefix + 1)

// Sherpa changes

// resource IDs
#define kFontMgrStringsRsrcID			1100
#define kFontMgrStringsNoTransRsrcID	1200
#define kFontMgrErrorStringTableRsrcID	1300

// <Class ID>
DECLARE_PMID(kClassIDSpace, kFontSystemUpdateTaskBoss, kFontMgrPrefix + 1)
// gap
DECLARE_PMID(kClassIDSpace, kFontGroupBoss, kFontMgrPrefix + 3)
// gap
// gap
DECLARE_PMID(kClassIDSpace, kFontConverterBoss, kFontMgrPrefix + 6)
DECLARE_PMID(kClassIDSpace, kMissingFontsOpenDocResponderBoss, kFontMgrPrefix + 7)
DECLARE_PMID(kClassIDSpace, kFontMgrErrorStringServiceBoss, kFontMgrPrefix + 8)
DECLARE_PMID(kClassIDSpace, kNewFontFamilyCommandBoss, kFontMgrPrefix + 9)
DECLARE_PMID(kClassIDSpace, kTypeKitConnectionStartupShutdownBoss, kFontMgrPrefix + 10)
DECLARE_PMID(kClassIDSpace, kRefreshMissingFontsCmdBoss, kFontMgrPrefix + 11)
// gap
DECLARE_PMID(kClassIDSpace, kFontMgrStartupShutdownBoss, kFontMgrPrefix + 13)
DECLARE_PMID(kClassIDSpace, kFontMgrConversionBoss, kFontMgrPrefix + 14)
DECLARE_PMID(kClassIDSpace, kFontMetricsTableBoss, kFontMgrPrefix + 15)
DECLARE_PMID(kClassIDSpace, kMissingFontSignalMgrBoss, kFontMgrPrefix + 16)
DECLARE_PMID(kClassIDSpace, kDefaultMissingFontResponderBoss, kFontMgrPrefix + 17)

DECLARE_PMID(kClassIDSpace, kFontTestMenuBoss, kFontMgrPrefix + 99)
DECLARE_PMID(kClassIDSpace, kDefaultPairKerningBoss, kFontMgrPrefix + 100)
DECLARE_PMID(kClassIDSpace, kRomanOnlyPairKerningBoss, kFontMgrPrefix + 101)

DECLARE_PMID(kClassIDSpace, kFontScriptProviderBoss, kFontMgrPrefix + 182)
DECLARE_PMID(kClassIDSpace, kFontScriptObjectBoss, kFontMgrPrefix + 183)
DECLARE_PMID(kClassIDSpace, kFontMgrPhase2ConversionBoss, kFontMgrPrefix + 184)
DECLARE_PMID(kClassIDSpace, kFontFamilyScriptProviderBoss, kFontMgrPrefix + 185)

DECLARE_PMID(kClassIDSpace, kFontFamilyStubBoss, kFontMgrPrefix + 188)
// gap: 189
DECLARE_PMID(kClassIDSpace, kTinIdleTaskBoss, kFontMgrPrefix + 190)
DECLARE_PMID(kClassIDSpace, kTinScriptProviderBoss, kFontMgrPrefix + 191)
DECLARE_PMID(kClassIDSpace, kCheckFontSeedChangeResponderBoss, kFontMgrPrefix + 192)
DECLARE_PMID(kClassIDSpace, kNetworkWatcherBoss, kFontMgrPrefix + 193)


// <Message ID>		// note - message ids conflict with class id space.
DECLARE_PMID(kMessageIDSpace, kUsedFontListMessage, kFontMgrPrefix + 201)
DECLARE_PMID(kMessageIDSpace, kFontSystemChangedMessage, kFontMgrPrefix + 202)
DECLARE_PMID(kMessageIDSpace, kTypekitErrorMessage, kFontMgrPrefix + 203)
DECLARE_PMID(kMessageIDSpace, kFindFontRequestUpdateMessage, kFontMgrPrefix + 204)
DECLARE_PMID(kMessageIDSpace, kSubscriptionRequestUpdateMessage, kFontMgrPrefix + 205)
DECLARE_PMID(kMessageIDSpace, kSyncFontRequestUpdateMessage, kFontMgrPrefix + 206)
DECLARE_PMID(kMessageIDSpace, kNetworkStatusChangedMessage, kFontMgrPrefix + 207)
DECLARE_PMID(kMessageIDSpace, kTypeQuestFontSystemChangedMessage, kFontMgrPrefix + 208)
DECLARE_PMID(kMessageIDSpace, kTypeQuestFontFamiliesChangedMessage, kFontMgrPrefix + 209)



// <Interface ID>
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTMGR, kFontMgrPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IUSEDFONTLIST, kFontMgrPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTFAMILY, kFontMgrPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCFONTMGR, kFontMgrPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTFAMILYDATA, kFontMgrPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_ITYPEKITCONNECTIONCACHE, kFontMgrPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTUSEWARNINGMANAGER, kFontMgrPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTTHREAD, kFontMgrPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_ITYPEKITLUTILS, kFontMgrPrefix + 9)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTMETRICSTABLE, kFontMgrPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTMETRICSTABLELIST, kFontMgrPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IMISSINGFONTSIGNALDATA, kFontMgrPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTLISTDATA, kFontMgrPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTFACENAME, kFontMgrPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRYAUTOACTIVATION, kFontMgrPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IOVERRIDEFONTFAMILY, kFontMgrPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTSYSTEMEVENTWATCHER, kFontMgrPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_ITINFONTS, kFontMgrPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTSET, kFontMgrPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_TINDOCUMENTDATA, kFontMgrPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_IPSNAMEDATA, kFontMgrPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_ITESTTINFONTS, kFontMgrPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTFAMILYTYPEKITINFO, kFontMgrPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_ITYPEKITIMSIDLETASK, kFontMgrPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTSYSTEMNETWORKOBSERVER, kFontMgrPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_INETWORKWATCHER, kFontMgrPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTFEATURE, kFontMgrPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_IFONTCLASSIFIER, kFontMgrPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_IDFONTSIMILARITY, kFontMgrPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_IADDEDFONTDIRS, kFontMgrPrefix + 31)

// <Implementation ID>
DECLARE_PMID(kImplementationIDSpace, kFontManagerImpl, kFontMgrPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kOpenDocFontObsImpl, kFontMgrPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kDocFontListImpl, kFontMgrPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kTypeKitUtilsImpl, kFontMgrPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kFontFamilyImpl, kFontMgrPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kDocFontManagerImpl, kFontMgrPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kFontMgrErrorStringServiceImpl, kFontMgrPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kFontRefConverterImpl, kFontMgrPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kFontSystemUpdateTaskImpl, kFontMgrPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kMissingFontsOpenDocResponderImpl, kFontMgrPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kFontMetricsTableListImpl, kFontMgrPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kNewFontFamilyCommandImpl, kFontMgrPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kFontFamilyDataImpl, kFontMgrPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kCheckFontSeedChangeResponderImpl, kFontMgrPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kTypeKitConnectionCacheImpl, kFontMgrPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kRefreshMissingFontsCmdImpl, kFontMgrPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kTypeKitConnectionStartupShutdownImpl, kFontMgrPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kFontMgrConversionImpl, kFontMgrPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kFontMetricsTableImpl, kFontMgrPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kMissingFontSignalDataImpl, kFontMgrPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kMissingFontSignalResponderImpl, kFontMgrPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kFontListDataImpl, kFontMgrPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kFontMgrPhase2ConversionImpl, kFontMgrPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kScriptFaceNameImpl, kFontMgrPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kFontSystemEventWatcherImpl, kFontMgrPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kPSNameImpl, kFontMgrPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kTypekitIMSIdleTaskImpl, kFontMgrPrefix + 27)
//gap
DECLARE_PMID(kImplementationIDSpace, kFontFamilyForwardImpl, kFontMgrPrefix + 30)
//gap
//DECLARE_PMID(kImplementationIDSpace, kPairKernExternalImpl, kFontMgrPrefix + 100)
//DECLARE_PMID(kImplementationIDSpace, kPKExternalServiceImpl, kFontMgrPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kDefaultPairKernServiceImpl, kFontMgrPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kPairKernDictImpl, kFontMgrPrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kFontUseWarningManagerImpl, kFontMgrPrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kFontMgrConversionProviderImpl, kFontMgrPrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kFontMgrStartupShutdownImpl, kFontMgrPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kRomanOnlyPairKernServiceImpl, kFontMgrPrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kRomanOnlyPairKernDictImpl, kFontMgrPrefix + 108)
//gap
DECLARE_PMID(kImplementationIDSpace, kFontScriptProviderImpl, kFontMgrPrefix + 222)
//gap
DECLARE_PMID(kImplementationIDSpace, kFontScriptImpl, kFontMgrPrefix + 224)
DECLARE_PMID(kImplementationIDSpace, kTinFontsImpl, kFontMgrPrefix + 225)
DECLARE_PMID(kImplementationIDSpace, kFontSetImpl, kFontMgrPrefix + 226)
// gap: 227
DECLARE_PMID(kImplementationIDSpace, kLocalFontManagerImpl, kFontMgrPrefix + 228)
DECLARE_PMID(kImplementationIDSpace, kTinGatherIdleTaskImpl, kFontMgrPrefix + 229)
DECLARE_PMID(kImplementationIDSpace, kTinDocumentDataImpl, kFontMgrPrefix + 230)
DECLARE_PMID(kImplementationIDSpace, kTinScriptProviderImpl, kFontMgrPrefix + 231)
DECLARE_PMID(kImplementationIDSpace, kFontFamilyScriptProviderImpl, kFontMgrPrefix + 232)
DECLARE_PMID(kImplementationIDSpace, kFontFamilyScriptImpl, kFontMgrPrefix + 233)
DECLARE_PMID(kImplementationIDSpace, kTestTinFontsImpl, kFontMgrPrefix + 234)
DECLARE_PMID(kImplementationIDSpace, kFontFamilyTypekitInfoImpl, kFontMgrPrefix + 235)
DECLARE_PMID(kImplementationIDSpace, kFontSystemNwStatusObserverImpl, kFontMgrPrefix + 236)
DECLARE_PMID(kImplementationIDSpace, kNetworkWatcherImpl, kFontMgrPrefix + 237)
DECLARE_PMID(kImplementationIDSpace, kFontFeatureCallerImpl, kFontMgrPrefix + 238)
DECLARE_PMID(kImplementationIDSpace, kFontClassifierCallerImpl, kFontMgrPrefix + 239)
DECLARE_PMID(kImplementationIDSpace, kDFontSimilarityCallerImpl, kFontMgrPrefix + 240)
DECLARE_PMID(kImplementationIDSpace, kAddedFontDirsImpl, kFontMgrPrefix + 241)

// <Widget ID>

// <Service ID>
DECLARE_PMID(kServiceIDSpace, kMissingFontSignalResponderService, kFontMgrPrefix + 1)


// Error ID
DECLARE_PMID(kErrorIDSpace, kFontStyleNotAvailableError,			kFontMgrPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kFontFamilyNotAvailableError,			kFontMgrPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kWorkspaceUnavailableError,				kFontMgrPrefix + 4)
DECLARE_PMID(kErrorIDSpace, kDatabaseUnavailableError,				kFontMgrPrefix + 5)
DECLARE_PMID(kErrorIDSpace, kCannotGetFontManager,					kFontMgrPrefix + 6)
DECLARE_PMID(kErrorIDSpace, kCantGetFontObjectError,				kFontMgrPrefix + 7)
DECLARE_PMID(kErrorIDSpace, kCorruptFeatureCode,					kFontMgrPrefix + 8)
DECLARE_PMID(kErrorIDSpace, kUnknownOpenTypeFeature,				kFontMgrPrefix + 9)
DECLARE_PMID(kErrorIDSpace, kCantGetFontProperty,					kFontMgrPrefix +10)
DECLARE_PMID(kErrorIDSpace, kCantGetUsedFontsList,					kFontMgrPrefix +11)
DECLARE_PMID(kErrorIDSpace, kCantGetGraphicsUsedFontsList,			kFontMgrPrefix +12)
DECLARE_PMID(kErrorIDSpace, kIndexBeyondEndOfFontList,				kFontMgrPrefix +13)
DECLARE_PMID(kErrorIDSpace, kCantGetFontsDocument,					kFontMgrPrefix +14)
DECLARE_PMID(kErrorIDSpace, kCantGetDocumentFontManager,			kFontMgrPrefix +15)
DECLARE_PMID(kErrorIDSpace, kCantGetFontUIDFromName,				kFontMgrPrefix +16)
DECLARE_PMID(kErrorIDSpace, kCantGetFontFromUID,					kFontMgrPrefix +17)
DECLARE_PMID(kErrorIDSpace, kCantGetMissingFontFromUID,				kFontMgrPrefix +18)
DECLARE_PMID(kErrorIDSpace, kUnableToIdentifyFont,					kFontMgrPrefix +19)
DECLARE_PMID(kErrorIDSpace, kCantGetFontFromGraphic,				kFontMgrPrefix +20)
DECLARE_PMID(kErrorIDSpace, kGeneralFontEnumerationFailure,			kFontMgrPrefix +21)
DECLARE_PMID(kErrorIDSpace, kAxisIndexOutOfRangeError,              kFontMgrPrefix +22)
DECLARE_PMID(kErrorIDSpace, kAxisValueOutOfRangeError,              kFontMgrPrefix +23)
DECLARE_PMID(kErrorIDSpace, kDesignAxesNotSupportedError,           kFontMgrPrefix +24)
DECLARE_PMID(kErrorIDSpace, kFontNotSpecifiedError,                 kFontMgrPrefix +25)

//
//Script Element IDs
//
//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kFontObjectScriptElement,						kFontMgrPrefix + 40)
DECLARE_PMID(kScriptInfoIDSpace, kTinObjectScriptElement,						kFontMgrPrefix + 41)
DECLARE_PMID(kScriptInfoIDSpace, kFontFamilyObjectScriptElement,				kFontMgrPrefix + 42)

//Events
DECLARE_PMID(kScriptInfoIDSpace, kCheckOpenTypeFeatureMethodScriptElement,		kFontMgrPrefix + 80)
DECLARE_PMID(kScriptInfoIDSpace, kUpdateFontsMethodScriptElement,				kFontMgrPrefix + 81)
DECLARE_PMID(kScriptInfoIDSpace, kSubsetFontMethodScriptElement,				kFontMgrPrefix + 82)
DECLARE_PMID(kScriptInfoIDSpace, kAddFontDirectoryMethodScriptElement,          kFontMgrPrefix + 83)
DECLARE_PMID(kScriptInfoIDSpace, kRemoveFontDirectoryMethodScriptElement,       kFontMgrPrefix + 84)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kAllowEmbeddingPropertyScriptElement,			kFontMgrPrefix + 140)
DECLARE_PMID(kScriptInfoIDSpace, kAllowOutlinesPropertyScriptElement,			kFontMgrPrefix + 141)
DECLARE_PMID(kScriptInfoIDSpace, kAllowPDFEmbeddingPropertyScriptElement,		kFontMgrPrefix + 142)
DECLARE_PMID(kScriptInfoIDSpace, kAllowPrintingPropertyScriptElement,			kFontMgrPrefix + 143)
DECLARE_PMID(kScriptInfoIDSpace, kFamilyPropertyScriptElement,					kFontMgrPrefix + 144)
DECLARE_PMID(kScriptInfoIDSpace, kLocationPropertyScriptElement,				kFontMgrPrefix + 145)
DECLARE_PMID(kScriptInfoIDSpace, kTinPropertyScriptElement,						kFontMgrPrefix + 146)
DECLARE_PMID(kScriptInfoIDSpace, kPostScriptNamePropertyScriptElement,			kFontMgrPrefix + 147)
DECLARE_PMID(kScriptInfoIDSpace, kRestrictedPrintingPropertyScriptElement,		kFontMgrPrefix + 148)
DECLARE_PMID(kScriptInfoIDSpace, kFontStatusPropertyScriptElement ,				kFontMgrPrefix + 149)
DECLARE_PMID(kScriptInfoIDSpace, kStylePropertyScriptElement, 					kFontMgrPrefix + 150)
DECLARE_PMID(kScriptInfoIDSpace, kFontTypePropertyScriptElement, 				kFontMgrPrefix + 151)
DECLARE_PMID(kScriptInfoIDSpace, kTinSINGGlyphletBlobElement,					kFontMgrPrefix + 152)
DECLARE_PMID(kScriptInfoIDSpace, kWritingScriptScriptElement,					kFontMgrPrefix + 153)
DECLARE_PMID(kScriptInfoIDSpace, kFontPlatformNamePropertyScriptElement,		kFontMgrPrefix + 154)
DECLARE_PMID(kScriptInfoIDSpace, kFontFullNamePropertyScriptElement,			kFontMgrPrefix + 155)
DECLARE_PMID(kScriptInfoIDSpace, kFontFullNameNativeNamePropertyScriptElement,	kFontMgrPrefix + 156)
DECLARE_PMID(kScriptInfoIDSpace, kFontStyleNameNativeNamePropertyScriptElement,	kFontMgrPrefix + 157)
DECLARE_PMID(kScriptInfoIDSpace, kFontVersionPropertyScriptElement,				kFontMgrPrefix + 158)
DECLARE_PMID(kScriptInfoIDSpace, kRegistryPropertyScriptElement,				kFontMgrPrefix + 159)
DECLARE_PMID(kScriptInfoIDSpace, kOrderingPropertyScriptElement,				kFontMgrPrefix + 160)
DECLARE_PMID(kScriptInfoIDSpace, kTinSINGGlyphletReferenceMaps,					kFontMgrPrefix + 161)
DECLARE_PMID(kScriptInfoIDSpace, kFontNumDesignAxesScriptElement,               kFontMgrPrefix + 162)
DECLARE_PMID(kScriptInfoIDSpace, kFontDesignAxesNameScriptElement,              kFontMgrPrefix + 163)
DECLARE_PMID(kScriptInfoIDSpace, kFontDesignAxesRangeScriptElement,             kFontMgrPrefix + 164)
DECLARE_PMID(kScriptInfoIDSpace, kFontDesignAxesValueScriptElement,             kFontMgrPrefix + 165)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kFontStatusEnumScriptElement,					kFontMgrPrefix + 220)
DECLARE_PMID(kScriptInfoIDSpace, kFontTypeEnumScriptElement,					kFontMgrPrefix + 221)
DECLARE_PMID(kScriptInfoIDSpace, kOTFeatureEnumScriptElement,					kFontMgrPrefix + 222)

//Metadata
DECLARE_PMID(kScriptInfoIDSpace, kTinObjectINXPolicies40MetadataScriptElement,	kFontMgrPrefix + 240)
DECLARE_PMID(kScriptInfoIDSpace, kTinObjectINXPolicies70MetadataScriptElement,	kFontMgrPrefix + 241)
DECLARE_PMID(kScriptInfoIDSpace, kFontTKDScriptElement,	kFontMgrPrefix + 242)
//GUIDS
// {758A3D29-A294-4e59-AFE8-05F8F4E0F130}
#define kFont_CLSID { 0x758a3d29, 0xa294, 0x4e59, { 0xaf, 0xe8, 0x5, 0xf8, 0xf4, 0xe0, 0xf1, 0x30 } }
// {BA73BD7C-6CC7-47a4-915A-D711875752B9}
#define kFonts_CLSID { 0xba73bd7c, 0x6cc7, 0x47a4, { 0x91, 0x5a, 0xd7, 0x11, 0x87, 0x57, 0x52, 0xb9 } }
// {FEF820E3-3CCB-4bbe-93EF-D99E0072A413}
#define kTinDocument_CLSID { 0xfef820e3, 0x3ccb, 0x4bbe, { 0x93, 0xef, 0xd9, 0x9e, 0x0, 0x72, 0xa4, 0x13 } }
// {36FAEEBB-B171-4439-B31A-1AF387F3C1CC}
#define kFontFamily_CLSID { 0x36faeebb, 0xb171, 0x4439, { 0xb3, 0x1a, 0x1a, 0xf3, 0x87, 0xf3, 0xc1, 0xcc } }
// {E60A33FF-F538-40b1-8EAC-D246E839F7F6}
#define kFontFamilies_CLSID { 0xe60a33ff, 0xf538, 0x40b1, { 0x8e, 0xac, 0xd2, 0x46, 0xe8, 0x39, 0xf7, 0xf6 } }


#endif		// __FontMgrID__
