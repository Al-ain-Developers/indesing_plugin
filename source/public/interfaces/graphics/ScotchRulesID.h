//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ScotchRulesID.h $
//  
//  Owner: Greg St. Pierre
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

#ifndef __ScotchRulesID__
#define __ScotchRulesID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"
#include "FormatNumber.h"

#define kScotchRulesID						RezLong(0xb000)

// PluginID
#define kScotchRulesPluginName 				"ScotchRules"
DECLARE_PMID(kPlugInIDSpace, kScotchRulesPluginID, kScotchRulesID + 1)

// ClassIDs
//
//gap
DECLARE_PMID(kClassIDSpace, kStrokeParametersBoss, kScotchRulesID + 2)
//DECLARE_PMID(kClassIDSpace, kCustomStripePathStrokerBoss_Obsolete, kScotchRulesID + 3)
DECLARE_PMID(kClassIDSpace, kThinThinPathStrokerBoss, kScotchRulesID + 4)
DECLARE_PMID(kClassIDSpace, kThinThickPathStrokerBoss, kScotchRulesID + 5)
DECLARE_PMID(kClassIDSpace, kThickThinPathStrokerBoss, kScotchRulesID + 6)
DECLARE_PMID(kClassIDSpace, kThickThickPathStrokerBoss, kScotchRulesID + 7)
DECLARE_PMID(kClassIDSpace, kThinThickThinPathStrokerBoss, kScotchRulesID + 8)
DECLARE_PMID(kClassIDSpace, kThickThinThickPathStrokerBoss, kScotchRulesID + 9)
// gap
// gap
// gap
// gap
//DECLARE_PMID(kClassIDSpace, kStrokeParamsStartValueBoss_Obsolete, kScotchRulesID + 14)
//DECLARE_PMID(kClassIDSpace, kStrokeParamsWidthValueBoss_Obsolete, kScotchRulesID + 15)
DECLARE_PMID(kClassIDSpace, kScotchRulesNewDocResponderBoss, kScotchRulesID + 16)
DECLARE_PMID(kClassIDSpace, kScotchRulesOpenDocResponderBoss, kScotchRulesID + 17)
DECLARE_PMID(kClassIDSpace, kCachePathGeometryBoss, kScotchRulesID + 18)
// gap
DECLARE_PMID(kClassIDSpace, kScotchRulesTempPathGeometryBoss, kScotchRulesID + 20)
DECLARE_PMID(kClassIDSpace, kScotchRulesConversionProviderBoss, kScotchRulesID + 21)
DECLARE_PMID(kClassIDSpace, kCustomStripedPathStrokerBoss, kScotchRulesID + 22)
DECLARE_PMID(kClassIDSpace, kStripedPathStrokerMetadataBoss, kScotchRulesID + 23)
DECLARE_PMID(kClassIDSpace, kSetStripedAttrCmdBoss, kScotchRulesID + 24)
//DECLARE_PMID(kClassIDSpace, kScotchRulesMenuComponentBoss_Obsolete, kScotchRulesID + 25)
DECLARE_PMID(kClassIDSpace, kTriplePathStrokerBoss, kScotchRulesID + 26)
DECLARE_PMID(kClassIDSpace, kScotchRulesRefConverterBoss, kScotchRulesID + 27)
DECLARE_PMID(kClassIDSpace, kNewCustomStripeStyleCommandBoss, kScotchRulesID + 28)
// gap
// gap
DECLARE_PMID(kClassIDSpace, kTableStripePathStrokerBoss, kScotchRulesID + 31)

