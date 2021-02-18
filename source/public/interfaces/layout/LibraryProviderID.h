//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/LibraryProviderID.h $
//  
//  Owner: Hardeep
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

#ifndef __LibraryProviderID__
#define __LibraryProviderID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kLibraryProviderPrefix	 			RezLong(0x9800)

// Plugin ID
#define kLibraryProviderPluginName 			"Asset PubLibrary"
DECLARE_PMID(kPlugInIDSpace, kLibraryProviderPluginID, kLibraryProviderPrefix + 1)

// Conversion
// For pub conversion constants see LibraryProviderConversionID.h


// <Class ID>

DECLARE_PMID(kClassIDSpace, kLibraryProviderBoss				,kLibraryProviderPrefix + 1)
//gap
DECLARE_PMID(kClassIDSpace, kLibraryBoss						,kLibraryProviderPrefix + 3)
DECLARE_PMID(kClassIDSpace, kLibraryAssetBoss					,kLibraryProviderPrefix + 4)
DECLARE_PMID(kClassIDSpace,	kLibraryScrapControllerBoss			,kLibraryProviderPrefix + 5)
DECLARE_PMID(kClassIDSpace, kLibraryScrapHandlerBoss			,kLibraryProviderPrefix + 6)
DECLARE_PMID(kClassIDSpace, kLibraryScriptObserverBoss			,kLibraryProviderPrefix + 7)
//gap
DECLARE_PMID(kClassIDSpace, kLibrarySimpleFilterBoss			,kLibraryProviderPrefix + 9)
DECLARE_PMID(kClassIDSpace, kLibraryComplexFilterBoss			,kLibraryProviderPrefix + 10)
//gap
DECLARE_PMID(kClassIDSpace, kLibraryAddItemCmdBoss				,kLibraryProviderPrefix + 21)
DECLARE_PMID(kClassIDSpace, kLibraryCopyItemsCmdBoss			,kLibraryProviderPrefix + 22)
DECLARE_PMID(kClassIDSpace, kLibraryAddPageCmdBoss				,kLibraryProviderPrefix + 23)
DECLARE_PMID(kClassIDSpace, kLibraryDeleteItemsCmdBoss			,kLibraryProviderPrefix + 24)
DECLARE_PMID(kClassIDSpace, kLibraryNewLibCmdBoss				,kLibraryProviderPrefix + 25)
DECLARE_PMID(kClassIDSpace, kLibraryOpenLibCmdBoss				,kLibraryProviderPrefix + 26)
DECLARE_PMID(kClassIDSpace, kLibraryCloseLibCmdBoss				,kLibraryProviderPrefix + 27)
DECLARE_PMID(kClassIDSpace, kLibraryMemStreamReadBoss			,kLibraryProviderPrefix + 29)
//gap
DECLARE_PMID(kClassIDSpace, kPMStringPropertyDataBoss			,kLibraryProviderPrefix + 40)
DECLARE_PMID(kClassIDSpace, kDateTimePropertyDataBoss			,kLibraryProviderPrefix + 41)
DECLARE_PMID(kClassIDSpace, kIntPropertyDataBoss				,kLibraryProviderPrefix + 42)
DECLARE_PMID(kClassIDSpace, kPointPropertyDataBoss				,kLibraryProviderPrefix + 43)
DECLARE_PMID(kClassIDSpace, kThumbnailPropertyDataBoss			,kLibraryProviderPrefix + 44)
DECLARE_PMID(kClassIDSpace, kStringPropTabBoss					,kLibraryProviderPrefix + 45)
DECLARE_PMID(kClassIDSpace, kDateTimePropTabBoss				,kLibraryProviderPrefix + 46)
DECLARE_PMID(kClassIDSpace, kIntPropTabBoss						,kLibraryProviderPrefix + 47)
DECLARE_PMID(kClassIDSpace, kPointPropTabBoss					,kLibraryProviderPrefix + 48)
DECLARE_PMID(kClassIDSpace, kThumbnailPropTabBoss				,kLibraryProviderPrefix + 49)

