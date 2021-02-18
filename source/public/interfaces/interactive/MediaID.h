//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/MediaID.h $
//  
//  Owner: wtislar
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

#ifndef __MediaID__
#define __MediaID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"


#define kMediaPrefix 				RezLong( 0x14000 )


//----------------------------------------------------------------------------------------
//
// PluginID
//

#define kMediaPluginName 			"Media"
#define kMediaPluginID 			kMediaPrefix + 1


enum MediaType
{
	enMovie = 0,
	enSound = 1
};

//----------------------------------------------------------------------------------------
//
// <Class IDs>
//

DECLARE_PMID(kClassIDSpace, kPosterImporterBoss, kMediaPrefix + 2)
DECLARE_PMID(kClassIDSpace, kPosterUtilsBoss, kMediaPrefix + 3)
DECLARE_PMID(kClassIDSpace, kMediaPageItemBoss, kMediaPrefix + 4)
DECLARE_PMID(kClassIDSpace, kMediaUtilsBoss, kMediaPrefix + 5)
DECLARE_PMID(kClassIDSpace, kMediaAdornmentBoss, kMediaPrefix + 6)
// gap
DECLARE_PMID(kClassIDSpace, kTopMediaAdornmentBoss, kMediaPrefix + 8)
DECLARE_PMID(kClassIDSpace, kDeleteMediaCmdBoss, kMediaPrefix + 9)
DECLARE_PMID(kClassIDSpace, kAlignMediaCmdBoss, kMediaPrefix + 10)
DECLARE_PMID(kClassIDSpace, kNewMediaPageItemCmdBoss, kMediaPrefix + 11)
DECLARE_PMID(kClassIDSpace, kResizeMediaCmdBoss, kMediaPrefix + 12)
DECLARE_PMID(kClassIDSpace, kMediaScriptUtilsBoss, kMediaPrefix + 13)
// gap
DECLARE_PMID(kClassIDSpace, kSetMediaAttrCmdBoss, kMediaPrefix + 15)
DECLARE_PMID(kClassIDSpace, kMediaContentDataBoss, kMediaPrefix + 16)
DECLARE_PMID(kClassIDSpace, kMediaPlaceProviderBoss, kMediaPrefix + 17)
DECLARE_PMID(kClassIDSpace, kMediaSelectionUtilsBoss, kMediaPrefix + 18)
DECLARE_PMID(kClassIDSpace, kFitMediaToFrameCmdBoss, kMediaPrefix + 19)
DECLARE_PMID(kClassIDSpace, kSetMediaContentCmdBoss, kMediaPrefix + 20)
DECLARE_PMID(kClassIDSpace, kUpdateMediaContentRefCmdBoss, kMediaPrefix + 21)
DECLARE_PMID(kClassIDSpace, kAddContentToDBCmdBoss, kMediaPrefix + 22)
DECLARE_PMID(kClassIDSpace, kChangeMediaLocationCmdBoss, kMediaPrefix + 23)
DECLARE_PMID(kClassIDSpace, kPasteMediaItemCmdBoss, kMediaPrefix + 24)
DECLARE_PMID(kClassIDSpace, kChangePosterCmdBoss, kMediaPrefix + 25)
DECLARE_PMID(kClassIDSpace, kCopyMediaItemCmdBoss, kMediaPrefix + 26)
DECLARE_PMID(kClassIDSpace, kMediaErrorStringServiceBoss, kMediaPrefix + 27)
DECLARE_PMID(kClassIDSpace, kPlaceMediaFromURLCmdBoss, kMediaPrefix + 28)
DECLARE_PMID(kClassIDSpace, kCheckMissingControllerSkinProviderBoss, kMediaPrefix + 29)
DECLARE_PMID(kClassIDSpace, kMediaCodeConversionProviderBoss, kMediaPrefix + 30)
DECLARE_PMID(kClassIDSpace, kClearAllMediaAttrCmdBoss, kMediaPrefix + 31)

//----------------------------------------------------------------------------------------
//
// <Interface IDs>
//

