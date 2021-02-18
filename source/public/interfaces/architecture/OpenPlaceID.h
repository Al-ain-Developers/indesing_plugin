//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/OpenPlaceID.h $
//  
//  Owner: Zak Williamson
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

#ifndef __OpenPlaceID__
#define __OpenPlaceID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"
#include "FormatNumber.h"

#define kOpenPlacePrefix	RezLong(0x7300)


// PluginID
#define kOpenPlacePluginName 		"Open Place"
DECLARE_PMID(kPlugInIDSpace, kOpenPlacePluginID, kOpenPlacePrefix + 1)

// Class IDs
DECLARE_PMID(kClassIDSpace, kImportManagerBoss, kOpenPlacePrefix + 1)
DECLARE_PMID(kClassIDSpace, kOpenManagerBoss, kOpenPlacePrefix + 2)
DECLARE_PMID(kClassIDSpace, kPlaceToolBoss_obsolete, kOpenPlacePrefix + 3)
DECLARE_PMID(kClassIDSpace, kImportResourceCmdBoss, kOpenPlacePrefix + 4)
DECLARE_PMID(kClassIDSpace, kLoadPlaceGunCmdBoss, kOpenPlacePrefix + 5)
DECLARE_PMID(kClassIDSpace, kClearPlaceGunCmdBoss, kOpenPlacePrefix + 6)
DECLARE_PMID(kClassIDSpace, kOpenPlaceErrorStringServiceBoss, kOpenPlacePrefix + 7)
DECLARE_PMID(kClassIDSpace, kRotatePlaceGunCmdBoss, kOpenPlacePrefix + 8)
DECLARE_PMID(kClassIDSpace, kAbortPlaceGunCmdBoss, kOpenPlacePrefix + 9)
DECLARE_PMID(kClassIDSpace, kImportPIFromResourceCmdBoss, kOpenPlacePrefix + 10)
DECLARE_PMID(kClassIDSpace, kOpenFileCmdBoss, kOpenPlacePrefix + 11)
DECLARE_PMID(kClassIDSpace, kLoadSnippetCmdBoss, kOpenPlacePrefix + 12)
DECLARE_PMID(kClassIDSpace, kPlaceScriptProviderBoss, kOpenPlacePrefix + 13)
DECLARE_PMID(kClassIDSpace, kImportScriptEventResponderServiceBoss, kOpenPlacePrefix + 14)
//DECLARE_PMID(kClassIDSpace, kImportProviderSignalMgrBoss, kOpenPlacePrefix + 15)	//For now we use a kExportProviderSignalMgrBoss for import and export signaling
DECLARE_PMID(kClassIDSpace, kImportAndLoadPlaceGunCmdBoss, kOpenPlacePrefix + 16)
DECLARE_PMID(kClassIDSpace, kPlaceComponentBoss_obsolete, kOpenPlacePrefix + 17)
DECLARE_PMID(kClassIDSpace, kImportAndPlaceCmdBoss, kOpenPlacePrefix + 18)
DECLARE_PMID(kClassIDSpace, kReplaceCmdBoss, kOpenPlacePrefix + 19)
DECLARE_PMID(kClassIDSpace, kReimportCmdBoss, kOpenPlacePrefix + 20)
DECLARE_PMID(kClassIDSpace, kPlaceBehaviorSignalMgrBoss, kOpenPlacePrefix + 21)
DECLARE_PMID(kClassIDSpace, kCancelImportFileMsg, kOpenPlacePrefix + 22)
DECLARE_PMID(kClassIDSpace, kPlaceScriptEventResponderServiceBoss, kOpenPlacePrefix + 23)
DECLARE_PMID(kClassIDSpace, kPlaceConversionProviderBoss, kOpenPlacePrefix + 24)
DECLARE_PMID(kClassIDSpace, kEndPlaceCmdBoss, kOpenPlacePrefix + 25)
DECLARE_PMID(kClassIDSpace, kPlaceGunOpenDocResponderBoss, kOpenPlacePrefix + 26)
DECLARE_PMID(kClassIDSpace, kPlaceGunNewDocResponderBoss, kOpenPlacePrefix + 27)
DECLARE_PMID(kClassIDSpace, kOpenPlaceCodeConverterProviderBoss, kOpenPlacePrefix + 28)
DECLARE_PMID(kClassIDSpace, kSetSnippetImportLocationPrefCmdBoss, kOpenPlacePrefix + 29)
DECLARE_PMID(kClassIDSpace, kPlaceSnippetCmdBoss, kOpenPlacePrefix + 30)
DECLARE_PMID(kClassIDSpace, kPlaceGunScriptProviderBoss, kOpenPlacePrefix + 31)
DECLARE_PMID(kClassIDSpace, kPlaceGunContentScriptProviderBoss, kOpenPlacePrefix + 32)

