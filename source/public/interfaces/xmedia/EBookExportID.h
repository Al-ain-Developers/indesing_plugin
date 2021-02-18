//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/EBookExportID.h $
//  
//  Owner: Gang Xiao
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
//  Info:	Contains IDs used by the EbookExport plugin.
//  
//========================================================================================

#ifndef __EbookExportID__
#define __EbookExportID__

// ----- Interfaces -----

#include "IDFactory.h"

// ----- Includes -----

#include "CrossPlatformTypes.h"


#define kEBookExportPrefix				RezLong(0x21A00)

//
// PluginID
//
#define kEBookExportPluginName 			"EbookExport"
DECLARE_PMID(kPlugInIDSpace, kEBookExportPluginID,					kEBookExportPrefix + 1)

//
// <Class ID>
//
DECLARE_PMID(kClassIDSpace, kEBookExportProviderBoss,				kEBookExportPrefix + 1)
DECLARE_PMID(kClassIDSpace, kEBookExportBookProviderBoss,			kEBookExportPrefix + 2)
DECLARE_PMID(kClassIDSpace, kXHTMLExportProviderBoss,				kEBookExportPrefix + 3)
DECLARE_PMID(kClassIDSpace, kXHTMLEBookExporterBaseBoss,			kEBookExportPrefix + 4)
DECLARE_PMID(kClassIDSpace, kEBookExporterBoss,						kEBookExportPrefix + 5)	
DECLARE_PMID(kClassIDSpace, kEBookXHTMLPhase2ConversionBoss,		kEBookExportPrefix + 6)
DECLARE_PMID(kClassIDSpace, kXHTMLExportBoss,						kEBookExportPrefix + 7)	
DECLARE_PMID(kClassIDSpace, kSetEBookExportPrefsCmdBoss,			kEBookExportPrefix + 8)
DECLARE_PMID(kClassIDSpace, kEPubExportPrefsScriptProviderBoss,		kEBookExportPrefix + 9)
DECLARE_PMID(kClassIDSpace, kXHTMLExportPrefsScriptProviderBoss,	kEBookExportPrefix + 10)
DECLARE_PMID(kClassIDSpace, kEBookExportErrorStringServiceBoss,		kEBookExportPrefix + 11)
DECLARE_PMID(kClassIDSpace, kSetXHTMLExportPrefsCmdBoss,			kEBookExportPrefix + 12)
DECLARE_PMID(kClassIDSpace, kEBookExportConversionProviderBoss,		kEBookExportPrefix + 13)
DECLARE_PMID(kClassIDSpace, kFixedLayoutEBookExporterBoss,			kEBookExportPrefix + 14)	
DECLARE_PMID(kClassIDSpace, kTextIteratorBoss,						kEBookExportPrefix + 22)
DECLARE_PMID(kClassIDSpace, kSetFillStrokeNoneCmdBoss,				kEBookExportPrefix + 23)
DECLARE_PMID(kClassIDSpace, kExcludeTextFlagVPAttr,					kEBookExportPrefix + 24)
DECLARE_PMID(kClassIDSpace, kExcludeInlineGraphicFlagVPAttr,			kEBookExportPrefix + 25)
DECLARE_PMID(kClassIDSpace, kEBookExportFXLProviderBoss,				kEBookExportPrefix + 26)
DECLARE_PMID(kClassIDSpace, kSetEBookExportFXLPrefsCmdBoss,				kEBookExportPrefix + 27)
DECLARE_PMID(kClassIDSpace, kEPubExportFXLPrefsScriptProviderBoss,		kEBookExportPrefix + 28)
DECLARE_PMID(kClassIDSpace, kInvalidateWaxLineCmdBoss,					kEBookExportPrefix + 29)
DECLARE_PMID(kClassIDSpace, kSetEBookViewingAppsPrefsCmdBoss,			kEBookExportPrefix + 30)
DECLARE_PMID(kClassIDSpace, kEPubViewingAppsPrefsScriptProviderBoss,	kEBookExportPrefix + 31)
DECLARE_PMID(kClassIDSpace, kSetXHTMLExportFXLPrefsCmdBoss,				kEBookExportPrefix + 32)
DECLARE_PMID(kClassIDSpace, kXHTMLExportFXLPrefsScriptProviderBoss,		kEBookExportPrefix + 33)
DECLARE_PMID(kClassIDSpace, kExcludeRubyFlagVPAttr,						kEBookExportPrefix + 34)
DECLARE_PMID(kClassIDSpace, kSetPublishPrefsCmdBoss,					kEBookExportPrefix + 35)
DECLARE_PMID(kClassIDSpace, kPublishPrefsScriptProviderBoss,			kEBookExportPrefix + 36)
DECLARE_PMID(kClassIDSpace, kLastMileConnectionStartupShutdownBoss,		kEBookExportPrefix + 37)
DECLARE_PMID(kClassIDSpace, kXHTMLPublishExportBoss,					kEBookExportPrefix + 38)
//
// <Interface ID>
//
DECLARE_PMID(kInterfaceIDSpace, IID_IEBOOKEXPORT,					kEBookExportPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IXHTMLEXPORT,					kEBookExportPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOMBUILDER,					kEBookExportPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOMPROCESSOR,					kEBookExportPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IHTMLEPUBEXPORTUTILS,			kEBookExportPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IXHTMLEXPORTSUITE,				kEBookExportPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IXMLWRITER,						kEBookExportPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTYLESHEETSMANAGER,			kEBookExportPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IEBOOKIDMANAGER,				kEBookExportPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_EBOOKRASTERIZER,				kEBookExportPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTYLECSSGENERATOR,				kEBookExportPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IXHTMLEXPORTPREFS,				kEBookExportPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IEPUBEXPORTPREFS,				kEBookExportPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IHTMLEPUBEXPORTCONTEXT,			kEBookExportPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IHTMLRESOURCESMANAGER,			kEBookExportPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IHTMLEPUBPRIVATEPREVIEWOPTION,	kEBookExportPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IHTMLPAGEITEMUTILS,				kEBookExportPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_IEPUBEXPORTCOUNT,				kEBookExportPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_IEPUBEXPORTPREFS_2,				kEBookExportPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_IEPUBEXPORTFXLPREFS,			kEBookExportPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_EPUBPRIVATEFXLOPTION,			kEBookExportPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_IFXLBOOKEXPORT,					kEBookExportPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_IEPUBVIEWINGAPPSPREFS,			kEBookExportPrefix + 23)

