//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpProcessDocumentLayerCmds.cpp $
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

#include "ICommandSequence.h"
#include "IDocument.h"
#include "IDocumentLayer.h"
#include "INewLayerCmdData.h"
#include "ICopyCmdData.h"
#include "ILayoutControlData.h"
#include "IScrapSuite.h"
#include "IClipboardController.h"
#include "ILayoutCmdData.h"
#include "IControlView.h"
#include "ILayerPrefs.h"
#include "ILayerPrefsCmdData.h"
#include "ISelectionUtils.h"
#include "IUIDData.h"
#include "IActiveContext.h"
#include "IStringData.h"
#include <ILayerList.h>
#include "ILayerSuite.h"
#include "ISpreadLayer.h"
#include "ISpread.h"
#include "IGuideDataSuite.h"
#include "IHierarchy.h"
// General includes:
#include "CmdUtils.h"
#include "ILayerUtils.h"
#include "PreferenceUtils.h"
#include "Utils.h"
#include "ErrorUtils.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

#include "ISpreadList.h"
#include "IPageItemVisibilityFacade.h"
#include "IPageItemNameFacade.h"
/** 
	\li how to write code that processes document layer commands and sequence of commands.

   	@ingroup sdk_snippet
	@ingroup sdk_layout
 */
class SnpProcessDocumentLayerCmds
{
	public:
		/** Constructor.
		 */
		SnpProcessDocumentLayerCmds() {}

		/** Destructor.
		 */
		virtual			~SnpProcessDocumentLayerCmds() {}

		/** 
			@param doc IN the document
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode CreateNewLayer(IDocument* doc);

		/**
			@param doc IN the document
			@param view IN the control view
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode CopyToNewLayer(IDocument* doc, IControlView* view);

		/** 
			Invokes NewLayerCmd to create a new command followed by
			SetActiveLayerCmd to make the new layer active. 
			
			@param doc IN the document
			@param view IN the control view
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode CreateActiveLayer(IDocument* doc, IControlView* view);

		/** 
			Copy/Paste the current selection into the current layer via
			the IScrapSuite and the clipboard.
  
			@param view IN the control view
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode CopySelectedItems(IControlView* view);

		/** 
			Invokes SetLayerPrefsCmd to set layer preferences
			@param pasteRemembersLayers IN whether or not to set PasteRemembersLayers preference
			@return  kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode SetLayerPrefs(bool16 pasteRemembersLayers);

		/**
			Queries the layer preferences to find if the preference
			PasteRemembersLayers is set.
  
			@return   kTrue PasteRemembersLayers is On, kFalse PasteRemembersLayers is Off.

		*/
		bool16 GetPasteRemembersLayers();

		
		/** 
		 select all page items on active layer
		 @param doc IN the current document
		 @param view IN the control view to use
		 @return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode SelectAllItemsOnActiveLayer(IDocument* doc, IControlView* view);

		/** 
			change the current selected item name if it is not assigned by user
			@param selectedItemRef IN the current selected item
			@param itemName IN the new pageitem name
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode ChangeItemName(UIDRef selectedItemRef,PMString itemName);

		/** 
			hide the current selected item
			@param selectedItemRef IN the current selected item
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode ShowHidePageItem(UIDRef selectedItemRef);

};

/*
*/
ErrorCode SnpProcessDocumentLayerCmds::CreateNewLayer(IDocument* doc)
{
	ErrorCode error = kFailure;
	if (doc == nil)
	{
		ASSERT_FAIL("The document is nil.");
		return error;
	}

	do
	{
		// Create the NewLayerCmd:
		InterfacePtr<ICommand> layerCmd(CmdUtils::CreateCommand(kNewLayerCmdBoss));

		// Set NewLayerCmd arguments:
		InterfacePtr<INewLayerCmdData> layerData(layerCmd, IID_INEWLAYERCMDDATA);
		if (layerData == nil)
		{
			ASSERT_FAIL("layerData is nil");
			break;
		}

		layerData->Set
		(
			GetUIDRef(doc),	// const UIDRef& layerList
			nil,							// const PMString *name = nil
			kTrue,							// bool16 isVisible = kTrue, 
			kFalse,							// bool16 isLocked = kFalse, 
			kFalse,							// bool16 isGuideVisible = kTrue, 
			kFalse,							// bool16 isGuideLocked = kFalse, 
			kInvalidUID,					// UID layerColor = kInvalidUID, 
			kTrue,							// bool16 isUILayer = kTrue,
			kTrue							// bool16 isExpendable = kTrue;
		);		
		layerData->SetPrintable(kTrue);		// bool16 isPrintable = kTrue
		layerData->SetIgnoreTextWrapWhenNotVisible(kFalse);		// bool16 bIgnoreWhenNotVisible = kFalse
		        
		// Specify that the new layer goes just above the active layer, CS5 change instead of always creating at top of list.
		InterfacePtr<IDocumentLayer> activeLayer(Utils<ILayerUtils>()->QueryDocumentActiveLayer(doc));
		InterfacePtr<IUIDData> uidLayerData(layerCmd, UseDefaultIID());
		uidLayerData->Set(activeLayer);

		// Process the command:
		error = CmdUtils::ProcessCommand(layerCmd);
		
	} while (false); 
	
	return error;
}

/*
*/
ErrorCode SnpProcessDocumentLayerCmds::CopyToNewLayer(IDocument* doc, IControlView* view)
{
	ErrorCode error = kFailure;
	if (doc == nil || view == nil)
	{
		ASSERT_FAIL("The document or the control view is nil.");
		return error;
	}

	// Begin the sequence:
	ICommandSequence* sequ = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);

