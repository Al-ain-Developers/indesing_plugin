//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/dialogs/ListBoxListZOrderDDTarget.cpp $
//  
//  Owner: Mark VerMurlen
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
//  
//  Drop target for z-order reordering of the list box in the list box field options panel
//  
//  (Derived from SwatchesListZOrderDDTarget)
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "IListBoxController.h"
#include "ITreeViewHierarchyAdapter.h"
#include "ITreeNodeIDData.h"

#include "DragDropID.h"
#include "IntNodeID.h"
#include "ListBoxListZOrderDDTarget.h"
#include "OrderListControlData.h"
#include "OrderListElement.h"
#include "PMFlavorTypes.h"

#include "FormFieldUIID.h"

//========================================================================================

DEFINE_HELPER_METHODS(ListBoxListZOrderDDTarget)

CREATE_PMINTERFACE(ListBoxListZOrderDDTarget, kOrderListBoxListZOrderDDTargetImpl)

ListBoxListZOrderDDTarget::ListBoxListZOrderDDTarget(IPMUnknown *boss) :
	CTreeViewDragDropTarget(boss),
	HELPER_METHODS_INIT(boss)
{
}

ListBoxListZOrderDDTarget::~ListBoxListZOrderDDTarget()
{
}

//______________________________________________________________________________________

DragDrop::TargetResponse ListBoxListZOrderDDTarget::CouldAcceptTypes(DataObjectIterator* dataIter, const IDragDropSource* fromSource, const IDragDropController*) const
{
	// Check the available external flavors to see if we can handle any of them
	if (dataIter)
	{
		// Use unique flavors. Make ssure we don't accept drops from other palettes
		DataExchangeResponse flavorResponse = dataIter->FlavorExistsWithPriorityInAllObjects (kPMListBoxZOrderFlavor);
		if (flavorResponse.CanDo())
			return DragDrop::TargetResponse(flavorResponse, DragDrop::kDropWillMove);
	}
	
	return DragDrop::kWontAcceptTargetResponse;
}

//______________________________________________________________________________________

ErrorCode	ListBoxListZOrderDDTarget::ProcessDragDropCommand
	(
	IDragDropController*						controller,
	DragDrop::eCommandType					type
	)
{
	ErrorCode errorCode = kFailure;
	ICommand* command = nil;	
	
	InterfacePtr<ITreeNodeIDData> treeData(fOldTarget, UseDefaultIID());
	InterfacePtr<OrderListControlData> listData(this, IID_ILISTCONTROLDATA);
	int32 moveToIndex = listData->Length();		// last position in case the item is being dragged to the empty area...
	if (treeData)		// treeData will be null when we are dragging it to the empty area in the widget.
	{
		InterfacePtr<ITreeViewHierarchyAdapter> adapter(this, UseDefaultIID());
		moveToIndex = adapter->GetChildIndex(adapter->GetRootNode(), treeData->Get());
	}
	
	errorCode = kSuccess;

	//Move the item that was dragged (IIntData) to its new location (moveToIndex)
	
	if ((controller->InternalizeDrag(kPMListBoxZOrderFlavor, kPMListBoxZOrderFlavor) == kSuccess))
		MoveItems( moveToIndex );

	return errorCode;
}

//______________________________________________________________________________________

void ListBoxListZOrderDDTarget::MoveItems( int32 inMoveToIndex )
{
	const int32 kAtEnd = StringListBoxControlData::kEnd;
	
	InterfacePtr<OrderListControlData> listData(this, IID_ILISTCONTROLDATA);
	InterfacePtr<IListBoxController> listController(this, IID_ILISTBOXCONTROLLER);

	int32 listLength = listData->Length();
	
	// Get the list of selected items
	K2Vector<int32> selectedList;
	listController->GetSelected( selectedList );
	std::sort( selectedList.begin(), selectedList.end() );
	int32 selectedListLength = selectedList.size();
	
	int32 moveFromIndex;
	int32 moveToIndex = inMoveToIndex;
	
	// Deselect all the items since they'll all get reselected in their new locations below
	listController->DeselectAll();
	
	for ( int32 i = 0; i < selectedListLength; i++ ) {
		
		moveFromIndex = selectedList[i];

		if (moveFromIndex >= 0 && moveFromIndex < listLength) {
			
			// Check the validity of the move to index
			if ( moveToIndex != kAtEnd ) {
				if ( moveToIndex < 0)
					moveToIndex = 0;
				if (moveToIndex >= listLength)
					moveToIndex = kAtEnd;
			}
			
			// Save and remove the item from the list
			OrderListElement moveItem = listData->GetElementAt(moveFromIndex);
			listData->Remove(moveFromIndex);

			//Account for the removed item...
			if (moveToIndex != kAtEnd && moveFromIndex < moveToIndex)
				moveToIndex--;
			
			// Add the item back in at its new location
	  		listData->AddELement(moveItem, moveToIndex);
			
			// Select the item
			listController->Select( moveToIndex ); //select it.
			
			// Update the location of the selected items
			for ( int32 j = i+1; j <selectedListLength; j++ ) {
				if ( moveToIndex == kAtEnd || selectedList[j] <= moveToIndex )
					selectedList[j] -= 1;
			}
			
			// Update the Move To location
			if ( moveToIndex != kAtEnd )
				moveToIndex += 1;
		}
	}
}