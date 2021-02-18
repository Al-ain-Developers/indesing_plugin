//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/GraphicsID.h $
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
//  
//  Contains IDs used by the graphics sub-system.
//  
//========================================================================================

#ifndef __GRAPHICSID__
#define __GRAPHICSID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kGraphicsPrefix	 RezLong(0x1600)

// <Start IDC>
// <Class ID>
// ClassIDs
//GAP
DECLARE_PMID(kClassIDSpace, kDV_OffscreenViewPortBoss, kGraphicsPrefix + 8)

//GAP
DECLARE_PMID(kClassIDSpace, kPlatformGraphicsContextBoss, kGraphicsPrefix + 12)
DECLARE_PMID(kClassIDSpace, kAGMImageViewPortBoss, kGraphicsPrefix + 13)
DECLARE_PMID(kClassIDSpace, kDrawServicesBoss, kGraphicsPrefix + 15)
DECLARE_PMID(kClassIDSpace, kPathPortBoss, kGraphicsPrefix + 16)
DECLARE_PMID(kClassIDSpace, kDrawMgrBoss, kGraphicsPrefix + 17)
//GAP
DECLARE_PMID(kClassIDSpace, kAGMGraphixCaptureViewPortBoss, kGraphicsPrefix + 20)
DECLARE_PMID(kClassIDSpace, kGfxTreeIncrementalDrawServicesBoss, kGraphicsPrefix + 21)
DECLARE_PMID(kClassIDSpace, kAGMGraphixCaptureIncrViewPortBoss, kGraphicsPrefix + 22)



	// Messages sent by ViewPort
	// -- these are ClassIDs but have no classes!
	// -- they are only used for sending messages
DECLARE_PMID(kMessageIDSpace, kMsgShapeChangedBoss, kGraphicsPrefix + 15)	// sent by commands that change the shape (see StandOffSelectionObserver)

DECLARE_PMID(kMessageIDSpace, kMaskGeneratingViewPortBoss, kGraphicsPrefix + 16)

// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IVIEWPORT, kGraphicsPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IVIEWPORTATTRIBUTES, kGraphicsPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICSPORT, kGraphicsPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, IID_IRASTERPORT, kGraphicsPrefix + 6)
DECLARE_PMID(kInterfaceIDSpace, IID_IRASTERPORTSETUP, kGraphicsPrefix + 7)
DECLARE_PMID(kInterfaceIDSpace, IID_ISYSTEMPORT, kGraphicsPrefix + 8)
DECLARE_PMID(kInterfaceIDSpace, IID_IDISPLAYLISTDRAWINFO, kGraphicsPrefix + 9)

