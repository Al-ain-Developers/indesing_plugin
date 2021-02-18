//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicpersistinterface/BPIHelper.cpp $
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

// Interface headers
#include "ICommand.h"
#include "ITextFrameColumn.h"
#include "ITOPFrameData.h"
#include "IGraphicFrameData.h"
#include "IHierarchy.h"
#include "ITextUtils.h"

// General includes:
#include "CmdUtils.h"
#include "UIDList.h"
#include "Utils.h"

// Project includes:
#include "BPIID.h"
#include "IBPIData.h"
#include "BPIHelper.h"


/*	Constructor.
*/
BPIHelper::BPIHelper(void)
{
}

/*	Destructor.
*/
BPIHelper::~BPIHelper(void)
{
}

/*
*/
bool16 BPIHelper::HasBPIData(const UIDList& itemList)
{
	bool16 result = kFalse;
	do {
		if (itemList.Length() <= 0) {
			break;
		}
		for (int32 i = 0; i < itemList.Length(); i++) {
			InterfacePtr<IBPIData> bpiData(itemList.GetRef(i), UseDefaultIID());
 			if (bpiData) {
				// At least one object has IBPIData so we can return kTrue
				// and stop examining objects.
  				result = kTrue;
				break;
  			} 
		}
	} while(false);
	return result;
}

/*
*/
void BPIHelper::FilterForBPIData(UIDList& itemList)
{
	for (int32 i = itemList.Length()-1; i >= 0; i--) {
		InterfacePtr<IBPIData> bpiData(itemList.GetRef(i), UseDefaultIID());
		if (!bpiData) {
			// Object does not have any IBPIData so filter it.
			itemList.Remove(i);
		} 
	}
}

/*
*/
void BPIHelper::GetBPIData(const UIDList& itemList, K2Vector<WideString>& values)
{
	// Collect all unique IBPIData attribute values that apply to the given itemList.
	for(int32 i = 0; i <itemList.Length(); i++) {
		InterfacePtr<IBPIData> bpiData(itemList.GetRef(i), UseDefaultIID());
		if (bpiData) {
			// Iterate over the values vector to see if it already contains the new value.
			WideString value = bpiData->Get();
			if(value.empty() == kTrue) continue;
			K2Vector<WideString>::const_iterator iter = K2find(values.begin(), values.end(), value);
			if (iter == values.end()) {
				// The vector does not contain the value so add it in.
				values.push_back(value);
			}
		}
	}
}

/*
*/
ErrorCode BPIHelper::ProcessBPISetDataCmd(const UIDList& itemList, const WideString& value)
{
	ErrorCode result = kFailure;
	do {
		// Validate parameters.
		if (itemList.Length() <= 0) {
			ASSERT_FAIL("No items. This should not happen!");
			break;
		}

		// Create the command that sets the IBPIData.
		InterfacePtr<ICommand> bpiSetDataCmd(CmdUtils::CreateCommand(kBPISetDataCmdBoss));
		ASSERT(bpiSetDataCmd);
		if (bpiSetDataCmd == nil) {
			break;
		}
		
		// Pass the attribute value to be applied.
		InterfacePtr<IBPIData> bpiData(bpiSetDataCmd, UseDefaultIID());
		ASSERT(bpiData);
		if (bpiData == nil) {
			break;
		}
		bpiData->Set(value);

		// Process the command is to set the attribute for these objects.
		bpiSetDataCmd->SetItemList(itemList);
		result = CmdUtils::ProcessCommand(bpiSetDataCmd);
	} while(false);
	
	return result;
}

/*
*/
UID BPIHelper::FindAssociatedGraphicFrame(const InterfacePtr<ITextFrameColumn>& textFrameColumn)
{
	UID result = kInvalidUID;

	do {
		// Check for a text frame for text on a path.
		InterfacePtr<ITOPFrameData> topFrameData(textFrameColumn, UseDefaultIID());
		if (topFrameData != nil) {
			// This is a text on a path text frame. Refer to the
			// spline that the text on a path is associated with.
			result = topFrameData->GetMainSplineItemUID();
			break;
		}

		// Check for a regular text frame
		InterfacePtr<IHierarchy> graphicFrameHierarchy(Utils<ITextUtils>()->QuerySplineFromTextFrame(textFrameColumn));
		if (graphicFrameHierarchy)
			result = ::GetUID(graphicFrameHierarchy);
	} while(false);

	return result;
}

// End, BPIHelper.cpp.

