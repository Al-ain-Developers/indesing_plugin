//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/AppFrameworkID.h $
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
//========================================================================================

#ifndef __AppFrameworkID__
#define __AppFrameworkID__

#include "CrossPlatformTypes.h"
#include "GUID.h"
#include "IDFactory.h"

#define kAppFrameworkPrefix	 RezLong(0x16100)		// see AdobePrefix.h


// PluginID
#define kAppFrameworkPluginName 	"AppFramework"
DECLARE_PMID(kPlugInIDSpace, kAppFrameworkPluginID, kAppFrameworkPrefix + 1)


// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kEventConverterBoss,					kAppFrameworkPrefix + 1)
DECLARE_PMID(kClassIDSpace, kChangeManagerBoss,						kAppFrameworkPrefix + 2)
DECLARE_PMID(kClassIDSpace, kCmdCollectionBoss,						kAppFrameworkPrefix + 3)
DECLARE_PMID(kClassIDSpace, kAppFrameworkConversionBoss,			kAppFrameworkPrefix + 4)
DECLARE_PMID(kClassIDSpace, kDebugPrefsServiceBoss,					kAppFrameworkPrefix + 5)
DECLARE_PMID(kClassIDSpace, kDebugPrefsContentHandlerBoss,			kAppFrameworkPrefix + 6)
DECLARE_PMID(kClassIDSpace, kApplicationScriptProviderBoss,			kAppFrameworkPrefix + 7)
DECLARE_PMID(kClassIDSpace, kUndoRedoScriptProviderBoss,			kAppFrameworkPrefix + 8)
DECLARE_PMID(kClassIDSpace, kAutoUndoRedoTestMenuBoss,				kAppFrameworkPrefix + 9)
DECLARE_PMID(kClassIDSpace, kSBOSPageBoss,							kAppFrameworkPrefix + 10)
DECLARE_PMID(kClassIDSpace, kSBOSTestBoss,							kAppFrameworkPrefix + 11)
DECLARE_PMID(kClassIDSpace, kNoPubActiveContextBoss,				kAppFrameworkPrefix + 12)
DECLARE_PMID(kClassIDSpace, kDisplayListViewPortBoss,				kAppFrameworkPrefix + 13)
DECLARE_PMID(kClassIDSpace, kAutoUndoRedoSnapshotBoss,				kAppFrameworkPrefix + 14)
DECLARE_PMID(kClassIDSpace, kSaLRIDBRootBoss,						kAppFrameworkPrefix + 15)
DECLARE_PMID(kClassIDSpace, kSaLRICacheBlockBoss,					kAppFrameworkPrefix + 16)
DECLARE_PMID(kClassIDSpace, kDBChangesMonitorBoss,					kAppFrameworkPrefix + 17)
DECLARE_PMID(kClassIDSpace, kStringInitializerBoss,					kAppFrameworkPrefix + 18)
DECLARE_PMID(kClassIDSpace, kDeleteRepositoryCmdBoss,				kAppFrameworkPrefix + 19)
DECLARE_PMID(kClassIDSpace, kSBOSUnknownBoss,						kAppFrameworkPrefix + 20)
DECLARE_PMID(kClassIDSpace, kAppFrameworkIteratorRegBoss,			kAppFrameworkPrefix + 21)
DECLARE_PMID(kClassIDSpace, kAppChangesSignalMgrBoss, 				kAppFrameworkPrefix + 22)
DECLARE_PMID(kClassIDSpace, kAppChangesObserverBoss, 				kAppFrameworkPrefix + 23)
DECLARE_PMID(kClassIDSpace, kAutoUndoCmdHistoryStubBoss,			kAppFrameworkPrefix + 24)
DECLARE_PMID(kClassIDSpace, kCodeConversionBoss,					kAppFrameworkPrefix + 25)
DECLARE_PMID(kClassIDSpace, kAutomationManagerBoss,					kAppFrameworkPrefix + 26)
DECLARE_PMID(kClassIDSpace, kMainUserActionManagerBoss,				kAppFrameworkPrefix + 27)
DECLARE_PMID(kClassIDSpace, kUserActionAutomationServiceBoss,		kAppFrameworkPrefix + 28)
DECLARE_PMID(kClassIDSpace, kUserActionBoss,						kAppFrameworkPrefix + 29)
DECLARE_PMID(kClassIDSpace, kUserActionSequenceBoss,				kAppFrameworkPrefix + 30)	
DECLARE_PMID(kClassIDSpace, kGeneralPrefsScriptProviderBoss,		kAppFrameworkPrefix + 31)
DECLARE_PMID(kClassIDSpace, kActionPolicyBoss,						kAppFrameworkPrefix + 32)
DECLARE_PMID(kClassIDSpace, kActionImportPolicyBoss,				kAppFrameworkPrefix + 33)
DECLARE_PMID(kClassIDSpace, kAppFrameworkErrorStringServiceBoss,	kAppFrameworkPrefix + 34)
DECLARE_PMID(kClassIDSpace, kUserActionPersonalityManagerBoss,		kAppFrameworkPrefix + 35)
DECLARE_PMID(kClassIDSpace, kTransformAgainUserActionManagerBoss,	kAppFrameworkPrefix + 36)
DECLARE_PMID(kClassIDSpace, kActionImportValidationBoss,			kAppFrameworkPrefix + 37)
DECLARE_PMID(kClassIDSpace, kActionExportPolicyBoss,				kAppFrameworkPrefix + 38)
DECLARE_PMID(kClassIDSpace, kDelayedAlertCmdBoss,					kAppFrameworkPrefix + 39)
DECLARE_PMID(kClassIDSpace, kSBOSMgrIndexStorageBoss,				kAppFrameworkPrefix + 40)
DECLARE_PMID(kClassIDSpace, kDontWarnPluginCmdBoss,					kAppFrameworkPrefix + 41)
DECLARE_PMID(kClassIDSpace, kSetActionsPlaybackPrefCmdBoss,			kAppFrameworkPrefix + 42)
DECLARE_PMID(kClassIDSpace, kTaskMonitorScriptProviderBoss,			kAppFrameworkPrefix + 43)
DECLARE_PMID(kClassIDSpace, kAsyncWorkManagerIdleTaskBoss,			kAppFrameworkPrefix + 44)
DECLARE_PMID(kClassIDSpace, kBackgroundTaskScriptObjectBoss,		kAppFrameworkPrefix + 45)
DECLARE_PMID(kClassIDSpace, kAsyncWorkManagerAppFlagsIdleTaskBoss,	kAppFrameworkPrefix + 46)
DECLARE_PMID(kClassIDSpace, kTaskMonitorIdleTaskBoss,				kAppFrameworkPrefix + 47)
DECLARE_PMID(kClassIDSpace, kReverseStringInitializerBoss,			kAppFrameworkPrefix + 48)
DECLARE_PMID(kClassIDSpace, kSnapshotDBStreamWriteBoss,				kAppFrameworkPrefix + 49)
DECLARE_PMID(kClassIDSpace, kSnapshotDBStreamReadBoss,				kAppFrameworkPrefix + 50)
DECLARE_PMID(kClassIDSpace, kCompareStreamBoss,						kAppFrameworkPrefix + 51)
DECLARE_PMID(kClassIDSpace, kApplicationScriptObserverBoss,			kAppFrameworkPrefix + 52)
DECLARE_PMID(kClassIDSpace, kHierarchyM2MListenerServiceBoss,		kAppFrameworkPrefix + 53)
DECLARE_PMID(kClassIDSpace, kAsyncWorkManagerInitIdleTaskBoss,		kAppFrameworkPrefix + 54)
DECLARE_PMID(kClassIDSpace, kSaLRIBlockDBStreamWriteBoss,			kAppFrameworkPrefix + 55)
DECLARE_PMID(kClassIDSpace, kSaLRIBlockDBStreamReadBoss,			kAppFrameworkPrefix + 56)
DECLARE_PMID(kClassIDSpace, kScriptInfoMgrStartupBoss,				kAppFrameworkPrefix + 57)
DECLARE_PMID(kClassIDSpace, kWorkerThreadSessionUpdateSignalMgrBoss,		kAppFrameworkPrefix + 58)
DECLARE_PMID(kClassIDSpace,	kSettingsMigrationStartupShutdownBoss,	kAppFrameworkPrefix + 59)
DECLARE_PMID(kClassIDSpace,	kProcessSettingsMigrationCmdBoss,		kAppFrameworkPrefix + 60)
DECLARE_PMID(kClassIDSpace,	kVulcanStartupShutdownBoss,				kAppFrameworkPrefix + 61)
DECLARE_PMID(kClassIDSpace, kNglProfileChangeSignalMgrBoss, 		kAppFrameworkPrefix + 62)
DECLARE_PMID(kClassIDSpace, kNglStartupShutdownBoss,				kAppFrameworkPrefix + 63)
DECLARE_PMID(kClassIDSpace, kNglOnLaunchCmdBoss,					kAppFrameworkPrefix + 64)
DECLARE_PMID(kClassIDSpace, kNglIdleTaskBoss,						kAppFrameworkPrefix + 65)

// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IEVENTCONVERTER,				kAppFrameworkPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRAPUTILS,					kAppFrameworkPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTIONUTILS,				kAppFrameworkPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTUTILS,					kAppFrameworkPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IFREETRANSFORMUTILS,			kAppFrameworkPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IUICOLORUTILS,					kAppFrameworkPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORSYSTEMUTILS,				kAppFrameworkPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_ISWATCHUTILS,					kAppFrameworkPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_ISWATCHSCRIPTUTILS,				kAppFrameworkPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IMENUUTILS,						kAppFrameworkPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_ISHORTCUTUTILS,					kAppFrameworkPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMPORTPROVIDERUTILS,			kAppFrameworkPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IREFPOINTUTILS,					kAppFrameworkPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IREFPOINTSHAPE,					kAppFrameworkPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_ISECONDPHASEUNDOREDOHANDLER,	kAppFrameworkPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEITEMSELECTION,				kAppFrameworkPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_ISYNCEVENTOBJECTS,				kAppFrameworkPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_IINITIALIZERMANAGER,			kAppFrameworkPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_INSTANCEPROCESSOR,				kAppFrameworkPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_IDBCHANGESMONITOR,				kAppFrameworkPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_IAUTOCMDUIDTRACKINGINFO,		kAppFrameworkPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_ISNAPSHOTCACHE,					kAppFrameworkPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAZYNOTIFICATIONHANDLER,		kAppFrameworkPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_IUNITTESTBENCHMARKMGR,			kAppFrameworkPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_IAGMUTILS,						kAppFrameworkPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_ILASTREVINFOCACHE,				kAppFrameworkPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_IREADSTREAMLENGTH,				kAppFrameworkPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_ISBOSPAGE,						kAppFrameworkPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_ISBOSMGR,						kAppFrameworkPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_ISBOSLINK,						kAppFrameworkPrefix + 32)
DECLARE_PMID(kInterfaceIDSpace, IID_ISBOSIDDATA,					kAppFrameworkPrefix + 33)
DECLARE_PMID(kInterfaceIDSpace, IID_IAUTOMATIONMANAGER,				kAppFrameworkPrefix + 34)
DECLARE_PMID(kInterfaceIDSpace, IID_IUSERACTIONMANAGER,				kAppFrameworkPrefix + 35)
DECLARE_PMID(kInterfaceIDSpace, IID_IAUTOMATIONSERVICE,				kAppFrameworkPrefix + 36)
DECLARE_PMID(kInterfaceIDSpace, IID_IUSERACTION,					kAppFrameworkPrefix + 37)
DECLARE_PMID(kInterfaceIDSpace, IID_IUSERACTIONSEQUENCE,			kAppFrameworkPrefix + 38)
DECLARE_PMID(kInterfaceIDSpace, IID_IUSERACTIONSEQUENCEATTRIBUTES,	kAppFrameworkPrefix + 39)
DECLARE_PMID(kInterfaceIDSpace, IID_IUSERACTIONATTRIBUTES,			kAppFrameworkPrefix + 40)
DECLARE_PMID(kInterfaceIDSpace, IID_IRIDXNOTIFIERHANDLER,			kAppFrameworkPrefix + 41)
DECLARE_PMID(kInterfaceIDSpace, IID_IRIDXNOTIFIERUTILS,				kAppFrameworkPrefix + 42)
DECLARE_PMID(kInterfaceIDSpace, IID_IUSERACTIONPERSONALITYMANAGER,	kAppFrameworkPrefix + 43)
DECLARE_PMID(kInterfaceIDSpace, IID_IUSERACTIONFACADE,				kAppFrameworkPrefix + 44)
DECLARE_PMID(kInterfaceIDSpace, IID_IUSERACTIONUTILS,				kAppFrameworkPrefix + 45)
DECLARE_PMID(kInterfaceIDSpace, IID_IPLUGINPRIVATEDATA,				kAppFrameworkPrefix + 46)
DECLARE_PMID(kInterfaceIDSpace, IID_ISTARTUPUTILS,					kAppFrameworkPrefix + 47)
DECLARE_PMID(kInterfaceIDSpace, IID_IVSIZEBASELINE,					kAppFrameworkPrefix + 48)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAZYSTARTUPSERVICEIDLETASK,	kAppFrameworkPrefix + 49)
DECLARE_PMID(kInterfaceIDSpace, IID_IM2MMESSAGEMANAGER,				kAppFrameworkPrefix + 50)
#ifdef DEBUG
DECLARE_PMID(kInterfaceIDSpace, IID_ISHOWINSTANTIATIONASSERTS,		kAppFrameworkPrefix + 51)	
#endif // DEBUG
DECLARE_PMID(kInterfaceIDSpace, IID_IAPPLICATIONDEBUGFLAGS,			kAppFrameworkPrefix + 52)
// -- The ID for this interface is defined here but there two separate implementations.
// -- One is in AppUI for the client and the other is in SoapServer for the server.
DECLARE_PMID(kInterfaceIDSpace, IID_IDEFAULTEHFACTORY,				kAppFrameworkPrefix + 53)	
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRAPFACADE,					kAppFrameworkPrefix + 54)	
DECLARE_PMID(kInterfaceIDSpace, IID_ISELECTIONTHUMBNAILSUITE,		kAppFrameworkPrefix + 55)
DECLARE_PMID(kInterfaceIDSpace, IID_IICONIDDATA,					kAppFrameworkPrefix + 56)		
DECLARE_PMID(kInterfaceIDSpace, IID_ITITLESTRINGDATA,				kAppFrameworkPrefix + 57)	
DECLARE_PMID(kInterfaceIDSpace, IID_IOKSTRINGDATA,					kAppFrameworkPrefix + 58)		
DECLARE_PMID(kInterfaceIDSpace, IID_ICANCELSTRINGDATA,				kAppFrameworkPrefix + 59)	
DECLARE_PMID(kInterfaceIDSpace, IID_IDEBUGPREFSUTILS,				kAppFrameworkPrefix + 60)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAZYNOTIFS_IDLETASK,			kAppFrameworkPrefix + 61)
DECLARE_PMID(kInterfaceIDSpace, IID_IPLUGINIDLIST,					kAppFrameworkPrefix + 62)
DECLARE_PMID(kInterfaceIDSpace, IID_IOLDPLUGINIDLIST,				kAppFrameworkPrefix + 63)	// same as IID_IPLUGINIDLIST, allows duplicate on kDontWarnPluginCmd
DECLARE_PMID(kInterfaceIDSpace, IID_IACTIONSPLAYBACKPREFERENCE,		kAppFrameworkPrefix + 64)	
DECLARE_PMID(kInterfaceIDSpace, IID_IASYNCWORKMANAGER,				kAppFrameworkPrefix + 65)
DECLARE_PMID(kInterfaceIDSpace, IID_IASYNCWORKPROCESSORFACTORY,		kAppFrameworkPrefix + 66)
DECLARE_PMID(kInterfaceIDSpace, IID_ILAZYNOTIFICATIONSUTILS,		kAppFrameworkPrefix + 67)
DECLARE_PMID(kInterfaceIDSpace, IID_IINTERFACESNAPSHOTSTREAMDATA,	kAppFrameworkPrefix + 68)
DECLARE_PMID(kInterfaceIDSpace, IID_IM2MMESSAGELISTENER,			kAppFrameworkPrefix + 69)
DECLARE_PMID(kInterfaceIDSpace, IID_ISNAPSHOTUTILS,					kAppFrameworkPrefix + 70)
DECLARE_PMID(kInterfaceIDSpace, IID_ILASTREVINFOUTILS,				kAppFrameworkPrefix + 71)
DECLARE_PMID(kInterfaceIDSpace, IID_ISERVICEPROVIDERTRACKINGUTILS, 	kAppFrameworkPrefix + 72)
DECLARE_PMID(kInterfaceIDSpace, IID_IBGTASKSUTILS, 					kAppFrameworkPrefix + 73)
DECLARE_PMID(kInterfaceIDSpace, IID_IAPPLICATIONDEFAULTSUTILS, 		kAppFrameworkPrefix + 74)
DECLARE_PMID(kInterfaceIDSpace, IID_ITASKEVENTSOBSERVER,			kAppFrameworkPrefix + 75)
DECLARE_PMID(kInterfaceIDSpace, IID_ICLOSEALLDOCSCMDDATA,			kAppFrameworkPrefix + 76)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRIVATEBGTASKSUTILS,			kAppFrameworkPrefix + 77)
DECLARE_PMID(kInterfaceIDSpace, IID_ITASKMONITORFACADE,				kAppFrameworkPrefix + 78)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETTINGSMIGRATIONMANAGER, 		kAppFrameworkPrefix + 79)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETTINGSMIGRATION, 			kAppFrameworkPrefix + 80)
DECLARE_PMID(kInterfaceIDSpace, IID_IVULCANMESSENGER, 				kAppFrameworkPrefix + 81)
DECLARE_PMID(kInterfaceIDSpace, IID_ICCXSTARTRECENTFILELIST,	 	kAppFrameworkPrefix + 82)
DECLARE_PMID(kInterfaceIDSpace, IID_IAUTOOPENEDFILES,			 	kAppFrameworkPrefix + 83)
DECLARE_PMID(kInterfaceIDSpace, IID_IABTESTINGFEATUREMAP,			kAppFrameworkPrefix + 84)
DECLARE_PMID(kInterfaceIDSpace, IID_IABTESTINGOBSERVER,				kAppFrameworkPrefix + 85)
DECLARE_PMID(kInterfaceIDSpace, IID_IABTESTINGUTILS,				kAppFrameworkPrefix + 86)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEMPORARYDATAFORLOGGING,		kAppFrameworkPrefix + 87)
DECLARE_PMID(kInterfaceIDSpace, IID_IGPUOVERRIDESDRAWOPTIONS,		kAppFrameworkPrefix + 88)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOMMENTSIMPORTPROVIDERUTILS,	kAppFrameworkPrefix + 89)
DECLARE_PMID(kInterfaceIDSpace, IID_IGOCARTINITIDLETASK,			kAppFrameworkPrefix + 90)
DECLARE_PMID(kInterfaceIDSpace, IID_INORMALIAMDOCSTORAGEMAP,		kAppFrameworkPrefix + 91)
// <Implementation ID>
// ImplementationIDs
DECLARE_PMID(kImplementationIDSpace, kEventConverterImpl,				kAppFrameworkPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kChangeManagerImpl,				kAppFrameworkPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kScrapUtilsImpl,					kAppFrameworkPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kSelectionUtilsImpl,				kAppFrameworkPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kSelectUtilsImpl,					kAppFrameworkPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kFreeTransformUtilsImpl,			kAppFrameworkPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kUIColorUtilsImpl,					kAppFrameworkPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kSwatchUtilsImpl,					kAppFrameworkPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kSwatchScriptUtilsImpl,			kAppFrameworkPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kMenuUtilsImpl,					kAppFrameworkPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kShortcutUtilsImpl,				kAppFrameworkPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kImportProviderUtilsImpl,			kAppFrameworkPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kRefPointUtilsImpl,				kAppFrameworkPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kColorSystemUtilsImpl,				kAppFrameworkPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kLazyStartupServiceIdleTaskImpl,	kAppFrameworkPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kAutomationManagerImpl,			kAppFrameworkPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kAutomationScriptManagerImpl,		kAppFrameworkPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kDebugPrefsServiceImpl,			kAppFrameworkPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kDebugPrefsStartupShutdownImpl,	kAppFrameworkPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kDebugPrefsContentHandlerImpl,		kAppFrameworkPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kApplicationScriptProviderImpl,	kAppFrameworkPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kApplicationScriptImpl,			kAppFrameworkPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kApplicationScriptObserverImpl,	kAppFrameworkPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kCodeConversionProviderImpl,		kAppFrameworkPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kUndoRedoScriptProviderImpl,		kAppFrameworkPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kSyncEventObjectsImpl,				kAppFrameworkPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kInitializerManagerImpl,			kAppFrameworkPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kDBChangesMonitorImpl,				kAppFrameworkPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kActionPolicyImpl,					kAppFrameworkPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kServiceProviderTrackingUtilsImpl, kAppFrameworkPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kReverseStringInitializerImpl,		kAppFrameworkPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kActionImportPolicyImpl,			kAppFrameworkPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kDebugPrefsUtilsImpl,				kAppFrameworkPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kUnitTestBenchmarkMgrImpl,			kAppFrameworkPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kAGMUtilsImpl,						kAppFrameworkPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kStringInitializerImpl,			kAppFrameworkPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kSBOSIDDataImpl,					kAppFrameworkPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kSBOSMgrImpl,						kAppFrameworkPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kSBOSPageImpl,						kAppFrameworkPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kForwardingActiveContextImpl,		kAppFrameworkPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kLeafActiveContextImpl,			kAppFrameworkPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kActiveContextObserverImpl,		kAppFrameworkPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kDelegateContextDataImpl,			kAppFrameworkPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kNoPubActiveContextImpl,			kAppFrameworkPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kSBOSPersistIntDataImpl,			kAppFrameworkPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kDeleteRepositoryCmdImpl,			kAppFrameworkPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kAppFrameworkIteratorRegImpl,		kAppFrameworkPrefix + 47)
#ifdef DEBUG
	DECLARE_PMID(kImplementationIDSpace, kShowInstantiationAssertsImpl, kAppFrameworkPrefix + 48)
