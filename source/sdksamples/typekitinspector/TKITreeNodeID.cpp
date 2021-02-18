//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/typekitinspector/TKITreeNodeID.cpp $
//  
//  Owner: Timothy Brand-Spencer
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2015 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"
#include "TKITreeNodeID.h"
#include "IPMStream.h"

//----------------------------------------------------------------------------------------
// TKITreeNodeID::Compare
//----------------------------------------------------------------------------------------
int32 TKITreeNodeID::Compare(const NodeIDClass* NodeID) const
{

	const TKITreeNodeID* otherNode = static_cast<const TKITreeNodeID*>(NodeID);
	return fString.Compare(kTrue, otherNode->GetString());
}

//----------------------------------------------------------------------------------------
// TKITreeNodeID::Copy
//----------------------------------------------------------------------------------------
NodeIDClass* TKITreeNodeID::Clone() const
{
	return new TKITreeNodeID(this->GetString(), this->GetTextRange());
}

//----------------------------------------------------------------------------------------
// TKITreeNodeID::Read
//----------------------------------------------------------------------------------------
void TKITreeNodeID::Read(IPMStream* stream)
{
	fString.ReadWrite(stream);
}

//----------------------------------------------------------------------------------------
// TKITreeNodeID::Write
//----------------------------------------------------------------------------------------
void TKITreeNodeID::Write(IPMStream* stream) const
{
	(const_cast<TKITreeNodeID*>(this)->fString).ReadWrite(stream);
}

//----------------------------------------------------------------------------------------
// TKITreeNodeID::GetDescription
//----------------------------------------------------------------------------------------
PMString TKITreeNodeID::GetDescription() const
{
	return GetString();
}

//----------------------------------------------------------------------------------------
// TKITreeNodeID::GetDescription
//----------------------------------------------------------------------------------------
InDesign::TextRange TKITreeNodeID::GetTextRange() const
{
	return fTextRange;
}