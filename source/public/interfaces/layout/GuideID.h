//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/GuideID.h $
//  
//  Owner: Stacy Molitor
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
//  Contains IDs used by the guide item plug-in
//  
//========================================================================================

#ifndef __GuideID__
#define __GuideID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"
#include "FormatNumber.h"

#define kGuidePrefix	 RezLong(0x3300)

// PluginID
#define kGuidePluginName			"Guides"
DECLARE_PMID(kPlugInIDSpace, kGuidePluginID, kGuidePrefix + 1)

// ClassIDs
DECLARE_PMID(kClassIDSpace, kGuideItemBoss, kGuidePrefix + 1)
DECLARE_PMID(kClassIDSpace, kNewGuideCmdBoss, kGuidePrefix + 3)
DECLARE_PMID(kClassIDSpace, kMoveGuideRelativeCmdBoss, kGuidePrefix + 4)
DECLARE_PMID(kClassIDSpace, kMoveGuideAbsoluteCmdBoss, kGuidePrefix + 5)
DECLARE_PMID(kClassIDSpace, kSetGuideViewThresholdCmdBoss, kGuidePrefix + 9)
DECLARE_PMID(kClassIDSpace, kGuideZoomFactorObserverBoss, kGuidePrefix + 11)
DECLARE_PMID(kClassIDSpace, kChangeGuideColorCmdBoss, kGuidePrefix + 12)
DECLARE_PMID(kClassIDSpace, kSetGuidesBackCmdBoss, kGuidePrefix + 13)
//gap
DECLARE_PMID(kClassIDSpace, kSetGuideOrientationCmdBoss, kGuidePrefix + 20)
DECLARE_PMID(kClassIDSpace, kSetGuideFitToPageCmdBoss, kGuidePrefix + 21)
DECLARE_PMID(kClassIDSpace, kSetGuideTypeCmdBoss, kGuidePrefix + 22)
DECLARE_PMID(kClassIDSpace, kSetGuideGrowZoneCmdBoss, kGuidePrefix + 23)
//gap
DECLARE_PMID(kClassIDSpace, kGuideConversionProviderBoss, kGuidePrefix + 24)
DECLARE_PMID(kClassIDSpace, kGuideCodeConversionProviderBoss, kGuidePrefix + 25)
DECLARE_PMID(kClassIDSpace, kGuideDataPhase2ConversionResponderBoss, kGuidePrefix + 26)
DECLARE_PMID(kClassIDSpace, kGuideScriptProviderBoss, kGuidePrefix + 27)
DECLARE_PMID(kClassIDSpace, kMultiGuideScriptProviderBoss, kGuidePrefix + 28)

// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IGUIDEDATA, kGuidePrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_INEWGUIDECMDDATA, kGuidePrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IGUIDEFACADE, kGuidePrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IMYPMPOINTDATA, kGuidePrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IMYINTDATA, kGuidePrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IGUIDEMOVEDISTANCE, kGuidePrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IGUIDEUTILS, kGuidePrefix + 9)

// Implementation IIDs
DECLARE_PMID(kImplementationIDSpace, kGuideShapeImpl, kGuidePrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kGuideFacadeImpl, kGuidePrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kControlPointsGuideImpl, kGuidePrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kGuideTransformImpl, kGuidePrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kGeometryGuideImpl, kGuidePrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kGuideDataImpl, kGuidePrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kNewGuideCmdImpl, kGuidePrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kNewGuideCmdDataImpl, kGuidePrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kMoveGuideRelativeCmdImpl, kGuidePrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kMoveGuideAbsoluteCmdImpl, kGuidePrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kGuideItemScrapImpl, kGuidePrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kGuideHandleShapeImpl, kGuidePrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kChangeGuideColorCmdImpl, kGuidePrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kSetGuideViewThresholdCmdImpl, kGuidePrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kSetGuidesBackCmdImpl, kGuidePrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kGuideStartMoveDataImpl, kGuidePrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kMultiGuideScriptProviderImpl, kGuidePrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kSetGuideTypeCmdImpl, kGuidePrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kSetGuideGrowZoneCmdImpl, kGuidePrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kGuideMoveDistanceDataImpl, kGuidePrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kSetGuideOrientationCmdImpl, kGuidePrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kSetGuideFitToPageCmdImpl, kGuidePrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kGuideVisitorHelperImpl, kGuidePrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kGuideColorInkResourcesImpl, kGuidePrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kGuideCodeConversionProviderImpl, kGuidePrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kGuideDataPhase2ConversionImpl, kGuidePrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kGuideScriptProviderImpl, kGuidePrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kGuideScriptImpl, kGuidePrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kGuideUtilsImpl, kGuidePrefix + 40)

// Widget IDs

// Action IDs

//
//Script Element IDs
//

//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kGuideObjectScriptElement, kGuidePrefix + 5)

//Events
DECLARE_PMID(kScriptInfoIDSpace, kCreateGuideMethodScriptElement, kGuidePrefix + 10)
DECLARE_PMID(kScriptInfoIDSpace, kCreateGuidesMethodScriptElement, kGuidePrefix + 11)
DECLARE_PMID(kScriptInfoIDSpace, kMoveGuideMethodScriptElement, kGuidePrefix + 12)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kGuideColorPropertyScriptElement, kGuidePrefix + 50)
DECLARE_PMID(kScriptInfoIDSpace, kGuideOrientationPropertyScriptElement, kGuidePrefix + 51)
DECLARE_PMID(kScriptInfoIDSpace, kGuideLocationPropertyScriptElement, kGuidePrefix + 52)
DECLARE_PMID(kScriptInfoIDSpace, kGuideFitToPagePropertyScriptElement, kGuidePrefix + 53)
DECLARE_PMID(kScriptInfoIDSpace, kGuideViewThresholdPropertyScriptElement, kGuidePrefix + 54)
DECLARE_PMID(kScriptInfoIDSpace, kGuidePageIndexPropertyScriptElement, kGuidePrefix + 55)
DECLARE_PMID(kScriptInfoIDSpace, kGuideTypePropertyScriptElement, kGuidePrefix + 56)
DECLARE_PMID(kScriptInfoIDSpace, kGuideGrowZonePropertyScriptElement, kGuidePrefix + 57)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kGuideTypeEnumScriptElement, kGuidePrefix + 70)

//GUIDS
// {EE964079-06C6-11d2-AAC9-00C04FA349C7}
#define kGuide_CLSID { 0xee964079, 0x6c6, 0x11d2, { 0xaa, 0xc9, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {EE96407A-06C6-11d2-AAC9-00C04FA349C7}
#define kGuides_CLSID { 0xee96407a, 0x6c6, 0x11d2, { 0xaa, 0xc9, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }

#endif // __GuideID__
