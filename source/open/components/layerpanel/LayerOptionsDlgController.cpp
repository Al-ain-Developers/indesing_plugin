//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/layerpanel/LayerOptionsDlgController.cpp $
//  
//  Owner: psorrick
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
#include "IBoolData.h"
#include "ICmdCollection.h"
#include "IColorData.h"
#include "IColorListControlData.h"
#include "ICommand.h"
#include "IControlView.h"
#include "IDialog.h"
#include "IDocument.h"
#include "IDocumentLayer.h"
#include "IDropDownListController.h"
#include "IEventHandler.h"
#include "IHierarchy.h"
#include "IIntData.h"
#include "ILayerList.h"
#include "ILayoutCmdData.h"
#include "INewLayerCmdData.h"
#include "IPanelControlData.h"
#include "IPMUnknownData.h"
#include "IRealNumberData.h"
#include "IStringData.h"
#include "IStringListControlData.h"
#include "ISubject.h"
#include "ISwatchList.h"
#include "ITextControlData.h"
#include "ITextValue.h"
#include "ITriStateControlData.h"
#include "IUIDData.h"
#include "IWidgetParent.h"
#include "ILayerFacade.h"

// ----- Includes -----

#include "CAlert.h"
#include "CUIColorSwatchView.h"	// For kMixedColorUID
#include "LayerOptionsDlgController.h"
#include "PMReal.h"

#include "UIDList.h"
#include "LocaleSetting.h"

// ----- Utility files -----

#include "CmdUtils.h"
#include "IPalettePanelUtils.h"
#include "iuicolorutils.h"

// ----- ID.h files -----

#include "LayerID.h"
#include "LayerPanelID.h"
#include "LayoutUIID.h"


CREATE_PMINTERFACE(LayerOptionsDlgController, kLayerOptionsDlgControllerImpl)

//========================================================================================
// CLASS LayerOptionsDlgController
//========================================================================================

LayerOptionsDlgController::LayerOptionsDlgController(IPMUnknown *boss) :
	CDialogController(boss),
	fDialogType (LayerPanelUtils::kNewLayerDialog),
	fLayerLocation (LayerPanelUtils::kAboveActive)
{
}

LayerOptionsDlgController::~LayerOptionsDlgController()
{
}

