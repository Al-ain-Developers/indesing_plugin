//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actionpanel/BehaviorTreeObserver.cpp $
//  
//  Owner: Michael Burbidge
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

// ----- Interface Includes -----

#include "IActionMenuManager.h"
#include "IBehaviorData.h"
#include "IBehaviorSuite.h"
#include "IBehaviorEvent.h"
#include "IBehaviorEventData.h"
#include "IDocument.h"
#include "IDropDownListController.h"
#include "IFormFieldSuite.h"
#include "ISubject.h"
#include "IListControlDataOf.h"
#include "IPanelControlData.h"
#include "ISelectionDataSuite.h"
#include "ITreeNodeIDData.h"
#include "ITreeViewController.h"
#include "ITreeViewHierarchyAdapter.h"
#include "ITreeViewMgr.h"

// ----- Implementation Includes -----

#include "UIDNodeID.h"
#include "BehaviorSelectionSuiteData.h"
#include "CActiveSelectionObserver.h"
#include "K2Pair.h"
#include "K2Vector.tpp"	// ...Mac Release complains otherwise
#include "PMString.h"
#include "ListLazyNotificationData.h"

#include "FormFieldUIUtils.h"
#include "SelectionUtils.h"
#include "WidgetUtils.h"

#include "BehaviorUIID.h"
#include "FormFieldUIID.h"
#include "GenericID.h"

//========================================================================================
// CLASS BehaviorsTreeObserver
//========================================================================================

class BehaviorsTreeObserver : public CActiveSelectionObserver
{
public:
	BehaviorsTreeObserver(IPMUnknown *boss);
	virtual ~BehaviorsTreeObserver();

	virtual void AutoAttach();
	virtual void AutoDetach();
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);
	virtual void LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data);
	
protected:
	virtual void HandleSelectionChanged(const ISelectionMessage*);
	virtual void HandleSelectionAttributeChanged (const ISelectionMessage*);

private:
	void		UpdateActionList(IBehaviorSuite* actionSuite);
	void		UpdateActionEnableStates();
	void		UpdateNoActionsAddedInfoWidget();
	void		InitializeEventChoices();
	void		FilterChangesForSelectedEvent(K2Vector<UID> *changesList);

	void		AttachToDocument();
	void		DetachFromDocument();

	ITriStateControlData*	QueryTriStateControlData(IControlView* view) const;

	bool	 fEventListBuilt;
	bool	 fUpdating;
	int32	 fSelectedEventIndex;
	UIDRef	 fCurrentDocRef;
};

//========================================================================================
// METHODS BehaviorsTreeObserver
//========================================================================================

CREATE_PMINTERFACE(BehaviorsTreeObserver, kBehaviorsTreeObserverImpl)

//----------------------------------------------------------------------------------------
// BehaviorsTreeObserver::BehaviorsTreeObserver
//----------------------------------------------------------------------------------------
BehaviorsTreeObserver::BehaviorsTreeObserver(IPMUnknown *boss) :
	CActiveSelectionObserver(boss, IID_IOBSERVER),
	fEventListBuilt(false),
	fSelectedEventIndex(0),
	fUpdating(false),
	fCurrentDocRef(nil, kInvalidUID)
{
}

//----------------------------------------------------------------------------------------
// BehaviorsTreeObserver::~BehaviorsTreeObserver
//----------------------------------------------------------------------------------------
BehaviorsTreeObserver::~BehaviorsTreeObserver()
{
}

//----------------------------------------------------------------------------------------
// BehaviorsTreeObserver::AutoAttach
//----------------------------------------------------------------------------------------