// Interface IDs
DECLARE_PMID(kInterfaceIDSpace, IID_IIMPORTPROVIDER, kOpenPlacePrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IPLACEGUN, kOpenPlacePrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IOPENMANAGER, kOpenPlacePrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMPORTMANAGER, kOpenPlacePrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IOPENCORE, kOpenPlacePrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IOPENRECOVERYOPTIONS, kOpenPlacePrefix + 6)
//DECLARE_PMID(kInterfaceIDSpace, IID_IIMPORTPROVIDERSIGNALDATA, kOpenPlacePrefix + 6)	//For now we use a kExportProviderSignalMgrBoss for import and export signaling
DECLARE_PMID(kInterfaceIDSpace, IID_IIMPORTRESOURCECMDDATA, kOpenPlacePrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMPORTCORE, kOpenPlacePrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMPORTMANAGEROPTIONS, kOpenPlacePrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IREPLACECMDDATA, kOpenPlacePrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IOPENFILECMDDATA, kOpenPlacePrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMPORTFILECMDDBOBSERVER, kOpenPlacePrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMPORTSUITE, kOpenPlacePrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMPORTPREVIEW, kOpenPlacePrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IPLACESCRIPTHELPER, kOpenPlacePrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEITEMIMPORTMANAGER, kOpenPlacePrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_ILOADPLACEGUNCMDDATA, kOpenPlacePrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_ISNIPPETIMPORTUSESORIGINALLOCATIONPREF, kOpenPlacePrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_ISNIPPETIMPORTUSESORIGINALLOCATIONPREFCMDDATA, kOpenPlacePrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_IBATCHPLACETRACKERHELPER, kOpenPlacePrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_IPLACEBEHAVIORSIGNALDATA, kOpenPlacePrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMPORTEXPORTFACADE, kOpenPlacePrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_IALLOWSPREADCHANGE, kOpenPlacePrefix + 23) 
DECLARE_PMID(kInterfaceIDSpace, IID_IPLACEGUNUTILS, kOpenPlacePrefix + 24) 
DECLARE_PMID(kInterfaceIDSpace, IID_ITEMPORARYIMPORTCACHE, kOpenPlacePrefix + 25) 
DECLARE_PMID(kInterfaceIDSpace, IID_IPLACECLOUDASSETUTILS, kOpenPlacePrefix + 26)

