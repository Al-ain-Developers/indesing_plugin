//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/GapToolID.h $
//  
//  Owner: Rich Gartland
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

#ifndef __GapToolID_h__
#define __GapToolID_h__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"


// Plug-in:
#define kGapToolPluginName	"GapTool" // Name of this plug-in.

#define kGapToolPrefix		RezLong(0x20F00)
// PluginID:
DECLARE_PMID(kPlugInIDSpace, kGapToolPluginID, kGapToolPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kGapToolBoss,kGapToolPrefix + 0)
DECLARE_PMID(kClassIDSpace, kGapToolTrackerBoss,kGapToolPrefix + 1)
DECLARE_PMID(kClassIDSpace, kGapToolTrackerRegisterBoss,kGapToolPrefix + 3)
//gap
DECLARE_PMID(kClassIDSpace, kBasicGapToolBoss,kGapToolPrefix + 6)
DECLARE_PMID(kClassIDSpace, kBasicGapToolTrackerRegisterBoss,kGapToolPrefix + 7)
//gap
DECLARE_PMID(kClassIDSpace, kGapToolOpenLayoutResponderBoss,kGapToolPrefix + 10)


// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_IGAPTOOLMOUSEWATCHER,kGapToolPrefix + 0)
DECLARE_PMID(kInterfaceIDSpace, IID_IGAPTOOLEDGELOCK,kGapToolPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IGAPTOOLPAGEITEMCHANGESOBSERVER,kGapToolPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IDATA_K2VECTOR_GAP, kGapToolPrefix + 4) 
DECLARE_PMID(kInterfaceIDSpace, IID_IKEYLIFTED, kGapToolPrefix + 5) 


// Implementation IDs:
DECLARE_PMID(kImplementationIDSpace, kGapToolImpl, kGapToolPrefix + 0)
DECLARE_PMID(kImplementationIDSpace, kGapToolTrackerImpl, kGapToolPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kGapToolTrackerRegisterImpl, kGapToolPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kGapToolCursorProviderImpl, kGapToolPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kGapToolSpriteImpl, kGapToolPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kGapTrackerSpriteImpl, kGapToolPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kGapMouseWatcherImpl, kGapToolPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kGapEventWatcherImpl, kGapToolPrefix + 7)
//gap
DECLARE_PMID(kImplementationIDSpace, kBasicGapToolImpl, kGapToolPrefix + 9)
//gap
DECLARE_PMID(kImplementationIDSpace, kBasicGapToolTrackerRegisterImpl, kGapToolPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kGapToolOpenLayoutResponderImpl, kGapToolPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kGapToolPageItemChangesObserverImpl, kGapToolPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kIData_K2Vector_GapImpl, kGapToolPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kGapToolTrackerEHImpl, kGapToolPrefix + 15)


// WidgetIDs	
DECLARE_PMID(kWidgetIDSpace, kGapToolWidgetID, kGapToolPrefix + 0) 

// Action IDs
DECLARE_PMID(kActionIDSpace, kGapToolActionID, kGapToolPrefix + 0)
DECLARE_PMID(kActionIDSpace, kBasicGapToolActionID, kGapToolPrefix + 1)

// Icon IDs
// Even although the ID spaces do not overlap, I assign the same ID to both the ID and the Icons.
#define kIconGapToolID				kIconGapTool
#define kIconBasicGapToolID			kIconBasicGapTool

#endif // __GapToolID_h__

// End, GapToolID.h.




