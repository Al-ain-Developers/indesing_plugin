//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/DeleteConditionTagButtonDNDTarget.cpp $
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
#include "IControlView.h"
#include "ITreeViewHierarchyAdapter.h"
#include "ITreeViewController.h"
#include "IUIDListData.h"
#include "IWidgetParent.h"
#include "IWorkspace.h"

// ----- Includes -----

#include "CButtonDragDropTarget.h"
#include "UIDNodeID.h"

// ----- Utility files -----

#include "IConditionalTextUIFacade.h"
#include "IDocument.h"
#include "IEventUtils.h"
#include "IInCopySharedUtils.h"
#include "IWidgetUtils.h"

// ----- ID.h files -----

#include "ConditionalTextUIID.h"
#include "DragDropID.h"


class DeleteConditionTagButtonDNDTarget : public CButtonDragDropTarget
{
public:
	DeleteConditionTagButtonDNDTarget(IPMUnknown *boss);
	virtual	~DeleteConditionTagButtonDNDTarget();
		
	virtual DragDrop::TargetResponse CouldAcceptTypes(DataObjectIterator*, const IDragDropSource*, const IDragDropController*) const;
	virtual ErrorCode		ProcessDragDropCommand(IDragDropController*, DragDrop::eCommandType);
};

// =============================================================================
// *** DeleteConditionTagButtonDNDTarget impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(DeleteConditionTagButtonDNDTarget, kDeleteConditionTagButtonDNDTargetImpl)

DeleteConditionTagButtonDNDTarget::DeleteConditionTagButtonDNDTarget(IPMUnknown *boss) :
	CButtonDragDropTarget(boss)
{
} // end constructor

DeleteConditionTagButtonDNDTarget::~DeleteConditionTagButtonDNDTarget()
{
} // end destructor

// -----------------------------------------------------------------------------

DragDrop::TargetResponse DeleteConditionTagButtonDNDTarget::CouldAcceptTypes(DataObjectIterator* dataIter, const IDragDropSource* fromSource, const IDragDropController* controller) const
{
	// Check the available external flavors to see if we can handle any of them
	if (dataIter)
	{
		// Make sure we don't accept drops from other palettes
		DataExchangeResponse response = dataIter->FlavorExistsWithPriorityInAllObjects(kPMConditionTagListFlavor);
		if (!response.CanDo())
			return DragDrop::kWontAcceptTargetResponse;

		IDataBase* db = ::GetDataBase(GetExecutionContextSession()->GetActiveContext()->GetContextWorkspace());
		if (!Utils<IInCopySharedUtils>()->StylesEditable(db))
			return DragDrop::kWontAcceptTargetResponse;

		InterfacePtr<IControlView> treeView((IControlView*)Utils<IWidgetUtils>()->QueryRelatedWidget(this, kConditionTagListTreeViewWidgetBoss, IID_ICONTROLVIEW));
		InterfacePtr<ITreeViewController> tvController(treeView, UseDefaultIID());
		InterfacePtr<ITreeViewHierarchyAdapter> tvAdapter(tvController, UseDefaultIID());
		if (tvAdapter && tvController->IsSelected(tvAdapter->GetRootNode()))
			return DragDrop::kWontAcceptTargetResponse;
		
		return DragDrop::TargetResponse(response, DragDrop::kDropWillCopy);	// Always copy in the drag and drop sense
	}
	
	return DragDrop::kWontAcceptTargetResponse;
} // end CouldAcceptTypes()

// -----------------------------------------------------------------------------

ErrorCode DeleteConditionTagButtonDNDTarget::ProcessDragDropCommand(IDragDropController* controller, DragDrop::eCommandType type)
{
	InterfacePtr<IDataExchangeHandler> handler(controller->QuerySourceHandler());
	InterfacePtr<IUIDListData>	listData(handler, UseDefaultIID());
	if(listData)
	{
		IActiveContext* context = GetExecutionContextSession()->GetActiveContext();
		if (context)
		{
			UIDList draggedTagsList(*(listData->GetRef()));
			if (draggedTagsList.size() > 0)
			{
				K2Vector<UID> draggedUIDsToDelete;
				std::copy(draggedTagsList.begin(), draggedTagsList.end(), std::back_inserter(draggedUIDsToDelete));
				Utils<Facade::IConditionalTextUIFacade>()->DeleteConditions(context->GetContextWorkspace(), draggedUIDsToDelete, kFalse);
			}
		}
		return kSuccess;
	}

	return kSuccess;
} // end ProcessDragDropCommand()
