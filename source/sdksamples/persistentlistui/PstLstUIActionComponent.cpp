//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlistui/PstLstUIActionComponent.cpp $
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
#include "IApplication.h"
#include "ISession.h"
#include "IDialogMgr.h"
#include "ISelectionManager.h"
#include "ILayoutUIUtils.h"
#include "IDocument.h"
#include "IWidgetParent.h"
#include "IPanelControlData.h"
#include "ITreeViewController.h"

// General includes:
#include "CActionComponent.h"
#include "CAlert.h"
#include "CoreResTypes.h"
#include "IActionStateList.h"
#include "LocaleSetting.h"
#include "K2Vector.tpp"
#include "UIDList.h"

// Project includes:
#include "PstLstUINodeID.h"
#include "PstLstUIID.h"
#include "PstLstUIUtils.h"
#include "IPstLstSuite.h"
#include "IPstLstUIDList.h"

/** PstLstUIActionComponent
	Implements the actions that are executed when the plug-in's
	menu items are selected.


	@ingroup persistentlist
	
*/
class PstLstUIActionComponent : public CActionComponent
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		PstLstUIActionComponent(IPMUnknown* boss);

		/**
			The action component should do the requested action.
			@param context See IActionComponent::DoAction
			@param actionID identifies the menu item that was selected.
			@param mousePoint See IActionComponent::DoAction
			@param widget See IActionComponent::DoAction
			@see IActionComponent::DoAction
			*/
		virtual void DoAction(IActiveContext* context, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);

		/**
			Called by the framework enable or disable items.
			@param context See IActionComponent::UpdateActionStates
			@param listToUpdate is used for action components to update the state of their actions.
			@param mousePoint See IActionComponent::UpdateActionStates
			@param widget See IActionComponent::UpdateActionStates
			@see IActionComponent::UpdateActionStates
		*/
		virtual void	UpdateActionStates(IActiveContext* context, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget);

	private:
		typedef enum
		{
			kNothingSelected = 0,
			kPageItemSelected,
			kPstLstItemSelected,
			kMixedItemSelected
		} PanelSelectionType;

		/** 
			Encapsulates functionality for the about menu item. 
		*/
		void DoAbout();

		/** 
			Create a new string & add it to the list of strings associated with the selected page item.
		*/
		void DoNew(UIDList * &list);

		/** 
			Edit the string selected in the panel.
		*/
		void DoModify(UIDList *&list);

		/** 
			Remove the string from the list of strings attached to the page item, and delete the string from the database.
			@param context IN The active context.
		*/
		void DoDelete(UIDList *&list);

		/*	PstLstUIActionComponent::GetPanelSelectedItems
			Get a list of Persistent list data or drawable page items selected on the panel. 
			@param widget See IActionComponent::DoAction
			@param list UIDList of selected persistent list data or drawable page items.
			@return selectionType current panel selection type. Valid values are defined in PanelSelectionType.
		*/
		int32 GetPanelSelectedItems(IPMUnknown* widget, UIDList * &list);
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(PstLstUIActionComponent, kPstLstUIActionComponentImpl)

/* PstLstUIActionComponent Constructor
*/
PstLstUIActionComponent::PstLstUIActionComponent(IPMUnknown* boss)
: CActionComponent(boss)
{
}

/*	PstLstUIActionComponent::DoAction
*/
void PstLstUIActionComponent::DoAction(IActiveContext* context, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
	switch (actionID.Get())
	{
		case kPstLstUIPopupAboutThisActionID:
		case kPstLstUIAboutActionID:
		{
			this->DoAbout();
			break;
		}

		case kPstLstUINewActionID:
		{
			UIDList *list = nil;
			int32 selType = this->GetPanelSelectedItems(widget, list);

			//At this point, if we found there is nothing selected, populate
			//the UIDList with all of the drawable page items in the panel
			if 	(selType == kNothingSelected)
			{
				//We get the drawable page items from the selection suite directly
				//The other alternative, you may also get the list from the panel
				// by iterating children of the root node.
				InterfacePtr<IPstLstSuite> iPstLstSuite(context->GetContextSelection(), UseDefaultIID()); 
				if (iPstLstSuite)
				{
					int32 count = 0;
					UIDRef item;
					iPstLstSuite->GetNumDrawablePageItemSelected(count);
					for(int i=0; i < count; i++)
					{
						iPstLstSuite->GetNthSelectedDrawablePageItem(i, item);
						list->Append(item);
					}
				}
			}

			if ( selType == kNothingSelected || selType == kPageItemSelected  )
				this->DoNew(list);
			delete list;
			break;
		}

		case kPstLstUIModifyActionID:
		{
			UIDList *list = nil;
			int32 selType = this->GetPanelSelectedItems(widget, list);
			if ( selType == kPstLstItemSelected)
				this->DoModify(list);
			delete list;
			break;
		}

		case kPstLstUIDeleteActionID:
		{
			UIDList *list = nil;
			int32 selType = this->GetPanelSelectedItems(widget, list);
			if ( selType == kPstLstItemSelected)
				this->DoDelete(list);
			delete list;
			break;
		}

		default:
		{
			break;
		}
	}
}

