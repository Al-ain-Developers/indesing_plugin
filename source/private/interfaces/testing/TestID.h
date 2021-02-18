//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/private/interfaces/testing/TestID.h $
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
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#ifndef __TestID__
#define __TestID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

//Prefixes 0xD9 through 0xDE are reserved for testing.  They were needed at one time in
//order to allocate ActionIDs for tests listed on the QA menu.  0xD9 and 0xDE are still
//used here; 0xDA and 0xDB are used in QAMenuID.h; 0xDC is used in TestLibPluginID.h.

#define kTestingPrefix	 RezLong(0xD900)
//#define kTestingPrefix	 RezLong(0xDA00) //Used in QAMenuID.h
//#define kTestingPrefix	 RezLong(0xDB00) //Used in QAMenuID.h
//#define kTestingPrefix	 RezLong(0xDC00) //Used by TestUILib & plugin
//#define kTestingPrefix	 RezLong(0xDD00) //Used by TestPanel
#define kTestingPrefixE	 RezLong(0xDE00)

// converter stuff
#define kLastTestingFormatChg	RezLong(427)

// <Start IDC>
// PluginIDs
#define kTestLibPluginName 							"TestLibPlugin"
DECLARE_PMID(kPlugInIDSpace, kTestLibPluginID, kTestingPrefix + 1)

#define kInvalToolPluginName 						"InvalTool"
DECLARE_PMID(kPlugInIDSpace, kInvalToolPluginID, kTestingPrefix + 2)

#define kTestProviderPluginName 						"TestProvider"
DECLARE_PMID(kPlugInIDSpace, kTestProviderPluginID, kTestingPrefix + 5)

