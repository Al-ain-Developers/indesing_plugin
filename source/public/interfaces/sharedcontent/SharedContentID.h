//======================================================================================== 
//   
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/sharedcontent/SharedContentID.h $ 
//   
//  Owner: Ashish Duggal
//   
//  $Author: pmbuilder $ 
//   
//  $DateTime: 2020/11/06 13:08:29 $ 
//   
//  $Revision: #2 $ 
//   
//  $Change: 1088580 $ 
//
//  ADOBE CONFIDENTIAL
//   
//  Copyright 2010 Adobe Systems Incorporated
//  All Rights Reserved.
//   
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received 
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe. 
//   
//======================================================================================== 

#ifndef __SharedContentID__
#define __SharedContentID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kSharedContentPrefix				RezLong(0x21D00)

// <Start IDC>
#define kSharedContentPluginName 			"Shared Content"
DECLARE_PMID(kPlugInIDSpace, kSharedContentPluginID, kSharedContentPrefix + 1)

// <Class ID> 
DECLARE_PMID(kClassIDSpace, kSharedContentLinkResourceProviderBoss, kSharedContentPrefix + 0)
DECLARE_PMID(kClassIDSpace, kSharedContentLinkResourceHandlerBoss, kSharedContentPrefix + 1)
DECLARE_PMID(kClassIDSpace, kSharedContentLinkUpdateLinkServiceProviderBoss, kSharedContentPrefix + 2)
DECLARE_PMID(kClassIDSpace, kSharedContentLinkBoss, kSharedContentPrefix + 3)
DECLARE_PMID(kClassIDSpace, kCreateSharedStoryCmdBoss, kSharedContentPrefix + 4)
DECLARE_PMID(kClassIDSpace, kSharedContentLinkDeleteResponderBoss, kSharedContentPrefix + 5) 
DECLARE_PMID(kClassIDSpace, kSharedContentDeleteStoryResponderBoss, kSharedContentPrefix + 6) 
DECLARE_PMID(kClassIDSpace, kSharedContentLinkAddResponderBoss, kSharedContentPrefix + 7) 
DECLARE_PMID(kClassIDSpace, kSharedContentBeforeDocCloseResponderBoss, kSharedContentPrefix + 8) 
DECLARE_PMID(kClassIDSpace, kSharedContentScriptProviderBoss, kSharedContentPrefix + 9)
DECLARE_PMID(kClassIDSpace, kSchemaBasedSharedContentConversionProviderBoss, kSharedContentPrefix + 10)
DECLARE_PMID(kClassIDSpace, kSetLinkedStoryPlacePrefsCmdBoss, kSharedContentPrefix + 11)
DECLARE_PMID(kClassIDSpace, kLinkedStoryOptionsScriptProviderBoss, kSharedContentPrefix + 12)
DECLARE_PMID(kClassIDSpace, kSharedContentDocSaveResponderBoss, kSharedContentPrefix + 13) 
DECLARE_PMID(kClassIDSpace, kSharedContentDocSaveAsResponderBoss, kSharedContentPrefix + 14) 
DECLARE_PMID(kClassIDSpace, kSharedContentPlaceScriptProviderBoss, kSharedContentPrefix + 15)
DECLARE_PMID(kClassIDSpace, kSharedContentNewDocResponderBoss, kSharedContentPrefix + 16)
DECLARE_PMID(kClassIDSpace, kSharedContentErrorStringServiceBoss,  kSharedContentPrefix + 17)
DECLARE_PMID(kClassIDSpace, kSharedContentLinkObjectAdornmentBoss,  kSharedContentPrefix + 18)