DECLARE_PMID(kInterfaceIDSpace, IID_IJAVASCRIPTMANAGER,				kEBookExportPrefix + 24)

DECLARE_PMID(kInterfaceIDSpace, IID_IXHTMLEXPORTFXLPREFS,			kEBookExportPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_XHTMLPRIVATEFXLOPTION,			kEBookExportPrefix + 26)
//Obsolete DECLARE_PMID(kInterfaceIDSpace, IID_IEPUBEXPORTFXLPREFS_2,			kEBookExportPrefix + 27) //DO NOT REUSE
DECLARE_PMID(kInterfaceIDSpace, IID_IHIGHBEAMDATALOGGER,			kEBookExportPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_IHTMLPUBLISHSEQUENCE,			kEBookExportPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_IHTMLIMAGESTORE,				kEBookExportPrefix + 30)

DECLARE_PMID(kInterfaceIDSpace, IID_PUBLISHCANCEL,					kEBookExportPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_IPUBLISHPREFS,					kEBookExportPrefix + 32)
DECLARE_PMID(kInterfaceIDSpace, IID_IPUBLISHOPTION,					kEBookExportPrefix + 33)
DECLARE_PMID(kInterfaceIDSpace, IID_ILASTMILECONNECTIONCACHE,		kEBookExportPrefix + 34)
DECLARE_PMID(kInterfaceIDSpace, IID_ILASTMILEIMSIDLETASK,			kEBookExportPrefix + 35)

DECLARE_PMID(kInterfaceIDSpace, IID_IEXPORTEDFILESDATA,				kEBookExportPrefix + 36)
DECLARE_PMID(kInterfaceIDSpace, IID_IEBOOKEXPORTXMLOPTIONSDATA,		kEBookExportPrefix + 37)
DECLARE_PMID(kInterfaceIDSpace, IID_IPUBLISHPDFREQUIRED,			kEBookExportPrefix + 38)
DECLARE_PMID(kInterfaceIDSpace, IID_IREPUBLISHPREFS,				kEBookExportPrefix + 39)

