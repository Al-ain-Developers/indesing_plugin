//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ScriptingID.h $
//  
//  Owner: Jonathan W. Brown
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
//  Info:	Contains IDs used by the scripting architecture.
//  
//========================================================================================

#ifndef __SCRIPTINGID__
#define __SCRIPTINGID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"
#include "FormatNumber.h"

#define kScriptingPrefix	 RezLong(0x7700)

//**********************************************************************************************************
// RsrcID
//**********************************************************************************************************
#define kScriptIconResID				129
#define kScriptingStringsRsrcID			7000
#define kScriptingStringsNoTransRsrcID	7100
#define kScriptErrorStringTableRsrcID	7002

//**********************************************************************************************************
// PluginID
//**********************************************************************************************************
#define kScriptPluginName 					"Scripting"
DECLARE_PMID(kPlugInIDSpace, kScriptPluginID, kScriptingPrefix + 1)

//**********************************************************************************************************
// ClassIDs
//**********************************************************************************************************
DECLARE_PMID(kClassIDSpace, kScriptStartupShutdownBoss,					kScriptingPrefix + 1)
DECLARE_PMID(kClassIDSpace, kScriptInfoManagerBoss,						kScriptingPrefix + 2)
DECLARE_PMID(kClassIDSpace, kCScriptRequestDataBoss,					kScriptingPrefix + 3)
DECLARE_PMID(kClassIDSpace, kCoreScriptManagerBoss,						kScriptingPrefix + 4)
DECLARE_PMID(kClassIDSpace, kScriptInfoInitializerBoss,					kScriptingPrefix + 5)
DECLARE_PMID(kClassIDSpace, kScriptInfoInitializer2Boss,				kScriptingPrefix + 6)
DECLARE_PMID(kClassIDSpace, kScriptingConversionProviderBoss,			kScriptingPrefix + 7)
DECLARE_PMID(kClassIDSpace, kScriptErrorStringServiceBoss,				kScriptingPrefix + 8)
DECLARE_PMID(kClassIDSpace, kBaseProxyScriptObjectBoss,					kScriptingPrefix + 9)
DECLARE_PMID(kClassIDSpace, kBasePrefsScriptObjectBoss,					kScriptingPrefix + 10)
DECLARE_PMID(kClassIDSpace, kBaseScriptProviderBoss,					kScriptingPrefix + 11)
DECLARE_PMID(kClassIDSpace, kBaseObjectScriptProviderBoss,				kScriptingPrefix + 12)
DECLARE_PMID(kClassIDSpace, kSetScriptingTagCmdBoss,					kScriptingPrefix + 13)
DECLARE_PMID(kClassIDSpace, kObsoleteFeatureScriptProviderBoss,			kScriptingPrefix + 14)
DECLARE_PMID(kClassIDSpace, kSetGlobalScriptPrefsCmdBoss,				kScriptingPrefix + 15)
DECLARE_PMID(kClassIDSpace, kScriptPrefsScriptProviderBoss,				kScriptingPrefix + 16)
DECLARE_PMID(kClassIDSpace, kScriptArgsScriptProviderBoss,				kScriptingPrefix + 17)
DECLARE_PMID(kClassIDSpace, kProxyScriptObjectEventTargetBoss,			kScriptingPrefix + 18)
DECLARE_PMID(kClassIDSpace, kScriptEventScriptProviderBoss,				kScriptingPrefix + 19)
DECLARE_PMID(kClassIDSpace, kBaseScriptEventBoss,						kScriptingPrefix + 20)
DECLARE_PMID(kClassIDSpace, kEnableAttachabilityCmdBoss,				kScriptingPrefix + 21)
DECLARE_PMID(kClassIDSpace, kScriptEventListenerBoss,					kScriptingPrefix + 22)
DECLARE_PMID(kClassIDSpace, kPreferencesScriptProviderBoss,				kScriptingPrefix + 23)
DECLARE_PMID(kClassIDSpace, kScriptInfoDatabaseBoss,					kScriptingPrefix + 24)
DECLARE_PMID(kClassIDSpace, kScriptInstanceProcessorBoss,				kScriptingPrefix + 25)
DECLARE_PMID(kClassIDSpace, kObsoletePrefsScriptProviderBoss,			kScriptingPrefix + 26)
DECLARE_PMID(kClassIDSpace, kAttachabilityIdleTaskBoss,					kScriptingPrefix + 27)
DECLARE_PMID(kClassIDSpace, kIdleTaskScriptEventBoss,					kScriptingPrefix + 28)
DECLARE_PMID(kClassIDSpace, kMutationScriptEventBoss,					kScriptingPrefix + 29)
DECLARE_PMID(kClassIDSpace, kAttachableIdleTaskScriptProviderBoss,		kScriptingPrefix + 30)
DECLARE_PMID(kClassIDSpace, kAttachableIdleEventScriptProviderBoss,		kScriptingPrefix + 31)
DECLARE_PMID(kClassIDSpace, kScriptSettingsMigrationServiceProviderBoss,kScriptingPrefix + 32)

