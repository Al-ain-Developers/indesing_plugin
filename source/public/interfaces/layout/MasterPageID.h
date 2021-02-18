//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/MasterPageID.h $
//  
//  Owner:
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
//  ADOBE CONFIDENTIAL
//  
//  Contains IDs used by the master pages plug-in
//  
//========================================================================================

#ifndef __MasterPagesID__
#define __MasterPagesID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"
#include "FormatNumber.h"


#define kMasterPagesPrefix	 RezLong(0x1400)


// PluginID
#define kMasterPagePluginName			"Master Page"
DECLARE_PMID(kPlugInIDSpace, kMasterPagePluginID, kMasterPagesPrefix + 1)

// ClassIDs
DECLARE_PMID(kClassIDSpace, kMasterPagesBoss, kMasterPagesPrefix + 1)
DECLARE_PMID(kClassIDSpace, kNewMasterSpreadCmdBoss, kMasterPagesPrefix + 4)
DECLARE_PMID(kClassIDSpace, kDeleteMasterSpreadCmdBoss, kMasterPagesPrefix + 5)
DECLARE_PMID(kClassIDSpace, kOverrideMasterPageItemCmdBoss, kMasterPagesPrefix + 6)
DECLARE_PMID(kClassIDSpace, kShowMasterItemsCmdBoss, kMasterPagesPrefix + 7)
DECLARE_PMID(kClassIDSpace, kCreateMasterFromSpreadCmdBoss, kMasterPagesPrefix + 9)
DECLARE_PMID(kClassIDSpace, kMasterStandOffModeBoss, kMasterPagesPrefix + 10)

DECLARE_PMID(kClassIDSpace, kMasterPageEventDrawServicesBoss, kMasterPagesPrefix + 11)
DECLARE_PMID(kClassIDSpace, kMoveMasterSpreadCmdBoss, kMasterPagesPrefix + 12)
DECLARE_PMID(kClassIDSpace, kApplyMasterSpreadCmdBoss, kMasterPagesPrefix + 13)
DECLARE_PMID(kClassIDSpace, kMasterPageScript50ProviderBoss, kMasterPagesPrefix + 14)
DECLARE_PMID(kClassIDSpace, kCreateMasterFromMasterCmdBoss, kMasterPagesPrefix + 15)
DECLARE_PMID(kClassIDSpace, kMasterPageRIDXNotifierHandlerBoss, kMasterPagesPrefix + 16)
DECLARE_PMID(kClassIDSpace, kRenameMasterSpreadCmdBoss, kMasterPagesPrefix + 17)
DECLARE_PMID(kClassIDSpace, kMasterPageIterateServiceBoss, kMasterPagesPrefix + 18)
DECLARE_PMID(kClassIDSpace, kRemoveMasterPageOverrideCmdBoss, kMasterPagesPrefix + 19)
DECLARE_PMID(kClassIDSpace, kSetPrimaryTextFlowCmdBoss, kMasterPagesPrefix + 20)

DECLARE_PMID(kClassIDSpace, kApplyMasterFlowResponderBoss, kMasterPagesPrefix + 21)
DECLARE_PMID(kClassIDSpace, kMasterPageErrorStringServiceBoss, kMasterPagesPrefix + 22)
DECLARE_PMID(kClassIDSpace, kMasterPageDeletePageItemServiceBoss, kMasterPagesPrefix + 23)
DECLARE_PMID(kClassIDSpace, kOverrideObserverOpenAppActionBoss, kMasterPagesPrefix + 24)
DECLARE_PMID(kClassIDSpace, kOverridePgItmInterfaceCmdBoss, kMasterPagesPrefix + 25)
DECLARE_PMID(kClassIDSpace, kOverrideDeleteCleanupCmdBoss, kMasterPagesPrefix + 26)
DECLARE_PMID(kClassIDSpace, kMasterSpreadNewDocResponderBoss, kMasterPagesPrefix + 27)

