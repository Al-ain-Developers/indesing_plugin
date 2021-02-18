//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/ConditionTagListTreeObserver.cpp $
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
//#include "boost/bind.hpp"

// ----- Interfaces -----

#include "IActiveContext.h"
#include "IPanelControlData.h"
#include "ISubject.h"
#include "ITreeViewMgr.h"
#include "IUIDData.h"
#include "IWorkspace.h"

// ----- Includes -----

#include "ListLazyNotificationData.h"
#include "UIDNodeID.h"

// ----- Utility files -----


// ----- ID.h files -----

#include "ConditionalTextID.h"
#include "ConditionalTextUIID.h"
#include "DocumentID.h"


class ConditionTagListTreeObserver : public CObserver
{
public:
	ConditionTagListTreeObserver(IPMUnknown *boss);
	virtual ~ConditionTagListTreeObserver();

	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
	virtual void LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data);

	virtual void AutoAttach();			
	virtual void AutoDetach();

private:
	void	AttachTo(UIDRef workspaceRef);
	void	DetachFromWorkspace();
	void	UpdateTreeViewList();

	UIDRef	fCurrentWorkspaceRef;
};

// =============================================================================
// *** ConditionTagListTreeObserver impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(ConditionTagListTreeObserver, kConditionTagListTreeObserverImpl)

ConditionTagListTreeObserver::ConditionTagListTreeObserver(IPMUnknown *boss) :
	CObserver(boss),
	fCurrentWorkspaceRef(nil,kInvalidUID)
{
} // end constructor

ConditionTagListTreeObserver::~ConditionTagListTreeObserver()
{
} // end destructor

// -----------------------------------------------------------------------------

void ConditionTagListTreeObserver::AutoAttach()
{
	// Attach to the active context
	IActiveContext *context = GetExecutionContextSession()->GetActiveContext();
	if (context)
	{
		InterfacePtr<ISubject> contextSubject(context, IID_ISUBJECT);
		if (contextSubject && !contextSubject->IsAttached(ISubject::kRegularAttachment, this, IID_IACTIVECONTEXT, IID_IOBSERVER))
			contextSubject->AttachObserver(ISubject::kRegularAttachment, this, IID_IACTIVECONTEXT, IID_IOBSERVER);
	}

	InterfacePtr<ISubject> mySubject(this, UseDefaultIID());
	if (mySubject && !mySubject->IsAttached(ISubject::kRegularAttachment, this, IID_ITREEVIEWCONTROLLER, IID_IOBSERVER))
		mySubject->AttachObserver(ISubject::kRegularAttachment, this, IID_ITREEVIEWCONTROLLER, IID_IOBSERVER);

	IWorkspace* ws = context->GetContextWorkspace();
	if (ws)
		this->AttachTo(::GetUIDRef(ws));
} // end AutoAttach()

// -----------------------------------------------------------------------------

void ConditionTagListTreeObserver::AutoDetach()
{
	CObserver::AutoDetach();

	// Detach from whatever workspace we are observing

	IActiveContext *context = GetExecutionContextSession()->GetActiveContext();
	if (context)
	{
		InterfacePtr<ISubject> contextSubject(context, IID_ISUBJECT);
		if (contextSubject && contextSubject->IsAttached(ISubject::kRegularAttachment, this, IID_IACTIVECONTEXT, IID_IOBSERVER))
			contextSubject->DetachObserver(ISubject::kRegularAttachment, this, IID_IACTIVECONTEXT, IID_IOBSERVER);
	}

	InterfacePtr<ISubject> mySubject(this, UseDefaultIID());
	if (mySubject && mySubject->IsAttached(ISubject::kRegularAttachment, this, IID_ITREEVIEWCONTROLLER, IID_IOBSERVER))
		mySubject->DetachObserver(ISubject::kRegularAttachment, this, IID_ITREEVIEWCONTROLLER, IID_IOBSERVER);

	DetachFromWorkspace();
} // end AutoDetach()

// -----------------------------------------------------------------------------

void ConditionTagListTreeObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
#pragma unused(theChange)
	IActiveContext *context = GetExecutionContextSession()->GetActiveContext();
	if (protocol == IID_IACTIVECONTEXT)
	{
		InterfacePtr<IActiveContext> newContext(theSubject, UseDefaultIID());
		IWorkspace* newWS = newContext->GetContextWorkspace();
		UIDRef newWorkspaceRef = ::GetUIDRef(newWS);

		if (fCurrentWorkspaceRef != newWorkspaceRef)
		{
			// Detach the old workspace and attach to the new one for style table changes.

			this->DetachFromWorkspace();
			
			if (newWS)
			{
				this->AttachTo(newWorkspaceRef);
			}

			this->UpdateTreeViewList();
		}
	}
} // end Update()

// -----------------------------------------------------------------------------

