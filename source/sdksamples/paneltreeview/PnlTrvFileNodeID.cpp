//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/paneltreeview/PnlTrvFileNodeID.cpp $
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
#include "PnlTrvFileNodeID.h"

/**
	@ingroup paneltreeview
*/

/* Compare
*/
int32 PnlTrvFileNodeID::Compare(const NodeIDClass* nodeID) const
{
	const PnlTrvFileNodeID* fileNode = static_cast<const PnlTrvFileNodeID*>(nodeID);
	ASSERT(nodeID);
	return (const_cast<PnlTrvFileNodeID*>(this)->fPath.Compare(kFalse, fileNode->GetPath()));
}

/* Clone
*/
NodeIDClass* PnlTrvFileNodeID::Clone() const
{
	return new PnlTrvFileNodeID(this->GetPath());
}

/* Read
*/
void PnlTrvFileNodeID::Read(IPMStream* stream)
{
	fPath.ReadWrite(stream);
}

/* Write
*/
void PnlTrvFileNodeID::Write(IPMStream* stream) const
{
	(const_cast<PnlTrvFileNodeID*>(this)->fPath).ReadWrite(stream);
}
