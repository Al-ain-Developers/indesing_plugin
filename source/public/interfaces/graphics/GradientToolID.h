//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/GradientToolID.h $
//  
//  Owner: charles guy
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
//  Contains IDs used by gradient tool plug-in
//  
//========================================================================================

#ifndef __GradientToolID__
#define __GradientToolID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kGradientToolPrefix	 RezLong(0xA000)

// <Start IDC>
// PluginID
// These no longer exist, combined with BasicTools plug-in.
// Access via kZoomToolPlugInName and kZoomToolPluginID
// #define kGradientToolPluginName 			"GradientTool"
// DECLARE_PMID(kPlugInIDSpace, kGradientToolPluginID, kGradientToolPrefix + 1)

// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kGradientToolBoss, kGradientToolPrefix + 1)
DECLARE_PMID(kClassIDSpace, kGradientToolTrackerBoss, kGradientToolPrefix + 2)
DECLARE_PMID(kClassIDSpace, kGradientToolTrackerRegisterBoss, kGradientToolPrefix + 3)
DECLARE_PMID(kClassIDSpace, kGradientSwatchToolTrackerBoss, kGradientToolPrefix + 4)
DECLARE_PMID(kClassIDSpace, kGradientFeatherToolTrackerBoss, kGradientToolPrefix + 5)
DECLARE_PMID(kClassIDSpace, kGradientFeatherToolBoss, kGradientToolPrefix + 6)


// <Implementation ID>
// ImplementationIDs
DECLARE_PMID(kImplementationIDSpace, kGradientTool, kGradientToolPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kGradientToolTrackerImpl, kGradientToolPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kGradientToolTrackerRegister, kGradientToolPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kGradientSwatchToolTrackerImpl, kGradientToolPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kGradientFeatherToolTrackerImpl, kGradientToolPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kGradientToolSprite, kGradientToolPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kGradientFeatherToolImpl, kGradientToolPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kGradientToolCursorProviderImpl, kGradientToolPrefix + 8)

// <Widget ID>
// WidgetIDs
DECLARE_PMID(kWidgetIDSpace, kGradientToolWidgetId, kGradientToolPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kGradientFeatherToolWidgetId, kGradientToolPrefix + 2)

// <Action ID>
// ActionIDs
DECLARE_PMID(kActionIDSpace, kGradientToolActionID, kGradientToolPrefix + 1)
DECLARE_PMID(kActionIDSpace, kGradientFeatherToolActionID, kGradientToolPrefix + 2)

#endif //__GradientToolID__
