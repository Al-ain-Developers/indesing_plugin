//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/EPSID.h $
//  
//  Owner: David Berggren
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

#ifndef __EPSID_H__
#define __EPSID_H__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

//========================================================================================
// Constants for the  plug-in
//========================================================================================

#define 	kEPSPrefix 					RezLong( 0x6600 )		// double check with DeveloperPrefix.h

// <Start IDC>
// PluginID
#define kEPSPluginName 					"EPS Page Item"
DECLARE_PMID(kPlugInIDSpace, kEPSPluginID, kEPSPrefix + 1)


// <Class ID>
// boss ids
DECLARE_PMID(kClassIDSpace, kEPSItem,						kEPSPrefix  + 1)
DECLARE_PMID(kClassIDSpace, kPICTItem,						kEPSPrefix  + 2)
DECLARE_PMID(kClassIDSpace, kWMFItem,						kEPSPrefix  + 3)
DECLARE_PMID(kClassIDSpace, kImportEPSCmdBoss,				kEPSPrefix 	+ 4)
DECLARE_PMID(kClassIDSpace, kEPSPlaceProviderBoss,			kEPSPrefix 	+ 5)
DECLARE_PMID(kClassIDSpace, kEPSImageReadFormatBoss,		kEPSPrefix  + 6)
DECLARE_PMID(kClassIDSpace, kInDesignPageItemBoss,			kEPSPrefix  + 7)
DECLARE_PMID(kClassIDSpace, kImportDocCmdBoss,				kEPSPrefix  + 8)
DECLARE_PMID(kClassIDSpace, kDeleteEPSItemCmdBoss,			kEPSPrefix  + 9)
DECLARE_PMID(kClassIDSpace, kSetImportDocOptionsCmdBoss,	kEPSPrefix  + 10)
DECLARE_PMID(kClassIDSpace, kEPSTextItemBoss,				kEPSPrefix  + 11)
DECLARE_PMID(kClassIDSpace, kEPSTagTableBoss,				kEPSPrefix  + 12)
DECLARE_PMID(kClassIDSpace, kSetEPSPrefsCmdBoss,			kEPSPrefix  + 13)
DECLARE_PMID(kClassIDSpace, kOPIInfoBoss,					kEPSPrefix  + 14)
DECLARE_PMID(kClassIDSpace, kDCSItemBoss,					kEPSPrefix  + 15)
DECLARE_PMID(kClassIDSpace, kDCSInfoBoss,					kEPSPrefix  + 16)
DECLARE_PMID(kClassIDSpace, kDisplayListPageItemBoss,		kEPSPrefix  + 17)
DECLARE_PMID(kClassIDSpace, kCommentExtractorBoss,			kEPSPrefix	+ 18)
DECLARE_PMID(kClassIDSpace, kEPSImportConvertProviderBoss,	kEPSPrefix	+ 19)
DECLARE_PMID(kClassIDSpace, kCascadePlaceInDesignDocCmdBoss,		kEPSPrefix + 20)
DECLARE_PMID(kClassIDSpace, kPSEDataSourceStreamBoss,				kEPSPrefix + 21)
DECLARE_PMID(kClassIDSpace, kQRCodeVCardCreationScriptProviderBoss,	kEPSPrefix + 22)
DECLARE_PMID(kClassIDSpace, kQRCodePlainTextScriptProviderBoss,		kEPSPrefix + 23)
DECLARE_PMID(kClassIDSpace, kQRCodeHyperlinkScriptProviderBoss,		kEPSPrefix + 24)
DECLARE_PMID(kClassIDSpace, kQRCodeEmailScriptProviderBoss,			kEPSPrefix + 25)
DECLARE_PMID(kClassIDSpace, kQRCodeTextMsgScriptProviderBoss,		kEPSPrefix + 26)



DECLARE_PMID(kClassIDSpace, kEPSConversionProviderBoss,				kEPSPrefix	+ 1000)

// EPS import preferences script
DECLARE_PMID(kClassIDSpace, kEPSImportPrefsScriptProviderBoss,	kEPSPrefix + 30)
DECLARE_PMID(kClassIDSpace, kEPSTextItemScriptProviderBoss,		kEPSPrefix + 31)
DECLARE_PMID(kClassIDSpace, kSetEPSTextDataCmdBoss,				kEPSPrefix + 32)
DECLARE_PMID(kClassIDSpace, kSetEPSTextBoundsCmdBoss,			kEPSPrefix + 33)

// Place InDesign Document Scripting
DECLARE_PMID(kClassIDSpace, kINDDAttributesScriptProviderBoss,	kEPSPrefix + 34)
DECLARE_PMID(kClassIDSpace, kINDDPlacePrefsScriptProviderBoss,	kEPSPrefix + 35)
DECLARE_PMID(kClassIDSpace, kPlacedPageDocFileHandlerBoss,		kEPSPrefix + 36)

