//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/GraphicStylesID.h $
//  
//  Owner: Michael_Martz
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

#ifndef _GraphicStyles_ID_
#define _GraphicStyles_ID_

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

// Resource IDs
#define kRsrcID_GraphicStyleStrings			2000
#define kGraphicStyleStringsNoTransRsrcID	2100
#define kGraphicsErrorStringTableRsrcID		2300

#define kGraphicStylesPrefix	 				RezLong (0x6E00)

// <Start IDC>
// PluginID
#define kGraphicsModelPluginName			"Graphics"
DECLARE_PMID(kPlugInIDSpace, kGraphicStylesPluginID, kGraphicStylesPrefix + 1)

#pragma mark Class IDs
// <Class ID>
// ClassIDs (Bosses)
DECLARE_PMID(kClassIDSpace, kGraphicStyleBoss, kGraphicStylesPrefix + 1)
DECLARE_PMID(kClassIDSpace, kGraphicStyleNoneBoss, kGraphicStylesPrefix + 2)
DECLARE_PMID(kClassIDSpace, kGraphicStyleDescriptorBoss, kGraphicStylesPrefix + 3)
DECLARE_PMID(kClassIDSpace, kGraphicsErrorStringServiceBoss, kGraphicStylesPrefix + 4)
DECLARE_PMID(kClassIDSpace, kGraphicStyleReferenceConverterBoss, kGraphicStylesPrefix + 5)
DECLARE_PMID(kClassIDSpace, kGraphicStateScriptProviderBoss, kGraphicStylesPrefix + 6)
DECLARE_PMID(kClassIDSpace, kGraphicStateBoss, kGraphicStylesPrefix + 7)
DECLARE_PMID(kClassIDSpace, kGraphicStateStartupShutdownBoss, kGraphicStylesPrefix + 8)
DECLARE_PMID(kClassIDSpace, kGraphicStateMetaDataObjectBoss_Obsolete, kGraphicStylesPrefix + 9)
DECLARE_PMID(kClassIDSpace, kGraphicStateNoneMetaDataBoss_Obsolete, kGraphicStylesPrefix + 10)
DECLARE_PMID(kClassIDSpace, kGraphicStateNoneRenderingObjectBoss, kGraphicStylesPrefix + 11)
//gap
DECLARE_PMID(kClassIDSpace, kGraphicStateNewDocResponderBoss, kGraphicStylesPrefix + 14)
DECLARE_PMID(kClassIDSpace, kGraphicStyleNewDocResponderBoss, kGraphicStylesPrefix + 15)
DECLARE_PMID(kClassIDSpace, kGraphicStyleNewWSResponderBoss, kGraphicStylesPrefix + 16)
DECLARE_PMID(kClassIDSpace, kMultipleRenderingObjectsBoss, kGraphicStylesPrefix + 17)
DECLARE_PMID(kClassIDSpace, kMultipleMetaDataBoss_Obsolete, kGraphicStylesPrefix + 18)
DECLARE_PMID(kClassIDSpace, kGraphicStyleNewScrapResponderBoss, kGraphicStylesPrefix + 19)
DECLARE_PMID(kClassIDSpace, kGraphicStateSwatchesRIDXNotifierHandlerBoss, kGraphicStylesPrefix + 20)
//gap
DECLARE_PMID(kClassIDSpace, kGraphicAccessorBoss, kGraphicStylesPrefix + 25)
DECLARE_PMID(kClassIDSpace, kGraphicStateNewWSResponderBoss, kGraphicStylesPrefix + 26)
//gap
DECLARE_PMID(kClassIDSpace, kChangePageItemIsApplicableCmdBoss, kGraphicStylesPrefix + 29)
//gap
DECLARE_PMID(kClassIDSpace, kGfxStateNewScrapDocResponderBoss, kGraphicStylesPrefix + 31)
DECLARE_PMID(kClassIDSpace, kGraphicStylesIteratorRegBoss, kGraphicStylesPrefix + 32)
DECLARE_PMID(kClassIDSpace, kGraphicsSchemaConverterBoss, kGraphicStylesPrefix + 33)
//gap
DECLARE_PMID(kClassIDSpace, kGraphicStyleApplyStyleCmdBoss, kGraphicStylesPrefix + 50)
DECLARE_PMID(kClassIDSpace, kGraphicStyleAddStyleCmdBoss, kGraphicStylesPrefix + 51)
DECLARE_PMID(kClassIDSpace, kGraphicStyleRemoveStyleCmdBoss, kGraphicStylesPrefix + 52)
//gap
DECLARE_PMID(kClassIDSpace, kGfxStateSetRenderDataBlockCmdBoss, kGraphicStylesPrefix + 57)
DECLARE_PMID(kClassIDSpace, kGfxStateClearAllRenderDataBlocksCmdBoss, kGraphicStylesPrefix + 58)
DECLARE_PMID(kClassIDSpace, kGfxStateSetProxyBoss, kGraphicStylesPrefix + 59)
DECLARE_PMID(kClassIDSpace, kGfxStateChangeAttributeCmdBoss, kGraphicStylesPrefix + 60)
DECLARE_PMID(kClassIDSpace, kGfxStateAddAttributeCmdBoss, kGraphicStylesPrefix + 61)
DECLARE_PMID(kClassIDSpace, kGfxStateRemoveAttributeCmdBoss, kGraphicStylesPrefix + 62)
DECLARE_PMID(kClassIDSpace, kGfxApplyAttrOverrideCmdBoss, kGraphicStylesPrefix + 63)
//gap
DECLARE_PMID(kClassIDSpace, kGfxClearAttrOverrideCmdBoss, kGraphicStylesPrefix + 67)
//gap
DECLARE_PMID(kClassIDSpace, kBoss_GfxStateApplyROAttributeCmd, kGraphicStylesPrefix + 69	/* Private	*/)
DECLARE_PMID(kClassIDSpace, kGfxStateSwapFillStrokeCmdBoss, kGraphicStylesPrefix + 70)
//gap
DECLARE_PMID(kClassIDSpace, kGfxDefaultStrokeAndFillCmdBoss, kGraphicStylesPrefix + 72)
DECLARE_PMID(kClassIDSpace, kSwapPageItemStrokeAndFillCmdBoss, kGraphicStylesPrefix + 73)
DECLARE_PMID(kClassIDSpace, kAddMultAttributesCmdBoss, kGraphicStylesPrefix + 74)
DECLARE_PMID(kClassIDSpace, kRemoveMultAttributesCmdBoss, kGraphicStylesPrefix + 75)
DECLARE_PMID(kClassIDSpace, kSwapTextStrokeAndFillCmdBoss, kGraphicStylesPrefix + 76)
DECLARE_PMID(kClassIDSpace, kGfxApplyMultAttributesCmdBoss, kGraphicStylesPrefix + 77)
DECLARE_PMID(kClassIDSpace, kTextSwapFillStrokeForDefaultCmdBoss, kGraphicStylesPrefix + 78)
DECLARE_PMID(kClassIDSpace, kUpdateDefRenderDataCmdBoss, kGraphicStylesPrefix + 79)
DECLARE_PMID(kClassIDSpace, kPrivateUpdateGSRenderDataCmdBoss, kGraphicStylesPrefix + 80)
DECLARE_PMID(kClassIDSpace, kPrivateSetGSRenderDataCmdBoss, kGraphicStylesPrefix + 81)
DECLARE_PMID(kClassIDSpace, kPrivateSetGSStateDataBoss, kGraphicStylesPrefix + 82)
DECLARE_PMID(kClassIDSpace, kPrivateReplaceGSRenderDataCmdBoss, kGraphicStylesPrefix + 83)
DECLARE_PMID(kClassIDSpace, kPrivateReplaceGSStateDataCmdBoss, kGraphicStylesPrefix + 84)
DECLARE_PMID(kClassIDSpace, kPrivateUndoSetRenderBlockCmdBoss, kGraphicStylesPrefix + 85)
//gap
#pragma mark Attribute classIDs
DECLARE_PMID(kClassIDSpace, kGraphicsAttrBoss, kGraphicStylesPrefix +  99)
DECLARE_PMID(kClassIDSpace, kGraphicStyleStrokeRenderingAttrBoss, kGraphicStylesPrefix + 100)
DECLARE_PMID(kClassIDSpace, kGraphicStyleStrokeWeightAttrBoss, kGraphicStylesPrefix + 101)
DECLARE_PMID(kClassIDSpace, kGraphicStyleStrokeTintAttrBoss, kGraphicStylesPrefix + 102)
DECLARE_PMID(kClassIDSpace, kGraphicStyleOverprintStrokeAttrBoss, kGraphicStylesPrefix + 103)
DECLARE_PMID(kClassIDSpace, kGraphicStyleFillRenderingAttrBoss, kGraphicStylesPrefix + 104	)
DECLARE_PMID(kClassIDSpace, kGraphicStyleFillTintAttrBoss, kGraphicStylesPrefix + 105)
DECLARE_PMID(kClassIDSpace, kGraphicStyleOverprintFillAttrBoss, kGraphicStylesPrefix + 106)
DECLARE_PMID(kClassIDSpace, kGraphicStyleLineCapAttrBoss, kGraphicStylesPrefix + 107)
DECLARE_PMID(kClassIDSpace, kGraphicStyleJoinTypeAttrBoss, kGraphicStylesPrefix + 108)
DECLARE_PMID(kClassIDSpace, kGraphicStyleMiterLimitAttrBoss, kGraphicStylesPrefix + 109)
DECLARE_PMID(kClassIDSpace, kGraphicStyleStrokeLineImplAttrBoss, kGraphicStylesPrefix + 110)
DECLARE_PMID(kClassIDSpace, kGraphicStyleCornerImplAttrBoss, kGraphicStylesPrefix + 111)
DECLARE_PMID(kClassIDSpace, kGraphicStyleCornerRadiusAttrBoss, kGraphicStylesPrefix + 112)
DECLARE_PMID(kClassIDSpace, kGraphicStyleLineEndStartAttrBoss, kGraphicStylesPrefix + 113)
DECLARE_PMID(kClassIDSpace, kGraphicStyleLineEndEndAttrBoss, kGraphicStylesPrefix + 114)
DECLARE_PMID(kClassIDSpace, kGraphicStyleEvenOddAttrBoss, kGraphicStylesPrefix + 115)
DECLARE_PMID(kClassIDSpace, kGS_ConversionProviderBoss, kGraphicStylesPrefix + 116)
DECLARE_PMID(kClassIDSpace, kSetStrokeChangeCmdBoss, kGraphicStylesPrefix + 117)
DECLARE_PMID(kClassIDSpace, kStrokeGraphicsAttrBoss, kGraphicStylesPrefix + 118)
DECLARE_PMID(kClassIDSpace, kFillGraphicsAttrBoss, kGraphicStylesPrefix + 119)
DECLARE_PMID(kClassIDSpace, kGraphicStyleNonPrintAttrBoss, kGraphicStylesPrefix + 120)
DECLARE_PMID(kClassIDSpace, kCornerEffectGraphicsAttrBoss, kGraphicStylesPrefix + 121)
DECLARE_PMID(kClassIDSpace, kStrokeEffectGraphicsAttrBoss, kGraphicStylesPrefix + 122)
DECLARE_PMID(kClassIDSpace, kDefaultGraphicsAttrBoss,	   kGraphicStylesPrefix + 123)
DECLARE_PMID(kClassIDSpace, kFitContentsGraphicsAttrBoss,		kGraphicStylesPrefix + 124)
DECLARE_PMID(kClassIDSpace, kFittingRefPointGraphicsAttrBoss,	kGraphicStylesPrefix + 125)
DECLARE_PMID(kClassIDSpace, kFittingCropLeftGraphicsAttrBoss,	kGraphicStylesPrefix + 126)
DECLARE_PMID(kClassIDSpace, kFittingCropTopGraphicsAttrBoss,	kGraphicStylesPrefix + 127)
DECLARE_PMID(kClassIDSpace, kFittingCropRightGraphicsAttrBoss,	kGraphicStylesPrefix + 128)
DECLARE_PMID(kClassIDSpace, kFittingCropBottomGraphicsAttrBoss,	kGraphicStylesPrefix + 129)
DECLARE_PMID(kClassIDSpace, kFrameFittingGraphicsAttrBoss,		kGraphicStylesPrefix + 130)
DECLARE_PMID(kClassIDSpace, kFittingAutoFitGraphicsAttrBoss,	kGraphicStylesPrefix + 131)
DECLARE_PMID(kClassIDSpace, kGraphicStyleArrowHeadAlignmentAttrBoss, kGraphicStylesPrefix + 132)
//gap
DECLARE_PMID(kClassIDSpace, kGraphicStateDataPhase2ConversionBoss, kGraphicStylesPrefix + 135)
DECLARE_PMID(kClassIDSpace, kGraphicAttrListPhase2ConversionBoss, kGraphicStylesPrefix + 136)
DECLARE_PMID(kClassIDSpace, kGraphicStyleGapRenderingAttrBoss, kGraphicStylesPrefix + 137)
DECLARE_PMID(kClassIDSpace, kGraphicStyleGapTintAttrBoss, kGraphicStylesPrefix + 138)
DECLARE_PMID(kClassIDSpace, kGraphicStyleOverprintGapAttrBoss, kGraphicStylesPrefix + 139)
DECLARE_PMID(kClassIDSpace, kGraphicStyleStrokeAlignmentAttrBoss, kGraphicStylesPrefix + 140)
DECLARE_PMID(kClassIDSpace, kGraphicStyleOverridesPhase2ConversionBoss, kGraphicStylesPrefix + 141)
DECLARE_PMID(kClassIDSpace, kGraphicStylePhase2ConversionBoss, kGraphicStylesPrefix + 142)

