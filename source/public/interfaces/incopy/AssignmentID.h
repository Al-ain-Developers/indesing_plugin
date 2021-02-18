//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/AssignmentID.h $
//  
//  Owner: Jon Pugh
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

#ifndef __AssignmentID__
#define __AssignmentID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kAssignmentPrefix	 RezLong(0x1be00)

//PlugInID
#define kAssignmentPlugInName				"Assignment"
DECLARE_PMID(kPlugInIDSpace, kAssignmentPlugInID,							kAssignmentPrefix + 1)

// ClassIDs
//gap
DECLARE_PMID(kClassIDSpace, kAssignmentBoss,								kAssignmentPrefix + 1)
DECLARE_PMID(kClassIDSpace, kAssignmentMenuBoss,							kAssignmentPrefix + 2)
DECLARE_PMID(kClassIDSpace, kAssignmentScriptProviderBoss,					kAssignmentPrefix + 3)
DECLARE_PMID(kClassIDSpace, kAssignmentStoryScriptProviderBoss,				kAssignmentPrefix + 4)
DECLARE_PMID(kClassIDSpace, kAssignmentMgrDuringOpenDocResponderBoss,		kAssignmentPrefix + 5)
// DECLARE_PMID(kClassIDSpace, kAssignmentExportPolicyBoss,					kAssignmentPrefix + 6)
//gap
DECLARE_PMID(kClassIDSpace, kAssignmentCodeConversionProviderBoss,			kAssignmentPrefix + 8)
DECLARE_PMID(kClassIDSpace, kAssignmentImageScriptProviderBoss,				kAssignmentPrefix + 9)
DECLARE_PMID(kClassIDSpace, kAssignmentMgrOpenDocResponderBoss,				kAssignmentPrefix + 10)
DECLARE_PMID(kClassIDSpace, kAssignmentMgrNewDocResponderBoss,				kAssignmentPrefix + 11)
DECLARE_PMID(kClassIDSpace, kAssignmentMgrSaveDocResponderBoss,				kAssignmentPrefix + 12)
//gap
DECLARE_PMID(kClassIDSpace, kAssignmentMgrBeforeCloseDocResponderBoss,		kAssignmentPrefix + 14)
DECLARE_PMID(kClassIDSpace, kAssignmentSetColorCmdBoss,						kAssignmentPrefix + 15)
DECLARE_PMID(kClassIDSpace, kAssignedDocumentBoss,							kAssignmentPrefix + 16)
DECLARE_PMID(kClassIDSpace, kAssignDocCmdBoss,								kAssignmentPrefix + 17)
DECLARE_PMID(kClassIDSpace, kICAssignmentImportPolicyBoss,					kAssignmentPrefix + 18)
DECLARE_PMID(kClassIDSpace, kIDAssignmentImportPolicyBoss,					kAssignmentPrefix + 19)
DECLARE_PMID(kClassIDSpace, kUnassignDocCmdBoss,							kAssignmentPrefix + 20)
DECLARE_PMID(kClassIDSpace, kAssignedStoryBoss,								kAssignmentPrefix + 21)
DECLARE_PMID(kClassIDSpace, kAssignedImageBoss,								kAssignmentPrefix + 22)
DECLARE_PMID(kClassIDSpace, kObsoleteAssignedFrameBoss,						kAssignmentPrefix + 23)
DECLARE_PMID(kClassIDSpace, kAssignSetPropsCmdBoss,							kAssignmentPrefix + 24)
DECLARE_PMID(kClassIDSpace, kAssignStorySetPropsCmdDataBoss,				kAssignmentPrefix + 25)
DECLARE_PMID(kClassIDSpace, kAddToAssignmentCmdBoss,						kAssignmentPrefix + 26)
DECLARE_PMID(kClassIDSpace, kAssignStorySetPropsCmdBoss,					kAssignmentPrefix + 27)
DECLARE_PMID(kClassIDSpace, kIDAssignmentPackageOpenServiceBoss,			kAssignmentPrefix + 28)
DECLARE_PMID(kClassIDSpace, kAssignmentMgrAfterCloseDocResponderBoss,		kAssignmentPrefix + 29)
DECLARE_PMID(kClassIDSpace, kAssignImageSetPropsCmdDataBoss,				kAssignmentPrefix + 30)
DECLARE_PMID(kClassIDSpace, kAssignmentMgrBeforeSaveAsDocResponderBoss,		kAssignmentPrefix + 31)
DECLARE_PMID(kClassIDSpace, kAssignmentMgrAfterSaveAsDocResponderBoss,		kAssignmentPrefix + 32)
DECLARE_PMID(kClassIDSpace, kAssignmentImportValidationBoss,				kAssignmentPrefix + 33)
DECLARE_PMID(kClassIDSpace, kRemoveAssignedStoryCmdBoss,					kAssignmentPrefix + 34)
//gap
DECLARE_PMID(kClassIDSpace, kRemoveAssignedFrameCmdBoss,					kAssignmentPrefix + 36)
DECLARE_PMID(kClassIDSpace, kAssignmentScrapItemBoss,						kAssignmentPrefix + 37)
DECLARE_PMID(kClassIDSpace, kAssignmentMgrBeforeAddLinkResponderBoss,		kAssignmentPrefix + 38)
DECLARE_PMID(kClassIDSpace, kAssignmentMgrAfterAddLinkResponderBoss,		kAssignmentPrefix + 39)
//gap
DECLARE_PMID(kClassIDSpace, kAssignmentMgrBeforeAddExtraLinkResponderBoss,	kAssignmentPrefix + 42)
DECLARE_PMID(kClassIDSpace, kAssignmentMgrAfterAddExtraLinkResponderBoss,	kAssignmentPrefix + 43)
DECLARE_PMID(kClassIDSpace, kAssignmentMgrBeforeAttachDataLinkResponderBoss,kAssignmentPrefix + 44)
DECLARE_PMID(kClassIDSpace, kAssignmentMgrAfterAttachDataLinkResponderBoss,	kAssignmentPrefix + 45)
//gap
DECLARE_PMID(kClassIDSpace, kAssignmentMgrBeforeRemoveLinksResponderBoss,	kAssignmentPrefix + 50)
DECLARE_PMID(kClassIDSpace, kAssignmentMgrAfterRemoveLinksResponderBoss,	kAssignmentPrefix + 51)
DECLARE_PMID(kClassIDSpace, kAssignmentMgrBeforeRestoreLinkResponderBoss,	kAssignmentPrefix + 52)
DECLARE_PMID(kClassIDSpace, kAssignmentMgrAfterRestoreLinkResponderBoss,	kAssignmentPrefix + 53)
DECLARE_PMID(kClassIDSpace, kAssignmentMgrBeforeUpdateLinkResponderBoss,	kAssignmentPrefix + 54)
DECLARE_PMID(kClassIDSpace, kAssignmentMgrAfterUpdateLinkResponderBoss,		kAssignmentPrefix + 55)
DECLARE_PMID(kClassIDSpace, kAssignmentMgrBeforeAddEmbedResponderBoss,		kAssignmentPrefix + 56)
DECLARE_PMID(kClassIDSpace, kAssignmentMgrAfterAddEmbedResponderBoss,		kAssignmentPrefix + 57)
DECLARE_PMID(kClassIDSpace, kAssignmentMgrBeforeRemoveResponderBoss,		kAssignmentPrefix + 58)
DECLARE_PMID(kClassIDSpace, kAssignmentMgrAfterRemoveEmbedResponderBoss,	kAssignmentPrefix + 59)
DECLARE_PMID(kClassIDSpace, kAssignFrameSetPropsCmdBoss,					kAssignmentPrefix + 60)
DECLARE_PMID(kClassIDSpace, kShowAssignedFramesCmdBoss,						kAssignmentPrefix + 61)
DECLARE_PMID(kClassIDSpace, kMoveAssignedStoryCmdBoss,						kAssignmentPrefix + 62)
DECLARE_PMID(kClassIDSpace, kAssignmentConversionProviderBoss,				kAssignmentPrefix + 63)
DECLARE_PMID(kClassIDSpace, kMoveAssignmentCmdBoss,							kAssignmentPrefix + 64)
DECLARE_PMID(kClassIDSpace, kAssignmentMgrDuringSaveACopyDocServiceBoss,	kAssignmentPrefix + 65)
DECLARE_PMID(kClassIDSpace, kAssignmentExportAllPolicyBoss,					kAssignmentPrefix + 66)
DECLARE_PMID(kClassIDSpace, kAssignmentExportSpreadsPolicyBoss,				kAssignmentPrefix + 67)
DECLARE_PMID(kClassIDSpace, kAssignmentExportFramesPolicyBoss,				kAssignmentPrefix + 68)
DECLARE_PMID(kClassIDSpace, kAssignmentErrorStringServiceBoss,				kAssignmentPrefix + 69)
DECLARE_PMID(kClassIDSpace, kAssignmentMgrAfterRevertDocServiceBoss,		kAssignmentPrefix + 70)
DECLARE_PMID(kClassIDSpace, kRelinkAssignmentCmdBoss_Obsolete,				kAssignmentPrefix + 71)
DECLARE_PMID(kClassIDSpace, kAssignmentPackageInfoFileBoss,					kAssignmentPrefix + 72)
DECLARE_PMID(kClassIDSpace, kAssignmentPackageInfoHandlerBoss,				kAssignmentPrefix + 73)
DECLARE_PMID(kClassIDSpace, kCreateAssignmentPackageCmdBoss,				kAssignmentPrefix + 74)
DECLARE_PMID(kClassIDSpace, kCancelAssignmentPackageCmdBoss,				kAssignmentPrefix + 75)
DECLARE_PMID(kClassIDSpace, kCreateAssignmentReturnPackageCmdBoss,			kAssignmentPrefix + 76)
DECLARE_PMID(kClassIDSpace, kCreateAssignmentForwardPackageCmdBoss,			kAssignmentPrefix + 77)
DECLARE_PMID(kClassIDSpace, kIDAssignmentPackageOpenDocResponderBoss,		kAssignmentPrefix + 78)
DECLARE_PMID(kClassIDSpace, kAssignmentMgrLinksChangedLinkResponderBoss,	kAssignmentPrefix + 79)
DECLARE_PMID(kClassIDSpace, kAssignmentPhase2ConversionBoss,				kAssignmentPrefix + 80)

