//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/CSliderTracker.h $
//  
//  Owner: SusanCL, lance bushore
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
//  Implementation for the slider bar tracker
//  
//========================================================================================

#pragma once
#ifndef __CSliderTracker__
#define __CSliderTracker__

#include "CTracker.h"
#include "PMRect.h"

#ifdef WIDGET_BUILD
#pragma export on
#endif

class WIDGET_DECL CSliderTracker : public CTracker
{
	public:
		CSliderTracker(IPMUnknown *boss);
		~CSliderTracker();

		virtual bool16	BeginTracking(IEvent* theEvent);
		virtual void	ContinueTracking(const PBPMPoint& where, bool16 mouseDidMove);
		virtual bool16	EndTracking(IEvent* theEvent);
		virtual void	AbortTracking(IEvent* theEvent);

	protected:
		virtual void	GlobalToPasteboard(const GSysPoint& thePoint, PBPMPoint& convertedPoint);
		
		// subclasses should override these 2 methods.
		virtual	PMReal	MapPointToDataRange(const PBPMPoint& pt); 
		virtual	void	UpdateControls( const PBPMPoint& where );
		
		PMReal	fInitialSliderValue;
		PMRect	fConstrainingRect;
};

#pragma export off

#endif //__CSliderTracker__