DECLARE_PMID(kClassIDSpace, kGraphicStyleLiveCornerBLImplAttrBoss, kGraphicStylesPrefix + 143)
DECLARE_PMID(kClassIDSpace, kGraphicStyleLiveCornerBRImplAttrBoss, kGraphicStylesPrefix + 144)
DECLARE_PMID(kClassIDSpace, kGraphicStyleLiveCornerTRImplAttrBoss, kGraphicStylesPrefix + 145)

DECLARE_PMID(kClassIDSpace, kGraphicStyleLiveCornerBLRadiusAttrBoss, kGraphicStylesPrefix + 146)
DECLARE_PMID(kClassIDSpace, kGraphicStyleLiveCornerBRRadiusAttrBoss, kGraphicStylesPrefix + 147)
DECLARE_PMID(kClassIDSpace, kGraphicStyleLiveCornerTRRadiusAttrBoss, kGraphicStylesPrefix + 148)
DECLARE_PMID(kClassIDSpace, kGraphicStyleArrowHeadStartScaleAttrBoss, kGraphicStylesPrefix + 149)
DECLARE_PMID(kClassIDSpace, kGraphicStyleArrowHeadEndScaleAttrBoss, kGraphicStylesPrefix + 150)

// Layout Attr IDs declaration 
DECLARE_PMID(kClassIDSpace, kGfxLayoutBaseAttrBoss,	kGraphicStylesPrefix + 151)
DECLARE_PMID(kClassIDSpace, kGfxLayoutXPosAttrBoss, kGraphicStylesPrefix + 152)
DECLARE_PMID(kClassIDSpace, kGfxLayoutYPosAttrBoss, kGraphicStylesPrefix + 153)
DECLARE_PMID(kClassIDSpace, kGfxLayoutWidthAttrBoss, kGraphicStylesPrefix + 154)
DECLARE_PMID(kClassIDSpace, kGfxLayoutHeightAttrBoss, kGraphicStylesPrefix + 155)
DECLARE_PMID(kClassIDSpace, kGfxLayoutPositionRefPointAttrBoss, kGraphicStylesPrefix + 156)
DECLARE_PMID(kClassIDSpace, kGfxXPositionRefPointAttrBoss, kGraphicStylesPrefix + 157)
DECLARE_PMID(kClassIDSpace, kGfxYPositionRefPointAttrBoss, kGraphicStylesPrefix + 158)
DECLARE_PMID(kClassIDSpace, kGfxLayoutObjStylesAttrHandlerBoss, kGraphicStylesPrefix + 159)
DECLARE_PMID(kClassIDSpace, kGfxLayoutRefAnchorPointAttrBoss, kGraphicStylesPrefix + 160)

