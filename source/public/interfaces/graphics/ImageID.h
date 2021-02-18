//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ImageID.h $
//  
//  Owner: jargast
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
//  Contains IDs used by the image item plug-in
//  
//========================================================================================

#ifndef __ImageID__
#define __ImageID__


#include "CrossPlatformTypes.h"
#include "IDFactory.h"


#define kImagePrefix	RezLong(0x1700)


// <Start IDC>
// PluginID
#define kImagePluginName			 			"Image"
DECLARE_PMID(kPlugInIDSpace, kImagePluginID, kImagePrefix + 1)


// <Class ID>
/**********************************************************************
*	CLASS IDs
**********************************************************************/

DECLARE_PMID(kClassIDSpace, kImageBaseItem, kImagePrefix + 1)
DECLARE_PMID(kClassIDSpace, kImageItem, kImagePrefix + 2)
DECLARE_PMID(kClassIDSpace, kPlaceImageCmdBoss, kImagePrefix + 3)
DECLARE_PMID(kClassIDSpace, kSetImageDataAccessCmdBoss, kImagePrefix + 4)
DECLARE_PMID(kClassIDSpace, kImagePlaceProviderBoss, kImagePrefix + 5)
DECLARE_PMID(kClassIDSpace, kImageObject, kImagePrefix + 6)
DECLARE_PMID(kClassIDSpace, kImageInFile, kImagePrefix + 7)
DECLARE_PMID(kClassIDSpace, kImageInDB, kImagePrefix + 8)
DECLARE_PMID(kClassIDSpace, kCreateLowResImageCmdBoss, kImagePrefix + 9)
DECLARE_PMID(kClassIDSpace, kLowResImageRefConverterBoss, kImagePrefix + 10)
DECLARE_PMID(kClassIDSpace, kCopyLowResToScrapCmdBoss, kImagePrefix + 11)
DECLARE_PMID(kClassIDSpace, kSetRelinkPrefsCmdBoss, kImagePrefix + 12)
DECLARE_PMID(kClassIDSpace, kDeleteLowResImageCmdBoss, kImagePrefix + 13)
DECLARE_PMID(kClassIDSpace, kImageFormatManager, kImagePrefix + 14)
DECLARE_PMID(kClassIDSpace, kDeleteImageItemCmdBoss, kImagePrefix + 15)
DECLARE_PMID(kClassIDSpace, kDeepCutLazyStartupShutdownBoss, kImagePrefix + 16)
//gap
DECLARE_PMID(kClassIDSpace, kImageErrorStringServiceBoss, kImagePrefix + 17)
DECLARE_PMID(kClassIDSpace, kCopyImageItemCmdBoss, kImagePrefix + 18)
DECLARE_PMID(kClassIDSpace, kImageIteratorRegBoss, kImagePrefix + 19)
DECLARE_PMID(kClassIDSpace, kSetImageFormatClassCmdBoss, kImagePrefix + 20)
//gap
DECLARE_PMID(kClassIDSpace, kSetImagePrefsCmdBoss_OBSOLETE, kImagePrefix + 22)
DECLARE_PMID(kClassIDSpace, kEdgeDetectionBoss, kImagePrefix + 23)
DECLARE_PMID(kClassIDSpace, kPhotoshopClippingPathBoss, kImagePrefix + 24)
DECLARE_PMID(kClassIDSpace, kSetImageIOPrefsCmdBoss, kImagePrefix + 25)
DECLARE_PMID(kClassIDSpace, kImageConversionProviderBoss, kImagePrefix + 26)
DECLARE_PMID(kClassIDSpace, kImageCreateMetaDataCmdBoss, kImagePrefix + 27)
//gap
DECLARE_PMID(kClassIDSpace, kClippingPathScriptProviderBoss, kImagePrefix + 29)
//gap
DECLARE_PMID(kClassIDSpace, kImageIOPrefsScriptProviderBoss, kImagePrefix + 31)	//jwb 4/30/02 Moved from ScriptingID.h
DECLARE_PMID(kClassIDSpace, kImageOpenDocResponderBoss, kImagePrefix + 32)
DECLARE_PMID(kClassIDSpace, kImageNewDocResponderBoss, kImagePrefix + 33)

// Class ID -- ImageStream
DECLARE_PMID(kClassIDSpace, kImageStreamManagerBoss, kImagePrefix + 50)
DECLARE_PMID(kClassIDSpace, kReadDataImageStreamBoss, kImagePrefix + 51)
DECLARE_PMID(kClassIDSpace, kReadFormatImageStreamBoss, kImagePrefix + 52)
DECLARE_PMID(kClassIDSpace, kDownSampleImageStreamBoss, kImagePrefix + 53)
DECLARE_PMID(kClassIDSpace, kAntiAliasImageStreamBoss, kImagePrefix + 54)
DECLARE_PMID(kClassIDSpace, kConvertBitDepthImageStreamBoss, kImagePrefix + 55)
DECLARE_PMID(kClassIDSpace, kCreateCacheImageStreamBoss, kImagePrefix + 56)
DECLARE_PMID(kClassIDSpace, kMungeSamplesImageStreamBoss, kImagePrefix + 57)
DECLARE_PMID(kClassIDSpace, kPlanarToChunkyImageStreamBoss, kImagePrefix + 58)
DECLARE_PMID(kClassIDSpace, kChunkyToPlanarImageStreamBoss, kImagePrefix + 59)
DECLARE_PMID(kClassIDSpace, kIndexedToChunkyImageStreamBoss, kImagePrefix + 60)
DECLARE_PMID(kClassIDSpace, kChunkyToIndexedImageStreamBoss, kImagePrefix + 61)
DECLARE_PMID(kClassIDSpace, kColorConverterImageStreamBoss, kImagePrefix + 62)
DECLARE_PMID(kClassIDSpace, kInvertImageStreamBoss, kImagePrefix + 63)
DECLARE_PMID(kClassIDSpace, kSimpleImageStreamManagerBoss, kImagePrefix + 64)
// gap
DECLARE_PMID(kClassIDSpace, kReadAGMImageStreamBoss, kImagePrefix + 66)
DECLARE_PMID(kClassIDSpace, kReadAlphaImageStreamBoss, kImagePrefix + 67)
DECLARE_PMID(kClassIDSpace, kBicubicImageStreamBoss, kImagePrefix + 68)
DECLARE_PMID(kClassIDSpace, kConvertAlphaImageStreamBoss, kImagePrefix + 69)
DECLARE_PMID(kClassIDSpace, kRepackAlphaImageStreamBoss, kImagePrefix + 70)
DECLARE_PMID(kClassIDSpace, kReorderChannelsImageStreamBoss, kImagePrefix + 71)
DECLARE_PMID(kClassIDSpace, kDownsamplePlanarToChunkyImageStreamBoss, kImagePrefix + 72)
DECLARE_PMID(kClassIDSpace, kAntiAliasPlanarToChunkyBoss, kImagePrefix + 73)
DECLARE_PMID(kClassIDSpace, kMergeAlphasImageStreamBoss, kImagePrefix + 74)
DECLARE_PMID(kClassIDSpace, kMapSpotToAlphaImageStreamBoss, kImagePrefix + 75)
DECLARE_PMID(kClassIDSpace, kSubAveragingImageStreamBoss, kImagePrefix + 76)
DECLARE_PMID(kClassIDSpace, kSubAveragePlanarToChunkyImageStreamBoss, kImagePrefix + 77)

