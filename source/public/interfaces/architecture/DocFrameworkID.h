//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/DocFrameworkID.h $
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
//========================================================================================

#ifndef __DocFrameworkID__
#define __DocFrameworkID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kDocFrameworkPrefix	 RezLong(0x16300)		// see AdobePrefix.h

// PluginID
#define kDocFrameworkPluginName 	"DocFramework"
DECLARE_PMID(kPlugInIDSpace, kDocFrameworkPluginID, kDocFrameworkPrefix + 1)
DECLARE_PMID(kPlugInIDSpace, kDocumentActionsPluginID, kDocFrameworkPrefix + 2)

//    Rsrc IDs
#define kDocFrameworkStringsRsrcID				3000
#define kDocFrameworkStringsNoTransRsrcID		3100
#define kDocFrameworkErrorStringTableRsrcID		3300

// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kConvertSwatchCmdBoss,						kDocFrameworkPrefix + 1)
DECLARE_PMID(kClassIDSpace, kDocFrameworkConversionBoss,				kDocFrameworkPrefix + 2)
DECLARE_PMID(kClassIDSpace, kPMLockFileBoss,							kDocFrameworkPrefix + 3)
DECLARE_PMID(kClassIDSpace, kDocFrameworkIteratorRegBoss, 				kDocFrameworkPrefix + 4)
DECLARE_PMID(kClassIDSpace, kConversionStreamWriteBoss, 				kDocFrameworkPrefix + 5)
DECLARE_PMID(kClassIDSpace, kDocumentScriptProviderBoss,				kDocFrameworkPrefix + 6)
DECLARE_PMID(kClassIDSpace, kScrapScriptProviderBoss,					kDocFrameworkPrefix + 8)
DECLARE_PMID(kClassIDSpace, kExtractRecentFileThumbnailIdleTaskBoss,	kDocFrameworkPrefix + 9)
DECLARE_PMID(kClassIDSpace, kTrackPluginRefStreamBoss,					kDocFrameworkPrefix + 10)
DECLARE_PMID(kClassIDSpace, kDocumentEventScriptProviderBoss,			kDocFrameworkPrefix + 11)
DECLARE_PMID(kClassIDSpace, kDocumentScriptEventBoss,					kDocFrameworkPrefix + 12)
DECLARE_PMID(kClassIDSpace, kImportExportEventScriptProviderBoss,		kDocFrameworkPrefix + 13)
DECLARE_PMID(kClassIDSpace, kImportExportScriptEventBoss,				kDocFrameworkPrefix + 14)
DECLARE_PMID(kClassIDSpace, kExportProviderSignalMgrBoss,				kDocFrameworkPrefix + 15)
DECLARE_PMID(kClassIDSpace, kDocFrameworkStartupShutdownBoss,			kDocFrameworkPrefix + 16)
DECLARE_PMID(kClassIDSpace, kDocChangesObserverBoss,					kDocFrameworkPrefix + 17)
DECLARE_PMID(kClassIDSpace, kColorDataStandaloneBoss,					kDocFrameworkPrefix + 18)
//gap
DECLARE_PMID(kClassIDSpace, kDocFrameworkErrorStringServiceBoss,		kDocFrameworkPrefix + 21)
DECLARE_PMID(kClassIDSpace, kCustomPtsPerInchOpenDocResponderBoss,		kDocFrameworkPrefix + 22)
DECLARE_PMID(kClassIDSpace, kExportScriptProviderBoss, 					kDocFrameworkPrefix + 23)
DECLARE_PMID(kClassIDSpace, kExportMgrConversionBoss, 					kDocFrameworkPrefix + 24)
DECLARE_PMID(kClassIDSpace, kDocFrameworkPhase2ConversionResponderBoss,	kDocFrameworkPrefix + 25)
DECLARE_PMID(kClassIDSpace, kFileStreamReadLazyBoss,					kDocFrameworkPrefix + 26)
DECLARE_PMID(kClassIDSpace, kFileStreamWriteLazyBoss,					kDocFrameworkPrefix + 27)
DECLARE_PMID(kClassIDSpace, kBlackBoxAddDataCmdBoss,					kDocFrameworkPrefix + 28)
DECLARE_PMID(kClassIDSpace, kBlackBoxRemoveDataCmdBoss,					kDocFrameworkPrefix + 29)
DECLARE_PMID(kClassIDSpace, kTrackPluginsScriptProviderBoss,			kDocFrameworkPrefix + 30)
DECLARE_PMID(kClassIDSpace, kSetLastOutputTimeCmdBoss,					kDocFrameworkPrefix + 31)
DECLARE_PMID(kClassIDSpace, kDocumentScriptEventResponderServiceBoss,	kDocFrameworkPrefix + 32)
DECLARE_PMID(kClassIDSpace, kExportScriptEventResponderServiceBoss,		kDocFrameworkPrefix + 33)
DECLARE_PMID(kClassIDSpace, kOpenedFileInfoOpenDocResponderBoss,		kDocFrameworkPrefix + 34)
DECLARE_PMID(kClassIDSpace, kDocUIDValidatorBoss,						kDocFrameworkPrefix + 35)
DECLARE_PMID(kClassIDSpace, kDocumentScriptObserverBoss,				kDocFrameworkPrefix + 36)
DECLARE_PMID(kClassIDSpace, kDoc_NoUI_FileHandlerBoss,					kDocFrameworkPrefix + 37)

//Watermark Class IDs:
DECLARE_PMID(kClassIDSpace, kWatermarkNewDocResponderBoss,				kDocFrameworkPrefix + 38)
DECLARE_PMID(kClassIDSpace, kWatermarkErrorStringServiceBoss,			kDocFrameworkPrefix + 39)
DECLARE_PMID(kClassIDSpace, kWatermarkScriptProviderBoss,				kDocFrameworkPrefix + 40)
DECLARE_PMID(kClassIDSpace, kWatermarkSetDataCmdBoss,					kDocFrameworkPrefix + 41)
DECLARE_PMID(kClassIDSpace, kWatermarkServiceBoss,						kDocFrameworkPrefix + 42)
DECLARE_PMID(kClassIDSpace, kWatermarkOpenDocResponderBoss,				kDocFrameworkPrefix + 43)

DECLARE_PMID(kClassIDSpace, kFileListSetFileMaxCmdBoss,					kDocFrameworkPrefix + 44)
DECLARE_PMID(kClassIDSpace, kFileListGetNthFileCmdBoss,					kDocFrameworkPrefix + 45)
DECLARE_PMID(kClassIDSpace, kFileListAddFileCmdBoss,					kDocFrameworkPrefix + 46)
DECLARE_PMID(kClassIDSpace, kFileListRemoveFileCmdBoss,					kDocFrameworkPrefix + 47)
DECLARE_PMID(kClassIDSpace, kFileListCleanListCmdBoss,					kDocFrameworkPrefix + 48)
DECLARE_PMID(kClassIDSpace, kFileListSetNthFileThumbnailInfoCmdBoss,	kDocFrameworkPrefix + 49)

// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace,	IID_ICONVERTSWATCHCMDDATA,				kDocFrameworkPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace,	IID_IPMLOCKFILE,						kDocFrameworkPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace,	IID_IPMLOCKFILEFACTORY,					kDocFrameworkPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace,	IID_IPMLOCKFILEDATA,					kDocFrameworkPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace,	IID_IVALIDATOR,							kDocFrameworkPrefix + 5)	// DEBUG ONLY!
DECLARE_PMID(kInterfaceIDSpace,	IID_IDOCSCRIPTUTILS,					kDocFrameworkPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IRECENTFILEINFOLIST,				kDocFrameworkPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace,	IID_IAGMPAINTCONVERTER,                 kDocFrameworkPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCUMENTCOMMANDS,					kDocFrameworkPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCUMENTUIACTIONS,					kDocFrameworkPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IRECENTFILEINFO,					kDocFrameworkPrefix + 11)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_ITRACKPLUGINREFSTREAMDATA,			kDocFrameworkPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace,	IID_IIDDOCUMENTCOMMANDS,				kDocFrameworkPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace,	IID_IICDOCUMENTCOMMANDS,				kDocFrameworkPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_ICREATIONPARENTINGPREF,				kDocFrameworkPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace,	IID_IEXPORTPROVIDERSIGNALDATA,			kDocFrameworkPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace,	IID_IDISPLAYOVERRIDESMGR,               kDocFrameworkPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace,	IID_IDRAWINTERRUPTCONTEXT,              kDocFrameworkPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace,	IID_IFILEDIALOGPATHS,					kDocFrameworkPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_IEXPORTPROVIDER,					kDocFrameworkPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_IOUTPUTPAGES,						kDocFrameworkPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCFILETYPE,						kDocFrameworkPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRIVATESWATCHUTILS,				kDocFrameworkPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_IINCOPYGRAPHICFILE,					kDocFrameworkPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_IBLACKBOXDATA, 						kDocFrameworkPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_IBLACKBOXCOMMANDS,					kDocFrameworkPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_IBLACKBOXCMDDATA,					kDocFrameworkPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_IALREADYEXPORTEDDATA,				kDocFrameworkPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_ILASTOUTPUTTIME,					kDocFrameworkPrefix + 32)
DECLARE_PMID(kInterfaceIDSpace, IID_IOPENEDFILEINFO,					kDocFrameworkPrefix + 33)
#ifdef DEBUG
DECLARE_PMID(kInterfaceIDSpace, IID_IVALIDATORUTILS,					kDocFrameworkPrefix + 34)
DECLARE_PMID(kInterfaceIDSpace, IID_IBADUIDLIST,						kDocFrameworkPrefix + 35)
#endif
DECLARE_PMID(kInterfaceIDSpace, IID_IWATERMARKDATA,						kDocFrameworkPrefix + 36)
DECLARE_PMID(kInterfaceIDSpace, IID_IWATERMARKDATAFACADE,				kDocFrameworkPrefix + 37)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRIVATEDOCUMENTUTILS,			    kDocFrameworkPrefix + 38)

DECLARE_PMID(kInterfaceIDSpace, IID_IRECENTFILELISTFACADE,				kDocFrameworkPrefix + 39)
DECLARE_PMID(kInterfaceIDSpace, IID_ILOGGINGDELAYEDFORDOUBLECLICK,		kDocFrameworkPrefix + 40)
DECLARE_PMID(kInterfaceIDSpace, IID_IRECENTDOCSTYLEINFO,				kDocFrameworkPrefix + 41)
DECLARE_PMID(kInterfaceIDSpace, IID_IFAILEDOPENDOCUMENTIDDATA,          kDocFrameworkPrefix + 42)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCARTIFACTDATA,                   kDocFrameworkPrefix + 43)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOCARTIFACTCHANGE,					kDocFrameworkPrefix + 44)
DECLARE_PMID(kInterfaceIDSpace, IID_IAUTOACTIVATEFONTDATA,              kDocFrameworkPrefix + 45)

// <Widget ID>
DECLARE_PMID(kWidgetIDSpace, kCustomPtsPerInchMismatchAlertID,			kDocFrameworkPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kSpotColorWarningAlertID,					kDocFrameworkPrefix + 2)

// <Implementation ID>
// ImplementationIDs
DECLARE_PMID(kImplementationIDSpace, kConvertSwatchCmdImpl,					kDocFrameworkPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kConvertSwatchCmdDataImpl,				kDocFrameworkPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kPMLockFileImpl,						kDocFrameworkPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kPMLockFileFactoryImpl,				kDocFrameworkPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kPMLockFileDataImpl,					kDocFrameworkPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kDocFrameworkIteratorRegImpl,			kDocFrameworkPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kValidatorServiceImpl,					kDocFrameworkPrefix + 7)	// DEBUG ONLY!
DECLARE_PMID(kImplementationIDSpace, kDocScriptUtilsImpl,					kDocFrameworkPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kDocumentEventScriptProviderImpl,		kDocFrameworkPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kDocumentScriptProviderImpl,			kDocFrameworkPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kDocumentScriptImpl,					kDocFrameworkPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kCustomPtsPerInchOpenDocResponderImpl,	kDocFrameworkPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kLayoutWindowScriptImpl,				kDocFrameworkPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kStoryWindowScriptImpl,				kDocFrameworkPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kWindowScriptImpl,						kDocFrameworkPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kWindowScriptObserverImpl,				kDocFrameworkPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kScrapScriptProviderImpl,				kDocFrameworkPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kAGMPaintConverterImpl,				kDocFrameworkPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kObsoleteSurrogateTableImpl,           kDocFrameworkPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kImportExportEventScriptProviderImpl,	kDocFrameworkPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kDocumentScriptObserverImpl,			kDocFrameworkPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kObsoleteSurrogateSwapCmdImpl,         kDocFrameworkPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kTrackPluginRefStreamImpl,				kDocFrameworkPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kTrackPluginRefStreamDataImpl,			kDocFrameworkPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kRecentFileInfoListImpl,				kDocFrameworkPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kRecentFileInfoImpl,					kDocFrameworkPrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kExtractRecentFileThumbnailIdleTaskImpl, kDocFrameworkPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kDocFrameworkStartupShutdownImpl,		kDocFrameworkPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kDocChangesObserverImpl,				kDocFrameworkPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kDocChangesResponderServiceImpl,		kDocFrameworkPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kDocChangesStartupShutdownImpl,		kDocFrameworkPrefix + 32)
//gap
DECLARE_PMID(kImplementationIDSpace, kExportProviderSignalDataImpl,			kDocFrameworkPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kDisplayOverridesMgrImpl,				kDocFrameworkPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kDrawInterruptContextImpl,				kDocFrameworkPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kFileDialogPathsImpl,					kDocFrameworkPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kDocFrameworkErrorStringServiceImpl,	kDocFrameworkPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kExportScriptProviderImpl,				kDocFrameworkPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kExportServiceImpl,					kDocFrameworkPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kOutputPagesImpl,						kDocFrameworkPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kDocFileTypeImpl,						kDocFrameworkPrefix + 43)	// direct open/save text/rtf file
DECLARE_PMID(kImplementationIDSpace, kDocFrameworkPhase2ConversionImpl,		kDocFrameworkPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kPrivateSwatchUtilsImpl,				kDocFrameworkPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kBlackBoxAddDataCmdImpl,				kDocFrameworkPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kBlackBoxDataImpl,						kDocFrameworkPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kBlackBoxCommandsImpl,					kDocFrameworkPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kBlackBoxRemoveDataCmdImpl,			kDocFrameworkPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kBlackBoxCmdDataImpl,					kDocFrameworkPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kTrackPluginsScriptProviderImpl,		kDocFrameworkPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kJBXResourceTypeServiceImpl,			kDocFrameworkPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kLastOutputTimeImpl,					kDocFrameworkPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kSetLastOutputTimeCmdImpl,				kDocFrameworkPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kDocumentScriptEventServiceProviderImpl,kDocFrameworkPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kDocumentScriptEventResponderImpl,		kDocFrameworkPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kExportScriptEventServiceProviderImpl,	kDocFrameworkPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kExportScriptEventResponderImpl,		kDocFrameworkPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kOpenedFileInfoImpl,					kDocFrameworkPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kOpenedFileInfoOpenDocResponderImpl,	kDocFrameworkPrefix + 60)
#ifdef DEBUG
DECLARE_PMID(kImplementationIDSpace, kValidatorUtilsImpl, kDocFrameworkPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kDocUIDValidatorImpl, kDocFrameworkPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kBadUIDListImpl, kDocFrameworkPrefix + 63)
#endif
DECLARE_PMID(kImplementationIDSpace, kDocFileHandlerFactoryImpl, kDocFrameworkPrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kDoc_NoUI_FileHandlerImpl, kDocFrameworkPrefix + 65)