// Defining the layout attr category
DECLARE_PMID(kClassIDSpace, kGfxLayoutXPositionAttrCategory, kGraphicStylesPrefix + 161)
DECLARE_PMID(kClassIDSpace, kGfxLayoutYPositionAttrCategory, kGraphicStylesPrefix + 162)
DECLARE_PMID(kClassIDSpace, kGfxLayoutWidthAttrCategory, kGraphicStylesPrefix + 163)
DECLARE_PMID(kClassIDSpace, kGfxLayoutHeightAttrCategory, kGraphicStylesPrefix + 164)
DECLARE_PMID(kClassIDSpace, kGfxLayoutXRefPointCategory, kGraphicStylesPrefix + 165)
DECLARE_PMID(kClassIDSpace, kGfxLayoutYRefPointCategory, kGraphicStylesPrefix + 166)
DECLARE_PMID(kClassIDSpace, kGfxLayoutReferenceAnchorPointCategory, kGraphicStylesPrefix + 167)
DECLARE_PMID(kClassIDSpace, kGfxStylePostCreatePageItemNewDocResponderBoss, kGraphicStylesPrefix + 168)
DECLARE_PMID(kClassIDSpace, kGfxStylePostCreatePageItemOpenDocResponderBoss, kGraphicStylesPrefix + 169)
DECLARE_PMID(kClassIDSpace, kGfxStylePostCreatePageItemCloseDocResponderBoss, kGraphicStylesPrefix + 170)


// End of Layout attrs

