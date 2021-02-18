//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/UtilitiesID.h $
//  
//  Owner: Bernd Paradies
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

#ifndef __UtilitiesID__
#define __UtilitiesID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kUtilitiesPrefix	RezLong(0x16200)		// see AdobePrefix.h


// <Start IDC>
// PluginID
#define kUtilitiesPluginName 	"Utilities"
DECLARE_PMID(kPlugInIDSpace, kUtilitiesPluginID, kUtilitiesPrefix + 1)

// <Class ID>
DECLARE_PMID(kClassIDSpace, kPageItemTransformM2MListenerServiceBoss, kUtilitiesPrefix + 1)

// <Implementation ID>
DECLARE_PMID(kImplementationIDSpace, kFrameTypeImpl, kUtilitiesPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kURLUtilsImpl, kUtilitiesPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kAsciiEncodingUtilsImpl, kUtilitiesPrefix + 3) 
DECLARE_PMID(kImplementationIDSpace, kURIUtilsImpl, kUtilitiesPrefix + 4) 
DECLARE_PMID(kImplementationIDSpace, kAutoFindFileUtilsImpl, kUtilitiesPrefix + 5) 
DECLARE_PMID(kImplementationIDSpace, kPageItemTransformM2MListenerImpl, kUtilitiesPrefix + 6) 

// <Action ID>

// <Widget ID>
// Widget IDs

// <Interface ID>
DECLARE_PMID(kInterfaceIDSpace, IID_IFRAMETYPE, kUtilitiesPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IURLUTILS, kUtilitiesPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IASCIIENCODINGUTILS, kUtilitiesPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IURIUTILS, kUtilitiesPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, IID_IAUTOFINDFILEUTILS, kUtilitiesPrefix + 5)

// <Interface ID>
// Interface ID

// <Service ID>
// Service IDs 

// Messages ID


#endif // __UtilitiesID__