void BehaviorsTreeObserver::AutoAttach()
{
	InterfacePtr<IFormFieldSuite> iFormFieldSuite(FormFieldUIUtils::QueryFormSuite());
	InterfacePtr<ISelectionDataSuite> iSelectionDataSuite (static_cast<ISelectionDataSuite*>(Utils<ISelectionUtils>()->QuerySuite(IID_ISELECTIONDATASUITE)));
	bool16 isSingleSelection = iSelectionDataSuite && iSelectionDataSuite->GetSelectionCount() == 1;

	if ( !fUpdating && isSingleSelection && iFormFieldSuite && iFormFieldSuite->IsFieldSelection() && !iFormFieldSuite->IsFieldSelectionOfType(kMultiStateObjectItemBoss))
	{
		fUpdating = true;
		InitializeEventChoices();
		fUpdating = false;
	}

	CActiveSelectionObserver::AutoAttach();
	AttachToWidget(kBehaviorsTreeWidgetID, IID_ITREEVIEWCONTROLLER);
	AttachToWidget(kButtonEventChoicesWidgetID, IID_ISTRINGLISTCONTROLDATA);
	AttachToDocument();

	InterfacePtr<IBehaviorSuite> actionSuite (SelectionUtils::QuerySuite<IBehaviorSuite>());
	UpdateActionList(actionSuite);
}

//----------------------------------------------------------------------------------------
// BehaviorsTreeObserver::AutoDetach
//----------------------------------------------------------------------------------------

void BehaviorsTreeObserver::AutoDetach()
{
	CActiveSelectionObserver::AutoDetach();
	DetachFromWidget(kBehaviorsTreeWidgetID, IID_ITREEVIEWCONTROLLER);
	DetachFromWidget(kButtonEventChoicesWidgetID, IID_ISTRINGLISTCONTROLDATA);
	DetachFromDocument();
}

// -----------------------------------------------------------------------------

void BehaviorsTreeObserver::AttachToDocument()
{
	if (fCurrentSelection)
	{
		InterfacePtr<IDocument> doc(fCurrentSelection->GetDataBase(), fCurrentSelection->GetDataBase()->GetRootUID(), UseDefaultIID());
		InterfacePtr<ISubject> docSubject(doc, IID_ISUBJECT);
		if (docSubject)
		{
			if (!docSubject->IsAttached(ISubject::kLazyAttachment, this, IID_IPAGEITEMNAME, IID_IOBSERVER)) 
				docSubject->AttachObserver(ISubject::kLazyAttachment, this, IID_IPAGEITEMNAME, IID_IOBSERVER); 
			if (!docSubject->IsAttached(ISubject::kLazyAttachment, this, IID_IACTIONSADDED_DOCUMENT, IID_IOBSERVER))
				docSubject->AttachObserver(ISubject::kLazyAttachment, this, IID_IACTIONSADDED_DOCUMENT, IID_IOBSERVER);
			if (!docSubject->IsAttached(ISubject::kLazyAttachment, this, IID_IACTIONSDELETED_DOCUMENT, IID_IOBSERVER))
				docSubject->AttachObserver(ISubject::kLazyAttachment, this, IID_IACTIONSDELETED_DOCUMENT, IID_IOBSERVER);
			if (!docSubject->IsAttached(ISubject::kLazyAttachment, this, IID_IACTIONSMOVED_DOCUMENT, IID_IOBSERVER))
				docSubject->AttachObserver(ISubject::kLazyAttachment, this, IID_IACTIONSMOVED_DOCUMENT, IID_IOBSERVER);
			if (!docSubject->IsAttached(ISubject::kLazyAttachment, this, IID_IACTIONSCHANGED_DOCUMENT, IID_IOBSERVER))
				docSubject->AttachObserver(ISubject::kLazyAttachment, this, IID_IACTIONSCHANGED_DOCUMENT, IID_IOBSERVER);
			if (!docSubject->IsAttached(ISubject::kLazyAttachment, this, IID_IACTIONSENABLED_DOCUMENT, IID_IOBSERVER))
				docSubject->AttachObserver(ISubject::kLazyAttachment, this, IID_IACTIONSENABLED_DOCUMENT, IID_IOBSERVER);

			fCurrentDocRef = UIDRef(fCurrentSelection->GetDataBase(), fCurrentSelection->GetDataBase()->GetRootUID());
		}	
	}
} // end AttachToDocument()

