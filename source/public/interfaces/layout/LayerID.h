//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/LayerID.h $
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
//  Contains IDs used by the layers plug-in
//  
//========================================================================================

#ifndef __LayerID__
#define __LayerID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"
#include "FormatNumber.h"


#define kLayerPrefix			RezLong(0x0300)


// PluginID
#define kLayerPluginName 		"Layer"
DECLARE_PMID(kPlugInIDSpace, kLayerPluginID, kLayerPrefix + 1)

// ClassIDs
DECLARE_PMID(kClassIDSpace, kSpreadLayerBoss, kLayerPrefix + 1)
DECLARE_PMID(kClassIDSpace, kDocumentLayerBoss, kLayerPrefix + 2)
DECLARE_PMID(kClassIDSpace, kDocumentLayerListBoss, kLayerPrefix + 3 )
DECLARE_PMID(kClassIDSpace, kNewLayerCmdBoss, kLayerPrefix + 4)
DECLARE_PMID(kClassIDSpace, kMoveLayerCmdBoss, kLayerPrefix + 5)
DECLARE_PMID(kClassIDSpace, kLockLayerCmdBoss, kLayerPrefix + 7)
DECLARE_PMID(kClassIDSpace, kShowLayerCmdBoss, kLayerPrefix + 8)
DECLARE_PMID(kClassIDSpace, kChangeLayerNameCmdBoss, kLayerPrefix + 9)
DECLARE_PMID(kClassIDSpace, kMoveToLayerCmdBoss, kLayerPrefix + 10)
DECLARE_PMID(kClassIDSpace, kDeleteLayerCmdBoss, kLayerPrefix + 11)
DECLARE_PMID(kClassIDSpace, kSetLayerColorCmdBoss, kLayerPrefix + 12)
DECLARE_PMID(kClassIDSpace, kShowGuideLayerCmdBoss, kLayerPrefix + 13)
DECLARE_PMID(kClassIDSpace, kLockGuideLayerCmdBoss, kLayerPrefix + 14)
DECLARE_PMID(kClassIDSpace, kLayerOpenDocResponderBoss, kLayerPrefix + 15)
DECLARE_PMID(kClassIDSpace, kSetLayerUngroupPrefsCmdBoss, kLayerPrefix + 16)
DECLARE_PMID(kClassIDSpace, kSetLayerPrefsCmdBoss, kLayerPrefix + 17)
DECLARE_PMID(kClassIDSpace, kLayerNewDocResponderBoss, kLayerPrefix + 18)
DECLARE_PMID(kClassIDSpace, kMergeLayersCmdBoss, kLayerPrefix + 19)
DECLARE_PMID(kClassIDSpace, kLayerErrorStringServiceBoss, kLayerPrefix + 20)
DECLARE_PMID(kClassIDSpace, kAddDefaultLayersCmdBoss, kLayerPrefix + 22)
DECLARE_PMID(kClassIDSpace, kCreateLayerFromLayerCmdBoss, kLayerPrefix + 23)
DECLARE_PMID(kClassIDSpace, kDuplicateLayerCmdBoss, kLayerPrefix + 24)
DECLARE_PMID(kClassIDSpace, kLayerSuiteRegisterBoss, kLayerPrefix + 26)
DECLARE_PMID(kClassIDSpace, kLayerConversionProviderBoss, kLayerPrefix + 27)
DECLARE_PMID(kClassIDSpace, kLayerScriptProviderBoss, kLayerPrefix + 28)
DECLARE_PMID(kClassIDSpace, kLayersPhase2ConversionBoss, kLayerPrefix + 29)
DECLARE_PMID(kClassIDSpace, kTextWrapLayerOptionsCmdBoss, kLayerPrefix + 30)
DECLARE_PMID(kClassIDSpace, kIgnoreHiddenTextWrapCmdBoss, kLayerPrefix + 31)
DECLARE_PMID(kClassIDSpace, kSetUILayerCmdBoss, kLayerPrefix + 32)
DECLARE_PMID(kClassIDSpace, kSetExpendableLayerCmdBoss, kLayerPrefix + 33)
DECLARE_PMID(kClassIDSpace, kSetActiveLayerCmdBoss, kLayerPrefix + 34)
DECLARE_PMID(kClassIDSpace, kPrintLayerCmdBoss, kLayerPrefix + 35)

// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYERLIST, kLayerPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCUMENTLAYER, kLayerPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ISPREADLAYER, kLayerPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_INEWLAYERCMDDATA, kLayerPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IACTIVELAYER, kLayerPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYERPREFERENCES, kLayerPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYERPREFSCMDDATA, kLayerPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IDUPLICATELAYERCMDDATA, kLayerPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYERUTILS, kLayerPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTWRAPLAYEROPTIONSCMDDATA, kLayerPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IDELETELAYEROBSERVER, kLayerPrefix + 14)
// Custom message
DECLARE_PMID(kInterfaceIDSpace, IID_IUPDATEPROXYSELECTION, kLayerPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYERFACADE, kLayerPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_ISPREADLAYERHIERARCHYCHANGED, kLayerPrefix + 17)
// normal interfaces
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYERINFOBEFOREGROUPING, kLayerPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYERUNGROUPPREFERENCES, kLayerPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAYERUNGROUPPREFSCMDDATA, kLayerPrefix + 20)