// <Class ID>
//******CLASS IDs
DECLARE_PMID(kClassIDSpace, kUnregisteredTestSuiteBoss_obsolete, 	kTestingPrefix + 0)
DECLARE_PMID(kClassIDSpace, kCTestSuiteBoss, 						kTestingPrefix + 1)
DECLARE_PMID(kClassIDSpace, kReadPixMapImageStreamTestBoss, 		kTestingPrefix + 2)
DECLARE_PMID(kClassIDSpace, kTestSuiteListenerContainerBoss, 		kTestingPrefix + 3)
DECLARE_PMID(kClassIDSpace, kQASetErrorsStartupShutdownBoss,		kTestingPrefix + 4)
DECLARE_PMID(kClassIDSpace, kQASetErrorsBeforeSaveDocResponderBoss, kTestingPrefix + 5)
DECLARE_PMID(kClassIDSpace, kQASetErrorsAfterSaveDocResponderBoss,  kTestingPrefix + 6)
DECLARE_PMID(kClassIDSpace, kQASetErrorsBeforeSaveAsResponderBoss,  kTestingPrefix + 7)
DECLARE_PMID(kClassIDSpace, kQASetErrorsAfterSaveAsResponderBoss,   kTestingPrefix + 8)
DECLARE_PMID(kClassIDSpace, kTestLibPluginIteratorRegBoss, 			kTestingPrefix + 9)
//gap
DECLARE_PMID(kClassIDSpace, kTestServiceBoss, 						kTestingPrefix + 11)
DECLARE_PMID(kClassIDSpace, kInvalToolBoss, 						kTestingPrefix + 12)
DECLARE_PMID(kClassIDSpace, kInvalToolTrackerBoss, 					kTestingPrefix + 13)
DECLARE_PMID(kClassIDSpace, kInvalTrackerRegisterBoss, 				kTestingPrefix + 14)
DECLARE_PMID(kClassIDSpace, kQATestIdleTaskBoss, 					kTestingPrefix + 15)
DECLARE_PMID(kClassIDSpace, kQASetErrorsBeforeCloseDocResponderBoss,kTestingPrefix + 16)
DECLARE_PMID(kClassIDSpace, kQASetErrorsAfterCloseDocResponderBoss, kTestingPrefix + 17)
DECLARE_PMID(kClassIDSpace, kQADocumentObserverBoss, 				kTestingPrefix + 18)
DECLARE_PMID(kClassIDSpace, kInvalToolRegisterBoss, 				kTestingPrefix + 19)
//gap
DECLARE_PMID(kClassIDSpace, kBenchmarkSuiteBoss_Obsolete, 			kTestingPrefix + 22)
DECLARE_PMID(kClassIDSpace, kBenchmarkReorgSuiteBoss_obsolete, 				kTestingPrefix + 23)
DECLARE_PMID(kClassIDSpace, kQAGoesNowhereDoesNothingClassID, 		kTestingPrefix + 24)
DECLARE_PMID(kClassIDSpace, kTestPagedSetStorageBoss, 				kTestingPrefix + 25)
DECLARE_PMID(kClassIDSpace, kCmdListRetreiverBoss, 					kTestingPrefix + 26)
DECLARE_PMID(kClassIDSpace, kTestPagedMapStorageBoss, 				kTestingPrefix + 27)
DECLARE_PMID(kClassIDSpace, kQATestLogBoss, 						kTestingPrefix + 28)
DECLARE_PMID(kClassIDSpace, kQAXMLTestLogBoss, 						kTestingPrefix + 29)
DECLARE_PMID(kClassIDSpace, kQAThreadingLogBoss,	 				kTestingPrefix + 30)
DECLARE_PMID(kClassIDSpace, kTestRunnerBoss, 							kTestingPrefix + 31)
//gap
DECLARE_PMID(kClassIDSpace, kTestStartupShutdownBoss, 				kTestingPrefix + 32)
//gap
DECLARE_PMID(kClassIDSpace, kRunScriptIdleTaskBoss, 				kTestingPrefix + 34)
//gap
DECLARE_PMID(kClassIDSpace, kQAAlertHandlerBoss, 					kTestingPrefix + 36)
DECLARE_PMID(kClassIDSpace, kDataBaseObserverBoss, 					kTestingPrefix + 37)
DECLARE_PMID(kClassIDSpace, kSetTestPrefsCmdBoss, 					kTestingPrefix + 38)
DECLARE_PMID(kClassIDSpace, kSetBenchPrefsCmdBoss, 					kTestingPrefix + 39)
DECLARE_PMID(kClassIDSpace, kCommandCoverageCmdBoss, 				kTestingPrefix + 40)
DECLARE_PMID(kClassIDSpace, kQASessionLogResponderBoss, 			kTestingPrefix + 41)
DECLARE_PMID(kClassIDSpace, kBeginSuiteSignalBoss, 					kTestingPrefix + 42)
//gap
DECLARE_PMID(kClassIDSpace, kDocDBObserverBoss, 					kTestingPrefix + 44)
DECLARE_PMID(kClassIDSpace, kQAListenerRegistryBoss, 				kTestingPrefix + 45)
DECLARE_PMID(kClassIDSpace, kCrashListenerContainerBoss, 			kTestingPrefix + 46)
DECLARE_PMID(kClassIDSpace, kCleanupListenerContainerBoss, 			kTestingPrefix + 47)
DECLARE_PMID(kClassIDSpace, kAlertListenerContainerBoss, 			kTestingPrefix + 48)
DECLARE_PMID(kClassIDSpace, kAssertListenerContainerBoss, 			kTestingPrefix + 49)
DECLARE_PMID(kClassIDSpace, kQAScriptListenerContainerBoss, 		kTestingPrefix + 50)
DECLARE_PMID(kClassIDSpace, kSteppingListenerContainerBoss, 		kTestingPrefix + 51)
DECLARE_PMID(kClassIDSpace, kNewQATestProviderBoss, 				kTestingPrefix + 52)
DECLARE_PMID(kClassIDSpace, kNewMastersTestProviderBoss, 			kTestingPrefix + 53)
DECLARE_PMID(kClassIDSpace, kNewSpreadsTestProviderBoss, 			kTestingPrefix + 54)
DECLARE_PMID(kClassIDSpace, kNewSectionsTestProviderBoss, 			kTestingPrefix + 55)
DECLARE_PMID(kClassIDSpace, kNewStandoffTestProviderBoss, 			kTestingPrefix + 56)
DECLARE_PMID(kClassIDSpace, kNewColorTestProviderBoss, 				kTestingPrefix + 57)
DECLARE_PMID(kClassIDSpace, kNewLayersTestProviderBoss, 			kTestingPrefix + 58)
DECLARE_PMID(kClassIDSpace, kNewAutoLayoutTestProviderBoss, 		kTestingPrefix + 59)
DECLARE_PMID(kClassIDSpace, kNewGraphicsTestProviderBoss, 			kTestingPrefix + 60)
DECLARE_PMID(kClassIDSpace, kNewGuidesTestProviderBoss, 			kTestingPrefix + 61)
DECLARE_PMID(kClassIDSpace, kNewMeasurementTestProviderBoss, 		kTestingPrefix + 62)
DECLARE_PMID(kClassIDSpace, kNewStoryTestProviderBoss, 				kTestingPrefix + 63)
DECLARE_PMID(kClassIDSpace, kNewPageItemTestProviderBoss, 			kTestingPrefix + 64)
DECLARE_PMID(kClassIDSpace, kNewTextFrameTestProviderBoss, 			kTestingPrefix + 65)
//DECLARE_PMID(kClassIDSpace, kNewUITestProviderBoss, 				kTestingPrefix + 66)
DECLARE_PMID(kClassIDSpace, kNewLibraryPaletteTestProviderBoss, 	kTestingPrefix + 67)
DECLARE_PMID(kClassIDSpace, kNewScrapTestProviderBoss, 				kTestingPrefix + 68)
DECLARE_PMID(kClassIDSpace, kNewSelectionTestProviderBoss, 			kTestingPrefix + 69)
DECLARE_PMID(kClassIDSpace, kNewMenusTestProviderBoss, 				kTestingPrefix + 70)
DECLARE_PMID(kClassIDSpace, kNewPlugInsTestProviderBoss, 			kTestingPrefix + 71)
DECLARE_PMID(kClassIDSpace, kNewPubsTestProviderBoss, 				kTestingPrefix + 72)
DECLARE_PMID(kClassIDSpace, kNewTransformTestProviderBoss, 			kTestingPrefix + 73)
DECLARE_PMID(kClassIDSpace, kNewPrintTestProviderBoss, 				kTestingPrefix + 74)
//DECLARE_PMID(kClassIDSpace, kOldMinimalSuiteBoss, 					kTestingPrefix + 75)
DECLARE_PMID(kClassIDSpace, kNewConversionTestProviderBoss, 		kTestingPrefix + 76)
DECLARE_PMID(kClassIDSpace, kNewExportTestProviderBoss, 			kTestingPrefix + 77)
DECLARE_PMID(kClassIDSpace, kNewGraphicsImportTestProviderBoss, 	kTestingPrefix + 78)
DECLARE_PMID(kClassIDSpace, kNewSystemsTestProviderBoss, 			kTestingPrefix + 79)
DECLARE_PMID(kClassIDSpace, kNewFindChgTestProviderBoss, 			kTestingPrefix + 80)
DECLARE_PMID(kClassIDSpace, kNewToolTestProviderBoss, 				kTestingPrefix + 81)
DECLARE_PMID(kClassIDSpace, kBasicThreadingTestProviderBoss, 			kTestingPrefix + 82)
DECLARE_PMID(kClassIDSpace, kNewPDFTestProviderBoss, 				kTestingPrefix + 83)
//gap
DECLARE_PMID(kClassIDSpace, kNewDictionaryTestProviderBoss, 		kTestingPrefix + 85)
//gap
DECLARE_PMID(kClassIDSpace, kTestFilteringListenerContainerBoss, 	kTestingPrefix + 87)
DECLARE_PMID(kClassIDSpace, kTablesTestProviderBoss, 				kTestingPrefix + 88)
DECLARE_PMID(kClassIDSpace, kMemoryListenerContainerBoss, 			kTestingPrefix + 89)
//	New QA Test Providers	
DECLARE_PMID(kClassIDSpace, kQADocTestProviderBoss, kTestingPrefix + 90)
DECLARE_PMID(kClassIDSpace, kQAAppTestProviderBoss, kTestingPrefix + 91)
DECLARE_PMID(kClassIDSpace, kQAColorTestProviderBoss, kTestingPrefix + 92)
DECLARE_PMID(kClassIDSpace, kQAGraphicFrameTestProviderBoss, kTestingPrefix + 93)
DECLARE_PMID(kClassIDSpace, kQAGuideTestProviderBoss, kTestingPrefix + 94)
DECLARE_PMID(kClassIDSpace, kQALayersTestProviderBoss, kTestingPrefix + 95)
DECLARE_PMID(kClassIDSpace, kQALibraryTestProviderBoss, kTestingPrefix + 96)
DECLARE_PMID(kClassIDSpace, kQAMastersTestProviderBoss, kTestingPrefix + 97)
DECLARE_PMID(kClassIDSpace, kQAPageTestProviderBoss, kTestingPrefix + 98)
DECLARE_PMID(kClassIDSpace, kQAPageItemTestProviderBoss, kTestingPrefix + 99)
DECLARE_PMID(kClassIDSpace, kQASectionTestProviderBoss, kTestingPrefix + 100)
DECLARE_PMID(kClassIDSpace, kQASplineTestProviderBoss, kTestingPrefix + 101)
DECLARE_PMID(kClassIDSpace, kQASpreadTestProviderBoss, kTestingPrefix + 102)
DECLARE_PMID(kClassIDSpace, kQAStoryTestProviderBoss, kTestingPrefix + 103)
DECLARE_PMID(kClassIDSpace, kQATextFrameTestProviderBoss, kTestingPrefix + 104)
DECLARE_PMID(kClassIDSpace, kQAWindowTestProviderBoss, kTestingPrefix + 105)
DECLARE_PMID(kClassIDSpace, kQAInlineTestProviderBoss, kTestingPrefix + 106)
DECLARE_PMID(kClassIDSpace, kQALinkTestProviderBoss, kTestingPrefix + 107)
DECLARE_PMID(kClassIDSpace, kQABugTestProviderBoss, kTestingPrefix + 108)
DECLARE_PMID(kClassIDSpace, kQATextColumnTestProviderBoss, kTestingPrefix + 109)
DECLARE_PMID(kClassIDSpace, kQAGroupClassTestProviderBoss, kTestingPrefix + 110)
//DECLARE_PMID(kClassIDSpace, kActiveBugSuiteBoss, kTestingPrefix + 111)
DECLARE_PMID(kClassIDSpace, kQAPDFStyleTestProviderBoss, kTestingPrefix + 112)
DECLARE_PMID(kClassIDSpace, kQAPictureTestProviderBoss, kTestingPrefix + 113)
DECLARE_PMID(kClassIDSpace, kQAStyleTestProviderBoss, kTestingPrefix + 114)
DECLARE_PMID(kClassIDSpace, kQATableTestProviderBoss, kTestingPrefix + 115)
DECLARE_PMID(kClassIDSpace, kQARegressionTestProviderBoss, kTestingPrefix + 116)
DECLARE_PMID(kClassIDSpace, kBookTestProviderBoss, kTestingPrefix + 117)
//DECLARE_PMID(kClassIDSpace, kDocsHundBrowserBoss, kTestingPrefix + 118)
DECLARE_PMID(kClassIDSpace, kTestLibPluginErrStringBoss, kTestingPrefix + 119)
DECLARE_PMID(kClassIDSpace,	kParametricFindChangeTestProviderBoss, kTestingPrefix + 120)
DECLARE_PMID(kClassIDSpace,	kParaStrandTestProviderBoss, kTestingPrefix + 121)
DECLARE_PMID(kClassIDSpace, kSUIDSTestProviderBoss, kTestingPrefix + 122)
DECLARE_PMID(kClassIDSpace, kQAXMLTestProviderBoss, kTestingPrefix + 123)
DECLARE_PMID(kClassIDSpace, kZZLastTestProviderBoss, kTestingPrefix + 124)
//DECLARE_PMID(kClassIDSpace, kNewMeasureLineTestProviderBoss, kTestingPrefix + 125)
DECLARE_PMID(kClassIDSpace, kQAMovieTestProviderBoss, kTestingPrefix + 126)
DECLARE_PMID(kClassIDSpace, kQASoundTestProviderBoss, kTestingPrefix + 127)
DECLARE_PMID(kClassIDSpace, kQABookmarkTestProviderBoss, kTestingPrefix + 128)
DECLARE_PMID(kClassIDSpace, kXMLInsertTextCmdBoss, kTestingPrefix + 129)
DECLARE_PMID(kClassIDSpace, kTestMgrReleaseTestsBoss, kTestingPrefix + 130)
DECLARE_PMID(kClassIDSpace, kTestMgrLoadTestsBoss, kTestingPrefix + 131)
DECLARE_PMID(kClassIDSpace, kNewConversionVerifyProviderBoss, kTestingPrefix + 132)
//gap
DECLARE_PMID(kClassIDSpace,	kFindStringIteratorTestProBoss, kTestingPrefix + 134)
DECLARE_PMID(kClassIDSpace,	kQARegressionQuitTestProviderBoss, kTestingPrefix + 135)
DECLARE_PMID(kClassIDSpace, kBossThreadingTestBoss1, kTestingPrefix + 136)
//gap