//GAP
DECLARE_PMID(kInterfaceIDSpace, IID_IWINDOWPORT, kGraphicsPrefix + 14)
// gapDECLARE_PMID(kInterfaceIDSpace, IID_IFONTMGR, kGraphicsPrefix + 16 )
DECLARE_PMID(kInterfaceIDSpace, IID_IOFFSCREENPORTDATA, kGraphicsPrefix + 22)
DECLARE_PMID(kInterfaceIDSpace, IID_IOFFSCREENPORTDATA_NEW, kGraphicsPrefix + 23)
DECLARE_PMID(kInterfaceIDSpace, IID_ISPRITE, kGraphicsPrefix + 24)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICSCONTEXTARBITRATOR, kGraphicsPrefix + 25)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICSCONTEXT, kGraphicsPrefix + 26)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICSCONTEXTSYSHELPER, kGraphicsPrefix + 27)
DECLARE_PMID(kInterfaceIDSpace, IID_IDRAWMGR, kGraphicsPrefix + 28)
DECLARE_PMID(kInterfaceIDSpace, IID_IDRWEVTDISPATCHER, kGraphicsPrefix + 29)
DECLARE_PMID(kInterfaceIDSpace, IID_IDRWEVTHANDLER, kGraphicsPrefix + 30)
DECLARE_PMID(kInterfaceIDSpace, IID_IPATHSTORAGE, kGraphicsPrefix + 31)
DECLARE_PMID(kInterfaceIDSpace, IID_IPATHPAGEITEM, kGraphicsPrefix + 32)
DECLARE_PMID(kInterfaceIDSpace, IID_IAGMIMAGEPORT, kGraphicsPrefix + 33)
DECLARE_PMID(kInterfaceIDSpace, IID_IPATHPORT, kGraphicsPrefix + 34)
DECLARE_PMID(kInterfaceIDSpace, IID_IPATHDATA, kGraphicsPrefix + 35)
DECLARE_PMID(kInterfaceIDSpace, IID_IPATHSTROKER, kGraphicsPrefix + 36)
DECLARE_PMID(kInterfaceIDSpace, IID_IPATHENDSTROKER, kGraphicsPrefix + 37)
DECLARE_PMID(kInterfaceIDSpace, IID_IPATHCORNER, kGraphicsPrefix + 38)
DECLARE_PMID(kInterfaceIDSpace, IID_IOFFSCREENVIEWPORTCACHE, kGraphicsPrefix + 39 )
DECLARE_PMID(kInterfaceIDSpace, IID_IAGMPORTDATA, kGraphicsPrefix + 40)
DECLARE_PMID(kInterfaceIDSpace, IID_ITABLESTRIPEPATHSTROKER, kGraphicsPrefix + 41)
DECLARE_PMID(kInterfaceIDSpace, IID_IDVOFFSCREENPORTDATA, kGraphicsPrefix + 42)
DECLARE_PMID(kInterfaceIDSpace, IID_IDVOFFSCREENVIEWPORTCACHE, kGraphicsPrefix + 43)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IVIEWPORTATTRIBUTESMAP, kGraphicsPrefix + 46)
DECLARE_PMID(kInterfaceIDSpace, IID_IGFXCAPTUREPORT, kGraphicsPrefix + 47)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICVISIBILITYUTILS, kGraphicsPrefix + 48)
DECLARE_PMID(kInterfaceIDSpace, IID_IGFXINCREMENTALDRAWSTATE, kGraphicsPrefix + 49)
//DECLARE_PMID(kInterfaceIDSpace, IID_ISHAPEGRAPHIX, kGraphicsPrefix + 50)
DECLARE_PMID(kInterfaceIDSpace, IID_ISHAPEGRAFIXCACHE, kGraphicsPrefix + 51)
DECLARE_PMID(kInterfaceIDSpace, IID_ISUPPRESSSMARTGUIDES, kGraphicsPrefix + 52)
DECLARE_PMID(kInterfaceIDSpace, IID_IREDRAWSPRITEBACKGROUND, kGraphicsPrefix + 53)
//gap

// Page Item definitions begin at 200
DECLARE_PMID(kInterfaceIDSpace, IID_IGEOMETRY, kGraphicsPrefix + 200)
//DECLARE_PMID(kInterfaceIDSpace, IID_ICONTROLPOINTS, kGraphicsPrefix + 201)
DECLARE_PMID(kInterfaceIDSpace, IID_ISHAPE, kGraphicsPrefix + 202)
DECLARE_PMID(kInterfaceIDSpace, IID_IHANDLESHAPE, kGraphicsPrefix + 203)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICFRAMEDATA, kGraphicsPrefix + 205)
//gap
DECLARE_PMID(kInterfaceIDSpace, IID_IPATHGEOMETRY, kGraphicsPrefix + 207)
DECLARE_PMID(kInterfaceIDSpace, IID_IWINDOWPORTDATA, kGraphicsPrefix + 208)
DECLARE_PMID(kInterfaceIDSpace, IID_IVIEWPORTARBITRATOR, kGraphicsPrefix + 209)
DECLARE_PMID(kInterfaceIDSpace, IID_IQUARTZCONTEXTPORTDATA,		kGraphicsPrefix + 210 )
DECLARE_PMID(kInterfaceIDSpace, IID_IPATHHANDLESHAPE, kGraphicsPrefix + 211)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICBOUNDS, kGraphicsPrefix + 212)
DECLARE_PMID(kInterfaceIDSpace, IID_IPOINTSELECTORDATA, kGraphicsPrefix + 213)
DECLARE_PMID(kInterfaceIDSpace, IID_IPORTERROR, kGraphicsPrefix + 214) // IIntData is interface
DECLARE_PMID(kInterfaceIDSpace, IID_IAGMIMAGERECORDDATA, kGraphicsPrefix + 215)


