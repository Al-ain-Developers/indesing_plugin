//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmldataupdaterui/DataUpdaterUIActionComponent.cpp $
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
#include "ISession.h"
#include "ITreeViewMgr.h"
#include "IControlView.h"
#include "IPanelControlData.h"
#include "ISysFileData.h"
#include "ITextControlData.h"
#include "IActiveContext.h"
#include "IActionStateList.h"
#include "ISelectionManager.h"
#include "IDocument.h"
#include "IWidgetParent.h"
#include "IPalettePanelUtils.h"
#include "K2Vector.tpp" // For NodeIDList to compile

#include "IDataUpdaterFacade.h"
#include "ITreeViewController.h"
#include "IDataUpdaterUIDataModel.h"
#include "IDataUpdaterSuite.h"

// General includes:
#include "CActionComponent.h"
#include "CmdUtils.h"
#include "Utils.h"
#include "CAlert.h"

// Project includes:
#include "DataUpdaterUINodeID.h"
#include "DataUpdaterUIID.h"
#include "DataUpdaterConst.h"
#include "SDKFileHelper.h"
#include "DataUpdaterCSVFileHelper.h"


/** Implements the actions that are executed when the plug-in's menu items are selected.

	Implements IActionComponent based on the partial implementation CActionComponent.

	
	@ingroup xmldataupdaterui
*/

class DataUpdaterUIActionComponent : public CActionComponent
{
public:
	/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	DataUpdaterUIActionComponent(IPMUnknown* boss);

	/**
		destructor.
	*/
	~DataUpdaterUIActionComponent();

	/**
		Enables or disables actions, see CActionComponent::UpdateActionStates.

	*/
	virtual void UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint = kInvalidMousePoint, IPMUnknown* widget = nil);

	/**
		The action component should do the requested action.
		This is where the menu item's action is taken.

		@param ac [IN] specifies context for menu action.
		@param actionID [IN] identifies which action this action component should perform.
		@param mousePoint [IN] contains the global mouse location at time of event-causing 
		action (e.g. context menus). kInvalidMousePoint if not relevant.
		@param widget [IN] contains the widget that invoked this action. May be nil. 
		e.g. Useful to use as a basis for Utils<IWidgetUtils>()->QueryRelatedWidget(...) 
		to find widgets in a panel after its popup menu is hit.
	*/
	virtual void DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, 	IPMUnknown* widget);

private:
	/** Encapsulates functionality for the about menu item. */
	void DoAbout();

	/** Encapsulates functionality for the Load data menu item. */
	void LoadData();

	/** Insert one value selected on the panel to the document. */
	void InsertSelectedValue(IActiveContext* ac);

	/** Insert all data from the file to the document. */
	void InsertAllData(IActiveContext* ac);

	/** Update all data in the document with new ones from the file. */
	void UpdateData(IActiveContext* ac);


private:
	void SetPanelControlData(IPMUnknown* widget);

	IPanelControlData *fPanelControlData;
	// Store the current panel control data to avoid query the data for every menu
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(DataUpdaterUIActionComponent, kDataUpdaterUIActionComponentImpl)

/* Constructor
*/
DataUpdaterUIActionComponent::DataUpdaterUIActionComponent(IPMUnknown* boss)
: CActionComponent(boss), fPanelControlData(nil)
{
}

/* Constructor
*/
DataUpdaterUIActionComponent::~DataUpdaterUIActionComponent()
{
	if (fPanelControlData)
	{
		fPanelControlData->Release();
		fPanelControlData = nil;
	}
}