void LayerOptionsDlgController::InitializeDialogFields( IActiveContext* dlgContext)
{
	ColorArray emptyColor;
	IDocument* doc = dlgContext->GetContextDocument();
	if (!doc)
		return;

	InterfacePtr<IWidgetParent> parentHolder(this, IID_IWIDGETPARENT);
	InterfacePtr<IPanelControlData> panel(parentHolder->GetParent(),IID_IPANELCONTROLDATA);
	IControlView* nameWidget = panel->FindWidget(kLayerNameWidgetID);
	bool16 enableName = kTrue;

	// See if this dialog is in Layer Options or New Layer mode. This dialog
	// is shared between both dialogs, and just the title is changed.
	InterfacePtr<IIntData> dialogTypeData(this, IID_IDIALOGTYPEDATA);
	fDialogType = (LayerPanelUtils::LayerDialogType)dialogTypeData->GetInt();

	// For New Layer, user can control the location the new layer is put in.
	InterfacePtr<IIntData> intData(this, IID_IINTDATA);
	fLayerLocation = (LayerPanelUtils::LayerLocation)intData->GetInt();

	// State of each checkbox and control
	ITriStateControlData::TriState show = ITriStateControlData::kSelected;
	ITriStateControlData::TriState print = ITriStateControlData::kSelected;
	ITriStateControlData::TriState lock = ITriStateControlData::kUnselected;
	ITriStateControlData::TriState showGuides = ITriStateControlData::kSelected;
	ITriStateControlData::TriState lockGuides = ITriStateControlData::kUnselected;
	ITriStateControlData::TriState ignore = ITriStateControlData::kUnselected;

	PMString name;
	ColorArray color;
	UID	swatchColorUID = kInvalidUID;

	// Layer Options and Duplicate Layer dialogs
	if (fDialogType == LayerPanelUtils::kLayerOptionsDialog)
	{
		// Get the list of selected layers that we are operating on.
		InterfacePtr<IPMUnknownData> targetData(this, UseDefaultIID());
		UIDList targetUIDList(::GetDataBase(doc));

		LayerPanelUtils::GetTargetLayers(targetUIDList, targetData->GetPMUnknown());

		int32 numLayers = targetUIDList.Length();
		if (numLayers > 1)
			enableName = kFalse;

		InterfacePtr<IDocumentLayer> firstLayer(targetUIDList.GetRef(0), IID_IDOCUMENTLAYER);
		
		show = firstLayer->IsVisible() ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected;
		print = firstLayer->IsPrintable() ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected;
		lock = firstLayer->IsLocked() ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected;
		showGuides = firstLayer->IsGuideVisible() ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected;
		lockGuides = firstLayer->IsGuideLocked() ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected;
		ignore = firstLayer->GetIgnoreTextWrapWhenNotVisible() ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected;

		name = firstLayer->GetName();

		swatchColorUID = firstLayer->GetColorUID();
		color = Utils<IUIColorUtils>()->GetRGBColorValue(::GetDataBase(doc), swatchColorUID);

		// Now do the rest of the layers
		for (int32 i = 1; i < numLayers; i++)
		{
			InterfacePtr<IDocumentLayer> docLayer(targetUIDList.GetRef(i), IID_IDOCUMENTLAYER);
			if (show != ITriStateControlData::kUnknown)
			{
				ITriStateControlData::TriState nextShow = docLayer->IsVisible() ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected;
				if (show != nextShow)
					show = ITriStateControlData::kUnknown;
			}

			if (print != ITriStateControlData::kUnknown)
			{
				ITriStateControlData::TriState nextPrint = docLayer->IsPrintable() ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected;
				if (print != nextPrint)
					print = ITriStateControlData::kUnknown;
			}

			if (lock != ITriStateControlData::kUnknown)
			{
				ITriStateControlData::TriState nextLock = docLayer->IsLocked() ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected;
				if (lock != nextLock)
					lock = ITriStateControlData::kUnknown;
			}

			if (showGuides != ITriStateControlData::kUnknown)
			{
				ITriStateControlData::TriState nextShowGuides = docLayer->IsGuideVisible() ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected;
				if (showGuides != nextShowGuides)
					showGuides = ITriStateControlData::kUnknown;
			}

			if (lockGuides != ITriStateControlData::kUnknown)
			{
				ITriStateControlData::TriState nextLockGuides = docLayer->IsGuideLocked() ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected;
				if (lockGuides != nextLockGuides)
					lockGuides = ITriStateControlData::kUnknown;
			}

			name = "";

			if (color != Utils<IUIColorUtils>()->GetRGBColorValue(::GetDataBase(doc), docLayer->GetColorUID()))
				swatchColorUID = kMixedColorUID;

			if ( ignore != ITriStateControlData::kUnknown )
			{
				ITriStateControlData::TriState nextIgnore = docLayer->GetIgnoreTextWrapWhenNotVisible() ? ITriStateControlData::kSelected : ITriStateControlData::kUnselected;
				if ( nextIgnore != ignore )
					ignore = ITriStateControlData::kUnknown;
			}
		}
	}
	else	// New Layer dialog
	{
		ASSERT_MSG(fDialogType == LayerPanelUtils::kNewLayerDialog, "Unknown dialog type");
		InterfacePtr<ILayerList> layerList(doc, IID_ILAYERLIST);
		show = ITriStateControlData::kSelected;
		print = ITriStateControlData::kSelected;
		lock = ITriStateControlData::kUnselected;
		showGuides = ITriStateControlData::kSelected;
		lockGuides = ITriStateControlData::kUnselected;
		layerList->GenerateNewLayerName(&name);
		swatchColorUID = layerList->GetLeastUsedLayerColor();
	}
	
	// Set all the checkboxes
	SetTriStateControlData(kLayerShowCheckboxWidgetID, show);
	SetTriStateControlData(kLayerPrintCheckboxWidgetID, print);
	SetTriStateControlData(kLayerLockCheckboxWidgetID, lock);
	SetTriStateControlData(kLayerShowGuidesCheckboxWidgetID, showGuides);
	SetTriStateControlData(kLayerLockGuidesCheckboxWidgetID, lockGuides);
	SetTriStateControlData(kIgnoreTextWrapCheckboxWidgetID, ignore);

	IControlView* printCheckbox = panel->FindWidget(kLayerPrintCheckboxWidgetID);
	if (show == kFalse)
		printCheckbox->Disable();
	else
		printCheckbox->Enable();

	if (LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS))
	{
		// Set the layer name
		SetTextControlData(kUILayerNameStaticWidgetID, name);

		IControlView* colorWidgetView = panel ? panel->FindWidget(kUILayerColorWidgetID) : nil;
		
		InterfacePtr<IUIDData> colorUIDData(colorWidgetView, UseDefaultIID());
		
		if (colorUIDData)
		{
			colorUIDData->Set(doc->GetDocWorkSpace().GetDataBase(), swatchColorUID);
			int32 colorIndex = Utils<IUIColorUtils>()->GetUIColorIndex(swatchColorUID, doc);
			ASSERT(colorIndex != -1);
			
			SetTextControlData(kColorNameWidgetID, Utils<IUIColorUtils>()->GetUIColorName(colorIndex));
		}
		
		
	}
	else
	{
		// Set the layer name
		SetTextControlData(kLayerNameWidgetID, name);
		nameWidget->Enable(enableName);

		// Fill in color popup menu with the color names installed
		IControlView* panelControlView = panel ? panel->FindWidget(kLayerColorDropDownWidgetID) : nil;
		
		InterfacePtr<IColorListControlData> colorListControlData(panelControlView, IID_ICOLORLISTCONTROLDATA);
		
		if (colorListControlData)
			colorListControlData->Setup(doc->GetDocWorkSpace(), IID_IUICOLORLIST, IColorListControlData::kIncludeCustom, swatchColorUID);
	}

	if (nameWidget && nameWidget->IsEnabled()) SelectDialogWidget(kLayerNameWidgetID);
	else SelectDialogWidget(kOKButtonWidgetID);
}


