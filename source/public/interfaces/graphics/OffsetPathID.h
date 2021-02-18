//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/OffsetPathID.h $
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
//  Contains IDs used by the offsetpath item plug-in
//  
//========================================================================================

#ifndef __OffsetPathID__
#define __OffsetPathID__
#include "CrossPlatformTypes.h"

#define kOffsetPathPrefix			RezLong(0x7a00)	
#include "IDFactory.h"

// <Start IDC>
// PluginID
#define kOffsetPathPluginName 		"Text Wrap Path"
DECLARE_PMID(kPlugInIDSpace, kOffsetPathPluginID, kOffsetPathPrefix + 1)

// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kOffsetPathBoss, kOffsetPathPrefix + 1)
DECLARE_PMID(kClassIDSpace, kOffsetPathTempPathGeometry, kOffsetPathPrefix + 2)

// <Implementation ID>
// Implementation IDs
DECLARE_PMID(kImplementationIDSpace, kOffsetPathImpl, kOffsetPathPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kPathFinderImpl, kOffsetPathPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kPSPathFinderImpl, kOffsetPathPrefix + 3)

// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IOFFSETPATH, kOffsetPathPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IPATHFINDER, kOffsetPathPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IPSPATHFINDER, kOffsetPathPrefix + 3)

#endif // __OffsetPathID__






