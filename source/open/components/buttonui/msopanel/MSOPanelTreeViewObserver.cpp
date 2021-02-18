//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/msopanel/MSOPanelTreeViewObserver.cpp $
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
#include "CObserver.h"

// ----- Interfaces -----

#include "IActiveContext.h"
#include "IAppearanceSuite.h"
#include "IBoolData.h"
#include "IDocument.h"
#include "IFormFieldSuite.h"
#include "IPanelControlData.h"
#include "ISubject.h"
#include "ITextControlData.h"
#include "ITreeViewController.h"
#include "ITreeViewHierarchyAdapter.h"
#include "ITreeViewMgr.h"

// ----- Includes -----

#include "ListLazyNotificationData.h"
#include "MSOStateNodeID.h"
#include "K2Vector.tpp"

// ----- Utility files -----

#include "FormFieldUIUtils.h"
#include "IFormFieldUtils.h"
#include "MSOPanelUtils.h"
#include "IPalettePanelUtils.h"

// ----- ID.h files -----

#include "FormFieldID.h"
#include "FormFieldUIID.h"
#include "GenericID.h"
#include "DocumentID.h"


class MSOPanelTreeViewObserver : public CObserver
{
public:
	MSOPanelTreeViewObserver(IPMUnknown *boss);
	virtual ~MSOPanelTreeViewObserver();

	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
	virtual void LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data);

	virtual void AutoAttach();			
	virtual void AutoDetach();

private:
	void	AttachToDocument(UIDRef docRef);
	void	DetachFromDocument();

	UIDRef	fCurrentDocRef;
};

// =============================================================================
// *** MSOPanelTreeViewObserver impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(MSOPanelTreeViewObserver, kMSOPanelTreeViewObserverImpl)

MSOPanelTreeViewObserver::MSOPanelTreeViewObserver(IPMUnknown *boss) :
	CObserver(boss), fCurrentDocRef(nil, kInvalidUID)
{
} // end constructor

MSOPanelTreeViewObserver::~MSOPanelTreeViewObserver()
{
} // end destructor

// -----------------------------------------------------------------------------

void MSOPanelTreeViewObserver::AutoAttach()
{
	InterfacePtr<ISubject> mySubject(this, UseDefaultIID());
	if (mySubject && !mySubject->IsAttached(ISubject::kRegularAttachment, this, IID_ITREEVIEWCONTROLLER, IID_IOBSERVER))
		mySubject->AttachObserver(ISubject::kRegularAttachment, this, IID_ITREEVIEWCONTROLLER, IID_IOBSERVER);

	// Attach to the active context
	IActiveContext *context = GetExecutionContextSession()->GetActiveContext();
	if (context)
	{
		InterfacePtr<ISubject> contextSubject(context, IID_ISUBJECT);
		if (contextSubject && !contextSubject->IsAttached(ISubject::kRegularAttachment, this, IID_IACTIVECONTEXT, IID_IOBSERVER))
			contextSubject->AttachObserver(ISubject::kRegularAttachment, this, IID_IACTIVECONTEXT, IID_IOBSERVER);
	}

	IDocument* doc = context->GetContextDocument();
	if (doc)
		this->AttachToDocument(::GetUIDRef(doc));

} // end AutoAttach()

// -----------------------------------------------------------------------------

void MSOPanelTreeViewObserver::AutoDetach()
{
	CObserver::AutoDetach();

	InterfacePtr<ISubject> mySubject(this, UseDefaultIID());
	if (mySubject && mySubject->IsAttached(ISubject::kRegularAttachment, this, IID_ITREEVIEWCONTROLLER, IID_IOBSERVER))
		mySubject->DetachObserver(ISubject::kRegularAttachment, this, IID_ITREEVIEWCONTROLLER, IID_IOBSERVER);

	// Detach from whatever workspace we are observing

	IActiveContext *context = GetExecutionContextSession()->GetActiveContext();
	if (context)
	{
		InterfacePtr<ISubject> contextSubject(context, IID_ISUBJECT);
		if (contextSubject && contextSubject->IsAttached(ISubject::kRegularAttachment, this, IID_IACTIVECONTEXT, IID_IOBSERVER))
			contextSubject->DetachObserver(ISubject::kRegularAttachment, this, IID_IACTIVECONTEXT, IID_IOBSERVER);
	}

	DetachFromDocument();
} // end AutoDetach()