//
// ImplementationIIDs
//
//gap
DECLARE_PMID(kImplementationIDSpace, kStrokeParametersImpl, kScotchRulesID + 2)
//DECLARE_PMID(kImplementationIDSpace, kCustomStripePathStrokerImpl_Obsolete, kScotchRulesID + 3)
DECLARE_PMID(kImplementationIDSpace, kThinThinPathStrokerImpl, kScotchRulesID + 4)
DECLARE_PMID(kImplementationIDSpace, kThinThickPathStrokerImpl, kScotchRulesID + 5)
DECLARE_PMID(kImplementationIDSpace, kThickThinPathStrokerImpl, kScotchRulesID + 6)
DECLARE_PMID(kImplementationIDSpace, kThickThickPathStrokerImpl, kScotchRulesID + 7)
DECLARE_PMID(kImplementationIDSpace, kThinThickThinPathStrokerImpl, kScotchRulesID + 8)
DECLARE_PMID(kImplementationIDSpace, kThickThinThickPathStrokerImpl, kScotchRulesID + 9)
DECLARE_PMID(kImplementationIDSpace, kStrokeParamsGraphicAttrImpl, kScotchRulesID + 10)
DECLARE_PMID(kImplementationIDSpace, kScotchRulesDebugFlagsImpl, kScotchRulesID + 11)
// gap
// gap
// gap
// gap
//DECLARE_PMID(kImplementationIDSpace, kStrokeParamsStartObserverImpl_Obsolete, kScotchRulesID + 16)
//DECLARE_PMID(kImplementationIDSpace, kStrokeParamsWidthObserverImpl_Obsolete, kScotchRulesID + 17)
//DECLARE_PMID(kImplementationIDSpace, kStrokeParamsGfxStateObserverImpl_Obsolete, kScotchRulesID + 18)
//DECLARE_PMID(kImplementationIDSpace, kStripedStrokePanelImpl_Obsolete, kScotchRulesID + 19)
DECLARE_PMID(kImplementationIDSpace, kOffsetPathCacheImpl, kScotchRulesID + 20)
DECLARE_PMID(kImplementationIDSpace, kOffsetPathCacheObserverImpl, kScotchRulesID + 21)
DECLARE_PMID(kImplementationIDSpace, kScotchRulesNewDocResponderImpl, kScotchRulesID + 22)
DECLARE_PMID(kImplementationIDSpace, kRangeToRealMapImpl, kScotchRulesID + 23)
// gap
DECLARE_PMID(kImplementationIDSpace, kCustomStripedPathStrokerImpl, kScotchRulesID + 25)
DECLARE_PMID(kImplementationIDSpace, kStripedPathStrokerMetadataImpl, kScotchRulesID + 26)
DECLARE_PMID(kImplementationIDSpace, kSetStripedAttrCmdImpl, kScotchRulesID + 27)
DECLARE_PMID(kImplementationIDSpace, kSetStripedAttrCmdDataImpl, kScotchRulesID + 28)
//DECLARE_PMID(kImplementationIDSpace, kScotchRulesMenuComponentImpl_Obsolete, kScotchRulesID + 29)
DECLARE_PMID(kImplementationIDSpace, kTriplePathStrokerImpl, kScotchRulesID + 30)
DECLARE_PMID(kImplementationIDSpace, kScotchRulesRefConverterImpl, kScotchRulesID + 31)
// gap
DECLARE_PMID(kImplementationIDSpace, kNPCustomStrokeParametersImpl, kScotchRulesID + 33)
// gap
DECLARE_PMID(kImplementationIDSpace, kCustomStripedPathStrokerDataImpl, kScotchRulesID + 35)
DECLARE_PMID(kImplementationIDSpace, kNewCustomStripeStyleCommandImpl, kScotchRulesID + 36)
// gap
DECLARE_PMID(kImplementationIDSpace, kTableStripePathStrokerImpl, kScotchRulesID + 39)
DECLARE_PMID(kImplementationIDSpace, kScotchRulesFillPathOverrideImpl, kScotchRulesID + 40)

//
// InterfaceIIDs
//
DECLARE_PMID(kInterfaceIDSpace, IID_ISTROKEPARAMETERS, kScotchRulesID + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCOTCHRULESDEBUGFLAGS, kScotchRulesID + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IOFFSETPATHCACHE, kScotchRulesID + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IOFFSETPATHCACHEOBSERVER, kScotchRulesID + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IRANGETOREALMAP, kScotchRulesID + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETSTRIPEDATTRCMDDATA, kScotchRulesID + 6)

//---------------------------------------------------
// InvalHandlerTypeID
//---------------------------------------------------
DECLARE_PMID(kInvalHandlerIDSpace, kOffsetPathInvalHandlerID, kScotchRulesID + 1 )

//ResourceID
#define kScotchRulesRsrcID					10005
#define kScotchRulesStringsRsrcID			10000
#define kScotchRulesStringsNoTransRsrcID	11000

//
// ActionIDs
//

#endif // __ScotchRulesID__
