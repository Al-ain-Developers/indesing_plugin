//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/msopanel/MSOStateNodeID.cpp $
//  
//  Owner: Michele Stutzman
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
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

#include "IActiveContext.h"
#include "IDataBase.h"
#include "IPMStream.h"
#include "IWorkspace.h"

// ----- Includes -----

#include "MSOStateNodeID.h"

// ----- Utility files -----


// ----- ID.h files -----

#include "FormFieldUIID.h"


// =============================================================================
// *** MSOStateNodeID impl ***
// -----------------------------------------------------------------------------

NodeIDClass* MSOStateNodeID::Clone() const
{
	return new MSOStateNodeID(fAppearanceState);
} // end Clone()

// -----------------------------------------------------------------------------

int32 MSOStateNodeID::Compare(const NodeIDClass* otherNode) const
{
	const MSOStateNodeID* otherNodeData = static_cast<const MSOStateNodeID*>(otherNode);
	if (fAppearanceState > otherNodeData->fAppearanceState)
		return 1;
	else if (fAppearanceState < otherNodeData->fAppearanceState)
		return -1;
	else
		return 0;
} // end Compare()

// -----------------------------------------------------------------------------

void MSOStateNodeID::Read(IPMStream* stream)
{
	MSOStateNodeID::Write(stream);
} // end Read()

// -----------------------------------------------------------------------------

void MSOStateNodeID::Write(IPMStream* stream) const
{
	stream->XferInt32((int32&)fAppearanceState);
} // end Write()

// -----------------------------------------------------------------------------

PMString MSOStateNodeID::GetDescription() const
{
	PMString desc("Appearance State:");
    desc.AppendNumber(fAppearanceState);
	return desc;
}  // end GetDescription()

// -----------------------------------------------------------------------------

NodeID_rv MSOStateNodeID::GetGenericNodeID() const
{
	return MSOStateNodeID::Create(Form::kStateInvalid);	
} // end GetGenericNodeID()

// -----------------------------------------------------------------------------

IDataBase* MSOStateNodeID::GetDataBase() const
{
	IWorkspace*	iWs = GetExecutionContextSession()->GetActiveContext()->GetContextWorkspace();
	return ::GetDataBase(iWs);
} // end GetDataBase()
