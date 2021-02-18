//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/SaveBackID.h $
//  
//  Owner: Steve Pellegrin
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
//  Info:	Contains IDs used by the SaveBack plugin.
//  
//========================================================================================

#ifndef __SaveBackID__
#define __SaveBackID__

// ----- Interfaces -----

#include "IDFactory.h"

// ----- Includes -----

#include "CrossPlatformTypes.h"


#define kSaveBackPrefix				RezLong(0x15D00)

// PluginID
#define kSaveBackPluginName 			"SaveBack"
DECLARE_PMID(kPlugInIDSpace, kSaveBackPluginID, kSaveBackPrefix + 1)

// <Class ID>
DECLARE_PMID(kClassIDSpace, kSaveBackExportProviderBoss,					kSaveBackPrefix + 1)
DECLARE_PMID(kClassIDSpace, kSaveBackOpenProviderBoss,						kSaveBackPrefix + 2)
DECLARE_PMID(kClassIDSpace, kSaveBackErrorStringServiceBoss,				kSaveBackPrefix + 3)
DECLARE_PMID(kClassIDSpace, kSaveBackImportValidationBoss,					kSaveBackPrefix + 4)
DECLARE_PMID(kClassIDSpace, kSaveBackImportPolicyBoss,						kSaveBackPrefix + 5)
DECLARE_PMID(kClassIDSpace, kSaveBackExportPolicyBoss,						kSaveBackPrefix + 6)

// <Interface ID>
DECLARE_PMID(kInterfaceIDSpace, IID_ISAVEBACKDEFAULTVERSION,				kSaveBackPrefix + 1)

// <Service ID>
//DECLARE_PMID(kServiceIDSpace, kFutureID, kSaveBackPrefix + 1)


// <Implementation ID>
DECLARE_PMID(kImplementationIDSpace, kSaveBackExportProviderImpl,			kSaveBackPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kSaveBackOpenProviderImpl,				kSaveBackPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kSaveBackErrorStringServiceImpl,		kSaveBackPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kSaveBackImportValidationImpl,			kSaveBackPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kSaveBackImportPolicyImpl,				kSaveBackPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kSaveBackExportPolicyImpl,				kSaveBackPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kSaveBackDefaultVersionImpl,			kSaveBackPrefix + 7)

// <Error ID>

// Import Errors
DECLARE_PMID(kErrorIDSpace, kSaveBackWrongDocType,							kSaveBackPrefix + 1)
DECLARE_PMID(kErrorIDSpace, kSaveBackWrongBuildNumber,						kSaveBackPrefix + 2)

// <Script ID>
//Suites

//Objects

//Events

//Properties

//Enums

#endif	// __SaveBackID__