// Interface IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IASSIGNMENTMGR,							kAssignmentPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IASSIGNMENTSELECTIONSUITE,				kAssignmentPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IASSIGNMENTUTILS,						kAssignmentPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IASSIGNMENTMGRCHANGED,					kAssignmentPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IASSIGNMENTPACKAGEINFOFILE,				kAssignmentPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IASSIGNMENTDATACHANGED,					kAssignmentPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IASSIGNMENTCOLORPERSISTUIDDATA,			kAssignmentPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IASSIGNMENTCOLORCHANGED,				kAssignmentPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IASSIGNEDDOCUMENT,						kAssignmentPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace,	IID_IASSIGNMENTOBSERVER,					kAssignmentPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace,	IID_IASSIGNMENT,							kAssignmentPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace,	IID_IASSIGNEDSTORY,							kAssignmentPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IOPENASSIGNMENTPACKAGEDETAILS,			kAssignmentPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IASSIGNMENTPACKAGEUTILS,				kAssignmentPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace,	IID_IASSIGNSETPROPSCMDDATA,					kAssignmentPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace,	IID_IASSIGNSTORYSETPROPSCMDDATA,			kAssignmentPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace,	IID_IASSIGNMENTPACKAGEINFOFILEDATA,			kAssignmentPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_IIDOPENASSIGNMENTPACKAGEDETAILS,		kAssignmentPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace,	IID_IASSIGNMENTPREFERENCES,					kAssignmentPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace,	IID_ITOASSIGNMENT,							kAssignmentPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace,	IID_IFROMASSIGNMENT,						kAssignmentPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace,	IID_IADDSTORY,								kAssignmentPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace,	IID_IBEFORESTORY,							kAssignmentPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_IASSIGNMENTPRIVATEUTILS,				kAssignmentPrefix + 24)