// Validate the values in the edit boxes.
WidgetID LayerOptionsDlgController::ValidateDialogFields( IActiveContext* dlgContext)
{
	WidgetID badWidgetId = kDefaultWidgetId;

	// Get the name string out of the dialog and validate it.
	PMString newName(GetTextControlData(kLayerNameWidgetID));
	PMString errorString;
	badWidgetId = this->ValidateNameField(dlgContext, newName, errorString);

	if (badWidgetId != kDefaultWidgetId)
	{
		errorString.Translate();
		CAlert::ErrorAlert(errorString);
	}

	return badWidgetId;
}

// Returns kLayerNameWidgetID if the name field
// is bad and fill in the appropriate error string.
WidgetID LayerOptionsDlgController::ValidateNameField(IActiveContext* dlgContext, PMString& nameString, PMString& errorString)
{
	IDocument* doc = dlgContext->GetContextDocument();
	WidgetID badWidgetId = kDefaultWidgetId;
	PMString localString(nameString);
	localString.StripWhiteSpace(PMString::kLeadingAndTrailingWhiteSpace);

	IDocumentLayer* currentLayer = nil;
	if (fDialogType == LayerPanelUtils::kLayerOptionsDialog)
	{
		// Get the list of selected layers that we are operating on.
		InterfacePtr<IPMUnknownData> targetData(this, UseDefaultIID());
		UIDList targetUIDList(::GetDataBase(doc));
		LayerPanelUtils::GetTargetLayers(targetUIDList, targetData->GetPMUnknown());

		int32 numLayers = targetUIDList.Length();
		if (numLayers > 1)
			return badWidgetId;	// Nothing to validate, control is disabled.

		// Fill in current layer for check below, no need to validate name against itself when in Layer Options mode
		if (fDialogType == LayerPanelUtils::kLayerOptionsDialog)
		{
			IDataBase* db = targetUIDList.GetDataBase();
			currentLayer = (IDocumentLayer*) db->Instantiate(targetUIDList.GetRef(0).GetUID(), IID_IDOCUMENTLAYER);
		}
	}

	if(!LayerPanelUtils::ValidateNewLayerName(::GetDataBase(doc),currentLayer, localString, errorString))
	{
		badWidgetId = kLayerNameWidgetID;
		SetTextControlData(kLayerNameWidgetID, localString, nil, kTrue, kFalse);	// Invalidate but don't notify
	}

	if (currentLayer)
		currentLayer->Release();

	return badWidgetId;
}

