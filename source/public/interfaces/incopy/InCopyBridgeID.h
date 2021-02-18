//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/InCopyBridgeID.h $
//  
//  Owner: Bernd Paradies
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
//  Contains IDs used by the InCopyBridge
//  
//========================================================================================

#ifndef __InCopyBridge__
#define __InCopyBridge__

#include "CrossPlatformTypes.h"							

#include "IDFactory.h"

// double check with AdobePrefix.h
#define kICBridgePrefix			RezLong(0x18E00)  

//----------------------------------------------------------------------------------------
// Plug-in identifier
//----------------------------------------------------------------------------------------

#define kICBridgePluginName 	"InCopy Bridge"
DECLARE_PMID(kPlugInIDSpace, kICBridgePluginID, kICBridgePrefix + 1)

//----------------------------------------------------------------------------------------
// Class identifiers
//----------------------------------------------------------------------------------------

// Available
DECLARE_PMID(kClassIDSpace, kICBridgeScriptProviderBoss,			kICBridgePrefix + 2)
// Gap
DECLARE_PMID(kClassIDSpace, kICBridgeAddLinkResponderBoss,			kICBridgePrefix + 9)
DECLARE_PMID(kClassIDSpace, kICBridgeAddLinksResponderBoss,			kICBridgePrefix + 10)
DECLARE_PMID(kClassIDSpace, kICBridgeRemoveLinksResponderBoss,		kICBridgePrefix + 11)
DECLARE_PMID(kClassIDSpace, kICBridgeAfterOpenDocResponderBoss,		kICBridgePrefix + 12)
DECLARE_PMID(kClassIDSpace, kICBridgeAfterNewDocResponderBoss,		kICBridgePrefix + 13)
DECLARE_PMID(kClassIDSpace, kICBridgeAfterRevertDocResponderBoss,	kICBridgePrefix + 14)
DECLARE_PMID(kClassIDSpace, kICBridgeDocChangesResponderBoss,		kICBridgePrefix + 15)
DECLARE_PMID(kClassIDSpace, kICBridgeAppChangesResponderBoss,		kICBridgePrefix + 16)
DECLARE_PMID(kClassIDSpace, kICBridgeSetUserNameResponderBoss,		kICBridgePrefix + 17)
DECLARE_PMID(kClassIDSpace, kICStoryStateMachineBoss,				kICBridgePrefix + 18)
//gap
DECLARE_PMID(kClassIDSpace, kICBridgeBeforeCloseDocResponderBoss,	kICBridgePrefix + 23)
//DECLARE_PMID(kClassIDSpace, available,					kICBridgePrefix + 24)
DECLARE_PMID(kClassIDSpace, kICBridgeAfterSaveDocResponderBoss,		kICBridgePrefix + 25)
DECLARE_PMID(kClassIDSpace, kICBridgeAfterSaveAsDocResponderBoss,	kICBridgePrefix + 26)
DECLARE_PMID(kClassIDSpace, kICBridgeAfterSaveACopyResponderBoss,	kICBridgePrefix + 27)
//DECLARE_PMID(kClassIDSpace, available,			kICBridgePrefix + 28)
DECLARE_PMID(kClassIDSpace, kICBridgeResponderBoss,					kICBridgePrefix + 29)
DECLARE_PMID(kClassIDSpace, kICBridgeAttachDataLinkResponderBoss,	kICBridgePrefix + 30)
//DECLARE_PMID(kClassIDSpace, available,			kICBridgePrefix + 31)
DECLARE_PMID(kClassIDSpace, kICBridgeBeforeSaveAsDocResponderBoss,	kICBridgePrefix + 32)
DECLARE_PMID(kClassIDSpace,	kICManagedStoryStatusBoss,				kICBridgePrefix + 33)
DECLARE_PMID(kClassIDSpace,	kVCICEnsureLatestStoryServiceBoss,		kICBridgePrefix + 34)
DECLARE_PMID(kClassIDSpace,	kICCheckOutServiceBoss,					kICBridgePrefix + 35)
DECLARE_PMID(kClassIDSpace,	kICCancelCheckOutServiceBoss,			kICBridgePrefix + 36)
DECLARE_PMID(kClassIDSpace,	kVCICAfterCancelCheckOutServiceBoss,	kICBridgePrefix + 37)
DECLARE_PMID(kClassIDSpace,	kVCICCheckInServiceBoss,				kICBridgePrefix + 38)
DECLARE_PMID(kClassIDSpace,	kVCInitializeVersionedStoryServiceBoss,	kICBridgePrefix + 39)
DECLARE_PMID(kClassIDSpace,	kICCheckInServiceBoss,					kICBridgePrefix + 40)
DECLARE_PMID(kClassIDSpace,	kICInitializeStoryServiceBoss,			kICBridgePrefix + 41)
DECLARE_PMID(kClassIDSpace,	kVCManagedStoryStatusBoss,				kICBridgePrefix + 42)
DECLARE_PMID(kClassIDSpace,	kVCVersionedStoryStateMachineBoss,		kICBridgePrefix + 43)
DECLARE_PMID(kClassIDSpace,	kVCICBeforeCheckOutServiceBoss,			kICBridgePrefix + 44)
DECLARE_PMID(kClassIDSpace,	kVCICAfterCheckInServiceBoss,			kICBridgePrefix + 45)
DECLARE_PMID(kClassIDSpace,	kVCLocalStoryStateMachineBoss,			kICBridgePrefix + 46)
DECLARE_PMID(kClassIDSpace,	kVCInitializeLocalStoryServiceBoss,		kICBridgePrefix + 47)
DECLARE_PMID(kClassIDSpace,	kVCICCheckOutServiceBoss,				kICBridgePrefix + 48)
//DECLARE_PMID(kClassIDSpace,	available,							kICBridgePrefix + 49)
//DECLARE_PMID(kClassIDSpace,	available,							kICBridgePrefix + 50)
DECLARE_PMID(kClassIDSpace,	kLiveEditBaseCmdBoss,					kICBridgePrefix + 51)
DECLARE_PMID(kClassIDSpace,	kLiveEditCheckOutStoriesCmdBoss,		kICBridgePrefix + 52)
//DECLARE_PMID(kClassIDSpace,	available,							kICBridgePrefix + 53)
DECLARE_PMID(kClassIDSpace,	kLiveEditCheckInStoriesCmdBoss,			kICBridgePrefix + 54)
DECLARE_PMID(kClassIDSpace,	kLiveEditCancelCheckOutStoriesCmdBoss,	kICBridgePrefix + 55)
DECLARE_PMID(kClassIDSpace,	kLiveEditUpdateStoryLinksCmdBoss,		kICBridgePrefix + 56)
DECLARE_PMID(kClassIDSpace,	kLiveEditSaveStoriesCmdBoss,			kICBridgePrefix + 57)
DECLARE_PMID(kClassIDSpace,	kLiveEditRelockStoriesCmdBoss,			kICBridgePrefix + 58)

