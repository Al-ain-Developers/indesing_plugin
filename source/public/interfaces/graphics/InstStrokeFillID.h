//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/InstStrokeFillID.h $
//  
//  Owner: Jeff Argast
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

#ifndef __InstStrokeFillID__
#define __InstStrokeFillID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kInstStrokeFillID	RezLong(0x5a00)


// <Start IDC>
// PluginID
#define kInstStrokeFillPluginName 		"Stroke and Fill"
DECLARE_PMID(kPlugInIDSpace, kInstStrokeFillPluginID, kInstStrokeFillID + 1)

// <Class ID>
//
// ClassIDs
//

// Arrow Heads
DECLARE_PMID(kClassIDSpace, kArrowHeadServiceBoss, kInstStrokeFillID + 1)
DECLARE_PMID(kClassIDSpace, kArrowHeadAttrBoss, kInstStrokeFillID + 2)
DECLARE_PMID(kClassIDSpace, kSimpleArrowHeadBoss, kInstStrokeFillID + 3)
DECLARE_PMID(kClassIDSpace, kSimpleWideArrowHeadBoss, kInstStrokeFillID + 4)
DECLARE_PMID(kClassIDSpace, kTriangleArrowHeadBoss, kInstStrokeFillID + 5)
DECLARE_PMID(kClassIDSpace, kTriangleWideArrowHeadBoss, kInstStrokeFillID + 6)
DECLARE_PMID(kClassIDSpace, kBarbedArrowHeadBoss, kInstStrokeFillID + 7)
DECLARE_PMID(kClassIDSpace, kCurvedArrowHeadBoss, kInstStrokeFillID + 8)
DECLARE_PMID(kClassIDSpace, kCircleArrowHeadBoss, kInstStrokeFillID + 9)
DECLARE_PMID(kClassIDSpace, kCircleSolidArrowHeadBoss, kInstStrokeFillID + 10)
DECLARE_PMID(kClassIDSpace, kSquareArrowHeadBoss, kInstStrokeFillID + 11)
DECLARE_PMID(kClassIDSpace, kSquareSolidArrowHeadBoss, kInstStrokeFillID + 12)
DECLARE_PMID(kClassIDSpace, kBarArrowHeadBoss, kInstStrokeFillID + 13)

// Corners
DECLARE_PMID(kClassIDSpace, kCornerServiceBoss, kInstStrokeFillID + 20)
DECLARE_PMID(kClassIDSpace, kRoundedCornerBoss, kInstStrokeFillID + 21)
DECLARE_PMID(kClassIDSpace, kInverseRoundedCornerBoss, kInstStrokeFillID + 22)
DECLARE_PMID(kClassIDSpace, kInsetCornerBoss, kInstStrokeFillID + 23)
DECLARE_PMID(kClassIDSpace, kBevelCornerBoss, kInstStrokeFillID + 24)
DECLARE_PMID(kClassIDSpace, kFancyCornerBoss, kInstStrokeFillID + 25)

// Path Strokers
DECLARE_PMID(kClassIDSpace, kSolidPathStrokerBoss, kInstStrokeFillID + 41)
DECLARE_PMID(kClassIDSpace, kDashedPathStrokerBoss, kInstStrokeFillID + 42)

// String registration boss
//gap

DECLARE_PMID(kClassIDSpace, kDashedEditBoxBoss, kInstStrokeFillID + 52)

DECLARE_PMID(kClassIDSpace, kDashedAttributeValuesBoss, kInstStrokeFillID + 53)

// Document conversion
DECLARE_PMID(kClassIDSpace, kInstStrokeFillConversionBoss, kInstStrokeFillID + 54)

// Canned path strokers
DECLARE_PMID(kClassIDSpace, kCannedDash4x4PathStrokerBoss, kInstStrokeFillID + 55)
DECLARE_PMID(kClassIDSpace, kCannedDash3x2PathStrokerBoss, kInstStrokeFillID + 56)
DECLARE_PMID(kClassIDSpace, kCannedDotPathStrokerBoss, kInstStrokeFillID + 57)