// Implementation IIDs
DECLARE_PMID(kImplementationIDSpace, kLayerListImpl, kLayerPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kSpreadLayerImpl, kLayerPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kCSpreadLayerNodeImpl, kLayerPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kDocumentLayerImpl, kLayerPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kNewLayerCmdImpl, kLayerPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kMoveLayerCmdImpl, kLayerPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kLockLayerCmdImpl, kLayerPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kShowLayerCmdImpl, kLayerPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kChangeLayerNameCmdImpl, kLayerPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kMoveToLayerCmdImpl, kLayerPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kDeleteLayerCmdImpl, kLayerPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kSetLayerColorCmdImpl, kLayerPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kShowGuideLayerCmdImpl, kLayerPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kLockGuideLayerCmdImpl, kLayerPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kLayerShapeImpl, kLayerPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kNewLayerCmdDataImpl, kLayerPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kActiveLayerUIDRefDataImpl, kLayerPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kCLayerPrefsImpl, kLayerPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kSetLayerPrefsCmdImpl, kLayerPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kLayerPrefsCmdDataImpl, kLayerPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kLayerNewDocResponderImpl, kLayerPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kMergeLayersCmdImpl, kLayerPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kLayerErrorStringServiceImpl, kLayerPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kAddDefaultLayersCmdImpl, kLayerPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kLayerVisitorHelperImpl, kLayerPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kCreateLayerFromLayerCmdImpl, kLayerPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kDuplicateLayerCmdImpl, kLayerPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kDuplicateLayerCmdDataImpl, kLayerPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kDeleteLayerObserverImpl, kLayerPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kLayerInfoBeforeGroupingImpl, kLayerPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kLayerUngroupPrefsImpl, kLayerPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kLayerUtilsImpl, kLayerPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kSetLayerUngroupPrefsCmdImpl, kLayerPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kSessionUngroupRemembersLayersPrefsDataImpl, kLayerPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kLayerScriptProviderImpl, kLayerPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kLayerScriptImpl, kLayerPrefix + 42)
//gap
DECLARE_PMID(kImplementationIDSpace, kLayersPhase2ConversionImpl, kLayerPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kTextWrapLayerOptionsCmdDataImpl, kLayerPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kTextWrapLayerOptionsCmdImpl, kLayerPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kIgnoreHiddenTextWrapCmdImpl, kLayerPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kSetUILayerCmdImpl, kLayerPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kSetExpendableLayerCmdImpl, kLayerPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kSetActiveLayerCmdImpl, kLayerPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kPrintLayerCmdImpl, kLayerPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kLayerFacadeImpl, kLayerPrefix + 52)


// Error Codes
DECLARE_PMID(kErrorIDSpace, kCantMoveToLayerError,				kLayerPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kCantMoveInlineToLayerError,		kLayerPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kCantDeleteLayerError,				kLayerPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kCantDropOnLayerError,				kLayerPrefix + 4)
DECLARE_PMID(kErrorIDSpace, kLastLayerError,					kLayerPrefix + 5)
DECLARE_PMID(kErrorIDSpace, kLockedLayerError,					kLayerPrefix + 6)
DECLARE_PMID(kErrorIDSpace, kLayerNameAlreadyExistsError,		kLayerPrefix + 7)
DECLARE_PMID(kErrorIDSpace, kCantMoveLockedItemsToLayerError,	kLayerPrefix + 8)

//
//Script Element IDs
//

//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kLayerObjectScriptElement,				kLayerPrefix + 40)

//Events
DECLARE_PMID(kScriptInfoIDSpace, kMergeLayerMethodScriptElement,			kLayerPrefix + 82)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kTextWrapLayerPropertyScriptElement,		kLayerPrefix + 160)
DECLARE_PMID(kScriptInfoIDSpace, kLayerColorPropertyScriptElement,			kLayerPrefix + 161)
DECLARE_PMID(kScriptInfoIDSpace, kIgnoreWrapLayerPropertyScriptElement,		kLayerPrefix + 162)
DECLARE_PMID(kScriptInfoIDSpace, kShowGuidesLayerPropertyScriptElement,		kLayerPrefix + 163)
DECLARE_PMID(kScriptInfoIDSpace, kLockGuidesLayerPropertyScriptElement,		kLayerPrefix + 164)
DECLARE_PMID(kScriptInfoIDSpace, kUILayerPropertyScriptElement,				kLayerPrefix + 165)
DECLARE_PMID(kScriptInfoIDSpace, kExpendableLayerPropertyScriptElement,		kLayerPrefix + 166)
DECLARE_PMID(kScriptInfoIDSpace, kPrintablePropertyScriptElement,			kLayerPrefix + 167)
DECLARE_PMID(kScriptInfoIDSpace, kUngroupRemembersLayersPropertyScriptElement, kLayerPrefix + 168) 

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kTextWrapOptionsEnumScriptElement,			kLayerPrefix + 220)


//GUIDS
// {1A5E8DB8-3443-11d1-803C-0060B03C02E4}
#define kLayer_CLSID { 0x1a5e8db8, 0x3443, 0x11d1, { 0x80, 0x3c, 0x0, 0x60, 0xb0, 0x3c, 0x2, 0xe4 } }
// {1A5E8DB9-3443-11d1-803C-0060B03C02E4}
#define kLayers_CLSID { 0x1a5e8db9, 0x3443, 0x11d1, { 0x80, 0x3c, 0x0, 0x60, 0xb0, 0x3c, 0x2, 0xe4 } }

#endif // __LayerID__