DECLARE_PMID(kImplementationIDSpace, kWatermarkDataImpl,					kDocFrameworkPrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kWatermarkDataFacadeImpl,				kDocFrameworkPrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kWatermarkDataPersistImpl,				kDocFrameworkPrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kWatermarkNewOpenDocResponderImpl,		kDocFrameworkPrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kWatermarkDrwEvtHandlerImpl,			kDocFrameworkPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kWatermarkDrwEvtSrvcImpl,				kDocFrameworkPrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kWatermarkErrorStringServiceImpl,		kDocFrameworkPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kWatermarkScriptProviderImpl,			kDocFrameworkPrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kWatermarkSetDataCmdImpl,				kDocFrameworkPrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kPrivateDocumentUtilsImpl,				kDocFrameworkPrefix + 75)

DECLARE_PMID(kImplementationIDSpace, kFileListSetFileMaxCmdImpl,			kDocFrameworkPrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kFileListGetNthFileCmdImpl,			kDocFrameworkPrefix + 77)
DECLARE_PMID(kImplementationIDSpace, kFileListAddFileCmdImpl,				kDocFrameworkPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kFileListRemoveFileCmdImpl,			kDocFrameworkPrefix + 79)
DECLARE_PMID(kImplementationIDSpace, kRecentFileListFacadeImpl,	            kDocFrameworkPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kFileListCleanListCmdImpl,	            kDocFrameworkPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kFileListSetNthFileThumbnailInfoCmdImpl,	kDocFrameworkPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kBeforeExportSignalResponderServiceImpl,	kDocFrameworkPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kAfterExportSignalResponderServiceImpl,	kDocFrameworkPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kFailedExportSignalResponderServiceImpl,	kDocFrameworkPrefix + 85)
DECLARE_PMID(kImplementationIDSpace, kRecentDocStyleInfoImpl,					kDocFrameworkPrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kLastUsedFormatStringAliasForTextImpl,     kDocFrameworkPrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kFailedOpenDocumentIdImpl,                 kDocFrameworkPrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kDocArtifactDataImpl,                      kDocFrameworkPrefix + 89)
DECLARE_PMID(kImplementationIDSpace, kAutoActivateFontDataImpl,                 kDocFrameworkPrefix + 90)

// <Message ID>


// <Service ID>
// Service IDs

DECLARE_PMID(kServiceIDSpace, kService_Validate,						kDocFrameworkPrefix + 1)	// DEBUG ONLY!

DECLARE_PMID(kServiceIDSpace, kDocChangesSignalResponderService,		kDocFrameworkPrefix + 2)
DECLARE_PMID(kServiceIDSpace, kExportProviderService, 					kDocFrameworkPrefix + 3)
DECLARE_PMID(kServiceIDSpace, kJBXResourceTypeService,					kDocFrameworkPrefix + 4)
DECLARE_PMID(kServiceIDSpace, kBeforeExportSignalResponderService,		kDocFrameworkPrefix + 5)
DECLARE_PMID(kServiceIDSpace, kAfterExportSignalResponderService,		kDocFrameworkPrefix + 6)
DECLARE_PMID(kServiceIDSpace, kFailedExportSignalResponderService,		kDocFrameworkPrefix + 7)

// <Error ID>
// Error Codes
DECLARE_PMID(kErrorIDSpace, kCannotCreateLockFileError,					kDocFrameworkPrefix + 1)	//No error string; internal use only
DECLARE_PMID(kErrorIDSpace, kTagInfoNotFoundInContentManager,			kDocFrameworkPrefix + 2)	//No error string; internal use only
DECLARE_PMID(kErrorIDSpace, kPluginNotFoundInContentManager,			kDocFrameworkPrefix + 3)	//No error string; internal use only
DECLARE_PMID(kErrorIDSpace, kNoDocumentOpenError,						kDocFrameworkPrefix + 4)
DECLARE_PMID(kErrorIDSpace, kCantCloseLastWinError,						kDocFrameworkPrefix + 5)
DECLARE_PMID(kErrorIDSpace, kNoWindowOpenError,							kDocFrameworkPrefix + 6)
DECLARE_PMID(kErrorIDSpace, kUntitledNoPathError,						kDocFrameworkPrefix + 7)
DECLARE_PMID(kErrorIDSpace, kUntitledNoFullNameError,					kDocFrameworkPrefix + 8)
DECLARE_PMID(kErrorIDSpace, kCantEditColorPropertyError,				kDocFrameworkPrefix + 9)
DECLARE_PMID(kErrorIDSpace, kCantDuplicateColorError,					kDocFrameworkPrefix + 10)
DECLARE_PMID(kErrorIDSpace, kScriptingCannotCopyCut,					kDocFrameworkPrefix + 11)
DECLARE_PMID(kErrorIDSpace, kScriptInvalidConfiguration,				kDocFrameworkPrefix + 12)
DECLARE_PMID(kErrorIDSpace, kNoScriptIsActiveError,						kDocFrameworkPrefix + 13)
DECLARE_PMID(kErrorIDSpace, kSetRegistrationInkTypeError,				kDocFrameworkPrefix + 14)
DECLARE_PMID(kErrorIDSpace, kClipboardIsInaccessibleError,				kDocFrameworkPrefix + 15)

