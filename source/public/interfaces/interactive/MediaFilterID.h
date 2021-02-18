//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/MediaFilterID.h $
//  
//  Owner: xdx
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
//  Contains IDs used by WaveSound import filter
//  
//========================================================================================

#ifndef __MediaFilterID__
#define __MediaFilterID__

#include "CrossPlatformTypes.h"

#define kMediaFilterPrefix				RezLong (0x17600)

// PluginID
#define kMediaFilterPluginName 			"Media Import Filter"
#define kMediaFilterPluginID 				kMediaFilterPrefix + 1

// Anna
#define kMediaFilterAnnaRemoveImpls		kAnnaInitialMinorFormatNumber

// Add one of these for each product version.
#define kMediaFilterLastAnnaMinorFormat	kMediaFilterAnnaRemoveImpls

// Overall
#define kMediaFilterLastFormatChg			kMediaFilterLastAnnaMinorFormat


//----------------------------------------------------------------------------------------
//
// <Class IDs>

DECLARE_PMID( kClassIDSpace, kURLReadFormatBoss, kMediaFilterPrefix + 1 )
DECLARE_PMID( kClassIDSpace, kMediaAccessProviderBoss, kMediaFilterPrefix + 2 )
DECLARE_PMID( kClassIDSpace, kPosterReadFormatBoss, kMediaFilterPrefix + 3 )
DECLARE_PMID( kClassIDSpace, kQTMovieReadFormatBoss, kMediaFilterPrefix + 4 )
//DECLARE_PMID( kClassIDSpace, kQTPosterReadFormatBoss, kMediaFilterPrefix + 5 )
DECLARE_PMID( kClassIDSpace, kAVIMovieReadFormatBoss, kMediaFilterPrefix + 6 )
//DECLARE_PMID( kClassIDSpace, kAVIPosterReadFormatBoss, kMediaFilterPrefix + 7 )
DECLARE_PMID( kClassIDSpace, kMPEGMovieReadFormatBoss, kMediaFilterPrefix + 8 )
//gap
//DECLARE_PMID( kClassIDSpace, kMPEGPosterReadFormatBoss, kMediaFilterPrefix + 10 )
//gap
DECLARE_PMID( kClassIDSpace, kMediaFilterErrorStringServiceBoss, kMediaFilterPrefix + 12 )
DECLARE_PMID( kClassIDSpace, kAIFSoundReadFormatBoss, kMediaFilterPrefix + 13 )
DECLARE_PMID( kClassIDSpace, kAUSoundReadFormatBoss, kMediaFilterPrefix + 14 )
DECLARE_PMID( kClassIDSpace, kWAVSoundReadFormatBoss, kMediaFilterPrefix + 15 )
//DECLARE_PMID( kClassIDSpace, kQTMLAccessProviderBoss, kMediaFilterPrefix + 16 )
DECLARE_PMID( kClassIDSpace, kGenericMovieReadFormatBoss, kMediaFilterPrefix + 17 )
DECLARE_PMID( kClassIDSpace, kMediaAPManagerBoss, kMediaFilterPrefix + 18 )
//DECLARE_PMID( kClassIDSpace, kReadQTPosterImageStreamBoss, kMediaFilterPrefix + 19 )
DECLARE_PMID( kClassIDSpace, kAtmoReadFormatBoss, kMediaFilterPrefix + 20 )
DECLARE_PMID( kClassIDSpace, kVideoDecoderStartupShutdownBoss, kMediaFilterPrefix + 21 )
//gap
DECLARE_PMID( kClassIDSpace, kF4VReadFormatBoss, kMediaFilterPrefix + 23 )
DECLARE_PMID( kClassIDSpace, kMP3ReadFormatBoss, kMediaFilterPrefix + 24 )
DECLARE_PMID( kClassIDSpace, kVideoPreviewProviderBoss, kMediaFilterPrefix + 25 )
DECLARE_PMID( kClassIDSpace, kAudioPreviewProviderBoss, kMediaFilterPrefix + 26 )
//gap
//gap
DECLARE_PMID( kClassIDSpace, kVideoDecoderBeforeCloseDocResponderBoss, kMediaFilterPrefix + 29 )
DECLARE_PMID( kClassIDSpace, kHTMLLoaderProviderBoss, kMediaFilterPrefix + 30 )
DECLARE_PMID( kClassIDSpace, kHTMLLoaderBeforeCloseDocResponderBoss, kMediaFilterPrefix + 31 )

//----------------------------------------------------------------------------------------
//
// <Interface IDs>