#endif // DEBUG
//gap
DECLARE_PMID(kImplementationIDSpace, kCloseAllDocsCmdDataImpl, 			kAppFrameworkPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kAppChangesObserverImpl, 			kAppFrameworkPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kAppChangesResponderServiceImpl,	kAppFrameworkPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kAppChangesStartupShutdownImpl, 	kAppFrameworkPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kAutoUndoCmdHistoryStubImpl, kAppFrameworkPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kAutomationServiceProviderImpl, kAppFrameworkPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kMainUserActionManagerImpl, kAppFrameworkPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kUserActionAutomationServiceImpl, kAppFrameworkPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kUserActionImpl, kAppFrameworkPrefix + 58)				//••
DECLARE_PMID(kImplementationIDSpace, kUserActionSequenceImpl, kAppFrameworkPrefix + 59)		//••
DECLARE_PMID(kImplementationIDSpace, kPMUnknownRefListDataImpl, kAppFrameworkPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kGeneralPrefsScriptProviderImpl, kAppFrameworkPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kUserActionSequenceAttributesImpl, kAppFrameworkPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kUserActionAttributesImpl, kAppFrameworkPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kAppFrameworkErrorStringServiceImpl, kAppFrameworkPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kRIDXNotifierUtilsImpl, kAppFrameworkPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kRIDXNotifierServiceProviderImpl, kAppFrameworkPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kUserActionPersonalityManagerImpl, kAppFrameworkPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kUserActionPersonalityServiceImpl, kAppFrameworkPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kTransformAgainUserActionManagerImpl, kAppFrameworkPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kUserActionFacadeImpl, kAppFrameworkPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kUserActionUtilsImpl, kAppFrameworkPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kPluginPrivateDataImpl, kAppFrameworkPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kActionImportValidationImpl, kAppFrameworkPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kActionExportPolicyImpl, kAppFrameworkPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kApplicationDebugFlagsImpl, kAppFrameworkPrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kIScrapFacadeImpl, kAppFrameworkPrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kSelectionThumbnailSuiteASBImpl, kAppFrameworkPrefix + 77)
DECLARE_PMID(kImplementationIDSpace, kSelectionThumbnailLayoutCSBImpl, kAppFrameworkPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kSelectionThumbnailStructureCSBImpl, kAppFrameworkPrefix + 79)
DECLARE_PMID(kImplementationIDSpace, kDelayedAlertCmdImpl, kAppFrameworkPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kIconIDDataAliasImpl, kAppFrameworkPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kTitleStringDataAliasImpl, kAppFrameworkPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kOKStringDataAliasImpl, kAppFrameworkPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kCancelStringDataAliasImpl, kAppFrameworkPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kStartupUtilsImpl, kAppFrameworkPrefix + 85)
DECLARE_PMID(kImplementationIDSpace, kSBOSMgrIndexStorageImpl, kAppFrameworkPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kViewObjectChangesImpl, kAppFrameworkPrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kLazyNotificationsHandlerImpl, kAppFrameworkPrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kLazyNotifsIdleTaskImpl, kAppFrameworkPrefix + 89)
DECLARE_PMID(kImplementationIDSpace, kDontWarnPluginCmdImpl, kAppFrameworkPrefix + 90)
DECLARE_PMID(kImplementationIDSpace, kPluginIDListImpl,	kAppFrameworkPrefix + 91)
DECLARE_PMID(kImplementationIDSpace, kPluginIDListPersistImpl, kAppFrameworkPrefix + 92)
DECLARE_PMID(kImplementationIDSpace, kActionsPlaybackPreferenceImpl, kAppFrameworkPrefix + 93)
DECLARE_PMID(kImplementationIDSpace, kSetActionsPlaybackPrefCmdImpl, kAppFrameworkPrefix + 94)
DECLARE_PMID(kImplementationIDSpace, kAsyncWorkManagerImpl, kAppFrameworkPrefix + 95)
DECLARE_PMID(kImplementationIDSpace, kAsyncWorkManagerStartupShutdownImpl, kAppFrameworkPrefix + 96)
DECLARE_PMID(kImplementationIDSpace, kAsyncWorkManagerIdleTaskImpl, kAppFrameworkPrefix + 97)
DECLARE_PMID(kImplementationIDSpace, kAsyncWorkManagerProxyImpl, kAppFrameworkPrefix + 98)
DECLARE_PMID(kImplementationIDSpace, kLazyNotificationsUtilsImpl, kAppFrameworkPrefix + 99)
DECLARE_PMID(kImplementationIDSpace, kSecondPhaseUndoRedoHandlerImpl, kAppFrameworkPrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kSelectionThumbnailTextCSBImpl, kAppFrameworkPrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kVSizeBaselineImpl, kAppFrameworkPrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kSnapshotDBStreamWriteImpl, kAppFrameworkPrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kCompareStreamImpl, kAppFrameworkPrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kM2MMessageManagerImpl, kAppFrameworkPrefix + 105)
DECLARE_PMID(kImplementationIDSpace, kM2MMessageListenerServiceProviderImpl, kAppFrameworkPrefix + 106)
DECLARE_PMID(kImplementationIDSpace, kHierarchyM2MListenerImpl, kAppFrameworkPrefix + 107)
DECLARE_PMID(kImplementationIDSpace, kThreadProgressBarManagerImpl, kAppFrameworkPrefix + 108)
DECLARE_PMID(kImplementationIDSpace, kTaskMonitorScriptProviderImpl,	kAppFrameworkPrefix + 109)
DECLARE_PMID(kImplementationIDSpace, kBackgroundTaskScriptImpl,	kAppFrameworkPrefix + 110)
DECLARE_PMID(kImplementationIDSpace, kAsyncWorkManagerAppFlagsIdleTaskImpl, kAppFrameworkPrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kSaLRIBlockDBStreamWriteImpl, kAppFrameworkPrefix + 112)
DECLARE_PMID(kImplementationIDSpace, kIDThreadServiceRegistryImpl, kAppFrameworkPrefix + 113)
DECLARE_PMID(kImplementationIDSpace, kScriptInfoMgrStartupShutdownImpl, kAppFrameworkPrefix + 114)
DECLARE_PMID(kImplementationIDSpace, kScriptInfoMgrServiceProviderImpl, kAppFrameworkPrefix + 115)
DECLARE_PMID(kImplementationIDSpace, kBGTasksUtilsImpl, kAppFrameworkPrefix + 116)
DECLARE_PMID(kImplementationIDSpace, kApplicationDefaultsUtilsImpl, kAppFrameworkPrefix + 117)
DECLARE_PMID(kImplementationIDSpace, kTaskMonitorIdleTaskImpl, kAppFrameworkPrefix + 118)
DECLARE_PMID(kImplementationIDSpace, kAsyncWorkManagerInitIdleTaskImpl, kAppFrameworkPrefix + 119)
DECLARE_PMID(kImplementationIDSpace, kPrivateBGTasksUtilsImpl, kAppFrameworkPrefix + 120)
DECLARE_PMID(kImplementationIDSpace, kTaskMonitorFacadeImpl, kAppFrameworkPrefix + 121)
DECLARE_PMID(kImplementationIDSpace, kSettingsMigrationStartupShutdownImpl, kAppFrameworkPrefix + 122)
DECLARE_PMID(kImplementationIDSpace, kSettingsMigrationImpl , kAppFrameworkPrefix + 123)
DECLARE_PMID(kImplementationIDSpace, kSettingsMigrationManagerImpl, kAppFrameworkPrefix + 124)
DECLARE_PMID(kImplementationIDSpace, kProcessSettingsMigrationCmdImpl, kAppFrameworkPrefix + 125)
DECLARE_PMID(kImplementationIDSpace, kVulcanMessengerImpl, kAppFrameworkPrefix + 126)
DECLARE_PMID(kImplementationIDSpace, kVulcanStartupShutdownServiceImpl, kAppFrameworkPrefix + 127)
DECLARE_PMID(kImplementationIDSpace, kABTestingFeatureMapImpl, kAppFrameworkPrefix + 128)
DECLARE_PMID(kImplementationIDSpace, kABTestingObserverImpl, kAppFrameworkPrefix + 129)
DECLARE_PMID(kImplementationIDSpace, kABTestingUtilsImpl, kAppFrameworkPrefix + 130)
DECLARE_PMID(kImplementationIDSpace, kTemporaryDataForLoggingImpl, kAppFrameworkPrefix + 131)
DECLARE_PMID(kImplementationIDSpace, kCommentsImportProviderUtilsImpl, kAppFrameworkPrefix + 132)
DECLARE_PMID(kImplementationIDSpace, kNglStartupShutdownImpl, kAppFrameworkPrefix + 133)
DECLARE_PMID(kImplementationIDSpace, kNglOnLaunchCmdImpl, kAppFrameworkPrefix + 134)
DECLARE_PMID(kImplementationIDSpace, kNGLWorkflowLauncherIdleTaskImpl, kAppFrameworkPrefix + 135)
DECLARE_PMID(kImplementationIDSpace, kGoCartLauncherIdleTaskImpl, kAppFrameworkPrefix + 136)
DECLARE_PMID(kImplementationIDSpace, kNormalModeIAMDocMapImpl, kAppFrameworkPrefix + 137)