// <Implementation ID>
// Implementation IDs
DECLARE_PMID(kImplementationIDSpace, kPlaceGunScriptProviderImpl, kOpenPlacePrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kPlaceGunContentScriptProviderImpl, kOpenPlacePrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kPlaceScriptEventServiceProviderImpl, kOpenPlacePrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kPlaceScriptEventResponderImpl, kOpenPlacePrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kPlaceComponentImpl_obsolete, kOpenPlacePrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kPlaceGunImpl, kOpenPlacePrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kImportResourceCmdImpl, kOpenPlacePrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kLoadPlaceGunCmdImpl, kOpenPlacePrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kClearPlaceGunCmdImpl, kOpenPlacePrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kOpenMgrServiceImpl, kOpenPlacePrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kImportServiceImpl, kOpenPlacePrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kOpenServiceImpl, kOpenPlacePrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kOpenManagerImpl, kOpenPlacePrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kAbortPlaceGunCmdImpl, kOpenPlacePrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kRotatePlaceGunCmdImpl, kOpenPlacePrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kImportManagerOptionsImpl, kOpenPlacePrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kPlaceGunUtilsImpl, kOpenPlacePrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kOpenPlaceErrorStringServiceImpl, kOpenPlacePrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kImportPIFromResourceCmdImpl, kOpenPlacePrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kOpenFileCmdImpl, kOpenPlacePrefix + 19)
//DECLARE_PMID(kImplementationIDSpace, kImportProviderSignalDataImpl, kOpenPlacePrefix + 20)	//For now we use a kExportProviderSignalMgrBoss for import and export signaling
DECLARE_PMID(kImplementationIDSpace, kPlaceGunCursorProviderImpl_obsolete, kOpenPlacePrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kPlaceGunToolImpl_obsolete, kOpenPlacePrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kImportScriptEventServiceProviderImpl, kOpenPlacePrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kPlaceScriptProviderImpl, kOpenPlacePrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kImportScriptEventResponderImpl, kOpenPlacePrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kImportAndLoadPlaceGunCmdImpl, kOpenPlacePrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kReplaceCmdImpl, kOpenPlacePrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kImportManagerImpl, kOpenPlacePrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kOpenCoreImpl, kOpenPlacePrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kImportCoreImpl, kOpenPlacePrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kImportMgrServiceImpl, kOpenPlacePrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kImportAndPlaceCmdImpl, kOpenPlacePrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kReplaceCmdDataImpl, kOpenPlacePrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kReimportCmdImpl, kOpenPlacePrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kImportResourceCmdDataImpl, kOpenPlacePrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kOpenFileCmdDataImpl, kOpenPlacePrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kLoadPlaceGunCmdDataImpl, kOpenPlacePrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kPlaceBehaviorSignalDataImpl, kOpenPlacePrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kImportSuiteASBImpl, kOpenPlacePrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kImportSuiteLayoutCSBImpl, kOpenPlacePrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kImportSuiteTextCSBImpl, kOpenPlacePrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kImportSuiteDocDefaultCSBImpl, kOpenPlacePrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kImportSuiteXMLCSBImpl, kOpenPlacePrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kImportSuiteTableCSBImpl, kOpenPlacePrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kImportSuiteGalleyCSBImpl, kOpenPlacePrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kEndPlaceCmdImpl, kOpenPlacePrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kPlaceGunDocResponderImpl, kOpenPlacePrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kOpenPlaceCodeConverterProviderImpl, kOpenPlacePrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kSetSnippetImportLocationPrefCmdImpl, kOpenPlacePrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kSnippetImportUsesOriginalLocationImpl, kOpenPlacePrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kSnippetImportLocationPrefCmdDataImpl, kOpenPlacePrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kPlaceSnippetCmdImpl, kOpenPlacePrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kSnippetPlaceBehaviorImpl, kOpenPlacePrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kSnippetBatchPlaceTrackerHelperImpl, kOpenPlacePrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kExportDirectoryPersistImpl, kOpenPlacePrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kExportFileNamePersistImpl, kOpenPlacePrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kImportExportFacadeImpl, kOpenPlacePrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kAllowSpreadChangeImpl, kOpenPlacePrefix + 58) 
DECLARE_PMID(kImplementationIDSpace, kLoadSnippetCmdImpl, kOpenPlacePrefix + 59) 
DECLARE_PMID(kImplementationIDSpace, kTemporaryImportCacheImpl, kOpenPlacePrefix + 60) 
DECLARE_PMID(kImplementationIDSpace, kPlaceCloudAssetUtilsImpl, kOpenPlacePrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kOpenRecoveryOptionsImpl, kOpenPlacePrefix + 62)

// <Widget ID>
DECLARE_PMID(kWidgetIDSpace, kOpeningInCopyGraphicStandAloneAlertID, kOpenPlacePrefix + 98)
DECLARE_PMID(kWidgetIDSpace, kOpeningWithoutInCopyContentAlertID, kOpenPlacePrefix + 99)

// Service IDs
DECLARE_PMID(kServiceIDSpace, kImportProviderService, kOpenPlacePrefix + 1)
DECLARE_PMID(kServiceIDSpace, kOpenProviderService, kOpenPlacePrefix + 2)
DECLARE_PMID(kServiceIDSpace, kImportManagerService, kOpenPlacePrefix + 3)
DECLARE_PMID(kServiceIDSpace, kOpenManagerService, kOpenPlacePrefix + 4)
//gap
DECLARE_PMID(kServiceIDSpace, kBeforeImportSignalResponderService, kOpenPlacePrefix + 6)
DECLARE_PMID(kServiceIDSpace, kAfterImportSignalResponderService, kOpenPlacePrefix + 7)
DECLARE_PMID(kServiceIDSpace, kBeforePlaceSignalResponderService, kOpenPlacePrefix + 8)
DECLARE_PMID(kServiceIDSpace, kAfterPlaceSignalResponderService, kOpenPlacePrefix + 9)
DECLARE_PMID(kServiceIDSpace, kBeforeReplaceSignalResponderService, kOpenPlacePrefix + 10)
DECLARE_PMID(kServiceIDSpace, kAfterReplaceSignalResponderService, kOpenPlacePrefix + 11)