// QR Codes
DECLARE_PMID(kClassIDSpace, kQRCodeDataBoss,				kEPSPrefix + 40)
DECLARE_PMID(kClassIDSpace, kQREmailDataBoss,				kEPSPrefix + 41)
DECLARE_PMID(kClassIDSpace, kQRHyperLinkDataBoss,			kEPSPrefix + 42)
DECLARE_PMID(kClassIDSpace, kQRPlainTextDataBoss,			kEPSPrefix + 43)
DECLARE_PMID(kClassIDSpace, kQRvCardDataBoss,				kEPSPrefix + 44)
DECLARE_PMID(kClassIDSpace, kQRSMSDataBoss,					kEPSPrefix + 45)

// Command for creating QR code.
DECLARE_PMID(kClassIDSpace, kCreateQRCodeCmdBoss, kEPSPrefix + 51)
DECLARE_PMID(kClassIDSpace, kCreateQRCodeEmailCmdBoss, kEPSPrefix + 52)
DECLARE_PMID(kClassIDSpace, kCreateQRCodevCardCmdBoss, kEPSPrefix + 53)
DECLARE_PMID(kClassIDSpace, kCreateQRCodeSMSCmdBoss, kEPSPrefix + 54)
DECLARE_PMID(kClassIDSpace, kCreateQRCodeHyperLinkCmdBoss, kEPSPrefix + 55)
DECLARE_PMID(kClassIDSpace, kCreateQRCodePlainTextCmdBoss, kEPSPrefix + 56)

// SVG
DECLARE_PMID(kClassIDSpace, kSVGItem,					kEPSPrefix + 57)
DECLARE_PMID(kClassIDSpace, kSVGPlaceProviderBoss,		kEPSPrefix + 58)
DECLARE_PMID(kClassIDSpace, kSVGReadZipStreamBoss, kEPSPrefix + 59)
DECLARE_PMID(kClassIDSpace, kSVGWriteZipStreamBoss, kEPSPrefix + 60)
DECLARE_PMID(kClassIDSpace, kSVGPreviewWidgetBoss, kEPSPrefix + 61)
DECLARE_PMID(kClassIDSpace, kSetSVGImportPrefsCmdBoss, kEPSPrefix + 62)


// <Interface ID>
// interface ids
DECLARE_PMID(kInterfaceIDSpace, IID_IIMPORTEPSCMDDATA, kEPSPrefix  + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IEPSPREFERENCES, kEPSPrefix  + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IEPSTEXTITEMDATA, kEPSPrefix  + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IEPSATTRIBUTES, kEPSPrefix  + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IEPSTAGTABLE, kEPSPrefix  + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IEPSPREFSCMDDATA, kEPSPrefix  + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IOPIINFO, kEPSPrefix  + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IDCSINFO, kEPSPrefix  + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMMENTEXTRACTOR, kEPSPrefix  + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IEPSDISPLAYINFO, kEPSPrefix  + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IEPSCOLORXFORMOBSERVER, kEPSPrefix  + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IPSEDATASOURCESTREAMDATA, kEPSPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IPHOTOSHOPEPSIMAGEDATA, kEPSPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMPORTDOCOPTIONS, kEPSPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMPORTDOCUTILS, kEPSPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IINDDLINKSOBSERVER, kEPSPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IOPENDOCCOPY, kEPSPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_INDDAPPLICATIONOBSERVER, kEPSPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_IINDDSOURCEPAGEITEM_UIDDATA, kEPSPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_IBARCODESUITE, kEPSPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_ICREATEQRCODECMDDATA, kEPSPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_IQRHYPERLINKDATA, kEPSPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_IQRPLAINTEXTDATA, kEPSPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_IQRVCARDDATA, kEPSPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_IQRCODEMETADATA, kEPSPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_IQREMAILDATA, kEPSPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_IQRSMSDATA, kEPSPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_IBARCODEFACADE, kEPSPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_IEPSITEMUID	, kEPSPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_IQRCODEDATAUID	, kEPSPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_IQRVCARDDATA_2, kEPSPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_IZIPSTREAMDATA, kEPSPrefix + 32)
DECLARE_PMID(kInterfaceIDSpace, IID_ISVGUTILS, kEPSPrefix + 33)
DECLARE_PMID(kInterfaceIDSpace, IID_ISVGIMPORTPREFS, kEPSPrefix + 34)
DECLARE_PMID(kInterfaceIDSpace, IID_ISVGATTRIBUTES, kEPSPrefix + 35)
DECLARE_PMID(kInterfaceIDSpace, IID_ISVGDOCPREFS, kEPSPrefix + 36)

// <Implementation ID>
// implementation ids

