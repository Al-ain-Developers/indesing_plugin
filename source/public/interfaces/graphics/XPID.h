//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/XPID.h $
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
//  
//  Description: IDs for the transparency plugin.
//  
//========================================================================================

#ifndef __XPID__
#define __XPID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kXPPrefix	 		RezLong(0x10800)		//Refer also to AdobePrefix.h
#define kXPPrefix2	 		RezLong(0x1EB00)		//Refer also to AdobePrefix.h

// <Start IDC>
// PluginID
#define kXPPluginName 							"Transparency"
DECLARE_PMID(kPlugInIDSpace, kXPPluginID, (kXPPrefix + 1))

// Conversion
// For pub conversion constants see XPConversionID.h

// <Class ID>
// ClassIDs (i.e. bosses)
DECLARE_PMID(kClassIDSpace, kXPDrwEvtHandlerBoss, kXPPrefix + 1)
DECLARE_PMID(kClassIDSpace, kXPTestMenuBoss, kXPPrefix + 2)
DECLARE_PMID(kClassIDSpace, kXPWaxRunShadowBoss, kXPPrefix + 3)
DECLARE_PMID(kClassIDSpace, kXPDropShadowTABoss, kXPPrefix + 4)
DECLARE_PMID(kClassIDSpace, kXPDropShadowTADataBoss, kXPPrefix + 5)
DECLARE_PMID(kClassIDSpace, kXPDropShadowModeTABoss, kXPPrefix + 6)
DECLARE_PMID(kClassIDSpace, kXPDropShadowDistanceTABoss, kXPPrefix + 7)
DECLARE_PMID(kClassIDSpace, kXPDropShadowRadiusTABoss, kXPPrefix + 8)
DECLARE_PMID(kClassIDSpace, kXPDropShadowOpacityTABoss, kXPPrefix + 9)
DECLARE_PMID(kClassIDSpace, kXPDropShadowBlendModeTABoss, kXPPrefix + 10)
DECLARE_PMID(kClassIDSpace, kXPPageItemAdornmentBoss, kXPPrefix + 11)
DECLARE_PMID(kClassIDSpace, kXPDropShadowAdornmentBoss, kXPPrefix + 12)
DECLARE_PMID(kClassIDSpace, kXPVignetteAdornmentBoss, kXPPrefix + 13)
DECLARE_PMID(kClassIDSpace, kXPSetDropShadowCmdBoss, kXPPrefix + 14)
DECLARE_PMID(kClassIDSpace, kXPSetVignetteCmdBoss, kXPPrefix + 15)
DECLARE_PMID(kClassIDSpace, kXPSetBasicAttributesCmdBoss, kXPPrefix + 16)
// OBSOLETE: DECLARE_PMID(kClassIDSpace, kXPFlattenerSetupServiceBoss, kXPPrefix + 17)
DECLARE_PMID(kClassIDSpace, kXPManagerBoss, kXPPrefix + 18)
DECLARE_PMID(kClassIDSpace, kXPConversionBoss, kXPPrefix + 19)
//gap
DECLARE_PMID(kClassIDSpace, kXPSetPreferencesCmdBoss, kXPPrefix + 21)
DECLARE_PMID(kClassIDSpace, kXPBasicOpacityAttrBoss, kXPPrefix + 22)
DECLARE_PMID(kClassIDSpace, kXPBasicBlendModeAttrBoss, kXPPrefix + 23)
DECLARE_PMID(kClassIDSpace, kXPBasicKnockoutGroupAttrBoss, kXPPrefix + 24)
DECLARE_PMID(kClassIDSpace, kXPBasicIsolationGroupAttrBoss, kXPPrefix + 25)
DECLARE_PMID(kClassIDSpace, kXPDropShadowModeAttrBoss, kXPPrefix + 26)
DECLARE_PMID(kClassIDSpace, kXPDropShadowOffsetXAttrBoss, kXPPrefix + 27)
DECLARE_PMID(kClassIDSpace, kXPDropShadowOffsetYAttrBoss, kXPPrefix + 28)
DECLARE_PMID(kClassIDSpace, kXPDropShadowGrayValueAttrBoss_Obsolete, kXPPrefix + 29)
DECLARE_PMID(kClassIDSpace, kXPDropShadowOpacityAttrBoss, kXPPrefix + 30)
DECLARE_PMID(kClassIDSpace, kXPDropShadowBlendModeAttrBoss, kXPPrefix + 31)
DECLARE_PMID(kClassIDSpace, kXPDropShadowBlurRadiusAttrBoss, kXPPrefix + 32)
DECLARE_PMID(kClassIDSpace, kXPVignetteModeAttrBoss, kXPPrefix + 33)
DECLARE_PMID(kClassIDSpace, kXPVignetteWidthAttrBoss, kXPPrefix + 34)
DECLARE_PMID(kClassIDSpace, kXPVignetteOuterOpacityAttrBoss, kXPPrefix + 35)
DECLARE_PMID(kClassIDSpace, kXPVignetteInnerOpacityAttrBoss, kXPPrefix + 36)
DECLARE_PMID(kClassIDSpace, kXPVignetteCornersAttrBoss, kXPPrefix + 37)
DECLARE_PMID(kClassIDSpace, kTestViewPortBoss, kXPPrefix + 38)
DECLARE_PMID(kClassIDSpace, kXPStartupShutdownBoss, kXPPrefix + 39)
DECLARE_PMID(kClassIDSpace, kXPItemXPChangedCmdBoss, kXPPrefix + 40)
//replaced by itemxpprepost DECLARE_PMID(kClassIDSpace, kXPInvalItemCmdBoss, kXPPrefix + 41)
DECLARE_PMID(kClassIDSpace, kXPAttrScriptProviderBoss, kXPPrefix + 42)
DECLARE_PMID(kClassIDSpace, kXPPrefsScriptProviderBoss, kXPPrefix + 43)
DECLARE_PMID(kClassIDSpace, kXPEffectAdornmentBoss, kXPPrefix + 44)
//gap
DECLARE_PMID(kClassIDSpace, kXPFlattenerSettingsScrProvBoss, kXPPrefix + 47)

DECLARE_PMID(kClassIDSpace, kXPFlattenerStyleBoss, kXPPrefix + 48)
DECLARE_PMID(kClassIDSpace, kXPFlattenerStyleSetNameCmdBoss, kXPPrefix + 49)
DECLARE_PMID(kClassIDSpace, kXPFlattenerStyleAddCmdBoss, kXPPrefix + 50)
DECLARE_PMID(kClassIDSpace, kXPFlattenerStyleEditCmdBoss, kXPPrefix + 51)
DECLARE_PMID(kClassIDSpace, kXPFlattenerStyleDeleteCmdBoss, kXPPrefix + 52)
DECLARE_PMID(kClassIDSpace, kXPFlattenerStyleSetCmdBoss, kXPPrefix + 53)
DECLARE_PMID(kClassIDSpace, kXPFlattenerStyleExportRootBoss, kXPPrefix + 54)

