//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/TimingPanelTreeDDTarget.cpp $
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

#include "IDynamicEventTimingSuite.h"
#include "IDynamicEventTimingFacade.h"
#include "IGraphicsPort.h"
#include "IInterfaceColors.h"
#include "ISelectionManager.h"
#include "ITextControlData.h"
#include "ITreeNodeIDData.h"
#include "ITreeViewController.h"
#include "ITreeViewMgr.h"

// ----- Include files -----

#include "AGMGraphicsContext.h"
#include "AutoGSave.h"
#include "CTreeViewDragDropTarget.h"
#include "DynamicDocumentsUIDefs.h"
#include "TimingPanelTreeNodeID.h"
#include "K2Vector.tpp"

// ----- Utilitity files -----

#include "DrawStringUtils.h"
#include "DynamicDocumentsUIUtils.h"
#include "ISelectionUtils.h"
#include "IWidgetUtils.h"

//draws with drawbot and private conversion utils
#include "DVAPublicIncludes.h"
#include "DVPublicUtilities.h"

// ----- ID files -----

#include "DynamicDocumentsUIID.h"

class TimingPanelTreeDDTarget : public CTreeViewDragDropTarget
{
	public:
		typedef CTreeViewDragDropTarget inherited;

				TimingPanelTreeDDTarget(IPMUnknown *boss);
		virtual	~TimingPanelTreeDDTarget() { }
		
		// Can the target accept the data being dragged?
		//	(Drag source is provided to determine if data should be moved, copied or linked.)
		virtual DragDrop::TargetResponse CouldAcceptTypes(DataObjectIterator*, const IDragDropSource*, const IDragDropController*) const;

		// Create the commands needed to complete a drop 
		// 	(targets will only receive kDragMove or kDrop)
		virtual ErrorCode ProcessDragDropCommand(IDragDropController*, DragDrop::eCommandType);
		virtual SysWireframe DoMakeDropHiliteRegion() const
			{
				return (SysWireframe) DragDrop::kNoDropHilite;
			}


	protected:
		virtual void DrawHilite(IControlView* targetWidget, int32 hitWhere);
		virtual int32 HitTest(IControlView*	widget, const PMPoint& localPoint );
		virtual bool DirectDrawHilite(const dvaui::ui::UI_Node* nodeP, dvaui::drawbot::Drawbot* drawbotP);

	private:
		ErrorCode MoveOneGroupOrItems(IDynamicEventTimingMgr::DynamicTargetList selectedItems, bool const bSameGroup);
		ErrorCode MoveMultipleGroups(IDynamicEventTimingMgr::DynamicTargetList selectedItems, std::map<int32, IDynamicEventTimingMgr::DynamicTargetList> const &groupTargetList);
		PMPoint fLocalPoint;
		bool fNeedsToDrawHighlite;
};

CREATE_PMINTERFACE(TimingPanelTreeDDTarget, kTimingPanelTreeDDTargetImpl)

//--------------------------------------------------------------------------------------
// TimingPanelTreeDDTarget::TimingPanelTreeDDTarget()
//-------------------------------------------------------------------------------------
TimingPanelTreeDDTarget::TimingPanelTreeDDTarget(IPMUnknown *boss) :
	inherited(boss),
	fLocalPoint(0,0),fNeedsToDrawHighlite(kFalse)
{	
}

//--------------------------------------------------------------------------------------
// TimingPanelTreeDDTarget::CouldAcceptTypes()
//--------------------------------------------------------------------------------------
DragDrop::TargetResponse TimingPanelTreeDDTarget::CouldAcceptTypes(DataObjectIterator* dataIter, const IDragDropSource* fromSource, const IDragDropController* controller) const
{
	//
	// Check the available external flavors to see if we can handle any of them
	//
	if (dataIter)
	{		
		DataExchangeResponse response;
	
		// This DDTarget actually only handle timing item drop.
		response = dataIter->FlavorExistsWithPriorityInAllObjects(kPMTimingPanelDragDropFlavor); 
        if (response.CanDo()) 
        { 
			// We don't allow to reorder for unassigned type.
			EventTriggerType eventType = ddui_utils::GetCurrentEventTypeInTimingPanel();
			if (eventType != kNoTriggerEvent)
				return DragDrop::TargetResponse(response, DragDrop::kDropWillMove);	// kDropWillMove shows the hand without plus cursor
		}
	}
	
	return DragDrop::kWontAcceptTargetResponse;
}