// -----------------------------------------------------------------------------

void BehaviorsTreeObserver::DetachFromDocument()
{
	InterfacePtr<ISubject> docSubject(fCurrentDocRef, IID_ISUBJECT);
	if (docSubject)
	{
		if (docSubject->IsAttached(ISubject::kLazyAttachment, this, IID_IPAGEITEMNAME, IID_IOBSERVER))
			docSubject->DetachObserver(ISubject::kLazyAttachment, this, IID_IPAGEITEMNAME, IID_IOBSERVER);
		if (docSubject->IsAttached(ISubject::kLazyAttachment, this, IID_IACTIONSADDED_DOCUMENT, IID_IOBSERVER))
			docSubject->DetachObserver(ISubject::kLazyAttachment, this, IID_IACTIONSADDED_DOCUMENT, IID_IOBSERVER);
		if (docSubject->IsAttached(ISubject::kLazyAttachment, this, IID_IACTIONSDELETED_DOCUMENT, IID_IOBSERVER))
			docSubject->DetachObserver(ISubject::kLazyAttachment, this, IID_IACTIONSDELETED_DOCUMENT, IID_IOBSERVER);
		if (docSubject->IsAttached(ISubject::kLazyAttachment, this, IID_IACTIONSMOVED_DOCUMENT, IID_IOBSERVER))
			docSubject->DetachObserver(ISubject::kLazyAttachment, this, IID_IACTIONSMOVED_DOCUMENT, IID_IOBSERVER);
		if (docSubject->IsAttached(ISubject::kLazyAttachment, this, IID_IACTIONSCHANGED_DOCUMENT, IID_IOBSERVER))
			docSubject->DetachObserver(ISubject::kLazyAttachment, this, IID_IACTIONSCHANGED_DOCUMENT, IID_IOBSERVER);
		if (docSubject->IsAttached(ISubject::kLazyAttachment, this, IID_IACTIONSENABLED_DOCUMENT, IID_IOBSERVER))
			docSubject->DetachObserver(ISubject::kLazyAttachment, this, IID_IACTIONSENABLED_DOCUMENT, IID_IOBSERVER);
	}

	if (fCurrentDocRef != UIDRef(nil,kInvalidUID))
		fCurrentDocRef = UIDRef(nil,kInvalidUID);
} // end DetachFromDocument()

//----------------------------------------------------------------------------------------
// BehaviorsTreeObserver::Update
//----------------------------------------------------------------------------------------

void BehaviorsTreeObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy)
{
	CActiveSelectionObserver::Update(theChange, theSubject, protocol, changedBy);
	
	if ( protocol == IID_ISTRINGLISTCONTROLDATA )
	{
		InterfacePtr<IDropDownListController> eventChoice(theSubject, IID_IDROPDOWNLISTCONTROLLER);
		if ( eventChoice )
			fSelectedEventIndex = eventChoice->GetSelected();

		HandleSelectionChanged(nil);
	}
	else if (protocol == IID_IACTIVECONTEXT)
	{
		UIDRef newDocRef(fCurrentSelection->GetDataBase(), fCurrentSelection->GetDataBase()->GetRootUID());

		if (fCurrentDocRef != newDocRef)
		{
			// Detach the old document and attach to the new one.

			this->DetachFromDocument();

			if (newDocRef.GetDataBase() != nil && newDocRef.GetUID() != kInvalidUID)
				this->AttachToDocument();
		}
	}
}

//----------------------------------------------------------------------------------------
// BehaviorsTreeObserver::LazyUpdate
//----------------------------------------------------------------------------------------