// NOTE:  The offset is used to find the corresponding error string
DECLARE_PMID(kErrorIDSpace, kNoSwatchNameError, 						kDocFrameworkPrefix + 16)
DECLARE_PMID(kErrorIDSpace, kNoUniqueSwatchNameError, 					kDocFrameworkPrefix + 17)
DECLARE_PMID(kErrorIDSpace, kCantDeleteColorError, 						kDocFrameworkPrefix + 18)
DECLARE_PMID(kErrorIDSpace, kColorNameExistsError,						kDocFrameworkPrefix + 19)
DECLARE_PMID(kErrorIDSpace, kInvalidColorValueError, 					kDocFrameworkPrefix + 20)
DECLARE_PMID(kErrorIDSpace, kIncorrectNumberColorValueError, 			kDocFrameworkPrefix + 21)
DECLARE_PMID(kErrorIDSpace, kNoUniqueTintError, 						kDocFrameworkPrefix + 22)
DECLARE_PMID(kErrorIDSpace, kCreateSpotCopyError, 						kDocFrameworkPrefix + 23)
DECLARE_PMID(kErrorIDSpace, kReplaceSpotError, 							kDocFrameworkPrefix + 24)
DECLARE_PMID(kErrorIDSpace, kDuplicateSwatchExistsError, 				kDocFrameworkPrefix + 25)
DECLARE_PMID(kErrorIDSpace, kSameNameSwatchExistsError, 				kDocFrameworkPrefix + 26)
DECLARE_PMID(kErrorIDSpace, kCantEditColorError, 						kDocFrameworkPrefix + 27)
DECLARE_PMID(kErrorIDSpace, kCantEditColorWithLibGradientError, 		kDocFrameworkPrefix + 28)
DECLARE_PMID(kErrorIDSpace, kCantEditTintWithLibTintError, 				kDocFrameworkPrefix + 29)
DECLARE_PMID(kErrorIDSpace, kDeleteInkAliasError, 						kDocFrameworkPrefix + 30)
DECLARE_PMID(kErrorIDSpace, kChangeSpotInkAliasError, 					kDocFrameworkPrefix + 31)
DECLARE_PMID(kErrorIDSpace, kPantoneOldNewOverlapError,					kDocFrameworkPrefix + 32)
DECLARE_PMID(kErrorIDSpace, kCantMergeSwatchError, 						kDocFrameworkPrefix + 33)
DECLARE_PMID(kErrorIDSpace, kCantEditBaseWithLibTintError, 				kDocFrameworkPrefix + 34)
DECLARE_PMID(kErrorIDSpace, kReservedSwatchNameError, 					kDocFrameworkPrefix + 35)
DECLARE_PMID(kErrorIDSpace, kMixedInkSwatchCreationError, 				kDocFrameworkPrefix + 36)
DECLARE_PMID(kErrorIDSpace, kExceedMaxMixedInkSwatchesInGroupError, 	kDocFrameworkPrefix + 37)
DECLARE_PMID(kErrorIDSpace, kMixedInkParentMustHaveTwoInksError, 		kDocFrameworkPrefix + 38)
DECLARE_PMID(kErrorIDSpace, kMixedInkParentProcessInksOnlyError, 		kDocFrameworkPrefix + 39)
DECLARE_PMID(kErrorIDSpace, kMultiSwatchLibSelectionError, 				kDocFrameworkPrefix + 40)
DECLARE_PMID(kErrorIDSpace, kMultiSameSwatchNameError, 					kDocFrameworkPrefix + 41)
DECLARE_PMID(kErrorIDSpace, kMultiPantoneOldNewOverlapError, 			kDocFrameworkPrefix + 42)
DECLARE_PMID(kErrorIDSpace, kMultiSameTintSwatchNameError, 				kDocFrameworkPrefix + 43)
DECLARE_PMID(kErrorIDSpace, kExceedMaxInksInInkGroupError, 				kDocFrameworkPrefix + 44)
DECLARE_PMID(kErrorIDSpace, kDeleteSpotInMixedInkError, 				kDocFrameworkPrefix + 45)
DECLARE_PMID(kErrorIDSpace, kDeleteSpotInMixedInkDestructError, 		kDocFrameworkPrefix + 46)
DECLARE_PMID(kErrorIDSpace, kCantEditSpotWithMixedInkError, 			kDocFrameworkPrefix + 47)
DECLARE_PMID(kErrorIDSpace, kCantEditTintWithMixedInkError, 			kDocFrameworkPrefix + 48)
DECLARE_PMID(kErrorIDSpace, kCantDuplicateSwatchError, 					kDocFrameworkPrefix + 49)
DECLARE_PMID(kErrorIDSpace, kLoadSwatchesActiveDocError, 				kDocFrameworkPrefix + 50)
DECLARE_PMID(kErrorIDSpace, kLoadSwatchesOpenDocError, 					kDocFrameworkPrefix + 51)
DECLARE_PMID(kErrorIDSpace, kLoadSwatchesNotSwatchbookError, 			kDocFrameworkPrefix + 52)
DECLARE_PMID(kErrorIDSpace, kSaveSwatchesError, 						kDocFrameworkPrefix + 53)
DECLARE_PMID(kErrorIDSpace, kInvalidExportFormatForObjectError, 		kDocFrameworkPrefix + 54)
DECLARE_PMID(kErrorIDSpace, kScriptCantPasteError, 						kDocFrameworkPrefix + 55)
DECLARE_PMID(kErrorIDSpace, kInvalidSwatchNameErr,						kDocFrameworkPrefix + 56)
DECLARE_PMID(kErrorIDSpace, kUnsavedNoPathError,						kDocFrameworkPrefix + 57)
DECLARE_PMID(kErrorIDSpace, kUnsavedNoFullNameError,					kDocFrameworkPrefix + 58)
DECLARE_PMID(kErrorIDSpace, kCantCloseDocumentWithActiveEventsError,	kDocFrameworkPrefix + 59)
DECLARE_PMID(kErrorIDSpace, kCantSaveDocumentWithOpenTransactionError,	kDocFrameworkPrefix + 60)
DECLARE_PMID(kErrorIDSpace, kCantSaveDocumentInUseByBGTasksError,		kDocFrameworkPrefix + 61)
DECLARE_PMID(kErrorIDSpace, kCantSaveAsDocumentInUseByBGTasksError,		kDocFrameworkPrefix + 62)
DECLARE_PMID(kErrorIDSpace, kCantSaveACopyDocumentInUseByBGTasksError,	kDocFrameworkPrefix + 63)
DECLARE_PMID(kErrorIDSpace, kCantRevertDocumentInUseByBGTasksError,		kDocFrameworkPrefix + 64)
DECLARE_PMID(kErrorIDSpace, kCantCloseDocumentInUseByBGTasksError,		kDocFrameworkPrefix + 65)
DECLARE_PMID(kErrorIDSpace, kCantQuitWithBGTasksError,					kDocFrameworkPrefix + 66)
DECLARE_PMID(kErrorIDSpace, kFileInUseByBGTasksError,					kDocFrameworkPrefix + 67)
DECLARE_PMID(kErrorIDSpace, kAsynchronousExportUnsupportedFormatError,	kDocFrameworkPrefix + 68)
DECLARE_PMID(kErrorIDSpace, kCantDeleteColorGroupError, 				kDocFrameworkPrefix + 69)
DECLARE_PMID(kErrorIDSpace, kCantUngroupColorGroupError, 				kDocFrameworkPrefix + 70)
DECLARE_PMID(kErrorIDSpace, kNoUniqueColorGroupNameError, 				kDocFrameworkPrefix + 71)
DECLARE_PMID(kErrorIDSpace, kColorGroupNameBlankError, 					kDocFrameworkPrefix + 72)
DECLARE_PMID(kErrorIDSpace, kUnsupportedSwatchesInColorGroupError, 		kDocFrameworkPrefix + 73)
DECLARE_PMID(kErrorIDSpace, kPsoitiveValueExpectedError,				kDocFrameworkPrefix + 74)
DECLARE_PMID(kErrorIDSpace, kCantExportSelectedPageItemsError,          kDocFrameworkPrefix + 75)
DECLARE_PMID(kErrorIDSpace, kCantSetDocumentNameError,					kDocFrameworkPrefix + 76)
// <Ignore>


// <Global ID>
// ActionIDs

// <Performance Metric IDs>
DECLARE_PMID(kPerformanceMetricIDSpace,	kNumberOpenDocsPerfID,			kDocFrameworkPrefix + 1)
DECLARE_PMID(kPerformanceMetricIDSpace,	kMaxNumberOpenDocsPerfID,		kDocFrameworkPrefix + 2)

