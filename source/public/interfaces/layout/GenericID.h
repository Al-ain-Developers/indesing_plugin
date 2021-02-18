//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/GenericID.h $
//  
//  Owner: Robin_Briggs
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
//  Contains IDs used by the generic page item plug-in
//  
//========================================================================================

#ifndef __GenericID__
#define __GenericID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kGenericIDPrefix	RezLong(0x2C00)
#define kGenericIDPrefix2	RezLong(0x1e200)
#define kObjectStylePrefix	RezLong(0x1b900)

// <Start IDC>
// PluginID
#define kGenericPluginName 				"Generic Page Item"
DECLARE_PMID(kPlugInIDSpace, kGenericPluginID, kGenericIDPrefix + 1)


// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kNewPageItemCmdBoss, kGenericIDPrefix + 1)
DECLARE_PMID(kClassIDSpace, kPlacePICmdBoss, kGenericIDPrefix + 2)
DECLARE_PMID(kClassIDSpace, kMoveRelativeCmdBoss, kGenericIDPrefix + 3)
DECLARE_PMID(kClassIDSpace, kMoveAbsoluteCmdBoss, kGenericIDPrefix + 4)
DECLARE_PMID(kClassIDSpace, kVisibilityDrawEventServicesBoss, kGenericIDPrefix + 5)
DECLARE_PMID(kClassIDSpace, kHiddenItemsM2MListenerServiceBoss, kGenericIDPrefix + 6)
DECLARE_PMID(kClassIDSpace, kLockedItemsM2MListenerServiceBoss, kGenericIDPrefix + 7)
// gap
DECLARE_PMID(kClassIDSpace, kTransformBoss, kGenericIDPrefix + 14)
DECLARE_PMID(kClassIDSpace, kPageItemBoss, kGenericIDPrefix + 15)	// used for inheritance only!
DECLARE_PMID(kClassIDSpace, kDrawablePageItemBoss, kGenericIDPrefix + 16)	// used for inheritance only!
// gap
//DECLARE_PMID(kClassIDSpace, kScaleItemCmdBoss, kGenericIDPrefix + 19)
DECLARE_PMID(kClassIDSpace, kFrameFittingScriptProviderBoss, kGenericIDPrefix + 20)
// gap
DECLARE_PMID(kClassIDSpace, kAddToHierarchyCmdBoss, kGenericIDPrefix + 25)
DECLARE_PMID(kClassIDSpace, kRemoveFromHierarchyCmdBoss, kGenericIDPrefix + 26)
DECLARE_PMID(kClassIDSpace, kPlaceGraphicFrameTrackerBoss, kGenericIDPrefix + 28)
DECLARE_PMID(kClassIDSpace, kPlaceGraphicFrameCmdBoss, kGenericIDPrefix + 29)
DECLARE_PMID(kClassIDSpace, kConvertFrameToItemCmdBoss, kGenericIDPrefix + 30)
DECLARE_PMID(kClassIDSpace, kConvertItemToFrameCmdBoss, kGenericIDPrefix + 31)
DECLARE_PMID(kClassIDSpace, kPlaceItemInGraphicFrameCmdBoss, kGenericIDPrefix + 32)
DECLARE_PMID(kClassIDSpace, kSetLockPositionCmdBoss, kGenericIDPrefix + 33)
DECLARE_PMID(kClassIDSpace, kSetItemLockDataCmdBoss, kGenericIDPrefix + 34)
DECLARE_PMID(kClassIDSpace, kPageItemScriptM2MListenerServiceBoss, kGenericIDPrefix + 35)
DECLARE_PMID(kClassIDSpace, kSetVisibleCmdBoss, kGenericIDPrefix + 36)
DECLARE_PMID(kClassIDSpace, kDownloadCmdBoss, kGenericIDPrefix + 37)
DECLARE_PMID(kClassIDSpace, kSetBoundingBoxCmdBoss, kGenericIDPrefix + 38)
DECLARE_PMID(kClassIDSpace, kSetPMMatrixCmdBoss, kGenericIDPrefix + 39)
DECLARE_PMID(kClassIDSpace, kResizeItemsCmdBoss, kGenericIDPrefix + 40)
DECLARE_PMID(kClassIDSpace, kFitFrameToContentCmdBoss, kGenericIDPrefix + 41)
DECLARE_PMID(kClassIDSpace, kFitContentToFrameCmdBoss, kGenericIDPrefix + 42)
DECLARE_PMID(kClassIDSpace, kFitContentPropCmdBoss, kGenericIDPrefix + 43)
DECLARE_PMID(kClassIDSpace, kCenterContentInFrameCmdBoss, kGenericIDPrefix + 44)
DECLARE_PMID(kClassIDSpace, kAlignContentInFrameCmdBoss, kGenericIDPrefix + 45)
DECLARE_PMID(kClassIDSpace, kAlignContentInFrameCmdDataBoss, kGenericIDPrefix + 46)
DECLARE_PMID(kClassIDSpace, kAlignCmdBoss, kGenericIDPrefix + 47)
DECLARE_PMID(kClassIDSpace, kDistributeCmdBoss, kGenericIDPrefix + 48)
DECLARE_PMID(kClassIDSpace, kPageItemCreateMetaDataCmdBoss, kGenericIDPrefix + 49)
DECLARE_PMID(kClassIDSpace, kSetDrawOptionOverrideCmdBoss, kGenericIDPrefix + 50)
DECLARE_PMID(kClassIDSpace, kSetGraphicFrameDataCmdBoss, kGenericIDPrefix + 51)
DECLARE_PMID(kClassIDSpace, kGenericErrorStringServiceBoss, kGenericIDPrefix + 52)
DECLARE_PMID(kClassIDSpace, kSetFittingOptionsCmdBoss, kGenericIDPrefix + 53)
//DECLARE_PMID(kClassIDSpace, kSetDimensionsCmdBoss, kGenericIDPrefix + 54)
DECLARE_PMID(kClassIDSpace, kConvertItemToTextCmdBoss, kGenericIDPrefix + 55)
DECLARE_PMID(kClassIDSpace, kPathGeometryBoss, kGenericIDPrefix + 56)
DECLARE_PMID(kClassIDSpace, kNewPISignalMgrBoss, kGenericIDPrefix + 57)
DECLARE_PMID(kClassIDSpace, kPageItemAdornmentBoss, kGenericIDPrefix + 58)
DECLARE_PMID(kClassIDSpace, kAddPageItemAdornmentCmdBoss, kGenericIDPrefix + 59)
DECLARE_PMID(kClassIDSpace, kRemovePageItemAdornmentCmdBoss, kGenericIDPrefix + 60)
DECLARE_PMID(kClassIDSpace, kAddPageItemHandleAdornmentCmdBoss, kGenericIDPrefix + 61)
DECLARE_PMID(kClassIDSpace, kRemovePageItemHandleAdornmentCmdBoss, kGenericIDPrefix + 62)
DECLARE_PMID(kClassIDSpace, kGraphicFrameEdgeAdornmentBoss, kGenericIDPrefix + 63)
DECLARE_PMID(kClassIDSpace, kRegisterScrapItemCmdBoss, kGenericIDPrefix + 64)
DECLARE_PMID(kClassIDSpace, kUnregisterScrapItemCmdBoss, kGenericIDPrefix + 65)
DECLARE_PMID(kClassIDSpace, kPasteGraphicItemCmdBoss, kGenericIDPrefix + 66)
DECLARE_PMID(kClassIDSpace, kTransformPageItemsCmdBoss, kGenericIDPrefix + 68)
DECLARE_PMID(kClassIDSpace, kRedefineScalingCmdBoss, kGenericIDPrefix + 69)
DECLARE_PMID(kClassIDSpace, kBaseVisitorBoss, kGenericIDPrefix + 70)
DECLARE_PMID(kClassIDSpace, kPageItemScriptProviderBoss, kGenericIDPrefix + 71)
DECLARE_PMID(kClassIDSpace, kAllPageItemsScriptProviderBoss, kGenericIDPrefix + 72)
DECLARE_PMID(kClassIDSpace, kPageItemINXPropsScriptProviderBoss, kGenericIDPrefix + 73)
DECLARE_PMID(kClassIDSpace, kGenericConversionProviderBoss, kGenericIDPrefix + 74)
DECLARE_PMID(kClassIDSpace, kDeferredAnchoredObjectAdornmentBoss, kGenericIDPrefix + 75)
DECLARE_PMID(kClassIDSpace, kPageItemPropsScriptProviderBoss, kGenericIDPrefix + 76)
DECLARE_PMID(kClassIDSpace, kPageItemDefaultScriptProviderBoss, kGenericIDPrefix + 77 )
DECLARE_PMID(kClassIDSpace, kTranslatePageItemsCmdBoss, kGenericIDPrefix + 78)
//DECLARE_PMID(kClassIDSpace, kSetCustomWidthExportOptionCmdBoss, kGenericIDPrefix2 + 79 )
//DECLARE_PMID(kClassIDSpace, kSetCustomHeightExportOptionCmdBoss, kGenericIDPrefix2 + 80 )
// gap
DECLARE_PMID(kClassIDSpace, kGenericIteratorRegBoss, kGenericIDPrefix + 95)
//DECLARE_PMID(kClassIDSpace, kLayoutISuiteBoss, kGenericIDPrefix + 96)	�� no longer used ��
DECLARE_PMID(kClassIDSpace, kLayoutSuiteBoss, kGenericIDPrefix + 97)
DECLARE_PMID(kClassIDSpace, kNewLayoutSelectionBoss, kGenericIDPrefix + 98)
// gap
DECLARE_PMID(kClassIDSpace, kGenericPISuiteRegisterBoss, kGenericIDPrefix + 100)
DECLARE_PMID(kClassIDSpace, kPlaceHolderItemBoss, kGenericIDPrefix + 101)
//DECLARE_PMID(kClassIDSpace, kObsoleteSurrogatePageItemBoss, kGenericIDPrefix + 104 )
//DECLARE_PMID(kClassIDSpace, kObsoleteDeleteSurrogatePageItemCmdBoss, kGenericIDPrefix + 106 )
//DECLARE_PMID(kClassIDSpace, kObsoletePageItemCmdBoss, kGenericIDPrefix + 107 )
DECLARE_PMID(kClassIDSpace, kAdornmentIteratorBoss, kGenericIDPrefix + 108 )
DECLARE_PMID(kClassIDSpace, kSetEditBoxCustomSizeExportOptionCmdBoss,  kGenericIDPrefix + 109  )
// gap
// ---- Moved from Clipping Path Dialog plug-in
DECLARE_PMID(kClassIDSpace, kClip_ConversionProviderBoss, kGenericIDPrefix + 111)
DECLARE_PMID(kClassIDSpace, kSetClipValuesCmdBoss, kGenericIDPrefix + 112)
// ---- end move.
DECLARE_PMID(kClassIDSpace, kPolygonPrefsScriptProviderBoss, kGenericIDPrefix + 113)		//jwb 4/30/02 Moved from ScriptingID.h
DECLARE_PMID(kClassIDSpace, kSetRegPolyPrefsCmdBoss, kGenericIDPrefix + 114)
//DECLARE_PMID(kClassIDSpace, kSetLoupeToolPrefsCmdBoss, kGenericIDPrefix + 115)
DECLARE_PMID(kClassIDSpace, kBringToFrontCmdBoss, kGenericIDPrefix + 116)
DECLARE_PMID(kClassIDSpace, kBringForwardCmdBoss, kGenericIDPrefix + 117)
DECLARE_PMID(kClassIDSpace, kSendBackwardCmdBoss, kGenericIDPrefix + 118)
DECLARE_PMID(kClassIDSpace, kSendToBackCmdBoss, kGenericIDPrefix + 119)
DECLARE_PMID(kClassIDSpace, kGenericSwatchesRIDXNotifierHandlerBoss, kGenericIDPrefix + 120 )
DECLARE_PMID(kClassIDSpace, kPageItemScript40ProviderBoss, kGenericIDPrefix + 121 )
DECLARE_PMID(kClassIDSpace, kSetGraphicBoundsCmdBoss, kGenericIDPrefix + 122 )
DECLARE_PMID(kClassIDSpace, kPageItemConversionProviderBoss, kGenericIDPrefix + 123 )
DECLARE_PMID(kClassIDSpace, kPageItemScript50ProviderBoss, kGenericIDPrefix + 124 )
DECLARE_PMID(kClassIDSpace, kPageItemScript70ProviderBoss, kGenericIDPrefix + 125 )
DECLARE_PMID(kClassIDSpace, kSetPageItemNameCmdBoss, kGenericIDPrefix + 126 )
//gap
DECLARE_PMID(kClassIDSpace, kTransformAgainNewDocResponderBoss, kGenericIDPrefix + 173)
DECLARE_PMID(kClassIDSpace, kTransformAgainOpenDocResponderBoss, kGenericIDPrefix + 174)
DECLARE_PMID(kClassIDSpace, kTransformAgainSentinelCmdBoss, kGenericIDPrefix + 175 )
DECLARE_PMID(kClassIDSpace, kAlignDistributeScriptProviderBoss, kGenericIDPrefix + 176 )
DECLARE_PMID(kClassIDSpace, kSetDistributeOffsetCmdBoss, kGenericIDPrefix + 177 )
DECLARE_PMID(kClassIDSpace, kSetDistributeOffsetStateCmdBoss, kGenericIDPrefix + 178 )
DECLARE_PMID(kClassIDSpace, kAlignDistributePropertiesScriptProviderBoss, kGenericIDPrefix + 179 )
DECLARE_PMID(kClassIDSpace, kGenericDataPhase2ConversionBoss, kGenericIDPrefix + 180 )
DECLARE_PMID(kClassIDSpace, kLockAdornmentBoss, kGenericIDPrefix + 181)
//DECLARE_PMID(kClassIDSpace, kSetEditBoxCustomWidthUnitExportOptionCmdBoss, kGenericIDPrefix + 182 )
//DECLARE_PMID(kClassIDSpace, kSetEditBoxCustomHeightUnitExportOptionCmdBoss, kGenericIDPrefix + 183 )
DECLARE_PMID(kClassIDSpace, kFormFieldMissingFontAdornmentBoss, kGenericIDPrefix + 182)
//gap
DECLARE_PMID(kClassIDSpace, kTransformMatrixScriptObjectBoss, kGenericIDPrefix + 198 )
DECLARE_PMID(kClassIDSpace, kTransformMatrixScriptProviderBoss, kGenericIDPrefix + 199 )
DECLARE_PMID(kClassIDSpace, kLiveShapeModeHandleAdornmentBoss, kGenericIDPrefix + 200 )
DECLARE_PMID(kClassIDSpace, kSetAltTextSourceExportOptionCmdBoss, kGenericIDPrefix + 201 )
DECLARE_PMID(kClassIDSpace, kSetCustomAltTextExportOptionCmdBoss, kGenericIDPrefix + 202 )
DECLARE_PMID(kClassIDSpace, kSetAltTextMetadataExportOptionCmdBoss, kGenericIDPrefix + 203 )
DECLARE_PMID(kClassIDSpace, kSetActualTextSourceExportOptionCmdBoss, kGenericIDPrefix + 204 )
DECLARE_PMID(kClassIDSpace, kSetCustomActualTextExportOptionCmdBoss, kGenericIDPrefix + 205 )
DECLARE_PMID(kClassIDSpace, kSetActualTextMetadataExportOptionCmdBoss, kGenericIDPrefix + 206 )
DECLARE_PMID(kClassIDSpace, kSetTagTypeExportOptionCmdBoss, kGenericIDPrefix + 207 )
DECLARE_PMID(kClassIDSpace, kSetCustomConvExportOptionCmdBoss, kGenericIDPrefix + 208 )
DECLARE_PMID(kClassIDSpace, kSetImageTypeExportOptionCmdBoss, kGenericIDPrefix + 209 )
//DECLARE_PMID(kClassIDSpace, kSetObjectSizeExportOptionCmdBoss, kGenericIDPrefix + 210 )
DECLARE_PMID(kClassIDSpace, kSetImageResolutionExportOptionCmdBoss, kGenericIDPrefix + 211 )
DECLARE_PMID(kClassIDSpace, kSetJPEGEncodingExportOptionCmdBoss, kGenericIDPrefix + 212 )
DECLARE_PMID(kClassIDSpace, kSetJPEGQualityExportOptionCmdBoss, kGenericIDPrefix + 213 )
DECLARE_PMID(kClassIDSpace, kSetGIFPaletteTypeExportOptionCmdBoss, kGenericIDPrefix + 214 )
DECLARE_PMID(kClassIDSpace, kSetGIFInterlacedExportOptionCmdBoss, kGenericIDPrefix + 215 )
DECLARE_PMID(kClassIDSpace, kSetCustomLayoutExportOptionCmdBoss, kGenericIDPrefix + 216 )
DECLARE_PMID(kClassIDSpace, kSetImageAlignmentExportOptionCmdBoss, kGenericIDPrefix + 217 )
DECLARE_PMID(kClassIDSpace, kSetImageSpaceBeforeExportOptionCmdBoss, kGenericIDPrefix + 218 )
DECLARE_PMID(kClassIDSpace, kSetImageSpaceAfterExportOptionCmdBoss, kGenericIDPrefix + 219 )
DECLARE_PMID(kClassIDSpace, kObjectFCOECustomContentConvAttrBoss, kGenericIDPrefix + 220)
DECLARE_PMID(kClassIDSpace, kSetUseImagePageBreakExportOptionCmdBoss, kGenericIDPrefix + 221 )
DECLARE_PMID(kClassIDSpace, kSetImagePageBreakExportOptionCmdBoss, kGenericIDPrefix + 222 )
DECLARE_PMID(kClassIDSpace, kObjectExportOptionsScriptProviderBoss, kGenericIDPrefix + 223 )
DECLARE_PMID(kClassIDSpace, kSetCustomLayoutTypeExportOptionCmdBoss, kGenericIDPrefix + 224 )

//export options attributes
DECLARE_PMID(kClassIDSpace, kObjectFCOEImageTypeAttrBoss, kGenericIDPrefix + 225)
DECLARE_PMID(kClassIDSpace, kObjectFCOEImageSizeAttrBoss, kGenericIDPrefix + 226)
DECLARE_PMID(kClassIDSpace, kObjectFCOEImgResolutionAttrBoss, kGenericIDPrefix + 227)
DECLARE_PMID(kClassIDSpace, kObjectFCOEJPEGEncodingAttrBoss, kGenericIDPrefix + 228)
DECLARE_PMID(kClassIDSpace, kObjectFCOEJPEGQualityAttrBoss, kGenericIDPrefix + 229)
DECLARE_PMID(kClassIDSpace, kObjectFCOEGIFPaletteTypeAttrBoss, kGenericIDPrefix + 230)
DECLARE_PMID(kClassIDSpace, kObjectFCOEGIFInterlacedAttrBoss, kGenericIDPrefix + 231)
DECLARE_PMID(kClassIDSpace, kObjectFCOECustomLayoutAttrBoss, kGenericIDPrefix + 232)
DECLARE_PMID(kClassIDSpace, kObjectFCOECustomLayoutTypeAttrBoss, kGenericIDPrefix + 233)
DECLARE_PMID(kClassIDSpace, kObjectFCOEImageAlignmentAttrBoss, kGenericIDPrefix + 234)
DECLARE_PMID(kClassIDSpace, kObjectFCOEImgSpaceBeforeAttrBoss, kGenericIDPrefix + 235)
DECLARE_PMID(kClassIDSpace, kObjectFCOEImgSpaceAfterAttrBoss, kGenericIDPrefix + 236)
DECLARE_PMID(kClassIDSpace, kObjectFCOEUseImagePageBreakAttrBoss, kGenericIDPrefix + 237)
DECLARE_PMID(kClassIDSpace, kObjectFCOEImagePageBreakAttrBoss, kGenericIDPrefix + 238)
DECLARE_PMID(kClassIDSpace, kObjectFCOECustomImgConvAttrBoss, kGenericIDPrefix + 239)
DECLARE_PMID(kClassIDSpace, kObjectFCOEAltTextSourceTypeAttrBoss, kGenericIDPrefix + 240)
DECLARE_PMID(kClassIDSpace, kObjectFCOECustomAltTextAttrBoss, kGenericIDPrefix + 241)
DECLARE_PMID(kClassIDSpace, kObjectFCOEAltTextMetadataPropAttrBoss, kGenericIDPrefix + 242)
DECLARE_PMID(kClassIDSpace, kObjectFCOECustomActualTextAttrBoss, kGenericIDPrefix + 243)
DECLARE_PMID(kClassIDSpace, kObjectFCOEActualTextSourceTypeAttrBoss, kGenericIDPrefix + 244)
DECLARE_PMID(kClassIDSpace, kObjectFCOEActualTextMetadataPropAttrBoss, kGenericIDPrefix + 245)
DECLARE_PMID(kClassIDSpace, kObjectFCOETagTypeAttrBoss, kGenericIDPrefix + 246)
DECLARE_PMID(kClassIDSpace, kObjStylesOEOptionsDataBoss, kGenericIDPrefix + 247)
DECLARE_PMID(kClassIDSpace, kSetObjectExportOptionsCmdBoss, kGenericIDPrefix + 248 )
DECLARE_PMID(kClassIDSpace, kObjectExportNewPIResponderBoss, kGenericIDPrefix + 249 )
DECLARE_PMID(kClassIDSpace, kSetUseOriginalImageOptionCmdBoss, kGenericIDPrefix + 250 )
DECLARE_PMID(kClassIDSpace, kObjectFCOEUseOriginalImageAttrBoss, kGenericIDPrefix + 251)
DECLARE_PMID(kClassIDSpace, kSetEpubTypeExportOptionCmdBoss, kGenericIDPrefix + 252)
DECLARE_PMID(kClassIDSpace, kObjectFCOEEpubTypeAttrBoss, kGenericIDPrefix + 253)
DECLARE_PMID(kClassIDSpace, kSetCustomSizeTypeExportOptionCmdBoss, kGenericIDPrefix + 254 )
DECLARE_PMID(kClassIDSpace, kSetCustomContentConvOptionCmdBoss, kGenericIDPrefix + 255 )

DECLARE_PMID(kClassIDSpace, kGlobalAdornmentStartupShutDownBoss, kGenericIDPrefix2 + 1)
DECLARE_PMID(kClassIDSpace, kStockAdornmentBoss, kGenericIDPrefix2 + 2)
DECLARE_PMID(kClassIDSpace, kLayoutAttributeScriptProviderBoss, kGenericIDPrefix2 + 3)
DECLARE_PMID(kClassIDSpace, kPageItemOverrideM2MListenerServiceBoss, kGenericIDPrefix2 + 4)
DECLARE_PMID(kClassIDSpace, kObjStylesTFOContentIteratorRegBoss, kGenericIDPrefix2 + 5)
DECLARE_PMID(kClassIDSpace, kSetSVGExportTypeExportOptionCmdBoss, kGenericIDPrefix2 + 6)
DECLARE_PMID(kClassIDSpace, kSetApplyOnAllSVGsOptionCmdBoss, kGenericIDPrefix2 + 7)

// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IPLACEPITRACKERDATA, kGenericIDPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IPLACEPIDATA, kGenericIDPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEITEMNAME, kGenericIDPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IHIERARCHY, kGenericIDPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEITEMNAMEFACADE, kGenericIDPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IKEYOBJECTUIDDATA, kGenericIDPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRANSFORM, kGenericIDPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IDISTRIBUTEREALNUMBERDATA, kGenericIDPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_USEDISTRIBUTEVALUEDATA, kGenericIDPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRAPITEM, kGenericIDPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETFITTINGOPTIONSCMDDATA, kGenericIDPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_INEWPAGEITEMCMDDATA, kGenericIDPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IMOVEPOINTCMDDATA, kGenericIDPrefix + 13)
//DECLARE_PMID(kInterfaceIDSpace, IID_IROTATEITEMCMDDATA, kGenericIDPrefix + 14)
//DECLARE_PMID(kInterfaceIDSpace, IID_IMOVEABSOLUTECMDDATA, kGenericIDPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IMOVERELATIVECMDDATA, kGenericIDPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IBACKGROUNDSHAPE, kGenericIDPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_IHIERARCHYCMDDATA, kGenericIDPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICFRAMEPREFERENCES, kGenericIDPrefix + 19)
//DECLARE_PMID(kInterfaceIDSpace, IID_ISKEWITEMCMDDATA, kGenericIDPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_IRECTLISTDATA, kGenericIDPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_IPMMATRIXLISTDATA, kGenericIDPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_IRESIZEITEMSCMDDATA, kGenericIDPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_IALIGNCONTENTINFRAMECMDDATA, kGenericIDPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_ILOCKPOSITION, kGenericIDPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEITEMCACHE, kGenericIDPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_IOEOPTIONSEPUBUTILS, kGenericIDPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_IBOUNDSCHECKER, kGenericIDPrefix + 28) // Just an ID. Implementation is an ICOMMANDCHECKER
DECLARE_PMID(kInterfaceIDSpace, IID_ISETBOUNDINGBOXCMDDATA, kGenericIDPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_IPLACEBEHAVIOR, kGenericIDPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRANSFORM_DOCUMENT, kGenericIDPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_IGEOMETRY_DOCUMENT, kGenericIDPrefix + 32)
DECLARE_PMID(kInterfaceIDSpace, IID_IPLACEBEHAVIORUI, kGenericIDPrefix + 33)
DECLARE_PMID(kInterfaceIDSpace, IID_INEWPAGEITEMACTION, kGenericIDPrefix + 34)
DECLARE_PMID(kInterfaceIDSpace, IID_INEWPAGEITEMSIGNALDATA, kGenericIDPrefix + 35)
DECLARE_PMID(kInterfaceIDSpace, IID_IADORNMENTSHAPE, kGenericIDPrefix + 36)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEITEMADORNMENTLIST, kGenericIDPrefix + 37)
DECLARE_PMID(kInterfaceIDSpace, IID_IADORNMENTHANDLESHAPE, kGenericIDPrefix + 38)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRANSLATECMDDATA, kGenericIDPrefix + 39)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRANSFORMCMDDATA, kGenericIDPrefix + 40)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEITEMBOUNDSLIST, kGenericIDPrefix + 41)
DECLARE_PMID(kInterfaceIDSpace, IID_IHIERARCHY_DOCUMENT, kGenericIDPrefix + 42)
DECLARE_PMID(kInterfaceIDSpace, IID_IBASEVISITOR, kGenericIDPrefix + 43)
DECLARE_PMID(kInterfaceIDSpace, IID_IBASEHANDLER, kGenericIDPrefix + 44)
DECLARE_PMID(kInterfaceIDSpace, IID_IBASESELECTIONHANDLERDATA, kGenericIDPrefix + 45)
DECLARE_PMID(kInterfaceIDSpace, IID_IVISITORHELPER, kGenericIDPrefix + 46)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEITEMUTILS, kGenericIDPrefix + 47 )
DECLARE_PMID(kInterfaceIDSpace, IID_IPATHINFOUTILS, kGenericIDPrefix + 48 )
DECLARE_PMID(kInterfaceIDSpace, IID_IGUIDESELECTIONUTILS, kGenericIDPrefix + 49 )
DECLARE_PMID(kInterfaceIDSpace, IID_IFRAMECONTENTUTILS, kGenericIDPrefix + 50 )
DECLARE_PMID(kInterfaceIDSpace, IID_IGROUPITEMUTILS, kGenericIDPrefix + 51 )
DECLARE_PMID(kInterfaceIDSpace, IID_IFRAMEFITTINGOPTIONS_DOCUMENT, kGenericIDPrefix + 52 )
DECLARE_PMID(kInterfaceIDSpace, IID_IITEMCONTEXTUTILS, kGenericIDPrefix + 53 )
DECLARE_PMID(kInterfaceIDSpace, IID_ITRANSFORMUPDATEUTILS, kGenericIDPrefix + 54 )
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEITEMSCRIPTUTILS, kGenericIDPrefix + 55 )
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEITEMTYPEUTILS, kGenericIDPrefix + 56 )
DECLARE_PMID(kInterfaceIDSpace, IID_IPATHUTILS, kGenericIDPrefix + 57 )
DECLARE_PMID(kInterfaceIDSpace, IID_IBOUNDSUTILS, kGenericIDPrefix + 58 )
DECLARE_PMID(kInterfaceIDSpace, IID_IPASTEBOARDUTILS, kGenericIDPrefix + 59 )
DECLARE_PMID(kInterfaceIDSpace, IID_ISCALEOBJECT, kGenericIDPrefix + 60 )
DECLARE_PMID(kInterfaceIDSpace, IID_ISCALEOBJECTCMDDATA, kGenericIDPrefix + 61 )
DECLARE_PMID(kInterfaceIDSpace, IID_ISTANDOFFUTILS, kGenericIDPrefix + 62 )
DECLARE_PMID(kInterfaceIDSpace, IID_IVALIDATEGEOMETRYUTILS, kGenericIDPrefix + 63 )
DECLARE_PMID(kInterfaceIDSpace, IID_IPATHPOINTUTILS, kGenericIDPrefix + 64 )
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEITEMSCRAPUTILS, kGenericIDPrefix + 65 )
DECLARE_PMID(kInterfaceIDSpace, IID_ISETDRAWOPTIONOVERRIDECMDDATA, kGenericIDPrefix + 66)
DECLARE_PMID(kInterfaceIDSpace, IID_IFILLFRAMEBOOLDATA, kGenericIDPrefix + 67)	// Just an ID. Implementation is an IBOOLDATA
DECLARE_PMID(kInterfaceIDSpace, IID_IADORNMENTITERATOR, kGenericIDPrefix + 68 )
DECLARE_PMID(kInterfaceIDSpace, IID_IHIERARCHYUTILS, kGenericIDPrefix + 69 )
DECLARE_PMID(kInterfaceIDSpace, IID_IDUPLICATE_DOCUMENT, kGenericIDPrefix + 70)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEITEMEVENTACTION, kGenericIDPrefix + 71 )
DECLARE_PMID(kInterfaceIDSpace, IID_IACTIVATETEXTEDITOR, kGenericIDPrefix + 72 )
DECLARE_PMID(kInterfaceIDSpace, IID_IDRAWOPTIONOVERRIDE, kGenericIDPrefix + 73)
DECLARE_PMID(kInterfaceIDSpace, IID_IPASTEBEHAVIOR, kGenericIDPrefix + 74 )
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTROLSTRIPGENERICPISUITE, kGenericIDPrefix + 75 )
DECLARE_PMID(kInterfaceIDSpace, IID_IREGPOLYPREFERENCES, kGenericIDPrefix + 76)
DECLARE_PMID(kInterfaceIDSpace, IID_IREGPOLYPREFSCMDDATA, kGenericIDPrefix + 77)
//DECLARE_PMID(kInterfaceIDSpace, IID_ILOUPETOOLPREFS, kGenericIDPrefix + 78)
//DECLARE_PMID(kInterfaceIDSpace, IID_ILOUPETOOLPREFSCMDDATA, kGenericIDPrefix + 79)
DECLARE_PMID(kInterfaceIDSpace, IID_IITEMLOCKDATA, kGenericIDPrefix + 80)
DECLARE_PMID(kInterfaceIDSpace, IID_IITEMLOCK_DOCUMENT, kGenericIDPrefix + 81 )
DECLARE_PMID(kInterfaceIDSpace, IID_IDONOTIFYFLAG, kGenericIDPrefix + 82 )
DECLARE_PMID(kInterfaceIDSpace, IID_IDOINVALFLAG, kGenericIDPrefix + 83 )
DECLARE_PMID(kInterfaceIDSpace, IID_ILOCKINLINESTORIESDATA, kGenericIDPrefix + 84 )
DECLARE_PMID(kInterfaceIDSpace, IID_ISPACEFLAG, kGenericIDPrefix + 85 )
DECLARE_PMID(kInterfaceIDSpace, IID_IFRAMECONTENTFACADE, kGenericIDPrefix + 86 )
DECLARE_PMID(kInterfaceIDSpace, IID_IDISTRIBUTEOFFSETDATA, kGenericIDPrefix + 87 )
DECLARE_PMID(kInterfaceIDSpace, IID_IDISTRIBUTESPACEOFFSETDATA, kGenericIDPrefix + 88 )
DECLARE_PMID(kInterfaceIDSpace, IID_ITRANSFORMFACADE, kGenericIDPrefix + 89 )
DECLARE_PMID(kInterfaceIDSpace, IID_IGEOMETRYFACADE, kGenericIDPrefix + 90 )
DECLARE_PMID(kInterfaceIDSpace, IID_ITRANSFORMMATRIX, kGenericIDPrefix + 91 )
DECLARE_PMID(kInterfaceIDSpace, IID_ICLEAROVERRIDESWHENAPPLYSTYLE, kGenericIDPrefix + 92 )
DECLARE_PMID(kInterfaceIDSpace, IID_IIGNORENONRECTINSETADJUST, kGenericIDPrefix + 93)
DECLARE_PMID(kInterfaceIDSpace, IID_IVISIBLE, kGenericIDPrefix + 94 )
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEITEMVISIBILITYFACADE, kGenericIDPrefix + 95 )
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEITEMVISIBILITYSUITE, kGenericIDPrefix + 96 )
DECLARE_PMID(kInterfaceIDSpace, IID_IHIDDENITEMS, kGenericIDPrefix + 97 )
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCUMENT_BROADCAST, kGenericIDPrefix + 98 )		// Used for broadcast only
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYOUTCSB_BROADCAST, kGenericIDPrefix + 99 )		// Used for broadcast only
DECLARE_PMID(kInterfaceIDSpace, IID_IALIGNSETTINGS, kGenericIDPrefix + 100)
DECLARE_PMID(kInterfaceIDSpace, IID_IITEMTHUMBNAILFACADE, kGenericIDPrefix + 101)

//
// All these IID_IHIERARCHY_* interfaces are really messages that are part
// of the IM2MMessageManager scheme. They are used to communicate well known
// changes to a Target to Hierarchy Ancestors/Descendents.
// See HierarchyListener for how this is done.
//
// Child adding to/removing from Hierarchy. NOT forwarded.
DECLARE_PMID(kInterfaceIDSpace, IID_IHIERARCHY_CHILD, kGenericIDPrefix + 102)

// Root of the Hierarchy changing. Forwarded to all descendents
DECLARE_PMID(kInterfaceIDSpace, IID_IHIERARCHY_ROOT, kGenericIDPrefix + 103)

// Spread of the Hierarchy changing (for non Root changes). Used for transitory
// Hierarchy members such as Inlines. Forwarded to all descendents.
DECLARE_PMID(kInterfaceIDSpace, IID_IHIERARCHY_SPREAD, kGenericIDPrefix + 104)

// Layer of the Hierarchy changing. Sent to the Hierarchy moving and forwarded
// to all descendents.
DECLARE_PMID(kInterfaceIDSpace, IID_IHIERARCHY_LAYER, kGenericIDPrefix + 105)

// Effective ZOrder of the Hierarchy changing. Sent to the Hierarch(ies) moving
// and forwarded to all descendents.
DECLARE_PMID(kInterfaceIDSpace, IID_IHIERARCHY_ZORDER, kGenericIDPrefix + 106)

// IID_ITRANSFORM on a Hierarchy ancestor or child changing. Forwarded to the
// parent and all descendents.
DECLARE_PMID(kInterfaceIDSpace, IID_IHIERARCHY_TRANSFORM, kGenericIDPrefix + 107)

// IID_IGEOMETRY on a Hierarchy child changing. Forwarded to the parent.
DECLARE_PMID(kInterfaceIDSpace, IID_IHIERARCHY_GEOMETRY, kGenericIDPrefix + 108)

// IID_IPATHGEOMETRY on a Hierarchy ancestor changing. Forwarded to all
// descendents BUT not typically forwarded to sub-Hierarchies such as TOP.
DECLARE_PMID(kInterfaceIDSpace, IID_IHIERARCHY_PATHGEOMETRY, kGenericIDPrefix + 109)

// Synthetic message - some property of an ancestor has changed which *may*
// mean that our effective visibility has changed. Forwarded to all descendents.
DECLARE_PMID(kInterfaceIDSpace, IID_IHIERARCHY_VISIBILITY, kGenericIDPrefix + 110)

// Synthetic message - an Inline ancestor is part of a WaxRun rebuild and has
// discovered that it's position will change from where it was when first
// applied. This can occur due to re-justification on the part of the Composer
// due to things such as, for example, font changes or page number changes.
//
// This message always preceeds a IID_IHIERARCHY_TRANSFORM which represents
// the actual change to the effective transform. As such thus this synthetic
// message provides a qualifier to the later IID_IHIERARCHY_TRANSFORM message.
//
// The policy around rebuilt is that all the normal transform reactive behavior
// needs to take place - such as invalidating PB caches - but that nothing
// should be done that would trigger damage or re-composition.
//
// So, for example, StandOffs and MultiColumnTextFrames should react to the
// movement relative to the Spread by damaging content.
DECLARE_PMID(kInterfaceIDSpace, IID_IHIERARCHY_INLINEREBUILDSHIFT, kGenericIDPrefix + 111)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEITEMLOCKFACADE, kGenericIDPrefix + 112)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEITEMSCRAPFACADE, kGenericIDPrefix + 113)
DECLARE_PMID(kInterfaceIDSpace, IID_ILOCKEDITEMS, kGenericIDPrefix + 114 )

// Synthetic message to the spline listener that tells it the user (or a script)
// is doing a content fit.
DECLARE_PMID(kInterfaceIDSpace, IID_IUSERTRIGGEREDFRAMEFIT, kGenericIDPrefix + 115)

// Synthetic message - sent from SpreadLayer bosses to kPageBoss IHierarchy
// children when their index within the Hierarchy list is about to change.
// So if you insert a new child at index 0 then all the other children will see
// this message. NOT forwarded.
//
// This is to support Pages determining that their index within their parent
// has changed since that influences how their effective Master.
DECLARE_PMID(kInterfaceIDSpace, IID_IHIERARCHY_CINDEX, kGenericIDPrefix + 116)

DECLARE_PMID(kInterfaceIDSpace, IID_IOBJECTEXPORTOPTIONS, kGenericIDPrefix + 117)
DECLARE_PMID(kInterfaceIDSpace, IID_IOBJECTEXPORTOPTIONSDATA, kGenericIDPrefix + 118)
DECLARE_PMID(kInterfaceIDSpace, IID_IOBJECTEXPORTOPTIONSSUITE, kGenericIDPrefix + 119)
DECLARE_PMID(kInterfaceIDSpace, IID_IEXPORTOPTIONSUTILS, kGenericIDPrefix + 120)
//
// Synthetic message - called from the DataBase::DeleteUID() method before
// the UID is actually deleted - note that there will never be subsequent call
// to M2MMessageListener::Validate() because the UID will be deleted.
//
// 01/05/12 dwaterfa: This is hooked into the DataBase at a very low level and
// that creates problems for AutoUndo. As a result AutoUndo we will SUPPRESS
// this notification when it directly deletes UIDs as part of Undo OR Redo. 
// The upshot of this is that for most Listeners you will only be called on the
// Do() of a DeleteUID operation and never for Undo() or Redo() of that
// operation. Note that during Undo/Redo operations inval handlers can be called
// and THEY might DeleteUIDs and for those you WILL be called - it is only those
// UIDs which the AutoUndo mechanism remembers directly does this apply too.
//
DECLARE_PMID(kInterfaceIDSpace, IID_IDATABASE_DELETEUID, kGenericIDPrefix + 121)
DECLARE_PMID(kInterfaceIDSpace, IID_INAMESPACEPREFIXDATA, kGenericIDPrefix + 122)
DECLARE_PMID(kInterfaceIDSpace, IID_IPROPERTYPATHDATA, kGenericIDPrefix + 123)
// Object export options command notifications
DECLARE_PMID(kInterfaceIDSpace, IID_IALTTEXTSOURCEEXPORTOPTION, kGenericIDPrefix + 124)
DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMALTTEXTEXPORTOPTION, kGenericIDPrefix + 125)
DECLARE_PMID(kInterfaceIDSpace, IID_IALTTEXTMETADATAEXPORTOPTION, kGenericIDPrefix + 126)
DECLARE_PMID(kInterfaceIDSpace, IID_IACTUALTEXTSOURCEEXPORTOPTION, kGenericIDPrefix + 127)
DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMACTUALTEXTEXPORTOPTION, kGenericIDPrefix + 128)
DECLARE_PMID(kInterfaceIDSpace, IID_IACTUALTEXTMETADATAEXPORTOPTION, kGenericIDPrefix + 129)
DECLARE_PMID(kInterfaceIDSpace, IID_ITAGTYPEEXPORTOPTION, kGenericIDPrefix + 130)
DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMCONVEXPORTOPTION, kGenericIDPrefix + 131)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGETYPEEXPORTOPTION, kGenericIDPrefix + 132)
DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMCONTENTCONVEXPORTOPTION, kGenericIDPrefix + 133)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGERESOLUTIONEXPORTOPTION, kGenericIDPrefix + 134)
DECLARE_PMID(kInterfaceIDSpace, IID_IJPEGENCODINGEXPORTOPTION, kGenericIDPrefix + 135)
DECLARE_PMID(kInterfaceIDSpace, IID_IJPEGQUALITYEXPORTOPTION, kGenericIDPrefix + 136)
DECLARE_PMID(kInterfaceIDSpace, IID_IGIFPALETTETYPEEXPORTOPTION, kGenericIDPrefix + 137)
DECLARE_PMID(kInterfaceIDSpace, IID_IGIFINTERLACEDEXPORTOPTION, kGenericIDPrefix + 138)
DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMLAYOUTEXPORTOPTION, kGenericIDPrefix + 139)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGEALIGNMENTEXPORTOPTION, kGenericIDPrefix + 140)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGESPACEBEFOREEXPORTOPTION, kGenericIDPrefix + 141)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGESPACEAFTEREXPORTOPTION, kGenericIDPrefix + 142)
DECLARE_PMID(kInterfaceIDSpace, IID_IRASTEREXPORTOPTION, kGenericIDPrefix + 143)
DECLARE_PMID(kInterfaceIDSpace, IID_IUSEIMAGEPAGEBREAKEXPORTOPTION, kGenericIDPrefix + 144)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGEPAGEBREAKEXPORTOPTION, kGenericIDPrefix + 145)

// end of Object export options command notifications

// Effective ZOrder of the Hierarchy changing. Not forwarded.
DECLARE_PMID(kInterfaceIDSpace, IID_IHIERARCHY_CHILD_ZORDER, kGenericIDPrefix + 146)

// Synthetic message - the content dropper is about to resize a PageItem during
// the drop action. This message is sent against the PageItem being resized.
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTENTDROPPERRESIZE, kGenericIDPrefix + 147)

// The above message forwarded to descendents of the initial target of the drop
DECLARE_PMID(kInterfaceIDSpace, IID_IHIERARCHY_CONTENTDROPPERRESIZE, kGenericIDPrefix + 148)

DECLARE_PMID(kInterfaceIDSpace, IID_IOBJECTEXPORTOPTIONS_2, kGenericIDPrefix + 149)
DECLARE_PMID(kInterfaceIDSpace, IID_IOBJECTEXPORTOPTIONSDATA_2, kGenericIDPrefix + 150)
DECLARE_PMID(kInterfaceIDSpace, IID_IUSEORIGINALIMAGEEXPORTOPTION, kGenericIDPrefix + 151)
DECLARE_PMID(kInterfaceIDSpace, IID_IEDITBOXCUSTOMSIZEEXPORTOPTION, kGenericIDPrefix + 152)
DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMSIZETYPEEXPORTOPTION, kGenericIDPrefix + 153)
DECLARE_PMID(kInterfaceIDSpace, IID_IEPUBTYPEEXPORTOPTION, kGenericIDPrefix + 154)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTSELECTIONADORNMENT, kGenericIDPrefix + 155)
DECLARE_PMID(kInterfaceIDSpace, IID_IGLOBALPAGEITEMADORNMENTLIST, kGenericIDPrefix + 156)
DECLARE_PMID(kInterfaceIDSpace, IID_IGFXLAYOUTATTRIBUTEOPTIONS, kGenericIDPrefix + 157)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRANSFORMATTRSOPTIONSDATA, kGenericIDPrefix + 158)
DECLARE_PMID(kInterfaceIDSpace, IID_IINM2MPAGERESIZEBOOLDATA, kGenericIDPrefix + 159)
DECLARE_PMID(kInterfaceIDSpace, IID_IOBJSTYLEOVERRIDEACTIONDATA, kGenericIDPrefix + 160)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRIVATECONTENTAWAREFITMANAGER, kGenericIDPrefix + 161)
DECLARE_PMID(kInterfaceIDSpace, IID_ICAF_CAPTURING_ITEM_TRANSFORM, kGenericIDPrefix + 162)
DECLARE_PMID(kInterfaceIDSpace, IID_ICAF_RESTORING_ITEM_TRANSFORM, kGenericIDPrefix + 163)
DECLARE_PMID(kInterfaceIDSpace, IID_ITRANSFORMPIINOBJECTSTYLES, kGenericIDPrefix + 164)
DECLARE_PMID(kInterfaceIDSpace, IID_ISVGEXPORTTYPEEXPORTOPTION, kGenericIDPrefix + 165)
DECLARE_PMID(kInterfaceIDSpace, IID_ISVGEXPORTOPTIONSDATA, kGenericIDPrefix + 166)
DECLARE_PMID(kInterfaceIDSpace, IID_IAPPLYONALLSVGSOPTION, kGenericIDPrefix + 167)
DECLARE_PMID(kInterfaceIDSpace, IID_IHIERARCHY_INLINEREBUILTCONTENTDAMAGE, kGenericIDPrefix + 168)
DECLARE_PMID(kInterfaceIDSpace, IID_IPROCESSPAGEITEMUTILS, kGenericIDPrefix + 169)

// -- GAP ---

// gap

//DECLARE_PMID(kInterfaceIDSpace, IID_IMYFANCYNEWINTERFACE, kGenericIDPrefix + 255 )