DECLARE_PMID(kClassIDSpace, kMasterSpreadScriptProviderBoss, kMasterPagesPrefix + 28)
DECLARE_PMID(kClassIDSpace, kMasterPageScriptProviderBoss, kMasterPagesPrefix + 29)
DECLARE_PMID(kClassIDSpace, kSetMasterOverrideableCmdBoss, kMasterPagesPrefix + 30)
DECLARE_PMID(kClassIDSpace, kPrivateApplyMasterSpreadCmdBoss, kMasterPagesPrefix + 31)
DECLARE_PMID(kClassIDSpace, kPrivateNewMasterSpreadCmdBoss, kMasterPagesPrefix + 32)
DECLARE_PMID(kClassIDSpace, kBreakControllingLinkCmdBoss, kMasterPagesPrefix + 33)
DECLARE_PMID(kClassIDSpace, kPrivateRemoveMPOverrideCmdBoss, kMasterPagesPrefix + 34)
DECLARE_PMID(kClassIDSpace, kPrivateDeleteMasterSpreadCmdBoss, kMasterPagesPrefix + 35)
DECLARE_PMID(kClassIDSpace, kPrivateOverrideMasterPageItemCmdBoss, kMasterPagesPrefix + 36)

DECLARE_PMID(kClassIDSpace, kApplyMasterSignalMgrBoss, kMasterPagesPrefix + 37)
DECLARE_PMID(kClassIDSpace, kApplyMasterMarColResponderBoss, kMasterPagesPrefix + 38)
DECLARE_PMID(kClassIDSpace, kPrivateOverrideMPILinkCmdBoss, kMasterPagesPrefix + 39)
DECLARE_PMID(kClassIDSpace, kMasterPageSyncBoss, kMasterPagesPrefix + 40)
DECLARE_PMID(kClassIDSpace, kMasterPagesConversionProviderBoss, kMasterPagesPrefix + 41)
DECLARE_PMID(kClassIDSpace, kPrivateCleanupOnPageDelCmdBoss, kMasterPagesPrefix + 42)
DECLARE_PMID(kClassIDSpace, kMasterPagesPhase2ConvBoss, kMasterPagesPrefix + 43)
DECLARE_PMID(kClassIDSpace, kOverrideScriptProviderBoss, kMasterPagesPrefix + 44)

DECLARE_PMID(kClassIDSpace, kDuplicateSpreadMasterPageResponderBoss, kMasterPagesPrefix + 45)
DECLARE_PMID(kClassIDSpace, kPrivateDuplicateOverrideCmdBoss, kMasterPagesPrefix + 46)
DECLARE_PMID(kClassIDSpace, kImportMasterPageCmdBoss, kMasterPagesPrefix + 47)
DECLARE_PMID(kClassIDSpace, kOverrideOrSyncMasterPageCmdBoss, kMasterPagesPrefix + 48)
DECLARE_PMID(kClassIDSpace, kSynchronizeMasterPageCmdBoss, kMasterPagesPrefix + 49)
DECLARE_PMID(kClassIDSpace, kMasterPageCodeConversionProviderBoss, kMasterPagesPrefix + 50)
DECLARE_PMID(kClassIDSpace, kMasterPageSyncConversionProviderBoss, kMasterPagesPrefix + 51)
DECLARE_PMID(kClassIDSpace, kDeletePrimaryFlowStoryCmdResponderBoss, kMasterPagesPrefix + 52)
DECLARE_PMID(kClassIDSpace, kPrimaryFlowModelPostProcessorBoss, kMasterPagesPrefix + 53)
//gap
DECLARE_PMID(kClassIDSpace, kMasterPageFilterNonCrossoversServiceBoss, kMasterPagesPrefix + 55)
DECLARE_PMID(kClassIDSpace, kOverrideScript50ProviderBoss, kMasterPagesPrefix + 56)
DECLARE_PMID(kClassIDSpace, kMasterPageFormXObjectProviderBoss, kMasterPagesPrefix + 57)
DECLARE_PMID(kClassIDSpace, kSetMasterPageTransformCmdBoss, kMasterPagesPrefix + 58)


// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IMASTERSPREADLIST, kMasterPagesPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IMASTERSPREAD, kMasterPagesPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IMASTERSPREADCMDDATA, kMasterPagesPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IOVERRIDEMASTERPAGEITEMDATA, kMasterPagesPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IMASTEROVERRIDEABLE, kMasterPagesPrefix + 5)

DECLARE_PMID(kInterfaceIDSpace, IID_IDRAWMASTERELEMENTS, kMasterPagesPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IMASTERPAGE, kMasterPagesPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IFLOWFACADE, kMasterPagesPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IMASTEROVERRIDELIST, kMasterPagesPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IFLOWDATA, kMasterPagesPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IFLOWSUITE, kMasterPagesPrefix + 11)
// The next 3 IIDs probably ought to be in Public
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTROLLINGPAGEITEM, kMasterPagesPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONTROLLEDPAGEITEMS, kMasterPagesPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IOVERRIDEOFFSET, kMasterPagesPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IOVERRIDEOBSERVER, kMasterPagesPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IAUTOMATICMASTERTEXTFRAME, kMasterPagesPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGESPERSPREAD, kMasterPagesPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_IAPPLYMASTERSIGNALDATA, kMasterPagesPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_IMASTERSPREADUTILS, kMasterPagesPrefix + 19)
// new for DragonTail:
DECLARE_PMID(kInterfaceIDSpace, IID_IMASTERPAGESUITE, kMasterPagesPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRIVATEMASTERPAGEUTILS, kMasterPagesPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_IOVERRIDEMPILINKDATA, kMasterPagesPrefix + 22)
// for kPrivateRemoveMPOverrideCmdBoss which needs two UIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEUIDDATA, kMasterPagesPrefix + 23)

DECLARE_PMID(kInterfaceIDSpace, IID_ISOURCEPAGEITEMUIDLIST, kMasterPagesPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_IDESTINATIONPAGEITEMUIDLIST, kMasterPagesPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_IDESTINATIONMASTERPAGEUIDLIST, kMasterPagesPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_ISOURCEDOCUMENTINFO, kMasterPagesPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_ISYNCMASTERPAGEDATA, kMasterPagesPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_ISOURCESPREADUIDDATA,kMasterPagesPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_ITARGETSPREADUIDDATA,kMasterPagesPrefix + 30)

DECLARE_PMID(kInterfaceIDSpace, IID_IPRIVATEMASTERSCRIPTUTILS, kMasterPagesPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_ISYNCMASTERPAGECMDDATA, kMasterPagesPrefix + 32)

// new for Cobalt:
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEITEMMASTEROVERRIDEABLESUITE, kMasterPagesPrefix + 33 )
DECLARE_PMID(kInterfaceIDSpace, IID_ILOADMASTERPAGESOURCEDOCINFO, kMasterPagesPrefix + 34)
DECLARE_PMID(kInterfaceIDSpace, IID_IFORWARDINGATTRIBUTES, kMasterPagesPrefix + 35)
DECLARE_PMID(kInterfaceIDSpace, IID_IMASTERPAGESYNCOPTION, kMasterPagesPrefix + 36)
DECLARE_PMID(kInterfaceIDSpace, IID_IDURINGLOADINGMASTERPAGE, kMasterPagesPrefix + 37)
DECLARE_PMID(kInterfaceIDSpace, IID_IDURINGCREATEALTERNATELAYOUT, kMasterPagesPrefix + 38)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IINTDATABINDING, kMasterPagesPrefix + 41)
DECLARE_PMID(kInterfaceIDSpace, IID_IMASTERPAGEITEMDRAWACCUMULATOR, kMasterPagesPrefix + 42)
DECLARE_PMID(kInterfaceIDSpace, IID_IM2MAPPLYMASTERMESSAGE, kMasterPagesPrefix + 43)


