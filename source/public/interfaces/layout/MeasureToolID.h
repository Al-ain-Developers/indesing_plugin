//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/MeasureToolID.h $
//  
//  Owner: Yeming Liu
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
//  Contains IDs used by measure tool which is combined in the basic tools project.
//  
//========================================================================================

#ifndef __MEASURETOOLID__
#define __MEASURETOOLID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kMeasureToolPrefix	 RezLong(0x11800)

// <Start IDC>
// PluginID
// Access via kZoomToolPlugInName and kZoomToolPluginID
// since measure tool is combined in the BasicTools plugin.

START_IDS()

// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kMeasureToolBoss,				kMeasureToolPrefix + 1)
DECLARE_PMID(kClassIDSpace, kMeasureToolTrackerBoss,		kMeasureToolPrefix + 2)
DECLARE_PMID(kClassIDSpace, kMeasureToolTrackerRegisterBoss,kMeasureToolPrefix + 3)
DECLARE_PMID(kClassIDSpace, kMeasureLineDrawServiceBoss,    kMeasureToolPrefix + 4)

// <Interface ID>
// Interface IDs
DECLARE_PMID(kInterfaceIDSpace, IID_IMEASURETOOLDATA, kMeasureToolPrefix + 1)		

// <Implementation ID>
// Implementation IIDs
DECLARE_PMID(kImplementationIDSpace, kMeasureToolImpl,				  kMeasureToolPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kMeasureToolTrackerImpl,		  kMeasureToolPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kMeasureToolTrackerRegisterImpl, kMeasureToolPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kMeasureToolDataImpl,			  kMeasureToolPrefix + 4)	
DECLARE_PMID(kImplementationIDSpace, kMeasureToolCursorProviderImpl,  kMeasureToolPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kMeasureToolSpriteImpl,		  kMeasureToolPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kMeasureLineDrawServiceImpl,	  kMeasureToolPrefix + 7)	
DECLARE_PMID(kImplementationIDSpace, kMeasureLineDrawHandlerImpl,     kMeasureToolPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kMeasureToolObserverImpl,        kMeasureToolPrefix + 9)

// <Widget ID>
// Widget IDs
DECLARE_PMID(kWidgetIDSpace, kMeasureToolWidgetId,					kMeasureToolPrefix + 1)

// <Action ID>
// Action IDs
DECLARE_PMID(kActionIDSpace, kMeasureToolActionID,		kMeasureToolPrefix + 1)
// kMeasureToolPrefix + 2 to kMeasureToolPrefix + 22 is reserved for the measure system, 
// please start from kMeasureToolPrefix + 23 to define new actionIDs.

END_IDS()
#endif // __MEASURETOOLID__








