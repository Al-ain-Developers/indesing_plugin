//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/HTMLPGTID.h $
//  
//  Owner: Matt Phillips
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

#ifndef __HTMLPGTID__
#define __HTMLPGTID__

// ----- Includes -----

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kHTMLPGTPrefix 						RezLong( 0x22100 )

//----------------------------------------------------------------------------------------
//
// PluginID
//

#define kHTMLPGTPluginName 					"HTMLPGT"
DECLARE_PMID(kPlugInIDSpace, kHTMLPGTPluginID, kHTMLPGTPrefix + 1)

// <Start IDC>
// <Class ID>
//----------------------------------------------------------------------------------------
//
// Boss ids
//

//DECLARE_PMID(kClassIDSpace, kHTMLPGTExportCmdBoss,					kHTMLPGTPrefix + 1)
DECLARE_PMID(kClassIDSpace, kHTMLPGTExportPrefsScriptProviderBoss,	kHTMLPGTPrefix + 2)
DECLARE_PMID(kClassIDSpace, kSetHTMLPGTExportPrefsCmdBoss,			kHTMLPGTPrefix + 3)
DECLARE_PMID(kClassIDSpace, kHTMLPGTExportBoss,						kHTMLPGTPrefix + 4)
DECLARE_PMID(kClassIDSpace, kHTMLPGTErrorStringServiceBoss,			kHTMLPGTPrefix + 5)
DECLARE_PMID(kClassIDSpace, kHTMLPGTStartupBoss,					kHTMLPGTPrefix + 6)
DECLARE_PMID(kClassIDSpace, kHTMLPGTExportServiceBoss,				kHTMLPGTPrefix + 7)
DECLARE_PMID(kClassIDSpace, kHTMLPageItemBoss,						kHTMLPGTPrefix + 8)
DECLARE_PMID(kClassIDSpace, kNewHTMLPageItemCmdBoss,				kHTMLPGTPrefix + 9)
DECLARE_PMID(kClassIDSpace, kHTMLImportProviderBoss,				kHTMLPGTPrefix + 10)
DECLARE_PMID(kClassIDSpace, kNewHTMLPosterCmdBoss,					kHTMLPGTPrefix + 11)
DECLARE_PMID(kClassIDSpace, kHTMLItemScriptProviderBoss,			kHTMLPGTPrefix + 12)
DECLARE_PMID(kClassIDSpace, kSetHTMLContentCmdBoss,					kHTMLPGTPrefix + 13)
DECLARE_PMID(kClassIDSpace, kHTMLWebServiceBoss,					kHTMLPGTPrefix + 14)
DECLARE_PMID(kClassIDSpace, kPGTEHBaseBoss,							kHTMLPGTPrefix + 15)
DECLARE_PMID(kClassIDSpace, kPGTEHLayoutAndPageBuilderBoss,			kHTMLPGTPrefix + 16)
DECLARE_PMID(kClassIDSpace, kPGTEHCalculateRegionPositionBoss,		kHTMLPGTPrefix + 17)
DECLARE_PMID(kClassIDSpace, kPGTEHNoRegionsHandlerBoss,				kHTMLPGTPrefix + 18)
DECLARE_PMID(kClassIDSpace, kPGTEHFormFieldHandlerBoss,				kHTMLPGTPrefix + 19)
DECLARE_PMID(kClassIDSpace, kPGTEHSVGRenderedFrameHandlerBoss,		kHTMLPGTPrefix + 20)
DECLARE_PMID(kClassIDSpace, kPGTEHGroupHandlerBoss,					kHTMLPGTPrefix + 21)
//obsolete (PGT) DECLARE_PMID(kClassIDSpace, kPGTEHInteractivityHandlerBoss,			kHTMLPGTPrefix + 22)
DECLARE_PMID(kClassIDSpace, kPGTEHInteractivityPGT2HandlerBoss,		kHTMLPGTPrefix + 23)
DECLARE_PMID(kClassIDSpace, kPGTEHPageItemListBuilderBoss,			kHTMLPGTPrefix + 24)
DECLARE_PMID(kClassIDSpace, kPGTEHDefaultFrameHandlerBoss,			kHTMLPGTPrefix + 25)
DECLARE_PMID(kClassIDSpace, kPGTEHGenericGraphicPropertiesBoss,		kHTMLPGTPrefix + 26)
DECLARE_PMID(kClassIDSpace, kPGTEHReorderFramesForFlowBoss,			kHTMLPGTPrefix + 27)
DECLARE_PMID(kClassIDSpace, kPGTEHImageFrameHandlerBoss,			kHTMLPGTPrefix + 28)
DECLARE_PMID(kClassIDSpace, kPGTEHTextFrameHandlerBoss,				kHTMLPGTPrefix + 29)
DECLARE_PMID(kClassIDSpace, kPGTEHTextWrapPropertiesBoss,			kHTMLPGTPrefix + 30)
DECLARE_PMID(kClassIDSpace, kPGTEHGenericRegionCreatorBoss,			kHTMLPGTPrefix + 31)
DECLARE_PMID(kClassIDSpace, kPGTEHMediaFrameHandlerBoss,			kHTMLPGTPrefix + 32)
DECLARE_PMID(kClassIDSpace, kPGTEHHTMLPageItemHandlerBoss,			kHTMLPGTPrefix + 33)
DECLARE_PMID(kClassIDSpace, kPGTEHDefaultSectionsGeneratorBoss,		kHTMLPGTPrefix + 34)
DECLARE_PMID(kClassIDSpace, kHTMLPGTConversionProviderBoss,			kHTMLPGTPrefix + 35)
DECLARE_PMID(kClassIDSpace, kPGTEHPageRegionCreatorBoss,			kHTMLPGTPrefix + 36)
DECLARE_PMID(kClassIDSpace, kHTMLPGTRuleServiceBoss,				kHTMLPGTPrefix + 37)
DECLARE_PMID(kClassIDSpace, kRenderedThreadedTextRuleBoss,			kHTMLPGTPrefix + 38)
DECLARE_PMID(kClassIDSpace, kDigPubProfilePrelightStartupResponderBoss,kHTMLPGTPrefix + 39)
DECLARE_PMID(kClassIDSpace, kSetupDigPubProfileCmdBoss,				kHTMLPGTPrefix + 40)
DECLARE_PMID(kClassIDSpace, kPGTEHConfigureViewportBoss,			kHTMLPGTPrefix + 41)