//--------------------------------------------------------------------------------------
// TimingPanelTreeDDTarget::ProcessDragDropCommand
//--------------------------------------------------------------------------------------
ErrorCode TimingPanelTreeDDTarget::ProcessDragDropCommand(IDragDropController* controller, DragDrop::eCommandType type)
{
	ErrorCode result = kSuccess;

	InterfacePtr<ISelectionManager> iSelectionMgr(Utils<ISelectionUtils>()->QueryActiveSelection ()); 
	IDataBase* db = iSelectionMgr->GetDataBase();
	if (!db)
		return result;

	InterfacePtr<IDynamicEventTimingSuite> iDynamicEventTimingSuite(static_cast<IDynamicEventTimingSuite*>(Utils<ISelectionUtils>()->QuerySuite(IID_IDYNAMICEVENTTIMINGSUITE, iSelectionMgr)));
	if (!iDynamicEventTimingSuite)
		return result;

	IDynamicEventTimingMgr::DynamicTargetList selectedItems;
	ddui_utils::GetSelectedTimingItems(db, selectedItems);
	if (selectedItems.size() <= 0)
		return result;
	
	// Check if the selected items are all in groups or not. 
	// If they are all in groups (all items in the group are selected), we will process move groups command. 
	std::map<int32, IDynamicEventTimingMgr::DynamicTargetList> groupTargetList;
	if (ddui_utils::AllItemsInTimingGroups(selectedItems, groupTargetList) && (static_cast<int32>(groupTargetList.size()) > 1))
	{
		result = this->MoveMultipleGroups(selectedItems, groupTargetList);
	}
	else
	{	
		uint32 originalGroupIndex = 0;
		bool bSameGroup = ddui_utils::AllItemsInSameTimingGroup(selectedItems, originalGroupIndex);

		result = this->MoveOneGroupOrItems(selectedItems, bSameGroup);
	}

	InterfacePtr<IControlView>	iTreeView(this, UseDefaultIID());
	InterfacePtr<ITreeViewController> iTreeViewController(iTreeView, UseDefaultIID());
	iTreeViewController->DeselectAll(kFalse/*don't notify*/, kTrue/*invalidate*/);

	return result;
}

