//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IGuideTrackerData.h $
//  
//  Owner: Paul Sorrick
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
//  Interface for storing what type of guide is being tracked.
//  
//========================================================================================

#pragma once
#ifndef __IGuideTrackerData__
#define __IGuideTrackerData__

#include "IPMUnknown.h"
#include "CommandID.h"

class IGuideTrackerData : public IPMUnknown
{
public:
	enum { kHGuide = 1, kVGuide, kMultiGuides };			

	virtual void Set(int32 i) = 0;
	virtual int32 GetInt() = 0;
};



#endif // __IGuideTrackerData__