	do
	{
		if (sequ == nil)
		{
			ASSERT_FAIL("Could not create command sequence");
			break;
		}

		// Name the command sequence:
		PMString sequName = PMString("SnpProcessDocumentLayerCmds sequence");
		sequName.SetTranslatable(kFalse);
		sequ->SetName(sequName);

		// Get the PasteRemembersLayers preference:
		bool16 pasteRemembersLayers = kFalse;
		pasteRemembersLayers = GetPasteRemembersLayers();

		// Clear the PasteRemembersLayers preference.
		// Otherwise we won't paste into to our new layer:
		if (pasteRemembersLayers != kFalse)
		{
			error = SetLayerPrefs(kFalse);
			if (error != kSuccess)
				break;
		}
		
		// Create a new layer & make it active:
		error = CreateActiveLayer(doc, view);
		if (error != kSuccess)
		{
			break;
		}
		
		// Copy the current selection into the new layer:
		error = CopySelectedItems(view);
		if (error != kSuccess)
		{
			break;
		}

		// Reset PasteRemembersLayers preference
		// to it's value when we were called:
		if (pasteRemembersLayers != kFalse)
		{
			error = SetLayerPrefs(kTrue);
		}
	
	} while (false); 
	
	if (error == kSuccess)
	{
		// no error, end the command sequence
		CmdUtils::EndCommandSequence(sequ);
	}
	else
	{
		// there is an error, abort the command sequence
		ErrorUtils::PMSetGlobalErrorCode(error);
		CmdUtils::EndCommandSequence(sequ);	
	}

	return error;
}

