//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/AutoCorrectNodeID.cpp $
//  
//  Owner: Heath Horton
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

#include "AutoCorrectNodeID.h"
#include "IPMStream.h"


AutoCorrectNodeID::AutoCorrectNodeID(const WideString& correctedName, const WideString& misspelledName):
	fCorrectedName(correctedName), 
	fMisspelledName(misspelledName)
{
}

PMString AutoCorrectNodeID::GetDescription() const
{
	return fMisspelledName; 
}
//----------------------------------------------------------------------------------------
// AutoCorrectNodeID::Compare
//----------------------------------------------------------------------------------------
int32 AutoCorrectNodeID::Compare(const NodeIDClass* NodeID) const
{
	const AutoCorrectNodeID* syncNodeData = static_cast<const AutoCorrectNodeID*>(NodeID);
	ASSERT(syncNodeData != nil);

	return this->fMisspelledName.compare(syncNodeData->fMisspelledName);	/* the mis typed name is the sortable item */
}

//----------------------------------------------------------------------------------------
// AutoCorrectNodeID::Copy
//----------------------------------------------------------------------------------------
NodeIDClass* AutoCorrectNodeID::Clone() const
{
	return new AutoCorrectNodeID(fCorrectedName, fMisspelledName);
}

//----------------------------------------------------------------------------------------
// AutoCorrectNodeID::Read
//----------------------------------------------------------------------------------------
void AutoCorrectNodeID::Read(IPMStream* stream)
{
	fMisspelledName.ReadWrite(stream);
	fCorrectedName.ReadWrite(stream);
}

//----------------------------------------------------------------------------------------
// AutoCorrectNodeID::Write
//----------------------------------------------------------------------------------------
void AutoCorrectNodeID::Write(IPMStream* stream) const
{
	(const_cast<AutoCorrectNodeID*>(this)->fMisspelledName).ReadWrite(stream);
	(const_cast<AutoCorrectNodeID*>(this)->fCorrectedName).ReadWrite(stream);
}