void BehaviorsTreeObserver::LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data)
{
	InterfacePtr<ITreeViewMgr>	treeViewMgr(this, UseDefaultIID());
	if (!treeViewMgr) return;

	InterfacePtr<ITreeViewHierarchyAdapter> treeViewAdapter(treeViewMgr, UseDefaultIID());
	if (!treeViewAdapter) return;

	if (protocol == IID_IACTIONSADDED_DOCUMENT || 
		protocol == IID_IACTIONSDELETED_DOCUMENT || 
		protocol == IID_IACTIONSMOVED_DOCUMENT ||
		protocol == IID_IACTIONSCHANGED_DOCUMENT ||
		protocol == IID_IACTIONSENABLED_DOCUMENT)
	{
		const ListLazyNotificationData<UID> *listData = static_cast<const ListLazyNotificationData<UID> *>(data);
		InterfacePtr<IFormFieldSuite> iFormFieldSuite(FormFieldUIUtils::QueryFormSuite());
		InterfacePtr<ISelectionDataSuite> iSelectionDataSuite (static_cast<ISelectionDataSuite*>(Utils<ISelectionUtils>()->QuerySuite(IID_ISELECTIONDATASUITE)));
		bool16 isSingleSelection = iSelectionDataSuite && iSelectionDataSuite->GetSelectionCount() == 1;

		if (iFormFieldSuite && isSingleSelection && iFormFieldSuite->IsFieldSelection() && 
			!iFormFieldSuite->IsFieldSelectionOfType(kMultiStateObjectItemBoss))
		{
			if(listData)
			{
				InterfacePtr<ITreeViewController> tvController(this, UseDefaultIID());
				NodeID rootNode = treeViewAdapter->GetRootNode();

				// Update the items in the tree.
				K2Vector<UID> addedItems, deletedItems, changedItems;
				listData->BreakoutChanges(&addedItems, &deletedItems, &changedItems);	

				// Filter out items that are not in the selected event since scripting can
				// change these, but our tree doesn't care since it's only interested in the
				// items for the selected event. Don't filter deleted items since these
				// needed to be removed and the tree manager doesn't complain.
				FilterChangesForSelectedEvent(&addedItems);
				FilterChangesForSelectedEvent(&changedItems);

				K2Vector<NodeID> nodes;
				nodes.clear();
				for (int32 i = 0; i < addedItems.size(); i++)
					nodes.push_back(UIDNodeID::Create(addedItems[i]));
				if (nodes.size() > 0)
				{
					// Add the new action nodes.
					treeViewMgr->NodesAdded(nodes);

					// Select the first action node that was added.
					tvController->DeselectAll(kFalse, kTrue);
					tvController->Select(nodes[0], kTrue, kTrue);
					treeViewMgr->ScrollToNode(nodes[0], ITreeViewMgr::eScrollIntoView);
				}

				bool bDeletedNodeIsSelected(false);
				nodes.clear();
				for (int32 i = 0; i < deletedItems.size(); i++)
				{
					nodes.push_back(UIDNodeID::Create(deletedItems[i]));
					if (!bDeletedNodeIsSelected)
						bDeletedNodeIsSelected = tvController->IsSelected(nodes[i]);
				}
				if (nodes.size() > 0)
				{
					// Delete the action node and select the one node that followed it (if any)
					treeViewMgr->BeforeNodesDeleted(nodes);

					if (bDeletedNodeIsSelected)
					{
						if (treeViewAdapter->GetNumChildren(rootNode) > 0)
						{
							// Select the last action node (if any). This retains existing behavior but it seems 
							// strange compared to other panels, shouldn't we select the one above??
							tvController->DeselectAll(kFalse, kTrue);

							NodeID selectNode = treeViewAdapter->GetNthChild(rootNode, treeViewAdapter->GetNumChildren(rootNode)-1);
							tvController->Select(selectNode, kTrue, kTrue);
							treeViewMgr->ScrollToNode(selectNode, ITreeViewMgr::eScrollIntoView);
						}
						else
							tvController->DeselectAll(kTrue, kTrue);
					}
				}

				for (int32 i = 0; i < changedItems.size(); i++)
				{
					NodeID behaviorNode = UIDNodeID::Create(changedItems[i]);
					bool16 reselect = tvController->IsSelected(behaviorNode) ? kTrue : kFalse;

					treeViewMgr->NodeMoved(behaviorNode, rootNode);

					if (reselect)
						tvController->Select(behaviorNode, kFalse, kTrue);
				}
			}
			else
			{
				HandleSelectionChanged(nil);
			}
		}
	}
	else if (protocol == IID_IPAGEITEMNAME)
	{
		InterfacePtr<ITreeViewMgr> viewMgr(this, UseDefaultIID());
		if (viewMgr)
			viewMgr->ChangeRoot();
	}
	UpdateNoActionsAddedInfoWidget();
}

