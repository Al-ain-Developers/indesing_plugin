//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/workgroup/workgroupid.h $
//  
//  Owner: Jack Kirstein
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

#ifndef __WORKGROUPID__
#define __WORKGROUPID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kVersionCueResourceScheme "adobevc"

#define kWorkgroupPrefix RezLong(0x15A00)

// <Start IDC>
// PluginID
#define kWorkgroupPluginName   "Workgroup"

DECLARE_PMID(kPlugInIDSpace, kWorkgroupPluginID, kWorkgroupPrefix + 1)

// <Class ID>
//========================================================================================
// ----- ClassIDs -----
//========================================================================================
//DECLARE_PMID(kClassIDSpace, kBossID, kPrefix + x)
DECLARE_PMID(kClassIDSpace, kVersionCueAMSPBoss,					kWorkgroupPrefix + 0x01)
DECLARE_PMID(kClassIDSpace, kVCInCopyAMSPBoss,						kWorkgroupPrefix + 0x02)
DECLARE_PMID(kClassIDSpace, kInCopyAMSPBoss,						kWorkgroupPrefix + 0x03)
// Available
DECLARE_PMID(kClassIDSpace, kWGDocumentScriptProviderBoss,			kWorkgroupPrefix + 0x05)
DECLARE_PMID(kClassIDSpace, kWGLinkScriptProviderBoss,				kWorkgroupPrefix + 0x06)
DECLARE_PMID(kClassIDSpace, kWGErrorStringServiceBoss,				kWorkgroupPrefix + 0x07)
DECLARE_PMID(kClassIDSpace, kWGOpenDocResponderBoss,				kWorkgroupPrefix + 0x08)
DECLARE_PMID(kClassIDSpace, kStandardAMSPBoss,						kWorkgroupPrefix + 0x09)
DECLARE_PMID(kClassIDSpace, kAMSPBoss,								kWorkgroupPrefix + 0x0A)
DECLARE_PMID(kClassIDSpace, kWGCloseDocResponderBoss,				kWorkgroupPrefix + 0x0B)
DECLARE_PMID(kClassIDSpace, kInitializeLocalAssetServiceBoss,		kWorkgroupPrefix + 0x0C)
DECLARE_PMID(kClassIDSpace, kSetAssetAttributesCmdBoss,				kWorkgroupPrefix + 0x0D)
DECLARE_PMID(kClassIDSpace, kManagedStatusBoss,						kWorkgroupPrefix + 0x0E)
// Available
DECLARE_PMID(kClassIDSpace, kWGAfterSaveDocResponderBoss,			kWorkgroupPrefix + 0x12)
DECLARE_PMID(kClassIDSpace, kWGAfterSaveAsDocResponderBoss,			kWorkgroupPrefix + 0x13)
DECLARE_PMID(kClassIDSpace, kStdGetUniqueAssetLocationServiceBoss,	kWorkgroupPrefix + 0x14)
DECLARE_PMID(kClassIDSpace, kWGUpdateLinkResourceStateCmdBoss,		kWorkgroupPrefix + 0x15)
DECLARE_PMID(kClassIDSpace, kWGNewDocResponderBoss,					kWorkgroupPrefix + 0x16)
DECLARE_PMID(kClassIDSpace, kLinkInfoWorkgroupStatusProviderBoss,	kWorkgroupPrefix + 0x17)
DECLARE_PMID(kClassIDSpace, kLinkInfoWorkgroupUserProviderBoss,		kWorkgroupPrefix + 0x18)
DECLARE_PMID(kClassIDSpace, kWorkgroupConversionBoss,				kWorkgroupPrefix + 0x19)
DECLARE_PMID(kClassIDSpace, kWGExportDocResponderBoss,				kWorkgroupPrefix + 0x1A)

