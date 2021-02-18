//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ColorSpaceID.h $
//  
//  Owner: fhaberma
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

#ifndef __ColorSpaceID__
#define __ColorSpaceID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kColorSpacePrefix	 RezLong(0x7f00)		//Refer also to AdobePrefix.h

// <Start IDC>
// PluginID
#define kColorSpacePluginName 				"ColorSpace"
DECLARE_PMID(kPlugInIDSpace, kColorSpacePluginID, kColorSpacePrefix + 1)

// <Class ID>
// ClassIDs (i.e. bosses)
DECLARE_PMID(kClassIDSpace, kColorSpaceServiceBoss, kColorSpacePrefix + 1)
DECLARE_PMID(kClassIDSpace, kDefaultCSStartupBoss, kColorSpacePrefix + 2)

// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_ICOLORSPACEMGR, kColorSpacePrefix + 1)

// <Implementation ID>
// Implementation IIDs (i.e. C++ classes)
DECLARE_PMID(kImplementationIDSpace, kDefaultColorSpaceMgrImpl, kColorSpacePrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kDefaultColorSpaceMgrServiceImpl, kColorSpacePrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kDefaultColorConverterImpl, kColorSpacePrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kDefaultCSStartupServiceImpl, kColorSpacePrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kDefaultCSStartupShutdownImpl, kColorSpacePrefix + 5)

// <Service ID>
//	Service IDs
DECLARE_PMID(kServiceIDSpace, kColorSpaceMgrService, kColorSpacePrefix + 1)

#endif	//__ColorSpaceID__