DECLARE_PMID(kClassIDSpace, kTestLibPluginConversionProviderBoss, kTestingPrefix + 141)
// gap
DECLARE_PMID(kClassIDSpace, kNewHyperlinkTestProviderBoss, kTestingPrefix + 143)
DECLARE_PMID(kClassIDSpace, kSangamImportExportTestProviderBoss, kTestingPrefix + 144)

DECLARE_PMID(kClassIDSpace, kQARootPrefDataBase, kTestingPrefix + 145)
DECLARE_PMID(kClassIDSpace, kTextSnapshotTestProviderBoss, kTestingPrefix + 146)
//DECLARE_PMID(kClassIDSpace, kQAWorkFlowWebDavProviderBoss, kTestingPrefix + 147)
DECLARE_PMID(kClassIDSpace, kNewPDFAndPSTestProviderBoss, kTestingPrefix + 148)
DECLARE_PMID(kClassIDSpace, kStreamingGraphicsPortBoss, kTestingPrefix + 149)
//gap
DECLARE_PMID(kClassIDSpace, kQAPageItemFormFieldTestProviderBoss, kTestingPrefix + 155)
//gap
DECLARE_PMID(kClassIDSpace, kLazyAutomationStartupBoss, kTestingPrefix + 164)
DECLARE_PMID(kClassIDSpace, kAutomationStartupBoss, kTestingPrefix + 165)
DECLARE_PMID(kClassIDSpace, kTestAsyncWorkManager1ProviderBoss, kTestingPrefix + 166)
DECLARE_PMID(kClassIDSpace, kTestAsyncWorkManager2ProviderBoss, kTestingPrefix + 167)
DECLARE_PMID(kClassIDSpace, kTestAsyncWorkManager3ProviderBoss, kTestingPrefix + 168)
//gap
DECLARE_PMID(kClassIDSpace, kRestartTestsCmdBoss, kTestingPrefix + 171)
DECLARE_PMID(kClassIDSpace, kNewObjectStyleTestProviderBoss, kTestingPrefix + 172)
DECLARE_PMID(kClassIDSpace, kQAXMPTestProviderBoss, kTestingPrefix + 173)
DECLARE_PMID(kClassIDSpace, kQASurrogateTestProviderBoss, kTestingPrefix + 174)

DECLARE_PMID(kClassIDSpace, kScriptingTestProviderBoss, kTestingPrefix + 175)
DECLARE_PMID(kClassIDSpace, kBNTestProviderBoss, kTestingPrefix + 176)
DECLARE_PMID(kClassIDSpace, kImageCaptionTestProviderBoss, kTestingPrefix + 177)
//gap
DECLARE_PMID(kClassIDSpace, kTestSetActionRegisterBoss, kTestingPrefix + 181)
DECLARE_PMID(kClassIDSpace, kQAXMLLogResponderBoss, kTestingPrefix + 182)
DECLARE_PMID(kClassIDSpace, kCheckUIDAutoCmdBoss, kTestingPrefix + 183)
//gap
DECLARE_PMID(kClassIDSpace, kTestServiceRegistryWorkerThreadBoss, kTestingPrefix + 184)
DECLARE_PMID(kClassIDSpace, kTestServiceRegistryMainThreadBoss, kTestingPrefix + 185)
DECLARE_PMID(kClassIDSpace, kTestServiceRegistryAnywhereBoss, kTestingPrefix + 186)
// gap
DECLARE_PMID(kClassIDSpace, kQACommandProcessorProxyBoss, kTestingPrefix + 191)
DECLARE_PMID(kClassIDSpace, kBenchmarkReorgTestBoss, kTestingPrefix + 192)
//DECLARE_PMID(kClassIDSpace, kFooBoss, kTestingPrefix + 193)
DECLARE_PMID(kClassIDSpace, kDTITestProviderBoss, kTestingPrefix + 194)
DECLARE_PMID(kClassIDSpace, kSnippetTestProviderBoss, kTestingPrefix + 195)
//gap
DECLARE_PMID(kClassIDSpace, kAATTestProviderBoss, kTestingPrefix + 197)
DECLARE_PMID(kClassIDSpace, kDynamicTestProviderBoss, kTestingPrefix + 198)

//gap
DECLARE_PMID(kClassIDSpace, kTestResultsListenerContainerBoss, 		kTestingPrefix + 200)
DECLARE_PMID(kClassIDSpace, kQAStaticListenerContainerBoss, 		kTestingPrefix + 201)
//gap
DECLARE_PMID(kClassIDSpace, kBenchmarkListenerContainerBoss,	 	kTestingPrefix + 203)
//gap

//gap
DECLARE_PMID(kClassIDSpace, kINXTestProviderBoss, 					kTestingPrefix + 210)
//gap
DECLARE_PMID(kClassIDSpace, kQASerializationTestProviderBoss,   	kTestingPrefix + 213)
DECLARE_PMID(kClassIDSpace, kConditionalTextTestProviderBoss,		kTestingPrefix + 214)
DECLARE_PMID(kClassIDSpace, kQABasicCommandProcessorProxyBoss,		kTestingPrefix + 215)