DECLARE_PMID(kClassIDSpace, kXPDropShadowColorAttrBoss, kXPPrefix + 55)
DECLARE_PMID(kClassIDSpace, kXPFlattenerSettingsSetCmdBoss, kXPPrefix + 56)
DECLARE_PMID(kClassIDSpace, kXPItemXPPrePostCmdBoss, kXPPrefix + 57)
DECLARE_PMID(kClassIDSpace, kFlattenerStyleNewWSResponderBoss, kXPPrefix + 58)
DECLARE_PMID(kClassIDSpace, kXPSchemaConversionBoss, kXPPrefix + 59)
DECLARE_PMID(kClassIDSpace, kXPAttrBoss, kXPPrefix + 60)
DECLARE_PMID(kClassIDSpace, kDropShadowAttrBoss, kXPPrefix + 61)
DECLARE_PMID(kClassIDSpace, kVignetteAttrBoss, kXPPrefix + 62)
//DECLARE_PMID(kClassIDSpace, kTransparencySuiteRegisterBoss, kXPPrefix + 63)
DECLARE_PMID(kClassIDSpace, kFlattenerSettingsScriptProviderBoss, kXPPrefix + 64)
DECLARE_PMID(kClassIDSpace, kFlattenerStyleScriptProviderBoss, kXPPrefix + 65)
DECLARE_PMID(kClassIDSpace, kFlattenerPropScriptProviderBoss, kXPPrefix + 66)
//gap
DECLARE_PMID(kClassIDSpace, kFlattenerSettingsSpreadAddOnBoss,					kXPPrefix + 69)
DECLARE_PMID(kClassIDSpace, kXPFC_SettingsScriptProviderBoss,					kXPPrefix + 70)
DECLARE_PMID(kClassIDSpace, kXPWindowScriptProviderBoss,						kXPPrefix + 71)
DECLARE_PMID(kClassIDSpace, kXPNewDocResponderBoss,								kXPPrefix + 72)
DECLARE_PMID(kClassIDSpace, kXPCodeConversionProviderBoss,						kXPPrefix + 73)
DECLARE_PMID(kClassIDSpace, kXPDropShadowSpreadAttrBoss,						kXPPrefix + 74)
DECLARE_PMID(kClassIDSpace, kXPDropShadowNoiseAttrBoss,							kXPPrefix + 75)
DECLARE_PMID(kClassIDSpace, kXPVignetteNoiseAttrBoss,							kXPPrefix + 76)
DECLARE_PMID(kClassIDSpace, kXPInnerShadowApplyAttrBoss,						kXPPrefix + 77)
DECLARE_PMID(kClassIDSpace, kXPInnerShadowColorAttrBoss,						kXPPrefix + 78)
DECLARE_PMID(kClassIDSpace, kXPInnerShadowBlendModeAttrBoss,					kXPPrefix + 79)
DECLARE_PMID(kClassIDSpace, kXPInnerShadowOpacityAttrBoss,						kXPPrefix + 80)
DECLARE_PMID(kClassIDSpace, kXPInnerShadowAngleAttrBoss,						kXPPrefix + 81)
DECLARE_PMID(kClassIDSpace, kXPInnerShadowDistanceAttrBoss,						kXPPrefix + 82)
DECLARE_PMID(kClassIDSpace, kXPInnerShadowUseGlobalLightAttrBoss,				kXPPrefix + 83)
DECLARE_PMID(kClassIDSpace, kXPInnerShadowChokeAttrBoss,						kXPPrefix + 84)
DECLARE_PMID(kClassIDSpace, kXPInnerShadowSizeAttrBoss,							kXPPrefix + 85)
DECLARE_PMID(kClassIDSpace, kXPInnerShadowNoiseAttrBoss,						kXPPrefix + 86)
DECLARE_PMID(kClassIDSpace, kXPOuterGlowApplyAttrBoss,							kXPPrefix + 87)
DECLARE_PMID(kClassIDSpace, kXPOuterGlowBlendModeAttrBoss,						kXPPrefix + 88)
DECLARE_PMID(kClassIDSpace, kXPOuterGlowOpacityAttrBoss,						kXPPrefix + 89)
DECLARE_PMID(kClassIDSpace, kXPOuterGlowNoiseAttrBoss,							kXPPrefix + 90)
DECLARE_PMID(kClassIDSpace, kXPOuterGlowColorAttrBoss,							kXPPrefix + 91)
DECLARE_PMID(kClassIDSpace, kXPOuterGlowTechniqueAttrBoss,						kXPPrefix + 92)
DECLARE_PMID(kClassIDSpace, kXPOuterGlowSpreadAttrBoss,							kXPPrefix + 93)
DECLARE_PMID(kClassIDSpace, kXPOuterGlowSizeAttrBoss,							kXPPrefix + 94)
DECLARE_PMID(kClassIDSpace, kXPInnerGlowApplyAttrBoss,							kXPPrefix + 95)
DECLARE_PMID(kClassIDSpace, kXPInnerGlowBlendModeAttrBoss,						kXPPrefix + 96)
DECLARE_PMID(kClassIDSpace, kXPInnerGlowOpacityAttrBoss,						kXPPrefix + 97)
DECLARE_PMID(kClassIDSpace, kXPInnerGlowNoiseAttrBoss,							kXPPrefix + 98)
DECLARE_PMID(kClassIDSpace, kXPInnerGlowColorAttrBoss,							kXPPrefix + 99)
DECLARE_PMID(kClassIDSpace, kXPInnerGlowTechniqueAttrBoss,						kXPPrefix + 100)
DECLARE_PMID(kClassIDSpace, kXPInnerGlowSpreadAttrBoss,							kXPPrefix + 101)
DECLARE_PMID(kClassIDSpace, kXPInnerGlowSizeAttrBoss,							kXPPrefix + 102)
DECLARE_PMID(kClassIDSpace, kXPInnerGlowSourceAttrBoss,							kXPPrefix + 103)
DECLARE_PMID(kClassIDSpace, kXPBevelEmbossApplyAttrBoss,						kXPPrefix + 104)
DECLARE_PMID(kClassIDSpace, kXPBevelEmbossStyleAttrBoss,						kXPPrefix + 105)
DECLARE_PMID(kClassIDSpace, kXPBevelEmbossTechniqueAttrBoss,					kXPPrefix + 106)
DECLARE_PMID(kClassIDSpace, kXPBevelEmbossDepthAttrBoss,						kXPPrefix + 107)
DECLARE_PMID(kClassIDSpace, kXPBevelEmbossDirectionAttrBoss,					kXPPrefix + 108)
DECLARE_PMID(kClassIDSpace, kXPBevelEmbossSizeAttrBoss,							kXPPrefix + 109)
DECLARE_PMID(kClassIDSpace, kXPBevelEmbossSoftenAttrBoss,						kXPPrefix + 110)
DECLARE_PMID(kClassIDSpace, kXPBevelEmbossAngleAttrBoss,						kXPPrefix + 111)
DECLARE_PMID(kClassIDSpace, kXPBevelEmbossAltitudeAttrBoss,						kXPPrefix + 112)
DECLARE_PMID(kClassIDSpace, kXPBevelEmbossUseGlobalLightAttrBoss,				kXPPrefix + 113)
DECLARE_PMID(kClassIDSpace, kXPBevelEmbossHighlightColorAttrBoss,				kXPPrefix + 114)
DECLARE_PMID(kClassIDSpace, kXPBevelEmbossHighlightBlendModeAttrBoss,			kXPPrefix + 115)
DECLARE_PMID(kClassIDSpace, kXPBevelEmbossHighlightOpacityAttrBoss,				kXPPrefix + 116)
DECLARE_PMID(kClassIDSpace, kXPBevelEmbossShadowColorAttrBoss,					kXPPrefix + 117)
DECLARE_PMID(kClassIDSpace, kXPBevelEmbossShadowBlendModeAttrBoss,				kXPPrefix + 118)
DECLARE_PMID(kClassIDSpace, kXPBevelEmbossShadowOpacityAttrBoss,				kXPPrefix + 119)
DECLARE_PMID(kClassIDSpace, kXPSatinApplyAttrBoss,								kXPPrefix + 120)
DECLARE_PMID(kClassIDSpace, kXPSatinColorAttrBoss,								kXPPrefix + 121)
DECLARE_PMID(kClassIDSpace, kXPSatinBlendModeAttrBoss,							kXPPrefix + 122)
DECLARE_PMID(kClassIDSpace, kXPSatinOpacityAttrBoss,							kXPPrefix + 123)
DECLARE_PMID(kClassIDSpace, kXPSatinAngleAttrBoss,								kXPPrefix + 124)
DECLARE_PMID(kClassIDSpace, kXPSatinDistanceAttrBoss,							kXPPrefix + 125)
DECLARE_PMID(kClassIDSpace, kXPSatinSizeAttrBoss,								kXPPrefix + 126)
DECLARE_PMID(kClassIDSpace, kXPSatinInvertAttrBoss,								kXPPrefix + 127)
DECLARE_PMID(kClassIDSpace, kXPSetAttributesCmdBoss,							kXPPrefix + 128)
// Leave 10-id gap here (129-138) for private purposes.
DECLARE_PMID(kClassIDSpace, kXPInnerShadowAttrBoss,								kXPPrefix + 139)
DECLARE_PMID(kClassIDSpace, kXPOuterGlowAttrBoss,								kXPPrefix + 140)
DECLARE_PMID(kClassIDSpace, kXPInnerGlowAttrBoss,								kXPPrefix + 141)
DECLARE_PMID(kClassIDSpace, kXPBevelEmbossAttrBoss,								kXPPrefix + 142)
DECLARE_PMID(kClassIDSpace, kXPSatinAttrBoss,									kXPPrefix + 143)
DECLARE_PMID(kClassIDSpace, kXPDropShadowUseGlobalLightAttrBoss,				kXPPrefix + 144)
DECLARE_PMID(kClassIDSpace, kXPStrokeBlendingOpacityAttrBoss,					kXPPrefix + 145)
DECLARE_PMID(kClassIDSpace, kXPStrokeBlendingBlendModeAttrBoss,					kXPPrefix + 146)
DECLARE_PMID(kClassIDSpace, kXPStrokeBlendingKnockoutGroupAttrBoss,				kXPPrefix + 147)
DECLARE_PMID(kClassIDSpace, kXPStrokeBlendingIsolationGroupAttrBoss,			kXPPrefix + 148)
DECLARE_PMID(kClassIDSpace, kXPStrokeDropShadowModeAttrBoss,					kXPPrefix + 149)
DECLARE_PMID(kClassIDSpace, kXPStrokeDropShadowOffsetXAttrBoss,					kXPPrefix + 150)
DECLARE_PMID(kClassIDSpace, kXPStrokeDropShadowOffsetYAttrBoss,					kXPPrefix + 151)
DECLARE_PMID(kClassIDSpace, kXPStrokeDropShadowOpacityAttrBoss,					kXPPrefix + 152)
DECLARE_PMID(kClassIDSpace, kXPStrokeDropShadowBlendModeAttrBoss,				kXPPrefix + 153)
DECLARE_PMID(kClassIDSpace, kXPStrokeDropShadowBlurRadiusAttrBoss,				kXPPrefix + 154)
DECLARE_PMID(kClassIDSpace, kXPStrokeDropShadowSpreadAttrBoss,					kXPPrefix + 155)
DECLARE_PMID(kClassIDSpace, kXPStrokeDropShadowNoiseAttrBoss,					kXPPrefix + 156)
DECLARE_PMID(kClassIDSpace, kXPStrokeDropShadowColorAttrBoss,					kXPPrefix + 157)
DECLARE_PMID(kClassIDSpace, kXPStrokeDropShadowUseGlobalLightAttrBoss,			kXPPrefix + 158)
DECLARE_PMID(kClassIDSpace, kXPStrokeFeatherModeAttrBoss,						kXPPrefix + 159)
DECLARE_PMID(kClassIDSpace, kXPStrokeFeatherWidthAttrBoss,						kXPPrefix + 160)
DECLARE_PMID(kClassIDSpace, kXPStrokeFeatherOuterOpacityAttrBoss,				kXPPrefix + 161)
DECLARE_PMID(kClassIDSpace, kXPStrokeFeatherInnerOpacityAttrBoss,				kXPPrefix + 162)
DECLARE_PMID(kClassIDSpace, kXPStrokeFeatherCornersAttrBoss,					kXPPrefix + 163)
DECLARE_PMID(kClassIDSpace, kXPStrokeFeatherNoiseAttrBoss,						kXPPrefix + 164)
DECLARE_PMID(kClassIDSpace, kXPStrokeInnerShadowApplyAttrBoss,					kXPPrefix + 165)
DECLARE_PMID(kClassIDSpace, kXPStrokeInnerShadowColorAttrBoss,					kXPPrefix + 166)
DECLARE_PMID(kClassIDSpace, kXPStrokeInnerShadowBlendModeAttrBoss,				kXPPrefix + 167)
DECLARE_PMID(kClassIDSpace, kXPStrokeInnerShadowOpacityAttrBoss,				kXPPrefix + 168)
DECLARE_PMID(kClassIDSpace, kXPStrokeInnerShadowAngleAttrBoss,					kXPPrefix + 169)
DECLARE_PMID(kClassIDSpace, kXPStrokeInnerShadowDistanceAttrBoss,				kXPPrefix + 170)
DECLARE_PMID(kClassIDSpace, kXPStrokeInnerShadowUseGlobalLightAttrBoss,			kXPPrefix + 171)
DECLARE_PMID(kClassIDSpace, kXPStrokeInnerShadowChokeAttrBoss,					kXPPrefix + 172)
DECLARE_PMID(kClassIDSpace, kXPStrokeInnerShadowSizeAttrBoss,					kXPPrefix + 173)
DECLARE_PMID(kClassIDSpace, kXPStrokeInnerShadowNoiseAttrBoss,					kXPPrefix + 174)
DECLARE_PMID(kClassIDSpace, kXPStrokeOuterGlowApplyAttrBoss,					kXPPrefix + 175)
DECLARE_PMID(kClassIDSpace, kXPStrokeOuterGlowBlendModeAttrBoss,				kXPPrefix + 176)
DECLARE_PMID(kClassIDSpace, kXPStrokeOuterGlowOpacityAttrBoss,					kXPPrefix + 177)
DECLARE_PMID(kClassIDSpace, kXPStrokeOuterGlowNoiseAttrBoss,					kXPPrefix + 178)
DECLARE_PMID(kClassIDSpace, kXPStrokeOuterGlowColorAttrBoss,					kXPPrefix + 179)
DECLARE_PMID(kClassIDSpace, kXPStrokeOuterGlowTechniqueAttrBoss,				kXPPrefix + 180)
DECLARE_PMID(kClassIDSpace, kXPStrokeOuterGlowSpreadAttrBoss,					kXPPrefix + 181)
DECLARE_PMID(kClassIDSpace, kXPStrokeOuterGlowSizeAttrBoss,						kXPPrefix + 182)
DECLARE_PMID(kClassIDSpace, kXPStrokeInnerGlowApplyAttrBoss,					kXPPrefix + 183)
DECLARE_PMID(kClassIDSpace, kXPStrokeInnerGlowBlendModeAttrBoss,				kXPPrefix + 184)
DECLARE_PMID(kClassIDSpace, kXPStrokeInnerGlowOpacityAttrBoss,					kXPPrefix + 185)
DECLARE_PMID(kClassIDSpace, kXPStrokeInnerGlowNoiseAttrBoss,					kXPPrefix + 186)
DECLARE_PMID(kClassIDSpace, kXPStrokeInnerGlowColorAttrBoss,					kXPPrefix + 187)
DECLARE_PMID(kClassIDSpace, kXPStrokeInnerGlowTechniqueAttrBoss,				kXPPrefix + 188)
DECLARE_PMID(kClassIDSpace, kXPStrokeInnerGlowSpreadAttrBoss,					kXPPrefix + 189)
DECLARE_PMID(kClassIDSpace, kXPStrokeInnerGlowSizeAttrBoss,						kXPPrefix + 190)
DECLARE_PMID(kClassIDSpace, kXPStrokeInnerGlowSourceAttrBoss,					kXPPrefix + 191)
DECLARE_PMID(kClassIDSpace, kXPStrokeBevelEmbossApplyAttrBoss,					kXPPrefix + 192)
DECLARE_PMID(kClassIDSpace, kXPStrokeBevelEmbossStyleAttrBoss,					kXPPrefix + 193)
DECLARE_PMID(kClassIDSpace, kXPStrokeBevelEmbossTechniqueAttrBoss,				kXPPrefix + 194)
DECLARE_PMID(kClassIDSpace, kXPStrokeBevelEmbossDepthAttrBoss,					kXPPrefix + 195)
DECLARE_PMID(kClassIDSpace, kXPStrokeBevelEmbossDirectionAttrBoss,				kXPPrefix + 196)
DECLARE_PMID(kClassIDSpace, kXPStrokeBevelEmbossSizeAttrBoss,					kXPPrefix + 197)
DECLARE_PMID(kClassIDSpace, kXPStrokeBevelEmbossSoftenAttrBoss,					kXPPrefix + 198)
DECLARE_PMID(kClassIDSpace, kXPStrokeBevelEmbossAngleAttrBoss,					kXPPrefix + 199)
DECLARE_PMID(kClassIDSpace, kXPStrokeBevelEmbossAltitudeAttrBoss,				kXPPrefix + 200)
DECLARE_PMID(kClassIDSpace, kXPStrokeBevelEmbossUseGlobalLightAttrBoss,			kXPPrefix + 201)
DECLARE_PMID(kClassIDSpace, kXPStrokeBevelEmbossHighlightColorAttrBoss,			kXPPrefix + 202)
DECLARE_PMID(kClassIDSpace, kXPStrokeBevelEmbossHighlightBlendModeAttrBoss,		kXPPrefix + 203)
DECLARE_PMID(kClassIDSpace, kXPStrokeBevelEmbossHighlightOpacityAttrBoss,		kXPPrefix + 204)
DECLARE_PMID(kClassIDSpace, kXPStrokeBevelEmbossShadowColorAttrBoss,			kXPPrefix + 205)
DECLARE_PMID(kClassIDSpace, kXPStrokeBevelEmbossShadowBlendModeAttrBoss,		kXPPrefix + 206)
DECLARE_PMID(kClassIDSpace, kXPStrokeBevelEmbossShadowOpacityAttrBoss,			kXPPrefix + 207)
DECLARE_PMID(kClassIDSpace, kXPStrokeSatinApplyAttrBoss,						kXPPrefix + 208)
DECLARE_PMID(kClassIDSpace, kXPStrokeSatinColorAttrBoss,						kXPPrefix + 209)
DECLARE_PMID(kClassIDSpace, kXPStrokeSatinBlendModeAttrBoss,					kXPPrefix + 210)
DECLARE_PMID(kClassIDSpace, kXPStrokeSatinOpacityAttrBoss,						kXPPrefix + 211)
DECLARE_PMID(kClassIDSpace, kXPStrokeSatinAngleAttrBoss,						kXPPrefix + 212)
DECLARE_PMID(kClassIDSpace, kXPStrokeSatinDistanceAttrBoss,						kXPPrefix + 213)
DECLARE_PMID(kClassIDSpace, kXPStrokeSatinSizeAttrBoss,							kXPPrefix + 214)
DECLARE_PMID(kClassIDSpace, kXPStrokeSatinInvertAttrBoss,						kXPPrefix + 215)
DECLARE_PMID(kClassIDSpace, kXPFillBlendingOpacityAttrBoss,						kXPPrefix + 216)
DECLARE_PMID(kClassIDSpace, kXPFillBlendingBlendModeAttrBoss,					kXPPrefix + 217)
DECLARE_PMID(kClassIDSpace, kXPFillBlendingKnockoutGroupAttrBoss,				kXPPrefix + 218)
DECLARE_PMID(kClassIDSpace, kXPFillBlendingIsolationGroupAttrBoss,				kXPPrefix + 219)
DECLARE_PMID(kClassIDSpace, kXPFillDropShadowModeAttrBoss,						kXPPrefix + 220)
DECLARE_PMID(kClassIDSpace, kXPFillDropShadowOffsetXAttrBoss,					kXPPrefix + 221)
DECLARE_PMID(kClassIDSpace, kXPFillDropShadowOffsetYAttrBoss,					kXPPrefix + 222)
DECLARE_PMID(kClassIDSpace, kXPFillDropShadowOpacityAttrBoss,					kXPPrefix + 223)
DECLARE_PMID(kClassIDSpace, kXPFillDropShadowBlendModeAttrBoss,					kXPPrefix + 224)
DECLARE_PMID(kClassIDSpace, kXPFillDropShadowBlurRadiusAttrBoss,				kXPPrefix + 225)
DECLARE_PMID(kClassIDSpace, kXPFillDropShadowSpreadAttrBoss,					kXPPrefix + 226)
DECLARE_PMID(kClassIDSpace, kXPFillDropShadowNoiseAttrBoss,						kXPPrefix + 227)
DECLARE_PMID(kClassIDSpace, kXPFillDropShadowColorAttrBoss,						kXPPrefix + 228)
DECLARE_PMID(kClassIDSpace, kXPFillDropShadowUseGlobalLightAttrBoss,			kXPPrefix + 229)
DECLARE_PMID(kClassIDSpace, kXPFillFeatherModeAttrBoss,							kXPPrefix + 230)
DECLARE_PMID(kClassIDSpace, kXPFillFeatherWidthAttrBoss,						kXPPrefix + 231)
DECLARE_PMID(kClassIDSpace, kXPFillFeatherOuterOpacityAttrBoss,					kXPPrefix + 232)
DECLARE_PMID(kClassIDSpace, kXPFillFeatherInnerOpacityAttrBoss,					kXPPrefix + 233)
DECLARE_PMID(kClassIDSpace, kXPFillFeatherCornersAttrBoss,						kXPPrefix + 234)
DECLARE_PMID(kClassIDSpace, kXPFillFeatherNoiseAttrBoss,						kXPPrefix + 235)
DECLARE_PMID(kClassIDSpace, kXPFillInnerShadowApplyAttrBoss,					kXPPrefix + 236)
DECLARE_PMID(kClassIDSpace, kXPFillInnerShadowColorAttrBoss,					kXPPrefix + 237)
DECLARE_PMID(kClassIDSpace, kXPFillInnerShadowBlendModeAttrBoss,				kXPPrefix + 238)
DECLARE_PMID(kClassIDSpace, kXPFillInnerShadowOpacityAttrBoss,					kXPPrefix + 239)
DECLARE_PMID(kClassIDSpace, kXPFillInnerShadowAngleAttrBoss,					kXPPrefix + 240)
DECLARE_PMID(kClassIDSpace, kXPFillInnerShadowDistanceAttrBoss,					kXPPrefix + 241)
DECLARE_PMID(kClassIDSpace, kXPFillInnerShadowUseGlobalLightAttrBoss,			kXPPrefix + 242)
DECLARE_PMID(kClassIDSpace, kXPFillInnerShadowChokeAttrBoss,					kXPPrefix + 243)
DECLARE_PMID(kClassIDSpace, kXPFillInnerShadowSizeAttrBoss,						kXPPrefix + 244)
DECLARE_PMID(kClassIDSpace, kXPFillInnerShadowNoiseAttrBoss,					kXPPrefix + 245)
DECLARE_PMID(kClassIDSpace, kXPFillOuterGlowApplyAttrBoss,						kXPPrefix + 246)
DECLARE_PMID(kClassIDSpace, kXPFillOuterGlowBlendModeAttrBoss,					kXPPrefix + 247)
DECLARE_PMID(kClassIDSpace, kXPFillOuterGlowOpacityAttrBoss,					kXPPrefix + 248)
DECLARE_PMID(kClassIDSpace, kXPFillOuterGlowNoiseAttrBoss,						kXPPrefix + 249)
DECLARE_PMID(kClassIDSpace, kXPFillOuterGlowColorAttrBoss,						kXPPrefix + 250)
DECLARE_PMID(kClassIDSpace, kXPFillOuterGlowTechniqueAttrBoss,					kXPPrefix + 251)
DECLARE_PMID(kClassIDSpace, kXPFillOuterGlowSpreadAttrBoss,						kXPPrefix + 252)
DECLARE_PMID(kClassIDSpace, kXPFillOuterGlowSizeAttrBoss,						kXPPrefix + 253)
DECLARE_PMID(kClassIDSpace, kXPFillInnerGlowApplyAttrBoss,						kXPPrefix + 254)
DECLARE_PMID(kClassIDSpace, kXPFillInnerGlowBlendModeAttrBoss,					kXPPrefix + 255)
DECLARE_PMID(kClassIDSpace, kXPFillInnerGlowOpacityAttrBoss,					kXPPrefix2 + 0)
DECLARE_PMID(kClassIDSpace, kXPFillInnerGlowNoiseAttrBoss,						kXPPrefix2 + 1)
DECLARE_PMID(kClassIDSpace, kXPFillInnerGlowColorAttrBoss,						kXPPrefix2 + 2)
DECLARE_PMID(kClassIDSpace, kXPFillInnerGlowTechniqueAttrBoss,					kXPPrefix2 + 3)
DECLARE_PMID(kClassIDSpace, kXPFillInnerGlowSpreadAttrBoss,						kXPPrefix2 + 4)
DECLARE_PMID(kClassIDSpace, kXPFillInnerGlowSizeAttrBoss,						kXPPrefix2 + 5)
DECLARE_PMID(kClassIDSpace, kXPFillInnerGlowSourceAttrBoss,						kXPPrefix2 + 6)
DECLARE_PMID(kClassIDSpace, kXPFillBevelEmbossApplyAttrBoss,					kXPPrefix2 + 7)
DECLARE_PMID(kClassIDSpace, kXPFillBevelEmbossStyleAttrBoss,					kXPPrefix2 + 8)
DECLARE_PMID(kClassIDSpace, kXPFillBevelEmbossTechniqueAttrBoss,				kXPPrefix2 + 9)
DECLARE_PMID(kClassIDSpace, kXPFillBevelEmbossDepthAttrBoss,					kXPPrefix2 + 10)
DECLARE_PMID(kClassIDSpace, kXPFillBevelEmbossDirectionAttrBoss,				kXPPrefix2 + 11)
DECLARE_PMID(kClassIDSpace, kXPFillBevelEmbossSizeAttrBoss,						kXPPrefix2 + 12)
DECLARE_PMID(kClassIDSpace, kXPFillBevelEmbossSoftenAttrBoss,					kXPPrefix2 + 13)
DECLARE_PMID(kClassIDSpace, kXPFillBevelEmbossAngleAttrBoss,					kXPPrefix2 + 14)
DECLARE_PMID(kClassIDSpace, kXPFillBevelEmbossAltitudeAttrBoss,					kXPPrefix2 + 15)
DECLARE_PMID(kClassIDSpace, kXPFillBevelEmbossUseGlobalLightAttrBoss,			kXPPrefix2 + 16)
DECLARE_PMID(kClassIDSpace, kXPFillBevelEmbossHighlightColorAttrBoss,			kXPPrefix2 + 17)
DECLARE_PMID(kClassIDSpace, kXPFillBevelEmbossHighlightBlendModeAttrBoss,		kXPPrefix2 + 18)
DECLARE_PMID(kClassIDSpace, kXPFillBevelEmbossHighlightOpacityAttrBoss,			kXPPrefix2 + 19)
DECLARE_PMID(kClassIDSpace, kXPFillBevelEmbossShadowColorAttrBoss,				kXPPrefix2 + 20)
DECLARE_PMID(kClassIDSpace, kXPFillBevelEmbossShadowBlendModeAttrBoss,			kXPPrefix2 + 21)
DECLARE_PMID(kClassIDSpace, kXPFillBevelEmbossShadowOpacityAttrBoss,			kXPPrefix2 + 22)
DECLARE_PMID(kClassIDSpace, kXPFillSatinApplyAttrBoss,							kXPPrefix2 + 23)
DECLARE_PMID(kClassIDSpace, kXPFillSatinColorAttrBoss,							kXPPrefix2 + 24)
DECLARE_PMID(kClassIDSpace, kXPFillSatinBlendModeAttrBoss,						kXPPrefix2 + 25)
DECLARE_PMID(kClassIDSpace, kXPFillSatinOpacityAttrBoss,						kXPPrefix2 + 26)
DECLARE_PMID(kClassIDSpace, kXPFillSatinAngleAttrBoss,							kXPPrefix2 + 27)
DECLARE_PMID(kClassIDSpace, kXPFillSatinDistanceAttrBoss,						kXPPrefix2 + 28)
DECLARE_PMID(kClassIDSpace, kXPFillSatinSizeAttrBoss,							kXPPrefix2 + 29)
DECLARE_PMID(kClassIDSpace, kXPFillSatinInvertAttrBoss,							kXPPrefix2 + 30)
DECLARE_PMID(kClassIDSpace, kXPSettingsScriptProviderBoss,						kXPPrefix2 + 31)
DECLARE_PMID(kClassIDSpace, kXPBlendingSettingsScriptProviderBoss,				kXPPrefix2 + 32)
DECLARE_PMID(kClassIDSpace, kXPDropShadowSettingsScriptProviderBoss,			kXPPrefix2 + 33)
DECLARE_PMID(kClassIDSpace, kXPFeatherSettingsScriptProviderBoss,				kXPPrefix2 + 34)
DECLARE_PMID(kClassIDSpace, kXPInnerShadowSettingsScriptProviderBoss,			kXPPrefix2 + 35)
DECLARE_PMID(kClassIDSpace, kXPOuterGlowSettingsScriptProviderBoss,				kXPPrefix2 + 36)
DECLARE_PMID(kClassIDSpace, kXPInnerGlowSettingsScriptProviderBoss,				kXPPrefix2 + 37)
DECLARE_PMID(kClassIDSpace, kXPBevelEmbossSettingsScriptProviderBoss,			kXPPrefix2 + 38)
DECLARE_PMID(kClassIDSpace, kXPSatinSettingsScriptProviderBoss,					kXPPrefix2 + 39)
DECLARE_PMID(kClassIDSpace, kXPContentBlendingOpacityAttrBoss,					kXPPrefix2 + 40)
DECLARE_PMID(kClassIDSpace, kXPContentBlendingBlendModeAttrBoss,				kXPPrefix2 + 41)
DECLARE_PMID(kClassIDSpace, kXPContentBlendingKnockoutGroupAttrBoss,			kXPPrefix2 + 42)
DECLARE_PMID(kClassIDSpace, kXPContentBlendingIsolationGroupAttrBoss,			kXPPrefix2 + 43)
DECLARE_PMID(kClassIDSpace, kXPContentDropShadowModeAttrBoss,					kXPPrefix2 + 44)
DECLARE_PMID(kClassIDSpace, kXPContentDropShadowOffsetXAttrBoss,				kXPPrefix2 + 45)
DECLARE_PMID(kClassIDSpace, kXPContentDropShadowOffsetYAttrBoss,				kXPPrefix2 + 46)
DECLARE_PMID(kClassIDSpace, kXPContentDropShadowOpacityAttrBoss,				kXPPrefix2 + 47)
DECLARE_PMID(kClassIDSpace, kXPContentDropShadowBlendModeAttrBoss,				kXPPrefix2 + 48)
DECLARE_PMID(kClassIDSpace, kXPContentDropShadowBlurRadiusAttrBoss,				kXPPrefix2 + 49)
DECLARE_PMID(kClassIDSpace, kXPContentDropShadowSpreadAttrBoss,					kXPPrefix2 + 50)
DECLARE_PMID(kClassIDSpace, kXPContentDropShadowNoiseAttrBoss,					kXPPrefix2 + 51)
DECLARE_PMID(kClassIDSpace, kXPContentDropShadowColorAttrBoss,					kXPPrefix2 + 52)
DECLARE_PMID(kClassIDSpace, kXPContentDropShadowUseGlobalLightAttrBoss,			kXPPrefix2 + 53)
DECLARE_PMID(kClassIDSpace, kXPContentFeatherModeAttrBoss,						kXPPrefix2 + 54)
DECLARE_PMID(kClassIDSpace, kXPContentFeatherWidthAttrBoss,						kXPPrefix2 + 55)
DECLARE_PMID(kClassIDSpace, kXPContentFeatherOuterOpacityAttrBoss,				kXPPrefix2 + 56)
DECLARE_PMID(kClassIDSpace, kXPContentFeatherInnerOpacityAttrBoss,				kXPPrefix2 + 57)
DECLARE_PMID(kClassIDSpace, kXPContentFeatherCornersAttrBoss,					kXPPrefix2 + 58)
DECLARE_PMID(kClassIDSpace, kXPContentFeatherNoiseAttrBoss,						kXPPrefix2 + 59)
DECLARE_PMID(kClassIDSpace, kXPContentInnerShadowApplyAttrBoss,					kXPPrefix2 + 60)
DECLARE_PMID(kClassIDSpace, kXPContentInnerShadowColorAttrBoss,					kXPPrefix2 + 61)
DECLARE_PMID(kClassIDSpace, kXPContentInnerShadowBlendModeAttrBoss,				kXPPrefix2 + 62)
DECLARE_PMID(kClassIDSpace, kXPContentInnerShadowOpacityAttrBoss,				kXPPrefix2 + 63)
DECLARE_PMID(kClassIDSpace, kXPContentInnerShadowAngleAttrBoss,					kXPPrefix2 + 64)
DECLARE_PMID(kClassIDSpace, kXPContentInnerShadowDistanceAttrBoss,				kXPPrefix2 + 65)
DECLARE_PMID(kClassIDSpace, kXPContentInnerShadowUseGlobalLightAttrBoss,		kXPPrefix2 + 66)
DECLARE_PMID(kClassIDSpace, kXPContentInnerShadowChokeAttrBoss,					kXPPrefix2 + 67)
DECLARE_PMID(kClassIDSpace, kXPContentInnerShadowSizeAttrBoss,					kXPPrefix2 + 68)
DECLARE_PMID(kClassIDSpace, kXPContentInnerShadowNoiseAttrBoss,					kXPPrefix2 + 69)
DECLARE_PMID(kClassIDSpace, kXPContentOuterGlowApplyAttrBoss,					kXPPrefix2 + 70)
DECLARE_PMID(kClassIDSpace, kXPContentOuterGlowBlendModeAttrBoss,				kXPPrefix2 + 71)
DECLARE_PMID(kClassIDSpace, kXPContentOuterGlowOpacityAttrBoss,					kXPPrefix2 + 72)
DECLARE_PMID(kClassIDSpace, kXPContentOuterGlowNoiseAttrBoss,					kXPPrefix2 + 73)
DECLARE_PMID(kClassIDSpace, kXPContentOuterGlowColorAttrBoss,					kXPPrefix2 + 74)
DECLARE_PMID(kClassIDSpace, kXPContentOuterGlowTechniqueAttrBoss,				kXPPrefix2 + 75)
DECLARE_PMID(kClassIDSpace, kXPContentOuterGlowSpreadAttrBoss,					kXPPrefix2 + 76)
DECLARE_PMID(kClassIDSpace, kXPContentOuterGlowSizeAttrBoss,					kXPPrefix2 + 77)
DECLARE_PMID(kClassIDSpace, kXPContentInnerGlowApplyAttrBoss,					kXPPrefix2 + 78)
DECLARE_PMID(kClassIDSpace, kXPContentInnerGlowBlendModeAttrBoss,				kXPPrefix2 + 79)
DECLARE_PMID(kClassIDSpace, kXPContentInnerGlowOpacityAttrBoss,					kXPPrefix2 + 80)
DECLARE_PMID(kClassIDSpace, kXPContentInnerGlowNoiseAttrBoss,					kXPPrefix2 + 81)
DECLARE_PMID(kClassIDSpace, kXPContentInnerGlowColorAttrBoss,					kXPPrefix2 + 82)
DECLARE_PMID(kClassIDSpace, kXPContentInnerGlowTechniqueAttrBoss,				kXPPrefix2 + 83)
DECLARE_PMID(kClassIDSpace, kXPContentInnerGlowSpreadAttrBoss,					kXPPrefix2 + 84)
DECLARE_PMID(kClassIDSpace, kXPContentInnerGlowSizeAttrBoss,					kXPPrefix2 + 85)
DECLARE_PMID(kClassIDSpace, kXPContentInnerGlowSourceAttrBoss,					kXPPrefix2 + 86)
DECLARE_PMID(kClassIDSpace, kXPContentBevelEmbossApplyAttrBoss,					kXPPrefix2 + 87)
DECLARE_PMID(kClassIDSpace, kXPContentBevelEmbossStyleAttrBoss,					kXPPrefix2 + 88)
DECLARE_PMID(kClassIDSpace, kXPContentBevelEmbossTechniqueAttrBoss,				kXPPrefix2 + 89)
DECLARE_PMID(kClassIDSpace, kXPContentBevelEmbossDepthAttrBoss,					kXPPrefix2 + 90)
DECLARE_PMID(kClassIDSpace, kXPContentBevelEmbossDirectionAttrBoss,				kXPPrefix2 + 91)
DECLARE_PMID(kClassIDSpace, kXPContentBevelEmbossSizeAttrBoss,					kXPPrefix2 + 92)
DECLARE_PMID(kClassIDSpace, kXPContentBevelEmbossSoftenAttrBoss,				kXPPrefix2 + 93)
DECLARE_PMID(kClassIDSpace, kXPContentBevelEmbossAngleAttrBoss,					kXPPrefix2 + 94)
DECLARE_PMID(kClassIDSpace, kXPContentBevelEmbossAltitudeAttrBoss,				kXPPrefix2 + 95)
DECLARE_PMID(kClassIDSpace, kXPContentBevelEmbossUseGlobalLightAttrBoss,		kXPPrefix2 + 96)
DECLARE_PMID(kClassIDSpace, kXPContentBevelEmbossHighlightColorAttrBoss,		kXPPrefix2 + 97)
DECLARE_PMID(kClassIDSpace, kXPContentBevelEmbossHighlightBlendModeAttrBoss,	kXPPrefix2 + 98)
DECLARE_PMID(kClassIDSpace, kXPContentBevelEmbossHighlightOpacityAttrBoss,		kXPPrefix2 + 99)
DECLARE_PMID(kClassIDSpace, kXPContentBevelEmbossShadowColorAttrBoss,			kXPPrefix2 + 100)
DECLARE_PMID(kClassIDSpace, kXPContentBevelEmbossShadowBlendModeAttrBoss,		kXPPrefix2 + 101)
DECLARE_PMID(kClassIDSpace, kXPContentBevelEmbossShadowOpacityAttrBoss,			kXPPrefix2 + 102)
DECLARE_PMID(kClassIDSpace, kXPContentSatinApplyAttrBoss,						kXPPrefix2 + 103)
DECLARE_PMID(kClassIDSpace, kXPContentSatinColorAttrBoss,						kXPPrefix2 + 104)
DECLARE_PMID(kClassIDSpace, kXPContentSatinBlendModeAttrBoss,					kXPPrefix2 + 105)
DECLARE_PMID(kClassIDSpace, kXPContentSatinOpacityAttrBoss,						kXPPrefix2 + 106)
DECLARE_PMID(kClassIDSpace, kXPContentSatinAngleAttrBoss,						kXPPrefix2 + 107)
DECLARE_PMID(kClassIDSpace, kXPContentSatinDistanceAttrBoss,					kXPPrefix2 + 108)
DECLARE_PMID(kClassIDSpace, kXPContentSatinSizeAttrBoss,						kXPPrefix2 + 109)
DECLARE_PMID(kClassIDSpace, kXPContentSatinInvertAttrBoss,						kXPPrefix2 + 110)
DECLARE_PMID(kClassIDSpace, kXPDropShadowKOAttrBoss,							kXPPrefix2 + 111)
DECLARE_PMID(kClassIDSpace, kXPStrokeDropShadowKOAttrBoss,						kXPPrefix2 + 112)
DECLARE_PMID(kClassIDSpace, kXPFillDropShadowKOAttrBoss,						kXPPrefix2 + 113)
DECLARE_PMID(kClassIDSpace, kXPContentDropShadowKOAttrBoss,						kXPPrefix2 + 114)
// Back to other stuff now..
DECLARE_PMID(kClassIDSpace, kXPInnerEffectsAdornmentBoss,						kXPPrefix2 + 115)
// Directional feather attributes..
DECLARE_PMID(kClassIDSpace, kXPDirectionalFeatherApplyAttrBoss,					kXPPrefix2 + 116)
DECLARE_PMID(kClassIDSpace, kXPDirectionalFeatherWidthAttrBoss,					kXPPrefix2 + 117)
DECLARE_PMID(kClassIDSpace, kXPDirectionalFeatherAngleAttrBoss,					kXPPrefix2 + 118)
DECLARE_PMID(kClassIDSpace, kXPDirectionalFeatherFollowShapeAttrBoss,			kXPPrefix2 + 119)
DECLARE_PMID(kClassIDSpace, kXPDirectionalFeatherNoiseAttrBoss,					kXPPrefix2 + 120)
DECLARE_PMID(kClassIDSpace, kXPStrokeDirectionalFeatherApplyAttrBoss,			kXPPrefix2 + 121)
DECLARE_PMID(kClassIDSpace, kXPStrokeDirectionalFeatherWidthAttrBoss,			kXPPrefix2 + 122)
DECLARE_PMID(kClassIDSpace, kXPStrokeDirectionalFeatherAngleAttrBoss,			kXPPrefix2 + 123)
DECLARE_PMID(kClassIDSpace, kXPStrokeDirectionalFeatherFollowShapeAttrBoss,		kXPPrefix2 + 124)
DECLARE_PMID(kClassIDSpace, kXPStrokeDirectionalFeatherNoiseAttrBoss,			kXPPrefix2 + 125)
DECLARE_PMID(kClassIDSpace, kXPFillDirectionalFeatherApplyAttrBoss,				kXPPrefix2 + 126)
DECLARE_PMID(kClassIDSpace, kXPFillDirectionalFeatherWidthAttrBoss,				kXPPrefix2 + 127)
DECLARE_PMID(kClassIDSpace, kXPFillDirectionalFeatherAngleAttrBoss,				kXPPrefix2 + 128)
DECLARE_PMID(kClassIDSpace, kXPFillDirectionalFeatherFollowShapeAttrBoss,		kXPPrefix2 + 129)
DECLARE_PMID(kClassIDSpace, kXPFillDirectionalFeatherNoiseAttrBoss,				kXPPrefix2 + 130)
DECLARE_PMID(kClassIDSpace, kXPContentDirectionalFeatherApplyAttrBoss,			kXPPrefix2 + 131)
DECLARE_PMID(kClassIDSpace, kXPContentDirectionalFeatherWidthAttrBoss,			kXPPrefix2 + 132)
DECLARE_PMID(kClassIDSpace, kXPContentDirectionalFeatherAngleAttrBoss,			kXPPrefix2 + 133)
DECLARE_PMID(kClassIDSpace, kXPContentDirectionalFeatherFollowShapeAttrBoss,	kXPPrefix2 + 134)
DECLARE_PMID(kClassIDSpace, kXPContentDirectionalFeatherNoiseAttrBoss,			kXPPrefix2 + 135)
DECLARE_PMID(kClassIDSpace, kXPDirectionalFeatherAttrBoss,						kXPPrefix2 + 136)
DECLARE_PMID(kClassIDSpace, kXPDirectionalFeatherSettingsScriptProviderBoss,	kXPPrefix2 + 137)
// Gradient feather attributes..
DECLARE_PMID(kClassIDSpace, kXPGradientFeatherApplyAttrBoss,					kXPPrefix2 + 138)
DECLARE_PMID(kClassIDSpace, kXPGradientFeatherTypeAttrBoss,						kXPPrefix2 + 139)
DECLARE_PMID(kClassIDSpace, kXPGradientFeatherOpacityStopsAttrBoss,				kXPPrefix2 + 140)
DECLARE_PMID(kClassIDSpace, kXPGradientFeatherAngleAttrBoss,					kXPPrefix2 + 141)
DECLARE_PMID(kClassIDSpace, kXPGradientFeatherLengthAttrBoss,					kXPPrefix2 + 142)
DECLARE_PMID(kClassIDSpace, kXPGradientFeatherCenterAttrBoss,					kXPPrefix2 + 143)
DECLARE_PMID(kClassIDSpace, kXPGradientFeatherRadiusAttrBoss,					kXPPrefix2 + 144)
DECLARE_PMID(kClassIDSpace, kXPGradientFeatherHiliteAngleAttrBoss,				kXPPrefix2 + 145)
DECLARE_PMID(kClassIDSpace, kXPGradientFeatherHiliteLengthAttrBoss,				kXPPrefix2 + 146)
DECLARE_PMID(kClassIDSpace, kXPStrokeGradientFeatherApplyAttrBoss,				kXPPrefix2 + 147)
DECLARE_PMID(kClassIDSpace, kXPStrokeGradientFeatherTypeAttrBoss,				kXPPrefix2 + 148)
DECLARE_PMID(kClassIDSpace, kXPStrokeGradientFeatherOpacityStopsAttrBoss,		kXPPrefix2 + 149)
DECLARE_PMID(kClassIDSpace, kXPStrokeGradientFeatherAngleAttrBoss,				kXPPrefix2 + 150)
DECLARE_PMID(kClassIDSpace, kXPStrokeGradientFeatherLengthAttrBoss,				kXPPrefix2 + 151)
DECLARE_PMID(kClassIDSpace, kXPStrokeGradientFeatherCenterAttrBoss,				kXPPrefix2 + 152)
DECLARE_PMID(kClassIDSpace, kXPStrokeGradientFeatherRadiusAttrBoss,				kXPPrefix2 + 153)
DECLARE_PMID(kClassIDSpace, kXPStrokeGradientFeatherHiliteAngleAttrBoss,		kXPPrefix2 + 154)
DECLARE_PMID(kClassIDSpace, kXPStrokeGradientFeatherHiliteLengthAttrBoss,		kXPPrefix2 + 155)
DECLARE_PMID(kClassIDSpace, kXPFillGradientFeatherApplyAttrBoss,				kXPPrefix2 + 156)
DECLARE_PMID(kClassIDSpace, kXPFillGradientFeatherTypeAttrBoss,					kXPPrefix2 + 157)
DECLARE_PMID(kClassIDSpace, kXPFillGradientFeatherOpacityStopsAttrBoss,			kXPPrefix2 + 158)
DECLARE_PMID(kClassIDSpace, kXPFillGradientFeatherAngleAttrBoss,				kXPPrefix2 + 159)
DECLARE_PMID(kClassIDSpace, kXPFillGradientFeatherLengthAttrBoss,				kXPPrefix2 + 160)
DECLARE_PMID(kClassIDSpace, kXPFillGradientFeatherCenterAttrBoss,				kXPPrefix2 + 161)
DECLARE_PMID(kClassIDSpace, kXPFillGradientFeatherRadiusAttrBoss,				kXPPrefix2 + 162)
DECLARE_PMID(kClassIDSpace, kXPFillGradientFeatherHiliteAngleAttrBoss,			kXPPrefix2 + 163)
DECLARE_PMID(kClassIDSpace, kXPFillGradientFeatherHiliteLengthAttrBoss,			kXPPrefix2 + 164)
DECLARE_PMID(kClassIDSpace, kXPContentGradientFeatherApplyAttrBoss,				kXPPrefix2 + 165)
DECLARE_PMID(kClassIDSpace, kXPContentGradientFeatherTypeAttrBoss,				kXPPrefix2 + 166)
DECLARE_PMID(kClassIDSpace, kXPContentGradientFeatherOpacityStopsAttrBoss,		kXPPrefix2 + 167)
DECLARE_PMID(kClassIDSpace, kXPContentGradientFeatherAngleAttrBoss,				kXPPrefix2 + 168)
DECLARE_PMID(kClassIDSpace, kXPContentGradientFeatherLengthAttrBoss,			kXPPrefix2 + 169)
DECLARE_PMID(kClassIDSpace, kXPContentGradientFeatherCenterAttrBoss,			kXPPrefix2 + 170)
DECLARE_PMID(kClassIDSpace, kXPContentGradientFeatherRadiusAttrBoss,			kXPPrefix2 + 171)
DECLARE_PMID(kClassIDSpace, kXPContentGradientFeatherHiliteAngleAttrBoss,		kXPPrefix2 + 172)
DECLARE_PMID(kClassIDSpace, kXPContentGradientFeatherHiliteLengthAttrBoss,		kXPPrefix2 + 173)
DECLARE_PMID(kClassIDSpace, kXPGradientFeatherAttrBoss,							kXPPrefix2 + 174)
DECLARE_PMID(kClassIDSpace, kXPGradientFeatherSettingsScriptProviderBoss,		kXPPrefix2 + 175)
DECLARE_PMID(kClassIDSpace, kOpacityGradientStopScriptObjectBoss,				kXPPrefix2 + 176)
DECLARE_PMID(kClassIDSpace, kOpacityGradientStopScriptProviderBoss,				kXPPrefix2 + 177)
DECLARE_PMID(kClassIDSpace, kOpacityGradientStopsSimpleBoss,					kXPPrefix2 + 178)
DECLARE_PMID(kClassIDSpace, kXPVignetteChokeAttrBoss,							kXPPrefix2 + 179)
DECLARE_PMID(kClassIDSpace, kXPStrokeFeatherChokeAttrBoss,						kXPPrefix2 + 180)
DECLARE_PMID(kClassIDSpace, kXPFillFeatherChokeAttrBoss,						kXPPrefix2 + 181)
DECLARE_PMID(kClassIDSpace, kXPContentFeatherChokeAttrBoss,						kXPPrefix2 + 182)
DECLARE_PMID(kClassIDSpace, kXPDirectionalFeatherWidthLeftAttrBoss,				kXPPrefix2 + 183)
DECLARE_PMID(kClassIDSpace, kXPDirectionalFeatherWidthRightAttrBoss,			kXPPrefix2 + 184)
DECLARE_PMID(kClassIDSpace, kXPDirectionalFeatherWidthTopAttrBoss,				kXPPrefix2 + 185)
DECLARE_PMID(kClassIDSpace, kXPDirectionalFeatherWidthBottomAttrBoss,			kXPPrefix2 + 186)
DECLARE_PMID(kClassIDSpace, kXPStrokeDirectionalFeatherWidthLeftAttrBoss,		kXPPrefix2 + 187)
DECLARE_PMID(kClassIDSpace, kXPStrokeDirectionalFeatherWidthRightAttrBoss,		kXPPrefix2 + 188)
DECLARE_PMID(kClassIDSpace, kXPStrokeDirectionalFeatherWidthTopAttrBoss,		kXPPrefix2 + 189)
DECLARE_PMID(kClassIDSpace, kXPStrokeDirectionalFeatherWidthBottomAttrBoss,		kXPPrefix2 + 190)
DECLARE_PMID(kClassIDSpace, kXPFillDirectionalFeatherWidthLeftAttrBoss,			kXPPrefix2 + 191)
DECLARE_PMID(kClassIDSpace, kXPFillDirectionalFeatherWidthRightAttrBoss,		kXPPrefix2 + 192)
DECLARE_PMID(kClassIDSpace, kXPFillDirectionalFeatherWidthTopAttrBoss,			kXPPrefix2 + 193)
DECLARE_PMID(kClassIDSpace, kXPFillDirectionalFeatherWidthBottomAttrBoss,		kXPPrefix2 + 194)
DECLARE_PMID(kClassIDSpace, kXPContentDirectionalFeatherWidthLeftAttrBoss,		kXPPrefix2 + 195)
DECLARE_PMID(kClassIDSpace, kXPContentDirectionalFeatherWidthRightAttrBoss,		kXPPrefix2 + 196)
DECLARE_PMID(kClassIDSpace, kXPContentDirectionalFeatherWidthTopAttrBoss,		kXPPrefix2 + 197)
DECLARE_PMID(kClassIDSpace, kXPContentDirectionalFeatherWidthBottomAttrBoss,	kXPPrefix2 + 198)
DECLARE_PMID(kClassIDSpace, kXPDirectionalFeatherChokeAttrBoss,					kXPPrefix2 + 199)
DECLARE_PMID(kClassIDSpace, kXPStrokeDirectionalFeatherChokeAttrBoss,			kXPPrefix2 + 200)
DECLARE_PMID(kClassIDSpace, kXPFillDirectionalFeatherChokeAttrBoss,				kXPPrefix2 + 201)
DECLARE_PMID(kClassIDSpace, kXPContentDirectionalFeatherChokeAttrBoss,			kXPPrefix2 + 202)
DECLARE_PMID(kClassIDSpace, kXPDropShadowHonorFXAttrBoss,						kXPPrefix2 + 203)
DECLARE_PMID(kClassIDSpace, kXPStrokeDropShadowHonorFXAttrBoss,					kXPPrefix2 + 204)
DECLARE_PMID(kClassIDSpace, kXPFillDropShadowHonorFXAttrBoss,					kXPPrefix2 + 205)
DECLARE_PMID(kClassIDSpace, kXPContentDropShadowHonorFXAttrBoss,				kXPPrefix2 + 206)
DECLARE_PMID(kClassIDSpace, kXPExportSignalResponderBoss,						kXPPrefix2 + 207)
DECLARE_PMID(kClassIDSpace, kXPAlternativeADXYScriptProviderBoss,				kXPPrefix2 + 208)
DECLARE_PMID(kClassIDSpace, kXPFlattenerUtilsViewPortBoss,						kXPPrefix2 + 209)