DECLARE_PMID(kClassIDSpace,	kSingleWavyPathStrokerBoss,kInstStrokeFillID + 58)
DECLARE_PMID(kClassIDSpace,	kStraightHashPathStrokerBoss,kInstStrokeFillID + 59)
DECLARE_PMID(kClassIDSpace,	kRightSlantHashPathStrokerBoss,kInstStrokeFillID + 60)
DECLARE_PMID(kClassIDSpace,	kLeftSlantHashPathStrokerBoss,kInstStrokeFillID + 61)
DECLARE_PMID(kClassIDSpace, kWhiteDiamondPathStrokerBoss,kInstStrokeFillID + 62)
DECLARE_PMID(kClassIDSpace, 	kJapaneseDotsPathStrokerBoss,kInstStrokeFillID + 63)
//gap
DECLARE_PMID(kClassIDSpace, kCustomPathStrokerBoss, kInstStrokeFillID + 66)
DECLARE_PMID(kClassIDSpace, kCustomDashedPathStrokerBoss, kInstStrokeFillID + 67)
DECLARE_PMID(kClassIDSpace, kAddCustomLineStyleCmdBoss, kInstStrokeFillID + 68)
DECLARE_PMID(kClassIDSpace, kDeleteCustomLineStyleCmdBoss, kInstStrokeFillID + 69)
DECLARE_PMID(kClassIDSpace, kDashedPathStrokerMetadataBoss, kInstStrokeFillID + 70)
DECLARE_PMID(kClassIDSpace, kSetDashedAttrCommandBoss, kInstStrokeFillID + 71)
DECLARE_PMID(kClassIDSpace, kInstStrokeFillNewDocResponderBoss, kInstStrokeFillID + 72)
DECLARE_PMID(kClassIDSpace, kSetCustomLineStyleNameCmdBoss, kInstStrokeFillID + 73)
DECLARE_PMID(kClassIDSpace, kCustomPathStrokerRefConverterBoss, kInstStrokeFillID + 74)
// gap
DECLARE_PMID(kClassIDSpace, kNewCustomDashStyleCmdBoss, kInstStrokeFillID + 83)
// gap
DECLARE_PMID(kClassIDSpace, kRemoveCustomLineStyleCmdBoss, kInstStrokeFillID + 88)
// gap
DECLARE_PMID(kClassIDSpace, kCustomDottedPathStrokerBoss, kInstStrokeFillID + 92)
DECLARE_PMID(kClassIDSpace, kDottedPathStrokerMetadataBoss, kInstStrokeFillID + 93)
// gap
DECLARE_PMID(kClassIDSpace, kStrokeStyleExportRootBoss, kInstStrokeFillID + 99)
DECLARE_PMID(kClassIDSpace, kStrokeStyleManagerListBoxBoss, kInstStrokeFillID + 100)
DECLARE_PMID(kClassIDSpace, kStrokeStyleScriptProviderBoss, kInstStrokeFillID + 101)
DECLARE_PMID(kClassIDSpace, kStrokeStyleScriptObjectBoss, kInstStrokeFillID + 102)
DECLARE_PMID(kClassIDSpace, kImportLineStylesCmdBoss, kInstStrokeFillID + 103)


// Available								kInstStrokeFillID + 104

// <Interface ID>
//
// IIDs
//
DECLARE_PMID(kInterfaceIDSpace, IID_IDASHEDEDITBOXOBSERVER, kInstStrokeFillID + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IDASHEDATTRIBUTEVALUES, kInstStrokeFillID + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICSUTILS, kInstStrokeFillID + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IPATHSTROKERUTILS, kInstStrokeFillID + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IPATHSTROKERLIST, kInstStrokeFillID + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMPATHSTROKERDATA, kInstStrokeFillID + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IPATHSTROKERMETADATA, kInstStrokeFillID + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IPATHSTROKEROVERRIDES, kInstStrokeFillID + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_ICUSTOMDASHEDPATHSTROKERVALUES, kInstStrokeFillID + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IDASHEDSTROKESLIDERCONTROLDATA, kInstStrokeFillID + 10)
// gap
DECLARE_PMID(kInterfaceIDSpace, IID_IPATHGEOMETRYUTILS, kInstStrokeFillID + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IPATHSTROKERFILLPATHOVERRIDE, kInstStrokeFillID + 15)

// Available								kInstStrokeFillID + 16

// <Implementation ID>
//
// ImplementationIIDs
//


