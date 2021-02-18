//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/SCTFilterID.h $
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
//  Contains IDs used by the Scitex CT format filter
//  
//========================================================================================

#ifndef __SCTFilterID__
#define __SCTFilterID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kSCTFilterPrefix	RezLong(0x3a00)

// <Start IDC>
// PluginID
//#define kSCTFilterPluginName 			"SCT Filter"
//DECLARE_PMID(kPlugInIDSpace, kSCTFilterPluginID, kSCTFilterPrefix + 1)

// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kSCTImageReadFormatBoss, kSCTFilterPrefix + 1)
DECLARE_PMID(kClassIDSpace, kSCTImageWriteFormatBoss, kSCTFilterPrefix + 2)
//gap
DECLARE_PMID(kClassIDSpace, kSCTFilterConversionProviderBoss, kSCTFilterPrefix + 4)

// <Implementation ID>
// ImplementationIDs
DECLARE_PMID(kImplementationIDSpace, kSCTImageReadFormatServiceImpl, kSCTFilterPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kSCTImageReadFormatInfoImpl, kSCTFilterPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kSCTImageReadFormatImpl, kSCTFilterPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kSCTImageWriteFormatServiceImpl, kSCTFilterPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kSCTImageWriteFormatInfoImpl, kSCTFilterPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kSCTImageWriteFormatImpl, kSCTFilterPrefix + 6)

#endif // __SCTFilterID__

// End, SCTFilterID.h.
