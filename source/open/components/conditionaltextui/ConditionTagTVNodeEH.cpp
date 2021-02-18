//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/ConditionTagTVNodeEH.cpp $
//  
//  Owner: Kevin Van Wiel
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

#include "IActionManager.h"
#include "IActiveContext.h"
#include "IApplication.h"
#include "IConditionTagSuite.h"
#include "IControlView.h"
#include "IDocument.h"
#include "IMenuManager.h"
#include "ISelectionManager.h"
#include "ISubject.h"
#include "ITreeAttributes.h"
#include "ITreeNodeIDData.h"
#include "ITreeViewController.h"
#include "ITreeViewHierarchyAdapter.h"
#include "IWidgetParent.h"
#include "IWorkspace.h"
#include "IUIDData.h"

// ----- Includes -----

#include "TreeNodeEventHandler.h"
#include "UIDList.h"
#include "UIDNodeID.h"
#include "K2Vector.tpp"

// ----- Utility files -----

#include "IConditionalTextUIFacade.h"
#include "IEventUtils.h"

// ----- ID.h files -----

#include "ConditionalTextUIID.h"


class ConditionTagTVNodeEH : public TreeNodeEventHandler
{
public:
	ConditionTagTVNodeEH(IPMUnknown *boss);
	virtual ~ConditionTagTVNodeEH();

	virtual bool16 RButtonDn(IEvent* e);
	virtual bool16 ButtonDblClk(IEvent* e);
	virtual bool16 LButtonDn(IEvent* e);

private:
	void	ApplyOrUnapplyConditionTag(ITreeViewController* treeController, UID tagUID, bool16 bUnconditional, bool16 bAppliedWidget);
	bool16	IsMouseOnEyeballWidget(IEvent* e) const;
	bool16	IsMouseOnAppliedWidget(IEvent* e) const;
};

// =============================================================================
// *** kConditionTagTVNodeEH impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(ConditionTagTVNodeEH, kConditionTagTVNodeEHImpl)

ConditionTagTVNodeEH::ConditionTagTVNodeEH(IPMUnknown *boss) : TreeNodeEventHandler(boss)
{
} // end constructor

ConditionTagTVNodeEH::~ConditionTagTVNodeEH()
{
} // end destructor

// -----------------------------------------------------------------------------

bool16 ConditionTagTVNodeEH::RButtonDn(IEvent* e)
{
    //
    // Bring up the context menu.
    //
    InterfacePtr<IApplication> iApp(GetExecutionContextSession()->QueryApplication());
    InterfacePtr<IActionManager> iActionMgr(iApp->QueryActionManager());
    InterfacePtr<IMenuManager> iMenuMgr(iActionMgr, UseDefaultIID());

    iMenuMgr->HandlePopupMenu("#CondTextUI_RtMenuConditionTagTVNode", e->GlobalWhere(), e->GlobalWhere(), kTrue, this);

    return kTrue;
} // end RButtonDn()

// -----------------------------------------------------------------------------

bool16 ConditionTagTVNodeEH::ButtonDblClk(IEvent* e) 
{
	// Make sure we do this so node widgets like inline edit know about the double-click.
	if (TreeNodeEventHandler::ButtonDblClk(e))
		return kTrue;

	// Check if the mouse is on the eyeball or applied icon.
	if (this->IsMouseOnEyeballWidget(e) || this->IsMouseOnAppliedWidget(e))
		return kTrue;

	// Display the options dialog.
	InterfacePtr<IWidgetParent> treeNodeWidget(this, UseDefaultIID());
	InterfacePtr<ITreeNodeIDData> nodeID(treeNodeWidget, UseDefaultIID());

	InterfacePtr<ITreeViewController> treeController((ITreeViewController*)treeNodeWidget->QueryParentFor(IID_ITREEVIEWCONTROLLER));
	InterfacePtr<ITreeViewHierarchyAdapter> adapter(treeController, UseDefaultIID());
	if (nodeID->Get() != adapter->GetRootNode())
	{
		TreeNodePtr<UIDNodeID> tagNode(nodeID->Get());
		IActiveContext* ac = GetExecutionContextSession()->GetActiveContext();
		IWorkspace* ws = ac->GetContextWorkspace();
		if (ws != nil)
			Utils<Facade::IConditionalTextUIFacade>()->DoConditionOptionsDialog(ws, tagNode->GetUID());
	}

	return kTrue;
} // end ButtonDblClk()

// -----------------------------------------------------------------------------