//**********************************************************************************************************
// IIDs
//**********************************************************************************************************
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTMANAGER,						kScriptingPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTREQUESTHANDLER,				kScriptingPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPT,							kScriptingPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTPROVIDER,					kScriptingPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTDATACONVERTER,				kScriptingPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTREQUESTDATA,					kScriptingPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTDATASPECIFIC,				kScriptingPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTPREFERENCES,					kScriptingPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTSPANELUTILS,					kScriptingPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTVERSIONINFO,					kScriptingPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTPERSIST,						kScriptingPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTERRORUTILS,					kScriptingPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTERROR,						kScriptingPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTLABEL,						kScriptingPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTFILEMANAGER,					kScriptingPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTEVENTTARGET,					kScriptingPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTOBSERVER,					kScriptingPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTOBJECTPARENT,				kScriptingPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTRUNNER,						kScriptingPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTSELECTIONSUITE,				kScriptingPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTUTILS,						kScriptingPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTINFOMANAGER,					kScriptingPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTINFOMANAGERFACTORY,			kScriptingPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTTAGCMDDATA,					kScriptingPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTARGS,						kScriptingPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTDOMHELPER,					kScriptingPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTCOREFUNCTOR,					kScriptingPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTEVENTLISTENER,				kScriptingPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTOBJECTMGR,					kScriptingPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTEVENT,						kScriptingPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTATTACHABILITYPREFS,			kScriptingPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTFILELOCATIONS,				kScriptingPrefix + 32)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTINFODATABASE,				kScriptingPrefix + 33)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTENGINE,						kScriptingPrefix + 34)
DECLARE_PMID(kInterfaceIDSpace, IID_IGLOBALSCRIPTPREFERENCES,			kScriptingPrefix + 35)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTMUTATIONDATA,				kScriptingPrefix + 36)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPTCLIENTOBJECTDATA,			kScriptingPrefix + 37)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRIVATESCRIPTIDLETASKINFO, 		kScriptingPrefix + 38)
DECLARE_PMID(kInterfaceIDSpace, IID_IATTACHABLEIDLETASKID, 				kScriptingPrefix + 39)
DECLARE_PMID(kInterfaceIDSpace, IID_IATTACHABLEIDLETASKTIMEALLOC,		kScriptingPrefix + 40)

// IID_ISCRIPT_LABEL and IID_ISCRIPT_KEY_DPS are faux messages generated to let the client listeners know what kind of script key change occurred.
// If a DPS label changes or gets deleted, then IID_ISCRIPT_KEY_DPS is sent to clients, else IID_ISCRIPT_LABEL is generated.
// In CS6, the only known listener is the sharedContent plug-in which uses this to distinguish between DPS and non-DPS keys.
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPT_LABEL,						kScriptingPrefix + 41)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRIPT_KEY_DPS,					kScriptingPrefix + 42)

//**********************************************************************************************************
// Implementation IDs
//**********************************************************************************************************
DECLARE_PMID(kImplementationIDSpace, kScriptUtilsImpl,					kScriptingPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kScriptStartupShutdownImpl,		kScriptingPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kScriptManagerServiceImpl,			kScriptingPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kCScriptRequestDataImpl,			kScriptingPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kScriptServiceImpl,				kScriptingPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kScriptLabelKeyDataImpl, 			kScriptingPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kScriptPreferencesImpl, 			kScriptingPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kSetGlobalScriptPrefsCmdImpl, 		kScriptingPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kCRootStyleGroupScriptImpl, 		kScriptingPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kScriptInfoInitializer2Impl,		kScriptingPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kSetScriptingTagCmdImpl,			kScriptingPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kScriptRequestHandlerImpl,			kScriptingPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kApplicationScriptImpl_Obsolete,	kScriptingPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kScriptErrorStringServiceImpl,		kScriptingPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kDocumentScriptImpl_Obsolete,		kScriptingPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kScriptObjectMgrImpl,				kScriptingPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kLayerScriptImpl_Obsolete,			kScriptingPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kScriptObjectParentImpl,			kScriptingPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kSpreadScriptImpl_Obsolete,		kScriptingPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kBaseObjectScriptProviderImpl,		kScriptingPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kScriptPrefsScriptProviderImpl,	kScriptingPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kScriptDOMHelperImpl,				kScriptingPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kPageScriptImpl_Obsolete,			kScriptingPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kPrefsScriptImpl,					kScriptingPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kPageItemScriptImpl_Obsolete,		kScriptingPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kScriptInfoManagerFactoryImpl,		kScriptingPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kScriptErrorUtilsImpl,				kScriptingPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kGlobalScriptPreferencesImpl,		kScriptingPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kScriptInfoManagerImpl,			kScriptingPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kLinkScriptImpl_Obsolete,			kScriptingPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kCProxyScriptImpl,					kScriptingPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kScriptErrorImpl,					kScriptingPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kScriptTagCmdDataImpl,				kScriptingPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kScriptArgsImpl,					kScriptingPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kScriptArgsScriptProviderImpl,		kScriptingPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kStoryScriptImpl_Obsolete,			kScriptingPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kScriptAppResumeObserverImpl,		kScriptingPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kScriptLabelImpl,					kScriptingPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kScriptsPanelFileManagerImpl,		kScriptingPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kScriptVersionInfoImpl,			kScriptingPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kObsoleteFeatureScriptProviderImpl,kScriptingPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kScriptEventListenerScriptImpl,	kScriptingPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kScriptAttachabilityPrefsImpl,		kScriptingPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kEnableAttachabilityCmdImpl,		kScriptingPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kWindowScriptImpl_Obsolete,		kScriptingPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kScriptEventScriptProviderImpl,	kScriptingPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kCScriptEventTargetImpl,			kScriptingPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kScriptEventImpl,					kScriptingPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kScriptEventScriptImpl,			kScriptingPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kScriptEventListenerImpl,			kScriptingPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kScriptFileLocationsImpl,			kScriptingPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kAllScriptsFileManagerImpl,		kScriptingPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kPreferencesScriptProviderImpl,	kScriptingPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kSwatchScriptImpl_Obsolete,		kScriptingPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kScriptInfoDatabaseImpl,			kScriptingPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kScriptInstanceProcessorImpl,		kScriptingPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kObsoletePrefsScriptProviderImpl,	kScriptingPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kSingleScriptEngineImpl,			kScriptingPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kScriptPreferencesConstVersionImpl,kScriptingPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kAttachabilityIdleTaskImpl,		kScriptingPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kGuideScriptImpl_Obsolete,			kScriptingPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kScriptMutationDataImpl,			kScriptingPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kAttachableIdleTaskScriptImpl,		kScriptingPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kAttachableIdleTaskScriptProviderImpl,		kScriptingPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kPrivateScriptIdleTaskInfoImpl,	kScriptingPrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kAttachableIdleTaskIDImpl,			kScriptingPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kAttachableIdleEventScriptProviderImpl,	kScriptingPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kAttachableIdleTaskTimeAllocImpl,	kScriptingPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kProxyScriptEventTargetImpl,		kScriptingPrefix + 69)
//gap
DECLARE_PMID(kImplementationIDSpace, kSectionScriptImpl_Obsolete,		kScriptingPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kScriptClientObjectDataImpl,		kScriptingPrefix + 72)
//gap
DECLARE_PMID(kImplementationIDSpace, kStyleScriptImpl_Obsolete,			kScriptingPrefix + 90)
//gap
DECLARE_PMID(kImplementationIDSpace, kLanguageScriptImpl_Obsolete,		kScriptingPrefix + 135)
//gap
DECLARE_PMID(kImplementationIDSpace, kExportPDFStyleScriptImpl_Obsolete, kScriptingPrefix + 214)
//gap
DECLARE_PMID(kImplementationIDSpace, kCompositeFontScriptImpl_Obsolete, kScriptingPrefix + 224)
//gap
DECLARE_PMID(kImplementationIDSpace, kCompositeFontEntryScriptImpl_Obsolete, kScriptingPrefix + 227)
DECLARE_PMID(kImplementationIDSpace, kBeforeRunScriptSignalRespServiceImpl, kScriptingPrefix + 228)
DECLARE_PMID(kImplementationIDSpace, kAfterRunScriptSignalRespServiceImpl, kScriptingPrefix + 229)
DECLARE_PMID(kImplementationIDSpace, kScriptManagerService_MainThreadOnlyImpl,			kScriptingPrefix + 230)
DECLARE_PMID(kImplementationIDSpace, kScriptSettingsMigrationImpl,			kScriptingPrefix + 231)