// <Message ID>
DECLARE_PMID(kMessageIDSpace, kVulcanUsageContextDataResponseMessage, kAppFrameworkPrefix + 1)
DECLARE_PMID(kMessageIDSpace, kAdobeDesktopServiceHasStartedMessage, kAppFrameworkPrefix + 2)

// <Service ID>
DECLARE_PMID(kServiceIDSpace, kAppChangesSignalResponderService,			kAppFrameworkPrefix + 1)
DECLARE_PMID(kServiceIDSpace, kAutomationService,							kAppFrameworkPrefix + 2)
DECLARE_PMID(kServiceIDSpace, kUserActionPersonalityService,				kAppFrameworkPrefix + 3)
DECLARE_PMID(kServiceIDSpace, kRIDXNotifierService,							kAppFrameworkPrefix + 4)
DECLARE_PMID(kServiceIDSpace, kM2MMessageListenerService,					kAppFrameworkPrefix + 5)
DECLARE_PMID(kServiceIDSpace, kWorkerThreadSessionUpdateRespService,		kAppFrameworkPrefix + 6)
DECLARE_PMID(kServiceIDSpace, kSettingsMigrationService,					kAppFrameworkPrefix + 7)
DECLARE_PMID(kServiceIDSpace, kNglProfileSignInService,						kAppFrameworkPrefix + 8)
DECLARE_PMID(kServiceIDSpace, kNglProfileSignOutService,					kAppFrameworkPrefix + 9)
DECLARE_PMID(kServiceIDSpace, kNglInitialProfileService,					kAppFrameworkPrefix + 10)