/* PstLstUIActionComponent::UpdateActionStates
*/
void PstLstUIActionComponent::UpdateActionStates(IActiveContext* context, IActionStateList *listToUpdate, GSysPoint mousePoint,IPMUnknown* widget)
{
	do 
	{			
		if (!listToUpdate) 
		{
			ASSERT(listToUpdate);
			break;
		}
		if (context == nil)
		{
			ASSERT(context);
			break;
		}
		InterfacePtr<IPstLstSuite> iPstLstSuite(context->GetContextSelection(), UseDefaultIID()); 
		if (iPstLstSuite == nil) 
		{
			ASSERT(iPstLstSuite);
			break;
		}

		for(int i=0; i < listToUpdate->Length(); i++) 
		{
			ActionID actionID = listToUpdate->GetNthAction(i);
			switch (actionID.Get())
			{
				case kPstLstUINewActionID:
				{
					UIDList *list = nil;
					int32 selType = this->GetPanelSelectedItems(widget, list);
					if ( selType == kNothingSelected || selType == kPageItemSelected  )
					{
						listToUpdate->SetNthActionState(i,kEnabledAction);
						
						// update menu string according to selection
						PMString menuItemString(kPstLstUINewMenuItemKey);
						if (selType == kNothingSelected)
							menuItemString = kPstLstUINewAllMenuItemKey;

						listToUpdate->SetNthActionName(i,menuItemString);

					}
					else {
						listToUpdate->SetNthActionState(i,kDisabled_Unselected);
					}
					delete list;
					break;
				}

				case kPstLstUIModifyActionID:
				{
					UIDList *list = nil;
					int32 selType = this->GetPanelSelectedItems(widget, list);
					if (selType == kPstLstItemSelected )
					{
						listToUpdate->SetNthActionState(i,kEnabledAction);
					}
					else {
						listToUpdate->SetNthActionState(i,kDisabled_Unselected);
					}
					delete list;
					break;
				}

				case kPstLstUIDeleteActionID:
				{
					UIDList *list = nil;
					int32 selType = this->GetPanelSelectedItems(widget, list);
					if (selType == kPstLstItemSelected )
					{
						listToUpdate->SetNthActionState(i,kEnabledAction);
					}
					else {
						listToUpdate->SetNthActionState(i,kDisabled_Unselected);
					}
					delete list;

					break;
				}

				default: 
				{
					break;
				}
			} // end switch
		} // end for
	} while(kFalse);
}

/*	PstLstUIActionComponent::DoAbout
*/
void PstLstUIActionComponent::DoAbout()
{
	CAlert::ModalAlert
	(
	   kPstLstUIAboutBoxStringKey,			// Alert string
	   kOKString, 							// OK button
	   kNullString, 						// No second button
	   kNullString, 						// No third button
	   1,									// Set OK button to default
	   CAlert::eInformationIcon				// Information icon.
	);
}

/*	PstLstUIActionComponent::DoNew
*/
void PstLstUIActionComponent::DoNew(UIDList * &list)
{
	PstLstUIUtils::InvokePstLstDialog(kPstLstNew, list);
}

/*	PstLstUIActionComponent::DoModify
*/
void PstLstUIActionComponent::DoModify(UIDList * &list)
{
	PstLstUIUtils::InvokePstLstDialog(kPstLstModify, list);
}

/*	PstLstUIActionComponent::DoDelete
*/
void PstLstUIActionComponent::DoDelete(UIDList * &list)
{
	InterfacePtr<ICommand> deleteDataCmd(CmdUtils::CreateCommand(kPstLstDeleteDataCmdBoss));
	deleteDataCmd->SetItemList(*list);
	ErrorCode err = CmdUtils::ProcessCommand(deleteDataCmd);
	if (err != kSuccess)
		CAlert::WarningAlert(kPstLstUIDeleteCmdFailedKey);
}

/*	PstLstUIActionComponent::GetPanelSelectedItems
    Get a list of selected Persistent data selected on the panel. If a page item
	is selected, all persistent list data items are included.
*/
int32 PstLstUIActionComponent::GetPanelSelectedItems(IPMUnknown* widget, UIDList* &list)
{
	int32 selectionType = kNothingSelected;
	IDocument* document = Utils<ILayoutUIUtils>()->GetFrontDocument();
	if (!document)
		return 0;

	IDataBase *db = ::GetDataBase(document);
	UIDList *retList = new UIDList(db);
	do
	{
		if (!widget)
			break;

        InterfacePtr<IWidgetParent> widgetParent(widget,UseDefaultIID());
        if (!widgetParent)
			break;

        InterfacePtr<IPanelControlData> panelData((IPanelControlData*)widgetParent->QueryParentFor(IID_IPANELCONTROLDATA));
  
		//get selected value on the panel and insert into the document
        IControlView* treeWidget = panelData->FindWidget(kPstLstUITreeViewWidgetID);
        ASSERT(treeWidget);
        if(!treeWidget) {
            break;
        }

        InterfacePtr<ITreeViewController>     controller(treeWidget, UseDefaultIID());
        ASSERT(controller);
        if(!controller)
        {
            break;
        }

        NodeIDList selectedItems;
        controller->GetSelectedItems(selectedItems);
        int32 len = selectedItems.size();

		for (int32 i = 0; i < len; i++)
		{
			TreeNodePtr<PstLstUINodeID> nodeID(selectedItems[i]);
			ASSERT(nodeID);
			if(!nodeID)
				break;

			if ( nodeID->GetDataType() == PstLstUINodeID::kPageItemType)
			{  
				if 	(selectionType == kNothingSelected)
					selectionType = kPageItemSelected;
				else if (selectionType == kPstLstItemSelected)
					selectionType = kMixedItemSelected;

				retList->Append(nodeID->GetUID());
			}
			else if ( nodeID->GetDataType() == PstLstUINodeID::kPersistentListType)
			{
				if 	(selectionType == kNothingSelected)
					selectionType = kPstLstItemSelected;
				else if (selectionType == kPageItemSelected)
					selectionType = kMixedItemSelected;

				retList->Append(nodeID->GetUID());
			}
			else
				ASSERT_MSG(kFalse, "Unexpected selected root type");
		}


	} while (kFalse);

	list = retList;
	return selectionType;
}

//  Generated by Dolly build 17: template "IfPanelMenu".
// End, PstLstUIActionComponent.cpp.

