//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IndexingID.h $
//  
//  Owner: blecheva
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

#ifndef __IndexingID__
#define __IndexingID__

#include "CrossPlatformTypes.h" // for RezLong
#include "IDFactory.h"
//#include "FormatNumber.h"

#define kIndexingPrefix		RezLong(0x13000)

// Conversion
// For pub conversion constants see IndexingConversionID.h

// PluginID
#define kIndexingPluginName 	"Indexing"
DECLARE_PMID(kPlugInIDSpace, kIndexingPluginID, kIndexingPrefix + 1)

// Where to declare this?
#define kIDXMaxTopicLevel		4

// <Start IDC>
// <Class ID>
// ClassIDs
// gap
DECLARE_PMID(kClassIDSpace, kIndexInstanceBoss,				kIndexingPrefix + 3)
DECLARE_PMID(kClassIDSpace, kIndexTopicListBoss,			kIndexingPrefix + 4)
DECLARE_PMID(kClassIDSpace, kIndexTopicSectionBoss,			kIndexingPrefix + 5)
DECLARE_PMID(kClassIDSpace, kIndexPageEntryBoss,			kIndexingPrefix + 6)
DECLARE_PMID(kClassIDSpace, kIndexXRefEntryBoss,			kIndexingPrefix + 7)
DECLARE_PMID(kClassIDSpace, kIndexXRefLinkBoss,				kIndexingPrefix + 8)
DECLARE_PMID(kClassIDSpace, kSetFormatOptionsCmdBoss,		kIndexingPrefix + 9)
//DECLARE_PMID(kClassIDSpace, kDeleteIndexCmdBoss,			kIndexingPrefix + 10)
DECLARE_PMID(kClassIDSpace, kCreateTopicListCmdBoss,		kIndexingPrefix + 11)
DECLARE_PMID(kClassIDSpace, kDeleteTopicListCmdBoss,		kIndexingPrefix + 12)
//DECLARE_PMID(kClassIDSpace, kCreateTopicSectionCmdBoss,		kIndexingPrefix + 13)
//DECLARE_PMID(kClassIDSpace, kDeleteTopicSectionCmdBoss,		kIndexingPrefix + 14)
DECLARE_PMID(kClassIDSpace, kTAIndexMarkBoss,				kIndexingPrefix + 15)
DECLARE_PMID(kClassIDSpace, kInsertIndexMarkCmdBoss,		kIndexingPrefix + 16)
DECLARE_PMID(kClassIDSpace, kTextAdornmentIndexMarkBoss,	kIndexingPrefix + 17)
DECLARE_PMID(kClassIDSpace, kCreateTopicEntryCmdBoss,		kIndexingPrefix + 18)
DECLARE_PMID(kClassIDSpace, kDeleteTopicEntryCmdBoss,		kIndexingPrefix + 19)
DECLARE_PMID(kClassIDSpace, kCreateIndexPageEntryCmdBoss,	kIndexingPrefix + 20)
DECLARE_PMID(kClassIDSpace, kEditIndexPageEntryCmdBoss,		kIndexingPrefix + 21)
DECLARE_PMID(kClassIDSpace, kDeleteIndexPageEntryCmdBoss,	kIndexingPrefix + 22)
DECLARE_PMID(kClassIDSpace, kSelectIndexPageEntryCmdBoss,	kIndexingPrefix + 23)
DECLARE_PMID(kClassIDSpace, kCreateIndexXRefEntryCmdBoss,	kIndexingPrefix + 24)
DECLARE_PMID(kClassIDSpace, kEditIndexXRefEntryCmdBoss,		kIndexingPrefix + 25)
DECLARE_PMID(kClassIDSpace, kDeleteIndexXRefEntryCmdBoss,	kIndexingPrefix + 26)
DECLARE_PMID(kClassIDSpace, kCopyIndexPageEntryCmdBoss,		kIndexingPrefix + 27)
DECLARE_PMID(kClassIDSpace, kUpdatePageEntryCmdBoss,		kIndexingPrefix + 28)
DECLARE_PMID(kClassIDSpace, kUpdateIndexCmdBoss,			kIndexingPrefix + 29)
DECLARE_PMID(kClassIDSpace, kGenerateIndexCmdBoss,			kIndexingPrefix + 30)
DECLARE_PMID(kClassIDSpace, kImportTopicsCmdBoss,			kIndexingPrefix + 31)
DECLARE_PMID(kClassIDSpace, kIndexingStartupShutdownBoss,	kIndexingPrefix + 32)
//gap
DECLARE_PMID(kClassIDSpace, kSetActiveTopicListScopeCmdBoss,kIndexingPrefix + 35)
DECLARE_PMID(kClassIDSpace, kAttachTopicListCmdBoss,		kIndexingPrefix + 36)
DECLARE_PMID(kClassIDSpace, kDetachTopicListCmdBoss,		kIndexingPrefix + 37)
DECLARE_PMID(kClassIDSpace, kEditTopicEntryCmdBoss,			kIndexingPrefix + 38)
DECLARE_PMID(kClassIDSpace, kCapitalizeTopicEntryCmdBoss,	kIndexingPrefix + 39)
DECLARE_PMID(kClassIDSpace, kCreateIndexInstanceCmdBoss,	kIndexingPrefix + 40)
DECLARE_PMID(kClassIDSpace, kIndexingErrorStringServiceBoss,kIndexingPrefix + 41)
DECLARE_PMID(kClassIDSpace, kRemoveIndexInstanceCmdBoss,	kIndexingPrefix + 42)
DECLARE_PMID(kClassIDSpace, kPlaceIndexCmdBoss,				kIndexingPrefix + 43)
DECLARE_PMID(kClassIDSpace, kIndexDataLinkRegistryBoss,		kIndexingPrefix + 44)
DECLARE_PMID(kClassIDSpace, kIndexDataLinkHelperBoss,		kIndexingPrefix + 45)
DECLARE_PMID(kClassIDSpace, kAttachIndexDataLinkCmdBoss,	kIndexingPrefix + 46)
DECLARE_PMID(kClassIDSpace, kRemoveIndexDataLinkCmdBoss,	kIndexingPrefix + 47)
DECLARE_PMID(kClassIDSpace, kIndexingContextCmdBoss,		kIndexingPrefix + 48)
DECLARE_PMID(kClassIDSpace, kRemoveUnusedTopicsCmdBoss,		kIndexingPrefix + 49)
DECLARE_PMID(kClassIDSpace, kChangeIndexHeaderSetCmdBoss,	kIndexingPrefix + 50)
DECLARE_PMID(kClassIDSpace, kIndexingCmdBoss,				kIndexingPrefix + 51)
DECLARE_PMID(kClassIDSpace, kIndexingRomanHSHandlerBoss,	kIndexingPrefix + 52)
DECLARE_PMID(kClassIDSpace, kIndexingJapaneseHSHandlerBoss,	kIndexingPrefix + 53)
DECLARE_PMID(kClassIDSpace, kIndexingIteratorRegBoss,		kIndexingPrefix + 54)
DECLARE_PMID(kClassIDSpace, kIndexingNewWSResponderBoss,	kIndexingPrefix + 55)
DECLARE_PMID(kClassIDSpace, kIndexingConversionProviderBoss, kIndexingPrefix + 56)
DECLARE_PMID(kClassIDSpace, kIndexRIDXNotifierHandlerBoss,		kIndexingPrefix + 57)
DECLARE_PMID(kClassIDSpace, kIndexingAllHSHandlerBoss,			kIndexingPrefix + 58)
DECLARE_PMID(kClassIDSpace, kChangeIndexHeaderSetMasterCmdBoss,	kIndexingPrefix + 59)
DECLARE_PMID(kClassIDSpace, kIndexingPhase2ConversionBoss,		kIndexingPrefix + 60)
DECLARE_PMID(kClassIDSpace, kIndexingDocResponderBoss,			kIndexingPrefix + 61)
//gap
DECLARE_PMID(kClassIDSpace, kIndexScriptProviderBoss,			kIndexingPrefix + 100)
DECLARE_PMID(kClassIDSpace, kTopicScriptProvider40Boss,			kIndexingPrefix + 101)
DECLARE_PMID(kClassIDSpace, kIndexOptionsScriptProviderBoss,	kIndexingPrefix + 102)
DECLARE_PMID(kClassIDSpace, kPageRefScriptObjectBoss,			kIndexingPrefix + 103)
DECLARE_PMID(kClassIDSpace, kPageRefScriptProviderBoss,			kIndexingPrefix + 104)
DECLARE_PMID(kClassIDSpace, kCrossRefScriptObjectBoss,			kIndexingPrefix + 105)
DECLARE_PMID(kClassIDSpace, kCrossRefScriptProviderBoss,		kIndexingPrefix + 106)
DECLARE_PMID(kClassIDSpace, kTopicScriptObjectBoss,				kIndexingPrefix + 107)
DECLARE_PMID(kClassIDSpace, kTopicScriptProviderBoss,			kIndexingPrefix + 108)
DECLARE_PMID(kClassIDSpace, kSubtopicScriptObjectBoss,			kIndexingPrefix + 109)
DECLARE_PMID(kClassIDSpace, kSubtopicScriptProviderBoss,		kIndexingPrefix + 110)
DECLARE_PMID(kClassIDSpace, kIndexingTextModelMementoBoss,		kIndexingPrefix + 111)
DECLARE_PMID(kClassIDSpace, kIndexSectionScriptProviderBoss,	kIndexingPrefix + 112)
DECLARE_PMID(kClassIDSpace, kIndexInstanceScriptProviderBoss,	kIndexingPrefix + 113)
DECLARE_PMID(kClassIDSpace, kIndexHeaderSetScriptProviderBoss,	kIndexingPrefix + 114)
DECLARE_PMID(kClassIDSpace, kIndexingSortOptionScriptProviderBoss,	kIndexingPrefix + 115)
DECLARE_PMID(kClassIDSpace, kIndexingSortOptionProxyScriptBoss,	kIndexingPrefix + 116)