// Service IDs
// Error Codes

// <Error ID>
DECLARE_PMID(kErrorIDSpace, kUserActionStreamErr,							kAppFrameworkPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kUserActionWrongDocType,						kAppFrameworkPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kCannotUndoError,								kAppFrameworkPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kCannotRedoError,								kAppFrameworkPrefix + 4)
DECLARE_PMID(kErrorIDSpace, kCannotSetPortError,							kAppFrameworkPrefix + 5)
DECLARE_PMID(kErrorIDSpace, kCannotSetConfigurationError,					kAppFrameworkPrefix + 6)
DECLARE_PMID(kErrorIDSpace, kActionsEventNotHandledError,					kAppFrameworkPrefix + 7)
DECLARE_PMID(kErrorIDSpace, kCannotSetContentAwareFitPrefOnWin32Error,		kAppFrameworkPrefix + 8)
DECLARE_PMID(kErrorIDSpace, kRecoveryScriptMethodInternalUseError,			kAppFrameworkPrefix + 9)

// InvalHandlerTypeID
DECLARE_PMID(kInvalHandlerIDSpace, kM2MMessageManagerInvalHandlerID, kAppFrameworkPrefix + 1)

// <Ignore>


// <Global ID>
// ActionIDs

// <ViewPortAttr ID>
// ViewPortAttrIDs
DECLARE_PMID(kViewPortAttrIDSpace, kDisableTimedUpdatesVPAttr, kAppFrameworkPrefix + 1)
DECLARE_PMID(kViewPortAttrIDSpace, kCapturePortForRasterVPAttr, kAppFrameworkPrefix + 2)
DECLARE_PMID(kViewPortAttrIDSpace, kZoomIndependenceVPAttr, kAppFrameworkPrefix + 3)
DECLARE_PMID(kViewPortAttrIDSpace, kAcceleratedDrawingVPAttr, kAppFrameworkPrefix + 4)