// Class ID -- ImagePreferences
DECLARE_PMID(kClassIDSpace, kSetImagePrefsLayoutActionBoss_OBSOLETE, kImagePrefix + 100)

DECLARE_PMID(kClassIDSpace, kImageListAddRefCmdBoss, kImagePrefix + 101)
DECLARE_PMID(kClassIDSpace, kImageListReleaseCmdBoss, kImagePrefix + 102)
DECLARE_PMID(kClassIDSpace, kSetGraphicDisplayOptionsCmdBoss_OBSOLETE, kImagePrefix + 103)
// unused - formerly kImagePhase2ConversionBoss  kImagePrefix + 104
DECLARE_PMID(kClassIDSpace,	kVirtualImageStreamBoss, kImagePrefix + 105)
DECLARE_PMID(kClassIDSpace,	kImageConvertProviderBoss, kImagePrefix + 106)
DECLARE_PMID(kClassIDSpace,	kAddImageColorsCmdBoss, kImagePrefix + 107)
DECLARE_PMID(kClassIDSpace, kReplaceFPOImageHolderBoss, kImagePrefix + 108)
DECLARE_PMID(kClassIDSpace, kSetGraphicLayerInfoCmdBoss, kImagePrefix + 109)
DECLARE_PMID(kClassIDSpace, kChangeVisibleLayersCmdBoss, kImagePrefix + 110)
DECLARE_PMID(kClassIDSpace, kGraphicLayerInfoBoss, kImagePrefix + 111)
DECLARE_PMID(kClassIDSpace, kInitializeGraphicLayersCmdBoss, kImagePrefix + 112)
DECLARE_PMID(kClassIDSpace, kGraphicLayerOptionsScriptProviderBoss, kImagePrefix + 113)
DECLARE_PMID(kClassIDSpace, kGraphicLayerScriptProviderBoss, kImagePrefix + 114)
DECLARE_PMID(kClassIDSpace, kGraphicLayerProxyScriptObjectBoss, kImagePrefix + 115)
DECLARE_PMID(kClassIDSpace, kImageLinksChangedResponderBoss, kImagePrefix + 116)
DECLARE_PMID(kClassIDSpace, kImageSwatchesRIDXNotifierHandlerBoss, kImagePrefix + 117)
DECLARE_PMID(kClassIDSpace, kPSDLayerCompScriptProviderBoss, kImagePrefix + 118)
DECLARE_PMID(kClassIDSpace, kLinkInfoXMPApertureProviderBoss, kImagePrefix + 119)
DECLARE_PMID(kClassIDSpace, kLinkInfoXMPShutterProviderBoss, kImagePrefix + 120)
DECLARE_PMID(kClassIDSpace, kLinkInfoXMPISOSpeedProviderBoss, kImagePrefix + 121)
DECLARE_PMID(kClassIDSpace, kLinkInfoXMPCameraProviderBoss, kImagePrefix + 122)
DECLARE_PMID(kClassIDSpace, kLinkInfoXMPLensProviderBoss, kImagePrefix + 123)
DECLARE_PMID(kClassIDSpace, kLinkInfoXMPFocalLengthProviderBoss, kImagePrefix + 124)
DECLARE_PMID(kClassIDSpace, kLinkInfoXMPKeywordsProviderBoss, kImagePrefix + 125)
DECLARE_PMID(kClassIDSpace, kLinkInfoXMPCaptureDateProviderBoss, kImagePrefix + 126)
DECLARE_PMID(kClassIDSpace, kLinkInfoXMPRatingProviderBoss, kImagePrefix + 127)
DECLARE_PMID(kClassIDSpace, kLinkInfoUsedSwatchesProviderBoss, kImagePrefix + 128)
DECLARE_PMID(kClassIDSpace, kLinkInfoXMPCreditProviderBoss, kImagePrefix + 129)
DECLARE_PMID(kClassIDSpace, kLinkInfoXMPDescriptionProviderBoss, kImagePrefix + 130)
DECLARE_PMID(kClassIDSpace, kLinkInfoXMPHeadlineProviderBoss, kImagePrefix + 131)
DECLARE_PMID(kClassIDSpace, kLinkInfoXMPLocationProviderBoss, kImagePrefix + 132)
DECLARE_PMID(kClassIDSpace, kLinkInfoXMPLocationCityProviderBoss, kImagePrefix + 133)
DECLARE_PMID(kClassIDSpace, kLinkInfoXMPLocationStateProviderBoss, kImagePrefix + 134)
DECLARE_PMID(kClassIDSpace, kLinkInfoXMPLocationCountryProviderBoss, kImagePrefix + 135)
DECLARE_PMID(kClassIDSpace, kOptimizeImagesCmdBoss, kImagePrefix + 136)
DECLARE_PMID(kClassIDSpace, kSetUpdateLinkNewLayersAsHiddenPrefCmdBoss, kImagePrefix + 137)

