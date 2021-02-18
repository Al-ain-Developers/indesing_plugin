//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmldataupdaterui/DataUpdaterUINodeID.cpp $
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
#include "DataUpdaterUINodeID.h"
#include "DataUpdaterConst.h"
/**
	@ingroup xmldataupdaterui
*/

/* Compare
*/
int32 DataUpdaterUINodeID::Compare(const NodeIDClass* nodeID) const
{
	const DataUpdaterUINodeID* oneNode = static_cast<const DataUpdaterUINodeID*>(nodeID);
	ASSERT(nodeID);
	if (const_cast<DataUpdaterUINodeID*>(this)->fType < oneNode->GetType())
		return -1;
	else if (const_cast<DataUpdaterUINodeID*>(this)->fType > oneNode->GetType())
		return 1;
	else
	{	//same type, look for index
		if (const_cast<DataUpdaterUINodeID*>(this)->fIndex < oneNode->GetIndex())
			return -1;
		else if (const_cast<DataUpdaterUINodeID*>(this)->fIndex > oneNode->GetIndex())
			return 1;
		else
		{
			if (const_cast<DataUpdaterUINodeID*>(this)->fValue < oneNode->GetValue())
				return -1;
			else if (const_cast<DataUpdaterUINodeID*>(this)->fValue > oneNode->GetValue())
				return 1;
			else 
				return 0; // all equal
		}
	}
}


/* Clone
*/
NodeIDClass* DataUpdaterUINodeID::Clone() const
{
	return new DataUpdaterUINodeID(this->GetType(),this->GetIndex(),this->GetValue());
}


/* Read
*/
void DataUpdaterUINodeID::Read(IPMStream* stream)
{
	fType.ReadWrite(stream);
    stream->XferInt32(fIndex);
	fValue.ReadWrite(stream);
}


/* Write
*/
void DataUpdaterUINodeID::Write(IPMStream* stream) const
{
	(const_cast<DataUpdaterUINodeID*>(this)->fType).ReadWrite(stream);
	stream->XferInt32(const_cast<DataUpdaterUINodeID*>(this)->fIndex);
	(const_cast<DataUpdaterUINodeID*>(this)->fValue).ReadWrite(stream);
}

//	end, File:	PnlTrvDataNode.cpp
