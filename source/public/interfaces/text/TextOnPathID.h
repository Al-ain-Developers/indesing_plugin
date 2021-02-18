//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/TextOnPathID.h $
//  
//  Owner: Bertrand Lechevalier
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
//  Contains IDs used by Path Type plug-in
//  
//========================================================================================

#ifndef __TextOnPathID__
#define __TextOnPathID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kTOPPrefix	 RezLong(0x0B300)


//---------------------------------------------------------------
// <Start IDC>
//---------------------------------------------------------------

// PluginID
#define kTOPPluginName 		"Path Type"

START_IDS()
DECLARE_PMID(kPlugInIDSpace, kTOPPluginID, kTOPPrefix + 1)


//---------------------------------------------------------------
// <Class ID>
//---------------------------------------------------------------

// ClassIDs
// gap
DECLARE_PMID(kClassIDSpace, kTOPNewCmdBoss, kTOPPrefix + 8)
DECLARE_PMID(kClassIDSpace, kTOPDeleteCmdBoss, kTOPPrefix + 9)
// gap
DECLARE_PMID(kClassIDSpace, kTOPChangeItemCmdBoss, kTOPPrefix + 12)
// gap
DECLARE_PMID(kClassIDSpace, kSetTOPPrefsCmdBoss, kTOPPrefix + 15)
// gap
DECLARE_PMID(kClassIDSpace, kTOPConversionProviderBoss, kTOPPrefix + 17)
DECLARE_PMID(kClassIDSpace, kTOPHandleShapeAdornmentBoss, kTOPPrefix + 18)
// gap
DECLARE_PMID(kClassIDSpace, kTOPNewDocResponderBoss, kTOPPrefix + 21)
DECLARE_PMID(kClassIDSpace, kTOPShapeAdornmentBoss, kTOPPrefix + 22)
// gap
DECLARE_PMID(kClassIDSpace, kTOPFrameItemBoss, kTOPPrefix + 24)
DECLARE_PMID(kClassIDSpace, kTOPOpenDocResponderBoss, kTOPPrefix + 25)
DECLARE_PMID(kClassIDSpace, kTOPConnectCmdBoss, kTOPPrefix + 26)
DECLARE_PMID(kClassIDSpace, kTOPDisconnectCmdBoss, kTOPPrefix + 27)
DECLARE_PMID(kClassIDSpace, kTOPMarkChangeDamageCmdBoss, kTOPPrefix + 28)
DECLARE_PMID(kClassIDSpace, kTOPWorkPathGeometryBoss, kTOPPrefix + 29)
DECLARE_PMID(kClassIDSpace, kTOPRIDXNotifierHandlerBoss, kTOPPrefix + 30)
// gap
DECLARE_PMID(kClassIDSpace, kTOPSplineItemBoss, kTOPPrefix + 32)
DECLARE_PMID(kClassIDSpace, kTOPDeleteSpreadCmdBoss, kTOPPrefix + 33)
DECLARE_PMID(kClassIDSpace, kTOPDeleteLayerCmdBoss, kTOPPrefix + 34)
DECLARE_PMID(kClassIDSpace, kTOPDeleteMasterSpreadCmdBoss, kTOPPrefix + 35)
DECLARE_PMID(kClassIDSpace, kCopyTOPSplineCmdBoss, kTOPPrefix + 36)
DECLARE_PMID(kClassIDSpace, kTOPRefConverterBoss, kTOPPrefix + 37)
// gap
DECLARE_PMID(kClassIDSpace, kTOPErrorStringServiceBoss, kTOPPrefix + 39)
DECLARE_PMID(kClassIDSpace, kAddTextOnPathCmdBoss, kTOPPrefix + 40)
DECLARE_PMID(kClassIDSpace, kPickUpTOPAttributesCmdBoss, kTOPPrefix + 41)
DECLARE_PMID(kClassIDSpace, kApplyTOPAttributesCmdBoss, kTOPPrefix + 42)
DECLARE_PMID(kClassIDSpace, kTOPScriptProviderBoss, kTOPPrefix + 43)
DECLARE_PMID(kClassIDSpace, kTOPSchemaConversionProviderBoss, kTOPPrefix + 44)
DECLARE_PMID(kClassIDSpace, kMainItemTOPDataM2MListenerServiceBoss, kTOPPrefix + 45)

DECLARE_PMID(kClassIDSpace, kTOPInvertAbsCmdBoss, kTOPPrefix + 50)