DECLARE_PMID( kInterfaceIDSpace, IID_IMEDIAAPMANAGER, kMediaFilterPrefix + 1 )
DECLARE_PMID( kInterfaceIDSpace, IID_IMEDIAACCESSPROVIDER, kMediaFilterPrefix + 2 )
DECLARE_PMID( kInterfaceIDSpace, IID_IMEDIAAPINFO, kMediaFilterPrefix + 3 )
DECLARE_PMID( kInterfaceIDSpace, IID_IQTPOSTERIMAGESTREAMDATA, kMediaFilterPrefix + 4 )
DECLARE_PMID( kInterfaceIDSpace, IID_IMEDIAENCODER, kMediaFilterPrefix + 5 )
DECLARE_PMID( kInterfaceIDSpace, IID_IMEDIAENCODINGINFO, kMediaFilterPrefix + 6 )
DECLARE_PMID( kInterfaceIDSpace, IID_IMEDIAPLAYERACCESS, kMediaFilterPrefix + 7 )
DECLARE_PMID( kInterfaceIDSpace, IID_IMEDIAPLAYERUTILS, kMediaFilterPrefix + 8 )
DECLARE_PMID( kInterfaceIDSpace, IID_IDECODEDMEDIAATTRIBUTES, kMediaFilterPrefix + 9 )

//----------------------------------------------------------------------------------------
//
// <Implementation IDs>

DECLARE_PMID(kImplementationIDSpace, kMediaURLAccessServiceImpl, kMediaFilterPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kURLReadFormatImpl, kMediaFilterPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kPosterReadFormatImpl, kMediaFilterPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kPosterReadFormatInfoImpl, kMediaFilterPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kPosterReadFormatServiceImpl, kMediaFilterPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kQTReadFormatImpl, kMediaFilterPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kQTReadFormatInfoImpl, kMediaFilterPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kAVIReadFormatImpl, kMediaFilterPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kAVIReadFormatInfoImpl, kMediaFilterPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kMediaReadFormatServiceImpl, kMediaFilterPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kMPEGReadFormatImpl, kMediaFilterPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kMPEGReadFormatInfoImpl, kMediaFilterPrefix + 12)
//gap
DECLARE_PMID(kImplementationIDSpace, kMFErrorStringServiceImpl, kMediaFilterPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kAIFReadFormatImpl, kMediaFilterPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kAIFReadFormatInfoImpl, kMediaFilterPrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kAUReadFormatImpl, kMediaFilterPrefix + 18)
DECLARE_PMID(kImplementationIDSpace, kAUReadFormatInfoImpl, kMediaFilterPrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kWAVReadFormatImpl, kMediaFilterPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kWAVReadFormatInfoImpl, kMediaFilterPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kURLReadFormatInfoImpl, kMediaFilterPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kMediaAPManagerImpl, kMediaFilterPrefix + 23)
//DECLARE_PMID(kImplementationIDSpace, kQTMLAccessProviderImpl, kMediaFilterPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kGenericMovieReadFormatImpl, kMediaFilterPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kGenericMovieAPInfoImpl, kMediaFilterPrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kURLAPInfoImpl, kMediaFilterPrefix + 27)
//DECLARE_PMID(kImplementationIDSpace, kQTPosterImageStreamDataImpl, kMediaFilterPrefix + 28)
//DECLARE_PMID(kImplementationIDSpace, kQTPosterImageStreamImpl, kMediaFilterPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kAtmoReadFormatInfoImpl, kMediaFilterPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kAtmoReadFormatImpl, kMediaFilterPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kVideoPreviewAccessProviderImpl, kMediaFilterPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kDecodedMediaAttributesImpl, kMediaFilterPrefix + 33)
//gap
DECLARE_PMID(kImplementationIDSpace, kAMEWrapperImpl, kMediaFilterPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kDefaultVideoEncodingInfoImpl, kMediaFilterPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kHighDefVideoEncodingInfoImpl, kMediaFilterPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kF4VReadFormatInfoImpl, kMediaFilterPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kF4VReadFormatImpl, kMediaFilterPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kMP3ReadFormatInfoImpl, kMediaFilterPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kMP3ReadFormatImpl, kMediaFilterPrefix + 42)
//gap
DECLARE_PMID(kImplementationIDSpace, kVideoPreviewServiceProviderImpl, kMediaFilterPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kAudioPreviewServiceProviderImpl, kMediaFilterPrefix + 45)
//gap
DECLARE_PMID(kImplementationIDSpace, kAudioPreviewAccessProviderImpl, kMediaFilterPrefix + 47)
//gap
DECLARE_PMID(kImplementationIDSpace, kMP3PlayerAccessImpl, kMediaFilterPrefix + 49)
//gap
DECLARE_PMID(kImplementationIDSpace, kMediaPlayerUtilsImpl, kMediaFilterPrefix + 51)
//gap
//gap
//gap
DECLARE_PMID(kImplementationIDSpace, kVideoDecoderStartupShutdownImpl, kMediaFilterPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kVideoDecoderBeforeCloseDocResponderImpl, kMediaFilterPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kHTMLLoaderAccessImpl,					kMediaFilterPrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kHTMLLoaderServiceProviderImpl,		kMediaFilterPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kHTMLLoaderAccessProviderImpl,			kMediaFilterPrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kHTMLLoaderBeforeCloseDocResponderImpl, kMediaFilterPrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kMediaFilterObserverImpl, kMediaFilterPrefix + 61)