#pragma mark Interface IDs
// <Interface ID>
// Interface IDs
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICSTYLE_REFERENCE, kGraphicStylesPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICSTYLE_DESCRIPTOR, kGraphicStylesPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICSTYLE_OVERRIDES, kGraphicStylesPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICSTYLE_INFO, kGraphicStylesPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICSTYLE_DEFINITION, kGraphicStylesPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICSTATE_RENDEROBJECTS, kGraphicStylesPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICSTATE_DEFINITION, kGraphicStylesPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICSTYLE_IS_APPLICABLE, kGraphicStylesPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICSTATE_CONTEXTOBSERVER, kGraphicStylesPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICSTYLE_OVERRIDES_STROKEBOUNDS, kGraphicStylesPrefix + 10)

DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICSTYLE_SELECTION, kGraphicStylesPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICSTATE_ACCESSOR, kGraphicStylesPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICSTYLE_NAMETABLE, kGraphicStylesPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICATTR_CLASSID, kGraphicStylesPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICATTR_BOOLEAN, kGraphicStylesPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICATTR_INT16, kGraphicStylesPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICATTR_INT32, kGraphicStylesPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICATTR_REALNUMBER, kGraphicStylesPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_IINDETERMINATE_DATA, kGraphicStylesPrefix + 19)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IRENDERCLASS_PANELDATA, kGraphicStylesPrefix + 21)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IADDDEFAULTGRAPHICATTRDATA, kGraphicStylesPrefix + 23)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICSTATE_DEFINITIONOBSERVER, kGraphicStylesPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICATTR_POINT, kGraphicStylesPrefix + 26)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICATTR_INFO, kGraphicStylesPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_IATTRIBUTE_PREPOST_ACTION, kGraphicStylesPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_IRENDERINGOBJECTAPPLYACTION, kGraphicStylesPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICSTATE_ATTRIBUTECMDDATA, kGraphicStylesPrefix + 32)
DECLARE_PMID(kInterfaceIDSpace, IID_TOOLBOX_STROKEFILL_PREF, kGraphicStylesPrefix + 33)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICSTYLE_OVERRIDES_DOCUMENT, kGraphicStylesPrefix + 34)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICSTYLE_REFERENCE_DOCUMENT, kGraphicStylesPrefix + 35)
DECLARE_PMID(kInterfaceIDSpace, IID_IAPPLYRENDOBJATTR_CMDDATA, kGraphicStylesPrefix + 36)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICMETADATAOBJECT_OBSOLETE, kGraphicStylesPrefix + 38)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICSTYLE_IS_APPLICABLE_DOCUMENT, kGraphicStylesPrefix + 41)
DECLARE_PMID(kInterfaceIDSpace, IID_CHANGEISAPPLICABLE_CMDDATA, kGraphicStylesPrefix + 42)
DECLARE_PMID(kInterfaceIDSpace, IID_CLEARATTROVERRIDE_CMDDATA, kGraphicStylesPrefix + 43)
DECLARE_PMID(kInterfaceIDSpace, IID_IAPPLYATTRIBUTE_CMDDATA, kGraphicStylesPrefix + 44)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTROKECHANGEPREFERENCE, kGraphicStylesPrefix + 45)
DECLARE_PMID(kInterfaceIDSpace, IID_IADDMULTATTRIBUTESCMDDATA, kGraphicStylesPrefix + 46)
DECLARE_PMID(kInterfaceIDSpace, IID_IREMOVEMULTATTRIBUTESCMDDATA, kGraphicStylesPrefix + 47)
DECLARE_PMID(kInterfaceIDSpace, IID_IAPPLYMULTATTRIBUTES_CMDDATA, kGraphicStylesPrefix + 48)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICSTATE_DATA, kGraphicStylesPrefix + 49)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICATTRIBUTESUITE, kGraphicStylesPrefix + 50)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICSTATE_CMDDATA, kGraphicStylesPrefix + 52)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IRECORDGRAPHICATTRIBUTEFACADE, kGraphicStylesPrefix + 58)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICATTRCACHE_BROADCAST, kGraphicStylesPrefix + 59)	//Graphic attribute cache IID used for broadcasting only
//	Graphic attribute caches for CSB
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTGRAPHICATTRCACHE, kGraphicStylesPrefix + 60)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTGRAPHICATTRCACHE, kGraphicStylesPrefix + 61)
DECLARE_PMID(kInterfaceIDSpace, IID_ITABLEGRAPHICATTRCACHE, kGraphicStylesPrefix + 62)
DECLARE_PMID(kInterfaceIDSpace, IID_IDEFAULTGRAPHICATTRCACHE, kGraphicStylesPrefix + 63)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICATTRPROXYSUITE, kGraphicStylesPrefix + 64)
DECLARE_PMID(kInterfaceIDSpace, IID_IGFXSTATERENDEROBJECTCONSTRCUTIONFLAG, kGraphicStylesPrefix + 65)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTROKEATTRIBUTESUITE, kGraphicStylesPrefix + 66)
DECLARE_PMID(kInterfaceIDSpace, IID_IRENDEROBJECTSERVICE, kGraphicStylesPrefix + 67)
DECLARE_PMID(kInterfaceIDSpace, IID_IUPDATEDEFRENDERDATACMDDATA, kGraphicStylesPrefix + 68)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRIVATEGRAPHICSTATECOMMANDS, kGraphicStylesPrefix + 69)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRIVATEGSFILLUIDLISTDATA, kGraphicStylesPrefix + 70)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRIVATEGSSTROKEUIDLISTDATA, kGraphicStylesPrefix + 71)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICATTRASBOBSERVER, kGraphicStylesPrefix + 72)
DECLARE_PMID(kInterfaceIDSpace, IID_ILIVESHAPEGFXUTILS, kGraphicStylesPrefix + 73)

// Layout attr Interface declarations.
DECLARE_PMID(kInterfaceIDSpace, IID_IGFXLAYOUT_BOOLBACKED_REALNUMBER, kGraphicStylesPrefix + 74)
// End of layout attr declarations.

