//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/CropToolID.h $
//  
//  Owner: vineet batra
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

#ifndef __CropToolID_h__
#define __CropToolID_h__

#if 0 //Moved to CoreCropToolID.h
	#include "CrossPlatformTypes.h"
	#include "IDFactory.h"
#endif 

#include "CoreCropToolID.h"

// Plug-in:
#define kCropToolPluginName	"PositionTool" // Name of this plug-in.

#if 0 //Moved to CoreCropToolID.h
	#define kCropToolPrefix		RezLong(0x19B00)
// PluginID:
DECLARE_PMID(kPlugInIDSpace, kCropToolPluginID, kCropToolPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kCropToolBoss,kCropToolPrefix + 4)
#endif

DECLARE_PMID(kClassIDSpace, kCropToolTrackerBoss,kCropToolPrefix + 5)
DECLARE_PMID(kClassIDSpace, kCropToolTrackerRegisterBoss,kCropToolPrefix + 8)
DECLARE_PMID(kClassIDSpace, kFrameSelectionFilterBoss, kCropToolPrefix + 9)
DECLARE_PMID(kClassIDSpace, kCropToolSelInfoPanelWidgetBoss,kCropToolPrefix + 10)
DECLARE_PMID(kClassIDSpace, kCropToolNonSelInfoPanelWidgetBoss,kCropToolPrefix + 11)



// InterfaceIDs:


// Implementation IDs:
DECLARE_PMID(kImplementationIDSpace, kCropToolImpl, kCropToolPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kCropToolTrackerImpl, kCropToolPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kCropToolTrackerRegisterImpl, kCropToolPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kCropToolCursorProviderImpl, kCropToolPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kCropToolInfoPanelProviderImpl, kCropToolPrefix + 5)
// gap
DECLARE_PMID(kImplementationIDSpace, kFrameSelectionFilterImpl, kCropToolPrefix + 10)


// WidgetIDs	
DECLARE_PMID(kWidgetIDSpace, kCropToolWidgetID, kCropToolPrefix + 0) 

// Action IDs
DECLARE_PMID(kActionIDSpace, kCropToolActionID, kCropToolPrefix + 1)

// Icon IDs
// Even although the ID spaces do not overlap, I assign the same ID to both the ID and the Icons.
#define kIconCropToolID			kIconCropTool

#endif // __CropToolID_h__

// End, CropToolID.h.




