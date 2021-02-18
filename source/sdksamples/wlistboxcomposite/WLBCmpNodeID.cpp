//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/wlistboxcomposite/WLBCmpNodeID.cpp $
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
#include "WLBCmpNodeID.h"
/**
	@ingroup wlistboxcomposite
*/

/* Compare
*/
int32 WLBCmpNodeID::Compare(const NodeIDClass* nodeID) const
{
	const WLBCmpNodeID* oneNode = static_cast<const WLBCmpNodeID*>(nodeID);
	ASSERT(nodeID);
    return fName.Compare(kTrue, oneNode->GetName());

}


/* Clone
*/
NodeIDClass* WLBCmpNodeID::Clone() const
{
	return new WLBCmpNodeID(this->GetName());
}


/* Read
*/
void WLBCmpNodeID::Read(IPMStream* stream)
{
	fName.ReadWrite(stream);
}


/* Write
*/
void WLBCmpNodeID::Write(IPMStream* stream) const
{
	(const_cast<WLBCmpNodeID*>(this)->fName).ReadWrite(stream);
}

//	end, File:	PnlTrvDataNode.cpp
