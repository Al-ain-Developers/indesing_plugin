//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/TimingPanelTreeNodeDDSource.cpp $
//  
//  Owner: Yeming Liu
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

// ----- Interface files -----

#include "IActiveContext.h"
#include "IDynamicEventTimingFacade.h"
#include "IDynamicTargetListData.h"
#include "IIntData.h"
#include "ISelectionUtils.h"
#include "IStringListData.h"
#include "ITreeViewController.h"
#include "IUIDListData.h"
#include "IWidgetParent.h"
#include "IWidgetUtils.h"
#include "IWorkspace.h"

// ----- Include files -----

#include "CDragDropSource.h"

// ----- Utilitity files -----

#include "DynamicDocumentsUIUtils.h"
#include "Utils.h"

// ----- ID files -----

#include "DynamicDocumentsUIID.h"
#include "TimingPanelTreeNodeID.h"

class TimingPanelTreeNodeDDSource : public CDragDropSource
{
	public:
				TimingPanelTreeNodeDDSource(IPMUnknown *boss) : CDragDropSource(boss) { }
		virtual ~TimingPanelTreeNodeDDSource() { }

		virtual bool16		DoAddDragContent(IDragDropController*);
		virtual CursorSpec 	GetDragCursor(DragDrop::eTargetResponse, bool16 isDragLocal) const;
		virtual ErrorCode ProcessDragDropCommand(IDragDropController* controller, DragDrop::eCommandType type);
};

CREATE_PMINTERFACE(TimingPanelTreeNodeDDSource, kTimingPanelTreeNodeDDSourceImpl)

//--------------------------------------------------------------------------------------
// TimingPanelTreeNodeDDSource::DoAddDragContent()
//--------------------------------------------------------------------------------------
bool16 TimingPanelTreeNodeDDSource::DoAddDragContent(IDragDropController* controller)
{
	//
	// Obtain a handler for our internal data flavor. 
	// Don't promise anything if we couldn't get a handler
	//
	InterfacePtr<IDataExchangeHandler> iDataExchangeHandler(controller->QueryHandler(kPMTimingPanelDragDropFlavor));
	if (!iDataExchangeHandler)
		return kFalse;

	//
	// Cache the selected items in the tree. 
	//			
	InterfacePtr<ISelectionManager> iSelectionMgr(Utils<ISelectionUtils>()->QueryActiveSelection ()); 
	IDataBase* db = iSelectionMgr->GetDataBase();

	IDynamicEventTimingMgr::DynamicTargetList selectedItems;
	ddui_utils::GetSelectedTimingItems(db, selectedItems);
	
	if (!selectedItems.empty())
	{
		Utils<Facade::IDynamicEventTimingFacade> iTimingFacade;
		InterfacePtr<IDynamicTargetListData> iDynamicTargetListData(iDataExchangeHandler, UseDefaultIID());
		iDynamicTargetListData->Clear();
		for (IDynamicEventTimingMgr::DynamicTargetList::const_iterator iter = selectedItems.begin(); iter != selectedItems.end(); ++iter)
		{
			// Don't need to create a target in this case. Since these are ref-counted, we could just append.
			//IDynamicEventTimingMgr::DynamicTargetPtr dynamicTargetPtr = iTimingFacade->CreateDynamicTarget (UIDRef(db, (*iter)->GetTargetUID()), *iter);

			iDynamicTargetListData->Append(*iter);
		}
	}

	//
	// Install our handler so we can fulfill promises we make below
	//
	controller->SetSourceHandler(iDataExchangeHandler) ;

	//
	// Add a data item and promise the appropriate data flavors
	// Note that in this case we promise only one since the internal flavor and 
	// external flavor are the same.
	//
	InterfacePtr<IPMDataObject> item(controller->AddDragItem(1));
	PMFlavorFlags flavorFlags = 0;
	item->PromiseFlavor(kPMTimingPanelDragDropFlavor, flavorFlags);

	return kTrue;
}

//--------------------------------------------------------------------------------------
// TimingPanelTreeNodeDDSource::GetDragCursor()
//--------------------------------------------------------------------------------------
CursorSpec 	TimingPanelTreeNodeDDSource::GetDragCursor(DragDrop::eTargetResponse dropEffect, bool16 isDragLocal) const
{
	CursorSpec    spec = CursorSpec((CursorID) DragDrop::kDefaultDragCursors);

    if ( dropEffect == DragDrop::kDropWillMove )
	{
        spec = CursorSpec((CursorID) kCrsrClosedHand );
	}
    else if ( dropEffect == DragDrop::kDropWillCopy )
	{
        spec = CursorSpec((CursorID) kCrsrClosedHandCopy );
	}

    return spec;
}

ErrorCode	TimingPanelTreeNodeDDSource::ProcessDragDropCommand(IDragDropController* controller, DragDrop::eCommandType type)
{
	return kSuccess;
}