// <Implementation ID>
// ImplementationIIDs
// gap
DECLARE_PMID(kImplementationIDSpace, kSetFittingOptionsCmdDataImpl, kGenericIDPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kSetFittingOptionsCmdImpl, kGenericIDPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kPageItemScriptM2MListenerImpl, kGenericIDPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kHiddenItemsImpl, kGenericIDPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kRectPolygonDataImpl, kGenericIDPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kPageItemDefaultScriptProviderImpl, kGenericIDPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kNewPageItemCmdImpl, kGenericIDPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kNewPageItemCmdDataImpl, kGenericIDPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kPageItemPropsScriptProviderImpl, kGenericIDPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kPageItemScriptProviderImpl, kGenericIDPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kPageItemScriptImpl, kGenericIDPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kPageItemINXPropsScriptProviderImpl, kGenericIDPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kMoveRelativeCmdImpl, kGenericIDPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kHiddenItemsM2MListenerImpl, kGenericIDPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kMovePointCmdDataImpl, kGenericIDPrefix + 15	)
DECLARE_PMID(kImplementationIDSpace, kGenericPageItemNameImpl, kGenericIDPrefix + 16	)
DECLARE_PMID(kImplementationIDSpace, kSetPageItemNameCmdImpl, kGenericIDPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kConvertItemToTextCmdImpl, kGenericIDPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kMoveRelativeCmdDataImpl, kGenericIDPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kMoveAbsoluteCmdImpl, kGenericIDPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kPointListDataImpl, kGenericIDPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kFrameFittingScriptProviderImpl, kGenericIDPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kPlacePIDataImpl, kGenericIDPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kPlacePICmdImpl, kGenericIDPrefix + 24		)
DECLARE_PMID(kImplementationIDSpace, kClip_ConversionProviderImpl, kGenericIDPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kClipSettingsImpl, kGenericIDPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kDocumentClipSettingsImpl, kGenericIDPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kSessionClipSettingsImpl, kGenericIDPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kSetClipValuesCmdImpl, kGenericIDPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kSetClipValuesCmdDataImpl, kGenericIDPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kOEOptionsEpubUtilsImpl, kGenericIDPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kPrivateContentAwareFitManagerImpl, kGenericIDPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kAddToHierarchyCmdImpl, kGenericIDPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kRemoveFromHierarchyCmdImpl, kGenericIDPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kHierarchyCmdDataImpl, kGenericIDPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kLockedItemsImpl, kGenericIDPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kPlaceGraphicFrameTrackerImpl, kGenericIDPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kPlaceGraphicFrameCmdImpl, kGenericIDPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kConvertItemToFrameCmdImpl, kGenericIDPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kConvertFrameToItemCmdImpl, kGenericIDPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kPlaceItemInGraphicFrameCmdImpl, kGenericIDPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kGraphicFramePreferencesImpl, kGenericIDPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kSessionGraphicFramePrefsImpl, kGenericIDPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kDocGraphicFramePrefsImpl, kGenericIDPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kLockPositionImpl, kGenericIDPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kSetLockPositionCmdImpl, kGenericIDPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kItemLockDataImpl, kGenericIDPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kSetItemLockDataCmdImpl, kGenericIDPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kSetVisibleDataCmdImpl, kGenericIDPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kPageItemVisibleImpl, kGenericIDPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kPageItemVisibilityFacadeImpl, kGenericIDPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kDownloadCmdImpl, kGenericIDPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kRectListDataImpl, kGenericIDPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kSetBoundingBoxCmdImpl, kGenericIDPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kPMMatrixListDataImpl, kGenericIDPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kSetPMMatrixCmdImpl, kGenericIDPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kPageItemSubjectImpl, kGenericIDPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kResizeItemsCmdImpl, kGenericIDPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kResizeItemsCmdDataImpl, kGenericIDPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kPageItemNameFacadeImpl, kGenericIDPrefix + 60)		
DECLARE_PMID(kImplementationIDSpace, kFitContentToFrameCmdImpl, kGenericIDPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kFitContentPropCmdImpl, kGenericIDPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kCenterContentInFrameCmdImpl, kGenericIDPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kAlignContentInFrameCmdImpl, kGenericIDPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kAlignContentInFrameCmdDataImpl, kGenericIDPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kAlignCmdImpl, kGenericIDPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kDistributeCmdImpl, kGenericIDPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kAllPageItemsScriptProviderImpl, kGenericIDPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kPageItemCacheImpl, kGenericIDPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kSetBoundingBoxCheckerImpl, kGenericIDPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kGenericErrorStringServiceImpl, kGenericIDPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kVisibilityDrawEventServiceImpl, kGenericIDPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kVisibilityDrawEventHandlerImpl, kGenericIDPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kPageItemScrapFacadeImpl, kGenericIDPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kLockedItemsM2MListenerImpl, kGenericIDPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kGenericDataPhase2ConversionImpl, kGenericIDPrefix + 76)
//gap
DECLARE_PMID(kImplementationIDSpace, kMoveBoundsCheckerImpl, kGenericIDPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kResizeBoundsCheckerImpl, kGenericIDPrefix + 79)
//DECLARE_PMID(kImplementationIDSpace, kSetDimensionsBoundsCheckerImpl, kGenericIDPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kSetBoundingBoxCmdDataImpl, kGenericIDPrefix + 81)
//DECLARE_PMID(kImplementationIDSpace, kPageItemGeometrySuiteImpl, kGenericIDPrefix + 82)
//DECLARE_PMID(kImplementationIDSpace, kPageItemTransformSuiteImpl, kGenericIDPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kCGraphicPlaceBehaviorUIImpl, kGenericIDPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kBoundsConstraintSuiteImpl, kGenericIDPrefix + 85)
DECLARE_PMID(kImplementationIDSpace, kRectToPolygonImpl, kGenericIDPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kCGraphicPlaceBehaviorImpl, kGenericIDPrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kGenericSwatchReferenceDataImpl, kGenericIDPrefix + 88)
//DECLARE_PMID(kImplementationIDSpace, kGenericRenderingObjSuiteImpl, kGenericIDPrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kNewPISignalRespServiceImpl, kGenericIDPrefix + 91)
DECLARE_PMID(kImplementationIDSpace, kNewPISignalDataImpl, kGenericIDPrefix + 92)
DECLARE_PMID(kImplementationIDSpace, kPageItemAdornmentListImpl, kGenericIDPrefix + 93)
DECLARE_PMID(kImplementationIDSpace, kAddPageItemAdornmentCmdImpl, kGenericIDPrefix + 94)
DECLARE_PMID(kImplementationIDSpace, kRemovePageItemAdornmentCmdImpl, kGenericIDPrefix + 95)
DECLARE_PMID(kImplementationIDSpace, kAddPageItemHandleAdornmentCmdImpl, kGenericIDPrefix + 96)
DECLARE_PMID(kImplementationIDSpace, kRemovePageItemHandleAdornmentCmdImpl, kGenericIDPrefix + 97)
DECLARE_PMID(kImplementationIDSpace, kGraphicFrameEdgeAdornmentImpl, kGenericIDPrefix + 98)
DECLARE_PMID(kImplementationIDSpace, kSetGraphicFrameDataCmdImpl, kGenericIDPrefix + 99)
DECLARE_PMID(kImplementationIDSpace, kRegisterScrapItemCmdImpl, kGenericIDPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kUnregisterScrapItemCmdImpl, kGenericIDPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kPasteGraphicItemCmdImpl, kGenericIDPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kRedefineScalingCmdImpl, kGenericIDPrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kTransformCmdDataImpl, kGenericIDPrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kTransformPageItemsCmdImpl, kGenericIDPrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kTransformCmdBoundsCheckerImpl, kGenericIDPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kPageItemBoundsListImpl, kGenericIDPrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kPageItemBoundsCacheImpl, kGenericIDPrefix + 108)
DECLARE_PMID(kImplementationIDSpace, kTranslatePageItemsCmdImpl, kGenericIDPrefix + 109)
DECLARE_PMID(kImplementationIDSpace, kBaseVisitorImpl, kGenericIDPrefix + 110)
DECLARE_PMID(kImplementationIDSpace, kPageItemCreateMetaDataCmdImpl, kGenericIDPrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kDeferredAnchoredObjectAdornmentImpl, kGenericIDPrefix + 112)
DECLARE_PMID(kImplementationIDSpace, kTranslateCmdDataImpl, kGenericIDPrefix + 113)
DECLARE_PMID(kImplementationIDSpace, kHierarchyVisitorHelperImpl, kGenericIDPrefix + 114)
DECLARE_PMID(kImplementationIDSpace, kCGraphicFrameVisitorHelperImpl, kGenericIDPrefix + 115)
DECLARE_PMID(kImplementationIDSpace, kCPathShapeVisitorHelperImpl, kGenericIDPrefix + 116)
DECLARE_PMID(kImplementationIDSpace, kCShapeVisitorHelperImpl, kGenericIDPrefix + 117)
DECLARE_PMID(kImplementationIDSpace, kBringToFrontCmdImpl, kGenericIDPrefix + 118 )
DECLARE_PMID(kImplementationIDSpace, kBringForwardCmdImpl, kGenericIDPrefix + 119 )
DECLARE_PMID(kImplementationIDSpace, kSendBackwardCmdImpl, kGenericIDPrefix + 120 )
DECLARE_PMID(kImplementationIDSpace, kSendToBackCmdImpl, kGenericIDPrefix + 121 )
DECLARE_PMID(kImplementationIDSpace, kSetGraphicBoundsCmdImpl, kGenericIDPrefix + 122 )
DECLARE_PMID(kImplementationIDSpace, kPageItemConversionProviderImpl, kGenericIDPrefix + 123 )
// gap
DECLARE_PMID(kImplementationIDSpace, kGenericIteratorRegImpl, kGenericIDPrefix + 139)
DECLARE_PMID(kImplementationIDSpace, kSetDrawOptionOverrideCmdImpl, kGenericIDPrefix + 140)
DECLARE_PMID(kImplementationIDSpace, kSetDrawOptionOverrideCmdDataImpl, kGenericIDPrefix + 141)
DECLARE_PMID(kImplementationIDSpace, kDrawOptionOverridesImpl, kGenericIDPrefix + 142)
// gap
DECLARE_PMID(kImplementationIDSpace, kGeometrySuiteLayoutCSBImpl, kGenericIDPrefix + 145)
DECLARE_PMID(kImplementationIDSpace, kTransformSuiteLayoutCSBImpl, kGenericIDPrefix + 146)
DECLARE_PMID(kImplementationIDSpace, kLayoutTargetImpl, kGenericIDPrefix + 147)
// gap
DECLARE_PMID(kImplementationIDSpace, kReferencePointDataImpl, kGenericIDPrefix + 152)
DECLARE_PMID(kImplementationIDSpace, kPathSelectionImpl, kGenericIDPrefix + 153)
//DECLARE_PMID(kImplementationIDSpace, kPathSelectionTargetImpl, kGenericIDPrefix + 154)
// gap
DECLARE_PMID(kImplementationIDSpace, kPlaceHolderItemShapeImpl, kGenericIDPrefix + 156)
// gap
DECLARE_PMID(kImplementationIDSpace, kStoryPropertiesSuiteLayoutCSBImpl, kGenericIDPrefix + 160)
DECLARE_PMID(kImplementationIDSpace, kTextRangesLayoutCSBImpl, kGenericIDPrefix + 161 )
// gap
DECLARE_PMID(kImplementationIDSpace, kScaleObjectCmdImpl, kGenericIDPrefix + 165 )
DECLARE_PMID(kImplementationIDSpace, kScaleObjectCmdDataImpl, kGenericIDPrefix + 166 )
//DECLARE_PMID(kImplementationIDSpace, kScaleHierarchyImpl, kGenericIDPrefix + 167 )
DECLARE_PMID(kImplementationIDSpace, kPageItemUtilsImpl, kGenericIDPrefix + 168 )
DECLARE_PMID(kImplementationIDSpace, kPathInfoUtilsImpl, kGenericIDPrefix + 169 )
DECLARE_PMID(kImplementationIDSpace, kGuideSelectionUtilsImpl, kGenericIDPrefix + 170 )
//DECLARE_PMID(kImplementationIDSpace, kTransformCmdUtilsImpl, kGenericIDPrefix + 171 )
DECLARE_PMID(kImplementationIDSpace, kItemContextUtilsImpl, kGenericIDPrefix + 172 )
DECLARE_PMID(kImplementationIDSpace, kTransformUpdateUtilsImpl, kGenericIDPrefix + 173 )
DECLARE_PMID(kImplementationIDSpace, kPageItemScriptUtilsImpl, kGenericIDPrefix + 174 )
DECLARE_PMID(kImplementationIDSpace, kPageItemTypeUtilsImpl, kGenericIDPrefix + 175 )
DECLARE_PMID(kImplementationIDSpace, kPathUtilsImpl, kGenericIDPrefix + 176 )
DECLARE_PMID(kImplementationIDSpace, kFrameContentUtilsImpl, kGenericIDPrefix + 177 )
DECLARE_PMID(kImplementationIDSpace, kGroupItemUtilsImpl, kGenericIDPrefix + 178 )
DECLARE_PMID(kImplementationIDSpace, kBoundsUtilsImpl, kGenericIDPrefix + 179 )
DECLARE_PMID(kImplementationIDSpace, kPasteboardUtilsImpl, kGenericIDPrefix + 180 )
DECLARE_PMID(kImplementationIDSpace, kStandOffUtilsImpl, kGenericIDPrefix + 181 )
DECLARE_PMID(kImplementationIDSpace, kValidateGeometryUtilsImpl, kGenericIDPrefix + 182 )
DECLARE_PMID(kImplementationIDSpace, kPathPointUtilsImpl, kGenericIDPrefix + 183 )
DECLARE_PMID(kImplementationIDSpace, kPageItemScrapUtilsImpl, kGenericIDPrefix + 184 )
//gap
//DECLARE_PMID(kImplementationIDSpace, kObsoleteSurrogateShapeImpl, kGenericIDPrefix + 186 )
//DECLARE_PMID(kImplementationIDSpace, kObsoleteSurrogatePageItemImpl, kGenericIDPrefix + 187 )
//DECLARE_PMID(kImplementationIDSpace, kObsoleteGeometrySurrogateImpl, kGenericIDPrefix + 188 )
DECLARE_PMID(kImplementationIDSpace, kGuideDataSuiteLayoutCSBImpl, kGenericIDPrefix + 189 )
DECLARE_PMID(kImplementationIDSpace, kGroupItemSuiteLayoutCSBImpl, kGenericIDPrefix + 191 )
//gap
DECLARE_PMID(kImplementationIDSpace, kPageItemLockSuiteLayoutCSBImpl, kGenericIDPrefix + 193 )
DECLARE_PMID(kImplementationIDSpace, kGeometrySuiteTextCSBImpl, kGenericIDPrefix + 194)
DECLARE_PMID(kImplementationIDSpace, kTransformSuiteTextCSBImpl, kGenericIDPrefix + 195)
DECLARE_PMID(kImplementationIDSpace, kPageItemEventActionDefaultImpl, kGenericIDPrefix + 196 )
DECLARE_PMID(kImplementationIDSpace, kGeneralTransformCmdSuiteLayoutCSBImpl, kGenericIDPrefix + 198 )
DECLARE_PMID(kImplementationIDSpace, kFrameContentSuiteLayoutCSBImpl, kGenericIDPrefix + 199 )
DECLARE_PMID(kImplementationIDSpace, kFrameContentSuiteTextCSBImpl, kGenericIDPrefix + 200 )
DECLARE_PMID(kImplementationIDSpace, kPathOperationSuiteLayoutCSBImpl, kGenericIDPrefix + 201 )
DECLARE_PMID(kImplementationIDSpace, kAlignAndDistributeSuiteLayoutCSBImpl, kGenericIDPrefix + 202)
DECLARE_PMID(kImplementationIDSpace, kFrameContentSuiteSpreadCSBImpl, kGenericIDPrefix + 203 )
//DECLARE_PMID(kImplementationIDSpace, kObsoleteSurrogateHierarchyImpl, kGenericIDPrefix + 204 )
DECLARE_PMID(kImplementationIDSpace, kFootnoteOptionsLayoutCSBSelectionExtImpl, kGenericIDPrefix + 205)
//DECLARE_PMID(kImplementationIDSpace, kObsoleteSurrogateScrapImpl, kGenericIDPrefix + 206 )
//DECLARE_PMID(kImplementationIDSpace, kObsoleteDeleteSurrogatePageItemCmdImpl, kGenericIDPrefix + 207 )
DECLARE_PMID(kImplementationIDSpace, kLayoutCSB_TextAttributeSuiteImpl, kGenericIDPrefix + 208 )
DECLARE_PMID(kImplementationIDSpace, kLayoutCSB_TextAttributeSuiteSelExtImpl, kGenericIDPrefix + 209 )
DECLARE_PMID(kImplementationIDSpace, kControlStripGenericPIRegisterImpl, kGenericIDPrefix + 210 )
DECLARE_PMID(kImplementationIDSpace, kTextFrameOptionsLayoutCSBSelectionExtImpl, kGenericIDPrefix + 211)
//DECLARE_PMID(kImplementationIDSpace, kObsoleteDeleteMainPageItemCmdImpl, kGenericIDPrefix + 212 )
DECLARE_PMID(kImplementationIDSpace, kHierarchyUtilsImpl, kGenericIDPrefix + 213 )
// gap
DECLARE_PMID(kImplementationIDSpace, kAdornmentIteratorImpl, kGenericIDPrefix + 216 )
//DECLARE_PMID(kImplementationIDSpace, kObsoleteCopySurrogatePageItemCmdImpl, kGenericIDPrefix + 217 )
DECLARE_PMID(kImplementationIDSpace, kStoryPropertiesSuiteLayoutCSBSelectionExtImpl, kGenericIDPrefix + 218)
// gap
DECLARE_PMID(kImplementationIDSpace, kPageItemScript70ProviderImpl, kGenericIDPrefix + 220 )
DECLARE_PMID(kImplementationIDSpace, kAlignDistributeScriptProviderImpl, kGenericIDPrefix + 221 )
DECLARE_PMID(kImplementationIDSpace, kTransformFacadeImpl, kGenericIDPrefix + 222 )
DECLARE_PMID(kImplementationIDSpace, kGenericSwatchesRIDXNotifierHandlerImpl, kGenericIDPrefix + 223 )
DECLARE_PMID(kImplementationIDSpace, kGenericSwatcheReferenceDataImpl, kGenericIDPrefix + 224 )
DECLARE_PMID(kImplementationIDSpace, kPageItemScript50ProviderImpl, kGenericIDPrefix + 225 )
DECLARE_PMID(kImplementationIDSpace, kPageItemScript40ProviderImpl, kGenericIDPrefix + 226 )
DECLARE_PMID(kImplementationIDSpace, kPolygonPrefsScriptProviderImpl, kGenericIDPrefix + 227)	//jwb 4/30/02 Moved from ScriptingID.h
DECLARE_PMID(kImplementationIDSpace, kTransformAgainDocResponderImpl, kGenericIDPrefix + 228)
DECLARE_PMID(kImplementationIDSpace, kSessionRegPolyPrefsImpl, kGenericIDPrefix + 229)
DECLARE_PMID(kImplementationIDSpace, kDocRegPolyPrefsImpl, kGenericIDPrefix + 230)
DECLARE_PMID(kImplementationIDSpace, kSetRegPolyPrefsCmdImpl, kGenericIDPrefix + 231)
DECLARE_PMID(kImplementationIDSpace, kRegPolyPrefsCmdDataImpl, kGenericIDPrefix + 232)
DECLARE_PMID(kImplementationIDSpace, kLoupeToolPrefsImpl2_Obsolete, kGenericIDPrefix + 233)
//DECLARE_PMID(kImplementationIDSpace, kSetLoupeToolPrefsCmdImpl, kGenericIDPrefix + 234)
//DECLARE_PMID(kImplementationIDSpace, kLoupeToolPrefsCmdDataImpl, kGenericIDPrefix + 235)
DECLARE_PMID(kImplementationIDSpace, kDistributeOffsetDataImpl, kGenericIDPrefix + 236 )
DECLARE_PMID(kImplementationIDSpace, kSetDistributeOffsetCmdImpl, kGenericIDPrefix + 237 )
DECLARE_PMID(kImplementationIDSpace, kGeometryFacadeImpl, kGenericIDPrefix + 238 )
DECLARE_PMID(kImplementationIDSpace, kSetDistributeOffsetStateCmdImpl, kGenericIDPrefix + 239 )
DECLARE_PMID(kImplementationIDSpace, kFrameContentFacadeImpl, kGenericIDPrefix + 240 )
DECLARE_PMID(kImplementationIDSpace, kDistributeSpaceOffsetDataImpl, kGenericIDPrefix + 241 )
DECLARE_PMID(kImplementationIDSpace, kAlignDistributePropertiesScriptProviderImpl, kGenericIDPrefix + 242 )
DECLARE_PMID(kImplementationIDSpace, kTransformAgainSentinelCmdImpl, kGenericIDPrefix + 243 )
DECLARE_PMID(kImplementationIDSpace, kTransformMatrixImpl, kGenericIDPrefix + 244 )
DECLARE_PMID(kImplementationIDSpace, kTransformMatrixScriptImpl, kGenericIDPrefix + 245 )
DECLARE_PMID(kImplementationIDSpace, kTransformMatrixScriptProviderImpl, kGenericIDPrefix + 246 )
DECLARE_PMID(kImplementationIDSpace, kPageItemLockFacadeImpl, kGenericIDPrefix + 247 )
DECLARE_PMID(kImplementationIDSpace, kPageItemVisibilitySuiteASBImpl, kGenericIDPrefix + 248 )
DECLARE_PMID(kImplementationIDSpace, kPageItemVisibilitySuiteLayoutCSBImpl, kGenericIDPrefix + 249 )
//gap
DECLARE_PMID(kImplementationIDSpace, kScaleTransformImpl, kGenericIDPrefix + 251 )
DECLARE_PMID(kImplementationIDSpace, kScaleSplineImpl, kGenericIDPrefix + 252 )
DECLARE_PMID(kImplementationIDSpace, kOldOffsetPathCodePhase2ConversionImpl, kGenericIDPrefix + 253 )
DECLARE_PMID(kImplementationIDSpace, kAlignSettingsImpl, kGenericIDPrefix + 254 )
DECLARE_PMID(kImplementationIDSpace, kAlignTypeCmdImpl, kGenericIDPrefix + 255)

DECLARE_PMID(kImplementationIDSpace, kItemThumbnailFacadeImpl, kGenericIDPrefix2 + 1)
DECLARE_PMID(kImplementationIDSpace, kLiveShapeModeHandleAdornmentImpl, kGenericIDPrefix2 + 2)
//gap
DECLARE_PMID(kImplementationIDSpace, kFrameContentSuiteLayoutCSBExtImpl, kGenericIDPrefix2 + 4)
DECLARE_PMID(kImplementationIDSpace, kFrameContentSuiteDefaultCSBExtImpl, kGenericIDPrefix2 + 5)

DECLARE_PMID(kImplementationIDSpace, kObjectExportOptionsImpl, kGenericIDPrefix2 + 6)
DECLARE_PMID(kImplementationIDSpace, kObjectExportOptionsDataImpl, kGenericIDPrefix2 + 7)
DECLARE_PMID(kImplementationIDSpace, kSetAltTextSourceExportOptionCmdImpl, kGenericIDPrefix2 + 8)
DECLARE_PMID(kImplementationIDSpace, kSetCustomAltTextExportOptionCmdImpl, kGenericIDPrefix2 + 9)
DECLARE_PMID(kImplementationIDSpace, kSetAltTextMetadataExportOptionCmdImpl, kGenericIDPrefix2 + 10)
DECLARE_PMID(kImplementationIDSpace, kSetActualTextSourceExportOptionCmdImpl, kGenericIDPrefix2 + 11)
DECLARE_PMID(kImplementationIDSpace, kSetCustomActualTextExportOptionCmdImpl, kGenericIDPrefix2 + 12)
DECLARE_PMID(kImplementationIDSpace, kSetActualTextMetadataExportOptionCmdImpl, kGenericIDPrefix2 + 13)
DECLARE_PMID(kImplementationIDSpace, kSetTagTypeExportOptionCmdImpl, kGenericIDPrefix2 + 14)
DECLARE_PMID(kImplementationIDSpace, kSetCustomConvExportOptionCmdImpl, kGenericIDPrefix2 + 15)
DECLARE_PMID(kImplementationIDSpace, kSetImageTypeExportOptionCmdImpl, kGenericIDPrefix2 + 16)
//DECLARE_PMID(kImplementationIDSpace, /*kSetObjectSizeExportOptionCmdImpl*/, kGenericIDPrefix2 + 17)
DECLARE_PMID(kImplementationIDSpace, kSetImageResolutionExportOptionCmdImpl, kGenericIDPrefix2 + 18)
DECLARE_PMID(kImplementationIDSpace, kSetJPEGEncodingExportOptionCmdImpl, kGenericIDPrefix2 + 19)
DECLARE_PMID(kImplementationIDSpace, kSetJPEGQualityExportOptionCmdImpl, kGenericIDPrefix2 + 20)
DECLARE_PMID(kImplementationIDSpace, kSetGIFPaletteTypeExportOptionCmdImpl, kGenericIDPrefix2 + 21)
DECLARE_PMID(kImplementationIDSpace, kSetGIFInterlacedExportOptionCmdImpl, kGenericIDPrefix2 + 22)
DECLARE_PMID(kImplementationIDSpace, kSetCustomLayoutExportOptionCmdImpl, kGenericIDPrefix2 + 23)
DECLARE_PMID(kImplementationIDSpace, kSetImageAlignmentExportOptionCmdImpl, kGenericIDPrefix2 + 24)
DECLARE_PMID(kImplementationIDSpace, kSetImageSpaceBeforeExportOptionCmdImpl, kGenericIDPrefix2 + 25)
DECLARE_PMID(kImplementationIDSpace, kSetImageSpaceAfterExportOptionCmdImpl, kGenericIDPrefix2 + 26)
//gap
DECLARE_PMID(kImplementationIDSpace, kSetUseImagePageBreakExportOptionCmdImpl, kGenericIDPrefix2 + 28)
DECLARE_PMID(kImplementationIDSpace, kSetImagePageBreakExportOptionCmdImpl, kGenericIDPrefix2 + 29)
// kStringDataImpl aliases
DECLARE_PMID(kImplementationIDSpace, kNamespacePrefixDataImpl, kGenericIDPrefix2 + 30)
DECLARE_PMID(kImplementationIDSpace, kPropertyPathDataImpl, kGenericIDPrefix2 + 31)
DECLARE_PMID(kImplementationIDSpace, kObjectExportOptionsSuiteLayoutCSBImpl, kGenericIDPrefix2 + 32)
DECLARE_PMID(kImplementationIDSpace, kExportOptionsUtilsImpl, kGenericIDPrefix2 + 33)
DECLARE_PMID(kImplementationIDSpace, kObjectExportOptionsScriptProviderImpl, kGenericIDPrefix2 + 34)
DECLARE_PMID(kImplementationIDSpace, kOEOptionsSuiteLayoutCSBSelExtImpl, kGenericIDPrefix2 + 35)
DECLARE_PMID(kImplementationIDSpace, kSetCustomLayoutTypeExportOptiomCmdImpl, kGenericIDPrefix2 + 37)

DECLARE_PMID(kImplementationIDSpace, kObjectFCOEAltTextOptionsAttrInfoImpl, kGenericIDPrefix2 + 38)
DECLARE_PMID(kImplementationIDSpace, kObjectFCOETaggedPDFOptionsAttrInfoImpl, kGenericIDPrefix2 + 39)
DECLARE_PMID(kImplementationIDSpace, kObjectFCOEEPUBOptionsAttrInfoImpl, kGenericIDPrefix2 + 40)