DECLARE_PMID(kImplementationIDSpace, kEPSShapeImpl, kEPSPrefix	+ 1)
DECLARE_PMID(kImplementationIDSpace, kPICTShapeImpl, kEPSPrefix	+ 2)
DECLARE_PMID(kImplementationIDSpace, kWMFShapeImpl, kEPSPrefix	+ 3)
DECLARE_PMID(kImplementationIDSpace, kImportEPSCmdDataImpl, kEPSPrefix	+ 4)
DECLARE_PMID(kImplementationIDSpace, kEPSPlaceServiceImpl, kEPSPrefix	+ 5)
DECLARE_PMID(kImplementationIDSpace, kEPSPlaceProviderImpl, kEPSPrefix	+ 6)
DECLARE_PMID(kImplementationIDSpace, kImportEPSCmdImpl, kEPSPrefix	+ 7)
DECLARE_PMID(kImplementationIDSpace, kEPSImageReadFormatInfoImpl, kEPSPrefix  + 8)
DECLARE_PMID(kImplementationIDSpace, kEPSImageReadFormatImpl, kEPSPrefix  + 9)
DECLARE_PMID(kImplementationIDSpace, kSessionEPSPreferencesImpl, kEPSPrefix  + 10)
DECLARE_PMID(kImplementationIDSpace, kInDesignPageItemShapeImpl, kEPSPrefix  + 11)
DECLARE_PMID(kImplementationIDSpace, kImportDocCmdImpl, kEPSPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kEPSItemScrapImpl, kEPSPrefix  + 13)
DECLARE_PMID(kImplementationIDSpace, kDeleteEPSItemCmdImpl, kEPSPrefix  + 14)
DECLARE_PMID(kImplementationIDSpace, kInDesignPageItemDrawHandlerImpl, kEPSPrefix  + 15)
DECLARE_PMID(kImplementationIDSpace, kEPSTextItemShapeImpl, kEPSPrefix	+ 16)
DECLARE_PMID(kImplementationIDSpace, kEPSTextItemDataImpl, kEPSPrefix	+ 17)
DECLARE_PMID(kImplementationIDSpace, kEPSAttributesImpl, kEPSPrefix  + 18)
DECLARE_PMID(kImplementationIDSpace, kEPSTagTableImpl, kEPSPrefix	+ 19)
DECLARE_PMID(kImplementationIDSpace, kSetEPSPrefsCmdImpl, kEPSPrefix	+ 20)
DECLARE_PMID(kImplementationIDSpace, kEPSPrefsCmdDataImpl, kEPSPrefix	+ 21)
DECLARE_PMID(kImplementationIDSpace, kOPIInfoImpl, kEPSPrefix	+ 22)
DECLARE_PMID(kImplementationIDSpace, kDCSShapeImpl, kEPSPrefix	+ 23)
DECLARE_PMID(kImplementationIDSpace, kDCSInfoImpl, kEPSPrefix	+ 24)
DECLARE_PMID(kImplementationIDSpace, kCommentExtractorImpl, kEPSPrefix	+ 25)
DECLARE_PMID(kImplementationIDSpace, kEPSDisplayInfoImpl, kEPSPrefix	+ 26)
DECLARE_PMID(kImplementationIDSpace, kGeometryEPSImpl, kEPSPrefix	+ 27)
DECLARE_PMID(kImplementationIDSpace, kEPSItemInkResourcesImpl, kEPSPrefix  + 28)
DECLARE_PMID(kImplementationIDSpace, kAllProcessInkResourcesImpl, kEPSPrefix  + 29)
//DECLARE_PMID(kImplementationIDSpace, kEPSRenderingObjSuiteImpl, kEPSPrefix	+ 31)
DECLARE_PMID(kImplementationIDSpace, kEPSSwatchReferenceDataImpl, kEPSPrefix	+ 31)
DECLARE_PMID(kImplementationIDSpace, kEPSColorXFormObserverImpl, kEPSPrefix	+ 32)
DECLARE_PMID(kImplementationIDSpace, kEPSFontNamesImpl, kEPSPrefix	+ 33)
DECLARE_PMID(kImplementationIDSpace, kEPSTextItemFontNamesImpl, kEPSPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kEPSImportPreviewImpl, kEPSPrefix  + 35)
DECLARE_PMID(kImplementationIDSpace, kImportDocOptionsImpl, kEPSPrefix  + 36)
DECLARE_PMID(kImplementationIDSpace, kImportDocUtilsImpl, kEPSPrefix  + 37)
DECLARE_PMID(kImplementationIDSpace, kSetImportDocOptionsCmdImpl, kEPSPrefix  + 38)
DECLARE_PMID(kImplementationIDSpace, kCascadePlaceInDesignDocCmdImpl, kEPSPrefix  + 39)
DECLARE_PMID(kImplementationIDSpace, kEPS_ConversionProviderImpl, kEPSPrefix	+ 40)
DECLARE_PMID(kImplementationIDSpace, kEPSItemVisitorHelperImpl, kEPSPrefix  + 41)
DECLARE_PMID(kImplementationIDSpace, kEPSTextItemVisitorHelperImpl, kEPSPrefix  + 42)
DECLARE_PMID(kImplementationIDSpace, kInDesignPageItemDrawServiceImpl, kEPSPrefix  + 43)
DECLARE_PMID(kImplementationIDSpace, kEPSCacheHintsImpl, kEPSPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kPSEDataSourceStreamImpl, kEPSPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kPSEDataSourceStreamDataImpl, kEPSPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kPhotoshopEPSImageDataImpl, kEPSPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kPlacedINDDLinksObserverImpl, kEPSPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kINDDXPPageItemDrawSetupImpl, kEPSPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kEPSImportPrefsScriptProviderImpl, kEPSPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kEPSCopyDisplayListInMemoryCacheImpl, kEPSPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kEPSTextItemScriptProviderImpl, kEPSPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kSetEPSTextDataCmdImpl, kEPSPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kSetEPSTextBoundsCmdImpl, kEPSPrefix + 54)

