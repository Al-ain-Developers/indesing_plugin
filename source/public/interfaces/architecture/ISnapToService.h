//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ISnapToService.h $
//  
//  Owner: Patrick Lau
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
//  Purpose of Interface:
//  Interface to service for providing snap on support inside a spread when a
//  page item is moved or resized.
//  
//========================================================================================

#pragma once
#ifndef __ISnapToService__
#define __ISnapToService__


#include "IPMUnknown.h"
#include "ISnapTo.h"
#include "IDocument.h"
#include "IControlView.h"
#include "ILayoutControlData.h"

class ISnapToService : public IPMUnknown
{
public:
    // Check the document and the current snap flags and see if
    // we want to snap to this SnapTo service
    //
    virtual bool16 DoSnap(IDocument *document, SnapFlags flags) = 0;
  
    // Return a provider ranking to be used for determining the order of
    // invocation
    //
    virtual PMReal GetProviderRanking() = 0;

    // Find the snap to point given the current point and view and report
    // the type of snap found.
    //
    virtual SnapType FindSnapPoint(ISnapTo* snapTo,				// Snap to interface
	                               IControlView* theView,		// View being snapped in
								   PMPoint& thePoint,			// Point being snapped
								   const PMRect* theRect,		// Rect being snapped (may be nil)
								   SnapType snapType,			// How to snap the points
								   PMReal snapToZone,			// Zone for snapping
								   ILayoutControlData* layoutData) = 0;	// Current layout data
};

#endif //__ISnapToService__
