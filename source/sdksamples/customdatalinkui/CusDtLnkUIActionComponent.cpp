//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalinkui/CusDtLnkUIActionComponent.cpp $
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
#include "IActionStateList.h"
#include "IActiveContext.h"
#include "IDialog.h"
#include "IDocument.h"
#include "IPanelControlData.h"
#include "ICusDtLnkFacade.h"
#include "ITreeViewMgr.h"
#include "IControlView.h"
#include "ICusDtLnkUITreeDataModel.h"
#include "IApplication.h"
#include "IIntData.h"
#include "IUIDData.h"
#include "IDialogMgr.h"
#include "ILinkFacade.h"
#include "IWindow.h"
#include "LinksUIID.h"
#include "UIDList.h"
#include "ILinksUIUtils.h"
#include "ILink.h"
#include "ILinkResource.h"
#include "PMLocaleId.h"
#include "LocaleSetting.h"
#include "RsrcSpec.h"
#include "CoreResTypes.h"
#include "CActionComponent.h"
#include "CAlert.h"
#include "IPalettePanelUtils.h"
#include "SDKFileHelper.h"
#include "CusDtLnkUIID.h"

// Performs actions when the plug-in's menu items are selected.
class CusDtLnkUIActionComponent : public CActionComponent
{
public:
	/**
	Constructor.
	@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	CusDtLnkUIActionComponent(IPMUnknown* boss);

	/** The action component should perform the requested action.
		This is where the menu item's action is taken.
		When a menu item is selected, the Menu Manager determines
		which plug-in is responsible for it, and calls its DoAction
		with the ID for the menu item chosen.

		@see IActionComponent::DoAction
		@param actionID identifies the menu item that was selected.
		@param ac active context
		@param mousePoint contains the global mouse location at time of event causing action (e.g. context menus). kInvalidMousePoint if not relevant.
		@param widget contains the widget that invoked this action. May be nil. 
		*/
	virtual void DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);

	/** Called when the action component is asked to update a list of actions to the proper state.
		This method is required to be overridden by subclasses only if there are action components with 
		kCustomEnabling specified.

		The list of actions is intially disabled and unselected, so it only has to be
		changed if this state is not correct. Note that action components are never asked to update
		actions that don't belong to them, or actions they have not specified kCustomEnabling for.
		
		@see CActionComponent::UpdateActionStates
	*/
	virtual void UpdateActionStates(IActiveContext* ac, IActionStateList* listToUpdate, GSysPoint mousePoint = kInvalidMousePoint, IPMUnknown* widget = nil);

private:
	void DoAbout();	
	void DoSyncView(IActiveContext* ac);
	void DoAddNewDB(IActiveContext* ac);
	void DoPlaceFromCSV(IActiveContext* ac, int32 whichDialog, const UIDRef& selectedLink);
    UIDList GetLinksForMenuAction(IPMUnknown* widget) const;
	IControlView* GetWidgetOnPanel(const WidgetID& panelWidgetID, const WidgetID& widgetID);
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(CusDtLnkUIActionComponent, kCusDtLnkUIActionComponentImpl)

CusDtLnkUIActionComponent::CusDtLnkUIActionComponent(IPMUnknown* boss)
: CActionComponent(boss)
{
}

void CusDtLnkUIActionComponent::UpdateActionStates(IActiveContext* ac, IActionStateList* listToUpdate, GSysPoint mousePoint, IPMUnknown* widget)
{
	do
	{
		const int32 nCount = listToUpdate->Length();

		for (int32 i = 0; i < nCount; i++)
		{
			ActionID nAction = listToUpdate->GetNthAction(i);

			switch (nAction.Get())
			{
				case kCusDtLnkUIRelinkActionID:
				{
					UIDList targetLinks = GetLinksForMenuAction(widget);
                    for(int linkIndex = targetLinks.Length() - 1; linkIndex >= 0; --linkIndex)
                    {
                        if (Utils<Facade::ILinkFacade>()->CanRelinkLink(targetLinks.GetRef(linkIndex)))
                        {
                            listToUpdate->SetNthActionState(i,kEnabledAction);
                            break;
                        }
                    }
				}
				break;
				default:
				break;
			}
		}
  	} while (kFalse);
}