//
//Script Element IDs
//
//Events
DECLARE_PMID(kScriptInfoIDSpace, kBeforeNewDocumentEventScriptElement,		kDocFrameworkPrefix + 0)
DECLARE_PMID(kScriptInfoIDSpace, kAfterNewDocumentEventScriptElement,		kDocFrameworkPrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kBeforeOpenDocumentEventScriptElement,		kDocFrameworkPrefix + 2)
DECLARE_PMID(kScriptInfoIDSpace, kAfterOpenDocumentEventScriptElement,		kDocFrameworkPrefix + 3)
DECLARE_PMID(kScriptInfoIDSpace, kBeforeSaveDocumentEventScriptElement,		kDocFrameworkPrefix + 4)
DECLARE_PMID(kScriptInfoIDSpace, kAfterSaveDocumentEventScriptElement,		kDocFrameworkPrefix + 5)
DECLARE_PMID(kScriptInfoIDSpace, kBeforeSaveAsDocumentEventScriptElement,	kDocFrameworkPrefix + 6)
DECLARE_PMID(kScriptInfoIDSpace, kAfterSaveAsDocumentEventScriptElement,	kDocFrameworkPrefix + 7)
DECLARE_PMID(kScriptInfoIDSpace, kBeforeSaveACopyDocumentEventScriptElement,kDocFrameworkPrefix + 8)
DECLARE_PMID(kScriptInfoIDSpace, kAfterSaveACopyDocumentEventScriptElement,	kDocFrameworkPrefix + 9)
DECLARE_PMID(kScriptInfoIDSpace, kBeforeRevertDocumentEventScriptElement,	kDocFrameworkPrefix + 10)
DECLARE_PMID(kScriptInfoIDSpace, kAfterRevertDocumentEventScriptElement,	kDocFrameworkPrefix + 11)
DECLARE_PMID(kScriptInfoIDSpace, kBeforeCloseDocumentEventScriptElement,	kDocFrameworkPrefix + 12)
DECLARE_PMID(kScriptInfoIDSpace, kAfterCloseDocumentEventScriptElement,		kDocFrameworkPrefix + 13)
DECLARE_PMID(kScriptInfoIDSpace, kBeforeExportEventScriptElement,			kDocFrameworkPrefix + 14)
DECLARE_PMID(kScriptInfoIDSpace, kAfterExportEventScriptElement,			kDocFrameworkPrefix + 15)
DECLARE_PMID(kScriptInfoIDSpace, kBeforeImportEventScriptElement,			kDocFrameworkPrefix + 16)
DECLARE_PMID(kScriptInfoIDSpace, kAfterImportEventScriptElement,			kDocFrameworkPrefix + 17)
DECLARE_PMID(kScriptInfoIDSpace, kFailedExportEventScriptElement,			kDocFrameworkPrefix + 18)

//Suites
DECLARE_PMID(kScriptInfoIDSpace, kColorSuiteScriptElement,					kDocFrameworkPrefix + 22)

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kDocumentObjectScriptElement,				kDocFrameworkPrefix + 40)
DECLARE_PMID(kScriptInfoIDSpace, kWindowObjectScriptElement,				kDocFrameworkPrefix + 41)
DECLARE_PMID(kScriptInfoIDSpace, kSwatchObjectScriptElement,				kDocFrameworkPrefix + 42)
DECLARE_PMID(kScriptInfoIDSpace, kColorObjectScriptElement,					kDocFrameworkPrefix + 43)
DECLARE_PMID(kScriptInfoIDSpace, kTintObjectScriptElement,					kDocFrameworkPrefix + 44)
DECLARE_PMID(kScriptInfoIDSpace, kLayoutWindowObjectScriptElement,			kDocFrameworkPrefix + 45)
DECLARE_PMID(kScriptInfoIDSpace, kStoryWindowObjectScriptElement,			kDocFrameworkPrefix + 46)
DECLARE_PMID(kScriptInfoIDSpace, kDocumentEventObjectScriptElement,			kDocFrameworkPrefix + 47)
DECLARE_PMID(kScriptInfoIDSpace, kImportExportEventObjectScriptElement,		kDocFrameworkPrefix + 48)
DECLARE_PMID(kScriptInfoIDSpace, kBringWindowToFrontMethodScriptElement,		kDocFrameworkPrefix + 49)
DECLARE_PMID(kScriptInfoIDSpace, kColorGroupObjectScriptElement,				kDocFrameworkPrefix + 50)
DECLARE_PMID(kScriptInfoIDSpace, kColorGroupMemberObjectScriptElement,				kDocFrameworkPrefix + 51)
DECLARE_PMID(kScriptInfoIDSpace, kUngroupColorGroupMethodScriptElement,				kDocFrameworkPrefix + 52)
DECLARE_PMID(kScriptInfoIDSpace, kAddColorGroupMethodScriptElement,				kDocFrameworkPrefix + 53)

//Methods
DECLARE_PMID(kScriptInfoIDSpace, kCreateDocumentMethodScriptElement,			kDocFrameworkPrefix + 82)
DECLARE_PMID(kScriptInfoIDSpace, kCloseWithSaveMethodScriptElement,			kDocFrameworkPrefix + 83)
DECLARE_PMID(kScriptInfoIDSpace, kSaveDocumentMethodScriptElement,			kDocFrameworkPrefix + 84)
DECLARE_PMID(kScriptInfoIDSpace, kSaveACopyDocumentMethodScriptElement,		kDocFrameworkPrefix + 85)
DECLARE_PMID(kScriptInfoIDSpace, kGetUntitledDocCountMethodScriptElement,	kDocFrameworkPrefix + 86)
DECLARE_PMID(kScriptInfoIDSpace, kSetUntitledDocCountMethodScriptElement,	kDocFrameworkPrefix + 87)



//gap
DECLARE_PMID(kScriptInfoIDSpace, kZoomToMethodScriptElement,					kDocFrameworkPrefix + 89)
DECLARE_PMID(kScriptInfoIDSpace, kMaximizeMethodScriptElement,				kDocFrameworkPrefix + 90)
DECLARE_PMID(kScriptInfoIDSpace, kMinimizeMethodScriptElement,				kDocFrameworkPrefix + 91)
DECLARE_PMID(kScriptInfoIDSpace, kRestoreMethodScriptElement,				kDocFrameworkPrefix + 92)
//gap
DECLARE_PMID(kScriptInfoIDSpace, kCutMethodScriptElement,					kDocFrameworkPrefix + 94)
DECLARE_PMID(kScriptInfoIDSpace, kCopyMethodScriptElement,					kDocFrameworkPrefix + 95)
DECLARE_PMID(kScriptInfoIDSpace, kPasteMethodScriptElement,					kDocFrameworkPrefix + 96)
DECLARE_PMID(kScriptInfoIDSpace, kPasteIntoMethodScriptElement,				kDocFrameworkPrefix + 97)
DECLARE_PMID(kScriptInfoIDSpace, kDeleteSwatchMethodScriptElement,			kDocFrameworkPrefix + 98)
DECLARE_PMID(kScriptInfoIDSpace, kMergeSwatchMethodScriptElement,			kDocFrameworkPrefix + 99)
DECLARE_PMID(kScriptInfoIDSpace, kCreateTintMethodScriptElement,				kDocFrameworkPrefix + 100)
DECLARE_PMID(kScriptInfoIDSpace, kPasteInPlaceMethodScriptElement,			kDocFrameworkPrefix + 101)
DECLARE_PMID(kScriptInfoIDSpace, kPasteUnformattedMethodScriptElement,		kDocFrameworkPrefix + 102)
DECLARE_PMID(kScriptInfoIDSpace, kTrackPluginsMethodScriptElement,			kDocFrameworkPrefix + 103)
DECLARE_PMID(kScriptInfoIDSpace, kAddColorGroupMemberMethodScriptElement,	kDocFrameworkPrefix + 104)
DECLARE_PMID(kScriptInfoIDSpace, kColorTransformMethodScriptElement,		kDocFrameworkPrefix + 105)