DECLARE_PMID(kImplementationIDSpace, kSetObjectExportOptionsCmdImpl, kGenericIDPrefix2 + 41)
DECLARE_PMID(kImplementationIDSpace, kObjectExportOptionsNewPIResponderImpl, kGenericIDPrefix2 + 42)
DECLARE_PMID(kImplementationIDSpace, kObjectExportOptions_2Impl, kGenericIDPrefix2 + 43)
DECLARE_PMID(kImplementationIDSpace, kSetUseOriginalImageOptionCmdImpl, kGenericIDPrefix2 + 44)
DECLARE_PMID(kImplementationIDSpace, kSetEpubTypeExportOptionCmdImpl, kGenericIDPrefix2 + 45) 

DECLARE_PMID(kImplementationIDSpace, kSetCustomSizeTypeExportOptionCmdImpl, kGenericIDPrefix2 + 46)
DECLARE_PMID(kImplementationIDSpace, kSetEditBoxCustomSizeExportOptionCmdImpl, kGenericIDPrefix2 + 48)

DECLARE_PMID(kImplementationIDSpace, kSetCustomContentConvOptionCmdImpl,	kGenericIDPrefix2 + 49)
DECLARE_PMID(kImplementationIDSpace, kGlobalPageItemAdornmentListImpl,		kGenericIDPrefix2 + 50)
DECLARE_PMID(kImplementationIDSpace, kGlobalAdornmentStartupShutdownImpl,	kGenericIDPrefix2 + 51)
DECLARE_PMID(kImplementationIDSpace, kGfxLayoutAttributeOptionsImpl, kGenericIDPrefix2 + 52)
DECLARE_PMID(kImplementationIDSpace, kLayoutAttributesScriptProviderImpl, kGenericIDPrefix2 + 53)
DECLARE_PMID(kImplementationIDSpace, kTransformAttrsOptionsDataImpl, kGenericIDPrefix2 + 54)
DECLARE_PMID(kImplementationIDSpace, kEndnoteOptionsLayoutCSBSelectionExtImpl, kGenericIDPrefix2 + 55)
DECLARE_PMID(kImplementationIDSpace, kInM2MPageResizeBoolDataImpl, kGenericIDPrefix2 + 56)
DECLARE_PMID(kImplementationIDSpace, kPageItemOverrideM2MListenerImpl, kGenericIDPrefix2 + 57)
DECLARE_PMID(kImplementationIDSpace, kObjStyleOverrideActionDataImpl, kGenericIDPrefix2 + 58)
//gap
DECLARE_PMID(kImplementationIDSpace, kContentAwareFitAsDefaultPrefCmdImpl, kGenericIDPrefix2 + 60)
DECLARE_PMID(kImplementationIDSpace, kContentAwareFitCmdImpl, kGenericIDPrefix2 + 61)
DECLARE_PMID(kImplementationIDSpace, kObjStylesTFOContentIteratorRegImpl, kGenericIDPrefix2 + 62)
DECLARE_PMID(kImplementationIDSpace, kSetSVGExportTypeExportOptionCmdImpl, kGenericIDPrefix2 + 63)
DECLARE_PMID(kImplementationIDSpace, kSVGExportOptionsDataImpl, kGenericIDPrefix2 + 65)
DECLARE_PMID(kImplementationIDSpace, kSetApplyOnAllSVGsOptionCmdImpl, kGenericIDPrefix2 + 66)
DECLARE_PMID(kImplementationIDSpace, kProcessPageItemUtilsImpl, kGenericIDPrefix2 + 67 )
// <Service ID>
// Service Providers
DECLARE_PMID(kServiceIDSpace, kNewPISignalResponderService, kGenericIDPrefix + 1)
DECLARE_PMID(kServiceIDSpace, kNewPageItemActionService, kGenericIDPrefix + 2)


// <Error ID>
// Error Codes
DECLARE_PMID(kErrorIDSpace, kItemDoesNotIntersectBoundsError, kGenericIDPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kItemTooSmallError, kGenericIDPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kItemTooLargeError, kGenericIDPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kIllegalScaleValueError, kGenericIDPrefix + 4)
DECLARE_PMID(kErrorIDSpace, kIllegalDimensionError, kGenericIDPrefix + 5)
DECLARE_PMID(kErrorIDSpace, kUnableToSetBoundingBoxError, kGenericIDPrefix + 6)
DECLARE_PMID(kErrorIDSpace, kPathIndexOutOfBounds, kGenericIDPrefix + 7)
DECLARE_PMID(kErrorIDSpace, kPointIndexOutOfBounds, kGenericIDPrefix + 8)
DECLARE_PMID(kErrorIDSpace, kIllegalSkewValueError, kGenericIDPrefix + 9)
DECLARE_PMID(kErrorIDSpace, kObjectIsLockedError, kGenericIDPrefix + 10)
DECLARE_PMID(kErrorIDSpace, kCantSplitThisObjectError, kGenericIDPrefix + 11)
DECLARE_PMID(kErrorIDSpace, kPathOPResultEmptyError, kGenericIDPrefix + 12)
DECLARE_PMID(kErrorIDSpace, kCantMoveInFrontBehindError, kGenericIDPrefix + 13)
DECLARE_PMID(kErrorIDSpace, kBadInLineMoveError, kGenericIDPrefix + 14)
DECLARE_PMID(kErrorIDSpace, kCannotConvertShapeError, kGenericIDPrefix + 15)
DECLARE_PMID(kErrorIDSpace, kCannotJoinPathPointsError, kGenericIDPrefix + 16)
DECLARE_PMID(kErrorIDSpace, kGraphicAttrNotSupportedError, kGenericIDPrefix + 17)
DECLARE_PMID(kErrorIDSpace, kGraphicAttrMixedSelectionError, kGenericIDPrefix + 18)
DECLARE_PMID(kErrorIDSpace, kNoValidPIParentFoundError, kGenericIDPrefix + 19)
DECLARE_PMID(kErrorIDSpace, kImageInfoNotAvailableError, kGenericIDPrefix + 20)
DECLARE_PMID(kErrorIDSpace, kUnsupportedRotateParametersError, kGenericIDPrefix + 21)
DECLARE_PMID(kErrorIDSpace, kUnsupportedShearParametersError, kGenericIDPrefix + 22)
DECLARE_PMID(kErrorIDSpace, kCannotUnlinkItemNotOverriddenError, kGenericIDPrefix + 23)
DECLARE_PMID(kErrorIDSpace, kCannotTransformAgainError, kGenericIDPrefix + 24)
DECLARE_PMID(kErrorIDSpace, kCannotConvertToLineError, kGenericIDPrefix + 25)
DECLARE_PMID(kErrorIDSpace, kCannotConvertPointToShapeError, kGenericIDPrefix + 26)
DECLARE_PMID(kErrorIDSpace, kCannotConvertOrthogonalLineToShapeError, kGenericIDPrefix + 27)
DECLARE_PMID(kErrorIDSpace, kCannotConvertLineToClosedPath, kGenericIDPrefix + 28)
DECLARE_PMID(kErrorIDSpace, kCannotMoveBetweenDocsError, kGenericIDPrefix + 29)
DECLARE_PMID(kErrorIDSpace, kNoTransformMatrixError, kGenericIDPrefix + 30)
DECLARE_PMID(kErrorIDSpace, kAlternativeTransformMatrixError, kGenericIDPrefix + 31)
DECLARE_PMID(kErrorIDSpace, kInvalidOperationOnUnplacedContentError, kGenericIDPrefix + 32)
DECLARE_PMID(kErrorIDSpace, kEmptySplineErrorCode, kGenericIDPrefix + 33)
DECLARE_PMID(kErrorIDSpace, kXMPMetadataAbsentErrorCode, kGenericIDPrefix + 34)
DECLARE_PMID(kErrorIDSpace, kXMPPropertyAbsentErrorCode, kGenericIDPrefix + 35)
DECLARE_PMID(kErrorIDSpace, kXMPPropertyValueStructTypeErrorCode, kGenericIDPrefix + 36)
DECLARE_PMID(kErrorIDSpace, kXMPPropertyValueArrayTypeErrorCode, kGenericIDPrefix + 37)
DECLARE_PMID(kErrorIDSpace, kXMLStructureAbsentErrorCode, kGenericIDPrefix + 38)
DECLARE_PMID(kErrorIDSpace, kXMLAttributeAbsentErrorCode, kGenericIDPrefix + 39)
DECLARE_PMID(kErrorIDSpace, kMixedMetadataTextErrorCode, kGenericIDPrefix + 40)
DECLARE_PMID(kErrorIDSpace, kMixedStructureTextErrorCode, kGenericIDPrefix + 41)
DECLARE_PMID(kErrorIDSpace, kInvalidEpubTypeErrorCode, kGenericIDPrefix + 42)
DECLARE_PMID(kErrorIDSpace, kInvalidValueErrorCode, kGenericIDPrefix + 43)
DECLARE_PMID(kErrorIDSpace, kInvalidUnitErrorCode, kGenericIDPrefix + 44)
DECLARE_PMID(kErrorIDSpace, kCanNotConvertTableObjToLineError, kGenericIDPrefix + 45)
DECLARE_PMID(kErrorIDSpace, kCanNotPlaceTextFrameInTableError, kGenericIDPrefix + 46)
//gap
//gap
DECLARE_PMID(kErrorIDSpace, kFailedToGetItemProxyError, kGenericIDPrefix + 49)
DECLARE_PMID(kErrorIDSpace, kCannotApplyContentAwareFitOnWin32Error, kGenericIDPrefix + 50)

// <Message ID>
// Message IDs (start at 200)
DECLARE_PMID(kMessageIDSpace, kGenericMsgPrefix, kGenericIDPrefix + 200)
//DECLARE_PMID(kMessageIDSpace, kRotationChangedMessage, kGenericMsgPrefix + 1			)
//DECLARE_PMID(kMessageIDSpace, kScaleChangedMessage, kGenericMsgPrefix + 3			)
//DECLARE_PMID(kMessageIDSpace, kSkewChangedMessage, kGenericMsgPrefix + 5			)
DECLARE_PMID(kMessageIDSpace, kLocationChangedMessage, kGenericMsgPrefix + 7			)
DECLARE_PMID(kMessageIDSpace, kSizeChangedMessage, kGenericMsgPrefix + 9			)
DECLARE_PMID(kMessageIDSpace, kBoundsChangedMessage, kGenericMsgPrefix + 11			)
DECLARE_PMID(kMessageIDSpace, kPathPointsChangedMessage, kGenericMsgPrefix + 13			)
DECLARE_PMID(kMessageIDSpace, kTransformChangedMessage, kGenericMsgPrefix + 14)
DECLARE_PMID(kMessageIDSpace, kRedefineScalingMessage, kGenericMsgPrefix + 15)

// <Global ID>
// Global IDs
DECLARE_PMID(kActionIDSpace, kZeroStrokeActionID, kGenericIDPrefix + 1)
DECLARE_PMID(kActionIDSpace, kQuarterPointActionID, kGenericIDPrefix + 2)
DECLARE_PMID(kActionIDSpace, kHalfPointActionID, kGenericIDPrefix + 3)
DECLARE_PMID(kActionIDSpace, kThreeQuarterPointActionID, kGenericIDPrefix + 4)
DECLARE_PMID(kActionIDSpace, k1PointActionID, kGenericIDPrefix + 5)
DECLARE_PMID(kActionIDSpace, k2PointsActionID, kGenericIDPrefix + 6)
DECLARE_PMID(kActionIDSpace, k3PointsActionID, kGenericIDPrefix + 7)
DECLARE_PMID(kActionIDSpace, k4PointsActionID, kGenericIDPrefix + 8)
DECLARE_PMID(kActionIDSpace, k5PointsActionID, kGenericIDPrefix + 9)
DECLARE_PMID(kActionIDSpace, k6PointsActionID, kGenericIDPrefix + 10)
DECLARE_PMID(kActionIDSpace, k7PointsActionID, kGenericIDPrefix + 11)
DECLARE_PMID(kActionIDSpace, k8PointsActionID, kGenericIDPrefix + 12)
DECLARE_PMID(kActionIDSpace, k9PointsActionID, kGenericIDPrefix + 13)
DECLARE_PMID(kActionIDSpace, k10PointsActionID, kGenericIDPrefix + 14)

DECLARE_PMID(kActionIDSpace, kTenthMMActionID, kGenericIDPrefix + 15)
DECLARE_PMID(kActionIDSpace, kNoFillActionID, kGenericIDPrefix + 16)
DECLARE_PMID(kActionIDSpace, kSolidActionID, kGenericIDPrefix + 17)
DECLARE_PMID(kActionIDSpace, kPointThreeFiveMMActionID, kGenericIDPrefix + 18)

DECLARE_PMID(kActionIDSpace, kBringToFrontActionID, kGenericIDPrefix + 19)
DECLARE_PMID(kActionIDSpace, kBringForwardActionID, kGenericIDPrefix + 20)
DECLARE_PMID(kActionIDSpace, kSendBackwardActionID, kGenericIDPrefix + 21)
DECLARE_PMID(kActionIDSpace, kSendToBackActionID, kGenericIDPrefix + 22)

DECLARE_PMID(kActionIDSpace, kSelectForwardActionID, kGenericIDPrefix + 23)
DECLARE_PMID(kActionIDSpace, kSelectBackwardActionID, kGenericIDPrefix + 24)
DECLARE_PMID(kActionIDSpace, kSelectFrontActionID, kGenericIDPrefix + 25)
DECLARE_PMID(kActionIDSpace, kSelectBackActionID, kGenericIDPrefix + 26)

DECLARE_PMID(kActionIDSpace, kFitFrameToContentActionID, kGenericIDPrefix + 27)
DECLARE_PMID(kActionIDSpace, kFitContentToFrameActionID, kGenericIDPrefix + 28)
DECLARE_PMID(kActionIDSpace, kFitContentPropActionID, kGenericIDPrefix + 29)
DECLARE_PMID(kActionIDSpace, kCenterContentInFrameActionID, kGenericIDPrefix + 30)
DECLARE_PMID(kActionIDSpace, kConvertItemToFrameActionID, kGenericIDPrefix + 31)
DECLARE_PMID(kActionIDSpace, kConvertItemToTextActionID, kGenericIDPrefix + 32)
DECLARE_PMID(kActionIDSpace, kConvertFrameToItemActionID, kGenericIDPrefix + 33)
DECLARE_PMID(kActionIDSpace, kIncreaseObjectScaleActionID, kGenericIDPrefix + 34)
DECLARE_PMID(kActionIDSpace, kDecreaseObjectScaleActionID, kGenericIDPrefix + 35)
DECLARE_PMID(kActionIDSpace, kIncreaseObjectScaleTimes5ActionID, kGenericIDPrefix + 36)
DECLARE_PMID(kActionIDSpace, kDecreaseObjectScaleTimes5ActionID, kGenericIDPrefix + 37)
DECLARE_PMID(kActionIDSpace, kFillStrokeMenuDynamicActionID, kGenericIDPrefix + 38)
DECLARE_PMID(kActionIDSpace, kDefaultSelectSepActionID, kGenericIDPrefix + 39)
DECLARE_PMID(kActionIDSpace, kLockPositionActionID, kGenericIDPrefix + 40)
DECLARE_PMID(kActionIDSpace, kUnlockActionID, kGenericIDPrefix + 41)
DECLARE_PMID(kActionIDSpace, kSelectObjectSepActionID, kGenericIDPrefix + 42)
DECLARE_PMID(kActionIDSpace, kFittingSepActionID, kGenericIDPrefix + 43)
DECLARE_PMID(kActionIDSpace, kConvertSepActionID, kGenericIDPrefix + 44)
DECLARE_PMID(kActionIDSpace, kLockSepActionID, kGenericIDPrefix + 45)
DECLARE_PMID(kActionIDSpace, kContextSelectObjectSepActionID, kGenericIDPrefix + 46)
DECLARE_PMID(kActionIDSpace, kPathConvertSepActionID, kGenericIDPrefix + 47)
DECLARE_PMID(kActionIDSpace, kPathLockSepActionID, kGenericIDPrefix + 48)
DECLARE_PMID(kActionIDSpace, kGraphicArrangeSepActionID, kGenericIDPrefix + 49)
DECLARE_PMID(kActionIDSpace, kGraphicFittingSepActionID, kGenericIDPrefix + 50)
DECLARE_PMID(kActionIDSpace, kGraphicConvertSepActionID, kGenericIDPrefix + 51)
DECLARE_PMID(kActionIDSpace, kGraphicLockSepActionID, kGenericIDPrefix + 52)
DECLARE_PMID(kActionIDSpace, kTextArrangeSepActionID, kGenericIDPrefix + 53)
DECLARE_PMID(kActionIDSpace, kTextConvertSepActionID, kGenericIDPrefix + 54)
DECLARE_PMID(kActionIDSpace, kTextLockSepActionID, kGenericIDPrefix + 55)
DECLARE_PMID(kActionIDSpace, kImageFittingSepActionID, kGenericIDPrefix + 56)

DECLARE_PMID(kActionIDSpace, kZeroMMActionID, kGenericIDPrefix + 57)
DECLARE_PMID(kActionIDSpace, kQuarterMMActionID, kGenericIDPrefix + 58)
DECLARE_PMID(kActionIDSpace, kHalfMMActionID, kGenericIDPrefix + 59)
DECLARE_PMID(kActionIDSpace, k1MMActionID, kGenericIDPrefix + 60)
DECLARE_PMID(kActionIDSpace, k1HalfMMActionID, kGenericIDPrefix + 61)
DECLARE_PMID(kActionIDSpace, k2MMActionID, kGenericIDPrefix + 62)
DECLARE_PMID(kActionIDSpace, k3MMActionID, kGenericIDPrefix + 63)
DECLARE_PMID(kActionIDSpace, k4MMActionID, kGenericIDPrefix + 64)
DECLARE_PMID(kActionIDSpace, k5MMActionID, kGenericIDPrefix + 65)
DECLARE_PMID(kActionIDSpace, k10MMActionID, kGenericIDPrefix + 66)
DECLARE_PMID(kActionIDSpace, k15MMActionID, kGenericIDPrefix + 67)
DECLARE_PMID(kActionIDSpace, k20MMActionID, kGenericIDPrefix + 68)

DECLARE_PMID(kActionIDSpace, kHAlignLeftActionID, 		kGenericIDPrefix + 69)
DECLARE_PMID(kActionIDSpace, kHAlignCenterActionID, 		kGenericIDPrefix + 70)
DECLARE_PMID(kActionIDSpace, kHAlignRightActionID, 		kGenericIDPrefix + 71)
DECLARE_PMID(kActionIDSpace, kVAlignTopActionID, 		kGenericIDPrefix + 72)
DECLARE_PMID(kActionIDSpace, kVAlignCenterActionID, 		kGenericIDPrefix + 73)
DECLARE_PMID(kActionIDSpace, kVAlignBottomActionID, 		kGenericIDPrefix + 74)
DECLARE_PMID(kActionIDSpace, kHDistributeLeftActionID, 	kGenericIDPrefix + 75)
DECLARE_PMID(kActionIDSpace, kHDistributeCenterActionID, kGenericIDPrefix + 76)
DECLARE_PMID(kActionIDSpace, kHDistributeRightActionID, 	kGenericIDPrefix + 77)
DECLARE_PMID(kActionIDSpace, kVDistributeTopActionID, 	kGenericIDPrefix + 78)
DECLARE_PMID(kActionIDSpace, kVDistributeCenterActionID, kGenericIDPrefix + 79)
DECLARE_PMID(kActionIDSpace, kVDistributeBottomActionID, kGenericIDPrefix + 80)
DECLARE_PMID(kActionIDSpace, kVDistributeSpaceActionID, kGenericIDPrefix + 81)
DECLARE_PMID(kActionIDSpace, kHDistributeSpaceActionID, kGenericIDPrefix + 82)

DECLARE_PMID(kActionIDSpace, kFillFramePropActionID, kGenericIDPrefix + 83)

DECLARE_PMID(kActionIDSpace, kMasterOverrideableActionID, kGenericIDPrefix + 84)
DECLARE_PMID(kActionIDSpace, kMasterNotOverrideableActionID, kGenericIDPrefix + 85)
DECLARE_PMID(kActionIDSpace, kGraphicFramePropActionID, kGenericIDPrefix + 86)
DECLARE_PMID(kActionIDSpace, kSelectParentFrameActionID, kGenericIDPrefix + 87)
DECLARE_PMID(kActionIDSpace, kSelectContentItemActionID, kGenericIDPrefix + 88)
DECLARE_PMID(kActionIDSpace, kSelectSubmenuSepActionID, kGenericIDPrefix + 89)
DECLARE_PMID(kActionIDSpace, kContextSelectSubmenuSepActionID, kGenericIDPrefix + 90)
DECLARE_PMID(kActionIDSpace, kSelectPreviousItemActionID, kGenericIDPrefix + 91)
DECLARE_PMID(kActionIDSpace, kSelectNextItemActionID, kGenericIDPrefix + 92)
DECLARE_PMID(kActionIDSpace, kSelectSubmenuSep2ActionID, kGenericIDPrefix + 93)
DECLARE_PMID(kActionIDSpace, kPersistentFittingSepActionID, kGenericIDPrefix + 95)
DECLARE_PMID(kActionIDSpace, kHAlignPageLeftActionID, kGenericIDPrefix + 96)
DECLARE_PMID(kActionIDSpace, kHAlignPageCenterActionID, kGenericIDPrefix + 97)
DECLARE_PMID(kActionIDSpace, kHAlignPageRightActionID, kGenericIDPrefix + 98)
DECLARE_PMID(kActionIDSpace, kVAlignPageTopActionID, kGenericIDPrefix + 99)
DECLARE_PMID(kActionIDSpace, kVAlignPageCenterActionID, kGenericIDPrefix + 100)
DECLARE_PMID(kActionIDSpace, kVAlignPageBottomActionID, kGenericIDPrefix + 101)
DECLARE_PMID(kActionIDSpace, kHAlignSpreadLeftActionID, kGenericIDPrefix + 102)
DECLARE_PMID(kActionIDSpace, kHAlignSpreadCenterActionID, kGenericIDPrefix + 103)
DECLARE_PMID(kActionIDSpace, kHAlignSpreadRightActionID, kGenericIDPrefix + 104)
DECLARE_PMID(kActionIDSpace, kVAlignSpreadTopActionID, kGenericIDPrefix + 105)
DECLARE_PMID(kActionIDSpace, kVAlignSpreadCenterActionID, kGenericIDPrefix + 106)
DECLARE_PMID(kActionIDSpace, kVAlignSpreadBottomActionID, kGenericIDPrefix + 107)
DECLARE_PMID(kActionIDSpace, kHAlignMarginLeftActionID, kGenericIDPrefix + 108)
DECLARE_PMID(kActionIDSpace, kHAlignMarginCenterActionID, kGenericIDPrefix + 109)
DECLARE_PMID(kActionIDSpace, kHAlignMarginRightActionID, kGenericIDPrefix + 110)
DECLARE_PMID(kActionIDSpace, kVAlignMarginTopActionID, kGenericIDPrefix + 111)
DECLARE_PMID(kActionIDSpace, kVAlignMarginCenterActionID, kGenericIDPrefix + 112)
DECLARE_PMID(kActionIDSpace, kVAlignMarginBottomActionID, kGenericIDPrefix + 113)
DECLARE_PMID(kActionIDSpace, kPathLockSep2ActionID, kGenericIDPrefix + 114)
DECLARE_PMID(kActionIDSpace, kIncreaseObjectSizeActionID, kGenericIDPrefix + 115)
DECLARE_PMID(kActionIDSpace, kDecreaseObjectSizeActionID, kGenericIDPrefix + 116)
DECLARE_PMID(kActionIDSpace, kIncreaseObjectSizeTimes5ActionID, kGenericIDPrefix + 117)
DECLARE_PMID(kActionIDSpace, kDecreaseObjectSizeTimes5ActionID, kGenericIDPrefix + 118)
DECLARE_PMID(kActionIDSpace, kToggleAutoFitActionID, kGenericIDPrefix + 119)
DECLARE_PMID(kActionIDSpace, k0PixelsActionID, kGenericIDPrefix + 120)
DECLARE_PMID(kActionIDSpace, k1PixelsActionID, kGenericIDPrefix + 121)
DECLARE_PMID(kActionIDSpace, k2PixelsActionID, kGenericIDPrefix + 122)
DECLARE_PMID(kActionIDSpace, k3PixelsActionID, kGenericIDPrefix + 123)
DECLARE_PMID(kActionIDSpace, k4PixelsActionID, kGenericIDPrefix + 124)
DECLARE_PMID(kActionIDSpace, k5PixelsActionID, kGenericIDPrefix + 125)
DECLARE_PMID(kActionIDSpace, k6PixelsActionID, kGenericIDPrefix + 126)
DECLARE_PMID(kActionIDSpace, k7PixelsActionID, kGenericIDPrefix + 127)
DECLARE_PMID(kActionIDSpace, k8PixelsActionID, kGenericIDPrefix + 128)
DECLARE_PMID(kActionIDSpace, k9PixelsActionID, kGenericIDPrefix + 129)
DECLARE_PMID(kActionIDSpace, k10PixelsActionID, kGenericIDPrefix + 130)
DECLARE_PMID(kActionIDSpace, kUnlockAllOnSpreadActionID, kGenericIDPrefix + 131)
DECLARE_PMID(kActionIDSpace, kUnlockAllActionID, kGenericIDPrefix + 132)
DECLARE_PMID(kActionIDSpace, kClearFittingSepActionID, kGenericIDPrefix + 133)
DECLARE_PMID(kActionIDSpace, kClearFittingOptionsActionID, kGenericIDPrefix + 134)
DECLARE_PMID(kActionIDSpace, kAutoCropActionID, kGenericIDPrefix + 135)
DECLARE_PMID(kActionIDSpace, kSearchSimilarActionID, kGenericIDPrefix + 136)

