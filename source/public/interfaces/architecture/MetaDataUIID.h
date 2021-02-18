//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/MetaDataUIID.h $
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

#ifndef __MetaDataUIID_h__
#define __MetaDataUIID_h__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kMetaDataUIPrefix	 			RezLong(0x1d500)

// ----- Plug-in ID -----

#define kMetaDataUIPluginName 			"MetaData UI"
DECLARE_PMID(kPlugInIDSpace,			kMetaDataUIPluginID,				kMetaDataUIPrefix + 1)

// ----- Class IDs -----

DECLARE_PMID(kClassIDSpace,				kMetaDataActionBoss,				kMetaDataUIPrefix + 1)

// ----- Interface IDs -----

DECLARE_PMID(kInterfaceIDSpace,			IID_IMETADATAUIUTILS,				kMetaDataUIPrefix + 1)

// ----- Implementatin IDs -----

DECLARE_PMID(kImplementationIDSpace,	kMetaDataActionComponentImpl,		kMetaDataUIPrefix + 1)
DECLARE_PMID(kImplementationIDSpace,	kMetaDataUIUtilsImpl,				kMetaDataUIPrefix + 2)

// ----- Widget IDs -----

// ----- Action IDs -----

// ----- Service IDs -----

//
//Script Element IDs
//

//Suites

#endif // __MetaDataUIID_h__