DECLARE_PMID(kInterfaceIDSpace, IID_IREFLOWBOOKEXPORT,				kEBookExportPrefix + 40)


//
// <Implementation ID>
//
DECLARE_PMID(kImplementationIDSpace, kEBookExportProviderImpl,			kEBookExportPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kEBookExportErrorStringServiceImpl,kEBookExportPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kXHTMLExportImpl,					kEBookExportPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kHTMLDOMProcessorImpl,				kEBookExportPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kPGTDOMProcessorImpl,				kEBookExportPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kDOMBuilderImpl,					kEBookExportPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kHTMLEPubExportUtilsImpl,			kEBookExportPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kXHTMLExportSuiteASBImpl,			kEBookExportPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kXHTMLExportSuiteLayoutCSBImpl,	kEBookExportPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kXHTMLExportSuiteTextCSBImpl,		kEBookExportPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kXHTMLExportSuiteTableCSBImpl,		kEBookExportPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kEBookRasterizerImpl,				kEBookExportPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kXHTMLWriterImpl,					kEBookExportPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kStyleSheetsManagerImpl,			kEBookExportPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kEBookIDManagerImpl,				kEBookExportPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kEBookExportXMLOptionsImpl,		kEBookExportPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kSetEBookExportPrefsCmdImpl,		kEBookExportPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kEPubXHTMLWriterImpl,				kEBookExportPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kXHTMLExportProviderImpl,			kEBookExportPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kEBookXHTMLPhase2ConversionImpl,	kEBookExportPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kEBookExportImpl,					kEBookExportPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kXHTMLExportPrefsScriptProviderImpl,kEBookExportPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kEBookExportPrefsScriptProviderImpl,kEBookExportPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kStyleCSSGeneratorImpl,			kEBookExportPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kXHTMLExportPrefsImpl,				kEBookExportPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kEPubExportPrefsImpl,				kEBookExportPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kHTMLEPubExportContextImpl,		kEBookExportPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kSetXHTMLExportPrefsCmdImpl,		kEBookExportPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kHTMLResourcesManagerImpl,			kEBookExportPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kHTMLPageitemUtilsImpl,			kEBookExportPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kEPUBExportCountImpl,				kEBookExportPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kPublishPrefsImpl,					kEBookExportPrefix + 32)
//DECLARE_PMID(kImplementationIDSpace, kFixedLayoutEPubDrawEHImpl,		kEBookExportPrefix + 33)
//DECLARE_PMID(kImplementationIDSpace, kEPubPageitemRasterizerImpl,		kEBookExportPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kSetFillStrokeNoneCmdImpl,			kEBookExportPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kEPubExportPrefs_2Impl,				kEBookExportPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kEPubExportFXLPrefsImpl,                kEBookExportPrefix + 37) 
DECLARE_PMID(kImplementationIDSpace, kSetEBookExportFXLPrefsCmdImpl,		kEBookExportPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kEBookExportFXLPrefsScriptProviderImpl,kEBookExportPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kInvalidateWaxLineCmdImpl,kEBookExportPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kEPubViewingAppsPrefsImpl,				kEBookExportPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kSetEBookViewingAppsPrefsCmdImpl,		kEBookExportPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kEBookViewingAppsPrefsScriptProviderImpl,kEBookExportPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kJavaScriptManagerImpl,			kEBookExportPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kSetXHTMLExportFXLPrefsCmdImpl,		kEBookExportPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kXHTMLExportFXLPrefsImpl,				kEBookExportPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kXHTMLExportFXLPrefsScriptProviderImpl,kEBookExportPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kEPubExportFXLPrefs_2ImplObsolete,		kEBookExportPrefix + 48) //DO NOT REUSE
DECLARE_PMID(kImplementationIDSpace, kHighBeamDataLoggerImpl,				kEBookExportPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kHTMLPublishSequenceImpl,					kEBookExportPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kSetPublishPrefsCmdImpl,					kEBookExportPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kPublishPrefsScriptProviderImpl,			kEBookExportPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kHTMLImageStoreImpl,					kEBookExportPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kLastMileConnectionCacheImpl,			kEBookExportPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kLastMileIMSIdleTaskImpl,				kEBookExportPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kLastMileConnectionStartupShutdownImpl,kEBookExportPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kExportedFilesDataImpl,				kEBookExportPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kPublishImageStoreImpl,				kEBookExportPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kEBookExportXMLOptionsDataImpl,		kEBookExportPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kPublishPdfReqdImpl,					kEBookExportPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kXHTMLPublishExportImpl,				kEBookExportPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kRePublishPrefsImpl,					kEBookExportPrefix + 62)