// <Interface ID>
//========================================================================================
// ----- Interface IDs -----
//========================================================================================
//DECLARE_PMID(kInterfaceIDSpace, IID_INTERFACE, kPrefix + x) 
DECLARE_PMID(kInterfaceIDSpace,	IID_IAMSERVICEPROVIDER,				kWorkgroupPrefix + 0x01)
DECLARE_PMID(kInterfaceIDSpace,	IID_IMANAGEDSTATUS,					kWorkgroupPrefix + 0x02)
DECLARE_PMID(kInterfaceIDSpace,	IID_IAMSPMANAGER,					kWorkgroupPrefix + 0x03)
DECLARE_PMID(kInterfaceIDSpace,	IID_IAMUISERVICEPROVIDER,			kWorkgroupPrefix + 0x04)
DECLARE_PMID(kInterfaceIDSpace,	IID_IASSETMONITOR,					kWorkgroupPrefix + 0x05)
DECLARE_PMID(kInterfaceIDSpace,	IID_IMANAGEABLEASSET,				kWorkgroupPrefix + 0x06)
DECLARE_PMID(kInterfaceIDSpace,	IID_IAMSERVICE,						kWorkgroupPrefix + 0x07)
DECLARE_PMID(kInterfaceIDSpace,	IID_IAMSERVICEDATA,					kWorkgroupPrefix + 0x08)
DECLARE_PMID(kInterfaceIDSpace,	IID_IAMSYSTEMPROVIDER,				kWorkgroupPrefix + 0x09)
DECLARE_PMID(kInterfaceIDSpace,	IID_ISAVEASSETCONTENT,				kWorkgroupPrefix + 0x0A)
DECLARE_PMID(kInterfaceIDSpace,	IID_IAMAUTHENTICATIONUI,			kWorkgroupPrefix + 0x0B)
DECLARE_PMID(kInterfaceIDSpace,	IID_IAMSTATUSLISTENER,				kWorkgroupPrefix + 0x0C)
DECLARE_PMID(kInterfaceIDSpace,	IID_IASSETSTATEMACHINE,				kWorkgroupPrefix + 0x0D)
DECLARE_PMID(kInterfaceIDSpace,	IID_IWORKGROUPFACADE,				kWorkgroupPrefix + 0x0F)
DECLARE_PMID(kInterfaceIDSpace,	IID_IAMUISERVICE,					kWorkgroupPrefix + 0x10)
DECLARE_PMID(kInterfaceIDSpace,	IID_IAMLOCKABLE,					kWorkgroupPrefix + 0x11)
DECLARE_PMID(kInterfaceIDSpace,	IID_IWORKGROUPUIFACADE,				kWorkgroupPrefix + 0x12)
DECLARE_PMID(kInterfaceIDSpace,	IID_IMANAGEDLINKHELPER,				kWorkgroupPrefix + 0x13)
DECLARE_PMID(kInterfaceIDSpace,	IID_IAMUIENABLEMENTRULES,			kWorkgroupPrefix + 0x14)
// gap
DECLARE_PMID(kInterfaceIDSpace,	IID_IALLOWCANCEL,					kWorkgroupPrefix + 0x18) // bool data
DECLARE_PMID(kInterfaceIDSpace,	IID_IWORKGROUPUTILS,				kWorkgroupPrefix + 0x19)
DECLARE_PMID(kInterfaceIDSpace,	IID_IWORKGROUPSTORYFACADE,			kWorkgroupPrefix + 0x1A)
DECLARE_PMID(kInterfaceIDSpace,	IID_IWORKGROUPEXPORTUTILS,			kWorkgroupPrefix + 0x1B)
DECLARE_PMID(kInterfaceIDSpace,	IID_IWORKGROUPICUTILS,				kWorkgroupPrefix + 0x1C)
DECLARE_PMID(kInterfaceIDSpace,	IID_ISETASSETATTRIBUTESCMDDATA,		kWorkgroupPrefix + 0x1D)
DECLARE_PMID(kInterfaceIDSpace, IID_LINKWGSTATUSCHANGE,				kWorkgroupPrefix + 0x1E)