void DataUpdaterUIActionComponent::UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget)
{
	// We'll use a do-while(false) to break out on bad pointers:
	do
	{

		bool16 dataLoaded = kFalse;
		this->SetPanelControlData(widget);
		InterfacePtr<ISysFileData> sysFileData(fPanelControlData, IID_ISYSFILEDATA);
		if (sysFileData) {
			IDFile theFile = sysFileData->GetSysFile();
			SDKFileHelper fileHelper(theFile);
			dataLoaded = fileHelper.IsExisting();
		}

		const int32 total_items = listToUpdate->Length();

		// Iterate through the menu items and enable or disable them
		for(int32 i = 0; i < total_items; i++)
		{
			ActionID action = listToUpdate->GetNthAction(i);
        
			switch (action.Get())
			{
				case kDataUpdaterUIAboutActionID:
				case kDataUpdaterUILoadDataActionID:
				{
					listToUpdate->SetNthActionState(i,kEnabledAction);
					break;
				}
				
				case kDataUpdaterUIInsertDataActionID:
				case kDataUpdaterUIInsertAllDataActionID:
				{
					// Enable item if text focus is set and values are loaded
					InterfacePtr<IDataUpdaterSuite> duSuite(ac->GetContextSelection(), UseDefaultIID());
					if (duSuite)
					{
						if ( dataLoaded == kTrue && duSuite->CanInsertData())
						{
							listToUpdate->SetNthActionState(i,kEnabledAction);
						}
					}
						
					break;
				}
				
				case kDataUpdaterUIUpdateDataActionID: // Update
				{			
					// Enable merge if document is open and values are loaded:
					IDocument* doc = ac->GetContextDocument();
					if (doc && dataLoaded == kTrue)
					{
						listToUpdate->SetNthActionState(i,kEnabledAction);
					}
						
					break;
				}
				
				default:
				{
					ASSERT_FAIL("Unknown menu item");
					break;
				}
			}
		}
	} while (false); // Only do once.
}

/* DoAction
*/
void DataUpdaterUIActionComponent::DoAction(
	IActiveContext* ac, 
	ActionID actionID, 
	GSysPoint mousePoint, 
	IPMUnknown* widget)
{
	switch (actionID.Get())
	{
		case kDataUpdaterUIAboutActionID:
		{
			this->DoAbout();
			break;
		}

		case kDataUpdaterUILoadDataActionID:
		{
			this->SetPanelControlData(widget);
			this->LoadData();
			break;
		}

		case kDataUpdaterUIInsertDataActionID:
		{
			this->SetPanelControlData(widget);
			this->InsertSelectedValue(ac);
			break;
		}

		case kDataUpdaterUIInsertAllDataActionID:
		{
			this->SetPanelControlData(widget);
			this->InsertAllData(ac);
			break;
		}

		case kDataUpdaterUIUpdateDataActionID:
		{
			this->SetPanelControlData(widget);
			this->UpdateData(ac);
			break;
		}

		default:
		{
			break;
		}
	}
}


/* DoAbout
*/
void DataUpdaterUIActionComponent::DoAbout()
{
	CAlert::ModalAlert
	(
	   kDataUpdaterUIAboutBoxStringKey,	// Alert string
	   kOKString, 						// OK button
	   kNullString, 					// No second button
	   kNullString, 					// No third button
	   1,									// Set OK button to default
	   CAlert::eInformationIcon	// Information icon.
	);
}


/* Load data
*/
void DataUpdaterUIActionComponent::LoadData()
{
	do
	{
		// Browse for CSV data file to load into panel
		SDKFileOpenChooser fileChooser;
		fileChooser.SetTitle(kDataUpdaterUISelectDataFileStringKey);
		fileChooser.AddFilter(kCSVFileTypeInfoID, kDataUpdaterUICSVFilterStringKey);
		fileChooser.ShowDialog();
		if (!fileChooser.IsChosen()) {
			break;
		}
		IDFile theFile = fileChooser.GetIDFile();

		
		// Set the data file of the panel
		InterfacePtr<ISysFileData> sysFileData(fPanelControlData, IID_ISYSFILEDATA);
		ASSERT(sysFileData);
		if (sysFileData) {
			sysFileData->Set(theFile);
		}

		// Update tree view
		IControlView* treeWidget = fPanelControlData->FindWidget(kDataUpdaterUITreeViewWidgetID);
		ASSERT(treeWidget);
		if(!treeWidget) {
			break;
		}

		InterfacePtr<ITreeViewMgr> 
				iTreeViewMgr(treeWidget, UseDefaultIID());
		ASSERT(iTreeViewMgr);
		if(!iTreeViewMgr){
			break;
		}
		InterfacePtr<IDataUpdaterUIDataModel> model(iTreeViewMgr, UseDefaultIID());
		model->Initialize(theFile);
		
		iTreeViewMgr->ClearTree();
		iTreeViewMgr->ChangeRoot(kFalse);

		// Update the file name 
        IControlView *iWidgetView = fPanelControlData->FindWidget(kDataUpdaterUITextMessageWidgetID);
        ASSERT(iWidgetView);
        if(!iWidgetView) {
            break;
        }
        InterfacePtr<ITextControlData>   textControlData(iWidgetView, UseDefaultIID());
        ASSERT(textControlData);
        if(!textControlData)
        {
            break;
        }
        textControlData->SetString(model->GetFileName());

	} while(kFalse);
}