//--------------------------------------------------------------------------------------
// TimingPanelTreeDDTarget::MoveOneGroupOrItems
//--------------------------------------------------------------------------------------
ErrorCode TimingPanelTreeDDTarget::MoveOneGroupOrItems(IDynamicEventTimingMgr::DynamicTargetList selectedItems, bool const bSameGroup)
{	
	InterfacePtr<const ITreeNodeIDData> nodeData(fOldTarget,UseDefaultIID()); 
	if (!nodeData)
		return kSuccess;
	
	EventTriggerType eventType = ddui_utils::GetCurrentEventTypeInTimingPanel();
	ASSERT(eventType != kNoTriggerEvent);

	InterfacePtr<ISelectionManager> iSelectionMgr(Utils<ISelectionUtils>()->QueryActiveSelection ()); 
	IDataBase* db = iSelectionMgr->GetDataBase();

	InterfacePtr<IDynamicEventTimingSuite> iDynamicEventTimingSuite(static_cast<IDynamicEventTimingSuite*>(Utils<ISelectionUtils>()->QuerySuite(IID_IDYNAMICEVENTTIMINGSUITE, iSelectionMgr)));
	uint32 newGroup = iDynamicEventTimingSuite->GetNumGroupsInEvent(eventType)-1;

	TreeNodePtr<const TimingPanelTreeNodeID> destNode(nodeData->Get()); 
	UIDRef destItemUIDRef = UIDRef(db, destNode->GetUID());
	uint32 role = destNode->GetRole();
	uint32 action = destNode->GetAction();

	uint32 position = -1;
	IDynamicEventTimingMgr::DynamicTargetPtr dynamicTarget (Utils<Facade::IDynamicEventTimingFacade> ()->CreateDynamicTarget(destItemUIDRef, role, action));
	newGroup = iDynamicEventTimingSuite->FindTargetInEvent(eventType, dynamicTarget, position);

	IDynamicEventTimingMgr::DynamicTargetList itemList;
	iDynamicEventTimingSuite->GetNthGroupInEvent(eventType, newGroup, itemList);
	ASSERT(newGroup >= 0);

	if (destNode->IsGroupItem())
	{
		ICommandSequence* iMoveToGroupCmdSequence = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
		ASSERT (iMoveToGroupCmdSequence != nil);

		//
		// Move to a group
		//
		int32 numItems = static_cast<int32>(selectedItems.size());
		for (int32 i = 0; i < numItems; ++i)
		{
			uint32 oldPosition = -1;
			int32 oldGroup = iDynamicEventTimingSuite->FindTargetInEvent(eventType, selectedItems[i], oldPosition);	

			if (destNode->IsFirstItemInGroup())
			{
				// Drop onto first item in a group will become the first item in the group;
				// Drop before first item in a group will not be in the group.
				if (fHitLocation == kInsideNode)	
					iDynamicEventTimingSuite->MoveTargetToInEventAt(eventType, selectedItems[i], oldGroup, newGroup, i);	
				else if ((fHitLocation == kAbove) && (position == 0))
				{
					if (i == 0)
					{
						iDynamicEventTimingSuite->MoveTargetBeforeInEvent(eventType, selectedItems[i], oldGroup, newGroup);
						newGroup = iDynamicEventTimingSuite->FindTargetInEvent(eventType, selectedItems[i], oldPosition);
					}
					else
						iDynamicEventTimingSuite->MoveTargetToInEventAt(eventType, selectedItems[i], oldGroup, newGroup, -1);					
				}
				else
				{
					iDynamicEventTimingSuite->MoveTargetToInEventAt(eventType, selectedItems[i], oldGroup, newGroup, 
																fHitLocation == kAbove ? position : position+1);
					++position;
					newGroup = iDynamicEventTimingSuite->FindTargetInEvent(eventType, dynamicTarget, oldPosition);
				}
			}
			else if (destNode->IsLastItemInGroup())
			{
				// Drop onto the last item in a gorup will become the last item in the group;
				// Drop after last item in a group will not be in the group.
				if (fHitLocation == kInsideNode)
					iDynamicEventTimingSuite->MoveTargetToInEventAt(eventType, selectedItems[i], oldGroup, newGroup, -1);			
				else if ((fHitLocation == kBelow) && (position == itemList.size() - 1))
				{
					if (i == 0)
					{
						iDynamicEventTimingSuite->MoveTargetAfterInEvent(eventType, selectedItems[i], oldGroup, newGroup);	
						newGroup = iDynamicEventTimingSuite->FindTargetInEvent(eventType, selectedItems[i], oldPosition);
					}
					else
						iDynamicEventTimingSuite->MoveTargetToInEventAt(eventType, selectedItems[i], oldGroup, newGroup, -1);	
				}
				else
				{
					iDynamicEventTimingSuite->MoveTargetToInEventAt(eventType, selectedItems[i], oldGroup, newGroup, 
																fHitLocation == kAbove ? position : position+1);
				}
			}
			else 
			{
				// Drop between items in a group will make it in the group
				if ((oldPosition < position) && (oldGroup == newGroup))
				{
					iDynamicEventTimingSuite->MoveTargetToInEventAt(eventType, selectedItems[i], oldGroup, newGroup, 
																	fHitLocation == kAbove ? position-1 : position);
					++position;
				}
				else
				{
					iDynamicEventTimingSuite->MoveTargetToInEventAt(eventType, selectedItems[i], oldGroup, newGroup, 
																	fHitLocation == kAbove ? position : position+1);
					++position;
				}

				// don't need to regroup since we already within a group.
			}
		}

		ErrorCode result = (CmdUtils::EndCommandSequence (iMoveToGroupCmdSequence));

		return result;
	}

	ICommandSequence* iMoveToNonGroupCmdSequence = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
	ASSERT (iMoveToNonGroupCmdSequence != nil);

	//
	// Move to non-group
	//
	for (IDynamicEventTimingMgr::DynamicTargetList::const_iterator iter = selectedItems.begin(); iter != selectedItems.end(); ++iter)
	{
		uint32 oldPosition = -1;
		int32 oldGroup = iDynamicEventTimingSuite->FindTargetInEvent(eventType, *iter, oldPosition);	

		if ((fHitLocation == kAbove) && (nodeData != nil))
		{
			if (bSameGroup)
			{
				if (iter == selectedItems.begin())
				{
					iDynamicEventTimingSuite->MoveTargetBeforeInEvent(eventType, *iter, oldGroup, newGroup);			
					newGroup = iDynamicEventTimingSuite->FindTargetInEvent(eventType, *iter, oldPosition);
				}
				else
					iDynamicEventTimingSuite->MoveTargetToInEventAt(eventType, *iter, oldGroup, newGroup, -1);	
			}
			else
				iDynamicEventTimingSuite->MoveTargetBeforeInEvent(eventType, *iter, oldGroup, newGroup);	
		}
		else 
		{
			if (bSameGroup)
			{
				if (iter == selectedItems.begin())
				{
					iDynamicEventTimingSuite->MoveTargetAfterInEvent(eventType, *iter, oldGroup, newGroup);	
					newGroup = iDynamicEventTimingSuite->FindTargetInEvent(eventType, *iter, oldPosition);
				}
				else
					iDynamicEventTimingSuite->MoveTargetToInEventAt(eventType, *iter, oldGroup, newGroup, -1);	
			}
			else
				iDynamicEventTimingSuite->MoveTargetAfterInEvent(eventType, *iter, oldGroup, newGroup);			
		}
	}
	
	ErrorCode result = CmdUtils::EndCommandSequence(iMoveToNonGroupCmdSequence);

	return result;
}

