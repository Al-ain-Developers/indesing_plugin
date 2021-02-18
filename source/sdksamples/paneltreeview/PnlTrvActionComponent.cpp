//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/paneltreeview/PnlTrvActionComponent.cpp $
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
#include "IPnlTrvOptions.h"
#include "IWorkspace.h"
#include "IPnlTrvChangeOptionsCmdData.h"
#include "ITreeViewMgr.h"
#include "IControlView.h"
#include "IPnlTrvDataModel.h"
// General includes:
#include "CActionComponent.h"
#include "PnlTrvUtils.h"
#include "UIDList.h"
#include "CmdUtils.h"
#include "CAlert.h"

// Project includes:
#include "PnlTrvID.h"
#include "PnlTrvUtils.h"
#include "SDKFileHelper.h"


/** Implements the actions that are executed when the plug-in's menu items are selected.

	Implements IActionComponent based on the partial implementation CActionComponent.

	
	@ingroup paneltreeview
*/

class PnlTrvActionComponent : public CActionComponent
{
public:
	/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	PnlTrvActionComponent(IPMUnknown* boss);

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
	virtual void DoAction(
		IActiveContext* ac, 
		ActionID actionID, 
		GSysPoint mousePoint, 
		IPMUnknown* widget);

private:
	/** Encapsulates functionality for the about menu item. */
	void handleAbout();

	/** Encapsulates functionality for the Refresh menu item. */
	void handleRefresh();

	/** Encapsulates functionality for the SetOptions menu item. */
	void handleSetOptions();

	/**	Exec cmd to change options for this plug-in
		@param options [IN] list of options to drive this command with
		@return  kSuccess if we could process it, kFailure otherwise
	 */
	ErrorCode processSetOptionsCommand(const K2Vector<PMString>& options);
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(PnlTrvActionComponent, kPnlTrvActionComponentImpl)

/* Constructor
*/
PnlTrvActionComponent::PnlTrvActionComponent(IPMUnknown* boss)
: CActionComponent(boss)
{
}


/* DoAction
*/
void PnlTrvActionComponent::DoAction(
	IActiveContext* ac, 
	ActionID actionID, 
	GSysPoint mousePoint, 
	IPMUnknown* widget)
{
	switch (actionID.Get())
	{
		case kPnlTrvPopupAboutThisActionID:
		case kPnlTrvAboutActionID:
		{
			this->handleAbout();
			break;
		}

		case kPnlTrvRefreshActionID:
		{
			this->handleRefresh();
			break;
		}

		case kPnlTrvSetOptionsActionID:
		{
			this->handleSetOptions();
			break;
		}

		default:
		{
			break;
		}
	}
}


/* handleAbout
*/
void PnlTrvActionComponent::handleAbout()
{
	CAlert::ModalAlert
	(
	   kPnlTrvAboutBoxStringKey,	// Alert string
	   kOKString, 						// OK button
	   kNullString, 					// No second button
	   kNullString, 					// No third button
	   1,									// Set OK button to default
	   CAlert::eInformationIcon	// Information icon.
	);
}


/* handleRefresh
*/
void PnlTrvActionComponent::handleRefresh()
{
	do
	{
		IControlView* treeWidget = PnlTrvUtils::GetWidgetOnPanel(
			kPnlTrvPanelWidgetID, kPnlTrvTreeViewWidgetID);
		ASSERT(treeWidget);
		if(!treeWidget) {
			break;
		}
			
		InterfacePtr<IPnlTrvDataModel> model(treeWidget, UseDefaultIID());
		ASSERT(model);
		if(!model) {
			break;
		}
		PMString folderRootPath = PnlTrvUtils::GetFolderSelectedPath();
		if(folderRootPath.empty()) {
			break;
		}
		model->Rebuild(folderRootPath);
		InterfacePtr<ITreeViewMgr> 
				iTreeViewMgr(treeWidget, UseDefaultIID());
		ASSERT(iTreeViewMgr);
		if(!iTreeViewMgr){
			break;
		}
		

		iTreeViewMgr->ClearTree();
		iTreeViewMgr->ChangeRoot(kTrue);
		
	} while(kFalse);
}


/* handleSetOptions
*/
void PnlTrvActionComponent::handleSetOptions()
{
	do
	{
		const int32 cCountOfOptions = 1;
        K2Vector<PMString> optionsVec;
        optionsVec.reserve(cCountOfOptions);
		PMString assetPathTitle(kPnlTrvSetOption1StringKey, PMString::kTranslateDuringCall);
		assetPathTitle.SetTranslatable(kFalse);
		SDKFolderChooser folderChooser;
		folderChooser.SetTitle(assetPathTitle);
		folderChooser.ShowDialog();
		if(!folderChooser.IsChosen())
		{
			break;
		}

		PMString folder = folderChooser.GetPath();
		if(folder.empty() == kTrue)
		{
			break;
		}	
		optionsVec.push_back(folder);
		if(folder.empty() == kFalse)
		{
			this->processSetOptionsCommand(optionsVec);
			this->handleRefresh();
		}
	} while(kFalse);	

}


/* processSetOptionsCommand
*/
ErrorCode PnlTrvActionComponent::processSetOptionsCommand(
	const K2Vector<PMString>& options)
{
	ErrorCode retval = kFailure;
	do
	{
		InterfacePtr<IWorkspace>
			iSessionWorkspace(GetExecutionContextSession()->QueryWorkspace());
		ASSERT(iSessionWorkspace);
		if(iSessionWorkspace == nil)
		{
			break;
		}

		InterfacePtr<IPnlTrvOptions>
			iOptions(iSessionWorkspace, UseDefaultIID());
		ASSERT(iOptions);
		if(!iOptions)
		{
			break;
		}
		InterfacePtr<ICommand>
			modOptionsCmd (CmdUtils::CreateCommand(kPnlTrvChangeOptionsCmdBoss));
		ASSERT(modOptionsCmd);
		if(!modOptionsCmd)
		{
			break;
		}	
		modOptionsCmd->SetItemList(UIDList(iSessionWorkspace));

		InterfacePtr<IPnlTrvChangeOptionsCmdData>
			cmdData (modOptionsCmd, UseDefaultIID());
		ASSERT(cmdData);
		if (cmdData == nil)
		{
			break;
		}

		K2Vector<PMString>::const_iterator iter;
		for(iter = options.begin(); iter != options.end(); ++iter)
		{
			cmdData->AddOption(WideString(*iter));	// template path
		}
		retval = CmdUtils::ProcessCommand(modOptionsCmd);
		ASSERT(retval == kSuccess);	
	
	} while(kFalse);

	return retval;
}

//  Generated by Dolly build 17: template "IfPanelMenu".
// End, PnlTrvActionComponent.cpp.