void LayerOptionsDlgController::ApplyDialogFields( IActiveContext* dlgContext, const WidgetID& ) 
{
	IDocument* doc = dlgContext->GetContextDocument();
	if (doc)	
	{
		InterfacePtr<IPMUnknownData> targetData(this, UseDefaultIID());
		UIDList targetUIDList(::GetDataBase(doc));
		LayerPanelUtils::GetTargetLayers(targetUIDList, targetData->GetPMUnknown());

		ICommandSequence* cmdSeq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);

		int32 numLayers(0);
		ICommand *iNewLayerCmd = nil;
		InterfacePtr<IPanelControlData> layerPanelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kLayerParentWidgetId));
		switch (fDialogType)
		{
			case LayerPanelUtils::kLayerOptionsDialog:
				cmdSeq->SetName("Layer Options");
				numLayers = targetUIDList.Length();
				break;
			case LayerPanelUtils::kNewLayerDialog:
			{
				// Returns a pipeline command containing a new layer cmd,
				// active layer cmd, and a move layer cmd.
				cmdSeq->SetName("New Layer");
				numLayers = 1;

				InterfacePtr<IPMUnknownData> targetNewLayerData(this, IID_ITARGETNEWLAYER);
				InterfacePtr<IDocumentLayer> targetNewLayer(targetNewLayerData->GetPMUnknown(), UseDefaultIID());
				iNewLayerCmd = LayerPanelUtils::CreateNewLayerCommand(fLayerLocation, targetNewLayer);
				CmdUtils::ProcessCommand(iNewLayerCmd);
				break;
			}
			default:
				ASSERT_FAIL("Unknown dialog type");
		}

		IDocumentLayer* docLayer = nil;
		for (int32 i = 0; i < numLayers; i++)
		{
			// Layer Options
			if (fDialogType == LayerPanelUtils::kLayerOptionsDialog)
			{
				InterfacePtr<IDocumentLayer> aLayer(targetUIDList.GetRef(i), IID_IDOCUMENTLAYER);
				docLayer = aLayer;
				docLayer->AddRef();	// Extra Ref to keep this interface around
			}
			else
			{   // Newlayer command should store created layer list in ItemList. If we're duplicating, the layer facade call overwrites targetUIDList with the duplicated layers.
				const UIDList* uidList = &targetUIDList;
				if(iNewLayerCmd)
					uidList = iNewLayerCmd->GetItemList();
				InterfacePtr<IDocumentLayer> aLayer(uidList->GetRef(i), IID_IDOCUMENTLAYER);
				docLayer = aLayer;
				docLayer->AddRef();	// Extra Ref to keep this interface around
			}

			// Show/hide the layer
			ITriStateControlData::TriState show = GetTriStateControlData(kLayerShowCheckboxWidgetID);
			ICommand* showCmd = this->MakeBoolCommand(kShowLayerCmdBoss, docLayer, show);
			if (showCmd)
			{
				CmdUtils::ProcessCommand(showCmd);
				showCmd->Release();
			}

			// Print the layer
			ITriStateControlData::TriState print = GetTriStateControlData(kLayerPrintCheckboxWidgetID);
			ICommand* printCmd = this->MakeBoolCommand(kPrintLayerCmdBoss, docLayer, print);
			if (printCmd)
			{
				CmdUtils::ProcessCommand(printCmd);
				printCmd->Release();
			}

			// Lock/Unlock the layer
			ITriStateControlData::TriState lock = GetTriStateControlData(kLayerLockCheckboxWidgetID);
			ICommand* lockCmd = this->MakeBoolCommand(kLockLayerCmdBoss, docLayer, lock);
			if (lockCmd)
			{
				CmdUtils::ProcessCommand(lockCmd);
				lockCmd->Release();
			}

			// Show/hide guides on the layer
			ITriStateControlData::TriState showGuides = GetTriStateControlData(kLayerShowGuidesCheckboxWidgetID);
			ICommand* showGuidesCmd = this->MakeBoolCommand(kShowGuideLayerCmdBoss, docLayer, showGuides);
			if (showGuidesCmd)
			{
				CmdUtils::ProcessCommand(showGuidesCmd);
				showGuidesCmd->Release();
			}

			// Lock/Unlock guides on the layer
			ITriStateControlData::TriState lockGuides = GetTriStateControlData(kLayerLockGuidesCheckboxWidgetID);
			ICommand* lockGuidesCmd = this->MakeBoolCommand(kLockGuideLayerCmdBoss, docLayer, lockGuides);
			if (lockGuidesCmd)
			{
				CmdUtils::ProcessCommand(lockGuidesCmd);
				lockGuidesCmd->Release();
			}

			// Ignore Text Wrap when Layer is Hidden
			ITriStateControlData::TriState ignore = GetTriStateControlData(kIgnoreTextWrapCheckboxWidgetID);
			ICommand* ignoreCmd = this->MakeBoolCommand(kIgnoreHiddenTextWrapCmdBoss, docLayer, ignore);
			if (ignoreCmd)
			{
				CmdUtils::ProcessCommand(ignoreCmd);
				ignoreCmd->Release();
			}

			// Set name of the layer in New Layer mode or (Layer Options or Duplicate Layer) with 1 layer
			if (fDialogType == LayerPanelUtils::kNewLayerDialog || numLayers == 1)
			{
				ICommand* nameCmd = CmdUtils::CreateCommand(kChangeLayerNameCmdBoss);
				if (nameCmd)
				{
					if (docLayer)
						nameCmd->SetItemList(  UIDList(docLayer));
					InterfacePtr<IStringData> data(nameCmd, IID_ISTRINGDATA);
					PMString name(GetTextControlData(kLayerNameWidgetID));
					name.StripWhiteSpace(PMString::kLeadingAndTrailingWhiteSpace);
					data->Set(name);
					CmdUtils::ProcessCommand(nameCmd);
					nameCmd->Release();
				}
			}

			// Find the UID of the color that was chosen
			InterfacePtr<IPanelControlData> panelData(this, IID_IPANELCONTROLDATA);
			IControlView* panelControlView = panelData ? panelData->FindWidget(kLayerColorDropDownWidgetID) : nil;
			
			InterfacePtr<IColorListControlData> colorListControlData(panelControlView, IID_ICOLORLISTCONTROLDATA);
			
			if (colorListControlData && colorListControlData->IsSetup())
			{
				UIDRef uiColorRef(::GetDataBase(docLayer), colorListControlData->GetSelection());
				
				if (uiColorRef.GetUID() != kInvalidUID)
				{
					// use the color listed in the drop down list			
					// Make a command for changing the selected layer color
					ICommand* changeLayerColorCmd = CmdUtils::CreateCommand(kSetLayerColorCmdBoss);
					if (docLayer)
						changeLayerColorCmd->SetItemList(  UIDList(docLayer));
					
					InterfacePtr<IUIDData> iUIDData(changeLayerColorCmd, IID_IUIDDATA);
					//UIDRef uiColorRef = Utils<IUIColorUtils>()->GetUIColor(dropDownIndex, doc);
					iUIDData->Set(uiColorRef);
					if (changeLayerColorCmd)
					{
						CmdUtils::ProcessCommand(changeLayerColorCmd);
						changeLayerColorCmd->Release();
					}
				}
				//			}
			}

			// Release the extra ref to docLayer we have in Layer Options mode
			if (docLayer)
			{
				docLayer->Release();
				docLayer = nil;
			}
		}

		if (iNewLayerCmd)
			iNewLayerCmd->Release();
					
		CmdUtils::EndCommandSequence(cmdSeq);
	}
}