// <Widget ID>
// Widget IDs

// <Implementation ID>
// Implementation IDs
// gap
DECLARE_PMID(kImplementationIDSpace, kIndexTopicListListImpl,			kIndexingPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kIndexInstanceImpl,				kIndexingPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kIndexTopicListImpl,				kIndexingPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kIndexTopicSectionImpl,			kIndexingPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kIndexTopicNodeListImpl,			kIndexingPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kIndexEntryDataImpl,				kIndexingPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kIndexPageEntryDataImpl,			kIndexingPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kIndexPageEntryScrapImpl,			kIndexingPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kIndexXRefEntryDataImpl,			kIndexingPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kIndexXRefLinkDataImpl,			kIndexingPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kSetFormatOptionsCmdImpl,			kIndexingPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kIndexHeaderSetImpl,				kIndexingPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kSessionIndexOptionsImpl,			kIndexingPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kDocIndexOptionsImpl,				kIndexingPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kCreateTopicListCmdImpl,			kIndexingPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kCreateTopicListCmdDataImpl,		kIndexingPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kDeleteTopicListCmdImpl,			kIndexingPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kDeleteTopicListCmdDataImpl,		kIndexingPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kUpdateSelectedIndexStoryImpl,		kIndexingPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kIndexingDataSuiteLayoutCSBImpl,	kIndexingPrefix + 22)
//gap
DECLARE_PMID(kImplementationIDSpace, kInsertIndexMarkCmdImpl,			kIndexingPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kInsertIndexMarkCmdDataImpl,		kIndexingPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kTAIndexMarkReportImpl,			kIndexingPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kTextAdornmentIndexMarkImpl,		kIndexingPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kCreateTopicEntryCmdImpl,			kIndexingPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kCreateTopicEntryCmdDataImpl,		kIndexingPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kDeleteTopicEntryCmdImpl,			kIndexingPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kDeleteTopicEntryCmdDataImpl,		kIndexingPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kCreateIndexPageEntryCmdImpl,		kIndexingPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kIndexPageEntryCmdDataImpl,		kIndexingPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kCreateIndexPageEntryCmdDataImpl,	kIndexingPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kEditIndexPageEntryCmdImpl,		kIndexingPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kDeleteIndexPageEntryCmdImpl,		kIndexingPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kDeleteIndexPageEntryCmdDataImpl,	kIndexingPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kSelectIndexPageEntryCmdImpl,		kIndexingPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kCreateIndexXRefEntryCmdImpl,		kIndexingPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kIndexXRefEntryCmdDataImpl,		kIndexingPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kCreateIndexXRefEntryCmdDataImpl,	kIndexingPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kEditIndexXRefEntryCmdImpl,		kIndexingPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kDeleteIndexXRefEntryCmdImpl,		kIndexingPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kDeleteIndexXRefEntryCmdDataImpl,	kIndexingPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kCopyIndexPageEntryCmdImpl,		kIndexingPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kCopyIndexPageEntryCmdDataImpl,	kIndexingPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kUpdatePageEntryCmdImpl,			kIndexingPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kUpdateIndexCmdImpl,				kIndexingPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kGenerateIndexCmdImpl,				kIndexingPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kIndexCmdDataImpl,					kIndexingPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kIndexOptionsImpl,					kIndexingPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kImportTopicsCmdImpl,				kIndexingPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kIndexingStartupShutdownImpl,		kIndexingPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kIndexingContextObserverImpl,		kIndexingPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kActiveTopicListContextImpl,		kIndexingPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kIndexingDocObserverImpl,			kIndexingPrefix + 57)
//gap
DECLARE_PMID(kImplementationIDSpace, kSetActiveTopicListScopeCmdImpl,	kIndexingPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kIndexTopicListComponentsImpl,		kIndexingPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kAttachTopicListCmdImpl,			kIndexingPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kAttachTopicListCmdDataImpl,		kIndexingPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kDetachTopicListCmdImpl,			kIndexingPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kEditTopicEntryCmdImpl,			kIndexingPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kEditTopicEntryCmdDataImpl,		kIndexingPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kCapitalizeTopicEntryCmdImpl,		kIndexingPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kCapitalizeTopicEntryCmdDataImpl,	kIndexingPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kCreateIndexInstanceCmdImpl,		kIndexingPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kInstanceCmdDataImpl,				kIndexingPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kIndexingErrorStringServiceImpl,	kIndexingPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kRemoveIndexInstanceCmdImpl,		kIndexingPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kIndexInstanceListImpl,			kIndexingPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kPlaceIndexCmdImpl,				kIndexingPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kIndexDataLinkProviderImpl,		kIndexingPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kIndexDataLinkServiceImpl,			kIndexingPrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kIndexDataLinkHelperImpl,			kIndexingPrefix + 77)
DECLARE_PMID(kImplementationIDSpace, kAttachIndexDataLinkCmdImpl,		kIndexingPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kRemoveIndexDataLinkCmdImpl,		kIndexingPrefix + 79)
DECLARE_PMID(kImplementationIDSpace, kIdxDataLinkUIDDataImpl,			kIndexingPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kIdxStoryUIDDataImpl,				kIndexingPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kIdxInstanceUIDDataImpl,			kIndexingPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kIndexOwnedItemImpl,				kIndexingPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kIndexingContextCmdDataImpl,		kIndexingPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kRemoveUnusedTopicsCmdImpl,		kIndexingPrefix + 85)
DECLARE_PMID(kImplementationIDSpace, kRemoveUnusedTopicsCmdDataImpl,	kIndexingPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kChangeIndexHeaderSetCmdImpl,		kIndexingPrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kChangeIndexHeaderSetCmdDataImpl,	kIndexingPrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kIndexingUtilsPublicImpl,			kIndexingPrefix + 89)
DECLARE_PMID(kImplementationIDSpace, kIndexingCmdSelectionDataImpl,		kIndexingPrefix + 90)
DECLARE_PMID(kImplementationIDSpace, kIndexingHSHandlerServiceImpl,		kIndexingPrefix + 91)
DECLARE_PMID(kImplementationIDSpace, kIndexingRomanHSHandlerImpl,		kIndexingPrefix + 92)
DECLARE_PMID(kImplementationIDSpace, kIndexingJapaneseHSHandlerImpl,	kIndexingPrefix + 93)
DECLARE_PMID(kImplementationIDSpace, kIndexingIteratorRegImpl,			kIndexingPrefix + 94)
DECLARE_PMID(kImplementationIDSpace, kIdxInstancePersistUIDDataImpl,	kIndexingPrefix + 95)
DECLARE_PMID(kImplementationIDSpace, kIndexingNewWSResponderImpl,		kIndexingPrefix + 96)
DECLARE_PMID(kImplementationIDSpace, kIndexingAllHSHandlerImpl,			kIndexingPrefix + 97)
DECLARE_PMID(kImplementationIDSpace, kChangeIndexHeaderSetMasterCmdImpl,kIndexingPrefix + 98)