// <Interface ID>
// IIDs
// DECLARE_PMID(kInterfaceIDSpace, IID_IXPSHADOWADORNMENTDATA, kXPPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IXPSETDROPSHADOWCMDDATA, kXPPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IXPSETVIGNETTECMDDATA, kXPPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IXPSETBASICATTRIBUTESCMDDATA, kXPPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IFLATTENERUSAGE, kXPPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IADORNMENTFLATTENERUSAGE, kXPPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IXPMANAGER, kXPPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IXPPREFERENCES, kXPPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IXPSETPREFERENCESCMDDATA, kXPPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IXPATTRIBUTESUITE, kXPPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IXPATTRIBUTES_OVERRIDES_DOCUMENT, kXPPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IXPSETATTRIBUTESCMDDATA, kXPPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IXPDOCOBSERVER, kXPPrefix + 17)

DECLARE_PMID(kInterfaceIDSpace, IID_IXPFLATTENERSETTINGS, kXPPrefix + 18)
//DECLARE_PMID(kInterfaceIDSpace, IID_IXPFLATTENERSTYLELOCKINFO, kXPPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_IXPFLATTENERSTYLELISTMGR, kXPPrefix + 20)
//DECLARE_PMID(kInterfaceIDSpace, IID_IXPFLATTENERSTYLECMDDATA, kXPPrefix + 21)

