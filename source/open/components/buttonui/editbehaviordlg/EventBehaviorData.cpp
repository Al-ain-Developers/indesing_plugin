//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/editbehaviordlg/EventBehaviorData.cpp $
//  
//  Owner: Michael Burbidge
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

#include "VCPlugInHeaders.h"

// ----- Interface Includes -----

#include "IEventBehaviorData.h"
#include "IPMStream.h"

// ----- Implementation Includes -----

#include "BehaviorUIID.h"
#include "CPMUnknown.h"

//========================================================================================
// CLASS SoundBhvrDeleteCleanup
//========================================================================================

class EventBehaviorData : public CPMUnknown<IEventBehaviorData>
{
public:
	EventBehaviorData(IPMUnknown *boss);
	virtual ~EventBehaviorData();

	virtual void 	ReadWrite(IPMStream* s, ImplementationID prop);

	virtual int32	GetEvent() const;
	virtual void	SetEvent(const int32& event);

	virtual int32	GetBehavior() const;
	virtual void	SetBehavior(const int32& behavior);

private:
	int32	fEvent, fBehavior;
};	

//========================================================================================
// METHODS SoundBhvrDeleteCleanup
//========================================================================================

CREATE_PERSIST_PMINTERFACE(EventBehaviorData, kEventBehaviorDataImpl)

//----------------------------------------------------------------------------------------
// EventBehaviorData::EventBehaviorData
//----------------------------------------------------------------------------------------

EventBehaviorData::EventBehaviorData(IPMUnknown *boss) :
	CPMUnknown<IEventBehaviorData>(boss),
	fEvent(0),
	fBehavior(9)
{
}

//----------------------------------------------------------------------------------------
// EventBehaviorData::~EventBehaviorData
//----------------------------------------------------------------------------------------

EventBehaviorData::~EventBehaviorData()
{
}

//----------------------------------------------------------------------------------------
// EventBehaviorData::ReadWrite
//----------------------------------------------------------------------------------------

void EventBehaviorData::ReadWrite(IPMStream* s, ImplementationID prop)
{
	s->XferInt32(fEvent);
	s->XferInt32(fBehavior);
}

//----------------------------------------------------------------------------------------
// EventBehaviorData::GetEvent
//----------------------------------------------------------------------------------------

int32 EventBehaviorData::GetEvent() const
{
	return fEvent;
}

//----------------------------------------------------------------------------------------
// EventBehaviorData::SetEvent
//----------------------------------------------------------------------------------------

void EventBehaviorData::SetEvent(const int32& event)
{
	fEvent = event;
}

//----------------------------------------------------------------------------------------
// EventBehaviorData::GetBehavior
//----------------------------------------------------------------------------------------

int32 EventBehaviorData::GetBehavior() const
{
	return fBehavior;
}

//----------------------------------------------------------------------------------------
// EventBehaviorData::SetBehavior
//----------------------------------------------------------------------------------------

void EventBehaviorData::SetBehavior(const int32& behavior)
{
	fBehavior = behavior;
}
