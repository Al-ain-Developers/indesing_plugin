//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/DCSID.h $
//  
//  Owner: David Berggren
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

#ifndef __DCSID_H__
#define __DCSID_H__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"
#include "FormatNumber.h"


//========================================================================================
// Constants for the  plug-in
//========================================================================================

#define 	kDCSPrefix 					RezLong( 0xa600 )		// double check with DeveloperPrefix.h

// <Start IDC>
// PluginID
#define kDCSPluginName 					"DCS Import Filter"
DECLARE_PMID(kPlugInIDSpace, kDCSPluginID, kDCSPrefix + 1)

// boss ids
DECLARE_PMID(kClassIDSpace, kDCSPlaceProviderBoss, kDCSPrefix 	+ 1)
DECLARE_PMID(kClassIDSpace, kDCSConversionProviderBoss, kDCSPrefix 	+ 2)

// implementation ids
DECLARE_PMID(kImplementationIDSpace, kDCSPlaceServiceImpl, kDCSPrefix	+ 1)
DECLARE_PMID(kImplementationIDSpace, kDCSPlaceProviderImpl, kDCSPrefix	+ 2)

#endif