//
//Script Element IDs
//

//Suites
DECLARE_PMID(kScriptInfoIDSpace, kLayoutSuiteScriptElement,						kGenericIDPrefix + 1)

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kPageItemObjectScriptElement,					kGenericIDPrefix + 10)
DECLARE_PMID(kScriptInfoIDSpace, kOvalObjectScriptElement,						kGenericIDPrefix + 11)
DECLARE_PMID(kScriptInfoIDSpace, kRectangleObjectScriptElement,					kGenericIDPrefix + 12)
DECLARE_PMID(kScriptInfoIDSpace, kGraphicLineObjectScriptElement,				kGenericIDPrefix + 13)
DECLARE_PMID(kScriptInfoIDSpace, kPolygonObjectScriptElement,					kGenericIDPrefix + 14)
DECLARE_PMID(kScriptInfoIDSpace, kGroupObjectScriptElement,						kGenericIDPrefix + 15)
DECLARE_PMID(kScriptInfoIDSpace, kImageObjectScriptElement,						kGenericIDPrefix + 16)
DECLARE_PMID(kScriptInfoIDSpace, kEPSObjectScriptElement,						kGenericIDPrefix + 17)
DECLARE_PMID(kScriptInfoIDSpace, kPDFObjectScriptElement,						kGenericIDPrefix + 18)
DECLARE_PMID(kScriptInfoIDSpace, kWMFObjectScriptElement,						kGenericIDPrefix + 19)
DECLARE_PMID(kScriptInfoIDSpace, kPICTObjectScriptElement,						kGenericIDPrefix + 20)
DECLARE_PMID(kScriptInfoIDSpace, kGraphicObjectScriptElement,					kGenericIDPrefix + 21)
DECLARE_PMID(kScriptInfoIDSpace, kPageItemDefaultObjectScriptElement,			kGenericIDPrefix + 22)
DECLARE_PMID(kScriptInfoIDSpace, kFlipAbsolutePropertyScriptElement,			kGenericIDPrefix + 23)
DECLARE_PMID(kScriptInfoIDSpace, kObjectExportOptionsScriptElement,				kGenericIDPrefix + 24)

//Events
DECLARE_PMID(kScriptInfoIDSpace, kBeforeNodeRemovedEventScriptElement,			kGenericIDPrefix + 40)
DECLARE_PMID(kScriptInfoIDSpace, kAfterNodeInsertedEventScriptElement,			kGenericIDPrefix + 41)
DECLARE_PMID(kScriptInfoIDSpace, kBeforeNodeRemovedFromDocumentEventScriptElement,kGenericIDPrefix + 42)
//DECLARE_PMID(kScriptInfoIDSpace, kAfterNodeInsertedIntoDocumentEventScriptElement,kGenericIDPrefix + 43)
//DECLARE_PMID(kScriptInfoIDSpace, kBeforeGeometryChangedEventScriptElement,		kGenericIDPrefix + 44)
DECLARE_PMID(kScriptInfoIDSpace, kAfterGeometryChangedEventScriptElement,		kGenericIDPrefix + 45)
//DECLARE_PMID(kScriptInfoIDSpace, kBeforeTransformChangedEventScriptElement,		kGenericIDPrefix + 46)
DECLARE_PMID(kScriptInfoIDSpace, kAfterTransformChangedEventScriptElement,		kGenericIDPrefix + 47)
//DECLARE_PMID(kScriptInfoIDSpace, kAfterLabelChangedEventScriptElement,			kGenericIDPrefix + 48)
//DECLARE_PMID(kScriptInfoIDSpace, kAfterTextWrapChangedEventScriptElement,		kGenericIDPrefix + 49)

//Methods
DECLARE_PMID(kScriptInfoIDSpace, kClearFittingOptionsMethodScriptElement,		kGenericIDPrefix + 77)
DECLARE_PMID(kScriptInfoIDSpace, kChangeBoundsMethodScriptElement,				kGenericIDPrefix + 78)
DECLARE_PMID(kScriptInfoIDSpace, kChangeSizeMethodScriptElement,					kGenericIDPrefix + 79)
DECLARE_PMID(kScriptInfoIDSpace, kBringToFrontMethodScriptElement,				kGenericIDPrefix + 80)
DECLARE_PMID(kScriptInfoIDSpace, kBringForwardMethodScriptElement,				kGenericIDPrefix + 81)
DECLARE_PMID(kScriptInfoIDSpace, kSendToBackMethodScriptElement,					kGenericIDPrefix + 82)
DECLARE_PMID(kScriptInfoIDSpace, kSendBackwardMethodScriptElement,				kGenericIDPrefix + 83)
DECLARE_PMID(kScriptInfoIDSpace, kResetScalingMethodScriptElement,				kGenericIDPrefix + 84)
DECLARE_PMID(kScriptInfoIDSpace, kFlipMethodScriptElement,						kGenericIDPrefix + 85)
DECLARE_PMID(kScriptInfoIDSpace, kCreatePageItemMethodScriptElement,				kGenericIDPrefix + 86)
DECLARE_PMID(kScriptInfoIDSpace, kCreatePolygonMethodScriptElement,				kGenericIDPrefix + 87)
DECLARE_PMID(kScriptInfoIDSpace, kCreateGroupMethodScriptElement,				kGenericIDPrefix + 88)
DECLARE_PMID(kScriptInfoIDSpace, kMovePageItemMethodScriptElement,				kGenericIDPrefix + 89)
DECLARE_PMID(kScriptInfoIDSpace, kRotateMethodScriptElement,						kGenericIDPrefix + 90)
DECLARE_PMID(kScriptInfoIDSpace, kResizeMethodScriptElement,						kGenericIDPrefix + 91)
DECLARE_PMID(kScriptInfoIDSpace, kShearMethodScriptElement,						kGenericIDPrefix + 92)
DECLARE_PMID(kScriptInfoIDSpace, kUngroupMethodScriptElement,					kGenericIDPrefix + 93)
DECLARE_PMID(kScriptInfoIDSpace, kTransformGroupContentsMethodScriptElement,		kGenericIDPrefix + 94)
DECLARE_PMID(kScriptInfoIDSpace, kFitMethodScriptElement,						kGenericIDPrefix + 95)
DECLARE_PMID(kScriptInfoIDSpace, kUnlinkMethodScriptElement,						kGenericIDPrefix + 96)
DECLARE_PMID(kScriptInfoIDSpace, kDuplicatePageItemMethodScriptElement,	        kGenericIDPrefix + 97)
DECLARE_PMID(kScriptInfoIDSpace, kScaleSkewMethodScriptElement,	        		kGenericIDPrefix + 98)
DECLARE_PMID(kScriptInfoIDSpace, kConvertShapeMethodScriptElement,				kGenericIDPrefix + 99)
DECLARE_PMID(kScriptInfoIDSpace, kConvertShapeOptionEnumScriptElement,			kGenericIDPrefix + 100)
DECLARE_PMID(kScriptInfoIDSpace, kClearTransformationsMethodScriptElement,		kGenericIDPrefix + 101)
DECLARE_PMID(kScriptInfoIDSpace, kTransformMethodScriptElement,					kGenericIDPrefix + 102)
DECLARE_PMID(kScriptInfoIDSpace, kCoordinateSpacesEnumScriptElement,			kGenericIDPrefix + 103)
DECLARE_PMID(kScriptInfoIDSpace, kTransformActionsEnumScriptElement,			kGenericIDPrefix + 104)
DECLARE_PMID(kScriptInfoIDSpace, kMakeCompoundPathMethodScriptElement,			kGenericIDPrefix + 105)
DECLARE_PMID(kScriptInfoIDSpace, kIntersectPathMethodScriptElement,				kGenericIDPrefix + 106)
DECLARE_PMID(kScriptInfoIDSpace, kUnionPathMethodScriptElement,					kGenericIDPrefix + 107)
DECLARE_PMID(kScriptInfoIDSpace, kDifferencePathMethodScriptElement,				kGenericIDPrefix + 108)
DECLARE_PMID(kScriptInfoIDSpace, kReverseDiffPathMethodScriptElement,			kGenericIDPrefix + 109)
DECLARE_PMID(kScriptInfoIDSpace, kXorPathMethodScriptElement,					kGenericIDPrefix + 110)
DECLARE_PMID(kScriptInfoIDSpace, kReleaseCompoundPathMethodScriptElement,		kGenericIDPrefix + 111)
DECLARE_PMID(kScriptInfoIDSpace, kTransformMatrixObjectScriptElement,			kGenericIDPrefix + 112)
DECLARE_PMID(kScriptInfoIDSpace, kCreateTransformMatrixMethodScriptElement,		kGenericIDPrefix + 113)
DECLARE_PMID(kScriptInfoIDSpace, kMatrixContentEnumScriptElement,				kGenericIDPrefix + 114)
DECLARE_PMID(kScriptInfoIDSpace, kTransformPropertyMethodScriptElement,			kGenericIDPrefix + 115)
DECLARE_PMID(kScriptInfoIDSpace, kGeometryPropertyMethodScriptElement,			kGenericIDPrefix + 116)
DECLARE_PMID(kScriptInfoIDSpace, kBoundsKindsEnumScriptElement,					kGenericIDPrefix + 117)
DECLARE_PMID(kScriptInfoIDSpace, kResolveLocationMethodScriptElement,			kGenericIDPrefix + 118)
DECLARE_PMID(kScriptInfoIDSpace, kRedefineScalingMethodScriptElement,			kGenericIDPrefix + 119)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kContentTypePropertyScriptElement,				kGenericIDPrefix + 120)
DECLARE_PMID(kScriptInfoIDSpace, kMiterLimitPropertyScriptElement,				kGenericIDPrefix + 121)
DECLARE_PMID(kScriptInfoIDSpace, kEndCapPropertyScriptElement,					kGenericIDPrefix + 122)
DECLARE_PMID(kScriptInfoIDSpace, kEndJoinPropertyScriptElement,					kGenericIDPrefix + 123)
DECLARE_PMID(kScriptInfoIDSpace, kStrokeTypePropertyScriptElement,				kGenericIDPrefix + 124)
DECLARE_PMID(kScriptInfoIDSpace, kStrokeCornerAdjustmentPropertyScriptElement,	kGenericIDPrefix + 125)
DECLARE_PMID(kScriptInfoIDSpace, kStrokeDashAndGapPropertyScriptElement,		kGenericIDPrefix + 126)
DECLARE_PMID(kScriptInfoIDSpace, kLeftLineEndPropertyScriptElement,				kGenericIDPrefix + 127)
DECLARE_PMID(kScriptInfoIDSpace, kRightLineEndPropertyScriptElement,			kGenericIDPrefix + 128)
DECLARE_PMID(kScriptInfoIDSpace, kCornerEffectPropertyScriptElement,			kGenericIDPrefix + 129)
DECLARE_PMID(kScriptInfoIDSpace, kCornerRadiusPropertyScriptElement,			kGenericIDPrefix + 130)
DECLARE_PMID(kScriptInfoIDSpace, kItemLayerPropertyScriptElement,				kGenericIDPrefix + 131)
DECLARE_PMID(kScriptInfoIDSpace, kOverriddenPropertyScriptElement,				kGenericIDPrefix + 132)
DECLARE_PMID(kScriptInfoIDSpace, kRotationAnglePropertyScriptElement,			kGenericIDPrefix + 133)
DECLARE_PMID(kScriptInfoIDSpace, kShearAnglePropertyScriptElement,				kGenericIDPrefix + 134)
DECLARE_PMID(kScriptInfoIDSpace, kAbsoluteRotationAnglePropertyScriptElement,	kGenericIDPrefix + 135)
DECLARE_PMID(kScriptInfoIDSpace, kAbsoluteShearAnglePropertyScriptElement,		kGenericIDPrefix + 136)
DECLARE_PMID(kScriptInfoIDSpace, kAbsoluteHorizontalScalePropertyScriptElement,	kGenericIDPrefix + 137)
DECLARE_PMID(kScriptInfoIDSpace, kAbsoluteVerticalScalePropertyScriptElement,	kGenericIDPrefix + 138)
DECLARE_PMID(kScriptInfoIDSpace, kGeometricBoundsPropertyScriptElement,			kGenericIDPrefix + 142)
DECLARE_PMID(kScriptInfoIDSpace, kVisibleBoundsPropertyScriptElement,			kGenericIDPrefix + 143)
DECLARE_PMID(kScriptInfoIDSpace, kLocalDisplaySettingPropertyScriptElement,		kGenericIDPrefix + 144)
DECLARE_PMID(kScriptInfoIDSpace, kAllPageItemsPropertyScriptElement,			kGenericIDPrefix + 145)
DECLARE_PMID(kScriptInfoIDSpace, kGapColorPropertyScriptElement,				kGenericIDPrefix + 146)
DECLARE_PMID(kScriptInfoIDSpace, kGapTintPropertyScriptElement,					kGenericIDPrefix + 147)
DECLARE_PMID(kScriptInfoIDSpace, kOverprintGapPropertyScriptElement,			kGenericIDPrefix + 148)
DECLARE_PMID(kScriptInfoIDSpace, kStrokeAlignmentPropertyScriptElement,			kGenericIDPrefix + 149)
DECLARE_PMID(kScriptInfoIDSpace, kImageContentsScriptElement,					kGenericIDPrefix + 150)
DECLARE_PMID(kScriptInfoIDSpace, kItemGeometryPropertyScriptElement,			kGenericIDPrefix + 151)
DECLARE_PMID(kScriptInfoIDSpace, kPIFillColorPropertyScriptElement,				kGenericIDPrefix + 152)
DECLARE_PMID(kScriptInfoIDSpace, kPIStrokeColorPropertyScriptElement,			kGenericIDPrefix + 153)
DECLARE_PMID(kScriptInfoIDSpace, kPIStrokeTintPropertyScriptElement,			kGenericIDPrefix + 154)
DECLARE_PMID(kScriptInfoIDSpace, kPIOverprintFillPropertyScriptElement,			kGenericIDPrefix + 155)
DECLARE_PMID(kScriptInfoIDSpace, kPIOverprintStrokePropertyScriptElement,		kGenericIDPrefix + 156)
DECLARE_PMID(kScriptInfoIDSpace, kPIFillTintPropertyScriptElement,				kGenericIDPrefix + 157)
DECLARE_PMID(kScriptInfoIDSpace, kPIStrokeWeightPropertyScriptElement,			kGenericIDPrefix + 158)
DECLARE_PMID(kScriptInfoIDSpace, kPIGradientFillLengthPropertyScriptElement,	kGenericIDPrefix + 159)
DECLARE_PMID(kScriptInfoIDSpace, kPIGradientFillAnglePropertyScriptElement,		kGenericIDPrefix + 160)
DECLARE_PMID(kScriptInfoIDSpace, kPIGradientFillStartPropertyScriptElement,		kGenericIDPrefix + 161)
DECLARE_PMID(kScriptInfoIDSpace, kPIGradientStrokeStartPropertyScriptElement,	kGenericIDPrefix + 162)
DECLARE_PMID(kScriptInfoIDSpace, kPIGradientStrokeLengthPropertyScriptElement,	kGenericIDPrefix + 163)
DECLARE_PMID(kScriptInfoIDSpace, kPIGradientStrokeAnglePropertyScriptElement,	kGenericIDPrefix + 164)
DECLARE_PMID(kScriptInfoIDSpace, kActualppiPropertyScriptElement,				kGenericIDPrefix + 165)
DECLARE_PMID(kScriptInfoIDSpace, kEffectiveppiPropertyScriptElement,			kGenericIDPrefix + 166)
DECLARE_PMID(kScriptInfoIDSpace, kImageColorSpacePropertyScriptElement,			kGenericIDPrefix + 167)
DECLARE_PMID(kScriptInfoIDSpace, kImageTypePropertyScriptElement,				kGenericIDPrefix + 168)
DECLARE_PMID(kScriptInfoIDSpace, kPIStoryOffsetPropertyScriptElement,			kGenericIDPrefix + 169)
DECLARE_PMID(kScriptInfoIDSpace, kAllGraphicsPropertyScriptElement,				kGenericIDPrefix + 170)
DECLARE_PMID(kScriptInfoIDSpace, kPIGradientFillHiliteLengthPropertyScriptElement,	kGenericIDPrefix + 171)
DECLARE_PMID(kScriptInfoIDSpace, kPIGradientFillHiliteAnglePropertyScriptElement,	kGenericIDPrefix + 172)
DECLARE_PMID(kScriptInfoIDSpace, kPIGradientStrokeHiliteLengthPropertyScriptElement,	kGenericIDPrefix + 173)
DECLARE_PMID(kScriptInfoIDSpace, kPIGradientStorkeHiliteAnglePropertyScriptElement,	kGenericIDPrefix + 174)
DECLARE_PMID(kScriptInfoIDSpace, kPageItemDefaultObjectPropertyScriptElement,   kGenericIDPrefix + 175)
DECLARE_PMID(kScriptInfoIDSpace, kFittingOnEmptyFrameScriptElement,				kGenericIDPrefix + 176)
DECLARE_PMID(kScriptInfoIDSpace, kFittingAlignmentScriptElement,				kGenericIDPrefix + 177)
DECLARE_PMID(kScriptInfoIDSpace, kFittingCropLeftScriptElement,					kGenericIDPrefix + 178)
DECLARE_PMID(kScriptInfoIDSpace, kFittingCropTopScriptElement,					kGenericIDPrefix + 179)
DECLARE_PMID(kScriptInfoIDSpace, kFittingCropRightScriptElement,				kGenericIDPrefix + 180)
DECLARE_PMID(kScriptInfoIDSpace, kFittingCropBottomScriptElement,				kGenericIDPrefix + 181)
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleFrameFittingCategoryPropertyScriptElement, kGenericIDPrefix + 182)
DECLARE_PMID(kScriptInfoIDSpace, kFrameFittingObjectScriptElement,				kGenericIDPrefix + 183)
DECLARE_PMID(kScriptInfoIDSpace, kFrameFittingPropertyScriptElement,			kGenericIDPrefix + 184)
DECLARE_PMID(kScriptInfoIDSpace, kGraphicProxyScriptElement,					kGenericIDPrefix + 185)
DECLARE_PMID(kScriptInfoIDSpace, kCornerOptionsPropertyScriptElement,			kGenericIDPrefix + 186)
DECLARE_PMID(kScriptInfoIDSpace, kItemTransformPropertyScriptElement,			kGenericIDPrefix + 187)
DECLARE_PMID(kScriptInfoIDSpace, kPathBoundingBoxPropertyScriptElement,			kGenericIDPrefix + 188)
DECLARE_PMID(kScriptInfoIDSpace, kClippingPathGeometryPropertyScriptElement,	kGenericIDPrefix + 189)
DECLARE_PMID(kScriptInfoIDSpace, kGraphicBoundsPropertyScriptElement,			kGenericIDPrefix + 190)
DECLARE_PMID(kScriptInfoIDSpace, kPathGeometryPropertyScriptElement,			kGenericIDPrefix + 191)
DECLARE_PMID(kScriptInfoIDSpace, kParentPagePropertyScriptElement,				kGenericIDPrefix + 192)
DECLARE_PMID(kScriptInfoIDSpace, kAutoFitPropertyScriptElement,					kGenericIDPrefix + 193)
DECLARE_PMID(kScriptInfoIDSpace, kObjectExportOptionsPropertyScriptElement,		kGenericIDPrefix + 194)
DECLARE_PMID(kScriptInfoIDSpace, kAltTextSourceTypePropertyScriptElement,		kGenericIDPrefix + 195)
DECLARE_PMID(kScriptInfoIDSpace, kActualTextSourceTypePropertyScriptElement,	kGenericIDPrefix + 196)
DECLARE_PMID(kScriptInfoIDSpace, kCustomAltTextPropertyScriptElement,			kGenericIDPrefix + 197)
DECLARE_PMID(kScriptInfoIDSpace, kCustomActualTextPropertyScriptElement,		kGenericIDPrefix + 198)
DECLARE_PMID(kScriptInfoIDSpace, kAltMetadataPropertyScriptElement,				kGenericIDPrefix + 199)
DECLARE_PMID(kScriptInfoIDSpace, kActualMetadataPropertyScriptElement,			kGenericIDPrefix + 200)
DECLARE_PMID(kScriptInfoIDSpace, kCustomImageConversionPropertyScriptElement,	kGenericIDPrefix + 201)
DECLARE_PMID(kScriptInfoIDSpace, kApplyTagTypePropertyScriptElement,			kGenericIDPrefix + 202)
DECLARE_PMID(kScriptInfoIDSpace, kImageConversionTypePropertyScriptElement,		kGenericIDPrefix + 203)
DECLARE_PMID(kScriptInfoIDSpace, kImageSizeOptionPropertyScriptElement,			kGenericIDPrefix + 204)
DECLARE_PMID(kScriptInfoIDSpace, kImageResolutionPropertyScriptElement,			kGenericIDPrefix + 205)
DECLARE_PMID(kScriptInfoIDSpace, kCustomImageAlignmentPropertyScriptElement,	kGenericIDPrefix + 206)
DECLARE_PMID(kScriptInfoIDSpace, kImageAlignmentPropertyScriptElement,			kGenericIDPrefix + 207)
DECLARE_PMID(kScriptInfoIDSpace, kImageSpaceBeforePropertyScriptElement,		kGenericIDPrefix + 208)
DECLARE_PMID(kScriptInfoIDSpace, kImageSpaceAfterPropertyScriptElement,			kGenericIDPrefix + 209)
DECLARE_PMID(kScriptInfoIDSpace, kSpaceUnitPropertyScriptElement,				kGenericIDPrefix + 210)
DECLARE_PMID(kScriptInfoIDSpace, kUseImagePageBreakPropertyScriptElement,		kGenericIDPrefix + 211)
DECLARE_PMID(kScriptInfoIDSpace, kImagePageBreakPropertyScriptElement,			kGenericIDPrefix + 212)
DECLARE_PMID(kScriptInfoIDSpace, kHorizontalConstraintsPropertyScriptElement,	kGenericIDPrefix + 213)
DECLARE_PMID(kScriptInfoIDSpace, kVerticalConstraintsPropertyScriptElement,		kGenericIDPrefix + 214)
DECLARE_PMID(kScriptInfoIDSpace, kEditBoxCustomHeightPropertyScriptElement,		kGenericIDPrefix + 215)
DECLARE_PMID(kScriptInfoIDSpace, kEditBoxCustomWidthPropertyScriptElement,		kGenericIDPrefix + 216)
DECLARE_PMID(kScriptInfoIDSpace, kEditBoxCustomSizePropertyScriptElement,		kGenericIDPrefix + 217)

//Methods
DECLARE_PMID(kScriptInfoIDSpace, kAltTextMethodScriptElement,					kGenericIDPrefix + 220)
DECLARE_PMID(kScriptInfoIDSpace, kActualTextMethodScriptElement,				kGenericIDPrefix + 221)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kResizeConstraintsEnumScriptElement,			kGenericIDPrefix + 228)
DECLARE_PMID(kScriptInfoIDSpace, kResizeMethodsEnumScriptElement,				kGenericIDPrefix + 229)
DECLARE_PMID(kScriptInfoIDSpace, kEmptyFrameFittingOptionEnumScriptElement,		kGenericIDPrefix + 230)
DECLARE_PMID(kScriptInfoIDSpace, kCornerOptionEnumScriptElement,				kGenericIDPrefix + 231)
DECLARE_PMID(kScriptInfoIDSpace, kDimensionConstraintsEnumScriptElement,			kGenericIDPrefix + 232)

