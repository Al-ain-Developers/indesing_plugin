//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/MetaDataID.h $
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
//========================================================================================

#ifndef __MetaDataID_h__
#define __MetaDataID_h__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kMetaDataPrefix	 					RezLong(0x12600)

// ----- Plug-in ID -----

#define kMetaDataPluginName 			"MetaData"
DECLARE_PMID(kPlugInIDSpace,			kMetaDataPluginID,					kMetaDataPrefix + 1)

// ----- Class IDs -----

//gap
DECLARE_PMID(kClassIDSpace,				kSetAdobeCoreMetaDataCmdBoss,		kMetaDataPrefix + 2)
DECLARE_PMID(kClassIDSpace,				kSetAdobeRightsMgmtMDCmdBoss,		kMetaDataPrefix + 3)
DECLARE_PMID(kClassIDSpace,				kSetAdobeBasicJobMDCmdBoss,			kMetaDataPrefix + 4)
DECLARE_PMID(kClassIDSpace,				kMetaDataBeforeSaveDocResponderBoss,kMetaDataPrefix + 5)
DECLARE_PMID(kClassIDSpace,				kMetaDataBeforeSaveAsResponderBoss,	kMetaDataPrefix + 6)
DECLARE_PMID(kClassIDSpace,				kMetaDataSaveACopyDocResponderBoss,	kMetaDataPrefix + 7)
DECLARE_PMID(kClassIDSpace,				kMetaDataAfterNewDocResponderBoss,	kMetaDataPrefix + 8)
DECLARE_PMID(kClassIDSpace,				kMetaDataBoss,						kMetaDataPrefix + 9)
DECLARE_PMID(kClassIDSpace,				kSetAdobeMediaMgmtMDCmdBoss,		kMetaDataPrefix + 10)
DECLARE_PMID(kClassIDSpace,				kMetaDataOpsBoss,					kMetaDataPrefix + 11)
DECLARE_PMID(kClassIDSpace,				kMetaDataAfterOpenDocResponderBoss,	kMetaDataPrefix + 12)
DECLARE_PMID(kClassIDSpace,				kMetaDataBeforeCloseDocResponderBoss,kMetaDataPrefix + 13)
DECLARE_PMID(kClassIDSpace,				kAppendMetaDataCmdBoss,				kMetaDataPrefix + 14)
DECLARE_PMID(kClassIDSpace,				kReplaceMetaDataCmdBoss,			kMetaDataPrefix + 15)
DECLARE_PMID(kClassIDSpace,				kMetaDataDuringNewDocResponderBoss,	kMetaDataPrefix + 16)
DECLARE_PMID(kClassIDSpace,				kMetaDataPropScriptProviderBoss,	kMetaDataPrefix + 17)
DECLARE_PMID(kClassIDSpace,				kMetaDataPrefsScriptProviderBoss,	kMetaDataPrefix + 18)
DECLARE_PMID(kClassIDSpace,				kStripForeignMetaDataCmdBoss,		kMetaDataPrefix + 20)
DECLARE_PMID(kClassIDSpace,				kMetaDataSchemaConversionBoss,		kMetaDataPrefix + 21)
DECLARE_PMID(kClassIDSpace,				kMetaDataPhase2ConversionBoss,		kMetaDataPrefix + 22)
DECLARE_PMID(kClassIDSpace,				kDeleteMetaDataCmdBoss,				kMetaDataPrefix + 23)
DECLARE_PMID(kClassIDSpace,				kMetaDataReferenceConverterBoss,	kMetaDataPrefix + 24)
DECLARE_PMID(kClassIDSpace,				kMetaDataDeleteCleanupBoss,			kMetaDataPrefix + 25)
DECLARE_PMID(kClassIDSpace,				kRemoveScrapItemPhase2ConversionBoss,kMetaDataPrefix + 26)
DECLARE_PMID(kClassIDSpace,				kMetaDataErrorStringServiceBoss,	kMetaDataPrefix + 27)
DECLARE_PMID(kClassIDSpace,				kSetMetaXAPCmdBoss,					kMetaDataPrefix + 28)
DECLARE_PMID(kClassIDSpace,				kMetaDataCodeConversionProviderBoss,kMetaDataPrefix + 29)
DECLARE_PMID(kClassIDSpace,				kSetXMPPropertyCmdBoss,				kMetaDataPrefix + 30)
DECLARE_PMID(kClassIDSpace,				kCreateContainerItemCmdBoss,		kMetaDataPrefix + 31)
DECLARE_PMID(kClassIDSpace,				kMetaDataPacketScriptProviderBoss,	kMetaDataPrefix + 32)
DECLARE_PMID(kClassIDSpace,				kMetaDataPktPropScriptProviderBoss, kMetaDataPrefix + 33)
DECLARE_PMID(kClassIDSpace,				kSetMetadataBeforeSaveCmdBoss,		kMetaDataPrefix + 34)
DECLARE_PMID(kClassIDSpace, 			kLinkMetadataScriptProviderBoss, 	kMetaDataPrefix + 35)
DECLARE_PMID(kClassIDSpace, 			kSetAdobeCoreMetaDataCreatorToolCmdBoss,	kMetaDataPrefix + 36)
DECLARE_PMID(kClassIDSpace, 			kMetaDataIteratorBoss,				kMetaDataPrefix + 37)
DECLARE_PMID(kClassIDSpace,				kMetaDataAfterSaveACopyDocResponderBoss, kMetaDataPrefix + 38)