// Implementation IIDs
DECLARE_PMID(kImplementationIDSpace, kAssignmentMgrImpl,					kAssignmentPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kAssignmentSuiteASBImpl,				kAssignmentPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kAssignmentSuiteCSBImpl,				kAssignmentPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kAssignmentScriptImpl,					kAssignmentPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kAssignmentScriptProviderImpl,			kAssignmentPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kAssignmentStoryScriptImpl,			kAssignmentPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kAssignmentStoryScriptProviderImpl,	kAssignmentPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kAssignmentUtilsImpl,					kAssignmentPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kAssignmentCodeConversionProviderImpl,	kAssignmentPrefix + 9)

// DECLARE_PMID(kImplementationIDSpace, kAssignmentExportPolicyImpl,			kAssignmentPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kAssignmentImageScriptImpl,			kAssignmentPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kAssignmentImageScriptProviderImpl,	kAssignmentPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kAssignmentMgrObserverImpl,			kAssignmentPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kAssignmentMgrResponderImpl,			kAssignmentPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kAssignmentSetColorCmdImpl,			kAssignmentPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kAssignmentColorPersistUIDDataImpl,	kAssignmentPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kAssignedDocumentImpl,					kAssignmentPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kAssignDocCmdImpl,						kAssignmentPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kICAssignmentImportPolicyImpl,			kAssignmentPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kIDAssignmentImportPolicyImpl,			kAssignmentPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kUnassignDocCmdImpl,					kAssignmentPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kAssignedStoryImpl,					kAssignmentPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kAssignedImageImpl,					kAssignmentPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kObsoleteAssignedFrameImpl,			kAssignmentPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kAssignmentImpl,						kAssignmentPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kAssignSetPropsCmdImpl,				kAssignmentPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kAssignSetPropsCmdDataImpl,			kAssignmentPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kAssignStorySetPropsCmdDataImpl,		kAssignmentPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kAddToAssignmentCmdImpl,				kAssignmentPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kAssignStorySetPropsCmdImpl,			kAssignmentPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kOpenAssignmentPackageDetailsImpl,		kAssignmentPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kAssignmentPackageUtilsImpl,			kAssignmentPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kAssignmentImportValidationImpl,		kAssignmentPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kRemoveAssignedStoryCmdImpl,			kAssignmentPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kAssignmentPackageInfoFileDataImpl,	kAssignmentPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kRemoveAssignedFrameCmdImpl,			kAssignmentPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kAssignmentScrapItemImpl,				kAssignmentPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kAssignFrameSetPropsCmdImpl,			kAssignmentPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kAssignFrameSetPropsCmdDataImpl,		kAssignmentPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kAssignmentPreferencesImpl,			kAssignmentPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kShowAssignedFramesCmdImpl,			kAssignmentPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kMoveAssignedStoryCmdImpl,				kAssignmentPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kMoveAssignmentCmdImpl,				kAssignmentPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kAssignmentExportAllPolicyImpl,		kAssignmentPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kAssignmentExportSpreadsPolicyImpl,	kAssignmentPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kAssignmentExportFramesPolicyImpl,		kAssignmentPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kAssignmentErrorStringServiceImpl,		kAssignmentPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kToAssignmentImpl,						kAssignmentPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kFromAssignmentImpl,					kAssignmentPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kAddStoryImpl,							kAssignmentPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kBeforeStoryImpl,						kAssignmentPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kRelinkAssignmentCmdImpl_Obsolete,		kAssignmentPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kAssignmentPackageInfoFileImpl,		kAssignmentPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kAssignmentPackageInfoHandlerImpl,		kAssignmentPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kCreateAssignmentPackageCmdImpl,		kAssignmentPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kIDAssignmentPackageOpenFilterImpl,	kAssignmentPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kCancelAssignmentPackageCmdImpl,		kAssignmentPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kCreateAssignmentReturnPackageCmdImpl, kAssignmentPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kCreateAssignmentForwardPackageCmdImpl, kAssignmentPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kIDAssignmentPackageOpenDocResponderImpl, kAssignmentPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kIDOpenAssignmentPackageDetailsImpl,	kAssignmentPrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kAssignmentPhase2ConversionImpl,		kAssignmentPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kAssignmentPrivateUtilsImpl,			kAssignmentPrefix + 65)

