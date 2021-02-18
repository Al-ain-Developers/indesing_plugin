//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/RectID.h $
//  
//  Owner: Robin_Briggs
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
//  Contains IDs used by the rect item plug-in
//  
//========================================================================================

#ifndef __RECTID__
#define __RECTID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

DECLARE_PMID(kActionIDSpace, kRectanglePrefix, RezLong(0x900))

// <Start IDC>
// PluginID
// These no longer exist, combined with BasicTools plug-in.
// Access via kZoomToolPlugInName and kZoomToolPluginID
// #define kRectanglePluginName		"Rectangle"
// DECLARE_PMID(kPlugInIDSpace, kRectanglePluginID, kRectanglePrefix + 1)

// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kRectToolBoss, kRectanglePrefix + 1)
DECLARE_PMID(kClassIDSpace, kRectangleTrackerBoss, kRectanglePrefix + 2)
DECLARE_PMID(kClassIDSpace, kRectTrackerRegisterBoss, kRectanglePrefix + 3)
//gap
DECLARE_PMID(kClassIDSpace, kRectFrameToolBoss, kRectanglePrefix + 5)
DECLARE_PMID(kClassIDSpace, kRectangleFrameTrackerBoss, kRectanglePrefix + 6)
//gap
DECLARE_PMID(kClassIDSpace, kCreateRectDialogBoss, kRectanglePrefix + 8)

// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IMOUSEDRAGGED, kRectanglePrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IRECTANGLEPREFERENCES, kRectanglePrefix + 2)

// <Implementation ID>
// ImplementationIDs
DECLARE_PMID(kImplementationIDSpace, kRectToolImpl, kRectanglePrefix + 1 )
DECLARE_PMID(kImplementationIDSpace, kRectangleTrackerImpl, kRectanglePrefix + 2 )
DECLARE_PMID(kImplementationIDSpace, kRectTrackerRegisterImpl, kRectanglePrefix + 3)
//gap
DECLARE_PMID(kImplementationIDSpace, kRectFrameToolImpl, kRectanglePrefix + 5 )
DECLARE_PMID(kImplementationIDSpace, kRectangleFrameTrackerImpl, kRectanglePrefix + 6 )
//gap
DECLARE_PMID(kImplementationIDSpace, kCreateRectDialogControllerImpl, kRectanglePrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kDrawingToolPrefsImpl, kRectanglePrefix + 9)

// <Widget ID>
// WidgetIDs
DECLARE_PMID(kWidgetIDSpace, kRectToolWidgetId, kRectanglePrefix + 1 )
DECLARE_PMID(kWidgetIDSpace, kRectFrameToolWidgetId, kRectanglePrefix + 2)

// Widget IDs for CreateRect dialog
DECLARE_PMID(kWidgetIDSpace, kCreateRectParentWidgetID, kRectanglePrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kRectWidthEditWidgetID, kRectanglePrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kRectHeightEditWidgetID, kRectanglePrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kRectWidthTextWidgetID, kRectanglePrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kRectHeightTextWidgetID, kRectanglePrefix + 7)
DECLARE_PMID(kWidgetIDSpace, kRectGroupWidgetID, kRectanglePrefix + 8)
DECLARE_PMID(kWidgetIDSpace, kRectGroupTextWidgetId, kRectanglePrefix + 9)

// <Action ID>
// ActionIDs
DECLARE_PMID(kActionIDSpace, kRectToolActionID, kRectanglePrefix + 1 )
DECLARE_PMID(kActionIDSpace, kRectFrameToolActionID, kRectanglePrefix + 2)

#endif // __RectID__
