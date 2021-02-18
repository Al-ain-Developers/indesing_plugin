//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/FreeTransformID.h $
//  
//  Owner: jshankar
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
//  Contains IDs used by the free transform tool plug-in
//  
//========================================================================================

#ifndef __FreeTranformID_H__
#define __FreeTranformID_H__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kFreeTransformPrefix RezLong(0xb200) 

// PluginID
#define kFreeTransformPluginName		"FreeTransform"
DECLARE_PMID(kPlugInIDSpace, kFreeTransformPluginID, kFreeTransformPrefix + 1)

// Define your ClassIDs here 
DECLARE_PMID(kClassIDSpace, kFreeTransformToolBoss, kFreeTransformPrefix + 1)
DECLARE_PMID(kClassIDSpace, kFreeTransformTrackerBoss, kFreeTransformPrefix + 2)
// gap
DECLARE_PMID(kClassIDSpace, kFreeTransformTrackerRegisterBoss, kFreeTransformPrefix + 4)
//gap
DECLARE_PMID(kClassIDSpace, kFreeTransformMoveTrackerBoss, kFreeTransformPrefix + 6)
DECLARE_PMID(kClassIDSpace, kFreeTransformMoveToolBoss, kFreeTransformPrefix + 7)
DECLARE_PMID(kClassIDSpace, kFreeTransformRotateTrackerBoss, kFreeTransformPrefix + 8)
DECLARE_PMID(kClassIDSpace, kFreeTransformRotateToolBoss, kFreeTransformPrefix + 9)
DECLARE_PMID(kClassIDSpace, kFreeTransformScaleTrackerBoss, kFreeTransformPrefix + 10)
DECLARE_PMID(kClassIDSpace, kFreeTransformScaleToolBoss, kFreeTransformPrefix + 11)

// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IPOINTINDEX, kFreeTransformPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_ISCALEBOUNDSCHECKER, kFreeTransformPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_ISKEWBOUNDSCHECKER, kFreeTransformPrefix + 3)

// Define your ImplementationIDs here
DECLARE_PMID(kImplementationIDSpace, kFreeTransformToolImpl, kFreeTransformPrefix + 1 )
DECLARE_PMID(kImplementationIDSpace, kFreeTransformCursorProviderImpl, kFreeTransformPrefix + 2 )
DECLARE_PMID(kImplementationIDSpace, kFreeTransformTrackerImpl, kFreeTransformPrefix + 3)
//gap
DECLARE_PMID(kImplementationIDSpace, kFreeTransformTrackerRegisterImpl, kFreeTransformPrefix + 5)
//gap
DECLARE_PMID(kImplementationIDSpace, kFreeTransformMoveTrackerImpl, kFreeTransformPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kFreeTransformRotateTrackerImpl, kFreeTransformPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kFreeTransformScaleTrackerImpl, kFreeTransformPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kFreeTransformSpriteImpl, kFreeTransformPrefix + 10)

// Widget IDs
DECLARE_PMID(kWidgetIDSpace, kFreeTransformToolWidgetId, kFreeTransformPrefix + 1 )

// Action IDs
DECLARE_PMID(kActionIDSpace, kFreeTransformToolActionID, kFreeTransformPrefix + 1 )

#endif // __FreeTranformID_H__