//
//Script Element IDs
//
DECLARE_PMID(kScriptInfoIDSpace, kActionTargetingScriptID, 						kAppFrameworkPrefix + 10)

//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kApplicationObjectScriptElement,				kAppFrameworkPrefix + 40)
DECLARE_PMID(kScriptInfoIDSpace, kBackgroundTaskObjectScriptElement,			kAppFrameworkPrefix + 41)

//Events
DECLARE_PMID(kScriptInfoIDSpace, kBeforeQuitEventScriptElement,					kAppFrameworkPrefix + 56)
DECLARE_PMID(kScriptInfoIDSpace, kAfterQuitEventScriptElement,					kAppFrameworkPrefix + 57)

//Methods
DECLARE_PMID(kScriptInfoIDSpace, kActivateMethodScriptElement,					kAppFrameworkPrefix + 80)
DECLARE_PMID(kScriptInfoIDSpace, kQuitMethodScriptElement,						kAppFrameworkPrefix + 81)
DECLARE_PMID(kScriptInfoIDSpace, kTileMethodScriptElement,						kAppFrameworkPrefix + 82)
DECLARE_PMID(kScriptInfoIDSpace, kCascadeMethodScriptElement,					kAppFrameworkPrefix + 83)
DECLARE_PMID(kScriptInfoIDSpace, kUndoMethodScriptElement,						kAppFrameworkPrefix + 84)
DECLARE_PMID(kScriptInfoIDSpace, kRedoMethodScriptElement,						kAppFrameworkPrefix + 85)
DECLARE_PMID(kScriptInfoIDSpace, kOpenMethodScriptElement,						kAppFrameworkPrefix + 88)
DECLARE_PMID(kScriptInfoIDSpace, kDoScriptMethodScriptElement,					kAppFrameworkPrefix + 89)
DECLARE_PMID(kScriptInfoIDSpace, kConsoleOutMethodScriptElement,				kAppFrameworkPrefix + 90)
DECLARE_PMID(kScriptInfoIDSpace, kConsoleErrMethodScriptElement,				kAppFrameworkPrefix + 91)
DECLARE_PMID(kScriptInfoIDSpace, kClearAllErrorsMethodScriptElement,			kAppFrameworkPrefix + 92)
DECLARE_PMID(kScriptInfoIDSpace, kFindKeyStringsMethodScriptElement,			kAppFrameworkPrefix + 95)
DECLARE_PMID(kScriptInfoIDSpace, kTranslateKeyStringMethodScriptElement,		kAppFrameworkPrefix + 96)
DECLARE_PMID(kScriptInfoIDSpace, kResolveSpecifierMethodScriptElement,			kAppFrameworkPrefix + 97)
DECLARE_PMID(kScriptInfoIDSpace, kGenerateINXSchemaScriptElement,				kAppFrameworkPrefix + 98)
DECLARE_PMID(kScriptInfoIDSpace, kLanguageRegionEnumScriptElement,				kAppFrameworkPrefix + 99)
DECLARE_PMID(kScriptInfoIDSpace, kCancelBackgroundTaskMethodScriptElement,		kAppFrameworkPrefix + 100)
DECLARE_PMID(kScriptInfoIDSpace, kCancelAllBackgroundTasksMethodScriptElement,	kAppFrameworkPrefix + 101)
DECLARE_PMID(kScriptInfoIDSpace, kWaitForBackgroundTaskMethodScriptElement,		kAppFrameworkPrefix + 102)
DECLARE_PMID(kScriptInfoIDSpace, kWaitForAllBackgroundTasksMethodScriptElement,	kAppFrameworkPrefix + 103)
DECLARE_PMID(kScriptInfoIDSpace, kQueryBackgroundTaskInfoMethodScriptElement,	kAppFrameworkPrefix + 104)
DECLARE_PMID(kScriptInfoIDSpace, kSetApplicationPreferencesScriptElement,		kAppFrameworkPrefix + 105)
DECLARE_PMID(kScriptInfoIDSpace, kRecoverMethodScriptElement,                   kAppFrameworkPrefix + 106)