//gap
DECLARE_PMID(kScriptInfoIDSpace, kSkipVerifyGroupItemsParamMetadataScriptElement,kGenericIDPrefix + 234)
DECLARE_PMID(kScriptInfoIDSpace, kGeoPathTypeDefScriptElement,					kGenericIDPrefix + 235)
DECLARE_PMID(kScriptInfoIDSpace, kPointTypeDefScriptElement,					kGenericIDPrefix + 236)
DECLARE_PMID(kScriptInfoIDSpace, kPathPointTypeDefScriptElement,				kGenericIDPrefix + 237)
DECLARE_PMID(kScriptInfoIDSpace, kRecBoundsTypeDefScriptElement,				kGenericIDPrefix + 238)
DECLARE_PMID(kScriptInfoIDSpace, kTransformMatrixTypeDefScriptElement,			kGenericIDPrefix + 239)
DECLARE_PMID(kScriptInfoIDSpace, kUnlinkFromWhatEnumScriptElement,				kGenericIDPrefix + 240)
DECLARE_PMID(kScriptInfoIDSpace, kContentTypeEnumScriptElement,					kGenericIDPrefix + 241)
DECLARE_PMID(kScriptInfoIDSpace, kEndCapEnumScriptElement,						kGenericIDPrefix + 242)
DECLARE_PMID(kScriptInfoIDSpace, kEndJoinEnumScriptElement,						kGenericIDPrefix + 243)
DECLARE_PMID(kScriptInfoIDSpace, kFlipOptionEnumScriptElement,					kGenericIDPrefix + 244)
DECLARE_PMID(kScriptInfoIDSpace, kStrokeCornerAdjustmentEnumScriptElement,		kGenericIDPrefix + 245)
DECLARE_PMID(kScriptInfoIDSpace, kArrowHeadEnumScriptElement,					kGenericIDPrefix + 246)
DECLARE_PMID(kScriptInfoIDSpace, kCornerEffectEnumScriptElement,				kGenericIDPrefix + 247)
DECLARE_PMID(kScriptInfoIDSpace, kLocalDisplaySettingEnumScriptElement,			kGenericIDPrefix + 249)
DECLARE_PMID(kScriptInfoIDSpace, kFitContentOptionEnumScriptElement,			kGenericIDPrefix + 250)
DECLARE_PMID(kScriptInfoIDSpace, kNonPrintingPropertyScriptElement,				kGenericIDPrefix + 251)
DECLARE_PMID(kScriptInfoIDSpace, kStrokeAlignmentEnumScriptElement,				kGenericIDPrefix + 252)
DECLARE_PMID(kScriptInfoIDSpace, kRealResizeMethodScriptElement,					kGenericIDPrefix + 253)
DECLARE_PMID(kScriptInfoIDSpace, kTransformAgainMethodScriptElement,				kGenericIDPrefix + 254)
DECLARE_PMID(kScriptInfoIDSpace, kTransformSequenceAgainMethodScriptElement,		kGenericIDPrefix + 255)


DECLARE_PMID(kScriptInfoIDSpace, kTransformAgainIndividuallyMethodScriptElement,		kGenericIDPrefix2 + 1)
DECLARE_PMID(kScriptInfoIDSpace, kTransformSequenceAgainIndividuallyMethodScriptElement,		kGenericIDPrefix2 + 2)
DECLARE_PMID(kScriptInfoIDSpace, kMatrixScaleMethodScriptElement,				kGenericIDPrefix2 + 3)
DECLARE_PMID(kScriptInfoIDSpace, kMatrixSkewMethodScriptElement,					kGenericIDPrefix2 + 4)
DECLARE_PMID(kScriptInfoIDSpace, kMatrixRotateMethodScriptElement,				kGenericIDPrefix2 + 5)
DECLARE_PMID(kScriptInfoIDSpace, kMatrixTranslateMethodScriptElement,			kGenericIDPrefix2 + 6)
DECLARE_PMID(kScriptInfoIDSpace, kMatrixCatenateMethodScriptElement,				kGenericIDPrefix2 + 7)
DECLARE_PMID(kScriptInfoIDSpace, kTransformMatrixValuesPropertyScriptElement,	kGenericIDPrefix2 + 8)
DECLARE_PMID(kScriptInfoIDSpace, kAlignDistributeBoundsPropertyEnumScriptElement,		kGenericIDPrefix2 + 9)
DECLARE_PMID(kScriptInfoIDSpace, kAlignDistributeItemsTypePropertyScriptElement,		kGenericIDPrefix2 + 10)
DECLARE_PMID(kScriptInfoIDSpace, kAlignItemsScriptElement,								kGenericIDPrefix2 + 11)
DECLARE_PMID(kScriptInfoIDSpace, kDistributeItemsScriptElement,							kGenericIDPrefix2 + 12)
DECLARE_PMID(kScriptInfoIDSpace, kAlignOptionsEnumScriptElement,						kGenericIDPrefix2 + 13)
DECLARE_PMID(kScriptInfoIDSpace, kDistributeOptionsEnumScriptElement,					kGenericIDPrefix2 + 14)
DECLARE_PMID(kScriptInfoIDSpace, kDistributeAbsoluteActivePropertyScriptElement,		kGenericIDPrefix2 + 15)
DECLARE_PMID(kScriptInfoIDSpace, kDistributeAbsoluteValuePropertyScriptElement,			kGenericIDPrefix2 + 16)
DECLARE_PMID(kScriptInfoIDSpace, kDistributeBySpaceBetweenAbsoluteActivePropertyScriptElement,		kGenericIDPrefix2 + 17)
DECLARE_PMID(kScriptInfoIDSpace, kDistributeAbsoluteBySpaceBetweenValuePropertyScriptElement,		kGenericIDPrefix2 + 18)
DECLARE_PMID(kScriptInfoIDSpace, kAlignDistributePrefsObjectScriptElement,			kGenericIDPrefix2 + 19)
DECLARE_PMID(kScriptInfoIDSpace, kAlignDistributePrefsPropertyScriptElement,		kGenericIDPrefix2 + 20)
//gap
DECLARE_PMID(kScriptInfoIDSpace, kTransformMatrixScaleXPropertyScriptElement,		kGenericIDPrefix2 + 50)
DECLARE_PMID(kScriptInfoIDSpace, kTransformMatrixScaleYPropertyScriptElement,		kGenericIDPrefix2 + 51)
DECLARE_PMID(kScriptInfoIDSpace, kTransformMatrixSkewPropertyScriptElement,			kGenericIDPrefix2 + 52)
DECLARE_PMID(kScriptInfoIDSpace, kTransformMatrixRotationPropertyScriptElement,		kGenericIDPrefix2 + 53)
DECLARE_PMID(kScriptInfoIDSpace, kTransformMatrixTranslateXPropertyScriptElement,	kGenericIDPrefix2 + 54)
DECLARE_PMID(kScriptInfoIDSpace, kTransformMatrixTranslateYPropertyScriptElement,	kGenericIDPrefix2 + 55)
DECLARE_PMID(kScriptInfoIDSpace, kMatrixInverseMethodScriptElement,					kGenericIDPrefix2 + 56)
DECLARE_PMID(kScriptInfoIDSpace, kMatrixApplyMethodScriptElement,					kGenericIDPrefix2 + 57)
DECLARE_PMID(kScriptInfoIDSpace, kTransformMatrixMappingPropertyScriptElement,		kGenericIDPrefix2 + 58)

DECLARE_PMID(kScriptInfoIDSpace, kCornerRadiusTopLeftPropertyScriptElement,		kGenericIDPrefix2 + 59)
DECLARE_PMID(kScriptInfoIDSpace, kCornerOptionsTopLeftPropertyScriptElement,	kGenericIDPrefix2 + 60)
DECLARE_PMID(kScriptInfoIDSpace, kCornerRadiusTopRightPropertyScriptElement,	kGenericIDPrefix2 + 61)
DECLARE_PMID(kScriptInfoIDSpace, kCornerOptionsTopRightPropertyScriptElement,	kGenericIDPrefix2 + 62)
DECLARE_PMID(kScriptInfoIDSpace, kCornerRadiusBottomLeftPropertyScriptElement,	kGenericIDPrefix2 + 63)
DECLARE_PMID(kScriptInfoIDSpace, kCornerOptionsBottomLeftPropertyScriptElement,	kGenericIDPrefix2 + 64)
DECLARE_PMID(kScriptInfoIDSpace, kCornerRadiusBottomRightPropertyScriptElement,	kGenericIDPrefix2 + 65)
DECLARE_PMID(kScriptInfoIDSpace, kCornerOptionsBottomRightPropertyScriptElement,kGenericIDPrefix2 + 66)

DECLARE_PMID(kScriptInfoIDSpace, kSourceTypeEnumScriptElement,					kGenericIDPrefix2 + 67)
DECLARE_PMID(kScriptInfoIDSpace, kTagTypeEnumScriptElement,						kGenericIDPrefix2 + 68)
DECLARE_PMID(kScriptInfoIDSpace, kImageConversionTypeEnumScriptElement,			kGenericIDPrefix2 + 69)
DECLARE_PMID(kScriptInfoIDSpace, kImageSizeOptionEnumScriptElement,				kGenericIDPrefix2 + 70)
DECLARE_PMID(kScriptInfoIDSpace, kImageResolutionEnumScriptElement,				kGenericIDPrefix2 + 71)
DECLARE_PMID(kScriptInfoIDSpace, kImageAlignmentEnumScriptElement,				kGenericIDPrefix2 + 72)
DECLARE_PMID(kScriptInfoIDSpace, kCSSUnitEnumScriptElement,						kGenericIDPrefix2 + 73)
DECLARE_PMID(kScriptInfoIDSpace, kImagePageBreakEnumScriptElement,				kGenericIDPrefix2 + 74)
DECLARE_PMID(kScriptInfoIDSpace, kUseoriginalImagePropertyScriptElement,		kGenericIDPrefix2 + 75)
DECLARE_PMID(kScriptInfoIDSpace, kEpubTypePropertyScriptElement,				kGenericIDPrefix2 + 76)
DECLARE_PMID(kScriptInfoIDSpace, kUseexistingImagePropertyScriptElement,				kGenericIDPrefix2 + 77)
//Adding Scripting Support for Height/Width
//DECLARE_PMID(kScriptInfoIDSpace, kCustomWidthPropertyScriptElement,							kGenericIDPrefix2 + 77)
DECLARE_PMID(kScriptInfoIDSpace, kCustomWidthTypeEnumScriptElement,							kGenericIDPrefix2 + 78)
DECLARE_PMID(kScriptInfoIDSpace, kCustomWidthTypePropertyScriptElement,						kGenericIDPrefix2 + 79)
//DECLARE_PMID(kScriptInfoIDSpace, kEditBoxCustomWidthUnitScriptElement,						kGenericIDPrefix2 + 80)
//DECLARE_PMID(kScriptInfoIDSpace, kWidthCSSUnitTypeEnumScriptElement,						kGenericIDPrefix2 + 81)

//DECLARE_PMID(kScriptInfoIDSpace, kCustomHeightPropertyScriptElement,						kGenericIDPrefix2 + 82)
DECLARE_PMID(kScriptInfoIDSpace, kCustomHeightTypeEnumScriptElement,						kGenericIDPrefix2 + 83)
DECLARE_PMID(kScriptInfoIDSpace, kCustomHeightTypePropertyScriptElement,					kGenericIDPrefix2 + 84)
//DECLARE_PMID(kScriptInfoIDSpace, kEditBoxCustomHeightUnitScriptElement,					kGenericIDPrefix2 + 85)
//DECLARE_PMID(kScriptInfoIDSpace, kHeightCSSUnitTypeEnumScriptElement,						kGenericIDPrefix2 + 86)
DECLARE_PMID(kScriptInfoIDSpace, kCustomSizeTypeEnumScriptElement,							kGenericIDPrefix2 + 85)
DECLARE_PMID(kScriptInfoIDSpace, kCustomSizeTypePropertyScriptElement,						kGenericIDPrefix2 + 86)
DECLARE_PMID(kScriptInfoIDSpace, kPreserveObjectLayoutAppearanceEnumScriptElement,					kGenericIDPrefix2 + 87)
DECLARE_PMID(kScriptInfoIDSpace, kPreserveObjectLayoutAppearancePropertyScriptElement,				kGenericIDPrefix2 + 88)
DECLARE_PMID(kScriptInfoIDSpace, kConvertToRawTextMethodScriptElement, kGenericIDPrefix2 + 89)

//gap
DECLARE_PMID(kScriptInfoIDSpace, kArrowHeadAlignmentPropertyScriptElement,		kGenericIDPrefix2 + 94)
DECLARE_PMID(kScriptInfoIDSpace, kArrowHeadAlignmentEnumScriptElement,						kGenericIDPrefix2 + 95)
DECLARE_PMID(kScriptInfoIDSpace, kLeftArrowHeadScalePropertyScriptElement,						kGenericIDPrefix2 + 96)
DECLARE_PMID(kScriptInfoIDSpace, kRightArrowHeadScalePropertyScriptElement,						kGenericIDPrefix2 + 97)
DECLARE_PMID(kScriptInfoIDSpace, kLayoutAttributeOptionsObjectScriptElement, kGenericIDPrefix2 + 98)
DECLARE_PMID(kScriptInfoIDSpace, kLayoutAttributeOptionsPropertyScritElement, kGenericIDPrefix2 + 99)
DECLARE_PMID(kScriptInfoIDSpace, kTransformXPositionScriptElement, kGenericIDPrefix2 + 100)
DECLARE_PMID(kScriptInfoIDSpace, kTransformYPositionScriptElement, kGenericIDPrefix2 + 101)
DECLARE_PMID(kScriptInfoIDSpace, kTransformWidthScriptElement, kGenericIDPrefix2 + 102)
DECLARE_PMID(kScriptInfoIDSpace, kTransformHeightScriptElement, kGenericIDPrefix2 + 103)
DECLARE_PMID(kScriptInfoIDSpace, kTransformLeftRefPointScriptElement, kGenericIDPrefix2 + 104)
DECLARE_PMID(kScriptInfoIDSpace, kTransformTopRefPointScriptElement, kGenericIDPrefix2 + 105)
DECLARE_PMID(kScriptInfoIDSpace, kTransformPositionRefPointEnumScriptElement, kGenericIDPrefix2 + 106)
DECLARE_PMID(kScriptInfoIDSpace, kTransformAttrRefAnchorPointScriptElement, kGenericIDPrefix2 + 107)
DECLARE_PMID(kScriptInfoIDSpace, kObjStylesTransformAttrsCategoryScriptElement, kGenericIDPrefix2 + 108)
DECLARE_PMID(kScriptInfoIDSpace, kObjStylesTransformAttrEnableDisableDimensionsAttrScriptElement, kGenericIDPrefix2 + 109)
DECLARE_PMID(kScriptInfoIDSpace, kObjStylesTransformAttrEnableDisablePositionAttrScriptElement, kGenericIDPrefix2 + 110)
DECLARE_PMID(kScriptInfoIDSpace, kWhichDimAttributeEnumScriptElement, kGenericIDPrefix2 + 111)
DECLARE_PMID(kScriptInfoIDSpace, kWhichPosAttributeEnumScriptElement, kGenericIDPrefix2 + 112)



//---------------------------------------------------
// InvalHandlerTypeID
//---------------------------------------------------
DECLARE_PMID(kInvalHandlerIDSpace, kTransformAgainInvalHandlerID, kGenericIDPrefix + 1)


///////////////////////////////////////////////////////////////////////////////////////////////////////
//     Object Styles																				 //
///////////////////////////////////////////////////////////////////////////////////////////////////////

// ClassIDs
DECLARE_PMID(kClassIDSpace, kObjectStyleBoss,				kObjectStylePrefix + 1 )
DECLARE_PMID(kClassIDSpace, kObjectStyleNewWSResponderBoss, kObjectStylePrefix + 2 )
DECLARE_PMID(kClassIDSpace, kObjectStyleNewDocResponderBoss,kObjectStylePrefix + 3 )
DECLARE_PMID(kClassIDSpace, kNewObjectStyleCmdBoss,			kObjectStylePrefix + 4 )
DECLARE_PMID(kClassIDSpace, kDeleteObjectStyleCmdBoss,		kObjectStylePrefix + 5 )
DECLARE_PMID(kClassIDSpace, kObjectStyleBaseCmdBoss,		kObjectStylePrefix + 6 )
DECLARE_PMID(kClassIDSpace, kDuplicateObjectStyleCmdBoss,	kObjectStylePrefix + 7 )
DECLARE_PMID(kClassIDSpace, kLoadObjectStyleCmdBoss,		kObjectStylePrefix + 8 )
DECLARE_PMID(kClassIDSpace, kEditObjectStyleCmdBoss,		kObjectStylePrefix + 9 )
DECLARE_PMID(kClassIDSpace, kReplaceObjectStylesCmdBoss,	kObjectStylePrefix + 10 )
DECLARE_PMID(kClassIDSpace, kSortObjectStyleCmdBoss,		kObjectStylePrefix + 11 )
DECLARE_PMID(kClassIDSpace, kMoveObjectStyleCmdBoss,		kObjectStylePrefix + 12 )
DECLARE_PMID(kClassIDSpace, kSetDefaultObjectStyleCmdBoss,	kObjectStylePrefix + 13 )
DECLARE_PMID(kClassIDSpace, kUnlinkObjectStyleCmdBoss,		kObjectStylePrefix + 14 )
DECLARE_PMID(kClassIDSpace, kApplyObjectStyleCmdBoss,		kObjectStylePrefix + 15 )
DECLARE_PMID(kClassIDSpace, kObjectStylePhase2ConversionBoss, kObjectStylePrefix + 16 )
DECLARE_PMID(kClassIDSpace, kGfxObjStylesAttrHandlerBoss, kObjectStylePrefix + 17 )
DECLARE_PMID(kClassIDSpace, kDeleteObjectStylesCmdBoss,		kObjectStylePrefix + 18 )
DECLARE_PMID(kClassIDSpace, kDuplicateObjectStylesCmdBoss,  kObjectStylePrefix + 19 )
DECLARE_PMID(kClassIDSpace, kMoveObjectStylesCmdBoss,		kObjectStylePrefix + 20 )
DECLARE_PMID(kClassIDSpace, kTFObjectStylesAttrsHandlerBoss, kObjectStylePrefix + 21 )
DECLARE_PMID(kClassIDSpace, kObjectStylesTargetBoss, kObjectStylePrefix + 22 )
DECLARE_PMID(kClassIDSpace, kApplyObjStyleToDefaultsCmdBoss,		kObjectStylePrefix + 23 )
DECLARE_PMID(kClassIDSpace, kObjStylesBaselineFrameGridConversionProviderBoss, kObjectStylePrefix + 24 )
DECLARE_PMID(kClassIDSpace, kObjectStylesSyncBoss,			kObjectStylePrefix + 25 )
DECLARE_PMID(kClassIDSpace, kObjectStyleAttrBoss,			kObjectStylePrefix + 26 )
DECLARE_PMID(kClassIDSpace, kChangeDefaultTFObjStyleCmdBoss,	kObjectStylePrefix + 27 )
DECLARE_PMID(kClassIDSpace, kXPObjStylesAttrHandlerBoss,	kObjectStylePrefix + 28 )
DECLARE_PMID(kClassIDSpace, kCopyOneObjectStyleCmdBoss,		kObjectStylePrefix + 29 )
DECLARE_PMID(kClassIDSpace, kObjStylesTFOptionsCollectDataBoss,		kObjectStylePrefix + 30 )
DECLARE_PMID(kClassIDSpace, kBreaklinkWithObjectStylesCmdBoss, kObjectStylePrefix + 31 )
DECLARE_PMID(kClassIDSpace, kEditObjectStyleInfoSubCmdBoss, kObjectStylePrefix + 32)
DECLARE_PMID(kClassIDSpace, kEditObjectStyleTargetSubCmdBoss, kObjectStylePrefix + 33)
DECLARE_PMID(kClassIDSpace, kExportObjectStylesCmdBoss,		kObjectStylePrefix + 34)
DECLARE_PMID(kClassIDSpace, kImportObjectStylesCmdBoss,		kObjectStylePrefix + 35)
DECLARE_PMID(kClassIDSpace, kObjectStylesScriptProviderBoss, kObjectStylePrefix + 36)
DECLARE_PMID(kClassIDSpace, kEditObjectStyleForDefaultCmdBoss, kObjectStylePrefix + 37)
DECLARE_PMID(kClassIDSpace, kObjStylesRIDXNotifierHandlerBoss, kObjectStylePrefix + 38)
DECLARE_PMID(kClassIDSpace, kSetAllUsedStyleCmdBoss, kObjectStylePrefix + 39)
DECLARE_PMID(kClassIDSpace, kObjectStyleConverterBoss, kObjectStylePrefix + 40)
DECLARE_PMID(kClassIDSpace, kObjectStylesAnchoredFrameDataBoss, kObjectStylePrefix + 41)
DECLARE_PMID(kClassIDSpace, kParaStyleObjectStylesAttrHandlerBoss, kObjectStylePrefix + 42)
DECLARE_PMID(kClassIDSpace, kInnerChangeDefaultStylesCmdBoss, kObjectStylePrefix + 43)
DECLARE_PMID(kClassIDSpace, kUpdateNamedGridForObjectStyleCmdBoss, kObjectStylePrefix + 44)
DECLARE_PMID(kClassIDSpace, kObjectStyleOpenDocResponderBoss, kObjectStylePrefix + 45)
DECLARE_PMID(kClassIDSpace, kRemoveStyleFromObjStyleNameTableCmdBoss, kObjectStylePrefix + 46)
DECLARE_PMID(kClassIDSpace, kChangeBasedOnStyleInnerCmdBoss, kObjectStylePrefix + 47)