// Service IDs
DECLARE_PMID(kServiceIDSpace, kScriptManagerService,					kScriptingPrefix + 1)
DECLARE_PMID(kServiceIDSpace, kScriptProviderService,					kScriptingPrefix + 2)
DECLARE_PMID(kServiceIDSpace, kBeforeRunScriptSignalResponderService, 	kScriptingPrefix + 3)
DECLARE_PMID(kServiceIDSpace, kAfterRunScriptSignalResponderService, 	kScriptingPrefix + 4)

// <Performance Metric IDs>
DECLARE_PMID(kPerformanceMetricIDSpace,	kNumberOfEventsDispatchedPerfID,			kScriptingPrefix + 1)
DECLARE_PMID(kPerformanceMetricIDSpace,	kNumberOfAttachedScriptsExecutedPerfID,		kScriptingPrefix + 2)
DECLARE_PMID(kPerformanceMetricIDSpace,	kTotalDispatchTimePerfID,					kScriptingPrefix + 3)


//**********************************************************************************************************
// DontShowAlertIDs
//**********************************************************************************************************

#define kDontShowEventListenerErrorAlert	kScriptingPrefix + 1

//**********************************************************************************************************
// Error Codes
//**********************************************************************************************************

	//********* The following errors don't have string entries in our string table. 
	//We use the defined ID as a core id but intercept the errors within each 
	//scripting client in order to returning a client-specific error.
#define kFirstScriptErrorWithoutString									kScriptingPrefix + 1
	DECLARE_PMID(kErrorIDSpace, kRequestNotHandledError,					kScriptingPrefix + 1)
	DECLARE_PMID(kErrorIDSpace, kReqParamMissing,							kScriptingPrefix + 2)	//obsolete; use kMissingRequiredParameterError
#define kLastScriptErrorWithoutString									kScriptingPrefix + 5

	//********* Script Architecture Errors are those related to misuse of the scripting architecture.
#define kFirstScriptArchitectureError									kScriptingPrefix + 6
	//gap
	DECLARE_PMID(kErrorIDSpace, kReadOnlyPropertyError,						kScriptingPrefix + 10)
	DECLARE_PMID(kErrorIDSpace, kInvalidCollectionItemError,				kScriptingPrefix + 11)
	DECLARE_PMID(kErrorIDSpace, kObjectDeletedError,						kScriptingPrefix + 12)
	DECLARE_PMID(kErrorIDSpace, kInvalidParameterError,						kScriptingPrefix + 13)
	//gap
	DECLARE_PMID(kErrorIDSpace, kMissingRequiredParameterError,				kScriptingPrefix + 15)
	DECLARE_PMID(kErrorIDSpace, kNoDataOfTheRequestedTypeError,				kScriptingPrefix + 16)
	DECLARE_PMID(kErrorIDSpace, kOutOfRangeError,							kScriptingPrefix + 17)
	DECLARE_PMID(kErrorIDSpace, kInvalidCreateOnCollectionError,			kScriptingPrefix + 18)
	DECLARE_PMID(kErrorIDSpace, kCannotCompileScriptErr,					kScriptingPrefix + 19)
	DECLARE_PMID(kErrorIDSpace, kScriptExecutionCanceled,					kScriptingPrefix + 20)
	DECLARE_PMID(kErrorIDSpace, kIncompatibleScriptLanguageError,			kScriptingPrefix + 21)
	DECLARE_PMID(kErrorIDSpace, kModalDialogOpenError,						kScriptingPrefix + 22)
	DECLARE_PMID(kErrorIDSpace, kSetPropertiesFailedCompletelyError,		kScriptingPrefix + 23)
	DECLARE_PMID(kErrorIDSpace, kGetPropertiesFailedCompletelyError,		kScriptingPrefix + 24)
	DECLARE_PMID(kErrorIDSpace, kHandleMethodFailedCompletelyError,			kScriptingPrefix + 25)
	DECLARE_PMID(kErrorIDSpace, kNoScriptFileAvailableError,				kScriptingPrefix + 26)
	DECLARE_PMID(kErrorIDSpace, kNaNError,									kScriptingPrefix + 27)
	DECLARE_PMID(kErrorIDSpace, kUnrecognizedEventTypeError,				kScriptingPrefix + 28)
	DECLARE_PMID(kErrorIDSpace, kCantDeleteTargetOfActiveScriptEvent,		kScriptingPrefix + 29)
	//gap