// Layout Attrs Helper Util
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTATTRSHELPERUTILS, kGraphicStylesPrefix + 75)
DECLARE_PMID(kInterfaceIDSpace, IID_IPOSTADDTOHIERARCHYOBSERVER, kGraphicStylesPrefix + 76)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRANSFORM_ATTR_OVERRIDES, kGraphicStylesPrefix + 77)


#pragma mark Implementation IDs
// <Implementation ID>
// Implementation IDs
DECLARE_PMID(kImplementationIDSpace, kGraphicStyleReferenceImpl, kGraphicStylesPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kGraphicStyleDescriptorImpl, kGraphicStylesPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kGraphicStyleBossListImpl, kGraphicStylesPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kGraphicStyleInfoImpl, kGraphicStylesPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kGraphicStyleReferenceConverterImpl, kGraphicStylesPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kGraphicStateRenderObjectsImpl, kGraphicStylesPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kGraphicStateDataImpl, kGraphicStylesPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kGraphicStateScriptProviderImpl, kGraphicStylesPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kGraphicStateServiceProviderImpl, kGraphicStylesPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kGraphicStateStartupShutdownImpl, kGraphicStylesPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kGraphicStateContextObserverImpl, kGraphicStylesPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kFrameFittingGraphicsAttrInfoImpl, kGraphicStylesPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kGraphicStateAccessorImpl, kGraphicStylesPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kNewGraphicStyleButtonImpl, kGraphicStylesPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kGraphicStyleNameTableImpl, kGraphicStylesPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kPersistGraphicStateAccessorImpl, kGraphicStylesPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kRenderClassProviderImpl, kGraphicStylesPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kRecordGraphicAttributeFacadeImpl, kGraphicStylesPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kGraphicsErrorStringServiceImpl, kGraphicStylesPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kGraphicStateDefnObserverImpl, kGraphicStylesPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kGraphicStateSwatchesRIDXNotifierHandlerImpl, kGraphicStylesPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kGraphicStateSwatchReferenceDataImpl, kGraphicStylesPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kGraphicStateDefaultGSDescriptorImpl, kGraphicStylesPrefix + 23)
//gap
DECLARE_PMID(kImplementationIDSpace, kGraphicStateDocResponderImpl, kGraphicStylesPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kGraphicStateObserverImpl, kGraphicStylesPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kGraphicStateNewDocResponderImpl, kGraphicStylesPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kGraphicStyleNewDocResponderImpl, kGraphicStylesPrefix + 28)
//gap
DECLARE_PMID(kImplementationIDSpace, kGraphicStyleNewWSResponderImpl, kGraphicStylesPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kGraphicStyleNewScrapResponderImpl, kGraphicStylesPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kMediaIsApplicableImpl, kGraphicStylesPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kStrokeGraphicsAttrInfoImpl,		kGraphicStylesPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kFillGraphicsAttrInfoImpl,			kGraphicStylesPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kStrokeEffectGraphicsAttrInfoImpl,	kGraphicStylesPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kCornerEffectGraphicsAttrInfoImpl,	kGraphicStylesPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kDefaultGraphicsAttrInfoImpl,		kGraphicStylesPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kGeneralGraphicsAttrInfoImpl,		kGraphicStylesPrefix + 38)
//gap
DECLARE_PMID(kImplementationIDSpace, kImpl_ClearFillStrokeTool, kGraphicStylesPrefix + 40)
//gap
DECLARE_PMID(kImplementationIDSpace, kImpl_ToolsObserver, kGraphicStylesPrefix + 43)
//gap
DECLARE_PMID(kImplementationIDSpace, kGraphicStateNewWSResponderImpl, kGraphicStylesPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kToolboxStrokeFillPreferenceImpl, kGraphicStylesPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kGenericGraphicMetaDataObjectImpl_Obsolete, kGraphicStylesPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kImageBaseIsApplicableImpl, kGraphicStylesPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kSplineIsApplicableImpl, kGraphicStylesPrefix + 49)
//gap
DECLARE_PMID(kImplementationIDSpace, kApplyGraphicStyleCmdImpl, kGraphicStylesPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kAddGraphicStyleCmdImpl, kGraphicStylesPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kRemoveGraphicStyleCmdImpl, kGraphicStylesPrefix + 52)
//gap
DECLARE_PMID(kImplementationIDSpace, kGfxStateSetRenderDataBlockCmdImpl, kGraphicStylesPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kGfxStateClearAllRenderDataBlocksCmdImpl, kGraphicStylesPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kGfxStateSetProxyCmdImpl, kGraphicStylesPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kGfxStateChangeAttributeCmdImpl, kGraphicStylesPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kGfxStateAddAttributeCmdImpl, kGraphicStylesPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kGfxStateRemoveAttributeCmdImpl, kGraphicStylesPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kGfxApplyAttributeOverrideCmdImpl, kGraphicStylesPrefix + 63)
//gap
DECLARE_PMID(kImplementationIDSpace, kImpl_GfxStateApplyROAttributeCmd, kGraphicStylesPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kImpl_GfxStateSwapFillStrokeCmd, kGraphicStylesPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kGfxClearAttrOverrideCmdImpl, kGraphicStylesPrefix + 69)
//gap
DECLARE_PMID(kImplementationIDSpace, kGraphicStateAttributeCmdDataImpl, kGraphicStylesPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kDefaultStrokeAndFillCmdImpl, kGraphicStylesPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kSwapPageItemStrokeAndFillCmdImpl, kGraphicStylesPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kApplyRendObjAttrCmdDataImpl, kGraphicStylesPrefix + 74)

//...............................................................................
// Service provider implementations
// 		These are the IK2ServiceProvider implementations that all plugins should
// 		use when there installed stroke and fill objects.  The plugin only
//		provide the implementation for all the other interfaces that may exist
//		on the objects.
//
// 		As of 7/15/97 service providers are attached to the specific attributes
// 		they represent -- this provides a  means to create a list of Class IDs 
// 		of all the installed path strokers, path end strokers, and path corners.
//...............................................................................