DECLARE_PMID(kClassIDSpace, kSharedContentDuringOpenDocResponderBoss, kSharedContentPrefix + 19)
DECLARE_PMID(kClassIDSpace, kSharedContentDuringNewDocResponderBoss, kSharedContentPrefix + 20)
DECLARE_PMID(kClassIDSpace, kSetShowLinkedStoryStatusPrefsCmdBoss, kSharedContentPrefix + 21)
DECLARE_PMID(kClassIDSpace, kSharedContentLinkChangedResponderBoss,  kSharedContentPrefix + 22)
DECLARE_PMID(kClassIDSpace, kSharedContentAttachDataLinkResponderBoss, kSharedContentPrefix + 23)
DECLARE_PMID(kClassIDSpace, kSharedContentPhase2ConversionBoss, kSharedContentPrefix + 24)
DECLARE_PMID(kClassIDSpace, kSetSharedContentChangeCountCmdBoss, kSharedContentPrefix + 25)
DECLARE_PMID(kClassIDSpace, kCreateLinkStoryBoss, kSharedContentPrefix + 26)
DECLARE_PMID(kClassIDSpace, kSerializeSharedContentStampToXMPCmdBoss, kSharedContentPrefix + 27)
DECLARE_PMID(kClassIDSpace, kNonPersistentInterfaceChangeCountBoss, kSharedContentPrefix + 28)
DECLARE_PMID(kClassIDSpace, kSetSourceObjectNameCmdBoss, kSharedContentPrefix + 29)
DECLARE_PMID(kClassIDSpace, kCreateSharedContentLinkCmdBoss, kSharedContentPrefix + 30)
//gap
DECLARE_PMID(kClassIDSpace, kSetStyleMappingRuleCmdBoss, kSharedContentPrefix + 33)
DECLARE_PMID(kClassIDSpace, kAddStyleMappingRuleCmdBoss, kSharedContentPrefix + 34)
DECLARE_PMID(kClassIDSpace, kRemoveStyleMappingRuleCmdBoss, kSharedContentPrefix + 35)
DECLARE_PMID(kClassIDSpace, kClearStyleMappingsCmdBoss, kSharedContentPrefix + 36)


//------- gap -----//

//***************Shared Article bosses****************************

// <Class ID> 
DECLARE_PMID(kClassIDSpace, kSharedArticleLinkBoss, kSharedContentPrefix + 50)
DECLARE_PMID(kClassIDSpace, kCreateSharedObjectCmdBoss, kSharedContentPrefix + 51)
DECLARE_PMID(kClassIDSpace, kSharedObjectM2MListenerServiceBoss, kSharedContentPrefix + 52)
DECLARE_PMID(kClassIDSpace, kPathGeometryUpdateProviderBoss, kSharedContentPrefix + 53)
DECLARE_PMID(kClassIDSpace, kGraphicStyleOverridesProviderBoss, kSharedContentPrefix + 54)
DECLARE_PMID(kClassIDSpace, kHierarchyUpdateProviderBoss, kSharedContentPrefix + 55)
DECLARE_PMID(kClassIDSpace, kChildLinkUIDListDataM2MListenerServiceBoss, kSharedContentPrefix + 56)
DECLARE_PMID(kClassIDSpace, kAnimationDataUpdateProviderBoss, kSharedContentPrefix + 57)
//--gap--
DECLARE_PMID(kClassIDSpace, kUpdateChangeCountCmdBoss, kSharedContentPrefix + 61)
//---gap---
DECLARE_PMID(kClassIDSpace, kSetLinkedArticlePlacePrefsCmdBoss, kSharedContentPrefix + 63)
DECLARE_PMID(kClassIDSpace, kCreateLinkPageItemBoss, kSharedContentPrefix + 64)
DECLARE_PMID(kClassIDSpace, kUpdateAllInterfacesCmdBoss, kSharedContentPrefix + 65)
DECLARE_PMID(kClassIDSpace, kOtherAttributesUpdateProviderBoss, kSharedContentPrefix + 66)
DECLARE_PMID(kClassIDSpace, kCopyObjectExportOptionsCmdBoss, kSharedContentPrefix + 67)
//---gap---
DECLARE_PMID(kClassIDSpace, kTextStoryUpdateProviderBoss, kSharedContentPrefix + 70)
DECLARE_PMID(kClassIDSpace, kSetStyleMappingsCmdBoss, kSharedContentPrefix + 71)
DECLARE_PMID(kClassIDSpace, kLinkedPageItemOptionsScriptProviderBoss, kSharedContentPrefix + 72)
DECLARE_PMID(kClassIDSpace, kLinkedArticleConversionProviderBoss, kSharedContentPrefix + 73)
DECLARE_PMID(kClassIDSpace, kStyleMappingsScriptProviderBoss, kSharedContentPrefix + 74)
DECLARE_PMID(kClassIDSpace, kStyleMappingRuleScriptBoss, kSharedContentPrefix + 75)
DECLARE_PMID(kClassIDSpace, kStyleMappingsNamedSetBoss, kSharedContentPrefix + 76)
DECLARE_PMID(kClassIDSpace, kSetICCCmdBoss, kSharedContentPrefix + 77)
DECLARE_PMID(kClassIDSpace, kStyleMappingScriptObjectBoss, kSharedContentPrefix + 78)
DECLARE_PMID(kClassIDSpace, kAddStyleMappingCmdBoss, kSharedContentPrefix + 82)
DECLARE_PMID(kClassIDSpace, kSharedContentAdornmentM2MListenerServiceBoss, kSharedContentPrefix + 83)


