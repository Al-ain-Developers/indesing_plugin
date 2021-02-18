//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerTreeUIDNodeID.cpp $
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

#include "VCPlugInHeaders.h"

#include "LayerTreeUIDNodeID.h"
#include "IPMStream.h"
#include "widgetid.h"
#include "LinksUIID.h"
#include "ILinksTreeNodeList.h"

LayerTreeUIDNodeID::LayerTreeUIDNodeID( const UID& uid, bool isLayerEntry ) : 
fUID(uid),fIsLayerEntry(isLayerEntry)
{
//	TRACEFLOW("LayerPanel","LayerTreeUIDNodeID constructed at 0x%x with UID %d, isLayer %d\n",this,uid.Get(),isLayerEntry);
}

LayerTreeUIDNodeID::~LayerTreeUIDNodeID()
{
//	TRACEFLOW("LayerPanel","LayerTreeUIDNodeID destructing 0x%x(fUID %d, fIsLayerEntry %d)\n",this,fUID.Get(),fIsLayerEntry);
}
	
UID LayerTreeUIDNodeID::GetUID() const
{
	return fUID;
}

bool16 LayerTreeUIDNodeID::IsLayerEntry() const
{
	return fIsLayerEntry;
}


//----------------------------------------------------------------------------------------
// LayerTreeUIDNodeID::Compare
//----------------------------------------------------------------------------------------
int32 LayerTreeUIDNodeID::Compare(const NodeIDClass* otherNode) const
{
	const LayerTreeUIDNodeID* otherLayerNode = static_cast<const LayerTreeUIDNodeID*>(otherNode);
	if(fUID > otherLayerNode->fUID)
		return 1;
	else if(fUID < otherLayerNode->fUID)
		return -1;
	else
	{
		if(fIsLayerEntry && !otherLayerNode->fIsLayerEntry)
			return 1;
		else if(!fIsLayerEntry && otherLayerNode->fIsLayerEntry)
			return -1;
		else
			return 0;
	}
}

NodeIDClass* LayerTreeUIDNodeID::Clone() const
{
	return new LayerTreeUIDNodeID(fUID,fIsLayerEntry);
}


void LayerTreeUIDNodeID::Read(IPMStream*	stream)
{
 LayerTreeUIDNodeID::Write(stream);
}

void LayerTreeUIDNodeID::Write(IPMStream*	stream) const
{
	int32 temp = fUID.Get();
	stream->XferInt32(temp);
	((LayerTreeUIDNodeID*)this)->fUID = temp;
	stream->XferBool(((LayerTreeUIDNodeID*)this)->fIsLayerEntry);
}

PMString LayerTreeUIDNodeID::GetDescription() const 
{ 
	PMString desc("Item UID:");
	desc.AppendNumber(GetUID().Get());
	desc.Append(" Is Layer:");
	desc.AppendNumber(IsLayerEntry());
	return desc; 
}