// Error ID
DECLARE_PMID(kErrorIDSpace, kNoFilterFoundError, kOpenPlacePrefix + 1)
DECLARE_PMID(kErrorIDSpace, kImportFailedError, kOpenPlacePrefix + 2)
DECLARE_PMID(kErrorIDSpace, kOpenFailedError, kOpenPlacePrefix + 3)
DECLARE_PMID(kErrorIDSpace, kNoFilterFoundOpenError, kOpenPlacePrefix + 4)
DECLARE_PMID(kErrorIDSpace, kAlreadyOpenError, kOpenPlacePrefix + 5)
DECLARE_PMID(kErrorIDSpace, kFileDoesNotExistError, kOpenPlacePrefix + 6)
DECLARE_PMID(kErrorIDSpace, kCannotOpenFileError, kOpenPlacePrefix + 7)
DECLARE_PMID(kErrorIDSpace, kIncompatibleMediaTypeError, kOpenPlacePrefix + 8)
DECLARE_PMID(kErrorIDSpace, kPDFPresetInstalledEarlyAbort, kOpenPlacePrefix + 9)
DECLARE_PMID(kErrorIDSpace, kFileInaccessibleError, kOpenPlacePrefix + 10)

// Action IDs
// moved to ImportExportUIID.h DECLARE_PMID(kActionIDSpace, kPlaceActionID, kOpenPlacePrefix + 1)
// moved to ImportExportUIID.h DECLARE_PMID(kActionIDSpace, kPlaceSeperatorActionID, kOpenPlacePrefix + 2)

//
//Script Element IDs
//

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kPlaceGunObjectScriptElement,				kOpenPlacePrefix + 10)

//Methods
DECLARE_PMID(kScriptInfoIDSpace, kPlaceMethodScriptElement,					kOpenPlacePrefix + 80)
DECLARE_PMID(kScriptInfoIDSpace, kPlaceOnSpreadMethodScriptElement,			kOpenPlacePrefix + 81)
DECLARE_PMID(kScriptInfoIDSpace, kLoadPlaceGunMethodScriptElement,			kOpenPlacePrefix + 82)
DECLARE_PMID(kScriptInfoIDSpace, kPlaceableFileExtensionsScriptElement,		kOpenPlacePrefix + 83)
DECLARE_PMID(kScriptInfoIDSpace, kPlaceableFileTypesScriptElement,			kOpenPlacePrefix + 84)
DECLARE_PMID(kScriptInfoIDSpace, kPlaceUsingUIMethodScriptElement,			kOpenPlacePrefix + 85)
DECLARE_PMID(kScriptInfoIDSpace, kAbortPlaceGunMethodScriptElement,			kOpenPlacePrefix + 86)
DECLARE_PMID(kScriptInfoIDSpace, kRotatePlaceGunMethodScriptElement,		kOpenPlacePrefix + 87)
DECLARE_PMID(kScriptInfoIDSpace, kPlaceCloudAssetMethodScriptElement,		kOpenPlacePrefix + 88)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kPlaceGunPropertyScriptElement,			kOpenPlacePrefix + 120)
DECLARE_PMID(kScriptInfoIDSpace, kPlaceGunLoadedPropertyScriptElement,		kOpenPlacePrefix + 121)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kRotateDirectionEnumScriptElement,			kOpenPlacePrefix + 180)

//Events
DECLARE_PMID(kScriptInfoIDSpace, kBeforePlaceEventScriptElement,			kOpenPlacePrefix + 220)
DECLARE_PMID(kScriptInfoIDSpace, kAfterPlaceEventScriptElement,				kOpenPlacePrefix + 221)

//GUIDS
// {9C91BB16-AD4D-4196-B8F0-F77FF642B49C}
#define kPlaceGun_CLSID { 0x9c91bb16, 0xad4d, 0x4196, { 0xb8, 0xf0, 0xf7, 0x7f, 0xf6, 0x42, 0xb4, 0x9c } }

enum PlaceScriptIDs
{
	c_PlaceGun			= 'cPGn',
	p_PlaceGun			= 'pPGn',
	p_Loaded			= 'Load',
	e_LoadPlaceGun		= 'LPGn',
	e_AbortPlaceGun		= 'APGn',
	e_BeforePlace		= 'BfPl',
	e_AfterPlace		= 'AfPl',
	en_RotationDirection= 'RotD',
	en_Forward			= 'Forw',
	en_Backward			= 'Bakw',
} ;

//---------------------------------------------------
// InvalHandlerTypeID
//---------------------------------------------------
DECLARE_PMID(kInvalHandlerIDSpace, kPlaceGunInvalHandlerID, kOpenPlacePrefix + 1 )


#endif // __OpenPlaceID__