//----------------------------------------------------------------------------------------
// BehaviorsTreeObserver::HandleSelectionChanged
//----------------------------------------------------------------------------------------

void BehaviorsTreeObserver::HandleSelectionChanged(const ISelectionMessage* selectionMessage)
{
	if ( !fUpdating )
	{
		fUpdating = true;
		
		InterfacePtr<IFormFieldSuite> iFormFieldSuite(FormFieldUIUtils::QueryFormSuite());
		InterfacePtr<ISelectionDataSuite> iSelectionDataSuite (static_cast<ISelectionDataSuite*>(Utils<ISelectionUtils>()->QuerySuite(IID_ISELECTIONDATASUITE)));
		bool16 isSingleSelection = iSelectionDataSuite && iSelectionDataSuite->GetSelectionCount() == 1;

		if ( selectionMessage && selectionMessage->GetMessageType () == ISelectionMessage::kSelectionChanged
			 && iFormFieldSuite && isSingleSelection && iFormFieldSuite->IsFieldSelection() && !iFormFieldSuite->IsFieldSelectionOfType(kMultiStateObjectItemBoss))
		{
			InitializeEventChoices();
		}
		fUpdating = false;

		InterfacePtr<IBehaviorSuite> actionSuite (SelectionUtils::QuerySuite<IBehaviorSuite>());
		UpdateActionList(actionSuite);
	}
}

//----------------------------------------------------------------------------------------
// BehaviorsTreeObserver::InitializeEventChoices: 
//----------------------------------------------------------------------------------------

void BehaviorsTreeObserver::InitializeEventChoices()
{
	InterfacePtr<IDropDownListController> eventChoice((IDropDownListController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kButtonEventChoicesWidgetID, IID_IDROPDOWNLISTCONTROLLER));
	if ( eventChoice )
	{
		if ( !fEventListBuilt )
		{
			InterfacePtr<IActionMenuManager> actionMenuMgr(GetExecutionContextSession(), UseDefaultIID());
			actionMenuMgr->BuildEventMenuSupportingSelection(eventChoice, 0);
			fSelectedEventIndex = eventChoice->GetSelected();

			fEventListBuilt = true;
		}
		
		// Check the list of actions associated with the selected event. If empty, look for an
		// event that has a non-empty list of actions.
		InterfacePtr<IBehaviorSuite> behaviorSuite (SelectionUtils::QuerySuite<IBehaviorSuite>());
		if ( behaviorSuite )
		{
			InterfacePtr< IListControlDataOf< K2Pair<PMString, int32> > > eventData(eventChoice, IID_ILISTCONTROLDATA);
			if ( fSelectedEventIndex >= 0 && fSelectedEventIndex < eventData->Length() )
			{
				ActionEvent selectedEvent =  (*eventData)[fSelectedEventIndex].second;
				
				IDataBase* db;
				std::vector<UID> behaviorsForSelectedEvent;
				
				behaviorSuite->GetActions(selectedEvent, db, behaviorsForSelectedEvent);
				if ( behaviorsForSelectedEvent.empty() )
				{
					std::vector< std::pair<ActionEvent, UID> > behaviors;
					
					behaviorSuite->GetEventAndActions(db, behaviors);
					if ( !behaviors.empty() )
					{
						selectedEvent = behaviors.begin()->first;
						int32 count = eventData->Length();
						for ( int32 index = 0; index < count; ++index )
						{
							if ( (*eventData)[index].second == selectedEvent )
							{
								eventChoice->Select(index, kFalse, kTrue);
								fSelectedEventIndex = index;
								break;
							}
						}							
					}
				}
			}
		}
		
		if ( !eventChoice->IsSelected(fSelectedEventIndex) )
			eventChoice->Select(fSelectedEventIndex, kFalse, kTrue);
	}
}