//DECLARE_PMID(kInterfaceIDSpace, IID_IFTHANDLESHAPE, kGraphicsPrefix + 215)
//DECLARE_PMID(kInterfaceIDSpace, IID_IFREETRANSFORMDATA, kGraphicsPrefix + 216)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICATTRIBUTEUTILS, kGraphicsPrefix + 217)
DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICSTATEUTILS, kGraphicsPrefix + 218)
//DECLARE_PMID(kInterfaceIDSpace, IID_IGRAPHICMETADATAUTILS, kGraphicsPrefix + 219)



DECLARE_PMID(kInterfaceIDSpace, IID_IPATHGEOMETRY_DOCUMENT, kGraphicsPrefix + 255)

// <Implementation ID>
// ImplementationIIDs
DECLARE_PMID(kImplementationIDSpace, kGenericRasterPortImpl, kGraphicsPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kViewPortAttributesImpl, kGraphicsPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kAGMViewPortAttributesImpl, kGraphicsPrefix + 5)

//GAP
DECLARE_PMID(kImplementationIDSpace, kDisplayListDrawInfoImpl, kGraphicsPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kPathStorageImpl, kGraphicsPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kAGMImageViewPortImpl, kGraphicsPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kMultiplexViewPortImpl, kGraphicsPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kMultiplexGraphicsPortImpl, kGraphicsPrefix + 16	)
//gap
DECLARE_PMID(kImplementationIDSpace, kCRectHandleShapeImpl, kGraphicsPrefix + 19)
//GAP
DECLARE_PMID(kImplementationIDSpace, kGenericGraphicsPortImpl, kGraphicsPrefix + 21)
DECLARE_PMID(kImplementationIDSpace, kGraphicsContextArbitratorImpl, kGraphicsPrefix + 22)
DECLARE_PMID(kImplementationIDSpace, kDrawMgrImpl, kGraphicsPrefix + 23)
DECLARE_PMID(kImplementationIDSpace, kIDrwEvtDispatcherImpl, kGraphicsPrefix + 24)
DECLARE_PMID(kImplementationIDSpace, kPointSelectorDataImpl, kGraphicsPrefix + 25)
//GAP
DECLARE_PMID(kImplementationIDSpace, kQDGraphicsContextImpl, kGraphicsPrefix + 28)
DECLARE_PMID(kImplementationIDSpace, kGraphicsContextSysHelperImpl, kGraphicsPrefix + 29)
DECLARE_PMID(kImplementationIDSpace, kViewPortImpl, kGraphicsPrefix + 30)
DECLARE_PMID(kImplementationIDSpace, kCHandleShapeImpl, kGraphicsPrefix + 31)
DECLARE_PMID(kImplementationIDSpace, kCClipDataImpl_Obsolete, kGraphicsPrefix + 32)
DECLARE_PMID(kImplementationIDSpace, kCGeometryImpl, kGraphicsPrefix + 33)
DECLARE_PMID(kImplementationIDSpace, kPathPageItemImpl, kGraphicsPrefix + 34)
DECLARE_PMID(kImplementationIDSpace, kCGraphicFrameDataImpl, kGraphicsPrefix + 35)
DECLARE_PMID(kImplementationIDSpace, kDrawServiceImpl, kGraphicsPrefix + 36)
DECLARE_PMID(kImplementationIDSpace, kDrawStartupShutdownImpl, kGraphicsPrefix + 37)
DECLARE_PMID(kImplementationIDSpace, kDrwEvtHandlerImpl, kGraphicsPrefix + 38)
DECLARE_PMID(kImplementationIDSpace, kCPathShapeImpl, kGraphicsPrefix + 39)
DECLARE_PMID(kImplementationIDSpace, kCGraphicFrameShapeImpl, kGraphicsPrefix + 42)
DECLARE_PMID(kImplementationIDSpace, kPathGeometryImpl, kGraphicsPrefix + 43)
DECLARE_PMID(kImplementationIDSpace, kOffscreenViewPortCacheImpl, kGraphicsPrefix + 44)
DECLARE_PMID(kImplementationIDSpace, kOffscreenCacheObserverImpl, kGraphicsPrefix + 45)
DECLARE_PMID(kImplementationIDSpace, kNoHandleSpriteImpl, kGraphicsPrefix + 46)

