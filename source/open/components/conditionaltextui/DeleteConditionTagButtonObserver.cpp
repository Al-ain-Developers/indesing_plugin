//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/DeleteConditionTagButtonObserver.cpp $
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
#include "IDocument.h"
#include "IPanelControlData.h"
#include "ISubject.h"
#include "ITreeViewHierarchyAdapter.h"
#include "ITreeViewController.h"
#include "ITriStateControlData.h"
#include "IUIDData.h"
#include "IWorkspace.h"

// ----- Includes -----

#include "CAlert.h"
#include "K2Vector.tpp"
#include "CObserver.h"
#include "UIDNodeID.h"

// ----- Utility files -----

#include "IConditionalTextUIFacade.h"
#include "IInCopySharedUtils.h"
#include "IPalettePanelUtils.h"
#include "IWidgetUtils.h"

// ----- ID.h files -----

#include "ConditionalTextUIID.h"
#include "InCopyCoreID.h"
#include "LayoutUIID.h"


class DeleteConditionTagButtonObserver : public CObserver
{
public:
	DeleteConditionTagButtonObserver(IPMUnknown* boss);
	virtual ~DeleteConditionTagButtonObserver();

	virtual void AutoAttach();
	virtual void AutoDetach();
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy) ; 

private:
	void EnableButton(IActiveContext* activeContext);
};

// =============================================================================
// *** DeleteConditionTagButtonObserver impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(DeleteConditionTagButtonObserver, kDeleteConditionTagButtonObserverImpl)

DeleteConditionTagButtonObserver::DeleteConditionTagButtonObserver(IPMUnknown* boss): CObserver(boss) 
{
} // end constructor

DeleteConditionTagButtonObserver::~DeleteConditionTagButtonObserver()
{
} // end destructor

// -----------------------------------------------------------------------------

void DeleteConditionTagButtonObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy) 
{
	InterfacePtr<IPanelControlData> panelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kConditionalTextUIPanelWidgetID));
	ASSERT_MSG(panelData != nil, "DeleteConditionTagButtonObserver - Can't find IPanelControlData in Conditional Text panel.");

	InterfacePtr<ITreeViewController> tvController(panelData ? panelData->FindWidget(kConditionTagListTreeViewWidgetID) : nil, UseDefaultIID());
	ASSERT_MSG(tvController != nil, "DeleteConditionTagButtonObserver - Can't find ITreeViewController in Conditional Text panel.");
			
	IActiveContext* activeContext = GetExecutionContextSession()->GetActiveContext();

	if (theChange == kTrueStateMessage)
	{
		NodeIDList selNodes;
		tvController->GetSelectedItems(selNodes);
		if (selNodes.size() <= 0)
			return;

		K2Vector<UID> tagUIDsToDelete;
		for (int32 i = 0; i < selNodes.size(); i++)
		{
			TreeNodePtr<UIDNodeID> uidNodeID(selNodes[i]);
			tagUIDsToDelete.push_back(uidNodeID->GetUID());
		}

		IWorkspace* ws = GetExecutionContextSession()->GetActiveContext()->GetContextWorkspace();
		Utils<Facade::IConditionalTextUIFacade>()->DeleteConditions(ws, tagUIDsToDelete, kFalse);

		this->EnableButton(activeContext);
	}
	else if (theChange == kListSelectionChangedMessage)
	{
		this->EnableButton(activeContext);
	}
 	else if (protocol == IID_IACTIVECONTEXT)  //this protocol sends IID instead of cmdID
 	{
 		const PMIID& what = *((const PMIID*)changedBy);
 		if (what == IID_IDOCUMENT || what == IID_ILAYOUTCONTROLDATA)
 		{
			this->EnableButton(activeContext);
 		}
 	}
 	else if (protocol == IID_IDOCUMENT)
 	{
 		// check the SaveAs
 		if (theChange == kSetStandAloneCmdBoss)
 		{		
			this->EnableButton(activeContext);
		}
 	}
} // end Update()

// -----------------------------------------------------------------------------