// -----------------------------------------------------------------------------

void MSOPanelTreeViewObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
#pragma unused(theChange)
	if (protocol == IID_ITREEVIEWCONTROLLER && theChange == kListSelectionChangedMessage)
	{
		// Change the active state
		InterfacePtr<ITreeViewController> tvController(this, UseDefaultIID());

		NodeIDList selNodes;
		tvController->GetSelectedItems(selNodes);
		if (selNodes.size() == 1)
		{

			TreeNodePtr<MSOStateNodeID> msoStateNode(selNodes[0]);
			InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
			if (iAppearanceSuite && 
				iAppearanceSuite->HasAppearance(msoStateNode->GetAppearance()) &&
				iAppearanceSuite->GetActiveState() != msoStateNode->GetAppearance())
			{
				MSOPanelUtils::AcceptMSONameIfNeeded(iAppearanceSuite);

				// Create a sequence otherwise the selection becomes out of sync when redo set active state.
				ICommandSequence* cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);

				iAppearanceSuite->SetActiveState(msoStateNode->GetAppearance());
				iAppearanceSuite->SelectActiveState();

				CmdUtils::EndCommandSequence(cmdSeq);
			}
		}
	}
	else if (protocol == IID_IACTIVECONTEXT)
	{
		InterfacePtr<IActiveContext> newContext(theSubject, UseDefaultIID());
		IDocument* newDoc = newContext->GetContextDocument();
		UIDRef newDocRef = ::GetUIDRef(newDoc);

		if (fCurrentDocRef != newDocRef)
		{
			// Detach the old document and attach to the new one.

			this->DetachFromDocument();
			
			if (newDoc)
			{
				this->AttachToDocument(newDocRef);
			}
		}
	}
} // end Update()


// -----------------------------------------------------------------------------

void MSOPanelTreeViewObserver::LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data)
{
	InterfacePtr<ITreeViewMgr>	treeViewMgr(this, UseDefaultIID());
	if (!treeViewMgr) return;

	InterfacePtr<ITreeViewHierarchyAdapter> treeViewAdapter(treeViewMgr, UseDefaultIID());
	if (!treeViewAdapter) return;

	// If the tree is empty presumably because there is nothing or a non-MSO selected then
	// we don't do anything since selection will need to be restored before we can process
	// the items added, deleted, or changed. For example, this can happen when change a MSO's
	// name from Layers panel.
	//
	// Also, during undo of "Release State to Objects" the selection update happens after the
	// lazy update so the panel is not yet populated with the MSO, see bug 2376331.
	InterfacePtr<IPanelControlData> panelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kMSOPanelWidgetID));
	InterfacePtr<IBoolData> msoSelectedData(panelData, UseDefaultIID());
	if (!msoSelectedData || !msoSelectedData->Get())
		return;

	if (protocol == IID_IAPPEARANCELIST)
	{
		const ListLazyNotificationData<int32> *listData = static_cast<const ListLazyNotificationData<int32> *>(data);
		if (listData)
		{
			//Bug Fix : #2944193
			/*
				MSO Panel is based only on selection. It queries from selection only what to show on UI. It lazily listens to all
				the commands which modifies states of an MSO. However, it interprets everything in current selection context.
				So, if i have added a state to an MSO which is not selected (How? not via UI but via scripting or some cmd), then 
				it things that a new state is added to an currently selected MSO and hence it cries :(

				Also, there is no way to know that from which MSO notification has come as it just sends out stateID's (merely int32)
				and tree also just stores ID's, though we can figure out from selection that which MSO it is showing. 
				So, we cannot even perform comparision at MSO Level.

				Hence, we are now just rebuilding the tree for any change. Too Bad : no other way 
			*/
			treeViewMgr->ChangeRoot();

			// Update the items in the tree.
			/*K2Vector<int32> addedItems, deletedItems, changedItems;
			listData->BreakoutChanges(&addedItems, &deletedItems, &changedItems);
			
			K2Vector<NodeID> nodes;
			nodes.clear();
			for (int32 i = 0; i < addedItems.size(); i++)
			{
				if (addedItems[i] > Form::kStateLast)
					nodes.push_back(MSOStateNodeID::Create((Form::AppearanceState)addedItems[i]));
			}
			if (nodes.size() > 0)
			{
				// Add the new nodes, select the node for the active appearance, and enter inline editing mode.
				treeViewMgr->NodesAdded(nodes);
			}

			nodes.clear();
			for (int32 i = 0; i < deletedItems.size(); i++)
			{
				if (deletedItems[i] > Form::kStateLast)
					nodes.push_back(MSOStateNodeID::Create((Form::AppearanceState)deletedItems[i]));
			}
			if (nodes.size() > 0)
			{
				// Delete the nodes and make sure the active node is selected (i.e. for undo).
				treeViewMgr->BeforeNodesDeleted(nodes);
			}

			for (int32 i = 0; i < changedItems.size(); i++)
			{
				if (changedItems[i] > Form::kStateLast)
				{
					// Delete/add instead of NodeChanged() so that a move will reorder the list.
					NodeID msoStateNode = MSOStateNodeID::Create((Form::AppearanceState)changedItems[i]);
					InterfacePtr<ITreeViewController> tvController(this, UseDefaultIID());
					bool16 reselect = tvController->IsSelected(msoStateNode) ? kTrue : kFalse;

					treeViewMgr->BeforeNodeDeleted(msoStateNode);
					treeViewMgr->NodeAdded(msoStateNode);

					if (reselect)
						tvController->Select(msoStateNode, kFalse, kTrue);
				}
			}*/
		}
	}
	else if (protocol == IID_IPAGEITEMNAME)
	{
		const ListLazyNotificationData<UID> *listData = static_cast<const ListLazyNotificationData<UID> *>(data);
		if (listData)
		{
			K2Vector<UID> changedItems;
			listData->BreakoutChanges(nil, nil, &changedItems);
			for (int32 i = 0; i < changedItems.size(); i++)
			{
				if (!fCurrentDocRef.GetDataBase()->IsValidUID(changedItems[i])) continue;

				InterfacePtr<IPMUnknown> changedItem(fCurrentDocRef.GetDataBase(), changedItems[i], IID_IUNKNOWN);
				if (changedItem != nil)
				{
					UIDRef parent;
					Form::AppearanceState activeState;
					Form::AppearanceState state = Utils<IFormFieldUtils>()->GetChildAppearanceState(changedItem, &parent, &activeState);
					if (state > Form::kStateLast)
					{
						NodeID msoStateNode = MSOStateNodeID::Create((Form::AppearanceState)state);

						if (treeViewAdapter->GetChildIndex(treeViewAdapter->GetRootNode(), msoStateNode) >= 0)
							treeViewMgr->NodeChanged(msoStateNode);
					}
				}
			}
		}
	}
} // end LazyUpdate()