// Class ID -- ImageCache
DECLARE_PMID(kClassIDSpace, kImageCacheBoss, kImagePrefix + 200)
 
// <Interface ID>
/**********************************************************************
*	INTERFACE IDs
**********************************************************************/
DECLARE_PMID(kInterfaceIDSpace, IID_ICACHEDIMAGEDATA, kImagePrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMPORTIMAGECMDDATA, kImagePrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGEREADFORMATINFO, kImagePrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGEREADFORMAT, kImagePrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGEWRITEFORMATINFO, kImagePrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGEWRITEFORMAT, kImagePrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGEATTRIBUTES, kImagePrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGEREADDATA, kImagePrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGEDATAACCESS, kImagePrefix + 10)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGEFORMATACCESS, kImagePrefix + 11)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGECACHEVALIDMARK_UNUSED, kImagePrefix + 12)	// Obsolete: Use the IImageCacheMgr
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGEPREFERENCES_OBSOLETE, kImagePrefix + 13)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGEFORMATMANAGER, kImagePrefix + 14)
DECLARE_PMID(kInterfaceIDSpace, IID_IOPTIMIZEIMAGES_CMDOPTIONS, kImagePrefix + 15)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGEPREFSCMDDATA_OBSOLETE, kImagePrefix + 16)
DECLARE_PMID(kInterfaceIDSpace, IID_IEDGEDETECTION, kImagePrefix + 17)
DECLARE_PMID(kInterfaceIDSpace, IID_IPHOTOSHOPCLIPPINGPATH, kImagePrefix + 18)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGEIOPREFSCMDDATA, kImagePrefix + 19)
DECLARE_PMID(kInterfaceIDSpace, IID_ICREATELOWRESIMAGECMDDATA, kImagePrefix + 20)
DECLARE_PMID(kInterfaceIDSpace, IID_ILINKRESOURCEUIDDATA, kImagePrefix + 21)

DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGEITEM, kImagePrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICITEM, kImagePrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_IMAGETAGSERVICE, kImagePrefix + 32)

DECLARE_PMID(kInterfaceIDSpace, IID_ILOWRESIMAGELIST, kImagePrefix + 46)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCRAPIMAGELIST, kImagePrefix + 47)

// IID -- ImageStream	
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGESTREAMMANAGER, kImagePrefix + 50)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGESTREAM, kImagePrefix + 51)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONNECTIMAGESTREAMDATA, kImagePrefix + 52)
DECLARE_PMID(kInterfaceIDSpace, IID_IREADDATAIMAGESTREAMDATA, kImagePrefix + 53)
DECLARE_PMID(kInterfaceIDSpace, IID_IFORMATIMAGESTREAMDATA, kImagePrefix + 54)
DECLARE_PMID(kInterfaceIDSpace, IID_IDOWNSAMPLEIMAGESTREAMDATA, kImagePrefix + 55)
DECLARE_PMID(kInterfaceIDSpace, IID_IANTIALIASIMAGESTREAMDATA, kImagePrefix + 56)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONVERTDEPTHIMAGESTREAMDATA, kImagePrefix + 57)
DECLARE_PMID(kInterfaceIDSpace, IID_ICREATECACHEIMAGESTREAMDATA, kImagePrefix + 58)
DECLARE_PMID(kInterfaceIDSpace, IID_IMUNGESAMPLESIMAGESTREAMDATA, kImagePrefix + 59)
DECLARE_PMID(kInterfaceIDSpace, IID_IPLANARTOCHUNKYIMAGESTREAMDATA, kImagePrefix + 60)
DECLARE_PMID(kInterfaceIDSpace, IID_ICHUNKYTOPLANARIMAGESTREAMDATA, kImagePrefix + 61)
DECLARE_PMID(kInterfaceIDSpace, IID_IINDEXEDTOCHUNKYIMAGESTREAMDATA, kImagePrefix + 62)
DECLARE_PMID(kInterfaceIDSpace, IID_ICHUNKYTOINDEXEDIMAGESTREAMDATA, kImagePrefix + 63)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORCONVERTERIMAGESTREAMDATA, kImagePrefix + 64)
DECLARE_PMID(kInterfaceIDSpace, IID_IPAGEITEMREFERENCE, kImagePrefix + 65) // Same as IID_IPERSISTUIDDATA
DECLARE_PMID(kInterfaceIDSpace, IID_ISIMPLEIMAGESTREAMMANAGER, kImagePrefix + 66)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IREADAGMIMAGESTREAMDATA, kImagePrefix + 68)
DECLARE_PMID(kInterfaceIDSpace, IID_IREADALPHAIMAGESTREAMDATA, kImagePrefix + 69)
DECLARE_PMID(kInterfaceIDSpace, IID_IBICUBICIMAGESTREAMDATA, kImagePrefix + 70)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGEUTILS, kImagePrefix + 71)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGESHIFTUTILS, kImagePrefix + 72)
DECLARE_PMID(kInterfaceIDSpace, IID_ICONVERTALPHAIMAGESTREAMDATA, kImagePrefix + 73)
DECLARE_PMID(kInterfaceIDSpace, IID_IREPACKALPHAIMAGESTREAMDATA, kImagePrefix + 74)
DECLARE_PMID(kInterfaceIDSpace, IID_ISUBAVERAGINGIMAGESTREAMDATA, kImagePrefix + 75)
DECLARE_PMID(kInterfaceIDSpace, IID_IDEEPCUTOUT_MANAGER, kImagePrefix + 76)
//gap
// IID -- ImagePreferences	
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGEPREFSLAYOUTOBSERVER_OBSOLETE, kImagePrefix + 100)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGEIOPREFERENCES, kImagePrefix + 101)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICDISPLAYOPTIONS_OBSOLETE, kImagePrefix + 102)
DECLARE_PMID(kInterfaceIDSpace, IID_ISETGRAPHICDISPLAYCMDDATA_OBSOLETE, kImagePrefix + 103)
DECLARE_PMID(kInterfaceIDSpace, IID_IRELINKPREFERENCES, kImagePrefix + 104)
DECLARE_PMID(kInterfaceIDSpace, IID_IUPDATELINKNEWLAYERSASHIDDENPREF, kImagePrefix + 105)