//--------------------------------------------------------------------------------------
// TimingPanelTreeDDTarget::MoveMultipleGroups
//--------------------------------------------------------------------------------------
ErrorCode TimingPanelTreeDDTarget::MoveMultipleGroups(IDynamicEventTimingMgr::DynamicTargetList selectedItems, std::map<int32, IDynamicEventTimingMgr::DynamicTargetList> const &groupTargetList)
{
	ErrorCode result = kSuccess;

	InterfacePtr<const ITreeNodeIDData> nodeData(fOldTarget,UseDefaultIID()); 
	if (!nodeData)
		return result;
	
	EventTriggerType eventType = ddui_utils::GetCurrentEventTypeInTimingPanel();
	ASSERT(eventType != kNoTriggerEvent);

	InterfacePtr<ISelectionManager> iSelectionMgr(Utils<ISelectionUtils>()->QueryActiveSelection ()); 
	IDataBase* db = iSelectionMgr->GetDataBase();

	InterfacePtr<IDynamicEventTimingSuite> iDynamicEventTimingSuite(static_cast<IDynamicEventTimingSuite*>(Utils<ISelectionUtils>()->QuerySuite(IID_IDYNAMICEVENTTIMINGSUITE, iSelectionMgr)));

	TreeNodePtr<const TimingPanelTreeNodeID> destNode(nodeData->Get()); 
	UIDRef destItemUIDRef = UIDRef(db, destNode->GetUID());
	uint32 role = destNode->GetRole();
	uint32 action = destNode->GetAction();

	uint32 position = -1;
	IDynamicEventTimingMgr::DynamicTargetPtr destDynamicTarget (Utils<Facade::IDynamicEventTimingFacade> ()->CreateDynamicTarget(destItemUIDRef, role, action));
	int32 newGroup = iDynamicEventTimingSuite->FindTargetInEvent(eventType, destDynamicTarget, position);

	IDynamicEventTimingMgr::DynamicTargetList itemList;
	iDynamicEventTimingSuite->GetNthGroupInEvent(eventType, newGroup, itemList);
	ASSERT(newGroup >= 0);

	ICommandSequence* iMoveToGroupCmdSequence = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
	ASSERT (iMoveToGroupCmdSequence != nil);

	if (destNode->IsGroupItem())
	{
		//
		// Move to a group
		//			
		int32 newPosition = position;
		for (std::map<int32, IDynamicEventTimingMgr::DynamicTargetList>::const_iterator groupIndexIter = groupTargetList.begin(); groupIndexIter != groupTargetList.end(); ++groupIndexIter)
		{
			uint32 nthGroupPosition = -1;
			IDynamicEventTimingMgr::DynamicTargetList nthGroupItemList = groupIndexIter->second;
			int32 oldGroup = iDynamicEventTimingSuite->FindTargetInEvent(eventType, nthGroupItemList[0], nthGroupPosition);

			if (destNode->IsFirstItemInGroup())
			{
				// Drop onto first item in a group will become the first item in the group;
				// Drop before first item in a group will not be in the group.
				if (fHitLocation == kInsideNode)	
				{
					iDynamicEventTimingSuite->MoveNthGroupToInEventAt (eventType, oldGroup, newGroup, newPosition);
					newGroup = iDynamicEventTimingSuite->FindTargetInEvent(eventType, destDynamicTarget, position);
					int32 numItems = static_cast<int32>(nthGroupItemList.size());
					newPosition += numItems;

				}
				else if ((fHitLocation == kAbove) && (position == 0))
				{
					iDynamicEventTimingSuite->MoveNthGroupInEvent(eventType, oldGroup, newGroup);
					newGroup = iDynamicEventTimingSuite->FindTargetInEvent(eventType, destDynamicTarget, position);
				}
				else
				{
					iDynamicEventTimingSuite->MoveNthGroupToInEventAt (eventType, oldGroup, newGroup, fHitLocation == kAbove ? newPosition : newPosition+1);
					newGroup = iDynamicEventTimingSuite->FindTargetInEvent(eventType, destDynamicTarget, position);
					int32 numItems = static_cast<int32>(nthGroupItemList.size());
					newPosition += numItems;
				}
			}
			else if (destNode->IsLastItemInGroup())
			{
				// Drop onto the last item in a gorup will become the last item in the group;
				// Drop after last item in a group will not be in the group.
				if (fHitLocation == kInsideNode)
				{
					iDynamicEventTimingSuite->MoveNthGroupToInEventAt (eventType, oldGroup, newGroup);
					newGroup = iDynamicEventTimingSuite->FindTargetInEvent(eventType, destDynamicTarget, position);
				}
				else if ((fHitLocation == kBelow) && (position == itemList.size() - 1))
				{
					iDynamicEventTimingSuite->MoveNthGroupInEvent(eventType, oldGroup, newGroup+1);
					if (oldGroup > newGroup)
						++newGroup;
				}
				else
				{
					iDynamicEventTimingSuite->MoveNthGroupInEvent (eventType, oldGroup, (fHitLocation == kBelow) ? newGroup+1 : newGroup);
					if (oldGroup > newGroup)
						++newGroup;
				}
			}
			else 
			{
				iDynamicEventTimingSuite->MoveNthGroupToInEventAt (eventType, oldGroup, newGroup, (fHitLocation == kAbove) ? newPosition : newPosition+1);
				newGroup = iDynamicEventTimingSuite->FindTargetInEvent(eventType, destDynamicTarget, position);
				int32 numItems = static_cast<int32>(nthGroupItemList.size());
				newPosition += numItems;
			}
		}
	}
	else
	{
		for (std::map<int32, IDynamicEventTimingMgr::DynamicTargetList>::const_iterator groupIndexIter = groupTargetList.begin(); groupIndexIter != groupTargetList.end(); ++groupIndexIter)
		{
			IDynamicEventTimingMgr::DynamicTargetList nthGroupItemList = groupIndexIter->second;
			int32 oldGroup = iDynamicEventTimingSuite->FindTargetInEvent(eventType, nthGroupItemList[0], position);

			iDynamicEventTimingSuite->MoveNthGroupInEvent(eventType, oldGroup, fHitLocation == kAbove ? newGroup : newGroup+1);
		}
	}

	result = (CmdUtils::EndCommandSequence (iMoveToGroupCmdSequence));

	return result;
}