// <Interface ID>
//----------------------------------------------------------------------------------------
//
// Interface ids
//

DECLARE_PMID(kInterfaceIDSpace, IID_IHTMLPGTEXPORT	,				kHTMLPGTPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IHTMLPGTEXPORTPREFS,			kHTMLPGTPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IPGTMANAGER,					kHTMLPGTPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IHTMLPAGEITEMFACADE,			kHTMLPGTPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IHTMLPAGEITEMSUITE,				kHTMLPGTPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IHTMLSTRINGDATA,				kHTMLPGTPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IHTMLWEBSERVER,					kHTMLPGTPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IPGTPORT,						kHTMLPGTPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IPGTEXPORTHANDLER,				kHTMLPGTPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IDPSPGTEXTENSIONS,				kHTMLPGTPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IHTMLPAGEITEMATTRIBUTES,		kHTMLPGTPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IPGTUTILS,						kHTMLPGTPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IDIGPUBPROFILEUTILS,			kHTMLPGTPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IBOOLDATA_RESIZEFRAME_TO_FIT_CONTENT, kHTMLPGTPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IPGTPAGESURVEYOR,				kHTMLPGTPrefix + 15)

// <Implementation ID>
//----------------------------------------------------------------------------------------
//
// Implementation ids
//

DECLARE_PMID(kImplementationIDSpace, kHTMLPGTExportPrefsScriptProviderImpl,		kHTMLPGTPrefix + 1)
//DECLARE_PMID(kImplementationIDSpace, kHTMLPGTExportCmdImpl,						kHTMLPGTPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kHTMLPGTExportImpl,						kHTMLPGTPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kHTMLPGTExportPrefsImpl,					kHTMLPGTPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kHTMLPGTExportSetupServiceImpl,			kHTMLPGTPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kHTMLPGTExportProviderImpl,				kHTMLPGTPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kHTMLPGTStartupServiceImpl,				kHTMLPGTPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kHTMLPGTStartupShutdownImpl,				kHTMLPGTPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kPGTManagerImpl,							kHTMLPGTPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kSetHTMLPGTExportPrefsCmdImpl,				kHTMLPGTPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kHTMLPageItemShapeImpl,					kHTMLPGTPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kHTMLStringDataImpl,						kHTMLPGTPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kNewHTMLPageItemCmdImpl,					kHTMLPGTPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kNewHTMLPosterCmdImpl,						kHTMLPGTPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kHTMLPageItemFacadeImpl,					kHTMLPGTPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kHTMLPageItemScriptProviderImpl,			kHTMLPGTPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kSetHTMLContentCmdImpl,					kHTMLPGTPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kHTMLItemVisitorHelperImpl,				kHTMLPGTPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kHTMLPageItemSuiteASBImpl,					kHTMLPGTPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kHTMLPageItemSuiteASBSelExtImpl,			kHTMLPGTPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kHTMLPageItemSuiteLayoutCSBImpl,			kHTMLPGTPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kHTMLPageItemSuiteLayoutCSBSelExtImpl,		kHTMLPGTPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kHTMLPageItemSuiteDefaultCSBImpl,			kHTMLPGTPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kHTMLWebServerServiceImpl,					kHTMLPGTPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kHTMLWebServerImpl,						kHTMLPGTPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kPGTPortImpl,								kHTMLPGTPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kPGTExportHandlerServiceImpl,				kHTMLPGTPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kPGTEHLayoutAndPageBuilderImpl,			kHTMLPGTPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kPGTEHCalculateRegionPositionImpl,			kHTMLPGTPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kPGTEHNoRegionsHandlerImpl,				kHTMLPGTPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kPGTEHFormFieldHandlerImpl,				kHTMLPGTPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kPGTEHSVGRenderedFrameHandlerImpl,			kHTMLPGTPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kPGTEHGroupHandlerImpl,					kHTMLPGTPrefix + 43)
//obsolete (PGT) DECLARE_PMID(kImplementationIDSpace, kPGTEHInteractivityHandlerImpl,			kHTMLPGTPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kPGTEHInteractivityPGT2HandlerImpl,		kHTMLPGTPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kPGTEHPageItemListBuilderImpl,				kHTMLPGTPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kPGTEHDefaultFrameHandlerImpl,				kHTMLPGTPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kPGTEHGenericGraphicPropertiesImpl,		kHTMLPGTPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kPGTEHReorderFramesForFlowImpl,			kHTMLPGTPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kPGTEHImageFrameHandlerImpl,				kHTMLPGTPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kPGTEHTextFrameHandlerImpl,				kHTMLPGTPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kPGTEHTextWrapPropertiesImpl,				kHTMLPGTPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kPGTEHGenericRegionCreatorImpl,			kHTMLPGTPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kPGTEHMediaFrameHandlerImpl,				kHTMLPGTPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kHTMLImportProviderImpl,					kHTMLPGTPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kHTMLPlaceBehaviorImpl,					kHTMLPGTPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kPGTEHHTMLPageItemHandlerImpl,				kHTMLPGTPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kPGTEHDefaultSectionsGeneratorImpl,		kHTMLPGTPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kHTMLPageItemAttributesImpl,				kHTMLPGTPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kPGTEHPageRegionCreatorImpl,				kHTMLPGTPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kPGTUtilsImpl,								kHTMLPGTPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kHTMLPGTRuleServiceImpl,					kHTMLPGTPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kRenderedThreadedTextRuleImpl,				kHTMLPGTPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kRenderedThreadedTextRuleUIImpl,			kHTMLPGTPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kDigPubProfilePrelightStartupResponderImpl,kHTMLPGTPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kDigPubProfileUtilsImpl,					kHTMLPGTPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kSetupDigPubProfileCmdImpl,				kHTMLPGTPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kPGTEHConfigureViewportImpl,				kHTMLPGTPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kHTMLPageItemHierarchyImpl,				kHTMLPGTPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kHTMLPGTErrorStringServiceImpl,			kHTMLPGTPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kPGTPageSurveyorImpl,						kHTMLPGTPrefix + 71)


