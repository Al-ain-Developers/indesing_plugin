//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/GradientFillID.h $
//  
//  Owner: Thanh Nguyen
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
//  Contains IDs used by the gradient fill plug-in
//  
//========================================================================================

#ifndef __GradientFillID__
#define __GradientFillID__

#include "IDFactory.h"
#include "CrossPlatformTypes.h"


#define kGradientFillPrefix	RezLong(0x5500)


// <Start IDC>
// PluginID
#define kGradientFillPluginName 		"Gradient Fill"
DECLARE_PMID(kPlugInIDSpace, kGradientFillPluginID, kGradientFillPrefix + 1)

// <Class ID>
// ClassIDs
//	Gap
DECLARE_PMID(kClassIDSpace, kGradientFillTestMenuBoss, kGradientFillPrefix + 2)
DECLARE_PMID(kClassIDSpace, kGradientRenderingObjectBoss, kGradientFillPrefix + 3)
DECLARE_PMID(kClassIDSpace, kGradientFillRefConverterBoss, kGradientFillPrefix + 4)
DECLARE_PMID(kClassIDSpace, kNewGradientFillCmdBoss, kGradientFillPrefix + 5)
DECLARE_PMID(kClassIDSpace, kGradientMetaDataBoss_Obsolete, kGradientFillPrefix + 6)
DECLARE_PMID(kClassIDSpace, kDeleteGradientFillCmdBoss, kGradientFillPrefix	+ 7)
DECLARE_PMID(kClassIDSpace, kChangeGradientCmdBoss, kGradientFillPrefix + 8)
DECLARE_PMID(kClassIDSpace, kGradientRIDXNotifierHandlerBoss, kGradientFillPrefix + 9)
DECLARE_PMID(kClassIDSpace, kGradientRenderProviderBoss, kGradientFillPrefix + 10)
//gap
DECLARE_PMID(kClassIDSpace, kSetGradientAttributeCmdBoss, kGradientFillPrefix + 12)
DECLARE_PMID(kClassIDSpace, kGradGfxStateStartupShutdownBoss, kGradientFillPrefix + 13)
DECLARE_PMID(kClassIDSpace, kGradientConversionBoss_obsolete, kGradientFillPrefix + 14)
//gap
DECLARE_PMID(kClassIDSpace, kGraphicStyleGradientFillAngleAttrBoss, kGradientFillPrefix +30)
DECLARE_PMID(kClassIDSpace, kGraphicStyleGradientFillLengthAttrBoss, kGradientFillPrefix +31)
DECLARE_PMID(kClassIDSpace, kGraphicStyleGradientFillGradCenterAttrBoss, kGradientFillPrefix +32)
DECLARE_PMID(kClassIDSpace, kGraphicStyleGradientFillRadiusAttrBoss, kGradientFillPrefix +33)
DECLARE_PMID(kClassIDSpace, kGraphicStyleGradientFillHiliteLengthAttrBoss, kGradientFillPrefix + 34)
DECLARE_PMID(kClassIDSpace, kGraphicStyleGradientFillHiliteAngleAttrBoss, kGradientFillPrefix + 35)
DECLARE_PMID(kClassIDSpace, kGraphicStyleGradientStrokeAngleAttrBoss, kGradientFillPrefix +36)
DECLARE_PMID(kClassIDSpace, kGraphicStyleGradientStrokeLengthAttrBoss, kGradientFillPrefix +37)
DECLARE_PMID(kClassIDSpace, kGraphicStyleGradientStrokeGradCenterAttrBoss, kGradientFillPrefix +38)
DECLARE_PMID(kClassIDSpace, kGraphicStyleGradientStrokeRadiusAttrBoss, kGradientFillPrefix +39)
DECLARE_PMID(kClassIDSpace, kGraphicStyleGradientStrokeHiliteLengthAttrBoss, kGradientFillPrefix + 40)
DECLARE_PMID(kClassIDSpace, kGraphicStyleGradientStrokeHiliteAngleAttrBoss, kGradientFillPrefix + 41)
//DECLARE_PMID(kClassIDSpace, kGradientRenderingObjSuiteBoss, kGradientFillPrefix + 42  )
//DECLARE_PMID(kClassIDSpace, kGradientFillLayoutActionBoss, kGradientFillPrefix + 43)
DECLARE_PMID(kClassIDSpace, kGradientConversionProviderBoss, kGradientFillPrefix + 44)
DECLARE_PMID(kClassIDSpace, kGradientFillIteratorRegBoss, kGradientFillPrefix + 45)
//DECLARE_PMID(kClassIDSpace, kGradientSuiteRegisterBoss, kGradientFillPrefix + 46)
DECLARE_PMID(kClassIDSpace, kGradientScriptProviderBoss, kGradientFillPrefix + 47)
DECLARE_PMID(kClassIDSpace, kGradStopScriptProviderBoss, kGradientFillPrefix + 48)
DECLARE_PMID(kClassIDSpace, kGradStopScriptObjectBoss, kGradientFillPrefix + 49)
DECLARE_PMID(kClassIDSpace, kGradientPhase2ConversionResponderBoss, kGradientFillPrefix + 50)
DECLARE_PMID(kClassIDSpace, kAGMBlackBoxRenderingObjectBoss, kGradientFillPrefix + 51)
DECLARE_PMID(kClassIDSpace, kAGMMetaDataObjectBoss_Obsolete, kGradientFillPrefix + 52)
DECLARE_PMID(kClassIDSpace, kNewAGMBlackBoxFillCmdBoss, kGradientFillPrefix + 53)
DECLARE_PMID(kClassIDSpace, kAGMBlackBoxRenderProviderBoss, kGradientFillPrefix + 54)
DECLARE_PMID(kClassIDSpace, kAGMBlackBoxRefConverterBoss, kGradientFillPrefix + 55)
DECLARE_PMID(kClassIDSpace, kDeleteAGMBlackBoxFillCmdBoss, kGradientFillPrefix + 56)
DECLARE_PMID(kClassIDSpace, kDeleteBlackBoxInksCmdBoss,   kGradientFillPrefix + 57) 
DECLARE_PMID(kClassIDSpace, kGradientBlackBoxConversionProviderBoss, kGradientFillPrefix + 58) 
DECLARE_PMID(kClassIDSpace, kAGMBlackBoxScriptProviderBoss, kGradientFillPrefix + 59) 
DECLARE_PMID(kClassIDSpace, kAGMBlackBoxModifyFromScriptCmdBoss, kGradientFillPrefix + 60) 
DECLARE_PMID(kClassIDSpace, kGradientFillGraphicsAttrBoss, kGradientFillPrefix + 61) 
DECLARE_PMID(kClassIDSpace, kGradientStrokeGraphicsAttrBoss, kGradientFillPrefix + 62) 
DECLARE_PMID(kClassIDSpace, kGraphicStyleGradientAspectRatioAttrBoss, kGradientFillPrefix + 63)
// <Interface ID>
// PM IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IGRADIENTFILL, kGradientFillPrefix + 1)
//DECLARE_PMID(kInterfaceIDSpace, gap, kGradientFillPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRADIENTFILLINSTALL, kGradientFillPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRADIENTMETADATA_OBSOLETE, kGradientFillPrefix + 4)
//DECLARE_PMID(kInterfaceIDSpace, gap, kGradientFillPrefix + 5)
//DECLARE_PMID(kInterfaceIDSpace, gap, kGradientFillPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETGRADIENTATTRIBUTEDATA, kGradientFillPrefix + 7)
//DECLARE_PMID(kInterfaceIDSpace, IID_IGRADGRAPHICSTATEOBSERVER, kGradientFillPrefix + 8)
//DECLARE_PMID(kInterfaceIDSpace, IID_IGRADFILLGFXSTATEDATA, kGradientFillPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRADIENTFILLDOCOBSERVER, kGradientFillPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRIVATEGRADIENTCACHE, kGradientFillPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRADIENTATTRIBUTESUITE, kGradientFillPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IAGMBLACKBOXPAINTDATA, kGradientFillPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IAGMMODIFYFROMSCRIPTPAINTDATA, kGradientFillPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRADIENTFILLPRIVATEUTILS, kGradientFillPrefix + 15)