// Implementation IIDs
DECLARE_PMID(kImplementationIDSpace, kMasterSpreadListImpl, kMasterPagesPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kMasterSpreadImpl, kMasterPagesPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kOverrideMasterPageItemCmdImpl, kMasterPagesPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kMasterOverrideListImpl, kMasterPagesPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kNewMasterSpreadCmdImpl, kMasterPagesPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kMasterSpreadCmdDataImpl, kMasterPagesPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kDeleteMasterSpreadCmdImpl, kMasterPagesPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kFlowFacadeImpl, kMasterPagesPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kSetPrimaryTextFlowCmdImpl, kMasterPagesPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kFlowDataImpl, kMasterPagesPrefix + 10)

DECLARE_PMID(kImplementationIDSpace, kApplyMasterFlowResponderImpl, kMasterPagesPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kOverrideMasterPageItemDataImpl, kMasterPagesPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kDrawMasterElementsImpl, kMasterPagesPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kShowMasterItemsCmdImpl, kMasterPagesPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kCMasterPageImpl, kMasterPagesPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kMasterSpreadScriptProviderImpl, kMasterPagesPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kApplyMasterSpreadCmdImpl, kMasterPagesPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kFlowSuiteLayoutCSBImpl, kMasterPagesPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kMasterPageDrawEventServiceImpl, kMasterPagesPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kMasterPageDrawEventHandlerImpl, kMasterPagesPrefix + 20)

DECLARE_PMID(kImplementationIDSpace, kMasterPageOverrideHandlerImpl, kMasterPagesPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kFlowSuiteASBImpl, kMasterPagesPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kCreateMasterFromSpreadCmdImpl, kMasterPagesPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kCreateMasterFromMasterCmdImpl, kMasterPagesPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kPageItemMasterOverrideableSuiteASBImpl, kMasterPagesPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kRenameMasterSpreadCmdImpl, kMasterPagesPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kMasterPageIterateServiceImpl, kMasterPagesPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kMasterPageIterateEHImpl, kMasterPagesPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kRemoveMasterPageOverrideCmdImpl, kMasterPagesPrefix + 29)
// gap
DECLARE_PMID(kImplementationIDSpace, kDeletePrimaryFlowStoryCmdResponderImpl, kMasterPagesPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kPrimaryFlowPostProcessorImpl, kMasterPagesPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kMasterPageErrorStringServiceImpl, kMasterPagesPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kMasterPageDeleteCleanupServiceImpl, kMasterPagesPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kControllingPageItemImpl, kMasterPagesPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kControlledPageItemsImpl, kMasterPagesPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kOverrideObsOpenAppActionImpl, kMasterPagesPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kPageItemOverrideObserverImpl, kMasterPagesPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kOverridePgItmInterfaceCmdImpl, kMasterPagesPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kOverrideDeleteCleanupCmdImpl, kMasterPagesPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kMasterSpreadNewDocResponderImpl, kMasterPagesPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kMasterSpreadScriptImpl, kMasterPagesPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kMasterPageScriptProviderImpl, kMasterPagesPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kMasterOverrideableImpl, kMasterPagesPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kSetMasterOverrideableCmdImpl, kMasterPagesPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kPageItemMasterOverrideableSuiteLayoutCSBImpl, kMasterPagesPrefix + 47 )
DECLARE_PMID(kImplementationIDSpace, kPrivateApplyMasterSpreadCmdImpl, kMasterPagesPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kPrivateNewMasterSpreadCmdImpl, kMasterPagesPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kMasterSpreadAETEImpl, kMasterPagesPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kBreakControllingLinkCmdImpl, kMasterPagesPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kPrivateRemoveMPOverrideCmdImpl, kMasterPagesPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kPrivateDeleteMasterSpreadCmdImpl, kMasterPagesPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kPrivateOverrideMasterPageItemCmdImpl, kMasterPagesPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kApplyMasterSignalDataImpl, kMasterPagesPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kApplyMasterSignalRespServiceImpl, kMasterPagesPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kApplyMasterMarColResponderImpl, kMasterPagesPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kMoveMasterSpreadCmdImpl, kMasterPagesPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kMasterSpreadUtilsImpl, kMasterPagesPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kPrivateCleanupOnPageDelCmdImpl, kMasterPagesPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kMasterPagesPhase2ConvImpl, kMasterPagesPrefix + 61)
// new for DragonTail:
DECLARE_PMID(kImplementationIDSpace, kMasterPageSuiteASBImpl, kMasterPagesPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kMasterPageSuiteLayoutCSBImpl, kMasterPagesPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kOverrideScriptProviderImpl, kMasterPagesPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kPrivateMasterPageUtilsImpl, kMasterPagesPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kPrivateOverrideMPILinkCmdImpl, kMasterPagesPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kOverrideMPILinkDataImpl, kMasterPagesPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kPageUIDDataImpl, kMasterPagesPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kDuplicateSpreadMasterPageResponderImpl, kMasterPagesPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kPrivateDuplicateOverrideCmdImpl, kMasterPagesPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kSourcePageItemsUIDList, kMasterPagesPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kDestinationPageItemsUIDList, kMasterPagesPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kDestinationMasterPageUIDList, kMasterPagesPrefix + 73)