// Arrow Heads
DECLARE_PMID(kImplementationIDSpace, kArrowHeadService, kInstStrokeFillID + 1)
DECLARE_PMID(kImplementationIDSpace, kArrowHeadAttr, kInstStrokeFillID + 2)
DECLARE_PMID(kImplementationIDSpace, kSimpleArrowHead, kInstStrokeFillID + 3)
DECLARE_PMID(kImplementationIDSpace, kSimpleWideArrowHead, kInstStrokeFillID + 4)
DECLARE_PMID(kImplementationIDSpace, kTriangleArrowHead, kInstStrokeFillID + 5)
DECLARE_PMID(kImplementationIDSpace, kTriangleWideArrowHead, kInstStrokeFillID + 6)
DECLARE_PMID(kImplementationIDSpace, kBarbedArrowHead, kInstStrokeFillID + 7)
DECLARE_PMID(kImplementationIDSpace, kCurvedArrowHead, kInstStrokeFillID + 8)
DECLARE_PMID(kImplementationIDSpace, kCircleArrowHead, kInstStrokeFillID + 9)
DECLARE_PMID(kImplementationIDSpace, kCircleSolidArrowHead, kInstStrokeFillID + 10)
DECLARE_PMID(kImplementationIDSpace, kSquareArrowHead, kInstStrokeFillID + 11)
DECLARE_PMID(kImplementationIDSpace, kSquareSolidArrowHead, kInstStrokeFillID + 12)
DECLARE_PMID(kImplementationIDSpace, kBarArrowHead, kInstStrokeFillID + 13)

// Corners
DECLARE_PMID(kImplementationIDSpace, kCornerService, kInstStrokeFillID + 20)
DECLARE_PMID(kImplementationIDSpace, kRoundedCorner, kInstStrokeFillID + 22)
DECLARE_PMID(kImplementationIDSpace, kInverseRoundedCorner, kInstStrokeFillID + 23)
DECLARE_PMID(kImplementationIDSpace, kInsetCorner, kInstStrokeFillID + 24)
DECLARE_PMID(kImplementationIDSpace, kBevelCorner, kInstStrokeFillID + 25)
DECLARE_PMID(kImplementationIDSpace, kFancyCorner, kInstStrokeFillID + 26)

// Path Strokers
DECLARE_PMID(kImplementationIDSpace, kSolidPathStroker, kInstStrokeFillID + 41)
DECLARE_PMID(kImplementationIDSpace, kDashedPathStrokerImpl, kInstStrokeFillID + 42)
DECLARE_PMID(kImplementationIDSpace, kStrokeTypeAttributePrePostImpl, kInstStrokeFillID + 43)

// String registration
//gap

// Dashed panel things
DECLARE_PMID(kImplementationIDSpace, kDashedGfxStateObserverImpl, kInstStrokeFillID + 51)
DECLARE_PMID(kImplementationIDSpace, kDashedEditBoxObserverImpl, kInstStrokeFillID + 52)
DECLARE_PMID(kImplementationIDSpace, kDashedPanelViewImpl, kInstStrokeFillID + 53)

// Dashed attribute impl
DECLARE_PMID(kImplementationIDSpace, kDashedAttributeValuesImpl, kInstStrokeFillID + 54)

// Document conversion
DECLARE_PMID(kImplementationIDSpace, kInstStrokeFillConversionImpl, kInstStrokeFillID + 55)

DECLARE_PMID(kImplementationIDSpace, kCannedDash4x4PathStrokerImpl, kInstStrokeFillID + 56)
DECLARE_PMID(kImplementationIDSpace, kCannedDash3x2PathStrokerImpl, kInstStrokeFillID + 57)
DECLARE_PMID(kImplementationIDSpace, kCannedDotPathStrokerImpl, kInstStrokeFillID + 58)
DECLARE_PMID(kImplementationIDSpace, kGraphicsUtilsImpl, kInstStrokeFillID + 59)

DECLARE_PMID(kImplementationIDSpace,	kWhiteDiamondPathStrokerImpl, kInstStrokeFillID + 60)
DECLARE_PMID(kImplementationIDSpace,	kJapaneseDotsPathStrokerImpl, kInstStrokeFillID + 61)
DECLARE_PMID(kImplementationIDSpace,	kStraightHashPathStrokerImpl, kInstStrokeFillID + 62)
DECLARE_PMID(kImplementationIDSpace, kRightSlantHashPathStrokerImpl, kInstStrokeFillID + 63)
DECLARE_PMID(kImplementationIDSpace,	 kLeftSlantHashPathStrokerImpl, kInstStrokeFillID + 64)
//DECLARE_PMID(kImplementationIDSpace,	 kTallRightSlantHashPathStrokerImpl, kInstStrokeFillID + 65) unused
DECLARE_PMID(kImplementationIDSpace, kSingleWavyPathStrokerImpl, kInstStrokeFillID + 66)