DECLARE_PMID(kClassIDSpace, kNewCatalogCmdBoss					,kLibraryProviderPrefix + 50)
DECLARE_PMID(kClassIDSpace, kAddCatalogPropertyCmdBoss			,kLibraryProviderPrefix + 51)
DECLARE_PMID(kClassIDSpace, kAddChangeItemPropertyCmdBoss		,kLibraryProviderPrefix + 52)

DECLARE_PMID(kClassIDSpace, kCatalogPropertyBoss				,kLibraryProviderPrefix + 53)
DECLARE_PMID(kClassIDSpace, kCatalogBoss						,kLibraryProviderPrefix + 54)
DECLARE_PMID(kClassIDSpace, kNewAssetCmdBoss					,kLibraryProviderPrefix + 55)
DECLARE_PMID(kClassIDSpace, kDeleteAssetCmdBoss					,kLibraryProviderPrefix + 56)
DECLARE_PMID(kClassIDSpace, kSetMetaDataCmdBoss					,kLibraryProviderPrefix + 57)	
DECLARE_PMID(kClassIDSpace, kSetThumbnailCmdBoss				,kLibraryProviderPrefix + 58)	
DECLARE_PMID(kClassIDSpace, kSetAssetContentsCmdBoss			,kLibraryProviderPrefix + 59)	
DECLARE_PMID(kClassIDSpace, kRecoverLibraryCmdBoss				,kLibraryProviderPrefix + 60)	

DECLARE_PMID(kClassIDSpace, kLibraryScriptProviderBoss			,kLibraryProviderPrefix + 72)
DECLARE_PMID(kClassIDSpace, kLibraryAssetScriptProviderBoss		,kLibraryProviderPrefix + 73)
DECLARE_PMID(kClassIDSpace, kStoreLAScriptProviderBoss			,kLibraryProviderPrefix + 74)
//DECLARE_PMID(kClassIDSpace, kOpenLibraryScriptProviderBoss		,kLibraryProviderPrefix + 75)
//DECLARE_PMID(kClassIDSpace, kLibrayAppScriptProviderBoss		,kLibraryProviderPrefix + 76)	//obsolete
DECLARE_PMID(kClassIDSpace, kDirInfoBoss						,kLibraryProviderPrefix + 77)
DECLARE_PMID(kClassIDSpace, kLibraryConversionProviderBoss		,kLibraryProviderPrefix + 78)
DECLARE_PMID(kClassIDSpace, kLibraryAssetOpenServiceBoss		,kLibraryProviderPrefix + 79)
DECLARE_PMID(kClassIDSpace, kLibraryErrorStringServiceBoss		,kLibraryProviderPrefix + 80)
DECLARE_PMID(kClassIDSpace, kLibraryFakeDocBoss					,kLibraryProviderPrefix + 81)
DECLARE_PMID(kClassIDSpace, kPageItemDataExchHandlerSnippetHelperBoss ,kLibraryProviderPrefix + 82)
DECLARE_PMID(kClassIDSpace, kSnippetBasedCatalogBoss			,kLibraryProviderPrefix + 90)
DECLARE_PMID(kClassIDSpace, kLibraryAddStructureCmdBoss			,kLibraryProviderPrefix + 91)
DECLARE_PMID(kClassIDSpace, kLibraryUpdateItemCmdBoss			,kLibraryProviderPrefix + 92)
DECLARE_PMID(kClassIDSpace, kLibraryUpdateStructureCmdBoss		,kLibraryProviderPrefix + 93)

// <Service ID>

DECLARE_PMID(kServiceIDSpace, kLibraryServiceID					,kLibraryProviderPrefix + 1)

// <Interface ID>

