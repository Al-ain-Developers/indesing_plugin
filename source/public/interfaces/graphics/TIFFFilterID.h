//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/TIFFFilterID.h $
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
//  Contains IDs used by the TIFF format filter
//  
//========================================================================================

#ifndef __TIFFFilterID__
#define __TIFFFilterID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"
#include "FormatNumber.h"

#define kTIFFFilterPrefix	RezLong(0x2a00)

// PluginID
//#define kTIFFFilterPluginName 			"TIFF Filter"
//DECLARE_PMID(kPlugInIDSpace, kTIFFFilterPluginID, kTIFFFilterPrefix + 1)

// ClassIDs
DECLARE_PMID(kClassIDSpace, kTIFFImageReadFormatBoss, kTIFFFilterPrefix + 1)
DECLARE_PMID(kClassIDSpace, kTIFFImageWriteFormatBoss, kTIFFFilterPrefix + 2)
DECLARE_PMID(kClassIDSpace, kTIFFErrorStringServiceBoss, kTIFFFilterPrefix + 3)
DECLARE_PMID(kClassIDSpace, kTIFFImageReadFormat2Boss, kTIFFFilterPrefix + 4)
DECLARE_PMID(kClassIDSpace, kTIFFFilterConversionProviderBoss, kTIFFFilterPrefix + 5)

// ImplementationIDs
DECLARE_PMID(kImplementationIDSpace, kTIFFImageReadFormatServiceImpl, kTIFFFilterPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kTIFFImageReadFormatInfoImpl, kTIFFFilterPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kTIFFImageReadFormatImpl, kTIFFFilterPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kTIFFImageWriteFormatServiceImpl, kTIFFFilterPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kTIFFImageWriteFormatInfoImpl, kTIFFFilterPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kTIFFImageWriteFormatImpl, kTIFFFilterPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kTIFFErrorStringServiceImpl, kTIFFFilterPrefix + 7)


// Error Codes are defined in includes\imerr.h

#endif // __TIFFFilterID__




