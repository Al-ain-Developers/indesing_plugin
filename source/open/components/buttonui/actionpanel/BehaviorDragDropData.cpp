//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actionpanel/BehaviorDragDropData.cpp $
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

#include "IBehaviorDragDropData.h"
#include "IPMStream.h"

// ----- Implementation Includes -----

#include "BehaviorUIID.h"
#include "CPMUnknown.h"

//========================================================================================
// CLASS BehaviorDragDropData
//========================================================================================

class BehaviorDragDropData : public CPMUnknown<IBehaviorDragDropData>
{
public:
	BehaviorDragDropData(IPMUnknown *boss);
	virtual ~BehaviorDragDropData();

	void ReadWrite(IPMStream *s, ImplementationID prop);

	virtual void Clear();
	virtual bool16 IsEmpty() const;

	virtual void Set(IDataBase* db, const std::vector< std::pair<ActionEvent, UID> >& behaviors);

	virtual IDataBase* GetDataBase() const;
	virtual std::vector< std::pair<ActionEvent, UID> > Get() const;

private:
	IDataBase* fDb;
	std::vector< std::pair<ActionEvent, UID> > fBehaviors;
};

//========================================================================================
// METHODS BehaviorDragDropData
//========================================================================================

CREATE_PERSIST_PMINTERFACE(BehaviorDragDropData, kBehaviorDragDropDataImpl)

//----------------------------------------------------------------------------------------
// BehaviorDragDropData::BehaviorDragDropData
//----------------------------------------------------------------------------------------

BehaviorDragDropData::BehaviorDragDropData(IPMUnknown *boss) :
	CPMUnknown<IBehaviorDragDropData>(boss), fDb(nil)
{
}

//----------------------------------------------------------------------------------------
// BehaviorDragDropData::~BehaviorDragDropData
//----------------------------------------------------------------------------------------

BehaviorDragDropData::~BehaviorDragDropData()
{
}

//----------------------------------------------------------------------------------------
// BehaviorDragDropData::ReadWrite
//----------------------------------------------------------------------------------------

void BehaviorDragDropData::ReadWrite(IPMStream *s, ImplementationID prop)
{
	if (s->IsReading())
	{
		s->XferInt32((int32&) fDb);

		int32 len = s->XferInt32(len);
		fBehaviors.clear();
		for (int32 i = 0; i < len; i++)
		{
			ActionEvent event = s->XferInt32(event);
			UID action = s->XferObject(action);

			fBehaviors.push_back(std::pair<ActionEvent, UID>(event, action));
		}
	}
	else
	{
		s->XferInt32((int32&) fDb);

		int32 len = static_cast<int32>(fBehaviors.size());
		s->XferInt32(len);

		for (std::vector< std::pair<ActionEvent, UID> >::iterator i = fBehaviors.begin(); i != fBehaviors.end(); i++)
		{
			ActionEvent event = (*i).first;
			s->XferInt32(event);

			UID action = (*i).second;
			s->XferObject(action);
		}
	}
}

//----------------------------------------------------------------------------------------
// BehaviorDragDropData::Clear
//----------------------------------------------------------------------------------------

void BehaviorDragDropData::Clear()
{
	PreDirty ();
	fBehaviors.clear();

}

//----------------------------------------------------------------------------------------
// BehaviorDragDropData::IsEmpty
//----------------------------------------------------------------------------------------

bool16 BehaviorDragDropData::IsEmpty() const
{
	return fBehaviors.size() == 0;
}

//----------------------------------------------------------------------------------------
// BehaviorDragDropData::Set
//----------------------------------------------------------------------------------------

void BehaviorDragDropData::Set(IDataBase* db, const std::vector< std::pair<ActionEvent, UID> >& behaviors)
{
	PreDirty ();
	fDb = db;
	fBehaviors = behaviors;

}

//----------------------------------------------------------------------------------------
// BehaviorDragDropData::Get
//----------------------------------------------------------------------------------------

IDataBase* BehaviorDragDropData::GetDataBase() const
{
	return fDb;
}

//----------------------------------------------------------------------------------------
// BehaviorDragDropData::Get
//----------------------------------------------------------------------------------------

std::vector< std::pair<ActionEvent, UID> > BehaviorDragDropData::Get() const
{
	return fBehaviors;
}