// Place InDesign Document Scripting
DECLARE_PMID(kImplementationIDSpace, kINDDPlacePrefsScriptProviderImpl, kEPSPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kINDDAttributesScriptProviderImpl, kEPSPrefix + 56)

DECLARE_PMID(kImplementationIDSpace, kINDDCopyDisplayListInMemoryCacheImpl, kEPSPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kPlacedINDDPageFontNamesImpl, kEPSPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kINDDPageNameImpl, kEPSPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kOpenDocCopyImpl, kEPSPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kINDDApplicationObserverImpl, kEPSPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kPlacedPageDocFileHandlerImpl, kEPSPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kInDesignDocPlaceBehaviorImpl,	kEPSPrefix + 63)

// Barcode suite impl IDs.
DECLARE_PMID(kImplementationIDSpace, kBarcodeSuiteLayoutCSBImpl,	kEPSPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kBarcodeSuiteDefaultCSBImpl,	kEPSPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kBarcodeSuiteASBImpl,	kEPSPrefix + 66)
DECLARE_PMID (kImplementationIDSpace, kBarcodeSuiteASBSelExtImpl, kEPSPrefix + 67)
DECLARE_PMID (kImplementationIDSpace, kBarcodeSuiteDefaultCSBSelExtImpl, kEPSPrefix + 68)
DECLARE_PMID (kImplementationIDSpace, kBarcodeSuiteLayoutCSBSelExtImpl, kEPSPrefix + 69)
DECLARE_PMID (kImplementationIDSpace, kCreateQRCodeCmdImpl, kEPSPrefix + 70)
DECLARE_PMID (kImplementationIDSpace, kCreateQRCodeCmdDataImpl, kEPSPrefix + 71)
DECLARE_PMID (kImplementationIDSpace, kQRCmdDataImpl, kEPSPrefix + 72)
DECLARE_PMID (kImplementationIDSpace, kCreateQRCodeEmailCmdImpl, kEPSPrefix + 73)
DECLARE_PMID (kImplementationIDSpace, kCreateQRCodevCardCmdImpl, kEPSPrefix + 74)
DECLARE_PMID (kImplementationIDSpace, kCreateQRCodeSmsCmdImpl, kEPSPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kCreateQRCodeHyperLinkCmdImpl,	kEPSPrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kCreateQRCodePlainTextCmdImpl,	kEPSPrefix + 77)

// QR Codes
DECLARE_PMID(kImplementationIDSpace, kQRCodeMetaDataImpl,	kEPSPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kQREmailDataImpl,	kEPSPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kQRHyperLinkDataImpl,	kEPSPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kQRPlainTextDataImpl,	kEPSPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kQRvCardDataImpl,	kEPSPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kQRSMSDataImpl,	kEPSPrefix + 85)

// Barcode suite impl IDs, contd..
DECLARE_PMID(kImplementationIDSpace, kBarcodeFacadeImpl, kEPSPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kBarcodeSuiteTextCSBImpl,	kEPSPrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kBarcodeSuiteTextCSBSelExtImpl, kEPSPrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kBarcodeSuiteXMLCSBImpl,	kEPSPrefix + 89)
DECLARE_PMID(kImplementationIDSpace, kBarcodeSuiteXMLCSBSelExtImpl, kEPSPrefix + 90)
DECLARE_PMID(kImplementationIDSpace, kBarcodeSuiteTableCSBImpl,	kEPSPrefix + 91)
DECLARE_PMID(kImplementationIDSpace, kBarcodeSuiteTableCSBSelExtImpl, kEPSPrefix + 92)

//Scripting Impls for QR Codes
DECLARE_PMID(kImplementationIDSpace, kQRCodePlainTextScriptProviderImpl,	kEPSPrefix + 93)
DECLARE_PMID(kImplementationIDSpace, kQRCodeHyperlinkScriptProviderImpl,	kEPSPrefix + 94)
DECLARE_PMID(kImplementationIDSpace, kQRCodeEmailScriptProviderImpl,	kEPSPrefix + 95)
DECLARE_PMID(kImplementationIDSpace, kQRCodeTextMsgScriptProviderImpl,	kEPSPrefix + 96)
DECLARE_PMID(kImplementationIDSpace, kQRCodeScriptProviderImpl,	kEPSPrefix + 97)
DECLARE_PMID(kImplementationIDSpace, kQRCodeSMSScriptimpl,	kEPSPrefix + 98)
DECLARE_PMID(kImplementationIDSpace, kQRCodeEmailScriptimpl,	kEPSPrefix + 99)
DECLARE_PMID(kImplementationIDSpace, kQRCodeHyperlinkScriptimpl,	kEPSPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kQRCodePlainTextScriptimpl,	kEPSPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kQRCodeVCardScriptimpl,	kEPSPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kQRvCardData_2Impl,	kEPSPrefix + 103)