//----------------------------------------------------------------------------------------
// Interface identifiers
//----------------------------------------------------------------------------------------

DECLARE_PMID(kInterfaceIDSpace,	IID_IINCOPYBRIDGEUTILS,				kICBridgePrefix + 1)
DECLARE_PMID(kInterfaceIDSpace,	IID_ILIVEEDITSELECTIONSUITE,		kICBridgePrefix + 2)
//DECLARE_PMID(kInterfaceIDSpace,	available,						kICBridgePrefix + 3)
//DECLARE_PMID(kInterfaceIDSpace,	available,						kICBridgePrefix + 4)
DECLARE_PMID(kInterfaceIDSpace,	IID_ISTORYNEEDSRELINK,				kICBridgePrefix + 5)
DECLARE_PMID(kInterfaceIDSpace,	IID_IOPENEDFILEDATE,				kICBridgePrefix + 6)
//DECLARE_PMID(kInterfaceIDSpace,	available,						kICBridgePrefix + 7)
//DECLARE_PMID(kInterfaceIDSpace,	available,						kICBridgePrefix + 8)
//DECLARE_PMID(kInterfaceIDSpace,	available,						kICBridgePrefix + 9)
//DECLARE_PMID(kInterfaceIDSpace,	available,						kICBridgePrefix + 10)
DECLARE_PMID(kInterfaceIDSpace,	IID_IINCOPYVERSIONCOMMENT,			kICBridgePrefix + 11)
DECLARE_PMID(kInterfaceIDSpace,	IID_ILIVEEDITFACADE,				kICBridgePrefix + 12)
DECLARE_PMID(kInterfaceIDSpace,	IID_ILIVEEDITIMPORTOBSERVER,		kICBridgePrefix + 13)
DECLARE_PMID(kInterfaceIDSpace,	IID_IPREVIOUSLOCKSTATEFORTHREAD,	kICBridgePrefix + 14)//DEPRECATED
//DECLARE_PMID(kInterfaceIDSpace,	available,						kICBridgePrefix + 15)
//DECLARE_PMID(kInterfaceIDSpace,	available,						kICBridgePrefix + 16)
//DECLARE_PMID(kInterfaceIDSpace,	available,						kICBridgePrefix + 17)
DECLARE_PMID(kInterfaceIDSpace,	IID_ILIVEEDITCMDDATA,				kICBridgePrefix + 18)
//DECLARE_PMID(kInterfaceIDSpace,	available,						kICBridgePrefix + 19)
DECLARE_PMID(kInterfaceIDSpace,	IID_IICWORKGROUPUIUTILS,			kICBridgePrefix + 20)