DECLARE_PMID(kInterfaceIDSpace, IID_IXPITEMXPPREPOSTCMDDATA, kXPPrefix + 22)

DECLARE_PMID(kInterfaceIDSpace, IID_IXPUTILS, kXPPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_IXPATTRIBUTEUTILS, kXPPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_IXPATTRIBUTEFACADE, kXPPrefix + 25)

DECLARE_PMID(kInterfaceIDSpace, IID_IXPPAGEITEMDRAWSETUP, kXPPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_IXPUIUTILS, kXPPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_IOPACITYGRADIENTSTOPS, kXPPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_IXPINTERNALUTILS, kXPPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_IXPFLATTENERUTILS, kXPPrefix + 30)


// <Implementation ID>
// Implementation IIDs (i.e. C++ classes)
DECLARE_PMID(kImplementationIDSpace, kXPDrwEvtServiceImpl, kXPPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kXPDrwEvtHandlerImpl, kXPPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kXPTestMenuImpl, kXPPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kXPWaxRunShadowImpl, kXPPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kXPDropShadowTADataImpl, kXPPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kXPShadowAdornmentDataImpl, kXPPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kXPDropShadowModeTARImpl, kXPPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kXPDropShadowDistanceTARImpl, kXPPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kXPDropShadowRadiusTARImpl, kXPPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kXPDropShadowOpacityTARImpl, kXPPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kXPDropShadowBlendModeTARImpl, kXPPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kXPPageItemAdornmentImpl, kXPPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kXPDropShadowAdornmentImpl, kXPPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kXPVignetteAdornmentImpl, kXPPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kXPSetDropShadowCmdImpl, kXPPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kXPSetDropShadowCmdDataImpl, kXPPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kXPSetBasicAttributesCmdImpl, kXPPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kXPSetBasicAttributesCmdDataImpl, kXPPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kXPSetVignetteCmdImpl, kXPPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kXPSetVignetteCmdDataImpl, kXPPrefix + 23)
// OBSOLETE: DECLARE_PMID(kImplementationIDSpace, kXPFlattenerSetupImpl, kXPPrefix + 24)
// OBSOLETE: DECLARE_PMID(kImplementationIDSpace, kXPFlattenerSetupServiceImpl, kXPPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kXPAdornmentFlattenerUsageImpl, kXPPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kXPManagerImpl, kXPPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kXPPreferencesImpl, kXPPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kXPDocPreferencesImpl, kXPPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kXPSetPreferencesCmdImpl, kXPPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kXPSetPreferencesCmdDataImpl, kXPPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kXPAttributeSuiteASBImpl, kXPPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kXPAttributeSuiteLayoutCSBImpl, kXPPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kXPAttributeSuiteDefaultCSBImpl, kXPPrefix + 36)
// OBSOLETE: DECLARE_PMID(kImplementationIDSpace, kXPAttributePrePostImpl, kXPPrefix + 37)
// OBSOLETE: Moved to output preview. DECLARE_PMID(kImplementationIDSpace, kXPWindowOPPSettingsImpl, kXPPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kXPDocObserverImpl, kXPPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kXPStartupServiceImpl, kXPPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kXPStartupShutdownImpl, kXPPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kXPItemXPChangedCmdImpl, kXPPrefix + 42)
//replaced with itemxpprepost DECLARE_PMID(kImplementationIDSpace, kXPInvalItemCmdImpl, kXPPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kXPPrefsScriptProviderImpl, kXPPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kXPAttrInfoImpl, kXPPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kDropShadowAttrInfoImpl, kXPPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kVignetteAttrInfoImpl, kXPPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kXPFlattenerSettingsScrProvImpl, kXPPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kXPAttrScriptProviderImpl, kXPPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kXPFlattenerSettingsImpl, kXPPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kXPFlattenerSettingsPersistImpl, kXPPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kXPFlattenerStyleLockInfoImpl, kXPPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kXPFlattenerStyleListMgrImpl, kXPPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kXPFlattenerStyleSetNameCmdImpl, kXPPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kXPFlattenerStyleAddCmdImpl, kXPPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kXPFlattenerStyleEditCmdImpl, kXPPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kXPFlattenerStyleDeleteCmdImpl, kXPPrefix + 57)
// DECLARE_PMID(kImplementationIDSpace, kXPFlattenerStyleCmdDataImpl, kXPPrefix + 58)
// OBSOLETE: DECLARE_PMID(kImplementationIDSpace, kXPShadowColorAttrPrePostImpl, kXPPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kXPFlattenerSettingsSetCmdImpl, kXPPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kXPItemXPPrePostCmdImpl, kXPPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kXPItemXPPrePostCmdDataImpl, kXPPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kXPTestViewPortAttributesImpl, kXPPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kFlattenerStyleNewWSResponderImpl, kXPPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kXPPhase2ConversionImpl, kXPPrefix + 65)

