//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/MPEGFilterID.h $
//  
//  Owner: dma
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
//  Contains IDs used by the MPEG import filter
//  
//========================================================================================

#ifndef __MPEGFilterID__
#define __MPEGFilterID__


#include "CrossPlatformTypes.h"


#define kMPEGFilterPrefix	RezLong (0x14C00)


// PluginID
#define kMPEGFilterPluginName 				"MPEG Import Filter"
#define kMPEGFilterPluginID 					kMPEGFilterPrefix + 1


// Anna
#define kMPEGFilterAnnaRemoveImpls		kAnnaInitialMinorFormatNumber


// Add one of these for each product version.
#define kMPEGFilterLastAnnaMinorFormat	kMPEGFilterAnnaRemoveImpls


// Overall
#define kMPEGFilterLastFormatChg			kMPEGFilterLastAnnaMinorFormat



// <Implementation ID>
DECLARE_PMID(kImplementationIDSpace, kMPEGReadFormatService, kMPEGFilterPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kMPEGReadFormatInfo, kMPEGFilterPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kMPEGReadFormat, kMPEGFilterPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kMPEGPosterReadFormatImpl, kMPEGFilterPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kMPEGErrorStringServiceImpl, kMPEGFilterPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kMPEGFilterStringRegisterImpl, kMPEGFilterPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kMPEGPosterReadFormatServiceImpl, kMPEGFilterPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kMPEGPosterReadFormatInfoImpl, kMPEGFilterPrefix + 8)


#endif // __MPEGFilterID__
