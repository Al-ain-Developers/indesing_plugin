//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/ConditionTagListTreeSelectionObserver.cpp $
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

#include "IConditionTagList.h"
#include "IConditionTagSuite.h"
#include "IPanelControlData.h"
#include "ISelectionManager.h"
#include "ITreeViewHierarchyAdapter.h"
#include "ITreeViewController.h"
#include "IWorkspace.h"

// ----- Includes -----

#include "SelectionObserver.h"
#include "UIDList.h"
#include "UIDNodeID.h"

// ----- Utility files -----

#include "IConditionalTextFacade.h"
#include "IConditionalTextUIFacade.h"
#include "IObjectStylesUtils.h"

// ----- ID.h files -----

#include "ConditionalTextUIID.h"

#include "TemplateDefs.h"

#include "K2Vector.tpp"
#include "NodeID.h"
template class K2Vector<NodeID>;

class ConditionTagListTreeSelectionObserver : public ActiveSelectionObserver
{
public:
	ConditionTagListTreeSelectionObserver(IPMUnknown *boss);

	virtual void HandleSelectionChanged( const ISelectionMessage* iSelectionMessage );
	virtual void HandleSelectionAttributeChanged( const ISelectionMessage* iSelectionMessage );

private:
	void UpdateSelectedNodes();

};

// =============================================================================
// *** ConditionTagListTreeSelectionObserver impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(ConditionTagListTreeSelectionObserver, kConditionTagListTreeSelectionObserverImpl)

ConditionTagListTreeSelectionObserver::ConditionTagListTreeSelectionObserver(IPMUnknown *boss) :
	ActiveSelectionObserver(boss, IID_ISELECTIONOBSERVER)
{
} // end constructor

// -----------------------------------------------------------------------------

void ConditionTagListTreeSelectionObserver::HandleSelectionChanged(const ISelectionMessage* iSelectionMessage)
{
#pragma unused(iSelectionMessage)
	InterfacePtr<IPanelControlData> myWidgets(this, UseDefaultIID());
	InterfacePtr<IWorkspace> workspace(Utils<IObjectStylesUtils>()->QueryWorkspaceFromDataBase(fCurrentSelection->GetDataBase()));
	Utils<Facade::IConditionalTextUIFacade>()->UpdateAppliedIcons(workspace, myWidgets);
	this->UpdateSelectedNodes();
} // end HandleSelectionChanged()

// -----------------------------------------------------------------------------

void ConditionTagListTreeSelectionObserver::HandleSelectionAttributeChanged(const ISelectionMessage* iSelectionMessage)
{
#pragma unused(iSelectionMessage)
	InterfacePtr<IPanelControlData> myWidgets(this, UseDefaultIID());
	InterfacePtr<IWorkspace> workspace(Utils<IObjectStylesUtils>()->QueryWorkspaceFromDataBase(fCurrentSelection->GetDataBase()));
	Utils<Facade::IConditionalTextUIFacade>()->UpdateAppliedIcons(workspace, myWidgets);
	this->UpdateSelectedNodes();
} // end HandleSelectionChanged()

// -----------------------------------------------------------------------------

void ConditionTagListTreeSelectionObserver::UpdateSelectedNodes()
{
	InterfacePtr<IConditionTagList> conditionTagList(Utils<Facade::IConditionalTextFacade>()->QueryConditionList(fCurrentSelection->GetDataBase()));
	if (conditionTagList)
	{
		InterfacePtr<ITreeViewController> tvController(this, UseDefaultIID());
		if (tvController)
		{
			NodeIDList currentSelection;
			tvController->GetSelectedItems(currentSelection);

			NodeIDList newSelection;

			UIDList appliedToAllChars;
			UIDList appliedToSomeChars;
			InterfacePtr<IConditionTagSuite> conditionsSuite(static_cast<IConditionTagSuite*>(fCurrentSelection->QueryIntegratorSuite(IID_ICONDITIONTAGSUITE, ISelectionManager::kEnabledInterface)));
			if (conditionsSuite && conditionsSuite->GetAppliedConditionTags(appliedToAllChars, appliedToSomeChars) == kSuccess)
			{
				// Select the condition node unless mixed state or multiple applied conditions.
				UIDList appliedList(appliedToAllChars);
				appliedList.Append(appliedToSomeChars);
				if (appliedList.size() > 0)
				{					
					if (appliedList.size() == 1 && appliedToSomeChars.size() == 0 /* not mixed */)
					{
						// Put applied condition in list to select.
						newSelection.push_back(UIDNodeID::Create(appliedList[0]));
					}
				}
				else
				{
					// Put unconditional row item in list to select.
					InterfacePtr<ITreeViewHierarchyAdapter> tvAdapter(tvController, UseDefaultIID());
					if (tvAdapter)
						newSelection.push_back(tvAdapter->GetRootNode());
				}
			}

			// Only change select if it has changed, reduces flash when typing
			if (newSelection != currentSelection)
			{
				tvController->DeselectAll(kTrue, kTrue);
				if (newSelection.size())
					tvController->Select(newSelection[0], kTrue /*so delete button will disable*/, kTrue);
			}
		}
	}
} // UpdateSelectedNodes()