// Attribute Categories
DECLARE_PMID(kClassIDSpace, kGeneralAttributeCategory,		kObjectStylePrefix + 50)
DECLARE_PMID(kClassIDSpace, kFillAttributeCategory,			kObjectStylePrefix + 51)
DECLARE_PMID(kClassIDSpace, kStrokeAttributeCategory,		kObjectStylePrefix + 52)
DECLARE_PMID(kClassIDSpace, kStrokeEffectAttributeCategory,	kObjectStylePrefix + 53)
DECLARE_PMID(kClassIDSpace, kCornerEffectAttributeCategory,	kObjectStylePrefix + 54)
DECLARE_PMID(kClassIDSpace, kTransparencyAttributeCategory,	kObjectStylePrefix + 55)
DECLARE_PMID(kClassIDSpace, kDropShadowAttributeCategory,	kObjectStylePrefix + 56)
DECLARE_PMID(kClassIDSpace, kVignetteAttributeCategory,		kObjectStylePrefix + 57)
DECLARE_PMID(kClassIDSpace, kDefaultAttributeCategory,		kObjectStylePrefix + 58)
DECLARE_PMID(kClassIDSpace, kGradFillGraphicAttributeCategory,		kObjectStylePrefix + 59)
DECLARE_PMID(kClassIDSpace, kGradStrokeGraphicAttributeCategory,	kObjectStylePrefix + 60)
DECLARE_PMID(kClassIDSpace, kFormFieldGraphicsAttributeCategory,	kObjectStylePrefix + 61)
DECLARE_PMID(kClassIDSpace, kTextFrameOptionsDataAttributeCategory, kObjectStylePrefix + 62)
DECLARE_PMID(kClassIDSpace, kParagraphStyleCategory, kObjectStylePrefix + 63)
DECLARE_PMID(kClassIDSpace, kStoryOptionsDataAttributeCategory, kObjectStylePrefix + 64)
DECLARE_PMID(kClassIDSpace, kObjStylesSwatchesRIDXNotifierHandlerBoss, kObjectStylePrefix + 65 )
DECLARE_PMID(kClassIDSpace, kOtherObjStylesAttributeCategory,		kObjectStylePrefix + 66 )
DECLARE_PMID(kClassIDSpace, kInnerShadowAttributeCategory,			kObjectStylePrefix + 67)
DECLARE_PMID(kClassIDSpace, kOuterGlowAttributeCategory,			kObjectStylePrefix + 68)
DECLARE_PMID(kClassIDSpace, kInnerGlowAttributeCategory,			kObjectStylePrefix + 69)
DECLARE_PMID(kClassIDSpace, kBevelEmbossAttributeCategory,			kObjectStylePrefix + 70)
DECLARE_PMID(kClassIDSpace, kSatinAttributeCategory,				kObjectStylePrefix + 71)
DECLARE_PMID(kClassIDSpace, kStrokeTransparencyAttributeCategory,	kObjectStylePrefix + 72)
DECLARE_PMID(kClassIDSpace, kStrokeDropShadowAttributeCategory,		kObjectStylePrefix + 73)
DECLARE_PMID(kClassIDSpace, kStrokeVignetteAttributeCategory,		kObjectStylePrefix + 74)
DECLARE_PMID(kClassIDSpace, kStrokeInnerShadowAttributeCategory,	kObjectStylePrefix + 75)
DECLARE_PMID(kClassIDSpace, kStrokeOuterGlowAttributeCategory,		kObjectStylePrefix + 76)
DECLARE_PMID(kClassIDSpace, kStrokeInnerGlowAttributeCategory,		kObjectStylePrefix + 77)
DECLARE_PMID(kClassIDSpace, kStrokeBevelEmbossAttributeCategory,	kObjectStylePrefix + 78)
DECLARE_PMID(kClassIDSpace, kStrokeSatinAttributeCategory,			kObjectStylePrefix + 79)
DECLARE_PMID(kClassIDSpace, kFillTransparencyAttributeCategory,		kObjectStylePrefix + 80)
DECLARE_PMID(kClassIDSpace, kFillDropShadowAttributeCategory,		kObjectStylePrefix + 81)
DECLARE_PMID(kClassIDSpace, kFillVignetteAttributeCategory,			kObjectStylePrefix + 82)
DECLARE_PMID(kClassIDSpace, kFillInnerShadowAttributeCategory,		kObjectStylePrefix + 83)
DECLARE_PMID(kClassIDSpace, kFillOuterGlowAttributeCategory,		kObjectStylePrefix + 84)
DECLARE_PMID(kClassIDSpace, kFillInnerGlowAttributeCategory,		kObjectStylePrefix + 85)
DECLARE_PMID(kClassIDSpace, kFillBevelEmbossAttributeCategory,		kObjectStylePrefix + 86)
DECLARE_PMID(kClassIDSpace, kFillSatinAttributeCategory,			kObjectStylePrefix + 87)
DECLARE_PMID(kClassIDSpace, kContentTransparencyAttributeCategory,	kObjectStylePrefix + 88)
DECLARE_PMID(kClassIDSpace, kContentDropShadowAttributeCategory,	kObjectStylePrefix + 89)
DECLARE_PMID(kClassIDSpace, kContentVignetteAttributeCategory,		kObjectStylePrefix + 90)
DECLARE_PMID(kClassIDSpace, kContentInnerShadowAttributeCategory,	kObjectStylePrefix + 91)
DECLARE_PMID(kClassIDSpace, kContentOuterGlowAttributeCategory,		kObjectStylePrefix + 92)
DECLARE_PMID(kClassIDSpace, kContentInnerGlowAttributeCategory,		kObjectStylePrefix + 93)
DECLARE_PMID(kClassIDSpace, kContentBevelEmbossAttributeCategory,	kObjectStylePrefix + 94)
DECLARE_PMID(kClassIDSpace, kContentSatinAttributeCategory,			kObjectStylePrefix + 95)
DECLARE_PMID(kClassIDSpace, kFrameFittingOptionsCategory,			kObjectStylePrefix + 96)
DECLARE_PMID(kClassIDSpace, kFittingObjStylesAttrsHandlerBoss,		kObjectStylePrefix + 97)
DECLARE_PMID(kClassIDSpace, kObjectStylePaletteNotificationMsg, kObjectStylePrefix + 100)
DECLARE_PMID(kClassIDSpace, kDirectionalFeatherAttributeCategory,			kObjectStylePrefix + 101)
DECLARE_PMID(kClassIDSpace, kStrokeDirectionalFeatherAttributeCategory,		kObjectStylePrefix + 102)
DECLARE_PMID(kClassIDSpace, kFillDirectionalFeatherAttributeCategory,		kObjectStylePrefix + 103)
DECLARE_PMID(kClassIDSpace, kContentDirectionalFeatherAttributeCategory,	kObjectStylePrefix + 104)
DECLARE_PMID(kClassIDSpace, kGradientFeatherAttributeCategory,			kObjectStylePrefix + 105)
DECLARE_PMID(kClassIDSpace, kStrokeGradientFeatherAttributeCategory,	kObjectStylePrefix + 106)
DECLARE_PMID(kClassIDSpace, kFillGradientFeatherAttributeCategory,		kObjectStylePrefix + 107)
DECLARE_PMID(kClassIDSpace, kContentGradientFeatherAttributeCategory,	kObjectStylePrefix + 108)

DECLARE_PMID(kClassIDSpace, kObjStylesPageItemEffectsCategory,			kObjectStylePrefix + 109)
DECLARE_PMID(kClassIDSpace, kObjStylesFillEffectsCategory,				kObjectStylePrefix + 110)
DECLARE_PMID(kClassIDSpace, kObjStylesStrokeEffectsCategory,			kObjectStylePrefix + 111)
DECLARE_PMID(kClassIDSpace, kObjStylesContentEffectsCategory,			kObjectStylePrefix + 112)

//for style groups
DECLARE_PMID(kClassIDSpace, kObjectStylesScriptProvider50Boss,		kObjectStylePrefix + 113)
DECLARE_PMID(kClassIDSpace, kRootObjectStyleHierarchyBoss,			kObjectStylePrefix + 114)
DECLARE_PMID(kClassIDSpace, kDeleteObjectStyleGroupCmdBoss,			kObjectStylePrefix + 115)
DECLARE_PMID(kClassIDSpace, kDuplicateObjectStyleGroupCmdBoss,		kObjectStylePrefix + 116)
DECLARE_PMID(kClassIDSpace, kMoveObjectStyleGroupCmdBoss,			kObjectStylePrefix + 117)
DECLARE_PMID(kClassIDSpace, kCopyToObjectStyleGroupCmdBoss,			kObjectStylePrefix + 118)

DECLARE_PMID(kClassIDSpace, kObjectStylesXPEffectsScriptProviderBoss, kObjectStylePrefix + 119)
DECLARE_PMID(kClassIDSpace, kObjectStylesScriptProvider60Boss, kObjectStylePrefix + 120)
DECLARE_PMID(kClassIDSpace, kObjStylesOEOptionsCollectDataBoss, kObjectStylePrefix + 121)
DECLARE_PMID(kClassIDSpace, kOEOptionsAltTextDataAttributeCategory, kObjectStylePrefix + 122)
DECLARE_PMID(kClassIDSpace, kOEOjectStylesAttrHandlerBoss, kObjectStylePrefix + 123)
DECLARE_PMID(kClassIDSpace, kOEOptionsTaggedPDFDataAttributeCategory, kObjectStylePrefix + 124)
DECLARE_PMID(kClassIDSpace, kOEOptionsEPUBAndHTMLDataAttributeCategory, kObjectStylePrefix + 125)
DECLARE_PMID(kClassIDSpace, kObjStylesExportTaggingCategory,		kObjectStylePrefix + 126)
DECLARE_PMID(kClassIDSpace, kExportTaggingObjStylesAttrHandlerBoss, kObjectStylePrefix + 127 )
DECLARE_PMID(kClassIDSpace, kObjectStylesScriptProvider90Boss, kObjectStylePrefix + 128)
DECLARE_PMID(kClassIDSpace, kObjectStylesExportTagScriptProviderBoss, kObjectStylePrefix + 129)
DECLARE_PMID(kClassIDSpace, kObjStylesTransformAttrsOptionsBoss, kObjectStylePrefix + 130)
DECLARE_PMID(kClassIDSpace, kObjectStylesScriptProvider130Boss, kObjectStylePrefix + 131)
DECLARE_PMID(kClassIDSpace, kContentAwareFitAsDefaultPrefCmdBoss, kObjectStylePrefix + 132)
DECLARE_PMID(kClassIDSpace, kContentAwareFitCmdBoss, kObjectStylePrefix + 133)

// InterfaceIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IOBJECTSTYLEATTRINFO,	kObjectStylePrefix + 1 )
DECLARE_PMID(kInterfaceIDSpace, IID_IOBJECTSTYLENAMETABLE_OBSOLETE,	kObjectStylePrefix + 2 )
DECLARE_PMID(kInterfaceIDSpace, IID_IOBJECTATTRIBUTELIST,	kObjectStylePrefix + 3 )
DECLARE_PMID(kInterfaceIDSpace, IID_IOBJECTSTYLEINFO,		kObjectStylePrefix + 4 )
DECLARE_PMID(kInterfaceIDSpace, IID_IDISPLAYUIDATA,			kObjectStylePrefix + 5 )
DECLARE_PMID(kInterfaceIDSpace, IID_ISOURCEOBJECTSTYLE,		kObjectStylePrefix + 6 )
DECLARE_PMID(kInterfaceIDSpace, IID_ITARGETOBJECTSTYLES,	kObjectStylePrefix + 7 )
DECLARE_PMID(kInterfaceIDSpace, IID_IPERSISTOBJECTSTYLEDATA,kObjectStylePrefix + 8 )
DECLARE_PMID(kInterfaceIDSpace, IID_IOBJSTYLESATTRHANDLER, kObjectStylePrefix + 9 )
DECLARE_PMID(kInterfaceIDSpace, IID_IOBJECTSTYLESUTILS, kObjectStylePrefix + 10 )
DECLARE_PMID(kInterfaceIDSpace, IID_IOBJECTSTYLESSUITE, kObjectStylePrefix + 11 )
DECLARE_PMID(kInterfaceIDSpace, IID_IOBJECTSTYLESFACADE, kObjectStylePrefix + 12 )
DECLARE_PMID(kInterfaceIDSpace, IID_IGFXOBJECTATTRIBUTELIST,	kObjectStylePrefix + 13 )
DECLARE_PMID(kInterfaceIDSpace, IID_IXPOBJECTATTRIBUTELIST,	kObjectStylePrefix + 14 )
DECLARE_PMID(kInterfaceIDSpace, IID_IOBJSTYLESATTRCATEGORIESLIST,	kObjectStylePrefix + 15 )
DECLARE_PMID(kInterfaceIDSpace, IID_IOBJECTSTYLESSCRIPTUTILS,	kObjectStylePrefix + 16 )
DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTIONSUITEDATA,		kObjectStylePrefix + 17 )
DECLARE_PMID(kInterfaceIDSpace, IID_IACTIVEUSEDSTYLELIST,		kObjectStylePrefix + 18 )
DECLARE_PMID(kInterfaceIDSpace, IID_IREPLACEWITHOBJECTSTYLE,	kObjectStylePrefix + 19 )
DECLARE_PMID(kInterfaceIDSpace, IID_IAFFECTEDPAGEITEMLIST,		kObjectStylePrefix + 20 )
DECLARE_PMID(kInterfaceIDSpace, IID_IAFFECTEDBASEDONSTYLELIST,	kObjectStylePrefix + 21 )
DECLARE_PMID(kInterfaceIDSpace, IID_ICLEAROVERRIDECATEGORIES_DATA,		kObjectStylePrefix + 22 )
DECLARE_PMID(kInterfaceIDSpace, IID_IOBJECTSTYLECACHE,	kObjectStylePrefix + 23 )
DECLARE_PMID(kInterfaceIDSpace, IID_IOBJSTYLE_PARAGRAPHSTYLEUID,	kObjectStylePrefix + 24 )
DECLARE_PMID(kInterfaceIDSpace, IID_IAPPLYATTRS_DATA,				kObjectStylePrefix + 25 )
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IOBJECTSTYLESSELECTIONCACHE, kObjectStylePrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_IOBJSTYLE_PARAGRAPHSTYLE_APPLYNEXTSTYLEBOOL, kObjectStylePrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_IAPPLYDEFAULTFRAMEGRIDCMD,		kObjectStylePrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_IUSERTRIGGEREDDATAMERGE, kObjectStylePrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_IREPLACENAMEDGRIDDATA,		kObjectStylePrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_INORMALGRIDOBJECTSTYLEUSEDINDOC, kObjectStylePrefix + 32)
DECLARE_PMID(kInterfaceIDSpace, IID_ILOADNORMALGRIDSTYLEFLAG, kObjectStylePrefix + 33)
DECLARE_PMID(kInterfaceIDSpace, IID_ICHANGEOBJSTYLECATEGORIES, kObjectStylePrefix + 34)
DECLARE_PMID(kInterfaceIDSpace, IID_IFRAMEFITTINGOBJECTATTRIBUTELIST, kObjectStylePrefix + 35)
DECLARE_PMID(kInterfaceIDSpace, IID_IOBJECTSTYLEGROUPMANAGER,	kObjectStylePrefix + 36)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRIVATEOBJECTSTYLESFACADE, kObjectStylePrefix + 37 )		
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTENTAWAREFITPREFERENCE, kObjectStylePrefix + 38)

// ImplementationIDs
DECLARE_PMID(kImplementationIDSpace, kApplyObjectStyleCmdImpl,		kObjectStylePrefix + 1 )
DECLARE_PMID(kImplementationIDSpace, kUnlinkObjectStyleCmdImpl,		kObjectStylePrefix + 2 )
DECLARE_PMID(kImplementationIDSpace, kMoveObjectStyleCmdImpl,		kObjectStylePrefix + 3 )
DECLARE_PMID(kImplementationIDSpace, kSetDefaultObjectStyleCmdImpl, kObjectStylePrefix + 4 )
DECLARE_PMID(kImplementationIDSpace, kObjectStyleNameTableImpl,		kObjectStylePrefix + 5 )
DECLARE_PMID(kImplementationIDSpace, kObjectAttributeListImpl,		kObjectStylePrefix + 6 )
DECLARE_PMID(kImplementationIDSpace, kObjectStyleInfoImpl,			kObjectStylePrefix + 7 )
DECLARE_PMID(kImplementationIDSpace, kObjectStyleNewWSResponderImpl,kObjectStylePrefix + 8 )
DECLARE_PMID(kImplementationIDSpace, kObjectStyleNewDocResponderImpl, kObjectStylePrefix + 9 )
DECLARE_PMID(kImplementationIDSpace, kObjectStyleScriptImpl,		kObjectStylePrefix + 10 )
DECLARE_PMID(kImplementationIDSpace, kNewObjectStyleCmdImpl,		kObjectStylePrefix + 11 )
DECLARE_PMID(kImplementationIDSpace, kDeleteObjectStyleCmdImpl,		kObjectStylePrefix + 12 )
DECLARE_PMID(kImplementationIDSpace, kDuplicateObjectStyleCmdImpl,	kObjectStylePrefix + 13 )
DECLARE_PMID(kImplementationIDSpace, kDisplayUIDataImpl,			kObjectStylePrefix + 14 )
DECLARE_PMID(kImplementationIDSpace, kLoadObjectStyleCmdImpl,		kObjectStylePrefix + 15 )
DECLARE_PMID(kImplementationIDSpace, kEditObjectStyleCmdImpl,		kObjectStylePrefix + 16 )
DECLARE_PMID(kImplementationIDSpace, kReplaceObjectStylesCmdImpl,	kObjectStylePrefix + 17 )
DECLARE_PMID(kImplementationIDSpace, kSourceObjectStyleImpl,		kObjectStylePrefix + 18 )
DECLARE_PMID(kImplementationIDSpace, kTargetObjectStylesImpl,		kObjectStylePrefix + 19 )
DECLARE_PMID(kImplementationIDSpace, kSortObjectStyleCmdImpl,		kObjectStylePrefix + 20 )
DECLARE_PMID(kImplementationIDSpace, kObjectStylePhase2ConversionImpl, kObjectStylePrefix + 21 )
DECLARE_PMID(kImplementationIDSpace, kPersistObjectStyleDataImpl,	kObjectStylePrefix + 22 )
DECLARE_PMID(kImplementationIDSpace, kGfxObjStylesAttrsHandlerImpl, kObjectStylePrefix + 23 )
DECLARE_PMID(kImplementationIDSpace, kObjectStylesUtilsImpl, kObjectStylePrefix + 24 )
DECLARE_PMID(kImplementationIDSpace, kObjStylesServiceProviderImpl, kObjectStylePrefix + 25 )
DECLARE_PMID(kImplementationIDSpace, kObjectStylesSuiteDefaultCSBImpl, kObjectStylePrefix + 26 )
//DECLARE_PMID(kImplementationIDSpace, kMyFancyNewImpl, kObjectStylePrefix + 27 )
DECLARE_PMID(kImplementationIDSpace, kObjectStylesSuiteLayoutCSBImpl, kObjectStylePrefix + 28 )
DECLARE_PMID(kImplementationIDSpace, kObjectStylesSuiteASBImpl, kObjectStylePrefix + 29 )
DECLARE_PMID(kImplementationIDSpace, kDeleteObjectStylesCmdImpl,	kObjectStylePrefix + 30 )
DECLARE_PMID(kImplementationIDSpace, kDuplicateObjectStylesCmdImpl,	kObjectStylePrefix + 31 )
DECLARE_PMID(kImplementationIDSpace, kMoveObjectStylesCmdImpl,		kObjectStylePrefix + 32 )
DECLARE_PMID(kImplementationIDSpace, kTFObjectStylesAttrsHandlerImpl, kObjectStylePrefix + 33 )
DECLARE_PMID(kImplementationIDSpace, kObjectStylesFacadeImpl, kObjectStylePrefix + 34 )
DECLARE_PMID(kImplementationIDSpace, kPersistObjectStyleTargetImpl, kObjectStylePrefix + 35 )
DECLARE_PMID(kImplementationIDSpace, kObjStylesTextFrameOptDataImpl, kObjectStylePrefix + 36 )
DECLARE_PMID(kImplementationIDSpace, kOSBaselineFGCodeConversionProviderImpl, kObjectStylePrefix + 37 )
DECLARE_PMID(kImplementationIDSpace, kObjectStylesSyncServiceImpl,	kObjectStylePrefix + 38 )
DECLARE_PMID(kImplementationIDSpace, kApplyObjStyleToDefaultsCmdImpl, kObjectStylePrefix + 39 )
DECLARE_PMID(kImplementationIDSpace, kObjectStyleAttrInfoImpl,	kObjectStylePrefix + 40 )
DECLARE_PMID(kImplementationIDSpace, kChangeDefaultTFObjStyleCmdImpl,	kObjectStylePrefix + 41 )
DECLARE_PMID(kImplementationIDSpace, kXPObjStylesAttrsHandlerImpl, kObjectStylePrefix + 42 )
DECLARE_PMID(kImplementationIDSpace, kGfxObjectAttributeListImpl,	kObjectStylePrefix + 43 )
DECLARE_PMID(kImplementationIDSpace, kXPObjectAttributeListImpl, kObjectStylePrefix + 44 )
DECLARE_PMID(kImplementationIDSpace, kCopyOneObjectStyleCmdImpl, kObjectStylePrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kObjStylesAttrCategoriesListImpl, kObjectStylePrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kEditObjectStyleInfoSubCmdImpl, kObjectStylePrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kEditObjectStyleTargetSubCmdImpl, kObjectStylePrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kExportObjectStylesCmdImpl,	kObjectStylePrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kImportObjectStylesCmdImpl,	kObjectStylePrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kObjectStylesScriptProviderImpl, kObjectStylePrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kObjectStylesScriptUtilsImpl, kObjectStylePrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kObjStylesGfxStyleDescriptorImpl, kObjectStylePrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kBreaklinkWithObjectStylesCmdImpl,kObjectStylePrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kObjectStylesSuiteTextCSBImpl, kObjectStylePrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kEditObjectStyleForDefaultCmdImpl, kObjectStylePrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kSelectionSuiteDataImpl, kObjectStylePrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kObjStylesRIDXNotifierHandlerImpl, kObjectStylePrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kReplaceWithObjectStyleImpl, kObjectStylePrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kObjectStylesRefConverterImpl, kObjectStylePrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kSetAllUsedStyleCmdImpl, kObjectStylePrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kActiveUsedStyleListImpl, kObjectStylePrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kAffectedBasedOnObjectStyleListImpl, kObjectStylePrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kObjectStylesSuiteLayoutCSBSelectionExtImpl,	kObjectStylePrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kObjectStylesSuiteDefaultCSBSelectionExtImpl,	kObjectStylePrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kObjectStylesLayoutSelectionCacheImpl,	kObjectStylePrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kObjectStylesDefaultSelectionCacheImpl,	kObjectStylePrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kObjectStylesTextSelectionCacheImpl,	kObjectStylePrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kProcessGfxAttrsObjStylesServiceProviderImpl,	kObjectStylePrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kObjStyleParaStylePersistDataImpl,	kObjectStylePrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kParaStyleObjectStylesAttrHandlerImpl,	kObjectStylePrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kInnerChangeDefaultStylesCmdImpl,	kObjectStylePrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kLoadObjectStyleCmdInfoImpl, kObjectStylePrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kObjStylesSwatchesRIDXNotifierHandlerImpl, kObjectStylePrefix + 74 )
DECLARE_PMID(kImplementationIDSpace, kObjStylesSwatchReferenceDataImpl, kObjectStylePrefix + 75 )
DECLARE_PMID(kImplementationIDSpace, kObjectStyleCacheImpl,	kObjectStylePrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kObjStyleParaStyleApplyNextStyleDataImpl,	kObjectStylePrefix + 77)
DECLARE_PMID(kImplementationIDSpace, kUpdateNamedGridForObjectStyleCmdImpl, kObjectStylePrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kReplacedNamedGridDataImpl, kObjectStylePrefix + 79)
DECLARE_PMID(kImplementationIDSpace, kObjectStyleOpenDocResponderImpl, kObjectStylePrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kNormalGridObjectStyleUsedInDocImpl, kObjectStylePrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kRemoveStyleFromObjStyleNameTableCmdImpl, kObjectStylePrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kChangeBasedOnStyleInnerCmdImpl, kObjectStylePrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kLoadNormalGridStyleFlagImpl,	kObjectStylePrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kChangedObjectStyleCategoriesImpl,	kObjectStylePrefix + 85)
DECLARE_PMID(kImplementationIDSpace, kFrameFittingObjectAttributeListImpl, kObjectStylePrefix + 86 )
DECLARE_PMID(kImplementationIDSpace, kFittingObjStylesAttrsHandlerImpl, kObjectStylePrefix + 87 )
DECLARE_PMID(kImplementationIDSpace, kFrameContentSuiteDefaultCSBImpl, kObjectStylePrefix + 88 )
DECLARE_PMID(kImplementationIDSpace, kObjectStyleGroupManagerImpl, kObjectStylePrefix + 89 )
DECLARE_PMID(kImplementationIDSpace, kRootObjectStyleHierarchyImpl, kObjectStylePrefix + 90 )
DECLARE_PMID(kImplementationIDSpace, kObjectStyleHierarchyImpl, kObjectStylePrefix + 91 )
DECLARE_PMID(kImplementationIDSpace, kPrivateObjectStylesFacadeImpl, kObjectStylePrefix + 92 )
DECLARE_PMID(kImplementationIDSpace, kDeleteObjectStyleGroupCmdImpl, kObjectStylePrefix + 93 )
DECLARE_PMID(kImplementationIDSpace, kDuplicateObjectStyleGroupCmdImpl, kObjectStylePrefix + 94 )
DECLARE_PMID(kImplementationIDSpace, kObjectStylesScriptProvider50Impl, kObjectStylePrefix + 95 )
DECLARE_PMID(kImplementationIDSpace, kMoveObjectStyleGroupCmdImpl, kObjectStylePrefix + 96 )
DECLARE_PMID(kImplementationIDSpace, kCopyToObjectStyleGroupCmdImpl, kObjectStylePrefix + 97 )
DECLARE_PMID(kImplementationIDSpace, kObjectStylesXPEffectsScriptProviderImpl, kObjectStylePrefix + 98 )
DECLARE_PMID(kImplementationIDSpace, kClearOverridesWhenApplyStyleImpl,			kObjectStylePrefix + 99)
DECLARE_PMID(kImplementationIDSpace, kObjectStylesScriptProvider60Impl,			kObjectStylePrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kOEObjectStylesAttrsHandlerImpl,			kObjectStylePrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kExportTaggingObjectStylesAttrsHandlerImpl,	kObjectStylePrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kObjectStylesScriptProvider90Impl,			kObjectStylePrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kObjectStyleExportTagScriptProviderImpl,			kObjectStylePrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kObjStylesScriptProvider130Impl,			kObjectStylePrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kContentAwareFitPreferenceDataImpl, kObjectStylePrefix + 106)