// SVG
DECLARE_PMID(kImplementationIDSpace, kSVGShapeImpl,					kEPSPrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kSVGPlaceProviderImpl,			kEPSPrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kSVGPlaceServiceImpl,			kEPSPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kSVGFontNamesImpl,				kEPSPrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kSVGFlattenerUsageImpl,		kEPSPrefix + 108)
DECLARE_PMID(kImplementationIDSpace, kSVGReadZipStreamImpl, kEPSPrefix + 109)
DECLARE_PMID(kImplementationIDSpace, kSVGWriteZipStreamImpl, kEPSPrefix + 110)
DECLARE_PMID(kImplementationIDSpace, kSVGZipStreamDataImpl, kEPSPrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kSVGUtilsImpl, kEPSPrefix + 112)
DECLARE_PMID(kImplementationIDSpace, kSetSVGImportPrefsCmdImpl, kEPSPrefix + 113)
DECLARE_PMID(kImplementationIDSpace, kSVGImportPrefsImpl, kEPSPrefix + 114)
DECLARE_PMID(kImplementationIDSpace, kSVGAttributesImpl, kEPSPrefix + 115)
DECLARE_PMID(kImplementationIDSpace, kSVGDocPrefsImpl, kEPSPrefix + 116)

// <Ignore>
// resource id
#define kEPSStringsRsrcID				1100
#define kEPSStringsNoTransRsrcID		1200


// <Service ID>
//	Service IDs

// <Error ID>
//	Error Codes
DECLARE_PMID(kErrorIDSpace, kEPSErrorStartNum, kEPSPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kEPSErrorParse, kEPSPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kEPSErrorParseMissingFont, kEPSPrefix + 3)

//
//Script Element IDs
//

DECLARE_PMID(kScriptInfoIDSpace, kEPSImportReadOPICommentsPropertyScriptElement,	kEPSPrefix + 5)
DECLARE_PMID(kScriptInfoIDSpace, kEPSImportCreateFramePropertyScriptElement,		kEPSPrefix + 6)
DECLARE_PMID(kScriptInfoIDSpace, kEPSImportProxyEnumScriptElement,					kEPSPrefix + 7)
DECLARE_PMID(kScriptInfoIDSpace, kEPSImportProxyPropertyScriptElement,				kEPSPrefix + 8)
DECLARE_PMID(kScriptInfoIDSpace, kEPSImportDisplayResPropertyScriptElement,			kEPSPrefix + 9)
DECLARE_PMID(kScriptInfoIDSpace, kEPSImportPrefsObjectScriptElement,				kEPSPrefix + 10)
DECLARE_PMID(kScriptInfoIDSpace, kEPSImportPrefsPropertyScriptElement,				kEPSPrefix + 11)
//gap
DECLARE_PMID(kScriptInfoIDSpace, kEPSTextObjectScriptElement,						kEPSPrefix + 20)
DECLARE_PMID(kScriptInfoIDSpace, kEPSTextDataPropertyScriptElement,					kEPSPrefix + 21)
DECLARE_PMID(kScriptInfoIDSpace, kEPSTextAttrBoundPropertyScriptElement,			kEPSPrefix + 22)
DECLARE_PMID(kScriptInfoIDSpace, kINDDObjectScriptElement,							kEPSPrefix + 23)
DECLARE_PMID(kScriptInfoIDSpace, kINDDCropOptionsEnumScriptElement,					kEPSPrefix + 24)
DECLARE_PMID(kScriptInfoIDSpace, kINDDCropPropertyScriptElement,					kEPSPrefix + 25)
DECLARE_PMID(kScriptInfoIDSpace, kINDDPageNumberPropertyScriptElement,				kEPSPrefix + 26)
DECLARE_PMID(kScriptInfoIDSpace, kINDDPlacePreferencesObjectScriptElement,			kEPSPrefix + 27)
DECLARE_PMID(kScriptInfoIDSpace, kINDDPlacePreferencePropertyScriptElement,			kEPSPrefix + 28)
DECLARE_PMID(kScriptInfoIDSpace, kINDDAttributePropertyScriptElement,				kEPSPrefix + 29)
DECLARE_PMID(kScriptInfoIDSpace, kINDDAttributesObjectScriptElement,				kEPSPrefix + 30)