/* Insert selected value
*/
void DataUpdaterUIActionComponent::InsertSelectedValue(IActiveContext* ac)
{
	do
	{
		//get selected value on the panel and insert into the document
		IControlView* treeWidget = fPanelControlData->FindWidget(kDataUpdaterUITreeViewWidgetID);
		ASSERT(treeWidget);
		if(!treeWidget) {
			break;
		}

		InterfacePtr<ITreeViewController> 	controller(treeWidget, UseDefaultIID());
		ASSERT(controller);
		if(!controller)
		{
			break;
		}

		NodeIDList selectedItems;
		controller->GetSelectedItems(selectedItems);
		// We've got single selection only
		if(selectedItems.size()<=0)
			break;

		TreeNodePtr<DataUpdaterUINodeID> nodeID(selectedItems[0]);
		ASSERT(nodeID);
		if(!nodeID)
			break;

		PMString type(nodeID->GetType());
		PMString value(nodeID->GetValue());
		//Now we only insert one value at a time, 
		//May be able to insert a record or even a whole table depend on selection
		if (type == kDataUpdaterValueTag)
		{
			InterfacePtr<IDataUpdaterUIDataModel> model(treeWidget, UseDefaultIID());
			if (!model)
				break;
			
			int32 valueIndex(nodeID->GetIndex());
			PMString table = model->GetTable();
			int32 numField = model->GetFieldCount();
			int32 recIndex = valueIndex / numField;
			int32 fieldIndex = valueIndex - recIndex * numField;
			PMString record = model->GetNthValue(recIndex, 0);
			PMString field = model->GetNthField(fieldIndex);

			// Use the suite to insert the data
			InterfacePtr<IDataUpdaterSuite> duSuite(ac->GetContextSelection(), UseDefaultIID());
			ASSERT(duSuite);
			if (!duSuite) {
				break;
			}

			duSuite->InsertData(WideString(table),WideString(record), WideString(field), WideString(value) );
		}
		
	} while(kFalse);	

}

/* Insert all value
*/
void DataUpdaterUIActionComponent::InsertAllData(IActiveContext* ac)
{
	do
	{
		InterfacePtr<ISysFileData> sysFileData(fPanelControlData, IID_ISYSFILEDATA);
		ASSERT(sysFileData);
		if (!sysFileData) 
			break;

		IDFile file = sysFileData->GetSysFile();

		// Use the suite to insert the data
		InterfacePtr<IDataUpdaterSuite> duSuite(ac->GetContextSelection(), UseDefaultIID());
		ASSERT(duSuite);
		if (!duSuite) {
			break;
		}
		ErrorCode status = duSuite->InsertAllData(file);
		if (status != kSuccess) {
			CAlert::ErrorAlert(kDataUpdaterUIErrorInsertAllSequenceFailed);
		}		
	} while(kFalse);	

}

/* Insert all value
*/
void DataUpdaterUIActionComponent::UpdateData(IActiveContext* ac)
{
	do
	{
		InterfacePtr<ISysFileData> sysFileData(fPanelControlData, IID_ISYSFILEDATA);
		ASSERT(sysFileData);
		if (!sysFileData) 
			break;

		IDFile file = sysFileData->GetSysFile();

		IDocument* doc = ac->GetContextDocument();
		if (!doc)
			break;
		ErrorCode status = Utils<IDataUpdaterFacade>()->UpdateData(::GetUIDRef(doc), file); 
		if (status != kSuccess) 
			CAlert::ErrorAlert(kDataUpdaterUIErrorUpdateDataFailed);
	} while(kFalse);	

}

/*	SetPanelControlData
*/
void DataUpdaterUIActionComponent::SetPanelControlData(IPMUnknown* widget)
{
	if (fPanelControlData == nil )
		fPanelControlData = Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kDataUpdaterUIPanelWidgetID) ;
	ASSERT( fPanelControlData ) ;
}

// End, DataUpdaterUIActionComponent.cpp.