/* CreateActiveLayer
*/
ErrorCode SnpProcessDocumentLayerCmds::CreateActiveLayer(IDocument* doc, IControlView* view)
{
	ErrorCode status = kFailure;

	if (doc == nil || view == nil)
	{
		ASSERT_FAIL("The document or the control view is nil.");
		return status;
	}
	
	do
	{
		// Create a new layer:
	    InterfacePtr<ICommand> newLayerCmd(CmdUtils::CreateCommand(kNewLayerCmdBoss));
		if (newLayerCmd == nil)
		{
			ASSERT_FAIL("could not create newLayerCmd");
			break;
		}
		
		InterfacePtr<INewLayerCmdData> newLayerData(newLayerCmd, IID_INEWLAYERCMDDATA);
		
		if (newLayerData == nil)
		{
			ASSERT_FAIL("newLayerData invalid");
			break;
		}

		newLayerData->Set(GetUIDRef(doc));	
		status = CmdUtils::ProcessCommand(newLayerCmd);

		if (status != kSuccess)
		{
			ASSERT_FAIL("newLayerCmd failed");
			break;
		}
		
		// newLayerCmd returns the UID of the newly created layer
		// in it's item list. Make a copy of this list to pass into
		// setActiveLayerCmd:
		UIDList newLayerUIDList = UIDList(*newLayerCmd->GetItemList());
		
		// Make the new layer the active layer:
		InterfacePtr<ICommand> setActiveLayerCmd(CmdUtils::CreateCommand(kSetActiveLayerCmdBoss));
		if (setActiveLayerCmd == nil)
		{
			ASSERT_FAIL("could not create setActiveLayerCmd");
			break;
		}
		
		setActiveLayerCmd->SetItemList(newLayerUIDList);

		InterfacePtr<ILayoutCmdData> setActiveLayerCmdData(setActiveLayerCmd, UseDefaultIID());
		if (setActiveLayerCmd == nil)
		{
			ASSERT_FAIL("setActiveLayerCmdData invalid");
			break;
		}

		InterfacePtr<ILayoutControlData> layoutControlData(view, UseDefaultIID());
		setActiveLayerCmdData->Set(::GetUIDRef(doc), layoutControlData);

		status = CmdUtils::ProcessCommand(setActiveLayerCmd);
		
	} while (false); 

	return status;
}


/*
*/
ErrorCode SnpProcessDocumentLayerCmds::CopySelectedItems(IControlView* view)
{
	ErrorCode status = kFailure;
	if (view == nil)
	{
		ASSERT_FAIL("The control view is nil.");
		return status;
	}
	
	do
	{
		// Acquire the interfaces we need to use IScrapSuite:
		InterfacePtr<IScrapSuite> scrapSuite(static_cast<IScrapSuite*>(Utils<ISelectionUtils>()->QuerySuite(IID_ISCRAPSUITE)));
		if (scrapSuite == nil)
		{
			ASSERT_FAIL("scrapSuite invalid");
			break;
		}
		InterfacePtr<IClipboardController> clipController(GetExecutionContextSession(), UseDefaultIID());
		if (clipController == nil)
		{
			ASSERT_FAIL("clipController invalid");
			break;
		}

		// Copy and paste the selection:
		if (scrapSuite->CanCopy(clipController) != kTrue)
			break;
		if (scrapSuite->Copy(clipController) != kSuccess)
			break;
		if (scrapSuite->CanPaste(clipController) != kTrue)
			break;
		if (scrapSuite->Paste(clipController, view) != kSuccess)
			break;

		status = kSuccess;

	} while (false); 

	return status;
}

/*
*/
ErrorCode SnpProcessDocumentLayerCmds::SetLayerPrefs(bool16 pasteRemembersLayers)
{
	ErrorCode error = kFailure;

	InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSetLayerPrefsCmdBoss));
	InterfacePtr<ILayerPrefsCmdData> data(cmd, IID_ILAYERPREFSCMDDATA);
	if (data == nil)
	{
		ASSERT_FAIL("SnpProcessDocumentLayerCmds: layerPrefsCmdData invalid");
	}
	else
	{
		data->Set(pasteRemembersLayers);
		
		error = CmdUtils::ProcessCommand(cmd);
	}	
	return error;
}

/*
*/
bool16 SnpProcessDocumentLayerCmds::GetPasteRemembersLayers()
{
	bool16 pasteRemembersLayers = kFalse;
	
	InterfacePtr<ILayerPrefs> layerPrefs((ILayerPrefs*)::QuerySessionPreferences(IID_ILAYERPREFERENCES));

	if (layerPrefs != nil)
	{
		pasteRemembersLayers = layerPrefs->GetPasteRemembersLayers();
	}
	
	return pasteRemembersLayers;
}