DECLARE_PMID(kInterfaceIDSpace, IID_IPOSTER, kMediaPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IOPENDIALOGFACTORY, kMediaPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IPOSTERIMPORTER, kMediaPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IPOSTERUTILS, kMediaPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IMEDIAADORNMENTICON, kMediaPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IMEDIAADORNMENTINFO, kMediaPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IMEDIAUTILS, kMediaPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IMEDIAATTRIBUTES, kMediaPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IALIGNMEDIACMDDATA, kMediaPrefix + 9)
DECLARE_PMID(kInterfaceIDSpace, IID_INEWMEDIAPAGEITEMCMDDATA, kMediaPrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IRESIZEMEDIACMDDATA, kMediaPrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IMEDIASCRIPTUTILS, kMediaPrefix + 12)
DECLARE_PMID(kInterfaceIDSpace, IID_IMEDIAREADFORMATINFO, kMediaPrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IMEDIAREADFORMAT, kMediaPrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IMEDIAINFO, kMediaPrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IMEDIAFORMATMANAGER, kMediaPrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETMEDIAATTRCMDDATA, kMediaPrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_APPLYFILTERATTRCMDDATA, kMediaPrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_IMEDIAERRORHANDLER, kMediaPrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_IMEDIASELECTIONUTILS, kMediaPrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_IINTERACTIVEFRAMEPREFERENCES, kMediaPrefix + 21)
DECLARE_PMID(kInterfaceIDSpace, IID_IINTERACTIVEFRAMEPREFSCMDDATA, kMediaPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_IMEDIACONTENT, kMediaPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_IMEDIACONTENTDATA, kMediaPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETMEDIACONTENTCMDDATA, kMediaPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_ICHGMEDIALOCATIONCMDDATA, kMediaPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_IMEDIAPROPERTIES_DOCUMENT,	kMediaPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_ICHANGEPOSTERCMDDATA, kMediaPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_IMEDIASUITE, kMediaPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_INAVIGATIONPOINTS, kMediaPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_IPLACEMEDIAFROMURLCMDDATA, kMediaPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_IPOSTERDATA, kMediaPrefix + 32)


//----------------------------------------------------------------------------------------
//
// <Implementation IDs>
//

DECLARE_PMID(kImplementationIDSpace, kMediaOpenDialogFactoryImpl, kMediaPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kPosterImporterImpl, kMediaPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kPosterUtilsImpl, kMediaPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kMediaAttributesImpl, kMediaPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kMediaUtilsImpl, kMediaPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kMediaItemScriptImpl, kMediaPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kTopFrameAdornmentImpl, kMediaPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kDeleteMediaCmdImpl, kMediaPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kMediaItemScrapImpl, kMediaPrefix + 9)
// gap
DECLARE_PMID(kImplementationIDSpace, kAlignMediaCmdImpl, kMediaPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kAlignMediaCmdDataImpl, kMediaPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kNewMediaPageItemCmdImpl, kMediaPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kNewMediaPageItemCmdDataImpl, kMediaPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kResizeMediaCmdImpl, kMediaPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kResizeMediaCmdDataImpl, kMediaPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kMediaScriptUtilsImpl, kMediaPrefix + 17)
// gap
DECLARE_PMID(kImplementationIDSpace, kSetMediaAttrCmdImpl, kMediaPrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kSetMediaAttrCmdDataImpl, kMediaPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kMediaPlaceProviderImpl, kMediaPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kMediaPlaceBehaviorImpl, kMediaPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kMediaPasteBehaviorImpl, kMediaPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kMediaPlaceScriptHelperImpl, kMediaPrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kMediaSelectionUtilsImpl, kMediaPrefix + 26)
// gap
DECLARE_PMID(kImplementationIDSpace, kMediaContentImpl, kMediaPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kFitMediaToFrameCmdImpl, kMediaPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kMediaContentDataImpl, kMediaPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kSetMediaContentCmdImpl, kMediaPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kSetMediaContentCmdDataImpl, kMediaPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kChgMediaLocationCmdImpl, kMediaPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kChgMediaLocationCmdDataImpl, kMediaPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kPasteMediaItemCmdImpl, kMediaPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kChangePosterCmdImpl, kMediaPrefix + 40)
DECLARE_PMID(kImplementationIDSpace, kChangePosterCmdDataImpl, kMediaPrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kCopyMediaItemCmdImpl, kMediaPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kMediaErrorStringServiceImpl, kMediaPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kMediaSuiteLayoutCSBImpl, kMediaPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kMediaSuiteLayoutCSBSelExtImpl, kMediaPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kMediaSuiteASBImpl, kMediaPrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kMediaSuiteASBSelExtImpl, kMediaPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kMediaSuiteDefaultCSBImpl, kMediaPrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kNavigationPointsImpl, kMediaPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kPlaceMediaFromURLCmdImpl, kMediaPrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kPlaceMediaFromURLCmdDataImpl, kMediaPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kCheckMissingControllerSkinProviderImpl, kMediaPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kPosterDataImpl, kMediaPrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kMediaCodeConversionProviderImpl, kMediaPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kClearAllMediaAttrCmdImpl, kMediaPrefix + 55)