DECLARE_PMID(kImplementationIDSpace, kMasterPageScriptUtilsImpl, kMasterPagesPrefix + 74)

// new for firedrake
DECLARE_PMID(kImplementationIDSpace, kMasterPageSyncServiceImpl,kMasterPagesPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kSourceDocumentInfoImpl,	kMasterPagesPrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kSyncMasterPageDataImpl,	kMasterPagesPrefix + 77)
DECLARE_PMID(kImplementationIDSpace, kImportMasterPageCmdImpl,  kMasterPagesPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kOverrideOrSyncMasterPageCmdImpl, kMasterPagesPrefix + 79)
DECLARE_PMID(kImplementationIDSpace, kSourceSpreadUIDDataImpl,	kMasterPagesPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kTargetSpreadUIDDataImpl,	kMasterPagesPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kSynchronizeMasterPageCmdImpl, kMasterPagesPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kDuringCreateAlternateLayoutImpl, kMasterPagesPrefix + 83)
//gap
DECLARE_PMID(kImplementationIDSpace, kSyncMasterPageCmdDataImpl, kMasterPagesPrefix + 85)

DECLARE_PMID(kImplementationIDSpace, kMasterPageFilterNonCrossoversEventHandlerImpl, kMasterPagesPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kMasterPageRIDXNotifierHandlerImpl, kMasterPagesPrefix + 87)

// new for cobalt
DECLARE_PMID(kImplementationIDSpace, kOverrideScript50ProviderImpl, kMasterPagesPrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kMasterPageScript50ProviderImpl, kMasterPagesPrefix + 89)
DECLARE_PMID(kImplementationIDSpace, kMasterPageCodeConversionProviderImpl, kMasterPagesPrefix + 90)
DECLARE_PMID(kImplementationIDSpace, kLoadMasterPageSourceDocInfoImpl, kMasterPagesPrefix + 91)
DECLARE_PMID(kImplementationIDSpace, kForwardingAttributesImpl, kMasterPagesPrefix + 92)
DECLARE_PMID(kImplementationIDSpace, kDuringLoadingMasterPageImpl, kMasterPagesPrefix + 93)

// new for basil
DECLARE_PMID(kImplementationIDSpace, kMasterPageFormXObjectProviderImpl, kMasterPagesPrefix + 94)
//gap
DECLARE_PMID(kImplementationIDSpace, kIntDataBindingImpl, kMasterPagesPrefix + 97)
DECLARE_PMID(kImplementationIDSpace, kMasterPageItemDrawAccumulatorImpl, kMasterPagesPrefix + 98)

