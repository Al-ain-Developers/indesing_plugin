//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/JPEGFilterID.h $
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
//  Contains IDs used by the JPEG format filter
//  
//========================================================================================

#ifndef __JPEGFilterID__
#define __JPEGFilterID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"
#include "FormatNumber.h"

#define kJPEGFilterPrefix	RezLong(0x1D00)

START_IDS()

// PluginID
#define kJPEGFilterPluginName 			"JPEG Filter"
DECLARE_PMID(kPlugInIDSpace, kJPEGFilterPluginID, kJPEGFilterPrefix + 1)

// ClassIDs
DECLARE_PMID(kClassIDSpace, kJPEGImageReadFormatBoss, kJPEGFilterPrefix + 1)
DECLARE_PMID(kClassIDSpace, kJPEGImageWriteFormatBoss, kJPEGFilterPrefix + 2)
//gap
DECLARE_PMID(kClassIDSpace, kJPEGFilterConversionProviderBoss, kJPEGFilterPrefix + 4)

// Interface IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IJPEGIMAGEWRITEOPTIONS, kJPEGFilterPrefix + 1)	// LHS

// Implementation IIDs
DECLARE_PMID(kImplementationIDSpace, kJPEGImageReadFormatServiceImpl, kJPEGFilterPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kJPEGImageReadFormatInfoImpl, kJPEGFilterPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kJPEGImageReadFormatImpl, kJPEGFilterPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kJPEGImageWriteFormatServiceImpl, kJPEGFilterPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kJPEGImageWriteFormatInfoImpl, kJPEGFilterPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kJPEGImageWriteFormatImpl, kJPEGFilterPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kJPEGImageWriteOptionsImpl, kJPEGFilterPrefix + 7)	// LHS
END_IDS()
#endif // __JPEGFilterID__