DECLARE_PMID(kScriptInfoIDSpace, kQRCodeVCardDataObjectScriptElement,				kEPSPrefix + 31)
DECLARE_PMID(kScriptInfoIDSpace, kQRCodeVCardFirstNamePropertyScriptElement,		kEPSPrefix + 32)
DECLARE_PMID(kScriptInfoIDSpace, kQRCodeVCardLastNamePropertyScriptElement,			kEPSPrefix + 33)
DECLARE_PMID(kScriptInfoIDSpace, kQRCodeVCardTitlePropertyScriptElement,			kEPSPrefix + 34)
DECLARE_PMID(kScriptInfoIDSpace, kQRCodeVCardCellPhonePropertyScriptElement,		kEPSPrefix + 35)
DECLARE_PMID(kScriptInfoIDSpace, kQRCodeVCardPhoneNumberPropertyScriptElement,		kEPSPrefix + 36)
DECLARE_PMID(kScriptInfoIDSpace, kQRCodeVCardEmailIdPropertyScriptElement,			kEPSPrefix + 37)
DECLARE_PMID(kScriptInfoIDSpace, kQRCodeVCardOrganisationPropertyScriptElement,		kEPSPrefix + 38)
DECLARE_PMID(kScriptInfoIDSpace, kQRCodeVCardAddressPropertyScriptElement,			kEPSPrefix + 39)
DECLARE_PMID(kScriptInfoIDSpace, kQRCodeVCardCityPropertyScriptElement,				kEPSPrefix + 40)
DECLARE_PMID(kScriptInfoIDSpace, kQRCodeVCardCountryPropertyScriptElement,			kEPSPrefix + 41)
DECLARE_PMID(kScriptInfoIDSpace, kQRCodeVCardPostalCodePropertyScriptElement,		kEPSPrefix + 42)
DECLARE_PMID(kScriptInfoIDSpace, kQRCodeVCardURLPropertyScriptElement,				kEPSPrefix + 43)
DECLARE_PMID(kScriptInfoIDSpace, kGenerateQRCodeMethodScriptElement,				kEPSPrefix + 44)
DECLARE_PMID(kScriptInfoIDSpace, kQRCodeEmailDataObjectScriptElement,				kEPSPrefix + 45)
DECLARE_PMID(kScriptInfoIDSpace, kQRCodeEmailToPropertyScriptElement,				kEPSPrefix + 46)
DECLARE_PMID(kScriptInfoIDSpace, kQRCodeEmailSubPropertyScriptElement,				kEPSPrefix + 47)
DECLARE_PMID(kScriptInfoIDSpace, kQRCodeEmailMesgPropertyScriptElement,				kEPSPrefix + 48)
DECLARE_PMID(kScriptInfoIDSpace, kQRCodeTextMsgDataObjectScriptElement,				kEPSPrefix + 49)
DECLARE_PMID(kScriptInfoIDSpace, kQRCodePhoneNumPropertyScriptElement,				kEPSPrefix + 50)
DECLARE_PMID(kScriptInfoIDSpace, kQRCodeTextMesgPropertyScriptElement,				kEPSPrefix + 51)
DECLARE_PMID(kScriptInfoIDSpace, kQRCodePlainTextDataObjectScriptElement,			kEPSPrefix + 52)
DECLARE_PMID(kScriptInfoIDSpace, kQRCodePlainTextPropertyScriptElement,				kEPSPrefix + 53)
DECLARE_PMID(kScriptInfoIDSpace, kQRCodeHyperlinkDataObjectScriptElement,			kEPSPrefix + 54)
DECLARE_PMID(kScriptInfoIDSpace, kQRCodeURLDataPropertyScriptElement,				kEPSPrefix + 55)
DECLARE_PMID(kScriptInfoIDSpace, kQRCodePlaceOnSpreadMethodScriptElement,			kEPSPrefix + 56)
DECLARE_PMID(kScriptInfoIDSpace, kCreatePlainTextQRCodeOnPageItemMethodScriptElement,			kEPSPrefix + 57)
DECLARE_PMID(kScriptInfoIDSpace, kCreateHyperlinkQRCodeOnPageItemMethodScriptElement,			kEPSPrefix + 58)
DECLARE_PMID(kScriptInfoIDSpace, kCreateTextMsgQRCodeOnPageItemMethodScriptElement,			kEPSPrefix + 59)
DECLARE_PMID(kScriptInfoIDSpace, kCreateEmailQRCodeOnPageItemMethodScriptElement,			kEPSPrefix + 60)
DECLARE_PMID(kScriptInfoIDSpace, kCreateVCardQRCodeOnPageItemMethodScriptElement,			kEPSPrefix + 61)
DECLARE_PMID(kScriptInfoIDSpace, kVCardTypeDefScriptElement,			kEPSPrefix + 62)
DECLARE_PMID(kScriptInfoIDSpace, kVCardDataScriptElement,			kEPSPrefix + 63)
DECLARE_PMID(kScriptInfoIDSpace, kQRCodeSwatchPropertyScriptElement,			kEPSPrefix + 64)

DECLARE_PMID(kScriptInfoIDSpace, kQRCodeVCardStatePropertyScriptElement,				kEPSPrefix + 65)

//svg
DECLARE_PMID(kScriptInfoIDSpace, kSVGObjectScriptElement,							kEPSPrefix + 70)
DECLARE_PMID(kScriptInfoIDSpace, kUseSVGAsEnumScriptElement,						kEPSPrefix + 71)
DECLARE_PMID(kScriptInfoIDSpace, kUseSVGAsPropertyScriptElement,					kEPSPrefix + 72)




