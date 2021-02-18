//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/JPEGCodecID.h $
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
//========================================================================================

#ifndef __JPEGCodec__
#define __JPEGCodec__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kJPEGCodecPrefix	RezLong(0x1C00)

// <Start IDC>
// PluginID
//#define kJPEGCodecPluginName 		"JPEG Compression"
//DECLARE_PMID(kPlugInIDSpace, kJPEGCodecPluginID, kJPEGCodecPrefix + 1)

// <Class ID>
// Class IDs
DECLARE_PMID(kClassIDSpace, kJPEGEncoderBoss, kJPEGCodecPrefix + 1)
DECLARE_PMID(kClassIDSpace, kJPEGDecoderBoss, kJPEGCodecPrefix + 2)
//gap
DECLARE_PMID(kClassIDSpace, kJPEGCodecStringServiceBoss, kJPEGCodecPrefix + 4)

// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IJPEGENCODER, kJPEGCodecPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IJPEGDECODER, kJPEGCodecPrefix + 2)

// <Implementation ID>
// ImplementationIIDs
DECLARE_PMID(kImplementationIDSpace, kJPEGEncoderImpl, kJPEGCodecPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kJPEGDecoderImpl, kJPEGCodecPrefix + 2)
//gap
DECLARE_PMID(kImplementationIDSpace, kJPEGCodecErrorStringServiceImpl, kJPEGCodecPrefix + 4)


#endif
