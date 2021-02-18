//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/treeview/ListIndexNodeID.cpp $
//  
//  Owner: Matt Joss
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

#include "DV_VCWidgetHeaders.h"

#include "ListIndexNodeID.h"
#include "IPMStream.h"
#include "widgetid.h"

//----------------------------------------------------------------------------------------
// ListIndexNodeID::Create
//----------------------------------------------------------------------------------------
NodeID_rv ListIndexNodeID::Create( const int32& index )
{ 
	return new ListIndexNodeID(index); 
}

//----------------------------------------------------------------------------------------
// ListIndexNodeID::RootNodeID
//----------------------------------------------------------------------------------------
NodeID_rv ListIndexNodeID::RootNodeID(  )
{ 
	return new ListIndexNodeID(-1); 
}

//----------------------------------------------------------------------------------------
// ListIndexNodeID::Compare
//----------------------------------------------------------------------------------------
int32 ListIndexNodeID::Compare(const NodeIDClass* NodeID) const
{
	const ListIndexNodeID* indexData = static_cast<const ListIndexNodeID*>(NodeID);
	if (this->GetIndex() == indexData->GetIndex())
		return 0;
	if (this->GetIndex() > indexData->GetIndex())
		return 1;
	else
		return -1;
}

//----------------------------------------------------------------------------------------
// ListIndexNodeID::Copy
//----------------------------------------------------------------------------------------
NodeIDClass* ListIndexNodeID::Clone() const
{
	return new ListIndexNodeID(fIndex);
}

//----------------------------------------------------------------------------------------
// ListIndexNodeID::Read
//----------------------------------------------------------------------------------------
void ListIndexNodeID::Read(IPMStream*	stream)
{
	stream->XferInt32(fIndex);
}

//----------------------------------------------------------------------------------------
// ListIndexNodeID::Write
//----------------------------------------------------------------------------------------
void ListIndexNodeID::Write(IPMStream*	stream) const
{
	stream->XferInt32( const_cast<ListIndexNodeID*>(this)->fIndex );
}

//----------------------------------------------------------------------------------------
// ListIndexNodeID::GetDescription
//----------------------------------------------------------------------------------------
PMString ListIndexNodeID::GetDescription() const 
{ 
	PMString desc("index:");
	desc.AppendNumber(fIndex);
	return desc; 
}