//----------------------------------------------------------------------------------------
//
// <Service IDs>
//

DECLARE_PMID(kServiceIDSpace, kMediaReadFormatService, kMediaPrefix + 1)
DECLARE_PMID(kServiceIDSpace, kMediaURLAccessService, kMediaPrefix + 2)


// <Error IDs>

DECLARE_PMID(kErrorIDSpace, kCreateMediaFailed, kMediaPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kSetMediaAttrFailedError, kMediaPrefix + 2)
DECLARE_PMID(kErrorIDSpace, kChangeMediaLocationFailed, kMediaPrefix + 3)
DECLARE_PMID(kErrorIDSpace, kSetMediaContentFailedError, kMediaPrefix + 4)
DECLARE_PMID(kErrorIDSpace, kBrokenMediaDataLinkError, kMediaPrefix + 5)
DECLARE_PMID(kErrorIDSpace, kChangePosterFailedError, kMediaPrefix + 6)


// <Don't Show'Again IDs>
DECLARE_PMID(kDontShowAgainIDSpace, kOpenFlashUnsupportedMediaWarningId, kMediaPrefix + 1)
DECLARE_PMID(kDontShowAgainIDSpace, kPlaceFlashUnsupportedMediaWarningId, kMediaPrefix + 2)
DECLARE_PMID(kDontShowAgainIDSpace, kExportFlashUnsupportedMediaWarningId, kMediaPrefix + 3)
DECLARE_PMID(kDontShowAgainIDSpace, kMissingControllerSkinsWarningId, kMediaPrefix + 4)


//
//Script Element IDs
//

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kMediaItemObjectScriptElement,					kMediaPrefix + 24)

// Events
DECLARE_PMID(kScriptInfoIDSpace, kVerifyURLMethodScriptElement,					kMediaPrefix + 150)

// Properties
// WHT: removed script elements 7/14/2003 [Vantive 616739]
DECLARE_PMID(kScriptInfoIDSpace, kEmbedContentInPDFPropertyScriptElement,		kMediaPrefix + 160)
DECLARE_PMID(kScriptInfoIDSpace, kPlayOnPageTurnPropertyScriptElement,			kMediaPrefix + 161)
//DECLARE_PMID(kScriptInfoIDSpace, kPosterOptionPropertyScriptElement,			kMediaPrefix + 162)
DECLARE_PMID(kScriptInfoIDSpace, kPosterFilePropertyScriptElement,				kMediaPrefix + 163)
//DECLARE_PMID(kScriptInfoIDSpace, kPosterTypePropertyScriptElement,			kMediaPrefix + 164)
//DECLARE_PMID(kScriptInfoIDSpace, kPosterContentsScriptElement,				kMediaPrefix + 165)

// enums
//DECLARE_PMID(kScriptInfoIDSpace, kPosterOptionEnumScriptElement,				kMediaPrefix + 240)
//DECLARE_PMID(kScriptInfoIDSpace, kPosterTypeEnumScriptElement,				kMediaPrefix + 241)

// {8E11BA7A-A81F-4395-93AA-873D8034ECF4}
#define kMediaItem_CLSID { 0x8e11ba7a, 0xa81f, 0x4395, { 0x93, 0xaa, 0x87, 0x3d, 0x80, 0x34, 0xec, 0xf4 } }
// {F9CFE1FA-0C47-4c6c-B456-AE8D23267D24}
#define kMediaItems_CLSID { 0xf9cfe1fa, 0xc47, 0x4c6c, { 0xb4, 0x56, 0xae, 0x8d, 0x23, 0x26, 0x7d, 0x24 } }

enum MediaScriptIDs
{
	c_MediaItem					= 'MedI',
	c_MediaItems				= 'Meds'
} ;

#endif // __MediaID__