DECLARE_PMID(kInterfaceIDSpace, IID_ICLOSEDOCOBSERVER, kImagePrefix + 110)
DECLARE_PMID(kInterfaceIDSpace, IID_ITEXTWRAPPATH, kImagePrefix + 111)

// New to DragonTail
// *** WARNING: Notice that the ImageCache IDs are out of order ***
DECLARE_PMID(kInterfaceIDSpace, IID_ICLIPPINGPATHSUITE, kImagePrefix + 112)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGEFACADE, kImagePrefix + 113)
DECLARE_PMID(kInterfaceIDSpace, IID_ICLIPPINGPATHFACADE, kImagePrefix + 114)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICLAYERINFO, kImagePrefix  + 115)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICCHANNELINFO, kImagePrefix  + 116)
DECLARE_PMID(kInterfaceIDSpace,	IID_IVIRTUALIMAGESTREAMDATA, kImagePrefix + 117)
DECLARE_PMID(kInterfaceIDSpace,	IID_IADDIMAGECOLORSCMDDATA, kImagePrefix + 118)
DECLARE_PMID(kInterfaceIDSpace, IID_IREORDERCHANNELSIMAGESTREAMDATA, kImagePrefix + 119)
DECLARE_PMID(kInterfaceIDSpace, IID_I16TO8BITDEPTHREDUCER, kImagePrefix + 120)
DECLARE_PMID(kInterfaceIDSpace, IID_IDUOTONEINFO, kImagePrefix  + 121)
DECLARE_PMID(kInterfaceIDSpace, IID_IVIRTUALIMAGEUTILS, kImagePrefix + 122)
DECLARE_PMID(kInterfaceIDSpace, IID_IMERGEALPHASIMAGESTREAMDATA, kImagePrefix + 123)
DECLARE_PMID(kInterfaceIDSpace, IID_IMAPSPOTTOALPHAIMAGESTREAMDATA, kImagePrefix + 124)
DECLARE_PMID(kInterfaceIDSpace, IID_IREPLACEFPOIMAGE, kImagePrefix + 125)
DECLARE_PMID(kInterfaceIDSpace, IID_IREPLACEFPOIMAGEDATA, kImagePrefix + 126)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGEBOSSINFO, kImagePrefix + 127)

DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGEIMPORTUIDIALOG, kImagePrefix + 128)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGEOBJECTSUITE, kImagePrefix + 129)
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORCONVIMGSTRMOPTIONS, kImagePrefix + 130)
DECLARE_PMID(kInterfaceIDSpace, IID_IAGMIMAGEDATA, kImagePrefix + 131)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGEPRIVATEUTILS, kImagePrefix + 132)
//gap 133-134
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGEGRAPHIXCACHE, kImagePrefix + 135)
// gap
// IID -- ImageCache
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGECACHE, kImagePrefix + 200)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMAGECACHEMGR, kImagePrefix + 201)

// <Implementation ID>
/**********************************************************************
*	IMPLEMENTATION IDs
**********************************************************************/
DECLARE_PMID(kImplementationIDSpace, kImageShape, kImagePrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kSetImageDataAccessCmdImpl, kImagePrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kImportImageCmdData, kImagePrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kCreateLowResImageCmdDataImpl, kImagePrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kGeometryImage, kImagePrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kImagePlaceProvider, kImagePrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kCImageAttributes, kImagePrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kCImageFormatAccess, kImagePrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kImageReadDataImpl, kImagePrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kScrapImageListImpl, kImagePrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kCImageFileInfo, kImagePrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kImageDataAccessImpl, kImagePrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kDocImagePreferences_OBSOLETE, kImagePrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kSessionImagePreferences, kImagePrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kCImageFormatManager, kImagePrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kPlaceImageCmd, kImagePrefix + 17)
DECLARE_PMID(kImplementationIDSpace, kImageCacheValidMarkImpl_Unused, kImagePrefix + 18) //Obsolete: Use the IImageCacheMgr
DECLARE_PMID(kImplementationIDSpace, kCreateLowResImageCmdImpl, kImagePrefix + 19)
DECLARE_PMID(kImplementationIDSpace, kImageItemIOPreferencesImpl, kImagePrefix + 20)
DECLARE_PMID(kImplementationIDSpace, kSessionImageIOPreferencesImpl, kImagePrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kCopyLowResToScrapCmdImpl, kImagePrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kDeleteLowResImageCmdImpl, kImagePrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kImageIOPrefsScriptProviderImpl, kImagePrefix + 24)		//jwb 4/30/02 Moved from ScriptingID.h
DECLARE_PMID(kImplementationIDSpace, kImageDocResponderImpl, kImagePrefix + 25)
DECLARE_PMID(kImplementationIDSpace, kRelinkPreferencesImpl, kImagePrefix + 26)
DECLARE_PMID(kImplementationIDSpace, kSetRelinkPrefsCmdImpl, kImagePrefix + 27)
DECLARE_PMID(kImplementationIDSpace, kImageItemScrap, kImagePrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kDeleteImageItemCmd, kImagePrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kImageToPolygon, kImagePrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kCImagePreferences_OBSOLETE, kImagePrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kImportedImageDataProp, kImagePrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kImageErrorStringService, kImagePrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kDfltImageReadFormatService, kImagePrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kCopyImageItemCmd, kImagePrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kGraphicDisplayOptionsImpl_OBSOLETE, kImagePrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kSetImageFormatClassCmdImpl, kImagePrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kImageIteratorRegImpl, kImagePrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kSetImagePrefsCmd_OBSOLETE, kImagePrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kImagePrefsCmdData_OBSOLETE, kImagePrefix + 40)