//--------------------------------------------------------------------------------------
// TimingPanelTreeDDTarget::DrawHilite
//--------------------------------------------------------------------------------------
void TimingPanelTreeDDTarget::DrawHilite(IControlView*	targetWidget, int32 hitWhere)
{
	if (hitWhere == kInsideNode)
	{
		InterfacePtr<ITreeNodeIDData> iTreeNodeIDData(targetWidget, UseDefaultIID()); 
		if (iTreeNodeIDData)
		{
			NodeID nodeData = iTreeNodeIDData->Get(); 
			TreeNodePtr<TimingPanelTreeNodeID> itemNode(nodeData); 
			if (itemNode->IsGroupItem() && (itemNode->IsFirstItemInGroup() || itemNode->IsLastItemInGroup()))
			{
				//
				// If we hit the first/last item in a group, we will draw hilite for the node.
				//
				PMRect frame = targetWidget->GetFrame();
				frame.Inset(0, 1);	// Top/Bottom shrink 1 pixel
				frame.MoveRel( fTreeScrollerView->GetFrame().LeftTop() );

				if (fLocalPoint.X() >= frame.Left() && fLocalPoint.X() <= frame.Right() && fLocalPoint.Y() >= frame.Top() && fLocalPoint.Y() <= frame.Bottom())
				{
					fNeedsToDrawHighlite = kTrue;
				
					// Save off the area we drew into in window coordinates so we can force that area to draw again to erase
					//
					fPreviousHilite = targetWidget->GetBBox();

					//
					// Save off the old target and hit location so that we can check to see if they are the same and only change the hilite if necessary
					//
					fOldTarget = targetWidget;
					fHitLocation = hitWhere;

					InterfacePtr<IControlView>	myView(this, IID_ICONTROLVIEW);
					SysRgn invalRgn = ::CreateRectSysRgn( fPreviousHilite );
					
					dv_utils::DirectDrawUsingDrawbot(myView, invalRgn, boost::bind(&TimingPanelTreeDDTarget::DoDirectDrawing, this, _1, _2));

					::DeleteSysRgn(invalRgn);

					return;
				}
			}
		}
	}

	//
	// Default is to draw the hilite lines between nodes.
	//
	inherited::DrawHilite(targetWidget, hitWhere);
}