DECLARE_PMID(kInterfaceIDSpace, IID_ILIBRARYSERVICE					,kLibraryProviderPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ILIBRARY						,kLibraryProviderPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ILIBRARYPREFS					,kLibraryProviderPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace,	IID_ILIBRARYASSETCOLLECTION			,kLibraryProviderPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace,	IID_ILIBRARYSCRAPCONTROLLER			,kLibraryProviderPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace,	IID_ILIBRARYSCRAPUTILS				,kLibraryProviderPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_ILIBRARYSCRAPDATA				,kLibraryProviderPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_ILIBRARYDRAGDROPUTILS			,kLibraryProviderPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_ILIBRARYCMDUTILS				,kLibraryProviderPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace,	IID_ILIBRARYCMDDATA					,kLibraryProviderPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace,	IID_ILIBRARYASSET					,kLibraryProviderPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace,	IID_ILIBRARYASSETCONTENTS			,kLibraryProviderPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace,	IID_ILIBRARYASSETMETADATA			,kLibraryProviderPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace,	IID_ILIBRARYASSETTHUMBNAIL			,kLibraryProviderPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_ILIBRARYMGR						,kLibraryProviderPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_ILIBRARYSIMPLEFILTER			,kLibraryProviderPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_ILIBRARYCOMPLEXFILTER			,kLibraryProviderPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_ICATALOGDATA					,kLibraryProviderPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_IUIDTRANSLATIONTABLE			,kLibraryProviderPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_ILIBRARYSCRIPTUTILS				,kLibraryProviderPrefix + 20)

// Pub Library Additions
DECLARE_PMID(kInterfaceIDSpace, IID_IPROPERTYMGR					,kLibraryProviderPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_IPROPERTY						,kLibraryProviderPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_IPROPERTYTABLE					,kLibraryProviderPrefix + 33)
DECLARE_PMID(kInterfaceIDSpace, IID_IDATETIMEDATA					,kLibraryProviderPrefix + 34)
DECLARE_PMID(kInterfaceIDSpace, IID_ICATALOGLIST					,kLibraryProviderPrefix + 35)
DECLARE_PMID(kInterfaceIDSpace, IID_ICATALOGPROPERTYCMDDATA			,kLibraryProviderPrefix + 36)
DECLARE_PMID(kInterfaceIDSpace, IID_ICATALOG						,kLibraryProviderPrefix + 37)
DECLARE_PMID(kInterfaceIDSpace, IID_IPROPERTYCMDDATA				,kLibraryProviderPrefix + 38)
DECLARE_PMID(kInterfaceIDSpace, IID_IDELETEASSETCMDDATA				,kLibraryProviderPrefix + 39)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETMETADATACMDDATA				,kLibraryProviderPrefix + 40)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETASSETCONTENTSCMDDATA		,kLibraryProviderPrefix + 41)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTREAMMGR						,kLibraryProviderPrefix + 42)
DECLARE_PMID(kInterfaceIDSpace, IID_IUIDBLOBDATATABLE				,kLibraryProviderPrefix + 44)
DECLARE_PMID(kInterfaceIDSpace, IID_IDIRINFO						,kLibraryProviderPrefix + 45)
DECLARE_PMID(kInterfaceIDSpace, IID_ITHUMBNAILDATA					,kLibraryProviderPrefix + 46)
DECLARE_PMID(kInterfaceIDSpace, IID_IASSETCONVERSIONSTATE			,kLibraryProviderPrefix + 47)
DECLARE_PMID(kInterfaceIDSpace, IID_IASSETPAGEITEMLIST				,kLibraryProviderPrefix + 48)
DECLARE_PMID(kInterfaceIDSpace, IID_ILIBRARYCONVERSIONFLAG			,kLibraryProviderPrefix + 49)

// <Implementation ID>