// ----- Interface IDs -----

DECLARE_PMID(kInterfaceIDSpace,			IID_IMETADATA,						kMetaDataPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace,			IID_IMETADATAACCESS,				kMetaDataPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace,			IID_IADOBECOREMETADATA,				kMetaDataPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace,			IID_IADOBEBASICJOBMETADATA,			kMetaDataPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace,			IID_IADOBERIGHTSMGMTMETADATA,		kMetaDataPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace,			IID_IADOBEMEDIAMGMTMETADATA,		kMetaDataPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace,			IID_ISETADOBECOREMDCMDDATA,			kMetaDataPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace,			IID_ISETADOBERIGHTSMGMTMDCMDDATA,	kMetaDataPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace,			IID_ISETADOBEBASICJOBMDCMDDATA,		kMetaDataPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace,			IID_ISETADOBEMEDIAMGMTMDCMDDATA,	kMetaDataPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace,			IID_IMETADATAOBSERVER,				kMetaDataPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace,			IID_ICALCULATEMETADATA,				kMetaDataPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace,			IID_IXMPTHUMBNAIL,					kMetaDataPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace,			IID_IRESTOREINTERNALMETADATA,		kMetaDataPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace,			IID_IAPPENDMETADATACMDDATA,			kMetaDataPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace,			IID_IREPLACEMETADATACMDDATA,		kMetaDataPrefix + 16)
// gap
DECLARE_PMID(kInterfaceIDSpace,			IID_ISTRIPFOREIGNMETADATACMDDATA,	kMetaDataPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace,			IID_IMETADATAUTILS,					kMetaDataPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace,			IID_IMETADATAUIDDATA,				kMetaDataPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace,			IID_IXMPPACKETFILTER,				kMetaDataPrefix + 21)
//DECLARE_PMID(kInterfaceIDSpace,			IID_IMETADATAACCESS2,				kMetaDataPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace,			IID_IREGENERATELINKMANIFEST,		kMetaDataPrefix + 23)
// gap
DECLARE_PMID(kInterfaceIDSpace,			IID_ICHARSTRINGDATA,				kMetaDataPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace,			IID_ISETXMPPROPERTYCMDDATA,			kMetaDataPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace,			IID_ICREATECONTAINERITEMCMDDATA,	kMetaDataPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace,			IID_ISETMDBEFORESAVECMDDATA,		kMetaDataPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace,			IID_IADOBEAUXMETADATA,				kMetaDataPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace,			IID_IMETADATAITERATOR,				kMetaDataPrefix + 30)

// ----- Implementatin IDs -----