#define kLastScriptArchitectureError									kScriptingPrefix + 149

	//********* User-oriented Errors are those that a non-scripting language client of the scripting 
	//architecture (e.g., Action Automation) can safely display to a user; generally they are errors 
	//related to feature functionality rather than to misuse of the scripting architecture.
#define kFirstUserOrientedScriptError									kScriptingPrefix + 150
	DECLARE_PMID(kErrorIDSpace, kInvalidScriptTargetError,					kScriptingPrefix + 150)	//return when an invalid object is passed to a script provider
	DECLARE_PMID(kErrorIDSpace, kPropertyNotApplicableError,				kScriptingPrefix + 151)
	DECLARE_PMID(kErrorIDSpace, kPropertyValueLockedError,					kScriptingPrefix + 152)
	DECLARE_PMID(kErrorIDSpace, kCantDeleteDefaultStyleError,				kScriptingPrefix + 153)
	DECLARE_PMID(kErrorIDSpace, kCantRenameThisItemError,					kScriptingPrefix + 154)
	DECLARE_PMID(kErrorIDSpace, kItemWithThisNameAlreadyExistsError,		kScriptingPrefix + 155)
	DECLARE_PMID(kErrorIDSpace, kInvalidVersionNumberError,					kScriptingPrefix + 156)
	DECLARE_PMID(kErrorIDSpace, kObjectFromDifferentDatabaseError,			kScriptingPrefix + 157)
	DECLARE_PMID(kErrorIDSpace, kObsoleteScriptingRequestError,				kScriptingPrefix + 158)
	DECLARE_PMID(kErrorIDSpace, kEventIsNotCancelableError,					kScriptingPrefix + 159)
	DECLARE_PMID(kErrorIDSpace, kCantReplaceWithDeletedObjectError,			kScriptingPrefix + 160)
	DECLARE_PMID(kErrorIDSpace, kObsoleteMethodParameterError,				kScriptingPrefix + 161)
	//gap
#define kLastUserOrientedScriptError									kScriptingPrefix + 255

//**********************************************************************************************************
// Script Element IDs
//**********************************************************************************************************

//Types
#define							kScriptInfoFirstBaseType				kScriptingPrefix + 0
DECLARE_PMID(kScriptInfoIDSpace, kScriptInfoVoidType,						kScriptingPrefix + 0)
DECLARE_PMID(kScriptInfoIDSpace, kScriptInfoVariableType,					kScriptingPrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kScriptInfoInt16Type,						kScriptingPrefix + 2)
DECLARE_PMID(kScriptInfoIDSpace, kScriptInfoInt32Type,						kScriptingPrefix + 3)
DECLARE_PMID(kScriptInfoIDSpace, kScriptInfoBoolType,						kScriptingPrefix + 4)
DECLARE_PMID(kScriptInfoIDSpace, kScriptInfoStringType,						kScriptingPrefix + 5)
DECLARE_PMID(kScriptInfoIDSpace, kScriptInfoUnitType,						kScriptingPrefix + 6)
DECLARE_PMID(kScriptInfoIDSpace, kScriptInfoRealType,						kScriptingPrefix + 7)
DECLARE_PMID(kScriptInfoIDSpace, kScriptInfoDateType,						kScriptingPrefix + 8)
DECLARE_PMID(kScriptInfoIDSpace, kScriptInfoFileType,						kScriptingPrefix + 9)
DECLARE_PMID(kScriptInfoIDSpace, kScriptInfoRecordType,						kScriptingPrefix + 10)
DECLARE_PMID(kScriptInfoIDSpace, kScriptInfoStreamType,						kScriptingPrefix + 11)
DECLARE_PMID(kScriptInfoIDSpace, kScriptInfoAnyType,						kScriptingPrefix + 12)
DECLARE_PMID(kScriptInfoIDSpace, kScriptInfoFunctionType,					kScriptingPrefix + 13)
DECLARE_PMID(kScriptInfoIDSpace, kScriptInfoInt64Type,						kScriptingPrefix + 14)
DECLARE_PMID(kScriptInfoIDSpace, kScriptInfoStructType,						kScriptingPrefix + 15)
//If you add a new type, you need to handle it in a couple of core places:
//	CScriptManager::AppendBaseTypeAsString
//	ScriptInfo::TypeInfo::IsValidValue
//Also, update any scripting clients that include this type in their DOM.
#define							kScriptInfoLastBaseType					kScriptingPrefix + 15
#define							kScriptInfoAbstractArrayType			kScriptInfoLastBaseType + 1

#ifdef DEBUG
DECLARE_PMID(kScriptInfoIDSpace, kIgnoreTypeChangeToken,					kScriptingPrefix + 30)	//Indicates that the type of a property changed and this is acceptable (otherwise INX will assert during DOM merging)
#endif
DECLARE_PMID(kScriptInfoIDSpace, kContainerObjectScriptElement,				kScriptingPrefix + 31)	//Indicates that the actual type of an event/param/property is the object containing the event/property
DECLARE_PMID(kScriptInfoIDSpace, kContainerParentScriptElement,				kScriptingPrefix + 32)	//Indicates that the actual type of an event/param/property is the parent object(s) of the object containing the event/property
DECLARE_PMID(kScriptInfoIDSpace, kContainerNonSurrogateParentScriptElement,	kScriptingPrefix + 33)	//Indicates that the actual type of an event/param/property is the non-surrogate parent object(s) of the object containing the event/property