// <Implementation ID>
DECLARE_PMID(kImplementationIDSpace, kSharedContentLinkResourceFactoryImpl, kSharedContentPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kSharedContentLinkResourceHandlerImpl, kSharedContentPrefix + 1) 
DECLARE_PMID(kImplementationIDSpace, kSharedContentLinkResourceStateUpdaterImpl, kSharedContentPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kSharedContentLinkUpdateLinkServiceImpl, kSharedContentPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kSharedContentFacadeImpl, kSharedContentPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kCreateSharedStoryCmdImpl, kSharedContentPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kSharedContentTableImpl, kSharedContentPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kChildLinksUIDListDataImpl_Obsolete, kSharedContentPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kLinkDeleteCmdResponderImpl, kSharedContentPrefix + 8) 
DECLARE_PMID(kImplementationIDSpace, kDeleteStoryCmdResponderImpl, kSharedContentPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kLinkAddCmdResponderImpl, kSharedContentPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kOriginatingDBImpl, kSharedContentPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kSharedContentDocResponderImpl, kSharedContentPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kSharedContentScriptProviderImpl, kSharedContentPrefix + 13) 
DECLARE_PMID(kImplementationIDSpace, kSharedContentChildLinksUIDListDataImpl, kSharedContentPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kSharedContentSuiteASBImpl, kSharedContentPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kSharedContentSuiteLayoutCSBImpl, kSharedContentPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kSharedContentSuiteTextCSBImpl, kSharedContentPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kLinkedStoryPlacePrefsImpl, kSharedContentPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kSetLinkedStoryPlacePrefsCmdImpl, kSharedContentPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kLinkedStoryPlacePrefsDataImpl, kSharedContentPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kLinkedStoryOptionsScriptProviderImpl, kSharedContentPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kSharedContentDocSaveResponderImpl, kSharedContentPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kSharedContentPlaceScriptProviderImpl, kSharedContentPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kSharedContentNewDocResponderImpl, kSharedContentPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kSharedContentErrorStringServiceImpl, kSharedContentPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kSharedContentLinkObjectAdornmentImpl, kSharedContentPrefix + 27)
//-----------gap--------------------
DECLARE_PMID(kImplementationIDSpace, kCShowLinkedStoryStatusPrefsImpl, kSharedContentPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kSessionShowLinkedStoryStatusPrefsImpl, kSharedContentPrefix + 30) 
DECLARE_PMID(kImplementationIDSpace, kDocShowLinkedStoryStatusPrefsImpl, kSharedContentPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kSetShowLinkedStoryStatusPrefsCmdImpl, kSharedContentPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kSharedContentLinkChangedResponderImpl, kSharedContentPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kLinkAttachCmdResponderImpl, kSharedContentPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kSharedContentGlobalScopeImpl, kSharedContentPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kSharedContentChangeCountImpl_Obsolete, kSharedContentPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kSharedContentPhase2ConversionImpl, kSharedContentPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kSetSharedContentChangeCountCmdImpl, kSharedContentPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kCreateLinkServiceImpl, kSharedContentPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kCreateLinkStoryProviderImpl, kSharedContentPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kSerializeSharedContentStampToXMPCmdImpl, kSharedContentPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kSharedContentPrivateUtilsImpl, kSharedContentPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kSharedContentXMPStampsTableImpl, kSharedContentPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kLinkResourceXMPStampCacheImpl, kSharedContentPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kSetSourceObjectNameCmdImpl, kSharedContentPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kSourceObjectNameStringImpl, kSharedContentPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kStyleMappingsImpl, kSharedContentPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kCreateSharedContentLinkCmdImpl, kSharedContentPrefix + 49)
//gap
DECLARE_PMID(kImplementationIDSpace, kStyleGroupLookUpImpl, kSharedContentPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kStyleMappingScriptImpl, kSharedContentPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kAddStyleMappingCmdImpl, kSharedContentPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kSharedContentRelinkMonitorImpl, kSharedContentPrefix + 55)