/*
 * Switches on ActionID of menu item which called this function and takes appropriate action.
 */
void CusDtLnkUIActionComponent::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
	switch (actionID.Get())
	{
		case kCusDtLnkUIPopupAboutThisActionID:
		case kCusDtLnkUIAboutActionID:
		{
			this->DoAbout();
			break;
		}
					
		
		case kCusDtLnkUISyncViewActionID:
		{
			this->DoSyncView(ac);
			break;
		}

		case kCusDtLnkUIAddNewDBActionID:
		{
			this->DoAddNewDB(ac);
			break;
		}

		case kCusDtLnkUIPlaceFromCSVActionID:
		{
			UIDRef bogusRef = kInvalidUIDRef;
			this->DoPlaceFromCSV(ac, kPlaceDialog, bogusRef);
			break;
		}
		
		case kCusDtLnkUIRelinkActionID:
		{
			UIDList targetLinks = GetLinksForMenuAction(widget);
			for (int32 i=0; i<targetLinks.Length(); i++)
				this->DoPlaceFromCSV(ac, kRelinkDialog, targetLinks.GetRef(i));
			break;
		}
		
		default:
		{
			break;
		}
	}
}

/* 
 * Shows an about dialog.
 */
void CusDtLnkUIActionComponent::DoAbout()
{
	CAlert::ModalAlert
	(
		kCusDtLnkUIAboutBoxStringKey,				// Alert string
		kOKString, 						// OK button
		kNullString, 						// No second button
		kNullString, 						// No third button
		1,							// Set OK button to default
		CAlert::eInformationIcon				// Information icon.
	);
}

void CusDtLnkUIActionComponent::DoSyncView(IActiveContext* ac)
{
	do
	{
		IControlView* treeWidget = this->GetWidgetOnPanel(kCusDtLnkUIPalettePanelWidgetID, kCusDtLnkUITreeViewWidgetID);
		ASSERT(treeWidget);
		if(!treeWidget)
		{
			break;
		}

		InterfacePtr<ITreeViewMgr> iTreeViewMgr(treeWidget, UseDefaultIID());
		ASSERT(iTreeViewMgr);
		if(!iTreeViewMgr) 
		{
			break;
		}

		InterfacePtr<ICusDtLnkUITreeDataModel> model(treeWidget, UseDefaultIID());
		ASSERT(model);
		IWorkspace *ws = ac->GetContextWorkspace();
		model->Rebuild(ws);

		iTreeViewMgr->ClearTree();
		iTreeViewMgr->ChangeRoot(kTrue);
		
	} while(kFalse);

}

/*
 * Displays a browse for file dialog (uses SDKFileOpenChooser helper).
 */
void CusDtLnkUIActionComponent::DoAddNewDB(IActiveContext* ac)
{
	do
	{
		Utils<ICusDtLnkFacade> facade;
		ASSERT(facade);
		if (!facade) 
		{
			break;
		}

		SDKFileOpenChooser fileChooser;
		fileChooser.SetTitle(kCusDtLnkUIChooseFileStringKey);
		fileChooser.AddFilter(kCSVFileTypeInfoID, kCusDtLnkUIAliasDBFilterStringKey);
		fileChooser.AddAllFiles();
		fileChooser.ShowDialog();
		if (!fileChooser.IsChosen()) 
		{
			break;
		}

		PMString path = fileChooser.GetPath();
		path.SetTranslatable(kFalse);
		IDFile idFile = fileChooser.GetIDFile();
		PMString dbName = idFile.GetFileName();
		IWorkspace *ws = ac->GetContextWorkspace();
		ErrorCode err = facade->AddAssetDataBase(ws, dbName,path);
		ASSERT(err == kSuccess);
		
	} while(kFalse);
}