DECLARE_PMID(kImplementationIDSpace,	kAdobeMediaMgmtMetaDataImpl,		kMetaDataPrefix + 1)
DECLARE_PMID(kImplementationIDSpace,	kAdobeBasicJobMetaDataImpl,			kMetaDataPrefix + 2)
DECLARE_PMID(kImplementationIDSpace,	kAdobeRightsMgmtMetaDataImpl,		kMetaDataPrefix + 3)
DECLARE_PMID(kImplementationIDSpace,	kAdobeCoreMetaDataImpl,				kMetaDataPrefix + 4)
DECLARE_PMID(kImplementationIDSpace,	kMetaDataAccessImpl,				kMetaDataPrefix + 5)
DECLARE_PMID(kImplementationIDSpace,	kSetAdobeCoreMDCmdDataImpl,			kMetaDataPrefix + 6)
DECLARE_PMID(kImplementationIDSpace,	kSetAdobeCoreMetaDataCmdImpl,		kMetaDataPrefix + 7)
DECLARE_PMID(kImplementationIDSpace,	kSetAdobeRightsMgmtMDCmdDataImpl,	kMetaDataPrefix + 8)
DECLARE_PMID(kImplementationIDSpace,	kSetAdobeRightsMgmtMDCmdImpl,		kMetaDataPrefix + 9)
DECLARE_PMID(kImplementationIDSpace,	kSetAdobeBasicJobMDCmdDataImpl,		kMetaDataPrefix + 10)
DECLARE_PMID(kImplementationIDSpace,	kSetAdobeBasicJobMDCmdImpl,			kMetaDataPrefix + 11)
DECLARE_PMID(kImplementationIDSpace,	kDocumentDialogObserverImpl,		kMetaDataPrefix + 12)
DECLARE_PMID(kImplementationIDSpace,	kMetaDataResponderImpl,				kMetaDataPrefix + 13)
DECLARE_PMID(kImplementationIDSpace,	kSetAdobeMediaMgmtMDCmdDataImpl,	kMetaDataPrefix + 14)
DECLARE_PMID(kImplementationIDSpace,	kSetAdobeMediaMgmtMDCmdImpl,		kMetaDataPrefix + 15)
DECLARE_PMID(kImplementationIDSpace,	kMetaDataImpl,						kMetaDataPrefix + 16)
DECLARE_PMID(kImplementationIDSpace,	kDocumentContentObserverImpl,		kMetaDataPrefix + 17)
DECLARE_PMID(kImplementationIDSpace,	kMetaDataOpsProviderImpl,			kMetaDataPrefix + 18)
DECLARE_PMID(kImplementationIDSpace,	kCalculateMetaDataImpl,				kMetaDataPrefix + 19)
DECLARE_PMID(kImplementationIDSpace,	kDocumentThumbnailImpl,				kMetaDataPrefix + 20)
DECLARE_PMID(kImplementationIDSpace,	kRestoreInternalMetaDataImpl,		kMetaDataPrefix + 21)
DECLARE_PMID(kImplementationIDSpace,	kAppendMetaDataCmdDataImpl,			kMetaDataPrefix + 22)
DECLARE_PMID(kImplementationIDSpace,	kAppendMetaDataCmdImpl,				kMetaDataPrefix + 23)
DECLARE_PMID(kImplementationIDSpace,	kReplaceMetaDataCmdDataImpl,		kMetaDataPrefix + 24)
DECLARE_PMID(kImplementationIDSpace,	kReplaceMetaDataCmdImpl,			kMetaDataPrefix + 25)
DECLARE_PMID(kImplementationIDSpace,	kMetaDataErrorStringServiceImpl,	kMetaDataPrefix + 26)
DECLARE_PMID(kImplementationIDSpace,	kMetaDataPropScriptProviderImpl,	kMetaDataPrefix + 27)
DECLARE_PMID(kImplementationIDSpace,	kMetaDataPrefsScriptProviderImpl,	kMetaDataPrefix + 28)
DECLARE_PMID(kImplementationIDSpace,	kPlacedEPSItemMetaDataImpl,			kMetaDataPrefix + 29)
DECLARE_PMID(kImplementationIDSpace,	kStripForeignMetaDataCmdDataImpl,	kMetaDataPrefix + 30)
DECLARE_PMID(kImplementationIDSpace,	kStripForeignMetaDataCmdImpl,		kMetaDataPrefix + 31)
DECLARE_PMID(kImplementationIDSpace,	kMetaDataUtilsImpl,					kMetaDataPrefix + 32)
DECLARE_PMID(kImplementationIDSpace,	kPlacedPDFItemMetaDataImpl,			kMetaDataPrefix + 33)
DECLARE_PMID(kImplementationIDSpace,	kMetaDataPhase2ConversionImpl,		kMetaDataPrefix + 34)
DECLARE_PMID(kImplementationIDSpace,	kDeleteMetaDataCmdImpl,				kMetaDataPrefix + 35)
DECLARE_PMID(kImplementationIDSpace,	kMetaDataScrapItemImpl,				kMetaDataPrefix + 36)
DECLARE_PMID(kImplementationIDSpace,	kMetaDataReferenceConverterImpl,	kMetaDataPrefix + 37)
DECLARE_PMID(kImplementationIDSpace,	kMetaDataDeleteCleanupImpl,			kMetaDataPrefix + 38)
DECLARE_PMID(kImplementationIDSpace,	kXMPPacketFilterImpl,				kMetaDataPrefix + 39)
DECLARE_PMID(kImplementationIDSpace,	kRemoveScrapItemPhase2ConversionImpl,kMetaDataPrefix + 40)
DECLARE_PMID(kImplementationIDSpace,	kPlacedINDDPageMetaDataImpl,		kMetaDataPrefix + 41)
DECLARE_PMID(kImplementationIDSpace,	kPlacedImageItemMetaDataImpl,		kMetaDataPrefix + 42)
// gap
DECLARE_PMID(kImplementationIDSpace,	kSetMetaXAPCmdImpl,					kMetaDataPrefix + 44)
// gap
DECLARE_PMID(kImplementationIDSpace,	kMetaDataCodeConversionProviderImpl,kMetaDataPrefix + 46)
DECLARE_PMID(kImplementationIDSpace,	kCharStringDataImpl,				kMetaDataPrefix + 47)
DECLARE_PMID(kImplementationIDSpace,	kSetXMPPropertyCmdImpl,				kMetaDataPrefix + 48)
DECLARE_PMID(kImplementationIDSpace,	kSetXMPPropertyCmdDataImpl,			kMetaDataPrefix + 49)
DECLARE_PMID(kImplementationIDSpace,	kCreateContainerItemCmdDataImpl,	kMetaDataPrefix + 50)
DECLARE_PMID(kImplementationIDSpace,	kCreateContainerItemCmdImpl,		kMetaDataPrefix + 51)
DECLARE_PMID(kImplementationIDSpace,	kMetaDataPacketScriptProviderImpl,	kMetaDataPrefix + 52)
DECLARE_PMID(kImplementationIDSpace,	kMetaDataPktPropScriptProviderImpl,	kMetaDataPrefix + 53)
DECLARE_PMID(kImplementationIDSpace,	kSetMDBeforeSaveCmdDataImpl,		kMetaDataPrefix + 54)
DECLARE_PMID(kImplementationIDSpace,	kSetMetadataBeforeSaveCmdImpl,		kMetaDataPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, 	kLinkMetadataScriptProviderImpl,	kMetaDataPrefix + 56)
DECLARE_PMID(kImplementationIDSpace,	kAdobeAuxMetaDataImpl,				kMetaDataPrefix + 57)
DECLARE_PMID(kImplementationIDSpace,	kSetAdobeCoreMetaDataCreatorToolCmdImpl,	kMetaDataPrefix + 58)
DECLARE_PMID(kImplementationIDSpace,	kMetaDataIteratorImpl,				kMetaDataPrefix + 59)

