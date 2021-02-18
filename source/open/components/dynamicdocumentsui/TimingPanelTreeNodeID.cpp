//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/TimingPanelTreeNodeID.cpp $
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
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IPMStream.h"

// ----- Includes -----

#include "DynamicDocumentsUIDefs.h"
#include "TimingPanelTreeNodeID.h"

// ----- Utils -----

// ----- ID.h files -----

#include "DynamicDocumentsUIID.h"

TimingPanelTreeNodeID::TimingPanelTreeNodeID(UID const &itemUID, bool16 const &isGroupItem, 
											 bool16 const &isFirstItemInGroup, bool16 const &isLastItemInGroup,
											 uint32 const &role, uint32 const &action) : 
											 fUID(itemUID), fIsGroupItem(isGroupItem), fIsFirstItemInGroup(isFirstItemInGroup), 
											 fIsLastItemInGroup(isLastItemInGroup),
											 fRole(role), fAction(action)
{
}

TimingPanelTreeNodeID::~TimingPanelTreeNodeID()
{

}
	
UID TimingPanelTreeNodeID::GetUID() const
{
	return fUID;
}

bool16 TimingPanelTreeNodeID::IsGroupItem() const
{
	return fIsGroupItem;
}

bool16 TimingPanelTreeNodeID::IsFirstItemInGroup() const
{
	return fIsFirstItemInGroup;
}

bool16 TimingPanelTreeNodeID::IsLastItemInGroup() const
{
	return fIsLastItemInGroup;
}

uint32 TimingPanelTreeNodeID::GetRole() const
{
	return fRole;
}

uint32 TimingPanelTreeNodeID::GetAction() const
{
	return fAction;
}

//----------------------------------------------------------------------------------------
// TimingPanelTreeNodeID::Compare
//----------------------------------------------------------------------------------------
int32 TimingPanelTreeNodeID::Compare(const NodeIDClass* otherNode) const
{
	const TimingPanelTreeNodeID* otherTimingNode = static_cast<const TimingPanelTreeNodeID*>(otherNode);
	if(fUID > otherTimingNode->fUID)
		return 1;
	else if(fUID < otherTimingNode->fUID)
		return -1;
	else
	{
		if (fIsGroupItem && !otherTimingNode->fIsGroupItem)
			return 1;
		else if(!fIsGroupItem && otherTimingNode->fIsGroupItem)
			return -1;
		else if (fIsFirstItemInGroup && !otherTimingNode->fIsFirstItemInGroup)
			return 1;
		else if(!fIsFirstItemInGroup && otherTimingNode->fIsFirstItemInGroup)
			return -1;
		else  if (fIsLastItemInGroup && !otherTimingNode->fIsLastItemInGroup)
			return 1;
		else if(!fIsLastItemInGroup && otherTimingNode->fIsLastItemInGroup)
			return -1;
		else if (fRole > otherTimingNode->fRole)
			return 1;
		else if (fRole < otherTimingNode->fRole)
			return -1;
		else if (fAction > otherTimingNode->fAction)
			return 1;
		else if (fAction < otherTimingNode->fAction)
			return -1;
		else
			return 0;
	}
}

NodeIDClass* TimingPanelTreeNodeID::Clone() const
{
	return new TimingPanelTreeNodeID(fUID, fIsGroupItem, fIsFirstItemInGroup, fIsLastItemInGroup, fRole, fAction);
}

void TimingPanelTreeNodeID::Read(IPMStream*	stream)
{
	stream->XferReference(fUID);
	stream->XferBool(fIsGroupItem);
	stream->XferBool(fIsFirstItemInGroup);
	stream->XferBool(fIsLastItemInGroup);
	stream->XferInt32((int32&)fRole);
	stream->XferInt32((int32&)fAction);
}

void TimingPanelTreeNodeID::Write(IPMStream* stream) const
{
	stream->XferReference(((TimingPanelTreeNodeID*)this)->fUID);
	stream->XferBool(((TimingPanelTreeNodeID*)this)->fIsGroupItem);
	stream->XferBool(((TimingPanelTreeNodeID*)this)->fIsFirstItemInGroup);
	stream->XferBool(((TimingPanelTreeNodeID*)this)->fIsLastItemInGroup);
	stream->XferInt32( (int32&)(((TimingPanelTreeNodeID*)this)->fRole) );
	stream->XferInt32( (int32&)(((TimingPanelTreeNodeID*)this)->fAction ) );
}
