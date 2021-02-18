//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/appearancepanel/RemoveListOptionButtonObserver.cpp $
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

#include "IControlView.h"
#include "IFormFieldSuite.h"
#include "ISelectionDataSuite.h"
#include "ISubject.h"
#include "ITreeViewController.h"
#include "ITreeViewMgr.h"
#include "IWidgetUtils.h"

// ----- Implementation Includes -----

#include "CWidgetObserver.h"
#include "IntNodeID.h"

// ----- Utility files -----

#include "FormFieldUIUtils.h"
#include "SelectionUtils.h"

// ----- ID.h files -----

#include "FormFieldUIID.h"

//========================================================================================
// CLASS RemoveListOptionButtonObserver
//========================================================================================

class RemoveListOptionButtonObserver : public CWidgetObserver
{
public:
	typedef CWidgetObserver	Inherited;

	RemoveListOptionButtonObserver(IPMUnknown *boss);
	virtual ~RemoveListOptionButtonObserver();
	
	virtual void 	AutoAttach();
	virtual void 	AutoDetach();
	virtual void 	Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
};

//========================================================================================
// METHODS RemoveListOptionButtonObserver
//========================================================================================

CREATE_PMINTERFACE(RemoveListOptionButtonObserver, kRemoveListOptionButtonObserverImpl)

//----------------------------------------------------------------------------------------
// RemoveListOptionButtonObserver constructor 
//----------------------------------------------------------------------------------------

RemoveListOptionButtonObserver::RemoveListOptionButtonObserver(IPMUnknown *boss) :
	Inherited(boss)
{
}

//----------------------------------------------------------------------------------------
// RemoveListOptionButtonObserver destructor 
//----------------------------------------------------------------------------------------

RemoveListOptionButtonObserver::~RemoveListOptionButtonObserver()
{
}

//----------------------------------------------------------------------------------------
// RemoveListOptionButtonObserver::AutoAttach
//----------------------------------------------------------------------------------------

void RemoveListOptionButtonObserver::AutoAttach()
{	
	AttachToWidget(kRemoveListOptionButtonWidgetID, IID_ITRISTATECONTROLDATA);
	AttachToWidget(kListItemsWidgetID, IID_ITREEVIEWCONTROLLER);
}

//----------------------------------------------------------------------------------------
// RemoveListOptionButtonObserver::AutoDetach
//----------------------------------------------------------------------------------------

void RemoveListOptionButtonObserver::AutoDetach()
{
	DetachFromWidget(kRemoveListOptionButtonWidgetID, IID_ITRISTATECONTROLDATA);
	DetachFromWidget(kListItemsWidgetID, IID_ITREEVIEWCONTROLLER);
}

//----------------------------------------------------------------------------------------
// RemoveListOptionButtonObserver::Update
//----------------------------------------------------------------------------------------

void RemoveListOptionButtonObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	InterfacePtr<IControlView> view(theSubject, UseDefaultIID());
	InterfacePtr<ISelectionDataSuite> iSelectionDataSuite (static_cast<ISelectionDataSuite*>(Utils<ISelectionUtils>()->QuerySuite(IID_ISELECTIONDATASUITE)));
	bool16 isSingleSelection = iSelectionDataSuite && iSelectionDataSuite->GetSelectionCount() == 1;
	InterfacePtr<ITreeViewController> optionsTreeViewCntlr((ITreeViewController*) Utils<IWidgetUtils>()->QueryRelatedWidget(
			this, kListItemsWidgetID, IID_ITREEVIEWCONTROLLER));
	NodeIDList selectedItems;
	optionsTreeViewCntlr->GetSelectedItems(selectedItems);

	if (view && (view->GetWidgetID() == kRemoveListOptionButtonWidgetID && theChange == kTrueStateMessage))
	{
		InterfacePtr<IFormFieldSuite> iFormFieldSuite(FormFieldUIUtils::QueryFormSuite());

		if (iFormFieldSuite && isSingleSelection && 
			(iFormFieldSuite->IsFieldSelectionOfType(kComboBoxItemBoss) || iFormFieldSuite->IsFieldSelectionOfType(kListBoxFieldItemBoss)))
		{			
			if (selectedItems.size() == 1)
			{
				Form::ChoiceList choiceList;
				iFormFieldSuite->GetChoiceList(choiceList);

				TreeNodePtr<const IntNodeID> treeNode(selectedItems[0]);
				int32 toRemove = treeNode->Get();

				int32 choiceListSize = choiceList.size();
				if (toRemove >= choiceListSize)
					return; // should not happen

				ICommandSequence* cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
				cmdSeq->SetName( PMString("$$$/ModifyChoiceList") );

				// First remove the selected option.
				iFormFieldSuite->RemoveChoice(choiceList[toRemove]);

				// Now set the new default (selected) option.
				PMString newDefaultStr;
				if (choiceListSize > 1)
				{
					// If removing the last option, set the new last option as the default.
					if (toRemove == choiceListSize - 1)
						newDefaultStr = choiceList[toRemove - 1];
					else
						newDefaultStr = choiceList[toRemove + 1]; // Else set the next option as default.
				}
				iFormFieldSuite->SetDefaultChoice(newDefaultStr);

				CmdUtils::EndCommandSequence(cmdSeq);
			}
		}
	}
	else if (theChange == kListSelectionChangedMessage)
	{
		InterfacePtr<IControlView> removeItemView(this, UseDefaultIID());

		// Enable the delete button if there is only a single combo/list box is selected and it has some default list item.
		if (isSingleSelection && selectedItems.size() == 1)
			removeItemView->Enable();
		else
			removeItemView->Disable();
	}
}
