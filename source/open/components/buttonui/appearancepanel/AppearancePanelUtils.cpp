//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/appearancepanel/AppearancePanelUtils.cpp $
//  
//  Owner: Tim Wright
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
//  
//  Comments: Implements behaviors for appearance panel (creating/deleting/selecting states)
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interfaces:
#include "IApplication.h"
#include "IBoolData.h"
#include "ICmdCollection.h"
#include "ICommand.h"
#include "IDialogController.h"
#include "IDialogController.h"
#include "IDialogMgr.h"
#include "IDialogMgr.h"
#include "IDocument.h"
#include "IDocumentLayer.h"
#include "IGuidePrefs.h"
#include "IHierarchy.h"
#include "IImportManager.h"
#include "IImportManagerOptions.h"
#include "IImportSuite.h"
#include "IIntData.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "ILayoutCmdData.h"
#include "ILayoutControlData.h"
#include "IListBoxAttributes.h"
#include "IListBoxController.h"
#include "IListControlDataOf.h"
#include "IMasterSpreadList.h"
#include "IMemoryManager.h"
#include "INewLayerCmdData.h"
#include "IPanelControlData.h"
#include "IPanelMgr.h"
#include "ISpread.h"
#include "ISpreadLayer.h"
#include "ISpreadList.h"
#include "ITextFocus.h"
#include "IUIDData.h"
#include "IUIDListData.h"
#include "IWidgetParent.h"
#include "IWindow.h"
#include "IWorkspace.h"
#include "IImportCore.h"
#include "IOpenFileDialog.h"

// Includes:
#include "CAlert.h"
#include "CoreResTypes.h"
#include "EventUtilities.h"
#include "LocaleSetting.h"

#include "RsrcSpec.h"
#include "SelectionUtils.h"
#include "UIDList.h"

// Utility files:
#include "CmdUtils.h"
#include "ILayoutUIUtils.h"
#include "IPalettePanelUtils.h"
#include "PreferenceUtils.h"
#include "StringUtils.h"
#include "UIDListUtils.h"
#include "IURIUtils.h"
// ID.h files:
#include "LayerID.h"
#include "LayoutUIID.h"
#include "MasterPageID.h"
#include "SpreadID.h"
#include "TextID.h"
#include "OpenPlaceID.h"

#include "IStateData.h"
#include "IAppearanceSuite.h"
#include "AppearancePanelUtils.h"
#include "FormFieldUIID.h"
#include "FormFieldUIDefs.h"
#include "IFormFieldUtils.h"
#include "FormFieldUIUtils.h"
#include "UserInterfaceUtils.h"


// ------------------------------------------------------------------------------

// Helper function to return the indices of selected items in this list and their states
// Use the Widget parent interface of the panel to find the list box and then the selected items.
// Note that the active state is always the first index (and state) in the list(s).
void GetSelectedStates(
		K2Vector<int32>& ioSelectedItems,
		K2Vector<Form::AppearanceState>& ioStates,
		IPanelControlData* layerPanelData)
{
	InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IPanelMgr> panelMgr(app->QueryPanelManager());

	if (panelMgr->IsPanelWithWidgetIDShown(kAppearanceParentWidgetId))
	{
		IControlView* panelControlView = panelMgr->GetVisiblePanel(kAppearanceParentWidgetId);
		if (panelControlView)
		{
			InterfacePtr<IPanelControlData> panelData(panelControlView, IID_IPANELCONTROLDATA);
			
			WidgetID listBoxID = Utils<IPalettePanelUtils>()->GetCurrentListBoxID(panelData);
			InterfacePtr< IListControlDataOf<IControlView*> > listData(panelData->FindWidget(listBoxID), IID_ILISTCONTROLDATA);
			InterfacePtr<IListBoxController> controller(listData, IID_ILISTBOXCONTROLLER);
			if (listData)
			{
				controller->GetSelected(ioSelectedItems);
				
				int32 numStates = ioSelectedItems.size();
				for (int32 i = 0; i < numStates; i++)
				{
					int32 stateIndex = ioSelectedItems[i];
					if (controller->IsSelected(stateIndex))
					{
						InterfacePtr<IStateData> listElementStateData((*listData)[stateIndex], IID_ISTATEDATA);
						Form::AppearanceState state = listElementStateData->GetState();
						ioStates.push_back(state);
					}
				}
			}
		}
	}

}