DECLARE_PMID(kImplementationIDSpace, kWindowPortDataImpl, kGraphicsPrefix + 47)
DECLARE_PMID(kImplementationIDSpace, kViewPortArbitratorImpl, kGraphicsPrefix + 49)
DECLARE_PMID(kImplementationIDSpace, kOffscreenPortDataImpl, kGraphicsPrefix + 50)

DECLARE_PMID(kImplementationIDSpace, kGraphicBoundsImpl, kGraphicsPrefix + 51)
DECLARE_PMID(kImplementationIDSpace, kAGMPortDataImpl, kGraphicsPrefix + 52)
DECLARE_PMID(kImplementationIDSpace, kPathGeometryImpl2, kGraphicsPrefix + 53)

//DECLARE_PMID(kImplementationIDSpace, kCFTHandleShapeImpl, kGraphicsPrefix + 54)
DECLARE_PMID(kImplementationIDSpace, kNoHandleAndCrossSpriteImpl, kGraphicsPrefix + 55)
DECLARE_PMID(kImplementationIDSpace, kAGMImageRecordDataImpl, kGraphicsPrefix + 56)
DECLARE_PMID(kImplementationIDSpace, kMaskGeneratingGraphicsPortImpl, kGraphicsPrefix + 57)
//DECLARE_PMID(kImplementationIDSpace, kFreeTransformDataImpl, kGraphicsPrefix + 58)
DECLARE_PMID(kImplementationIDSpace, kCGraphicHandleShapeImpl, kGraphicsPrefix + 60)

DECLARE_PMID(kImplementationIDSpace, kGraphicAttributeUtilsImpl, kGraphicsPrefix + 61)
DECLARE_PMID(kImplementationIDSpace, kGraphicStateUtilsImpl, kGraphicsPrefix + 62)
DECLARE_PMID(kImplementationIDSpace, kGraphicMetaDataUtilsImpl, kGraphicsPrefix + 63)

DECLARE_PMID(kImplementationIDSpace, kOffscreenPortData_NEWImpl, kGraphicsPrefix + 70)
DECLARE_PMID(kImplementationIDSpace, kQuartzContextPortDataImpl, kGraphicsPrefix + 71)

DECLARE_PMID(kImplementationIDSpace, kDV_OffscreenPortDataImpl, kGraphicsPrefix + 72)
DECLARE_PMID(kImplementationIDSpace, kDVOffscreenViewPortCacheImpl, kGraphicsPrefix + 73)

//gap
DECLARE_PMID(kImplementationIDSpace, kMapBasedViewPortAttributesImpl, kGraphicsPrefix + 76)
DECLARE_PMID(kImplementationIDSpace, kViewPortAttributesMapImpl, kGraphicsPrefix + 77)
DECLARE_PMID(kImplementationIDSpace, kGfxTreeIncDrwEvtHndlerImpl, kGraphicsPrefix + 78)
DECLARE_PMID(kImplementationIDSpace, kGfxCaptureRasterPortImpl, kGraphicsPrefix + 79)
DECLARE_PMID(kImplementationIDSpace, kGfxCapturePortImpl, kGraphicsPrefix + 80)
DECLARE_PMID(kImplementationIDSpace, kGfxVisibiltyUtilsImpl, kGraphicsPrefix + 81)
DECLARE_PMID(kImplementationIDSpace, kGfxTreeIncrementalDrawServiceImpl, kGraphicsPrefix + 82)
DECLARE_PMID(kImplementationIDSpace, kGfxIncrementalDrawStateImpl, kGraphicsPrefix + 83)
DECLARE_PMID(kImplementationIDSpace, kShapeGraphixCacheImpl, kGraphicsPrefix + 84)
DECLARE_PMID(kImplementationIDSpace, kTopSplineGraphixCacheImpl, kGraphicsPrefix + 85)





// <Service ID>
//	Service IDs
DECLARE_PMID(kServiceIDSpace, kPrintEventService, kGraphicsPrefix + 1)
DECLARE_PMID(kServiceIDSpace, kDrawEventService, kGraphicsPrefix + 2)
DECLARE_PMID(kServiceIDSpace, kRasterPortSetupService, kGraphicsPrefix + 3)

#endif // __GraphicsID__