// <Interface ID>
//******INTERFACE IDs
DECLARE_PMID(kInterfaceIDSpace, IID_ITESTPROVIDER, 				kTestingPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IQAMESSAGEUTILS, 			kTestingPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ITESTPREFS, 				kTestingPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ITESTMGR,					kTestingPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IQALOG, 					kTestingPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMMANDCOVERAGE,		 	kTestingPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IQAINTDATA, 				kTestingPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IBENCHPREFS, 				kTestingPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IBENCHDATA, 				kTestingPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_ITESTSUITE, 				kTestingPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IBENCHGLOBALDATA, 			kTestingPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_ITESTSUITESTATUS, 			kTestingPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IRESTARTTESTSDATA, 			kTestingPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IMAXINTEGERCONTROLDATA, 	kTestingPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IALERTHANDLERDATA, 			kTestingPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IQAPLUGINUTILS, 			kTestingPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IDATABASEOBSERVER, 			kTestingPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_IUNDOAFTERTESTPREFS, 		kTestingPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_IQALOGREGISTRY, 			kTestingPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_IQAASSERTLOG, 				kTestingPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_IQASELECTIONSUITE, 			kTestingPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_ITESTSUITETREEVIEWMGR,	 	kTestingPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_ITESTSUITEPREFSMGR,		 	kTestingPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_IQAFILEDIFFUTILS,			kTestingPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_IQAAPPLESCRIPTUTILS, 		kTestingPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_IQAATTRIBUTEUTILS, 			kTestingPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_IQALISTENERREGISTRY, 		kTestingPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_IQACLASSIFICATIONUTILS,	 	kTestingPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_IQACOLORUTILS, 				kTestingPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_IQATEXTFRAMEUTILS,		 	kTestingPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_IQACONTEXTUTILS, 			kTestingPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_IQALAYOUTSELECTIONUTILS, 	kTestingPrefix + 32)
DECLARE_PMID(kInterfaceIDSpace, IID_IQAOPENTYPEUTILS, 			kTestingPrefix + 33)
DECLARE_PMID(kInterfaceIDSpace, IID_IQAPAGEITEMUTILS, 			kTestingPrefix + 34)
DECLARE_PMID(kInterfaceIDSpace, IID_IQAPROPERTYUTILS, 			kTestingPrefix + 35)
DECLARE_PMID(kInterfaceIDSpace, IID_IQARULEUTILS, 				kTestingPrefix + 36)
DECLARE_PMID(kInterfaceIDSpace, IID_IQASTORYUTILS, 				kTestingPrefix + 37)
DECLARE_PMID(kInterfaceIDSpace, IID_IQASTRINGFILTERUTILS, 		kTestingPrefix + 38)
DECLARE_PMID(kInterfaceIDSpace, IID_IQASTRUCTUREUTILS, 			kTestingPrefix + 39)
DECLARE_PMID(kInterfaceIDSpace, IID_IQASTYLEUTILS, 				kTestingPrefix + 40)
DECLARE_PMID(kInterfaceIDSpace, IID_IQATAGUTILS, 				kTestingPrefix + 41)
DECLARE_PMID(kInterfaceIDSpace, IID_IQASECONDPASSFAKEPREFINTDATA,		kTestingPrefix + 42)
DECLARE_PMID(kInterfaceIDSpace, IID_IQALISTENERCREATOR, 		kTestingPrefix + 43)
DECLARE_PMID(kInterfaceIDSpace, IID_IQAWORKGROUPUTILS, 			kTestingPrefix + 44)
DECLARE_PMID(kInterfaceIDSpace, IID_IQAWGAUTOUISETTINGS, 		kTestingPrefix + 45)
DECLARE_PMID(kInterfaceIDSpace, IID_ITREEMGRXMLCHANDLERDATA, 	kTestingPrefix + 46)
DECLARE_PMID(kInterfaceIDSpace, IID_IQALISTENERCONTAINER, 		kTestingPrefix + 47)
DECLARE_PMID(kInterfaceIDSpace, IID_IQADTDVALIDATIONUTILS, 		kTestingPrefix + 48)
DECLARE_PMID(kInterfaceIDSpace, IID_IQADEBUGUTILS, 				kTestingPrefix + 49)
DECLARE_PMID(kInterfaceIDSpace, IID_IQALINESTYLEUTILS, 			kTestingPrefix + 50)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IPOSTTESTUTILS, 			kTestingPrefix + 52)
DECLARE_PMID(kInterfaceIDSpace, IID_IQAEXPORTUTILS, 			kTestingPrefix + 53)
DECLARE_PMID(kInterfaceIDSpace, IID_IQADOCUMENTUTILS, 		kTestingPrefix + 54)
DECLARE_PMID(kInterfaceIDSpace, IID_IQAIMPORTUTILS, 			kTestingPrefix + 55)
DECLARE_PMID(kInterfaceIDSpace, IID_IBENCHMARKUTILS, 			kTestingPrefix + 56)
DECLARE_PMID(kInterfaceIDSpace, IID_IQAIDWITHICUTILS, 		kTestingPrefix + 57)
DECLARE_PMID(kInterfaceIDSpace, IID_IQAINCTEXTMACROUTILS, 	kTestingPrefix + 58)
DECLARE_PMID(kInterfaceIDSpace, IID_IQAINCUTILS, 		kTestingPrefix + 59)
DECLARE_PMID(kInterfaceIDSpace, IID_IQALOCALEUTILS, 		kTestingPrefix + 60)
DECLARE_PMID(kInterfaceIDSpace, IID_ITESTRUNNER, 				kTestingPrefix + 61)
DECLARE_PMID(kInterfaceIDSpace, IID_IDYNAMICTESTPROVIDER, 	kTestingPrefix + 62)
DECLARE_PMID(kInterfaceIDSpace, IID_IQAFILETAGUTILS, 		kTestingPrefix + 63)
DECLARE_PMID(kInterfaceIDSpace, IID_ITESTSUITELOADER, 		kTestingPrefix + 64)
DECLARE_PMID(kInterfaceIDSpace, IID_IQAJBXUTILS, 				kTestingPrefix + 65)

DECLARE_PMID(kInterfaceIDSpace, IID_IBOSSTHREADINGTEST1, 				kTestingPrefix + 66)
DECLARE_PMID(kInterfaceIDSpace, IID_IBOSSTHREADINGTEST2, 				kTestingPrefix + 67)
DECLARE_PMID(kInterfaceIDSpace, IID_IBOSSTHREADINGTEST3, 				kTestingPrefix + 68)
DECLARE_PMID(kInterfaceIDSpace, IID_IQASYNCSETTINGUTILS, 				kTestingPrefix + 69)
DECLARE_PMID(kInterfaceIDSpace, IID_IQAEPUBUTILS, 						kTestingPrefix + 70)
DECLARE_PMID(kInterfaceIDSpace, IID_ISAVEALLIMPLINXTEST,				kTestingPrefix + 71)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETERRORS_IN_SPECIFIC_OBS_RESP,	kTestingPrefix + 72)


// <Service ID>
//******SERVICE IDs
DECLARE_PMID(kServiceIDSpace, kTestProviderService, 				kTestingPrefix + 1)
DECLARE_PMID(kServiceIDSpace, kCTestSuiteProviderService, 			kTestingPrefix + 2)
DECLARE_PMID(kServiceIDSpace, kBeginSuiteSignalResponderService, 	kTestingPrefix + 3)
DECLARE_PMID(kServiceIDSpace, kQALogService, 						kTestingPrefix + 4)
//gap
DECLARE_PMID(kServiceIDSpace, kQAListenerService, 					kTestingPrefix + 6)
DECLARE_PMID(kServiceIDSpace, kTestServiceRegistryTrackingService,  kTestingPrefix + 7)