void LayerOptionsDlgController::ClosingDialog(IActiveContext* )
{
	// Clear out our reference to target layer from LayerPanelUtils::InvokeLayerDialog.
	InterfacePtr<IPMUnknownData> targetNewLayerData(this, IID_ITARGETNEWLAYER);
	targetNewLayerData->SetPMUnknown(nil);
}


// Helper function to make either a show, lock, or print command. layer may
// be nil in the New Layer dialog case when we are using a pipeline cmd.
ICommand* LayerOptionsDlgController::MakeBoolCommand(ClassID classID, IDocumentLayer* layer, ITriStateControlData::TriState value)
{
	ICommand* cmd = nil;
	bool16 cmdValue(kFalse);

	if (value != ITriStateControlData::kUnknown)
	{
		// Only create the command if the value has changed.
		cmdValue = (value == ITriStateControlData::kSelected);
		switch(classID.Get())
		{
			case kShowLayerCmdBoss:
			{
				if ((layer && cmdValue != layer->IsVisible()) || (!layer && !value))
					cmd = CmdUtils::CreateCommand(kShowLayerCmdBoss);
				break;
			}

			case kPrintLayerCmdBoss:
			{
				if ((layer && cmdValue != layer->IsPrintable()) || (!layer && !value))
					cmd = CmdUtils::CreateCommand(kPrintLayerCmdBoss);
				break;
			}

			case kLockLayerCmdBoss:
			{
				if ((layer && cmdValue != layer->IsLocked()) || (!layer && value))
					cmd = CmdUtils::CreateCommand(kLockLayerCmdBoss);
				break;
			}

			case kShowGuideLayerCmdBoss:
			{
				if ((layer && cmdValue != layer->IsGuideVisible()) || (!layer && !value))
					cmd = CmdUtils::CreateCommand(kShowGuideLayerCmdBoss);
				break;
			}

			case kLockGuideLayerCmdBoss:
			{
				if ((layer && cmdValue != layer->IsGuideLocked()) || (!layer && value))
					cmd = CmdUtils::CreateCommand(kLockGuideLayerCmdBoss);
				break;
			}

			case kIgnoreHiddenTextWrapCmdBoss:
			{
				//cmdValue = !cmdValue;
				if ((layer && cmdValue != layer->GetIgnoreTextWrapWhenNotVisible()) || (!layer && value))
					cmd = CmdUtils::CreateCommand(kIgnoreHiddenTextWrapCmdBoss);
				break;
			}
		}
	}

	if (cmd)
	{
		if (layer)
			cmd->SetItemList(  UIDList(layer));
		InterfacePtr<IBoolData> data(cmd, IID_IBOOLDATA);
		data->Set(cmdValue);
	}
	
	return cmd;
}