//Suites
DECLARE_PMID(kScriptInfoIDSpace, kBasicSuiteScriptElement,					kScriptingPrefix + 40)
DECLARE_PMID(kScriptInfoIDSpace, kPreferencesSuiteScriptElement,			kScriptingPrefix + 41)

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kAnyObjectScriptElement,					kScriptingPrefix + 49)	//Indicates that the type could be any object type
DECLARE_PMID(kScriptInfoIDSpace, kNonIDBasedObjectScriptElement,			kScriptingPrefix + 50)
DECLARE_PMID(kScriptInfoIDSpace, kIDBasedObjectScriptElement,				kScriptingPrefix + 51)
DECLARE_PMID(kScriptInfoIDSpace, kUIDBasedObjectScriptElement,				kScriptingPrefix + 52)
DECLARE_PMID(kScriptInfoIDSpace, kPreferencesObjectScriptElement,			kScriptingPrefix + 53)
DECLARE_PMID(kScriptInfoIDSpace, kScriptPrefsObjectScriptElement,			kScriptingPrefix + 54)
DECLARE_PMID(kScriptInfoIDSpace, kRootDataBaseObjectScriptElement,			kScriptingPrefix + 55)
DECLARE_PMID(kScriptInfoIDSpace, kEventListenerObjectScriptElement,			kScriptingPrefix + 56)
DECLARE_PMID(kScriptInfoIDSpace, kEventObjectScriptElement,					kScriptingPrefix + 57)
DECLARE_PMID(kScriptInfoIDSpace, kIdleEventObjectScriptElement,				kScriptingPrefix + 58)
DECLARE_PMID(kScriptInfoIDSpace, kMutationEventObjectScriptElement,			kScriptingPrefix + 59)
DECLARE_PMID(kScriptInfoIDSpace, kIdleTaskObjectScriptElement,				kScriptingPrefix + 60)

//Metadata
DECLARE_PMID(kScriptInfoIDSpace, kDontAddToPropertiesPropertyMetadataScriptElement,	kScriptingPrefix + 80)
DECLARE_PMID(kScriptInfoIDSpace, kDontAddToBasePropertiesMetadataScriptElement,	kScriptingPrefix + 81)
DECLARE_PMID(kScriptInfoIDSpace, kIgnoreForGetPropertiesMetadataScriptElement,	kScriptingPrefix + 82)
DECLARE_PMID(kScriptInfoIDSpace, kAllowCoreMethodsWithModalDialogMetadataScriptElement,	kScriptingPrefix + 83)
DECLARE_PMID(kScriptInfoIDSpace, kAllowEventListenerMethodsWithModalDialogMetadataScriptElement, kScriptingPrefix + 84)

//Events
DECLARE_PMID(kScriptInfoIDSpace, kOnIdleEventScriptElement,					kScriptingPrefix + 90)
DECLARE_PMID(kScriptInfoIDSpace, kAfterAttributeChangedEventScriptElement,	kScriptingPrefix + 91)

//Methods
DECLARE_PMID(kScriptInfoIDSpace, kItemMethodScriptElement,					kScriptingPrefix + 100)
DECLARE_PMID(kScriptInfoIDSpace, kItemByNameMethodScriptElement,			kScriptingPrefix + 101)
DECLARE_PMID(kScriptInfoIDSpace, kItemByIDMethodScriptElement,				kScriptingPrefix + 102)
DECLARE_PMID(kScriptInfoIDSpace, kItemByRangeMethodScriptElement,			kScriptingPrefix + 103)
//DECLARE_PMID(kScriptInfoIDSpace, kItemWhoseMethodScriptElement,			kScriptingPrefix + 104)
DECLARE_PMID(kScriptInfoIDSpace, kFirstItemMethodScriptElement,				kScriptingPrefix + 105)
DECLARE_PMID(kScriptInfoIDSpace, kLastItemMethodScriptElement,				kScriptingPrefix + 106)
DECLARE_PMID(kScriptInfoIDSpace, kMiddleItemMethodScriptElement,			kScriptingPrefix + 107)
DECLARE_PMID(kScriptInfoIDSpace, kPreviousItemMethodScriptElement,			kScriptingPrefix + 108)
DECLARE_PMID(kScriptInfoIDSpace, kNextItemMethodScriptElement,				kScriptingPrefix + 109)
DECLARE_PMID(kScriptInfoIDSpace, kAnyItemMethodScriptElement,				kScriptingPrefix + 110)
DECLARE_PMID(kScriptInfoIDSpace, kEveryItemMethodScriptElement,				kScriptingPrefix + 111)
//gap
DECLARE_PMID(kScriptInfoIDSpace, kCreateMethodScriptElement,				kScriptingPrefix + 117)
DECLARE_PMID(kScriptInfoIDSpace, kMoveMethodScriptElement,					kScriptingPrefix + 118)
DECLARE_PMID(kScriptInfoIDSpace, kDuplicateMethodScriptElement,				kScriptingPrefix + 119)
DECLARE_PMID(kScriptInfoIDSpace, kCountMethodScriptElement,					kScriptingPrefix + 120)
DECLARE_PMID(kScriptInfoIDSpace, kDeleteMethodScriptElement,				kScriptingPrefix + 121)
DECLARE_PMID(kScriptInfoIDSpace, kInsertLabelMethodScriptElement,			kScriptingPrefix + 122)
DECLARE_PMID(kScriptInfoIDSpace, kExtractLabelMethodScriptElement,			kScriptingPrefix + 123)
DECLARE_PMID(kScriptInfoIDSpace, kCloseMethodScriptElement,					kScriptingPrefix + 124)
DECLARE_PMID(kScriptInfoIDSpace, kPublishTerminologyMethodScriptElement,	kScriptingPrefix + 125)
DECLARE_PMID(kScriptInfoIDSpace, kCreateEventListenerMethodScriptElement,	kScriptingPrefix + 126)
DECLARE_PMID(kScriptInfoIDSpace, kAddEventListenerMethodScriptElement,		kScriptingPrefix + 127)
DECLARE_PMID(kScriptInfoIDSpace, kRemoveEventListenerMethodScriptElement,	kScriptingPrefix + 128)
//DECLARE_PMID(kScriptInfoIDSpace, kDispatchEventMethodScriptElement,		kScriptingPrefix + 129)
DECLARE_PMID(kScriptInfoIDSpace, kStopPropagationMethodScriptElement,		kScriptingPrefix + 130)
DECLARE_PMID(kScriptInfoIDSpace, kPreventDefaultMethodScriptElement,		kScriptingPrefix + 131)