//----------------------------------------------------------------------------------------
// BehaviorsTreeObserver::HandleSelectionAttributeChanged
//----------------------------------------------------------------------------------------

void BehaviorsTreeObserver::HandleSelectionAttributeChanged (const ISelectionMessage* selectionMsg)
{
	if (selectionMsg->WasSuiteAffected (IID_IBEHAVIORSUITE))
	{
		BehaviorSelectionSuiteData* suiteData = 
			static_cast<BehaviorSelectionSuiteData*>(selectionMsg->GetSuiteBroadcastData (IID_IBEHAVIORSUITE));

		if (suiteData->GetMessage() == IID_IACTIONSCHANGED_DOCUMENT || suiteData->GetMessage() == IID_IACTIONSENABLED_DOCUMENT)
			UpdateActionEnableStates();
	}
}


//----------------------------------------------------------------------------------------
// BehaviorsTreeObserver::UpdateActionList
//----------------------------------------------------------------------------------------

void BehaviorsTreeObserver::UpdateActionList(IBehaviorSuite* actionSuite)
{
	InterfacePtr<ITreeViewMgr> viewMgr(this, UseDefaultIID());
	if (viewMgr)
		viewMgr->ChangeRoot();

	InterfacePtr<ITreeViewHierarchyAdapter> viewAdapter(viewMgr, UseDefaultIID());
	InterfacePtr<ITreeViewController> viewController(viewMgr, UseDefaultIID());
	ASSERT(viewAdapter != nil && viewController != nil);

	NodeID rootNode = viewAdapter->GetRootNode();
	if (viewAdapter->GetNumChildren(rootNode) == 0)
	{
		// Deselect so that the "holder" will refresh the subpanel.
		viewController->DeselectAll(kTrue, kTrue);
	}
	else
	{
		K2Vector<NodeID> selection;
		viewController->GetSelectedItems(selection);
		if (selection.size() == 0)
		{
			// Select the last action node (if any).
			NodeID selectNode = viewAdapter->GetNthChild(rootNode, viewAdapter->GetNumChildren(rootNode)-1);
			if (selectNode != nil && !viewController->IsSelected(selectNode))
			{
				viewController->DeselectAll(kFalse, kTrue);
				viewController->Select(selectNode, kTrue, kTrue);
				viewMgr->ScrollToNode(selectNode, ITreeViewMgr::eScrollIntoView);
			}
		}
	}

	UpdateNoActionsAddedInfoWidget();
}

//----------------------------------------------------------------------------------------
// BehaviorsTreeObserver::UpdateActionEnableStates
//----------------------------------------------------------------------------------------