// <Implementation ID>
//========================================================================================
// ----- Implementation IDs -----
//========================================================================================
//DECLARE_PMID(kImplementationIDSpace, kImpl, kPrefix + x)
DECLARE_PMID(kImplementationIDSpace, kAMSPServiceProviderImpl,          kWorkgroupPrefix + 0x01)
DECLARE_PMID(kImplementationIDSpace, kAMSPManagerImpl,                  kWorkgroupPrefix + 0x02)
DECLARE_PMID(kImplementationIDSpace, kVCLinkAlternateResourceServiceImpl,kWorkgroupPrefix + 0x03)
// gap
DECLARE_PMID(kImplementationIDSpace, kWGDocumentScriptProviderImpl,    	kWorkgroupPrefix + 0x05)
DECLARE_PMID(kImplementationIDSpace, kWGLinkScriptProviderImpl,  	    kWorkgroupPrefix + 0x06)
DECLARE_PMID(kImplementationIDSpace, kWGErrorStringServiceImpl,			kWorkgroupPrefix + 0x07)
DECLARE_PMID(kImplementationIDSpace, kWGOpenDocResponderImpl,           kWorkgroupPrefix + 0x08)
DECLARE_PMID(kImplementationIDSpace, kManageableAssetImpl,				kWorkgroupPrefix + 0x09)
DECLARE_PMID(kImplementationIDSpace, kAMServiceDataImpl,				kWorkgroupPrefix + 0x0A)
DECLARE_PMID(kImplementationIDSpace, kStandardAMServiceProviderImpl,    kWorkgroupPrefix + 0x0B)
DECLARE_PMID(kImplementationIDSpace, kStandardAMSPImpl,					kWorkgroupPrefix + 0x0C)
DECLARE_PMID(kImplementationIDSpace, kStdGetUniqueAssetLocationServiceImpl,	kWorkgroupPrefix + 0x0D)
DECLARE_PMID(kImplementationIDSpace, kWorkgroupUtilsImpl,				kWorkgroupPrefix + 0x0E)
// Available
DECLARE_PMID(kImplementationIDSpace, kManagedStatusImpl,				kWorkgroupPrefix + 0x11)
DECLARE_PMID(kImplementationIDSpace, kWGCloseDocResponderImpl,			kWorkgroupPrefix + 0x12)
// Available
DECLARE_PMID(kImplementationIDSpace, kWorkgroupFacadeImpl,				kWorkgroupPrefix + 0x14)
DECLARE_PMID(kImplementationIDSpace, kVersionCueUISPImpl,				kWorkgroupPrefix + 0x15)
// Available
DECLARE_PMID(kImplementationIDSpace, kWorkgroupUIFacadeImpl,			kWorkgroupPrefix + 0x18)
// Available
DECLARE_PMID(kImplementationIDSpace, kSaveDocumentContentImpl,			kWorkgroupPrefix + 0x1C)
DECLARE_PMID(kImplementationIDSpace, kWGAfterSaveDocResponderImpl,		kWorkgroupPrefix + 0x1D)
DECLARE_PMID(kImplementationIDSpace, kWGAfterSaveAsDocResponderImpl,	kWorkgroupPrefix + 0x1E)
DECLARE_PMID(kImplementationIDSpace, kManagedDocStatusImpl,				kWorkgroupPrefix + 0x1F)
DECLARE_PMID(kImplementationIDSpace, kWorkgroupMgrImpl,                 kWorkgroupPrefix + 0x20)
// Available
DECLARE_PMID(kImplementationIDSpace, kWGUpdateLinkResourceStateCmdImpl,	kWorkgroupPrefix + 0x22)
DECLARE_PMID(kImplementationIDSpace, kWorkgroupStoryFacadeImpl,			kWorkgroupPrefix + 0x23)
DECLARE_PMID(kImplementationIDSpace, kWorkgroupExportUtilsImpl,			kWorkgroupPrefix + 0x24)
DECLARE_PMID(kImplementationIDSpace, kWorkgroupICUtilsImpl,				kWorkgroupPrefix + 0x25)
DECLARE_PMID(kImplementationIDSpace, kSetAssetAttributesCmdImpl,		kWorkgroupPrefix + 0x26)
DECLARE_PMID(kImplementationIDSpace, kSetAssetAttributesCmdDataImpl,	kWorkgroupPrefix + 0x27)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoWorkgroupStatusProviderImpl, kWorkgroupPrefix + 0x28)
DECLARE_PMID(kImplementationIDSpace, kWGLinkInfoStatusObserverImpl,		kWorkgroupPrefix + 0x29)
DECLARE_PMID(kImplementationIDSpace, kWGLinkInfoStatusListenerImpl,		kWorkgroupPrefix + 0x2A)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoWorkgroupUserProviderImpl, kWorkgroupPrefix + 0x2B)
DECLARE_PMID(kImplementationIDSpace, kWGExportDocResponderImpl,			kWorkgroupPrefix + 0x2C)
DECLARE_PMID(kImplementationIDSpace, kWGExportDocSignalServiceProviderImpl,			kWorkgroupPrefix + 0x2D)