//---------------------------------------------------------------
// <Implementation ID>
//---------------------------------------------------------------

// ImplementationIDs
DECLARE_PMID(kImplementationIDSpace, kMainItemTOPDataImpl, kTOPPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kTOPNewCmdImpl, kTOPPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kTOPItemCmdDataImpl, kTOPPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kTOPHandleShapeImpl, kTOPPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kTOPDeleteCmdImpl, kTOPPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kPathTypeDrawingUtilsImpl, kTOPPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kPathTypeUtilsImpl, kTOPPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kTOPChangeItemCmdImpl, kTOPPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kTOPChangeItemCmdDataImpl, kTOPPrefix + 18)
// gap
DECLARE_PMID(kImplementationIDSpace, kTOPOptionsImpl, kTOPPrefix + 21)
// gap
DECLARE_PMID(kImplementationIDSpace, kSetTOPPrefsCmdImpl, kTOPPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kSetTOPPrefsCmdDataImpl, kTOPPrefix + 24)
// gap
DECLARE_PMID(kImplementationIDSpace, kTOPConversionProviderImpl, kTOPPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kTOPNewDocResponderImpl, kTOPPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kTOPShapeAdornmentImpl, kTOPPrefix + 28)
// gap
// DECLARE_PMID(kImplementationIDSpace, kTOPFrameObserverImpl, kTOPPrefix + 30) // Can't file any reference to this [LDM]
DECLARE_PMID(kImplementationIDSpace, kTOPFrameDataImpl, kTOPPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kTOPFrameHierarchyImpl, kTOPPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kTOPErrorStringServiceImpl, kTOPPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kTOPTextTilerImpl, kTOPPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kWaxGlyphsTOPTransformImpl, kTOPPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kTOPDocObserverImpl, kTOPPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kTOPOpenDocResponderImpl, kTOPPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kTOPConnectCmdImpl, kTOPPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kTOPDisconnectCmdImpl, kTOPPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kTOPInkResourcesAdrnImpl, kTOPPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kTOPOffscreenAttrImpl, kTOPPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kTOPMarkChangeDamageCmdImpl, kTOPPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kTOPMainItemObserverImpl, kTOPPrefix + 43)
//DECLARE_PMID(kImplementationIDSpace, kTOPStopCmdImpl, kTOPPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kUpdateTOPPathsCmdImpl, kTOPPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kUpdateTOPPathsCmdDataImpl, kTOPPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kWaxRunFinalValuesImpl, kTOPPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kTOPDeleteSpreadCmdImpl, kTOPPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kTOPDeleteLayerCmdImpl, kTOPPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kTOPSplineDataImpl, kTOPPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kTOPSplineObserverImpl, kTOPPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kTOPSplineHierarchyImpl, kTOPPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kTOPSplineTransformImpl, kTOPPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kCopyTOPSplineCmdImpl, kTOPPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kTOPDeleteMasterSpreadCmdImpl, kTOPPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kTOPRefConverterImpl, kTOPPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kTOPRIDXNotifierHandlerImpl, kTOPPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kCopyTOPSplineCmdDataImpl, kTOPPrefix + 58)
// gap
DECLARE_PMID(kImplementationIDSpace, kAddTextOnPathCmdImpl, kTOPPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kPickUpTOPAttributesCmdImpl, kTOPPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kApplyTOPAttributesCmdImpl, kTOPPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kTOPOptionsCmdDataImpl, kTOPPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kTOPInlineDataImpl, kTOPPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kTOPVisitorHelperImpl, kTOPPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kTextOnPathSuiteLayoutCSBImpl, kTOPPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kPathTypeDebugDataImpl, kTOPPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kTextOnPathSuiteASBImpl, kTOPPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kTextOnPathSuiteTextCSBImpl, kTOPPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kTOPScriptProviderImpl, kTOPPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kTOPScriptImpl, kTOPPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kTOPAdornmentFlattenerUsageImpl, kTOPPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kTextOnPathSuiteDefaultCSBImpl, kTOPPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kTOPTextFrameOversetOverrideImpl, kTOPPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kMainItemTOPDataM2MListenerImpl, kTOPPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kTOPInvertAbsCmdImpl, kTOPPrefix + 76)

//---------------------------------------------------------------
// <Service ID>
//---------------------------------------------------------------

// <Service ID>