DECLARE_PMID(kImplementationIDSpace, kLibraryServiceProviderImpl			,kLibraryProviderPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kLibraryServiceImpl					,kLibraryProviderPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kLibraryImpl							,kLibraryProviderPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kLibraryPrefsImpl						,kLibraryProviderPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kLibraryAssetCollectionImpl			,kLibraryProviderPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kLibraryScrapControllerImpl			,kLibraryProviderPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kLibraryScrapUtilsImpl					,kLibraryProviderPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kLibraryScrapHandlerImpl				,kLibraryProviderPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kLibraryScrapDataImpl					,kLibraryProviderPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kLibraryDragDropUtilsImpl				,kLibraryProviderPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kLibraryAssetImpl						,kLibraryProviderPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kLibraryAssetContentsImpl				,kLibraryProviderPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kLibraryAssetMetaDataImpl				,kLibraryProviderPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kLibraryAssetThumbnailImpl				,kLibraryProviderPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kLibraryAssetPMDataObjectImpl			,kLibraryProviderPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kLibraryAssetStreamReadImpl			,kLibraryProviderPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kLibraryAssetStreamWriteImpl			,kLibraryProviderPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kLibrarySimpleFilterDataImpl			,kLibraryProviderPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kLibraryComplexFilterDataImpl			,kLibraryProviderPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kCatalogDataImpl						,kLibraryProviderPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kPropertyCmdDataImpl					,kLibraryProviderPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kDeleteAssetCmdDataImpl				,kLibraryProviderPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kSetMetaDataCmdDataImpl				,kLibraryProviderPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kSetAssetContentsCmdDataImpl			,kLibraryProviderPrefix + 25)

DECLARE_PMID(kImplementationIDSpace, kLibraryCmdUtilsImpl					,kLibraryProviderPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kLibraryCmdDataImpl					,kLibraryProviderPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kLibraryAddItemCmdImpl					,kLibraryProviderPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kLibraryCopyItemsCmdImpl				,kLibraryProviderPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kLibraryDeleteItemsCmdImpl				,kLibraryProviderPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kLibraryNewLibCmdImpl					,kLibraryProviderPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kLibraryOpenLibCmdImpl					,kLibraryProviderPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kLibraryCloseLibCmdImpl				,kLibraryProviderPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kDeleteAssetCmdImpl					,kLibraryProviderPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kSetMetaDataCmdImpl					,kLibraryProviderPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kSetThumbnailCmdImpl					,kLibraryProviderPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kRecoverLibraryCmdImpl					,kLibraryProviderPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kNewAssetCmdImpl						,kLibraryProviderPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kNewCatalogCmdImpl						,kLibraryProviderPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kAddCatalogPropertyCmdImpl				,kLibraryProviderPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kSetAssetContentsCmdImpl				,kLibraryProviderPrefix + 55)

DECLARE_PMID(kImplementationIDSpace, kLibraryMemStreamWriteImpl				,kLibraryProviderPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kLibraryMemStreamReadImpl				,kLibraryProviderPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kUIDTranslationTableImpl				,kLibraryProviderPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kCatalogPropertyCmdDataImpl			,kLibraryProviderPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kCatalogListImpl						,kLibraryProviderPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kCatalogImpl							,kLibraryProviderPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kThumbnailPropertyTableImpl			,kLibraryProviderPrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kThumbnailDataImpl						,kLibraryProviderPrefix + 77)
DECLARE_PMID(kImplementationIDSpace, kPropertyMgrImpl						,kLibraryProviderPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kPropertyImpl							,kLibraryProviderPrefix + 79)

DECLARE_PMID(kImplementationIDSpace, kPointPropertyTableImpl				,kLibraryProviderPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kIntPropertyTableImpl					,kLibraryProviderPrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kDateTimePropertyTableImpl				,kLibraryProviderPrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kDateTimeDataImpl						,kLibraryProviderPrefix + 89)
DECLARE_PMID(kImplementationIDSpace, kPMStringPropertyTableImpl				,kLibraryProviderPrefix + 90)
//gap
DECLARE_PMID(kImplementationIDSpace, kLibraryStreamMgrImpl					,kLibraryProviderPrefix + 99)
//gap
DECLARE_PMID(kImplementationIDSpace, kDirInfoImpl							,kLibraryProviderPrefix + 101)
//gap