void DeleteConditionTagButtonObserver::AutoAttach()
{
	InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	if (subject)
	{
		subject->AttachObserver(this, IID_ITRISTATECONTROLDATA);

		InterfacePtr<ISubject> treeSubject((ISubject*)Utils<IWidgetUtils>()->QueryRelatedWidget(this, kConditionTagListTreeViewWidgetID, IID_ISUBJECT));
		if (treeSubject && !treeSubject->IsAttached(this, IID_ITREEVIEWCONTROLLER))
			treeSubject->AttachObserver(this, IID_ITREEVIEWCONTROLLER);
	}

	// active context
 	IActiveContext* activeContext = GetExecutionContextSession()->GetActiveContext();
 	InterfacePtr<ISubject> acSubject(activeContext, IID_ISUBJECT);

 	if (acSubject && !acSubject->IsAttached(ISubject::kRegularAttachment, this, IID_IACTIVECONTEXT, IID_IOBSERVER))
 	{
 		acSubject->AttachObserver(ISubject::kRegularAttachment, this, IID_IACTIVECONTEXT, IID_IOBSERVER);
		this->EnableButton(activeContext);
 	}

 	if (acSubject && !acSubject->IsAttached(this, IID_IDOCUMENT))
 		acSubject->AttachObserver(this, IID_IDOCUMENT);
} // end AutoAttach()

// -----------------------------------------------------------------------------

void DeleteConditionTagButtonObserver::AutoDetach() 
{
	InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
	if (subject)
	{
		subject->DetachObserver(this, IID_ITRISTATECONTROLDATA);

		InterfacePtr<ISubject> treeSubject((ISubject*)Utils<IWidgetUtils>()->QueryRelatedWidget(this, kConditionTagListTreeViewWidgetID, IID_ISUBJECT));
		if (treeSubject && treeSubject->IsAttached(this, IID_ITREEVIEWCONTROLLER))
			treeSubject->DetachObserver(this, IID_ITREEVIEWCONTROLLER);
	}

	// active context
 	IActiveContext* activeContext = GetExecutionContextSession()->GetActiveContext();
 	InterfacePtr<ISubject> acSubject(activeContext, IID_ISUBJECT);

 	if (acSubject && acSubject->IsAttached(ISubject::kRegularAttachment, this, IID_IACTIVECONTEXT, IID_IOBSERVER))
 		acSubject->DetachObserver(ISubject::kRegularAttachment, this, IID_IACTIVECONTEXT, IID_IOBSERVER);

	if (acSubject && acSubject->IsAttached(this, IID_IDOCUMENT))
 		acSubject->DetachObserver(this, IID_IDOCUMENT);
} // end AutoDetach()

// -----------------------------------------------------------------------------

void DeleteConditionTagButtonObserver::EnableButton(IActiveContext* activeContext) 
{
	if (activeContext == nil)
	{
		ASSERT_FAIL("NewConditionTagButtonObserver::EnableButton - active context nil?");
		return;
	}

	InterfacePtr<IPanelControlData> panelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kConditionalTextUIPanelWidgetID));
	InterfacePtr<ITreeViewController> tvController(panelData ? panelData->FindWidget(kConditionTagListTreeViewWidgetID) : nil, UseDefaultIID());

	InterfacePtr<ITreeViewHierarchyAdapter> tvAdapter(tvController, UseDefaultIID());
	InterfacePtr<IControlView> view(this, UseDefaultIID());
	InterfacePtr<IUIDData> dbData(tvAdapter, UseDefaultIID());
	if (dbData && Utils<IInCopySharedUtils>()->StylesEditable(dbData->GetItemDataBase()))
	{
		NodeIDList selNodes;
		tvController->GetSelectedItems(selNodes);
		bool16 bEnable(selNodes.size() > 0);
		for (int32 i = 0; i < selNodes.size(); i++)
		{
			TreeNodePtr<UIDNodeID> uidNodeID(selNodes[i]);
			if (selNodes[i] == tvAdapter->GetRootNode())
			{
				bEnable = kFalse;	// can't delete [Unconditional]
				break;
			}
		}
		view->Enable(bEnable);
	}
	else
		view->Enable(kFalse);
} // end EnableButton()