//
// <Error ID>
//
DECLARE_PMID(kErrorIDSpace, kBookMasterDocMissing,								kEBookExportPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kEPubFontNotEmbeddable,								kEBookExportPrefix + 2)

//
//Script Element IDs
//
DECLARE_PMID(kScriptInfoIDSpace, kEPubExportPrefsObjectScriptElement,			kEBookExportPrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kEPubExportPrefsPropertyScriptElement,			kEBookExportPrefix + 2)
DECLARE_PMID(kScriptInfoIDSpace, kHTMLExportPrefsObjectScriptElement,			kEBookExportPrefix + 3)
DECLARE_PMID(kScriptInfoIDSpace, kHTMLExportPrefsPropertyScriptElement,			kEBookExportPrefix + 4)

// ebook
// -- general panel
DECLARE_PMID(kScriptInfoIDSpace, kIncludeDocMetadataPropertyScriptElement,		kEBookExportPrefix + 5)
DECLARE_PMID(kScriptInfoIDSpace, kPublisherPropertyScriptElement,				kEBookExportPrefix + 6)
DECLARE_PMID(kScriptInfoIDSpace, kUniqueIdentifierPropertyScriptElement,		kEBookExportPrefix + 7)
DECLARE_PMID(kScriptInfoIDSpace, kEPubHTMLExportOrderEnumScriptElement,			kEBookExportPrefix + 8)
DECLARE_PMID(kScriptInfoIDSpace, kExportOrderPropertyScriptElement,				kEBookExportPrefix + 9)
DECLARE_PMID(kScriptInfoIDSpace, kEPubCoverEnumScriptElement,					kEBookExportPrefix + 10)
DECLARE_PMID(kScriptInfoIDSpace, kEPubCoverPropertyScriptElement,				kEBookExportPrefix + 11)
DECLARE_PMID(kScriptInfoIDSpace, kCoverImagePathPropertyScriptElement,			kEBookExportPrefix + 12)
DECLARE_PMID(kScriptInfoIDSpace, kHTMLLeftMarginPropertyScriptElement,			kEBookExportPrefix + 13)
DECLARE_PMID(kScriptInfoIDSpace, kHTMLRightMarginPropertyScriptElement,			kEBookExportPrefix + 14)
DECLARE_PMID(kScriptInfoIDSpace, kHTMLTopMarginPropertyScriptElement,			kEBookExportPrefix + 15)
DECLARE_PMID(kScriptInfoIDSpace, kHTMLBottomMarginPropertyScriptElement,		kEBookExportPrefix + 16)
DECLARE_PMID(kScriptInfoIDSpace, kHTMLMarginUnitPropertyScriptElement,			kEBookExportPrefix + 17)
DECLARE_PMID(kScriptInfoIDSpace, kBulletListOptionEnumScriptElement,			kEBookExportPrefix + 18)
DECLARE_PMID(kScriptInfoIDSpace, kBulletExportOptionPropertyScriptElement,		kEBookExportPrefix + 19)
DECLARE_PMID(kScriptInfoIDSpace, kNumberedListOptionEnumScriptElement,			kEBookExportPrefix + 20)
DECLARE_PMID(kScriptInfoIDSpace, kNumberedListExportOptionPropertyScriptElement,kEBookExportPrefix + 21)
DECLARE_PMID(kScriptInfoIDSpace, kViewDocumentAfterExportPropertyScriptElement,	kEBookExportPrefix + 22)