// <Implementation ID>
// ImplementationIIDs
//DECLARE_PMID(kImplementationIDSpace, kSetGradientFillCmdImpl, kGradientFillPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kGradientFillTestMenuImpl, kGradientFillPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kGradientFillImpl, kGradientFillPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kGradientFillInstallImpl, kGradientFillPrefix	+ 4)
DECLARE_PMID(kImplementationIDSpace, kGradientRenderingObjectImpl, kGradientFillPrefix	+ 5)
DECLARE_PMID(kImplementationIDSpace, kGradientFillRefConverterImpl, kGradientFillPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kNewGradientFillCmdImpl, kGradientFillPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kGradientMetaDataImpl_Obsolete, kGradientFillPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kDeleteGradientFillCmdImpl, kGradientFillPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kGradMetaDataRenderingObjectImpl_Obsolete, kGradientFillPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kChangeGradientCmdImpl, kGradientFillPrefix + 11 )
DECLARE_PMID(kImplementationIDSpace, kAGMGradientCacheImpl, kGradientFillPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kGradientRIDXNotifierHandlerImpl, kGradientFillPrefix + 13)
//gap
DECLARE_PMID(kImplementationIDSpace, kGradFillConversionImpl_obsolete, kGradientFillPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kGradGfxStateServiceProviderImpl, kGradientFillPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kGradGfxStateStartupShutdownImpl, kGradientFillPrefix + 20)
//DECLARE_PMID(kImplementationIDSpace, kGradFillGfxStateObserverImpl, kGradientFillPrefix + 21)
//DECLARE_PMID(kImplementationIDSpace, kGradFillGraphicStateDataImpl, kGradientFillPrefix + 22)
//DECLARE_PMID(kImplementationIDSpace, kGradientRenderingObjSuiteImpl, kGradientFillPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kGradientSwatchReferenceDataImpl, kGradientFillPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kGradientInkResourcesImpl, kGradientFillPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kGradRenderObjApplyActionImpl, kGradientFillPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kGradientFillLayoutActionImpl, kGradientFillPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kGradientFillDocObserverImpl, kGradientFillPrefix + 27)
//DECLARE_PMID(kImplementationIDSpace, kGradFillSpreadObserverImpl, kGradientFillPrefix + 28)
//DECLARE_PMID(kImplementationIDSpace, kGradPanelSelectionObserverImpl, kGradientFillPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kGradientMetaDataObjectImpl_Obsolete, kGradientFillPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kGradientFillIteratorRegImpl, kGradientFillPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kGradientAttrSuiteASBImpl, kGradientFillPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kGradientAttrSuiteDefaultCSBImpl, kGradientFillPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kGradientAttrSuiteLayoutCSBImpl, kGradientFillPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kGradientAttrSuiteTextCSBImpl, kGradientFillPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kGradientAttrSuiteTableCSBImpl, kGradientFillPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kGradientAttrSuiteASBExtImpl, kGradientFillPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kGradientAttrSuiteDefaultSelectionExtImpl, kGradientFillPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kGradientAttrSuiteLayoutSelectionExtImpl, kGradientFillPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kGradientAttrSuiteTextSelectionExtImpl, kGradientFillPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kGradientAttrSuiteTableSelectionExtImpl, kGradientFillPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kGradientScriptProviderImpl, kGradientFillPrefix + 42)
//gap
DECLARE_PMID(kImplementationIDSpace, kGradStopScriptProviderImpl, kGradientFillPrefix + 44)
//gap
DECLARE_PMID(kImplementationIDSpace, kGradStopScriptImpl, kGradientFillPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kGradientPhase2ConversionImpl,           kGradientFillPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kAGMBlackBoxRenderingObjectImpl,         kGradientFillPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kAGMBlackBoxPaintDataImpl,               kGradientFillPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kAGMBlackBoxPaintInkResourcesImpl,       kGradientFillPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kAGMBlackBoxPaintSwatchReferenceDataImpl,     kGradientFillPrefix + 52)
//DECLARE_PMID(kImplementationIDSpace, kAGMBlackBoxPaintRenderObjSuiteImpl,     kGradientFillPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kAGMBlackBoxRenderObjApplyActionImpl,    kGradientFillPrefix + 53)
//DECLARE_PMID(kImplementationIDSpace, kAGMBlackBoxMetaDataConverterImpl_Obsolete, kGradientFillPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kNewAGMBlackBoxFillCmdImpl,              kGradientFillPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kAGMBlackBoxMetaDataObjectImpl_Obsolete, kGradientFillPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kAGMBlackBoxRefConverterImpl,            kGradientFillPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kAGMBlackBoxRenderingObjectUIImpl,       kGradientFillPrefix + 59) 
DECLARE_PMID(kImplementationIDSpace, kDeleteAGMBlackBoxCmdImpl,               kGradientFillPrefix + 60) 
DECLARE_PMID(kImplementationIDSpace, kDeleteBlackBoxInksCmdImpl,              kGradientFillPrefix + 61) 
DECLARE_PMID(kImplementationIDSpace, kAGMBlackBoxConversionImpl,              kGradientFillPrefix + 62) 
DECLARE_PMID(kImplementationIDSpace, kGradientRenderObjectServiceImpl,        kGradientFillPrefix + 63) 
DECLARE_PMID(kImplementationIDSpace, kAGMBlackBoxRenderObjectServiceImpl,     kGradientFillPrefix + 64) 
//gap
DECLARE_PMID(kImplementationIDSpace, kAGMBlackBoxScriptProviderImpl,          kGradientFillPrefix + 66) 
DECLARE_PMID(kImplementationIDSpace, kAGMBlackBoxModifyFromScriptCmdDataImpl, kGradientFillPrefix + 67) 
DECLARE_PMID(kImplementationIDSpace, kAGMBlackBoxModifyFromScriptCmdImpl,     kGradientFillPrefix + 68) 
// gap
DECLARE_PMID(kImplementationIDSpace, kGradFillGraphicsAttrInfoImpl,     kGradientFillPrefix + 70) 
DECLARE_PMID(kImplementationIDSpace, kGradStrokeGraphicsAttrInfoImpl,                 kGradientFillPrefix + 71) 
DECLARE_PMID(kImplementationIDSpace, kGradientFillPrivateUtilsImpl,				kGradientFillPrefix + 72) 