//GUIDS
// {526B10ED-ADC9-4c8b-AC96-5BE855B16B60}
#define kEPSImportPrefs_CLSID {0x526b10ed, 0xadc9, 0x4c8b, { 0xac, 0x96, 0x5b, 0xe8, 0x55, 0xb1, 0x6b, 0x60 }}
// {98DC8882-4AE4-42ee-94A8-1B981541546F}
#define kEPSText_CLSID { 0x98dc8882, 0x4ae4, 0x42ee, { 0x94, 0xa8, 0x1b, 0x98, 0x15, 0x41, 0x54, 0x6f } }
// {97AE2672-B3F4-4e54-9137-D60D1F5F6C1C}
#define kEPSTexts_CLSID { 0x97ae2672, 0xb3f4, 0x4e54, { 0x91, 0x37, 0xd6, 0xd, 0x1f, 0x5f, 0x6c, 0x1c } }
// {F8CB4D2C-3F31-4edc-A111-9170FCB8248D}
#define kINDD_CLSID { 0xf8cb4d2c, 0x3f31, 0x4edc, {0xa1, 0x11, 0x91, 0x70, 0xfc, 0xb8, 0x24, 0x8d } }
// {E8F27BBA-95E7-4821-96B3-F274AECB2230}
#define kINDDs_CLSID { 0xe8f27bba, 0x95e7, 0x4821, {0x96, 0xb3, 0xf2, 0x74, 0xae, 0xcb, 0x22, 0x30 } }
// {8AABBB19-3302-49d2-A68F-56CD12A098C5}
#define kINDDPages_CLSID { 0x8aabbb19, 0x3302, 0x49d2, { 0xa6, 0x8f, 0x56, 0xcd, 0x12, 0xa0, 0x98, 0xc5 } }
// {5FF31BDF-D60D-4b63-B5BC-ED6427B6D763}
#define kINDDPlacePref_CLSID {0x5ff31bdf, 0xd60d, 0x4b63, {0xb5, 0xbc, 0xed, 0x64, 0x27, 0xb6, 0xd7, 0x63 } }
// {AE476BF1-0129-4823-A1CF-71F3C4E8E628}
#define kINDDAttribute_CLSID {0xae476bf1, 0x129, 0x4823, {0xa1, 0xcf, 0x71, 0xf3, 0xc4, 0xe8, 0xe6, 0x28 } }
// {229F927F-28C1-4914-A69F-0117D6EF6299}
#define kQRCodeVCardData_CLSID { 0x229f927f, 0x28c1, 0x4914, { 0xa6, 0x9f, 0x1, 0x17, 0xd6, 0xef, 0x62, 0x99 } }
// {76C1D126-09A2-4299-B5D5-FE2170587747}
#define kQRCodeEmailData_CLSID { 0x76c1d126, 0x9a2, 0x4299, { 0xb5, 0xd5, 0xfe, 0x21, 0x70, 0x58, 0x77, 0x47 } }
// {9AC22210-F4E8-416C-8572-F257B80ABC15}
#define kQRCodeTextMsgData_CLSID { 0x9ac22210, 0xf4e8, 0x416c, { 0x85, 0x72, 0xf2, 0x57, 0xb8, 0xa, 0xbc, 0x15 } }
// {A42A5C64-1EB7-4B99-9BB5-3B7E1C6A9E16}
#define kQRCodePlainTextData_CLSID { 0xa42a5c64, 0x1eb7, 0x4b99, { 0x9b, 0xb5, 0x3b, 0x7e, 0x1c, 0x6a, 0x9e, 0x16 } }
// {E862E06B-4FEE-4125-B911-C9426B76667A}
#define kQRCodeHyperlinkData_CLSID { 0xe862e06b, 0x4fee, 0x4125, { 0xb9, 0x11, 0xc9, 0x42, 0x6b, 0x76, 0x66, 0x7a } }
// {8A532630-ADF8-4BB7-B3F1-E25F2C941359}
#define kQRCodesDataCollection_CLSID { 0x8a532630, 0xadf8, 0x4bb7, { 0xb3, 0xf1, 0xe2, 0x5f, 0x2c, 0x94, 0x13, 0x59 } }

// {FFB554E4-1435-40AC-8AC8-7213CEFAC73D}
#define kQRCodesPlainDataCollection_CLSID { 0xffb554e4, 0x1435, 0x40ac, { 0x8a, 0xc8, 0x72, 0x13, 0xce, 0xfa, 0xc7, 0x3d } }
// {BC1D3260-A232-4A63-BD31-8F4657D6066D}
#define kQRCodesHyperlinkCollection_CLSID { 0xbc1d3260, 0xa232, 0x4a63, { 0xbd, 0x31, 0x8f, 0x46, 0x57, 0xd6, 0x6, 0x6d } }
// {650C9EEE-0583-4C1D-9E35-EDAE4BDB38C2}
#define kQRCodesEmailCollection_CLSID { 0x650c9eee, 0x583, 0x4c1d, { 0x9e, 0x35, 0xed, 0xae, 0x4b, 0xdb, 0x38, 0xc2 } }
// {AE7229CA-12DF-4183-BE20-C23F09F4FC6C}
#define kQRCodesTextMsgCollection_CLSID { 0xae7229ca, 0x12df, 0x4183, { 0xbe, 0x20, 0xc2, 0x3f, 0x9, 0xf4, 0xfc, 0x6c } }