DECLARE_PMID(kImplementationIDSpace, kXPAttributeSuiteASBSelectionExtImpl, kXPPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kXPAttributeSuiteLayoutSelectionExtImpl, kXPPrefix + 69)

DECLARE_PMID(kImplementationIDSpace, kXPUtilsImpl, kXPPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kXPAttributeUtilsImpl, kXPPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kXPPrivateUtilsImpl, kXPPrefix + 72)

DECLARE_PMID(kImplementationIDSpace, kXPAttributeSuiteDefaultSelectionExtImpl, kXPPrefix + 73)

DECLARE_PMID(kImplementationIDSpace, kFlattenerSettingsScriptProviderImpl, kXPPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kFlattenerPropScriptProviderImpl, kXPPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kFlattenerStyleScriptImpl, kXPPrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kFlattenerStyleScriptProviderImpl, kXPPrefix + 77)
DECLARE_PMID(kImplementationIDSpace, kXPFC_SettingsScriptProviderImpl, kXPPrefix + 78)
//gap
DECLARE_PMID(kImplementationIDSpace, kFlattenerSettingsSpreadAddOnImpl, kXPPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kXPCantDoOPPAlertImpl, kXPPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kXPPageItemInkResourcesImpl, kXPPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kXPDropShadowInkResourcesImpl, kXPPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kXPWindowScriptProviderImpl, kXPPrefix + 85)
DECLARE_PMID(kImplementationIDSpace, kXPNewDocResponderImpl, kXPPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kXPCodeConversionProviderImpl, kXPPrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kXPAttributeFacadeImpl, kXPPrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kXPSetAttributesCmdImpl, kXPPrefix + 89)
DECLARE_PMID(kImplementationIDSpace, kXPSetAttributesCmdDataImpl, kXPPrefix + 90)
DECLARE_PMID(kImplementationIDSpace, kXPSettingsScriptProviderImpl, kXPPrefix + 91)
DECLARE_PMID(kImplementationIDSpace, kXPInnerEffectsAdornmentImpl, kXPPrefix + 92)
DECLARE_PMID(kImplementationIDSpace, kXPInnerEffectsInkResourcesImpl, kXPPrefix + 93)
DECLARE_PMID(kImplementationIDSpace, kOpacityGradientStopScriptProviderImpl, kXPPrefix + 94)
DECLARE_PMID(kImplementationIDSpace, kOpacityGradientStopsImpl, kXPPrefix + 95)
DECLARE_PMID(kImplementationIDSpace, kOpacityGradientStopScriptImpl, kXPPrefix + 96)
DECLARE_PMID(kImplementationIDSpace, kXPExportSignalProviderImpl, kXPPrefix + 97)
DECLARE_PMID(kImplementationIDSpace, kXPExportSignalResponderImpl, kXPPrefix + 98)
DECLARE_PMID(kImplementationIDSpace, kXPInternalUtilsImpl, kXPPrefix + 99)
DECLARE_PMID(kImplementationIDSpace, kXPAlternativeADXYScriptProviderImpl,			kXPPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kXPFlattenerUtilsImpl, kXPPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kXPFlattenerUtilsViewPortAttrImpl, kXPPrefix + 102)

// <Widget ID>
DECLARE_PMID(kWidgetIDSpace, kXPTooManySpotsAlertID, kXPPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kXPCantDoOPPAlertID, kXPPrefix + 2)

// <ViewPortAttr ID>
// ViewPortAttrIDs
DECLARE_PMID(kViewPortAttrIDSpace, kXPIsMaskPortVPAttr, kXPPrefix + 1)
DECLARE_PMID(kViewPortAttrIDSpace, kXPEffectsResolutionVPAttr, kXPPrefix + 2)
DECLARE_PMID(kViewPortAttrIDSpace, kXPIsolationGroupDepthVPAttr, kXPPrefix + 3)
DECLARE_PMID(kViewPortAttrIDSpace, kXPIsolationGroupColorFamilyVPAttr, kXPPrefix + 4)
DECLARE_PMID(kViewPortAttrIDSpace, kXPCMYKMattingVPAttr, kXPPrefix + 5)
DECLARE_PMID(kViewPortAttrIDSpace, kXPFlattenerOffVPAttr, kXPPrefix + 6)
DECLARE_PMID(kViewPortAttrIDSpace, kXPWantCMYKMattingVPAttr, kXPPrefix + 7)
DECLARE_PMID(kViewPortAttrIDSpace, kXPSuppressSpreadLevelSetupVPAttr, kXPPrefix + 8)
// When set, this will suppress drop shadows and feathers and any other effects.
// It's useful for when you want to generate a mask that doesn't include those effects.
DECLARE_PMID(kViewPortAttrIDSpace, kXPSuppressEffectsVPAttr, kXPPrefix + 9)
DECLARE_PMID(kViewPortAttrIDSpace, kXPMaskingTargetVPAttr, kXPPrefix + 10)
DECLARE_PMID(kViewPortAttrIDSpace, kXPCollectingInnerFXArtVPAttr, kXPPrefix + 11)
DECLARE_PMID(kViewPortAttrIDSpace, kXPNeedPathReissueVPAttr, kXPPrefix + 12)
DECLARE_PMID(kViewPortAttrIDSpace, kXPNoTextInAlphaServersVPAttr, kXPPrefix + 13)
DECLARE_PMID(kViewPortAttrIDSpace, kXPOutlineInnerEffectTextVPAttr, kXPPrefix + 14)
DECLARE_PMID(kViewPortAttrIDSpace, kXPForceOffVPAttr, kXPPrefix + 15)
DECLARE_PMID(kViewPortAttrIDSpace, kXPForcePrintIsoGroupVPAttr, kXPPrefix + 16)

//
//Script Element IDs
//