DECLARE_PMID(kImplementationIDSpace, kEdgeDetectionImpl, kImagePrefix + 41)
DECLARE_PMID(kImplementationIDSpace, kImageItemImpl, kImagePrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kPhotoshopClippingPathImpl, kImagePrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kImageItemInkResourcesImpl, kImagePrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kOptimizeImagesCmdImpl, kImagePrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kLowResImageListImpl, kImagePrefix + 46)
DECLARE_PMID(kImplementationIDSpace, kLowResImageRefConverterImpl, kImagePrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kImagePlaceBehaviorImpl, kImagePrefix + 48)
DECLARE_PMID(kImplementationIDSpace, kImageCreateMetaDataCmdImpl, kImagePrefix + 49)

// Image ImageStream Implementation IDs
DECLARE_PMID(kImplementationIDSpace, kAntiAliasImageStreamData, kImagePrefix + 50)
DECLARE_PMID(kImplementationIDSpace, kChunkyToIndexedImageStream, kImagePrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kChunkyToIndexedImageStreamData, kImagePrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kChunkyToPlanarImageStream, kImagePrefix + 53)
DECLARE_PMID(kImplementationIDSpace, kChunkyToPlanarImageStreamData, kImagePrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kConnectImageStreamData, kImagePrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kConvertDepthImageStreamData, kImagePrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kConvertBitDepthImageStream, kImagePrefix + 57)
DECLARE_PMID(kImplementationIDSpace, kCreateCacheImageStream, kImagePrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kCreateCacheImageStreamData, kImagePrefix + 59)
DECLARE_PMID(kImplementationIDSpace, kDownSampleImageStreamData, kImagePrefix + 60)
DECLARE_PMID(kImplementationIDSpace, kFormatImageStreamData, kImagePrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kMungeSamplesImageStream, kImagePrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kMungeSamplesImageStreamData, kImagePrefix + 63)
DECLARE_PMID(kImplementationIDSpace, kPlanarToChunkyImageStream, kImagePrefix + 64)
DECLARE_PMID(kImplementationIDSpace, kPlanarToChunkyImageStreamData, kImagePrefix + 65)
DECLARE_PMID(kImplementationIDSpace, kReadDataImageStreamData, kImagePrefix + 66)
DECLARE_PMID(kImplementationIDSpace, kSimpleImageStreamManagerImpl, kImagePrefix + 67)
DECLARE_PMID(kImplementationIDSpace, kImageStreamManager, kImagePrefix + 68)
DECLARE_PMID(kImplementationIDSpace, kDownSampleImageStream, kImagePrefix + 69)
DECLARE_PMID(kImplementationIDSpace, kAntiAliasImageStream, kImagePrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kReadDataImageStream, kImagePrefix + 71)
DECLARE_PMID(kImplementationIDSpace, kReadFormatImageStream, kImagePrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kIndexedToChunkyImageStream, kImagePrefix + 73)
DECLARE_PMID(kImplementationIDSpace, kIndexedToChunkyImageStreamData, kImagePrefix + 74)
DECLARE_PMID(kImplementationIDSpace, kColorConverterImageStream, kImagePrefix + 75)
DECLARE_PMID(kImplementationIDSpace, kColorConverterImageStreamData, kImagePrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kSubAveragingImageStreamDataImpl, kImagePrefix + 77)
DECLARE_PMID(kImplementationIDSpace, kSubAveragingImageStreamImpl, kImagePrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kInvertImageStream, kImagePrefix + 79)
DECLARE_PMID(kImplementationIDSpace, kUpdateLinkNewLayersAsHiddenPrefImpl, kImagePrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kSetUpdateLinkNewLayersAsHiddenPrefCmdImpl, kImagePrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kReadAGMImageStreamImpl, kImagePrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kReadAGMImageStreamDataImpl, kImagePrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kReadAlphaImageStreamImpl, kImagePrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kReadAlphaImageStreamDataImpl, kImagePrefix + 85)
DECLARE_PMID(kImplementationIDSpace, kBicubicImageStreamImpl, kImagePrefix + 86)
DECLARE_PMID(kImplementationIDSpace, kBicubicImageStreamDataImpl, kImagePrefix + 87)
DECLARE_PMID(kImplementationIDSpace, kImageUtilsImpl, kImagePrefix + 88)
DECLARE_PMID(kImplementationIDSpace, kImageShiftUtilsImpl, kImagePrefix + 89)
DECLARE_PMID(kImplementationIDSpace, kConvertAlphaImageStreamImpl, kImagePrefix + 90)
DECLARE_PMID(kImplementationIDSpace, kConvertAlphaImageStreamDataImpl, kImagePrefix + 91)
DECLARE_PMID(kImplementationIDSpace, kRepackAlphaImageStreamImpl, kImagePrefix + 92)
DECLARE_PMID(kImplementationIDSpace, kRepackAlphaImageStreamDataImpl, kImagePrefix + 93)
DECLARE_PMID(kImplementationIDSpace, kReorderChannelsImageStreamImpl, kImagePrefix + 94)
DECLARE_PMID(kImplementationIDSpace, kReorderChannelsImageStreamDataImpl, kImagePrefix + 95)
DECLARE_PMID(kImplementationIDSpace, kDownsamplePlanarToChunkyImpl, kImagePrefix + 96)
DECLARE_PMID(kImplementationIDSpace, kAntiAliasPlanarToChunkyImpl, kImagePrefix + 97)
DECLARE_PMID(kImplementationIDSpace, kSubAveragePlanarToChunkyImpl, kImagePrefix + 98)

// ImagePreferences Implementation IDs
DECLARE_PMID(kImplementationIDSpace, kSetImagePrefsLayoutObserver_OBSOLETE, kImagePrefix + 100)
DECLARE_PMID(kImplementationIDSpace, kSetImagePrefsLayoutAction_OBSOLETE, kImagePrefix + 101)
DECLARE_PMID(kImplementationIDSpace, kSetImageIOPrefsCmdImpl, kImagePrefix + 102)
DECLARE_PMID(kImplementationIDSpace, kImageIOPrefsCmdDataImpl, kImagePrefix + 103)
DECLARE_PMID(kImplementationIDSpace, kSetGraphicDisplayOptionsCmdImpl_OBSOLETE, kImagePrefix + 104)
DECLARE_PMID(kImplementationIDSpace, kSetGraphicDisplayCmdDataImpl_OBSOLETE, kImagePrefix + 105)