// <Widget ID>
//******WIDGET IDs
DECLARE_PMID(kWidgetIDSpace, kProfileCheckboxWidgetID, kTestingPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kTestPopupWidgetID, kTestingPrefix + 2)
//gap
DECLARE_PMID(kWidgetIDSpace, kUndoRedoButtonWidgetID, kTestingPrefix + 15)
//gap
DECLARE_PMID(kWidgetIDSpace, kInvalToolWidgetId, kTestingPrefix + 21)
//gap

//TestPanel TreeView Widgets
//DECLARE_PMID(kWidgetIDSpace, kTPQAAppPanelWidgetId,				kTestingPrefix + 29)


// <Implementation ID>
//******IMPLEMENTATION IDs
DECLARE_PMID(kImplementationIDSpace, kRestartTestsDataImpl, 			kTestingPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kQAMessageUtilsImpl, 				kTestingPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kQALogServiceProviderImpl, 		kTestingPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kQAPluginUtilsImpl,				kTestingPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kOverrideThisImplementationImpl, 	kTestingPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kCTestServiceImpl, 				kTestingPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kTestSuiteListenerContainerImpl,	kTestingPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kQASetErrorsStartupShutdownImpl,	kTestingPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kQASetErrorsObserverImpl,			kTestingPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kQAThreadingLogImpl, 				kTestingPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kQALogRegistryImpl, 				kTestingPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kQATestLogImpl, 					kTestingPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kTestLibPluginIteratorRegImpl, 	kTestingPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kTablesTestProviderImpl, 			kTestingPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kRunScriptIdleTaskImpl, 			kTestingPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kQAXMLTestLogImpl,		 			kTestingPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kQADocumentObserverImpl, 			kTestingPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kTestPrefsImpl, 					kTestingPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kInvalToolImpl, 					kTestingPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kInvalToolTrackerImpl, 			kTestingPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kInvalTrackerRegisterImpl, 		kTestingPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kQAListenerServiceProviderImpl, 	kTestingPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kTestProviderImpl, 				kTestingPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kCommandCoverageImpl, 				kTestingPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kBenchPrefsImpl, 					kTestingPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kBenchDataImpl, 					kTestingPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, k2ndPassTestPrefIntImpl, 			kTestingPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kQASetErrorsResponderImpl,         kTestingPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kQAListenerRegistryImpl, 			kTestingPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kSuiteHierMenuComponentImpl, 		kTestingPrefix + 30) //Keep for conversion.
DECLARE_PMID(kImplementationIDSpace, kCmdListRetrieverObserverImpl, 	kTestingPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kCrashListenerContainerImpl, 		kTestingPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kCleanupListenerContainerImpl, 	kTestingPrefix + 33)
//gap
DECLARE_PMID(kImplementationIDSpace, kLazyAutomationStartupShutdownImpl,kTestingPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kAutomationStartupShutdownImpl, 	kTestingPrefix + 36)
//DECLARE_PMID(kImplementationIDSpace, kTeamTestsSuiteImpImpl, 			kTestingPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kTestSuiteStatusImpl, 				kTestingPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kTestStartupShutdownServiceImpl, 	kTestingPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kTestPagedSetStorageImpl, 			kTestingPrefix + 40)
//gap
DECLARE_PMID(kImplementationIDSpace, kTestPagedMapStorageImpl, 			kTestingPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kTestSuiteIdleTaskImpl,			kTestingPrefix + 44)
//gap
DECLARE_PMID(kImplementationIDSpace, kQAAlertHandlerDataImpl, 			kTestingPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kQAAlertHandlerImpl, 				kTestingPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kQADebugUtilsImpl, 				kTestingPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kDataBaseObserverImpl, 			kTestingPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kDocDBObserverImpl, 				kTestingPrefix + 52)
//gap
DECLARE_PMID(kImplementationIDSpace, kSetTestPrefsCmdImpl, 				kTestingPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kSetBenchPrefsCmdImpl, 			kTestingPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kCommandCoverageCmdImpl, 			kTestingPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kTestSuiteSignalServiceImpl, 		kTestingPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kAfterSignalObserverImpl, 			kTestingPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kQASessionLogResponderImpl, 		kTestingPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kTestPrefsNoPersistImpl, 			kTestingPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kBenchPrefsNoPersistImpl, 			kTestingPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kAlertListenerContainerImpl, 		kTestingPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kAssertListenerContainerImpl, 		kTestingPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kBenchmarkListenerContainerImpl, 	kTestingPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kQAScriptListenerContainerImpl, 	kTestingPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kSteppingListenerContainerImpl, 	kTestingPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kTestFilteringListenerContainerImpl, kTestingPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kMemoryListenerContainerImpl, 		kTestingPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kTestResultsListenerContainerImpl,	kTestingPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kNewQATestProviderImpl, kTestingPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kNewMastersTestProviderImpl, kTestingPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kNewSpreadsTestProviderImpl, kTestingPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kNewSectionsTestProviderImpl, kTestingPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kNewStandoffTestProviderImpl, kTestingPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kNewColorTestProviderImpl, kTestingPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kNewLayersTestProviderImpl, kTestingPrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kNewAutoLayoutTestProviderImpl, kTestingPrefix + 77)
DECLARE_PMID(kImplementationIDSpace, kNewGraphicsTestProviderImpl, kTestingPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kNewGuidesTestProviderImpl, kTestingPrefix + 79)
DECLARE_PMID(kImplementationIDSpace, kNewMeasurementTestProviderImpl, kTestingPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kNewStoryTestProviderImpl, kTestingPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kNewPageItemTestProviderImpl, kTestingPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kNewTextFrameTestProviderImpl, kTestingPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kQALocaleUtilsImpl, kTestingPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kNewLibraryPaletteTestProviderImpl, kTestingPrefix + 85)
DECLARE_PMID(kImplementationIDSpace, kNewScrapTestProviderImpl, kTestingPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kNewSelectionTestProviderImpl, kTestingPrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kNewMenusTestProviderImpl, kTestingPrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kNewPlugInsTestProviderImpl, kTestingPrefix + 89)
DECLARE_PMID(kImplementationIDSpace, kNewPubsTestProviderImpl, kTestingPrefix + 90)
DECLARE_PMID(kImplementationIDSpace, kNewTransformTestProviderImpl, kTestingPrefix + 91)
DECLARE_PMID(kImplementationIDSpace, kNewPrintTestProviderImpl, kTestingPrefix + 92)
DECLARE_PMID(kImplementationIDSpace, kQAEpubUtilsImpl, kTestingPrefix + 93)
DECLARE_PMID(kImplementationIDSpace, kNewConversionTestProviderImpl, kTestingPrefix + 94)
DECLARE_PMID(kImplementationIDSpace, kNewExportTestProviderImpl, kTestingPrefix + 95)
DECLARE_PMID(kImplementationIDSpace, kNewGraphicsImportTestProviderImpl, kTestingPrefix + 96)
DECLARE_PMID(kImplementationIDSpace, kNewSystemsTestProviderImpl, kTestingPrefix + 97)
DECLARE_PMID(kImplementationIDSpace, kNewFindChgTestProviderImpl, kTestingPrefix + 98)
DECLARE_PMID(kImplementationIDSpace, kNewToolTestProviderImpl, kTestingPrefix + 99)
DECLARE_PMID(kImplementationIDSpace, kBasicThreadingTestProviderImpl, kTestingPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kNewPDFTestProviderImpl, kTestingPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kQASyncSettingUtilsImpl, kTestingPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kNewDictionaryTestProviderImpl, kTestingPrefix + 103)
//gap
DECLARE_PMID(kImplementationIDSpace, kQAAssertLogImpl, kTestingPrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kQADocTestProviderImpl, kTestingPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kQAAppTestProviderImpl, kTestingPrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kQAColorTestProviderImpl, kTestingPrefix + 108)
DECLARE_PMID(kImplementationIDSpace, kQAGraphicFrameTestProviderImpl, kTestingPrefix + 109)
DECLARE_PMID(kImplementationIDSpace, kQAGuideTestProviderImpl, kTestingPrefix + 110)
DECLARE_PMID(kImplementationIDSpace, kQALayersTestProviderImpl, kTestingPrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kQALibraryTestProviderImpl, kTestingPrefix + 112)
DECLARE_PMID(kImplementationIDSpace, kQAMastersTestProviderImpl, kTestingPrefix + 113)
DECLARE_PMID(kImplementationIDSpace, kQAPageTestProviderImpl, kTestingPrefix + 114)
DECLARE_PMID(kImplementationIDSpace, kQAPageItemTestProviderImpl, kTestingPrefix + 115)
DECLARE_PMID(kImplementationIDSpace, kQASectionTestProviderImpl, kTestingPrefix + 116)
DECLARE_PMID(kImplementationIDSpace, kQASplineTestProviderImpl, kTestingPrefix + 117)
DECLARE_PMID(kImplementationIDSpace, kQASpreadTestProviderImpl, kTestingPrefix + 118)
DECLARE_PMID(kImplementationIDSpace, kQAStoryTestProviderImpl, kTestingPrefix + 119)
DECLARE_PMID(kImplementationIDSpace, kQATextFrameTestProviderImpl, kTestingPrefix + 120)
DECLARE_PMID(kImplementationIDSpace, kQAWindowTestProviderImpl, kTestingPrefix + 121)
//gap
DECLARE_PMID(kImplementationIDSpace, kQAInlineTestProviderImpl, kTestingPrefix + 123)
DECLARE_PMID(kImplementationIDSpace, kQALinkProviderImpl, kTestingPrefix + 124)
DECLARE_PMID(kImplementationIDSpace, kQABugTestProviderImpl, kTestingPrefix + 125)
DECLARE_PMID(kImplementationIDSpace, kQATextColumnTestProviderImpl, kTestingPrefix + 126)
DECLARE_PMID(kImplementationIDSpace, kQAGroupClassTestProviderImpl, kTestingPrefix + 127)
//DECLARE_PMID(kImplementationIDSpace, kActiveBugSuiteImpl, kTestingPrefix + 128)
DECLARE_PMID(kImplementationIDSpace, kQAPDFStyleTestProviderImpl, kTestingPrefix + 129)
DECLARE_PMID(kImplementationIDSpace, kQAPictureTestProviderImpl, kTestingPrefix + 130)
DECLARE_PMID(kImplementationIDSpace, kQAStyleTestProviderImpl, kTestingPrefix + 131)
DECLARE_PMID(kImplementationIDSpace, kQATableTestProviderImpl, kTestingPrefix + 132)
DECLARE_PMID(kImplementationIDSpace, kQARegressionTestProviderImpl, kTestingPrefix + 133)
DECLARE_PMID(kImplementationIDSpace, kBookTestProviderImpl, kTestingPrefix + 134)
//DECLARE_PMID(kImplementationIDSpace, kDocsHundBrowserImpl, kTestingPrefix + 135)
DECLARE_PMID(kImplementationIDSpace, kTestLibPluginErrStringImpl, kTestingPrefix + 136)
DECLARE_PMID(kImplementationIDSpace, kParametricFindChangeTestProviderImpl, kTestingPrefix + 137)
DECLARE_PMID(kImplementationIDSpace, kParaStrandTestProviderImpl, kTestingPrefix + 138)
DECLARE_PMID(kImplementationIDSpace, kQASoundTestProviderImpl, kTestingPrefix + 139)
DECLARE_PMID(kImplementationIDSpace, kSUIDSTestProviderImpl, kTestingPrefix + 140)
DECLARE_PMID(kImplementationIDSpace, kQAXMLReferenceDataImpl, kTestingPrefix + 141)
//DECLARE_PMID(kImplementationIDSpace, kNewMeasureLineTestProviderImpl, kTestingPrefix + 142)
DECLARE_PMID(kImplementationIDSpace, kQAPageItemFormFieldTestProviderImpl, kTestingPrefix + 143)
DECLARE_PMID(kImplementationIDSpace, kQAMovieTestProviderImpl, kTestingPrefix + 144)
DECLARE_PMID(kImplementationIDSpace, kQAXMLTestProviderImpl, kTestingPrefix + 145)
DECLARE_PMID(kImplementationIDSpace, kTextSnapshotTestProviderImpl, kTestingPrefix + 146)
DECLARE_PMID(kImplementationIDSpace, kQABookmarkTestProviderImpl, kTestingPrefix + 147)
DECLARE_PMID(kImplementationIDSpace, kNewConversionVerifyProviderImpl, kTestingPrefix + 150)
DECLARE_PMID(kImplementationIDSpace, kFindStringIteratorTestProImpl, kTestingPrefix + 152)
DECLARE_PMID(kImplementationIDSpace, kQARegressionQuitTestProviderImpl, kTestingPrefix + 153)
DECLARE_PMID(kImplementationIDSpace, kQAXMLLogResponderImpl, kTestingPrefix + 157)
DECLARE_PMID(kImplementationIDSpace, kNewObjectStyleTestProviderImpl, kTestingPrefix + 158)
DECLARE_PMID(kImplementationIDSpace, kQAExportUtilsImpl, kTestingPrefix + 159)
DECLARE_PMID(kImplementationIDSpace, kQADocumentUtilsImpl, kTestingPrefix + 160)
DECLARE_PMID(kImplementationIDSpace, kQAImportUtilsImpl, kTestingPrefix + 161)
DECLARE_PMID(kImplementationIDSpace, kBenchmarkUtilsImpl, kTestingPrefix + 162)
DECLARE_PMID(kImplementationIDSpace, kQASnapshotScriptResponderImpl, kTestingPrefix + 163)
DECLARE_PMID(kImplementationIDSpace, kNewHyperlinkTestProviderImpl, kTestingPrefix + 164)
DECLARE_PMID(kImplementationIDSpace, kSangamImportExportTestProviderImpl, kTestingPrefix + 165)
//DECLARE_PMID(kImplementationIDSpace, kQAWorkFlowWebDavProviderImpl, kTestingPrefix + 166)
DECLARE_PMID(kImplementationIDSpace, kNewPDFAndPSTestProviderImpl, kTestingPrefix + 167)
DECLARE_PMID(kImplementationIDSpace, kZZLastTestProviderImpl, kTestingPrefix + 168)
DECLARE_PMID(kImplementationIDSpace, kXMLInsertTextCmdImpl, kTestingPrefix + 169)
DECLARE_PMID(kImplementationIDSpace, kBossThreadingTest1Impl,	kTestingPrefix + 170)
DECLARE_PMID(kImplementationIDSpace, kBossThreadingTest2Impl,	kTestingPrefix + 171)
DECLARE_PMID(kImplementationIDSpace, kBossThreadingTest3Impl,	kTestingPrefix + 172)
DECLARE_PMID(kImplementationIDSpace, kBossThreadingTestObserverImpl,	kTestingPrefix + 173)
//gap
//DECLARE_PMID(kImplementationIDSpace, kTestSuiteTreeViewMgrImpl, kTestingPrefix + 175)
//gap
DECLARE_PMID(kImplementationIDSpace, kTestServiceRegistryAnywhereImpl,	kTestingPrefix + 176)
DECLARE_PMID(kImplementationIDSpace, kTestServiceRegistryMainThreadImpl,	kTestingPrefix + 177)
DECLARE_PMID(kImplementationIDSpace, kTestServiceRegistryWorkerThreadImpl,	kTestingPrefix + 178)
//gap
DECLARE_PMID(kImplementationIDSpace, kStreamingGraphicsPortImpl, kTestingPrefix + 190)
DECLARE_PMID(kImplementationIDSpace, kTestSuitePrefsMgrImpl,	kTestingPrefix + 191)
//gap
DECLARE_PMID(kImplementationIDSpace, kQAFileDiffUtilsImpl,	kTestingPrefix + 194)
DECLARE_PMID(kImplementationIDSpace, kTestAsyncWorkManager1ProcessorFactoryImpl,	kTestingPrefix + 195)
DECLARE_PMID(kImplementationIDSpace, kTestAsyncWorkManager2ProcessorFactoryImpl,	kTestingPrefix + 196)
DECLARE_PMID(kImplementationIDSpace, kTestAsyncWorkManager3ProcessorFactoryImpl,	kTestingPrefix + 197)
DECLARE_PMID(kImplementationIDSpace, kTestAsyncWorkManagerFactoryServiceImpl,	kTestingPrefix + 198)
DECLARE_PMID(kImplementationIDSpace, kQAInDesignWithInCopyUtilsImpl, kTestingPrefix + 199)
DECLARE_PMID(kImplementationIDSpace, kQAInCTextMacroUtilsImpl, kTestingPrefix + 200)
DECLARE_PMID(kImplementationIDSpace, kQAInCUtilsImpl, kTestingPrefix + 201)
//gap
DECLARE_PMID(kImplementationIDSpace, kRestartTestsCmdImpl, kTestingPrefix + 203)
//gap
DECLARE_PMID(kImplementationIDSpace, kQAXMPTestProviderImpl, kTestingPrefix + 205)
DECLARE_PMID(kImplementationIDSpace, kQASurrogateTestProviderImpl, kTestingPrefix + 206)
//gap
DECLARE_PMID(kImplementationIDSpace, kQATestIdleTaskImpl, kTestingPrefix + 208)
//gap
DECLARE_PMID(kImplementationIDSpace, kScriptingTestProviderImpl, kTestingPrefix + 212)
DECLARE_PMID(kImplementationIDSpace, kBNTestProviderImpl, kTestingPrefix + 213)
DECLARE_PMID(kImplementationIDSpace, kImageCaptionTestProviderImpl,	kTestingPrefix + 214)
DECLARE_PMID(kImplementationIDSpace, kPostTestUtilsImpl,	kTestingPrefix + 215)
DECLARE_PMID(kImplementationIDSpace, kTestRunnerImpl,	kTestingPrefix + 216)