// -----------------------------------------------------------------------------

void MSOPanelTreeViewObserver::AttachToDocument(UIDRef docRef)
{
	InterfacePtr<ISubject> docSubject(docRef, IID_ISUBJECT);
	if (docSubject)
	{
		if (!docSubject->IsAttached(ISubject::kLazyAttachment, this, IID_IAPPEARANCELIST, IID_IOBSERVER))
			docSubject->AttachObserver(ISubject::kLazyAttachment, this, IID_IAPPEARANCELIST, IID_IOBSERVER);

		if (!docSubject->IsAttached(ISubject::kLazyAttachment, this, IID_IPAGEITEMNAME, IID_IOBSERVER)) 
			docSubject->AttachObserver(ISubject::kLazyAttachment, this, IID_IPAGEITEMNAME, IID_IOBSERVER); 

		fCurrentDocRef = docRef;
	}	
} // end AttachToDocument()

// -----------------------------------------------------------------------------

void MSOPanelTreeViewObserver::DetachFromDocument()
{
	InterfacePtr<ISubject> docSubject(fCurrentDocRef, IID_ISUBJECT);
	if (docSubject)
	{
		if (docSubject->IsAttached(ISubject::kLazyAttachment, this, IID_IAPPEARANCELIST, IID_IOBSERVER))
			docSubject->DetachObserver(ISubject::kLazyAttachment, this, IID_IAPPEARANCELIST, IID_IOBSERVER);

		if (docSubject->IsAttached(ISubject::kLazyAttachment, this, IID_IPAGEITEMNAME, IID_IOBSERVER))
			docSubject->DetachObserver(ISubject::kLazyAttachment, this, IID_IPAGEITEMNAME, IID_IOBSERVER);
	}

	if (fCurrentDocRef != UIDRef(nil,kInvalidUID))
		fCurrentDocRef = UIDRef(nil,kInvalidUID);
} // end DetachFromDocument()

