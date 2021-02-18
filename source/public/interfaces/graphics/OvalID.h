//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/OvalID.h $
//  
//  Owner: Lonnie Millett
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

#ifndef __OVALID__
#define __OVALID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kOvalPrefix	 RezLong(0x2300) 

// <Start IDC>
// PluginID
// These no longer exist, combined with BasicTools plug-in.
// Access via kZoomToolPlugInName and kZoomToolPluginID
// #define kOvalPluginName 			"Oval"
// DECLARE_PMID(kPlugInIDSpace, kOvalPluginID, kOvalPrefix + 1)

// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kOvalToolBoss, kOvalPrefix + 2)
DECLARE_PMID(kClassIDSpace, kOvalTrackerBoss, kOvalPrefix + 3)
DECLARE_PMID(kClassIDSpace, kOvalTrackerRegisterBoss, kOvalPrefix + 5)
//gap
DECLARE_PMID(kClassIDSpace, kOvalFrameToolBoss, kOvalPrefix + 7)
DECLARE_PMID(kClassIDSpace, kOvalFrameTrackerBoss, kOvalPrefix + 8)
//gap
DECLARE_PMID(kClassIDSpace, kCreateOvalDialogBoss, kOvalPrefix + 10)

// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IOVALPREFERENCES, kOvalPrefix + 1)

// <Implementation ID>
// ImplementationIIDs
DECLARE_PMID(kImplementationIDSpace, kOvalToolImpl, kOvalPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kOvalTrackerImpl, kOvalPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kOvalTrackerRegisterImpl, kOvalPrefix + 4)
//gap
DECLARE_PMID(kImplementationIDSpace, kOvalFrameToolImpl, kOvalPrefix + 6 )
DECLARE_PMID(kImplementationIDSpace, kOvalFrameTrackerImpl, kOvalPrefix + 7 )
//gap
DECLARE_PMID(kImplementationIDSpace, kCreateOvalDialogControllerImpl, kOvalPrefix + 9)

// <Widget ID>
// WidgetIDs
DECLARE_PMID(kWidgetIDSpace, kOvalToolWidgetId, kOvalPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kOvalFrameToolWidgetId, kOvalPrefix + 2)

// Widget IDs for CreateOval dialog
DECLARE_PMID(kWidgetIDSpace, kCreateOvalParentWidgetID, kOvalPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kOvalWidthEditWidgetID, kOvalPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kOvalHeightEditWidgetID, kOvalPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kOvalWidthTextWidgetID, kOvalPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kOvalHeightTextWidgetID, kOvalPrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kOvalGroupWidgetID, kOvalPrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kOvalGroupTextWidgetID, kOvalPrefix + 9)

// <Action ID>
// ActionIDs
DECLARE_PMID(kActionIDSpace, kOvalToolActionID, kOvalPrefix + 1)
DECLARE_PMID(kActionIDSpace, kOvalFrameToolActionID, kOvalPrefix + 2)

#endif