bool16 ConditionTagTVNodeEH::LButtonDn(IEvent* e)
{
	// This is essentially the same as TreeNodeEventHandler except that 
	// don't change the selection if clicked the applied widget.

	if (TreeNodeEventHandler::HandleLButtonDnBeforeSelectionProcessing(e))
		return kTrue;
		
	InterfacePtr<IWidgetParent>	wp( this, UseDefaultIID());
	InterfacePtr<ITreeAttributes>	attribs((ITreeAttributes*)wp->QueryParentFor(IID_ITREEATTRIBUTES));
	InterfacePtr<ITreeViewController>	controller(attribs, UseDefaultIID());
	
	// Process selection rules, unless clicked on applied widget.
	bool16 bAppliedWidget(this->IsMouseOnAppliedWidget(e));
	if (!bAppliedWidget)
		controller->ProcessSelectionRules(e, ::GetUID(this) );

	// Handle drag and drop.
	if (this->HandleTreeNodeDragDrop(e))
		return kTrue;
				
	// Do the apply or unapply.
	if (!e->ShiftKeyDown() && !e->CmdKeyDown())
	{
		InterfacePtr<ITreeViewHierarchyAdapter> adapter(controller, IID_ITREEVIEWHIERARCHYADAPTER);
		InterfacePtr<ITreeNodeIDData> nodeIDData(wp, UseDefaultIID());
		bool16 bUnconditional = nodeIDData->Get() == adapter->GetRootNode();

		TreeNodePtr<UIDNodeID> tagNode(nodeIDData->Get());
		UID tagUID = tagNode->GetUID();
		this->ApplyOrUnapplyConditionTag(controller, tagUID, bUnconditional, bAppliedWidget);
	}

	return TreeNodeEventHandler::HandleLButtonDnAfterSelectionProcessing(e);
}

// -----------------------------------------------------------------------------

void ConditionTagTVNodeEH::ApplyOrUnapplyConditionTag(ITreeViewController* treeController, UID tagUID, bool16 bUnconditional, bool16 bAppliedWidget)
{
	IActiveContext* ac = GetExecutionContextSession()->GetActiveContext();
	ISelectionManager* selMgr = ac->GetContextSelection();
	InterfacePtr<IConditionTagSuite> conditionsSuite(static_cast<IConditionTagSuite*>(selMgr->QueryIntegratorSuite(IID_ICONDITIONTAGSUITE, ISelectionManager::kEnabledInterface)));
	if (conditionsSuite)
	{
		K2Vector<UID> tags;
		if (bUnconditional)
		{
			// User wants to to make text unconditional; apply empty list of conditions.
			conditionsSuite->ApplyConditionTags(tags, kTrue /* remove others */);
		}
		else
		{
			tags.push_back(tagUID);

			if (::IsOptionAltKeyPressed())
			{
				// User pressed option-key so apply the condition tag and remove others (if any).
				conditionsSuite->ApplyConditionTags(tags, kTrue /* remove others */);
			}
			else if (bAppliedWidget)
			{
				// If the condition tag clicked is not already applied to all characters then apply it; 
				// otherwise, remove it. Does not remove other condition tags.
				UIDList appliedToAllChars;
				UIDList appliedToSomeChars;
				conditionsSuite->GetAppliedConditionTags(appliedToAllChars, appliedToSomeChars);
				if (K2find(appliedToAllChars, tagUID) == appliedToAllChars.end())
				{
					// Apply the condition tag.
					conditionsSuite->ApplyConditionTags(tags, kFalse);
				}
				else if (bAppliedWidget)
				{
					// Unapply the condition tag.
					conditionsSuite->UnapplyConditionTags(tags);
				}
			}
			else
			{
				UIDList appliedToAllChars;
				UIDList appliedToSomeChars;
				conditionsSuite->GetAppliedConditionTags(appliedToAllChars, appliedToSomeChars);
				if (K2find(appliedToAllChars, tagUID) == appliedToAllChars.end()/* not yet applied */)
				{
					// Apply new but don't unapply existing. 
					conditionsSuite->ApplyConditionTags(tags, kFalse);
				}
			}
		}
	}
}

// -----------------------------------------------------------------------------

bool16	ConditionTagTVNodeEH::IsMouseOnEyeballWidget(IEvent* e) const 
{
	GSysPoint globalWhere = e->GlobalWhere();

	InterfacePtr<IPanelControlData> panel(this, UseDefaultIID());
	ASSERT(panel);

	IControlView* eyeballWidgetView = panel->FindWidget(kConditionTagEyeballWidgetID);
	if (eyeballWidgetView == nil)
		return kFalse;

	PMPoint localWhere = eyeballWidgetView->GlobalToWindow(globalWhere);
	
	PMRect rect = eyeballWidgetView->GetBBox();
	bool16 isPointInEyeballWidgetRect = (rect.PointIn(localWhere));

	return isPointInEyeballWidgetRect;
} // end IsMouseOnEyeballWidget()

// -----------------------------------------------------------------------------

bool16	ConditionTagTVNodeEH::IsMouseOnAppliedWidget(IEvent* e) const 
{
	GSysPoint globalWhere = e->GlobalWhere();

	InterfacePtr<IPanelControlData> panel(this, UseDefaultIID());
	ASSERT(panel);

	IControlView* appliedWidgetView = panel->FindWidget(kConditionTagAppliedStateWidgetId);
	if (appliedWidgetView == nil)
		return kFalse;

	PMPoint localWhere = appliedWidgetView->GlobalToWindow(globalWhere);
	
	PMRect rect = appliedWidgetView->GetBBox();
	bool16 isPointInAppliedWidgetRect = (rect.PointIn(localWhere));

	return isPointInAppliedWidgetRect;
} // end IsMouseOnAppliedWidget()