//QA Selection Suite
DECLARE_PMID(kImplementationIDSpace, kQASelectionSuiteASBImpl, kTestingPrefix + 217)
DECLARE_PMID(kImplementationIDSpace, kQASelectionSuiteLayoutCSBImpl, kTestingPrefix + 218)
DECLARE_PMID(kImplementationIDSpace, kQASelectionSuiteTextCSBImpl, kTestingPrefix + 219)

//QA Utils
DECLARE_PMID(kImplementationIDSpace, kQAAppleScriptUtilsImpl, kTestingPrefix + 220)
DECLARE_PMID(kImplementationIDSpace, kQAAttributeUtilsImpl, kTestingPrefix + 221)
DECLARE_PMID(kImplementationIDSpace, kQASnippetTestProviderImpl, kTestingPrefix + 222)
DECLARE_PMID(kImplementationIDSpace, kQAClassificationUtilsImpl, kTestingPrefix + 223)
DECLARE_PMID(kImplementationIDSpace, kQAColorUtilsImpl, kTestingPrefix + 224)
DECLARE_PMID(kImplementationIDSpace, kQATextFrameUtilsImpl, kTestingPrefix + 225)
DECLARE_PMID(kImplementationIDSpace, kQAContextUtilsImpl, kTestingPrefix + 226)
DECLARE_PMID(kImplementationIDSpace, kQALayoutSelectionUtilsImpl, kTestingPrefix + 227)
DECLARE_PMID(kImplementationIDSpace, kQAOpenTypeUtilsImpl, kTestingPrefix + 228)
DECLARE_PMID(kImplementationIDSpace, kQAPageItemUtilsImpl, kTestingPrefix + 229)
DECLARE_PMID(kImplementationIDSpace, kQAPropertyUtilsImpl, kTestingPrefix + 230)
DECLARE_PMID(kImplementationIDSpace, kQARuleUtilsImpl, kTestingPrefix + 231)
DECLARE_PMID(kImplementationIDSpace, kQAStoryUtilsImpl,	kTestingPrefix + 232)
DECLARE_PMID(kImplementationIDSpace, kQAStringFilterUtilsImpl, kTestingPrefix + 233)
DECLARE_PMID(kImplementationIDSpace, kQAStructureUtilsImpl, kTestingPrefix + 234)
DECLARE_PMID(kImplementationIDSpace, kQAStyleUtilsImpl, kTestingPrefix + 235)
DECLARE_PMID(kImplementationIDSpace, kQATagUtilsImpl, kTestingPrefix + 236)
//gap
DECLARE_PMID(kImplementationIDSpace, kDTITestProviderImpl, kTestingPrefix + 238)
DECLARE_PMID(kImplementationIDSpace, kQAWorkgroupUtilsImpl, kTestingPrefix + 239)
//gap
DECLARE_PMID(kImplementationIDSpace, kQALineStyleUtilsImpl, kTestingPrefix + 241)
DECLARE_PMID(kImplementationIDSpace, kQACommandProcessorProxyImpl, kTestingPrefix + 242)
DECLARE_PMID(kImplementationIDSpace, kQACmdHistoryProxyImpl, kTestingPrefix + 243)
DECLARE_PMID(kImplementationIDSpace, kQAJBXUtilsImpl, kTestingPrefix + 244)
DECLARE_PMID(kImplementationIDSpace, kQACommandProcessorPrivateProxyImpl, kTestingPrefix + 245)
DECLARE_PMID(kImplementationIDSpace, kQACmdQueueProxyImpl, kTestingPrefix + 246)
DECLARE_PMID(kImplementationIDSpace, kQASubjectProxyImpl, kTestingPrefix + 247)
//DECLARE_PMID(kImplementationIDSpace, kUnusedImpl, kTestingPrefix + 248)
DECLARE_PMID(kImplementationIDSpace, kQAIntegerControlDataProxyImpl, kTestingPrefix + 249)
DECLARE_PMID(kImplementationIDSpace, kQACmdDebuggerProxyImpl, kTestingPrefix + 250)
DECLARE_PMID(kImplementationIDSpace, kQADocConsistObserverProxyImpl, kTestingPrefix + 251)
//DECLARE_PMID(kImplementationIDSpace, kUnusedImpl, kTestingPrefix + 252)
DECLARE_PMID(kImplementationIDSpace, kQAAURCommandProcessorProxyImpl, kTestingPrefix + 253)
DECLARE_PMID(kImplementationIDSpace, kBenchmarkReorgTestProviderImpl, kTestingPrefix + 254)
//DECLARE_PMID(kImplementationIDSpace, kUnusedImpl, kTestingPrefix + 255)
//Don't add any ImplementationID for kTestingPrefix past 255; it is the maximum.

