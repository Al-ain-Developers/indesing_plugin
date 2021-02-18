//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/SoapServerID.h $
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
//========================================================================================

#ifndef __SoapServerID__
#define __SoapServerID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kSoapServerIDPrefix	RezLong(0x1DB00)

// <Start IDC>
// PluginID
#define kSoapServerName 				"SoapServer"

START_IDS()
DECLARE_PMID(kPlugInIDSpace, kSoapServerID, kSoapServerIDPrefix + 1)


// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kSoapServerStartupShutdownBoss, 				kSoapServerIDPrefix + 1)
DECLARE_PMID(kClassIDSpace, kSoapServerIdleTaskBoss, 						kSoapServerIDPrefix + 2)
DECLARE_PMID(kClassIDSpace, kSoapServerScriptProviderBoss, 					kSoapServerIDPrefix + 3)
DECLARE_PMID(kClassIDSpace, kErrorListScriptProviderBoss, 					kSoapServerIDPrefix + 4)
DECLARE_PMID(kClassIDSpace, kServerSettingsScriptProviderBoss, 				kSoapServerIDPrefix + 5)
DECLARE_PMID(kClassIDSpace, kErrorListScriptObjectBoss, 					kSoapServerIDPrefix + 6)
//DECLARE_PMID(kClassIDSpace, kUnusedBoss, 						kSoapServerIDPrefix + 7)
DECLARE_PMID(kClassIDSpace, kServerDocFileHandlerBoss, 						kSoapServerIDPrefix + 8)
// gap

#ifdef DEBUG
DECLARE_PMID(kClassIDSpace, kModelUIScriptProviderBoss, 					kSoapServerIDPrefix + 9)
#endif

DECLARE_PMID(kClassIDSpace, kXSLEnablerServiceBoss, 						kSoapServerIDPrefix + 10)
DECLARE_PMID(kClassIDSpace, kServerTestScriptProviderBoss, 					kSoapServerIDPrefix + 11)

DECLARE_PMID(kClassIDSpace, kShutdownRequestIdleTaskBoss, 					kSoapServerIDPrefix + 12)

// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IERRORLIST, 							kSoapServerIDPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ISERVERSHUTDOWNOBSERVER, 				kSoapServerIDPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IERRORLISTDATA, 						kSoapServerIDPrefix + 3)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_ISOAPSERVERDATA, 						kSoapServerIDPrefix + 5)

// <Implementation ID>
// ImplementationIIDs
DECLARE_PMID(kImplementationIDSpace, kSoapServerStartupShutdownImpl, 		kSoapServerIDPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kSoapServerIdleTaskImpl, 				kSoapServerIDPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kErrorListImpl, 						kSoapServerIDPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kErrorListDataImpl, 					kSoapServerIDPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kErrorListScriptImpl, 					kSoapServerIDPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kErrorListScriptProviderImpl, 			kSoapServerIDPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kServerSettingsScriptProviderImpl, 	kSoapServerIDPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kServerShutdownObserverImpl,			kSoapServerIDPrefix + 8)
//DECLARE_PMID(kImplementationIDSpace, kUnusedImpl, 			kSoapServerIDPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kSoapServerDataImpl, 					kSoapServerIDPrefix + 10)
#ifdef DEBUG
DECLARE_PMID(kImplementationIDSpace, kModelUIScriptProviderImpl, 			kSoapServerIDPrefix + 11)
#endif

DECLARE_PMID(kImplementationIDSpace, kServerTestScriptProviderImpl, 		kSoapServerIDPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kServerStartupShutdownProviderImpl, 	kSoapServerIDPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kShutdownRequestIdleTaskImpl, 			kSoapServerIDPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kServerDocFileHandlerImpl, 			kSoapServerIDPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kServerProgressBarManagerImpl,			kSoapServerIDPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kIDSApplicationDelegateImpl, 			kSoapServerIDPrefix + 19)

// <Service ID>
// Service Providers
//DECLARE_PMID(kServiceIDSpace, kNewPISignalResponderService, kGenericIDPrefix + 1)


// <Error ID>
// Error Codes
//DECLARE_PMID(kErrorIDSpace, kItemDoesNotIntersectBoundsError, kGenericIDPrefix + 1)

// <Message ID>
// Message IDs (start at 200)
//DECLARE_PMID(kMessageIDSpace, kGenericMsgPrefix, kGenericIDPrefix + 200)

// <Global ID>
// Global IDs
//DECLARE_PMID(kActionIDSpace, kZeroStrokeActionID, kGenericIDPrefix + 1)