// Scripting
DECLARE_PMID(kImplementationIDSpace, kLibraryAssetScriptProviderImpl		,kLibraryProviderPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kLibraryScriptObserverImpl				,kLibraryProviderPrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kLibraryScriptProviderImpl				,kLibraryProviderPrefix + 108)
DECLARE_PMID(kImplementationIDSpace, kLibraryScriptUtilsImpl				,kLibraryProviderPrefix + 109)
DECLARE_PMID(kImplementationIDSpace, kStoreLAScriptProviderImpl				,kLibraryProviderPrefix + 110)
//gap
DECLARE_PMID(kImplementationIDSpace, kLibraryAssetScriptImpl				,kLibraryProviderPrefix + 116)
//gap
DECLARE_PMID(kImplementationIDSpace, kLibraryOLETypeLibImpl					,kLibraryProviderPrefix + 119)
DECLARE_PMID(kImplementationIDSpace, kLibraryScriptImpl						,kLibraryProviderPrefix + 120)
//gap
DECLARE_PMID(kImplementationIDSpace, kLibraryAssetOpenFilterImpl			,kLibraryProviderPrefix + 122)
DECLARE_PMID(kImplementationIDSpace, kLibrarySuiteLayoutCSBImpl				,kLibraryProviderPrefix + 123)
DECLARE_PMID(kImplementationIDSpace, kLibrarySuiteDefaultCSBImpl			,kLibraryProviderPrefix + 124)
DECLARE_PMID(kImplementationIDSpace, kLibrarySuiteTextCSBImpl				,kLibraryProviderPrefix + 125)
DECLARE_PMID(kImplementationIDSpace, kLibrarySuiteASBImpl					,kLibraryProviderPrefix + 126)
DECLARE_PMID(kImplementationIDSpace, kLibrarySuiteStoryEditorCSBImpl		,kLibraryProviderPrefix + 127)
DECLARE_PMID(kImplementationIDSpace, kLibraryStyleNameTableImpl				,kLibraryProviderPrefix + 128)
DECLARE_PMID(kImplementationIDSpace, kLibraryParaStyleNameTableImpl			,kLibraryProviderPrefix + 129)
DECLARE_PMID(kImplementationIDSpace, kLibraryCharStyleNameTableImpl			,kLibraryProviderPrefix + 130)
DECLARE_PMID(kImplementationIDSpace, kLibraryInvalidRootNameTableImpl		,kLibraryProviderPrefix + 131)
DECLARE_PMID(kImplementationIDSpace, kLibraryNamedGridsNameTableImpl		,kLibraryProviderPrefix + 132)
DECLARE_PMID(kImplementationIDSpace, kLibraryMojikumiNameTableImpl			,kLibraryProviderPrefix + 133)
DECLARE_PMID(kImplementationIDSpace, kLibraryFalseInitBoolDataImpl			,kLibraryProviderPrefix + 134)
DECLARE_PMID(kImplementationIDSpace, kAssetPageItemListImpl					,kLibraryProviderPrefix + 135)
DECLARE_PMID(kImplementationIDSpace, kLibrarySuiteStructureCSBImpl			,kLibraryProviderPrefix + 136)
DECLARE_PMID(kImplementationIDSpace, kPageItemDataExchHandlerSnippetHelperImpl ,kLibraryProviderPrefix + 137)
DECLARE_PMID(kImplementationIDSpace, kLibraryAddStructureCmdImpl,			kLibraryProviderPrefix + 138)
DECLARE_PMID(kImplementationIDSpace, kLibraryUpdateItemCmdImpl				,kLibraryProviderPrefix + 139)
DECLARE_PMID(kImplementationIDSpace, kLibraryUpdateStructureCmdImpl				,kLibraryProviderPrefix + 140)

//Style sets 
DECLARE_PMID(kImplementationIDSpace, kLibraryParaStyleGroupManagerImpl				,kLibraryProviderPrefix + 142)
DECLARE_PMID(kImplementationIDSpace, kLibraryCharStyleGroupManagerImpl				,kLibraryProviderPrefix + 143)

