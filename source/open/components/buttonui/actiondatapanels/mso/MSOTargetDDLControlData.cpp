//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/mso/MSOTargetDDLControlData.cpp $
//  
//  Owner: Greg St. Pierre
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

#include "IPageItemNameFacade.h"

#include "BehaviorUIID.h"
#include "DropDownListControlDataOf.tpp"
#include "K2Vector.tpp"		// NB: This is necessary to avoid linker errors. Obviously.
#include "Utils.h"

#include "MSOBehaviorPanelTypes.h"

CREATE_PMINTERFACE(DropDownListControlDataOf<MSOTargetReference>, kMSOTargetDDLControlDataImpl);

template <>
PMString DropDownListControlDataOf<MSOTargetReference>::GetString(const MSOTargetReference& item) const
{
	if (item.fReference != UIDRef::gNull)
	{
		PMString title = Utils<Facade::IPageItemNameFacade>()->GetUserAssignedPageItemName(item.fReference);
		
		if (title.IsEmpty())
		{
			title = Utils<Facade::IPageItemNameFacade>()->GetDefaultPageItemName(item.fReference);
			title.Translate();
			title.Insert("<");
			title.Append(">");
		}
		
		return title;
	}
	return PMString("$$$/Dialog/Behaviors/MSO/NoMSO");
}