// Services
DECLARE_PMID(kServiceIDSpace, kObjectStylesService, kObjectStylePrefix + 1)
DECLARE_PMID(kServiceIDSpace, kObjStylesSelectableDialogService, kObjectStylePrefix + 2)
DECLARE_PMID(kServiceIDSpace, kProcessGfxAttrsObjStylesService, kObjectStylePrefix + 3)

//
//Script Element IDs
//

//Suites
DECLARE_PMID(kScriptInfoIDSpace, kObjectStylesSuiteScriptElement,						kObjectStylePrefix + 1)

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kObjectStylesObjectScriptElement,					kObjectStylePrefix + 10)

//Methods
DECLARE_PMID(kScriptInfoIDSpace, kExportStylesMethodScriptElement,						kObjectStylePrefix + 81)
DECLARE_PMID(kScriptInfoIDSpace, kChangeDefaultMethodScriptElement,					kObjectStylePrefix + 82)
DECLARE_PMID(kScriptInfoIDSpace, kChangeTextDefaultMethodScriptElement,				kObjectStylePrefix + 83)
DECLARE_PMID(kScriptInfoIDSpace, kApplyObjectStyleMethodScriptElement,				kObjectStylePrefix + 84)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kKeyboardShortcutPropertyScriptElement,				kObjectStylePrefix + 120)
DECLARE_PMID(kScriptInfoIDSpace, kDefaultFrameGridObjectStyleScriptElement,				kObjectStylePrefix + 121)
DECLARE_PMID(kScriptInfoIDSpace, kDefaultObjectStyleScriptElement,						kObjectStylePrefix + 122)
DECLARE_PMID(kScriptInfoIDSpace, kTextFrameDefaultObjectStyleScriptElement,				kObjectStylePrefix + 123)
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleFillCategoryPropertyScriptElement,			kObjectStylePrefix + 124)
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleStrokeCategoryPropertyScriptElement,			kObjectStylePrefix + 125)
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleStrokeAndCornerEffectsCategoryPropertyScriptElement,	kObjectStylePrefix + 126)
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleTransparencyCategoryPropertyScriptElement,			kObjectStylePrefix + 127)
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleDropShadowAndFeatherCategoryPropertyScriptElement,	kObjectStylePrefix + 128)
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleParagraphCategoryPropertyScriptElement,				kObjectStylePrefix + 129)
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleTextFrameGeneralCategoryPropertyScriptElement,		kObjectStylePrefix + 130)
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleTextFrameBaselineCategoryPropertyScriptElement,		kObjectStylePrefix + 131)
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleStoryOptionsPropertyScriptElement,					kObjectStylePrefix + 132)
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleTextWrapAndOthersCategoryPropertyScriptElement,		kObjectStylePrefix + 133)
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleAnchoredObjectOptionsCategoryPropertyScriptElement,	kObjectStylePrefix + 134)
DECLARE_PMID(kScriptInfoIDSpace, kAppliedObjectStylePropertyScriptElement,	kObjectStylePrefix + 135)
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleApplyNextParaStylePropertyScriptElement,	kObjectStylePrefix + 136)
DECLARE_PMID(kScriptInfoIDSpace, kAppliedGraphicObjectStylePropertyScriptElement,	kObjectStylePrefix + 137)
DECLARE_PMID(kScriptInfoIDSpace, kAppliedTextObjectStylePropertyScriptElement,	kObjectStylePrefix + 138)
DECLARE_PMID(kScriptInfoIDSpace, kAppliedGridObjectStylePropertyScriptElement,	kObjectStylePrefix + 139)
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleStrokeAndCornerOptionsCategoryPropertyScriptElement,	kObjectStylePrefix + 140)

// Enums
DECLARE_PMID(kScriptInfoIDSpace, kAxisEnumScriptElement,					kObjectStylePrefix + 141)
DECLARE_PMID(kScriptInfoIDSpace, kByScaleEnumScriptElement,					kObjectStylePrefix + 142)

//Style Groups
DECLARE_PMID(kScriptInfoIDSpace, kObjectStyleGroupObjectScriptElement,					kObjectStylePrefix + 143)
DECLARE_PMID(kScriptInfoIDSpace, kAllObjectStylesPropertyScriptElement,					kObjectStylePrefix + 144)
DECLARE_PMID(kScriptInfoIDSpace, kMoveObjectStyleMethodScriptElement,					kObjectStylePrefix + 145)
DECLARE_PMID(kScriptInfoIDSpace, kDeleteObjectStyleGroupMethodScriptElement,				kObjectStylePrefix + 146)

//new XP categories
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleXPPageItemSettingsCategoryObjectScriptElement,		kObjectStylePrefix + 147)
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleXPStrokeSettingsCategoryObjectScriptElement,			kObjectStylePrefix + 148)
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleXPFillSettingsCategoryObjectScriptElement,			kObjectStylePrefix + 149)
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleXPContentSettingsCategoryObjectScriptElement,			kObjectStylePrefix + 150)
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleXPPageItemSettingsCategoryPropertyScriptElement,		kObjectStylePrefix + 151)
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleXPStrokeSettingsCategoryPropertyScriptElement,		kObjectStylePrefix + 152)
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleXPFillSettingsCategoryPropertyScriptElement,			kObjectStylePrefix + 153)
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleXPContentSettingsCategoryPropertyScriptElement,		kObjectStylePrefix + 154)
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleDropShadowCategoryPropertyScriptElement,				kObjectStylePrefix + 155)
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleVignetteCategoryPropertyScriptElement,				kObjectStylePrefix + 156)
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleInnerShadowCategoryPropertyScriptElement,				kObjectStylePrefix + 157)
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleOuterGlowCategoryPropertyScriptElement,				kObjectStylePrefix + 158)
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleInnerGlowCategoryPropertyScriptElement,				kObjectStylePrefix + 159)
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleBevelEmbossCategoryPropertyScriptElement,				kObjectStylePrefix + 160)
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleSatinCategoryPropertyScriptElement,					kObjectStylePrefix + 161)
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleDirectionalFeatherCategoryPropertyScriptElement,		kObjectStylePrefix + 162)
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleGradientFeatherCategoryPropertyScriptElement,			kObjectStylePrefix + 163)
DECLARE_PMID(kScriptInfoIDSpace, kObjectStyleClearOverridesMethodScriptElement,					kObjectStylePrefix + 164)
DECLARE_PMID(kScriptInfoIDSpace, kClearOverridesWhenApplyingObjectStylePropertyScriptElement,	kObjectStylePrefix + 165)
DECLARE_PMID(kScriptInfoIDSpace, kRootObjectStyleGroupObjectScriptElement,						kObjectStylePrefix + 166)

// New Text frame auto size option
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleTextFrameAutoSizeCategoryPropertyScriptElement,		kObjectStylePrefix + 167)

//New  Custom Layout Type options
DECLARE_PMID(kScriptInfoIDSpace, kCustomLayoutTypeEnumScriptElement,							kObjectStylePrefix + 168)
DECLARE_PMID(kScriptInfoIDSpace, kCustomLayoutTypePropertyScriptElement,						kObjectStylePrefix + 169)
DECLARE_PMID(kScriptInfoIDSpace, kCustomLayoutPropertyScriptElement,							kObjectStylePrefix + 170)

DECLARE_PMID(kScriptInfoIDSpace, kObjStyleExportTaggingCategoryPropertyScriptElement,			kObjectStylePrefix + 171)
DECLARE_PMID(kScriptInfoIDSpace, kCreateObjectStyleExportTagMapMethodScriptElement,				kObjectStylePrefix + 172)
DECLARE_PMID(kScriptInfoIDSpace, kObjectStyleExportTagMapObjectScriptElement,					kObjectStylePrefix + 173)


DECLARE_PMID(kScriptInfoIDSpace, kObjStyleObjectExportAltTextCategoryPropertyScriptElement,			kObjectStylePrefix + 174)
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleObjectExportTaggedPDFCategoryPropertyScriptElement,	    kObjectStylePrefix + 175)
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleObjectExportEPUBCategoryPropertyScriptElement,			kObjectStylePrefix + 176)
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleTextFrameFootnoteOptionsCategoryPropertyScriptElement,	kObjectStylePrefix + 177)
DECLARE_PMID(kScriptInfoIDSpace, kKeyboardShortcutExtendedPropertyScriptElement,					kObjectStylePrefix + 178)
DECLARE_PMID(kScriptInfoIDSpace, kObjStyleTextFrameColumnRuleCategoryPropertyScriptElement,			kObjectStylePrefix + 179)

//GUIDS
// {D7D2C130-D321-11d1-AAA2-00C04FA349C7}
#define kPageItem_CLSID { 0xd7d2c130, 0xd321, 0x11d1, { 0xaa, 0xa2, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {D7D2C131-D321-11d1-AAA2-00C04FA349C7}
#define kPageItems_CLSID { 0xd7d2c131, 0xd321, 0x11d1, { 0xaa, 0xa2, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {7761758B-D3DE-11d1-AAA6-00C04FA349C7}
#define kGroup_CLSID { 0x7761758b, 0xd3de, 0x11d1, { 0xaa, 0xa6, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {EE964062-06C6-11d2-AAC9-00C04FA349C7}
#define kGroups_CLSID { 0xee964062, 0x6c6, 0x11d2, { 0xaa, 0xc9, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {6AE52037-9E4E-442d-ADFC-2D492B4BCBEF}
#define kGraphic_CLSID { 0x6ae52037, 0x9e4e, 0x442d, { 0xad, 0xfc, 0x2d, 0x49, 0x2b, 0x4b, 0xcb, 0xef } }
// {C85A4AB3-9492-4c40-8A7B-F8305706C8B8}
#define kGraphics_CLSID { 0xc85a4ab3, 0x9492, 0x4c40, { 0x8a, 0x7b, 0xf8, 0x30, 0x57, 0x6, 0xc8, 0xb8 } }
// {77617582-D3DE-11d1-AAA6-00C04FA349C7}
#define kImage_CLSID { 0x77617582, 0xd3de, 0x11d1, { 0xaa, 0xa6, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {77617583-D3DE-11d1-AAA6-00C04FA349C7}
#define kImages_CLSID { 0x77617583, 0xd3de, 0x11d1, { 0xaa, 0xa6, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {77617584-D3DE-11d1-AAA6-00C04FA349C7}
#define kEPS_CLSID { 0x77617584, 0xd3de, 0x11d1, { 0xaa, 0xa6, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {77617585-D3DE-11d1-AAA6-00C04FA349C7}
#define kEPSs_CLSID { 0x77617585, 0xd3de, 0x11d1, { 0xaa, 0xa6, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {A2B63906-121F-4ae5-ABB4-8A13B4C18B3C}
#define kWMF_CLSID { 0xa2b63906, 0x121f, 0x4ae5, { 0xab, 0xb4, 0x8a, 0x13, 0xb4, 0xc1, 0x8b, 0x3c } }
// {37AC274D-488D-489e-8E69-94A2168971F7}
#define kWMFs_CLSID { 0x37ac274d, 0x488d, 0x489e, { 0x8e, 0x69, 0x94, 0xa2, 0x16, 0x89, 0x71, 0xf7 } }
// {62E3E8FA-B2EC-41f1-90F2-C5AF3AFBC750}
#define kPICT_CLSID { 0x62e3e8fa, 0xb2ec, 0x41f1, { 0x90, 0xf2, 0xc5, 0xaf, 0x3a, 0xfb, 0xc7, 0x50 } }
// {7D72B638-C127-42a5-B60F-F3CA6EFF9E5F}
#define kPICTs_CLSID { 0x7d72b638, 0xc127, 0x42a5, { 0xb6, 0xf, 0xf3, 0xca, 0x6e, 0xff, 0x9e, 0x5f } }
// {77617586-D3DE-11d1-AAA6-00C04FA349C7}
#define kPDF_CLSID { 0x77617586, 0xd3de, 0x11d1, { 0xaa, 0xa6, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {77617587-D3DE-11d1-AAA6-00C04FA349C7}
#define kPDFs_CLSID { 0x77617587, 0xd3de, 0x11d1, { 0xaa, 0xa6, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {8014E427-849B-4476-BBEC-C14E3B546F80}
#define kObjectStyle_CLSID { 0x8014e427, 0x849b, 0x4476, { 0xbb, 0xec, 0xc1, 0x4e, 0x3b, 0x54, 0x6f, 0x80   } }
// {825602C7-96FB-41f4-8B5D-F51FCDC92413}
#define kObjectStyles_CLSID { 0x825602c7, 0x96fb, 0x41f4, { 0x8b, 0x5d, 0xf5, 0x1f, 0xcd, 0xc9, 0x24, 0x13} }
// {21EC2086-4911-4879-B8DE-A7049C96C769}
#define kFrameFittingOptions_CLSID     { 0x21ec2086, 0x4911, 0x4879, { 0xb8, 0xde, 0xa7, 0x4, 0x9c, 0x96, 0xc7, 0x69 } }
// {84A2FCDA-3906-473f-A9B5-2ECAD5AE68B8}
#define kPageItemDefault_CLSID { 0x84a2fcda, 0x3906, 0x473f, { 0xa9, 0xb5, 0x2e, 0xca, 0xd5, 0xae, 0x68, 0xb8 } }
// {D68B4EC1-1E8D-443b-8B52-0CDB037F8483}
#define kObjectStyleGroup_CLSID { 0xd68b4ec1, 0x1e8d, 0x443b, { 0x8b, 0x52, 0xc, 0xdb, 0x3, 0x7f, 0x84, 0x83 } }
// {53D49BD2-D485-4f57-9259-08609E389AAE}
#define kObjectStyleGroups_CLSID { 0x53d49bd2, 0xd485, 0x4f57, { 0x92, 0x59, 0x8, 0x60, 0x9e, 0x38, 0x9a, 0xae } }
// {A7F95DBB-18A4-44a3-9E0D-2E684B3D6A0C}
#define kTransformMatrix_CLSID { 0xa7f95dbb, 0x18a4, 0x44a3, { 0x9e, 0xd, 0x2e, 0x68, 0x4b, 0x3d, 0x6a, 0xc } }
// {5E39F04A-7FF9-45c9-AD13-65DBE13A460E}
#define kTransformValue_CLSID { 0x5e39f04a, 0x7ff9, 0x45c9, { 0xad, 0x13, 0x65, 0xdb, 0xe1, 0x3a, 0x46, 0xe } }
// {1684D190-8EB4-40d1-AD5D-FA4AA209ACA9}
#define kResizeValue_CLSID { 0x1684d190, 0x8eb4, 0x40d1, { 0xad, 0x5d, 0xfa, 0x4a, 0xa2, 0x9, 0xac, 0xa9 } }
// {E8901C74-4DAB-41b7-8622-29DED5A7EDF0}
#define kTransformMatrices_CLSID { 0xe8901c74, 0x4dab, 0x41b7, { 0x86, 0x22, 0x29, 0xde, 0xd5, 0xa7, 0xed, 0xf0 } }
// {4F016B6D-E5C0-49e3-9BCE-878E56711671}
#define kAlignDistPref_CLSID { 0x4f016b6d, 0xe5c0, 0x49e3, { 0x9b, 0xce, 0x87, 0x8e, 0x56, 0x71, 0x16, 0x71 } }
// {A39D6F3B-52C7-4459-A29C-8EAAD7D8ED0A}
#define kObjStyleXPPageItemSettingsCategory_CLSID { 0xa39d6f3b, 0x52c7, 0x4459, { 0xa2, 0x9c, 0x8e, 0xaa, 0xd7, 0xd8, 0xed, 0xa } }
// {DF03D94D-9CC2-4248-8503-EE8AACCAA3C8}
#define kObjStyleXPStrokeSettingsCategory_CLSID { 0xdf03d94d, 0x9cc2, 0x4248, { 0x85, 0x3, 0xee, 0x8a, 0xac, 0xca, 0xa3, 0xc8 } }
// {CABD713E-5D70-4a32-B94A-EAD956BC758B}
#define kObjStyleXPFillSettingsCategory_CLSID { 0xcabd713e, 0x5d70, 0x4a32, { 0xb9, 0x4a, 0xea, 0xd9, 0x56, 0xbc, 0x75, 0x8b } }
// {26037992-69DF-42e2-A7B2-E28AB15A81D9}
#define kObjStyleXPContentSettingsCategory_CLSID { 0x26037992, 0x69df, 0x42e2, { 0xa7, 0xb2, 0xe2, 0x8a, 0xb1, 0x5a, 0x81, 0xd9 } }
// {FF9A3CFD-C8A6-4dee-9802-D87C716756F8}
#define kRootObjectStyleGroup_CLSID { 0xff9a3cfd, 0xc8a6, 0x4dee, { 0x98, 0x2, 0xd8, 0x7c, 0x71, 0x67, 0x56, 0xf8 } }
// {76BA337C-A2B9-4daa-935D-4E7B1C3E329C}
#define kObjectExportOptions_CLSID { 0x76ba337c, 0xa2b9, 0x4daa, { 0x93, 0x5d, 0x4e, 0x7b, 0x1c, 0x3e, 0x32, 0x9c } }
// {B41C6E16-E7B6-4D68-BAC1-38292E7AF712}
#define kObjectStyleExportTagMap_CLSID { 0xb41c6e16, 0xe7b6, 0x4d68, { 0xba, 0xc1, 0x38, 0x29, 0x2e, 0x7a, 0xf7, 0x12 } }
// {BB98DEF5-A07E-4E96-B545-7FEFFB29640F}
#define kObjectStyleExportTagMaps_CLSID  { 0xbb98def5, 0xa07e, 0x4e96, { 0xb5, 0x45, 0x7f, 0xef, 0xfb, 0x29, 0x64, 0xf } }
// {DF7AB3F9-1449-4B73-B813-5742028C69DB}
#define kObjectStyleLayoutAttrOptions_CLSID { 0xdf7ab3f9, 0x1449, 0x4b73 {0xb8, 0x13, 0x57, 0x42, 0x2, 0x8c, 0x69, 0xdb } }


enum GenericScriptIDs
{
	c_PageItem					= 'pitm',
	c_PageItems					= 'pits',
	c_Graphic					= 'Grfc',
	c_Graphics					= 'Grfs',
	c_Image						= 'imag',
	c_Images					= 'imgs',
	c_WMF						= 'WMF ',
	c_WMFs						= 'WMFs',
	c_PICT						= 'PICT',
	c_PICTs						= 'PICs',
	c_ObjectExportOptions		= 'ObEx',

	e_BeforeNodeRemoved			= 'bfNR',
	e_AfterNodeInserted			= 'afNI',
	e_BeforeNodeRemovedFromDocument = 'bNRD',
	e_AfterNodeInsertedIntoDocument = 'aNID',
	e_BeforeGeometryChanged		= 'bfGC',
	e_AfterGeometryChanged		= 'afGC',
	e_BeforeTransformChanged	= 'bfTC',
	e_AfterTransformChanged		= 'afTC',
	e_AfterLabelChanged			= 'afLC',
	e_AfterTextWrapChanged		= 'afTW',
	e_AlternateText				= 'alTx',
	e_ActualText				= 'acTx',

	p_ParentPage				= 'PaPa',
	p_ObjectExportOptionsProperty		= 'oExP',
	p_AltTextSourceType			= 'alSP',
	p_ActualTextSourceType		= 'acSP',
	p_CustomAltText				= 'alCt',
	p_CustomActualText			= 'acCt',
	p_AltMetadataProperty		= 'alMp',
	p_ActualMetadataProperty	= 'acMp',
	p_CustomImageConversion		= 'CIcv',
	p_UseOriginalImage			= 'Uoim',
	p_ApplyTagType				= 'Aptt',
	p_ImageConversionType		= 'ICvt',
	p_ImageSizeOption			= 'pISz',
	p_ImageResolution			= 'ImRs',
	p_CustomImageAlignment		= 'CIma',
	p_CustomLayout				= 'CuLy',
	p_CustomLayoutType			= 'CLaT',
	p_CustomWidthType			= 'CWiT',
	p_CustomHeightType			= 'CHeT',
	p_CustomSizeType			= 'CSsT',
	p_EditBoxCustomSize			= 'EbCu',
	p_ImageAlignment			= 'ImAl',
	p_ImageSpaceBefore			= 'ImSB',
	p_EditBoxCustomWidth		= 'OcWi',
	//p_EditBoxCustomWidthUnit	= 'ObCu',
	p_EditBoxCustomHeight		= 'OcHe',
	//p_EditBoxCustomHeightUnit	= 'ObCh',
	p_ImageSpaceAfter			= 'ImSA',
	p_SpaceUnit					= 'SpUn',
	p_UseImagePageBreak			= 'Uipb',
	p_ImagePageBreak			= 'ImPk',
	p_EpubType					= 'EpTy',
	p_UseExistingImage			= 'Ueim',
	p_PreserveObjectLayoutAppearance		= 'PoLa',

	en_SourceType				= 'sTyp',
	en_SourceCustom				= 'sTCm',
	en_SourceXMPTitle			= 'sTXt',
	en_SourceXMPDescription		= 'sTXd',
	en_SourceXMPHeadline		= 'sTXh',
	en_SourceXMPOther			= 'sTXo',
	en_SourceXMLStructure		= 'sTXs',
	en_TagType					= 'tgTp',
	en_TagFromStructure			= 'tgSe',
	en_TagArtifact				= 'tgAf',
	en_TagBasedOnObject			= 'tgBo',
	en_ImageConversionType		= 'iCvt',
	en_ImageSizeOption			= 'ImSz',
	en_RelativeToPageWidth		= 'RvPw',
	en_RelativeSizeToTextFlow	= 'RsTT',
	en_RelativeToTextFlow	    = 'RvTf',
	en_RelativeToTextSize		= 'RvTs',
	en_ImageSizeResolution		= 'Imrs',
	en_72						= 'rsSt',
	en_96						= 'rsNs',
	en_150						= 'rs0f',
	en_300						= 'rsTh',
	en_ObjectImageAlignment		= 'ImAn',
	en_AlignLeft				= 'AlLf',
	en_AlignCenter				= 'AlCr',
	en_AlignRight				= 'AlRt',
	en_CSSUnit					= 'CsUn',
	en_CSSEm					= 'SpEm',
	en_CSSPixel					= 'SpPx',
	en_ImagePageBreak			= 'ImPb',
	en_CustomLayoutType			= 'CuLT',

	en_CustomWidthType			= 'CuWT',
	en_CustomHeightType			= 'CuHT',
	en_CustomSizeType			= 'CuSi',
	en_BreakBefore				= 'Brbf',
	en_BreakAfter				= 'Braf',
	en_BreakBeforeAndAfter		= 'Brba',
	en_NoneSize					= 'NonS',
	en_DefaultSize				= 'DeSi',
	en_RelativeSize				= 'RelS',
	en_FixedOptionSize			= 'FixS',
	en_FixedSize				= 'Fxdz',
	en_NoneWidth				= 'NWid',
	en_DefaultWidth				= 'DWid',
	en_RelativeWidth			= 'RelW',
	en_FixedWidth				= 'FixW',
	en_CustomWidth				= 'CVWi',
	en_NoneHeight				= 'NHei',
	en_DefaultHeight			= 'DefH',
	en_FixedHeight				= 'FHei',
	en_CustomHeight				= 'CuVH',
	en_UseCustomWidth			= 'UCWi',
	en_UseCustomHeight			= 'UCHe',
	en_AlignmentAndSpacing		= 'AlSp',
	en_FloatLeft				= 'FlLe',
	en_FloatRight				= 'FlRi',

	en_PreserveObjectLayoutAppearance = 'PrAp',
	en_DefaultAppearance		= 'PrDe',
	en_UseExisting				= 'PrUe',
	en_RasterizeContainer		= 'PrRr',
	en_RasterizeContent			= 'PrRt',
	e_ConvertToRawText =  'CtRt',
} ;

// User Action Categories
DECLARE_PMID(kUserActionCategoryIDSpace, kTransformCategory, kGenericIDPrefix + 1)
DECLARE_PMID(kUserActionCategoryIDSpace, kArrangeCategory, kGenericIDPrefix + 2)
DECLARE_PMID(kUserActionCategoryIDSpace, kGroupCategory, kGenericIDPrefix + 3)
DECLARE_PMID(kUserActionCategoryIDSpace, kLockCategory, kGenericIDPrefix + 4)
DECLARE_PMID(kUserActionCategoryIDSpace, kFrameContentCategory, kGenericIDPrefix + 5)


// Default styles names
#define kNoObjectStyleName "[None]"
#define kDefaultObjectStyleForAGraphicFrameName "[Normal Graphics Frame]"
#define kDefaultObjectStyleForATextFrameName "[Normal Text Frame]"
#define kDefaultObjectStyleForAFrameGridName "[Normal Grid]"

#endif // __GenericID__