DECLARE_PMID(kScriptInfoIDSpace, kExportPageItemsSelectionToSnippetMethodScriptElement, kDocFrameworkPrefix + 106)
DECLARE_PMID(kScriptInfoIDSpace, kExportPageItemsToSnippetMethodScriptElement, kDocFrameworkPrefix + 107)
//Properties
DECLARE_PMID(kScriptInfoIDSpace, kModifiedPropertyScriptElement,			kDocFrameworkPrefix + 164)
DECLARE_PMID(kScriptInfoIDSpace, kSavedPropertyScriptElement,				kDocFrameworkPrefix + 165)
DECLARE_PMID(kScriptInfoIDSpace, kZeroPointPropertyScriptElement,			kDocFrameworkPrefix + 166)
DECLARE_PMID(kScriptInfoIDSpace, kIncludePreviewPropertyScriptElement,		kDocFrameworkPrefix + 167)
DECLARE_PMID(kScriptInfoIDSpace, kZoomPropertyScriptElement,				kDocFrameworkPrefix + 168)
DECLARE_PMID(kScriptInfoIDSpace, kWindowBoundsPropertyScriptElement,		kDocFrameworkPrefix + 169)
DECLARE_PMID(kScriptInfoIDSpace, kActiveLayerPropertyScriptElement,			kDocFrameworkPrefix + 170)
DECLARE_PMID(kScriptInfoIDSpace, kActiveSpreadPropertyScriptElement,		kDocFrameworkPrefix + 171)
DECLARE_PMID(kScriptInfoIDSpace, kViewDisplaySettingPropertyScriptElement,	kDocFrameworkPrefix + 172)
DECLARE_PMID(kScriptInfoIDSpace, kReferencePointPropertyScriptElement,		kDocFrameworkPrefix + 173)
DECLARE_PMID(kScriptInfoIDSpace, kUnusedSwatchesPropertyScriptElement,		kDocFrameworkPrefix + 174)
DECLARE_PMID(kScriptInfoIDSpace, kColorModelPropertyScriptElement,			kDocFrameworkPrefix + 175)
DECLARE_PMID(kScriptInfoIDSpace, kColorSpacePropertyScriptElement,			kDocFrameworkPrefix + 176)
DECLARE_PMID(kScriptInfoIDSpace, kColorValuePropertyScriptElement,			kDocFrameworkPrefix + 177)
DECLARE_PMID(kScriptInfoIDSpace, kTintValuePropertyScriptElement,			kDocFrameworkPrefix + 178)
DECLARE_PMID(kScriptInfoIDSpace, kActivePagePropertyScriptElement,			kDocFrameworkPrefix + 179)
DECLARE_PMID(kScriptInfoIDSpace, kBaseColorPropertyScriptElement,			kDocFrameworkPrefix + 180)
DECLARE_PMID(kScriptInfoIDSpace, kColorOverridePropertyScriptElement,		kDocFrameworkPrefix + 181)
DECLARE_PMID(kScriptInfoIDSpace, kColorEditablePropertyScriptElement,		kDocFrameworkPrefix + 182)
DECLARE_PMID(kScriptInfoIDSpace, kColorRemovablePropertyScriptElement,		kDocFrameworkPrefix + 183)
DECLARE_PMID(kScriptInfoIDSpace, kViewTabPropertyScriptElement,				kDocFrameworkPrefix + 184)
DECLARE_PMID(kScriptInfoIDSpace, kColorVisiblePropertyScriptElement,		kDocFrameworkPrefix + 185)
DECLARE_PMID(kScriptInfoIDSpace, kBaseGroupPropertyScriptElement,			kDocFrameworkPrefix + 186)
DECLARE_PMID(kScriptInfoIDSpace, kScreenModeModePropertyScriptElement,		kDocFrameworkPrefix + 187)
DECLARE_PMID(kScriptInfoIDSpace, kConvertedPropertyScriptElement,			kDocFrameworkPrefix + 188)
DECLARE_PMID(kScriptInfoIDSpace, kRecoveredPropertyScriptElement,			kDocFrameworkPrefix + 189)
DECLARE_PMID(kScriptInfoIDSpace, kReadOnlyPropertyScriptElement,			kDocFrameworkPrefix + 190)
DECLARE_PMID(kScriptInfoIDSpace, kMissingPluginsPropertyScriptElement,		kDocFrameworkPrefix + 191)
DECLARE_PMID(kScriptInfoIDSpace, kImportExportFormatPropertyScriptElement,	kDocFrameworkPrefix + 192)

DECLARE_PMID(kScriptInfoIDSpace, kWatermarkPropertyScriptElement,				kDocFrameworkPrefix + 193)
DECLARE_PMID(kScriptInfoIDSpace, kWatermarkVisibilityPropertyScriptElement,		kDocFrameworkPrefix + 194)
DECLARE_PMID(kScriptInfoIDSpace, kWatermarkDoPrintPropertyScriptElement,		kDocFrameworkPrefix + 195)
DECLARE_PMID(kScriptInfoIDSpace, kWatermarkTextPropertyScriptElement,			kDocFrameworkPrefix + 196)
DECLARE_PMID(kScriptInfoIDSpace, kWatermarkFontPointSizePropertyScriptElement,	kDocFrameworkPrefix + 197)
DECLARE_PMID(kScriptInfoIDSpace, kWatermarkFontColorPropertyScriptElement,		kDocFrameworkPrefix + 198)
DECLARE_PMID(kScriptInfoIDSpace, kWatermarkRotationPropertyScriptElement,		kDocFrameworkPrefix + 199)
DECLARE_PMID(kScriptInfoIDSpace, kWatermarkHorzPositionPropertyScriptElement,	kDocFrameworkPrefix + 200)
DECLARE_PMID(kScriptInfoIDSpace, kWatermarkHorzOffsetPropertyScriptElement,		kDocFrameworkPrefix + 201)
DECLARE_PMID(kScriptInfoIDSpace, kWatermarkVertPositionPropertyScriptElement,	kDocFrameworkPrefix + 202)
DECLARE_PMID(kScriptInfoIDSpace, kWatermarkVertOffsetPropertyScriptElement,		kDocFrameworkPrefix + 203)
DECLARE_PMID(kScriptInfoIDSpace, kWatermarkPrefObjectScriptElement,				kDocFrameworkPrefix + 204)
DECLARE_PMID(kScriptInfoIDSpace, kWatermarkPrefObjectPropertyScriptElement,		kDocFrameworkPrefix + 205)
DECLARE_PMID(kScriptInfoIDSpace, kWatermarkOpacityPropertyScriptElement,		kDocFrameworkPrefix + 206)
DECLARE_PMID(kScriptInfoIDSpace, kWatermarkFontFamilyPropertyScriptElement,		kDocFrameworkPrefix + 207)
DECLARE_PMID(kScriptInfoIDSpace, kWatermarkFontStylePropertyScriptElement,		kDocFrameworkPrefix + 208)
DECLARE_PMID(kScriptInfoIDSpace, kWatermarkDrawInBackPropertyScriptElement,		kDocFrameworkPrefix + 209)
DECLARE_PMID(kScriptInfoIDSpace, kParentColorGroupPropertyScriptElement,		kDocFrameworkPrefix + 210)
DECLARE_PMID(kScriptInfoIDSpace, kSwatchItemRefScriptElement,					kDocFrameworkPrefix + 211)
DECLARE_PMID(kScriptInfoIDSpace, kIsRootColorGroupScriptElement,				kDocFrameworkPrefix + 212)
DECLARE_PMID(kScriptInfoIDSpace, kUntitledDocumentCountPropertyScriptElement,			kDocFrameworkPrefix + 213)