//------- gap -----//

//***************Shared Article impls****************************

// <Implementation ID>
DECLARE_PMID(kImplementationIDSpace, kCreateSharedObjectCmdImpl, kSharedContentPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kSharedObjectM2MListenerImpl, kSharedContentPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kUpdateServiceImpl, kSharedContentPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kPathGeometryUpdateProviderImpl, kSharedContentPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kGraphicStyleOverridesProviderImpl, kSharedContentPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kHierarchyUpdateProviderImpl, kSharedContentPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kUIDMapImpl, kSharedContentPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kDeletePageItemCmdResponderImpl, kSharedContentPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kChildLinkUIDM2MListnerImpl, kSharedContentPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kAnimationDataUpdateProviderImpl, kSharedContentPrefix + 69)

//--gap--
DECLARE_PMID(kImplementationIDSpace, kSharedArticleObserverImpl, kSharedContentPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kUpdateChangeCountCmdImpl, kSharedContentPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kOtherAttributesUpdateProviderImpl, kSharedContentPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kChangeCountNumberImpl, kSharedContentPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kDescChangeCountNumberImpl, kSharedContentPrefix + 76)
//--gap--
DECLARE_PMID(kImplementationIDSpace, kInterfaceChangeCountImpl, kSharedContentPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kInterfaceIDListDataImpl, kSharedContentPrefix + 79)
DECLARE_PMID(kImplementationIDSpace, kTargetInterfaceChangeCountImpl, kSharedContentPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kSetLinkedArticlePlacePrefsCmdImpl, kSharedContentPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kCreateLinkPageItemProviderImpl, kSharedContentPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kLastUpdatedInterfaceChangeCountImpl, kSharedContentPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kUpdateAllInterfacesCmdImpl, kSharedContentPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kParentUIDDataImpl, kSharedContentPrefix + 85)
//---gap--
DECLARE_PMID(kImplementationIDSpace, kCopyObjectExportOptionsCmdImpl, kSharedContentPrefix + 87)
//--gap---
DECLARE_PMID(kImplementationIDSpace, kNonPersistentInterfaceChangeCountImpl, kSharedContentPrefix + 90)
DECLARE_PMID(kImplementationIDSpace, kMemberInterfaceChangeCountImpl_obsolete, kSharedContentPrefix + 91)
DECLARE_PMID(kImplementationIDSpace, kTargetMemberInterfaceChangeCountImpl_obsolete, kSharedContentPrefix + 92)
// gap
DECLARE_PMID(kImplementationIDSpace, kLinkedPageItemPrefsImpl, kSharedContentPrefix + 94)
DECLARE_PMID(kImplementationIDSpace, kLinkStatusObserverImpl, kSharedContentPrefix + 95)
DECLARE_PMID(kImplementationIDSpace, kSetStyleMappingsCmdImpl, kSharedContentPrefix + 96)
DECLARE_PMID(kImplementationIDSpace, kLinkedPageItemOptionsScriptProviderImpl, kSharedContentPrefix + 97)
DECLARE_PMID(kImplementationIDSpace, kLinkedPageItemPrefsCmdDataImpl, kSharedContentPrefix + 98)
DECLARE_PMID(kImplementationIDSpace, kLinkedArticleConversionProviderImpl, kSharedContentPrefix + 99)
DECLARE_PMID(kImplementationIDSpace, kStyleMappingsScriptProviderImpl, kSharedContentPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kStyleMappingsCmdDataImpl, kSharedContentPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kSetStyleMappingRuleCmdImpl, kSharedContentPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kAddStyleMappingRuleCmdImpl, kSharedContentPrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kRemoveStyleMappingRuleCmdImpl, kSharedContentPrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kClearStyleMappingsCmdImpl, kSharedContentPrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kStyleMappingFacadeImpl, kSharedContentPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kStyleMappingNamedSetNameStringImpl, kSharedContentPrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kMappingSessionImpl, kSharedContentPrefix + 108)
DECLARE_PMID(kImplementationIDSpace, kSetICCCmdImpl, kSharedContentPrefix + 109)
DECLARE_PMID(kImplementationIDSpace, kInterfaceIDToQueryImpl, kSharedContentPrefix + 110)
DECLARE_PMID(kImplementationIDSpace, kSharedContentAdornmentM2MListenerImpl, kSharedContentPrefix + 111)	