// TBD -- Not actual generated GUIDs
// {C8F27BBA-95E7-4821-92B3-F274AECB2230}
#define kSVG_CLSID { 0xC8f27bba, 0x95e7, 0x4821, {0x92, 0xb3, 0xf2, 0x74, 0xae, 0xcb, 0x22, 0x30 } }
// {8BABBB19-3302-49d2-A58F-56CD12A098C5}
#define kSVGs_CLSID { 0x8babbb19, 0x3302, 0x49d2, { 0xa5, 0x8f, 0x56, 0xcd, 0x12, 0xa0, 0x98, 0xc5 } }







enum EPSScriptIDs
{
	c_InDesignPageItem = 'InDp',
	c_InDesignPageItems = 'InDs',	//5.0 DOM
	c_InDesignPages =	'IDPs',		//6.0 DOM
	c_INDDAttribute =	'InDA',
	p_INDDAttribute =	'pIDA',
	//c_INDDPlacePref =	'InDP',
	//p_INDDPlacePref =	'pIDP',
	p_INDDPlaceCrop =	'pIDc',
	en_INDDCrop =		'enID',

	c_EPS =				'EPS ',	// typeEPS in AERegistry.h
	c_EPSs =			'EPSs',
	c_EPSText =			'EPST',
	c_EPSTexts =		'EPTs',
	en_EPS				= c_EPS,
    
    c_SVG   =           'SVG ',
    c_SVGs  =           'SVGs',
	en_UseSVGAs =		'usve',
	p_UseSVGAs =		'usvp',
	en_EmbedCode =		'embc',
	en_ObjectTags =		'objt',
};
enum QRCodeScriptIDs
{
	c_QRCodeVCardData		= 'QRvC',
	c_QRCodeCollection		= 'QvCa',
	p_QRCodeVCardFName		= 'QRFN',
	p_QRCodeVCardLName		= 'QRLN',
	p_QRCodeVCardTitle		= 'QRTl',
	p_QRCodeVCardCellPh		= 'QRCP',
	p_QRCodeVCardPhone		= 'QRPh',
	p_QRCodeVCardEmailId	= 'QREm',
	p_QRCodeVCardOrg		= 'QROg',
	p_QRCodeVCardAddress	= 'QRAd',
	p_QRCodeVCardCity		= 'QRCi',
	p_QRCodeVCardState		= 'QRSt',
	p_QRCodeVCardCountry	= 'QRCn',
	p_QRCodeVCardPostalCode = 'QRPC',
	p_QRCodeVCardURL        = 'QRUr',
	c_QRCodeEmailData		= 'QReM',
	c_QRCodeEmailDataCollection = 'QRem',
	p_QRCodeEmailTo			= 'QETo',
	p_QRCodeEmailSub		= 'QRSu',
	p_QRCodeEmailMesg		= 'GNbo',
	c_QRCodeTextMsgData		= 'QRTM',
	c_QRCodeTextMsgDataCollection = 'QRTm',
	p_QRCodeTextPhone		= 'QPhN',
	p_QRCodeTextMesg		= 'QRtM',
	c_QRCodePlainTextData	= 'QRPT',
	c_QRCodePlainTextDataCollection  = 'QRpT',
	p_QRCodePlainText		= 'TYPt',
	c_QRCodeHyperlinkData	= 'QRHy',
	c_QRCodeHyperlinkCollection		= 'QRhy',
	p_QRCodeURLData			= 'QrUr',
	e_CreateQRVCardCode		= 'QrVc',
	e_CreateQREmailCode		= 'Qrem',
	e_CreateQRSMSCode		= 'QrSm',
	e_CreateQRPlainTextCode	= 'QrPt',
	e_CreateQRURLCode		= 'Qurl',
	p_vCardData				= 'vCQR',
	t_VCardHeaderType		= 'QvCt',
	p_QRCodeSwatch			= 'QRsw',
};
//_______________________________________________________________________________________
// <ViewPortAttr ID>
// ViewPortAttrIDs
//_______________________________________________________________________________________

// boolean attribute: if non-zero, EPSShape will create a wrapper port for your 
// IGraphicsPort when parsing with MPS; if zero (false), it will attempt to use the port
// specified in your IAGMPortData. Default is kFalse.
DECLARE_PMID(kViewPortAttrIDSpace, kParseToWrapperPortVPAttr, kEPSPrefix + 1)

// boolean attribute: if non-zero, EPSShape will enable MPS streaming behavior; zero
// disables streaming (images are provided as bands in this case). Default is kTrue.
DECLARE_PMID(kViewPortAttrIDSpace, kEnableMPSStreamingVPAttr, kEPSPrefix + 2)

// boolean attribute: if non-zero, we are building a display list for a placed INDD page.
DECLARE_PMID(kViewPortAttrIDSpace, kBuildingDLforPlacedINDDVPAttr, kEPSPrefix + 3)
#endif