//Functions
DECLARE_PMID(kScriptInfoIDSpace, kHandleEventFunctionScriptElement,			kScriptingPrefix + 150)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kNamePropertyScriptElement,				kScriptingPrefix + 161)
DECLARE_PMID(kScriptInfoIDSpace, kFullNamePropertyScriptElement,			kScriptingPrefix + 162)
DECLARE_PMID(kScriptInfoIDSpace, kPathPropertyScriptElement,				kScriptingPrefix + 163)
DECLARE_PMID(kScriptInfoIDSpace, kDescriptionPropertyScriptElement,			kScriptingPrefix + 164)
DECLARE_PMID(kScriptInfoIDSpace, kVisiblePropertyScriptElement,				kScriptingPrefix + 165)
DECLARE_PMID(kScriptInfoIDSpace, kLockedPropertyScriptElement,				kScriptingPrefix + 166)
DECLARE_PMID(kScriptInfoIDSpace, kFilePropertyScriptElement,				kScriptingPrefix + 167)
DECLARE_PMID(kScriptInfoIDSpace, kBoundsPropertyScriptElement,				kScriptingPrefix + 168)
DECLARE_PMID(kScriptInfoIDSpace, kIndexPropertyScriptElement,				kScriptingPrefix + 169)
DECLARE_PMID(kScriptInfoIDSpace, kParentPropertyScriptElement,				kScriptingPrefix + 170)
DECLARE_PMID(kScriptInfoIDSpace, kLabelPropertyScriptElement,				kScriptingPrefix + 171)
DECLARE_PMID(kScriptInfoIDSpace, kIDPropertyScriptElement,					kScriptingPrefix + 172)
DECLARE_PMID(kScriptInfoIDSpace, kPropertiesPropertyScriptElement,			kScriptingPrefix + 173)
DECLARE_PMID(kScriptInfoIDSpace, kScriptPrefsPropertyScriptElement,			kScriptingPrefix + 174)
DECLARE_PMID(kScriptInfoIDSpace, kScriptingVersionPropertyScriptElement,	kScriptingPrefix + 175)
DECLARE_PMID(kScriptInfoIDSpace, kScriptingLocalePropertyScriptElement,		kScriptingPrefix + 176)
DECLARE_PMID(kScriptInfoIDSpace, kLeftPropertyScriptElement,				kScriptingPrefix + 177)
DECLARE_PMID(kScriptInfoIDSpace, kTopPropertyScriptElement,					kScriptingPrefix + 178)
DECLARE_PMID(kScriptInfoIDSpace, kRightPropertyScriptElement,				kScriptingPrefix + 179)
DECLARE_PMID(kScriptInfoIDSpace, kBottomPropertyScriptElement,				kScriptingPrefix + 180)
DECLARE_PMID(kScriptInfoIDSpace, kWidthPropertyScriptElement,				kScriptingPrefix + 181)
DECLARE_PMID(kScriptInfoIDSpace, kHeightPropertyScriptElement,				kScriptingPrefix + 182)
DECLARE_PMID(kScriptInfoIDSpace, kDatePropertyScriptElement,				kScriptingPrefix + 183)
DECLARE_PMID(kScriptInfoIDSpace, kScriptsListPropertyScriptElement,			kScriptingPrefix + 184)
DECLARE_PMID(kScriptInfoIDSpace, kScriptsFolderPropertyScriptElement,		kScriptingPrefix + 185)
DECLARE_PMID(kScriptInfoIDSpace, kEnableRedrawPropertyScriptElement,		kScriptingPrefix + 186)
DECLARE_PMID(kScriptInfoIDSpace, kEventTypePropertyScriptElement,			kScriptingPrefix + 187)
DECLARE_PMID(kScriptInfoIDSpace, kTargetPropertyScriptElement,				kScriptingPrefix + 188)
DECLARE_PMID(kScriptInfoIDSpace, kCurrentTargetPropertyScriptElement,		kScriptingPrefix + 189)
DECLARE_PMID(kScriptInfoIDSpace, kEventPhasePropertyScriptElement,			kScriptingPrefix + 190)
DECLARE_PMID(kScriptInfoIDSpace, kCapturesPropertyScriptElement,			kScriptingPrefix + 191)
DECLARE_PMID(kScriptInfoIDSpace, kBubblesPropertyScriptElement,				kScriptingPrefix + 192)
DECLARE_PMID(kScriptInfoIDSpace, kCancelablePropertyScriptElement,			kScriptingPrefix + 193)
DECLARE_PMID(kScriptInfoIDSpace, kTimeStampPropertyScriptElement,			kScriptingPrefix + 194)
DECLARE_PMID(kScriptInfoIDSpace, kPropagationStoppedPropertyScriptElement,	kScriptingPrefix + 195)
DECLARE_PMID(kScriptInfoIDSpace, kDefaultPreventedPropertyScriptElement,	kScriptingPrefix + 196)
DECLARE_PMID(kScriptInfoIDSpace, kHandlerPropertyScriptElement,				kScriptingPrefix + 197)
DECLARE_PMID(kScriptInfoIDSpace, kKeyValuePairTypeDefScriptElement,			kScriptingPrefix + 198)
DECLARE_PMID(kScriptInfoIDSpace, kEnabledPropertyScriptElement,				kScriptingPrefix + 199)
DECLARE_PMID(kScriptInfoIDSpace, kPathAsStringPropertyScriptElement,		kScriptingPrefix + 200)
DECLARE_PMID(kScriptInfoIDSpace, kNameFromLabelPropertyScriptElement,		kScriptingPrefix + 201)
DECLARE_PMID(kScriptInfoIDSpace, kMeasurementUnitPropertyScriptElement,		kScriptingPrefix + 202)
DECLARE_PMID(kScriptInfoIDSpace, kAttributeNamePropertyScriptElement,		kScriptingPrefix + 203)
DECLARE_PMID(kScriptInfoIDSpace, kAttributeValuePropertyScriptElement,		kScriptingPrefix + 204)
DECLARE_PMID(kScriptInfoIDSpace, kSleepPropertyScriptElement,				kScriptingPrefix + 205)
DECLARE_PMID(kScriptInfoIDSpace, kTimeAllocatedPropertyScriptElement,		kScriptingPrefix + 206)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kLocationOptionsEnumScriptElement,			kScriptingPrefix + 221)
DECLARE_PMID(kScriptInfoIDSpace, kUIColorsEnumScriptElement,				kScriptingPrefix + 222)
DECLARE_PMID(kScriptInfoIDSpace, kNothingEnumScriptElement,					kScriptingPrefix + 223)
DECLARE_PMID(kScriptInfoIDSpace, kAutoEnumScriptElement,					kScriptingPrefix + 224)
DECLARE_PMID(kScriptInfoIDSpace, kEventPhaseEnumScriptElement,				kScriptingPrefix + 225)