// <Interface ID> 
DECLARE_PMID(kInterfaceIDSpace, IID_ISHAREDCONTENTFACADE, kSharedContentPrefix + 0)
DECLARE_PMID(kInterfaceIDSpace, IID_ISHAREDCONTENTTABLE, kSharedContentPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IORIGINATINGDB, kSharedContentPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ISHAREDCONTENTCHILDLINKUIDLISTDATA, kSharedContentPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ISHAREDCONTENTSUITE, kSharedContentPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKEDSTORYPLACEPREFS, kSharedContentPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKEDSTORYPLACEPREFSDATA, kSharedContentPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_ISHAREDSTORYPRIVATEUTILS, kSharedContentPrefix + 8)
//-----------------gap-----------------
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKEDSTORYSTATUSPREFERENCES, kSharedContentPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_ISHAREDCONTENTGLOBALSCOPE, kSharedContentPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_ISHAREDCONTENTCHANGECOUNT, kSharedContentPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_ICREATELINKPROVIDER, kSharedContentPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_ISHAREDSTORYFACADE, kSharedContentPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_ISHAREDCONTENTPRIVATEUTILS, kSharedContentPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_ISHAREDCONTENTXMPSTAMPSTABLE, kSharedContentPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKRESOURCEXMPSTAMPCACHE, kSharedContentPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTYLEMAPPINGS, kSharedContentPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_IISMAPPING_OBSOLETE, kSharedContentPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTYLEGROUPLOOKUP, kSharedContentPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTYLEMAPPINGSCMDDATA, kSharedContentPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_ISHAREDCONTENTRELINKMONITOR, kSharedContentPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_ISHAREDCONTENTLINKUPDATE, kSharedContentPrefix + 23)


//------- gap -----//

//***************Shared Article interfaces****************************