// -- image panel
DECLARE_PMID(kScriptInfoIDSpace, kPreserveLayoutAppearencePropertyScriptElement,kEBookExportPrefix + 23)
DECLARE_PMID(kScriptInfoIDSpace, kPNGCompressionPropertyScriptElement,			kEBookExportPrefix + 24)
DECLARE_PMID(kScriptInfoIDSpace, kIgnorePIImageSettingsPropertyScriptElement,	kEBookExportPrefix + 25)
DECLARE_PMID(kScriptInfoIDSpace, kApplyImageASToAOPropertyScriptElement,		kEBookExportPrefix + 26)
DECLARE_PMID(kScriptInfoIDSpace, kUseOriginalImageScriptElement,				kEBookExportPrefix + 27)
DECLARE_PMID(kScriptInfoIDSpace, kUseExistingImageScriptElement,				kEBookExportPrefix + 28)

// -- content panel
DECLARE_PMID(kScriptInfoIDSpace, kEPubXHTMLFormatPropertyScriptElement,			kEBookExportPrefix + 35)
DECLARE_PMID(kScriptInfoIDSpace, kUseTOCStylePropertyScriptElement,				kEBookExportPrefix + 36)
DECLARE_PMID(kScriptInfoIDSpace, kEPubTOCStyleNamePropertyScriptElement,		kEBookExportPrefix + 37)
DECLARE_PMID(kScriptInfoIDSpace, kBreakDocumentPropertyScriptElement,			kEBookExportPrefix + 38)
DECLARE_PMID(kScriptInfoIDSpace, kBreakDocParaStyleNamePropertyScriptElement,	kEBookExportPrefix + 39)
DECLARE_PMID(kScriptInfoIDSpace, kFootnoteAfterParagraphPropertyScriptElement,	kEBookExportPrefix + 40)
DECLARE_PMID(kScriptInfoIDSpace, kStripSoftReturnPropertyScriptElement,			kEBookExportPrefix + 41)
DECLARE_PMID(kScriptInfoIDSpace, kEPubXHTMLCSSOptionEnumScriptElement,			kEBookExportPrefix + 42)
DECLARE_PMID(kScriptInfoIDSpace, kCSSOptionPropertyScriptElement,				kEBookExportPrefix + 43)
DECLARE_PMID(kScriptInfoIDSpace, kIncludeCSSDefinitionPropertyScriptElement,	kEBookExportPrefix + 44)
DECLARE_PMID(kScriptInfoIDSpace, kPreserveLocalOverridePropertyScriptElement,	kEBookExportPrefix + 45)
DECLARE_PMID(kScriptInfoIDSpace, kEmbedFontPropertyScriptElement,				kEBookExportPrefix + 46)
DECLARE_PMID(kScriptInfoIDSpace, kExternalCSSPathPropertyScriptElement,			kEBookExportPrefix + 47)
DECLARE_PMID(kScriptInfoIDSpace, kStyleSheetsPropertyScriptElement,				kEBookExportPrefix + 48)
DECLARE_PMID(kScriptInfoIDSpace, kJavascriptsPropertyScriptElement,				kEBookExportPrefix + 49)
DECLARE_PMID(kScriptInfoIDSpace, kEPubVersionEnumScriptElement,					kEBookExportPrefix + 50)
DECLARE_PMID(kScriptInfoIDSpace, kEPubVersionPropertyScriptElement,				kEBookExportPrefix + 51)
DECLARE_PMID(kScriptInfoIDSpace, kGenerateCSSPropertyScriptElement,				kEBookExportPrefix + 52)
DECLARE_PMID(kScriptInfoIDSpace, kIncludeClassesInHTMLPropertyScriptElement,	kEBookExportPrefix + 53)