//----------------------------------------------------------------------------------------
// Widget ids
//

//DECLARE_PMID(kWidgetIDSpace, kHTMLPGTExportMainDlgWidgetID, kHTMLPGTPrefix + 1)


//----------------------------------------------------------------------------------------
//
// Service IDs

DECLARE_PMID(kServiceIDSpace, kHTMLPGTExportSetupService,						kHTMLPGTPrefix + 1)
DECLARE_PMID(kServiceIDSpace, kHTMLWebServerService,							kHTMLPGTPrefix + 2)
DECLARE_PMID(kServiceIDSpace, kPGTExportHandlerService,							kHTMLPGTPrefix + 3)


// <Error ID>
//----------------------------------------------------------------------------------------
//
// Error Codes

DECLARE_PMID(kErrorIDSpace, kInvalidAlternateFlowsInLayoutErrorID,				kHTMLPGTPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kNoEligibleExpansionPageForLayoutErrorID,			kHTMLPGTPrefix + 2)

//----------------------------------------------------------------------------------------
//
//Script Element IDs
//
//DECLARE_PMID(kScriptInfoIDSpace, kHTMLPGTExportPrefsObjectScriptElement,			kHTMLPGTPrefix + 1)
//DECLARE_PMID(kScriptInfoIDSpace, kHTMLPGTExportPrefsPropertyScriptElement,			kHTMLPGTPrefix + 2)
DECLARE_PMID(kScriptInfoIDSpace, kHTMLObjectScriptElement,							kHTMLPGTPrefix + 3)
DECLARE_PMID(kScriptInfoIDSpace, kHTMLContentPropertyScriptElement,					kHTMLPGTPrefix + 4) 
DECLARE_PMID(kScriptInfoIDSpace, kHTMLPosterPropertyScriptElement,					kHTMLPGTPrefix + 5) 
DECLARE_PMID(kScriptInfoIDSpace, kINXImportClassPolicy80MetadataScriptElement,		kHTMLPGTPrefix + 6) 
//DECLARE_PMID(kScriptInfoIDSpace, kRootScriptPathPropertyScriptElement,				kHTMLPGTPrefix + 7)
//DECLARE_PMID(kScriptInfoIDSpace, kCopyStdPGTScriptPropertyScriptElement,			kHTMLPGTPrefix + 8)
DECLARE_PMID(kScriptInfoIDSpace, kHTMLFixedDimensionsPropertyScriptElement,			kHTMLPGTPrefix + 9) 
DECLARE_PMID(kScriptInfoIDSpace, kHTMLRelativePathPropertyScriptElement,			kHTMLPGTPrefix + 10) 

//GUIDS 
// {806004AF-8AC3-4ddf-825C-99143B5E67DE}
#define  kHTMLPGTExportPref_CLSID { 0x806004af, 0x8ac3, 0x4ddf, { 0x82, 0x5c, 0x99, 0x14, 0x3b, 0x5e, 0x67, 0xde } }
// {F10255C1-BA33-4794-BEA5-2599703A7DE3}
#define kHTMLPageItem_CLSID { 0xf10255c1, 0xba33, 0x4794, { 0xbe, 0xa5, 0x25, 0x99, 0x70, 0x3a, 0x7d, 0xe3} }
// {6F8FE2A9-3DC8-4964-B6FC-E9885A33C12E}
#define kHTMLPageItems_CLSID { 0x6f8fe2a9, 0x3dc8, 0x4964, { 0xb6, 0xfc, 0xe9, 0x88, 0x5a, 0x33, 0xc1, 0x2e } }

#endif // __HTMLPGTID__