//----------------------------------------------------------------------------------------
//
// <Service IDs>
// DECLARE_PMID(kServiceIDSpace, kServiceID, kPrefix + x)
DECLARE_PMID(kServiceIDSpace,        kVideoPreviewService,					kMediaFilterPrefix + 1)
DECLARE_PMID(kServiceIDSpace,        kAudioPreviewService,					kMediaFilterPrefix + 2)
//gap
DECLARE_PMID(kServiceIDSpace,        kVideoDecoderService,					kMediaFilterPrefix + 4)
DECLARE_PMID(kServiceIDSpace,        kHTMLLoaderService,					kMediaFilterPrefix + 5)

//----------------------------------------------------------------------------------------
//
// <Error IDs> (ErrorCodes)

//DECLARE_PMID(kErrorIDSpace, kURLDownloadFailed, kMediaFilterPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kMalformedURL, kMediaFilterPrefix + 2)
//DECLARE_PMID(kErrorIDSpace, kCorruptedSource, kMediaFilterPrefix + 3)
//DECLARE_PMID(kErrorIDSpace, kMissingSource, kMediaFilterPrefix + 4)
//DECLARE_PMID(kErrorIDSpace, kErrorLoadingQTComponent, kMediaFilterPrefix + 5)
//DECLARE_PMID(kErrorIDSpace, kMissingQTComponent, kMediaFilterPrefix + 6)
//DECLARE_PMID(kErrorIDSpace, kQTNotInitialized, kMediaFilterPrefix + 7)
//DECLARE_PMID(kErrorIDSpace, kUnspecifiedQTDownloadError, kMediaFilterPrefix + 8)
//DECLARE_PMID(kErrorIDSpace, kUnspecifiedQTError, kMediaFilterPrefix + 9)
//DECLARE_PMID(kErrorIDSpace, kHTTPProtocolError, kMediaFilterPrefix + 10)
//DECLARE_PMID(kErrorIDSpace, kHTTPNoNetDriverError, kMediaFilterPrefix + 11)
//DECLARE_PMID(kErrorIDSpace, kHTTPURLError, kMediaFilterPrefix + 12)
//DECLARE_PMID(kErrorIDSpace, kHTTPRedirectError, kMediaFilterPrefix + 13)
//DECLARE_PMID(kErrorIDSpace, kFTPError, kMediaFilterPrefix + 14)
//DECLARE_PMID(kErrorIDSpace, kNotEnoughDataError, kMediaFilterPrefix + 15)
//DECLARE_PMID(kErrorIDSpace, kActionNotHandledError, kMediaFilterPrefix + 16)
DECLARE_PMID(kErrorIDSpace, kUnsupportedProtocolError, kMediaFilterPrefix + 17)
//DECLARE_PMID(kErrorIDSpace, kMPEGsNotAllowedWithThisQTVersion, kMediaFilterPrefix + 18)
//DECLARE_PMID(kErrorIDSpace, kQTNotInstalled, kMediaFilterPrefix + 19)
DECLARE_PMID(kErrorIDSpace, kURLToContentTypeIsNotSupported, kMediaFilterPrefix + 20)
//DECLARE_PMID(kErrorIDSpace, kQTPortLostConnection, kMediaFilterPrefix + 21)
//DECLARE_PMID(kErrorIDSpace, kQTWrongVersion, kMediaFilterPrefix + 22)
DECLARE_PMID(kErrorIDSpace, kInvalidOrUnsupportedSoundFormat, kMediaFilterPrefix + 23)
DECLARE_PMID(kErrorIDSpace, kPosterSelectionIsNotAvailable, kMediaFilterPrefix + 24)
//DECLARE_PMID(kErrorIDSpace, kQTMLFatalError, kMediaFilterPrefix + 25)
//DECLARE_PMID(kErrorIDSpace, kQTMLIsDisabled, kMediaFilterPrefix + 26)
DECLARE_PMID(kErrorIDSpace, kPosterSelectionFailed, kMediaFilterPrefix + 27)
DECLARE_PMID(kErrorIDSpace, kCouldNotFindServer, kMediaFilterPrefix + 28)
//DECLARE_PMID(kErrorIDSpace, kQTCouldNotResolveDataRef, kMediaFilterPrefix + 29)
//DECLARE_PMID(kErrorIDSpace, kQTUserCanceled, kMediaFilterPrefix + 30)
DECLARE_PMID(kErrorIDSpace, kNoQTAccess, kMediaFilterPrefix + 31)
DECLARE_PMID(kErrorIDSpace, kFlashSecurityError, kMediaFilterPrefix + 32)

#endif // __MediaFilterID__