//gap
DECLARE_PMID(kImplementationIDSpace, kDeepCutLazyStartupShutdownImpl, kImagePrefix + 109)
DECLARE_PMID(kImplementationIDSpace, kCloseDocObserverImpl, kImagePrefix + 110)

DECLARE_PMID(kImplementationIDSpace, kImageListAddRefCmdImpl, kImagePrefix + 111)
DECLARE_PMID(kImplementationIDSpace, kImageListReleaseCmdImpl, kImagePrefix + 112)
// gap
DECLARE_PMID(kImplementationIDSpace, kImageVisitorHelperImpl, kImagePrefix + 114)

//gap
// *** WARNING: Notice that the ImageCache IDs are out of order ***
DECLARE_PMID(kImplementationIDSpace, kImageItemFlattenerUsageImpl, kImagePrefix + 116)

// Implementation IDs new To DragonTail
DECLARE_PMID(kImplementationIDSpace, kClippingPathSuiteASBImpl, kImagePrefix + 117)
DECLARE_PMID(kImplementationIDSpace, kClippingPathSuiteLayoutCSBImpl, kImagePrefix + 118)
DECLARE_PMID(kImplementationIDSpace, kImageFacadeImpl, kImagePrefix + 119)
DECLARE_PMID(kImplementationIDSpace, kClippingPathFacadeImpl, kImagePrefix + 120)
// gap
DECLARE_PMID(kImplementationIDSpace, kGraphicLayerInfoImpl, kImagePrefix + 122)
// unused - formerly kImagePhase2ConversionImpl  kImagePrefix + 123
DECLARE_PMID(kImplementationIDSpace, kGraphicChannelInfoImpl, kImagePrefix + 124)
DECLARE_PMID(kImplementationIDSpace, kVirtualImageStreamImpl, kImagePrefix + 125)
DECLARE_PMID(kImplementationIDSpace, kVirtualImageStreamDataImpl, kImagePrefix + 126)

DECLARE_PMID(kImplementationIDSpace, kClippingPathScriptProviderImpl, kImagePrefix + 127)
//gap
DECLARE_PMID(kImplementationIDSpace, kImageConversionProviderImpl, kImagePrefix + 129)
DECLARE_PMID(kImplementationIDSpace, kAddImageColorsCmdImpl, kImagePrefix + 130)
DECLARE_PMID(kImplementationIDSpace, kAddImageColorsCmdDataImpl, kImagePrefix + 131)
DECLARE_PMID(kImplementationIDSpace, k16To8BitDepthReducerImpl, kImagePrefix + 132)
DECLARE_PMID(kImplementationIDSpace, kDuotoneInfoImpl, kImagePrefix + 133)
DECLARE_PMID(kImplementationIDSpace, kVirtualImageUtilsImpl, kImagePrefix + 134)
DECLARE_PMID(kImplementationIDSpace, kMergeAlphasImageStreamImpl, kImagePrefix + 135)
DECLARE_PMID(kImplementationIDSpace, kMergeAlphasImageStreamDataImpl, kImagePrefix + 136)
DECLARE_PMID(kImplementationIDSpace, kMapSpotToAlphaImageStreamImpl, kImagePrefix + 137)
DECLARE_PMID(kImplementationIDSpace, kMapSpotToAlphaImageStreamDataImpl, kImagePrefix + 138)

//DECLARE_PMID(kImplementationIDSpace, kImageRenderingObjSuiteImpl, kImagePrefix + 139)
DECLARE_PMID(kImplementationIDSpace, kImageSwatchReferenceDataImpl, kImagePrefix + 139)
DECLARE_PMID(kImplementationIDSpace, kReplaceFPOImageReadDataImpl, kImagePrefix + 140)
DECLARE_PMID(kImplementationIDSpace, kReplaceFPOImageDataImpl, kImagePrefix + 141)

DECLARE_PMID(kImplementationIDSpace, kImageBossInfoImpl, kImagePrefix + 142)

DECLARE_PMID(kImplementationIDSpace, kSetGraphicLayerInfoCmdImpl, kImagePrefix + 143)
DECLARE_PMID(kImplementationIDSpace, kChangeVisibleLayersCmdImpl, kImagePrefix + 144)
DECLARE_PMID(kImplementationIDSpace, kInitializeGraphicLayersCmdImpl, kImagePrefix + 145)

DECLARE_PMID(kImplementationIDSpace, kImageObjectSuiteASBImpl, kImagePrefix + 146)
DECLARE_PMID(kImplementationIDSpace, kImageObjectSuiteLayoutCSBImpl, kImagePrefix + 147)
DECLARE_PMID(kImplementationIDSpace, kImageObjectSuiteSelectionExtImpl, kImagePrefix + 148)
DECLARE_PMID(kImplementationIDSpace, kGraphicLayerOptionsScriptProviderImpl, kImagePrefix + 149)
DECLARE_PMID(kImplementationIDSpace, kGraphicLayerScriptProviderImpl, kImagePrefix + 150)
DECLARE_PMID(kImplementationIDSpace, kGraphicLayerProxyScriptImpl, kImagePrefix + 151)
DECLARE_PMID(kImplementationIDSpace, kImageLinksChangedResponderImpl, kImagePrefix + 152)
DECLARE_PMID(kImplementationIDSpace, kColorConvImgStrmOptionsImpl, kImagePrefix + 153)
DECLARE_PMID(kImplementationIDSpace, kImageSwatchesRIDXNotifierHandlerImpl, kImagePrefix + 154)
DECLARE_PMID(kImplementationIDSpace, kPSDLayerCompScriptProviderImpl, kImagePrefix + 155)
DECLARE_PMID(kImplementationIDSpace, kAGMImageDataImpl, kImagePrefix + 156)
DECLARE_PMID(kImplementationIDSpace, kImagePrivateUtilsImpl, kImagePrefix + 157)

