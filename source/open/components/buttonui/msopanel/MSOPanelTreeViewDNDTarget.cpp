//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/msopanel/MSOPanelTreeViewDNDTarget.cpp $
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

#include "IAppearanceSuite.h"
#include "ITreeViewController.h"
#include "ITreeViewMgr.h"
#include "ITreeNodeIDData.h"
#include "IWidgetParent.h"

// ----- Includes -----

#include "CTreeViewDragDropTarget.h"
#include "MSOStateNodeID.h"

// ----- Utility files -----

#include "EventUtilities.h"
#include "FormFieldUIUtils.h"
#include "MSOPanelUtils.h"

// ----- ID.h files -----

#include "FormFieldUIID.h"


class MSOPanelTreeViewDNDTarget : public CTreeViewDragDropTarget
{
	public: 
		MSOPanelTreeViewDNDTarget(IPMUnknown *boss);
		virtual	~MSOPanelTreeViewDNDTarget();
		
		virtual DragDrop::TargetResponse	CouldAcceptTypes(DataObjectIterator*, const IDragDropSource*, const IDragDropController*) const;
		virtual ErrorCode ProcessDragDropCommand(IDragDropController*, DragDrop::eCommandType);

	private:
		mutable PMFlavor			fFlavor;
};

// =============================================================================
// *** MSOPanelTreeViewDNDTarget impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(MSOPanelTreeViewDNDTarget, kMSOPanelTreeViewDNDTargetImpl)

MSOPanelTreeViewDNDTarget::MSOPanelTreeViewDNDTarget(IPMUnknown *boss) :
	CTreeViewDragDropTarget(boss), fFlavor(kNoFlavor)
{
} // end constructor

MSOPanelTreeViewDNDTarget::~MSOPanelTreeViewDNDTarget()
{
} // end destructor

// -----------------------------------------------------------------------------

DragDrop::TargetResponse MSOPanelTreeViewDNDTarget::CouldAcceptTypes(DataObjectIterator* dataIter, const IDragDropSource* source, const IDragDropController* controller) const
{
	// Check the available external flavors to see if we can handle any of them
	if (dataIter)
	{
		// Make sure we don't accept drops from other palettes
		DataExchangeResponse response = dataIter->FlavorExistsWithPriorityInAllObjects(kMSOStateDragDropFlavor);
		if (!response.CanDo())
			return DragDrop::kWontAcceptTargetResponse;
		
		fFlavor = kMSOStateDragDropFlavor;
		return DragDrop::TargetResponse(response, DragDrop::kDropWillCopy);
	}
	return DragDrop::kWontAcceptTargetResponse;
} // end CouldAcceptTypes()

// -----------------------------------------------------------------------------

ErrorCode MSOPanelTreeViewDNDTarget::ProcessDragDropCommand(IDragDropController* controller, DragDrop::eCommandType type)
{
	ErrorCode err = kSuccess;

	if (fFlavor == kMSOStateDragDropFlavor && controller->InternalizeDrag(kNoExternalFlavor, kMSOStateDragDropFlavor) == kSuccess)
	{
		InterfacePtr<IDataExchangeHandler> handler(controller->QueryHandler(kMSOStateDragDropFlavor));
		if (handler)
		{
			InterfacePtr<ITreeNodeIDData> treeData(fOldTarget, UseDefaultIID());
			if (!treeData) return kSuccess;
			
			TreeNodePtr<MSOStateNodeID> dropStateNode(treeData->Get());

			InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
			if (iAppearanceSuite)
			{
				Form::AppearanceState dragState = MSOPanelUtils::GetSelectedAppearance();
				if (dragState != Form::kStateInvalid)
				{
					bool bAltKeyIsPressed = ::IsOptionAltKeyPressed();

					int32 dragStatePos = iAppearanceSuite->GetStatePosition(dragState);

					Form::AppearanceState dropState = dropStateNode->GetAppearance();
					int32 dropStatePos = iAppearanceSuite->GetStatePosition(dropState); 

					if (fHitLocation == kAbove)
					{
						// Dropped above the state being dragged or above the state after the state being 
						// dragged. Unless duplicating there is nothing to do.
						if (!bAltKeyIsPressed && (dragStatePos == dropStatePos || dragStatePos == dropStatePos - 1))
							return kSuccess;						
					}
					else
					{
						if (dragStatePos == dropStatePos || dragStatePos == dropStatePos + 1)
						{
							// Dropped below state being dragged or below the state before the dragged state.
							// If duplicating then adjust the drop position so duplicated state will be below
							// the dragged state; otherwise, nothing to do.
							if (bAltKeyIsPressed)
							{
								if (dropStatePos == iAppearanceSuite->NumStates()-1)
									dropStatePos = IAppearanceList::kLastInOrder;
								else
									++dropStatePos;
							}
							else
								return kSuccess;
						}
						else if (dropStatePos == iAppearanceSuite->NumStates()-1)
							dropStatePos = IAppearanceList::kLastInOrder;
						else
							++dropStatePos;
					}

					if (bAltKeyIsPressed)
						err = iAppearanceSuite->NewState(iAppearanceSuite->GetNewState(), dropStatePos);
					else
						err = iAppearanceSuite->MoveState(dragState, dropStatePos);
				}

				if (err == kSuccess)
				{
					InterfacePtr<ITreeViewMgr> treeViewMgr(this, UseDefaultIID());
					MSOPanelUtils::RebuildTreeViewList(treeViewMgr);
				}
			}
		}
	}

	return err;
} // end ProcessDragDropCommand()
