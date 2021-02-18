//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinksUIButtonObserver.cpp $
//  
//  Owner: lance bushore
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
#include "ISubject.h"
#include "IControlView.h"
#include "ILinksUIPanelPrefs.h"
#include "IRelinkUtils.h"
#include "IActionManager.h"
#include "IApplication.h"
#include "ILinkManager.h"

// ----- Includes -----

#include "CObserver.h"
#include "LinksUIID.h"
#include "ILinksUIUtils.h"
#include "IWidgetUtils.h"
#include "Utils.h"
#include "UIDList.h"
#include "ActionStateList.h"
#include "KeyStates.h"
#include "PreferenceUtils.h"
#include "LinkResourceQuery.h"

// ----- Utility files -----

//========================================================================================
//
//	This observer class is on 4 seperate bosses. It looks at what widget it's on to decide how to behave.
//
//========================================================================================
class LinksUIButtonObserver : public CObserver
{
	public:
		LinksUIButtonObserver(IPMUnknown *boss);
		virtual ~LinksUIButtonObserver();
		
		virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
		
		virtual void AutoAttach();
		virtual void AutoDetach();
	private:
		void UpdateButtonState();
		ActionID fActionID;
};


CREATE_PMINTERFACE(LinksUIButtonObserver, kLinksUIButtonObserverImpl)

//----------------------------------------------------------------------------------------
// LinksUIButtonObserver constructor 
//----------------------------------------------------------------------------------------

LinksUIButtonObserver::LinksUIButtonObserver(IPMUnknown *boss) :
	CObserver(boss),fActionID(kInvalidActionID)
{
}

//----------------------------------------------------------------------------------------
// LinksUIButtonObserver::~LinksUIButtonObserver: 
//----------------------------------------------------------------------------------------

LinksUIButtonObserver::~LinksUIButtonObserver()
{
}

//----------------------------------------------------------------------------------------
// LinksUIButtonObserver::AutoAttach: 
//----------------------------------------------------------------------------------------
void LinksUIButtonObserver::AutoAttach()
{
	if(fActionID == kInvalidActionID)
	{
		InterfacePtr<const IControlView> myView(this,UseDefaultIID());
		WidgetID myWidgetID = myView->GetWidgetID();
		switch(myWidgetID.Get())
		{
			case kRelinkButtonWidgetID:
				fActionID = kLinksUIRelinkActionID;
				break;
			case kUpdateLinkButtonWidgetID:
				fActionID = kLinksUIUpdateLinkActionID;
				break;
			case kEditOriginalButtonWidgetID:
				fActionID = kLinksUIEditOriginalActionID;
				break;
			case kGotoLinkButtonWidgetID:
				fActionID = kGotoLinkActionID;
				break;
			case kCCRelinkButtonWidgetID:
				fActionID = kLinksUIRelinkToCloudAssetActionID;
				break;
            case kAALRelinkButtonWidgetID:
                fActionID = kLinksUIRelinkToAALAssetActionID;
                break;
			default:
				ASSERT_FAIL("Unrecognized widget ID. Don't know what this observer is supposed to do");
		
		
		}
	}
	InterfacePtr<ISubject> subject(this, UseDefaultIID());
	if (subject)
		subject->AttachObserver(this, IID_ITRISTATECONTROLDATA);

	InterfacePtr<ISubject> treeSubject((ISubject*)Utils<IWidgetUtils>()->QueryRelatedWidget( this, kLinksUIPanelTreeWidgetID,IID_ISUBJECT ));
	treeSubject->AttachObserver(ISubject::kRegularAttachment,this, IID_ITREEVIEWCONTROLLER,IID_IOBSERVER);
	
	UpdateButtonState();
}

//----------------------------------------------------------------------------------------
// LinksUIButtonObserver::AutoDetach: 
//----------------------------------------------------------------------------------------
void LinksUIButtonObserver::AutoDetach()
{
	InterfacePtr<ISubject> subject(this, UseDefaultIID());
	if (subject)
		subject->DetachObserver(this, IID_ITRISTATECONTROLDATA);
	
	InterfacePtr<ISubject> treeSubject((ISubject*)Utils<IWidgetUtils>()->QueryRelatedWidget(this,kLinksUIPanelTreeWidgetID,IID_ISUBJECT));
	treeSubject->DetachObserver(ISubject::kRegularAttachment,this, IID_ITREEVIEWCONTROLLER,IID_IOBSERVER);
}

void LinksUIButtonObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	#pragma unused(theSubject,changedBy)
	if (theChange == kTrueStateMessage)
	{
		if(fActionID == kLinksUIRelinkActionID && ::IsOptionAltKeyPressed())
		{
			// relink all missing
			InterfacePtr<const ILinksUIPanelPrefs> linksUIPanelPrefs((ILinksUIPanelPrefs*)::QuerySessionPreferences(IID_ILINKSUIPANELPREFS));
			IDataBase* docDB = linksUIPanelPrefs->GetCurrentDocDB();
			if(docDB)
			{
				UIDList missingLinkRes(docDB);
				InterfacePtr<const ILinkManager> linkMgr(docDB,docDB->GetRootUID(),UseDefaultIID());
				LinkResourceQuery query; 
				query.SetState(ILinkResource::kMissing);
				
				linkMgr->QueryResources(query, kIDLinkClientID, missingLinkRes);
				
				Utils<IRelinkUtils>()->DoRelinkSelectedLinkResources(missingLinkRes,kIDLinkClientID);
			}
		}
		else
		{
			ActionID actionToDo = fActionID;
			if(actionToDo == kLinksUIUpdateLinkActionID && ::IsOptionAltKeyPressed())
				actionToDo = kUpdateAllOutOfDateLinksActionID;
			InterfacePtr<const IApplication> app(GetExecutionContextSession()->QueryApplication());
			InterfacePtr<IActionManager> actionMgr(app->QueryActionManager());
			actionMgr->PerformAction(GetExecutionContextSession()->GetActiveContext(),actionToDo);
		}
	}
	
	if(protocol == IID_ITREEVIEWCONTROLLER && (theChange == kListSelectionChangedMessage || theChange == kLinksUITreeSelectionAlteredMsgBoss))
	{
		UpdateButtonState();
	}
}

void LinksUIButtonObserver::UpdateButtonState()
{
	// if the menu item is enabled, enable the button.
	InterfacePtr<const IApplication> app(GetExecutionContextSession()->QueryApplication());
	InterfacePtr<IActionManager> actionMgr(app->QueryActionManager());
	
	ActionStateList updateList;
	updateList.AddActionID(fActionID);
	actionMgr->UpdateActionStates(GetExecutionContextSession()->GetActiveContext(), &updateList);
	
	InterfacePtr<IControlView> view(this,UseDefaultIID());
	bool shouldEnable = updateList.GetNthActionState(0) & kEnabledAction;
	
//#ifdef DEBUG
//	DebugClassUtilsBuffer idBuf;
//	TRACEFLOW("Links:LinksUI","LinksUIButtonObserver::UpdateButtonState %s button %s\n",shouldEnable ? "enabling" : "disabling", DebugClassUtils::GetIDName(&idBuf,view->GetWidgetID()));
//#endif
	if(shouldEnable)
		view->Enable();
	else
		view->Disable();
}