DECLARE_PMID(kImplementationIDSpace, kIndexScriptImpl,					kIndexingPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kIndexInstanceScriptProviderImpl,	kIndexingPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kIndexScriptProviderImpl,			kIndexingPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kIndexOptionsScriptProviderImpl,	kIndexingPrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kIndexSectionScriptImpl,			kIndexingPrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kIndexSectionScriptProviderImpl,	kIndexingPrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kPageRefScriptProviderImpl,		kIndexingPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kIndexRIDXNotifierHandlerImpl,		kIndexingPrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kPageRefScriptImpl,				kIndexingPrefix + 108)
DECLARE_PMID(kImplementationIDSpace, kCrossRefScriptProviderImpl,		kIndexingPrefix + 109)
//gap
DECLARE_PMID(kImplementationIDSpace, kCrossRefScriptImpl,				kIndexingPrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kTopicScriptProviderImpl,			kIndexingPrefix + 112)
DECLARE_PMID(kImplementationIDSpace, kTopicScriptProvider40Impl,		kIndexingPrefix + 113)
//gap
DECLARE_PMID(kImplementationIDSpace, kSubtopicScriptProviderImpl,		kIndexingPrefix + 115)
//gap
DECLARE_PMID(kImplementationIDSpace, kIndexingTextModelMementoImpl,		kIndexingPrefix + 119)
DECLARE_PMID(kImplementationIDSpace, kIndexScriptTopicEntryImpl,		kIndexingPrefix + 120)
DECLARE_PMID(kImplementationIDSpace, kIndexSubtopicEntryNodeImpl,		kIndexingPrefix + 121)
DECLARE_PMID(kImplementationIDSpace, kIndexInstanceScriptImpl,			kIndexingPrefix + 122)
DECLARE_PMID(kImplementationIDSpace, kTopicScriptImpl,					kIndexingPrefix + 123)
DECLARE_PMID(kImplementationIDSpace, kSubtopicScriptImpl,				kIndexingPrefix + 124)
DECLARE_PMID(kImplementationIDSpace, kIndexHeaderSetScriptProviderImpl, kIndexingPrefix + 125)
DECLARE_PMID(kImplementationIDSpace, kIndexingHeaderSetMasterImpl,		kIndexingPrefix + 126)
DECLARE_PMID(kImplementationIDSpace, kIndexingPhase2ConversionImpl,		kIndexingPrefix + 127)
DECLARE_PMID(kImplementationIDSpace, kIndexingDocResponderImpl,			kIndexingPrefix + 128)
DECLARE_PMID(kImplementationIDSpace, kIndexingDocServiceProviderImpl,	kIndexingPrefix + 129)
DECLARE_PMID(kImplementationIDSpace, kIndexingSortOptionScriptProviderImpl,	kIndexingPrefix + 130)
DECLARE_PMID(kImplementationIDSpace, kIndexingSortOptionProxyScriptImpl,	kIndexingPrefix + 131)