// <Service ID>
//========================================================================================
// ----- Service IDs -----
//========================================================================================
// DECLARE_PMID(kServiceIDSpace, kServiceID, kPrefix + x)
DECLARE_PMID(kServiceIDSpace,        kAMSPService,						kWorkgroupPrefix + 0x01)
DECLARE_PMID(kServiceIDSpace,		 kVCLinkAlternateResourceService,	kWorkgroupPrefix + 0x02) 

//========================================================================================
// ----- InvalHandler IDs -----
//========================================================================================
DECLARE_PMID(kInvalHandlerIDSpace, kWGLinkInvalHandlerID,			kWorkgroupPrefix + 1 )
DECLARE_PMID(kInvalHandlerIDSpace, kWGLockStateInvalHandlerID,		kWorkgroupPrefix + 2 )
DECLARE_PMID(kInvalHandlerIDSpace, kWGCheckoutStateInvalHandlerID,	kWorkgroupPrefix + 3 )
DECLARE_PMID(kInvalHandlerIDSpace, kWGLinkResourceInvalHandlerID,	kWorkgroupPrefix + 4 )

//========================================================================================
// ----- ASyncUI IDs -----
//========================================================================================
//DECLARE_PMID(kAsyncUIIDSpace, kQuestionID, kPrefix + x)
DECLARE_PMID(kAsyncUIIDSpace, kCheckoutReplicaClobberModified,  kWorkgroupPrefix + 0x01)
DECLARE_PMID(kAsyncUIIDSpace, kRevertReplicaClobberModified,    kWorkgroupPrefix + 0x02)
DECLARE_PMID(kAsyncUIIDSpace, kMakeReplicaEditableOffline,      kWorkgroupPrefix + 0x03)
DECLARE_PMID(kAsyncUIIDSpace, kWarnOffline,                     kWorkgroupPrefix + 0x04)
DECLARE_PMID(kAsyncUIIDSpace, kWarnRemoteEdit,                  kWorkgroupPrefix + 0x05)
DECLARE_PMID(kAsyncUIIDSpace, kGenericSucceeded,                kWorkgroupPrefix + 0x06)
DECLARE_PMID(kAsyncUIIDSpace, kGenericFailed,                   kWorkgroupPrefix + 0x07)
DECLARE_PMID(kAsyncUIIDSpace, kWantClobber,                    	kWorkgroupPrefix + 0x08)
DECLARE_PMID(kAsyncUIIDSpace, kWantOverride,                   	kWorkgroupPrefix + 0x09)
DECLARE_PMID(kAsyncUIIDSpace, kAskSaveVersion,                  kWorkgroupPrefix + 0x0a)
DECLARE_PMID(kAsyncUIIDSpace, kAskSaveVersionFinal,             kWorkgroupPrefix + 0x0b)
DECLARE_PMID(kAsyncUIIDSpace, kRevertToVersion,                 kWorkgroupPrefix + 0x0c)
//gap
DECLARE_PMID(kAsyncUIIDSpace, kInUseAlert,  					kWorkgroupPrefix + 0x11)
DECLARE_PMID(kAsyncUIIDSpace, kEditAlert,  						kWorkgroupPrefix + 0x12)
DECLARE_PMID(kAsyncUIIDSpace, kConflictAlert,  					kWorkgroupPrefix + 0x13)
DECLARE_PMID(kAsyncUIIDSpace, kNewVersionReplacingCurrentAlert, kWorkgroupPrefix + 0x14)
DECLARE_PMID(kAsyncUIIDSpace, kOverrideFailureAlert,  			kWorkgroupPrefix + 0x15)
DECLARE_PMID(kAsyncUIIDSpace, kSaveAlert,  						kWorkgroupPrefix + 0x16)
DECLARE_PMID(kAsyncUIIDSpace, kSaveVersionAlert,  				kWorkgroupPrefix + 0x17)
DECLARE_PMID(kAsyncUIIDSpace, kOutOfDateAlert,  				kWorkgroupPrefix + 0x18)
DECLARE_PMID(kAsyncUIIDSpace, kServerUpdateAlert,  				kWorkgroupPrefix + 0x19)
DECLARE_PMID(kAsyncUIIDSpace, kRevertAlert,  					kWorkgroupPrefix + 0x1a)
DECLARE_PMID(kAsyncUIIDSpace, kServerDisconnectAlert,  			kWorkgroupPrefix + 0x1b)
DECLARE_PMID(kAsyncUIIDSpace, kDisconnectInMiddleAlert,  		kWorkgroupPrefix + 0x1c)