//----------------------------------------------------------------------------------------
// Implementation identifiers
//----------------------------------------------------------------------------------------

//DECLARE_PMID(kImplementationIDSpace, available,						kICBridgePrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kICBridgeScriptProviderImpl,		kICBridgePrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kICStoryStateMachineImpl,			kICBridgePrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kLiveEditFacadeImpl,				kICBridgePrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kStoryLinkEditActionImpl,			kICBridgePrefix + 5) 
DECLARE_PMID(kImplementationIDSpace, kLiveEditCmdResponderServiceImpl,	kICBridgePrefix + 6)	
//DECLARE_PMID(kImplementationIDSpace, available,						kICBridgePrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kLiveEditDocResponderImpl,			kICBridgePrefix + 8) 
//DECLARE_PMID(kImplementationIDSpace, available,						kICBridgePrefix + 9) 
//DECLARE_PMID(kImplementationIDSpace, available,						kICBridgePrefix + 10) 
DECLARE_PMID(kImplementationIDSpace, kLiveEditSelectionSuiteASBImpl,	kICBridgePrefix + 11) 
DECLARE_PMID(kImplementationIDSpace, kLiveEditSelectionSuiteImpl,		kICBridgePrefix + 12) 
DECLARE_PMID(kImplementationIDSpace, kLiveEditLinkResponderImpl,		kICBridgePrefix + 13) 
//DECLARE_PMID(kImplementationIDSpace, available,						kICBridgePrefix + 14) 
DECLARE_PMID(kImplementationIDSpace, kICBridgeAllowOverridesImpl,		kICBridgePrefix + 15)
//DECLARE_PMID(kImplementationIDSpace, available,						kICBridgePrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kICBridgeStoreInternalImpl,		kICBridgePrefix + 17)
// Gap
//DECLARE_PMID(kImplementationIDSpace, available,						kICBridgePrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kLiveEditCloseDocResponderImpl,	kICBridgePrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kStoryNeedsRelinkDataImpl,			kICBridgePrefix + 22)
//DECLARE_PMID(kImplementationIDSpace, available,						kICBridgePrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kLiveEditCmdDataImpl,				kICBridgePrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kICBridgeOpenFileDateImpl,			kICBridgePrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kICBridgeLockedImpl,				kICBridgePrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kLiveEditImportObserverImpl,		kICBridgePrefix + 27)
//DECLARE_PMID(kImplementationIDSpace, available,						kICBridgePrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kLiveEditDefaultSelectionSuiteImpl,kICBridgePrefix + 29) 
//DECLARE_PMID(kImplementationIDSpace, available,						kICBridgePrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kInCopyAMSPImpl,					kICBridgePrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kVCInCopyAMSPImpl,					kICBridgePrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kVCStoryLockImpl,					kICBridgePrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kVCICUIEnablementRulesImpl,		kICBridgePrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kICCheckOutServiceImpl,			kICBridgePrefix + 35)
//DECLARE_PMID(kImplementationIDSpace, available,						kICBridgePrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kVCVersionedStoryStateMachineImpl,	kICBridgePrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kVCLocalStoryStateMachineImpl,		kICBridgePrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kSaveStoryContentImpl,				kICBridgePrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kVCICBeforeCheckOutServiceImpl,	kICBridgePrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kVCICAfterCheckInServiceImpl,		kICBridgePrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kVCICAfterCancelCheckOutServiceImpl, kICBridgePrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kICUIEnablementRulesImpl,			kICBridgePrefix + 43)
//DECLARE_PMID(kImplementationIDSpace, available,						kICBridgePrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kVCInitializeVersionedStoryServiceImpl, kICBridgePrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kICStoryLockImpl,					kICBridgePrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kICCancelCheckOutServiceImpl,		kICBridgePrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kICCheckInServiceImpl,				kICBridgePrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kICInitializeStoryServiceImpl,		kICBridgePrefix + 49)
//DECLARE_PMID(kImplementationIDSpace, kICWorkgroupUIUtilsImpl,			kICBridgePrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kInCopyAMServiceProviderImpl,		kICBridgePrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kVCInCopyAMServiceProviderImpl,	kICBridgePrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kVCInitializeLocalStoryServiceImpl,kICBridgePrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kVCICEnsureLatestStoryServiceImpl,	kICBridgePrefix + 54)
//DECLARE_PMID(kImplementationIDSpace, available,						kICBridgePrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kVCInCopyUIServiceProviderImpl,	kICBridgePrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kVCICCheckOutServiceImpl,			kICBridgePrefix + 57)
//DECLARE_PMID(kImplementationIDSpace, available,						kICBridgePrefix + 58)
//DECLARE_PMID(kImplementationIDSpace, available,						kICBridgePrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kLiveEditCheckOutStoriesCmdImpl,	kICBridgePrefix + 60)
//DECLARE_PMID(kImplementationIDSpace, available,						kICBridgePrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kVCCheckInStoryServiceImpl,		kICBridgePrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kLiveEditCheckInStoriesCmdImpl,	kICBridgePrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kLiveEditCancelCheckOutStoriesCmdImpl,kICBridgePrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kLiveEditUpdateStoryLinksCmdImpl,	kICBridgePrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kLiveEditSaveStoriesCmdImpl,		kICBridgePrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kLiveEditRelockStoriesCmdImpl,		kICBridgePrefix + 67)

