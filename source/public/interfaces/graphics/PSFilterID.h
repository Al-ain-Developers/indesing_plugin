//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/PSFilterID.h $
//  
//  Owner: twright
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
//  Contains IDs used by the Photoshop format filter
//  
//========================================================================================

#ifndef __PSFilterID__
#define __PSFilterID__

#include "IDFactory.h"

#define kPSFilterPrefix	RezLong(0x9200)


// PluginID
#define kPSFilterPluginName 				"Photoshop Import Filter"
START_IDS()

DECLARE_PMID(kPlugInIDSpace, kPSFilterPluginID, kPSFilterPrefix + 1)

// <Class ID>
DECLARE_PMID(kClassIDSpace, kPSImageReadFormatBoss, kPSFilterPrefix + 1)
//DECLARE_PMID(kClassIDSpace, kPSImageWriteFormatBoss, kPSFilterPrefix + 2)
DECLARE_PMID(kClassIDSpace, kPSErrorStringServiceBoss, kPSFilterPrefix + 3)
//gap
DECLARE_PMID(kClassIDSpace, kPSFilterConversionProviderBoss, kPSFilterPrefix + 5)
DECLARE_PMID(kClassIDSpace, kPSDPreviewBoss, kPSFilterPrefix + 6)
DECLARE_PMID(kClassIDSpace, kPSLStartupShutdownBoss, kPSFilterPrefix + 7)
DECLARE_PMID(kClassIDSpace, kPSDVersionBoss, kPSFilterPrefix + 8)

DECLARE_PMID(kClassIDSpace, kPSLMemoryCleanupIdleTaskBoss, kPSFilterPrefix + 9)

DECLARE_PMID(kClassIDSpace, kPSDLayerCompInfoConversionProviderBoss, kPSFilterPrefix + 10)

// <Interface ID>
DECLARE_PMID(kInterfaceIDSpace, IID_IPSDLAYERCOMPINFO, kPSFilterPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IPSCLIPPINGPATHUTILS, kPSFilterPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IPSDPREVIEW, kPSFilterPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IPRIVATEPSDUTILS, kPSFilterPrefix + 4)


// <Implementation ID>
DECLARE_PMID(kImplementationIDSpace, kPSImageReadFormatService, kPSFilterPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kPSImageReadFormatInfo, kPSFilterPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kPSImageReadFormat, kPSFilterPrefix + 3)
//DECLARE_PMID(kImplementationIDSpace, kPSImageWriteFormatServiceImpl, kPSFilterPrefix + 4)
//DECLARE_PMID(kImplementationIDSpace, kPSImageWriteFormatInfoImpl, kPSFilterPrefix + 5)
//DECLARE_PMID(kImplementationIDSpace, kPSImageWriteFormatImpl, kPSFilterPrefix + 6)
#ifdef DEBUG
DECLARE_PMID(kImplementationIDSpace, kPSDTestMenuBoss, kPSFilterPrefix + 6)
#endif
DECLARE_PMID(kImplementationIDSpace, kPSErrorStringServiceImpl, kPSFilterPrefix + 7)
#ifdef DEBUG
DECLARE_PMID(kImplementationIDSpace, kPSDTestMenuImpl, kPSFilterPrefix + 8)
#endif
DECLARE_PMID(kImplementationIDSpace, kPSDLayerCompInfoImpl, kPSFilterPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kPSClippingPathUtilsImpl, kPSFilterPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kPSDPreviewImpl, kPSFilterPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kPSLStartupShutdownImpl, kPSFilterPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kPSDComponentVersionImpl, kPSFilterPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kPSDComponentVersionServiceImpl, kPSFilterPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kPrivatePSDUtilsImpl, kPSFilterPrefix + 15)

DECLARE_PMID(kImplementationIDSpace, kPSLMemoryCleanupIdleTaskImpl, kPSFilterPrefix + 16)

DECLARE_PMID(kImplementationIDSpace, kPSDLayerCompInfoConversionProviderImpl, kPSFilterPrefix + 17)

END_IDS()
#endif // __PSFilterID__