// <Interface ID> 
DECLARE_PMID(kInterfaceIDSpace, IID_IUPDATEPROVIDER, kSharedContentPrefix + 40) 
//DECLARE_PMID(kInterfaceIDSpace, IID_IOBJECTSTYLEEDITBEGIN, kSharedContentPrefix + 41) 
//DECLARE_PMID(kInterfaceIDSpace, IID_IOBJECTSTYLEEDITEND, kSharedContentPrefix + 42) 
//DECLARE_PMID(kInterfaceIDSpace, IID_IDESCENDANTCHANGECOUNT, kSharedContentPrefix + 43) 
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKUIDMAP, kSharedContentPrefix + 44) 
DECLARE_PMID(kInterfaceIDSpace, IID_IUIDMAP, kSharedContentPrefix + 45) 
DECLARE_PMID(kInterfaceIDSpace, IID_ISHAREDARTICLEOBSERVER, kSharedContentPrefix + 46)
//DECLARE_PMID(kInterfaceIDSpace, IID_IOBJECTCHANGECOUNT, kSharedContentPrefix + 47)
//DECLARE_PMID(kInterfaceIDSpace, IID_IISEDITINGSTYLE, kSharedContentPrefix + 48)
DECLARE_PMID(kInterfaceIDSpace, IID_IINTERFACECHANGECOUNT, kSharedContentPrefix + 49)
DECLARE_PMID(kInterfaceIDSpace, IID_IINTERFACEIDLISTDATA, kSharedContentPrefix + 50)
DECLARE_PMID(kInterfaceIDSpace, IID_INONOVERIDABLEINTERFCAE, kSharedContentPrefix + 51)
DECLARE_PMID(kInterfaceIDSpace, IID_TARGETINTERFACECHANGECOUNT, kSharedContentPrefix + 52)

DECLARE_PMID(kInterfaceIDSpace, IID_ISHAREDARTICLEFACADE, kSharedContentPrefix + 54)
DECLARE_PMID(kInterfaceIDSpace, IID_ILASTUPDATEDINTERFACECHANGECOUNT, kSharedContentPrefix + 55)
DECLARE_PMID(kInterfaceIDSpace, IID_IPARENTUIDDATA, kSharedContentPrefix + 56)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKEDPAGEITEMPREFS, kSharedContentPrefix + 59)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKSTATUSOBSERVER, kSharedContentPrefix + 60)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKEDPAGEITEMPREFSCMDDATA, kSharedContentPrefix + 61)
DECLARE_PMID(kInterfaceIDSpace, IID_IOTHERATTRIBUTES, kSharedContentPrefix + 62)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTYLEMAPPINGFACADE, kSharedContentPrefix + 63)
DECLARE_PMID(kInterfaceIDSpace, IID_IMAPPINGSESSION, kSharedContentPrefix + 64)
DECLARE_PMID(kInterfaceIDSpace, IID_IINTERFACEIDTOQUERY, kSharedContentPrefix + 65)

	

//Service IDs
DECLARE_PMID(kServiceIDSpace, kCreateLinkProviderService, kSharedContentPrefix + 1) 

//------- gap -----//

//***************Shared Article services****************************

// <Service ID>
DECLARE_PMID(kServiceIDSpace, kUpdateProviderService, kSharedContentPrefix + 10)


DECLARE_PMID(kScriptInfoIDSpace, kSharedContentDestUniqueKeyPropertyScriptElement, kSharedContentPrefix + 0) 
DECLARE_PMID(kScriptInfoIDSpace, kLinkedStoryOptionsScriptElement, kSharedContentPrefix + 1) 
DECLARE_PMID(kScriptInfoIDSpace, kLinkedStoryOptionsPropertyScriptElement, kSharedContentPrefix + 2) 
DECLARE_PMID(kScriptInfoIDSpace, kLinkedStoryUpdateDuringSavePropertyScriptElement, kSharedContentPrefix + 3) 
DECLARE_PMID(kScriptInfoIDSpace, kLinkedStoryWarnOnUpdateOfEditedStoryPropertyScriptElement, kSharedContentPrefix + 4) 
DECLARE_PMID(kScriptInfoIDSpace, kLinkedStoryRemoveForcedLineBreaksPropertyScriptElement, kSharedContentPrefix + 5) 
DECLARE_PMID(kScriptInfoIDSpace, kPlaceAndLinkMethodScriptElement, kSharedContentPrefix + 6) 
DECLARE_PMID(kScriptInfoIDSpace, kPlaceAndLinkOnSpreadMethodScriptElement, kSharedContentPrefix + 7) 
DECLARE_PMID(kScriptInfoIDSpace, kPlaceAndLinkOnDocumentMethodScriptElement, kSharedContentPrefix + 8) 
DECLARE_PMID(kScriptInfoIDSpace, kMappingRuleTypeEnumScriptElement, kSharedContentPrefix + 9)

