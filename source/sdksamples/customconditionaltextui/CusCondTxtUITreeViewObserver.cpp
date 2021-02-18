//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customconditionaltextui/CusCondTxtUITreeViewObserver.cpp $
//  
//  Owner: Adobe Developer Technologies
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

// Interface includes:
#include "IActiveContext.h"
#include "IPanelControlData.h"
#include "ISubject.h"
#include "ITreeViewMgr.h"
#include "IUIDData.h"
#include "IWorkspace.h"

// General includes:
#include "CObserver.h"
#include "ListLazyNotificationData.h"
#include "UIDNodeID.h"
#include "ConditionalTextID.h"
#include "ConditionalTextUIID.h"
#include "K2Vector.h"
#include "K2Vector.tpp"

// Project includes:
#include "CusCondTxtUIID.h"
#include "ICustomConditionTag.h"

class CusCondTxtTreeViewObserver : public CObserver
{
public:
	CusCondTxtTreeViewObserver(IPMUnknown *boss);
	virtual ~CusCondTxtTreeViewObserver();

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


CREATE_PMINTERFACE(CusCondTxtTreeViewObserver, kCusCondTxtUITreeViewObserverImpl)

/* CusCondTxtTreeViewObserver Constructor
*/
CusCondTxtTreeViewObserver::CusCondTxtTreeViewObserver(IPMUnknown *boss) :
	CObserver(boss),
	fCurrentWorkspaceRef(nil,kInvalidUID)
{
}

/* CusCondTxtTreeViewObserver Destructor
*/
CusCondTxtTreeViewObserver::~CusCondTxtTreeViewObserver()
{
}

/* AutoAttach
*/
void CusCondTxtTreeViewObserver::AutoAttach()
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
	{
		this->AttachTo(::GetUIDRef(ws));
	}
} 

/* AutoDetach
*/
void CusCondTxtTreeViewObserver::AutoDetach()
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
	
}

/* Update
*/
void CusCondTxtTreeViewObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
#pragma unused(theChange)

	do
	{
		IActiveContext *context = GetExecutionContextSession()->GetActiveContext();
		if (context == nil)
		{
			ASSERT_FAIL("IActiveContext is invalid");
			break ;
		}
		
		if (protocol == IID_IACTIVECONTEXT)
		{
			InterfacePtr<IActiveContext> newContext(theSubject, UseDefaultIID());
					if (newContext == nil)
			{
				ASSERT_FAIL("IActiveContext is invalid");
				break ;
			}
			
			IWorkspace* newWS = newContext->GetContextWorkspace();
			if (newWS == nil)
			{
				ASSERT_FAIL("IWorkspace is invalid");
				break ;
			}	

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
	} while (false);
} 

/* LazyUpdate
*/
void CusCondTxtTreeViewObserver::LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* data)
{
	do
	{
		InterfacePtr<ITreeViewMgr> treeViewMgr(this, UseDefaultIID());
		if (treeViewMgr == nil)
		{
			ASSERT_FAIL("ITreeViewMgr is invalid");
			break ;
		}

		if (protocol == IID_ICONDITIONTAGLIST || protocol == IID_ICUSTOMCONDITIONTAG)
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
	} while (false);
}

/* AttachTo
*/
void CusCondTxtTreeViewObserver::AttachTo(UIDRef workspaceRef)
{
	do
	{
		InterfacePtr<ISubject> wsSubject(workspaceRef, IID_ISUBJECT);

		if (wsSubject == nil)
		{
			break;
		}
		
		if (!wsSubject->IsAttached(ISubject::kLazyAttachment, this, IID_ICONDITIONTAGLIST, IID_IOBSERVER))
			wsSubject->AttachObserver(ISubject::kLazyAttachment, this, IID_ICONDITIONTAGLIST, IID_IOBSERVER);
			
		if (!wsSubject->IsAttached(ISubject::kLazyAttachment, this, IID_ICONDITIONTAGSET, IID_IOBSERVER))
			wsSubject->AttachObserver(ISubject::kLazyAttachment, this, IID_ICONDITIONTAGSET, IID_IOBSERVER);

		if (!wsSubject->IsAttached(ISubject::kLazyAttachment, this, IID_ICUSTOMCONDITIONTAG, IID_IOBSERVER))
			wsSubject->AttachObserver(ISubject::kLazyAttachment, this, IID_ICUSTOMCONDITIONTAG, IID_IOBSERVER);
			
		InterfacePtr<IPanelControlData> myWidgets(this, UseDefaultIID());
		InterfacePtr<ITreeViewMgr> treeViewMgr(myWidgets->FindWidget(kConditionTagListTreeViewWidgetID), UseDefaultIID());
		if (treeViewMgr)
		{
			
			InterfacePtr<IUIDData>	forActiveDB(treeViewMgr, UseDefaultIID());				
			if (forActiveDB == nil)
			{
				ASSERT_FAIL("IUIDData is invalid");
				break ;
			}
			forActiveDB->Set(workspaceRef);

			treeViewMgr->ChangeRoot(kTrue);
		}

		fCurrentWorkspaceRef = workspaceRef;

	} while (false);
}

/* DetachFromWorkspace
*/
void CusCondTxtTreeViewObserver::DetachFromWorkspace()
{
	do
	{
		InterfacePtr<ISubject> wsSubject(fCurrentWorkspaceRef, IID_ISUBJECT);
		if(wsSubject)
		{
			if (wsSubject->IsAttached(ISubject::kLazyAttachment, this, IID_ICONDITIONTAGLIST, IID_IOBSERVER))
				wsSubject->DetachObserver(ISubject::kLazyAttachment, this, IID_ICONDITIONTAGLIST, IID_IOBSERVER);
				
			if (wsSubject->IsAttached(ISubject::kLazyAttachment, this, IID_ICONDITIONTAGSET, IID_IOBSERVER))
				wsSubject->DetachObserver(ISubject::kLazyAttachment, this, IID_ICONDITIONTAGSET, IID_IOBSERVER);
				
			if (wsSubject->IsAttached(ISubject::kLazyAttachment, this, IID_ICUSTOMCONDITIONTAG, IID_IOBSERVER))
				wsSubject->DetachObserver(ISubject::kLazyAttachment, this, IID_ICUSTOMCONDITIONTAG, IID_IOBSERVER);
		}
		
		if (fCurrentWorkspaceRef != UIDRef(nil,kInvalidUID))
			fCurrentWorkspaceRef = UIDRef(nil,kInvalidUID);

		// Clear the uid data
		InterfacePtr<IPanelControlData> myWidgets(this, UseDefaultIID());
		if (myWidgets == nil)
		{
			ASSERT_FAIL("IPanelControlData is invalid");
			break ;
		}
		
		InterfacePtr<ITreeViewMgr> treeViewMgr(myWidgets->FindWidget(kConditionTagListTreeViewWidgetID), UseDefaultIID());
		if (treeViewMgr)
		{
			InterfacePtr<IUIDData>	forActiveDB(treeViewMgr, UseDefaultIID());
			if (forActiveDB == nil)
			{
				ASSERT_FAIL("IUIDData is invalid");
				break ;
			}
			forActiveDB->Set(UIDRef::gNull);		
		}
	} while (false);
}

/* UpdateTreeViewList
*/
void CusCondTxtTreeViewObserver::UpdateTreeViewList()
{
	InterfacePtr<ITreeViewMgr>	treeMgr(this, UseDefaultIID());
	if (treeMgr)
	{
		treeMgr->ChangeRoot();	
	}
} 