DECLARE_PMID(kImplementationIDSpace, kTestMgrImpl, 						kTestingPrefixE + 0)
DECLARE_PMID(kImplementationIDSpace, kQASerializationTestProviderImpl,	kTestingPrefixE + 1)
//gap
DECLARE_PMID(kImplementationIDSpace, kQAStaticListenerContainerImpl, 	kTestingPrefixE + 3)
DECLARE_PMID(kImplementationIDSpace, kQADTDValidationUtilsImpl, 		kTestingPrefixE + 4)
//gap
DECLARE_PMID(kImplementationIDSpace, kCTestSuiteImpl, 					kTestingPrefixE + 6)
DECLARE_PMID(kImplementationIDSpace, kQAFileTagUtilsImpl, 				kTestingPrefixE + 7)
DECLARE_PMID(kImplementationIDSpace, kTestSuiteLoaderImpl, 				kTestingPrefixE + 8)

//gap
DECLARE_PMID(kImplementationIDSpace, kQAAATTestProviderImpl, 			kTestingPrefixE + 21)
DECLARE_PMID(kImplementationIDSpace, kDynamicTestProviderImpl, 			kTestingPrefixE + 22)
DECLARE_PMID(kImplementationIDSpace, kINXTestProviderImpl, 				kTestingPrefixE + 23)
//gap
DECLARE_PMID(kImplementationIDSpace, kConditionalTextTestProviderImpl,	kTestingPrefixE + 25)