// <Interface ID>
// IIDs
//DECLARE_PMID(kInterfaceIDSpace, IID_IINDEXINGMANAGER,				kIndexingPrefix + 1) never used
DECLARE_PMID(kInterfaceIDSpace, IID_IINDEXTOPICLISTLIST,			kIndexingPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IINDEXINSTANCE,					kIndexingPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IINDEXTOPICLIST,				kIndexingPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IINDEXTOPICSECTION,				kIndexingPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IINDEXTOPICNODELIST,			kIndexingPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IINDEXENTRYDATA,				kIndexingPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IINDEXPAGEENTRYDATA,			kIndexingPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IINDEXXREFENTRYDATA,			kIndexingPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IINDEXXREFLINKDATA,				kIndexingPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_ICREATEINDEXCMDDATA,			kIndexingPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IDELETEINDEXCMDDATA,			kIndexingPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_ICREATETOPICLISTCMDDATA,		kIndexingPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IDELETETOPICLISTCMDDATA,		kIndexingPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_ICREATETOPICSECTIONCMDDATA,		kIndexingPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IDELETETOPICSECTIONCMDDATA,		kIndexingPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IINSERTINDEXMARKCMDDATA,		kIndexingPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_ICREATETOPICENTRYCMDDATA,		kIndexingPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_IDELETETOPICENTRYCMDDATA,		kIndexingPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_IINDEXPAGEENTRYCMDDATA,			kIndexingPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_ICREATEINDEXPAGEENTRYCMDDATA,	kIndexingPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_IDELETEINDEXPAGEENTRYCMDDATA,	kIndexingPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_IINDEXXREFENTRYCMDDATA,			kIndexingPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_ICREATEINDEXXREFENTRYCMDDATA,	kIndexingPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_IDELETEINDEXXREFENTRYCMDDATA,	kIndexingPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOPYINDEXPAGEENTRYCMDDATA,		kIndexingPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_IINDEXCMDDATA,					kIndexingPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_IINDEXOPTIONS,					kIndexingPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_INDEXINGCONTEXTOBSERVER,		kIndexingPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_IACTIVETOPICLISTCONTEXT,		kIndexingPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_IINDEXINGDOCOBSERVER,			kIndexingPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_IINDEXTOPICLISTCOMPONENTS,		kIndexingPrefix + 32)
DECLARE_PMID(kInterfaceIDSpace, IID_IATTACHTOPICLISTCMDDATA,		kIndexingPrefix + 33)
DECLARE_PMID(kInterfaceIDSpace, IID_IEDITTOPICENTRYCMDDATA,			kIndexingPrefix + 34)
DECLARE_PMID(kInterfaceIDSpace, IID_ICAPITALIZETOPICENTRYCMDDATA,	kIndexingPrefix + 35)