//TypeDefs
DECLARE_PMID(kScriptInfoIDSpace, kInDesignUIColorTypeDefScriptElement,		kScriptingPrefix + 235)
DECLARE_PMID(kScriptInfoIDSpace, kUnitPointTypeDefScriptElement,			kScriptingPrefix + 236)
DECLARE_PMID(kScriptInfoIDSpace, kUnitRecBoundsTypeDefScriptElement,		kScriptingPrefix + 237)

//Scripting Args
DECLARE_PMID(kScriptInfoIDSpace, kScriptArgsObjectScriptElement,			kScriptingPrefix + 245)
DECLARE_PMID(kScriptInfoIDSpace, kGetScriptArgMethodScriptElement,			kScriptingPrefix + 246)
DECLARE_PMID(kScriptInfoIDSpace, kSetScriptArgMethodScriptElement,			kScriptingPrefix + 247)
DECLARE_PMID(kScriptInfoIDSpace, kIsDefinedScriptArgMethodScriptElement,	kScriptingPrefix + 248)
DECLARE_PMID(kScriptInfoIDSpace, kClearScriptArgsMethodScriptElement,		kScriptingPrefix + 249)
DECLARE_PMID(kScriptInfoIDSpace, kSaveScriptArgsMethodScriptElement,		kScriptingPrefix + 250)
DECLARE_PMID(kScriptInfoIDSpace, kRestoreScriptArgsMethodScriptElement,		kScriptingPrefix + 251)
DECLARE_PMID(kScriptInfoIDSpace, kScriptArgsPropertyScriptElement,			kScriptingPrefix + 252)
DECLARE_PMID(kScriptInfoIDSpace, kGetValueScriptArgMethodScriptElement,		kScriptingPrefix + 253)
DECLARE_PMID(kScriptInfoIDSpace, kSetValueScriptArgMethodScriptElement,		kScriptingPrefix + 254)

enum ScriptingScriptIDs
{
	t_IDUIColorType			= 'IDCT',
	t_TransformMatrixType	= 'MTXT',
	t_RectangleBoundsType	= 'RBDT',
	t_PathPointType			= 'PPTT',
	t_PointType				= 'PNTT',
	t_GeoPathType			= 'GPTT',
	t_KeyValuePairType		= 'KVPT',
	t_GeometryType			= 'GEOT',
	t_UnitPointType			= 'UPTT',
	t_UnitRecBoundsType		= 'URBT',
	t_NameValuePairType		= 'NVPT',

	c_NonIDBased			= 'noID',
	c_IDBased				= 'nuID',
	c_UIDBased				= 'unID',
	c_Root					= 'ROOT',
	c_Object				= 'BObj',
	c_Objects				= 'OBJS',
	c_PrefsObject			= 'PObj',
	c_PrefsObjects			= 'Prfs',
	c_Event					= 'evnt',
	c_Events				= 'evts',
	c_EventListener			= 'EvLi',
	c_EventListeners		= 'EvLs',
	c_IdleEvent				= 'IdEv',
	c_MutationEvent			= 'EvMu',
	c_IdleTask				= 'ITsk',
	c_IdleTasks				= 'ITks',

	e_AddEventListener		= 'eAEL',
	e_RemoveEventListener	= 'eREL',
	e_StopPropagation		= 'eStP',
	e_PreventDefault		= 'ePrD',

	e_OnIdle				= 'OnId',
	e_AfterAttributeChanged	= 'AfAC',
	e_BeforeNew				= 'bfNw',
	e_AfterNew				= 'afNw',
	e_BeforeDelete			= 'BfDl',
	e_AfterDelete			= 'AfDl',
	e_BeforeMove			= 'BfMv',
	e_AfterMove				= 'AfMv',

	f_HandleEvent			= 'eHEv',

	p_EventType				= 'pEvT',
	p_Handler				= 'pHnd',
	p_EventData				= 'pEvD',
	p_Target				= 'Xtrg',
	p_CurrentTarget			= 'pCur',
	p_EventPhase			= 'pEvP',
	p_Captures				= 'pCps',
	p_Bubbles				= 'pBus',
	p_Cancelable			= 'pCan',
	p_TimeStamp				= 'pTim',
	p_PropagationStopped	= 'pPSp',
	p_DefaultPrevented		= 'pDPr',
	p_AttributeName			= 'Xatn',
	p_AttributeValue		= 'AtVl',
	p_Sleep					= 'Slep',
	p_TimeAllocated			= 'TmAl',
	p_Status				= 'stts',
	p_Size					= 'dsiz',	//kAEGetDataSize in AERegistry.h
	p_Date					= 'sdte',

	en_EventPhase			= 'enEP',
	en_NotDispatching		= 'enND',
	en_CapturingPhase		= 'enCp',
	en_AtTarget				= 'enAT',
	en_BubblingPhase		= 'enBu',
	en_DoneDispatching		= 'enDD',

	p_UndoMode				= 'pSUM',
	en_UndoMode				= 'eSUM',
	en_UndoScriptRequest	= 'eSrU',
	en_UndoEntireScript		= 'eScU',
	en_AutoUndoScript		= 'eSaU',
	en_FastUndoEntireScript	= 'eSfU',

	p_UserInteraction		= 'UIAc',
	en_UserInteraction		= 'elnt',
	en_NeverInteract		= 'eNvr',
	en_InteractWithSelf		= 'eInS',
	en_InteractWithLocal	= 'eInL',
	en_InteractWithAll		= 'eInA',
	en_InteractWithAlerts	= 'eInB',