// <Widget ID>
DECLARE_PMID(kWidgetIDSpace, kReplaceBlackBoxSpotAlertWidgetID, kGradientFillPrefix + 1)

//
//Script Element IDs
//

//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kGradientObjectScriptElement,				kGradientFillPrefix + 45)
DECLARE_PMID(kScriptInfoIDSpace, kGradStopObjectScriptElement,				kGradientFillPrefix + 46)
DECLARE_PMID(kScriptInfoIDSpace, kAGMBlackBoxObjectScriptElement,           kGradientFillPrefix + 47)

//Events

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kGradientTypePropertyScriptElement,		kGradientFillPrefix + 162)
DECLARE_PMID(kScriptInfoIDSpace, kStopColorPropertyScriptElement,			kGradientFillPrefix + 163)
DECLARE_PMID(kScriptInfoIDSpace, kStopPositionPropertyScriptElement,		kGradientFillPrefix + 164)
DECLARE_PMID(kScriptInfoIDSpace, kMidPointPropertyScriptElement,			kGradientFillPrefix + 165)
DECLARE_PMID(kScriptInfoIDSpace, kSpotListPropertyScriptElement,            kGradientFillPrefix + 166)
DECLARE_PMID(kScriptInfoIDSpace, kAGMBlackBoxContentsScriptElement,         kGradientFillPrefix + 167)
DECLARE_PMID(kScriptInfoIDSpace, kAGMBlackBoxTypeScriptElement,             kGradientFillPrefix + 168)
DECLARE_PMID(kScriptInfoIDSpace, kAGMBlackBoxVersionScriptElement,          kGradientFillPrefix + 169)
DECLARE_PMID(kScriptInfoIDSpace, kAGMBlackBoxMatrixScriptElement,           kGradientFillPrefix + 170)
DECLARE_PMID(kScriptInfoIDSpace, kAGMBlackBoxEncodingScriptElement,         kGradientFillPrefix + 171)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kGradientTypeEnumScriptElement,			kGradientFillPrefix + 220)
DECLARE_PMID(kScriptInfoIDSpace, kBinaryBlobEncodingTypeEnum,               kGradientFillPrefix + 221)
DECLARE_PMID(kScriptInfoIDSpace, kAGMBlackBoxTypeScriptElementEnum,         kGradientFillPrefix + 222)


#endif // __GradientFillID__