DECLARE_PMID(kImplementationIDSpace, kLinkInfoXMPApertureProviderImpl, kImagePrefix + 158)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoXMPKeywordsProviderImpl, kImagePrefix + 159)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoXMPISOSpeedProviderImpl, kImagePrefix + 160)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoXMPCameraProviderImpl, kImagePrefix + 161)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoXMPShutterProviderImpl, kImagePrefix + 162)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoXMPFocalLengthProviderImpl, kImagePrefix + 163)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoXMPLensProviderImpl, kImagePrefix + 164)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoXMPCaptureDateProviderImpl, kImagePrefix + 165)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoXMPRatingProviderImpl, kImagePrefix + 166)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoUsedSwatchesProviderImpl, kImagePrefix + 167)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoXMPCreditProviderImpl, kImagePrefix + 168)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoXMPDescriptionProviderImpl, kImagePrefix + 169)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoXMPHeadlineProviderImpl, kImagePrefix + 170)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoXMPLocationProviderImpl, kImagePrefix + 171)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoXMPLocationCityProviderImpl, kImagePrefix + 172)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoXMPLocationStateProviderImpl, kImagePrefix + 173)
DECLARE_PMID(kImplementationIDSpace, kLinkInfoXMPLocationCountryProviderImpl, kImagePrefix + 174)
DECLARE_PMID(kImplementationIDSpace, kDeepCutoutManagerImpl, kImagePrefix + 175)
//gap
DECLARE_PMID(kImplementationIDSpace, kImageGraphixCacheImpl, kImagePrefix + 177)


// ImageCache Implementation IDs
DECLARE_PMID(kImplementationIDSpace, kImageCacheImpl, kImagePrefix + 200)
DECLARE_PMID(kImplementationIDSpace, kImageCacheMgrImpl, kImagePrefix + 201)

// <Service ID>
/**********************************************************************
*	SERVICE IDs
**********************************************************************/
DECLARE_PMID(kServiceIDSpace, kImageReadFormatService, kImagePrefix + 1)
DECLARE_PMID(kServiceIDSpace, kImageWriteFormatService, kImagePrefix + 2)
DECLARE_PMID(kServiceIDSpace, kReplaceFPOImageService, kImagePrefix + 3)
DECLARE_PMID(kServiceIDSpace, kImageImportUIDialogService, kImagePrefix + 4)


// <Error ID>
/**********************************************************************
*	Error Codes
**********************************************************************/
DECLARE_PMID(kErrorIDSpace, kImageImportFailedError, kImagePrefix + 1)
DECLARE_PMID(kErrorIDSpace, kImagePlaceFailedError, kImagePrefix + 2)
DECLARE_PMID(kErrorIDSpace, kImageUnsupportedColorSpaceError, kImagePrefix + 3)

// <ViewPortAttr ID>
/**********************************************************************
*	ViewPort Attributes
**********************************************************************/
DECLARE_PMID(kViewPortAttrIDSpace, kNeedsMultipliedAlphaVPAttr, kImagePrefix + 1)
DECLARE_PMID(kViewPortAttrIDSpace, kBMSamplingTypeVPAttr, kImagePrefix + 2)

//
//Script Element IDs
//

//Suites

//Objects
DECLARE_PMID(kScriptInfoIDSpace, kImagePrefsPropertyScriptElement,				kImagePrefix + 18)
DECLARE_PMID(kScriptInfoIDSpace, kImagePrefsObjectScriptElement,				kImagePrefix + 19)
DECLARE_PMID(kScriptInfoIDSpace, kImageIOPrefsObjectScriptElement,				kImagePrefix + 20)
DECLARE_PMID(kScriptInfoIDSpace, kClippingPathObjectScriptElement,				kImagePrefix + 21)
DECLARE_PMID(kScriptInfoIDSpace, kGraphicLayerOptionsObjectScriptElement,		kImagePrefix + 22)
DECLARE_PMID(kScriptInfoIDSpace, kGraphicLayerObjectScriptElement,				kImagePrefix + 23)
DECLARE_PMID(kScriptInfoIDSpace, kPSDLayerCompObjectScriptElement,				kImagePrefix + 24)
DECLARE_PMID(kScriptInfoIDSpace, kPSDLayerCompPropertyScriptElement,			kImagePrefix + 25)
DECLARE_PMID(kScriptInfoIDSpace, kPSDLayerCompAppliedPropertyScriptElement,		kImagePrefix + 26)

//Events
DECLARE_PMID(kScriptInfoIDSpace, kConvertToFrameMethodScriptElement,				kImagePrefix + 50)

//Properties
DECLARE_PMID(kScriptInfoIDSpace, kImageIOPrefsPropertyScriptElement,			kImagePrefix + 120)
DECLARE_PMID(kScriptInfoIDSpace, kCreateClippingFramePropertyScriptElement,		kImagePrefix + 121)
DECLARE_PMID(kScriptInfoIDSpace, kPreviewResolutionPropertyScriptElement,		kImagePrefix + 122)
// formerly: (kScriptInfoIDSpace, kPreviewFormatPropertyScriptElement,			kImagePrefix + 123)
// formerly: (kScriptInfoIDSpace, kExportFormatPropertyScriptElement,			kImagePrefix + 124)
DECLARE_PMID(kScriptInfoIDSpace, kAllowAutoEmbedPropertyScriptElement,			kImagePrefix + 125)
DECLARE_PMID(kScriptInfoIDSpace, kAlphaChannelNamePropertyScriptElement,		kImagePrefix + 126)
DECLARE_PMID(kScriptInfoIDSpace, kRelinkBehaviorPropertyScriptElement,			kImagePrefix + 127)
DECLARE_PMID(kScriptInfoIDSpace, kAlphaOrPathIndexPropertyScriptElement,		kImagePrefix + 128)

