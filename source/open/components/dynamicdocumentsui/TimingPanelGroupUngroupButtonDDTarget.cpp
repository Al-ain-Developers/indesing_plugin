//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/TimingPanelGroupUngroupButtonDDTarget.cpp $
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
//  
//  Comments: Object style panel drag/drop target for delete button
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interface files -----

#include "IControlView.h"
#include "IDynamicEventTimingFacade.h"
#include "IDynamicEventTimingSuite.h"
#include "IDynamicTargetListData.h"
#include "IIntData.h"

// ----- Include files -----

#include "CButtonDragDropTarget.h"
#include "DataObjectIterator.h"
#include "PMFlavorTypes.h"
#include "UIDList.h"

// ----- Utilitity files -----

#include "DynamicDocumentsUIUtils.h"
#include "ISelectionUtils.h"
#include "Utils.h"

// ----- ID files -----

#include "NodeID.h"
#include "DynamicDocumentsUIID.h"

class IDragDropController;
class IDragDropSource;

class CTimingPanelGroupUngroupButtonDDTarget : public CButtonDragDropTarget
{
	public:
				CTimingPanelGroupUngroupButtonDDTarget(IPMUnknown *boss);
		virtual	~CTimingPanelGroupUngroupButtonDDTarget();
		
		//
		// Can the target accept the data being dragged?
		// (Drag source is provided to determine if data should be moved, copied or linked.)
		//
		virtual DragDrop::TargetResponse CouldAcceptTypes(DataObjectIterator*, const IDragDropSource*, const IDragDropController* controller) const;

		//
		// Create the commands needed to complete a drop 
		// (targets will only receive kDragMove or kDrop)
		// Subclass should override this function.
		//
		virtual ErrorCode ProcessDragDropCommand(IDragDropController*, DragDrop::eCommandType);

	protected:
		virtual ErrorCode ProcessPrivateCommand(IDynamicEventTimingMgr::DynamicTargetList const &itemList) = 0;
};

//--------------------------------------------------------------------------------------
// CTimingPanelGroupUngroupButtonDDTarget::CTimingPanelGroupUngroupButtonDDTarget()
//-------------------------------------------------------------------------------------
CTimingPanelGroupUngroupButtonDDTarget::CTimingPanelGroupUngroupButtonDDTarget(IPMUnknown *boss) :
	CButtonDragDropTarget(boss)
{
}

//--------------------------------------------------------------------------------------
// CTimingPanelGroupUngroupButtonDDTarget::~CTimingPanelGroupUngroupButtonDDTarget()
//-------------------------------------------------------------------------------------
CTimingPanelGroupUngroupButtonDDTarget::~CTimingPanelGroupUngroupButtonDDTarget()
{
}

//--------------------------------------------------------------------------------------
// CTimingPanelGroupUngroupButtonDDTarget::CouldAcceptTypes()
//--------------------------------------------------------------------------------------
DragDrop::TargetResponse CTimingPanelGroupUngroupButtonDDTarget::CouldAcceptTypes(DataObjectIterator* dataIter, const IDragDropSource* fromSource, const IDragDropController* controller) const
{
	//
	// Check the available external flavors to see if we can handle any of them
	//
	if (dataIter)
	{
		//
		// If the button is disabled, we won't accept drops
		//
		InterfacePtr<IControlView>	view(this, UseDefaultIID());
		if (!view || !view->IsEnabled())
		{
			return DragDrop::kWontAcceptTargetResponse;
		}
		
		//
		// Unique timing panel flavor (same as the flavor for rearranging layers since the source is also the listbox). 
		// Make ssure we don't accept drops from other palettes
		//
		DataExchangeResponse response = dataIter->FlavorExistsWithPriorityInAllObjects(kPMTimingPanelDragDropFlavor);

		if (!response.CanDo())
		{
			return DragDrop::kWontAcceptTargetResponse;
		}

		//
		// If no item is selected, we don't accept.
		//
		InterfacePtr<IDataExchangeHandler> iDataExchangeHandler(controller->QueryHandler(kPMTimingPanelDragDropFlavor));
		InterfacePtr<IDynamicTargetListData> iSelectedItems(iDataExchangeHandler, UseDefaultIID());
		if (iSelectedItems && (iSelectedItems->size() > 0))		
		{
			return DragDrop::kDropWillMove;
		}
	}

	return DragDrop::kWontAcceptTargetResponse;
}

//--------------------------------------------------------------------------------------
// CTimingPanelGroupUngroupButtonDDTarget::ProcessDragDropCommand()
//--------------------------------------------------------------------------------------
ErrorCode CTimingPanelGroupUngroupButtonDDTarget::ProcessDragDropCommand(IDragDropController* controller, DragDrop::eCommandType type)
{
	InterfacePtr<IDataExchangeHandler> iDataExchangeHandler(controller->QueryHandler(kPMTimingPanelDragDropFlavor));
	InterfacePtr<IDynamicTargetListData> iSelectedItems(iDataExchangeHandler, UseDefaultIID());
	ASSERT(iSelectedItems != nil);

	if (iSelectedItems && (iSelectedItems->size() > 0))
	{
		IDynamicEventTimingMgr::DynamicTargetList itemList;
		iSelectedItems->GetDynamicTargetList(itemList);

		if (itemList.size() > 0)
			return ProcessPrivateCommand(itemList);
	}

	return kSuccess;
}

class TimingPanelGroupButtonDDTarget : public CTimingPanelGroupUngroupButtonDDTarget
{
	public:
		TimingPanelGroupButtonDDTarget(IPMUnknown *boss) : CTimingPanelGroupUngroupButtonDDTarget(boss) { }
		virtual	~TimingPanelGroupButtonDDTarget() { }
		
	protected:
		virtual ErrorCode ProcessPrivateCommand(IDynamicEventTimingMgr::DynamicTargetList const &itemList);
};


CREATE_PMINTERFACE(TimingPanelGroupButtonDDTarget, kTimingPanelGroupButtonDDTargetImpl)

//--------------------------------------------------------------------------------------
// TimingPanelGroupButtonDDTarget::ProcessPrivateCommand
//--------------------------------------------------------------------------------------
ErrorCode TimingPanelGroupButtonDDTarget::ProcessPrivateCommand(IDynamicEventTimingMgr::DynamicTargetList const &itemList)
{
	return ddui_utils::GroupTimingItems(itemList);
}

class TimingPanelUngroupButtonDDTarget : public CTimingPanelGroupUngroupButtonDDTarget
{
	public:
				TimingPanelUngroupButtonDDTarget(IPMUnknown *boss) : CTimingPanelGroupUngroupButtonDDTarget(boss) { }
		virtual	~TimingPanelUngroupButtonDDTarget() { }
		
	protected:
		virtual ErrorCode ProcessPrivateCommand(IDynamicEventTimingMgr::DynamicTargetList const &itemList);
};


CREATE_PMINTERFACE(TimingPanelUngroupButtonDDTarget, kTimingPanelUngroupButtonDDTargetImpl)

//--------------------------------------------------------------------------------------
// TimingPanelUngroupButtonDDTarget::ProcessPrivateCommand
//--------------------------------------------------------------------------------------
ErrorCode TimingPanelUngroupButtonDDTarget::ProcessPrivateCommand(IDynamicEventTimingMgr::DynamicTargetList const &itemList)
{
	return ddui_utils::UngroupTimingItems(itemList);
}