IControlView* CusDtLnkUIActionComponent::GetWidgetOnPanel(
	const WidgetID& panelWidgetID, const WidgetID& widgetID)
{
	IControlView* controlView=nil;
	do
	{
		// TODO Maybe fix to query up hierarchy so we can re-use treewidget on dialg (say)
		// if looking for treewidget at least
		InterfacePtr<IPanelControlData> 
			panelData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(panelWidgetID));	
		// Don't assert, fail silently, the tree view panel may be closed.
		if(panelData == nil) {
			break;
		}
		controlView = panelData->FindWidget(widgetID);
		ASSERT(controlView);
		if(controlView == nil) {
			break;
		}
	} while(0);
	
	return controlView;
}

/*
 * Displays the 'Place From CSV...' dialog which is defined in CusDtLnkUI.fr
 */
void CusDtLnkUIActionComponent::DoPlaceFromCSV(IActiveContext* ac, int32 whichDialog, const UIDRef& selectedLink)
{
	do
	{
		// Get the application interface and the DialogMgr.	
		InterfacePtr<IApplication> application(GetExecutionContextSession()->QueryApplication());
		if (application == nil)
		{
			ASSERT_FAIL("CusDtLnkUIActionComponent::DoDialog: application invalid"); 
			break;
		}
		InterfacePtr<IDialogMgr> dialogMgr(application, UseDefaultIID());
		if (dialogMgr == nil)
		{ 
			ASSERT_FAIL("CusDtLnkUIActionComponent::DoDialog: dialogMgr invalid"); 
			break;
		}

		// Load the plug-in's resource.
		PMLocaleId nLocale = LocaleSetting::GetLocale();
		RsrcSpec dialogSpec
		(
			nLocale,					// Locale index from PMLocaleIDs.h. 
			kCusDtLnkUIPluginID,			// Our Plug-in ID from BasicDialogID.h. 
			kViewRsrcType,				// This is the kViewRsrcType.
			kCusDtLnkUIBrowsDialogResourceID,	// Resource ID for our dialog.
			kTrue						// Initially visible.
		);

		// CreateNewDialog takes the dialogSpec created above, and also
		// the type of dialog being created (kMovableModal).
		IDialog* dialog = dialogMgr->CreateNewDialog(dialogSpec, IDialog::kMovableModal);
		if (dialog == nil)
		{ 
			ASSERT_FAIL("CusDtLnkUIActionComponent::DoDialog: can't create dialog"); 
			break;
		}
		// flag the dialog boss's IIntData to indicate the purpose of the dialog, for place or relink
		InterfacePtr<IIntData> intData(dialog->GetDialogPanel(), IID_IINTDATA);
		intData->Set(whichDialog);
		InterfacePtr<IUIDData> savedLink(intData, IID_IUIDDATA);
		InterfacePtr<IWindow> iWindow(dialog, UseDefaultIID());
		if (iWindow == nil)
		{
			ASSERT_FAIL("Dialog window does not exist!");
			break;
		}
		if (whichDialog == kRelinkDialog)
		{
			savedLink->Set(selectedLink);
			InterfacePtr<const ILink> oneLink(selectedLink, UseDefaultIID());
			InterfacePtr<const ILinkResource> linkResource(selectedLink.GetDataBase(),oneLink->GetResource(),UseDefaultIID());
			PMString title("Relink ");
			PMString path(linkResource->GetLongName(true));
			PMString relinkTitle = title + path;
			relinkTitle.SetTranslatable(false);
			iWindow->SetTitle(relinkTitle);
		}
		// Open the dialog.
		dialog->Open(); 
	} while(kFalse);

}

UIDList CusDtLnkUIActionComponent::GetLinksForMenuAction(IPMUnknown* widget) const
{
    InterfacePtr<const ILink> theLink(Utils<ILinksUIUtils>()->QueryLinkFromLinksUIWidget(widget));
    if(!theLink)
    {
        return Utils<ILinksUIUtils>()->GetLinksSelectedInPanel();
    }
    return UIDList(::GetUIDRef(theLink));
}