DECLARE_PMID(kImplementationIDSpace, kPathStrokerServiceProviderImpl, kGraphicStylesPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kPathEndStrokerServiceProviderImpl, kGraphicStylesPrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kPathCornerServiceProviderImpl, kGraphicStylesPrefix + 77)
DECLARE_PMID(kImplementationIDSpace, kChangePIIsApplicableCmdImpl, kGraphicStylesPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kChangePIIsApplicableCmdDataImpl, kGraphicStylesPrefix + 79)
DECLARE_PMID(kImplementationIDSpace, kClearAttrOverrideCmdDataImpl, kGraphicStylesPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kApplyAttributeCmdDataImpl, kGraphicStylesPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kSwapTextStrokeAndFillCmdImpl, kGraphicStylesPrefix + 82)
//gap
DECLARE_PMID(kImplementationIDSpace, kGfxApplyMultAttributesCmdImpl, kGraphicStylesPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kApplyMultAttributesCmdDataImpl, kGraphicStylesPrefix + 85)
DECLARE_PMID(kImplementationIDSpace, kGraphicStateCmdDataImpl, kGraphicStylesPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kUpdateDefRenderDataCmdImpl, kGraphicStylesPrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kUpdateDefRederDataCmdDataImpl, kGraphicStylesPrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kPrivateGraphicStateCommandsImpl, kGraphicStylesPrefix + 89)
DECLARE_PMID(kImplementationIDSpace, kPrivateSetGSRenderDataCmdImpl, kGraphicStylesPrefix + 90)
DECLARE_PMID(kImplementationIDSpace, kPrivateReplaceGSRenderDataCmdImpl, kGraphicStylesPrefix + 91)
DECLARE_PMID(kImplementationIDSpace, kPrivateReplaceGSStateDataCmdImpl, kGraphicStylesPrefix + 92)
DECLARE_PMID(kImplementationIDSpace, kGraphicAttrASBObserverImpl, kGraphicStylesPrefix + 93)
DECLARE_PMID(kImplementationIDSpace, kPrivateUndoSetRenderBlockCmdImpl, kGraphicStylesPrefix + 94)
DECLARE_PMID(kImplementationIDSpace, kPrivateUpdateGSRenderDataCmdImpl, kGraphicStylesPrefix + 95)
//gap
DECLARE_PMID(kImplementationIDSpace, kImpl_GraphicAttrInfo, kGraphicStylesPrefix +  98)
DECLARE_PMID(kImplementationIDSpace, kGraphicAttrIndeterminateDataImpl, kGraphicStylesPrefix +  99)
DECLARE_PMID(kImplementationIDSpace, kGraphicAttrClassIDImpl, kGraphicStylesPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kGraphicAttrBooleanImpl, kGraphicStylesPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kGraphicAttrInt16Impl, kGraphicStylesPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kGraphicAttrInt32Impl, kGraphicStylesPrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kGraphicAttrRealNumberImpl, kGraphicStylesPrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kGraphicAttrPointImpl, kGraphicStylesPrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kImpl_GraphicAttrRendObjPrePost, kGraphicStylesPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kGS_ConversionProviderImpl, kGraphicStylesPrefix + 107)
//gap
DECLARE_PMID(kImplementationIDSpace, kStrokeAttributePrePostImpl, kGraphicStylesPrefix + 109)
DECLARE_PMID(kImplementationIDSpace, kStrokeChangePreferenceImpl, kGraphicStylesPrefix + 110)
DECLARE_PMID(kImplementationIDSpace, kSetStrokeChangeCmdImpl, kGraphicStylesPrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kAddMultAttributesCmdImpl, kGraphicStylesPrefix + 112)
DECLARE_PMID(kImplementationIDSpace, kRemoveMultAttributesCmdImpl, kGraphicStylesPrefix + 113)
DECLARE_PMID(kImplementationIDSpace, kAddMultAttributesCmdDataImpl, kGraphicStylesPrefix + 114)
DECLARE_PMID(kImplementationIDSpace, kRemoveMultAttributesCmdDataImpl, kGraphicStylesPrefix + 115)
//gap
DECLARE_PMID(kImplementationIDSpace, kLayoutSwapProxyToolImpl, kGraphicStylesPrefix + 120)
DECLARE_PMID(kImplementationIDSpace, kTextSwapProxyToolImpl, kGraphicStylesPrefix + 121)
DECLARE_PMID(kImplementationIDSpace, kTextLayoutSwapProxyToolImpl, kGraphicStylesPrefix + 122)
DECLARE_PMID(kImplementationIDSpace, kTextSwapFillStrokeForDefaultCmdImpl, kGraphicStylesPrefix + 123)
DECLARE_PMID(kImplementationIDSpace, kUpdateDefRenderDataCmdDataImpl, kGraphicStylesPrefix + 124)
//gap
DECLARE_PMID(kImplementationIDSpace, kLeafSelectionImpl, kGraphicStylesPrefix + 150)
DECLARE_PMID(kImplementationIDSpace, kGroupSelectionImpl, kGraphicStylesPrefix + 151)
DECLARE_PMID(kImplementationIDSpace, kEPSTextIsApplicableImpl, kGraphicStylesPrefix + 152)
DECLARE_PMID(kImplementationIDSpace, kSolidColorMetaDataObjectImpl_Obsolete, kGraphicStylesPrefix + 153)
//gap
DECLARE_PMID(kImplementationIDSpace, kGraphicStyleNewScrapDocResponderImpl, kGraphicStylesPrefix + 155)
//gap
DECLARE_PMID(kImplementationIDSpace, kGraphicAttrSuiteASBImpl, kGraphicStylesPrefix + 157)
DECLARE_PMID(kImplementationIDSpace, kGraphicAttrSuiteTextCSBImpl, kGraphicStylesPrefix + 158)
DECLARE_PMID(kImplementationIDSpace, kGraphicAttrSuiteLayoutCSBImpl, kGraphicStylesPrefix + 159)
DECLARE_PMID(kImplementationIDSpace, kGraphicAttrSuiteDefaultCSBImpl, kGraphicStylesPrefix + 160)
DECLARE_PMID(kImplementationIDSpace, kGraphicStyleOverridesPhase2ConverterImpl, kGraphicStylesPrefix + 161)	
DECLARE_PMID(kImplementationIDSpace, kGraphicStylePhase2ConverterImpl, kGraphicStylesPrefix + 162)
//gap
DECLARE_PMID(kImplementationIDSpace, kGroupIsApplicableImpl, kGraphicStylesPrefix + 164)
DECLARE_PMID(kImplementationIDSpace, kGraphicStylesIteratorRegImpl, kGraphicStylesPrefix + 165)
DECLARE_PMID(kImplementationIDSpace, kGraphicAttrSuiteTableCSBImpl, kGraphicStylesPrefix + 166)
//gap
DECLARE_PMID(kImplementationIDSpace, kGraphicAttrASBSelectionExtImpl, kGraphicStylesPrefix + 169)
DECLARE_PMID(kImplementationIDSpace, kGraphicAttrSuiteLayoutCSBSelectionExtImpl, kGraphicStylesPrefix + 170)
DECLARE_PMID(kImplementationIDSpace, kGraphicAttrSuiteDefaultCSBSelectionExtImpl, kGraphicStylesPrefix + 171)
DECLARE_PMID(kImplementationIDSpace, kGraphicAttrSuiteTextCSBSelectionExtImpl, kGraphicStylesPrefix + 172)
DECLARE_PMID(kImplementationIDSpace, kGraphicAttrSuiteTableCSBSelectionExtImpl, kGraphicStylesPrefix + 173)
//gap
//	Graphic attribute caches for CSB
DECLARE_PMID(kImplementationIDSpace, kLayoutGraphicAttrCacheImpl, kGraphicStylesPrefix + 180)
DECLARE_PMID(kImplementationIDSpace, kTextGraphicAttrCacheImpl, kGraphicStylesPrefix + 181)
DECLARE_PMID(kImplementationIDSpace, kTableGraphicAttrCacheImpl, kGraphicStylesPrefix + 182)
DECLARE_PMID(kImplementationIDSpace, kDefaultGraphicAttrCacheImpl, kGraphicStylesPrefix + 183)
DECLARE_PMID(kImplementationIDSpace, kLayoutGraphicAttrCacheSelectionExtImpl, kGraphicStylesPrefix + 184)
DECLARE_PMID(kImplementationIDSpace, kTextGraphicAttrCacheSelectionExtImpl, kGraphicStylesPrefix + 185)
DECLARE_PMID(kImplementationIDSpace, kTableGraphicAttrCacheSelectionExtImpl, kGraphicStylesPrefix + 186)
DECLARE_PMID(kImplementationIDSpace, kDefaultGraphicAttrCacheSelectionExtImpl, kGraphicStylesPrefix + 187)
DECLARE_PMID(kImplementationIDSpace, kGraphicAttrProxyASBImpl, kGraphicStylesPrefix + 188)
DECLARE_PMID(kImplementationIDSpace, kGraphicAttrProxyLayoutCSBImpl, kGraphicStylesPrefix + 189)
DECLARE_PMID(kImplementationIDSpace, kGraphicAttrProxyTextCSBImpl, kGraphicStylesPrefix + 190)
DECLARE_PMID(kImplementationIDSpace, kGraphicAttrProxyTableCSBImpl, kGraphicStylesPrefix + 191)
DECLARE_PMID(kImplementationIDSpace, kGraphicAttrProxyDefaultCSBImpl, kGraphicStylesPrefix + 192)
DECLARE_PMID(kImplementationIDSpace, kGraphicAttrProxyASBSelectionExtImpl, kGraphicStylesPrefix + 193)
DECLARE_PMID(kImplementationIDSpace, kGraphicAttrProxyLayoutCSBSelectionExtImpl, kGraphicStylesPrefix + 194)
DECLARE_PMID(kImplementationIDSpace, kGraphicAttrProxyTextCSBSelectionExtImpl, kGraphicStylesPrefix + 195)
DECLARE_PMID(kImplementationIDSpace, kGraphicAttrProxyTableCSBSelectionExtImpl, kGraphicStylesPrefix + 196)
DECLARE_PMID(kImplementationIDSpace, kGraphicAttrProxyDefaultCSBSelectionExtImpl, kGraphicStylesPrefix + 197)
DECLARE_PMID(kImplementationIDSpace, kDisplayListItemIsApplicableImpl, kGraphicStylesPrefix + 198)
DECLARE_PMID(kImplementationIDSpace, kGfxStateDataPhase2ConverterImpl, kGraphicStylesPrefix + 199)
DECLARE_PMID(kImplementationIDSpace, kGfxAttrListPhase2ConverterImpl, kGraphicStylesPrefix + 200)
DECLARE_PMID(kImplementationIDSpace, kStrokeAttrSuiteASBImpl, kGraphicStylesPrefix + 201)
DECLARE_PMID(kImplementationIDSpace, kStrokeAttrSuiteLayoutCSBImpl, kGraphicStylesPrefix + 202)
DECLARE_PMID(kImplementationIDSpace, kStrokeAttrSuiteTextCSBImpl, kGraphicStylesPrefix + 203)
DECLARE_PMID(kImplementationIDSpace, kStrokeAttrSuiteTableCSBImpl, kGraphicStylesPrefix + 204)
DECLARE_PMID(kImplementationIDSpace, kStrokeAttrSuiteDefaultCSBImpl, kGraphicStylesPrefix + 205)
DECLARE_PMID(kImplementationIDSpace, kStrokeAttrSuiteLayoutCSBSelectionExtImpl, kGraphicStylesPrefix + 206)
DECLARE_PMID(kImplementationIDSpace, kStrokeAttrSuiteTextCSBSelectionExtImpl, kGraphicStylesPrefix + 207)
DECLARE_PMID(kImplementationIDSpace, kStrokeAttrSuiteTableCSBSelectionExtImpl, kGraphicStylesPrefix + 208)
DECLARE_PMID(kImplementationIDSpace, kLiveShapeGfxUtilsImpl, kGraphicStylesPrefix + 209)