//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kXPDefaultContainerObjectScriptElement,					kXPPrefix + 39)
DECLARE_PMID(kScriptInfoIDSpace, kFlattenerStyleObjectScriptElement,						kXPPrefix + 40)
DECLARE_PMID(kScriptInfoIDSpace, kFlattenerPrefsObjectScriptElement,						kXPPrefix + 41)
DECLARE_PMID(kScriptInfoIDSpace, kXPPrefsObjectScriptElement,								kXPPrefix + 42)
DECLARE_PMID(kScriptInfoIDSpace, kXPPageItemSettingsObjectScriptElement,					kXPPrefix + 43)
DECLARE_PMID(kScriptInfoIDSpace, kXPStrokeSettingsObjectScriptElement,						kXPPrefix + 44)
DECLARE_PMID(kScriptInfoIDSpace, kXPFillSettingsObjectScriptElement,						kXPPrefix + 45)
DECLARE_PMID(kScriptInfoIDSpace, kXPBlendingSettingsObjectScriptElement,					kXPPrefix + 46)
DECLARE_PMID(kScriptInfoIDSpace, kXPDropShadowSettingsObjectScriptElement,					kXPPrefix + 47)
DECLARE_PMID(kScriptInfoIDSpace, kXPFeatherSettingsObjectScriptElement,						kXPPrefix + 48)
DECLARE_PMID(kScriptInfoIDSpace, kXPInnerShadowSettingsObjectScriptElement,					kXPPrefix + 49)
DECLARE_PMID(kScriptInfoIDSpace, kXPOuterGlowSettingsObjectScriptElement,					kXPPrefix + 50)
DECLARE_PMID(kScriptInfoIDSpace, kXPInnerGlowSettingsObjectScriptElement,					kXPPrefix + 51)
DECLARE_PMID(kScriptInfoIDSpace, kXPBevelEmbossSettingsObjectScriptElement,					kXPPrefix + 52)
DECLARE_PMID(kScriptInfoIDSpace, kXPSatinSettingsObjectScriptElement,						kXPPrefix + 53)
DECLARE_PMID(kScriptInfoIDSpace, kXPContentSettingsObjectScriptElement,						kXPPrefix + 54)
DECLARE_PMID(kScriptInfoIDSpace, kXPDirectionalFeatherSettingsObjectScriptElement,			kXPPrefix + 55)
DECLARE_PMID(kScriptInfoIDSpace, kXPGradientFeatherSettingsObjectScriptElement,				kXPPrefix + 56)
DECLARE_PMID(kScriptInfoIDSpace, kXPFC_PageItemSettingsObjectScriptElement,					kXPPrefix + 57)
DECLARE_PMID(kScriptInfoIDSpace, kXPFC_StrokeSettingsObjectScriptElement,					kXPPrefix + 58)
DECLARE_PMID(kScriptInfoIDSpace, kXPFC_FillSettingsObjectScriptElement,						kXPPrefix + 59)
DECLARE_PMID(kScriptInfoIDSpace, kXPFC_ContentSettingsObjectScriptElement,					kXPPrefix + 60)
DECLARE_PMID(kScriptInfoIDSpace, kXPFC_BlendingSettingsObjectScriptElement,					kXPPrefix + 61)
DECLARE_PMID(kScriptInfoIDSpace, kXPFC_DropShadowSettingsObjectScriptElement,				kXPPrefix + 62)
DECLARE_PMID(kScriptInfoIDSpace, kXPFC_FeatherSettingsObjectScriptElement,					kXPPrefix + 63)
DECLARE_PMID(kScriptInfoIDSpace, kXPFC_InnerShadowSettingsObjectScriptElement,				kXPPrefix + 64)
DECLARE_PMID(kScriptInfoIDSpace, kXPFC_OuterGlowSettingsObjectScriptElement,				kXPPrefix + 65)
DECLARE_PMID(kScriptInfoIDSpace, kXPFC_InnerGlowSettingsObjectScriptElement,				kXPPrefix + 66)
DECLARE_PMID(kScriptInfoIDSpace, kXPFC_BevelEmbossSettingsObjectScriptElement,				kXPPrefix + 67)
DECLARE_PMID(kScriptInfoIDSpace, kXPFC_SatinSettingsObjectScriptElement,					kXPPrefix + 68)
DECLARE_PMID(kScriptInfoIDSpace, kXPFC_DirectionalFeatherSettingsObjectScriptElement,		kXPPrefix + 69)
DECLARE_PMID(kScriptInfoIDSpace, kXPFC_GradientFeatherSettingsObjectScriptElement,			kXPPrefix + 70)
//gap

//Events

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kFlattenerPrefsPropertyScriptElement,						kXPPrefix + 140)
DECLARE_PMID(kScriptInfoIDSpace, kFlattenerLevelPropertyScriptElement,						kXPPrefix + 141)
DECLARE_PMID(kScriptInfoIDSpace, kFlattenerResolutionPropertyScriptElement,					kXPPrefix + 142)
DECLARE_PMID(kScriptInfoIDSpace, kGradientResolutionPropertyScriptElement,					kXPPrefix + 143)
DECLARE_PMID(kScriptInfoIDSpace, kClipComplexRegionsPropertyScriptElement,					kXPPrefix + 144)
DECLARE_PMID(kScriptInfoIDSpace, kConvertStrokesToFillsPropertyScriptElement,				kXPPrefix + 145)
DECLARE_PMID(kScriptInfoIDSpace, kTextToOutlinesPropertyScriptElement,						kXPPrefix + 146)
DECLARE_PMID(kScriptInfoIDSpace, kXPPrefsPropertyScriptElement,								kXPPrefix + 147)
DECLARE_PMID(kScriptInfoIDSpace, kBlendSpacePropertyScriptElement,							kXPPrefix + 148)
// Note: The following script elements appear to be duplicated below; but these are the *old* script
// elements hanging off the page item in INX.  The ones below are the *new* ones that reside in the
// new effects hierarchy for Cobalt.  (The name of the property changed in the rearrangement, thus
// we need old and new versions.)
DECLARE_PMID(kScriptInfoIDSpace, kBlendModePropertyScriptElement,							kXPPrefix + 149)
DECLARE_PMID(kScriptInfoIDSpace, kOpacityPropertyScriptElement,								kXPPrefix + 150)
DECLARE_PMID(kScriptInfoIDSpace, kKnockoutGroupPropertyScriptElement,						kXPPrefix + 151)
DECLARE_PMID(kScriptInfoIDSpace, kIsolateBlendingPropertyScriptElement,						kXPPrefix + 152)
DECLARE_PMID(kScriptInfoIDSpace, kShadowModePropertyScriptElement,							kXPPrefix + 153)
DECLARE_PMID(kScriptInfoIDSpace, kShadowBlendModePropertyScriptElement,						kXPPrefix + 154)
DECLARE_PMID(kScriptInfoIDSpace, kShadowXOffsetPropertyScriptElement,						kXPPrefix + 155)
DECLARE_PMID(kScriptInfoIDSpace, kShadowYOffsetPropertyScriptElement,						kXPPrefix + 156)
DECLARE_PMID(kScriptInfoIDSpace, kShadowBlurRadiusPropertyScriptElement,					kXPPrefix + 157)
DECLARE_PMID(kScriptInfoIDSpace, kShadowColorPropertyScriptElement,							kXPPrefix + 158)
DECLARE_PMID(kScriptInfoIDSpace, kShadowOpacityPropertyScriptElement,						kXPPrefix + 159)
DECLARE_PMID(kScriptInfoIDSpace, kFeatherModePropertyScriptElement,							kXPPrefix + 160)
DECLARE_PMID(kScriptInfoIDSpace, kFeatherWidthPropertyScriptElement,						kXPPrefix + 161)
DECLARE_PMID(kScriptInfoIDSpace, kFeatherCornerTypePropertyScriptElement,					kXPPrefix + 162)
DECLARE_PMID(kScriptInfoIDSpace, kSpreadFlattenerOverridePropertyScriptElement,				kXPPrefix + 163)
DECLARE_PMID(kScriptInfoIDSpace, kShadowSpreadPropertyScriptElement,						kXPPrefix + 164)
DECLARE_PMID(kScriptInfoIDSpace, kShadowNoisePropertyScriptElement,							kXPPrefix + 165)
DECLARE_PMID(kScriptInfoIDSpace, kFeatherNoisePropertyScriptElement,						kXPPrefix + 166)
// The following are the new elements for Cobalt.
DECLARE_PMID(kScriptInfoIDSpace, kBlendingBlendModePropertyScriptElement,					kXPPrefix + 167)
DECLARE_PMID(kScriptInfoIDSpace, kBlendingOpacityPropertyScriptElement,						kXPPrefix + 168)
DECLARE_PMID(kScriptInfoIDSpace, kBlendingKnockoutGroupPropertyScriptElement,				kXPPrefix + 169)
DECLARE_PMID(kScriptInfoIDSpace, kBlendingIsolationGroupPropertyScriptElement,				kXPPrefix + 170)
DECLARE_PMID(kScriptInfoIDSpace, kDropShadowModePropertyScriptElement,						kXPPrefix + 171)
DECLARE_PMID(kScriptInfoIDSpace, kDropShadowBlendModePropertyScriptElement,					kXPPrefix + 172)
DECLARE_PMID(kScriptInfoIDSpace, kDropShadowOpacityPropertyScriptElement,					kXPPrefix + 173)
DECLARE_PMID(kScriptInfoIDSpace, kDropShadowXOffsetPropertyScriptElement,					kXPPrefix + 174)
DECLARE_PMID(kScriptInfoIDSpace, kDropShadowYOffsetPropertyScriptElement,					kXPPrefix + 175)
DECLARE_PMID(kScriptInfoIDSpace, kDropShadowBlurRadiusPropertyScriptElement,				kXPPrefix + 176)
DECLARE_PMID(kScriptInfoIDSpace, kDropShadowColorPropertyScriptElement,						kXPPrefix + 177)
DECLARE_PMID(kScriptInfoIDSpace, kDropShadowNoisePropertyScriptElement,						kXPPrefix + 178)
DECLARE_PMID(kScriptInfoIDSpace, kDropShadowSpreadPropertyScriptElement,					kXPPrefix + 179)
DECLARE_PMID(kScriptInfoIDSpace, kDropShadowUseGlobalLightPropertyScriptElement,			kXPPrefix + 180)
DECLARE_PMID(kScriptInfoIDSpace, k50FeatherModePropertyScriptElement,						kXPPrefix + 181)
DECLARE_PMID(kScriptInfoIDSpace, k50FeatherWidthPropertyScriptElement,						kXPPrefix + 182)
DECLARE_PMID(kScriptInfoIDSpace, k50FeatherCornerTypePropertyScriptElement,					kXPPrefix + 183)
DECLARE_PMID(kScriptInfoIDSpace, k50FeatherNoisePropertyScriptElement,						kXPPrefix + 184)
DECLARE_PMID(kScriptInfoIDSpace, kInnerShadowApplyPropertyScriptElement,					kXPPrefix + 185)
DECLARE_PMID(kScriptInfoIDSpace, kInnerShadowColorPropertyScriptElement,					kXPPrefix + 186)
DECLARE_PMID(kScriptInfoIDSpace, kInnerShadowBlendModePropertyScriptElement,				kXPPrefix + 187)
DECLARE_PMID(kScriptInfoIDSpace, kInnerShadowOpacityPropertyScriptElement,					kXPPrefix + 188)
DECLARE_PMID(kScriptInfoIDSpace, kInnerShadowAnglePropertyScriptElement,					kXPPrefix + 189)
DECLARE_PMID(kScriptInfoIDSpace, kInnerShadowDistancePropertyScriptElement,					kXPPrefix + 190)
DECLARE_PMID(kScriptInfoIDSpace, kInnerShadowUseGlobalLightPropertyScriptElement,			kXPPrefix + 191)
DECLARE_PMID(kScriptInfoIDSpace, kInnerShadowChokePropertyScriptElement,					kXPPrefix + 192)
DECLARE_PMID(kScriptInfoIDSpace, kInnerShadowSizePropertyScriptElement,						kXPPrefix + 193)
DECLARE_PMID(kScriptInfoIDSpace, kInnerShadowNoisePropertyScriptElement,					kXPPrefix + 194)
DECLARE_PMID(kScriptInfoIDSpace, kOuterGlowApplyPropertyScriptElement,						kXPPrefix + 195)
DECLARE_PMID(kScriptInfoIDSpace, kOuterGlowBlendModePropertyScriptElement,					kXPPrefix + 196)
DECLARE_PMID(kScriptInfoIDSpace, kOuterGlowOpacityPropertyScriptElement,					kXPPrefix + 197)
DECLARE_PMID(kScriptInfoIDSpace, kOuterGlowNoisePropertyScriptElement,						kXPPrefix + 198)
DECLARE_PMID(kScriptInfoIDSpace, kOuterGlowColorPropertyScriptElement,						kXPPrefix + 199)
DECLARE_PMID(kScriptInfoIDSpace, kOuterGlowTechniquePropertyScriptElement,					kXPPrefix + 200)
DECLARE_PMID(kScriptInfoIDSpace, kOuterGlowSpreadPropertyScriptElement,						kXPPrefix + 201)
DECLARE_PMID(kScriptInfoIDSpace, kOuterGlowSizePropertyScriptElement,						kXPPrefix + 202)
DECLARE_PMID(kScriptInfoIDSpace, kInnerGlowApplyPropertyScriptElement,						kXPPrefix + 203)
DECLARE_PMID(kScriptInfoIDSpace, kInnerGlowBlendModePropertyScriptElement,					kXPPrefix + 204)
DECLARE_PMID(kScriptInfoIDSpace, kInnerGlowOpacityPropertyScriptElement,					kXPPrefix + 205)
DECLARE_PMID(kScriptInfoIDSpace, kInnerGlowNoisePropertyScriptElement,						kXPPrefix + 206)
DECLARE_PMID(kScriptInfoIDSpace, kInnerGlowColorPropertyScriptElement,						kXPPrefix + 207)
DECLARE_PMID(kScriptInfoIDSpace, kInnerGlowTechniquePropertyScriptElement,					kXPPrefix + 208)
DECLARE_PMID(kScriptInfoIDSpace, kInnerGlowSpreadPropertyScriptElement,						kXPPrefix + 209)
DECLARE_PMID(kScriptInfoIDSpace, kInnerGlowSizePropertyScriptElement,						kXPPrefix + 210)
DECLARE_PMID(kScriptInfoIDSpace, kInnerGlowSourcePropertyScriptElement,						kXPPrefix + 211)
DECLARE_PMID(kScriptInfoIDSpace, kBevelEmbossApplyPropertyScriptElement,					kXPPrefix + 212)
DECLARE_PMID(kScriptInfoIDSpace, kBevelEmbossStylePropertyScriptElement,					kXPPrefix + 213)
DECLARE_PMID(kScriptInfoIDSpace, kBevelEmbossTechniquePropertyScriptElement,				kXPPrefix + 214)
DECLARE_PMID(kScriptInfoIDSpace, kBevelEmbossDepthPropertyScriptElement,					kXPPrefix + 215)
DECLARE_PMID(kScriptInfoIDSpace, kBevelEmbossDirectionPropertyScriptElement,				kXPPrefix + 216)
DECLARE_PMID(kScriptInfoIDSpace, kBevelEmbossSizePropertyScriptElement,						kXPPrefix + 217)
DECLARE_PMID(kScriptInfoIDSpace, kBevelEmbossSoftenPropertyScriptElement,					kXPPrefix + 218)
DECLARE_PMID(kScriptInfoIDSpace, kBevelEmbossAnglePropertyScriptElement,					kXPPrefix + 219)
//Enums
DECLARE_PMID(kScriptInfoIDSpace, kFlattenerLevelEnumScriptElement,							kXPPrefix + 220)
DECLARE_PMID(kScriptInfoIDSpace, kXPBlendSpaceEnumScriptElement,							kXPPrefix + 221)
DECLARE_PMID(kScriptInfoIDSpace, kXPBlendModeEnumScriptElement,								kXPPrefix + 222)
DECLARE_PMID(kScriptInfoIDSpace, kXPShadowModeEnumScriptElement,							kXPPrefix + 223)
DECLARE_PMID(kScriptInfoIDSpace, kXPFeatherModeEnumScriptElement,							kXPPrefix + 224)
DECLARE_PMID(kScriptInfoIDSpace, kXPCornersEnumScriptElement,								kXPPrefix + 225)
DECLARE_PMID(kScriptInfoIDSpace, kSpreadFlattenerLevelEnumScriptElement,					kXPPrefix + 226)
DECLARE_PMID(kScriptInfoIDSpace, kXPGlowTechniqueEnumScriptElement,							kXPPrefix + 227)
DECLARE_PMID(kScriptInfoIDSpace, kXPInnerGlowSourceEnumScriptElement,						kXPPrefix + 228)
DECLARE_PMID(kScriptInfoIDSpace, kXPBevelEmbossStyleEnumScriptElement,						kXPPrefix + 229)
DECLARE_PMID(kScriptInfoIDSpace, kXPBevelEmbossTechniqueEnumScriptElement,					kXPPrefix + 230)
DECLARE_PMID(kScriptInfoIDSpace, kXPBevelEmbossDirectionEnumScriptElement,					kXPPrefix + 231)
DECLARE_PMID(kScriptInfoIDSpace, kXPFollowShapeModeEnumScriptElement,						kXPPrefix + 232)
//gap