//Functions
DECLARE_PMID(kScriptInfoIDSpace, kDoScriptFunctionScriptElement,				kAppFrameworkPrefix + 110)

//Metadata
DECLARE_PMID(kScriptInfoIDSpace, kAllowAppMethodsWithModalDialogMetadataScriptElement,	kAppFrameworkPrefix + 120)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kActiveDocumentPropertyScriptElement,			kAppFrameworkPrefix + 160)
DECLARE_PMID(kScriptInfoIDSpace, kActiveWindowPropertyScriptElement,			kAppFrameworkPrefix + 161)
DECLARE_PMID(kScriptInfoIDSpace, kCurrentScriptPropertyScriptElement,			kAppFrameworkPrefix + 162)
DECLARE_PMID(kScriptInfoIDSpace, kCurrentScriptUndoModePropertyScriptElement,	kAppFrameworkPrefix + 163)
DECLARE_PMID(kScriptInfoIDSpace, kSerialNumberPropertyScriptElement,			kAppFrameworkPrefix + 164)
DECLARE_PMID(kScriptInfoIDSpace, kPercentDonePropertyScriptElement,				kAppFrameworkPrefix + 165)
DECLARE_PMID(kScriptInfoIDSpace, kFeatureSetPropertyScriptElement,				kAppFrameworkPrefix + 166)
DECLARE_PMID(kScriptInfoIDSpace, kUserInteractionLevelPropertyScriptElement,	kAppFrameworkPrefix + 167)
DECLARE_PMID(kScriptInfoIDSpace, kVersionPropertyScriptElement,					kAppFrameworkPrefix + 168)
DECLARE_PMID(kScriptInfoIDSpace, kLocalePropertyScriptElement,					kAppFrameworkPrefix + 169)
DECLARE_PMID(kScriptInfoIDSpace, kUndoNamePropertyScriptElement,				kAppFrameworkPrefix + 170)
DECLARE_PMID(kScriptInfoIDSpace, kRedoNamePropertyScriptElement,				kAppFrameworkPrefix + 171)
DECLARE_PMID(kScriptInfoIDSpace, kPalettesVisiblePropertyScriptElement,			kAppFrameworkPrefix + 172)
DECLARE_PMID(kScriptInfoIDSpace, kUndoHistoryPropertyScriptElement,				kAppFrameworkPrefix + 173)
DECLARE_PMID(kScriptInfoIDSpace, kRedoHistoryPropertyScriptElement,				kAppFrameworkPrefix + 174)
DECLARE_PMID(kScriptInfoIDSpace, kEnableUndoPropertyScriptElement,				kAppFrameworkPrefix + 175)
DECLARE_PMID(kScriptInfoIDSpace, kPortPropertyScriptElement,					kAppFrameworkPrefix + 176)
DECLARE_PMID(kScriptInfoIDSpace, kConfigurationPropertyScriptElement,			kAppFrameworkPrefix + 177)
DECLARE_PMID(kScriptInfoIDSpace, kApplicationModalStatePropertyScriptElement,	kAppFrameworkPrefix + 178)
DECLARE_PMID(kScriptInfoIDSpace, kTaskStatusPropertyScriptElement,				kAppFrameworkPrefix + 179)
DECLARE_PMID(kScriptInfoIDSpace, kDocumentNamePropertyScriptElement,			kAppFrameworkPrefix + 180)
DECLARE_PMID(kScriptInfoIDSpace, kTaskAlertsPropertyScriptElement,				kAppFrameworkPrefix + 181)
//gap
DECLARE_PMID(kScriptInfoIDSpace, kServerAdminPortScriptElement,					kAppFrameworkPrefix + 185)
DECLARE_PMID(kScriptInfoIDSpace, kServerHostNameScriptElement,					kAppFrameworkPrefix + 186)
DECLARE_PMID(kScriptInfoIDSpace, kUserAdobeIDPropertyScriptElement,				kAppFrameworkPrefix + 187)
DECLARE_PMID(kScriptInfoIDSpace, kUserGUIDPropertyScriptElement,				kAppFrameworkPrefix + 188)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kUserInteractionLevelsEnumScriptElement,		kAppFrameworkPrefix + 220)
DECLARE_PMID(kScriptInfoIDSpace, kLocaleEnumScriptElement,						kAppFrameworkPrefix + 221)
DECLARE_PMID(kScriptInfoIDSpace, kScriptLanguageEnumScriptElement,				kAppFrameworkPrefix + 222)
DECLARE_PMID(kScriptInfoIDSpace, kFeatureSetEnumScriptElement,					kAppFrameworkPrefix + 223)
DECLARE_PMID(kScriptInfoIDSpace, kUndoModeEnumScriptElement,					kAppFrameworkPrefix + 224)
DECLARE_PMID(kScriptInfoIDSpace, kOpenOptionsEnumScriptElement,					kAppFrameworkPrefix + 225)
DECLARE_PMID(kScriptInfoIDSpace, kTaskStateEnumScriptElement,					kAppFrameworkPrefix + 226)
DECLARE_PMID(kScriptInfoIDSpace, kTaskAlertTypeEnumScriptElement,				kAppFrameworkPrefix + 227)