//----------------------------------------------------------------------------------------
// Service Provider IDs
//----------------------------------------------------------------------------------------

DECLARE_PMID(kServiceIDSpace,		kLiveEditCmdResponderService,		kICBridgePrefix + 1)

//----------------------------------------------------------------------------------------
// Action ID
//----------------------------------------------------------------------------------------
// <Action ID>

//
//Script Element IDs
//

//Suites

//Objects

//Events
DECLARE_PMID(kScriptInfoIDSpace, kICBridgeEditInPlaceMethodScriptElement,			kICBridgePrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kICBridgeSubmitMethodScriptElement,					kICBridgePrefix + 2)
DECLARE_PMID(kScriptInfoIDSpace, kICBridgeRevertMethodScriptElement,					kICBridgePrefix + 3)
DECLARE_PMID(kScriptInfoIDSpace, kICBridgeUpdateStoryMethodScriptElement,			kICBridgePrefix + 4)
DECLARE_PMID(kScriptInfoIDSpace, kICBridgeUpdateDesignMethodScriptElement,			kICBridgePrefix + 5)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kLockStatePropertyScriptElement,				kICBridgePrefix + 20)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kLockStateEnumScriptElement,					kICBridgePrefix + 50)

// <Error ID>
//----------------------------------------------------------------------------------------
// Error Codes
//----------------------------------------------------------------------------------------
#define kICBErr_NoError		kSuccess
#define kICBErr_Cancelled	kCancel					
#define kICBErr_Unknown		kFailure				

DECLARE_PMID(kErrorIDSpace, kICBErr_InvalidParameter,		kICBridgePrefix + 3)	
DECLARE_PMID(kErrorIDSpace, kICBErr_NoDataLink,				kICBridgePrefix + 4)	
DECLARE_PMID(kErrorIDSpace, kICBErr_BrokenLink,				kICBridgePrefix + 5)	
DECLARE_PMID(kErrorIDSpace, kICBErr_LinkIsEmbedded,			kICBridgePrefix + 6)	
DECLARE_PMID(kErrorIDSpace, kICBErr_NotNormalLink,			kICBridgePrefix + 7)	
DECLARE_PMID(kErrorIDSpace, kICBErr_CantGetLinkFile,		kICBridgePrefix + 8)	
DECLARE_PMID(kErrorIDSpace, kICBErr_kInvalidUserName,		kICBridgePrefix + 9)	
DECLARE_PMID(kErrorIDSpace, kICBErr_kLinkIsMissing,			kICBridgePrefix + 10)	

//----------------------------------------------------------------------------------------
// Strings
//----------------------------------------------------------------------------------------

// <String ID>
#define kICBridgeStringsRsrcID 					1000
#define kICBridgeStringsNoTransRsrcID 			1100

// used as TRACEFLOW category
#define kICBridgeTraceFlow		 				"InCopyBridge"

//----------------------------------------------------------------------------------------
// Lock File Version Numbers
//----------------------------------------------------------------------------------------

#define kICBridgeLockFileMajorFormatNumber		kDragontailMajorFormatNumber
#define kICBridgeLockFileMinorFormatNumber		RezLong(4)


#endif // __InCopyBridge__