// <Error ID>
// NOTE:  The offset is used to find the corresponding error string
DECLARE_PMID(kErrorIDSpace, kLibraryOpenFailureError				,kLibraryProviderPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kLibraryAlreadyOpenFailureError			,kLibraryProviderPrefix + 2)
DECLARE_PMID(kErrorIDSpace,	kLibraryCreateFailureError				,kLibraryProviderPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kLibraryWriteFailureError				,kLibraryProviderPrefix + 4)
DECLARE_PMID(kErrorIDSpace, kLibraryReadFailureError				,kLibraryProviderPrefix + 5)
DECLARE_PMID(kErrorIDSpace, kLibraryCloseFailureError				,kLibraryProviderPrefix + 6)
DECLARE_PMID(kErrorIDSpace, kLibraryCorruptError					,kLibraryProviderPrefix + 7)
DECLARE_PMID(kErrorIDSpace, kLibraryWrongVersionError				,kLibraryProviderPrefix + 8)
DECLARE_PMID(kErrorIDSpace, kLibraryGetItemFailureError				,kLibraryProviderPrefix + 9)
DECLARE_PMID(kErrorIDSpace, kLibraryAddItemFailureError				,kLibraryProviderPrefix + 10)
DECLARE_PMID(kErrorIDSpace, kLibraryCopyItemFailureError			,kLibraryProviderPrefix + 11)
DECLARE_PMID(kErrorIDSpace, kLibraryPasteItemFailureError			,kLibraryProviderPrefix + 12)
DECLARE_PMID(kErrorIDSpace, kLibraryRemoveItemFailureError			,kLibraryProviderPrefix + 13)
DECLARE_PMID(kErrorIDSpace, kLibraryAddBlankItemFailureError		,kLibraryProviderPrefix + 14)
DECLARE_PMID(kErrorIDSpace, kLibraryMissingPlugInsFailureError		,kLibraryProviderPrefix + 15)
DECLARE_PMID(kErrorIDSpace, kLibraryExportItemFailureError			,kLibraryProviderPrefix + 16)
// DECLARE_PMID(kErrorIDSpace, kLibraryMissingPlugInsFailureError		,kLibraryProviderPrefix + 16)
// GAP
DECLARE_PMID(kErrorIDSpace, kLibraryNotWritableFailureError			,kLibraryProviderPrefix + 18)
DECLARE_PMID(kErrorIDSpace, kLibraryUpdateItemFailureError				,kLibraryProviderPrefix + 19)
DECLARE_PMID(kErrorIDSpace, kLibraryUpdateBlankItemFailureError		,kLibraryProviderPrefix + 20)
DECLARE_PMID(kErrorIDSpace, kLibraryNotFoundFailureError			,kLibraryProviderPrefix + 21)
DECLARE_PMID(kErrorIDSpace, kLibraryUnknownOpenFailureError			,kLibraryProviderPrefix + 22)

// Messages
DECLARE_PMID(kMessageIDSpace, kLibraryConversionWarningDontShowID	,kLibraryProviderPrefix + 1)
DECLARE_PMID(kMessageIDSpace, IID_INEWLIBRARYMSG					,kLibraryProviderPrefix + 2)
DECLARE_PMID(kMessageIDSpace, IID_IOPENLIBRARYMSG					,kLibraryProviderPrefix + 3)
DECLARE_PMID(kMessageIDSpace, IID_ICLOSELIBRARYMSG					,kLibraryProviderPrefix + 4)

//
//Script Element IDs
//

//Suites
DECLARE_PMID(kScriptInfoIDSpace, kLibrarySuiteScriptElement,				kLibraryProviderPrefix + 1)

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kLibraryObjectScriptElement,				kLibraryProviderPrefix + 40)
DECLARE_PMID(kScriptInfoIDSpace, kLibraryAssetObjectScriptElement,			kLibraryProviderPrefix + 41)

//Events
DECLARE_PMID(kScriptInfoIDSpace, kCreateLibraryMethodScriptElement,			kLibraryProviderPrefix + 80)
//gap
DECLARE_PMID(kScriptInfoIDSpace, kStoreInLibraryMethodScriptElement,			kLibraryProviderPrefix + 82)
DECLARE_PMID(kScriptInfoIDSpace, kStorePageItemMethodScriptElement,			kLibraryProviderPrefix + 83)
DECLARE_PMID(kScriptInfoIDSpace, kPlaceAssetMethodScriptElement,				kLibraryProviderPrefix + 84)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kAssetTypePropertyScriptElement,			kLibraryProviderPrefix + 160)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kAssetTypeEnumScriptElement,				kLibraryProviderPrefix + 220)

#endif // __LibraryID__