DECLARE_PMID(kImplementationIDSpace, kPathStrokerUtilsImpl, kInstStrokeFillID + 67)
DECLARE_PMID(kImplementationIDSpace, kPathStrokerListImpl, kInstStrokeFillID + 68)
// gap
DECLARE_PMID(kImplementationIDSpace, kCustomPathStrokerImpl, kInstStrokeFillID + 70)
DECLARE_PMID(kImplementationIDSpace, kCustomDashedPathStrokerImpl, kInstStrokeFillID + 71)
DECLARE_PMID(kImplementationIDSpace, kCustomDashedPathStrokerDataImpl, kInstStrokeFillID + 72)
DECLARE_PMID(kImplementationIDSpace, kAddCustomLineStyleCmdImpl, kInstStrokeFillID + 73)
DECLARE_PMID(kImplementationIDSpace, kDeleteCustomLineStyleCmdImpl, kInstStrokeFillID + 74)
DECLARE_PMID(kImplementationIDSpace, kDashedPathStrokerMetadataImpl, kInstStrokeFillID + 75)
DECLARE_PMID(kImplementationIDSpace, kSetDashedAttrCommandImpl, kInstStrokeFillID + 76)
DECLARE_PMID(kImplementationIDSpace, kNPCustomDashedPathStrokerValuesImpl, kInstStrokeFillID + 77)	// Non-persistant, for command data
DECLARE_PMID(kImplementationIDSpace, kPathStrokerMetadataServiceProviderImpl, kInstStrokeFillID + 78)
DECLARE_PMID(kImplementationIDSpace, kCustomDashedPathStrokerValuesImpl, kInstStrokeFillID + 79)
DECLARE_PMID(kImplementationIDSpace, kInstStrokeFillNewDocResponderImpl, kInstStrokeFillID + 80)
DECLARE_PMID(kImplementationIDSpace, kSetCustomLineStyleNameCmdImpl, kInstStrokeFillID + 81)
DECLARE_PMID(kImplementationIDSpace, kDottedPathStrokerOverridesImpl, kInstStrokeFillID + 82)
DECLARE_PMID(kImplementationIDSpace, kCustomDashedPathStrokerOverridesImpl, kInstStrokeFillID + 83)
DECLARE_PMID(kImplementationIDSpace, kCustomPathStrokerRefConverterImpl, kInstStrokeFillID + 84)
// gap
DECLARE_PMID(kImplementationIDSpace, kNewCustomDashStyleCmdImpl, kInstStrokeFillID + 96)
// gap
//DECLARE_PMID(kImplementationIDSpace, kPathStrokerViewImpl_obsolete, kInstStrokeFillID + 100)
// gap
DECLARE_PMID(kImplementationIDSpace, kRemoveCustomLineStyleCmdImpl, kInstStrokeFillID + 102)
// gap
DECLARE_PMID(kImplementationIDSpace, kCustomDottedPathStrokerImpl, kInstStrokeFillID + 106)
DECLARE_PMID(kImplementationIDSpace, kCustomDottedPathStrokerDataImpl, kInstStrokeFillID + 107)
DECLARE_PMID(kImplementationIDSpace, kDottedPathStrokerMetadataImpl, kInstStrokeFillID + 108)
// gap
DECLARE_PMID(kImplementationIDSpace, kExportPathStrokerListImpl, kInstStrokeFillID + 116)
// gap
DECLARE_PMID(kImplementationIDSpace, kPathGeometryUtilsImpl, kInstStrokeFillID + 119)
DECLARE_PMID(kImplementationIDSpace, kStrokeStyleScriptProviderImpl, kInstStrokeFillID + 120)
DECLARE_PMID(kImplementationIDSpace, kStrokeStyleScriptImpl, kInstStrokeFillID + 121)
DECLARE_PMID(kImplementationIDSpace, kBuiltinStrokeStyleScriptImpl, kInstStrokeFillID + 122)
// gap
DECLARE_PMID(kImplementationIDSpace, kButtOnlyOverridesImpl, kInstStrokeFillID + 125)
DECLARE_PMID(kImplementationIDSpace, kSolidFillPathOverrideImpl, kInstStrokeFillID + 126)

DECLARE_PMID(kImplementationIDSpace, kImportLineStylesCmdImpl, kInstStrokeFillID + 127)
//DECLARE_PMID(kImplementationIDSpace, kExportLineStylesCmdImpl, kInstStrokeFillID + 128)


// Available							kInstStrokeFillID + 126