// <Error ID>
//========================================================================================
// ----- ErrorIDs -----
//========================================================================================
// ARM related errors: upto 0x4F
DECLARE_PMID(kErrorIDSpace, kVCCancelledError,					kWorkgroupPrefix + 0x01)
DECLARE_PMID(kErrorIDSpace, kVCUnauthorizedError,				kWorkgroupPrefix + 0x02)
DECLARE_PMID(kErrorIDSpace, kVCNoSuchResourceError,				kWorkgroupPrefix + 0x03)
DECLARE_PMID(kErrorIDSpace, kVCNoContentError,					kWorkgroupPrefix + 0x04)
DECLARE_PMID(kErrorIDSpace, kVCPermissionDeniedError,			kWorkgroupPrefix + 0x05)
DECLARE_PMID(kErrorIDSpace, kVCLockedElsewhereError,			kWorkgroupPrefix + 0x06)
DECLARE_PMID(kErrorIDSpace, kVCLockedByOtherError,				kWorkgroupPrefix + 0x07)
DECLARE_PMID(kErrorIDSpace, kVCLockedExclusivelyError,			kWorkgroupPrefix + 0x08)
DECLARE_PMID(kErrorIDSpace, kVCLockedSharedError,				kWorkgroupPrefix + 0x09)
DECLARE_PMID(kErrorIDSpace, kVCLockRevokedError,				kWorkgroupPrefix + 0x0A)
DECLARE_PMID(kErrorIDSpace, kVCNoSuchReplicaError,				kWorkgroupPrefix + 0x0B)
DECLARE_PMID(kErrorIDSpace, kVCWouldClobberLockedError,			kWorkgroupPrefix + 0x0C)
DECLARE_PMID(kErrorIDSpace, kVCWouldClobberModifiedError,		kWorkgroupPrefix + 0x0D)
DECLARE_PMID(kErrorIDSpace, kVCWouldClobberCurrentError,		kWorkgroupPrefix + 0x0E)
DECLARE_PMID(kErrorIDSpace, kVCNoSuchParentError,				kWorkgroupPrefix + 0x0F)
DECLARE_PMID(kErrorIDSpace, kVCNoMountPointError,				kWorkgroupPrefix + 0x10)
DECLARE_PMID(kErrorIDSpace, kVCCantMountParentError,			kWorkgroupPrefix + 0x11)
DECLARE_PMID(kErrorIDSpace, kVCCantMountChildError,				kWorkgroupPrefix + 0x12)
DECLARE_PMID(kErrorIDSpace, kVCMountPointsDifferError,			kWorkgroupPrefix + 0x13)
DECLARE_PMID(kErrorIDSpace, kVCNotInARMError,					kWorkgroupPrefix + 0x14)
DECLARE_PMID(kErrorIDSpace, kVCCollectionAlreadyExistsError,	kWorkgroupPrefix + 0x15)
DECLARE_PMID(kErrorIDSpace, kVCNonCollectionAlreadyExistsError,	kWorkgroupPrefix + 0x16)
DECLARE_PMID(kErrorIDSpace, kVCCantCaptureUnlessCurrentError,	kWorkgroupPrefix + 0x17)
DECLARE_PMID(kErrorIDSpace, kVCNetworkFailureError,				kWorkgroupPrefix + 0x18)
// Gap 0x19-0x4E
DECLARE_PMID(kErrorIDSpace, kVCUnexpectedError,					kWorkgroupPrefix + 0x4F)