//
//Script Element IDs
//
DECLARE_PMID(kScriptInfoIDSpace,	kSoapServerSuiteScriptElement,			kSoapServerIDPrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace,	kErrorListObjectScriptElement,			kSoapServerIDPrefix + 2)
DECLARE_PMID(kScriptInfoIDSpace,	kMountProjectMethodScriptElement,		kSoapServerIDPrefix + 3)
// gap
DECLARE_PMID(kScriptInfoIDSpace,	kErrorListLogErrorsPropertyScriptElement,	kSoapServerIDPrefix + 5)
DECLARE_PMID(kScriptInfoIDSpace,	kErrorCodePropertyScriptElement,		kSoapServerIDPrefix + 6)
DECLARE_PMID(kScriptInfoIDSpace,	kErrorLevelPropertyScriptElement,		kSoapServerIDPrefix + 7)
DECLARE_PMID(kScriptInfoIDSpace,	kErrorMessagePropertyScriptElement,		kSoapServerIDPrefix + 8)
DECLARE_PMID(kScriptInfoIDSpace,	kErrorTimePropertyScriptElement,		kSoapServerIDPrefix + 9)

DECLARE_PMID(kScriptInfoIDSpace,	kServerTestMethodScriptElement,			kSoapServerIDPrefix + 10)
// gap
DECLARE_PMID(kScriptInfoIDSpace,	kServerSettingsImagePreviewPropertyScriptElement,	kSoapServerIDPrefix + 12)
DECLARE_PMID(kScriptInfoIDSpace,	kServerSettingsJavaScriptUIPropertyScriptElement,	kSoapServerIDPrefix + 13)
//gap
DECLARE_PMID(kScriptInfoIDSpace,	kServerSettingsMainThreadModePropertyScriptElement,	kSoapServerIDPrefix + 15)
DECLARE_PMID(kScriptInfoIDSpace,	kIsSSLoggingEnabledPropertyScriptElement,	kSoapServerIDPrefix + 16)
DECLARE_PMID(kScriptInfoIDSpace,	kSessionTimeoutPropertyScriptElement,	kSoapServerIDPrefix + 17)
//gap
DECLARE_PMID(kScriptInfoIDSpace,   kNonBlockingSessionSupportPropertyScriptElement,   kSoapServerIDPrefix + 19)
DECLARE_PMID(kScriptInfoIDSpace,   kNonBlockingSSMaxWaitPropertyScriptElement,   kSoapServerIDPrefix + 20)

#ifdef DEBUG
DECLARE_PMID(kScriptInfoIDSpace, kPluginsWithUIPropertyScriptElement,		kSoapServerIDPrefix + 250)
DECLARE_PMID(kScriptInfoIDSpace, kModelPluginsWithUIPropertyScriptElement,	kSoapServerIDPrefix + 251)
DECLARE_PMID(kScriptInfoIDSpace, kUIPluginsWithModelPropertyScriptElement,	kSoapServerIDPrefix + 252)
#endif
//Suites

//Objects
//DECLARE_PMID(kScriptInfoIDSpace, kPageItemObjectScriptElement,					kGenericIDPrefix + 10)

//Events
//DECLARE_PMID(kScriptInfoIDSpace, kBringToFrontMethodScriptElement,				kGenericIDPrefix + 80)

//Properties
//DECLARE_PMID(kScriptInfoIDSpace, kContentTypePropertyScriptElement,				kGenericIDPrefix + 120)

//Enums
//DECLARE_PMID(kScriptInfoIDSpace, kUnlinkFromWhatEnumScriptElement,				kGenericIDPrefix + 240)

END_IDS()

#ifndef RESOURCE_NUMBER	 //avoid errors in SoapServerID.fr

enum SoapServerScriptIDs
{
    s_SoapServerSuite 		=		'ssrs',

	c_errorlisterror 		=		'eler',
	c_errorlisterrors 		=		'elrs',

	e_ServerTest			= 		'Stst',

	p_ErrorCode				=		'gerc',
    p_ErrorLevel 			=		'gerl',
    p_ErrorMessage 			=		'germ',
    p_ErrorTime 			=		'gert',

	p_ImagePreview 			=		'gsip',
    p_JavaScriptUI 			=		'gsju',

	p_OnMainThreadOnly		=		'omto',
	p_SSLoggingEnabled		=		'sslo',
	p_SessionTimeout		=		'stmo',
	p_heartbeatUpdateInterval =		'hbui',
	p_NonBlockingSessionSupport =	'nbss',
	p_NonBlockingSSMaxWait		=	'nbmw',
};

// {9D85AD06-8A8A-485e-89B2-39BD9886AA51}
#define kErrorListError_CLSID { 0x9d85ad06, 0x8a8a, 0x485e, { 0x89, 0xb2, 0x39, 0xbd, 0x98, 0x86, 0xaa, 0x51 } }
// {66FC6455-CBC1-4bc3-8CBB-4CC3C4692B45}
#define kErrorListErrors_CLSID { 0x66fc6455, 0xcbc1, 0x4bc3, { 0x8c, 0xBB, 0x4c, 0xc3, 0xc4, 0x69, 0x2b, 0x45 } }

#endif

#endif // __GenericID__