// ----- Widget IDs -----

// ----- Action IDs -----
DECLARE_PMID(kActionIDSpace,			kFileInfoActionID,					kMetaDataPrefix + 1)
DECLARE_PMID(kActionIDSpace,			kFileInfoSepActionID,				kMetaDataPrefix + 2)
DECLARE_PMID(kActionIDSpace,			kStoryInfoActionID,					kMetaDataPrefix + 3)

// ----- Service IDs -----

DECLARE_PMID(kServiceIDSpace,			kMetaDataOpsService,				kMetaDataPrefix + 1)

// ErrorID
DECLARE_PMID(kErrorIDSpace,				kNoMetaDataAvailableError,			kMetaDataPrefix + 1)
DECLARE_PMID(kErrorIDSpace,				kInvalidMetaDataError,				kMetaDataPrefix + 2)

//
//Script Element IDs
//

//Suites
//DECLARE_PMID(kScriptInfoIDSpace, k???SuiteScriptElement,					kMetaDataPrefix + 1)

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kMetaDataPrefsObjectScriptElement,			kMetaDataPrefix + 40)
DECLARE_PMID(kScriptInfoIDSpace, kMetaDataPacketObjectScriptElement,		kMetaDataPrefix + 41)
DECLARE_PMID(kScriptInfoIDSpace, kLinkMetadataObjectScriptElement,			kMetaDataPrefix + 42)