//--- gap ---

DECLARE_PMID(kScriptInfoIDSpace, kLinkedStoryStyleMappingsPropertyScriptElement, kSharedContentPrefix + 20)
DECLARE_PMID(kScriptInfoIDSpace, kParaStyleMappingObjectScriptElement, kSharedContentPrefix + 21)
DECLARE_PMID(kScriptInfoIDSpace, kAddStyleMappingMethodScriptElement, kSharedContentPrefix + 22)
DECLARE_PMID(kScriptInfoIDSpace, kCellStyleMappingObjectScriptElement, kSharedContentPrefix + 23)
DECLARE_PMID(kScriptInfoIDSpace, kCharStyleMappingObjectScriptElement, kSharedContentPrefix + 24)
DECLARE_PMID(kScriptInfoIDSpace, kTableStyleMappingObjectScriptElement, kSharedContentPrefix + 25)



//***************Shared Article Scripting Elements****************************

DECLARE_PMID(kScriptInfoIDSpace, kSharedContentParentICCPropertyScriptElement, kSharedContentPrefix + 50)
DECLARE_PMID(kScriptInfoIDSpace, kSharedContentTargetICCPropertyScriptElement, kSharedContentPrefix + 51)
DECLARE_PMID(kScriptInfoIDSpace, kSharedContentLastUpdatedICCPropertyScriptElement, kSharedContentPrefix + 52)

DECLARE_PMID(kScriptInfoIDSpace, kLinkedPageItemOptionsScriptElement, kSharedContentPrefix + 53)
DECLARE_PMID(kScriptInfoIDSpace, kLinkedPageItemOptionsPropertyScriptElement, kSharedContentPrefix + 54)
DECLARE_PMID(kScriptInfoIDSpace, kLinkedPageItemUpdateDuringSavePropertyScriptElement, kSharedContentPrefix + 55)
DECLARE_PMID(kScriptInfoIDSpace, kLinkedPageItemWarnOnUpdateOfEditedPageItemPropertyScriptElement, kSharedContentPrefix + 56)
DECLARE_PMID(kScriptInfoIDSpace, kLinkedPageItemOverrideOtherAttributesPropertyScriptElement, kSharedContentPrefix + 57)
DECLARE_PMID(kScriptInfoIDSpace, kLinkedPageItemShowLinkOptionsWhenCreatingLinkPropertyScriptElement, kSharedContentPrefix + 58)
DECLARE_PMID(kScriptInfoIDSpace, kLinkedPageItemOverridePathgeometryPropertyScriptElement, kSharedContentPrefix + 59)
DECLARE_PMID(kScriptInfoIDSpace, kLinkedPageItemOverrideGraphicAttributesPropertyScriptElement, kSharedContentPrefix + 60)
DECLARE_PMID(kScriptInfoIDSpace, kLinkedPageItemOverrideInteractiveAttributesPropertyScriptElement, kSharedContentPrefix + 61)
DECLARE_PMID(kScriptInfoIDSpace, kLinkedPageItemOverrideContentPropertyScriptElement, kSharedContentPrefix + 62)
DECLARE_PMID(kScriptInfoIDSpace, kDeleteStyleMappingMethodScriptElement, kSharedContentPrefix + 63)
DECLARE_PMID(kScriptInfoIDSpace, kSourceStyleNamePropertyScriptElement, kSharedContentPrefix + 64)
DECLARE_PMID(kScriptInfoIDSpace, kDestStyleNamePropertyScriptElement, kSharedContentPrefix + 65)
DECLARE_PMID(kScriptInfoIDSpace, kRuleTypePropertyScriptElement, kSharedContentPrefix + 67)
DECLARE_PMID(kScriptInfoIDSpace, kSharedContentUIDMapPropertyScriptElement, kSharedContentPrefix + 68)


