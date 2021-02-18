//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/appearancepanel/ListItemsTreeViewDDTarget.cpp $
//  
//  Owner: Reena Agrawal
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

#include "IFormFieldSuite.h"
#include "ITreeNodeIDData.h"
#include "ITreeViewController.h"

// ----- Includes -----

#include "CTreeViewDragDropTarget.h"
#include "IntNodeID.h"
#include "PMFlavorTypes.h"

// ----- Utility files -----

#include "FormFieldUIUtils.h"

// ----- ID.h files -----

#include "FormFieldUIID.h"


class ListItemsTreeViewDDTarget : public CTreeViewDragDropTarget
{
public: 
	ListItemsTreeViewDDTarget(IPMUnknown *boss);
	virtual        ~ListItemsTreeViewDDTarget();

	virtual DragDrop::TargetResponse        CouldAcceptTypes(DataObjectIterator*, const IDragDropSource*, const IDragDropController*) const;
	virtual ErrorCode ProcessDragDropCommand(IDragDropController*, DragDrop::eCommandType);

private:
	mutable PMFlavor                        fFlavor;
};

// =============================================================================
// *** ListItemsTreeViewDDTarget impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(ListItemsTreeViewDDTarget, kListItemsTreeViewDDTargetImpl)

ListItemsTreeViewDDTarget::ListItemsTreeViewDDTarget(IPMUnknown *boss) :
CTreeViewDragDropTarget(boss), fFlavor(kNoFlavor)
{
} // end constructor

ListItemsTreeViewDDTarget::~ListItemsTreeViewDDTarget()
{
} // end destructor

// -----------------------------------------------------------------------------

DragDrop::TargetResponse ListItemsTreeViewDDTarget::CouldAcceptTypes(DataObjectIterator* dataIter, const IDragDropSource* source, const IDragDropController* controller) const
{
	// Check the available external flavors to see if we can handle any of them
	if (dataIter)
	{
		// Make sure we don't accept drops from other palettes
		DataExchangeResponse response = dataIter->FlavorExistsWithPriorityInAllObjects(kListItemsDragDropFlavor);
		if (!response.CanDo())
			return DragDrop::kWontAcceptTargetResponse;

		InterfacePtr<IFormFieldSuite> iFormFieldSuite(FormFieldUIUtils::QueryFormSuite());
		if (iFormFieldSuite)
		{
			bool16 isMixed;
			bool16 sortListItems = iFormFieldSuite->GetShouldSortListItems(isMixed);
			ASSERT_MSG(!isMixed, "Mixed value for single selection?");

			if (sortListItems)
				return DragDrop::kWontAcceptTargetResponse;
		}

		fFlavor = kListItemsDragDropFlavor;
		return DragDrop::TargetResponse(response, DragDrop::kDropWillCopy);
	}
	return DragDrop::kWontAcceptTargetResponse;
} // end CouldAcceptTypes()

// -----------------------------------------------------------------------------

ErrorCode ListItemsTreeViewDDTarget::ProcessDragDropCommand(IDragDropController* controller, DragDrop::eCommandType type)
{
	ErrorCode err = kSuccess;

	if (fFlavor == kListItemsDragDropFlavor && controller->InternalizeDrag(kNoExternalFlavor, kListItemsDragDropFlavor) == kSuccess)
	{
		InterfacePtr<IDataExchangeHandler> handler(controller->QueryHandler(kListItemsDragDropFlavor));
		if (handler)
		{
			InterfacePtr<IFormFieldSuite> iFormFieldSuite(FormFieldUIUtils::QueryFormSuite());
			Form::ChoiceList choiceList;
			iFormFieldSuite->GetChoiceList(choiceList);

			K2Vector<NodeID> selectedItems;
			InterfacePtr<ITreeViewController> optionsTreeViewCntlr(this, UseDefaultIID());
			optionsTreeViewCntlr->GetSelectedItems(selectedItems);
			TreeNodePtr<IntNodeID> dragItemNode(selectedItems[0]);
			int32 dragItemPos = dragItemNode->Get();

			InterfacePtr<ITreeNodeIDData> treeData(fOldTarget, UseDefaultIID());
			int32 dropItemPos = choiceList.size() - 1;		// last position in case the item is being dragged to the empty area...
			if (treeData)		// treeData will be null when we are dragging it to the empty area in the widget.
			{
				TreeNodePtr<IntNodeID> dropItemNode(treeData->Get());
				dropItemPos = dropItemNode->Get();
			}

			err = iFormFieldSuite->MoveChoice(choiceList[dragItemPos], dropItemPos);
		}
	}

	return err;
} // end ProcessDragDropCommand()