// xhtml specific
DECLARE_PMID(kScriptInfoIDSpace, kHTMLExportSelectionPropertyScriptElement,		kEBookExportPrefix + 55)
DECLARE_PMID(kScriptInfoIDSpace, kImageExportOptionEnumScriptElement,			kEBookExportPrefix + 56)
DECLARE_PMID(kScriptInfoIDSpace, kImageExportOptionPropertyScriptElement,		kEBookExportPrefix + 57)
DECLARE_PMID(kScriptInfoIDSpace, kServerPathPropertyScriptElement,				kEBookExportPrefix + 58)
DECLARE_PMID(kScriptInfoIDSpace, kImageExtensionPropertyScriptElement,			kEBookExportPrefix + 59)
DECLARE_PMID(kScriptInfoIDSpace, kLinkToJavascriptPropertyScriptElement,		kEBookExportPrefix + 60)
DECLARE_PMID(kScriptInfoIDSpace, kJavascriptURLPropertyScriptElement,			kEBookExportPrefix + 61)
DECLARE_PMID(kScriptInfoIDSpace, kEPubFootnotePlacementPropertyScriptElement,	kEBookExportPrefix + 62)
DECLARE_PMID(kScriptInfoIDSpace, kEPubFootnotePlacementEnumScriptElement,		kEBookExportPrefix + 63)
DECLARE_PMID(kScriptInfoIDSpace, kEPubTitlePropertyScriptElement,				kEBookExportPrefix + 64)
DECLARE_PMID(kScriptInfoIDSpace, kEPubCreatorPropertyScriptElement,				kEBookExportPrefix + 65)
DECLARE_PMID(kScriptInfoIDSpace, kEPubDatePropertyScriptElement,				kEBookExportPrefix + 66)
DECLARE_PMID(kScriptInfoIDSpace, kEPubDescriptionPropertyScriptElement,			kEBookExportPrefix + 67)
DECLARE_PMID(kScriptInfoIDSpace, kEPubRightsPropertyScriptElement,				kEBookExportPrefix + 68)
DECLARE_PMID(kScriptInfoIDSpace, kEPubSubjectPropertyScriptElement,				kEBookExportPrefix + 69)
DECLARE_PMID(kScriptInfoIDSpace, kEPubExportFXLPrefsObjectScriptElement,		kEBookExportPrefix + 70)
DECLARE_PMID(kScriptInfoIDSpace, kEPubExportFXLPrefsPropertyScriptElement,		kEBookExportPrefix + 71)
DECLARE_PMID(kScriptInfoIDSpace, kEPubPageRangeFormatEnumScriptElement,			kEBookExportPrefix + 72)
DECLARE_PMID(kScriptInfoIDSpace, kEPubPageRangePropertyScriptElement,			kEBookExportPrefix + 73)
DECLARE_PMID(kScriptInfoIDSpace, kEPubPageRangeFormatPropertyScriptElement,		kEBookExportPrefix + 74)
DECLARE_PMID(kScriptInfoIDSpace, kEPubNavigationStyleEnumScriptElement,			kEBookExportPrefix + 75)
DECLARE_PMID(kScriptInfoIDSpace, kEPubNavigationStylePropertyScriptElement,		kEBookExportPrefix + 76)
DECLARE_PMID(kScriptInfoIDSpace, kEPubSpreadControlOptionEnumScriptElement,		kEBookExportPrefix + 77)
DECLARE_PMID(kScriptInfoIDSpace, kEPubSpreadControlOptionPropertyScriptElement,	kEBookExportPrefix + 78)
DECLARE_PMID(kScriptInfoIDSpace, kEPubViewingAppsPrefsMethodScriptElement,	kEBookExportPrefix + 81)
DECLARE_PMID(kScriptInfoIDSpace, kAppSelectedReflowScriptElement,	kEBookExportPrefix + 82)
DECLARE_PMID(kScriptInfoIDSpace, kApplicationNameScriptElement,	kEBookExportPrefix + 83)
DECLARE_PMID(kScriptInfoIDSpace, kCreateAppInfoMethodScriptElement,	kEBookExportPrefix + 86)
DECLARE_PMID(kScriptInfoIDSpace, kEPubViewingAppsPrefsObjectScriptElement,		kEBookExportPrefix + 87)
DECLARE_PMID(kScriptInfoIDSpace, kEPubViewingAppsPrefsPropertyScriptElement,	kEBookExportPrefix + 88)
DECLARE_PMID(kScriptInfoIDSpace, kAppSelectedFXLScriptElement,	kEBookExportPrefix + 90)
DECLARE_PMID(kScriptInfoIDSpace, kRemoveAppAtIndexMethodScriptElement,	kEBookExportPrefix + 91)
DECLARE_PMID(kScriptInfoIDSpace, kAppAtIndexMethodScriptElement,	kEBookExportPrefix + 92)
DECLARE_PMID(kScriptInfoIDSpace, kGetNoOfAppsMethodScriptElement,	kEBookExportPrefix + 93)
DECLARE_PMID(kScriptInfoIDSpace, kAppIndexScriptElement,	kEBookExportPrefix + 94)
DECLARE_PMID(kScriptInfoIDSpace, kHTMLExportFXLPrefsObjectScriptElement,           kEBookExportPrefix + 95)
DECLARE_PMID(kScriptInfoIDSpace, kHTMLExportFXLPrefsPropertyScriptElement,         kEBookExportPrefix + 96)
DECLARE_PMID(kScriptInfoIDSpace, kPublishPrefsObjectScriptElement,         		kEBookExportPrefix + 97)
DECLARE_PMID(kScriptInfoIDSpace, kPublishPrefsPropertyScriptElement,         	kEBookExportPrefix + 98)
DECLARE_PMID(kScriptInfoIDSpace, kPublishTitlePropertyScriptElement,         	kEBookExportPrefix + 99)
DECLARE_PMID(kScriptInfoIDSpace, kPublishDescriptionPropertyScriptElement,		kEBookExportPrefix + 100)
DECLARE_PMID(kScriptInfoIDSpace, kPublishFormatEnumScriptElement		 ,		kEBookExportPrefix + 101)
//DECLARE_PMID(kScriptInfoIDSpace, kDownloadPermissionPropertyScriptElement,		kEBookExportPrefix + 102)
DECLARE_PMID(kScriptInfoIDSpace, kExportFormatPropertyScriptElement		 ,		kEBookExportPrefix + 103)
DECLARE_PMID(kScriptInfoIDSpace, kPublishCoverPropertyScriptElement,			kEBookExportPrefix + 104)
DECLARE_PMID(kScriptInfoIDSpace, kPublishPageRangeFormatPropertyScriptElement,	kEBookExportPrefix + 106)
DECLARE_PMID(kScriptInfoIDSpace, kPublishPageRangePropertyScriptElement,		kEBookExportPrefix + 107)
DECLARE_PMID(kScriptInfoIDSpace, kPublishFileNamePropertyScriptElement,			kEBookExportPrefix + 108)
DECLARE_PMID(kScriptInfoIDSpace, kPublishCoverEnumScriptElement,				kEBookExportPrefix + 109)
DECLARE_PMID(kScriptInfoIDSpace, kPublishCoverPagePropertyScriptElement,		kEBookExportPrefix + 110)
DECLARE_PMID(kScriptInfoIDSpace, kPublishPDFRequiredPropertyScriptElement,		kEBookExportPrefix + 111)	


