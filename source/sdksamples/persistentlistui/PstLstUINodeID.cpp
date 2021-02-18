//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlistui/PstLstUINodeID.cpp $
//  
//  Owner: Adobe Developer Technologies
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

// Interface includes:
#include "IPMStream.h"

// Project includes:
#include "PstLstUINodeID.h"
/**
	@ingroup wlistboxcomposite
*/

/* Compare
*/
int32 PstLstUINodeID::Compare(const NodeIDClass* nodeID) const
{
	const PstLstUINodeID* oneNode = static_cast<const PstLstUINodeID*>(nodeID);
	ASSERT(nodeID);
	if (const_cast<PstLstUINodeID*>(this)->fDataType < oneNode->GetDataType())
		return -1;
	else if (const_cast<PstLstUINodeID*>(this)->fDataType > oneNode->GetDataType())
		return 1;
	else
	{	//same DataType, look at uid
		if (const_cast<PstLstUINodeID*>(this)->fUID.Get() < oneNode->GetUID().Get())
			return -1;
		else if (const_cast<PstLstUINodeID*>(this)->fUID.Get() > oneNode->GetUID().Get())
			return 1;
		else
		{
			if (const_cast<PstLstUINodeID*>(this)->fDataDescription < oneNode->GetDataDescription())
				return -1;
			else if (const_cast<PstLstUINodeID*>(this)->fDataDescription > oneNode->GetDataDescription())
				return 1;
			else 
				return 0; // all equal
		}
	}
}


/* Clone
*/
NodeIDClass* PstLstUINodeID::Clone() const
{
	return new PstLstUINodeID(this->GetDataType(), this->GetUID(), this->GetDataDescription());
}


/* Read
*/
void PstLstUINodeID::Read(IPMStream* stream)
{
    stream->XferInt32(fDataType);
	stream->XferReference(fUID);
	fDataDescription.ReadWrite(stream);
}


/* Write
*/
void PstLstUINodeID::Write(IPMStream* stream) const
{
	stream->XferInt32(const_cast<PstLstUINodeID*>(this)->fDataType);
	stream->XferReference(const_cast<PstLstUINodeID*>(this)->fUID);
	(const_cast<PstLstUINodeID*>(this)->fDataDescription).ReadWrite(stream);
}

//