DECLARE_PMID(kInterfaceIDSpace, IID_IINDEXINSTANCELIST,				kIndexingPrefix + 36)
DECLARE_PMID(kInterfaceIDSpace, IID_IINSTANCECMDDATA,				kIndexingPrefix + 37)
DECLARE_PMID(kInterfaceIDSpace, IID_IINDEXDATALINKHELPER,			kIndexingPrefix + 38)
DECLARE_PMID(kInterfaceIDSpace, IID_IIDXDATALINKUIDDATA,			kIndexingPrefix + 39)
DECLARE_PMID(kInterfaceIDSpace, IID_IIDXSTORYUIDDATA,				kIndexingPrefix + 40)
DECLARE_PMID(kInterfaceIDSpace, IID_IIDXINSTANCEUIDDATA,			kIndexingPrefix + 41)
DECLARE_PMID(kInterfaceIDSpace, IID_IINDEXINGCONTEXTCMDDATA,		kIndexingPrefix + 42)
DECLARE_PMID(kInterfaceIDSpace, IID_IREMOVEUNUSEDTOPICSCMDDATA,		kIndexingPrefix + 43)
DECLARE_PMID(kInterfaceIDSpace, IID_ICHANGEINDEXHEADERSETCMDDATA,	kIndexingPrefix + 44)
DECLARE_PMID(kInterfaceIDSpace, IID_IINDEXHEADERSET,				kIndexingPrefix + 45)
DECLARE_PMID(kInterfaceIDSpace, IID_IINDEXINGUTILSPUBLIC,			kIndexingPrefix + 46)
DECLARE_PMID(kInterfaceIDSpace, IID_IINDEXINGCMDSELECTIONDATA,		kIndexingPrefix + 47)
DECLARE_PMID(kInterfaceIDSpace, IID_IUPDATESELECTEDINDEXSTORY,		kIndexingPrefix + 48)	// Free to reuse
DECLARE_PMID(kInterfaceIDSpace, IID_IINDEXINGHEADERSETHANDLER,		kIndexingPrefix + 49)
DECLARE_PMID(kInterfaceIDSpace, IID_IIDXINSTANCEPERSISTUIDDATA,		kIndexingPrefix + 50)
DECLARE_PMID(kInterfaceIDSpace, IID_IINDEXSCRIPTTOPICENTRY,			kIndexingPrefix + 51)
DECLARE_PMID(kInterfaceIDSpace, IID_IINDEXSUBTOPICENTRYNODE,		kIndexingPrefix + 52)
DECLARE_PMID(kInterfaceIDSpace, IID_IINDEXINGHEADERSETMASTER,		kIndexingPrefix + 53)
DECLARE_PMID(kInterfaceIDSpace, IID_IINDEXPAGEENTRYUNIQUEID,		kIndexingPrefix + 54)