// Layout Attribute impl ID declarations.
DECLARE_PMID(kImplementationIDSpace, kGfxLayout_BoolBackedRealAttrDataImpl, kGraphicStylesPrefix + 210)
DECLARE_PMID(kImplementationIDSpace, kGfxLayoutAttrInfoImpl, kGraphicStylesPrefix + 211)
DECLARE_PMID(kImplementationIDSpace, kGfxLayoutObjStyleAttrInfoImpl, kGraphicStylesPrefix + 212)
DECLARE_PMID(kImplementationIDSpace, kGfxLayoutPositionRefPointAttrInfoImpl, kGraphicStylesPrefix + 213)
DECLARE_PMID(kImplementationIDSpace, kGfxLayoutRefPointObjStyleAttrInfoImpl, kGraphicStylesPrefix + 214)
DECLARE_PMID(kImplementationIDSpace, kGfxLayoutObjStylesAttrHandlerImpl, kGraphicStylesPrefix + 215)
// End of Layout Attribute impl ID declarations.

// Layout Attrs Helper Utils
DECLARE_PMID(kImplementationIDSpace, kLayoutAttrsHelperUtilsImpl, kGraphicStylesPrefix + 216)

// Implemetations for the page item creation responder
DECLARE_PMID(kImplementationIDSpace, kGfxStylePostCreatePageItemServiceProviderImpl, kGraphicStylesPrefix + 217)
DECLARE_PMID(kImplementationIDSpace, kGfxStylePostCreatePageItemResponderImpl, kGraphicStylesPrefix + 218)
DECLARE_PMID(kImplementationIDSpace, kDocPostAddToHierarchyObserverImpl, kGraphicStylesPrefix + 219)
DECLARE_PMID(kImplementationIDSpace, kGraphicAttrInt32_NoPersistImpl, kGraphicStylesPrefix +220)
DECLARE_PMID(kImplementationIDSpace, kSplineTransformAttrOverridesImpl, kGraphicStylesPrefix + 221)