//
// <Service ID>
//
DECLARE_PMID(kServiceIDSpace, kPathStrokerMetaData, kInstStrokeFillID + 1)

//
// <Action ID>
//
DECLARE_PMID(kActionIDSpace, kLineStylesActionID, kInstStrokeFillID + 1)
DECLARE_PMID(kActionIDSpace, kStrokePanelSepActionID, kInstStrokeFillID + 2)

//
// <Script Info ID>
//

// Suites
DECLARE_PMID(kScriptInfoIDSpace, kStrokeStyleSuiteScriptElement, kInstStrokeFillID + 1)

// Objects
DECLARE_PMID(kScriptInfoIDSpace, kStrokeStyleObjectScriptElement, kInstStrokeFillID + 10)
DECLARE_PMID(kScriptInfoIDSpace, kDashStrokeStyleObjectScriptElement, kInstStrokeFillID + 11)
DECLARE_PMID(kScriptInfoIDSpace, kDotStrokeStyleObjectScriptElement, kInstStrokeFillID + 12)
DECLARE_PMID(kScriptInfoIDSpace, kStripeStrokeStyleObjectScriptElement, kInstStrokeFillID + 13)

// Events
DECLARE_PMID(kScriptInfoIDSpace, kDeleteStrokeStyleMethodScriptElement, kInstStrokeFillID + 33)

// Properties
DECLARE_PMID(kScriptInfoIDSpace, kStrokeStyleTypePropScriptElement, kInstStrokeFillID + 50)
DECLARE_PMID(kScriptInfoIDSpace, kStrokeStyleDashArrayPropScriptElement, kInstStrokeFillID + 51)
DECLARE_PMID(kScriptInfoIDSpace, kStrokeStyleDotArrayPropScriptElement, kInstStrokeFillID + 52)
DECLARE_PMID(kScriptInfoIDSpace, kStrokeStyleStripeArrayPropScriptElement, kInstStrokeFillID + 53)

// Enums


//GUIDS
// {B36EB9CA-8E4B-4a1c-B81A-E8FAE5C6AE65}
#define kStrokeStyle_CLSID { 0xb36eb9ca, 0x8e4b, 0x4a1c, { 0xb8, 0x1a, 0xe8, 0xfa, 0xe5, 0xc6, 0xae, 0x65 } }
// {C7389C0F-88CA-4f14-9F2B-DE5D00EE1AD8}
#define kStrokeStyles_CLSID { 0xc7389c0f, 0x88ca, 0x4f14, { 0x9f, 0x2b, 0xde, 0x5d, 0x0, 0xee, 0x1a, 0xd8 } }
// {B5C62A60-8A8C-4603-8FD4-C926B4AB418B}
#define kDashStrokeStyle_CLSID { 0xb5c62a60, 0x8a8c, 0x4603, { 0x8f, 0xd4, 0xc9, 0x26, 0xb4, 0xab, 0x41, 0x8b } }
// {112329E6-AE7F-414f-A2D5-8FACCDE89D8F}
#define kDashStrokeStyles_CLSID { 0x112329e6, 0xae7f, 0x414f, { 0xa2, 0xd5, 0x8f, 0xac, 0xcd, 0xe8, 0x9d, 0x8f } }
// {06C0694C-901E-4b78-9AE7-D936C3D7E021}
#define kDotStrokeStyle_CLSID { 0x6c0694c, 0x901e, 0x4b78, { 0x9a, 0xe7, 0xd9, 0x36, 0xc3, 0xd7, 0xe0, 0x21 } }
// {932B0085-3F0E-4803-B1A1-F1FD8193CB2E}
#define kDotStrokeStyles_CLSID { 0x932b0085, 0x3f0e, 0x4803, { 0xb1, 0xa1, 0xf1, 0xfd, 0x81, 0x93, 0xcb, 0x2e } }
// {17D90403-74CA-4252-9D90-6B16F51F7B8A}
#define kStripeStrokeStyle_CLSID { 0x17d90403, 0x74ca, 0x4252, { 0x9d, 0x90, 0x6b, 0x16, 0xf5, 0x1f, 0x7b, 0x8a } }
// {A33CD91E-4EDE-4886-8762-FE2AA010947A}
#define kStripeStrokeStyles_CLSID { 0xa33cd91e, 0x4ede, 0x4886, { 0x87, 0x62, 0xfe, 0x2a, 0xa0, 0x10, 0x94, 0x7a } }

#endif // __InstStrokeFillID__