/*
*/
ErrorCode SnpProcessDocumentLayerCmds::SelectAllItemsOnActiveLayer(IDocument* doc, IControlView* view)
{
	InterfacePtr<ISelectionManager> selectionMgr(Utils<ISelectionUtils>()->QueryActiveSelection());
	InterfacePtr<ILayerSuite> iLayerSuite (selectionMgr, UseDefaultIID());
	InterfacePtr<ILayoutControlData> layoutData(view, UseDefaultIID());

	InterfacePtr<IDocumentLayer> activeLayer(Utils<ILayerUtils>()->QueryDocumentActiveLayer(doc));

	if(iLayerSuite && layoutData)
	{
		InterfacePtr<ISpread> spread(layoutData->GetSpreadRef(), UseDefaultIID());
		InterfacePtr<ISpreadLayer> spreadLayer(spread->QueryLayer(activeLayer, nil, kFalse));
		InterfacePtr<IHierarchy> layerHierarchy(spreadLayer, UseDefaultIID());
	
		// If layer has no regular page item content, then try guide layer.
		// Also, if guides are selected, favor selecting guides.
		InterfacePtr<IGuideDataSuite> iGuideSuite(selectionMgr, UseDefaultIID());		

		bool16 bGuidesSelected = iGuideSuite && iGuideSuite->AreGuidesSelected();

		bool16 bGuideLayerOnly = kFalse;
		if (layerHierarchy && !layerHierarchy->GetChildCount())
		{
			bGuideLayerOnly = kTrue;
		}

		if(!iLayerSuite->AreAllItemsOnLayerSelected((IDocumentLayer*)activeLayer, view, bGuideLayerOnly || bGuidesSelected))
		{
			iLayerSuite->SelectAllItemsOnLayer((IDocumentLayer*)activeLayer, view, bGuideLayerOnly || bGuidesSelected, Selection::kAddTo );
		}
	}
	return kSuccess;
}

/*
*/
ErrorCode SnpProcessDocumentLayerCmds::ChangeItemName(UIDRef selectedItemRef,PMString layerName)
{
	ErrorCode error = kFailure;
	PMString itemName;
	itemName.SetString(Utils<Facade::IPageItemNameFacade>()->GetUserAssignedPageItemName(selectedItemRef));
	if(itemName.IsEmpty())
	{
		itemName.SetString(Utils<Facade::IPageItemNameFacade>()->GetDefaultPageItemName(selectedItemRef));
		error = Utils<Facade::IPageItemNameFacade>()->SetUserAssignedPageItemName(selectedItemRef,layerName);
	}
	return error;
}

/*
*/
ErrorCode SnpProcessDocumentLayerCmds::ShowHidePageItem(UIDRef selectedItemRef)
{
	ErrorCode error = kFailure;
	//bool actuallyVisible = !Utils<Facade::IPageItemVisibilityFacade>()->IsHidden(selectedItemRef) && IsOnVisibleLayer(piHier);
	if(Utils<Facade::IPageItemVisibilityFacade>()->CanHide(selectedItemRef))
	{
		bool16 hidden = !Utils<Facade::IPageItemVisibilityFacade>()->GetVisibleState(selectedItemRef);
		if(hidden)
			error = Utils<Facade::IPageItemVisibilityFacade>()->Show(selectedItemRef);
		else
			error = Utils<Facade::IPageItemVisibilityFacade>()->Hide(selectedItemRef);
	}
	return error;
}


// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

class _SnpRunnerProcessDocumentLayerCmds : public SnpRunnable
{
	

	public:
		// SnippetRunner framework hooks.

		/** Constructor.
		 */
		_SnpRunnerProcessDocumentLayerCmds();

		/** Destructor.
		 */
		virtual			~_SnpRunnerProcessDocumentLayerCmds();

		/** Return kTrue if the snippet can run.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kTrue if snippet can run, kFalse otherwise
		 */
		bool16			CanRun(ISnpRunnableContext* runnableContext);