// ------------------------------------------------------------------------------

ErrorCode DuplicateStates(IPanelControlData* inPanelData)
{
	IDocument* frontDoc = Utils<ILayoutUIUtils>()->GetFrontDocument();
	InterfacePtr<ILayoutControlData> layoutData(Utils<ILayoutUIUtils>()->QueryFrontLayoutData());

	if (frontDoc && layoutData)
	{

		// Get a list of selected layers and their UIDs
		K2Vector<int32> selectedStateIndeces;
		K2Vector<Form::AppearanceState> selectedStates;
		GetSelectedStates(selectedStateIndeces, selectedStates, inPanelData);

		int32 numStates = selectedStateIndeces.size();
		for (int32 i = 0; i < numStates; i++)
		{
			if (CanCreateNewState())
				CreateNewState();
		}
	}
	
	return kSuccess;
}

// ------------------------------------------------------------------------------


// Are there expendable states selected?
bool16 CanDeleteSelectedStates(IPanelControlData* panelData)
{
	InterfacePtr<IMemoryManager> memMgr(GetExecutionContextSession(), IID_IMEMORYMANAGER);
	if(memMgr->MemoryIsLow())
		return kFalse;
		
	if (Utils<ILayoutUIUtils>()->GetFrontDocument() != nil)
	{
		// Get a list of selected states and their indeces
		K2Vector<int32> selectedItems;
		K2Vector<Form::AppearanceState> selectedStates;
		GetSelectedStates(selectedItems, selectedStates, panelData);

		int32 numSelected = selectedItems.size();
		if (numSelected)
		{
			InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
			if (iAppearanceSuite && iAppearanceSuite->HasStates())
			{
				bool16 canDelete = kTrue;
				for (int32 ii = 0; ii < numSelected && canDelete; ii++)
				{
					canDelete = iAppearanceSuite->HasAppearance(selectedStates[ii])
						&& Utils<IFormFieldUtils>()->CanDeleteState(selectedStates[ii]);
				}
				return canDelete;
			}
		}
	}

	return kFalse;
}

// ------------------------------------------------------------------------------

// This function returns a compound command made up of delete layer
// commands delete all the selected layers. The boolean determines whether
// to check and see if the layer(s) are used in the pub or not. If we
// check, and there are used layers, put up an alert and ask the user if
// they really want to delete the layers.
ErrorCode DeleteSelectedStates(IPanelControlData* inPanelData)
{	
	// Get a list of selected states
	K2Vector<int32> selectedItems;
	IDocument* frontDoc = Utils<ILayoutUIUtils>()->GetFrontDocument();
	K2Vector<Form::AppearanceState> selectedStates;
	GetSelectedStates(selectedItems, selectedStates, inPanelData);

	int32 numStates = selectedItems.size();

	if (numStates)
	{
		InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());

		if (iAppearanceSuite && iAppearanceSuite->HasStates())
		{
			ICommandSequence* cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
			cmdSeq->SetName("$$$/Command/DeleteStates");

			// Delete all the selected layers
			for (int32 ii = 0; ii < numStates; ii++)
			{
				if ( Utils<IFormFieldUtils>()->CanDeleteState(selectedStates[ii]) )
					iAppearanceSuite->DeleteState( selectedStates[ii] );
			}
			
			return CmdUtils::EndCommandSequence(cmdSeq);
		}
	}
	
	return kSuccess;
}

// ------------------------------------------------------------------------------

