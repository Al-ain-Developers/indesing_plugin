//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actionpanel/MoveBehaviorData.cpp $
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

#include "IMoveBehaviorData.h"

// ----- Implementation Includes -----

#include "BehaviorUIID.h"
#include "CPMUnknown.h"

//========================================================================================
// CLASS SoundBhvrDeleteCleanup
//========================================================================================

class MoveBehaviorData : public CPMUnknown<IMoveBehaviorData>
{
public:
	MoveBehaviorData(IPMUnknown *boss);
	virtual ~MoveBehaviorData();
	
	virtual void Set(IDataBase* db,
					 const std::vector< std::pair<ActionEvent, UID> >& behaviors,
					 const ActionEvent& event,
					 const int32& position);
	virtual void Clear();
	
	virtual IDataBase* GetDataBase() const;
	virtual std::vector< std::pair<ActionEvent, UID> > GetBehaviors() const;
	virtual ActionEvent GetEvent() const;
	virtual int32 GetPosition() const;

private:
	IDataBase*	fDb;
	std::vector< std::pair<ActionEvent, UID> > fBehaviors;
	ActionEvent	fEvent;
	int32		fPosition;
};	

//========================================================================================
// METHODS MoveBehaviorData
//========================================================================================

CREATE_PMINTERFACE(MoveBehaviorData, kMoveBehaviorDataImpl)

//----------------------------------------------------------------------------------------
// MoveBehaviorData::MoveBehaviorData
//----------------------------------------------------------------------------------------

MoveBehaviorData::MoveBehaviorData(IPMUnknown *boss) :
	CPMUnknown<IMoveBehaviorData>(boss),
	fDb(nil),
	fBehaviors(),
	fEvent(0),
	fPosition(0)
{
}

//----------------------------------------------------------------------------------------
// MoveBehaviorData::~MoveBehaviorData
//----------------------------------------------------------------------------------------

MoveBehaviorData::~MoveBehaviorData()
{
}

//----------------------------------------------------------------------------------------
// MoveBehaviorData::Set
//----------------------------------------------------------------------------------------

void MoveBehaviorData::Set(IDataBase* db,
						   const std::vector< std::pair<ActionEvent, UID> >& behaviors,
						   const ActionEvent& event,
						   const int32& position)
{
	fDb = db;
	fBehaviors = behaviors;
	fEvent = event;
	fPosition = position;
}

//----------------------------------------------------------------------------------------
// MoveBehaviorData::Clear
//----------------------------------------------------------------------------------------

void MoveBehaviorData::Clear()
{
	fDb = nil;
	fBehaviors.clear();
	fEvent = 0;
	fPosition = 0;
}

//----------------------------------------------------------------------------------------
// MoveBehaviorData::GetDataBase
//----------------------------------------------------------------------------------------

IDataBase* MoveBehaviorData::GetDataBase() const
{
	return fDb;
}

//----------------------------------------------------------------------------------------
// MoveBehaviorData::GetBehaviors
//----------------------------------------------------------------------------------------

std::vector< std::pair<ActionEvent, UID> > MoveBehaviorData::GetBehaviors() const
{
	return fBehaviors;
}

//----------------------------------------------------------------------------------------
// MoveBehaviorData::GetEvent
//----------------------------------------------------------------------------------------

ActionEvent MoveBehaviorData::GetEvent() const
{
	return fEvent;
}

//----------------------------------------------------------------------------------------
// MoveBehaviorData::GetPosition
//----------------------------------------------------------------------------------------

int32 MoveBehaviorData::GetPosition() const
{
	return fPosition;
}