//Enums
DECLARE_PMID(kScriptInfoIDSpace, kSaveOptionsEnumScriptElement,				kDocFrameworkPrefix + 220)
DECLARE_PMID(kScriptInfoIDSpace, kZoomOptionEnumScriptElement,				kDocFrameworkPrefix + 221)
DECLARE_PMID(kScriptInfoIDSpace, kViewDisplaySettingEnumScriptElement,		kDocFrameworkPrefix + 222)
DECLARE_PMID(kScriptInfoIDSpace, kAnchorPointEnumScriptElement,				kDocFrameworkPrefix + 223)
DECLARE_PMID(kScriptInfoIDSpace, kColorModelEnumScriptElement,				kDocFrameworkPrefix + 224)
DECLARE_PMID(kScriptInfoIDSpace, kColorSpaceEnumScriptElement,				kDocFrameworkPrefix + 225)
DECLARE_PMID(kScriptInfoIDSpace, kColorOverrideEnumScriptElement,			kDocFrameworkPrefix + 226)
DECLARE_PMID(kScriptInfoIDSpace, kViewTabEnumScriptElement,					kDocFrameworkPrefix + 227)

DECLARE_PMID(kScriptInfoIDSpace, kOverprintBlackPropertyScriptElement,		kDocFrameworkPrefix + 228)

DECLARE_PMID(kScriptInfoIDSpace, kSaveFileTypeEnumScriptElement,			kDocFrameworkPrefix + 229)
DECLARE_PMID(kScriptInfoIDSpace, kLoadSwatchesMethodScriptElement,			kDocFrameworkPrefix + 230)
DECLARE_PMID(kScriptInfoIDSpace, kSaveSwatchesMethodScriptElement,			kDocFrameworkPrefix + 231)
DECLARE_PMID(kScriptInfoIDSpace, kScreenModeOptionEnumScriptElement,		kDocFrameworkPrefix + 232)
DECLARE_PMID(kScriptInfoIDSpace, kWatermarkVertPositionEnumElement,			kDocFrameworkPrefix + 233)
DECLARE_PMID(kScriptInfoIDSpace, kWatermarkHorzPositionEnumElement,			kDocFrameworkPrefix + 234)

DECLARE_PMID(kScriptInfoIDSpace, kINXMatchPropertyColorGroupMetadataScriptElement,	kDocFrameworkPrefix + 235)

DECLARE_PMID(kScriptInfoIDSpace, kConvertToHSBPropertyScriptElement,            kDocFrameworkPrefix + 236)

// moved from now defunct ExportManager plugin
#define kOldExportManagerPrefix	 RezLong(0x7800)
DECLARE_PMID(kScriptInfoIDSpace, kExportMethodScriptElement, kOldExportManagerPrefix + 80)
DECLARE_PMID(kScriptInfoIDSpace, kExportWithGridsMethodScriptElement, kOldExportManagerPrefix + 81)
DECLARE_PMID(kScriptInfoIDSpace, kExportFormatEnumScriptElement, kOldExportManagerPrefix + 200)
DECLARE_PMID(kScriptInfoIDSpace, kAsynchronousExportMethodScriptElement, kOldExportManagerPrefix + 82)
DECLARE_PMID(kScriptInfoIDSpace, kAsynchronousExportWithGridsMethodScriptElement, kOldExportManagerPrefix + 83)