// <Message ID>
DECLARE_PMID(kMessageIDSpace, IID_IDX_NEW_ACTIVE_TOPICLIST_MSG,		kIndexingPrefix + 1)
DECLARE_PMID(kMessageIDSpace, IID_IDX_ACTIVE_TOPICLIST_CHANGED_MSG,	kIndexingPrefix + 2)
DECLARE_PMID(kMessageIDSpace, IID_IDX_ACTIVE_BOOKCONTEXT_CHANGED_MSG,kIndexingPrefix + 3)

// <Error ID>
// Error Codes
DECLARE_PMID(kErrorIDSpace, kInvalidDataPageEntryError,			kIndexingPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kInvalidDataXRefError,				kIndexingPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kInvalidRefedDataXRefError,			kIndexingPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kRecursiveXRefError,				kIndexingPrefix + 4)
DECLARE_PMID(kErrorIDSpace, kImportTopicsError,					kIndexingPrefix + 5)
DECLARE_PMID(kErrorIDSpace, kInvalidCapitalizeOptionError,		kIndexingPrefix + 6)
DECLARE_PMID(kErrorIDSpace, kStoryLockedError,					kIndexingPrefix + 7)
DECLARE_PMID(kErrorIDSpace, kGenerateIndexError,				kIndexingPrefix + 8)
DECLARE_PMID(kErrorIDSpace, kInvalidIndexOptionsSeparatorsError, kIndexingPrefix + 9)
DECLARE_PMID(kErrorIDSpace, kDocMissingFromBookError, 		kIndexingPrefix + 10)


// <Service ID>
DECLARE_PMID(kServiceIDSpace, kIndexingHeaderSetHandlerService,	kIndexingPrefix + 1)

// <Action ID>

//
//Script Element IDs
//

//Suites
DECLARE_PMID(kScriptInfoIDSpace, kIndexingSuiteScriptElement,							kIndexingPrefix + 1)

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kIndexObjectScriptElement,								kIndexingPrefix + 20)
DECLARE_PMID(kScriptInfoIDSpace, kIndexOptionsObjectScriptElement,						kIndexingPrefix + 21)
DECLARE_PMID(kScriptInfoIDSpace, kTopicObjectScriptElement,								kIndexingPrefix + 22)
DECLARE_PMID(kScriptInfoIDSpace, kSubtopicObjectScriptElement,							kIndexingPrefix + 23)
DECLARE_PMID(kScriptInfoIDSpace, kCrossReferenceObjectScriptElement,					kIndexingPrefix + 24)
DECLARE_PMID(kScriptInfoIDSpace, kPageReferenceObjectScriptElement,						kIndexingPrefix + 25)
DECLARE_PMID(kScriptInfoIDSpace, kIndexSectionObjectScriptElement,						kIndexingPrefix + 26)
DECLARE_PMID(kScriptInfoIDSpace, kIndexInstanceObjectScriptElement,						kIndexingPrefix + 27)
DECLARE_PMID(kScriptInfoIDSpace, kIndexHeaderSetObjectScriptElement,					kIndexingPrefix + 28)
DECLARE_PMID(kScriptInfoIDSpace, kIndexingSortOptionObjectScriptElement,				kIndexingPrefix + 29)