DECLARE_PMID(kScriptInfoIDSpace, kBevelEmbossAltitudePropertyScriptElement,					kXPPrefix2 + 0)
DECLARE_PMID(kScriptInfoIDSpace, kBevelEmbossUseGlobalLightPropertyScriptElement,			kXPPrefix2 + 1)
DECLARE_PMID(kScriptInfoIDSpace, kBevelEmbossHighlightColorPropertyScriptElement,			kXPPrefix2 + 2)
DECLARE_PMID(kScriptInfoIDSpace, kBevelEmbossHighlightBlendModePropertyScriptElement,		kXPPrefix2 + 3)
DECLARE_PMID(kScriptInfoIDSpace, kBevelEmbossHighlightOpacityPropertyScriptElement,			kXPPrefix2 + 4)
DECLARE_PMID(kScriptInfoIDSpace, kBevelEmbossShadowColorPropertyScriptElement,				kXPPrefix2 + 5)
DECLARE_PMID(kScriptInfoIDSpace, kBevelEmbossShadowBlendModePropertyScriptElement,			kXPPrefix2 + 6)
DECLARE_PMID(kScriptInfoIDSpace, kBevelEmbossShadowOpacityPropertyScriptElement,			kXPPrefix2 + 7)
DECLARE_PMID(kScriptInfoIDSpace, kSatinApplyPropertyScriptElement,							kXPPrefix2 + 8)
DECLARE_PMID(kScriptInfoIDSpace, kSatinColorPropertyScriptElement,							kXPPrefix2 + 9)
DECLARE_PMID(kScriptInfoIDSpace, kSatinBlendModePropertyScriptElement,						kXPPrefix2 + 10)
DECLARE_PMID(kScriptInfoIDSpace, kSatinOpacityPropertyScriptElement,						kXPPrefix2 + 11)
DECLARE_PMID(kScriptInfoIDSpace, kSatinAnglePropertyScriptElement,							kXPPrefix2 + 12)
DECLARE_PMID(kScriptInfoIDSpace, kSatinDistancePropertyScriptElement,						kXPPrefix2 + 13)
DECLARE_PMID(kScriptInfoIDSpace, kSatinSizePropertyScriptElement,							kXPPrefix2 + 14)
DECLARE_PMID(kScriptInfoIDSpace, kSatinInvertPropertyScriptElement,							kXPPrefix2 + 15)
DECLARE_PMID(kScriptInfoIDSpace, kDropShadowKOPropertyScriptElement,						kXPPrefix2 + 16)
// These point to the nodes in the new hierarchical effects structure.
DECLARE_PMID(kScriptInfoIDSpace, kXPPageItemSettingsPropertyScriptElement,					kXPPrefix2 + 17)
DECLARE_PMID(kScriptInfoIDSpace, kXPStrokeSettingsPropertyScriptElement,					kXPPrefix2 + 18)
DECLARE_PMID(kScriptInfoIDSpace, kXPFillSettingsPropertyScriptElement,						kXPPrefix2 + 19)
DECLARE_PMID(kScriptInfoIDSpace, kXPContentSettingsPropertyScriptElement,					kXPPrefix2 + 20)
DECLARE_PMID(kScriptInfoIDSpace, kXPBlendingSettingsPropertyScriptElement,					kXPPrefix2 + 21)
DECLARE_PMID(kScriptInfoIDSpace, kXPDropShadowSettingsPropertyScriptElement,				kXPPrefix2 + 22)
DECLARE_PMID(kScriptInfoIDSpace, kXPFeatherSettingsPropertyScriptElement,					kXPPrefix2 + 23)
DECLARE_PMID(kScriptInfoIDSpace, kXPInnerShadowSettingsPropertyScriptElement,				kXPPrefix2 + 24)
DECLARE_PMID(kScriptInfoIDSpace, kXPOuterGlowSettingsPropertyScriptElement,					kXPPrefix2 + 25)
DECLARE_PMID(kScriptInfoIDSpace, kXPInnerGlowSettingsPropertyScriptElement,					kXPPrefix2 + 26)
DECLARE_PMID(kScriptInfoIDSpace, kXPBevelEmbossSettingsPropertyScriptElement,				kXPPrefix2 + 27)
DECLARE_PMID(kScriptInfoIDSpace, kXPSatinSettingsPropertyScriptElement,						kXPPrefix2 + 28)
DECLARE_PMID(kScriptInfoIDSpace, kXPDirectionalFeatherSettingsPropertyScriptElement,		kXPPrefix2 + 29)
// Back to properties
DECLARE_PMID(kScriptInfoIDSpace, kDirectionalFeatherApplyPropertyScriptElement,				kXPPrefix2 + 30)
DECLARE_PMID(kScriptInfoIDSpace, kDirectionalFeatherWidthPropertyScriptElement,				kXPPrefix2 + 31)
DECLARE_PMID(kScriptInfoIDSpace, kDirectionalFeatherAnglePropertyScriptElement,				kXPPrefix2 + 32)
DECLARE_PMID(kScriptInfoIDSpace, kDirectionalFeatherFollowShapePropertyScriptElement,		kXPPrefix2 + 33)
DECLARE_PMID(kScriptInfoIDSpace, kDirectionalFeatherNoisePropertyScriptElement,				kXPPrefix2 + 34)
// Gradient feather nodes & properties
DECLARE_PMID(kScriptInfoIDSpace, kXPGradientFeatherSettingsPropertyScriptElement,			kXPPrefix2 + 35)
DECLARE_PMID(kScriptInfoIDSpace, kGradientFeatherApplyPropertyScriptElement,				kXPPrefix2 + 36)
DECLARE_PMID(kScriptInfoIDSpace, kGradientFeatherTypePropertyScriptElement,					kXPPrefix2 + 37)
DECLARE_PMID(kScriptInfoIDSpace, kGradientFeatherOpacityStopsPropertyScriptElement,			kXPPrefix2 + 38)
DECLARE_PMID(kScriptInfoIDSpace, kGradientFeatherAnglePropertyScriptElement,				kXPPrefix2 + 39)
DECLARE_PMID(kScriptInfoIDSpace, kGradientFeatherLengthPropertyScriptElement,				kXPPrefix2 + 40)
DECLARE_PMID(kScriptInfoIDSpace, kGradientFeatherCenterPropertyScriptElement,				kXPPrefix2 + 41)
DECLARE_PMID(kScriptInfoIDSpace, kGradientFeatherRadiusPropertyScriptElement,				kXPPrefix2 + 42)
DECLARE_PMID(kScriptInfoIDSpace, kGradientFeatherHiliteAnglePropertyScriptElement,			kXPPrefix2 + 43)
DECLARE_PMID(kScriptInfoIDSpace, kGradientFeatherHiliteLengthPropertyScriptElement,			kXPPrefix2 + 44)
// Opacity gradient data
DECLARE_PMID(kScriptInfoIDSpace, kOpacityGradientStopObjectScriptElement,					kXPPrefix2 + 45)
DECLARE_PMID(kScriptInfoIDSpace, kOpacityGradientStopOpacityPropertyScriptElement,			kXPPrefix2 + 46)
DECLARE_PMID(kScriptInfoIDSpace, kOpacityGradientStopPositionPropertyScriptElement,			kXPPrefix2 + 47)
DECLARE_PMID(kScriptInfoIDSpace, kOpacityGradientStopMidpointPropertyScriptElement,			kXPPrefix2 + 48)
// Global light
DECLARE_PMID(kScriptInfoIDSpace, kGlobalLightAnglePropertyScriptElement,					kXPPrefix2 + 49)
DECLARE_PMID(kScriptInfoIDSpace, kGlobalLightAltitudePropertyScriptElement,					kXPPrefix2 + 50)
// More attributes
DECLARE_PMID(kScriptInfoIDSpace, kFeatherChokePropertyScriptElement,						kXPPrefix2 + 51)
DECLARE_PMID(kScriptInfoIDSpace, kDirectionalFeatherWidthLeftPropertyScriptElement,			kXPPrefix2 + 52)
DECLARE_PMID(kScriptInfoIDSpace, kDirectionalFeatherWidthRightPropertyScriptElement,		kXPPrefix2 + 53)
DECLARE_PMID(kScriptInfoIDSpace, kDirectionalFeatherWidthTopPropertyScriptElement,			kXPPrefix2 + 54)
DECLARE_PMID(kScriptInfoIDSpace, kDirectionalFeatherWidthBottomPropertyScriptElement,		kXPPrefix2 + 55)
DECLARE_PMID(kScriptInfoIDSpace, kDirectionalFeatherChokePropertyScriptElement,				kXPPrefix2 + 56)
DECLARE_PMID(kScriptInfoIDSpace, kXPDefaultContainerPropertyScriptElement,					kXPPrefix2 + 57)
DECLARE_PMID(kScriptInfoIDSpace, kDropShadowHonorFXPropertyScriptElement,					kXPPrefix2 + 58)
// Special 'derived' attributes (not real attributes, translated at scripting level)
DECLARE_PMID(kScriptInfoIDSpace, kDropShadowDistancePropertyScriptElement,					kXPPrefix2 + 59)
DECLARE_PMID(kScriptInfoIDSpace, kDropShadowAnglePropertyScriptElement,						kXPPrefix2 + 60)
DECLARE_PMID(kScriptInfoIDSpace, kInnerShadowXOffsetPropertyScriptElement,					kXPPrefix2 + 61)
DECLARE_PMID(kScriptInfoIDSpace, kInnerShadowYOffsetPropertyScriptElement,					kXPPrefix2 + 62)
//FC Nodes
DECLARE_PMID(kScriptInfoIDSpace, kXPFC_PageItemSettingsPropertyScriptElement,				kXPPrefix2 + 63)
DECLARE_PMID(kScriptInfoIDSpace, kXPFC_StrokeSettingsPropertyScriptElement,					kXPPrefix2 + 64)
DECLARE_PMID(kScriptInfoIDSpace, kXPFC_FillSettingsPropertyScriptElement,					kXPPrefix2 + 65)
DECLARE_PMID(kScriptInfoIDSpace, kXPFC_ContentSettingsPropertyScriptElement,				kXPPrefix2 + 66)
DECLARE_PMID(kScriptInfoIDSpace, kXPFC_BlendingSettingsPropertyScriptElement,				kXPPrefix2 + 67)
DECLARE_PMID(kScriptInfoIDSpace, kXPFC_DropShadowSettingsPropertyScriptElement,				kXPPrefix2 + 68)
DECLARE_PMID(kScriptInfoIDSpace, kXPFC_FeatherSettingsPropertyScriptElement,				kXPPrefix2 + 69)
DECLARE_PMID(kScriptInfoIDSpace, kXPFC_InnerShadowSettingsPropertyScriptElement,			kXPPrefix2 + 70)
DECLARE_PMID(kScriptInfoIDSpace, kXPFC_OuterGlowSettingsPropertyScriptElement,				kXPPrefix2 + 71)
DECLARE_PMID(kScriptInfoIDSpace, kXPFC_InnerGlowSettingsPropertyScriptElement,				kXPPrefix2 + 72)
DECLARE_PMID(kScriptInfoIDSpace, kXPFC_BevelEmbossSettingsPropertyScriptElement,			kXPPrefix2 + 73)
DECLARE_PMID(kScriptInfoIDSpace, kXPFC_SatinSettingsPropertyScriptElement,					kXPPrefix2 + 74)
DECLARE_PMID(kScriptInfoIDSpace, kXPFC_DirectionalFeatherSettingsPropertyScriptElement,		kXPPrefix2 + 75)
DECLARE_PMID(kScriptInfoIDSpace, kXPFC_GradientFeatherSettingsPropertyScriptElement,		kXPPrefix2 + 76)
DECLARE_PMID(kScriptInfoIDSpace, kAddNothingEnumToXPPropsMetadataScriptElement,				kXPPrefix2 + 77)
DECLARE_PMID(kScriptInfoIDSpace, kAddNothingEnumToXPFC_PropsMetadataScriptElement,			kXPPrefix2 + 78)