//GUIDS
// {1A5E8DB4-3443-11d1-803C-0060B03C02E4}
#define kDocument_CLSID { 0x1a5e8db4, 0x3443, 0x11d1, { 0x80, 0x3c, 0x0, 0x60, 0xb0, 0x3c, 0x2, 0xe4 } }
// {1A5E8DB5-3443-11d1-803C-0060B03C02E4}
#define kDocuments_CLSID { 0x1a5e8db5, 0x3443, 0x11d1, { 0x80, 0x3c, 0x0, 0x60, 0xb0, 0x3c, 0x2, 0xe4 } }
// {1A5E8DB6-3443-11d1-803C-0060B03C02E4}
#define kWindow_CLSID { 0x1a5e8db6, 0x3443, 0x11d1, { 0x80, 0x3c, 0x0, 0x60, 0xb0, 0x3c, 0x2, 0xe4 } }
// {1A5E8DB7-3443-11d1-803C-0060B03C02E4}
#define kWindows_CLSID { 0x1a5e8db7, 0x3443, 0x11d1, { 0x80, 0x3c, 0x0, 0x60, 0xb0, 0x3c, 0x2, 0xe4 } }
// {240D537B-9336-4501-99A2-14812D15A9D3}
#define kLayoutWindow_CLSID { 0x240d537b, 0x9336, 0x4501, { 0x99, 0xa2, 0x14, 0x81, 0x2d, 0x15, 0xa9, 0xd3 } }
// {D15B28BF-5610-4ee3-A5B4-B4E2133BFC0B}
#define kLayoutWindows_CLSID { 0xd15b28bf, 0x5610, 0x4ee3, { 0xa5, 0xb4, 0xb4, 0xe2, 0x13, 0x3b, 0xfc, 0xb } }
// {1C1923C1-E259-4a36-9C1F-BDF5AA1E1F86}
#define kStoryWindow_CLSID { 0x1c1923c1, 0xe259, 0x4a36, { 0x9c, 0x1f, 0xbd, 0xf5, 0xaa, 0x1e, 0x1f, 0x86 } }
// {AA226D3C-0BA4-4248-9DE1-F603131AF465}
#define kStoryWindows_CLSID { 0xaa226d3c, 0xba4, 0x4248, { 0x9d, 0xe1, 0xf6, 0x3, 0x13, 0x1a, 0xf4, 0x65 } }
// {A373654F-4F5C-11d2-AB07-00C04FA349C7}
#define kSwatch_CLSID { 0xa373654f, 0x4f5c, 0x11d2, { 0xab, 0x7, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {A3736550-4F5C-11d2-AB07-00C04FA349C7}
#define kSwatches_CLSID { 0xa3736550, 0x4f5c, 0x11d2, { 0xab, 0x7, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {2256FBE8-5584-11d1-804A-0060B03C02E4}
#define kColor_CLSID { 0x2256fbe8, 0x5584, 0x11d1, { 0x80, 0x4a, 0x0, 0x60, 0xb0, 0x3c, 0x2, 0xe4 } }
// {2256FBE9-5584-11d1-804A-0060B03C02E4}
#define kColors_CLSID { 0x2256fbe9, 0x5584, 0x11d1, { 0x80, 0x4a, 0x0, 0x60, 0xb0, 0x3c, 0x2, 0xe4 } }
// {A3736551-4F5C-11d2-AB07-00C04FA349C7}
#define kGradient_CLSID { 0xa3736551, 0x4f5c, 0x11d2, { 0xab, 0x7, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {385ed624-252a-4fb5-9cb2-b3a99eb80823}
#define kAGMBlackBox_CLSID { 0x385ed624, 0x252a, 0x4fb5, {0x9c, 0xb2, 0xb3, 0xa9, 0x9e, 0xb8, 0x08, 0x23} }
// {6e3baa1f-a817-4fab-8c20-2ef5e6635597}
#define kAGMBlackBoxes_CLSID { 0x6e3baa1f, 0xa817, 0x4fab, {0x8c, 0x20, 0x2e, 0xf5, 0xe6, 0x63, 0x55, 0x97} }
// {A3736552-4F5C-11d2-AB07-00C04FA349C7}
#define kGradients_CLSID { 0xa3736552, 0x4f5c, 0x11d2, { 0xab, 0x7, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {496F0BD4-7834-11d2-AAF0-00C04FA37726}
#define kGradStop_CLSID { 0x496f0bd4, 0x7834, 0x11d2, { 0xaa, 0xf0, 0x0, 0xc0, 0x4f, 0xa3, 0x77, 0x26 } }
// {496F0BD5-7834-11d2-AAF0-00C04FA37726}
#define kGradStops_CLSID { 0x496f0bd5, 0x7834, 0x11d2, { 0xaa, 0xf0, 0x0, 0xc0, 0x4f, 0xa3, 0x77, 0x26 } }
// {A373654D-4F5C-11d2-AB07-00C04FA349C7}
#define kTint_CLSID { 0xa373654d, 0x4f5c, 0x11d2, { 0xab, 0x7, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {A373654E-4F5C-11d2-AB07-00C04FA349C7}
#define kTints_CLSID { 0xa373654e, 0x4f5c, 0x11d2, { 0xab, 0x7, 0x0, 0xc0, 0x4f, 0xa3, 0x49, 0xc7 } }
// {7EB3B437-5D14-410c-94E4-7FB721D22C30}
#define kMixedInk_CLSID { 0x7eb3b437, 0x5d14, 0x410c, { 0x94, 0xe4, 0x7f, 0xb7, 0x21, 0xd2, 0x2c, 0x30 } }
// {A50BD6D8-6F1A-4cae-A05E-19B219AE5338}
#define kMixedInks_CLSID { 0xa50bd6d8, 0x6f1a, 0x4cae, { 0xa0, 0x5e, 0x19, 0xb2, 0x19, 0xae, 0x53, 0x38 } }
// {EAD3C699-166B-43f4-814E-2379FD129185}
#define kMixedInkGroup_CLSID { 0xead3c699, 0x166b, 0x43f4, { 0x81, 0x4e, 0x23, 0x79, 0xfd, 0x12, 0x91, 0x85 } }
// {7B49364B-B15E-4119-9AB2-FD88D6D4C3BC}
#define kMixedInkGroups_CLSID { 0x7b49364b, 0xb15e, 0x4119, { 0x9a, 0xb2, 0xfd, 0x88, 0xd6, 0xd4, 0xc3, 0xbc } }
// {3CD4BFBC-34A9-4bf0-8E36-F84C135A2D5D}
#define kDocumentEvent_CLSID { 0x3cd4bfbc, 0x34a9, 0x4bf0, { 0x8e, 0x36, 0xf8, 0x4c, 0x13, 0x5a, 0x2d, 0x5d } }
// {9123D596-C038-4296-8003-258CB4E6D6A6}
#define kImportExportEvent_CLSID { 0x9123d596, 0xc038, 0x4296, { 0x80, 0x3, 0x25, 0x8c, 0xb4, 0xe6, 0xd6, 0xa6 } }
#define kWatermarkPref_CLSID { 0x74dd09e5, 0x8658, 0x4c1b, { 0xa4, 0x18, 0x7, 0x3e, 0xcf, 0x95, 0x53, 0x93 } }

// {BBA05B9D-6328-4275-94E5-06A491E67F5D}
#define kColorGroup_CLSID { 0xbba05b9d, 0x6328, 0x4275, { 0x94, 0xe5, 0x6, 0xa4, 0x91, 0xe6, 0x7f, 0x5d } }
// {B29B5C06-8E74-4A3E-AB4E-9DDB0E8AF419}
#define kColorGroups_CLSID { 0xb29b5c06, 0x8e74, 0x4a3e, { 0xab, 0x4e, 0x9d, 0xdb, 0xe, 0x8a, 0xf4, 0x19 } }
// {248D90EE-BD6A-42D9-B7DC-79BCFADDF727}
#define kColorGroupMember_CLSID { 0x248d90ee, 0xbd6a, 0x42d9, { 0xb7, 0xdc, 0x79, 0xbc, 0xfa, 0xdd, 0xf7, 0x27 } }
// {B79A00A7-0245-40B1-9620-543FE05DD84D}
#define kColorGroupMembers_CLSID { 0xb79a00a7, 0x245, 0x40b1, { 0x96, 0x20, 0x54, 0x3f, 0xe0, 0x5d, 0xd8, 0x4d } }

//ScriptIDs
enum DocFrameworkScriptIDs
{
	c_DocumentEvent		=	'cDEv',
	c_ImportExportEvent	=	'cIEv',

	e_BeforeOpen		=	'bfOp',
	e_AfterOpen			=	'afOp',
	e_BeforeSave		=	'bfSv',
	e_AfterSave			=	'afSv',
	e_BeforeSaveAs		=	'bfSA',
	e_AfterSaveAs		=	'afSA',
	e_BeforeSaveACopy	=	'bSAC',
	e_AfterSaveACopy	=	'aSAC',
	e_BeforeRevert		=	'bfRv',
	e_AfterRevert		=	'afRv',
	e_BeforeClose		=	'bfCl',
	e_AfterClose		=	'afCl',
	e_BeforeExport		=	'bfEx',
	e_AfterExport		=	'afEx',
	e_FailedExport		=	'flEx',
	e_BeforeImport		=	'bfIm',
	e_AfterImport		=	'afIm',

	p_Converted			=	'pCnv',
	p_Recovered			=	'pRcv',
	p_ReadOnly			=	'pROy',
	p_MissingPlugins	=	'pMPl',
	p_UntitledDocCount		=	'pUDC',

	en_ExportFormat 		= 'eXft',
	en_TaggedText			= 'Tgtx',
	en_HTML					= 'HTML',
	en_RTF					= 'RTF ',
	en_SVG					= 'SVG ',
	en_SVGCompressed		= 'SVGC',
	en_XML					= 'XML ',
 	en_JPEG					= 'JPG ',
	en_InDesignInterchange	= 'INX ', // Now used for Generic interchange export
	en_InDesignMarkup		= 'idml',
 	en_InCopyCSStory		= 'incd',
	en_InCopyInterchange	= 'incx',
 	en_InCopyCSDocument		= 'etcd',
	en_InCopyDocument		= 'etcx',
	en_InCopyMarkup			= 'icml',
	en_Snippet				= 'snpt',
	en_PNG					= 'ePNG',
	en_EPUB					= 'epub', 
	en_EPUBFXL				= 'epfx',
	en_HTMLFXL			    = 'HTfx',
	en_LastMile			    = 'Lsfx',

	e_GetUntitledDocCount	= 'GUDC',
	e_SetUntitledDocCount	= 'SUDC',
	p_UntitledDocumentCount	= 'PUDC',
} ;

// User Action Categories
DECLARE_PMID(kUserActionCategoryIDSpace, kSwatchCategory, kDocFrameworkPrefix + 1)

#endif //__DocFrameworkID__