// <Ignore>
//******Obsolete page item ids.  Still used by tests to create different types of page items
#define kRegPolyItem									kTestingPrefix + 125
#define kOvalItem											kTestingPrefix + 126
#define kLineItem											kTestingPrefix + 127
#define kRectItem											kTestingPrefix + 128

// <Ignore>
//******PROGRESSBAR IDs
#define kProgressBarMinimalSuite				kTestingPrefix + 1
#define kProgressBarImportExportTest			kTestingPrefix + 2
#define kProgressBarSystemsTest					kTestingPrefix + 3
#define kProgressBarTeamSuite					kTestingPrefix + 4

// <Error ID>
//******ERROR IDs
DECLARE_PMID(kErrorIDSpace, kTestSkippedError, kTestingPrefix + 0)
DECLARE_PMID(kErrorIDSpace, kPanelNotFoundError, kTestingPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kCannotScrollError, kTestingPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kMenuNotFoundError, kTestingPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kMenuDisabledError, kTestingPrefix + 4)
DECLARE_PMID(kErrorIDSpace, kWidgetDisabledError, kTestingPrefix + 5)
DECLARE_PMID(kErrorIDSpace, kWidgetNotFoundError, kTestingPrefix + 6)
DECLARE_PMID(kErrorIDSpace, kListItemNotFoundError, kTestingPrefix + 7)
DECLARE_PMID(kErrorIDSpace, kInvalidWidgetTypeError, kTestingPrefix + 8)
DECLARE_PMID(kErrorIDSpace, kAppleScriptNotInstalledError, kTestingPrefix + 9)
DECLARE_PMID(kErrorIDSpace, kCancelSuiteError, kTestingPrefix + 10)
DECLARE_PMID(kErrorIDSpace, kNoListItemSelectedError, kTestingPrefix + 11)
DECLARE_PMID(kErrorIDSpace, kWidgetListItemNotFoundError, kTestingPrefix + 12)
DECLARE_PMID(kErrorIDSpace, kInvalidLanguageError, kTestingPrefix + 13)
DECLARE_PMID(kErrorIDSpace, kWidgetNotVisibleError, kTestingPrefix + 14)
DECLARE_PMID(kErrorIDSpace, kQAInvalidUIDRefParameterError, kTestingPrefix + 15)
DECLARE_PMID(kErrorIDSpace, kSnapshotNotFoundAndLocked, kTestingPrefix + 16)
DECLARE_PMID(kErrorIDSpace, kDontRunOrLogTestError, kTestingPrefix + 17)
DECLARE_PMID(kErrorIDSpace, kCantRunWithoutIdleTaskError, kTestingPrefix + 18)
DECLARE_PMID(kErrorIDSpace, kCantMakeAssertLogError, kTestingPrefix + 19)
DECLARE_PMID(kErrorIDSpace, kRestartCurrentIterationError, kTestingPrefix + 20)
DECLARE_PMID(kErrorIDSpace, kParsingSuiteDescriptionFileError, kTestingPrefix + 21)
DECLARE_PMID(kErrorIDSpace, kDuplicateSuiteNameError, kTestingPrefix + 22)
DECLARE_PMID(kErrorIDSpace, kCannotAddSuiteError, kTestingPrefix + 23)
DECLARE_PMID(kErrorIDSpace, kInvalidDescriptionFileSuiteNameError, kTestingPrefix + 24)
DECLARE_PMID(kErrorIDSpace, kInvalidSuiteNameError, kTestingPrefix + 25)
DECLARE_PMID(kErrorIDSpace, kSuiteDoesNotExistError, kTestingPrefix + 26)
DECLARE_PMID(kErrorIDSpace, kCannotRemoveSuiteError, kTestingPrefix + 27)
DECLARE_PMID(kErrorIDSpace, kCannotCreateSuiteError, kTestingPrefix + 28)
DECLARE_PMID(kErrorIDSpace, kCannotWriteSuiteListError, kTestingPrefix + 29)
DECLARE_PMID(kErrorIDSpace, kCannotApplyBenchDataError, kTestingPrefix + 30)
DECLARE_PMID(kErrorIDSpace, kQAStatusExpiryOutOfRange, kTestingPrefix + 31)
DECLARE_PMID(kErrorIDSpace, kQAStatusBadExpiry, kTestingPrefix + 32)
DECLARE_PMID(kErrorIDSpace, kQAStatusUnrecognizedTag, kTestingPrefix + 33)
DECLARE_PMID(kErrorIDSpace, kQAStatusTooManyProductTags, kTestingPrefix + 34)
// Special testing dummy errors
DECLARE_PMID(kErrorIDSpace, kErrorSetForCloseAllAndQuit, kTestingPrefix + 35)
DECLARE_PMID(kErrorIDSpace, kErrorSetForQuit, kTestingPrefix + 36)
DECLARE_PMID(kErrorIDSpace, kErrorSetByBeforeSaveDocResponder, kTestingPrefix + 37)
DECLARE_PMID(kErrorIDSpace, kErrorSetByBeforeSaveAsDocResponder, kTestingPrefix + 38)
DECLARE_PMID(kErrorIDSpace, kErrorSetByBeforeSaveACopyDocResponder, kTestingPrefix + 39)
DECLARE_PMID(kErrorIDSpace, kErrorSetByBeforeCloseDocResponder, kTestingPrefix + 40)
DECLARE_PMID(kErrorIDSpace, kErrorSetByAfterSaveDocResponder, kTestingPrefix + 41)
DECLARE_PMID(kErrorIDSpace, kErrorSetByAfterSaveAsDocResponder, kTestingPrefix + 42)
DECLARE_PMID(kErrorIDSpace, kErrorSetByAfterCloseDocResponder, kTestingPrefix + 43)

// <Message ID>
//******MESSAGE IDs
DECLARE_PMID(kMessageIDSpace, kLoadedTestSuiteMsg, kTestingPrefix + 0)
DECLARE_PMID(kMessageIDSpace, kEndTestSuiteMsg, kTestingPrefix + 1)
DECLARE_PMID(kMessageIDSpace, kUnloadedTestSuiteMsg, kTestingPrefix + 2)

// <Action ID>
//gap

#endif // __TestID__
