//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/InCopyImportID.h $
//  
//  Owner: Frank Rubino
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
//  IDs used by InCopyImport
//  
//========================================================================================

#ifndef __InCopyImportID__
#define __InCopyImportID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kInCopyImportPrefix			RezLong(0x17100)

//----------------------------------------------------------------------------------------
// Plug-in identifier
//----------------------------------------------------------------------------------------

#define kInCopyImportPluginName 	"InCopyImport"
DECLARE_PMID(kPlugInIDSpace, kInCopyImportPluginID, kInCopyImportPrefix + 1)

//----------------------------------------------------------------------------------------
// Class identifiers
//----------------------------------------------------------------------------------------

DECLARE_PMID(kClassIDSpace,			kInCopyImportProviderBoss,			kInCopyImportPrefix + 1)
DECLARE_PMID(kClassIDSpace,			kInCopyImportStringRegisterBoss,	kInCopyImportPrefix + 3)


//----------------------------------------------------------------------------------------
// Interface identifiers
//----------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------
// Implementation identifiers
//----------------------------------------------------------------------------------------

DECLARE_PMID(kImplementationIDSpace, kInCopyImportServiceImpl,		kInCopyImportPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kInCopyImportProviderImpl,		kInCopyImportPrefix + 2)

//----------------------------------------------------------------------------------------
// Widget identifiers
//----------------------------------------------------------------------------------------

//DECLARE_PMID(kWidgetIDSpace,	kXMLPanelWidgetID,					kXMediaUIPrefix + 1)


//----------------------------------------------------------------------------------------
// Action identifiers
//----------------------------------------------------------------------------------------

//DECLARE_PMID(kActionIDSpace,	kXMLPanelActionID,				kXMediaUIPrefix + 1)

//----------------------------------------------------------------------------------------
// Service Provider IDs
//----------------------------------------------------------------------------------------

//DECLARE_PMID(kServiceIDSpace,	kStructureDDTargetFlavorHelperService, kXMediaUIPrefix + 1)


#endif // __InCopyImportID__