DECLARE_PMID(kScriptInfoIDSpace, kClippingPathPropertyScriptElement,			kImagePrefix + 165)
DECLARE_PMID(kScriptInfoIDSpace, kClippingPathTypePropertyScriptElement,		kImagePrefix + 166)
DECLARE_PMID(kScriptInfoIDSpace, kInvertPropertyScriptElement,					kImagePrefix + 167)
DECLARE_PMID(kScriptInfoIDSpace, kIncludeInsideEdgesPropertyScriptElement,		kImagePrefix + 168)
DECLARE_PMID(kScriptInfoIDSpace, kRestrictToFramePropertyScriptElement,			kImagePrefix + 169)
DECLARE_PMID(kScriptInfoIDSpace, kUseHighResolutionImagePropertyScriptElement,	kImagePrefix + 170)
DECLARE_PMID(kScriptInfoIDSpace, kThresholdPropertyScriptElement,				kImagePrefix + 171)
DECLARE_PMID(kScriptInfoIDSpace, kTolerancePropertyScriptElement,				kImagePrefix + 172)
DECLARE_PMID(kScriptInfoIDSpace, kInsetFramePropertyScriptElement,				kImagePrefix + 173)
DECLARE_PMID(kScriptInfoIDSpace, kPSPathNamesPropertyScriptElement,				kImagePrefix + 174)
DECLARE_PMID(kScriptInfoIDSpace, kPathNamePropertyScriptElement,				kImagePrefix + 175)
DECLARE_PMID(kScriptInfoIDSpace, kACPathNamesPropertyScriptElement,				kImagePrefix + 176)

DECLARE_PMID(kScriptInfoIDSpace, kGraphicLayerPropertyScriptElement,			kImagePrefix + 177)
DECLARE_PMID(kScriptInfoIDSpace, kUpdateLinkOptionPropertyScriptElement,		kImagePrefix + 178)
DECLARE_PMID(kScriptInfoIDSpace, kOriginalVisibilityPropertyScriptElement,		kImagePrefix + 179)
DECLARE_PMID(kScriptInfoIDSpace, kCurrentVisibilityPropertyScriptElement,		kImagePrefix + 180)
DECLARE_PMID(kScriptInfoIDSpace, kSeparatorLayerPropertyScriptElement,			kImagePrefix + 181)
DECLARE_PMID(kScriptInfoIDSpace, kAdjustmentLayerPropertyScriptElement,			kImagePrefix + 182)
DECLARE_PMID(kScriptInfoIDSpace, kFXLayerPropertyScriptElement,					kImagePrefix + 183)
DECLARE_PMID(kScriptInfoIDSpace, kViewStatePropertyScriptElement,				kImagePrefix + 184)
DECLARE_PMID(kScriptInfoIDSpace, kExportStatePropertyScriptElement,				kImagePrefix + 185)
DECLARE_PMID(kScriptInfoIDSpace, kPrintStatePropertyScriptElement,				kImagePrefix + 186)
DECLARE_PMID(kScriptInfoIDSpace, kSectionDividerLayerPropertyScriptElement,		kImagePrefix + 187)
DECLARE_PMID(kScriptInfoIDSpace, kHasViewStatePropertyScriptElement,			kImagePrefix + 188)
DECLARE_PMID(kScriptInfoIDSpace, kHasExportStatePropertyScriptElement,			kImagePrefix + 189)
DECLARE_PMID(kScriptInfoIDSpace, kHasPrintStatePropertyScriptElement,			kImagePrefix + 190)

//Enums
// formerly: (kScriptInfoIDSpace, kImageFormatEnumScriptElement,					kImagePrefix + 220)
DECLARE_PMID(kScriptInfoIDSpace, kClippingPathTypeEnumScriptElement,		kImagePrefix + 221)
DECLARE_PMID(kScriptInfoIDSpace, kUpdateLinkOptionEnumScriptElement,		kImagePrefix + 222)


//GUIDS
// {72BF23EF-B70B-4027-B8B3-EBA5C9866999}
#define kImageIOPref_CLSID { 0x72bf23ef, 0xb70b, 0x4027, { 0xb8, 0xb3, 0xeb, 0xa5, 0xc9, 0x86, 0x69, 0x99 } }
// {C54F12A6-BFA4-11d6-AA94-00C04F603A14}
#define kClippingPath_CLSID { 0xc54f12a6, 0xbfa4, 0x11d6, { 0xaa, 0x94, 0x0, 0xc0, 0x4f, 0x60, 0x3a, 0x14 } }
// {A2D02A57-08BD-44d8-B6C3-05ABC76901FA}
#define kGraphicLayerOptions_CLSID { 0xa2d02a57, 0x8bd, 0x44d8, { 0xb6, 0xc3, 0x5, 0xab, 0xc7, 0x69, 0x1, 0xfa } }
// {4B319B39-986A-4faa-B237-FAE05358C994}
#define kGraphicLayer_CLSID { 0x4b319b39, 0x986a, 0x4faa, { 0xb2, 0x37, 0xfa, 0xe0, 0x53, 0x58, 0xc9, 0x94 } }
// {989CE962-8171-4830-815A-E0F363162B82}
#define kGraphicLayers_CLSID { 0x989ce962, 0x8171, 0x4830, { 0x81, 0x5a, 0xe0, 0xf3, 0x63, 0x16, 0x2b, 0x82 } }
// {E740022B-6D86-4d75-B82E-DBF241055D1C}
#define kPSDLayerComp_CLSID { 0xe740022b, 0x6d86, 0x4d75, { 0xb8, 0x2e, 0xdb, 0xf2, 0x41, 0x5, 0x5d, 0x1c } }
// {70D5BAB3-C459-4d58-94B0-1C32CBDD189C}
#define kImagePref_CLSID {0x70d5bab3, 0xc459, 0x4d58, {0x94, 0xb0, 0x1c, 0x32, 0xcb, 0xdd, 0x18, 0x9c } }

//---------------------------------------------------
// InvalHandlerTypeID
//---------------------------------------------------
DECLARE_PMID(kInvalHandlerIDSpace, kImageCacheInvalHandlerID, kImagePrefix + 1)
DECLARE_PMID(kInvalHandlerIDSpace, kProxyInvalHandlerID, kImagePrefix + 2)

// Don't show again warning IDs
#define kNoPhotoshopCompositeWarning									(kImagePrefix + 1)

// Private IIMAGEATTRIBUTES tags
#define kOptimizedImagesTag												(kImagePrefix + 1)

#endif // __ImageID__