ErrorCode DeleteSelectedStateContent(IPanelControlData* inPanelData)
{	
	// Get a list of selected states
	K2Vector<int32> selectedItems;
	IDocument* frontDoc = Utils<ILayoutUIUtils>()->GetFrontDocument();
	K2Vector<Form::AppearanceState> selectedStates;
	GetSelectedStates(selectedItems, selectedStates, inPanelData);

	int32 numStates = selectedItems.size();

	if (numStates)
	{
		InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());

		if (iAppearanceSuite && iAppearanceSuite->HasStates())
		{
			ICommandSequence* cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
			cmdSeq->SetName("$$$/CmdName/DeleteStateContent");

			// Delete the content of all the selected states
			for (int32 ii = 0; ii < numStates; ii++)
			{
				iAppearanceSuite->DeleteStateContent( selectedStates[ii] );
			}
			
			return CmdUtils::EndCommandSequence(cmdSeq);
		}
	}
	
	return kSuccess;
}

// ------------------------------------------------------------------------------

ErrorCode PlaceIntoSelectedState(IPanelControlData* inPanelData)
{		
	InterfacePtr<IK2ServiceRegistry>	registry(GetExecutionContextSession(), UseDefaultIID());
	InterfacePtr<IK2ServiceProvider> importMgrService(registry->QueryDefaultServiceProvider(kImportManagerService));
	InterfacePtr<IImportManager> importMgr(importMgrService, UseDefaultIID());
	
	URIList URIsToImport;
	// aol - linksrework, we now require a dialog be passed to the import manager. 
	InterfacePtr<IImportCore> iImportCore(importMgr,IID_IIMPORTCORE);
	if (iImportCore == nil){
		ASSERT(iImportCore);
		return kFailure;
	}
	InterfacePtr<IOpenFileDialog> iPlaceDialog(iImportCore->QueryPlaceFileDialog());
	if (importMgr->DoImportDialog(&URIsToImport, kFalse,iPlaceDialog)) 
	{
		// Grab the import options before any thing has a chance to be purged.  The import options
		// interface is NOT persistent.
		InterfacePtr<IImportManagerOptions> importOptions(importMgr, IID_IIMPORTMANAGEROPTIONS);
		UIFlags uiFlags;
		
		// If the shift key is down, show filter preferences.
		if (::IsShiftKeyPressed() || importOptions->GetShowFilterPrefs())
			uiFlags = kFullUI;
		else
			uiFlags = kMinimalUI;
		
		bool16 retainFormat = importOptions->GetRetainFormat();
		bool16 convertQuotes = importOptions->GetConvertQuotes();
		bool16 replaceSelectedItem = kTrue;
		bool16 applyCJKGrid = importOptions->GetApplyCJKGrid();
		
		IDocument	* frontDoc = Utils<ILayoutUIUtils>()->GetFrontDocument();
		ASSERT(frontDoc != nil);
		IDataBase * db = ::GetDataBase(frontDoc);
		ASSERT(db != nil);
		InterfacePtr<IImportSuite> iImportSuite(SelectionUtils::QuerySuite<IImportSuite>());
		ASSERT(iImportSuite != nil);

		iImportSuite->DoImport(URIsToImport.GetNthURI(0), db, replaceSelectedItem, uiFlags, retainFormat, convertQuotes, applyCJKGrid);
	}
	return kSuccess;
}

// ------------------------------------------------------------------------------


// Is there content within the states selected?
bool16 HasStateContent(IPanelControlData* panelData)
{
	InterfacePtr<IMemoryManager> memMgr(GetExecutionContextSession(), IID_IMEMORYMANAGER);
	if(memMgr->MemoryIsLow())
		return kFalse;
		
	bool16 canDelete = kFalse;
	if (Utils<ILayoutUIUtils>()->GetFrontDocument() != nil)
	{
		// Get a list of selected states and their indeces
		K2Vector<int32> selectedItems;
		K2Vector<Form::AppearanceState> selectedStates;
		GetSelectedStates(selectedItems, selectedStates, panelData);

		int32 numSelected = selectedItems.size();
		if (numSelected)
		{
			InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());
			if (iAppearanceSuite && iAppearanceSuite->HasStates())
			{
				bool16 hasContent = kFalse;
				for (int32 ii = 0; ii < numSelected && !hasContent; ii++)
				{
					hasContent = iAppearanceSuite->HasAppearanceContent(selectedStates[ii]);
				}
				return hasContent;
			}
		}
	}

	return kFalse;
}