//GUIDS 

// {DEFAFCF5-B9A4-4024-B557-CEA5DBFAB7B2}
#define  kEPubExportPref_CLSID { 0xdefafcf5, 0xb9a4, 0x4024, { 0xb5, 0x57, 0xce, 0xa5, 0xdb, 0xfa, 0xb7, 0xb2 } }
// {C677E37B-05A0-4ce9-876C-FD9D289027BA}
#define kHTMLExportPref_CLSID { 0xc677e37b, 0x5a0, 0x4ce9, { 0x87, 0x6c, 0xfd, 0x9d, 0x28, 0x90, 0x27, 0xba } }
// {7AA934A0-5466-4BA1-B16F-26942974AD7D}
#define kEPubExportFXLPref_CLSID {0x7aa934a0, 0x5466, 0x4ba1, { 0xb1, 0x6f, 0x26, 0x94, 0x29, 0x74, 0xad, 0x7d } }
// {2743E6D2-BB9A-4DB5-B2E7-6806A95E36CF}
#define kEPubViewingAppsPref_CLSID {0x2743e6d2, 0xbb9a, 0x4db5, { 0xb2, 0xe7, 0x68, 0x6, 0xa9, 0x5e, 0x36, 0xcf } }
// {2AA600B3-D906-44B5-B984-28F336E938FC}
#define kHTMLExportFXLPref_CLSID { 0x2aa600b3, 0xd906, 0x44b5, { 0xb9, 0x84, 0x28, 0xf3, 0x36, 0xe9, 0x38, 0xfc } }
// {C086A280-7D83-4B59-908C-D8EB20C513E3}
#define  kPublishPref_CLSID		{0xc086a280, 0x7d83, 0x4b59, {0x90, 0x8c, 0xd8, 0xeb, 0x20, 0xc5, 0x13, 0xe3} }
#endif	// __EbookExportID__

