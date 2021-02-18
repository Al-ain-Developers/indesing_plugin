//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/XCopyID.h $
//  
//  Owner: Chris Parrish
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
//  IDs used by XCopy
//  
//========================================================================================

#ifndef __XCopyID__
#define __XCopyID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kXCopyPrefix			RezLong(0xfe00)  //TODO: Get real ID if needed...this is a keystone ID

//----------------------------------------------------------------------------------------
// Plug-in identifier
//----------------------------------------------------------------------------------------

#define kXCopyPluginName 	"XCopy"
DECLARE_PMID(kPlugInIDSpace, kXCopyPluginID, kXCopyPrefix + 1)

//----------------------------------------------------------------------------------------
// Class identifiers
//----------------------------------------------------------------------------------------

//Plugin
//gap
DECLARE_PMID(kClassIDSpace,			kXCopyTestMenuComponentBoss,    kXCopyPrefix + 2)
DECLARE_PMID(kClassIDSpace,			kXCopyPagePreviewBoss,    		kXCopyPrefix + 3)
//DECLARE_PMID(kClassIDSpace,		kXMediaUIActionRegisterBoss,	kXMediaUIPrefix + 3)
//DECLARE_PMID(kClassIDSpace,		kXMediaUIMenuRegisterBoss,		kXMediaUIPrefix + 4)


//----------------------------------------------------------------------------------------
// Interface identifiers
//----------------------------------------------------------------------------------------

DECLARE_PMID(kInterfaceIDSpace,	IID_IPAGEPREVIEW,					kXCopyPrefix + 1)


//----------------------------------------------------------------------------------------
// Implementation identifiers
//----------------------------------------------------------------------------------------

DECLARE_PMID(kImplementationIDSpace, kXCopyActionImpl,				kXCopyPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kPagePreviewImpl,				kXCopyPrefix + 2)


//----------------------------------------------------------------------------------------
// Widget identifiers
//----------------------------------------------------------------------------------------

//DECLARE_PMID(kWidgetIDSpace,	kXMLPanelWidgetID,					kXMediaUIPrefix + 1)


//----------------------------------------------------------------------------------------
// Action identifiers
//----------------------------------------------------------------------------------------

//DECLARE_PMID(kActionIDSpace,	kXMLPanelActionID,				kXMediaUIPrefix + 1)

//----------------------------------------------------------------------------------------
// Servide Provider IDs
//----------------------------------------------------------------------------------------

//DECLARE_PMID(kServiceIDSpace,	kStructureDDTargetFlavorHelperService, kXMediaUIPrefix + 1)


#endif // __XMediaUIID__