//Events
DECLARE_PMID(kScriptInfoIDSpace, kImportTopicsMethodScriptElement,						kIndexingPrefix + 81)
DECLARE_PMID(kScriptInfoIDSpace, kRemoveUnusedTopicsMethodScriptElement,					kIndexingPrefix + 82)
DECLARE_PMID(kScriptInfoIDSpace, kCapitalizeMethodScriptElement,							kIndexingPrefix + 83)
DECLARE_PMID(kScriptInfoIDSpace, kUpdateIndexMethodScriptElement,						kIndexingPrefix + 84)
DECLARE_PMID(kScriptInfoIDSpace, kGenerateIndexMethodScriptElement,						kIndexingPrefix + 85)
DECLARE_PMID(kScriptInfoIDSpace, kCreateTopicMethodScriptElement,						kIndexingPrefix + 86)
DECLARE_PMID(kScriptInfoIDSpace, kCreateSubtopicMethodScriptElement,						kIndexingPrefix + 87)
DECLARE_PMID(kScriptInfoIDSpace, kMoveTopicMethodScriptElement,							kIndexingPrefix + 88)
DECLARE_PMID(kScriptInfoIDSpace, kCreateCrossReferenceMethodScriptElement,				kIndexingPrefix + 89)
DECLARE_PMID(kScriptInfoIDSpace, kCreatePageReferenceMethodScriptElement,				kIndexingPrefix + 90)