// Error IDs
DECLARE_PMID(kErrorIDSpace, kAssignmentWrongDocType,						kAssignmentPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kBadEnumErr,									kAssignmentPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kAssignmentExistsError,							kAssignmentPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kNoAssignmentPathError,							kAssignmentPrefix + 4)
DECLARE_PMID(kErrorIDSpace, kCantDeleteUnAssignmentErr,						kAssignmentPrefix + 5)
DECLARE_PMID(kErrorIDSpace, kCantWriteAssignmentPackageInfoFile,			kAssignmentPrefix + 6)
DECLARE_PMID(kErrorIDSpace, kCantParseAssignmentPackageInfoFile,			kAssignmentPrefix + 7)
DECLARE_PMID(kErrorIDSpace, kAcquireMailServiceErr,							kAssignmentPrefix + 8)
DECLARE_PMID(kErrorIDSpace, kCreateMessageErr,								kAssignmentPrefix + 9)
DECLARE_PMID(kErrorIDSpace, kSendMessageErr,								kAssignmentPrefix + 10)
DECLARE_PMID(kErrorIDSpace, kAddAttachmentErr,								kAssignmentPrefix + 11)
DECLARE_PMID(kErrorIDSpace, kNoAssignmentAssetErr,							kAssignmentPrefix + 12)
DECLARE_PMID(kErrorIDSpace, kNoPackageFileErr,								kAssignmentPrefix + 13)
DECLARE_PMID(kErrorIDSpace, kAssignmentFileNotFoundErr,						kAssignmentPrefix + 14)
DECLARE_PMID(kErrorIDSpace, kAsnPkgWrongFileTypeIDErr,						kAssignmentPrefix + 15)
DECLARE_PMID(kErrorIDSpace, kAssignmentNotInDocErr,							kAssignmentPrefix + 16)
DECLARE_PMID(kErrorIDSpace, kAssignmentNotPackagedErr,						kAssignmentPrefix + 17)
DECLARE_PMID(kErrorIDSpace, kAssignmentPackageMismatchErr,					kAssignmentPrefix + 18)
DECLARE_PMID(kErrorIDSpace, kAssignmentDocNotFoundErr,						kAssignmentPrefix + 19)
DECLARE_PMID(kErrorIDSpace, kAssignmentWrongDocTypeErr,						kAssignmentPrefix + 20)
DECLARE_PMID(kErrorIDSpace, kAssignmentExplodeForOpenErr,					kAssignmentPrefix + 21)
DECLARE_PMID(kErrorIDSpace, kAssignmentNotInDocTryBrowse,					kAssignmentPrefix + 22)
DECLARE_PMID(kErrorIDSpace, kAssignmentNotInDocTryExtract,					kAssignmentPrefix + 23)
DECLARE_PMID(kErrorIDSpace, kAssignmentPackageMismatchTryExtract,			kAssignmentPrefix + 24)
DECLARE_PMID(kErrorIDSpace, kAssignmentNotPackagedTryExtract,				kAssignmentPrefix + 25)
DECLARE_PMID(kErrorIDSpace, kCreatePkgNoPackagePathError,					kAssignmentPrefix + 26)
DECLARE_PMID(kErrorIDSpace, kCreatePkgUnassignmentNotAllowedErr,			kAssignmentPrefix + 27)
DECLARE_PMID(kErrorIDSpace, kCreatePkgAlreadyPackagedErr,					kAssignmentPrefix + 28)
DECLARE_PMID(kErrorIDSpace, kCreatePkgCheckedOutByOtherErr,					kAssignmentPrefix + 29)
DECLARE_PMID(kErrorIDSpace, kCancelPkgNotPackagedErr,						kAssignmentPrefix + 30)
DECLARE_PMID(kErrorIDSpace, kCreatePkgSubmitBeforePackageFailedErr,			kAssignmentPrefix + 31)
DECLARE_PMID(kErrorIDSpace, kCreatePkgCheckedOutErr,						kAssignmentPrefix + 32)
DECLARE_PMID(kErrorIDSpace, kCreatePkgNotPackagedErr,						kAssignmentPrefix + 33)
DECLARE_PMID(kErrorIDSpace, kCreatePkgSaveAsnErr,							kAssignmentPrefix + 34)
DECLARE_PMID(kErrorIDSpace, kCreatePkgJobBagErr,							kAssignmentPrefix + 35)
DECLARE_PMID(kErrorIDSpace, kCreatePkgFailure,								kAssignmentPrefix + 36)
DECLARE_PMID(kErrorIDSpace, kGetUpToDateNotPackagedErr,						kAssignmentPrefix + 37)
DECLARE_PMID(kErrorIDSpace, kCreatePkgCheckOutAfterPackageFailedErr,		kAssignmentPrefix + 38)
DECLARE_PMID(kErrorIDSpace, kPackageAssignmentNameErr,						kAssignmentPrefix + 39)
DECLARE_PMID(kErrorIDSpace, kCreatePkgDocNotSavedErr,						kAssignmentPrefix + 40)
DECLARE_PMID(kErrorIDSpace, kCreateAssignmentDocNotSavedErr,				kAssignmentPrefix + 41)
DECLARE_PMID(kErrorIDSpace, kStoryFormatNotCompatibleErr,					kAssignmentPrefix + 42)
DECLARE_PMID(kErrorIDSpace, kEndnotesLinksUIError,							kAssignmentPrefix + 43)