// ------------------------------------------------------------------------------

// This function returns a pipeline command made up of
// a new layer command, a set active layer command, and
// potentially a move layer command depending on the desired
// layer location.
bool16 CanCreateNewState()
{
	ICommand* cmd = nil;
	IDocument* frontDocument = Utils<ILayoutUIUtils>()->GetFrontDocument();
	if (frontDocument)
	{
		InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());

		//Ask for the next non-existant, supported state
		if (iAppearanceSuite)
			return ( iAppearanceSuite->GetNewState() != Form::kStateInvalid );
	}
	
	return kFalse;
}

// ------------------------------------------------------------------------------

// This function returns a pipeline command made up of
// a new layer command, a set active layer command, and
// potentially a move layer command depending on the desired
// layer location.
void CreateNewState()
{
	ICommand* cmd = nil;
	IDocument* frontDocument = Utils<ILayoutUIUtils>()->GetFrontDocument();
	if (frontDocument)
	{
		InterfacePtr<IAppearanceSuite> iAppearanceSuite(FormFieldUIUtils::QueryAppearanceSuite());

		//Create the next non-existant, supported state
		if (iAppearanceSuite)
		{
			Form::AppearanceState newState = iAppearanceSuite->GetNewState();
				
			if ( newState != Form::kStateInvalid )
			{
				ICommandSequence* cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
				cmdSeq->SetName("$$$/Command/NewState");

				iAppearanceSuite->NewState(newState);
				iAppearanceSuite->SetActiveState( newState );
				
				CmdUtils::EndCommandSequence(cmdSeq);
			}
		}
	}
}


// ------------------------------------------------------------------------------

// Invoke the Layer Options or New Layer dialog based on the options parameter.
// kTrue for the Layer Options dialog, kFalse for New Layer dialog. A UIDList of
// selected layers is stored in IUIDListData for the dialog controller to use.
void InvokeStatePropertiesDialog(Form::AppearanceState inState)
{
	//SPAM twright 05/02/2001 Need to decide what to do if anything for this...
	
	if (CanDoStatePropertiesDialog(inState))
		DoStatePropertiesDialog(inState);
}


//------------------------------------------------------------------------
// Check if state properties dialog is allowed on the state inState of the current selection...

bool16 CanDoStatePropertiesDialog(Form::AppearanceState inState)
{
	InterfacePtr<IAppearanceSuite> iAppearanceSuite( FormFieldUIUtils::QueryAppearanceSuite() );
	
	return (iAppearanceSuite && iAppearanceSuite->HasAppearance(inState) && Utils<IFormFieldUtils>()->CanDeleteState(inState));
}


//------------------------------------------------------------------------

void DoStatePropertiesDialog(Form::AppearanceState inState)
{
	bool canDoDialog = CanDoStatePropertiesDialog(inState);
	ASSERT_MSG( canDoDialog, "No modifiable states on selection");
	
	if (canDoDialog)
	{
		IDialog* dialog = UserInterfaceUtils::GetModalDialog( kFormFieldUIPluginID, kStateOptionsDialogRsrcID );
		
		IControlView* dialogView = dialog->GetDialogPanel();
		InterfacePtr<IDialogController> iDialogController(dialogView, IID_IDIALOGCONTROLLER);
		InterfacePtr<IStateData> iState( iDialogController, IID_ISTATEDATA );

		iState->Set( inState );
		
		// Open causes the dialog to be displayed and then returns immediately
		//	so WaitForDialog() is used.
		dialog->Open();
		dialog->WaitForDialog();
	}
}