DECLARE_PMID(kErrorIDSpace, kPlaceAndLinkFailedError, kSharedContentPrefix + 1) 
DECLARE_PMID(kErrorIDSpace, kPlaceAndLinkInlineError, kSharedContentPrefix + 2) 
DECLARE_PMID(kErrorIDSpace, kInvalidSourceMappingNameParameterError, kSharedContentPrefix + 3) 
DECLARE_PMID(kErrorIDSpace, kInvalidDestMappingNameParameterError, kSharedContentPrefix + 4) 
DECLARE_PMID(kErrorIDSpace, kStyleMappingFailedError, kSharedContentPrefix + 5)

//GUIDS 
// {CE38D788-413B-4562-A498-B4AE5E36EE82}
#define  kLinkedStoryOptions_CLSID { 0xce38d788, 0x413b, 0x4562, { 0xa4, 0x98, 0xb4, 0xae, 0x5e, 0x36, 0xee, 0x82 } }

// {fedf506c-b334-4c29-b417-392b2e7dbe19}
#define  kSharedContentICC_CLSID { 0xfedf506c, 0xb334, 0x4c29, { 0xb4, 0x17, 0x39, 0x2b, 0x2e, 0x7d, 0xbe, 0x19 } }

// {116a50e0-dab9-11e0-be68-0002a5d5c51b}
#define  kLinkedPageItemOptions_CLSID { 0x116a50e0, 0xdab9, 0x11e0, { 0xbe, 0x68, 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } }

// {B0D6C8D8-876D-4523-A573-FACA73A0661E}
#define kParaStyleMapping_CLSID { 0xb0d6c8d8, 0x876d, 0x4523, { 0xa5, 0x73, 0xfa, 0xca, 0x73, 0xa0, 0x66, 0x1e } }

// {9F9F4DAB-B4A0-4BCF-A838-77E807E63574}
#define kParaStyleMappings_CLSID { 0x9f9f4dab, 0xb4a0, 0x4bcf, { 0xa8, 0x38, 0x77, 0xe8, 0x7, 0xe6, 0x35, 0x74 } }

// {5BF64089-C1EE-462F-9B8D-70E1F67C6932}
#define kCellStyleMapping_CLSID { 0x5bf64089, 0xc1ee, 0x462f, { 0x9b, 0x8d, 0x70, 0xe1, 0xf6, 0x7c, 0x69, 0x32 } }

// {C26B9F05-9487-446E-9F1F-04F777278012}
#define kCellStyleMappings_CLSID { 0xc26b9f05, 0x9487, 0x446e, { 0x9f, 0x1f, 0x4, 0xf7, 0x77, 0x27, 0x80, 0x12 } }

// {8C4FB68E-C8B0-4270-A519-2951EA90C99E}
#define kCharStyleMapping_CLSID { 0x8c4fb68e, 0xc8b0, 0x4270, { 0xa5, 0x19, 0x29, 0x51, 0xea, 0x90, 0xc9, 0x9e } }

// {85A15D80-48E2-4CE1-A283-69B5DC6F9FE7}
#define kCharStyleMappings_CLSID { 0x85a15d80, 0x48e2, 0x4ce1, { 0xa2, 0x83, 0x69, 0xb5, 0xdc, 0x6f, 0x9f, 0xe7 } }

// {8B9F5475-0280-4606-A865-B54281AED0B6}
#define kTableStyleMapping_CLSID { 0x8b9f5475, 0x280, 0x4606, { 0xa8, 0x65, 0xb5, 0x42, 0x81, 0xae, 0xd0, 0xb6 } }

// {D90F3576-AFAA-411E-AE8A-DB097E37F9E1}
#define kTableStyleMappings_CLSID { 0xd90f3576, 0xafaa, 0x411e, { 0xae, 0x8a, 0xdb, 0x9, 0x7e, 0x37, 0xf9, 0xe1 } }


#endif // __SharedContentID__
