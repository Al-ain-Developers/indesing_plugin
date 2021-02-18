//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/DataServicesID.h $
//  
//  Owner: Michael Burbidge
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

#ifndef __DataServicesID_h__
#define __DataServicesID_h__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kDataServicesPrefix	 		RezLong(0x1aa00)

// ----- Plug-in ID -----

#define kDataServicesPluginName 		"DataServices"
DECLARE_PMID(kPlugInIDSpace,			kDataServicesPluginID,				kDataServicesPrefix + 1)

// ----- Class IDs -----

DECLARE_PMID(kClassIDSpace, 			kDataServicesBoss,					kDataServicesPrefix + 1)
DECLARE_PMID(kClassIDSpace, 			kDataServicesAttributesBoss,		kDataServicesPrefix + 2)

// ----- Interface IDs -----

DECLARE_PMID(kInterfaceIDSpace, 		IID_IDATASERVICES,					kDataServicesPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, 		IID_IDATATRANSFORM,					kDataServicesPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, 		IID_IDATATRANSFORMDATA,				kDataServicesPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, 		IID_IDATAREGISTRY,					kDataServicesPrefix + 4)
DECLARE_PMID(kInterfaceIDSpace, 		IID_IDATASERVICESOPTIONS,			kDataServicesPrefix + 5)
DECLARE_PMID(kInterfaceIDSpace, 		IID_IDATATRANSFORMPARAMS,			kDataServicesPrefix + 6)

// ----- Implementatin IDs -----

DECLARE_PMID(kImplementationIDSpace,	kDataServicesImpl, 					kDataServicesPrefix + 1)
DECLARE_PMID(kImplementationIDSpace,	kDataServicesServiceImpl, 			kDataServicesPrefix + 2)
DECLARE_PMID(kImplementationIDSpace,	kDataRegistryImpl, 					kDataServicesPrefix + 3)
DECLARE_PMID(kImplementationIDSpace,	kDataServicesOptionsImpl, 			kDataServicesPrefix + 4)
DECLARE_PMID(kImplementationIDSpace,	kDataServicesAttributesImpl, 		kDataServicesPrefix + 5)

// ----- Widget IDs -----

// ----- Action IDs -----

// ----- Service IDs -----

DECLARE_PMID(kServiceIDSpace, 			kDataServices, 						kDataServicesPrefix + 1)
DECLARE_PMID(kServiceIDSpace, 			kDataTransformService, 				kDataServicesPrefix + 2)

#endif // __DataServicesID_h__