	m_HideFromPublishedDOM	= 'HFPD',
	m_SkipVerification		= 'SkpV',
	m_AddNothingEnumToProperties = 'ANEP',
	m_DontAddNothingEnum	= 'DANE',
	m_IgnoreForGetProperties = 'IFGP',
	m_AllowWithModalDialog	= 'AWMD',

	// Scripting prefs
	p_ScriptPrefs			= 'pScr',
	p_ScriptsList			= 'Slst',
	p_ScriptsFolder			= 'SFdr',
	p_CurrentScriptUndoMode	= 'CSUM',
	p_MeasurementUnit		= 'MtUt',

	// Performance metrics
	en_AttachableEventCount	= 'AECt', 
	en_AttachedScriptsCount	= 'ASCt', 
	en_DispatchEventTime	= 'DETm', 
};

//GUIDS
// {CF550CEA-6B35-47b3-9149-5819BF3E7F35}
#define kObjects_CLSID { 0xcf550cea, 0x6b35, 0x47b3, { 0x91, 0x49, 0x58, 0x19, 0xbf, 0x3e, 0x7f, 0x35 } }
// {C6C9874C-08B6-4901-9503-86B283BD28BE}
#define kObject_CLSID { 0xc6c9874c, 0x8b6, 0x4901, { 0x95, 0x3, 0x86, 0xb2, 0x83, 0xbd, 0x28, 0xbe } }
// {5919318D-FF15-43f7-8870-489572876084}
#define kNonIDBasedObject_CLSID { 0x5919318d, 0xff15, 0x43f7, { 0x88, 0x70, 0x48, 0x95, 0x72, 0x87, 0x60, 0x84 } }
// {53658867-DC21-4eac-9BDE-F531A4826880}
#define kIDBasedObject_CLSID { 0x53658867, 0xdc21, 0x4eac, { 0x9b, 0xde, 0xf5, 0x31, 0xa4, 0x82, 0x68, 0x80 } }
// {D8035C7E-E73C-4615-B277-5CBF27E5C125}
#define kUIDBasedObject_CLSID { 0xd8035c7e, 0xe73c, 0x4615, { 0xb2, 0x77, 0x5c, 0xbf, 0x27, 0xe5, 0xc1, 0x25 } }
// {88EB691E-8FE2-4f37-BDDF-05441748B180}
#define kRootObject_CLSID { 0x88eb691e, 0x8fe2, 0x4f37, { 0xbd, 0xdf, 0x5, 0x44, 0x17, 0x48, 0xb1, 0x80 } }
// {4964C0C5-3DDA-425b-B943-3BCA8469E6B9}
#define kPrefsObject_CLSID { 0x4964c0c5, 0x3dda, 0x425b, { 0xb9, 0x43, 0x3b, 0xca, 0x84, 0x69, 0xe6, 0xb9 } }
// {D6F21922-A644-46cf-8B21-B7112ACDD69B}
#define kPrefsObjects_CLSID { 0xd6f21922, 0xa644, 0x46cf, { 0x8b, 0x21, 0xb7, 0x11, 0x2a, 0xcd, 0xd6, 0x9b } }
// {3C5D982B-F5F2-40d7-AC27-991D1A532E04}
#define kScriptPrefs_CLSID { 0x3c5d982b, 0xf5f2, 0x40d7, { 0xac, 0x27, 0x99, 0x1d, 0x1a, 0x53, 0x2e, 0x4 } }
// {A02E541B-40B3-44a9-921C-9DEC0898EAB2}
#define kScriptArgs_CLSID { 0xa02e541b, 0x40b3, 0x44a9, { 0x92, 0x1c, 0x9d, 0xec, 0x8, 0x98, 0xea, 0xb2 } }
// {83E3CEE7-839D-460b-B014-978C020C95CF}
#define kEventListener_CLSID { 0x83e3cee7, 0x839d, 0x460b, { 0xb0, 0x14, 0x97, 0x8c, 0x2, 0xc, 0x95, 0xcf } }
// {66503A71-3620-4c50-AFD2-16743353D5A5}
#define kEventListeners_CLSID { 0x66503a71, 0x3620, 0x4c50, { 0xaf, 0xd2, 0x16, 0x74, 0x33, 0x53, 0xd5, 0xa5 } }
// {CD89E052-7CED-474a-B183-CC353B4BFE3A}
#define kEvent_CLSID { 0xcd89e052, 0x7ced, 0x474a, { 0xb1, 0x83, 0xcc, 0x35, 0x3b, 0x4b, 0xfe, 0x3a } }
// {7E528261-8EA4-42d0-9955-8CED430317C9}
#define kEvents_CLSID { 0x7e528261, 0x8ea4, 0x42d0, { 0x99, 0x55, 0x8c, 0xed, 0x43, 0x3, 0x17, 0xc9 } }
// {DA1486FD-37B4-4642-A751-023322D17EC2}
#define kIdleEvent_CLSID { 0xda1486fd, 0x37b4, 0x4642, { 0xa7, 0x51, 0x2, 0x33, 0x22, 0xd1, 0x7e, 0xc2 } }
// {507774AA-EE26-4d66-B035-B15745A7E12A}
#define kMutationEvent_CLSID { 0x507774aa, 0xee26, 0x4d66, { 0xb0, 0x35, 0xb1, 0x57, 0x45, 0xa7, 0xe1, 0x2a } }
// {F66681FE-7936-42c2-8928-ECF5BC17DC04}
#define kIdleTask_CLSID { 0xf66681fe, 0x7936, 0x42c2, { 0x89, 0x28, 0xec, 0xf5, 0xbc, 0x17, 0xdc, 0x4 } }
// {1E048FE5-5927-4698-A686-5E13F68F0250}
#define kIdleTasks_CLSID { 0x1e048fe5, 0x5927, 0x4698, { 0xa6, 0x86, 0x5e, 0x13, 0xf6, 0x8f, 0x2, 0x50 } }

#endif