void BehaviorsTreeObserver::UpdateActionEnableStates()
{
	InterfacePtr<IPanelControlData> widgets((IPanelControlData *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kTreeScrollerWidgetID, IID_IPANELCONTROLDATA));
	for (int32 i = 0; i < widgets->Length(); i++)
	{
		InterfacePtr<ITreeNodeIDData> nodeData(widgets->GetWidget(i), UseDefaultIID());

		TreeNodePtr<UIDNodeID>	behaviorNode(nodeData->Get());
		if (behaviorNode->GetUID() != kInvalidUID)
		{
			InterfacePtr<ITriStateControlData> triStateData(QueryTriStateControlData(widgets->GetWidget(i)));
			UIDRef uidRef = UIDRef(fCurrentSelection->GetDataBase(), behaviorNode->GetUID());
			InterfacePtr<IBehaviorData> behavior(uidRef, UseDefaultIID());
			if (behavior == nil || triStateData == nil || triStateData->IsSelected() && behavior->IsEnabled()
					|| triStateData->IsDeselected() && behavior->IsDisabled())
				;
			else
				triStateData->SetState(behavior->IsEnabled() ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected, kTrue, kFalse);
			}
	}
}

//----------------------------------------------------------------------------------------
// BehaviorsTreeObserver::UpdateNoActionsAddedInfoWidget
//----------------------------------------------------------------------------------------

void BehaviorsTreeObserver::UpdateNoActionsAddedInfoWidget()
{
	InterfacePtr<IControlView> infoView((IControlView *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kNoActionsAddedTextWidgetID, IID_ICONTROLVIEW));		
	if (infoView)
	{
		InterfacePtr<IFormFieldSuite> iFormFieldSuite(FormFieldUIUtils::QueryFormSuite());
		InterfacePtr<ISelectionDataSuite> iSelectionDataSuite (static_cast<ISelectionDataSuite*>(Utils<ISelectionUtils>()->QuerySuite(IID_ISELECTIONDATASUITE)));
		bool16 isSingleSelection = iSelectionDataSuite && iSelectionDataSuite->GetSelectionCount() == 1;
		bool16 isFormField = isSingleSelection && iFormFieldSuite && iFormFieldSuite->IsFieldSelection() && !iFormFieldSuite->IsFieldSelectionOfType(kMultiStateObjectItemBoss) ;

		InterfacePtr<ITreeViewHierarchyAdapter> adapter(this, UseDefaultIID());
		if (!isFormField || (adapter && adapter->GetNumChildren(adapter->GetRootNode()) > 0))
			infoView->HideView();
		else
			infoView->ShowView();
	}
}

//----------------------------------------------------------------------------------------
// BehaviorsTreeObserver::QueryTriStateControlData
//----------------------------------------------------------------------------------------

ITriStateControlData* BehaviorsTreeObserver::QueryTriStateControlData(IControlView* view) const
{
	InterfacePtr<IPanelControlData> panel(view, UseDefaultIID());
	
	// The following code will work if the on/off button is within another widget
	InterfacePtr<IPanelControlData> iconPanel(panel->GetWidget(0), UseDefaultIID());
	return (ITriStateControlData*) iconPanel->GetWidget(0)->QueryInterface(IID_ITRISTATECONTROLDATA);
}

//----------------------------------------------------------------------------------------
// BehaviorsTreeObserver::FilterChangesForSelectedEvent
//----------------------------------------------------------------------------------------

void BehaviorsTreeObserver::FilterChangesForSelectedEvent(K2Vector<UID> *changesList)
{
	InterfacePtr<IBehaviorSuite> behaviorSuite (SelectionUtils::QuerySuite<IBehaviorSuite>());
	if (behaviorSuite)
	{
		IDataBase* db;
		std::vector<UID> behaviorsForSelectedEvent;				
		behaviorSuite->GetActions(FormFieldUIUtils::GetSelectedEvent(this), db, behaviorsForSelectedEvent);

		if (behaviorsForSelectedEvent.empty())
		{
			changesList->clear();
		}
		else
		{
			K2Vector<UID>::iterator changeItem = changesList->begin();
			while (changeItem != changesList->end())
			{
				if (std::find(behaviorsForSelectedEvent.begin(), behaviorsForSelectedEvent.end(), *changeItem) == behaviorsForSelectedEvent.end())
					changeItem = changesList->erase(changeItem);
				else
					changeItem++;
			}
		}
	}
}