//Events
DECLARE_PMID(kScriptInfoIDSpace, kSaveMethodScriptElement,					kMetaDataPrefix + 80)
DECLARE_PMID(kScriptInfoIDSpace, kLoadMetaDataMethodScriptElement,			kMetaDataPrefix + 81)
DECLARE_PMID(kScriptInfoIDSpace, kAppendMethodScriptElement,					kMetaDataPrefix + 82)
//DECLARE_PMID(kScriptInfoIDSpace, kPurgeAdditionalInfoMethodScriptElement,	kMetaDataPrefix + 83)
DECLARE_PMID(kScriptInfoIDSpace, kGetXMPPropertyScriptElement,				kMetaDataPrefix + 84)
DECLARE_PMID(kScriptInfoIDSpace, kSetXMPPropertyScriptElement,				kMetaDataPrefix + 85)
DECLARE_PMID(kScriptInfoIDSpace, kContainerTypeEnumScriptElement,			kMetaDataPrefix + 86)
DECLARE_PMID(kScriptInfoIDSpace, kCreateContainerItemScriptElement,			kMetaDataPrefix + 87)
DECLARE_PMID(kScriptInfoIDSpace, kCountContainerScriptElement,				kMetaDataPrefix + 88)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kMetaDataPrefsPropertyScriptElement,		kMetaDataPrefix + 140)
DECLARE_PMID(kScriptInfoIDSpace, kAuthorPropertyScriptElement,				kMetaDataPrefix + 141)
DECLARE_PMID(kScriptInfoIDSpace, kJobNamePropertyScriptElement,				kMetaDataPrefix + 142)
DECLARE_PMID(kScriptInfoIDSpace, kCopyrightedPropertyScriptElement,			kMetaDataPrefix + 143)
DECLARE_PMID(kScriptInfoIDSpace, kCopyRightNoticePropertyScriptElement,		kMetaDataPrefix + 144)
DECLARE_PMID(kScriptInfoIDSpace, kOwnerURLPropertyScriptElement,			kMetaDataPrefix + 145)
DECLARE_PMID(kScriptInfoIDSpace, kKeywordsPropertyScriptElement,			kMetaDataPrefix + 146)
DECLARE_PMID(kScriptInfoIDSpace, kServerURLPropertyScriptElement,			kMetaDataPrefix + 147)
//DECLARE_PMID(kScriptInfoIDSpace, kCheckedOutToPropertyScriptElement,		kMetaDataPrefix + 148)
DECLARE_PMID(kScriptInfoIDSpace, kModificationDatePropertyScriptElement,	kMetaDataPrefix + 149)
DECLARE_PMID(kScriptInfoIDSpace, kCreationDatePropertyScriptElement,		kMetaDataPrefix + 150)
//DECLARE_PMID(kScriptInfoIDSpace, kLocalFilePropertyScriptElement,			kMetaDataPrefix + 151)
DECLARE_PMID(kScriptInfoIDSpace, kContentPropertyScriptElement,				kMetaDataPrefix + 152)
DECLARE_PMID(kScriptInfoIDSpace, kDocumentTitleNamePropertyScriptElement,	kMetaDataPrefix + 153)
DECLARE_PMID(kScriptInfoIDSpace, kApplicationPropertyScriptElement,			kMetaDataPrefix + 154)
DECLARE_PMID(kScriptInfoIDSpace, kFormatPropertyScriptElement,				kMetaDataPrefix + 155)
DECLARE_PMID(kScriptInfoIDSpace, kMetaDataPacketPropertyScriptElement,		kMetaDataPrefix + 156)
DECLARE_PMID(kScriptInfoIDSpace, kLinkMetadataPropertyScriptElement,		kMetaDataPrefix + 157)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kCopyrightStatusEnumScriptElement,			kMetaDataPrefix + 220)


//GUIDs
// {6CEFF8B2-3BA3-4693-97DF-813F9DDA71CF}
#define kLinkMetadata_CLSID { 0x6ceff8b2, 0x3ba3, 0x4693, { 0x97, 0xdf, 0x81, 0x3f, 0x9d, 0xda, 0x71, 0xcf } }
// {F50AB9D8-9C61-499e-9EAB-66FA113EF7D4}
#define kMetaDataPref_CLSID { 0xf50ab9d8, 0x9c61, 0x499e, { 0x9e, 0xab, 0x66, 0xfa, 0x11, 0x3e, 0xf7, 0xd4 } }
// {24E6CA90-7263-48f5-971A-B001202BBECE}
#define kMetaDataPacket_CLSID { 0x24e6ca90, 0x7263, 0x48f5, { 0x97, 0x1a, 0xb0, 0x1, 0x20, 0x2b, 0xbe, 0xce } }

#endif // __MetaDataID_h__