// Action IDs
DECLARE_PMID(kActionIDSpace, kAssignmentActionID,							kAssignmentPrefix + 1)

// Message IDs
DECLARE_PMID(kMessageIDSpace, kAssignmentMgrChangedNotifyMsg,				kAssignmentPrefix + 1)
DECLARE_PMID(kMessageIDSpace, kAssignmentPanelInvalidateNotifyMsg,			kAssignmentPrefix + 2)

// Scripting IDs
DECLARE_PMID(kScriptIDSpace, kAssignmentSuiteScriptElement,					kAssignmentPrefix + 1)
DECLARE_PMID(kScriptIDSpace, kAssignmentObjectScriptElement,				kAssignmentPrefix + 2)
DECLARE_PMID(kScriptIDSpace, kAssignmentStoryObjectScriptElement,			kAssignmentPrefix + 3)
DECLARE_PMID(kScriptIDSpace, kAssignmentUserNamePropertyScriptElement,		kAssignmentPrefix + 4)
DECLARE_PMID(kScriptIDSpace, kAssignmentPackageUpToDatePropertyScriptElement,kAssignmentPrefix + 5)
DECLARE_PMID(kScriptIDSpace, kStoryRefPropScriptElement,					kAssignmentPrefix + 6)
DECLARE_PMID(kScriptIDSpace, kCreateAssignmentMethodScriptElement,			kAssignmentPrefix + 7)
DECLARE_PMID(kScriptIDSpace, kAssignmentArticleObjectScriptElement,			kAssignmentPrefix + 8)
DECLARE_PMID(kScriptIDSpace, kAssignmentImageObjectScriptElement,			kAssignmentPrefix + 9)
DECLARE_PMID(kScriptIDSpace, kPageItemRefPropScriptElement,					kAssignmentPrefix + 10)
DECLARE_PMID(kScriptIDSpace, kUIDPropScriptElement,							kAssignmentPrefix + 11)
DECLARE_PMID(kScriptIDSpace, kCreateAssignedStoryMethodScriptElement,		kAssignmentPrefix + 12)
DECLARE_PMID(kScriptIDSpace, kCreateAssignedImageMethodScriptElement,		kAssignmentPrefix + 13)
DECLARE_PMID(kScriptIDSpace, kFrameColorPropScriptElement,					kAssignmentPrefix + 14)
DECLARE_PMID(kScriptIDSpace, kSaveAssignmentMethodScriptElement,				kAssignmentPrefix + 15)
DECLARE_PMID(kScriptIDSpace, kExportOptionsEnumScriptElement,				kAssignmentPrefix + 16)
DECLARE_PMID(kScriptIDSpace, kExportOptionsPropScriptElement,				kAssignmentPrefix + 17)
DECLARE_PMID(kScriptIDSpace, kMoveAssignedStoryMethodScriptElement,			kAssignmentPrefix + 18)
DECLARE_PMID(kScriptIDSpace, kDeleteAssignmentMethodScriptElement,			kAssignmentPrefix + 19)
DECLARE_PMID(kScriptIDSpace, kAssignmentStatusEnumScriptElement,			kAssignmentPrefix + 20)
DECLARE_PMID(kScriptIDSpace, kAssignmentStatusPropScriptElement,			kAssignmentPrefix + 21)
DECLARE_PMID(kScriptIDSpace, kIncludeLinksWhenPackagePropScriptElement,		kAssignmentPrefix + 22)
DECLARE_PMID(kScriptIDSpace, kCreateAssignmentPackageMethodScriptElement,	kAssignmentPrefix + 23)
DECLARE_PMID(kScriptIDSpace, kCancelAssignmentPackageMethodScriptElement,	kAssignmentPrefix + 24)
DECLARE_PMID(kScriptIDSpace, kAssignmentPackageTypeEnumScriptElement,		kAssignmentPrefix + 25)
DECLARE_PMID(kScriptIDSpace, kAssignmentPackagedPropertyScriptElement,		kAssignmentPrefix + 26)

// Inval Handler IDs
DECLARE_PMID(kInvalHandlerIDSpace, kAssignmentCreatePackageInvalHandlerID, 		kAssignmentPrefix + 1)
DECLARE_PMID(kInvalHandlerIDSpace, kAssignmentCancelPackageInvalHandlerID, 		kAssignmentPrefix + 2)



#define kAssignmentStringsRsrcID				1000
#define kAssignmentStringsNoTransRsrcID			2000
#define kAssignmentErrorStringTableRsrcID		3000

#endif // __AssignmentID__
