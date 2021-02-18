//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/appearancepanel/ListItemsNodeEventHandler.cpp $
//  
//  Owner: Reena Agrawal
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

#include "IDragDropController.h"
#include "IDragDropSource.h"
#include "IFormFieldSuite.h"
#include "ITreeAttributes.h"
#include "ITreeNodeIDData.h"
#include "ITreeViewController.h"
#include "IWidgetParent.h"

// ----- Implementation Includes -----

#include "IntNodeID.h"
#include "TreeNodeEventHandler.h"

// ----- ID.h files -----

#include "FormFieldUIID.h"

// ----- Utility files -----

#include "EventUtilities.h" 
#include "FormFieldUIUtils.h"

//========================================================================================
// CLASS ListItemsNodeEventHandler
//========================================================================================

class ListItemsNodeEventHandler : public TreeNodeEventHandler
{
public:
	ListItemsNodeEventHandler(IPMUnknown *boss);
	virtual ~ListItemsNodeEventHandler();

	virtual bool16 LButtonDn(IEvent* e);
};

//========================================================================================
// CLASS ListItemsNodeEventHandler
//========================================================================================

CREATE_PMINTERFACE(ListItemsNodeEventHandler, kListItemsNodeEventHandlerImpl)

//----------------------------------------------------------------------------------------
// ListItemsNodeEventHandler::ListItemsNodeEventHandler
//----------------------------------------------------------------------------------------

ListItemsNodeEventHandler::ListItemsNodeEventHandler(IPMUnknown *boss) :
	TreeNodeEventHandler(boss)
{
}

//----------------------------------------------------------------------------------------
// ListItemsNodeEventHandler::~ListItemsNodeEventHandler
//----------------------------------------------------------------------------------------

ListItemsNodeEventHandler::~ListItemsNodeEventHandler()
{
}

//----------------------------------------------------------------------------------------
// ListItemsNodeEventHandler::LButtonDn
//----------------------------------------------------------------------------------------
bool16 ListItemsNodeEventHandler::LButtonDn(IEvent* e)
{
	// The following code is taken from TreeNodeEventHandler::LButtonDn.
	// We do this ourselves, since,
	// 1. If SortItems is enabled, we do not want drag and drop.
	// 2. In the case of drag and drop, we do not want to change the default choice.
	InterfacePtr<IWidgetParent>	wp(this, UseDefaultIID());
	InterfacePtr<ITreeAttributes> attribs((ITreeAttributes*) wp->QueryParentFor(IID_ITREEATTRIBUTES));
	InterfacePtr<ITreeViewController> treeController(attribs, UseDefaultIID());
	treeController->ProcessSelectionRules(e, ::GetUID(this));

	// Check for drag-n-drop
	InterfacePtr<IDragDropSource> dragSource(this, UseDefaultIID());
	if (dragSource && dragSource->WillDrag(e))
	{
		// Check to see if user is trying to start a drag
		bool16 isPatientUser;
		if (::IsUserStartingDrag(e, isPatientUser))
		{
			InterfacePtr<IDragDropController> ddController(GetExecutionContextSession(), UseDefaultIID());
			if (ddController)
			{
				bool16 dragSucceeded = ddController->StartDrag(dragSource, e);
				e->SetSystemHandledState(IEvent::kDontCall);
				if (dragSucceeded)
					return kTrue; // Make up for the fact that StartDrag will swallow the mouse up
			}
		}
	}

	// Set this node to be the default choice
	InterfacePtr<IFormFieldSuite> iFormFieldSuite(FormFieldUIUtils::QueryFormSuite());
	if (iFormFieldSuite && (iFormFieldSuite->IsFieldSelectionOfType(kComboBoxItemBoss) || iFormFieldSuite->IsFieldSelectionOfType(kListBoxFieldItemBoss) ))
	{
		PMString defaultChoice;
		int32 defaultChoiceIndex;
		iFormFieldSuite->GetDefaultChoice(defaultChoice, defaultChoiceIndex);

		InterfacePtr<const ITreeNodeIDData> nodeData(this, UseDefaultIID());
		TreeNodePtr<const IntNodeID> treeNode(nodeData->Get());

		if (treeNode->Get() != defaultChoiceIndex)
		{
			Form::ChoiceList choiceList;
			iFormFieldSuite->GetChoiceList(choiceList);
			iFormFieldSuite->SetDefaultChoice(choiceList[treeNode->Get()]);
		}
		else
		{
			// If this was already the default choice, set the default choice to be empty. This is because
			// there is no other switch/button to set the default choice to be empty, after a choice has been
			// set as default. So, if the default choice is clicked again, set the default choice as empty.
			iFormFieldSuite->SetDefaultChoice(PMString());
		}
	}

	return kTrue;
}