//ScriptIDs
enum AppFrameworkScriptIDs
{
	c_BackgroundTask		= 'cBKT',
	c_BackgroundTasks		= 'cBTs',
	e_FindKeyStrings		= 'eFKS',
	e_TranslateKeyString	= 'eTKS',
	e_ResolveSpecifier		= 'RSpc',
	e_CancelBackgroundTask	= 'TCbt',
	e_CancelAllBackgroundTasks = 'TCAt',
	e_WaitForBackgroundTask = 'TWbt',
	e_WaitForAllBackgroundTasks = 'TWAt',
	e_QueryBackgroundTaskInfo = 'TQin',
	e_SetApplicationPreferences	= 'sApp',
    
	e_BeforeQuit			= 'eBQu',
	e_AfterQuit				= 'eAQu',

	p_SerialNumber			= 'SeNu',
	p_PercentDone			= 'pDon',
	p_DocumentName			= 'pDcN',
	p_OpenOption			= 'pOpp',
	p_Alerts				= 'pAlr',
	p_ApplicationPreferencesSet	= 'pApp',
	
	p_ServerAdminPort		= 'pSaP',
	p_ServerHostName		= 'pShN',

	en_OpenOptions			= 'OpOp',
	en_OpenOriginal			= 'OpOr',
	en_OpenCopy				= 'OpCp',

	en_TaskState			= 'enTS',
	en_Queued				= 'eQue',
	en_Running				= 'eTru',
	en_Waiting				= 'eWat',
	en_Cancelling			= 'eTca',
	en_Completed			= 'eTcp',
	en_Cancelled			= 'eTcl',
	
	en_TaskAlertType		= 'enTA',
	en_InformationMsg		= 'eIMs',
	en_WarningMsg			= 'eWMs',
	en_ErrorMsg				= 'eEMs',
	en_LanguageRegion		= 'eLnR',

	// InDesign Server
	e_ConsoleOut			= 'cnso',
	e_ConsoleErr			= 'cnse',
	p_Message				= 'MSge',
	e_ClearAllErrors		= 'clae',
    p_recoveryParam         = 'rcvp',
} ;

//GUIDS
// {ABD4CBB2-0CFE-11d1-801D-0060B03C02E4}
#define k_Application_CLSID { 0xabd4cbb2, 0xcfe, 0x11d1, { 0x80, 0x1d, 0x0, 0x60, 0xb0, 0x3c, 0x2, 0xe4 } }
DECLARE_GUID( _Application_CLSID, k_Application_CLSID ) ;		//Use DECLARE_GUID for any GUID that is referenced in C++ code
// {296CAEB5-C99C-4b3e-9359-6E7D6EAE71FC}
#define kIDApplication_CLSID { 0x296caeb5, 0xc99c, 0x4b3e, { 0x93, 0x59, 0x6e, 0x7d, 0x6e, 0xae, 0x71, 0xfc } }
DECLARE_GUID( IDApplication_CLSID, kIDApplication_CLSID ) ;		//Use DECLARE_GUID for any GUID that is referenced in C++ code
// {CAC1EF5D-EFF1-4f16-B67D-54E603F31FAE}
#define kICApplication_CLSID { 0xcac1ef5d, 0xeff1, 0x4f16, { 0xb6, 0x7d, 0x54, 0xe6, 0x3, 0xf3, 0x1f, 0xae } }
DECLARE_GUID( ICApplication_CLSID, kICApplication_CLSID ) ;		//Use DECLARE_GUID for any GUID that is referenced in C++ code

// {D5F580C2-0126-4256-87EA-06444945B78E}
#define kBackgroundTask_CLSID { 0xd5f580c2, 0x126, 0x4256, { 0x87, 0xea, 0x6, 0x44, 0x49, 0x45, 0xb7, 0x8e } }
// {381D8C13-E90F-4b4b-9A2D-30DAEF628D05}
#define kBackgroundTasks_CLSID { 0x381d8c13, 0xe90f, 0x4b4b, { 0x9a, 0x2d, 0x30, 0xda, 0xef, 0x62, 0x8d, 0x5 } }

#endif //__AppFrameworkID__
