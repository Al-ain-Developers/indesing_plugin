//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/treeview/ViewNodeID.cpp $
//  
//  Owner: Bob Freeman
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
#include "ViewNodeID.h"

#include "IPMStream.h"

//----------------------------------------------------------------------------------------
// ViewNodeID::Compare
//----------------------------------------------------------------------------------------
int32 ViewNodeID::Compare(const NodeIDClass* NodeID) const
{
	const ViewNodeID* otherNode = static_cast<const ViewNodeID*>(NodeID);
	IControlView* otherView = otherNode->GetView();
    if (fView == otherView)
        return 0;
    else if (fView > otherView)
        return 1;
	else
		return -1;
}

//----------------------------------------------------------------------------------------
// ViewNodeID::Copy
//----------------------------------------------------------------------------------------
NodeIDClass* ViewNodeID::Clone() const
{
	return new ViewNodeID(fView);
}

//----------------------------------------------------------------------------------------
// ViewNodeID::Read
//----------------------------------------------------------------------------------------
void ViewNodeID::Read(IPMStream* stream)
{
}

//----------------------------------------------------------------------------------------
// ViewNodeID::Write
//----------------------------------------------------------------------------------------
void ViewNodeID::Write(IPMStream* stream) const
{
}

//----------------------------------------------------------------------------------------
// ViewNodeID::GetDescription
//----------------------------------------------------------------------------------------
PMString ViewNodeID::GetDescription() const
{
    PMString desc("UID:");
    desc.AppendNumber(reinterpret_cast<uintptr_t>(fView));
    return desc;
}