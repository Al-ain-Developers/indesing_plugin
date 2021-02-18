//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/incopyexportui/InCopyExportMenuComponent.cpp $
//  
//  Owner: Ben Park
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

// ----- ID files -----
#include "ImportExportUIID.h"
#include "InCopyExportID.h"
#include "InCopyExportUIID.h"
#include "InCopyWorkflowID.h"

// ----- Interfaces -----
#include "IActionStateList.h"
#include "IBoolData.h"
#include "ICmdCollection.h"
#include "ICommand.h"
#include "IDocument.h"
#include "IExportProvider.h"
#include "ISaveFileDialog.h"
#include "ISelectionUtils.h"
#include "ISession.h"

// ----- Utility files -----
#include "CActionComponent.h"
#include "CmdUtils.h"
#include "FileUtils.h"
#include "InCopyImportExportDefs.h"
#include "ILayoutUIUtils.h"
#include "widgetid.h"

//========================================================================================
// CLASS InCopyExportMenuComponent
//========================================================================================

class InCopyExportMenuComponent : public CActionComponent
{
public:
		InCopyExportMenuComponent(IPMUnknown *boss);

	
		virtual void	DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);
		virtual void	UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget);
};

CREATE_PMINTERFACE(InCopyExportMenuComponent, kInCopyExportMenuComponentImpl)

//========================================================================================
// CLASS InCopyExportMenuComponent
//========================================================================================

InCopyExportMenuComponent::InCopyExportMenuComponent(IPMUnknown *boss) :
	CActionComponent(boss)
{
}

void	InCopyExportMenuComponent::UpdateActionStates(IActiveContext* ac, IActionStateList *listToUpdate, GSysPoint mousePoint, IPMUnknown* widget)
{
	const int32 nCount = listToUpdate->Length();
	
	for (int32 i = 0; i < nCount; i++)
	{
		ActionID nAction = listToUpdate->GetNthAction(i);
		PMIID	exporterIID;

		switch (nAction.Get())
		{
			// This should be active if there are any stories on the active layer.
			case kExportLayerToICActionID:
				exporterIID = IID_IINCOPYEXPORTLAYERSUITE;
				break;
			case kExportAllStoriesToICActionID:
				exporterIID = IID_IINCOPYEXPORTALLSTORIESSUITE;
				break;
			case kExportAllGraphicsToICActionID:
				exporterIID = IID_IINCOPYEXPORTALLGRAPHICSSUITE;
				break;
			case kExportAllItemsToICActionID:
				exporterIID = IID_IINCOPYEXPORTALLSUITE;
				break;
				
			default:
				ASSERT_FAIL("asked to update action I don't know about!");
				return;
		}

		// It's go time
		IDocument* currentDoc = Utils<ILayoutUIUtils>()->GetFrontDocument();
		ISelectionManager* selMgr = Utils<ISelectionUtils>()->GetActiveSelection();

		InterfacePtr<IExportProvider> exporter(this, exporterIID);
		ASSERT(exporter);

		// This should answer the question for us
		bool16 canExport = exporter->CanExportThisFormat(currentDoc, selMgr, InCopy::kInCopyInterchangeFormatName);
		if (!canExport)
			canExport = exporter->CanExportThisFormat(currentDoc, selMgr, InCopy::kInCopyMarkupFormatName);
		listToUpdate->SetNthActionState(i, canExport ? kEnabledAction : kDisabled_Unselected);
	}
}

void	InCopyExportMenuComponent::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
	PMIID	exporterIID;

	switch (actionID.Get())
	{
		// Well, here we are.  Now what?
		case kExportLayerToICActionID:
			exporterIID = IID_IINCOPYEXPORTLAYERSUITE;
			break;
		case kExportAllStoriesToICActionID:
			exporterIID = IID_IINCOPYEXPORTALLSTORIESSUITE;
			break;
		case kExportAllGraphicsToICActionID:
			exporterIID = IID_IINCOPYEXPORTALLGRAPHICSSUITE;
			break;
		case kExportAllItemsToICActionID:
			exporterIID = IID_IINCOPYEXPORTALLSUITE;
			break;
			
		default:
			ASSERT_FAIL("InCopyExportMenuComponent - unknown menu id");
			return;
	}

	InterfacePtr<IExportProvider> exporter (this, exporterIID);
	ASSERT(exporter);

	IDFile sysFile;
	IDFile defaultFile;
	PMString baseFileName;

	// Get the Doc name to use as a base
	IDocument* frontDoc = Utils<ILayoutUIUtils>()->GetFrontDocument();	
	frontDoc->GetName(baseFileName);

	PMString icDocumentFormatName("InCopyMarkup");
	//PMString icInterchangeFormatName("InCopyInterchange");
	PMString icDocumentFileExtension (exporter->GetExtensionForFormatName(icDocumentFormatName));
	//PMString icInterchangeFileExtension (exporter->GetExtensionForFormatName(icInterchangeFormatName));
	icDocumentFormatName.Translate();
	//icInterchangeFormatName.Translate();

	ISelectionManager* selMgr = Utils<ISelectionUtils>()->GetActiveSelection();

	// Let's start off with getting a filename from the user via a dialog
	bool16 bUseSystemDefaultDir = kTrue;
	FileUtils::PMStringToIDFile(baseFileName, defaultFile);

	// Create the export Dialog
	InterfacePtr<ISaveFileDialog> exportDialog((ISaveFileDialog *)CreateObject(kExportDialogBoss, IID_ISAVEFILEDIALOG));
	ASSERT_MSG(exportDialog != nil, "Cannot create export dialog!");
    InterfacePtr<IBoolData> showRetainFilenameCheckbox(exportDialog, UseDefaultIID());
    showRetainFilenameCheckbox->Set(false);
    
	// Add the File Type to it
	exportDialog->AddFileTypeInfo(icDocumentFormatName, icDocumentFileExtension);
	//exportDialog->AddFileTypeInfo(icInterchangeFormatName, 0, 0, icInterchangeFileExtension);

	// Activate the dialog
	int32 formatIndex = 0;
	if (exportDialog->DoDialog(&defaultFile, &sysFile, &formatIndex, bUseSystemDefaultDir))	// use system default folder
	{
		// sysFile should be our destination at this point.
		const PMString formatName = formatIndex == 0 ? InCopy::kInCopyMarkupFormatName : InCopy::kInCopyInterchangeFormatName;
		exporter->ExportToFile(sysFile, frontDoc, selMgr, formatName, kFullUI);
	}
}