//Typedefs
DECLARE_PMID(kScriptInfoIDSpace, kIndexHeaderGroupTypeDefScriptElement,					kIndexingPrefix + 100)
DECLARE_PMID(kScriptInfoIDSpace, kSectionHeaderTypeDefScriptElement,					kIndexingPrefix + 101)
DECLARE_PMID(kScriptInfoIDSpace, kIndexInstanceTypeDefScriptElement,					kIndexingPrefix + 102)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kIndexOptionsPropertyScriptElement,					kIndexingPrefix + 120)
DECLARE_PMID(kScriptInfoIDSpace, kTitleNamePropertyScriptElement,						kIndexingPrefix + 121)
DECLARE_PMID(kScriptInfoIDSpace, kTitleStylePropertyScriptElement,						kIndexingPrefix + 122)
DECLARE_PMID(kScriptInfoIDSpace, kReplaceExistingIndexPropertyScriptElement,			kIndexingPrefix + 123)
DECLARE_PMID(kScriptInfoIDSpace, kIncludeBookDocumentsPropertyScriptElement,			kIndexingPrefix + 124)
DECLARE_PMID(kScriptInfoIDSpace, kIncludeHiddenEntriesPropertyScriptElement,			kIndexingPrefix + 125)
DECLARE_PMID(kScriptInfoIDSpace, kIndexFormatPropertyScriptElement,						kIndexingPrefix + 126)
DECLARE_PMID(kScriptInfoIDSpace, kIncludeSectionHeadingsPropertyScriptElement,			kIndexingPrefix + 127)
DECLARE_PMID(kScriptInfoIDSpace, kIncludeEmptyIndexSectionsPropertyScriptElement,		kIndexingPrefix + 128)
DECLARE_PMID(kScriptInfoIDSpace, kLevel1StylePropertyScriptElement,						kIndexingPrefix + 129)
DECLARE_PMID(kScriptInfoIDSpace, kLevel2StylePropertyScriptElement,						kIndexingPrefix + 130)
DECLARE_PMID(kScriptInfoIDSpace, kLevel3StylePropertyScriptElement,						kIndexingPrefix + 131)
DECLARE_PMID(kScriptInfoIDSpace, kLevel4StylePropertyScriptElement,						kIndexingPrefix + 132)
DECLARE_PMID(kScriptInfoIDSpace, kSectionHeadingStylePropertyScriptElement,				kIndexingPrefix + 133)
DECLARE_PMID(kScriptInfoIDSpace, kIndexPageNumberStylePropertyScriptElement,			kIndexingPrefix + 134)
DECLARE_PMID(kScriptInfoIDSpace, kCrossReferenceStylePropertyScriptElement,				kIndexingPrefix + 135)
DECLARE_PMID(kScriptInfoIDSpace, kCrossReferenceTopicStylePropertyScriptElement,		kIndexingPrefix + 136)
DECLARE_PMID(kScriptInfoIDSpace, kFollowingTopicSeparatorPropertyScriptElement,			kIndexingPrefix + 137)
DECLARE_PMID(kScriptInfoIDSpace, kBetweenEntriesSeparatorPropertyScriptElement,			kIndexingPrefix + 138)
DECLARE_PMID(kScriptInfoIDSpace, kPageRangeSeparatorPropertyScriptElement,				kIndexingPrefix + 139)
DECLARE_PMID(kScriptInfoIDSpace, kBetweenPageNumbersSeparatorPropertyScriptElement,		kIndexingPrefix + 140)
DECLARE_PMID(kScriptInfoIDSpace, kBeforeCrossReferenceSeparatorPropertyScriptElement,	kIndexingPrefix + 141)
DECLARE_PMID(kScriptInfoIDSpace, kEntryEndSeparatorPropertyScriptElement,				kIndexingPrefix + 142)
DECLARE_PMID(kScriptInfoIDSpace, kSortOrderPropertyScriptElement,						kIndexingPrefix + 143)
DECLARE_PMID(kScriptInfoIDSpace, kReferencedTopicPropertyScriptElement,					kIndexingPrefix + 144)
DECLARE_PMID(kScriptInfoIDSpace, kCrossReferenceTypePropertyScriptElement,				kIndexingPrefix + 145)
DECLARE_PMID(kScriptInfoIDSpace, kCustomTypeStringPropertyScriptElement,				kIndexingPrefix + 146)
DECLARE_PMID(kScriptInfoIDSpace, kPageReferenceTypePropertyScriptElement,				kIndexingPrefix + 147)
DECLARE_PMID(kScriptInfoIDSpace, kPageReferenceLimitPropertyScriptElement,				kIndexingPrefix + 148)
DECLARE_PMID(kScriptInfoIDSpace, kPageNumberStyleOverridePropertyScriptElement,			kIndexingPrefix + 149)
DECLARE_PMID(kScriptInfoIDSpace, kIndexInstanceListPropertyScriptElement,				kIndexingPrefix + 150)
DECLARE_PMID(kScriptInfoIDSpace, kAllTopicsPropertyScriptElement,						kIndexingPrefix + 151)
DECLARE_PMID(kScriptInfoIDSpace, kIndexInstancePropertyScriptElement,					kIndexingPrefix + 152)
DECLARE_PMID(kScriptInfoIDSpace, kIndexHeaderSetPropertyScriptElement,					kIndexingPrefix + 153)
DECLARE_PMID(kScriptInfoIDSpace, kIndexHeaderSetNamePropertyScriptElement,				kIndexingPrefix + 154)
DECLARE_PMID(kScriptInfoIDSpace, kIndexHeaderSetLanguagePropertyScriptElement,			kIndexingPrefix + 155)
DECLARE_PMID(kScriptInfoIDSpace, kIndexHeaderSetHandlerClassPropertyScriptElement,		kIndexingPrefix + 156)
DECLARE_PMID(kScriptInfoIDSpace, kIndexHeaderSetGroupValuePropertyScriptElement,		kIndexingPrefix + 157)
DECLARE_PMID(kScriptInfoIDSpace, kIndexHeaderSetGroupOptionValuePropertyScriptElement,	kIndexingPrefix + 158)
DECLARE_PMID(kScriptInfoIDSpace, kIndexHeaderSetGroupListPropertyScriptElement,			kIndexingPrefix + 159)
DECLARE_PMID(kScriptInfoIDSpace, kIndexingSortOptionIncludeScriptElement,				kIndexingPrefix + 160)
DECLARE_PMID(kScriptInfoIDSpace, kIndexingSortOptionPriorityScriptElement,				kIndexingPrefix + 161)
DECLARE_PMID(kScriptInfoIDSpace, kIndexingSortOptionHeaderTypePropertyScriptElement,	kIndexingPrefix + 162)
DECLARE_PMID(kScriptInfoIDSpace, kIndexMarkerUniqueIDPropertyScriptElement,				kIndexingPrefix + 163)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kIndexCapitalizationOptionsEnumScriptElement,			kIndexingPrefix + 220)
DECLARE_PMID(kScriptInfoIDSpace, kIndexFormatEnumScriptElement,							kIndexingPrefix + 221)
DECLARE_PMID(kScriptInfoIDSpace, kCrossReferenceTypeEnumScriptElement,					kIndexingPrefix + 222)
DECLARE_PMID(kScriptInfoIDSpace, kPageReferenceTypeEnumScriptElement,					kIndexingPrefix + 223)
DECLARE_PMID(kScriptInfoIDSpace, kIndexingSortOptionHeaderTypeEnumScriptElement,		kIndexingPrefix + 224)

//Metadata
DECLARE_PMID(kScriptInfoIDSpace, kIndexingSortOptionINXPolicies50ScriptElement,			kIndexingPrefix + 240)

enum IndexingScriptIDs
{
	t_IndexHeaderGroupType		= 'IHGT',
	t_SectionHeaderType			= 'SEHT',
	t_IndexInstanceType			= 'INIT',
};

// InvalHandler
DECLARE_PMID(kInvalHandlerIDSpace, kActiveTopicListContextInvalHandlerID,				kIndexingPrefix + 1)

#endif	// __IndexingID__

