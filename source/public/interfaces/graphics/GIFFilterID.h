//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/GIFFilterID.h $
//  
//  Owner: SusanCL
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
//  Contains IDs used by the CompuServe GIF format filter
//  
//========================================================================================

#ifndef __GIFFilterID__
#define __GIFFilterID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kGIFFilterPrefix	RezLong(0x3b00)

// <Start IDC>
// PluginID
//#define kGIFFilterPluginName 			"GIF Filter"
//DECLARE_PMID(kPlugInIDSpace, kGIFFilterPluginID, kGIFFilterPrefix + 1)

// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kGIFImageReadFormatBoss, kGIFFilterPrefix + 1)
DECLARE_PMID(kClassIDSpace, kGIFImageWriteFormatBoss, kGIFFilterPrefix + 2)
//gap
DECLARE_PMID(kClassIDSpace, kGIFFilterConversionProviderBoss, kGIFFilterPrefix + 4)

// <Interface ID>
// Interface IDs
DECLARE_PMID(kInterfaceIDSpace, IID_IGIFIMAGEWRITEOPTIONS, kGIFFilterPrefix + 1)	// LHS

// <Implementation ID>
// ImplementationIDs
DECLARE_PMID(kImplementationIDSpace, kGIFImageReadFormatServiceImpl, kGIFFilterPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kGIFImageReadFormatInfoImpl, kGIFFilterPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kGIFImageReadFormatImpl, kGIFFilterPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kGIFImageWriteFormatServiceImpl, kGIFFilterPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kGIFImageWriteFormatInfoImpl, kGIFFilterPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kGIFImageWriteFormatImpl, kGIFFilterPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kGIFImageWriteOptionsImpl, kGIFFilterPrefix + 7)	// LHS

#endif // __GIFFilterID__

// End, GIFFilterID.h.