//--------------------------------------------------------------------------------------
// TimingPanelTreeDDTarget::HitTest
//--------------------------------------------------------------------------------------
int32 TimingPanelTreeDDTarget::HitTest(IControlView* widget, const PMPoint& localPoint)
{
	fLocalPoint = localPoint;

	//
	// Get the frame in scroller coordinate and translate it into tree view coordinates.
	//
	PMRect frame = widget->GetFrame();
	frame.MoveRel( fTreeScrollerView->GetFrame().LeftTop() );

	//
	// Check the new location about within the node area.
	//
	if ((localPoint.Y() >= frame.Top() + 2) && (localPoint.Y() <= frame.Bottom() - 2) && 
		(localPoint.X() >= frame.Left() + kTimingPanelGroupWidgetWidth))
	{
		return kInsideNode;
	}
	else if (localPoint.Y() >= frame.Top() && localPoint.Y() <= frame.Bottom())
	{
		if (localPoint.Y() >= (frame.Top() + frame.Height()/2))
			return kBelow;

		return kAbove;
	}
	
	return kNotHit;
}

//--------------------------------------------------------------------------------------
// TimingPanelTreeDDTarget::DirectDrawHilite
//--------------------------------------------------------------------------------------
bool TimingPanelTreeDDTarget::DirectDrawHilite(const dvaui::ui::UI_Node* nodeP, dvaui::drawbot::Drawbot* drawbotP)
{
	if (fNeedsToDrawHighlite)
	{
		fNeedsToDrawHighlite = kFalse;		// Set this as false again.

		InterfacePtr<ITreeNodeIDData> iTreeNodeIDData(fOldTarget, UseDefaultIID()); 
		if (iTreeNodeIDData)
		{
			NodeID nodeData = iTreeNodeIDData->Get(); 
			TreeNodePtr<TimingPanelTreeNodeID> itemNode(nodeData); 

			// Need to translate everything into Tree View coordinates. Get the tree scroller frame for this.
			PMRect treeScrollerFrame = fTreeScrollerView->GetFrame();

			// Draw the background highlight first.
			RealAGMColor hiliteColor;
			InterfacePtr<IInterfaceColors> colors(GetExecutionContextSession(), IID_IINTERFACECOLORS);
			colors->GetRealAGMColor(kInterfaceBlueProgressBack, hiliteColor);			
			PMRect hiliteRect = fOldTarget->GetFrame();
			hiliteRect.MoveRel( treeScrollerFrame.LeftTop() );			// Need to translate into Tree View coordinates.
			dv_utils::DVFillRect(drawbotP, hiliteColor, hiliteRect );			

			// Draw text next. As done in PostTransformPMDrawStringRGBDroverized() 
			InterfacePtr<IControlView> iItemNameView((IControlView*)Utils<IWidgetUtils>()->QueryRelatedWidget(fOldTarget,kTimingItemElementItemNameWidgetID,IID_ICONTROLVIEW)); 
			InterfacePtr<ITextControlData> iNameData(iItemNameView, UseDefaultIID());
			const PMString& itemString = iNameData->GetString();
		
			RealAGMColor textHiliteColor;
			colors->GetRealAGMColor(kInterfaceWhite, textHiliteColor);
			const InterfaceFontInfo& fontInfo = Utils<IWidgetUtils>()->GetAppropriateFontForWidget(iItemNameView);
			
			float size, ascent, descent, leading;
			(void) dv_utils::FontInfoGetDVAFontMetrics(fontInfo, &size, &ascent, &descent, &leading);

			PMRect textRect = iItemNameView->GetFrame();
			textRect.MoveRel( treeScrollerFrame.LeftTop() );	// Need to translate into Tree View coordinates.
			PMPoint startPoint(textRect.Left()+1, hiliteRect.Bottom()-descent*3);
			StringUtils::PMDrawStringRGB(drawbotP, startPoint, kAlignLeft, itemString, fontInfo, textHiliteColor, kFalse, kFalse);

			// Now draw the group widget
			InterfacePtr<IControlView> iGroupWidgetView((IControlView*)Utils<IWidgetUtils>()->QueryRelatedWidget(fOldTarget,kTimingPanelTreeNodeGroupWidgetID,IID_ICONTROLVIEW)); 
			PMRect groupWidgetFrame = iGroupWidgetView->GetFrame();
			groupWidgetFrame.MoveRel( treeScrollerFrame.LeftTop() );	// Need to translate into Tree View coordinates.
			ddui_utils::DrawGroupWidgetLines(hiliteRect.LeftTop(), groupWidgetFrame.Width(), groupWidgetFrame.Height(), drawbotP,
											 kTrue, itemNode->IsFirstItemInGroup(), itemNode->IsLastItemInGroup());
		}
		return true;
	}

	return inherited::DirectDrawHilite(nodeP, drawbotP);
}