// <Service ID>
#pragma mark Service IDs

//_______________________________________________________________________________
// Service IDs
//
// These service IDs are the means for accessing installed stroke and fill
// objects.  In this way graphic styles does not need to know explicitly about
// any of the objects prior to runtime.
// 
//_______________________________________________________________________________

DECLARE_PMID(kServiceIDSpace, kPathStrokerService, kGraphicStylesPrefix + 1)
DECLARE_PMID(kServiceIDSpace, kPathEndStrokerService, kGraphicStylesPrefix + 2)
DECLARE_PMID(kServiceIDSpace, kPathCornerService, kGraphicStylesPrefix + 3)
DECLARE_PMID(kServiceIDSpace, kRenderingObjectService, kGraphicStylesPrefix + 4)


// <Widget ID>
#pragma mark Widget IDs

// <Action ID>
#pragma mark Action IDs

// User Action Categories
DECLARE_PMID(kUserActionCategoryIDSpace, kGraphicAttributeCategory, kGraphicStylesPrefix + 1)

// <InvalHandler ID>
#pragma mark Action IDs
//_______________________________________________________________________________
// InvalHandlerTypeID
//_______________________________________________________________________________
DECLARE_PMID(kInvalHandlerIDSpace, kGraphicColorXFormInvalHandlerID, kGraphicStylesPrefix + 1)

// Error IDs
DECLARE_PMID(kErrorIDSpace, kCantSwapActiveProxyTargetError, kGraphicStylesPrefix + 1)

// <Script Element ID>
// Script Element IDs
//Objects
DECLARE_PMID(kScriptInfoIDSpace, kStrokeFillProxySettingsObjectScriptElement,		kGraphicStylesPrefix + 10)
//Properties
DECLARE_PMID(kScriptInfoIDSpace, kStrokeFillProxySettingsPropertyScriptElement,		kGraphicStylesPrefix + 99)
DECLARE_PMID(kScriptInfoIDSpace, kStrokeFillActiveProxyPropertyScriptElement,		kGraphicStylesPrefix + 100)
DECLARE_PMID(kScriptInfoIDSpace, kStrokeFillProxyTargetPropertyScriptElement,		kGraphicStylesPrefix + 101)
DECLARE_PMID(kScriptInfoIDSpace, kStrokeFillProxyFillColorPropertyScriptElement,	kGraphicStylesPrefix + 102)
DECLARE_PMID(kScriptInfoIDSpace, kStrokeFillProxyStrokeColorPropertyScriptElement,	kGraphicStylesPrefix + 103)
//Enums
DECLARE_PMID(kScriptInfoIDSpace, kStrokeFillProxyOptionsEnumScriptElement,			kGraphicStylesPrefix + 200)
DECLARE_PMID(kScriptInfoIDSpace, kStrokeFillTargetOptionsEnumScriptElement,			kGraphicStylesPrefix + 201)

//ScriptIDs

enum GraphicStateScriptIDs
{
	c_StrokeFillProxySettings		= 'cSFP',
	p_StrokeFillProxySettings		= 'pSFP',
	p_Active						= 'APav',
	en_StrokeFillProxyOptions		= 'SFPO',
	en_Stroke						= 'Strk',
	en_Fill							= 'Fill',
	en_StrokeFillTargetOptions		= 'SFTO',
	en_FormattingAffectsContainer	= 'FoAC',
	en_FormattingAffectsText		= 'FoAT',
} ;

//GUIDS
// {534C6846-8D1D-4df2-9757-121B50949336}
#define kStrokeFillProxySettings_CLSID { 0x534c6846, 0x8d1d, 0x4df2, { 0x97, 0x57, 0x12, 0x1b, 0x50, 0x94, 0x93, 0x36 } }


// creating the Boss Alias so that we can reuse the existing bosses and can have
// name consistency as well
#define kGraphicStyleLiveCornerTLImplAttrBoss kGraphicStyleCornerImplAttrBoss
#define kGraphicStyleLiveCornerTLRadiusAttrBoss kGraphicStyleCornerRadiusAttrBoss

#endif // _GraphicStyles_ID_