//new for rocket
DECLARE_PMID(kImplementationIDSpace, kOverrideOffsetImpl, kMasterPagesPrefix + 99)
DECLARE_PMID(kImplementationIDSpace, kSetMasterPageTransformCmdImpl, kMasterPagesPrefix + 100)



// Service IDs
DECLARE_PMID(kServiceIDSpace, kApplyMasterSignalResponderService, kMasterPagesPrefix + 1)

// Error Codes
DECLARE_PMID(kErrorIDSpace, kCircularMastersError, kMasterPagesPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kMasterPageItemAlreadyOverriddenError, kMasterPagesPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kMasterPageItemNotOverrideableError, kMasterPagesPrefix + 3)

// <Action ID>

// Viewport Attribute IDs
DECLARE_PMID(kViewPortAttrIDSpace, kMasterPageItemsDrawingVPAttr, kMasterPagesPrefix + 1)

//
//Script Element IDs
//

//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kMasterSpreadObjectScriptElement,					kMasterPagesPrefix + 40)
DECLARE_PMID(kScriptInfoIDSpace, kMasterPrimaryTextFramePropertyScriptElement,		kMasterPagesPrefix + 41)
DECLARE_PMID(kScriptInfoIDSpace, kCreateAlternateLayoutMethodScriptElement,			kMasterPagesPrefix + 42)
DECLARE_PMID(kScriptInfoIDSpace, kDeleteAlternateLayoutMethodScriptElement,			kMasterPagesPrefix + 43)

//Events
DECLARE_PMID(kScriptInfoIDSpace, kOverrideMethodScriptElement,						kMasterPagesPrefix + 60)
DECLARE_PMID(kScriptInfoIDSpace, kRemoveOverrideMethodScriptElement,					kMasterPagesPrefix + 61)
DECLARE_PMID(kScriptInfoIDSpace, kCreateMasterMethodScriptElement,					kMasterPagesPrefix + 62)
DECLARE_PMID(kScriptInfoIDSpace, kDetachMethodScriptElement,							kMasterPagesPrefix + 63)
DECLARE_PMID(kScriptInfoIDSpace, kLoadMastersMethodScriptElement,					kMasterPagesPrefix + 64)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kNamePrefixPropertyScriptElement,					kMasterPagesPrefix + 100)
DECLARE_PMID(kScriptInfoIDSpace, kBaseNamePropertyScriptElement,					kMasterPagesPrefix + 101)
DECLARE_PMID(kScriptInfoIDSpace, kAppliedMasterPropertyScriptElement,				kMasterPagesPrefix + 102)
DECLARE_PMID(kScriptInfoIDSpace, kOverridenPageItemPropertyScriptElement,			kMasterPagesPrefix + 103)
DECLARE_PMID(kScriptInfoIDSpace, kOverridenPIPropsPropertyScriptElement,			kMasterPagesPrefix + 104)
DECLARE_PMID(kScriptInfoIDSpace, kOverrideListPropertyScriptElement,				kMasterPagesPrefix + 105)
DECLARE_PMID(kScriptInfoIDSpace, kPageItemPropsEnumScriptElement,					kMasterPagesPrefix + 106)
DECLARE_PMID(kScriptInfoIDSpace, kMasterPageItemsListScriptElement,					kMasterPagesPrefix + 107)
DECLARE_PMID(kScriptInfoIDSpace, kMasterOverrideablePropertyScriptElement,			kMasterPagesPrefix + 108)
DECLARE_PMID(kScriptInfoIDSpace, kMasterPageTransformPropertyScriptElement,			kMasterPagesPrefix + 109)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kMasterPageClashResolutionStrategyEnumScriptElement, kMasterPagesPrefix + 150)

#endif // __MasterPagesID__