// Other errors 0x50 - 0xFF
DECLARE_PMID(kErrorIDSpace, kVCNotEnabledError,					kWorkgroupPrefix + 0x50)
DECLARE_PMID(kErrorIDSpace, kVCFileNotManagedError,				kWorkgroupPrefix + 0x51)
DECLARE_PMID(kErrorIDSpace, kVCLinkNotManagedError,				kWorkgroupPrefix + 0x52)
DECLARE_PMID(kErrorIDSpace, kVCLinkEmbeddedError,				kWorkgroupPrefix + 0x53)

// <Script Info ID>
//========================================================================================
// ----- ScriptInfoIDs -----
//========================================================================================

// Enums (range 0x01 - 0x32)
DECLARE_PMID(kScriptInfoIDSpace, kVersionStateEnumScriptElement,	kWorkgroupPrefix + 0x01)
DECLARE_PMID(kScriptInfoIDSpace, kEditingStateEnumScriptElement,	kWorkgroupPrefix + 0x02)
DECLARE_PMID(kScriptInfoIDSpace, kSyncStatusEnumScriptElement,		kWorkgroupPrefix + 0x03)
DECLARE_PMID(kScriptInfoIDSpace, kSyncConflictResEnumScriptElement,	kWorkgroupPrefix + 0x04)

// Properties (range 0x33 - 0x64)
DECLARE_PMID(kScriptInfoIDSpace, kVersionStatePropertyScriptElement,	kWorkgroupPrefix + 0x33)
DECLARE_PMID(kScriptInfoIDSpace, kEditingStatePropertyScriptElement,	kWorkgroupPrefix + 0x34)

// Events (range 0x65 - 0x8F)
DECLARE_PMID(kScriptInfoIDSpace, kSaveAVersionMethodScriptElement,		kWorkgroupPrefix + 0x65)
DECLARE_PMID(kScriptInfoIDSpace, kRevertToProjectDocumentMethodScriptElement,kWorkgroupPrefix + 0x66)
DECLARE_PMID(kScriptInfoIDSpace, kSyncWithVersionCueMethodScriptElement,	kWorkgroupPrefix + 0x67)
DECLARE_PMID(kScriptInfoIDSpace, kCheckInVersionCueMethodScriptElement,	kWorkgroupPrefix + 0x68)
#endif