		/** Run the snippet.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode		Run(ISnpRunnableContext* runnableContext);
		
		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunFrontDocContext;}
};

/* Constructor.
*/
_SnpRunnerProcessDocumentLayerCmds::_SnpRunnerProcessDocumentLayerCmds() : SnpRunnable("ProcessDocumentLayerCmds")
{
	this->SetDescription("Process creating a new document layer or copy selected items to a new document layer command sequence for the front most opened document");
	this->SetPreconditions("document open");
	this->SetCategories("sdk_snippet, sdk_layout");
}

/* Destructor.
*/
_SnpRunnerProcessDocumentLayerCmds::~_SnpRunnerProcessDocumentLayerCmds()
{
}

/* 
*/
bool16	_SnpRunnerProcessDocumentLayerCmds::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do {
		//If there is a front document, we can run this snippet.
		InterfacePtr<IDocument> doc(runnableContext->GetActiveContext()->GetContextDocument(), UseDefaultIID());
		if (doc != nil) {
			result = kTrue;
		}
	} while(false);
	return result;
}

/* 
*/
ErrorCode _SnpRunnerProcessDocumentLayerCmds::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do {
		SnpProcessDocumentLayerCmds instance;
		// Use runnableContext to discover the selection target or IActiveContext.

		// Use IParameterUtils to prompt for parameters to set up your call(if any).
		// Utils<ISnipRunParameterUtils> parameterUtils;

		// Perform your operation.

		InterfacePtr<IDocument> doc(runnableContext->GetActiveContext()->GetContextDocument(), UseDefaultIID());
		if (doc == nil) {
			SNIPLOG("Please open a document and try again.");
			break;
		}

		// Ask which kind of frame is wanted.
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		choices.push_back(PMString("Create a new layer"));
		choices.push_back(PMString("Copy selected items on the current layer to a new layer"));
		choices.push_back(PMString("Select all page items"));
		choices.push_back(PMString("Change Item name"));
		choices.push_back(PMString("Hide Item"));
		enum {kNewLayer, kCopyToNewLayer,kSelectItems,kChangeItemName,kHideItem};
		int32 choice  = parameterUtils->GetChoice("Choose process option?", choices);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		IActiveContext* ac = runnableContext-> GetActiveContext();
		ASSERT(ac); // this should not happen if you already have a front doc open

		switch (choice) 
		{
		case kNewLayer:
			{
				status = instance.CreateNewLayer(ac->GetContextDocument());
				break;
			}
		case kCopyToNewLayer:
			{
				status = instance.CopyToNewLayer(ac->GetContextDocument(), ac->GetContextView());
				break;
			}
		case kSelectItems:
			{
				status = instance.SelectAllItemsOnActiveLayer(ac->GetContextDocument(), ac->GetContextView());
				break;
			}
		case kChangeItemName:
			{
				InterfacePtr<ILayoutTarget> layoutTarget(runnableContext, UseDefaultIID());
				if (layoutTarget) 
				{
					UIDList itemList = layoutTarget->GetUIDList(kStripStandoffs);
					if (itemList.Length() != 1)
						break;
					UIDRef selectedItemRef = UIDRef::gNull;
					selectedItemRef = itemList.GetRef(0);
					PMString itemName = parameterUtils->GetPMString("Specify the name of the new named pageItem.", "MyNamedItem"); 
					if (parameterUtils->WasDialogCancelled()) 
					{
						break;
					}
					status = instance.ChangeItemName(selectedItemRef,itemName);
				}
				break;
			}
		case kHideItem:
			{
				InterfacePtr<ILayoutTarget> layoutTarget(runnableContext, UseDefaultIID());
				if (layoutTarget) 
				{
					UIDList itemList = layoutTarget->GetUIDList(kStripStandoffs);
					if (itemList.Length() != 1)
						break;
					UIDRef selectedItemRef = UIDRef::gNull;
					selectedItemRef = itemList.GetRef(0);
					status = instance.ShowHidePageItem(selectedItemRef);
				}
				break;
			}
		default:
			{
				break;
			}
		}
	} while(false);

	return status;
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerProcessDocumentLayerCmds instance_SnpRunnerProcessDocumentLayerCmds;
DEFINE_SNIPPET(_SnpRunnerProcessDocumentLayerCmds) 	

// End, SnpProcessDocumentLayerCmds.cpp