void ConditionTagListTreeObserver::LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data)
{
	InterfacePtr<ITreeViewMgr> treeViewMgr(this, UseDefaultIID());

	if (protocol == IID_ICONDITIONTAGLIST)
	{
		const ListLazyNotificationData<UID> *listData = static_cast<const ListLazyNotificationData<UID> *>(data);
		if (listData)
		{
			// Update the items in the tree.
			K2Vector<UID> addedItems, deletedItems, changedItems;
			listData->BreakoutChanges(&addedItems, &deletedItems, &changedItems);

			K2Vector<NodeID> nodes;
			nodes.clear();
			for (int32 i = 0; i < addedItems.size(); i++)
			{
				nodes.push_back(UIDNodeID::Create(addedItems[i]));
			}
			if (nodes.size() > 0)
				treeViewMgr->NodesAdded(nodes);

			nodes.clear();
			for (int32 i = 0; i < deletedItems.size(); i++)
			{
				nodes.push_back(UIDNodeID::Create(deletedItems[i]));
			}
			if (nodes.size() > 0)
				treeViewMgr->BeforeNodesDeleted(nodes);

			for (int32 i = 0; i < changedItems.size(); i++)
			{
				// Delete/add instead of NodeChanged() so that a name change will reorder the list.
				treeViewMgr->BeforeNodeDeleted(UIDNodeID::Create(changedItems[i]));
				treeViewMgr->NodeAdded(UIDNodeID::Create(changedItems[i]));
			}
		}
		else
		{
			// Force rebuild the entire tree. 
			treeViewMgr->ChangeRoot();
		}
	}
	else if (protocol == IID_ICONDITIONTAGSET)
	{
		treeViewMgr->ChangeRoot();
	}
} // end LazyUpdate()

// -----------------------------------------------------------------------------

void ConditionTagListTreeObserver::AttachTo(UIDRef workspaceRef)
{
	InterfacePtr<ISubject> wsSubject(workspaceRef, IID_ISUBJECT);
	if (wsSubject)
	{
		if (!wsSubject->IsAttached(ISubject::kLazyAttachment, this, IID_ICONDITIONTAGLIST, IID_IOBSERVER))
			wsSubject->AttachObserver(ISubject::kLazyAttachment, this, IID_ICONDITIONTAGLIST, IID_IOBSERVER);
			
		if (!wsSubject->IsAttached(ISubject::kLazyAttachment, this, IID_ICONDITIONTAGSET, IID_IOBSERVER))
			wsSubject->AttachObserver(ISubject::kLazyAttachment, this, IID_ICONDITIONTAGSET, IID_IOBSERVER);


		// Set up the tree stuff

		InterfacePtr<IPanelControlData> myWidgets(this, UseDefaultIID());
		InterfacePtr<ITreeViewMgr> treeViewMgr(myWidgets->FindWidget(kConditionTagListTreeViewWidgetID), UseDefaultIID());
		if (treeViewMgr)
		{
			InterfacePtr<IUIDData>	forActiveDB(treeViewMgr, UseDefaultIID());
			forActiveDB->Set(workspaceRef);

			treeViewMgr->ChangeRoot(kTrue);
		}

		fCurrentWorkspaceRef = workspaceRef;
	}	
} // end AttachTo()

// -----------------------------------------------------------------------------

void ConditionTagListTreeObserver::DetachFromWorkspace()
{
	InterfacePtr<ISubject> wsSubject(fCurrentWorkspaceRef, IID_ISUBJECT);
	if (wsSubject && wsSubject->IsAttached(ISubject::kLazyAttachment, this, IID_ICONDITIONTAGLIST, IID_IOBSERVER))
		wsSubject->DetachObserver(ISubject::kLazyAttachment, this, IID_ICONDITIONTAGLIST, IID_IOBSERVER);
		
	if (wsSubject && wsSubject->IsAttached(ISubject::kLazyAttachment, this, IID_ICONDITIONTAGSET, IID_IOBSERVER))
		wsSubject->DetachObserver(ISubject::kLazyAttachment, this, IID_ICONDITIONTAGSET, IID_IOBSERVER);

	if (fCurrentWorkspaceRef != UIDRef(nil,kInvalidUID))
		fCurrentWorkspaceRef = UIDRef(nil,kInvalidUID);

	// Clear the uid data
	InterfacePtr<IPanelControlData> myWidgets(this, UseDefaultIID());
	InterfacePtr<ITreeViewMgr> treeViewMgr(myWidgets->FindWidget(kConditionTagListTreeViewWidgetID), UseDefaultIID());
	if (treeViewMgr)
	{
		InterfacePtr<IUIDData>	forActiveDB(treeViewMgr, UseDefaultIID());
		forActiveDB->Set(UIDRef::gNull);
	}
} // end DetachFromWorkspace()

// -----------------------------------------------------------------------------

void ConditionTagListTreeObserver::UpdateTreeViewList()
{
	InterfacePtr<IPanelControlData> myWidgets(this, UseDefaultIID());
	IControlView* treeView = myWidgets->FindWidget(kConditionTagListTreeViewWidgetID);
	InterfacePtr<ITreeViewMgr>	treeMgr(treeView, UseDefaultIID());
	treeMgr->ChangeRoot();
} // end UpdateTreeViewList()