//GUIDS
// {9E955039-6DBC-4988-B7D6-E8E13E700CC1}
#define kFlattenerSettings_CLSID { 0x9e955039, 0x6dbc, 0x4988, { 0xb7, 0xd6, 0xe8, 0xe1, 0x3e, 0x70, 0xc, 0xc1 } }
// {2841C44D-00CB-4faf-9B61-D889C7FA4F61}
#define kFlattenerStyle_CLSID { 0x2841c44d, 0xcb, 0x4faf, { 0x9b, 0x61, 0xd8, 0x89, 0xc7, 0xfa, 0x4f, 0x61 } }
// {6EBE0972-2FF7-4c88-B28D-BAC0B02DE562}
#define kFlattenerStyles_CLSID { 0x6ebe0972, 0x2ff7, 0x4c88, { 0xb2, 0x8d, 0xba, 0xc0, 0xb0, 0x2d, 0xe5, 0x62 } }
// {f42ea18c-cf8b-11d4-8950-00b0d02095de}
#define kXPPref_CLSID { 0xf42ea18c, 0xcf8b, 0x11d4, { 0x89, 0x50, 0x0, 0xb0, 0xd0, 0x20, 0x95, 0xde } }
// {908CD67F-C8A4-4852-A62A-1A86E7A56C24}
#define kXPPageItemSettings_CLSID { 0x908CD67F, 0xC8A4, 0x4852, { 0xA6, 0x2A, 0x1A, 0x86, 0xE7, 0xA5, 0x6C, 0x24}}
// {1D2811AD-F7E0-43ef-93B8-8971AA4BDE59}
#define kXPStrokeSettings_CLSID { 0x1D2811AD, 0xF7E0, 0x43ef, { 0x93, 0xB8, 0x89, 0x71, 0xAA, 0x4B, 0xDE, 0x59}}
// {6C9CF717-6B0C-4e6e-9D36-62B144CE3A2A}
#define kXPFillSettings_CLSID { 0x6C9CF717, 0x6B0C, 0x4e6e, { 0x9D, 0x36, 0x62, 0xB1, 0x44, 0xCE, 0x3A, 0x2A}}
// {5669E404-E901-4077-8D14-B08C1F2854FE}
#define kXPContentSettings_CLSID { 0x5669E404, 0xE901, 0x4077, { 0x8D, 0x14, 0xB0, 0x8C, 0x1F, 0x28, 0x54, 0xFE} }
// {65F068E4-DAA2-4276-8402-F0B4E43AE915}
#define kXPBlendingSettings_CLSID { 0x65F068E4, 0xDAA2, 0x4276, { 0x84, 0x02, 0xF0, 0xB4, 0xE4, 0x3A, 0xE9, 0x15 } }
// {48684C51-29BA-41d7-B97A-A00506A903BB}
#define kXPDropShadowSettings_CLSID { 0x48684C51, 0x29BA, 0x41d7, { 0xB9, 0x7A, 0xA0, 0x05, 0x06, 0xA9, 0x03, 0xBB } }
// {6572C2FD-37E5-48aa-B45C-A4E7DDCEACC2}
#define kXPFeatherSettings_CLSID { 0x6572C2FD, 0x37E5, 0x48aa, { 0xB4, 0x5C, 0xA4, 0xE7, 0xDD, 0xCE, 0xAC, 0xC2 } }
// {43094EB8-B4DB-4261-BDEC-911ACB58555D}
#define kXPInnerShadowSettings_CLSID { 0x43094EB8, 0xB4DB, 0x4261, { 0xBD, 0xEC, 0x91, 0x1A, 0xCB, 0x58, 0x55, 0x5D } }
// {77A0E0E3-AADE-42aa-9928-929D74837039}
#define kXPOuterGlowSettings_CLSID { 0x77A0E0E3, 0xAADE, 0x42aa, { 0x99, 0x28, 0x92, 0x9D, 0x74, 0x83, 0x70, 0x39 } }
// {8148D6C4-29D3-47e5-870D-749F36E2EC4F}
#define kXPInnerGlowSettings_CLSID { 0x8148D6C4, 0x29D3, 0x47e5, { 0x87, 0x0D, 0x74, 0x9F, 0x36, 0xE2, 0xEC, 0x4F } }
// {FC0A7913-E840-4b78-9091-F26C59BC9293}
#define kXPBevelEmbossSettings_CLSID { 0xFC0A7913, 0xE840, 0x4b78, { 0x90, 0x91, 0xF2, 0x6C, 0x59, 0xBC, 0x92, 0x93 } }
// {9249E5FF-5E40-47cc-9713-C0B13C5BABD2}
#define kXPSatinSettings_CLSID { 0x9249E5FF, 0x5E40, 0x47cc, { 0x97, 0x13, 0xC0, 0xB1, 0x3C, 0x5B, 0xAB, 0xD2 } }
// {93019E4E-1C3E-45f5-9431-5FD511DCCA35}
#define kXPDirectionalFeatherSettings_CLSID { 0x93019E4E, 0x1C3E, 0x45f5, { 0x94, 0x31, 0x5F, 0xD5, 0x11, 0xDC, 0xCA, 0x35 } }
// {A8CC0B02-28D0-4f82-BACB-AE711B602A1B}
#define kXPGradientFeatherSettings_CLSID { 0xA8CC0B02, 0x28D0, 0x4f82, { 0xBA, 0xCB, 0xAE, 0x71, 0x1B, 0x60, 0x2A, 0x1B } }
// {C375C23A-C422-4a2e-A8E2-F3C20EACFD46}
#define kOpacityGradientStop_CLSID { 0xC375C23A, 0xC422, 0x4a2e, { 0xA8, 0xE2, 0xF3, 0xC2, 0x0E, 0xAC, 0xFD, 0x46} }
// {03D5546B-BDB1-488c-BF5C-A622B962B58C}
#define kOpacityGradientStops_CLSID { 0x03D5546B, 0xBDB1, 0x488c, { 0xBF, 0x5C, 0xA6, 0x22, 0xB9, 0x62, 0xB5, 0x8C } }
// {4CFD4056-2AF2-434e-8D91-15F8A0548BE1}
#define kXPDefaultContainer_CLSID { 0x4cfd4056, 0x2af2, 0x434e, { 0x8d, 0x91, 0x15, 0xf8, 0xa0, 0x54, 0x8b, 0xe1 } }

// {75D193B7-A3E1-4a9b-8400-A9A4B0E61B72}
#define kXPFC_PageItemSettings_CLSID { 0x75d193b7, 0xa3e1, 0x4a9b, { 0x84, 0x0, 0xa9, 0xa4, 0xb0, 0xe6, 0x1b, 0x72 } }
// {B1C1C975-8037-4103-B96E-D1C861ECB211}
#define kXPFC_StrokeSettings_CLSID { 0xb1c1c975, 0x8037, 0x4103, { 0xb9, 0x6e, 0xd1, 0xc8, 0x61, 0xec, 0xb2, 0x11 } }
// {98646CD0-DB2B-41c8-B774-F834E178C29F}
#define kXPFC_FillSettings_CLSID { 0x98646cd0, 0xdb2b, 0x41c8, { 0xb7, 0x74, 0xf8, 0x34, 0xe1, 0x78, 0xc2, 0x9f } }
// {A75E01D3-62A3-4d01-BC8B-73327CEDE0D3}
#define kXPFC_ContentSettings_CLSID { 0xa75e01d3, 0x62a3, 0x4d01, { 0xbc, 0x8b, 0x73, 0x32, 0x7c, 0xed, 0xe0, 0xd3 } }
// {D9409068-0D4D-4782-A81C-1CA0D736D283}
#define kXPFC_BlendingSettings_CLSID { 0xd9409068, 0xd4d, 0x4782, { 0xa8, 0x1c, 0x1c, 0xa0, 0xd7, 0x36, 0xd2, 0x83 } }
// {2703BF04-4585-4d38-93B3-73820FDED4BD}
#define kXPFC_DropShadowSettings_CLSID { 0x2703bf04, 0x4585, 0x4d38, { 0x93, 0xb3, 0x73, 0x82, 0xf, 0xde, 0xd4, 0xbd } }
// {6F2EE154-4911-4679-B36E-A4CAE0FE2259}
#define kXPFC_FeatherSettings_CLSID { 0x6f2ee154, 0x4911, 0x4679, { 0xb3, 0x6e, 0xa4, 0xca, 0xe0, 0xfe, 0x22, 0x59 } }
// {F4C0F4B2-964F-43db-A4A7-6BFC7CC09CD2}
#define kXPFC_InnerShadowSettings_CLSID { 0xf4c0f4b2, 0x964f, 0x43db, { 0xa4, 0xa7, 0x6b, 0xfc, 0x7c, 0xc0, 0x9c, 0xd2 } }
// {C4585392-4B16-4f6a-9191-311619BB989F}
#define kXPFC_OuterGlowSettings_CLSID { 0xc4585392, 0x4b16, 0x4f6a, { 0x91, 0x91, 0x31, 0x16, 0x19, 0xbb, 0x98, 0x9f } }
// {D3F3A468-B6F1-46b9-B855-7790F14EC052}
#define kXPFC_InnerGlowSettings_CLSID { 0xd3f3a468, 0xb6f1, 0x46b9, { 0xb8, 0x55, 0x77, 0x90, 0xf1, 0x4e, 0xc0, 0x52 } }
// {371E10A6-BE71-492f-8F35-866D579C9621}
#define kXPFC_BevelEmbossSettings_CLSID { 0x371e10a6, 0xbe71, 0x492f, { 0x8f, 0x35, 0x86, 0x6d, 0x57, 0x9c, 0x96, 0x21 } }
// {87536138-1998-40be-AFCB-9806846AA126}
#define kXPFC_SatinSettings_CLSID { 0x87536138, 0x1998, 0x40be, { 0xaf, 0xcb, 0x98, 0x6, 0x84, 0x6a, 0xa1, 0x26 } }
// {6A55918A-5DF6-461e-83E4-E38FA3496463}
#define kXPFC_DirectionalFeatherSettings_CLSID { 0x6a55918a, 0x5df6, 0x461e, { 0x83, 0xe4, 0xe3, 0x8f, 0xa3, 0x49, 0x64, 0x63 } }
// {7AC3C41B-9150-4dde-982A-4EFB0C68E4E0}
#define kXPFC_GradientFeatherSettings_CLSID { 0x7ac3c41b, 0x9150, 0x4dde, { 0x98, 0x2a, 0x4e, 0xfb, 0xc, 0x68, 0xe4, 0xe0 } }

enum TransparencyScriptIDs
{
	// Transparency
	c_BaseFlattenerProperties		= 'flBp',
	c_FlattenerSettings				= 'flSe',
	p_FlattenerSettings				= 'fsFS',
	c_FlattenerStyle				= 'flSt',
	c_FlattenerStyles				= 'flSs',
	c_XPDefaultContainer			= 'xpDC',
	c_OpacityGradientStops			= 'xpQo',
	c_OpacityGradientStop			= 'xpQp',

	c_PageItemTransparencySettings	= 'xpQa',
	c_StrokeTransparencySettings	= 'xpQb',
	c_FillTransparencySettings		= 'xpQc',
	c_ContentTransparencySettings	= 'xpQd',
	c_BlendingSettings				= 'xpQe',
	c_DropShadowSettings			= 'xpQf',
	c_FeatherSettings				= 'xpQg',
	c_InnerShadowSettings			= 'xpQh',
	c_OuterGlowSettings				= 'xpQi',
	c_InnerGlowSettings				= 'xpQj',
	c_BevelEmbossSettings			= 'xpQk',
	c_SatinSettings					= 'xpQl',
	c_DirectionalFeatherSettings	= 'xpQm',
	c_GradientFeatherSettings		= 'xpQn',

	c_FC_PageItemTransparencySettings	= 'xfQa',
	c_FC_StrokeTransparencySettings		= 'xfQb',
	c_FC_FillTransparencySettings		= 'xfQc',
	c_FC_ContentTransparencySettings	= 'xfQd',
	c_FC_BlendingSettings				= 'xfQe',
	c_FC_DropShadowSettings				= 'xfQf',
	c_FC_FeatherSettings				= 'xfQg',
	c_FC_InnerShadowSettings			= 'xfQh',
	c_FC_OuterGlowSettings				= 'xfQi',
	c_FC_InnerGlowSettings				= 'xfQj',
	c_FC_BevelEmbossSettings			= 'xfQk',
	c_FC_SatinSettings					= 'xfQl',
	c_FC_DirectionalFeatherSettings		= 'xfQm',
	c_FC_GradientFeatherSettings		= 'xfQn',

	// Transparency properties
	// Object properties (linking page item to child prefs)
	p_XPDefaultContainer			= 'xpCP',
	p_XPPageItemSettings			= 'xpSP',
	p_XPStrokeSettings				= 'xpSS',
	p_XPFillSettings				= 'xpSF',
	p_XPContentSettings				= 'xpSC',
	p_XPBlendingSettings			= 'xpS0',
	p_XPDropShadowSettings			= 'xpS1',
	p_XPFeatherSettings				= 'xpS2',
	p_XPInnerShadowSettings			= 'xpS3',
	p_XPOuterGlowSettings			= 'xpS4',
	p_XPInnerGlowSettings			= 'xpS5',
	p_XPBevelEmbossSettings			= 'xpS6',
	p_XPSatinSettings				= 'xpS7',
	p_XPDirectionalFeatherSettings	= 'xpS8',
	p_XPGradientFeatherSettings		= 'xpS9',

	// Basic
	p_XPBlendMode				= 'xpBm', // uses enum 'enXM'
	p_XPOpacity					= 'xpBo',
	p_XPKnockoutGroup			= 'xpBk',
	p_XPIsolateBlending			= 'xpBi',
	// DropShadow (legacy)
	p_XPDSMode					= 'xpSm', // uses enum 'enXS'
	p_XPDSBlendMode				= 'xpSb', // uses enum 'enXM'
	p_XPDSOffsetX				= 'xpSx',
	p_XPDSOffsetY				= 'xpSy',
	p_XPDSBlurRadius			= 'xpSr',
	p_XPDSSpread				= 'xpSs',
	p_XPDSNoise					= 'xpSn',
	p_XPDSColor					= 'xpSc',
	p_XPDSOpacity				= 'xpSo',
	// Feather (Vignette) (legacy)
	p_XPVGMode					= 'xpVm', // uses enum 'enXF'
	p_XPVGWidth					= 'xpVw',
	p_XPVGCornerType			= 'xpVc', // uses enum 'enXC'
	p_XPVGNoise					= 'xpVn',

	// The following p_XP constants are for the new hierarchical arrangement
	// of properties where the terms are simpler because they're grouped into
	// effect categories.

	p_XPStyle					= 'xpUb', // uses enum 'enX2'
	p_XPDepth					= 'xpUc',
	p_XPDirection				= 'xpUd', // uses enum 'enX4'
	p_XPSoften					= 'xpUe',
	p_XPAltitude				= 'xpUf',
	p_XPHighlightColor			= 'e0E4',
	p_XPHighlightBlendMode		= 'xpUh', // uses enum 'enXM'
	p_XPHighlightOpacity		= 'e0E3',
	p_XPXOffset					= 'xpUj',
	p_XPYOffset					= 'xpUk',
	p_XPDistance				= 'e0D8',
	p_XPNoise					= 'e0D5',
	p_XPApply					= 'xpUn',
	p_XPTechnique				= 'xpUo', // uses enum 'enX0' or 'enX3'
	p_XPMode					= 'xpUp', // uses enum 'enXS' or 'enXF'
	p_XPCornerType				= 'xpUq', // uses enum 'enXC'
	p_XPKnockout				= 'xpUr',
	p_XPUseGlobalLight			= 'xpUs',
	p_XPEffectColor				= 'xpUt', // enum/property conflict with "color"
	p_XPChokeAmount				= 'xpUu', // enum/property conflict with "choke"
	p_XPInvertEffect			= 'xpUv', // enum/property conflict with "invert"
	p_XPFollowShape				= 'xpUw', // uses enum 'enX5'
	p_XPGradientCenter			= 'xpUx',
	p_XPHighlightAngle			= 'xpUy',
	p_XPHighlightLength			= 'xpUz',
	p_XPRadius					= 'xpU0',
	p_XPGlobalLightAngle		= 'xpU1',
	p_XPGlobalLightAltitude		= 'xpU2',
	p_XPWidthLeft				= 'xpU3',
	p_XPWidthRight				= 'xpU4',
	p_XPWidthTop				= 'xpU5',
	p_XPWidthBottom				= 'xpU6',
	p_XPHonorFX					= 'xpU7',

	// borrowed terms (can't have name match but ID discrepancy in AS)
	p_XPShadowColor				= p_XPDSColor,
	p_XPShadowBlendMode			= p_XPDSBlendMode,
	p_XPShadowOpacity			= p_XPDSOpacity,

	// Preferences
	p_XPBlendSpace				= 'xpPb', // uses enum 'enXB'
} ;

// User Action Categories
DECLARE_PMID(kUserActionCategoryIDSpace, kTransparencyCategory, kXPPrefix + 1)

#endif // __XPID__