//---------------------------------------------------------------
// <Interface ID>
//---------------------------------------------------------------

// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IMAINITEMTOPDATA, kTOPPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ITOPFRAMEDATA, kTOPPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ITOPITEMCMDDATA, kTOPPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ITOPCHANGEITEMCMDDATA, kTOPPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_ITOPOPTIONS, kTOPPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_ITOPPREFSCMDDATA, kTOPPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IUPDATETOPPATHSCMDDATA, kTOPPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IWAXGLYPHSTOPTRANSFORM, kTOPPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IWAXRUNFINALVALUES, kTOPPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_ITOPMAINITEMOBSERVER, kTOPPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_ITOPSPLINEDATA, kTOPPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_ITOPDOCOBSERVER, kTOPPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IPATHTYPEDRAWINGUTILS, kTOPPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOPYTOPSPLINECMDDATA, kTOPPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_ICLOSEDOCTOPOBSERVER, kTOPPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_ITOPOPTIONSCMDDATA, kTOPPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_ITOPINLINEDATA, kTOPPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTONPATHSELECTIONSUITE, kTOPPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_IPATHTYPEUTILS, kTOPPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_IPATHTYPEDEBUGDATA, kTOPPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_IMAINITEMTOPDATA_ROOT, kTOPPrefix + 21)

//Error IDs
DECLARE_PMID(kErrorIDSpace, kCantCreateTOPOnInlines,		kTOPPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kTOPAlreadyExists,				kTOPPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kPathIsNotAvailable,			kTOPPrefix + 3)

//---------------------------------------------------------------
// <Scripting ID>
//---------------------------------------------------------------

//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kTOPObjectScriptElement,					kTOPPrefix + 1)

//Events

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kStartBracketPropertyScriptElement,		kTOPPrefix + 20)
DECLARE_PMID(kScriptInfoIDSpace, kCenterBracketPropertyScriptElement,		kTOPPrefix + 21)
DECLARE_PMID(kScriptInfoIDSpace, kEndBracketPropertyScriptElement,			kTOPPrefix + 22)
DECLARE_PMID(kScriptInfoIDSpace, kFlipTOPEffectPropertyScriptElement,		kTOPPrefix + 23)
DECLARE_PMID(kScriptInfoIDSpace, kTOPTextAlignmentPropertyScriptElement,	kTOPPrefix + 24)
DECLARE_PMID(kScriptInfoIDSpace, kTOPPathAlignmentPropertyScriptElement,	kTOPPrefix + 25)
DECLARE_PMID(kScriptInfoIDSpace, kTOPSpacingPropertyScriptElement,			kTOPPrefix + 26)
DECLARE_PMID(kScriptInfoIDSpace, kTOPEffectPropertyScriptElement,			kTOPPrefix + 27)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kTOPEffectEnumScriptElement,				kTOPPrefix + 30)
DECLARE_PMID(kScriptInfoIDSpace, kTOPTextAlignmentEnumScriptElement,		kTOPPrefix + 31)
DECLARE_PMID(kScriptInfoIDSpace, kTOPPathAlignmentEnumScriptElement,		kTOPPrefix + 32)
DECLARE_PMID(kScriptInfoIDSpace, kTOPFlipEnumScriptElement,					kTOPPrefix + 33)

//---------------------------------------------------
// InvalHandlerTypeID
//---------------------------------------------------
DECLARE_PMID(kInvalHandlerIDSpace, kTextOnPathItemsInvalHandlerID, kTOPPrefix + 1)

//---------------------------------------------------------------
// <Message ID>
//---------------------------------------------------------------

DECLARE_PMID(kMessageIDSpace, kTOPBeforeDrawMessage, kTOPPrefix + 1)
DECLARE_PMID(kMessageIDSpace, kTOPAfterDrawMessage, kTOPPrefix + 2)



END_IDS()

//GUIDS
// {CB13E01A-0161-4a08-BA44-E3F1E0256900}
#define kTextPath_CLSID {0xcb13e01a, 0x161, 0x4a08, { 0xba, 0x44, 0xe3, 0xf1, 0xe0, 0x25, 0x69, 0x0 }}
// {49DE930A-C5C7-48f7-BC94-6F4375FAC282}
#define kTextPaths_CLSID {0x49de930a, 0xc5c7, 0x48f7, { 0xbc, 0x94, 0x6f, 0x43, 0x75, 0xfa, 0xc2, 0x82 }}

#endif
